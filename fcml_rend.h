/*
 * fcml_rend.h
 *
 *  Created on: Oct 20, 2013
 *      Author: tas
 */

#ifndef FCML_REND_H_
#define FCML_REND_H_

#include "fcml_stream.h"
#include "fcml_asm_dialect.h"

#define FCML_REND_FLAG_RENDER_CODE				0x00000001
#define FCML_REND_FLAG_HEX_IMM					0x00000002
#define FCML_REND_FLAG_RENDER_DEFAULT_SEG		0x00000004
#define FCML_REND_FLAG_HEX_DISPLACEMENT			0x00000008
#define FCML_REND_FLAG_COND_GROUP_1				0x00000010
#define FCML_REND_FLAG_COND_GROUP_2				0x00000020
#define FCML_REND_FLAG_COND_SHOW_CARRY			0x00000040

#define RCML_REND_DEFAULT_FLAGS		0

fcml_ceh_error fcml_fn_rend_render_instruction( fcml_st_dialect_context *dialect_context, fcml_st_memory_stream *output_stream, fcml_st_dasm_disassembler_result *result, fcml_uint32_t render_flags );

#endif /* FCML_REND_H_ */
