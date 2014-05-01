/*
 * stream_t.c
 *
 *  Created on: 06-02-2013
 *      Author: Slawomir Wojtasiak
 */

#include <stdlib.h>

#include <fcml_stream.h>

#include "stream_t.h"

fcml_uint8_t buffer[128];

fcml_bool fcml_tf_stream_suite_init(void) {
	return FCML_TRUE;
}

fcml_bool fcml_tf_stream_suite_cleanup(void) {
	return FCML_TRUE;
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
    fcml_uint8_t data;
    data = fcml_fn_stream_read( &stream, &result );
    STF_ASSERT( result == FCML_TRUE );
    STF_ASSERT( data == 1 );

    data = fcml_fn_stream_read( &stream, &result );
    STF_ASSERT( result == FCML_TRUE );
    STF_ASSERT( data == 2 );

    data = fcml_fn_stream_read( &stream, &result );
    STF_ASSERT( result == FCML_TRUE );
    STF_ASSERT( data == 3 );

    data = fcml_fn_stream_read( &stream, &result );
    STF_ASSERT( result == FCML_TRUE );
    STF_ASSERT( data == 4 );

    data = fcml_fn_stream_read( &stream, &result );
    STF_ASSERT( result == FCML_FALSE );

    stream.base_address = buffer;
    stream.offset = 0;
    stream.size = 0;

    data = fcml_fn_stream_read( &stream, &result );
    STF_ASSERT( result == FCML_FALSE );
}

void fcml_tf_stream_write_byte(void) {

    memset( buffer, 0, sizeof( buffer ) );

    fcml_st_memory_stream stream;
    stream.base_address = buffer;
    stream.offset = 0;
    stream.size = 4;

    fcml_bool result;
    result = fcml_fn_stream_write( &stream, 1 );
    STF_ASSERT( result == FCML_TRUE );

    result = fcml_fn_stream_write( &stream, 2 );
    STF_ASSERT( result == FCML_TRUE );

    result = fcml_fn_stream_write( &stream, 3 );
    STF_ASSERT( result == FCML_TRUE );

    result = fcml_fn_stream_write( &stream, 4 );
    STF_ASSERT( result == FCML_TRUE );

    result = fcml_fn_stream_write( &stream, 5 );
    STF_ASSERT( result == FCML_FALSE );

    STF_ASSERT(buffer[0] == 1);
    STF_ASSERT(buffer[1] == 2);
    STF_ASSERT(buffer[2] == 3);
    STF_ASSERT(buffer[3] == 4);

    stream.base_address = buffer;
    stream.offset = 0;
    stream.size = 0;

    result = fcml_fn_stream_write( &stream, 1 );
    STF_ASSERT( result == FCML_FALSE );
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
    fcml_uint16_t data;
    data = fcml_fn_stream_read_word( &stream, &result );
    STF_ASSERT( result == FCML_TRUE );
    STF_ASSERT( data == 0x0201 );

    data = fcml_fn_stream_read_word( &stream, &result );
    STF_ASSERT( result == FCML_TRUE );
    STF_ASSERT( data == 0x0403 );

    data = fcml_fn_stream_read_word( &stream, &result );
    STF_ASSERT( result == FCML_TRUE );
    STF_ASSERT( data == 0x0605 );

    data = fcml_fn_stream_read_word( &stream, &result );
    STF_ASSERT( result == FCML_TRUE );
    STF_ASSERT( data == 0x0807 );

    data = fcml_fn_stream_read_word( &stream, &result );
    STF_ASSERT( result == FCML_FALSE );

    stream.base_address = buffer;
    stream.offset = 0;
    stream.size = 1;

    data = fcml_fn_stream_read_word( &stream, &result );
    STF_ASSERT( result == FCML_FALSE );

    stream.base_address = buffer;
    stream.offset = 0;
    stream.size = 0;

    data = fcml_fn_stream_read_word( &stream, &result );
    STF_ASSERT( result == FCML_FALSE );

    stream.base_address = buffer;
    stream.offset = 0;
    stream.size = 2;

    data = fcml_fn_stream_read_word( &stream, &result );
    STF_ASSERT( result == FCML_TRUE );
    STF_ASSERT( data == 0x0201 );
}

