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

#ifndef FCML_MODRM_DECODER_H_
#define FCML_MODRM_DECODER_H_

#include <fcml_common.h>
#include <fcml_types.h>

#include "fcml_ceh.h"
#include "fcml_modrm.h"
#include "fcml_stream.h"

/* Some macros that might be also useful outside decoder.*/

#define FCML_MODRM_DEC_MOD(x)			(x >> 6)
#define FCML_MODRM_DEC_REG_OPCODE(x)	((x & 0x38) >> 3)
#define FCML_MODRM_DEC_RM(x)			(x & 0x07)

#define FCML_MODRM_SIB_SS(x)			(x >> 6)
#define FCML_MODRM_SIB_INDEX(x)			((x & 0x38) >> 3)
#define FCML_MODRM_SIB_BASE(x)			(x& 0x07)

#define FCML_MODRM_DEC_FLAG_EXTEND_DISPLACEMENT_TO_ASA		0x01

typedef struct fcml_st_modrm_source {
    fcml_uint8_t ext_R;
    fcml_uint8_t ext_R_prim;
    fcml_uint8_t ext_X;
    fcml_uint8_t ext_B;
    fcml_uint8_t ext_V_prim;
    fcml_bool is_vsib;
    fcml_usize vsib_index_size;
    fcml_st_memory_stream *stream;
} fcml_st_modrm_source;

/**
 * Displacement in raw form.
 */
typedef struct fcml_st_modrm_displacement {
    /** Displacement as encoded in disp8/disp16/disp32/disp8*N. */
    fcml_st_integer displacement;
    /** Scaling factor N in EVEX specific compressed disp8*N. */
    fcml_nuint32_t N;
} fcml_st_modrm_displacement;

typedef struct fcml_st_modrm_details {
    /** ModR/M byte. */
    fcml_uint8_t modrm;
    /** Optional SIB byte. */
    fcml_nuint8_t sib;
    /** Displacement as it is encoded in the instruction. */
    fcml_st_modrm_displacement displacement;
} fcml_st_modrm_details;

typedef struct fcml_st_modrm_decoder_context {
    /* Sets 32 or 64 bit addressing mode. */
    fcml_en_operating_mode op_mode;
    /* Effective address size using to decode/encode ModR/M.
     * It's very important to set this value properly,
     * because 16 and 32/64 addressing forms and encoded in
     * different way.
     */
    fcml_usize effective_address_size;
    /**
     * Used as an input size when N factor for compressed disp8 is calculated.
     */
    fcml_usize input_size;
    /** Length of the SIMD vector. */
    fcml_usize vector_length;
    /** Tuple type needed to calculate N factor for compressed disp8. */
    fcml_uint32_t tuple_type;
    /** True if EVEX prefix is available. Used to handle compressed
     * disp8 encoding. */
    fcml_bool is_evex;
    /** True if EVEX.b is set. */
    fcml_bool b;
} fcml_st_modrm_decoder_context;

fcml_ceh_error fcml_fn_modrm_decode(fcml_st_modrm_decoder_context *context,
        fcml_st_modrm_source *modrm_source, fcml_st_modrm *decoded_modrm,
        fcml_st_modrm_details *modrm_details, fcml_uint8_t flags);

fcml_ceh_error fcml_fn_modrm_decode_rip(fcml_uint64_t rip,
        fcml_usize effective_address_size, fcml_st_offset *offset,
        fcml_st_offset *address);

#endif /* FCML_MODRM_DECODER_H_ */
