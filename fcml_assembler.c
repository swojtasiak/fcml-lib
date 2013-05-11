/*
 * fcml_assembler.c
 *
 *  Created on: 24-03-2013
 *      Author: tAs
 */

#include <string.h>

#include "fcml_ceh.h"
#include "fcml_env.h"

#include "fcml_assembler.h"
#include "fcml_asm_encoding.h"

fcml_ceh_error fcml_fn_asm_init() {
	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
	error = fcml_fn_asm_init_instruction_encodings();
	return error;
}

void fcml_ifp_coll_list_action_free_assembled_instruction( fcml_ptr item_value, fcml_ptr *args ) {
	fcml_st_assembled_instruction *asm_inst = (fcml_st_assembled_instruction*)args;
	if( asm_inst ) {
		fcml_fn_env_memory_free( asm_inst->code );
		fcml_fn_env_memory_free( asm_inst );
	}
}

void fcml_fn_assemble_free( fcml_st_assembler_result *result ) {
	if( result ) {
		if( result->errors ) {
			fcml_fn_ceh_free_error_container( result->errors );
		}
		if(result->instructions ) {
			fcml_fn_coll_list_free( result->instructions, fcml_ifp_coll_list_action_free_assembled_instruction );
		}
		fcml_fn_env_memory_free( result );
	}
}

fcml_ceh_error fcml_fn_assemble( fcml_st_instruction *instruction, fcml_st_assembler_result **result ) {

	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

	if( instruction == NULL ) {
		return FCML_CEH_GEC_INVALID_INPUT;
	}

	// Find instruction addressing modes.
	fcml_st_asm_instruction_addr_modes *addr_modes = NULL;
	error = fcml_fn_asm_get_instruction_encodings( instruction->mnemonic, &addr_modes );
	if( error ) {
		return error;
	}

	fcml_st_asm_encoding_context context;

	memset( &context, 0, sizeof( fcml_st_asm_encoding_context ) );

	context.result = fcml_fn_env_memory_alloc( sizeof( fcml_st_assembler_result ) );
	if( !context.result ) {
		return FCML_CEH_GEC_OUT_OF_MEMORY;
	}

	// Allocate error container.
	context.result->errors = fcml_fn_ceh_alloc_error_container();
	if( !(context.result->errors) ) {
		fcml_fn_assemble_free( context.result );
		return FCML_CEH_GEC_OUT_OF_MEMORY;
	}

	// Allocate list for assembled instructions.
	context.result->instructions = fcml_fn_coll_list_alloc();
	if( !(context.result->errors) ) {
		fcml_fn_assemble_free( context.result );
		return FCML_CEH_GEC_OUT_OF_MEMORY;
	}

	// Execute instruction encoder.
	if( addr_modes != NULL ) {
		if( addr_modes->instruction_encoder ) {
			addr_modes->instruction_encoder( &context, addr_modes );
		} else {
			// Unavailable instruction encoder.
			error = FCML_CEH_GEC_INTERNAL_BUG;
		}
	} else {
		error = FCML_EN_ASM_UNKNOWN_MNEMONIC;
	}

	if( error ) {
		fcml_fn_env_memory_free( context.result );
	} else {
		*result = context.result;
	}

	return error;
}

void fcml_fn_asm_free() {
	fcml_fn_asm_free_instruction_encodings();
}


