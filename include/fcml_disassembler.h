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

/* This structure and type definition represents an abstract disassembler. */
typedef struct fcml_st_disassembler {
} fcml_st_disassembler;

/* Disassembler configuration. */
typedef struct fcml_st_disassembler_conf {
    // True if suffixes for carry flag has to be used by disassembler.
	fcml_bool carry_flag_conditional_suffix;
	// There are two groups of suffixes for conditional instructions, you can choose which one should be used.
	fcml_uint8_t conditional_group;
	/* Set to true in order to use short forms of encoded instructions.
	 * For insatnce 'cmpsb' will be used instead of 'cmps byte ptr [si],byte ptr [di]' */
	fcml_bool short_forms;
	/* True if disaplacement should be sign extended to effective address size; otherwise false. */
	fcml_bool extend_disp_to_asa;
} fcml_st_disassembler_conf;

/* Disassembler context. */
typedef struct fcml_st_disassembler_context {
    // Disassembler used to decode instructions.
	fcml_st_disassembler *disassembler;
	// Disassembler configuration.
	fcml_st_disassembler_conf configuration;
	// Addressing mode: 16, 32 or 64 bit.
	fcml_en_addr_form addr_form;
	// Default address size attribute.
	fcml_data_size address_size_attribute;
	// Default operand size attribute.
	fcml_data_size operand_size_attribute;
	// Pointer to the encoded instruction.
	fcml_ptr code;
	// Size of the code in the buffer above.
	fcml_data_size code_length;
	// Instruction pointer EIP/RIP. Take into account that even in 16 bit mode EIP register is used.
	fcml_st_instruction_pointer ip;
} fcml_st_disassembler_context;

/* Prefixes */

/* Available types of instruction prefixes. */
typedef enum fcml_st_prefix_types {
	FCML_PT_GROUP_UNKNOWN = 0,
	FCML_PT_GROUP_1 = 1,
	FCML_PT_GROUP_2,
	FCML_PT_GROUP_3,
	FCML_PT_GROUP_4,
	FCML_PT_REX,
	FCML_PT_VEX,
	FCML_PT_XOP,
} fcml_st_prefix_types;

/* Describes one decoded prefix. */
typedef struct fcml_st_instruction_prefix {
	/* Prefix itself. */
	fcml_uint8_t prefix;
	/* Type of prefix, see enumeration above. */
	fcml_st_prefix_types prefix_type;
	/* 1 if prefix can be treated as mandatory one. */
	fcml_bool mandatory_prefix;
	/* Place for additional bytes of VEX prefix. */
	fcml_uint8_t vex_xop_bytes[2];
} fcml_st_instruction_prefix;

/* Contains some information about all decoded instruction prefixes. */
typedef struct fcml_st_prefixes_details {
    // All decoded prefixes are available here as raw bytes.
	fcml_st_instruction_prefix prefixes[FCML_DASM_PREFIXES_COUNT];
	// Number of decoded prefixes.
	fcml_int prefixes_count;
	// Number of bytes used by all decoded prefixes.
	fcml_int prefixes_bytes_count;
	// Some flags indicating existence of prefixes.
	fcml_bool is_branch;
	fcml_bool is_nobranch;
	fcml_bool is_lock;
	fcml_bool is_rep;
	fcml_bool is_repne;
	fcml_bool is_xrelease;
	fcml_bool is_xacquire;
	fcml_bool is_vex;
	fcml_bool is_xop;
	fcml_bool is_rex;
	// Various fields encoded inside decoded prefixes.
	fcml_uint8_t vex_xop_first_byte;
	fcml_uint8_t r;
	fcml_uint8_t x;
	fcml_uint8_t b;
	fcml_uint8_t w;
	fcml_uint8_t l;
	fcml_uint8_t mmmm;
	fcml_uint8_t vvvv;
	fcml_uint8_t pp;
} fcml_st_prefixes_details;

/* Some disassembler specific information about decoded operands. */
typedef struct fcml_st_operand_details {
	fcml_en_access_mode access_mode;
} fcml_st_operand_details;

/* Some basic information about decoded ModR/M and SIB bytes. */
typedef struct fcml_st_decoded_modrm_details {
    // ModR/M byte is exists.
	fcml_uint8_t modrm;
	// SIB byte if exists.
	fcml_nuint8_t sib;
	// True if RIP encoding is used by decoded instruction. This flag is used only in 64 bit mode.
	fcml_bool is_rip;
} fcml_st_decoded_modrm_details;

/* Additional details provided by disassembler. */
typedef struct fcml_st_instruction_details {
    /* True if this is a shortcut. Shortcuts do not have any operands decoded. A good example of
     * such instruction is 'cmpsb' as opposed to 'cmps byte ptr [si],byte ptr [di]'. It's very important
     * to take this information into consideration because there is no operadns for such instruction. */
	fcml_bool is_shortcut;
	/* True if given instruction is a short form of pseudo-ops instructions. See 'vcmpunordsd' for instance. */
	fcml_bool is_pseudo_op_shortcut;
	/* Code of disassembled instruction. */
	fcml_uint8_t instruction_code[FCML_INSTRUCTION_SIZE];
	/* Instruction size in bytes. */
	fcml_data_size instruction_size;
	/* Some information about decoded instruction prefixes. */
	fcml_st_prefixes_details prefixes_details;
	/* All disassembler specific information about opcodes going there. */
	fcml_st_operand_details operand_details[FCML_OPERANDS_COUNT];
	/* Some useful details about decoded ModR/M and SIB bytes. */
	fcml_st_decoded_modrm_details modrm_details;
	/* Opcode field 's'. This is set only for informational purpose only,
	 * you should not use it for any critical functionality.*/
	fcml_bool opcode_field_s_bit;
	/* Opcode field 'w'. This is set only for informational purpose only,
	 * you should not use it for any critical functionality.*/
	fcml_bool opcode_field_w_bit;
} fcml_st_instruction_details;

/* Disassembler result. */
typedef struct fcml_st_dasm_disassembler_result {
    // All errors and warnings messages going there.
	fcml_st_ceh_error_container errors;
	// Detailed information about instructions.
	fcml_st_instruction_details instruction_details;
	// Decoded instruction in its generic form.
	fcml_st_instruction instruction;
} fcml_st_disassembler_result;

fcml_ceh_error fcml_fn_disassembler_init( fcml_st_dialect *dialect, fcml_st_disassembler **disassembler );
fcml_ceh_error fcml_fn_disassemble( fcml_st_disassembler_context *context, fcml_st_disassembler_result **result );
void fcml_fn_disassemble_result_free( fcml_st_disassembler_result *result );
void fcml_fn_disassembler_free( fcml_st_disassembler *disassembler );

#endif /* FCML_DISASSEMBLER_H_ */
