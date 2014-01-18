/*
 * fcml_parser_common.c
 *
 *  Created on: Nov 14, 2013
 *      Author: tas
 */

#include "fcml_parser.h"

#include "fcml_dialect_int.h"
#include "fcml_apc_ast.h"
#include "fcml_env.h"

fcml_ceh_error fcml_fn_parse( fcml_st_dialect *dialect, fcml_string instruction, fcml_st_parser_result **result_out ) {
	fcml_st_dialect_context_int *dialect_context_int = (fcml_st_dialect_context_int*)dialect;
	if( dialect_context_int->instruction_parser ) {
		fcml_fnp_parse_instruction parser = (fcml_fnp_parse_instruction)dialect_context_int->instruction_parser;
		return parser( dialect, instruction, result_out );
	} else {
		// Dialect not initialized correctly.
		return FCML_CEH_GEC_ILLEGAL_STATE_EXCEPTION;
	}
}

void fcml_fn_parser_result_free( fcml_st_parser_result *result ) {
	if( result ) {
		// Frees parsed instruction, potential errors and warnings and result structure itself.
		if( result->instruction ) {
			fcml_fn_ast_free_converted_cif( result->instruction );
		}
		fcml_fn_ceh_free_errors_only( &(result->errors) );
		fcml_fn_env_memory_free( result );
	}
}
