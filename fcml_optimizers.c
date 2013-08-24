/*
 * fcml_optimizers.c
 *
 *  Created on: 16-06-2013
 *      Author: tAs
 */

#include "fcml_optimizers.h"
#include "fcml_assembler.h"
#include "fcml_errors.h"
#include "fcml_trace.h"

fcml_ceh_error fcml_fnp_asm_default_optimizer( fcml_st_asm_encoding_context *context, fcml_st_asm_instruction_addr_mode *addr_mode, fcml_fnp_asm_optimizer_callback callback, fcml_ptr args ) {

	fcml_ceh_error error = FCML_EN_UNSUPPORTED_ADDRESS_SIZE;

	fcml_data_size easa[2], eosa[3];
	int easa_count = 0, eosa_count = 0;

	// Choose best ASA and OSA size, but first check if uses decided to set attribute size himself.

	fcml_uint16_t opt_flags = context->assembler_context->configuration.optimizer_flags;
	fcml_st_asm_data_size_flags *ds_flags =  &(context->data_size_flags);
    fcml_data_size asa = 0, osa = 0;

	// ASA

    switch( opt_flags & 0x000F ) {
    case FCML_OPTF_ASA_16:
        if( ( ds_flags->allowed_effective_address_size.flags & FCML_EN_ASF_16 ) || ( ds_flags->allowed_effective_address_size.flags == FCML_EN_ASF_ANY ) ) {
            asa = FCML_DS_16;
        }
        break;
    case FCML_OPTF_ASA_32:
        if( ( ds_flags->allowed_effective_address_size.flags & FCML_EN_ASF_32 ) || ( ds_flags->allowed_effective_address_size.flags == FCML_EN_ASF_ANY ) ) {
            asa = FCML_DS_32;
        }
        break;
    case FCML_OPTF_ASA_64:
        if( ( ds_flags->allowed_effective_address_size.flags & FCML_EN_ASF_64 ) || ( ds_flags->allowed_effective_address_size.flags == FCML_EN_ASF_ANY ) ) {
            asa = FCML_DS_64;
        }
        break;
    }

    // OSA

    switch( opt_flags & 0x00F0 ) {
    case FCML_OPTF_OSA_16:
        if( ( ds_flags->allowed_effective_operand_size.flags & FCML_EN_ASF_16 ) || ( ds_flags->allowed_effective_operand_size.flags == FCML_EN_ASF_ANY ) ) {
            osa = FCML_DS_16;
        }
        break;
    case FCML_OPTF_OSA_32:
        if( ( ds_flags->allowed_effective_operand_size.flags & FCML_EN_ASF_32 ) || ( ds_flags->allowed_effective_operand_size.flags == FCML_EN_ASF_ANY ) ) {
            osa = FCML_DS_32;
        }
        break;
    case FCML_OPTF_OSA_64:
        if( ( ds_flags->allowed_effective_operand_size.flags & FCML_EN_ASF_64 ) || ( ds_flags->allowed_effective_operand_size.flags == FCML_EN_ASF_ANY ) ) {
            osa = FCML_DS_64;
        }
        break;
    }

	fcml_st_asm_data_size_flags *flags =  &(context->data_size_flags);
	if( flags ) {
		if( !flags->effective_address_size ) {
			switch( context->assembler_context->addr_form ) {
			case FCML_AF_16_BIT:
			    // ASA.
			    if( asa ) {
			        easa[easa_count++] = asa;
			    } else {
                    if( ( flags->allowed_effective_address_size.flags & FCML_EN_ASF_16 ) || ( flags->allowed_effective_address_size.flags == FCML_EN_ASF_ANY ) ) {
                        easa[easa_count++] = FCML_DS_16;
                    }
                    if( ( flags->allowed_effective_address_size.flags & FCML_EN_ASF_32 ) || flags->allowed_effective_address_size.flags == FCML_EN_ASF_ANY ) {
                        easa[easa_count++] = FCML_DS_32;
                    }
			    }
				// OSA.
			    if( osa ) {
			        eosa[eosa_count++] = osa;
			    } else {
                    if( ( flags->allowed_effective_operand_size.flags & FCML_EN_ASF_16 ) || ( flags->allowed_effective_operand_size.flags == FCML_EN_ASF_ANY ) ) {
                        eosa[eosa_count++] = FCML_DS_16;
                    }
                    if( ( flags->allowed_effective_operand_size.flags & FCML_EN_ASF_32 ) || flags->allowed_effective_operand_size.flags == FCML_EN_ASF_ANY ) {
                        eosa[eosa_count++] = FCML_DS_32;
                    }
			    }
				break;
			case FCML_AF_32_BIT:
			    if( asa ) {
                    easa[easa_count++] = asa;
                } else {
                    if( ( flags->allowed_effective_address_size.flags & FCML_EN_ASF_32 ) || ( flags->allowed_effective_address_size.flags == FCML_EN_ASF_ANY ) ) {
                        easa[easa_count++] = FCML_DS_32;
                    }
                    if( ( flags->allowed_effective_address_size.flags & FCML_EN_ASF_16 ) || flags->allowed_effective_address_size.flags == FCML_EN_ASF_ANY ) {
                        easa[easa_count++] = FCML_DS_16;
                    }
                }
				// OSA.
			    if( osa ) {
                   eosa[eosa_count++] = osa;
                } else {
                    if( ( flags->allowed_effective_operand_size.flags & FCML_EN_ASF_32 ) || ( flags->allowed_effective_operand_size.flags == FCML_EN_ASF_ANY ) ) {
                        eosa[eosa_count++] = FCML_DS_32;
                    }
                    if( ( flags->allowed_effective_operand_size.flags & FCML_EN_ASF_16 ) || flags->allowed_effective_operand_size.flags == FCML_EN_ASF_ANY ) {
                        eosa[eosa_count++] = FCML_DS_16;
                    }
                }
				break;
			case FCML_AF_64_BIT:
			    if( asa ) {
                    easa[easa_count++] = asa;
                } else {
                    if( ( flags->allowed_effective_address_size.flags & FCML_EN_ASF_64 ) || ( flags->allowed_effective_address_size.flags == FCML_EN_ASF_ANY ) ) {
                        easa[easa_count++] = FCML_DS_64;
                    }
                    if( ( flags->allowed_effective_address_size.flags & FCML_EN_ASF_32 ) || flags->allowed_effective_address_size.flags == FCML_EN_ASF_ANY ) {
                        easa[easa_count++] = FCML_DS_32;
                    }
                }
				// OSA.
			    if( osa ) {
                  eosa[eosa_count++] = osa;
                } else {
                    if( ( flags->allowed_effective_operand_size.flags & FCML_EN_ASF_32 ) || ( flags->allowed_effective_operand_size.flags == FCML_EN_ASF_ANY ) ) {
                        eosa[eosa_count++] = FCML_DS_32;
                    }
                    if( ( flags->allowed_effective_operand_size.flags & FCML_EN_ASF_64 ) || ( flags->allowed_effective_operand_size.flags == FCML_EN_ASF_ANY ) ) {
                        eosa[eosa_count++] = FCML_DS_64;
                    }
                    if( ( flags->allowed_effective_operand_size.flags & FCML_EN_ASF_16 ) || flags->allowed_effective_operand_size.flags == FCML_EN_ASF_ANY ) {
                        eosa[eosa_count++] = FCML_DS_16;
                    }
                }
				break;
			}
		}
	}

	if( !easa_count ) {
	    easa[easa_count++] = 0;
	}

	if( !eosa_count ) {
        eosa[eosa_count++] = 0;
    }

	int i, j;
	for( i = 0; i < easa_count && error; i++ ) {
		context->data_size_flags.effective_address_size = easa[i];
		for( j = 0; j < eosa_count && error; j++ ) {
		    context->data_size_flags.effective_operand_size = eosa[j];
		    error = callback( context, addr_mode, args );
		}
	}

	return error;
}

fcml_fnp_asm_optimizer fcml_ar_optimizers[] = {
	fcml_fnp_asm_default_optimizer,
	NULL
};


