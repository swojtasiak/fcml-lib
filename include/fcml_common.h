/*
 * fcml_int_common.h
 *
 *  Created on: 04-02-2013
 *      Author: tAs
 */

#ifndef FCML_INT_COMMON_H_
#define FCML_INT_COMMON_H_

#include "fcml_types.h"

#define FCML_OPERANDS_COUNT			5
#define FCML_INSTRUCTION_SIZE 		15
#define FCML_OPCODES_NUM			3

#define FCML_PREFIX_LOCK			0x0001
#define FCML_PREFIX_REPNE			0x0002
#define FCML_PREFIX_REPNZ			FCML_PREFIX_REPNE
#define FCML_PREFIX_REP				0x0004
#define FCML_PREFIX_REPE			FCML_PREFIX_REP
#define FCML_PREFIX_REPZ			FCML_PREFIX_REP
#define FCML_PREFIX_XACQUIRE		0x0008
#define FCML_PREFIX_XRELEASE		0x0010
#define FCML_PREFIX_BRANCH_HINT		0x0020
#define FCML_PREFIX_NOBRANCH_HINT	0x0040

/* Supported addressing modes. */
typedef enum fcml_en_addr_form {
	/* Real-addressing mode, virtual 8086 mode. */
	FCML_AF_16_BIT = 1,
	/* Protected/Compatibility mode when 'D' segment descriptor flag is set to 1.*/
	FCML_AF_32_BIT,
	/* 64-bit mode. ('L' flag of segment descriptor set to 1.)*/
	FCML_AF_64_BIT,
} fcml_en_addr_form;

/* Simple types. */

typedef fcml_uint16_t fcml_hints;
typedef fcml_uint16_t fcml_prefixes;

/* Instruction pointer.*/

typedef union fcml_st_instruction_pointer {
	fcml_uint32_t eip;
	fcml_uint64_t rip;
} fcml_st_instruction_pointer;

/* Effective Operand-Size Attributes.*/

#define FCML_EOSA_UNDEF	0
#define FCML_EOSA_16	16
#define FCML_EOSA_32	32
#define FCML_EOSA_64	64

/* Effective Address-Size Attributes.*/

#define FCML_EASA_UNDEF	16
#define FCML_EASA_16	16
#define FCML_EASA_32	32
#define FCML_EASA_64	64

/* Register numbers.*/

#define FCML_REG_AL		0
#define FCML_REG_AX		0
#define FCML_REG_EAX	0
#define FCML_REG_RAX	0
#define FCML_REG_MM0	0
#define FCML_REG_XMM0	0
#define FCML_REG_YMM0	0

#define FCML_REG_CL		1
#define FCML_REG_CX		1
#define FCML_REG_ECX	1
#define FCML_REG_RCX	1
#define FCML_REG_MM1	1
#define FCML_REG_XMM1	1
#define FCML_REG_YMM1	1

#define FCML_REG_DL		2
#define FCML_REG_DX		2
#define FCML_REG_EDX	2
#define FCML_REG_RDX	2
#define FCML_REG_MM2	2
#define FCML_REG_XMM2	2
#define FCML_REG_YMM2	2

#define FCML_REG_BL		3
#define FCML_REG_BX		3
#define FCML_REG_EBX	3
#define FCML_REG_RBX	3
#define FCML_REG_MM3	3
#define FCML_REG_XMM3	3
#define FCML_REG_YMM3	3

#define FCML_REG_AH		4
#define FCML_REG_SP		4
#define FCML_REG_SPL	4
#define FCML_REG_ESP	4
#define FCML_REG_RSP	4
#define FCML_REG_MM4	4
#define FCML_REG_XMM4	4
#define FCML_REG_YMM4	4

#define FCML_REG_CH		5
#define FCML_REG_BP		5
#define FCML_REG_BPL	5
#define FCML_REG_EBP	5
#define FCML_REG_RBP	5
#define FCML_REG_MM5	5
#define FCML_REG_XMM5	5
#define FCML_REG_YMM5	5

