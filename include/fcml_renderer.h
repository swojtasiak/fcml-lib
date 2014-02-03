/*
 * fcml_rend.h
 *
 *  Created on: Oct 20, 2013
 *      Author: tas
 */

#ifndef FCML_REND_H_
#define FCML_REND_H_

#include "fcml_lib_export.h"

#include "fcml_types.h"
#include "fcml_errors.h"
#include "fcml_dialect.h"
#include "fcml_disassembler.h"

#ifdef __cplusplus
extern "C" {
#endif

#define FCML_REND_MAX_BUFF_LEN					512

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
#define FCML_REND_FLAG_CODE_PADDING				0x00002000

#define RCML_REND_DEFAULT_FLAGS		0

void LIB_EXPORT fcml_fn_render_clean_buffer( fcml_char *buffer, fcml_usize buffer_len );
fcml_ceh_error LIB_EXPORT fcml_fn_render( fcml_st_dialect *dialect, fcml_char *buffer, fcml_usize buffer_len, fcml_st_disassembler_result *result, fcml_uint32_t render_flags );

#ifdef __cplusplus
}
#endif

#endif /* FCML_REND_H_ */
