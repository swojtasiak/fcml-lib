/*
 * fcml_environment.c
 *
 *  Created on: 05-02-2013
 *      Author: tAs
 */

#include "fcml_env.h"

#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>

static void *fcml_fn_env_default_memory_alloc( fcml_usize size ) {
    return malloc(size);
}

static void fcml_fp_env_default_memory_free( void *memory_block ) {
    free( memory_block );
}

static fcml_fp_env_memory_alloc_handler fcml_gl_fp_memory_alloc = fcml_fn_env_default_memory_alloc;

static fcml_fp_env_memory_free_handler fcml_gl_fp_memory_free = fcml_fp_env_default_memory_free;

void fcml_fn_env_register_memory_alloc_handler( fcml_fp_env_memory_alloc_handler function_pointer ) {
    fcml_gl_fp_memory_alloc = function_pointer;
}

void fcml_fn_env_register_memory_free_handler( fcml_fp_env_memory_free_handler function_pointer ) {
    fcml_gl_fp_memory_free = function_pointer;
}

fcml_ptr fcml_fn_env_memory_alloc_clear( fcml_usize size ) {
	fcml_ptr ptr = fcml_fn_env_memory_alloc( size );
	if( ptr ) {
		fcml_fn_env_memory_clear( ptr, size );
	}
	return ptr;
}

fcml_ptr fcml_fn_env_memory_alloc( fcml_usize size ) {
    return fcml_gl_fp_memory_alloc(size);
}

void fcml_fn_env_memory_copy( fcml_ptr dest, const fcml_ptr src, fcml_usize len ) {
	memcpy( dest, src, len );
}

void fcml_fn_env_memory_clear( fcml_ptr src, fcml_usize len ) {
	memset( src, 0, len );
}

fcml_bool fcml_fn_env_memory_cmp( const fcml_ptr src1, const fcml_ptr src2, fcml_usize len ) {
    return strncmp( (char *)src1, (char *)src2, len ) == 0 ? FCML_TRUE : FCML_FALSE;
}

void fcml_fn_env_memory_free( fcml_ptr ptr ) {
    fcml_gl_fp_memory_free(ptr);
}

fcml_string fcml_fn_env_str_strldup( const fcml_string str, fcml_usize size ) {
	fcml_string new_str = (fcml_string)fcml_fn_env_memory_alloc( size + 1 );
	if( new_str ) {
		memcpy( new_str, str, size );
		new_str[size] = '\0';
	}
	return new_str;
}

fcml_bool fcml_fn_env_str_strblank( const fcml_string str ) {
	fcml_usize len = fcml_fn_env_str_strlen( str );
	fcml_int i;
	for( i = 0; i < len; i++ ) {
		if( !isspace( str[i] ) ) {
			return FCML_FALSE;
		}
	}
	return FCML_TRUE;
}

fcml_usize fcml_fn_env_str_strlen( const fcml_string str ) {
    return (fcml_usize)strlen( str );
}

void fcml_fn_env_str_strcpy( fcml_string dst, const fcml_string src ) {
	strcpy( dst, src );
}

fcml_bool fcml_fn_env_str_strcmp( const fcml_string src1, const fcml_string src2 ) {
	return !strcmp( src1, src2 );
}

void fcml_fn_env_str_strncpy( fcml_string dst, const fcml_string src, fcml_usize len ) {
    strncpy( dst, src, len );
}

fcml_string fcml_fn_env_str_strdup( const fcml_string str ) {
	fcml_usize size = strlen( str ) + 1;
	fcml_string new_str = (fcml_string)fcml_fn_env_memory_alloc( size );
	if( new_str ) {
		memcpy( new_str, str, size );
	}
	return new_str;
}

fcml_string fcml_fn_env_str_stralloc( fcml_usize len ) {
    return (fcml_string)fcml_fn_env_memory_alloc_clear( len );
}

void fcml_fn_env_str_strclr( fcml_string str ) {
    str[0] = '\0';
}

void fcml_fn_env_str_strfree( fcml_string str ) {
	if( str ) {
		fcml_fn_env_memory_free( str );
	}
}

void fcml_fn_env_str_vsnprintf( fcml_string buffer, fcml_usize maxlen, fcml_string format, va_list args ) {
	vsnprintf( buffer, maxlen, format, args );
}

void fcml_fn_env_str_snprintf( fcml_string buffer, fcml_usize maxlen, fcml_string format, ... ) {
	va_list args;
	va_start( args, format );
	vsnprintf( buffer, maxlen, format, args );
	va_end( args );
}

fcml_bool fcml_fn_env_is_alpha( fcml_char c ) {
	return isalpha( c );
}

fcml_bool fcml_fn_env_is_digit( fcml_char c ) {
    return isdigit( c );
}

