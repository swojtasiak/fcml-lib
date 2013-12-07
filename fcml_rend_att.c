/*
 * fcml_rend_intel.c
 *
 *  Created on: Oct 20, 2013
 *      Author: tas
 */

#include "fcml_ceh.h"
#include "fcml_common.h"
#include "fcml_common_utils.h"
#include "fcml_dialect.h"
#include "fcml_dialect_int.h"
#include "fcml_disassembler.h"
#include "fcml_env.h"
#include "fcml_rend.h"
#include "fcml_rend_utils.h"
#include "fcml_stream.h"
#include "fcml_types.h"
#include "fcml_utils.h"

#define FCML_REND_LOCAL_BUFFER_SIZE 512

fcml_string fcml_iarr_rend_utils_integer_formats_att[4][4] = {
	// Signed integer values.
	{FCML_PRI_INT8_DEC, FCML_PRI_INT16_DEC, FCML_PRI_INT32_DEC, FCML_PRI_INT64_DEC},
	// Unsigned integer values.
	{FCML_PRI_UINT8_DEC, FCML_PRI_UINT16_DEC, FCML_PRI_UINT32_DEC, FCML_PRI_UINT64_DEC},
	// Signed hex values.
	{"0x"FCML_PRI_INT8_HEX, "0x"FCML_PRI_INT16_HEX, "0x"FCML_PRI_INT32_HEX, "0x"FCML_PRI_INT64_HEX},
	// Unsigned hex values.
	{"0x"FCML_PRI_INT8_HEX, "0x"FCML_PRI_INT16_HEX, "0x"FCML_PRI_INT32_HEX, "0x"FCML_PRI_INT64_HEX}
};

fcml_string fcml_iarr_rend_conditional_suffixes_att[2][16] = {
	{ "o", "no", "b", "nb", "e", "ne", "be", "nbe", "s", "ns", "p", "np", "l", "nl", "le", "nle" },
	{ "o", "no", "nae", "ae", "z", "nz", "na", "a", "s", "ns", "pe", "po", "nge", "ge", "ng", "g" }
};

void fcml_ifn_rend_print_prefixes_att( fcml_st_memory_stream *output_stream, fcml_st_dasm_prefixes *prefixes, fcml_uint32_t flags ) {
	if( prefixes->is_xacquire ) {
		fcml_fn_rend_utils_format_append_str( output_stream, "xacquire " );
	}
	if( prefixes->is_xrelease ) {
		fcml_fn_rend_utils_format_append_str( output_stream, "xrelease " );
	}
	if( prefixes->is_lock ) {
		fcml_fn_rend_utils_format_append_str( output_stream, "lock " );
	}
	if( prefixes->is_branch ) {
		fcml_fn_rend_utils_format_append_str( output_stream, "branch " );
	}
	if( prefixes->is_nobranch ) {
		fcml_fn_rend_utils_format_append_str( output_stream, "nobranch " );
	}
	if( prefixes->is_rep ) {
		if( flags & FCML_REND_FLAG_REP_PREFIX_GROUP_1 ) {
			fcml_fn_rend_utils_format_append_str( output_stream, "repe " );
		} else if( flags & FCML_REND_FLAG_REP_PREFIX_GROUP_2 ) {
			fcml_fn_rend_utils_format_append_str( output_stream, "repz " );
		} else {
			fcml_fn_rend_utils_format_append_str( output_stream, "rep " );
		}
	}
	if( prefixes->is_repne ) {
		if( flags & FCML_REND_FLAG_REP_PREFIX_GROUP_2 ) {
			fcml_fn_rend_utils_format_append_str( output_stream, "repnz " );
		} else {
			fcml_fn_rend_utils_format_append_str( output_stream, "repne " );
		}
	}
}

