/*
 * fcml_disassembler.c
 *
 *  Created on: Oct 13, 2013
 *      Author: tas
 */

#include "fcml_stream.h"
#include "fcml_disassembler.h"
#include "fcml_asm_decoding.h"
#include "fcml_env.h"

/**************************
 * Input validation
 **************************/

fcml_ceh_error fcml_ifn_dasm_validate_and_prepare_context( fcml_st_disassembler_context *context ) {

	/* Mode has to be set. */
    if( context->addr_form != FCML_AF_16_BIT && context->addr_form != FCML_AF_32_BIT && context->addr_form != FCML_AF_64_BIT ) {
        return FCML_EN_UNSUPPORTED_ADDRESSING_FORM;
    }

    /* 16 bit address size attribute is not supported in 64bit mode. */
    if( context->addr_form == FCML_AF_64_BIT && context->address_size_attribute == FCML_DS_16 ) {
        return FCML_EN_UNSUPPORTED_ADDRESS_SIZE;
    }

    /* Check if attributes are valid and set them to default values. */
    if( !context->address_size_attribute ) {
        switch( context->addr_form ) {
		case FCML_AF_16_BIT:
			context->address_size_attribute = FCML_DS_16;
			break;
		case FCML_AF_32_BIT:
			context->address_size_attribute = FCML_DS_32;
			break;
		case FCML_AF_64_BIT:
			context->address_size_attribute = FCML_DS_64;
			break;
        }
    }

    if( !context->operand_size_attribute ) {
        switch( context->addr_form ) {
		case FCML_AF_16_BIT:
			context->operand_size_attribute = FCML_DS_16;
			break;
		case FCML_AF_32_BIT:
			context->operand_size_attribute = FCML_DS_32;
			break;
		case FCML_AF_64_BIT:
			context->operand_size_attribute = FCML_DS_32;
			break;
        }
    }

    // Check if ASA is value.
    fcml_data_size asa = context->address_size_attribute;
    if( asa != FCML_DS_16 && asa != FCML_DS_32 && asa != FCML_DS_64 ) {
		return FCML_EN_UNSUPPORTED_ADDRESS_SIZE;
	}

    // Check if OSA is value.
    fcml_data_size osa = context->operand_size_attribute;
    if( osa != FCML_DS_16 && osa != FCML_DS_32 && osa != FCML_DS_64 ) {
   		return FCML_EN_UNSUPPORTED_OPPERAND_SIZE;
   	}

    return FCML_CEH_GEC_NO_ERROR;
}

/****************************
 * Prefixes decoding.
 ****************************/

fcml_ceh_error fcml_fn_dasm_decode_prefixes( fcml_st_memory_stream *stream, fcml_st_asm_dec_prefixes *prefixes ) {
	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
	return error;
}

/****************************
 * API.
 ****************************/

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

fcml_ceh_error fcml_fn_disassemble( fcml_st_disassembler_context *context, fcml_st_disassembler_result **result ) {

	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

	error = fcml_ifn_dasm_validate_and_prepare_context( context );
	if( error ) {
		return error;
	}

	// Prepare stream.
	fcml_st_memory_stream stream;
	stream.base_address = context->code_address;
	stream.size = context->code_size;
	stream.offset = 0;

	// Prepare disassemble context.
	fcml_st_asm_decoding_context decoding_context = {0};
	decoding_context.disassembler_context = context;
	decoding_context.effective_address_size = context->address_size_attribute;
	decoding_context.effective_operand_size = context->operand_size_attribute;

	error = fcml_fn_dasm_decode_prefixes( &stream, &(decoding_context.prefixes) );
	if( error ) {
		return error;
	}

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
