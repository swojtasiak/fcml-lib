/*
 * FCML - Free Code Manipulation Library.
 * Copyright (C) 2010-2014 Slawomir Wojtasiak
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

#include "fcml_def.h"
#include "fcml_env_int.h"

typedef fcml_ptr (*fcml_fnp_def_addr_mode_args_decoder)( fcml_uint32_t encoded_addr_mode );

fcml_ptr fcml_fnp_def_addr_mode_args_decoder_is( fcml_uint32_t encoded_addr_mode ) {
    fcml_sf_def_tma_is *is_args = (fcml_sf_def_tma_is*) fcml_fn_env_memory_alloc( sizeof(fcml_sf_def_tma_is) );
    if (is_args) {
        is_args->flags = ( encoded_addr_mode & 0x000000FF );
    }
    return is_args;
}

fcml_ptr fcml_fnp_def_addr_mode_args_decoder_imm( fcml_uint32_t encoded_addr_mode ) {
    fcml_sf_def_tma_imm *imm_args = (fcml_sf_def_tma_imm*) fcml_fn_env_memory_alloc( sizeof(fcml_sf_def_tma_imm) );
    if (imm_args) {
        imm_args->encoded_size = ( encoded_addr_mode & 0x0000FF00 ) >> 8;
        imm_args->encoded_ex_size = encoded_addr_mode & 0x000000FF;
        imm_args->is_64bit_imm_allowed = ( encoded_addr_mode & 0x00FF0000 ) >> 16;
    }
    return imm_args;
}

fcml_ptr fcml_fnp_def_addr_mode_args_decoder_explicit_reg( fcml_uint32_t encoded_addr_mode ) {
    fcml_sf_def_tma_explicit_reg *explicit_reg_args = (fcml_sf_def_tma_explicit_reg*) fcml_fn_env_memory_alloc( sizeof(fcml_sf_def_tma_explicit_reg) );
    if (explicit_reg_args) {
        explicit_reg_args->reg_type = ( encoded_addr_mode & 0x0000F000 ) >> 12;
        explicit_reg_args->reg_num = ( encoded_addr_mode & 0x00000F00 ) >> 8;
        explicit_reg_args->encoded_reg_size = encoded_addr_mode & 0x000000FF;
    }
    return explicit_reg_args;
}

fcml_ptr fcml_fnp_def_addr_mode_args_decoder_opcode_reg( fcml_uint32_t encoded_addr_mode ) {
    fcml_sf_def_tma_opcode_reg *opcode_reg_args = (fcml_sf_def_tma_opcode_reg*) fcml_fn_env_memory_alloc( sizeof(fcml_sf_def_tma_opcode_reg) );
    if (opcode_reg_args) {
        opcode_reg_args->reg_type = ( encoded_addr_mode & 0x0000FF00 ) >> 8;
        opcode_reg_args->encoded_reg_size = encoded_addr_mode & 0x000000FF;
    }
    return opcode_reg_args;
}

fcml_ptr fcml_fnp_def_addr_mode_args_decoder_immediate_dis_relative( fcml_uint32_t encoded_addr_mode ) {
    fcml_sf_def_tma_immediate_dis_relative *immediate_dis_relative_args = (fcml_sf_def_tma_immediate_dis_relative*) fcml_fn_env_memory_alloc(
            sizeof(fcml_sf_def_tma_immediate_dis_relative) );
    if (immediate_dis_relative_args) {
        immediate_dis_relative_args->encoded_size = encoded_addr_mode & 0x000000FF;
    }
    return immediate_dis_relative_args;
}

fcml_ptr fcml_fnp_def_addr_mode_args_decoder_explicit_gps_reg_addressing( fcml_uint32_t encoded_addr_mode ) {
    fcml_sf_def_tma_explicit_gps_reg_addressing *explicit_gps_reg_addressing_args = (fcml_sf_def_tma_explicit_gps_reg_addressing*) fcml_fn_env_memory_alloc(
            sizeof(fcml_sf_def_tma_explicit_gps_reg_addressing) );
    if (explicit_gps_reg_addressing_args) {
        explicit_gps_reg_addressing_args->reg_num = ( encoded_addr_mode & 0x00FF0000 ) >> 16;
        explicit_gps_reg_addressing_args->encoded_operand_size = ( encoded_addr_mode & 0x0000FF00 ) >> 8;
        explicit_gps_reg_addressing_args->encoded_segment_register = encoded_addr_mode & 0x000000FF;
    }
    return explicit_gps_reg_addressing_args;
}

fcml_ptr fcml_fnp_def_addr_mode_args_decoder_explicit_ib( fcml_uint32_t encoded_addr_mode ) {
    fcml_sf_def_tma_explicit_ib *explicit_ib_args = (fcml_sf_def_tma_explicit_ib*) fcml_fn_env_memory_alloc( sizeof(fcml_sf_def_tma_explicit_ib) );
    if (explicit_ib_args) {
        explicit_ib_args->ib = encoded_addr_mode & 0x000000FF;
    }
    return explicit_ib_args;
}

fcml_ptr fcml_fnp_def_addr_mode_args_decoder_segment_relative_offset( fcml_uint32_t encoded_addr_mode ) {
    fcml_sf_def_tma_segment_relative_offset *segment_relative_offset_args = (fcml_sf_def_tma_segment_relative_offset*) fcml_fn_env_memory_alloc(
            sizeof(fcml_sf_def_tma_segment_relative_offset) );
    if (segment_relative_offset_args) {
        segment_relative_offset_args->encoded_operand_size = ( encoded_addr_mode & 0x0000FF00 ) >> 8;
        segment_relative_offset_args->encoded_segment_register = encoded_addr_mode & 0x000000FF;
    }
    return segment_relative_offset_args;
}

fcml_ptr fcml_fnp_def_addr_mode_args_decoder_rm( fcml_uint32_t encoded_addr_mode ) {
    fcml_sf_def_tma_rm *rm_args = (fcml_sf_def_tma_rm*) fcml_fn_env_memory_alloc( sizeof(fcml_sf_def_tma_rm) );
    if (rm_args) {
        rm_args->reg_type = ( encoded_addr_mode & 0x000000F0 ) >> 4;
        rm_args->encoded_register_operand_size = ( encoded_addr_mode & 0x0000FF00 ) >> 8;
        rm_args->encoded_memory_operand_size = ( encoded_addr_mode & 0x00FF0000 ) >> 16;
        rm_args->flags = encoded_addr_mode & 0x0000000F;
        rm_args->is_vsib = FCML_FALSE;
        rm_args->vector_index_register = 0;
    }
    return rm_args;
}

fcml_ptr fcml_fnp_def_addr_mode_args_decoder_r( fcml_uint32_t encoded_addr_mode ) {
    fcml_sf_def_tma_r *r_args = (fcml_sf_def_tma_r*) fcml_fn_env_memory_alloc( sizeof(fcml_sf_def_tma_r) );
    if (r_args) {
        r_args->reg_type = (fcml_en_register) ( encoded_addr_mode & 0x0000000F );
        r_args->encoded_register_operand_size = ( encoded_addr_mode & 0x00000FF0 ) >> 4;
    }
    return r_args;
}

fcml_ptr fcml_fnp_def_addr_mode_args_decoder_vex_vvvv( fcml_uint32_t encoded_addr_mode ) {
    fcml_sf_def_tma_vex_vvvv_reg *vex_vvvv_args = (fcml_sf_def_tma_vex_vvvv_reg*) fcml_fn_env_memory_alloc( sizeof(fcml_sf_def_tma_vex_vvvv_reg) );
    if (vex_vvvv_args) {
        vex_vvvv_args->reg_type = encoded_addr_mode & 0x0000000F;
        vex_vvvv_args->encoded_register_size = ( encoded_addr_mode & 0x00000FF0 ) >> 4;
    }
    return vex_vvvv_args;
}

fcml_ptr fcml_fnp_def_addr_mode_args_decoder_vsib( fcml_uint32_t encoded_addr_mode ) {
    fcml_sf_def_tma_rm *vsib_args = (fcml_sf_def_tma_rm*) fcml_fn_env_memory_alloc( sizeof(fcml_sf_def_tma_rm) );
    if (vsib_args) {
        vsib_args->vector_index_register = encoded_addr_mode >> 8;
        vsib_args->encoded_memory_operand_size = encoded_addr_mode & 0x000000FF;
        vsib_args->encoded_register_operand_size = 0;
        vsib_args->flags = FCML_RMF_M;
        vsib_args->reg_type = FCML_REG_UNDEFINED;
        vsib_args->is_vsib = FCML_TRUE;
    }
    return vsib_args;
}

fcml_ptr fcml_fnp_def_addr_mode_args_decoder_pseudo_op( fcml_uint32_t encoded_addr_mode ) {
    fcml_sf_def_tma_pseudo_op *pseudo_op_args = (fcml_sf_def_tma_pseudo_op*) fcml_fn_env_memory_alloc( sizeof(fcml_sf_def_tma_pseudo_op) );
    if (pseudo_op_args) {
        pseudo_op_args->mask = (fcml_uint8_t) ( encoded_addr_mode & 0x000000FF );
    }
    return pseudo_op_args;
}

#define FCML_DEF_DECODERS_COUNT		( sizeof( fcml_def_addr_mode_args_decoders ) / sizeof( fcml_fnp_def_addr_mode_args_decoder ) )

fcml_fnp_def_addr_mode_args_decoder fcml_def_addr_mode_args_decoders[] = {
NULL, fcml_fnp_def_addr_mode_args_decoder_imm, fcml_fnp_def_addr_mode_args_decoder_explicit_reg, fcml_fnp_def_addr_mode_args_decoder_opcode_reg,
        fcml_fnp_def_addr_mode_args_decoder_immediate_dis_relative,
        NULL, fcml_fnp_def_addr_mode_args_decoder_explicit_gps_reg_addressing, fcml_fnp_def_addr_mode_args_decoder_explicit_ib,
        fcml_fnp_def_addr_mode_args_decoder_segment_relative_offset, fcml_fnp_def_addr_mode_args_decoder_rm, fcml_fnp_def_addr_mode_args_decoder_r,
        fcml_fnp_def_addr_mode_args_decoder_vex_vvvv, fcml_fnp_def_addr_mode_args_decoder_is, fcml_fnp_def_addr_mode_args_decoder_vsib,
        fcml_fnp_def_addr_mode_args_decoder_pseudo_op };

fcml_st_def_decoded_addr_mode* fcml_fn_def_decode_addr_mode_args( fcml_uint32_t encoded_addr_mode, fcml_ceh_error *error ) {

    *error = FCML_CEH_GEC_NO_ERROR;

    fcml_st_def_decoded_addr_mode *addr_mode = (fcml_st_def_decoded_addr_mode*) fcml_fn_env_memory_alloc( sizeof(fcml_st_def_decoded_addr_mode) );

    if (addr_mode) {

        addr_mode->addr_mode = FCML_GET_ADDR_MODE( encoded_addr_mode );

        /* Store access mode for this operand decoding.*/
        fcml_int access_mode = FCML_AM_ACCESS_MODE_UNDEFINED;
        if (encoded_addr_mode & FCML_OA_W) {

            /* Destination operands for some instructions can be also a source operands.
             * In such a case "READ" flag has to be set for such operands.
             */
            access_mode |= (fcml_int) FCML_AM_WRITE;
            if (encoded_addr_mode & FCML_OA_R) {
                access_mode |= (fcml_int) FCML_AM_READ;
            }

        } else {
            /* All operands but destination ones have the access mode automatically set to "READ". */
            access_mode |= (fcml_int) FCML_AM_READ;
        }

        addr_mode->access_mode = (fcml_en_access_mode) access_mode;

        if (addr_mode->addr_mode > FCML_DEF_DECODERS_COUNT) {
            /* Corrupted instruction model. */
            *error = FCML_CEH_GEC_INTERNAL_ERROR;
            fcml_fn_env_memory_free( addr_mode );
            return NULL;
        }

        addr_mode->addr_mode_args = NULL;
        fcml_fnp_def_addr_mode_args_decoder args_decoder = fcml_def_addr_mode_args_decoders[addr_mode->addr_mode];
        if (args_decoder) {
            addr_mode->addr_mode_args = args_decoder( encoded_addr_mode & 0x00FFFFFF );
            if (!addr_mode->addr_mode_args) {
                fcml_fn_env_memory_free( addr_mode );
                addr_mode = NULL;
                *error = FCML_CEH_GEC_OUT_OF_MEMORY;
            }
        }

    } else {
        *error = FCML_CEH_GEC_OUT_OF_MEMORY;
    }

    return addr_mode;
}

void fcml_fnp_def_free_addr_mode( fcml_st_def_decoded_addr_mode *decoded_addr_mode ) {
    if (decoded_addr_mode) {
        if (decoded_addr_mode->addr_mode_args) {
            fcml_fn_env_memory_free( decoded_addr_mode->addr_mode_args );
        }
        fcml_fn_env_memory_free( decoded_addr_mode );
    }
}

