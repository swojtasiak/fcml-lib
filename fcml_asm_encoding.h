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
#include "fcml_ceh.h"
#include "fcml_coll.h"
#include "fcml_common.h"
#include "fcml_modrm_encoder.h"
#include "fcml_assembler.h"

#define FCML_ASM_MAX_PART_PROCESSORS	40

// REX prefix.
#define FCML_ENCODE_REX_BASE		0x40
#define FCML_ENCODE_REX_W(rex,w)	( rex | ( w << 3 ) )
#define FCML_ENCODE_REX_R(rex,r)	( rex | ( r << 2 ) )
#define FCML_ENCODE_REX_X(rex,x)	( rex | ( x << 1 ) )
#define FCML_ENCODE_REX_B(rex,b)	( rex | b )

// XOP/VEX prefixes.
#define FCML_ENCODE_VEXOP_MMMM(vexop,x)		( ( vexop ) | ( ( x ) & 0x1F ) )
#define FCML_ENCODE_VEXOP_VVVV(vexop,x)		( ( vexop ) | ( ( ~( x ) & 0x0F ) << 3 ) )
#define FCML_ENCODE_VEXOP_PP(vexop,x)		( ( vexop ) | ( ( x ) & 0x03 ) )
#define FCML_ENCODE_VEXOP_W(vexop,x)		( ( vexop ) | ( ( ( x ) & 0x01 ) << 7 ) )
#define FCML_ENCODE_VEXOP_L(vexop,x)		( ( vexop ) | ( ( ( x ) & 0x01 ) << 2 ) )
// R,X and B are stored in 1's complement form.
#define FCML_ENCODE_VEXOP_R(vexop,x)		( ( vexop ) | ( ( ~( x ) & 0x01 ) << 7 ) )
#define FCML_ENCODE_VEXOP_X(vexop,x)		( ( vexop ) | ( ( ~( x ) & 0x01 ) << 6 ) )
#define FCML_ENCODE_VEXOP_B(vexop,x)		( ( vexop ) | ( ( ~( x ) & 0x01 ) << 5 ) )

#define FCML_ASM_FCF	16

typedef enum fcml_en_attribute_size_flag {
	FCML_EN_ASF_ANY = 0x00,
	FCML_EN_ASF_16 = 0x01,
	FCML_EN_ASF_32 = 0x02,
	FCML_EN_ASF_64 = 0x04,
	FCML_EN_ASF_ALL = FCML_EN_ASF_16 | FCML_EN_ASF_32 | FCML_EN_ASF_64
} fcml_en_attribute_size_flag;

struct fcml_st_asm_instruction_part;

typedef struct fcml_st_asm_nullable_size_flags {
	fcml_bool is_set;
	fcml_en_attribute_size_flag flags;
} fcml_st_asm_nullable_size_flags;

typedef struct fcml_st_asm_data_size_flags {
	fcml_nuint8_t l;
	// Flags describing all EOSa sizes available for given addressing mode.
	fcml_st_asm_nullable_size_flags allowed_effective_operand_size;
	fcml_st_asm_nullable_size_flags allowed_effective_address_size;
	// Effective address/operand size chosen for currently processed address mode. If set can not be changed anymore.
	// It has higher priority than flags above.
	fcml_data_size effective_address_size;
	fcml_data_size effective_operand_size;
} fcml_st_asm_data_size_flags;

typedef union fcml_st_asm_part_processor_cache {
	// Cached immediate value. It's for example used by IMM acceptor to pass converted value to encoder.
	fcml_st_immediate imm16;
	fcml_st_immediate imm32;
	fcml_st_immediate imm64;
} fcml_st_asm_part_processor_cache;

typedef struct fcml_st_asm_part_processor_context {
	fcml_st_asm_part_processor_cache cache[FCML_ASM_MAX_PART_PROCESSORS];
	int part_processor_index;
} fcml_st_asm_part_processor_context;

typedef struct fcml_st_asm_extension_prefixes_fields {
	fcml_uint8_t vvvv;
	fcml_uint8_t mmmm;
} fcml_st_asm_extension_prefixes_fields;

