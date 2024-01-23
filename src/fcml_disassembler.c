/*
 * FCML - Free Code Manipulation Library.
 * Copyright (C) 2010-2024 Slawomir Wojtasiak
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

#include "fcml_disassembler.h"

#include <stddef.h>

#include <fcml_errors.h>

#include "fcml_coll.h"
#include "fcml_decoding_tree.h"
#include "fcml_def.h"
#include "fcml_env_int.h"
#include "fcml_hints.h"
#include "fcml_mnemonic_parser.h"
#include "fcml_modrm.h"
#include "fcml_modrm_decoder.h"
#include "fcml_stream.h"
#include "fcml_utils.h"
#include "fcml_dialect_int.h"
#include "fcml_trace.h"
#include "fcml_messages.h"
#include "fcml_operand_decorators.h"
#include "fcml_trace.h"

/* R,X and B are stored in 1's complement form.*/
#define FCML_VEX_W(x)                FCML_TP_GET_BIT(x, 7)
#define FCML_VEX_R(x)                !FCML_TP_GET_BIT(x, 7)
#define FCML_VEX_X(x)                !FCML_TP_GET_BIT(x, 6)
#define FCML_VEX_B(x)                !FCML_TP_GET_BIT(x, 5)
#define FCML_VEX_L(x)                FCML_TP_GET_BIT(x, 2)
#define FCML_VEX_MMMM(x)             (x & 0x1F)
#define FCML_VEX_VVVV(x)             (~((x & 0x78) >> 3) & 0x00F)
#define FCML_VEX_PP(x)               (x & 0x03)

/* EVEX prefix fields. */
#define FCML_EVEX_R(x)               !FCML_TP_GET_BIT(x, 7)
#define FCML_EVEX_X(x)               !FCML_TP_GET_BIT(x, 6)
#define FCML_EVEX_B(x)               !FCML_TP_GET_BIT(x, 5)
#define FCML_EVEX_R_PRIM(x)          !FCML_TP_GET_BIT(x, 4)
#define FCML_EVEX_MM(x)              (x & 0x03)
#define FCML_EVEX_W(x)               FCML_TP_GET_BIT(x, 7)
#define FCML_EVEX_VVVV(x)            FCML_VEX_VVVV(x)
#define FCML_EVEX_PP(x)              (x & 0x03)
#define FCML_EVEX_z(x)               FCML_TP_GET_BIT(x, 7)
#define FCML_EVEX_L_PRIM(x)          FCML_TP_GET_BIT(x, 6)
#define FCML_EVEX_L(x)               FCML_TP_GET_BIT(x, 5)
#define FCML_EVEX_b(x)               FCML_TP_GET_BIT(x, 4)
#define FCML_EVEX_V_PRIM(x)          !FCML_TP_GET_BIT(x, 3)
#define FCML_EVEX_aaa(x)             (x & 0x07)

/* REX prefix fields.*/
#define FCML_REX_W(x)                FCML_TP_GET_BIT(x, 3)
#define FCML_REX_R(x)                FCML_TP_GET_BIT(x, 2)
#define FCML_REX_X(x)                FCML_TP_GET_BIT(x, 1)
#define FCML_REX_B(x)                FCML_TP_GET_BIT(x, 0)

typedef struct operand_wrapper {
    fcml_st_operand operand;
    fcml_en_access_mode access_mode;
} operand_wrapper;

/* Definition is located below.*/
struct inst_decoding_def;

typedef struct decoding_context {
    fcml_st_disassembler_context *disassembler_context;
    fcml_st_ceh_error_container errors;
    fcml_st_memory_stream *stream;
    fcml_st_mp_mnemonic_set *mnemonics;
    fcml_en_pseudo_operations pseudo_op;
    fcml_uint64_t instruction_group;
    fcml_en_instruction instruction;
    fcml_uint16_t addr_mode;
    fcml_usize effective_address_size_attribute;
    fcml_usize effective_operand_size_attribute;
    /* Size of SIMD element. */
    fcml_usize element_size;
    /* Size of SIMD vector length calculated basing on EVEX.L'L/VEX.L/XOP.L */
    fcml_usize vector_length;
    fcml_int calculated_instruction_size;
    fcml_uint8_t opcodes[FCML_OPCODES_NUM];
    fcml_uint8_t primary_opcode_byte;
    fcml_int opcodes_count;
    fcml_int virtual_opcodes_count;
    fcml_st_prefixes_details prefixes;
    operand_wrapper operand_wrappers[FCML_OPERANDS_COUNT];
    fcml_st_modrm decoded_modrm;
    fcml_st_modrm_details decoded_modrm_details;
    /* True if ModR/M is available for instruction. */
    fcml_bool is_modrm;
    /* True if ModR/M is used by register to register operation. */
    fcml_bool is_modrm_reg_reg;
    fcml_hints instruction_hints;
    fcml_nuint8_t pseudo_opcode;
    fcml_nuint8_t suffix;
    /* Opcode fields.*/
    fcml_st_condition condition;
    fcml_bool is_conditional;
    fcml_bool opcode_field_w_bit;
    fcml_bool opcode_field_s_bit;
    /* is4/is5 byte.*/
    fcml_nuint8_t isX_byte;
    /* Instruction tuple type used to calculate disp8 */
    fcml_uint8_t tuple_type;
    /* Currently proceeded decoding definition.*/
    struct inst_decoding_def *decoding_def;
} decoding_context;

typedef struct disassembler {
    fcml_st_dialect_context_int *dialect_context;
    fcml_st_dt_decoding_tree *decoding_tree;
} disassembler;

/* Decoders responsible for operand disassembling. */
typedef fcml_ceh_error (*operand_decoder)(struct decoding_context *context,
        operand_wrapper *operand, fcml_operand_decorators decorators,
        fcml_ptr args);

/* Calculates the size of the encoded operand in bytes. */
typedef fcml_int (*operand_size_calculator)(struct decoding_context *context,
        fcml_ptr args);

/* Decoders responsible for instruction disassembling. */
typedef fcml_ceh_error (*instruction_decoder)(decoding_context *context);

typedef fcml_bool (*instruction_acceptor)(decoding_context *context);

typedef struct addr_mode_acceptor_chain {
    struct addr_mode_acceptor_chain *next;
    fcml_string name;
    instruction_acceptor acceptor;
} addr_mode_acceptor_chain;

typedef struct operand_decoding {
    /* Operand access mode. */
    fcml_st_def_decoded_addr_mode *decoded_addr_mode;
    /* Operand decoder. */
    operand_decoder decoder;
    /* Calculates size of the encoded operand in bytes. */
    operand_size_calculator size_calculator;
    /* Optional hints, if operand has any. */
    fcml_hints hints;
    /* Operand decorators. */
    fcml_operand_decorators decorators;
} operand_decoding;

typedef struct modrm_decoding_details {
    /* True if vector-index memory addressing is used. */
    fcml_bool is_vsib;
    /* Vector register size. */
    fcml_usize vsib_index_size;
    /* True if addressing mode is restricted only to register. */
    fcml_bool is_reg_restriction;
    /* True if addressing mode is restricted only to memory. */
    fcml_bool is_mem_restriction;
} modrm_decoding_details;

typedef struct inst_decoding_def {
    /* Instruction code. */
    fcml_en_instruction instruction;
    /* Addressing mode.*/
    fcml_uint16_t addr_mode;
    /* Additional details for addressing mode. */
    fcml_uint32_t details;
    /* Type of the instruction. */
    fcml_uint64_t instruction_group;
    /* Opcodes. */
    fcml_uint8_t opcodes[FCML_OPCODES_NUM];
    /* Instruction mnemonic. */
    fcml_st_mp_mnemonic_set *mnemonics;
    /* Flags that describe prefixes usage. */
    fcml_uint32_t prefixes_flags;
    /* Flags that describe some details of opcodes. */
    fcml_uint32_t opcode_flags;
    /* Instruction decoder. */
    instruction_decoder instruction_decoder;
    /* Chain of address mode acceptors registered for given addressing mode. */
    addr_mode_acceptor_chain *instruction_acceptors_chain;
    /* Function used to decode instruction operands. */
    operand_decoding operand_decodings[FCML_OPERANDS_COUNT];
    /* Instruction decoding order, for information purpose only. */
    fcml_int order;
    /* Instruction level hints. */
    fcml_hints hints;
    /* ModRM details. */
    modrm_decoding_details modrm_details;
    /* Decorators existence. */
    fcml_st_decorators_existence decorators_existence;
} inst_decoding_def;

/* Instruction decoder for IA instruction set, currently it is the only 
 * one supported decoder.
 */
static fcml_ceh_error instruction_decoder_IA(
        decoding_context *decoding_context);

/*********************
 * Utility functions.
 *********************/

static void set_x64_exp(fcml_st_register *reg, fcml_bool is_rex) {
    if (is_rex) {
        reg->x64_exp = (reg->type == FCML_REG_GPR && reg->size == FCML_DS_8 
                && reg->reg >= 4 && reg->reg <= 7);
    } else {
        reg->x64_exp = FCML_FALSE;
    }
}

static void set_segment_selector(fcml_st_segment_selector *seg_sel,
        fcml_uint8_t seg_reg, fcml_bool is_default) {
    seg_sel->is_default_reg = is_default;
    fcml_st_register *reg_seg = &(seg_sel->segment_selector);
    reg_seg->reg = seg_reg;
    reg_seg->size = FCML_DS_16;
    reg_seg->type = FCML_REG_SEG;
    reg_seg->x64_exp = FCML_FALSE;
}

static fcml_uint8_t override_segment_reg(decoding_context *context,
        fcml_uint8_t reg) {
    for (int i = 0; i < context->prefixes.prefixes_count; i++) {
        fcml_st_instruction_prefix *prefix = &(context->prefixes.prefixes[i]);
        if (prefix->prefix_type == FCML_PT_GROUP_2 
                && !prefix->mandatory_prefix) {
            switch (prefix->prefix) {
            case 0x2E:
                reg = FCML_REG_CS;
                break;
            case 0x36:
                reg = FCML_REG_SS;
                break;
            case 0x3E:
                reg = FCML_REG_DS;
                break;
            case 0x26:
                reg = FCML_REG_ES;
                break;
            case 0x64:
                reg = FCML_REG_FS;
                break;
            case 0x65:
                reg = FCML_REG_GS;
                break;
            }
        }
    }
    return reg;
}

static fcml_ceh_error decode_segment_selector(decoding_context *context,
        fcml_st_segment_selector *selector, fcml_uint8_t encoded_segment_reg) {
    fcml_uint8_t seg_reg = ~FCML_SEG_ALLOW_OVERRIDE & encoded_segment_reg;
    if (encoded_segment_reg & FCML_SEG_ALLOW_OVERRIDE) {
        fcml_uint8_t tmp = seg_reg;
        seg_reg = override_segment_reg(context, seg_reg);
        selector->is_default_reg = (seg_reg == tmp);
    } else {
        selector->is_default_reg = FCML_TRUE;
    }
    selector->segment_selector.reg = seg_reg;
    selector->segment_selector.size = FCML_DS_16;
    selector->segment_selector.type = FCML_REG_SEG;
    selector->segment_selector.x64_exp = FCML_FALSE;
    return FCML_CEH_GEC_NO_ERROR;
}

static fcml_usize calculate_vector_length(fcml_uint8_t tuple_type,
        fcml_bool sae_enabled, fcml_uint8_t encoded_vector_length) {
    fcml_usize vector_length = 0;
    if (sae_enabled) {
        /* Vector length is assumed to be 512-bit in case of AVX-512 packed
         * vector instructions or 128-bit for scalar instructions.
         */
        if (tuple_type == FCML_TT_T1S || tuple_type == FCML_TT_T1F) {
            /* SIMD scalar instructions. */
            vector_length = FCML_DS_128;
        } else {
            vector_length = FCML_DS_512;
        }
    } else {
        switch (encoded_vector_length) {
        case 0:
            vector_length = FCML_DS_128;
        break;
        case 1:
            vector_length = FCML_DS_256;
        break;
        case 2:
            vector_length = FCML_DS_512;
        break;
        }
    }
    return vector_length;
};

static fcml_usize decode_encoded_size_value(
        decoding_context *context, fcml_uint8_t encoded_size) {
    fcml_usize result = 0;
    /* Extracts size explicitly encoded in the encoded operand size. */
    fcml_uint8_t size = (encoded_size & ~FCML_EOS_OPT);
    if (FCML_IS_EOS_DYNAMIC(size)) {
        switch (size) {
        case FCML_EOS_EOSA:
            result = context->effective_operand_size_attribute;
            break;
        case FCML_EOS_EASA:
            result = context->effective_address_size_attribute;
            break;
        case FCML_EOS_L:
            result = context->vector_length;
            break;
        case FCML_EOS_14_28:
            result = (context->effective_operand_size_attribute == FCML_DS_16) 
                ? (14 * 8) : (28 * 8);
            break;
        case FCML_EOS_94_108:
            result = (context->effective_operand_size_attribute == FCML_DS_16) 
                ? (94 * 8) : (108 * 8);
            break;
        case FCML_EOS_32_64:
            result = (context->effective_operand_size_attribute == FCML_DS_16) 
                ? (16 * 2) : (32 * 2);
            break;
        case FCML_EOS_FP:
        case FCML_EOS_FPI:
            result = context->effective_operand_size_attribute + 16;
            break;
        }
    } else {
        result = size * 8;
    }
    return result;
}

/***********************************
 * Decoding tree related functions.
 ***********************************/

static int calculate_decoding_order(inst_decoding_def *decoding) {

    fcml_uint32_t prefixes = decoding->prefixes_flags;
    fcml_uint32_t opcodes = decoding->opcode_flags;

    int order = 0;

    /* Mandatory prefix. */
    if (FCML_DEF_PREFIX_MANDATORY_66(prefixes) 
            | FCML_DEF_PREFIX_MANDATORY_F2(prefixes) 
            | FCML_DEF_PREFIX_MANDATORY_F3(prefixes)) {
        order += 3;
    }

    /* Opcode extension. */
    if (FCML_DEF_OPCODE_FLAGS_OPCODE_IS_EXT(opcodes)) {
        order++;
    }

    /* VEX, XOP and EVEX prefixes. */
    if (FCML_DEF_PREFIX_IS_AVX_REQ(prefixes)) {
        order++;
    }

    /* REX/VEX/EVEX prefix. */
    if (FCML_DEF_PREFIX_W_1(prefixes) 
            || FCML_DEF_PREFIX_W_0(prefixes) 
            || FCML_DEF_PREFIX_L_1(prefixes) 
            || FCML_DEF_PREFIX_L_0(prefixes)
            || FCML_DEF_PREFIX_L_prim_1(prefixes)
            || FCML_DEF_PREFIX_L_prim_0(prefixes)) {
        order += 2;
    }

    return order;
}

