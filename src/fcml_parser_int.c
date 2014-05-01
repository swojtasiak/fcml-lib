/*
 * fcml_parser_int.c
 *
 *  Created on: Feb 20, 2014
 *      Author: tas
 */

#include <fcml_symbols.h>
#include "fcml_parser_int.h"
#include "fcml_messages.h"
#include "fcml_env_int.h"
#include "fcml_dialect_int.h"

fcml_ceh_error fcml_fn_parser_add_symbol_to_symbol_table( fcml_st_ceh_error_container *errors, fcml_st_symbol_table symbol_table, fcml_st_symbol *symbol, fcml_bool allow_override ) {

	fcml_ceh_error error = FCML_COLL_ERROR_NO_ERROR;

	if( !allow_override ) {
		if( fcml_fn_symbol_get( symbol_table, symbol->symbol ) ) {
			/* Symbol already defined. */
			fcml_char msg_buffer[FCML_MESSAGE_MAX];
			fcml_string msg_pattern = fcml_fn_msg_get_message( FCML_MC_SEGMENT_SYMBOL_ALREADY_DEFINED );
			fcml_fn_env_str_snprintf( msg_buffer, sizeof( msg_buffer ), msg_pattern, symbol->symbol );
			fcml_fn_ceh_add_error( errors, (const fcml_string)msg_buffer, FCML_CEH_MEC_ERROR_SYMBOL_ALREADY_DEFINED, FCML_EN_CEH_EL_ERROR );
			error = FCML_CEH_GEC_INVALID_INPUT;
		}
	}

	if( !error ) {
		error = fcml_fn_symbol_add( symbol_table, symbol );
	}

	return error;
}

fcml_ceh_error fcml_fn_parse_to_cif( fcml_st_parser_context *context, fcml_string mnemonic, fcml_st_parser_result *result ) {

	if( !result || !mnemonic || !context ) {
		return FCML_CEH_GEC_INVALID_INPUT;
	}

	fcml_st_parser_ast ast = {0};

	/* Free previous parser results. */
	fcml_fn_parser_result_free( result );

	fcml_ceh_error error = fcml_fn_parse_to_ast( context, mnemonic, &ast );

	/* Copy errors from parser.*/
	result->errors = ast.errors;

	if( error ) {

		/* Just in case. */
		fcml_fn_symbol_free( ast.symbol );
		fcml_fn_ast_free_node( ast.tree );
		return error;
	}

	/* Symbol */
	if( ast.symbol ) {

		/* If there is no symbol table yet, allocate it. */
		if( !context->symbol_table ) {
			context->symbol_table = fcml_fn_symbol_table_alloc();
			if( !context->symbol_table ) {
				fcml_fn_symbol_free( ast.symbol );
				fcml_fn_ast_free_node( ast.tree );
				return FCML_CEH_GEC_OUT_OF_MEMORY;
			}
		}

		error = fcml_fn_parser_add_symbol_to_symbol_table( &(result->errors), context->symbol_table, ast.symbol, context->config.override_labels );
		if( error ) {
			fcml_fn_symbol_free( ast.symbol );
			fcml_fn_ast_free_node( ast.tree );
			return error;
		}

		result->symbol = ast.symbol;

	}

	/* Instruction. */
	if( !error && ast.tree ) {

		fcml_st_cif_converter_context cif_ctx;
		cif_ctx.errors = &(result->errors);
		cif_ctx.symbol_table = context->symbol_table;
		cif_ctx.ignore_undefined_symbols = context->config.ignore_undefined_symbols;

		error = fcml_fn_ast_to_cif_converter( &cif_ctx, ast.tree, &(result->instruction) );
		if( error ) {

			/* Free instruction, because it might haven't been fully parsed.*/
			if( result->instruction ) {
				fcml_fn_ast_free_converted_cif( result->instruction );
				result->instruction = NULL;
			}

			/* Defined symbol should also be freed, because we can not leave
			 * such symbols to be defined in the main symbols table.
			 */
			if( result->symbol ) {
				fcml_fn_symbol_remove( context->symbol_table, result->symbol->symbol );
				result->symbol = NULL;
			}
		}

	}

	fcml_fn_ast_free_node( ast.tree );

	return error;
}

fcml_ceh_error fcml_fn_parse_to_ast( fcml_st_parser_context *context, fcml_string mnemonic, fcml_st_parser_ast *ast ) {
	fcml_st_dialect_context_int *dialect = (fcml_st_dialect_context_int*)context->dialect;
	return dialect->instruction_parser( context->ip, mnemonic, ast );
}

void fcml_fn_parser_free_ast( fcml_st_parser_ast *ast ) {

	if( ast ) {
		/* Free symbol. */
		if( ast->symbol ) {
			fcml_fn_env_str_strfree( ast->symbol->symbol );
			fcml_fn_env_memory_free( ast->symbol );
			ast->symbol = NULL;
		}
		/* Free errors and warnings. */
		fcml_fn_ceh_free_errors_only( &(ast->errors) );
		/* Free AST tree. */
		if( ast->tree ) {
			fcml_fn_ast_free_node( ast->tree );
		}
		ast->tree = NULL;
	}

}

