/*
 * fcml_modrm_encoder.c
 *
 *  Created on: 19-05-2013
 *      Author: tAs
 */

#include "fcml_modrm_encoder.h"
#include "fcml_utils.h"

fcml_ceh_error fcml_fn_modrm_calculate_efective_address_size( const fcml_st_modrm *decoded_modrm, fcml_esa *effective_address_size ) {

	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

	// Calculate EOSA.

	fcml_esa easa;

	fcml_st_register reg;
	if( decoded_modrm->base.type ) {
		reg = decoded_modrm->base;
	} else {
		reg = decoded_modrm->index;
	}
	if( reg.type ) {
		switch( reg.size ) {
		case FCML_DS_16:
		case FCML_DS_32:
		case FCML_DS_64:
			easa = reg.size >> 4;
			break;
		case FCML_DS_128:
		case FCML_DS_256:
			easa = FCML_ESA_SF_32 | FCML_ESA_SF_64;
			break;
		default:
			error = FCML_EN_UNSUPPORTED_ADDRESSING_MODE;
			break;
		}
	} else if ( decoded_modrm->displacement.size ) {
		// Base register is not available, but displacement is.
		if( decoded_modrm->displacement.size <= FCML_DS_16 ) {
			easa = FCML_ESA_SF_16 | FCML_ESA_SF_32 | FCML_ESA_SF_64;
		} else {
			easa = FCML_ESA_SF_32 | FCML_ESA_SF_64;
		}
	}

	if( error ) {
		return error;
	}

	// Calculate EASA.

	*effective_address_size = easa;

	return error;
}

/*
 * int result = _IRA_INT_ERROR_NO_ERROR;

	// ModR/M.
	uint8_t mod, rm;

	struct ira_decoding_context *decoding_context = &(context->decoding_context);
	struct ira_decoded_mod_rm *decoded_mod_rm = &(decoding_context->mod_rm);

	// Get raw ModR/M byte to decode it.
	uint8_t mod_rm = context->decoding_context.mod_rm.raw_mod_rm.value;

	// Decode ModRM.
	mod = _IRA_MODRM_MOD(mod_rm);
	rm = _IRA_MODRM_RM(mod_rm);

	if( args->is_vsib ) {
		return _IRA_INT_ERROR_ILLEGAL_ADDRESSING;
	}

	if( mod == 0 && rm == 6 ) {
		// disp16.
		result = _ira_decode_displacement( context, &(decoded_mod_rm->displacement), IRA_DISPLACEMENT_16, IRA_DISPLACEMENT_EXT_SIZE_16 );
	} else if( mod < 3 ) {
		decoded_mod_rm->base_reg = _ira_addressing_form_reg_array_16[rm][0];
		decoded_mod_rm->index_reg = _ira_addressing_form_reg_array_16[rm][1];
		if( mod > 0 ) {
			result = _ira_decode_displacement( context, &(decoded_mod_rm->displacement), ( mod == 1 ) ? IRA_DISPLACEMENT_8 : IRA_DISPLACEMENT_16, IRA_DISPLACEMENT_EXT_SIZE_16 );
		}
	} else {
		// Straight copy of registers.
		decoded_mod_rm->reg = _ira_modrm_decode_register( context, args->reg_type, args->register_operand_size, rm );
	}

	// Decode register if something needs it.
	if ( args->flags & _IRA_MOD_RM_FLAGS_DECODE_REG ) {
		decoded_mod_rm->operand_reg = _ira_modrm_decode_register( context, args->reg_type, args->register_operand_size, _IRA_MODRM_REG_OPCODE(mod_rm) );
		decoded_mod_rm->decoded_reg = _IRA_TRUE;
	}

	return result;
 */

fcml_st_memory_stream fcml_ifn_map_displacement_to_stream( fcml_st_encoded_modrm *encoded_modrm ) {
	fcml_st_memory_stream stream;
	stream.base_address = &(encoded_modrm->displacement);
	stream.offset = 0;
	stream.size = sizeof(encoded_modrm->displacement);
	return stream;
}

fcml_ceh_error fcml_fn_modrm_encode_16bit( fcml_st_modrm_context *context, const fcml_st_modrm *decoded_modrm, fcml_st_encoded_modrm *encoded_modrm ) {
	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

	// Check if there is disp16 addressing mode encoded.
	if( decoded_modrm->displacement.size && !decoded_modrm->base.type ) {
		fcml_st_memory_stream stream = fcml_ifn_map_displacement_to_stream( encoded_modrm );
		error = fcml_fn_utils_encode_displacement( &stream, &(decoded_modrm->displacement) );
		encoded_modrm->displacement_size = stream.offset;
	}

	return error;
}

fcml_ceh_error fcml_fn_modrm_encode_3264bit( fcml_st_modrm_context *context, const fcml_st_modrm *decoded_modrm, fcml_st_encoded_modrm *encoded_modrm ) {
	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
	return error;
}

fcml_ceh_error fcml_fn_modrm_encode( fcml_st_modrm_context *context, const fcml_st_modrm *decoded_modrm, fcml_st_encoded_modrm *encoded_modrm ) {
	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
	if( context->effective_address_size == FCML_DS_16 ) {
		error = fcml_fn_modrm_encode_16bit( context, decoded_modrm, encoded_modrm );
	} else if ( context->effective_address_size == FCML_DS_32 || context->effective_address_size == FCML_DS_64 ) {
		error = fcml_fn_modrm_encode_3264bit( context, decoded_modrm, encoded_modrm );
	} else {
		// Unknown
		error = FCML_CEH_GEC_INVALID_INPUT;
	}
	return error;
}


