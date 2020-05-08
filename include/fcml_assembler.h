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

/** @file fcml_assembler.h
 * Structures and functions declarations related to one-line FCML assembler.
 * @copyright Copyright (C) 2010-2020 Slawomir Wojtasiak. All rights reserved.
 * This project is released under the GNU Lesser General Public License.
 */

#ifndef FCML_ASSEMBLER_H_
#define FCML_ASSEMBLER_H_

#include "fcml_lib_export.h"

#include "fcml_types.h"
#include "fcml_errors.h"
#include "fcml_common.h"
#include "fcml_dialect.h"
#include "fcml_optimizers.h"
#include "fcml_choosers.h"

#ifdef __cplusplus
extern "C" {
#endif

/** Abstract assembler representation. */
typedef struct fcml_st_assembler fcml_st_assembler;

/**
 * Assembler runtime configuration.
 */
typedef struct fcml_st_assembler_conf {
    /** Set to true in order to force assembler to increment IP address by
     * length of the assembled instruction. */
    fcml_bool increment_ip;
    /** True if optional error and warning messages should be collected
     *  during processing. */
    fcml_bool enable_error_messages;
    /** If there are SIB and "ModR/M only" encodings available, choose
     * the SIB based one. */
    fcml_bool choose_sib_encoding;
    /** If memory address can be encoded as relative or absolute value choose
     * the absolute addressing. It works in 64 bit mode only. */
    fcml_bool choose_abs_encoding;
    /** Sometimes REX prefix is useless so it is just omitted in the final
     * machine code. By setting this flag to true you can force this prefix
to be added anyway. */
    fcml_bool force_rex_prefix;
    /** Every 2 byte VEX/XOP prefix can be encoded using three byte form.
     * Setting this flag to true forces it. */
    fcml_bool force_three_byte_VEX;
    /** Optimizer implementation that should be used by assembler. Setting it
     *  to NULL causes assembler to use default one. */
    fcml_fnp_asm_optimizer optimizer;
    /** This field is passed to the chosen optimizer. It can be used to
     *  configure its behavior. */
    fcml_uint16_t optimizer_flags;
    /** instruction chooser implementation that should be used by assembler
     * to choose most appropriate instruction encoding. Setting this value to
     * NULL cause assembler to use default instruction chooser. */
    fcml_fnp_asm_instruction_chooser chooser;
} fcml_st_assembler_conf;

/**
 * Encoded instruction.
 * Every instruction might be encoded to more than one binary form.
 * This chain holds all forms assembler was able to assemble instruction to.
 */
typedef struct fcml_st_assembled_instruction {
    /** Next assembled instruction in the chain. */
    struct fcml_st_assembled_instruction *next;
    /** Warning messages related to assembled instruction.*/
    fcml_st_ceh_error_container warnings;
    /** Instruction machine code.*/
    fcml_uint8_t *code;
    /** Instruction code length in bytes.*/
    fcml_usize code_length;
#ifdef FCML_DEBUG
    fcml_uint8_t __def_index;
#endif
} fcml_st_assembled_instruction;

/** Assembler result. */
typedef struct fcml_st_assembler_result {
    /** Error and warning messages from assembler.*/
    fcml_st_ceh_error_container errors;
    /** Chain of assembled instructions. */
    fcml_st_assembled_instruction *instructions;
    /** Instruction chosen by used instruction chooser; otherwise NULL.*/
    fcml_st_assembled_instruction *chosen_instruction;
    /** Number of encoded instruction forms. */
    fcml_usize number_of_instructions;
} fcml_st_assembler_result;

/** Assembler runtime context. */
typedef struct fcml_st_assembler_context {
    /** Assembler instance that should be used to assemble instructions. */
    fcml_st_assembler *assembler;
    /** Assembler behavior can be configured here.*/
    fcml_st_assembler_conf configuration;
    /** Instruction entry point configuration. */
    fcml_st_entry_point entry_point;
} fcml_st_assembler_context;

/**
 * Initializes assembler for given dialect.
 * Initializes assembler instance for given dialect (Intel, AT&T). Assembler
 * initialized in such a way is dialect dependent and supports GIM with the
 * syntax supported by it. Every assembler instance has to be freed using
 * fcml_fn_assembler_free() function as soon as it is not needed anymore.
 *
 * @param dialect Dialect instance.
 * @param[out] assembler Initialized assembler instance.
 * @return Error code or FCML_CEH_GEC_NO_ERROR.
 * @see fcml_fn_assembler_free
 */
LIB_EXPORT fcml_ceh_error LIB_CALL fcml_fn_assembler_init(
        const fcml_st_dialect *dialect, fcml_st_assembler **assembler);

/**
 * Assembles one instruction encoded in the generic instruction model.
 * Instruction is proceeded using configuration and assembler provided
 * in given fcml_st_assembler_context instance. Assembled code as well
 * as potential errors or warnings are accessible via provided reusable
 * result holder instance. Result holder has to be allocated by the
 * user and appropriately prepared using fcml_fn_assembler_result_prepare()
 * function. As long as the instruction context and the result holder
 * are not shared across multiple function calls assembling process is
 * thread safe.
 *
 * @param context Assembler context (Assembler, Entry Point, Configuration).
 * @param instruction Instruction encoded as generic instruction model
 * (Dialect dependent).
 * @param result Result holder (Remember to prepare it appropriately).
 * @return Error code or FCML_CEH_GEC_NO_ERROR.
 * @see fcml_fn_assembler_result_prepare fcml_fn_assembler_init
 */
LIB_EXPORT fcml_ceh_error LIB_CALL fcml_fn_assemble(
        fcml_st_assembler_context *context,
        const fcml_st_instruction *instruction,
        fcml_st_assembler_result *result);

/**
 * Prepares reusable result holder for assembler.
 * Every instance of fcml_st_assembler_result structure is reusable from
 * the assembler's point of view, so it has to be prepared in the right way
 * in order to allow assembler to reuse it correctly. It is up to the library
 * user to allocate space for the holder itself. This function is only
 * responsible for cleaning the structure correctly and preparing it for the
 * first assembling process. Notice that assembler has to clean the result
 * holder at the beginning so you can not pass an uninitialized memory block
 * because it can even cause a crash due to illegal memory access.
 *
 * @param result Result holder instance to be prepared.
 */
LIB_EXPORT void LIB_CALL fcml_fn_assembler_result_prepare(
        fcml_st_assembler_result *result);

/**
 * Cleans result holder.
 * Frees all memory blocks allocated by the assembler and held inside the
 * result holder (Instructions, errors etc.). Notice that result holder itself
 * is not freed and can be even safety reused after call to this function. In
 * fact this function is also called internally by the assembler in order to
 * clean result holder before reusing it.
 * @param result Result holder to clean.
 */
LIB_EXPORT void LIB_CALL fcml_fn_assembler_result_free(
        fcml_st_assembler_result *result);

/**
 * Frees assembled instruction.
 * Take into account that it does not free whole chain recursively but only
 * the one instruction you have provided.
 * @param instruction Instruction to be freed.
 */
LIB_EXPORT void LIB_CALL fcml_fn_assembler_instruction_free(
        fcml_st_assembled_instruction *instruction);

/**
 * Detaches given instruction from the instructions chain.
 * Removes given assembled instruction from the provided chain in order
 * to prevent premature freeing of memory while assembler cleans result holder
 * reusing it. Detached instructions are not automatically deallocated by
 * fcml_fn_assemble() or fcml_fn_assembler_result_free() functions, so
 * it is up to you to free it using fcml_fn_assembler_instruction_free()
 * function when it is not needed anymore. Function may be useful
 * when you need to store assembled instructions across multiple calls
 * to the assembler if you reuse the same result holder. If there is only one
 * instruction in the chain its pointer will be set to NULL after detaching it.
 * @param chain Pointer to the instructions chain pointer.
 * @param instruction Instruction to be detached from the chain.
 *
 */
LIB_EXPORT void LIB_CALL fcml_fn_assembler_instruction_detach(
        fcml_st_assembled_instruction **chain,
        fcml_st_assembled_instruction *instruction);

/**
 * Frees assembler instance.
 * Every assembler instance manages some resources internally and as such it has
 * to be deallocated as soon as it is not needed anymore.
 * @param assembler Assembler to be freed.
 */
LIB_EXPORT void LIB_CALL fcml_fn_assembler_free(fcml_st_assembler *assembler);

#ifdef __cplusplus
}
#endif

#endif /* FCML_ASSEMBLER_H_ */
