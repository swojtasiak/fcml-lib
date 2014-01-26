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
	FCML_CEH_GEC_NO_ERROR = 0,
	FCML_CEH_GEC_OUT_OF_MEMORY,
	FCML_CEH_GEC_INVALID_INPUT,
	FCML_CEH_GEC_INTERNAL_BUG,
	// TODO: Usunąć , wewnetrznie COLL.h nie powinien używc error code tylko jakies swoje wewnetrzne kody bledow,ktore nie powinny leciec do uzytkownia.
	FCML_CEH_GEC_NO_SPACE_LEFT,
	// Component hasn't been initialized yet.
	FCML_CEH_GEC_NOT_INITIALIZED,
	FCML_CEH_GEC_EOF,
	// Used mainly in case of integers and offsets.
	FCML_CEH_GEC_VALUE_OUT_OF_RANGE,
	// TODO: Chyba nie do konca odpowiednie dla uzytkownika koncowego, powinno byc raczej jako blad krytyczny i tyle, ewentualnie nie udalo sie znalezc mnemoniki.
	FCML_CEH_GEC_ILLEGAL_STATE_EXCEPTION,
	/* Assembler. */
	FCML_CEH_GEC_UNSUPPORTED_ADDRESSING_MODE,
	FCML_CEH_GEC_UNKNOWN_MNEMONIC,
	/* Rest. */
	FCML_CEH_GEC_UNSUPPORTED_OPPERAND,
	FCML_CEH_GEC_UNSUPPORTED_OPPERAND_SIZE,
	FCML_CEH_GEC_UNSUPPORTED_ADDRESS_SIZE,
	// TODO: Czym sie rozni od FCML_CEH_GEC_UNSUPPORTED_ADDRESSING_MODE.
	FCML_CEH_GEC_UNSUPPORTED_ADDRESSING_FORM,
	FCML_CEH_GEC_UNKNOWN_INSTRUCTION,
	FCML_CEH_GEC_UNSUPPORTED_PREFIX,
	FCML_CEH_GEC_UNKNOWN_DATA_SIZE_FOR_MEMORY_ADDRESSING
};

enum fcml_en_ceh_message_errors {
	FCML_CEH_MEC_ERROR_ILLEGAL_SEG_REG_OVERRIDE,
	FCML_CEH_MEC_ERROR_TO_MANY_OPERANDS,
	FCML_CEH_MEC_ERROR_INVALID_PSEUDO_OPCODE_VALUE,
	FCML_CEH_MEC_ERROR_HLE_PREFIX_NOT_ALLOWED,
	FCML_CEH_MEC_ERROR_HLE_MORE_THAN_ONE_PREFIX,
	FCML_CEH_MEC_ERROR_DIVISION_BY_0,
	FCML_CEH_MEC_ERROR_WRONG_VALUE_FORMAT,
	FCML_CEH_MEC_ERROR_VALUE_OUT_OF_RANGE,
	FCML_CEH_MEC_ERROR_INVALID_SYNTAX
};

enum fcml_en_ceh_message_warnings {
	FCML_CEH_MEW_WARN_VALUE_OUT_OF_RANGE
};

typedef fcml_uint16_t fcml_ceh_error;

/* Information level. */
typedef enum fcml_en_ceh_error_level {
	FCML_EN_CEH_EL_WARN, FCML_EN_CEH_EL_ERROR
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
