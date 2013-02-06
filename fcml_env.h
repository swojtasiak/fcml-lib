/*
 * fcml_environment.h
 *
 *  Created on: 05-02-2013
 *      Author: tAs
 */

#ifndef FCML_ENVIRONMENT_H_
#define FCML_ENVIRONMENT_H_

#include <stdint.h>

// Memory allocator function pointer.
typedef void *(*fcml_fp_env_memory_alloc_handler)( uint32_t size );

// Memory deallocator function pointer.
typedef void (*fcml_fp_env_memory_free_handler)( void *memory_block );

void fcml_fn_env_register_memory_alloc_handler( fcml_fp_env_memory_alloc_handler function_pointer );

void fcml_fn_env_register_memory_free_handler( fcml_fp_env_memory_free_handler function_pointer );

void *fcml_fn_env_memory_alloc( uint32_t size );

void fcml_fn_env_memory_free( void *address );

#endif /* FCML_ENVIRONMENT_H_ */