fcml_ceh_error fcml_ifn_rend_operand_renderer_immediate_att( fcml_st_dialect_context_int *dialect_context, fcml_st_memory_stream *output_stream, fcml_st_dasm_disassembler_result *result, fcml_st_operand *operand, fcml_st_dasm_operand_details *operand_details, fcml_uint32_t render_flags, fcml_bool *do_not_render ) {

	// Do not render pseudo opcodes if shortcut is used.
	if( ( operand->hints & FCML_OP_HINT_PSEUDO_OPCODE ) && result->instruction_details.is_pseudo_op_shortcut ) {
		*do_not_render = FCML_TRUE;
		return FCML_CEH_GEC_NO_ERROR;
	}

	fcml_st_immediate *immediate = &(operand->immediate);
	fcml_st_integer integer;
	fcml_ceh_error error = fcml_fn_utils_imm_to_integer( immediate, &integer );
	if( error ) {
		return error;
	}

	fcml_fn_rend_utils_format_append_str( output_stream, "$" );

	return fcml_fn_rend_utils_format_append_integer( fcml_iarr_rend_utils_integer_formats_att, output_stream, &integer, render_flags & FCML_REND_FLAG_HEX_IMM );
}

fcml_ceh_error fcml_ifn_rend_operand_renderer_reg_att( fcml_st_dialect_context_int *dialect_context, fcml_st_memory_stream *output_stream, fcml_st_dasm_disassembler_result *result, fcml_st_operand *operand, fcml_st_dasm_operand_details *operand_details, fcml_uint32_t render_flags, fcml_bool *do_not_render ) {
	fcml_fn_rend_utils_format_append_reg( dialect_context, output_stream, &(operand->reg), result->instruction_details.prefixes.is_rex );
	return FCML_CEH_GEC_NO_ERROR;
}

