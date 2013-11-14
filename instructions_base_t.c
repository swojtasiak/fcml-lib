/*
 * instructions_base_t.c
 *
 *  Created on: 01-06-2013
 *      Author: tAs
 */

#include "instructions_base_t.h"

#include <string.h>
#include <stdio.h>
#include <inttypes.h>
#include <fcml_env.h>

#include "fcml_assembler.h"
#include "fcml_x64intel_asm_parser.h"
#include "fcml_disassembler.h"
#include "fcml_dialect_intel.h"
#include "fcml_rend_intel.h"

extern fcml_st_asm_assembler *assembler;

extern fcml_st_dasm_disassembler *disassembler;

extern fcml_st_dialect_context dialect;

void fcml_ifn_ts_set_ip( fcml_st_instruction_pointer *ip, fcml_en_addr_form addr_form ) {
	switch( addr_form ) {
	case FCML_AF_16_BIT:
	case FCML_AF_32_BIT:
		ip->eip = 0x00401000;
		break;
	case FCML_AF_64_BIT:
		ip->rip = 0x0000800000401000;
		break;
	}
}

fcml_bool fcml_fn_ts_instruction_test( fcml_uint8_t *code, int size, fcml_en_addr_form addr_form, fcml_string mnemonic, fcml_uint32_t t_flags, fcml_uint32_t rend_flags ) {

	fcml_bool success = FCML_TRUE;

	fcml_st_dasm_disassembler_result *dis_result = NULL;

	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

	if( !(t_flags & FCML_TSF_ASM_ONLY) ) {

		fcml_st_dasm_disassembler_context context;
		context.configuration.use_short_form_mnemonics = FCML_FALSE;
		context.configuration.extend_displacement_to_asa = FCML_TRUE;
		context.configuration.conditional_group = FCML_DASM_CONDITIONAL_GROUP_1;
		context.configuration.choose_carry_conditional_mnemonic = FCML_TRUE;
		context.configuration.extend_displacement_to_asa = FCML_TRUE;
		context.disassembler = disassembler;
		context.addr_form = addr_form;
		context.address_size_attribute = 0;
		context.operand_size_attribute = 0;
		if( !(t_flags & FCML_TSF_MULTI_ASM_RESULTS) ) {
			context.code_address = code;
			context.code_size = size;
		} else {
			context.code_address = code + 2;
			context.code_size = code[1];
		}

		fcml_ifn_ts_set_ip( &(context.ip), addr_form );

		// Disassemble.
		error = fcml_fn_dasm_disassemble( &context, &dis_result );

	}

	if( error == FCML_CEH_GEC_NO_ERROR ) {

		fcml_bool is_67 = FCML_FALSE;
		fcml_bool is_66 = FCML_FALSE;

		if( !(t_flags & FCML_TSF_ASM_ONLY) ) {

			if( (t_flags & FCML_TSF_PRINT_ONLY) ) {
				printf("Instruction: %s\n", mnemonic);
			}

			if( t_flags & FCML_TSF_SHOULD_FAIL ) {
				printf("Should fail: %s\n", mnemonic);
				success = FCML_FALSE;
				fcml_fn_dasm_disassemble_result_free( dis_result );
				return success;
			}

			// Looking for 0x67 prefix.
			int i;
			for( i = 0; i < FCML_DASM_PREFIXES_COUNT; i++ ) {
				if( dis_result->instruction_details.prefixes.prefixes[i].prefix == 0x67 ) {
					is_67 = FCML_TRUE;
				}
				if( dis_result->instruction_details.prefixes.prefixes[i].prefix == 0x66 ) {
                    is_66 = FCML_TRUE;
                }
			}

			// Print.
			char buffer[512] = {0};

			fcml_st_memory_stream stream;
			stream.base_address = buffer;
			stream.offset = 0;
			stream.size = sizeof( buffer );

			error = fcml_fn_rend_render_instruction( &dialect, &stream, dis_result, FCML_REND_FLAG_HEX_IMM | FCML_REND_FLAG_COND_SHOW_CARRY | FCML_REND_FLAG_HEX_DISPLACEMENT | rend_flags);
			if( error ) {
				printf("Disassemblation failed, with error code: %d\n", error );
				if( !(t_flags & FCML_TSF_PRINT_ONLY) ) {
					success = FCML_FALSE;
				}
				fcml_fn_dasm_disassemble_result_free( dis_result );
				return success;
			}

			if( strcmp( buffer, mnemonic ) != 0 ) {
				printf("Disassemblation failed, should be: %s (Was: %s)\n", mnemonic, buffer);
				if( !(t_flags & FCML_TSF_PRINT_ONLY) ) {
					success = FCML_FALSE;
				}
				fcml_fn_dasm_disassemble_result_free( dis_result );
				return success;
			} else {
				if( !(t_flags & FCML_TSF_PRINT_ONLY) ) {
					CU_ASSERT(FCML_TRUE);
				}
			}

		}

		// Parsing.

		fcml_st_parser_result *result;
		fcml_ceh_error error = fcml_fn_parse_instruction( &dialect, mnemonic, &result );
		if( error ) {
			printf("Can not parse: %s\n", mnemonic );
			if( !(t_flags & FCML_TSF_PRINT_ONLY) ) {
				success = FCML_FALSE;
			}
			fcml_fn_parser_result_free( result );
			fcml_fn_dasm_disassemble_result_free( dis_result );
			return success;
		}

		fcml_uint16_t opt_flags = 0;

		// Assembling.
		fcml_st_asm_assembler_context context;
		context.assembler = assembler;
		context.address_size_attribute = 0;
		context.operand_size_attribute = 0;
		context.addr_form = addr_form;

		if( is_67 ) {
			if( addr_form == FCML_AF_64_BIT ) {
				opt_flags = FCML_OPTF_ASA_32;
			} else {
				opt_flags = FCML_OPTF_ASA_16;
			}
		}
		if( is_66 ) {
            opt_flags |= FCML_OPTF_OSA_16;
        }

		context.configuration.choose_sib_encoding = FCML_FALSE;
		context.configuration.choose_abs_encoding = !(t_flags & FCML_TSF_ENABLE_RIP);
		context.configuration.force_3byte_vex = FCML_FALSE;
		context.configuration.chooser = NULL;
		context.configuration.optimizer = NULL;
		context.configuration.optimizer_flags = opt_flags;
		context.configuration.force_unnecessary_rex_prefix = FCML_FALSE;
		context.configuration.force_three_byte_VEX = FCML_FALSE;

		fcml_ifn_ts_set_ip( &(context.ip), addr_form );

		fcml_st_asm_assembler_result *asm_result = NULL;
		error = fcml_fn_asm_assemble( &context, result->instruction, &asm_result );
		if( error ) {
		    if( !t_flags & FCML_TSF_SHOULD_FAIL ) {
		        printf("Can not assemble: %s\n", mnemonic );
		    }
			if( !(t_flags & FCML_TSF_PRINT_ONLY) ) {
				success = t_flags & FCML_TSF_SHOULD_FAIL;
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
                    fcml_st_asm_assembled_instruction *assembled_instruction = (fcml_st_asm_assembled_instruction *)element->item;
                    assembled_code_len[assembled_code_index] = assembled_instruction->code_length;
                    assembled_code[assembled_code_index++] = assembled_instruction->code;
                    element = element->next;
                }

                if( !(t_flags & FCML_TSF_PRINT_ONLY) ) {
                    if( !(t_flags & FCML_TSF_MULTI_ASM_RESULTS) && inst->size != 1 ) {
                        found = FCML_FALSE;
                        break;
                    }
                }

                element = inst->head;
                while( element ) {
                    fcml_st_asm_assembled_instruction *assembled_instruction = (fcml_st_asm_assembled_instruction *)element->item;
                    fcml_bool differ = FCML_FALSE;
                    if( !(t_flags & FCML_TSF_PRINT_ONLY) ) {
                        int i;
                        if( (t_flags & FCML_TSF_MULTI_ASM_RESULTS) ) {
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

                    if( (t_flags & FCML_TSF_PRINT_ONLY) || ( differ && !looking_for_instruction ) ) {
#ifdef FCML_DEBUG
                        printf( "Index: %d\nOriginal code : ", assembled_instruction->__def_index );
#else
                        printf( "Original code : " );
#endif
                        int i;
                        for( i = 0; i < size; i++ ) {
                            printf( FCML_PRI_INT8_HEX, code[i] );
                        }

                        printf( "\nAssembled code: " );
                        for( i = 0; i < assembled_instruction->code_length; i++ ) {
                            printf( FCML_PRI_INT8_HEX, assembled_instruction->code[i] );
                        }

                        printf("\n");
                    }
                    element = element->next;
                }

                if( found ) {
                    break;
                }

                looking_for_instruction = FCML_FALSE;

                if( (t_flags & FCML_TSF_PRINT_ONLY) ) {
                    break;
                }
            }

            if( !found ) {
                if( !(t_flags & FCML_TSF_PRINT_ONLY) && !(t_flags & FCML_TSF_SHOULD_FAIL) ) {
                    printf("Can not assemble: %s\n", mnemonic);
                }
                if( !(t_flags & FCML_TSF_PRINT_ONLY) ) {
                    success = t_flags & FCML_TSF_SHOULD_FAIL;
                }
            }

            // Prints test code.
            if( !(t_flags & FCML_TSF_SHOULD_FAIL) && assembled_code_index >= 1 && ( (t_flags & FCML_TSF_PRINT_ONLY) || !found ) ) {

               // Mnemonic.
               fcml_string macro;
			   switch( addr_form ) {
			   case FCML_AF_16_BIT:
				   macro = ( assembled_code_index > 1 ) ? "FCML_I16_M" : "FCML_I16";
			   break;
			   case FCML_AF_32_BIT:
				   macro = ( assembled_code_index > 1 ) ? "FCML_I32_M" : "FCML_I32";
			   break;
			   case FCML_AF_64_BIT:
				   macro = ( assembled_code_index > 1 ) ? "FCML_I64_M" : "FCML_I64";
			   break;
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
                           printf( "0x"FCML_PRI_INT8_HEX, assembled_code[i][j] );
                       }
                       printf( " )" );
                   }
               } else if ( assembled_code_index == 1  ) {
                   int i;
                   for( i = 0; i < assembled_code_len[0]; i++ ) {
                       if( i > 0 ) {
                           printf(", ");
                       }
                       printf( "0x"FCML_PRI_INT8_HEX, assembled_code[0][i] );
                   }
               }

               printf(" );\n");
            }

		}

		fcml_fn_asm_assembler_result_free( asm_result );

		fcml_fn_parser_result_free( result );


	} else {

		success = t_flags & FCML_TSF_SHOULD_FAIL;

	}

	fcml_fn_dasm_disassemble_result_free( dis_result );

	return success;
}

