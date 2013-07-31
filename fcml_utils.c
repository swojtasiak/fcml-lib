/*
 * fcml_utils.c
 *
 *  Created on: 23-05-2013
 *      Author: tAs
 */

#include "fcml_utils.h"
#include "fcml_types.h"

fcml_ceh_error fcml_fn_utils_convert_sig_imm_to_sig_imm( fcml_st_immediate *source, fcml_st_immediate *destination, fcml_data_size expected_source_size, fcml_data_size destination_size ) {

	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

	// Convert given source immediate value to expected one.

	fcml_st_immediate expected = {0};
	expected.imm_size = expected_source_size;
	if( source->imm_size != expected_source_size ) {
		switch( expected_source_size ) {
		case FCML_DS_8:
			error = fcml_fn_utils_convert_imm_to_int8( source, (fcml_int8_t*)&(expected.imm8) );
			break;
		case FCML_DS_16:
			error = fcml_fn_utils_convert_imm_to_int16( source, (fcml_int16_t*)&(expected.imm16) );
			break;
		case FCML_DS_32:
			error = fcml_fn_utils_convert_imm_to_int32( source, (fcml_int32_t*)&(expected.imm32) );
			break;
		case FCML_DS_64:
			error = fcml_fn_utils_convert_imm_to_int64( source, (fcml_int64_t*)&(expected.imm64) );
			break;
		}
	} else {
		expected = *source;
	}

	if( !error ) {

		// Event is expected immediate value is unsigned, we can treat is as a signed value,
		// just because we expect signed value here and they are of the same size.
		expected.is_signed = FCML_TRUE;

		// Convert expected value to destination one.

		switch( destination_size ) {
			case FCML_DS_8:
				error = fcml_fn_utils_convert_imm_to_int8( &expected, (fcml_int8_t*)&(destination->imm8) );
				break;
			case FCML_DS_16:
				error = fcml_fn_utils_convert_imm_to_int16( &expected, (fcml_int16_t*)&(destination->imm16) );
				break;
			case FCML_DS_32:
				error = fcml_fn_utils_convert_imm_to_int32( &expected, (fcml_int32_t*)&(destination->imm32) );
				break;
			case FCML_DS_64:
				error = fcml_fn_utils_convert_imm_to_int64( &expected, (fcml_int64_t*)&(destination->imm64) );
				break;
		}

		destination->imm_size = destination_size;
		destination->is_signed = FCML_TRUE;

	}

	return error;
}

fcml_ceh_error fcml_fn_utils_convert_imm_to_uint8( fcml_st_immediate *imm, fcml_uint8_t *value ) {
	switch( imm->imm_size ) {
	case FCML_DS_8:
		// In this case we doesn't care what is in IMM, because no conversion is needed.
		*value = imm->imm8;
		break;
	case FCML_DS_16:
		if( imm->is_signed ) {
			if( (fcml_int16_t)imm->imm16 > FCML_UINT8_MAX || (fcml_int16_t)imm->imm16 < 0 ) {
				return FCML_CEH_GEC_VALUE_OUT_OF_RANGE;
			}
			*value = (fcml_uint8_t)(fcml_int16_t)imm->imm16;
		} else {
			if( imm->imm16 > FCML_UINT8_MAX ) {
				return FCML_CEH_GEC_VALUE_OUT_OF_RANGE;
			}
			*value = (fcml_uint8_t)imm->imm16;
		}
		break;
	case FCML_DS_32:
		if( imm->is_signed ) {
			if( (fcml_int32_t)imm->imm32 > FCML_UINT8_MAX || (fcml_int32_t)imm->imm32 < 0 ) {
				return FCML_CEH_GEC_VALUE_OUT_OF_RANGE;
			}
			*value = (fcml_uint8_t)(fcml_int32_t)imm->imm32;
		} else {
			if( imm->imm32 > FCML_UINT8_MAX ) {
				return FCML_CEH_GEC_VALUE_OUT_OF_RANGE;
			}
			*value = (fcml_uint8_t)imm->imm32;
		}
		break;
	case FCML_DS_64:
		if( imm->is_signed ) {
			if( (fcml_int64_t)imm->imm64 > FCML_UINT8_MAX || (fcml_int64_t)imm->imm64 < 0 ) {
				return FCML_CEH_GEC_VALUE_OUT_OF_RANGE;
			}
			*value = (fcml_uint8_t)(fcml_int64_t)imm->imm64;
		} else {
			if( imm->imm64 > FCML_UINT8_MAX ) {
				return FCML_CEH_GEC_VALUE_OUT_OF_RANGE;
			}
			*value = (fcml_uint8_t)imm->imm64;
		}
		break;
	default:
		return FCML_CEH_GEC_VALUE_OUT_OF_RANGE;
	}
	return FCML_CEH_GEC_NO_ERROR;
}

