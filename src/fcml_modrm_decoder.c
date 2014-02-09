/*
 * fcml_modrm_decoder.c
 *
 *  Created on: 19-05-2013
 *      Author: tAs
 */

#include "fcml_modrm_decoder.h"

#include <stddef.h>

#include "fcml_env.h"
#include <fcml_errors.h>
#include "fcml_utils.h"

/* Register configurations used for 16 bit addressing form decoding */

struct fcml_st_register fcml_iarr_modrm_addressing_form_reg_16[8][2] = {
	{ { FCML_REG_GPR, FCML_DS_16, FCML_REG_BX, FCML_FALSE }, { FCML_REG_GPR, FCML_DS_16, FCML_REG_SI, FCML_FALSE } },
	{ { FCML_REG_GPR, FCML_DS_16, FCML_REG_BX, FCML_FALSE }, { FCML_REG_GPR, FCML_DS_16, FCML_REG_DI, FCML_FALSE } },
	{ { FCML_REG_GPR, FCML_DS_16, FCML_REG_BP, FCML_FALSE }, { FCML_REG_GPR, FCML_DS_16, FCML_REG_SI, FCML_FALSE } },
	{ { FCML_REG_GPR, FCML_DS_16, FCML_REG_BP, FCML_FALSE }, { FCML_REG_GPR, FCML_DS_16, FCML_REG_DI, FCML_FALSE } },
	{ { FCML_REG_GPR, FCML_DS_16, FCML_REG_SI, FCML_FALSE }, { FCML_REG_UNDEFINED, 0, 0, FCML_FALSE } },
	{ { FCML_REG_GPR, FCML_DS_16, FCML_REG_DI, FCML_FALSE }, { FCML_REG_UNDEFINED, 0, 0, FCML_FALSE } },
	{ { FCML_REG_GPR, FCML_DS_16, FCML_REG_BP, FCML_FALSE }, { FCML_REG_UNDEFINED, 0, 0, FCML_FALSE } },
	{ { FCML_REG_GPR, FCML_DS_16, FCML_REG_BX, FCML_FALSE }, { FCML_REG_UNDEFINED, 0, 0, FCML_FALSE } }
};

fcml_ceh_error fcml_ifn_modrm_decode_displacement( fcml_st_memory_stream *stream, fcml_st_displacement *displacement, fcml_st_offset *offset, fcml_usize size, fcml_data_size offset_extension_size, fcml_data_size displacement_extension_size ) {

    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

    fcml_st_integer integer;
    error = fcml_fn_utils_decode_integer( stream, &integer, size );
    if( error ) {
        return error;
    }

    /* Offsets and displacement are signed integers.*/
    integer.is_signed = FCML_TRUE;

    if( displacement_extension_size ) {
   		fcml_fn_utils_extend_integer( &integer, displacement_extension_size );
   	}

    if( displacement ) {
        error = fcml_fn_utils_integer_to_displacement( &integer, displacement );
        if( error ) {
            return error;
        }
    }

    if( offset ) {

    	if( offset_extension_size ) {
			fcml_fn_utils_extend_integer( &integer, offset_extension_size );
		}

        error = fcml_fn_utils_integer_to_offset( &integer, offset );
        if( error ) {
            return FCML_CEH_GEC_INVALID_ADDRESSING_FORM;
        }

    }

    return error;
}

fcml_data_size fcml_ifn_modrm_get_displacement_extension( fcml_st_modrm_decoder_context *context, fcml_uint8_t flags ) {
	return flags & FCML_MODRM_DEC_FLAG_EXTEND_DISPLACEMENT_TO_ASA ? context->effective_address_size : 0;
}

