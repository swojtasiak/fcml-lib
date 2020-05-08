/*
 * FCML - Free Code Manipulation Library.
 * Copyright (C) 2010-2020 Slawomir Wojtasiak
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

/** @file fcml_common.h
 * Definitions of common structures used by FCML components.
 * @copyright Copyright (C) 2010-2020 Slawomir Wojtasiak. All rights reserved.
 * This project is released under the GNU Lesser General Public License.
 */

#ifndef FCML_INT_COMMON_H_
#define FCML_INT_COMMON_H_

#include "fcml_lib_export.h"

#include "fcml_types.h"
#include "fcml_instructions.h"

/** Maximal number of the instruction operands. */
#define FCML_OPERANDS_COUNT           5
/** Maximal number of bytes instruction can use. */
#define FCML_INSTRUCTION_SIZE         15
/** Number of opcode bytes. */
#define FCML_OPCODES_NUM              3

/**
 * @defgroup PREFIX_GROUP Explicit prefixes
 * List of prefixes that can be explicitly defined for instruction.
 * @{
 */

/** LOCK prefix (0xF0)*/
#define FCML_PREFIX_LOCK            0x0001
/** REPNE prefix (0xF2) */
#define FCML_PREFIX_REPNE           0x0002
/** REPNZ prefix (0xF2) */
#define FCML_PREFIX_REPNZ           FCML_PREFIX_REPNE
/** REP prefix (0xF3) */
#define FCML_PREFIX_REP             0x0004
/** REPE prefix (0xF3) */
#define FCML_PREFIX_REPE            FCML_PREFIX_REP
/** REPZ prefix (0xF3) */
#define FCML_PREFIX_REPZ            FCML_PREFIX_REP
/** XACQUIRE prefix (0xF2) */
#define FCML_PREFIX_XACQUIRE        0x0008
/** XRELEASE prefix (0xF3) */
#define FCML_PREFIX_XRELEASE        0x0010
/** branch hint (0x2E) (SSE2 extension)*/
#define FCML_PREFIX_BRANCH_HINT     0x0020
/** nobranch hint (0x3E) (SSE2 extension)*/
#define FCML_PREFIX_NOBRANCH_HINT   0x0040

/** @} */

/**
 *  Supported processor operating modes.
 */
typedef enum fcml_en_operating_mode {
    /** Real-addressing mode, virtual 8086 mode. */
    FCML_OM_16_BIT = 1,
    /** Protected/Compatibility mode when 'D' segment descriptor
     * flag is set to 1. */
    FCML_OM_32_BIT,
    /** 64-bit mode. ('L' flag of segment descriptor set to 1.) */
    FCML_OM_64_BIT,
} fcml_en_operating_mode;

/* Simple types. */

/** Type used for storing instruction and operand hint masks. */
typedef fcml_uint16_t fcml_hints;

/**
 * Type for explicit instruction prefixes bit mask.
 */
typedef fcml_uint16_t fcml_prefixes;

/**
 * General instruction pointer holder.
 */
typedef fcml_int64_t fcml_ip;

/* Register numbers.*/

/**
 * @defgroup REGISTERS_GROUP Registers.
 * All supported x64_64 registers are defined here.
 * @{
 */

#define FCML_REG_AL     0
#define FCML_REG_AX     0
#define FCML_REG_EAX    0
#define FCML_REG_RAX    0
#define FCML_REG_MM0    0
#define FCML_REG_XMM0   0
#define FCML_REG_YMM0   0
#define FCML_REG_ZMM0   0

#define FCML_REG_CL     1
#define FCML_REG_CX     1
#define FCML_REG_ECX    1
#define FCML_REG_RCX    1
#define FCML_REG_MM1    1
#define FCML_REG_XMM1   1
#define FCML_REG_YMM1   1
#define FCML_REG_ZMM1   1