fcml_ceh_error fcml_fn_utils_convert_imm_to_uint16( fcml_st_immediate *imm, fcml_uint16_t *value ) {
	switch( imm->imm_size ) {
	case FCML_DS_8:
		*value = (fcml_uint16_t)imm->imm8;
		break;
	case FCML_DS_16:
		*value = (fcml_uint16_t)imm->imm16;
		break;
	case FCML_DS_32:
		if( imm->is_signed ) {
			if( (fcml_int32_t)imm->imm32 > FCML_UINT16_MAX || (fcml_int32_t)imm->imm32 < 0 ) {
				return FCML_CEH_GEC_VALUE_OUT_OF_RANGE;
			}
			*value = (fcml_uint16_t)(fcml_int32_t)imm->imm32;
		} else {
			if( imm->imm32 > FCML_UINT16_MAX ) {
				return FCML_CEH_GEC_VALUE_OUT_OF_RANGE;
			}
			*value = (fcml_uint16_t)imm->imm32;
		}
		break;
	case FCML_DS_64:
		if( imm->is_signed ) {
			if( (fcml_int64_t)imm->imm64 > FCML_UINT16_MAX || (fcml_int64_t)imm->imm64 < 0 ) {
				return FCML_CEH_GEC_VALUE_OUT_OF_RANGE;
			}
			*value = (fcml_uint16_t)(fcml_int64_t)imm->imm64;
		} else {
			if( imm->imm64 > FCML_UINT16_MAX ) {
				return FCML_CEH_GEC_VALUE_OUT_OF_RANGE;
			}
			*value = (fcml_uint16_t)imm->imm64;
		}
		break;
	default:
		return FCML_CEH_GEC_VALUE_OUT_OF_RANGE;
	}
	return FCML_CEH_GEC_NO_ERROR;
}

fcml_ceh_error fcml_fn_utils_convert_imm_to_uint32( fcml_st_immediate *imm, fcml_uint32_t *value ) {
	switch( imm->imm_size ) {
	case FCML_DS_8:
		*value = (fcml_uint32_t)imm->imm8;
		break;
	case FCML_DS_16:
		*value = (fcml_uint32_t)imm->imm16;
		break;
	case FCML_DS_32:
		*value = (fcml_uint32_t)imm->imm32;
		break;
	case FCML_DS_64:
		if( imm->is_signed ) {
			if( (fcml_int64_t)imm->imm64 > FCML_UINT32_MAX || (fcml_int64_t)imm->imm64 < 0 ) {
				return FCML_CEH_GEC_VALUE_OUT_OF_RANGE;
			}
			*value = (fcml_uint32_t)(fcml_int64_t)imm->imm64;
		} else {
			if( imm->imm64 > FCML_UINT32_MAX ) {
				return FCML_CEH_GEC_VALUE_OUT_OF_RANGE;
			}
			*value = (fcml_uint32_t)imm->imm64;
		}
		break;
	default:
		return FCML_CEH_GEC_VALUE_OUT_OF_RANGE;
	}
	return FCML_CEH_GEC_NO_ERROR;
}

fcml_ceh_error fcml_fn_utils_convert_imm_to_uint64( fcml_st_immediate *imm, fcml_uint64_t *value ) {
	switch( imm->imm_size ) {
	case FCML_DS_8:
		*value = (fcml_uint64_t)imm->imm8;
		break;
	case FCML_DS_16:
		*value = (fcml_uint64_t)imm->imm16;
		break;
	case FCML_DS_32:
		*value = (fcml_uint64_t)imm->imm32;
		break;
	case FCML_DS_64:
		*value = (fcml_uint64_t)imm->imm64;
		break;
	default:
		return FCML_CEH_GEC_VALUE_OUT_OF_RANGE;
	}
	return FCML_CEH_GEC_NO_ERROR;
}

