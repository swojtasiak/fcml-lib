/*
 * fcml_utils.c
 *
 *  Created on: 23-05-2013
 *      Author: tAs
 */

#include "fcml_utils.h"
#include "fcml_types.h"

fcml_ceh_error fcml_fn_utils_int64_to_integer( fcml_uint64_t src, fcml_bool is_src_signed, fcml_st_integer *integer, fcml_en_utils_size_flags filter ) {
    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
    if( is_src_signed ) {
        // Optimized for 32 bit processors.
        if( ( src & 0xFFFFFFFF80000000UL ) == 0xFFFFFFFF80000000UL || ( src & 0xFFFFFFFF00000000UL ) == 0x0000000000000000UL ) {
            fcml_int32_t s_imm = (fcml_int32_t)src;
            if( ( filter & FCML_ENUSF_8 ) && ( ( s_imm & 0xFFFFFF80 ) == 0xFFFFFF80 || ( s_imm & 0xFFFFFF00 ) == 0x00000000 ) ) {
                integer->int8 = (fcml_int8_t)s_imm;
                integer->size = FCML_DS_8;
            } else if( ( filter & FCML_ENUSF_16 ) && ( ( s_imm & 0xFFFF8000 ) == 0xFFFF8000 || ( s_imm & 0xFFFF0000 ) == 0x00000000 ) ) {
                integer->int16 = (fcml_int16_t)s_imm;
                integer->size = FCML_DS_16;
            } else if ( filter & FCML_ENUSF_32 ) {
                integer->int32 = (fcml_int32_t)s_imm;
                integer->size = FCML_DS_32;
            } else {
                error = FCML_CEH_GEC_VALUE_OUT_OF_RANGE;
            }
        } else {
            if( filter & FCML_ENUSF_64 ) {
                integer->int64 = src;
                integer->size = FCML_DS_64;
            } else {
                error = FCML_CEH_GEC_VALUE_OUT_OF_RANGE;
            }
        }
    } else {
        if( ( filter & FCML_ENUSF_8 ) && ( src <= FCML_UINT8_MAX ) ) {
            integer->int8 = (fcml_uint8_t)src;
            integer->size = FCML_DS_8;
        } else if( ( filter & FCML_ENUSF_16 ) && ( src <= FCML_UINT16_MAX ) ) {
            integer->int16 = (fcml_uint16_t)src;
            integer->size = FCML_DS_16;
        } else if( ( filter & FCML_ENUSF_32 ) && ( src <= FCML_UINT32_MAX ) ) {
            integer->int32 = (fcml_uint32_t)src;
            integer->size = FCML_DS_32;
        } else if( filter & FCML_ENUSF_64 ) {
            integer->int64 = src;
            integer->size = FCML_DS_64;
        } else {
            error = FCML_CEH_GEC_VALUE_OUT_OF_RANGE;
        }
    }
    integer->is_signed = is_src_signed;
    return error;
}

fcml_ceh_error fcml_fn_utils_convert_integer_to_integer( const fcml_st_integer *source, fcml_st_integer *destination, fcml_data_size expected_source_size, fcml_data_size destination_size ) {

	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

	// Convert given source immediate value to expected one.

	fcml_st_integer expected = {0};

	expected.size = expected_source_size;
	expected.is_signed = source->is_signed;

	if( source->size != expected_source_size ) {
		switch( expected_source_size ) {
		case FCML_DS_8:
			error = fcml_fn_utils_convert_integer_to_int8( source, &(expected.int8) );
			break;
		case FCML_DS_16:
			error = fcml_fn_utils_convert_integer_to_int16( source, &(expected.int16) );
			break;
		case FCML_DS_32:
			error = fcml_fn_utils_convert_integer_to_int32( source, &(expected.int32) );
			break;
		case FCML_DS_64:
			error = fcml_fn_utils_convert_integer_to_int64( source, &(expected.int64) );
			break;
		}
	} else {
		expected = *source;
	}

	if( !error ) {

		// Convert expected value to destination one.

		switch( destination_size ) {
			case FCML_DS_8:
				error = fcml_fn_utils_convert_integer_to_int8( &expected, &(destination->int8) );
				break;
			case FCML_DS_16:
				error = fcml_fn_utils_convert_integer_to_int16( &expected, &(destination->int16) );
				break;
			case FCML_DS_32:
				error = fcml_fn_utils_convert_integer_to_int32( &expected, &(destination->int32) );
				break;
			case FCML_DS_64:
				error = fcml_fn_utils_convert_integer_to_int64( &expected, &(destination->int64) );
				break;
		}

		destination->size = destination_size;
		destination->is_signed = expected.is_signed;

	}

	return error;
}

