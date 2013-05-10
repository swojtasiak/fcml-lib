/*
 * fcml_assembler.c
 *
 *  Created on: 24-03-2013
 *      Author: tAs
 */

#include "fcml_ceh.h"

#include "fcml_assembler.h"
#include "fcml_asm_encoding.h"

fcml_ceh_error fcml_fn_asm_init() {
	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
	error = fcml_fn_asm_init_instruction_encodings();
	return error;
}

fcml_ceh_error fcml_fn_assemble( fcml_st_instruction *instruction, fcml_st_ceh_error_container *errors ) {

	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

	if( instruction == NULL ) {
		return FCML_CEH_GEC_INVALID_INPUT;
	}

	// Find instruction addressing modes.
	fcml_st_asm_instruction_addr_modes *addr_modes;
	error = fcml_fn_asm_get_instruction_encodings( instruction->mnemonic, &addr_modes );
	if( error ) {
		return error;
	}

	fcml_st_asm_encoding_context context = {0};

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

	return error;
}

void fcml_fn_asm_free() {
	fcml_fn_asm_free_instruction_encodings();
}


