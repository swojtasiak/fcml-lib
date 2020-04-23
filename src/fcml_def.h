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

#ifndef FCML_DEF_H_
#define FCML_DEF_H_

#include <fcml_instructions.h>
#include <fcml_types.h>
#include <fcml_common.h>

#include "fcml_ceh.h"

/* Constants used to encode operand size on one byte. Used only in
 * instruction descriptions.
 */

/* Take into account that every size is given in a number of bytes. */
#define FCML_EOS_UNDEFINED    0
#define FCML_EOS_512B         FCML_EOS_UNDEFINED
#define FCML_EOS_BYTE         1
#define FCML_EOS_WORD         2
#define FCML_EOS_DWORD        4
#define FCML_EOS_FWORD        6
#define FCML_EOS_QWORD        8
#define FCML_EOS_MWORD        8
#define FCML_EOS_TBYTE        10
#define FCML_EOS_OWORD        16
#define FCML_EOS_XWORD        16
#define FCML_EOS_YWORD        32
#define FCML_EOS_ZWORD        64

/* Dynamic encoded operand sizes calculated at runtime. */

#define FCML_EOS_DYNAMIC_BASE   0x70

/* Memory location size (size operator) is optional and doesn't have to
   be set at all. */
#define FCML_EOS_OPT            0x80

/* Operand size calculated by Effective
 * Operand Size Attribute and Effective Address Size Attribute.
 */
#define FCML_EOS_EOSA           0x7F
#define FCML_EOS_EASA           0x7E

/* Operand size calculated on EVEX.L'L/VEX.L/XOP/L fields. */
#define FCML_EOS_L              0x7D

/* Operand sizes that cannot be simply written as number of bytes.*/
#define FCML_EOS_14_28          0x7C
#define FCML_EOS_94_108         0x7B
#define FCML_EOS_32_64          0x7A

/* Far pointer indirect.*/
#define FCML_EOS_FPI            0x79

/* Far pointer.*/
#define FCML_EOS_FP             0x78

/* True if encoded operand size is a dynamic one.*/
#define FCML_IS_EOS_DYNAMIC(x)  (((x) & 0x40) != 0)
#define FCML_IS_EOS_OPT(x)      (((x) & 0x80) != 0)
#define FCML_GET_OS(x)          ((x) & ~FCML_EOS_OPT)

/* Instruction and addressing mode types. */

typedef enum fcml_en_def_instruction_type {
    /* Intel IA.*/
    FCML_EN_IT_IA
} fcml_en_def_instruction_type;

/****************/
/* Instructions */
/****************/

/* Multi instructions. */
#define FCML_MI_AMD3DNOW        0x0001

/*******************/
/* Addressing mode */
/*******************/

/* Wild card for mnemonic used by default.*/
#define FCML_AM_ALL             0

/*********************************************/
/* Instruction groups.                       */
/* Bit fields are not compatible with CPUID. */
/*********************************************/

#define FCML_IS_MULTI_INSTRUCTION(x)        (0x8000 & (x))
#define FCML_MULTI_INSTRUCTION(x)           (0x8000 | (x))

/**
 * Lower 40 bits are used to specify operand addressing mode.
 * Upper 24 bits are used to specify operand decorators.
 */
typedef fcml_uint64_t fcml_operand_desc;
typedef fcml_uint32_t fcml_operand_decorators;

#define FCML_ADDR_MODE(x)    ((x) & 0x000000FFFFFFFFFFLL)
#define FCML_DECORATORS(x)   \
    (fcml_operand_decorators)(((x) & 0xFFFFFF0000000000LL) >> 40)

/* Operand decorators encoders. */

#define FCML_DECOR_BCAST      0x010000000000LL
#define FCML_DECOR_Z          0x020000000000LL
#define FCML_DECOR_K1         0x040000000000LL
#define FCML_DECOR_ER         0x080000000000LL
/* SAE is supported by instruction operand. */
#define FCML_DECOR_SAE        0x100000000000LL
/* SAE is required by addressing mode. */
#define FCML_DECOR_SAE_REQ    (0x200000000000LL | FCML_DECOR_SAE)
/* Predicate operand is mandatory and cannot be omited. */
#define FCML_DECOR_K1_REQ     (0x400000000000LL | FCML_DECOR_K1)


/* Operand decorators decoders. Use only on 'fcml_operand_decorators'. */

#define FCML_IS_DECOR_BCAST(x)                ((x) & 0x00000001)
#define FCML_IS_DECOR_Z(x)                    ((x) & 0x00000002)
#define FCML_IS_DECOR_OPMASK_REG(x)           ((x) & 0x00000004)
#define FCML_IS_DECOR_OPMASK_REG_REQ(x)       (((x) & 0x00000044) == 0x00000044)
#define FCML_IS_DECOR_ER(x)                   ((x) & 0x00000008)
#define FCML_IS_DECOR_SAE(x)                  ((x) & 0x00000010)
#define FCML_IS_DECOR_SAE_REQ(x)              (((x) & 0x00000030) == 0x00000030)

/* Instruction details. */

#define FCML_NO_DETAILS                 0x0
#define FCML_SIMD_ELEMENT_SIZE(x)       ((x) << 4)

#define FCML_GET_SIMD_TUPLETYPE(x)      ((x) & 0x0000000F)
/* Compressed element size * 8. */
#define FCML_GET_SIMD_ELEMENT_SIZE(x)  (((x) & 0x000000F0) >> 1)

#define FCML_SIMD_ES_64                 FCML_SIMD_ELEMENT_SIZE(FCML_EOS_QWORD)
#define FCML_SIMD_ES_32                 FCML_SIMD_ELEMENT_SIZE(FCML_EOS_DWORD)
#define FCML_SIMD_ES_16                 FCML_SIMD_ELEMENT_SIZE(FCML_EOS_WORD)
#define FCML_SIMD_ES_8                  FCML_SIMD_ELEMENT_SIZE(FCML_EOS_BYTE)

/* Structures used to describe instructions with they all allowed addressing
 * modes.
 */
typedef struct fcml_st_def_addr_mode_desc {
    /* Addressing mode type. */
    fcml_uint64_t instruction_group;
    /* Additional details dependent on the instruction group. */
    fcml_uint32_t details;
    /* Flags describing allowed prefixes.*/
    fcml_uint32_t allowed_prefixes;
    /* Some flags that contains various information about opcode.*/
    fcml_uint32_t opcode_flags;
    /* Opcode bytes.*/
    fcml_uint8_t opcode[3];
    /* Addressing of instruction operands.*/
    fcml_operand_desc operands[FCML_OPERANDS_COUNT];
    /* Addressing mode.*/
    fcml_uint16_t addr_mode;
    /* Instruction hints. */
    fcml_hints instruction_hints;
} fcml_st_def_addr_mode_desc;

/* Instruction code definition for multi-instructions. Currently only the
 * instructions with suffixes use this mechanism.
 */
typedef struct fcml_st_def_instruction_code_desc {
    /* Instruction code.*/
    fcml_uint16_t instruction;
    /* Suffix.*/
    fcml_uint8_t suffix;
} fcml_st_def_instruction_code_desc;

/* Describes one addressing mode of instruction. */
typedef struct fcml_st_def_instruction_desc {
    /* Instruction code.*/
    fcml_en_instruction instruction;
    /* Optional array of multi-instruction codes.*/
    fcml_st_def_instruction_code_desc *multi_instruction;
    /* Mnemonic.*/
    fcml_string mnemonic;
    /* Type of the instruction.*/
    fcml_en_def_instruction_type instruction_type;
    /* Number of opcodes descriptions.*/
    fcml_uint8_t opcode_desc_count;
    /* Opcodes descriptions.*/
    fcml_st_def_addr_mode_desc *addr_modes;
} fcml_st_def_instruction_desc;

/* Operands encoding */

#define FCML_IA_INSTRUCTION(i,x,y)          {i, NULL, x, FCML_EN_IT_IA, \
    (sizeof(y) / sizeof(struct fcml_st_def_addr_mode_desc)), y}

#define FCML_IA_MULTI_INSTRUCTION(i,x,y)    {(fcml_en_instruction) \
    FCML_MULTI_INSTRUCTION(i), x, FCML_EMPTY_MNEMONIC, FCML_EN_IT_IA, \
    (sizeof(y) / sizeof(struct fcml_st_def_addr_mode_desc)), y}

#define FCML_REG_FIELD_NUMBER_OF_REGISTERS                8
#define FCML_REG_FIELD_NUMBER_OF_CONDITIONS               16

/*********************************
 * Prefix fields.
 *********************************/

#define FCML_DEF_PREFIX_LOCK_ALLOWED(x)              FCML_TP_GET_BIT(x,0)
#define FCML_DEF_PREFIX_REPNE_XACQUIRE_ALLOWED(x)    FCML_TP_GET_BIT(x,1)
#define FCML_DEF_PREFIX_REP_XRELEASE_ALLOWED(x)      FCML_TP_GET_BIT(x,2)
#define FCML_DEF_PREFIX_W_1(x)                       FCML_TP_GET_BIT(x,3)
#define FCML_DEF_PREFIX_W_0(x)                       FCML_TP_GET_BIT(x,4)
#define FCML_DEF_PREFIX_L_1(x)                       FCML_TP_GET_BIT(x,5)
#define FCML_DEF_PREFIX_L_0(x)                       FCML_TP_GET_BIT(x,6)
#define FCML_DEF_PREFIX_VEX_REQ(x)                   FCML_TP_GET_BIT(x,7)
#define FCML_DEF_PREFIX_L_IGNORE_OS(x)               FCML_TP_GET_BIT(x,8)
#define FCML_DEF_PREFIX_XOP_REQ(x)                   FCML_TP_GET_BIT(x,9)
#define FCML_DEF_PREFIX_HLE_ENABLED(x)               FCML_TP_GET_BIT(x,10)
#define FCML_DEF_PREFIX_MANDATORY_66(x)              FCML_TP_GET_BIT(x,11)
#define FCML_DEF_PREFIX_MANDATORY_F2(x)              FCML_TP_GET_BIT(x,12)
#define FCML_DEF_PREFIX_MANDATORY_F3(x)              FCML_TP_GET_BIT(x,13)
#define FCML_DEF_PREFIX_SUFFIX(x)                    FCML_TP_GET_BIT(x,14)
#define FCML_DEF_PREFIX_EVEX_REQ(x)                  FCML_TP_GET_BIT(x,15)
#define FCML_DEF_PREFIX_L_prim_1(x)                  FCML_TP_GET_BIT(x,16)
#define FCML_DEF_PREFIX_L_prim_0(x)                  FCML_TP_GET_BIT(x,17)

#define FCML_DEF_PREFIX_IS_AVX_REQ(x)   (FCML_DEF_PREFIX_VEX_REQ(x) || \
    FCML_DEF_PREFIX_EVEX_REQ(x) || FCML_DEF_PREFIX_XOP_REQ(x))

/*********************************
 * Opcode fields extractors.
 *********************************/

