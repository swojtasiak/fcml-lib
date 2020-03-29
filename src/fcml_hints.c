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

#include "fcml_hints.h"

fcml_st_hts_calculated_hints fcml_fn_hts_ihc_far_pointer(
        const fcml_st_def_addr_mode_desc *addr_mode,
        fcml_st_def_decoded_addr_mode *decoded_addr_mode) {
    fcml_st_hts_calculated_hints hints;
    hints.instruction_hints = FCML_HINT_FAR_POINTER;
    hints.operand_hints = 0;
    return hints;
}

fcml_st_hts_calculated_hints fcml_fn_hts_ihc_modrm_hints(
        const fcml_st_def_addr_mode_desc *addr_mode,
        fcml_st_def_decoded_addr_mode *decoded_addr_mode) {
    fcml_st_hts_calculated_hints hints = { 0 };
    fcml_st_def_tma_rm *rm_args =
            (fcml_st_def_tma_rm*) decoded_addr_mode->addr_mode_args;
    if (rm_args->flags & FCML_RMF_M) {
        hints.operand_hints = 0;
        /* VSIB addressing mode is available for multimedia instructions only. */
        if (rm_args->reg_type == FCML_REG_SIMD || rm_args->is_vsib) {
            /* SIMD media instruction. */
            hints.operand_hints |= FCML_OP_HINT_MULTIMEDIA_INSTRUCTION;
        }
        if ( FCML_GET_OS( rm_args->encoded_memory_operand_size ) == FCML_EOS_FP) {
            /* Far pointer. */
            hints.instruction_hints |= FCML_HINT_FAR_POINTER;
        } else if ( FCML_GET_OS(
                rm_args->encoded_memory_operand_size) != FCML_EOS_FPI) {
            /* If not far, then near :) */
            hints.instruction_hints |= FCML_HINT_NEAR_POINTER;
        }
        if (rm_args->flags & FCML_RMF_I) {
            hints.instruction_hints |= FCML_HINT_INDIRECT_POINTER;
        }
        /* Every ModR/M encoded operand supports SIB hint. */
        hints.operand_hints |= FCML_OP_HINT_SIB_ENCODING;
    } else {
        hints.operand_hints = 0;
    }
    return hints;
}

fcml_st_hts_calculated_hints fcml_fn_hts_ihc_immediate_dis_relative(
        const fcml_st_def_addr_mode_desc *addr_mode,
        fcml_st_def_decoded_addr_mode *decoded_addr_mode) {
    fcml_st_hts_calculated_hints hints;
    hints.instruction_hints = 0;
    hints.operand_hints = FCML_OP_HINT_DISPLACEMENT_RELATIVE_ADDRESS;
    return hints;
}

fcml_st_hts_calculated_hints fcml_fn_hts_ihc_pseudo_opcode(
        const fcml_st_def_addr_mode_desc *addr_mode,
        fcml_st_def_decoded_addr_mode *decoded_addr_mode) {
    fcml_st_hts_calculated_hints hints;
    hints.instruction_hints = 0;
    hints.operand_hints = FCML_OP_HINT_PSEUDO_OPCODE;
    return hints;
}