fcml_ceh_error fcml_ifn_rend_operand_renderer_address_att( fcml_st_dialect_context_int *dialect_context, fcml_st_memory_stream *output_stream, fcml_st_dasm_disassembler_result *result, fcml_st_operand *operand, fcml_st_dasm_operand_details *operand_details, fcml_uint32_t render_flags, fcml_bool *do_not_render ) {

	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

	fcml_st_address *address = &(operand->address);
	fcml_st_dasm_prefixes *prefixes = &(result->instruction_details.prefixes);

	fcml_hints hints = operand->hints;

	if( hints & FCML_OP_HINT_DISPLACEMENT_RELATIVE_ADDRESS ) {

		fcml_st_integer integer;
		fcml_ceh_error error = fcml_fn_utils_offset_to_integer( &(address->offset), &integer );
		if( error ) {
			return error;
		}

		error = fcml_fn_rend_utils_format_append_integer( fcml_iarr_rend_utils_integer_formats_att, output_stream, &integer, FCML_TRUE );

		return error;
	}

	if( !address->segment_selector.is_default_reg || ( render_flags & FCML_REND_FLAG_RENDER_DEFAULT_SEG ) ) {
		fcml_fn_rend_utils_format_append_reg( dialect_context, output_stream, &(address->segment_selector.segment_selector), prefixes->is_rex );
		fcml_fn_rend_utils_format_append_str( output_stream, ":" );
	}

	fcml_st_effective_address *effective_address = &(address->effective_address);

	fcml_bool first = FCML_TRUE;

	// Adds SIB hints to all instructions where SIB presents.

	/*
	if( ( render_flags & FCML_REND_FLAG_RENDER_SIB_HINT ) && ( result->instruction_details.modrm_details.sib.is_not_null ) ) {
		fcml_fn_rend_utils_format_append_str( output_stream, "sib " );
	}
	*/

	if( result->instruction.hints & FCML_HINT_INDIRECT_POINTER  ) {
		fcml_fn_rend_utils_format_append_str( output_stream, "*" );
	}

	if( address->address_form == FCML_AF_COMBINED ) {

		// Displacement.
		if( effective_address->displacement.size > 0 ) {

			first = FCML_FALSE;

			fcml_st_integer integer;
			error = fcml_fn_utils_displacement_to_integer( &(effective_address->displacement), &integer );
			if( error ) {
				return error;
			}

			error = fcml_fn_rend_utils_format_append_integer( fcml_iarr_rend_utils_integer_formats_att, output_stream, &integer, render_flags & FCML_REND_FLAG_HEX_DISPLACEMENT );
			if( error ) {
				return error;
			}
		}

		fcml_fn_rend_utils_format_append_str( output_stream, "(" );

		// Append base register.
		if( !fcml_fn_utils_is_reg_undef( &(effective_address->base) ) ) {
			fcml_fn_rend_utils_format_append_reg( dialect_context, output_stream, &(effective_address->base), prefixes->is_rex );
			first = FCML_FALSE;
		}

		// Append index register.
		if( !fcml_fn_utils_is_reg_undef( &(effective_address->index) ) ) {
			fcml_fn_rend_utils_format_append_str( output_stream, "," );
			fcml_fn_rend_utils_format_append_reg( dialect_context, output_stream, &(effective_address->index), prefixes->is_rex );
			first = FCML_FALSE;
		}

		// Append scale.
		if( effective_address->scale_factor > 0 ) {

			first = FCML_FALSE;

			fcml_fn_rend_utils_format_append_str( output_stream, "," );

			fcml_st_integer scale_value = {0};
			scale_value.is_signed = FCML_FALSE;
			scale_value.size = 8;
			scale_value.int8 = (fcml_int8_t)effective_address->scale_factor;

			fcml_fn_rend_utils_format_append_integer( fcml_iarr_rend_utils_integer_formats_att, output_stream, &scale_value, FCML_FALSE );
		}

		fcml_fn_rend_utils_format_append_str( output_stream, ")" );

	} else {

		// Absolute offset or RIP.
		if( !error ) {
			// For RIP base register is set to IP.
			// TODO: moze dodac jakas flage po ktorej mozna by bylo rozpoznac RIP.
			fcml_st_integer integer;
			if( address->effective_address.base.type == FCML_REG_IP ) {
				// IP relative addressing.
				fcml_ceh_error error = fcml_fn_utils_displacement_to_integer( &(address->effective_address.displacement), &integer );
				if( error ) {
					return error;
				}
				error = fcml_fn_rend_utils_format_append_integer( fcml_iarr_rend_utils_integer_formats_att, output_stream, &integer, FCML_TRUE );
				if( !error ) {
					fcml_fn_rend_utils_format_append_str( output_stream, "(" );
					fcml_fn_rend_utils_format_append_reg( dialect_context, output_stream, &(fcml_reg_RIP), FCML_FALSE );
					fcml_fn_rend_utils_format_append_str( output_stream, ")" );
				}
			} else {
				// Absolute offset.
				fcml_ceh_error error = fcml_fn_utils_offset_to_integer( &(address->offset), &integer );
				if( error ) {
					return error;
				}
				error = fcml_fn_rend_utils_format_append_integer( fcml_iarr_rend_utils_integer_formats_att, output_stream, &integer, FCML_TRUE );
			}

		}

	}

	return error;
}

fcml_ceh_error fcml_ifn_rend_operand_renderer_far_pointer_att( fcml_st_dialect_context_int *dialect_context, fcml_st_memory_stream *output_stream, fcml_st_dasm_disassembler_result *result, fcml_st_operand *operand, fcml_st_dasm_operand_details *operand_details, fcml_uint32_t render_flags, fcml_bool *do_not_render ) {

	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

	fcml_st_integer integer = {0};
	integer.is_signed = FCML_TRUE;
	integer.size = 16;
	integer.int16 = operand->far_pointer.segment;

	fcml_fn_rend_utils_format_append_str( output_stream, "$" );
	fcml_fn_rend_utils_format_append_integer( fcml_iarr_rend_utils_integer_formats_att, output_stream, &integer, FCML_TRUE );

	fcml_fn_rend_utils_format_append_str( output_stream, "," );

	integer.size = operand->far_pointer.offset_size;
	switch( integer.size ) {
	case FCML_DS_16:
		integer.int16 = operand->far_pointer.offset16;
		break;
	case FCML_DS_32:
		integer.int32 = operand->far_pointer.offset32;
		break;
	}

	fcml_fn_rend_utils_format_append_str( output_stream, "$" );
	fcml_fn_rend_utils_format_append_integer( fcml_iarr_rend_utils_integer_formats_att, output_stream, &integer, FCML_TRUE );

	return error;
}

