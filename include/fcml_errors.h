/*
 * fcml_asm_errors.h
 *
 *  Created on: 10-05-2013
 *      Author: tAs
 */

#ifndef FCML_ASM_ERRORS_H_
#define FCML_ASM_ERRORS_H_

enum fcml_en_ceh_error_globals {
	FCML_CEH_GEC_NO_ERROR = 0,
	FCML_CEH_GEC_UNKNOWN_ERROR,
	FCML_CEH_GEC_OUT_OF_MEMORY,
	FCML_CEH_GEC_DATA_ERROR,
	FCML_CEH_GEC_INTERNAL_BUG,
	FCML_CEH_GEC_INVALID_INPUT,
	FCML_CEH_GEC_NO_SPACE_LEFT,
	FCML_CEH_GEC_NOT_INITIALIZED,
	FCML_CEH_GEC_EOF,
	FCML_CEH_GEC_VALUE_OUT_OF_RANGE,
	FCML_CEH_GEC_ILLEGAL_STATE_EXCEPTION,
	FCML_CEH_GEC_NOT_SUPPORTED,
	FCML_CEH_GEC_INDEX_OUT_OF_BOUND,
	/* Assembler. */
	FCML_CEH_AEC_ILLEGAL_SEG_REG_OVERRIDE,
	FCML_CEH_AEC_INVALID_PSEUDO_OPCODE_VALUE,
	FCML_CEH_AEC_HLE_PREFIX_NOT_ALLOWED,
	FCML_CEH_AEC_HLE_MORE_THAN_ONE_PREFIX,
	FCML_EN_UNKNOWN_MNEMONIC,
	/* Rest. */
	FCML_EN_UNSUPPORTED_ADDRESSING_MODE,
	FCML_EN_UNSUPPORTED_OPPERAND,
	FCML_EN_UNSUPPORTED_OPPERAND_SIZE,
	FCML_EN_UNSUPPORTED_ADDRESS_SIZE,
	FCML_EN_RIP_DISPLACEMENT_NOT_SET,
	FCML_EN_UNSUPPORTED_ADDRESSING_FORM,
	FCML_EN_UNKNOWN_INSTRUCTION,
	FCML_EN_UNSUPPORTED_PREFIX,
	FCML_EN_UNKNOWN_DATA_SIZE_FOR_MEMORY_ADDRESSING,
	/* AST.*/
	FCML_EN_APC_AST_ERROR_TO_MANY_OPERANDS,
	FCML_EN_APC_AST_ERROR_UNSUPPORTED_NODE_IN_EXPRESSION,
	FCML_EN_APC_AST_ERROR_DIVISION_BY_0,
	FCML_EN_APC_AST_ERROR_WRONG_VALUE_FORMAT,
	FCML_EN_APC_AST_ERROR_VALUE_OUT_OF_RANGE,
	/* parser/Lexer.*/
	FCML_EN_X64IP_ERROR_CAN_NOT_INITIALIZE_LEXER,
	FCML_EN_X64IP_ERROR_INV_SYNTAX
};

enum fcml_en_ceh_message_warnings {
	FCML_EN_APC_AST_WARN_VALUE_OUT_OF_RANGE
};

typedef fcml_uint16_t fcml_ceh_error;

typedef enum fcml_en_ceh_error_level {
	FCML_EN_CEH_EL_WARN,
	FCML_EN_CEH_EL_ERROR,
	FCML_EN_CEH_EL_FATAL
} fcml_en_ceh_error_level;

typedef struct fcml_st_ceh_error_info {
	struct fcml_st_ceh_error_info *next_error;
	fcml_string message;
	fcml_ceh_error code;
	fcml_en_ceh_error_level level;
} fcml_st_ceh_error_info;

typedef struct fcml_st_ceh_error_container {
	fcml_st_ceh_error_info *errors;
	fcml_st_ceh_error_info *last_error;
} fcml_st_ceh_error_container;

#endif /* FCML_ASM_ERRORS_H_ */