#define FCML_DEF_OPCODE_FLAGS_OPCODE_FIELD_REG(x)           ((x) & 0x00000001)
#define FCML_DEF_OPCODE_FLAGS_OPCODE_FIELD_W(x)             ((x) & 0x00000002)
#define FCML_DEF_OPCODE_FLAGS_OPCODE_FIELD_S(x)             ((x) & 0x00000004)
/* tttn field for conditional instructions, specifies a condition
 * asserted or negated. The field is located in opcode byte. */
#define FCML_DEF_OPCODE_FLAGS_OPCODE_FIELD_TTTN(x)          ((x) & 0x00000040)
#define FCML_DEF_OPCODE_FLAGS_64BITS_EOSA_BY_DEFAULT(x)     ((x) & 0x00000080)
#define FCML_DEF_OPCODE_FLAGS_POS(x)                  (((x) & 0x00000700) >> 8)
#define FCML_DEF_OPCODE_FLAGS_OPCODE_EXT(x)           (((x) & 0x00007800) >> 11)
#define FCML_DEF_OPCODE_FLAGS_OPCODE_IS_MODRM(x)      FCML_TP_GET_BIT(x,15)
/* Reg/Opcode field is used as an opcode extension. */
#define FCML_DEF_OPCODE_FLAGS_OPCODE_IS_EXT(x)        FCML_TP_GET_BIT(x,16)
#define FCML_DEF_OPCODE_FLAGS_OPCODE_NUM(x)           (((x) & 0x000C0000) >> 18)
#define FCML_DEF_OPCODE_FLAGS_PRIMARY_OPCODE(x)       (((x) & 0x00300000) >> 20)
#define FCML_DEF_OPCODE_FLAGS_64_BIT_MODE_SUPPORTED(x)      ((x) & 0x00800000)
#define FCML_DEF_OPCODE_FLAGS_16_32_BIT_MODE_SUPPORTED(x)   ((x) & 0x00400000)
#define FCML_DEF_OPCODE_FLAGS_EOSA_16(x)                    ((x) & 0x01000000)
#define FCML_DEF_OPCODE_FLAGS_EOSA_32(x)                    ((x) & 0x02000000)
#define FCML_DEF_OPCODE_FLAGS_EOSA_64(x)                    ((x) & 0x04000000)
#define FCML_DEF_OPCODE_FLAGS_IS_EOSA_RESTRICTION(x)        ((x) & 0x07000000)
#define FCML_DEF_OPCODE_FLAGS_EASA_16(x)                    ((x) & 0x08000000)
#define FCML_DEF_OPCODE_FLAGS_EASA_32(x)                    ((x) & 0x10000000)
#define FCML_DEF_OPCODE_FLAGS_EASA_64(x)                    ((x) & 0x20000000)
#define FCML_DEF_OPCODE_FLAGS_IS_EASA_RESTRICTION(x)        ((x) & 0x38000000)
#define FCML_DEF_OPCODE_FLAGS_FORCE_64BITS_EOSA(x)          ((x) & 0x40000000)

/*********************************
 * Addressing modes.
 *********************************/

/* Operand access mode (source/destination).*/
#define FCML_OA_R           0x80000000
#define FCML_OA_W           0x40000000
#define FCML_OA_RW          (FCML_OA_R | FCML_OA_W)
#define FCML_NA             0x00000000

/* Immediate data.*/
#define FCML_OP_IMM_BASE 0x01000000

#define FCML_OP_IMM(encoded_size, encoded_ex_size)   (FCML_OP_IMM_BASE | \
        (encoded_size) << 8 | (encoded_ex_size))

#define FCML_OP_IMM_64_ALLOWED  1 << 16
#define FCML_OP_IMM_64   (FCML_OP_IMM(FCML_EOS_EOSA, FCML_EOS_UNDEFINED) | \
        FCML_OP_IMM_64_ALLOWED)

/* Register explicitly set.*/
#define FCML_OP_EXPLICIT_REG_BASE 0x02000000

#define FCML_OP_EXPLICIT_REG(reg_type, reg_num, encoded_reg_size)    \
    (FCML_OP_EXPLICIT_REG_BASE | (reg_type) << 12 | (reg_num) << 8 | \
            encoded_reg_size )

/* Register field in opcode byte.*/
#define FCML_OP_OPCODE_REG_BASE 0x03000000

#define FCML_OP_OPCODE_REG(reg_type, encoded_reg_size) (\
        FCML_OP_OPCODE_REG_BASE | ( reg_type ) << 8 | encoded_reg_size )

/* Relative addressing.*/
#define FCML_OP_IMMEDIATE_DIS_RELATIVE_BASE                0x04000000
#define FCML_OP_IMMEDIATE_DIS_RELATIVE(encoded_size)       \
    (FCML_OP_IMMEDIATE_DIS_RELATIVE_BASE | encoded_size )

/* Far pointers. */
#define FCML_OP_FAR_POINTER   0x05000000

/* Addressing by explicit GPR register. (Used by CMPS for instance.)*/
#define FCML_OP_EXPLICIT_GPS_REG_ADDRESSING_BASE     0x06000000
#define FCML_OP_EXPLICIT_GPS_REG_ADDRESSING(reg_num, encoded_operand_size, \
        encoded_segment_register)  (FCML_OP_EXPLICIT_GPS_REG_ADDRESSING_BASE | \
                (reg_num) << 16 | (encoded_operand_size) << 8 | \
                (encoded_segment_register))

/* It allows defining explicit IMM8 operand type. See INT instruction.*/
#define FCML_OP_EXPLICIT_IB_BASE       0x07000000
#define FCML_OP_EXPLICIT_IB(value)     (FCML_OP_EXPLICIT_IB_BASE | (value))

/* Segment relative addressing.*/
#define FCML_OP_SEGMENT_RELATIVE_OFFSET_BASE    0x08000000
#define FCML_OP_SEGMENT_RELATIVE_OFFSET(operand_size, \
        encoded_segment_register)    (FCML_OP_SEGMENT_RELATIVE_OFFSET_BASE | \
                (operand_size) << 8 | (encoded_segment_register))


/********************************/
/*      ModR/M encoding.        */
/********************************/

/* Allows to encode all common ModR/M based addressing modes using
 * only one macro.
 */

/* Only register addressing is allowed.*/
#define FCML_RMF_R        0x01
/* Only memory addressing is allowed.*/
#define FCML_RMF_M        0x02
/* Indirect addressing.*/
#define FCML_RMF_I        0x04
/* Shortcut, operand acts as source and destination.*/
#define FCML_RMF_RM       (FCML_RMF_R | FCML_RMF_M)

#define FCML_OP_RM_BASE                                0x09000000
#define FCML_OP_RM(reg_type, encoded_register_operand_size, \
        encoded_memory_operand_size, flags)        (FCML_OP_RM_BASE | \
                ((encoded_memory_operand_size) << 16) | \
                ((encoded_register_operand_size) << 8) | ((reg_type) << 4) | \
                (flags))

#define FCML_OP_RM_W(reg_type, encoded_register_operand_size, \
        encoded_memory_operand_size, flags)     (FCML_OP_RM(reg_type, \
                encoded_register_operand_size, encoded_memory_operand_size, \
                flags) | FCML_OA_W)

#define FCML_OP_R_BASE    0x0A000000
#define FCML_OP_R(reg_type, encoded_register_operand_size)  (FCML_OP_R_BASE | \
        ((encoded_register_operand_size) << 4) | (reg_type))

/******************************/
/* XOP/VEX specific encoding. */
/******************************/

#define FCML_OP_VEX_VVVV_REG_BASE           0x0B000000
#define FCML_OP_VEX_VVVV_REG(reg_type, encoded_register_size)    \
    (FCML_OP_VEX_VVVV_REG_BASE | ((encoded_register_size) << 4) | (reg_type))

/*****************************/
/* IS4/IS5 operand decoding. */
/*****************************/

#define FCML_ISF_IS4        0x01
#define FCML_ISF_IS5        0x02
#define FCML_ISF_IS5_SRC    0x10
#define FCML_ISF_IS5_M2Z    0x20

#define FCML_OP_OPERAND_ISx_BASE    0x0C000000
#define FCML_OP_OPERAND_IS4         (FCML_OP_OPERAND_ISx_BASE | FCML_ISF_IS4)
#define FCML_OP_OPERAND_IS5(flags)  (FCML_OP_OPERAND_ISx_BASE | FCML_ISF_IS5 | \
        flags)

/**************************/
/* VSIB operand decoding. */
/**************************/

/* Vector index register. */
#define FCML_VSIB_XMM    0x01
#define FCML_VSIB_YMM    0x02
#define FCML_VSIB_ZMM    0x03
/* Size based on vector length. */
#define FCML_VSIB_UNDEF  0x04

#define FCML_OP_VSIB_BASE            0x0D000000
#define FCML_OP_VSIB(vector_index_register, encoded_index_value_size)        \
    (FCML_OP_VSIB_BASE | (vector_index_register) << 8 | \
            (encoded_index_value_size))

/**
 * Converts VSIB register type to corresponding data size.
 */
fcml_usize fcml_fn_def_vsib_reg_to_ds(fcml_uint8_t vsib_reg);

/**************/
/* Pseudo-Op. */
/**************/

#define FCML_OP_PSEUDO_OP_BASE            0x0E000000
#define FCML_OP_PSEUDO_OP(mask)           (FCML_OP_PSEUDO_OP_BASE | (mask))

/*********************/
/* Virtual operator. */
/*********************/

#define FCML_OP_VIRTUAL_BASE              0x0F000000
#define FCML_OP_VIRTUAL(decorator)        (FCML_OP_VIRTUAL_BASE | (decorator))

#define FCML_OP_VIRTUAL_ER                FCML_OP_VIRTUAL(FCML_DECOR_ER)
#define FCML_OP_VIRTUAL_SAE               FCML_OP_VIRTUAL(FCML_DECOR_SAE)
/* This operand encoding is needed to encode SAE in cases where virtual operand
 * is not the last one. In such a case when SAE is not used the operands
 * ordering may be disturbed, because there will be a gap between operand
 * encoders. To avoid such hard to handle situations we need to prepare two
 * addressing mode descriptions one supporting SAO virtual operand and one
 * without it, but we have to mark the SAE virtual operand as a mandatory
 * one in order to use such a address mode only if SAE is defined. It's
 * needed because by default SAE is optional as may be omitted when the
 * virtual operand is the last one.
 */
#define FCML_OP_VIRTUAL_SAE_REQ           FCML_OP_VIRTUAL(FCML_DECOR_SAE_REQ)

/*******************************/
/* Segment registers encoding. */
/*******************************/

#define FCML_SEG_ALLOW_OVERRIDE                      0x80
#define FCML_SEG_DENY_OVERRIDE                       0x00
#define FCML_SEG_GET_REG(encoded_reg)                (encoded_reg & 0x7F)
#define FCML_SEG_ENCODE_REGISTER(reg_num, override)  (reg_num | override)

#define FCML_SEG_DECODE_IS_OVERRIDE_ALLOWED(encoded) \
    (FCML_SEG_ALLOW_OVERRIDE & encoded)

