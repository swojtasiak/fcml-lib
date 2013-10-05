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
#include "fcml_trace.h"

typedef struct fcml_ist_asm_enc_assembler {
    fcml_coll_map instructions_map;
    fcml_st_dialect_context dialect_context;
} fcml_ist_asm_enc_assembler;

typedef struct fcml_ist_asm_init_context {
    fcml_ist_asm_enc_assembler *assembler;
} fcml_ist_asm_init_context;

#ifdef FCML_DEBUG

// ************************
// DEBUG related functions.
// ************************

fcml_char __data_attr_flags_buff[64];

fcml_string fcml_idfn_print_attr_size_flags( fcml_en_attribute_size_flag flags ) {
	int index = 0;
	if( flags == FCML_EN_ASF_ANY ) {
		sprintf( __data_attr_flags_buff, "ANY" );
	} else {
		if( flags & FCML_EN_ASF_16 ) {
			index += sprintf( __data_attr_flags_buff, "2" );
		}
		if( flags & FCML_EN_ASF_32 ) {
			index += sprintf( __data_attr_flags_buff + index, "4" );
		}
		if( flags & FCML_EN_ASF_64 ) {
			index += sprintf( __data_attr_flags_buff + index, "8" );
		}
	}
	return __data_attr_flags_buff;
}

fcml_char __data_flags_buff[512];

fcml_string fcml_idfn_encode_size_flags( fcml_st_asm_data_size_flags *size_flags ) {

	int index = 0;

	// L flag.
	if( size_flags->l.is_not_null ) {
		index += sprintf( __data_flags_buff, "L: %d, ", size_flags->l.value );
	} else {
		index += sprintf( __data_flags_buff, "L: NS, " );
	}

	// Allowed EOSA.
	if( size_flags->allowed_effective_operand_size.is_set ) {
		index += sprintf( __data_flags_buff + index, "Allowed OSA: [%s], ", fcml_idfn_print_attr_size_flags( size_flags->allowed_effective_operand_size.flags ) );
	} else {
		index += sprintf( __data_flags_buff + index, "Allowed OSA: NS, " );
	}

	// Allowed EASA.
	if( size_flags->allowed_effective_address_size.is_set ) {
		index += sprintf( __data_flags_buff + index, "Allowed ASA: [%s], ", fcml_idfn_print_attr_size_flags( size_flags->allowed_effective_address_size.flags ) );
	} else {
		index += sprintf( __data_flags_buff + index, "Allowed ASA: NS, " );
	}

	// Chosen OSA.
	index += sprintf( __data_flags_buff + index, "EOSA: %d, ", size_flags->effective_operand_size );

	// Chosen OSA.
	index += sprintf( __data_flags_buff + index, "EASA: %d", size_flags->effective_address_size );

	return __data_flags_buff;
}

// ************************
// End of debug functions
// ************************

#endif

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
	data_size_flags->allowed_effective_address_size.flags = 0;
	data_size_flags->allowed_effective_address_size.is_set = FCML_FALSE;
	data_size_flags->allowed_effective_operand_size.flags = 0;
	data_size_flags->allowed_effective_operand_size.is_set = FCML_FALSE;
}

fcml_st_memory_stream fcml_ifn_instruction_part_stream( fcml_st_asm_instruction_part *instruction_part ) {
	fcml_st_memory_stream stream;
	stream.base_address = &(instruction_part->code);
	stream.offset = 0;
	stream.size = sizeof(instruction_part->code);
	return stream;
}

