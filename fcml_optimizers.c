/*
 * fcml_optimizers.c
 *
 *  Created on: 16-06-2013
 *      Author: tAs
 */

#include "fcml_optimizers.h"
#include "fcml_assembler.h"
#include "fcml_errors.h"

fcml_ceh_error fcml_fnp_asm_choose_ASA_optimizer( fcml_st_asm_encoding_context *context, fcml_st_asm_instruction_addr_mode *addr_mode, fcml_fnp_asm_optimizer_callback callback, fcml_ptr args ) {

	fcml_ceh_error error = FCML_EN_UNSUPPORTED_ADDRESS_SIZE;

	fcml_uint16_t flags = context->assembler_context->configuration.optimizer_flags;
	fcml_st_asm_data_size_flags *ds_flags =  &(context->data_size_flags);

	fcml_data_size asa = 0;

	switch( flags ) {
	case FCML_OPTF_ASA_16:
		if( ( ds_flags->allowed_effective_address_size & FCML_EN_ASF_16 ) || ( ds_flags->allowed_effective_address_size == FCML_EN_ASF_ANY ) ) {
			asa = FCML_DS_16;
		}
		break;
	case FCML_OPTF_ASA_32:
		if( ( ds_flags->allowed_effective_address_size & FCML_EN_ASF_32 ) || ( ds_flags->allowed_effective_address_size == FCML_EN_ASF_ANY ) ) {
			asa = FCML_DS_32;
		}
		break;
	case FCML_OPTF_ASA_64:
		if( ( ds_flags->allowed_effective_address_size & FCML_EN_ASF_64 ) || ( ds_flags->allowed_effective_address_size == FCML_EN_ASF_ANY ) ) {
			asa = FCML_DS_64;
		}
		break;
	}

	if( asa && ( !context->data_size_flags.effective_address_size || context->data_size_flags.effective_address_size == asa ) ) {
		context->data_size_flags.effective_address_size = asa;
		error = callback( context, addr_mode, args );
	}

	return error;
}

fcml_ceh_error fcml_fnp_asm_default_optimizer( fcml_st_asm_encoding_context *context, fcml_st_asm_instruction_addr_mode *addr_mode, fcml_fnp_asm_optimizer_callback callback, fcml_ptr args ) {

	fcml_ceh_error error = FCML_EN_UNSUPPORTED_ADDRESS_SIZE;

	fcml_data_size easa[2];
	int easa_count = 0;

	fcml_st_asm_data_size_flags *flags =  &(context->data_size_flags);
	if( flags ) {
		if( !flags->effective_address_size ) {
			switch( context->assembler_context->addr_form ) {
			case FCML_AF_16_BIT:
				if( ( flags->allowed_effective_address_size & FCML_EN_ASF_16 ) || ( flags->allowed_effective_address_size == FCML_EN_ASF_ANY ) ) {
					easa[easa_count++] = FCML_DS_16;
				}
				if( flags->allowed_effective_address_size & FCML_EN_ASF_32 ) {
					easa[easa_count++] = FCML_DS_32;
				}
				break;
			case FCML_AF_32_BIT:
				if( ( flags->allowed_effective_address_size & FCML_EN_ASF_32 ) || ( flags->allowed_effective_address_size == FCML_EN_ASF_ANY ) ) {
					easa[easa_count++] = FCML_DS_32;
				}
				if( flags->allowed_effective_address_size & FCML_EN_ASF_16 ) {
					easa[easa_count++] = FCML_DS_16;
				}
				break;
			case FCML_AF_64_BIT:
				if( ( flags->allowed_effective_address_size & FCML_EN_ASF_64 ) || ( flags->allowed_effective_address_size == FCML_EN_ASF_ANY ) ) {
					easa[easa_count++] = FCML_DS_64;
				}
				if( flags->allowed_effective_address_size & FCML_EN_ASF_32 ) {
					easa[easa_count++] = FCML_DS_32;
				}
				break;
			}
		}
	}

	int i = 0;
	for( i = 0; i < easa_count && error; i++ ) {
		context->data_size_flags.effective_address_size = easa[i];
		error = callback( context, addr_mode, args );
	}

	return error;
}

fcml_fnp_asm_optimizer fcml_ar_optimizers[] = {
	fcml_fnp_asm_default_optimizer,
	fcml_fnp_asm_choose_ASA_optimizer,
	NULL
};


