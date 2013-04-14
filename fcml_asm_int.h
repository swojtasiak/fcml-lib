/*
 * fcml_asm_int.h
 *
 *  Created on: 24-03-2013
 *      Author: tAs
 */

#ifndef FCML_ASM_INT_H_
#define FCML_ASM_INT_H_

#include "fcml_coll.h"

typedef struct fcml_st_asm_instruction_encoding {
	/* Pointer to the next decoding. There is no need to provide additional structure for one directional list */
	struct fcml_st_asm_instruction_encoding *next_instruction_encoding;
	/* Opcodes. */
	uint8_t opcodes[3];
	/* Flags that describe prefixes usage. */
	uint16_t prefixes_flags;
	/* Flags that describe some details of opcodes. */
	uint32_t opcode_flags;
} fcml_st_asm_instruction_encoding;

typedef struct fcml_st_asm_encoded_operand {

} fcml_st_asm_encoded_operand;

typedef struct fcml_st_asm_encodeing_context {

} fcml_st_asm_encodeing_context;

#endif /* FCML_ASM_INT_H_ */
