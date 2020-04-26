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

#include "fcml_def.h"
#include "fcml_env_int.h"

static fcml_ptr args_decoder_is(fcml_operand_desc encoded_addr_mode) {
    FCML_ENV_ALLOC_CLEAR(is_args, fcml_st_def_tma_is);
    if (is_args) {
        is_args->flags = ( encoded_addr_mode & 0x000000FF );
    }
    return is_args;
}

static fcml_ptr args_decoder_imm(fcml_operand_desc encoded_addr_mode) {
    FCML_ENV_ALLOC_CLEAR(imm_args, fcml_st_def_tma_imm);
    if (imm_args) {
        imm_args->encoded_size = (encoded_addr_mode & 0x0000FF00) >> 8;
        imm_args->encoded_ex_size = encoded_addr_mode & 0x000000FF;
        imm_args->is_64bit_imm_allowed =
                encoded_addr_mode & FCML_OP_IMM_64_ALLOWED;
    }
    return imm_args;
}

static fcml_ptr args_decoder_explicit_reg(fcml_operand_desc addr_mode) {
    FCML_ENV_ALLOC_CLEAR(explicit_reg_args, fcml_st_def_tma_explicit_reg);
    if (explicit_reg_args) {
        explicit_reg_args->reg_type = (addr_mode & 0x0000F000 ) >> 12;
        explicit_reg_args->reg_num = (addr_mode & 0x00000F00 ) >> 8;
        explicit_reg_args->encoded_reg_size = addr_mode & 0x000000FF;
    }
    return explicit_reg_args;
}

static fcml_ptr args_decoder_opcode_reg(fcml_operand_desc encoded_addr_mode) {
    FCML_ENV_ALLOC_CLEAR(opcode_reg_args, fcml_st_def_tma_opcode_reg);
    if (opcode_reg_args) {
        opcode_reg_args->reg_type = (encoded_addr_mode & 0x0000FF00) >> 8;
        opcode_reg_args->encoded_reg_size = encoded_addr_mode & 0x000000FF;
    }
    return opcode_reg_args;
}

static fcml_ptr args_decoder_immediate_dis_relative(
        fcml_operand_desc addr_mode) {
    FCML_ENV_ALLOC_CLEAR(immediate_dis_relative_args,
            fcml_sf_def_tma_immediate_dis_relative);
    if (immediate_dis_relative_args) {
        immediate_dis_relative_args->encoded_size = addr_mode & 0x000000FF;
    }
    return immediate_dis_relative_args;
}

static fcml_ptr args_decoder_explicit_gps_reg_addressing(
        fcml_operand_desc addr_mode) {
    FCML_ENV_ALLOC_CLEAR(args, fcml_st_def_tma_explicit_gps_reg_addressing);
    if (args) {
        args->reg_num = (fcml_uint8_t)((addr_mode & 0x00FF0000) >> 16);
        args->encoded_operand_size = (addr_mode & 0x0000FF00) >> 8;
        args->encoded_segment_register = addr_mode & 0x000000FF;
    }
    return args;
}

static fcml_ptr args_decoder_explicit_ib(fcml_operand_desc addr_mode) {
    FCML_ENV_ALLOC_CLEAR(explicit_ib_args, fcml_st_def_tma_explicit_ib);
    if (explicit_ib_args) {
        explicit_ib_args->ib = addr_mode & 0x000000FF;
    }
    return explicit_ib_args;
}

static fcml_ptr args_decoder_segment_relative_offset(
        fcml_operand_desc addr_mode) {
    FCML_ENV_ALLOC_CLEAR(segment_relative_offset_args,
            fcml_st_def_tma_segment_relative_offset);
    if (segment_relative_offset_args) {
        segment_relative_offset_args->encoded_operand_size =
                (addr_mode & 0x0000FF00) >> 8;
        segment_relative_offset_args->encoded_segment_register =
                addr_mode & 0x000000FF;
    }
    return segment_relative_offset_args;
}

static fcml_ptr args_decoder_rm(fcml_operand_desc addr_mode) {
    FCML_ENV_ALLOC_CLEAR(rm_args, fcml_st_def_tma_rm);
    if (rm_args) {
        fcml_operand_decorators decorators = FCML_DECORATORS(addr_mode);
        rm_args->reg_type = (addr_mode & 0x000000F0) >> 4;
        rm_args->encoded_register_operand_size =
                (addr_mode & 0x0000FF00) >> 8;
        rm_args->encoded_memory_operand_size =
                (fcml_uint8_t)((addr_mode & 0x00FF0000) >> 16);
        rm_args->flags = addr_mode & 0x0000000F;
        rm_args->is_vsib = FCML_FALSE;
        rm_args->vector_index_register = 0;
        rm_args->is_bcast = FCML_IS_DECOR_BCAST(decorators);
    }
    return rm_args;
}

static fcml_ptr args_decoder_r(fcml_operand_desc addr_mode) {
    FCML_ENV_ALLOC_CLEAR(r_args, fcml_st_def_tma_r);
    if (r_args) {
        r_args->reg_type = (fcml_en_register)(addr_mode & 0x0000000F);
        r_args->encoded_register_operand_size =
                (fcml_uint8_t)((addr_mode & 0x00000FF0) >> 4);
        /* TODO: Decode decorators here. Hide the encoding format here! */
        r_args->decorators = FCML_DECORATORS(addr_mode);
    }
    return r_args;
}

static fcml_ptr args_decoder_vex_vvvv(fcml_operand_desc addr_mode) {
    FCML_ENV_ALLOC_CLEAR(vex_vvvv_args, fcml_st_def_tma_vex_vvvv_reg);
    if (vex_vvvv_args) {
        vex_vvvv_args->reg_type = addr_mode & 0x0000000F;
        vex_vvvv_args->encoded_register_size =
                (fcml_uint8_t)((addr_mode & 0x00000FF0) >> 4);
    }
    return vex_vvvv_args;
}

