/*
 * stream_t.c
 *
 *  Created on: 06-02-2013
 *      Author: tAs
 */

#include <stdlib.h>

#include <fcml_stream.h>

#include "stream_t.h"

uint8_t buffer[128];

int fcml_tf_stream_suite_init(void) {
    return 0;
}

int fcml_tf_stream_suite_cleanup(void) {
    return 0;
}

void fcml_tf_stream_read_byte(void) {

    buffer[0] = 1;
    buffer[1] = 2;
    buffer[2] = 3;
    buffer[3] = 4;

    fcml_st_memory_stream stream;
    stream.base_address = buffer;
    stream.offset = 0;
    stream.size = 4;

    fcml_bool result;
    uint8_t data;
    data = fcml_fn_stream_read( &stream, &result );
    CU_ASSERT( result == FCML_TRUE );
    CU_ASSERT( data == 1 );

    data = fcml_fn_stream_read( &stream, &result );
    CU_ASSERT( result == FCML_TRUE );
    CU_ASSERT( data == 2 );

    data = fcml_fn_stream_read( &stream, &result );
    CU_ASSERT( result == FCML_TRUE );
    CU_ASSERT( data == 3 );

    data = fcml_fn_stream_read( &stream, &result );
    CU_ASSERT( result == FCML_TRUE );
    CU_ASSERT( data == 4 );

    data = fcml_fn_stream_read( &stream, &result );
    CU_ASSERT( result == FCML_FALSE );

    stream.base_address = buffer;
    stream.offset = 0;
    stream.size = 0;

    data = fcml_fn_stream_read( &stream, &result );
    CU_ASSERT( result == FCML_FALSE );
}

void fcml_tf_stream_write_byte(void) {

    memset( buffer, 0, sizeof( buffer ) );

    fcml_st_memory_stream stream;
    stream.base_address = buffer;
    stream.offset = 0;
    stream.size = 4;

    fcml_bool result;
    result = fcml_fn_stream_write( &stream, 1 );
    CU_ASSERT( result == FCML_TRUE );

    result = fcml_fn_stream_write( &stream, 2 );
    CU_ASSERT( result == FCML_TRUE );

    result = fcml_fn_stream_write( &stream, 3 );
    CU_ASSERT( result == FCML_TRUE );

    result = fcml_fn_stream_write( &stream, 4 );
    CU_ASSERT( result == FCML_TRUE );

    result = fcml_fn_stream_write( &stream, 5 );
    CU_ASSERT( result == FCML_FALSE );

    CU_ASSERT(buffer[0] == 1);
    CU_ASSERT(buffer[1] == 2);
    CU_ASSERT(buffer[2] == 3);
    CU_ASSERT(buffer[3] == 4);

    stream.base_address = buffer;
    stream.offset = 0;
    stream.size = 0;

    result = fcml_fn_stream_write( &stream, 1 );
    CU_ASSERT( result == FCML_FALSE );
}

void fcml_tf_stream_read_word(void) {

    buffer[0] = 1;
    buffer[1] = 2;
    buffer[2] = 3;
    buffer[3] = 4;
    buffer[4] = 5;
    buffer[5] = 6;
    buffer[6] = 7;
    buffer[7] = 8;

    fcml_st_memory_stream stream;
    stream.base_address = buffer;
    stream.offset = 0;
    stream.size = 8;

    fcml_bool result;
    uint16_t data;
    data = fcml_fn_stream_read_word( &stream, &result );
    CU_ASSERT( result == FCML_TRUE );
    CU_ASSERT( data == 0x0201 );

    data = fcml_fn_stream_read_word( &stream, &result );
    CU_ASSERT( result == FCML_TRUE );
    CU_ASSERT( data == 0x0403 );

    data = fcml_fn_stream_read_word( &stream, &result );
    CU_ASSERT( result == FCML_TRUE );
    CU_ASSERT( data == 0x0605 );

    data = fcml_fn_stream_read_word( &stream, &result );
    CU_ASSERT( result == FCML_TRUE );
    CU_ASSERT( data == 0x0807 );

    data = fcml_fn_stream_read_word( &stream, &result );
    CU_ASSERT( result == FCML_FALSE );

    stream.base_address = buffer;
    stream.offset = 0;
    stream.size = 1;

    data = fcml_fn_stream_read_word( &stream, &result );
    CU_ASSERT( result == FCML_FALSE );

    stream.base_address = buffer;
    stream.offset = 0;
    stream.size = 0;

    data = fcml_fn_stream_read_word( &stream, &result );
    CU_ASSERT( result == FCML_FALSE );

    stream.base_address = buffer;
    stream.offset = 0;
    stream.size = 2;

    data = fcml_fn_stream_read_word( &stream, &result );
    CU_ASSERT( result == FCML_TRUE );
    CU_ASSERT( data == 0x0201 );
}

