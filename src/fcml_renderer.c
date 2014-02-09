/*
 * fcml_rend.c
 *
 *  Created on: Oct 20, 2013
 *      Author: tas
 */

#include <fcml_renderer.h>
#include "fcml_stream.h"
#include "fcml_dialect_int.h"
#include "fcml_trace.h"
#include "fcml_env.h"

fcml_ceh_error LIB_CALL fcml_fn_render( fcml_st_dialect *dialect, fcml_st_render_config *config, fcml_char *buffer, fcml_usize buffer_len, fcml_st_disassembler_result *result ) {

	fcml_st_memory_stream output_stream;
	output_stream.base_address = buffer;
	output_stream.offset = 0;
	output_stream.size = buffer_len;

	fcml_st_dialect_context_int *dialect_context_int = (fcml_st_dialect_context_int*)dialect;
	if( dialect_context_int->instruction_renderer ) {
		fcml_fnp_render_instruction renderer = (fcml_fnp_render_instruction)dialect_context_int->instruction_renderer;
		return renderer( dialect, config, &output_stream, result );
	} else {
		/* Dialect not initialized correctly.*/
		FCML_TRACE_MSG("Rendering not supported by current dialect.");
		return FCML_CEH_GEC_FEATURE_NOT_SUPPORTED;
	}

}
