/*
 * fcml_rend_intel.c
 *
 *  Created on: Oct 20, 2013
 *      Author: tas
 */

#include "fcml_intel_rend.h"

#include <stdio.h>

#include <fcml_types.h>
#include <fcml_renderer.h>
#include <fcml_common.h>
#include <fcml_dialect.h>
#include <fcml_disassembler.h>

#include "fcml_mnemonic_parser.h"
#include "fcml_ceh.h"
#include "fcml_dialect_int.h"
#include "fcml_env.h"
#include "fcml_rend_utils.h"
#include "fcml_stream.h"
#include "fcml_utils.h"

#define FCML_REND_LOCAL_BUFFER_SIZE 512

fcml_string fcml_iarr_rend_utils_integer_formats_intel[6][4] = {
	/* Signed integer values.*/
	{FCML_PRI_INT8_DEC, FCML_PRI_INT16_DEC, FCML_PRI_INT32_DEC, FCML_PRI_INT64_DEC},
	/* Unsigned integer values.*/
	{FCML_PRI_UINT8_DEC, FCML_PRI_UINT16_DEC, FCML_PRI_UINT32_DEC, FCML_PRI_UINT64_DEC},
	/* Signed hex values.*/
	{FCML_PRI_INT8_HEX FCML_TEXT("h"), FCML_PRI_INT16_HEX FCML_TEXT("h"), FCML_PRI_INT32_HEX FCML_TEXT("h"), FCML_PRI_INT64_HEX FCML_TEXT("h")},
	/* Unsigned hex values.*/
	{FCML_PRI_INT8_HEX FCML_TEXT("h"), FCML_PRI_INT16_HEX FCML_TEXT("h"), FCML_PRI_INT32_HEX FCML_TEXT("h"), FCML_PRI_INT64_HEX FCML_TEXT("h")},
	/* Signed hex values without leading zeros. */
	{FCML_PRI_INT8_HEX_NO_ZEROS FCML_TEXT("h"), FCML_PRI_INT16_HEX_NO_ZEROS FCML_TEXT("h"), FCML_PRI_INT32_HEX_NO_ZEROS FCML_TEXT("h"), FCML_PRI_INT64_HEX_NO_ZEROS FCML_TEXT("h")},
	/* Unsigned hex values without leading zeros. */
	{FCML_PRI_INT8_HEX_NO_ZEROS FCML_TEXT("h"), FCML_PRI_INT16_HEX_NO_ZEROS FCML_TEXT("h"), FCML_PRI_INT32_HEX_NO_ZEROS FCML_TEXT("h"), FCML_PRI_INT64_HEX_NO_ZEROS FCML_TEXT("h")}
};

fcml_string fcml_iarr_rend_conditional_suffixes_intel[2][16] = {
	{ FCML_TEXT("o"), FCML_TEXT("no"), FCML_TEXT("b"), FCML_TEXT("nb"), FCML_TEXT("e"), FCML_TEXT("ne"), FCML_TEXT("be"), FCML_TEXT("nbe"), FCML_TEXT("s"), FCML_TEXT("ns"), FCML_TEXT("p"), FCML_TEXT("np"), FCML_TEXT("l"), FCML_TEXT("nl"), FCML_TEXT("le"), FCML_TEXT("nle") },
	{ FCML_TEXT("o"), FCML_TEXT("no"), FCML_TEXT("nae"), FCML_TEXT("ae"), FCML_TEXT("z"), FCML_TEXT("nz"), FCML_TEXT("na"), FCML_TEXT("a"), FCML_TEXT("s"), FCML_TEXT("ns"), FCML_TEXT("pe"), FCML_TEXT("po"), FCML_TEXT("nge"), FCML_TEXT("ge"), FCML_TEXT("ng"), FCML_TEXT("g") }
};