fcml_ceh_error fcml_fn_utils_convert_integer_to_uint8( fcml_st_integer *integer, fcml_uint8_t *value ) {
	switch( integer->size ) {
	case FCML_DS_8:
		// In this case we doesn't care what is in IMM, because no conversion is needed.
		*value = integer->int8;
		break;
	case FCML_DS_16:
		if( integer->is_signed ) {
			if( integer->int16 > FCML_UINT8_MAX || integer->int16 < 0 ) {
				return FCML_CEH_GEC_VALUE_OUT_OF_RANGE;
			}
			*value = (fcml_uint8_t)(fcml_int16_t)integer->int16;
		} else {
			if( (fcml_uint16_t)integer->int16 > FCML_UINT8_MAX ) {
				return FCML_CEH_GEC_VALUE_OUT_OF_RANGE;
			}
			*value = (fcml_uint8_t)integer->int16;
		}
		break;
	case FCML_DS_32:
		if( integer->is_signed ) {
			if( integer->int32 > FCML_UINT8_MAX || integer->int32 < 0 ) {
				return FCML_CEH_GEC_VALUE_OUT_OF_RANGE;
			}
			*value = (fcml_uint8_t)(fcml_int32_t)integer->int32;
		} else {
			if( (fcml_uint32_t)integer->int32 > FCML_UINT8_MAX ) {
				return FCML_CEH_GEC_VALUE_OUT_OF_RANGE;
			}
			*value = (fcml_uint8_t)integer->int32;
		}
		break;
	case FCML_DS_64:
		if( integer->is_signed ) {
			if( integer->int64 > FCML_UINT8_MAX || integer->int64 < 0 ) {
				return FCML_CEH_GEC_VALUE_OUT_OF_RANGE;
			}
			*value = (fcml_uint8_t)(fcml_int64_t)integer->int64;
		} else {
			if( (fcml_uint64_t)integer->int64 > FCML_UINT8_MAX ) {
				return FCML_CEH_GEC_VALUE_OUT_OF_RANGE;
			}
			*value = (fcml_uint8_t)integer->int64;
		}
		break;
	default:
		return FCML_CEH_GEC_VALUE_OUT_OF_RANGE;
	}
	return FCML_CEH_GEC_NO_ERROR;
}

fcml_ceh_error fcml_fn_utils_convert_integer_to_uint16( fcml_st_integer *integer, fcml_uint16_t *value ) {
	switch( integer->size ) {
	case FCML_DS_8:
	    if( integer->is_signed ) {
	        *value = (fcml_uint16_t)integer->int8;
	    } else {
	        *value = (fcml_uint16_t)(fcml_uint8_t)integer->int8;
	    }
		break;
	case FCML_DS_16:
		*value = (fcml_uint16_t)integer->int16;
		break;
	case FCML_DS_32:
		if( integer->is_signed ) {
			if( integer->int32 > FCML_UINT16_MAX || integer->int32 < 0 ) {
				return FCML_CEH_GEC_VALUE_OUT_OF_RANGE;
			}
			*value = (fcml_uint16_t)integer->int32;
		} else {
			if( (fcml_uint32_t)integer->int32 > FCML_UINT16_MAX ) {
				return FCML_CEH_GEC_VALUE_OUT_OF_RANGE;
			}
			*value = (fcml_uint16_t)integer->int32;
		}
		break;
	case FCML_DS_64:
		if( integer->is_signed ) {
			if( integer->int64 > FCML_UINT16_MAX || integer->int64 < 0 ) {
				return FCML_CEH_GEC_VALUE_OUT_OF_RANGE;
			}
			*value = (fcml_uint16_t)integer->int64;
		} else {
			if( (fcml_uint64_t)integer->int64 > FCML_UINT16_MAX ) {
				return FCML_CEH_GEC_VALUE_OUT_OF_RANGE;
			}
			*value = (fcml_uint16_t)integer->int64;
		}
		break;
	default:
		return FCML_CEH_GEC_VALUE_OUT_OF_RANGE;
	}
	return FCML_CEH_GEC_NO_ERROR;
}

