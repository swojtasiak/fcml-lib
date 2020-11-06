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

#include "fcml_rend_utils.h"

#include <ctype.h>
#include <stdarg.h>

#include <fcml_types.h>
#include <fcml_common.h>
#include <fcml_dialect.h>

#include "fcml_env_int.h"
#include "fcml_ceh.h"
#include "fcml_stream.h"

static fcml_string rounding_modes[4] = {
        "{rn-sae}", "{rd-sae}",
        "{ru-sae}", "{rz-sae}"
};

void fcml_fn_rend_utils_format_printf(fcml_st_memory_stream *stream,
        const fcml_string format, ...) {

    /* We'll never reach this limit.*/
    fcml_char local_buffer[512];

    va_list arg_list;
    va_start(arg_list, format);

    fcml_fn_env_str_vsnprintf(local_buffer, sizeof(local_buffer), format,
            arg_list);
    int part_size = fcml_fn_env_str_strlen(local_buffer);
    if (part_size > stream->size - stream->offset - 1) {
        part_size = stream->size - stream->offset - 1;
    }

    fcml_fn_env_memory_copy(
            &(((fcml_char*) stream->base_address)[stream->offset]),
            local_buffer, part_size);

    stream->offset += part_size;
}

void fcml_fn_rend_utils_format_append_hex_byte(fcml_st_memory_stream *stream,
        fcml_uint8_t hex_byte) {
    fcml_fn_rend_utils_format_printf(stream, FCML_PRI_INT8_HEX, hex_byte);
}

void fcml_fn_rend_utils_format_append_code(const fcml_st_render_config *config,
        fcml_st_memory_stream *stream, const fcml_uint8_t *instrunction_code,
        const fcml_usize instruction_code_size) {
    fcml_int c_pad = 0;
    for (int i = 0; i < instruction_code_size; i++) {
        fcml_fn_rend_utils_format_append_hex_byte(stream, instrunction_code[i]);
    }
    if (config->render_flags & FCML_REND_FLAG_CODE_PADDING) {
        int padding = FCML_REND_DEFAULT_CODE_PADDING;
        if (config->prefered_code_padding > 0) {
            padding = config->prefered_code_padding;
        }
        c_pad = (padding - instruction_code_size) * 2;
        if (c_pad > 0) {
            fcml_fn_rend_utils_format_repeat_char(stream, ' ', c_pad);
        }
    }
    if (c_pad <= 0) {
        fcml_fn_rend_utils_format_append_str(stream, FCML_TEXT(" "));
    }
}

fcml_int fcml_fn_rend_utils_format_append_str_if(fcml_st_memory_stream *stream,
        const fcml_string string, fcml_bool condition) {
    if (condition) {
        return fcml_fn_rend_utils_format_append_str(stream, string);
    }
    return 0;
}

void fcml_fn_rend_utils_format_finish_str(fcml_st_memory_stream *stream) {
    int size = sizeof(FCML_TEXT("\0"));
    if (fcml_fn_stream_size(stream) >= size) {
        fcml_fn_env_str_strncpy(
                &(((fcml_char*) stream->base_address)[stream->offset]),
                FCML_TEXT("\0"), size);
        stream->offset += size;
    }
}

void fcml_fn_rend_utils_format_append_printf(fcml_st_memory_stream *stream,
        fcml_string format, ...) {
    fcml_char buffer[256];
    va_list args;
    va_start(args, format);
    fcml_fn_env_str_vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);
    fcml_fn_rend_utils_format_append_str(stream, buffer);
}

fcml_int fcml_fn_rend_utils_format_append_str(fcml_st_memory_stream *stream,
        const fcml_string source) {

    fcml_int source_size;
    if (source == NULL || (source_size = fcml_fn_env_str_strlen(source)) == 0) {
        return 0;
    }

    fcml_int destination_size = stream->size - stream->offset;
    fcml_int n =
            (destination_size < source_size) ? destination_size : source_size;
    if (n > 0) {
        fcml_fn_env_str_strncpy(
                &(((fcml_char*) stream->base_address)[stream->offset]), source,
                n);
        stream->offset += n;
    } else {
        n = 0;
    }

    return n;
}

