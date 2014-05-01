/*
 * fcml_environment.h
 *
 *  Created on: 05-02-2013
 *      Author: tAs
 */

#ifndef FCML_ENVIRONMENT_H_
#define FCML_ENVIRONMENT_H_

#include <stdarg.h>
#include <fcml_env.h>

#include "fcml_types.h"

/* Memory. */
fcml_ptr fcml_fn_env_memory_alloc( fcml_usize size );
fcml_ptr fcml_fn_env_memory_alloc_clear( fcml_usize size );
void fcml_fn_env_memory_copy( fcml_ptr dest, const fcml_ptr src, fcml_usize len );
void fcml_fn_env_memory_clear( fcml_ptr src, fcml_usize len );
fcml_bool fcml_fn_env_memory_cmp( const fcml_ptr src1, const fcml_ptr src2, fcml_usize len );
void fcml_fn_env_memory_free( fcml_ptr ptr );

/* Strings. */
fcml_bool fcml_fn_env_str_strblank( const fcml_string str );
fcml_usize fcml_fn_env_str_strlen( const fcml_string str );
fcml_string fcml_fn_env_str_stralloc( fcml_usize len );
fcml_string fcml_fn_env_str_strdup( const fcml_string str );
void fcml_fn_env_str_strcpy( fcml_string src, const fcml_string dst );
fcml_bool fcml_fn_env_str_strcmp( const fcml_string src1, const fcml_string src2 );
void fcml_fn_env_str_strncpy( fcml_string dst, const fcml_string src, fcml_usize len );
void fcml_fn_env_str_strclr( fcml_string str );
fcml_string fcml_fn_env_str_strldup( const fcml_string str, fcml_usize size );
void fcml_fn_env_str_strfree( fcml_string str );
void fcml_fn_env_str_vsnprintf( fcml_string buffer, fcml_usize maxlen, fcml_string format, va_list args );
void fcml_fn_env_str_snprintf( fcml_string buffer, fcml_usize maxlen, fcml_string format, ... );

/* Characters. */
fcml_bool fcml_fn_env_is_alpha( fcml_char c );
fcml_bool fcml_fn_env_is_digit( fcml_char c );

#endif /* FCML_ENVIRONMENT_H_ */
