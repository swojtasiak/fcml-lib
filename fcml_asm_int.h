/*
 * fcml_asm_int.h
 *
 *  Created on: 24-03-2013
 *      Author: tAs
 */

#ifndef FCML_ASM_INT_H_
#define FCML_ASM_INT_H_

#include "fcml_coll.h"
#include "fcml_common.h"
#include "fcml_stream.h"
#include "fcml_assembler.h"

typedef struct fcml_st_asm_encoded_operand {
	// Scace for encoded operands.
	fcml_st_memory_stream encoded_operand;
} fcml_st_asm_encoded_operand;

typedef struct fcml_st_asm_encoding_context {
	fcml_st_asm_encoded_operand encoded_operands[FCML_OPERANDS_COUNT];
	fcml_st_assembler_result *result;
} fcml_st_asm_encoding_context;

#endif /* FCML_ASM_INT_H_ */