fcml_int fcml_fn_rend_utils_format_append_str_padding(
        fcml_st_memory_stream *stream, const fcml_string source,
        fcml_int16_t padding) {

    fcml_usize str_len = fcml_fn_env_str_strlen(source);
    fcml_int len = 0;

    len += fcml_fn_rend_utils_format_append_str(stream, source);

    if (str_len < padding) {
        padding -= str_len;
        while (padding > 0) {
            len += fcml_fn_rend_utils_format_append_str(stream, " ");
        }
    }

    return len;
}

void fcml_fn_rend_utils_format_append_stream(
        fcml_st_memory_stream *destination_stream,
        const fcml_st_memory_stream *source_stream) {

    if (source_stream->offset == 0) {
        return;
    }

    fcml_int destination_size =
            destination_stream->size - destination_stream->offset;
    fcml_int n = (destination_size < source_stream->offset) ?
                    destination_size : source_stream->offset;
    if (n > 0) {
        fcml_fn_env_str_strncpy(
                (fcml_string) &(((fcml_char*) destination_stream->base_address)[destination_stream->offset]),
                (fcml_string) source_stream->base_address, n);
        destination_stream->offset += n;
    }
}

fcml_ceh_error fcml_fn_rend_utils_format_append_integer(
        fcml_string patterns[6][4], fcml_st_memory_stream *stream,
        const fcml_st_integer *integer, fcml_bool is_hex,
        fcml_bool remove_leading_zeros) {

    fcml_string *format;

    fcml_int delta = integer->is_signed ? 0 : 1;

    if (is_hex) {
        if (remove_leading_zeros) {
            format = &(patterns[4 + delta][0]);
        } else {
            format = &(patterns[2 + delta][0]);
        }
    } else {
        format = &(patterns[0 + delta][0]);
    }

    fcml_char local_buffer[32];

    switch (integer->size) {
    case 8:
        fcml_fn_env_str_snprintf(local_buffer, sizeof(local_buffer), format[0],
                integer->is_signed & !is_hex ?
                        integer->int8 : (fcml_uint8_t) integer->int8);
        break;
    case 16:
        fcml_fn_env_str_snprintf(local_buffer, sizeof(local_buffer), format[1],
                integer->is_signed & !is_hex ?
                        integer->int16 : (fcml_uint16_t) integer->int16);
        break;
    case 32:
        fcml_fn_env_str_snprintf(local_buffer, sizeof(local_buffer), format[2],
                integer->is_signed & !is_hex ?
                        integer->int32 : (fcml_uint32_t) integer->int32);
        break;
    case 64:
        fcml_fn_env_str_snprintf(local_buffer, sizeof(local_buffer), format[3],
                integer->is_signed & !is_hex ?
                        integer->int64 : (fcml_uint64_t) integer->int64);
        break;
    default:
        return FCML_CEH_GEC_INVALID_INPUT;
    }

    /* Currently this logic desn't collide with AT&T dialect, so parameterization is not needed.*/
    if (is_hex && !isdigit(local_buffer[0])) {
        fcml_fn_rend_utils_format_append_str(stream, "0");
    }

    fcml_fn_rend_utils_format_append_str(stream, (fcml_string) local_buffer);

    return FCML_CEH_GEC_NO_ERROR;
}

void fcml_fn_rend_utils_format_append_reg(
        const fcml_st_dialect_context_int *dialect_context,
        fcml_st_memory_stream *output_stream, const fcml_st_register *reg,
        fcml_bool is_rex) {
    fcml_char printable_reg[64];
    dialect_context->get_register(reg, printable_reg, sizeof(printable_reg),
            is_rex);
    fcml_fn_rend_utils_format_append_str(output_stream, printable_reg);
}

void fcml_fn_rend_utils_format_append_operand_decorators(
        const fcml_st_dialect_context_int *dialect_context,
        fcml_st_memory_stream *output_stream,
        const fcml_st_operand_decorators *decorators) {

    /* Operand mask register attribute. */
    if (decorators->operand_mask_reg.type != FCML_REG_UNDEFINED) {
        fcml_fn_rend_utils_format_append_str(output_stream, "{");
        fcml_fn_rend_utils_format_append_reg(dialect_context, output_stream,
                &(decorators->operand_mask_reg), FCML_FALSE);
        fcml_fn_rend_utils_format_append_str(output_stream, "}");
    }

    /* Broadcasting. */
    if (decorators->bcast.is_not_null) {
        fcml_fn_rend_utils_format_append_printf(output_stream, "{1to%d}",
                (fcml_int32_t) decorators->bcast.value);
    }

    /* Zeroing. */
    if (decorators->z) {
        fcml_fn_rend_utils_format_append_str(output_stream, "{z}");
    }

    /* Embedded rounding control. */
    if (decorators->er.is_not_null) {
        fcml_fn_rend_utils_format_append_str(output_stream,
                rounding_modes[decorators->er.value]);
    }

    /* Indicates support for SAE (Suppress All Exceptions). */
    if (decorators->sae) {
        fcml_fn_rend_utils_format_append_str(output_stream, "{sae}");
    }
}

