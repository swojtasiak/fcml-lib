/*
 * FCML - Free Code Manipulation Library.
 * Copyright (C) 2010-2017 Slawomir Wojtasiak
 * 
 * This piece of software is available under LGPL or Apache License.
 * 
 * Linkage exception:
 *
 * You are permitted to build hsdis binaries and link them statically
 * with fcml-lib and still release these binaries under Apache License
 * without need to distribute the source code.
 *
 * LGPL:
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
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301
 * USA
 *
 * Apache License:
 * 
 * Copyright 2010-2017 Sławomir Wojtasiak
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef FCML_HSDIS_H_
#define FCML_HSDIS_H_

#include <fcml_types.h>

#ifdef FCML_MSCC
#ifdef HSDIS_EXPORT_DLL
#define HSDIS_API __declspec(dllexport)
#endif
#ifdef HSDIS_IMPORT_DLL
#define HSDIS_API __declspec(dllimport)
#endif
#endif

#ifndef HSDIS_API
#define HSDIS_API
#endif

#ifdef FCML_MSCC
#define HSDIS_CALL  __cdecl
#else
#define HSDIS_CALL
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef void* (*jvm_event_callback) (void *env_pv, const char *ev, void *arg);
typedef int   (*jvm_printf_callback)(void *env_pv, const char *format, ...);

/* Called directly by jvm.so/jvm.dll. */
HSDIS_API void* HSDIS_CALL decode_instructions( void* start, void* end, jvm_event_callback,
        void* event_stream, jvm_printf_callback, void* printf_stream, const char* options );

#ifdef __cplusplus
}
#endif

#endif /* FCML_HSDIS_H_ */
