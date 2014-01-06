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

typedef struct fcml_ist_asm_opt_optimization_path_element {
	fcml_en_cmi_attribute_size_flag flags;
	fcml_data_size attribute_size;
} fcml_ist_asm_opt_optimization_path_element;

fcml_ist_asm_opt_optimization_path_element fcml_iarr_asm_opt_16_32_bit_optimization_path_16[] = {
	{ FCML_EN_ASF_16, FCML_DS_16 },
	{ FCML_EN_ASF_32, FCML_DS_32 }
};

fcml_ist_asm_opt_optimization_path_element fcml_iarr_asm_opt_16_32_bit_optimization_path_32[] = {
	{ FCML_EN_ASF_32, FCML_DS_32 },
	{ FCML_EN_ASF_16, FCML_DS_16 }
};

fcml_ist_asm_opt_optimization_path_element fcml_iarr_asm_opt_64_bit_optimization_path_for_asa_64[] = {
	{ FCML_EN_ASF_64, FCML_DS_64 },
	{ FCML_EN_ASF_32, FCML_DS_32 }
};

fcml_ist_asm_opt_optimization_path_element fcml_iarr_asm_opt_64_bit_optimization_path_for_asa_32[] = {
	{ FCML_EN_ASF_32, FCML_DS_32 },
	{ FCML_EN_ASF_64, FCML_DS_64 }
};

fcml_ist_asm_opt_optimization_path_element fcml_iarr_asm_opt_64_bit_optimization_path_for_osa_16[] = {
	{ FCML_EN_ASF_16, FCML_DS_16 },
	{ FCML_EN_ASF_64, FCML_DS_64 },
	{ FCML_EN_ASF_32, FCML_DS_32 }
};

fcml_ist_asm_opt_optimization_path_element fcml_iarr_asm_opt_64_bit_optimization_path_for_osa_32[] = {
	{ FCML_EN_ASF_32, FCML_DS_32 },
	{ FCML_EN_ASF_64, FCML_DS_64 },
	{ FCML_EN_ASF_16, FCML_DS_16 }
};

fcml_ist_asm_opt_optimization_path_element fcml_iarr_asm_opt_64_bit_optimization_path_for_osa_64[] = {
	{ FCML_EN_ASF_64, FCML_DS_64 },
	{ FCML_EN_ASF_32, FCML_DS_32 },
	{ FCML_EN_ASF_16, FCML_DS_16 }
};

inline fcml_int fcml_ifn_asm_opt_go_through_the_optimization_path( fcml_en_cmi_attribute_size_flag flags, fcml_int path_length, fcml_ist_asm_opt_optimization_path_element *path, fcml_data_size *attribute_dest ) {
	int i, count = 0;
	for( i = 0; i < path_length; i++ ) {
		fcml_ist_asm_opt_optimization_path_element *element = &(path[i]);
		if( ( flags & element->flags ) || ( flags == FCML_EN_ASF_ANY ) ) {
			attribute_dest[count++] = element->attribute_size;
		}
	}
	return count;
}

