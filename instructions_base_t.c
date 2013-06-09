/*
 * instructions_base_t.c
 *
 *  Created on: 01-06-2013
 *      Author: tAs
 */

#include "instructions_base_t.h"

#include <string.h>
#include <stdio.h>

#include "fcml_assembler.h"
#include "ira.h"
#include "ira_ren_intel.h"
#include "fcml_x64intel_asm_parser.h"

void IA3264_instruction_test( fcml_uint8_t *code, int size, fcml_bool x64, fcml_string mnemonic, fcml_bool failed, fcml_bool only_print_result, fcml_bool enable_rip ) {

	struct ira_disassemble_info info;
	info.address = code;
	info.size = size;
	info.address_size_attribute = 0;
	info.operand_size_attribute = 0;
	info.mode = x64 ? IRA_MOD_64BIT : IRA_MOD_32BIT;
	info.config.flags = 0;

	if( x64 ) {
		info.instruction_pointer.rip = 0x0000800000401000;
	} else {
		info.instruction_pointer.eip = 0x00401000;
	}

	struct ira_disassemble_result result;

	// Disassemble.
	ira_disassemble( &info, &result );

	if( result.code == RC_OK ) {

		if( only_print_result ) {
			printf("Instruction: %s\n", mnemonic);
		}

		if( !failed ) {
			printf("Should fail: %s\n", mnemonic);
			CU_FAIL(FCML_FALSE);
			return;
		}

		// Print.
		char buffer[512] = {0};

		struct ira_intel_format_info format;
		format.show_zero_displacement = 0;
		format.show_extended_displacement = 1;
		format.immediate_hex_display = 1;
		format.immediate_signed = 1;
		format.show_instruction_code = 0;
		format.show_extended_immediate = 1;
		format.show_conditional_mnemonics_for_carry_flag = 1;
		format.conditional_suffix_group = 0;

		ira_format_intel_instruction( buffer, sizeof(buffer), &result, &format );

		if( strcmp( buffer, mnemonic ) != 0 ) {
			printf("Disassemblation failed, should be: %s (Was: %s)\n", mnemonic, buffer);
			if( !only_print_result ) {
				CU_ASSERT( FCML_FALSE );
			}
			return;
		} else {
			if( !only_print_result ) {
				CU_ASSERT(FCML_TRUE);
			}
		}

		// Assemblation.
		fcml_st_x64iap_parser_result *result;
		fcml_ceh_error error = fcml_x64iap_parse( mnemonic, &result );
		if( error ) {
			printf("Can not parse: %s\n", mnemonic );
			if( !only_print_result ) {
				CU_ASSERT( FCML_FALSE );
			}
			return;
		}

		fcml_st_assembler_context context;
		context.effective_address_size = 0;
		context.effective_operand_size = 0;
		context.addr_form = x64 ? FCML_AF_64_BIT : FCML_AF_32_BIT;
		context.configuration.choose_sib_encoding = FCML_FALSE;
		context.configuration.choose_rip_encoding = enable_rip;

		fcml_st_assembler_result *asm_result;
		error = fcml_fn_assemble( &context, result->instruction, &asm_result );
		if( error ) {
			printf("Can not assemble: %s\n", mnemonic );
			if( !only_print_result ) {
				CU_ASSERT( FCML_FALSE );
			}
		} else {

			fcml_bool looking_for_instruction = FCML_TRUE;
			fcml_bool found = FCML_FALSE;

			int j = 0;
			for( j = 0; j < 2; j++ ) {

				fcml_st_coll_list *inst = asm_result->instructions;
				fcml_st_coll_list_element *element = inst->head;
				while( element ) {
					fcml_st_assembled_instruction *assembled_instruction = (fcml_st_assembled_instruction *)element->item;
					fcml_bool differ = FCML_FALSE;
					if( !only_print_result ) {
						int i;
						if( size == assembled_instruction->code_length ) {
							for( i = 0; i < size; i++ ) {
								if( code[i] != assembled_instruction->code[i] ) {
									differ = FCML_TRUE;
									break;
								}
							}
						} else {
							differ = FCML_TRUE;
						}
						if( !differ ) {
							found = FCML_TRUE;
							break;
						}
					}
					if( only_print_result || ( differ && !looking_for_instruction ) ) {
#if FCML_DEBUG
						printf( "Index: %d\nOriginal code : ", assembled_instruction->__def_index );
#else
						printf( "Original code : " );
#endif
						int i;
						for( i = 0; i < size; i++ ) {
							printf( "%02"PRIx8, code[i] );
						}
						printf( "\nAssembled code: " );
						for( i = 0; i < assembled_instruction->code_length; i++ ) {
							printf( "%02"PRIx8, assembled_instruction->code[i] );
						}
						printf("\n");
					}
					element = element->next;
				}

				if( found ) {
					break;
				}

				looking_for_instruction = FCML_FALSE;

				if( only_print_result ) {
					break;
				}
			}

			if( !only_print_result && !found ) {
				printf("Can not assemble: %s\n", mnemonic);
				if( !only_print_result ) {
					CU_ASSERT( FCML_FALSE );
				}
			}

		}

		fcml_fn_assemble_free( asm_result );

		fcml_x64iap_free( result );


	} else {

		if( !failed ) {
			return;
		}

		if( strcmp( "FAIL", mnemonic ) != 0 ) {
			printf("Failed: %s\n", mnemonic);
			if( !only_print_result ) {
				CU_ASSERT( FCML_FALSE );
			}
		}
	}

}

void IA3264_instruction_diss_test( fcml_uint8_t *code, int size, fcml_bool x64, fcml_string mnemonic, fcml_bool failed ) {

	struct ira_disassemble_info info;
	info.address = code;
	info.size = size;
	info.address_size_attribute = 0;
	info.operand_size_attribute = 0;
	info.mode = x64 ? IRA_MOD_64BIT : IRA_MOD_32BIT;
	info.config.flags = 0;

	if( x64 ) {
		info.instruction_pointer.rip = 0x0000800000401000;
	} else {
		info.instruction_pointer.eip = 0x00401000;
	}

	struct ira_disassemble_result result;

	// Disassemble.
	ira_disassemble( &info, &result );

	if( result.code == RC_OK ) {

		if( !failed ) {
			printf("Should fail: %s\n", mnemonic);
			CU_FAIL(FCML_FALSE);
			return;
		}

		// Print.
		char buffer[512] = {0};

		struct ira_intel_format_info format;
		format.show_zero_displacement = 0;
		format.show_extended_displacement = 1;
		format.immediate_hex_display = 1;
		format.immediate_signed = 1;
		format.show_instruction_code = 0;
		format.show_extended_immediate = 1;
		format.show_conditional_mnemonics_for_carry_flag = 1;
		format.conditional_suffix_group = 0;

		ira_format_intel_instruction( buffer, sizeof(buffer), &result, &format );

		if( strcmp( buffer, mnemonic ) != 0 ) {
			printf("Disassemblation failed, should be: %s (Was: %s)\n", mnemonic, buffer);
			CU_ASSERT( FCML_FALSE );
			return;
		} else {

			if( result.instruction_size != size ) {
				printf("Instruction size: %d Disassembled code size: %d (%s)\n", (fcml_uint32_t)result.instruction_size, size, mnemonic);
				CU_ASSERT(FCML_FALSE);
			} else {
				CU_ASSERT(FCML_TRUE);
			}
		}

	} else {
		CU_ASSERT(FCML_TRUE);
	}

}