void fcml_tf_stream_write_word(void) {

    memset( buffer, 0, sizeof( buffer ) );

    fcml_st_memory_stream stream;
    stream.base_address = buffer;
    stream.offset = 0;
    stream.size = 8;

    fcml_bool result;
    result = fcml_fn_stream_write_word( &stream, 0x0201 );
    STF_ASSERT( result == FCML_TRUE );

    result = fcml_fn_stream_write_word( &stream, 0x0403 );
    STF_ASSERT( result == FCML_TRUE );

    result = fcml_fn_stream_write_word( &stream, 0x0605 );
    STF_ASSERT( result == FCML_TRUE );

    result = fcml_fn_stream_write_word( &stream, 0x0807 );
    STF_ASSERT( result == FCML_TRUE );

    result = fcml_fn_stream_write_word( &stream, 0x0F09 );
    STF_ASSERT( result == FCML_FALSE );

    STF_ASSERT(buffer[0] == 1);
    STF_ASSERT(buffer[1] == 2);
    STF_ASSERT(buffer[2] == 3);
    STF_ASSERT(buffer[3] == 4);
    STF_ASSERT(buffer[4] == 5);
    STF_ASSERT(buffer[5] == 6);
    STF_ASSERT(buffer[6] == 7);
    STF_ASSERT(buffer[7] == 8);

    stream.base_address = buffer;
    stream.offset = 0;
    stream.size = 0;

    result = fcml_fn_stream_write_word( &stream, 0x0102 );
    STF_ASSERT( result == FCML_FALSE );

    stream.base_address = buffer;
    stream.offset = 0;
    stream.size = 1;

    result = fcml_fn_stream_write_word( &stream, 0x0102 );
    STF_ASSERT( result == FCML_FALSE );

    stream.base_address = buffer;
    stream.offset = 0;
    stream.size = 2;

    result = fcml_fn_stream_write_word( &stream, 0x0A0B );
    STF_ASSERT( result == FCML_TRUE );

    STF_ASSERT(buffer[0] == 0x0B);
    STF_ASSERT(buffer[1] == 0x0A);
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
    fcml_uint32_t data;
    data = fcml_fn_stream_read_dword( &stream, &result );
    STF_ASSERT( result == FCML_TRUE );
    STF_ASSERT( data == 0x04030201 );

    data = fcml_fn_stream_read_dword( &stream, &result );
    STF_ASSERT( result == FCML_TRUE );
    STF_ASSERT( data == 0x08070605 );

    data = fcml_fn_stream_read_dword( &stream, &result );
    STF_ASSERT( result == FCML_FALSE );

    stream.base_address = buffer;
    stream.offset = 0;
    stream.size = 0;

    data = fcml_fn_stream_read_dword( &stream, &result );
    STF_ASSERT( result == FCML_FALSE );

    stream.base_address = buffer;
    stream.offset = 0;
    stream.size = 3;

    data = fcml_fn_stream_read_dword( &stream, &result );
    STF_ASSERT( result == FCML_FALSE );

    stream.base_address = buffer;
    stream.offset = 0;
    stream.size = 4;

    data = fcml_fn_stream_read_dword( &stream, &result );
    STF_ASSERT( result == FCML_TRUE );
    STF_ASSERT( data == 0x04030201 );

}

