/*
 * fcml_streaming.h
 *
 *  Created on: 04-02-2013
 *      Author: tAs
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
    FCML_EN_ST_START = 0,
    FCML_EN_ST_END,
    FCML_EN_ST_CURRENT
} fcml_en_stream_seek_type;

void fcml_fn_stream_seek( fcml_st_memory_stream *stream, fcml_int32_t offset, fcml_en_stream_seek_type type );
fcml_uint8_t fcml_fn_stream_read( fcml_st_memory_stream *stream, fcml_bool *result );
fcml_bool fcml_fn_stream_write( fcml_st_memory_stream *stream, fcml_uint8_t data );
fcml_uint8_t fcml_fn_stream_peek( fcml_st_memory_stream *stream, fcml_bool *result );
fcml_int32_t fcml_fn_stream_size( const fcml_st_memory_stream *stream );
int fcml_fn_stream_read_bytes( fcml_st_memory_stream *stream, fcml_ptr buffer, fcml_usize size);
int fcml_fn_stream_write_bytes( fcml_st_memory_stream *stream, fcml_ptr buffer, fcml_usize size);
fcml_uint16_t fcml_fn_stream_read_word( fcml_st_memory_stream *stream, fcml_bool *result );
fcml_uint32_t fcml_fn_stream_read_dword( fcml_st_memory_stream *stream, fcml_bool *result );
fcml_uint64_t fcml_fn_stream_read_qword( fcml_st_memory_stream *stream, fcml_bool *result );
fcml_bool fcml_fn_stream_write_word( fcml_st_memory_stream *stream, fcml_uint16_t data );
fcml_bool fcml_fn_stream_write_dword( fcml_st_memory_stream *stream, fcml_uint32_t data );
fcml_bool fcml_fn_stream_write_qword( fcml_st_memory_stream *stream, fcml_uint64_t data );
fcml_stream_pointer fcml_fn_stream_save_point( const fcml_st_memory_stream *stream );
void fcml_fn_stream_restore_point( fcml_st_memory_stream *stream, const fcml_stream_pointer stream_pointer );
void fcml_fn_stream_clean( fcml_st_memory_stream *stream );
fcml_st_memory_stream fcml_fn_stream_wrap( fcml_string buffer, fcml_usize length );

#endif /* FCML_STREAMING_H_ */
