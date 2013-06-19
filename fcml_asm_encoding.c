/*
 * fcml_asm_encoding.c
 *
 *  Created on: 31-03-2013
 *      Author: tAs
 */

#include <string.h>

#include "fcml_asm_encoding.h"
#include "fcml_def.h"
#include "fcml_coll.h"
#include "fcml_env.h"
#include "fcml_errors.h"
#include "fcml_utils.h"
#include "fcml_optimizers.h"

fcml_coll_map instructions_map = NULL;

enum fcml_ien_comparator_type {
	FCML_IEN_CT_EQUAL,
	FCML_IEN_CT_EQUAL_OR_LESS,
};

void fcml_ifn_clean_context( fcml_st_asm_encoding_context *context ) {
	fcml_st_asm_data_size_flags *data_size_flags = &(context->data_size_flags);
	data_size_flags->effective_address_size = FCML_DS_UNDEF;
	data_size_flags->effective_operand_size = FCML_DS_UNDEF;
	data_size_flags->l.is_not_null = FCML_FALSE;
	data_size_flags->l.value = 0;
	data_size_flags->allowed_effective_address_size = 0;
}

fcml_st_memory_stream fcml_ifn_instruction_part_stream( fcml_st_asm_instruction_part *instruction_part ) {
	fcml_st_memory_stream stream;
	stream.base_address = &(instruction_part->code);
	stream.offset = 0;
	stream.size = sizeof(instruction_part->code);
	return stream;
}

fcml_bool fcml_ifn_validate_effective_address_size( fcml_st_asm_encoding_context *context ) {
	fcml_en_addr_form addr_form = context->assembler_context->addr_form;
	fcml_data_size eas = context->data_size_flags.effective_address_size;
	if( eas ) {
		if( addr_form == FCML_AF_64_BIT && eas == FCML_DS_16 ) {
			return FCML_FALSE;
		}
		if( addr_form == FCML_AF_16_BIT && eas == FCML_DS_64 ) {
			return FCML_FALSE;
		}
	}
	return FCML_TRUE;
}

fcml_data_size fcml_ifn_get_effective_address_size( fcml_st_asm_encoding_context *context ) {
	if(context->data_size_flags.effective_address_size ) {
		return context->data_size_flags.effective_address_size;
	}
	return context->assembler_context->effective_address_size;
}

fcml_ceh_error fcml_ifn_decode_dynamic_operand_size( fcml_st_asm_encoding_context *context, fcml_uint8_t encoded_operand_size, fcml_data_size data_size, fcml_data_size *encoded_data_size, enum fcml_ien_comparator_type comparator ) {
	fcml_st_asm_data_size_flags *flags = &(context->data_size_flags);
	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
	fcml_data_size effective_address_size = 0;
	fcml_data_size effective_operand_size = 0;
	fcml_nuint8_t l = { 0, FCML_FALSE };
	if( encoded_data_size != NULL ) {
		*encoded_data_size = data_size;
	}
	switch( encoded_operand_size ) {
	case FCML_EOS_UNDEFINED:
		break;
	case FCML_EOS_L:
		switch( data_size) {
		case FCML_DS_128:
			l.is_not_null = FCML_TRUE;
			l.value = 0;
			break;
		case FCML_DS_256:
			l.is_not_null = FCML_TRUE;
			l.value = 1;
			break;
		default:
			error = FCML_EN_UNSUPPORTED_OPPERAND_SIZE;
			break;
		}
		break;
	case FCML_EOS_EASA:
		if( data_size == FCML_DS_16 || data_size == FCML_DS_32 || data_size == FCML_DS_64 ) {
			effective_address_size = data_size;
		} else {
			error = FCML_EN_UNSUPPORTED_OPPERAND_SIZE;
		}
		break;
	case FCML_EOS_EOSA:
		if( data_size == FCML_DS_16 || data_size == FCML_DS_32 || data_size == FCML_DS_64 ) {
			effective_operand_size = data_size;
		} else {
			error = FCML_EN_UNSUPPORTED_OPPERAND_SIZE;
		}
		break;
	case FCML_EOS_14_28:
		switch( data_size ) {
		case 14 * 8:
			effective_operand_size = 16;
			break;
		case 28 * 8:
			if( context->assembler_context->effective_operand_size == FCML_DS_16 ) {
				error = FCML_EN_UNSUPPORTED_OPPERAND_SIZE;
			} else {
				effective_operand_size = context->assembler_context->effective_operand_size;
			}
			break;
		default:
			break;
		}
		break;
	case FCML_EOS_32_64:
		switch( data_size ) {
		case 16 * 2:
			effective_operand_size = 16;
			break;
		case 32 * 2:
			if( context->assembler_context->effective_operand_size == FCML_DS_16 ) {
				error = FCML_EN_UNSUPPORTED_OPPERAND_SIZE;
			} else {
				effective_operand_size = context->assembler_context->effective_operand_size;
			}
			break;
		default:
			break;
		}
		break;
	case FCML_EOS_94_108:
		switch( data_size ) {
		case 94 * 8:
			effective_operand_size = 16;
			break;
		case 108 * 8:
			if( context->assembler_context->effective_operand_size == FCML_DS_16 ) {
				error = FCML_EN_UNSUPPORTED_OPPERAND_SIZE;
			} else {
				effective_operand_size = context->assembler_context->effective_operand_size;
			}
			break;
		default:
			break;
		}
		break;
	default:
		if( comparator == FCML_IEN_CT_EQUAL ) {
			if ( encoded_operand_size * 8 != data_size ) {
				error = FCML_EN_UNSUPPORTED_OPPERAND_SIZE;
			}
		} else {
			if ( encoded_operand_size * 8 < data_size ) {
				error = FCML_EN_UNSUPPORTED_OPPERAND_SIZE;
			} else {
				if( encoded_data_size != NULL ) {
					*encoded_data_size = encoded_operand_size * 8;
				}
			}
		}

		break;
	}

	if( !error ) {
		if( l.is_not_null ) {
			if( flags->l.is_not_null && flags->l.value != l.value ) {
				// All dynamic operands have to be of the same size.
				error = FCML_EN_UNSUPPORTED_OPPERAND_SIZE;
			} else {
				flags->l = l;
			}
		}
		if( effective_address_size ) {
			if( flags->effective_address_size && effective_address_size != flags->effective_address_size ) {
				error = FCML_EN_UNSUPPORTED_OPPERAND_SIZE;
			} else {
				flags->effective_address_size = effective_address_size;
				if( encoded_data_size != NULL ) {
					*encoded_data_size = effective_address_size;
				}
			}
		}
		if( effective_operand_size ) {
			if( flags->effective_operand_size && effective_operand_size != flags->effective_operand_size ) {
				error = FCML_EN_UNSUPPORTED_OPPERAND_SIZE;
			} else {
				flags->effective_operand_size = effective_operand_size;
				if( encoded_data_size != NULL ) {
					*encoded_data_size = effective_operand_size;
				}
			}
		}
	}

	return error;
}

fcml_bool fcml_ifn_accept_data_size( fcml_st_asm_encoding_context *context, fcml_st_def_addr_mode_desc *addr_mode_desc, fcml_uint8_t encoded_register_operand_size, fcml_data_size operand_size, enum fcml_ien_comparator_type comparator ) {
	fcml_bool result = FCML_TRUE;
	switch( encoded_register_operand_size ) {
	case FCML_EOS_UNDEFINED:
		break;
	case FCML_EOS_L:
		if( FCML_DEF_PREFIX_VEX_L_IGNORE_OS( addr_mode_desc->allowed_prefixes ) ) {
			result = ( operand_size == context->assembler_context->effective_operand_size );
		} else {
			result = ( ( operand_size == FCML_DS_128 ) || ( operand_size == FCML_DS_256 ) );
		}
		break;
	case FCML_EOS_EASA:
		if( context->assembler_context->addr_form == FCML_AF_32_BIT ) {
			result = ( ( operand_size == FCML_DS_16 ) || ( operand_size == FCML_DS_32 ) );
		} else {
			result = ( ( operand_size == FCML_DS_32 ) || ( operand_size == FCML_DS_64 ) );
		}
		break;
	case FCML_EOS_EOSA:
		if( context->assembler_context->addr_form == FCML_AF_32_BIT ) {
			result = ( ( operand_size == FCML_DS_16 ) || ( operand_size == FCML_DS_32 ) );
		} else {
			result = ( ( operand_size == FCML_DS_16 ) || ( operand_size == FCML_DS_32 ) || ( operand_size == FCML_DS_64 ) );
		}
		break;
	case FCML_EOS_14_28:
		if( context->assembler_context->addr_form == FCML_AF_32_BIT ) {
			result = ( ( operand_size == 14 * 8 ) || ( operand_size == 28 * 8 ) );
		} else {
			result = ( operand_size == 28 * 8 );
		}
		break;
	case FCML_EOS_32_64:
		if( context->assembler_context->addr_form == FCML_AF_32_BIT ) {
			result = ( ( operand_size == FCML_DS_16 * 2 ) || ( operand_size == FCML_DS_32 * 2 ) );
		} else {
			result = ( ( operand_size == FCML_DS_16 * 2 ) || ( operand_size == FCML_DS_32 * 2 ) || ( operand_size == FCML_DS_64 * 2 ) );
		}
		break;
	case FCML_EOS_94_108:
		if( context->assembler_context->addr_form == FCML_AF_32_BIT ) {
			result = ( ( operand_size == 94 * 8 ) || ( operand_size == 108 * 8 ) );
		} else {
			result = ( operand_size == 28 * 8 );
		}
		break;
	default:
		if( comparator == FCML_IEN_CT_EQUAL ) {
			result = ( encoded_register_operand_size * 8 == operand_size );
		} else {
			result = ( encoded_register_operand_size * 8 >= operand_size );
		}
		break;
	}
	return result;
}