#define FCML_SEG_DECODE_REGISTER(encoded)            \
    (encoded & ~FCML_SEG_ALLOW_OVERRIDE)

/* Useful macros related to addressing modes.*/
#define FCMP_DEF_IS_ADDR_MODE(x, y)            ((x) == ((y) >> 24))

/* Addressing mode checking macro for not shifted addressing mode codes. */
#define FCML_IS_ADDR_MODE(mode, code)          (((mode) & (code)) == (code))

/* Shorthands*/

#define FCML_OP_MODRM_RM_8 \
    FCML_OP_RM(FCML_REG_GPR, FCML_EOS_BYTE, FCML_EOS_BYTE, FCML_RMF_RM )

#define FCML_OP_MODRM_RM_8_W            (FCML_OP_MODRM_RM_8 | FCML_OA_W)
#define FCML_OP_MODRM_RM_8_RW           (FCML_OP_MODRM_RM_8 | FCML_OA_RW)

#define FCML_OP_MODRM_RM_16             \
    FCML_OP_RM(FCML_REG_GPR, FCML_EOS_WORD, FCML_EOS_WORD, FCML_RMF_RM)
#define FCML_OP_MODRM_RM_16_W           (FCML_OP_MODRM_RM_16 | FCML_OA_W)
#define FCML_OP_MODRM_RM_16_RW          (FCML_OP_MODRM_RM_16 | FCML_OA_RW)

#define FCML_OP_MODRM_RM_32             \
    FCML_OP_RM(FCML_REG_GPR, FCML_EOS_DWORD, FCML_EOS_DWORD, FCML_RMF_RM )
#define FCML_OP_MODRM_RM_32_W           (FCML_OP_MODRM_RM_32 | FCML_OA_W)
#define FCML_OP_MODRM_RM_32_RW          (FCML_OP_MODRM_RM_32 | FCML_OA_RW)

#define FCML_OP_MODRM_RM_64             \
    FCML_OP_RM(FCML_REG_GPR, FCML_EOS_QWORD, FCML_EOS_QWORD, FCML_RMF_RM)
#define FCML_OP_MODRM_RM_64_W           (FCML_OP_MODRM_RM_64 | FCML_OA_W)
#define FCML_OP_MODRM_RM_64_RW          (FCML_OP_MODRM_RM_64 | FCML_OA_RW)

#define FCML_OP_MODRM_RM_128            \
    FCML_OP_RM(FCML_REG_GPR, FCML_EOS_OWORD, FCML_EOS_OWORD, FCML_RMF_RM )
#define FCML_OP_MODRM_RM_128_W          (FCML_OP_MODRM_RM_128 | FCML_OA_W)
#define FCML_OP_MODRM_RM_128_RW         (FCML_OP_MODRM_RM_128 | FCML_OA_RW)

#define FCML_OP_MODRM_RM_OP_8           \
    FCML_OP_RM(FCML_REG_GPR, FCML_EOS_BYTE, FCML_EOS_BYTE | FCML_EOS_OPT, \
            FCML_RMF_RM)
#define FCML_OP_MODRM_RM_OP_8_W         (FCML_OP_MODRM_RM_OP_8 | FCML_OA_W)
#define FCML_OP_MODRM_RM_OP_8_RW        (FCML_OP_MODRM_RM_OP_8 | FCML_OA_RW)

#define FCML_OP_MODRM_RM_OP_16          \
    FCML_OP_RM(FCML_REG_GPR, FCML_EOS_WORD, FCML_EOS_WORD | FCML_EOS_OPT, \
            FCML_RMF_RM )
#define FCML_OP_MODRM_RM_OP_16_W        (FCML_OP_MODRM_RM_OP_16 | FCML_OA_W)
#define FCML_OP_MODRM_RM_OP_16_RW       (FCML_OP_MODRM_RM_OP_16 | FCML_OA_RW)

#define FCML_OP_MODRM_RM_OP_32          \
    FCML_OP_RM(FCML_REG_GPR, FCML_EOS_DWORD, FCML_EOS_DWORD | FCML_EOS_OPT, \
            FCML_RMF_RM)
#define FCML_OP_MODRM_RM_OP_32_W        (FCML_OP_MODRM_RM_OP_32 | FCML_OA_W)
#define FCML_OP_MODRM_RM_OP_32_RW       (FCML_OP_MODRM_RM_OP_32 | FCML_OA_RW)

#define FCML_OP_MODRM_RM_OP_64          \
    FCML_OP_RM(FCML_REG_GPR, FCML_EOS_QWORD, FCML_EOS_QWORD | FCML_EOS_OPT, \
            FCML_RMF_RM )
#define FCML_OP_MODRM_RM_OP_64_W        (FCML_OP_MODRM_RM_OP_64 | FCML_OA_W)
#define FCML_OP_MODRM_RM_OP_64_RW       (FCML_OP_MODRM_RM_OP_64 | FCML_OA_RW)
#define FCML_OP_MODRM_RM_OP_128         \
    FCML_OP_RM(FCML_REG_GPR, FCML_EOS_OWORD, FCML_EOS_OWORD | FCML_EOS_OPT, \
            FCML_RMF_RM)
#define FCML_OP_MODRM_RM_OP_128_W       (FCML_OP_MODRM_RM_OP_128 | FCML_OA_W)
#define FCML_OP_MODRM_RM_OP_128_RW      (FCML_OP_MODRM_RM_OP_128 | FCML_OA_RW)

#define FCML_OP_MODRM_RM                \
    FCML_OP_RM(FCML_REG_GPR, FCML_EOS_EOSA, FCML_EOS_EOSA, FCML_RMF_RM)
#define FCML_OP_MODRM_RM_W              (FCML_OP_MODRM_RM | FCML_OA_W)
#define FCML_OP_MODRM_RM_RW             (FCML_OP_MODRM_RM | FCML_OA_RW)

#define FCML_OP_MODRM_RM_I              \
    FCML_OP_RM(FCML_REG_GPR, FCML_EOS_EOSA, FCML_EOS_EOSA, FCML_RMF_RM | \
            FCML_RMF_I)
#define FCML_OP_MODRM_RM_I_W            (FCML_OP_MODRM_RM | FCML_OA_W)
#define FCML_OP_MODRM_RM_I_RW           (FCML_OP_MODRM_RM | FCML_OA_RW)
#define FCML_OP_MODRM_R_8               FCML_OP_R(FCML_REG_GPR, FCML_EOS_BYTE)
#define FCML_OP_MODRM_R_8_W             (FCML_OP_MODRM_R_8 | FCML_OA_W)
#define FCML_OP_MODRM_R_8_RW            (FCML_OP_MODRM_R_8 | FCML_OA_RW)
#define FCML_OP_MODRM_R_16              FCML_OP_R(FCML_REG_GPR, FCML_EOS_WORD)
#define FCML_OP_MODRM_R_16_W            (FCML_OP_MODRM_R_16 | FCML_OA_W)
#define FCML_OP_MODRM_R_16_RW           (FCML_OP_MODRM_R_16 | FCML_OA_RW)
#define FCML_OP_MODRM_R_32              FCML_OP_R(FCML_REG_GPR, FCML_EOS_DWORD)
#define FCML_OP_MODRM_R_32_W            (FCML_OP_MODRM_R_32 | FCML_OA_W)
#define FCML_OP_MODRM_R_32_RW           (FCML_OP_MODRM_R_32 | FCML_OA_RW)
#define FCML_OP_MODRM_R_64              FCML_OP_R(FCML_REG_GPR, FCML_EOS_QWORD)
#define FCML_OP_MODRM_R_64_W            (FCML_OP_MODRM_R_64 | FCML_OA_W)
#define FCML_OP_MODRM_R_64_RW           (FCML_OP_MODRM_R_64 | FCML_OA_RW)
#define FCML_OP_MODRM_R                 FCML_OP_R(FCML_REG_GPR, FCML_EOS_EOSA)
#define FCML_OP_MODRM_R_W               (FCML_OP_MODRM_R | FCML_OA_W)
#define FCML_OP_MODRM_R_RW              (FCML_OP_MODRM_R | FCML_OA_RW)

#define FCML_OP_MODRM_M                 \
    FCML_OP_RM(FCML_REG_UNDEFINED, FCML_EOS_UNDEFINED, FCML_EOS_EOSA, \
            FCML_RMF_M)
#define FCML_OP_MODRM_M_W               (FCML_OP_MODRM_M | FCML_OA_W)
#define FCML_OP_MODRM_M_RW              (FCML_OP_MODRM_M | FCML_OA_RW)

#define FCML_OP_MODRM_M_8               \
    FCML_OP_RM(FCML_REG_UNDEFINED, FCML_EOS_UNDEFINED, FCML_EOS_BYTE, \
            FCML_RMF_M)
#define FCML_OP_MODRM_M_8_W             (FCML_OP_MODRM_M_8 | FCML_OA_W)
#define FCML_OP_MODRM_M_8_RW            (FCML_OP_MODRM_M_8 | FCML_OA_RW)

#define FCML_OP_MODRM_M_16              \
    FCML_OP_RM(FCML_REG_UNDEFINED, FCML_EOS_UNDEFINED, FCML_EOS_WORD, \
            FCML_RMF_M)
#define FCML_OP_MODRM_M_16_W            (FCML_OP_MODRM_M_16 | FCML_OA_W)
#define FCML_OP_MODRM_M_16_RW           (FCML_OP_MODRM_M_16 | FCML_OA_RW)

#define FCML_OP_MODRM_M_32              \
    FCML_OP_RM(FCML_REG_UNDEFINED, FCML_EOS_UNDEFINED, FCML_EOS_DWORD, \
            FCML_RMF_M)
#define FCML_OP_MODRM_M_32_W            (FCML_OP_MODRM_M_32 | FCML_OA_W)
#define FCML_OP_MODRM_M_32_RW           (FCML_OP_MODRM_M_32 | FCML_OA_RW)

#define FCML_OP_MODRM_M_64              \
    FCML_OP_RM(FCML_REG_UNDEFINED, FCML_EOS_UNDEFINED, FCML_EOS_QWORD, \
            FCML_RMF_M)
#define FCML_OP_MODRM_M_64_W            (FCML_OP_MODRM_M_64 | FCML_OA_W)
#define FCML_OP_MODRM_M_64_RW           (FCML_OP_MODRM_M_64 | FCML_OA_RW)

#define FCML_OP_MODRM_M_80              \
    FCML_OP_RM(FCML_REG_UNDEFINED, FCML_EOS_UNDEFINED, FCML_EOS_TBYTE, \
            FCML_RMF_M)
#define FCML_OP_MODRM_M_80_W            (FCML_OP_MODRM_M_80 | FCML_OA_W)
#define FCML_OP_MODRM_M_80_RW           (FCML_OP_MODRM_M_80 | FCML_OA_RW)

#define FCML_OP_MODRM_M_128             \
    FCML_OP_RM(FCML_REG_UNDEFINED, FCML_EOS_UNDEFINED, FCML_EOS_OWORD, \
            FCML_RMF_M)
