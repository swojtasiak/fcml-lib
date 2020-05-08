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

#include "fcml_modrm_encoder.h"

#include <fcml_common.h>
#include <fcml_errors.h>
#include <fcml_types.h>

#include "fcml_stream.h"
#include "fcml_utils.h"
#include "fcml_disp8_n.h"

static fcml_st_memory_stream map_displacement_to_stream(
        fcml_st_encoded_modrm *encoded_modrm) {
    fcml_st_memory_stream stream;
    stream.base_address = &(encoded_modrm->displacement);
    stream.offset = 0;
    stream.size = sizeof(encoded_modrm->displacement);
    return stream;
}

static inline fcml_ceh_error is_displacement(const fcml_st_address *address) {
    return address->offset.size || address->effective_address.displacement.size;
}

static fcml_ceh_error convert_absolute_address_to_integer(
        const fcml_st_address *address, fcml_st_integer *integer) {
    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
    if (address->address_form == FCML_AF_OFFSET) {
        if (address->offset.size) {
            error = fcml_fn_utils_offset_to_integer(&(address->offset),
                    integer);
        } else {
            *integer = address->effective_address.displacement;
        }
    } else {
        /* Combined effective address can not be treated as absolute offset. */
        return FCML_CEH_GEC_INVALID_INPUT;
    }
    return error;
}

static fcml_ceh_error encode_compress_disp8(
        const fcml_st_modrm_encoder_context *context,
        const fcml_st_integer *displacement, fcml_st_integer *dest,
        fcml_usize asa) {

    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
    fcml_uint32_t n = fcml_fn_d8n_calculate_n(context->tuple_type,
           context->b, context->input_size, context->vector_length);

    if (n) {
        fcml_st_integer compressed_disp;
        fcml_int64_t remainder = fcml_fn_utils_divide_integer(
                displacement, &compressed_disp, n);

        if (remainder == 0) {
            /* Check if we can still store compressed displacement
             * on 8-bits. */
            error = fcml_fn_utils_conv_int_to_int(
                    &compressed_disp, dest, asa, FCML_DS_8);
        } else {
            error = FCML_CEH_GEC_VALUE_OUT_OF_RANGE;
        }
    }

    if (error == FCML_CEH_GEC_VALUE_OUT_OF_RANGE || !n) {
        /* Displacement cannot be compressed, so force disp32. */
        error = fcml_fn_utils_conv_int_to_int(displacement, dest,
                asa, asa == FCML_DS_16 ? FCML_DS_16 : FCML_DS_32);
    }

    return error;
}

/* Optionally extends and encodes displacement.*/
static fcml_ceh_error encode_displacement(
        fcml_st_modrm_encoder_context *context,
        const fcml_st_integer *displacement,
        fcml_st_encoded_modrm *encoded_modrm, fcml_usize asa,
        fcml_usize *disp_size, fcml_bool is_rip) {

    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

    fcml_st_integer dest;

    /* Displacement value is always signed, so change it to signed value
     * if it has expected size.
     */
    fcml_st_integer src = *displacement;
    if (src.size == asa) {
        src.is_signed = FCML_TRUE;
    }

    if (*disp_size == FCML_DS_UNDEF) {
        /* Check if compressed disp8 has to be used. Notice that for EVEX
         * encoded instructions disp8 is always compressed. */
        if (!is_rip && context->is_evex && asa != FCML_DS_16) {
           error = encode_compress_disp8(context, &src, &dest,
                   asa);
        } else {

            /* Convert displacement to 8 bits value.*/
            error = fcml_fn_utils_conv_int_to_int(&src, &dest, asa,
                    FCML_DS_8);

            if (error == FCML_CEH_GEC_VALUE_OUT_OF_RANGE) {
                /* Convert displacement to 32 bits value.*/
                error = fcml_fn_utils_conv_int_to_int(&src, &dest,
                        asa, asa == FCML_DS_16 ? FCML_DS_16 : FCML_DS_32);
            }
        }
    } else {
        error = fcml_fn_utils_conv_int_to_int(&src, &dest, asa,
                *disp_size);
    }

    if (error) {
        return error;
    }

    /* Gets displacement as stream. */
    fcml_st_memory_stream stream = map_displacement_to_stream(
            encoded_modrm);

    /* Writes displacement to the stream. */
    error = fcml_fn_utils_encode_integer(&stream, &dest);
    if (error) {
        return error;
    }

    *disp_size = dest.size;

    encoded_modrm->displacement_size = stream.offset;

    return error;
}

