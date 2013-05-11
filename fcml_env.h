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
typedef void (*fcml_fp_env_memory_free_handler)( void *memory_block );

void fcml_fn_env_register_memory_alloc_handler( fcml_fp_env_memory_alloc_handler function_pointer );

void fcml_fn_env_register_memory_free_handler( fcml_fp_env_memory_free_handler function_pointer );

void *fcml_fn_env_memory_alloc( uint32_t size );

fcml_string fcml_fn_env_memory_strdup( fcml_string str );

fcml_string fcml_fn_env_memory_strldup( fcml_string str, fcml_usize size );

void fcml_fn_env_memory_strfree( fcml_string str );

void fcml_fn_env_memory_free( void *ptr );

#endif /* FCML_ENVIRONMENT_H_ */
