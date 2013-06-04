/*
 * fcml_asm_errors.h
 *
 *  Created on: 10-05-2013
 *      Author: tAs
 */

#ifndef FCML_ASM_ERRORS_H_
#define FCML_ASM_ERRORS_H_

#include "fcml_ceh.h"

#define FCML_ERROR_CODE_BASE	FCML_CEH_USER_ERROR_CODE_BASE + 1250
#define FCML_WARN_CODE_BASE		FCML_CEH_USER_ERROR_CODE_BASE + 1500

// Errors.
enum fcml_en_asm_errors {
	FCML_EN_UNKNOWN_MNEMONIC = FCML_ERROR_CODE_BASE,
	FCML_EN_UNSUPPORTED_ADDRESSING_MODE = FCML_ERROR_CODE_BASE + 1,
	FCML_EN_UNSUPPORTED_OPPERAND = FCML_ERROR_CODE_BASE + 2,
	FCML_EN_UNSUPPORTED_OPPERAND_SIZE = FCML_ERROR_CODE_BASE + 3,
	FCML_EN_UNSUPPORTED_ADDRESS_SIZE = FCML_ERROR_CODE_BASE + 4
};

// Warnings.
//enum fcml_en_asm_warnings {
//};

#endif /* FCML_ASM_ERRORS_H_ */
