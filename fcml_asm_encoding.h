/*
 * fcml_asm_encoding.h
 *
 *  Created on: 31-03-2013
 *      Author: tAs
 */

#ifndef FCML_ASM_ENCODING_H_
#define FCML_ASM_ENCODING_H_

#include "fcml_def.h"
#include "fcml_asm_int.h"
#include "fcml_ceh.h"
#include "fcml_coll.h"
#include "fcml_common.h"

typedef struct fcml_st_asm_instruction_part {
	fcml_st_memory_stream encoded_operand;
} fcml_st_asm_instruction_part;

struct fcml_st_asm_instruction_addr_modes;

typedef fcml_bool (*fcml_fnp_asm_operand_encoder)( fcml_st_operand *operand_def, fcml_st_asm_encoded_operand *operand_enc );
typedef fcml_ceh_error (*fcml_fnp_asm_instruction_encoder)( fcml_st_asm_encoding_context *context, struct fcml_st_asm_instruction_addr_modes *addr_modes );

typedef enum fcml_ien_asm_instruction_part_processor_type {
	FCML_IEN_ASM_IPPT_ENCODER,
	FCML_IEN_ASM_IPPT_DECORATOR,
} fcml_ien_asm_instruction_part_processor_type;

typedef void (*fcml_ifn_asm_instruction_part_processor)( fcml_st_asm_encoding_context *context );

typedef fcml_ifn_asm_instruction_part_processor (*fcml_ifn_asm_instruction_part_processor_factory)( fcml_st_def_instruction_description *instruction, fcml_st_def_addr_mode_desc *addr_mode, fcml_ien_asm_instruction_part_processor_type *processor_type );

typedef struct fcml_ifn_asm_instruction_part_processor_chain {
	struct fcml_ifn_asm_instruction_part_processor_chain *next_processor;
	fcml_ifn_asm_instruction_part_processor processor;
	fcml_ien_asm_instruction_part_processor_type processor_type;
} fcml_ifn_asm_instruction_part_processor_chain;

typedef fcml_ifn_asm_instruction_part_processor_chain* (*fcml_ifn_asm_instruction_part_processor_factory_dispatcher)( fcml_st_def_instruction_description *instruction, fcml_st_def_addr_mode_desc *addr_mode );

typedef struct fcml_st_asm_operand_encoder {
	// Typ obslugiwany przez ponizszy encoder, uzywany w zasadzie tylko z powodow wydajnosciowych, aby wstepnie porownac typy.
	fcml_en_operand_type supported_operand_type;
	// Enkoder wlasciwy odpowiedzialnyz za enkodowanie operandu.
	fcml_fnp_asm_operand_encoder operand_encoder;
	// Argumenty dla enkodera.
	fcml_st_def_decoded_addr_mode* decoded_addr_mode;
} fcml_st_asm_operand_encoder;

typedef struct fcml_st_asm_instruction_addr_modes {
	// All addressing modes for given mnemonic are available in this list.
	fcml_st_coll_list *addr_modes;
	// Mnemonic.
	fcml_string mnemonic;
	// Instruction encoder.
	fcml_fnp_asm_instruction_encoder instruction_encoder;
} fcml_st_asm_instruction_addr_modes;

typedef struct fcml_st_asm_instruction_addr_mode {
	// Instruction definition.
	fcml_st_def_addr_mode_desc *addr_mode_desc;
	// Akceptory operandow odpowiedzialne za wstepna akceptacje operandów.
	fcml_st_asm_operand_encoder operand_encoders[FCML_OPERANDS_COUNT];
	// Chain of instruction part processors registered for instruction addressing mode.
	fcml_ifn_asm_instruction_part_processor_chain *part_processor_chain;
} fcml_st_asm_instruction_addr_mode;

fcml_ceh_error fcml_fn_asm_init_instruction_encodings();
fcml_ceh_error fcml_fn_asm_get_instruction_encodings( fcml_string mnemonic, fcml_st_asm_instruction_addr_modes ** );
void fcml_fn_asm_free_instruction_encodings();

#endif /* FCML_ASM_ENCODING_H_ */