static instruction_decoder choose_instruction_decoder(
        fcml_uint8_t instruction_type) {
    switch (instruction_type) {
    case FCML_EN_IT_IA:
        /* Currently only IA decoder is supported. */
        return &instruction_decoder_IA;
    }
    return NULL;
}

/***********************/
/** Operand decoders. **/
/***********************/

/********************/
/* Immediate value. */
/********************/

static fcml_ceh_error operand_decoder_imm(decoding_context *context,
        operand_wrapper *operand_wrapper, fcml_operand_decorators decorators,
        fcml_ptr args) {

    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

    fcml_st_def_tma_imm *imm_args = (fcml_st_def_tma_imm *) args;
    fcml_st_operand *operand = &(operand_wrapper->operand);
    fcml_st_integer *immediate = &(operand->immediate);
    fcml_st_memory_stream *stream = context->stream;

    operand->type = FCML_OT_IMMEDIATE;

    fcml_usize size = decode_encoded_size_value(
            context, imm_args->encoded_size);

    /* Correct calculated IMM size if 64 bit IMM is not supported 
     * by addressing mode.
     */
    if (size == FCML_DS_64 && !imm_args->is_64bit_imm_allowed) {
        size = FCML_DS_32;
    }

    fcml_usize size_ex = decode_encoded_size_value(context,
            imm_args->encoded_ex_size);
    if (size_ex == FCML_DS_UNDEF) {
        /* check if S opcode field is set.*/
        if (size == FCML_DS_8 && context->opcode_field_s_bit) {
            size_ex = context->effective_operand_size_attribute;
        } else {
            size_ex = size;
        }
    }

    /* All immediate integers are signed.*/
    immediate->is_signed = FCML_TRUE;

    error = fcml_fn_utils_decode_integer(stream, immediate, size);
    if (error) {
        return error;
    }

    if (size_ex != size) {
        error = fcml_fn_utils_conv_int_to_int(immediate, immediate, 
                size, size_ex);
        if (error) {
            return error;
        }
    }

    return error;
}

static fcml_int operand_size_calculator_imm(decoding_context *context,
        fcml_ptr args) {
    fcml_st_def_tma_imm *imm_args = (fcml_st_def_tma_imm *) args;
    fcml_int size = decode_encoded_size_value(context, 
            imm_args->encoded_size) / 8;
    /* 8 bytes IMM size is only supported for instructions with 
     * following flag set.
     */
    if (size == 8 && !imm_args->is_64bit_imm_allowed) {
        size = 4;
    }
    return size;
}

/**********************/
/* Explicit register. */
/**********************/

static fcml_ceh_error operand_decoder_explicit_reg(decoding_context *context,
        operand_wrapper *operand_wrapper, fcml_operand_decorators decorators,
        fcml_ptr args) {

    fcml_st_operand *operand = &(operand_wrapper->operand);
    fcml_st_def_tma_explicit_reg *reg_args = 
        (fcml_st_def_tma_explicit_reg*)args;

    operand->type = FCML_OT_REGISTER;
    operand->reg.reg = reg_args->reg_num;
    operand->reg.type = (fcml_en_register) reg_args->reg_type;
    operand->reg.size = decode_encoded_size_value(context,
            reg_args->encoded_reg_size);

    return FCML_CEH_GEC_NO_ERROR;
}

/**************************************/
/* Explicit register base addressing. */
/**************************************/

static fcml_ceh_error operand_decoder_explicit_gps_reg_addressing(
        decoding_context *context, operand_wrapper *operand_wrapper,
        fcml_operand_decorators decorators, fcml_ptr args) {

    fcml_st_operand *operand = &(operand_wrapper->operand);
    fcml_st_address *address = &(operand->address);
    fcml_st_effective_address *effective_address = 
        &(address->effective_address);

    operand->type = FCML_OT_ADDRESS;
    address->address_form = FCML_AF_COMBINED;

    fcml_st_def_tma_explicit_gps_reg_addressing *reg_addr_args = 
        (fcml_st_def_tma_explicit_gps_reg_addressing*)args;

    /* Size operator.*/
    address->size_operator = decode_encoded_size_value(
            context, reg_addr_args->encoded_operand_size);

    /* Base register.*/
    effective_address->base.size = context->effective_address_size_attribute;
    effective_address->base.reg = reg_addr_args->reg_num;
    effective_address->base.type = FCML_REG_GPR;

    /* Segment register.*/
    return decode_segment_selector(context,
            &(address->segment_selector), 
            reg_addr_args->encoded_segment_register);
}

/********************/
/* Opcode register. */
/********************/

static fcml_ceh_error operand_decoder_opcode_reg(
        decoding_context *context, operand_wrapper *operand_wrapper,
        fcml_operand_decorators decorators, fcml_ptr args) {

    fcml_st_def_tma_opcode_reg *reg_args = (fcml_st_def_tma_opcode_reg*) args;
    fcml_uint8_t reg_num = context->primary_opcode_byte & 0x07;

    if (context->prefixes.B) {
        reg_num |= 0x08;
    }

    /* Size operator.*/
    operand_wrapper->operand.type = FCML_OT_REGISTER;
    fcml_st_register *reg = &(operand_wrapper->operand.reg);

    /* Base register.*/
    reg->size = decode_encoded_size_value(context, 
            reg_args->encoded_reg_size);
    reg->type = (fcml_en_register) reg_args->reg_type;
    reg->reg = reg_num;

    return FCML_CEH_GEC_NO_ERROR;
}

/************************************/
/* Immediate displacement relative. */
/************************************/

static fcml_ceh_error operand_decoder_immediate_dis_relative(
        decoding_context *context,  operand_wrapper *operand_wrapper,
        fcml_operand_decorators decorators, fcml_ptr args) {

    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
    fcml_sf_def_tma_immediate_dis_relative *rel_args = 
        (fcml_sf_def_tma_immediate_dis_relative*)args;
    fcml_usize int_size = 0;
    fcml_int32_t offset32;
    fcml_int16_t offset16;

    // Just in case.
    if (FCML_IS_EOS_DYNAMIC(rel_args->encoded_size)) {
        FCML_TRACE_MSG("Currently dynamically calculated IMM size is \
                not supported here.");
        return FCML_CEH_GEC_INTERNAL_ERROR;
    }

    fcml_st_entry_point *entry_point = 
        &(context->disassembler_context->entry_point);

    if (rel_args->encoded_size != FCML_EOS_UNDEFINED) {
        int_size = rel_args->encoded_size * 8;
    } else {

        if (context->effective_operand_size_attribute == FCML_DS_16 
                && entry_point->op_mode == FCML_OM_64_BIT) {
            fcml_fn_ceh_add_error(&(context->errors), 
                    fcml_fn_msg_get_message(
                        FCML_MC_CEH_GEC_INVALID_ADDRESSING_MODE),
                    FCML_CEH_MEW_WARN_INVALID_ADDRESSING_MODE, 
                    FCML_EN_CEH_EL_WARN);
        }

        int_size = FCML_DS_32;

        /* For 32 and 64 bit addressing, 32 bit immediate value should be
         * used. Only for 16 bit addressing value differs and is 
         * equal to 16. 
         */
        if (context->effective_operand_size_attribute == FCML_DS_16) {
            int_size = FCML_DS_16;
        }

    }

    fcml_st_integer integer;
    integer.is_signed = FCML_TRUE;

    /* Read displacement value from stream.*/
    error = fcml_fn_utils_decode_integer(context->stream, &integer, int_size);
    if (error) {
        return error;
    }

    operand_wrapper->operand.type = FCML_OT_ADDRESS;
    operand_wrapper->operand.address.address_form = FCML_AF_OFFSET;

    fcml_st_offset *offset = &(operand_wrapper->operand.address.offset);
    offset->is_signed = FCML_TRUE;

    /* Calculate offset relative to IP.*/
    fcml_ip ip = entry_point->ip;

    switch (context->effective_operand_size_attribute) {
    case FCML_DS_16:
        error = fcml_fn_utils_conv_int_to_int16(&integer, &offset16);
        if (!error) {
            offset->off16 = ((fcml_int32_t) ip + 
                    context->calculated_instruction_size + offset16) 
                & 0x0000FFFF;
            offset->size = FCML_DS_16;
        }
        break;
    case FCML_DS_32:
        error = fcml_fn_utils_conv_int_to_int32(&integer, &offset32);
        if (!error) {
            offset->off32 = ((fcml_int32_t) ip + 
                    context->calculated_instruction_size + offset32);
            offset->size = FCML_DS_32;
        }
        break;
    case FCML_DS_64:
        error = fcml_fn_utils_conv_int_to_int32(&integer, &offset32);
        if (!error) {
            offset->off64 = ((fcml_int64_t)ip + 
                    context->calculated_instruction_size + offset32);
            offset->size = FCML_DS_64;
        }
        break;
    }

    /* Sets CS segment register.*/
    set_segment_selector(
            &(operand_wrapper->operand.address.segment_selector), FCML_REG_CS,
            FCML_TRUE);

    return error;
}

static fcml_int operand_size_calculator_imm_dis_rel(decoding_context *context,
        fcml_ptr args) {
    fcml_sf_def_tma_immediate_dis_relative *rel_args = 
        (fcml_sf_def_tma_immediate_dis_relative*)args;
    fcml_int size;
    if (rel_args->encoded_size != FCML_EOS_UNDEFINED) {
        size = rel_args->encoded_size;
    } else {
        size = (context->effective_operand_size_attribute == FCML_DS_16) 
            ? FCML_DS_16 / 8 : FCML_DS_32 / 8;
    }
    return size;
}

/***************/
/* Far pointer */
/***************/

static fcml_ceh_error operand_decoder_far_pointer(decoding_context *context,
        operand_wrapper *operand_wrapper, fcml_operand_decorators decorators,
        fcml_ptr args) {

    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
    fcml_st_operand *operand = &(operand_wrapper->operand);
    fcml_st_far_pointer *far_pointer = &(operand->far_pointer);
    fcml_bool result;

    operand->type = FCML_OT_FAR_POINTER;

    switch (context->effective_operand_size_attribute) {
    case FCML_DS_16:
        far_pointer->offset16 = (fcml_int16_t)fcml_fn_stream_read_word(
                context->stream, &result);
        break;
    case FCML_DS_32:
        far_pointer->offset32 = (fcml_int32_t)fcml_fn_stream_read_dword(
                context->stream, &result);
        break;
    default:
        error = FCML_CEH_GEC_INVALID_OPERATING_MODE;
        break;
    }

    far_pointer->offset_size = context->effective_operand_size_attribute;

    far_pointer->segment = fcml_fn_stream_read_word(context->stream, &result);
    if (!result) {
        return FCML_CEH_GEC_EOF;
    }

    if (!result) {
        error = FCML_CEH_GEC_EOF;
    }

    return error;
}

static fcml_int operand_size_calculator_far_pointer(decoding_context *context,
        fcml_ptr args) {
    return context->effective_operand_size_attribute / 8 + 2;
}

/****************************/
/* Explicit 8-bits integer. */
/****************************/

static fcml_ceh_error operand_decoder_explicit_ib(
        decoding_context *context, operand_wrapper *operand_wrapper,
        fcml_operand_decorators decorators, fcml_ptr args) {

    fcml_st_def_tma_explicit_ib *imm_args = (fcml_st_def_tma_explicit_ib*)args;

    fcml_st_operand *operand = &(operand_wrapper->operand);
    fcml_st_integer *immediate = &(operand->immediate);

    operand->type = FCML_OT_IMMEDIATE;
    immediate->is_signed = FCML_TRUE;
    immediate->size = FCML_DS_8;
    immediate->int8 = imm_args->ib;

    return FCML_CEH_GEC_NO_ERROR;
}

/***************************/
/* Segment relative offset */
/***************************/

static fcml_ceh_error operand_decoder_segment_relative_offset(
        decoding_context *context,  operand_wrapper *operand_wrapper,
        fcml_operand_decorators decorators, fcml_ptr args) {

    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

    fcml_st_def_tma_segment_relative_offset *seg_args = 
        (fcml_st_def_tma_segment_relative_offset*)args;

    fcml_st_operand *operand = &(operand_wrapper->operand);
    fcml_st_address *address = &(operand->address);
    fcml_st_offset *offset = &(address->offset);

    fcml_bool result;

    error = decode_segment_selector(context, 
            &(address->segment_selector), seg_args->encoded_segment_register);
    if (error) {
        return error;
    }

    address->size_operator = decode_encoded_size_value(
            context, seg_args->encoded_operand_size);
    address->address_form = FCML_AF_OFFSET;

    operand->type = FCML_OT_ADDRESS;

    switch (context->effective_address_size_attribute) {
    case FCML_DS_16:
        offset->off16 = fcml_fn_stream_read_word(context->stream, &result);
        break;
    case FCML_DS_32:
        offset->off32 = fcml_fn_stream_read_dword(context->stream, &result);
        break;
    case FCML_DS_64:
        offset->off64 = fcml_fn_stream_read_qword(context->stream, &result);
        break;
    default:
        error = FCML_CEH_GEC_INVALID_OPERATING_MODE;
        break;
    }

    offset->size = context->effective_address_size_attribute;

    if (!result) {
        error = FCML_CEH_GEC_EOF;
    }

    return error;
}

static fcml_int operand_size_calculator_seg_rel_offset(
        decoding_context *context, fcml_ptr args) {
    return context->effective_address_size_attribute / 8;
}

/**************/
/* ModRM - RM */
/**************/

