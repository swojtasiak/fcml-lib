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

#include "fcml_stream.h"

#include "fcml_env_int.h"

void fcml_fn_stream_seek(fcml_st_memory_stream *stream, fcml_int32_t offset,
        fcml_en_stream_seek_type type) {
    switch (type) {
    case FCML_EN_ST_START:
        stream->offset = offset;
        break;
    case FCML_EN_ST_CURRENT:
        stream->offset += offset;
        break;
    case FCML_EN_ST_END:
        stream->offset = (stream->size + offset);
        break;
    }
    if (stream->offset < 0) {
        stream->offset = 0;
    }
    if (stream->offset > stream->size) {
        stream->offset = stream->size;
    }
}

void fcml_fn_stream_clean(fcml_st_memory_stream *stream) {
    fcml_fn_env_memory_clear(stream->base_address, stream->size);
    stream->offset = 0;
}

fcml_uint8_t fcml_fn_stream_read(fcml_st_memory_stream *stream,
        fcml_bool *result) {
    fcml_uint8_t *base_address = (fcml_uint8_t*) stream->base_address;
    *result = (stream->offset == stream->size) ? FCML_FALSE : FCML_TRUE;
    if (*result) {
        return base_address[stream->offset++];
    }
    return 0;
}

fcml_bool fcml_fn_stream_write(fcml_st_memory_stream *stream, fcml_uint8_t data) {
    fcml_bool result = FCML_FALSE;
    if (stream->offset < stream->size) {
        fcml_uint8_t *base_address = (fcml_uint8_t*) stream->base_address;
        base_address[stream->offset++] = data;
        result = FCML_TRUE;
    }
    return result;
}

fcml_uint8_t fcml_fn_stream_peek(fcml_st_memory_stream *stream,
        fcml_bool *result) {
    fcml_uint8_t *base_address = (fcml_uint8_t*) stream->base_address;
    *result = (stream->offset == stream->size) ? FCML_FALSE : FCML_TRUE;
    if (*result)
        return base_address[stream->offset];
    return 0;
}

fcml_int32_t fcml_fn_stream_size(const fcml_st_memory_stream *stream) {
    return stream->size - stream->offset;
}

int fcml_fn_stream_read_bytes(fcml_st_memory_stream *stream, fcml_ptr buffer,
        fcml_usize size) {
    if (size == 0) {
        return 0;
    }
    fcml_uint8_t *destination_buffer = (fcml_uint8_t*) buffer;
    fcml_uint8_t *source_buffer = (fcml_uint8_t*) stream->base_address;
    fcml_usize i = 0;
    while (stream->offset < stream->size && i < size) {
        destination_buffer[i++] = source_buffer[stream->offset++];
    }
    return i;
}

int fcml_fn_stream_write_bytes(fcml_st_memory_stream *stream, fcml_ptr buffer,
        fcml_usize size) {
    if (size == 0) {
        return 0;
    }
    fcml_uint8_t *source_buffer = (fcml_uint8_t*) buffer;
    fcml_uint8_t *destination_buffer = (fcml_uint8_t*) stream->base_address;
    fcml_usize i = 0;
    while (stream->offset < stream->size && i < size) {
        destination_buffer[stream->offset++] = source_buffer[i++];
    }
    return i;
}

fcml_uint16_t fcml_fn_stream_read_word(fcml_st_memory_stream *stream,
        fcml_bool *result) {
    fcml_uint16_t value = 0;
    if (stream->size - stream->offset >= sizeof(fcml_uint16_t)) {
        int offset = stream->offset;
        value |= ((fcml_uint8_t*) stream->base_address)[offset];
        value |= ((fcml_uint8_t*) stream->base_address)[offset + 1] << 8;
        stream->offset += sizeof(fcml_uint16_t);
        *result = FCML_TRUE;
    } else {
        *result = FCML_FALSE;
    }
    return value;
}

