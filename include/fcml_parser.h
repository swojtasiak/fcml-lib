/*
 * fcml_parser.h
 *
 *  Created on: Nov 14, 2013
 *      Author: tas
 */

#ifndef FCML_PARSER_H_
#define FCML_PARSER_H_

#include "fcml_lib_export.h"

#include "fcml_types.h"
#include "fcml_errors.h"
#include "fcml_common.h"
#include "fcml_dialect.h"

#ifdef __cplusplus
extern "C" {
#endif

#define FCML_PARSER_MAX_INSTRUCTION_LEN	1024

typedef struct fcml_st_parser_config {
	/* Set to true in order to ignore all undefined symbols.
	 * In such case every unknown symbol is treated as 0.
	 */
	fcml_bool ignore_unknown_symbols;
} fcml_st_parser_config;

typedef struct fcml_st_parser_context {
	/* Pserser configuration. */
	fcml_st_parser_config config;
	/* Dialect to be used by parser. */
	fcml_st_dialect *dialect;
	/* RIP/EIP used as a value for newly declared symbols. */
	const fcml_parser_ip ip;
} fcml_st_parser_context;

typedef struct fcml_st_parser_result {
	fcml_st_ceh_error_container errors;
	fcml_st_instruction *instruction;
} fcml_st_parser_result;

LIB_EXPORT fcml_st_parser_context* LIB_CALL fcml_fn_parser_allocate_context( fcml_st_dialect *dialect );
LIB_EXPORT fcml_ceh_error LIB_CALL fcml_fn_parse( fcml_st_parser_context *context, fcml_string instruction, fcml_st_parser_result *result );
LIB_EXPORT void LIB_CALL fcml_fn_parser_result_prepare( fcml_st_parser_result *result );
LIB_EXPORT void LIB_CALL fcml_fn_parser_result_free( fcml_st_parser_result *result );
LIB_EXPORT fcml_ceh_error LIB_CALL fcml_fn_parser_add_symbol( fcml_st_parser_context *context, fcml_string symbol, fcml_int64_t value );
LIB_EXPORT void LIB_CALL fcml_fn_parser_remove_symbol( fcml_st_parser_context *context, fcml_string symbol );
LIB_EXPORT fcml_st_symbol* LIB_CALL fcml_fn_parser_get_symbol( fcml_st_parser_context *context, fcml_string symbol );
LIB_EXPORT void LIB_CALL fcml_fn_parser_remove_all_symbols( fcml_st_parser_context *context );
LIB_EXPORT void LIB_CALL fcml_fn_parser_free_context( fcml_st_parser_context *context );

#ifdef __cplusplus
}
#endif

#endif /* FCML_PARSER_H_ */
