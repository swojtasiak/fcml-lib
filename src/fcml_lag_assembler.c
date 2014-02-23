/*
 * fcml_lag_assembler.c
 *
 *  Created on: Feb 22, 2014
 *      Author: tas
 */

#include <fcml_lag_assembler.h>
#include <fcml_parser.h>
#include <fcml_parser_int.h>
#include "fcml_env.h"
#include "fcml_coll.h"
#include "fcml_apc_ast.h"
#include "fcml_errors.h"
#include "fcml_messages.h"

/*
 *         jmp second
start:  jmp finish
        rb  124
second: jmp 249-(finish-start)
finish: ret
 */

typedef struct fcml_ist_lag_instruction_code {
	/* Warnings from last pass. */
	fcml_st_ceh_error_container warnings;
	/* Instruction machine code.*/
	fcml_uint8_t *code;
	/* Instruction code length in bytes.*/
	fcml_usize code_length;
} fcml_ist_lag_instruction_code;

typedef struct fcml_ist_lag_instruction {
	fcml_parser_ip ip;
	/* Next instruction. */
	struct fcml_ist_lag_instruction *next;
	/* If instruction has symbols, we have its AST just to reassemble it when needed. */
	fcml_st_parser_ast ast;
	/* List of symbols used by instruction. Every symbol is represented by its name (list of fcml_string). */
	fcml_st_coll_list *used_symbols;
	/* Number of undefined symbols when instruction was assembled last time. */
	fcml_int undefined_symbols;
	/* Instruction choosen in the last pass. */
	fcml_ist_lag_instruction_code instruction;
	/* Number of instruction forms provided by assembler.
	 * Information might be useful in the late stages.
	 */
	fcml_uint8_t number_of_instructions;
	/* Line number where instruction is defined. */
	fcml_int line;
	/* Generated instruction can not be shorter than */
	fcml_int size_guard;
} fcml_ist_lag_instruction;

typedef struct fcml_ist_log_asseblation_context {
	fcml_ist_lag_instruction *first_instruction;
	fcml_ist_lag_instruction *last_instruction;
} fcml_ist_log_asseblation_context;

fcml_ceh_error fcml_ifn_lag_copy_instruction_code( fcml_ist_lag_instruction_code *instruction, fcml_st_assembled_instruction *chosen_instruction ) {
	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
	if( instruction->code ) {
		fcml_fn_env_memory_free( instruction->code );
	}
	instruction->code = fcml_fn_env_memory_alloc( chosen_instruction->code_length );
	if( !instruction->code ) {
		return FCML_CEH_GEC_OUT_OF_MEMORY;
	}
	fcml_fn_env_memory_copy( instruction->code, chosen_instruction->code, chosen_instruction->code_length );
	instruction->code_length = chosen_instruction->code_length;
	/* Free all warnings from previous pass. */
	fcml_fn_ceh_free_errors_only( &(instruction->warnings) );
	/* Copy warnings from current instruction. */
	instruction->warnings = chosen_instruction->errors;
	/* Detach warnings from assembled instruction. */
	chosen_instruction->errors.errors = NULL;
	chosen_instruction->errors.last_error = NULL;
	return error;
}

fcml_int fcml_ifn_lag_count_instructions( fcml_st_assembled_instruction *instruction ) {
	fcml_int counter = 0;
	while( instruction ) {
		counter++;
		instruction = instruction->next;
	}
	return counter;
}

void LIB_CALL fcml_fn_lag_assembler_result_prepare( fcml_st_lag_assembler_result *result ) {
	if( result ) {
		fcml_fn_env_memory_clear( result, sizeof( fcml_st_lag_assembler_result ) );
	}
}

fcml_ceh_error fcml_ifn_choose_instruction( fcml_ist_lag_instruction *lag_instruction, fcml_st_assembled_instruction *instructions, fcml_st_assembled_instruction *choosen_instruction ) {

	fcml_int guard = lag_instruction->size_guard;

	if( !lag_instruction->undefined_symbols && guard > 0 ) {
		fcml_st_assembled_instruction *chosen_instruction = NULL;
		/* Choose the longes form. */
		fcml_st_assembled_instruction *current = instructions;
		while( current ) {
			if( !chosen_instruction && guard <= current->code_length ) {
				chosen_instruction = current;
			} else if( current->code_length > chosen_instruction->code_length && guard <= current->code_length ) {
				chosen_instruction = current;
			}
			current = current->next;
		}
	}

	if( !lag_instruction->undefined_symbols ) {
		if( choosen_instruction->code_length > lag_instruction->instruction.code_length ) {
			lag_instruction->size_guard = choosen_instruction->code_length;
		}
	}

	return fcml_ifn_lag_copy_instruction_code( &(lag_instruction->instruction), choosen_instruction );

}

