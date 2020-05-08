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

#include <fcml_errors.h>
#include <fcml_common.h>
#include <fcml_parser.h>

#include "fcml_gas_parser.h"
#include "fcml_ceh.h"
#include "fcml_env_int.h"
#include "fcml_parser_utils.h"
#include "fcml_gas_parser_def.h"
#include "fcml_gas_lexer.h"
#include "fcml_utils.h"
#include "fcml_messages.h"
#include "fcml_parser_int.h"

void gas_error(YYLTYPE *yylloc, struct fcml_st_parser_data *pd,
        const char *error) {
    /* Stores parser error into standard container.*/
    fcml_fn_ceh_add_error(&(pd->errors), (const fcml_string) error,
            FCML_CEH_MEC_ERROR_INVALID_SYNTAX, FCML_EN_CEH_EL_ERROR);
}

void* gas_alloc(yy_size_t size, yyscan_t yyscanner) {
    return fcml_fn_env_memory_alloc((fcml_usize) size);
}

void* gas_realloc(void *ptr, yy_size_t size, yyscan_t yyscanner) {
    return fcml_fn_env_memory_realloc(ptr, (fcml_usize) size);
}

void gas_free(void *ptr, yyscan_t yyscanner) {
    return fcml_fn_env_memory_free(ptr);
}

fcml_ceh_error fcml_fn_gas_parse_instruction_to_ast(fcml_ip ip,
        const fcml_string mnemonic, fcml_st_parser_ast *ast) {

    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

    /* Instruction size is limited to prevent from parser's stack and buffer overflows. */
    if (!mnemonic || !ast
            || fcml_fn_env_str_strlen(mnemonic)
                    > FCML_PARSER_MAX_INSTRUCTION_LEN) {
        return FCML_CEH_GEC_INVALID_INPUT;
    }

    /* Fill instruction pointer. */
    fcml_st_parser_data parser = { 0 };
    parser.ip = ip;

    /* Set up scanner. */
    if (gas_lex_init_extra(&parser, &(parser.scannerInfo))) {
        return FCML_CEH_GEC_OUT_OF_MEMORY;
    }

    gas__scan_string(mnemonic, parser.scannerInfo);

    int yyresult = gas_parse(&parser);

    gas_lex_destroy(parser.scannerInfo);

    ast->errors = parser.errors;
    ast->symbol = parser.symbol;
    ast->tree = parser.tree;

    if (yyresult) {
        switch (yyresult) {
        case 1: /*Syntax error.*/
            error = FCML_CEH_GEC_INVALID_INPUT;
            break;
        case 2: /*Out of memory*/
            error = FCML_CEH_GEC_OUT_OF_MEMORY;
            break;
        }
    }

    return error;
}
