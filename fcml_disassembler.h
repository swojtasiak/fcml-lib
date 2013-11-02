/*
 * fcml_disassembler.h
 *
 *  Created on: 08-02-2013
 *      Author: tAs
 */

#ifndef FCML_DISASSEMBLER_H_
#define FCML_DISASSEMBLER_H_

#include "fcml_errors.h"
#include "fcml_stream.h"
#include "fcml_common.h"
#include "fcml_ceh.h"
#include "fcml_dialect.h"
#include "fcml_disassembler_result.h"

#define FCML_CONDITIONAL_GROUP_1	0x00
#define FCML_CONDITIONAL_GROUP_2	0x01

typedef struct fcml_st_disassembler {
} fcml_st_disassembler;

typedef struct fcml_st_dasm_disassembler_configuration {
	fcml_bool show_carry;
	fcml_uint8_t conditional_group;
	fcml_bool use_short_form_mnemonics;
	fcml_bool imm_extend_to_osa;
	fcml_bool extend_displacement_to_asa;
} fcml_st_dasm_disassembler_configuration;

typedef struct fcml_st_dasm_disassembler_context {
	fcml_st_disassembler *disassembler;
	fcml_st_dasm_disassembler_configuration configuration;
	fcml_en_addr_form addr_form;
	fcml_data_size address_size_attribute;
	fcml_data_size operand_size_attribute;
	fcml_ptr code_address;
	fcml_data_size code_size;
	fcml_st_instruction_pointer ip;
} fcml_st_dasm_disassembler_context;


fcml_ceh_error fcml_fn_dasm_disassembler_init( fcml_st_dialect_context *context, fcml_st_disassembler **disassembler );
fcml_ceh_error fcml_fn_dasm_disassemble( fcml_st_dasm_disassembler_context *context, fcml_st_dasm_disassembler_result **result );
void fcml_fn_dasm_disassemble_result_free( fcml_st_dasm_disassembler_result *result );
void fcml_fn_dasm_disassembler_free( fcml_st_disassembler *disassembler );

#endif /* FCML_DISASSEMBLER_H_ */
