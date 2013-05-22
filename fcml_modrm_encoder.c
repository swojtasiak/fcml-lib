/*
 * fcml_modrm_encoder.c
 *
 *  Created on: 19-05-2013
 *      Author: tAs
 */

#include "fcml_modrm_encoder.h"

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
		if( reg.size > FCML_DS_8 ) {
			easa = reg.size >> 4;
		} else {
			error = FCML_EN_UNSUPPORTED_ADDRESSING_MODE;
		}
	} else if ( decoded_modrm->displacement.size ) {
		// Base register is not available, but displacement is.
		if( decoded_modrm->displacement.size <= FCML_DS_16 ) {
			easa = FCML_DS_16 | FCML_DS_32 | FCML_DS_64;
		} else {
			easa = FCML_DS_32 | FCML_DS_64;
		}
	}

	if( error ) {
		return error;
	}

	// Calculate EASA.

	*effective_address_size = easa;

	return error;
}

fcml_ceh_error fcml_fn_modrm_encode_16bit( fcml_st_modrm_context *context, const fcml_st_modrm *decoded_modrm, fcml_st_encoded_modrm *encoded_modrm ) {
	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
	return error;
}

fcml_ceh_error fcml_fn_modrm_encode_3264bit( fcml_st_modrm_context *context, const fcml_st_modrm *decoded_modrm, fcml_st_encoded_modrm *encoded_modrm ) {
	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
	return error;
}

fcml_ceh_error fcml_fn_modrm_encode( fcml_st_modrm_context *context, const fcml_st_modrm *decoded_modrm, fcml_st_encoded_modrm *encoded_modrm ) {

	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
	if( context->addr_form == FCML_MODRM_AF_16_BIT ) {
		error = fcml_fn_modrm_encode_16bit( context, decoded_modrm, encoded_modrm );
	} else if ( context->addr_form == FCML_MODRM_AF_32_BIT ) {
		error = fcml_fn_modrm_encode_3264bit( context, decoded_modrm, encoded_modrm );
	} else {
		// Unknown
		error = FCML_CEH_GEC_INVALID_INPUT;
	}
	return error;
}