#define FCML_OP_MODRM_M_128_W           (FCML_OP_MODRM_M_128 | FCML_OA_W)
#define FCML_OP_MODRM_M_128_RW          (FCML_OP_MODRM_M_128 | FCML_OA_RW)

#define FCML_OP_MODRM_M_256             \
    FCML_OP_RM(FCML_REG_UNDEFINED, FCML_EOS_UNDEFINED, FCML_EOS_YWORD, \
            FCML_RMF_M)
#define FCML_OP_MODRM_M_256_W           (FCML_OP_MODRM_M_256 | FCML_OA_W)
#define FCML_OP_MODRM_M_256_RW          (FCML_OP_MODRM_M_256 | FCML_OA_RW)

#define FCML_OP_MODRM_M_XMM             \
    FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_UNDEFINED, FCML_EOS_OWORD, FCML_RMF_M)
#define FCML_OP_MODRM_M_XMM_W           (FCML_OP_MODRM_M_XMM | FCML_OA_W)
#define FCML_OP_MODRM_M_XMM_RW          (FCML_OP_MODRM_M_XMM | FCML_OA_RW)

#define FCML_OP_MODRM_M_YMM             \
    FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_UNDEFINED, FCML_EOS_YWORD, FCML_RMF_M)
#define FCML_OP_MODRM_M_YMM_W           (FCML_OP_MODRM_M_YMM | FCML_OA_W)
#define FCML_OP_MODRM_M_YMM_RW          (FCML_OP_MODRM_M_YMM | FCML_OA_RW)

#define FCML_OP_MODRM_M_14_28           \
    FCML_OP_RM(FCML_REG_UNDEFINED, FCML_EOS_UNDEFINED, FCML_EOS_14_28, \
            FCML_RMF_M)
#define FCML_OP_MODRM_M_14_28_W         (FCML_OP_MODRM_M_14_28 | FCML_OA_W)
#define FCML_OP_MODRM_M_14_28_RW        (FCML_OP_MODRM_M_14_28 | FCML_OA_RW)

#define FCML_OP_MODRM_M_94_108          \
    FCML_OP_RM(FCML_REG_UNDEFINED, FCML_EOS_UNDEFINED, FCML_EOS_94_108, \
            FCML_RMF_M)
#define FCML_OP_MODRM_M_94_108_W        (FCML_OP_MODRM_M_94_108 | FCML_OA_W)
#define FCML_OP_MODRM_M_94_108_RW       (FCML_OP_MODRM_M_94_108 | FCML_OA_RW)

#define FCML_OP_MODRM_M_FP              \
    FCML_OP_RM(FCML_REG_UNDEFINED, FCML_EOS_UNDEFINED, FCML_EOS_FP, FCML_RMF_M)
#define FCML_OP_MODRM_M_FP_W            (FCML_OP_MODRM_M_FP | FCML_OA_W)
#define FCML_OP_MODRM_M_FP_RW           (FCML_OP_MODRM_M_FP | FCML_OA_RW)

#define FCML_OP_MODRM_M_FPI             \
    FCML_OP_RM(FCML_REG_UNDEFINED, FCML_EOS_UNDEFINED, FCML_EOS_FPI, FCML_RMF_M)
#define FCML_OP_MODRM_M_FPI_W           (FCML_OP_MODRM_M_FPI | FCML_OA_W)
#define FCML_OP_MODRM_M_FPI_RW          (FCML_OP_MODRM_M_FPI | FCML_OA_RW)

#define FCML_OP_MODRM_M_512B            \
    FCML_OP_RM(FCML_REG_UNDEFINED, FCML_EOS_UNDEFINED, FCML_EOS_512B, \
            FCML_RMF_M)
#define FCML_OP_MODRM_M_512B_W          (FCML_OP_MODRM_M_512B | FCML_OA_W)
#define FCML_OP_MODRM_M_512B_RW         (FCML_OP_MODRM_M_512B | FCML_OA_RW)

#define FCML_OP_MODRM_M_UNDEF           \
    FCML_OP_RM(FCML_REG_UNDEFINED, FCML_EOS_UNDEFINED, FCML_EOS_UNDEFINED, \
            FCML_RMF_M)
#define FCML_OP_MODRM_M_UNDEF_W         (FCML_OP_MODRM_M_UNDEF | FCML_OA_W)
#define FCML_OP_MODRM_M_UNDEF_RW        (FCML_OP_MODRM_M_UNDEF | FCML_OA_RW)

#define FCML_OP_MODRM_M_FPI             \
    FCML_OP_RM(FCML_REG_UNDEFINED, FCML_EOS_UNDEFINED, FCML_EOS_FPI, \
            FCML_RMF_M)

#define FCML_OP_MODRM_RM_OP             \
    FCML_OP_RM(FCML_REG_GPR, FCML_EOS_EOSA, FCML_EOS_EOSA | FCML_EOS_OPT, \
            FCML_RMF_RM)
#define FCML_OP_MODRM_RM_OP_W           (FCML_OP_MODRM_RM_OP | FCML_OA_W)
#define FCML_OP_MODRM_RM_OP_RW          (FCML_OP_MODRM_RM_OP | FCML_OA_RW)

#define FCML_OP_MODRM_RM_GPR_8_REG          \
    FCML_OP_RM(FCML_REG_GPR, FCML_EOS_BYTE, FCML_EOS_UNDEFINED, FCML_RMF_R)

#define FCML_OP_MODRM_RM_GPR_16_REG         \
    FCML_OP_RM(FCML_REG_GPR, FCML_EOS_WORD, FCML_EOS_UNDEFINED, FCML_RMF_R)

#define FCML_OP_MODRM_RM_GPR_32_REG         \
    FCML_OP_RM(FCML_REG_GPR, FCML_EOS_DWORD, FCML_EOS_UNDEFINED, FCML_RMF_R)

#define FCML_OP_MODRM_RM_GPR_64_REG         \
    FCML_OP_RM(FCML_REG_GPR, FCML_EOS_QWORD, FCML_EOS_UNDEFINED, FCML_RMF_R)

#define FCML_OP_MODRM_RM_K_REG_W        (FCML_OP_MODRM_RM_K_REG | FCML_OA_W)
#define FCML_OP_MODRM_RM_K_REG_RW       (FCML_OP_MODRM_RM_K_REG | FCML_OA_RW)

#define FCML_OP_MODRM_M_OP              \
    FCML_OP_RM(FCML_REG_UNDEFINED, FCML_EOS_UNDEFINED, FCML_EOS_EOSA | \
            FCML_EOS_OPT, FCML_RMF_M)
#define FCML_OP_MODRM_M_OP_W            (FCML_OP_MODRM_M_OP | FCML_OA_W)
#define FCML_OP_MODRM_M_OP_RW           (FCML_OP_MODRM_M_OP | FCML_OA_RW)

#define FCML_OP_MODRM_M_OP_8            \
    FCML_OP_RM(FCML_REG_UNDEFINED, FCML_EOS_UNDEFINED, FCML_EOS_BYTE | \
            FCML_EOS_OPT, FCML_RMF_M)
#define FCML_OP_MODRM_M_OP_8_W          (FCML_OP_MODRM_M_OP_8 | FCML_OA_W)
#define FCML_OP_MODRM_M_OP_8_RW         (FCML_OP_MODRM_M_OP_8 | FCML_OA_RW)

#define FCML_OP_MODRM_M_OP_16           \
    FCML_OP_RM(FCML_REG_UNDEFINED, FCML_EOS_UNDEFINED, FCML_EOS_WORD | \
            FCML_EOS_OPT, FCML_RMF_M)
#define FCML_OP_MODRM_M_OP_16_W         (FCML_OP_MODRM_M_OP_16 | FCML_OA_W)
#define FCML_OP_MODRM_M_OP_16_RW        (FCML_OP_MODRM_M_OP_16 | FCML_OA_RW)

#define FCML_OP_MODRM_M_OP_32           \
    FCML_OP_RM(FCML_REG_UNDEFINED, FCML_EOS_UNDEFINED, FCML_EOS_DWORD | \
            FCML_EOS_OPT, FCML_RMF_M)
#define FCML_OP_MODRM_M_OP_32_W         (FCML_OP_MODRM_M_OP_32 | FCML_OA_W)
#define FCML_OP_MODRM_M_OP_32_RW        (FCML_OP_MODRM_M_OP_32 | FCML_OA_RW)

#define FCML_OP_MODRM_M_OP_64           \
    FCML_OP_RM(FCML_REG_UNDEFINED, FCML_EOS_UNDEFINED, FCML_EOS_QWORD | \
            FCML_EOS_OPT, FCML_RMF_M)
#define FCML_OP_MODRM_M_OP_64_W         (FCML_OP_MODRM_M_OP_64 | FCML_OA_W)
#define FCML_OP_MODRM_M_OP_64_RW        (FCML_OP_MODRM_M_OP_64 | FCML_OA_RW)

#define FCML_OP_MODRM_M_OP_80           \
    FCML_OP_RM(FCML_REG_UNDEFINED, FCML_EOS_UNDEFINED, FCML_EOS_TBYTE | \
            FCML_EOS_OPT, FCML_RMF_M)
#define FCML_OP_MODRM_M_OP_80_W         (FCML_OP_MODRM_M_OP_80 | FCML_OA_W)
#define FCML_OP_MODRM_M_OP_80_RW        (FCML_OP_MODRM_M_OP_80 | FCML_OA_RW)

#define FCML_OP_MODRM_M_OP_128          \
    FCML_OP_RM(FCML_REG_UNDEFINED, FCML_EOS_UNDEFINED, FCML_EOS_OWORD | \
            FCML_EOS_OPT, FCML_RMF_M)
#define FCML_OP_MODRM_M_OP_128_W        (FCML_OP_MODRM_M_OP_128 | FCML_OA_W)
#define FCML_OP_MODRM_M_OP_128_RW       (FCML_OP_MODRM_M_OP_128 | FCML_OA_RW)

#define FCML_OP_MODRM_M_OP_256          \
    FCML_OP_RM(FCML_REG_UNDEFINED, FCML_EOS_UNDEFINED, FCML_EOS_YWORD | \
            FCML_EOS_OPT, FCML_RMF_M)
#define FCML_OP_MODRM_M_OP_256_W        (FCML_OP_MODRM_M_OP_256 | FCML_OA_W)
#define FCML_OP_MODRM_M_OP_256_RW       (FCML_OP_MODRM_M_OP_256 | FCML_OA_RW)

#define FCML_OP_MODRM_M_OP_XMM          \
    FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_UNDEFINED, FCML_EOS_XWORD | \
            FCML_EOS_OPT, FCML_RMF_M)
#define FCML_OP_MODRM_M_OP_XMM_W        (FCML_OP_MODRM_M_OP_XMM | FCML_OA_W)
#define FCML_OP_MODRM_M_OP_XMM_RW       (FCML_OP_MODRM_M_OP_XMM | FCML_OA_RW)

