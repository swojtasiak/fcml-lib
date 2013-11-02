/*
 * fcml_disassembler_result.h
 *
 *  Created on: Oct 20, 2013
 *      Author: tas
 */

#ifndef FCML_DISASSEMBLER_RESULT_H_
#define FCML_DISASSEMBLER_RESULT_H_

#include "fcml_common.h"

#define FCML_DASM_PREFIXES_COUNT	12

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

typedef struct fcml_st_dasm_disassembler_result {
	fcml_st_ceh_error_container *errors;
	/* Mnemonic */
	fcml_bool is_shortcut;
	fcml_bool is_pseudo_op_shortcut;
	fcml_string mnemonic;
	fcml_uint8_t instruction_code[FCML_INSTRUCTION_SIZE];
	fcml_data_size instruction_size;
	fcml_st_dasm_prefixes prefixes;
	fcml_st_dasm_operand_details operand_details[FCML_OPERANDS_COUNT];
	fcml_st_operand operands[FCML_OPERANDS_COUNT];
	fcml_bool is_conditional;
	fcml_st_condition condition;
	fcml_hints hints;
} fcml_st_dasm_disassembler_result;

#endif /* FCML_DISASSEMBLER_RESULT_H_ */
