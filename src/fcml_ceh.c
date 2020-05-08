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

#include <string.h>
#include "fcml_env_int.h"
#include "fcml_ceh.h"

void fcml_fn_ceh_free_error_info(fcml_st_ceh_error_info *error_info) {
    if (error_info) {
        if (error_info->message) {
            fcml_fn_env_str_strfree(error_info->message);
            error_info->message = NULL;
        }
        fcml_fn_env_memory_free(error_info);
    }
}

void fcml_fn_ceh_move_errors(fcml_st_ceh_error_container *destination,
        fcml_st_ceh_error_container *source) {
    if (source != NULL && destination != NULL) {
        /* Clean destination if there are any errors. */
        fcml_fn_ceh_free_errors_only(destination);
        destination->errors = source->errors;
        destination->last_error = source->last_error;
        source->errors = NULL;
        source->last_error = NULL;
    }
}

void fcml_fn_ceh_free_errors_only(fcml_st_ceh_error_container *error_container) {
    if (error_container) {
        fcml_st_ceh_error_info *next = error_container->errors;
        while (next) {
            fcml_st_ceh_error_info *curr = next;
            next = next->next_error;
            fcml_fn_ceh_free_error_info(curr);
        }
        error_container->errors = NULL;
        error_container->last_error = NULL;
    }
}

void fcml_fn_ceh_free_errors_only_with_level(
        fcml_st_ceh_error_container *error_container,
        fcml_en_ceh_error_level level) {
    if (error_container) {
        fcml_st_ceh_error_info **prev = &(error_container->errors);
        fcml_st_ceh_error_info *next = error_container->errors;
        while (next) {
            fcml_st_ceh_error_info *curr = next;
            next = next->next_error;
            if (curr->level == level) {
                *prev = curr->next_error;
                fcml_fn_ceh_free_error_info(curr);
            } else {
                prev = &(curr->next_error);
            }
        }
        if (*prev == NULL) {
            error_container->last_error = NULL;
        }
    }
}

fcml_st_ceh_error_info* fcml_fn_ceh_alloc_error_info(const fcml_string message,
        fcml_ceh_error code, fcml_en_ceh_error_level level) {
    FCML_ENV_ALLOC_CLEAR(error_info, fcml_st_ceh_error_info);
    if (error_info) {
        error_info->message = fcml_fn_env_str_strdup(message);
        if (!error_info->message) {
            fcml_fn_env_memory_free(error_info);
            return NULL;
        }
        error_info->code = code;
        error_info->level = level;
    }
    return error_info;
}

fcml_st_ceh_error_info* fcml_fn_ceh_add_error(
        fcml_st_ceh_error_container *error_container, const fcml_string message,
        fcml_ceh_error code, fcml_en_ceh_error_level level) {

    fcml_st_ceh_error_info *error_info;

    /* Container is null.*/
    if (!error_container) {
        return NULL;
    }

    /* Checks if there is already such error reported. */
    fcml_st_ceh_error_info *current = error_container->errors;
    while (current) {
        if (current->code == code) {
            // Already added.
            return current;
        }
        current = current->next_error;
    }

    error_info = fcml_fn_ceh_alloc_error_info(message, code, level);
    if (!error_info) {
        return NULL;
    }

    fcml_st_ceh_error_info *last_error = error_container->last_error;
    if (last_error) {
        last_error->next_error = error_info;
    } else {
        error_container->errors = error_info;
    }

    error_container->last_error = error_info;

    return error_info;
}
