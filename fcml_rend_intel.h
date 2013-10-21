/*
 * fcml_rend_intel.h
 *
 *  Created on: Oct 20, 2013
 *      Author: tas
 */

#ifndef FCML_REND_INTEL_H_
#define FCML_REND_INTEL_H_

#include "fcml_ceh.h"
#include "fcml_rend.h"

fcml_ceh_error fcml_fn_rend_render_instruction_intel( fcml_st_dialect_context *dialect_context, fcml_st_memory_stream *output_stream, fcml_st_disassembler_result *result, fcml_uint32_t render_flags );

#endif /* FCML_REND_INTEL_H_ */
