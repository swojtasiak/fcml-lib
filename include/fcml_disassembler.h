/*
 * fcml_disassembler.h
 *
 *  Created on: 08-02-2013
 *      Author: tAs
 */

#ifndef FCML_DISASSEMBLER_H_
#define FCML_DISASSEMBLER_H_

#include "fcml_lib_export.h"

#include "fcml_instructions.h"
#include "fcml_types.h"
#include "fcml_errors.h"
#include "fcml_common.h"
#include "fcml_dialect.h"

#ifdef __cplusplus
extern "C" {
#endif

#define FCML_DASM_PREFIXES_COUNT	12

#define FCML_DASM_CONDITIONAL_GROUP_1	0x00
#define FCML_DASM_CONDITIONAL_GROUP_2	0x01

/* This structure and type definition represents an abstract disassembler. */
typedef struct fcml_st_disassembler fcml_st_disassembler;

/* Disassembler configuration. */
typedef struct fcml_st_disassembler_conf {
	/* Set to true in order to make disassembler to increment IP address by length of the disassembled instruction. */
	fcml_bool increment_ip;
	/* True if optional error and warning messages should be collected during processing. */
	fcml_bool enable_error_messages;
    /* True if suffixes for carry flag has to be used by disassembler.*/
	fcml_bool carry_flag_conditional_suffix;
	/* There are two groups of suffixes for conditional instructions, you can choose which one should be used.*/
	fcml_uint8_t conditional_group;
	/* Set to true in order to use short forms of encoded instructions.
	 * For instance 'cmpsb' will be used instead of 'cmps byte ptr [si],byte ptr [di]' */
	fcml_bool short_forms;
	/* True if displacement should be sign extended to effective address size; otherwise false. */
	fcml_bool extend_disp_to_asa;
} fcml_st_disassembler_conf;

/* Disassembler context. */
typedef struct fcml_st_disassembler_context {
    /* Disassembler used to decode instructions. */
	fcml_st_disassembler *disassembler;
	/* Disassembler configuration. */
	fcml_st_disassembler_conf configuration;
	/* Instruction entry point configuration. */
	fcml_st_entry_point entry_point;
	/* Pointer to the encoded instruction. */
	fcml_ptr code;
	/* Size of the code in the buffer above. */
	fcml_data_size code_length;
} fcml_st_disassembler_context;

/* Prefixes */

/* Available types of instruction prefixes. */
typedef enum fcml_en_prefix_types {
	FCML_PT_GROUP_UNKNOWN = 0,
	FCML_PT_GROUP_1 = 1,
	FCML_PT_GROUP_2,
	FCML_PT_GROUP_3,
	FCML_PT_GROUP_4,
	FCML_PT_REX,
	FCML_PT_VEX,
	FCML_PT_XOP,
} fcml_en_prefix_types;

/* Describes one decoded prefix. */
typedef struct fcml_st_instruction_prefix {
	/* Prefix itself. */
	fcml_uint8_t prefix;
	/* Type of prefix, see enumeration above. */
	fcml_en_prefix_types prefix_type;
	/* 1 if prefix can be treated as mandatory one. */
	fcml_bool mandatory_prefix;
	/* Place for additional bytes of VEX prefix. */
	fcml_uint8_t vex_xop_bytes[2];
} fcml_st_instruction_prefix;

/* Contains some information about all decoded instruction prefixes. */
typedef struct fcml_st_prefixes_details {
    /* All decoded prefixes are available here as raw bytes.*/
	fcml_st_instruction_prefix prefixes[FCML_DASM_PREFIXES_COUNT];
	/* Number of decoded prefixes.*/
	fcml_int prefixes_count;
	/* Number of bytes used by all decoded prefixes.*/
	fcml_int prefixes_bytes_count;
	/* Some flags indicating existence of prefixes.*/
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
	/* Various fields encoded inside decoded prefixes.*/
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
    /* ModR/M byte if exists.*/
	fcml_uint8_t modrm;
	/* SIB byte if exists.*/
	fcml_nuint8_t sib;
	/* True if RIP encoding is used by decoded instruction. This flag is used only in 64 bit mode.*/
	fcml_bool is_rip;
} fcml_st_decoded_modrm_details;

// TODO:Dodac mozliwosc sprawdzenia czy jest modrm.


/* Additional details provided by disassembler. */
typedef struct fcml_st_instruction_details {
    /* True if this is a shortcut. Shortcuts do not have any operands decoded. A good example of
     * such instruction is 'cmpsb' as opposed to 'cmps byte ptr [si],byte ptr [di]'. It's very important
     * to take this information into consideration because there is no operadns for such instruction.
     */
	fcml_bool is_shortcut;
	/* True if given instruction is a short form of pseudo-ops instructions. See 'vcmpunordsd' for instance. */
	fcml_bool is_pseudo_op;
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
	/* Instruction code. */
	fcml_en_instruction instruction;
	/*  Addressing form of the instruction above. */
	fcml_uint16_t addr_mode;
} fcml_st_instruction_details;

/* Disassembler result. */
typedef struct fcml_st_dasm_disassembler_result {
    /* All errors and warnings messages going there.*/
	fcml_st_ceh_error_container errors;
	/* Detailed information about instructions.*/
	fcml_st_instruction_details instruction_details;
	/* Decoded instruction in its generic form.*/
	fcml_st_instruction instruction;
} fcml_st_disassembler_result;

LIB_EXPORT fcml_ceh_error LIB_CALL fcml_fn_disassembler_init( fcml_st_dialect *dialect, fcml_st_disassembler **disassembler );
LIB_EXPORT fcml_ceh_error LIB_CALL fcml_fn_disassemble( fcml_st_disassembler_context *context, fcml_st_disassembler_result *result );
LIB_EXPORT void LIB_CALL fcml_fn_disassembler_result_prepare( fcml_st_disassembler_result *result );
LIB_EXPORT void LIB_CALL fcml_fn_disassembler_result_free( fcml_st_disassembler_result *result );
LIB_EXPORT void LIB_CALL fcml_fn_disassembler_free( fcml_st_disassembler *disassembler );

#ifdef __cplusplus
}
#endif

#endif /* FCML_DISASSEMBLER_H_ */
