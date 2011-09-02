/*
 * ira_def.c
 *
 *  Created on: 19-11-2010
 *      Author: Slawomir Wojtasiak
 */

#include "ira_int.h"

struct ira_opcode_desc _ira_opcode_desc_AAA[] = {
	{ NULL, 0x0001, 0x00540000, { 0x37, 0x00, 0x00 }, _IRA_NA, _IRA_NA, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_AAD[] = {
	{ NULL, 0x0001, 0x00580000, { 0xD5, 0x0A, 0x00 }, _IRA_NA, _IRA_NA, _IRA_NA, _IRA_NA },
	{ NULL, 0x0001, 0x00540000, { 0xD5, 0x00, 0x00 }, _IRA_OPERAND_IB, _IRA_NA, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_AAM[] = {
	{ NULL, 0x0001, 0x00580000, { 0xD4, 0x0A, 0x00 }, _IRA_NA, _IRA_NA, _IRA_NA, _IRA_NA },
	{ NULL, 0x0001, 0x00540000, { 0xD4, 0x00, 0x00 }, _IRA_OPERAND_IB, _IRA_NA, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_AAS[] = {
	{ NULL, 0x0001, 0x00540000, { 0x3F, 0x00, 0x00 }, _IRA_NA, _IRA_NA, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_ADC[] = {
	// 14 ib ADC AL, imm8 C Valid Valid Add with carry imm8 to AL.
	{ NULL, 0x0001, 0x00C40000, { 0x14, 0x00, 0x00 }, _IRA_OPERAND_REG_ACCUMULATOR_8, _IRA_OPERAND_IB, _IRA_NA, _IRA_NA },
	// 15 iw ADC AX, imm16 C Valid Valid Add with carry imm16 to AX.
	// 15 id ADC EAX, imm32 C Valid Valid Add with carry imm32 to EAX.
	{ NULL, 0x0001, 0x00D40000, { 0x15, 0x00, 0x00 }, _IRA_OPERAND_REG_ACCUMULATOR_OSA_W, _IRA_OPERAND_IMM_EOSA, _IRA_NA, _IRA_NA },
	// REX.W + 15 id ADC RAX, imm32 C Valid N.E. Add with carry imm32 sign extended to 64-bits to RAX.
	{ NULL, 0x0009, 0x00940000, { 0x15, 0x00, 0x00 }, _IRA_OPERAND_REG_ACCUMULATOR_OSA_W, _IRA_OPERAND_ID_EX_EOSA, _IRA_NA, _IRA_NA },
	// 80 /2 ib ADC r/m8, imm8 B Valid Valid Add with carry imm8 to r/m8.
	// REX + 80 /2 ib ADC r/m8*, imm8 B Valid N.E. Add with carry imm8 to r/m8.
	{ NULL, 0x0001, 0x00C59000, { 0x80, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_8_W, _IRA_OPERAND_IB, _IRA_NA, _IRA_NA },
	// 81 /2 iw ADC r/m16, imm16 B Valid Valid Add with carry imm16 to r/m16.
	// 81 /2 id ADC r/m32, imm32 B Valid Valid Add with CF imm32 to r/m32.
	{ NULL, 0x0001, 0x00C59000, { 0x81, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_ASA_W, _IRA_OPERAND_IMM_EOSA, _IRA_NA, _IRA_NA },
	// REX.W + 81 /2 id ADC r/m64, imm32 B Valid N.E. Add with CF imm32 sign extended to 64-bits to r/m64.
	{ NULL, 0x0009, 0x00859000, { 0x81, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_ASA_W, _IRA_OPERAND_ID_EX_EOSA, _IRA_NA, _IRA_NA },
	// 83 /2 ib ADC r/m16, imm8 B Valid Valid Add with CF sign-extended imm8 to r/m16.
	// 83 /2 ib ADC r/m32, imm8 B Valid Valid Add with CF sign-extended imm8 into r/m32.
	{ NULL, 0x0001, 0x00C59000, { 0x83, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_ASA_W, _IRA_OPERAND_IB_EX_EOSA, _IRA_NA, _IRA_NA },
	// REX.W + 83 /2 ib ADC r/m64, imm8 B Valid N.E. Add with CF sign-extended imm8 into r/m64.
	{ NULL, 0x0009, 0x00859000, { 0x83, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_ASA_W, _IRA_OPERAND_IB_EX_EOSA, _IRA_NA, _IRA_NA },
	// 10 /r ADC r/m8, r8 A Valid Valid Add with carry byte register to r/m8.
	// REX + 10 /r ADC r/m8*, r8* A Valid N.E. Add with carry byte register to r/m64.
	{ NULL, 0x0001, 0x00C48000, { 0x10, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_8_W, _IRA_OPERAND_MODRM_R_8, _IRA_NA, _IRA_NA },
	// 11 /r ADC r/m16, r16 A Valid Valid Add with carry r16 to r/m16.
	// 11 /r ADC r/m32, r32 A Valid Valid Add with CF r32 to r/m32.
	// REX.W + 11 /r ADC r/m64, r64 A Valid N.E. Add with CF r64 to r/m64.
	{ NULL, 0x0001, 0x00C48000, { 0x11, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_ASA_W, _IRA_OPERAND_MODRM_R_OSA, _IRA_NA, _IRA_NA },
	// 12 /r ADC r8, r/m8 A Valid Valid Add with carry r/m8 to byte register.
	// REX + 12 /r ADC r8*, r/m8* A Valid N.E. Add with carry r/m64 to byte register.
	{ NULL, 0x0001, 0x00C48000, { 0x12, 0x00, 0x00 }, _IRA_OPERAND_MODRM_R_8_W, _IRA_OPERAND_MODRM_RM_8, _IRA_NA, _IRA_NA },
	// 13 /r ADC r16, r/m16 A Valid Valid Add with carry r/m16 to r16.
	// 13 /r ADC r32, r/m32 A Valid Valid Add with CF r/m32 to r32.
	// REX.W + 13 /r ADC r64, r/m64 A Valid N.E. Add with CF r/m64 to r64.
	{ NULL, 0x0001, 0x00C48000, { 0x13, 0x00, 0x00 }, _IRA_OPERAND_MODRM_R_OSA_W, _IRA_OPERAND_MODRM_RM_ASA, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_ADD[] = {
	// 04 ib ADD AL, imm8 C Valid Valid Add imm8 to AL..
	{ NULL, 0x0001, 0x00C40000, { 0x04, 0x00, 0x00 }, _IRA_OPERAND_REG_ACCUMULATOR_8, _IRA_OPERAND_IB, _IRA_NA, _IRA_NA },
	// 05 iw ADD AX, imm16 C Valid Valid Add imm16 to AX.
	// 05 id ADD EAX, imm32 C Valid Valid Add imm32 to EAX.
	{ NULL, 0x0001, 0x00D40000, { 0x05, 0x00, 0x00 }, _IRA_OPERAND_REG_ACCUMULATOR_OSA_W, _IRA_OPERAND_IMM_EOSA, _IRA_NA, _IRA_NA },
	// REX.W + 05 id ADD RAX, imm32 C Valid N.E. Add imm32 sign-extended to 64-bits to RAX.
	{ NULL, 0x0009, 0x00940000, { 0x05, 0x00, 0x00 }, _IRA_OPERAND_REG_ACCUMULATOR_OSA_W, _IRA_OPERAND_ID_EX_EOSA, _IRA_NA, _IRA_NA },
	// 80 /0 ib ADD r/m8, imm8 B Valid Valid Add imm8 to r/m8.
	// REX + 80 /0 ib ADD r/m8*, imm8 B Valid N.E. Add sign-extended imm8 to r/m64.
	{ NULL, 0x0001, 0x00C58000, { 0x80, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_8_W, _IRA_OPERAND_IB, _IRA_NA, _IRA_NA },
	// 81 /0 iw ADD r/m16, imm16 B Valid Valid Add imm16 to r/m16.
	// 81 /0 id ADD r/m32, imm32 B Valid Valid Add imm32 to r/m32.
	{ NULL, 0x0001, 0x00C58000, { 0x81, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_ASA_W, _IRA_OPERAND_IMM_EOSA, _IRA_NA, _IRA_NA },
	// REX.W + 81 /0 id ADD r/m64, imm32 B Valid N.E. Add imm32 sign-extended to 64-bits to r/m64.
	{ NULL, 0x0009, 0x00858000, { 0x81, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_ASA_W, _IRA_OPERAND_ID_EX_EOSA, _IRA_NA, _IRA_NA },
	// 83 /0 ib ADD r/m16, imm8 B Valid Valid Add sign-extended imm8 to r/m16.
	// 83 /0 ib ADD r/m32, imm8 B Valid Valid Add sign-extended imm8 to r/m32.
	{ NULL, 0x0001, 0x00C58000, { 0x83, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_ASA_W, _IRA_OPERAND_IB_EX_EOSA, _IRA_NA, _IRA_NA },
	// REX.W + 83 /0 ib ADD r/m64, imm8 B Valid N.E. Add sign-extended imm8 to r/m64.
	{ NULL, 0x0009, 0x00858000, { 0x83, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_ASA_W, _IRA_OPERAND_IB_EX_EOSA, _IRA_NA, _IRA_NA },
	// 00 /r ADD r/m8, r8 A Valid Valid Add r8 to r/m8.
	// REX + 00 /r ADD r/m8*, r8* A Valid N.E. Add r8 to r/m8.
	{ NULL, 0x0001, 0x00C48000, { 0x00, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_8_W, _IRA_OPERAND_MODRM_R_8, _IRA_NA, _IRA_NA },
	// 01 /r ADD r/m16, r16 A Valid Valid Add r16 to r/m16.
	// 01 /r ADD r/m32, r32 A Valid Valid Add r32 to r/m32.
	// REX.W + 01 /r ADD r/m64, r64 A Valid N.E. Add r64 to r/m64.
	{ NULL, 0x0001, 0x00C48000, { 0x01, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_ASA_W, _IRA_OPERAND_MODRM_R_OSA, _IRA_NA, _IRA_NA },
	// 02 /r ADD r8, r/m8 A Valid Valid Add r/m8 to r8.
	// REX + 02 /r ADD r8*, r/m8* A Valid N.E. Add r/m8 to r8.
	{ NULL, 0x0001, 0x00C48000, { 0x02, 0x00, 0x00 }, _IRA_OPERAND_MODRM_R_8_W, _IRA_OPERAND_MODRM_RM_8, _IRA_NA, _IRA_NA },
	// 03 /r ADD r16, r/m16 A Valid Valid Add r/m16 to r16.
	// 03 /r ADD r32, r/m32 A Valid Valid Add r/m32 to r32.
	// REX.W + 03 /r ADD r64, r/m64 A Valid N.E. Add r/m64 to r64.
	{ NULL, 0x0001, 0x00C48000, { 0x03, 0x00, 0x00 }, _IRA_OPERAND_MODRM_R_OSA_W, _IRA_OPERAND_MODRM_RM_ASA, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_ADDPD[] = {
	// 66 0F 58 /r ADDPD xmm1, xmm2/m128 A Valid Valid Add packed double-precision floating-point values from xmm2/m128 to xmm1.
	{ NULL, 0x1001, 0x00D88000, { 0x0F, 0x58, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_128_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA }
};

struct ira_instruction_desc _ira_instructions_desc[] = {
		{ "aaa", _IRA_IT_IA, _IRA_OPERANDS_SIZEOF(_ira_opcode_desc_AAA), _ira_opcode_desc_AAA },
		{ "aad", _IRA_IT_IA, _IRA_OPERANDS_SIZEOF(_ira_opcode_desc_AAD), _ira_opcode_desc_AAD },
		{ "aam", _IRA_IT_IA, _IRA_OPERANDS_SIZEOF(_ira_opcode_desc_AAM), _ira_opcode_desc_AAM },
		{ "aas", _IRA_IT_IA, _IRA_OPERANDS_SIZEOF(_ira_opcode_desc_AAS), _ira_opcode_desc_AAS },
		{ "adc", _IRA_IT_IA, _IRA_OPERANDS_SIZEOF(_ira_opcode_desc_ADC), _ira_opcode_desc_ADC },
		{ "add", _IRA_IT_IA, _IRA_OPERANDS_SIZEOF(_ira_opcode_desc_ADD), _ira_opcode_desc_ADD },
		{ "addpd", _IRA_IT_IA, _IRA_OPERANDS_SIZEOF(_ira_opcode_desc_ADDPD), _ira_opcode_desc_ADDPD },
		{ NULL, 0, 0, NULL }
};