#define FCML_OP_MODRM_M_OP_YMM          \
    FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_UNDEFINED, FCML_EOS_YWORD | \
            FCML_EOS_OPT, FCML_RMF_M)
#define FCML_OP_MODRM_M_OP_YMM_W        (FCML_OP_MODRM_M_OP_YMM | FCML_OA_W)
#define FCML_OP_MODRM_M_OP_YMM_RW       (FCML_OP_MODRM_M_OP_YMM | FCML_OA_RW)

#define FCML_OP_MODRM_M_OP_14_28        \
    FCML_OP_RM(FCML_REG_UNDEFINED, FCML_EOS_UNDEFINED, FCML_EOS_14_28 | \
            FCML_EOS_OPT, FCML_RMF_M)
#define FCML_OP_MODRM_M_OP_14_28_W      (FCML_OP_MODRM_M_OP_14_28 | FCML_OA_W)
#define FCML_OP_MODRM_M_OP_14_28_RW     (FCML_OP_MODRM_M_OP_14_28 | FCML_OA_RW)

#define FCML_OP_MODRM_M_OP_FP           \
    FCML_OP_RM(FCML_REG_UNDEFINED, FCML_EOS_UNDEFINED, FCML_EOS_FP | \
            FCML_EOS_OPT, FCML_RMF_M)
#define FCML_OP_MODRM_M_OP_FP_W         (FCML_OP_MODRM_M_OP_FP | FCML_OA_W)
#define FCML_OP_MODRM_M_OP_FP_RW        (FCML_OP_MODRM_M_OP_FP | FCML_OA_RW)

#define FCML_OP_MODRM_M_OP_512B         \
    FCML_OP_RM(FCML_REG_UNDEFINED, FCML_EOS_UNDEFINED, FCML_EOS_512B | \
            FCML_EOS_OPT, FCML_RMF_M)
#define FCML_OP_MODRM_M_OP_512B_W       (FCML_OP_MODRM_M_OP_512B | FCML_OA_W)
#define FCML_OP_MODRM_M_OP_512B_RW      (FCML_OP_MODRM_M_OP_512B | FCML_OA_RW)

#define FCML_OP_MODRM_MM_OSA            \
    FCML_OP_RM(FCML_REG_UNDEFINED, FCML_EOS_UNDEFINED, FCML_EOS_32_64, \
            FCML_RMF_M)
#define FCML_OP_MODRM_MM_OSA_W          (FCML_OP_MODRM_MM_OSA | FCML_OA_W)
#define FCML_OP_MODRM_MM_OSA_RW         (FCML_OP_MODRM_MM_OSA | FCML_OA_RW)

#define FCML_OP_MODRM_MM_OP_OSA         \
    FCML_OP_RM(FCML_REG_UNDEFINED, FCML_EOS_UNDEFINED, FCML_EOS_32_64 | \
            FCML_EOS_OPT, FCML_RMF_M)
#define FCML_OP_MODRM_MM_OP_OSA_W       (FCML_OP_MODRM_MM_OP_OSA | FCML_OA_W)
#define FCML_OP_MODRM_MM_OP_OSA_RW      (FCML_OP_MODRM_MM_OP_OSA | FCML_OA_RW)

#define FCML_OP_MODRM_RM_MMX_OP         \
    FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_QWORD, FCML_EOS_QWORD | FCML_EOS_OPT, \
            FCML_RMF_RM)
#define FCML_OP_MODRM_RM_MMX_OP_W       (FCML_OP_MODRM_RM_MMX_OP | FCML_OA_W)
#define FCML_OP_MODRM_RM_MMX_OP_RW      (FCML_OP_MODRM_RM_MMX_OP | FCML_OA_RW)

#define FCML_OP_MODRM_RM_MMX            \
    FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_QWORD, FCML_EOS_QWORD, FCML_RMF_RM)
#define FCML_OP_MODRM_RM_MMX_W          (FCML_OP_MODRM_RM_MMX | FCML_OA_W)
#define FCML_OP_MODRM_RM_MMX_RW         (FCML_OP_MODRM_RM_MMX | FCML_OA_RW)

#define FCML_OP_MODRM_RM_MMX_32         \
    FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_QWORD, FCML_EOS_DWORD, FCML_RMF_RM)
#define FCML_OP_MODRM_RM_MMX_32_W       (FCML_OP_MODRM_RM_MMX_32 | FCML_OA_W)
#define FCML_OP_MODRM_RM_MMX_32_RW      (FCML_OP_MODRM_RM_MMX_32 | FCML_OA_RW)

#define FCML_OP_MODRM_R_MMX             FCML_OP_R(FCML_REG_SIMD, FCML_EOS_QWORD)
#define FCML_OP_MODRM_R_MMX_W           (FCML_OP_MODRM_R_MMX | FCML_OA_W)
#define FCML_OP_MODRM_R_MMX_RW          (FCML_OP_MODRM_R_MMX | FCML_OA_RW)

#define FCML_OP_MODRM_RM_ZMM_512        \
    FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_ZWORD, FCML_EOS_ZWORD, FCML_RMF_RM)
#define FCML_OP_MODRM_RM_ZMM_512_W      (FCML_OP_MODRM_RM_ZMM_512 | FCML_OA_W)
#define FCML_OP_MODRM_RM_ZMM_512_RW     (FCML_OP_MODRM_RM_ZMM_512 | FCML_OA_RW)

#define FCML_OP_MODRM_RM_YMM_256        \
    FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_YWORD, FCML_EOS_YWORD, FCML_RMF_RM)
#define FCML_OP_MODRM_RM_YMM_256_W      (FCML_OP_MODRM_RM_YMM_256 | FCML_OA_W)
#define FCML_OP_MODRM_RM_YMM_256_RW     (FCML_OP_MODRM_RM_YMM_256 | FCML_OA_RW)

#define FCML_OP_MODRM_RM_XMM_128        \
    FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_OWORD, FCML_EOS_OWORD, FCML_RMF_RM)
#define FCML_OP_MODRM_RM_XMM_128_W      (FCML_OP_MODRM_RM_XMM_128 | FCML_OA_W)
#define FCML_OP_MODRM_RM_XMM_128_RW     (FCML_OP_MODRM_RM_XMM_128 | FCML_OA_RW)

#define FCML_OP_MODRM_RM_XMM_64         \
    FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_OWORD, FCML_EOS_QWORD, FCML_RMF_RM)
#define FCML_OP_MODRM_RM_XMM_64_W       (FCML_OP_MODRM_RM_XMM_64 | FCML_OA_W)
#define FCML_OP_MODRM_RM_XMM_64_RW      (FCML_OP_MODRM_RM_XMM_64 | FCML_OA_RW)

#define FCML_OP_MODRM_RM_XMM_32         \
    FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_OWORD, FCML_EOS_DWORD, FCML_RMF_RM)
#define FCML_OP_MODRM_RM_XMM_32_W       (FCML_OP_MODRM_RM_XMM_32 | FCML_OA_W)
#define FCML_OP_MODRM_RM_XMM_32_RW      (FCML_OP_MODRM_RM_XMM_32 | FCML_OA_RW)

#define FCML_OP_MODRM_RM_XMM_8          \
    FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_OWORD, FCML_EOS_BYTE, FCML_RMF_RM)
#define FCML_OP_MODRM_RM_XMM_8_W        (FCML_OP_MODRM_RM_XMM_8 | FCML_OA_W)
#define FCML_OP_MODRM_RM_XMM_8_RW       (FCML_OP_MODRM_RM_XMM_8 | FCML_OA_RW)

#define FCML_OP_MODRM_RM_XMM_16         \
    FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_OWORD, FCML_EOS_WORD, FCML_RMF_RM)
#define FCML_OP_MODRM_RM_XMM_16_W       (FCML_OP_MODRM_RM_XMM_16 | FCML_OA_W)
#define FCML_OP_MODRM_RM_XMM_16_RW      (FCML_OP_MODRM_RM_XMM_16 | FCML_OA_RW)

#define FCML_OP_MODRM_RM_XMM_OP_64      \
    FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_OWORD, FCML_EOS_QWORD | FCML_EOS_OPT, \
            FCML_RMF_RM)
#define FCML_OP_MODRM_RM_XMM_OP_64_W   (FCML_OP_MODRM_RM_XMM_OP_64 | FCML_OA_W)
#define FCML_OP_MODRM_RM_XMM_OP_64_RW  (FCML_OP_MODRM_RM_XMM_OP_64 | FCML_OA_RW)

#define FCML_OP_MODRM_RM_XMM_OP_128    \
    FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_OWORD, FCML_EOS_OWORD | FCML_EOS_OPT, \
            FCML_RMF_RM)
#define FCML_OP_MODRM_RM_XMM_OP_128_W  (FCML_OP_MODRM_RM_XMM_OP_128 | FCML_OA_W)
#define FCML_OP_MODRM_RM_XMM_OP_128_RW \
    (FCML_OP_MODRM_RM_XMM_OP_128 | FCML_OA_RW)

#define FCML_OP_MODRM_RM_YMM_OP_256    \
    FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_YWORD, FCML_EOS_YWORD | FCML_EOS_OPT, \
            FCML_RMF_RM)
#define FCML_OP_MODRM_RM_YMM_OP_256_W   \
    (FCML_OP_MODRM_RM_YMM_OP_256 | FCML_OA_W)
#define FCML_OP_MODRM_RM_YMM_OP_256_RW  \
    (FCML_OP_MODRM_RM_YMM_OP_256 | FCML_OA_RW)

#define FCML_OP_MODRM_RM_ZMM_OP_512    \
    FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_ZWORD, FCML_EOS_ZWORD | FCML_EOS_OPT, \
            FCML_RMF_RM)
#define FCML_OP_MODRM_RM_ZMM_OP_512_W   \
    (FCML_OP_MODRM_RM_ZMM_OP_512 | FCML_OA_W)
#define FCML_OP_MODRM_RM_ZMM_OP_512_RW  \
    (FCML_OP_MODRM_RM_ZMM_OP_512 | FCML_OA_RW)

#define FCML_OP_MODRM_RM_MMX_OP_32      \
    FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_QWORD, FCML_EOS_DWORD | FCML_EOS_OPT, \
            FCML_RMF_RM)

#define FCML_OP_MODRM_RM_MMX_OP_32_W   (FCML_OP_MODRM_RM_MMX_OP_32 | FCML_OA_W)
#define FCML_OP_MODRM_RM_MMX_OP_32_RW  (FCML_OP_MODRM_RM_MMX_OP_32 | FCML_OA_RW)
#define FCML_OP_MODRM_RM_XMM_OP_32     \
    FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_OWORD, FCML_EOS_DWORD | FCML_EOS_OPT, \
            FCML_RMF_RM)

#define FCML_OP_MODRM_RM_XMM_OP_32_W   (FCML_OP_MODRM_RM_XMM_OP_32 | FCML_OA_W)
#define FCML_OP_MODRM_RM_XMM_OP_32_RW  (FCML_OP_MODRM_RM_XMM_OP_32 | FCML_OA_RW)
#define FCML_OP_MODRM_RM_XMM_OP_16     \
    FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_OWORD, FCML_EOS_WORD | FCML_EOS_OPT, \
            FCML_RMF_RM)

