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
void fcml_fn_rend_utils_format_append_code( fcml_st_render_config *config, fcml_st_memory_stream *stream, fcml_uint8_t *instrunction_code, fcml_usize instruction_code_size );
fcml_int fcml_fn_rend_utils_format_append_str_if( fcml_st_memory_stream *stream, const fcml_string string, fcml_bool condition );
void fcml_fn_rend_utils_format_finish_str( fcml_st_memory_stream *stream );
fcml_int fcml_fn_rend_utils_format_repeat_char( fcml_st_memory_stream *stream, fcml_char character, fcml_int repeats );
fcml_int fcml_fn_rend_utils_format_append_str( fcml_st_memory_stream *stream, const fcml_string source );
fcml_int fcml_fn_rend_utils_format_append_str_padding( fcml_st_memory_stream *stream, const fcml_string source, fcml_int16_t padding );
void fcml_fn_rend_utils_format_append_stream( fcml_st_memory_stream *destination_stream, const fcml_st_memory_stream *source_stream );
fcml_ceh_error fcml_fn_rend_utils_format_append_integer( fcml_string patterns[6][4], fcml_st_memory_stream *stream, const fcml_st_integer *integer, fcml_bool is_hex, fcml_bool remove_leading_zeros );
void fcml_fn_rend_utils_format_append_reg( fcml_st_dialect_context_int *dialect_context, fcml_st_memory_stream *stream, const fcml_st_register *reg, fcml_bool is_rex );
fcml_int fcml_fn_rend_utils_padding( fcml_st_memory_stream *output_stream, fcml_int len, fcml_int padding, fcml_int default_padding );
fcml_int fcml_ifn_rend_utils_print_prefixes( fcml_st_memory_stream *output_stream, fcml_st_prefixes_details *prefixes, fcml_uint32_t flags );
fcml_bool fcml_fn_rend_utils_render_operand_separator( fcml_st_render_config *config, fcml_st_memory_stream *output_stream, fcml_int padding_length, fcml_bool first_operand );

#endif /* FCML_REND_UTILS_H_ */
