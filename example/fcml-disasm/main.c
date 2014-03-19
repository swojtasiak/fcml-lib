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
#include <fcml_renderer.h>

fcml_string conditions[] = {
	"o", "b", "e", "be", "s", "p", "l", "le"
};

fcml_string prefix_types[] = {
	"FCML_PT_GROUP_UNKNOWN",
	"FCML_PT_GROUP_1",
	"FCML_PT_GROUP_2",
	"FCML_PT_GROUP_3",
	"FCML_PT_GROUP_4",
	"FCML_PT_REX",
	"FCML_PT_VEX",
	"FCML_PT_XOP",
};
fcml_string operand_types[] = {
	"FCML_EOT_NONE",
	"FCML_EOT_IMMEDIATE",
	"FCML_EOT_FAR_POINTER",
	"FCML_EOT_ADDRESS",
	"FCML_EOT_REGISTER"
};

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

fcml_string get_boolean( fcml_bool b ) {
	return b ? "true" : "false";
}

void print_instruction_details( fcml_st_dialect *dialect, fcml_st_disassembler_result *result, fcml_st_render_config *render_config ) {

	int i;

	fcml_char buffer[FCML_REND_MAX_BUFF_LEN];

	fcml_ceh_error error = fcml_fn_render( dialect, render_config, buffer, sizeof( buffer ), result );
	if( error ) {
		printf( "Can not render instruction. Error code: %d\n", error );
		return;
	}

	printf("Basic information:\n");

	printf(" Disassembled instruction: %s\n", buffer);

	fcml_st_instruction *instruction = &(result->instruction);

	printf(" Mnemonic: %s\n", instruction->mnemonic );

	if( instruction->is_conditional ) {
		char neg[2] = {0};
		if( instruction->condition.is_negation ) {
			neg[0] = 'n';
		}
		printf(" Conditional instruction. Condition: \"%s%s\".\n", neg, conditions[ instruction->condition.condition_type ] );
	}

	if( instruction->hints ) {

		printf(" Instruction hints:");

		if( instruction->hints & FCML_HINT_FAR_POINTER ) {
			printf(" FCML_HINT_FAR_POINTER");
		}

		if( instruction->hints & FCML_HINT_NEAR_POINTER ) {
			printf(" FCML_HINT_NEAR_POINTER");
		}

		if( instruction->hints & FCML_HINT_LONG_FORM_POINTER ) {
			printf(" FCML_HINT_LONG_FORM_POINTER");
		}

		if( instruction->hints & FCML_HINT_INDIRECT_POINTER ) {
			printf(" FCML_HINT_INDIRECT_POINTER");
		}

		printf("\n");
	}

	if( instruction->prefixes ) {

		printf(" Explicit prefixes:");

		if( instruction->prefixes & FCML_PREFIX_LOCK ) {
			printf(" FCML_PREFIX_LOCK");
		}
		if( instruction->prefixes & FCML_PREFIX_REPNE ) {
			printf(" FCML_PREFIX_REPNE");
		}
		if( instruction->prefixes & FCML_PREFIX_REP ) {
			printf(" FCML_PREFIX_REP");
		}
		if( instruction->prefixes & FCML_PREFIX_XACQUIRE ) {
			printf(" FCML_PREFIX_XACQUIRE");
		}
		if( instruction->prefixes & FCML_PREFIX_XRELEASE ) {
			printf(" FCML_PREFIX_XRELEASE");
		}
		if( instruction->prefixes & FCML_PREFIX_BRANCH_HINT ) {
			printf(" FCML_PREFIX_BRANCH_HINT");
		}
		if( instruction->prefixes & FCML_PREFIX_NOBRANCH_HINT ) {
			printf(" FCML_PREFIX_NOBRANCH_HINT");
		}

		printf("\n");
	}

	printf( " Number of operands: %d\n", instruction->operands_count );

	printf( "  Operands:\n" );

	for( i = 0; i < instruction->operands_count; i++ ) {
		printf("   Operand: %d\n", i + 1 );
		fcml_st_operand *operand = &(instruction->operands[i]);
		printf("    Type: %s\n", operand_types[ operand->type ] );
		switch( operand->type ) {
		case FCML_EOT_IMMEDIATE: {
			fcml_st_immediate *immediate = &(operand->immediate);
			printf("    Signed: %s\n", get_boolean( immediate->is_signed ) );
			printf("    Size: %d\n", immediate->imm_size );
			printf("    Value: " );
			switch( immediate->imm_size ) {
			case FCML_DS_8:
				printf("0x%02x\n", immediate->imm8);
				break;
			case FCML_DS_16:
				printf("0x%04x\n", immediate->imm16);
				break;
			case FCML_DS_32:
				printf("0x%08x\n", immediate->imm32);
				break;
			case FCML_DS_64:
				printf("0x%016llx\n", immediate->imm64);
				break;
			}
			break;
		}
		case FCML_EOT_FAR_POINTER:
			break;
		case FCML_EOT_ADDRESS:
			break;
		case FCML_EOT_REGISTER:
			break;
		}
	}

	printf( "Details:\n" );

	fcml_st_instruction_details *details = &(result->instruction_details);

	printf(" Instruction code: 0x");
	for( i = 0; i < details->instruction_size; i++ ) {
		printf( "%02x", details->instruction_code[i] );
	}
	printf("\n");

	printf( " Instruction code length: %d\n", details->instruction_size );
	printf( " Pseudo-op: %s\n", details->is_pseudo_op ? "true" : "false" );
	printf( " Shortcut: %s\n", details->is_shortcut ? "true" : "false" );

	/* ModR/M */

	fcml_st_decoded_modrm_details *modrm_details = &(details->modrm_details);
	if( modrm_details ) {
		printf( " ModR/M details:\n" );
		printf( "  Is RIP: %s\n", get_boolean( modrm_details->is_rip ) );
		printf( "  ModR/M byte: 0x%02x\n", modrm_details->modrm );
		if( modrm_details->sib.is_not_null ) {
			printf( "  SIB byte: 0x%02x\n", modrm_details->sib );
		}
	}

	/* Prefixes details. */

	fcml_st_prefixes_details *prefixes_details = &(details->prefixes_details);
	if( prefixes_details->prefixes_bytes_count ) {
		printf( " Prefixes details:\n" );
		printf( "  Prefixes size in bytes: %d\n", prefixes_details->prefixes_bytes_count );
		printf( "  Number of available prefixes: %d\n", prefixes_details->prefixes_count );
		printf( "  Available prefixes (flags):" );
		if( prefixes_details->is_branch ) {
			printf(" branch");
		}
		if( prefixes_details->is_lock ) {
			printf(" lock");
		}
		if( prefixes_details->is_nobranch ) {
			printf(" nobranch");
		}
		if( prefixes_details->is_rep ) {
			printf(" rep");
		}
		if( prefixes_details->is_repne ) {
			printf(" repne");
		}
		if( prefixes_details->is_rex ) {
			printf(" rex");
		}
		if( prefixes_details->is_vex ) {
			printf(" vex");
		}
		if( prefixes_details->is_xacquire ) {
			printf(" xacquire");
		}
		if( prefixes_details->is_xrelease ) {
			printf(" xrelease");
		}
		if( prefixes_details->is_xop ) {
			printf(" xop");
		}

		printf( "\n  Prefixes fields:");

		if( prefixes_details->is_vex || prefixes_details->is_xop )
			printf( " mmmm:%d", prefixes_details->mmmm );
		if( prefixes_details->is_vex || prefixes_details->is_xop || prefixes_details->is_rex )
			printf( " r:%d", prefixes_details->r );
		if( prefixes_details->is_vex || prefixes_details->is_xop || prefixes_details->is_rex )
			printf( " x:%d", prefixes_details->x );
		if( prefixes_details->is_vex || prefixes_details->is_xop || prefixes_details->is_rex )
			printf( " b:%d", prefixes_details->b );
		if( prefixes_details->is_vex || prefixes_details->is_xop || prefixes_details->is_rex )
			printf( " w:%d", prefixes_details->w );
		if( prefixes_details->is_vex || prefixes_details->is_xop )
			printf( " vvvv:%d", prefixes_details->vvvv );
		if( prefixes_details->is_vex || prefixes_details->is_xop )
			printf( " l:%d", prefixes_details->l );
		if( prefixes_details->is_vex || prefixes_details->is_xop )
			printf( " pp:%d", prefixes_details->pp );

		printf( "\n  Available prefixes (details):\n" );

		for( i = 0; i < prefixes_details->prefixes_count; i++ ) {
			fcml_st_instruction_prefix *prefix = &(prefixes_details->prefixes[i]);
			printf("   Byte: 0x%02x, Type %s, Mandatory: %s, XOP/VEX bytes: 0x%02x, 0x%02x.\n", prefix->prefix, prefix_types[ prefix->prefix_type ], get_boolean( prefix->mandatory_prefix ), prefix->vex_xop_bytes[0], prefix->vex_xop_bytes[1] );
		}

	}

	printf( " Operands details:\n" );

	for( i = 0; i < instruction->operands_count; i++ ) {
		printf("  Operand: %d\n", i + 1 );
		fcml_st_operand_details *operand_details = &(details->operand_details[i]);
		printf("   Access mode: " );
		if( operand_details->access_mode & FCML_AM_READ ) {
			printf( "FCML_AM_READ" );
		}
		if( operand_details->access_mode & FCML_AM_WRITE ) {
			printf( "FCML_AM_WRITE" );
		}
		printf("\n");
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

	fcml_st_render_config render_config = {0};

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
		} else if( strcmp( argv[i], "-rc" ) == 0 ) {
			render_config.render_flags |= FCML_REND_FLAG_RENDER_CODE;
		} else if( strcmp( argv[i], "-rh" ) == 0 ) {
			render_config.render_flags |= FCML_REND_FLAG_HEX_IMM | FCML_REND_FLAG_HEX_DISPLACEMENT;
		} else if( strcmp( argv[i], "-rz" ) == 0 ) {
			render_config.render_flags |= FCML_REND_FLAG_REMOVE_LEADING_ZEROS;
		} else if( strcmp( argv[i], "-rs" ) == 0 ) {
			render_config.render_flags |= FCML_REND_FLAG_RENDER_DEFAULT_SEG;
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
				code[index++] = (fcml_uint8_t)strtol( buff, &res, 16 );
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
	if( !error ) {
		print_instruction_details( dialect, &result, &render_config );
	} else {
		printf("Disassembling failed with error code: %d\n", error );
		print_error_msg( &(result.errors) );
	}

	fcml_fn_disassembler_result_free( &result );

	/* Free everything. */

	fcml_fn_disassembler_free( disassembler );

	fcml_fn_dialect_free( dialect );

	return 0;
}
