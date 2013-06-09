/*
 * fcml_assembler.h
 *
 *  Created on: 08-02-2013
 *      Author: tAs
 */

#ifndef FCML_ASSEMBLER_H_
#define FCML_ASSEMBLER_H_

#include "fcml_coll.h"
#include "fcml_common.h"
#include "fcml_errors.h"

typedef struct fcml_st_assembler_configuration {
	fcml_bool choose_sib_encoding;
	fcml_bool choose_rip_encoding;
} fcml_st_assembler_configuration;

typedef struct fcml_st_assembler_context {
	fcml_st_assembler_configuration configuration;
	fcml_en_addr_form addr_form;
	fcml_data_size effective_address_size;
	fcml_data_size effective_operand_size;
} fcml_st_assembler_context;

typedef struct fcml_st_assembled_instruction {
#ifdef FCML_DEBUG
	// Index of addressing mode used to assemble instruction.
	fcml_uint8_t __def_index;
#endif
	fcml_uint8_t *code;
	fcml_usize code_length;
} fcml_st_assembled_instruction;

typedef struct fcml_st_assembler_result {
	fcml_st_ceh_error_container *errors;
	fcml_st_coll_list *instructions;
} fcml_st_assembler_result;

fcml_ceh_error fcml_fn_asm_init();
fcml_ceh_error fcml_fn_assemble( fcml_st_assembler_context *context, fcml_st_instruction *instruction, fcml_st_assembler_result **result );
void fcml_fn_assemble_free( fcml_st_assembler_result *result );
void fcml_fn_asm_free();

#endif /* FCML_ASSEMBLER_H_ */