void fcml_tf_stream_write_word(void) {

    memset( buffer, 0, sizeof( buffer ) );

    fcml_st_memory_stream stream;
    stream.base_address = buffer;
    stream.offset = 0;
    stream.size = 8;

    fcml_bool result;
    result = fcml_fn_stream_write_word( &stream, 0x0201 );
    CU_ASSERT( result == FCML_TRUE );

    result = fcml_fn_stream_write_word( &stream, 0x0403 );
    CU_ASSERT( result == FCML_TRUE );

    result = fcml_fn_stream_write_word( &stream, 0x0605 );
    CU_ASSERT( result == FCML_TRUE );

    result = fcml_fn_stream_write_word( &stream, 0x0807 );
    CU_ASSERT( result == FCML_TRUE );

    result = fcml_fn_stream_write_word( &stream, 0x0F09 );
    CU_ASSERT( result == FCML_FALSE );

    CU_ASSERT(buffer[0] == 1);
    CU_ASSERT(buffer[1] == 2);
    CU_ASSERT(buffer[2] == 3);
    CU_ASSERT(buffer[3] == 4);
    CU_ASSERT(buffer[4] == 5);
    CU_ASSERT(buffer[5] == 6);
    CU_ASSERT(buffer[6] == 7);
    CU_ASSERT(buffer[7] == 8);

    stream.base_address = buffer;
    stream.offset = 0;
    stream.size = 0;

    result = fcml_fn_stream_write_word( &stream, 0x0102 );
    CU_ASSERT( result == FCML_FALSE );

    stream.base_address = buffer;
    stream.offset = 0;
    stream.size = 1;

    result = fcml_fn_stream_write_word( &stream, 0x0102 );
    CU_ASSERT( result == FCML_FALSE );

    stream.base_address = buffer;
    stream.offset = 0;
    stream.size = 2;

    result = fcml_fn_stream_write_word( &stream, 0x0A0B );
    CU_ASSERT( result == FCML_TRUE );

    CU_ASSERT(buffer[0] == 0x0B);
    CU_ASSERT(buffer[1] == 0x0A);
}

void fcml_tf_stream_read_dword(void) {

    buffer[0] = 1;
    buffer[1] = 2;
    buffer[2] = 3;
    buffer[3] = 4;
    buffer[4] = 5;
    buffer[5] = 6;
    buffer[6] = 7;
    buffer[7] = 8;

    fcml_st_memory_stream stream;
    stream.base_address = buffer;
    stream.offset = 0;
    stream.size = 8;

    fcml_bool result;
    uint32_t data;
    data = fcml_fn_stream_read_dword( &stream, &result );
    CU_ASSERT( result == FCML_TRUE );
    CU_ASSERT( data == 0x04030201 );

    data = fcml_fn_stream_read_dword( &stream, &result );
    CU_ASSERT( result == FCML_TRUE );
    CU_ASSERT( data == 0x08070605 );

    data = fcml_fn_stream_read_dword( &stream, &result );
    CU_ASSERT( result == FCML_FALSE );

    stream.base_address = buffer;
    stream.offset = 0;
    stream.size = 0;

    data = fcml_fn_stream_read_dword( &stream, &result );
    CU_ASSERT( result == FCML_FALSE );

    stream.base_address = buffer;
    stream.offset = 0;
    stream.size = 3;

    data = fcml_fn_stream_read_dword( &stream, &result );
    CU_ASSERT( result == FCML_FALSE );

    stream.base_address = buffer;
    stream.offset = 0;
    stream.size = 4;

    data = fcml_fn_stream_read_dword( &stream, &result );
    CU_ASSERT( result == FCML_TRUE );
    CU_ASSERT( data == 0x04030201 );

}