#define FCML_REG_DH		6
#define FCML_REG_SI		6
#define FCML_REG_SIL	6
#define FCML_REG_ESI	6
#define FCML_REG_RSI	6
#define FCML_REG_MM6	6
#define FCML_REG_XMM6	6
#define FCML_REG_YMM6	6

#define FCML_REG_BH		7
#define FCML_REG_DI		7
#define FCML_REG_DIL	7
#define FCML_REG_EDI	7
#define FCML_REG_RDI	7
#define FCML_REG_MM7	7
#define FCML_REG_XMM7	7
#define FCML_REG_YMM7	7

#define FCML_REG_R8L	8
#define FCML_REG_R8W	8
#define FCML_REG_R8D	8
#define FCML_REG_R8		8
#define FCML_REG_XMM8	8
#define FCML_REG_YMM8	8

#define FCML_REG_R9L	9
#define FCML_REG_R9W	9
#define FCML_REG_R9D	9
#define FCML_REG_R9		9
#define FCML_REG_XMM9	9
#define FCML_REG_YMM9	9

#define FCML_REG_R10L	10
#define FCML_REG_R10W	10
#define FCML_REG_R10D	10
#define FCML_REG_R10	10
#define FCML_REG_XMM10	10
#define FCML_REG_YMM10	10

#define FCML_REG_R11L	11
#define FCML_REG_R11W	11
#define FCML_REG_R11D	11
#define FCML_REG_R11	11
#define FCML_REG_XMM11	11
#define FCML_REG_YMM11	11

#define FCML_REG_R12L	12
#define FCML_REG_R12W	12
#define FCML_REG_R12D	12
#define FCML_REG_R12	12
#define FCML_REG_XMM12	12
#define FCML_REG_YMM12	12

#define FCML_REG_R13L	13
#define FCML_REG_R13W	13
#define FCML_REG_R13D	13
#define FCML_REG_R13	13
#define FCML_REG_XMM13	13
#define FCML_REG_YMM13	13

#define FCML_REG_R14L	14
#define FCML_REG_R14W	14
#define FCML_REG_R14D	14
#define FCML_REG_R14	14
#define FCML_REG_XMM14	14
#define FCML_REG_YMM14	14

#define FCML_REG_R15L	15
#define FCML_REG_R15W	15
#define FCML_REG_R15D	15
#define FCML_REG_R15	15
#define FCML_REG_XMM15	15
#define FCML_REG_YMM15	15

/* Segment registers. */

#define FCML_REG_ES		0
#define FCML_REG_CS		1
#define FCML_REG_SS		2
#define FCML_REG_DS		3
#define FCML_REG_FS		4
#define FCML_REG_GS		5

/* FPU registers */

#define FCML_REG_ST0	0
#define FCML_REG_ST1	1
#define FCML_REG_ST2	2
#define FCML_REG_ST3	3
#define FCML_REG_ST4	4
#define FCML_REG_ST5	5
#define FCML_REG_ST6	6
#define FCML_REG_ST7	7

/* Control registers. */

#define FCML_REG_CR0	0
#define FCML_REG_CR2	2
#define FCML_REG_CR3	3
#define FCML_REG_CR4	4
#define FCML_REG_CR8	8

/* Debug register. */

#define FCML_REG_DR0	0
#define FCML_REG_DR1	1
#define FCML_REG_DR2	2
#define FCML_REG_DR3	3
#define FCML_REG_DR4	4
#define FCML_REG_DR5	5
#define FCML_REG_DR6	6
#define FCML_REG_DR7	7

/* Constants used to describe data size. */

#define FCML_DS_UNDEF   0
#define FCML_DS_8    	8
#define FCML_DS_16   	16
#define FCML_DS_32   	32
#define FCML_DS_64   	64
#define FCML_DS_128  	128
#define FCML_DS_256  	256

/* Size operators. */

#define FCML_OS_UNDEFINED	0
#define FCML_OS_BYTE		8
#define FCML_OS_WORD		16
#define FCML_OS_DWORD		32
#define FCML_OS_FWORD		48
#define FCML_OS_QWORD		64
#define FCML_OS_MWORD		64
#define FCML_OS_TBYTE		80
#define FCML_OS_OWORD		128
#define FCML_OS_XWORD		128
#define FCML_OS_YWORD		256

