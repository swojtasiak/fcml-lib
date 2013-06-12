/*
 * fcml_modrm_encoder.c
 *
 *  Created on: 19-05-2013
 *      Author: tAs
 */

#include "fcml_modrm_encoder.h"
#include "fcml_utils.h"

fcml_ceh_error fcml_fn_modrm_encode_rip_offset( fcml_st_memory_stream *stream, fcml_uint64_t rip, fcml_uint8_t instruction_size, fcml_st_encoded_modrm *encoded_modrm ) {

	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

	if( encoded_modrm->is_rip ) {
		fcml_int64_t rip_offset = ( encoded_modrm->rip_address + instruction_size ) - (fcml_int64_t)rip;

		if( rip_offset < FCML_INT32_MIN || rip_offset > FCML_INT32_MAX ) {
			error = FCML_CEH_GEC_VALUE_OUT_OF_RANGE;
		} else {

			fcml_uvint uvint;
			uvint.uint32 = (fcml_uint32_t)rip_offset;
			uvint.size = FCML_DS_32;

			// Extends and encodes displacement to given stream.
			error = fcml_fn_utils_encode_uvint( stream, &uvint );

		}
	} else {
		error = FCML_CEH_GEC_INVALID_INPUT;
	}

	return error;
}

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
fcml_ceh_error fcml_ifn_modrm_encode_displacement( const fcml_st_displacement *displacement, fcml_st_encoded_modrm *encoded_modrm, fcml_usize extension, fcml_bool is_rip ) {

	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

	// Zdekodowac displacement i zapsac go ewentualnie jako RIP do poziejzego rpzetworzenia przez post processing i encoer RIP z mod_rm_encoding.

	// Converts displacement to signed variable size integer value.
	fcml_vint disp;
	error = fcml_fn_utils_displacement_to_vint( displacement, &disp );
	if( error ) {
		return error;
	}

	if( is_rip ) {
		// Just in case.
		extension = FCML_DS_64;
	}

	// Extend displacement value if there is such need.
	if( disp.size != extension ) {
		error = fcml_fn_utils_extend_vint( &disp, extension );
		if( error ) {
			return error;
		}
	}

	if( is_rip ) {
		// Store RIP offset. It can be used then to calculate displacement
		encoded_modrm->is_rip = is_rip;
		encoded_modrm->rip_address = disp.int64;
	} else {
		// Gets displacement as stream.
		fcml_st_memory_stream stream = fcml_ifn_map_displacement_to_stream( encoded_modrm );

		// Extends and encodes displacement to given stream.
		error = fcml_fn_utils_encode_vint( &stream, &disp );
		if( error ) {
			return error;
		}

		encoded_modrm->displacement_size = stream.offset;
	}

	return error;
}

