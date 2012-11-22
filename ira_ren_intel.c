/*
 * Default instruction renderer compatible with Intel instruction format.
 *
 * ira_ren.c
 *
 *  Created on: 12-12-2010
 *  Last Modification: 05-11-2012
 *
 *      Author: Slawomir Wojtasiak
 */

#include <stdio.h>

#include "ira_ren_intel.h"

#define _IRA_LOCAL_BUFFER_SIZE 512

// Operand formating methods.

typedef void (*_ira_operand_formater)( struct ira_disassemble_result *result, struct ira_intel_format_info *format_info, struct ira_instruction_operand *operand, struct _ira_format_stream *stream );

void _ira_operand_formater_addressing( struct ira_disassemble_result *result, struct ira_intel_format_info *format_info, struct ira_instruction_operand *operand, struct _ira_format_stream *stream );
void _ira_operand_formater_addressing_address( struct ira_disassemble_result *result, struct ira_intel_format_info *format_info, struct ira_instruction_operand *operand, struct _ira_format_stream *stream, int is_addressing );
void _ira_operand_formater_addressing_far_pointer( struct ira_disassemble_result *result, struct ira_intel_format_info *format_info, struct ira_instruction_operand *operand, struct _ira_format_stream *stream );
void _ira_operand_formater_immediate( struct ira_disassemble_result *result, struct ira_intel_format_info *format_info, struct ira_instruction_operand *operand, struct _ira_format_stream *stream );
void _ira_operand_formater_register( struct ira_disassemble_result *result, struct ira_intel_format_info *format_info, struct ira_instruction_operand *operand, struct _ira_format_stream *stream );
void _ira_operand_formater_addressing_modrm( struct ira_disassemble_result *result, struct ira_intel_format_info *format_info, struct ira_instruction_operand *operand, struct _ira_format_stream *stream );
void _ira_operand_formater_addressing_implicit_reg( struct ira_disassemble_result *result, struct ira_intel_format_info *format_info, struct ira_instruction_operand *operand, struct _ira_format_stream *stream );

// TODO: Pomyslec nad zrefaktorowaniem.
int _ira_is_rex_prefix_available(struct ira_disassemble_result *result) {
	int i;
	for( i = 0; i < result->prefixes_count; i++ ) {
		if( result->prefixes[i].prefix_type == IRA_REX ) {
			return _IRA_TRUE;
		}
	}
	return _IRA_FALSE;
}

// Utilities.

