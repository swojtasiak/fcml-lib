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

#ifndef FCML_STREAMING_H_
#define FCML_STREAMING_H_

#include <fcml_types.h>

/* Structures used to store information about memory. */

typedef struct fcml_st_memory_stream {
    void *base_address; /* Base address of memory. */
    fcml_int32_t offset; /* Offset. */
    fcml_int32_t size; /* Size. */
} fcml_st_memory_stream;

typedef fcml_uint32_t fcml_stream_pointer;

/* Methods used for streaming. */

typedef enum fcml_en_stream_seek_type {
    FCML_EN_ST_START = 0, FCML_EN_ST_END, FCML_EN_ST_CURRENT
} fcml_en_stream_seek_type;

static inline fcml_st_memory_stream fcml_fn_stream_init(void *base_address,
        fcml_int32_t offset, fcml_int32_t size) {
    fcml_st_memory_stream stream;
    stream.base_address = base_address;
    stream.offset = offset;
    stream.size = size;
    return stream;
}

void fcml_fn_stream_seek(fcml_st_memory_stream *stream, fcml_int32_t offset,
        fcml_en_stream_seek_type type);

fcml_uint8_t fcml_fn_stream_read(fcml_st_memory_stream *stream,
        fcml_bool *result);

fcml_bool fcml_fn_stream_write(fcml_st_memory_stream *stream,
        fcml_uint8_t data);

fcml_uint8_t fcml_fn_stream_peek(fcml_st_memory_stream *stream,
        fcml_bool *result);

fcml_int32_t fcml_fn_stream_size(const fcml_st_memory_stream *stream);

int fcml_fn_stream_read_bytes(fcml_st_memory_stream *stream, fcml_ptr buffer,
        fcml_usize size);

int fcml_fn_stream_write_bytes(fcml_st_memory_stream *stream, fcml_ptr buffer,
        fcml_usize size);

fcml_uint16_t fcml_fn_stream_read_word(fcml_st_memory_stream *stream,
        fcml_bool *result);

fcml_uint32_t fcml_fn_stream_read_dword(fcml_st_memory_stream *stream,
        fcml_bool *result);

fcml_uint64_t fcml_fn_stream_read_qword(fcml_st_memory_stream *stream,
        fcml_bool *result);

fcml_bool fcml_fn_stream_write_word(fcml_st_memory_stream *stream,
        fcml_uint16_t data);

fcml_bool fcml_fn_stream_write_dword(fcml_st_memory_stream *stream,
        fcml_uint32_t data);

fcml_bool fcml_fn_stream_write_qword(fcml_st_memory_stream *stream,
        fcml_uint64_t data);

fcml_stream_pointer fcml_fn_stream_save_point(
        const fcml_st_memory_stream *stream);

void fcml_fn_stream_restore_point(fcml_st_memory_stream *stream,
        const fcml_stream_pointer stream_pointer);

void fcml_fn_stream_clean(fcml_st_memory_stream *stream);

fcml_st_memory_stream fcml_fn_stream_wrap( fcml_string buffer,
        fcml_usize length);

#endif /* FCML_STREAMING_H_ */
