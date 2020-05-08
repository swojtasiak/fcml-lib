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

/* There is a bit of code duplication between GAS and Intel instruction renderers.
 * It evaluated up to this point due to historical reasons and it will be probably fixed in
 * the near future by providing one generic customizable rendering template as a base for
 * instruction renderers.
 */

#include "fcml_gas_rend.h"

#include <fcml_types.h>
#include <fcml_common.h>
#include <fcml_dialect.h>
#include <fcml_renderer.h>
#include <fcml_disassembler.h>

#include "fcml_common_dialect.h"
#include "fcml_ceh.h"
#include "fcml_common_utils.h"
#include "fcml_dialect_int.h"
#include "fcml_env_int.h"
#include "fcml_rend_utils.h"
#include "fcml_stream.h"
#include "fcml_utils.h"

#define FCML_REND_LOCAL_BUFFER_SIZE 512

static fcml_string integer_formats_gas[6][4] = {
        /* Signed integer values.*/
        {
                FCML_PRI_INT8_DEC, FCML_PRI_INT16_DEC, FCML_PRI_INT32_DEC,
                FCML_PRI_INT64_DEC
        },
        /* Unsigned integer values.*/
        {
                FCML_PRI_UINT8_DEC, FCML_PRI_UINT16_DEC, FCML_PRI_UINT32_DEC,
                FCML_PRI_UINT64_DEC
        },
        /* Signed hex values.*/
        {
                FCML_TEXT("0x") FCML_PRI_INT8_HEX, FCML_TEXT("0x") FCML_PRI_INT16_HEX,
                FCML_TEXT("0x") FCML_PRI_INT32_HEX, FCML_TEXT("0x") FCML_PRI_INT64_HEX
        },
        /* Unsigned hex values.*/
        {
                FCML_TEXT("0x") FCML_PRI_INT8_HEX, FCML_TEXT("0x") FCML_PRI_INT16_HEX,
                FCML_TEXT("0x") FCML_PRI_INT32_HEX,FCML_TEXT("0x") FCML_PRI_INT64_HEX
        },
        /* Signed hex values without leading zeros. */
        {
                FCML_TEXT("0x") FCML_PRI_INT8_HEX_NO_ZEROS,
                FCML_TEXT("0x") FCML_PRI_INT16_HEX_NO_ZEROS,
                FCML_TEXT("0x") FCML_PRI_INT32_HEX_NO_ZEROS,
                FCML_TEXT("0x") FCML_PRI_INT64_HEX_NO_ZEROS
        },
        /* Unsigned hex values without leading zeros. */
        {
                FCML_TEXT("0x") FCML_PRI_INT8_HEX_NO_ZEROS,
                FCML_TEXT("0x") FCML_PRI_INT16_HEX_NO_ZEROS,
                FCML_TEXT("0x") FCML_PRI_INT32_HEX_NO_ZEROS,
                FCML_TEXT("0x") FCML_PRI_INT64_HEX_NO_ZEROS
        }
};

static fcml_ceh_error operand_renderer_imm(
        const fcml_st_render_config *config,
        fcml_st_memory_stream *output_stream,
        const fcml_st_operand *operand) {

    const fcml_st_integer *immediate = &(operand->immediate);

    fcml_fn_rend_utils_format_append_str(output_stream, FCML_TEXT("$"));

    return fcml_fn_rend_utils_format_append_integer(
            integer_formats_gas, output_stream, immediate,
            config->render_flags & FCML_REND_FLAG_HEX_IMM,
            config->render_flags & FCML_REND_FLAG_REMOVE_LEADING_ZEROS);
}

static inline fcml_ceh_error operand_renderer_reg(
        const fcml_st_dialect_context_int *dialect_context,
        fcml_st_memory_stream *output_stream,
        const fcml_st_disassembler_result *result,
        const fcml_st_operand *operand) {
    fcml_fn_rend_utils_format_append_reg(dialect_context, output_stream,
            &(operand->reg),
            result->instruction_details.prefixes_details.is_rex);
    return FCML_CEH_GEC_NO_ERROR;
}

