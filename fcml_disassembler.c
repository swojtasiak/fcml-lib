/*
 * fcml_disassembler.c
 *
 *  Created on: Oct 13, 2013
 *      Author: tas
 */

#include "fcml_disassembler.h"
#include "fcml_asm_decoding.h"
#include "fcml_env.h"

fcml_ceh_error fcml_fn_disassembler_init( fcml_st_dialect_context context, fcml_st_disassembler **disassembler ) {
	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

	*disassembler = fcml_fn_env_memory_alloc( sizeof( fcml_st_disassembler ) );
	if( *disassembler ) {
		error = fcml_fn_asm_init_instruction_decodings( &context, disassembler );
	} else {
		error = FCML_CEH_GEC_OUT_OF_MEMORY;
	}

	return error;
}

fcml_ceh_error fcml_fn_disassemble( fcml_st_disassembler_context *context, fcml_st_instruction *instruction, fcml_st_disassembler_result **result ) {
	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
	return error;
}

void fcml_fn_disassemble_result_free( fcml_st_disassembler_result *result ) {
	if( result ) {
		if( result->errors ) {
			fcml_fn_ceh_free_error_container( result->errors );
		}
		fcml_fn_env_memory_free( result );
	}
}

void fcml_fn_disassembler_free( fcml_st_disassembler *disassembler ) {
	fcml_fn_asm_free_instruction_decodings( disassembler );
}
