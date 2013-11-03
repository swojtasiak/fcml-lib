/*
 * fcml_hints.c
 *
 *  Created on: Nov 2, 2013
 *      Author: tas
 */

#include "fcml_hints.h"

fcml_st_hts_calculated_hints fcml_fn_hts_ihc_far_pointer( fcml_st_def_addr_mode_desc *addr_mode, fcml_st_def_decoded_addr_mode *decoded_addr_mode ) {
	fcml_st_hts_calculated_hints hints;
    hints.instruction_hints = FCML_HINT_FAR_POINTER;
    hints.operand_hints = 0;
    return hints;
}

fcml_st_hts_calculated_hints fcml_fn_hts_ihc_modrm_hints( fcml_st_def_addr_mode_desc *addr_mode, fcml_st_def_decoded_addr_mode *decoded_addr_mode ) {
	fcml_st_hts_calculated_hints hints;
    fcml_sf_def_tma_rm *rm_args = (fcml_sf_def_tma_rm*)decoded_addr_mode->addr_mode_args;
    if( rm_args->flags & FCML_RMF_M ) {
    	hints.operand_hints = 0;
    	if( rm_args->reg_type == FCML_REG_SIMD ) {
			hints.operand_hints |= FCML_OP_HINT_MULTIMEDIA_INSTRUCTION;
    	}
    	if( rm_args->encoded_memory_operand_size == FCML_EOS_FPI ) {
    		hints.instruction_hints = FCML_HINT_FAR_POINTER;
    	} else {
    		hints.instruction_hints = FCML_HINT_NEAR_POINTER;
    	}
    	// Every ModR/M encoded operand supports SIB hint.
    	hints.operand_hints |= FCML_OP_HINT_SIB_ENCODING;
    } else {
    	hints.operand_hints = 0;
    }
    return hints;
}

fcml_st_hts_calculated_hints fcml_fn_hts_ihc_immediate_dis_relative( fcml_st_def_addr_mode_desc *addr_mode, fcml_st_def_decoded_addr_mode *decoded_addr_mode ) {
	fcml_st_hts_calculated_hints hints;
    hints.instruction_hints = 0;
    hints.operand_hints = FCML_OP_HINT_DISPLACEMENT_RELATIVE_ADDRESS;
    return hints;
}

fcml_st_hts_calculated_hints fcml_fn_hts_ihc_pseudo_opcode( fcml_st_def_addr_mode_desc *addr_mode, fcml_st_def_decoded_addr_mode *decoded_addr_mode ) {
	fcml_st_hts_calculated_hints hints;
    hints.instruction_hints = 0;
    hints.operand_hints = FCML_OP_HINT_PSEUDO_OPCODE;
    return hints;
}