fcml_int fcml_fn_rend_utils_padding(fcml_st_memory_stream *output_stream,
        fcml_int len, fcml_int padding, fcml_int default_padding) {
    if (padding <= 0) {
        padding = default_padding;
    }
    return fcml_fn_rend_utils_format_repeat_char(output_stream, ' ',
            padding - len);
}

fcml_int fcml_fn_rend_utils_format_repeat_char(fcml_st_memory_stream *stream,
        fcml_char character, fcml_int repeats) {
    if (repeats > 0) {
        fcml_int size = fcml_fn_stream_size(stream);
        if (size < repeats) {
            repeats = size;
        }
        if (repeats > 0) {
            fcml_char *buffer =
                    &(((fcml_char*) stream->base_address)[stream->offset]);
            stream->offset += repeats;
            fcml_int counter = repeats;
            while (counter > 0) {
                buffer[--counter] = character;
            }
        }
    } else {
        repeats = 0;
    }
    return repeats;
}

fcml_int fcml_ifn_rend_utils_print_prefixes(
        fcml_st_memory_stream *output_stream,
        const fcml_st_prefixes_details *prefixes, fcml_uint32_t flags) {
    fcml_int len = 0;
    if (prefixes->is_xacquire) {
        len += fcml_fn_rend_utils_format_append_str(output_stream,
                FCML_TEXT("xacquire "));
    }
    if (prefixes->is_xrelease) {
        len += fcml_fn_rend_utils_format_append_str(output_stream,
                FCML_TEXT("xrelease "));
    }
    if (prefixes->is_lock) {
        len += fcml_fn_rend_utils_format_append_str(output_stream,
                FCML_TEXT("lock "));
    }
    if (prefixes->is_branch) {
        len += fcml_fn_rend_utils_format_append_str(output_stream,
                FCML_TEXT("branch "));
    }
    if (prefixes->is_nobranch) {
        len += fcml_fn_rend_utils_format_append_str(output_stream,
                FCML_TEXT("nobranch "));
    }
    if (prefixes->is_rep) {
        if (flags & FCML_REND_FLAG_REP_PREFIX_GROUP_1) {
            len += fcml_fn_rend_utils_format_append_str(output_stream,
                    FCML_TEXT("repe "));
        } else if (flags & FCML_REND_FLAG_REP_PREFIX_GROUP_2) {
            len += fcml_fn_rend_utils_format_append_str(output_stream,
                    FCML_TEXT("repz "));
        } else {
            len += fcml_fn_rend_utils_format_append_str(output_stream,
                    FCML_TEXT("rep "));
        }
    }
    if (prefixes->is_repne) {
        if (flags & FCML_REND_FLAG_REP_PREFIX_GROUP_2) {
            len += fcml_fn_rend_utils_format_append_str(output_stream,
                    FCML_TEXT("repnz "));
        } else {
            len += fcml_fn_rend_utils_format_append_str(output_stream,
                    FCML_TEXT("repne "));
        }
    }
    return len;
}

fcml_bool fcml_fn_rend_utils_render_operand_separator(
        const fcml_st_render_config *config,
        fcml_st_memory_stream *output_stream, fcml_int mnemonic_length,
        fcml_bool first_operand) {
    if (!first_operand) {
        fcml_fn_rend_utils_format_append_str(output_stream, FCML_TEXT(","));
    } else {
        /* Deferred mnemonic part padding. */
        fcml_int padding_len = 0;
        if (config->render_flags & FCML_REND_FLAG_MNEMONIC_PADDING) {
            padding_len = fcml_fn_rend_utils_padding(output_stream,
                    mnemonic_length, config->prefered_mnemonic_padding,
                    FCML_REND_DEFAULT_MNEMONIC_PADDING);
        }
        if (padding_len <= 0) {
            fcml_fn_rend_utils_format_append_str(output_stream, FCML_TEXT(" "));
        }
        first_operand = FCML_FALSE;
    }
    return FCML_FALSE;
}