fcml_ceh_error LIB_CALL fcml_fn_lag_assemble( fcml_st_lag_assembler_context *context, const fcml_string *source_code, fcml_st_lag_assembler_result *result ) {

	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

	fcml_ist_log_asseblation_context processing_ctx = {0};

	/* Allocate symbol table, if it hasn't been defined yet. */
	if( !context->symbol_table ) {
		context->symbol_table = fcml_fn_symbol_table_alloc();
		if( !context->symbol_table ) {
			return FCML_CEH_GEC_OUT_OF_MEMORY;
		}
	}

	fcml_st_assembler_context assembler_context = {0};
	assembler_context.assembler = context->assembler;
	assembler_context.configuration = context->configuration;
	/* Default optimizer ans chosoer has to be used here. */
	assembler_context.configuration.optimizer = NULL;
	assembler_context.configuration.chooser = NULL;
	assembler_context.entry_point = context->entry_point;

	fcml_st_parser_context parser_context = {0};
	parser_context.config.ignore_undefined_symbols = FCML_TRUE;
	parser_context.config.override_labels = FCML_FALSE;
	parser_context.ip = ( assembler_context.entry_point.addr_form == FCML_AF_64_BIT ) ? assembler_context.entry_point.ip.rip : assembler_context.entry_point.ip.eip;
	parser_context.dialect = context->dialect;

	fcml_st_parser_result parser_result;
	fcml_fn_parser_result_prepare( &parser_result );

	fcml_st_assembler_result assembler_result;
	fcml_fn_assembler_result_prepare( &assembler_result );

	// Stage 1.
	// - Parses instructions one by one. Every parsed instruction is then converted to CIF and assembled.
	//   Assembler should return all allowed forms of assembled instruction. If all symbols were known, the
	//   shortest instruction for is chooen; otherwise the longest one.

	fcml_bool invoke_next_phase = FCML_FALSE;

	fcml_int line = 0;

	fcml_string instruction;

	while( ( instruction = source_code[line] ) ) {

		/* Check if line is blank. */

		fcml_int length = fcml_fn_env_str_strlen( instruction );
		if( length > FCML_PARSER_MAX_INSTRUCTION_LEN ) {
			error = FCML_CEH_GEC_INVALID_INPUT;
			break;
		}

		/* Empty lines should be ignored. */
		if( !fcml_fn_env_str_strblank( instruction ) ) {

			fcml_st_parser_ast ast = {0};

			/* Parse instruction to AST. */
			error = fcml_fn_parse_to_ast( &parser_context, instruction, &ast );
			if( error ) {
				break;
			}

			if( ast.symbol ) {

				if( fcml_fn_symbol_get( context->symbol_table, ast.symbol->symbol ) ) {
					/* Symbol already defined. */
					fcml_char msg_buffer[FCML_MESSAGE_MAX];
					fcml_string msg_pattern = fcml_fn_msg_get_message( FCML_MC_SEGMENT_SYMBOL_ALREADY_DEFINED );
					fcml_fn_env_str_snprintf( msg_buffer, sizeof( msg_buffer ), msg_pattern, ast.symbol->symbol );
					fcml_fn_ceh_add_error( &(result->errors), (const fcml_string)msg_buffer, FCML_CEH_MEC_ERROR_SYMBOL_ALREADY_DEFINED, FCML_EN_CEH_EL_ERROR );
					error = FCML_CEH_GEC_INVALID_INPUT;
					break;
				}

				if( !error ) {
					error = fcml_fn_symbol_add( context->symbol_table, ast.symbol );
					if( error ) {
						break;
					}
				}

			}

			fcml_ist_lag_instruction *lag_instruction = fcml_fn_env_memory_alloc_clear( sizeof( fcml_ist_lag_instruction ) );
			if( !lag_instruction ) {
				error = FCML_CEH_GEC_OUT_OF_MEMORY;
				break;
			}

			fcml_int code_length = 0;

			/* Check if there is any instruction to assemble. */
			if( ast.tree ) {

				/* Convert AST to common instruction format. */

				fcml_st_cif_converter_context cif_context = {0};
				cif_context.ignore_undefined_symbols = FCML_TRUE;
				cif_context.symbol_table = context->symbol_table;

				fcml_st_instruction *cif_instruction;

				error = fcml_fn_ast_to_cif_converter( &cif_context, ast.tree, &cif_instruction );
				if( error ) {
					break;
				}

				/* Assemble instruction. */

				if( assembler_context.entry_point.addr_form == FCML_AF_64_BIT ) {
					assembler_context.entry_point.ip.rip = (fcml_uint64_t)parser_context.ip;
				} else {
					assembler_context.entry_point.ip.eip = (fcml_uint32_t)parser_context.ip;
				}

				error = fcml_fn_assemble( &assembler_context, cif_instruction, &assembler_result );
				if( error ) {
					break;
				}

				/* Choose the best instruction. */

				fcml_st_assembled_instruction *chosen_instruction = NULL;
				if( cif_context.ignored_symbols > 0 ) {
					/* Choose the longes form. */
					fcml_st_assembled_instruction *current = assembler_result.instructions;
					while( current ) {
						if( !chosen_instruction ) {
							chosen_instruction = current;
						} else if( current->code_length > chosen_instruction->code_length ) {
							chosen_instruction = current;
						}
						current = current->next;
					}
					/* At last one forward symbol, so next phase is needed. */
					invoke_next_phase = FCML_TRUE;
				} else {
					/* Default chooser chooses the shortest for for us. */
					chosen_instruction = assembler_result.chosen_instruction;
				}

				code_length += chosen_instruction->code_length;

				lag_instruction->undefined_symbols = cif_context.ignored_symbols;
				lag_instruction->number_of_instructions = fcml_ifn_lag_count_instructions( assembler_result.instructions );
				fcml_ifn_lag_copy_instruction_code( &(lag_instruction->instruction), chosen_instruction );

				/* Instruction uses symbols, so extract it just in order to make
				 * them visible later in second stage, because we have to reassemble
				 * instructions which use modified symbols.
				 */
				if( cif_context.evaluated_symbols > 0 ) {
					error = fcml_fn_ast_extract_used_symbols( ast.tree, &(lag_instruction->used_symbols) );
					if( error ) {
						break;
					}
				}

				lag_instruction->ip = parser_context.ip;
			}

			lag_instruction->line = line;
			lag_instruction->ast = ast;

			if( !processing_ctx.first_instruction ) {
				processing_ctx.first_instruction = lag_instruction;
				processing_ctx.last_instruction = lag_instruction;
			} else {
				processing_ctx.last_instruction->next = lag_instruction;
				processing_ctx.last_instruction = lag_instruction;
			}

			/* Increment instruction pointer. */

			parser_context.ip += code_length;
		}

		line++;
	}

	if( error ) {

		result->error_line = line;

		/* Free environment. */

		return error;
	}

	// Stage 2.

	while( invoke_next_phase ) {

		invoke_next_phase = FCML_FALSE;

		fcml_ist_lag_instruction *lag_instruction = processing_ctx.first_instruction;

		fcml_parser_ip ip_delta = 0;

		while( lag_instruction ) {

			lag_instruction->ip += ip_delta;

			fcml_st_symbol *def_symbol = lag_instruction->ast.symbol;

			/* Update defined symbol if there is such need. */

			if( def_symbol && ip_delta != 0 ) {

				def_symbol->value += ip_delta;

				invoke_next_phase = FCML_TRUE;

			}

			/* Check if there are any symbols used by instructions. */
			if( lag_instruction->used_symbols ) {

				fcml_st_instruction *cif_instruction;

				/* Regenerate instruction with symbols. */

				fcml_st_cif_converter_context cif_context = {0};
				cif_context.ignore_undefined_symbols = FCML_TRUE;
				cif_context.symbol_table = context->symbol_table;

				error = fcml_fn_ast_to_cif_converter( &cif_context, lag_instruction->ast.tree, &cif_instruction );
				if( error ) {
					break;
				}

				/* Assemble instruction. */

				if( assembler_context.entry_point.addr_form == FCML_AF_64_BIT ) {
					assembler_context.entry_point.ip.rip = (fcml_uint64_t)parser_context.ip;
				} else {
					assembler_context.entry_point.ip.eip = (fcml_uint32_t)parser_context.ip;
				}

				error = fcml_fn_assemble( &assembler_context, cif_instruction, &assembler_result );
				if( error ) {
					break;
				}

				fcml_int code_length = lag_instruction->instruction.code_length;

				/* Choose the best instruction form. */

				error = fcml_ifn_choose_instruction( lag_instruction, assembler_result.instructions, assembler_result.chosen_instruction );
				if( error ) {
					break;
				}

				fcml_int code_diff = ( lag_instruction->instruction.code_length - code_length );

				ip_delta += code_diff;

			}

			lag_instruction = lag_instruction->next;
		}

	}

	return error;

}

void LIB_CALL fcml_fn_lag_assembler_result_free( fcml_st_lag_assembler_result *result ) {

}