fcml_ceh_error fcml_fn_utils_convert_imm_to_int8( fcml_st_immediate *imm, fcml_int8_t *value ) {
	switch( imm->imm_size ) {
	case FCML_DS_8:
		*value = (fcml_int8_t)imm->imm8;
		break;
	case FCML_DS_16:
		if( imm->is_signed ) {
			if( (fcml_int16_t)imm->imm16 < FCML_INT8_MIN || (fcml_int16_t)imm->imm16 > FCML_INT8_MAX ) {
				return FCML_CEH_GEC_VALUE_OUT_OF_RANGE;
			}
		} else {
			if( imm->imm16 > FCML_INT8_MAX ) {
				return FCML_CEH_GEC_VALUE_OUT_OF_RANGE;
			}
		}
		*value = (fcml_int8_t)(fcml_int16_t)imm->imm16;
		break;
	case FCML_DS_32:
		if( imm->is_signed ) {
			if( (fcml_int32_t)imm->imm32 < FCML_INT8_MIN || (fcml_int32_t)imm->imm32 > FCML_INT8_MAX ) {
				return FCML_CEH_GEC_VALUE_OUT_OF_RANGE;
			}
		} else {
			if( imm->imm32 > FCML_INT8_MAX ) {
				return FCML_CEH_GEC_VALUE_OUT_OF_RANGE;
			}
		}
		*value = (fcml_int8_t)(fcml_int32_t)imm->imm32;
		break;
	case FCML_DS_64:
		if( imm->is_signed ) {
			if( (fcml_int64_t)imm->imm64 < FCML_INT8_MIN || (fcml_int64_t)imm->imm64 > FCML_INT8_MAX ) {
				return FCML_CEH_GEC_VALUE_OUT_OF_RANGE;
			}
		} else {
			if( imm->imm64 > FCML_INT8_MAX ) {
				return FCML_CEH_GEC_VALUE_OUT_OF_RANGE;
			}
		}
		*value = (fcml_int8_t)(fcml_int64_t)imm->imm64;
		break;
	default:
		return FCML_CEH_GEC_VALUE_OUT_OF_RANGE;
	}
	return FCML_CEH_GEC_NO_ERROR;
}

fcml_ceh_error fcml_fn_utils_convert_imm_to_int16( fcml_st_immediate *imm, fcml_int16_t *value ) {
	switch( imm->imm_size ) {
	case FCML_DS_8:
		*value = imm->is_signed ? (fcml_int16_t)(fcml_int8_t)imm->imm8 : (fcml_int16_t)imm->imm8;
		break;
	case FCML_DS_16:
		*value = (fcml_int16_t)imm->imm16;
		break;
	case FCML_DS_32:
		if( imm->is_signed ) {
			if( (fcml_int32_t)imm->imm32 < FCML_INT16_MIN || (fcml_int32_t)imm->imm32 > FCML_INT16_MAX ) {
				return FCML_CEH_GEC_VALUE_OUT_OF_RANGE;
			}
		} else {
			if( imm->imm32 > FCML_INT16_MAX ) {
				return FCML_CEH_GEC_VALUE_OUT_OF_RANGE;
			}
		}
		*value = (fcml_int16_t)(fcml_int32_t)imm->imm32;
		break;
	case FCML_DS_64:
		if( imm->is_signed ) {
			if( (fcml_int64_t)imm->imm64 < FCML_INT16_MIN || (fcml_int64_t)imm->imm64 > FCML_INT16_MAX ) {
				return FCML_CEH_GEC_VALUE_OUT_OF_RANGE;
			}
		} else {
			if( imm->imm64 > FCML_INT16_MAX ) {
				return FCML_CEH_GEC_VALUE_OUT_OF_RANGE;
			}
		}
		*value = (fcml_int16_t)(fcml_int64_t)imm->imm64;
		break;
	default:
		return FCML_CEH_GEC_VALUE_OUT_OF_RANGE;
	}
	return FCML_CEH_GEC_NO_ERROR;
}

