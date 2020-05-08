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

#ifndef FCML_APC_AST_H_
#define FCML_APC_AST_H_

#include <stdlib.h>
#include <fcml_symbols.h>
#include <fcml_parser.h>
#include "fcml_common.h"
#include "fcml_coll.h"

#define FCML_AST_INT_FLAG_IMMEDIATE		0x0001

typedef enum fcml_en_ast_node_type {
    FCML_EN_TN_INSTRUCTION,
    FCML_EN_TN_OPERAND_LIST,
    FCML_EN_TN_EXP,
    FCML_EN_TN_UMINUS,
    FCML_EN_TN_VALUE,
    FCML_EN_TN_REG,
    FCML_EN_TN_VIRTUAL,
    FCML_EN_TN_FAR_POINTER,
    FCML_EN_TN_EFFECTIVE_ADDRESS,
    FCML_EN_TN_USE_SYMBOL
} fcml_en_ast_node_type;

typedef struct fcml_st_ast_size_operator {
    fcml_uint16_t size;
    fcml_bool multimedia;
} fcml_st_size_operator;

typedef struct fcml_st_ast_val_integer {
    fcml_uint64_t value;
    fcml_bool overflow;
    fcml_bool is_signed;
} fcml_st_ast_val_integer;

typedef struct fcml_st_ast_val_float {
    fcml_float value;
    fcml_bool overflow;
} fcml_st_ast_val_float;

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
    fcml_st_operand_decorators decorators;
} fcml_st_ast_node_register;

typedef struct fcml_st_ast_node_virtual {
    fcml_st_operand_decorators decorators;
} fcml_st_ast_node_virtual;

typedef enum fcml_en_ast_exp_node_operator {
    FCML_EN_EXN_SUB,
    FCML_EN_EXN_ADD,
    FCML_EN_EXN_MUL,
    FCML_EN_EXN_DIV
} fcml_en_ast_exp_node_operator;

typedef struct fcml_st_ast_node_exp {
    fcml_st_ast_node *l;
    fcml_st_ast_node *r;
    fcml_en_ast_exp_node_operator op;
} fcml_st_ast_node_exp;

typedef struct fcml_st_ast_node_uminus {
    fcml_st_ast_node *exp;
} fcml_st_ast_node_uminus;

typedef struct fcml_st_ast_node_define_symbol {
    fcml_st_symbol *symbol;
} fcml_st_ast_node_define_symbol;

typedef struct fcml_st_ast_node_use_symbol {
    fcml_string symbol;
} fcml_st_ast_node_use_symbol;

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
    fcml_st_operand_decorators decorators;
} fcml_st_ast_node_effective_address;

typedef struct fcml_st_ast_node_operand_list {
    fcml_st_coll_list *operands;
} fcml_st_ast_node_operand_list;

typedef struct fcml_st_ast_node_instruction {
    fcml_uint16_t prefixes;
    fcml_hints hints;
    fcml_string mnemonic;
    fcml_st_ast_node *operands;
} fcml_st_ast_node_instruction;

typedef struct fcml_st_cif_converter_context {
    /* Set to true in order to ignore all undefined symbols.
     * In such case every unknown symbol is treated as 0.
     */
    fcml_bool ignore_undefined_symbols;
    /* Container for errors. */
    fcml_st_ceh_error_container *errors;
    /* Symbols table. */
    fcml_st_symbol_table symbol_table;
    /* Number of evaluated symbols. */
    fcml_int evaluated_symbols;
    /* Number of ignored undefined symbols. */
    fcml_int ignored_symbols;
} fcml_st_cif_converter_context;

/* Function pointer for node visitor. */
typedef fcml_ceh_error (*fcml_fnp_ast_node_visitor)(fcml_st_ast_node *node,
        fcml_ptr visitor_args );

/* Operations */

fcml_st_ast_node *fcml_fn_ast_alloc_node_integer(
        fcml_st_ast_val_integer *integer_value);

fcml_st_ast_node *fcml_fn_ast_alloc_node_float(
        fcml_st_ast_val_float *float_value);

fcml_st_ast_node *fcml_fn_ast_alloc_node_operand_list(
        fcml_st_ast_node *operand_l, fcml_st_ast_node *operand_r);

fcml_st_ast_node *fcml_fn_ast_alloc_node_instruction(fcml_prefixes prefixes,
        fcml_string mnemonic, fcml_usize length, fcml_hints hints,
        fcml_st_ast_node *operand_list);

fcml_st_ast_node *fcml_fn_ast_alloc_node_pseudo_operation(fcml_string mnemonic,
        fcml_usize length, fcml_st_ast_node *exp);

fcml_st_ast_node *fcml_fn_ast_alloc_node_virtual(fcml_bool sae,
        fcml_bool er_enabled, fcml_uint8_t er_value);

fcml_st_ast_node *fcml_fn_ast_alloc_node_register(fcml_st_register *reg,
        fcml_st_register *opmask_reg_decorator, fcml_bool zero_decorator);

fcml_st_symbol *fcml_fn_ast_alloc_node_define_symbol(fcml_ip ip,
        fcml_string symbol, fcml_usize length);

fcml_st_ast_node *fcml_fn_ast_alloc_node_use_symbol(fcml_string symbol_name,
        fcml_usize length);

fcml_st_ast_node *fcml_fn_ast_alloc_node_exp(fcml_en_ast_exp_node_operator op,
        fcml_st_ast_node *exp_left, fcml_st_ast_node *exp_right);

fcml_st_ast_node *fcml_fn_ast_alloc_node_far_pointer(
        fcml_st_ast_node *segment_selector, fcml_st_ast_node *offset);

fcml_st_ast_node *fcml_fn_ast_set_effective_address_hins(
        fcml_st_ast_node *effective_address_node,
        fcml_hints hints);

fcml_st_ast_node *fcml_fn_ast_decorate_effective_address(
        fcml_st_ast_node *node, fcml_st_register *opmask_reg_decorator,
        fcml_bool zero_decorator);

fcml_st_ast_node *fcml_fn_ast_set_effective_address_details(
        fcml_st_register *segment_selector, fcml_st_size_operator *size_operator,
        fcml_uint8_t bcast_decorator, fcml_st_ast_node *effective_address );

fcml_st_ast_node *fcml_fn_ast_set_displacemnt(fcml_st_ast_node *displacement,
        fcml_st_ast_node *effective_address);

fcml_st_ast_node *fcml_fn_ast_alloc_node_effective_address(fcml_st_register *base,
        fcml_st_register *index, fcml_st_ast_val_integer *scale_factor,
        fcml_st_ast_node *displacement, fcml_bool uminus_displacement, fcml_hints hints);

fcml_st_ast_node *fcml_fn_ast_alloc_node_uminus(fcml_st_ast_node *exp);

void fcml_fn_ast_free_node(fcml_st_ast_node *exp);

fcml_ceh_error visit_nodes(fcml_st_ast_node *ast_tree,
        fcml_fnp_ast_node_visitor visitor, fcml_ptr visitor_args);

fcml_ceh_error fcml_fn_ast_extract_used_symbols(fcml_st_ast_node *ast_tree,
        fcml_st_coll_list **extracted_symbols);

fcml_ceh_error fcml_fn_ast_to_cif_converter(
        fcml_st_cif_converter_context *context,
        fcml_st_ast_node *ast_tree, fcml_st_instruction **instruction);

void fcml_fn_ast_free_converted_cif(fcml_st_instruction *cif_instruction);

#endif /* FCML_APC_AST_H_ */
