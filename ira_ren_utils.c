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
#include <ctype.h>

#include "ira_ren_utils.h"

// Suffixes for conditional instructions.

#define _IRA_CONST_STR_LOCK		"lock "

char* ira_ren_conditional_suffixes[2][16] = {
	{ "o", "no", "b", "nb", "e", "ne", "be", "nbe", "s", "ns", "p", "np", "l", "nl", "le", "nle" },
	{ "o", "no", "nae", "ae", "z", "nz", "na", "a", "s", "ns", "pe", "po", "nge", "ge", "ng", "g" }
};

char *_ira_reg_symbol_table[7][16] = {
	{ "<none>", "<none>", "<none>", "<none>", "<none>", "<none>", "<none>", "<none>", "<none>", "<none>", "<none>", "<none>", "<none>", "<none>", "<none>", "<none>" },
	{ "<unknown GPR>", "<unknown GPR>", "<unknown GPR>", "<unknown GPR>", "<unknown GPR>", "<unknown GPR>", "<unknown GPR>", "<unknown GPR>", "<unknown GPR>", "<unknown GPR>", "<unknown GPR>", "<unknown GPR>", "<unknown GPR>", "<unknown GPR>", "<unknown GPR>", "<unknown GPR>" },
	{ "<unknown SIMD>", "<unknown SIMD>", "<unknown SIMD>", "<unknown SIMD>", "<unknown SIMD>", "<unknown SIMD>", "<unknown SIMD>", "<unknown SIMD>", "<unknown SIMD>", "<unknown SIMD>", "<unknown SIMD>", "<unknown SIMD>", "<unknown SIMD>", "<unknown SIMD>", "<unknown SIMD>", "<unknown SIMD>" },
	{ "st(0)", "st(1)", "st(2)", "st(3)", "st(4)", "st(5)", "st(6)", "st(7)", "<unknown fpu>", "<unknown fpu>", "<unknown fpu>", "<unknown fpu>", "<unknown fpu>", "<unknown fpu>", "<unknown fpu>", "<unknown fpu>" },
	{ "es", "cs", "ss", "ds", "fs", "gs", "<unknown SR>", "<unknown SR>", "<unknown SR>", "<unknown SR>", "<unknown SR>", "<unknown SR>", "<unknown SR>", "<unknown SR>", "<unknown SR>", "<unknown SR>" },
	{ "cr0", "<unknown CR>", "cr2", "cr3", "cr4", "<unknown CR>", "<unknown CR>", "<unknown CR>", "cr8", "<unknown CR>", "<unknown CR>", "<unknown CR>", "<unknown CR>", "<unknown CR>", "<unknown CR>", "<unknown CR>" },
	{ "dr0", "dr1", "dr2", "dr3", "dr4", "dr5", "dr6", "dr7", "<unknown DR>", "<unknown DR>", "<unknown DR>", "<unknown DR>", "<unknown DR>", "<unknown DR>", "<unknown DR>", "<unknown DR>" }
};

char *_ira_reg_gpr_symbol_table[4][16] = {
	{ "al", "cl", "dl", "bl", "ah", "ch", "dh", "bh", "r8l", "r9l", "r10l", "r11l", "r12l", "r13l", "r14l", "r15l" },
	{ "ax", "cx", "dx", "bx", "sp", "bp", "si", "di", "r8w", "r9w", "r10w", "r11w", "r12w", "r13w", "r14w", "r15w" },
	{ "eax", "ecx", "edx", "ebx", "esp", "ebp", "esi", "edi", "r8d", "r9d", "r10d", "r11d", "r12d", "r13d", "r14d", "r15d" },
	{ "rax", "rcx", "rdx", "rbx", "rsp", "rbp", "rsi", "rdi", "r8", "r9", "r10", "r11", "r12", "r13", "r14", "r15" }
};

char *_ira_reg_symbol_table_rex[7][16] = {
	{ "<none>", "<none>", "<none>", "<none>", "<none>", "<none>", "<none>", "<none>", "<none>", "<none>", "<none>", "<none>", "<none>", "<none>", "<none>", "<none>" },
	{ "<unknown GPR>", "<unknown GPR>", "<unknown GPR>", "<unknown GPR>", "<unknown GPR>", "<unknown GPR>", "<unknown GPR>", "<unknown GPR>", "<unknown GPR>", "<unknown GPR>", "<unknown GPR>", "<unknown GPR>", "<unknown GPR>", "<unknown GPR>", "<unknown GPR>", "<unknown GPR>" },
	{ "<unknown SIMD>", "<unknown SIMD>", "<unknown SIMD>", "<unknown SIMD>", "<unknown SIMD>", "<unknown SIMD>", "<unknown SIMD>", "<unknown SIMD>", "<unknown SIMD>", "<unknown SIMD>", "<unknown SIMD>", "<unknown SIMD>", "<unknown SIMD>", "<unknown SIMD>", "<unknown SIMD>", "<unknown SIMD>" },
	{ "st(0)", "st(1)", "st(2)", "st(3)", "st(4)", "st(5)", "st(6)", "st(7)", "<unknown fpu>", "<unknown fpu>", "<unknown fpu>", "<unknown fpu>", "<unknown fpu>", "<unknown fpu>", "<unknown fpu>", "<unknown fpu>" },
	{ "es", "cs", "ss", "ds", "fs", "gs", "<unknown SR>", "<unknown SR>", "<unknown SR>", "<unknown SR>", "<unknown SR>", "<unknown SR>", "<unknown SR>", "<unknown SR>", "<unknown SR>", "<unknown SR>" },
	{ "cr0", "<unknown CR>", "cr2", "cr3", "cr4", "<unknown CR>", "<unknown CR>", "<unknown CR>", "cr8", "<unknown CR>", "<unknown CR>", "<unknown CR>", "<unknown CR>", "<unknown CR>", "<unknown CR>", "<unknown CR>" },
	{ "dr0", "dr1", "dr2", "dr3", "dr4", "dr5", "dr6", "dr7", "<unknown DR>", "<unknown DR>", "<unknown DR>", "<unknown DR>", "<unknown DR>", "<unknown DR>", "<unknown DR>", "<unknown DR>" }
};