typedef struct fcml_st_asm_opcode_reg {
	fcml_uint8_t opcode_reg;
	fcml_uint8_t ext_b;
} fcml_st_asm_opcode_reg;

typedef struct fcml_st_asm_encoding_context {
#ifdef FCML_DEBUG
	int __def_index;
#endif
	fcml_st_asm_part_processor_context part_processor_context;
	fcml_st_asm_data_size_flags data_size_flags;
	fcml_st_asm_extension_prefixes_fields epf;
	fcml_st_modrm mod_rm;
	fcml_st_encoded_modrm encoded_mod_rm;
	fcml_st_assembler_context *assembler_context;
	fcml_st_instruction *instruction;
	fcml_st_assembler_result *result;
	fcml_st_asm_opcode_reg opcode_reg;
	fcml_nint8_t instruction_size;
} fcml_st_asm_encoding_context;

typedef fcml_ceh_error (*fcml_st_asm_instruction_part_post_processor)( fcml_st_asm_encoding_context *context, struct fcml_st_asm_instruction_part *instruction_part, fcml_ptr post_processor_args );

typedef struct fcml_st_asm_instruction_part {
	fcml_uint8_t code[10];
	int code_length;
	fcml_ptr post_processor_args;
	fcml_st_asm_instruction_part_post_processor post_processor;
} fcml_st_asm_instruction_part;

typedef struct fcml_st_asm_instruction_part_container {
	// Address of the instruction parts array.
	fcml_st_asm_instruction_part *instruction_parts;
	// Number of instruction parts in the array.
	int count;
} fcml_st_asm_instruction_part_container;

struct fcml_st_asm_instruction_addr_modes;

typedef enum fcml_ien_asm_part_processor_phase {
	// ModR/M arguments filling.
	FCML_IEN_ASM_IPPP_FIRST_PHASE,
	// ModR/M encoding.
	FCML_IEN_ASM_IPPP_SECOND_PHASE,
	// Prefixes are applied in this phase.
	FCML_IEN_ASM_IPPP_THIRD_PHASE
} fcml_ien_asm_part_processor_phase;

typedef struct fcml_st_asm_addr_mode_desc_details {
	// Pre-calculated flags describing which ASA and OSA values are available for addressing mode.
	fcml_en_attribute_size_flag allowed_osa;
	fcml_en_attribute_size_flag allowed_asa;
} fcml_st_asm_addr_mode_desc_details;

typedef fcml_ceh_error (*fcml_fnp_asm_operand_encoder)( fcml_ien_asm_part_processor_phase phase, fcml_st_asm_encoding_context *context, fcml_st_def_addr_mode_desc *addr_mode_desc, fcml_st_def_decoded_addr_mode *addr_mode, fcml_st_operand *operand_def, fcml_st_asm_instruction_part *operand_enc );
typedef fcml_ceh_error (*fcml_fnp_asm_operand_acceptor)( fcml_st_asm_encoding_context *context, fcml_st_asm_addr_mode_desc_details *addr_mode_details, fcml_st_def_addr_mode_desc *addr_mode_desc, fcml_st_def_decoded_addr_mode *addr_mode, fcml_st_operand *operand_def, fcml_st_asm_instruction_part *operand_enc );
typedef fcml_ceh_error (*fcml_fnp_asm_instruction_encoder)( fcml_st_asm_encoding_context *context, struct fcml_st_asm_instruction_addr_modes *addr_modes );
typedef fcml_hints (*fcml_fnp_asm_instruction_hints_calculator)( fcml_st_def_addr_mode_desc *addr_mode, fcml_st_def_decoded_addr_mode *decoded_addr_mode );

typedef struct fcml_st_asm_operand_encoder_def {
	fcml_fnp_asm_operand_encoder encoder;
	fcml_fnp_asm_operand_acceptor acceptor;
	fcml_fnp_asm_instruction_hints_calculator hints_calculator;
} fcml_st_asm_operand_encoder_def;

