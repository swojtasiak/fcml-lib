/*
 * fcml_intel_asm_parser.c
 *
 *  Created on: 20-03-2013
 *      Author: tAs
 */

#include <string.h>
#include "fcml_ceh.h"
#include "fcml_env.h"
#include "fcml_common.h"
#include <fcml_errors.h>
#include "fcml_parser_data.h"
#include "fcml_intel_parser_def.h"
#include "fcml_intel_lexer.h"
#include "fcml_intel_parser.h"
#include "fcml_parser.h"
#include "fcml_parser_int.h"

void intel_error( struct fcml_st_parser_data *pd, const char *error ) {
	/* Stores parser error into standard container.*/
	fcml_fn_ceh_add_error( &(pd->errors), (const fcml_string)error, FCML_CEH_MEC_ERROR_INVALID_SYNTAX, FCML_EN_CEH_EL_ERROR );
}

fcml_ceh_error fcml_intel_parse( fcml_st_parser_context *ctx, fcml_string asm_code, fcml_st_parser_result *result ) {

	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

	fcml_st_parser_context_int *context = (fcml_st_parser_context_int*)ctx;

	/* Free previous parser results. */
	fcml_fn_parser_result_free( result );

	fcml_st_parser_data parser = {0};
	parser.ip = context->context.ip;

	/* Set up scanner. */
	if ( intel_lex_init_extra( &parser, &(parser.scannerInfo) ) ) {
		return FCML_CEH_GEC_OUT_OF_MEMORY;
	}

	/*Instruction size is limited to prevent from parser's stack and buffer overflow.*/
	if( strlen( asm_code ) > FCML_PARSER_MAX_INSTRUCTION_LEN ) {
		intel_lex_destroy( parser.scannerInfo );
		return FCML_CEH_GEC_INVALID_INPUT;
	}

	intel__scan_string( asm_code, parser.scannerInfo );

	int yyresult = intel_parse(&parser);

	intel_lex_destroy( parser.scannerInfo );

	/* Copy errors from parser.*/
	result->errors = parser.errors;

	if( yyresult ) {
		switch( yyresult ) {
		case 1: /*Syntax error.*/
			error = FCML_CEH_GEC_INVALID_INPUT;
			break;
		case 2: /*Out of memory*/
			error = FCML_CEH_GEC_OUT_OF_MEMORY;
			break;
		}
		return error;
	}

	/* Symbol */
	if( parser.symbol ) {
		/* This method frees symbol in case of any error. */
		error = fcml_fn_parser_add_symbol_to_symbol_table( &(result->errors), context->symbols, parser.symbol, context->context.config.override_labels );
		if( !error ) {
			result->symbol = parser.symbol;
		}
	}

	/* Instruction. */
	if( !error && parser.tree ) {
		error = fcml_fn_ast_to_cif_converter( parser.tree, &(result->errors), &(result->instruction) );
		if( error ) {
			/* Free instruction, because it might haven't been fully parsed.*/
			fcml_fn_ast_free_converted_cif( result->instruction );
			result->instruction = NULL;
		}
	}

	fcml_fn_ast_free_node( parser.tree );

	return error;
}