fcml_ceh_error fcml_fn_utils_convert_imm_to_int32( fcml_st_immediate *imm, fcml_int32_t *value ) {
	switch( imm->imm_size ) {
	case FCML_DS_8:
		*value = imm->is_signed ? (fcml_int32_t)(fcml_int8_t)imm->imm8 : (fcml_int32_t)imm->imm8;
		break;
	case FCML_DS_16:
		*value = imm->is_signed ? (fcml_int32_t)(fcml_int16_t)imm->imm16 : (fcml_int32_t)imm->imm16;
		break;
	case FCML_DS_32:
		*value = (fcml_int32_t)imm->imm32;
		break;
	case FCML_DS_64:
		if( imm->is_signed ) {
			if( (fcml_int64_t)imm->imm64 < FCML_INT32_MIN || (fcml_int64_t)imm->imm64 > FCML_INT32_MAX ) {
				return FCML_CEH_GEC_VALUE_OUT_OF_RANGE;
			}
		} else {
			if( imm->imm64 > FCML_INT32_MAX ) {
				return FCML_CEH_GEC_VALUE_OUT_OF_RANGE;
			}
		}
		*value = (fcml_int32_t)(fcml_int64_t)imm->imm64;
		break;
	default:
		return FCML_CEH_GEC_VALUE_OUT_OF_RANGE;
	}
	return FCML_CEH_GEC_NO_ERROR;
}