void fcml_tf_stream_write_dword(void) {

    memset( buffer, 0, sizeof( buffer ) );

    fcml_st_memory_stream stream;
    stream.base_address = buffer;
    stream.offset = 0;
    stream.size = 8;

    fcml_bool result;
    result = fcml_fn_stream_write_dword( &stream, 0x04030201 );
    STF_ASSERT( result == FCML_TRUE );

    result = fcml_fn_stream_write_dword( &stream, 0x08070605 );
    STF_ASSERT( result == FCML_TRUE );

    result = fcml_fn_stream_write_dword( &stream, 0x090A0B0C );
    STF_ASSERT( result == FCML_FALSE );

    STF_ASSERT(buffer[0] == 1);
    STF_ASSERT(buffer[1] == 2);
    STF_ASSERT(buffer[2] == 3);
    STF_ASSERT(buffer[3] == 4);
    STF_ASSERT(buffer[4] == 5);
    STF_ASSERT(buffer[5] == 6);
    STF_ASSERT(buffer[6] == 7);
    STF_ASSERT(buffer[7] == 8);

    stream.base_address = buffer;
    stream.offset = 0;
    stream.size = 0;

    result = fcml_fn_stream_write_dword( &stream, 0x01020304 );
    STF_ASSERT( result == FCML_FALSE );

    stream.base_address = buffer;
    stream.offset = 0;
    stream.size = 3;

    result = fcml_fn_stream_write_dword( &stream, 0x01020304 );
    STF_ASSERT( result == FCML_FALSE );

    stream.base_address = buffer;
    stream.offset = 0;
    stream.size = 4;

    result = fcml_fn_stream_write_dword( &stream, 0x0A0B0C0D );
    STF_ASSERT( result == FCML_TRUE );

    STF_ASSERT(buffer[0] == 0x0D);
    STF_ASSERT(buffer[1] == 0x0C);
    STF_ASSERT(buffer[2] == 0x0B);
    STF_ASSERT(buffer[3] == 0x0A);
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
    fcml_uint64_t data;
    data = fcml_fn_stream_read_qword( &stream, &result );
    STF_ASSERT( result == FCML_TRUE );
    STF_ASSERT( data == 0x0807060504030201 );

    data = fcml_fn_stream_read_qword( &stream, &result );
    STF_ASSERT( result == FCML_TRUE );
    STF_ASSERT( data == 0x000F0E0D0C0B0A09 );

    data = fcml_fn_stream_read_qword( &stream, &result );
    STF_ASSERT( result == FCML_FALSE );

    stream.base_address = buffer;
    stream.offset = 0;
    stream.size = 0;

    data = fcml_fn_stream_read_qword( &stream, &result );
    STF_ASSERT( result == FCML_FALSE );

    stream.base_address = buffer;
    stream.offset = 0;
    stream.size = 7;

    data = fcml_fn_stream_read_qword( &stream, &result );
    STF_ASSERT( result == FCML_FALSE );

    stream.base_address = buffer;
    stream.offset = 0;
    stream.size = 8;

    data = fcml_fn_stream_read_qword( &stream, &result );
    STF_ASSERT( result == FCML_TRUE );
    STF_ASSERT( data == 0x0807060504030201 );
}

void fcml_tf_stream_write_qword(void) {

    memset( buffer, 0, sizeof( buffer ) );

    fcml_st_memory_stream stream;
    stream.base_address = buffer;
    stream.offset = 0;
    stream.size = 16;

    fcml_bool result;
    result = fcml_fn_stream_write_qword( &stream, 0x0706050403020100 );
    STF_ASSERT( result == FCML_TRUE );

    result = fcml_fn_stream_write_qword( &stream, 0x0F0E0D0C0B0A0908 );
    STF_ASSERT( result == FCML_TRUE );

    result = fcml_fn_stream_write_qword( &stream, 0x0706050403020100 );
    STF_ASSERT( result == FCML_FALSE );

    STF_ASSERT(buffer[0] == 0);
    STF_ASSERT(buffer[1] == 1);
    STF_ASSERT(buffer[2] == 2);
    STF_ASSERT(buffer[3] == 3);
    STF_ASSERT(buffer[4] == 4);
    STF_ASSERT(buffer[5] == 5);
    STF_ASSERT(buffer[6] == 6);
    STF_ASSERT(buffer[7] == 7);

    STF_ASSERT(buffer[8] == 8);
    STF_ASSERT(buffer[9] == 9);
    STF_ASSERT(buffer[10] == 0x0A);
    STF_ASSERT(buffer[11] == 0x0B);
    STF_ASSERT(buffer[12] == 0x0C);
    STF_ASSERT(buffer[13] == 0x0D);
    STF_ASSERT(buffer[14] == 0x0E);
    STF_ASSERT(buffer[15] == 0x0F);

    stream.base_address = buffer;
    stream.offset = 0;
    stream.size = 0;

    result = fcml_fn_stream_write_qword( &stream, 0x0706050403020100 );
    STF_ASSERT( result == FCML_FALSE );

    stream.base_address = buffer;
    stream.offset = 0;
    stream.size = 7;

    result = fcml_fn_stream_write_qword( &stream, 0x0706050403020100 );
   STF_ASSERT( result == FCML_FALSE );

    stream.base_address = buffer;
    stream.offset = 0;
    stream.size = 8;

    memset(buffer, 0, sizeof(buffer));

    result = fcml_fn_stream_write_qword( &stream, 0x0706050403020100 );
    STF_ASSERT( result == FCML_TRUE );

    STF_ASSERT(buffer[0] == 0);
    STF_ASSERT(buffer[1] == 1);
    STF_ASSERT(buffer[2] == 2);
    STF_ASSERT(buffer[3] == 3);
    STF_ASSERT(buffer[4] == 4);
    STF_ASSERT(buffer[5] == 5);
    STF_ASSERT(buffer[6] == 6);
    STF_ASSERT(buffer[7] == 7);
}