fcml_ceh_error fcml_ifn_modrm_decode_16bit( fcml_st_modrm_decoder_context *context, fcml_st_modrm_source *modrm_source, fcml_st_modrm *decoded_modrm, fcml_st_modrm_details *modrm_details, fcml_uint8_t flags ) {

	fcml_bool result;
	fcml_st_memory_stream *stream = modrm_source->stream;

	/* Just in case.*/
	if( context->addr_form == FCML_AF_64_BIT ) {
		return FCML_CEH_GEC_INVALID_ADDRESSING_FORM;
	}

	fcml_st_address *address = &(decoded_modrm->address);
	fcml_st_effective_address *effective_address = &(address->effective_address);

	/* Gets ModR/M byte from stream.*/
	fcml_uint8_t mod_rm = fcml_fn_stream_read( stream, &result );
	if( !result ) {
		return FCML_CEH_GEC_EOF;
	}

	modrm_details->modrm = mod_rm;

	/* Decode ModRM.*/
	fcml_uint8_t f_mod = FCML_MODRM_DEC_MOD(mod_rm);
	fcml_uint8_t f_rm = FCML_MODRM_DEC_RM(mod_rm);
	fcml_uint8_t f_reg_opcode = FCML_MODRM_DEC_REG_OPCODE(mod_rm);

	if( modrm_source->is_vsib ) {
		return FCML_CEH_GEC_INVALID_ADDRESSING_FORM;
	}

	address->address_form = FCML_AF_COMBINED;

	if( f_mod == 0 && f_rm == 6 ) {

		/* disp16.*/
		fcml_ceh_error error = fcml_ifn_modrm_decode_displacement( stream, &(effective_address->displacement), &(address->offset), FCML_DS_16, context->effective_address_size, fcml_ifn_modrm_get_displacement_extension( context, flags ) );
		if( error ) {
			return error;
		}

		address->address_form = FCML_AF_OFFSET;

	} else if( f_mod < 3 ) {
	    effective_address->base = fcml_iarr_modrm_addressing_form_reg_16[f_rm][0];
	    effective_address->index = fcml_iarr_modrm_addressing_form_reg_16[f_rm][1];
		if( f_mod > 0 ) {
			fcml_ceh_error error = fcml_ifn_modrm_decode_displacement( stream, &(effective_address->displacement), NULL, ( f_mod == 1 ) ? FCML_DS_8 : FCML_DS_16, 0, fcml_ifn_modrm_get_displacement_extension( context, flags ) );
			if( error ) {
				return error;
			}
		}
	} else {
		/* Straight copy of registers.*/
		decoded_modrm->reg.is_not_null = FCML_TRUE;
		decoded_modrm->reg.value = f_rm;
	}

	decoded_modrm->reg_opcode = f_reg_opcode;

	return FCML_CEH_GEC_NO_ERROR;
}

fcml_ceh_error fcml_ifn_modrm_decode_sib( fcml_st_modrm_decoder_context *context, fcml_uint8_t mod_rm, fcml_st_modrm_source *modrm_source, fcml_st_modrm *decoded_modrm, fcml_st_modrm_details *modrm_details, fcml_uint8_t flags ) {

	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

	fcml_st_memory_stream *stream = modrm_source->stream;

	fcml_st_address *address = &(decoded_modrm->address);
    fcml_st_effective_address *effective_address = &(address->effective_address);

	/* Effective address size affects index register.*/
	fcml_data_size effective_address_size = context->effective_address_size;

	/* ModR/M fields.*/
	fcml_uint8_t f_base;
	fcml_uint8_t f_index;
	fcml_uint8_t f_scale;
	fcml_uint8_t f_mod;

	/* Get SIB.*/
	fcml_bool sib_found = FCML_FALSE;
	fcml_uint8_t sib = fcml_fn_stream_read( stream, &sib_found );
	if( !sib_found ) {
		return FCML_CEH_GEC_EOF;
	}

	modrm_details->sib.is_not_null = FCML_TRUE;
	modrm_details->sib.value = sib;

	f_mod = FCML_MODRM_DEC_MOD(mod_rm);
	f_base = FCML_MODRM_SIB_BASE(sib) | ( modrm_source->ext_b << 3 );
	f_index = FCML_MODRM_SIB_INDEX(sib) | ( modrm_source->ext_x << 3 );
	f_scale = FCML_MODRM_SIB_SS(sib);

	/* Index register and scale.*/
	if( FCML_MODRM_SIB_INDEX(sib) != 4 ) {
		if( modrm_source->is_vsib ) {
		    effective_address->index.type = FCML_REG_SIMD;
		    effective_address->index.size = modrm_source->vsib_index_size;
		} else {
		    effective_address->index.type = FCML_REG_GPR;
		    effective_address->index.size = ( effective_address_size == FCML_DS_64 ) ? FCML_DS_64 : FCML_DS_32;
		}
		effective_address->index.reg = f_index;
		/* Scale.*/
		effective_address->scale_factor = f_scale ? ( 1 << f_scale ) : 0; /* f_scale * 2*/
	}

	address->address_form = FCML_AF_COMBINED;

	/* Base register and displacement.*/
	if( f_mod == 0 && FCML_MODRM_SIB_BASE( sib ) == 5 ) {

	    address->address_form = FCML_AF_OFFSET;

		/* In this case base register doesn't exist.*/
	    error = fcml_ifn_modrm_decode_displacement( stream, &(effective_address->displacement), &(address->offset), FCML_DS_32, effective_address_size, 0 );

	} else {
		/* Effective address size affects base register.*/
	    effective_address->base.type = FCML_REG_GPR;
	    effective_address->base.size = (effective_address_size == FCML_DS_64) ? FCML_DS_64 : FCML_DS_32;
	    effective_address->base.reg = f_base;

		/* There is no displacement for mod == 0.*/
		if( f_mod > 0 ) {
			error = fcml_ifn_modrm_decode_displacement( stream, &(effective_address->displacement), NULL, ( f_mod == 1 ) ? FCML_DS_8 : FCML_DS_32, 0, fcml_ifn_modrm_get_displacement_extension( context, flags ) );
		}
	}

	return error;
}