fcml_uint32_t fcml_fn_stream_read_dword(fcml_st_memory_stream *stream,
        fcml_bool *result) {
    fcml_uint32_t value = 0;
    if (stream->size - stream->offset >= sizeof(fcml_uint32_t)) {
        int offset = stream->offset;
        value |= ((fcml_uint8_t*) stream->base_address)[offset];
        value |= ((fcml_uint8_t*) stream->base_address)[offset + 1] << 8;
        value |= ((fcml_uint8_t*) stream->base_address)[offset + 2] << 16;
        value |= ((fcml_uint8_t*) stream->base_address)[offset + 3] << 24;
        stream->offset += sizeof(fcml_uint32_t);
        *result = FCML_TRUE;
    } else {
        *result = FCML_FALSE;
    }
    return value;
}

fcml_uint64_t fcml_fn_stream_read_qword(fcml_st_memory_stream *stream,
        fcml_bool *result) {
    fcml_uint64_t value = 0;
    if (stream->size - stream->offset >= sizeof(fcml_uint64_t)) {
        int i;
        int offset = stream->offset;
        for (i = 0; i < sizeof(fcml_uint64_t); i++) {
            value |=
                    ((fcml_uint64_t) ((fcml_uint8_t*) stream->base_address)[offset
                            + i]) << (i << 3);
        }
        stream->offset += sizeof(fcml_uint64_t);
        *result = FCML_TRUE;
    } else {
        *result = FCML_FALSE;
    }
    return value;
}

fcml_bool fcml_fn_stream_write_word(fcml_st_memory_stream *stream,
        fcml_uint16_t data) {
    fcml_bool result = FCML_FALSE;
    if (stream->size - stream->offset >= sizeof(fcml_uint16_t)) {
        int offset = stream->offset;
        fcml_uint8_t *buffer = (fcml_uint8_t*) stream->base_address;
        buffer[offset] = data & 0x00FF;
        buffer[offset + 1] = data >> 8;
        stream->offset += sizeof(fcml_uint16_t);
        result = FCML_TRUE;
    }
    return result;
}

fcml_bool fcml_fn_stream_write_dword(fcml_st_memory_stream *stream,
        fcml_uint32_t data) {
    fcml_bool result = FCML_FALSE;
    if (stream->size - stream->offset >= sizeof(fcml_uint32_t)) {
        int offset = stream->offset;
        ((fcml_uint8_t*) stream->base_address)[offset] = data;
        ((fcml_uint8_t*) stream->base_address)[offset + 1] = data >> 8;
        ((fcml_uint8_t*) stream->base_address)[offset + 2] = data >> 16;
        ((fcml_uint8_t*) stream->base_address)[offset + 3] = data >> 24;
        stream->offset += sizeof(fcml_uint32_t);
        result = FCML_TRUE;
    }
    return result;
}

fcml_bool fcml_fn_stream_write_qword(fcml_st_memory_stream *stream,
        fcml_uint64_t data) {
    fcml_bool result = FCML_FALSE;
    if (stream->size - stream->offset >= sizeof(fcml_uint64_t)) {
        int i;
        int offset = stream->offset;
        fcml_uint8_t *buffer = (fcml_uint8_t*) stream->base_address;
        for (i = 0; i < sizeof(fcml_uint64_t); i++) {
            buffer[offset + i] = (fcml_uint8_t) (data >> (i << 3));
        }
        stream->offset += sizeof(fcml_uint64_t);
        result = FCML_TRUE;
    }
    return result;
}

fcml_stream_pointer fcml_fn_stream_save_point(
        const fcml_st_memory_stream *stream) {
    return stream->offset;
}

void fcml_fn_stream_restore_point(fcml_st_memory_stream *stream,
        const fcml_stream_pointer stream_pointer) {
    stream->offset = stream_pointer;
}

fcml_st_memory_stream fcml_fn_stream_wrap( fcml_string buffer,
        fcml_usize length) {
    fcml_st_memory_stream stream = { 0 };
    stream.base_address = buffer;
    stream.offset = 0;
    stream.size = length;
    return stream;
}
