/*
 * fcml_rend_utils.h
 *
 *  Created on: Oct 20, 2013
 *      Author: tas
 */

#ifndef FCML_REND_UTILS_H_
#define FCML_REND_UTILS_H_

#include "fcml_ceh.h"
#include "fcml_common.h"
#include "fcml_dialect_int.h"
#include "fcml_stream.h"
#include "fcml_types.h"

void fcml_fn_rend_utils_format_printf(struct fcml_st_memory_stream *stream, const fcml_string format, ...);
void fcml_fn_rend_utils_format_append_hex_byte( fcml_st_memory_stream *stream, fcml_uint8_t hex_byte );
void fcml_fn_rend_utils_format_append_code( fcml_st_memory_stream *stream, fcml_uint8_t *instrunction_code, fcml_data_size instruction_code_size, fcml_bool is_padding );
void fcml_fn_rend_utils_format_append_str_if( fcml_st_memory_stream *stream, const fcml_string string, fcml_bool condition );
void fcml_fn_rend_utils_format_finish_str( fcml_st_memory_stream *stream );
void fcml_fn_rend_utils_format_append_str( fcml_st_memory_stream *stream, const fcml_string source );
void fcml_fn_rend_utils_format_append_stream( fcml_st_memory_stream *destination_stream, const fcml_st_memory_stream *source_stream );
fcml_ceh_error fcml_fn_rend_utils_format_append_integer( fcml_string patterns[4][4], fcml_st_memory_stream *stream, const fcml_st_integer *integer, fcml_bool is_hex );
void fcml_fn_rend_utils_format_append_reg( fcml_st_dialect_context_int *dialect_context, fcml_st_memory_stream *stream, const fcml_st_register *reg, fcml_bool is_rex );

#endif /* FCML_REND_UTILS_H_ */