/*********************************
 * Operand encoders.
 *********************************/

//---------------
// IMM
//---------------

fcml_ceh_error fcml_fnp_asm_operand_acceptor_imm( fcml_st_asm_encoding_context *context, fcml_st_def_addr_mode_desc *addr_mode_desc, fcml_st_def_decoded_addr_mode *addr_mode, fcml_st_operand *operand_def, fcml_st_asm_instruction_part *operand_enc ) {
	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
	fcml_sf_def_tma_imm *args = (fcml_sf_def_tma_imm*)addr_mode->addr_mode_args;
	if( operand_def->type == FCML_EOT_IMMEDIATE ) {
		if( !fcml_ifn_accept_data_size( context, addr_mode_desc, args->encoded_imm_size, operand_def->immediate.imm_size, FCML_IEN_CT_EQUAL_OR_LESS ) ) {
			error = FCML_EN_UNSUPPORTED_OPPERAND;
		}
	} else {
		error = FCML_EN_UNSUPPORTED_OPPERAND;
	}
	return error;
}

fcml_ceh_error fcml_fnp_asm_operand_encoder_imm( fcml_ien_asm_part_processor_phase phase, fcml_st_asm_encoding_context *context, fcml_st_def_addr_mode_desc *addr_mode_desc, fcml_st_def_decoded_addr_mode *addr_mode, fcml_st_operand *operand_def, fcml_st_asm_instruction_part *operand_enc ) {
	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
	fcml_sf_def_tma_imm *args = (fcml_sf_def_tma_imm*)addr_mode->addr_mode_args;
	fcml_st_immediate *immediate = &(operand_def->immediate);
	switch( phase ) {
	case FCML_IEN_ASM_IPPP_FIRST_PHASE: {
		// Encode IMM.
		fcml_data_size encoded_size;
		error = fcml_ifn_decode_dynamic_operand_size( context, args->encoded_imm_size, immediate->imm_size, &encoded_size, FCML_IEN_CT_EQUAL_OR_LESS );
		if( !error ) {
			fcml_uvint uvint;
			if( !fcml_fn_utils_imm_to_uvint( immediate, &uvint ) && !fcml_fn_utils_extend_uvint( &uvint, encoded_size ) ) {
				fcml_st_memory_stream stream = { &(operand_enc->code), 0, sizeof( operand_enc->code ) };
				error = fcml_fn_utils_encode_uvint( &stream, &uvint );
				if( !error ) {
					operand_enc->code_length = stream.offset;
				}
			} else {
				error = FCML_EN_UNSUPPORTED_OPPERAND_SIZE;
			}
		}
		break;
	}
	default:
		break;
	}
	return error;
}

//-------------------
// Explicit register
//-------------------

fcml_ceh_error fcml_fnp_asm_operand_acceptor_explicit_reg( fcml_st_asm_encoding_context *context, fcml_st_def_addr_mode_desc *addr_mode_desc, fcml_st_def_decoded_addr_mode *addr_mode, fcml_st_operand *operand_def, fcml_st_asm_instruction_part *operand_enc ) {
	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
	fcml_sf_def_tma_explicit_reg *args = (fcml_sf_def_tma_explicit_reg*)addr_mode->addr_mode_args;
	if( operand_def->type != FCML_EOT_REGISTER || operand_def->reg.reg != args->reg_num ) {
		error = FCML_EN_UNSUPPORTED_OPPERAND;
	}
	return error;
}

// Example: FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_AL, FCML_EOS_BYTE )
fcml_ceh_error fcml_fnp_asm_operand_encoder_explicit_reg( fcml_ien_asm_part_processor_phase phase, fcml_st_asm_encoding_context *context, fcml_st_def_addr_mode_desc *addr_mode_desc, fcml_st_def_decoded_addr_mode *addr_mode, fcml_st_operand *operand_def, fcml_st_asm_instruction_part *operand_enc ) {
	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
	fcml_sf_def_tma_explicit_reg *args = (fcml_sf_def_tma_explicit_reg*)addr_mode->addr_mode_args;
	fcml_st_register *reg = &(operand_def->reg);
	switch( phase ) {
	case FCML_IEN_ASM_IPPP_FIRST_PHASE: {
		// Encode IMM.
		fcml_data_size encoded_size;
		error = fcml_ifn_decode_dynamic_operand_size( context, args->encoded_reg_size, reg->size, &encoded_size, FCML_IEN_CT_EQUAL );
		break;
	}
	default:
		break;
	}
	return error;
}

//-------------------
// Opcode register
//-------------------

fcml_ceh_error fcml_fnp_asm_operand_acceptor_opcode_reg( fcml_st_asm_encoding_context *context, fcml_st_def_addr_mode_desc *addr_mode_desc, fcml_st_def_decoded_addr_mode *addr_mode, fcml_st_operand *operand_def, fcml_st_asm_instruction_part *operand_enc ) {
	return FCML_EN_UNSUPPORTED_OPPERAND;
}

fcml_ceh_error fcml_fnp_asm_operand_encoder_opcode_reg( fcml_ien_asm_part_processor_phase phase, fcml_st_asm_encoding_context *context, fcml_st_def_addr_mode_desc *addr_mode_desc, fcml_st_def_decoded_addr_mode *addr_mode, fcml_st_operand *operand_def, fcml_st_asm_instruction_part *operand_enc ) {
	return FCML_EN_UNSUPPORTED_OPPERAND;
}

//-------------------------
// Immediate dis. relative
//-------------------------

fcml_ceh_error fcml_fnp_asm_operand_acceptor_immediate_dis_relative( fcml_st_asm_encoding_context *context, fcml_st_def_addr_mode_desc *addr_mode_desc, fcml_st_def_decoded_addr_mode *addr_mode, fcml_st_operand *operand_def, fcml_st_asm_instruction_part *operand_enc ) {
	return FCML_EN_UNSUPPORTED_OPPERAND;
}

fcml_ceh_error fcml_fnp_asm_operand_encoder_immediate_dis_relative( fcml_ien_asm_part_processor_phase phase, fcml_st_asm_encoding_context *context, fcml_st_def_addr_mode_desc *addr_mode_desc, fcml_st_def_decoded_addr_mode *addr_mode, fcml_st_operand *operand_def, fcml_st_asm_instruction_part *operand_enc ) {
	return FCML_EN_UNSUPPORTED_OPPERAND;
}

//-------------------------
// Far pointer
//-------------------------

fcml_ceh_error fcml_fnp_asm_operand_acceptor_far_pointer( fcml_st_asm_encoding_context *context, fcml_st_def_addr_mode_desc *addr_mode_desc, fcml_st_def_decoded_addr_mode *addr_mode, fcml_st_operand *operand_def, fcml_st_asm_instruction_part *operand_enc ) {
	return FCML_EN_UNSUPPORTED_OPPERAND;
}

fcml_ceh_error fcml_fnp_asm_operand_encoder_far_pointer( fcml_ien_asm_part_processor_phase phase, fcml_st_asm_encoding_context *context, fcml_st_def_addr_mode_desc *addr_mode_desc, fcml_st_def_decoded_addr_mode *addr_mode, fcml_st_operand *operand_def, fcml_st_asm_instruction_part *operand_enc ) {
	return FCML_EN_UNSUPPORTED_OPPERAND;
}

//-------------------------
// Far pointer indirect
//-------------------------

fcml_ceh_error fcml_fnp_asm_operand_acceptor_far_pointer_indirect( fcml_st_asm_encoding_context *context, fcml_st_def_addr_mode_desc *addr_mode_desc, fcml_st_def_decoded_addr_mode *addr_mode, fcml_st_operand *operand_def, fcml_st_asm_instruction_part *operand_enc ) {
	return FCML_EN_UNSUPPORTED_OPPERAND;
}

fcml_ceh_error fcml_fnp_asm_operand_encoder_far_pointer_indirect( fcml_ien_asm_part_processor_phase phase, fcml_st_asm_encoding_context *context, fcml_st_def_addr_mode_desc *addr_mode_desc, fcml_st_def_decoded_addr_mode *addr_mode, fcml_st_operand *operand_def, fcml_st_asm_instruction_part *operand_enc ) {
	return FCML_EN_UNSUPPORTED_OPPERAND;
}

//-----------------------------
// Explicit gps reg addressing
//-----------------------------

fcml_ceh_error fcml_fnp_asm_operand_acceptor_explicit_gps_reg_addressing( fcml_st_asm_encoding_context *context, fcml_st_def_addr_mode_desc *addr_mode_desc, fcml_st_def_decoded_addr_mode *addr_mode, fcml_st_operand *operand_def, fcml_st_asm_instruction_part *operand_enc ) {
	return FCML_EN_UNSUPPORTED_OPPERAND;
}