fcml_ceh_error fcml_fn_modrm_encode_16bit( fcml_st_modrm_encoder_context *context, const fcml_st_modrm *decoded_modrm, fcml_st_encoded_modrm *encoded_modrm ) {

	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

	// ModR/M fields.
	fcml_uint8_t f_reg = 0;
	fcml_uint8_t f_mod = 0;
	fcml_uint8_t f_rm = 0;

	if( context->addr_form == FCML_AF_64_BIT ) {
		return FCML_EN_UNSUPPORTED_ADDRESSING_MODE;
	}

	// Check if there is disp16 addressing mode encoded.
	if( decoded_modrm->displacement.size && !decoded_modrm->base.type ) {
		// Sign extends displacement to 16 bits if there is such need, and encode it.
		error = fcml_ifn_modrm_encode_displacement( &(decoded_modrm->displacement), encoded_modrm, FCML_DS_16, FCML_FALSE );
	} else if ( decoded_modrm->base.type ) {

		if( decoded_modrm->base.type && decoded_modrm->base.size != FCML_DS_16 ) {
			error = FCML_EN_UNSUPPORTED_ADDRESSING_MODE;
		}

		if( decoded_modrm->index.type && decoded_modrm->index.size != FCML_DS_16 ) {
			error = FCML_EN_UNSUPPORTED_ADDRESSING_MODE;
		}

		if( !error ) {

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
					error = fcml_ifn_modrm_encode_displacement(  &(decoded_modrm->displacement), encoded_modrm, decoded_modrm->displacement.size, FCML_FALSE );
				}
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

// 32 and 64 bit addressing mode.s
fcml_ceh_error fcml_fn_modrm_encode_3264bit( fcml_st_modrm_encoder_context *context, const fcml_st_modrm *decoded_modrm, fcml_st_encoded_modrm *encoded_modrm ) {

	fcml_uint8_t f_mod = 0;
	fcml_uint8_t f_rm = 0;
	fcml_uint8_t f_reg = 0;

	fcml_uint8_t f_ext_r = 0;
	fcml_uint8_t f_ext_x = 0;
	fcml_uint8_t f_ext_b = 0;

	fcml_data_size disp_size = 0;

	fcml_bool choose_sib = FCML_FALSE;

	// Check if addressing mode and effestive address size are compatible.
	if( ( context->effective_address_size == FCML_DS_64 && context->addr_form != FCML_AF_64_BIT ) || ( context->addr_form == FCML_AF_64_BIT && context->effective_address_size == FCML_DS_16 ) ) {
		return FCML_EN_UNSUPPORTED_ADDRESSING_MODE;
	}

	// Check if there is SIB alternative.
	if( decoded_modrm->index.type ) {
		choose_sib = FCML_TRUE;
	} else {
		if( !decoded_modrm->base.type && decoded_modrm->displacement.size ) {
			// disp32
			if( context->choose_rip_encoding && context->addr_form == FCML_AF_64_BIT ) {
				context->is_rip_encoding = FCML_TRUE;
				context->is_sib_alternative = FCML_FALSE;
			} else {
				choose_sib = context->choose_sib_encoding;
				context->is_sib_alternative = FCML_TRUE;
			}
		} else if ( decoded_modrm->base.type ) {
			// [esp],edx can be only encoded with using of SIB byte.
			if( decoded_modrm->base.reg == FCML_REG_ESP ) {
				choose_sib = FCML_TRUE;
			} else {
				// [base]+[disp8/disp32]
				choose_sib = context->choose_sib_encoding;
				context->is_sib_alternative = FCML_TRUE;
			}
		}
	}

	if( choose_sib ) {

		// SIB needed.

		fcml_uint8_t f_base = 0;
		fcml_uint8_t f_ss = 0;
		fcml_uint8_t f_index = 0;

		// Base register.
		if( decoded_modrm->base.type ) {
			if( context->effective_address_size != decoded_modrm->base.size ) {
				// Wrong size of base register, it has to be equal to EASA.
				return FCML_EN_UNSUPPORTED_ADDRESSING_MODE;
			}
			f_base = decoded_modrm->base.reg;
			if( f_base > 7 ) {
				f_ext_b = 0x01;
				f_base &= 0x07;
			}
		} else {
			// SIB without base register, there is only one addressing mode with this combination
			// and it needs disp32.
			if( !decoded_modrm->displacement.size ) {
				return FCML_EN_UNSUPPORTED_ADDRESSING_MODE;
			}
			disp_size = FCML_DS_32;
		}

		// Index register.
		if( decoded_modrm->index.type ) {
			// Check if index register size is correct.
			if( context->effective_address_size != decoded_modrm->index.size ) {
				// Wrong size of index register, it has to be equal to EASA.
				return FCML_EN_UNSUPPORTED_ADDRESSING_MODE;
			}
			// ESP is not allowed as index register.
			if( decoded_modrm->index.reg == FCML_REG_ESP ) {
				return FCML_EN_UNSUPPORTED_ADDRESSING_MODE;
			}
			f_index = decoded_modrm->index.reg;
			if( f_index > 7 ) {
				f_ext_x = 0x01;
				f_index &= 0x07;
			}
		} else {
			f_index = 0x04;
		}

		// Scale factor.
		switch( decoded_modrm->scale_factor ) {
		case 2:
			f_ss = 1;
			break;
		case 4:
			f_ss = 2;
			break;
		case 8:
			f_ss = 3;
			break;
		}

		// Encode SIB.
		encoded_modrm->sib.is_not_null = FCML_TRUE;
		encoded_modrm->sib.value = FCML_MODRM_SIB_ENC( f_ss, f_index, f_base );

		// RM when SIB is used.
		f_rm = 0x04;

	} else {

		// SIB not needed.

		if ( decoded_modrm->base.type ) {
			if( context->effective_address_size != decoded_modrm->base.size ) {
				return FCML_EN_UNSUPPORTED_ADDRESSING_MODE;
			}
			f_rm = decoded_modrm->base.reg;
		} else if ( decoded_modrm->reg.is_not_null ) {
			f_mod = 0x03;
			f_rm = decoded_modrm->reg.value;
			if( decoded_modrm->displacement.size ) {
				return FCML_EN_UNSUPPORTED_ADDRESSING_MODE;
			}
		} else if ( !decoded_modrm->displacement.size ) {
			return FCML_EN_UNSUPPORTED_ADDRESSING_MODE;
		} else if( decoded_modrm->displacement.size ) {
			disp_size = FCML_DS_32;
			f_rm = 0x05;
		}

		if( f_rm > 7 ) {
			f_ext_b = 0x01;
			f_rm &= 0x07;
		}
	}

	// Encode displacement.
	if( !disp_size && !decoded_modrm->reg.is_not_null ) {
		if( decoded_modrm->displacement.size == FCML_DS_8 ) {
			disp_size = FCML_DS_8;
			f_mod = 0x01;
		} else if ( decoded_modrm->displacement.size ) {
			disp_size = FCML_DS_32;
			f_mod = 0x02;
		} else {
			f_mod = 0x00;
		}
	}

	if( disp_size ) {
		fcml_ceh_error error = fcml_ifn_modrm_encode_displacement(  &(decoded_modrm->displacement), encoded_modrm, disp_size, context->is_rip_encoding );
		if( error ) {
			return error;
		}
	}

	// Encode reg/opcode.
	f_reg = decoded_modrm->reg_opcode;
	if( f_reg > 7 ) {
		f_ext_r = 0x01;
		f_reg &= 0x07;
	}

	if( context->addr_form != FCML_AF_64_BIT && ( f_ext_r || f_ext_x || f_ext_b ) ) {
		return FCML_EN_UNSUPPORTED_ADDRESSING_MODE;
	}

	encoded_modrm->modrm = FCML_MODRM_ENC( f_mod, f_reg, f_rm );
	encoded_modrm->ext_r = f_ext_r;
	encoded_modrm->ext_x = f_ext_x;
	encoded_modrm->ext_b = f_ext_b;

	return FCML_CEH_GEC_NO_ERROR;
}

fcml_ceh_error fcml_fn_modrm_encode( fcml_st_modrm_encoder_context *context, const fcml_st_modrm *decoded_modrm, fcml_st_encoded_modrm *encoded_modrm ) {
	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

	fcml_data_size easa = context->effective_address_size;
	fcml_en_addr_form addr_form = context->addr_form;

	// Check if there is ambiguity.
	if( decoded_modrm->base.size == FCML_DS_16 || decoded_modrm->index.size == FCML_DS_16 ) {
		if( addr_form == FCML_AF_64_BIT ) {
			// 16 bit addressing is not supported in 64 bit mode.
			return FCML_EN_UNSUPPORTED_ADDRESSING_MODE;
		}
		easa = FCML_DS_16;
	} else if( decoded_modrm->base.size == FCML_DS_64 || decoded_modrm->index.size == FCML_DS_64 ) {
		if( addr_form == FCML_AF_16_BIT ) {
			// 64 bit addressing is not supported in 16 bit mode.
			return FCML_EN_UNSUPPORTED_ADDRESSING_MODE;
		}
		easa = FCML_DS_64;
	}

	context->chosen_effective_address_size = easa;

	if( easa == FCML_DS_16 ) {
		error = fcml_fn_modrm_encode_16bit( context, decoded_modrm, encoded_modrm );
	} else if ( easa == FCML_DS_32 || easa == FCML_DS_64 ) {
		error = fcml_fn_modrm_encode_3264bit( context, decoded_modrm, encoded_modrm );
	} else {
		// Unknown addressing mode.
		error = FCML_EN_UNSUPPORTED_ADDRESSING_MODE;
	}
	return error;
}


