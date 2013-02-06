/*
 * fcml_streaming.c
 *
 *  Created on: 04-02-2013
 *      Author: tAs
 */

#include <stdlib.h>

#include "fcml_stream.h"
#include "stdbool.h"

void fcml_fn_stream_seek( fcml_st_memory_stream *stream, uint32_t offset, enum ira_seek_type type ) {
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

uint8_t fcml_fn_stream_read( fcml_st_memory_stream *stream, fcml_bool *result ) {
    uint8_t *base_address = (uint8_t *)stream->base_address;
    *result = ( stream->offset == stream->size ) ? FCML_FALSE : FCML_TRUE;
    if( *result ) {
        return base_address[stream->offset++];
    }
    return 0;
}

fcml_bool fcml_fn_stream_write( fcml_st_memory_stream *stream, uint8_t data ) {
    fcml_bool result = FCML_FALSE;
    if( stream->offset < stream->size )  {
        uint8_t *base_address = (uint8_t *)stream->base_address;
        base_address[stream->offset++] = data;
        result = FCML_TRUE;
    }
    return result;
}

uint8_t fcml_fn_stream_peek( fcml_st_memory_stream *stream, fcml_bool *result ) {
    uint8_t *base_address = (uint8_t *)stream->base_address;
    *result = ( stream->offset == stream->size ) ? FCML_FALSE : FCML_TRUE;
    if( *result )
        return base_address[stream->offset];
    return 0;
}

uint32_t fcml_fn_stream_size( fcml_st_memory_stream *stream ) {
    return stream->size - stream->offset;
}

int fcml_fn_stream_read_bytes( fcml_st_memory_stream *stream, void *buffer , int size) {
    if( size == 0 ) {
        return 0;
    }
    uint8_t *destination_buffer = (uint8_t*)buffer;
    uint8_t *source_buffer = (uint8_t*)stream->base_address;
    int i = 0;
    while( stream->offset < stream->size && i < size ) {
        destination_buffer[i++] = source_buffer[stream->offset++];
    }
    return i;
}

int fcml_fn_stream_write_bytes( fcml_st_memory_stream *stream, void *buffer , int size) {
    if( size == 0 ) {
        return 0;
    }
    uint8_t *source_buffer = (uint8_t*)buffer;
    uint8_t *destination_buffer = (uint8_t*)stream->base_address;
    int i = 0;
    while( stream->offset < stream->size && i < size ) {
        destination_buffer[stream->offset++] = source_buffer[i++];
    }
    return i;
}

uint16_t fcml_fn_stream_read_word( fcml_st_memory_stream *stream, fcml_bool *result ) {
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

uint32_t fcml_fn_stream_read_dword( fcml_st_memory_stream *stream, fcml_bool *result ) {
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

uint64_t fcml_fn_stream_read_qword( fcml_st_memory_stream *stream, fcml_bool *result ) {
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

fcml_bool fcml_fn_stream_write_word( fcml_st_memory_stream *stream, uint16_t data ) {
    fcml_bool result = FCML_FALSE;
    if( stream->size - stream->offset >= sizeof(uint16_t) ) {
       int offset = stream->offset;
       uint8_t *buffer = (uint8_t*)stream->base_address;
       buffer[offset] = data & 0x00FF;
       buffer[offset + 1] = data >> 8;
       stream->offset += sizeof(uint16_t);
    }
    return result;
}

fcml_bool fcml_fn_stream_write_dword( fcml_st_memory_stream *stream, uint32_t data ) {
    fcml_bool result = FCML_FALSE;
    if( stream->size - stream->offset >= sizeof(uint32_t) ) {
        int offset = stream->offset;
        ((uint8_t*)stream->base_address)[offset] = data;
        ((uint8_t*)stream->base_address)[offset + 1] = data >> 8;
        ((uint8_t*)stream->base_address)[offset + 2] = data >> 16;
        ((uint8_t*)stream->base_address)[offset + 3] = data >> 24;
        stream->offset += sizeof(uint32_t);
    }
    return result;
}

fcml_bool fcml_fn_stream_write_qword( fcml_st_memory_stream *stream, uint64_t data ) {
   fcml_bool result = FCML_FALSE;
   if( stream->size - stream->offset >= sizeof(uint64_t) ) {
       int i;
       int offset = stream->offset;
       uint8_t *buffer = (uint8_t*)stream->base_address;
       for( i = 0; i < sizeof(uint64_t); i++ ) {
           buffer[offset + i] = data >> ( i << 3 );
       }
       stream->offset += sizeof(uint64_t);
   }
   return result;
}

fcml_stream_pointer fcml_fn_stream_save_point( fcml_st_memory_stream *stream ) {
    return stream->offset;
}

void fcml_fn_stream_restore_point( fcml_st_memory_stream *stream, fcml_stream_pointer stream_pointer ) {
    stream->offset = stream_pointer;
}
