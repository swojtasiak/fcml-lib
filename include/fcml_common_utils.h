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

/** @file fcml_common_utils.h
 *
 * Common general purpose utility functions.
 *
 * @copyright Copyright (C) 2010-2020 Slawomir Wojtasiak. All rights reserved.
 * This project is released under the GNU Lesser General Public License.
 */

#ifndef FCML_COMMON_UTILS_H_
#define FCML_COMMON_UTILS_H_

#include "fcml_lib_export.h"

#include "fcml_common.h"
#include "fcml_assembler.h"
#include "fcml_disassembler.h"
#include "fcml_instructions.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup REG_STRUCTURES_GROUP Registers
 * Declarations of structures describing all available registers.
 * @{
 */

extern LIB_EXPORT fcml_st_register fcml_reg_AL;
extern LIB_EXPORT fcml_st_register fcml_reg_AX;
extern LIB_EXPORT fcml_st_register fcml_reg_EAX;
extern LIB_EXPORT fcml_st_register fcml_reg_RAX;
extern LIB_EXPORT fcml_st_register fcml_reg_MM0;
extern LIB_EXPORT fcml_st_register fcml_reg_XMM0;
extern LIB_EXPORT fcml_st_register fcml_reg_YMM0;
extern LIB_EXPORT fcml_st_register fcml_reg_ZMM0;

extern LIB_EXPORT fcml_st_register fcml_reg_CL;
extern LIB_EXPORT fcml_st_register fcml_reg_CX;
extern LIB_EXPORT fcml_st_register fcml_reg_ECX;
extern LIB_EXPORT fcml_st_register fcml_reg_RCX;
extern LIB_EXPORT fcml_st_register fcml_reg_MM1;
extern LIB_EXPORT fcml_st_register fcml_reg_XMM1;
extern LIB_EXPORT fcml_st_register fcml_reg_YMM1;
extern LIB_EXPORT fcml_st_register fcml_reg_ZMM1;

extern LIB_EXPORT fcml_st_register fcml_reg_DL;
extern LIB_EXPORT fcml_st_register fcml_reg_DX;
extern LIB_EXPORT fcml_st_register fcml_reg_EDX;
extern LIB_EXPORT fcml_st_register fcml_reg_RDX;
extern LIB_EXPORT fcml_st_register fcml_reg_MM2;
extern LIB_EXPORT fcml_st_register fcml_reg_XMM2;
extern LIB_EXPORT fcml_st_register fcml_reg_YMM2;
extern LIB_EXPORT fcml_st_register fcml_reg_ZMM2;

extern LIB_EXPORT fcml_st_register fcml_reg_BL;
extern LIB_EXPORT fcml_st_register fcml_reg_BX;
extern LIB_EXPORT fcml_st_register fcml_reg_EBX;
extern LIB_EXPORT fcml_st_register fcml_reg_RBX;
extern LIB_EXPORT fcml_st_register fcml_reg_MM3;
extern LIB_EXPORT fcml_st_register fcml_reg_XMM3;
extern LIB_EXPORT fcml_st_register fcml_reg_YMM3;
extern LIB_EXPORT fcml_st_register fcml_reg_ZMM3;

extern LIB_EXPORT fcml_st_register fcml_reg_AH;
extern LIB_EXPORT fcml_st_register fcml_reg_SPL;
extern LIB_EXPORT fcml_st_register fcml_reg_SP;
extern LIB_EXPORT fcml_st_register fcml_reg_ESP;
extern LIB_EXPORT fcml_st_register fcml_reg_RSP;
extern LIB_EXPORT fcml_st_register fcml_reg_MM4;
extern LIB_EXPORT fcml_st_register fcml_reg_XMM4;
extern LIB_EXPORT fcml_st_register fcml_reg_YMM4;
extern LIB_EXPORT fcml_st_register fcml_reg_ZMM4;

extern LIB_EXPORT fcml_st_register fcml_reg_CH;
extern LIB_EXPORT fcml_st_register fcml_reg_BPL;
extern LIB_EXPORT fcml_st_register fcml_reg_BP;
extern LIB_EXPORT fcml_st_register fcml_reg_EBP;
extern LIB_EXPORT fcml_st_register fcml_reg_RBP;
extern LIB_EXPORT fcml_st_register fcml_reg_MM5;
extern LIB_EXPORT fcml_st_register fcml_reg_XMM5;
extern LIB_EXPORT fcml_st_register fcml_reg_YMM5;
extern LIB_EXPORT fcml_st_register fcml_reg_ZMM5;

extern LIB_EXPORT fcml_st_register fcml_reg_DH;
extern LIB_EXPORT fcml_st_register fcml_reg_SIL;
extern LIB_EXPORT fcml_st_register fcml_reg_SI;
extern LIB_EXPORT fcml_st_register fcml_reg_ESI;
extern LIB_EXPORT fcml_st_register fcml_reg_RSI;
extern LIB_EXPORT fcml_st_register fcml_reg_MM6;
extern LIB_EXPORT fcml_st_register fcml_reg_XMM6;
extern LIB_EXPORT fcml_st_register fcml_reg_YMM6;
extern LIB_EXPORT fcml_st_register fcml_reg_ZMM6;

extern LIB_EXPORT fcml_st_register fcml_reg_BH;
extern LIB_EXPORT fcml_st_register fcml_reg_DIL;
extern LIB_EXPORT fcml_st_register fcml_reg_DI;
extern LIB_EXPORT fcml_st_register fcml_reg_EDI;
extern LIB_EXPORT fcml_st_register fcml_reg_RDI;
extern LIB_EXPORT fcml_st_register fcml_reg_MM7;
extern LIB_EXPORT fcml_st_register fcml_reg_XMM7;
extern LIB_EXPORT fcml_st_register fcml_reg_YMM7;
extern LIB_EXPORT fcml_st_register fcml_reg_ZMM7;

extern LIB_EXPORT fcml_st_register fcml_reg_R8L;
extern LIB_EXPORT fcml_st_register fcml_reg_R8W;
extern LIB_EXPORT fcml_st_register fcml_reg_R8D;
extern LIB_EXPORT fcml_st_register fcml_reg_R8;
extern LIB_EXPORT fcml_st_register fcml_reg_XMM8;
extern LIB_EXPORT fcml_st_register fcml_reg_YMM8;
extern LIB_EXPORT fcml_st_register fcml_reg_ZMM8;

extern LIB_EXPORT fcml_st_register fcml_reg_R9L;
extern LIB_EXPORT fcml_st_register fcml_reg_R9W;
extern LIB_EXPORT fcml_st_register fcml_reg_R9D;
extern LIB_EXPORT fcml_st_register fcml_reg_R9;
extern LIB_EXPORT fcml_st_register fcml_reg_XMM9;
extern LIB_EXPORT fcml_st_register fcml_reg_YMM9;
extern LIB_EXPORT fcml_st_register fcml_reg_ZMM9;

extern LIB_EXPORT fcml_st_register fcml_reg_R10L;
extern LIB_EXPORT fcml_st_register fcml_reg_R10W;
extern LIB_EXPORT fcml_st_register fcml_reg_R10D;
extern LIB_EXPORT fcml_st_register fcml_reg_R10;
extern LIB_EXPORT fcml_st_register fcml_reg_XMM10;
extern LIB_EXPORT fcml_st_register fcml_reg_YMM10;
extern LIB_EXPORT fcml_st_register fcml_reg_ZMM10;

extern LIB_EXPORT fcml_st_register fcml_reg_R11L;
extern LIB_EXPORT fcml_st_register fcml_reg_R11W;
extern LIB_EXPORT fcml_st_register fcml_reg_R11D;
extern LIB_EXPORT fcml_st_register fcml_reg_R11;
extern LIB_EXPORT fcml_st_register fcml_reg_XMM11;
extern LIB_EXPORT fcml_st_register fcml_reg_YMM11;
extern LIB_EXPORT fcml_st_register fcml_reg_ZMM11;

extern LIB_EXPORT fcml_st_register fcml_reg_R12L;
extern LIB_EXPORT fcml_st_register fcml_reg_R12W;
extern LIB_EXPORT fcml_st_register fcml_reg_R12D;
extern LIB_EXPORT fcml_st_register fcml_reg_R12;
extern LIB_EXPORT fcml_st_register fcml_reg_XMM12;
extern LIB_EXPORT fcml_st_register fcml_reg_YMM12;
extern LIB_EXPORT fcml_st_register fcml_reg_ZMM12;

extern LIB_EXPORT fcml_st_register fcml_reg_R13L;
extern LIB_EXPORT fcml_st_register fcml_reg_R13W;
extern LIB_EXPORT fcml_st_register fcml_reg_R13D;
extern LIB_EXPORT fcml_st_register fcml_reg_R13;
extern LIB_EXPORT fcml_st_register fcml_reg_XMM13;
extern LIB_EXPORT fcml_st_register fcml_reg_YMM13;
extern LIB_EXPORT fcml_st_register fcml_reg_ZMM13;

extern LIB_EXPORT fcml_st_register fcml_reg_R14L;
extern LIB_EXPORT fcml_st_register fcml_reg_R14W;
extern LIB_EXPORT fcml_st_register fcml_reg_R14D;
extern LIB_EXPORT fcml_st_register fcml_reg_R14;
extern LIB_EXPORT fcml_st_register fcml_reg_XMM14;
extern LIB_EXPORT fcml_st_register fcml_reg_YMM14;
extern LIB_EXPORT fcml_st_register fcml_reg_ZMM14;

extern LIB_EXPORT fcml_st_register fcml_reg_R15L;
extern LIB_EXPORT fcml_st_register fcml_reg_R15W;
extern LIB_EXPORT fcml_st_register fcml_reg_R15D;
extern LIB_EXPORT fcml_st_register fcml_reg_R15;
extern LIB_EXPORT fcml_st_register fcml_reg_XMM15;
extern LIB_EXPORT fcml_st_register fcml_reg_YMM15;
extern LIB_EXPORT fcml_st_register fcml_reg_ZMM15;

extern LIB_EXPORT fcml_st_register fcml_reg_XMM16;
extern LIB_EXPORT fcml_st_register fcml_reg_YMM16;
extern LIB_EXPORT fcml_st_register fcml_reg_ZMM16;

extern LIB_EXPORT fcml_st_register fcml_reg_XMM17;
extern LIB_EXPORT fcml_st_register fcml_reg_YMM17;
extern LIB_EXPORT fcml_st_register fcml_reg_ZMM17;

extern LIB_EXPORT fcml_st_register fcml_reg_XMM18;
extern LIB_EXPORT fcml_st_register fcml_reg_YMM18;
extern LIB_EXPORT fcml_st_register fcml_reg_ZMM18;

extern LIB_EXPORT fcml_st_register fcml_reg_XMM19;
extern LIB_EXPORT fcml_st_register fcml_reg_YMM19;
extern LIB_EXPORT fcml_st_register fcml_reg_ZMM19;

extern LIB_EXPORT fcml_st_register fcml_reg_XMM20;
extern LIB_EXPORT fcml_st_register fcml_reg_YMM20;
extern LIB_EXPORT fcml_st_register fcml_reg_ZMM20;

extern LIB_EXPORT fcml_st_register fcml_reg_XMM21;
extern LIB_EXPORT fcml_st_register fcml_reg_YMM21;
extern LIB_EXPORT fcml_st_register fcml_reg_ZMM21;

extern LIB_EXPORT fcml_st_register fcml_reg_XMM22;
extern LIB_EXPORT fcml_st_register fcml_reg_YMM22;
extern LIB_EXPORT fcml_st_register fcml_reg_ZMM22;

extern LIB_EXPORT fcml_st_register fcml_reg_XMM23;
extern LIB_EXPORT fcml_st_register fcml_reg_YMM23;
extern LIB_EXPORT fcml_st_register fcml_reg_ZMM23;

extern LIB_EXPORT fcml_st_register fcml_reg_XMM24;
extern LIB_EXPORT fcml_st_register fcml_reg_YMM24;
extern LIB_EXPORT fcml_st_register fcml_reg_ZMM24;

extern LIB_EXPORT fcml_st_register fcml_reg_XMM25;
extern LIB_EXPORT fcml_st_register fcml_reg_YMM25;
extern LIB_EXPORT fcml_st_register fcml_reg_ZMM25;

extern LIB_EXPORT fcml_st_register fcml_reg_XMM26;
extern LIB_EXPORT fcml_st_register fcml_reg_YMM26;
extern LIB_EXPORT fcml_st_register fcml_reg_ZMM26;

extern LIB_EXPORT fcml_st_register fcml_reg_XMM27;
extern LIB_EXPORT fcml_st_register fcml_reg_YMM27;
extern LIB_EXPORT fcml_st_register fcml_reg_ZMM27;

extern LIB_EXPORT fcml_st_register fcml_reg_XMM28;
extern LIB_EXPORT fcml_st_register fcml_reg_YMM28;
extern LIB_EXPORT fcml_st_register fcml_reg_ZMM28;

extern LIB_EXPORT fcml_st_register fcml_reg_XMM29;
extern LIB_EXPORT fcml_st_register fcml_reg_YMM29;
extern LIB_EXPORT fcml_st_register fcml_reg_ZMM29;

extern LIB_EXPORT fcml_st_register fcml_reg_XMM30;
extern LIB_EXPORT fcml_st_register fcml_reg_YMM30;
extern LIB_EXPORT fcml_st_register fcml_reg_ZMM30;

extern LIB_EXPORT fcml_st_register fcml_reg_XMM31;
extern LIB_EXPORT fcml_st_register fcml_reg_YMM31;
extern LIB_EXPORT fcml_st_register fcml_reg_ZMM31;

extern LIB_EXPORT fcml_st_register fcml_reg_ES;
extern LIB_EXPORT fcml_st_register fcml_reg_CS;
extern LIB_EXPORT fcml_st_register fcml_reg_SS;
extern LIB_EXPORT fcml_st_register fcml_reg_DS;
extern LIB_EXPORT fcml_st_register fcml_reg_FS;
extern LIB_EXPORT fcml_st_register fcml_reg_GS;

extern LIB_EXPORT fcml_st_register fcml_reg_ST0;
extern LIB_EXPORT fcml_st_register fcml_reg_ST1;
extern LIB_EXPORT fcml_st_register fcml_reg_ST2;
extern LIB_EXPORT fcml_st_register fcml_reg_ST3;
extern LIB_EXPORT fcml_st_register fcml_reg_ST4;
extern LIB_EXPORT fcml_st_register fcml_reg_ST5;
extern LIB_EXPORT fcml_st_register fcml_reg_ST6;
extern LIB_EXPORT fcml_st_register fcml_reg_ST7;

extern LIB_EXPORT fcml_st_register fcml_reg_CR0;
extern LIB_EXPORT fcml_st_register fcml_reg_CR2;
extern LIB_EXPORT fcml_st_register fcml_reg_CR3;
extern LIB_EXPORT fcml_st_register fcml_reg_CR4;
extern LIB_EXPORT fcml_st_register fcml_reg_CR8;

extern LIB_EXPORT fcml_st_register fcml_reg_DR0;
extern LIB_EXPORT fcml_st_register fcml_reg_DR1;
extern LIB_EXPORT fcml_st_register fcml_reg_DR2;
extern LIB_EXPORT fcml_st_register fcml_reg_DR3;
extern LIB_EXPORT fcml_st_register fcml_reg_DR4;
extern LIB_EXPORT fcml_st_register fcml_reg_DR5;
extern LIB_EXPORT fcml_st_register fcml_reg_DR6;
extern LIB_EXPORT fcml_st_register fcml_reg_DR7;

extern LIB_EXPORT fcml_st_register fcml_reg_K0;
extern LIB_EXPORT fcml_st_register fcml_reg_K1;
extern LIB_EXPORT fcml_st_register fcml_reg_K2;
extern LIB_EXPORT fcml_st_register fcml_reg_K3;
extern LIB_EXPORT fcml_st_register fcml_reg_K4;
extern LIB_EXPORT fcml_st_register fcml_reg_K5;
extern LIB_EXPORT fcml_st_register fcml_reg_K6;
extern LIB_EXPORT fcml_st_register fcml_reg_K7;

extern LIB_EXPORT fcml_st_register fcml_reg_IP;
extern LIB_EXPORT fcml_st_register fcml_reg_EIP;
extern LIB_EXPORT fcml_st_register fcml_reg_RIP;

/** @} */

/** Prepares register operand for given register.
 * @param reg Register for instruction operator.
 * @return Prepared operand.
 */
LIB_EXPORT fcml_st_operand LIB_CALL fcml_fn_cu_operand_reg(
        fcml_st_register *reg);

/* IMM.*/

/** Prepares immediate operand for unsigned int8.
 * @param value Value for immediate operand.
 * @return Prepared operand.
 */
LIB_EXPORT fcml_st_operand LIB_CALL fcml_fn_cu_operand_unsigned_imm_8(
        fcml_uint8_t value);
/** Prepares immediate operand for signed int8.
 * @param value Value for immediate operand.
 * @return Prepared operand.
 */
LIB_EXPORT fcml_st_operand LIB_CALL fcml_fn_cu_operand_signed_imm_8(
        fcml_int8_t value);
/** Prepares immediate operand for unsigned int16.
 * @param value Value for immediate operand.
 * @return Prepared operand.
 */
LIB_EXPORT fcml_st_operand LIB_CALL fcml_fn_cu_operand_unsigned_imm_16(
        fcml_uint16_t value);
/** Prepares immediate operand for signed int16.
 * @param value Value for immediate operand.
 * @return Prepared operand.
 */
LIB_EXPORT fcml_st_operand LIB_CALL fcml_fn_cu_operand_signed_imm_16(
        fcml_int16_t value);
/** Prepares immediate operand for unsigned int32.
 * @param value Value for immediate operand.
 * @return Prepared operand.
 */
LIB_EXPORT fcml_st_operand LIB_CALL fcml_fn_cu_operand_unsigned_imm_32(
        fcml_uint32_t value);
/** Prepares immediate operand for signed int32.
 * @param value Value for immediate operand.
 * @return Prepared operand.
 */
LIB_EXPORT fcml_st_operand LIB_CALL fcml_fn_cu_operand_signed_imm_32(
        fcml_int32_t value);
/** Prepares immediate operand for unsigned int64.
 * @param value Value for immediate operand.
 * @return Prepared operand.
 */
LIB_EXPORT fcml_st_operand LIB_CALL fcml_fn_cu_operand_unsigned_imm_64(
        fcml_uint64_t value);
/** Prepares immediate operand for signed int64.
 * @param value Value for immediate operand.
 * @return Prepared operand.
 */
LIB_EXPORT fcml_st_operand LIB_CALL fcml_fn_cu_operand_signed_imm_64(
        fcml_int64_t value);

/* Memory addressing.*/

/** Prepares far pointer operand for given segment and offset.
 * @param seg 16-bit code segment.
 * @param offset 16-bit code offset.
 * @return Prepared operand.
 */
LIB_EXPORT fcml_st_operand LIB_CALL fcml_fn_cu_operand_addr_far_pointer_offset16(
        fcml_int16_t seg, fcml_int16_t offset);
/** Prepares far pointer operand for given segment and offset.
 * @param seg 16-bit code segment.
 * @param offset 32-bit code offset.
 * @return Prepared operand.
 */
LIB_EXPORT fcml_st_operand LIB_CALL fcml_fn_cu_operand_addr_far_pointer_offset32(
        fcml_int16_t seg, fcml_int32_t offset);
/** Prepares memory addressing operand for 16-bit absolute offset.
 * @param offset 16-bit absolute offset.
 * @param size_operator Size operator.
 * @return Prepared operand.
 */
LIB_EXPORT fcml_st_operand LIB_CALL fcml_fn_cu_operand_addr_offset_16(
        fcml_int16_t offset, fcml_usize size_operator);
/** Prepares memory addressing operand for 32-bit absolute offset.
 * @param offset 32-bit absolute offset.
 * @param size_operator Size operator.
 * @return Prepared operand.
 */
LIB_EXPORT fcml_st_operand LIB_CALL fcml_fn_cu_operand_addr_offset_32(
        fcml_int32_t offset, fcml_usize size_operator);
/** Prepares memory addressing operand for 64-bit absolute offset. Function
 *  sets operand level hint: FCML_OP_HINT_ABSOLUTE_ADDRESSING.
 * @param offset 64-bit absolute offset.
 * @param size_operator Size operator.
 * @return Prepared operand.
 * @see RIP addressing.
 */
LIB_EXPORT fcml_st_operand LIB_CALL fcml_fn_cu_operand_addr_offset_abs_64(
        fcml_int64_t offset, fcml_usize size_operator);
/** Prepares memory addressing operand for 64-bit absolute offset. Function
 * sets operand level hint: FCML_OP_HINT_RELATIVE_ADDRESSING.
 * @param offset 64-bit absolute offset.
 * @param size_operator Size operator.
 * @return Prepared operand.
 * @see RIP addressing.
 */
LIB_EXPORT fcml_st_operand LIB_CALL fcml_fn_cu_operand_addr_offset_rel_64(
        fcml_int64_t offset, fcml_usize size_operator);
/** Prepares effective memory addressing operand for 16-bit displacement.
 * @param disp 16-bit displacement.
 * @param size_operator Size operator.
 * @return Prepared operand.
 */
LIB_EXPORT fcml_st_operand LIB_CALL fcml_fn_cu_operand_addr_disp_16(
        fcml_int16_t disp, fcml_usize size_operator);
/** Prepares effective memory addressing operand for 32-bit displacement.
 * @param disp 32-bit displacement.
 * @param size_operator Size operator.
 * @return Prepared operand.
 */
LIB_EXPORT fcml_st_operand LIB_CALL fcml_fn_cu_operand_addr_disp_32(
        fcml_int32_t disp, fcml_usize size_operator);
/** Prepares effective memory addressing operand for 64-bit displacement.
 * @param disp 64-bit displacement.
 * @param size_operator Size operator.
 * @return Prepared operand.
 */
LIB_EXPORT fcml_st_operand LIB_CALL fcml_fn_cu_operand_addr_disp_64(
        fcml_int64_t disp, fcml_usize size_operator);
/** Prepares effective memory addressing operand for 8-bit displacement
 *  and base register.
 * @param base Base register.
 * @param disp 8-bit displacement.
 * @param size_operator Size operator.
 * @return Prepared operand.
 */
LIB_EXPORT fcml_st_operand LIB_CALL fcml_fn_cu_operand_addr_b_disp_8(
        fcml_st_register *base, fcml_int8_t disp, fcml_usize size_operator);
/** Prepares effective memory addressing operand for 16-bit displacement
 *  and base register.
 * @param base Base register.
 * @param disp 16-bit displacement.
 * @param size_operator Size operator.
 * @return Prepared operand.
 */
LIB_EXPORT fcml_st_operand LIB_CALL fcml_fn_cu_operand_addr_b_disp_16(
        fcml_st_register *base, fcml_int16_t disp, fcml_usize size_operator);
/** Prepares effective memory addressing operand for 32-bit displacement
 *  and base register.
 * @param base Base register.
 * @param disp 32-bit displacement.
 * @param size_operator Size operator.
 * @return Prepared operand.
 */
LIB_EXPORT fcml_st_operand LIB_CALL fcml_fn_cu_operand_addr_b_disp_32(
        fcml_st_register *base, fcml_int32_t disp, fcml_usize size_operator);
/** Prepares effective memory addressing operand for 64-bit displacement
 *  and base register.
 * @param base Base register.
 * @param disp 64-bit displacement.
 * @param size_operator Size operator.
 * @return Prepared operand.
 */
LIB_EXPORT fcml_st_operand LIB_CALL fcml_fn_cu_operand_addr_b_disp_64(
        fcml_st_register *base, fcml_int64_t disp, fcml_usize size_operator);
/** Prepares effective memory addressing operand for 8-bit displacement,
 *  scale factor and index register.
 * @param index Index register.
 * @param scale_factor Scale factor.
 * @param disp 8-bit displacement.
 * @param size_operator Size operator.
 * @return Prepared operand.
 */
LIB_EXPORT fcml_st_operand LIB_CALL fcml_fn_cu_operand_addr_is_disp_8(
        fcml_st_register *index, fcml_uint8_t scale_factor, fcml_int8_t disp,
        fcml_usize size_operator);
/** Prepares effective memory addressing operand for 16-bit displacement,
 *  scale factor and index register.
 * @param index Index register.
 * @param scale_factor Scale factor.
 * @param disp 16-bit displacement.
 * @param size_operator Size operator.
 * @return Prepared operand.
 */
LIB_EXPORT fcml_st_operand LIB_CALL fcml_fn_cu_operand_addr_is_disp_32(
        fcml_st_register *index, fcml_uint8_t scale_factor, fcml_int32_t disp,
        fcml_usize size_operator);
/** Prepares effective memory addressing operand for 32-bit displacement,
 *  scale factor and index register.
 * @param index Index register.
 * @param scale_factor Scale factor.
 * @param disp 32-bit displacement.
 * @param size_operator Size operator.
 * @return Prepared operand.
 */
LIB_EXPORT fcml_st_operand LIB_CALL fcml_fn_cu_operand_addr_is_disp_64(
        fcml_st_register *index, fcml_uint8_t scale_factor, fcml_int64_t disp,
        fcml_usize size_operator);
/** Prepares effective memory addressing operand for 8-bit displacement,
 *  base register, scale factor and index register.
 * @param base Base register.
 * @param index Index register.
 * @param scale_factor Scale factor.
 * @param disp 8-bit displacement.
 * @param size_operator Size operator.
 * @return Prepared operand.
 */
LIB_EXPORT fcml_st_operand LIB_CALL fcml_fn_cu_operand_addr_bis_disp_8(
        fcml_st_register *base, fcml_st_register *index,
        fcml_uint8_t scale_factor, fcml_int8_t disp, fcml_usize size_operator);
/** Prepares effective memory addressing operand for 16-bit displacement,
 *  base register, scale factor and index register.
 * @param base Base register.
 * @param index Index register.
 * @param scale_factor Scale factor.
 * @param disp 16-bit displacement.
 * @param size_operator Size operator.
 * @return Prepared operand.
 */
LIB_EXPORT fcml_st_operand LIB_CALL fcml_fn_cu_operand_addr_bis_disp_32(
        fcml_st_register *base, fcml_st_register *index,
        fcml_uint8_t scale_factor, fcml_int32_t disp, fcml_usize size_operator);
/** Prepares effective memory addressing operand for 32-bit displacement,
 *  base register, scale factor and index register.
 * @param base Base register.
 * @param index Index register.
 * @param scale_factor Scale factor.
 * @param disp 32-bit displacement.
 * @param size_operator Size operator.
 * @return Prepared operand.
 */
LIB_EXPORT fcml_st_operand LIB_CALL fcml_fn_cu_operand_addr_bis_disp_64(
        fcml_st_register *base, fcml_st_register *index,
        fcml_uint8_t scale_factor, fcml_int64_t disp, fcml_usize size_operator);

/** Adds hints to the operand.
 * @param operand Operand for hints.
 * @param hints Hints mask.
 * @return Prepared operand.
 */
LIB_EXPORT fcml_st_operand LIB_CALL fcml_fn_cu_add_operand_hints(
        fcml_st_operand operand, fcml_hints hints);

/** Clones given instruction.
 * Allocates new instance of instruction and makes a deep copy of
 * all fields. Remember that cloned instructions have to be freed
 * using fcml_fn_cu_free_instruction() function. Do not try to free
 * it on your own because it might be allocated on different
 * dedicated memory heap.
 * @param instruction Instruction to be cloned.
 * @return Cloned instruction.
 */
LIB_EXPORT fcml_st_instruction* LIB_CALL fcml_fn_cu_clone_instruction(
        fcml_st_instruction *instruction);

/** Frees given instruction.
 * Frees instruction allocated by fcml_fn_cu_clone_instruction() function.
 * @param instruction Instruction to be freed.
 */
LIB_EXPORT void LIB_CALL fcml_fn_cu_free_instruction(
        fcml_st_instruction *instruction);

/** Gets operand of given type or NULL if there is no such operand.
 * If more than one operand of given type exist, the first one is returned.
 * @param instruction Finds an operand of the given type for for
 *  given instruction.
 * @param operand_type Operand type.
 * @return Pointer to the operand of given type.
 */
LIB_EXPORT fcml_st_operand* fcml_fn_cu_find_operand(
        fcml_st_instruction *instruction, fcml_en_operand_type operand_type);

/* Some shortcuts for those who prefer to use macros instead of functions.*/

#define FCML_IMM8_S( x )		fcml_fn_cu_operand_signed_imm_8( x )
#define FCML_IMM8( x )			fcml_fn_cu_operand_unsigned_imm_8( x )
#define FCML_IMM16_S( x )		fcml_fn_cu_operand_signed_imm_16( x )
#define FCML_IMM16( x )			fcml_fn_cu_operand_unsigned_imm_16( x )
#define FCML_IMM32_S( x )		fcml_fn_cu_operand_signed_imm_32( x )
#define FCML_IMM32( x )			fcml_fn_cu_operand_unsigned_imm_32( x )
#define FCML_IMM64_S( x )		fcml_fn_cu_operand_signed_imm_64( x )
#define FCML_IMM64( x )			fcml_fn_cu_operand_unsigned_imm_64( x )

#ifdef FCML_USE_SHORT_REG
#define FCML_REG( x )			fcml_fn_cu_operand_reg( &fcml_reg_##x )
#else
#define FCML_REG( x )			fcml_fn_cu_operand_reg( &x )
#endif

#define FCML_FAR_POINTER_16( seg, offset ) \
    fcml_fn_cu_operand_addr_far_pointer_offset16( seg, offset )
#define FCML_FAR_POINTER_32( seg, offset ) \
    fcml_fn_cu_operand_addr_far_pointer_offset32( seg, offset )
#define FCML_OFFSET_16( offset )           \
    fcml_fn_cu_operand_addr_offset_16( offset )
#define FCML_OFFSET_32( offset )           \
    fcml_fn_cu_operand_addr_offset_32( offset )
#define FCML_OFFSET_ABS_64( offset )       \
    fcml_fn_cu_operand_addr_offset_abs_64( offset )
#define FCML_OFFSET_REL_64( offset )       \
    fcml_fn_cu_operand_addr_offset_rel_64( offset )
#define FCML_DISP_16( offset )             \
    fcml_fn_cu_operand_addr_disp_16( offset )
#define FCML_DISP_32( offset )             \
    fcml_fn_cu_operand_addr_disp_32( offset )
#define FCML_DISP_64( offset )             \
    fcml_fn_cu_operand_addr_disp_64( offset )

#ifdef FCML_USE_SHORT_REG
#define FCML_B_DISP_8(base, offset) \
fcml_fn_cu_operand_addr_b_disp_8( &fcml_reg_##base, offset )
#define FCML_B_DISP_16(base, offset) \
    fcml_fn_cu_operand_addr_b_disp_16( &fcml_reg_##base, offset )
#define FCML_B_DISP_32(base, offset) \
    fcml_fn_cu_operand_addr_b_disp_32( &fcml_reg_##base, offset )
#define FCML_B_DISP_64(base, offset) \
    fcml_fn_cu_operand_addr_b_disp_64( &fcml_reg_##base, offset )
#define FCML_IS_DISP_8(index, scale, offset) \
    fcml_fn_cu_operand_addr_is_disp_8( &fcml_reg_##index, scale, offset )
#define FCML_IS_DISP_16(index, scale, offset) \
    fcml_fn_cu_operand_addr_is_disp_32( &fcml_reg_##index, scale, offset )
#define FCML_IS_DISP_32(index, scale, offset) \
    fcml_fn_cu_operand_addr_is_disp_64( &fcml_reg_##index, scale, offset )
#define FCML_BIS_DISP_8(base, index, scale, offset) \
    fcml_fn_cu_operand_addr_bis_disp_8( &fcml_reg_##base, &fcml_reg_##index, \
            scale, offset )
#define FCML_BIS_DISP_16(base, index, scale, offset) \
    fcml_fn_cu_operand_addr_bis_disp_32( &fcml_reg_##base, &fcml_reg_##index, \
            scale, offset )
#define FCML_BIS_DISP_32(base, index, scale, offset) \
    fcml_fn_cu_operand_addr_bis_disp_64( &fcml_reg_##base, &fcml_reg_##index, \
            scale, offset )
#else
#define FCML_B_DISP_8(base, offset)                   \
    fcml_fn_cu_operand_addr_b_disp_8( &base, offset )
#define FCML_B_DISP_16(base, offset)                  \
    fcml_fn_cu_operand_addr_b_disp_16( &base, offset )
#define FCML_B_DISP_32(base, offset)                  \
    fcml_fn_cu_operand_addr_b_disp_32( &base, offset )
#define FCML_B_DISP_64(base, offset)                  \
    fcml_fn_cu_operand_addr_b_disp_64( &base, offset )
#define FCML_IS_DISP_8(index, scale, offset)          \
    fcml_fn_cu_operand_addr_is_disp_8( &index, scale, offset )
#define FCML_IS_DISP_16(index, scale, offset)         \
    fcml_fn_cu_operand_addr_is_disp_32( &index, scale, offset )
#define FCML_IS_DISP_32(index, scale, offset)         \
    fcml_fn_cu_operand_addr_is_disp_64( &index, scale, offset )
#define FCML_BIS_DISP_8(base, index, scale, offset)   \
    fcml_fn_cu_operand_addr_bis_disp_8( &base, &index, scale, offset )
#define FCML_BIS_DISP_16(base, index, scale, offset)  \
    fcml_fn_cu_operand_addr_bis_disp_32( &base, &index, scale, offset )
#define FCML_BIS_DISP_32(base, index, scale, offset)  \
    fcml_fn_cu_operand_addr_bis_disp_64( &base, &index, scale, offset )
#endif

#define FCML_IS_INSTRUCTION_GROUP(result, group) \
    ( result.instruction_details.instruction_group & ( group ) )
#define FCML_IS_INSTRUCTION_CODE(result, _ins) \
    ( result.instruction_details.instruction == _ins )

#ifdef __cplusplus
}
#endif

#endif /* FCML_COMMON_UTILS_H_ */