#define FCML_REG_DL     2
#define FCML_REG_DX     2
#define FCML_REG_EDX    2
#define FCML_REG_RDX    2
#define FCML_REG_MM2    2
#define FCML_REG_XMM2   2
#define FCML_REG_YMM2   2
#define FCML_REG_ZMM2   2

#define FCML_REG_BL     3
#define FCML_REG_BX     3
#define FCML_REG_EBX    3
#define FCML_REG_RBX    3
#define FCML_REG_MM3    3
#define FCML_REG_XMM3   3
#define FCML_REG_YMM3   3
#define FCML_REG_ZMM3   3

#define FCML_REG_AH     4
#define FCML_REG_SP     4
#define FCML_REG_SPL    4
#define FCML_REG_ESP    4
#define FCML_REG_RSP    4
#define FCML_REG_MM4    4
#define FCML_REG_XMM4   4
#define FCML_REG_YMM4   4
#define FCML_REG_ZMM4   4

#define FCML_REG_CH     5
#define FCML_REG_BP     5
#define FCML_REG_BPL    5
#define FCML_REG_EBP    5
#define FCML_REG_RBP    5
#define FCML_REG_MM5    5
#define FCML_REG_XMM5   5
#define FCML_REG_YMM5   5
#define FCML_REG_ZMM5   5

#define FCML_REG_DH     6
#define FCML_REG_SI     6
#define FCML_REG_SIL    6
#define FCML_REG_ESI    6
#define FCML_REG_RSI    6
#define FCML_REG_MM6    6
#define FCML_REG_XMM6   6
#define FCML_REG_YMM6   6
#define FCML_REG_ZMM6   6

#define FCML_REG_BH     7
#define FCML_REG_DI     7
#define FCML_REG_DIL    7
#define FCML_REG_EDI    7
#define FCML_REG_RDI    7
#define FCML_REG_MM7    7
#define FCML_REG_XMM7   7
#define FCML_REG_YMM7   7
#define FCML_REG_ZMM7   7

#define FCML_REG_R8L    8
#define FCML_REG_R8W    8
#define FCML_REG_R8D    8
#define FCML_REG_R8     8
#define FCML_REG_XMM8   8
#define FCML_REG_YMM8   8
#define FCML_REG_ZMM8   8

#define FCML_REG_R9L    9
#define FCML_REG_R9W    9
#define FCML_REG_R9D    9
#define FCML_REG_R9     9
#define FCML_REG_XMM9   9
#define FCML_REG_YMM9   9
#define FCML_REG_ZMM9   9

#define FCML_REG_R10L   10
#define FCML_REG_R10W   10
#define FCML_REG_R10D   10
#define FCML_REG_R10    10
#define FCML_REG_XMM10  10
#define FCML_REG_YMM10  10
#define FCML_REG_ZMM10  10

#define FCML_REG_R11L   11
#define FCML_REG_R11W   11
#define FCML_REG_R11D   11
#define FCML_REG_R11    11
#define FCML_REG_XMM11  11
#define FCML_REG_YMM11  11
#define FCML_REG_ZMM11  11

#define FCML_REG_R12L   12
#define FCML_REG_R12W   12
#define FCML_REG_R12D   12
#define FCML_REG_R12    12
#define FCML_REG_XMM12  12
#define FCML_REG_YMM12  12
#define FCML_REG_ZMM12  12

#define FCML_REG_R13L   13
#define FCML_REG_R13W   13
#define FCML_REG_R13D   13
#define FCML_REG_R13    13
#define FCML_REG_XMM13  13
#define FCML_REG_YMM13  13
#define FCML_REG_ZMM13  13

#define FCML_REG_R14L   14
#define FCML_REG_R14W   14
#define FCML_REG_R14D   14
#define FCML_REG_R14    14
#define FCML_REG_XMM14  14
#define FCML_REG_YMM14  14
#define FCML_REG_ZMM14  14