static fcml_ceh_error operand_decoder_rm(decoding_context *context,
        operand_wrapper *operand_wrapper, fcml_operand_decorators decorators,
        fcml_ptr args) {

    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

    fcml_st_modrm *decoded_modrm = &(context->decoded_modrm);
    fcml_st_operand *operand = &(operand_wrapper->operand);

    fcml_st_def_tma_rm *rm_args = (fcml_st_def_tma_rm*) args;

    if ((rm_args->flags & FCML_RMF_R) && decoded_modrm->reg.is_not_null) {

        operand->type = FCML_OT_REGISTER;
        operand->reg.reg = decoded_modrm->reg.value;
        operand->reg.type = (fcml_en_register) rm_args->reg_type;
        operand->reg.size = decode_encoded_size_value(
                context, rm_args->encoded_register_operand_size);

        set_x64_exp(&(operand->reg),
                context->prefixes.is_rex);

    } else if (rm_args->flags & FCML_RMF_M) {

        operand->type = FCML_OT_ADDRESS;

        fcml_st_address *address = &(operand->address);
        *address = decoded_modrm->address;

        address->size_operator = decode_encoded_size_value(
                context, rm_args->encoded_memory_operand_size);

        /* If AVX-512 broadcast is used, use size operator from broadcast
         * instead of the one directly encoded in ModR/M.
         */
        if (FCML_IS_DECOR_BCAST(decorators) && context->prefixes.b) {
            /* Directly encoded bcast size has precedence over 
               SIMD element size. */
            operand->decorators.bcast.is_not_null = FCML_TRUE;
            operand->decorators.bcast.value = address->size_operator /
                    context->element_size;
            address->size_operator = context->element_size;
        }

        if (decoded_modrm->is_rip) {
            /* We known the instruction size, so post processing is not needed
             * and RIP can be calculated now.
             */
            error = fcml_fn_modrm_decode_rip((fcml_uint64_t)
                    context->disassembler_context->entry_point.ip + 
                        context->calculated_instruction_size,
                    context->effective_address_size_attribute, 
                    &(address->offset), &(address->offset));
        }

        /* Segment registers.*/

        fcml_st_effective_address *effective_address = 
            &(address->effective_address);
        fcml_st_segment_selector *segment_selector = 
            &(address->segment_selector);

        segment_selector->segment_selector.type = FCML_REG_SEG;
        segment_selector->segment_selector.size = FCML_DS_16;

        if (context->decoding_def->instruction_group & FCML_AMT_BRANCH) {
            /* For all branches only CS segment register is used. 
             * Segment override prefixes are ignored in this case.
             */
            segment_selector->segment_selector.reg = FCML_REG_CS;
            segment_selector->is_default_reg = FCML_TRUE;
        } else {
            if (effective_address->base.type == FCML_REG_GPR
                    && (effective_address->base.reg == FCML_REG_BP 
                        || effective_address->base.reg == FCML_REG_SP)) {
                segment_selector->segment_selector.reg = FCML_REG_SS;
                segment_selector->is_default_reg = FCML_TRUE;
            } else {
                segment_selector->segment_selector.reg = 
                    override_segment_reg(context,
                            FCML_REG_DS);
                segment_selector->is_default_reg = 
                    (segment_selector->segment_selector.reg == FCML_REG_DS) 
                    ? FCML_TRUE : FCML_FALSE;
            }
        }

        /* These hints aren't used in 32 bit addressing mode.*/
        if ((context->disassembler_context->entry_point.op_mode 
                    == FCML_OM_64_BIT) 
                && (address->address_form == FCML_AF_OFFSET)) {
            operand->hints |= context->decoded_modrm.is_rip 
                ? FCML_OP_HINT_RELATIVE_ADDRESSING 
                : FCML_OP_HINT_ABSOLUTE_ADDRESSING;
        }

    } else {
        error = FCML_CEH_GEC_INVALID_ADDRESSING_FORM;
    }

    return error;
}

/*************/
/* ModRM - R */
/*************/

static fcml_ceh_error operand_decoder_r(decoding_context *context,
        operand_wrapper *operand_wrapper, fcml_operand_decorators decorators,
        fcml_ptr args) {

    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
    fcml_st_def_tma_r *r_args = (fcml_st_def_tma_r*) args;

    operand_wrapper->operand.type = FCML_OT_REGISTER;
    fcml_st_register *reg = &(operand_wrapper->operand.reg);

    reg->reg = context->decoded_modrm.reg_opcode;
    reg->type = r_args->reg_type;
    reg->size = decode_encoded_size_value(context,
            r_args->encoded_register_operand_size);

    set_x64_exp(reg, context->prefixes.is_rex);

    return error;
}

/********/
/* VVVV */
/********/

static fcml_ceh_error operand_decoder_vex_vvvv(
        decoding_context *context, operand_wrapper *operand_wrapper,
        fcml_operand_decorators decorators, fcml_ptr args) {

    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

    fcml_st_def_tma_vex_vvvv_reg *v_args = (fcml_st_def_tma_vex_vvvv_reg*)args;

    operand_wrapper->operand.type = FCML_OT_REGISTER;
    fcml_st_register *reg = &(operand_wrapper->operand.reg);

    reg->reg = context->prefixes.vvvv | context->prefixes.V_prim << 4;
    reg->type = (fcml_en_register) v_args->reg_type;
    reg->size = decode_encoded_size_value(context, 
            v_args->encoded_register_size);

    return error;
}

static fcml_ceh_error operand_decoder_isX(
        decoding_context *context, operand_wrapper *operand_wrapper,
        fcml_operand_decorators decorators, fcml_ptr args) {

    /* IS4/IS5 byte is located just after ModR/M field, so it doesn't have 
     * to be read in any post processors.
     */
    fcml_st_def_tma_is *is_args = (fcml_st_def_tma_is *) args;

    /* Read isX byte from stream, or get cached value from context.*/
    fcml_uint8_t isX;
    if (context->isX_byte.is_not_null) {
        isX = context->isX_byte.value;
    } else {
        fcml_bool result;
        isX = fcml_fn_stream_read(context->stream, &result);
        if (!result) {
            return FCML_CEH_GEC_EOF;
        }
        context->isX_byte.is_not_null = FCML_TRUE;
        context->isX_byte.value = isX;
    }

    /* IS4.*/
    if ((is_args->flags & FCML_ISF_IS4) 
            || (is_args->flags & FCML_ISF_IS5_SRC)) {

        operand_wrapper->operand.type = FCML_OT_REGISTER;
        fcml_st_register *reg = &(operand_wrapper->operand.reg);

        reg->reg = ((context->disassembler_context->entry_point.op_mode 
                    == FCML_OM_32_BIT) ? (0x70 & isX) : (0xF0 & isX)) >> 4;
        reg->type = FCML_REG_SIMD;
        reg->size = context->prefixes.L ? FCML_OS_YWORD : FCML_OS_XWORD;
        reg->x64_exp = FCML_FALSE;

    } else {
        /* IS5 - M2Z*/
        operand_wrapper->operand.type = FCML_OT_IMMEDIATE;
        fcml_st_integer *imm = &(operand_wrapper->operand.immediate);
        imm->is_signed = FCML_FALSE;
        imm->int8 = isX & 0x03;
        imm->size = FCML_DS_8;
    }

    return FCML_CEH_GEC_NO_ERROR;
}

static fcml_int operand_size_calculator_isX(decoding_context *context,
        fcml_ptr args) {
    return 1;
}

static fcml_ceh_error operand_decoder_pseudo_op(decoding_context *context,
        operand_wrapper *operand_wrapper, fcml_operand_decorators decorators,
        fcml_ptr args) {

    fcml_bool result;
    fcml_uint8_t pseudo_op = fcml_fn_stream_read(context->stream, &result);
    if (!result) {
        return FCML_CEH_GEC_EOF;
    }

    fcml_st_operand *operand = &(operand_wrapper->operand);
    fcml_st_integer *immediate = &(operand->immediate);

    operand->type = FCML_OT_IMMEDIATE;
    immediate->is_signed = FCML_TRUE;
    immediate->size = FCML_DS_8;
    immediate->int8 = pseudo_op;

    context->pseudo_opcode.is_not_null = FCML_TRUE;
    context->pseudo_opcode.value = pseudo_op;

    return FCML_CEH_GEC_NO_ERROR;
}

static fcml_int operand_size_calculator_pseudo_op(decoding_context *context,
        fcml_ptr args) {
    return 1;
}

/***********/
/* Virtual */
/***********/

static fcml_ceh_error operand_decoder_virtual(decoding_context *context,
        operand_wrapper *operand_wrapper, fcml_operand_decorators decorators,
        fcml_ptr args) {

    fcml_st_operand_decorators *op_decorators =
            &(operand_wrapper->operand.decorators);

    if(context->is_modrm_reg_reg && context->prefixes.b &&
            (context->vector_length == FCML_DS_128 ||
                    context->vector_length == FCML_DS_512)) {

        fcml_uint8_t ll = context->prefixes.L_prim << 1 | context->prefixes.L;

        /* Static rounding. */
        if (FCML_IS_DECOR_ER(decorators) ) {
            op_decorators->er.is_not_null = FCML_TRUE;
            op_decorators->er.value = ll;
            operand_wrapper->operand.type = FCML_OT_VIRTUAL;
        }

        /* Suppress All Exceptions. */
        if (FCML_IS_DECOR_SAE(decorators) && ll == 0) {
            op_decorators->sae = FCML_TRUE;
            operand_wrapper->operand.type = FCML_OT_VIRTUAL;
        }

    }

    if (FCML_IS_DECOR_SAE_REQ(decorators) && !op_decorators->sae) {
        return FCML_CEH_GEC_MISSING_DECORATOR;
    }

    return FCML_CEH_GEC_NO_ERROR;
}

/****************************/
/* Operand decoders table. */
/****************************/

typedef struct operand_decoder_def {
    operand_decoder decoder;
    operand_size_calculator size_calculator;
    fcml_fp_hts_instruction_hints_calculator hints_calculator;
} operand_decoder_def;

/* Order of elements in this array is really important and
 * is related to addressing mode.
 */
static operand_decoder_def operand_decoders[] = {
    {NULL, NULL}, 
    {operand_decoder_imm, operand_size_calculator_imm, NULL},
    {operand_decoder_explicit_reg, NULL, NULL},
    {operand_decoder_opcode_reg, NULL, NULL}, 
    {operand_decoder_immediate_dis_relative, operand_size_calculator_imm_dis_rel,
        fcml_fn_hts_ihc_immediate_dis_relative },
    {operand_decoder_far_pointer, operand_size_calculator_far_pointer,
        fcml_fn_hts_ihc_far_pointer}, 
    {operand_decoder_explicit_gps_reg_addressing, NULL, NULL}, 
    {operand_decoder_explicit_ib, NULL, NULL},
    {operand_decoder_segment_relative_offset,
            operand_size_calculator_seg_rel_offset, NULL },
    {operand_decoder_rm, NULL, fcml_fn_hts_ihc_modrm_hints}, 
    {operand_decoder_r, NULL, NULL},
    {operand_decoder_vex_vvvv, NULL, NULL}, 
    {operand_decoder_isX, operand_size_calculator_isX, NULL},
    {operand_decoder_rm, NULL, fcml_fn_hts_ihc_modrm_hints},
    {operand_decoder_pseudo_op, operand_size_calculator_pseudo_op,
        fcml_fn_hts_ihc_pseudo_opcode},
    {operand_decoder_virtual, NULL, NULL}
};

static void free_operand_decoding(operand_decoding *operand_decoding) {
    if (operand_decoding->decoded_addr_mode) {
        fcml_fnp_def_free_addr_mode(operand_decoding->decoded_addr_mode);
    }
}

static void free_acceptors_chain(addr_mode_acceptor_chain *chain) {
    if (!chain) {
        return;
    }
    if (chain->next) {
        free_acceptors_chain(chain->next);
    }
    fcml_fn_env_memory_free(chain);
}

static void free_decoding_def(inst_decoding_def *decoding) {
    if (decoding->mnemonics) {
        fcml_fn_mp_free_mnemonics(decoding->mnemonics);
    }
    for (int i = 0; i < FCML_OPERANDS_COUNT; i++) {
        free_operand_decoding(&(decoding->operand_decodings[i]));
    }
    free_acceptors_chain(decoding->instruction_acceptors_chain);
    fcml_fn_env_memory_free(decoding);
}

static fcml_ceh_error prepare_operand_decoding(
        fcml_st_def_addr_mode_desc *addr_mode_desc, 
        operand_decoding *operand_decoding,
        fcml_operand_desc operand_desc,
        fcml_hints *instruction_hints) {

    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

    if (operand_desc == FCML_NA) {
        return error;
    }

    operand_decoding->hints = 0;
    operand_decoding->decorators = FCML_DECORATORS(operand_desc);

    fcml_st_def_decoded_addr_mode *decoded_addr_mode;
    error = fcml_fn_def_decode_addr_mode_args(operand_desc, &decoded_addr_mode);
    if (error) {
        return error;
    }

    operand_decoding->decoded_addr_mode = decoded_addr_mode;

    operand_decoder_def *operand_decoder_def = 
        &(operand_decoders[decoded_addr_mode->addr_mode]);

    operand_decoding->decoder = operand_decoder_def->decoder;
    operand_decoding->size_calculator = operand_decoder_def->size_calculator;

    if (operand_decoder_def->hints_calculator) {
        fcml_st_hts_calculated_hints hints = 
            operand_decoder_def->hints_calculator(addr_mode_desc, 
                    decoded_addr_mode);
        operand_decoding->hints |= hints.operand_hints;
        *instruction_hints |= hints.instruction_hints;
    }

    return error;
}

/*********************
 * Prefixes.
 *********************/

static fcml_st_instruction_prefix* get_prefix_if_available(
        decoding_context *context, fcml_uint8_t prefix_value) {
    fcml_st_instruction_prefix* prefix = NULL;
    fcml_st_prefixes_details *prefixes = &(context->prefixes);
    fcml_int prefix_count = prefixes->prefixes_count;
    fcml_int i;
    for (i = 0; i < prefix_count; i++) {
        if (prefixes->prefixes[i].prefix == prefix_value) {
            prefix = &(prefixes->prefixes[i]);
            break;
        }
    }
    return prefix;
}

static fcml_bool is_prefix_available(decoding_context *context,
        fcml_uint8_t prefix, fcml_bool mandatory) {
    fcml_st_prefixes_details *prefixes = &(context->prefixes);
    /* Handle VEX mandatory prefixes.*/
    if (mandatory && (prefixes->is_vex || prefixes->is_evex) && prefixes->pp) {
        if (prefixes->pp == 0x01 && prefix == 0x66) {
            return FCML_TRUE;
        }
        if (prefixes->pp == 0x02 && prefix == 0xF3) {
            return FCML_TRUE;
        }
        if (prefixes->pp == 0x03 && prefix == 0xF2) {
            return FCML_TRUE;
        }
    }
    fcml_st_instruction_prefix *found_prefix = 
            get_prefix_if_available(context, prefix);
    return mandatory ? (found_prefix != NULL && found_prefix->mandatory_prefix)
        : (found_prefix != NULL);
}

static void clear_mandatory_flag(decoding_context *context,
        fcml_uint8_t prefix_code) {
    fcml_st_instruction_prefix *prefix = get_prefix_if_available(
            context, prefix_code);
    if (prefix) {
        prefix->mandatory_prefix = FCML_FALSE;
    }
}

