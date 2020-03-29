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

#ifndef FCML_HINTS_H_
#define FCML_HINTS_H_

#include <fcml_common.h>

#include "fcml_def.h"

typedef struct fcml_st_hts_calculated_hints {
    fcml_hints instruction_hints;
    fcml_hints operand_hints;
} fcml_st_hts_calculated_hints;

typedef fcml_st_hts_calculated_hints (*fcml_fp_hts_instruction_hints_calculator)(
        const fcml_st_def_addr_mode_desc *addr_mode,
        fcml_st_def_decoded_addr_mode *decoded_addr_mode);

fcml_st_hts_calculated_hints fcml_fn_hts_ihc_far_pointer(
        const fcml_st_def_addr_mode_desc *addr_mode,
        fcml_st_def_decoded_addr_mode *decoded_addr_mode);

fcml_st_hts_calculated_hints fcml_fn_hts_ihc_modrm_hints(
        const fcml_st_def_addr_mode_desc *addr_mode,
        fcml_st_def_decoded_addr_mode *decoded_addr_mode);

fcml_st_hts_calculated_hints fcml_fn_hts_ihc_immediate_dis_relative(
        const fcml_st_def_addr_mode_desc *addr_mode,
        fcml_st_def_decoded_addr_mode *decoded_addr_mode);

fcml_st_hts_calculated_hints fcml_fn_hts_ihc_pseudo_opcode(
        const fcml_st_def_addr_mode_desc *addr_mode,
        fcml_st_def_decoded_addr_mode *decoded_addr_mode);

#endif /* FCML_HINTS_H_ */