fcml_ceh_error fcml_ifn_rend_operand_renderer_immediate_intel( fcml_st_render_config *config, fcml_st_dialect_context_int *dialect_context, fcml_st_memory_stream *output_stream, fcml_st_disassembler_result *result, fcml_st_operand *operand, fcml_st_operand_details *operand_details, fcml_bool *do_not_render ) {
	// TODO: usunac poniewaz ten operand jest usuwany na etapie disassemblacji.
	/* Do not render pseudo opcodes if shortcut is used.*/
	if( ( operand->hints & FCML_OP_HINT_PSEUDO_OPCODE ) && result->instruction_details.is_pseudo_op ) {
		*do_not_render = FCML_TRUE;
		return FCML_CEH_GEC_NO_ERROR;
	}

	fcml_st_immediate *immediate = &(operand->immediate);
	fcml_st_integer integer;
	fcml_ceh_error error = fcml_fn_utils_imm_to_integer( immediate, &integer );
	if( error ) {
		return error;
	}
	return fcml_fn_rend_utils_format_append_integer( fcml_iarr_rend_utils_integer_formats_intel, output_stream, &integer, config->render_flags & FCML_REND_FLAG_HEX_IMM, config->render_flags & FCML_REND_FLAG_REMOVE_LEADING_ZEROS );
}

fcml_ceh_error fcml_ifn_rend_operand_renderer_reg_intel( fcml_st_render_config *config, fcml_st_dialect_context_int *dialect_context, fcml_st_memory_stream *output_stream, fcml_st_disassembler_result *result, fcml_st_operand *operand, fcml_st_operand_details *operand_details, fcml_bool *do_not_render ) {
	fcml_fn_rend_utils_format_append_reg( dialect_context, output_stream, &(operand->reg), result->instruction_details.prefixes_details.is_rex );
	return FCML_CEH_GEC_NO_ERROR;
}


fcml_ceh_error fcml_ifn_rend_size_operator_intel( fcml_data_size size_operator, fcml_string buffer, fcml_usize buffer_len, fcml_bool is_media_instruction ) {

    fcml_string size_operator_printable = NULL;

    switch( size_operator ) {
    case 0:
        break;
    case 8:
        size_operator_printable = FCML_TEXT("byte ptr ");
        break;
    case 16:
        size_operator_printable = FCML_TEXT("word ptr ");
        break;
    case 32:
        size_operator_printable = FCML_TEXT("dword ptr ");
        break;
    case 48:
        size_operator_printable = FCML_TEXT("fword ptr ");
        break;
    case 64:
        size_operator_printable = is_media_instruction ? FCML_TEXT("mmword ptr ") : FCML_TEXT("qword ptr ");
        break;
    case 80:
        size_operator_printable = FCML_TEXT("tbyte ptr ");
        break;
    case 128:
        size_operator_printable = is_media_instruction ? FCML_TEXT("xmmword ptr ") : FCML_TEXT("oword ptr ");
        break;
    case 256:
        size_operator_printable = is_media_instruction ? FCML_TEXT("ymmword ptr ") : FCML_TEXT("qqword ");
        break;
    default:
#ifdef FCML_MSCC
		_snprintf( buffer, buffer_len, FCML_TEXT("%dbyte ptr "), size_operator / 8 );
#else
        snprintf( buffer, buffer_len, FCML_TEXT("%dbyte ptr "), size_operator / 8 );
#endif
    }

    if( size_operator_printable ) {
        fcml_fn_env_str_strncpy( buffer, size_operator_printable, buffer_len );
    }

    return FCML_CEH_GEC_NO_ERROR;
}

