/*
 * ira_ren_utils.h
 *
 *  Created on: 01-05-2011
 *      Author: tAs
 */

#ifndef IRA_REN_UTILS_H_
#define IRA_REN_UTILS_H_

#define _IRA_TRUE 1
#define _IRA_FALSE 0

#define _IRA_FORMAT_HEX		16
#define _IRA_FORMAT_DEC		10

#include "ira.h"

struct ira_format_info {
};

struct _ira_format_stream {
	// Buffer for formated instruction.
	char *buffer;
	// Size of the buffer.
	int size;
	// Current offset.
	int offset;
};

union _ira_integer_value {
	uint8_t v8;
	uint16_t v16;
	uint32_t v32;
	uint64_t v64;
};

struct _ira_integer {
	// Whether value is signed or not.
	uint8_t is_signed;
	// Value size 8, 16, 32, 64.
	uint8_t size;
	// Value itself.
	union _ira_integer_value value;
};

// Instruction used to build destination string with formated instruction.
void _ira_format_printf( struct _ira_format_stream *stream, const char *format, ... );

// Appends source stream to destination stream.
void _ira_format_append( struct _ira_format_stream *destination_stream, struct _ira_format_stream *source_stream );

// Appends source string to destination stream.
void _ira_format_append_str( struct _ira_format_stream *destination_stream, const char *source );

// Cleans stream.
void _ira_stream_clean( struct _ira_format_stream *stream );

// Append given register to stream.
void _ira_format_append_reg( struct _ira_format_stream *stream, struct ira_register *reg, uint8_t is_rex );

// Adds comma to the stream if needed.
void _ira_format_append_if_not_first( struct _ira_format_stream *stream, int *first, char *str );

// Prints integer value.
void _ira_format_append_integer( struct _ira_format_stream *stream, struct _ira_integer *integer, int format );

// Prints plain hex byte.
void _ira_format_append_hex_byte( struct _ira_format_stream *stream, uint8_t hex_byte );

// Extends given integer to given size with sign or not.
void _ira_extend_integer( struct _ira_integer *value, int extension_size, int sign_extend );

void _ira_format_append_code( struct _ira_format_stream *stream, uint8_t *instrunction_code, uint8_t instruction_size );

// Gets suffix for conditional instruction.
char* _ira_get_conditional_prefix( int group, int condition, int carry );

#endif /* IRA_REN_UTILS_H_ */
