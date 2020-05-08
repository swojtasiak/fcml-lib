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

/** @file fcml_dialect.h
 * Structures and functions related to dialects.
 * Functions and structures used for developing new dialects are not exposed
 * as public API. If you are interested in implementing another dialect
 * you have to use internal headers.
 *
 * @copyright Copyright (C) 2010-2020 Slawomir Wojtasiak. All rights reserved.
 * This project is released under the GNU Lesser General Public License.
 */

#ifndef FCML_DIALECT_H_
#define FCML_DIALECT_H_

#include "fcml_lib_export.h"

/** Assembler dialect.*/
typedef struct fcml_st_dialect fcml_st_dialect;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Frees dialect instance.
 * Frees all resources occupied by the dialect instance.
 * @param dialect Dialect to be freed.
 */
LIB_EXPORT void LIB_CALL fcml_fn_dialect_free( fcml_st_dialect *dialect );

#ifdef __cplusplus
}
#endif

#endif /* FCML_DIALECT_H_ */
