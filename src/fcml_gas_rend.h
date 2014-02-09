/*
 * fcml_rend_intel.h
 *
 *  Created on: Oct 20, 2013
 *      Author: tas
 */

#ifndef FCML_REND_INTEL_H_
#define FCML_REND_INTEL_H_

#include <fcml_types.h>
#include <fcml_dialect.h>
#include <fcml_disassembler.h>
#include <fcml_renderer.h>

#include "fcml_ceh.h"
#include "fcml_stream.h"

fcml_ceh_error fcml_fn_rend_render_instruction_gas( fcml_st_dialect *dialect_context, fcml_st_render_config *config, fcml_st_memory_stream *output_stream, fcml_st_disassembler_result *result );

#endif /* FCML_REND_INTEL_H_ */
