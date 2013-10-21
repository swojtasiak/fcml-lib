/*
 * fcml_rend.c
 *
 *  Created on: Oct 20, 2013
 *      Author: tas
 */

#include "fcml_rend.h"

fcml_ceh_error fcml_fn_rend_render_instruction( fcml_st_dialect_context *dialect_context, fcml_st_memory_stream *output_stream, fcml_st_disassembler_result *result, fcml_uint32_t render_flags ) {
	if( dialect_context->instruction_renderer ) {
		return dialect_context->instruction_renderer( dialect_context, output_stream, result, render_flags );
	} else {
		// Dialect not initialized correctly.
		return FCML_CEH_GEC_ILLEGAL_STATE_EXCEPTION;
	}
}
