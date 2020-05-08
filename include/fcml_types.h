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

/** @file fcml_types.h
 * Types declarations.
 *
 * @copyright Copyright (C) 2010-2020 Slawomir Wojtasiak. All rights reserved.
 * This project is released under the GNU Lesser General Public License.
 */

#ifndef FCML_TYPES_H_
#define FCML_TYPES_H_

/* If config.h is available, we depend on it; otherwise we give
 * the responsibility to handle headers appropriately to the compiler runtime.
 **/
#ifdef HAVE_CONFIG_H
#include <config.h>
#ifdef HAVE_STDDEF_H
#include <stddef.h>
#endif
#if HAVE_STDINT_H
#include <stdint.h>
#endif
#if HAVE_INTTYPES_H
#include <inttypes.h>
#endif
#else
#if defined(_MSC_VER) && defined(_WIN32)
#include <windows.h>
#define FCML_MSCC
/* Disable unit specific lexer features. */
#define YY_NO_INPUT 1
#define YY_NO_UNISTD_H 1
#else
#include <stddef.h>
#include <stdint.h>
#include <inttypes.h>
#endif
#endif

#include "fcml_lib_export.h"

/** Used to code literal strings. It will be useful if FCML supports UNICODE in the future.  */
#define FCML_TEXT(x)	x
#define _FT(x)			FCML_TEXT(x)

#ifdef FCML_MSCC

#define FCML_PRI_INT8_DEC	"%d"
#define FCML_PRI_INT16_DEC	"%d"
#define FCML_PRI_INT32_DEC	"%d"
#define FCML_PRI_INT64_DEC	"%lld"

#define FCML_PRI_UINT8_DEC	"%u"
#define FCML_PRI_UINT16_DEC	"%u"
#define FCML_PRI_UINT32_DEC	"%u"
#define FCML_PRI_UINT64_DEC	"%llu"

#define FCML_PRI_INT8_HEX	"%02x"
#define FCML_PRI_INT16_HEX	"%04x"
#define FCML_PRI_INT32_HEX	"%08x"
#define FCML_PRI_INT64_HEX	"%016llx"

#define FCML_PRI_INT8_HEX_NO_ZEROS	"%x"
#define FCML_PRI_INT16_HEX_NO_ZEROS	"%x"
#define FCML_PRI_INT32_HEX_NO_ZEROS	"%x"
#define FCML_PRI_INT64_HEX_NO_ZEROS	"%llx"

typedef int fcml_int;
typedef int fcml_bool;
typedef __int8 fcml_int8_t;
typedef unsigned __int8 fcml_uint8_t;
typedef __int16 fcml_int16_t;
typedef unsigned __int16 fcml_uint16_t;
typedef __int32 fcml_int32_t;
typedef unsigned __int32 fcml_uint32_t;
typedef __int64 fcml_int64_t;
typedef unsigned __int64 fcml_uint64_t;

/* Signed integers. */
#define FCML_INT64_MAX	_I64_MAX
#define FCML_INT64_MIN	_I64_MIN
#define FCML_INT32_MAX	INT_MAX
#define FCML_INT32_MIN	INT_MIN
#define FCML_INT16_MAX	SHRT_MAX
#define FCML_INT16_MIN	SHRT_MIN
#define FCML_INT8_MAX	SCHAR_MAX
#define FCML_INT8_MIN	SCHAR_MIN

/* Unsigned integers. */
#define FCML_UINT8_MAX	UCHAR_MAX
#define FCML_UINT16_MAX	USHRT_MAX
#define FCML_UINT32_MAX	UINT_MAX
#define FCML_UINT64_MAX	_UI64_MAX

#else

#ifdef PRId8
#define FCML_PRI_INT8_DEC	"%" PRId8
#endif
#ifdef PRId16
#define FCML_PRI_INT16_DEC	"%" PRId16
#endif
#ifdef PRId32
#define FCML_PRI_INT32_DEC	"%" PRId32
#endif
#ifdef PRId64
#define FCML_PRI_INT64_DEC	"%" PRId64
#endif

#ifdef PRIu8
#define FCML_PRI_UINT8_DEC	"%" PRIu8
#endif
#ifdef PRIu16
#define FCML_PRI_UINT16_DEC	"%" PRIu16
#endif
#ifdef PRIu32
#define FCML_PRI_UINT32_DEC	"%" PRIu32
#endif
#ifdef PRIu64
#define FCML_PRI_UINT64_DEC	"%" PRIu64
#endif