/*******************************
 * Effective attributes sizes. *
 *******************************/

static fcml_usize calculate_effective_asa(decoding_context *context) {

    fcml_st_entry_point *entry_point = 
        &(context->disassembler_context->entry_point);
    fcml_usize effective_asa = entry_point->address_size_attribute;

    /* Checks if address size attribute is overridden.*/
    if (is_prefix_available(context, 0x67, FCML_FALSE)) {
        switch (entry_point->op_mode) {
        case FCML_OM_16_BIT:
        case FCML_OM_32_BIT:
            effective_asa = (effective_asa == FCML_DS_32) 
                ? FCML_DS_16 : FCML_DS_32;
            break;
        case FCML_OM_64_BIT:
            effective_asa = (effective_asa == FCML_DS_32) 
                ? FCML_DS_64 : FCML_DS_32;
            break;
        }
    }

    return effective_asa;
}

static fcml_usize calculate_effective_osa(decoding_context *context,
        fcml_uint32_t opcode_flags) {

    fcml_st_instruction_prefix *prefix;
    fcml_st_entry_point *entry_point = 
        &(context->disassembler_context->entry_point);
    fcml_st_prefixes_details *prefixes = &(context->prefixes);
    fcml_usize osa = entry_point->operand_size_attribute;

    /* Gets effective address-size attribute for used mode.*/
    switch (entry_point->op_mode) {
    case FCML_OM_16_BIT:
    case FCML_OM_32_BIT:
        /* In 16 and 32 bit mode only prefixes can change address-size
         * attribute.
         */
        prefix = get_prefix_if_available(context, 0x66);
        if (prefix != NULL && !prefix->mandatory_prefix) {
            osa = (osa == FCML_DS_16) ? FCML_DS_32 : FCML_DS_16;
        }
        break;
    case FCML_OM_64_BIT:
        /* For some instructions EOSA can be forced to 64 bits.*/
        if (FCML_DEF_OPCODE_FLAGS_FORCE_64BITS_EOSA(opcode_flags)) {
            osa = FCML_DS_64;
        } else {
            if (prefixes->W) {
                /* Prefixes can not override REX.W.*/
                osa = FCML_DS_64;
            } else {
                prefix = get_prefix_if_available(context, 0x66);
                if (prefix != NULL && !prefix->mandatory_prefix) {
                    osa = (osa == FCML_DS_16) ? FCML_DS_32 : FCML_DS_16;
                } else {
                    /* By default EOSA 32 bits is a default value in 64 
                     * bit mode, but some instruction do not use this rule.
                     */
                    if (FCML_DEF_OPCODE_FLAGS_64BITS_EOSA_BY_DEFAULT(
                                opcode_flags) && (osa == FCML_DS_32)) {
                        osa = FCML_DS_64;
                    }
                }
            }
        }
        break;
    }

    return osa;
}

/**************
 * Acceptors. *
 **************/

typedef instruction_acceptor (*inst_acceptor_factory)(
        fcml_st_def_addr_mode_desc *addr_mode_desc);

typedef struct inst_acceptor_factory_holder {
    fcml_string name;
    inst_acceptor_factory acceptor;
} inst_acceptor_factory_holder;

#define FCML_IA_FACTORY(fn)     { #fn, fn }

/**************/
/* Prefixes.  */
/**************/

static fcml_bool inst_acceptor_prefixes(decoding_context *context) {

    inst_decoding_def *decoding_def =
                context->decoding_def;
    /* Prefixes. */
    fcml_st_prefixes_details *prefixes = &(context->prefixes);

    /* LOCK prefix. */
    if (prefixes->is_lock && !FCML_DEF_PREFIX_LOCK_ALLOWED(
                decoding_def->prefixes_flags)) {
        FCML_TRACE("Lock prefix is not allowed.");
        return FCML_FALSE;
    }

    /* VEX required. */
    if ((FCML_DEF_PREFIX_VEX_REQ(decoding_def->prefixes_flags)
                && !prefixes->is_vex)
            || (!FCML_DEF_PREFIX_VEX_REQ(
                    decoding_def->prefixes_flags)
                && prefixes->is_vex)) {
        FCML_TRACE("VEX prefix is required.");
        return FCML_FALSE;
    }

    /* EVEX required. */
    fcml_bool evex_req = FCML_DEF_PREFIX_EVEX_REQ(decoding_def->prefixes_flags);
    if ((evex_req && !prefixes->is_evex) || (!evex_req && prefixes->is_evex)) {
        FCML_TRACE("EVEX prefix is required.");
        return FCML_FALSE;
    }

    /* XOP required. */
    if ((FCML_DEF_PREFIX_XOP_REQ(decoding_def->prefixes_flags)
                && !prefixes->is_xop)
            || (!FCML_DEF_PREFIX_XOP_REQ(
                    decoding_def->prefixes_flags)
                && prefixes->is_xop)) {
        FCML_TRACE("XOP prefix is required.");
        return FCML_FALSE;
    }

    /* W field. */
    if ((FCML_DEF_PREFIX_W_0(decoding_def->prefixes_flags)
                && prefixes->W)
            || (FCML_DEF_PREFIX_W_1(decoding_def->prefixes_flags)
                && !prefixes->W)) {
        FCML_TRACE("Prefix field 'W' has unsupported value.");
        return FCML_FALSE;
    }

    /* L field. */
    fcml_bool l = FCML_TRUE;
    if ((FCML_DEF_PREFIX_L_1(decoding_def->prefixes_flags) &&
                (!prefixes->is_avx || !prefixes->L))
            || (FCML_DEF_PREFIX_L_0(decoding_def->prefixes_flags)
                && (!prefixes->is_avx || prefixes->L))) {
        FCML_TRACE("Prefix field L has unsupported value.");
        l = FCML_FALSE;
    }

    /* L' field. */
    fcml_bool l_prim = FCML_TRUE;
    if ((FCML_DEF_PREFIX_L_prim_1(decoding_def->prefixes_flags) &&
                (!prefixes->is_avx || !prefixes->L_prim))
            || (FCML_DEF_PREFIX_L_prim_0(
                    decoding_def->prefixes_flags)
                && (!prefixes->is_avx || prefixes->L_prim))) {
        FCML_TRACE("Prefix field L' has unsupported value.");
        l_prim = FCML_FALSE;
    }

    if ((!l || !l_prim) && !((decoding_def->decorators_existence.er ||
            decoding_def->decorators_existence.sae ) && prefixes->b)) {
        return FCML_FALSE;
    }

    /* Mandatory prefixes. */

    fcml_bool found = FCML_FALSE;
    if (FCML_DEF_PREFIX_MANDATORY_66(
                decoding_def->prefixes_flags)) {
        found = is_prefix_available(context, 0x66, FCML_TRUE);
    } else if (FCML_DEF_PREFIX_MANDATORY_F2(
                decoding_def->prefixes_flags)) {
        found = is_prefix_available(context, 0xF2, FCML_TRUE);
    } else if (FCML_DEF_PREFIX_MANDATORY_F3(
                decoding_def->prefixes_flags)) {
        found = is_prefix_available(context, 0xF3, FCML_TRUE);
    } else {
        /* Mandatory prefixes not used. */
        found = !((prefixes->is_vex || prefixes->is_evex) && prefixes->pp);
    }
    if (!found) {
        /* Mandatory prefixes not found. */
        FCML_TRACE("Missing mandatory prefix.");
        return FCML_FALSE;
    }

    return FCML_TRUE;
}

static instruction_acceptor inst_acceptor_factory_prefixes(
        fcml_st_def_addr_mode_desc *addr_mode_desc) {
    return inst_acceptor_prefixes;
}

/**********/
/* ModRM. */
/**********/

static fcml_bool inst_acceptor_modrm(decoding_context *context) {

    inst_decoding_def *instruction_decoding_def =
                context->decoding_def;
    fcml_uint32_t opcode_flags = instruction_decoding_def->opcode_flags;
    fcml_st_memory_stream *code = context->stream;
    fcml_st_prefixes_details *prefixes = &(context->prefixes);

    modrm_decoding_details *modrm_details = 
        &(instruction_decoding_def->modrm_details);

    /* Check addressing mode for ModRM opcodes.*/
    if (modrm_details->is_mem_restriction) {
        fcml_bool modrm_found = FCML_FALSE;
        fcml_uint8_t modrm = fcml_fn_stream_peek(code, &modrm_found);
        if (!modrm_found || FCML_MODRM_DEC_MOD(modrm) == 3) {
            return FCML_FALSE;
        }
    }

    if (modrm_details->is_reg_restriction) {
        fcml_bool modrm_found = FCML_FALSE;
        fcml_uint8_t modrm = fcml_fn_stream_peek(code, &modrm_found);
        if (!modrm_found || FCML_MODRM_DEC_MOD(modrm) != 3) {
            return FCML_FALSE;
        }
    }

    /* Check opcode extension. We have to access ModRM byte directly here.*/
    fcml_bool opcodes_valid = FCML_FALSE;
    if (FCML_DEF_OPCODE_FLAGS_OPCODE_IS_EXT(opcode_flags)) {
        fcml_bool modrm_found = FCML_FALSE;
        fcml_uint8_t modrm = fcml_fn_stream_peek(code, &modrm_found);
        if (modrm_found) {
            fcml_uint8_t ext_reg_opcode = ((prefixes->R << 4) 
                    | (FCML_MODRM_DEC_REG_OPCODE(modrm)));
            fcml_uint8_t expected_ext_reg_opcode = 
                FCML_DEF_OPCODE_FLAGS_OPCODE_EXT(opcode_flags);
            opcodes_valid = (ext_reg_opcode == expected_ext_reg_opcode);
        }
    } else {
        opcodes_valid = FCML_TRUE;
    }

    if (!opcodes_valid) {
        return FCML_FALSE;
    }

    return FCML_TRUE;
}

static instruction_acceptor inst_acceptor_factory_modrm(
        fcml_st_def_addr_mode_desc *addr_mode_desc) {
    return FCML_DEF_OPCODE_FLAGS_OPCODE_IS_MODRM(addr_mode_desc->opcode_flags) 
        ? inst_acceptor_modrm : NULL;
}

/********************/
/* Size attributes. */
/********************/

static fcml_bool inst_acceptor_size_attributes_restrictions(
        decoding_context *context) {

    inst_decoding_def *instruction_decoding_def =
                context->decoding_def;

    /* Check EOSA. These fields allow us to restrict instruction decoding only
     * to specific effective operand sizes. For instance we can define 
     * instruction that can be chosen only if EOSA is equal to 16.
     */
    if (FCML_DEF_OPCODE_FLAGS_IS_EOSA_RESTRICTION(
                instruction_decoding_def->opcode_flags)) {
        fcml_bool mandatory_prefix = FCML_FALSE;
        /* Ignore 0x66 prefix if this instruction uses it as mandatory prefix.
         * This correction is also done in the next phase for already 
         * chosen instruction.
         */
        fcml_st_instruction_prefix *prefix = 
            get_prefix_if_available(context, 0x66);
        /* Set this prefix as a mandatory one if this instruction defines 66 as
         * mandatory. This is set temporarily only to calculate correct 
         * EOSA for instruction.
         */
        if (prefix != NULL) {
            mandatory_prefix = prefix->mandatory_prefix;
            prefix->mandatory_prefix = FCML_DEF_PREFIX_MANDATORY_66(
                    instruction_decoding_def->prefixes_flags);
        }
        fcml_usize eosa = calculate_effective_osa(context,
                instruction_decoding_def->opcode_flags);
        if (prefix != NULL) {
            prefix->mandatory_prefix = mandatory_prefix;
        }
        if (!((FCML_DEF_OPCODE_FLAGS_EOSA_16(
                            instruction_decoding_def->opcode_flags) 
                        && eosa == FCML_DS_16)
                || (FCML_DEF_OPCODE_FLAGS_EOSA_32(
                        instruction_decoding_def->opcode_flags) 
                    && eosa == FCML_DS_32)
                || (FCML_DEF_OPCODE_FLAGS_EOSA_64(
                        instruction_decoding_def->opcode_flags) 
                    && eosa == FCML_DS_64))) {
            /* Wrong EOSA, ignore instruction. */
            return FCML_FALSE;
        }
    }

    /* Check EASA. These fields allow us to restrict instruction only
     * to specific effective address sizes. For instance we can define
     * instruction that can be chosen only if EASA is equal to 16.
     */
    if (FCML_DEF_OPCODE_FLAGS_IS_EASA_RESTRICTION(
                instruction_decoding_def->opcode_flags)) {
        fcml_usize easa = calculate_effective_asa(context);
        if (!((FCML_DEF_OPCODE_FLAGS_EASA_16(
                            instruction_decoding_def->opcode_flags) 
                        && easa == FCML_DS_16)
                || (FCML_DEF_OPCODE_FLAGS_EASA_32(
                        instruction_decoding_def->opcode_flags) 
                    && easa == FCML_DS_32)
                || (FCML_DEF_OPCODE_FLAGS_EASA_64(
                        instruction_decoding_def->opcode_flags) 
                    && easa == FCML_DS_64))) {
            /* Wrong EASA, ignore instruction.*/
            return FCML_FALSE;
        }
    }

    return FCML_TRUE;
}

static instruction_acceptor inst_acceptor_factory_size_attributes_restrictions(
        fcml_st_def_addr_mode_desc *addr_mode_desc) {
    return (FCML_DEF_OPCODE_FLAGS_IS_EOSA_RESTRICTION(
                addr_mode_desc->opcode_flags)
            || FCML_DEF_OPCODE_FLAGS_IS_EASA_RESTRICTION(
                addr_mode_desc->opcode_flags)) 
        ? inst_acceptor_size_attributes_restrictions 
        : NULL;
}

/********************/
/* Addressing mode. */
/********************/

static fcml_bool inst_acceptor_addr_mode(decoding_context *context) {
    inst_decoding_def *inst_dec_def = context->decoding_def;
    fcml_st_disassembler_context *dis_ctx = context->disassembler_context;
    fcml_en_operating_mode op_mode = dis_ctx->entry_point.op_mode;
    return ((op_mode == FCML_OM_16_BIT || op_mode == FCML_OM_32_BIT)
            && FCML_DEF_OPCODE_FLAGS_16_32_BIT_MODE_SUPPORTED(
                inst_dec_def->opcode_flags))
            || (op_mode == FCML_OM_64_BIT 
                    && FCML_DEF_OPCODE_FLAGS_64_BIT_MODE_SUPPORTED(
                        inst_dec_def->opcode_flags));
}

