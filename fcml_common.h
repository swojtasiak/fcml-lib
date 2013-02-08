/*
 * fcml_int_common.h
 *
 *  Created on: 04-02-2013
 *      Author: tAs
 */

#ifndef FCML_INT_COMMON_H_
#define FCML_INT_COMMON_H_

#define FCML_DS_8    8
#define FCML_DS_16   16
#define FCML_DS_32   32
#define FCML_DS_64   64

typedef enum fcml_en_register {
    FCML_REG_NONE = 0,
    FCML_REG_GPR,
    FCML_REG_SIMD,
    FCML_REG_FPU,
    FCML_REG_SEG,
    FCML_REG_CR,
    FCML_REG_DR,
} fcml_en_register;

typedef struct fcml_st_register {
    fcml_en_register type;
    uint8_t size;
    uint8_t reg;
} fcml_st_register;

typedef struct fcml_st_immediate {
    uint8_t imm_size;
    union {
        uint8_t imm8;
        uint16_t imm16;
        uint32_t imm32;
        uint64_t imm64;
    };
} fcml_st_immediate;

typedef struct fcml_st_far_pointer {
    uint16_t segment;
    uint8_t offset_size;
    union {
        uint16_t offset16;
        uint32_t offset32;
    };
} fcml_st_far_pointer;

typedef struct fcml_st_displacement {
    uint8_t size;
    uint8_t sign_extension;
    union {
        uint8_t dis8;
        uint8_t dis16;
        uint8_t dis32;
    };
} fcml_st_displacement;

typedef struct fcml_st_effective_address {
    fcml_st_register base;
    fcml_st_register index;
    uint8_t scale_factor;
    fcml_st_displacement displacement;
} fcml_st_effective_address;

typedef struct fcml_st_offset {
    uint8_t size;
    union {
        uint16_t off16;
        uint32_t off32;
        uint64_t off64;
    };
} fcml_st_offset;

typedef enum fcml_en_operand_type {
    FCML_EOT_IMMEDIATE,
    FCML_EOT_FAR_POINTER,
    FCML_EOT_EFFECTIVE_ADDRESS,
    FCML_EOT_OFFSET,
    FCML_EOT_REGISTER
} fcml_en_operand_type;

typedef struct fcml_st_operand {
    fcml_en_operand_type type;
    fcml_st_immediate immediate;
    fcml_st_far_pointer far_pointer;
    fcml_st_effective_address effective_address;
    fcml_st_offset offset;
    fcml_st_register reg;
} fcml_st_operand;

#endif /* FCML_INT_COMMON_H_ */