void fcml_tf_stream_read_bytes(void) {

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

    fcml_uint8_t buff[4];

    fcml_uint64_t data = fcml_fn_stream_read_bytes( &stream, buff, sizeof( buff ) );
    STF_ASSERT( data == 4 );
    STF_ASSERT( buff[0] == 1 );
    STF_ASSERT( buff[1] == 2 );
    STF_ASSERT( buff[2] == 3 );
    STF_ASSERT( buff[3] == 4 );

    stream.size = 3;
    stream.offset = 0;

    memset( buff, 0, sizeof( buff ) );

    data = fcml_fn_stream_read_bytes( &stream, buff, 4 );
    STF_ASSERT( data == 3 );
    STF_ASSERT( buff[0] == 1 );
    STF_ASSERT( buff[1] == 2 );
    STF_ASSERT( buff[2] == 3 );
    STF_ASSERT( buff[3] == 0 );

    stream.size = 0;
    stream.offset = 0;

    memset( buff, 0, sizeof( buff ) );

    data = fcml_fn_stream_read_bytes( &stream, buff, 4 );
    STF_ASSERT( data == 0 );
}


void fcml_tf_stream_write_bytes(void) {

    memset( buffer, 0, sizeof( buffer ) );

    fcml_uint8_t buff[5];

    buff[0] = 1;
    buff[1] = 2;
    buff[2] = 3;
    buff[3] = 4;
    buff[4] = 5;

    fcml_st_memory_stream stream;
    stream.base_address = buffer;
    stream.offset = 0;
    stream.size = 16;

    fcml_uint64_t data = fcml_fn_stream_write_bytes( &stream, buff, sizeof( buff ) );
    STF_ASSERT( data == 5 );
    STF_ASSERT( buffer[0] == 1 );
    STF_ASSERT( buffer[1] == 2 );
    STF_ASSERT( buffer[2] == 3 );
    STF_ASSERT( buffer[3] == 4 );
    STF_ASSERT( buffer[4] == 5 );

    stream.size = 3;
    stream.offset = 0;

    memset( buffer, 0, sizeof( buffer ) );

    data = fcml_fn_stream_write_bytes( &stream, buff, sizeof( buff ) );
    STF_ASSERT( data == 3 );
    STF_ASSERT( buffer[0] == 1 );
    STF_ASSERT( buffer[1] == 2 );
    STF_ASSERT( buffer[2] == 3 );
    STF_ASSERT( buffer[3] == 0 );

    stream.size = 0;
    stream.offset = 0;

    memset( buff, 0, sizeof( buff ) );

    data = fcml_fn_stream_read_bytes( &stream, buff, 4 );
    STF_ASSERT( data == 0 );
}

void fcml_tf_stream_peek() {

    buffer[0] = 1;
    buffer[1] = 2;
    buffer[2] = 3;
    buffer[3] = 4;

    fcml_st_memory_stream stream;
    stream.base_address = buffer;
    stream.offset = 0;
    stream.size = 4;

    fcml_bool result;
    fcml_uint8_t data;
    data = fcml_fn_stream_read( &stream, &result );
    STF_ASSERT( result == FCML_TRUE );
    STF_ASSERT( data == 1 );
    STF_ASSERT( stream.offset == 1 );

    data = fcml_fn_stream_peek( &stream, &result );
    STF_ASSERT( result == FCML_TRUE );
    STF_ASSERT( data == 2 );
    STF_ASSERT( stream.offset == 1 );

}

