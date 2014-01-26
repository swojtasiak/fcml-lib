/*
 * fcml_asm_errors.h
 *
 *  Created on: 10-05-2013
 *      Author: tAs
 */

#ifndef FCML_ASM_ERRORS_H_
#define FCML_ASM_ERRORS_H_

#include "fcml_types.h"

enum fcml_en_ceh_error_globals {
	/* Operation succeed. */
	FCML_CEH_GEC_NO_ERROR = 0,
	/* There is no enough memory to complete operation. */
	FCML_CEH_GEC_OUT_OF_MEMORY,
	/* Syntax error or instruction exceeds max length. */
	FCML_CEH_GEC_INVALID_INPUT,
	/* An internal error occurred. Enable tracing in order to get more detailed information. */
	FCML_CEH_GEC_INTERNAL_ERROR,
	/* Component hasn't been initialized yet. */
	FCML_CEH_GEC_NOT_INITIALIZED,
	// Incomplete instruction.
	FCML_CEH_GEC_EOF,
	/* Used mainly in case of integers and offsets. */
	FCML_CEH_GEC_VALUE_OUT_OF_RANGE,
	/* Chosen operation is not supported in case of given configuration. */
	FCML_CEH_GEC_FEATURE_NOT_SUPPORTED,
	/* It's very generic error used always when used addressing mode can not be identified. */
	FCML_CEH_GEC_UNSUPPORTED_ADDRESSING_MODE,
	/* Instruction do not support one of the defined operands. */
	FCML_CEH_GEC_UNSUPPORTED_OPPERAND,
	/* Unknown mnemonic. */
	FCML_CEH_GEC_UNKNOWN_MNEMONIC,
	/* Operand size (Operand size attribute) is not allowed in given context. */
	FCML_CEH_GEC_UNSUPPORTED_OPPERAND_SIZE,
	/* Address size (Address size attribute) is not allowed in given context. */
	FCML_CEH_GEC_UNSUPPORTED_ADDRESS_SIZE,
	// User chosen unsupported addressing form.
	FCML_CEH_GEC_UNSUPPORTED_ADDRESSING_FORM,
	/* Unknown instruction (used by disassembler.) */
	FCML_CEH_GEC_UNKNOWN_INSTRUCTION,
	/* Assembler can return this error code if there is not allowed prefix defined for given instruction. */
	FCML_CEH_GEC_UNSUPPORTED_PREFIX
};

enum fcml_en_ceh_message_errors {
	/* Segment register can not be overriden. */
	FCML_CEH_MEC_ERROR_ILLEGAL_SEG_REG_OVERRIDE = 1000,
	/* To many operands passed to parser. */
	FCML_CEH_MEC_ERROR_TO_MANY_OPERANDS,
	/* Unsupported pseudo-op value. */
	FCML_CEH_MEC_ERROR_INVALID_PSEUDO_OPCODE_VALUE,
	/* HLE prefix is not allowed in given context. */
	FCML_CEH_MEC_ERROR_HLE_PREFIX_NOT_ALLOWED,
	/* There is more than one HLE prefix. */
	FCML_CEH_MEC_ERROR_HLE_MORE_THAN_ONE_PREFIX,
	/* Expression attempts to divide by 0 */
	FCML_CEH_MEC_ERROR_DIVISION_BY_0,
	/* Wrong value type used in given context. For example float used in place of integer. */
	FCML_CEH_MEC_ERROR_WRONG_VALUE_FORMAT,
	/* Value out of range, for example 32 bit value used as segment selector. */
	FCML_CEH_MEC_ERROR_VALUE_OUT_OF_RANGE,
	/* Syntax error from parser. */
	FCML_CEH_MEC_ERROR_INVALID_SYNTAX,
	/* Wrong register type used in place of segment register. */
	FCML_CEH_MEC_ERROR_WRONG_REGISTER_TYPE_SEG,
};

enum fcml_en_ceh_message_warnings {
	/* Value out of range  */
	FCML_CEH_MEW_WARN_VALUE_OUT_OF_RANGE = 2000
};

typedef fcml_uint16_t fcml_ceh_error;

/* Information level. */
typedef enum fcml_en_ceh_error_level {
	/* Warnings are reported when processing doesn't need to be stopped. */
	FCML_EN_CEH_EL_WARN,
	/* Errors are reported when something more important happened and processing
	 * should be stopped. */
	FCML_EN_CEH_EL_ERROR
} fcml_en_ceh_error_level;

/* Information about one particulat event. */
typedef struct fcml_st_ceh_error_info {
	/* Next event on the list. */
	struct fcml_st_ceh_error_info *next_error;
	/* Event description. */
	fcml_string message;
	/* Event code */
	fcml_ceh_error code;
	/* Event error level. */
	fcml_en_ceh_error_level level;
} fcml_st_ceh_error_info;

/* Container for all collected events. */
typedef struct fcml_st_ceh_error_container {
	/* All events going there. */
	fcml_st_ceh_error_info *errors;
	/* Pointer to the last error on the list. */
	fcml_st_ceh_error_info *last_error;
} fcml_st_ceh_error_container;

#endif /* FCML_ASM_ERRORS_H_ */