void fcml_tf_stream_write_dword(void) {

    memset( buffer, 0, sizeof( buffer ) );

    fcml_st_memory_stream stream;
    stream.base_address = buffer;
    stream.offset = 0;
    stream.size = 8;

    fcml_bool result;
    result = fcml_fn_stream_write_dword( &stream, 0x04030201 );
    CU_ASSERT( result == FCML_TRUE );

    result = fcml_fn_stream_write_dword( &stream, 0x08070605 );
    CU_ASSERT( result == FCML_TRUE );

    result = fcml_fn_stream_write_dword( &stream, 0x090A0B0C );
    CU_ASSERT( result == FCML_FALSE );

    CU_ASSERT(buffer[0] == 1);
    CU_ASSERT(buffer[1] == 2);
    CU_ASSERT(buffer[2] == 3);
    CU_ASSERT(buffer[3] == 4);
    CU_ASSERT(buffer[4] == 5);
    CU_ASSERT(buffer[5] == 6);
    CU_ASSERT(buffer[6] == 7);
    CU_ASSERT(buffer[7] == 8);

    stream.base_address = buffer;
    stream.offset = 0;
    stream.size = 0;

    result = fcml_fn_stream_write_dword( &stream, 0x01020304 );
    CU_ASSERT( result == FCML_FALSE );

    stream.base_address = buffer;
    stream.offset = 0;
    stream.size = 3;

    result = fcml_fn_stream_write_dword( &stream, 0x01020304 );
    CU_ASSERT( result == FCML_FALSE );

    stream.base_address = buffer;
    stream.offset = 0;
    stream.size = 4;

    result = fcml_fn_stream_write_dword( &stream, 0x0A0B0C0D );
    CU_ASSERT( result == FCML_TRUE );

    CU_ASSERT(buffer[0] == 0x0D);
    CU_ASSERT(buffer[1] == 0x0C);
    CU_ASSERT(buffer[2] == 0x0B);
    CU_ASSERT(buffer[3] == 0x0A);
}

void fcml_tf_stream_read_qword(void) {

    buffer[0] = 1;
    buffer[1] = 2;
    buffer[2] = 3;
    buffer[3] = 4;
    buffer[4] = 5;
    buffer[5] = 6;
    buffer[6] = 7;
    buffer[7] = 8;

    buffer[8] = 9;
    buffer[9] = 10;
    buffer[10] = 11;
    buffer[11] = 12;
    buffer[12] = 13;
    buffer[13] = 14;
    buffer[14] = 15;
    buffer[15] = 0;

    fcml_st_memory_stream stream;
    stream.base_address = buffer;
    stream.offset = 0;
    stream.size = 16;

    fcml_bool result;
    uint64_t data;
    data = fcml_fn_stream_read_qword( &stream, &result );
    CU_ASSERT( result == FCML_TRUE );
    CU_ASSERT( data == 0x0807060504030201 );

    data = fcml_fn_stream_read_qword( &stream, &result );
    CU_ASSERT( result == FCML_TRUE );
    CU_ASSERT( data == 0x000F0E0D0C0B0A09 );

    data = fcml_fn_stream_read_qword( &stream, &result );
    CU_ASSERT( result == FCML_FALSE );

    stream.base_address = buffer;
    stream.offset = 0;
    stream.size = 0;

    data = fcml_fn_stream_read_qword( &stream, &result );
    CU_ASSERT( result == FCML_FALSE );

    stream.base_address = buffer;
    stream.offset = 0;
    stream.size = 7;

    data = fcml_fn_stream_read_qword( &stream, &result );
    CU_ASSERT( result == FCML_FALSE );

    stream.base_address = buffer;
    stream.offset = 0;
    stream.size = 8;

    data = fcml_fn_stream_read_qword( &stream, &result );
    CU_ASSERT( result == FCML_TRUE );
    CU_ASSERT( data == 0x0807060504030201 );

}


CU_TestInfo fctl_ti_stream[] = {
    { "fcml_tf_stream_read_byte", fcml_tf_stream_read_byte },
    { "fcml_tf_stream_write_byte", fcml_tf_stream_write_byte },
    { "fcml_tf_stream_read_word", fcml_tf_stream_read_word },
    { "fcml_tf_stream_write_word", fcml_tf_stream_write_word },
    { "fcml_tf_stream_read_dword", fcml_tf_stream_read_dword },
    { "fcml_tf_stream_write_dword", fcml_tf_stream_write_dword },
    { "fcml_tf_stream_read_qword", fcml_tf_stream_read_qword },
    CU_TEST_INFO_NULL,
};

CU_SuiteInfo fctl_si_stream[] = {
    { "suite-stream", fcml_tf_stream_suite_init, fcml_tf_stream_suite_cleanup, fctl_ti_stream },
    CU_SUITE_INFO_NULL,
};



