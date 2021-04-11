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

#include "fcml_env_int.h"

#include <fcml_env.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>

static void* default_memory_alloc(fcml_usize size) {
    return malloc((fcml_usize) size);
}

static void* default_memory_realloc(fcml_ptr ptr, fcml_usize size) {
    return realloc(ptr, (fcml_usize) size);
}

static void default_memory_free(fcml_ptr memory_block) {
    free(memory_block);
}

static fcml_fp_env_memory_alloc_handler memory_alloc = default_memory_alloc;
static fcml_fp_env_memory_realloc_handler memory_realloc =
        default_memory_realloc;
static fcml_fp_env_memory_free_handler memory_free = default_memory_free;

fcml_fp_env_memory_alloc_handler LIB_CALL fcml_fn_env_register_memory_alloc_handler(
        fcml_fp_env_memory_alloc_handler handler) {
    fcml_fp_env_memory_alloc_handler tmp = memory_alloc;
    memory_alloc = handler;
    return tmp;
}

fcml_fp_env_memory_realloc_handler LIB_CALL fcml_fn_env_register_memory_realloc_handler(
        fcml_fp_env_memory_realloc_handler handler) {
    fcml_fp_env_memory_realloc_handler tmp = memory_realloc;
    memory_realloc = handler;
    return tmp;
}

fcml_fp_env_memory_free_handler LIB_CALL fcml_fn_env_register_memory_free_handler(
        fcml_fp_env_memory_free_handler handler) {
    fcml_fp_env_memory_free_handler tmp = memory_free;
    memory_free = handler;
    return tmp;
}

fcml_ptr fcml_fn_env_memory_alloc_clear(fcml_usize size) {
    fcml_ptr ptr = fcml_fn_env_memory_alloc(size);
    if (ptr) {
        fcml_fn_env_memory_clear(ptr, size);
    }
    return ptr;
}

fcml_ptr fcml_fn_env_memory_alloc(fcml_usize size) {
    return memory_alloc(size);
}

fcml_ptr fcml_fn_env_memory_realloc(fcml_ptr ptr, fcml_usize size) {
    return memory_realloc(ptr, size);
}

void fcml_fn_env_memory_copy(fcml_ptr dest, const fcml_ptr src,
        fcml_usize len) {
    memcpy(dest, src, (fcml_usize) len);
}

void fcml_fn_env_memory_clear(fcml_ptr src, fcml_usize len) {
    memset(src, 0, (fcml_usize) len);
}

fcml_bool fcml_fn_env_memory_cmp(const fcml_ptr src1,
        const fcml_ptr src2, fcml_usize len) {
    return strncmp((char*) src1, (char*) src2, len) == 0 ?
    FCML_TRUE :
                                                           FCML_FALSE;
}

void fcml_fn_env_memory_free(fcml_ptr ptr) {
    memory_free(ptr);
}

fcml_string fcml_fn_env_str_strldup(const fcml_string str, fcml_usize size) {
    fcml_string new_str = (fcml_string) fcml_fn_env_memory_alloc(size + 1);
    if (new_str) {
        memcpy(new_str, str, (fcml_usize) size);
        new_str[size] = '\0';
    }
    return new_str;
}

fcml_bool fcml_fn_env_str_strblank(const fcml_string str) {
    fcml_usize len = fcml_fn_env_str_strlen(str);
    fcml_int i;
    for (i = 0; i < len; i++) {
        if (!isspace(str[i])) {
            return FCML_FALSE;
        }
    }
    return FCML_TRUE;
}

fcml_usize fcml_fn_env_str_strlen(const fcml_string str) {
    return (fcml_usize) strlen(str);
}

void fcml_fn_env_str_strcpy( fcml_string dst, const fcml_string src) {
    strcpy(dst, src);
}

fcml_bool fcml_fn_env_str_strcmp(const fcml_string src1,
        const fcml_string src2) {
    return !strcmp(src1, src2);
}

void fcml_fn_env_str_strncpy( fcml_string dst, const fcml_string src,
        fcml_usize len) {
    strncpy(dst, src, (fcml_usize) len);
}

fcml_string fcml_fn_env_str_strdup(const fcml_string str) {
    fcml_usize size = (fcml_usize) (strlen(str) + 1);
    fcml_string new_str = (fcml_string) fcml_fn_env_memory_alloc(size);
    if (new_str) {
        memcpy(new_str, str, (fcml_usize) size);
    }
    return new_str;
}

fcml_string fcml_fn_env_str_stralloc(fcml_usize len) {
    return (fcml_string) fcml_fn_env_memory_alloc_clear(len);
}

void fcml_fn_env_str_strclr( fcml_string str) {
    str[0] = '\0';
}

void fcml_fn_env_str_strfree( fcml_string str) {
    if (str) {
        fcml_fn_env_memory_free(str);
    }
}

void fcml_fn_env_str_vsnprintf( fcml_string buffer, fcml_usize maxlen,
        const fcml_string format, va_list args) {
    vsnprintf(buffer, (fcml_usize) maxlen, format, args);
}

void fcml_fn_env_str_snprintf( fcml_string buffer, fcml_usize maxlen,
fcml_string format, ...) {
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, (fcml_usize) maxlen, format, args);
    va_end(args);
}

fcml_bool fcml_fn_env_is_alpha(fcml_char c) {
    return isalpha(c);
}

fcml_bool fcml_fn_env_is_digit(fcml_char c) {
    return isdigit(c);
}