fcml_ceh_error fcml_fn_utils_convert_integer_to_uint32( fcml_st_integer *integer, fcml_uint32_t *value ) {
	switch( integer->size ) {
	case FCML_DS_8:
		if( integer->is_signed ) {
            *value = (fcml_uint32_t)integer->int8;
        } else {
            *value = (fcml_uint32_t)(fcml_uint8_t)integer->int8;
        }
		break;
	case FCML_DS_16:
		if( integer->is_signed ) {
            *value = (fcml_uint32_t)integer->int16;
        } else {
            *value = (fcml_uint32_t)(fcml_uint16_t)integer->int16;
        }
		break;
	case FCML_DS_32:
		*value = (fcml_uint32_t)integer->int32;
		break;
	case FCML_DS_64:
		if( integer->is_signed ) {
			if( integer->int64 > FCML_UINT32_MAX || integer->int64 < 0 ) {
				return FCML_CEH_GEC_VALUE_OUT_OF_RANGE;
			}
			*value = (fcml_uint32_t)integer->int16;
		} else {
			if( (fcml_uint64_t)integer->int64 > FCML_UINT32_MAX ) {
				return FCML_CEH_GEC_VALUE_OUT_OF_RANGE;
			}
			*value = (fcml_uint32_t)integer->int64;
		}
		break;
	default:
		return FCML_CEH_GEC_VALUE_OUT_OF_RANGE;
	}
	return FCML_CEH_GEC_NO_ERROR;
}

fcml_ceh_error fcml_fn_utils_convert_integer_to_uint64( fcml_st_integer *integer, fcml_uint64_t *value ) {
	switch( integer->size ) {
	case FCML_DS_8:
		if( integer->is_signed ) {
            *value = (fcml_uint64_t)integer->int8;
        } else {
            *value = (fcml_uint64_t)(fcml_uint8_t)integer->int8;
        }
		break;
	case FCML_DS_16:
		if( integer->is_signed ) {
            *value = (fcml_uint64_t)integer->int16;
        } else {
            *value = (fcml_uint64_t)(fcml_uint16_t)integer->int16;
        }
		break;
	case FCML_DS_32:
		if( integer->is_signed ) {
            *value = (fcml_uint64_t)integer->int32;
        } else {
            *value = (fcml_uint64_t)(fcml_uint32_t)integer->int32;
        }
		break;
	case FCML_DS_64:
		*value = (fcml_uint64_t)integer->int64;
		break;
	default:
		return FCML_CEH_GEC_VALUE_OUT_OF_RANGE;
	}
	return FCML_CEH_GEC_NO_ERROR;
}

fcml_ceh_error fcml_fn_utils_convert_integer_to_int8( const fcml_st_integer *integer, fcml_int8_t *value ) {
	switch( integer->size ) {
	case FCML_DS_8:
		*value = (fcml_int8_t)integer->int8;
		break;
	case FCML_DS_16:
		if( integer->is_signed ) {
			if( integer->int16 < FCML_INT8_MIN || integer->int16 > FCML_INT8_MAX ) {
				return FCML_CEH_GEC_VALUE_OUT_OF_RANGE;
			}
			*value = (fcml_int8_t)integer->int16;
		} else {
			if( (fcml_uint16_t)integer->int16 > FCML_UINT8_MAX ) {
				return FCML_CEH_GEC_VALUE_OUT_OF_RANGE;
			}
			*value = (fcml_int8_t)(fcml_uint16_t)integer->int16;
		}
		break;
	case FCML_DS_32:
		if( integer->is_signed ) {
			if( integer->int32 < FCML_INT8_MIN || integer->int32 > FCML_INT8_MAX ) {
				return FCML_CEH_GEC_VALUE_OUT_OF_RANGE;
			}
			*value = (fcml_int8_t)integer->int32;
		} else {
			if( (fcml_uint32_t)integer->int32 > FCML_INT8_MAX ) {
				return FCML_CEH_GEC_VALUE_OUT_OF_RANGE;
			}
			*value = (fcml_int8_t)(fcml_uint32_t)integer->int32;
		}
		break;
	case FCML_DS_64:
		if( integer->is_signed ) {
			if( (fcml_int64_t)integer->int64 < FCML_INT8_MIN || (fcml_int64_t)integer->int64 > FCML_INT8_MAX ) {
				return FCML_CEH_GEC_VALUE_OUT_OF_RANGE;
			}
			*value = (fcml_int8_t)integer->int64;
		} else {
			if( (fcml_uint64_t)integer->int64 > FCML_INT8_MAX ) {
				return FCML_CEH_GEC_VALUE_OUT_OF_RANGE;
			}
			*value = (fcml_int8_t)(fcml_uint64_t)integer->int64;
		}
		break;
	default:
		return FCML_CEH_GEC_VALUE_OUT_OF_RANGE;
	}
	return FCML_CEH_GEC_NO_ERROR;
}