#define FCML_REG_R15L   15
#define FCML_REG_R15W   15
#define FCML_REG_R15D   15
#define FCML_REG_R15    15
#define FCML_REG_XMM15  15
#define FCML_REG_YMM15  15
#define FCML_REG_ZMM15  15

#define FCML_REG_XMM16  16
#define FCML_REG_YMM16  16
#define FCML_REG_ZMM16  16

#define FCML_REG_XMM17  17
#define FCML_REG_YMM17  17
#define FCML_REG_ZMM17  17

#define FCML_REG_XMM18  18
#define FCML_REG_YMM18  18
#define FCML_REG_ZMM18  18

#define FCML_REG_XMM19  19
#define FCML_REG_YMM19  19
#define FCML_REG_ZMM19  19

#define FCML_REG_XMM20  20
#define FCML_REG_YMM20  20
#define FCML_REG_ZMM20  20

#define FCML_REG_XMM21  21
#define FCML_REG_YMM21  21
#define FCML_REG_ZMM21  21

#define FCML_REG_XMM22  22
#define FCML_REG_YMM22  22
#define FCML_REG_ZMM22  22

#define FCML_REG_XMM23  23
#define FCML_REG_YMM23  23
#define FCML_REG_ZMM23  23

#define FCML_REG_XMM24  24
#define FCML_REG_YMM24  24
#define FCML_REG_ZMM24  24

#define FCML_REG_XMM25  25
#define FCML_REG_YMM25  25
#define FCML_REG_ZMM25  25

#define FCML_REG_XMM26  26
#define FCML_REG_YMM26  26
#define FCML_REG_ZMM26  26

#define FCML_REG_XMM27  27
#define FCML_REG_YMM27  27
#define FCML_REG_ZMM27  27

#define FCML_REG_XMM28  28
#define FCML_REG_YMM28  28
#define FCML_REG_ZMM28  28

#define FCML_REG_XMM29  29
#define FCML_REG_YMM29  29
#define FCML_REG_ZMM29  29

#define FCML_REG_XMM30  30
#define FCML_REG_YMM30  30
#define FCML_REG_ZMM30  30

#define FCML_REG_XMM31  31
#define FCML_REG_YMM31  31
#define FCML_REG_ZMM31  31

/* Segment registers. */

#define FCML_REG_ES     0
#define FCML_REG_CS     1
#define FCML_REG_SS     2
#define FCML_REG_DS     3
#define FCML_REG_FS     4
#define FCML_REG_GS     5

/* FPU registers */

#define FCML_REG_ST0    0
#define FCML_REG_ST1    1
#define FCML_REG_ST2    2
#define FCML_REG_ST3    3
#define FCML_REG_ST4    4
#define FCML_REG_ST5    5
#define FCML_REG_ST6    6
#define FCML_REG_ST7    7

/* Control registers. */

#define FCML_REG_CR0    0
#define FCML_REG_CR2    2
#define FCML_REG_CR3    3
#define FCML_REG_CR4    4
#define FCML_REG_CR8    8

/* Debug register. */

#define FCML_REG_DR0    0
#define FCML_REG_DR1    1
#define FCML_REG_DR2    2
#define FCML_REG_DR3    3
#define FCML_REG_DR4    4
#define FCML_REG_DR5    5
#define FCML_REG_DR6    6
#define FCML_REG_DR7    7

/* Opmask registers. */

#define FCML_REG_K0     0
#define FCML_REG_K1     1
#define FCML_REG_K2     2
#define FCML_REG_K3     3
#define FCML_REG_K4     4
#define FCML_REG_K5     5
#define FCML_REG_K6     6
#define FCML_REG_K7     7

/** @} */

/**
 * @defgroup DATA_SIZE_GROUP Constants used to describe data size.
 * @{instrunction->hints
 */

#define FCML_DS_UNDEF   0
#define FCML_DS_8       8
#define FCML_DS_16      16
#define FCML_DS_32      32
#define FCML_DS_64      64
#define FCML_DS_128     128
#define FCML_DS_256     256
#define FCML_DS_512     512

