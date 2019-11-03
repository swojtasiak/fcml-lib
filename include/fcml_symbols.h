/*
 * FCML - Free Code Manipulation Library.
 * Copyright (C) 2010-2019 Slawomir Wojtasiak
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

/** @file fcml_symbols.h
 * API for symbols handling. Currently used only by parsers.
 *
 * @copyright Copyright (C) 2010-2015 Slawomir Wojtasiak. All rights reserved.
 * This project is released under the GNU Lesser General Public License.
 */

#ifndef FCML_SYMBOLS_H_
#define FCML_SYMBOLS_H_

#include "fcml_lib_export.h"
#include "fcml_common.h"
#include "fcml_errors.h"

/** Type for symbol tables. */
typedef fcml_ptr fcml_st_symbol_table;

/*********************************
 * Symbols.
 *********************************/

/** Represents one named symbol with associated value. */
typedef struct fcml_st_symbol {
    /* The symbol name. */
    fcml_string symbol;
    /* The symbol value. */
    fcml_int64_t value;
} fcml_st_symbol;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Allocates new symbol on FCML library heap.
 * This function should be always used when symbols
 * are added using fcml_fn_symbol_add() function.
 * @return Allocated symbol or NULL if allocation failed.
 */
LIB_EXPORT fcml_st_symbol* LIB_CALL fcml_fn_symbol_alloc(
        const fcml_string symbol, fcml_int64_t value);

/**
 * Frees symbol allocated by FCML library.
 * @param symbol The symbol to be freed.
 */
LIB_EXPORT void LIB_CALL fcml_fn_symbol_free(fcml_st_symbol *symbol);

/**
 * Allocates new symbol table.
 * @return The allocated symbol table or NULL if something failed.
 */
LIB_EXPORT fcml_st_symbol_table LIB_CALL fcml_fn_symbol_table_alloc();

/**
 * Adds new symbol to the symbol table.
 * This function is more secure than fcml_fn_symbol_add() because it
 * always allocates new symbol instance internally, so you do not have
 * to pay attention not to pass the symbol allocated on the different heap
 * to the symbol table. After the symbol has been properly added you can
 * safely free the name because this function duplicates the name
 * to the symbol needs. Of course the symbol as well as the duplicated name
 * are freed by fcml_fn_symbol_table_free() function. You can also
 * free it on your own if the symbol is not managed by symbol table
 * using fcml_fn_symbol_free() function.
 * @param symbol_table The symbol table.
 * @param symbol The symbol name.
 * @param value The symbol value.
 * @see fcml_fn_symbol_table_free
 */
LIB_EXPORT fcml_ceh_error LIB_CALL fcml_fn_symbol_add_raw(
        fcml_st_symbol_table symbol_table, const fcml_string symbol,
        fcml_int64_t value);

/**
 * Adds existing symbol to the symbol table.
 * Remember that only symbols allocated on FCML heap should be
 * added there. Of course in some cases heaps are shared so
 * it will works without any problems but even if they are you
 * <b>should</b> use fcml_fn_symbol_table_alloc() function to allocate
 * every symbol.
 *
 * @param symbol_table The symbol table where new symbol should be placed.
 * @param symbol The symbol to be added.
 * @return Error code or FCML_CEH_GEC_NO_ERROR.
 */
LIB_EXPORT fcml_ceh_error LIB_CALL fcml_fn_symbol_add(
        fcml_st_symbol_table symbol_table, const fcml_st_symbol *symbol);

/**
 * Removes the symbol from the symbol table.
 * The removed symbol is automatically freed.
 * @param symbol_table The symbol table.
 * @param symbol The name of the symbol to remove.
 */
LIB_EXPORT void LIB_CALL fcml_fn_symbol_remove(
        fcml_st_symbol_table symbol_table, const fcml_string symbol);

/**
 * Gets the symbol with the given name from the symbol table.
 * @param symbol_table The symbol table.
 * @param symbol The name of the symbol to get from the table.
 * @return The pointer to the symbol or NULL if there is no such symbol
 *  in the symbol table.
 */
LIB_EXPORT fcml_st_symbol* LIB_CALL fcml_fn_symbol_get(
        fcml_st_symbol_table symbol_table, const fcml_string symbol);

/**
 * Removes all symbols from the symbol table.
 * Removes and frees all symbols from the given symbol table
 * but does not free the symbol table itself.
 * @param symbol_table The symbol table to be cleared.
 */
LIB_EXPORT void LIB_CALL fcml_fn_symbol_remove_all(
        fcml_st_symbol_table symbol_table);

/**
 * Frees a symbol table.
 * Frees all symbols as well as the symbol table itself.
 * @param symbol_table A symbol table to be freed.
 */
LIB_EXPORT void LIB_CALL fcml_fn_symbol_table_free(
        fcml_st_symbol_table symbol_table);

#ifdef __cplusplus
}
#endif

#endif /* FCML_SYMBOLS_H_ */