void _ira_print_size_directive( uint16_t size_directive, struct _ira_format_stream *stream );

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

	_ira_format_append_prefixes( &stream, result->prefixes, result->prefixes_count );

	// Add mnemonic.
	_ira_format_append_str( &stream, result->mnemonic );

	if( result->condition.is_conditional ) {
		int condition = ( result->condition.condition_type << 1 ) | ( ( result->condition.is_condition_negation ) ? 1 : 0 );
		char *suffix = _ira_get_conditional_prefix( format_info->conditional_suffix_group, condition, format_info->show_conditional_mnemonics_for_carry_flag );
		_ira_format_append_str( &stream, suffix );
	}

	// Add all operands.
	for( i = 0; i < _IRA_OPERANDS_COUNT; i++ ) {
		int res = _ira_format_print_operand( result, format_info, &result->operands[i], &local_stream );
		if( res ) {
			if( i > 0 ) {
				_ira_format_append_str( &stream, "," );
			} else {
				_ira_format_append_str( &stream, " " );
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
		// TODO: trzeba sprawdzic dlaczego IRA_RELATIVE_ADDRESS nie dodaje ptr[] IRA_SEGMENT_RELATIVE_ADDRESS dodaje, bo troche niekonsekwentne, trzeba to jakos ujednolicic i parametryzoac, zeby zalezalo to jakieo tyopu adresowania?
		// bo trzeba zauwazyyc ze niektor instrukcje jako adreowanie poprostu uzywaja odresu jako operandu a niektore danj z pod tego adresu.
	case IRA_SEGMENT_RELATIVE_ADDRESS:
		_ira_operand_formater_addressing_address( result, format_info, operand, stream, _IRA_TRUE );
		break;
	case IRA_RELATIVE_ADDRESS:
		_ira_operand_formater_addressing_address( result, format_info, operand, stream, _IRA_FALSE );
		break;
	case IRA_FAR_POINTER:
		_ira_operand_formater_addressing_far_pointer( result, format_info, operand, stream );
		break;
	case IRA_IMPLICIT_REGISTER_ADDRESSING:
		_ira_operand_formater_addressing_implicit_reg( result, format_info, operand, stream );
		break;
	}
}

void _ira_operand_formater_addressing_modrm( struct ira_disassemble_result *result, struct ira_intel_format_info *format_info, struct ira_instruction_operand *operand, struct _ira_format_stream *stream ) {

	struct ira_addressing *addressing = &operand->addressing;
	struct ira_mod_rm_addressing *mod_rm = &addressing->mod_rm;

	int first = _IRA_TRUE;

	_ira_print_size_directive( operand->operand_size, stream );

	_ira_format_append_str( stream, "[" );

	int is_rex = _ira_is_rex_prefix_available(result);

	// Append base register.
	if( mod_rm->base_reg.reg_type != IRA_NO_REG ) {
		_ira_format_append_reg( stream, &mod_rm->base_reg, is_rex );
		first = _IRA_FALSE;
	}

	// Append index register.
	if( mod_rm->index_reg.reg_type != IRA_NO_REG ) {
		_ira_format_append_if_not_first( stream, &first, "+" );
		_ira_format_append_reg( stream, &mod_rm->index_reg, is_rex );
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

void _ira_operand_formater_addressing_far_pointer( struct ira_disassemble_result *result, struct ira_intel_format_info *format_info, struct ira_instruction_operand *operand, struct _ira_format_stream *stream ) {

	_ira_format_append_str( stream, "far " );

	struct _ira_integer cs_reg_value = {0};
	cs_reg_value.is_signed = _IRA_TRUE;
	cs_reg_value.size = 16;
	cs_reg_value.value.v16 = operand->addressing.segment_selector.segment_register_value;

	_ira_format_append_integer( stream, &cs_reg_value, 16 );

	_ira_format_append_str( stream, ":" );

	_ira_operand_formater_addressing_address( result, format_info,operand, stream, _IRA_FALSE );

}

void _ira_operand_formater_addressing_implicit_reg( struct ira_disassemble_result *result, struct ira_intel_format_info *format_info, struct ira_instruction_operand *operand, struct _ira_format_stream *stream ) {

	_ira_print_size_directive( operand->operand_size, stream );

	_ira_format_append_str( stream, "[" );

	// Append register with memory location.
	_ira_format_append_reg( stream, &(operand->addressing.address_register), _ira_is_rex_prefix_available(result) );

	_ira_format_append_str( stream, "]" );

}

void _ira_operand_formater_addressing_address( struct ira_disassemble_result *result, struct ira_intel_format_info *format_info, struct ira_instruction_operand *operand, struct _ira_format_stream *stream, int is_addressing ) {

	struct ira_addressing *addressing = &operand->addressing;

	if( is_addressing ) {
		_ira_print_size_directive( operand->operand_size, stream );
		_ira_format_append_str( stream, "[" );
	}

	struct _ira_integer address_value = {0};
	address_value.is_signed = _IRA_TRUE;

	switch( addressing->address_size ) {

	case IRA_ADDRESS_16:
		address_value.size = addressing->address_size;
		address_value.value.v16 = addressing->address_value.address_16;
		break;
	case IRA_ADDRESS_32:
		address_value.size = addressing->address_size;
		address_value.value.v32 = addressing->address_value.address_64;
		break;
	case IRA_ADDRESS_64:
		address_value.size = addressing->address_size;
		address_value.value.v64 = addressing->address_value.address_64;
		break;
	}

	_ira_format_append_integer( stream, &address_value, 16 );

	if( is_addressing ) {
		_ira_format_append_str( stream, "]" );
	}
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
	_ira_format_append_reg( stream, &operand->reg, _ira_is_rex_prefix_available(result) );
}

void _ira_print_size_directive( uint16_t size_directive, struct _ira_format_stream *stream ) {

	struct _ira_integer size_directive_int;

	// TODO: Rozpoznawac instrukcje SIMD i inne kodowanie ielkosci danych zastosowac XMMWORD itd.
	switch( size_directive ) {
	case 0:
		break;
	case 8:
		_ira_format_append_str( stream, "byte ptr " );
		break;
	case 16:
		_ira_format_append_str( stream, "word ptr " );
		break;
	case 32:
		_ira_format_append_str( stream, "dword ptr " );
		break;
	case 48:
		_ira_format_append_str( stream, "fword ptr " );
		break;
	case 64:
		_ira_format_append_str( stream, "qword ptr " );
		break;
	case 80:
		_ira_format_append_str( stream, "tbyte ptr " );
		break;
	case 128:
		_ira_format_append_str( stream, "oword ptr " );
		break;
	case 256:
		_ira_format_append_str( stream, "ymmword ptr " );
		break;
	default:
		size_directive_int.is_signed = 0;
		size_directive_int.size = 16;
		size_directive_int.value.v16 = size_directive / 8;
		_ira_format_append_integer( stream, &size_directive_int, 10 );
		_ira_format_append_str( stream, "byte ptr " );
	}
}
