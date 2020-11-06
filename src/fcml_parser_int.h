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

#ifndef FCML_PARSER_INT_H_
#define FCML_PARSER_INT_H_

#include <fcml_parser.h>

#include "fcml_apc_ast.h"
#include "fcml_coll.h"
#include "fcml_ceh.h"

typedef struct fcml_st_parser_ast {
    /* Defined symbol. */
    fcml_st_symbol *symbol;
    /* Abstract syntax tree of parsed instruction. */
    fcml_st_ast_node *tree;
    /* All potential errors going here. */
    fcml_st_ceh_error_container errors;
} fcml_st_parser_ast;

fcml_ceh_error fcml_fn_parse_to_cif(fcml_st_parser_context *context,
        const fcml_string instruction, fcml_st_parser_result *result_out);

fcml_ceh_error fcml_fn_parse_to_ast(fcml_st_parser_context *context,
        const fcml_string instruction, fcml_st_parser_ast *ast_out);

fcml_ceh_error fcml_fn_parser_add_symbol_to_symbol_table(
        fcml_st_ceh_error_container *errors, fcml_st_symbol_table symbol_table,
        fcml_st_symbol *symbol, fcml_bool allow_override);

void fcml_fn_parser_free_ast(fcml_st_parser_ast *ast);

void fcml_fn_parser_free_symbol(fcml_st_symbol *symbol);

#endif /* FCML_PARSER_INT_H_ */
