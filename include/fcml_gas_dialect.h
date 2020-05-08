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

/** @file fcml_gas_dialect.h
 * AT&T dialect implementation.
 * @copyright Copyright (C) 2010-2020 Slawomir Wojtasiak. All rights reserved.
 * This project is released under the GNU Lesser General Public License.
 */

#ifndef FCML_ASM_DIALECT_GAS_H_
#define FCML_ASM_DIALECT_GAS_H_

#include "fcml_lib_export.h"

#include "fcml_errors.h"
#include "fcml_dialect.h"

#ifdef __cplusplus
extern "C" {
#endif

/** Disables "SystemV/386 SVR3.2" compatibility for the non-commutative
 * arithmetic floating point operations with two register operands. */
#define FCML_GAS_DIALECT_CF_SYSV_SVR32_INCOMPATIBLE       0x00000001

/** Default combination of configuration flags. */
#define FCML_GAS_DIALECT_CF_DEFAULT                       0

/**
 * Initializes AT&T dialect.
 * Prepares new instance of AT&T dialect for given set of configuration flags.
 * Every dialect has to be freed using fcml_fn_dialect_free() function.
 *
 * @param config_flags Configuration flags dedicated to the dialect.
 * @param[out] dialect Prepared dialect instance.
 * @return Error code or FCML_CEH_GEC_NO_ERROR.
 * @see fcml_fn_dialect_free
 */
LIB_EXPORT fcml_ceh_error LIB_CALL fcml_fn_dialect_init_gas(
        fcml_uint32_t config_flags, fcml_st_dialect **dialect);

#ifdef __cplusplus
}
#endif

#endif /* FCML_ASM_DIALECT_GAS_H_ */
