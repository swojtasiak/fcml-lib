/*
 * FCML - Free Code Manipulation Library.
 * Copyright (C) 2010-2020 Slawomir Wojtasiak
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

/** @file fcml_parser.h
 * Structures and functions declarations related to FCML parsers
 *
 * @copyright Copyright (C) 2010-2020 Slawomir Wojtasiak. All rights reserved.
 * This project is released under the GNU Lesser General Public License.
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

/** Maximal number of character for parsed instruction. */
#define FCML_PARSER_MAX_INSTRUCTION_LEN	1024

/** Parser configuration. */
typedef struct fcml_st_parser_config {
    /** Set to true in order to ignore all undefined symbols.
     * In such a case every unknown symbol is treated as 0.
     */
    fcml_bool ignore_undefined_symbols;
    /** Disables symbols support.
     * If set to true every defined label will cause an error.
     */
    fcml_bool disable_symbols_declaration;
    /** Set to true in order to allow overriding existing labels.
     * If set to false parser returns "Symbol already exists" error when
     *  symbol already exists.
     */
    fcml_bool override_labels;
    /** By default parser ignores all symbol declarations
     * if there is no symbol table provided in the parser
     * context. By setting this value to true you can force
     * the parser to allocate new symbol table when needed.
     * Remember that you are then responsible for freeing it,
     * so this functionality can be a bit dangerous because
     * you have to check the existence of the symbol table
     * every time it should be deallocated.
     */
    fcml_bool alloc_symbol_table_if_needed;
    // TODO: Support has to be implemented yet.
    /** Enables textual error messages. */
    fcml_bool enable_error_messages;
} fcml_st_parser_config;

/** Parser runtime context. */
typedef struct fcml_st_parser_context {
    /** Dialect to be used by parser. Defines supported instructions syntax. */
    fcml_st_dialect *dialect;
    /** Parser configuration. */
    fcml_st_parser_config configuration;
    /** Instruction pointer. RIP/EIP register value used as a value for
     * newly declared symbols.
     * This value is never changed by the parser.
     */
    fcml_ip ip;
    /** Symbol table. It holds symbols added by the user as
     * well as symbols allocated by the parsers (labels). It is
     * very important to free this container on your own
     * because even if it is not allocated by the user it can be
     * set by the parser when the first symbol definition is found.
     * So the most safe way to manage it is to always use
     * "fcml_fn_symbol_table_free" function as soon as context
     * if going to be freed.
     */
    fcml_st_symbol_table symbol_table;
} fcml_st_parser_context;

/** Reusable result holder */
typedef struct fcml_st_parser_result {
    /** Parsing errors and warnings going here. */
    fcml_st_ceh_error_container errors;
    /** Defined symbol if there is any.
     * Remember that this symbol is also stored in the context's symbol table.
     * It is the symbol table that is the owner and that is responsible
     * for freeing it.
     */
    fcml_st_symbol *symbol;
    /** Parsed instruction as generic instruction model. */
    fcml_st_instruction *instruction;
} fcml_st_parser_result;

/**
 * Parses given instruction into the generic instruction model.
 * Parses the textual representation of the instruction using dialect and
 * configuration provided by the parser context. Parsed instruction is returned in the
 * reusable result holder. Result holder has to be allocated by the
 * user and appropriately prepared using fcml_fn_parser_result_prepare()
 * function. As long as the instruction context and the result holder
 * are not shared across multiple function calls parsing process is
 * thread safe.
 *
 * Remember that textual representation of the instruction has to be written
 * using syntax supported by the dialect parser is going to use.
 *
 * @param context Parser runtime context.
 * @param instruction textual representation of the instruction to be parsed.
 * @param result Reusable result holder.
 * @return Error code or FCML_CEH_GEC_NO_ERROR.
 */
LIB_EXPORT fcml_ceh_error LIB_CALL fcml_fn_parse(
        fcml_st_parser_context *context, const fcml_string instruction,
        fcml_st_parser_result *result);

/**
 * Prepares reusable result holder for parser.
 * Every instance of fcml_st_parser_result structure is reusable from the
 * parser's point of view, so it has to be prepared in the right way in order
 * to allow parser to reuse it correctly. It is up to the library user to
 * allocate space for the holder itself. This function is only responsible
 * for cleaning the structure correctly and preparing it for the first parsing
 * process. Notice that parser has to clean the result holder at the beginning
 * so you can not pass an uninitialized memory block because it can even cause
 * a crash due to illegal memory access.
 *
 * @param result Result holder instance to be prepared.
 */
LIB_EXPORT void LIB_CALL fcml_fn_parser_result_prepare(
        fcml_st_parser_result *result);

/**
 * Cleans result holder.
 * Frees all memory blocks allocated by the parser and held inside the result
 * holder (Instructions, errors etc.). Notice that result holder itself is
 * not freed and can be even safety reused after call to this function. In fact
 * this function is also called internally by the parser in order to clean
 * result holder before  reusing it.
 * @param result Result holder to clean.
 */
LIB_EXPORT void LIB_CALL fcml_fn_parser_result_free(
        fcml_st_parser_result *result);

#ifdef __cplusplus
}
#endif

#endif /* FCML_PARSER_H_ */
