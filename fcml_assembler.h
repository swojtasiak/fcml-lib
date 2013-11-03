/*
 * fcml_assembler.h
 *
 *  Created on: 08-02-2013
 *      Author: tAs
 */

#ifndef FCML_ASSEMBLER_H_
#define FCML_ASSEMBLER_H_

#include "fcml_ceh.h"
#include "fcml_coll.h"
#include "fcml_common.h"
#include "fcml_dialect.h"
#include "fcml_errors.h"
#include "fcml_types.h"

typedef struct fcml_st_asm_assembler {
} fcml_st_asm_assembler;

typedef enum fcml_en_asm_assembler_optimizers {
	FCML_EN_OP_DEFAULT_ADDRESSING_MODE_OPTIMIZER = 0,
	FCML_EN_OP_NO_OPTIMIZER,
} fcml_en_asm_assembler_optimizers;

typedef struct fcml_st_asm_assembler_configuration {
	fcml_bool choose_sib_encoding;
	fcml_bool choose_abs_encoding;
	fcml_en_asm_assembler_optimizers optimizer;
	fcml_uint16_t optimizer_flags;
	fcml_bool force_unnecessary_rex_prefix;
	fcml_bool force_three_byte_VEX;
} fcml_st_asm_assembler_configuration;

typedef struct fcml_st_asm_assembler_result {
	fcml_st_ceh_error_container *errors;
	// List of fcml_st_asm_assembled_instruction structures.
	fcml_st_coll_list *instructions;
} fcml_st_asm_assembler_result;

typedef struct fcml_st_asm_assembler_context {
    // Assembler instance that should be used to assemble instructions.
    fcml_st_asm_assembler *assembler;
	fcml_st_asm_assembler_configuration configuration;
	fcml_en_addr_form addr_form;
	fcml_data_size effective_address_size;
	fcml_data_size effective_operand_size;
	fcml_st_instruction_pointer ip;
} fcml_st_asm_assembler_context;

typedef struct fcml_st_asm_assembled_instruction {
#ifdef FCML_DEBUG
	// Index of addressing mode used to assemble instruction.
	fcml_uint8_t __def_index;
#endif
	fcml_uint8_t *code;
	fcml_usize code_length;
} fcml_st_asm_assembled_instruction;

fcml_ceh_error fcml_fn_asm_assembler_init( fcml_st_dialect_context context, fcml_st_asm_assembler **assembler );
fcml_ceh_error fcml_fn_asm_assemble( fcml_st_asm_assembler_context *context, fcml_st_instruction *instruction, fcml_st_asm_assembler_result **result );
void fcml_fn_asm_assembler_result_free( fcml_st_asm_assembler_result *result );
void fcml_fn_asm_assembler_free( fcml_st_asm_assembler *assembler );

#endif /* FCML_ASSEMBLER_H_ */