#define FCML_OP_MODRM_RM_XMM_OP_16_W   (FCML_OP_MODRM_RM_XMM_OP_16 | FCML_OA_W)
#define FCML_OP_MODRM_RM_XMM_OP_16_RW  (FCML_OP_MODRM_RM_XMM_OP_16 | FCML_OA_RW)
#define FCML_OP_MODRM_RM_XMM_OP_8      \
    FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_OWORD, FCML_EOS_BYTE | FCML_EOS_OPT, \
            FCML_RMF_RM)

#define FCML_OP_MODRM_RM_XMM_OP_8_W    (FCML_OP_MODRM_RM_XMM_OP_8 | FCML_OA_W)
#define FCML_OP_MODRM_RM_XMM_OP_8_RW   (FCML_OP_MODRM_RM_XMM_OP_8 | FCML_OA_RW)
#define FCML_OP_MODRM_M_YMM_256        \
    FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_YWORD, FCML_EOS_YWORD, FCML_RMF_M)

#define FCML_OP_MODRM_M_YMM_256_W      (FCML_OP_MODRM_RM_YMM_256 | FCML_OA_W)
#define FCML_OP_MODRM_M_YMM_256_RW     (FCML_OP_MODRM_RM_YMM_256 | FCML_OA_RW)
#define FCML_OP_MODRM_M_XMM_128        \
    FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_OWORD, FCML_EOS_OWORD, FCML_RMF_M)

#define FCML_OP_MODRM_M_XMM_128_W      (FCML_OP_MODRM_RM_XMM_128 | FCML_OA_W)
#define FCML_OP_MODRM_M_XMM_128_RW     (FCML_OP_MODRM_RM_XMM_128 | FCML_OA_RW)
#define FCML_OP_MODRM_M_XMM_64         \
    FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_OWORD, FCML_EOS_QWORD, FCML_RMF_M)

#define FCML_OP_MODRM_M_XMM_64_W       (FCML_OP_MODRM_RM_XMM_64 | FCML_OA_W)
#define FCML_OP_MODRM_M_XMM_64_RW      (FCML_OP_MODRM_RM_XMM_64 | FCML_OA_RW)
#define FCML_OP_MODRM_M_XMM_32         \
    FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_OWORD, FCML_EOS_DWORD, FCML_RMF_M)

#define FCML_OP_MODRM_M_XMM_32_W       (FCML_OP_MODRM_RM_XMM_32 | FCML_OA_W)
#define FCML_OP_MODRM_M_XMM_32_RW      (FCML_OP_MODRM_RM_XMM_32 | FCML_OA_RW)
#define FCML_OP_MODRM_M_XMM_16         \
    FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_OWORD, FCML_EOS_WORD, FCML_RMF_M)

#define FCML_OP_MODRM_M_XMM_16_W       (FCML_OP_MODRM_RM_XMM_16 | FCML_OA_W)
#define FCML_OP_MODRM_M_XMM_16_RW      (FCML_OP_MODRM_RM_XMM_16 | FCML_OA_RW)
#define FCML_OP_MODRM_R_XMM            FCML_OP_R(FCML_REG_SIMD, FCML_EOS_OWORD)
#define FCML_OP_MODRM_R_XMM_W          (FCML_OP_MODRM_R_XMM | FCML_OA_W)
#define FCML_OP_MODRM_R_XMM_RW         (FCML_OP_MODRM_R_XMM | FCML_OA_RW)
#define FCML_OP_MODRM_R_YMM            FCML_OP_R(FCML_REG_SIMD, FCML_EOS_YWORD)
#define FCML_OP_MODRM_R_YMM_W          (FCML_OP_MODRM_R_YMM | FCML_OA_W)
#define FCML_OP_MODRM_R_YMM_RW         (FCML_OP_MODRM_R_YMM | FCML_OA_RW)
#define FCML_OP_MODRM_R_ZMM            FCML_OP_R(FCML_REG_SIMD, FCML_EOS_ZWORD)
#define FCML_OP_MODRM_R_ZMM_W          (FCML_OP_MODRM_R_ZMM | FCML_OA_W)
#define FCML_OP_MODRM_R_ZMM_RW         (FCML_OP_MODRM_R_ZMM | FCML_OA_RW)
#define FCML_OP_MODRM_RM_SIMD_L        FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_L, \
        FCML_EOS_L, FCML_RMF_RM)
#define FCML_OP_MODRM_RM_SIMD_L_W       (FCML_OP_MODRM_RM_SIMD_L | FCML_OA_W)
#define FCML_OP_MODRM_RM_SIMD_L_RW      (FCML_OP_MODRM_RM_SIMD_L | FCML_OA_RW)
#define FCML_OP_MODRM_RM_SIMD_L_128     FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_L, \
        FCML_EOS_OWORD, FCML_RMF_RM)
#define FCML_OP_MODRM_RM_SIMD_L_128_W   \
    (FCML_OP_MODRM_RM_SIMD_L_128 | FCML_OA_W)
#define FCML_OP_MODRM_RM_SIMD_L_128_RW  \
    (FCML_OP_MODRM_RM_SIMD_L_128 | FCML_OA_RW)
#define FCML_OP_MODRM_RM_SIMD_L_64      FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_L, \
        FCML_EOS_QWORD, FCML_RMF_RM)
#define FCML_OP_MODRM_RM_SIMD_L_64_W    (FCML_OP_MODRM_RM_SIMD_L_64 | FCML_OA_W)
#define FCML_OP_MODRM_RM_SIMD_L_64_RW   \
    (FCML_OP_MODRM_RM_SIMD_L_64 | FCML_OA_RW)
#define FCML_OP_MODRM_RM_SIMD_L_32      \
    FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_L, FCML_EOS_DWORD, FCML_RMF_RM)
#define FCML_OP_MODRM_RM_SIMD_L_32_W    \
    (FCML_OP_MODRM_RM_SIMD_L_32 | FCML_OA_W)
#define FCML_OP_MODRM_RM_SIMD_L_32_RW   \
    (FCML_OP_MODRM_RM_SIMD_L_32 | FCML_OA_RW)
#define FCML_OP_MODRM_RM_SIMD_L_16      \
    FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_L, FCML_EOS_WORD, FCML_RMF_RM)
#define FCML_OP_MODRM_RM_SIMD_L_16_W    \
    (FCML_OP_MODRM_RM_SIMD_L_16 | FCML_OA_W)
#define FCML_OP_MODRM_RM_SIMD_L_16_RW   \
    (FCML_OP_MODRM_RM_SIMD_L_16 | FCML_OA_RW)
#define FCML_OP_MODRM_RM_SIMD_L_8       \
    FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_L, FCML_EOS_BYTE, FCML_RMF_RM)
#define FCML_OP_MODRM_RM_SIMD_L_8_W     \
    (FCML_OP_MODRM_RM_SIMD_L_8 | FCML_OA_W)
#define FCML_OP_MODRM_RM_SIMD_L_8_RW    \
    (FCML_OP_MODRM_RM_SIMD_L_8 | FCML_OA_RW)
#define FCML_OP_MODRM_RM_SIMD_L_OP      \
    FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_L, FCML_EOS_L | FCML_EOS_OPT, \
            FCML_RMF_RM)
#define FCML_OP_MODRM_RM_SIMD_L_OP_W    \
    (FCML_OP_MODRM_RM_SIMD_L_OP | FCML_OA_W)
#define FCML_OP_MODRM_RM_SIMD_L_OP_RW   \
    (FCML_OP_MODRM_RM_SIMD_L_OP | FCML_OA_RW)
#define FCML_OP_MODRM_RM_SIMD_L_OP_128    \
    FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_L, FCML_EOS_OWORD | FCML_EOS_OPT, \
            FCML_RMF_RM)
#define FCML_OP_MODRM_RM_SIMD_L_OP_128_W  \
    (FCML_OP_MODRM_RM_SIMD_L_OP_128 | FCML_OA_W)
#define FCML_OP_MODRM_RM_SIMD_L_OP_128_RW \
    (FCML_OP_MODRM_RM_SIMD_L_OP_128 | FCML_OA_RW)
#define FCML_OP_MODRM_RM_SIMD_L_OP_64     \
    FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_L, FCML_EOS_QWORD | FCML_EOS_OPT, \
            FCML_RMF_RM)
#define FCML_OP_MODRM_RM_SIMD_L_OP_64_W   \
    (FCML_OP_MODRM_RM_SIMD_L_OP_64 | FCML_OA_W)
#define FCML_OP_MODRM_RM_SIMD_L_OP_64_RW  \
    (FCML_OP_MODRM_RM_SIMD_L_OP_64 | FCML_OA_RW)
#define FCML_OP_MODRM_RM_SIMD_L_OP_32     \
    FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_L, FCML_EOS_DWORD | FCML_EOS_OPT, \
            FCML_RMF_RM)
#define FCML_OP_MODRM_RM_SIMD_L_OP_32_W   \
    (FCML_OP_MODRM_RM_SIMD_L_OP_32 | FCML_OA_W)
#define FCML_OP_MODRM_RM_SIMD_L_OP_32_RW  \
    (FCML_OP_MODRM_RM_SIMD_L_OP_32 | FCML_OA_RW)
#define FCML_OP_MODRM_RM_SIMD_L_OP_16     \
    FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_L, FCML_EOS_WORD | FCML_EOS_OPT, \
            FCML_RMF_RM)
#define FCML_OP_MODRM_RM_SIMD_L_OP_16_W   \
    (FCML_OP_MODRM_RM_SIMD_L_OP_16 | FCML_OA_W)
#define FCML_OP_MODRM_RM_SIMD_L_OP_16_RW  \
    (FCML_OP_MODRM_RM_SIMD_L_OP_16 | FCML_OA_RW)
#define FCML_OP_MODRM_RM_SIMD_L_OP_8      \
    FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_L, FCML_EOS_BYTE | FCML_EOS_OPT, \
            FCML_RMF_RM)
#define FCML_OP_MODRM_RM_SIMD_L_OP_8_W    \
    (FCML_OP_MODRM_RM_SIMD_L_OP_8 | FCML_OA_W)
#define FCML_OP_MODRM_RM_SIMD_L_OP_8_RW   \
    (FCML_OP_MODRM_RM_SIMD_L_OP_8 | FCML_OA_RW)
#define FCML_OP_MODRM_RM_SIMD_L_K1_Z_OP      \
    (FCML_OP_MODRM_RM_SIMD_L_OP | FCML_DECOR_Z | FCML_DECOR_K1)
#define FCML_OP_MODRM_RM_SIMD_L_K1_Z_OP_W    \
    (FCML_OP_MODRM_RM_SIMD_L_K1_Z_OP | FCML_OA_W)
#define FCML_OP_MODRM_RM_SIMD_E          \
    FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_EOSA, FCML_EOS_EOSA, FCML_RMF_RM)
