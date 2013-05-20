/*
 * fcml_modrm_encoder.c
 *
 *  Created on: 19-05-2013
 *      Author: tAs
 */

#include "fcml_modrm_encoder.h"

fcml_ceh_error fcml_fn_modrm_encode_16bit( fcml_st_modrm_context *context, const fcml_st_modrm *decoded_modrm, fcml_st_encoded_modrm *encoded_modrm ) {

}

fcml_ceh_error fcml_fn_modrm_encode_3264bit( fcml_st_modrm_context *context, const fcml_st_modrm *decoded_modrm, fcml_st_encoded_modrm *encoded_modrm ) {

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