fcml_ceh_error fcml_fn_utils_convert_integer_to_int16( const fcml_st_integer *integer, fcml_int16_t *value ) {
	switch( integer->size ) {
	case FCML_DS_8:
		*value = integer->is_signed ? (fcml_int16_t)integer->int8 : (fcml_int16_t)(fcml_uint8_t)integer->int8;
		break;
	case FCML_DS_16:
		*value = integer->int16;
		break;
	case FCML_DS_32:
		if( integer->is_signed ) {
			if( integer->int32 < FCML_INT16_MIN || integer->int32 > FCML_INT16_MAX ) {
				return FCML_CEH_GEC_VALUE_OUT_OF_RANGE;
			}
			*value = (fcml_int16_t)integer->int32;
		} else {
			if( (fcml_uint32_t)integer->int32 > FCML_INT16_MAX ) {
				return FCML_CEH_GEC_VALUE_OUT_OF_RANGE;
			}
			*value = (fcml_int16_t)(fcml_uint32_t)integer->int32;
		}
		break;
	case FCML_DS_64:
		if( integer->is_signed ) {
			if( integer->int64 < FCML_INT16_MIN || integer->int64 > FCML_INT16_MAX ) {
				return FCML_CEH_GEC_VALUE_OUT_OF_RANGE;
			}
			*value = (fcml_int16_t)integer->int64;
		} else {
			if( (fcml_uint64_t)integer->int64 > FCML_INT16_MAX ) {
				return FCML_CEH_GEC_VALUE_OUT_OF_RANGE;
			}
			*value = (fcml_int16_t)(fcml_uint64_t)integer->int64;
		}
		break;
	default:
		return FCML_CEH_GEC_VALUE_OUT_OF_RANGE;
	}
	return FCML_CEH_GEC_NO_ERROR;
}

fcml_ceh_error fcml_fn_utils_convert_integer_to_int32( const fcml_st_integer *integer, fcml_int32_t *value ) {
	switch( integer->size ) {
	case FCML_DS_8:
		*value = integer->is_signed ? (fcml_int32_t)integer->int8 : (fcml_int32_t)(fcml_uint8_t)integer->int8;
		break;
	case FCML_DS_16:
		*value = integer->is_signed ? (fcml_int32_t)integer->int16 : (fcml_int32_t)(fcml_uint16_t)integer->int16;
		break;
	case FCML_DS_32:
		*value = integer->int32;
		break;
	case FCML_DS_64:
		if( integer->is_signed ) {
			if( integer->int64 < FCML_INT32_MIN || integer->int64 > FCML_INT32_MAX ) {
				return FCML_CEH_GEC_VALUE_OUT_OF_RANGE;
			}
			*value = (fcml_int32_t)integer->int64;
		} else {
			if( (fcml_uint64_t)integer->int64 > FCML_INT32_MAX ) {
				return FCML_CEH_GEC_VALUE_OUT_OF_RANGE;
			}
			*value = (fcml_int32_t)(fcml_uint64_t)integer->int64;
		}
		break;
	default:
		return FCML_CEH_GEC_VALUE_OUT_OF_RANGE;
	}
	return FCML_CEH_GEC_NO_ERROR;
}

fcml_ceh_error fcml_fn_utils_convert_integer_to_int64( const fcml_st_integer *integer, fcml_int64_t *value ) {
	switch( integer->size ) {
	case FCML_DS_8:
		*value = integer->is_signed ? (fcml_int64_t)integer->int8 : (fcml_int64_t)(fcml_uint8_t)integer->int8;
		break;
	case FCML_DS_16:
		*value = integer->is_signed ? (fcml_int64_t)integer->int16 : (fcml_int64_t)(fcml_uint16_t)integer->int16;
		break;
	case FCML_DS_32:
		*value = integer->is_signed ? (fcml_int64_t)integer->int32 : (fcml_int64_t)(fcml_uint32_t)integer->int32;
		break;
	case FCML_DS_64:
		*value = integer->int64;
		break;
	default:
		return FCML_CEH_GEC_VALUE_OUT_OF_RANGE;
	}
	return FCML_CEH_GEC_NO_ERROR;
}

