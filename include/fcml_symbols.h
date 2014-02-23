/*
 * fcml_symbols.h
 *
 *  Created on: Feb 22, 2014
 *      Author: tas
 */

#ifndef FCML_SYMBOLS_H_
#define FCML_SYMBOLS_H_

#include "fcml_lib_export.h"
#include "fcml_common.h"
#include "fcml_errors.h"

typedef fcml_ptr fcml_st_symbol_table;

/*********************************
 * Symbols.
 *********************************/

/* Represents one symbol which defines named value used by parsers. */
typedef struct fcml_st_symbol {
	/* Symbol name. */
	fcml_string symbol;
	/* Symbol value. */
	fcml_int64_t value;
} fcml_st_symbol;

LIB_EXPORT void LIB_CALL fcml_fn_symbol_free( fcml_st_symbol *symbol );
LIB_EXPORT fcml_st_symbol_table LIB_CALL fcml_fn_symbol_table_alloc();
LIB_EXPORT fcml_ceh_error LIB_CALL fcml_fn_symbol_add_raw( fcml_st_symbol_table symbol_table, fcml_string symbol, fcml_int64_t value );
LIB_EXPORT fcml_ceh_error LIB_CALL fcml_fn_symbol_add( fcml_st_symbol_table symbol_table, fcml_st_symbol *symbol );
LIB_EXPORT void LIB_CALL fcml_fn_symbol_remove( fcml_st_symbol_table symbol_table, fcml_string symbol );
LIB_EXPORT fcml_st_symbol* LIB_CALL fcml_fn_symbol_get( fcml_st_symbol_table symbol_table, fcml_string symbol );
LIB_EXPORT void LIB_CALL fcml_fn_symbol_remove_all( fcml_st_symbol_table symbol_table );
LIB_EXPORT void LIB_CALL fcml_fn_symbol_table_free( fcml_st_symbol_table symbol_table );

#endif /* FCML_SYMBOLS_H_ */
