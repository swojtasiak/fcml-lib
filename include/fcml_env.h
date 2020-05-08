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

/** @file fcml_env.h
 * API for environment configuration.
 * @copyright Copyright (C) 2010-2020 Slawomir Wojtasiak. All rights reserved.
 * This project is released under the GNU Lesser General Public License.
 */

#ifndef FCML_ENV_H_
#define FCML_ENV_H_

#include "fcml_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/** Memory allocator handler function pointer declaration.
 * Memory allocation handlers are used to allocate requested memory in
 * environment specific way.
 * @param size Size of the memory to allocate.
 * @return The allocated memory block or NULL in case of out of memory.
 */
typedef fcml_ptr (*fcml_fp_env_memory_alloc_handler)(fcml_usize size);

/** Memory reallocator handler function pointer declaration.
 * Memory reallocation handlers are used to reallocate requested memory in
 * environment specific way.
 * @param ptr The memory block to be reallocated.
 * @param size Size of the memory to allocate.
 * @return The reallocated memory block or NULL in case of out of memory.
 */
typedef fcml_ptr (*fcml_fp_env_memory_realloc_handler)(fcml_ptr ptr,
        fcml_usize size);

/** Memory deallocator handler function pointer declaration.
 * Memory deallocation handlers are used to free requested memory blocks in
 * environment specific way.
 * @param memory_block The memory block to free.
 */
typedef void (*fcml_fp_env_memory_free_handler)(fcml_ptr memory_block);

/**
 * Registers the new dedicated handler responsible for allocating
 * memory for the sake of internal FCML implementation.
 * @param handler New memory allocation handler.
 * @return The replaced memory handler.
 */
LIB_EXPORT fcml_fp_env_memory_alloc_handler LIB_CALL
    fcml_fn_env_register_memory_alloc_handler(
        fcml_fp_env_memory_alloc_handler handler);

/**
 * Registers the new dedicated handler responsible for reallocating
 * memory for the sake
 * of internal FCML implementation.
 * @param handler New memory reallocation handler.
 * @return The replaced memory handler.
 */
LIB_EXPORT fcml_fp_env_memory_realloc_handler LIB_CALL
    fcml_fn_env_register_memory_realloc_handler(
        fcml_fp_env_memory_realloc_handler handler);

/**
 * Registers the new dedicated handler responsible for deallocating the
 * memory for the sake
 * of internal FCML implementation.
 * @param handler New memory deallocation handler.
 * @return The replaced memory handler.
 */
LIB_EXPORT fcml_fp_env_memory_free_handler LIB_CALL
    fcml_fn_env_register_memory_free_handler(
        fcml_fp_env_memory_free_handler handler);

#ifdef __cplusplus
}
#endif

#endif /* FCML_ENV_H_ */
