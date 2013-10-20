/*
 * fcml_rend_utils.h
 *
 *  Created on: Oct 20, 2013
 *      Author: tas
 */

#ifndef FCML_REND_UTILS_H_
#define FCML_REND_UTILS_H_

#include "fcml_types.h"
#include "fcml_stream.h"

void fcml_fn_rend_utils_format_printf(struct fcml_st_memory_stream *stream, const fcml_string format, ...);
void fcml_fn_rend_utils_format_append_hex_byte( fcml_st_memory_stream *stream, fcml_uint8_t hex_byte );
void fcml_fn_rend_utils_format_append_code( fcml_st_memory_stream *stream, fcml_uint8_t *instrunction_code, uint8_t instruction_code_size );
void fcml_fn_rend_utils_format_append_str( fcml_st_memory_stream *stream, const fcml_string source );
void fcml_fn_rend_utils_format_append_stream( fcml_st_memory_stream *destination_stream, fcml_st_memory_stream *source_stream );

#endif /* FCML_REND_UTILS_H_ */
