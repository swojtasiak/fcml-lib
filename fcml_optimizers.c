/*
 * fcml_optimizers.c
 *
 *  Created on: 16-06-2013
 *      Author: tAs
 */

#include "fcml_optimizers.h"

#include <stddef.h>

#include "fcml_common.h"
#include "fcml_common_int.h"
#include "fcml_errors.h"

fcml_ceh_error fcml_fnp_asm_default_optimizer( fcml_st_asm_assembler_context *context, fcml_st_asm_data_size_flags *ds_flags, fcml_fnp_asm_optimizer_callback callback, fcml_ptr callback_args ) {

	fcml_ceh_error error = FCML_EN_UNSUPPORTED_ADDRESS_SIZE;

	fcml_data_size easa[2], eosa[3];

	int easa_count = 0, eosa_count = 0;

	// Choose best ASA and OSA size, but first check if uses decided to set attribute size himself.

    fcml_data_size asa = 0, osa = 0;

	// ASA

    fcml_uint16_t opt_flags = context->configuration.optimizer_flags;

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

	if( ds_flags ) {
		if( !ds_flags->effective_address_size ) {
			switch( context->addr_form ) {
			case FCML_AF_16_BIT:
			    // ASA.
			    if( asa ) {
			        easa[easa_count++] = asa;
			    } else {
                    if( ( ds_flags->allowed_effective_address_size.flags & FCML_EN_ASF_16 ) || ( ds_flags->allowed_effective_address_size.flags == FCML_EN_ASF_ANY ) ) {
                        easa[easa_count++] = FCML_DS_16;
                    }
                    if( ( ds_flags->allowed_effective_address_size.flags & FCML_EN_ASF_32 ) || ds_flags->allowed_effective_address_size.flags == FCML_EN_ASF_ANY ) {
                        easa[easa_count++] = FCML_DS_32;
                    }
			    }
				// OSA.
			    if( osa ) {
			        eosa[eosa_count++] = osa;
			    } else {
                    if( ( ds_flags->allowed_effective_operand_size.flags & FCML_EN_ASF_16 ) || ( ds_flags->allowed_effective_operand_size.flags == FCML_EN_ASF_ANY ) ) {
                        eosa[eosa_count++] = FCML_DS_16;
                    }
                    if( ( ds_flags->allowed_effective_operand_size.flags & FCML_EN_ASF_32 ) || ds_flags->allowed_effective_operand_size.flags == FCML_EN_ASF_ANY ) {
                        eosa[eosa_count++] = FCML_DS_32;
                    }
			    }
				break;
			case FCML_AF_32_BIT:
			    if( asa ) {
                    easa[easa_count++] = asa;
                } else {
                    if( ( ds_flags->allowed_effective_address_size.flags & FCML_EN_ASF_32 ) || ( ds_flags->allowed_effective_address_size.flags == FCML_EN_ASF_ANY ) ) {
                        easa[easa_count++] = FCML_DS_32;
                    }
                    if( ( ds_flags->allowed_effective_address_size.flags & FCML_EN_ASF_16 ) || ds_flags->allowed_effective_address_size.flags == FCML_EN_ASF_ANY ) {
                        easa[easa_count++] = FCML_DS_16;
                    }
                }
				// OSA.
			    if( osa ) {
                   eosa[eosa_count++] = osa;
                } else {
                    if( ( ds_flags->allowed_effective_operand_size.flags & FCML_EN_ASF_32 ) || ( ds_flags->allowed_effective_operand_size.flags == FCML_EN_ASF_ANY ) ) {
                        eosa[eosa_count++] = FCML_DS_32;
                    }
                    if( ( ds_flags->allowed_effective_operand_size.flags & FCML_EN_ASF_16 ) || ds_flags->allowed_effective_operand_size.flags == FCML_EN_ASF_ANY ) {
                        eosa[eosa_count++] = FCML_DS_16;
                    }
                }
				break;
			case FCML_AF_64_BIT:
			    if( asa ) {
                    easa[easa_count++] = asa;
                } else {
                    if( ( ds_flags->allowed_effective_address_size.flags & FCML_EN_ASF_64 ) || ( ds_flags->allowed_effective_address_size.flags == FCML_EN_ASF_ANY ) ) {
                        easa[easa_count++] = FCML_DS_64;
                    }
                    if( ( ds_flags->allowed_effective_address_size.flags & FCML_EN_ASF_32 ) || ds_flags->allowed_effective_address_size.flags == FCML_EN_ASF_ANY ) {
                        easa[easa_count++] = FCML_DS_32;
                    }
                }
				// OSA.
			    if( osa ) {
                  eosa[eosa_count++] = osa;
                } else {
                    if( ( ds_flags->allowed_effective_operand_size.flags & FCML_EN_ASF_32 ) || ( ds_flags->allowed_effective_operand_size.flags == FCML_EN_ASF_ANY ) ) {
                        eosa[eosa_count++] = FCML_DS_32;
                    }
                    if( ( ds_flags->allowed_effective_operand_size.flags & FCML_EN_ASF_64 ) || ( ds_flags->allowed_effective_operand_size.flags == FCML_EN_ASF_ANY ) ) {
                        eosa[eosa_count++] = FCML_DS_64;
                    }
                    if( ( ds_flags->allowed_effective_operand_size.flags & FCML_EN_ASF_16 ) || ds_flags->allowed_effective_operand_size.flags == FCML_EN_ASF_ANY ) {
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
	// TODO: zoptymalizowac instruckje JCC, jezeli nie mozna zdekodowac rel offset na 8 bitach, to powtarza probe dla wszystkich kombinacji asa i eosa zamiast prejsc o nastepego trybu adresowania, chya bedzie trzeba dodac jakies hinty ook kodu bledu, ktore bea sugerowaly optymizerowi ze nie ma co dalej meczyc daneo trybu adresowania.
	int i, j;
	for( i = 0; i < easa_count && error; i++ ) {
		ds_flags->effective_address_size = easa[i];
		for( j = 0; j < eosa_count && error; j++ ) {
			ds_flags->effective_operand_size = eosa[j];
		    error = callback( callback_args );
		}
	}

	return error;
}

fcml_fnp_asm_optimizer fcml_ar_optimizers[] = {
	fcml_fnp_asm_default_optimizer,
	NULL
};


