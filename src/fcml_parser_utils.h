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

#ifndef FCML_PUTILS_H_
#define FCML_PUTILS_H_

#include <fcml_common.h>

#include "fcml_env_int.h"
#include "fcml_apc_ast.h"
#include "fcml_ceh.h"
#include "fcml_coll.h"

/** Override default memory allocation function used by bison parser */
#define YYMALLOC fcml_fn_env_memory_alloc

/** Override default memory deallocation function used by bison parser */
#define YYFREE fcml_fn_env_memory_free

typedef struct fcml_st_parser_data {
    /* Lexer context. */
    void *scannerInfo;
    /* Instruction pointer used to declare symbols. */
    fcml_ip ip;
    /* Defined symbol. */
    fcml_st_symbol *symbol;
    /* Abstract syntax tree of parsed isntruction. */
    fcml_st_ast_node *tree;
    /* All potential errors going here. */
    fcml_st_ceh_error_container errors;
} fcml_st_parser_data;

void fcml_fn_pu_parse_integer(const fcml_char *str,
        fcml_st_ast_val_integer *integer_value, int base);

void fcml_fn_pu_parse_float(const fcml_char *str,
        fcml_st_ast_val_float *float_value);

void fcml_fn_pu_parse_register(fcml_en_register type, fcml_usize size,
        fcml_uint8_t num, fcml_bool x64_exp, fcml_st_register *reg_dest);

fcml_char* fcml_fn_pu_reg_type_to_string(fcml_en_register type);

#endif /* FCML_PUTILS_H_ */
