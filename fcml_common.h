/*
 * fcml_int_common.h
 *
 *  Created on: 04-02-2013
 *      Author: tAs
 */

#ifndef FCML_INT_COMMON_H_
#define FCML_INT_COMMON_H_

#include "fcml_types.h"

#define FCML_OPERANDS_COUNT	5

typedef enum fcml_en_addr_form {
	FCML_AF_16_BIT,
	FCML_AF_32_BIT,
	FCML_AF_64_BIT,
} fcml_en_addr_form;

// Effective Operand-Size Attributes.

#define FCML_EOSA_UNDEF	0
#define FCML_EOSA_16	16
#define FCML_EOSA_32	32
#define FCML_EOSA_64	64

// Effective Address-Size Attributes.

#define FCML_EASA_UNDEF	16
#define FCML_EASA_16	16
#define FCML_EASA_32	32
#define FCML_EASA_64	64

// Register numbers.

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
#define FCML_OS_TBYTE		80
#define FCML_OS_OWORD		128
#define FCML_OS_YWORD		256

typedef enum fcml_en_register {
    FCML_REG_UNDEFINED = 0,
    FCML_REG_GPR,
    FCML_REG_SIMD,
    FCML_REG_FPU,
    FCML_REG_SEG,
    FCML_REG_CR,
    FCML_REG_DR,
} fcml_en_register;

typedef struct fcml_st_register {
    fcml_en_register type;
    fcml_data_size size;
    fcml_uint8_t reg;
    // In case of SPL,BPL,SIL,DIL GPR registers has to be set to true.
    fcml_bool x64_exp;
} fcml_st_register;

/*********************************
 * Operands.
 *********************************/

typedef struct fcml_st_immediate {
	fcml_data_size imm_size;
    union {
        uint8_t imm8;
        uint16_t imm16;
        uint32_t imm32;
    };
} fcml_st_immediate;

typedef struct fcml_st_far_pointer {
    fcml_uint16_t segment;
    fcml_data_size offset_size;
    union {
        fcml_uint16_t offset16;
        fcml_uint32_t offset32;
    };
} fcml_st_far_pointer;

typedef struct fcml_st_displacement {
	fcml_data_size size;
    fcml_data_size sign_extension;
    union {
        int8_t dis8;
        int16_t dis16;
        int32_t dis32;
    };
} fcml_st_displacement;

typedef struct fcml_st_effective_address {
	fcml_uint16_t size_operator;
	fcml_st_register segment_selector;
    fcml_st_register base;
    fcml_st_register index;
    fcml_uint8_t scale_factor;
    fcml_st_displacement displacement;
} fcml_st_effective_address;

// TODO: nie mam pojecia dla jakiego trybu adresowania to zostawilem, jak sobie przypome dodac przyklad trybu.
typedef struct fcml_st_offset {
	fcml_data_size size;
    union {
        uint16_t off16;
        uint32_t off32;
        uint64_t off64;
    };
} fcml_st_offset;

typedef enum fcml_en_operand_type {
	FCML_EOT_NONE,
    FCML_EOT_IMMEDIATE,
    FCML_EOT_FAR_POINTER,
    FCML_EOT_EFFECTIVE_ADDRESS,
    FCML_EOT_OFFSET,
    FCML_EOT_REGISTER
} fcml_en_operand_type;

typedef struct fcml_st_operand {
    fcml_en_operand_type type;
    union {
        fcml_st_immediate immediate;
        fcml_st_far_pointer far_pointer;
        fcml_st_effective_address effective_address;
        fcml_st_offset offset;
        fcml_st_register reg;
    };
} fcml_st_operand;

/*********************************
 * Instruction definition.
 *********************************/

typedef enum fcml_en_explicit_prefixes {
	FCML_PREFIX_NONE,
    FCML_PREFIX_LOCK,
    FCML_PREFIX_WAIT,
    FCML_PREFIX_REPNE,
    FCML_PREFIX_REPE
} fcml_en_explicit_prefixes;

typedef struct fcml_st_instruction {
    fcml_en_explicit_prefixes prefixes;
    fcml_char *mnemonic;
    fcml_st_operand operands[FCML_OPERANDS_COUNT];
    int operands_count;
} fcml_st_instruction;

#endif /* FCML_INT_COMMON_H_ */
