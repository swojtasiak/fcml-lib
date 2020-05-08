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

#ifndef FCML_UTILS_H_
#define FCML_UTILS_H_

#include <fcml_types.h>
#include <fcml_common.h>
#include <fcml_errors.h>

#include "fcml_ceh.h"
#include "fcml_stream.h"

typedef enum fcml_en_utils_size_flags {
    FCML_ENUSF_8 = 0x01,
    FCML_ENUSF_16 = 0x02,
    FCML_ENUSF_32 = 0x04,
    FCML_ENUSF_64 = 0x08,
    FCML_ENUSF_ALL = ( FCML_ENUSF_8 | FCML_ENUSF_16 | FCML_ENUSF_32 | FCML_ENUSF_64 )
} fcml_en_utils_size_flags;

fcml_ceh_error fcml_fn_utils_conv_int64_to_int(
        const fcml_uint64_t src, fcml_bool is_src_signed,
        fcml_st_integer *dest, fcml_en_utils_size_flags filter);

fcml_ceh_error fcml_fn_utils_conv_int_to_int(const fcml_st_integer *src,
        fcml_st_integer *dest, fcml_usize expected_source_size,
        fcml_usize destination_size);

fcml_ceh_error fcml_fn_utils_conv_int_to_uint8(const fcml_st_integer *src,
        fcml_uint8_t *dest);

fcml_ceh_error fcml_fn_utils_conv_int_to_uint16(const fcml_st_integer *src,
        fcml_uint16_t *dest);

fcml_ceh_error fcml_fn_utils_conv_int_to_uint32(const fcml_st_integer *src,
        fcml_uint32_t *dest);

fcml_ceh_error fcml_fn_utils_conv_int_to_uint64(const fcml_st_integer *src,
        fcml_uint64_t *dest);

fcml_ceh_error fcml_fn_utils_conv_int_to_int8(const fcml_st_integer *src,
        fcml_int8_t *dest);

fcml_ceh_error fcml_fn_utils_conv_int_to_int16(const fcml_st_integer *src,
        fcml_int16_t *dest);

fcml_ceh_error fcml_fn_utils_conv_int_to_int32(const fcml_st_integer *src,
        fcml_int32_t *dest);

fcml_ceh_error fcml_fn_utils_conv_int_to_int64(const fcml_st_integer *src,
        fcml_int64_t *dest);

fcml_ceh_error fcml_fn_utils_decode_integer(fcml_st_memory_stream *stream,
        fcml_st_integer *src, fcml_usize size);

fcml_ceh_error fcml_fn_utils_encode_integer(fcml_st_memory_stream *stream,
        const fcml_st_integer *src);

fcml_ceh_error fcml_fn_utils_offset_to_integer(const fcml_st_offset *offset,
        fcml_st_integer *src);

fcml_ceh_error fcml_fn_utils_integer_to_offset(const fcml_st_integer *src,
        fcml_st_offset *offset);

fcml_ceh_error fcml_fn_utils_extend_int(fcml_st_integer *src,
        fcml_usize ext);

fcml_ceh_error fcml_fn_utils_conv_map_error(fcml_int error);

void fcml_fn_utils_conv_gec_to_error_info(fcml_bool enabled,
        fcml_st_ceh_error_container *error_container, fcml_ceh_error code );

fcml_ceh_error fcml_fn_utils_prepare_entry_point(fcml_st_entry_point *entry_point);

fcml_bool fcml_fn_utils_is_disp_neg(const fcml_st_integer *displacement);

fcml_bool fcml_fn_utils_validate_vector_len(fcml_usize vector_length);

fcml_int64_t fcml_fn_utils_divide_integer(const fcml_st_integer *dividend,
        fcml_st_integer *quotient, fcml_int32_t divisor);

/**
 * Returns TRUE if value can be safely cast to int32.
 */
static inline fcml_bool safe_cast_i6432(fcml_int64_t value) {
    return value <= FCML_INT32_MAX && value >= FCML_INT32_MIN;
}

/**
 * Returns true if operand is SIMD register.
 */
static inline fcml_bool is_simd_reg(const fcml_st_operand *operand) {
    return operand->type == FCML_OT_REGISTER &&
            operand->reg.type == FCML_REG_SIMD;
}

/**
 * Returns true if operand is IMM.
 */
static inline fcml_bool is_imm(const fcml_st_operand *operand) {
    return operand->type == FCML_OT_IMMEDIATE;
}

/* Returns true if register type is undefined. */
static inline fcml_bool is_reg_undef(const fcml_st_register *reg) {
    return reg->type == FCML_REG_UNDEFINED;
}

/* Returns true if integer value is 0. */
static inline fcml_bool is_integer_zero(const fcml_st_integer *imm) {
    switch(imm->size) {
    case FCML_DS_8:
        return imm->int8 == 0;
    case FCML_DS_16:
        return imm->int16 == 0;
    case FCML_DS_32:
        return imm->int32 == 0;
    case FCML_DS_64:
        return imm->int64 == 0;
    }
    return FCML_FALSE;
}

#endif /* FCML_UTILS_H_ */