fcml_ceh_error fcml_ifn_rend_operand_renderer_address_intel( fcml_st_render_config *config, fcml_st_dialect_context_int *dialect_context, fcml_st_memory_stream *output_stream, fcml_st_disassembler_result *result, fcml_st_operand *operand, fcml_st_operand_details *operand_details, fcml_bool *do_not_render ) {

	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

	fcml_st_address *address = &(operand->address);

	fcml_st_prefixes_details *prefixes = &(result->instruction_details.prefixes_details);

	fcml_hints hints = operand->hints;

	fcml_uint32_t render_flags = config->render_flags;

	if( hints & FCML_OP_HINT_DISPLACEMENT_RELATIVE_ADDRESS ) {

		fcml_st_integer integer;
		fcml_ceh_error error = fcml_fn_utils_offset_to_integer( &(address->offset), &integer );
		if( error ) {
			return error;
		}

		error = fcml_fn_rend_utils_format_append_integer( fcml_iarr_rend_utils_integer_formats_intel, output_stream, &integer, FCML_TRUE, config->render_flags & FCML_REND_FLAG_REMOVE_LEADING_ZEROS );

		return error;
	}

	if( address->size_operator > 0 ) {
		fcml_char buffer[32] = {0};
		fcml_ifn_rend_size_operator_intel( address->size_operator, buffer, sizeof( buffer ), operand->hints & FCML_OP_HINT_MULTIMEDIA_INSTRUCTION );
		fcml_fn_rend_utils_format_append_str( output_stream, buffer );
	}

	if( !address->segment_selector.is_default_reg || ( render_flags & FCML_REND_FLAG_RENDER_DEFAULT_SEG ) ) {
		fcml_fn_rend_utils_format_append_reg( dialect_context, output_stream, &(address->segment_selector.segment_selector), prefixes->is_rex );
		fcml_fn_rend_utils_format_append_str( output_stream, FCML_TEXT(":") );
	}

	fcml_fn_rend_utils_format_append_str( output_stream, FCML_TEXT("[") );

	fcml_st_effective_address *effective_address = &(address->effective_address);

	fcml_bool first = FCML_TRUE;

	/* Adds SIB hints to all instructions where SIB presents.*/
	if( ( render_flags & FCML_REND_FLAG_RENDER_SIB_HINT ) && ( result->instruction_details.modrm_details.sib.is_not_null ) ) {
		fcml_fn_rend_utils_format_append_str( output_stream, FCML_TEXT("sib ") );
	}

	if( ( render_flags & FCML_REND_FLAG_RENDER_ABS_HINT ) && ( operand->hints & FCML_OP_HINT_ABSOLUTE_ADDRESSING ) ) {
		fcml_fn_rend_utils_format_append_str( output_stream, FCML_TEXT("abs ") );
	}

	if( ( render_flags & FCML_REND_FLAG_RENDER_REL_HINT ) && ( operand->hints & FCML_OP_HINT_RELATIVE_ADDRESSING ) ) {
		fcml_fn_rend_utils_format_append_str( output_stream, FCML_TEXT("rel ") );
	}

	if( address->address_form == FCML_AF_COMBINED ) {

		/* Append base register.*/
		if( !fcml_fn_utils_is_reg_undef( &(effective_address->base) ) ) {
			fcml_fn_rend_utils_format_append_reg( dialect_context, output_stream, &(effective_address->base), prefixes->is_rex );
			first = FCML_FALSE;
		}

		/* Append index register.*/
		if( !fcml_fn_utils_is_reg_undef( &(effective_address->index) ) ) {
			fcml_fn_rend_utils_format_append_str_if( output_stream, FCML_TEXT("+"), !first );
			fcml_fn_rend_utils_format_append_reg( dialect_context, output_stream, &(effective_address->index), prefixes->is_rex );
			first = FCML_FALSE;
		}

		/* Append scale.*/
		if( effective_address->scale_factor > 0 ) {

			fcml_fn_rend_utils_format_append_str_if( output_stream, FCML_TEXT("*"), !first );
			first = FCML_FALSE;

			fcml_st_integer scale_value = {0};
			scale_value.is_signed = FCML_FALSE;
			scale_value.size = 8;
			scale_value.int8 = (fcml_int8_t)effective_address->scale_factor;

			fcml_fn_rend_utils_format_append_integer( fcml_iarr_rend_utils_integer_formats_intel, output_stream, &scale_value, FCML_FALSE, FCML_FALSE );
		}

		/* Displacement.*/
		if( effective_address->displacement.size > 0 ) {

			if( ( render_flags & FCML_REND_FLAG_HEX_DISPLACEMENT ) || !fcml_fn_utils_is_displacement_negative( &(effective_address->displacement) ) ) {
				fcml_fn_rend_utils_format_append_str_if( output_stream, FCML_TEXT("+"), !first );
				first = FCML_FALSE;
			}

			fcml_st_integer integer;
			error = fcml_fn_utils_displacement_to_integer( &(effective_address->displacement), &integer );
			if( error ) {
				return error;
			}

			error = fcml_fn_rend_utils_format_append_integer( fcml_iarr_rend_utils_integer_formats_intel, output_stream, &integer, config->render_flags & FCML_REND_FLAG_HEX_DISPLACEMENT, config->render_flags & FCML_REND_FLAG_REMOVE_LEADING_ZEROS );
		}

	} else {

		/* Offset.*/

		fcml_st_integer integer;
		fcml_ceh_error error = fcml_fn_utils_offset_to_integer( &(address->offset), &integer );
		if( error ) {
			return error;
		}

		error = fcml_fn_rend_utils_format_append_integer( fcml_iarr_rend_utils_integer_formats_intel, output_stream, &integer, FCML_TRUE, config->render_flags & FCML_REND_FLAG_REMOVE_LEADING_ZEROS );
	}

	fcml_fn_rend_utils_format_append_str( output_stream, FCML_TEXT("]") );

	return error;
}

