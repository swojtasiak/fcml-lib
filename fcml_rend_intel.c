/*
 * fcml_rend_intel.c
 *
 *  Created on: Oct 20, 2013
 *      Author: tas
 */

#include "fcml_rend_intel.h"
#include "fcml_rend_utils.h"

#define FCML_REND_LOCAL_BUFFER_SIZE 512

void fcml_ifn_rend_print_prefixes_intel( fcml_st_asm_dec_prefixes *prefixes ) {
	// TODO: Prefixes, when they are added.
}

void fcml_ifn_rend_operand_renderer_immediate_intel( fcml_st_operand *operand, fcml_st_asm_dec_operand_details *operand_details, fcml_uint32_t render_flags ) {

}

fcml_bool fcml_ifn_rend_print_operand_intel( fcml_st_memory_stream *output_stream, fcml_st_disassembler_result *result, fcml_int operand_index, fcml_uint32_t render_flags ) {
	fcml_st_operand *operand = &(result->operands[operand_index]);
	switch( operand->type ) {
	case FCML_EOT_IMMEDIATE:
		fcml_ifn_rend_operand_renderer_immediate_intel( operand, &(result->operand_details[operand_index]), render_flags );
		break;
	case FCML_EOT_FAR_POINTER:
		break;
	case FCML_EOT_ADDRESS:
		break;
	case FCML_EOT_REGISTER:
		break;
	case FCML_EOT_NONE:
		return FCML_FALSE;
	}
	return FCML_TRUE;
}

fcml_ceh_error fcml_fn_rend_render_instruction_intel( fcml_st_memory_stream *output_stream, fcml_st_disassembler_result *result, fcml_uint32_t render_flags ) {

	fcml_char local_buffer[FCML_REND_LOCAL_BUFFER_SIZE] = {0};

	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

	// Local stream.
	fcml_st_memory_stream local_stream;
	local_stream.base_address = local_buffer;
	local_stream.size = sizeof( local_buffer );
	local_stream.offset = 0;

	// Instruction code.
	if( render_flags & FCML_REND_FLAG_RENDER_CODE ) {
		fcml_fn_rend_utils_format_append_code( output_stream, result->instruction_code, result->instruction_size );
		fcml_fn_rend_utils_format_append_str( output_stream, " " );
	}

	fcml_ifn_rend_print_prefixes_intel( &result->prefixes );

	// Mnemonic.
	fcml_fn_rend_utils_format_append_str( output_stream, result->mnemonic );

	// Short form, so operands should be ignored.
	if( result->is_shortcut ) {
		return error;
	}

	// Add hints.
	if( result->hints & FCML_HINT_FAR_POINTER ) {
		fcml_fn_rend_utils_format_append_str( output_stream, " " );
		fcml_fn_rend_utils_format_append_str( output_stream, "far" );
	}

	// Add all operands.
	fcml_int i;
	for( i = 0; i < FCML_OPERANDS_COUNT; i++ ) {
		fcml_bool res = fcml_ifn_rend_print_operand_intel( &local_stream, result, i, render_flags );
		if( res ) {
			fcml_fn_rend_utils_format_append_str( output_stream, ( i > 0 )  ? "," : " " );
			fcml_fn_rend_utils_format_append_stream( output_stream, &local_stream );
			fcml_fn_stream_clean( &local_stream );
		} else {
			break;
		}
	}

	return error;
}
