/*
 * ira_ren.c
 *
 *  Created on: 12-12-2010
 *      Author: Slawomir Wojtasiak
 */

#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#include "ira_ren.h"

struct _ira_format_stream {
	// Buffer for formated instruction.
	char *buffer;
	// Size of the buffer.
	int size;
	// Current offset.
	int offset;
};

// Instruction used to build destination string with formated instruction.
void _ira_format_printf( struct _ira_format_stream *stream, const char *format, ... );

/* Function used to format instructions using Intel syntax. */
void ira_format_intel_instruction( char *buffer, int size, struct ira_disassemble_result *result, struct ira_format_info *format_info ) {

	// Render mnemonic.
	struct _ira_format_stream stream = {0};
	stream.buffer = buffer;
	stream.size = size;
	stream.offset = 0;

	_ira_format_printf( &stream, "%s", result->mnemonic );

}

void _ira_format_printf( struct _ira_format_stream *stream, const char *format, ... ) {

	 va_list arg_list;
	 va_start(arg_list, format);

	 // We never reach this limit.
	 char local_buffer[512];
	 vsprintf( local_buffer, format, arg_list );

	 int part_size = strlen(local_buffer);

	 if( part_size > stream->size - stream->offset - 1 ) {
		 part_size = stream->size - stream->offset - 1;
	 }

	 strncpy( stream->buffer + stream->offset, local_buffer, part_size );

	 stream->offset += part_size;
}