static instruction_acceptor inst_acceptor_factory_addr_mode(
        fcml_st_def_addr_mode_desc *addr_mode_desc) {
    return inst_acceptor_addr_mode;
}

/************/
/* AVX-512. */
/************/

/* This acceptor is dedicated for AVX-512 broadcast and rounding. */
static fcml_bool inst_acceptor_avx512(decoding_context *context) {

    inst_decoding_def *decoding_def = context->decoding_def;

    if (context->prefixes.b) {

        fcml_st_memory_stream *code = context->stream;

        /* We need to check ModR/M to know if instruction
         * uses memory addressing. */
        fcml_bool modrm_found = FCML_FALSE;
        fcml_uint8_t modrm = fcml_fn_stream_peek(code, &modrm_found);
        fcml_bool is_reg = !modrm_found || FCML_MODRM_DEC_MOD(modrm) == 3;

        if (is_reg && !decoding_def->decorators_existence.er &&
                !decoding_def->decorators_existence.sae) {
            /* Register-to-register addressing with prefix flag 'b' set,
             * has to support rounding. */
            FCML_TRACE("Prefix flag 'b' is set but rounding is not supported.");
            return FCML_FALSE;
        }

        if (!is_reg && !decoding_def->decorators_existence.bcast) {
            /* Memory addressing with prefix flag 'b' set
             * has to support broadcasting. */
            FCML_TRACE("Prefix flag 'b' is set but broadcast is not supported.");
            return FCML_FALSE;
        }
    }

    return FCML_TRUE;
}

static instruction_acceptor inst_acceptor_factory_avx512(
        fcml_st_def_addr_mode_desc *addr_mode_desc) {
    return ((addr_mode_desc->instruction_group == FCML_AMT_AVX512_SIMD) &&
            FCML_DEF_OPCODE_FLAGS_OPCODE_IS_MODRM(
                    addr_mode_desc->opcode_flags)) ?
            inst_acceptor_avx512 : NULL;
}

static inst_acceptor_factory_holder acceptor_factories[] = {
    FCML_IA_FACTORY(inst_acceptor_factory_prefixes),
    FCML_IA_FACTORY(inst_acceptor_factory_addr_mode),
    FCML_IA_FACTORY(inst_acceptor_factory_modrm),
    FCML_IA_FACTORY(inst_acceptor_factory_size_attributes_restrictions),
    FCML_IA_FACTORY(inst_acceptor_factory_avx512),
    {NULL, NULL}
};

static fcml_ceh_error allocate_acceptors_chain(
        fcml_st_def_addr_mode_desc *addr_mode_desc, 
        addr_mode_acceptor_chain **chain) {

    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

    addr_mode_acceptor_chain *current = NULL, *chain_root = NULL;

    inst_acceptor_factory_holder *factory =
        &(acceptor_factories[0]);

    while (factory->acceptor) {
        /* Asks every factory for acceptor dedicated to the provided 
         * addressing mode description.
         */
        instruction_acceptor acceptor = 
            factory->acceptor(addr_mode_desc);
        if (acceptor) {
            addr_mode_acceptor_chain *chain_element = 
                (addr_mode_acceptor_chain*)
                fcml_fn_env_memory_alloc_clear(
                        sizeof(addr_mode_acceptor_chain));
            if (!chain_element) {
                /* Free already allocated chain.*/
                if (chain_root) {
                    free_acceptors_chain(chain_root);
                }
                return FCML_CEH_GEC_OUT_OF_MEMORY;
            }
            chain_element->name = factory->name;
            chain_element->acceptor = acceptor;
            if (!chain_root) {
                chain_root = chain_element;
            }
            if (current) {
                current->next = chain_element;
            }
            current = chain_element;
        }
        factory++;
    }

    *chain = chain_root;

    return error;
}

/**********************
 * Decoding callback. *
 **********************/

static void dispose_inst_def_callback_default(
        fcml_st_dialect_context_int *dialect, 
        fcml_ptr decoding_ptr) {
    free_decoding_def((inst_decoding_def*) decoding_ptr);
}

static void prepare_modrm_decoding_details(
        fcml_st_def_decoded_addr_mode *decoded_addr_mode, 
        modrm_decoding_details *modrm_details) {
    if (decoded_addr_mode) {
        if (FCMP_DEF_IS_ADDR_MODE(decoded_addr_mode->addr_mode,
                    FCML_OP_VSIB_BASE)) {
            fcml_st_def_tma_rm *rm_args = (fcml_st_def_tma_rm *)
                decoded_addr_mode->addr_mode_args;
            modrm_details->is_vsib = FCML_TRUE;
            modrm_details->vsib_index_size =
                    fcml_fn_def_vsib_reg_to_ds(rm_args->vector_index_register);
        }
        if (FCMP_DEF_IS_ADDR_MODE(decoded_addr_mode->addr_mode, 
                    FCML_OP_RM_BASE)) {
            fcml_st_def_tma_rm *rm_args = 
                (fcml_st_def_tma_rm*)decoded_addr_mode->addr_mode_args;
            modrm_details->is_reg_restriction = (rm_args->flags == FCML_RMF_R);
            modrm_details->is_mem_restriction = (rm_args->flags == FCML_RMF_M);
        }
    }
}

static fcml_ceh_error prepare_inst_def_callback_default(
        fcml_st_dialect_context_int *dialect, 
        fcml_st_dt_diss_tree_element *element,
        fcml_st_def_instruction_desc *instruction_desc, 
        fcml_st_def_addr_mode_desc *addr_mode_desc) {

    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

    /* Prepare instruction decoding structure.*/
    FCML_ENV_ALLOC_CLEAR(decoding, inst_decoding_def);
    if (!decoding) {
        return FCML_CEH_GEC_OUT_OF_MEMORY;
    }

    /* Copy opcodes.*/
    int i;
    for (i = 0; i < sizeof(addr_mode_desc->opcode); i++) {
        decoding->opcodes[i] = addr_mode_desc->opcode[i];
    }

    error = dialect->get_parsed_mnemonics((fcml_st_dialect*) dialect, 
            instruction_desc, addr_mode_desc, &(decoding->mnemonics));
    if (error) {
        free_decoding_def(decoding);
        return FCML_CEH_GEC_INVALID_INPUT;
    }

    /* Copy flags.*/
    decoding->prefixes_flags = addr_mode_desc->allowed_prefixes;
    decoding->opcode_flags = addr_mode_desc->opcode_flags;
    decoding->instruction_group = addr_mode_desc->instruction_group;
    decoding->instruction = instruction_desc->instruction;
    decoding->addr_mode = addr_mode_desc->addr_mode;
    decoding->details = addr_mode_desc->details;

    error = allocate_acceptors_chain(addr_mode_desc, 
            &(decoding->instruction_acceptors_chain));
    if (error) {
        free_decoding_def(decoding);
        return error;
    }

    /* Choose function used to disassemble instruction.*/
    decoding->instruction_decoder = 
        choose_instruction_decoder(
                instruction_desc->instruction_type);

    /* Copy instruction hints from instruction definition.*/
    decoding->hints = addr_mode_desc->instruction_hints;

    /* Prepare operand decoders.*/
    for (i = 0; i < FCML_OPERANDS_COUNT; i++) {
        error = prepare_operand_decoding(addr_mode_desc, 
                &(decoding->operand_decodings[i]), 
                addr_mode_desc->operands[i],
                &(decoding->hints));
        if (!error) {
            prepare_modrm_decoding_details(
                    decoding->operand_decodings[i].decoded_addr_mode, 
                    &(decoding->modrm_details));
        } else {
            free_decoding_def(decoding);
            return error;
        }
    }

    /* Calculates decorators existence. */
    fcml_fn_prepare_decorators_existence(&(addr_mode_desc->operands[0]),
            &(decoding->decorators_existence));

    /* Insert it in appropriate order.*/
    int order = calculate_decoding_order(decoding);

    decoding->order = order;

    fcml_st_coll_list *instruction_decoding_defs = 
        element->instruction_decoding_defs;
    fcml_st_coll_list_element *current = instruction_decoding_defs->head;

    /* Insert prepared instruction decoding in appropriate order.*/
    fcml_st_coll_list_element *prev = NULL;
    while (current) {
        inst_decoding_def *decoding_def = 
            (inst_decoding_def*)current->item;
        if (decoding_def && decoding_def->order < order) {
            break;
        }
        prev = current;
        current = current->next;
    }

    if (!fcml_fn_coll_list_insert(instruction_decoding_defs, prev, decoding)) {
        free_decoding_def(decoding);
        error = FCML_CEH_GEC_OUT_OF_MEMORY;
    }

    return error;
}

/********************
 * Opcode iterator. *
 ********************/

static fcml_uint8_t escape_0f[] = {0x0F};
static fcml_uint8_t escape_0f38[] = {0x0F, 0x38};
static fcml_uint8_t escape_0f3A[] = {0x0F, 0x3A};

static fcml_uint8_t *escape_opcode_table[3] = {
    escape_0f,
    escape_0f38, 
    escape_0f3A
};

static fcml_uint8_t escape_size_tablee_table[] = {1, 2, 2};

struct opcode_iterator;

typedef struct opcode_iterator_impl {
    fcml_st_memory_stream stream;
    fcml_uint8_t is_virtual_opcode;
    fcml_uint8_t *virtual_opcode;
    fcml_int virtual_opcode_count;
    fcml_int virtual_opcode_offset;
} opcode_iterator_impl;

static fcml_int decode_escape_opcode_bytes(decoding_context *decoding_context,
        fcml_uint8_t **virtual_opcode) {

    fcml_st_prefixes_details *prefixes_fields = &(decoding_context->prefixes);
    fcml_int8_t size = 0;

    if (prefixes_fields->is_vex) {
        if (prefixes_fields->avx_first_byte == 0xC4) {
            /* 3-byte VEX. */
            int index = prefixes_fields->mmmm - 1;
            *virtual_opcode = escape_opcode_table[index];
            size = escape_size_tablee_table[index];
        } else {
            /* The 2-byte VEX implies a leading 0Fh opcode byte. */
            *virtual_opcode = escape_0f;
            size = 1;
        }
    }

    if (prefixes_fields->is_xop) {
        /* For XOP opcode byte is directly encoded in mmmmm. */
        *virtual_opcode = &(prefixes_fields->mmmm);
        size = 1;
    }

    if (prefixes_fields->is_evex) {
        int index = prefixes_fields->mmmm - 1;
        *virtual_opcode = escape_opcode_table[index];
        size = escape_size_tablee_table[index];
    }

    return size;
}

static fcml_ceh_error prepare_opcode_iterator(
        decoding_context *decoding_context, 
        struct opcode_iterator **iterator_ptr) {
    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
    opcode_iterator_impl *iterator = 
        (opcode_iterator_impl*) fcml_fn_env_memory_alloc_clear(
            sizeof(opcode_iterator_impl));
    if (iterator) {
        /* Prepare virtual opcodes.*/
        iterator->virtual_opcode_count = 
            decode_escape_opcode_bytes(
                    decoding_context, &(iterator->virtual_opcode));
        iterator->virtual_opcode_offset = 0;
        iterator->stream = *decoding_context->stream;
        iterator->is_virtual_opcode = FCML_FALSE;
        /* Prepare virtual opcodes.*/
        *iterator_ptr = (struct opcode_iterator *) iterator;
    } else {
        error = FCML_CEH_GEC_OUT_OF_MEMORY;
    }
    return error;
}

static fcml_bool opcode_iterator_has_next(
        struct opcode_iterator *iterator_ptr) {
    opcode_iterator_impl *iterator = 
        (opcode_iterator_impl *) iterator_ptr;
    if (iterator->virtual_opcode_count > 0 && iterator->virtual_opcode_offset 
            < iterator->virtual_opcode_count) {
        /* Virtual byte is available.*/
        return FCML_TRUE;
    } else if (fcml_fn_stream_size(&(iterator->stream)) > 0) {
        return FCML_TRUE;
    }
    return FCML_FALSE;
}

static fcml_bool opcode_iterator_is_virtual_opcode(
        struct opcode_iterator *iterator_ptr) {
    opcode_iterator_impl *iterator = 
        (opcode_iterator_impl *)iterator_ptr;
    return iterator->is_virtual_opcode;
}

static fcml_uint8_t opcode_iterator_next(struct opcode_iterator *iterator_ptr) {
    opcode_iterator_impl *iterator = 
        (opcode_iterator_impl *)iterator_ptr;
    if (iterator->virtual_opcode_count > 0 && iterator->virtual_opcode_offset 
            < iterator->virtual_opcode_count) {
        iterator->is_virtual_opcode = FCML_TRUE;
        return iterator->virtual_opcode[iterator->virtual_opcode_offset++];
    } else {
        fcml_bool result;
        fcml_uint8_t opcode_byte = fcml_fn_stream_read(&(iterator->stream), 
                &result);
        if (result) {
            iterator->is_virtual_opcode = FCML_FALSE;
        }
        return opcode_byte;
    }
    return FCML_FALSE;
}

static void opcode_iterator_free(struct opcode_iterator *iterator_ptr) {
    if (iterator_ptr) {
        fcml_fn_env_memory_free(iterator_ptr);
    }
}

/**************************
 * Instructions decoding. *
 **************************/

static void decode_opcode_fields(decoding_context *decoding_context,
        inst_decoding_def *instruction_decoding_def,
        fcml_uint8_t primary_opcode_byte) {

    /* TTTN.*/
    if (FCML_DEF_OPCODE_FLAGS_OPCODE_FIELD_TTTN(
                instruction_decoding_def->opcode_flags)) {
        fcml_uint8_t condition = primary_opcode_byte & 0x0F;
        decoding_context->is_conditional = FCML_TRUE;
        decoding_context->condition.condition_type = (fcml_en_condition_type)
            (condition >> 1);
        decoding_context->condition.is_negation = primary_opcode_byte & 0x01;
    } else {
        decoding_context->is_conditional = FCML_FALSE;
    }

    /* W.*/
    if (FCML_DEF_OPCODE_FLAGS_OPCODE_FIELD_W(
                instruction_decoding_def->opcode_flags)) {
        decoding_context->opcode_field_w_bit = primary_opcode_byte & 0x01;
    }

    /* S.*/
    if (FCML_DEF_OPCODE_FLAGS_OPCODE_FIELD_S(
                instruction_decoding_def->opcode_flags)) {
        decoding_context->opcode_field_s_bit = primary_opcode_byte & 0x02;
    }
}