char *_ira_reg_gpr_symbol_table_rex[4][16] = {
	{ "al", "cl", "dl", "bl", "spl", "bpl", "sil", "dil", "r8l", "r9l", "r10l", "r11l", "r12l", "r13l", "r14l", "r15l" },
	{ "ax", "cx", "dx", "bx", "sp", "bp", "si", "di", "r8w", "r9w", "r10w", "r11w", "r12w", "r13w", "r14w", "r15w" },
	{ "eax", "ecx", "edx", "ebx", "esp", "ebp", "esi", "edi", "r8d", "r9d", "r10d", "r11d", "r12d", "r13d", "r14d", "r15d" },
	{ "rax", "rcx", "rdx", "rbx", "rsp", "rbp", "rsi", "rdi", "r8", "r9", "r10", "r11", "r12", "r13", "r14", "r15" }
};

char *_ira_reg_sidm_symbol_table[3][16] = {
	{ "mm0", "mm1", "mm2", "mm3", "mm4", "mm5", "mm6", "mm7", "<wrong register>", "<wrong register>", "<wrong register>", "<wrong register>", "<wrong register>", "<wrong register>", "<wrong register>", "<wrong register>" },
	{ "xmm0", "xmm1", "xmm2", "xmm3", "xmm4", "xmm5", "xmm6", "xmm7", "xmm8", "xmm9", "xmm10", "xmm11", "xmm12", "xmm13", "xmm14", "xmm15" },
	{ "ymm0", "ymm1", "ymm2", "ymm3", "ymm4", "ymm5", "ymm6", "ymm7", "ymm8", "ymm9", "ymm10", "ymm11", "ymm12", "ymm13", "ymm14", "ymm15" }
};

char *_ira_integer_formats[4][4] = {
	// Signed integer values.
	{"%"PRId8, "%"PRId16, "%"PRId32, "%"PRId64},
	// Unsigned integer values.
	{"%"PRIu8, "%"PRIu16, "%"PRIu32, "%"PRIu64},
	// Signed hex values.
	{"%02"PRIx8"h", "%04"PRIx16"h", "%08"PRIx32"h", "%016"PRIx64"h"},
	// Unsigned hex values.
	{"%02"PRIx8"h", "%04"PRIx16"h", "%08"PRIx32"h", "%016"PRIx64"h"}
};

char* _ira_get_conditional_prefix( int group, int condition, int carry ) {
	if( carry ) {
		if( condition == 2 ) {
			return "c";
		} else if( condition == 3 ) {
			return "nc";
		}
	}
	return ira_ren_conditional_suffixes[group][condition];

}

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

void _ira_format_printf(struct _ira_format_stream *stream, const char *format, ...) {

	// We'll never reach this limit.
	char local_buffer[512];

	va_list arg_list;
	va_start(arg_list, format);

	vsprintf(local_buffer, format, arg_list);
	int part_size = strlen(local_buffer);
	if (part_size > stream->size - stream->offset - 1) {
		part_size = stream->size - stream->offset - 1;
	}
	strncpy(stream->buffer + stream->offset, local_buffer, part_size);
	stream->offset += part_size;
}

