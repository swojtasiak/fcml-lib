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

typedef void (*_ira_operand_formater)( struct ira_disassemble_result *result, struct ira_format_info *format_info, struct ira_instruction_operand *operand, struct _ira_format_stream *stream );

void _ira_operand_formater_addressing( struct ira_disassemble_result *result, struct ira_format_info *format_info, struct ira_instruction_operand *operand, struct _ira_format_stream *stream );
void _ira_operand_formater_immediate_8( struct ira_disassemble_result *result, struct ira_format_info *format_info, struct ira_instruction_operand *operand, struct _ira_format_stream *stream );
void _ira_operand_formater_immediate_16( struct ira_disassemble_result *result, struct ira_format_info *format_info, struct ira_instruction_operand *operand, struct _ira_format_stream *stream );
void _ira_operand_formater_immediate_32( struct ira_disassemble_result *result, struct ira_format_info *format_info, struct ira_instruction_operand *operand, struct _ira_format_stream *stream );
void _ira_operand_formater_immediate_64( struct ira_disassemble_result *result, struct ira_format_info *format_info, struct ira_instruction_operand *operand, struct _ira_format_stream *stream );
void _ira_operand_formater_register( struct ira_disassemble_result *result, struct ira_format_info *format_info, struct ira_instruction_operand *operand, struct _ira_format_stream *stream );
void _ira_operand_formater_addressing_modrm( struct ira_disassemble_result *result, struct ira_format_info *format_info, struct ira_instruction_operand *operand, struct _ira_format_stream *stream );

/* Maps operand type to formating function. */
_ira_operand_formater _ira_formating_table[] = {
	NULL, // IRA_NONE
	&_ira_operand_formater_addressing, // IRA_ADDRESS
	&_ira_operand_formater_immediate_8, // IRA_IMMEDIATE_DATA_8
	&_ira_operand_formater_immediate_16, // IRA_IMMEDIATE_DATA_16
	&_ira_operand_formater_immediate_32, // IRA_IMMEDIATE_DATA_32
	&_ira_operand_formater_immediate_64, // IRA_IMMEDIATE_DATA_64
	&_ira_operand_formater_register // IRA_REGISTER
};

int _ira_format_print_operand( struct ira_disassemble_result *result, struct ira_format_info *format_info, struct ira_instruction_operand *operand, struct _ira_format_stream *stream ) {
	int res = _IRA_FALSE;
	_ira_operand_formater operand_formater = _ira_formating_table[operand->operand_type];
	if( operand_formater != NULL ) {
		operand_formater( result, format_info, operand, stream );
		res = _IRA_TRUE;
	}
	return res;
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
		int res = _ira_format_print_operand( result, format_info, &result->operands[i], &local_stream );
		if( res ) {
			if( i < 0 ) {
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

void _ira_operand_formater_addressing( struct ira_disassemble_result *result, struct ira_format_info *format_info, struct ira_instruction_operand *operand, struct _ira_format_stream *stream ) {
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

void _ira_operand_formater_addressing_modrm( struct ira_disassemble_result *result, struct ira_format_info *format_info, struct ira_instruction_operand *operand, struct _ira_format_stream *stream ) {

	struct ira_addressing *addressing = &operand->addressing;
	struct ira_mod_rm_addressing *mod_rm = &addressing->mod_rm;

	int first = _IRA_TRUE;

	_ira_format_append_str( stream, "[" );
	if( mod_rm->base_reg.reg_type != IRA_NO_REG ) {
		_ira_format_append_reg( stream, &mod_rm->base_reg, result->rex.is_not_null );
		first = _IRA_FALSE;
	}

	if( mod_rm->index_reg.reg_type != IRA_NO_REG ) {
		_ira_format_append_if_not_first( stream, &first, "+" );
		_ira_format_append_reg( stream, &mod_rm->base_reg, result->rex.is_not_null );
	}

	if( mod_rm->scale.is_not_null ) {
		_ira_format_append_if_not_first( stream, &first, "*" );

		struct _ira_integer scale_value;
		scale_value.is_signed = _IRA_FALSE;
		scale_value.size = 8;
		scale_value.value.v8 = mod_rm->scale.value;

		// 10 means decimal.
		_ira_format_append_integer( stream, scale_value, 10 );
	}

	if( mod_rm->displacement.displacement_type != IRA_NO_DISPLACEMENT ) {

		struct _ira_integer displacement_value;
		scale_value.is_signed = _IRA_FALSE;
		scale_value.size = mod_rm->displacement.extension_size;

		switch(mod_rm->displacement.displacement_type) {
		case IRA_DISPLACEMENT_8:
			scale_value.value.v8 =  mod_rm->displacement.displacement.displacement_8;
			break;
		case IRA_DISPLACEMENT_16:
			scale_value.value.v16 =  mod_rm->displacement.displacement.displacement_16;
			break;
		case IRA_DISPLACEMENT_32:
			scale_value.value.v32 =  mod_rm->displacement.displacement.displacement_32;
			break;
		}
	}

	_ira_format_append_str( stream, "]" );

}

void _ira_operand_formater_immediate_8( struct ira_disassemble_result *result, struct ira_format_info *format_info, struct ira_instruction_operand *operand, struct _ira_format_stream *stream ) {
}

void _ira_operand_formater_immediate_16( struct ira_disassemble_result *result, struct ira_format_info *format_info, struct ira_instruction_operand *operand, struct _ira_format_stream *stream ) {
}

void _ira_operand_formater_immediate_32( struct ira_disassemble_result *result, struct ira_format_info *format_info, struct ira_instruction_operand *operand, struct _ira_format_stream *stream ) {
}

void _ira_operand_formater_immediate_64( struct ira_disassemble_result *result, struct ira_format_info *format_info, struct ira_instruction_operand *operand, struct _ira_format_stream *stream ) {
}

void _ira_operand_formater_register( struct ira_disassemble_result *result, struct ira_format_info *format_info, struct ira_instruction_operand *operand, struct _ira_format_stream *stream ) {
}
