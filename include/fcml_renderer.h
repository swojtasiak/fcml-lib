/*
 * FCML - Free Code Manipulation Library.
 * Copyright (C) 2010-2020 Slawomir Wojtasiak
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

/** @file fcml_renderer.h
 * Structures and functions declarations related to FCML renderers
 *
 * @copyright Copyright (C) 2010-2020 Slawomir Wojtasiak. All rights reserved.
 * This project is released under the GNU Lesser General Public License.
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

/** The rendered instruction size can not exceed this value. */
#define FCML_REND_MAX_BUFF_LEN					512

/**
 * @defgroup RENDERER_FLAGS_GROUP Flags configuring rendering process.
 * @{
 */

/** Render the instruction code as HEX string. */
#define FCML_REND_FLAG_RENDER_CODE				0x00000001
/** Render the immediate operand as HEX integer. */
#define FCML_REND_FLAG_HEX_IMM					0x00000002
/** Render the segment code register even if it is a default one. */
#define FCML_REND_FLAG_RENDER_DEFAULT_SEG		0x00000004
/** Render the displacement value as HEX integer. */
#define FCML_REND_FLAG_HEX_DISPLACEMENT			0x00000008
/** Render the conditional mnemonics using suffixes from first group. */
#define FCML_REND_FLAG_COND_GROUP_1				0x00000010
/** Render the conditional mnemonics using suffixes from second group. */
#define FCML_REND_FLAG_COND_GROUP_2				0x00000020
/** Render the conditional mnemonics using suffixes for 'carry'. */
#define FCML_REND_FLAG_COND_SHOW_CARRY			0x00000040
/** Render SIB operand hints. */
#define FCML_REND_FLAG_RENDER_SIB_HINT			0x00000080
/** Render ABS (Absolute offset) operand hints. */
#define FCML_REND_FLAG_RENDER_ABS_HINT			0x00000100
/** Render REL (Relative offset) operand hints. */
#define FCML_REND_FLAG_RENDER_REL_HINT			0x00000200
/** Render hints for absolute addressing. */
#define FCML_REND_FLAG_RENDER_INDIRECT_HINT		0x00000400
/** Renders repetition prefixes using the first group (repe,repne). */
#define FCML_REND_FLAG_REP_PREFIX_GROUP_1		0x00000800
/** Renders repetition prefixes using the second group (repz,repnz). */
#define FCML_REND_FLAG_REP_PREFIX_GROUP_2		0x00001000
/** Renders the code padding between the instruction code and the mnemonic. */
#define FCML_REND_FLAG_CODE_PADDING				0x00002000
/** Renders the mnemonic padding between the mnemonic and the operands. */
#define FCML_REND_FLAG_MNEMONIC_PADDING			0x00004000
/** Should be used only with FCML_REND_FLAG_HEX_IMM and FCML_REND_FLAG_
 * HEX_DISPLACEMENT flags. */
#define FCML_REND_FLAG_REMOVE_LEADING_ZEROS		0x00008000

/** Default set of the rendering flags. */
#define FCML_REND_DEFAULT_FLAGS				0
/** Default number of characters used as code padding. */
#define FCML_REND_DEFAULT_CODE_PADDING		8
/** Default number of characters used as mnemonic padding. */
#define FCML_REND_DEFAULT_MNEMONIC_PADDING	8

/** @} */

/** Renderer configuration. */
typedef struct fcml_st_render_config {
    /** Flags which allows to control rendering process. */
    fcml_uint32_t render_flags;
    /** Preferred mnemonic padding in characters. */
    fcml_uint16_t prefered_mnemonic_padding;
    /** Preferred code padding in HEX bytes (2 characters on one byte.). */
    fcml_uint16_t prefered_code_padding;
} fcml_st_render_config;

/**
 * Renders the disassembled instruction into its textual representation.
 * Prepares textual representation of the disassembled code using syntax
 * based on the provided dialect.
 *
 * @param dialect Dialect instance.
 * @param config Renderer configuration.
 * @param[out] buffer Destination buffer for the generated instruction.
 * @param buffer_len Size of the destination buffer.
 * @param result Disassembled instruction.
 * @return Error code or FCML_CEH_GEC_NO_ERROR.
 *
 */
LIB_EXPORT fcml_ceh_error LIB_CALL fcml_fn_render(
        const fcml_st_dialect *dialect, const fcml_st_render_config *config,
        fcml_char *buffer, fcml_usize buffer_len,
        const fcml_st_disassembler_result *result);

#ifdef __cplusplus
}
#endif

#endif /* FCML_REND_H_ */
