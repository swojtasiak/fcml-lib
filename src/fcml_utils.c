/*
 * FCML - Free Code Manipulation Library.
 * Copyright (C) 2010-2014 Slawomir Wojtasiak
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include <fcml_types.h>
#include <fcml_errors.h>

#include "fcml_utils.h"
#include "fcml_coll.h"
#include "fcml_trace.h"
#include "fcml_messages.h"

fcml_ceh_error fcml_fn_utils_int64_to_integer( fcml_uint64_t src, fcml_bool is_src_signed, fcml_st_integer *integer, fcml_en_utils_size_flags filter ) {
    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
    if( is_src_signed ) {
    	fcml_int64_t imm = (fcml_int64_t)src;
    	if( ( filter & FCML_ENUSF_8 ) && imm <= FCML_INT8_MAX && imm >= FCML_INT8_MIN ) {
    		integer->int8 = (fcml_int8_t)imm;
			integer->size = FCML_DS_8;
		} else if( ( filter & FCML_ENUSF_16 ) && imm <= FCML_INT16_MAX && imm >= FCML_INT16_MIN ) {
			integer->int16 = (fcml_int16_t)imm;
			integer->size = FCML_DS_16;
		} else if( ( filter & FCML_ENUSF_32 ) && imm <= FCML_INT32_MAX && imm >= FCML_INT32_MIN ) {
			integer->int32 = (fcml_int32_t)imm;
			integer->size = FCML_DS_32;
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


fcml_ceh_error fcml_fn_utils_convert_integer_to_integer( const fcml_st_integer *source, fcml_st_integer *destination, fcml_usize expected_source_size, fcml_usize destination_size ) {

	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

	/* Convert given source immediate value to expected one.*/

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

		/* Convert expected value to destination one.*/

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