#define FCML_OP_MODRM_RM_SIMD_E_W        (FCML_OP_MODRM_RM_SIMD_E | FCML_OA_W)
#define FCML_OP_MODRM_RM_SIMD_E_RW       (FCML_OP_MODRM_RM_SIMD_E | FCML_OA_RW)
#define FCML_OP_MODRM_RM_SIMD_E_128      \
    FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_EOSA, FCML_EOS_OWORD, FCML_RMF_RM)
#define FCML_OP_MODRM_RM_SIMD_E_128_W    \
    (FCML_OP_MODRM_RM_SIMD_E_128 | FCML_OA_W)
#define FCML_OP_MODRM_RM_SIMD_E_128_RW   \
    (FCML_OP_MODRM_RM_SIMD_E_128 | FCML_OA_RW)
#define FCML_OP_MODRM_RM_SIMD_E_64       \
    FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_EOSA, FCML_EOS_QWORD, FCML_RMF_RM)
#define FCML_OP_MODRM_RM_SIMD_E_64_W     \
    (FCML_OP_MODRM_RM_SIMD_E_64 | FCML_OA_W)
#define FCML_OP_MODRM_RM_SIMD_E_64_RW    \
    (FCML_OP_MODRM_RM_SIMD_E_64 | FCML_OA_RW)
#define FCML_OP_MODRM_RM_SIMD_E_32       \
    FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_EOSA, FCML_EOS_DWORD, FCML_RMF_RM)
#define FCML_OP_MODRM_RM_SIMD_E_32_W     \
    (FCML_OP_MODRM_RM_SIMD_E_32 | FCML_OA_W)
#define FCML_OP_MODRM_RM_SIMD_E_32_RW    \
    (FCML_OP_MODRM_RM_SIMD_E_32 | FCML_OA_RW)
#define FCML_OP_MODRM_RM_SIMD_E_16       \
    FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_EOSA, FCML_EOS_WORD, FCML_RMF_RM)
#define FCML_OP_MODRM_RM_SIMD_E_16_W     \
    (FCML_OP_MODRM_RM_SIMD_E_16 | FCML_OA_W)
#define FCML_OP_MODRM_RM_SIMD_E_16_RW    \
    (FCML_OP_MODRM_RM_SIMD_E_16 | FCML_OA_RW)
#define FCML_OP_MODRM_RM_SIMD_E_8        \
    FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_EOSA, FCML_EOS_BYTE, FCML_RMF_RM)
#define FCML_OP_MODRM_RM_SIMD_E_8_W      \
    (FCML_OP_MODRM_RM_SIMD_E_8 | FCML_OA_W)
#define FCML_OP_MODRM_RM_SIMD_E_8_RW     \
    (FCML_OP_MODRM_RM_SIMD_E_8 | FCML_OA_RW)

#define FCML_OP_MODRM_R_SIMD_L          FCML_OP_R(FCML_REG_SIMD, FCML_EOS_L)
#define FCML_OP_MODRM_R_SIMD_L_W        (FCML_OP_MODRM_R_SIMD_L | FCML_OA_W)
#define FCML_OP_MODRM_R_SIMD_L_RW       (FCML_OP_MODRM_R_SIMD_L | FCML_OA_RW)
#define FCML_OP_MODRM_R_SIMD_E          FCML_OP_R(FCML_REG_SIMD, FCML_EOS_EOSA)
#define FCML_OP_MODRM_R_SIMD_E_W        (FCML_OP_MODRM_R_SIMD_E | FCML_OA_W)
#define FCML_OP_MODRM_R_SIMD_E_RW       (FCML_OP_MODRM_R_SIMD_E | FCML_OA_RW)

/* AVX-512 */

#define FCML_OP_MODRM_RM_SIMD_REG          \
    FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_L | FCML_EOS_OPT, \
            FCML_EOS_UNDEFINED, FCML_RMF_R)
#define FCML_OP_MODRM_RM_SIMD_REG_W        (FCML_OP_MODRM_RM_SIMD_REG | FCML_OA_W)
#define FCML_OP_MODRM_RM_SIMD_REG_RW       (FCML_OP_MODRM_RM_SIMD_REG | FCML_OA_RW)

#define FCML_OP_MODRM_RM_K_REG          \
    FCML_OP_RM(FCML_REG_OPMASK, FCML_EOS_QWORD | FCML_EOS_OPT, \
            FCML_EOS_UNDEFINED, FCML_RMF_R)
#define FCML_OP_MODRM_RM_K_REG_W        (FCML_OP_MODRM_RM_K_REG | FCML_OA_W)
#define FCML_OP_MODRM_RM_K_REG_RW       (FCML_OP_MODRM_RM_K_REG | FCML_OA_RW)

#define FCML_OP_MODRM_RM_K_OP_8         \
    FCML_OP_RM(FCML_REG_OPMASK, FCML_EOS_QWORD | FCML_EOS_OPT, FCML_EOS_BYTE \
            | FCML_EOS_OPT, FCML_RMF_RM)
#define FCML_OP_MODRM_RM_K_OP_8_W      (FCML_OP_MODRM_RM_K_OP_8 | FCML_OA_W)
#define FCML_OP_MODRM_RM_K_OP_8_RW     (FCML_OP_MODRM_RM_K_OP_8 | FCML_OA_RW)

#define FCML_OP_MODRM_RM_K_OP_16        \
    FCML_OP_RM(FCML_REG_OPMASK, FCML_EOS_QWORD | FCML_EOS_OPT, FCML_EOS_WORD \
            | FCML_EOS_OPT, FCML_RMF_RM)
#define FCML_OP_MODRM_RM_K_OP_16_W      (FCML_OP_MODRM_RM_K_OP_16 | FCML_OA_W)
#define FCML_OP_MODRM_RM_K_OP_16_RW     (FCML_OP_MODRM_RM_K_OP_16 | FCML_OA_RW)

#define FCML_OP_MODRM_RM_K_OP_32        \
    FCML_OP_RM(FCML_REG_OPMASK, FCML_EOS_QWORD | FCML_EOS_OPT, FCML_EOS_DWORD \
            | FCML_EOS_OPT, FCML_RMF_RM)
#define FCML_OP_MODRM_RM_K_OP_32_W      (FCML_OP_MODRM_RM_K_OP_32 | FCML_OA_W)
#define FCML_OP_MODRM_RM_K_OP_32_RW     (FCML_OP_MODRM_RM_K_OP_32 | FCML_OA_RW)

#define FCML_OP_MODRM_RM_K_OP_64        \
    FCML_OP_RM(FCML_REG_OPMASK, FCML_EOS_QWORD | FCML_EOS_OPT, FCML_EOS_QWORD \
            | FCML_EOS_OPT, FCML_RMF_RM)
#define FCML_OP_MODRM_RM_K_OP_64_W      (FCML_OP_MODRM_RM_K_OP_64 | FCML_OA_W)
#define FCML_OP_MODRM_RM_K_OP_64_RW     (FCML_OP_MODRM_RM_K_OP_64 | FCML_OA_RW)

#define FCML_OP_MODRM_R_K               FCML_OP_R(FCML_REG_OPMASK, \
        FCML_EOS_QWORD | FCML_EOS_OPT)
#define FCML_OP_MODRM_R_K_W             (FCML_OP_MODRM_R_K | FCML_OA_W)
#define FCML_OP_MODRM_R_K_RW            (FCML_OP_MODRM_R_K | FCML_OA_RW)

#define FCML_OP_MODRM_R_K_K1_W          FCML_OP_MODRM_R_K_W | FCML_DECOR_K1

#define FCML_OP_MODRM_R_SIMD_L_K1_Z_W   FCML_OP_MODRM_R_SIMD_L_W | \
    FCML_DECOR_Z | FCML_DECOR_K1

#define FCML_OP_MODRM_R_SIMD_L_K1_Z_RW   FCML_OP_MODRM_R_SIMD_L_RW | \
    FCML_DECOR_Z | FCML_DECOR_K1

#define FCML_OP_MODRM_R_XMM_K1_Z_W      FCML_OP_MODRM_R_XMM_W | \
    FCML_DECOR_Z | FCML_DECOR_K1

#define FCML_OP_MODRM_R_XMM_K1_Z_RW     (FCML_OP_MODRM_R_XMM_RW | \
    FCML_DECOR_Z | FCML_DECOR_K1)

#define FCML_OP_MODRM_R_YMM_K1_Z_W      FCML_OP_MODRM_R_YMM_W | \
    FCML_DECOR_Z | FCML_DECOR_K1

#define FCML_OP_MODRM_R_ZMM_K1_Z_W      FCML_OP_MODRM_R_ZMM_W | \
    FCML_DECOR_Z | FCML_DECOR_K1

#define FCML_OP_MODRM_R_ZMM_K1_Z_RW      FCML_OP_MODRM_R_ZMM_RW | \
    FCML_DECOR_Z | FCML_DECOR_K1

#define FCML_OP_MODRM_RM_SIMD_L_BCAST_OP     FCML_OP_MODRM_RM_SIMD_L_OP | \
    FCML_DECOR_BCAST

#define FCML_OP_MODRM_RM_XMM_32_BCAST_OP     FCML_OP_MODRM_RM_XMM_OP_32 | \
    FCML_DECOR_BCAST

#define FCML_OP_MODRM_RM_XMM_64_BCAST_OP     FCML_OP_MODRM_RM_XMM_OP_64 | \
    FCML_DECOR_BCAST

#define FCML_OP_MODRM_RM_XMM_128_BCAST_OP     FCML_OP_MODRM_RM_XMM_OP_128 | \
    FCML_DECOR_BCAST

#define FCML_OP_MODRM_RM_YMM_256_BCAST_OP     FCML_OP_MODRM_RM_YMM_OP_256 | \
    FCML_DECOR_BCAST

#define FCML_OP_MODRM_RM_ZMM_512_BCAST_OP     FCML_OP_MODRM_RM_ZMM_OP_512 | \
    FCML_DECOR_BCAST

#define FCML_OP_MODRM_RM_XMM_64_BCAST         FCML_OP_MODRM_RM_XMM_64 | \
    FCML_DECOR_BCAST

#define FCML_OP_MODRM_RM_XMM_128_BCAST        FCML_OP_MODRM_RM_XMM_128 | \
    FCML_DECOR_BCAST

#define FCML_OP_MODRM_RM_YMM_256_BCAST        FCML_OP_MODRM_RM_YMM_256 | \
    FCML_DECOR_BCAST

#define FCML_OP_MODRM_RM_ZMM_512_BCAST        FCML_OP_MODRM_RM_ZMM_512 | \
    FCML_DECOR_BCAST


#define FCML_OP_MODRM_M_OP_64_K1_W           (FCML_OP_MODRM_M_OP_64_W | FCML_DECOR_K1)

#define FCML_OP_MODRM_RM_XMM_OP_16_K1_Z      \
    FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_XWORD, FCML_EOS_WORD | FCML_EOS_OPT, \
            FCML_RMF_RM) | FCML_DECOR_Z | FCML_DECOR_K1
