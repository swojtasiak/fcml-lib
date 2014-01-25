/*
 * fcml_modrm_encoder.c
 *
 *  Created on: 19-05-2013
 *      Author: tAs
 */

#include "fcml_modrm_encoder.h"

#include "fcml_common.h"
#include "fcml_errors.h"
#include "fcml_stream.h"
#include "fcml_types.h"
#include "fcml_utils.h"

fcml_st_memory_stream fcml_ifn_modrm_map_displacement_to_stream( fcml_st_encoded_modrm *encoded_modrm ) {
	fcml_st_memory_stream stream;
	stream.base_address = &(encoded_modrm->displacement);
	stream.offset = 0;
	stream.size = sizeof(encoded_modrm->displacement);
	return stream;
}

fcml_ceh_error fcml_ifn_modrm_is_displacement( const fcml_st_address *address ) {
    return address->offset.size || address->effective_address.displacement.size;
}

fcml_ceh_error fcml_ifn_modrm_convert_absolute_address_to_integer( const fcml_st_address *address, fcml_st_integer *integer ) {
    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
    if( address->address_form == FCML_AF_OFFSET ) {
        if( address->offset.size ) {
            error = fcml_fn_utils_offset_to_integer( &(address->offset ), integer );
        } else {
            error = fcml_fn_utils_displacement_to_integer( &(address->effective_address.displacement ), integer );
        }
    } else {
        /* Combined effective address can not be treated as absolute offset.*/
        return FCML_CEH_GEC_INVALID_INPUT;
    }
    return error;
}

/* Optionally extends and encodes displacement.*/
fcml_ceh_error fcml_ifn_modrm_encode_displacement( fcml_st_modrm_encoder_context *context, const fcml_st_integer *displacement, fcml_st_encoded_modrm *encoded_modrm, fcml_data_size asa, fcml_data_size *disp_size ) {

	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

    fcml_st_integer dest;

    /* Displacement value is always signed, so change it to signed value if it has expected size.*/
    fcml_st_integer src = *displacement;
    if( src.size == asa ) {
        src.is_signed = FCML_TRUE;
    }

	if( *disp_size == FCML_DS_UNDEF ) {

        /* Convert displacement to 8 bits value.*/
        error = fcml_fn_utils_convert_integer_to_integer( &src, &dest, asa, FCML_DS_8 );
        if( error == FCML_CEH_GEC_VALUE_OUT_OF_RANGE ) {
            /* Convert displacement to 32 bits value.*/
            error = fcml_fn_utils_convert_integer_to_integer( &src, &dest, asa, asa == FCML_DS_16 ? FCML_DS_16 : FCML_DS_32 );
        }

	} else {
	    error = fcml_fn_utils_convert_integer_to_integer( &src, &dest, asa, *disp_size );
	}

	if( error ) {
        return error;
    }

    /* Gets displacement as stream.*/
    fcml_st_memory_stream stream = fcml_ifn_modrm_map_displacement_to_stream( encoded_modrm );

    /* Extends and encodes displacement to given stream.*/
    error = fcml_fn_utils_encode_integer( &stream, &dest );
    if( error ) {
        return error;
    }

    *disp_size = dest.size;

    encoded_modrm->displacement_size = stream.offset;

	return error;
}