fcml_ceh_error fcml_fn_utils_convert_integer_to_uint8( const fcml_st_integer *integer, fcml_uint8_t *value ) {
	switch( integer->size ) {
	case FCML_DS_8:
		/* In this case we doesn't care what is in IMM, because no conversion is needed.*/
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

fcml_ceh_error fcml_fn_utils_convert_integer_to_uint16( const fcml_st_integer *integer, fcml_uint16_t *value ) {
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

fcml_ceh_error fcml_fn_utils_convert_integer_to_uint32( const fcml_st_integer *integer, fcml_uint32_t *value ) {
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

fcml_ceh_error fcml_fn_utils_convert_integer_to_uint64( const fcml_st_integer *integer, fcml_uint64_t *value ) {
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
        /* Insufficient stream size.*/
        error = FCML_CEH_GEC_INVALID_INPUT;
    }
    return error;
}

fcml_ceh_error fcml_fn_utils_displacement_to_integer( const fcml_st_integer *displacement, fcml_st_integer *integer ) {
	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
	integer->int64 = 0;
	switch( displacement->size ) {
	case FCML_DS_8:
	    integer->int8 = displacement->int8;
		break;
	case FCML_DS_16:
	    integer->int16 = displacement->int16;
		break;
	case FCML_DS_32:
	    integer->int32 = displacement->int32;
		break;
	case FCML_DS_64:
        integer->int64 = displacement->int64;
        break;
	default:
		error = FCML_CEH_GEC_INVALID_INPUT;
		break;
	}
	integer->size = displacement->size;
	integer->is_signed = displacement->is_signed;
	return error;
}

fcml_ceh_error fcml_fn_utils_integer_to_displacement( const fcml_st_integer *integer, fcml_st_integer *displacement ) {
	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
	displacement->int64 = 0;
	switch( integer->size ) {
	case FCML_DS_8:
		displacement->int8 = integer->int8;
		break;
	case FCML_DS_16:
		displacement->int16 = integer->int16;
		break;
	case FCML_DS_32:
		displacement->int32 = integer->int32;
		break;
	case FCML_DS_64:
		displacement->int64 = integer->int64;
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

fcml_ceh_error fcml_fn_utils_extend_integer( fcml_st_integer *integer, fcml_usize extension ) {
	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
	if( !integer->is_signed ) {
        fcml_uint64_t temp_int = 0;
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
	    fcml_int64_t temp_int = 0;
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

fcml_bool fcml_fn_utils_is_reg_undef( const fcml_st_register *reg ) {
    return reg->type == FCML_REG_UNDEFINED;
}

fcml_ceh_error fcml_fn_utils_convert_map_error( fcml_int error ) {
	fcml_ceh_error ceh_error = FCML_CEH_GEC_NO_ERROR;
	switch( error ) {
	case FCML_COLL_ERROR_NO_ERROR:
		ceh_error = FCML_CEH_GEC_NO_ERROR;
		break;
	case FCML_COLL_ERROR_OUT_OF_MEMORY:
		ceh_error = FCML_CEH_GEC_OUT_OF_MEMORY;
		break;
	case FCML_COLL_ERROR_BAD_ARGS:
	case FCML_COLL_ERROR_MAP_FULL:
		// Should never happened in case of FCML.
		FCML_TRACE_MSG( "Map reached its maximal size or something different related to map processing happened." );
		ceh_error = FCML_CEH_GEC_INTERNAL_ERROR;
		break;
	}
	return ceh_error;
}

void fcml_fn_utils_convert_gec_to_error_info( fcml_bool enabled, fcml_st_ceh_error_container *error_container, fcml_ceh_error code ) {

	if( enabled ) {

		// Prepare standard description of the error code, but only if there is no other error on the list.
		fcml_st_ceh_error_info *current = error_container->errors;
		while( current ) {
			if( current->level == FCML_EN_CEH_EL_ERROR ) {
				return;
			}
			current = current->next_error;
		}

		if( !fcml_fn_ceh_add_error( error_container, fcml_fn_msg_get_message( (fcml_en_msg_message_code)code ), code, FCML_EN_CEH_EL_ERROR ) ) {
			FCML_TRACE_MSG( "Out of memory, can not allocate space for error info." );
		}

	}
}

fcml_ceh_error fcml_fn_prepare_entry_point( fcml_st_entry_point *entry_point ) {

	/* Mode has to be set. */
	if( entry_point->op_mode != FCML_AF_16_BIT && entry_point->op_mode != FCML_AF_32_BIT && entry_point->op_mode != FCML_AF_64_BIT ) {
		return FCML_CEH_GEC_INVALID_ADDRESSING_MODE;
	}

	/* 16 bit address size attribute is not supported in 64bit mode. */
	if( entry_point->op_mode == FCML_AF_64_BIT && entry_point->address_size_attribute == FCML_DS_16 ) {
		return FCML_CEH_GEC_INVALID_ADDRESS_SIZE;
	}

	/* Check if attributes are valid and set them to default values. */
	if( !entry_point->address_size_attribute ) {
		switch( entry_point->op_mode ) {
		case FCML_AF_16_BIT:
			entry_point->address_size_attribute = FCML_DS_16;
			break;
		case FCML_AF_32_BIT:
			entry_point->address_size_attribute = FCML_DS_32;
			break;
		case FCML_AF_64_BIT:
			entry_point->address_size_attribute = FCML_DS_64;
			break;
		}
	}

	if( !entry_point->operand_size_attribute ) {
		switch( entry_point->op_mode ) {
		case FCML_AF_16_BIT:
			entry_point->operand_size_attribute = FCML_DS_16;
			break;
		case FCML_AF_32_BIT:
			entry_point->operand_size_attribute = FCML_DS_32;
			break;
		case FCML_AF_64_BIT:
			entry_point->operand_size_attribute = FCML_DS_32;
			break;
		}
	}

	/* Check if ASA is value.*/
	fcml_usize asa = entry_point->address_size_attribute;
	if( asa != FCML_DS_16 && asa != FCML_DS_32 && asa != FCML_DS_64 ) {
		return FCML_CEH_GEC_INVALID_ADDRESS_SIZE;
	}

	/* Check if OSA is value.*/
	fcml_usize osa = entry_point->operand_size_attribute;
	if( osa != FCML_DS_16 && osa != FCML_DS_32 && osa != FCML_DS_64 ) {
		return FCML_CEH_GEC_INVALID_OPPERAND_SIZE;
	}

	return FCML_CEH_GEC_NO_ERROR;
}

fcml_bool fcml_fn_utils_is_displacement_negative( const fcml_st_integer *displacement ) {

	if( !displacement->is_signed ) {
		return FCML_FALSE;
	}

	switch( displacement->size ) {
	case FCML_DS_8:
	    return displacement->int8 < 0;
	case FCML_DS_16:
		return displacement->int16 < 0;
	case FCML_DS_32:
		return displacement->int32 < 0;
	case FCML_DS_64:
		return displacement->int64 < 0;
	default:
		return FCML_FALSE;
	}

}
