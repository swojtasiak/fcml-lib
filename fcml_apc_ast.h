/*
 * fcml_apc_ast.h
 *
 *  Created on: 10-03-2013
 *      Author: tAs
 */

#ifndef FCML_APC_AST_H_
#define FCML_APC_AST_H_

#include <stdlib.h>
#include "fcml_common.h"
#include "fcml_coll.h"

#define FCML_AST_INT_FLAG_IMMEDIATE		0x0001

typedef struct fcml_st_ast_size_operator {
    fcml_uint16_t size;
    fcml_bool multimedia;
} fcml_st_size_operator;

typedef struct fcml_st_ast_val_integer {
	fcml_uint64_t value;
	fcml_bool overflow;
	fcml_bool is_signed;
	fcml_uint16_t flags;
} fcml_st_ast_val_integer;

typedef struct fcml_st_ast_val_float {
	fcml_float value;
	fcml_bool overflow;
} fcml_st_ast_val_float;

typedef enum fcml_en_ast_node_type {
	FCML_EN_TN_INSTRUCTION,
	FCML_EN_TN_OPERAND_LIST,
	FCML_EN_TN_EXP,
	FCML_EN_TN_UMINUS,
	FCML_EN_TN_VALUE,
	FCML_EN_TN_REG,
	FCML_EN_TN_FAR_POINTER,
	FCML_EN_TN_EFFECTIVE_ADDRESS,
} fcml_en_ast_node_type;

typedef struct fcml_st_ast_node {
	fcml_en_ast_node_type type;
	fcml_ptr node;
} fcml_st_ast_node;

typedef enum fcml_st_ast_value_node_type {
	FCML_EN_ET_INTEGER,
	FCML_EN_ET_FLOAT
} fcml_st_ast_value_node_type;

typedef struct fcml_st_ast_node_value {
	fcml_st_ast_value_node_type type;
	fcml_st_ast_val_integer integer_value;
	fcml_st_ast_val_float float_value;
} fcml_st_ast_node_value;

typedef struct fcml_st_ast_node_register {
	fcml_st_register reg;
} fcml_st_ast_node_register;

typedef enum fcml_en_ast_exp_node_operator {
	FCML_EN_EXN_SUB,
	FCML_EN_EXN_ADD,
	FCML_EN_EXN_MUL,
	FCML_EN_EXN_DIV
} fcml_en_ast_exp_node_operator;

typedef struct fcml_st_ast_node_exp {
	fcml_st_ast_node *l;
	fcml_st_ast_node *r;
	fcml_en_ast_exp_node_operator operator;
} fcml_st_ast_node_exp;

typedef struct fcml_st_ast_node_uminus {
	fcml_st_ast_node *exp;
} fcml_st_ast_node_uminus;

typedef struct fcml_st_ast_node_far_pointer {
	fcml_st_ast_node *segment_selector;
	fcml_st_ast_node *offset;
} fcml_st_ast_node_far_pointer;

typedef struct fcml_st_ast_node_effective_address {
	fcml_hints instruction_hints;
    fcml_hints addressing_hints;
	fcml_uint16_t size_operator;
	fcml_st_register segment_selector;
    fcml_st_register base;
    fcml_st_register index;
    fcml_st_ast_val_integer scale_factor;
    fcml_st_ast_node *displacement;
    fcml_en_effective_address_form address_form;
} fcml_st_ast_node_effective_address;

typedef struct fcml_st_ast_node_offset {
    fcml_hints hints;
    fcml_st_ast_node *offset;
} fcml_st_ast_node_offset;

typedef struct fcml_st_ast_node_operand_list {
	fcml_st_coll_list *operands;
} fcml_st_ast_node_operand_list;

typedef struct fcml_st_ast_node_instruction {
	fcml_uint16_t prefixes;
    fcml_hints hints;
	fcml_string mnemonic;
	fcml_st_ast_node *operands;
} fcml_st_ast_node_instruction;

/* Operations */

fcml_st_ast_node *fcml_fn_ast_alloc_node_integer( fcml_st_ast_val_integer *integer_value );
fcml_st_ast_node *fcml_fn_ast_alloc_node_float( fcml_st_ast_val_float *float_value );
fcml_st_ast_node *fcml_fn_ast_alloc_node_operand_list( fcml_st_ast_node *operand_l, fcml_st_ast_node *operand_r );
fcml_st_ast_node *fcml_fn_ast_alloc_node_instruction( fcml_prefixes prefixes, fcml_string mnemonic, fcml_usize length, fcml_hints hints, fcml_st_ast_node *operand_list );
fcml_st_ast_node *fcml_fn_ast_alloc_node_register( fcml_st_register *reg );
fcml_st_ast_node *fcml_fn_ast_alloc_node_exp( fcml_en_ast_exp_node_operator operator, fcml_st_ast_node *exp_left, fcml_st_ast_node *exp_right );
fcml_st_ast_node *fcml_fn_ast_alloc_node_far_pointer( fcml_st_ast_node *segment_selector, fcml_st_ast_node *offset );
fcml_st_ast_node *fcml_fn_ast_set_effective_address_hins( fcml_st_ast_node *effective_address_node, fcml_hints hints );
fcml_st_ast_node *fcml_fn_ast_set_effective_address_details( fcml_st_register *segment_selector, fcml_st_size_operator *size_operator, fcml_st_ast_node *effective_address );
fcml_st_ast_node *fcml_fn_ast_set_displacemnt( fcml_st_ast_node *displacement, fcml_st_ast_node *effective_address );
fcml_st_ast_node *fcml_fn_ast_alloc_node_effective_address( fcml_st_register *base, fcml_st_register *index, fcml_st_ast_val_integer *scale_factor, fcml_st_ast_node *displacement, fcml_bool uminus_displacement, fcml_hints hints );
fcml_st_ast_node *fcml_fn_ast_alloc_node_uminus( fcml_st_ast_node *exp );
void fcml_fn_ast_free_node( fcml_st_ast_node *exp );

fcml_ceh_error fcml_fn_ast_to_cif_converter( fcml_st_ast_node *ast_instruction_node, fcml_st_ceh_error_container *error_container, fcml_st_instruction **instruction );
void fcml_fn_ast_free_converted_cif( fcml_st_instruction *cif_instruction );

#endif /* FCML_APC_AST_H_ */