static fcml_ceh_error operand_renderer_address(
        const fcml_st_render_config *config,
        const fcml_st_dialect_context_int *dialect_context,
        fcml_st_memory_stream *output_stream,
        const fcml_st_disassembler_result *result,
        const fcml_st_operand *operand) {

    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
    const fcml_st_address *address = &(operand->address);
    const fcml_st_prefixes_details *prefixes =
            &(result->instruction_details.prefixes_details);
    fcml_hints hints = operand->hints;

    if (hints & FCML_OP_HINT_DISPLACEMENT_RELATIVE_ADDRESS) {

        fcml_st_integer integer;
        fcml_ceh_error error = fcml_fn_utils_offset_to_integer(
                &(address->offset), &integer);
        if (error) {
            return error;
        }

        error = fcml_fn_rend_utils_format_append_integer(
                integer_formats_gas, output_stream,
                &integer, FCML_TRUE,
                config->render_flags & FCML_REND_FLAG_REMOVE_LEADING_ZEROS);

        return error;
    }

    if (!address->segment_selector.is_default_reg
            || (config->render_flags & FCML_REND_FLAG_RENDER_DEFAULT_SEG)) {
        fcml_fn_rend_utils_format_append_reg(dialect_context, output_stream,
                &(address->segment_selector.segment_selector),
                prefixes->is_rex);
        fcml_fn_rend_utils_format_append_str(output_stream, FCML_TEXT(":"));
    }

    const fcml_st_effective_address *effective_address =
            &(address->effective_address);

    if (result->instruction.hints & FCML_HINT_INDIRECT_POINTER) {
        fcml_fn_rend_utils_format_append_str(output_stream, FCML_TEXT("*"));
    }

    if (address->address_form == FCML_AF_COMBINED) {

        /* Displacement.*/
        if (effective_address->displacement.size > 0) {

            error = fcml_fn_rend_utils_format_append_integer(
                    integer_formats_gas, output_stream,
                    &(effective_address->displacement),
                    config->render_flags & FCML_REND_FLAG_HEX_DISPLACEMENT,
                    config->render_flags & FCML_REND_FLAG_REMOVE_LEADING_ZEROS);
            if (error) {
                return error;
            }
        }

        fcml_fn_rend_utils_format_append_str(output_stream, FCML_TEXT("("));

        /* Append base register.*/
        if (!is_reg_undef(&(effective_address->base))) {
            fcml_fn_rend_utils_format_append_reg(dialect_context, output_stream,
                    &(effective_address->base), prefixes->is_rex);
        }

        /* Append index register.*/
        if (!is_reg_undef(&(effective_address->index))) {
            fcml_fn_rend_utils_format_append_str(output_stream, FCML_TEXT(","));
            fcml_fn_rend_utils_format_append_reg(dialect_context, output_stream,
                    &(effective_address->index), prefixes->is_rex);
        }

        /* Append scale.*/
        if (effective_address->scale_factor > 0) {

            fcml_fn_rend_utils_format_append_str(output_stream, FCML_TEXT(","));

            fcml_st_integer scale_value = { 0 };
            scale_value.is_signed = FCML_FALSE;
            scale_value.size = 8;
            scale_value.int8 = (fcml_int8_t) effective_address->scale_factor;

            fcml_fn_rend_utils_format_append_integer(
                    integer_formats_gas, output_stream,
                    &scale_value, FCML_FALSE, FCML_FALSE);
        }

        fcml_fn_rend_utils_format_append_str(output_stream, FCML_TEXT(")"));

    } else {

        /* Absolute offset or RIP.*/
        if (!error) {

            /* For RIP base register is set to IP. */
            fcml_st_integer integer;
            if (address->effective_address.base.type == FCML_REG_IP) {
                /* IP relative addressing.*/
                error = fcml_fn_rend_utils_format_append_integer(
                        integer_formats_gas, output_stream,
                        &(address->effective_address.displacement), FCML_TRUE,
                        config->render_flags
                                & FCML_REND_FLAG_REMOVE_LEADING_ZEROS);
                if (!error) {
                    fcml_fn_rend_utils_format_append_str(output_stream,
                            FCML_TEXT("("));
                    fcml_fn_rend_utils_format_append_reg(dialect_context,
                            output_stream, &(fcml_reg_RIP), FCML_FALSE);
                    fcml_fn_rend_utils_format_append_str(output_stream,
                            FCML_TEXT(")"));
                }
            } else {
                /* Absolute offset.*/
                fcml_ceh_error error = fcml_fn_utils_offset_to_integer(
                        &(address->offset), &integer);
                if (error) {
                    return error;
                }
                error = fcml_fn_rend_utils_format_append_integer(
                        integer_formats_gas, output_stream,
                        &integer, FCML_TRUE,
                        config->render_flags
                                & FCML_REND_FLAG_REMOVE_LEADING_ZEROS);
            }
        }
    }

    return error;
}