fcml_ceh_error fcml_fn_utils_convert_imm_to_int64( fcml_st_immediate *imm, fcml_int64_t *value ) {
	switch( imm->imm_size ) {
	case FCML_DS_8:
		*value = imm->is_signed ? (fcml_int64_t)(fcml_int8_t)imm->imm8 : (fcml_int64_t)imm->imm8;
		break;
	case FCML_DS_16:
		*value = imm->is_signed ? (fcml_int64_t)(fcml_int16_t)imm->imm16 : (fcml_int64_t)imm->imm16;
		break;
	case FCML_DS_32:
		*value = imm->is_signed ? (fcml_int64_t)(fcml_int32_t)imm->imm32 : (fcml_int64_t)imm->imm32;
		break;
	case FCML_DS_64:
		*value = (fcml_int64_t)imm->imm64;
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

fcml_ceh_error fcml_fn_utils_decode_uvint( fcml_st_memory_stream *stream, fcml_uvint *uvint, fcml_usize size ) {
	fcml_bool result = FCML_FALSE;
	switch(size) {
	case FCML_DS_8:
		uvint->uint8 = fcml_fn_stream_read( stream, &result );
		uvint->size = FCML_DS_8;
		break;
	case FCML_DS_16:
		uvint->uint16 = fcml_fn_stream_read_word( stream, &result );
		uvint->size = FCML_DS_16;
		break;
	case FCML_DS_32:
		uvint->uint32 = fcml_fn_stream_read_dword( stream, &result );
		uvint->size = FCML_DS_32;
		break;
	case FCML_DS_64:
		uvint->uint64 = fcml_fn_stream_read_qword( stream, &result );
		uvint->size = FCML_DS_64;
		break;
	default:
		return FCML_CEH_GEC_INVALID_INPUT;
	}
	if( !result ) {
		return FCML_CEH_GEC_EOF;
	}
	return FCML_CEH_GEC_NO_ERROR;
}

fcml_ceh_error fcml_fn_utils_decode_vint( fcml_st_memory_stream *stream, fcml_vint *vint, fcml_usize size ) {
	fcml_bool result = FCML_FALSE;
	switch(size) {
	case FCML_DS_8:
		vint->int8 = fcml_fn_stream_read( stream, &result );
		vint->size = FCML_DS_8;
		break;
	case FCML_DS_16:
		vint->int16 = fcml_fn_stream_read_word( stream, &result );
		vint->size = FCML_DS_16;
		break;
	case FCML_DS_32:
		vint->int32 = fcml_fn_stream_read_dword( stream, &result );
		vint->size = FCML_DS_32;
		break;
	case FCML_DS_64:
		vint->int64 = fcml_fn_stream_read_qword( stream, &result );
		vint->size = FCML_DS_64;
		break;
	default:
		return FCML_CEH_GEC_INVALID_INPUT;
	}
	if( !result ) {
		return FCML_CEH_GEC_EOF;
	}
	return FCML_CEH_GEC_NO_ERROR;
}

fcml_ceh_error fcml_fn_utils_encode_uvint( fcml_st_memory_stream *stream, const fcml_uvint *uvint ) {
	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
	fcml_bool result = FCML_FALSE;
	switch( uvint->size ) {
	case FCML_DS_8:
		result = fcml_fn_stream_write( stream, uvint->uint8 );
		break;
	case FCML_DS_16:
		result = fcml_fn_stream_write_word( stream, uvint->uint16 );
		break;
	case FCML_DS_32:
		result = fcml_fn_stream_write_dword( stream, uvint->uint32 );
		break;
	case FCML_DS_64:
		result = fcml_fn_stream_write_qword( stream, uvint->uint64 );
		break;
	}
	if( !result ) {
		// Insufficient stream size.
		error = FCML_CEH_GEC_INVALID_INPUT;
	}
	return error;
}

fcml_ceh_error fcml_fn_utils_encode_vint( fcml_st_memory_stream *stream, const fcml_vint *vint ) {
	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
	fcml_bool result = FCML_FALSE;
	switch( vint->size ) {
	case FCML_DS_8:
		result = fcml_fn_stream_write( stream, (unsigned)vint->int8 );
		break;
	case FCML_DS_16:
		result = fcml_fn_stream_write_word( stream, (unsigned)vint->int16 );
		break;
	case FCML_DS_32:
		result = fcml_fn_stream_write_dword( stream, (unsigned)vint->int32 );
		break;
	case FCML_DS_64:
		result = fcml_fn_stream_write_qword( stream, (unsigned)vint->int64 );
		break;
	}
	if( !result ) {
		// Insufficient stream size.
		error = FCML_CEH_GEC_INVALID_INPUT;
	}
	return error;
}

fcml_ceh_error fcml_fn_utils_displacement_to_uvint( const fcml_st_displacement *displacement, fcml_uvint *uvint ) {
	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
	uvint->uint64 = 0;
	switch( displacement->size ) {
	case FCML_DS_8:
		uvint->uint8 = displacement->dis8;
		break;
	case FCML_DS_16:
		uvint->uint16 = displacement->dis16;
		break;
	case FCML_DS_32:
		uvint->uint32 = displacement->dis32;
		break;
	default:
		error = FCML_CEH_GEC_INVALID_INPUT;
		break;
	}
	uvint->size = displacement->size;
	return error;
}

fcml_ceh_error fcml_fn_utils_uvint_to_displacement( const fcml_uvint *uvint, fcml_st_displacement *displacement ) {
	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
	displacement->dis32 = 0;
	switch( uvint->size ) {
	case FCML_DS_8:
		displacement->dis8 = (signed)uvint->uint8;
		break;
	case FCML_DS_16:
		displacement->dis16 = (signed)uvint->uint16;
		break;
	case FCML_DS_32:
		displacement->dis32 = (signed)uvint->uint32;
		break;
	case FCML_DS_64:
		displacement->dis64 = (signed)uvint->uint64;
		break;
	default:
		error = FCML_CEH_GEC_INVALID_INPUT;
		break;
	}
	displacement->size = uvint->size;
	return error;
}

fcml_ceh_error fcml_fn_utils_vint_to_displacement( const fcml_vint *vint, fcml_st_displacement *displacement ) {
	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
	displacement->dis32 = 0;
	switch( vint->size ) {
	case FCML_DS_8:
		displacement->dis8 = vint->int8;
		break;
	case FCML_DS_16:
		displacement->dis16 = vint->int16;
		break;
	case FCML_DS_32:
		displacement->dis32 = vint->int32;
		break;
	case FCML_DS_64:
		displacement->dis64 = vint->int64;
		break;
	default:
		error = FCML_CEH_GEC_INVALID_INPUT;
		break;
	}
	displacement->size = vint->size;
	return error;
}

fcml_ceh_error fcml_fn_utils_displacement_to_vint( const fcml_st_displacement *displacement, fcml_vint *vint ) {
	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
	vint->int64 = 0;
	switch( displacement->size ) {
	case FCML_DS_8:
		vint->int8 = (fcml_int8_t)displacement->dis8;
		break;
	case FCML_DS_16:
		vint->int16 = (fcml_int16_t)displacement->dis16;
		break;
	case FCML_DS_32:
		vint->int32 = (fcml_int32_t)displacement->dis32;
		break;
	case FCML_DS_64:
		vint->int64 = (fcml_int64_t)displacement->dis64;
		break;
	default:
		error = FCML_CEH_GEC_INVALID_INPUT;
		break;
	}
	vint->size = displacement->size;
	return error;
}

fcml_ceh_error fcml_fn_utils_imm_to_uvint( fcml_st_immediate *imm, fcml_uvint *uvint ) {
	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
	uvint->uint64 = 0;
	switch( imm->imm_size ) {
	case FCML_DS_8:
		uvint->uint8 = imm->imm8;
		break;
	case FCML_DS_16:
		uvint->uint16 = imm->imm16;
		break;
	case FCML_DS_32:
		uvint->uint32 = imm->imm32;
		break;
	case FCML_DS_64:
		uvint->uint64 = imm->imm64;
		break;
	default:
		error = FCML_CEH_GEC_INVALID_INPUT;
		break;
	}
	uvint->size = imm->imm_size;
	return error;
}

fcml_ceh_error fcml_fn_utils_imm_to_vint( fcml_st_immediate *imm, fcml_vint *vint ) {
	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
	vint->int64 = 0;
	switch( imm->imm_size ) {
	case FCML_DS_8:
		vint->int8 = (fcml_int8_t)imm->imm8;
		break;
	case FCML_DS_16:
		vint->int16 = (fcml_int16_t)imm->imm16;
		break;
	case FCML_DS_32:
		vint->int32 = (fcml_int32_t)imm->imm32;
		break;
	case FCML_DS_64:
		vint->int64 = (fcml_int64_t)imm->imm64;
		break;
	default:
		error = FCML_CEH_GEC_INVALID_INPUT;
		break;
	}
	vint->size = imm->imm_size;
	return error;
}

fcml_ceh_error fcml_fn_utils_extend_uvint( fcml_uvint *uvint, fcml_usize extension ) {
	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
	uint64_t temp_int = 0;
	switch( uvint->size ) {
	case 8:
		temp_int = uvint->uint8;
		break;
	case 16:
		temp_int = uvint->uint16;
		break;
	case 32:
		temp_int = uvint->uint32;
		break;
	case 64:
		temp_int = uvint->uint64;
		break;
	default:
		error = FCML_CEH_GEC_INVALID_INPUT;
		break;
	}
	if( !error ) {
		uvint->uint64 = 0;
		switch( extension ) {
		case 8:
			uvint->uint8 = (fcml_uint8_t)temp_int;
			break;
		case 16:
			uvint->uint16 = (fcml_uint16_t)temp_int;
			break;
		case 32:
			uvint->uint32 = (fcml_uint32_t)temp_int;
			break;
		case 64:
			uvint->uint64 = (fcml_uint64_t)temp_int;
			break;
		}
		uvint->size = extension;
	}
	return error;
}

fcml_ceh_error fcml_fn_utils_extend_vint( fcml_vint *vint, fcml_usize extension ) {
	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
	int64_t temp_int = 0;
	switch( vint->size ) {
	case 8:
		temp_int = vint->int8;
		break;
	case 16:
		temp_int = vint->int16;
		break;
	case 32:
		temp_int = vint->int32;
		break;
	case 64:
		temp_int = vint->int64;
		break;
	default:
		error = FCML_CEH_GEC_INVALID_INPUT;
		break;
	}
	if( !error ) {
		vint->int64 = 0;
		switch( extension ) {
		case 8:
			vint->int8 = (fcml_uint8_t)temp_int;
			break;
		case 16:
			vint->int16 = (fcml_uint16_t)temp_int;
			break;
		case 32:
			vint->int32 = (fcml_uint32_t)temp_int;
			break;
		case 64:
			vint->int64 = (fcml_uint64_t)temp_int;
			break;
		}
		vint->size = extension;
	}
	return error;
}
