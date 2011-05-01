/*
 * ira_ren_utils.c
 *
 *  Created on: 01-05-2011
 *      Author: Slawomir Wojtasiak
 */

#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include <inttypes.h>

#include "ira_ren_utils.h"

char *_ira_reg_type_table[8][18] = {
	{ "<none>", "<none>", "<none>", "<none>", "<none>", "<none>", "<none>", "<none>", "<none>", "<none>", "<none>", "<none>", "<none>", "<none>", "<none>", "<none>" },
	{ "al", "bl", "cl", "dl", "ah", "bh", "ch", "dh", "r8l", "r9l", "r10l", "r11l", "r12l", "r13l", "r14l", "r15l" },
	{ "ax", "bx", "cx", "dx", "di", "si", "bp", "sp", "r8w", "r9w", "r10w", "r11w", "r12w", "r13w", "r14w", "r15w" },
	{ "eax", "ebx", "ecx", "edx", "edi", "esi", "ebp", "esp", "r8d", "r9d", "r10d", "r11d", "r12d", "r13d", "r14d", "r15d" },
	{ "rax", "rbx", "rcx", "rdx", "rdi", "rsi", "rbp", "rsp", "r8", "r9", "r10", "r11", "r12", "r13", "r14", "r15" },
	{ "mm0", "mm1", "mm2", "mm3", "mm4", "mm5", "mm6", "mm7", "<wrong register>", "<wrong register>", "<wrong register>", "<wrong register>", "<wrong register>", "<wrong register>", "<wrong register>", "<wrong register>" },
	{ "xmm0", "xmm1", "xmm2", "xmm3", "xmm4", "xmm5", "xmm6", "xmm7", "xmm8", "xmm9", "xmm10", "xmm11", "xmm12", "xmm13", "xmm14", "xmm15" },
	{ "<unknown GPR>", "<unknown GPR>", "<unknown GPR>", "<unknown GPR>", "<unknown GPR>", "<unknown GPR>", "<unknown GPR>", "<unknown GPR>", "<unknown GPR>", "<unknown GPR>", "<unknown GPR>", "<unknown GPR>", "<unknown GPR>", "<unknown GPR>", "<unknown GPR>", "<unknown GPR>" }
};

char *_ira_reg_type_table_rex[8][18] = {
	{ "<none>", "<none>", "<none>", "<none>", "<none>", "<none>", "<none>", "<none>", "<none>", "<none>", "<none>", "<none>", "<none>", "<none>", "<none>", "<none>" },
	{ "al", "bl", "cl", "dl", "dil", "sil", "bpl", "spl", "r8l", "r9l", "r10l", "r11l", "r12l", "r13l", "r14l", "r15l" },
	{ "ax", "bx", "cx", "dx", "di", "si", "bp", "sp", "r8w", "r9w", "r10w", "r11w", "r12w", "r13w", "r14w", "r15w" },
	{ "eax", "ebx", "ecx", "edx", "edi", "esi", "ebp", "esp", "r8d", "r9d", "r10d", "r11d", "r12d", "r13d", "r14d", "r15d" },
	{ "rax", "rbx", "rcx", "rdx", "rdi", "rsi", "rbp", "rsp", "r8", "r9", "r10", "r11", "r12", "r13", "r14", "r15" },
	{ "mm0", "mm1", "mm2", "mm3", "mm4", "mm5", "mm6", "mm7", "<wrong register>", "<wrong register>", "<wrong register>", "<wrong register>", "<wrong register>", "<wrong register>", "<wrong register>", "<wrong register>" },
	{ "xmm0", "xmm1", "xmm2", "xmm3", "xmm4", "xmm5", "xmm6", "xmm7", "xmm8", "xmm9", "xmm10", "xmm11", "xmm12", "xmm13", "xmm14", "xmm15" },
	{ "<unknown GPR>", "<unknown GPR>", "<unknown GPR>", "<unknown GPR>", "<unknown GPR>", "<unknown GPR>", "<unknown GPR>", "<unknown GPR>", "<unknown GPR>", "<unknown GPR>", "<unknown GPR>", "<unknown GPR>", "<unknown GPR>", "<unknown GPR>", "<unknown GPR>", "<unknown GPR>" }
};

char *_ira_integer_formats[4][4] = {
	// Signed integer values.
	{"%"PRId8, "%"PRId16, "%"PRId32, "%"PRId64},
	// Unsigned integer values.
	{"%"PRIu8, "%"PRIu16, "%"PRIu32, "%"PRIu64},
	// Signed hex values.
	{"%02"PRIx8, "%04"PRIx16, "%08"PRIx32, "%016"PRIx64},
	// Unsigned hex values.
	{"%02"PRIx8, "%04"PRIx16, "%08"PRIx32, "%016"PRIx64}
};

void _ira_format_append_str( struct _ira_format_stream *destination_stream, const char *source ) {

	int source_size;
	if( source == NULL || ( source_size = strlen( source ) ) == 0 ) {
		return;
	}

	int destination_size = destination_stream->size - destination_stream->offset;
	int n = ( destination_size < source_size ) ? destination_size : source_size;
	strncpy( destination_stream->buffer + destination_stream->offset, source, n );
	destination_stream->offset += n;
}

void _ira_format_append( struct _ira_format_stream *destination_stream, struct _ira_format_stream *source_stream ) {

	if( source_stream->offset == 0 ) {
		return;
	}

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

	 // We'll never reach this limit.
	 char local_buffer[512];
	 vsprintf( local_buffer, format, arg_list );

	 int part_size = strlen(local_buffer);

	 if( part_size > stream->size - stream->offset - 1 ) {
		 part_size = stream->size - stream->offset - 1;
	 }

	 strncpy( stream->buffer + stream->offset, local_buffer, part_size );

	 stream->offset += part_size;
}

// Append given register to stream.
void _ira_format_append_reg( struct _ira_format_stream *stream, struct ira_register *reg, uint8_t is_rex ) {
	if( is_rex ) {
		_ira_format_append_str( stream, _ira_reg_type_table_rex[reg->reg_type][reg->reg] );
	} else {
		_ira_format_append_str( stream, _ira_reg_type_table[reg->reg_type][reg->reg] );
	}
}

// Adds comma to the stream if needed.
void _ira_format_append_if_not_first( struct _ira_format_stream *stream, int *first, char *str ) {
	if( !*first ) {
		_ira_format_append_str( stream, str );
	} else {
		*first = _IRA_FALSE;
	}
}

void _ira_format_append_integer( struct _ira_format_stream *stream, struct _ira_integer *integer, int format ) {

	char *value_format = _ira_integer_formats[ ( integer->is_signed ? 1 : 0 ) + ( ( format == 10 ) ? 0 : 1 ) ][integer->size / 8];

	if( integer->is_signed ) {
		switch(integer->size) {
		case 8:
			_ira_format_printf( stream, value_format, (signed)integer->value.v8 );
			break;
		case 16:
			_ira_format_printf( stream, value_format, (signed)integer->value.v16 );
			break;
		case 32:
			_ira_format_printf( stream, value_format, (signed)integer->value.v32 );
			break;
		case 64:
			_ira_format_printf( stream, value_format, (signed)integer->value.v64 );
			break;
		}
	} else {
		switch(integer->size) {
		case 8:
			_ira_format_printf( stream, value_format, integer->value.v8 );
			break;
		case 16:
			_ira_format_printf( stream, value_format, integer->value.v16 );
			break;
		case 32:
			_ira_format_printf( stream, value_format, integer->value.v32 );
			break;
		case 64:
			_ira_format_printf( stream, value_format, integer->value.v64 );
			break;
		}
	}
}
