/*
 * fcml_environment.h
 *
 *  Created on: 05-02-2013
 *      Author: tAs
 */

#ifndef FCML_ENVIRONMENT_H_
#define FCML_ENVIRONMENT_H_

#include <stdint.h>
#include "fcml_types.h"

// Memory allocator function pointer.
typedef void *(*fcml_fp_env_memory_alloc_handler)( uint32_t size );
// Memory deallocator function pointer.
typedef void (*fcml_fp_env_memory_free_handler)( fcml_ptr memory_block );

// Memory related operations.

void fcml_fn_env_register_memory_alloc_handler( fcml_fp_env_memory_alloc_handler function_pointer );
void fcml_fn_env_register_memory_free_handler( fcml_fp_env_memory_free_handler function_pointer );
void *fcml_fn_env_memory_alloc( uint32_t size );
void *fcml_fn_env_clear_memory_alloc( uint32_t size );
void fcml_fn_env_memory_copy( void *dest, const void *src, fcml_usize len );
void fcml_fn_env_memory_clean( void *src, fcml_usize len );
void fcml_mem_clear( fcml_ptr ptr, fcml_usize size );
fcml_usize fcml_fn_env_memory_strlen( fcml_string str );
fcml_string fcml_fn_env_memory_stralloc( fcml_usize len );
fcml_string fcml_fn_env_memory_strdup( fcml_string str );
void fcml_fn_env_memory_strcpy( fcml_string src, fcml_string dst );
void fcml_fn_env_memory_strncpy( const fcml_string dst, fcml_string src, fcml_usize len );
void fcml_fn_env_memory_strclr( fcml_string str );
fcml_string fcml_fn_env_memory_strldup( fcml_string str, fcml_usize size );
void fcml_fn_env_memory_strfree( fcml_string str );
void fcml_fn_env_memory_free( void *ptr );

// Characters.

fcml_bool fcml_fn_env_is_alpha( fcml_char c );
fcml_bool fcml_fn_env_is_digit( fcml_char c );

#endif /* FCML_ENVIRONMENT_H_ */
