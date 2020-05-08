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

#ifndef FCML_ENVIRONMENT_H_
#define FCML_ENVIRONMENT_H_

#include <stdarg.h>
#include <fcml_env.h>

#include "fcml_types.h"

/* Memory. */

#define FCML_ENV_ALLOC_ST(str)   (str*) \
    fcml_fn_env_memory_alloc_clear(sizeof(str));

#define FCML_ENV_ALLOC_CLEAR(variable, type) type* variable = (type*) \
    fcml_fn_env_memory_alloc_clear(sizeof(type))

/* Memory allocation. */
fcml_ptr fcml_fn_env_memory_alloc(fcml_usize size);

fcml_ptr fcml_fn_env_memory_realloc(fcml_ptr ptr, fcml_usize size);

fcml_ptr fcml_fn_env_memory_alloc_clear(fcml_usize size);

void fcml_fn_env_memory_copy(fcml_ptr dest, const fcml_ptr src, fcml_usize len);

void fcml_fn_env_memory_clear(fcml_ptr src, fcml_usize len);

fcml_bool fcml_fn_env_memory_cmp(const fcml_ptr src1, const fcml_ptr src2,
        fcml_usize len);

void fcml_fn_env_memory_free(fcml_ptr ptr);

/* Strings. */
fcml_bool fcml_fn_env_str_strblank(const fcml_string str);

fcml_usize fcml_fn_env_str_strlen(const fcml_string str);

fcml_string fcml_fn_env_str_stralloc(fcml_usize len);

fcml_string fcml_fn_env_str_strdup(const fcml_string str);

void fcml_fn_env_str_strcpy( fcml_string src, const fcml_string dst);

fcml_bool fcml_fn_env_str_strcmp(const fcml_string src1,
        const fcml_string src2);

void fcml_fn_env_str_strncpy( fcml_string dst, const fcml_string src,
        fcml_usize len);

void fcml_fn_env_str_strclr( fcml_string str);

fcml_string fcml_fn_env_str_strldup(const fcml_string str, fcml_usize size);

void fcml_fn_env_str_strfree( fcml_string str);

void fcml_fn_env_str_vsnprintf( fcml_string buffer, fcml_usize maxlen,
        const fcml_string format, va_list args);

void fcml_fn_env_str_snprintf( fcml_string buffer, fcml_usize maxlen,
        fcml_string format, ...);

/* Characters. */
fcml_bool fcml_fn_env_is_alpha(fcml_char c);
fcml_bool fcml_fn_env_is_digit(fcml_char c);

#endif /* FCML_ENVIRONMENT_H_ */