// Append given register to stream.
void _ira_format_append_reg( struct _ira_format_stream *stream, struct ira_register *reg, uint8_t is_rex ) {
	int rs = 0;
	if( reg->reg_type != IRA_REG_SIMD ) {
		switch( reg->reg_size ) {
		case 8:
			rs = 0;
			break;
		case 16:
			rs = 1;
			break;
		case 32:
			rs = 2;
			break;
		case 64:
			rs = 3;
			break;
		}
		if( is_rex ) {
			// TODO: a vex i xop?
			if( reg->reg_type == IRA_REG_GPR ) {
				_ira_format_append_str( stream, _ira_reg_gpr_symbol_table_rex[rs][reg->reg] );
			} else {
				_ira_format_append_str( stream, _ira_reg_symbol_table_rex[reg->reg_type][reg->reg] );
			}
		} else {
			if( reg->reg_type == IRA_REG_GPR ) {
				_ira_format_append_str( stream, _ira_reg_gpr_symbol_table[rs][reg->reg] );
			} else {
				_ira_format_append_str( stream, _ira_reg_symbol_table[reg->reg_type][reg->reg] );
			}
		}
	} else {
		switch( reg->reg_size ) {
		case 64:
			rs = 0;
			break;
		case 128:
			rs = 1;
			break;
		case 256:
			rs = 2;
			break;
		}
		_ira_format_append_str( stream, _ira_reg_sidm_symbol_table[rs][reg->reg] );
		return;
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

// Prints integer value.
void _ira_format_append_integer( struct _ira_format_stream *stream, struct _ira_integer *integer, int format ) {

	int format_pos = integer->size / 16;
	if( format_pos == 4 ) {
		format_pos = 3;
	}

	char *value_format = _ira_integer_formats[ ( integer->is_signed ? 0 : 1 ) + ( ( format == _IRA_FORMAT_DEC ) ? 0 : 1 ) * 2 ][ format_pos ];

	char local_buffer[32];

	// Hex values should be always treated as unsigned.
	if( integer->is_signed && format == _IRA_FORMAT_DEC ) {

		switch(integer->size) {
		case 8:
			sprintf( local_buffer, value_format, (int8_t)integer->value.v8 );
			break;
		case 16:
			sprintf( local_buffer, value_format, (int16_t)integer->value.v16 );
			break;
		case 32:
			sprintf( local_buffer, value_format, (int32_t)integer->value.v32 );
			break;
		case 64:
			sprintf( local_buffer, value_format, (int64_t)integer->value.v64 );
			break;
		}

	} else {

		switch(integer->size) {
		case 8:
			sprintf( local_buffer, value_format, integer->value.v8 );
			break;
		case 16:
			sprintf( local_buffer, value_format, integer->value.v16 );
			break;
		case 32:
			sprintf( local_buffer, value_format, integer->value.v32 );
			break;
		case 64:
			sprintf( local_buffer, value_format, integer->value.v64 );
			break;
		}

	}

	// If value doesn't start with a digit add 0 at the beginning.
	if( format == _IRA_FORMAT_HEX && !isdigit( local_buffer[0] ) ) {
		_ira_format_append_str( stream, "0" );
	}

	_ira_format_append_str( stream, local_buffer );
}

// Extends given integer to given size with sign or not.
void _ira_extend_integer( struct _ira_integer *value, int extension_size, int sign_extend ) {

	if( sign_extend ) {

		int64_t temp_int = 0;

		switch( value->size ) {
		case 8:
			temp_int = (int64_t)((int8_t)value->value.v8);
			break;
		case 16:
			temp_int = (int64_t)((int16_t)value->value.v16);
			break;
		case 32:
			temp_int = (int64_t)((int32_t)value->value.v32);
			break;
		case 64:
			temp_int = (int64_t)value->value.v64;
			break;
		}

		value->value.v64 = 0;

		switch( extension_size ) {
		case 8:
			value->value.v8 = (int8_t)temp_int;
			break;
		case 16:
			value->value.v16 = (int16_t)temp_int;
			break;
		case 32:
			value->value.v32 = (int32_t)temp_int;
			break;
		case 64:
			value->value.v64 = (int64_t)temp_int;
			break;
		}

	} else {

		uint64_t temp_int = 0;

		switch( value->size ) {
		case 8:
			temp_int = (uint64_t)value->value.v8;
			break;
		case 16:
			temp_int = (uint64_t)value->value.v16;
			break;
		case 32:
			temp_int = (uint64_t)value->value.v32;
			break;
		case 64:
			temp_int = (uint64_t)value->value.v64;
			break;
		}

		value->value.v64 = 0;

		switch( extension_size ) {
		case 8:
			value->value.v8 = (uint8_t)temp_int;
			break;
		case 16:
			value->value.v16 = (uint16_t)temp_int;
			break;
		case 32:
			value->value.v32 = (uint32_t)temp_int;
			break;
		case 64:
			value->value.v64 = (uint64_t)temp_int;
			break;
		}
	}

	value->size = extension_size;
}

void _ira_format_append_prefixes( struct _ira_format_stream *stream, struct ira_instruction_prefix *prefixes, uint8_t prefixes_count ) {
	struct ira_instruction_prefix *prefix;
	if( prefixes_count > 0 ) {
		int i;
		for( i = 0; i < prefixes_count; i++ ) {
			prefix = &prefixes[i];
			if( !prefix->mandatory_prefix && prefix->prefix == _IRA_PREFIX_LOCK ) {
				_ira_format_append_str( stream, _IRA_CONST_STR_LOCK );
			}
		}
	}
}

void _ira_format_append_hex_byte( struct _ira_format_stream *stream, uint8_t hex_byte ) {
	_ira_format_printf( stream, "%02"PRIx8, hex_byte );
}

void _ira_format_append_code( struct _ira_format_stream *stream, uint8_t *instrunction_code, uint8_t instruction_size ) {
	int i;
	for( i = 0; i < instruction_size; i++ ) {
		_ira_format_append_hex_byte( stream, instrunction_code[i] );
	}
}