typedef enum fcml_en_register {
    FCML_REG_UNDEFINED = 0,
    FCML_REG_GPR,
    FCML_REG_SIMD,
    FCML_REG_FPU,
    FCML_REG_SEG,
    FCML_REG_CR,
    FCML_REG_DR,
    FCML_REG_IP
} fcml_en_register;

typedef struct fcml_st_register {
    fcml_en_register type;
    fcml_data_size size;
    fcml_uint8_t reg;
    /* In case of SPL,BPL,SIL,DIL GPR registers has to be set to true.*/
    fcml_bool x64_exp;
} fcml_st_register;

/*********************************
 * Conditions.
 *********************************/

#define FCML_NUMBER_OF_CONDITIONS  8

typedef enum fcml_en_condition_type {
    /* 0 Overflow*/
    FCML_CONDITION_O = 0,
    /* 1 Below*/
    FCML_CONDITION_B,
    /* 2 Equal*/
    FCML_CONDITION_E,
    /* 3 Below or equal*/
    FCML_CONDITION_BE,
    /* 4 Sign*/
    FCML_CONDITION_S,
    /* 5 Parity*/
    FCML_CONDITION_P,
    /* 6 Less than*/
    FCML_CONDITION_L,
    /* 7 Less than or equal to*/
    FCML_CONDITION_LE
} fcml_en_condition_type;

typedef struct fcml_st_condition {
    /* Condition type.*/
    fcml_en_condition_type condition_type;
    /* True if condition should be negated.*/
    fcml_bool is_negation;
} fcml_st_condition;

/*********************************
 * Size attributes flags.
 *********************************/

typedef enum fcml_en_attribute_size_flag {
    FCML_EN_ASF_ANY = 0x00,
    FCML_EN_ASF_16 = 0x01,
    FCML_EN_ASF_32 = 0x02,
    FCML_EN_ASF_64 = 0x04,
    FCML_EN_ASF_ALL = FCML_EN_ASF_16 | FCML_EN_ASF_32 | FCML_EN_ASF_64
} fcml_en_attribute_size_flag;

typedef struct fcml_st_nullable_size_flags {
    fcml_bool is_set;
    fcml_en_attribute_size_flag flags;
} fcml_st_nullable_size_flags;

/*********************************
 * Operands.
 *********************************/

typedef enum fcml_en_access_mode {
	FCML_AM_ACCESS_MODE_UNDEFINED = 0,
	FCML_AM_READ = 0x01,
	FCML_AM_WRITE = 0x02,
	FCML_AM_READ_WRITE = FCML_AM_READ | FCML_AM_WRITE
} fcml_en_access_mode;

typedef struct fcml_st_immediate {
	fcml_data_size imm_size;
	fcml_bool is_signed;
	/* Data fields. */
	fcml_uint8_t imm8;
	fcml_uint16_t imm16;
	fcml_uint32_t imm32;
	fcml_uint64_t imm64;
} fcml_st_immediate;

typedef struct fcml_st_far_pointer {
    fcml_uint16_t segment;
    fcml_data_size offset_size;
    /* Data fields. */
	fcml_uint16_t offset16;
	fcml_uint32_t offset32;
} fcml_st_far_pointer;

typedef struct fcml_st_displacement {
	fcml_data_size size;
	fcml_bool is_signed;
	/* Data fields. */
	fcml_int8_t dis8;
	fcml_int16_t dis16;
	fcml_int32_t dis32;
	fcml_int64_t dis64;
} fcml_st_displacement;

/* *******************************************/
/* *  Memory addressing using Mod/RM field  **/
/* *******************************************/

typedef enum fcml_en_address_form {
	/* Default value set if memory addressing hasn't been configured.*/
	FCML_AF_UNDEFINED,
    /* Only displacement value interpreted but it's assembler who decides*/
    /* what addressing should be used absolute or relative.*/
    FCML_AF_OFFSET,
    /* Effective address combined from more address components.*/
    FCML_AF_COMBINED
} fcml_en_effective_address_form;