static fcml_ceh_error operand_renderer_far_pointer(
        const fcml_st_render_config *config,
        fcml_st_memory_stream *output_stream,
        const fcml_st_operand *operand) {

    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
    fcml_st_integer integer = { 0 };

    integer.is_signed = FCML_TRUE;
    integer.size = 16;
    integer.int16 = operand->far_pointer.segment;

    fcml_fn_rend_utils_format_append_str(output_stream, FCML_TEXT("$"));
    fcml_fn_rend_utils_format_append_integer(integer_formats_gas, output_stream,
            &integer, FCML_TRUE,
            config->render_flags & FCML_REND_FLAG_REMOVE_LEADING_ZEROS);

    fcml_fn_rend_utils_format_append_str(output_stream, FCML_TEXT(","));

    integer.size = operand->far_pointer.offset_size;
    switch (integer.size) {
    case FCML_DS_16:
        integer.int16 = operand->far_pointer.offset16;
        break;
    case FCML_DS_32:
        integer.int32 = operand->far_pointer.offset32;
        break;
    }

    fcml_fn_rend_utils_format_append_str(output_stream, FCML_TEXT("$"));
    fcml_fn_rend_utils_format_append_integer(integer_formats_gas, output_stream,
            &integer, FCML_TRUE,
            config->render_flags & FCML_REND_FLAG_REMOVE_LEADING_ZEROS);

    return error;
}

static fcml_ceh_error print_operand(const fcml_st_render_config *config,
        const fcml_st_dialect_context_int *dialect_context,
        fcml_st_memory_stream *output_stream,
        const fcml_st_disassembler_result *result, fcml_int operand_index) {

    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
    const fcml_st_operand *operand =
            &(result->instruction.operands[operand_index]);

    switch (operand->type) {
    case FCML_OT_IMMEDIATE:
        error = operand_renderer_imm(config, output_stream, operand);
        break;
    case FCML_OT_FAR_POINTER:
        error = operand_renderer_far_pointer(config, output_stream, operand);
        break;
    case FCML_OT_ADDRESS:
        error = operand_renderer_address(config, dialect_context,
                output_stream, result, operand);
        break;
    case FCML_OT_REGISTER:
        error = operand_renderer_reg(dialect_context, output_stream,
                result, operand);
        break;
    case FCML_OT_VIRTUAL:
        break;
    case FCML_OT_NONE:
        break;
    default:
        error = FCML_CEH_GEC_INVALID_INPUT;
    }

    /* Print operand attributes just after the operand. */
    if (!error) {
        fcml_fn_rend_utils_format_append_operand_decorators(dialect_context,
                output_stream, &(operand->decorators));
    }

    return error;
}

fcml_ceh_error fcml_fn_rend_render_instruction_gas(
        const fcml_st_dialect *dialect_context,
        const fcml_st_render_config *config,
        fcml_st_memory_stream *output_stream,
        const fcml_st_disassembler_result *result) {

    fcml_st_dialect_context_int *dialect_context_int =
            (fcml_st_dialect_context_int*) dialect_context;
    fcml_char local_buffer[FCML_REND_LOCAL_BUFFER_SIZE] = { 0 };
    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
    fcml_uint32_t render_flags = config->render_flags;

    /* Local stream.*/
    fcml_st_memory_stream local_stream;
    local_stream.base_address = local_buffer;
    local_stream.size = sizeof(local_buffer);
    local_stream.offset = 0;

    /* Instruction code. */
    if (render_flags & FCML_REND_FLAG_RENDER_CODE) {
        fcml_fn_rend_utils_format_append_code(config, output_stream,
                result->instruction_details.instruction_code,
                result->instruction_details.instruction_size);
    }

    fcml_int len = 0;

    /* Instruction prefixes like LOCK. */
    len += fcml_ifn_rend_utils_print_prefixes(output_stream,
            &(result->instruction_details.prefixes_details), render_flags);

    /* Mnemonic. */
    len += fcml_fn_rend_utils_format_append_str(output_stream,
            result->instruction.mnemonic);

    /* Short form, so operands should be ignored. */
    if (result->instruction_details.is_shortcut) {
        return error;
    }

    /* Add all operands. */
    fcml_bool first_render = FCML_TRUE;
    fcml_int i;
    for (i = 0; i < FCML_OPERANDS_COUNT; i++) {
        if (result->instruction.operands[i].type != FCML_OT_NONE) {
            error = print_operand(config, dialect_context_int,
                    &local_stream, result, i);
            if (!error) {
                first_render = fcml_fn_rend_utils_render_operand_separator(
                        config, output_stream, len, first_render);
                fcml_fn_rend_utils_format_append_stream(output_stream,
                        &local_stream);
                fcml_fn_stream_clean(&local_stream);
            } else {
                break;
            }
        } else {
            break;
        }
    }

    fcml_fn_rend_utils_format_finish_str(output_stream);

    return error;
}
