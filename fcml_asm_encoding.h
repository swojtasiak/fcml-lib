/*
 * fcml_asm_encoding.h
 *
 *  Created on: 31-03-2013
 *      Author: tAs
 */

#ifndef FCML_ASM_ENCODING_H_
#define FCML_ASM_ENCODING_H_

#include "fcml_env.h"
#include "fcml_def.h"
#include "fcml_asm_int.h"
#include "fcml_ceh.h"
#include "fcml_coll.h"
#include "fcml_common.h"

typedef struct fcml_st_asm_instruction_part {
	fcml_uint8_t code[10];
	int code_length;
} fcml_st_asm_instruction_part;

typedef struct fcml_st_asm_instruction_part_container {
	// Address of the instruction parts array.
	fcml_st_asm_instruction_part *instruction_parts;
	// Number of instruction parts in the array.
	int count;
} fcml_st_asm_instruction_part_container;

struct fcml_st_asm_instruction_addr_modes;

typedef enum fcml_ien_asm_part_processor_phase {
	FCML_IEN_ASM_IPPP_ACCEPT,
	FCML_IEN_ASM_IPPP_FIRST_PHASE,
	FCML_IEN_ASM_IPPP_SECOND_PHASE
} fcml_ien_asm_part_processor_phase;

typedef fcml_bool (*fcml_fnp_asm_operand_encoder)( fcml_ien_asm_part_processor_phase phase, fcml_st_asm_encoding_context *context, fcml_st_def_decoded_addr_mode *addr_mode, fcml_st_operand *operand_def, fcml_st_asm_instruction_part *operand_enc );
typedef fcml_ceh_error (*fcml_fnp_asm_instruction_encoder)( fcml_st_asm_encoding_context *context, struct fcml_st_asm_instruction_addr_modes *addr_modes );

typedef enum fcml_ien_asm_instruction_part_processor_type {
	FCML_IEN_ASM_IPPT_ENCODER,
	FCML_IEN_ASM_IPPT_DECORATOR,
} fcml_ien_asm_instruction_part_processor_type;

typedef fcml_ceh_error (*fcml_ifn_asm_instruction_part_processor)( fcml_ien_asm_part_processor_phase phase, fcml_st_asm_encoding_context *context, fcml_st_asm_instruction_part *instruction_part, fcml_ptr args );
typedef fcml_bool (*fcml_ifn_asm_instruction_part_processor_acceptor)( fcml_st_instruction *instruction, fcml_ptr args );

typedef struct fcml_ifn_asm_instruction_part_processor_descriptor {
	fcml_ifn_asm_instruction_part_processor processor;
	fcml_ifn_asm_instruction_part_processor_acceptor processor_acceptor;
	fcml_ien_asm_instruction_part_processor_type processor_type;
	fcml_ptr processor_args;
	fcml_fp_env_memory_free_handler processor_args_deallocator;
} fcml_ifn_asm_instruction_part_processor_descriptor;

typedef fcml_ifn_asm_instruction_part_processor_descriptor (*fcml_ifn_asm_instruction_part_processor_factory)( fcml_uint32_t flags, fcml_st_def_instruction_description *instruction, fcml_st_def_addr_mode_desc *addr_mode, fcml_ceh_error *error );

typedef struct fcml_ifn_asm_instruction_part_processor_chain {
	struct fcml_ifn_asm_instruction_part_processor_chain *next_processor;
	fcml_ifn_asm_instruction_part_processor_descriptor processor_descriptor;
} fcml_ifn_asm_instruction_part_processor_chain;

typedef fcml_ifn_asm_instruction_part_processor_chain* (*fcml_ifn_asm_instruction_part_processor_factory_dispatcher)( fcml_st_def_instruction_description *instruction, fcml_st_def_addr_mode_desc *addr_mode, int *parts, fcml_ceh_error *error );

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
	// Chain of instruction part processors registered for instruction addressing mode.
	fcml_ifn_asm_instruction_part_processor_chain *part_processor_chain;
	// Number of instruction parts needed to assemble described instruction.
	int instruction_parts;
} fcml_st_asm_instruction_addr_mode;

void fcml_fn_free_instruction_parts( fcml_st_coll_list *instruction_parts );
fcml_ceh_error fcml_fn_asm_init_instruction_encodings();
fcml_ceh_error fcml_fn_asm_get_instruction_encodings( fcml_string mnemonic, fcml_st_asm_instruction_addr_modes ** );
void fcml_fn_asm_free_instruction_encodings();

#endif /* FCML_ASM_ENCODING_H_ */
