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

fcml_st_memory_stream fcml_ifn_map_displacement_to_stream( fcml_st_encoded_modrm *encoded_modrm ) {
	fcml_st_memory_stream stream;
	stream.base_address = &(encoded_modrm->displacement);
	stream.offset = 0;
	stream.size = sizeof(encoded_modrm->displacement);
	return stream;
}

// Optionaly extends and encodes displacement.
fcml_ceh_error fcml_ifn_modrm_encode_displacement( const fcml_st_displacement *displacement, fcml_st_encoded_modrm *encoded_modrm, fcml_usize extension ) {

	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

	// Converts displacement to signed variable size integer value.
	fcml_vint disp;
	error = fcml_fn_utils_displacement_to_vint( displacement, &disp );
	if( error ) {
		return error;
	}

	// Extend displacement value it there is such need.
	if( disp.size != extension ) {
		error = fcml_fn_utils_extend_vint( &disp, extension );
		if( error ) {
			return error;
		}
	}

	// Gets displacement as stream.
	fcml_st_memory_stream stream = fcml_ifn_map_displacement_to_stream( encoded_modrm );

	// Extends and encodes displacement to given stream.
	error = fcml_fn_utils_encode_vint( &stream, &disp );
	if( error ) {
		return error;
	}

	encoded_modrm->displacement_size = stream.offset;

	return error;
}

fcml_ceh_error fcml_fn_modrm_encode_16bit( fcml_st_modrm_context *context, const fcml_st_modrm *decoded_modrm, fcml_st_encoded_modrm *encoded_modrm ) {

	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

	// ModR/M fields.
	fcml_uint8_t f_reg = 0;
	fcml_uint8_t f_mod = 0;
	fcml_uint8_t f_rm = 0;

	// Check if there is disp16 addressing mode encoded.
	if( decoded_modrm->displacement.size && !decoded_modrm->base.type ) {
		// Sign extends displacement to 16 bits if there is such need, and encode it.
		error = fcml_ifn_modrm_encode_displacement( &(decoded_modrm->displacement), encoded_modrm, FCML_DS_16 );
	} else if ( decoded_modrm->base.type ) {

		// There is base register set.
		switch( decoded_modrm->base.reg ) {
		case FCML_REG_BX:
			if( decoded_modrm->index.type ) {
				if( decoded_modrm->index.reg == FCML_REG_DI ) {
					f_rm = 0x01;
				}
			} else {
				f_rm = 0x07;
			}
			break;
		case FCML_REG_BP:
			if( decoded_modrm->index.type ) {
				switch( decoded_modrm->index.reg ) {
				case FCML_REG_SI:
					f_rm = 0x02;
					break;
				case FCML_REG_DI:
					f_rm = 0x03;
					break;
				}
			} else if( !decoded_modrm->displacement.size ) {
				// BP is not allowed without displacement.
				error = FCML_EN_UNSUPPORTED_ADDRESSING_MODE;
			} else {
				f_rm = 0x06;
			}
			break;
		case FCML_REG_SI:
			f_rm = 0x04;
			break;
		case FCML_REG_DI:
			f_rm = 0x05;
			break;
		}

		if( !error ) {

			// Now encode displacement, is there is any.
			switch( decoded_modrm->displacement.size ) {
			case FCML_DS_UNDEF:
				f_mod = 0x00;
				break;
			case FCML_DS_8:
				f_mod = 0x01;
				break;
			case FCML_DS_16:
				f_mod = 0x02;
				break;
			default:
				// Only disp8 and disp16 is supporte in 16 bit addressing mode.
				error = FCML_EN_UNSUPPORTED_ADDRESSING_MODE;
				break;
			}

			if( f_mod > 0 ) {
				error = fcml_ifn_modrm_encode_displacement(  &(decoded_modrm->displacement), encoded_modrm, decoded_modrm->displacement.size );
			}
		}

	} else if ( decoded_modrm->reg.is_not_null ) {
		f_mod = 0x03;
		f_rm = decoded_modrm->reg.value;
	} else {
		// There is no base register and displacement, so
		error = FCML_EN_UNSUPPORTED_ADDRESSING_MODE;
	}

	if( !error ) {
		// Encode reg/opcode.
		f_reg = decoded_modrm->reg_opcode;
		// Encode calculated ModR/M byte.
		encoded_modrm->modrm = FCML_MODRM_ENC( f_mod, f_reg, f_rm );
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


