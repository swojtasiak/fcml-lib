/*
 * fcml_disassembler.h
 *
 *  Created on: 08-02-2013
 *      Author: tAs
 */

#ifndef FCML_DISASSEMBLER_H_
#define FCML_DISASSEMBLER_H_

#include "fcml_common.h"
#include "fcml_ceh.h"
#include "fcml_asm_dialect.h"

typedef struct fcml_st_disassembler {
} fcml_st_disassembler;

typedef struct fcml_st_disassembler_configuration {
} fcml_st_disassembler_configuration;

typedef struct fcml_st_disassembler_context {
	fcml_st_disassembler *disassembler;
	fcml_st_disassembler_configuration configuration;
	fcml_en_addr_form addr_form;
	fcml_data_size effective_address_size;
	fcml_data_size effective_operand_size;
	fcml_ptr code_address;
	fcml_data_size code_size;
	fcml_st_instruction_pointer ip;
} fcml_st_disassembler_context;

typedef struct fcml_st_disassembler_result {
	fcml_st_ceh_error_container *errors;
} fcml_st_disassembler_result;

fcml_ceh_error fcml_fn_disassembler_init( fcml_st_dialect_context context, fcml_st_disassembler **disassembler );
fcml_ceh_error fcml_fn_disassemble( fcml_st_disassembler_context *context, fcml_st_instruction *instruction, fcml_st_disassembler_result **result );
void fcml_fn_disassemble_result_free( fcml_st_disassembler_result *result );
void fcml_fn_disassembler_free( fcml_st_disassembler *disassembler );

#endif /* FCML_DISASSEMBLER_H_ */