static fcml_ceh_error encode_16bit(fcml_st_modrm_encoder_context *context,
        const fcml_st_modrm *decoded_modrm,
        fcml_st_encoded_modrm *encoded_modrm) {

    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

    const fcml_st_address *address = &(decoded_modrm->address);
    const fcml_st_effective_address *effective_address =
            &(address->effective_address);

    /* ModR/M fields.*/
    fcml_uint8_t f_reg = 0;
    fcml_uint8_t f_mod = 0;
    fcml_uint8_t f_rm = 0;

    if (context->op_mode == FCML_OM_64_BIT) {
        return FCML_CEH_GEC_INVALID_ADDRESSING_FORM;
    }

    /* Check if there is disp16 addressing mode encoded.*/
    if (!effective_address->base.type
            && (effective_address->displacement.size || address->offset.size)) {
        /* Sign extends displacement to 16 bits if there is such need,
         * and encode it. Remember that in 16 bit addressing mode address
         * form doesn't matter.
         */
        fcml_st_integer absolute_address;

        error = convert_absolute_address_to_integer(address,
                &absolute_address);
        if (!error) {
            fcml_usize disp_size = FCML_DS_16;
            error = encode_displacement(context,
                    &absolute_address, encoded_modrm, FCML_DS_16, &disp_size,
                    FCML_FALSE);
        }

        f_rm = 0x06;
    } else if (effective_address->base.type) {

        /* Registers are allowed only in COMBINED addressing form.*/
        if (address->address_form != FCML_AF_COMBINED) {
            return FCML_CEH_GEC_INVALID_INPUT;
        }

        if (effective_address->base.type
                && effective_address->base.size != FCML_DS_16) {
            error = FCML_CEH_GEC_INVALID_ADDRESSING_FORM;
        }

        if (effective_address->index.type
                && effective_address->index.size != FCML_DS_16) {
            error = FCML_CEH_GEC_INVALID_ADDRESSING_FORM;
        }

        if (!error) {
            /* There is base register set.*/
            switch (effective_address->base.reg) {
            case FCML_REG_BX:
                if (effective_address->index.type) {
                    if (effective_address->index.reg == FCML_REG_DI) {
                        f_rm = 0x01;
                    }
                } else {
                    f_rm = 0x07;
                }
                break;
            case FCML_REG_BP:
                if (effective_address->index.type) {
                    switch (effective_address->index.reg) {
                    case FCML_REG_SI:
                        f_rm = 0x02;
                        break;
                    case FCML_REG_DI:
                        f_rm = 0x03;
                        break;
                    }
                } else if (!effective_address->displacement.size) {
                    /* BP is not allowed without displacement.*/
                    error = FCML_CEH_GEC_INVALID_ADDRESSING_FORM;
                } else {
                    f_rm = 0x06;
                }
                break;
            case FCML_REG_SI:
                f_rm = 0x04;
                break;
            case FCML_REG_DI:
                f_rm = 0x05;
                break;
            }

            if (!error) {
                /* Encode displacement if there is any.*/
                fcml_usize disp_size = FCML_DS_UNDEF;
                if (effective_address->displacement.size) {
                    error = encode_displacement(context,
                            &(effective_address->displacement), encoded_modrm,
                            FCML_DS_16, &disp_size, FCML_FALSE);
                }

                if (!error) {
                    /* Now encode displacement, is there is any.*/
                    switch (disp_size) {
                    case FCML_DS_UNDEF:
                        f_mod = 0x00;
                        break;
                    case FCML_DS_8:
                        f_mod = 0x01;
                        break;
                    case FCML_DS_16:
                        f_mod = 0x02;
                        break;
                    default:
                        /* Only disp8 and disp16 is supported in 16 bit
                         * addressing mode.
                         */
                        error = FCML_CEH_GEC_INVALID_ADDRESSING_FORM;
                        break;
                    }
                }
            }
        }
    } else if (decoded_modrm->reg.is_not_null) {
        f_mod = 0x03;
        f_rm = decoded_modrm->reg.value;
    } else {
        /* There is no base register and displacement, so*/
        error = FCML_CEH_GEC_INVALID_ADDRESSING_FORM;
    }

    if (!error) {
        /* Encode reg/opcode.*/
        f_reg = decoded_modrm->reg_opcode;
        /* Encode calculated ModR/M byte.*/
        encoded_modrm->modrm = FCML_MODRM_ENC(f_mod, f_reg, f_rm);
    }

    return error;
}