static fcml_ceh_error decode_operand_decorators(
        decoding_context *decoding_context) {

    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

    for (int i = 0; i < FCML_OPERANDS_COUNT && !error; i++) {

        operand_decoding *operand_decoding =
                &(decoding_context->decoding_def->operand_decodings[i]);
        fcml_st_operand *operand =
                &(decoding_context->operand_wrappers[i].operand);

        fcml_st_decorators_prefix_flags flags;
        flags.b = decoding_context->prefixes.b;
        flags.z = decoding_context->prefixes.z;
        flags.aaa = decoding_context->prefixes.aaa;
        flags.ll = decoding_context->prefixes.L_prim << 1 |
                decoding_context->prefixes.L;

        error = fcml_fn_op_decor_decode(&flags, operand_decoding->decorators,
                operand);
    }

    return error;
}

static fcml_ceh_error instruction_decoder_IA(
        decoding_context *decoding_context) {

    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

    inst_decoding_def *instruction_decoding_def =
            decoding_context->decoding_def;

    /* Instruction hints.*/

    decoding_context->instruction_hints = instruction_decoding_def->hints;

    /* Change prefixes to mandatory one if needed.*/

    if (!FCML_DEF_PREFIX_MANDATORY_66(
                instruction_decoding_def->prefixes_flags)) {
        clear_mandatory_flag(decoding_context, 0x66);
    }

    if (!FCML_DEF_PREFIX_MANDATORY_F2(
                instruction_decoding_def->prefixes_flags)) {
        clear_mandatory_flag(decoding_context, 0xF2);
    } else {
        decoding_context->prefixes.is_repne = FCML_FALSE;
    }

    if (!FCML_DEF_PREFIX_MANDATORY_F3(
                instruction_decoding_def->prefixes_flags)) {
        clear_mandatory_flag(decoding_context, 0xF3);
    } else {
        decoding_context->prefixes.is_rep = FCML_FALSE;
    }

    /* Branches, take into account that this condition does not
     * collide with multi-instructions.
     */
    if (instruction_decoding_def->instruction != F_JCC) {
        decoding_context->prefixes.is_branch = FCML_FALSE;
        decoding_context->prefixes.is_nobranch = FCML_FALSE;
    }

    /* Change REP/REPNE prefixes to XACQUIRE/XRELEASE if instruction
     * support them.
     */
    if (FCML_DEF_PREFIX_HLE_ENABLED(
                instruction_decoding_def->prefixes_flags)) {
        if (decoding_context->prefixes.is_rep) {
            decoding_context->prefixes.is_xrelease = FCML_TRUE;
            decoding_context->prefixes.is_rep = FCML_FALSE;
        }
        if (decoding_context->prefixes.is_repne) {
            decoding_context->prefixes.is_xacquire = FCML_TRUE;
            decoding_context->prefixes.is_repne = FCML_FALSE;
        }
    }

    decoding_context->calculated_instruction_size = 
        decoding_context->prefixes.prefixes_bytes_count + 
        decoding_context->opcodes_count;

    /* Calculates effective operand sizes. It's not important if they will
     * be used or not.
     */
    decoding_context->effective_address_size_attribute = 
        calculate_effective_asa(decoding_context);
    decoding_context->effective_operand_size_attribute = 
        calculate_effective_osa(decoding_context, 
                instruction_decoding_def->opcode_flags);
    decoding_context->element_size =
            FCML_GET_SIMD_ELEMENT_SIZE(instruction_decoding_def->details);

    operand_wrapper *operand_wrappers = 
        &(decoding_context->operand_wrappers[0]);
    modrm_decoding_details *modrm_details = 
        &(instruction_decoding_def->modrm_details);
    fcml_st_prefixes_details *prefixes = &(decoding_context->prefixes);

    fcml_uint8_t tuple_type =
            FCML_GET_SIMD_TUPLETYPE(instruction_decoding_def->details);

    /* Decode ModRM field if there is any. */
    if (FCML_DEF_OPCODE_FLAGS_OPCODE_IS_MODRM(
                instruction_decoding_def->opcode_flags)) {

        decoding_context->is_modrm = FCML_TRUE;

        fcml_st_memory_stream *stream = decoding_context->stream;

        fcml_uint32_t offset = stream->offset;

        fcml_usize vector_length = calculate_vector_length(
                FCML_TT_NONE, FCML_FALSE, prefixes->L | prefixes->L_prim << 1);

        fcml_st_modrm_decoder_context modrm_context;
        modrm_context.op_mode = 
            decoding_context->disassembler_context->entry_point.op_mode;
        modrm_context.effective_address_size = 
            decoding_context->effective_address_size_attribute;
        modrm_context.input_size =
                FCML_GET_SIMD_ELEMENT_SIZE(instruction_decoding_def->details);

        modrm_context.vector_length = vector_length;
        modrm_context.tuple_type = tuple_type;
        modrm_context.b = prefixes->b;
        modrm_context.is_evex = prefixes->is_evex;

        fcml_st_modrm_source modrm_source;
        modrm_source.is_vsib = modrm_details->is_vsib;

        if (modrm_details->is_vsib) {
            if (modrm_details->vsib_index_size == FCML_DS_UNDEF) {
                modrm_source.vsib_index_size = vector_length;
            } else {
                modrm_source.vsib_index_size = modrm_details->vsib_index_size;
            }
        } else {
            modrm_source.vsib_index_size = 0;
        }

        modrm_source.ext_B = prefixes->B;
        modrm_source.ext_R = prefixes->R;
        modrm_source.ext_R_prim = prefixes->R_prim;
        modrm_source.ext_X = prefixes->X;
        modrm_source.ext_V_prim = prefixes->V_prim;
        modrm_source.stream = decoding_context->stream;

        fcml_uint8_t flags = 0;
        if (decoding_context->disassembler_context->
                configuration.extend_disp_to_asa) {
            flags |= FCML_MODRM_DEC_FLAG_EXTEND_DISPLACEMENT_TO_ASA;
        }

        error = fcml_fn_modrm_decode(&modrm_context, &modrm_source, 
                &(decoding_context->decoded_modrm), 
                &(decoding_context->decoded_modrm_details),
                flags);
        if (error) {
            return error;
        }

        decoding_context->tuple_type = tuple_type;

        decoding_context->is_modrm_reg_reg =
                decoding_context->decoded_modrm.reg.is_not_null;

        decoding_context->calculated_instruction_size += stream->offset - 
            offset;
    }

    /* After decoding ModR/M we can calculate vector length in order to
     * handle static rounding mode correctly. If {er} is enabled vector
     * length is implied. */
    if (prefixes->is_avx) {
        /* Static Rounding Mode and SAE is enabled for reg-to-reg instructions
         * when EXEV.b is set.
         */
        fcml_bool sae_enabled = prefixes->b &&
                decoding_context->is_modrm_reg_reg &&
                (instruction_decoding_def->decorators_existence.er ||
                instruction_decoding_def->decorators_existence.sae);

        decoding_context->vector_length =
                calculate_vector_length(tuple_type, sae_enabled,
                        prefixes->L | prefixes->L_prim << 1);
    }

    /* Calculate operands size. */
    fcml_int i, operands_size = 0;
    for (i = 0; i < FCML_OPERANDS_COUNT; i++) {
        operand_decoding *operand_decoding = 
            &(instruction_decoding_def->operand_decodings[i]);
        fcml_st_def_decoded_addr_mode *decoded_addr_mode = 
            operand_decoding->decoded_addr_mode;
        if (operand_decoding->size_calculator) {
            operands_size += operand_decoding->size_calculator(
                    decoding_context, decoded_addr_mode->addr_mode_args);
        }
    }

    decoding_context->calculated_instruction_size += operands_size;
    decoding_context->mnemonics = instruction_decoding_def->mnemonics;
    decoding_context->instruction = instruction_decoding_def->instruction;
    decoding_context->instruction_group = 
        instruction_decoding_def->instruction_group;
    decoding_context->addr_mode = instruction_decoding_def->addr_mode;

    /* Store primary opcode byte.*/
    fcml_int opcode_num = FCML_DEF_OPCODE_FLAGS_PRIMARY_OPCODE(
            instruction_decoding_def->opcode_flags);
    decoding_context->primary_opcode_byte = decoding_context->opcodes[
        opcode_num - decoding_context->virtual_opcodes_count];

    /* Decode opcode fields.*/
    decode_opcode_fields(decoding_context, 
            instruction_decoding_def, decoding_context->primary_opcode_byte);

    /* Decode operands.*/
    for (i = 0; i < FCML_OPERANDS_COUNT; i++) {
        operand_decoding *operand_decoding = 
            &(instruction_decoding_def->operand_decodings[i]);
        fcml_st_def_decoded_addr_mode *decoded_addr_mode = 
            operand_decoding->decoded_addr_mode;
        /* It's important not to break the loop before it
         * goes through all the operands to make sure
         * that all of them will be cleaned. */
        fcml_fn_env_memory_clear(operand_wrappers,
                sizeof(operand_wrapper));
        if (operand_decoding->decoder) {
            error = operand_decoding->decoder(decoding_context,
                    operand_wrappers, operand_decoding->decorators,
                    decoded_addr_mode->addr_mode_args);
            if (error) {
                break;
            }
            operand_wrappers->operand.hints |= operand_decoding->hints;
            operand_wrappers->access_mode = decoded_addr_mode->access_mode;
            operand_wrappers++;
        }
    }

    if (!error) {
        error = decode_operand_decorators(decoding_context);
    }

    /* Decode suffix.*/
    if (!error &&
            FCML_DEF_PREFIX_SUFFIX(instruction_decoding_def->prefixes_flags)) {
        fcml_bool result;
        decoding_context->suffix.value = fcml_fn_stream_read(
                decoding_context->stream, &result);
        if (result) {
            decoding_context->suffix.is_not_null = FCML_TRUE;
        } else {
            error = FCML_CEH_GEC_EOF;
        }
    }

    return error;
}

static fcml_ceh_error prepare_pseudo_operation(decoding_context *context) {

    /* Seek to the beginning of the stream. */
    fcml_fn_stream_seek(context->stream, 0, FCML_EN_ST_START);

    /* Clean whole decoding context, because there might be
     * remains of the previous processing.
     */
    fcml_fn_env_memory_clear(&(context->prefixes), 
            sizeof(fcml_st_prefixes_details));

    /* Get first instruction byte. */
    fcml_bool result;
    fcml_uint8_t po_byte = fcml_fn_stream_read(context->stream, &result);
    if (!result) {
        return FCML_CEH_GEC_EOF;
    }

    context->pseudo_op = FP_DB;

    /* Prepare operand with immediate value. */
    fcml_st_operand *operand = &(context->operand_wrappers[0].operand);
    operand->type = FCML_OT_IMMEDIATE;
    operand->immediate.int8 = po_byte;
    operand->immediate.size = FCML_DS_8;

    context->opcodes_count = 1;
    context->calculated_instruction_size = 1;

    return FCML_CEH_GEC_NO_ERROR;
}

static fcml_ceh_error decode_instruction(decoding_context *context) {

    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
    disassembler *disasm =
            (disassembler *)context->disassembler_context->disassembler;
    fcml_st_dt_decoding_tree *decoding_tree = disasm->decoding_tree;

    /* Prepare opcode iterator.*/
    struct opcode_iterator *iterator;
    error = prepare_opcode_iterator(context, &iterator);
    if (error) {
        return error;
    }

    struct fcml_st_dt_diss_tree_element **opcodes = 
        &(decoding_tree->opcode[0]);

    /* Found instruction addressing modes going here.*/
    fcml_st_dt_diss_tree_element* tree_element = NULL;

    while (opcode_iterator_has_next(iterator)) {
        /* Get next instructions opcode. */
        fcml_uint8_t opcode_byte = opcode_iterator_next(
                iterator);

        /* Get instruction for given opcode. */
        fcml_st_dt_diss_tree_element *current = opcodes[opcode_byte];

        if (current) {
            /* There is something for given opcode byte, so save it.*/
            tree_element = current;
            /* Store all non virtual opcode bytes inside context.*/
            if (!opcode_iterator_is_virtual_opcode(iterator)) {
                context->opcodes[context->opcodes_count++] = opcode_byte;
            } else {
                context->virtual_opcodes_count++;
            }
            opcodes = &(tree_element->opcodes[0]);
        } else {
            break;
        }
    }

    /* Free opcode iterator.*/
    opcode_iterator_free(iterator);

    /* Skip opcode bytes.*/
    fcml_fn_stream_seek(context->stream, context->opcodes_count, 
            FCML_EN_ST_CURRENT);

    fcml_bool found = FCML_FALSE;

    /* Disassemble instruction using most appropriate addressing mode from 
     * disassembling tree.
     */
    if (tree_element && tree_element->instruction_decoding_defs) {

        fcml_st_coll_list_element *current = 
            tree_element->instruction_decoding_defs->head;
        int i = 0;
        while (current) {
            inst_decoding_def *decoding_def = 
                (inst_decoding_def*) current->item;
            if (decoding_def) {

                FCML_TRACE("Accepting next addressing mode %d - " \
                        "prefixes: 0x%08X, opcode: 0x%08X.",
                        i, decoding_def->prefixes_flags,
                        decoding_def->opcode_flags);

                /* Set current decoding definition.*/
                context->decoding_def = decoding_def;
                /* Try to accept this addressing mode.*/
                fcml_bool accept = FCML_TRUE;
                addr_mode_acceptor_chain *chain = 
                    decoding_def->instruction_acceptors_chain;
                while (chain) {
                    if (chain->acceptor && !chain->acceptor(context)) {
                        FCML_TRACE("Denied addressing mode %d - " \
                                "prefixes: 0x%08X, opcode: 0x%08X. Acceptor: %s",
                                i, decoding_def->prefixes_flags,
                                decoding_def->opcode_flags,
                                chain->name);
                        accept = FCML_FALSE;
                        break;
                    }
                    chain = chain->next;
                }
                if (accept) {
                    FCML_TRACE("Accepted addressing mode %d - " \
                            "prefixes: 0x%08X, opcode: 0x%08X.",
                            i, decoding_def->prefixes_flags,
                            decoding_def->opcode_flags);
                    fcml_stream_pointer save_point =
                            fcml_fn_stream_save_point(context->stream);
                    error = decoding_def->instruction_decoder(context);
                    if (!error) {
                        found = FCML_TRUE;
                        break;
                    } else {
                        FCML_TRACE("Instruction decoding failed for "
                                "addressing mode %d - " \
                                "prefixes: 0x%08X, opcode: 0x%08X. Error: %d",
                                i, decoding_def->prefixes_flags,
                                decoding_def->opcode_flags, error);
                        /* We are to try the next addressing form, so
                         * restore the stream. */
                        fcml_fn_stream_restore_point(context->stream,
                                save_point);
                    }
                }
            }
            current = current->next;
            i++;
        }

    } else {
        if (!context->disassembler_context->configuration
                .fail_if_unknown_instruction) {
            error = prepare_pseudo_operation(context);
            if (!error) {
                found = FCML_TRUE;
            }
        } else {
            /* Unknown instruction.*/
            error = FCML_CEH_GEC_UNKNOWN_INSTRUCTION;
        }
    }

    if (!found && !error) {
        error = FCML_CEH_GEC_UNKNOWN_INSTRUCTION;
    }

    return error;
}

