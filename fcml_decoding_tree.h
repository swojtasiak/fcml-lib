/*
 * fcml_asm_decoding_tree.h
 *
 *  Created on: Oct 13, 2013
 *      Author: tas
 */

#ifndef FCML_ASM_DECODING_TREE_H_
#define FCML_ASM_DECODING_TREE_H_

#include "fcml_coll.h"
#include "fcml_def.h"
#include "fcml_dialect.h"

#define FCML_DT_TREE_OPCODE_ARRAY_SIZE	256

typedef struct fcml_st_dt_diss_tree_element {
	struct fcml_st_dt_diss_tree_element* opcodes[FCML_DT_TREE_OPCODE_ARRAY_SIZE];
	fcml_st_coll_list *instruction_decoding_defs;
} fcml_st_dt_diss_tree_element;

typedef fcml_ceh_error (*fcml_fp_dt_prepare_instruction_decoding_callback)( fcml_st_dialect_context *dialect, fcml_st_dt_diss_tree_element *element, fcml_st_def_instruction_desc *instruction_desc, fcml_st_def_addr_mode_desc *opcode_desc );
typedef void (*fcml_fp_dt_dispose_instruction_decoding_callback)( fcml_st_dialect_context *dialect, fcml_ptr instruction_decoding );

typedef struct fcml_st_dt_decoding_tree {
	fcml_st_dt_diss_tree_element* opcode[FCML_DT_TREE_OPCODE_ARRAY_SIZE];
	fcml_st_dialect_context dialect_context;
	fcml_fp_dt_prepare_instruction_decoding_callback prepare_callback;
	fcml_fp_dt_dispose_instruction_decoding_callback dispose_callback;
} fcml_st_dt_decoding_tree;

fcml_ceh_error fcml_fn_dt_dts_tree_init( fcml_st_dialect_context *dialect_context, fcml_st_dt_decoding_tree **tree, fcml_fp_dt_prepare_instruction_decoding_callback prepare_callback, fcml_fp_dt_dispose_instruction_decoding_callback dispose_callback );
void fcml_fn_dt_dts_tree_free( fcml_st_dialect_context *dialect_context, fcml_st_dt_decoding_tree *tree );

#endif /* FCML_ASM_DECODING_TREE_H_ */