typedef enum fcml_ien_asm_instruction_part_processor_type {
	FCML_IEN_ASM_IPPT_VERIFIER,
	FCML_IEN_ASM_IPPT_ENCODER,
	FCML_IEN_ASM_IPPT_DECORATOR,
} fcml_ien_asm_instruction_part_processor_type;

typedef fcml_ceh_error (*fcml_ifn_asm_instruction_part_processor)( fcml_ien_asm_part_processor_phase phase, fcml_st_asm_encoding_context *context, fcml_st_def_addr_mode_desc *addr_mode_def, fcml_st_asm_instruction_part *instruction_part, fcml_ptr args );
typedef fcml_ceh_error (*fcml_ifn_asm_instruction_part_processor_acceptor)( fcml_st_asm_encoding_context *context, fcml_st_asm_addr_mode_desc_details *addr_mode_details, fcml_st_def_addr_mode_desc *addr_mode_desc, fcml_st_instruction *instruction, fcml_ptr args );

typedef struct fcml_ifn_asm_instruction_part_processor_descriptor {
	fcml_ifn_asm_instruction_part_processor processor_encoder;
	fcml_ifn_asm_instruction_part_processor_acceptor processor_acceptor;
	fcml_ien_asm_instruction_part_processor_type processor_type;
	fcml_ptr processor_args;
	fcml_fp_env_memory_free_handler processor_args_deallocator;
} fcml_ifn_asm_instruction_part_processor_descriptor;

typedef fcml_ifn_asm_instruction_part_processor_descriptor (*fcml_ifn_asm_instruction_part_processor_factory)( fcml_uint32_t flags, fcml_st_def_instruction_description *instruction, fcml_st_def_addr_mode_desc *addr_mode, fcml_hints *hints, fcml_ceh_error *error );

typedef struct fcml_ifn_asm_instruction_part_processor_chain {
	struct fcml_ifn_asm_instruction_part_processor_chain *next_processor;
	fcml_ifn_asm_instruction_part_processor_descriptor processor_descriptor;
} fcml_ifn_asm_instruction_part_processor_chain;

typedef fcml_ifn_asm_instruction_part_processor_chain* (*fcml_ifn_asm_instruction_part_processor_factory_dispatcher)( fcml_st_def_instruction_description *instruction, fcml_st_def_addr_mode_desc *addr_mode, int *parts, fcml_hints *hints, fcml_ceh_error *error );

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
	// Some pre-calculated information about instruction addressing mode. This structure can be helpful, because
	// some details of the addressing mode can be pre-calculate while addressing mode is processed in initialization mode.
	// So we can get some performance improvements.
	fcml_st_asm_addr_mode_desc_details addr_mode_details;
	// Chain of instruction part processors registered for instruction addressing mode.
	fcml_ifn_asm_instruction_part_processor_chain *part_processor_chain;
	// Number of instruction parts needed to assemble described instruction.
	int instruction_parts;
	// Addressing mode related hints.
	fcml_hints hints;
} fcml_st_asm_instruction_addr_mode;

// Optimizer definition.
typedef fcml_ceh_error (*fcml_fnp_asm_optimizer_callback)( fcml_st_asm_encoding_context *context, fcml_st_asm_instruction_addr_mode *addr_mode, fcml_ptr args );
typedef fcml_ceh_error (*fcml_fnp_asm_optimizer)( fcml_st_asm_encoding_context *context, fcml_st_asm_instruction_addr_mode *addr_mode, fcml_fnp_asm_optimizer_callback callback, fcml_ptr args );

void fcml_fn_free_instruction_parts( fcml_st_coll_list *instruction_parts );
fcml_ceh_error fcml_fn_asm_init_instruction_encodings();
fcml_ceh_error fcml_fn_asm_get_instruction_encodings( fcml_string mnemonic, fcml_st_asm_instruction_addr_modes ** );
void fcml_fn_asm_free_instruction_encodings();

#endif /* FCML_ASM_ENCODING_H_ */
