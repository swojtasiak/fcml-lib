/*
 * fcml_utils.c
 *
 *  Created on: 23-05-2013
 *      Author: tAs
 */

#include "fcml_utils.h"

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

fcml_ceh_error fcml_fn_utils_displacement_to_vint( const fcml_st_displacement *displacement, fcml_vint *vint ) {
	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
	vint->int64 = 0;
	switch( displacement->size ) {
	case FCML_DS_8:
		vint->int8 = (signed)displacement->dis8;
		break;
	case FCML_DS_16:
		vint->int16 = (signed)displacement->dis16;
		break;
	case FCML_DS_32:
		vint->int32 = (signed)displacement->dis32;
		break;
	default:
		error = FCML_CEH_GEC_INVALID_INPUT;
		break;
	}
	vint->size = displacement->size;
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
