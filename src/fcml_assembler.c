/*
 * fcml_assembler.c
 *
 *  Created on: 24-03-2013
 *      Author: tAs
 */

#include <fcml_assembler.h>

#include <stddef.h>

#include <fcml_errors.h>

#include "fcml_dialect_int.h"
#include "fcml_encoding.h"
#include "fcml_env_int.h"
#include "fcml_utils.h"
#include "fcml_trace.h"

/** Initialized assembler instance. */
typedef struct fcml_ist_asm_enc_assembler {
	/** Map of supported instructions, with mnemonic as key and instructions addressing modes as values. */
    fcml_coll_map instructions_map;
    /** Dialect used to initialize assembler. */
    fcml_st_dialect_context_int *dialect_context;
} fcml_ist_asm_enc_assembler;

fcml_ceh_error LIB_CALL fcml_fn_assembler_init( fcml_st_dialect *dialect, fcml_st_assembler **assembler ) {

	/* Allocate assembler instance.*/
	fcml_ist_asm_enc_assembler *enc_asm = (fcml_ist_asm_enc_assembler*)fcml_fn_env_memory_alloc_clear( sizeof( fcml_ist_asm_enc_assembler ) );
	if( !enc_asm ) {
		return FCML_CEH_GEC_OUT_OF_MEMORY;
	}

	fcml_ceh_error error = fcml_fn_asm_init_instruction_encodings( (fcml_st_dialect_context_int*)dialect, &(enc_asm->instructions_map) );
	if( error ) {
		fcml_fn_env_memory_free( enc_asm );
		return error;
	}

	enc_asm->dialect_context = (fcml_st_dialect_context_int*)dialect;

	*assembler = (fcml_st_assembler *)enc_asm;

	return FCML_CEH_GEC_NO_ERROR;
}

void fcml_ifn_asm_free_instruction_chain( fcml_st_assembled_instruction *chain ) {

	/* Free every instruction in the chain. */
    while( chain ) {
        fcml_st_assembled_instruction *instruction = chain;
        chain = chain->next;
        fcml_fn_env_memory_free( instruction->code );
        fcml_fn_env_memory_free( instruction );
    }

}

void LIB_CALL fcml_fn_assembler_instruction_detach( fcml_st_assembled_instruction **chain, fcml_st_assembled_instruction *instruction ) {

	if( !chain || !instruction ) {
		return;
	}

	fcml_st_assembled_instruction **current = chain;
	fcml_bool found = FCML_FALSE;

	do {
		if( *current == instruction ) {
			*current = instruction->next;
			found = FCML_TRUE;
		}
		current = &((*current)->next);
	} while( !found && *current );

}

void LIB_CALL fcml_fn_assembler_instruction_free( fcml_st_assembled_instruction *instruction ) {
	if( instruction ) {
		if( instruction->code ) {
			fcml_fn_env_memory_free( instruction->code );
		}
		fcml_fn_ceh_free_errors_only( &(instruction->warnings ) );
		fcml_fn_env_memory_free( instruction );
	}
}

void LIB_CALL fcml_fn_assembler_result_free( fcml_st_assembler_result *result ) {
	if( result ) {
		// Free errors but leave container as is.
		fcml_fn_ceh_free_errors_only( &(result->errors) );
		// Free all available instructions in the chain.
        fcml_ifn_asm_free_instruction_chain( result->instructions );
        // Prepare for next usage.
        fcml_fn_assembler_result_prepare( result );
	}
}

void LIB_CALL fcml_fn_assembler_result_prepare( fcml_st_assembler_result *result ) {
	// Clean assembler result container before it is first used.
	if( result ) {
		fcml_fn_env_memory_clear( result, sizeof( fcml_st_assembler_result ) );
	}
}

