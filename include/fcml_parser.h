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
#include "fcml_symbols.h"

#ifdef __cplusplus
extern "C" {
#endif

#define FCML_PARSER_MAX_INSTRUCTION_LEN	1024

typedef struct fcml_st_parser_config {
	/* Set to true in order to ignore all undefined symbols.
	 * In such case every unknown symbol is treated as 0.
	 */
	fcml_bool ignore_undefined_symbols;
	/* Set to true in order to allow overriding existing labels.
	 * If set to false, parser returns "Symbol already exists"
	 * in such cases.
	 */
	fcml_bool override_labels;
} fcml_st_parser_config;

/* EIP/RIP is always represent as 64 bit value in parsing environment. */
typedef fcml_int64_t fcml_parser_ip;

typedef struct fcml_st_parser_context {
	/* Dialect to be used by parser. */
	fcml_st_dialect *dialect;
	/* Pserser configuration. */
	fcml_st_parser_config config;
	/* RIP/EIP used as a value for newly declared symbols.
	 * This value is never changed by parser.
	 */
	fcml_parser_ip ip;
	/* Symbol table. It holds symbols added by user as
	 * well as symbols allocated by parsers (labels). It is
	 * very important to free this container on your own
	 * because even if is not allocated by the user, it can be
	 * set by the parser when the first symbol definition is found.
	 * So the most safe way to manage it, is to always use
	 * "fcml_fn_symbol_table_free" function as soon as context
	 * if going to be freed.
	 */
	fcml_st_symbol_table symbol_table;
} fcml_st_parser_context;

typedef struct fcml_st_parser_result {
	fcml_st_ceh_error_container errors;
	/* Defined symbol if there is any. Remember, this symbol is also stored in the context
	 * and it is context that is responsible for de-allocating it.
	 */
	fcml_st_symbol *symbol;
	fcml_st_instruction *instruction;
} fcml_st_parser_result;

LIB_EXPORT fcml_ceh_error LIB_CALL fcml_fn_parse( fcml_st_parser_context *context, fcml_string instruction, fcml_st_parser_result *result );
LIB_EXPORT void LIB_CALL fcml_fn_parser_result_prepare( fcml_st_parser_result *result );
LIB_EXPORT void LIB_CALL fcml_fn_parser_result_free( fcml_st_parser_result *result );

#ifdef __cplusplus
}
#endif

#endif /* FCML_PARSER_H_ */
