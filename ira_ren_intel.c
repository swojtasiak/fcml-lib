/*
 * Default instruction renderer compatible with Intel instruction format.
 *
 * ira_ren.c
 *
 *  Created on: 12-12-2010
 *      Author: Slawomir Wojtasiak
 */

#include <stdio.h>

#include "ira_ren_intel.h"

#define _IRA_LOCAL_BUFFER_SIZE 512

// Operand formating methods.

typedef void (*_ira_operand_formater)( struct ira_disassemble_result *result, struct ira_intel_format_info *format_info, struct ira_instruction_operand *operand, struct _ira_format_stream *stream );

void _ira_operand_formater_addressing( struct ira_disassemble_result *result, struct ira_intel_format_info *format_info, struct ira_instruction_operand *operand, struct _ira_format_stream *stream );
void _ira_operand_formater_immediate( struct ira_disassemble_result *result, struct ira_intel_format_info *format_info, struct ira_instruction_operand *operand, struct _ira_format_stream *stream );
void _ira_operand_formater_register( struct ira_disassemble_result *result, struct ira_intel_format_info *format_info, struct ira_instruction_operand *operand, struct _ira_format_stream *stream );
void _ira_operand_formater_addressing_modrm( struct ira_disassemble_result *result, struct ira_intel_format_info *format_info, struct ira_instruction_operand *operand, struct _ira_format_stream *stream );

/* Maps operand type to formating function. */
_ira_operand_formater _ira_formating_table[] = {
	NULL, // IRA_NONE
	&_ira_operand_formater_addressing, // IRA_ADDRESS
	&_ira_operand_formater_immediate, // IRA_IMMEDIATE_DATA
	&_ira_operand_formater_register // IRA_REGISTER
};

int _ira_format_print_operand( struct ira_disassemble_result *result, struct ira_intel_format_info *format_info, struct ira_instruction_operand *operand, struct _ira_format_stream *stream ) {
	int res = _IRA_FALSE;
	_ira_operand_formater operand_formater = _ira_formating_table[operand->operand_type];
	if( operand_formater != NULL ) {
		operand_formater( result, format_info, operand, stream );
		res = _IRA_TRUE;
	}
	return res;
}

/* Function used to format instructions using Intel syntax. */
void ira_format_intel_instruction( char *buffer, int size, struct ira_disassemble_result *result, struct ira_intel_format_info *format_info ) {

	int i;
	char local_buffer[_IRA_LOCAL_BUFFER_SIZE] = {0};

	// Render mnemonic.
	struct _ira_format_stream stream;
	stream.buffer = buffer;
	stream.size = size;
	stream.offset = 0;

	// Local stream.
	struct _ira_format_stream local_stream;
	local_stream.buffer = local_buffer;
	local_stream.size = _IRA_LOCAL_BUFFER_SIZE;
	local_stream.offset = 0;

	// Instruction code.
	if( format_info->show_instruction_code ) {
		_ira_format_append_code( &stream, result->instruction_code, result->instruction_size );
		_ira_format_append_str( &stream, " " );
	}

	// Add mnemonic.
	_ira_format_printf( &stream, "%s ", result->mnemonic );

	// Add all operands.
	for( i = 0; i < _IRA_OPERANDS_COUNT; i++ ) {
		int res = _ira_format_print_operand( result, format_info, &result->operands[i], &local_stream );
		if( res ) {
			if( i > 0 ) {
				_ira_format_append_str( &stream, "," );
			}
			_ira_format_append( &stream, &local_stream );
			_ira_stream_clean(&local_stream);
		} else {
			break;
		}
	}
}

/* Operand formating functions. */

void _ira_operand_formater_addressing( struct ira_disassemble_result *result, struct ira_intel_format_info *format_info, struct ira_instruction_operand *operand, struct _ira_format_stream *stream ) {
	switch( operand->addressing.addressing_type ) {
	case IRA_MOD_RM:
		_ira_operand_formater_addressing_modrm( result, format_info, operand, stream );
		break;
	case IRA_IMMEDIATE_ADDRESS:
		break;
	case IRA_RELATIVE_ADDRESS:
		break;
	}
}

