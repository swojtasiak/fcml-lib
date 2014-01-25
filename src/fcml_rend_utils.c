/*
 * fcml_rend_utils.c
 *
 *  Created on: Oct 20, 2013
 *      Author: tas
 */

#include "fcml_rend_utils.h"

#include <ctype.h>
#include <inttypes.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#include "fcml_env.h"
#include "fcml_ceh.h"
#include "fcml_common.h"
#include "fcml_dialect.h"
#include "fcml_stream.h"
#include "fcml_types.h"

void fcml_fn_rend_utils_format_printf( fcml_st_memory_stream *stream, const fcml_string format, ...) {

	/* We'll never reach this limit.*/
	fcml_char local_buffer[512];

	va_list arg_list;
	va_start(arg_list, format);

	vsnprintf(local_buffer, sizeof( local_buffer ), format, arg_list);
	int part_size = strlen(local_buffer);
	if (part_size > stream->size - stream->offset - 1) {
		part_size = stream->size - stream->offset - 1;
	}

	strncpy( &(((fcml_char*)stream->base_address)[stream->offset]), local_buffer, part_size);

	stream->offset += part_size;
}

void fcml_fn_rend_utils_format_append_hex_byte( fcml_st_memory_stream *stream, fcml_uint8_t hex_byte ) {
	fcml_fn_rend_utils_format_printf( stream, FCML_PRI_INT8_HEX, hex_byte );
}

void fcml_fn_rend_utils_format_append_code( fcml_st_memory_stream *stream, fcml_uint8_t *instrunction_code, fcml_uint8_t instruction_code_size ) {
	fcml_int i;
	for( i = 0; i < instruction_code_size; i++ ) {
		fcml_fn_rend_utils_format_append_hex_byte( stream, instrunction_code[i] );
	}
}

void fcml_fn_rend_utils_format_append_str_if( fcml_st_memory_stream *stream, const fcml_string string, fcml_bool condition ) {
	if( condition ) {
		 fcml_fn_rend_utils_format_append_str( stream, string );
	}
}

void fcml_fn_rend_utils_format_finish_str( fcml_st_memory_stream *stream ) {
    int size = sizeof( FCML_TEXT( "\0" ) );
    if( fcml_fn_stream_size( stream ) >= size ) {
        strncpy( &(((fcml_char*)stream->base_address)[stream->offset]), FCML_TEXT( "\0" ), size );
        stream->offset += size;
    }
}

void fcml_fn_rend_utils_format_append_str( fcml_st_memory_stream *stream, const fcml_string source ) {

	fcml_int source_size;
	if( source == NULL || ( source_size = strlen( source ) ) == 0 ) {
		return;
	}

	fcml_int destination_size = stream->size - stream->offset;
	fcml_int n = ( destination_size < source_size ) ? destination_size : source_size;
	strncpy( &(((fcml_char*)stream->base_address)[stream->offset]), source, n );
	stream->offset += n;
}

void fcml_fn_rend_utils_format_append_stream( fcml_st_memory_stream *destination_stream, const fcml_st_memory_stream *source_stream ) {
	if( source_stream->offset == 0 ) {
		return;
	}
	fcml_int destination_size = destination_stream->size - destination_stream->offset;
	fcml_int n = ( destination_size < source_stream->offset ) ? destination_size : source_stream->offset;
	strncpy( &(((fcml_char*)destination_stream->base_address)[destination_stream->offset]), source_stream->base_address, n );
	destination_stream->offset += n;
}

fcml_ceh_error fcml_fn_rend_utils_format_append_integer( fcml_string patterns[4][4], fcml_st_memory_stream *stream, const fcml_st_integer *integer, fcml_bool is_hex ) {

	fcml_string *format;
	if( integer->is_signed ) {
		format = &(patterns[is_hex ? 2 : 0][0]);
	} else {
		format = &(patterns[is_hex ? 3 : 1][0]);
	}

	fcml_char local_buffer[32];

	switch( integer->size ) {
	case 8:
		snprintf( local_buffer, sizeof( local_buffer ), format[0], (fcml_uint8_t)integer->int8 );
		break;
	case 16:
		snprintf( local_buffer, sizeof( local_buffer ), format[1], (fcml_uint16_t)integer->int16 );
		break;
	case 32:
		snprintf( local_buffer, sizeof( local_buffer ), format[2], (fcml_uint32_t)integer->int32 );
		break;
	case 64:
		snprintf( local_buffer, sizeof( local_buffer ), format[3], (fcml_uint64_t)integer->int64 );
		break;
	default:
		return FCML_CEH_GEC_INVALID_INPUT;
	}

	/* Currently this logic desn't collide with AT&T dialect, so parameterization is not needed.*/
	if( is_hex && !isdigit( local_buffer[0] ) ) {
		fcml_fn_rend_utils_format_append_str( stream, "0" );
	}

	fcml_fn_rend_utils_format_append_str( stream, (fcml_string)local_buffer );

	return FCML_CEH_GEC_NO_ERROR;
}

void fcml_fn_rend_utils_format_append_reg( fcml_st_dialect_context_int *dialect_context, fcml_st_memory_stream *output_stream, const fcml_st_register *reg, fcml_bool is_rex ) {
	fcml_char printable_reg[64];
	dialect_context->get_register( reg, printable_reg, sizeof( printable_reg ), is_rex );
	fcml_fn_rend_utils_format_append_str( output_stream, printable_reg );
}
