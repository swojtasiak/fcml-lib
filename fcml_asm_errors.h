/*
 * fcml_asm_errors.h
 *
 *  Created on: 10-05-2013
 *      Author: tAs
 */

#ifndef FCML_ASM_ERRORS_H_
#define FCML_ASM_ERRORS_H_

#include "fcml_ceh.h"

#define FCML_PARSER_ASM_ERROR_CODE_BASE	FCML_CEH_USER_ERROR_CODE_BASE + 1250
#define FCML_PARSER_ASM_WARN_CODE_BASE	FCML_CEH_USER_ERROR_CODE_BASE + 1500

// Errors.
enum fcml_en_asm_errors {
	FCML_EN_ASM_UNKNOWN_MNEMONIC = FCML_PARSER_ASM_ERROR_CODE_BASE,
	FCML_EN_ASM_UNSUPPORTED_ADDRESSING_MODE = FCML_PARSER_ASM_ERROR_CODE_BASE + 1
};

// Warnings.
//enum fcml_en_asm_warnings {
//};

#endif /* FCML_ASM_ERRORS_H_ */
