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

#include <fcml_types.h>
#include <fcml_errors.h>

#include "fcml_utils.h"
#include "fcml_coll.h"
#include "fcml_trace.h"
#include "fcml_messages.h"

fcml_ceh_error fcml_fn_utils_conv_int64_to_int(const fcml_uint64_t src,
        fcml_bool is_src_signed, fcml_st_integer *dest,
        fcml_en_utils_size_flags filter) {

    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

    if (is_src_signed) {
        fcml_int64_t imm = (fcml_int64_t) src;
        if ((filter & FCML_ENUSF_8) && imm <= FCML_INT8_MAX
                && imm >= FCML_INT8_MIN) {
            dest->int8 = (fcml_int8_t) imm;
            dest->size = FCML_DS_8;
        } else if ((filter & FCML_ENUSF_16) && imm <= FCML_INT16_MAX
                && imm >= FCML_INT16_MIN) {
            dest->int16 = (fcml_int16_t) imm;
            dest->size = FCML_DS_16;
        } else if ((filter & FCML_ENUSF_32) && imm <= FCML_INT32_MAX
                && imm >= FCML_INT32_MIN) {
            dest->int32 = (fcml_int32_t) imm;
            dest->size = FCML_DS_32;
        } else {
            if (filter & FCML_ENUSF_64) {
                dest->int64 = imm;
                dest->size = FCML_DS_64;
            } else {
                error = FCML_CEH_GEC_VALUE_OUT_OF_RANGE;
            }
        }
    } else {
        if ((filter & FCML_ENUSF_8) && (src <= FCML_UINT8_MAX)) {
            dest->int8 = (fcml_uint8_t) src;
            dest->size = FCML_DS_8;
        } else if ((filter & FCML_ENUSF_16) && (src <= FCML_UINT16_MAX)) {
            dest->int16 = (fcml_uint16_t) src;
            dest->size = FCML_DS_16;
        } else if ((filter & FCML_ENUSF_32) && (src <= FCML_UINT32_MAX)) {
            dest->int32 = (fcml_uint32_t) src;
            dest->size = FCML_DS_32;
        } else if (filter & FCML_ENUSF_64) {
            dest->int64 = src;
            dest->size = FCML_DS_64;
        } else {
            error = FCML_CEH_GEC_VALUE_OUT_OF_RANGE;
        }
    }

    dest->is_signed = is_src_signed;

    return error;
}

fcml_ceh_error fcml_fn_utils_conv_int_to_int(const fcml_st_integer *src,
        fcml_st_integer *dest, fcml_usize expected_src_size,
        fcml_usize dest_size) {

    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

    /* Convert given source immediate value to expected one.*/
    fcml_st_integer expected = { 0 };

    expected.size = expected_src_size;
    expected.is_signed = src->is_signed;

    if (src->size != expected_src_size) {
        switch (expected_src_size) {
        case FCML_DS_8:
            error = fcml_fn_utils_conv_int_to_int8(src, &(expected.int8));
            break;
        case FCML_DS_16:
            error = fcml_fn_utils_conv_int_to_int16(src, &(expected.int16));
            break;
        case FCML_DS_32:
            error = fcml_fn_utils_conv_int_to_int32(src, &(expected.int32));
            break;
        case FCML_DS_64:
            error = fcml_fn_utils_conv_int_to_int64(src, &(expected.int64));
            break;
        }
    } else {
        expected = *src;
    }

    if (!error) {
        /* Convert expected value to destination one.*/
        switch (dest_size) {
        case FCML_DS_8:
            error = fcml_fn_utils_conv_int_to_int8(&expected, &(dest->int8));
            break;
        case FCML_DS_16:
            error = fcml_fn_utils_conv_int_to_int16(&expected, &(dest->int16));
            break;
        case FCML_DS_32:
            error = fcml_fn_utils_conv_int_to_int32(&expected, &(dest->int32));
            break;
        case FCML_DS_64:
            error = fcml_fn_utils_conv_int_to_int64(&expected, &(dest->int64));
            break;
        }
        if (!error) {
            dest->size = dest_size;
            dest->is_signed = expected.is_signed;
        }
    }

    return error;
}

