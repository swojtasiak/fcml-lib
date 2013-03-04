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
    int32_t offset; /* Offset. */
    int32_t size; /* Size. */
} fcml_st_memory_stream;

typedef uint32_t fcml_stream_pointer;

/* Methods used for streaming. */

enum ira_seek_type {
    IRA_START = 0, IRA_END, IRA_CURRENT
};

void fcml_fn_stream_seek( fcml_st_memory_stream *stream, int32_t offset, enum ira_seek_type type );
uint8_t fcml_fn_stream_read( fcml_st_memory_stream *stream, fcml_bool *result );
fcml_bool fcml_fn_stream_write( fcml_st_memory_stream *stream, uint8_t data );
uint8_t fcml_fn_stream_peek( fcml_st_memory_stream *stream, fcml_bool *result );
int32_t fcml_fn_stream_size( fcml_st_memory_stream *stream );
int fcml_fn_stream_read_bytes( fcml_st_memory_stream *stream, void *buffer , int size);
int fcml_fn_stream_write_bytes( fcml_st_memory_stream *stream, void *buffer , int size);
uint16_t fcml_fn_stream_read_word( fcml_st_memory_stream *stream, fcml_bool *result );
uint32_t fcml_fn_stream_read_dword( fcml_st_memory_stream *stream, fcml_bool *result );
uint64_t fcml_fn_stream_read_qword( fcml_st_memory_stream *stream, fcml_bool *result );
fcml_bool fcml_fn_stream_write_word( fcml_st_memory_stream *stream, uint16_t data );
fcml_bool fcml_fn_stream_write_dword( fcml_st_memory_stream *stream, uint32_t data );
fcml_bool fcml_fn_stream_write_qword( fcml_st_memory_stream *stream, uint64_t data );
fcml_stream_pointer fcml_fn_stream_save_point( fcml_st_memory_stream *stream );
void fcml_fn_stream_restore_point( fcml_st_memory_stream *stream, fcml_stream_pointer stream_pointer );

#endif /* FCML_STREAMING_H_ */
