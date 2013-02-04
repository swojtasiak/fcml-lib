/*
 * fcml_streaming.h
 *
 *  Created on: 04-02-2013
 *      Author: tAs
 */

#ifndef FCML_STREAMING_H_
#define FCML_STREAMING_H_

#include <stdint.h>


/* Structures used to store information about memory. */

struct ira_memory_stream {
    void *base_address; /* Base address of memory. */
    uint32_t offset; /* Offset. */
    uint32_t size; /* Size. */
};

/* Methods used for streaming. */

enum ira_seek_type {
    IRA_START = 0, IRA_END, IRA_CURRENT
};

void _ira_stream_seek( struct ira_memory_stream *stream, uint32_t offset, enum ira_seek_type type );
uint8_t _ira_stream_read( struct ira_memory_stream *stream, int *result );
uint8_t _ira_stream_peek( struct ira_memory_stream *stream, int *result );
uint32_t _ira_stream_size( struct ira_memory_stream *stream );
int _ira_stream_read_bytes( struct ira_memory_stream *stream, void *buffer , int size);
uint16_t _ira_stream_read_word( struct ira_memory_stream *stream, int *result );
uint32_t _ira_stream_read_dword( struct ira_memory_stream *stream, int *result );
uint64_t _ira_stream_read_qword( struct ira_memory_stream *stream, int *result );

#endif /* FCML_STREAMING_H_ */