fcml_ceh_error fcml_fn_utils_conv_int_to_uint8(const fcml_st_integer *src,
        fcml_uint8_t *dest) {
    switch (src->size) {
    case FCML_DS_8:
        /* In this case we doesn't care what is in IMM, because no conversion is needed.*/
        *dest = src->int8;
        break;
    case FCML_DS_16:
        if (src->is_signed) {
            if (src->int16 > FCML_UINT8_MAX || src->int16 < 0) {
                return FCML_CEH_GEC_VALUE_OUT_OF_RANGE;
            }
            *dest = (fcml_uint8_t) (fcml_int16_t) src->int16;
        } else {
            if ((fcml_uint16_t) src->int16 > FCML_UINT8_MAX) {
                return FCML_CEH_GEC_VALUE_OUT_OF_RANGE;
            }
            *dest = (fcml_uint8_t) src->int16;
        }
        break;
    case FCML_DS_32:
        if (src->is_signed) {
            if (src->int32 > FCML_UINT8_MAX || src->int32 < 0) {
                return FCML_CEH_GEC_VALUE_OUT_OF_RANGE;
            }
            *dest = (fcml_uint8_t) (fcml_int32_t) src->int32;
        } else {
            if ((fcml_uint32_t) src->int32 > FCML_UINT8_MAX) {
                return FCML_CEH_GEC_VALUE_OUT_OF_RANGE;
            }
            *dest = (fcml_uint8_t) src->int32;
        }
        break;
    case FCML_DS_64:
        if (src->is_signed) {
            if (src->int64 > FCML_UINT8_MAX || src->int64 < 0) {
                return FCML_CEH_GEC_VALUE_OUT_OF_RANGE;
            }
            *dest = (fcml_uint8_t) (fcml_int64_t) src->int64;
        } else {
            if ((fcml_uint64_t) src->int64 > FCML_UINT8_MAX) {
                return FCML_CEH_GEC_VALUE_OUT_OF_RANGE;
            }
            *dest = (fcml_uint8_t) src->int64;
        }
        break;
    default:
        return FCML_CEH_GEC_VALUE_OUT_OF_RANGE;
    }
    return FCML_CEH_GEC_NO_ERROR;
}

fcml_ceh_error fcml_fn_utils_conv_int_to_uint16(const fcml_st_integer *src,
        fcml_uint16_t *dest) {
    switch (src->size) {
    case FCML_DS_8:
        if (src->is_signed) {
            *dest = (fcml_uint16_t) src->int8;
        } else {
            *dest = (fcml_uint16_t) (fcml_uint8_t) src->int8;
        }
        break;
    case FCML_DS_16:
        *dest = (fcml_uint16_t) src->int16;
        break;
    case FCML_DS_32:
        if (src->is_signed) {
            if (src->int32 > FCML_UINT16_MAX || src->int32 < 0) {
                return FCML_CEH_GEC_VALUE_OUT_OF_RANGE;
            }
            *dest = (fcml_uint16_t) src->int32;
        } else {
            if ((fcml_uint32_t) src->int32 > FCML_UINT16_MAX) {
                return FCML_CEH_GEC_VALUE_OUT_OF_RANGE;
            }
            *dest = (fcml_uint16_t) src->int32;
        }
        break;
    case FCML_DS_64:
        if (src->is_signed) {
            if (src->int64 > FCML_UINT16_MAX || src->int64 < 0) {
                return FCML_CEH_GEC_VALUE_OUT_OF_RANGE;
            }
            *dest = (fcml_uint16_t) src->int64;
        } else {
            if ((fcml_uint64_t) src->int64 > FCML_UINT16_MAX) {
                return FCML_CEH_GEC_VALUE_OUT_OF_RANGE;
            }
            *dest = (fcml_uint16_t) src->int64;
        }
        break;
    default:
        return FCML_CEH_GEC_VALUE_OUT_OF_RANGE;
    }
    return FCML_CEH_GEC_NO_ERROR;
}