fcml_data_size fcml_fn_utils_get_default_ASA(fcml_en_addr_form addr_form) {
	fcml_data_size result = 0;
	if (addr_form) {
		switch (addr_form) {
		case FCML_AF_16_BIT:
			result = FCML_DS_16;
			break;
		case FCML_AF_32_BIT:
			result = FCML_DS_32;
			break;
		case FCML_AF_64_BIT:
			result = FCML_DS_64;
			break;

		}
	}
	return result;
}

fcml_data_size fcml_fn_utils_get_default_OSA(fcml_en_addr_form addr_form) {
	fcml_data_size result = 0;
	switch (addr_form) {
	case FCML_AF_16_BIT:
		result = FCML_DS_16;
		break;
	case FCML_AF_32_BIT:
		result = FCML_DS_32;
		break;
	case FCML_AF_64_BIT:
		result = FCML_DS_32;
		break;
	}
	return result;
}

fcml_ceh_error fcml_fn_utils_decode_integer( fcml_st_memory_stream *stream, fcml_st_integer *integer, fcml_usize size ) {
	fcml_bool result = FCML_FALSE;
	switch(size) {
	case FCML_DS_8:
	    integer->int8 = fcml_fn_stream_read( stream, &result );
	    integer->size = FCML_DS_8;
		break;
	case FCML_DS_16:
	    integer->int16 = fcml_fn_stream_read_word( stream, &result );
	    integer->size = FCML_DS_16;
		break;
	case FCML_DS_32:
	    integer->int32 = fcml_fn_stream_read_dword( stream, &result );
	    integer->size = FCML_DS_32;
		break;
	case FCML_DS_64:
	    integer->int64 = fcml_fn_stream_read_qword( stream, &result );
	    integer->size = FCML_DS_64;
		break;
	default:
		return FCML_CEH_GEC_INVALID_INPUT;
	}
	if( !result ) {
		return FCML_CEH_GEC_EOF;
	}
	return FCML_CEH_GEC_NO_ERROR;
}


fcml_ceh_error fcml_fn_utils_encode_integer( fcml_st_memory_stream *stream, const fcml_st_integer *integer ) {
    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
    fcml_bool result = FCML_FALSE;
    switch( integer->size ) {
    case FCML_DS_8:
        result = fcml_fn_stream_write( stream, integer->int8 );
        break;
    case FCML_DS_16:
        result = fcml_fn_stream_write_word( stream, integer->int16 );
        break;
    case FCML_DS_32:
        result = fcml_fn_stream_write_dword( stream, integer->int32 );
        break;
    case FCML_DS_64:
        result = fcml_fn_stream_write_qword( stream, integer->int64 );
        break;
    }
    if( !result ) {
        // Insufficient stream size.
        error = FCML_CEH_GEC_INVALID_INPUT;
    }
    return error;
}

fcml_ceh_error fcml_fn_utils_displacement_to_integer( const fcml_st_displacement *displacement, fcml_st_integer *integer ) {
	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
	integer->int64 = 0;
	switch( displacement->size ) {
	case FCML_DS_8:
	    integer->int8 = displacement->dis8;
		break;
	case FCML_DS_16:
	    integer->int16 = displacement->dis16;
		break;
	case FCML_DS_32:
	    integer->int32 = displacement->dis32;
		break;
	case FCML_DS_64:
        integer->int64 = displacement->dis64;
        break;
	default:
		error = FCML_CEH_GEC_INVALID_INPUT;
		break;
	}
	integer->size = displacement->size;
	integer->is_signed = displacement->is_signed;
	return error;
}

fcml_ceh_error fcml_fn_utils_integer_to_displacement( const fcml_st_integer *integer, fcml_st_displacement *displacement ) {
	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
	displacement->dis64 = 0;
	switch( integer->size ) {
	case FCML_DS_8:
		displacement->dis8 = integer->int8;
		break;
	case FCML_DS_16:
		displacement->dis16 = integer->int16;
		break;
	case FCML_DS_32:
		displacement->dis32 = integer->int32;
		break;
	case FCML_DS_64:
		displacement->dis64 = integer->int64;
		break;
	default:
		error = FCML_CEH_GEC_INVALID_INPUT;
		break;
	}
	displacement->size = integer->size;
	displacement->is_signed = integer->is_signed;
	return error;
}