static fcml_ptr args_decoder_vsib(fcml_operand_desc addr_mode) {
    FCML_ENV_ALLOC_CLEAR(vsib_args, fcml_st_def_tma_rm);
    if (vsib_args) {
        vsib_args->vector_index_register = (fcml_uint8_t)(addr_mode >> 8);
        vsib_args->encoded_memory_operand_size = addr_mode & 0x000000FF;
        vsib_args->encoded_register_operand_size = 0;
        vsib_args->flags = FCML_RMF_M;
        vsib_args->reg_type = FCML_REG_UNDEFINED;
        vsib_args->is_vsib = FCML_TRUE;
    }
    return vsib_args;
}

static fcml_ptr args_decoder_pseudo_op(fcml_operand_desc addr_mode) {
    FCML_ENV_ALLOC_CLEAR(pseudo_op_args, fcml_st_def_tma_pseudo_op);
    if (pseudo_op_args) {
        pseudo_op_args->mask = (fcml_uint8_t)(addr_mode & 0x000000FF);
    }
    return pseudo_op_args;
}

static fcml_ptr args_decoder_virtual_op(fcml_operand_desc encoded_addr_mode) {
    FCML_ENV_ALLOC_CLEAR(virtual_op_args, fcml_st_def_tma_virtual_op);
    if (virtual_op_args) {
        virtual_op_args->decorators = FCML_DECORATORS(encoded_addr_mode);
    }
    return virtual_op_args;
}

typedef fcml_ptr (*addr_mode_args_decoder)(fcml_operand_desc);

#define FCML_DEF_DECODERS_COUNT (sizeof(args_decoders) \
        / sizeof(addr_mode_args_decoder))

/**
 * Ordering is really important here because every decoder corresponds
 * to one addressing mode from "fcml_def.h".
 */
static addr_mode_args_decoder args_decoders[] = {
    NULL,
    args_decoder_imm,
    args_decoder_explicit_reg,
    args_decoder_opcode_reg,
    args_decoder_immediate_dis_relative,
    NULL,
    args_decoder_explicit_gps_reg_addressing,
    args_decoder_explicit_ib,
    args_decoder_segment_relative_offset,
    args_decoder_rm,
    args_decoder_r,
    args_decoder_vex_vvvv,
    args_decoder_is,
    args_decoder_vsib,
    args_decoder_pseudo_op,
    args_decoder_virtual_op
};

static fcml_en_access_mode decode_access_mode(
        const fcml_operand_desc operand_desc) {
    fcml_en_access_mode access_mode = FCML_AM_ACCESS_MODE_UNDEFINED;
    if (operand_desc & FCML_OA_W) {
        /* Destination operands for some instructions can be
         * also a source operands. In such a case "READ" flag
         * has to be set for such operands. */
        access_mode = (fcml_en_access_mode)(access_mode | FCML_AM_WRITE);
        if (operand_desc & FCML_OA_R) {
            access_mode = (fcml_en_access_mode)(access_mode | FCML_AM_READ);
        }
    } else {
        /* All operands but destination ones have the access mode
         * automatically set to "READ". */
        access_mode = FCML_AM_READ;
    }
    return access_mode;
}

fcml_ceh_error fcml_fn_def_decode_addr_mode_args(
        const fcml_operand_desc operand_desc,
        fcml_st_def_decoded_addr_mode **decoded_addr_mode) {

    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
    *decoded_addr_mode = NULL;

    FCML_ENV_ALLOC_CLEAR(addr_mode, fcml_st_def_decoded_addr_mode);
    if (addr_mode) {
        addr_mode->addr_mode = FCML_GET_ADDR_MODE(operand_desc);
        addr_mode->access_mode = decode_access_mode(operand_desc);
        if (addr_mode->addr_mode > FCML_DEF_DECODERS_COUNT) {
            /* Corrupted instruction model. */
            fcml_fn_env_memory_free(addr_mode);
            return FCML_CEH_GEC_INTERNAL_ERROR;
        }

        addr_mode->addr_mode_args = NULL;
        addr_mode_args_decoder decoder = args_decoders[addr_mode->addr_mode];
        if (decoder) {
            /* Send addressing mode together with decorators, because they
             * are used by decoders/encoders too. */
            addr_mode->addr_mode_args = decoder(operand_desc);
            if (!addr_mode->addr_mode_args) {
                fcml_fn_env_memory_free(addr_mode);
                return FCML_CEH_GEC_OUT_OF_MEMORY;
            }
        }

        *decoded_addr_mode = addr_mode;
    } else {
        error = FCML_CEH_GEC_OUT_OF_MEMORY;
    }

    return error;
}

void fcml_fnp_def_free_addr_mode(
        fcml_st_def_decoded_addr_mode *decoded_addr_mode) {
    if (decoded_addr_mode) {
        if (decoded_addr_mode->addr_mode_args) {
            fcml_fn_env_memory_free(decoded_addr_mode->addr_mode_args);
        }
        fcml_fn_env_memory_free(decoded_addr_mode);
    }
}

/**
 * Converts VSIB register type to corresponding data size.
 */
fcml_usize fcml_fn_def_vsib_reg_to_ds(fcml_uint8_t vsib_reg) {
    switch (vsib_reg) {
    case FCML_VSIB_XMM:
        return FCML_DS_128;
    case FCML_VSIB_YMM:
        return FCML_DS_256;
    case FCML_VSIB_ZMM:
        return FCML_DS_512;
    case FCML_VSIB_UNDEF:
        return FCML_DS_UNDEF;
    }
    return FCML_DS_UNDEF;
}
