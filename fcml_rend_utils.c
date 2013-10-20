/*
 * fcml_rend_utils.c
 *
 *  Created on: Oct 20, 2013
 *      Author: tas
 */

#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <inttypes.h>

#include "fcml_rend_utils.h"

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
