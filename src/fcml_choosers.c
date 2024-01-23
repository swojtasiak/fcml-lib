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

struct instruction_holder {
    fcml_ptr instruction;
    fcml_usize code_length;
};

fcml_ptr LIB_CALL fcml_fn_asm_no_instruction_chooser(
        fcml_st_chooser_context *context) {
    return NULL;
}

static void fcml_ifn_replace_shortest(struct instruction_holder *shortest, 
    fcml_ptr instruction, fcml_st_instruction_code *instruction_code) {
    if (!shortest->instruction || 
            instruction_code->code_length < shortest->code_length) {
        shortest->instruction = instruction;
        shortest->code_length = instruction_code->code_length;
    }
}

fcml_ptr LIB_CALL fcml_fn_asm_default_instruction_chooser(
        fcml_st_chooser_context *context) {
    fcml_st_instruction_code instruction_code;
    fcml_ptr instruction = context->instruction;

    struct instruction_holder shortest = {0};
    struct instruction_holder shortest_no_override = {0};

    while (instruction) {
        context->extract(instruction, &instruction_code);

        /* Keep the shortest GPI instruction which doesn't override anything. */
        if ((instruction_code.details.instruction_group & FCML_AMT_GPI) != 0 &&
            !instruction_code.details.osa_override && 
            !instruction_code.details.asa_override) {
            fcml_ifn_replace_shortest(&shortest_no_override, instruction, 
                &instruction_code);
        }

        fcml_ifn_replace_shortest(&shortest, instruction, &instruction_code);

        instruction = context->next(instruction);
    }

    /* Return the shortest instruction which doesn't override ASA and OSA
       if there is any. */
    if (shortest_no_override.instruction != NULL) {
        return shortest_no_override.instruction;
    }

    return shortest.instruction;
}
