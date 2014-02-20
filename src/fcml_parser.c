/*
 * fcml_parser_common.c
 *
 *  Created on: Nov 14, 2013
 *      Author: tas
 */

#include "fcml_parser.h"

#include <fcml_errors.h>
#include <fcml_common.h>
#include "fcml_dialect_int.h"
#include "fcml_apc_ast.h"
#include "fcml_env.h"
#include "fcml_trace.h"
#include "fcml_parser_int.h"

fcml_ceh_error LIB_CALL fcml_fn_parse( fcml_st_parser_context *ctx, fcml_string instruction, fcml_st_parser_result *result_out ) {
	fcml_st_parser_context_int *context = (fcml_st_parser_context_int*)ctx;
	fcml_st_dialect_context_int *dialect_context_int = (fcml_st_dialect_context_int*)context->context.dialect;
	if( dialect_context_int->instruction_parser ) {
		fcml_fnp_parse_instruction parser = (fcml_fnp_parse_instruction)dialect_context_int->instruction_parser;
		return parser( ctx, instruction, result_out );
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

void fcml_itf_eff_parser_free_symbol( fcml_ptr key, fcml_ptr value, fcml_ptr args ) {
	/* Key do not have to be freed, because it the same symbol as in symbol descriptor. */
	if( value ) {
		/* Free symbol structure. */
		fcml_st_symbol *symbol = (fcml_st_symbol*)value;
		fcml_fn_env_str_strfree( symbol->symbol );
		fcml_fn_env_memory_free( value );
	}
}

fcml_st_parser_context* LIB_CALL fcml_fn_parser_allocate_context( fcml_st_dialect *dialect ) {
	fcml_st_parser_context_int *context = (fcml_st_parser_context_int*)fcml_fn_env_memory_alloc_clear( sizeof( fcml_st_parser_context_int ) );
	if( !context ) {
		/* Out of memory. */
		return NULL;
	}
	context->context.dialect = dialect;
	/* Allocate space for symbols. */
	fcml_int error = FCML_COLL_ERROR_NO_ERROR;
	fcml_st_coll_map_descriptor desc = fcml_coll_map_descriptor_string;
	desc.entry_free_function = &fcml_itf_eff_parser_free_symbol;
	context->symbols = fcml_fn_coll_map_alloc( &desc, 0, &error );
	if( error ) {
		fcml_fn_env_memory_free( context );
		/* Out of memory. */
		return NULL;
	}
	return (fcml_st_parser_context*)context;
}

void LIB_CALL fcml_fn_parser_free_context( fcml_st_parser_context *ctx ) {
	if( ctx ) {
		fcml_st_parser_context_int *context = (fcml_st_parser_context_int*)ctx;
		/* Free all symbols. */
		fcml_fn_coll_map_free( context->symbols );
		/* Free context inself. */
		fcml_fn_env_memory_free( context );
	}
}

fcml_ceh_error LIB_CALL fcml_fn_parser_add_symbol( fcml_st_parser_context *ctx, fcml_string symbol, fcml_int64_t value ) {
	fcml_st_parser_context_int *context = (fcml_st_parser_context_int*)ctx;
	fcml_st_symbol *sym = (fcml_st_symbol*)fcml_fn_env_memory_alloc( sizeof( fcml_st_symbol* ) );
	if( !sym ) {
		return FCML_CEH_GEC_OUT_OF_MEMORY;
	}
	sym->symbol = fcml_fn_env_str_strdup( symbol );
	if( !sym->symbol ) {
		fcml_fn_env_memory_free( sym );
		return FCML_CEH_GEC_OUT_OF_MEMORY;
	}
	sym->value = value;
	fcml_int error = FCML_COLL_ERROR_NO_ERROR;
	fcml_fn_coll_map_put( context->symbols, sym->symbol, sym, &error );
	if( error ) {
		fcml_fn_env_str_strfree( sym->symbol );
		fcml_fn_env_memory_free( sym );
		return FCML_CEH_GEC_OUT_OF_MEMORY;
	}
	return FCML_CEH_GEC_NO_ERROR;
}

void LIB_CALL fcml_fn_parser_remove_symbol( fcml_st_parser_context *ctx, fcml_string symbol ) {
	fcml_st_parser_context_int *context = (fcml_st_parser_context_int*)ctx;
	if( context && symbol ) {
		fcml_fn_coll_map_remove( context->symbols, symbol );
	}
}

fcml_st_symbol* LIB_CALL fcml_fn_parser_get_symbol( fcml_st_parser_context *ctx, fcml_string symbol ) {
	fcml_st_parser_context_int *context = (fcml_st_parser_context_int*)ctx;
	if( context && symbol ) {
		return (fcml_st_symbol*)fcml_fn_coll_map_get(context->symbols, symbol );
	}
	return NULL;
}

void LIB_CALL fcml_fn_parser_remove_all_symbols( fcml_st_parser_context *ctx ) {
	fcml_st_parser_context_int *context = (fcml_st_parser_context_int*)ctx;
	if( context ) {
		fcml_fn_coll_map_free( context->symbols );
	}
}