inline fcml_int fcml_ifn_asm_opt_try_setting_attribute_size( fcml_en_cmi_attribute_size_flag flags, fcml_uint16_t opt_flags, fcml_data_size attribute_size, fcml_data_size *attribute_dest ) {
	if( ( flags & opt_flags ) || ( flags == FCML_EN_ASF_ANY ) ) {
		*attribute_dest = attribute_size;
		return 1;
	}
	return 0;
}
/*
fcml_ceh_error fcml_fn_asm_all_forms_optimizer( fcml_st_asm_assembler_context *context, fcml_st_asm_optimizer_processing_details *ds_flags, fcml_fnp_asm_optimizer_callback callback, fcml_ptr callback_args ) {

    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

    fcml_int asa_index = 0;
    fcml_int osa_index = 0;
    fcml_data_size asa[2];
    fcml_data_size osa[3];

    if( ds_flags == NULL ) {
       return FCML_CEH_GEC_ILLEGAL_STATE_EXCEPTION;
    }

    fcml_en_cmi_attribute_size_flag asa_flags = ds_flags->allowed_effective_address_size.flags;
    fcml_en_cmi_attribute_size_flag osa_flags = ds_flags->allowed_effective_operand_size.flags;

    if( ds_flags->effective_address_size ) {
        // Effective address size has been already chosen and cannot be changed.
        asa[asa_index++] = ds_flags->effective_address_size;
    } else {
        if( ( asa_flags & FCML_EN_ASF_16 ) || ( asa_flags == FCML_EN_ASF_ANY ) ) {
            asa[asa_index++] = FCML_DS_16;
        }
        if( ( asa_flags & FCML_EN_ASF_32 ) || ( asa_flags == FCML_EN_ASF_ANY ) ) {
            asa[asa_index++] = FCML_DS_32;
        }
        if( ( asa_flags & FCML_EN_ASF_64 ) || ( asa_flags == FCML_EN_ASF_ANY ) ) {
            asa[asa_index++] = FCML_DS_64;
        }
    }

    if( ds_flags->effective_operand_size ) {
        // Effective address size has been already chosen and cannot be changed.
        osa[osa_index++] = ds_flags->effective_operand_size;
    } else {
        if( ( osa_flags & FCML_EN_ASF_16 ) || ( osa_flags == FCML_EN_ASF_ANY ) ) {
            osa[osa_index++] = FCML_DS_16;
        }
        if( ( osa_flags & FCML_EN_ASF_32 ) || ( osa_flags == FCML_EN_ASF_ANY ) ) {
            osa[osa_index++] = FCML_DS_32;
        }
        if( ( osa_flags & FCML_EN_ASF_64 ) || ( osa_flags == FCML_EN_ASF_ANY ) ) {
            osa[osa_index++] = FCML_DS_64;
        }
    }

    return error;

}*/

