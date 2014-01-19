/*
 * fcml_choosers.c
 *
 *  Created on: Nov 7, 2013
 *      Author: tas
 */

#include <stddef.h>

#include <fcml_assembler.h>
#include <fcml_choosers.h>
#include "fcml_coll.h"

fcml_ptr fcml_fn_asm_no_instruction_chooser( fcml_st_chooser_context *context ) {
    return NULL;
}

fcml_ptr fcml_fn_asm_default_instruction_chooser( fcml_st_chooser_context *context ) {
	fcml_st_instruction_code instruction_code;
	fcml_ptr instruction = context->instruction;
	fcml_ptr *shortest = NULL;
	fcml_usize shortest_code_length = 0;
	while( instruction ) {
	    context->extract( instruction, &instruction_code );
	    if( !shortest ) {
            shortest = instruction;
            shortest_code_length = instruction_code.code_length;
        } else {
            if( instruction_code.code_length < shortest_code_length ) {
                shortest = instruction;
                shortest_code_length = instruction_code.code_length;
            }
        }
	    instruction = context->next( instruction );
	}
	return shortest;
}