fcml_ceh_error fcml_ifn_rend_operand_renderer_far_pointer_intel( fcml_st_render_config *config, fcml_st_dialect_context_int *dialect_context, fcml_st_memory_stream *output_stream, fcml_st_disassembler_result *result, fcml_st_operand *operand, fcml_st_operand_details *operand_details, fcml_bool *do_not_render ) {

	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

	fcml_st_integer integer = {0};
	integer.is_signed = FCML_TRUE;
	integer.size = 16;
	integer.int16 = operand->far_pointer.segment;

	fcml_fn_rend_utils_format_append_integer( fcml_iarr_rend_utils_integer_formats_intel, output_stream, &integer, FCML_TRUE, config->render_flags & FCML_REND_FLAG_REMOVE_LEADING_ZEROS );

	fcml_fn_rend_utils_format_append_str( output_stream, FCML_TEXT(":") );

	integer.size = operand->far_pointer.offset_size;
	switch( integer.size ) {
	case FCML_DS_16:
		integer.int16 = operand->far_pointer.offset16;
		break;
	case FCML_DS_32:
		integer.int32 = operand->far_pointer.offset32;
		break;
	}

	fcml_fn_rend_utils_format_append_integer( fcml_iarr_rend_utils_integer_formats_intel, output_stream, &integer, FCML_TRUE, config->render_flags & FCML_REND_FLAG_REMOVE_LEADING_ZEROS );

	return error;
}

fcml_ceh_error fcml_ifn_rend_print_operand_intel( fcml_st_render_config *config, fcml_st_dialect_context_int *dialect_context, fcml_st_memory_stream *output_stream, fcml_st_disassembler_result *result, fcml_int operand_index, fcml_bool *do_not_render ) {
	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
	fcml_st_operand *operand = &(result->instruction.operands[operand_index]);
	switch( operand->type ) {
	case FCML_EOT_IMMEDIATE:
		error = fcml_ifn_rend_operand_renderer_immediate_intel( config, dialect_context, output_stream, result, operand, &(result->instruction_details.operand_details[operand_index]), do_not_render );
		break;
	case FCML_EOT_FAR_POINTER:
		error = fcml_ifn_rend_operand_renderer_far_pointer_intel( config, dialect_context, output_stream, result, operand, &(result->instruction_details.operand_details[operand_index]), do_not_render );
		break;
	case FCML_EOT_ADDRESS:
		error = fcml_ifn_rend_operand_renderer_address_intel( config, dialect_context, output_stream, result, operand, &(result->instruction_details.operand_details[operand_index]), do_not_render );
		break;
	case FCML_EOT_REGISTER:
		error = fcml_ifn_rend_operand_renderer_reg_intel( config, dialect_context, output_stream, result, operand, &(result->instruction_details.operand_details[operand_index]), do_not_render );
		break;
	case FCML_EOT_NONE:
		break;
	default:
		error = FCML_CEH_GEC_INVALID_INPUT;
	}
	return error;
}

