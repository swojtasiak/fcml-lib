/*
 * fcml_lag_assembler.h
 *
 *  Created on: Feb 22, 2014
 *      Author: tas
 */

#ifndef FCML_LAG_ASSEMBLER_H_
#define FCML_LAG_ASSEMBLER_H_

#include "fcml_assembler.h"

/* Encoded instruction. */
typedef struct fcml_st_lag_assembled_instruction {
    /* Next assembled instruction in the chain.*/
    struct fcml_st_assembled_instruction *next;
    /* Warnings related to given instruction. */
	fcml_st_ceh_error_container warnings;
	/* Instruction machine code.*/
	fcml_uint8_t *code;
	/* Instruction code length in bytes.*/
	fcml_usize code_length;
} fcml_st_lag_assembled_instruction;

typedef struct fcml_st_lag_assembler_result {
	/* Error and warnign messages from assembler
	 * for instruction which failed.
	 */
	fcml_st_ceh_error_container errors;
	/* List of assembled instructions.*/
	fcml_st_assembled_instruction *instructions;
} fcml_st_lag_assembler_result;

LIB_EXPORT void LIB_CALL fcml_fn_lag_assembler_result_prepare( fcml_st_lag_assembler_result *result );
LIB_EXPORT fcml_ceh_error LIB_CALL fcml_fn_lag_assemble( fcml_st_assembler_context *context, const fcml_string *source_code, fcml_st_lag_assembler_result *result );
LIB_EXPORT void LIB_CALL fcml_fn_lag_assembler_result_free( fcml_st_lag_assembler_result *result );

#endif /* FCML_LAG_ASSEMBLER_H_ */
