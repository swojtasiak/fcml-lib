/*
 * Default instruction renderer compatible with Intel instruction format.
 *
 * ira_ren.c
 *
 *  Created on: 12-12-2010
 *      Author: Slawomir Wojtasiak
 */

#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#include "ira_ren.h"

#define _IRA_TRUE 1
#define _IRA_FALSE 0

#define _IRA_LOCAL_BUFFER_SIZE 512

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

// Appends source stream to destination stream.
void _ira_format_append( struct _ira_format_stream *destination_stream, struct _ira_format_stream *source_stream );

// Appends source string to destination stream.
void _ira_format_append_str( struct _ira_format_stream *destination_stream, const char *source );

// Cleans stream.
void _ira_stream_clean( struct _ira_format_stream *stream );

int _ira_format_print_operand( struct ira_instruction_operand *operand, struct _ira_format_stream *stream ) {

	return _IRA_TRUE;
}

/* Function used to format instructions using Intel syntax. */
void ira_format_intel_instruction( char *buffer, int size, struct ira_disassemble_result *result, struct ira_format_info *format_info ) {

	int i;
	char local_buffer[_IRA_LOCAL_BUFFER_SIZE] = {0};

	// Render mnemonic.
	struct _ira_format_stream stream;
	stream.buffer = buffer;
	stream.size = size;
	stream.offset = 0;

	// Local stream.
	struct _ira_format_stream local_stream;
	stream.buffer = local_buffer;
	stream.size = _IRA_LOCAL_BUFFER_SIZE;
	stream.offset = 0;

	// Add mnemonic.
	_ira_format_printf( &stream, "%s", result->mnemonic );

	// Add all operands.
	for( i = 0; i < _IRA_OPERANDS_COUNT; i++ ) {
		int res = _ira_format_print_operand( &result->operands[i], &local_stream );
		if( res ) {
			if( i < 0 ) {
				_ira_format_append_str( &stream, "," );
			}
			_ira_format_append( &stream, &local_stream );
			_ira_stream_clean(&local_stream);
		}
	}

}

void _ira_format_append_str( struct _ira_format_stream *destination_stream, const char *source ) {
	int source_size = strlen( source );
	int destination_size = destination_stream->size - destination_stream->offset;
	int n = ( destination_size < source_size ) ? destination_size : source_size;
	strncpy( destination_stream->buffer + destination_stream->offset, source, n );
	destination_stream->offset += n;
}

void _ira_format_append( struct _ira_format_stream *destination_stream, struct _ira_format_stream *source_stream ) {
	int destination_size = destination_stream->size - destination_stream->offset;
	int n = ( destination_size < source_stream->offset ) ? destination_size : source_stream->offset;
	strncpy( destination_stream->buffer + destination_stream->offset, source_stream->buffer, n );
	destination_stream->offset += n;
}

void _ira_stream_clean( struct _ira_format_stream *stream ) {
	stream->offset = 0;
	stream->buffer[0] = '\0';
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
