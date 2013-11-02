/*
 * fcml_assembler.c
 *
 *  Created on: 24-03-2013
 *      Author: tAs
 */

#include <string.h>

#include "fcml_ceh.h"
#include "fcml_env.h"
#include "fcml_utils.h"

#include "fcml_assembler.h"
#include "fcml_encoding.h"
#include "fcml_optimizers.h"

fcml_ceh_error fcml_fn_assembler_init( fcml_st_dialect_context context, fcml_st_assembler **assembler ) {
	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

	*assembler = fcml_fn_env_memory_alloc( sizeof( fcml_st_assembler ) );
	if( *assembler ) {
	    error = fcml_fn_asm_init_instruction_encodings( &context, assembler );
	} else {
	    error = FCML_CEH_GEC_OUT_OF_MEMORY;
	}

	return error;
}

void fcml_ifp_coll_list_action_free_assembled_instruction( fcml_ptr item_value, fcml_ptr args ) {
	fcml_st_assembled_instruction *asm_inst = (fcml_st_assembled_instruction*)item_value;
	if( asm_inst ) {
		fcml_fn_env_memory_free( asm_inst->code );
		fcml_fn_env_memory_free( asm_inst );
	}
}

void fcml_fn_assembler_result_free( fcml_st_assembler_result *result ) {
	if( result ) {
		if( result->errors ) {
			fcml_fn_ceh_free_error_container( result->errors );
		}
		if(result->instructions ) {
			fcml_fn_coll_list_free( result->instructions, fcml_ifp_coll_list_action_free_assembled_instruction, NULL );
		}
		fcml_fn_env_memory_free( result );
	}
}

fcml_ceh_error fcml_fn_assemble( fcml_st_assembler_context *asm_context, fcml_st_instruction *instruction, fcml_st_assembler_result **result ) {

	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

	if( instruction == NULL ) {
		return FCML_CEH_GEC_INVALID_INPUT;
	}

	// Find instruction addressing modes.
	fcml_st_asm_instruction_addr_modes *addr_modes = NULL;
	error = fcml_fn_asm_get_instruction_encodings( asm_context->assembler, instruction->mnemonic, &addr_modes );
	if( error ) {
		return error;
	}

	if( !asm_context->effective_address_size ) {
		asm_context->effective_address_size = fcml_fn_utils_get_default_ASA(asm_context->addr_form);
	}
	if( !asm_context->effective_operand_size ) {
		asm_context->effective_operand_size = fcml_fn_utils_get_default_OSA(asm_context->addr_form);
	}

	fcml_st_assembler_result *asm_result = fcml_fn_env_memory_alloc( sizeof( fcml_st_encoder_result ) );
	if( !asm_result ) {
		return FCML_CEH_GEC_OUT_OF_MEMORY;
	}

	// Allocate error container.
	asm_result->errors = fcml_fn_ceh_alloc_error_container();
	if( !(asm_result->errors) ) {
		fcml_fn_assembler_result_free( asm_result );
		return FCML_CEH_GEC_OUT_OF_MEMORY;
	}

	// Allocate list for assembled instructions.
	asm_result->instructions = fcml_fn_coll_list_alloc();
	if( !(asm_result->instructions) ) {
		fcml_fn_assembler_result_free( asm_result );
		return FCML_CEH_GEC_OUT_OF_MEMORY;
	}

	// Execute instruction encoder.
	if( addr_modes != NULL ) {
		if( addr_modes->instruction_encoder ) {

			fcml_st_encoder_result enc_result;
			enc_result.errors = asm_result->errors;
			enc_result.instructions = asm_result->instructions;

			addr_modes->instruction_encoder( asm_context, instruction, &enc_result, addr_modes );

		} else {
			// Unavailable instruction encoder.
			error = FCML_CEH_GEC_INTERNAL_BUG;
		}
	} else {
		error = FCML_EN_UNKNOWN_MNEMONIC;
	}

	if( error ) {
		fcml_fn_assembler_result_free( asm_result );
	} else {
		*result = asm_result;
	}

	return error;
}

void fcml_fn_assembler_free( fcml_st_assembler *assembler ) {
	fcml_fn_asm_free_instruction_encodings( assembler );
}