fcml_ceh_error fcml_fn_utils_conv_int_to_uint32(const fcml_st_integer *src,
        fcml_uint32_t *dest) {
    switch (src->size) {
    case FCML_DS_8:
        if (src->is_signed) {
            *dest = (fcml_uint32_t) src->int8;
        } else {
            *dest = (fcml_uint32_t) (fcml_uint8_t) src->int8;
        }
        break;
    case FCML_DS_16:
        if (src->is_signed) {
            *dest = (fcml_uint32_t) src->int16;
        } else {
            *dest = (fcml_uint32_t) (fcml_uint16_t) src->int16;
        }
        break;
    case FCML_DS_32:
        *dest = (fcml_uint32_t) src->int32;
        break;
    case FCML_DS_64:
        if (src->is_signed) {
            if (src->int64 > FCML_UINT32_MAX || src->int64 < 0) {
                return FCML_CEH_GEC_VALUE_OUT_OF_RANGE;
            }
            *dest = (fcml_uint32_t) src->int16;
        } else {
            if ((fcml_uint64_t) src->int64 > FCML_UINT32_MAX) {
                return FCML_CEH_GEC_VALUE_OUT_OF_RANGE;
            }
            *dest = (fcml_uint32_t) src->int64;
        }
        break;
    default:
        return FCML_CEH_GEC_VALUE_OUT_OF_RANGE;
    }
    return FCML_CEH_GEC_NO_ERROR;
}

fcml_ceh_error fcml_fn_utils_conv_int_to_uint64(const fcml_st_integer *src,
        fcml_uint64_t *dest) {
    switch (src->size) {
    case FCML_DS_8:
        if (src->is_signed) {
            *dest = (fcml_uint64_t) src->int8;
        } else {
            *dest = (fcml_uint64_t) (fcml_uint8_t) src->int8;
        }
        break;
    case FCML_DS_16:
        if (src->is_signed) {
            *dest = (fcml_uint64_t) src->int16;
        } else {
            *dest = (fcml_uint64_t) (fcml_uint16_t) src->int16;
        }
        break;
    case FCML_DS_32:
        if (src->is_signed) {
            *dest = (fcml_uint64_t) src->int32;
        } else {
            *dest = (fcml_uint64_t) (fcml_uint32_t) src->int32;
        }
        break;
    case FCML_DS_64:
        *dest = (fcml_uint64_t) src->int64;
        break;
    default:
        return FCML_CEH_GEC_VALUE_OUT_OF_RANGE;
    }
    return FCML_CEH_GEC_NO_ERROR;
}

fcml_ceh_error fcml_fn_utils_conv_int_to_int8(const fcml_st_integer *src,
        fcml_int8_t *dest) {
    switch (src->size) {
    case FCML_DS_8:
        *dest = (fcml_int8_t) src->int8;
        break;
    case FCML_DS_16:
        if (src->is_signed) {
            if (src->int16 < FCML_INT8_MIN || src->int16 > FCML_INT8_MAX) {
                return FCML_CEH_GEC_VALUE_OUT_OF_RANGE;
            }
            *dest = (fcml_int8_t) src->int16;
        } else {
            if ((fcml_uint16_t) src->int16 > FCML_UINT8_MAX) {
                return FCML_CEH_GEC_VALUE_OUT_OF_RANGE;
            }
            *dest = (fcml_int8_t) (fcml_uint16_t) src->int16;
        }
        break;
    case FCML_DS_32:
        if (src->is_signed) {
            if (src->int32 < FCML_INT8_MIN || src->int32 > FCML_INT8_MAX) {
                return FCML_CEH_GEC_VALUE_OUT_OF_RANGE;
            }
            *dest = (fcml_int8_t) src->int32;
        } else {
            if ((fcml_uint32_t) src->int32 > FCML_INT8_MAX) {
                return FCML_CEH_GEC_VALUE_OUT_OF_RANGE;
            }
            *dest = (fcml_int8_t) (fcml_uint32_t) src->int32;
        }
        break;
    case FCML_DS_64:
        if (src->is_signed) {
            if ((fcml_int64_t) src->int64 < FCML_INT8_MIN
                    || (fcml_int64_t) src->int64 > FCML_INT8_MAX) {
                return FCML_CEH_GEC_VALUE_OUT_OF_RANGE;
            }
            *dest = (fcml_int8_t) src->int64;
        } else {
            if ((fcml_uint64_t) src->int64 > FCML_INT8_MAX) {
                return FCML_CEH_GEC_VALUE_OUT_OF_RANGE;
            }
            *dest = (fcml_int8_t) (fcml_uint64_t) src->int64;
        }
        break;
    default:
        return FCML_CEH_GEC_VALUE_OUT_OF_RANGE;
    }
    return FCML_CEH_GEC_NO_ERROR;
}

