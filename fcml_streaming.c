/*
 * fcml_streaming.c
 *
 *  Created on: 04-02-2013
 *      Author: tAs
 */

#include "fcml_streaming.h"

void _ira_stream_seek( struct ira_memory_stream *stream, uint32_t offset, enum ira_seek_type type ) {
    switch(type) {
        case IRA_START:
            stream->offset = offset;
        break;
        case IRA_CURRENT:
            stream->offset += offset;
        break;
        case IRA_END:
            stream->offset = (stream->size - offset);
        break;
    }
}

uint8_t _ira_stream_read( struct ira_memory_stream *stream, int *result ) {
    uint8_t *base_address = (uint8_t *)stream->base_address;
    *result = ( stream->offset == stream->size ) ? 0 : 1;
    if( *result )
        return base_address[stream->offset++];
    return 0;
}

uint8_t _ira_stream_peek( struct ira_memory_stream *stream, int *result ) {
    uint8_t *base_address = (uint8_t *)stream->base_address;
    *result = ( stream->offset == stream->size ) ? 0 : 1;
    if( *result )
        return base_address[stream->offset];
    return 0;
}

uint32_t _ira_stream_size( struct ira_memory_stream *stream ) {
    return stream->size - stream->offset;
}

int _ira_stream_read_bytes( struct ira_memory_stream *stream, void *buffer , int size) {
    if( size == 0 ) {
        return 0;
    }
    uint8_t *destination_buffer = (uint8_t*)buffer;
    int i = 0;
    while( stream->offset < stream->size && i < size ) {
        destination_buffer[i++] = ((uint8_t*)stream->base_address)[stream->offset++];
    }
    return i;
}

uint16_t _ira_stream_read_word( struct ira_memory_stream *stream, int *result ) {
    uint16_t value = 0;
    *result = stream->size - stream->offset >= sizeof(uint16_t);
    if( *result ) {
        int offset = stream->offset;
        value |= ((uint8_t*)stream->base_address)[offset];
        value |= ((uint8_t*)stream->base_address)[offset + 1] << 8;
        stream->offset += sizeof(uint16_t);
    }
    return value;
}

uint32_t _ira_stream_read_dword( struct ira_memory_stream *stream, int *result ) {
    uint32_t value = 0;
    *result = stream->size - stream->offset >= sizeof(uint32_t);
    if( *result ) {
        int offset = stream->offset;
        value |= ((uint8_t*)stream->base_address)[offset];
        value |= ((uint8_t*)stream->base_address)[offset + 1] << 8;
        value |= ((uint8_t*)stream->base_address)[offset + 2] << 16;
        value |= ((uint8_t*)stream->base_address)[offset + 3] << 24;
        stream->offset += sizeof(uint32_t);
    }
    return value;
}

uint64_t _ira_stream_read_qword( struct ira_memory_stream *stream, int *result ) {
    // TODO: test it!
    uint64_t value = 0;
    *result = stream->size - stream->offset >= sizeof(uint64_t);
    if( *result ) {
        int i;
        int offset = stream->offset;
        for( i = 0; i < sizeof(uint64_t); i++ ) {
            value |= ((uint8_t*)stream->base_address)[offset + i] << ( i << 3 );
        }
        stream->offset += sizeof(uint64_t);
    }
    return value;
}