fcml_ceh_error fcml_fnp_asm_operand_encoder_explicit_gps_reg_addressing( fcml_ien_asm_part_processor_phase phase, fcml_st_asm_encoding_context *context, fcml_st_def_addr_mode_desc *addr_mode_desc, fcml_st_def_decoded_addr_mode *addr_mode, fcml_st_operand *operand_def, fcml_st_asm_instruction_part *operand_enc ) {
	return FCML_EN_UNSUPPORTED_OPPERAND;
}

//-------------
// Explicit IB
//-------------

fcml_ceh_error fcml_fnp_asm_operand_acceptor_explicit_ib( fcml_st_asm_encoding_context *context, fcml_st_def_addr_mode_desc *addr_mode_desc, fcml_st_def_decoded_addr_mode *addr_mode, fcml_st_operand *operand_def, fcml_st_asm_instruction_part *operand_enc ) {
	return FCML_EN_UNSUPPORTED_OPPERAND;
}

fcml_ceh_error fcml_fnp_asm_operand_encoder_explicit_ib( fcml_ien_asm_part_processor_phase phase, fcml_st_asm_encoding_context *context, fcml_st_def_addr_mode_desc *addr_mode_desc, fcml_st_def_decoded_addr_mode *addr_mode, fcml_st_operand *operand_def, fcml_st_asm_instruction_part *operand_enc ) {
	return FCML_EN_UNSUPPORTED_OPPERAND;
}

//-------------------------
// Segment relative offset
//-------------------------

fcml_ceh_error fcml_fnp_asm_operand_acceptor_segment_relative_offset( fcml_st_asm_encoding_context *context, fcml_st_def_addr_mode_desc *addr_mode_desc, fcml_st_def_decoded_addr_mode *addr_mode, fcml_st_operand *operand_def, fcml_st_asm_instruction_part *operand_enc ) {
	return FCML_EN_UNSUPPORTED_OPPERAND;
}

fcml_ceh_error fcml_fnp_asm_operand_encoder_segment_relative_offset( fcml_ien_asm_part_processor_phase phase, fcml_st_asm_encoding_context *context, fcml_st_def_addr_mode_desc *addr_mode_desc, fcml_st_def_decoded_addr_mode *addr_mode, fcml_st_operand *operand_def, fcml_st_asm_instruction_part *operand_enc ) {
	return FCML_EN_UNSUPPORTED_OPPERAND;
}

//-------------
// ModR/M - rm
//-------------

fcml_ceh_error fcml_fnp_asm_operand_acceptor_rm( fcml_st_asm_encoding_context *context, fcml_st_def_addr_mode_desc *addr_mode_desc, fcml_st_def_decoded_addr_mode *addr_mode, fcml_st_operand *operand_def, fcml_st_asm_instruction_part *operand_enc ) {
	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;;
	fcml_bool result = FCML_TRUE;
	fcml_bool is_reg = FCML_FALSE;
	fcml_bool is_mem = FCML_FALSE;
	fcml_sf_def_tma_rm *args = (fcml_sf_def_tma_rm*)addr_mode->addr_mode_args;
	is_mem = operand_def->type == FCML_EOT_EFFECTIVE_ADDRESS;
	is_reg = operand_def->type == FCML_EOT_REGISTER;
	// Check operand type.
	if ( args->flags == FCML_RMF_RM ) {
		result &= ( is_mem || is_reg );
	} else if ( args->flags & FCML_RMF_R ) {
		result &= is_reg;
	} else if ( args->flags & FCML_RMF_M ) {
		result &= is_mem;
	}
	if( result ) {
		if( is_reg ) {
			if( !fcml_ifn_accept_data_size( context, addr_mode_desc, args->encoded_register_operand_size, operand_def->reg.size, FCML_IEN_CT_EQUAL ) ) {
				error = FCML_EN_UNSUPPORTED_OPPERAND_SIZE;
			}
		}
		if( is_mem ) {
			if( !fcml_ifn_accept_data_size( context, addr_mode_desc, args->encoded_memory_operand_size, operand_def->effective_address.size_operator, FCML_IEN_CT_EQUAL ) ) {
				error = FCML_EN_UNSUPPORTED_OPPERAND_SIZE;
			}
			if( !(operand_def->effective_address.base.type) && !(operand_def->effective_address.index.type) && !(context->assembler_context->configuration.choose_rip_encoding) ) {
				// No register defined, so dispacement only addressing has to be used. We do not check RIP here, because in case of RIP, rip encoding is always used.
				if( context->assembler_context->addr_form == FCML_AF_64_BIT ) {
					context->data_size_flags.allowed_effective_address_size = FCML_EN_ASF_64 | FCML_EN_ASF_32;
				} else if( context->assembler_context->addr_form == FCML_AF_32_BIT || context->assembler_context->addr_form == FCML_AF_16_BIT ) {
					context->data_size_flags.allowed_effective_address_size = FCML_EN_ASF_16 | FCML_EN_ASF_32;
				}
			}
		}
	} else {
		error = FCML_EN_UNSUPPORTED_OPPERAND;
	}
	return error;
}

fcml_ceh_error fcml_fnp_asm_operand_encoder_rm( fcml_ien_asm_part_processor_phase phase, fcml_st_asm_encoding_context *context, fcml_st_def_addr_mode_desc *addr_mode_desc, fcml_st_def_decoded_addr_mode *addr_mode, fcml_st_operand *operand_def, fcml_st_asm_instruction_part *operand_enc ) {
	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;;
	fcml_sf_def_tma_rm *args = (fcml_sf_def_tma_rm*)addr_mode->addr_mode_args;
	switch( phase ) {
	case FCML_IEN_ASM_IPPP_FIRST_PHASE:
		if( operand_def->type == FCML_EOT_REGISTER ) {
			context->mod_rm.reg.is_not_null = FCML_TRUE;
			context->mod_rm.reg.value = operand_def->reg.reg;
			// Modify data size flags if there is such need.
			error = fcml_ifn_decode_dynamic_operand_size( context, args->encoded_register_operand_size, operand_def->reg.size, NULL,FCML_IEN_CT_EQUAL );
		} else {
			context->mod_rm.base = operand_def->effective_address.base;
			context->mod_rm.displacement = operand_def->effective_address.displacement;
			context->mod_rm.index = operand_def->effective_address.index;
			context->mod_rm.scale_factor = operand_def->effective_address.scale_factor;
			error = fcml_ifn_decode_dynamic_operand_size( context, args->encoded_memory_operand_size, operand_def->effective_address.size_operator, NULL, FCML_IEN_CT_EQUAL );
		}
		break;
	default:
		break;
	}
	return error;
}

//------------
// ModR/M - r
//------------

fcml_ceh_error fcml_fnp_asm_operand_acceptor_r( fcml_st_asm_encoding_context *context, fcml_st_def_addr_mode_desc *addr_mode_desc, fcml_st_def_decoded_addr_mode *addr_mode, fcml_st_operand *operand_def, fcml_st_asm_instruction_part *operand_enc ) {
	fcml_sf_def_tma_r *args = (fcml_sf_def_tma_r*)addr_mode->addr_mode_args;
	if( operand_def->type != FCML_EOT_REGISTER ) {
		return FCML_EN_UNSUPPORTED_OPPERAND;
	}
	if( !fcml_ifn_accept_data_size( context, addr_mode_desc, args->encoded_register_operand_size, operand_def->reg.size, FCML_IEN_CT_EQUAL ) ) {
		return FCML_EN_UNSUPPORTED_OPPERAND;
	}
	return FCML_CEH_GEC_NO_ERROR;
}

fcml_ceh_error fcml_fnp_asm_operand_encoder_r( fcml_ien_asm_part_processor_phase phase, fcml_st_asm_encoding_context *context, fcml_st_def_addr_mode_desc *addr_mode_desc, fcml_st_def_decoded_addr_mode *addr_mode, fcml_st_operand *operand_def, fcml_st_asm_instruction_part *operand_enc ) {
	if( phase == FCML_IEN_ASM_IPPP_FIRST_PHASE ) {
		context->mod_rm.reg_opcode = operand_def->reg.reg;
	}
	return FCML_CEH_GEC_NO_ERROR;
}

//------------
// VVVV
//------------

fcml_ceh_error fcml_fnp_asm_operand_acceptor_vex_vvvv( fcml_st_asm_encoding_context *context, fcml_st_def_addr_mode_desc *addr_mode_desc, fcml_st_def_decoded_addr_mode *addr_mode, fcml_st_operand *operand_def, fcml_st_asm_instruction_part *operand_enc ) {
	return FCML_EN_UNSUPPORTED_OPPERAND;
}

fcml_ceh_error fcml_fnp_asm_operand_encoder_vex_vvvv( fcml_ien_asm_part_processor_phase phase, fcml_st_asm_encoding_context *context, fcml_st_def_addr_mode_desc *addr_mode_desc, fcml_st_def_decoded_addr_mode *addr_mode, fcml_st_operand *operand_def, fcml_st_asm_instruction_part *operand_enc ) {
	return FCML_EN_UNSUPPORTED_OPPERAND;
}

//-----
// is4
//-----