/****************************
 * Prefixes decoding.
 ****************************/

#define FCML_IDFPF_IS_MANDATORY_CANDIDATE       0x0001
#define FCML_IDFPF_IS_LOCK                      0x0002
#define FCML_IDFPF_IS_REP_XRELEASE              0x0004
#define FCML_IDFPF_IS_REPNE_XACQUIRE            0x0008
#define FCML_IDFPF_IS_VEX                       0x0010
#define FCML_IDFPF_IS_XOP                       0x0020
#define FCML_IDFPF_IS_BRANCH                    0x0040
#define FCML_IDFPF_IS_XOP_ALLOWED               0x0080
#define FCML_IDFPF_IS_NOBRANCH                  0x0100
#define FCML_IDFPF_IS_EVEX                      0x0200

static fcml_ceh_error decode_prefixes(decoding_context *decoding_context) {

    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

    fcml_st_prefixes_details *prefixes = &(decoding_context->prefixes);
    fcml_st_memory_stream *stream = decoding_context->stream;
    fcml_en_operating_mode op_mode = 
        decoding_context->disassembler_context->entry_point.op_mode;
    fcml_st_prefixes_details *prefixes_details = &(decoding_context->prefixes);
    fcml_uint16_t p_flags = 0;
    fcml_en_prefix_types prefix_type = FCML_PT_GROUP_UNKNOWN;
    fcml_int prefix_index = 0;
    fcml_int prefix_size = 0;
    fcml_int xop_vex_prefix_size = 0;
    fcml_bool result = FCML_FALSE;
    fcml_bool is_xop_vex_allowed = FCML_TRUE;
    fcml_bool is_last_prefix = FCML_FALSE;

    /* VEX like prefixes are not allowed in 16 bit mode.*/
    if (op_mode == FCML_OM_16_BIT) {
        is_xop_vex_allowed = FCML_FALSE;
    }

    do {
        prefix_type = FCML_PT_GROUP_UNKNOWN;
        p_flags = 0;
        /* Almost all prefixes are one byte length, so it's a 
         * reasonable default here.
         */
        prefix_size = 1;
        fcml_uint8_t prefix = fcml_fn_stream_peek(stream, &result);
        if (result) {
            fcml_st_instruction_prefix *prefix_details = 
                &(prefixes->prefixes[prefix_index]);
            switch (prefix) {
            case 0xF0:
                prefix_type = FCML_PT_GROUP_1;
                is_xop_vex_allowed = FCML_FALSE;
                p_flags |= FCML_IDFPF_IS_LOCK;
                break;
            case 0xF2:
                p_flags |= (FCML_IDFPF_IS_MANDATORY_CANDIDATE | 
                            FCML_IDFPF_IS_REPNE_XACQUIRE);
                prefix_type = FCML_PT_GROUP_1;
                is_xop_vex_allowed = FCML_FALSE;
                break;
            case 0xF3:
                p_flags |= (FCML_IDFPF_IS_MANDATORY_CANDIDATE | 
                            FCML_IDFPF_IS_REP_XRELEASE);
                prefix_type = FCML_PT_GROUP_1;
                is_xop_vex_allowed = FCML_FALSE;
                break;
            case 0x2E:
                p_flags |= FCML_IDFPF_IS_NOBRANCH;
                prefix_type = FCML_PT_GROUP_2;
                break;
            case 0x3E:
                p_flags |= FCML_IDFPF_IS_BRANCH;
                prefix_type = FCML_PT_GROUP_2;
                break;
            case 0x26:
            case 0x36:
            case 0x64:
            case 0x65:
                prefix_type = FCML_PT_GROUP_2;
                break;
                break;
            case 0x66:
                p_flags |= FCML_IDFPF_IS_MANDATORY_CANDIDATE;
                prefix_type = FCML_PT_GROUP_3;
                is_xop_vex_allowed = FCML_FALSE;
                break;
            case 0x67:
                prefix_type = FCML_PT_GROUP_4;
                break;
            case 0xC5:
                xop_vex_prefix_size = 1;
                prefix_type = FCML_PT_VEX;
                p_flags |= FCML_IDFPF_IS_VEX;
                is_last_prefix = FCML_TRUE;
                break;
            case 0x8F:
                xop_vex_prefix_size = 2;
                prefix_type = FCML_PT_XOP;
                p_flags |= FCML_IDFPF_IS_XOP;
                is_last_prefix = FCML_TRUE;
                break;
            case 0xC4:
                xop_vex_prefix_size = 2;
                prefix_type = FCML_PT_VEX;
                p_flags |= FCML_IDFPF_IS_VEX;
                is_last_prefix = FCML_TRUE;
                break;
            case 0x62:
                xop_vex_prefix_size = 3;
                prefix_type = FCML_PT_EVEX;
                p_flags |= FCML_IDFPF_IS_EVEX;
                is_last_prefix = FCML_TRUE;
                break;
            default:
                /* REX prefix is the last one, so we have to break this loop 
                 * after finding one.
                 */
                if (op_mode == FCML_OM_64_BIT && prefix >= 0x40
                        && prefix <= 0x4F) {
                    /* REX prefix found.*/
                    prefix_type = FCML_PT_REX;
                    /* Decode fields.*/
                    prefixes_details->is_rex = FCML_TRUE;
                    prefixes_details->W = FCML_REX_W(prefix);
                    prefixes_details->R = FCML_REX_R(prefix);
                    prefixes_details->X = FCML_REX_X(prefix);
                    prefixes_details->B = FCML_REX_B(prefix);
                    /* REX can not be used together with the VEX at the 
                     * moment.
                     */
                    is_xop_vex_allowed = FCML_FALSE;
                    is_last_prefix = FCML_TRUE;
                }
                break;
            }

            /* Handle VEX/XOP prefixes. */
            if (prefix_type == FCML_PT_VEX || prefix_type == FCML_PT_XOP
            		|| prefix_type == FCML_PT_EVEX) {

            	if (is_xop_vex_allowed) {

                    fcml_stream_pointer sp = fcml_fn_stream_save_point(stream);

                    /* Skip to the second byte of VEX prefix.*/
                    fcml_fn_stream_seek(stream, 1, FCML_EN_ST_CURRENT);

                    if (op_mode == FCML_OM_32_BIT) {
                        /* Check if it is really a VEX/XOP prefix.*/
                        fcml_uint8_t second_byte = fcml_fn_stream_peek(stream, 
                                &result);
                        /* VEX.R/XOP.R and VEX.X/XOP.X has to be set to 11 in 
                         * 32bit mode.
                         */
                        if (!result || (second_byte & 0xC0) != 0xC0) {
                            fcml_fn_stream_restore_point(stream, sp);
                            prefix_type = FCML_PT_GROUP_UNKNOWN;
                        }
                        /* In case of XOP prefix, if the MMMMM field is less 
                         * than 8 then these two bytes are a form of the POP 
                         * instruction rather than an XOP prefix.
                         */
                        if (prefix_type == FCML_PT_XOP && 
                                FCML_VEX_MMMM(second_byte) < 0x08) {
                            fcml_fn_stream_restore_point(stream, sp);
                            prefix_type = FCML_PT_GROUP_UNKNOWN;
                        }
                    }

                    /* Copy rest of the VEX prefixes.*/
                    if (prefix_type != FCML_PT_GROUP_UNKNOWN) {

                        fcml_int nbytes = fcml_fn_stream_read_bytes(stream, 
                                &(prefix_details->avx_bytes),
								xop_vex_prefix_size);
                        if (nbytes != xop_vex_prefix_size) {
                            /* Stream is incomplete, so we can not treat it 
                             * as a VEX/XOP.
                             */
                            prefix_type = FCML_PT_GROUP_UNKNOWN;
                        } else {
                            switch (prefix) {
                                /* Decodes VEX/XOP fields.*/
                            case 0x62: {
                             	fcml_uint8_t p0 =
                            	        prefix_details->avx_bytes[0];
                            	fcml_uint8_t p1 =
                            	        prefix_details->avx_bytes[1];
                            	fcml_uint8_t p2 =
                            	        prefix_details->avx_bytes[2];

                            	// These fields are fixed for EVEX.
                            	if ((p0 & 0x0C) || !(p1 & 0x04)) {
                            	    prefix_type = FCML_PT_GROUP_UNKNOWN;
                            	    break;
                            	}

                            	// EVEX.mm cannot be set to 0.
                            	if (FCML_EVEX_MM(p0) == 0) {
                            	    prefix_type = FCML_PT_GROUP_UNKNOWN;
                                    break;
                            	}

                            	// In 32-bit mode EVEX.RX has to be set to 11.
                                // Otherwise it's a BOUND instruction.
                                if (op_mode == FCML_OM_32_BIT &&
                                        (p0 & 0xC0) != 0xC0) {
                                    prefix_type = FCML_PT_GROUP_UNKNOWN;
                                    break;
                                }

                                prefixes_details->R = FCML_EVEX_R(p0);
                                prefixes_details->X = FCML_EVEX_X(p0);
                                prefixes_details->B = FCML_EVEX_B(p0);
                                prefixes_details->R_prim = FCML_EVEX_R_PRIM(p0);
                                prefixes_details->mmmm = FCML_EVEX_MM(p0);

                                prefixes_details->W = FCML_EVEX_W(p1);
                                prefixes_details->vvvv = FCML_EVEX_VVVV(p1);
                                prefixes_details->pp = FCML_EVEX_PP(p1);

                                prefixes_details->z = FCML_EVEX_z(p2);
                                prefixes_details->L_prim = FCML_EVEX_L_PRIM(p2);
                                prefixes_details->L = FCML_EVEX_L(p2);
                                prefixes_details->b = FCML_EVEX_b(p2);
                                prefixes_details->V_prim = FCML_EVEX_V_PRIM(p2);
                                prefixes_details->aaa = FCML_EVEX_aaa(p2);

                            	break;
                            }
                            case 0x8F:
                                /* XOP is encoded like 3 bytes VEX prefix.*/
                            case 0xC4:
                                if (prefix_type == FCML_PT_XOP && 
                                        FCML_VEX_MMMM(
                                            prefix_details->avx_bytes[0]) 
                                        < 0x08) {
                                    prefix_type = FCML_PT_GROUP_UNKNOWN;
                                    break;
                                }
                                prefixes_details->R = FCML_VEX_R(
                                        prefix_details->avx_bytes[0]);
                                prefixes_details->X = FCML_VEX_X(
                                        prefix_details->avx_bytes[0]);
                                /* For AVX instructions, this bit is ignored in
                                 * 32-bit mode, but AVX-512 instructions using
                                 * opmask registers directly use it even in
                                 * 32-bit mode to distinguish instructions.
                                 */
                                prefixes_details->W = FCML_VEX_W(
                                        prefix_details->avx_bytes[1]);
                                if (op_mode == FCML_OM_64_BIT) {
                                    prefixes_details->B = FCML_VEX_B(
                                            prefix_details->avx_bytes[0]);
                                } else {
                                    /* Should be silently ignored in
                                       32-bit mode. */
                                    prefixes_details->B = 0;
                                }
                                prefixes_details->L = FCML_VEX_L(
                                        prefix_details->avx_bytes[1]);
                                prefixes_details->pp = FCML_VEX_PP(
                                        prefix_details->avx_bytes[1]);
                                prefixes_details->mmmm = FCML_VEX_MMMM(
                                        prefix_details->avx_bytes[0]);
                                prefixes_details->vvvv = FCML_VEX_VVVV(
                                        prefix_details->avx_bytes[1]);
                                break;
                            case 0xC5:
                                prefixes_details->R = FCML_VEX_R(
                                        prefix_details->avx_bytes[0]);
                                prefixes_details->L = FCML_VEX_L(
                                        prefix_details->avx_bytes[0]);
                                prefixes_details->vvvv = FCML_VEX_VVVV(
                                        prefix_details->avx_bytes[0]);
                                prefixes_details->pp = FCML_VEX_PP(
                                        prefix_details->avx_bytes[0]);
                                break;
                            }

                            if (op_mode == FCML_OM_32_BIT && 
                                    prefixes_details->vvvv > 7) {
                                prefix_type = FCML_PT_GROUP_UNKNOWN;
                            }

                            prefixes_details->avx_first_byte = prefix;

                            prefix_size += xop_vex_prefix_size;
                        }

                        fcml_fn_stream_restore_point(stream, sp);
                    }

                } else {
                    /* If 0xC5 and 0xC4 can not be treated as a VEX prefix,
                     * and 0x62 cannot be treated as EVEX prefix,
                     * it should be treated just as an instruction opcode.
                     */
                    prefix_type = FCML_PT_GROUP_UNKNOWN;
                }
            }

            if (prefix_type != FCML_PT_GROUP_UNKNOWN) {
                prefix_details->prefix = prefix;
                prefix_details->prefix_type = prefix_type;
                prefix_details->mandatory_prefix = (p_flags 
                        & FCML_IDFPF_IS_MANDATORY_CANDIDATE) 
                    ? FCML_TRUE : FCML_FALSE;
                if (p_flags & FCML_IDFPF_IS_EVEX) {
                    prefixes_details->is_evex = FCML_TRUE;
                }
                if (p_flags & FCML_IDFPF_IS_VEX) {
                    prefixes_details->is_vex = FCML_TRUE;
                }
                if (p_flags & FCML_IDFPF_IS_XOP) {
                    prefixes_details->is_xop = FCML_TRUE;
                }
                if (p_flags & FCML_IDFPF_IS_LOCK) {
                    prefixes_details->is_lock = 
                        (p_flags & FCML_IDFPF_IS_LOCK) 
                        ? FCML_TRUE : FCML_FALSE;
                }
                if (p_flags & FCML_IDFPF_IS_REP_XRELEASE) {
                    prefixes_details->is_rep = 
                        (p_flags & FCML_IDFPF_IS_REP_XRELEASE) 
                        ? FCML_TRUE : FCML_FALSE;
                }
                if (p_flags & FCML_IDFPF_IS_REPNE_XACQUIRE) {
                    prefixes_details->is_repne = 
                        (p_flags & FCML_IDFPF_IS_REPNE_XACQUIRE) 
                        ? FCML_TRUE : FCML_FALSE;
                }
                if (p_flags & FCML_IDFPF_IS_BRANCH) {
                    prefixes_details->is_branch = 
                        (p_flags & FCML_IDFPF_IS_BRANCH) 
                        ? FCML_TRUE : FCML_FALSE;
                }
                if (p_flags & FCML_IDFPF_IS_NOBRANCH) {
                    prefixes_details->is_nobranch = 
                        (p_flags & FCML_IDFPF_IS_NOBRANCH) 
                        ? FCML_TRUE : FCML_FALSE;
                }
                prefixes_details->is_avx = prefixes_details->is_vex
                        || prefixes_details->is_evex
                        || prefixes_details->is_xop;
                prefixes_details->prefixes_bytes_count += prefix_size;
                fcml_fn_stream_seek(stream, prefix_size, FCML_EN_ST_CURRENT);
                prefix_index++;
            } else {
                is_last_prefix = FCML_FALSE;
            }

        }
        /* Break loop if REX or VEX prefix is already found.*/
    } while (prefix_type != FCML_PT_GROUP_UNKNOWN && !is_last_prefix);

    prefixes_details->prefixes_count = prefix_index;

    /* Check if prefixes marked as mandatory are really a mandatory ones.*/
    /* VEX and XOP prefixes don't allow any mandatory prefixes, so following*/
    /* code has nothing to do if there is VEX or XOP.*/
    if (prefix_index > 0 && prefix_type != FCML_PT_VEX && 
            prefix_type != FCML_PT_XOP && prefix_type != FCML_PT_EVEX) {
        fcml_bool found_plain_prefix = FCML_FALSE;
        fcml_int i;
        for (i = prefix_index; i > 0; i--) {
            if (found_plain_prefix) {
                prefixes->prefixes[i - 1].mandatory_prefix = FCML_FALSE;
            } else {
                /* REX prefixes have to be preceded by mandatory and optional 
                 * prefixes if there are any.
                 */
                fcml_st_instruction_prefix *prefix = 
                    &(prefixes->prefixes[i - 1]);
                if (!prefix->mandatory_prefix && 
                        prefix->prefix_type != FCML_PT_REX) {
                    found_plain_prefix = FCML_TRUE;
                }
            }
        }
    }

    return error;
}

