/*
 * fcml_utils.c
 *
 *  Created on: 23-05-2013
 *      Author: tAs
 */

#include "fcml_utils.h"

fcml_ceh_error fcml_fn_utils_encode_displacement( fcml_st_memory_stream *stream, const fcml_st_displacement *displacement ) {
	fcml_ceh_error error;
	fcml_bool result;
	switch( displacement->size ) {
	case FCML_DS_8:
		result = fcml_fn_stream_write( stream, displacement->dis8 );
		break;
	case FCML_DS_16:
		result = fcml_fn_stream_write_word( stream, displacement->dis16 );
		break;
	case FCML_DS_32:
		result = fcml_fn_stream_write_dword( stream, displacement->dis32 );
		break;
	}
	if( !result ) {
		// Insufficient stream size.
		error = FCML_CEH_GEC_INVALID_INPUT;
	}
	return error;
}

