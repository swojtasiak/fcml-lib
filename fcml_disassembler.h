/*
 * fcml_disassembler.h
 *
 *  Created on: 08-02-2013
 *      Author: tAs
 */

#ifndef FCML_DISASSEMBLER_H_
#define FCML_DISASSEMBLER_H_

#include "fcml_ceh.h"
#include "fcml_common.h"
#include "fcml_dialect.h"
#include "fcml_types.h"

#define FCML_DASM_PREFIXES_COUNT	12
#define FCML_DASM_CONDITIONAL_GROUP_1	0x00
#define FCML_DASM_CONDITIONAL_GROUP_2	0x01

typedef struct fcml_st_dasm_disassembler {
} fcml_st_dasm_disassembler;

typedef struct fcml_st_dasm_disassembler_configuration {
	fcml_bool choose_carry_conditional_mnemonic;
	fcml_uint8_t conditional_group;
	fcml_bool use_short_form_mnemonics;
	fcml_bool extend_displacement_to_asa;
} fcml_st_dasm_disassembler_configuration;

typedef struct fcml_st_dasm_disassembler_context {
	fcml_st_dasm_disassembler *disassembler;
	fcml_st_dasm_disassembler_configuration configuration;
	fcml_en_addr_form addr_form;
	fcml_data_size address_size_attribute;
	fcml_data_size operand_size_attribute;
	fcml_ptr code_address;
	fcml_data_size code_size;
	fcml_st_instruction_pointer ip;
} fcml_st_dasm_disassembler_context;

/* Prefixes */

typedef enum fcml_st_dasm_prefix_types {
	FCML_PT_GROUP_UNKNOWN = 0,
	FCML_PT_GROUP_1 = 1,
	FCML_PT_GROUP_2,
	FCML_PT_GROUP_3,
	FCML_PT_GROUP_4,
	FCML_PT_REX,
	FCML_PT_VEX,
	FCML_PT_XOP,
} fcml_st_dasm_prefix_types;

typedef struct fcml_st_dasm_instruction_prefix {
	/* Prefix itself. */
	fcml_uint8_t prefix;
	/* Type of prefix, see enumeration above. */
	fcml_st_dasm_prefix_types prefix_type;
	/* 1 if prefix can be treated as mandatory one. */
	fcml_bool mandatory_prefix;
	/* Place for additional bytes of VEX prefix. */
	fcml_uint8_t vex_xop_bytes[2];
} fcml_st_dasm_instruction_prefix;

typedef struct fcml_st_dasm_prefixes {
	fcml_st_dasm_instruction_prefix prefixes[FCML_DASM_PREFIXES_COUNT];
	fcml_int prefixes_count;
	fcml_int prefixes_bytes_count;
	// Fast lookups.
	fcml_bool is_lock;
	fcml_bool is_rep;
	fcml_bool is_repne;
	fcml_bool is_xrelease;
	fcml_bool is_xacquire;
	fcml_bool is_vex;
	fcml_bool is_xop;
	fcml_bool is_rex;
	// Fields.
	fcml_uint8_t vex_xop_first_byte;
	fcml_uint8_t r;
	fcml_uint8_t x;
	fcml_uint8_t b;
	fcml_uint8_t w;
	fcml_uint8_t l;
	fcml_uint8_t mmmm;
	fcml_uint8_t vvvv;
	fcml_uint8_t pp;
} fcml_st_dasm_prefixes;

typedef struct fcml_st_dasm_operand_details {
	fcml_en_access_mode access_mode;
} fcml_st_dasm_operand_details;

/* Additional details provided by disassembler. */
typedef struct fcml_st_dasm_instruction_details {
	fcml_bool is_shortcut;
	fcml_bool is_pseudo_op_shortcut;
	fcml_uint8_t instruction_code[FCML_INSTRUCTION_SIZE];
	fcml_data_size instruction_size;
	fcml_st_dasm_prefixes prefixes;
	fcml_st_dasm_operand_details operand_details[FCML_OPERANDS_COUNT];
	fcml_bool opcode_field_s_bit;
	fcml_bool opcode_field_w_bit;
} fcml_st_dasm_instruction_details;

typedef struct fcml_st_dasm_disassembler_result {
	fcml_st_ceh_error_container *errors;
	fcml_st_dasm_instruction_details instruction_details;
	fcml_st_instruction instruction;
} fcml_st_dasm_disassembler_result;

fcml_ceh_error fcml_fn_dasm_disassembler_init( fcml_st_dialect_context *context, fcml_st_dasm_disassembler **disassembler );
fcml_ceh_error fcml_fn_dasm_disassemble( fcml_st_dasm_disassembler_context *context, fcml_st_dasm_disassembler_result **result );
void fcml_fn_dasm_disassemble_result_free( fcml_st_dasm_disassembler_result *result );
void fcml_fn_dasm_disassembler_free( fcml_st_dasm_disassembler *disassembler );

#endif /* FCML_DISASSEMBLER_H_ */