fcml_ceh_error fcml_fnp_asm_operand_acceptor_is4( fcml_st_asm_encoding_context *context, fcml_st_def_addr_mode_desc *addr_mode_desc, fcml_st_def_decoded_addr_mode *addr_mode, fcml_st_operand *operand_def, fcml_st_asm_instruction_part *operand_enc ) {
	return FCML_EN_UNSUPPORTED_OPPERAND;
}

fcml_ceh_error fcml_fnp_asm_operand_encoder_is4( fcml_ien_asm_part_processor_phase phase, fcml_st_asm_encoding_context *context, fcml_st_def_addr_mode_desc *addr_mode_desc, fcml_st_def_decoded_addr_mode *addr_mode, fcml_st_operand *operand_def, fcml_st_asm_instruction_part *operand_enc ) {
	return FCML_EN_UNSUPPORTED_OPPERAND;
}

//------
// vsib
//------

fcml_ceh_error fcml_fnp_asm_operand_acceptor_vsib( fcml_st_asm_encoding_context *context, fcml_st_def_addr_mode_desc *addr_mode_desc, fcml_st_def_decoded_addr_mode *addr_mode, fcml_st_operand *operand_def, fcml_st_asm_instruction_part *operand_enc ) {
	return FCML_EN_UNSUPPORTED_OPPERAND;
}

fcml_ceh_error fcml_fnp_asm_operand_encoder_vsib( fcml_ien_asm_part_processor_phase phase, fcml_st_asm_encoding_context *context, fcml_st_def_addr_mode_desc *addr_mode_desc, fcml_st_def_decoded_addr_mode *addr_mode, fcml_st_operand *operand_def, fcml_st_asm_instruction_part *operand_enc ) {
	return FCML_EN_UNSUPPORTED_OPPERAND;
}

fcml_st_asm_operand_encoder_def fcml_def_operand_encoders[] = {
	{ NULL, NULL },
	{ fcml_fnp_asm_operand_encoder_imm, fcml_fnp_asm_operand_acceptor_imm },
	{ fcml_fnp_asm_operand_encoder_explicit_reg, fcml_fnp_asm_operand_acceptor_explicit_reg },
	{ fcml_fnp_asm_operand_encoder_opcode_reg, fcml_fnp_asm_operand_acceptor_opcode_reg },
	{ fcml_fnp_asm_operand_encoder_immediate_dis_relative, fcml_fnp_asm_operand_acceptor_immediate_dis_relative },
	{ fcml_fnp_asm_operand_encoder_far_pointer, fcml_fnp_asm_operand_acceptor_far_pointer },
	{ fcml_fnp_asm_operand_encoder_far_pointer_indirect, fcml_fnp_asm_operand_acceptor_far_pointer_indirect },
	{ fcml_fnp_asm_operand_encoder_explicit_gps_reg_addressing, fcml_fnp_asm_operand_acceptor_explicit_gps_reg_addressing },
	{ fcml_fnp_asm_operand_encoder_explicit_ib, fcml_fnp_asm_operand_acceptor_explicit_ib },
	{ fcml_fnp_asm_operand_encoder_segment_relative_offset, fcml_fnp_asm_operand_acceptor_segment_relative_offset },
	{ fcml_fnp_asm_operand_encoder_rm, fcml_fnp_asm_operand_acceptor_rm },
	{ fcml_fnp_asm_operand_encoder_r, fcml_fnp_asm_operand_acceptor_r },
	{ fcml_fnp_asm_operand_encoder_vex_vvvv, fcml_fnp_asm_operand_acceptor_vex_vvvv },
	{ fcml_fnp_asm_operand_encoder_is4, fcml_fnp_asm_operand_acceptor_is4 },
	{ fcml_fnp_asm_operand_encoder_vsib, fcml_fnp_asm_operand_acceptor_vsib }
};

/*********************************
 * Instruction encoders.
 *********************************/

fcml_bool fcml_ifn_asm_accept_addr_mode( fcml_st_asm_encoding_context *context, fcml_st_asm_instruction_addr_mode *addr_mode, fcml_st_instruction *instruction ) {
	fcml_ifn_asm_instruction_part_processor_chain *current_processor = addr_mode->part_processor_chain;
	while( current_processor ) {
		fcml_ifn_asm_instruction_part_processor_descriptor *descriptor = &(current_processor->processor_descriptor);
		if( descriptor->processor_acceptor != NULL && descriptor->processor_acceptor( context, addr_mode->addr_mode_desc, instruction, descriptor->processor_args ) != FCML_CEH_GEC_NO_ERROR ) {
			return FCML_FALSE;
		}
		current_processor = current_processor->next_processor;
	}
	return FCML_TRUE;
}

fcml_ien_asm_part_processor_phase fcml_asm_executed_phases[] = { FCML_IEN_ASM_IPPP_FIRST_PHASE, FCML_IEN_ASM_IPPP_SECOND_PHASE, FCML_IEN_ASM_IPPP_THIRD_PHASE };


// Responsible for assembling given addressing mode using attributes provided by context.
fcml_ceh_error fcml_ifn_asm_process_addr_mode( fcml_st_asm_encoding_context *context, fcml_st_asm_instruction_addr_mode *addr_mode, fcml_st_asm_instruction_part_container *instruction_part_container ) {

	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

	// Allocate instruction parts.
	fcml_st_asm_instruction_part *instruction_part = (fcml_st_asm_instruction_part*)fcml_fn_env_clear_memory_alloc(sizeof( fcml_st_asm_instruction_part ) * addr_mode->instruction_parts );
	if( !instruction_part ) {
		return FCML_CEH_GEC_OUT_OF_MEMORY;
	}

	int i;
	for( i = 0; !error && i < sizeof( fcml_asm_executed_phases ) / sizeof( fcml_ien_asm_part_processor_phase ); i++ ) {
		fcml_st_asm_instruction_part *current_instruction_part = instruction_part;
		fcml_ifn_asm_instruction_part_processor_chain *current_processor = addr_mode->part_processor_chain;
		fcml_bool first = FCML_TRUE;
		while(current_processor) {
			fcml_ifn_asm_instruction_part_processor_descriptor *descriptor = &(current_processor->processor_descriptor);
			if( descriptor->processor_encoder ) {
				if( !first && descriptor->processor_type == FCML_IEN_ASM_IPPT_ENCODER ) {
					current_instruction_part++;
				}
				first = FCML_FALSE;
				error = descriptor->processor_encoder( fcml_asm_executed_phases[i], context, addr_mode->addr_mode_desc, descriptor->processor_type == FCML_IEN_ASM_IPPT_VERIFIER ? NULL : current_instruction_part, descriptor->processor_args );
				if( error ) {
					// Something failed.
					break;
				}
			}
			current_processor = current_processor->next_processor;
		}
	}

	// Calculate instruction size.
	fcml_uint8_t code_length = 0;
	for( i = 0; i < addr_mode->instruction_parts; i++ ) {
		fcml_st_asm_instruction_part *ip = &(instruction_part[i]);
		code_length += ip->code_length;
	}

	context->instruction_size.is_not_null = FCML_TRUE;
	context->instruction_size.value = code_length;

	// Execute potential post processors.
	for( i = 0; i < addr_mode->instruction_parts; i++ ) {
		fcml_st_asm_instruction_part *ip = &(instruction_part[i]);
		if( ip->post_processor != NULL ) {
			fcml_ceh_error error = ip->post_processor( context, ip, ip->post_processor_args );
			if( error ) {
				break;
			}
		}
	}

	if( error ) {
		fcml_fn_env_memory_free( instruction_part );
	} else {
		instruction_part_container->instruction_parts = instruction_part;
		instruction_part_container->count = addr_mode->instruction_parts;
	}

	return error;
}

void fcml_ifn_assemble_instruction_parts( fcml_st_assembled_instruction *assembled_instruction, fcml_st_asm_instruction_part_container *instruction_part_container ) {
	int i, count = instruction_part_container->count;
	int offset = 0;
	for( i = 0; i < count; i++ ) {
		fcml_st_asm_instruction_part *part = &(instruction_part_container->instruction_parts[i]);
		fcml_fn_env_memory_copy( assembled_instruction->code + offset, part->code, part->code_length );
		offset += part->code_length;
	}
	// Just to be consequent.
	assembled_instruction->code_length = offset;
}

void fcml_ifn_asm_free_assembled_instruction( fcml_st_assembled_instruction *assembled_instruction ) {
	if( assembled_instruction ) {
		if( assembled_instruction->code ) {
			fcml_fn_env_memory_free( assembled_instruction->code );
		}
		fcml_fn_env_memory_free( assembled_instruction );
	}
}

