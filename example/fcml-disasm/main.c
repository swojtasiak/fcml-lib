/*
 * main.c
 *
 *  Created on: Mar 18, 2014
 *      Author: tas
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>

#include <fcml_intel_dialect.h>
#include <fcml_gas_dialect.h>
#include <fcml_disassembler.h>

void print_error_msg( fcml_st_ceh_error_container *errors ) {
	fcml_st_ceh_error_info *error = errors->errors;
	while( error ) {
		// Print error message.
		if( error->level == FCML_EN_CEH_EL_WARN ) {
			puts("WARN: ");
		} else if( error->level == FCML_EN_CEH_EL_ERROR ) {
			puts("ERROR: ");
		}
		printf("%3d: %s\n", error->code, error->message );
		error = error->next_error;
	}
}

int main(int argc, char **argv) {

	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

	/* Interpret arguments. */

	if( argc <= 1 ) {
		printf("Bad arguments.\n");
		exit(1);
	}

	fcml_st_disassembler_context context = {0};

	fcml_bool gas_dialect = 0;

	fcml_uint8_t code[FCML_INSTRUCTION_SIZE] = {0};

	fcml_int code_length = 0;

	int i;
	for( i = 1; i < argc; i++ ) {
		if( strcmp( argv[i], "-m16" ) == 0 ) {
			context.entry_point.addr_form = FCML_AF_16_BIT;
		} else if( strcmp( argv[i], "-m32" ) == 0 ) {
			context.entry_point.addr_form = FCML_AF_32_BIT;
		} else if( strcmp( argv[i], "-m64" ) == 0 ) {
			context.entry_point.addr_form = FCML_AF_64_BIT;
		} else if( strcmp( argv[i], "-asa16" ) == 0 ) {
			context.entry_point.address_size_attribute = FCML_DS_16;
		} else if( strcmp( argv[i], "-asa32" ) == 0 ) {
			context.entry_point.address_size_attribute = FCML_DS_32;
		} else if( strcmp( argv[i], "-asa64" ) == 0 ) {
			context.entry_point.address_size_attribute = FCML_DS_64;
		} else if( strcmp( argv[i], "-osa16" ) == 0 ) {
			context.entry_point.operand_size_attribute = FCML_DS_16;
		} else if( strcmp( argv[i], "-osa32" ) == 0 ) {
			context.entry_point.operand_size_attribute = FCML_DS_32;
		} else if( strcmp( argv[i], "-osa64" ) == 0 ) {
			context.entry_point.operand_size_attribute = FCML_DS_64;
		} else if( strcmp( argv[i], "-ip" ) == 0 ) {
			if( ++i < argc ) {
				char *res;
				errno = 0;
				context.entry_point.ip = strtoll( argv[i], &res, 16 );
				if ((errno == ERANGE && (context.entry_point.ip == FCML_INT64_MAX || context.entry_point.ip == FCML_INT64_MIN)) || (errno != 0 && context.entry_point.ip == 0) || (argv[i] == res) ) {
				   perror("Wrong instruction pointer.");
				   exit(EXIT_FAILURE);
			    }
			} else {
				printf("IP not set.\n");
				exit(1);
			}
		} else if( strcmp( argv[i], "-s" ) == 0 ) {
			context.configuration.short_forms = FCML_TRUE;
		} else if( strcmp( argv[i], "-e" ) == 0 ) {
			context.configuration.extend_disp_to_asa = FCML_TRUE;
		} else if( strcmp( argv[i], "-gas" ) == 0 ) {
			gas_dialect = FCML_TRUE;
		} else if( i + 1 == argc ) {
			/* Parse instruction code. */
			char buff[3] = {0};
			char *code_str = argv[i];
			fcml_int code_str_size = strlen( code_str );
			fcml_int j, index = 0;
			for( j = 0; j < code_str_size; j += 2 ) {
				buff[0] = code_str[j];
				buff[1] = 0;
				if( j + 2 <= code_str_size ) {
					buff[1] = code_str[j + 1];
				}
				if( j == 0 && strcmp( buff, "0x" ) == 0 ) {
					continue;
				}
				char *res;
				errno = 0;
				code[index++] = strtol( buff, &res, 16 );
				fcml_int8_t code_byte = code[index - 1];
				if ((errno == ERANGE && (code_byte == FCML_INT8_MAX || code_byte == FCML_INT8_MIN)) || (errno != 0 && code_byte == 0) || (buff == res) ) {
				   printf("Wrong instruction code: %s\n", code_str );
				   exit(EXIT_FAILURE);
				}
			}
			code_length = index;
		}
	}

	if( !context.entry_point.addr_form ) {
		printf("Addressing mode not specified.\n");
		exit(1);
	}

	if( !code_length ) {
		printf("Instruction code not specified.\n");
		exit(1);
	}

	/* Initialize dialect to use with disassembler. */

	fcml_st_dialect *dialect;

	if( gas_dialect ) {
		error = fcml_fn_dialect_init_gas( FCML_GAS_DIALECT_CF_DEFAULT, &dialect );
	} else {
		error = fcml_fn_dialect_init_intel( FCML_INTEL_DIALECT_CF_DEFAULT, &dialect );
	}

	if( error ) {
		printf( "Can not initialize dialect, error: %d\n", error );
		exit(1);
	}

	/* Initialize disassembler for used dialect. */

	fcml_st_disassembler *disassembler;

	error = fcml_fn_disassembler_init( dialect, &disassembler );
	if( error ) {
		fcml_fn_dialect_free( dialect );
		printf( "Can not initialize assembler, error: %d\n", error );
		exit(1);
	}

	/* Prepare disassembler context. */

	context.disassembler = disassembler;
	context.code = code;
	context.code_length = code_length;

	fcml_st_disassembler_result result;

	fcml_fn_disassembler_result_prepare( &result );

	error = fcml_fn_disassemble( &context, &result );
	if( error ) {
		printf("Disassembling failed with error code: %d\n", error );
		print_error_msg( &(result.errors) );
	}

	fcml_fn_disassembler_result_free( &result );

	/* Free everything. */

	fcml_fn_disassembler_free( disassembler );

	fcml_fn_dialect_free( dialect );

	return 0;
}