fcml_ceh_error fcml_ifn_rend_print_operand_att( fcml_st_dialect_context_int *dialect_context, fcml_st_memory_stream *output_stream, fcml_st_dasm_disassembler_result *result, fcml_int operand_index, fcml_uint32_t render_flags, fcml_bool *do_not_render ) {
	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
	fcml_st_operand *operand = &(result->instruction.operands[operand_index]);
	switch( operand->type ) {
	case FCML_EOT_IMMEDIATE:
		error = fcml_ifn_rend_operand_renderer_immediate_att( dialect_context, output_stream, result, operand, &(result->instruction_details.operand_details[operand_index]), render_flags, do_not_render );
		break;
	case FCML_EOT_FAR_POINTER:
		error = fcml_ifn_rend_operand_renderer_far_pointer_att( dialect_context, output_stream, result, operand, &(result->instruction_details.operand_details[operand_index]), render_flags, do_not_render );
		break;
	case FCML_EOT_ADDRESS:
		error = fcml_ifn_rend_operand_renderer_address_att( dialect_context, output_stream, result, operand, &(result->instruction_details.operand_details[operand_index]), render_flags, do_not_render );
		break;
	case FCML_EOT_REGISTER:
		error = fcml_ifn_rend_operand_renderer_reg_att( dialect_context, output_stream, result, operand, &(result->instruction_details.operand_details[operand_index]), render_flags, do_not_render );
		break;
	case FCML_EOT_NONE:
		break;
	default:
		error = FCML_CEH_GEC_INVALID_INPUT;
	}
	return error;
}

fcml_string fcml_ifn_rend_get_conditional_suffix_att( fcml_int condition, fcml_uint32_t render_flags ) {
	if( render_flags & FCML_REND_FLAG_COND_SHOW_CARRY ) {
		if( condition == 2 ) {
			return "c";
		} else if( condition == 3 ) {
			return "nc";
		}
	}
	fcml_int group = ( render_flags & FCML_REND_FLAG_COND_GROUP_2 ) ? 1 : 0;
	return fcml_iarr_rend_conditional_suffixes_att[group][condition];
}

fcml_ceh_error fcml_fn_rend_render_instruction_att( fcml_st_dialect *dialect_context, fcml_st_memory_stream *output_stream, fcml_st_dasm_disassembler_result *result, fcml_uint32_t render_flags ) {

	fcml_st_dialect_context_int *dialect_context_int = (fcml_st_dialect_context_int*)dialect_context;

	fcml_char local_buffer[FCML_REND_LOCAL_BUFFER_SIZE] = {0};

	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

	// Local stream.
	fcml_st_memory_stream local_stream;
	local_stream.base_address = local_buffer;
	local_stream.size = sizeof( local_buffer );
	local_stream.offset = 0;

	// Instruction code.
	if( render_flags & FCML_REND_FLAG_RENDER_CODE ) {
		fcml_fn_rend_utils_format_append_code( output_stream, result->instruction_details.instruction_code, result->instruction_details.instruction_size );
		fcml_fn_rend_utils_format_append_str( output_stream, " " );
	}

	// Instruction prefixes like LOCK.
	fcml_ifn_rend_print_prefixes_att( output_stream, &(result->instruction_details.prefixes), render_flags );

	// Mnemonic.
	fcml_fn_rend_utils_format_append_str( output_stream, result->instruction.mnemonic );

	// Short form, so operands should be ignored.
	if( result->instruction_details.is_shortcut ) {
		return error;
	}

	// Add all operands.
	fcml_int i;
	for( i = 0; i < FCML_OPERANDS_COUNT; i++ ) {
		if( result->instruction.operands[i].type != FCML_EOT_NONE ) {
			fcml_bool do_not_render = FCML_FALSE;
			error = fcml_ifn_rend_print_operand_att( dialect_context_int, &local_stream, result, i, render_flags, &do_not_render );
			if( !error ) {
				if( !do_not_render ) {
					fcml_fn_rend_utils_format_append_str( output_stream, ( i > 0 )  ? "," : " " );
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

	return error;
}