void _ira_operand_formater_addressing_modrm( struct ira_disassemble_result *result, struct ira_intel_format_info *format_info, struct ira_instruction_operand *operand, struct _ira_format_stream *stream ) {

	struct ira_addressing *addressing = &operand->addressing;
	struct ira_mod_rm_addressing *mod_rm = &addressing->mod_rm;

	int first = _IRA_TRUE;

	switch( addressing->size_directive ) {
	case 8:
		_ira_format_append_str( stream, "byte ptr " );
		break;
	case 16:
		_ira_format_append_str( stream, "word ptr " );
		break;
	case 32:
		_ira_format_append_str( stream, "dword ptr " );
		break;
	case 64:
		_ira_format_append_str( stream, "qword ptr " );
		break;
	case 128:
		_ira_format_append_str( stream, "oword ptr " );
		break;
	default:
		// TODO: Maybe we should write size here?
		_ira_format_append_str( stream, "unknown size ptr " );
	}

	_ira_format_append_str( stream, "[" );

	// Append base register.
	if( mod_rm->base_reg.reg_type != IRA_NO_REG ) {
		_ira_format_append_reg( stream, &mod_rm->base_reg, result->rex.is_not_null );
		first = _IRA_FALSE;
	}

	// Append index register.
	if( mod_rm->index_reg.reg_type != IRA_NO_REG ) {
		_ira_format_append_if_not_first( stream, &first, "+" );
		_ira_format_append_reg( stream, &mod_rm->index_reg, result->rex.is_not_null );
	}

	// Append scale.
	if( mod_rm->scale.is_not_null && mod_rm->scale.value > 0 ) {
		_ira_format_append_if_not_first( stream, &first, "*" );

		struct _ira_integer scale_value = {0};
		scale_value.is_signed = _IRA_FALSE;
		scale_value.size = 8;
		scale_value.value.v8 = mod_rm->scale.value;

		// 10 means decimal.
		_ira_format_append_integer( stream, &scale_value, 10 );
	}

	// Append displacement.
	if( mod_rm->displacement.displacement_type != IRA_NO_DISPLACEMENT
			&& ( format_info->show_zero_displacement || mod_rm->displacement.displacement.displacement_32 != 0 ) ) {

		_ira_format_append_if_not_first( stream, &first, "+" );

		// Treat displacement like a plain integer value.
		struct _ira_integer displacement_value = {0};
		displacement_value.is_signed = _IRA_TRUE;
		displacement_value.size = mod_rm->displacement.displacement_type;

		switch(mod_rm->displacement.displacement_type) {
		case IRA_DISPLACEMENT_8:
			displacement_value.value.v8 = mod_rm->displacement.displacement.displacement_8;
			break;
		case IRA_DISPLACEMENT_16:
			displacement_value.value.v16 = mod_rm->displacement.displacement.displacement_16;
			break;
		case IRA_DISPLACEMENT_32:
			displacement_value.value.v32 = mod_rm->displacement.displacement.displacement_32;
			break;
		case IRA_NO_DISPLACEMENT:
			// Should never happened. Added only to avoid warnings.
			break;
		}

		// Extend displacement if there is such need.
		if( format_info->show_extended_displacement ) {
			if( displacement_value.size != mod_rm->displacement.extension_size ) {
				_ira_extend_integer( &displacement_value, mod_rm->displacement.extension_size, _IRA_TRUE );
			}
		}

		// Append integer as a hex string.
		_ira_format_append_integer( stream, &displacement_value, 16 );
	}

	_ira_format_append_str( stream, "]" );

}

void _ira_operand_formater_immediate( struct ira_disassemble_result *result, struct ira_intel_format_info *format_info, struct ira_instruction_operand *operand, struct _ira_format_stream *stream ) {
	struct ira_immediate_data *immediate = &operand->immediate;
	if( immediate->immediate_data_type != IRA_NO_IMMEDIATE_DATA ) {
		struct _ira_integer immediate_value = {0};
		// Check if immediate data should be treated as signed value.
		if( !format_info->immediate_hex_display && format_info->immediate_signed ) {
			immediate_value.is_signed = _IRA_TRUE;
		}
		immediate_value.size = immediate->immediate_data_type;
		// Copy value.
		switch( immediate->immediate_data_type ) {
		case IRA_IMMEDIATE_8:
			immediate_value.value.v8 = immediate->immediate_data.immediate_8;
			break;
		case IRA_IMMEDIATE_16:
			immediate_value.value.v16 = immediate->immediate_data.immediate_16;
			break;
		case IRA_IMMEDIATE_32:
			immediate_value.value.v32 = immediate->immediate_data.immediate_32;
			break;
		case IRA_IMMEDIATE_64:
			immediate_value.value.v64 = immediate->immediate_data.immediate_64;
			break;
		case IRA_NO_IMMEDIATE_DATA:
			break;
		}
		// Extend integer if immediate value is extended.
		if( format_info->show_extended_immediate ) {
			if( immediate->extension_size != 0 && immediate->extension_size != immediate->immediate_data_type ) {
				_ira_extend_integer( &immediate_value, immediate->extension_size, _IRA_TRUE );
			}
		}
		_ira_format_append_integer( stream, &immediate_value, format_info->immediate_hex_display ? _IRA_FORMAT_HEX : _IRA_FORMAT_DEC );
	}
}

void _ira_operand_formater_register( struct ira_disassemble_result *result, struct ira_intel_format_info *format_info, struct ira_instruction_operand *operand, struct _ira_format_stream *stream ) {
	_ira_format_append_reg( stream, &operand->reg, result->rex.is_not_null );
}