fcml_ceh_error fcml_ifn_modrm_encode_16bit( fcml_st_modrm_encoder_context *context, const fcml_st_modrm *decoded_modrm, fcml_st_encoded_modrm *encoded_modrm ) {

	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

	const fcml_st_address *address = &(decoded_modrm->address);
    const fcml_st_effective_address *effective_address = &(address->effective_address);

	/* ModR/M fields.*/
	fcml_uint8_t f_reg = 0;
	fcml_uint8_t f_mod = 0;
	fcml_uint8_t f_rm = 0;

	fcml_data_size disp_size = FCML_DS_UNDEF;

	if( context->addr_form == FCML_AF_64_BIT ) {
		return FCML_EN_UNSUPPORTED_ADDRESSING_MODE;
	}

	/* Check if there is disp16 addressing mode encoded.*/
	if( !effective_address->base.type && ( effective_address->displacement.size || address->offset.size ) ) {

		/* Sign extends displacement to 16 bits if there is such need, and encode it.*/
	    /* Remember that in 16 bit addressing mode address form doesn't matter.*/

	    fcml_st_integer absolute_address;

	    error = fcml_ifn_modrm_convert_absolute_address_to_integer( address, &absolute_address );
	    if( !error ) {
	        disp_size = FCML_DS_16;
	        error = fcml_ifn_modrm_encode_displacement( context, &absolute_address, encoded_modrm, FCML_DS_16, &disp_size );
	    }

		f_rm = 0x06;
	} else if ( effective_address->base.type ) {

	    /* Registers are allowed only in COMBINED addressing form.*/
	    if( address->address_form != FCML_AF_COMBINED ) {
	        return FCML_CEH_GEC_INVALID_INPUT;
	    }

		if( effective_address->base.type && effective_address->base.size != FCML_DS_16 ) {
			error = FCML_EN_UNSUPPORTED_ADDRESSING_MODE;
		}

		if( effective_address->index.type && effective_address->index.size != FCML_DS_16 ) {
			error = FCML_EN_UNSUPPORTED_ADDRESSING_MODE;
		}

		if( !error ) {

			/* There is base register set.*/
			switch( effective_address->base.reg ) {
			case FCML_REG_BX:
				if( effective_address->index.type ) {
					if( effective_address->index.reg == FCML_REG_DI ) {
						f_rm = 0x01;
					}
				} else {
					f_rm = 0x07;
				}
				break;
			case FCML_REG_BP:
				if( effective_address->index.type ) {
					switch( effective_address->index.reg ) {
					case FCML_REG_SI:
						f_rm = 0x02;
						break;
					case FCML_REG_DI:
						f_rm = 0x03;
						break;
					}
				} else if( !effective_address->displacement.size ) {
					/* BP is not allowed without displacement.*/
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

			    /* Encode displacement if there is any.*/
			    if( effective_address->displacement.size ) {
                    fcml_st_integer displacement;
                    error = fcml_fn_utils_displacement_to_integer( &(effective_address->displacement), &displacement );
                    if( !error ) {
                        error = fcml_ifn_modrm_encode_displacement( context, &displacement, encoded_modrm, FCML_DS_16, &disp_size );
                    }
			    }

			    if( !error ) {
                    /* Now encode displacement, is there is any.*/
                    switch( disp_size ) {
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
                        /* Only disp8 and disp16 is supported in 16 bit addressing mode.*/
                        error = FCML_EN_UNSUPPORTED_ADDRESSING_MODE;
                        break;
                    }
			    }

			}

		}

	} else if ( decoded_modrm->reg.is_not_null ) {
		f_mod = 0x03;
		f_rm = decoded_modrm->reg.value;
	} else {
		/* There is no base register and displacement, so*/
		error = FCML_EN_UNSUPPORTED_ADDRESSING_MODE;
	}

	if( !error ) {
		/* Encode reg/opcode.*/
		f_reg = decoded_modrm->reg_opcode;
		/* Encode calculated ModR/M byte.*/
		encoded_modrm->modrm = FCML_MODRM_ENC( f_mod, f_reg, f_rm );
	}

	return error;
}

/* 32 and 64 bit addressing mode.s*/
fcml_ceh_error fcml_ifn_modrm_encode_3264bit( fcml_st_modrm_encoder_context *context, const fcml_st_modrm *decoded_modrm, fcml_st_encoded_modrm *encoded_modrm ) {

	fcml_uint8_t f_mod = 0;
	fcml_uint8_t f_rm = 0;
	fcml_uint8_t f_reg = 0;

	fcml_uint8_t f_ext_r = 0;
	fcml_uint8_t f_ext_x = 0;
	fcml_uint8_t f_ext_b = 0;

	fcml_data_size disp_size = 0;

	fcml_bool choose_sib = FCML_FALSE;

    const fcml_st_address *address = &(decoded_modrm->address);
    const fcml_st_effective_address *effective_address = &(address->effective_address);

	/* Check if addressing mode and effective address size are compatible.*/
	if( ( context->chosen_effective_address_size == FCML_DS_64 && context->addr_form != FCML_AF_64_BIT ) || ( context->addr_form == FCML_AF_64_BIT && context->chosen_effective_address_size == FCML_DS_16 ) ) {
		return FCML_EN_UNSUPPORTED_ADDRESSING_MODE;
	}

	fcml_bool is_displacement = fcml_ifn_modrm_is_displacement( address );
	fcml_bool is_base = effective_address->base.type;
	fcml_bool is_index = effective_address->index.type;

	/* Should be treated like standard displacement when RIP addressing is not available.*/
	fcml_bool is_rip_disp = effective_address->base.type == FCML_REG_IP;

	/* Sanity check.*/
	if( ( is_base || is_index ) && address->address_form != FCML_AF_COMBINED )  {
	    return FCML_EN_UNSUPPORTED_ADDRESSING_MODE;
	}

	fcml_bool is_rip = FCML_FALSE;

	/* Check if there is SIB alternative.*/
	if( !is_rip_disp ) {

		if( is_index ) {
			choose_sib = FCML_TRUE;
		} else {
			if( !is_base && is_displacement ) {

				/* disp32 or RIP*/

				fcml_bool choose_rip = context->choose_rip_encoding && context->addr_form == FCML_AF_64_BIT;

				if( address->address_form != FCML_AF_OFFSET ) {
					choose_rip = FCML_FALSE;
				}

				if( address->address_form == FCML_AF_OFFSET && !context->addr_form == FCML_AF_64_BIT ) {
					/* User chooses address displacement, but RIP addressing can not be used.*/
					return FCML_EN_UNSUPPORTED_ADDRESSING_MODE;
				}

				if( choose_rip ) {
					/* Relative.*/
					is_rip = FCML_TRUE;
					context->is_sib_alternative = FCML_FALSE;
				} else {
					/* In case of 64 bit addressing SIB is needed to encode absolute address.*/
					choose_sib = ( context->addr_form == FCML_AF_64_BIT ) ? FCML_TRUE : context->choose_sib_encoding;
					context->is_sib_alternative = FCML_TRUE;
				}

			} else if ( is_base ) {
				/* [esp],edx can be only encoded with using of SIB byte.*/
				if( effective_address->base.reg == FCML_REG_ESP ) {
					choose_sib = FCML_TRUE;
				} else {
					/* RIP relative addressing can not be encoded using SIB.*/
					if( effective_address->base.type != FCML_REG_IP ) {
						/* [base]+[disp8/disp32]*/
						choose_sib = context->choose_sib_encoding;
						context->is_sib_alternative = FCML_TRUE;
					}
				}
			}
		}
	}

	if( choose_sib ) {

		/* SIB needed.*/

		fcml_uint8_t f_base = 0;
		fcml_uint8_t f_ss = 0;
		fcml_uint8_t f_index = 0;

		/* Base register.*/
		if( is_base ) {
			if( context->chosen_effective_address_size != effective_address->base.size ) {
				/* Wrong size of base register, it has to be equal to EASA.*/
				return FCML_EN_UNSUPPORTED_ADDRESSING_MODE;
			}
			f_base = effective_address->base.reg;
			if( f_base > 7 ) {
				f_ext_b = 0x01;
				f_base &= 0x07;
			}
		} else {
			/* SIB without base register, there is only one addressing mode with this combination*/
			/* and it needs disp32.*/
			if( !is_displacement ) {
				return FCML_EN_UNSUPPORTED_ADDRESSING_MODE;
			}
			disp_size = FCML_DS_32;
			f_base = 0x05;
		}

		/* Index register.*/
		if( is_index ) {
			/* Check if index register size is correct.*/
			if( effective_address->index.type != FCML_REG_SIMD && context->chosen_effective_address_size != effective_address->index.size ) {
				/* Wrong size of index register, it has to be equal to EASA.*/
				return FCML_EN_UNSUPPORTED_ADDRESSING_MODE;
			}
			/* ESP is not allowed as index register.*/
			if( effective_address->index.reg == FCML_REG_ESP ) {
				return FCML_EN_UNSUPPORTED_ADDRESSING_MODE;
			}
			f_index = effective_address->index.reg;
			if( f_index > 7 ) {
				f_ext_x = 0x01;
				f_index &= 0x07;
			}
		} else {
			f_index = 0x04;
		}

		/* Scale factor.*/
		switch( effective_address->scale_factor ) {
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

		/* Encode SIB.*/
		encoded_modrm->sib.is_not_null = FCML_TRUE;
		encoded_modrm->sib.value = FCML_MODRM_SIB_ENC( f_ss, f_index, f_base );

		/* RM when SIB is used.*/
		f_rm = 0x04;

	} else {

		/* SIB not needed.*/

		if ( is_base && !is_rip_disp ) {
			if( context->chosen_effective_address_size != effective_address->base.size ) {
				return FCML_EN_UNSUPPORTED_ADDRESSING_MODE;
			}
			f_rm = effective_address->base.reg;
		} else if ( decoded_modrm->reg.is_not_null ) {
			f_mod = 0x03;
			f_rm = decoded_modrm->reg.value;
			if( effective_address->displacement.size ) {
				return FCML_EN_UNSUPPORTED_ADDRESSING_MODE;
			}
		} else if ( is_displacement ) {
		    /* Absolute address or RIP.*/
			disp_size = FCML_DS_32;
			f_rm = 0x05;
		} else {
		    /* Only reg_opcode is encoded.*/
		    f_mod = 0x03;
		}

		if( f_rm > 7 ) {
			f_ext_b = 0x01;
			f_rm &= 0x07;
		}
	}

	if( is_rip ) {

	    /* RIP given ad absolute address that has to be converted to relative displacement.*/

	    fcml_st_integer rip_address;

	    /* Offset is not available, so displacement was used instead.*/
	    if( !address->offset.size ) {
	        return FCML_EN_UNSUPPORTED_ADDRESSING_MODE;
	    }

	    fcml_ceh_error error = fcml_fn_utils_offset_to_integer( &(address->offset), &rip_address );
	    if( error ) {
	        return error;
	    }

	    /* Extends RIP address to 64 bit value.*/
	    if( rip_address.size != FCML_DS_64 ) {
            error = fcml_fn_utils_extend_integer( &rip_address, FCML_DS_64 );
            if( error ) {
                return error;
            }
	    }

        /* Store RIP offset. It can be used then to calculate displacement*/
        encoded_modrm->is_rip = FCML_TRUE;
        encoded_modrm->rip_address = rip_address.int64;

        /* Check if 32 bit ASA should be used, if so check if RIP address is not out of range.*/
        fcml_data_size asa = ( context->chosen_effective_address_size ) ? context->chosen_effective_address_size : context->effective_address_size;
        if( asa == FCML_DS_32 ) {
            if( rip_address.is_signed ) {
                if( rip_address.int64 > FCML_INT32_MAX || rip_address.int64 < FCML_INT32_MIN ) {
                    return FCML_CEH_GEC_VALUE_OUT_OF_RANGE;
                }
            } else {
                if( (fcml_uint64_t)rip_address.int64 > FCML_UINT32_MAX ) {
                    return FCML_CEH_GEC_VALUE_OUT_OF_RANGE;
                }
            }
        }

        f_mod = 0x00;

	} else if ( is_displacement || is_rip_disp ) {

		if( is_base || is_index ) {

            /* Complex effective address.*/
            fcml_st_integer displacement;

            /* Convert absolute address to generic integer value in order to convert it to ASA size.*/
            fcml_data_size error = fcml_fn_utils_displacement_to_integer( &(effective_address->displacement), &displacement );
            if( error ) {
                return error;
            }

            error = fcml_ifn_modrm_encode_displacement( context, &displacement, encoded_modrm, context->chosen_effective_address_size, &disp_size );
            if( error ) {
                return error;
            }

            /* Encode displacement.*/
            if( disp_size == FCML_DS_8 ) {
                f_mod = 0x01;
            } else if ( disp_size == FCML_DS_32 && is_base && !is_rip_disp ) {
                f_mod = 0x02;
            } else {
                f_mod = 0x00;
            }

            /* Displacement has been already encoded, so postprocessing is not needed anymore.*/
            if( is_rip_disp ) {
            	encoded_modrm->is_rip = FCML_TRUE;
            	encoded_modrm->is_rip_encoded = FCML_TRUE;
            	encoded_modrm->rip_address = 0LL;
            }

	    } else {

	        /* Absolute address or RIP relative displacement.*/
            fcml_st_integer absolute_address;

            /* Convert absolute address to generic integer value in order to convert it to ASA size.*/
            fcml_data_size error = fcml_ifn_modrm_convert_absolute_address_to_integer( address, &absolute_address );
            if( error ) {
                return error;
            }

            error = fcml_ifn_modrm_encode_displacement( context, &absolute_address, encoded_modrm, context->chosen_effective_address_size, &disp_size );
            if( error ) {
                return error;
            }

            f_mod = 0x00;
	    }

	}

	/* Encode reg/opcode.*/
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

	const fcml_st_effective_address *effective_address = &(decoded_modrm->address.effective_address);

	/* Check if there is ambiguity.*/
	if( effective_address->base.size == FCML_DS_16 || effective_address->index.size == FCML_DS_16 ) {
		if( addr_form == FCML_AF_64_BIT ) {
			/* 16 bit addressing is not supported in 64 bit mode.*/
			return FCML_EN_UNSUPPORTED_ADDRESSING_MODE;
		}
		easa = FCML_DS_16;
	} else if( effective_address->base.size == FCML_DS_64 || effective_address->index.size == FCML_DS_64 ) {
		if( addr_form == FCML_AF_16_BIT ) {
			/* 64 bit addressing is not supported in 16 bit mode.*/
			return FCML_EN_UNSUPPORTED_ADDRESSING_MODE;
		}
		easa = FCML_DS_64;
	}

	context->chosen_effective_address_size = easa;

	if( easa == FCML_DS_16 ) {
		error = fcml_ifn_modrm_encode_16bit( context, decoded_modrm, encoded_modrm );
	} else if ( easa == FCML_DS_32 || easa == FCML_DS_64 ) {
		error = fcml_ifn_modrm_encode_3264bit( context, decoded_modrm, encoded_modrm );
	} else {
		/* Unknown addressing mode.*/
		error = FCML_EN_UNSUPPORTED_ADDRESSING_MODE;
	}
	return error;
}

fcml_ceh_error fcml_fn_modrm_encode_rip_offset( fcml_st_memory_stream *stream, fcml_uint64_t rip, fcml_uint8_t instruction_size, const fcml_st_encoded_modrm *encoded_modrm ) {

	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

	if( encoded_modrm->is_rip ) {
		fcml_int64_t rip_offset = ( encoded_modrm->rip_address - instruction_size ) - (fcml_int64_t)rip;

		if( rip_offset < FCML_INT32_MIN || rip_offset > FCML_INT32_MAX ) {
			error = FCML_CEH_GEC_VALUE_OUT_OF_RANGE;
		} else {

			fcml_st_integer integer;
			integer.int32 = (fcml_int32_t)rip_offset;
			integer.size = FCML_DS_32;

			/* Encodes and encodes displacement to given stream.*/
			error = fcml_fn_utils_encode_integer( stream, &integer );

		}
	} else {
		error = FCML_CEH_GEC_INVALID_INPUT;
	}

	return error;
}

fcml_ceh_error fcml_fn_modrm_calculate_effective_address_size( const fcml_st_modrm *decoded_modrm, fcml_en_attribute_size_flag *effective_address_size ) {

	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

	/* Calculate EOSA.*/

	const fcml_st_address *address = &(decoded_modrm->address);
    const fcml_st_effective_address *effective_address = &(address->effective_address);

    fcml_en_attribute_size_flag easa;

	fcml_st_register reg;
	if( effective_address->base.type ) {
		reg = effective_address->base;
	} else {
		reg = effective_address->index;
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
			easa = FCML_EN_ASF_32 | FCML_EN_ASF_64;
			break;
		default:
			error = FCML_EN_UNSUPPORTED_ADDRESSING_MODE;
			break;
		}
	} else  {
	    /* Remember that -1 can be represented as int64 value, so displacement nor offset size cannot be taken into account here.*/
	    easa = FCML_EN_ASF_ALL;
	}

	if( error ) {
		return error;
	}

	/* Calculate EASA.*/

	*effective_address_size = easa;

	return error;
}


