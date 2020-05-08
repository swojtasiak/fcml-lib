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

#ifndef FCML_ASM_DECODING_TREE_H_
#define FCML_ASM_DECODING_TREE_H_

#include "fcml_coll.h"
#include "fcml_def.h"
#include "fcml_dialect_int.h"

#define FCML_DT_TREE_OPCODE_ARRAY_SIZE	256

typedef struct fcml_st_dt_diss_tree_element {
    struct fcml_st_dt_diss_tree_element *opcodes[FCML_DT_TREE_OPCODE_ARRAY_SIZE];
    fcml_st_coll_list *instruction_decoding_defs;
} fcml_st_dt_diss_tree_element;

typedef fcml_ceh_error (*fcml_fp_dt_prep_inst_def_callback)(
        fcml_st_dialect_context_int *dialect,
        fcml_st_dt_diss_tree_element *element,
        fcml_st_def_instruction_desc *instruction_desc,
        fcml_st_def_addr_mode_desc *opcode_desc);

typedef void (*fcml_fp_dt_disp_inst_def_callback)(
        fcml_st_dialect_context_int *dialect, fcml_ptr instruction_decoding);

typedef struct fcml_st_dt_decoding_tree {
    fcml_st_dt_diss_tree_element *opcode[FCML_DT_TREE_OPCODE_ARRAY_SIZE];
    fcml_st_dialect_context_int *dialect_context;
    fcml_fp_dt_prep_inst_def_callback prep_callback;
    fcml_fp_dt_disp_inst_def_callback disp_callback;
} fcml_st_dt_decoding_tree;

fcml_ceh_error fcml_fn_dt_dts_tree_init(
        fcml_st_dialect_context_int *dialect_context,
        fcml_st_dt_decoding_tree **tree,
        fcml_fp_dt_prep_inst_def_callback prepare_callback,
        fcml_fp_dt_disp_inst_def_callback dispose_callback);

void fcml_fn_dt_dts_tree_free(fcml_st_dialect_context_int *dialect_context,
        fcml_st_dt_decoding_tree *tree);

#endif /* FCML_ASM_DECODING_TREE_H_ */
