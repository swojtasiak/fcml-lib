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

/** @file fcml_choosers.h
 *
 * API for instruction choosers.
 *
 * @copyright Copyright (C) 2010-2020 Slawomir Wojtasiak. All rights reserved.
 * This project is released under the GNU Lesser General Public License.
 */

#ifndef FCML_CHOOSER_H_
#define FCML_CHOOSER_H_

#include "fcml_lib_export.h"

#include "fcml_types.h"
#include "fcml_common.h"

#ifdef __cplusplus
extern "C" {
#endif

/** Returns next instructions from the iterator.
 * Instruction chooser uses this function to get next instruction from the chain.
 * @param instruction Current instruction.
 */
typedef fcml_ptr (*fcml_fnp_chooser_next)(fcml_ptr instruction);

/** Gets instruction code from current abstract instruction pointer.
 * Gets instruction pointer and fills given instruction code
 * holder with the binary code of the instruction.
 * @param instruction Instruction pointer.
 * @param instruction_code Holder for the instruction code.
 */
typedef void (*fcml_fnp_chooser_extract)(fcml_ptr instruction,
        fcml_st_instruction_code *instruction_code);

/** Instruction chooser context used to communicate with environment. */
typedef struct fcml_st_chooser_context {
    /** First instruction in the chain. */
    fcml_ptr instruction;
    /** Gets next instruction code from iterator. */
    fcml_fnp_chooser_next next;
    /** Extracts instruction code from abstract instruction pointer.*/
    fcml_fnp_chooser_extract extract;
} fcml_st_chooser_context;

/** Instruction chooser function pointer declaration.
 * @param chooser_context Instruction chooser context.
 */
typedef fcml_ptr (LIB_CALL *fcml_fnp_asm_instruction_chooser)(
        fcml_st_chooser_context *chooser_context);

/** Default instruction chooser which chooses the shortest instruction available.
 * @param chooser_context Instruction chooser context.
 */
fcml_ptr LIB_EXPORT LIB_CALL fcml_fn_asm_default_instruction_chooser(
        fcml_st_chooser_context *chooser_context);

/** NULL chooser which do not chose anything.
 * @param chooser_context Instruction chooser context.
 */
fcml_ptr LIB_EXPORT LIB_CALL fcml_fn_asm_no_instruction_chooser(
        fcml_st_chooser_context *chooser_context);

#ifdef __cplusplus
}
#endif

#endif /* FCML_CHOOSER_H_ */
