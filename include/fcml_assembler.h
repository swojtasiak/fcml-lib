/*
 * fcml_assembler.h
 *
 *  Created on: 08-02-2013
 *      Author: tAs
 */

#ifndef FCML_ASSEMBLER_H_
#define FCML_ASSEMBLER_H_

#include "fcml_types.h"
#include "fcml_ceh.h"
#include "fcml_common.h"
#include "fcml_dialect.h"
#include "fcml_optimizers.h"
#include "fcml_choosers.h"

/* This structure and type definition represents an abstract assembler. */
typedef struct fcml_st_assembler fcml_st_assembler;

/* Assembler runtime configuration. */
typedef struct fcml_st_assembler_conf {
	/* True if optional error and warning messages should be collected during processing. */
	fcml_bool enable_error_messages;
    /* If there is SIB and ModR/M only encoding available, choose the SIB based one. */
    fcml_bool choose_sib_encoding;
    /* If memory addressing can be encoded as relative and absolute one,
     * choose absolute addressing. It works in 64 bit mode only. */
    fcml_bool choose_abs_encoding;
    /* Sometimes REX prefix is useless so it is just omited in the final machine code. By setting this
     * flag to true you can forse this prefix to be added anyway. */
    fcml_bool force_rex_prefix;
    /* Every 2 byte VEX/XOP prefix can be encoded using three byte form. Setting this flag to true forces it. */
    fcml_bool force_three_byte_VEX;
    /* Optimizer implementation that should be used by assembler. Setting it to NULL causes assembler to use default one. */
    fcml_fnp_asm_optimizer optimizer;
    /* This filed is passed to optimizer, so it can be used to configure its behavior. */
    fcml_uint16_t optimizer_flags;
    /* Chooser implementation that should be used by assembler to choose most appropriate instruction encoding.
     * Setting this value to NULL cause assembler to use default instruction chooser. */
    fcml_fnp_asm_instruction_chooser chooser;
} fcml_st_assembler_conf;

/* Encoded instruction. */
typedef struct fcml_st_assembled_instruction {
    /* Next assembled instruction in the chain.*/
    struct fcml_st_assembled_instruction *next;
	/* Error and warning messages related to assembled instruction.*/
	fcml_st_ceh_error_container errors;
	/* Instruction machine code.*/
	fcml_uint8_t *code;
	/* Instruction code length in bytes.*/
	fcml_usize code_length;
#ifdef FCML_DEBUG
	/* Index of addressing mode used to assemble instruction.*/
	fcml_uint8_t __def_index;
#endif
} fcml_st_assembled_instruction;

/* Assembler result. */
typedef struct fcml_st_assembler_result {
    /* Error and warnign messages from assembler.*/
	fcml_st_ceh_error_container errors;
	/* List of assembled instructions.*/
	fcml_st_assembled_instruction *instructions;
	/* Instruction chosen by used instruction chooser; otherwise null.*/
	fcml_st_assembled_instruction *chosen_instruction;
	/* Number of assembled instructions.*/
	fcml_usize number_of_instructions;
} fcml_st_assembler_result;

/* Assembler runtime context. */
typedef struct fcml_st_assembler_context {
    /* Assembler instance that should be used to assemble instructions.*/
    fcml_st_assembler *assembler;
    /* Assembler behavior can be configured here.*/
	fcml_st_assembler_conf configuration;
	/* Instruction entry point configuration. */
	fcml_st_entry_point entry_point;
} fcml_st_assembler_context;

fcml_ceh_error fcml_fn_assembler_init( fcml_st_dialect *context, fcml_st_assembler **assembler );
fcml_ceh_error fcml_fn_assemble( fcml_st_assembler_context *context, const fcml_st_instruction *instruction, fcml_st_assembler_result *result );
void fcml_fn_assembler_result_prepare( fcml_st_assembler_result *result );
void fcml_fn_assembler_result_free( fcml_st_assembler_result *result );
void fcml_fn_assembler_free( fcml_st_assembler *assembler );

#endif /* FCML_ASSEMBLER_H_ */
