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

#include <stddef.h>

#include <fcml_assembler.h>
#include <fcml_choosers.h>

#include "fcml_coll.h"

fcml_ptr LIB_CALL fcml_fn_asm_no_instruction_chooser(
        fcml_st_chooser_context *context) {
    return NULL;
}

fcml_ptr LIB_CALL fcml_fn_asm_default_instruction_chooser(
        fcml_st_chooser_context *context) {
    fcml_st_instruction_code instruction_code;
    fcml_ptr instruction = context->instruction;
    fcml_ptr shortest = NULL;
    fcml_usize shortest_code_length = 0;
    while (instruction) {
        context->extract(instruction, &instruction_code);
        if (!shortest) {
            shortest = instruction;
            shortest_code_length = instruction_code.code_length;
        } else {
            if (instruction_code.code_length < shortest_code_length) {
                shortest = instruction;
                shortest_code_length = instruction_code.code_length;
            }
        }
        instruction = context->next(instruction);
    }
    return shortest;
}