fcml_ceh_error fcml_ifn_asm_assemble_instruction( fcml_st_asm_encoding_context *context, fcml_st_asm_instruction_addr_mode *addr_mode, fcml_st_assembled_instruction **assembled_instruction ) {

	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

	fcml_st_asm_instruction_part_container instruction_part_container = {0};

	error = fcml_ifn_asm_process_addr_mode( context, addr_mode, &instruction_part_container );

	// Assemble instruction parts.
	if( !error ) {
		int i, ip_count = instruction_part_container.count;
		fcml_usize code_length = 0;

		for( i = 0; i < ip_count; i++ ) {
			fcml_st_asm_instruction_part *ip = &(instruction_part_container.instruction_parts[i]);
			code_length += ip->code_length;
		}

		// Allocate memory block for assembled code.
		fcml_st_assembled_instruction *asm_inst = fcml_fn_env_clear_memory_alloc( sizeof( fcml_st_assembled_instruction ) );
		if( !asm_inst ) {
			error = FCML_CEH_GEC_NO_ERROR;
		} else {
			asm_inst->code = (fcml_uint8_t*)fcml_fn_env_memory_alloc( code_length );
			if( !asm_inst->code ) {
				fcml_fn_env_memory_free( asm_inst );
				error = FCML_CEH_GEC_NO_ERROR;
			}
			asm_inst->code_length = code_length;
		}

		// Prepareing result.
		if( !error ) {
			fcml_ifn_assemble_instruction_parts( asm_inst, &instruction_part_container );
			*assembled_instruction = asm_inst;
		}

	}

	// In case of error, free allocated instruction parts.
	if( instruction_part_container.instruction_parts ) {
		fcml_fn_env_memory_free( instruction_part_container.instruction_parts );
	}

	return error;
}

fcml_ceh_error fcml_ifn_asm_assemble_and_collect_instruction( fcml_st_asm_encoding_context *context, fcml_st_asm_instruction_addr_mode *addr_mode, fcml_ptr args ) {
	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
	fcml_st_assembled_instruction *assembled_instruction;
	error = fcml_ifn_asm_assemble_instruction( context, addr_mode, &assembled_instruction );
	if( !error ) {
		#ifdef FCML_DEBUG
			fcml_st_opt_debug_args *opt_args = (fcml_st_opt_debug_args*)args;
			assembled_instruction->__def_index = opt_args->__def_index;
		#endif
		if( !fcml_fn_coll_list_add_front( context->result->instructions, assembled_instruction ) ) {
			fcml_ifn_asm_free_assembled_instruction( assembled_instruction );
			error = FCML_CEH_GEC_OUT_OF_MEMORY;
		}
	}
	return error;
}

fcml_ceh_error fcml_fnp_asm_instruction_encoder_IA( fcml_st_asm_encoding_context *context, struct fcml_st_asm_instruction_addr_modes *addr_modes ) {
	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

	if( addr_modes ) {

		fcml_en_assembler_optimizers optimizer_type = context->assembler_context->configuration.optimizer;
		fcml_fnp_asm_optimizer optimizer = fcml_ar_optimizers[optimizer_type];
		if( !optimizer ) {
			// Optimizer not found.
			return FCML_CEH_GEC_ILLEGAL_STATE_EXCEPTION;
		}

		// Choose addressing mode.
		if( addr_modes->addr_modes->size ) {
			fcml_st_coll_list_element *addr_mode_element = addr_modes->addr_modes->head;
#ifdef FCML_DEBUG
			int index = 0;
#endif
			while( addr_mode_element ) {
				error = FCML_CEH_GEC_NO_ERROR;
				fcml_st_asm_instruction_addr_mode *addr_mode = (fcml_st_asm_instruction_addr_mode *)addr_mode_element->item;
				fcml_ifn_clean_context( context );
				if( fcml_ifn_asm_accept_addr_mode( context, addr_mode, context->instruction ) ) {
#ifdef FCML_DEBUG
					fcml_st_opt_debug_args args;
					args.__def_index = index;
					error = optimizer( context, addr_mode, fcml_ifn_asm_assemble_and_collect_instruction, &args );
#else
					error = optimizer( context, addr_mode, fcml_ifn_asm_assemble_and_collect_instruction, NULL );
#endif
				}
				addr_mode_element = addr_mode_element->next;
#ifdef FCML_DEBUG
				index++;
#endif
			}

			if( context->result->instructions->size == 0 ) {
				error = FCML_EN_UNSUPPORTED_ADDRESSING_MODE;
			}

		} else {
			// There is no addressing mode for given instruction. It should never happened, so it's an internal bug.
			error = FCML_CEH_GEC_INTERNAL_BUG;
		}
	}

	return error;
}

/****************************************
 * Processor part factories.
 ****************************************/

void fcml_ifn_asm_free_part_processor_chain( fcml_ifn_asm_instruction_part_processor_chain *chain ) {
	if( chain ) {
		fcml_ifn_asm_free_part_processor_chain( chain->next_processor );
		fcml_ifn_asm_instruction_part_processor_descriptor *descriptor = &(chain->processor_descriptor);
		if( descriptor->processor_args_deallocator ) {
			descriptor->processor_args_deallocator( descriptor->processor_args );
		}
		fcml_fn_env_memory_free( chain );
	}
}

//////////////////////////////////////
// Operand encoder wrapper factory. //
//////////////////////////////////////

struct fcml_ist_asm_operand_encoder_wrapper_args {
	// Decoder operand addressing.
	fcml_st_def_decoded_addr_mode *decoded_addr_mode;
	// Opernads acceptor.
	fcml_fnp_asm_operand_acceptor operand_acceptor;
	// Function responsible for encoding operand.
	fcml_fnp_asm_operand_encoder operand_encoder;
	// Index of the operand to encode.
	int operand_index;
};

void fcml_ifn_asm_processor_operand_encoder_args_deallocator( fcml_ptr ptr ) {
	struct fcml_ist_asm_operand_encoder_wrapper_args *wrapper_wrgs = (struct fcml_ist_asm_operand_encoder_wrapper_args*)ptr;
	if( wrapper_wrgs->decoded_addr_mode ) {
		fcml_fnp_def_free_addr_mode( wrapper_wrgs->decoded_addr_mode );
	}
	fcml_fn_env_memory_free( wrapper_wrgs );
}

fcml_ceh_error fcml_ifn_asm_instruction_part_processor_acceptor_operand_encoder_wrapper( fcml_st_asm_encoding_context *context, fcml_st_def_addr_mode_desc *addr_mode_desc, fcml_st_instruction *instruction, fcml_ptr args ) {
	struct fcml_ist_asm_operand_encoder_wrapper_args *wrapper_args = (struct fcml_ist_asm_operand_encoder_wrapper_args*)args;
	fcml_st_operand *operand = &(instruction->operands[wrapper_args->operand_index]);
	if( wrapper_args->operand_acceptor ) {
		return wrapper_args->operand_acceptor( context, addr_mode_desc, wrapper_args->decoded_addr_mode, operand, NULL );
	} else {
		// This operand shouldn't be defined.
		if( instruction->operands[wrapper_args->operand_index].type != FCML_EOT_NONE ) {
			return FCML_EN_UNSUPPORTED_OPPERAND;
		}
		return FCML_CEH_GEC_NO_ERROR;
	}
}

fcml_ceh_error fcml_ifn_asm_instruction_part_processor_operand_encoder_wrapper( fcml_ien_asm_part_processor_phase phase, fcml_st_asm_encoding_context *context, fcml_st_def_addr_mode_desc *addr_mode_def, fcml_st_asm_instruction_part *instruction_part, fcml_ptr args ) {
	struct fcml_ist_asm_operand_encoder_wrapper_args *wrapper_args = (struct fcml_ist_asm_operand_encoder_wrapper_args*)args;
	fcml_st_operand *operand = &(context->instruction->operands[wrapper_args->operand_index]);
	if( wrapper_args->operand_encoder ) {
		return wrapper_args->operand_encoder( phase, context, addr_mode_def, wrapper_args->decoded_addr_mode, operand, instruction_part );
	} else {
		return FCML_CEH_GEC_NO_ERROR;
	}
}

fcml_ifn_asm_instruction_part_processor_descriptor fcml_ifn_asm_instruction_part_processor_factory_operand_encoder_wrapper( fcml_uint32_t flags, fcml_st_def_instruction_description *instruction, fcml_st_def_addr_mode_desc *addr_mode, fcml_ceh_error *error ) {

	fcml_ifn_asm_instruction_part_processor_descriptor descriptor = {0};

	struct fcml_ist_asm_operand_encoder_wrapper_args *wrapper_args = fcml_fn_env_clear_memory_alloc( sizeof( struct fcml_ist_asm_operand_encoder_wrapper_args ) );
	if( !wrapper_args ) {
		*error = FCML_CEH_GEC_OUT_OF_MEMORY;
		return descriptor;
	}

	if( addr_mode->opperands[flags] != FCML_NA ) {

		wrapper_args->decoded_addr_mode = fcml_fnp_def_decode_addr_mode_args( addr_mode->opperands[flags], error );
		if( *error ) {
			return descriptor;
		}

		fcml_st_asm_operand_encoder_def *encoders_def = &(fcml_def_operand_encoders[wrapper_args->decoded_addr_mode->addr_mode]);
		wrapper_args->operand_encoder = encoders_def->encoder;
		wrapper_args->operand_acceptor = encoders_def->acceptor;

		descriptor.processor_type = FCML_IEN_ASM_IPPT_ENCODER;
	} else {
		descriptor.processor_type = FCML_IEN_ASM_IPPT_VERIFIER;
	}

	wrapper_args->operand_index = flags;

	descriptor.processor_args_deallocator = fcml_ifn_asm_processor_operand_encoder_args_deallocator;
	descriptor.processor_encoder = fcml_ifn_asm_instruction_part_processor_operand_encoder_wrapper;
	descriptor.processor_acceptor = fcml_ifn_asm_instruction_part_processor_acceptor_operand_encoder_wrapper;
	descriptor.processor_args = wrapper_args;

	return descriptor;
}