fcml_ceh_error fcml_fn_utils_conv_int_to_int16(const fcml_st_integer *src,
        fcml_int16_t *dest) {
    switch (src->size) {
    case FCML_DS_8:
        *dest = src->is_signed ?
                (fcml_int16_t) src->int8 :
                (fcml_int16_t) (fcml_uint8_t) src->int8;
        break;
    case FCML_DS_16:
        *dest = src->int16;
        break;
    case FCML_DS_32:
        if (src->is_signed) {
            if (src->int32 < FCML_INT16_MIN || src->int32 > FCML_INT16_MAX) {
                return FCML_CEH_GEC_VALUE_OUT_OF_RANGE;
            }
            *dest = (fcml_int16_t) src->int32;
        } else {
            if ((fcml_uint32_t) src->int32 > FCML_INT16_MAX) {
                return FCML_CEH_GEC_VALUE_OUT_OF_RANGE;
            }
            *dest = (fcml_int16_t) (fcml_uint32_t) src->int32;
        }
        break;
    case FCML_DS_64:
        if (src->is_signed) {
            if (src->int64 < FCML_INT16_MIN || src->int64 > FCML_INT16_MAX) {
                return FCML_CEH_GEC_VALUE_OUT_OF_RANGE;
            }
            *dest = (fcml_int16_t) src->int64;
        } else {
            if ((fcml_uint64_t) src->int64 > FCML_INT16_MAX) {
                return FCML_CEH_GEC_VALUE_OUT_OF_RANGE;
            }
            *dest = (fcml_int16_t) (fcml_uint64_t) src->int64;
        }
        break;
    default:
        return FCML_CEH_GEC_VALUE_OUT_OF_RANGE;
    }
    return FCML_CEH_GEC_NO_ERROR;
}

fcml_ceh_error fcml_fn_utils_conv_int_to_int32(const fcml_st_integer *src,
        fcml_int32_t *dest) {
    switch (src->size) {
    case FCML_DS_8:
        *dest = src->is_signed ?
                (fcml_int32_t) src->int8 :
                (fcml_int32_t) (fcml_uint8_t) src->int8;
        break;
    case FCML_DS_16:
        *dest = src->is_signed ?
                (fcml_int32_t) src->int16 :
                (fcml_int32_t) (fcml_uint16_t) src->int16;
        break;
    case FCML_DS_32:
        *dest = src->int32;
        break;
    case FCML_DS_64:
        if (src->is_signed) {
            if (src->int64 < FCML_INT32_MIN || src->int64 > FCML_INT32_MAX) {
                return FCML_CEH_GEC_VALUE_OUT_OF_RANGE;
            }
            *dest = (fcml_int32_t) src->int64;
        } else {
            if ((fcml_uint64_t) src->int64 > FCML_INT32_MAX) {
                return FCML_CEH_GEC_VALUE_OUT_OF_RANGE;
            }
            *dest = (fcml_int32_t) (fcml_uint64_t) src->int64;
        }
        break;
    default:
        return FCML_CEH_GEC_VALUE_OUT_OF_RANGE;
    }
    return FCML_CEH_GEC_NO_ERROR;
}

fcml_ceh_error fcml_fn_utils_conv_int_to_int64(const fcml_st_integer *src,
        fcml_int64_t *dest) {
    switch (src->size) {
    case FCML_DS_8:
        *dest = src->is_signed ?
                (fcml_int64_t) src->int8 :
                (fcml_int64_t) (fcml_uint8_t) src->int8;
        break;
    case FCML_DS_16:
        *dest = src->is_signed ?
                (fcml_int64_t) src->int16 :
                (fcml_int64_t) (fcml_uint16_t) src->int16;
        break;
    case FCML_DS_32:
        *dest = src->is_signed ?
                (fcml_int64_t) src->int32 :
                (fcml_int64_t) (fcml_uint32_t) src->int32;
        break;
    case FCML_DS_64:
        *dest = src->int64;
        break;
    default:
        return FCML_CEH_GEC_VALUE_OUT_OF_RANGE;
    }
    return FCML_CEH_GEC_NO_ERROR;
}

