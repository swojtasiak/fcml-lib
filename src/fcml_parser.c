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

#include "fcml_parser.h"

#include <fcml_errors.h>
#include <fcml_common.h>
#include <fcml_symbols.h>

#include "fcml_dialect_int.h"
#include "fcml_apc_ast.h"
#include "fcml_env_int.h"
#include "fcml_trace.h"
#include "fcml_parser_int.h"
#include "fcml_utils.h"

fcml_ceh_error LIB_CALL fcml_fn_parse(fcml_st_parser_context *context,
        const fcml_string instruction, fcml_st_parser_result *result_out) {

    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
    fcml_st_dialect_context_int *dialect_context_int =
            (fcml_st_dialect_context_int*) context->dialect;

    if (dialect_context_int->instruction_parser) {
        /* Call parser instance associated with given dialect. */
        error = fcml_fn_parse_to_cif(context, instruction, result_out);
    } else {
        /* Dialect not initialized correctly.*/
        FCML_TRACE_MSG("Parsing not supported by current dialect.");
        error = FCML_CEH_GEC_FEATURE_NOT_SUPPORTED;
    }
    if (error) {
        // Try to convert error code to error message if there is such need.
        fcml_fn_utils_conv_gec_to_error_info(
                context->configuration.enable_error_messages,
                &(result_out->errors), error);
    }
    return error;
}

void LIB_CALL fcml_fn_parser_result_free(fcml_st_parser_result *result) {
    if (result) {
        /* Frees parsed instruction, potential errors and warnings and result structure itself.*/
        if (result->instruction) {
            fcml_fn_ast_free_converted_cif(result->instruction);
            result->instruction = NULL;
        }
        /* Symbol can not be free, because it is managed by symbols
         * table, but of course we have to zero it.
         */
        result->symbol = NULL;
        fcml_fn_ceh_free_errors_only(&(result->errors));
    }
}

void LIB_CALL fcml_fn_parser_result_prepare(fcml_st_parser_result *result) {
    if (result) {
        result->errors.errors = NULL;
        result->errors.last_error = NULL;
        result->instruction = NULL;
    }
}
