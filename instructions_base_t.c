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
#include "fcml_disassembler.h"
#include "fcml_asm_dialect_intel.h"
#include "fcml_rend_intel.h"

extern fcml_st_assembler *assembler;

fcml_bool IA3264_instruction_test( fcml_uint8_t *code, int size, fcml_bool x64, fcml_string mnemonic, fcml_bool should_fail, fcml_bool only_print_result, fcml_bool enable_rip, fcml_en_assembler_optimizers optimizer, fcml_uint16_t opt_flags, fcml_bool multiple_assemblation_result, fcml_bool only_assemble ) {

	fcml_bool success = FCML_TRUE;

	fcml_st_disassembler_result *dis_result = NULL;

	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

	fcml_st_dialect_context dialect = fcml_fn_get_intel_dialect_context();

	fcml_st_disassembler *disassembler;

	if( !only_assemble ) {

		error = fcml_fn_disassembler_init( &dialect, &disassembler );
		if( error ) {
			// Error.
			printf( "Can not allocate disassembler." );
			return FCML_FALSE;
		}

		fcml_st_disassembler_context context;
		context.configuration.use_short_form_mnemonics = FCML_FALSE;
		context.configuration.imm_extend_to_osa = FCML_TRUE;
		context.configuration.extend_displacement_to_asa = FCML_TRUE;
		context.disassembler = disassembler;
		context.addr_form = x64 ? IRA_MOD_64BIT : FCML_AF_32_BIT;
		context.address_size_attribute = 0;
		context.operand_size_attribute = 0;
		if( !multiple_assemblation_result ) {
			context.code_address = code;
			context.code_size = size;
		} else {
			context.code_address = code + 2;
			context.code_size = code[1];
		}
		if( x64 ) {
			context.ip.rip = 0x0000800000401000;
		} else {
			context.ip.eip = 0x00401000;
		}

		// Disassemble.
		error = fcml_fn_disassemble( &context, &dis_result );

	}

	if( error == FCML_CEH_GEC_NO_ERROR ) {

		fcml_bool is_67 = FCML_FALSE;
		fcml_bool is_66 = FCML_FALSE;

		if( !only_assemble ) {

			if( only_print_result ) {
				printf("Instruction: %s\n", mnemonic);
			}

			if( should_fail ) {
				printf("Should fail: %s\n", mnemonic);
				success = FCML_FALSE;
				fcml_fn_disassemble_result_free( dis_result );
				fcml_fn_disassembler_free( disassembler );
				return success;
			}

			// Looking for 0x67 prefix.
			int i;
			for( i = 0; i < FCML_DASM_PREFIXES_COUNT; i++ ) {
				if( dis_result->prefixes.prefixes[i].prefix == 0x67 ) {
					is_67 = FCML_TRUE;
				}
				if( dis_result->prefixes.prefixes[i].prefix == 0x66 ) {
                    is_66 = FCML_TRUE;
                }
			}

			// Print.
			char buffer[512] = {0};

			fcml_st_memory_stream stream;
			stream.base_address = buffer;
			stream.offset = 0;
			stream.size = sizeof( buffer );

			error = fcml_fn_rend_render_instruction( &dialect, &stream, dis_result, FCML_REND_FLAG_HEX_IMM | FCML_REND_FLAG_COND_SHOW_CARRY | FCML_REND_FLAG_HEX_DISPLACEMENT );
			if( error ) {
				printf("Disassemblation failed, with error code: %d\n", error );
				if( !only_print_result ) {
					success = FCML_FALSE;
				}
				fcml_fn_disassemble_result_free( dis_result );
				fcml_fn_disassembler_free( disassembler );
				return success;
			}

			if( strcmp( buffer, mnemonic ) != 0 ) {
				printf("Disassemblation failed, should be: %s (Was: %s)\n", mnemonic, buffer);
				if( !only_print_result ) {
					success = FCML_FALSE;
				}
				fcml_fn_disassemble_result_free( dis_result );
				fcml_fn_disassembler_free( disassembler );
				return success;
			} else {
				if( !only_print_result ) {
					CU_ASSERT(FCML_TRUE);
				}
			}

		}

		// Assemblation.
		fcml_st_x64iap_parser_result *result;
		fcml_ceh_error error = fcml_x64iap_parse( mnemonic, &result );
		if( error ) {
			printf("Can not parse: %s\n", mnemonic );
			if( !only_print_result ) {
				success = FCML_FALSE;
			}
			fcml_x64iap_free( result );
			fcml_fn_disassemble_result_free( dis_result );
			fcml_fn_disassembler_free( disassembler );
			return success;
		}

		fcml_uint16_t opt_flags = 0;

		fcml_st_assembler_context context;
		context.assembler = assembler;
		context.effective_address_size = 0;
		context.effective_operand_size = 0;
		context.addr_form = x64 ? FCML_AF_64_BIT : FCML_AF_32_BIT;

		if( is_67 ) {
			if( x64 ) {
				opt_flags = FCML_OPTF_ASA_32;
			} else {
				opt_flags = FCML_OPTF_ASA_16;
			}
		}
		if( is_66 ) {
            opt_flags |= FCML_OPTF_OSA_16;
        }

		context.configuration.choose_sib_encoding = FCML_FALSE;
		context.configuration.choose_rip_encoding = enable_rip;
		context.configuration.optimizer = FCML_EN_OP_DEFAULT_ADDRESSING_MODE_OPTIMIZER;
		context.configuration.optimizer_flags = opt_flags;
		context.configuration.force_unnecessary_rex_prefix = FCML_FALSE;
		context.configuration.force_three_byte_VEX = FCML_FALSE;
		if( x64 ) {
			context.ip.rip = 0x0000800000401000;
		} else {
			context.ip.eip = 0x00401000;
		}

		fcml_st_assembler_result *asm_result = NULL;
		error = fcml_fn_assemble( &context, result->instruction, &asm_result );
		if( error ) {
		    if( !should_fail ) {
		        printf("Can not assemble: %s\n", mnemonic );
		    }
			if( !only_print_result ) {
				success = should_fail;
			}
		} else {

            fcml_bool looking_for_instruction = FCML_TRUE;
            fcml_bool found = FCML_FALSE;

            fcml_uint8_t *assembled_code[100];
            int assembled_code_len[100];
            int assembled_code_index = 0;

            int j = 0;
            for( j = 0; j < 2; j++ ) {

                fcml_st_coll_list *inst = asm_result->instructions;

                assembled_code_index = 0;

                // Fill code array.
                fcml_st_coll_list_element *element = inst->head;
                while( element ) {
                    fcml_st_assembled_instruction *assembled_instruction = (fcml_st_assembled_instruction *)element->item;
                    assembled_code_len[assembled_code_index] = assembled_instruction->code_length;
                    assembled_code[assembled_code_index++] = assembled_instruction->code;
                    element = element->next;
                }

                if( !only_print_result ) {
                    if( !multiple_assemblation_result && inst->size != 1 ) {
                        found = FCML_FALSE;
                        break;
                    }
                }

                element = inst->head;
                while( element ) {
                    fcml_st_assembled_instruction *assembled_instruction = (fcml_st_assembled_instruction *)element->item;
                    fcml_bool differ = FCML_FALSE;
                    if( !only_print_result ) {
                        int i;
                        if( multiple_assemblation_result ) {
                            int code_index = 0;
                            fcml_uint8_t instruction_count = code[code_index++];
                            for( i = 0; i < instruction_count; i++ ) {
                                fcml_uint8_t code_size = code[code_index++];
                                fcml_uint8_t *code_buff = &(code[code_index]);
                                code_index += code_size;
                                fcml_uint8_t k;
                                differ = FCML_FALSE;
                                if( code_size != assembled_instruction->code_length ) {
                                    differ = FCML_TRUE;
                                } else {
                                    for( k = 0; k < code_size; k++ ) {
                                        if( code_buff[k] != assembled_instruction->code[k] ) {
                                            differ = FCML_TRUE;
                                            break;
                                        }
                                    }
                                }
                                if( !differ ) {
                                    break;
                                }
                            }
                        } else {
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
                        }
                        if( differ ) {
                            found = FCML_FALSE;
                            break;
                        } else {
                            found = FCML_TRUE;
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

            if( !found ) {
                if( !only_print_result && !should_fail ) {
                    printf("Can not assemble: %s\n", mnemonic);
                }
                if( !only_print_result ) {
                    success = should_fail;
                }
            }

            // Prints test code.
            if( assembled_code_index >= 1 && ( only_print_result || !found ) ) {

               // Mnemonic.
               fcml_string macro;
               if( assembled_code_index > 1 ) {
                   macro = ( x64 ) ? "FCML_I64_M" : "FCML_I32_M";
               } else {
                   macro = ( x64 ) ? "FCML_I64" : "FCML_I32";
               }

               printf("%s( \"%s\", ", macro, mnemonic );

               // Code.

               if( assembled_code_index > 1 ) {
                   // multi.
                   printf( "%d, ", assembled_code_index );
                   int i, j;
                   for( i = 0; i < assembled_code_index; i++ ) {
                       if( i > 0 ) {
                           printf(", ");
                       }
                       printf( "FCML_MI( " );
                       for( j = 0; j < assembled_code_len[i]; j++ ) {
                           if( j > 0 ) {
                               printf(", ");
                           }
                           printf( "0x%02"PRIx8, assembled_code[i][j] );
                       }
                       printf( " )" );
                   }
               } else if ( assembled_code_index == 1  ) {
                   int i;
                   for( i = 0; i < assembled_code_len[0]; i++ ) {
                       if( i > 0 ) {
                           printf(", ");
                       }
                       printf( "0x%02"PRIx8, assembled_code[0][i] );
                   }
               }

               printf(" );\n");
            }

		}

		fcml_fn_assembler_result_free( asm_result );

		fcml_x64iap_free( result );


	} else {

		success = should_fail;

	}

	fcml_fn_disassemble_result_free( dis_result );
	fcml_fn_disassembler_free( disassembler );

	return success;
}

fcml_bool IA3264_instruction_diss_test( fcml_uint8_t *code, int size, fcml_bool x64, fcml_string mnemonic, fcml_bool should_fail, fcml_uint32_t flags, fcml_bool print_only ) {

	fcml_bool success = FCML_TRUE;

	struct ira_disassemble_info info;
	info.address = code;
	info.size = size;
	info.address_size_attribute = 0;
	info.operand_size_attribute = 0;
	info.mode = x64 ? IRA_MOD_64BIT : IRA_MOD_32BIT;
	info.config.flags = flags;

	if( x64 ) {
		info.instruction_pointer.rip = 0x0000800000401000;
	} else {
		info.instruction_pointer.eip = 0x00401000;
	}

	struct ira_disassemble_result result;

	// Disassemble.
	ira_disassemble( &info, &result );

	if( result.code == RC_OK ) {

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
		    if( !should_fail ) {
		        printf("Disassemblation failed, should be: %s (Was: %s)\n", mnemonic, buffer);
		    }
			return should_fail ? FCML_TRUE : FCML_FALSE;
		} else {
			if( result.instruction_size != size ) {
				printf("Instruction size: %d Disassembled code size: %d (%s)\n", (fcml_uint32_t)result.instruction_size, size, mnemonic);
				success = FCML_FALSE;
			} else {
			    if( !print_only ) {
			        if( should_fail ) {
                        printf("Should fail: %s\n", mnemonic);
                        success = FCML_FALSE;
                    } else {
                        CU_ASSERT(FCML_TRUE);
                    }
			    }
			}
		}

	} else {
	    if( !print_only ) {
	        CU_ASSERT(FCML_TRUE);
	    }
	}

	return success;
}