fcml_ceh_error fcml_fn_utils_decode_integer(fcml_st_memory_stream *stream,
        fcml_st_integer *integer, fcml_usize size) {
    fcml_bool result = FCML_FALSE;
    switch (size) {
    case FCML_DS_8:
        integer->int8 = fcml_fn_stream_read(stream, &result);
        integer->size = FCML_DS_8;
        break;
    case FCML_DS_16:
        integer->int16 = fcml_fn_stream_read_word(stream, &result);
        integer->size = FCML_DS_16;
        break;
    case FCML_DS_32:
        integer->int32 = fcml_fn_stream_read_dword(stream, &result);
        integer->size = FCML_DS_32;
        break;
    case FCML_DS_64:
        integer->int64 = fcml_fn_stream_read_qword(stream, &result);
        integer->size = FCML_DS_64;
        break;
    default:
        return FCML_CEH_GEC_INVALID_INPUT;
    }
    if (!result) {
        return FCML_CEH_GEC_EOF;
    }
    return FCML_CEH_GEC_NO_ERROR;
}

fcml_ceh_error fcml_fn_utils_encode_integer(fcml_st_memory_stream *stream,
        const fcml_st_integer *integer) {
    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
    fcml_bool result = FCML_FALSE;
    switch (integer->size) {
    case FCML_DS_8:
        result = fcml_fn_stream_write(stream, integer->int8);
        break;
    case FCML_DS_16:
        result = fcml_fn_stream_write_word(stream, integer->int16);
        break;
    case FCML_DS_32:
        result = fcml_fn_stream_write_dword(stream, integer->int32);
        break;
    case FCML_DS_64:
        result = fcml_fn_stream_write_qword(stream, integer->int64);
        break;
    }
    if (!result) {
        /* Insufficient stream size.*/
        error = FCML_CEH_GEC_INVALID_INPUT;
    }
    return error;
}

fcml_ceh_error fcml_fn_utils_offset_to_integer(const fcml_st_offset *offset,
        fcml_st_integer *integer) {
    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
    integer->int64 = 0;
    switch (offset->size) {
    case FCML_DS_16:
        integer->int16 = offset->off16;
        integer->size = FCML_DS_16;
        break;
    case FCML_DS_32:
        integer->int32 = offset->off32;
        integer->size = FCML_DS_32;
        break;
    case FCML_DS_64:
        integer->int64 = offset->off64;
        integer->size = FCML_DS_64;
        break;
    default:
        error = FCML_CEH_GEC_INVALID_INPUT;
        break;
    }
    integer->is_signed = offset->is_signed;
    return error;
}

fcml_ceh_error fcml_fn_utils_integer_to_offset(const fcml_st_integer *integer,
        fcml_st_offset *offset) {
    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
    offset->off64 = 0;
    switch (integer->size) {
    case FCML_DS_8:
        offset->off16 = (fcml_uint16_t) integer->int8;
        offset->size = FCML_DS_16;
        break;
    case FCML_DS_16:
        offset->off16 = (fcml_uint16_t) integer->int16;
        offset->size = FCML_DS_16;
        break;
    case FCML_DS_32:
        offset->off32 = (fcml_uint32_t) integer->int32;
        offset->size = FCML_DS_32;
        break;
    case FCML_DS_64:
        offset->off64 = (fcml_uint64_t) integer->int64;
        offset->size = FCML_DS_64;
        break;
    default:
        error = FCML_CEH_GEC_INVALID_INPUT;
        break;
    }
    offset->is_signed = integer->is_signed;
    return error;
}