/* 32 and 64 bit addressing mode */
static fcml_ceh_error encode_3264bit(fcml_st_modrm_encoder_context *context,
        const fcml_st_modrm *decoded_modrm,
        fcml_st_encoded_modrm *encoded_modrm) {

    fcml_uint8_t f_mod = 0;
    fcml_uint8_t f_rm = 0;
    fcml_uint8_t f_reg = 0;

    fcml_uint8_t f_ext_R = 0;
    fcml_uint8_t f_ext_R_prim = 0;
    fcml_uint8_t f_ext_X = 0;
    fcml_uint8_t f_ext_B = 0;
    fcml_uint8_t f_ext_V_prim = 0;

    fcml_usize disp_size = 0;

    fcml_bool choose_sib = FCML_FALSE;

    const fcml_st_address *address = &(decoded_modrm->address);
    const fcml_st_effective_address *effective_address =
            &(address->effective_address);
    fcml_st_integer displacement = address->effective_address.displacement;

    /* Check if addressing mode and effective address size are compatible.*/
    if ((context->chosen_effective_address_size == FCML_DS_64
            && context->op_mode != FCML_OM_64_BIT)
            || (context->op_mode == FCML_OM_64_BIT
                    && context->chosen_effective_address_size == FCML_DS_16)) {
        return FCML_CEH_GEC_INVALID_ADDRESSING_FORM;
    }

    fcml_bool is_disp = is_displacement(address);
    fcml_bool is_base = effective_address->base.type != FCML_REG_UNDEFINED;
    fcml_bool is_index = effective_address->index.type != FCML_REG_UNDEFINED;

    /* Should be treated like standard displacement when RIP addressing is
     * not available.
     */
    fcml_bool is_rip_disp = effective_address->base.type == FCML_REG_IP;

    /* Sanity check. */
    if ((is_base || is_index) && address->address_form != FCML_AF_COMBINED) {
        return FCML_CEH_GEC_INVALID_ADDRESSING_FORM;
    }

    fcml_bool is_rip = FCML_FALSE;

    /* Check if there is SIB alternative.*/
    if (!is_rip_disp) {

        if (is_index) {
            choose_sib = FCML_TRUE;
        } else {
            if (!is_base && is_disp) {

                /* disp32 or RIP*/

                fcml_bool choose_rip = context->choose_rip_encoding
                        && (context->op_mode == FCML_OM_64_BIT);

                if (address->address_form != FCML_AF_OFFSET) {
                    choose_rip = FCML_FALSE;
                }

                if (choose_rip) {
                    /* Relative.*/
                    is_rip = FCML_TRUE;
                    context->is_sib_alternative = FCML_FALSE;
                } else {
                    /* In case of 64 bit addressing SIB is needed to encode
                     * absolute address. */
                    choose_sib = (context->op_mode == FCML_OM_64_BIT) ?
                                    FCML_TRUE : context->choose_sib_encoding;
                    context->is_sib_alternative = FCML_TRUE;
                }

            } else if (is_base) {
                /* [esp],edx can be only encoded with using of SIB byte. */
                if (effective_address->base.reg == FCML_REG_ESP) {
                    choose_sib = FCML_TRUE;
                } else if (effective_address->base.reg == FCML_REG_EBP
                        && !is_disp) {
                    /* This addressing mode can be only encoded with
                     * displacement set to 0. */
                    disp_size = FCML_DS_8;
                    displacement.int8 = 0;
                    displacement.size = FCML_DS_8;
                    is_disp = FCML_TRUE;
                } else {
                    /* RIP relative addressing can not be encoded using SIB.*/
                    if (effective_address->base.type != FCML_REG_IP) {
                        /* [base]+[disp8/disp32]*/
                        choose_sib = context->choose_sib_encoding;
                        context->is_sib_alternative = FCML_TRUE;
                    }
                }
            }
        }
    }

    if (choose_sib) {

        /* SIB needed.*/

        fcml_uint8_t f_base = 0;
        fcml_uint8_t f_ss = 0;
        fcml_uint8_t f_index = 0;

        /* Base register.*/
        if (is_base) {
            if (context->chosen_effective_address_size
                    != effective_address->base.size) {
                /* Wrong size of base register, it has to be equal to EASA. */
                return FCML_CEH_GEC_INVALID_ADDRESSING_FORM;
            }
            f_base = effective_address->base.reg;
            if (f_base > 7) {
                f_ext_B = 0x01;
                f_base &= 0x07;
            }
        } else {
            /* SIB without base register, there is only one addressing
             * mode with this combination and it needs disp32.
             */
            if (!is_disp) {
                return FCML_CEH_GEC_INVALID_ADDRESSING_FORM;
            }
            disp_size = FCML_DS_32;
            f_base = 0x05;
        }

        /* Index register.*/
        if (is_index) {
            /* Check if index register size is correct. */
            if (effective_address->index.type != FCML_REG_SIMD
                    && context->chosen_effective_address_size
                            != effective_address->index.size) {
                /* Wrong size of index register, it has to be equal to EASA. */
                return FCML_CEH_GEC_INVALID_ADDRESSING_FORM;
            }
            /* ESP is not allowed as index register. */
            if (effective_address->index.reg == FCML_REG_ESP) {
                return FCML_CEH_GEC_INVALID_ADDRESSING_FORM;
            }
            f_index = effective_address->index.reg;

            f_ext_X = (f_index >> 3) & 0x01;
            f_ext_V_prim = (f_index >> 4) & 0x01;
            f_index &= 0x07;
        } else {
            f_index = 0x04;
        }

        /* Scale factor.*/
        switch (effective_address->scale_factor) {
        case 2:
            f_ss = 1;
            break;
        case 4:
            f_ss = 2;
            break;
        case 8:
            f_ss = 3;
            break;
        }

        /* Encode SIB.*/
        encoded_modrm->sib.is_not_null = FCML_TRUE;
        encoded_modrm->sib.value = FCML_MODRM_SIB_ENC(f_ss, f_index, f_base);

        /* RM when SIB is used.*/
        f_rm = 0x04;

    } else {

        /* SIB not needed.*/

        if (is_base && !is_rip_disp) {
            if (context->chosen_effective_address_size
                    != effective_address->base.size) {
                return FCML_CEH_GEC_INVALID_ADDRESSING_FORM;
            }
            f_rm = effective_address->base.reg;
        } else if (decoded_modrm->reg.is_not_null) {
            f_mod = 0x03;
            f_rm = decoded_modrm->reg.value;
            if (effective_address->displacement.size) {
                return FCML_CEH_GEC_INVALID_ADDRESSING_FORM;
            }
        } else if (is_disp) {
            /* Absolute address or RIP. Disp8 is not supported in
             * this case, so force disp32. */
            disp_size = FCML_DS_32;
            f_rm = 0x05;
        } else {
            /* Only reg_opcode is encoded.*/
            f_mod = 0x03;
        }

        f_ext_B = (f_rm >> 3) & 0x01;
        f_ext_X = (f_rm >> 4) & 0x01;
        f_rm &= 0x07;
    }

    if (is_rip) {

        /* RIP given ad absolute address that has to be converted to
         * relative displacement.
         */

        fcml_st_integer rip_address;

        /* Offset is not available, so displacement was used instead.*/
        if (!address->offset.size) {
            return FCML_CEH_GEC_INVALID_ADDRESSING_FORM;
        }

        fcml_ceh_error error = fcml_fn_utils_offset_to_integer(
                &(address->offset), &rip_address);
        if (error) {
            return error;
        }

        /* Extends RIP address to 64 bit value.*/
        if (rip_address.size != FCML_DS_64) {
            error = fcml_fn_utils_extend_int(&rip_address, FCML_DS_64);
            if (error) {
                return error;
            }
        }

        /* Store RIP offset. It can be used then to calculate displacement*/
        encoded_modrm->is_rip = FCML_TRUE;
        encoded_modrm->rip_address = rip_address.int64;

        /* Check if 32 bit ASA should be used, if so check if RIP address is
         * not out of range.
         */
        fcml_usize asa =
                (context->chosen_effective_address_size) ?
                        context->chosen_effective_address_size :
                        context->effective_address_size;
        if (asa == FCML_DS_32) {
            if (rip_address.is_signed) {
                if (rip_address.int64 > FCML_INT32_MAX
                        || rip_address.int64 < FCML_INT32_MIN) {
                    return FCML_CEH_GEC_VALUE_OUT_OF_RANGE;
                }
            } else {
                if ((fcml_uint64_t) rip_address.int64 > FCML_UINT32_MAX) {
                    return FCML_CEH_GEC_VALUE_OUT_OF_RANGE;
                }
            }
        }

        f_mod = 0x00;

    } else if (is_disp || is_rip_disp) {

        if (is_base || is_index) {

            fcml_ceh_error error = encode_displacement(context,
                    &displacement, encoded_modrm,
                    context->chosen_effective_address_size, &disp_size,
                    is_rip_disp);
            if (error) {
                return error;
            }

            /* Encode displacement.*/
            if (disp_size == FCML_DS_8) {
                f_mod = 0x01;
            } else if (disp_size == FCML_DS_32 && is_base && !is_rip_disp) {
                f_mod = 0x02;
            } else {
                f_mod = 0x00;
            }

            /* Displacement has been already encoded, so post processing is
             * not needed anymore.
             */
            if (is_rip_disp) {
                encoded_modrm->is_rip = FCML_TRUE;
                encoded_modrm->is_rip_encoded = FCML_TRUE;
                encoded_modrm->rip_address = 0LL;
            }

        } else {

            /* Absolute address or RIP relative displacement. */
            fcml_st_integer absolute_address;

            /* Convert absolute address to generic integer value in
             * order to convert it to ASA size.
             */
            fcml_usize error =
                    convert_absolute_address_to_integer(address,
                            &absolute_address);
            if (error) {
                return error;
            }

            /* Absolute address without base or index register set
            * cannot be encoded as disp8. */
            disp_size = FCML_DS_32;

            error = encode_displacement(context,
                    &absolute_address, encoded_modrm,
                    context->chosen_effective_address_size, &disp_size,
                    is_rip_disp);
            if (error) {
                return error;
            }

            f_mod = 0x00;
        }

    }

    /* Encode reg/opcode.*/
    f_reg = decoded_modrm->reg_opcode;
    f_ext_R = (f_reg >> 3) & 0x01;
    f_ext_R_prim = (f_reg >> 4) & 0x01;
    f_reg &= 0x07;

    if (context->op_mode != FCML_OM_64_BIT && (f_ext_R || f_ext_X || f_ext_B ||
            f_ext_R_prim || f_ext_V_prim)) {
        return FCML_CEH_GEC_INVALID_ADDRESSING_FORM;
    }

    encoded_modrm->modrm = FCML_MODRM_ENC(f_mod, f_reg, f_rm);
    encoded_modrm->ext_R = f_ext_R;
    encoded_modrm->ext_R_prim = f_ext_R_prim;
    encoded_modrm->ext_X = f_ext_X;
    encoded_modrm->ext_B = f_ext_B;
    encoded_modrm->ext_V_prim = f_ext_V_prim;

    return FCML_CEH_GEC_NO_ERROR;
}