static fcml_prefixes convert_prefixes_to_generic_prefixes(
        fcml_st_prefixes_details *prefixes) {
    fcml_prefixes gen_prefixes = 0;
    if (prefixes) {
        if (prefixes->is_rep) {
            gen_prefixes |= FCML_PREFIX_REP;
        }
        if (prefixes->is_repne) {
            gen_prefixes |= FCML_PREFIX_REPNE;
        }
        if (prefixes->is_lock) {
            gen_prefixes |= FCML_PREFIX_LOCK;
        }
        if (prefixes->is_xacquire) {
            gen_prefixes |= FCML_PREFIX_XACQUIRE;
        }
        if (prefixes->is_xrelease) {
            gen_prefixes |= FCML_PREFIX_XRELEASE;
        }
        if (prefixes->is_branch) {
            gen_prefixes |= FCML_PREFIX_BRANCH_HINT;
        }
        if (prefixes->is_nobranch) {
            gen_prefixes |= FCML_PREFIX_NOBRANCH_HINT;
        }
    }
    return gen_prefixes;
}

static void clean_operands_for_short_forms(fcml_st_instruction *instruction,
        fcml_st_instruction_details *instruction_details) {
    if (instruction_details->is_shortcut) {
        /* Clean all operands, short forms do not have them.*/
        instruction->operands_count = 0;
        fcml_fn_env_memory_clear(&(instruction->operands[0]),
                sizeof(fcml_st_operand[FCML_OPERANDS_COUNT]));
        fcml_fn_env_memory_clear(&(instruction_details->operand_details[0]),
                sizeof(fcml_st_operand_details[FCML_OPERANDS_COUNT]));
    } else if (instruction_details->is_pseudo_op) {
        for (int i = 0; i < FCML_OPERANDS_COUNT; i++) {
            /* Clean IMM pseudo opcode operand.*/
            if (instruction->operands[i].hints & FCML_OP_HINT_PSEUDO_OPCODE) {
                fcml_fn_env_memory_clear(&(instruction->operands[i]),
                        sizeof(fcml_st_operand));
                fcml_fn_env_memory_clear(
                        &(instruction_details->operand_details[i]),
                        sizeof(fcml_st_operand_details));
                instruction->operands_count--;
                /* It is always the last one.*/
                break;
            }
        }
    }
}

static fcml_ceh_error disassemble_core(fcml_st_disassembler_context *context,
        fcml_st_disassembler_result *result) {

    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
    disassembler *int_disasm = (disassembler *)context->disassembler;

    error = fcml_fn_utils_prepare_entry_point(&(context->entry_point));
    if (error) {
        return error;
    }

    /* Prepare stream.*/
    fcml_st_memory_stream stream;
    stream.base_address = context->code;
    stream.size = context->code_length;
    stream.offset = 0;

    /* Prepare disassemble context.*/
    decoding_context decoding_context = { 0 };
    decoding_context.disassembler_context = context;
    decoding_context.effective_address_size_attribute = 
        context->entry_point.address_size_attribute;
    decoding_context.effective_operand_size_attribute = 
        context->entry_point.operand_size_attribute;

    decoding_context.stream = &stream;

    error = decode_prefixes(&decoding_context);
    if (error) {
        return error;
    }

    error = decode_instruction(&decoding_context);

    if (!error) {

        /* Copy potential errors.*/
        result->errors = decoding_context.errors;

        fcml_st_instruction *inst = &(result->instruction);
        fcml_st_instruction_details *inst_details = 
            &(result->instruction_details);

        fcml_usize memory_data_size = 0;

        /* Prepare operands.*/
        fcml_int i;
        for (i = 0; i < FCML_OPERANDS_COUNT; i++) {
            operand_wrapper *operand_wrapper = 
                &(decoding_context.operand_wrappers[i]);
            if (operand_wrapper->operand.type != FCML_OT_NONE) {
                if (operand_wrapper->operand.type == FCML_OT_ADDRESS) {
                    memory_data_size = 
                        operand_wrapper->operand.address.size_operator;
                }
                inst->operands[i] = operand_wrapper->operand;
                inst_details->operand_details[i].access_mode = 
                    operand_wrapper->access_mode;
            } else {
                break;
            }
        }

        inst->operands_count = i;

        /* ModR/M details.*/
        fcml_st_decoded_modrm_details *modrm_details = 
            &(inst_details->modrm_details);

        modrm_details->modrm = decoding_context.decoded_modrm_details.modrm;
        modrm_details->sib = decoding_context.decoded_modrm_details.sib;
        modrm_details->is_rip = decoding_context.decoded_modrm.is_rip;
        modrm_details->is_modrm = decoding_context.is_modrm;

        fcml_st_modrm_displacement *disp =
                &(decoding_context.decoded_modrm_details.displacement);

        modrm_details->displacement.displacement = disp->displacement;
        modrm_details->displacement.N = disp->N;

        /* Prefixes.*/
        inst_details->prefixes_details = decoding_context.prefixes;
        inst->prefixes = convert_prefixes_to_generic_prefixes(
                    &(decoding_context.prefixes));

        /* Copy instruction hints.*/
        inst->hints = decoding_context.instruction_hints;

        /* Instruction code.*/
        inst_details->instruction_size = 
            decoding_context.calculated_instruction_size;
        fcml_fn_env_memory_copy(&inst_details->instruction_code, 
                context->code,
                inst_details->instruction_size > FCML_INSTRUCTION_SIZE ?
                FCML_INSTRUCTION_SIZE : inst_details->instruction_size);

        /* Conditions.*/
        if (decoding_context.is_conditional) {
            inst->is_conditional = FCML_TRUE;
            inst->condition = decoding_context.condition;
        } else {
            inst->is_conditional = FCML_FALSE;
        }

        /* Opcode fields.*/
        inst_details->opcode_field_s_bit = 
            decoding_context.opcode_field_s_bit;
        inst_details->opcode_field_w_bit = 
            decoding_context.opcode_field_w_bit;

        /* Instruction code. */
        inst_details->instruction = decoding_context.instruction;
        inst_details->addr_mode = decoding_context.addr_mode;
        inst_details->instruction_group = 
            decoding_context.instruction_group;

        /* L'L flag for mnemonic chooser.*/
        fcml_nuint8_t l;
        l.is_not_null = FCML_FALSE;
        if (inst_details->prefixes_details.is_avx) {
            l.is_not_null = FCML_TRUE;
            l.value = inst_details->prefixes_details.L_prim << 1 |
                    inst_details->prefixes_details.L;
        }

        fcml_st_mp_mnemonic *mnemonic = NULL;

        if (decoding_context.pseudo_op) {

            /* Gets mnemonic for pseudo operation. */
            inst->mnemonic = int_disasm->dialect_context->
                get_pseudo_op_mnemonic(decoding_context.pseudo_op);
            inst_details->pseudo_op = decoding_context.pseudo_op;

        } else {

            /* Mnemonic for real assembler instruction. */
            fcml_bool shortform = decoding_context.disassembler_context->
                configuration.short_forms;

            fcml_st_mp_config mp_config;
            mp_config.effective_asa = 
                decoding_context.effective_address_size_attribute;
            mp_config.effective_osa = 
                decoding_context.effective_operand_size_attribute;
            mp_config.is_memory = 
                (decoding_context.decoded_modrm.address.address_form != 
                 FCML_AF_UNDEFINED && 
                 !decoding_context.decoded_modrm.reg.is_not_null);
            mp_config.memory_data_size = memory_data_size;
            mp_config.use_shortcut = shortform;
            mp_config.pseudo_opcode = decoding_context.pseudo_opcode;
            mp_config.suffix = decoding_context.suffix;
            mp_config.l = l;

            mnemonic = fcml_fn_mp_choose_mnemonic(decoding_context.mnemonics, 
                    &mp_config);
            if (mnemonic) {
                inst_details->is_pseudo_op = mnemonic->pseudo_op.is_not_null;
                inst_details->is_shortcut = mnemonic->is_shortcut && shortform;
                /* Render mnemonic using provided dialect. */
                inst->mnemonic = 
                    int_disasm->dialect_context->render_mnemonic(
                            mnemonic->mnemonic, decoding_context.is_conditional
                                ? &(decoding_context.condition) : NULL, 
                            context->configuration.conditional_group,
                            context->configuration.
                                carry_flag_conditional_suffix);
            } else {
                /* Mnemonic not found.*/
                FCML_TRACE_MSG("Can not choose mnemonic for disassembled \
                        instruction.");
                return FCML_CEH_GEC_INTERNAL_ERROR;
            }

        }

        /* avx-512 */
        inst_details->tuple_type = decoding_context.tuple_type;

        /* Clean operands for short forms.*/
        clean_operands_for_short_forms(inst, inst_details);

        /* Increment IP */
        if (context->configuration.increment_ip) {
            fcml_usize size = result->instruction_details.instruction_size;
            context->entry_point.ip += size;
            // Skip to the next instruction.
            fcml_uint8_t *instruction_code = (fcml_uint8_t *)context->code;
            instruction_code += size;
            context->code = instruction_code;
            context->code_length -= (context->code_length >= size) 
                ? size : context->code_length;
        }

        /* Execute disassembler post processor if needed.*/
        fcml_fnp_disasm_postprocessor post_processor 
            = int_disasm->dialect_context->disasm_postprocessor;
        if (post_processor) {
            post_processor(mnemonic, result);
        }

    } else if (decoding_context.errors.errors) {
        /* If there are any errors, return them back to the user.*/
        result->errors = decoding_context.errors;
    }

    return error;
}

/****************************
 * API.
 ****************************/

fcml_ceh_error LIB_CALL fcml_fn_disassembler_init(
        const fcml_st_dialect *dialect,
        fcml_st_disassembler **disasm) {

    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

    FCML_ENV_ALLOC_CLEAR(int_disasm, disassembler);
    if (int_disasm) {

        int_disasm->dialect_context = (fcml_st_dialect_context_int*) dialect;
        error = fcml_fn_dt_dts_tree_init(
                (fcml_st_dialect_context_int*)dialect,
                &(int_disasm->decoding_tree),
                &prepare_inst_def_callback_default,
                &dispose_inst_def_callback_default);
        if (!error) {
            *disasm = (fcml_st_disassembler*) int_disasm;
        }

    } else {
        error = FCML_CEH_GEC_OUT_OF_MEMORY;
    }

    return error;
}

void LIB_CALL fcml_fn_disassembler_result_prepare(
        fcml_st_disassembler_result *result) {
    if (result) {
        /* Clean result container. */
        fcml_fn_env_memory_clear(result, sizeof(fcml_st_disassembler_result));
    }
}


fcml_ceh_error LIB_CALL fcml_fn_disassemble(
        fcml_st_disassembler_context *context, 
        fcml_st_disassembler_result *result) {

    // Sanity check.
    if (!context || !result) {
        return FCML_CEH_GEC_INVALID_INPUT;
    }

    if(!context->code_length) {
        return FCML_CEH_GEC_EOF;
    }

    /* Check if there is something already available in result, and free 
     * it in such cache.
     */
    fcml_fn_disassembler_result_free(result);

    fcml_ceh_error error = disassemble_core(context, result);
    if (error) {
        // Try to convert error code to error message if there is such need.
        fcml_fn_utils_conv_gec_to_error_info(
                context->configuration.enable_error_messages, 
                &(result->errors), error);
    }

    return error;
}

void LIB_CALL fcml_fn_disassembler_result_free(
        fcml_st_disassembler_result *result) {

    if (result) {
        /* Free all error messages. */
        fcml_fn_ceh_free_errors_only(&(result->errors));

        /* Mnemonic is allocated by dialect and has to be also free'd. */
        if (result->instruction.mnemonic) {
            fcml_fn_env_str_strfree(result->instruction.mnemonic);
        }

        /* Clean all information inside result. */
        fcml_fn_disassembler_result_prepare(result);
    }
}

void LIB_CALL fcml_fn_disassembler_free(fcml_st_disassembler *disasm) {
    disassembler *dec_disasm = (disassembler*)disasm;
    if (dec_disasm) {
        if (dec_disasm->decoding_tree) {
            fcml_fn_dt_dts_tree_free(dec_disasm->dialect_context, 
                    dec_disasm->decoding_tree);
        }
        fcml_fn_env_memory_free(dec_disasm);
    }
}