////////////////////////////////////
// Simple opcode encoder factory. //
////////////////////////////////////

fcml_ceh_error fcml_ifn_asm_instruction_part_processor_simple_opcode_encoder_acceptor( fcml_st_asm_encoding_context *context, fcml_st_def_addr_mode_desc *addr_mode_desc, fcml_st_instruction *instruction, fcml_ptr args ) {
	// Simple opcode encoder can be always applied.
	return FCML_CEH_GEC_NO_ERROR;
}

fcml_ceh_error fcml_ifn_asm_instruction_part_processor_simple_opcode_encoder( fcml_ien_asm_part_processor_phase phase, fcml_st_asm_encoding_context *context, fcml_st_def_addr_mode_desc *addr_mode_def, fcml_st_asm_instruction_part *instruction_part, fcml_ptr args ) {
	if( phase == FCML_IEN_ASM_IPPP_FIRST_PHASE ) {
		int opcode_bytes = FCML_DEF_OPCODE_FLAGS_OPCODE_NUM( addr_mode_def->opcode_flags );
		int i;
		for( i = 0; i < opcode_bytes; i++ ) {
			instruction_part->code[i] = addr_mode_def->opcode[i];
		}
		instruction_part->code_length = opcode_bytes;
	}
	return  FCML_CEH_GEC_NO_ERROR;
}

fcml_ifn_asm_instruction_part_processor_descriptor fcml_ifn_asm_instruction_part_processor_factory_simple_opcode_encoder( fcml_uint32_t flags, fcml_st_def_instruction_description *instruction, fcml_st_def_addr_mode_desc *addr_mode, fcml_ceh_error *error ) {
	fcml_ifn_asm_instruction_part_processor_descriptor descriptor = {0};
	descriptor.processor_type = FCML_IEN_ASM_IPPT_ENCODER;
	descriptor.processor_args = NULL;
	descriptor.processor_encoder = fcml_ifn_asm_instruction_part_processor_simple_opcode_encoder;
	descriptor.processor_acceptor = fcml_ifn_asm_instruction_part_processor_simple_opcode_encoder_acceptor;
	return descriptor;
}

/////////////////////////////////
// Prefixes encoder factories. //
/////////////////////////////////

// 66 prefix.

fcml_ceh_error fcml_ifn_asm_instruction_part_processor_66_prefix_encoder( fcml_ien_asm_part_processor_phase phase, fcml_st_asm_encoding_context *context, fcml_st_def_addr_mode_desc *addr_mode_def, fcml_st_asm_instruction_part *instruction_part, fcml_ptr args ) {
	if( phase == FCML_IEN_ASM_IPPP_THIRD_PHASE ) {
		fcml_bool encode = FCML_FALSE;
		if( FCML_DEF_PREFIX_MANDATORY_66( addr_mode_def->allowed_prefixes ) ) {
			encode = FCML_TRUE;
		} else {
			encode = ( context->assembler_context->addr_form == FCML_AF_16_BIT && context->data_size_flags.effective_operand_size == FCML_DS_32 ) ||
					( ( context->assembler_context->addr_form == FCML_AF_32_BIT || context->assembler_context->addr_form == FCML_AF_64_BIT ) && context->data_size_flags.effective_operand_size == FCML_DS_16 );
		}
		if( encode ) {
			instruction_part->code[0] = 0x66;
			instruction_part->code_length = 1;
		}
	}
	return FCML_CEH_GEC_NO_ERROR;
}

fcml_ifn_asm_instruction_part_processor_descriptor fcml_ifn_asm_instruction_part_processor_factory_66_prefix_encoder( fcml_uint32_t flags, fcml_st_def_instruction_description *instruction, fcml_st_def_addr_mode_desc *addr_mode, fcml_ceh_error *error ) {
	fcml_ifn_asm_instruction_part_processor_descriptor descriptor = {0};

	// 66 prefix can be applied to instructions without neither XOP nor VEX prefixes. Remember that this prefix can bes mandatory one.
	if( ( FCML_DEF_PREFIX_MANDATORY_66( addr_mode->allowed_prefixes ) ||
			( !FCML_DEF_PREFIX_VEX_REQ( addr_mode->allowed_prefixes ) && !FCML_DEF_PREFIX_XOP_REQ( addr_mode->allowed_prefixes ) ) ) ) {
		descriptor.processor_type = FCML_IEN_ASM_IPPT_ENCODER;
		descriptor.processor_args = NULL;
		descriptor.processor_encoder = fcml_ifn_asm_instruction_part_processor_66_prefix_encoder;
		descriptor.processor_acceptor = NULL;
	}

	return descriptor;
}

// REX prefix.

fcml_ceh_error fcml_ifn_asm_instruction_part_processor_REX_prefix_encoder( fcml_ien_asm_part_processor_phase phase, fcml_st_asm_encoding_context *context, fcml_st_def_addr_mode_desc *addr_mode_def, fcml_st_asm_instruction_part *instruction_part, fcml_ptr args ) {
	if( phase == FCML_IEN_ASM_IPPP_FIRST_PHASE ) {
		if( FCML_DEF_PREFIX_W_1( addr_mode_def->allowed_prefixes ) ) {
			context->data_size_flags.effective_operand_size = FCML_DS_64;
		}
	} if( phase == FCML_IEN_ASM_IPPP_THIRD_PHASE ) {

		// REX prefix is only available in 64 bit mode. Neither VEX nor XOP are allowed here,
		// but it's checked before this encoder is registered for
		if( context->assembler_context->addr_form == FCML_AF_64_BIT ) {

			fcml_uint8_t rex = FCML_ENCODE_REX_BASE;

			fcml_st_asm_data_size_flags *size_flags = &(context->data_size_flags);
			fcml_st_encoded_modrm *encoded_mod_rm = &(context->encoded_mod_rm);

			// W field.
			fcml_data_size eosa = size_flags->effective_operand_size;
			if( FCML_DEF_PREFIX_W_1( addr_mode_def->allowed_prefixes ) ) {
				if( eosa != 0 && eosa != FCML_DS_64  ) {
					// Operand size should be 64 bits.
					return FCML_EN_UNSUPPORTED_OPPERAND_SIZE;
				}
				rex = FCML_ENCODE_REX_W( rex, 1 );
			} else if( eosa == FCML_DS_64 ) {
				rex = FCML_ENCODE_REX_W( rex, 1 );
			}

			// Fields.
			rex = FCML_ENCODE_REX_R( rex, encoded_mod_rm->ext_r );
			rex = FCML_ENCODE_REX_X( rex, encoded_mod_rm->ext_x );
			rex = FCML_ENCODE_REX_B( rex, encoded_mod_rm->ext_b );

			if( rex != FCML_ENCODE_REX_BASE ) {
				instruction_part->code[0] = rex;
				instruction_part->code_length = 1;
			}

		}
	}
	return FCML_CEH_GEC_NO_ERROR;
}

fcml_ifn_asm_instruction_part_processor_descriptor fcml_ifn_asm_instruction_part_processor_factory_REX_prefix_encoder( fcml_uint32_t flags, fcml_st_def_instruction_description *instruction, fcml_st_def_addr_mode_desc *addr_mode, fcml_ceh_error *error ) {
	fcml_ifn_asm_instruction_part_processor_descriptor descriptor = {0};
	// 66 prefix can be applied to instructions without neither XOP nor VEX prefixes. Remember that this prefix can bes mandatory one.
	if( FCML_DEF_OPCODE_FLAGS_64_BIT_MODE_SUPPORTED( addr_mode->opcode_flags ) ) {
		descriptor.processor_type = FCML_IEN_ASM_IPPT_ENCODER;
		descriptor.processor_args = NULL;
		descriptor.processor_encoder = fcml_ifn_asm_instruction_part_processor_REX_prefix_encoder;
		descriptor.processor_acceptor = NULL;
	}
	return descriptor;
}

/////////////////////////////////
// ModR/M encoder factories.   //
/////////////////////////////////

fcml_ceh_error fcml_st_asm_instruction_part_rip_post_processor( fcml_st_asm_encoding_context *context, fcml_st_asm_instruction_part *instruction_part, fcml_ptr post_processor_args ) {
	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
	fcml_st_assembler_context *assembler_context = context->assembler_context;
	fcml_st_encoded_modrm *encoded_mod_rm = &(context->encoded_mod_rm);

	if( !context->instruction_size.is_not_null ) {
		// Should never happened.
		error = FCML_CEH_GEC_INTERNAL_BUG;
	} else {
		// Encode ModR/M and displacement.
		fcml_st_memory_stream stream = fcml_ifn_instruction_part_stream( instruction_part );
		fcml_fn_stream_write( &stream, encoded_mod_rm->modrm );
		error = fcml_fn_modrm_encode_rip_offset( &stream, assembler_context->ip.rip, context->instruction_size.value, encoded_mod_rm );
	}

	return error;
}