#define FCML_OP_MODRM_RM_XMM_OP_16_K1_Z_W   (FCML_OP_MODRM_RM_XMM_OP_16_K1_Z | FCML_OA_W)

#define FCML_OP_MODRM_RM_XMM_OP_32_K1_Z      \
    FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_XWORD, FCML_EOS_DWORD | FCML_EOS_OPT, \
            FCML_RMF_RM) | FCML_DECOR_Z | FCML_DECOR_K1
#define FCML_OP_MODRM_RM_XMM_OP_32_K1_Z_W   (FCML_OP_MODRM_RM_XMM_OP_32_K1_Z | FCML_OA_W)

#define FCML_OP_MODRM_RM_XMM_OP_64_K1_Z      \
    FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_XWORD, FCML_EOS_QWORD | FCML_EOS_OPT, \
            FCML_RMF_RM) | FCML_DECOR_Z | FCML_DECOR_K1
#define FCML_OP_MODRM_RM_XMM_OP_64_K1_Z_W   (FCML_OP_MODRM_RM_XMM_OP_64_K1_Z | FCML_OA_W)

#define FCML_OP_MODRM_RM_XMM_OP_128_K1_Z      \
    FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_XWORD, FCML_EOS_XWORD | FCML_EOS_OPT, \
            FCML_RMF_RM) | FCML_DECOR_Z | FCML_DECOR_K1
#define FCML_OP_MODRM_RM_XMM_OP_128_K1_Z_W   (FCML_OP_MODRM_RM_XMM_OP_128_K1_Z | FCML_OA_W)

#define FCML_OP_MODRM_RM_XMM_OP_256_K1_Z      \
    FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_XWORD, FCML_EOS_YWORD | FCML_EOS_OPT, \
            FCML_RMF_RM) | FCML_DECOR_Z | FCML_DECOR_K1
#define FCML_OP_MODRM_RM_XMM_OP_256_K1_Z_W   (FCML_OP_MODRM_RM_XMM_OP_256_K1_Z | FCML_OA_W)

#define FCML_OP_MODRM_RM_YMM_OP_256_K1_Z      \
    FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_YWORD, FCML_EOS_YWORD | FCML_EOS_OPT, \
            FCML_RMF_RM) | FCML_DECOR_Z | FCML_DECOR_K1
#define FCML_OP_MODRM_RM_YMM_OP_256_K1_Z_W   (FCML_OP_MODRM_RM_YMM_OP_256_K1_Z | FCML_OA_W)

/* End of AVX-512 */

#define FCML_OP_MODRM_M_SIMD_L          \
    FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_UNDEFINED, FCML_EOS_L, FCML_RMF_M)
#define FCML_OP_MODRM_M_SIMD_L_W        (FCML_OP_MODRM_M_SIMD_L | FCML_OA_W)
#define FCML_OP_MODRM_M_SIMD_L_RW       (FCML_OP_MODRM_M_SIMD_L | FCML_OA_RW)

#define FCML_OP_MODRM_M_SIMD_E          \
    FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_UNDEFINED, FCML_EOS_EOSA, FCML_RMF_M)
#define FCML_OP_MODRM_M_SIMD_E_W        (FCML_OP_MODRM_M_SIMD | FCML_OA_W)
#define FCML_OP_MODRM_M_SIMD_E_RW       (FCML_OP_MODRM_M_SIMD | FCML_OA_RW)

#define FCML_OP_MODRM_M_SIMD_OPL        \
    FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_UNDEFINED, FCML_EOS_L | FCML_EOS_OPT, \
            FCML_RMF_M)
#define FCML_OP_MODRM_M_SIMD_OPL_W      (FCML_OP_MODRM_M_SIMD_OPL | FCML_OA_W)
#define FCML_OP_MODRM_M_SIMD_OPL_RW     (FCML_OP_MODRM_M_SIMD_OPL | FCML_OA_RW)

#define FCML_OP_MODRM_M_SIMD_OPE        \
    FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_UNDEFINED, FCML_EOS_EOSA | \
            FCML_EOS_OPT, FCML_RMF_M)
#define FCML_OP_MODRM_M_SIMD_OPE_W      (FCML_OP_MODRM_M_SIMD_OPE | FCML_OA_W)
#define FCML_OP_MODRM_M_SIMD_OPE_RW     (FCML_OP_MODRM_M_SIMD_OPE | FCML_OA_RW)

/* Shorthands for relative addressing.*/

#define FCML_OP_IMMEDIATE_DIS_RELATIVE_EOSA  \
    FCML_OP_IMMEDIATE_DIS_RELATIVE(FCML_EOS_UNDEFINED)
#define FCML_OP_IMMEDIATE_DIS_RELATIVE_R_8   \
    FCML_OP_IMMEDIATE_DIS_RELATIVE(FCML_EOS_BYTE)

/* Shorthands for VVVV addressing.*/

#define FCML_OP_VEX_VVVV_SIMD_REG       \
    FCML_OP_VEX_VVVV_REG(FCML_REG_SIMD, FCML_EOS_L)
#define FCML_OP_VEX_VVVV_XMM_REG        \
    FCML_OP_VEX_VVVV_REG(FCML_REG_SIMD, FCML_EOS_OWORD)
#define FCML_OP_VEX_VVVV_YMM_REG        \
    FCML_OP_VEX_VVVV_REG(FCML_REG_SIMD, FCML_EOS_YWORD)
#define FCML_OP_VEX_VVVV_ZMM_REG        \
    FCML_OP_VEX_VVVV_REG(FCML_REG_SIMD, FCML_EOS_ZWORD)
#define FCML_OP_VEX_VVVV_K_REG        \
    FCML_OP_VEX_VVVV_REG(FCML_REG_OPMASK, \
            FCML_EOS_QWORD | FCML_EOS_OPT)
#define FCML_OP_VEX_VVVV_SIMD_REG_K1_Z   \
    (FCML_OP_VEX_VVVV_SIMD_REG | \
            FCML_DECOR_Z | FCML_DECOR_K1)
#define FCML_OP_VEX_VVVV_SIMD_REG_K1_Z_W   \
    (FCML_OP_VEX_VVVV_SIMD_REG_K1_Z | FCML_OA_W)

/* Shorthands for IMM.*/

#define FCML_OP_IB           FCML_OP_IMM(FCML_EOS_BYTE, FCML_EOS_UNDEFINED)
#define FCML_OP_IB_EX_EOSA   FCML_OP_IMM(FCML_EOS_BYTE, FCML_EOS_EOSA)
#define FCML_OP_IW           FCML_OP_IMM(FCML_EOS_WORD, FCML_EOS_UNDEFINED)
#define FCML_OP_IW_EX_EOSA   FCML_OP_IMM(FCML_EOS_WORD, FCML_EOS_EOSA)
#define FCML_OP_ID           FCML_OP_IMM(FCML_EOS_DWORD, FCML_EOS_UNDEFINED)
/* its used only by MOV for imm64 */
#define FCML_OP_ID_EX_EOSA   FCML_OP_IMM(FCML_EOS_DWORD, FCML_EOS_EOSA)
#define FCML_OP_EX_EOSA      FCML_OP_IMM(FCML_EOS_EOSA, FCML_EOS_EOSA)
#define FCML_OP_IMM_EOSA     FCML_OP_IMM(FCML_EOS_EOSA, FCML_EOS_UNDEFINED)

/* Externals. */

extern struct fcml_st_def_instruction_desc fcml_ext_instructions_def[];

#define FCML_EMPTY_MNEMONIC    FCML_TEXT("")

/* Addressing modes arguments encoders. */

typedef struct fcml_st_def_decoded_addr_mode {
    /* Code of the addressing mode.*/
    fcml_uint8_t addr_mode;
    /* Operand access mode R, RW, W. */
    fcml_en_access_mode access_mode;
    /* Decoded arguments.*/
    fcml_ptr addr_mode_args;
} fcml_st_def_decoded_addr_mode;

fcml_ceh_error fcml_fn_def_decode_addr_mode_args(
        const fcml_operand_desc encoded_addr_mode,
        fcml_st_def_decoded_addr_mode **decoded_addr_mode);

void fcml_fnp_def_free_addr_mode(
        fcml_st_def_decoded_addr_mode *decoded_addr_mode);

/* Addressing modes arguments. */

#define FCML_GET_ADDR_MODE(x)     ( ( x ) & 0x3F000000 ) >> 24

typedef struct fcml_st_def_tma_imm {
    fcml_uint8_t encoded_size;
    fcml_uint8_t encoded_ex_size;
    fcml_bool is_64bit_imm_allowed;
} fcml_st_def_tma_imm;

typedef struct fcml_st_def_tma_explicit_reg {
    fcml_uint8_t reg_type;
    fcml_uint8_t reg_num;
    fcml_uint8_t encoded_reg_size;
} fcml_st_def_tma_explicit_reg;

typedef struct fcml_st_def_tma_opcode_reg {
    fcml_uint8_t reg_type;
    fcml_uint8_t encoded_reg_size;
} fcml_st_def_tma_opcode_reg;

typedef struct fcml_st_def_tma_immediate_dis_relative {
    fcml_uint8_t encoded_size;
} fcml_sf_def_tma_immediate_dis_relative;

typedef struct fcml_st_def_tma_explicit_gps_reg_addressing {
    fcml_uint8_t reg_num;
    fcml_uint8_t encoded_operand_size;
    fcml_uint8_t encoded_segment_register;
} fcml_st_def_tma_explicit_gps_reg_addressing;

typedef struct fcml_st_def_tma_explicit_ib {
    fcml_uint8_t ib;
} fcml_st_def_tma_explicit_ib;

typedef struct fcml_st_def_tma_segment_relative_offset {
    fcml_uint8_t encoded_operand_size;
    fcml_uint8_t encoded_segment_register;
} fcml_st_def_tma_segment_relative_offset;

typedef struct fcml_st_def_tma_rm {
    fcml_uint8_t reg_type;
    fcml_uint8_t encoded_register_operand_size;
    fcml_uint8_t encoded_memory_operand_size;
    fcml_uint8_t flags;
    fcml_uint8_t vector_index_register;
    fcml_bool is_vsib;
    fcml_bool is_bcast;
} fcml_st_def_tma_rm;

typedef struct fcml_st_def_tma_r {
    fcml_en_register reg_type;
    fcml_uint8_t encoded_register_operand_size;
    fcml_operand_decorators decorators;
} fcml_st_def_tma_r;

typedef struct fcml_st_def_tma_vex_vvvv_reg {
    fcml_uint8_t reg_type;
    fcml_uint8_t encoded_register_size;
} fcml_st_def_tma_vex_vvvv_reg;

typedef struct fcml_st_def_tma_pseudo_op {
    fcml_uint8_t mask;
} fcml_st_def_tma_pseudo_op;

typedef struct fcml_st_def_tma_virtual_op {
    fcml_operand_decorators decorators;
} fcml_st_def_tma_virtual_op;

typedef struct fcml_st_def_tma_is {
    fcml_uint8_t flags;
} fcml_st_def_tma_is;

#endif /* FCML_DEF_H_ */