void fcml_tf_stream_seek() {

    buffer[0] = 1;
    buffer[1] = 2;
    buffer[2] = 3;
    buffer[3] = 4;

    fcml_st_memory_stream stream;
    stream.base_address = buffer;
    stream.offset = 0;
    stream.size = 4;

    fcml_bool result;
    fcml_uint8_t data;
    data = fcml_fn_stream_read( &stream, &result );
    STF_ASSERT( result == FCML_TRUE );
    STF_ASSERT( data == 1 );
    STF_ASSERT( stream.offset == 1 );

    fcml_fn_stream_seek( &stream, 3, FCML_EN_ST_START );

    data = fcml_fn_stream_read( &stream, &result );
    STF_ASSERT( result == FCML_TRUE );
    STF_ASSERT( data == 4 );
    STF_ASSERT( stream.offset == 4 );

    fcml_fn_stream_seek( &stream, -3, FCML_EN_ST_CURRENT );

    data = fcml_fn_stream_read( &stream, &result );
    STF_ASSERT( result == FCML_TRUE );
    STF_ASSERT( data == 2 );
    STF_ASSERT( stream.offset == 2 );

    fcml_fn_stream_seek( &stream, -4, FCML_EN_ST_END );

    data = fcml_fn_stream_read( &stream, &result );
    STF_ASSERT( result == FCML_TRUE );
    STF_ASSERT( data == 1 );
    STF_ASSERT( stream.offset == 1 );

    fcml_fn_stream_seek( &stream, -8, FCML_EN_ST_END );
    STF_ASSERT( stream.offset == 0 );

    fcml_fn_stream_seek( &stream, 8, FCML_EN_ST_END );
    STF_ASSERT( stream.offset == 4 );

    fcml_fn_stream_seek( &stream, 8, FCML_EN_ST_START );
    STF_ASSERT( stream.offset == 4 );

}

void fcml_tf_stream_size() {

    fcml_st_memory_stream stream;
    stream.base_address = buffer;
    stream.offset = 0;
    stream.size = 4;

    fcml_int32_t size = fcml_fn_stream_size( &stream );
    STF_ASSERT( size == 4 );

    stream.size = 5;

    size = fcml_fn_stream_size( &stream );
    STF_ASSERT( size == 5 );

    stream.size = -1;

    size = fcml_fn_stream_size( &stream );
    STF_ASSERT( size == -1 );

    stream.size = 5;
    stream.offset = 3;

    size = fcml_fn_stream_size( &stream );
    STF_ASSERT( size == 2 );
}

void fcml_tf_stream_save_restore_point() {

    fcml_st_memory_stream stream;
    stream.base_address = buffer;
    stream.offset = 2;
    stream.size = 4;

    fcml_stream_pointer point = fcml_fn_stream_save_point( &stream );

    stream.offset = 1;

    fcml_fn_stream_restore_point( &stream, point );

    STF_ASSERT(stream.offset = 2);
}

fcml_stf_test_case fctl_ti_stream[] = {
	{ "fcml_tf_stream_read_byte", fcml_tf_stream_read_byte },
	{ "fcml_tf_stream_write_byte", fcml_tf_stream_write_byte },
	{ "fcml_tf_stream_read_word", fcml_tf_stream_read_word },
	{ "fcml_tf_stream_write_word", fcml_tf_stream_write_word },
	{ "fcml_tf_stream_read_dword", fcml_tf_stream_read_dword },
	{ "fcml_tf_stream_write_dword", fcml_tf_stream_write_dword },
	{ "fcml_tf_stream_read_qword", fcml_tf_stream_read_qword },
	{ "fcml_tf_stream_write_qword", fcml_tf_stream_write_qword },
	{ "fcml_tf_stream_read_bytes", fcml_tf_stream_read_bytes },
	{ "fcml_tf_stream_write_bytes", fcml_tf_stream_write_bytes },
	{ "fcml_tf_stream_peek", fcml_tf_stream_peek },
	{ "fcml_tf_stream_seek", fcml_tf_stream_seek },
	{ "fcml_tf_stream_size", fcml_tf_stream_size },
	{ "fcml_tf_stream_save_restore_point", fcml_tf_stream_save_restore_point },
	FCML_STF_NULL_TEST
};

fcml_stf_test_suite fctl_si_stream = {
	"suite-stream", fcml_tf_stream_suite_init, fcml_tf_stream_suite_cleanup, fctl_ti_stream
};