/** @} */

/* Size operators. */

#define FCML_OS_UNDEFINED       0
#define FCML_OS_BYTE            8
#define FCML_OS_WORD            16
#define FCML_OS_DWORD           32
#define FCML_OS_FWORD           48
#define FCML_OS_QWORD           64
#define FCML_OS_MWORD           64
#define FCML_OS_TBYTE           80
#define FCML_OS_OWORD           128
#define FCML_OS_XWORD           128
#define FCML_OS_YWORD           256
#define FCML_OS_ZWORD           512

/* SIMD tuple types. */

/* Instructions affected by embedded broadcast */
#define FCML_TT_NONE            0
#define FCML_TT_FV              1
#define FCML_TT_HV              2

/* Instructions not affected by embedded broadcast */
#define FCML_TT_FVM             3 /* Full Mem */
#define FCML_TT_T1S             4
#define FCML_TT_T1F             5
#define FCML_TT_T2              6
#define FCML_TT_T4              7
#define FCML_TT_T8              8
#define FCML_TT_HVM             9
#define FCML_TT_QVM             10
#define FCML_TT_OVM             11
#define FCML_TT_M128            12
#define FCML_TT_DUP             13
#define FCML_TT_T1x4            14 /* Tuple1_4X */

/* Embedded rounding mode. */

#define FCML_ER_RN_SAE          0
#define FCML_ER_RD_SAE          1
#define FCML_ER_RU_SAE          2
#define FCML_ER_RZ_SAE          3

/**
 * Register type.
 * Every register is represented as an integer value and it's
 * register type. This enumeration provides all supported register types.
 */
typedef enum fcml_en_register {
    /** Undefined register type. */
    FCML_REG_UNDEFINED = 0,
    /** General purpose register. */
    FCML_REG_GPR,
    /** SIMD (SSE, MMX) register. */
    FCML_REG_SIMD,
    /** FPU register. */
    FCML_REG_FPU,
    /** Segment register */
    FCML_REG_SEG,
    /** Control register. */
    FCML_REG_CR,
    /** Debug register */
    FCML_REG_DR,
    /** Instruction pointer register. Used for relative RIP addressing. */
    FCML_REG_IP,
    /** Operand mask register. */
    FCML_REG_OPMASK
} fcml_en_register;

/**
 * Structure describes x86_64 register.
 */
typedef struct fcml_st_register {
    /** Register type. */
    fcml_en_register type;
    /** Register size in bits. */
    fcml_usize size;
    /** Register itself as a positive integer. @see REGISTERS_GROUP */
    fcml_uint8_t reg;
    /** In case of SPL,BPL,SIL,DIL GPR registers has to be set to true. */
    fcml_bool x64_exp;
} fcml_st_register;

/*********************************
 * Conditions.
 *********************************/

/** Number of supported condition types. */
#define FCML_NUMBER_OF_CONDITIONS  8

/**
 * Condition type.
 * Every conditional instruction has an appropriate condition type set.
 * Following enumeration defines all supported types.
 */
typedef enum fcml_en_condition_type {
    /** 0 Overflow*/
    FCML_CONDITION_O = 0,
    /** 1 Below*/
    FCML_CONDITION_B,
    /** 2 Equal*/
    FCML_CONDITION_E,
    /** 3 Below or equal*/
    FCML_CONDITION_BE,
    /** 4 Sign*/
    FCML_CONDITION_S,
    /** 5 Parity*/
    FCML_CONDITION_P,
    /** 6 Less than*/
    FCML_CONDITION_L,
    /** 7 Less than or equal to*/
    FCML_CONDITION_LE
} fcml_en_condition_type;

/**
 * Defines instruction's condition.
 */
