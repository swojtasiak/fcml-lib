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

#include <fcml_renderer.h>

#include "fcml_stream.h"
#include "fcml_dialect_int.h"
#include "fcml_trace.h"
#include "fcml_env_int.h"

fcml_ceh_error LIB_CALL fcml_fn_render(const fcml_st_dialect *dialect,
        const fcml_st_render_config *config, fcml_char *buffer,
        fcml_usize buffer_len,
        const fcml_st_disassembler_result *result) {

    fcml_st_memory_stream output_stream;
    output_stream.base_address = buffer;
    output_stream.offset = 0;
    output_stream.size = buffer_len;

    fcml_st_dialect_context_int *dialect_context_int =
            (fcml_st_dialect_context_int*)dialect;
    if (dialect_context_int->instruction_renderer) {
        fcml_fnp_render_instruction renderer = (fcml_fnp_render_instruction)
                dialect_context_int->instruction_renderer;
        return renderer( dialect, config, &output_stream, result );
    } else {
        /* Dialect not initialized correctly.*/
        FCML_TRACE_MSG("Rendering not supported by current dialect.");
        return FCML_CEH_GEC_FEATURE_NOT_SUPPORTED;
    }

}
