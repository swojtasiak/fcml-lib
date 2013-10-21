/*
 * fcml_rend_utils.c
 *
 *  Created on: Oct 20, 2013
 *      Author: tas
 */

#include "fcml_rend_utils.h"

//#include <ctype.h>
#include <inttypes.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#include "fcml_ceh.h"
#include "fcml_stream.h"
#include "fcml_types.h"

void fcml_fn_rend_utils_format_printf( fcml_st_memory_stream *stream, const fcml_string format, ...) {

	// We'll never reach this limit.
	fcml_char local_buffer[512];

	// TODO: Some of these functions might be platform specific, it would be probably a good idea to move it to the fcml_env.h.
	va_list arg_list;
	va_start(arg_list, format);

	vsnprintf(local_buffer, sizeof( local_buffer ), format, arg_list);
	int part_size = strlen(local_buffer);
	if (part_size > stream->size - stream->offset - 1) {
		part_size = stream->size - stream->offset - 1;
	}

	strncpy(stream->base_address + stream->offset, local_buffer, part_size);
	stream->offset += part_size;

}

void fcml_fn_rend_utils_format_append_hex_byte( fcml_st_memory_stream *stream, fcml_uint8_t hex_byte ) {
	// TODO: environment specific formating.
	fcml_fn_rend_utils_format_printf( stream, "%02"PRIx8, hex_byte );
}

void fcml_fn_rend_utils_format_append_code( fcml_st_memory_stream *stream, fcml_uint8_t *instrunction_code, uint8_t instruction_code_size ) {
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

void fcml_fn_rend_utils_format_append_str( fcml_st_memory_stream *stream, const fcml_string source ) {

	fcml_int source_size;
	if( source == NULL || ( source_size = strlen( source ) ) == 0 ) {
		return;
	}

	fcml_int destination_size = stream->size - stream->offset;
	fcml_int n = ( destination_size < source_size ) ? destination_size : source_size;
	strncpy( stream->base_address + stream->offset, source, n );
	stream->offset += n;
}

void fcml_fn_rend_utils_format_append_stream( fcml_st_memory_stream *destination_stream, fcml_st_memory_stream *source_stream ) {
	if( source_stream->offset == 0 ) {
		return;
	}
	fcml_int destination_size = destination_stream->size - destination_stream->offset;
	fcml_int n = ( destination_size < source_stream->offset ) ? destination_size : source_stream->offset;
	strncpy( destination_stream->base_address + destination_stream->offset, source_stream->base_address, n );
	destination_stream->offset += n;
}

fcml_string fcml_ar_rend_utils_integer_formats[4][4] = {
	// Signed integer values.
	{"%"PRId8, "%"PRId16, "%"PRId32, "%"PRId64},
	// Unsigned integer values.
	{"%"PRIu8, "%"PRIu16, "%"PRIu32, "%"PRIu64},
	// Signed hex values.
	{"%02"PRIx8"h", "%04"PRIx16"h", "%08"PRIx32"h", "%016"PRIx64"h"},
	// Unsigned hex values.
	{"%02"PRIx8"h", "%04"PRIx16"h", "%08"PRIx32"h", "%016"PRIx64"h"}
};

fcml_ceh_error fcml_fn_rend_utils_format_append_integer( fcml_st_memory_stream *stream, fcml_st_integer *integer, fcml_bool is_hex ) {

	fcml_string *format;
	if( integer->is_signed ) {
		format = &(fcml_ar_rend_utils_integer_formats[is_hex ? 2 : 0][0]);
	} else {
		format = &(fcml_ar_rend_utils_integer_formats[is_hex ? 3 : 1][0]);
	}

	fcml_char local_buffer[32];

	switch( integer->size ) {
	case 8:
		snprintf( local_buffer, sizeof( local_buffer ), format[0], integer->int8 );
		break;
	case 16:
		snprintf( local_buffer, sizeof( local_buffer ), format[1], integer->int16 );
		break;
	case 32:
		snprintf( local_buffer, sizeof( local_buffer ), format[2], integer->int32 );
		break;
	case 64:
		snprintf( local_buffer, sizeof( local_buffer ), format[3], integer->int64 );
		break;
	default:
		return FCML_CEH_GEC_INVALID_INPUT;
	}

	fcml_fn_rend_utils_format_append_str( stream, (fcml_string)local_buffer );

	return FCML_CEH_GEC_NO_ERROR;
}

void fcml_fn_rend_utils_format_append_reg( fcml_st_dialect_context *dialect_context, fcml_st_memory_stream *output_stream, fcml_st_register *reg, fcml_bool is_rex ) {
	fcml_string printable_reg;
	dialect_context->get_register( reg, &printable_reg, is_rex );
	fcml_fn_rend_utils_format_append_str( output_stream, printable_reg );
}
