/*
 * ira_def.c
 *
 *  Created on: 19-11-2010
 *      Author: Slawomir Wojtasiak
 */

#include "ira_int.h"
#include "common.h"

// Instruction descriptions.

#define _IRA_EMPTY_MNEMONIC	""

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
	{ NULL, 0x1001, 0x00EC8000, { 0x0F, 0x38, 0x15 }, _IRA_OPERAND_MODRM_R_XMM_128_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_EXPLICIT_REG_OSA( IRA_REG_XMM, _IRA_REG_XMM0 ), _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_BLENDVPS[] = {
	// 66 0F 38 14 /r BLENDVPS xmm1, xmm2/m128, <XMM0> A Valid Valid Select packed single precision floating-point values from xmm1 and xmm2/m128 from mask specified in XMM0 and store the values into xmm1.
	{ NULL, 0x1001, 0x00EC8000, { 0x0F, 0x38, 0x14 }, _IRA_OPERAND_MODRM_R_XMM_128_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_EXPLICIT_REG_OSA( IRA_REG_XMM, _IRA_REG_XMM0 ), _IRA_NA }
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
	{ NULL, 0x0001, 0x00D80001, { 0x0F, 0xC8, 0x00 }, _IRA_OPERAND_OPCODE_REG( IRA_REG_GPR, _IRA_GPRS_32 ), _IRA_NA, _IRA_NA, _IRA_NA },
	// REX.W + 0F C8+rd BSWAP r64 A Valid N.E. Reverses the byte order of a 64-bit register.
	{ NULL, 0x0009, 0x00980001, { 0x0F, 0xC8, 0x00 }, _IRA_OPERAND_OPCODE_REG( IRA_REG_GPR, _IRA_GPRS_64 ), _IRA_NA, _IRA_NA, _IRA_NA }
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
	{ NULL, 0x0001, 0x00C40000, { 0xE8, 0x00, 0x00 }, _IRA_OPERAND_IMMEDIATE_DIS_RELATIVE_EOSA, _IRA_NA, _IRA_NA, _IRA_NA },
	// FF /2 CALL r/m16 B N.E. Valid Call near, absolute indirect, address given in r/m16.
	// FF /2 CALL r/m32 B N.E. Valid Call near, absolute indirect, address given in r/m32.
	// FF /2 CALL r/m64 B Valid N.E. Call near, absolute indirect, address given in r/m64.
	{ NULL, 0x0001, 0x40C59000, { 0xFF, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM, _IRA_NA, _IRA_NA, _IRA_NA },
	// 9A cd CALL ptr16:16 A Invalid Valid Call far, absolute, address given in operand.
	// 9A cp CALL ptr16:32 A Invalid Valid Call far, absolute, address given in operand.
	{ NULL, 0x0001, 0x00440000, { 0x9A, 0x00, 0x00 }, _IRA_OPERAND_FAR_POINTER, _IRA_NA, _IRA_NA, _IRA_NA },
	// FF /3 CALL m16:16 B Valid Valid Call far, absolute indirect address given in m16:16.
	// FF /3 CALL m16:32 B Valid Valid In 64-bit mode.
	// REX.W + FF /3 CALL m16:64 B Valid N.E. In 64-bit mode.
	{ NULL, 0x0001, 0x00C59800, { 0xFF, 0x00, 0x00 }, _IRA_OPERAND_FAR_POINTER_INDIRECT, _IRA_NA, _IRA_NA, _IRA_NA },
};

struct ira_opcode_desc _ira_opcode_desc_CBW[] = {
	// 98 CBW A Valid Valid AX  sign-extend of AL.
	{ "cbw", 0x0001, 0x01C40000, { 0x98, 0x00, 0x00 }, _IRA_NA, _IRA_NA, _IRA_NA, _IRA_NA },
	// 98 CWDE A Valid Valid EAX  sign-extend of AX.
	{ "cwde", 0x0001, 0x02C40000, { 0x98, 0x00, 0x00 }, _IRA_NA, _IRA_NA, _IRA_NA, _IRA_NA },
	// REX.W + 98 CDQE A Valid N.E. RAX  sign-extend of EAX.
	{ "cdqe", 0x0001, 0x04C40000, { 0x98, 0x00, 0x00 }, _IRA_NA, _IRA_NA, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_CLC[] = {
	// F8 CLC A Valid Valid Clear CF flag.
	{ NULL, 0x0001, 0x00C40000, { 0xF8, 0x00, 0x00 }, _IRA_NA, _IRA_NA, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_CLD[] = {
	// F8 CLC A Valid Valid Clear CF flag.
	{ NULL, 0x0001, 0x00C40000, { 0xFC, 0x00, 0x00 }, _IRA_NA, _IRA_NA, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_CLFLUSH[] = {
	// 0F AE /7 CLFLUSH m8 A Valid Valid Flushes cache line containing m8.
	{ NULL, 0x0001, 0x00D9B800, { 0x0F, 0xAE, 0x00 }, _IRA_OPERAND_MODRM_M_8_W, _IRA_NA, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_CLI[] = {
	// FA CLI A Valid Valid Clear interrupt flag interrupts disabled when interrupt flag cleared.
	{ NULL, 0x0001, 0x00C40000, { 0xFA, 0x00, 0x00 }, _IRA_NA, _IRA_NA, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_CLTS[] = {
	// 0F 06 CLTS A Valid Valid Clears TS flag in CR0.
	{ NULL, 0x0001, 0x00D80000, { 0x0F, 0x06, 0x00 }, _IRA_NA, _IRA_NA, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_CMC[] = {
	// F5 CMC A Valid Valid Complement CF flag. Op/En
	{ NULL, 0x0001, 0x00C40000, { 0xF5, 0x00, 0x00 }, _IRA_NA, _IRA_NA, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_CMOVA[] = {
	// 0F 4X /r CMOVA r16, r/m16 A Valid Valid Move if above (CF=0 and ZF=0).
	// 0F 4X /r CMOVA r32, r/m32 A Valid Valid Move if above (CF=0 and ZF=0).
	// REX.W + 0F 4X /r CMOVA r64, r/m64 A Valid N.E. Move if above (CF=0 and ZF=0).
	{ NULL, 0x0001, 0x00D88040, { 0x0F, 0x40, 0x00 }, _IRA_OPERAND_MODRM_R_W, _IRA_OPERAND_MODRM_RM, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_JCXZ[] = {
	// E3 cb JCXZ rel8 A N.E. Valid Jump short if CX register is 0.
	{ "jcxz", 0x0001, 0x08440000, { 0xE3, 0x00, 0x00 }, _IRA_OPERAND_IMMEDIATE_DIS_RELATIVE_R_8, _IRA_NA, _IRA_NA, _IRA_NA },
	// E3 cb JECXZ rel8 A Valid Valid Jump short if ECX register is 0.
	{ "jecxz", 0x0001, 0x50C40000, { 0xE3, 0x00, 0x00 }, _IRA_OPERAND_IMMEDIATE_DIS_RELATIVE_R_8, _IRA_NA, _IRA_NA, _IRA_NA },
	// E3 cb JRCXZ rel8 A Valid N.E. Jump short if RCX register is 0.
	{ "jrcxz", 0x0001, 0x60840000, { 0xE3, 0x00, 0x00 }, _IRA_OPERAND_IMMEDIATE_DIS_RELATIVE_R_8, _IRA_NA, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_Jcc[] = {
	// JA rel8 A Valid Valid Jump short if ...
	{ NULL, 0x0001, 0x40C40040, { 0x70, 0x00, 0x00 }, _IRA_OPERAND_IMMEDIATE_DIS_RELATIVE_R_8, _IRA_NA, _IRA_NA, _IRA_NA },
	// JA rel32 A Valid Valid Jump near if ...
	// JAE rel16 A N.S. Valid Jump near if ...
	{ NULL, 0x0001, 0x40D80040, { 0x0F, 0x80, 0x00 }, _IRA_OPERAND_IMMEDIATE_DIS_RELATIVE_EOSA, _IRA_NA, _IRA_NA, _IRA_NA },
};

struct ira_opcode_desc _ira_opcode_desc_JMP[] = {
	// EB cb JMP rel8 A Valid Valid Jump short, RIP = RIP + 8-bit displacement sign extended to 64-bits
	{ NULL, 0x0001, 0x40C40000, { 0xEB, 0x00, 0x00 }, _IRA_OPERAND_IMMEDIATE_DIS_RELATIVE_R_8, _IRA_NA, _IRA_NA, _IRA_NA },
	// E9 cw JMP rel16 A N.S. Valid Jump near, relative, displacement relative to next instruction. Not supported in 64-bit mode.
	// E9 cd JMP rel32 A Valid Valid Jump near, relative, RIP = RIP + 32-bit displacement sign extended to 64-bits
	{ NULL, 0x0001, 0x40C40000, { 0xE9, 0x00, 0x00 }, _IRA_OPERAND_IMMEDIATE_DIS_RELATIVE_EOSA, _IRA_NA, _IRA_NA, _IRA_NA },
	// FF /4 JMP r/m16 B N.S. Valid Jump near, absolute indirect, address = zero-extended r/m16. Not supported in 64- bit mode.
	// FF /4 JMP r/m32 B N.S. Valid Jump near, absolute indirect, address given in r/m32. Not supported in 64-bit mode.
	// FF /4 JMP r/m64 B Valid N.E. Jump near, absolute indirect, RIP = 64-Bit offset from register or memory
	{ NULL, 0x0001, 0x40C5A000, { 0xFF, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM, _IRA_NA, _IRA_NA, _IRA_NA },
	// EA cd JMP ptr16:16 A Inv. Valid Jump far, absolute, address given in operand
	// EA cp JMP ptr16:32 A Inv. Valid Jump far, absolute, address given in operand
	{ NULL, 0x0001, 0x00440000, { 0xEA, 0x00, 0x00 }, _IRA_OPERAND_FAR_POINTER, _IRA_NA, _IRA_NA, _IRA_NA },
	// FF /5 JMP m16:16 A Valid Valid Jump far, absolute indirect, address given in m16:16
	// FF /5 JMP m16:32 A Valid Valid Jump far, absolute indirect, address given in m16:32.
	// REX.W + FF /5 JMP m16:64 A Valid N.E. Jump far, absolute indirect, address given in m16:64.
	{ NULL, 0x0001, 0x00C5A800, { 0xFF, 0x00, 0x00 }, _IRA_OPERAND_FAR_POINTER_INDIRECT, _IRA_NA, _IRA_NA, _IRA_NA }
};

// TODO: Sprobowac polaczyc z ADC/ADD it, moze jakis pattern?

//TODO: tests.
struct ira_opcode_desc _ira_opcode_desc_CMP[] = {
	// 3C ib CMP AL, imm8 D Valid Valid Compare imm8 with AL.
	{ NULL, 0x0001, 0x00C40000, { 0x3C, 0x00, 0x00 }, _IRA_OPERAND_REG_ACCUMULATOR_8, _IRA_OPERAND_IB, _IRA_NA, _IRA_NA },
	// 3D iw CMP AX, imm16 D Valid Valid Compare imm16 with AX.
	// 3D id CMP EAX, imm32 D Valid Valid Compare imm32 with EAX.
	{ NULL, 0x0001, 0x00C40000, { 0x3D, 0x00, 0x00 }, _IRA_OPERAND_REG_ACCUMULATOR_OSA_W, _IRA_OPERAND_IMM_EOSA, _IRA_NA, _IRA_NA },
	// REX.W + 3D id CMP RAX, imm32 D Valid N.E. Compare imm32 sign extended to 64-bits with RAX.
	{ NULL, 0x0009, 0x00840000, { 0x3D, 0x00, 0x00 }, _IRA_OPERAND_REG_ACCUMULATOR_OSA_W, _IRA_OPERAND_ID_EX_EOSA, _IRA_NA, _IRA_NA },
	// 80 /7 ib CMP r/m8, imm8 C Valid Valid Compare imm8 with r/m8.
	// REX + 80 /7 ib CMP r/m8*, imm8 C Valid N.E. Compare imm8 with r/m8.
	{ NULL, 0x0001, 0x00C5B800, { 0x80, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_8_W, _IRA_OPERAND_IB, _IRA_NA, _IRA_NA },
	// 81 /7 iw CMP r/m16, imm16 C Valid Valid Compare imm16 with r/m16.
	// 81 /7 id CMP r/m32, imm32 C Valid Valid Compare imm32 with r/m32.
	{ NULL, 0x0001, 0x00C5B800, { 0x81, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_W, _IRA_OPERAND_IMM_EOSA, _IRA_NA, _IRA_NA },
	// REX.W + 81 /7 id CMP r/m64, imm32 C Valid N.E. Compare imm32 sign extended to 64-bits with r/m64.
	{ NULL, 0x0009, 0x0085B800, { 0x81, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_W, _IRA_OPERAND_ID_EX_EOSA, _IRA_NA, _IRA_NA },
	// 83 /7 ib CMP r/m16, imm8 C Valid Valid Compare imm8 with r/m16.
	// 83 /7 ib CMP r/m32, imm8 C Valid Valid Compare imm8 with r/m32.
	{ NULL, 0x0001, 0x00C5B800, { 0x83, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_W, _IRA_OPERAND_IB_EX_EOSA, _IRA_NA, _IRA_NA },
	// REX.W + 83 /7 ib CMP r/m64, imm8 C Valid N.E. Compare imm8 with r/m64.
	{ NULL, 0x0009, 0x0085B800, { 0x83, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_W, _IRA_OPERAND_IB_EX_EOSA, _IRA_NA, _IRA_NA },
	// 38 /r CMP r/m8, r8 B Valid Valid Compare r8 with r/m8.
	// REX + 38 /r CMP r/m8*, r8* B Valid N.E. Compare r8 with r/m8.
	{ NULL, 0x0001, 0x00C48000, { 0x38, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_8_W, _IRA_OPERAND_MODRM_R_8, _IRA_NA, _IRA_NA },
	// 39 /r CMP r/m16, r16 B Valid Valid Compare r16 with r/m16.
	// 39 /r CMP r/m32, r32 B Valid Valid Compare r32 with r/m32.
	// REX.W + 39 /r CMP r/m64,r64 B Valid N.E. Compare r64 with r/m64.
	{ NULL, 0x0001, 0x00C48000, { 0x39, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_W, _IRA_OPERAND_MODRM_R, _IRA_NA, _IRA_NA },
	// 3A /r CMP r8, r/m8 A Valid Valid Compare r/m8 with r8.
	// REX + 3A /r CMP r8*, r/m8* A Valid N.E. Compare r/m8 with r8.
	{ NULL, 0x0001, 0x00C48000, { 0x3A, 0x00, 0x00 }, _IRA_OPERAND_MODRM_R_8_W, _IRA_OPERAND_MODRM_RM_8, _IRA_NA, _IRA_NA },
	// 3B /r CMP r16, r/m16 A Valid Valid Compare r/m16 with r16.
	// 3B /r CMP r32, r/m32 A Valid Valid Compare r/m32 with r32.
	// REX.W + 3B /r CMP r64, r/m64 A Valid N.E. Compare r/m64 with r64.
	{ NULL, 0x0001, 0x00C48000, { 0x3B, 0x00, 0x00 }, _IRA_OPERAND_MODRM_R_W, _IRA_OPERAND_MODRM_RM, _IRA_NA, _IRA_NA }
};

// TODO: Poalczyc z BLENDPS

//TODO: tests.
struct ira_opcode_desc _ira_opcode_desc_CMPPD[] = {
	// 66 0F C2 /r ib CMPPD xmm1, xmm2/m128, imm8 A Valid Valid Compare packed doubleprecision floating-point values in xmm2/m128 and xmm1 using imm8 as comparison predicate.
	{ NULL, 0x1001, 0x00D88000, { 0x0F, 0xC2, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_128_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_OPERAND_IB, _IRA_NA }
};

//TODO: tests.
struct ira_opcode_desc _ira_opcode_desc_CMPPS[] = {
	// 0F C2 /r ib CMPPS xmm1, xmm2/m128, imm8 A Valid Valid Compare packed singleprecision floating-point values in xmm2/mem and xmm1 using imm8 as comparison predicate.
	{ NULL, 0x0001, 0x00D88000, { 0x0F, 0xC2, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_128_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_OPERAND_IB, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_CMPS[] = {
	// A6 CMPS m8, m8 A Valid Valid For legacy mode, compare byte at address DS:(E)SI with byte at address ES:(E)DI; For 64-bit mode compare byte at address (R|E)SI to byte at address (R|E)DI. The status flags are set accordingly.
	{ NULL, 0x0001, 0x00C40000, { 0xA6, 0x00, 0x00 },
			_IRA_EXPLICIT_GPS_REG_ADDRESSING( _IRA_REG_SI, _IRA_EOS_BYTE, _IRA_SEG_ENCODE_REGISTER( _IRA_SEG_REG_DS, _IRA_SEG_ALLOW_OVERRIDE ) ),
			_IRA_EXPLICIT_GPS_REG_ADDRESSING( _IRA_REG_DI, _IRA_EOS_BYTE, _IRA_SEG_ENCODE_REGISTER( _IRA_SEG_REG_ES, _IRA_SEG_DENY_OVERRIDE ) ),
			_IRA_NA, _IRA_NA },
	// A7 CMPS m16, m16 A Valid Valid For legacy mode, compare word at address DS:(E)SI with word at address ES:(E)DI; For 64-bit mode compare word at address (R|E)SI with word at address (R|E)DI. The status flags are set accordingly.
	// A7 CMPS m32, m32 A Valid Valid For legacy mode, compare dword at address DS:(E)SI at dword at address ES:(E)DI; For 64-bit mode compare dword at address (R|E)SI at dword at address (R|E)DI. The status flags are set accordingly.
	// REX.W + A7 CMPS m64, m64 A Valid N.E. Compares quadword at address (R|E)SI with quadword at address (R|E)DI and sets the status flags accordingly.
	{ NULL, 0x0001, 0x00C40000, { 0xA7, 0x00, 0x00 },
			_IRA_EXPLICIT_GPS_REG_ADDRESSING( _IRA_REG_SI, _IRA_EOS_EOSA,_IRA_SEG_ENCODE_REGISTER( _IRA_SEG_REG_DS, _IRA_SEG_ALLOW_OVERRIDE ) ),
			_IRA_EXPLICIT_GPS_REG_ADDRESSING( _IRA_REG_DI, _IRA_EOS_EOSA,_IRA_SEG_ENCODE_REGISTER( _IRA_SEG_REG_ES, _IRA_SEG_DENY_OVERRIDE ) ),
			_IRA_NA, _IRA_NA }
};

//TODO: tests.
struct ira_opcode_desc _ira_opcode_desc_CMPSD[] = {
	// F2 0F C2 /r ib CMPSD xmm1, xmm2/m64, imm8 A Valid Valid Compare low doubleprecision floating-point value in xmm2/m64 and xmm1 using imm8 as comparison predicate.
	{ NULL, 0x2001, 0x00D88000, { 0x0F, 0xC2, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_64_W, _IRA_OPERAND_MODRM_RM_XMM_64, _IRA_OPERAND_IB, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_CMPSS[] = {
	// F3 0F C2 /r ib CMPSS xmm1, xmm2/m32, imm8 A Valid Valid Compare low singleprecision floating-point value in xmm2/m32 and xmm1 using imm8 as comparison predicate.
	{ NULL, 0x4001, 0x00D88000, { 0x0F, 0xC2, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_32_W, _IRA_OPERAND_MODRM_RM_XMM_32, _IRA_OPERAND_IB, _IRA_NA }
};

// TODO: tests.
struct ira_opcode_desc _ira_opcode_desc_CMPXCHG[] = {
	// 0F B0/r CMPXCHG r/m8, r8 A Valid Valid* Compare AL with r/m8. If equal, ZF is set and r8 is loaded into r/m8. Else, clear ZF and load r/m8 into AL.
	// REX + 0F B0/r CMPXCHG r/m8**,r8 A Valid N.E. Compare AL with r/m8. If equal, ZF is set and r8 is loaded into r/m8. Else, clear ZF and load r/m8 into AL.
	{ NULL, 0x0001, 0x00D88000, { 0x0F, 0xB0, 0x00 }, _IRA_OPERAND_MODRM_RM_8_W, _IRA_OPERAND_MODRM_R_8, _IRA_NA, _IRA_NA },
	// 0F B1/r CMPXCHG r/m16, r16 A Valid Valid* Compare AX with r/m16. If equal, ZF is set and r16 is loaded into r/m16. Else, clear ZF and load r/m16 into AX.
	// 0F B1/r CMPXCHG r/m32, r32 A Valid Valid* Compare EAX with r/m32. If equal, ZF is set and r32 is loaded into r/m32. Else, clear ZF and load r/m32 into EAX.
	// REX.W + 0F B1/r CMPXCHG r/m64, r64 A Valid N.E. Compare RAX with r/m64. If equal, ZF is set and r64 is loaded into r/m64. Else, clear ZF and load r/m64 into RAX.
	{ NULL, 0x0001, 0x00D88000, { 0x0F, 0xB1, 0x00 }, _IRA_OPERAND_MODRM_RM_W, _IRA_OPERAND_MODRM_R, _IRA_NA, _IRA_NA },
};

struct ira_opcode_desc _ira_opcode_desc_CMPXCHGxB[] = {
	// 0F C7 /1 m64 CMPXCHG8B m64 A Valid Valid* Compare EDX:EAX with m64. If equal, set ZF and load ECX:EBX into m64. Else, clear ZF and load m64 into EDX:EAX.
	// REX.W + 0F C7 /1 m128 CMPXCHG16B m128 A Valid N.E. Compare RDX:RAX with m128. If equal, set ZF and load RCX:RBX into m128. Else, clear ZF and load m128 into RDX:RAX.
	{ "cmpxchg8b", 0x0001, 0x03D98800, { 0x0F, 0xC7, 0x00 }, _IRA_OPERAND_MODRM_MM_OSA, _IRA_NA, _IRA_NA, _IRA_NA },
	{ "cmpxchg16b", 0x0001, 0x04D98800, { 0x0F, 0xC7, 0x00 }, _IRA_OPERAND_MODRM_MM_OSA, _IRA_NA, _IRA_NA, _IRA_NA },
};

// MMWORD
struct ira_opcode_desc _ira_opcode_desc_COMISD[] = {
	// 66 0F 2F /r COMISD xmm1, xmm2/m64 A Valid Valid Compare low doubleprecision floating-point values in xmm1 and xmm2/mem64 and set the EFLAGS flags accordingly.
	{ NULL, 0x1001, 0x00D88000, { 0x0F, 0x2F, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_64_W, _IRA_OPERAND_MODRM_RM_XMM_64, _IRA_NA, _IRA_NA }
};

// MMWORD
struct ira_opcode_desc _ira_opcode_desc_COMISS[] = {
	// 0F 2F /r COMISS xmm1, xmm2/m32 A Valid Valid Compare low singleprecision floating-point values in xmm1 and xmm2/mem32 and set the EFLAGS flags accordingly.
	{ NULL, 0x0001, 0x00D88000, { 0x0F, 0x2F, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_32_W, _IRA_OPERAND_MODRM_RM_XMM_32, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_CPUID[] = {
	// 0F A2 CPUID A Valid Valid Returns processor identification and feature information to the EAX, EBX, ECX, and EDX registers, as determined by input entered in EAX (in some cases, ECX as well).
	{ NULL, 0x0001, 0x00D80000, { 0x0F, 0xA2, 0x00 }, _IRA_NA, _IRA_NA, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_CRC32[] = {
	// F2 0F 38 F0 /r CRC32 r32, r/m8 A Valid Valid Accumulate CRC32 on r/m8.
	// F2 REX 0F 38 F0 /r CRC32 r32, r/m8* A Valid N.E. Accumulate CRC32 on r/m8.
	{ NULL, 0x2001, 0x03EC8000, { 0x0F, 0x38, 0xF0 }, _IRA_OPERAND_MODRM_R_32_W, _IRA_OPERAND_MODRM_RM_8, _IRA_NA, _IRA_NA },
	// F2 REX.W 0F 38 F0 /r CRC32 r64, r/m8 A Valid N.E. Accumulate CRC32 on r/m8.
	{ NULL, 0x2009, 0x04AC8000, { 0x0F, 0x38, 0xF0 }, _IRA_OPERAND_MODRM_R_64_W, _IRA_OPERAND_MODRM_RM_8, _IRA_NA, _IRA_NA },
	// F2 0F 38 F1 /r CRC32 r32, r/m16 A Valid Valid Accumulate CRC32 on r/m16.
	// F2 0F 38 F1 /r CRC32 r32, r/m32 A Valid Valid Accumulate CRC32 on r/m32.
	{ NULL, 0x2001, 0x03EC8000, { 0x0F, 0x38, 0xF1 }, _IRA_OPERAND_MODRM_R_32_W, _IRA_OPERAND_MODRM_RM, _IRA_NA, _IRA_NA },
	// F2 REX.W 0F 38 F1 /r CRC32 r64, r/m64 A Valid N.E. Accumulate CRC32 on r/m64.
	{ NULL, 0x2009, 0x04AC8000, { 0x0F, 0x38, 0xF1 }, _IRA_OPERAND_MODRM_R_64_W, _IRA_OPERAND_MODRM_RM, _IRA_NA, _IRA_NA },
};

// MMWORD
struct ira_opcode_desc _ira_opcode_desc_CVTDQ2PD[] = {
	// F3 0F E6 CVTDQ2PD xmm1, xmm2/m64 A Valid Valid Convert two packed signed doubleword integers from xmm2/m128 to two packed double-precision floatingpoint values in xmm1.
	{ NULL, 0x4001, 0x00D88000, { 0x0F, 0xE6, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_64_W, _IRA_OPERAND_MODRM_RM_XMM_64, _IRA_NA, _IRA_NA }
};

// XMMWORD
struct ira_opcode_desc _ira_opcode_desc_CVTDQ2PS[] = {
	// 0F 5B /r CVTDQ2PS xmm1, xmm2/m128 A Valid Valid Convert four packed signed doubleword integers from xmm2/m128 to four packed single-precision floatingpoint
	{ NULL, 0x0001, 0x00D88000, { 0x0F, 0x5B, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_128_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA }
};

// XMMWORD
struct ira_opcode_desc _ira_opcode_desc_CVTPD2DQ[] = {
	// F2 0F E6 CVTPD2DQ xmm1, xmm2/m128 A Valid Valid Convert two packed doubleprecision floating-point values from xmm2/m128 to two packed signed doubleword integers in xmm1.
	{ NULL, 0x2001, 0x00D88000, { 0x0F, 0xE6, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_128_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA }
};

// XMMWORD
struct ira_opcode_desc _ira_opcode_desc_CVTPD2PI[] = {
	// 66 0F 2D /r CVTPD2PI mm, xmm/m128 A Valid Valid Convert two packed doubleprecision floating-point values from xmm/m128 to two packed signed doubleword integers in mm.
	{ NULL, 0x1001, 0x00D88000, { 0x0F, 0x2D, 0x00 }, _IRA_OPERAND_MODRM_R_MMX_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA }
};

// XMMWORD
struct ira_opcode_desc _ira_opcode_desc_CVTPD2PS[] = {
	// 66 0F 5A /r CVTPD2PS//  xmm1,xmm2/m128 A Valid Valid Convert two packed doubleprecision floating-point values in xmm2/m128 to two packed single-precision floating-point values in xmm1.
	{ NULL, 0x1001, 0x00D88000, { 0x0F, 0x5A, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_128_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA }
};

// XMMWORD
struct ira_opcode_desc _ira_opcode_desc_CVTPI2PD[] = {
	// 66 0F 2A /r CVTPI2PD xmm, mm/m64* A Valid Valid Convert two packed signed doubleword integers from mm/mem64 to two packed double-precision floatingpoint values in xmm.
	{ NULL, 0x1001, 0x00D88000, { 0x0F, 0x2A, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_128_W, _IRA_OPERAND_MODRM_RM_MMX, _IRA_NA, _IRA_NA }
};

// XMMWORD
struct ira_opcode_desc _ira_opcode_desc_CVTPI2PS[] = {
	// 0F 2A /r CVTPI2PS xmm, mm/m64 A Valid Valid Convert two signed doubleword integers from mm/m64 to two singleprecision floating-point values in xmm.
	{ NULL, 0x0001, 0x00D88000, { 0x0F, 0x2A, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_128_W, _IRA_OPERAND_MODRM_RM_MMX, _IRA_NA, _IRA_NA }
};

// XMMWORD
struct ira_opcode_desc _ira_opcode_desc_CVTPS2DQ[] = {
	// 66 0F 5B /r CVTPS2DQ xmm1, xmm2/m128 A Valid Valid Convert four packed singleprecision floating-point values from xmm2/m128 to four packed signed doubleword integers in xmm1.
	{ NULL, 0x1001, 0x00D88000, { 0x0F, 0x5B, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_128_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA }
};

// XMMWORD
struct ira_opcode_desc _ira_opcode_desc_CVTPS2PD[] = {
	// 0F 5A /r CVTPS2PD xmm1, xmm2/m64 A Valid Valid Convert two packed singleprecision floating-point values in xmm2/m64 to two packed double-precision floating-point values in xmm1.
	{ NULL, 0x0001, 0x00D88000, { 0x0F, 0x5A, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_128_W, _IRA_OPERAND_MODRM_RM_XMM_64, _IRA_NA, _IRA_NA }
};

// XMMWORD
struct ira_opcode_desc _ira_opcode_desc_CVTPS2PI[] = {
	// 0F 2D /r CVTPS2PI mm, xmm/m64 A Valid Valid Convert two packed singleprecision floating-point values from xmm/m64 to two packed signed doubleword integers in mm.
	{ NULL, 0x0001, 0x00D88000, { 0x0F, 0x2D, 0x00 }, _IRA_OPERAND_MODRM_R_MMX_W, _IRA_OPERAND_MODRM_RM_XMM_64, _IRA_NA, _IRA_NA }
};

// MMWORD
struct ira_opcode_desc _ira_opcode_desc_CVTSD2SI[] = {
	// F2 0F 2D /r CVTSD2SI r32, xmm/m64 A Valid Valid Convert one doubleprecision floating-point value from xmm/m64 to one signed doubleword integer r32.
	{ NULL, 0x2001, 0x03D88000, { 0x0F, 0x2D, 0x00 }, _IRA_OPERAND_MODRM_R_32_W, _IRA_OPERAND_MODRM_RM_XMM_64, _IRA_NA, _IRA_NA },
	// F2 REX.W 0F 2D /r CVTSD2SI r64, xmm/m64 A Valid N.E. Convert one doubleprecision floating-point value from xmm/m64 to one signed quadword integer sign-extended into r64.
	{ NULL, 0x2009, 0x04988000, { 0x0F, 0x2D, 0x00 }, _IRA_OPERAND_MODRM_R_64_W, _IRA_OPERAND_MODRM_RM_XMM_64, _IRA_NA, _IRA_NA },
};

// MMWORD
struct ira_opcode_desc _ira_opcode_desc_CVTSD2SS[] = {
	// F2 0F 5A /r CVTSD2SS xmm1, xmm2/m64 A Valid Valid Convert one doubleprecision floating-point value in xmm2/m64 to one single-precision floatingpoint value in xmm1.
	{ NULL, 0x2001, 0x00D88000, { 0x0F, 0x5A, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_128_W, _IRA_OPERAND_MODRM_RM_XMM_64, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_CVTSI2SD[] = {
	// F2 0F 2A /r CVTSI2SD xmm, r/m32 A Valid Valid Convert one signed doubleword integer from r/m32 to one doubleprecision floating-point value in xmm.
	{ NULL, 0x2001, 0x03D88000, { 0x0F, 0x2A, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_128_W, _IRA_OPERAND_MODRM_RM_32, _IRA_NA, _IRA_NA },
	// F2 REX.W 0F 2A /r CVTSI2SD xmm, r/m64 A Valid N.E. Convert one signed quadword integer from r/m64 to one doubleprecision floating-point value in xmm.
	{ NULL, 0x2009, 0x04988000, { 0x0F, 0x2A, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_128_W, _IRA_OPERAND_MODRM_RM_64, _IRA_NA, _IRA_NA },
};

struct ira_opcode_desc _ira_opcode_desc_CVTSI2SS[] = {
	// F3 0F 2A /r CVTSI2SS xmm, r/m32 A Valid Valid Convert one signed doubleword integer from r/m32 to one singleprecision floating-point value in xmm.
	{ NULL, 0x4001, 0x03D88000, { 0x0F, 0x2A, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_128_W, _IRA_OPERAND_MODRM_RM_32, _IRA_NA, _IRA_NA },
	// F3 REX.W 0F 2A /r CVTSI2SS xmm, r/m64 A Valid N.E. Convert one signed quadword integer from r/m64 to one singleprecision floating-point value in xmm.
	{ NULL, 0x4009, 0x04988000, { 0x0F, 0x2A, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_128_W, _IRA_OPERAND_MODRM_RM_64, _IRA_NA, _IRA_NA },
};

// MMWORD
struct ira_opcode_desc _ira_opcode_desc_CVTSS2SD[] = {
	// F3 0F 5A /r CVTSS2SD xmm1, xmm2/m32 A Valid Valid Convert one single-precision floating-point value in xmm2/m32 to one doubleprecision floating-point value in xmm1.
	{ NULL, 0x4001, 0x00D88000, { 0x0F, 0x5A, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_128_W, _IRA_OPERAND_MODRM_RM_XMM_32, _IRA_NA, _IRA_NA }
};

// MMWORD
struct ira_opcode_desc _ira_opcode_desc_CVTSS2SI[] = {
	// F3 0F 2D /r CVTSS2SI r32, xmm/m32 A Valid Valid Convert one single-precision floating-point value from xmm/m32 to one signed doubleword integer in r32.
	{ NULL, 0x4001, 0x03D88000, { 0x0F, 0x2D, 0x00 }, _IRA_OPERAND_MODRM_R_32_W, _IRA_OPERAND_MODRM_RM_XMM_32, _IRA_NA, _IRA_NA },
	// F3 REX.W 0F 2D /r CVTSS2SI r64, xmm/m32 A Valid N.E. Convert one single-precision floating-point value from xmm/m32 to one signed quadword integer in r64.
	{ NULL, 0x4009, 0x04988000, { 0x0F, 0x2D, 0x00 }, _IRA_OPERAND_MODRM_R_64_W, _IRA_OPERAND_MODRM_RM_XMM_32, _IRA_NA, _IRA_NA },
};

// XMMWORD
struct ira_opcode_desc _ira_opcode_desc_CVTTPD2DQ[] = {
	// 66 0F E6 CVTTPD2DQ xmm1, xmm2/m128 A Valid Valid Convert two packed doubleprecision floating-point values from xmm2/m128 to two packed signed doubleword integers in xmm1 using truncation.
	{ NULL, 0x1001, 0x00D88000, { 0x0F, 0xE6, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_128_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA }
};

// XMMWORD
struct ira_opcode_desc _ira_opcode_desc_CVTTPD2PI[] = {
	// 66 0F 2C /r CVTTPD2PI mm, xmm/m128 A Valid Valid Convert two packer doubleprecision floating-point values from xmm/m128 to two packed signed doubleword integers in mm using truncation.
	{ NULL, 0x1001, 0x00D88000, { 0x0F, 0x2C, 0x00 }, _IRA_OPERAND_MODRM_R_MMX_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA }
};

// XMMWORD
struct ira_opcode_desc _ira_opcode_desc_CVTTPS2DQ[] = {
	// F3 0F 5B /r CVTTPS2DQ xmm1, xmm2/m128 A Valid Valid Convert four singleprecision floating-point values from xmm2/m128 to four signed doubleword integers in xmm1 using truncation.
	{ NULL, 0x4001, 0x00D88000, { 0x0F, 0x5B, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_128_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA }
};

// XMMWORD
struct ira_opcode_desc _ira_opcode_desc_CVTTPS2PI[] = {
	// 0F 2C /r CVTTPS2PI mm, xmm/m64 A Valid Valid Convert two singleprecision floating-point values from xmm/m64 to two signed doubleword signed integers in mm using truncation.
	{ NULL, 0x0001, 0x00D88000, { 0x0F, 0x2C, 0x00 }, _IRA_OPERAND_MODRM_R_MMX_W, _IRA_OPERAND_MODRM_RM_XMM_64, _IRA_NA, _IRA_NA }
};

// MMWORD
struct ira_opcode_desc _ira_opcode_desc_CVTTSD2SI[] = {
	// F2 0F 2C /r CVTTSD2SI r32, xmm/m64 A Valid Valid Convert one doubleprecision floating-point value from xmm/m64 to one signed doubleword integer in r32 using truncation.
	{ NULL, 0x2001, 0x03D88000, { 0x0F, 0x2C, 0x00 }, _IRA_OPERAND_MODRM_R_32_W, _IRA_OPERAND_MODRM_RM_XMM_64, _IRA_NA, _IRA_NA },
	// F2 REX.W 0F 2C /r CVTTSD2SI r64, xmm/m64 A Valid N.E. Convert one double precision floating-point value from xmm/m64 to one signedquad wordinteger in r64 using truncation.
	{ NULL, 0x2009, 0x04988000, { 0x0F, 0x2C, 0x00 }, _IRA_OPERAND_MODRM_R_64_W, _IRA_OPERAND_MODRM_RM_XMM_64, _IRA_NA, _IRA_NA },
};

// MMWORD
struct ira_opcode_desc _ira_opcode_desc_CVTTSS2SI[] = {
	// F3 0F 2C /r CVTTSS2SI r32, xmm/m32 A Valid Valid Convert one single-precision floating-point value from xmm/m32 to one signed doubleword integer in r32 using truncation.
	{ NULL, 0x4001, 0x03D88000, { 0x0F, 0x2C, 0x00 }, _IRA_OPERAND_MODRM_R_32_W, _IRA_OPERAND_MODRM_RM_XMM_32, _IRA_NA, _IRA_NA },
	// F3 REX.W 0F 2C /r CVTTSS2SI r64, xmm/m32 A Valid N.E. Convert one single-precision floating-point value from xmm/m32 to one signed quadword integer in
	{ NULL, 0x4009, 0x04988000, { 0x0F, 0x2C, 0x00 }, _IRA_OPERAND_MODRM_R_64_W, _IRA_OPERAND_MODRM_RM_XMM_32, _IRA_NA, _IRA_NA },
};

struct ira_opcode_desc _ira_opcode_desc_CWD_CDQ_CQO[] = {
	// 99 CWD A Valid Valid DX:AX <- sign-extend of AX.
	{ "cwd", 0x0001, 0x01C40000, { 0x99, 0x00, 0x00 }, _IRA_NA, _IRA_NA, _IRA_NA, _IRA_NA },
	// 99 CDQ A Valid Valid EDX:EAX <- sign-extend of EAX.
	{ "cdq", 0x0001, 0x02C40000, { 0x99, 0x00, 0x00 }, _IRA_NA, _IRA_NA, _IRA_NA, _IRA_NA },
	// REX.W + 99 CQO A Valid N.E. RDX:RAX <- sign-extend of RAX.
	{ "cqo", 0x0001, 0x04840000, { 0x99, 0x00, 0x00 }, _IRA_NA, _IRA_NA, _IRA_NA, _IRA_NA },
};

struct ira_opcode_desc _ira_opcode_desc_DAA[] = {
	// 27 DAA A Invalid Valid Decimal adjust AL after addition.
	{ NULL, 0x0001, 0x00440000, { 0x27, 0x00, 0x00 }, _IRA_NA, _IRA_NA, _IRA_NA, _IRA_NA },
};

struct ira_opcode_desc _ira_opcode_desc_DAS[] = {
	// 2F DAS A Invalid Valid Decimal adjust AL after subtraction.
	{ NULL, 0x0001, 0x00440000, { 0x2F, 0x00, 0x00 }, _IRA_NA, _IRA_NA, _IRA_NA, _IRA_NA },
};

struct ira_opcode_desc _ira_opcode_desc_DEC[] = {
	// FE /1 DEC r/m8 A Valid Valid Decrement r/m8 by 1.
	// REX + FE /1 DEC r/m8* A Valid N.E. Decrement r/m8 by 1.
	{ NULL, 0x0001, 0x00C58800, { 0xFE, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_8_W, _IRA_NA, _IRA_NA, _IRA_NA },
	// FF /1 DEC r/m16 A Valid Valid Decrement r/m16 by 1.
	// FF /1 DEC r/m32 A Valid Valid Decrement r/m32 by 1.
	// REX.W + FF /1 DEC r/m64 A Valid N.E. Decrement r/m64 by 1.
	{ NULL, 0x0001, 0x00C58800, { 0xFF, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_W, _IRA_NA, _IRA_NA, _IRA_NA },
	// 48+rw DEC r16 B N.E. Valid Decrement r16 by 1.
	// 48+rd DEC r32 B N.E. Valid Decrement r32 by 1.
	{ NULL, 0x0001, 0x00440001, { 0x48, 0x00, 0x00 }, _IRA_OPERAND_OPCODE_REG( IRA_REG_GPR, _IRA_GPRS_UNDEFINED ), _IRA_NA, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_DIV[] = {
	// F6 /6 DIV r/m8 A Valid Valid Unsigned divide AX by r/m8,with result stored in AL Quotient, AH Remainder.
	// REX + F6 /6 DIV r/m8* A Valid N.E. Unsigned divide AX by r/m8, with result stored in AL Quotient, AH Remainder.
	{ NULL, 0x0001, 0x00C5B000, { 0xF6, 0x00, 0x00 }, _IRA_EXPLICIT_REG( IRA_REG_GPR, _IRA_REG_AX, _IRA_OS_WORD ), _IRA_OPERAND_MODRM_RM_8_W, _IRA_NA, _IRA_NA },
	// F7 /6 DIV r/m16 A Valid Valid Unsigned divide DX:AX by r/m16, with result stored in AX Quotient, DX Remainder.
	// F7 /6 DIV r/m32 A Valid Valid Unsigned divide EDX:EAX by r/m32, with result stored in EAX Quotient, EDX Remainder.
	// REX.W + F7 /6 DIV r/m64 A Valid N.E. Unsigned divide RDX:RAX by r/m64, with result stored in RAX Quotient, RDX Remainder.
	{ NULL, 0x0001, 0x00C5B000, { 0xF7, 0x00, 0x00 }, _IRA_EXPLICIT_REG_OSA( IRA_REG_GPR, _IRA_REG_AL ), _IRA_OPERAND_MODRM_RM_W, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_DIVPD[] = {
	// 66 0F 5E /r DIVPD xmm1, xmm2/m128 A Valid Valid Divide packed doubleprecision floating-point values in xmm1 by packed double-precision floatingpoint values xmm2/m128.
	{ NULL, 0x1001, 0x00D88000, { 0x0F, 0x5E, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_128_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_DIVPS[] = {
	// 0F 5E /r DIVPS xmm1, xmm2/m128 A Valid Valid Divide packed singleprecision floating-point values in xmm1 by packed single-precision floatingpoint values xmm2/m128.
	{ NULL, 0x0001, 0x00D88000, { 0x0F, 0x5E, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_128_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_DIVSD[] = {
	// F2 0F 5E /r DIVSD xmm1, xmm2/m64 A Valid Valid Divide low double-precision floating-point value n xmm1 by low double-precision floating-point value in xmm2/mem64.
	{ NULL, 0x2001, 0x00D88000, { 0x0F, 0x5E, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_64_W, _IRA_OPERAND_MODRM_RM_XMM_64, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_DIVSS[] = {
	// F3 0F 5E /r DIVSS xmm1, xmm2/m32 A Valid Valid Divide low single-precision floating-point value in xmm1 by low singleprecision floating-point value in xmm2/m32.
	{ NULL, 0x4001, 0x00D88000, { 0x0F, 0x5E, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_32_W, _IRA_OPERAND_MODRM_RM_XMM_32, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_DPPD[] = {
	// 66 0F 3A 41 /r ib DPPD xmm1, xmm2/m128, imm8 A Valid Valid Selectively multiply packed DP floating-point values from xmm1 with packed DP floating-point values from xmm2, add and selectively store the packed DP floating-point values to xmm1.
	{ NULL, 0x1001, 0x00EC8000, { 0x0F, 0x3A, 0x41 }, _IRA_OPERAND_MODRM_R_XMM_128_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_OPERAND_IB, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_DPPS[] = {
	// 66 0F 3A 40 /r ib DPPS xmm1, xmm2/m128, imm8 A Valid Valid Selectively multiply packed SP floating-point values from xmm1 with packed SP floating-point values from xmm2, add and selectively store the packed SP floating-point values or zero values to xmm1.
	{ NULL, 0x1001, 0x00EC8000, { 0x0F, 0x3A, 0x40 }, _IRA_OPERAND_MODRM_R_XMM_128_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_OPERAND_IB, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_EMMS[] = {
	// 0F 77 EMMS A Valid Valid Set the x87 FPU tag word to empty.
	{ NULL, 0x0001, 0x00D80000, { 0x0F, 0x77, 0x00 }, _IRA_NA, _IRA_NA, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_ENTER[] = {
	// C8 iw 00 ENTER imm16, 0 A Valid Valid Create a stack frame for a procedure.
	// C8 iw 01 ENTER imm16, 1 A Valid Valid Create a nested stack frame for a procedure.
	// C8 iw ib ENTER imm16, imm8 A Valid Valid Create a nested stack frame for a procedure.
	{ NULL, 0x0001, 0x00C40000, { 0xC8, 0x00, 0x00 }, _IRA_OPERAND_IW | _IRA_WRITE, _IRA_OPERAND_IB, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_EXTRACTPS[] = {
	// 66 0F 3A 17 /r ib EXTRACTPS reg/m32, xmm2, imm8 A Valid Valid Extract a single-precision floating-point value from xmm2 at the source offset specified by imm8 and store the result to reg or m32. The upper 32 bits of r64 is zeroed if reg is r64.
	{ NULL, 0x1001, 0x00EC8000, { 0x0F, 0x3A, 0x17 }, _IRA_OPERAND_MODRM_RM_32_W, _IRA_OPERAND_MODRM_R_XMM_32, _IRA_OPERAND_IB, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_F2XM1[] = {
	// D9 F0 F2XM1 Valid Valid Replace ST(0) with (2ST(0) – 1).
	{ NULL, 0x0001, 0x00D80000, { 0xD9, 0xF0, 0x17 }, _IRA_NA, _IRA_NA, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_FABS[] = {
	// D9 E1 FABS Valid Valid Replace ST with its absolute value.
	{ NULL, 0x0001, 0x00D80000, { 0xD9, 0xE1, 0x17 }, _IRA_NA, _IRA_NA, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_FADD[] = {
	// D8 /0 FADD m32fp Valid Valid Add m32fp to ST(0) and store result in ST(0).
	{ NULL, 0x0001, 0x00C58000, { 0xD8, 0x00, 0x00 }, _IRA_OPERAND_MODRM_M_32, _IRA_NA, _IRA_NA, _IRA_NA },
	// DC /0 FADD m64fp Valid Valid Add m64fp to ST(0) and store result in ST(0).
	{ NULL, 0x0001, 0x00C58000, { 0xDC, 0x00, 0x00 }, _IRA_OPERAND_MODRM_M_64, _IRA_NA, _IRA_NA, _IRA_NA },
	// D8 C0+i FADD ST(0), ST(i) Valid Valid Add ST(0) to ST(i) and store result in ST(0).
	{ NULL, 0x0001, 0x00D80001, { 0xD8, 0xC0, 0x00 }, _IRA_EXPLICIT_REG( IRA_REG_FPU, _IRA_REG_ST0, _IRA_OS_UNDEFINED ), _IRA_OPERAND_OPCODE_REG( IRA_REG_FPU, 0 ), _IRA_NA, _IRA_NA },
	// DC C0+i FADD ST(i), ST(0) Valid Valid Add ST(i) to ST(0) and store result in ST(i).
	{ NULL, 0x0001, 0x00D80001, { 0xDC, 0xC0, 0x00 }, _IRA_OPERAND_OPCODE_REG( IRA_REG_FPU, 0 ), _IRA_EXPLICIT_REG( IRA_REG_FPU, _IRA_REG_ST0, _IRA_OS_UNDEFINED ), _IRA_NA, _IRA_NA },
	// DE C0+i FADDP ST(i), ST(0) Valid Valid Add ST(0) to ST(i), store result in ST(i), and pop the register stack.
	{ "faddp", 0x0001, 0x00D80001, { 0xDE, 0xC0, 0x00 }, _IRA_OPERAND_OPCODE_REG( IRA_REG_FPU, 0 ), _IRA_EXPLICIT_REG( IRA_REG_FPU, _IRA_REG_ST0, _IRA_OS_UNDEFINED ), _IRA_NA, _IRA_NA },
	// DA /0 FIADD m32int Valid Valid Add m32int to ST(0) and store result in ST(0).
	{ "fiadd", 0x0001, 0x00C58000, { 0xDA, 0x00, 0x00 }, _IRA_OPERAND_MODRM_M_32, _IRA_NA, _IRA_NA, _IRA_NA },
	// DE /0 FIADD m16int Valid Valid Add m16int to ST(0) and store result in ST(0).
	{ "fiadd", 0x0001, 0x00C58000, { 0xDE, 0x00, 0x00 }, _IRA_OPERAND_MODRM_M_16, _IRA_NA, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_FBLD[] = {
	// DF /4 FBLD m80 dec Valid Valid Convert BCD value to floating-point and push onto the FPU stack.
	{ NULL, 0x0001, 0x00C5A000, { 0xDF, 0x00, 0x00 }, _IRA_OPERAND_MODRM_M_80, _IRA_NA, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_FBSTP[] = {
	// DF /6 FBSTP m80bcd Valid Valid Store ST(0) in m80bcd and pop ST(0).
	{ NULL, 0x0001, 0x00C5B000, { 0xDF, 0x00, 0x00 }, _IRA_OPERAND_MODRM_M_80, _IRA_NA, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_FCHS[] = {
	// D9 E0 FCHS Valid Valid Complements sign of ST(0).
	{ NULL, 0x0001, 0x00D80000, { 0xD9, 0xE0, 0x00 }, _IRA_NA, _IRA_NA, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_FCLEX[] = {
	// 9B DB E2 FCLEX Valid Valid Clear floating-point exception flags after checking for pending unmasked floatingpoint exceptions.
	{ NULL, 0x0001, 0x00EC0000, { 0x9B, 0xDB, 0xE2 }, _IRA_NA, _IRA_NA, _IRA_NA, _IRA_NA },
	// DB E2 FNCLEX* Valid Valid Clear floating-point exception flags without checking for pending unmasked floating-point exceptions.
	{ "fnclex", 0x0001, 0x00D80000, { 0xDB, 0xE2, 0x00 }, _IRA_NA, _IRA_NA, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_FCMOV[] = {
	// DA C0+i FCMOVB ST(0), ST(i) Valid Valid Move if below (CF=1).
	{ "fcmovb", 0x0001, 0x00D80001, { 0xDA, 0xC0, 0x00 }, _IRA_EXPLICIT_REG( IRA_REG_FPU, _IRA_REG_ST0, _IRA_OS_UNDEFINED ), _IRA_OPERAND_OPCODE_REG( IRA_REG_FPU, 0 ), _IRA_NA, _IRA_NA },
	// DA C8+i FCMOVE ST(0), ST(i) Valid Valid Move if equal (ZF=1).
	{ "fcmove", 0x0001, 0x00D80001, { 0xDA, 0xC8, 0x00 }, _IRA_EXPLICIT_REG( IRA_REG_FPU, _IRA_REG_ST0, _IRA_OS_UNDEFINED ), _IRA_OPERAND_OPCODE_REG( IRA_REG_FPU, 0 ), _IRA_NA, _IRA_NA },
	// DA D0+i FCMOVBE ST(0), ST(i) Valid Valid Move if below or equal (CF=1 or ZF=1).
	{ "fcmovbe", 0x0001, 0x00D80001, { 0xDA, 0xD0, 0x00 }, _IRA_EXPLICIT_REG( IRA_REG_FPU, _IRA_REG_ST0, _IRA_OS_UNDEFINED ), _IRA_OPERAND_OPCODE_REG( IRA_REG_FPU, 0 ), _IRA_NA, _IRA_NA },
	// DA D8+i FCMOVU ST(0), ST(i) Valid Valid Move if unordered (PF=1).
	{ "fcmovu", 0x0001, 0x00D80001, { 0xDA, 0xD8, 0x00 }, _IRA_EXPLICIT_REG( IRA_REG_FPU, _IRA_REG_ST0, _IRA_OS_UNDEFINED ), _IRA_OPERAND_OPCODE_REG( IRA_REG_FPU, 0 ), _IRA_NA, _IRA_NA },
	// DB C0+i FCMOVNB ST(0), ST(i) Valid Valid Move if not below (CF=0).
	{ "fcmovnb", 0x0001, 0x00D80001, { 0xDB, 0xC0, 0x00 }, _IRA_EXPLICIT_REG( IRA_REG_FPU, _IRA_REG_ST0, _IRA_OS_UNDEFINED ), _IRA_OPERAND_OPCODE_REG( IRA_REG_FPU, 0 ), _IRA_NA, _IRA_NA },
	// DB C8+i FCMOVNE ST(0), ST(i) Valid Valid Move if not equal (ZF=0).
	{ "fcmovne", 0x0001, 0x00D80001, { 0xDB, 0xC8, 0x00 }, _IRA_EXPLICIT_REG( IRA_REG_FPU, _IRA_REG_ST0, _IRA_OS_UNDEFINED ), _IRA_OPERAND_OPCODE_REG( IRA_REG_FPU, 0 ), _IRA_NA, _IRA_NA },
	// DB D0+i FCMOVNBE ST(0), ST(i) Valid Valid Move if not below or equal (CF=0 and ZF=0).
	{ "fcmovnbe", 0x0001, 0x00D80001, { 0xDB, 0xD0, 0x00 }, _IRA_EXPLICIT_REG( IRA_REG_FPU, _IRA_REG_ST0, _IRA_OS_UNDEFINED ), _IRA_OPERAND_OPCODE_REG( IRA_REG_FPU, 0 ), _IRA_NA, _IRA_NA },
	// DB D8+i FCMOVNU ST(0), ST(i) Valid Valid Move if not unordered (PF=0).
	{ "fcmovnu", 0x0001, 0x00D80001, { 0xDB, 0xD8, 0x00 }, _IRA_EXPLICIT_REG( IRA_REG_FPU, _IRA_REG_ST0, _IRA_OS_UNDEFINED ), _IRA_OPERAND_OPCODE_REG( IRA_REG_FPU, 0 ), _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_FCOM[] = {
	// DB F0+i FCOMI ST, ST(i) Valid Valid Compare ST(0) with ST(i) and set status flags accordingly.
	{ "fcomi", 0x0001, 0x00D80001, { 0xDB, 0xF0, 0x00 }, _IRA_EXPLICIT_REG( IRA_REG_FPU, _IRA_REG_ST0, _IRA_OS_UNDEFINED ), _IRA_OPERAND_OPCODE_REG( IRA_REG_FPU, 0 ), _IRA_NA, _IRA_NA },
	// DF F0+i FCOMIP ST, ST(i) Valid Valid Compare ST(0) with ST(i), set status flags accordingly, and pop register stack.
	{ "fcomip", 0x0001, 0x00D80001, { 0xDF, 0xF0, 0x00 }, _IRA_EXPLICIT_REG( IRA_REG_FPU, _IRA_REG_ST0, _IRA_OS_UNDEFINED ), _IRA_OPERAND_OPCODE_REG( IRA_REG_FPU, 0 ), _IRA_NA, _IRA_NA },
	// DB E8+i FUCOMI ST, ST(i) Valid Valid Compare ST(0) with ST(i), check for ordered values, and set status flags accordingly.
	{ "fucomi", 0x0001, 0x00D80001, { 0xDB, 0xE8, 0x00 }, _IRA_EXPLICIT_REG( IRA_REG_FPU, _IRA_REG_ST0, _IRA_OS_UNDEFINED ), _IRA_OPERAND_OPCODE_REG( IRA_REG_FPU, 0 ), _IRA_NA, _IRA_NA },
	// DF E8+i FUCOMIP ST, ST(i) Valid Valid Compare ST(0) with ST(i), check for ordered values, set status flags accordingly, and pop register stack.
	{ "fucomip", 0x0001, 0x00D80001, { 0xDF, 0xE8, 0x00 }, _IRA_EXPLICIT_REG( IRA_REG_FPU, _IRA_REG_ST0, _IRA_OS_UNDEFINED ), _IRA_OPERAND_OPCODE_REG( IRA_REG_FPU, 0 ), _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_FCOS[] = {
	// D9 FF FCOS Valid Valid Replace ST(0) with its cosine.
	{ NULL, 0x0001, 0x00D80000, { 0xD9, 0xFF, 0x00 }, _IRA_NA, _IRA_NA, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_FDECSTP[] = {
	// D9 F6 FDECSTP Valid Valid Decrement
	{ NULL, 0x0001, 0x00D80000, { 0xD9, 0xF6, 0x00 }, _IRA_NA, _IRA_NA, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_FDIV[] = {
	// D8 /6 FDIV m32fp Valid Valid Divide ST(0) by m32fp and store result in ST(0).
	{ NULL, 0x0001, 0x00C5B000, { 0xD8, 0x00, 0x00 }, _IRA_OPERAND_MODRM_M_32, _IRA_NA, _IRA_NA, _IRA_NA },
	// DC /6 FDIV m64fp Valid Valid Divide ST(0) by m64fp and store result in ST(0).
	{ NULL, 0x0001, 0x00C5B000, { 0xDC, 0x00, 0x00 }, _IRA_OPERAND_MODRM_M_64, _IRA_NA, _IRA_NA, _IRA_NA },
	// D8 F0+i FDIV ST(0), ST(i) Valid Valid Divide ST(0) by ST(i) and store result in ST(0).
	{ NULL, 0x0001, 0x00D80001, { 0xD8, 0xF0, 0x00 }, _IRA_EXPLICIT_REG( IRA_REG_FPU, _IRA_REG_ST0, _IRA_OS_UNDEFINED ), _IRA_OPERAND_OPCODE_REG( IRA_REG_FPU, 0 ), _IRA_NA, _IRA_NA },
	// DC F8+i FDIV ST(i), ST(0) Valid Valid Divide ST(i) by ST(0) and store result in ST(i).
	{ NULL, 0x0001, 0x00D80001, { 0xDC, 0xF8, 0x00 }, _IRA_OPERAND_OPCODE_REG( IRA_REG_FPU, 0 ), _IRA_EXPLICIT_REG( IRA_REG_FPU, _IRA_REG_ST0, _IRA_OS_UNDEFINED ), _IRA_NA, _IRA_NA },
	// DE F8+i FDIVP ST(i), ST(0) Valid Valid Divide ST(i) by ST(0), store result in ST(i), and pop the register stack.
	{ "fdivp", 0x0001, 0x00D80001, { 0xDE, 0xF8, 0x00 }, _IRA_OPERAND_OPCODE_REG( IRA_REG_FPU, 0 ), _IRA_EXPLICIT_REG( IRA_REG_FPU, _IRA_REG_ST0, _IRA_OS_UNDEFINED ), _IRA_NA, _IRA_NA },
	// DA /6 FIDIV m32int Valid Valid Divide ST(0) by m32int and store result in ST(0).
	{ "fidiv", 0x0001, 0x00C5B000, { 0xDA, 0x00, 0x00 }, _IRA_OPERAND_MODRM_M_32, _IRA_NA, _IRA_NA, _IRA_NA },
	// DE /6 FIDIV m16int Valid Valid Divide ST(0) by m64int and store result in ST(0).
	{ "fidiv", 0x0001, 0x00C5B000, { 0xDE, 0x00, 0x00 }, _IRA_OPERAND_MODRM_M_16, _IRA_NA, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_FDIVR[] = {
	// D8 /7 FDIVR m32fp Valid Valid Divide m32fp by ST(0) and store result in ST(0).
	{ NULL, 0x0001, 0x00C5B800, { 0xD8, 0x00, 0x00 }, _IRA_OPERAND_MODRM_M_32, _IRA_NA, _IRA_NA, _IRA_NA },
	// DC /7 FDIVR m64fp Valid Valid Divide m64fp by ST(0) and store result in ST(0).
	{ NULL, 0x0001, 0x00C5B800, { 0xDC, 0x00, 0x00 }, _IRA_OPERAND_MODRM_M_64, _IRA_NA, _IRA_NA, _IRA_NA },
	// D8 F8+i FDIVR ST(0), ST(i) Valid Valid Divide ST(i) by ST(0) and store result in ST(0).
	{ NULL, 0x0001, 0x00D80001, { 0xD8, 0xF8, 0x00 }, _IRA_EXPLICIT_REG( IRA_REG_FPU, _IRA_REG_ST0, _IRA_OS_UNDEFINED ), _IRA_OPERAND_OPCODE_REG( IRA_REG_FPU, 0 ), _IRA_NA, _IRA_NA },
	// DC F0+i FDIVR ST(i), ST(0) Valid Valid Divide ST(0) by ST(i) and store result in ST(i).
	{ NULL, 0x0001, 0x00D80001, { 0xDC, 0xF0, 0x00 }, _IRA_OPERAND_OPCODE_REG( IRA_REG_FPU, 0 ), _IRA_EXPLICIT_REG( IRA_REG_FPU, _IRA_REG_ST0, _IRA_OS_UNDEFINED ), _IRA_NA, _IRA_NA },
	// DE F0+i FDIVRP ST(i), ST(0) Valid Valid Divide ST(0) by ST(i), store result in ST(i), and pop the register stack.
	{ "fdivrp", 0x0001, 0x00D80001, { 0xDE, 0xF0, 0x00 }, _IRA_OPERAND_OPCODE_REG( IRA_REG_FPU, 0 ), _IRA_EXPLICIT_REG( IRA_REG_FPU, _IRA_REG_ST0, _IRA_OS_UNDEFINED ), _IRA_NA, _IRA_NA },
	// DA /7 FIDIVR m32int Valid Valid Divide m32int by ST(0) and store result in ST(0).
	{ "fidivr", 0x0001, 0x00C5B800, { 0xDA, 0x00, 0x00 }, _IRA_OPERAND_MODRM_M_32, _IRA_NA, _IRA_NA, _IRA_NA },
	// DE /7 FIDIVR m16int Valid Valid Divide m16int by ST(0) and store result in ST(0).
	{ "fidivr", 0x0001, 0x00C5B800, { 0xDE, 0x00, 0x00 }, _IRA_OPERAND_MODRM_M_16, _IRA_NA, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_FFREE[] = {
	// DD C0+i FFREE ST(i) Valid Valid Sets tag for ST(i) to empty.
	{ NULL, 0x0001, 0x00D80001, { 0xDD, 0xC0, 0x00 }, _IRA_OPERAND_OPCODE_REG( IRA_REG_FPU, 0 ), _IRA_NA, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_FICOM[] = {
	// DE /2 FICOM m16int Valid Valid Compare ST(0) with m16int.
	{ NULL, 0x0001, 0x00C59000, { 0xDE, 0x00, 0x00 }, _IRA_OPERAND_MODRM_M_16, _IRA_NA, _IRA_NA, _IRA_NA },
	// DA /2 FICOM m32int Valid Valid Compare ST(0) with m32int.
	{ NULL, 0x0001, 0x00C59000, { 0xDA, 0x00, 0x00 }, _IRA_OPERAND_MODRM_M_32, _IRA_NA, _IRA_NA, _IRA_NA },
	// DE /3 FICOMP m16int Valid Valid Compare ST(0) with m16int and pop stack register.
	{ "ficomp", 0x0001, 0x00C59800, { 0xDE, 0x00, 0x00 }, _IRA_OPERAND_MODRM_M_16, _IRA_NA, _IRA_NA, _IRA_NA },
	// DA /3 FICOMP m32int Valid Valid Compare ST(0) with m32int and pop stack register.
	{ "ficomp", 0x0001, 0x00C59800, { 0xDA, 0x00, 0x00 }, _IRA_OPERAND_MODRM_M_32, _IRA_NA, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_FILD[] = {
	// DF /0 FILD m16int Valid Valid Push m16int onto the FPU register stack.
	{ NULL, 0x0001, 0x00C58000, { 0xDF, 0x00, 0x00 }, _IRA_OPERAND_MODRM_M_16, _IRA_NA, _IRA_NA, _IRA_NA },
	// DB /0 FILD m32int Valid Valid Push m32int onto the FPU register stack.
	{ NULL, 0x0001, 0x00C58000, { 0xDB, 0x00, 0x00 }, _IRA_OPERAND_MODRM_M_32, _IRA_NA, _IRA_NA, _IRA_NA },
	// DF /5 FILD m64int Valid Valid Push m64int onto the FPU register stack.
	{ NULL, 0x0001, 0x00C5A800, { 0xDF, 0x00, 0x00 }, _IRA_OPERAND_MODRM_M_64, _IRA_NA, _IRA_NA, _IRA_NA },
};

struct ira_opcode_desc _ira_opcode_desc_FINCSTP[] = {
	// D9 F7 FINCSTP Valid Valid Increment the TOP field in the FPU status register.
	{ NULL, 0x0001, 0x00D80000, { 0xD9, 0xF7, 0x00 }, _IRA_NA, _IRA_NA, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_FINIT[] = {
	// 9B DB E3 FINIT Valid Valid Initialize FPU after checking for pending unmasked floating-point exceptions.
	{ NULL, 0x0001, 0x00EC0000, { 0x9B, 0xDB, 0xE3 }, _IRA_NA, _IRA_NA, _IRA_NA, _IRA_NA },
	// DB E3 FNINIT* Valid Valid Initialize FPU without checking for pending unmasked floating-point exceptions.
	{ "fninit", 0x0001, 0x00D80000, { 0xDB, 0xE3, 0x00 }, _IRA_NA, _IRA_NA, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_FIST[] = {
	// DF /2 FIST m16int Valid Valid Store ST(0) in m16int.
	{ NULL, 0x0001, 0x00C59000, { 0xDF, 0x00, 0x00 }, _IRA_OPERAND_MODRM_M_16, _IRA_NA, _IRA_NA, _IRA_NA },
	// DB /2 FIST m32int Valid Valid Store ST(0) in m32int.
	{ NULL, 0x0001, 0x00C59000, { 0xDB, 0x00, 0x00 }, _IRA_OPERAND_MODRM_M_32, _IRA_NA, _IRA_NA, _IRA_NA },
	// DF /3 FISTP m16int Valid Valid Store ST(0) in m16int and pop register stack.
	{ "fistp", 0x0001, 0x00C59800, { 0xDF, 0x00, 0x00 }, _IRA_OPERAND_MODRM_M_16, _IRA_NA, _IRA_NA, _IRA_NA },
	// DB /3 FISTP m32int Valid Valid Store ST(0) in m32int and pop register stack.
	{ "fistp", 0x0001, 0x00C59800, { 0xDB, 0x00, 0x00 }, _IRA_OPERAND_MODRM_M_32, _IRA_NA, _IRA_NA, _IRA_NA },
	// DF /7 FISTP m64int Valid Valid Store ST(0) in m64int and pop register stack.
	{ "fistp", 0x0001, 0x00C5B800, { 0xDF, 0x00, 0x00 }, _IRA_OPERAND_MODRM_M_64, _IRA_NA, _IRA_NA, _IRA_NA },
};

struct ira_opcode_desc _ira_opcode_desc_FISTTP[] = {
	// DF /1 FISTTP m16int Valid Valid Store ST(0) in m16int with truncation.
	{ NULL, 0x0001, 0x00C58800, { 0xDF, 0x00, 0x00 }, _IRA_OPERAND_MODRM_M_16, _IRA_NA, _IRA_NA, _IRA_NA },
	// DB /1 FISTTP m32int Valid Valid Store ST(0) in m32int with truncation.
	{ NULL, 0x0001, 0x00C58800, { 0xDB, 0x00, 0x00 }, _IRA_OPERAND_MODRM_M_32, _IRA_NA, _IRA_NA, _IRA_NA },
	// DD /1 FISTTP m64int Valid Valid Store ST(0) in m64int with truncation.
	{ NULL, 0x0001, 0x00C58800, { 0xDD, 0x00, 0x00 }, _IRA_OPERAND_MODRM_M_64, _IRA_NA, _IRA_NA, _IRA_NA },
};

struct ira_opcode_desc _ira_opcode_desc_FLD[] = {
	// D9 /0 FLD m32fp Valid Valid Push m32fp onto the FPU register stack.
	{ NULL, 0x0001, 0x00C58000, { 0xD9, 0x00, 0x00 }, _IRA_OPERAND_MODRM_M_32, _IRA_NA, _IRA_NA, _IRA_NA },
	// DD /0 FLD m64fp Valid Valid Push m64fp onto the FPU register stack.
	{ NULL, 0x0001, 0x00C58000, { 0xDD, 0x00, 0x00 }, _IRA_OPERAND_MODRM_M_64, _IRA_NA, _IRA_NA, _IRA_NA },
	// DB /5 FLD m80fp Valid Valid Push m80fp onto the FPU register stack.
	{ NULL, 0x0001, 0x00C5A800, { 0xDB, 0x00, 0x00 }, _IRA_OPERAND_MODRM_M_80, _IRA_NA, _IRA_NA, _IRA_NA },
	// D9 C0+i FLD ST(i) Valid Valid Push ST(i) onto the FPU register stack.
	{ NULL, 0x0001, 0x00D80001, { 0xD9, 0xC0, 0x00 }, _IRA_OPERAND_OPCODE_REG( IRA_REG_FPU, 0 ), _IRA_NA, _IRA_NA, _IRA_NA },
};

struct ira_opcode_desc _ira_opcode_desc_FLDx[] = {
	// D9 E8 FLD1 Valid Valid Push +1.0 onto the FPU register stack.
	{ "fld1", 0x0001, 0x00D80000, { 0xD9, 0xE8, 0x00 }, _IRA_NA, _IRA_NA, _IRA_NA, _IRA_NA },
	// D9 E9 FLDL2T Valid Valid Push log210 onto the FPU register stack.
	{ "fldl2t", 0x0001, 0x00D80000, { 0xD9, 0xE9, 0x00 }, _IRA_NA, _IRA_NA, _IRA_NA, _IRA_NA },
	// D9 EA FLDL2E Valid Valid Push log2e onto the FPU register stack.
	{ "fldl2e", 0x0001, 0x00D80000, { 0xD9, 0xEA, 0x00 }, _IRA_NA, _IRA_NA, _IRA_NA, _IRA_NA },
	// D9 EB FLDPI Valid Valid Push onto the FPU register stack.
	{ "fldpi", 0x0001, 0x00D80000, { 0xD9, 0xEB, 0x00 }, _IRA_NA, _IRA_NA, _IRA_NA, _IRA_NA },
	// D9 EC FLDLG2 Valid Valid Push log102 onto the FPU register stack.
	{ "fldlg2", 0x0001, 0x00D80000, { 0xD9, 0xEC, 0x00 }, _IRA_NA, _IRA_NA, _IRA_NA, _IRA_NA },
	// D9 ED FLDLN2 Valid Valid Push loge2 onto the FPU register stack.
	{ "fldln2", 0x0001, 0x00D80000, { 0xD9, 0xED, 0x00 }, _IRA_NA, _IRA_NA, _IRA_NA, _IRA_NA },
	// D9 EE FLDZ Valid Valid Push +0.0 onto the FPU register stack.
	{ "fldz", 0x0001, 0x00D80000, { 0xD9, 0xEE, 0x00 }, _IRA_NA, _IRA_NA, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_FLDCW[] = {
	// D9 /5 FLDCW m2byte Valid Valid Load FPU control word from m2byte.
	{ NULL, 0x0001, 0x00C5A800, { 0xD9, 0x00, 0x00 }, _IRA_OPERAND_MODRM_M_16, _IRA_NA, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_FLDENV[] = {
	// D9 /4 FLDENV m14/28byte Valid Valid Load FPU environment from m14byte or m28byte.
	{ NULL, 0x0001, 0x00C5A000, { 0xD9, 0x00, 0x00 }, _IRA_OPERAND_MODRM_M_14_28, _IRA_NA, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_FMUL[] = {
	// D8 /1 FMUL m32fp Valid Valid Multiply ST(0) by m32fp and store result in ST(0).
	{ NULL, 0x0001, 0x00C58800, { 0xD8, 0x00, 0x00 }, _IRA_OPERAND_MODRM_M_32, _IRA_NA, _IRA_NA, _IRA_NA },
	// DC /1 FMUL m64fp Valid Valid Multiply ST(0) by m64fp and store result in ST(0).
	{ NULL, 0x0001, 0x00C58800, { 0xDC, 0x00, 0x00 }, _IRA_OPERAND_MODRM_M_64, _IRA_NA, _IRA_NA, _IRA_NA },
	// D8 C8+i FMUL ST(0), ST(i) Valid Valid Multiply ST(0) by ST(i) and store result in ST(0).
	{ NULL, 0x0001, 0x00D80001, { 0xD8, 0xC8, 0x00 }, _IRA_EXPLICIT_REG( IRA_REG_FPU, _IRA_REG_ST0, _IRA_OS_UNDEFINED ), _IRA_OPERAND_OPCODE_REG( IRA_REG_FPU, 0 ), _IRA_NA, _IRA_NA },
	// DC C8+i FMUL ST(i), ST(0) Valid Valid Multiply ST(i) by ST(0) and store result in ST(i).
	{ NULL, 0x0001, 0x00D80001, { 0xDC, 0xC8, 0x00 }, _IRA_OPERAND_OPCODE_REG( IRA_REG_FPU, 0 ), _IRA_EXPLICIT_REG( IRA_REG_FPU, _IRA_REG_ST0, _IRA_OS_UNDEFINED ), _IRA_NA, _IRA_NA },
	// DE C8+i FMULP ST(i), ST(0) Valid Valid Multiply ST(i) by ST(0), store result in ST(i), and pop the register stack.
	{ "fmulp", 0x0001, 0x00D80001, { 0xDE, 0xC8, 0x00 }, _IRA_OPERAND_OPCODE_REG( IRA_REG_FPU, 0 ), _IRA_EXPLICIT_REG( IRA_REG_FPU, _IRA_REG_ST0, _IRA_OS_UNDEFINED ), _IRA_NA, _IRA_NA },
	// DA /1 FIMUL m32int Valid Valid Multiply ST(0) by m32int and store result in ST(0).
	{ "fimul", 0x0001, 0x00C58800, { 0xDA, 0x00, 0x00 }, _IRA_OPERAND_MODRM_M_32, _IRA_NA, _IRA_NA, _IRA_NA },
	// DE /1 FIMUL m16int Valid Valid Multiply ST(0) by m16int and store result in ST(0).
	{ "fimul", 0x0001, 0x00C58800, { 0xDE, 0x00, 0x00 }, _IRA_OPERAND_MODRM_M_16, _IRA_NA, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_FNOP[] = {
	// D9 D0 FNOP Valid Valid No operation is performed.
	{ NULL, 0x0001, 0x00D80000, { 0xD9, 0xD0, 0x00 }, _IRA_NA, _IRA_NA, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_FPATAN[] = {
	// D9 F3 FPATAN Valid Valid Replace ST(1) with arctan(ST(1) ST(0)) and pop the register stack.
	{ NULL, 0x0001, 0x00D80000, { 0xD9, 0xF3, 0x00 }, _IRA_NA, _IRA_NA, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_FPREM[] = {
	// D9 F8 FPREM Valid Valid Replace ST(0) with the remainder obtained from dividing ST(0) by ST(1).
	{ NULL, 0x0001, 0x00D80000, { 0xD9, 0xF8, 0x00 }, _IRA_NA, _IRA_NA, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_FPREM1[] = {
	// D9 F5 FPREM1 Valid Valid Replace ST(0) with the IEEE remainder obtained from dividing ST(0) by ST(1).
	{ NULL, 0x0001, 0x00D80000, { 0xD9, 0xF5, 0x00 }, _IRA_NA, _IRA_NA, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_FPTAN[] = {
	// D9 F2 FPTAN Valid Valid Replace ST(0) with its tangent and push 1 onto the FPU stack.
	{ NULL, 0x0001, 0x00D80000, { 0xD9, 0xF2, 0x00 }, _IRA_NA, _IRA_NA, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_FRNDINT[] = {
	// D9 FC FRNDINT Valid Valid Round ST(0) to an integer.
	{ NULL, 0x0001, 0x00D80000, { 0xD9, 0xFC, 0x00 }, _IRA_NA, _IRA_NA, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_FRSTOR[] = {
	// DD /4 FRSTOR m94/108byte Valid Valid Load FPU state from m94byte or m108byte.
	{ NULL, 0x0001, 0x00C5A000, { 0xDD, 0x00, 0x00 }, _IRA_OPERAND_MODRM_M_94_108, _IRA_NA, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_FSAVE[] = {
	// 9B DD /6 FSAVE m94/108byte Valid Valid Store FPU state to m94byte or m108byte after checking for pending unmasked floatingpoint exceptions. Then reinitialize the FPU.
	{ NULL, 0x0001, 0x00D9B000, { 0x9B, 0xDD, 0x00 }, _IRA_OPERAND_MODRM_M_94_108, _IRA_NA, _IRA_NA, _IRA_NA },
	// DD /6 FNSAVE* m94/108byte Valid Valid Store FPU environment to m94byte or m108byte without checking for pending unmasked floating-point exceptions.
	{ "fnsave", 0x0001, 0x00C5B000, { 0xDD, 0x00, 0x00 }, _IRA_OPERAND_MODRM_M_94_108, _IRA_NA, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_FSCALE[] = {
	// D9 FD FSCALE Valid Valid Scale ST(0) by ST(1).
	{ NULL, 0x0001, 0x00D80000, { 0xD9, 0xFD, 0x00 }, _IRA_NA, _IRA_NA, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_FSIN[] = {
	// D9 FE FSIN Valid Valid Replace ST(0) with its sine.
	{ NULL, 0x0001, 0x00D80000, { 0xD9, 0xFE, 0x00 }, _IRA_NA, _IRA_NA, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_FSINCOS[] = {
	// D9 FB FSINCOS Valid Valid Compute the sine and cosine of ST(0); replace ST(0) with the sine, and push the cosine onto the register stack.
	{ NULL, 0x0001, 0x00D80000, { 0xD9, 0xFB, 0x00 }, _IRA_NA, _IRA_NA, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_FSQRT[] = {
	// D9 FA FSQRT Valid Valid Computes square root of ST(0) and stores the result in ST(0).
	{ NULL, 0x0001, 0x00D80000, { 0xD9, 0xFA, 0x00 }, _IRA_NA, _IRA_NA, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_FST[] = {
	// D9 /2 FST m32fp Valid Valid Copy ST(0) to m32fp.
	{ NULL, 0x0001, 0x00C59000, { 0xD9, 0x00, 0x00 }, _IRA_OPERAND_MODRM_M_32, _IRA_NA, _IRA_NA, _IRA_NA },
	// DD /2 FST m64fp Valid Valid Copy ST(0) to m64fp.
	{ NULL, 0x0001, 0x00C59000, { 0xDD, 0x00, 0x00 }, _IRA_OPERAND_MODRM_M_64, _IRA_NA, _IRA_NA, _IRA_NA },
	// DD D0+i FST ST(i) Valid Valid Copy ST(0) to ST(i).
	{ NULL, 0x0001, 0x00D80001, { 0xDD, 0xD0, 0x00 }, _IRA_OPERAND_OPCODE_REG( IRA_REG_FPU, 0 ), _IRA_NA, _IRA_NA, _IRA_NA },
	// D9 /3 FSTP m32fp Valid Valid Copy ST(0) to m32fp and pop register stack.
	{ "fstp", 0x0001, 0x00C59800, { 0xD9, 0x00, 0x00 }, _IRA_OPERAND_MODRM_M_32, _IRA_NA, _IRA_NA, _IRA_NA },
	// DD /3 FSTP m64fp Valid Valid Copy ST(0) to m64fp and pop register stack.
	{ "fstp", 0x0001, 0x00C59800, { 0xDD, 0x00, 0x00 }, _IRA_OPERAND_MODRM_M_64, _IRA_NA, _IRA_NA, _IRA_NA },
	// DB /7 FSTP m80fp Valid Valid Copy ST(0) to m80fp and pop register stack.
	{ "fstp", 0x0001, 0x00C5B800, { 0xDB, 0x00, 0x00 }, _IRA_OPERAND_MODRM_M_80, _IRA_NA, _IRA_NA, _IRA_NA },
	// DD D8+i FSTP ST(i) Valid Valid Copy ST(0) to ST(i) and pop register stack.
	{ "fstp", 0x0001, 0x00D80001, { 0xDD, 0xD8, 0x00 }, _IRA_OPERAND_OPCODE_REG( IRA_REG_FPU, 0 ), _IRA_NA, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_FSTCW[] = {
	// 9B D9 /7 FSTCW m2byte Valid Valid Store FPU control word to m2byte after checking for pending unmasked floating-point exceptions.
	{ NULL, 0x0001, 0x00D9B800, { 0x9B, 0xD9, 0x00 }, _IRA_OPERAND_MODRM_M_16_W, _IRA_NA, _IRA_NA, _IRA_NA },
	// D9 /7 FNSTCW* m2byte Valid Valid Store FPU control word to m2byte without checking for pending unmasked floating-point exceptions.
	{ "fnstcw", 0x0001, 0x00C5B800, { 0xD9, 0x00, 0x00 }, _IRA_OPERAND_MODRM_M_16_W, _IRA_NA, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_FSTENV[] = {
	// 9B D9 /6 FSTENV m14/28byte Valid Valid Store FPU environment to m14byte or m28byte after checking for pending unmasked floating-point exceptions. Then mask all floatingpoint exceptions.
	{ NULL, 0x0001, 0x00D9B000, { 0x9B, 0xD9, 0x00 }, _IRA_OPERAND_MODRM_M_14_28_W, _IRA_NA, _IRA_NA, _IRA_NA },
	// D9 /6 FNSTENV* m14/28byte Valid Valid Store FPU environment to m14byte or m28byte without checking for pending unmasked floating-point exceptions. Then mask all floatingpoint exceptions.
	{ "fnstenv", 0x0001, 0x00C5B000, { 0xD9, 0x00, 0x00 }, _IRA_OPERAND_MODRM_M_14_28_W, _IRA_NA, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_FSTSW[] = {
	// 9B DD /7 FSTSW m2byte Valid Valid Store FPU status word at m2byte after checking for pending unmasked floatingpoint exceptions.
	{ NULL, 0x0001, 0x00D9B800, { 0x9B, 0xDD, 0x00 }, _IRA_OPERAND_MODRM_M_16_W, _IRA_NA, _IRA_NA, _IRA_NA },
	// 9B DF E0 FSTSW AX Valid Valid Store FPU status word in AX register after checking for pending unmasked floatingpoint exceptions.
	{ NULL, 0x0001, 0x00EC0000, { 0x9B, 0xDF, 0xE0 }, _IRA_EXPLICIT_REG( IRA_REG_GPR, _IRA_REG_AX, _IRA_OS_WORD ), _IRA_NA, _IRA_NA, _IRA_NA },
	// DD /7 FNSTSW* m2byte Valid Valid Store FPU status word at m2byte without checking for pending unmasked floatingpoint exceptions.
	{ "fnstsw", 0x0001, 0x00C5B800, { 0xDD, 0x00, 0x00 }, _IRA_OPERAND_MODRM_M_16_W, _IRA_NA, _IRA_NA, _IRA_NA },
	// DF E0 FNSTSW* AX Valid Valid Store FPU status word in AX register without checking for pending unmasked floatingpoint exceptions.
	{ "fnstsw", 0x0001, 0x00D80000, { 0xDF, 0xE0, 0x00 }, _IRA_EXPLICIT_REG( IRA_REG_GPR, _IRA_REG_AX, _IRA_OS_WORD ), _IRA_NA, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_FSUB[] = {
	// D8 /4 FSUB m32fp Valid Valid Subtract m32fp from ST(0) and store result in ST(0).
	{ NULL, 0x0001, 0x00C5A000, { 0xD8, 0x00, 0x00 }, _IRA_OPERAND_MODRM_M_32, _IRA_NA, _IRA_NA, _IRA_NA },
	// DC /4 FSUB m64fp Valid Valid Subtract m64fp from ST(0) and store result in ST(0).
	{ NULL, 0x0001, 0x00C5A000, { 0xDC, 0x00, 0x00 }, _IRA_OPERAND_MODRM_M_64, _IRA_NA, _IRA_NA, _IRA_NA },
	// D8 E0+i FSUB ST(0), ST(i) Valid Valid Subtract ST(i) from ST(0) and store result in ST(0).
	{ NULL, 0x0001, 0x00D80001, { 0xD8, 0xE0, 0x00 }, _IRA_EXPLICIT_REG( IRA_REG_FPU, _IRA_REG_ST0, _IRA_OS_UNDEFINED ), _IRA_OPERAND_OPCODE_REG( IRA_REG_FPU, 0 ), _IRA_NA, _IRA_NA },
	// DC E8+i FSUB ST(i), ST(0) Valid Valid Subtract ST(0) from ST(i) and store result in ST(i).
	{ NULL, 0x0001, 0x00D80001, { 0xDC, 0xE8, 0x00 }, _IRA_OPERAND_OPCODE_REG( IRA_REG_FPU, 0 ), _IRA_EXPLICIT_REG( IRA_REG_FPU, _IRA_REG_ST0, _IRA_OS_UNDEFINED ), _IRA_NA, _IRA_NA },
	// DE E8+i FSUBP ST(i), ST(0) Valid Valid Subtract ST(0) from ST(i), store result in ST(i), and pop register stack.
	{ "fsubp", 0x0001, 0x00D80001, { 0xDE, 0xE8, 0x00 }, _IRA_OPERAND_OPCODE_REG( IRA_REG_FPU, 0 ), _IRA_EXPLICIT_REG( IRA_REG_FPU, _IRA_REG_ST0, _IRA_OS_UNDEFINED ), _IRA_NA, _IRA_NA },
	// DA /4 FISUB m32int Valid Valid Subtract m32int from ST(0) and store result in ST(0).
	{ "fisub", 0x0001, 0x00C5A000, { 0xDA, 0x00, 0x00 }, _IRA_OPERAND_MODRM_M_32, _IRA_NA, _IRA_NA, _IRA_NA },
	// DE /4 FISUB m16int Valid Valid Subtract m16int from ST(0) and store result in ST(0).
	{ "fisub", 0x0001, 0x00C5A000, { 0xDE, 0x00, 0x00 }, _IRA_OPERAND_MODRM_M_16, _IRA_NA, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_FSUBR[] = {
	// D8 /5 FSUBR m32fp Valid Valid Subtract ST(0) from m32fp and store result in ST(0).
	{ NULL, 0x0001, 0x00C5A800, { 0xD8, 0x00, 0x00 }, _IRA_OPERAND_MODRM_M_32, _IRA_NA, _IRA_NA, _IRA_NA },
	// DC /5 FSUBR m64fp Valid Valid Subtract ST(0) from m64fp and store result in ST(0).
	{ NULL, 0x0001, 0x00C5A800, { 0xDC, 0x00, 0x00 }, _IRA_OPERAND_MODRM_M_64, _IRA_NA, _IRA_NA, _IRA_NA },
	// D8 E8+i FSUBR ST(0), ST(i) Valid Valid Subtract ST(0) from ST(i) and store result in ST(0).
	{ NULL, 0x0001, 0x00D80001, { 0xD8, 0xE8, 0x00 }, _IRA_EXPLICIT_REG( IRA_REG_FPU, _IRA_REG_ST0, _IRA_OS_UNDEFINED ), _IRA_OPERAND_OPCODE_REG( IRA_REG_FPU, 0 ), _IRA_NA, _IRA_NA },
	// DC E0+i FSUBR ST(i), ST(0) Valid Valid Subtract ST(i) from ST(0) and store result in ST(i).
	{ NULL, 0x0001, 0x00D80001, { 0xDC, 0xE0, 0x00 }, _IRA_OPERAND_OPCODE_REG( IRA_REG_FPU, 0 ), _IRA_EXPLICIT_REG( IRA_REG_FPU, _IRA_REG_ST0, _IRA_OS_UNDEFINED ), _IRA_NA, _IRA_NA },
	// DE E0+i FSUBRP ST(i), ST(0) Valid Valid Subtract ST(i) from ST(0), store result in ST(i), and pop register stack.
	{ "fsubrp", 0x0001, 0x00D80001, { 0xDE, 0xE0, 0x00 }, _IRA_OPERAND_OPCODE_REG( IRA_REG_FPU, 0 ), _IRA_EXPLICIT_REG( IRA_REG_FPU, _IRA_REG_ST0, _IRA_OS_UNDEFINED ), _IRA_NA, _IRA_NA },
	// DA /5 FISUBR m32int Valid Valid Subtract ST(0) from m32int and store result in ST(0).
	{ "fisubr", 0x0001, 0x00C5A800, { 0xDA, 0x00, 0x00 }, _IRA_OPERAND_MODRM_M_32, _IRA_NA, _IRA_NA, _IRA_NA },
	// DE /5 FISUBR m16int Valid Valid Subtract ST(0) from m16int and store result in ST(0).
	{ "fisubr", 0x0001, 0x00C5A800, { 0xDE, 0x00, 0x00 }, _IRA_OPERAND_MODRM_M_16, _IRA_NA, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_FTST[] = {
	// D9 E4 FTST Valid Valid Compare ST(0) with 0.0.
	{ NULL, 0x0001, 0x00D80000, { 0xD9, 0xE4, 0x00 }, _IRA_NA, _IRA_NA, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_FUCOM[] = {
	// DD E0+i FUCOM ST(i) Valid Valid Compare ST(0) with ST(i).
	{ NULL, 0x0001, 0x00D80001, { 0xDD, 0xE0, 0x00 }, _IRA_OPERAND_OPCODE_REG( IRA_REG_FPU, 0 ), _IRA_NA, _IRA_NA, _IRA_NA },
	// DD E8+i FUCOMP ST(i) Valid Valid Compare ST(0) with ST(i) and pop register stack.
	{ "fucomp", 0x0001, 0x00D80001, { 0xDD, 0xE8, 0x00 }, _IRA_OPERAND_OPCODE_REG( IRA_REG_FPU, 0 ), _IRA_NA, _IRA_NA, _IRA_NA },
	// DA E9 FUCOMPP Valid Valid Compare ST(0) with ST(1) and pop register stack twice.
	{ "fucompp", 0x0001, 0x00D80000, { 0xDA, 0xE9, 0x00 }, _IRA_NA, _IRA_NA, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_FXAM[] = {
	// D9 E5 FXAM Valid Valid Classify value or number in ST(0).
	{ NULL, 0x0001, 0x00D80000, { 0xD9, 0xE5, 0x00 }, _IRA_NA, _IRA_NA, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_FXCH[] = {
	// D9 C8+i FXCH ST(i) Valid Valid Exchange the contents of ST(0) and ST(i).
	{ NULL, 0x0001, 0x00D80001, { 0xD9, 0xC8, 0x00 }, _IRA_OPERAND_OPCODE_REG( IRA_REG_FPU, 0 ), _IRA_NA, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_FXRSTOR[] = {
	// 0F AE /1 FXRSTOR m512byte A Valid Valid Restore the x87 FPU, MMX, XMM, and MXCSR register state from m512byte.
	{ NULL, 0x0001, 0x03D98800, { 0x0F, 0xAE, 0x00 }, _IRA_OPERAND_MODRM_M_512B, _IRA_NA, _IRA_NA, _IRA_NA },
	// REX.W+ 0F AE /1 FXRSTOR64 m512byte A Valid N.E. Restore the x87 FPU, MMX, XMM, and MXCSR register state from m512byte.
	{ "fxrstor64", 0x0008, 0x04998800, { 0x0F, 0xAE, 0x00 }, _IRA_OPERAND_MODRM_M_512B, _IRA_NA, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_FXSAVE[] = {
	// 0F AE /0 FXSAVE m512byte A Valid Valid Save the x87 FPU, MMX, XMM, and MXCSR register state to m512byte.
	{ NULL, 0x0001, 0x03D98000, { 0x0F, 0xAE, 0x00 }, _IRA_OPERAND_MODRM_M_512B, _IRA_NA, _IRA_NA, _IRA_NA },
	// REX.W+ 0F AE /0 FXSAVE64 m512byte A Valid N.E. Save the x87 FPU, MMX, XMM, and MXCSR register state to m512byte.
	{ "fxsave64", 0x0008, 0x04998000, { 0x0F, 0xAE, 0x00 }, _IRA_OPERAND_MODRM_M_512B, _IRA_NA, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_FXTRACT[] = {
	// D9 F4 FXTRACT Valid Valid Separate value in ST(0) into exponent and significand, store exponent in ST(0), and push the significand onto the register stack.
	{ NULL, 0x0001, 0x00D80000, { 0xD9, 0xF4, 0x00 }, _IRA_NA, _IRA_NA, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_FYL2X[] = {
	// D9 F1 FYL2X Valid Valid Replace ST(1) with (ST(1) log2ST(0)) and pop the register stack.
	{ NULL, 0x0001, 0x00D80000, { 0xD9, 0xF1, 0x00 }, _IRA_NA, _IRA_NA, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_FYL2XP1[] = {
	// D9 F9 FYL2XP1 Valid Valid Replace ST(1) with ST(1) log2(ST(0) + 1.0) and pop the register stack.
	{ NULL, 0x0001, 0x00D80000, { 0xD9, 0xF9, 0x00 }, _IRA_NA, _IRA_NA, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_HADDPD[] = {
	// 66 0F 7C /r HADDPD xmm1, xmm2/m128 A Valid Valid Horizontal add packed double-precision floatingpoint values from xmm2/m128 to xmm1.
	{ NULL, 0x1001, 0x00D88000, { 0x0F, 0x7C, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_128_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_HADDPS[] = {
	// F2 0F 7C /r HADDPS xmm1, xmm2/m128 A Valid Valid Horizontal add packed single-precision floatingpoint values from xmm2/m128 to xmm1.
	{ NULL, 0x2001, 0x00D88000, { 0x0F, 0x7C, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_128_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_HLT[] = {
	// F4 HLT A Valid Valid Halt
	{ NULL, 0x0001, 0x00C40000, { 0xF4, 0x00, 0x00 }, _IRA_NA, _IRA_NA, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_HSUBPD[] = {
	// 66 0F 7D /r HSUBPD xmm1, xmm2/m128A Valid Valid Horizontal subtract packed double-precision floating pointvalues from xmm2/m128 to xmm1.
	{ NULL, 0x1001, 0x00D88000, { 0x0F, 0x7D, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_128_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_HSUBPS[] = {
	// F2 0F 7D /r HSUBPS xmm1, xmm2/m128 A Valid Valid Horizontal subtract packedsingle-precision floatingpoint values from xmm2/m128 to xmm1.
	{ NULL, 0x2001, 0x00D88000, { 0x0F, 0x7D, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_128_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_IDIV[] = {
	// F6 /7 IDIV r/m8 A Valid Valid Signed divide AX by r/m8,with result stored in: AL Quotient, AH Remainder.
	// REX + F6 /7 IDIV r/m8* A Valid N.E. Signed divide AX by r/m8, with result stored in AL Quotient, AH Remainder.
	{ NULL, 0x0001, 0x00C5B800, { 0xF6, 0x00, 0x00 }, _IRA_EXPLICIT_REG( IRA_REG_GPR, _IRA_REG_AX, _IRA_OS_WORD ), _IRA_OPERAND_MODRM_RM_8_W, _IRA_NA, _IRA_NA },
	// F7 /7 IDIV r/m16 A Valid Valid Signed divide DX:AX by r/m16, with result stored in AX Quotient, DX Remainder.
	// F7 /7 IDIV r/m32 A Valid Valid Signed divide EDX:EAX by r/m32, with result stored in EAX Quotient, EDX Remainder.
	// REX.W + F7 /7 IDIV r/m64 A Valid N.E. Signed divide RDX:RAX by r/m64, with result stored in RAX Quotient, RDX Remainder.
	{ NULL, 0x0001, 0x00C5B800, { 0xF7, 0x00, 0x00 }, _IRA_EXPLICIT_REG_OSA( IRA_REG_GPR, _IRA_REG_AL ), _IRA_OPERAND_MODRM_RM_W, _IRA_NA, _IRA_NA }
};

// ***********************************
// TODO: RWX(W) is not used from here!
// ***********************************

struct ira_opcode_desc _ira_opcode_desc_IMUL[] = {
	// F6 /5 IMUL r/m8* A Valid Valid AX AL r/m byte.
	{ NULL, 0x0001, 0x00C5A800, { 0xF6, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_8_W, _IRA_NA, _IRA_NA, _IRA_NA },
	// F7 /5 IMUL r/m16 A Valid Valid DX:AX AX r/m word.
	// F7 /5 IMUL r/m32 A Valid Valid EDX:EAX EAX r/m32.
	// REX.W + F7 /5 IMUL r/m64 A Valid N.E. RDX:RAX RAX r/m64.
	{ NULL, 0x0001, 0x00C5A800, { 0xF7, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_W, _IRA_NA, _IRA_NA, _IRA_NA },
	// 0F AF /r IMUL r16, r/m16 B Valid Valid word register word register r/m16.
	// 0F AF /r IMUL r32, r/m32 B Valid Valid doubleword register doubleword register r/m32.
	// REX.W + 0F AF /r IMUL r64, r/m64 B Valid N.E. Quadword register Quadword register r/m64.
	{ NULL, 0x0001, 0x00D88000, { 0x0F, 0xAF, 0x00 }, _IRA_OPERAND_MODRM_R_W, _IRA_OPERAND_MODRM_RM,  _IRA_NA, _IRA_NA },
	// 6B /r ib IMUL r16, r/m16, imm8 C Valid Valid word register r/m16 sign-extended immediate byte.
	// 6B /r ib IMUL r32, r/m32, imm8 C Valid Valid doubleword register r/m32 sign-extended immediate byte.
	// REX.W + 6B /r ib IMUL r64, r/m64, imm8 C Valid N.E. Quadword register r/m64 sign-extended immediate byte.
	{ NULL, 0x0001, 0x00C48000, { 0x6B, 0x00, 0x00 }, _IRA_OPERAND_MODRM_R_W, _IRA_OPERAND_MODRM_RM, _IRA_OPERAND_IB_EX_EOSA, _IRA_NA },
	// 69 /r iw IMUL r16, r/m16, imm16 C Valid Valid word register r/m16 immediate word.
	// 69 /r id IMUL r32, r/m32, imm32 C Valid Valid doubleword register r/m32 immediate doubleword.
	{ NULL, 0x0001, 0x03C48000, { 0x69, 0x00, 0x00 }, _IRA_OPERAND_MODRM_R_W, _IRA_OPERAND_MODRM_RM, _IRA_OPERAND_IMM_EOSA, _IRA_NA },
	// REX.W + 69 /r id IMUL r64, r/m64, imm32 C Valid N.E. Quadword register r/m64 immediate doubleword.
	{ NULL, 0x0001, 0x04848000, { 0x69, 0x00, 0x00 }, _IRA_OPERAND_MODRM_R_W, _IRA_OPERAND_MODRM_RM, _IRA_OPERAND_ID_EX_EOSA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_IN[] = {
	// E4 ib IN AL, imm8 A Valid Valid Input byte from imm8 I/O port address into AL.
	{ NULL, 0x0001, 0x07C40000, { 0xE4, 0x00, 0x00 }, _IRA_EXPLICIT_REG( IRA_REG_GPR, _IRA_REG_AL, _IRA_OS_BYTE ), _IRA_OPERAND_IB, _IRA_NA, _IRA_NA },
	// E5 ib IN AX, imm8 A Valid Valid Input word from imm8 I/O port address into AX.
	{ NULL, 0x0001, 0x01C40000, { 0xE5, 0x00, 0x00 }, _IRA_EXPLICIT_REG( IRA_REG_GPR, _IRA_REG_AL, _IRA_OS_WORD), _IRA_OPERAND_IB, _IRA_NA, _IRA_NA },
	// E5 ib IN EAX, imm8 A Valid Valid Input dword from imm8 I/O port address into EAX.
	{ NULL, 0x0001, 0x06C40000, { 0xE5, 0x00, 0x00 }, _IRA_EXPLICIT_REG( IRA_REG_GPR, _IRA_REG_AL, _IRA_OS_DWORD), _IRA_OPERAND_IB, _IRA_NA, _IRA_NA },
	// EC IN AL,DX B Valid Valid Input byte from I/O port in DX into AL.
	{ NULL, 0x0001, 0x07C40000, { 0xEC, 0x00, 0x00 }, _IRA_EXPLICIT_REG( IRA_REG_GPR, _IRA_REG_AL, _IRA_OS_BYTE ), _IRA_EXPLICIT_REG( IRA_REG_GPR, _IRA_REG_DX, _IRA_OS_WORD ), _IRA_NA, _IRA_NA },
	// ED IN AX,DX B Valid Valid Input word from I/O port in DX into AX.
	{ NULL, 0x0001, 0x01C40000, { 0xED, 0x00, 0x00 }, _IRA_EXPLICIT_REG( IRA_REG_GPR, _IRA_REG_AL, _IRA_OS_WORD ), _IRA_EXPLICIT_REG( IRA_REG_GPR, _IRA_REG_DX, _IRA_OS_WORD ), _IRA_NA, _IRA_NA },
	// ED IN EAX,DX B Valid Valid Input doubleword from I/O port in DX into EAX.
	{ NULL, 0x0001, 0x06C40000, { 0xED, 0x00, 0x00 }, _IRA_EXPLICIT_REG( IRA_REG_GPR, _IRA_REG_AL, _IRA_OS_DWORD ), _IRA_EXPLICIT_REG( IRA_REG_GPR, _IRA_REG_DX, _IRA_OS_WORD ), _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_INC[] = {
	// FE /0 INC r/m8 A Valid Valid Increment r/m byte by 1.
	// REX + FE /0 INC r/m8* A Valid N.E. Increment r/m byte by 1.
	{ NULL, 0x0001, 0x00C58000, { 0xFE, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_8_W, _IRA_NA, _IRA_NA, _IRA_NA },
	// FF /0 INC r/m16 A Valid Valid Increment r/m word by 1.
	// FF /0 INC r/m32 A Valid Valid Increment r/m doubleword by 1.
	// REX.W + FF /0 INC r/m64 A Valid N.E. Increment r/m quadword by 1.
	{ NULL, 0x0001, 0x00C58000, { 0xFF, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_W, _IRA_NA, _IRA_NA, _IRA_NA },
	// 40+ rw** INC r16 B N.E. Valid Increment word register by 1.
	// 40+ rd INC r32 B N.E. Valid Increment doubleword register by 1.
	{ NULL, 0x0001, 0x00440001, { 0x40, 0x00, 0x00 }, _IRA_OPERAND_OPCODE_REG( IRA_REG_GPR, _IRA_GPRS_UNDEFINED ), _IRA_NA, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_INS[] = {
	// 6C INS m8, DX A Valid Valid Input byte from I/O port specified in DX into memory location specified in ES:(E)DI or RDI.*
	{ NULL, 0x0001, 0x07C40000, { 0x6C, 0x00, 0x00 },
			_IRA_EXPLICIT_GPS_REG_ADDRESSING( _IRA_REG_DI, _IRA_EOS_BYTE, _IRA_SEG_ENCODE_REGISTER( _IRA_SEG_REG_ES, _IRA_SEG_DENY_OVERRIDE ) ),
			_IRA_EXPLICIT_REG( IRA_REG_GPR, _IRA_REG_DX, _IRA_OS_WORD ), _IRA_NA, _IRA_NA },
	// 6D INS m16, DX A Valid Valid Input word from I/O port specified in DX into memory location specified in ES:(E)DI or RDI.1
	{ NULL, 0x0001, 0x01C40000, { 0x6D, 0x00, 0x00 },
			_IRA_EXPLICIT_GPS_REG_ADDRESSING( _IRA_REG_DI, _IRA_EOS_WORD, _IRA_SEG_ENCODE_REGISTER( _IRA_SEG_REG_ES, _IRA_SEG_DENY_OVERRIDE ) ),
			_IRA_EXPLICIT_REG( IRA_REG_GPR, _IRA_REG_DX, _IRA_OS_WORD ), _IRA_NA, _IRA_NA },
	// 6D INS m32, DX A Valid Valid Input doubleword from I/O port specified in DX into memory location specified in ES:(E)DI or RDI.1
	{ NULL, 0x0001, 0x06C40000, { 0x6D, 0x00, 0x00 },
			_IRA_EXPLICIT_GPS_REG_ADDRESSING( _IRA_REG_DI, _IRA_EOS_DWORD, _IRA_SEG_ENCODE_REGISTER( _IRA_SEG_REG_ES, _IRA_SEG_DENY_OVERRIDE ) ),
			_IRA_EXPLICIT_REG( IRA_REG_GPR, _IRA_REG_DX, _IRA_OS_WORD ), _IRA_NA, _IRA_NA }
	// TODO: W przypadku assemblera trzeba to bedzie obsluzyc.
	// 6C INSB A Valid Valid Input byte from I/O port specified in DX into memory location specified with ES:(E)DI or RDI.1
	// 6D INSW A Valid Valid Input word from I/O portspecified in DX into memory location specified in ES:(E)DI or RDI.1
	// 6D INSD A Valid Valid Input doubleword from I/O port specified in DX into memory location specified in ES:(E)DI or RDI.1
};

struct ira_opcode_desc _ira_opcode_desc_INSERTPS[] = {
	// 66 0F 3A 21 /r ib INSERTPS xmm1, xmm2/m32, imm8 A Valid Valid Insert a single precision floating-point value selected by imm8 from xmm2/m32 into xmm1 at the specified destination element specified by imm8 and zero out destination elements in xmm1 as indicated in imm8.
	{ NULL, 0x1001, 0x00EC8000, { 0x0F, 0x3A, 0x021 }, _IRA_OPERAND_MODRM_R_XMM_32_W, _IRA_OPERAND_MODRM_RM_XMM_32, _IRA_OPERAND_IB, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_INT[] = {
	// CC INT 3 A Valid Valid Interrupt 3—trap to debugger.
	{ NULL, 0x0001, 0x00C40000, { 0xCC, 0x00, 0x00 }, _IRA_EXPLICIT_OPERAND_IB( 3 ), _IRA_NA, _IRA_NA, _IRA_NA },
	// CD ib INT imm8 B Valid Valid Interrupt vector number specified by immediate byte.
	{ NULL, 0x0001, 0x00C40000, { 0xCD, 0x00, 0x00 }, _IRA_OPERAND_IB, _IRA_NA, _IRA_NA, _IRA_NA },
	// CE INTO A Invalid Valid Interrupt 4—if overflow flag is 1.
	{ "into", 0x0001, 0x00C40000, { 0xCE, 0x00, 0x00 }, _IRA_NA, _IRA_NA, _IRA_NA, _IRA_NA },
};

struct ira_opcode_desc _ira_opcode_desc_INVD[] = {
	// 0F 08 INVD A Valid Valid Flush internal caches; initiate flushing of external caches.
	{ NULL, 0x0001, 0x00D80000, { 0x0F, 0x08, 0x00 }, _IRA_NA, _IRA_NA, _IRA_NA, _IRA_NA },
};

struct ira_opcode_desc _ira_opcode_desc_INVLPG[] = {
	// 0F 01/7 INVLPG m A Valid Valid Invalidate TLB Entry for page that contains m.
	{ NULL, 0x0001, 0x00D9B800, { 0x0F, 0x01, 0x00 }, _IRA_OPERAND_MODRM_M_UNDEF, _IRA_NA, _IRA_NA, _IRA_NA },
};

struct ira_opcode_desc _ira_opcode_desc_IRET[] = {
	// CF IRET A Valid Valid Interrupt return (16-bit operand size).
	{ NULL, 0x0001, 0x01C40000, { 0xCF, 0x00, 0x00 }, _IRA_NA, _IRA_NA, _IRA_NA, _IRA_NA },
	// CF IRETD A Valid Valid Interrupt return (32-bit operand size).
	{ "iretd", 0x0001, 0x02C40000, { 0xCF, 0x00, 0x00 }, _IRA_NA, _IRA_NA, _IRA_NA, _IRA_NA },
	// REX.W + CF IRETQ A Valid N.E. Interrupt return (64-bit operand size).
	{ "iretq", 0x0001, 0x04C40000, { 0xCF, 0x00, 0x00 }, _IRA_NA, _IRA_NA, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_LAHF[] = {
	// 9F LAHF A Invalid* Valid Load: AH EFLAGS(SF:ZF:0:AF:0:PF:1:CF).
	{ NULL, 0x0001, 0x00C40000, { 0x9F, 0x00, 0x00 }, _IRA_NA, _IRA_NA, _IRA_NA, _IRA_NA },
};

struct ira_opcode_desc _ira_opcode_desc_LAR[] = {
	// 0F 02 /r LAR r16, r16/m16 A Valid Valid r16 r16/m16 masked by FF00H.
	// 0F 02 /r LAR r32, r32/m16 A Valid Valid r32 r32/m16 masked by 00FxFF00H
	{ NULL, 0x0001, 0x03D80000, { 0x0F, 0x02, 0x00 }, _IRA_OPERAND_MODRM_R_W, _IRA_OPERAND_RM( IRA_REG_GPR, _IRA_EOS_EOSA, _IRA_EOS_WORD, _IRA_RMF_RM ), _IRA_NA, _IRA_NA },
	// REX.W + 0F 02 /r LAR r64, r32/m16 A Valid N.E. r64 r32/m16 masked by 00FxFF00H
	{ NULL, 0x0001, 0x04980000, { 0x0F, 0x02, 0x00 }, _IRA_OPERAND_MODRM_R_W, _IRA_OPERAND_RM( IRA_REG_GPR, _IRA_EOS_DWORD, _IRA_EOS_WORD, _IRA_RMF_RM ), _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_LDDQU[] = {
	// F2 0F F0 /r LDDQU xmm1, mem A Valid Valid Load unaligned data from mem and return double quadword in xmm1.
	{ NULL, 0x2001, 0x00D88000, { 0x0F, 0xF0, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_128_W, _IRA_OPERAND_MODRM_M_UNDEF, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_LDMXCSR[] = {
	// 0F AE /2 LDMXCSR m32 A Valid Valid Load MXCSR register from m32.
	{ NULL, 0x0001, 0x00D99000, { 0x0F, 0xAE, 0x00 }, _IRA_OPERAND_MODRM_M_32, _IRA_NA, _IRA_NA, _IRA_NA }
};

// TODO: Nie ma aktualnie mozliwosci sprawdzenia po disassemblacji, czy to byl far indirect czy nie, poniewaz jest to
// disassemblowane poprostu jako RM z okrelslona wielkoscia operandu.
struct ira_opcode_desc _ira_opcode_desc_LDS[] = {
	// C5 /r LDS r16,m16:16 A Invalid Valid Load DS:r16 with far pointer from memory.
	// C5 /r LDS r32,m16:32 A Invalid Valid Load DS:r32 with far pointer from memory.
	{ NULL, 0x0001, 0x00448000, { 0xC5, 0x00, 0x00 }, _IRA_OPERAND_MODRM_R_W, _IRA_OPERAND_FAR_POINTER_INDIRECT, _IRA_NA, _IRA_NA },
	// 0F B2 /r LSS r16,m16:16 A Valid Valid Load SS:r16 with far pointer from memory.
	// 0F B2 /r LSS r32,m16:32 A Valid Valid Load SS:r32 with far pointer from memory.
	// REX + 0F B2 /r LSS r64,m16:64 A Valid N.E. Load SS:r64 with far pointer from memory.
	{ "lss", 0x0001, 0x00D88000, { 0x0F, 0xB2, 0x00 }, _IRA_OPERAND_MODRM_R_W, _IRA_OPERAND_FAR_POINTER_INDIRECT, _IRA_NA, _IRA_NA },
	// C4 /r LES r16,m16:16 A Invalid Valid Load ES:r16 with far pointer from memory.
	// C4 /r LES r32,m16:32 A Invalid Valid Load ES:r32 with far pointer from memory.
	{ "les", 0x0001, 0x00448000, { 0xC4, 0x00, 0x00 }, _IRA_OPERAND_MODRM_R_W, _IRA_OPERAND_FAR_POINTER_INDIRECT, _IRA_NA, _IRA_NA },
	// 0F B4 /r LFS r16,m16:16 A Valid Valid Load FS:r16 with far pointer from memory.
	// 0F B4 /r LFS r32,m16:32 A Valid Valid Load FS:r32 with far pointer from memory.
	// REX + 0F B4 /r LFS r64,m16:64 A Valid N.E. Load FS:r64 with far pointer from memory.
	{ "lfs", 0x0001, 0x00D88000, { 0x0F, 0xB4, 0x00 }, _IRA_OPERAND_MODRM_R_W, _IRA_OPERAND_FAR_POINTER_INDIRECT, _IRA_NA, _IRA_NA },
	// 0F B5 /r LGS r16,m16:16 A Valid Valid Load GS:r16 with far pointer from memory.
	// 0F B5 /r LGS r32,m16:32 A Valid Valid Load GS:r32 with far pointer from memory.
	// REX + 0F B5 /r LGS r64,m16:64 A Valid N.E. Load GS:r64 with far pointer from memory.
	{ "lgs", 0x0001, 0x00D88000, { 0x0F, 0xB5, 0x00 }, _IRA_OPERAND_MODRM_R_W, _IRA_OPERAND_FAR_POINTER_INDIRECT, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_LEA[] = {
	// 8D /r LEA r16,m A Valid Valid Store effective address for m in register r16.
	// 8D /r LEA r32,m A Valid Valid Store effective address for m in register r32.
	// REX.W + 8D /r LEA r64,m A Valid N.E. Store effective address for m in register r64.
	{ NULL, 0x0001, 0x00C48000, { 0x8D, 0x00, 0x00 }, _IRA_OPERAND_MODRM_R_W, _IRA_OPERAND_MODRM_M_UNDEF, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_LEAVE[] = {
	// C9 LEAVE A Valid Valid Set SP to BP, then pop BP.
	// C9 LEAVE A N.E. Valid Set ESP to EBP, then pop EBP.
	// C9 LEAVE A Valid N.E. Set RSP
	{ NULL, 0x0001, 0x00C40000, { 0xC9, 0x00, 0x00 }, _IRA_NA, _IRA_NA, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_LFENCE[] = {
	// 0F AE /5 LFENCE A Valid Valid Serializes load operations.
	{ NULL, 0x0001, 0x00EC0000, { 0x0F, 0xAE, 0xE8 }, _IRA_NA, _IRA_NA, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_LGDT[] = {
	// 0F 01 /2 LGDT m16&32 A N.E. Valid Load m into GDTR.
	{ NULL, 0x0001, 0x03D99000, { 0x0F, 0x01, 0x00 }, _IRA_OPERAND_M( ( _IRA_OS_WORD + _IRA_OS_DWORD ) ), _IRA_NA, _IRA_NA, _IRA_NA },
	// 0F 01 /2 LGDT m16&64 A Valid N.E. Load m into GDTR.
	{ NULL, 0x0001, 0x04999000, { 0x0F, 0x01, 0x00 }, _IRA_OPERAND_M( ( _IRA_OS_WORD + _IRA_OS_QWORD ) ), _IRA_NA, _IRA_NA, _IRA_NA },
	// 0F 01 /3 LIDT m16&32 A N.E. Valid Load m into IDTR.
	{ "lidt", 0x0001, 0x04999800, { 0x0F, 0x01, 0x00 }, _IRA_OPERAND_M( ( _IRA_OS_WORD + _IRA_OS_DWORD ) ), _IRA_NA, _IRA_NA, _IRA_NA },
	// 0F 01 /3 LIDT m16&64 A Valid N.E. Load m into IDTR.
	{ "lidt", 0x0001, 0x04980000, { 0x0F, 0x01, 0x00 }, _IRA_OPERAND_M( ( _IRA_OS_WORD + _IRA_OS_QWORD ) ), _IRA_NA, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_LLDT[] = {
	// 0F 00 /2 LLDT r/m16 A Valid Valid Load segment selector r/m16 into LDTR.
	{ NULL, 0x0001, 0x00D99000, { 0x0F, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_16, _IRA_NA, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_LMSW[] = {
	// 0F 01 /6 LMSW r/m16 A Valid Valid Loads r/m16 in machine status word of CR0.
	{ NULL, 0x0001, 0x00D9B000, { 0x0F, 0x01, 0x00 }, _IRA_OPERAND_MODRM_RM_16, _IRA_NA, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_LODS[] = {
	// AC LODS m8 A Valid Valid For legacy mode, Load byte at address DS:(E)SI into AL. For 64-bit mode load byte at address (R)SI into AL.
	{ NULL, 0x0001, 0x00C48000, { 0xAC, 0x00, 0x00 },
			_IRA_EXPLICIT_GPS_REG_ADDRESSING( _IRA_REG_SI, _IRA_EOS_BYTE, _IRA_SEG_ENCODE_REGISTER( _IRA_SEG_REG_DS, _IRA_SEG_ALLOW_OVERRIDE ) ),
			_IRA_NA, _IRA_NA, _IRA_NA },
	// AD LODS m16 A Valid Valid For legacy mode, Load word at address DS:(E)SI into AX. For 64-bit mode load word at address (R)SI into AX.
	// AD  LODS m32 A Valid Valid For legacy mode, Load dword at address DS:(E)SI into EAX. For 64-bit mode load dword at address (R)SI into EAX.
	// REX.W + AD LODS m64 A Valid N.E. Load qword at address (R)SI into RAX.
	{ NULL, 0x0001, 0x00C48000, { 0xAD, 0x00, 0x00 },
			_IRA_EXPLICIT_GPS_REG_ADDRESSING( _IRA_REG_SI, _IRA_EOS_EOSA,_IRA_SEG_ENCODE_REGISTER( _IRA_SEG_REG_DS, _IRA_SEG_ALLOW_OVERRIDE ) ),
			_IRA_NA, _IRA_NA, _IRA_NA }
	// TODO: Probably nedded by assembler.
	// AC LODSB A Valid Valid For legacy mode, Load byte at address DS:(E)SI into AL. For 64-bit mode load byte at address (R)SI into AL.
	// AD LODSW A Valid Valid For legacy mode, Load word at address DS:(E)SI into AX. For 64-bit mode load word at address (R)SI into AX.
	// AD LODSD A Valid Valid For legacy mode, Load dword at address DS:(E)SI into EAX. For 64-bit mode load dword at address (R)SI into EAX.
	// REX.W + AD LODSQ A Valid N.E. Load qword at address (R)SI into RAX.
};

struct ira_opcode_desc _ira_opcode_desc_LOOP[] = {
	// E2 cb LOOP rel8 A Valid Valid Decrement count; jump short if count 0.
	{ NULL, 0x0001, 0x00C40000, { 0xE2, 0x00, 0x00 }, _IRA_OPERAND_IMMEDIATE_DIS_RELATIVE_R_8, _IRA_NA, _IRA_NA, _IRA_NA },
	// E1 cb LOOPE rel8 A Valid Valid Decrement count; jump short if count 0 and ZF = 1.
	{ "loope", 0x0001, 0x00C40000, { 0xE1, 0x00, 0x00 }, _IRA_OPERAND_IMMEDIATE_DIS_RELATIVE_R_8, _IRA_NA, _IRA_NA, _IRA_NA },
	// E0 cb LOOPNE rel8 A Valid Valid Decrement count; jump short if count 0 and ZF = 0.
	{ "loopne", 0x0001, 0x00C40000, { 0xE0, 0x00, 0x00 }, _IRA_OPERAND_IMMEDIATE_DIS_RELATIVE_R_8, _IRA_NA, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_LSL[] = {
	// 0F 03 /r LSL r16, r16/m16 A Valid Valid Load: r16 segment limit, selector r16/m16.
	// 0F 03 /r LSL r32, r32/m16* A Valid Valid Load: r32 segment limit, selector r32/m16.
	{ NULL, 0x0001, 0x03D80000, { 0x0F, 0x03, 0x00 }, _IRA_OPERAND_MODRM_R_W, _IRA_OPERAND_RM( IRA_REG_GPR, _IRA_EOS_EOSA, _IRA_EOS_WORD, _IRA_RMF_RM ), _IRA_NA, _IRA_NA },
	// REX.W + 0F 03 /r LSL r64, r32/m16* A Valid Valid Load: r64 segment limit, selector r32/m16
	{ NULL, 0x0001, 0x04980000, { 0x0F, 0x03, 0x00 }, _IRA_OPERAND_MODRM_R_W, _IRA_OPERAND_RM( IRA_REG_GPR, _IRA_EOS_DWORD, _IRA_EOS_WORD, _IRA_RMF_RM ), _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_LTR[] = {
	// 0F 00 /3 LTR r/m16 A Valid Valid Load r/m16 into task register.
	{ NULL, 0x0001, 0x00D99800, { 0x0F, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_16, _IRA_NA, _IRA_NA, _IRA_NA },
};

struct ira_opcode_desc _ira_opcode_desc_MASKMOVDQU[] = {
	// 66 0F F7 /r MASKMOVDQU xmm1, xmm2 A Valid Valid Selectively write bytes from xmm1 to memory location using the byte mask in xmm2. The default memory location is specified by DS:EDI/RDI.
	{ NULL, 0x1001, 0x00D88000, { 0x0F, 0xF7, 0x00 }, _IRA_OPERAND_R( IRA_REG_XMM, _IRA_OS_OWORD ), _IRA_OPERAND_RM( IRA_REG_XMM, _IRA_EOS_OWORD, _IRA_EOS_UNDEFINED, _IRA_RMF_R ), _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_MASKMOVQ[] = {
	// 0F F7 /r MASKMOVQ mm1, mm2 A Valid Valid Selectively write bytes from mm1 to memory location using the byte mask in mm2. The default memory location is specified by DS:EDI/RDI.
	{ NULL, 0x0001, 0x00D88000, { 0x0F, 0xF7, 0x00 }, _IRA_OPERAND_R( IRA_REG_MMX, _IRA_OS_QWORD ), _IRA_OPERAND_RM( IRA_REG_MMX, _IRA_EOS_QWORD, _IRA_EOS_UNDEFINED, _IRA_RMF_R ), _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_MAXPD[] = {
	// 66 0F 5F /r MAXPD xmm1, xmm2/m128 A Valid Valid Return the maximum double-precision floatingpoint values between xmm2/m128 and xmm1.
	{ NULL, 0x1001, 0x00D88000, { 0x0F, 0x5F, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_128_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_MAXPS[] = {
	// 0F 5F /r MAXPS xmm1, xmm2/m128 A Valid Valid Return the maximum singleprecision floating-point values between xmm2/m128 and xmm1.
	{ NULL, 0x0001, 0x00D88000, { 0x0F, 0x5F, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_128_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA }
};

// TODO: Zastanowic sie na dwiloscia operandu podawanego dla trubow _IRA_OPERAND_MODRM_R_, czy ma ona sens? Najprwdopodobniejnie ma to zadnego znaczenia przynajmniej z punktu widzenia assemblera, no moze tylko dla GPR tu ma.

struct ira_opcode_desc _ira_opcode_desc_MAXSD[] = {
	// F2 0F 5F /r MAXSD xmm1, xmm2/m64 A Valid Valid Return the maximum scalardouble-precision floatingpoint value between xmm2/mem64 and xmm1.
	{ NULL, 0x2001, 0x00D88000, { 0x0F, 0x5F, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_64_W, _IRA_OPERAND_MODRM_RM_XMM_64, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_MAXSS[] = {
	// F3 0F 5F /r MAXSS xmm1, xmm2/m32 A Valid Valid Return the maximum scalarsingle-precision floatingpoint value between xmm2/mem32 and xmm1.
	{ NULL, 0x4001, 0x00D88000, { 0x0F, 0x5F, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_32_W, _IRA_OPERAND_MODRM_RM_XMM_32, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_MFENCE[] = {
	// MFENCE 0F AE /6  A Valid Valid Serializes load and store operations.
	{ NULL, 0x0001, 0x00EC0000, { 0x0F, 0xAE, 0xF0 }, _IRA_NA, _IRA_NA, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_MINPD[] = {
	// 66 0F 5D /r MINPD xmm1, xmm2/m128 A Valid Valid Return the minimum doubleprecision floating-point values between xmm2/m128 and xmm1.
	{ NULL, 0x1001, 0x00D88000, { 0x0F, 0x5D, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_128_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_MINPS[] = {
	// 0F 5D /r MINPS xmm1, xmm2/m128 A Valid Valid Return the minimum singleprecision floating-point values between xmm2/m128 and xmm1.
	{ NULL, 0x0001, 0x00D88000, { 0x0F, 0x5D, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_128_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_MINSD[] = {
	// F2 0F 5D /r MINSD xmm1, xmm2/m64 A Valid Valid Return the minimum scalar double-precision floatingpoint value between xmm2/mem64 and xmm1.
	{ NULL, 0x2001, 0x00D88000, { 0x0F, 0x5D, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_64_W, _IRA_OPERAND_MODRM_RM_XMM_64, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_MINSS[] = {
	// F3 0F 5D /r MINSS xmm1, xmm2/m32 A Valid Valid Return the minimum scalar single-precision floatingpoint value between xmm2/mem32 and xmm1.
	{ NULL, 0x4001, 0x00D88000, { 0x0F, 0x5D, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_32_W, _IRA_OPERAND_MODRM_RM_XMM_32, _IRA_NA, _IRA_NA }
};

// TODO: Zastanowic sie nad operandami virtualnymi, czyli takimi ktore wystepuja w instrukcji ale tak naprawde nie sa zapiane w pecyfikacji jako operancdy patrz instrukcja ponizej:

struct ira_opcode_desc _ira_opcode_desc_MONITOR[] = {
	// 0F 01 C8 MONITOR A Valid Valid Sets up a linear address range to be monitored by hardware and activates the monitor. The address range should be a write-back memory caching type. The address is DS:EAX
	{ NULL, 0x0001, 0x006C0000, { 0x0F, 0x01, 0xC8 }, _IRA_EXPLICIT_REG( IRA_REG_GPR, _IRA_REG_EAX, _IRA_OS_DWORD ),
		_IRA_EXPLICIT_REG( IRA_REG_GPR, _IRA_REG_ECX, _IRA_OS_DWORD ),
		_IRA_EXPLICIT_REG( IRA_REG_GPR, _IRA_REG_EDX, _IRA_OS_DWORD ), _IRA_NA },
	{ NULL, 0x0001, 0x00AC0000, { 0x0F, 0x01, 0xC8 }, _IRA_EXPLICIT_REG( IRA_REG_GPR, _IRA_REG_RAX, _IRA_OS_QWORD ),
		_IRA_EXPLICIT_REG( IRA_REG_GPR, _IRA_REG_RCX, _IRA_OS_QWORD ),
		_IRA_EXPLICIT_REG( IRA_REG_GPR, _IRA_REG_RDX, _IRA_OS_QWORD ), _IRA_NA }
	// TODO: Przy assemblacji pameitac zeby pozwolic na assemblacje samej mnemoniki!
};

struct ira_opcode_desc _ira_opcode_desc_MOVAPD[] = {
	// 66 0F 28 /r MOVAPD xmm1, xmm2/m128 A Valid Valid Move packed doubleprecision floating-point values from xmm2/m128 to xmm1.
	{ NULL, 0x1001, 0x00D88000, { 0x0F, 0x28, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_128_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA },
	// 66 0F 29 /r MOVAPD xmm2/m128, xmm1 B Valid Valid Move packed doubleprecision floating-point values from xmm1 to xmm2/m128.
	{ NULL, 0x1001, 0x00D88000, { 0x0F, 0x29, 0x00 }, _IRA_OPERAND_MODRM_RM_XMM_128_W, _IRA_OPERAND_MODRM_R_XMM_128, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_MOVAPS[] = {
	// 0F 28 /r MOVAPS xmm1, xmm2/m128 A Valid Valid Move packed singleprecision floating-point values from xmm2/m128 to xmm1.
	{ NULL, 0x0001, 0x00D88000, { 0x0F, 0x28, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_128_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA },
	// 0F 29 /r MOVAPS xmm2/m128, xmm1 B Valid Valid Move packed singleprecision floating-point values from xmm1 to xmm2/m128.
	{ NULL, 0x0001, 0x00D88000, { 0x0F, 0x29, 0x00 }, _IRA_OPERAND_MODRM_RM_XMM_128_W, _IRA_OPERAND_MODRM_R_XMM_128, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_MOVBE[] = {
	// 0F 38 F0 /r MOVBE r16, m16 A Valid Valid Reverse byte order in m16 and move to r16
	// 0F 38 F0 /r MOVBE r32, m32 A Valid Valid Reverse byte order in m32 and move to r32
	// REX.W + 0F 38 F0 /r MOVBE r64, m64 A Valid N.E. Reverse byte order in m64 and move to r64.
	{ NULL, 0x0001, 0x00EC8000, { 0x0F, 0x38, 0xF0 }, _IRA_OPERAND_MODRM_R_W, _IRA_OPERAND_MODRM_RM, _IRA_NA, _IRA_NA },
	// 0F 38 F1 /r MOVBE m16, r16 B Valid Valid Reverse byte order in r16 and move to m16
	// 0F 38 F1 /r MOVBE m32, r32 B Valid Valid Reverse byte order in r32 and move to m32
	// REX.W + 0F 38 F1 /r MOVBE m64, r64 B Valid N.E. Reverse byte order in
	{ NULL, 0x0001, 0x00EC8000, { 0x0F, 0x38, 0xF1 }, _IRA_OPERAND_MODRM_RM_W, _IRA_OPERAND_MODRM_R, _IRA_NA, _IRA_NA }
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
		_IA_INSTRUCTION( "cbw", _ira_opcode_desc_CBW),
		_IA_INSTRUCTION( "clc", _ira_opcode_desc_CLC),
		_IA_INSTRUCTION( "cld", _ira_opcode_desc_CLD),
		_IA_INSTRUCTION( "clflush", _ira_opcode_desc_CLFLUSH),
		_IA_INSTRUCTION( "cli", _ira_opcode_desc_CLI),
		_IA_INSTRUCTION( "clts", _ira_opcode_desc_CLTS),
		_IA_INSTRUCTION( "cmc", _ira_opcode_desc_CMC),
		_IA_INSTRUCTION( "cmov", _ira_opcode_desc_CMOVA),
		_IA_INSTRUCTION( "cmp", _ira_opcode_desc_CMP),
		_IA_INSTRUCTION( "cmppd", _ira_opcode_desc_CMPPD),
		_IA_INSTRUCTION( "cmpps", _ira_opcode_desc_CMPPS),
		_IA_INSTRUCTION( "cmps", _ira_opcode_desc_CMPS),
		_IA_INSTRUCTION( "cmpsd", _ira_opcode_desc_CMPSD),
		_IA_INSTRUCTION( "cmpss", _ira_opcode_desc_CMPSS),
		_IA_INSTRUCTION( "cmpxchg", _ira_opcode_desc_CMPXCHG),
		_IA_INSTRUCTION( "cmpxchg8b", _ira_opcode_desc_CMPXCHGxB),
		_IA_INSTRUCTION( "comisd", _ira_opcode_desc_COMISD),
		_IA_INSTRUCTION( "comiss", _ira_opcode_desc_COMISS),
		_IA_INSTRUCTION( "cpuid", _ira_opcode_desc_CPUID),
		_IA_INSTRUCTION( "crc32", _ira_opcode_desc_CRC32),
		_IA_INSTRUCTION( "cvtdq2pd", _ira_opcode_desc_CVTDQ2PD),
		_IA_INSTRUCTION( "cvtdq2ps", _ira_opcode_desc_CVTDQ2PS),
		_IA_INSTRUCTION( "cvtpd2dq", _ira_opcode_desc_CVTPD2DQ),
		_IA_INSTRUCTION( "cvtpd2pi", _ira_opcode_desc_CVTPD2PI),
		_IA_INSTRUCTION( "cvtpd2ps", _ira_opcode_desc_CVTPD2PS),
		_IA_INSTRUCTION( "cvtpi2pd", _ira_opcode_desc_CVTPI2PD),
		_IA_INSTRUCTION( "cvtpi2ps", _ira_opcode_desc_CVTPI2PS),
		_IA_INSTRUCTION( "cvtps2dq", _ira_opcode_desc_CVTPS2DQ),
		_IA_INSTRUCTION( "cvtps2pd", _ira_opcode_desc_CVTPS2PD),
		_IA_INSTRUCTION( "cvtps2pi", _ira_opcode_desc_CVTPS2PI),
		_IA_INSTRUCTION( "cvtsd2si", _ira_opcode_desc_CVTSD2SI),
		_IA_INSTRUCTION( "cvtsd2ss", _ira_opcode_desc_CVTSD2SS),
		_IA_INSTRUCTION( "cvtsi2sd", _ira_opcode_desc_CVTSI2SD),
		_IA_INSTRUCTION( "cvtsi2ss", _ira_opcode_desc_CVTSI2SS),
		_IA_INSTRUCTION( "cvtss2sd", _ira_opcode_desc_CVTSS2SD),
		_IA_INSTRUCTION( "cvtss2si", _ira_opcode_desc_CVTSS2SI),
		_IA_INSTRUCTION( "cvttpd2dq", _ira_opcode_desc_CVTTPD2DQ),
		_IA_INSTRUCTION( "cvttpd2pi", _ira_opcode_desc_CVTTPD2PI),
		_IA_INSTRUCTION( "cvttps2dq", _ira_opcode_desc_CVTTPS2DQ),
		_IA_INSTRUCTION( "cvttps2pi", _ira_opcode_desc_CVTTPS2PI),
		_IA_INSTRUCTION( "cvttsd2si", _ira_opcode_desc_CVTTSD2SI),
		_IA_INSTRUCTION( "cvttss2si", _ira_opcode_desc_CVTTSS2SI),
		_IA_INSTRUCTION( "cwd", _ira_opcode_desc_CWD_CDQ_CQO),
		_IA_INSTRUCTION( "daa", _ira_opcode_desc_DAA),
		_IA_INSTRUCTION( "das", _ira_opcode_desc_DAS),
		_IA_INSTRUCTION( "dec", _ira_opcode_desc_DEC),
		_IA_INSTRUCTION( "div", _ira_opcode_desc_DIV),
		_IA_INSTRUCTION( "divpd", _ira_opcode_desc_DIVPD),
		_IA_INSTRUCTION( "divps", _ira_opcode_desc_DIVPS),
		_IA_INSTRUCTION( "divsd", _ira_opcode_desc_DIVSD),
		_IA_INSTRUCTION( "divss", _ira_opcode_desc_DIVSS),
		_IA_INSTRUCTION( "dppd", _ira_opcode_desc_DPPD),
		_IA_INSTRUCTION( "dpps", _ira_opcode_desc_DPPS),
		_IA_INSTRUCTION( "emms", _ira_opcode_desc_EMMS),
		_IA_INSTRUCTION( "enter", _ira_opcode_desc_ENTER),
		_IA_INSTRUCTION( "extractps", _ira_opcode_desc_EXTRACTPS),
		_IA_INSTRUCTION( "f2xm1", _ira_opcode_desc_F2XM1),
		_IA_INSTRUCTION( "fabs", _ira_opcode_desc_FABS),
		_IA_INSTRUCTION( "fadd", _ira_opcode_desc_FADD),
		_IA_INSTRUCTION( "fbld", _ira_opcode_desc_FBLD),
		_IA_INSTRUCTION( "fbstp", _ira_opcode_desc_FBSTP),
		_IA_INSTRUCTION( "fchs", _ira_opcode_desc_FCHS),
		_IA_INSTRUCTION( "fclex", _ira_opcode_desc_FCLEX),
		_IA_INSTRUCTION( _IRA_EMPTY_MNEMONIC, _ira_opcode_desc_FCMOV),
		_IA_INSTRUCTION( _IRA_EMPTY_MNEMONIC, _ira_opcode_desc_FCOM),
		_IA_INSTRUCTION( "fcos", _ira_opcode_desc_FCOS),
		_IA_INSTRUCTION( "fdecstp", _ira_opcode_desc_FDECSTP),
		_IA_INSTRUCTION( "fdiv", _ira_opcode_desc_FDIV),
		_IA_INSTRUCTION( "fdivr", _ira_opcode_desc_FDIVR),
		_IA_INSTRUCTION( "ffree", _ira_opcode_desc_FFREE ),
		_IA_INSTRUCTION( "ficom", _ira_opcode_desc_FICOM ),
		_IA_INSTRUCTION( "fild", _ira_opcode_desc_FILD ),
		_IA_INSTRUCTION( "fincstp", _ira_opcode_desc_FINCSTP ),
		_IA_INSTRUCTION( "finit", _ira_opcode_desc_FINIT ),
		_IA_INSTRUCTION( "fist", _ira_opcode_desc_FIST ),
		_IA_INSTRUCTION( "fisttp", _ira_opcode_desc_FISTTP ),
		_IA_INSTRUCTION( "fld", _ira_opcode_desc_FLD ),
		_IA_INSTRUCTION( _IRA_EMPTY_MNEMONIC, _ira_opcode_desc_FLDx ),
		_IA_INSTRUCTION( "fldcw", _ira_opcode_desc_FLDCW),
		_IA_INSTRUCTION( "fldenv", _ira_opcode_desc_FLDENV),
		_IA_INSTRUCTION( "fmul", _ira_opcode_desc_FMUL ),
		_IA_INSTRUCTION( "fnop", _ira_opcode_desc_FNOP ),
		_IA_INSTRUCTION( "fpatan", _ira_opcode_desc_FPATAN ),
		_IA_INSTRUCTION( "fprem", _ira_opcode_desc_FPREM ),
		_IA_INSTRUCTION( "fprem1", _ira_opcode_desc_FPREM1 ),
		_IA_INSTRUCTION( "fptan", _ira_opcode_desc_FPTAN ),
		_IA_INSTRUCTION( "frndint", _ira_opcode_desc_FRNDINT ),
		_IA_INSTRUCTION( "frstor", _ira_opcode_desc_FRSTOR),
		_IA_INSTRUCTION( "fsave", _ira_opcode_desc_FSAVE ),
		_IA_INSTRUCTION( "fscale", _ira_opcode_desc_FSCALE ),
		_IA_INSTRUCTION( "fsin", _ira_opcode_desc_FSIN ),
		_IA_INSTRUCTION( "fsincos", _ira_opcode_desc_FSINCOS ),
		_IA_INSTRUCTION( "fsqrt", _ira_opcode_desc_FSQRT ),
		_IA_INSTRUCTION( "fst", _ira_opcode_desc_FST ),
		_IA_INSTRUCTION( "fstcw", _ira_opcode_desc_FSTCW ),
		_IA_INSTRUCTION( "fstenv", _ira_opcode_desc_FSTENV ),
		_IA_INSTRUCTION( "fstsw", _ira_opcode_desc_FSTSW ),
		_IA_INSTRUCTION( "fsub", _ira_opcode_desc_FSUB ),
		_IA_INSTRUCTION( "fsubr", _ira_opcode_desc_FSUBR ),
		_IA_INSTRUCTION( "ftst", _ira_opcode_desc_FTST ),
		_IA_INSTRUCTION( "fucom", _ira_opcode_desc_FUCOM ),
		_IA_INSTRUCTION( "fxam", _ira_opcode_desc_FXAM ),
		_IA_INSTRUCTION( "fxch", _ira_opcode_desc_FXCH ),
		_IA_INSTRUCTION( "fxrstor", _ira_opcode_desc_FXRSTOR ),
		_IA_INSTRUCTION( "fxsave", _ira_opcode_desc_FXSAVE ),
		_IA_INSTRUCTION( "fxtract", _ira_opcode_desc_FXTRACT ),
		_IA_INSTRUCTION( "fyl2x", _ira_opcode_desc_FYL2X ),
		_IA_INSTRUCTION( "fyl2xp1", _ira_opcode_desc_FYL2XP1 ),
		_IA_INSTRUCTION( "haddpd", _ira_opcode_desc_HADDPD ),
		_IA_INSTRUCTION( "haddps", _ira_opcode_desc_HADDPS ),
		_IA_INSTRUCTION( "hlt", _ira_opcode_desc_HLT ),
		_IA_INSTRUCTION( "hsubpd", _ira_opcode_desc_HSUBPD ),
		_IA_INSTRUCTION( "hsubps", _ira_opcode_desc_HSUBPS ),
		_IA_INSTRUCTION( "idiv", _ira_opcode_desc_IDIV ),
		_IA_INSTRUCTION( "imul", _ira_opcode_desc_IMUL ),
		_IA_INSTRUCTION( "in", _ira_opcode_desc_IN ),
		_IA_INSTRUCTION( "inc", _ira_opcode_desc_INC ),
		_IA_INSTRUCTION( "ins", _ira_opcode_desc_INS ),
		_IA_INSTRUCTION( "insertps", _ira_opcode_desc_INSERTPS ),
		_IA_INSTRUCTION( "int", _ira_opcode_desc_INT ),
		_IA_INSTRUCTION( "invd", _ira_opcode_desc_INVD ),
		_IA_INSTRUCTION( "invlpg", _ira_opcode_desc_INVLPG ),
		_IA_INSTRUCTION( "iret", _ira_opcode_desc_IRET ),
		_IA_INSTRUCTION( "jcxz", _ira_opcode_desc_JCXZ),
		_IA_INSTRUCTION( "j", _ira_opcode_desc_Jcc),
		_IA_INSTRUCTION( "jmp", _ira_opcode_desc_JMP),
		_IA_INSTRUCTION( "lahf", _ira_opcode_desc_LAHF),
		_IA_INSTRUCTION( "lar", _ira_opcode_desc_LAR),
		_IA_INSTRUCTION( "lddqu", _ira_opcode_desc_LDDQU),
		_IA_INSTRUCTION( "ldmxcsr", _ira_opcode_desc_LDMXCSR),
		_IA_INSTRUCTION( "lds", _ira_opcode_desc_LDS),
		_IA_INSTRUCTION( "lea", _ira_opcode_desc_LEA),
		_IA_INSTRUCTION( "leave", _ira_opcode_desc_LEAVE),
		_IA_INSTRUCTION( "lfence", _ira_opcode_desc_LFENCE),
		_IA_INSTRUCTION( "lgdt", _ira_opcode_desc_LGDT),
		_IA_INSTRUCTION( "lldt", _ira_opcode_desc_LLDT),
		_IA_INSTRUCTION( "lmsw", _ira_opcode_desc_LMSW),
		_IA_INSTRUCTION( "lods", _ira_opcode_desc_LODS),
		_IA_INSTRUCTION( "loop", _ira_opcode_desc_LOOP),
		_IA_INSTRUCTION( "lsl", _ira_opcode_desc_LSL),
		_IA_INSTRUCTION( "ltr", _ira_opcode_desc_LTR),
		_IA_INSTRUCTION( "maskmovdqu", _ira_opcode_desc_MASKMOVDQU),
		_IA_INSTRUCTION( "maskmovq", _ira_opcode_desc_MASKMOVQ),
		_IA_INSTRUCTION( "maxpd", _ira_opcode_desc_MAXPD),
		_IA_INSTRUCTION( "maxps", _ira_opcode_desc_MAXPS),
		_IA_INSTRUCTION( "maxsd", _ira_opcode_desc_MAXSD),
		_IA_INSTRUCTION( "maxss", _ira_opcode_desc_MAXSS),
		_IA_INSTRUCTION( "mfence", _ira_opcode_desc_MFENCE),
		_IA_INSTRUCTION( "minpd", _ira_opcode_desc_MINPD),
		_IA_INSTRUCTION( "minps", _ira_opcode_desc_MINPS),
		_IA_INSTRUCTION( "minsd", _ira_opcode_desc_MINSD),
		_IA_INSTRUCTION( "minss", _ira_opcode_desc_MINSS),
		_IA_INSTRUCTION( "monitor", _ira_opcode_desc_MONITOR),
		_IA_INSTRUCTION( "movapd", _ira_opcode_desc_MOVAPD),
		_IA_INSTRUCTION( "movaps", _ira_opcode_desc_MOVAPS),
		_IA_INSTRUCTION( "movbe", _ira_opcode_desc_MOVBE),
		{ NULL, 0, 0, NULL }
};