typedef struct fcml_st_condition {
    /* Condition type.*/
    fcml_en_condition_type condition_type;
    /* True if condition should be negated.*/
    fcml_bool is_negation;
} fcml_st_condition;

/*********************************
 * Size attributes flags.
 *********************************/

/**
 * @defgroup SUPPORTED_SIZE_GROUP These values can be used in order to
 * prepare a mask of supported sizes. Used mainly by optimizers where
 * instructions can be assembled using different attribute sizes.
 * @{
 */

/* Addressing mode is not set, so the caller does not care about it - any
 * addressing mode is allowed. */
#define    FCML_EN_ASF_ANY    0x00
#define    FCML_EN_ASF_16     0x01
#define    FCML_EN_ASF_32     0x02
#define    FCML_EN_ASF_64     0x04
/* All addressing modes are allowed, but in this particular case it's explicitly stated.
 * Effectively it's the same option as FCML_EN_ASF_ANY. */
#define    FCML_EN_ASF_ALL    FCML_EN_ASF_16 | FCML_EN_ASF_32 | FCML_EN_ASF_64

/** @} */

/**
 * Nullable wrapper for mask of size flags.
 */
typedef struct fcml_st_nullable_size_flags {
    /** True if mask is set. */
    fcml_bool is_set;
    /** Mask of supported size values. */
    fcml_flags flags;
} fcml_st_nullable_size_flags;

/*********************************
 * Operands.
 *********************************/

/**
 * Operand access mode.
 */
typedef enum fcml_en_access_mode {
    /** Undefined mode. */
    FCML_AM_ACCESS_MODE_UNDEFINED = 0,
    /** Operand is read by instruction. */
    FCML_AM_READ = 0x01,
    /** Operand is set by instruction */
    FCML_AM_WRITE = 0x02,
    /** Operand is read but can be also set. */
    FCML_AM_READ_WRITE = FCML_AM_READ | FCML_AM_WRITE
} fcml_en_access_mode;

/**
 * Representation of far pointer operand.
 */
typedef struct fcml_st_far_pointer {
    /** 16-bit Code segment. */
    fcml_uint16_t segment;
    /** Size of the offset. */
    fcml_usize offset_size;
    /** 16-bit offset. */
    fcml_int16_t offset16;
    /** 32-bit offset. */
    fcml_int32_t offset32;
} fcml_st_far_pointer;

/********************************************/
/**  Memory addressing using ModR/M field  **/
/********************************************/

/**
 * Addressing form.
 * Distinguish between two types of addressing forms: effective addressing
 * and explicit absolute offset.
 */
typedef enum fcml_en_address_form {
    /** Default value set if memory addressing hasn't been configured. */
    FCML_AF_UNDEFINED,
    /** Absolute offset (address). */
    FCML_AF_OFFSET,
    /** Effective address combined from address components like base register,
     * index registers, factor, displacement etc... */
    FCML_AF_COMBINED
} fcml_en_effective_address_form;

/**
 * Absolute offset.
 */
typedef struct fcml_st_offset {
    /** Offset size 16,32 or 64 bits. */
    fcml_usize size;
    /** True if offset should be treated as signed value. */
    fcml_bool is_signed;
    /** Place for 16-bit absolute offset. */
    fcml_int16_t off16;
    /** Place for 32-bit absolute offset. */
    fcml_int32_t off32;
    /** Place for 64-bit absolute offset. */
    fcml_int64_t off64;
} fcml_st_offset;

/**
 * Effective address.
 */
typedef struct fcml_st_effective_address {
    /** GPR base register. @see fcml_st_register. */
    fcml_st_register base;
    /** GPR index register. @see fcml_st_register. */
    fcml_st_register index;
    /** Scale factor 1,2,4 or 8. */
    fcml_uint8_t scale_factor;
    /** Displacement value. @see fcml_st_integer. */
    fcml_st_integer displacement;
} fcml_st_effective_address;

/**
 * Describes segment register.
 */
