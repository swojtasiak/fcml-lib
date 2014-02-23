/*
 * fcml_parser_common.c
 *
 *  Created on: Nov 14, 2013
 *      Author: tas
 */

#include "fcml_parser.h"

#include <fcml_errors.h>
#include <fcml_common.h>
#include <fcml_symbols.h>
#include "fcml_dialect_int.h"
#include "fcml_apc_ast.h"
#include "fcml_env.h"
#include "fcml_trace.h"
#include "fcml_parser_int.h"

fcml_ceh_error LIB_CALL fcml_fn_parse( fcml_st_parser_context *context, fcml_string instruction, fcml_st_parser_result *result_out ) {
	fcml_st_dialect_context_int *dialect_context_int = (fcml_st_dialect_context_int*)context->dialect;
	if( dialect_context_int->instruction_parser ) {
		return fcml_fn_parse_to_cif( context, instruction, result_out );
	} else {
		/* Dialect not initialized correctly.*/
		FCML_TRACE_MSG("Parsing not supported by current dialect.");
		return FCML_CEH_GEC_FEATURE_NOT_SUPPORTED;
	}
}

void LIB_CALL fcml_fn_parser_result_free( fcml_st_parser_result *result ) {
	if( result ) {
		/* Frees parsed instruction, potential errors and warnings and result structure itself.*/
		if( result->instruction ) {
			fcml_fn_ast_free_converted_cif( result->instruction );
			result->instruction = NULL;
		}
		/* Symbol can not be free, because it is managed by symbols
		 * table, but of course we have to zero it.
		 */
		result->symbol = NULL;
		fcml_fn_ceh_free_errors_only( &(result->errors) );
	}
}

void LIB_CALL fcml_fn_parser_result_prepare( fcml_st_parser_result *result ) {
	if( result ) {
		result->errors.errors = NULL;
		result->errors.last_error = NULL;
		result->instruction = NULL;
	}
}
