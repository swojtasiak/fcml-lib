/*
 * fcml_streaming.h
 *
 *  Created on: 04-02-2013
 *      Author: tAs
 */

#ifndef FCML_STREAMING_H_
#define FCML_STREAMING_H_

#include <stdint.h>

#include "fcml_types.h"

/* Structures used to store information about memory. */

typedef struct fcml_st_memory_stream {
    void *base_address; /* Base address of memory. */
    fcml_int32_t offset; /* Offset. */
    fcml_int32_t size; /* Size. */
} fcml_st_memory_stream;

typedef fcml_uint32_t fcml_stream_pointer;

/* Methods used for streaming. */

enum ira_seek_type {
    IRA_START = 0, IRA_END, IRA_CURRENT
};

void fcml_fn_stream_seek( fcml_st_memory_stream *stream, fcml_int32_t offset, enum ira_seek_type type );
fcml_uint8_t fcml_fn_stream_read( fcml_st_memory_stream *stream, fcml_bool *result );
fcml_bool fcml_fn_stream_write( fcml_st_memory_stream *stream, uint8_t data );
fcml_uint8_t fcml_fn_stream_peek( fcml_st_memory_stream *stream, fcml_bool *result );
fcml_int32_t fcml_fn_stream_size( const fcml_st_memory_stream *stream );
int fcml_fn_stream_read_bytes( fcml_st_memory_stream *stream, void *buffer , int size);
int fcml_fn_stream_write_bytes( fcml_st_memory_stream *stream, void *buffer , int size);
fcml_uint16_t fcml_fn_stream_read_word( fcml_st_memory_stream *stream, fcml_bool *result );
fcml_uint32_t fcml_fn_stream_read_dword( fcml_st_memory_stream *stream, fcml_bool *result );
fcml_uint64_t fcml_fn_stream_read_qword( fcml_st_memory_stream *stream, fcml_bool *result );
fcml_bool fcml_fn_stream_write_word( fcml_st_memory_stream *stream, fcml_uint16_t data );
fcml_bool fcml_fn_stream_write_dword( fcml_st_memory_stream *stream, fcml_uint32_t data );
fcml_bool fcml_fn_stream_write_qword( fcml_st_memory_stream *stream, fcml_uint64_t data );
fcml_stream_pointer fcml_fn_stream_save_point( const fcml_st_memory_stream *stream );
void fcml_fn_stream_restore_point( fcml_st_memory_stream *stream, const fcml_stream_pointer stream_pointer );
void fcml_fn_stream_clean( fcml_st_memory_stream *stream );

#endif /* FCML_STREAMING_H_ */
