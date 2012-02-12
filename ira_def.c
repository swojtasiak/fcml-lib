/*
 * ira_def.c
 *
 *  Created on: 19-11-2010
 *      Author: Slawomir Wojtasiak
 */

#include "ira_int.h"

struct ira_opcode_desc _ira_opcode_desc_AAA[] = {
	{ NULL, 0x0001, 0x00440000, { 0x37, 0x00, 0x00 }, _IRA_NA, _IRA_NA, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_AAD[] = {
	{ NULL, 0x0001, 0x00580000, { 0xD5, 0x0A, 0x00 }, _IRA_NA, _IRA_NA, _IRA_NA, _IRA_NA },
	{ NULL, 0x0001, 0x00440000, { 0xD5, 0x00, 0x00 }, _IRA_OPERAND_IB, _IRA_NA, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_AAM[] = {
	{ NULL, 0x0001, 0x00580000, { 0xD4, 0x0A, 0x00 }, _IRA_NA, _IRA_NA, _IRA_NA, _IRA_NA },
	{ NULL, 0x0001, 0x00440000, { 0xD4, 0x00, 0x00 }, _IRA_OPERAND_IB, _IRA_NA, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_AAS[] = {
	{ NULL, 0x0001, 0x00440000, { 0x3F, 0x00, 0x00 }, _IRA_NA, _IRA_NA, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_ADC[] = {
	// 14 ib ADC AL, imm8 C Valid Valid Add with carry imm8 to AL.
	{ NULL, 0x0001, 0x00C40000, { 0x14, 0x00, 0x00 }, _IRA_OPERAND_REG_ACCUMULATOR_8, _IRA_OPERAND_IB, _IRA_NA, _IRA_NA },
	// 15 iw ADC AX, imm16 C Valid Valid Add with carry imm16 to AX.
	// 15 id ADC EAX, imm32 C Valid Valid Add with carry imm32 to EAX.
	{ NULL, 0x0001, 0x00C40000, { 0x15, 0x00, 0x00 }, _IRA_OPERAND_REG_ACCUMULATOR_OSA_W, _IRA_OPERAND_IMM_EOSA, _IRA_NA, _IRA_NA },
	// REX.W + 15 id ADC RAX, imm32 C Valid N.E. Add with carry imm32 sign extended to 64-bits to RAX.
	{ NULL, 0x0009, 0x00840000, { 0x15, 0x00, 0x00 }, _IRA_OPERAND_REG_ACCUMULATOR_OSA_W, _IRA_OPERAND_ID_EX_EOSA, _IRA_NA, _IRA_NA },
	// 80 /2 ib ADC r/m8, imm8 B Valid Valid Add with carry imm8 to r/m8.
	// REX + 80 /2 ib ADC r/m8*, imm8 B Valid N.E. Add with carry imm8 to r/m8.
	{ NULL, 0x0001, 0x00C59000, { 0x80, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_8_W, _IRA_OPERAND_IB, _IRA_NA, _IRA_NA },
	// 81 /2 iw ADC r/m16, imm16 B Valid Valid Add with carry imm16 to r/m16.
	// 81 /2 id ADC r/m32, imm32 B Valid Valid Add with CF imm32 to r/m32.
	{ NULL, 0x0001, 0x00C59000, { 0x81, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_W, _IRA_OPERAND_IMM_EOSA, _IRA_NA, _IRA_NA },
	// REX.W + 81 /2 id ADC r/m64, imm32 B Valid N.E. Add with CF imm32 sign extended to 64-bits to r/m64.
	{ NULL, 0x0009, 0x00859000, { 0x81, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_W, _IRA_OPERAND_ID_EX_EOSA, _IRA_NA, _IRA_NA },
	// 83 /2 ib ADC r/m16, imm8 B Valid Valid Add with CF sign-extended imm8 to r/m16.
	// 83 /2 ib ADC r/m32, imm8 B Valid Valid Add with CF sign-extended imm8 into r/m32.
	{ NULL, 0x0001, 0x00C59000, { 0x83, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_W, _IRA_OPERAND_IB_EX_EOSA, _IRA_NA, _IRA_NA },
	// REX.W + 83 /2 ib ADC r/m64, imm8 B Valid N.E. Add with CF sign-extended imm8 into r/m64.
	{ NULL, 0x0009, 0x00859000, { 0x83, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_W, _IRA_OPERAND_IB_EX_EOSA, _IRA_NA, _IRA_NA },
	// 10 /r ADC r/m8, r8 A Valid Valid Add with carry byte register to r/m8.
	// REX + 10 /r ADC r/m8*, r8* A Valid N.E. Add with carry byte register to r/m64.
	{ NULL, 0x0001, 0x00C48000, { 0x10, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_8_W, _IRA_OPERAND_MODRM_R_8, _IRA_NA, _IRA_NA },
	// 11 /r ADC r/m16, r16 A Valid Valid Add with carry r16 to r/m16.
	// 11 /r ADC r/m32, r32 A Valid Valid Add with CF r32 to r/m32.
	// REX.W + 11 /r ADC r/m64, r64 A Valid N.E. Add with CF r64 to r/m64.
	{ NULL, 0x0001, 0x00C48000, { 0x11, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_W, _IRA_OPERAND_MODRM_R, _IRA_NA, _IRA_NA },
	// 12 /r ADC r8, r/m8 A Valid Valid Add with carry r/m8 to byte register.
	// REX + 12 /r ADC r8*, r/m8* A Valid N.E. Add with carry r/m64 to byte register.
	{ NULL, 0x0001, 0x00C48000, { 0x12, 0x00, 0x00 }, _IRA_OPERAND_MODRM_R_8_W, _IRA_OPERAND_MODRM_RM_8, _IRA_NA, _IRA_NA },
	// 13 /r ADC r16, r/m16 A Valid Valid Add with carry r/m16 to r16.
	// 13 /r ADC r32, r/m32 A Valid Valid Add with CF r/m32 to r32.
	// REX.W + 13 /r ADC r64, r/m64 A Valid N.E. Add with CF r/m64 to r64.
	{ NULL, 0x0001, 0x00C48000, { 0x13, 0x00, 0x00 }, _IRA_OPERAND_MODRM_R_W, _IRA_OPERAND_MODRM_RM, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_ADD[] = {
	// 04 ib ADD AL, imm8 C Valid Valid Add imm8 to AL..
	{ NULL, 0x0001, 0x00C40000, { 0x04, 0x00, 0x00 }, _IRA_OPERAND_REG_ACCUMULATOR_8, _IRA_OPERAND_IB, _IRA_NA, _IRA_NA },
	// 05 iw ADD AX, imm16 C Valid Valid Add imm16 to AX.
	// 05 id ADD EAX, imm32 C Valid Valid Add imm32 to EAX.
	{ NULL, 0x0001, 0x00C40000, { 0x05, 0x00, 0x00 }, _IRA_OPERAND_REG_ACCUMULATOR_OSA_W, _IRA_OPERAND_IMM_EOSA, _IRA_NA, _IRA_NA },
	// REX.W + 05 id ADD RAX, imm32 C Valid N.E. Add imm32 sign-extended to 64-bits to RAX.
	{ NULL, 0x0009, 0x00840000, { 0x05, 0x00, 0x00 }, _IRA_OPERAND_REG_ACCUMULATOR_OSA_W, _IRA_OPERAND_ID_EX_EOSA, _IRA_NA, _IRA_NA },
	// 80 /0 ib ADD r/m8, imm8 B Valid Valid Add imm8 to r/m8.
	// REX + 80 /0 ib ADD r/m8*, imm8 B Valid N.E. Add sign-extended imm8 to r/m64.
	{ NULL, 0x0001, 0x00C58000, { 0x80, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_8_W, _IRA_OPERAND_IB, _IRA_NA, _IRA_NA },
	// 81 /0 iw ADD r/m16, imm16 B Valid Valid Add imm16 to r/m16.
	// 81 /0 id ADD r/m32, imm32 B Valid Valid Add imm32 to r/m32.
	{ NULL, 0x0001, 0x00C58000, { 0x81, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_W, _IRA_OPERAND_IMM_EOSA, _IRA_NA, _IRA_NA },
	// REX.W + 81 /0 id ADD r/m64, imm32 B Valid N.E. Add imm32 sign-extended to 64-bits to r/m64.
	{ NULL, 0x0009, 0x00858000, { 0x81, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_W, _IRA_OPERAND_ID_EX_EOSA, _IRA_NA, _IRA_NA },
	// 83 /0 ib ADD r/m16, imm8 B Valid Valid Add sign-extended imm8 to r/m16.
	// 83 /0 ib ADD r/m32, imm8 B Valid Valid Add sign-extended imm8 to r/m32.
	{ NULL, 0x0001, 0x00C58000, { 0x83, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_W, _IRA_OPERAND_IB_EX_EOSA, _IRA_NA, _IRA_NA },
	// REX.W + 83 /0 ib ADD r/m64, imm8 B Valid N.E. Add sign-extended imm8 to r/m64.
	{ NULL, 0x0009, 0x00858000, { 0x83, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_W, _IRA_OPERAND_IB_EX_EOSA, _IRA_NA, _IRA_NA },
	// 00 /r ADD r/m8, r8 A Valid Valid Add r8 to r/m8.
	// REX + 00 /r ADD r/m8*, r8* A Valid N.E. Add r8 to r/m8.
	{ NULL, 0x0001, 0x00C48000, { 0x00, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_8_W, _IRA_OPERAND_MODRM_R_8, _IRA_NA, _IRA_NA },
	// 01 /r ADD r/m16, r16 A Valid Valid Add r16 to r/m16.
	// 01 /r ADD r/m32, r32 A Valid Valid Add r32 to r/m32.
	// REX.W + 01 /r ADD r/m64, r64 A Valid N.E. Add r64 to r/m64.
	{ NULL, 0x0001, 0x00C48000, { 0x01, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_W, _IRA_OPERAND_MODRM_R, _IRA_NA, _IRA_NA },
	// 02 /r ADD r8, r/m8 A Valid Valid Add r/m8 to r8.
	// REX + 02 /r ADD r8*, r/m8* A Valid N.E. Add r/m8 to r8.
	{ NULL, 0x0001, 0x00C48000, { 0x02, 0x00, 0x00 }, _IRA_OPERAND_MODRM_R_8_W, _IRA_OPERAND_MODRM_RM_8, _IRA_NA, _IRA_NA },
	// 03 /r ADD r16, r/m16 A Valid Valid Add r/m16 to r16.
	// 03 /r ADD r32, r/m32 A Valid Valid Add r/m32 to r32.
	// REX.W + 03 /r ADD r64, r/m64 A Valid N.E. Add r/m64 to r64.
	{ NULL, 0x0001, 0x00C48000, { 0x03, 0x00, 0x00 }, _IRA_OPERAND_MODRM_R_W, _IRA_OPERAND_MODRM_RM, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_ADDPD[] = {
	// 66 0F 58 /r ADDPD xmm1, xmm2/m128 A Valid Valid Add packed double-precision floating-point values from xmm2/m128 to xmm1.
	{ NULL, 0x1001, 0x00D88000, { 0x0F, 0x58, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_128_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_ADDPS[] = {
	// 0F 58 /r ADDPS xmm1, xmm2/m128 A Valid Valid Add packed single-precision floating-point values from xmm2/m128 to xmm1.
	{ NULL, 0x0001, 0x00D88000, { 0x0F, 0x58, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_128_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_ADDSD[] = {
	// F2 0F 58 /r ADDSD xmm1, xmm2/m64 A Valid Valid Add the low doubleprecision floating-point value from xmm2/m64 to xmm1.
	{ NULL, 0x2001, 0x00D88000, { 0x0F, 0x58, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_64_W, _IRA_OPERAND_MODRM_RM_XMM_64, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_ADDSS[] = {
	// F3 0F 58 /r ADDSS xmm1, xmm2/m32 A Valid Valid Add the low single-precision floating-point value from xmm2/m32 to xmm1.
	{ NULL, 0x4001, 0x00D88000, { 0x0F, 0x58, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_32_W, _IRA_OPERAND_MODRM_RM_XMM_32, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_ADDSUBPD[] = {
	//66 0F D0 /r ADDSUBPD xmm1, xmm2/m128 A Valid Valid Add/subtract doubleprecision floating-point values from xmm2/m128 to xmm1.
	{ NULL, 0x1001, 0x00D88000, { 0x0F, 0xD0, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_128_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_ADDSUBPS[] = {
	// F2 0F D0 /r ADDSUBPS xmm1, xmm2/m128 A Valid Valid Add/subtract singleprecision floating-point values from xmm2/m128 to xmm1.
	{ NULL, 0x2001, 0x00D88000, { 0x0F, 0xD0, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_128_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_AESDEC[] = {
	// 66 0F 38 DE /r AESDEC xmm1,xmm2/m128 A Valid Valid Perform one round of an AES decryption flow, using the Equivalent Inverse Cipher, operating on a 128-bit data (state) from xmm1 with a 128-bit round key from xmm2/m128.
	{ NULL, 0x1001, 0x00EC8000, { 0x0F, 0x38, 0xDE }, _IRA_OPERAND_MODRM_R_XMM_128_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_AESDECLAST[] = {
	// 66 0F 38 DF /r AESDECLAST xmm1,xmm2/m128 A Valid Valid Perform the last round of an AES decryption flow, using the Equivalent Inverse Cipher, operating on a 128-bit data (state) from xmm1 with a 128-bit round key from xmm2/m128.
	{ NULL, 0x1001, 0x00EC8000, { 0x0F, 0x38, 0xDF }, _IRA_OPERAND_MODRM_R_XMM_128_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_AESENC[] = {
	// 66 0F 38 DC /r AESENC xmm1, xmm2/m128 A Valid Valid Perform one round of an AES encryption flow, operating on a 128-bit data (state) from xmm1 with a 128-bit round key from xmm2/m128.
	{ NULL, 0x1001, 0x00EC8000, { 0x0F, 0x38, 0xDC }, _IRA_OPERAND_MODRM_R_XMM_128_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_AESENCLAST[] = {
	//66 0F 38 DD /r AESENCLAST xmm1, xmm2/m128 A Valid Valid Perform the last round of an AES encryption flow, operating on a 128-bit data (state) from xmm1 with a 128-bit round key from xmm2/m128.
	{ NULL, 0x1001, 0x00EC8000, { 0x0F, 0x38, 0xDD }, _IRA_OPERAND_MODRM_R_XMM_128_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_AESIMC[] = {
	// 66 0F 38 DB /r AESIMC xmm1, xmm2/m128 A Valid Valid Perform the InvMixColumn transformation on a 128-bit round key from xmm2/m128 and store the result in xmm1.
	{ NULL, 0x1001, 0x00EC8000, { 0x0F, 0x38, 0xDB }, _IRA_OPERAND_MODRM_R_XMM_128_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_AESKEYGENASSIST[] = {
	// 66 0F 3A DF /r ib AESKEYGENASSIST xmm1, xmm2/m128, imm8 A Valid Valid Assist in AES round key generation using an 8 bits Round Constant (RCON) specified in the immediate byte, operating on 128 bits of data specified in xmm2/m128 and stores the result in xmm1.
	{ NULL, 0x1001, 0x00EC8000, { 0x0F, 0x3A, 0xDF }, _IRA_OPERAND_MODRM_R_XMM_128_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_OPERAND_IB, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_AND[] = {
	// 24 ib AND AL, imm8 C Valid Valid AL AND imm8.
	{ NULL, 0x0001, 0x00C40000, { 0x24, 0x00, 0x00 }, _IRA_OPERAND_REG_ACCUMULATOR_8, _IRA_OPERAND_IB, _IRA_NA, _IRA_NA },
	// 25 iw AND AX, imm16 C Valid Valid AX AND imm16.
	// 25 id AND EAX, imm32 C Valid Valid EAX AND imm32.
	{ NULL, 0x0001, 0x00C40000, { 0x25, 0x00, 0x00 }, _IRA_OPERAND_REG_ACCUMULATOR_OSA_W, _IRA_OPERAND_IMM_EOSA, _IRA_NA, _IRA_NA },
	// REX.W + 25 id AND RAX, imm32 C Valid N.E. RAX AND imm32 signextended to 64-bits.
	{ NULL, 0x0009, 0x00840000, { 0x25, 0x00, 0x00 }, _IRA_OPERAND_REG_ACCUMULATOR_OSA_W, _IRA_OPERAND_ID_EX_EOSA, _IRA_NA, _IRA_NA },
	// 80 /4 ib AND r/m8, imm8 B Valid Valid r/m8 AND imm8.
	// REX + 80 /4 ib AND r/m8*, imm8 B Valid N.E. r/m64 AND imm8 (signextended).
	{ NULL, 0x0001, 0x00C5A000, { 0x80, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_8_W, _IRA_OPERAND_IB, _IRA_NA, _IRA_NA },
	// 81 /4 iw AND r/m16, imm16 B Valid Valid r/m16 AND imm16.
	// 81 /4 id AND r/m32, imm32 B Valid Valid r/m32 AND imm32.
	{ NULL, 0x0001, 0x00C5A000, { 0x81, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_W, _IRA_OPERAND_IMM_EOSA, _IRA_NA, _IRA_NA },
	// REX.W + 81 /4 id AND r/m64, imm32 B Valid N.E. r/m64 AND imm32 sign extended to 64-bits.
	{ NULL, 0x0009, 0x0085A000, { 0x81, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_W, _IRA_OPERAND_ID_EX_EOSA, _IRA_NA, _IRA_NA },
	// 83 /4 ib AND r/m16, imm8 B Valid Valid r/m16 AND imm8 (signextended).
	// 83 /4 ib AND r/m32, imm8 B Valid Valid r/m32 AND imm8 (signextended).
	{ NULL, 0x0001, 0x00C5A000, { 0x83, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_W, _IRA_OPERAND_IB_EX_EOSA, _IRA_NA, _IRA_NA },
	// REX.W + 83 /4 ib AND r/m64, imm8 B Valid N.E. r/m64 AND imm8 (signextended).
	{ NULL, 0x0009, 0x0085A0000, { 0x83, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_W, _IRA_OPERAND_IB_EX_EOSA, _IRA_NA, _IRA_NA },
	// 20 /r AND r/m8, r8 A Valid Valid r/m8 AND r8.
	// REX + 20 /r AND r/m8*, r8* A Valid N.E. r/m64 AND r8 (signextended).
	{ NULL, 0x0001, 0x00C48000, { 0x20, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_8_W, _IRA_OPERAND_MODRM_R_8, _IRA_NA, _IRA_NA },
	// 21 /r AND r/m16, r16 A Valid Valid r/m16 AND r16.
	// 21 /r AND r/m32, r32 A Valid Valid r/m32 AND r32.
	// REX.W + 21 /r AND r/m64, r64 A Valid N.E. r/m64 AND r32.
	{ NULL, 0x0001, 0x00C48000, { 0x21, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_W, _IRA_OPERAND_MODRM_R, _IRA_NA, _IRA_NA },
	// 22 /r AND r8, r/m8 A Valid Valid r8 AND r/m8.
	// REX + 22 /r AND r8*, r/m8* A Valid N.E. r/m64 AND r8 (signextended).
	{ NULL, 0x0001, 0x00C48000, { 0x22, 0x00, 0x00 }, _IRA_OPERAND_MODRM_R_8_W, _IRA_OPERAND_MODRM_RM_8, _IRA_NA, _IRA_NA },
	// 23 /r AND r16, r/m16 A Valid Valid r16 AND r/m16.
	// 23 /r AND r32, r/m32 A Valid Valid r32 AND r/m32.
	// REX.W + 23 /r AND r64, r/m64 A Valid N.E. r64 AND r/m64.
	{ NULL, 0x0001, 0x00C48000, { 0x23, 0x00, 0x00 }, _IRA_OPERAND_MODRM_R_W, _IRA_OPERAND_MODRM_RM, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_ANDPD[] = {
	// 66 0F 54 /r ANDPD xmm1, xmm2/m128 A Valid Valid Bitwise logical AND of xmm2/m128 and xmm1.
	{ NULL, 0x1001, 0x00D88000, { 0x0F, 0x54, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_128_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_ANDPS[] = {
	// 0F 54 /r ANDPS xmm1, xmm2/m128 A Valid Valid Bitwise logical AND of xmm2/m128 and xmm1.
	{ NULL, 0x0001, 0x00D88000, { 0x0F, 0x54, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_128_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_ANDNPD[] = {
	// 66 0F 55 /r ANDNPD xmm1, xmm2/m128 A Valid Valid Bitwise logical AND NOT of xmm2/m128 and xmm1.
	{ NULL, 0x1001, 0x00D88000, { 0x0F, 0x55, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_128_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_ANDNPS[] = {
	// 0F 55 /r ANDNPS xmm1, xmm2/m128 A Valid Valid Bitwise logical AND NOT of xmm2/m128 and xmm1.
	{ NULL, 0x0001, 0x00D88000, { 0x0F, 0x55, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_128_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_ARPL[] = {
	// 63 /r ARPL r/m16, r16 A N. E. Valid Adjust RPL of r/m16 to not less than RPL of r16.
	{ NULL, 0x0001, 0x00448000, { 0x63, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_16, _IRA_OPERAND_MODRM_R_16, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_BLENDPD[] = {
	// 66 0F 3A 0D /r ib BLENDPD xmm1, xmm2/m128, imm8 A Valid Valid Select packed DP-FP values from xmm1 and xmm2/m128 from mask specified in imm8 and store the values into xmm1.
	{ NULL, 0x1001, 0x00EC8000, { 0x0F, 0x3A, 0x0D }, _IRA_OPERAND_MODRM_R_XMM_128_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_OPERAND_IB, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_BLENDPS[] = {
	// 66 0F 3A 0C /r ib BLENDPS xmm1, xmm2/m128, imm8 A Valid Valid Select packed single precision floating-point values from xmm1 and xmm2/m128 from mask specified in imm8 and store the values into xmm1.
	{ NULL, 0x1001, 0x00EC8000, { 0x0F, 0x3A, 0x0C }, _IRA_OPERAND_MODRM_R_XMM_128_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_OPERAND_IB, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_BLENDVPD[] = {
	// 66 0F 38 15 /r BLENDVPD xmm1, xmm2/m128 , <XMM0> A Valid Valid Select packed DP FP values from xmm1 and xmm2 from mask specified in XMM0 and store the values in xmm1.
	{ NULL, 0x1001, 0x00EC8000, { 0x0F, 0x38, 0x15 }, _IRA_OPERAND_MODRM_R_XMM_128_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_IMPLICIT_REG( IRA_REG_XMM, _IRA_REG_XMM0 ), _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_BLENDVPS[] = {
	// 66 0F 38 14 /r BLENDVPS xmm1, xmm2/m128, <XMM0> A Valid Valid Select packed single precision floating-point values from xmm1 and xmm2/m128 from mask specified in XMM0 and store the values into xmm1.
	{ NULL, 0x1001, 0x00EC8000, { 0x0F, 0x38, 0x14 }, _IRA_OPERAND_MODRM_R_XMM_128_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_IMPLICIT_REG( IRA_REG_XMM, _IRA_REG_XMM0 ), _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_BOUND[] = {
	// 62 /r BOUND r16, m16&16 A Invalid Valid Check if r16 (array index) is within bounds specified by m16&16.
	// 62 /r BOUND r32, m32&32 A Invalid Valid Check if r32 (array index) is within bounds specified by m16&16.
	{ NULL, 0x0001, 0x00448000, { 0x62 }, _IRA_OPERAND_MODRM_R, _IRA_OPERAND_MODRM_MM_OSA, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_BSF[] = {
	// 0F BC /r BSF r16, r/m16 A Valid Valid Bit scan forward on r/m16.
	// 0F BC /r BSF r32, r/m32 A Valid Valid Bit scan forward on r/m32.
	// REX.W + 0F BC BSF r64, r/m64 A Valid N.E. Bit scan forward on r/m64.
	{ NULL, 0x0001, 0x00D88000, { 0x0F, 0xBC, 0x00 }, _IRA_OPERAND_MODRM_R_W, _IRA_OPERAND_MODRM_RM, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_BSR[] = {
	// 0F BD /r BSR r16, r/m16 A Valid Valid Bit scan reverse on r/m16.
	// 0F BD /r BSR r32, r/m32 A Valid Valid Bit scan reverse on r/m32.
	// REX.W + 0F BD BSR r64, r/m64 A Valid N.E. Bit scan reverse on r/m64.
	{ NULL, 0x0001, 0x00D88000, { 0x0F, 0xBC, 0x00 }, _IRA_OPERAND_MODRM_R_W, _IRA_OPERAND_MODRM_RM, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_BSWAP[] = {
	// 0F C8+rd BSWAP r32 A Valid* Valid Reverses the byte order of a 32-bit register.
	{ NULL, 0x0001, 0x00D80001, { 0x0F, 0xC8, 0x00 }, _IRA_OPERAND_OPCODE_REG( IRA_REG_GPR_32 ), _IRA_NA, _IRA_NA, _IRA_NA },
	// REX.W + 0F C8+rd BSWAP r64 A Valid N.E. Reverses the byte order of a 64-bit register.
	{ NULL, 0x0009, 0x00980001, { 0x0F, 0xC8, 0x00 }, _IRA_OPERAND_OPCODE_REG( IRA_REG_GPR_64 ), _IRA_NA, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_BT[] = {
	// 0F A3 BT r/m16, r16 A Valid Valid Store selected bit in CF flag.
	// 0F A3 BT r/m32, r32 A Valid Valid Store selected bit in CF flag.
	// REX.W + 0F A3 BT r/m64, r64 A Valid N.E. Store selected bit in CF flag.
	{ NULL, 0x0001, 0x00D88000, { 0x0F, 0xA3, 0x00 }, _IRA_OPERAND_MODRM_RM_W, _IRA_OPERAND_MODRM_R, _IRA_NA, _IRA_NA },
	// 0F BA /4 ib BT r/m16, imm8 B Valid Valid Store selected bit in CF flag.
	// 0F BA /4 ib BT r/m32, imm8 B Valid Valid Store selected bit in CF flag.
	// REX.W + 0F BA /4 ib BT r/m64, imm8 B Valid N.E. Store selected bit in CF flag.
	{ NULL, 0x0001, 0x00D9A000, { 0x0F, 0xBA, 0x00 }, _IRA_OPERAND_MODRM_RM_W, _IRA_OPERAND_IB, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_BTC[] = {
	// 0F BB BTC r/m16, r16 A Valid Valid Store selected bit in CF flag and complement.
	// 0F BB BTC r/m32, r32 A Valid Valid Store selected bit in CF flag and complement.
	// REX.W + 0F BB BTC r/m64, r64 A Valid N.E. Store selected bit in CF flag and complement.
	{ NULL, 0x0001, 0x00D88000, { 0x0F, 0xBB, 0x00 }, _IRA_OPERAND_MODRM_RM_W, _IRA_OPERAND_MODRM_R, _IRA_NA, _IRA_NA },
	// 0F BA /7 ib BTC r/m16, imm8 B Valid Valid Store selected bit in CF flag and complement.
	// 0F BA /7 ib BTC r/m32, imm8 B Valid Valid Store selected bit in CF flag and complement.
	// REX.W + 0F BA /7 ib BTC r/m64, imm8 B Valid N.E. Store selected bit in CF flag and complement.
	{ NULL, 0x0001, 0x00D9B800, { 0x0F, 0xBA, 0x00 }, _IRA_OPERAND_MODRM_RM_W, _IRA_OPERAND_IB, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_BTR[] = {
	// 0F B3 BTR r/m16, r16 A Valid Valid Store selected bit in CF flag and clear.
	// 0F B3 BTR r/m32, r32 A Valid Valid Store selected bit in CF flag and clear.
	// REX.W + 0F B3 BTR r/m64, r64 A Valid N.E. Store selected bit in CF flag and clear.
	{ NULL, 0x0001, 0x00D88000, { 0x0F, 0xB3, 0x00 }, _IRA_OPERAND_MODRM_RM_W, _IRA_OPERAND_MODRM_R, _IRA_NA, _IRA_NA },
	// 0F BA /6 ib BTR r/m16, imm8 B Valid Valid Store selected bit in CF flag and clear.
	// 0F BA /6 ib BTR r/m32, imm8 B Valid Valid Store selected bit in CF flag and clear.
	// REX.W + 0F BA /6 ib BTR r/m64, imm8 B Valid N.E. Store selected bit in CF flag and clear.
	{ NULL, 0x0001, 0x00D9B000, { 0x0F, 0xBA, 0x00 }, _IRA_OPERAND_MODRM_RM_W, _IRA_OPERAND_IB, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_BTS[] = {
	// 0F AB BTS r/m16, r16 A Valid Valid Store selected bit in CF flag and set.
	// 0F AB BTS r/m32, r32 A Valid Valid Store selected bit in CF flag and set.
	// REX.W + 0F AB BTS r/m64, r64 A Valid N.E. Store selected bit in CF flag and set.
	{ NULL, 0x0001, 0x00D88000, { 0x0F, 0xAB, 0x00 }, _IRA_OPERAND_MODRM_RM_W, _IRA_OPERAND_MODRM_R, _IRA_NA, _IRA_NA },
	// 0F BA /5 ib BTS r/m16, imm8 B Valid Valid Store selected bit in CF flag and set.
	// 0F BA /5 ib BTS r/m32, imm8 B Valid Valid Store selected bit in CF flag and set.
	// REX.W + 0F BA /5 ib BTS r/m64, imm8 B Valid N.E. Store selected bit in CF flag and set.
	{ NULL, 0x0001, 0x00D9A800, { 0x0F, 0xBA, 0x00 }, _IRA_OPERAND_MODRM_RM_W, _IRA_OPERAND_IB, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_CALL[] = {
	// E8 cw CALL rel16 B N.S. Valid Call near, relative, displacement relative to next instruction.
	// E8 cd CALL rel32 B Valid Valid Call near, relative, displacement relative to next instruction.
	// 32-bit displacement sign extended to 64-bits in 64-bit mode.
	{ NULL, 0x0001, 0x00440000, { 0xE8, 0x00, 0x00 }, _IRA_OPERAND_IMMEDIATE_DIS_RELATIVE, _IRA_NA, _IRA_NA, _IRA_NA },
	// FF /2 CALL r/m16 B N.E. Valid Call near, absolute indirect, address given in r/m16.
	// FF /2 CALL r/m32 B N.E. Valid Call near, absolute indirect, address given in r/m32.
	// FF /2 CALL r/m64 B Valid N.E. Call near, absolute indirect, address given in r/m64.
	{ NULL, 0x0001, 0x00C59000, { 0xFF, 0x00, 0x00 }, _IRA_OPERAND_CALL_RM, _IRA_NA, _IRA_NA, _IRA_NA },
	// 9A cd CALL ptr16:16 A Invalid Valid Call far, absolute, address given in operand.
	// 9A cp CALL ptr16:32 A Invalid Valid Call far, absolute, address given in operand.
	{ NULL, 0x0001, 0x00440000, { 0x9A, 0x00, 0x00 }, _IRA_OPERAND_FAR_POINTER, _IRA_NA, _IRA_NA, _IRA_NA },
	// FF /3 CALL m16:16 B Valid Valid Call far, absolute indirect address given in m16:16.
	// FF /3 CALL m16:32 B Valid Valid In 64-bit mode.
	// REX.W + FF /3 CALL m16:64 B Valid N.E. In 64-bit mode.
	{ NULL, 0x0001, 0x00C79800, { 0xFF, 0x00, 0x00 }, _IRA_OPERAND_FAR_POINTER_INDIRECT, _IRA_NA, _IRA_NA, _IRA_NA },
};

struct ira_instruction_desc _ira_instructions_desc[] = {
		_IA_INSTRUCTION( "aaa", _ira_opcode_desc_AAA ),
		_IA_INSTRUCTION( "aad", _ira_opcode_desc_AAD ),
		_IA_INSTRUCTION( "aam", _ira_opcode_desc_AAM ),
		_IA_INSTRUCTION( "aas", _ira_opcode_desc_AAS ),
		_IA_INSTRUCTION( "adc", _ira_opcode_desc_ADC ),
		_IA_INSTRUCTION( "add", _ira_opcode_desc_ADD ),
		_IA_INSTRUCTION( "addpd", _ira_opcode_desc_ADDPD ),
		_IA_INSTRUCTION( "addps", _ira_opcode_desc_ADDPS ),
		_IA_INSTRUCTION( "addsd", _ira_opcode_desc_ADDSD ),
		_IA_INSTRUCTION( "addss", _ira_opcode_desc_ADDSS ),
		_IA_INSTRUCTION( "addsubpd", _ira_opcode_desc_ADDSUBPD ),
		_IA_INSTRUCTION( "addsubps", _ira_opcode_desc_ADDSUBPS ),
		_IA_INSTRUCTION( "aesdec", _ira_opcode_desc_AESDEC ),
		_IA_INSTRUCTION( "aesdeclast", _ira_opcode_desc_AESDECLAST ),
		_IA_INSTRUCTION( "aesenc", _ira_opcode_desc_AESENC ),
		_IA_INSTRUCTION( "aesenclast", _ira_opcode_desc_AESENCLAST ),
		_IA_INSTRUCTION( "aesimc", _ira_opcode_desc_AESIMC ),
		_IA_INSTRUCTION( "aeskeygenassist", _ira_opcode_desc_AESKEYGENASSIST ),
		_IA_INSTRUCTION( "and", _ira_opcode_desc_AND ),
		_IA_INSTRUCTION( "andpd", _ira_opcode_desc_ANDPD ),
		_IA_INSTRUCTION( "andps", _ira_opcode_desc_ANDPS ),
		_IA_INSTRUCTION( "andnpd", _ira_opcode_desc_ANDNPD ),
		_IA_INSTRUCTION( "andnps", _ira_opcode_desc_ANDNPS ),
		_IA_INSTRUCTION( "arpl", _ira_opcode_desc_ARPL ),
		_IA_INSTRUCTION( "blendpd", _ira_opcode_desc_BLENDPD),
		_IA_INSTRUCTION( "blendps", _ira_opcode_desc_BLENDPS),
		_IA_INSTRUCTION( "blendvpd", _ira_opcode_desc_BLENDVPD),
		_IA_INSTRUCTION( "blendvps", _ira_opcode_desc_BLENDVPS),
		_IA_INSTRUCTION( "bound", _ira_opcode_desc_BOUND),
		_IA_INSTRUCTION( "bsf", _ira_opcode_desc_BSF),
		_IA_INSTRUCTION( "bsr", _ira_opcode_desc_BSR),
		_IA_INSTRUCTION( "bswap", _ira_opcode_desc_BSWAP),
		_IA_INSTRUCTION( "bt", _ira_opcode_desc_BT),
		_IA_INSTRUCTION( "btc", _ira_opcode_desc_BTC),
		_IA_INSTRUCTION( "btr", _ira_opcode_desc_BTR),
		_IA_INSTRUCTION( "bts", _ira_opcode_desc_BTS),
		_IA_INSTRUCTION( "call", _ira_opcode_desc_CALL),
		{ NULL, 0, 0, NULL }
};





