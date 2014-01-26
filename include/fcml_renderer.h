/*
 * fcml_rend.h
 *
 *  Created on: Oct 20, 2013
 *      Author: tas
 */

#ifndef FCML_REND_H_
#define FCML_REND_H_

#include "fcml_types.h"
#include "fcml_ceh.h"
#include "fcml_dialect.h"
#include "fcml_disassembler.h"
#include "fcml_stream.h"

#define FCML_REND_FLAG_RENDER_CODE				0x00000001
#define FCML_REND_FLAG_HEX_IMM					0x00000002
#define FCML_REND_FLAG_RENDER_DEFAULT_SEG		0x00000004
#define FCML_REND_FLAG_HEX_DISPLACEMENT			0x00000008
#define FCML_REND_FLAG_COND_GROUP_1				0x00000010
#define FCML_REND_FLAG_COND_GROUP_2				0x00000020
#define FCML_REND_FLAG_COND_SHOW_CARRY			0x00000040
#define FCML_REND_FLAG_RENDER_SIB_HINT			0x00000080
#define FCML_REND_FLAG_RENDER_ABS_HINT			0x00000100
#define FCML_REND_FLAG_RENDER_REL_HINT			0x00000200
#define FCML_REND_FLAG_RENDER_INDIRECT_HINT		0x00000400
#define FCML_REND_FLAG_REP_PREFIX_GROUP_1		0x00000800
#define FCML_REND_FLAG_REP_PREFIX_GROUP_2		0x00001000

#define RCML_REND_DEFAULT_FLAGS		0

fcml_ceh_error fcml_fn_render( fcml_st_dialect *dialect, fcml_st_memory_stream *output_stream, fcml_st_disassembler_result *result, fcml_uint32_t render_flags );

#endif /* FCML_REND_H_ */