fcml_ceh_error fcml_ifn_modrm_decode_3264bit( fcml_st_modrm_decoder_context *context, fcml_st_modrm_source *modrm_source, fcml_st_modrm *decoded_modrm, fcml_st_modrm_details *modrm_details, fcml_uint8_t flags ) {

	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

	fcml_st_memory_stream *stream = modrm_source->stream;

	fcml_st_address *address = &(decoded_modrm->address);
    fcml_st_effective_address *effective_address = &(address->effective_address);

	fcml_uint8_t f_mod;
	fcml_uint8_t f_rm;

	fcml_data_size effective_address_size = context->effective_address_size;

	/* Gets ModR/M byte from stream.*/
	fcml_bool result;
	fcml_uint8_t mod_rm = fcml_fn_stream_read( stream, &result );
	if( !result ) {
		return FCML_CEH_GEC_EOF;
	}

	modrm_details->modrm = mod_rm;

	/* Decode ModRM.*/
	f_mod = FCML_MODRM_DEC_MOD(mod_rm);
	f_rm = FCML_MODRM_DEC_RM(mod_rm) | ( modrm_source->ext_b << 3 );

	if( modrm_source->is_vsib && FCML_MODRM_DEC_RM( mod_rm ) != 4 ) {
		return FCML_CEH_GEC_INVALID_ADDRESSING_FORM;
	}

	address->address_form = FCML_AF_COMBINED;

	if( f_mod == 3 ) {
		/* Registers.*/
		decoded_modrm->reg.is_not_null = FCML_TRUE;
		decoded_modrm->reg.value = f_rm;
	} else if( FCML_MODRM_DEC_RM( mod_rm ) == 4 ) {
		/* Decode SIB addressing format.*/
		result = fcml_ifn_modrm_decode_sib( context, mod_rm, modrm_source, decoded_modrm, modrm_details, flags );
	} else if( f_mod == 0 && FCML_MODRM_DEC_RM( mod_rm ) == 5 ) {

	    address->address_form = FCML_AF_OFFSET;

		/* disp32.*/
		if( context->addr_form == FCML_AF_64_BIT ) {
			decoded_modrm->is_rip = FCML_TRUE;
			/* In case of RIP we also set base register to IP.*/
			decoded_modrm->address.effective_address.base.type = FCML_REG_IP;
			decoded_modrm->address.effective_address.base.size = FCML_DS_64;
		}

		/* Only displacement value is decoded here. RIP offset is calculated in post processors.*/
        error = fcml_ifn_modrm_decode_displacement( stream, &(effective_address->displacement), &(address->offset), FCML_DS_32, decoded_modrm->is_rip ? 0 : effective_address_size, 0 );
        if( error ) {
            return error;
        }

	} else {
		/* Base register.*/
		effective_address->base.type = FCML_REG_GPR;
		effective_address->base.size = ( effective_address_size == FCML_DS_64 ) ? FCML_DS_64 : FCML_DS_32;
		effective_address->base.reg = f_rm;
		/* Displacement.*/
		if( f_mod != 0 ) {
			error = fcml_ifn_modrm_decode_displacement( stream, &(effective_address->displacement), NULL, ( f_mod == 1 ) ? FCML_DS_8 : FCML_DS_32, 0, fcml_ifn_modrm_get_displacement_extension( context, flags ) );
			if( error ) {
				return error;
			}
		}
	}

	/* Decodes register if something needs it.*/
	decoded_modrm->reg_opcode = FCML_MODRM_DEC_REG_OPCODE( mod_rm ) | ( modrm_source->ext_r << 3 );

	return error;
}

fcml_ceh_error fcml_fn_modrm_decode_rip( fcml_uint64_t rip, fcml_data_size effective_address_size, fcml_st_offset *offset, fcml_st_offset *address ) {

	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

	fcml_int64_t effective_address = (fcml_int64_t)rip + offset->off32;

	if( effective_address_size == FCML_DS_32 ) {
		effective_address &= 0x00000000FFFFFFFFUL;
	} else if( effective_address_size == FCML_DS_16 ) {
		error = FCML_CEH_GEC_INVALID_ADDRESS_SIZE;
	}

	if( !error ) {
		address->off64 = effective_address;
		address->size = FCML_DS_64;
	}

	return error;
}

fcml_ceh_error fcml_fn_modrm_decode( fcml_st_modrm_decoder_context *context, fcml_st_modrm_source *modrm_source, fcml_st_modrm *decoded_modrm, fcml_st_modrm_details *modrm_details, fcml_uint8_t flags ) {
	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
	fcml_fn_env_memory_clear( decoded_modrm, sizeof( fcml_st_modrm ) );
	if( context->effective_address_size == FCML_DS_16 ) {
		error = fcml_ifn_modrm_decode_16bit( context, modrm_source, decoded_modrm, modrm_details, flags );
	} else if ( context->effective_address_size == FCML_DS_32 || context->effective_address_size == FCML_DS_64 ) {
		error = fcml_ifn_modrm_decode_3264bit( context, modrm_source, decoded_modrm, modrm_details, flags );
	} else {
		/* Unknown addressing mode.*/
		error = FCML_CEH_GEC_INVALID_ADDRESSING_MODE;
	}
	return error;
}


