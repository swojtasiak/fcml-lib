/*
 * fcml_modrm.c
 *
 *  Created on: 29-05-2013
 *      Author: tAs
 */

#include "fcml_modrm.h"

fcml_ceh_error fcml_fn_modrm_write_encoded_modrm( fcml_st_encoded_modrm *encoded_modrm, fcml_st_memory_stream *stream ) {
	if( !fcml_fn_stream_write( stream, encoded_modrm->modrm ) ) {
		return FCML_CEH_GEC_EOF;
	}
	if( encoded_modrm->sib.is_not_null ) {
		if( !fcml_fn_stream_write( stream, encoded_modrm->sib.value ) ) {
			return FCML_CEH_GEC_EOF;
		}
	}
	if( encoded_modrm->displacement_size ) {
		int size = encoded_modrm->displacement_size;
		if( fcml_fn_stream_write_bytes( stream, &(encoded_modrm->displacement ), size ) != size ) {
			return FCML_CEH_GEC_EOF;
		}
	}
	return FCML_CEH_GEC_NO_ERROR;
}