fcml_ceh_error fcml_fn_asm_default_optimizer( fcml_st_asm_assembler_context *context, fcml_st_asm_optimizer_processing_details *ds_flags, fcml_fnp_asm_optimizer_callback callback, fcml_ptr callback_args ) {

	fcml_ceh_error error = FCML_EN_UNSUPPORTED_ADDRESS_SIZE;

	fcml_data_size easa[2];
	fcml_data_size eosa[3];

	fcml_int easa_count = 0;
	fcml_int eosa_count = 0;

	fcml_ist_asm_opt_optimization_path_element *path;

    fcml_uint16_t opt_flags = context->configuration.optimizer_flags;

    if( ds_flags == NULL ) {
    	return FCML_CEH_GEC_ILLEGAL_STATE_EXCEPTION;
    }

	// ASA

    if( ds_flags->effective_address_size ) {
    	// Effective address size has been already chosen and cannot be changed.
    	easa[easa_count++] = ds_flags->effective_address_size;
    } else {
    	// Maybe user has already forced any address size attribute to be chosen?
    	fcml_data_size attr_size = 0;
    	fcml_en_cmi_attribute_size_flag attr_size_flag = 0;
		switch( opt_flags & 0x000F ) {
		case FCML_OPTF_ASA_16:
			attr_size = FCML_DS_16;
			attr_size_flag = FCML_EN_ASF_16;
			break;
		case FCML_OPTF_ASA_32:
			attr_size = FCML_DS_32;
			attr_size_flag = FCML_EN_ASF_32;
			break;
		case FCML_OPTF_ASA_64:
			attr_size = FCML_DS_64;
			attr_size_flag = FCML_EN_ASF_64;
			break;
		}
		if( attr_size ) {
			easa_count = fcml_ifn_asm_opt_try_setting_attribute_size( ds_flags->allowed_effective_address_size.flags, attr_size_flag, attr_size, &(easa[easa_count]) );
		}
    }

    // OSA

	if( ds_flags->effective_operand_size ) {
		// Effective address size has been already chosen and cannot be changed.
		eosa[eosa_count++] = ds_flags->effective_operand_size;
	} else {
		// Maybe user has already forced any address size attribute to be chosen?
		fcml_data_size attr_size = 0;
		fcml_en_cmi_attribute_size_flag attr_size_flag = 0;
		switch( opt_flags & 0x00F0 ) {
		case FCML_OPTF_OSA_16:
			attr_size = FCML_DS_16;
			attr_size_flag = FCML_EN_ASF_16;
			break;
		case FCML_OPTF_OSA_32:
			attr_size = FCML_DS_32;
			attr_size_flag = FCML_EN_ASF_32;
			break;
		case FCML_OPTF_OSA_64:
			attr_size = FCML_DS_64;
			attr_size_flag = FCML_EN_ASF_64;
			break;
		}
		if( attr_size ) {
			eosa_count = fcml_ifn_asm_opt_try_setting_attribute_size( ds_flags->allowed_effective_operand_size.flags, attr_size_flag, attr_size, &(eosa[eosa_count]) );
		}
	}

	// Choosing best optimization path for ASA.

	if( !easa_count ) {
		switch( context->addr_form ) {
		case FCML_AF_16_BIT:
		case FCML_AF_32_BIT:
			path = ( context->address_size_attribute == FCML_DS_16 ) ? fcml_iarr_asm_opt_16_32_bit_optimization_path_16 : fcml_iarr_asm_opt_16_32_bit_optimization_path_32;
			easa_count = fcml_ifn_asm_opt_go_through_the_optimization_path( ds_flags->allowed_effective_address_size.flags, 2, path, easa );
			break;
		case FCML_AF_64_BIT:
			path = ( context->address_size_attribute == FCML_DS_32 ) ? fcml_iarr_asm_opt_64_bit_optimization_path_for_asa_32 : fcml_iarr_asm_opt_64_bit_optimization_path_for_asa_64;
			easa_count = fcml_ifn_asm_opt_go_through_the_optimization_path( ds_flags->allowed_effective_address_size.flags, 2, path, easa );
			break;
		}
	}

	// Choosing best optimization path for OSA.

	if( !eosa_count ) {
		switch( context->addr_form ) {
		case FCML_AF_16_BIT:
		case FCML_AF_32_BIT:
			path = ( context->operand_size_attribute == FCML_DS_16 ) ? fcml_iarr_asm_opt_16_32_bit_optimization_path_16 : fcml_iarr_asm_opt_16_32_bit_optimization_path_32;
			eosa_count = fcml_ifn_asm_opt_go_through_the_optimization_path( ds_flags->allowed_effective_operand_size.flags, 2, path, eosa );
			break;
		case FCML_AF_64_BIT:
			switch( context->operand_size_attribute ) {
			case FCML_DS_16:
				path = &fcml_iarr_asm_opt_64_bit_optimization_path_for_osa_16[0];
				break;
			case FCML_DS_32:
				path = &fcml_iarr_asm_opt_64_bit_optimization_path_for_osa_32[0];
				break;
			case FCML_DS_64:
				path = &fcml_iarr_asm_opt_64_bit_optimization_path_for_osa_64[0];
				break;
			}
			eosa_count = fcml_ifn_asm_opt_go_through_the_optimization_path( ds_flags->allowed_effective_operand_size.flags, 3, path, eosa );
			break;
		}
	}

	ds_flags->break_optimization = FCML_FALSE;

	int i, j;
	for( i = 0; i < easa_count && ( ( opt_flags == FCML_OPTF_ALL_FORMS ) || error ) && !ds_flags->break_optimization; i++ ) {
		ds_flags->effective_address_size = easa[i];
		for( j = 0; j < eosa_count && ( ( opt_flags == FCML_OPTF_ALL_FORMS ) || error ) && !ds_flags->break_optimization; j++ ) {
			ds_flags->effective_operand_size = eosa[j];
		    error = callback( callback_args );
		}
	}

	return error;
}