fcml_ceh_error fcml_ifn_asm_instruction_part_processor_ModRM_encoder( fcml_ien_asm_part_processor_phase phase, fcml_st_asm_encoding_context *context, fcml_st_def_addr_mode_desc *addr_mode_def, fcml_st_asm_instruction_part *instruction_part, fcml_ptr args ) {
	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
	fcml_st_assembler_context *assembler_context = context->assembler_context;
	if( phase == FCML_IEN_ASM_IPPP_SECOND_PHASE ) {

		fcml_st_modrm_encoder_context ctx;
		ctx.addr_form = assembler_context->addr_form;
		ctx.choose_sib_encoding = assembler_context->configuration.choose_sib_encoding;
		ctx.choose_rip_encoding = assembler_context->configuration.choose_rip_encoding;
		ctx.chosen_effective_address_size = 0;
		ctx.effective_address_size = fcml_ifn_get_effective_address_size( context );
		ctx.is_sib_alternative = FCML_FALSE;
		ctx.is_rip_encoding = FCML_FALSE;

		if( FCML_DEF_OPCODE_FLAGS_OPCODE_IS_EXT( addr_mode_def->opcode_flags ) ) {
			context->mod_rm.reg_opcode = FCML_DEF_OPCODE_FLAGS_OPCODE_EXT( addr_mode_def->opcode_flags );
		}

		// Encodes ModR/M bytes.
		error = fcml_fn_modrm_encode( &ctx, &(context->mod_rm), &(context->encoded_mod_rm) );
		if( !error ) {
			context->data_size_flags.effective_address_size = ctx.chosen_effective_address_size;
			if( fcml_ifn_validate_effective_address_size( context ) ) {
				if( context->encoded_mod_rm.is_rip ) {
					// ModR/M + 4bytes displacement.
					instruction_part->code_length = 5;
					instruction_part->post_processor = fcml_st_asm_instruction_part_rip_post_processor;
					instruction_part->post_processor_args = NULL;
				} else {
					fcml_st_memory_stream stream = fcml_ifn_instruction_part_stream( instruction_part );
					fcml_st_encoded_modrm *encoded_modrm = &(context->encoded_mod_rm);
					fcml_fn_stream_write( &stream, encoded_modrm->modrm );
					if( encoded_modrm->sib.is_not_null ) {
						fcml_fn_stream_write( &stream, encoded_modrm->sib.value );
					}
					if( encoded_modrm->displacement_size ) {
						fcml_fn_stream_write_bytes( &stream, &(encoded_modrm->displacement), encoded_modrm->displacement_size );
					}
					instruction_part->code_length = stream.offset;
				}
			} else {
				error = FCML_EN_UNSUPPORTED_ADDRESS_SIZE;
			}
		}

	}
	return error;
}

fcml_ifn_asm_instruction_part_processor_descriptor fcml_ifn_asm_instruction_part_processor_factory_ModRM_encoder( fcml_uint32_t flags, fcml_st_def_instruction_description *instruction, fcml_st_def_addr_mode_desc *addr_mode, fcml_ceh_error *error ) {
	fcml_ifn_asm_instruction_part_processor_descriptor descriptor = {0};
	// Check if instruction has ModR/M byte.
	if( FCML_DEF_OPCODE_FLAGS_OPCODE_IS_MODRM( addr_mode->opcode_flags ) ) {
		descriptor.processor_type = FCML_IEN_ASM_IPPT_ENCODER;
		descriptor.processor_args = NULL;
		descriptor.processor_encoder = fcml_ifn_asm_instruction_part_processor_ModRM_encoder;
		descriptor.processor_acceptor = NULL;
	}
	return descriptor;
}

/////////////////////////////////
// Addressing mode validators. //
/////////////////////////////////

fcml_ceh_error fcml_ifn_asm_instruction_part_processor_addr_mode_acceptor( fcml_st_asm_encoding_context *context, fcml_st_def_addr_mode_desc *addr_mode_def, fcml_st_instruction *instruction, fcml_ptr args ) {
	fcml_en_addr_form addr_form = context->assembler_context->addr_form;
	if( !FCML_DEF_OPCODE_FLAGS_64_BIT_MODE_SUPPORTED( addr_mode_def->opcode_flags ) && addr_form == FCML_AF_64_BIT ) {
		return FCML_EN_UNSUPPORTED_ADDRESSING_MODE;
	} else if ( !FCML_DEF_OPCODE_FLAGS_16_32_BIT_MODE_SUPPORTED( addr_mode_def->opcode_flags ) && ( addr_form == FCML_AF_16_BIT || addr_form == FCML_AF_32_BIT ) ) {
		return FCML_EN_UNSUPPORTED_ADDRESSING_MODE;
	}
	return FCML_CEH_GEC_NO_ERROR;
}

fcml_ifn_asm_instruction_part_processor_descriptor fcml_ifn_asm_instruction_part_processor_factory_addr_mode_acceptor( fcml_uint32_t flags, fcml_st_def_instruction_description *instruction, fcml_st_def_addr_mode_desc *addr_mode, fcml_ceh_error *error ) {
	fcml_ifn_asm_instruction_part_processor_descriptor descriptor = {0};
	descriptor.processor_type = FCML_IEN_ASM_IPPT_VERIFIER;
	descriptor.processor_args = NULL;
	descriptor.processor_encoder = NULL;
	descriptor.processor_acceptor = fcml_ifn_asm_instruction_part_processor_addr_mode_acceptor;
	return descriptor;
}

//////////////////////////////////////////////
// Instruction parts factories definitions. //
//////////////////////////////////////////////

typedef struct fcml_ist_asm_instruction_part_factory_details {
	fcml_ifn_asm_instruction_part_processor_factory factory;
	uint32_t flags;
} fcml_ist_asm_instruction_part_factory_details;

typedef enum fcml_st_instruction_part_choice_type {
	FCML_IPCT_ONE,
	FCML_IPCT_ALL,
} fcml_st_instruction_part_choice_type;

typedef struct fcml_ist_asm_instruction_part_factory_sequence {
	fcml_ist_asm_instruction_part_factory_details *details;
	fcml_st_instruction_part_choice_type choice_type;
} fcml_ist_asm_instruction_part_factory_sequence;

// List of instruction part encoders for instruction opcode.
fcml_ist_asm_instruction_part_factory_details fcml_asm_instruction_part_processor_factories_opcode_for_IA[] = {
	{ fcml_ifn_asm_instruction_part_processor_factory_simple_opcode_encoder, 0 },
	{ NULL, 0 }
};

// List of instruction addressing mode acceptors.
fcml_ist_asm_instruction_part_factory_details fcml_asm_instruction_part_processor_factories_acceptors_IA[] = {
	{ fcml_ifn_asm_instruction_part_processor_factory_addr_mode_acceptor, 0 },
	{ NULL, 0 }
};

// List of instruction part encoders for instruction prefixes.
fcml_ist_asm_instruction_part_factory_details fcml_asm_instruction_part_processor_factories_prefixes_for_IA[] = {
	{ fcml_ifn_asm_instruction_part_processor_factory_66_prefix_encoder, 0 },
	{ fcml_ifn_asm_instruction_part_processor_factory_REX_prefix_encoder, 0 },
	{ NULL, 0 }
};

// ModR/M byte encoder.
fcml_ist_asm_instruction_part_factory_details fcml_asm_instruction_part_processor_factories_ModRM_for_IA[] = {
	{ fcml_ifn_asm_instruction_part_processor_factory_ModRM_encoder, 0 },
	{ NULL, 0 }
};

// List of instruction part encoders for instruction operands.
fcml_ist_asm_instruction_part_factory_details fcml_asm_instruction_part_processor_factories_operands_for_IA[] = {
	{ fcml_ifn_asm_instruction_part_processor_factory_operand_encoder_wrapper, 0 },
	{ fcml_ifn_asm_instruction_part_processor_factory_operand_encoder_wrapper, 1 },
	{ fcml_ifn_asm_instruction_part_processor_factory_operand_encoder_wrapper, 2 },
	{ fcml_ifn_asm_instruction_part_processor_factory_operand_encoder_wrapper, 3 },
	{ fcml_ifn_asm_instruction_part_processor_factory_operand_encoder_wrapper, 4 },
	{ NULL, 0 }
};

fcml_ist_asm_instruction_part_factory_sequence fcml_asm_instruction_part_processor_factory_sequences_for_IA[] = {
	{ fcml_asm_instruction_part_processor_factories_acceptors_IA, FCML_IPCT_ALL },
	{ fcml_asm_instruction_part_processor_factories_prefixes_for_IA, FCML_IPCT_ALL },
	{ fcml_asm_instruction_part_processor_factories_opcode_for_IA, FCML_IPCT_ONE },
	{ fcml_asm_instruction_part_processor_factories_ModRM_for_IA, FCML_IPCT_ALL },
	{ fcml_asm_instruction_part_processor_factories_operands_for_IA, FCML_IPCT_ALL },
	{ NULL }
};