#ifdef PRIx8
#define FCML_PRI_INT8_HEX	"%02" PRIx8
#endif
#ifdef PRIx16
#define FCML_PRI_INT16_HEX	"%04" PRIx16
#endif
#ifdef PRIx32
#define FCML_PRI_INT32_HEX	"%08" PRIx32
#endif
#ifdef PRIx64
#define FCML_PRI_INT64_HEX	"%016" PRIx64
#endif

#ifdef PRIx8
#define FCML_PRI_INT8_HEX_NO_ZEROS	"%" PRIx8
#endif
#ifdef PRIx16
#define FCML_PRI_INT16_HEX_NO_ZEROS	"%" PRIx16
#endif
#ifdef PRIx32
#define FCML_PRI_INT32_HEX_NO_ZEROS	"%" PRIx32
#endif
#ifdef PRIx64
#define FCML_PRI_INT64_HEX_NO_ZEROS	"%" PRIx64
#endif

typedef int fcml_int;
typedef unsigned int fcml_uint;
typedef int fcml_bool;
typedef int8_t fcml_int8_t;
typedef uint8_t fcml_uint8_t;
typedef int16_t fcml_int16_t;
typedef uint16_t fcml_uint16_t;
typedef int32_t fcml_int32_t;
typedef uint32_t fcml_uint32_t;
typedef int64_t fcml_int64_t;
typedef uint64_t fcml_uint64_t;

/* Signed integers. */
#define FCML_INT64_MAX	INT64_MAX
#define FCML_INT64_MIN	INT64_MIN
#define FCML_INT32_MAX	INT32_MAX
#define FCML_INT32_MIN	INT32_MIN
#define FCML_INT16_MAX	INT16_MAX
#define FCML_INT16_MIN	INT16_MIN
#define FCML_INT8_MAX	INT8_MAX
#define FCML_INT8_MIN	INT8_MIN

/* Unsigned integers. */
#define FCML_UINT8_MAX	UINT8_MAX
#define FCML_UINT16_MAX	UINT16_MAX
#define FCML_UINT32_MAX	UINT32_MAX
#define FCML_UINT64_MAX	UINT64_MAX

#endif

typedef char  fcml_char;
#define fcml_string char*
typedef float fcml_float;
typedef void* fcml_ptr;
typedef fcml_uint32_t fcml_flags;

typedef fcml_uint32_t fcml_usize;
typedef fcml_int32_t fcml_size;

#define FCML_TRUE		1
#define FCML_FALSE		0

/* Macro for bit manipulations. */

#define FCML_TP_SET_BIT(x,y)	( ( x ) | ( 0x01 << ( y ) ) )
#define FCML_TP_GET_BIT(x,y)	( ( x >> y ) & 0x01 )
#define FCML_TP_CLEAR_BIT(x,y)  ( ( x ) &= ~( 1 << ( y ) ) )

/* Nulleable types. */

typedef struct fcml_nuint8_t {
    fcml_uint8_t value;
    fcml_bool is_not_null;
} fcml_nuint8_t;

typedef struct fcml_nuint16_t {
    fcml_uint16_t value;
    fcml_bool is_not_null;
} fcml_nuint16_t;

typedef struct fcml_nuint32_t {
    fcml_uint32_t value;
    fcml_bool is_not_null;
} fcml_nuint32_t;

typedef struct fcml_nuint64_t {
    fcml_uint64_t value;
    fcml_bool is_not_null;
} fcml_nuint64_t;

typedef struct fcml_nint8_t {
    fcml_int8_t value;
    fcml_bool is_not_null;
} fcml_nint8_t;

typedef struct fcml_nint16_t {
    fcml_int16_t value;
    fcml_bool is_not_null;
} fcml_nint16_t;

typedef struct fcml_nint32_t {
    fcml_int32_t value;
    fcml_bool is_not_null;
} fcml_nint32_t;

typedef struct fcml_nint64_t {
    fcml_int64_t value;
    fcml_bool is_not_null;
} fcml_nint64_t;

typedef struct fcml_st_integer {
    fcml_usize size;
    fcml_bool is_signed;
    // Data fields.
    fcml_int8_t int8;
    fcml_int16_t int16;
    fcml_int32_t int32;
    fcml_int64_t int64;
} fcml_st_integer;

#define FCML_SET_VALUE(x, y) x.value = y; x.is_not_null = FCML_TRUE;
#define FCML_SET_NULL(x)     x.value = 0; x.is_not_null = FCML_FALSE;
#define FCML_IS_NULL(x)      ((x).is_not_null == FCML_FALSE)

#endif /* FCML_TYPES_H_ */