// TODO: Je¿eli nie ebdzie uzywana wywaliæ.
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
			FCML_TRACE( "Unsupported encoded EOSA size." );
			error = FCML_EN_UNSUPPORTED_OPPERAND_SIZE;
		}
		break;
	case FCML_EOS_EOSA:
		if( data_size == FCML_DS_16 || data_size == FCML_DS_32 || data_size == FCML_DS_64 ) {
			effective_operand_size = data_size;
		} else {
			FCML_TRACE( "Unsupported encoded EASA size." );
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
				FCML_TRACE( "Addressing mode not available for 16 bit EOSA." );
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
				FCML_TRACE( "Addressing mode not available for 16 bit EOSA." );
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
				FCML_TRACE( "Addressing mode not available for 16 bit EOSA." );
				error = FCML_EN_UNSUPPORTED_OPPERAND_SIZE;
			} else {
				effective_operand_size = context->assembler_context->effective_operand_size;
			}
			break;
		default:
			break;
		}
		break;
    case FCML_EOS_FPI:
        // Far pointer indirect.
        effective_operand_size = data_size - FCML_DS_16;
        break;
	default:
		if( comparator == FCML_IEN_CT_EQUAL ) {
			if ( encoded_operand_size * 8 != data_size ) {
				FCML_TRACE( "Unsupported operand size. Expected %d got %d.", data_size, encoded_operand_size * 8 );
				error = FCML_EN_UNSUPPORTED_OPPERAND_SIZE;
			}
		} else {
			if ( encoded_operand_size * 8 < data_size ) {
				FCML_TRACE( "Unsupported operand size. Expected greater or equal to %d got %d.", data_size, encoded_operand_size * 8 );
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
				FCML_TRACE( "L flag differs expected %d got %d.", flags->l.value, l.value );
				error = FCML_EN_UNSUPPORTED_OPPERAND_SIZE;
			} else {
				flags->l = l;
			}
		}
		if( effective_address_size ) {
			if( flags->effective_address_size && effective_address_size != flags->effective_address_size ) {
				FCML_TRACE( "Wrong encoded EASA size. Expected %d got %d.", flags->effective_address_size, effective_address_size );
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
				FCML_TRACE( "Wrong encoded EOSA size. Expected %d got %d.", flags->effective_operand_size, effective_operand_size );
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

fcml_ceh_error fcml_ifn_asm_choose_optimal_osa( fcml_st_asm_encoding_context *context, fcml_data_size *osa ) {
    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
    if( !context->data_size_flags.allowed_effective_operand_size.is_set ) {
        // On order to choose optimal OSA, flags should be set.
        return FCML_CEH_GEC_ILLEGAL_STATE_EXCEPTION;
    }
    fcml_en_attribute_size_flag flags = context->data_size_flags.allowed_effective_operand_size.flags;
    switch( context->assembler_context->addr_form ) {
    case FCML_AF_16_BIT:
        if( flags & FCML_EN_ASF_16 ) {
            *osa = FCML_DS_16;
        } else if( flags & FCML_EN_ASF_32 ) {
            *osa = FCML_DS_32;
        } else {
            // Only 16 and 32 bit OSA is available in 16 bit addressing mode.
            error = FCML_CEH_GEC_ILLEGAL_STATE_EXCEPTION;
        }
        break;
    case FCML_AF_32_BIT:
        if( flags & FCML_EN_ASF_32 ) {
            *osa = FCML_DS_32;
        } else if( flags & FCML_EN_ASF_16 ) {
            *osa = FCML_DS_16;
        } else {
            // Only 16 and 32 bit OSA is available in 16 bit addressing mode.
            error = FCML_CEH_GEC_ILLEGAL_STATE_EXCEPTION;
        }
        break;
    case FCML_AF_64_BIT:
        if( flags & FCML_EN_ASF_32 ) {
            *osa = FCML_DS_32;
        } else if ( flags & FCML_EN_ASF_64 ) {
            *osa = FCML_DS_64;
        } else if ( flags & FCML_EN_ASF_16 ) {
            *osa = FCML_DS_16;
        } else {
            // Flags aren't set.
            error = FCML_CEH_GEC_ILLEGAL_STATE_EXCEPTION;
        }
        break;
    }
    return error;
}

fcml_bool fcml_ifn_set_size_flag( fcml_st_asm_nullable_size_flags *nullable_flags, fcml_en_attribute_size_flag flags ) {
	if( nullable_flags->is_set ) {
		if( ( nullable_flags->flags & flags ) == 0 ) {
			// We need flags that weren't allowed by previous operands or IPPs.
			return FCML_FALSE;
		}
		// Set new set of flags, take into account that these might be a subset of existing ones.
		nullable_flags->flags = flags;
	} else {
		nullable_flags->flags = flags;
		nullable_flags->is_set = FCML_TRUE;
	}
	return FCML_TRUE;
}

fcml_bool fcml_ifn_accept_segment_register( fcml_st_asm_encoding_context *context, fcml_st_register *segment_register, fcml_uint8_t encoded_segment_register ) {
    fcml_uint8_t reg_num = encoded_segment_register & 0x7F;
    fcml_bool allow_override = encoded_segment_register & FCML_SEG_ALLOW_OVERRIDE;

    // No mater what segment register we have expected, default one has been used.
    if( segment_register->type == FCML_REG_UNDEFINED ) {
        return FCML_TRUE;
    } else if( segment_register->type != FCML_REG_SEG ) {
        // Wrong register type, segment register should be used.
        return FCML_FALSE;
    }

    if( segment_register->reg == reg_num ) {
        // Register are the same, everything going well.
        return FCML_TRUE;
    } else if ( allow_override ) {
        // TODO: dodac komuniat bledu, tak aby yuzytkownik mial swiadomosc tego co jest nie tak.
        context->segment_override = *segment_register;
        return FCML_TRUE;
    }

    return FCML_FALSE;
}

fcml_bool fcml_ifn_accept_data_size( fcml_st_asm_encoding_context *context, fcml_st_def_addr_mode_desc *addr_mode_desc, fcml_uint8_t encoded_register_operand_size, fcml_data_size operand_size, enum fcml_ien_comparator_type comparator ) {
	fcml_st_asm_data_size_flags *data_size_flags = &(context->data_size_flags);
	fcml_en_attribute_size_flag osa_flags = FCML_EN_ASF_ANY;
	fcml_en_attribute_size_flag asa_flags = FCML_EN_ASF_ANY;
	fcml_bool result = FCML_TRUE;
	switch( encoded_register_operand_size ) {
	case FCML_EOS_UNDEFINED:
		break;
	case FCML_EOS_L:
		if( FCML_DEF_PREFIX_L_IGNORE_OS( addr_mode_desc->allowed_prefixes ) ) {
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
		if( result ) {
			asa_flags = operand_size / FCML_ASM_FCF;
		}
		break;
	case FCML_EOS_EOSA:
		if( context->assembler_context->addr_form == FCML_AF_32_BIT ) {
			result = ( ( operand_size == FCML_DS_16 ) || ( operand_size == FCML_DS_32 ) );
		} else {
			result = ( ( operand_size == FCML_DS_16 ) || ( operand_size == FCML_DS_32 ) || ( operand_size == FCML_DS_64 ) );
		}
		if( result ) {
			osa_flags = operand_size / FCML_ASM_FCF;
		}
		break;
	case FCML_EOS_14_28:
		if( operand_size == 14 * 8 ) {
			osa_flags |= FCML_EN_ASF_16;
		} else if( operand_size == 28 * 8 ) {
			osa_flags |= ( FCML_EN_ASF_32 | FCML_EN_ASF_64 );
		} else {
			result = FCML_FALSE;
		}
		break;
	case FCML_EOS_32_64:
		if( ( operand_size == FCML_DS_16 * 2 ) || ( FCML_DS_32 * 2 ) || ( FCML_DS_64 * 2 ) ) {
			osa_flags = ( operand_size / 2 / FCML_ASM_FCF );
		} else {
			result = FCML_FALSE;
		}
		break;
	case FCML_EOS_94_108:
		if( operand_size == 94 * 8 ) {
			osa_flags |= FCML_EN_ASF_16;
		} else if( operand_size == 108 * 8 ) {
			osa_flags |= ( FCML_EN_ASF_32 | FCML_EN_ASF_64 );
		} else {
			result = FCML_FALSE;
		}
		break;
	case FCML_EOS_FPI:
	    // Far pointer indirect.
	    switch( operand_size ) {
	    case FCML_DS_16 + FCML_DS_16:
            osa_flags |= FCML_EN_ASF_16;
            break;
	    case FCML_DS_32 + FCML_DS_16:
	        osa_flags |= FCML_EN_ASF_32;
	        break;
	    case FCML_DS_64 + FCML_DS_16:
            osa_flags |= FCML_EN_ASF_64;
            break;
	    default:
	        result = FCML_FALSE;
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

	if( osa_flags && !fcml_ifn_set_size_flag( &(data_size_flags->allowed_effective_operand_size), osa_flags ) ) {
		result = FCML_FALSE;
	}

	if( asa_flags && !fcml_ifn_set_size_flag( &(data_size_flags->allowed_effective_address_size), asa_flags ) ) {
		result = FCML_FALSE;
	}

	return result;
}

/*********************************
 * Operand encoders.
 *********************************/

// TODO: zastnawic sie nad nazwa, ta jest beznadziejna,.
fcml_bool fcml_ifn_asm_convert_signed_integer( const fcml_st_integer *source, fcml_st_integer *destination, fcml_data_size expected_size, fcml_data_size size, fcml_en_attribute_size_flag flag, fcml_en_attribute_size_flag *flags ) {

    // We expect signed integers here, but of course user is not forced to provide values that match expected size. In such cases values are converted to
    // appropriate size using sign set by user. Anyway sometimes user is not able to guess if values are signed or not in given context.
    // Parsers might be a good example. To avoid sign problem, if source operand has expected size (so conversion to the expected size is not necessary),
    // we can treat it like signed value.

    // TODO: Zastanowic sie nad tym rozwiazaniem, troche mi nie pasuje ustwianie tego znaku w tym miejscu. zakladamy za kazdy konwerowany imm
    // jest wartoscia ze znakiem, a to tez raczej ni jest prawd¹, moze powinnimy w argumentach tryubu adresowania zaznaczac czy oczekujemy wartosci
    // ze znakiem? Chyba tak bylo by najsensowiej.
    fcml_st_integer tmp = *source;
    if( tmp.size == expected_size ) {
        tmp.is_signed = FCML_TRUE;
    }

	fcml_ceh_error error = fcml_fn_utils_convert_integer_to_integer( &tmp, destination, expected_size, size );
	if( !error && flags ) {
		*flags |= flag;
	}

	return !error;
}

fcml_ceh_error fcml_fnp_asm_operand_acceptor_imm( fcml_st_asm_encoding_context *context, fcml_st_asm_addr_mode_desc_details *addr_mode_details, fcml_st_def_addr_mode_desc *addr_mode_desc, fcml_st_def_decoded_addr_mode *addr_mode, fcml_st_operand *operand_def, fcml_st_asm_instruction_part *operand_enc ) {
	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
	if( operand_def->type == FCML_EOT_IMMEDIATE ) {

		fcml_st_integer destination = {0};

		fcml_en_attribute_size_flag flags = 0;

		fcml_sf_def_tma_imm *args = (fcml_sf_def_tma_imm*)addr_mode->addr_mode_args;
		fcml_uint8_t imm_size = args->encoded_imm_size;
		fcml_uint8_t imm_size_ex = args->encoded_ex_imm_size;
		fcml_st_immediate *immediate = &(operand_def->immediate);
		fcml_en_addr_form addr_form = context->assembler_context->addr_form;
		fcml_bool is_convertable = FCML_FALSE;

		fcml_en_attribute_size_flag osa_flags = context->data_size_flags.allowed_effective_operand_size.flags;
		if( !osa_flags ) {
			osa_flags = FCML_EN_ASF_ALL;
		}

		if( imm_size_ex == 0 ) {
			imm_size_ex = imm_size;
		}

		fcml_st_integer source;
		error = fcml_fn_utils_imm_to_integer( immediate, &source );
		if( !error ) {

            // Not all EOSA values are available for every addressing mode. Additional flags can enable or disable some of them.

            if( imm_size != FCML_EOS_EOSA && imm_size_ex != FCML_EOS_EOSA ) {
                is_convertable |= fcml_ifn_asm_convert_signed_integer( &source, &destination, imm_size_ex * 8, imm_size * 8, 0, NULL );
            } else if( imm_size == FCML_EOS_EOSA && imm_size_ex == FCML_EOS_EOSA ) {
                // Destination size calculated by EOSA.
                if( osa_flags & FCML_EN_ASF_16 )
                    is_convertable |= fcml_ifn_asm_convert_signed_integer( &source, &destination, FCML_DS_16, FCML_DS_16, FCML_EN_ASF_16, &flags );
                if( osa_flags & FCML_EN_ASF_32 )
                    is_convertable |= fcml_ifn_asm_convert_signed_integer( &source, &destination, FCML_DS_32, FCML_DS_32, FCML_EN_ASF_32, &flags );
                if( ( osa_flags & FCML_EN_ASF_64 ) && addr_form == FCML_AF_64_BIT ) {
                    is_convertable |= fcml_ifn_asm_convert_signed_integer( &source, &destination, FCML_DS_64, FCML_DS_64, FCML_EN_ASF_64, &flags );
                }
            } else if( imm_size == FCML_EOS_EOSA ) {
                if( osa_flags & FCML_EN_ASF_16 )
                    is_convertable |= fcml_ifn_asm_convert_signed_integer( &source, &destination, imm_size_ex * 8, FCML_DS_16, FCML_EN_ASF_16, &flags );
                if( osa_flags & FCML_EN_ASF_32 )
                    is_convertable |= fcml_ifn_asm_convert_signed_integer( &source, &destination, imm_size_ex * 8, FCML_DS_32, FCML_EN_ASF_32, &flags );
                if( ( osa_flags & FCML_EN_ASF_64 ) && addr_form == FCML_AF_64_BIT ) {
                    is_convertable |= fcml_ifn_asm_convert_signed_integer( &source, &destination, imm_size_ex * 8, FCML_DS_64, FCML_EN_ASF_64, &flags );
                }
            } else {
                // IMM extended to effective address size attribute.
                if( osa_flags & FCML_EN_ASF_16 )
                    is_convertable |= fcml_ifn_asm_convert_signed_integer( &source, &destination, FCML_DS_16, imm_size * 8, FCML_EN_ASF_16, &flags );
                if( osa_flags & FCML_EN_ASF_32 )
                    is_convertable |= fcml_ifn_asm_convert_signed_integer( &source, &destination, FCML_DS_32, imm_size * 8, FCML_EN_ASF_32, &flags );
                if( ( osa_flags & FCML_EN_ASF_64 ) && addr_form == FCML_AF_64_BIT ) {
                    is_convertable |= fcml_ifn_asm_convert_signed_integer( &source, &destination, FCML_DS_64, imm_size * 8, FCML_EN_ASF_64, &flags );
                }
            }

            if( !is_convertable || ( flags && !fcml_ifn_set_size_flag( &(context->data_size_flags.allowed_effective_operand_size ), flags ) ) ) {
                FCML_TRACE("Accept IMM: Can not accept IMM value." );
                error = FCML_EN_UNSUPPORTED_OPPERAND;
            }

		}

		return error;
	} else {
		error = FCML_EN_UNSUPPORTED_OPPERAND;
	}
	return error;
}

fcml_ceh_error fcml_fnp_asm_operand_encoder_imm( fcml_ien_asm_part_processor_phase phase, fcml_st_asm_encoding_context *context, fcml_st_def_addr_mode_desc *addr_mode_desc, fcml_st_def_decoded_addr_mode *addr_mode, fcml_st_operand *operand_def, fcml_st_asm_instruction_part *operand_enc ) {

	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
	fcml_sf_def_tma_imm *args = (fcml_sf_def_tma_imm*)addr_mode->addr_mode_args;

	if( phase == FCML_IEN_ASM_IPPP_FIRST_PHASE ) {

		fcml_uint8_t imm_size = args->encoded_imm_size;
		fcml_uint8_t imm_size_ex = args->encoded_ex_imm_size;

		if( imm_size_ex == 0 ) {
			imm_size_ex = imm_size;
		}

		fcml_st_immediate *source_imm = &(operand_def->immediate);
		fcml_st_integer source;
		fcml_st_integer converted_source;

		error = fcml_fn_utils_imm_to_integer( source_imm, &source );
		if( error ) {
		    return error;
		}

		fcml_data_size eosa_size = context->data_size_flags.effective_operand_size;

		if( ( imm_size == FCML_EOS_EOSA || imm_size_ex == FCML_EOS_EOSA ) && !eosa_size ) {
			FCML_TRACE("EOSA size not set! Processing failed.");
			return FCML_CEH_GEC_ILLEGAL_STATE_EXCEPTION;
		}

		fcml_bool is_converted = FCML_FALSE;

		if( imm_size != FCML_EOS_EOSA && imm_size_ex != FCML_EOS_EOSA ) {
		    is_converted = fcml_ifn_asm_convert_signed_integer( &source, &converted_source, imm_size_ex * 8, imm_size * 8, 0, NULL );
		} else if( imm_size == FCML_EOS_EOSA && imm_size_ex == FCML_EOS_EOSA ) {
		    is_converted = fcml_ifn_asm_convert_signed_integer( &source, &converted_source, eosa_size, eosa_size, 0, NULL );
		} else if( imm_size == FCML_EOS_EOSA ) {
		    is_converted = fcml_ifn_asm_convert_signed_integer( &source, &converted_source, imm_size_ex * 8, eosa_size, 0, NULL );
		} else {
		    is_converted = fcml_ifn_asm_convert_signed_integer( &source, &converted_source, eosa_size, imm_size * 8, 0, NULL );
		}

		if( !is_converted ) {
		    error = FCML_CEH_GEC_VALUE_OUT_OF_RANGE;
		}

		if( !error ) {
            fcml_st_memory_stream stream = { &(operand_enc->code), 0, sizeof( operand_enc->code ) };
            error = fcml_fn_utils_encode_integer( &stream, &converted_source );
            if( !error ) {
                operand_enc->code_length = stream.offset;
            }
		}
	}
	return error;
}

//-------------------
// Explicit register
//-------------------

fcml_ceh_error fcml_fnp_asm_operand_acceptor_explicit_reg( fcml_st_asm_encoding_context *context, fcml_st_asm_addr_mode_desc_details *addr_mode_details, fcml_st_def_addr_mode_desc *addr_mode_desc, fcml_st_def_decoded_addr_mode *addr_mode, fcml_st_operand *operand_def, fcml_st_asm_instruction_part *operand_enc ) {
	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
	fcml_sf_def_tma_explicit_reg *args = (fcml_sf_def_tma_explicit_reg*)addr_mode->addr_mode_args;
	if( operand_def->type != FCML_EOT_REGISTER || operand_def->reg.type != args->reg_type || operand_def->reg.reg != args->reg_num || !fcml_ifn_accept_data_size( context, addr_mode_desc, args->encoded_reg_size, operand_def->reg.size, FCML_IEN_CT_EQUAL ) ) {
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

fcml_ceh_error fcml_fnp_asm_operand_acceptor_opcode_reg( fcml_st_asm_encoding_context *context, fcml_st_asm_addr_mode_desc_details *addr_mode_details, fcml_st_def_addr_mode_desc *addr_mode_desc, fcml_st_def_decoded_addr_mode *addr_mode, fcml_st_operand *operand_def, fcml_st_asm_instruction_part *operand_enc ) {
	fcml_sf_def_tma_opcode_reg *args = (fcml_sf_def_tma_opcode_reg*)addr_mode->addr_mode_args;
	if( operand_def->type != FCML_EOT_REGISTER || operand_def->reg.type != args->reg_type ) {
		return FCML_EN_UNSUPPORTED_OPPERAND;
	}
	if( !fcml_ifn_accept_data_size( context, addr_mode_desc, args->encoded_reg_size, operand_def->reg.size, FCML_IEN_CT_EQUAL ) ) {
		return FCML_EN_UNSUPPORTED_OPPERAND;
	}
	return FCML_CEH_GEC_NO_ERROR;
}

fcml_ceh_error fcml_fnp_asm_operand_encoder_opcode_reg( fcml_ien_asm_part_processor_phase phase, fcml_st_asm_encoding_context *context, fcml_st_def_addr_mode_desc *addr_mode_desc, fcml_st_def_decoded_addr_mode *addr_mode, fcml_st_operand *operand_def, fcml_st_asm_instruction_part *operand_enc ) {
	if( phase == FCML_IEN_ASM_IPPP_FIRST_PHASE ) {
		if( operand_def->reg.reg > 7 ) {
			context->opcode_reg.opcode_reg = operand_def->reg.reg - 8;
			context->opcode_reg.ext_b = FCML_TRUE;
		} else {
			context->opcode_reg.opcode_reg = operand_def->reg.reg;
		}
		if( context->assembler_context->addr_form == FCML_AF_64_BIT ) {
		    context->reg_opcode_needs_rex = operand_def->reg.x64_exp;
		}
	}
	return FCML_CEH_GEC_NO_ERROR;
}

//---------------------------------
// Immediate relative displacement
//---------------------------------

fcml_ceh_error fcml_fnp_asm_operand_acceptor_immediate_dis_relative( fcml_st_asm_encoding_context *context, fcml_st_asm_addr_mode_desc_details *addr_mode_details, fcml_st_def_addr_mode_desc *addr_mode_desc, fcml_st_def_decoded_addr_mode *addr_mode, fcml_st_operand *operand_def, fcml_st_asm_instruction_part *operand_enc ) {
    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
	if ( operand_def->type == FCML_EOT_IMMEDIATE ) {
        fcml_en_attribute_size_flag flags = 0;
	    if( context->assembler_context->addr_form == FCML_AF_64_BIT ) {
            // 64 bit OSA forced. Just in case, addressing mode acceptor is responsible for interpreting FCML_DEF_OPCODE_FLAGS_FORCE_64BITS_EOSA
	        // flag and forcing appropriate OSA size.
	        // TODO: Pzeanalizowac to czy napewno jest poprawne, jezeli nie ma ustawionego FORCE 64 EOA in 64bit mode, dziala chyba nie tak.
	        flags = FCML_EN_ASF_64;
	    } else {
	        flags = FCML_EN_ASF_32 | FCML_EN_ASF_16;
	    }
	    if( !fcml_ifn_set_size_flag( &(context->data_size_flags.allowed_effective_operand_size), flags ) ) {
            error = FCML_EN_UNSUPPORTED_OPPERAND;
        }
	} else {
	    error = FCML_EN_UNSUPPORTED_OPPERAND;
	}
	return error;
}

fcml_ceh_error fcml_ifn_asm_convert_to_requested_rel( fcml_st_integer *value, fcml_data_size expected_size, fcml_uint8_t encoded_rel_size ) {
    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
    if( encoded_rel_size == FCML_EOS_BYTE ) {
        error = fcml_fn_utils_convert_integer_to_integer( value, value, expected_size, FCML_DS_8 );
        if( error ) {
            error = FCML_EN_UNSUPPORTED_OPPERAND;
        }
    }
    return error;
}

int fcml_ifn_asm_calculate_imm_size_for_encoded_rel( fcml_data_size osa, fcml_uint8_t encoded_rel_size ) {
    if( encoded_rel_size == FCML_EOS_UNDEFINED ) {
        return ( osa == FCML_DS_64 ) ? 4 : osa / 8;
    } else {
        return encoded_rel_size;
    }
}

fcml_ceh_error fcml_st_asm_instruction_part_immediate_dis_relative_post_processor( fcml_st_asm_encoding_context *context, fcml_st_asm_instruction_part *instruction_part, fcml_ptr post_processor_args, fcml_uint8_t encoded_rel_size ) {

    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

    // Sanity check.
    if( encoded_rel_size != FCML_EOS_UNDEFINED && encoded_rel_size != FCML_EOS_BYTE ) {
       return FCML_EN_UNSUPPORTED_OPPERAND;
    }

    if( !context->instruction_size.is_not_null ) {
        // Should never happened.
        error = FCML_CEH_GEC_INTERNAL_BUG;
    } else {

        // Optimizer is responsible for setting optimal OSA value.
        fcml_data_size osa = context->data_size_flags.effective_operand_size;

        fcml_st_immediate *imm = (fcml_st_immediate*)post_processor_args;
        fcml_st_integer source;
        fcml_st_integer destination = {0};
        fcml_st_integer displacement = {0};

        int rel_size = fcml_ifn_asm_calculate_imm_size_for_encoded_rel( osa, encoded_rel_size );

        error = fcml_fn_utils_imm_to_integer( imm, &source );
        if( !error ) {

            displacement.is_signed = FCML_TRUE;

            // Check if segment offset is a 16 bit value. Take into account that in case of 16 bit OSA address is truncated to 16 bits.
            if( fcml_fn_utils_convert_integer_to_integer( &source, &destination, osa, osa ) ) {
                error = FCML_EN_UNSUPPORTED_OPPERAND;
            }

            if( !error ) {

                switch( osa ) {
                    case FCML_DS_16: {

                        fcml_int16_t offset = destination.int16;
                        fcml_int16_t ip = (fcml_int16_t)( ( context->assembler_context->ip.eip + context->instruction_size.value + rel_size ) & 0x0000FFFF);
                        fcml_int16_t rel16 = offset - ip;

                        displacement.int16 = rel16;
                        displacement.size = FCML_DS_16;

                        error = fcml_ifn_asm_convert_to_requested_rel( &displacement, FCML_DS_16, encoded_rel_size );

                        break;
                    }
                    case FCML_DS_32: {

                        fcml_int32_t offset = destination.int32;
                        fcml_int32_t eip = (fcml_int32_t)( context->assembler_context->ip.eip + context->instruction_size.value + rel_size );
                        fcml_int32_t rel32 = offset - eip;

                        displacement.int32 = rel32;
                        displacement.size = FCML_DS_32;

                        error = fcml_ifn_asm_convert_to_requested_rel( &displacement, FCML_DS_32, encoded_rel_size );

                        break;
                    }
                    case FCML_DS_64: {

                        fcml_int64_t offset = (fcml_int64_t)destination.int64;
                        fcml_int64_t rip = (fcml_int64_t)( context->assembler_context->ip.rip + context->instruction_size.value + rel_size );
                        fcml_int64_t rel32 = offset - rip;

                        displacement.int32 = (fcml_int32_t)rel32;
                        displacement.size = FCML_DS_32;

                        error = fcml_ifn_asm_convert_to_requested_rel( &displacement, FCML_DS_32, encoded_rel_size );

                        break;
                    }
                }

                if( !error ) {
                    // Encode ModR/M and displacement.
                    fcml_st_memory_stream stream = fcml_ifn_instruction_part_stream( instruction_part );
                    fcml_fn_utils_encode_integer( &stream, &displacement );

                    instruction_part->code_length = stream.offset;
                }

            }

        }
    }

    return error;
}

fcml_ceh_error fcml_st_asm_instruction_part_immediate_dis_relative_post_processor_8( fcml_st_asm_encoding_context *context, fcml_st_asm_instruction_part *instruction_part, fcml_ptr post_processor_args ) {
    return fcml_st_asm_instruction_part_immediate_dis_relative_post_processor( context, instruction_part, post_processor_args, FCML_EOS_BYTE );
}

fcml_ceh_error fcml_st_asm_instruction_part_immediate_dis_relative_post_processor_undef( fcml_st_asm_encoding_context *context, fcml_st_asm_instruction_part *instruction_part, fcml_ptr post_processor_args ) {
    return fcml_st_asm_instruction_part_immediate_dis_relative_post_processor( context, instruction_part, post_processor_args, FCML_EOS_UNDEFINED );
}

fcml_ceh_error fcml_fnp_asm_operand_encoder_immediate_dis_relative( fcml_ien_asm_part_processor_phase phase, fcml_st_asm_encoding_context *context, fcml_st_def_addr_mode_desc *addr_mode_desc, fcml_st_def_decoded_addr_mode *addr_mode, fcml_st_operand *operand_def, fcml_st_asm_instruction_part *operand_enc ) {

    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

    if( phase == FCML_IEN_ASM_IPPP_SECOND_PHASE ) {

        fcml_sf_def_tma_immediate_dis_relative *args = (fcml_sf_def_tma_immediate_dis_relative*)addr_mode->addr_mode_args;

        operand_enc->code_length = 0;

        if( args->encoded_imm_size == FCML_EOS_BYTE ) {
            operand_enc->post_processor = fcml_st_asm_instruction_part_immediate_dis_relative_post_processor_8;
        } else if( args->encoded_imm_size == FCML_EOS_UNDEFINED ) {
            operand_enc->post_processor = fcml_st_asm_instruction_part_immediate_dis_relative_post_processor_undef;
        } else {
            // Unsupported operand size encoded in operand arguments.
            error = FCML_EN_UNSUPPORTED_OPPERAND;
        }

        operand_enc->post_processor_args = &(operand_def->immediate);

    }

	return error;
}

//-------------------------
// Far pointer
//-------------------------

fcml_ceh_error fcml_fnp_asm_operand_acceptor_far_pointer( fcml_st_asm_encoding_context *context, fcml_st_asm_addr_mode_desc_details *addr_mode_details, fcml_st_def_addr_mode_desc *addr_mode_desc, fcml_st_def_decoded_addr_mode *addr_mode, fcml_st_operand *operand_def, fcml_st_asm_instruction_part *operand_enc ) {
    fcml_ceh_error result = FCML_CEH_GEC_NO_ERROR;
    if( operand_def->type != FCML_EOT_FAR_POINTER ) {
        return FCML_EN_UNSUPPORTED_OPPERAND;
    }
    switch( context->assembler_context->addr_form ) {
    case FCML_AF_16_BIT:
        if( operand_def->far_pointer.offset_size == FCML_DS_16 ) {
            if( !fcml_ifn_set_size_flag( &(context->data_size_flags.allowed_effective_operand_size), FCML_EN_ASF_16 ) ) {
                // Size can not be used by this operand.
                result = FCML_EN_UNSUPPORTED_OPPERAND;
            }
        } else {
            // 32 bit offset is not suported in 16 bit mode.
            result = FCML_EN_UNSUPPORTED_OPPERAND;
        }
        break;
    case FCML_AF_32_BIT:
        if( !fcml_ifn_set_size_flag( &(context->data_size_flags.allowed_effective_operand_size), ( operand_def->far_pointer.offset_size == FCML_DS_16 ) ? ( FCML_EN_ASF_16 | FCML_EN_ASF_32 ) : FCML_EN_ASF_32 ) ) {
            // Size can not be used by this operand.
            result = FCML_EN_UNSUPPORTED_OPPERAND;
        }
        break;
    case FCML_AF_64_BIT:
        result = FCML_EN_UNSUPPORTED_OPPERAND;
        break;
    }
	return result;
}

fcml_ceh_error fcml_fnp_asm_operand_encoder_far_pointer( fcml_ien_asm_part_processor_phase phase, fcml_st_asm_encoding_context *context, fcml_st_def_addr_mode_desc *addr_mode_desc, fcml_st_def_decoded_addr_mode *addr_mode, fcml_st_operand *operand_def, fcml_st_asm_instruction_part *operand_enc ) {
    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
    if( phase == FCML_IEN_ASM_IPPP_FIRST_PHASE ) {

        fcml_data_size osa = 0;
        if( context->data_size_flags.effective_operand_size == FCML_DS_UNDEF ) {
            error = fcml_ifn_asm_choose_optimal_osa( context, &osa );
            if( !error ) {
                // Set chosen OSA for next operands.
                context->data_size_flags.effective_operand_size = osa;
            } else {
                FCML_TRACE("Can not calculate best OSA size for far pointer offset.");
                error = FCML_EN_UNSUPPORTED_OPPERAND;
            }
        } else {
            osa = context->data_size_flags.effective_operand_size;
        }

        fcml_st_memory_stream stream = fcml_ifn_instruction_part_stream( operand_enc );

        // Write offset.

        if( operand_def->far_pointer.offset_size == FCML_DS_16 ) {
            fcml_fn_stream_write_word( &stream, operand_def->far_pointer.offset16 );
            operand_enc->code_length = 4;
        } else {
            fcml_fn_stream_write_dword( &stream, operand_def->far_pointer.offset32 );
            operand_enc->code_length = 6;
        }

        // Write segment.

       fcml_fn_stream_write_word( &stream, operand_def->far_pointer.segment );

    }
	return error;

}

//-----------------------------
// Explicit gps reg addressing
//-----------------------------

fcml_ceh_error fcml_fnp_asm_operand_acceptor_explicit_gps_reg_addressing( fcml_st_asm_encoding_context *context, fcml_st_asm_addr_mode_desc_details *addr_mode_details, fcml_st_def_addr_mode_desc *addr_mode_desc, fcml_st_def_decoded_addr_mode *addr_mode, fcml_st_operand *operand_def, fcml_st_asm_instruction_part *operand_enc ) {
    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
    fcml_sf_def_tma_explicit_gps_reg_addressing *args = (fcml_sf_def_tma_explicit_gps_reg_addressing*)addr_mode->addr_mode_args;
    if( operand_def->type != FCML_EOT_ADDRESS || operand_def->address.effective_address.base.reg != args->reg_num ||
            !fcml_ifn_accept_data_size( context, addr_mode_desc, FCML_EOS_EASA, operand_def->address.effective_address.base.size, FCML_IEN_CT_EQUAL ) ||
            !fcml_ifn_accept_data_size( context, addr_mode_desc, args->encoded_operand_size, operand_def->address.effective_address.size_operator, FCML_IEN_CT_EQUAL ) ||
            !fcml_ifn_accept_segment_register( context, &(operand_def->address.segment_selector), args->encoded_segment_register ) ) {
        error = FCML_EN_UNSUPPORTED_OPPERAND;
    }
	return error;
}

//-------------
// Explicit IB
//-------------

fcml_ceh_error fcml_fnp_asm_operand_acceptor_explicit_ib( fcml_st_asm_encoding_context *context, fcml_st_asm_addr_mode_desc_details *addr_mode_details, fcml_st_def_addr_mode_desc *addr_mode_desc, fcml_st_def_decoded_addr_mode *addr_mode, fcml_st_operand *operand_def, fcml_st_asm_instruction_part *operand_enc ) {
    fcml_ceh_error error = FCML_EN_UNSUPPORTED_OPPERAND;
    if( operand_def->type == FCML_EOT_IMMEDIATE ) {
        fcml_st_integer source;
        fcml_st_integer dest;
        error = fcml_fn_utils_imm_to_integer( &(operand_def->immediate), &source );
        if( !error ) {
            error = fcml_fn_utils_convert_integer_to_integer( &source, &dest, FCML_DS_8, FCML_DS_8 );
        }
    }
	return error;
}

fcml_ceh_error fcml_fnp_asm_operand_encoder_explicit_ib( fcml_ien_asm_part_processor_phase phase, fcml_st_asm_encoding_context *context, fcml_st_def_addr_mode_desc *addr_mode_desc, fcml_st_def_decoded_addr_mode *addr_mode, fcml_st_operand *operand_def, fcml_st_asm_instruction_part *operand_enc ) {
    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
    if( phase == FCML_IEN_ASM_IPPP_FIRST_PHASE ) {
        error = FCML_EN_UNSUPPORTED_OPPERAND;
        fcml_sf_def_tma_explicit_ib *exp_ib = (fcml_sf_def_tma_explicit_ib*)addr_mode->addr_mode_args;
        fcml_st_integer source;
        fcml_st_integer dest;
        fcml_ceh_error res = fcml_fn_utils_imm_to_integer( &(operand_def->immediate), &source );
        if( !res ) {
            res = fcml_fn_utils_convert_integer_to_integer( &source, &dest, FCML_DS_8, FCML_DS_8 );
            if( !res ) {
                if( exp_ib->ib == (fcml_uint8_t)dest.int8 ) {
                    error = FCML_CEH_GEC_NO_ERROR;
                }
            }
        }
    }
    return error;
}

//-------------------------
// Segment relative offset
//-------------------------

fcml_ceh_error fcml_fnp_asm_operand_acceptor_segment_relative_offset( fcml_st_asm_encoding_context *context, fcml_st_asm_addr_mode_desc_details *addr_mode_details, fcml_st_def_addr_mode_desc *addr_mode_desc, fcml_st_def_decoded_addr_mode *addr_mode, fcml_st_operand *operand_def, fcml_st_asm_instruction_part *operand_enc ) {

    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

    if ( operand_def->type == FCML_EOT_ADDRESS ) {

        fcml_sf_def_tma_segment_relative_offset *args = (fcml_sf_def_tma_segment_relative_offset*)addr_mode->addr_mode_args;

        fcml_st_address *address = &(operand_def->address);

        if( address->address_form != FCML_AF_OFFSET ) {
            return FCML_EN_UNSUPPORTED_OPPERAND;
        }

        if( !fcml_ifn_accept_data_size( context, addr_mode_desc, args->encoded_operand_size, operand_def->address.effective_address.size_operator, FCML_IEN_CT_EQUAL ) ) {
           return FCML_EN_UNSUPPORTED_OPPERAND;
        }

        fcml_bool is_convertable = FCML_FALSE;
        fcml_en_attribute_size_flag flags;
        fcml_st_integer source_address = {0}, converted_address = {0};

        // Convert IMM value to address.
        error = fcml_fn_utils_offset_to_integer( &(address->offset ), &source_address );
        if( error ) {
           return FCML_EN_UNSUPPORTED_OPPERAND;
        }

        // Check if address can be converted to 16, 32 or 64 bits.
        is_convertable |= fcml_ifn_asm_convert_signed_integer( &source_address, &converted_address, FCML_DS_32, FCML_DS_32, FCML_EN_ASF_32, &flags );
        if( context->assembler_context->addr_form == FCML_AF_64_BIT ) {
           is_convertable |= fcml_ifn_asm_convert_signed_integer( &source_address, &converted_address, FCML_DS_64, FCML_DS_64, FCML_EN_ASF_64, &flags );
        } else {
           is_convertable |= fcml_ifn_asm_convert_signed_integer( &source_address, &converted_address, FCML_DS_16, FCML_DS_16, FCML_EN_ASF_16, &flags );
        }

        if( !fcml_ifn_set_size_flag( &(context->data_size_flags.allowed_effective_address_size), flags ) ) {
           error = FCML_EN_UNSUPPORTED_OPPERAND;
        }

    } else {
        error = FCML_EN_UNSUPPORTED_OPPERAND;
    }

    return error;
}

fcml_ceh_error fcml_fnp_asm_operand_encoder_segment_relative_offset( fcml_ien_asm_part_processor_phase phase, fcml_st_asm_encoding_context *context, fcml_st_def_addr_mode_desc *addr_mode_desc, fcml_st_def_decoded_addr_mode *addr_mode, fcml_st_operand *operand_def, fcml_st_asm_instruction_part *operand_enc ) {
    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
    if( phase == FCML_IEN_ASM_IPPP_FIRST_PHASE ) {
        fcml_data_size asa =  context->data_size_flags.effective_address_size;
        if( asa != FCML_DS_UNDEF ) {

            fcml_st_address *address = &(operand_def->address);

            // Convert IMM value to address.
            fcml_st_integer offset = {0};
            error = fcml_fn_utils_offset_to_integer( &(address->offset ), &offset );
            if( !error ) {

                // Convert address to size indicated by ASA.
                error = fcml_fn_utils_convert_integer_to_integer( &offset, &offset, asa, asa );
                if( !error ) {

                    // Encode offset.
                    fcml_st_memory_stream stream = fcml_ifn_instruction_part_stream( operand_enc );
                    fcml_fn_utils_encode_integer( &stream, &offset );
                    operand_enc->code_length = stream.offset;
                }

            }

        } else {
            // ASA should be set by optimizer.
            error = FCML_EN_UNSUPPORTED_OPPERAND;
        }
    }
    return error;
}

//-------------
// ModR/M - rm
//-------------

fcml_ceh_error fcml_fnp_asm_operand_acceptor_rm( fcml_st_asm_encoding_context *context, fcml_st_asm_addr_mode_desc_details *addr_mode_details, fcml_st_def_addr_mode_desc *addr_mode_desc, fcml_st_def_decoded_addr_mode *addr_mode, fcml_st_operand *operand_def, fcml_st_asm_instruction_part *operand_enc ) {
	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
	fcml_bool result = FCML_TRUE;
	fcml_bool is_reg = FCML_FALSE;
	fcml_bool is_mem = FCML_FALSE;
	fcml_sf_def_tma_rm *args = (fcml_sf_def_tma_rm*)addr_mode->addr_mode_args;
	is_mem = operand_def->type == FCML_EOT_ADDRESS;
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
				FCML_TRACE( "Unsupported register size." );
				error = FCML_EN_UNSUPPORTED_OPPERAND_SIZE;
			}
		}
		if( is_mem ) {
			// OSA.
			if( !fcml_ifn_accept_data_size( context, addr_mode_desc, args->encoded_memory_operand_size, operand_def->address.effective_address.size_operator, FCML_IEN_CT_EQUAL ) ) {
				FCML_TRACE( "Unsupported memory operand size." );
				error = FCML_EN_UNSUPPORTED_OPPERAND_SIZE;
			}
			if( !error ) {

				// ASA.
				fcml_en_addr_form addr_form = context->assembler_context->addr_form;

				fcml_st_modrm mod_rm = {0};
				mod_rm.address = operand_def->address;

				fcml_esa esa;
				fcml_fn_modrm_calculate_effective_address_size( &mod_rm, &esa );
				if( ( esa & FCML_ESA_SF_16 ) && addr_form != FCML_AF_64_BIT ) {
					context->data_size_flags.allowed_effective_address_size.flags |= FCML_EN_ASF_16;
				}
				if( esa & FCML_ESA_SF_32 ) {
					context->data_size_flags.allowed_effective_address_size.flags |= FCML_EN_ASF_32;
				}
				if( ( esa & FCML_ESA_SF_64 ) && addr_form != FCML_AF_16_BIT ) {
					context->data_size_flags.allowed_effective_address_size.flags |= FCML_EN_ASF_64;
				}

			}

		}
	} else {
		error = FCML_EN_UNSUPPORTED_OPPERAND;
	}
	return error;
}

fcml_ceh_error fcml_fnp_asm_operand_encoder_rm( fcml_ien_asm_part_processor_phase phase, fcml_st_asm_encoding_context *context, fcml_st_def_addr_mode_desc *addr_mode_desc, fcml_st_def_decoded_addr_mode *addr_mode, fcml_st_operand *operand_def, fcml_st_asm_instruction_part *operand_enc ) {
	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
	fcml_sf_def_tma_rm *args = (fcml_sf_def_tma_rm*)addr_mode->addr_mode_args;
	switch( phase ) {
	case FCML_IEN_ASM_IPPP_FIRST_PHASE:
		if( operand_def->type == FCML_EOT_REGISTER ) {
			context->mod_rm.reg.is_not_null = FCML_TRUE;
			context->mod_rm.reg.value = operand_def->reg.reg;
			if( context->assembler_context->addr_form == FCML_AF_64_BIT ) {
			    context->mod_rm.reg_opcode_needs_rex = operand_def->reg.x64_exp;
			}
			// Modify data size flags if there is such need.
			error = fcml_ifn_decode_dynamic_operand_size( context, args->encoded_register_operand_size, operand_def->reg.size, NULL,FCML_IEN_CT_EQUAL );
		} else {
		    context->mod_rm.address = operand_def->address;
			error = fcml_ifn_decode_dynamic_operand_size( context, args->encoded_memory_operand_size, operand_def->address.effective_address.size_operator, NULL, FCML_IEN_CT_EQUAL );
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

fcml_ceh_error fcml_fnp_asm_operand_acceptor_r( fcml_st_asm_encoding_context *context, fcml_st_asm_addr_mode_desc_details *addr_mode_details, fcml_st_def_addr_mode_desc *addr_mode_desc, fcml_st_def_decoded_addr_mode *addr_mode, fcml_st_operand *operand_def, fcml_st_asm_instruction_part *operand_enc ) {
	fcml_sf_def_tma_r *args = (fcml_sf_def_tma_r*)addr_mode->addr_mode_args;
	if( operand_def->type != FCML_EOT_REGISTER || operand_def->reg.type != args->reg_type  ) {
		return FCML_EN_UNSUPPORTED_OPPERAND;
	}
	// Some registers allow UNDEF size to be defined for them.
	if( ( operand_def->reg.type != FCML_REG_DR && operand_def->reg.type != FCML_REG_CR ) && operand_def->reg.size != FCML_DS_UNDEF ) {
        if( !fcml_ifn_accept_data_size( context, addr_mode_desc, args->encoded_register_operand_size, operand_def->reg.size, FCML_IEN_CT_EQUAL ) ) {
            return FCML_EN_UNSUPPORTED_OPPERAND;
        }
	}
	return FCML_CEH_GEC_NO_ERROR;
}

fcml_ceh_error fcml_fnp_asm_operand_encoder_r( fcml_ien_asm_part_processor_phase phase, fcml_st_asm_encoding_context *context, fcml_st_def_addr_mode_desc *addr_mode_desc, fcml_st_def_decoded_addr_mode *addr_mode, fcml_st_operand *operand_def, fcml_st_asm_instruction_part *operand_enc ) {
	if( phase == FCML_IEN_ASM_IPPP_FIRST_PHASE ) {
		context->mod_rm.reg_opcode = operand_def->reg.reg;
		if( context->assembler_context->addr_form == FCML_AF_64_BIT ) {
		    context->mod_rm.reg_opcode_needs_rex = operand_def->reg.x64_exp;
		}
	}
	return FCML_CEH_GEC_NO_ERROR;
}

//-------------------------
// Far pointer indirect
//-------------------------

fcml_sf_def_tma_rm  fcml_ist_far_pointer_indirect_args = { FCML_REG_UNDEFINED, FCML_EOS_UNDEFINED, FCML_EOS_FPI, FCML_RMF_M };

fcml_ceh_error fcml_fnp_asm_operand_acceptor_far_pointer_indirect( fcml_st_asm_encoding_context *context, fcml_st_asm_addr_mode_desc_details *addr_mode_details, fcml_st_def_addr_mode_desc *addr_mode_desc, fcml_st_def_decoded_addr_mode *addr_mode, fcml_st_operand *operand_def, fcml_st_asm_instruction_part *operand_enc ) {
    // Prepare modified addressing mode for
    fcml_st_def_decoded_addr_mode l_addr_mode = *addr_mode;
    l_addr_mode.addr_mode_args = &fcml_ist_far_pointer_indirect_args;
    return fcml_fnp_asm_operand_acceptor_rm( context, addr_mode_details, addr_mode_desc, &l_addr_mode, operand_def, operand_enc );
}

fcml_ceh_error fcml_fnp_asm_operand_encoder_far_pointer_indirect( fcml_ien_asm_part_processor_phase phase, fcml_st_asm_encoding_context *context, fcml_st_def_addr_mode_desc *addr_mode_desc, fcml_st_def_decoded_addr_mode *addr_mode, fcml_st_operand *operand_def, fcml_st_asm_instruction_part *operand_enc ) {
    // Prepare modified addressing mode for
    fcml_st_def_decoded_addr_mode l_addr_mode = *addr_mode;
    l_addr_mode.addr_mode_args = &fcml_ist_far_pointer_indirect_args;
    return fcml_fnp_asm_operand_encoder_rm( phase, context, addr_mode_desc, &l_addr_mode, operand_def, operand_enc );
}

//------------
// VVVV
//------------

fcml_ceh_error fcml_fnp_asm_operand_acceptor_vex_vvvv( fcml_st_asm_encoding_context *context, fcml_st_asm_addr_mode_desc_details *addr_mode_details, fcml_st_def_addr_mode_desc *addr_mode_desc, fcml_st_def_decoded_addr_mode *addr_mode, fcml_st_operand *operand_def, fcml_st_asm_instruction_part *operand_enc ) {
	fcml_sf_def_tma_vex_vvvv_reg *args = (fcml_sf_def_tma_vex_vvvv_reg*)addr_mode->addr_mode_args;
	if( operand_def->type != FCML_EOT_REGISTER || operand_def->reg.type != args->reg_type ) {
		return FCML_EN_UNSUPPORTED_OPPERAND;
	}
	if( !fcml_ifn_accept_data_size( context, addr_mode_desc, args->encoded_register_size, operand_def->reg.size, FCML_IEN_CT_EQUAL ) ) {
		return FCML_EN_UNSUPPORTED_OPPERAND;
	}
	return FCML_CEH_GEC_NO_ERROR;
}

fcml_ceh_error fcml_fnp_asm_operand_encoder_vex_vvvv( fcml_ien_asm_part_processor_phase phase, fcml_st_asm_encoding_context *context, fcml_st_def_addr_mode_desc *addr_mode_desc, fcml_st_def_decoded_addr_mode *addr_mode, fcml_st_operand *operand_def, fcml_st_asm_instruction_part *operand_enc ) {
	if( phase == FCML_IEN_ASM_IPPP_FIRST_PHASE ) {
		fcml_st_asm_extension_prefixes_fields *epf = &(context->epf);
		fcml_st_register *reg = &(operand_def->reg);
		epf->vvvv = reg->reg;
	}
	return FCML_CEH_GEC_NO_ERROR;
}

//-----
// is4
//-----

fcml_ceh_error fcml_fnp_asm_operand_acceptor_is4( fcml_st_asm_encoding_context *context, fcml_st_asm_addr_mode_desc_details *addr_mode_details, fcml_st_def_addr_mode_desc *addr_mode_desc, fcml_st_def_decoded_addr_mode *addr_mode, fcml_st_operand *operand_def, fcml_st_asm_instruction_part *operand_enc ) {
	if( operand_def->type != FCML_EOT_REGISTER || operand_def->reg.type != FCML_REG_SIMD ) {
		return FCML_EN_UNSUPPORTED_OPPERAND;
	}
	if( !fcml_ifn_accept_data_size( context, addr_mode_desc, FCML_EOS_L, operand_def->reg.size, FCML_IEN_CT_EQUAL ) ) {
		return FCML_EN_UNSUPPORTED_OPPERAND;
	}
	return FCML_CEH_GEC_NO_ERROR;
}

fcml_ceh_error fcml_fnp_asm_operand_encoder_is4( fcml_ien_asm_part_processor_phase phase, fcml_st_asm_encoding_context *context, fcml_st_def_addr_mode_desc *addr_mode_desc, fcml_st_def_decoded_addr_mode *addr_mode, fcml_st_operand *operand_def, fcml_st_asm_instruction_part *operand_enc ) {
	if( phase == FCML_IEN_ASM_IPPP_FIRST_PHASE ) {
		operand_enc->code[0] = operand_def->reg.reg << 4;
		operand_enc->code_length = 1;
	}
	return FCML_CEH_GEC_NO_ERROR;
}

//------
// vsib
//------

fcml_ceh_error fcml_fnp_asm_operand_acceptor_vsib( fcml_st_asm_encoding_context *context, fcml_st_asm_addr_mode_desc_details *addr_mode_details, fcml_st_def_addr_mode_desc *addr_mode_desc, fcml_st_def_decoded_addr_mode *addr_mode, fcml_st_operand *operand_def, fcml_st_asm_instruction_part *operand_enc ) {
	return FCML_EN_UNSUPPORTED_OPPERAND;
}

fcml_ceh_error fcml_fnp_asm_operand_encoder_vsib( fcml_ien_asm_part_processor_phase phase, fcml_st_asm_encoding_context *context, fcml_st_def_addr_mode_desc *addr_mode_desc, fcml_st_def_decoded_addr_mode *addr_mode, fcml_st_operand *operand_def, fcml_st_asm_instruction_part *operand_enc ) {
	return FCML_EN_UNSUPPORTED_OPPERAND;
}

//------------
// Pseudo-Op.
//------------

fcml_ceh_error fcml_fnp_asm_operand_acceptor_pseudo_op( fcml_st_asm_encoding_context *context, fcml_st_asm_addr_mode_desc_details *addr_mode_details, fcml_st_def_addr_mode_desc *addr_mode_desc, fcml_st_def_decoded_addr_mode *addr_mode, fcml_st_operand *operand_def, fcml_st_asm_instruction_part *operand_enc ) {
    fcml_sf_def_tma_pseudo_op *pseudo_op_args = (fcml_sf_def_tma_pseudo_op*)addr_mode->addr_mode_args;
    fcml_bool is_pseudo_op = context->mnemonic->pseudo_op.is_not_null;
    if( operand_def->type == FCML_EOT_IMMEDIATE && !is_pseudo_op ) {

        // IMM8 encoding is given directly in operand.
        fcml_st_integer source;
        fcml_ceh_error error = fcml_fn_utils_imm_to_integer( &(operand_def->immediate), &source );
        if( error ) {
            return error;
        }

        fcml_st_integer destination;
        if( !fcml_ifn_asm_convert_signed_integer( &source, &destination, FCML_DS_8, FCML_DS_8, 0, NULL ) ) {
            return FCML_EN_UNSUPPORTED_OPPERAND;
        }

        if( destination.int8 & ( ~pseudo_op_args->mask ) ) {
            // TODO: informacja dla uzytkownika w kontenerze bledow.
            return FCML_EN_UNSUPPORTED_OPPERAND;
        }

    } else if ( !is_pseudo_op || operand_def->type != FCML_EOT_NONE ) {
        // IMM8 is not available in operand, so its value should be given in mnemonic configuration. In such case, operand shouldn't exist.
        return FCML_EN_UNSUPPORTED_OPPERAND;
    }
    return FCML_CEH_GEC_NO_ERROR;
}

fcml_ceh_error fcml_fnp_asm_operand_encoder_pseudo_op( fcml_ien_asm_part_processor_phase phase, fcml_st_asm_encoding_context *context, fcml_st_def_addr_mode_desc *addr_mode_desc, fcml_st_def_decoded_addr_mode *addr_mode, fcml_st_operand *operand_def, fcml_st_asm_instruction_part *operand_enc ) {
    if( operand_def->type == FCML_EOT_IMMEDIATE ) {

        // IMM8 encoding is given directly in operand.
        fcml_st_integer source;
        fcml_ceh_error error = fcml_fn_utils_imm_to_integer( &(operand_def->immediate), &source );
        if( error ) {
            return error;
        }

        fcml_st_integer destination;
        if( !fcml_ifn_asm_convert_signed_integer( &source, &destination, FCML_DS_8, FCML_DS_8, 0, NULL ) ) {
            return FCML_EN_UNSUPPORTED_OPPERAND;
        }

        operand_enc->code[0] = destination.int8;

    } else if ( context->mnemonic->pseudo_op.is_not_null ) {
        // IMM8 is not available in operand, so its value should be given in mnemonic configuration.
        operand_enc->code[0] = context->mnemonic->pseudo_op.value;
    }
    operand_enc->code_length = 1;
    return FCML_CEH_GEC_NO_ERROR;
}

// -----------------
// Hints calculators
// -----------------

fcml_st_asm_calculated_hints fcml_fnp_asm_ihc_far_pointer( fcml_st_def_addr_mode_desc *addr_mode, fcml_st_def_decoded_addr_mode *decoded_addr_mode ) {
    fcml_st_asm_calculated_hints hints;
    hints.instruction_hints = FCML_HINT_FAR_POINTER;
    hints.operand_hints = 0;
    return hints;
}

fcml_st_asm_calculated_hints fcml_fnp_asm_ihc_near_pointer( fcml_st_def_addr_mode_desc *addr_mode, fcml_st_def_decoded_addr_mode *decoded_addr_mode ) {
    fcml_st_asm_calculated_hints hints;
    hints.instruction_hints = FCML_HINT_NEAR_POINTER;
    fcml_sf_def_tma_rm *rm_args = (fcml_sf_def_tma_rm*)decoded_addr_mode->addr_mode_args;
    if( rm_args->reg_type == FCML_REG_SIMD && ( rm_args->flags & FCML_RMF_M ) ) {
        hints.operand_hints = FCML_OP_HINT_MULTIMEDIA_INSTRUCTION;
    } else {
        hints.operand_hints = 0;
    }
    return hints;
}

fcml_st_asm_operand_encoder_def fcml_def_operand_encoders[] = {
	{ NULL, NULL, NULL },
	{ fcml_fnp_asm_operand_encoder_imm, fcml_fnp_asm_operand_acceptor_imm, NULL },
	{ fcml_fnp_asm_operand_encoder_explicit_reg, fcml_fnp_asm_operand_acceptor_explicit_reg, NULL },
	{ fcml_fnp_asm_operand_encoder_opcode_reg, fcml_fnp_asm_operand_acceptor_opcode_reg, NULL },
	{ fcml_fnp_asm_operand_encoder_immediate_dis_relative, fcml_fnp_asm_operand_acceptor_immediate_dis_relative, NULL },
	{ fcml_fnp_asm_operand_encoder_far_pointer, fcml_fnp_asm_operand_acceptor_far_pointer, fcml_fnp_asm_ihc_far_pointer },
	{ fcml_fnp_asm_operand_encoder_far_pointer_indirect, fcml_fnp_asm_operand_acceptor_far_pointer_indirect, fcml_fnp_asm_ihc_far_pointer },
	{ NULL, fcml_fnp_asm_operand_acceptor_explicit_gps_reg_addressing, NULL },
	{ fcml_fnp_asm_operand_encoder_explicit_ib, fcml_fnp_asm_operand_acceptor_explicit_ib, NULL },
	{ fcml_fnp_asm_operand_encoder_segment_relative_offset, fcml_fnp_asm_operand_acceptor_segment_relative_offset, NULL },
	{ fcml_fnp_asm_operand_encoder_rm, fcml_fnp_asm_operand_acceptor_rm, fcml_fnp_asm_ihc_near_pointer },
	{ fcml_fnp_asm_operand_encoder_r, fcml_fnp_asm_operand_acceptor_r, NULL },
	{ fcml_fnp_asm_operand_encoder_vex_vvvv, fcml_fnp_asm_operand_acceptor_vex_vvvv, NULL },
	{ fcml_fnp_asm_operand_encoder_is4, fcml_fnp_asm_operand_acceptor_is4, NULL },
	{ fcml_fnp_asm_operand_encoder_vsib, fcml_fnp_asm_operand_acceptor_vsib, NULL },
	{ fcml_fnp_asm_operand_encoder_pseudo_op, fcml_fnp_asm_operand_acceptor_pseudo_op, NULL }
};

/*********************************
 * Instruction encoders.
 *********************************/

fcml_bool fcml_ifn_asm_accept_addr_mode( fcml_st_asm_encoding_context *context, fcml_st_asm_instruction_addr_mode_encoding_details *addr_mode, fcml_st_instruction *instruction ) {

#ifdef FCML_DEBUG
	FCML_TRACE( "Accepting addressing mode: %d", context->__def_index );
#endif

	int index = 0;

	fcml_ifn_asm_instruction_part_processor_chain *current_processor = addr_mode->part_processor_chain;
	while( current_processor ) {
		fcml_ifn_asm_instruction_part_processor_descriptor *descriptor = &(current_processor->processor_descriptor);
		context->part_processor_context.part_processor_index = index;
		if( !context->is_short_form || ( context->is_short_form && descriptor->is_short_form_supported ) ) {
            if( descriptor->processor_acceptor != NULL && descriptor->processor_acceptor( context, &(addr_mode->addr_mode_details), addr_mode->addr_mode_desc, instruction, descriptor->processor_args ) != FCML_CEH_GEC_NO_ERROR ) {
                FCML_TRACE( "Addressing mode not accepted." );
                return FCML_FALSE;
            }
		}
		current_processor = current_processor->next_processor;
		index++;
	}

#ifdef FCML_DEBUG
	FCML_TRACE( "Accepted addressing mode %d - prefixes: 0x%04X, opcode: 0x%02X.", context->__def_index, addr_mode->addr_mode_desc->allowed_prefixes, addr_mode->addr_mode_desc->opcode_flags );
#endif

	return FCML_TRUE;
}

fcml_ien_asm_part_processor_phase fcml_asm_executed_phases[] = { FCML_IEN_ASM_IPPP_FIRST_PHASE, FCML_IEN_ASM_IPPP_SECOND_PHASE, FCML_IEN_ASM_IPPP_THIRD_PHASE };


// Responsible for assembling given addressing mode using attributes provided by context.
fcml_ceh_error fcml_ifn_asm_process_addr_mode( fcml_st_asm_encoding_context *context, fcml_st_asm_instruction_addr_mode_encoding_details *addr_mode, fcml_st_asm_instruction_part_container *instruction_part_container ) {

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
		int index = 0;
		while(current_processor) {
			fcml_ifn_asm_instruction_part_processor_descriptor *descriptor = &(current_processor->processor_descriptor);
			if( descriptor->processor_encoder && ( !context->is_short_form || ( context->is_short_form && descriptor->is_short_form_supported ) ) ) {
				if( !first && descriptor->processor_type == FCML_IEN_ASM_IPPT_ENCODER ) {
					current_instruction_part++;
				}
				first = FCML_FALSE;
				context->part_processor_context.part_processor_index = index;
				error = descriptor->processor_encoder( fcml_asm_executed_phases[i], context, &(addr_mode->addr_mode_details), addr_mode->addr_mode_desc, descriptor->processor_type == FCML_IEN_ASM_IPPT_VERIFIER ? NULL : current_instruction_part, descriptor->processor_args );
				if( error ) {
					// Something failed.
					break;
				}
			}
			current_processor = current_processor->next_processor;
			index++;
		}
	}

	if( !error ) {

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
				error = ip->post_processor( context, ip, ip->post_processor_args );
				if( error ) {
					break;
				}
			}
		}
#ifdef FCML_DEBUG
		FCML_TRACE( "Proceeded addressing mode %d - prefixes: 0x%04X, opcode: 0x%02X (%s).", context->__def_index, addr_mode->addr_mode_desc->allowed_prefixes, addr_mode->addr_mode_desc->opcode_flags, fcml_idfn_encode_size_flags( &(context->data_size_flags) ) );
#endif
	} else {
#ifdef FCML_DEBUG
		FCML_TRACE( "Failed to process addressing mode %d - prefixes: 0x%04X, opcode: 0x%02X (%s).", context->__def_index, addr_mode->addr_mode_desc->allowed_prefixes, addr_mode->addr_mode_desc->opcode_flags, fcml_idfn_encode_size_flags( &(context->data_size_flags) ) );
#endif
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

fcml_ceh_error fcml_ifn_asm_assemble_instruction( fcml_st_asm_encoding_context *context, fcml_st_asm_instruction_addr_mode_encoding_details *addr_mode, fcml_st_assembled_instruction **assembled_instruction ) {

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

		// Preparing result.
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

fcml_ceh_error fcml_ifn_asm_assemble_and_collect_instruction( fcml_st_asm_encoding_context *context, fcml_st_asm_instruction_addr_mode_encoding_details *addr_mode, fcml_ptr args ) {
	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
	fcml_st_assembled_instruction *assembled_instruction;
	error = fcml_ifn_asm_assemble_instruction( context, addr_mode, &assembled_instruction );
	if( !error ) {
		#ifdef FCML_DEBUG
			assembled_instruction->__def_index = context->__def_index;
		#endif

		fcml_bool ignore = FCML_FALSE;

		// Check if there is such instruction is already assembled.
		fcml_st_coll_list *instructions = context->result->instructions;
		fcml_st_coll_list_element *element = instructions->head;
		while( element ) {
		    fcml_st_assembled_instruction *instruction = (fcml_st_assembled_instruction*)element->item;
		    int max_code_len = instruction->code_length > assembled_instruction->code_length ? assembled_instruction->code_length : instruction->code_length;
		    if( fcml_fn_env_memory_cmp( instruction->code, assembled_instruction->code, max_code_len ) ) {
		        // Instructions are the same.
		        ignore = FCML_TRUE;
		        break;
		    }
		    element = element->next;
		}

		if( !ignore ) {
            if( !fcml_fn_coll_list_add_front( context->result->instructions, assembled_instruction ) ) {
                fcml_ifn_asm_free_assembled_instruction( assembled_instruction );
                error = FCML_CEH_GEC_OUT_OF_MEMORY;
            }
		} else {
		    // Free ignored instruction.
		    fcml_ifn_asm_free_assembled_instruction( assembled_instruction );
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

		// Check if there are any operands available. Short form can be used only if there are no operands.
		fcml_bool no_operands = FCML_TRUE;
		int i;
		for( i = 0; i < FCML_OPERANDS_COUNT; i++ ) {
		    if( context->instruction->operands[i].type != FCML_EOT_NONE ) {
		        no_operands = FCML_FALSE;
		        break;
		    }
		}

		// Choose addressing mode.
		if( addr_modes->addr_modes->size ) {
			fcml_st_coll_list_element *addr_mode_element = addr_modes->addr_modes->head;
#ifdef FCML_DEBUG
			int index = 0;
#endif
			while( addr_mode_element ) {

				error = FCML_CEH_GEC_NO_ERROR;

				fcml_st_asm_instruction_addr_mode_encoding_details *addr_mode = (fcml_st_asm_instruction_addr_mode_encoding_details*)addr_mode_element->item;

				fcml_ifn_clean_context( context );

				// This information is necessary to ignore operands encoding process.

				// Ignore all short forms if there are operands available.
				if( !addr_mode->mnemonic->shortcut || no_operands ) {

                    fcml_bool is_short_form = addr_mode->mnemonic->shortcut && no_operands;

                    context->is_short_form = is_short_form;

                    if( is_short_form ) {
                        fcml_data_size asa = addr_mode->mnemonic->supported_asa;
                        context->data_size_flags.effective_address_size = asa;
                        if( asa ) {
                            fcml_fn_cmi_set_attribute_size_flag_for_size( asa, &(context->data_size_flags.allowed_effective_address_size) );
                        }
                        fcml_data_size osa = addr_mode->mnemonic->supported_osa;
                        context->data_size_flags.effective_operand_size = osa;
                        if( osa ) {
                            fcml_fn_cmi_set_attribute_size_flag_for_size( osa, &(context->data_size_flags.allowed_effective_operand_size) );
                        }
                    }

                    context->mnemonic = addr_mode->mnemonic;

#ifdef FCML_DEBUG
				    context->__def_index = index;
#endif

                    // Check if addressing mode matches the hints, if there are any.
                    if( !context->instruction->hints || ( addr_mode->hints & context->instruction->hints ) == context->instruction->hints ) {
                        if( fcml_ifn_asm_accept_addr_mode( context, addr_mode, context->instruction ) ) {
                            // Currently error is just ignored, because we would like to check every available addressing
                            // mode before we return any errors.
                            error = optimizer( context, addr_mode, fcml_ifn_asm_assemble_and_collect_instruction, NULL );
                        }
                    }

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
	// Operands acceptor.
	fcml_fnp_asm_operand_acceptor operand_acceptor;
	// Function responsible for encoding operand.
	fcml_fnp_asm_operand_encoder operand_encoder;
	// Index of the operand to encode.
	int operand_index;
	// Operand hints.
	fcml_hints hints;
};

void fcml_ifn_asm_processor_operand_encoder_args_deallocator( fcml_ptr ptr ) {
	struct fcml_ist_asm_operand_encoder_wrapper_args *wrapper_wrgs = (struct fcml_ist_asm_operand_encoder_wrapper_args*)ptr;
	if( wrapper_wrgs->decoded_addr_mode ) {
		fcml_fnp_def_free_addr_mode( wrapper_wrgs->decoded_addr_mode );
	}
	fcml_fn_env_memory_free( wrapper_wrgs );
}

fcml_ceh_error fcml_ifn_asm_instruction_part_processor_acceptor_operand_encoder_wrapper( fcml_st_asm_encoding_context *context, fcml_st_asm_addr_mode_desc_details *addr_mode_details, fcml_st_def_addr_mode_desc *addr_mode_desc, fcml_st_instruction *instruction, fcml_ptr args ) {
	struct fcml_ist_asm_operand_encoder_wrapper_args *wrapper_args = (struct fcml_ist_asm_operand_encoder_wrapper_args*)args;
	fcml_st_operand *operand = &(instruction->operands[wrapper_args->operand_index]);
	if( wrapper_args->operand_acceptor ) {
	    // Check hints.
	    fcml_hints operand_hits = operand->hints;
	    if( !operand_hits || ( wrapper_args->hints & operand_hits ) == operand_hits ) {
	        return wrapper_args->operand_acceptor( context, addr_mode_details, addr_mode_desc, wrapper_args->decoded_addr_mode, operand, NULL );
	    } else {
	        FCML_TRACE( "Hints do not match." );
	        return FCML_EN_UNSUPPORTED_OPPERAND;
	    }
	} else {
		// This operand shouldn't be defined.
		if( instruction->operands[wrapper_args->operand_index].type != FCML_EOT_NONE ) {
			return FCML_EN_UNSUPPORTED_OPPERAND;
		}
		return FCML_CEH_GEC_NO_ERROR;
	}
}

fcml_ceh_error fcml_ifn_asm_instruction_part_processor_operand_encoder_wrapper( fcml_ien_asm_part_processor_phase phase, fcml_st_asm_encoding_context *context, fcml_st_asm_addr_mode_desc_details *addr_mode_details, fcml_st_def_addr_mode_desc *addr_mode_def, fcml_st_asm_instruction_part *instruction_part, fcml_ptr args ) {
	struct fcml_ist_asm_operand_encoder_wrapper_args *wrapper_args = (struct fcml_ist_asm_operand_encoder_wrapper_args*)args;
	fcml_st_operand *operand = &(context->instruction->operands[wrapper_args->operand_index]);
	if( wrapper_args->operand_encoder ) {
		return wrapper_args->operand_encoder( phase, context, addr_mode_def, wrapper_args->decoded_addr_mode, operand, instruction_part );
	} else {
		return FCML_CEH_GEC_NO_ERROR;
	}
}

fcml_ifn_asm_instruction_part_processor_descriptor fcml_ifn_asm_instruction_part_processor_factory_operand_encoder_wrapper( fcml_uint32_t flags, fcml_st_def_instruction_description *instruction, fcml_st_def_addr_mode_desc *addr_mode, fcml_hints *hints, fcml_ceh_error *error ) {

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

		if( encoders_def->hints_calculator ) {
		    fcml_st_asm_calculated_hints calculated_hints = encoders_def->hints_calculator( addr_mode, wrapper_args->decoded_addr_mode );
		    *hints |= calculated_hints.instruction_hints;
		    wrapper_args->hints = calculated_hints.operand_hints;
		}

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
// XOP/VEX opcode encoder factory. //
////////////////////////////////////

fcml_ceh_error fcml_ifn_asm_instruction_part_processor_XOP_VEX_opcode_encoder( fcml_ien_asm_part_processor_phase phase, fcml_st_asm_encoding_context *context, fcml_st_asm_addr_mode_desc_details *addr_mode_details, fcml_st_def_addr_mode_desc *addr_mode_def, fcml_st_asm_instruction_part *instruction_part, fcml_ptr args ) {
	if( phase == FCML_IEN_ASM_IPPP_FIRST_PHASE ) {
		// Encoder has to set some flags for XOP/VEX prefix encoder.
		fcml_st_asm_extension_prefixes_fields *epf = &(context->epf);
		int opcode_bytes = FCML_DEF_OPCODE_FLAGS_OPCODE_NUM( addr_mode_def->opcode_flags );
		int i = 0;
		int code_index = 0;
		fcml_uint8_t opcode_byte = addr_mode_def->opcode[i++];
		switch( opcode_byte ) {
		case 0x0F: {
			opcode_byte = addr_mode_def->opcode[i++];
			switch( opcode_byte ) {
			case 0x38:
				epf->mmmm = 0x02;
				break;
			case 0x3A:
				epf->mmmm = 0x03;
				break;
			default:
				instruction_part->code[code_index++] = opcode_byte;
				epf->mmmm = 0x01;
				break;
			}
			break;
		}
		case 0x08:
		case 0x09:
		case 0x0A:
			epf->mmmm = opcode_byte;
			break;
		}
		for( ; i < opcode_bytes; i++ ) {
			instruction_part->code[code_index++] = addr_mode_def->opcode[i];
		}
		instruction_part->code_length = code_index;
	}
	return  FCML_CEH_GEC_NO_ERROR;
}

fcml_ifn_asm_instruction_part_processor_descriptor fcml_ifn_asm_instruction_part_processor_factory_XOP_VEX_opcode_encoder( fcml_uint32_t flags, fcml_st_def_instruction_description *instruction, fcml_st_def_addr_mode_desc *addr_mode, fcml_hints *hints, fcml_ceh_error *error ) {
	fcml_ifn_asm_instruction_part_processor_descriptor descriptor = {0};
	if( FCML_DEF_PREFIX_VEX_REQ( addr_mode->allowed_prefixes ) || FCML_DEF_PREFIX_XOP_REQ( addr_mode->allowed_prefixes ) ) {
		descriptor.processor_type = FCML_IEN_ASM_IPPT_ENCODER;
		descriptor.processor_args = NULL;
		descriptor.processor_encoder = fcml_ifn_asm_instruction_part_processor_XOP_VEX_opcode_encoder;
		descriptor.processor_acceptor = NULL;
	}
	return descriptor;
}

////////////////////////////////////////////////////
// Opcode with condition encoded encoder factory. //
////////////////////////////////////////////////////

fcml_ceh_error fcml_ifn_asm_instruction_part_processor_conditional_opcode_encoder( fcml_ien_asm_part_processor_phase phase, fcml_st_asm_encoding_context *context, fcml_st_asm_addr_mode_desc_details *addr_mode_details, fcml_st_def_addr_mode_desc *addr_mode_def, fcml_st_asm_instruction_part *instruction_part, fcml_ptr args ) {
    if( phase == FCML_IEN_ASM_IPPP_SECOND_PHASE ) {
        int opcode_bytes = FCML_DEF_OPCODE_FLAGS_OPCODE_NUM( addr_mode_def->opcode_flags );
        int primary_opcode = FCML_DEF_OPCODE_FLAGS_PRIMARY_OPCODE( addr_mode_def->opcode_flags );
        int i;
        for( i = 0; i < opcode_bytes; i++ ) {
            fcml_uint8_t opcode_byte = addr_mode_def->opcode[i];
            // TODO: Mozna polaczyc kod tego i operand encodera od rejestrow, w zasadzie to to samo tylko ie rozni zrodem numerkow.
            instruction_part->code[i] = ( i == primary_opcode ) ? ( opcode_byte + addr_mode_details->condition.condition_type * 2 + ( addr_mode_details->condition.is_negation ? 1 : 0 ) ) : opcode_byte;
        }
        instruction_part->code_length = opcode_bytes;
    }
    return  FCML_CEH_GEC_NO_ERROR;
}

fcml_ifn_asm_instruction_part_processor_descriptor fcml_ifn_asm_instruction_part_processor_factory_conditional_opcode_encoder( fcml_uint32_t flags, fcml_st_def_instruction_description *instruction, fcml_st_def_addr_mode_desc *addr_mode, fcml_hints *hints, fcml_ceh_error *error ) {
    fcml_ifn_asm_instruction_part_processor_descriptor descriptor = {0};
    if( FCML_DEF_OPCODE_FLAGS_OPCODE_FIELD_TTTN( addr_mode->opcode_flags ) ) {
        descriptor.processor_type = FCML_IEN_ASM_IPPT_ENCODER;
        descriptor.processor_args = NULL;
        descriptor.processor_encoder = fcml_ifn_asm_instruction_part_processor_conditional_opcode_encoder;
        descriptor.processor_acceptor = NULL;
    }
    return descriptor;
}


///////////////////////////////////////////////////
// Opcode with register encoded encoder factory. //
///////////////////////////////////////////////////

fcml_ceh_error fcml_ifn_asm_instruction_part_processor_reg_opcode_encoder( fcml_ien_asm_part_processor_phase phase, fcml_st_asm_encoding_context *context, fcml_st_asm_addr_mode_desc_details *addr_mode_details, fcml_st_def_addr_mode_desc *addr_mode_def, fcml_st_asm_instruction_part *instruction_part, fcml_ptr args ) {
	if( phase == FCML_IEN_ASM_IPPP_SECOND_PHASE ) {
		int opcode_bytes = FCML_DEF_OPCODE_FLAGS_OPCODE_NUM( addr_mode_def->opcode_flags );
		int primary_opcode = FCML_DEF_OPCODE_FLAGS_PRIMARY_OPCODE( addr_mode_def->opcode_flags );
		int i;
		for( i = 0; i < opcode_bytes; i++ ) {
			fcml_uint8_t opcode_byte = addr_mode_def->opcode[i];
			instruction_part->code[i] = ( i == primary_opcode ) ? opcode_byte + context->opcode_reg.opcode_reg : opcode_byte;
		}
		instruction_part->code_length = opcode_bytes;
	}
	return  FCML_CEH_GEC_NO_ERROR;
}

fcml_ifn_asm_instruction_part_processor_descriptor fcml_ifn_asm_instruction_part_processor_factory_reg_opcode_encoder( fcml_uint32_t flags, fcml_st_def_instruction_description *instruction, fcml_st_def_addr_mode_desc *addr_mode, fcml_hints *hints, fcml_ceh_error *error ) {
	fcml_ifn_asm_instruction_part_processor_descriptor descriptor = {0};
	if( FCML_DEF_OPCODE_FLAGS_OPCODE_FIELD_REG( addr_mode->opcode_flags ) ) {
		descriptor.processor_type = FCML_IEN_ASM_IPPT_ENCODER;
		descriptor.processor_args = NULL;
		descriptor.processor_encoder = fcml_ifn_asm_instruction_part_processor_reg_opcode_encoder;
		descriptor.processor_acceptor = NULL;
	}
	return descriptor;
}

////////////////////////////////////
// Simple opcode encoder factory. //
////////////////////////////////////

fcml_ceh_error fcml_ifn_asm_instruction_part_processor_simple_opcode_encoder( fcml_ien_asm_part_processor_phase phase, fcml_st_asm_encoding_context *context, fcml_st_asm_addr_mode_desc_details *addr_mode_details, fcml_st_def_addr_mode_desc *addr_mode_def, fcml_st_asm_instruction_part *instruction_part, fcml_ptr args ) {
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

fcml_ifn_asm_instruction_part_processor_descriptor fcml_ifn_asm_instruction_part_processor_factory_simple_opcode_encoder( fcml_uint32_t flags, fcml_st_def_instruction_description *instruction, fcml_st_def_addr_mode_desc *addr_mode, fcml_hints *hints, fcml_ceh_error *error ) {
	fcml_ifn_asm_instruction_part_processor_descriptor descriptor = {0};
	descriptor.processor_type = FCML_IEN_ASM_IPPT_ENCODER;
	descriptor.processor_args = NULL;
	descriptor.processor_encoder = fcml_ifn_asm_instruction_part_processor_simple_opcode_encoder;
	descriptor.processor_acceptor = NULL;
	return descriptor;
}

/////////////////////////////////
// Prefixes encoder factories. //
/////////////////////////////////

// Segment override prefix.

fcml_uint8_t fcml_itb_asm_prefix_override_mapping[] = {
    0x26,
    0x2e,
    0x36,
    0x3e,
    0x64,
    0x65
};

fcml_ceh_error fcml_ifn_asm_instruction_part_processor_segment_override_prefix_encoder( fcml_ien_asm_part_processor_phase phase, fcml_st_asm_encoding_context *context, fcml_st_asm_addr_mode_desc_details *addr_mode_details, fcml_st_def_addr_mode_desc *addr_mode_def, fcml_st_asm_instruction_part *instruction_part, fcml_ptr args ) {
    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
    if( phase == FCML_IEN_ASM_IPPP_THIRD_PHASE ) {
        if( context->segment_override.type == FCML_REG_SEG ) {
            fcml_uint8_t seg_reg_num = context->segment_override.reg;
            if( seg_reg_num <= 5) {
                instruction_part->code[0] = fcml_itb_asm_prefix_override_mapping[ seg_reg_num ];
                instruction_part->code_length = 1;
            } else {
                // Unknown segment register.
                error = FCML_CEH_GEC_ILLEGAL_STATE_EXCEPTION;
            }
        }
    }
    return error;
}

fcml_ifn_asm_instruction_part_processor_descriptor fcml_ifn_asm_instruction_part_processor_factory_segment_override_prefix_encoder( fcml_uint32_t flags, fcml_st_def_instruction_description *instruction, fcml_st_def_addr_mode_desc *addr_mode, fcml_hints *hints, fcml_ceh_error *error ) {
    fcml_ifn_asm_instruction_part_processor_descriptor descriptor = {0};
    descriptor.processor_type = FCML_IEN_ASM_IPPT_ENCODER;
    descriptor.processor_args = NULL;
    descriptor.processor_encoder = fcml_ifn_asm_instruction_part_processor_segment_override_prefix_encoder;
    descriptor.processor_acceptor = NULL;
    return descriptor;
}

// Mandatory prefixes.

fcml_ceh_error fcml_ifn_asm_instruction_part_processor_mandatory_prefixes_encoder( fcml_ien_asm_part_processor_phase phase, fcml_st_asm_encoding_context *context, fcml_st_asm_addr_mode_desc_details *addr_mode_details, fcml_st_def_addr_mode_desc *addr_mode_def, fcml_st_asm_instruction_part *instruction_part, fcml_ptr args ) {
	if( phase == FCML_IEN_ASM_IPPP_THIRD_PHASE ) {
		fcml_uint8_t prefix = 0x66;
		if( FCML_DEF_PREFIX_MANDATORY_F2( addr_mode_def->allowed_prefixes ) ) {
			prefix = 0xF2;
		} else if( FCML_DEF_PREFIX_MANDATORY_F3( addr_mode_def->allowed_prefixes ) ) {
			prefix = 0xF3;
		}
		instruction_part->code[0] = prefix;
		instruction_part->code_length = 1;
	}
	return FCML_CEH_GEC_NO_ERROR;
}

fcml_ifn_asm_instruction_part_processor_descriptor fcml_ifn_asm_instruction_part_processor_factory_mandatory_prefixes_encoder( fcml_uint32_t flags, fcml_st_def_instruction_description *instruction, fcml_st_def_addr_mode_desc *addr_mode, fcml_hints *hints, fcml_ceh_error *error ) {
	fcml_ifn_asm_instruction_part_processor_descriptor descriptor = {0};
	fcml_bool is_mandatory = FCML_DEF_PREFIX_MANDATORY_66( addr_mode->allowed_prefixes ) || FCML_DEF_PREFIX_MANDATORY_F2( addr_mode->allowed_prefixes ) || FCML_DEF_PREFIX_MANDATORY_F3( addr_mode->allowed_prefixes );
	// Mandatory prefixes can be applied to instructions without neither XOP nor VEX prefixes.
	if( is_mandatory && !FCML_DEF_PREFIX_VEX_REQ( addr_mode->allowed_prefixes ) && !FCML_DEF_PREFIX_XOP_REQ( addr_mode->allowed_prefixes ) ) {
		descriptor.processor_type = FCML_IEN_ASM_IPPT_ENCODER;
		descriptor.processor_args = NULL;
		descriptor.processor_encoder = fcml_ifn_asm_instruction_part_processor_mandatory_prefixes_encoder;
		descriptor.processor_acceptor = NULL;
	}
	return descriptor;
}

// 66 prefix.

fcml_ceh_error fcml_ifn_asm_instruction_part_processor_66_prefix_encoder( fcml_ien_asm_part_processor_phase phase, fcml_st_asm_encoding_context *context, fcml_st_asm_addr_mode_desc_details *addr_mode_details, fcml_st_def_addr_mode_desc *addr_mode_def, fcml_st_asm_instruction_part *instruction_part, fcml_ptr args ) {
	if( phase == FCML_IEN_ASM_IPPP_THIRD_PHASE ) {
		fcml_bool encode = FCML_FALSE;
		fcml_uint64_t addr_type = addr_mode_def->addressing_mode_type;
		// Mandatory 0x66 prefix is encoded in different way in case of VEX encoded instructions.
		if( !( addr_type & FCML_AMT_VEXx ) ) {
            if( FCML_DEF_PREFIX_MANDATORY_66( addr_mode_def->allowed_prefixes ) ) {
                encode = FCML_TRUE;
            } else if ( !( addr_type & FCML_AMT_SIMD ) ) {
                // SIMD instructions do not need 0x66 to change EOSA.
                encode = ( context->assembler_context->addr_form == FCML_AF_16_BIT && context->data_size_flags.effective_operand_size == FCML_DS_32 ) ||
                        ( ( context->assembler_context->addr_form == FCML_AF_32_BIT || context->assembler_context->addr_form == FCML_AF_64_BIT ) && context->data_size_flags.effective_operand_size == FCML_DS_16 );
            }
            if( encode ) {
                instruction_part->code[0] = 0x66;
                instruction_part->code_length = 1;
            }
		}
	}
	return FCML_CEH_GEC_NO_ERROR;
}

fcml_ifn_asm_instruction_part_processor_descriptor fcml_ifn_asm_instruction_part_processor_factory_66_prefix_encoder( fcml_uint32_t flags, fcml_st_def_instruction_description *instruction, fcml_st_def_addr_mode_desc *addr_mode, fcml_hints *hints, fcml_ceh_error *error ) {
	fcml_ifn_asm_instruction_part_processor_descriptor descriptor = {0};
	// Mandatory prefixes are handled by dedicated IPP.
	if( !FCML_DEF_PREFIX_MANDATORY_66( addr_mode->allowed_prefixes ) && !FCML_DEF_PREFIX_VEX_REQ( addr_mode->allowed_prefixes ) && !FCML_DEF_PREFIX_XOP_REQ( addr_mode->allowed_prefixes ) ) {
		descriptor.processor_type = FCML_IEN_ASM_IPPT_ENCODER;
		descriptor.processor_args = NULL;
		descriptor.processor_encoder = fcml_ifn_asm_instruction_part_processor_66_prefix_encoder;
		descriptor.processor_acceptor = NULL;
	}
	return descriptor;
}

// 67 prefix.

fcml_ceh_error fcml_ifn_asm_instruction_part_processor_67_prefix_encoder( fcml_ien_asm_part_processor_phase phase, fcml_st_asm_encoding_context *context, fcml_st_asm_addr_mode_desc_details *addr_mode_details, fcml_st_def_addr_mode_desc *addr_mode_def, fcml_st_asm_instruction_part *instruction_part, fcml_ptr args ) {
	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
	if( phase == FCML_IEN_ASM_IPPP_THIRD_PHASE ) {
	    // If effective address size is not set, it means that instruction is not interested in ASA and just doesn't use it.
		if( context->data_size_flags.effective_address_size && ( context->assembler_context->effective_address_size != context->data_size_flags.effective_address_size ) ) {
			fcml_bool encode =
					( context->assembler_context->effective_address_size == FCML_DS_16 && context->data_size_flags.effective_address_size == FCML_DS_32 ) ||
					( context->assembler_context->effective_address_size == FCML_DS_32 && context->data_size_flags.effective_address_size == FCML_DS_16 ) ||
					( context->assembler_context->effective_address_size == FCML_DS_64 && context->data_size_flags.effective_address_size == FCML_DS_32 );
			if( encode ) {
				instruction_part->code[0] = 0x67;
				instruction_part->code_length = 1;
			} else {
				error = FCML_EN_UNSUPPORTED_ADDRESS_SIZE;
			}
		}
	}
	return error;
}

fcml_ifn_asm_instruction_part_processor_descriptor fcml_ifn_asm_instruction_part_processor_factory_67_prefix_encoder( fcml_uint32_t flags, fcml_st_def_instruction_description *instruction, fcml_st_def_addr_mode_desc *addr_mode, fcml_hints *hints, fcml_ceh_error *error ) {
	fcml_ifn_asm_instruction_part_processor_descriptor descriptor = {0};

	// 67 prefix can be applied to instructions without neither XOP nor VEX prefixes.
	if( !FCML_DEF_PREFIX_VEX_REQ( addr_mode->allowed_prefixes ) && !FCML_DEF_PREFIX_XOP_REQ( addr_mode->allowed_prefixes ) ) {
		descriptor.processor_type = FCML_IEN_ASM_IPPT_ENCODER;
		descriptor.processor_args = NULL;
		descriptor.processor_encoder = fcml_ifn_asm_instruction_part_processor_67_prefix_encoder;
		descriptor.processor_acceptor = NULL;
	}

	return descriptor;
}

// ******************
// * VEX/XOP Prefix *
// ******************

fcml_ceh_error fcml_ifn_asm_instruction_part_processor_VEX_XOP_prefix_encoder( fcml_ien_asm_part_processor_phase phase, fcml_st_asm_encoding_context *context, fcml_st_asm_addr_mode_desc_details *addr_mode_details, fcml_st_def_addr_mode_desc *addr_mode_def, fcml_st_asm_instruction_part *instruction_part, fcml_ptr args ) {
	if( phase == FCML_IEN_ASM_IPPP_FIRST_PHASE ) {
		if( FCML_DEF_PREFIX_L_1( addr_mode_def->allowed_prefixes ) ) {
			context->data_size_flags.l.is_not_null = FCML_TRUE;
			context->data_size_flags.l.value = 0x01;
		} else if ( FCML_DEF_PREFIX_L_0( addr_mode_def->allowed_prefixes ) ) {
			context->data_size_flags.l.is_not_null = FCML_TRUE;
			context->data_size_flags.l.value = 0x00;
		}
	} if( phase == FCML_IEN_ASM_IPPP_THIRD_PHASE ) {

		fcml_st_asm_extension_prefixes_fields *epf = &(context->epf);
		fcml_st_encoded_modrm *encoded_mod_rm = &(context->encoded_mod_rm);

		// Check if one byte VEX encoding can be used.
		fcml_bool is_vex = FCML_DEF_PREFIX_VEX_REQ( addr_mode_def->allowed_prefixes );

		// Remember, the 2-byte VEX implies a leading 0Fh opcode byte, it's why "m-mmmm" field should be 1.
		fcml_bool is_two_bytes_vex = ( !context->assembler_context->configuration.force_three_byte_VEX && is_vex && epf->mmmm == 0x01 && !FCML_DEF_PREFIX_W_1( addr_mode_def->allowed_prefixes ) && !encoded_mod_rm->ext_x && !encoded_mod_rm->ext_b );

		fcml_uint8_t prefix_bytes[3];
		fcml_uint8_t prefix_size = 0;

		// Encode PP.
		fcml_uint8_t pp = 0;
		if( FCML_DEF_PREFIX_MANDATORY_66( addr_mode_def->allowed_prefixes ) ) {
			pp = 0x01;
		} else if( FCML_DEF_PREFIX_MANDATORY_F2( addr_mode_def->allowed_prefixes ) ) {
			pp = 0x03;
		} else if( FCML_DEF_PREFIX_MANDATORY_F3( addr_mode_def->allowed_prefixes ) ) {
			pp = 0x02;
		}

		fcml_uint8_t prefix = 0;

		if( is_two_bytes_vex ) {
			// Two byte VEX prefix.
			prefix = FCML_ENCODE_VEXOP_R( prefix, encoded_mod_rm->ext_r );
			prefix = FCML_ENCODE_VEXOP_VVVV( prefix, epf->vvvv );
			if( context->data_size_flags.l.is_not_null ) {
				prefix = FCML_ENCODE_VEXOP_L( prefix, context->data_size_flags.l.value );
			}
			prefix = FCML_ENCODE_VEXOP_PP( prefix, pp );
			prefix_bytes[0] = 0xC5;
			prefix_bytes[1] = prefix;
			prefix_size = 2;
		} else {
			// Three bytes VEX or XOP prefix.
			prefix_bytes[0] = ( is_vex ) ? 0xC4 : 0x8F;
			prefix = FCML_ENCODE_VEXOP_R( prefix, encoded_mod_rm->ext_r );
			prefix = FCML_ENCODE_VEXOP_X( prefix, encoded_mod_rm->ext_x );
			prefix = FCML_ENCODE_VEXOP_B( prefix, encoded_mod_rm->ext_b );
			prefix = FCML_ENCODE_VEXOP_MMMM( prefix, epf->mmmm );
			prefix_bytes[1] = prefix;
			prefix = 0;
			prefix = FCML_ENCODE_VEXOP_W( prefix, FCML_DEF_PREFIX_W_1( addr_mode_def->allowed_prefixes ) );
			prefix = FCML_ENCODE_VEXOP_VVVV( prefix, epf->vvvv );
			if( context->data_size_flags.l.is_not_null ) {
				prefix = FCML_ENCODE_VEXOP_L( prefix, context->data_size_flags.l.value );
			}
			prefix = FCML_ENCODE_VEXOP_PP( prefix, pp );
			prefix_bytes[2] = prefix;
			prefix_size = 3;
		}

		int i;
		for( i = 0; i < prefix_size; i++ ) {
			instruction_part->code[i] = prefix_bytes[i];
		}
		instruction_part->code_length = prefix_size;

	}
	return FCML_CEH_GEC_NO_ERROR;
}

fcml_ifn_asm_instruction_part_processor_descriptor fcml_ifn_asm_instruction_part_processor_factory_VEX_XOP_prefix_encoder( fcml_uint32_t flags, fcml_st_def_instruction_description *instruction, fcml_st_def_addr_mode_desc *addr_mode, fcml_hints *hints, fcml_ceh_error *error ) {
	fcml_ifn_asm_instruction_part_processor_descriptor descriptor = {0};
	if( FCML_DEF_PREFIX_VEX_REQ( addr_mode->allowed_prefixes ) || FCML_DEF_PREFIX_XOP_REQ( addr_mode->allowed_prefixes ) ) {
		descriptor.processor_type = FCML_IEN_ASM_IPPT_ENCODER;
		descriptor.processor_args = NULL;
		descriptor.processor_encoder = fcml_ifn_asm_instruction_part_processor_VEX_XOP_prefix_encoder;
		descriptor.processor_acceptor = NULL;
	}
	return descriptor;
}

// REX prefix.

fcml_ceh_error fcml_ifn_asm_instruction_part_processor_REX_prefix_encoder( fcml_ien_asm_part_processor_phase phase, fcml_st_asm_encoding_context *context, fcml_st_asm_addr_mode_desc_details *addr_mode_details, fcml_st_def_addr_mode_desc *addr_mode_def, fcml_st_asm_instruction_part *instruction_part, fcml_ptr args ) {
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
			fcml_st_modrm *mod_rm = &(context->mod_rm);

			// W field.
			fcml_data_size eosa = size_flags->effective_operand_size;
			if( FCML_DEF_PREFIX_W_1( addr_mode_def->allowed_prefixes ) ) {
				if( eosa != 0 && eosa != FCML_DS_64  ) {
					// Operand size should be 64 bits.
					return FCML_EN_UNSUPPORTED_OPPERAND_SIZE;
				}
				rex = FCML_ENCODE_REX_W( rex, 1 );
			} else if( eosa == FCML_DS_64 && !FCML_DEF_OPCODE_FLAGS_FORCE_64BITS_EOSA( addr_mode_def->opcode_flags ) ) {
			    // When OSA is forced to 64 bits, W flag is needless.
				rex = FCML_ENCODE_REX_W( rex, 1 );
			}

			// Fields.
			rex = FCML_ENCODE_REX_R( rex, encoded_mod_rm->ext_r );
			rex = FCML_ENCODE_REX_X( rex, encoded_mod_rm->ext_x );
			rex = FCML_ENCODE_REX_B( rex, encoded_mod_rm->ext_b );
			rex = FCML_ENCODE_REX_B( rex, context->opcode_reg.ext_b );

			// Assembler configuration.
			fcml_st_assembler_configuration *cfg = &(context->assembler_context->configuration);

			// Even if REX do not contains any flags set in some cases registers BPL, SPL, DIL, SIL needs REX to be defined.
			// Additionally we can force it to occur by setting a configuration flag.
			if( rex != FCML_ENCODE_REX_BASE || ( FCML_DEF_OPCODE_FLAGS_OPCODE_IS_MODRM( addr_mode_def->opcode_flags ) && cfg->force_unnecessary_rex_prefix ) || mod_rm->reg_opcode_needs_rex || context->reg_opcode_needs_rex ) {
				instruction_part->code[0] = rex;
				instruction_part->code_length = 1;
			}

		}
	}
	return FCML_CEH_GEC_NO_ERROR;
}

fcml_ifn_asm_instruction_part_processor_descriptor fcml_ifn_asm_instruction_part_processor_factory_REX_prefix_encoder( fcml_uint32_t flags, fcml_st_def_instruction_description *instruction, fcml_st_def_addr_mode_desc *addr_mode, fcml_hints *hints, fcml_ceh_error *error ) {
	fcml_ifn_asm_instruction_part_processor_descriptor descriptor = {0};
	// 66 prefix can be applied to instructions without neither XOP nor VEX prefixes. Remember that this prefix can bes mandatory one.
	if( FCML_DEF_OPCODE_FLAGS_64_BIT_MODE_SUPPORTED( addr_mode->opcode_flags ) && !( FCML_DEF_PREFIX_VEX_REQ( addr_mode->allowed_prefixes ) || FCML_DEF_PREFIX_XOP_REQ( addr_mode->allowed_prefixes ) ) ) {
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

fcml_ceh_error fcml_ifn_asm_instruction_part_processor_ModRM_encoder( fcml_ien_asm_part_processor_phase phase, fcml_st_asm_encoding_context *context, fcml_st_asm_addr_mode_desc_details *addr_mode_details, fcml_st_def_addr_mode_desc *addr_mode_def, fcml_st_asm_instruction_part *instruction_part, fcml_ptr args ) {
	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
	fcml_st_assembler_context *assembler_context = context->assembler_context;
	if( phase == FCML_IEN_ASM_IPPP_SECOND_PHASE ) {

		fcml_st_modrm_encoder_context ctx;
		ctx.addr_form = assembler_context->addr_form;
		// TODO: Dodac hintsy.
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
			if( context->data_size_flags.effective_address_size == ctx.chosen_effective_address_size ) {
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
				// ModRM encoded to the form not supported by current addressing mode. For example, addressing mode needs ASA 32, but asembled ModRM required 16 bit ASA.
				error = FCML_EN_UNSUPPORTED_ADDRESS_SIZE;
			}
		}

	}
	return error;
}

fcml_ifn_asm_instruction_part_processor_descriptor fcml_ifn_asm_instruction_part_processor_factory_ModRM_encoder( fcml_uint32_t flags, fcml_st_def_instruction_description *instruction, fcml_st_def_addr_mode_desc *addr_mode, fcml_hints *hints, fcml_ceh_error *error ) {
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

fcml_ceh_error fcml_ifn_asm_instruction_part_processor_addr_mode_acceptor( fcml_st_asm_encoding_context *context, fcml_st_asm_addr_mode_desc_details *addr_mode_details, fcml_st_def_addr_mode_desc *addr_mode_def, fcml_st_instruction *instruction, fcml_ptr args ) {
	fcml_en_addr_form addr_form = context->assembler_context->addr_form;
	if( !FCML_DEF_OPCODE_FLAGS_64_BIT_MODE_SUPPORTED( addr_mode_def->opcode_flags ) && addr_form == FCML_AF_64_BIT ) {
		return FCML_EN_UNSUPPORTED_ADDRESSING_MODE;
	} else if ( !FCML_DEF_OPCODE_FLAGS_16_32_BIT_MODE_SUPPORTED( addr_mode_def->opcode_flags ) && ( addr_form == FCML_AF_16_BIT || addr_form == FCML_AF_32_BIT ) ) {
		return FCML_EN_UNSUPPORTED_ADDRESSING_MODE;
	}
	// Set restrictions if there are any.
	// TODO: sprawzi czy faktycznie jest potrzebne rozdzielenie na nullable i zwykla wartosc.
	if( addr_mode_details->allowed_osa != FCML_EN_ASF_ANY ) {
		context->data_size_flags.allowed_effective_operand_size.flags = addr_mode_details->allowed_osa;
		context->data_size_flags.allowed_effective_operand_size.is_set = FCML_TRUE;
	}
	if( addr_mode_details->allowed_asa != FCML_EN_ASF_ANY ) {
		context->data_size_flags.allowed_effective_address_size.flags = addr_mode_details->allowed_asa;
		context->data_size_flags.allowed_effective_address_size.is_set = FCML_TRUE;
	}
	// Force 64 bit OSA in 64 bit addressing mode.
	if( addr_form == FCML_AF_64_BIT && FCML_DEF_OPCODE_FLAGS_FORCE_64BITS_EOSA( addr_mode_def->opcode_flags ) ) {
	    context->data_size_flags.allowed_effective_operand_size.flags = FCML_EN_ASF_64;
        context->data_size_flags.allowed_effective_operand_size.is_set = FCML_TRUE;
	}
	return FCML_CEH_GEC_NO_ERROR;
}

fcml_ifn_asm_instruction_part_processor_descriptor fcml_ifn_asm_instruction_part_processor_factory_addr_mode_acceptor( fcml_uint32_t flags, fcml_st_def_instruction_description *instruction, fcml_st_def_addr_mode_desc *addr_mode, fcml_hints *hints, fcml_ceh_error *error ) {
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
	fcml_bool is_short_form_supported;
} fcml_ist_asm_instruction_part_factory_sequence;

// List of instruction part encoders for instruction opcode.
fcml_ist_asm_instruction_part_factory_details fcml_asm_instruction_part_processor_factories_opcode_for_IA[] = {
	{ fcml_ifn_asm_instruction_part_processor_factory_XOP_VEX_opcode_encoder, 0 },
	{ fcml_ifn_asm_instruction_part_processor_factory_reg_opcode_encoder, 0 },
	{ fcml_ifn_asm_instruction_part_processor_factory_conditional_opcode_encoder, 0 },
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
    { fcml_ifn_asm_instruction_part_processor_factory_segment_override_prefix_encoder, 0 },
	{ fcml_ifn_asm_instruction_part_processor_factory_66_prefix_encoder, 0 },
	{ fcml_ifn_asm_instruction_part_processor_factory_67_prefix_encoder, 0 },
	{ fcml_ifn_asm_instruction_part_processor_factory_mandatory_prefixes_encoder, 0 },
	{ fcml_ifn_asm_instruction_part_processor_factory_REX_prefix_encoder, 0 },
	{ fcml_ifn_asm_instruction_part_processor_factory_VEX_XOP_prefix_encoder, 0 },
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
	{ fcml_asm_instruction_part_processor_factories_acceptors_IA, FCML_IPCT_ALL, FCML_TRUE },
	{ fcml_asm_instruction_part_processor_factories_prefixes_for_IA, FCML_IPCT_ALL, FCML_TRUE },
	{ fcml_asm_instruction_part_processor_factories_opcode_for_IA, FCML_IPCT_ONE, FCML_TRUE },
	{ fcml_asm_instruction_part_processor_factories_ModRM_for_IA, FCML_IPCT_ALL, FCML_FALSE },
	{ fcml_asm_instruction_part_processor_factories_operands_for_IA, FCML_IPCT_ALL, FCML_FALSE },
	{ NULL }
};

fcml_ifn_asm_instruction_part_processor_chain* fcml_ifn_asm_instruction_part_processor_factory_dispatcher_IA( fcml_st_def_instruction_description *instruction, fcml_st_def_addr_mode_desc *addr_mode, int *parts, fcml_hints *hints, fcml_ceh_error *error ) {
	int instruction_parts = 0;
	fcml_ifn_asm_instruction_part_processor_chain *chain = NULL;
	fcml_ifn_asm_instruction_part_processor_chain *current_chain = NULL;
	fcml_ist_asm_instruction_part_factory_sequence *current_factories_sequence = &fcml_asm_instruction_part_processor_factory_sequences_for_IA[0];
	while( current_factories_sequence->details ) {
		int processor_counter = 0;
		fcml_st_instruction_part_choice_type choice = current_factories_sequence->choice_type;
		fcml_ist_asm_instruction_part_factory_details *current_factory = current_factories_sequence->details;
		while( current_factory->factory ) {
			fcml_ifn_asm_instruction_part_processor_descriptor descriptor = current_factory->factory( current_factory->flags, instruction, addr_mode, hints, error );
			if( descriptor.processor_encoder || descriptor.processor_acceptor ) {

				processor_counter++;

				// TODO: ozna by sie zastanowic jak ukrys ta zmienna przed fabyka deskryptorow.
				descriptor.is_short_form_supported = current_factories_sequence->is_short_form_supported;

				// Check max number of processors.
				if( processor_counter > FCML_ASM_MAX_PART_PROCESSORS ) {
					*error = FCML_CEH_GEC_ILLEGAL_STATE_EXCEPTION;
					if( chain ) {
						fcml_ifn_asm_free_part_processor_chain( chain );
					}
					return NULL;
				}

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

// Precalculates some data using given addressing mode.
fcml_st_asm_addr_mode_desc_details fcml_ifn_asm_precalculate_addr_mode( fcml_st_def_addr_mode_desc *addr_mode_desc ) {

	fcml_st_asm_addr_mode_desc_details details = {0};

	fcml_uint16_t allowed_prefixes = addr_mode_desc->allowed_prefixes;

	fcml_uint32_t opcode_flags = addr_mode_desc->opcode_flags;

	// Calculate OSA and ASA flags.

	fcml_en_attribute_size_flag osa_flags = FCML_EN_ASF_ANY;
	fcml_en_attribute_size_flag asa_flags = FCML_EN_ASF_ANY;

	if( FCML_DEF_PREFIX_W_1( allowed_prefixes ) ) {
		osa_flags |= FCML_EN_ASF_64;
		asa_flags |=  ( FCML_EN_ASF_32 | FCML_EN_ASF_64 );
	}

	if( FCML_DEF_PREFIX_W_0( allowed_prefixes ) ) {
		osa_flags |= ( FCML_EN_ASF_32 | FCML_EN_ASF_16 );
	}

	if( FCML_DEF_OPCODE_FLAGS_IS_EOSA_RESTRICTION( opcode_flags ) ) {
		fcml_en_attribute_size_flag osa_restriction_flags = FCML_EN_ASF_ANY;
		if( FCML_DEF_OPCODE_FLAGS_EOSA_16( opcode_flags ) ) {
			osa_restriction_flags |= FCML_EN_ASF_16;
		}
		if( FCML_DEF_OPCODE_FLAGS_EOSA_32( opcode_flags ) ) {
			osa_restriction_flags |= FCML_EN_ASF_32;
		}
		if( FCML_DEF_OPCODE_FLAGS_EOSA_64( opcode_flags ) ) {
			osa_restriction_flags |= FCML_EN_ASF_64;
		}
		osa_flags = ( osa_flags == FCML_EN_ASF_ANY ) ? osa_restriction_flags : osa_flags & osa_restriction_flags;
	}

	if( FCML_DEF_OPCODE_FLAGS_IS_EASA_RESTRICTION( opcode_flags ) ) {
		fcml_en_attribute_size_flag asa_restriction_flags = FCML_EN_ASF_ANY;
		if( FCML_DEF_OPCODE_FLAGS_EASA_16( opcode_flags ) ) {
			asa_restriction_flags |= FCML_EN_ASF_16;
		}
		if( FCML_DEF_OPCODE_FLAGS_EASA_32( opcode_flags ) ) {
			asa_restriction_flags |= FCML_EN_ASF_32;
		}
		if( FCML_DEF_OPCODE_FLAGS_EASA_64( opcode_flags ) ) {
			asa_restriction_flags |= FCML_EN_ASF_64;
		}
		asa_flags = ( asa_flags == FCML_EN_ASF_ANY ) ? asa_restriction_flags : asa_flags & asa_restriction_flags;
	}

	// Sets calculated values in details.

	details.allowed_asa = asa_flags;
	details.allowed_osa = osa_flags;

	return details;
}

void fcml_ifn_asm_free_addr_mode( fcml_st_asm_instruction_addr_mode_encoding_details *addr_mode, fcml_st_dialect_context *dialect_context ) {
    if( addr_mode ) {
        if( addr_mode->mnemonic ) {
            dialect_context->free_mnemonic( addr_mode->mnemonic );
        }
        fcml_fn_env_memory_free( addr_mode );
    }
}

void fcml_ifn_asm_free_instruction_addr_mode_item_handler( fcml_ptr item_value, fcml_ptr args ) {
    fcml_st_asm_instruction_addr_mode_encoding_details *addr_mode = (fcml_st_asm_instruction_addr_mode_encoding_details*)item_value;
    // Do not free clones.
    if( !addr_mode->is_cloned ) {
        if( addr_mode->part_processor_chain ) {
            fcml_ifn_asm_free_part_processor_chain( addr_mode->part_processor_chain );
        }
    }
    fcml_ifn_asm_free_addr_mode( addr_mode, (fcml_st_dialect_context*)args );
}

void fcml_ifn_asm_free_instruction_entry( fcml_ptr key, fcml_ptr value, fcml_ptr args ) {
    fcml_st_asm_instruction_addr_modes *addr_modes = (fcml_st_asm_instruction_addr_modes*)value;
    if( addr_modes ) {
        if( addr_modes->addr_modes ) {
            fcml_fn_coll_list_free( addr_modes->addr_modes, fcml_ifn_asm_free_instruction_addr_mode_item_handler, args );
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

// ******************************************
// Addressing mode encoding details builders.
// ******************************************

typedef fcml_ceh_error (*fcml_ifn_asm_instruction_addr_mode_encoding_details_handler)( fcml_ist_asm_init_context *init_context, fcml_st_def_instruction_description *instruction, fcml_st_def_addr_mode_desc *addr_mode_desc, fcml_st_asm_instruction_addr_mode_encoding_details *addr_mode );

typedef fcml_ceh_error (*fcml_ifn_asm_addr_mode_encoding_details_builder)( fcml_ist_asm_init_context *init_context, fcml_st_def_instruction_description *instruction, fcml_st_def_addr_mode_desc *addr_mode_desc, fcml_ifn_asm_instruction_addr_mode_encoding_details_handler addr_mode_handler );

fcml_st_condition fcml_itb_instruction_conditions[] = {
};

fcml_ceh_error fcml_ifn_asm_conditional_instruction_addr_mode_encoding_details_builder( fcml_ist_asm_init_context *init_context, fcml_st_def_instruction_description *instruction, fcml_st_def_addr_mode_desc *addr_mode_desc, fcml_ifn_asm_instruction_addr_mode_encoding_details_handler addr_mode_handler ) {

    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

    int i;
    for( i = 0; i < FCML_NUMBER_OF_CONDITIONS * 2 && !error; i++ ) {

        fcml_st_asm_instruction_addr_mode_encoding_details *addr_mode = (fcml_st_asm_instruction_addr_mode_encoding_details *)fcml_fn_env_clear_memory_alloc( sizeof( fcml_st_asm_instruction_addr_mode_encoding_details ) );
        if( !addr_mode ) {
            return FCML_CEH_GEC_OUT_OF_MEMORY;
        }

        addr_mode->addr_mode_desc = addr_mode_desc;
        addr_mode->addr_mode_details = fcml_ifn_asm_precalculate_addr_mode( addr_mode_desc );

        fcml_st_asm_addr_mode_desc_details *addr_mode_details = &(addr_mode->addr_mode_details);
        addr_mode_details->is_conditional = FCML_TRUE;
        addr_mode_details->condition.is_negation = ( i % 2 == 1 );
        addr_mode_details->condition.condition_type = i / 2;

        int instruction_parts;

        fcml_ifn_asm_instruction_part_processor_factory_dispatcher factory_dispatcher = fcml_ifn_get_instruction_part_processor_factory_dispatcher_for_instruction_type( instruction->instruction_type );

        addr_mode->part_processor_chain = factory_dispatcher( instruction, addr_mode_desc, &instruction_parts, &(addr_mode->hints), &error );
        if( !error ) {
            addr_mode->instruction_parts = instruction_parts;
            error = addr_mode_handler( init_context, instruction, addr_mode_desc, addr_mode );
            if( error ) {
                fcml_ifn_asm_free_part_processor_chain( addr_mode->part_processor_chain );
                fcml_fn_env_memory_free(addr_mode);
            }
        } else {
            fcml_fn_env_memory_free(addr_mode);
        }

    }

    return error;
}

fcml_ceh_error fcml_ifn_asm_default_addr_mode_encoding_details_builder( fcml_ist_asm_init_context *init_context, fcml_st_def_instruction_description *instruction, fcml_st_def_addr_mode_desc *addr_mode_desc, fcml_ifn_asm_instruction_addr_mode_encoding_details_handler addr_mode_handler ) {

    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

	fcml_st_asm_instruction_addr_mode_encoding_details *addr_mode = (fcml_st_asm_instruction_addr_mode_encoding_details *)fcml_fn_env_clear_memory_alloc( sizeof( fcml_st_asm_instruction_addr_mode_encoding_details ) );
	if( !addr_mode ) {
		return FCML_CEH_GEC_OUT_OF_MEMORY;
	}

	addr_mode->addr_mode_desc = addr_mode_desc;
	addr_mode->addr_mode_details = fcml_ifn_asm_precalculate_addr_mode( addr_mode_desc );

	int instruction_parts;

	fcml_ifn_asm_instruction_part_processor_factory_dispatcher factory_dispatcher = fcml_ifn_get_instruction_part_processor_factory_dispatcher_for_instruction_type( instruction->instruction_type );

	addr_mode->part_processor_chain = factory_dispatcher( instruction, addr_mode_desc, &instruction_parts, &(addr_mode->hints), &error );
	if( !error ) {
	    addr_mode->instruction_parts = instruction_parts;
        error = addr_mode_handler( init_context, instruction, addr_mode_desc, addr_mode );
        if( error ) {
            // In case of errors from handler, this function is responsible for freeing addressing mode.
            fcml_ifn_asm_free_part_processor_chain( addr_mode->part_processor_chain );
            fcml_fn_env_memory_free(addr_mode);
        }
	} else {
        fcml_fn_env_memory_free(addr_mode);
	}

	return error;
}

fcml_ifn_asm_addr_mode_encoding_details_builder fcml_ifn_asm_conditional_instruction_addr_mode_encoding_details_builder_factory( fcml_st_def_addr_mode_desc *addr_mode_desc ) {
    if( FCML_DEF_OPCODE_FLAGS_OPCODE_FIELD_TTTN( addr_mode_desc->opcode_flags ) ) {
        return &fcml_ifn_asm_conditional_instruction_addr_mode_encoding_details_builder;
    }
    return &fcml_ifn_asm_default_addr_mode_encoding_details_builder;
}

// ******************************************
// Addressing mode encoding details handlers.
// ******************************************

//void fcml_fn_asm_

fcml_ceh_error fcml_ifn_asm_encoded_handle_instruction_addr_mode_decoding( fcml_ist_asm_init_context *init_context, fcml_st_def_instruction_description *instruction, fcml_st_def_addr_mode_desc *addr_mode_desc, fcml_st_asm_instruction_addr_mode_encoding_details *addr_mode ) {

    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

    // Space for mnemonics.
    fcml_st_mp_mnemonic *mnemonics[FCML_ASM_DIALECT_MAX_MNEMONIC_COUNT];

    // Instruction can be registered for more than one mnemonic.
    int mnemonic_count = 0;
    error = init_context->assembler->dialect_context.get_mnemonic( instruction, addr_mode_desc, addr_mode->addr_mode_details.is_conditional ? &(addr_mode->addr_mode_details.condition) : NULL, mnemonics, &mnemonic_count );
    if( error ) {
        return error;
    }

    // Prepare addressing mode encoders for every mnemonic.
    int i;
    for( i = 0; i < mnemonic_count && !error; i++ ) {

        fcml_st_asm_instruction_addr_modes *addr_modes = (fcml_st_asm_instruction_addr_modes*)fcml_fn_coll_map_get( init_context->assembler->instructions_map, mnemonics[i]->mnemonic );
        if( !addr_modes ) {

            // Allocate space for new mnemonic.
            addr_modes = fcml_fn_env_memory_alloc( sizeof(fcml_st_asm_instruction_addr_modes) );
            if( addr_modes ) {

                // Allocate list for addressing modes.
                addr_modes->addr_modes = fcml_fn_coll_list_alloc();
                if( addr_modes->addr_modes ) {
                    // Do not care about freeing this piece of memory. Procedure responsible for freeing adressing mode is responsible for it.
                    addr_modes->mnemonic = mnemonics[i]->mnemonic;
                    addr_modes->instruction_encoder = fcml_ifn_asm_choose_instruction_encoder( instruction->instruction_type );

                    // Puts prepared structure under mnemonic key.
                    fcml_fn_coll_map_put( init_context->assembler->instructions_map, mnemonics[i]->mnemonic, addr_modes, &error );
                    if( error ) {
                        fcml_fn_coll_list_free( addr_modes->addr_modes, fcml_ifn_asm_free_instruction_addr_mode_item_handler, &(init_context->assembler->dialect_context) );
                        fcml_fn_env_memory_free(addr_modes);
                    }

                } else {
                    fcml_fn_env_memory_free(addr_modes);
                    error = FCML_CEH_GEC_OUT_OF_MEMORY;
                }

            } else {
                // Out of memory.
                error = FCML_CEH_GEC_OUT_OF_MEMORY;
            }
        }

        if( !error ) {

            fcml_bool is_cloned = ( i > 0 );

            fcml_st_asm_instruction_addr_mode_encoding_details *addr_mode_encoding_details = addr_mode;

            if( is_cloned ) {

                // Clone encoding details for secondary mnemonics.
                fcml_st_asm_instruction_addr_mode_encoding_details *clone_addr_mode_enc_details = fcml_fn_env_clear_memory_alloc( sizeof( fcml_st_asm_instruction_addr_mode_encoding_details ) );
                if( clone_addr_mode_enc_details ) {
                    *clone_addr_mode_enc_details = *addr_mode_encoding_details;
                    clone_addr_mode_enc_details->is_cloned = FCML_TRUE;
                    addr_mode_encoding_details = clone_addr_mode_enc_details;
                } else {
                    error = FCML_CEH_GEC_OUT_OF_MEMORY;
                }

            }

            // Every addressing mode has its own mnemonic configuration, it doesn't matter if it is cloned addressing mode or not
            // it is responsible for deallocating it.
            addr_mode_encoding_details->mnemonic = mnemonics[i];

            if( !error && !fcml_fn_coll_list_add_back( addr_modes->addr_modes, addr_mode_encoding_details ) ) {
                // Free holder allocated earlier.
                if( is_cloned ) {
                    fcml_fn_env_memory_free( addr_mode_encoding_details );
                }
                error = FCML_CEH_GEC_OUT_OF_MEMORY;
            }

        }

        if( error ) {
            // In case of error free all mnemonics which haven't been added to the addressing mode list.
            for( ; i < mnemonic_count; i++ ) {
               fcml_fn_asm_dialect_free_mnemonic( mnemonics[i] );
           }
        }

    }

    return error;
}

// ****************************************
// Addressing mode encoders initialization.
// ****************************************

void fcml_ifn_asm_prepare_instruction_encoding_details( fcml_ist_asm_init_context *init_context, fcml_st_def_instruction_description *instruction, fcml_ceh_error *error ) {

    // Prepare encoders for given instruction.
    int i;
    for( i = 0; i < instruction->opcode_desc_count; i++ ) {

        fcml_st_def_addr_mode_desc *addr_mode_desc = &(instruction->addr_modes[i]);

        fcml_ifn_asm_addr_mode_encoding_details_builder encoding_details_builder = fcml_ifn_asm_conditional_instruction_addr_mode_encoding_details_builder_factory( addr_mode_desc );

        // Prepare encoders for given addressing mode.
        *error = encoding_details_builder( init_context, instruction, addr_mode_desc, &fcml_ifn_asm_encoded_handle_instruction_addr_mode_decoding );
        if( *error ) {
            break;
        }

        addr_mode_desc++;
    }
}

fcml_ceh_error fcml_fn_asm_init_instruction_encodings( fcml_st_dialect_context *dialect_context, fcml_st_assembler **assembler ) {

	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

	// Allocate assembler instance.
	*assembler = fcml_fn_env_clear_memory_alloc( sizeof( fcml_ist_asm_enc_assembler ) );
	if( !*assembler ) {
	    return FCML_CEH_GEC_OUT_OF_MEMORY;
	}

	fcml_ist_asm_enc_assembler *enc_asm = (fcml_ist_asm_enc_assembler*)*assembler;

	enc_asm->dialect_context = *dialect_context;

	// Allocate map for all instructions.
	fcml_st_coll_map_descriptor inst_map_desc = fcml_coll_map_descriptor_string;
	inst_map_desc.entry_free_function = fcml_ifn_asm_free_instruction_entry;
	inst_map_desc.entry_free_args = &(enc_asm->dialect_context);

	enc_asm->instructions_map = fcml_fn_coll_map_alloc( &inst_map_desc, 64, &error );
	if( !(enc_asm->instructions_map) ) {
	    fcml_fn_asm_free_instruction_encodings( *assembler );
		return error;
	}

	fcml_ist_asm_init_context init_context;
	init_context.assembler = enc_asm;

	int i = 0;
	fcml_st_def_instruction_description *instruction = &(fcml_ext_instructions_def[i++]);
	while( instruction->mnemonic && !error ) {
	    fcml_ifn_asm_prepare_instruction_encoding_details( &init_context, instruction, &error );
		instruction = &(fcml_ext_instructions_def[i++]);
	}

	if( error ) {
		// Something failed, so free everything that have been properly allocated.
		fcml_fn_asm_free_instruction_encodings( *assembler );
	}

	return error;

}

void fcml_fn_asm_free_instruction_encodings( fcml_st_assembler *assembler ) {

    fcml_ist_asm_enc_assembler *enc_asm = (fcml_ist_asm_enc_assembler*)assembler;

    if( enc_asm ) {

        if( enc_asm->instructions_map ) {
            fcml_fn_coll_map_free( enc_asm->instructions_map );
            enc_asm->instructions_map = NULL;
        }

        fcml_fn_env_memory_free( enc_asm );
    }
}

fcml_ceh_error fcml_fn_asm_get_instruction_encodings( fcml_st_assembler *assembler, fcml_string mnemonic, fcml_st_asm_instruction_addr_modes **addr_modes ) {

    fcml_ist_asm_enc_assembler *enc_asm = (fcml_ist_asm_enc_assembler*)assembler;

	if( !(enc_asm->instructions_map) ) {
		return FCML_CEH_GEC_NOT_INITIALIZED;
	}

	*addr_modes = (fcml_st_asm_instruction_addr_modes*)fcml_fn_coll_map_get( enc_asm->instructions_map, mnemonic );
	if( !*addr_modes ) {
		return FCML_EN_UNKNOWN_MNEMONIC;
	}

	return FCML_CEH_GEC_NO_ERROR;
}

