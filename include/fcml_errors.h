/*
 * fcml_asm_errors.h
 *
 *  Created on: 10-05-2013
 *      Author: tAs
 */

#ifndef FCML_ASM_ERRORS_H_
#define FCML_ASM_ERRORS_H_

#include "fcml_lib_export.h"

#include "fcml_types.h"

enum fcml_en_ceh_error_globals {
	/* Operation succeed. */
	FCML_CEH_GEC_NO_ERROR = 0,
	/* There is not enough memory to complete operation. */
	FCML_CEH_GEC_OUT_OF_MEMORY = 1,
	/* Syntax error or instruction exceeds max length. */
	FCML_CEH_GEC_INVALID_INPUT = 2,
	/* An internal error occurred. Enable tracing in order to get more detailed information. */
	FCML_CEH_GEC_INTERNAL_ERROR = 3,
	/* Component hasn't been initialized yet. */
	FCML_CEH_GEC_NOT_INITIALIZED = 4,
	/* Incomplete instruction. */
	FCML_CEH_GEC_EOF = 5,
	/* Used mainly in case of integers and offsets. */
	FCML_CEH_GEC_VALUE_OUT_OF_RANGE = 6,
	/* Chosen operation is not supported in case of given configuration. */
	FCML_CEH_GEC_FEATURE_NOT_SUPPORTED = 7,
	/* Unsupported addressing mode. For instance encoded instruction
	 * needs 16 bit addressing mode, but we are in 64 bit mode. */
	FCML_CEH_GEC_INVALID_ADDRESSING_MODE = 8,
	/* Chosen addressing form can not be encoded as for example ModR/M field. */
	FCML_CEH_GEC_INVALID_ADDRESSING_FORM = 9,
	/* Unsupported instruction form (Instruction may be supported, but not with given set of operands). */
	FCML_CEH_GEC_INVALID_INSTRUCTION_FORM = 10,
	/* Instruction do not support one of the defined operands. */
	FCML_CEH_GEC_INVALID_OPPERAND = 11,
	/* Unknown mnemonic. */
	FCML_CEH_GEC_UNKNOWN_MNEMONIC = 12,
	/* Operand size (Operand size attribute) is not allowed in given context. */
	FCML_CEH_GEC_INVALID_OPPERAND_SIZE = 13,
	/* Address size (Address size attribute) is not allowed in given context. */
	FCML_CEH_GEC_INVALID_ADDRESS_SIZE = 14,
	/* User chosen unsupported addressing form */
	FCML_CEH_GEC_UNKNOWN_INSTRUCTION = 15,
	/* Assembler can return this error code if there is not allowed prefix defined for given instruction. */
	FCML_CEH_GEC_INVALID_PREFIX = 16,
	/* Wrong register type. */
	FCML_CEH_GEC_INVALID_REGISTER_TYPE = 17,
	/* Wrong register. */
	FCML_CEH_GEC_INVALID_REGISTER = 18,
	/* Error returned by parsers when there is undefined symbol used. */
	FCML_CEH_GEC_UNDEFINED_SYMBOL = 19,
};

enum fcml_en_ceh_message_errors {
	/* Segment register can not be overridden. */
	FCML_CEH_MEC_ERROR_ILLEGAL_SEG_REG_OVERRIDE = 1000,
	/* To many operands passed to parser. */
	FCML_CEH_MEC_ERROR_TO_MANY_OPERANDS = 1001,
	/* Unsupported pseudo-op value. */
	FCML_CEH_MEC_ERROR_INVALID_PSEUDO_OPCODE_VALUE = 1002,
	/* HLE prefix is not allowed in given context. */
	FCML_CEH_MEC_ERROR_HLE_PREFIX_NOT_ALLOWED = 1003,
	/* There is more than one HLE prefix. */
	FCML_CEH_MEC_ERROR_HLE_MORE_THAN_ONE_PREFIX = 1004,
	/* Expression attempts to divide by 0 */
	FCML_CEH_MEC_ERROR_DIVISION_BY_0 = 1005,
	/* Wrong value type used in given context. For example float used in place of integer. */
	FCML_CEH_MEC_ERROR_WRONG_VALUE_FORMAT = 1006,
	/* Value out of range, for example 32 bit value used as segment selector. */
	FCML_CEH_MEC_ERROR_VALUE_OUT_OF_RANGE = 1007,
	/* Syntax error from parser. */
	FCML_CEH_MEC_ERROR_INVALID_SYNTAX = 1008,
	/* Wrong register type used in place of segment register. */
	FCML_CEH_MEC_ERROR_INVALID_REGISTER_TYPE_SEG = 1009,
	/* Symbol is already defined in parser's symbol table. */
	FCML_CEH_MEC_ERROR_SYMBOL_ALREADY_DEFINED = 1010,
	/* Symbol is undefined. */
	FCML_CEH_MEC_ERROR_UNDEFINED_SYMBOL = 1011,
	/* Parsed line exceed maximal allowed length. */
	FCML_CEH_MEC_ERROR_PARSED_LINE_TOO_LONG = 1012,
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

/* Information about one particular event. */
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
