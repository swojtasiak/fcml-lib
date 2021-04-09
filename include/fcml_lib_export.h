/*
 * FCML - Free Code Manipulation Library.
 * Copyright (C) 2010-2021 Slawomir Wojtasiak
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

/** @file fcml_lib_export.h
 * Handles Win32 DLL symbols importing/exporting.
 * The only interesting thing here is the LIBFCML_DLL_IMPORT symbol which has to
 * be always defined in order to use dynamic DLL under Windows. You can achieve it
 * by declaring the symbol before this header file is included. For example:
 * @code
 *     #define LIBFCML_DLL_IMPORT
 *     #include <fcml_lib_export.h>
 * @endcode
 * Take into account that this header file is included by every FCML public header, so
 * in fact you should define the symbol before including anything from the FCML library.
 * This declaration can be omitted as long as you use undecorated symbol names.
 *
 * @copyright Copyright (C) 2010-2021 Slawomir Wojtasiak. All rights reserved.
 * This project is released under the GNU Lesser General Public License.
 */

#ifndef FCML_LIB_EXPORT_H_
#define FCML_LIB_EXPORT_H_

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#if _WIN32 || __CYGWIN__
#define LIB_CALL   __stdcall
#ifdef DLL_EXPORT
#define LIB_EXPORT __declspec(dllexport)
#else
#ifdef LIBFCML_DLL_IMPORT
#define LIB_EXPORT __declspec(dllimport)
#endif
#endif
#endif

#ifndef LIB_EXPORT
#ifdef SUPPORT_VISIBILITY_HIDDEN
#define LIB_EXPORT __attribute__((visibility("default")))
#else
#define LIB_EXPORT
#endif
#endif

#ifndef LIB_CALL
#define LIB_CALL
#endif

#endif /* FCML_LIB_EXPORT_H_ */
