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

#ifndef FCML_MODRM_ENCODER_H_
#define FCML_MODRM_ENCODER_H_

#include <fcml_common.h>
#include <fcml_types.h>

#include "fcml_ceh.h"
#include "fcml_modrm.h"
#include "fcml_stream.h"

/* Some macros that might be also useful outside encoder.*/

#define FCML_MODRM_ENC_MOD(x)				((x) << 6)
#define FCML_MODRM_ENC_REG_OPCODE(x)		((x) << 3)
#define FCML_MODRM_ENC_RM(x)				(x)
#define FCML_MODRM_ENC(mod,reg,rm)			(FCML_MODRM_ENC_MOD(mod) | \
        FCML_MODRM_ENC_REG_OPCODE(reg) | FCML_MODRM_ENC_RM(rm))

#define FCML_MODRM_ENC_SIB_SS(x)			((x) << 6)
#define FCML_MODRM_ENC_SIB_INDEX(x)			((x) << 3)
#define FCML_MODRM_ENC_SIB_BASE(x)			(x)
#define FCML_MODRM_SIB_ENC(ss,index,base)	(FCML_MODRM_ENC_SIB_SS(ss) | \
        FCML_MODRM_ENC_SIB_INDEX(index) | FCML_MODRM_ENC_SIB_BASE(base))

typedef struct fcml_st_encoded_modrm {
    fcml_uint8_t modrm;
    fcml_nuint8_t sib;
    fcml_uint8_t ext_R;
    fcml_uint8_t ext_R_prim;
    fcml_uint8_t ext_X;
    fcml_uint8_t ext_B;
    fcml_uint8_t ext_V_prim;
    fcml_uint8_t displacement[4];
    fcml_uint8_t displacement_size;
    fcml_bool is_rip;
    fcml_bool is_rip_encoded;
    fcml_int64_t rip_address;
} fcml_st_encoded_modrm;

typedef struct fcml_st_modrm_encoder_context {
    /* Sets 32 or 64 bit addressing mode.*/
    fcml_en_operating_mode op_mode;
    /* Preferred effective address size that should be
     * used to encode ModR/M.
     */
    fcml_usize effective_address_size;
    /* Effective address size ModR/M was encoded for. For example
     * "effective_address_size" might be set to 32 bits, but [BX+SI]
     * encoding forces 16 bit encoding. Set be encoder.
     */
    fcml_usize chosen_effective_address_size;
    /* Used to calculate N in compressed disp8. */
    fcml_usize input_size;
    /* SIMD vector size. */
    fcml_usize vector_length;
    /* This flag is set by encoder if there is alternative SIB
     * encoding available, but user chooses ModR/M only encoding.
     */
    fcml_bool is_sib_alternative;
    /* If set to true, encoder chooses SIB encoding instead on ModR/M
     * only alternative.
     */
    fcml_bool choose_sib_encoding;
    /* If there is alternative, use RIP encoding instead of SIB alternative. */
    fcml_bool choose_rip_encoding;
    /* SIMD instruction type. */
    fcml_uint32_t tuple_type;
    /* True if EVEX is available. */
    fcml_bool is_evex;
    /* EVEX.b field. */
    fcml_bool b;
} fcml_st_modrm_encoder_context;

fcml_ceh_error fcml_fn_modrm_encode(fcml_st_modrm_encoder_context *context,
        const fcml_st_modrm *decoded_modrm,
        fcml_st_encoded_modrm *encoded_modrm);

fcml_ceh_error fcml_fn_modrm_encode_rip_offset(fcml_st_memory_stream *stream,
        fcml_int64_t rip, fcml_uint8_t instruction_size,
        const fcml_st_encoded_modrm *encoded_modrm);

fcml_ceh_error fcml_fn_modrm_calculate_effective_address_size(
        const fcml_st_modrm *decoded_modrm, fcml_flags *effective_address_size);

#endif /* FCML_MODRM_ENCODER_H_ */