fcml_ceh_error fcml_ifn_assemble_core( fcml_st_assembler_context *asm_context, const fcml_st_instruction *instruction, fcml_st_assembler_result *result ) {

	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

	// Sanity check.
	if( !result || !instruction || !asm_context ) {
		return FCML_CEH_GEC_INVALID_INPUT;
	}

	/* Validate and prepare entry point. */
	error = fcml_fn_prepare_entry_point( &(asm_context->entry_point ) );
	if( error ) {
		return error;
	}

	/* Take into account that dialect can modify source instruction by
	 * preparing it for the assembler, so we have to use the local copy here.
	 */
	fcml_st_instruction tmp_instruction = *instruction;

	fcml_ist_asm_enc_assembler *enc_asm = (fcml_ist_asm_enc_assembler*)asm_context->assembler;

	/* The first place where the dialect can interfere with the instruction definition. */
	fcml_fnp_asm_dialect_prepare_assembler_preprocessor assembler_preprocessor = enc_asm->dialect_context->assembler_preprocessor;
	if( assembler_preprocessor ) {
		assembler_preprocessor( (fcml_st_dialect*)enc_asm->dialect_context, &tmp_instruction, NULL, NULL, NULL );
	}

	/* Find instruction addressing modes/forms. */
	fcml_st_asm_instruction_addr_modes *addr_modes = NULL;
	error = fcml_fn_asm_get_instruction_encodings( enc_asm->instructions_map, tmp_instruction.mnemonic, &addr_modes );
	if( error ) {
		return error;
	}

	/* Execute instruction encoder. */
	if( addr_modes ) {

		if( addr_modes->instruction_encoder ) {

			fcml_st_asm_encoder_result enc_result = {{0}};

			error = addr_modes->instruction_encoder( asm_context, enc_asm->dialect_context, &tmp_instruction, &enc_result, addr_modes );
			if( !error ) {
				result->instructions = enc_result.instructions;
				result->number_of_instructions = enc_result.number_of_instructions;
				result->chosen_instruction = enc_result.chosen_instruction;

				/* Increment IP by chosen instruction length. */
				if( result->chosen_instruction && asm_context->configuration.increment_ip ) {
					asm_context->entry_point.ip += result->chosen_instruction->code_length;
				}
			}

			/* Convert encoding result to assembler result. */
			result->errors = enc_result.errors;

		} else {
			FCML_TRACE_MSG( "Unavailable instruction encoder." );
			error = FCML_CEH_GEC_INTERNAL_ERROR;
		}

	} else {
		error = FCML_CEH_GEC_UNKNOWN_MNEMONIC;
	}

	/* Free results but only if there is no error messages. */
	if( error ) {
		/* Free only instructions, error messages should be returned to user. */
		fcml_ifn_asm_free_instruction_chain( result->instructions );
		result->instructions = NULL;
		result->chosen_instruction = NULL;
		result->number_of_instructions = 0;
	}

	return error;
}

fcml_ceh_error LIB_CALL fcml_fn_assemble( fcml_st_assembler_context *context, const fcml_st_instruction *instruction, fcml_st_assembler_result *result ) {

	// Check if there is something already available in the result and free it in such a cache.
	fcml_fn_assembler_result_free( result );

	fcml_ceh_error error = fcml_ifn_assemble_core( context, instruction, result );
	if( error ) {
		// Try to convert error code to error message if there is such need.
		fcml_fn_utils_convert_gec_to_error_info( context->configuration.enable_error_messages, &(result->errors), error );
	}

	return error;
}

void LIB_CALL fcml_fn_assembler_free( fcml_st_assembler *assembler ) {

	if( assembler ) {

		fcml_ist_asm_enc_assembler *enc_asm = (fcml_ist_asm_enc_assembler *)assembler;

		if( enc_asm->instructions_map ) {
			fcml_fn_asm_free_instruction_encodings( enc_asm->instructions_map );
		}

		/* Assembler is not the owner of the dialect context. */
		fcml_fn_env_memory_free( enc_asm );
	}

}

fcml_st_dialect *fcml_fn_assembler_extract_dialect( fcml_st_assembler *assembler ) {

	fcml_st_dialect *dialect = NULL;

	if( assembler ) {
		fcml_ist_asm_enc_assembler *enc_asm = (fcml_ist_asm_enc_assembler*)assembler;
		dialect = (fcml_st_dialect*)enc_asm->dialect_context;
	}

	return dialect;
}

