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

#ifndef FCML_ASM_ENCODING_H_
#define FCML_ASM_ENCODING_H_

#include "fcml_assembler.h"
#include "fcml_ceh.h"
#include "fcml_coll.h"
#include "fcml_common.h"
#include "fcml_dialect_int.h"
#include "fcml_types.h"

/**
 * Holds the result of instruction encoding.
 * The result consists of all assembled instructions and the one chosen
 * as the one expected by the caller.
 */
typedef struct fcml_st_asm_encoder_result {
    /** Potential encoding errors end up here. */
    fcml_st_ceh_error_container errors;
    /** All possible assembled instructions goes here. */
    fcml_st_assembled_instruction *instructions;
    /** The instruction that most likely is the expected one goes here. */
    fcml_st_assembled_instruction *chosen_instruction;
    /** Number of instructions assembled by the encoder. */
    fcml_usize number_of_instructions;
} fcml_st_asm_encoder_result;

struct fcml_st_instruction_addr_modes;

/** Instruction encoders have to be compatible with this pointer. */
typedef fcml_ceh_error (*fcml_fp_instruction_encoder)(
        fcml_st_assembler_context*, fcml_st_dialect_context_int*,
        struct fcml_st_instruction_addr_modes*, fcml_st_instruction*,
        fcml_st_asm_encoder_result*);

/** Supported addressing modes of one particular instruction.
 * Most of the instructions support more than one addressing mode.
 * Every addressing mode is described by a dedicated model which is
 * then interpreted by the encoder during assembling process.
 */
typedef struct fcml_st_instruction_addr_modes {
    /* All addressing modes for given mnemonic are available in this list. */
    fcml_st_coll_list *addr_modes_encodings;
    /* An instruction mnemonic shared by all the addressing modes. */
    const fcml_string mnemonic;
    /* Predefined instruction encoder responsible for encoding the instruction. */
    fcml_fp_instruction_encoder encoder;
} fcml_st_instruction_addr_modes;

/** Prepares static instruction address modes map. */
fcml_ceh_error fcml_fn_init_instructions_addr_modes(
        fcml_st_dialect_context_int *context,
        fcml_coll_map *instructions_map);

/** Gets addressing modes for given mnemonic. */
fcml_ceh_error fcml_fn_get_instruction_addr_modes(
        fcml_coll_map instructions_map,
        fcml_string mnemonic,
        fcml_st_instruction_addr_modes **);

/** Frees all the addressing modes. */
void fcml_fn_free_instructions_addr_modes(fcml_coll_map instructions_map);

#endif /* FCML_ASM_ENCODING_H_ */
