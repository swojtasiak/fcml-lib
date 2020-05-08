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

/** @file fcml_lag_assembler.h
 * Experimental multiline load-and-go assembler implementation.
 * @copyright Copyright (C) 2010-2020 Slawomir Wojtasiak. All rights reserved.
 * This project is released under the GNU Lesser General Public License.
 */

#ifndef FCML_LAG_ASSEMBLER_H_
#define FCML_LAG_ASSEMBLER_H_

#include "fcml_symbols.h"
#include "fcml_assembler.h"

#ifdef __cplusplus
extern "C" {
#endif

/** Result holder for load-and-go assembler. */
typedef struct fcml_st_lag_assembler_result {
    /** Error and warning messages from one-line assembler. */
    fcml_st_ceh_error_container errors;
    /** Number of line where assembler failed. */
    fcml_int error_line;
    /** Chain of assembled instructions.*/
    fcml_st_assembled_instruction *instructions;
} fcml_st_lag_assembler_result;

/** Load-and-go assembler runtime context. */
typedef struct fcml_st_lag_assembler_context {
    /** Assembler instance that should be used to assemble instructions. */
    fcml_st_assembler *assembler;
    /** Assembler behavior can be configured here.*/
    fcml_st_assembler_conf configuration;
    /** Instruction entry point configuration. */
    fcml_st_entry_point entry_point;
    /** Symbols table. */
    fcml_st_symbol_table symbol_table;
} fcml_st_lag_assembler_context;

/**
 * Multipass load-and-go assembler.
 * Assembles all instructions given in the NULL terminated source_code
 * array of strings. Every instruction has to be represented as one string
 * in the source array. Like every multipass assembler implementation it
 * passes through the source code multiple times in order to generate optimal
 * code. Assembler also supports symbols that can be provided using symbol
 * table available in the context. Context should be initialized the same way
 * as in case of one line assembler. The only difference here is the symbol
 * table itself which can be initialized using fcml_fn_symbol_table_alloc()
 * function. Symbols can be also declared directly in the source code and
 * accessed through the same symbols table when processing is done (Only if
 * you provide valid symbol table through the context). Reusable result holder
 * has to be prepared using fcml_fn_lag_assembler_result_prepare() function.
 * As long as the context and the result holder are not shared across multiple
 * calls function is thread safe.
 *
 * @param context Assembler context.
 * @param source_code NULL terminated array of the instructions.
 * @param result Reusable result holder.
 * @return Error code or FCML_CEH_GEC_NO_ERROR.
 * @warning This is an experimental implementation and it still needs
 * some testing.
 * @see fcml_fn_lag_assembler_result_prepare
 * @see fcml_fn_symbol_table_alloc
 */
LIB_EXPORT fcml_ceh_error LIB_CALL fcml_fn_lag_assemble(
        fcml_st_lag_assembler_context *context, const fcml_string *source_code,
        fcml_st_lag_assembler_result *result);

/**
 * Prepares reusable result holder for assembler.
 * Every instance of fcml_st_lag_assembler_result structure is reusable from
 * the assembler's point of view, so it has to be prepared in the right way in
 * order to allow assembler to reuse it correctly. It is up to the library user
 * to allocate space for the holder itself. This function is only responsible
 * for cleaning the structure correctly and preparing it for first assembling
 * process. Notice that assembler has to clean the result holder at the
 * beginning so you can not pass an uninitialized memory block because it can
 * even cause a crash due to illegal memory access.
 *
 * @param result Result holder instance to be prepared.
 */
LIB_EXPORT void LIB_CALL fcml_fn_lag_assembler_result_prepare(
        fcml_st_lag_assembler_result *result);

/**
 * Cleans result holder.
 * Frees all memory blocks allocated by the assembler and held inside the
 * result holder (Instructions, errors etc.). Notice that result holder itself
 * is not freed and can be even safety reused after call to this function. In
 * fact this function is also called internally by assembler in order to clean
 * result holder before
 * reusing it.
 * @param result Result holder to clean.
 */
LIB_EXPORT void LIB_CALL fcml_fn_lag_assembler_result_free(
        fcml_st_lag_assembler_result *result);

#ifdef __cplusplus
}
#endif

#endif /* FCML_LAG_ASSEMBLER_H_ */