fcml_ceh_error fcml_fn_utils_extend_int(fcml_st_integer *integer,
        fcml_usize extension) {
    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
    if (!integer->is_signed) {
        fcml_uint64_t temp_int = 0;
        switch (integer->size) {
        case 8:
            temp_int = (fcml_uint8_t) integer->int8;
            break;
        case 16:
            temp_int = (fcml_uint16_t) integer->int16;
            break;
        case 32:
            temp_int = (fcml_uint32_t) integer->int32;
            break;
        case 64:
            temp_int = (fcml_uint64_t) integer->int64;
            break;
        default:
            error = FCML_CEH_GEC_INVALID_INPUT;
            break;
        }
        if (!error) {
            integer->int64 = 0;
            switch (extension) {
            case 8:
                integer->int8 = (fcml_uint8_t) temp_int;
                break;
            case 16:
                integer->int16 = (fcml_uint16_t) temp_int;
                break;
            case 32:
                integer->int32 = (fcml_uint32_t) temp_int;
                break;
            case 64:
                integer->int64 = (fcml_uint64_t) temp_int;
                break;
            }
            integer->size = extension;
        }
    } else {
        fcml_int64_t temp_int = 0;
        switch (integer->size) {
        case 8:
            temp_int = integer->int8;
            break;
        case 16:
            temp_int = integer->int16;
            break;
        case 32:
            temp_int = integer->int32;
            break;
        case 64:
            temp_int = integer->int64;
            break;
        default:
            error = FCML_CEH_GEC_INVALID_INPUT;
            break;
        }
        if (!error) {
            integer->int64 = 0;
            switch (extension) {
            case 8:
                integer->int8 = (fcml_int8_t) temp_int;
                break;
            case 16:
                integer->int16 = (fcml_int16_t) temp_int;
                break;
            case 32:
                integer->int32 = (fcml_int32_t) temp_int;
                break;
            case 64:
                integer->int64 = (fcml_int64_t) temp_int;
                break;
            }
            integer->size = extension;
        }
        return error;
    }
    return error;
}

fcml_ceh_error fcml_fn_utils_conv_map_error(fcml_int error) {
    fcml_ceh_error ceh_error = FCML_CEH_GEC_NO_ERROR;
    switch (error) {
    case FCML_COLL_ERROR_NO_ERROR:
        ceh_error = FCML_CEH_GEC_NO_ERROR;
        break;
    case FCML_COLL_ERROR_OUT_OF_MEMORY:
        ceh_error = FCML_CEH_GEC_OUT_OF_MEMORY;
        break;
    case FCML_COLL_ERROR_BAD_ARGS:
    case FCML_COLL_ERROR_MAP_FULL:
        // Should never happened in case of FCML.
        FCML_TRACE_MSG("Map reached its maximal size or something "
                "different related to map processing happened.");
        ceh_error = FCML_CEH_GEC_INTERNAL_ERROR;
        break;
    }
    return ceh_error;
}

void fcml_fn_utils_conv_gec_to_error_info(fcml_bool enabled,
        fcml_st_ceh_error_container *error_container, fcml_ceh_error code) {
    if (enabled) {
        /* Prepare standard description of the error code,
         but only if there is no other error on the list. */
        fcml_st_ceh_error_info *current = error_container->errors;
        while (current) {
            if (current->level == FCML_EN_CEH_EL_ERROR) {
                return;
            }
            current = current->next_error;
        }

        if (!fcml_fn_ceh_add_error(error_container,
                fcml_fn_msg_get_message((fcml_en_msg_message_code) code), code,
                FCML_EN_CEH_EL_ERROR)) {
            FCML_TRACE_MSG("Out of memory, can not allocate space for error info.");
        }
    }
}

