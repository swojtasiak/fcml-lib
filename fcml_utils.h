/*
 * fcml_utils.h
 *
 *  Created on: 23-05-2013
 *      Author: tAs
 */

#ifndef FCML_UTILS_H_
#define FCML_UTILS_H_

#include "fcml_ceh.h"
#include "fcml_common.h"
#include "fcml_stream.h"

fcml_ceh_error fcml_fn_utils_encode_uvint( fcml_st_memory_stream *stream, const fcml_uvint *uvint );
fcml_ceh_error fcml_fn_utils_encode_vint( fcml_st_memory_stream *stream, const fcml_vint *vint );
fcml_ceh_error fcml_fn_utils_decode_uvint( fcml_st_memory_stream *stream, fcml_uvint *uvint, fcml_usize size );
fcml_ceh_error fcml_fn_utils_decode_vint( fcml_st_memory_stream *stream, fcml_vint *vint, fcml_usize size );
fcml_ceh_error fcml_fn_utils_displacement_to_uvint( const fcml_st_displacement *displacement, fcml_uvint *uvint );
fcml_ceh_error fcml_fn_utils_displacement_to_vint( const fcml_st_displacement *displacement, fcml_vint *vint );
fcml_ceh_error fcml_fn_utils_uvint_to_displacement( const fcml_uvint *uvint, fcml_st_displacement *displacement );
fcml_ceh_error fcml_fn_utils_vint_to_displacement( const fcml_vint *vint, fcml_st_displacement *displacement );
fcml_ceh_error fcml_fn_utils_imm_to_uvint( fcml_st_immediate *imm, fcml_uvint *uvint );
fcml_ceh_error fcml_fn_utils_imm_to_vint( fcml_st_immediate *imm, fcml_vint *vint );
fcml_ceh_error fcml_fn_utils_extend_uvint( fcml_uvint *uvint, fcml_usize extension );
fcml_ceh_error fcml_fn_utils_extend_vint( fcml_vint *vint, fcml_usize extension );
fcml_data_size fcml_fn_utils_get_default_ASA(fcml_en_addr_form addr_form);
fcml_data_size fcml_fn_utils_get_default_OSA(fcml_en_addr_form addr_form);
fcml_bool fcml_fn_utils_can_be_sign_converted_to_size( fcml_st_immediate *imm, fcml_usize size );
fcml_ceh_error fcml_fn_utils_sign_convert_imm_to_int8( fcml_st_immediate *imm, fcml_int8_t *value );
fcml_ceh_error fcml_fn_utils_sign_convert_imm_to_int16( fcml_st_immediate *imm, fcml_int16_t *value );
fcml_ceh_error fcml_fn_utils_sign_convert_imm_to_int32( fcml_st_immediate *imm, fcml_int32_t *value );

#endif /* FCML_UTILS_H_ */
