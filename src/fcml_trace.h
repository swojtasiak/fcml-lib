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

#ifndef FCML_TRACE_H_
#define FCML_TRACE_H_

#include "stdio.h"

#ifdef FCML_DEBUG
#define FCML_TRACE(pattern, ...) { printf("%s:%d ", __FILE__,  __LINE__); printf(pattern, ##__VA_ARGS__); printf("\n");}
#define FCML_TRACE_MSG(msg) { printf("%s:%d ", __FILE__,  __LINE__); printf("%s\n", msg); }
#else
#define FCML_TRACE(pattern, ...)
#define FCML_TRACE_MSG(msg)
#endif

#endif /* FCML_TRACE_H_ */