fcml_ceh_error fcml_fn_modrm_encode(fcml_st_modrm_encoder_context *context,
        const fcml_st_modrm *decoded_modrm,
        fcml_st_encoded_modrm *encoded_modrm) {

    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

    fcml_usize easa = context->effective_address_size;
    fcml_en_operating_mode op_mode = context->op_mode;

    const fcml_st_effective_address *effective_address =
            &(decoded_modrm->address.effective_address);

    /* Sanity check. */
    if (context->is_evex && context->input_size == FCML_DS_UNDEF &&
            context->vector_length == FCML_DS_UNDEF) {
        return FCML_CEH_GEC_INVALID_OPPERAND_SIZE;
    }

    /* Check if there is ambiguity.*/
    if (effective_address->base.size == FCML_DS_16
            || effective_address->index.size == FCML_DS_16) {
        if (op_mode == FCML_OM_64_BIT) {
            /* 16 bit addressing is not supported in 64 bit mode.*/
            return FCML_CEH_GEC_INVALID_ADDRESSING_FORM;
        }
        easa = FCML_DS_16;
    } else if (effective_address->base.size == FCML_DS_64
            || effective_address->index.size == FCML_DS_64) {
        if (op_mode == FCML_OM_16_BIT) {
            /* 64 bit addressing is not supported in 16 bit mode.*/
            return FCML_CEH_GEC_INVALID_ADDRESSING_FORM;
        }
        easa = FCML_DS_64;
    }

    context->chosen_effective_address_size = easa;

    if (easa == FCML_DS_16) {
        error = encode_16bit(context, decoded_modrm,
                encoded_modrm);
    } else if (easa == FCML_DS_32 || easa == FCML_DS_64) {
        error = encode_3264bit(context, decoded_modrm,
                encoded_modrm);
    } else {
        /* Unknown addressing mode.*/
        error = FCML_CEH_GEC_INVALID_OPERATING_MODE;
    }
    return error;
}