fcml_ceh_error fcml_fn_utils_offset_to_integer( const fcml_st_offset *offset, fcml_st_integer *integer ) {
   fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
   integer->int64 = 0;
   switch( offset->size ) {
   case FCML_DS_16:
       integer->int16 = offset->off16;
       integer->size = FCML_DS_16;
       break;
   case FCML_DS_32:
       integer->int32 = offset->off32;
       integer->size = FCML_DS_32;
       break;
   case FCML_DS_64:
       integer->int64 = offset->off64;
       integer->size = FCML_DS_64;
       break;
   default:
       error = FCML_CEH_GEC_INVALID_INPUT;
       break;
   }
   integer->is_signed = offset->is_signed;
   return error;
}

fcml_ceh_error fcml_fn_utils_integer_to_offset( const fcml_st_integer *integer, fcml_st_offset *offset ) {
    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
    offset->off64 = 0;
    switch( integer->size ) {
    case FCML_DS_8:
        offset->off16 = (fcml_uint16_t)integer->int8;
        offset->size = FCML_DS_16;
        break;
    case FCML_DS_16:
        offset->off16 = (fcml_uint16_t)integer->int16;
        offset->size = FCML_DS_16;
        break;
    case FCML_DS_32:
        offset->off32 = (fcml_uint32_t)integer->int32;
        offset->size = FCML_DS_32;
        break;
    case FCML_DS_64:
        offset->off64 = (fcml_uint64_t)integer->int64;
        offset->size = FCML_DS_64;
        break;
    default:
        error = FCML_CEH_GEC_INVALID_INPUT;
        break;
    }
    offset->is_signed = integer->is_signed;
    return error;
}

fcml_ceh_error fcml_fn_utils_imm_to_integer( fcml_st_immediate *imm, fcml_st_integer *integer ) {
	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
	integer->int64 = 0;
	switch( imm->imm_size ) {
	case FCML_DS_8:
	    integer->int8 = imm->imm8;
		break;
	case FCML_DS_16:
	    integer->int16 = imm->imm16;
		break;
	case FCML_DS_32:
	    integer->int32 = imm->imm32;
		break;
	case FCML_DS_64:
	    integer->int64 = imm->imm64;
		break;
	default:
		error = FCML_CEH_GEC_INVALID_INPUT;
		break;
	}
	integer->size = imm->imm_size;
	integer->is_signed = imm->is_signed;
	return error;
}

fcml_ceh_error fcml_fn_utils_extend_integer( fcml_st_integer *integer, fcml_usize extension ) {
	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
	if( !integer->is_signed ) {
        uint64_t temp_int = 0;
        switch( integer->size ) {
        case 8:
            temp_int = (fcml_uint8_t)integer->int8;
            break;
        case 16:
            temp_int = (fcml_uint16_t)integer->int16;
            break;
        case 32:
            temp_int = (fcml_uint32_t)integer->int32;
            break;
        case 64:
            temp_int = (fcml_uint64_t)integer->int64;
            break;
        default:
            error = FCML_CEH_GEC_INVALID_INPUT;
            break;
        }
        if( !error ) {
            integer->int64 = 0;
            switch( extension ) {
            case 8:
                integer->int8 = (fcml_uint8_t)temp_int;
                break;
            case 16:
                integer->int16 = (fcml_uint16_t)temp_int;
                break;
            case 32:
                integer->int32 = (fcml_uint32_t)temp_int;
                break;
            case 64:
                integer->int64 = (fcml_uint64_t)temp_int;
                break;
            }
            integer->size = extension;
        }
	} else {
	    int64_t temp_int = 0;
        switch( integer->size ) {
        case 8:
            temp_int = integer->int8;
            break;
        case 16:
            temp_int = integer->int16;
            break;
        case 32:
            temp_int = integer->int32;
            break;
        case 64:
            temp_int = integer->int64;
            break;
        default:
            error = FCML_CEH_GEC_INVALID_INPUT;
            break;
        }
        if( !error ) {
            integer->int64 = 0;
            switch( extension ) {
            case 8:
                integer->int8 = (fcml_int8_t)temp_int;
                break;
            case 16:
                integer->int16 = (fcml_int16_t)temp_int;
                break;
            case 32:
                integer->int32 = (fcml_int32_t)temp_int;
                break;
            case 64:
                integer->int64 = (fcml_int64_t)temp_int;
                break;
            }
            integer->size = extension;
        }
        return error;
	}
	return error;
}

inline fcml_bool fcml_fn_utils_is_reg_undef( fcml_st_register *reg ) {
    return reg->type == FCML_REG_UNDEFINED;
}

