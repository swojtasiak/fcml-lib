/*
 * fcml_modrm_decoder.c
 *
 *  Created on: 19-05-2013
 *      Author: tAs
 */

#include "fcml_modrm_decoder.h"
#include "fcml_utils.h"
#include "fcml_env.h"

/* Register configurations used for 16 bit addressing form decoding */

struct fcml_st_register fcml_modrm_addressing_form_reg_array_16[8][2] = {
	{ { FCML_REG_GPR, FCML_DS_16, FCML_REG_BX, FCML_FALSE }, { FCML_REG_GPR, FCML_DS_16, FCML_REG_SI, FCML_FALSE } },
	{ { FCML_REG_GPR, FCML_DS_16, FCML_REG_BX, FCML_FALSE }, { FCML_REG_GPR, FCML_DS_16, FCML_REG_DI, FCML_FALSE } },
	{ { FCML_REG_GPR, FCML_DS_16, FCML_REG_BP, FCML_FALSE }, { FCML_REG_GPR, FCML_DS_16, FCML_REG_SI, FCML_FALSE } },
	{ { FCML_REG_GPR, FCML_DS_16, FCML_REG_BP, FCML_FALSE }, { FCML_REG_GPR, FCML_DS_16, FCML_REG_DI, FCML_FALSE } },
	{ { FCML_REG_GPR, FCML_DS_16, FCML_REG_SI, FCML_FALSE }, { FCML_REG_UNDEFINED, 0, 0, FCML_FALSE } },
	{ { FCML_REG_GPR, FCML_DS_16, FCML_REG_DI, FCML_FALSE }, { FCML_REG_UNDEFINED, 0, 0, FCML_FALSE } },
	{ { FCML_REG_GPR, FCML_DS_16, FCML_REG_BP, FCML_FALSE }, { FCML_REG_UNDEFINED, 0, 0, FCML_FALSE } },
	{ { FCML_REG_GPR, FCML_DS_16, FCML_REG_BX, FCML_FALSE }, { FCML_REG_UNDEFINED, 0, 0, FCML_FALSE } }
};

fcml_ceh_error fcml_fn_modrm_decode_displacement( fcml_st_memory_stream *stream, fcml_st_displacement *displacement, fcml_usize size, fcml_usize size_ext ) {

	fcml_ceh_error error;

	fcml_vint vint;
	error = fcml_fn_utils_decode_vint( stream, &vint, size );
	if( error ) {
		return error;
	}

	if( size != size_ext ) {
		error = fcml_fn_utils_extend_vint( &vint, size_ext );
		if( error ) {
			return FCML_EN_UNSUPPORTED_ADDRESSING_MODE;
		}
	}

	error = fcml_fn_utils_vint_to_displacement( &vint, displacement );
	if( error ) {
		return FCML_EN_UNSUPPORTED_ADDRESSING_MODE;
	}

	displacement->size = size;
	displacement->sign_extension = size_ext;

	return error;
}

fcml_ceh_error fcml_fn_modrm_decode_16bit( fcml_st_modrm_context *context, fcml_st_modrm_source *modrm_source, fcml_st_modrm *decoded_modrm ) {

	fcml_bool result;
	fcml_st_memory_stream *stream = &(modrm_source->stream);

	fcml_fn_env_memory_clean( decoded_modrm, sizeof( fcml_st_modrm ) );

	if( context->addr_form != FCML_MODRM_AF_32_BIT ) {
		return FCML_EN_UNSUPPORTED_ADDRESSING_MODE;
	}

	// Gets ModR/M byte from stream.
	fcml_uint8_t mod_rm = fcml_fn_stream_read( stream, &result );
	if( !result ) {
		return FCML_CEH_GEC_EOF;
	}

	// Decode ModRM.
	fcml_uint8_t f_mod = FCML_MODRM_DEC_MOD(mod_rm);
	fcml_uint8_t f_rm = FCML_MODRM_DEC_RM(mod_rm);
	fcml_uint8_t f_reg_opcode = FCML_MODRM_DEC_REG_OPCODE(mod_rm);

	if( modrm_source->is_vsib ) {
		return FCML_EN_UNSUPPORTED_ADDRESSING_MODE;
	}

	if( f_mod == 0 && f_rm == 6 ) {
		// disp16.
		fcml_ceh_error error = fcml_fn_modrm_decode_displacement( stream, &(decoded_modrm->displacement), FCML_DS_16, FCML_DS_16 );
		if( error ) {
			return error;
		}
	} else if( f_mod < 3 ) {
		decoded_modrm->base = fcml_modrm_addressing_form_reg_array_16[f_rm][0];
		decoded_modrm->index = fcml_modrm_addressing_form_reg_array_16[f_rm][1];
		if( f_mod > 0 ) {
			fcml_ceh_error error = fcml_fn_modrm_decode_displacement( stream, &(decoded_modrm->displacement), ( f_mod == 1 ) ? FCML_DS_8 : FCML_DS_16, FCML_DS_16 );
			if( error ) {
				return error;
			}
		}
	} else {
		// Straight copy of registers.
		decoded_modrm->reg.is_not_null = FCML_TRUE;
		decoded_modrm->reg.value = f_rm;
	}

	decoded_modrm->reg_opcode = f_reg_opcode;

	return FCML_CEH_GEC_NO_ERROR;
}

fcml_ceh_error fcml_fn_modrm_decode_3264bit( fcml_st_modrm_context *context, fcml_st_modrm_source *modrm_source, fcml_st_modrm *decoded_modrm ) {
	return FCML_CEH_GEC_NO_ERROR;
}

fcml_ceh_error fcml_fn_modrm_decode( fcml_st_modrm_context *context, fcml_st_modrm_source *modrm_source, fcml_st_modrm *decoded_modrm ) {
	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
	if( context->effective_address_size == FCML_DS_16 ) {
		error = fcml_fn_modrm_decode_16bit( context, modrm_source, decoded_modrm );
	} else if ( context->effective_address_size == FCML_DS_32 || context->effective_address_size == FCML_DS_64 ) {
		error = fcml_fn_modrm_decode_3264bit( context, modrm_source, decoded_modrm );
	} else {
		// Unknown addressing mode.
		error = FCML_EN_UNSUPPORTED_ADDRESSING_MODE;
	}
	return error;
}