fcml_bool fcml_fn_ts_instruction_test_diss( fcml_uint8_t *code, int size, fcml_en_addr_form addr_form, fcml_string mnemonic, fcml_uint32_t t_flags, fcml_uint32_t ren_flags ) {

	fcml_bool success = FCML_TRUE;

	fcml_st_dasm_disassembler_result *dis_result = NULL;

	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

	fcml_st_dasm_disassembler_context context;
	context.configuration.use_short_form_mnemonics = ( t_flags & FCML_TSF_SHORT ) ? FCML_TRUE : FCML_FALSE;
	context.configuration.extend_displacement_to_asa = FCML_TRUE;
	context.configuration.conditional_group = FCML_DASM_CONDITIONAL_GROUP_1;
	context.configuration.choose_carry_conditional_mnemonic = FCML_TRUE;
	context.disassembler = disassembler;
	context.addr_form = addr_form;
	context.address_size_attribute = 0;
	context.operand_size_attribute = 0;
	context.code_address = code;
	context.code_size = size;

	fcml_ifn_ts_set_ip( &(context.ip), addr_form );

	// Disassemble.
	error = fcml_fn_dasm_disassemble( &context, &dis_result );

	if( !error ) {

		// Print.
		char buffer[512] = {0};

		fcml_st_memory_stream stream;
		stream.base_address = buffer;
		stream.offset = 0;
		stream.size = sizeof( buffer );

		error = fcml_fn_rend_render_instruction( &dialect, &stream, dis_result, FCML_REND_FLAG_HEX_IMM | FCML_REND_FLAG_COND_SHOW_CARRY | FCML_REND_FLAG_HEX_DISPLACEMENT | ren_flags );

		if( t_flags & FCML_TSF_PRINT_ONLY ) {
			printf("Disassembled instruction: %s", buffer);
		} else {
			if( error || strcmp( buffer, mnemonic ) != 0 ) {
				if( !(t_flags & FCML_TSF_SHOULD_FAIL) ) {
					printf("Disassemblation failed, should be: %s (Was: %s)\n", mnemonic, buffer);
				}
				return (t_flags & FCML_TSF_SHOULD_FAIL) ? FCML_TRUE : FCML_FALSE;
			} else {
				if( dis_result->instruction_details.instruction_size != size ) {
					printf("Instruction size: %d Disassembled code size: %d (%s)\n", (fcml_uint32_t)dis_result->instruction_details.instruction_size, size, mnemonic);
					success = FCML_FALSE;
				} else {
					if( !(t_flags & FCML_TSF_PRINT_ONLY) ) {
						if( (t_flags & FCML_TSF_SHOULD_FAIL) ) {
							printf("Should fail: %s\n", mnemonic);
							success = FCML_FALSE;
						} else {
							CU_ASSERT(FCML_TRUE);
						}
					}
				}
			}
		}
	} else {
		if( t_flags & FCML_TSF_SHOULD_FAIL ) {
			if( !(t_flags & FCML_TSF_PRINT_ONLY) ) {
				CU_ASSERT(FCML_TRUE);
			}
			success = FCML_TRUE;
		} else {
			success = FCML_FALSE;
		}
	}

	fcml_fn_dasm_disassemble_result_free( dis_result );

	return success;
}