typedef struct fcml_st_segment_selector {
    /** Used segment register. @see fcml_st_register*/
    fcml_st_register segment_selector;
    /** Set to true if given segment register is a default one in given
     * context. This value is set by disassembler.
     */
    fcml_bool is_default_reg;
} fcml_st_segment_selector;

/**
 * Generic memory addressing operator.
 */
typedef struct fcml_st_address {
    /** Size of data accessed in memory.*/
    fcml_usize size_operator;
    /** Memory addressing format: absolute offset/effective address.
     * @see fcml_en_effective_address_form
     */
    fcml_en_effective_address_form address_form;
    /** Segment register.*/
    fcml_st_segment_selector segment_selector;
    /** Memory address for FCML_AF_COMBINED form.*/
    fcml_st_effective_address effective_address;
    /** Memory address for FCML_AF_OFFSET form.*/
    fcml_st_offset offset;
} fcml_st_address;

/**
 * Rounding mode.
 */
typedef enum fcml_en_embeeded_rounding_control {
    FCML_ERC_RNE, FCML_ERC_RD, FCML_ERC_RU, FCML_ERC_RZ
} fcml_en_embeeded_rounding_control;

/**
 * Container for operand decorators.
 * @since 1.2.0
 */
typedef struct fcml_st_operand_decorators {
    /** Broadcasting: 2, 4, 8, 16, 32, 64. */
    fcml_nuint8_t bcast;
    /** Zeroing masking. */
    fcml_bool z;
    /** The 64-bit k registers are: k0 through k7. */
    fcml_st_register operand_mask_reg;
    /** Embedded rounding control. */
    fcml_nuint8_t er;
    /** Indicates support for SAE (Suppress All Exceptions). */
    fcml_bool sae;
} fcml_st_operand_decorators;

/**
 * Supported operand types.
 */
typedef enum fcml_en_operand_type {
    /** Operand not used. */
    FCML_OT_NONE,
    /** Immediate integer value. */
    FCML_OT_IMMEDIATE,
    /** Direct far pointer. */
    FCML_OT_FAR_POINTER,
    /** Memory address. */
    FCML_OT_ADDRESS,
    /** Processor register. */
    FCML_OT_REGISTER,
    /**
     * Not an operand in a strict sense,
     * only a container for attributes.
     */
    FCML_OT_VIRTUAL
} fcml_en_operand_type;

/**
 * Operand hints.
 * Hints dedicated for instruction operands.
 */
typedef enum fcml_en_operand_hints {
    /**
     * Undefined.
     */
    FCML_OP_HINT_UNDEFIEND = 0x0000,
    /**
     * SIMD operand. All operands which uses SIMD registers (mmx, xmm, ymm)
     * have this flag set. It is for instance used by Intel syntax renderer
     * for data size operators (mmword ptr, xmmword ptr, ymmword ptr).
     */
    FCML_OP_HINT_MULTIMEDIA_INSTRUCTION = 0x0001,
    /**
     * Relative address. Flags set for all branches which use jumps
     * calculated by displacement relative to the IP of the next instructions.
     */
    FCML_OP_HINT_DISPLACEMENT_RELATIVE_ADDRESS = 0x0002,
    /**
     * Pseudo opcode. Hint set for last operand (Intel syntax) which contains
     * comparison predicate of the following instructions: CMPSD, VCMPSD, CMPSS,
     *  VCMPSS, VPCOMB, VPCOMW, VPCOMD, VPCOMQ, VPCOMUB, VPCOMUW,
     *  VPCOMUD, VPCOMUQ.
     */
    FCML_OP_HINT_PSEUDO_OPCODE = 0x0004,
    /**
     * Offset should be encoded as absolute address.
     */
    FCML_OP_HINT_ABSOLUTE_ADDRESSING = 0x0008,
    /**
     * Offset should be encoded as relative address.
     */
    FCML_OP_HINT_RELATIVE_ADDRESSING = 0x0010,
    /**
     *  Encode ModR/M with optional SIB byte if possible.
     **/
    FCML_OP_HINT_SIB_ENCODING = 0x0020
} fcml_en_operand_hints;