fcml_string fcml_ifn_rend_get_conditional_suffix_intel( fcml_int condition, fcml_uint32_t render_flags ) {
	if( render_flags & FCML_REND_FLAG_COND_SHOW_CARRY ) {
		if( condition == 2 ) {
			return FCML_TEXT("c");
		} else if( condition == 3 ) {
			return FCML_TEXT("nc");
		}
	}
	fcml_int group = ( render_flags & FCML_REND_FLAG_COND_GROUP_2 ) ? 1 : 0;
	return fcml_iarr_rend_conditional_suffixes_intel[group][condition];
}

fcml_string fcml_ifn_rend_resolve_mnemonic_intel( fcml_st_disassembler_result *result ) {

	fcml_st_instruction *instruction = &(result->instruction);
	fcml_st_instruction_details *details = &(result->instruction);

	if( instruction->mnemonic ) {
		// If there is mnemonic already available use it instead on resolving it again.
		return instruction->mnemonic;
	} else {
		return NULL;
	}

}

fcml_ceh_error fcml_fn_rend_render_instruction_intel( fcml_st_dialect *dialect_context, fcml_st_render_config *config, fcml_st_memory_stream *output_stream, fcml_st_disassembler_result *result ) {

	fcml_st_dialect_context_int *dialect_context_int = (fcml_st_dialect_context_int*)dialect_context;

	fcml_char local_buffer[FCML_REND_LOCAL_BUFFER_SIZE] = {0};

	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

	fcml_uint32_t render_flags = config->render_flags;

	/* Local stream. */
	fcml_st_memory_stream local_stream;
	local_stream.base_address = local_buffer;
	local_stream.size = sizeof( local_buffer );
	local_stream.offset = 0;

	/* Instruction code. */
	if( render_flags & FCML_REND_FLAG_RENDER_CODE ) {
		fcml_fn_rend_utils_format_append_code( config, output_stream, result->instruction_details.instruction_code, result->instruction_details.instruction_size );
	}

	fcml_int len = 0;

	/* Instruction prefixes like LOCK. */
	len += fcml_ifn_rend_utils_print_prefixes( output_stream, &(result->instruction_details.prefixes_details), render_flags );

	/* Mnemonic.*/
	len += fcml_fn_rend_utils_format_append_str( output_stream, fcml_ifn_rend_resolve_mnemonic_intel( result ) );

	/* Short form, so operands should be ignored. */
	if( result->instruction_details.is_shortcut ) {
		return error;
	}

	/* Add hints.*/
	if( result->instruction.hints & FCML_HINT_FAR_POINTER ) {
		len += fcml_fn_rend_utils_format_append_str( output_stream, FCML_TEXT(" far") );
	}
	if( ( render_flags & FCML_REND_FLAG_RENDER_INDIRECT_HINT ) && ( result->instruction.hints & FCML_HINT_INDIRECT_POINTER ) ) {
		len += fcml_fn_rend_utils_format_append_str( output_stream, FCML_TEXT(" indirect") );
	}

	/* Add all operands.*/
	fcml_bool first_render = FCML_TRUE;
	fcml_int i;
	for( i = 0; i < FCML_OPERANDS_COUNT; i++ ) {
		if( result->instruction.operands[i].type != FCML_EOT_NONE ) {
			fcml_bool do_not_render = FCML_FALSE;
			error = fcml_ifn_rend_print_operand_intel( config, dialect_context_int, &local_stream, result, i, &do_not_render );
			if( !error ) {
				if( !do_not_render ) {
					first_render = fcml_fn_rend_utils_render_operand_separator( config, output_stream, len, first_render );
					fcml_fn_rend_utils_format_append_stream( output_stream, &local_stream );
					fcml_fn_stream_clean( &local_stream );
				}
			} else {
				break;
			}
		} else {
			break;
		}
	}

	fcml_fn_rend_utils_format_finish_str( output_stream );

	return error;
}
