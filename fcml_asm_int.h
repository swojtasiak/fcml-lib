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
#include "fcml_asm_encoding.h"

typedef struct fcml_st_asm_encoding_context {
	fcml_st_assembler_context *assembler_context;
	fcml_st_instruction *instruction;
	fcml_st_assembler_result *result;
} fcml_st_asm_encoding_context;

#endif /* FCML_ASM_INT_H_ */
