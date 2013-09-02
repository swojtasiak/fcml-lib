/*
 * fcml_environment.c
 *
 *  Created on: 05-02-2013
 *      Author: tAs
 */

#include <stdlib.h>
#include <string.h>

#include "fcml_env.h"

static void *fcml_fn_env_default_memory_alloc( uint32_t size ) {
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

void *fcml_fn_env_clear_memory_alloc( uint32_t size ) {
	fcml_ptr ptr = fcml_fn_env_memory_alloc( size );
	if( ptr ) {
		fcml_mem_clear( ptr, size );
	}
	return ptr;
}

void fcml_mem_clear( fcml_ptr ptr, fcml_usize size ) {
	memset( ptr, 0, size );
}

void *fcml_fn_env_memory_alloc( uint32_t size ) {
    return fcml_gl_fp_memory_alloc(size);
}

void fcml_fn_env_memory_copy( void *dest, const void *src, fcml_usize len ) {
	memcpy( dest, src, len );
}

void fcml_fn_env_memory_clean( void *src, fcml_usize len ) {
	memset( src, 0, len );
}

void fcml_fn_env_memory_free( void *ptr ) {
    fcml_gl_fp_memory_free(ptr);
}

fcml_string fcml_fn_env_memory_strldup( fcml_string str, fcml_usize size ) {
	// TODO: Unicode support.
	fcml_string new_str = fcml_fn_env_memory_alloc( size + 1 );
	if( new_str ) {
		memcpy( new_str, str, size );
		new_str[size] = '\0';
	}
	return new_str;
}

fcml_usize fcml_fn_env_memory_strlen( fcml_string str ) {
    return (fcml_usize)strlen( str );
}

fcml_string fcml_fn_env_memory_strdup( fcml_string str ) {
	uint32_t size = strlen( str ) + 1;
	fcml_string new_str = fcml_fn_env_memory_alloc( size );
	if( new_str ) {
		memcpy( new_str, str, size );
	}
	return new_str;
}

void fcml_fn_env_memory_strfree( fcml_string str ) {
	fcml_fn_env_memory_free( str );
}


