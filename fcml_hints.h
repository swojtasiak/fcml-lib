/*
 * fcml_hints.h
 *
 *  Created on: Nov 2, 2013
 *      Author: tas
 */

#ifndef FCML_HINTS_H_
#define FCML_HINTS_H_

#include "fcml_common.h"
#include "fcml_def.h"

typedef struct fcml_st_hts_calculated_hints {
    fcml_hints instruction_hints;
    fcml_hints operand_hints;
} fcml_st_hts_calculated_hints;

typedef fcml_st_hts_calculated_hints (*fcml_fp_hts_instruction_hints_calculator)( fcml_st_def_addr_mode_desc *addr_mode, fcml_st_def_decoded_addr_mode *decoded_addr_mode );

fcml_st_hts_calculated_hints fcml_fn_hts_ihc_far_pointer( fcml_st_def_addr_mode_desc *addr_mode, fcml_st_def_decoded_addr_mode *decoded_addr_mode );
fcml_st_hts_calculated_hints fcml_fn_hts_ihc_near_pointer( fcml_st_def_addr_mode_desc *addr_mode, fcml_st_def_decoded_addr_mode *decoded_addr_mode );
fcml_st_hts_calculated_hints fcml_fn_hts_ihc_immediate_dis_relative( fcml_st_def_addr_mode_desc *addr_mode, fcml_st_def_decoded_addr_mode *decoded_addr_mode );
fcml_st_hts_calculated_hints fcml_fn_hts_ihc_pseudo_opcode( fcml_st_def_addr_mode_desc *addr_mode, fcml_st_def_decoded_addr_mode *decoded_addr_mode );

#endif /* FCML_HINTS_H_ */
