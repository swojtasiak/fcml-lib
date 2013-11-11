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

// Processing details for optimizers.
typedef struct fcml_st_asm_optimizer_processing_details {
	// Flags describing all EOSa sizes available for given addressing mode.
	fcml_st_cmi_nullable_size_flags allowed_effective_operand_size;
	fcml_st_cmi_nullable_size_flags allowed_effective_address_size;
	// Effective address/operand size chosen for currently processed address mode. If set can not be changed anymore.
	// It has higher priority than flags above.
	fcml_data_size effective_address_size;
	fcml_data_size effective_operand_size;
	// L bit from VEX like prefixes set for encoded instruction.
	fcml_nuint8_t l;
	// Set to true in order to break optimization process.
	fcml_bool break_optimization;
} fcml_st_asm_optimizer_processing_details;

struct fcml_st_asm_assembler_context;

// Optimizer definition.
typedef fcml_ceh_error (*fcml_fnp_asm_optimizer_callback)( fcml_ptr args );
typedef fcml_ceh_error (*fcml_fnp_asm_optimizer)( struct fcml_st_asm_assembler_context *context, fcml_st_asm_optimizer_processing_details *ds_flags, fcml_fnp_asm_optimizer_callback callback, fcml_ptr args );

typedef struct fcml_st_asm_assembled_instruction {
#ifdef FCML_DEBUG
	// Index of addressing mode used to assemble instruction.
	fcml_uint8_t __def_index;
#endif
	// Error and warning messages related to assembled instruction.
	fcml_st_ceh_error_container errors;
	fcml_uint8_t *code;
	fcml_usize code_length;
} fcml_st_asm_assembled_instruction;

// Chooser definition.
typedef fcml_st_asm_assembled_instruction* (*fcml_fnp_asm_instruction_chooser)( fcml_st_coll_list *instructions );

typedef struct fcml_st_asm_assembler_configuration {
	fcml_bool choose_sib_encoding;
	fcml_bool choose_abs_encoding;
	fcml_bool force_3byte_vex;
	fcml_fnp_asm_optimizer optimizer;
	fcml_uint16_t optimizer_flags;
	fcml_fnp_asm_instruction_chooser chooser;
	fcml_bool force_unnecessary_rex_prefix;
	fcml_bool force_three_byte_VEX;
} fcml_st_asm_assembler_configuration;

typedef struct fcml_st_asm_assembler_result {
	fcml_st_ceh_error_container errors;
	// List of fcml_st_asm_assembled_instruction structures.
	fcml_st_coll_list *instructions;
	// Instruction chosen by used chooser.
	fcml_st_asm_assembled_instruction *chosen_instruction;
} fcml_st_asm_assembler_result;

typedef struct fcml_st_asm_assembler_context {
    // Assembler instance that should be used to assemble instructions.
    fcml_st_asm_assembler *assembler;
    // Assembler behavior can be configured here.
	fcml_st_asm_assembler_configuration configuration;
	// Processor addressing mode 16/32/64-bit.
	fcml_en_addr_form addr_form;
	// Default address/operand size attribute (See 'D' flag of segment descriptor.)
	fcml_data_size address_size_attribute;
	fcml_data_size operand_size_attribute;
	// Instruction pointer used for relative addressing address calculation.
	fcml_st_instruction_pointer ip;
} fcml_st_asm_assembler_context;

fcml_ceh_error fcml_fn_asm_assembler_init( fcml_st_dialect_context context, fcml_st_asm_assembler **assembler );
fcml_ceh_error fcml_fn_asm_assemble( fcml_st_asm_assembler_context *context, fcml_st_instruction *instruction, fcml_st_asm_assembler_result **result );
void fcml_fn_asm_assembler_result_free( fcml_st_asm_assembler_result *result );
void fcml_fn_asm_assembler_free( fcml_st_asm_assembler *assembler );

#endif /* FCML_ASSEMBLER_H_ */
