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

#include <fcml_symbols.h>

#include "fcml_parser_int.h"
#include "fcml_messages.h"
#include "fcml_env_int.h"
#include "fcml_dialect_int.h"

fcml_ceh_error fcml_fn_parser_add_symbol_to_symbol_table(
        fcml_st_ceh_error_container *errors, fcml_st_symbol_table symbol_table,
        fcml_st_symbol *symbol, fcml_bool allow_override) {

    fcml_ceh_error error = FCML_COLL_ERROR_NO_ERROR;

    if (!allow_override) {
        if (fcml_fn_symbol_get(symbol_table, symbol->symbol)) {
            /* Symbol already defined. */
            fcml_fn_msg_add_error_message(errors,
                    FCML_MC_SEGMENT_SYMBOL_ALREADY_DEFINED,
                    FCML_CEH_MEC_ERROR_SYMBOL_ALREADY_DEFINED,
                    FCML_EN_CEH_EL_ERROR, symbol->symbol);
            error = FCML_CEH_GEC_INVALID_INPUT;
        }
    }

    if (!error) {
        error = fcml_fn_symbol_add(symbol_table, symbol);
    }

    return error;
}

fcml_ceh_error fcml_fn_parse_to_cif(fcml_st_parser_context *context,
        const fcml_string mnemonic, fcml_st_parser_result *result) {

    if (!result || !mnemonic || !context) {
        return FCML_CEH_GEC_INVALID_INPUT;
    }

    fcml_st_parser_ast ast = { 0 };

    /* Free previous parser results. */
    fcml_fn_parser_result_free(result);

    fcml_ceh_error error = fcml_fn_parse_to_ast(context, mnemonic, &ast);

    /* Copy errors from parser.*/
    result->errors = ast.errors;

    if (error) {

        /* Just in case. */
        fcml_fn_symbol_free(ast.symbol);
        ast.symbol = NULL;
        fcml_fn_ast_free_node(ast.tree);
        ast.tree = NULL;

        return error;
    }

    fcml_bool new_symbol_table = FCML_FALSE;

    /* Symbol */
    if (ast.symbol) {
        if (!context->configuration.disable_symbols_declaration) {
            if (context->symbol_table
                    || context->configuration.alloc_symbol_table_if_needed) {
                /* If there is no symbol table yet, allocate it. */
                if (!context->symbol_table) {
                    context->symbol_table = fcml_fn_symbol_table_alloc();
                    if (!context->symbol_table) {
                        fcml_fn_symbol_free(ast.symbol);
                        fcml_fn_ast_free_node(ast.tree);
                        return FCML_CEH_GEC_OUT_OF_MEMORY;
                    }
                    new_symbol_table = FCML_TRUE;
                }

                error = fcml_fn_parser_add_symbol_to_symbol_table(
                        &(result->errors), context->symbol_table, ast.symbol,
                        context->configuration.override_labels);
                if (error) {
                    fcml_fn_symbol_free(ast.symbol);
                    fcml_fn_ast_free_node(ast.tree);
                    if (new_symbol_table) {
                        fcml_fn_symbol_table_free(context->symbol_table);
                        context->symbol_table = NULL;
                    }
                    return error;
                }
                result->symbol = ast.symbol;
            } else {
                /* Free found symbol. */
                fcml_fn_symbol_free(ast.symbol);
                ast.symbol = NULL;
            }
        } else {
            /* We haven't expected any symbols so error has to be returned. */
            fcml_fn_symbol_free(ast.symbol);
            ast.symbol = NULL;
            fcml_fn_ast_free_node(ast.tree);
            ast.tree = NULL;

            return FCML_CEH_GEC_UNSUPPORTED_LABEL_DECLARATION;
        }
    }

    /* Instruction. */
    if (!error && ast.tree) {

        fcml_st_cif_converter_context cif_ctx;
        cif_ctx.errors = &(result->errors);
        cif_ctx.symbol_table = context->symbol_table;
        cif_ctx.ignore_undefined_symbols =
                context->configuration.ignore_undefined_symbols;

        error = fcml_fn_ast_to_cif_converter(&cif_ctx, ast.tree,
                &(result->instruction));
        if (error) {

            /* Free instruction, because it might haven't been fully parsed.*/
            if (result->instruction) {
                fcml_fn_ast_free_converted_cif(result->instruction);
                result->instruction = NULL;
            }

            /* Defined symbol should also be freed, because we can not leave
             * such symbols to be defined in the main symbols table.
             */
            if (result->symbol) {
                fcml_fn_symbol_remove(context->symbol_table,
                        result->symbol->symbol);
                result->symbol = NULL;
                /* Free symbol table if it has been just allocated. */
                if (new_symbol_table) {
                    fcml_fn_symbol_table_free(context->symbol_table);
                    context->symbol_table = NULL;
                }
            }
        }
    }

    fcml_fn_ast_free_node(ast.tree);

    return error;
}

fcml_ceh_error fcml_fn_parse_to_ast(fcml_st_parser_context *context,
        const fcml_string mnemonic, fcml_st_parser_ast *ast) {
    fcml_st_dialect_context_int *dialect =
            (fcml_st_dialect_context_int*) context->dialect;
    return dialect->instruction_parser(context->ip, mnemonic, ast);
}

void fcml_fn_parser_free_ast(fcml_st_parser_ast *ast) {

    if (ast) {
        /* Free symbol. */
        if (ast->symbol) {
            fcml_fn_env_str_strfree(ast->symbol->symbol);
            fcml_fn_env_memory_free(ast->symbol);
            ast->symbol = NULL;
        }
        /* Free errors and warnings. */
        fcml_fn_ceh_free_errors_only(&(ast->errors));
        /* Free AST tree. */
        if (ast->tree) {
            fcml_fn_ast_free_node(ast->tree);
        }
        ast->tree = NULL;
    }
}