typedef struct fcml_st_offset {
	fcml_data_size size;
	fcml_bool is_signed;
	/* Data fields. */
	fcml_int16_t off16;
	fcml_int32_t off32;
	fcml_int64_t off64;
} fcml_st_offset;

typedef struct fcml_st_effective_address {
    fcml_st_register base;
    fcml_st_register index;
    fcml_uint8_t scale_factor;
    fcml_st_displacement displacement;
} fcml_st_effective_address;

typedef struct fcml_st_segment_selector {
	fcml_st_register segment_selector;
	fcml_bool is_default_reg;
} fcml_st_segment_selector;

typedef struct fcml_st_address {
	/* Size of data accessed in memory.*/
	fcml_data_size size_operator;
    /* Memory addressing format ABSOLUTE/RELATIVE etc.*/
    fcml_en_effective_address_form address_form;
    /* Segment register.*/
    fcml_st_segment_selector segment_selector;
    /* Memory address for FCML_AF_COMBINED form.*/
    fcml_st_effective_address effective_address;
    /* Memory address for FCML_AF_ABSOLUTE and FCML_AF_RELATIVE form.*/
    fcml_st_offset offset;
} fcml_st_address;

typedef enum fcml_en_operand_type {
	FCML_EOT_NONE,
    FCML_EOT_IMMEDIATE,
    FCML_EOT_FAR_POINTER,
    FCML_EOT_ADDRESS,
    FCML_EOT_REGISTER
} fcml_en_operand_type;

typedef enum fcml_en_operand_hints {
    FCML_OP_HINT_MULTIMEDIA_INSTRUCTION = 0x0001,
    FCML_OP_HINT_DISPLACEMENT_RELATIVE_ADDRESS = 0x0002,
    FCML_OP_HINT_PSEUDO_OPCODE = 0x0004,
    FCML_OP_HINT_ABSOLUTE_ADDRESSING = 0x0008,
    FCML_OP_HINT_RELATIVE_ADDRESSING = 0x0010,
    FCML_OP_HINT_SIB_ENCODING = 0x0020
} fcml_en_operand_hints;

typedef struct fcml_st_operand {
    fcml_en_operand_type type;
    fcml_hints hints;
	fcml_st_immediate immediate;
	fcml_st_far_pointer far_pointer;
	fcml_st_address address;
	fcml_st_register reg;
} fcml_st_operand;

/*********************************
 * Instruction definition.
 *********************************/

typedef enum fcml_en_instruction_hints {
    FCML_HINT_FAR_POINTER = 0x0001,
    FCML_HINT_NEAR_POINTER = 0x0002,
    FCML_HINT_LONG_FORM_POINTER = 0x0004,
	FCML_HINT_INDIRECT_POINTER = 0x0008
} fcml_en_instruction_hints;

/* Generic instruction definition used by assembler and disassembler to encode/decode instruction. */
typedef struct fcml_st_instruction {
	fcml_prefixes prefixes;
    fcml_hints hints;
    fcml_char *mnemonic;
    fcml_bool is_conditional;
    fcml_st_condition condition;
    fcml_st_operand operands[FCML_OPERANDS_COUNT];
    fcml_int operands_count;
} fcml_st_instruction;

/*********************************
 * Instruction definition.
 *********************************/

typedef struct fcml_st_instruction_code {
    fcml_uint8_t *code;
    fcml_usize code_length;
} fcml_st_instruction_code;

/****************************
 * Instruction entry point.
 ****************************/

typedef struct fcml_st_entry_point {
	/* Processor addressing mode 16/32/64-bit.*/
	fcml_en_addr_form addr_form;
	/* Default address/operand size attribute (See 'D' flag of segment descriptor.)*/
	fcml_data_size address_size_attribute;
	fcml_data_size operand_size_attribute;
	/* Instruction pointer EIP/RIP. Take into account that even in 16 bit mode EIP register is used.*/
	fcml_st_instruction_pointer ip;
} fcml_st_entry_point;

#endif /* FCML_INT_COMMON_H_ */