fcml_ceh_error fcml_fn_modrm_encode_rip_offset(fcml_st_memory_stream *stream,
        fcml_int64_t rip, fcml_uint8_t instruction_size,
        const fcml_st_encoded_modrm *encoded_modrm) {

    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

    if (encoded_modrm->is_rip) {
        fcml_int64_t rip_offset =
                (encoded_modrm->rip_address - instruction_size)
                        - (fcml_int64_t) rip;

        if (rip_offset < FCML_INT32_MIN || rip_offset > FCML_INT32_MAX) {
            error = FCML_CEH_GEC_VALUE_OUT_OF_RANGE;
        } else {

            fcml_st_integer integer;
            integer.int32 = (fcml_int32_t) rip_offset;
            integer.size = FCML_DS_32;

            /* Encodes and encodes displacement to given stream.*/
            error = fcml_fn_utils_encode_integer(stream, &integer);

        }
    } else {
        error = FCML_CEH_GEC_INVALID_INPUT;
    }

    return error;
}

fcml_ceh_error fcml_fn_modrm_calculate_effective_address_size(
        const fcml_st_modrm *decoded_modrm,
        fcml_flags *effective_address_size) {

    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

    /* Calculate EOSA.*/

    const fcml_st_address *address = &(decoded_modrm->address);
    const fcml_st_effective_address *effective_address =
            &(address->effective_address);

    fcml_flags easa = 0;

    fcml_st_register reg;
    if (effective_address->base.type) {
        reg = effective_address->base;
    } else {
        reg = effective_address->index;
    }
    if (reg.type) {
        switch (reg.size) {
        case FCML_DS_16:
        case FCML_DS_32:
        case FCML_DS_64:
            easa = reg.size >> 4;
            break;
        case FCML_DS_128:
        case FCML_DS_256:
        case FCML_DS_512:
            easa = FCML_EN_ASF_32 | FCML_EN_ASF_64;
            break;
        default:
            error = FCML_CEH_GEC_INVALID_OPERATING_MODE;
            break;
        }
    } else {
        /* Remember that -1 can be represented as int64 value, so displacement
         * nor offset size cannot be taken into account here.
         */
        easa = FCML_EN_ASF_ALL;
    }

    if (error) {
        return error;
    }

    /* Calculate EASA.*/

    *effective_address_size = easa;

    return error;
}

