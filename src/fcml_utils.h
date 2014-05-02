/*
 * fcml_utils.h
 *
 *  Created on: 23-05-2013
 *      Author: tAs
 */

#ifndef FCML_UTILS_H_
#define FCML_UTILS_H_

#include <fcml_errors.h>
#include "fcml_ceh.h"
#include "fcml_common.h"
#include "fcml_stream.h"

typedef enum fcml_en_utils_size_flags {
    FCML_ENUSF_8 = 0x01,
    FCML_ENUSF_16 = 0x02,
    FCML_ENUSF_32 = 0x04,
    FCML_ENUSF_64 = 0x08,
    FCML_ENUSF_ALL = ( FCML_ENUSF_8 | FCML_ENUSF_16 | FCML_ENUSF_32 | FCML_ENUSF_64 )
} fcml_en_utils_size_flags;

fcml_ceh_error fcml_fn_utils_int64_to_integer( fcml_uint64_t src, fcml_bool is_src_signed, fcml_st_integer *integer, fcml_en_utils_size_flags filter );
fcml_ceh_error fcml_fn_utils_convert_integer_to_integer( const fcml_st_integer *source, fcml_st_integer *destination, fcml_usize expected_source_size, fcml_usize destination_size );
fcml_ceh_error fcml_fn_utils_convert_integer_to_uint8( const fcml_st_integer *integer, fcml_uint8_t *value );
fcml_ceh_error fcml_fn_utils_convert_integer_to_uint16( const fcml_st_integer *integer, fcml_uint16_t *value );
fcml_ceh_error fcml_fn_utils_convert_integer_to_uint32( const fcml_st_integer *integer, fcml_uint32_t *value );
fcml_ceh_error fcml_fn_utils_convert_integer_to_uint64( const fcml_st_integer *integer, fcml_uint64_t *value );
fcml_ceh_error fcml_fn_utils_convert_integer_to_int8( const fcml_st_integer *integer, fcml_int8_t *value );
fcml_ceh_error fcml_fn_utils_convert_integer_to_int16( const fcml_st_integer *integer, fcml_int16_t *value );
fcml_ceh_error fcml_fn_utils_convert_integer_to_int32( const fcml_st_integer *integer, fcml_int32_t *value );
fcml_ceh_error fcml_fn_utils_convert_integer_to_int64( const fcml_st_integer *integer, fcml_int64_t *value );
fcml_ceh_error fcml_fn_utils_decode_integer( fcml_st_memory_stream *stream, fcml_st_integer *integer, fcml_usize size );
fcml_ceh_error fcml_fn_utils_encode_integer( fcml_st_memory_stream *stream, const fcml_st_integer *integer );
fcml_ceh_error fcml_fn_utils_displacement_to_integer( const fcml_st_integer *displacement, fcml_st_integer *integer );
fcml_ceh_error fcml_fn_utils_integer_to_displacement( const fcml_st_integer *integer, fcml_st_integer *displacement );
fcml_ceh_error fcml_fn_utils_offset_to_integer( const fcml_st_offset *offset, fcml_st_integer *integer );
fcml_ceh_error fcml_fn_utils_integer_to_offset( const fcml_st_integer *integer, fcml_st_offset *offset );
fcml_ceh_error fcml_fn_utils_integer_to_imm( const fcml_st_integer *integer, fcml_st_integer *imm );
fcml_ceh_error fcml_fn_utils_extend_integer( fcml_st_integer *integer, fcml_usize extension );
fcml_bool fcml_fn_utils_is_reg_undef( const fcml_st_register *reg );
fcml_ceh_error fcml_fn_utils_convert_map_error( fcml_int error );
void fcml_fn_utils_convert_gec_to_error_info( fcml_bool enabled, fcml_st_ceh_error_container *error_container, fcml_ceh_error code );
fcml_ceh_error fcml_fn_prepare_entry_point( fcml_st_entry_point *entry_point );
fcml_bool fcml_fn_utils_is_displacement_negative( const fcml_st_integer *displacement );

#endif /* FCML_UTILS_H_ */
