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
#include "fcml_modrm.h"

typedef enum fcml_en_attribute_size_flag {
	FCML_EN_ASF_ANY = 0x00,
	FCML_EN_ASF_16 = 0x01,
	FCML_EN_ASF_32 = 0x02,
	FCML_EN_ASF_64 = 0x04
} fcml_en_attribute_size_flag;

typedef struct fcml_st_asm_data_size_flags {
	fcml_nuint8_t l;
	fcml_en_attribute_size_flag allowed_effective_address_size;
	fcml_data_size effective_address_size;
	fcml_data_size effective_operand_size;
} fcml_st_asm_data_size_flags;

typedef struct fcml_st_encoder_acceptor_context {
	// Assembler configuration.
	fcml_st_assembler_context *assembler_context;
	fcml_en_attribute_size_flag asa_attr_flags;
	fcml_en_attribute_size_flag esa_attr_flags;
} fcml_st_encoder_acceptor_context;

typedef struct fcml_st_asm_encoding_context {
	fcml_st_asm_data_size_flags data_size_flags;
	fcml_st_modrm mod_rm;
	fcml_st_encoded_modrm encoded_mod_rm;
	fcml_st_assembler_context *assembler_context;
	fcml_st_instruction *instruction;
	fcml_st_assembler_result *result;
	fcml_nint8_t instruction_size;
} fcml_st_asm_encoding_context;

#endif /* FCML_ASM_INT_H_ */