fcml_ceh_error fcml_fn_utils_prepare_entry_point(
        fcml_st_entry_point *entry_point) {

    /* Mode has to be set. */
    if (entry_point->op_mode != FCML_OM_16_BIT
            && entry_point->op_mode != FCML_OM_32_BIT
            && entry_point->op_mode != FCML_OM_64_BIT) {
        return FCML_CEH_GEC_INVALID_OPERATING_MODE;
    }

    /* 16 bit address size attribute is not supported in 64bit mode. */
    if (entry_point->op_mode == FCML_OM_64_BIT&&
    entry_point->address_size_attribute == FCML_DS_16) {
        return FCML_CEH_GEC_INVALID_ADDRESS_SIZE;
    }

    /* Check if attributes are valid and set them to default values. */
    if (!entry_point->address_size_attribute) {
        switch (entry_point->op_mode) {
        case FCML_OM_16_BIT:
            entry_point->address_size_attribute = FCML_DS_16;
            break;
        case FCML_OM_32_BIT:
            entry_point->address_size_attribute = FCML_DS_32;
            break;
        case FCML_OM_64_BIT:
            entry_point->address_size_attribute = FCML_DS_64;
            break;
        }
    }

    if (!entry_point->operand_size_attribute) {
        switch (entry_point->op_mode) {
        case FCML_OM_16_BIT:
            entry_point->operand_size_attribute = FCML_DS_16;
            break;
        case FCML_OM_32_BIT:
            entry_point->operand_size_attribute = FCML_DS_32;
            break;
        case FCML_OM_64_BIT:
            entry_point->operand_size_attribute = FCML_DS_32;
            break;
        }
    }

    /* Check if ASA is value.*/
    fcml_usize asa = entry_point->address_size_attribute;
    if (asa != FCML_DS_16 && asa != FCML_DS_32 && asa != FCML_DS_64) {
        return FCML_CEH_GEC_INVALID_ADDRESS_SIZE;
    }

    /* Check if OSA is value.*/
    fcml_usize osa = entry_point->operand_size_attribute;
    if (osa != FCML_DS_16 && osa != FCML_DS_32 && osa != FCML_DS_64) {
        return FCML_CEH_GEC_INVALID_OPPERAND_SIZE;
    }

    return FCML_CEH_GEC_NO_ERROR;
}

fcml_bool fcml_fn_utils_is_disp_neg(const fcml_st_integer *disp) {
    if (!disp->is_signed) {
        return FCML_FALSE;
    }
    switch (disp->size) {
    case FCML_DS_8:
        return disp->int8 < 0;
    case FCML_DS_16:
        return disp->int16 < 0;
    case FCML_DS_32:
        return disp->int32 < 0;
    case FCML_DS_64:
        return disp->int64 < 0;
    default:
        return FCML_FALSE;
    }
}

fcml_bool fcml_fn_utils_validate_vector_len(fcml_usize vector_length) {
    switch (vector_length) {
    case FCML_DS_128:
    case FCML_DS_256:
    case FCML_DS_512:
        return FCML_TRUE;
    }
    return FCML_FALSE;
}

fcml_int64_t fcml_fn_utils_divide_integer(const fcml_st_integer *dividend,
        fcml_st_integer *quotient, fcml_int32_t divisor) {
    fcml_int64_t remainder;
    quotient->is_signed = dividend->is_signed;
    quotient->size = dividend->size;
    switch (dividend->size) {
    case FCML_DS_8:
        if (dividend->is_signed) {
            quotient->int8 = dividend->int8 / divisor;
            remainder = dividend->int8 % divisor;
        } else {
            quotient->int8 = ((fcml_uint8_t) dividend->int8) / divisor;
            remainder = ((fcml_uint8_t) dividend->int8) % divisor;
        }
        break;
    case FCML_DS_16:
        if (dividend->is_signed) {
            quotient->int16 = dividend->int16 / divisor;
            remainder = dividend->int16 % divisor;
        } else {
            quotient->int16 = ((fcml_uint16_t) dividend->int16) / divisor;
            remainder = ((fcml_uint16_t) dividend->int16) % divisor;
        }
        break;
    case FCML_DS_32:
        if (dividend->is_signed) {
            quotient->int32 = dividend->int32 / divisor;
            remainder = dividend->int32 % divisor;
        } else {
            quotient->int32 = ((fcml_uint32_t) dividend->int32) / divisor;
            remainder = ((fcml_uint32_t) dividend->int32) % divisor;
        }
        break;
    case FCML_DS_64:
        if (dividend->is_signed) {
            quotient->int64 = dividend->int64 / divisor;
            remainder = dividend->int64 % divisor;
        } else {
            quotient->int64 = ((fcml_uint64_t) dividend->int64) / divisor;
            remainder = ((fcml_uint64_t) dividend->int64) % divisor;
        }
        break;
    }
    return remainder;
}

