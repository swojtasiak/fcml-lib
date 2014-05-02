/*
 * FCML - Free Code Manipulation Library.
 * Copyright (C) 2010-2014 Slawomir Wojtasiak
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

#include <fcml_common_utils.h>

#include "fcml_env_int.h"

fcml_st_register fcml_reg_AL = { FCML_REG_GPR, FCML_DS_8, FCML_REG_AL, FCML_FALSE };
fcml_st_register fcml_reg_AX = { FCML_REG_GPR, FCML_DS_16, FCML_REG_AX, FCML_FALSE };
fcml_st_register fcml_reg_EAX = { FCML_REG_GPR, FCML_DS_32, FCML_REG_EAX, FCML_FALSE };
fcml_st_register fcml_reg_RAX = { FCML_REG_GPR, FCML_DS_64, FCML_REG_RAX, FCML_FALSE };
fcml_st_register fcml_reg_MM0 = { FCML_REG_SIMD, FCML_DS_64, FCML_REG_MM0, FCML_FALSE };
fcml_st_register fcml_reg_XMM0 = { FCML_REG_SIMD, FCML_DS_128, FCML_REG_XMM0, FCML_FALSE };
fcml_st_register fcml_reg_YMM0 = { FCML_REG_SIMD, FCML_DS_256, FCML_REG_YMM0, FCML_FALSE };

fcml_st_register fcml_reg_CL = { FCML_REG_GPR, FCML_DS_8, FCML_REG_CL, FCML_FALSE };
fcml_st_register fcml_reg_CX = { FCML_REG_GPR, FCML_DS_16, FCML_REG_CX, FCML_FALSE };
fcml_st_register fcml_reg_ECX = { FCML_REG_GPR, FCML_DS_32, FCML_REG_ECX, FCML_FALSE };
fcml_st_register fcml_reg_RCX = { FCML_REG_GPR, FCML_DS_64, FCML_REG_RCX, FCML_FALSE };
fcml_st_register fcml_reg_MM1 = { FCML_REG_SIMD, FCML_DS_64, FCML_REG_MM1, FCML_FALSE };
fcml_st_register fcml_reg_XMM1 = { FCML_REG_SIMD, FCML_DS_128, FCML_REG_XMM1, FCML_FALSE };
fcml_st_register fcml_reg_YMM1 = { FCML_REG_SIMD, FCML_DS_256, FCML_REG_YMM1, FCML_FALSE };

fcml_st_register fcml_reg_DL = { FCML_REG_GPR, FCML_DS_8, FCML_REG_DL, FCML_FALSE };
fcml_st_register fcml_reg_DX = { FCML_REG_GPR, FCML_DS_16, FCML_REG_DX, FCML_FALSE };
fcml_st_register fcml_reg_EDX = { FCML_REG_GPR, FCML_DS_32, FCML_REG_EDX, FCML_FALSE };
fcml_st_register fcml_reg_RDX = { FCML_REG_GPR, FCML_DS_64, FCML_REG_RDX, FCML_FALSE };
fcml_st_register fcml_reg_MM2 = { FCML_REG_SIMD, FCML_DS_64, FCML_REG_MM2, FCML_FALSE };
fcml_st_register fcml_reg_XMM2 = { FCML_REG_SIMD, FCML_DS_128, FCML_REG_XMM2, FCML_FALSE };
fcml_st_register fcml_reg_YMM2 = { FCML_REG_SIMD, FCML_DS_256, FCML_REG_YMM2, FCML_FALSE };

fcml_st_register fcml_reg_BL = { FCML_REG_GPR, FCML_DS_8, FCML_REG_BL, FCML_FALSE };
fcml_st_register fcml_reg_BX = { FCML_REG_GPR, FCML_DS_16, FCML_REG_BX, FCML_FALSE };
fcml_st_register fcml_reg_EBX = { FCML_REG_GPR, FCML_DS_32, FCML_REG_EBX, FCML_FALSE };
fcml_st_register fcml_reg_RBX = { FCML_REG_GPR, FCML_DS_64, FCML_REG_RBX, FCML_FALSE };
fcml_st_register fcml_reg_MM3 = { FCML_REG_SIMD, FCML_DS_64, FCML_REG_MM3, FCML_FALSE };
fcml_st_register fcml_reg_XMM3 = { FCML_REG_SIMD, FCML_DS_128, FCML_REG_XMM3, FCML_FALSE };
fcml_st_register fcml_reg_YMM3 = { FCML_REG_SIMD, FCML_DS_256, FCML_REG_YMM3, FCML_FALSE };

fcml_st_register fcml_reg_AH = { FCML_REG_GPR, FCML_DS_8, FCML_REG_AH, FCML_FALSE };
fcml_st_register fcml_reg_SPL = { FCML_REG_GPR, FCML_DS_8, FCML_REG_SPL, FCML_TRUE };
fcml_st_register fcml_reg_SP = { FCML_REG_GPR, FCML_DS_16, FCML_REG_SP, FCML_FALSE };
fcml_st_register fcml_reg_ESP = { FCML_REG_GPR, FCML_DS_32, FCML_REG_ESP, FCML_FALSE };
fcml_st_register fcml_reg_RSP = { FCML_REG_GPR, FCML_DS_64, FCML_REG_RSP, FCML_FALSE };
fcml_st_register fcml_reg_MM4 = { FCML_REG_SIMD, FCML_DS_64, FCML_REG_MM4, FCML_FALSE };
fcml_st_register fcml_reg_XMM4 = { FCML_REG_SIMD, FCML_DS_128, FCML_REG_XMM4, FCML_FALSE };
fcml_st_register fcml_reg_YMM4 = { FCML_REG_SIMD, FCML_DS_256, FCML_REG_YMM4, FCML_FALSE };

fcml_st_register fcml_reg_CH = { FCML_REG_GPR, FCML_DS_8, FCML_REG_CH, FCML_FALSE };
fcml_st_register fcml_reg_BPL = { FCML_REG_GPR, FCML_DS_8, FCML_REG_BPL, FCML_TRUE };
fcml_st_register fcml_reg_BP = { FCML_REG_GPR, FCML_DS_16, FCML_REG_BP, FCML_FALSE };
fcml_st_register fcml_reg_EBP = { FCML_REG_GPR, FCML_DS_32, FCML_REG_EBP, FCML_FALSE };
fcml_st_register fcml_reg_RBP = { FCML_REG_GPR, FCML_DS_64, FCML_REG_RBP, FCML_FALSE };
fcml_st_register fcml_reg_MM5 = { FCML_REG_SIMD, FCML_DS_64, FCML_REG_MM5, FCML_FALSE };
fcml_st_register fcml_reg_XMM5 = { FCML_REG_SIMD, FCML_DS_128, FCML_REG_XMM5, FCML_FALSE };
fcml_st_register fcml_reg_YMM5 = { FCML_REG_SIMD, FCML_DS_256, FCML_REG_YMM5, FCML_FALSE };

fcml_st_register fcml_reg_DH = { FCML_REG_GPR, FCML_DS_8, FCML_REG_DH, FCML_FALSE };
fcml_st_register fcml_reg_SIL = { FCML_REG_GPR, FCML_DS_8, FCML_REG_SIL, FCML_TRUE };
fcml_st_register fcml_reg_SI = { FCML_REG_GPR, FCML_DS_16, FCML_REG_SI, FCML_FALSE };
fcml_st_register fcml_reg_ESI = { FCML_REG_GPR, FCML_DS_32, FCML_REG_ESI, FCML_FALSE };
fcml_st_register fcml_reg_RSI = { FCML_REG_GPR, FCML_DS_64, FCML_REG_RSI, FCML_FALSE };
fcml_st_register fcml_reg_MM6 = { FCML_REG_SIMD, FCML_DS_64, FCML_REG_MM6, FCML_FALSE };
fcml_st_register fcml_reg_XMM6 = { FCML_REG_SIMD, FCML_DS_128, FCML_REG_XMM6, FCML_FALSE };
fcml_st_register fcml_reg_YMM6 = { FCML_REG_SIMD, FCML_DS_256, FCML_REG_YMM6, FCML_FALSE };

fcml_st_register fcml_reg_BH = { FCML_REG_GPR, FCML_DS_8, FCML_REG_BH, FCML_FALSE };
fcml_st_register fcml_reg_DIL = { FCML_REG_GPR, FCML_DS_8, FCML_REG_DIL, FCML_TRUE };
fcml_st_register fcml_reg_DI = { FCML_REG_GPR, FCML_DS_16, FCML_REG_DI, FCML_FALSE };
fcml_st_register fcml_reg_EDI = { FCML_REG_GPR, FCML_DS_32, FCML_REG_EDI, FCML_FALSE };
fcml_st_register fcml_reg_RDI = { FCML_REG_GPR, FCML_DS_64, FCML_REG_RDI, FCML_FALSE };
fcml_st_register fcml_reg_MM7 = { FCML_REG_SIMD, FCML_DS_64, FCML_REG_MM7, FCML_FALSE };
fcml_st_register fcml_reg_XMM7 = { FCML_REG_SIMD, FCML_DS_128, FCML_REG_XMM7, FCML_FALSE };
fcml_st_register fcml_reg_YMM7 = { FCML_REG_SIMD, FCML_DS_256, FCML_REG_YMM7, FCML_FALSE };

fcml_st_register fcml_reg_R8L = { FCML_REG_GPR, FCML_DS_8, FCML_REG_R8L, FCML_FALSE };
fcml_st_register fcml_reg_R8W = { FCML_REG_GPR, FCML_DS_16, FCML_REG_R8W, FCML_FALSE };
fcml_st_register fcml_reg_R8D = { FCML_REG_GPR, FCML_DS_32, FCML_REG_R8D, FCML_FALSE };
fcml_st_register fcml_reg_R8 = { FCML_REG_GPR, FCML_DS_64, FCML_REG_R8, FCML_FALSE };
fcml_st_register fcml_reg_XMM8 = { FCML_REG_SIMD, FCML_DS_128, FCML_REG_XMM8, FCML_FALSE };
fcml_st_register fcml_reg_YMM8 = { FCML_REG_SIMD, FCML_DS_256, FCML_REG_YMM8, FCML_FALSE };

fcml_st_register fcml_reg_R9L = { FCML_REG_GPR, FCML_DS_8, FCML_REG_R9L, FCML_FALSE };
fcml_st_register fcml_reg_R9W = { FCML_REG_GPR, FCML_DS_16, FCML_REG_R9W, FCML_FALSE };
fcml_st_register fcml_reg_R9D = { FCML_REG_GPR, FCML_DS_32, FCML_REG_R9D, FCML_FALSE };
fcml_st_register fcml_reg_R9 = { FCML_REG_GPR, FCML_DS_64, FCML_REG_R9, FCML_FALSE };
fcml_st_register fcml_reg_XMM9 = { FCML_REG_SIMD, FCML_DS_128, FCML_REG_XMM9, FCML_FALSE };
fcml_st_register fcml_reg_YMM9 = { FCML_REG_SIMD, FCML_DS_256, FCML_REG_YMM9, FCML_FALSE };

fcml_st_register fcml_reg_R10L = { FCML_REG_GPR, FCML_DS_8, FCML_REG_R10L, FCML_FALSE };
fcml_st_register fcml_reg_R10W = { FCML_REG_GPR, FCML_DS_16, FCML_REG_R10W, FCML_FALSE };
fcml_st_register fcml_reg_R10D = { FCML_REG_GPR, FCML_DS_32, FCML_REG_R10D, FCML_FALSE };
fcml_st_register fcml_reg_R10 = { FCML_REG_GPR, FCML_DS_64, FCML_REG_R10, FCML_FALSE };
fcml_st_register fcml_reg_XMM10 = { FCML_REG_SIMD, FCML_DS_128, FCML_REG_XMM10, FCML_FALSE };
fcml_st_register fcml_reg_YMM10 = { FCML_REG_SIMD, FCML_DS_256, FCML_REG_YMM10, FCML_FALSE };

fcml_st_register fcml_reg_R11L = { FCML_REG_GPR, FCML_DS_8, FCML_REG_R11L, FCML_FALSE };
fcml_st_register fcml_reg_R11W = { FCML_REG_GPR, FCML_DS_16, FCML_REG_R11W, FCML_FALSE };
fcml_st_register fcml_reg_R11D = { FCML_REG_GPR, FCML_DS_32, FCML_REG_R11D, FCML_FALSE };
fcml_st_register fcml_reg_R11 = { FCML_REG_GPR, FCML_DS_64, FCML_REG_R11, FCML_FALSE };
fcml_st_register fcml_reg_XMM11 = { FCML_REG_SIMD, FCML_DS_128, FCML_REG_XMM11, FCML_FALSE };
fcml_st_register fcml_reg_YMM11 = { FCML_REG_SIMD, FCML_DS_256, FCML_REG_YMM11, FCML_FALSE };

fcml_st_register fcml_reg_R12L = { FCML_REG_GPR, FCML_DS_8, FCML_REG_R12L, FCML_FALSE };
fcml_st_register fcml_reg_R12W = { FCML_REG_GPR, FCML_DS_16, FCML_REG_R12W, FCML_FALSE };
fcml_st_register fcml_reg_R12D = { FCML_REG_GPR, FCML_DS_32, FCML_REG_R12D, FCML_FALSE };
fcml_st_register fcml_reg_R12 = { FCML_REG_GPR, FCML_DS_64, FCML_REG_R12, FCML_FALSE };
fcml_st_register fcml_reg_XMM12 = { FCML_REG_SIMD, FCML_DS_128, FCML_REG_XMM12, FCML_FALSE };
fcml_st_register fcml_reg_YMM12 = { FCML_REG_SIMD, FCML_DS_256, FCML_REG_YMM12, FCML_FALSE };

fcml_st_register fcml_reg_R13L = { FCML_REG_GPR, FCML_DS_8, FCML_REG_R13L, FCML_FALSE };
fcml_st_register fcml_reg_R13W = { FCML_REG_GPR, FCML_DS_16, FCML_REG_R13W, FCML_FALSE };
fcml_st_register fcml_reg_R13D = { FCML_REG_GPR, FCML_DS_32, FCML_REG_R13D, FCML_FALSE };
fcml_st_register fcml_reg_R13 = { FCML_REG_GPR, FCML_DS_64, FCML_REG_R13, FCML_FALSE };
fcml_st_register fcml_reg_XMM13 = { FCML_REG_SIMD, FCML_DS_128, FCML_REG_XMM13, FCML_FALSE };
fcml_st_register fcml_reg_YMM13 = { FCML_REG_SIMD, FCML_DS_256, FCML_REG_YMM13, FCML_FALSE };

fcml_st_register fcml_reg_R14L = { FCML_REG_GPR, FCML_DS_8, FCML_REG_R14L, FCML_FALSE };
fcml_st_register fcml_reg_R14W = { FCML_REG_GPR, FCML_DS_16, FCML_REG_R14W, FCML_FALSE };
fcml_st_register fcml_reg_R14D = { FCML_REG_GPR, FCML_DS_32, FCML_REG_R14D, FCML_FALSE };
fcml_st_register fcml_reg_R14 = { FCML_REG_GPR, FCML_DS_64, FCML_REG_R14, FCML_FALSE };
fcml_st_register fcml_reg_XMM14 = { FCML_REG_SIMD, FCML_DS_128, FCML_REG_XMM14, FCML_FALSE };
fcml_st_register fcml_reg_YMM14 = { FCML_REG_SIMD, FCML_DS_256, FCML_REG_YMM14, FCML_FALSE };

fcml_st_register fcml_reg_R15L = { FCML_REG_GPR, FCML_DS_8, FCML_REG_R15L, FCML_FALSE };
fcml_st_register fcml_reg_R15W = { FCML_REG_GPR, FCML_DS_16, FCML_REG_R15W, FCML_FALSE };
fcml_st_register fcml_reg_R15D = { FCML_REG_GPR, FCML_DS_32, FCML_REG_R15D, FCML_FALSE };
fcml_st_register fcml_reg_R15 = { FCML_REG_GPR, FCML_DS_64, FCML_REG_R15, FCML_FALSE };
fcml_st_register fcml_reg_XMM15 = { FCML_REG_SIMD, FCML_DS_128, FCML_REG_XMM15, FCML_FALSE };
fcml_st_register fcml_reg_YMM15 = { FCML_REG_SIMD, FCML_DS_256, FCML_REG_YMM15, FCML_FALSE };

fcml_st_register fcml_reg_ES = { FCML_REG_SEG, FCML_DS_16, FCML_REG_ES, FCML_FALSE };
fcml_st_register fcml_reg_CS = { FCML_REG_SEG, FCML_DS_16, FCML_REG_CS, FCML_FALSE };
fcml_st_register fcml_reg_SS = { FCML_REG_SEG, FCML_DS_16, FCML_REG_SS, FCML_FALSE };
fcml_st_register fcml_reg_DS = { FCML_REG_SEG, FCML_DS_16, FCML_REG_DS, FCML_FALSE };
fcml_st_register fcml_reg_FS = { FCML_REG_SEG, FCML_DS_16, FCML_REG_FS, FCML_FALSE };
fcml_st_register fcml_reg_GS = { FCML_REG_SEG, FCML_DS_16, FCML_REG_GS, FCML_FALSE };

fcml_st_register fcml_reg_ST0 = { FCML_REG_FPU, FCML_DS_UNDEF, FCML_REG_ST0, FCML_FALSE };
fcml_st_register fcml_reg_ST1 = { FCML_REG_FPU, FCML_DS_UNDEF, FCML_REG_ST1, FCML_FALSE };
fcml_st_register fcml_reg_ST2 = { FCML_REG_FPU, FCML_DS_UNDEF, FCML_REG_ST2, FCML_FALSE };
fcml_st_register fcml_reg_ST3 = { FCML_REG_FPU, FCML_DS_UNDEF, FCML_REG_ST3, FCML_FALSE };
fcml_st_register fcml_reg_ST4 = { FCML_REG_FPU, FCML_DS_UNDEF, FCML_REG_ST4, FCML_FALSE };
fcml_st_register fcml_reg_ST5 = { FCML_REG_FPU, FCML_DS_UNDEF, FCML_REG_ST5, FCML_FALSE };
fcml_st_register fcml_reg_ST6 = { FCML_REG_FPU, FCML_DS_UNDEF, FCML_REG_ST6, FCML_FALSE };
fcml_st_register fcml_reg_ST7 = { FCML_REG_FPU, FCML_DS_UNDEF, FCML_REG_ST7, FCML_FALSE };

fcml_st_register fcml_reg_CR0 = { FCML_REG_CR, FCML_DS_UNDEF, FCML_REG_CR0, FCML_FALSE };
fcml_st_register fcml_reg_CR2 = { FCML_REG_CR, FCML_DS_UNDEF, FCML_REG_CR2, FCML_FALSE };
fcml_st_register fcml_reg_CR3 = { FCML_REG_CR, FCML_DS_UNDEF, FCML_REG_CR3, FCML_FALSE };
fcml_st_register fcml_reg_CR4 = { FCML_REG_CR, FCML_DS_UNDEF, FCML_REG_CR4, FCML_FALSE };
fcml_st_register fcml_reg_CR8 = { FCML_REG_CR, FCML_DS_UNDEF, FCML_REG_CR8, FCML_FALSE };

fcml_st_register fcml_reg_DR0 = { FCML_REG_DR, FCML_DS_UNDEF, FCML_REG_DR0, FCML_FALSE };
fcml_st_register fcml_reg_DR1 = { FCML_REG_DR, FCML_DS_UNDEF, FCML_REG_DR1, FCML_FALSE };
fcml_st_register fcml_reg_DR2 = { FCML_REG_DR, FCML_DS_UNDEF, FCML_REG_DR2, FCML_FALSE };
fcml_st_register fcml_reg_DR3 = { FCML_REG_DR, FCML_DS_UNDEF, FCML_REG_DR3, FCML_FALSE };
fcml_st_register fcml_reg_DR4 = { FCML_REG_DR, FCML_DS_UNDEF, FCML_REG_DR4, FCML_FALSE };
fcml_st_register fcml_reg_DR5 = { FCML_REG_DR, FCML_DS_UNDEF, FCML_REG_DR5, FCML_FALSE };
fcml_st_register fcml_reg_DR6 = { FCML_REG_DR, FCML_DS_UNDEF, FCML_REG_DR6, FCML_FALSE };
fcml_st_register fcml_reg_DR7 = { FCML_REG_DR, FCML_DS_UNDEF, FCML_REG_DR7, FCML_FALSE };

fcml_st_register fcml_reg_IP  = { FCML_REG_IP, FCML_DS_16, FCML_REG_UNDEFINED, FCML_FALSE };
fcml_st_register fcml_reg_EIP = { FCML_REG_IP, FCML_DS_32, FCML_REG_UNDEFINED, FCML_FALSE };
fcml_st_register fcml_reg_RIP = { FCML_REG_IP, FCML_DS_64, FCML_REG_UNDEFINED, FCML_FALSE };

fcml_st_operand LIB_CALL fcml_fn_cu_operand_unsigned_imm_8( fcml_uint8_t value ) {
	fcml_st_operand imm = {FCML_EOT_NONE};
	imm.type = FCML_EOT_IMMEDIATE;
	imm.immediate.size = FCML_DS_8;
	imm.immediate.int8 = value;
	return imm;
}

fcml_st_operand LIB_CALL fcml_fn_cu_operand_signed_imm_8( fcml_int8_t value ) {
	fcml_st_operand imm = {FCML_EOT_NONE};
	imm.type = FCML_EOT_IMMEDIATE;
	imm.immediate.size = FCML_DS_8;
	imm.immediate.is_signed = FCML_TRUE;
	imm.immediate.int8 = value;
	return imm;
}

fcml_st_operand LIB_CALL fcml_fn_cu_operand_unsigned_imm_16( fcml_uint16_t value ) {
	fcml_st_operand imm = {FCML_EOT_NONE};
	imm.type = FCML_EOT_IMMEDIATE;
	imm.immediate.size = FCML_DS_16;
	imm.immediate.int16 = value;
	return imm;
}

fcml_st_operand LIB_CALL fcml_fn_cu_operand_signed_imm_16( fcml_int16_t value ) {
	fcml_st_operand imm = {FCML_EOT_NONE};
	imm.type = FCML_EOT_IMMEDIATE;
	imm.immediate.size = FCML_DS_16;
	imm.immediate.is_signed = FCML_TRUE;
	imm.immediate.int16 = value;
	return imm;
}

fcml_st_operand LIB_CALL fcml_fn_cu_operand_unsigned_imm_32( fcml_uint32_t value ) {
	fcml_st_operand imm = {FCML_EOT_NONE};
	imm.type = FCML_EOT_IMMEDIATE;
	imm.immediate.size = FCML_DS_32;
	imm.immediate.int32 = value;
	return imm;
}

fcml_st_operand LIB_CALL fcml_fn_cu_operand_signed_imm_32( fcml_int32_t value ) {
	fcml_st_operand imm = {FCML_EOT_NONE};
	imm.type = FCML_EOT_IMMEDIATE;
	imm.immediate.size = FCML_DS_32;
	imm.immediate.is_signed = FCML_TRUE;
	imm.immediate.int32 = value;
	return imm;
}

fcml_st_operand LIB_CALL fcml_fn_cu_operand_unsigned_imm_64( fcml_uint64_t value ) {
	fcml_st_operand imm = {FCML_EOT_NONE};
	imm.type = FCML_EOT_IMMEDIATE;
	imm.immediate.size = FCML_DS_64;
	imm.immediate.int64 = value;
	return imm;
}

fcml_st_operand LIB_CALL fcml_fn_cu_operand_signed_imm_64( fcml_int64_t value ) {
	fcml_st_operand imm = {FCML_EOT_NONE};
	imm.type = FCML_EOT_IMMEDIATE;
	imm.immediate.size = FCML_DS_64;
	imm.immediate.is_signed = FCML_TRUE;
	imm.immediate.int64 = value;
	return imm;
}

fcml_st_operand LIB_CALL fcml_fn_cu_operand_reg( fcml_st_register *reg ) {
	fcml_st_operand reg_operand = {FCML_EOT_NONE};
	reg_operand.type = FCML_EOT_REGISTER;
	reg_operand.reg = *reg;
	return reg_operand;
}

fcml_st_operand LIB_CALL fcml_fn_cu_operand_addr_far_pointer_offset16( fcml_int16_t seg, fcml_int16_t offset ) {
    fcml_st_operand operand = {FCML_EOT_NONE};
    operand.type = FCML_EOT_FAR_POINTER;
    fcml_st_far_pointer *far_pointer = &(operand.far_pointer);
    far_pointer->segment = seg;
    far_pointer->offset16 = offset;
    far_pointer->offset_size = FCML_DS_16;
    return operand;
}

fcml_st_operand LIB_CALL fcml_fn_cu_operand_addr_far_pointer_offset32( fcml_int16_t seg, fcml_int32_t offset ) {
    fcml_st_operand operand = {FCML_EOT_NONE};
    operand.type = FCML_EOT_FAR_POINTER;
    fcml_st_far_pointer *far_pointer = &(operand.far_pointer);
    far_pointer->segment = seg;
    far_pointer->offset32 = offset;
    far_pointer->offset_size = FCML_DS_32;
    return operand;
}

fcml_st_operand LIB_CALL fcml_fn_cu_operand_addr_offset_16( fcml_int16_t offset ) {
    fcml_st_operand operand = {FCML_EOT_NONE};
    operand.type = FCML_EOT_ADDRESS;
    fcml_st_address *address = &(operand.address);
    address->address_form = FCML_AF_OFFSET;
    address->offset.off16 = offset;
    address->offset.size = FCML_DS_16;
    return operand;
}

fcml_st_operand LIB_CALL fcml_fn_cu_operand_addr_offset_32( fcml_int32_t offset ) {
    fcml_st_operand operand = {FCML_EOT_NONE};
    operand.type = FCML_EOT_ADDRESS;
    fcml_st_address *address = &(operand.address);
    address->address_form = FCML_AF_OFFSET;
    address->offset.off32 = offset;
    address->offset.size = FCML_DS_32;
    return operand;
}

fcml_st_operand LIB_CALL fcml_fn_cu_operand_addr_offset_abs_64( fcml_int64_t offset ) {
    fcml_st_operand operand = {FCML_EOT_NONE};
    operand.type = FCML_EOT_ADDRESS;
    fcml_st_address *address = &(operand.address);
    address->address_form = FCML_AF_OFFSET;
    address->offset.off64 = offset;
    address->offset.size = FCML_DS_64;
    operand.hints = FCML_OP_HINT_ABSOLUTE_ADDRESSING;
    return operand;
}

fcml_st_operand LIB_CALL fcml_fn_cu_operand_addr_offset_rel_64( fcml_int64_t offset ) {
    fcml_st_operand operand = {FCML_EOT_NONE};
    operand.type = FCML_EOT_ADDRESS;
    fcml_st_address *address = &(operand.address);
    address->address_form = FCML_AF_OFFSET;
    address->offset.off64 = offset;
    address->offset.size = FCML_DS_64;
    operand.hints = FCML_OP_HINT_RELATIVE_ADDRESSING;
    return operand;
}

fcml_st_operand LIB_CALL fcml_fn_cu_operand_addr_disp_16( fcml_int16_t disp ) {
    fcml_st_operand operand = {FCML_EOT_NONE};
    operand.type = FCML_EOT_ADDRESS;
    fcml_st_address *address = &(operand.address);
    fcml_st_effective_address *effective_address = &(address->effective_address);
    address->address_form = FCML_AF_COMBINED;
    effective_address->displacement.int16 = disp;
    effective_address->displacement.size = FCML_DS_16;
    return operand;
}

fcml_st_operand LIB_CALL fcml_fn_cu_operand_addr_disp_32( fcml_int32_t disp ) {
    fcml_st_operand operand = {FCML_EOT_NONE};
    operand.type = FCML_EOT_ADDRESS;
    fcml_st_address *address = &(operand.address);
    fcml_st_effective_address *effective_address = &(address->effective_address);
    address->address_form = FCML_AF_COMBINED;
    effective_address->displacement.int32 = disp;
    effective_address->displacement.size = FCML_DS_32;
    return operand;
}

fcml_st_operand LIB_CALL fcml_fn_cu_operand_addr_disp_64( fcml_int64_t disp ) {
    fcml_st_operand operand = {FCML_EOT_NONE};
    operand.type = FCML_EOT_ADDRESS;
    fcml_st_address *address = &(operand.address);
    fcml_st_effective_address *effective_address = &(address->effective_address);
    address->address_form = FCML_AF_COMBINED;
    effective_address->displacement.int64 = disp;
    effective_address->displacement.size = FCML_DS_64;
    return operand;
}

fcml_st_operand LIB_CALL fcml_fn_cu_operand_addr_b_disp_8( fcml_st_register *base, fcml_int8_t disp ) {
    fcml_st_operand operand = {FCML_EOT_NONE};
    operand.type = FCML_EOT_ADDRESS;
    fcml_st_address *address = &(operand.address);
    fcml_st_effective_address *effective_address = &(address->effective_address);
    address->address_form = FCML_AF_COMBINED;
    effective_address->displacement.int8 = disp;
    effective_address->displacement.size = FCML_DS_8;
    effective_address->base = *base;
    return operand;
}

fcml_st_operand LIB_CALL fcml_fn_cu_operand_addr_b_disp_16( fcml_st_register *base, fcml_int16_t disp ) {
    fcml_st_operand operand = fcml_fn_cu_operand_addr_disp_16( disp );
    operand.address.effective_address.base = *base;
    return operand;
}

fcml_st_operand LIB_CALL fcml_fn_cu_operand_addr_b_disp_32( fcml_st_register *base, fcml_int32_t disp ) {
    fcml_st_operand operand = fcml_fn_cu_operand_addr_disp_32( disp );
    operand.address.effective_address.base = *base;
    return operand;
}

fcml_st_operand LIB_CALL fcml_fn_cu_operand_addr_b_disp_64( fcml_st_register *base, fcml_int64_t disp ) {
    fcml_st_operand operand = fcml_fn_cu_operand_addr_disp_64( disp );
    operand.address.effective_address.base = *base;
    return operand;
}

fcml_st_operand LIB_CALL fcml_fn_cu_operand_addr_is_disp_8( fcml_st_register *index, fcml_uint8_t scale_factor, fcml_int8_t disp ) {
    fcml_st_operand operand = {FCML_EOT_NONE};
    operand.type = FCML_EOT_ADDRESS;
    fcml_st_address *address = &(operand.address);
    fcml_st_effective_address *effective_address = &(address->effective_address);
    address->address_form = FCML_AF_COMBINED;
    effective_address->displacement.int8 = disp;
    effective_address->displacement.size = FCML_DS_8;
    effective_address->index = *index;
    effective_address->scale_factor = scale_factor;
    return operand;
}

fcml_st_operand LIB_CALL fcml_fn_cu_operand_addr_is_disp_32( fcml_st_register *index, fcml_uint8_t scale_factor, fcml_int32_t disp ) {
    fcml_st_operand operand = fcml_fn_cu_operand_addr_disp_32( disp );
    fcml_st_effective_address *effective_address = &(operand.address.effective_address);
    effective_address->index = *index;
    effective_address->scale_factor = scale_factor;
    return operand;
}

fcml_st_operand LIB_CALL fcml_fn_cu_operand_addr_is_disp_64( fcml_st_register *index, fcml_uint8_t scale_factor, fcml_int64_t disp ) {
    fcml_st_operand operand = fcml_fn_cu_operand_addr_disp_32( (fcml_int32_t)disp );
    fcml_st_effective_address *effective_address = &(operand.address.effective_address);
    effective_address->index = *index;
    effective_address->scale_factor = scale_factor;
    return operand;
}

fcml_st_operand LIB_CALL fcml_fn_cu_operand_addr_bis_disp_8( fcml_st_register *base, fcml_st_register *index, fcml_uint8_t scale_factor, fcml_int8_t disp ) {
    fcml_st_operand operand = {FCML_EOT_NONE};
    operand.type = FCML_EOT_ADDRESS;
    fcml_st_address *address = &(operand.address);
    fcml_st_effective_address *effective_address = &(address->effective_address);
    address->address_form = FCML_AF_COMBINED;
    effective_address->displacement.int8 = disp;
    effective_address->displacement.size = FCML_DS_8;
    effective_address->base = *base;
    effective_address->index = *index;
    effective_address->scale_factor = scale_factor;
    return operand;
}

fcml_st_operand LIB_CALL fcml_fn_cu_operand_addr_bis_disp_32( fcml_st_register *base, fcml_st_register *index, fcml_uint8_t scale_factor, fcml_int32_t disp ) {
    fcml_st_operand operand = fcml_fn_cu_operand_addr_disp_32( disp );
    fcml_st_effective_address *effective_address = &(operand.address.effective_address);
    effective_address->base = *base;
    effective_address->index = *index;
    effective_address->scale_factor = scale_factor;
    return operand;
}

fcml_st_operand LIB_CALL fcml_fn_cu_operand_addr_bis_disp_64( fcml_st_register *base, fcml_st_register *index, fcml_uint8_t scale_factor, fcml_int64_t disp ) {
    fcml_st_operand operand = fcml_fn_cu_operand_addr_disp_32( (fcml_int32_t)disp );
    fcml_st_effective_address *effective_address = &(operand.address.effective_address);
    effective_address->base = *base;
    effective_address->index = *index;
    effective_address->scale_factor = scale_factor;
    return operand;
}

fcml_st_operand LIB_CALL fcml_fn_cu_add_operand_hints( fcml_st_operand operand, fcml_hints hints ) {
    operand.hints = hints;
    return operand;
}

fcml_st_instruction* LIB_CALL fcml_fn_cu_clone_instruction( fcml_st_instruction *instruction ) {
	if( !instruction ) {
		return NULL;
	}
	fcml_st_instruction *new_inst = (fcml_st_instruction*)fcml_fn_env_memory_alloc_clear( sizeof( fcml_st_instruction ) );
	if( !new_inst ) {
		return NULL;
	}
	*new_inst = *instruction;
	new_inst->mnemonic = fcml_fn_env_str_strdup( instruction->mnemonic );
	if( !new_inst->mnemonic ) {
		fcml_fn_env_memory_free( new_inst );
		return NULL;
	}
	return new_inst;
}

void LIB_CALL fcml_fn_cu_free_instruction( fcml_st_instruction *instruction ) {
	if( instruction ) {
		if( instruction->mnemonic ) {
			fcml_fn_env_str_strfree( instruction->mnemonic );
		}
		fcml_fn_env_memory_free( instruction );
	}
}