/** Instruction operand.
 * Structure represents one instruction operand.
 */
typedef struct fcml_st_operand {
    /** Operand type */
    fcml_en_operand_type type;
    /** Optional operand level hints. */
    fcml_hints hints;
    /** Immediate value operand. */
    fcml_st_integer immediate;
    /** Far pointer operand. */
    fcml_st_far_pointer far_pointer;
    /** Effective address or absolute offset. */
    fcml_st_address address;
    /** Register operand. */
    fcml_st_register reg;
    /** Operand decorators. */
    fcml_st_operand_decorators decorators;
} fcml_st_operand;

/*********************************
 * Instruction definition.
 *********************************/

/**
 * Instruction level hints.
 * Set of the hints that can be only defined on the
 * level of the whole instruction. They can not be used
 * with operands.
 */
typedef enum fcml_en_instruction_hints {
    /** No hints defined. */
    FCML_HINT_NO_HINTS,
    /** Hints instruction to use FAR pointer to address the memory. */
    FCML_HINT_FAR_POINTER = 0x0001,
    /** Hints instruction to use NEAR pointer to address the memory. */
    FCML_HINT_NEAR_POINTER = 0x0002,
    /** This hint is used only by assembler in order to force it to generate
     * three byte VEX/XOP prefix even if prefix fields fits into two bytes. */
    FCML_HINT_LONG_FORM_POINTER = 0x0004,
    /** Hints instruction to use INDIRECT pointer to address the memory. */
    FCML_HINT_INDIRECT_POINTER = 0x0008,
    /** Hints instruction to use DIRECT memory addressing. */
    FCML_HINT_DIRECT_POINTER = 0x0010
} fcml_en_instruction_hints;

/**
 * Generic instruction model.
 * Generic instruction model (GIM) is a common structure used to describe
 * instruction in a common way used by FCML assembler and disassembler.
 */
typedef struct fcml_st_instruction {
    /** Describes explicit instruction prefixes. @ref PREFIX_GROUP "List
     * of explicit prefixes." */
    fcml_prefixes prefixes;
    /** Holds instruction level hints. */
    fcml_hints hints;
    /** Dialect-dependent instruction mnemonic.
     * @see fcml_en_instruction_hints */
    fcml_char *mnemonic;
    /** True for conditional instructions. */
    fcml_bool is_conditional;
    /** Describes condition used by assembled/disassembled
     * conditional instruction. */
    fcml_st_condition condition;
    /** Fixed size array of instruction operands. */
    fcml_st_operand operands[FCML_OPERANDS_COUNT];
    /** Number of operands defined for instruction. */
    fcml_int operands_count;
} fcml_st_instruction;

/*********************************
 * Instruction definition.
 *********************************/

/**
 * An encoded instruction.
 */
typedef struct fcml_st_instruction_code {
    /** Pointer to the instruction code. */
    fcml_uint8_t *code;
    /** Instruction code length. */
    fcml_usize code_length;
} fcml_st_instruction_code;

/****************************
 * Instruction entry point.
 ****************************/

/**
 * Describes address of an instruction code.
 */
typedef struct fcml_st_entry_point {
    /** Processor operating mode 16/32/64-bit.*/
    fcml_en_operating_mode op_mode;
    /** Default address size attribute (See 'D' flag of segment descriptor.)*/
    fcml_usize address_size_attribute;
    /** Default operand size attribute (See 'D' flag of segment descriptor.)*/
    fcml_usize operand_size_attribute;
    /** Instruction pointer EIP/RIP. Take into account that even in 16 bit
     *  mode EIP register is used.*/
    fcml_ip ip;
} fcml_st_entry_point;

#endif /* FCML_INT_COMMON_H_ */
