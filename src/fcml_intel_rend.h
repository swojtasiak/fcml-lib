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

#ifndef FCML_INTEL_REND_H_
#define FCML_INTEL_REND_H_

#include <fcml_types.h>
#include <fcml_dialect.h>
#include <fcml_disassembler.h>
#include <fcml_renderer.h>
#include <fcml_errors.h>

#include "fcml_stream.h"

fcml_ceh_error fcml_fn_rend_render_instruction_intel(
        const fcml_st_dialect *dialect_context,
        const fcml_st_render_config *config,
        fcml_st_memory_stream *output_stream,
        const fcml_st_disassembler_result *result);

#endif /* FCML_INTEL_REND_H_ */