fcml_ifn_asm_instruction_part_processor_chain* fcml_ifn_asm_instruction_part_processor_factory_dispatcher_IA( fcml_st_def_instruction_description *instruction, fcml_st_def_addr_mode_desc *addr_mode, int *parts, fcml_ceh_error *error ) {
	int instruction_parts = 0;
	fcml_ifn_asm_instruction_part_processor_chain *chain = NULL;
	fcml_ifn_asm_instruction_part_processor_chain *current_chain = NULL;
	fcml_ist_asm_instruction_part_factory_sequence *current_factories_sequence = &fcml_asm_instruction_part_processor_factory_sequences_for_IA[0];
	while( current_factories_sequence->details ) {
		fcml_st_instruction_part_choice_type choice = current_factories_sequence->choice_type;
		fcml_ist_asm_instruction_part_factory_details *current_factory = current_factories_sequence->details;
		while( current_factory->factory ) {
			fcml_ifn_asm_instruction_part_processor_descriptor descriptor = current_factory->factory( current_factory->flags, instruction, addr_mode, error );
			if( descriptor.processor_encoder || descriptor.processor_acceptor ) {

				// Allocate chain element for new instruction part encoder.
				fcml_ifn_asm_instruction_part_processor_chain *new_chain = fcml_fn_env_clear_memory_alloc( sizeof( fcml_ifn_asm_instruction_part_processor_chain ) );
				if( !new_chain ) {
					*error = FCML_CEH_GEC_OUT_OF_MEMORY;
					fcml_ifn_asm_free_part_processor_chain( chain );
					return NULL;
				}

				if( !chain ) {
					chain = new_chain;
					current_chain = new_chain;
				} else {
					current_chain->next_processor = new_chain;
					current_chain = new_chain;
				}

				current_chain->processor_descriptor = descriptor;

				if( descriptor.processor_type == FCML_IEN_ASM_IPPT_ENCODER ) {
					instruction_parts++;
				}

				if( choice == FCML_IPCT_ONE ) {
					break;
				}
			}
			if( *error ) {
				fcml_ifn_asm_free_part_processor_chain( chain );
				return NULL;
			}
			current_factory++;
		}

		current_factories_sequence++;
	}

	*parts = instruction_parts;

	return chain;
}

fcml_ifn_asm_instruction_part_processor_factory_dispatcher fcml_ifn_get_instruction_part_processor_factory_dispatcher_for_instruction_type( fcml_en_def_instruction_type instruction_type ) {
	fcml_ifn_asm_instruction_part_processor_factory_dispatcher dispatcher = NULL;
	switch( instruction_type ) {
	case FCML_EN_IT_IA:
		dispatcher = fcml_ifn_asm_instruction_part_processor_factory_dispatcher_IA;
		break;
	}
	return dispatcher;
}

fcml_st_asm_instruction_addr_mode *fcml_ifn_asm_prepare_addr_mode( fcml_st_def_instruction_description *instruction, fcml_st_def_addr_mode_desc *addr_mode_desc, fcml_ceh_error *error ) {

	fcml_st_asm_instruction_addr_mode *addr_mode = (fcml_st_asm_instruction_addr_mode *)fcml_fn_env_clear_memory_alloc( sizeof( fcml_st_asm_instruction_addr_mode ) );
	if( !addr_mode ) {
		*error = FCML_CEH_GEC_OUT_OF_MEMORY;
		return NULL;
	}

	addr_mode->addr_mode_desc = addr_mode_desc;

	int instruction_parts;

	fcml_ifn_asm_instruction_part_processor_factory_dispatcher factory_dispatcher = fcml_ifn_get_instruction_part_processor_factory_dispatcher_for_instruction_type( instruction->instruction_type );

	addr_mode->part_processor_chain = factory_dispatcher( instruction, addr_mode_desc, &instruction_parts, error );
	if( *error ) {
		fcml_fn_env_memory_free(addr_mode);
		addr_mode = NULL;
	}

	addr_mode->instruction_parts = instruction_parts;

	return addr_mode;
}

void fcml_ifn_asm_free_addr_mode( fcml_st_asm_instruction_addr_mode *addr_mode ) {
	if( addr_mode ) {
		fcml_fn_env_memory_free( addr_mode );
	}
}

void fcml_ifn_asm_free_instruction_addr_mode_item_handler( fcml_ptr item_value, fcml_ptr *args ) {
	fcml_st_asm_instruction_addr_mode *addr_mode = (fcml_st_asm_instruction_addr_mode*)item_value;
	if( addr_mode->part_processor_chain ) {
		fcml_ifn_asm_free_part_processor_chain( addr_mode->part_processor_chain );
	}
	fcml_ifn_asm_free_addr_mode( addr_mode );
}

void fcml_ifn_asm_free_instruction_entry( fcml_ptr key, fcml_ptr value ) {
	fcml_st_asm_instruction_addr_modes *addr_modes = (fcml_st_asm_instruction_addr_modes*)value;
	if( addr_modes ) {
		if( addr_modes->addr_modes ) {
			fcml_fn_coll_list_free( addr_modes->addr_modes, fcml_ifn_asm_free_instruction_addr_mode_item_handler );
		}
		fcml_fn_env_memory_free( addr_modes );
	}
}

fcml_fnp_asm_instruction_encoder fcml_ifn_asm_choose_instruction_encoder( fcml_en_def_instruction_type instruction_type ) {
	fcml_fnp_asm_instruction_encoder encoder = NULL;
	switch( instruction_type ) {
	case FCML_EN_IT_IA:
		encoder = fcml_fnp_asm_instruction_encoder_IA;
		break;
	}
	return encoder;
}

void fcml_ifn_asm_add_instruction_encoding( fcml_st_def_instruction_description *instruction, fcml_ceh_error *error ) {

	// Prepare encoders for given instruction.
	int i;
	for( i = 0; i < instruction->opcode_desc_count; i++ ) {

		fcml_st_def_addr_mode_desc *addr_mode_desc = &(instruction->addr_modes[i]);

		fcml_string mnemonic = addr_mode_desc->mnemonic_override;
		if( !mnemonic ) {
			mnemonic = instruction->mnemonic;
		}

		fcml_st_asm_instruction_addr_modes *addr_modes = (fcml_st_asm_instruction_addr_modes*)fcml_fn_coll_map_get( instructions_map, mnemonic );
		if( !addr_modes ) {

			// Allocate space for new mnemonic.
			addr_modes = fcml_fn_env_memory_alloc( sizeof(fcml_st_asm_instruction_addr_modes) );
			if( !addr_modes ) {
				// Out of memory.
				*error = FCML_CEH_GEC_OUT_OF_MEMORY;
				break;
			}

			// Allocate list for addresing modes.
			addr_modes->addr_modes = fcml_fn_coll_list_alloc();
			if( !(addr_modes->addr_modes) ) {
				fcml_fn_env_memory_free(addr_modes);
				*error = FCML_CEH_GEC_OUT_OF_MEMORY;
				break;
			}

			addr_modes->mnemonic = mnemonic;
			addr_modes->instruction_encoder = fcml_ifn_asm_choose_instruction_encoder( instruction->instruction_type );

			// Puts prepared structure under mnemonic key.
			fcml_fn_coll_map_put( instructions_map, mnemonic, addr_modes, error );
			if( *error ) {
				fcml_fn_coll_list_free( addr_modes->addr_modes, fcml_ifn_asm_free_instruction_addr_mode_item_handler );
				fcml_fn_env_memory_free(addr_modes);
				break;
			}

		}

		fcml_st_asm_instruction_addr_mode *addr_mode = fcml_ifn_asm_prepare_addr_mode( instruction, addr_mode_desc, error );
		if( !*error ) {
			if( !fcml_fn_coll_list_add_back( addr_modes->addr_modes, addr_mode ) ) {
				*error = FCML_CEH_GEC_OUT_OF_MEMORY;
				fcml_ifn_asm_free_addr_mode( addr_mode );
				break;
			}
		} else {
			break;
		}

		addr_mode_desc++;
	}
}

fcml_ceh_error fcml_fn_asm_init_instruction_encodings() {

	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

	// Allocate map for all instructions.
	fcml_st_coll_map_descriptor inst_map_desc = fcml_coll_map_descriptor_string;
	inst_map_desc.entry_free_function = fcml_ifn_asm_free_instruction_entry;

	instructions_map = fcml_fn_coll_map_alloc( &inst_map_desc, 64, &error );
	if( !instructions_map ) {
		return error;
	}

	int i = 0;
	fcml_st_def_instruction_description *instruction = &(fcml_ext_instructions_def[i++]);
	while( instruction->mnemonic && !error ) {
		fcml_ifn_asm_add_instruction_encoding( instruction, &error );
		instruction = &(fcml_ext_instructions_def[i++]);
	}

	if( error ) {
		// Something failed, so free everything that have been properly allocated.
		fcml_fn_asm_free_instruction_encodings();
	}

	return error;

}

void fcml_fn_asm_free_instruction_encodings() {
	if( instructions_map ) {
		fcml_fn_coll_map_free( instructions_map );
		instructions_map = NULL;
	}
}

fcml_ceh_error fcml_fn_asm_get_instruction_encodings( fcml_string mnemonic, fcml_st_asm_instruction_addr_modes **addr_modes ) {

	if( !instructions_map ) {
		return FCML_CEH_GEC_NOT_INITIALIZED;
	}

	*addr_modes = (fcml_st_asm_instruction_addr_modes*)fcml_fn_coll_map_get( instructions_map, mnemonic );
	if( !*addr_modes ) {
		return FCML_EN_UNKNOWN_MNEMONIC;
	}

	return FCML_CEH_GEC_NO_ERROR;
}

