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


/*#define _INSTRUCTION_TEMPLATE_BINARY_ARITHMETIC_1( mnemonic, base_opcode, opcode_ext ) { \
		_IRA_ENCODE_OPCODE_FLAGS_OPCODE_EXT
	// base_opcode + 4 ib mnemonic AL,imm8
	{ NULL, 0x0001, 0x00C40000, { 0x14, 0x00, 0x00 }, _IRA_OPERAND_REG_ACCUMULATOR_8, _IRA_OPERAND_IB, _IRA_NA, _IRA_NA },
};*/

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
	{ NULL, 0x1001, 0x00D88000, { 0x0F, 0x58, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA },
	// VEX.NDS.128.66.0F 58 /r VADDPD xmm1,xmm2, xmm3/m128 V/V AVX Add packed double-precision floating-point values from xmm3/mem to xmm2 and stores result in xmm1.
	{ "vaddpd", 0x1080, 0x00D88000, { 0x0F, 0x58, 0x00 }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_SIMD, _IRA_NA }
};


struct ira_opcode_desc _ira_opcode_desc_ADDPS[] = {
	// 0F 58 /r ADDPS xmm1, xmm2/m128 A Valid Valid Add packed single-precision floating-point values from xmm2/m128 to xmm1.
	{ NULL, 0x0001, 0x00D88000, { 0x0F, 0x58, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA },
	// VEX.NDS.128.0F 58 /r VADDPS xmm1,xmm2, xmm3/m128
	// VEX.NDS.256.0F 58 /r VADDPS ymm1, ymm2, ymm3/m256
	{ "vaddps", 0x0080, 0x00D88000, { 0x0F, 0x58, 0x00 }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_SIMD, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_ADDSD[] = {
	// F2 0F 58 /r ADDSD xmm1, xmm2/m64 A Valid Valid Add the low doubleprecision floating-point value from xmm2/m64 to xmm1.
	{ NULL, 0x2001, 0x00D88000, { 0x0F, 0x58, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_64, _IRA_NA, _IRA_NA },
	// VEX.NDS.128.F2.0F 58 /r VADDSD xmm1,xmm2,xmm3/m64
	{ "vaddsd", 0x20C0, 0x00D88000, { 0x0F, 0x58, 0x00 }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_SIMD_64, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_ADDSS[] = {
	// F3 0F 58 /r ADDSS xmm1, xmm2/m32 A Valid Valid Add the low single-precision floating-point value from xmm2/m32 to xmm1.
	{ NULL, 0x4001, 0x00D88000, { 0x0F, 0x58, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_32, _IRA_NA, _IRA_NA },
	// VEX.NDS.128.F3.0F 58 /r VADDSS xmm1,xmm2, xmm3/m32
	{ "vaddss", 0x40C0, 0x00D88000, { 0x0F, 0x58, 0x00 }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_SIMD_32, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_ADDSUBPD[] = {
	//66 0F D0 /r ADDSUBPD xmm1, xmm2/m128 A Valid Valid Add/subtract doubleprecision floating-point values from xmm2/m128 to xmm1.
	{ NULL, 0x1001, 0x00D88000, { 0x0F, 0xD0, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA },
	// VEX.NDS.128.66.0F D0 /r VADDSUBPD xmm1,xmm2,xmm3/m128
	// VEX.NDS.256.66.0F D0 /r VADDSUBPD ymm1,ymm2,ymm3/m256
	{ "vaddsubpd", 0x1080, 0x00D88000, { 0x0F, 0xD0, 0x00 }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_SIMD, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_ADDSUBPS[] = {
	// F2 0F D0 /r ADDSUBPS xmm1, xmm2/m128 A Valid Valid Add/subtract singleprecision floating-point values from xmm2/m128 to xmm1.
	{ NULL, 0x2001, 0x00D88000, { 0x0F, 0xD0, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA },
	// VEX.NDS.128.F2.0F D0 /r VADDSUBPS xmm1,xmm2,xmm3/m128
	// VEX.NDS.256.F2.0F D0 /r VADDSUBPS ymm1, ymm2,ymm3/m256
	{ "vaddsubps", 0x2080, 0x00D88000, { 0x0F, 0xD0, 0x00 }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_SIMD, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_AESDEC[] = {
	// 66 0F 38 DE /r AESDEC xmm1,xmm2/m128 A Valid Valid Perform one round of an AES decryption flow, using the Equivalent Inverse Cipher, operating on a 128-bit data (state) from xmm1 with a 128-bit round key from xmm2/m128.
	{ NULL, 0x1001, 0x00EC8000, { 0x0F, 0x38, 0xDE }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_AESDECLAST[] = {
	// 66 0F 38 DF /r AESDECLAST xmm1,xmm2/m128 A Valid Valid Perform the last round of an AES decryption flow, using the Equivalent Inverse Cipher, operating on a 128-bit data (state) from xmm1 with a 128-bit round key from xmm2/m128.
	{ NULL, 0x1001, 0x00EC8000, { 0x0F, 0x38, 0xDF }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_AESENC[] = {
	// 66 0F 38 DC /r AESENC xmm1, xmm2/m128 A Valid Valid Perform one round of an AES encryption flow, operating on a 128-bit data (state) from xmm1 with a 128-bit round key from xmm2/m128.
	{ NULL, 0x1001, 0x00EC8000, { 0x0F, 0x38, 0xDC }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_AESENCLAST[] = {
	//66 0F 38 DD /r AESENCLAST xmm1, xmm2/m128 A Valid Valid Perform the last round of an AES encryption flow, operating on a 128-bit data (state) from xmm1 with a 128-bit round key from xmm2/m128.
	{ NULL, 0x1001, 0x00EC8000, { 0x0F, 0x38, 0xDD }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_AESIMC[] = {
	// 66 0F 38 DB /r AESIMC xmm1, xmm2/m128 A Valid Valid Perform the InvMixColumn transformation on a 128-bit round key from xmm2/m128 and store the result in xmm1.
	{ NULL, 0x1001, 0x00EC8000, { 0x0F, 0x38, 0xDB }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_AESKEYGENASSIST[] = {
	// 66 0F 3A DF /r ib AESKEYGENASSIST xmm1, xmm2/m128, imm8 A Valid Valid Assist in AES round key generation using an 8 bits Round Constant (RCON) specified in the immediate byte, operating on 128 bits of data specified in xmm2/m128 and stores the result in xmm1.
	{ NULL, 0x1001, 0x00EC8000, { 0x0F, 0x3A, 0xDF }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_OPERAND_IB, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_AND[] = {
	// 24 ib AND AL, imm8 C Valid Valid AL AND imm8.
	{ NULL, 0x0001, 0x00C40000, { 0x24, 0x00, 0x00 }, _IRA_OPERAND_REG_ACCUMULATOR_8, _IRA_OPERAND_IB, _IRA_NA, _IRA_NA },
	// 25 iw AND AX, imm16 C Valid Valid AX AND imm16.
	// 25 id AND EAX, imm32 C Valid Valid EAX AND imm32.
	{ NULL, 0x0001, 0x03C40000, { 0x25, 0x00, 0x00 }, _IRA_OPERAND_REG_ACCUMULATOR_OSA_W, _IRA_OPERAND_IMM_EOSA, _IRA_NA, _IRA_NA },
	// REX.W + 25 id AND RAX, imm32 C Valid N.E. RAX AND imm32 signextended to 64-bits.
	{ NULL, 0x0001, 0x04840000, { 0x25, 0x00, 0x00 }, _IRA_OPERAND_REG_ACCUMULATOR_OSA_W, _IRA_OPERAND_ID_EX_EOSA, _IRA_NA, _IRA_NA },
	// 80 /4 ib AND r/m8, imm8 MR Valid Valid r/m8 AND imm8.
	// REX + 80 /4 ib AND r/m8*, imm8 MR Valid N.E. r/m8 AND imm8.
	{ NULL, 0x0001, 0x00C5A000, { 0x80, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_8_W, _IRA_OPERAND_IB, _IRA_NA, _IRA_NA },
	// 81 /4 iw AND r/m16, imm16 B Valid Valid r/m16 AND imm16.
	// 81 /4 id AND r/m32, imm32 B Valid Valid r/m32 AND imm32.
	{ NULL, 0x0001, 0x03C5A000, { 0x81, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_W, _IRA_OPERAND_IMM_EOSA, _IRA_NA, _IRA_NA },
	// REX.W + 81 /4 id AND r/m64, imm32 B Valid N.E. r/m64 AND imm32 sign extended to 64-bits.
	{ NULL, 0x0001, 0x0485A000, { 0x81, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_W, _IRA_OPERAND_ID_EX_EOSA, _IRA_NA, _IRA_NA },
	// 83 /4 ib AND r/m16, imm8 B Valid Valid r/m16 AND imm8 (signextended).
	// 83 /4 ib AND r/m32, imm8 B Valid Valid r/m32 AND imm8 (signextended).
	{ NULL, 0x0001, 0x03C5A000, { 0x83, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_W, _IRA_OPERAND_IB_EX_EOSA, _IRA_NA, _IRA_NA },
	// REX.W + 83 /4 ib AND r/m64, imm8 B Valid N.E. r/m64 AND imm8 (signextended).
	{ NULL, 0x0001, 0x0485A000, { 0x83, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_W, _IRA_OPERAND_IB_EX_EOSA, _IRA_NA, _IRA_NA },
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
	{ NULL, 0x1001, 0x00D88000, { 0x0F, 0x54, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA },
	// VEX.NDS.128.66.0F 54 /r VANDPD xmm1,xmm2,xmm3/m128
	// VEX.NDS.256.66.0F 54 /r VANDPD ymm1,ymm2,ymm3/m256
	{ "vandpd", 0x1080, 0x00D88000, { 0x0F, 0x54, 0x00 }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_SIMD, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_ANDPS[] = {
	// 0F 54 /r ANDPS xmm1, xmm2/m128 A Valid Valid Bitwise logical AND of xmm2/m128 and xmm1.
	{ NULL, 0x0001, 0x00D88000, { 0x0F, 0x54, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA },
	// VEX.NDS.128.0F 54 /r VANDPS xmm1,xmm2, xmm3/m128
	// VEX.NDS.256.0F 54 /r VANDPS ymm1, ymm2, ymm3/m256
	{ "vandps", 0x0080, 0x00D88000, { 0x0F, 0x54, 0x00 }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_SIMD, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_ANDNPD[] = {
	// 66 0F 55 /r ANDNPD xmm1, xmm2/m128 A Valid Valid Bitwise logical AND NOT of xmm2/m128 and xmm1.
	{ NULL, 0x1001, 0x00D88000, { 0x0F, 0x55, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA },
	// VEX.NDS.128.66.0F 55 /r VANDNPD xmm1,xmm2,xmm3/m128
	// VEX.NDS.256.66.0F 55 /r VANDNPD ymm1,ymm2,ymm3/m256
	{ "vandnpd", 0x1080, 0x00D88000, { 0x0F, 0x55, 0x00 }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_SIMD, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_ANDNPS[] = {
	// 0F 55 /r ANDNPS xmm1, xmm2/m128 A Valid Valid Bitwise logical AND NOT of xmm2/m128 and xmm1.
	{ NULL, 0x0001, 0x00D88000, { 0x0F, 0x55, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA },
	// VEX.NDS.128.0F 55 /r VANDNPS xmm1,xmm2,xmm3/m128
	// VEX.NDS.256.0F 55 /r VANDNPS ymm1,ymm2,ymm3/m256
	{ "vandnps", 0x0080, 0x00D88000, { 0x0F, 0x55, 0x00 }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_SIMD, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_ARPL[] = {
	// 63 /r ARPL r/m16, r16 A N. E. Valid Adjust RPL of r/m16 to not less than RPL of r16.
	{ NULL, 0x0001, 0x00448000, { 0x63, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_16, _IRA_OPERAND_MODRM_R_16, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_BLENDPD[] = {
	// 66 0F 3A 0D /r ib BLENDPD xmm1, xmm2/m128, imm8 A Valid Valid Select packed DP-FP values from xmm1 and xmm2/m128 from mask specified in imm8 and store the values into xmm1.
	{ NULL, 0x1001, 0x00EC8000, { 0x0F, 0x3A, 0x0D }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_OPERAND_IB, _IRA_NA },
	// VEX.NDS.128.66.0F3A 0D /r ib VBLENDPD xmm1,xmm2,xmm3/m128,imm8
	// VEX.NDS.256.66.0F3A 0D /r ib VBLENDPD ymm1,ymm2,ymm3/m256,imm8
	{ "vblendpd", 0x1080, 0x00EC8000, { 0x0F, 0x3A, 0x0D }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_SIMD, _IRA_OPERAND_IB }
};

struct ira_opcode_desc _ira_opcode_desc_BLENDPS[] = {
	// 66 0F 3A 0C /r ib BLENDPS xmm1, xmm2/m128, imm8 A Valid Valid Select packed single precision floating-point values from xmm1 and xmm2/m128 from mask specified in imm8 and store the values into xmm1.
	{ NULL, 0x1001, 0x00EC8000, { 0x0F, 0x3A, 0x0C }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_OPERAND_IB, _IRA_NA },
	// VEX.NDS.128.66.0F3A 0C /r ib VBLENDPS xmm1,xmm2,xmm3/m128,imm8
	// VEX.NDS.256.66.0F3A 0C /r ib VBLENDPS ymm1,ymm2,ymm3/m256,imm8
	{ "vblendps", 0x1080, 0x00EC8000, { 0x0F, 0x3A, 0x0C }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_SIMD, _IRA_OPERAND_IB }
};

struct ira_opcode_desc _ira_opcode_desc_BLENDVPD[] = {
	// 66 0F 38 15 /r BLENDVPD xmm1, xmm2/m128 , <XMM0> A Valid Valid Select packed DP FP values from xmm1 and xmm2 from mask specified in XMM0 and store the values in xmm1.
	{ NULL, 0x1001, 0x00EC8000, { 0x0F, 0x38, 0x15 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_EXPLICIT_REG( IRA_REG_SIMD, _IRA_REG_XMM0, _IRA_OS_XMMWORD ), _IRA_NA },
	// VEX.NDS.128.66.0F3A 4B /r /is4 VBLENDVPD xmm1, xmm2, xmm3/m128, xmm4
	// VEX.NDS.256.66.0F3A 4B /r /is4 VBLENDVPD ymm1, ymm2, ymm3/m256, ymm4
	{ "vblendvpd", 0x1080, 0x00EC8000, { 0x0F, 0x3A, 0x4B }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_SIMD, _IRA_OPERAND_IS4 }
};

struct ira_opcode_desc _ira_opcode_desc_BLENDVPS[] = {
	// 66 0F 38 14 /r BLENDVPS xmm1, xmm2/m128, <XMM0> A Valid Valid Select packed single precision floating-point values from xmm1 and xmm2/m128 from mask specified in XMM0 and store the values into xmm1.
	{ NULL, 0x1001, 0x00EC8000, { 0x0F, 0x38, 0x14 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_EXPLICIT_REG( IRA_REG_SIMD, _IRA_REG_XMM0, _IRA_OS_XMMWORD ), _IRA_NA },
	// VEX.NDS.128.66.0F3A 4A /r /is4 VBLENDVPS xmm1, xmm2, xmm3/m128, xmm4
	// VEX.NDS.256.66.0F3A 4A /r /is4 VBLENDVPS ymm1, ymm2, ymm3/m256, ymm4
	{ "vblendvps", 0x1080, 0x00EC8000, { 0x0F, 0x3A, 0x4A }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_SIMD, _IRA_OPERAND_IS4 }
};

struct ira_opcode_desc _ira_opcode_desc_VBROADCASTSS[] = {
	// VEX.128.66.0F38 18 /r VBROADCASTSS xmm1, m32
	// VEX.256.66.0F38 18 /r VBROADCASTSS ymm1, m32
	{ NULL, 0x1001, 0x00EC8000, { 0x0F, 0x38, 0x18 }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_OPERAND_MODRM_M_32, _IRA_NA, _IRA_NA },
	// VEX.256.66.0F38 19 /r VBROADCASTSD ymm1, m64
	{ "vbroadcastsd", 0x11A0, 0x00EC8000, { 0x0F, 0x38, 0x19 }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_OPERAND_MODRM_M_64, _IRA_NA, _IRA_NA },
	// VEX.256.66.0F38 1A /r VBROADCASTF128 ymm1, m128
	{ "vbroadcastf128", 0x11A0, 0x00EC8000, { 0x0F, 0x38, 0x1A }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_OPERAND_MODRM_M_128, _IRA_NA, _IRA_NA }
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
	{ NULL, 0x0001, 0x00D80001, { 0x0F, 0xC8, 0x00 }, _IRA_OPERAND_OPCODE_REG( IRA_REG_GPR, _IRA_OS_DWORD ), _IRA_NA, _IRA_NA, _IRA_NA },
	// REX.W + 0F C8+rd BSWAP r64 A Valid N.E. Reverses the byte order of a 64-bit register.
	{ NULL, 0x0009, 0x00980001, { 0x0F, 0xC8, 0x00 }, _IRA_OPERAND_OPCODE_REG( IRA_REG_GPR, _IRA_OS_QWORD ), _IRA_NA, _IRA_NA, _IRA_NA }
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

struct ira_opcode_desc _ira_opcode_desc_CMPPD[] = {
	// 66 0F C2 /r ib CMPPD xmm1, xmm2/m128, imm8 A Valid Valid Compare packed doubleprecision floating-point values in xmm2/m128 and xmm1 using imm8 as comparison predicate.
	{ NULL, 0x1001, 0x00D88000, { 0x0F, 0xC2, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_OPERAND_IB, _IRA_NA },
	// VEX.NDS.128.66.0F C2 /r ib VCMPPD xmm1, xmm2, xmm3/m128, imm8
	// VEX.NDS.256.66.0F C2 /r ib VCMPPD ymm1, ymm2, ymm3/m256, imm8
	{ "vcmppd", 0x1080, 0x00D88000, { 0x0F, 0xC2, 0x0C }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_SIMD, _IRA_OPERAND_IB }
};

struct ira_opcode_desc _ira_opcode_desc_CMPPS[] = {
	// 0F C2 /r ib CMPPS xmm1, xmm2/m128, imm8 A Valid Valid Compare packed singleprecision floating-point values in xmm2/mem and xmm1 using imm8 as comparison predicate.
	{ NULL, 0x0001, 0x00D88000, { 0x0F, 0xC2, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_OPERAND_IB, _IRA_NA },
	// VEX.NDS.128.0F C2 /r ib VCMPPS xmm1, xmm2, xmm3/m128, imm8
	// VEX.NDS.256.0F C2 /r ib VCMPPS ymm1, ymm2, ymm3/m256, imm8
	{ "vcmpps", 0x0080, 0x00D88000, { 0x0F, 0xC2, 0x00 }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_SIMD, _IRA_OPERAND_IB }
};

struct ira_opcode_desc _ira_opcode_desc_CMPS[] = {
	// A6 CMPS m8, m8 A Valid Valid For legacy mode, compare byte at address DS:(E)SI with byte at address ES:(E)DI; For 64-bit mode compare byte at address (R|E)SI to byte at address (R|E)DI. The status flags are set accordingly.
	{ NULL, 0x0001, 0x00C40000, { 0xA6, 0x00, 0x00 },
			_IRA_EXPLICIT_GPS_REG_ADDRESSING( _IRA_REG_SI, _IRA_EOS_BYTE, _IRA_SEG_ENCODE_REGISTER( _IRA_REG_DS, _IRA_SEG_ALLOW_OVERRIDE ) ),
			_IRA_EXPLICIT_GPS_REG_ADDRESSING( _IRA_REG_DI, _IRA_EOS_BYTE, _IRA_SEG_ENCODE_REGISTER( _IRA_REG_ES, _IRA_SEG_DENY_OVERRIDE ) ),
			_IRA_NA, _IRA_NA },
	// A7 CMPS m16, m16 A Valid Valid For legacy mode, compare word at address DS:(E)SI with word at address ES:(E)DI; For 64-bit mode compare word at address (R|E)SI with word at address (R|E)DI. The status flags are set accordingly.
	// A7 CMPS m32, m32 A Valid Valid For legacy mode, compare dword at address DS:(E)SI at dword at address ES:(E)DI; For 64-bit mode compare dword at address (R|E)SI at dword at address (R|E)DI. The status flags are set accordingly.
	// REX.W + A7 CMPS m64, m64 A Valid N.E. Compares quadword at address (R|E)SI with quadword at address (R|E)DI and sets the status flags accordingly.
	{ NULL, 0x0001, 0x00C40000, { 0xA7, 0x00, 0x00 },
			_IRA_EXPLICIT_GPS_REG_ADDRESSING( _IRA_REG_SI, _IRA_EOS_EOSA,_IRA_SEG_ENCODE_REGISTER( _IRA_REG_DS, _IRA_SEG_ALLOW_OVERRIDE ) ),
			_IRA_EXPLICIT_GPS_REG_ADDRESSING( _IRA_REG_DI, _IRA_EOS_EOSA,_IRA_SEG_ENCODE_REGISTER( _IRA_REG_ES, _IRA_SEG_DENY_OVERRIDE ) ),
			_IRA_NA, _IRA_NA }
};

// TODO Jak bedzie czas doimplementowac Pseudo-Op patrz: dokumentacja VAX.
struct ira_opcode_desc _ira_opcode_desc_CMPSD[] = {
	// F2 0F C2 /r ib CMPSD xmm1, xmm2/m64, imm8 A Valid Valid Compare low doubleprecision floating-point value in xmm2/m64 and xmm1 using imm8 as comparison predicate.
	{ NULL, 0x2001, 0x00D88000, { 0x0F, 0xC2, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_64, _IRA_OPERAND_IB, _IRA_NA },
	// VEX.NDS.128.F2.0F C2 /r ib VCMPSD xmm1, xmm2, xmm3/m64, imm8
	{ "vcmpsd", 0x20C0, 0x00D88000, { 0x0F, 0xC2, 0x00 }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_SIMD_64, _IRA_OPERAND_IB }
};

// TODO Jak bedzie czas doimplementowac Pseudo-Op patrz: dokumentacja VAX.
struct ira_opcode_desc _ira_opcode_desc_CMPSS[] = {
	// F3 0F C2 /r ib CMPSS xmm1, xmm2/m32, imm8 A Valid Valid Compare low singleprecision floating-point value in xmm2/m32 and xmm1 using imm8 as comparison predicate.
	{ NULL, 0x4001, 0x00D88000, { 0x0F, 0xC2, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_32, _IRA_OPERAND_IB, _IRA_NA },
	// VEX.NDS.128.F3.0F C2 /r ib VCMPSS xmm1, xmm2, xmm3/m32, imm8
	{ "vcmpss", 0x40C0, 0x00D88000, { 0x0F, 0xC2, 0x00 }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_SIMD_32, _IRA_OPERAND_IB }
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

struct ira_opcode_desc _ira_opcode_desc_COMISD[] = {
	// 66 0F 2F /r COMISD xmm1, xmm2/m64 A Valid Valid Compare low doubleprecision floating-point values in xmm1 and xmm2/mem64 and set the EFLAGS flags accordingly.
	{ NULL, 0x1001, 0x00D88000, { 0x0F, 0x2F, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_64, _IRA_NA, _IRA_NA },
	// VEX.128.66.0F 2F /r VCOMISD xmm1, xmm2/m64
	{ "vcomisd", 0x11C1, 0x00D88000, { 0x0F, 0x2F, 0x00 }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_OPERAND_MODRM_RM_SIMD_64, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_COMISS[] = {
	// 0F 2F /r COMISS xmm1, xmm2/m32 A Valid Valid Compare low singleprecision floating-point values in xmm1 and xmm2/mem32 and set the EFLAGS flags accordingly.
	{ NULL, 0x0001, 0x00D88000, { 0x0F, 0x2F, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_32, _IRA_NA, _IRA_NA },
	// VEX.128.0F 2F /r VCOMISS xmm1, xmm2/m32
	{ "vcomiss", 0x01C1, 0x00D88000, { 0x0F, 0x2F, 0x00 }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_OPERAND_MODRM_RM_SIMD_64, _IRA_NA, _IRA_NA }
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
	{ NULL, 0x4001, 0x00D88000, { 0x0F, 0xE6, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_64, _IRA_NA, _IRA_NA },
	// VEX.128.F3.0F E6 /r VCVTDQ2PD xmm1, xmm2/m64
	{ "vcvtdq2pd", 0x41C1, 0x00D88000, { 0x0F, 0xE6, 0x00 }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_OPERAND_MODRM_RM_SIMD_64, _IRA_NA, _IRA_NA },
	// VEX.256.F3.0F E6 /r VCVTDQ2PD ymm1, xmm2/m128
	{ "vcvtdq2pd", 0x41A1, 0x00D88000, { 0x0F, 0xE6, 0x00 }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_OPERAND_MODRM_RM_SIMD_128, _IRA_NA, _IRA_NA }
};

// XMMWORD
struct ira_opcode_desc _ira_opcode_desc_CVTDQ2PS[] = {
	// 0F 5B /r CVTDQ2PS xmm1, xmm2/m128 A Valid Valid Convert four packed signed doubleword integers from xmm2/m128 to four packed single-precision floatingpoint
	{ NULL, 0x0001, 0x00D88000, { 0x0F, 0x5B, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA },
	// VEX.128.0F 5B /r VCVTDQ2PS xmm1, xmm2/m128
	// VEX.256.0F 5B /r VCVTDQ2PS ymm1, ymm2/m256
	{ "vcvtdq2ps", 0x0181, 0x00D88000, { 0x0F, 0x5B, 0x00 }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_OPERAND_MODRM_RM_SIMD, _IRA_NA, _IRA_NA }
};

// XMMWORD
struct ira_opcode_desc _ira_opcode_desc_CVTPD2DQ[] = {
	// F2 0F E6 CVTPD2DQ xmm1, xmm2/m128 A Valid Valid Convert two packed doubleprecision floating-point values from xmm2/m128 to two packed signed doubleword integers in xmm1.
	{ NULL, 0x2001, 0x00D88000, { 0x0F, 0xE6, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA },
	// VEX.128.F2.0F E6 /r VCVTPD2DQ xmm1, xmm2/m128
	// VEX.256.F2.0F E6 /r VCVTPD2DQ xmm1, ymm2/m256
	{ "vcvtpd2dq", 0x2181, 0x00D88000, { 0x0F, 0xE6, 0x00 }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_OPERAND_MODRM_RM_SIMD, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_CVTPD2PI[] = {
	// 66 0F 2D /r CVTPD2PI mm, xmm/m128 A Valid Valid Convert two packed doubleprecision floating-point values from xmm/m128 to two packed signed doubleword integers in mm.
	{ NULL, 0x1001, 0x00D88000, { 0x0F, 0x2D, 0x00 }, _IRA_OPERAND_MODRM_R_MMX_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_CVTPD2PS[] = {
	// 66 0F 5A /r CVTPD2PS xmm1,xmm2/m128 A Valid Valid Convert two packed doubleprecision floating-point values in xmm2/m128 to two packed single-precision floating-point values in xmm1.
	{ NULL, 0x1001, 0x00D88000, { 0x0F, 0x5A, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA },
	// VEX.128.66.0F 5A /r VCVTPD2PS xmm1, xmm2/m128
	// VEX.256.66.0F 5A /r VCVTPD2PS xmm1, ymm2/m256
	{ "vcvtpd2ps", 0x1181, 0x00D88000, { 0x0F, 0x5A, 0x00 }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_OPERAND_MODRM_RM_SIMD, _IRA_NA, _IRA_NA }
};

// XMMWORD
struct ira_opcode_desc _ira_opcode_desc_CVTPI2PD[] = {
	// 66 0F 2A /r CVTPI2PD xmm, mm/m64* A Valid Valid Convert two packed signed doubleword integers from mm/mem64 to two packed double-precision floatingpoint values in xmm.
	{ NULL, 0x1001, 0x00D88000, { 0x0F, 0x2A, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_MMX, _IRA_NA, _IRA_NA }
};

// XMMWORD
struct ira_opcode_desc _ira_opcode_desc_CVTPI2PS[] = {
	// 0F 2A /r CVTPI2PS xmm, mm/m64 A Valid Valid Convert two signed doubleword integers from mm/m64 to two singleprecision floating-point values in xmm.
	{ NULL, 0x0001, 0x00D88000, { 0x0F, 0x2A, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_MMX, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_CVTPS2DQ[] = {
	// 66 0F 5B /r CVTPS2DQ xmm1, xmm2/m128 A Valid Valid Convert four packed singleprecision floating-point values from xmm2/m128 to four packed signed doubleword integers in xmm1.
	{ NULL, 0x1001, 0x00D88000, { 0x0F, 0x5B, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA },
	// VEX.128.66.0F 5B /r VCVTPS2DQ xmm1, xmm2/m128
	// VEX.256.66.0F 5B /r VCVTPS2DQ ymm1, ymm2/m256
	{ "vcvtps2dq", 0x1180, 0x00D88000, { 0x0F, 0x5B, 0x00 }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_OPERAND_MODRM_RM_SIMD, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_CVTPS2PD[] = {
	// 0F 5A /r CVTPS2PD xmm1, xmm2/m64 A Valid Valid Convert two packed singleprecision floating-point values in xmm2/m64 to two packed double-precision floating-point values in xmm1.
	{ NULL, 0x0001, 0x00D88000, { 0x0F, 0x5A, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_64, _IRA_NA, _IRA_NA },
	// VEX.128.0F 5A /r VCVTPS2PD xmm1, xmm2/m64
	// VEX.256.0F 5A /r VCVTPS2PD ymm1, xmm2/m128
	{ "vcvtps2pd", 0x0180, 0x00D88000, { 0x0F, 0x5A, 0x00 }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_OPERAND_MODRM_RM_SIMD, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_CVTPS2PI[] = {
	// 0F 2D /r CVTPS2PI mm, xmm/m64 A Valid Valid Convert two packed singleprecision floating-point values from xmm/m64 to two packed signed doubleword integers in mm.
	{ NULL, 0x0001, 0x00D88000, { 0x0F, 0x2D, 0x00 }, _IRA_OPERAND_MODRM_R_MMX_W, _IRA_OPERAND_MODRM_RM_XMM_64, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_CVTSD2SI[] = {
	// F2 0F 2D /r CVTSD2SI r32, xmm/m64 A Valid Valid Convert one doubleprecision floating-point value from xmm/m64 to one signed doubleword integer r32.
	{ NULL, 0x2001, 0x03D88000, { 0x0F, 0x2D, 0x00 }, _IRA_OPERAND_MODRM_R_32_W, _IRA_OPERAND_MODRM_RM_XMM_64, _IRA_NA, _IRA_NA },
	// F2 REX.W 0F 2D /r CVTSD2SI r64, xmm/m64 A Valid N.E. Convert one doubleprecision floating-point value from xmm/m64 to one signed quadword integer sign-extended into r64.
	{ NULL, 0x2009, 0x04988000, { 0x0F, 0x2D, 0x00 }, _IRA_OPERAND_MODRM_R_64_W, _IRA_OPERAND_MODRM_RM_XMM_64, _IRA_NA, _IRA_NA },
	// VEX.128.F2.0F.W0 2D /r VCVTSD2SI r32, xmm1/m64
	{ "vcvtsd2si", 0x21D0, 0x03D88000, { 0x0F, 0x2D, 0x00 }, _IRA_OPERAND_MODRM_R_32_W, _IRA_OPERAND_MODRM_RM_SIMD_64, _IRA_NA, _IRA_NA },
	// VEX.128.F2.0F.W1 2D /r VCVTSD2SI r64, xmm1/m64
	{ "vcvtsd2si", 0x21C8, 0x04988000, { 0x0F, 0x2D, 0x00 }, _IRA_OPERAND_MODRM_R_64_W, _IRA_OPERAND_MODRM_RM_SIMD_64, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_CVTSD2SS[] = {
	// F2 0F 5A /r CVTSD2SS xmm1, xmm2/m64 A Valid Valid Convert one doubleprecision floating-point value in xmm2/m64 to one single-precision floatingpoint value in xmm1.
	{ NULL, 0x2001, 0x00D88000, { 0x0F, 0x5A, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_64, _IRA_NA, _IRA_NA },
	// VEX.NDS.128.F2.0F 5A /r VCVTSD2SS xmm1,xmm2,xmm3/m64
	{ "vcvtsd2ss", 0x20C0, 0x00D88000, { 0x0F, 0x5A, 0x00 }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_SIMD_64, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_CVTSI2SD[] = {
	// F2 0F 2A /r CVTSI2SD xmm, r/m32 A Valid Valid Convert one signed doubleword integer from r/m32 to one doubleprecision floating-point value in xmm.
	{ NULL, 0x2001, 0x03D88000, { 0x0F, 0x2A, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_32, _IRA_NA, _IRA_NA },
	// F2 REX.W 0F 2A /r CVTSI2SD xmm, r/m64 A Valid N.E. Convert one signed quadword integer from r/m64 to one doubleprecision floating-point value in xmm.
	{ NULL, 0x2009, 0x04988000, { 0x0F, 0x2A, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_64, _IRA_NA, _IRA_NA },
	// VEX.NDS.128.F2.0F.W0 2A /r VCVTSI2SD xmm1, xmm2, r/m32
	{ "vcvtsi2sd", 0x20D0, 0x03D88000, { 0x0F, 0x2A, 0x00 }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_32, _IRA_NA },
	// VEX.NDS.128.F2.0F.W1 2A /r VCVTSI2SD xmm1, xmm2, r/m64
	{ "vcvtsi2sd", 0x20C8, 0x04988000, { 0x0F, 0x2A, 0x00 }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_64, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_CVTSI2SS[] = {
	// F3 0F 2A /r CVTSI2SS xmm, r/m32 A Valid Valid Convert one signed doubleword integer from r/m32 to one singleprecision floating-point value in xmm.
	{ NULL, 0x4001, 0x03D88000, { 0x0F, 0x2A, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_32, _IRA_NA, _IRA_NA },
	// F3 REX.W 0F 2A /r CVTSI2SS xmm, r/m64 A Valid N.E. Convert one signed quadword integer from r/m64 to one singleprecision floating-point value in xmm.
	{ NULL, 0x4009, 0x04988000, { 0x0F, 0x2A, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_64, _IRA_NA, _IRA_NA },
	// VEX.NDS.128.F3.0F.W0 2A /r VCVTSI2SS xmm1, xmm2, r/m32
	{ "vcvtsi2ss", 0x40D0, 0x03D88000, { 0x0F, 0x2A, 0x00 }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_32, _IRA_NA },
	// VEX.NDS.128.F3.0F.W1 2A /r VCVTSI2SS xmm1, xmm2, r/m64
	{ "vcvtsi2ss", 0x40C8, 0x04988000, { 0x0F, 0x2A, 0x00 }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_64, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_CVTSS2SD[] = {
	// F3 0F 5A /r CVTSS2SD xmm1, xmm2/m32 A Valid Valid Convert one single-precision floating-point value in xmm2/m32 to one doubleprecision floating-point value in xmm1.
	{ NULL, 0x4001, 0x00D88000, { 0x0F, 0x5A, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_32, _IRA_NA, _IRA_NA },
	// VEX.NDS.128.F3.0F 5A /r VCVTSS2SD xmm1, xmm2, xmm3/m32
	{ "vcvtss2sd", 0x40C0, 0x00D88000, { 0x0F, 0x5A, 0x00 }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_32, _IRA_NA },
};

struct ira_opcode_desc _ira_opcode_desc_CVTSS2SI[] = {
	// F3 0F 2D /r CVTSS2SI r32, xmm/m32 A Valid Valid Convert one single-precision floating-point value from xmm/m32 to one signed doubleword integer in r32.
	{ NULL, 0x4001, 0x03D88000, { 0x0F, 0x2D, 0x00 }, _IRA_OPERAND_MODRM_R_32_W, _IRA_OPERAND_MODRM_RM_XMM_32, _IRA_NA, _IRA_NA },
	// F3 REX.W 0F 2D /r CVTSS2SI r64, xmm/m32 A Valid N.E. Convert one single-precision floating-point value from xmm/m32 to one signed quadword integer in r64.
	{ NULL, 0x4009, 0x04988000, { 0x0F, 0x2D, 0x00 }, _IRA_OPERAND_MODRM_R_64_W, _IRA_OPERAND_MODRM_RM_XMM_32, _IRA_NA, _IRA_NA },
	// VEX.128.F3.0F.W0 2D /r VCVTSS2SI r32, xmm1/m32
	{ "vcvtss2si", 0x41D0, 0x03D88000, { 0x0F, 0x2D, 0x00 }, _IRA_OPERAND_MODRM_R_32_W, _IRA_OPERAND_MODRM_RM_SIMD_32, _IRA_NA, _IRA_NA },
	// VEX.128.F3.0F.W1 2D /r VCVTSS2SI r64, xmm1/m32
	{ "vcvtss2si", 0x41C8, 0x04988000, { 0x0F, 0x2D, 0x00 }, _IRA_OPERAND_MODRM_R_64_W, _IRA_OPERAND_MODRM_RM_SIMD_32, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_CVTTPD2DQ[] = {
	// 66 0F E6 CVTTPD2DQ xmm1, xmm2/m128 A Valid Valid Convert two packed doubleprecision floating-point values from xmm2/m128 to two packed signed doubleword integers in xmm1 using truncation.
	{ NULL, 0x1001, 0x00D88000, { 0x0F, 0xE6, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA },
	// VEX.128.66.0F E6 /r VCVTTPD2DQ xmm1, xmm2/m128
	// VEX.256.66.0F E6 /r VCVTTPD2DQ xmm1, ymm2/m256
	{ "vcvttpd2dq", 0x1180, 0x00D88000, { 0x0F, 0xE6, 0x00 }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_OPERAND_MODRM_RM_SIMD, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_CVTTPD2PI[] = {
	// 66 0F 2C /r CVTTPD2PI mm, xmm/m128 A Valid Valid Convert two packer doubleprecision floating-point values from xmm/m128 to two packed signed doubleword integers in mm using truncation.
	{ NULL, 0x1001, 0x00D88000, { 0x0F, 0x2C, 0x00 }, _IRA_OPERAND_MODRM_R_MMX_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_CVTTPS2DQ[] = {
	// F3 0F 5B /r CVTTPS2DQ xmm1, xmm2/m128 A Valid Valid Convert four singleprecision floating-point values from xmm2/m128 to four signed doubleword integers in xmm1 using truncation.
	{ NULL, 0x4001, 0x00D88000, { 0x0F, 0x5B, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA },
	// VEX.128.F3.0F 5B /r VCVTTPS2DQ xmm1, xmm2/m128
	// VEX.256.F3.0F 5B /r VCVTTPS2DQ ymm1, ymm2/m256
	{ "vcvttps2dq", 0x4180, 0x00D88000, { 0x0F, 0x5B, 0x00 }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_OPERAND_MODRM_RM_SIMD, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_CVTTPS2PI[] = {
	// 0F 2C /r CVTTPS2PI mm, xmm/m64 A Valid Valid Convert two singleprecision floating-point values from xmm/m64 to two signed doubleword signed integers in mm using truncation.
	{ NULL, 0x0001, 0x00D88000, { 0x0F, 0x2C, 0x00 }, _IRA_OPERAND_MODRM_R_MMX_W, _IRA_OPERAND_MODRM_RM_XMM_64, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_CVTTSD2SI[] = {
	// F2 0F 2C /r CVTTSD2SI r32, xmm/m64 A Valid Valid Convert one doubleprecision floating-point value from xmm/m64 to one signed doubleword integer in r32 using truncation.
	{ NULL, 0x2001, 0x03D88000, { 0x0F, 0x2C, 0x00 }, _IRA_OPERAND_MODRM_R_32_W, _IRA_OPERAND_MODRM_RM_XMM_64, _IRA_NA, _IRA_NA },
	// F2 REX.W 0F 2C /r CVTTSD2SI r64, xmm/m64 A Valid N.E. Convert one double precision floating-point value from xmm/m64 to one signedquad wordinteger in r64 using truncation.
	{ NULL, 0x2009, 0x04988000, { 0x0F, 0x2C, 0x00 }, _IRA_OPERAND_MODRM_R_64_W, _IRA_OPERAND_MODRM_RM_XMM_64, _IRA_NA, _IRA_NA },
	// VEX.128.F2.0F.W0 2C /r VCVTTSD2SI r32, xmm1/m64
	{ "vcvttsd2si", 0x21D0, 0x03D88000, { 0x0F, 0x2C, 0x00 }, _IRA_OPERAND_MODRM_R_32_W, _IRA_OPERAND_MODRM_RM_SIMD_64, _IRA_NA, _IRA_NA },
	// VEX.128.F2.0F.W1 2C /r VCVTTSD2SI r64, xmm1/m64
	{ "vcvttsd2si", 0x21C8, 0x04988000, { 0x0F, 0x2C, 0x00 }, _IRA_OPERAND_MODRM_R_64_W, _IRA_OPERAND_MODRM_RM_SIMD_64, _IRA_NA, _IRA_NA }
};

// MMWORD
struct ira_opcode_desc _ira_opcode_desc_CVTTSS2SI[] = {
	// F3 0F 2C /r CVTTSS2SI r32, xmm/m32 A Valid Valid Convert one single-precision floating-point value from xmm/m32 to one signed doubleword integer in r32 using truncation.
	{ NULL, 0x4001, 0x03D88000, { 0x0F, 0x2C, 0x00 }, _IRA_OPERAND_MODRM_R_32_W, _IRA_OPERAND_MODRM_RM_XMM_32, _IRA_NA, _IRA_NA },
	// F3 REX.W 0F 2C /r CVTTSS2SI r64, xmm/m32 A Valid N.E. Convert one single-precision floating-point value from xmm/m32 to one signed quadword integer in
	{ NULL, 0x4009, 0x04988000, { 0x0F, 0x2C, 0x00 }, _IRA_OPERAND_MODRM_R_64_W, _IRA_OPERAND_MODRM_RM_XMM_32, _IRA_NA, _IRA_NA },
	// VEX.128.F3.0F.W0 2C /r VCVTTSS2SI r32, xmm1/m32
	{ "vcvttss2si", 0x41C0, 0x03D88000, { 0x0F, 0x2C, 0x00 }, _IRA_OPERAND_MODRM_R_32_W, _IRA_OPERAND_MODRM_RM_SIMD_32, _IRA_NA, _IRA_NA },
	// VEX.128.F3.0F.W1 2C /r VCVTTSS2SI r64, xmm1/m32
	{ "vcvttss2si", 0x41D0, 0x04988000, { 0x0F, 0x2C, 0x00 }, _IRA_OPERAND_MODRM_R_64_W, _IRA_OPERAND_MODRM_RM_SIMD_32, _IRA_NA, _IRA_NA }
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
	{ NULL, 0x0001, 0x00440001, { 0x48, 0x00, 0x00 }, _IRA_OPERAND_OPCODE_REG( IRA_REG_GPR, _IRA_OS_EOSA ), _IRA_NA, _IRA_NA, _IRA_NA }
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
	{ NULL, 0x1001, 0x00D88000, { 0x0F, 0x5E, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA },
	// VEX.NDS.128.66.0F 5E /r VDIVPD xmm1, xmm2, xmm3/m128
	// VEX.NDS.256.66.0F 5E /r VDIVPD ymm1, ymm2, ymm3/m256
	{ "vdivpd", 0x1080, 0x00D88000, { 0x0F, 0x5E, 0x00 }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_SIMD, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_DIVPS[] = {
	// 0F 5E /r DIVPS xmm1, xmm2/m128 A Valid Valid Divide packed singleprecision floating-point values in xmm1 by packed single-precision floatingpoint values xmm2/m128.
	{ NULL, 0x0001, 0x00D88000, { 0x0F, 0x5E, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA },
	// VEX.NDS.128.0F 5E /r VDIVPS xmm1, xmm2, xmm3/m128
	// VEX.NDS.256.0F 5E /r VDIVPS ymm1, ymm2, ymm3/m256
	{ "vdivps", 0x0080, 0x00D88000, { 0x0F, 0x5E, 0x00 }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_SIMD, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_DIVSD[] = {
	// F2 0F 5E /r DIVSD xmm1, xmm2/m64 A Valid Valid Divide low double-precision floating-point value n xmm1 by low double-precision floating-point value in xmm2/mem64.
	{ NULL, 0x2001, 0x00D88000, { 0x0F, 0x5E, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_64, _IRA_NA, _IRA_NA },
	// VEX.NDS.128.F2.0F 5E /r VDIVSD xmm1, xmm2, xmm3/m64
	{ "vdivsd", 0x20C0, 0x00D88000, { 0x0F, 0x5E, 0x00 }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_SIMD_64, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_DIVSS[] = {
	// F3 0F 5E /r DIVSS xmm1, xmm2/m32 A Valid Valid Divide low single-precision floating-point value in xmm1 by low singleprecision floating-point value in xmm2/m32.
	{ NULL, 0x4001, 0x00D88000, { 0x0F, 0x5E, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_32, _IRA_NA, _IRA_NA },
	// VEX.NDS.128.F3.0F 5E /r VDIVSS xmm1, xmm2, xmm3/m32
	{ "vdivss", 0x40C0, 0x00D88000, { 0x0F, 0x5E, 0x00 }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_SIMD_32, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_DPPD[] = {
	// 66 0F 3A 41 /r ib DPPD xmm1, xmm2/m128, imm8 A Valid Valid Selectively multiply packed DP floating-point values from xmm1 with packed DP floating-point values from xmm2, add and selectively store the packed DP floating-point values to xmm1.
	{ NULL, 0x1001, 0x00EC8000, { 0x0F, 0x3A, 0x41 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_OPERAND_IB, _IRA_NA },
	// VEX.NDS.128.66.0F3A 41 /r ib VDPPD xmm1,xmm2,xmm3/m128,imm8
	{ "vdppd", 0x10C0, 0x00EC8000, { 0x0F, 0x3A, 0x41 }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_SIMD_128, _IRA_OPERAND_IB }
};

struct ira_opcode_desc _ira_opcode_desc_DPPS[] = {
	// 66 0F 3A 40 /r ib DPPS xmm1, xmm2/m128, imm8 A Valid Valid Selectively multiply packed SP floating-point values from xmm1 with packed SP floating-point values from xmm2, add and selectively store the packed SP floating-point values or zero values to xmm1.
	{ NULL, 0x1001, 0x00EC8000, { 0x0F, 0x3A, 0x40 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_OPERAND_IB, _IRA_NA },
	// VEX.NDS.128.66.0F3A 40 /r ib VDPPS xmm1,xmm2,xmm3/m128,imm8
	// VEX.NDS.256.66.0F3A 40 /r ib VDPPS ymm1,ymm2,ymm3/m256,imm8
	{ "vdpps", 0x1080, 0x00EC8000, { 0x0F, 0x3A, 0x40 }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_SIMD, _IRA_OPERAND_IB }
};

struct ira_opcode_desc _ira_opcode_desc_VEXTRACTF128[] = {
	// VEX.256.66.0F3A 19 /r ib VEXTRACTF128 xmm1/m128,ymm2,imm8
	{ "vextractf128", 0x11A0, 0x00EC8000, { 0x0F, 0x3A, 0x19 }, _IRA_OPERAND_MODRM_RM_XMM_128_W, _IRA_OPERAND_MODRM_R_SIMD, _IRA_OPERAND_IB, _IRA_NA }
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
	// 66 0F 3A 17 /r ib EXTRACTPS reg/m32, xmm2, imm8 A Valid Valid Extract a single-precision floating-point value from xmm2 at the source offset specified by imm8 and store the result to reg or m32. The upper 32 bits of r64 is zeroed if reg is r64.,
	{ NULL, 0x1001, 0x00EC8000, { 0x0F, 0x3A, 0x17 }, _IRA_OPERAND_MODRM_RM_32_W, _IRA_OPERAND_MODRM_R_XMM, _IRA_OPERAND_IB, _IRA_NA },
	// VEX.128.66.0F3A 17 /r ib VEXTRACTPS r/m32, xmm1, imm8
	{ "vextractps", 0x11C0, 0x00EC8000, { 0x0F, 0x3A, 0x17 }, _IRA_OPERAND_MODRM_RM_32_W, _IRA_OPERAND_MODRM_R_XMM, _IRA_OPERAND_IB, _IRA_NA }
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
	{ NULL, 0x1001, 0x00D88000, { 0x0F, 0x7C, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA },
	// VEX.NDS.128.66.0F 7C /r VHADDPD xmm1,xmm2,xmm3/m128
	// VEX.NDS.256.66.0F 7C /r VHADDPD ymm1,ymm2,ymm3/m256
	{ "vhaddpd", 0x1080, 0x00D88000, { 0x0F, 0x7C, 0x00 }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_SIMD, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_HADDPS[] = {
	// F2 0F 7C /r HADDPS xmm1, xmm2/m128 A Valid Valid Horizontal add packed single-precision floatingpoint values from xmm2/m128 to xmm1.
	{ NULL, 0x2001, 0x00D88000, { 0x0F, 0x7C, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA },
	// VEX.NDS.128.F2.0F 7C /r VHADDPS xmm1,xmm2,xmm3/m128
	// VEX.NDS.256.F2.0F 7C /r VHADDPS ymm1,ymm2,ymm3/m256
	{ "vhaddps", 0x2080, 0x00D88000, { 0x0F, 0x7C, 0x00 }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_SIMD, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_HLT[] = {
	// F4 HLT A Valid Valid Halt
	{ NULL, 0x0001, 0x00C40000, { 0xF4, 0x00, 0x00 }, _IRA_NA, _IRA_NA, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_HSUBPD[] = {
	// 66 0F 7D /r HSUBPD xmm1, xmm2/m128A Valid Valid Horizontal subtract packed double-precision floating pointvalues from xmm2/m128 to xmm1.
	{ NULL, 0x1001, 0x00D88000, { 0x0F, 0x7D, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA },
	// VEX.NDS.128.66.0F 7D /r VHSUBPD xmm1,xmm2,xmm3/m128
	// VEX.NDS.256.66.0F 7D /r VHSUBPD ymm1,ymm2,ymm3/m256
	{ "vhsubpd", 0x1080, 0x00D88000, { 0x0F, 0x7D, 0x00 }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_SIMD, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_HSUBPS[] = {
	// F2 0F 7D /r HSUBPS xmm1, xmm2/m128 A Valid Valid Horizontal subtract packedsingle-precision floatingpoint values from xmm2/m128 to xmm1.
	{ NULL, 0x2001, 0x00D88000, { 0x0F, 0x7D, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA },
	// VEX.NDS.128.F2.0F 7D /r VHSUBPS xmm1,xmm2,xmm3/m128
	// VEX.NDS.256.F2.0F 7D /r VHSUBPS ymm1,ymm2,ymm3/m256
	{ "vhsubps", 0x2080, 0x00D88000, { 0x0F, 0x7D, 0x00 }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_SIMD, _IRA_NA }
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
	{ NULL, 0x0001, 0x00440001, { 0x40, 0x00, 0x00 }, _IRA_OPERAND_OPCODE_REG( IRA_REG_GPR, _IRA_OS_EOSA ), _IRA_NA, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_INS[] = {
	// 6C INS m8, DX A Valid Valid Input byte from I/O port specified in DX into memory location specified in ES:(E)DI or RDI.*
	{ NULL, 0x0001, 0x07C40000, { 0x6C, 0x00, 0x00 },
			_IRA_EXPLICIT_GPS_REG_ADDRESSING( _IRA_REG_DI, _IRA_EOS_BYTE, _IRA_SEG_ENCODE_REGISTER( _IRA_REG_ES, _IRA_SEG_DENY_OVERRIDE ) ),
			_IRA_EXPLICIT_REG( IRA_REG_GPR, _IRA_REG_DX, _IRA_OS_WORD ), _IRA_NA, _IRA_NA },
	// 6D INS m16, DX A Valid Valid Input word from I/O port specified in DX into memory location specified in ES:(E)DI or RDI.1
	{ NULL, 0x0001, 0x01C40000, { 0x6D, 0x00, 0x00 },
			_IRA_EXPLICIT_GPS_REG_ADDRESSING( _IRA_REG_DI, _IRA_EOS_WORD, _IRA_SEG_ENCODE_REGISTER( _IRA_REG_ES, _IRA_SEG_DENY_OVERRIDE ) ),
			_IRA_EXPLICIT_REG( IRA_REG_GPR, _IRA_REG_DX, _IRA_OS_WORD ), _IRA_NA, _IRA_NA },
	// 6D INS m32, DX A Valid Valid Input doubleword from I/O port specified in DX into memory location specified in ES:(E)DI or RDI.1
	{ NULL, 0x0001, 0x06C40000, { 0x6D, 0x00, 0x00 },
			_IRA_EXPLICIT_GPS_REG_ADDRESSING( _IRA_REG_DI, _IRA_EOS_DWORD, _IRA_SEG_ENCODE_REGISTER( _IRA_REG_ES, _IRA_SEG_DENY_OVERRIDE ) ),
			_IRA_EXPLICIT_REG( IRA_REG_GPR, _IRA_REG_DX, _IRA_OS_WORD ), _IRA_NA, _IRA_NA }
	// TODO: W przypadku assemblera trzeba to bedzie obsluzyc.
	// 6C INSB A Valid Valid Input byte from I/O port specified in DX into memory location specified with ES:(E)DI or RDI.1
	// 6D INSW A Valid Valid Input word from I/O portspecified in DX into memory location specified in ES:(E)DI or RDI.1
	// 6D INSD A Valid Valid Input doubleword from I/O port specified in DX into memory location specified in ES:(E)DI or RDI.1
};

struct ira_opcode_desc _ira_opcode_desc_INSERTPS[] = {
	// 66 0F 3A 21 /r ib INSERTPS xmm1, xmm2/m32, imm8 A Valid Valid Insert a single precision floating-point value selected by imm8 from xmm2/m32 into xmm1 at the specified destination element specified by imm8 and zero out destination elements in xmm1 as indicated in imm8.
	{ NULL, 0x1001, 0x00EC8000, { 0x0F, 0x3A, 0x021 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_32, _IRA_OPERAND_IB, _IRA_NA },
	// VEX.NDS.128.66.0F3A 21 /r ib VINSERTPS xmm1,xmm2,xmm3/m32,imm8
	{ "vinsertps", 0x10C0, 0x00EC8000, { 0x0F, 0x3A, 0x21 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_XMM_32, _IRA_OPERAND_IB }
};

struct ira_opcode_desc _ira_opcode_desc_VINSERTF128[] = {
	// VEX.NDS.256.66.0F3A 18 /r ib VINSERTF128 ymm1,ymm2,xmm3/m128,imm8
	{ "vinsertf128", 0x10A0, 0x00EC8000, { 0x0F, 0x3A, 0x18 }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_OPERAND_IB }
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

struct ira_opcode_desc _ira_opcode_desc_INVPCID[] = {
	// 66 0F 38 82 /r INVPCID r32, m128 RM NE/V INVPCID Invalidates entries in the TLBs and paging-structure caches based on invalidation type in r32 and descriptor in m128.
	{ NULL, 0x1001, 0x806C8000, { 0x0F, 0x38, 0x82 }, _IRA_OPERAND_MODRM_R_32, _IRA_OPERAND_RM( IRA_NO_REG, _IRA_EOS_UNDEFINED, _IRA_EOS_OWORD, _IRA_RMF_M ), _IRA_NA, _IRA_NA },
	// 66 0F 38 82 /r INVPCID r64, m128 RM V/NE INVPCID Invalidates entries in the TLBs and paging-structure caches based on invalidation type in r64 and descriptor in m128.
	{ NULL, 0x1001, 0x80AC8000, { 0x0F, 0x38, 0x82 }, _IRA_OPERAND_MODRM_R_64, _IRA_OPERAND_RM( IRA_NO_REG, _IRA_EOS_UNDEFINED, _IRA_EOS_OWORD, _IRA_RMF_M ), _IRA_NA, _IRA_NA }
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
	{ NULL, 0x2001, 0x00D88000, { 0x0F, 0xF0, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_M_UNDEF, _IRA_NA, _IRA_NA },
	// VEX.128.F2.0F F0 /r VLDDQU xmm1, m128
	// VEX.256.F2.0F F0 /r VLDDQU ymm1, m256
	{ "vlddqu", 0x2180, 0x80D88000, { 0x0F, 0xF0, 0x00 }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_OPERAND_RM( IRA_NO_REG, _IRA_EOS_UNDEFINED, _IRA_EOS_EOSA, _IRA_RMF_M ), _IRA_NA, _IRA_NA },
};

struct ira_opcode_desc _ira_opcode_desc_VLDMXCSR[] = {
	// VEX.128.0F AE /2 VLDMXCSR m32
	{ NULL, 0x01C0, 0x80D99000, { 0x0F, 0xAE, 0x00 }, _IRA_OPERAND_RM( IRA_NO_REG, _IRA_EOS_UNDEFINED, _IRA_EOS_DWORD, _IRA_RMF_M ), _IRA_NA, _IRA_NA, _IRA_NA },
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
			_IRA_EXPLICIT_GPS_REG_ADDRESSING( _IRA_REG_SI, _IRA_EOS_BYTE, _IRA_SEG_ENCODE_REGISTER( _IRA_REG_DS, _IRA_SEG_ALLOW_OVERRIDE ) ),
			_IRA_NA, _IRA_NA, _IRA_NA },
	// AD LODS m16 A Valid Valid For legacy mode, Load word at address DS:(E)SI into AX. For 64-bit mode load word at address (R)SI into AX.
	// AD  LODS m32 A Valid Valid For legacy mode, Load dword at address DS:(E)SI into EAX. For 64-bit mode load dword at address (R)SI into EAX.
	// REX.W + AD LODS m64 A Valid N.E. Load qword at address (R)SI into RAX.
	{ NULL, 0x0001, 0x00C48000, { 0xAD, 0x00, 0x00 },
			_IRA_EXPLICIT_GPS_REG_ADDRESSING( _IRA_REG_SI, _IRA_EOS_EOSA,_IRA_SEG_ENCODE_REGISTER( _IRA_REG_DS, _IRA_SEG_ALLOW_OVERRIDE ) ),
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
	{ NULL, 0x1001, 0x00D88000, { 0x0F, 0xF7, 0x00 }, _IRA_OPERAND_R( IRA_REG_SIMD, _IRA_OS_OWORD ), _IRA_OPERAND_RM( IRA_REG_SIMD, _IRA_EOS_OWORD, _IRA_EOS_UNDEFINED, _IRA_RMF_R ), _IRA_NA, _IRA_NA },
	// VEX.128.66.0F F7 /r VMASKMOVDQU xmm1,xmm2
	{ "vmaskmovdqu", 0x11C0, 0x00D88000, { 0x0F, 0xF7, 0x00 }, _IRA_OPERAND_R( IRA_REG_SIMD, _IRA_OS_XMMWORD ), _IRA_OPERAND_RM( IRA_REG_SIMD, _IRA_OS_XMMWORD, _IRA_EOS_UNDEFINED, _IRA_RMF_R ), _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_VMASKMOVP[] = {
	// VEX.NDS.128.66.0F38 2C /r VMASKMOVPS xmm1,xmm2,m128
	// VEX.NDS.256.66.0F38 2C /r VMASKMOVPS ymm1,ymm2,m256
	{ "vmaskmovps", 0x1080, 0x00EC8000, { 0x0F, 0x38, 0x2C }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_M_SIMD, _IRA_NA },
	// VEX.NDS.128.66.0F38 2D /r VMASKMOVPD xmm1,xmm2,m128
	// VEX.NDS.256.66.0F38 2D /r VMASKMOVPD ymm1,ymm2,m256
	{ "vmaskmovpd", 0x1080, 0x00EC8000, { 0x0F, 0x38, 0x2D }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_M_SIMD, _IRA_NA },
	// VEX.NDS.128.66.0F38 2E /r VMASKMOVPS m128,xmm1,xmm2
	// VEX.NDS.256.66.0F38 2E /r VMASKMOVPS m256,ymm1,ymm2
	{ "vmaskmovps", 0x1080, 0x00EC8000, { 0x0F, 0x38, 0x2E }, _IRA_OPERAND_MODRM_M_SIMD_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_R_SIMD, _IRA_NA },
	// VEX.NDS.128.66.0F38 2F /r VMASKMOVPD m128,xmm1,xmm2
	// VEX.NDS.256.66.0F38 2F /r VMASKMOVPD m256,ymm1,ymm2
	{ "vmaskmovpd", 0x1080, 0x00EC8000, { 0x0F, 0x38, 0x2F }, _IRA_OPERAND_MODRM_M_SIMD_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_R_SIMD, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_MASKMOVQ[] = {
	// 0F F7 /r MASKMOVQ mm1, mm2 A Valid Valid Selectively write bytes from mm1 to memory location using the byte mask in mm2. The default memory location is specified by DS:EDI/RDI.
	{ NULL, 0x0001, 0x00D88000, { 0x0F, 0xF7, 0x00 }, _IRA_OPERAND_R( IRA_REG_SIMD, _IRA_OS_MMWORD ), _IRA_OPERAND_RM( IRA_REG_SIMD, _IRA_OS_MMWORD, _IRA_EOS_UNDEFINED, _IRA_RMF_R ), _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_MAXPD[] = {
	// 66 0F 5F /r MAXPD xmm1, xmm2/m128 A Valid Valid Return the maximum double-precision floatingpoint values between xmm2/m128 and xmm1.
	{ NULL, 0x1001, 0x00D88000, { 0x0F, 0x5F, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA },
	// VEX.NDS.128.66.0F 5F /r VMAXPD xmm1,xmm2,xmm3/m128
	// VEX.NDS.256.66.0F 5F /r VMAXPD ymm1,ymm2,ymm3/m256
	{ "vmaxpd", 0x1080, 0x00D88000, { 0x0F, 0x5F, 0x00 }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_SIMD, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_MAXPS[] = {
	// 0F 5F /r MAXPS xmm1, xmm2/m128 A Valid Valid Return the maximum singleprecision floating-point values between xmm2/m128 and xmm1.
	{ NULL, 0x0001, 0x00D88000, { 0x0F, 0x5F, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA },
	// VEX.NDS.128.0F 5F /r VMAXPS xmm1,xmm2,xmm3/m128
	// VEX.NDS.256.0F 5F /r VMAXPS ymm1,ymm2,ymm3/m256
	{ "vmaxps", 0x0080, 0x00D88000, { 0x0F, 0x5F, 0x00 }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_SIMD, _IRA_NA }
};

// TODO: Zastanowic sie na dwiloscia operandu podawanego dla trubow _IRA_OPERAND_MODRM_R_, czy ma ona sens? Najprwdopodobniejnie ma to zadnego znaczenia przynajmniej z punktu widzenia assemblera, no moze tylko dla GPR tu ma.

struct ira_opcode_desc _ira_opcode_desc_MAXSD[] = {
	// F2 0F 5F /r MAXSD xmm1, xmm2/m64 A Valid Valid Return the maximum scalardouble-precision floatingpoint value between xmm2/mem64 and xmm1.
	{ NULL, 0x2001, 0x00D88000, { 0x0F, 0x5F, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_64, _IRA_NA, _IRA_NA },
	// VEX.NDS.128.F2.0F 5F /r VMAXSD xmm1,xmm2,xmm3/m64
	{ "vmaxsd", 0x20C0, 0x00D88000, { 0x0F, 0x5F, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_XMM_64, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_MAXSS[] = {
	// F3 0F 5F /r MAXSS xmm1, xmm2/m32 A Valid Valid Return the maximum scalarsingle-precision floatingpoint value between xmm2/mem32 and xmm1.
	{ NULL, 0x4001, 0x00D88000, { 0x0F, 0x5F, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_32, _IRA_NA, _IRA_NA },
	// VEX.NDS.128.F3.0F 5F /r VMAXSS xmm1, xmm2, xmm3/m32
	{ "vmaxss", 0x40C0, 0x00D88000, { 0x0F, 0x5F, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_XMM_32, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_MFENCE[] = {
	// MFENCE 0F AE /6  A Valid Valid Serializes load and store operations.
	{ NULL, 0x0001, 0x00EC0000, { 0x0F, 0xAE, 0xF0 }, _IRA_NA, _IRA_NA, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_MINPD[] = {
	// 66 0F 5D /r MINPD xmm1, xmm2/m128 A Valid Valid Return the minimum doubleprecision floating-point values between xmm2/m128 and xmm1.
	{ NULL, 0x1001, 0x00D88000, { 0x0F, 0x5D, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA },
	// VEX.NDS.128.66.0F 5D /r VMINPD xmm1,xmm2,xmm3/m128
	// VEX.NDS.256.66.0F 5D /r VMINPD ymm1,ymm2,ymm3/m256
	{ "vminpd", 0x1080, 0x00D88000, { 0x0F, 0x5D, 0x00 }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_SIMD, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_MINPS[] = {
	// 0F 5D /r MINPS xmm1, xmm2/m128 A Valid Valid Return the minimum singleprecision floating-point values between xmm2/m128 and xmm1.
	{ NULL, 0x0001, 0x00D88000, { 0x0F, 0x5D, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA },
	// VEX.NDS.128.0F 5D /r VMINPS xmm1,xmm2,xmm3/m128
	// VEX.NDS.256.0F 5D /r VMINPS ymm1,ymm2,ymm3/m256
	{ "vminps", 0x0080, 0x00D88000, { 0x0F, 0x5D, 0x00 }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_SIMD, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_MINSD[] = {
	// F2 0F 5D /r MINSD xmm1, xmm2/m64 A Valid Valid Return the minimum scalar double-precision floatingpoint value between xmm2/mem64 and xmm1.
	{ NULL, 0x2001, 0x00D88000, { 0x0F, 0x5D, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_64, _IRA_NA, _IRA_NA },
	// VEX.NDS.128.F2.0F 5D /r VMINSD xmm1, xmm2, xmm3/m64
	{ "vminsd", 0x20C0, 0x00D88000, { 0x0F, 0x5D, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_XMM_64, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_MINSS[] = {
	// F3 0F 5D /r MINSS xmm1, xmm2/m32 A Valid Valid Return the minimum scalar single-precision floatingpoint value between xmm2/mem32 and xmm1.
	{ NULL, 0x4001, 0x00D88000, { 0x0F, 0x5D, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_32, _IRA_NA, _IRA_NA },
	// VEX.NDS.128.F3.0F 5D /r VMINSS xmm1,xmm2,xmm3/m32
	{ "vminss", 0x40C0, 0x00D88000, { 0x0F, 0x5D, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_XMM_32, _IRA_NA }
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
	// TODO: Przy assemblacji pameitac zeby pozwolic na assemblacje samej mnemoniki!, byc moze idea virtualnych opcod rozwiaze problem
};



struct ira_opcode_desc _ira_opcode_desc_MOV[] = {
	// 88 /r MOV r/m8,r8 A Valid Valid Move r8 to r/m8.
	// REX + 88 /r MOV r/m8***,r8*** A Valid N.E. Move r8 to r/m8.
	{ NULL, 0x0001, 0x00C48000, { 0x88, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_8_W, _IRA_OPERAND_MODRM_R_8, _IRA_NA, _IRA_NA },
	// 89 /r MOV r/m16,r16 A Valid Valid Move r16 to r/m16.
	// 89 /r MOV r/m32,r32 A Valid Valid Move r32 to r/m32.
	// REX.W + 89 /r MOV r/m64,r64 A Valid N.E. Move r64 to r/m64.
	{ NULL, 0x0001, 0x00C48000, { 0x89, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_W, _IRA_OPERAND_MODRM_R, _IRA_NA, _IRA_NA },
	// 8A /r MOV r8,r/m8 B Valid Valid Move r/m8 to r8.
	// REX + 8A /r MOV r8***,r/m8*** B Valid N.E. Move r/m8 to r8.
	{ NULL, 0x0001, 0x00C48000, { 0x8A, 0x00, 0x00 }, _IRA_OPERAND_MODRM_R_8_W, _IRA_OPERAND_MODRM_RM_8, _IRA_NA, _IRA_NA },
	// 8B /r MOV r16,r/m16 B Valid Valid Move r/m16 to r16.
	// 8B /r MOV r32,r/m32 B Valid Valid Move r/m32 to r32.
	// REX.W + 8B /r MOV r64,r/m64 B Valid N.E. Move r/m64 to r64.
	{ NULL, 0x0001, 0x00C48000, { 0x8B, 0x00, 0x00 }, _IRA_OPERAND_MODRM_R_W, _IRA_OPERAND_MODRM_RM, _IRA_NA, _IRA_NA },
	// 8C /r MOV r/m16,Sreg** A Valid Valid Move segment register to r/m16.
	{ NULL, 0x0001, 0x03C48000, { 0x8C, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_16_W, _IRA_OPERAND_R( IRA_REG_SEG, _IRA_OS_WORD ), _IRA_NA, _IRA_NA },
	// REX.W + 8C /r MOV r/m64,Sreg** A Valid Valid Move zero extended 16-bit segment register to r/m64.
	{ NULL, 0x0001, 0x04848000, { 0x8C, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_64_W, _IRA_OPERAND_R( IRA_REG_SEG, _IRA_OS_WORD ), _IRA_NA, _IRA_NA },
	// A0 MOV AL,moffs8* C Valid Valid Move byte at (seg:offset) to AL.
	// REX.W + A0 MOV AL,moffs8* C Valid N.E. Move byte at (offset) to AL.
	{ NULL, 0x0001, 0x00C40000, { 0xA0, 0x00, 0x00 }, _IRA_EXPLICIT_REG( IRA_REG_GPR, _IRA_REG_AL, _IRA_OS_BYTE ), _IRA_OPERAND_SEGMENT_RELATIVE_OFFSET( _IRA_EOS_BYTE, _IRA_SEG_ENCODE_REGISTER( _IRA_REG_DS, _IRA_SEG_ALLOW_OVERRIDE ) ), _IRA_NA, _IRA_NA },
	// A1 MOV AX,moffs16* C Valid Valid Move word at (seg:offset) to AX.
	// A1 MOV EAX,moffs32* C Valid Valid Move doubleword at (seg:offset) to EAX.
	// REX.W + A1 MOV RAX,moffs64* C Valid N.E. Move quadword at (offset) to RAX.
	{ NULL, 0x0001, 0x00C40000, { 0xA1, 0x00, 0x00 }, _IRA_EXPLICIT_REG( IRA_REG_GPR, _IRA_REG_AL, _IRA_OS_EOSA ), _IRA_OPERAND_SEGMENT_RELATIVE_OFFSET( _IRA_EOS_EOSA, _IRA_SEG_ENCODE_REGISTER( _IRA_REG_DS, _IRA_SEG_ALLOW_OVERRIDE ) ), _IRA_NA, _IRA_NA },
	// A2 MOV moffs8,AL D Valid Valid Move AL to (seg:offset).
	// REX.W + A2 MOV moffs8***,AL D Valid N.E. Move AL to (offset).
	{ NULL, 0x0001, 0x00C40000, { 0xA2, 0x00, 0x00 }, _IRA_OPERAND_SEGMENT_RELATIVE_OFFSET( _IRA_EOS_BYTE, _IRA_SEG_ENCODE_REGISTER( _IRA_REG_DS, _IRA_SEG_ALLOW_OVERRIDE ) ), _IRA_EXPLICIT_REG( IRA_REG_GPR, _IRA_REG_AL, _IRA_OS_BYTE ), _IRA_NA, _IRA_NA },
	// A3 MOV moffs16*,AX D Valid Valid Move AX to (seg:offset).
	// A3 MOV moffs32*,EAX D Valid Valid Move EAX to (seg:offset).
	// REX.W + A3 MOV moffs64*,RAX D Valid N.E. Move RAX to (offset).
	{ NULL, 0x0001, 0x00C40000, { 0xA3, 0x00, 0x00 }, _IRA_OPERAND_SEGMENT_RELATIVE_OFFSET( _IRA_EOS_EOSA, _IRA_SEG_ENCODE_REGISTER( _IRA_REG_DS, _IRA_SEG_ALLOW_OVERRIDE ) ), _IRA_EXPLICIT_REG( IRA_REG_GPR, _IRA_REG_AL, _IRA_OS_EOSA ), _IRA_NA, _IRA_NA },
	// B0+ rb MOV r8, imm8 E Valid Valid Move imm8 to r8.
	// REX + B0+ rb MOV r8***, imm8 E Valid N.E. Move imm8 to r8.
	{ NULL, 0x0001, 0x00C40001, { 0xB0, 0x00, 0x00 }, _IRA_OPERAND_OPCODE_REG( IRA_REG_GPR, _IRA_OS_BYTE ) | _IRA_WRITE, _IRA_OPERAND_IB, _IRA_NA, _IRA_NA },
	// B8+ rw MOV r16, imm16 E Valid Valid Move imm16 to r16.
	// B8+ rd MOV r32, imm32 E Valid Valid Move imm32 to r32.
	// REX.W + B8+ rd MOV r64, imm64 E Valid N.E. Move imm64 to r64.
	{ NULL, 0x0001, 0x00C40001, { 0xB8, 0x00, 0x00 }, _IRA_OPERAND_OPCODE_REG( IRA_REG_GPR, _IRA_OS_EOSA ) | _IRA_WRITE, _IRA_OPERAND_IMM_EOSA, _IRA_NA, _IRA_NA },
	// C6 /0 MOV r/m8, imm8 F Valid Valid Move imm8 to r/m8.
	// REX + C6 /0 MOV r/m8***, imm8 F Valid N.E. Move imm8 to r/m8.
	{ NULL, 0x0001, 0x00C58000, { 0xC6, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_8_W, _IRA_OPERAND_IB, _IRA_NA, _IRA_NA },
	// C7 /0 MOV r/m16, imm16 F Valid Valid Move imm16 to r/m16.
	// C7 /0 MOV r/m32, imm32 F Valid Valid Move imm32 to r/m32.
	{ NULL, 0x0001, 0x03C58000, { 0xC7, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_W, _IRA_OPERAND_IMM_EOSA, _IRA_NA, _IRA_NA },
	// REX.W + C7 /0 MOV r/m64, imm32 F Valid N.E. Move imm32 sign extended to 64-bits to r/m64.
	{ NULL, 0x0001, 0x04858000, { 0xC7, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_W, _IRA_OPERAND_ID_EX_EOSA, _IRA_NA, _IRA_NA },
};

struct ira_opcode_desc _ira_opcode_desc_MOV_CR[] = {
	// 0F 20/r MOV r32, CR0–CR7 A N.E. Valid Move control register to r32
	{ NULL, 0x0001, 0x00588000, { 0x0F, 0x20, 0x00 }, _IRA_OPERAND_RM( IRA_REG_GPR, _IRA_EOS_DWORD, _IRA_EOS_UNDEFINED, _IRA_RMF_R ) | _IRA_WRITE, _IRA_OPERAND_R( IRA_REG_CR, _IRA_OS_DWORD ), _IRA_NA, _IRA_NA },
	// 0F 20/r MOV r64, CR0–CR7 A Valid N.E. Move extended control register to r64.
	// REX.R + 0F 20 /0 MOV r64, CR8 A Valid N.E. Move extended CR8 to r64.1
	{ NULL, 0x0001, 0x00988000, { 0x0F, 0x20, 0x00 }, _IRA_OPERAND_RM( IRA_REG_GPR, _IRA_EOS_QWORD, _IRA_EOS_UNDEFINED, _IRA_RMF_R ) | _IRA_WRITE, _IRA_OPERAND_R( IRA_REG_CR, _IRA_OS_QWORD ), _IRA_NA, _IRA_NA },
	// 0F 22 /r MOV CR0–CR7, r32 A N.E. Valid Move r32 to control register
	{ NULL, 0x0001, 0x00588000, { 0x0F, 0x22, 0x00 }, _IRA_OPERAND_R( IRA_REG_CR, _IRA_OS_DWORD ) | _IRA_WRITE, _IRA_OPERAND_RM( IRA_REG_GPR, _IRA_EOS_DWORD, _IRA_EOS_UNDEFINED, _IRA_RMF_R ), _IRA_NA, _IRA_NA },
	// 0F 22 /r MOV CR0–CR7, r64 A Valid N.E. Move r64 to extended control register.
	// REX.R + 0F 22 /0 MOV CR8, r64 A Valid N.E. Move r64 to extended CR8.1
	{ NULL, 0x0001, 0x00988000, { 0x0F, 0x22, 0x00 }, _IRA_OPERAND_R( IRA_REG_CR, _IRA_OS_QWORD ) | _IRA_WRITE, _IRA_OPERAND_RM( IRA_REG_GPR, _IRA_EOS_QWORD, _IRA_EOS_UNDEFINED, _IRA_RMF_R ), _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_MOV_DR[] = {
	// 0F 21/r MOV r32, DR0–DR7 A N.E. Valid Move debug register to r32
	{ NULL, 0x0001, 0x00588000, { 0x0F, 0x21, 0x00 }, _IRA_OPERAND_RM( IRA_REG_GPR, _IRA_EOS_DWORD, _IRA_EOS_UNDEFINED, _IRA_RMF_R ) | _IRA_WRITE, _IRA_OPERAND_R( IRA_REG_DR, _IRA_OS_DWORD ), _IRA_NA, _IRA_NA },
	// 0F 21/r MOV r64, DR0–DR7 A Valid N.E. Move extended debug register to r64.
	{ NULL, 0x0001, 0x00988000, { 0x0F, 0x21, 0x00 }, _IRA_OPERAND_RM( IRA_REG_GPR, _IRA_EOS_QWORD, _IRA_EOS_UNDEFINED, _IRA_RMF_R ) | _IRA_WRITE, _IRA_OPERAND_R( IRA_REG_DR, _IRA_OS_QWORD ), _IRA_NA, _IRA_NA },
	// 0F 23 /r MOV DR0–DR7, r32 A N.E. Valid Move r32 to debug register
	{ NULL, 0x0001, 0x00588000, { 0x0F, 0x23, 0x00 }, _IRA_OPERAND_R( IRA_REG_DR, _IRA_OS_DWORD ) | _IRA_WRITE, _IRA_OPERAND_RM( IRA_REG_GPR, _IRA_EOS_DWORD, _IRA_EOS_UNDEFINED, _IRA_RMF_R ), _IRA_NA, _IRA_NA },
	// 0F 23 /r MOV DR0–DR7, r64 A Valid N.E. Move r64 to extended debug register.
	{ NULL, 0x0001, 0x00988000, { 0x0F, 0x23, 0x00 }, _IRA_OPERAND_R( IRA_REG_DR, _IRA_OS_QWORD ) | _IRA_WRITE, _IRA_OPERAND_RM( IRA_REG_GPR, _IRA_EOS_QWORD, _IRA_EOS_UNDEFINED, _IRA_RMF_R ), _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_MOVAPD[] = {
	// 66 0F 28 /r MOVAPD xmm1, xmm2/m128 A Valid Valid Move packed doubleprecision floating-point values from xmm2/m128 to xmm1.
	{ NULL, 0x1001, 0x00D88000, { 0x0F, 0x28, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA },
	// 66 0F 29 /r MOVAPD xmm2/m128, xmm1 B Valid Valid Move packed doubleprecision floating-point values from xmm1 to xmm2/m128.
	{ NULL, 0x1001, 0x00D88000, { 0x0F, 0x29, 0x00 }, _IRA_OPERAND_MODRM_RM_XMM_128_W, _IRA_OPERAND_MODRM_R_XMM, _IRA_NA, _IRA_NA },
	// VEX.128.66.0F 28 /r VMOVAPD xmm1,xmm2/m128
	// VEX.256.66.0F 28 /r VMOVAPD ymm1,ymm2/m256
	{ "vmovapd", 0x1180, 0x00D88000, { 0x0F, 0x28, 0x00 }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_OPERAND_MODRM_RM_SIMD, _IRA_NA, _IRA_NA },
	// VEX.128.66.0F 29 /r VMOVAPD xmm2/m128,xmm1
	// VEX.256.66.0F 29 /r VMOVAPD ymm2/m256,ymm1
	{ "vmovapd", 0x1180, 0x00D88000, { 0x0F, 0x29, 0x00 }, _IRA_OPERAND_MODRM_RM_SIMD_W, _IRA_OPERAND_MODRM_R_SIMD, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_MOVAPS[] = {
	// 0F 28 /r MOVAPS xmm1, xmm2/m128 A Valid Valid Move packed singleprecision floating-point values from xmm2/m128 to xmm1.
	{ NULL, 0x0001, 0x00D88000, { 0x0F, 0x28, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA },
	// 0F 29 /r MOVAPS xmm2/m128, xmm1 B Valid Valid Move packed singleprecision floating-point values from xmm1 to xmm2/m128.
	{ NULL, 0x0001, 0x00D88000, { 0x0F, 0x29, 0x00 }, _IRA_OPERAND_MODRM_RM_XMM_128_W, _IRA_OPERAND_MODRM_R_XMM, _IRA_NA, _IRA_NA },
	// VEX.128.0F 28 /r VMOVAPS xmm1,xmm2/m128
	// VEX.256.0F 28 /r VMOVAPS ymm1,ymm2/m256
	{ "vmovaps", 0x0180, 0x00D88000, { 0x0F, 0x28, 0x00 }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_OPERAND_MODRM_RM_SIMD, _IRA_NA, _IRA_NA },
	// VEX.128.0F 29 /r VMOVAPS xmm2/m128,xmm1
	// VEX.256.0F 29 /r VMOVAPS ymm2/m256,ymm1
	{ "vmovaps", 0x0180, 0x00D88000, { 0x0F, 0x29, 0x00 }, _IRA_OPERAND_MODRM_RM_SIMD_W, _IRA_OPERAND_MODRM_R_SIMD, _IRA_NA, _IRA_NA }
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

struct ira_opcode_desc _ira_opcode_desc_MOVD[] = {
	// 0F 6E /r MOVD mm,r/m32 A Valid Valid Move doubleword from r/m32 to mm.
	{ NULL, 0x0001, 0x03D88000, { 0x0F, 0x6E, 0x00 }, _IRA_OPERAND_MODRM_R_MMX_W, _IRA_OPERAND_MODRM_RM_32, _IRA_NA, _IRA_NA },
	// REX.W + 0F 6E /r MOVQ mm, r/m64 A Valid N.E. Move quadword from r/m64 to mm.
	{ "movq", 0x0001, 0x04988000, { 0x0F, 0x6E, 0x00 }, _IRA_OPERAND_MODRM_R_MMX_W, _IRA_OPERAND_MODRM_RM_64, _IRA_NA, _IRA_NA },
	// 0F 7E /r MOVD r/m32, mm B Valid Valid Move doubleword from mm to r/m32.
	{ NULL, 0x0001, 0x03D88000, { 0x0F, 0x7E, 0x00 }, _IRA_OPERAND_MODRM_RM_32_W, _IRA_OPERAND_MODRM_R_MMX, _IRA_NA, _IRA_NA },
	// REX.W + 0F 7E /r MOVQ r/m64, mm B Valid N.E. Move quadword from mm to r/m64.
	{ "movq", 0x0001, 0x04988000, { 0x0F, 0x7E, 0x00 }, _IRA_OPERAND_MODRM_RM_64_W, _IRA_OPERAND_MODRM_R_MMX, _IRA_NA, _IRA_NA },
	// 66 0F 6E /r MOVD xmm, r/m32 A Valid Valid Move doubleword from r/m32 to xmm.
	{ NULL, 0x1001, 0x03D88000, { 0x0F, 0x6E, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_32, _IRA_NA, _IRA_NA },
	// 66 REX.W 0F 6E /r MOVQ xmm, r/m64 A Valid N.E. Move quadword from r/m64 to xmm.
	{ "movq", 0x1001, 0x04988000, { 0x0F, 0x6E, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_64, _IRA_NA, _IRA_NA },
	// 66 0F 7E /r MOVD r/m32, xmm B Valid Valid Move doubleword from xmm register to r/m32.
	{ NULL, 0x1001, 0x03D88000, { 0x0F, 0x7E, 0x00 }, _IRA_OPERAND_MODRM_RM_32_W, _IRA_OPERAND_MODRM_R_XMM, _IRA_NA, _IRA_NA },
	// 66 REX.W 0F 7E /r MOVQ r/m64, xmm B Valid N.E. Move quadword from xmm register to r/m64.
	{ "movq", 0x1001, 0x04988000, { 0x0F, 0x7E, 0x00 }, _IRA_OPERAND_MODRM_RM_64_W, _IRA_OPERAND_MODRM_R_XMM, _IRA_NA, _IRA_NA },
	// VEX.128.66.0F.W0 6E /r VMOVD xmm1,r32/m32
	{ "vmovd", 0x11D0, 0x03588000, { 0x0F, 0x6E, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_32, _IRA_NA, _IRA_NA },
	// VEX.128.66.0F.W1 6E /r VMOVQ xmm1,r64/m64
	{ "vmovq", 0x11C8, 0x04988000, { 0x0F, 0x6E, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_64, _IRA_NA, _IRA_NA },
	// VEX.128.66.0F.W0 7E /r VMOVD r32/m32,xmm1
	{ "vmovd", 0x11D0, 0x03588000, { 0x0F, 0x7E, 0x00 }, _IRA_OPERAND_MODRM_RM_32_W, _IRA_OPERAND_MODRM_R_XMM, _IRA_NA, _IRA_NA },
	// VEX.128.66.0F.W1 7E /r VMOVQ r64/m64,xmm1
	{ "vmovq", 0x11C8, 0x04988000, { 0x0F, 0x7E, 0x00 }, _IRA_OPERAND_MODRM_RM_64_W, _IRA_OPERAND_MODRM_R_XMM, _IRA_NA, _IRA_NA },
};

struct ira_opcode_desc _ira_opcode_desc_MOVDDUP[] = {
	//F2 0F 12 /r MOVDDUP xmm1, xmm2/m64 A Valid Valid Move one double-precision floating-point value from the lower 64-bit operand in xmm2/m64 to xmm1 and duplicate.
	{ NULL, 0x2001, 0x00D88000, { 0x0F, 0x12, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_64, _IRA_NA, _IRA_NA },
	// VEX.128.F2.0F 12 /r VMOVDDUP xmm1,xmm2/m64
	{ "vmovddup", 0x21C0, 0x00D88000, { 0x0F, 0x12, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_64, _IRA_NA, _IRA_NA },
	// VEX.256.F2.0F 12 /r VMOVDDUP ymm1,ymm2/m256
	{ "vmovddup", 0x21A0, 0x00D88000, { 0x0F, 0x12, 0x00 }, _IRA_OPERAND_MODRM_R_YMM_W, _IRA_OPERAND_MODRM_RM_YMM_256, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_MOVDQA[] = {
	// 66 0F 6F /r MOVDQA xmm1, xmm2/m128 A Valid Valid Move aligned double quadword from xmm2/m128 to xmm1.
	{ NULL, 0x1001, 0x00D88000, { 0x0F, 0x6F, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA },
	// 66 0F 7F /r MOVDQA xmm2/m128, xmm1 B Valid Valid Move aligned double quadword from xmm1 to xmm2/m128.
	{ NULL, 0x1001, 0x00D88000, { 0x0F, 0x7F, 0x00 }, _IRA_OPERAND_MODRM_RM_XMM_128_W, _IRA_OPERAND_MODRM_R_XMM, _IRA_NA, _IRA_NA },
	// VEX.128.66.0F 6F /r VMOVDQA xmm1,xmm2/m128
	// VEX.256.66.0F 6F /r VMOVDQA ymm1,ymm2/m256
	{ "vmovdqa", 0x1180, 0x00D88000, { 0x0F, 0x6F, 0x00 }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_OPERAND_MODRM_RM_SIMD, _IRA_NA, _IRA_NA },
	// VEX.128.66.0F 7F /r VMOVDQA xmm2/m128,xmm1
	// VEX.256.66.0F 7F /r VMOVDQA ymm2/m256,ymm1
	{ "vmovdqa", 0x1180, 0x00D88000, { 0x0F, 0x7F, 0x00 }, _IRA_OPERAND_MODRM_RM_SIMD_W, _IRA_OPERAND_MODRM_R_SIMD, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_MOVDQU[] = {
	// F3 0F 6F /r MOVDQU xmm1, xmm2/m128 A Valid Valid Move unaligned double quadword from xmm2/m128 to xmm1.
	{ NULL, 0x4001, 0x00D88000, { 0x0F, 0x6F, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA },
	// F3 0F 7F /r MOVDQU xmm2/m128, xmm1 B Valid Valid Move unaligned double quadword from xmm1 to xmm2/m128.
	{ NULL, 0x4001, 0x00D88000, { 0x0F, 0x7F, 0x00 }, _IRA_OPERAND_MODRM_RM_XMM_128_W, _IRA_OPERAND_MODRM_R_XMM, _IRA_NA, _IRA_NA },
	// VEX.128.F3.0F 6F /r VMOVDQU xmm1,xmm2/m128
	// VEX.256.F3.0F 6F /r VMOVDQU ymm1,ymm2/m256
	{ "vmovdqu", 0x4180, 0x00D88000, { 0x0F, 0x6F, 0x00 }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_OPERAND_MODRM_RM_SIMD, _IRA_NA, _IRA_NA },
	// VEX.128.F3.0F 7F /r VMOVDQU xmm2/m128,xmm1
	// VEX.256.F3.0F 7F /r VMOVDQU ymm2/m256,ymm1
	{ "vmovdqu", 0x4180, 0x00D88000, { 0x0F, 0x7F, 0x00 }, _IRA_OPERAND_MODRM_RM_SIMD_W, _IRA_OPERAND_MODRM_R_SIMD, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_MOVDQ2Q[] = {
	// F2 0F D6 MOVDQ2Q mm, xmm A Valid Valid Move low quadword from xmm to mmx register.
	{ NULL, 0x2001, 0x00DA8000, { 0x0F, 0xD6, 0x00 }, _IRA_OPERAND_MODRM_R_MMX_W, _IRA_OPERAND_RM( IRA_REG_SIMD, _IRA_EOS_XMMWORD, _IRA_EOS_UNDEFINED, _IRA_RMF_R ), _IRA_NA, _IRA_NA },
};

struct ira_opcode_desc _ira_opcode_desc_MOVHLPS[] = {
	// 0F 12 /r MOVHLPS xmm1, xmm2 A Valid Valid Move two packed singleprecision floating-point values from high quadword of xmm2 to low quadword of xmm1.
	{ NULL, 0x0001, 0x00DA8000, { 0x0F, 0x12, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_RM( IRA_REG_SIMD, _IRA_EOS_XMMWORD, _IRA_EOS_UNDEFINED, _IRA_RMF_R ), _IRA_NA, _IRA_NA },
	// VEX.NDS.128.0F 12 /r VMOVHLPS xmm1, xmm2, xmm3
	{ "vmovhlps", 0x00C0, 0x00DA8000, { 0x0F, 0x12, 0x00 }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_RM(IRA_REG_SIMD, _IRA_EOS_EOSA, _IRA_EOS_UNDEFINED, _IRA_RMF_R ), _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_MOVHPD[] = {
	// 66 0F 16 /r MOVHPD xmm, m64 A Valid Valid Move double-precision floating-point value from m64 to high quadword of xmm.
	{ NULL, 0x1001, 0x80D88000, { 0x0F, 0x16, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_RM( IRA_NO_REG, _IRA_EOS_UNDEFINED, _IRA_EOS_QWORD, _IRA_RMF_M ), _IRA_NA, _IRA_NA },
	// 66 0F 17 /r MOVHPD m64, xmm B Valid Valid Move double-precision floating-point value from high quadword of xmm to m64.
	{ NULL, 0x1001, 0x80D88000, { 0x0F, 0x17, 0x00 }, _IRA_OPERAND_RM( IRA_NO_REG, _IRA_EOS_UNDEFINED, _IRA_EOS_QWORD, _IRA_RMF_M ) | _IRA_WRITE, _IRA_OPERAND_MODRM_R_XMM, _IRA_NA, _IRA_NA },
	// VEX.NDS.128.66.0F 16 /r VMOVHPD xmm2,xmm1,m64
	{ "vmovhpd", 0x10C0, 0x80D88000, { 0x0F, 0x16, 0x00 }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_SIMD_64, _IRA_NA },
	// VEX128.66.0F 17/r VMOVHPD m64, xmm1
	{ "vmovhpd", 0x11C0, 0x80D88000, { 0x0F, 0x17, 0x00 }, _IRA_OPERAND_MODRM_RM_SIMD_64_W, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_MOVHPS[] = {
	// 0F 16 /r MOVHPS xmm, m64 A Valid Valid Move two packed singleprecision floating-point values from m64 to high quadword of xmm.
	{ NULL, 0x0001, 0x80D88000, { 0x0F, 0x16, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_RM( IRA_NO_REG, _IRA_EOS_UNDEFINED, _IRA_EOS_QWORD, _IRA_RMF_M ), _IRA_NA, _IRA_NA },
	// 0F 17 /r MOVHPS m64, xmm B Valid Valid Move two packed singleprecision floating-point values from high quadword of xmm to m64.
	{ NULL, 0x0001, 0x80D88000, { 0x0F, 0x17, 0x00 }, _IRA_OPERAND_RM( IRA_NO_REG, _IRA_EOS_UNDEFINED, _IRA_EOS_QWORD, _IRA_RMF_M ) | _IRA_WRITE, _IRA_OPERAND_MODRM_R_XMM, _IRA_NA, _IRA_NA },
	// VEX.NDS.128.0F 16 /r VMOVHPS xmm2,xmm1,m64
	{ "vmovhps", 0x00C0, 0x80D88000, { 0x0F, 0x16, 0x00 }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_SIMD_64, _IRA_NA },
	// VEX.128.0F 17 /r VMOVHPS m64,xmm1
	{ "vmovhps", 0x01C0, 0x80D88000, { 0x0F, 0x17, 0x00 }, _IRA_OPERAND_MODRM_RM_SIMD_64_W, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_MOVLHPS[] = {
	// 0F 16 /r MOVLHPS xmm1, xmm2 A Valid Valid Move two packed singleprecision floating-point values from low quadword of xmm2 to high quadword of xmm1.
	{ NULL, 0x0001, 0x00DA8000, { 0x0F, 0x16, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_RM( IRA_REG_SIMD, _IRA_EOS_XMMWORD, _IRA_EOS_UNDEFINED, _IRA_RMF_R ), _IRA_NA, _IRA_NA },
	// VEX.NDS.128.0F 16 /r VMOVLHPS xmm1,xmm2,xmm3
	{ "vmovlhps", 0x00C0, 0x00DA8000, { 0x0F, 0x16, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_RM( IRA_REG_SIMD, _IRA_EOS_XMMWORD, _IRA_EOS_UNDEFINED, _IRA_RMF_R ), _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_MOVLPD[] = {
	// 66 0F 12 /r MOVLPD xmm, m64 A Valid Valid Move double-precision floating-point value from m64 to low quadword of xmm register.
	{ NULL, 0x1001, 0x80D88000, { 0x0F, 0x12, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_RM( IRA_NO_REG, _IRA_EOS_UNDEFINED, _IRA_EOS_QWORD, _IRA_RMF_M ), _IRA_NA, _IRA_NA },
	// 66 0F 13 /r MOVLPD m64, xmm B Valid Valid Move double-precision floating-point nvalue from low quadword of xmm register to m64.
	{ NULL, 0x1001, 0x80D88000, { 0x0F, 0x13, 0x00 }, _IRA_OPERAND_RM( IRA_NO_REG, _IRA_EOS_UNDEFINED, _IRA_EOS_QWORD, _IRA_RMF_M ) | _IRA_WRITE, _IRA_OPERAND_MODRM_R_XMM, _IRA_NA, _IRA_NA },
	// VEX.NDS.128.66.0F 12 /r VMOVLPD xmm2,xmm1,m64
	{ "vmovlpd", 0x10C0, 0x80D88000, { 0x0F, 0x12, 0x00 }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_SIMD_64, _IRA_NA },
	// VEX.128.66.0F 13 /r VMOVLPD m64,xmm1
	{ "vmovlpd", 0x11C0, 0x80D88000, { 0x0F, 0x13, 0x00 }, _IRA_OPERAND_MODRM_RM_SIMD_64_W, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_MOVLPS[] = {
	// 0F 12 /r MOVLPS xmm, m64 A Valid Valid Move two packed singleprecision floating-point values from m64 to low quadword of xmm.
	{ NULL, 0x0001, 0x80D88000, { 0x0F, 0x12, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_RM( IRA_NO_REG, _IRA_EOS_UNDEFINED, _IRA_EOS_QWORD, _IRA_RMF_M ), _IRA_NA, _IRA_NA },
	// 0F 13 /r MOVLPS m64, xmm B Valid Valid Move two packed singleprecision floating-point values from low quadword of xmm to m64.
	{ NULL, 0x0001, 0x80D88000, { 0x0F, 0x13, 0x00 }, _IRA_OPERAND_RM( IRA_NO_REG, _IRA_EOS_UNDEFINED, _IRA_EOS_QWORD, _IRA_RMF_M ) | _IRA_WRITE, _IRA_OPERAND_MODRM_R_XMM, _IRA_NA, _IRA_NA },
	// VEX.NDS.128.0F 12 /r VMOVLPS xmm2,xmm1,m64
	{ "vmovlps", 0x00C0, 0x80D88000, { 0x0F, 0x12, 0x00 }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_M_64, _IRA_NA },
	// VEX.128.0F 13 /r VMOVLPS m64, xmm1
	{ "vmovlps", 0x01C0, 0x80D88000, { 0x0F, 0x13, 0x00 }, _IRA_OPERAND_MODRM_M_64_W, _IRA_OPERAND_MODRM_R_XMM, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_MOVMSKPD[] = {
	// 66 0F 50 /r MOVMSKPD reg, xmm A Valid Valid Extract 2-bit sign mask from xmm and store in reg. The upper bits of r32 or r64 are filled with zeros.
	{ NULL, 0x1001, 0x005A8000, { 0x0F, 0x50, 0x00 }, _IRA_OPERAND_MODRM_R_32_W, _IRA_OPERAND_RM( IRA_REG_SIMD, _IRA_EOS_XMMWORD, _IRA_EOS_UNDEFINED, _IRA_RMF_R ), _IRA_NA, _IRA_NA },
	{ NULL, 0x1001, 0x009A8000, { 0x0F, 0x50, 0x00 }, _IRA_OPERAND_MODRM_R_64_W, _IRA_OPERAND_RM( IRA_REG_SIMD, _IRA_EOS_XMMWORD, _IRA_EOS_UNDEFINED, _IRA_RMF_R ), _IRA_NA, _IRA_NA },
	// VEX.128.66.0F 50 /r VMOVMSKPD reg,xmm2
	// VEX.256.66.0F 50 /r VMOVMSKPD reg,ymm2
	{ "vmovmskpd", 0x1180, 0x005A8000, { 0x0F, 0x50, 0x00 }, _IRA_OPERAND_MODRM_R_32_W, _IRA_OPERAND_RM( IRA_REG_SIMD, _IRA_EOS_EOSA, _IRA_EOS_UNDEFINED, _IRA_RMF_R ), _IRA_NA, _IRA_NA },
	{ "vmovmskpd", 0x1180, 0x009A8000, { 0x0F, 0x50, 0x00 }, _IRA_OPERAND_MODRM_R_64_W, _IRA_OPERAND_RM( IRA_REG_SIMD, _IRA_EOS_EOSA, _IRA_EOS_UNDEFINED, _IRA_RMF_R ), _IRA_NA, _IRA_NA },
};

struct ira_opcode_desc _ira_opcode_desc_MOVMSKPS[] = {
	// 0F 50 /r MOVMSKPS reg, xmm A Valid Valid Extract 4-bit sign mask from xmm and store in reg. The upper bits of r32 or r64 are filled with zeros.
	{ NULL, 0x0001, 0x005A8000, { 0x0F, 0x50, 0x00 }, _IRA_OPERAND_MODRM_R_32_W, _IRA_OPERAND_RM( IRA_REG_SIMD, _IRA_EOS_XMMWORD, _IRA_EOS_UNDEFINED, _IRA_RMF_R ), _IRA_NA, _IRA_NA },
	{ NULL, 0x0001, 0x009A8000, { 0x0F, 0x50, 0x00 }, _IRA_OPERAND_MODRM_R_64_W, _IRA_OPERAND_RM( IRA_REG_SIMD, _IRA_EOS_XMMWORD, _IRA_EOS_UNDEFINED, _IRA_RMF_R ), _IRA_NA, _IRA_NA },
	// VEX.128.0F 50 /r VMOVMSKPS reg,xmm2
	// VEX.256.0F 50 /r VMOVMSKPS reg,ymm2
	{ "vmovmskps", 0x0180, 0x005A8000, { 0x0F, 0x50, 0x00 }, _IRA_OPERAND_MODRM_R_32_W, _IRA_OPERAND_RM( IRA_REG_SIMD, _IRA_EOS_EOSA, _IRA_EOS_UNDEFINED, _IRA_RMF_R ), _IRA_NA, _IRA_NA },
	{ "vmovmskps", 0x0180, 0x009A8000, { 0x0F, 0x50, 0x00 }, _IRA_OPERAND_MODRM_R_64_W, _IRA_OPERAND_RM( IRA_REG_SIMD, _IRA_EOS_EOSA, _IRA_EOS_UNDEFINED, _IRA_RMF_R ), _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_MOVNTDQA[] = {
	// 66 0F 38 2A /r MOVNTDQA xmm1, m128 A Valid Valid Move double quadword from m128 to xmm using non-temporal hint if WC memory type.
	{ NULL, 0x1001, 0x80EC8000, { 0x0F, 0x38, 0x2A }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_RM( IRA_NO_REG, _IRA_EOS_UNDEFINED, _IRA_EOS_OWORD, _IRA_RMF_M ), _IRA_NA, _IRA_NA },
	// VEX.128.66.0F38 2A /r VMOVNTDQA xmm1,m128
	{ "vmovntdqa", 0x11C0, 0x80EC8000, { 0x0F, 0x38, 0x2A }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_M_128, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_MOVNTDQ[] = {
	// 66 0F E7 /r MOVNTDQ m128, xmm A Valid Valid Move double quadword from xmm to m128 using non-temporal hint.
	{ NULL, 0x1001, 0x80D88000, { 0x0F, 0xE7, 0x00 }, _IRA_OPERAND_RM( IRA_NO_REG, _IRA_EOS_UNDEFINED, _IRA_EOS_OWORD, _IRA_RMF_M ) | _IRA_WRITE, _IRA_OPERAND_MODRM_R_XMM , _IRA_NA, _IRA_NA },
	// VEX.128.66.0F E7 /r VMOVNTDQ m128,xmm1
	{ "vmovntdq", 0x11C0, 0x80D88000, { 0x0F, 0xE7, 0x00 }, _IRA_OPERAND_MODRM_M_128_W, _IRA_OPERAND_MODRM_R_XMM, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_MOVNTI[] = {
	// 0F C3 /r MOVNTI m32, r32 A Valid Valid Move doubleword from r32 to m32 using non-temporal hint.
	{ NULL, 0x0001, 0x83D88000, { 0x0F, 0xC3, 0x00 }, _IRA_OPERAND_RM( IRA_NO_REG, _IRA_EOS_UNDEFINED, _IRA_EOS_DWORD, _IRA_RMF_M ) | _IRA_WRITE, _IRA_OPERAND_MODRM_R_32 , _IRA_NA, _IRA_NA },
	// REX.W + 0F C3 /rMOVNTI m64, r64 A Valid N.E. Move quadword from r64 to m64 using non-temporal hint.
	{ NULL, 0x0001, 0x84988000, { 0x0F, 0xC3, 0x00 }, _IRA_OPERAND_RM( IRA_NO_REG, _IRA_EOS_UNDEFINED, _IRA_EOS_QWORD, _IRA_RMF_M ) | _IRA_WRITE, _IRA_OPERAND_MODRM_R_64 , _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_MOVNTPD[] = {
	// 66 0F 2B /r MOVNTPD m128, xmm A Valid Valid Move packed doubleprecision floating-point values from xmm to m128 using non-temporal hint.
	{ NULL, 0x1001, 0x80D88000, { 0x0F, 0x2B, 0x00 }, _IRA_OPERAND_RM( IRA_NO_REG, _IRA_EOS_UNDEFINED, _IRA_EOS_OWORD, _IRA_RMF_M ) | _IRA_WRITE, _IRA_OPERAND_MODRM_R_XMM , _IRA_NA, _IRA_NA },
	// VEX.128.66.0F 2B /r VMOVNTPD m128,xmm1
	{ "vmovntpd", 0x11C0, 0x80D88000, { 0x0F, 0x2B, 0x00 }, _IRA_OPERAND_MODRM_M_128_W, _IRA_OPERAND_MODRM_R_XMM, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_MOVNTPS[] = {
	// 0F 2B /r MOVNTPS m128, xmm A Valid Valid Move packed singleprecision floating-point values from xmm to m128 using non-temporal hint.
	{ NULL, 0x0001, 0x80D88000, { 0x0F, 0x2B, 0x00 }, _IRA_OPERAND_RM( IRA_NO_REG, _IRA_EOS_UNDEFINED, _IRA_EOS_OWORD, _IRA_RMF_M ) | _IRA_WRITE, _IRA_OPERAND_MODRM_R_XMM , _IRA_NA, _IRA_NA },
	// VEX.128.0F 2B /r VMOVNTPS m128, xmm1
	{ "vmovntps", 0x01C0, 0x80D88000, { 0x0F, 0x2B, 0x00 }, _IRA_OPERAND_MODRM_M_128_W, _IRA_OPERAND_MODRM_R_XMM, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_MOVNTQ[] = {
	// 0F E7 /r MOVNTQ m64, mm A Valid Valid Move quadword from mm to m64 using non-temporal hint.
	{ NULL, 0x0001, 0x80D88000, { 0x0F, 0xE7, 0x00 }, _IRA_OPERAND_RM( IRA_NO_REG, _IRA_EOS_UNDEFINED, _IRA_EOS_QWORD, _IRA_RMF_M ) | _IRA_WRITE, _IRA_OPERAND_MODRM_R_MMX , _IRA_NA, _IRA_NA },
};

struct ira_opcode_desc _ira_opcode_desc_MOVQ[] = {
	// 0F 6F /r MOVQ mm, mm/m64 A Valid Valid Move quadword from mm/m64 to mm.
	{ NULL, 0x0001, 0x00D88000, { 0x0F, 0x6F, 0x00 }, _IRA_OPERAND_MODRM_R_MMX_W, _IRA_OPERAND_MODRM_RM_MMX, _IRA_NA, _IRA_NA },
	// 0F 7F /r MOVQ mm/m64, mm B Valid Valid Move quadword from mm to mm/m64.
	{ NULL, 0x0001, 0x00D88000, { 0x0F, 0x7F, 0x00 }, _IRA_OPERAND_MODRM_RM_MMX_W, _IRA_OPERAND_MODRM_R_MMX, _IRA_NA, _IRA_NA },
	// F3 0F 7E MOVQ xmm1, xmm2/m64 A Valid Valid Move quadword from xmm2/mem64 to xmm1.
	{ NULL, 0x4001, 0x00D88000, { 0x0F, 0x7E, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_64, _IRA_NA, _IRA_NA },
	// 66 0F D6 MOVQ xmm2/m64, xmm1 B Valid Valid Move quadword from xmm1 to xmm2/mem64.
	{ NULL, 0x1001, 0x00D88000, { 0x0F, 0xD6, 0x00 }, _IRA_OPERAND_MODRM_RM_XMM_64_W, _IRA_OPERAND_MODRM_R_XMM, _IRA_NA, _IRA_NA },
	// VEX.128.F3.0F 7E /r VMOVQ xmm1,xmm2
	// VEX.128.F3.0F 7E /r VMOVQ xmm1,m64
	{ "vmovq", 0x41C0, 0x00D88000, { 0x0F, 0x7E, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_64, _IRA_NA, _IRA_NA },
	// VEX.128.66.0F D6 /r VMOVQ xmm1/m64,xmm2
	{ "vmovq", 0x41C0, 0x00D88000, { 0x0F, 0xD6, 0x00 }, _IRA_OPERAND_MODRM_RM_XMM_64_W, _IRA_OPERAND_MODRM_R_XMM, _IRA_NA, _IRA_NA }

};

struct ira_opcode_desc _ira_opcode_desc_MOVQ2DQ[] = {
	// F3 0F D6 MOVQ2DQ xmm, mm A Valid Valid Move quadword from mmx to low quadword of xmm.
	{ NULL, 0x4001, 0x00DA8000, { 0x0F, 0xD6, 0x00 }, _IRA_OPERAND_RM( IRA_REG_SIMD, _IRA_EOS_XMMWORD, _IRA_EOS_UNDEFINED, _IRA_RMF_R ) | _IRA_WRITE, _IRA_OPERAND_MODRM_R_MMX, _IRA_NA, _IRA_NA },
};

struct ira_opcode_desc _ira_opcode_desc_MOVS[] = {
	// A4 MOVS m8, m8 A Valid Valid For legacy mode, Move byte from address DS:(E)SI to ES:(E)DI. For 64-bit mode move byte from address (R|E)SI to (R|E)DI.
	{ NULL, 0x0001, 0x00C40000, { 0xA4, 0x00, 0x00 },
			_IRA_EXPLICIT_GPS_REG_ADDRESSING( _IRA_REG_SI, _IRA_EOS_BYTE, _IRA_SEG_ENCODE_REGISTER( _IRA_REG_DS, _IRA_SEG_ALLOW_OVERRIDE ) ),
			_IRA_EXPLICIT_GPS_REG_ADDRESSING( _IRA_REG_DI, _IRA_EOS_BYTE, _IRA_SEG_ENCODE_REGISTER( _IRA_REG_ES, _IRA_SEG_DENY_OVERRIDE ) ),
			_IRA_NA, _IRA_NA },
	// A5 MOVS m16, m16 A Valid Valid For legacy mode, move word from address DS:(E)SI to ES:(E)DI. For 64-bit mode move word at address (R|E)SI to (R|E)DI.
	// A5 MOVS m32, m32 A Valid Valid For legacy mode, move dword from address DS:(E)SI to ES:(E)DI. For 64-bit mode move dword from address (R|E)SI to (R|E)DI.
	// REX.W + A5 MOVS m64, m64 A Valid N.E. Move qword from address (R|E)SI to (R|E)DI.
	{ NULL, 0x0001, 0x00C40000, { 0xA5, 0x00, 0x00 },
			_IRA_EXPLICIT_GPS_REG_ADDRESSING( _IRA_REG_SI, _IRA_EOS_EOSA,_IRA_SEG_ENCODE_REGISTER( _IRA_REG_DS, _IRA_SEG_ALLOW_OVERRIDE ) ),
			_IRA_EXPLICIT_GPS_REG_ADDRESSING( _IRA_REG_DI, _IRA_EOS_EOSA,_IRA_SEG_ENCODE_REGISTER( _IRA_REG_ES, _IRA_SEG_DENY_OVERRIDE ) ),
			_IRA_NA, _IRA_NA }
	// A4 MOVSB A Valid Valid For legacy mode, Move byte from address DS:(E)SI to ES:(E)DI. For 64-bit mode move byte from address (R|E)SI to (R|E)DI.
	// A5 MOVSW A Valid Valid For legacy mode, move word from address DS:(E)SI to ES:(E)DI. For 64-bit mode move word at address (R|E)SI to (R|E)DI.
	// A5 MOVSD A Valid Valid For legacy mode, move dword from address DS:(E)SI to ES:(E)DI. For 64-bit mode move dword from address (R|E)SI to (R|E)DI. REX.W + A5 MOVSQ A Valid N.E. Move qword from address
};

struct ira_opcode_desc _ira_opcode_desc_MOVSD[] = {
	// F2 0F 10 /r MOVSD xmm1, xmm2/m64 A Valid Valid Move scalar doubleprecision floating-point value from xmm2/m64 to xmm1 register.
	{ NULL, 0x2001, 0x00D88000, { 0x0F, 0x10, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_64, _IRA_NA, _IRA_NA },
	// F2 0F 11 /r MOVSD xmm2/m64, xmm1 B Valid Valid Move scalar doubleprecision floating-point value from xmm1 register to xmm2/m64.
	{ NULL, 0x2001, 0x00D88000, { 0x0F, 0x11, 0x00 }, _IRA_OPERAND_MODRM_RM_XMM_64_W, _IRA_OPERAND_MODRM_R_XMM, _IRA_NA, _IRA_NA },
	// VEX.NDS.128.F2.0F 10 /r VMOVSD xmm1,xmm2,xmm3
	{ "vmovsd", 0x20C0, 0x00DA8000, { 0x0F, 0x10, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_RM( IRA_REG_SIMD, _IRA_EOS_XMMWORD, _IRA_EOS_UNDEFINED, _IRA_RMF_R ), _IRA_NA },
	// VEX.NDS.128.F2.0F 11 /r VMOVSD xmm1,xmm2,xmm3
	{ "vmovsd", 0x20C0, 0x00DA8000, { 0x0F, 0x11, 0x00 }, _IRA_OPERAND_RM( IRA_REG_SIMD, _IRA_EOS_XMMWORD, _IRA_EOS_UNDEFINED, _IRA_RMF_R ) | _IRA_WRITE, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_R_XMM, _IRA_NA },
	// VEX.128.F2.0F 10 /r VMOVSD xmm1,m64
	{ "vmovsd", 0x21C0, 0x80D88000, { 0x0F, 0x10, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_M_64, _IRA_NA, _IRA_NA },
	// VEX.128.F2.0F 11 /r VMOVSD m64,xmm1
	{ "vmovsd", 0x21C0, 0x80D88000, { 0x0F, 0x11, 0x00 }, _IRA_OPERAND_MODRM_M_64_W, _IRA_OPERAND_MODRM_R_XMM, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_MOVSHDUP[] = {
	// F3 0F 16 /r MOVSHDUP xmm1, xmm2/m128 A Valid Valid Move two single-precisionfloating-point values from the higher 32-bit operand of each qword in xmm2/m128 to xmm1 and duplicate each 32-bit operand to the lower 32-bits of each qword.
	{ NULL, 0x4001, 0x00D88000, { 0x0F, 0x16, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA },
	// VEX.128.F3.0F 16 /r VMOVSHDUP xmm1,xmm2/m128
	// VEX.256.F3.0F 16 /r VMOVSHDUP ymm1,ymm2/m256
	{ "vmovshdup", 0x4180, 0x00D88000, { 0x0F, 0x16, 0x00 }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_OPERAND_MODRM_RM_SIMD, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_MOVSLDUP[] = {
	// F3 0F 12 /r MOVSLDUP xmm1, xmm2/m128 A Valid Valid Move two single-precision floating-point values from the lower 32-bit operand ofeach qword in xmm2/m128 to xmm1 and duplicate each 32-bit operand to the higher 32-bits of each qword.
	{ NULL, 0x4001, 0x00D88000, { 0x0F, 0x12, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA },
	// VEX.128.F3.0F 12 /r VMOVSLDUP xmm1,xmm2/m128
	// VEX.256.F3.0F 12 /r VMOVSLDUP ymm1,ymm2/m256
	{ "vmovsldup", 0x4180, 0x00D88000, { 0x0F, 0x12, 0x00 }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_OPERAND_MODRM_RM_SIMD, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_MOVSS[] = {
	// F3 0F 10 /r MOVSS xmm1, xmm2/m32 A Valid Valid Move scalar single-precision floating-point value from xmm2/m32 to xmm1 register.
	{ NULL, 0x4001, 0x00D88000, { 0x0F, 0x10, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_32, _IRA_NA, _IRA_NA },
	// F3 0F 11 /r MOVSS xmm2/m32, xmm B Valid Valid Move scalar single-precision floating-point value from xmm1 register to
	{ NULL, 0x4001, 0x00D88000, { 0x0F, 0x11, 0x00 }, _IRA_OPERAND_MODRM_RM_XMM_32_W, _IRA_OPERAND_MODRM_R_XMM, _IRA_NA, _IRA_NA },
	// VEX.NDS.128.F3.0F 10 /r VMOVSS xmm1,xmm2,xmm3
	{ "vmovss", 0x40C0, 0x00DA8000, { 0x0F, 0x10, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_RM( IRA_REG_SIMD, _IRA_EOS_XMMWORD, _IRA_EOS_UNDEFINED, _IRA_RMF_R ), _IRA_NA },
	// VEX.NDS.128.F3.0F 11 /r VMOVSS xmm1,xmm2,xmm3
	{ "vmovss", 0x40C0, 0x00DA8000, { 0x0F, 0x11, 0x00 }, _IRA_OPERAND_RM( IRA_REG_SIMD, _IRA_EOS_XMMWORD, _IRA_EOS_UNDEFINED, _IRA_RMF_R ) | _IRA_WRITE, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_R_XMM, _IRA_NA },
	// VEX.128.F3.0F 10 /r VMOVSS xmm1,m32
	{ "vmovss", 0x41C0, 0x80D88000, { 0x0F, 0x10, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_M_32, _IRA_NA, _IRA_NA },
	// VEX.128.F3.0F 11 /r VMOVSS m32,xmm1
	{ "vmovss", 0x41C0, 0x80D88000, { 0x0F, 0x11, 0x00 }, _IRA_OPERAND_MODRM_M_32_W, _IRA_OPERAND_MODRM_R_XMM, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_MOVSX[] = {
	// 0F BE /r MOVSX r16, r/m8 A Valid Valid Move byte to word with sign-extension.
	// 0F BE /r MOVSX r32, r/m8 A Valid Valid Move byte to doubleword with sign-extension.
	// REX + 0F BE /r MOVSX r64, r/m8* A Valid N.E. Move byte to quadword with sign-extension.
	{ NULL, 0x0001, 0x00D88000, { 0x0F, 0xBE, 0x00 }, _IRA_OPERAND_MODRM_R_W, _IRA_OPERAND_MODRM_RM_8, _IRA_NA, _IRA_NA },
	// 0F BF /r MOVSX r32, r/m16 A Valid Valid Move word to doubleword, with sign-extension.
	{ NULL, 0x0001, 0x03D88000, { 0x0F, 0xBF, 0x00 }, _IRA_OPERAND_MODRM_R_32_W, _IRA_OPERAND_MODRM_RM_16, _IRA_NA, _IRA_NA },
	// REX.W + 0F BF /r MOVSX r64, r/m16 A Valid N.E. Move word to quadword with sign-extension.
	{ NULL, 0x0001, 0x04988000, { 0x0F, 0xBF, 0x00 }, _IRA_OPERAND_MODRM_R_64_W, _IRA_OPERAND_MODRM_RM_16, _IRA_NA, _IRA_NA },
	// REX.W** + 63 /r MOVSXD r64, r/m32 A Valid N.E. Move doubleword to quadword with signextension.
	{ "movsxd", 0x0001, 0x04848000, { 0x63, 0x00, 0x00 }, _IRA_OPERAND_MODRM_R_64_W, _IRA_OPERAND_MODRM_RM_32, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_MOVUPD[] = {
	// 66 0F 10 /r MOVUPD xmm1, xmm2/m128 A Valid Valid Move packed doubleprecision floating-point values from xmm2/m128 to xmm1.
	{ NULL, 0x1001, 0x00D88000, { 0x0F, 0x10, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA },
	// 66 0F 11 /r MOVUPD xmm2/m128, xmm B Valid Valid Move packed doubleprecision floating-point values from xmm1 to xmm2/m128.
	{ NULL, 0x1001, 0x00D88000, { 0x0F, 0x11, 0x00 }, _IRA_OPERAND_MODRM_RM_XMM_128_W, _IRA_OPERAND_MODRM_R_XMM, _IRA_NA, _IRA_NA },
	// VEX.128.66.0F 10 /r VMOVUPD xmm1,xmm2/m128
	// VEX.256.66.0F 10 /r VMOVUPD ymm1,ymm2/m256
	{ "vmovupd", 0x1180, 0x00D88000, { 0x0F, 0x10, 0x00 }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_OPERAND_MODRM_RM_SIMD, _IRA_NA, _IRA_NA },
	// VEX.128.66.0F 11 /r VMOVUPD xmm2/m128,xmm1
	// VEX.256.66.0F 11 /r VMOVUPD ymm2/m256,ymm1
	{ "vmovupd", 0x1180, 0x00D88000, { 0x0F, 0x11, 0x00 }, _IRA_OPERAND_MODRM_RM_SIMD_W, _IRA_OPERAND_MODRM_R_SIMD, _IRA_NA, _IRA_NA },
};

struct ira_opcode_desc _ira_opcode_desc_MOVUPS[] = {
	// 0F 10 /r MOVUPS xmm1, xmm2/m128 A Valid Valid Move packed singleprecision floating-point values from xmm2/m128 to xmm1.
	{ NULL, 0x0001, 0x00D88000, { 0x0F, 0x10, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA },
	// 0F 11 /r MOVUPS xmm2/m128, xmm1 B Valid Valid Move packed singleprecision floating-point values from xmm1 to xmm2/m128.
	{ NULL, 0x0001, 0x00D88000, { 0x0F, 0x11, 0x00 }, _IRA_OPERAND_MODRM_RM_XMM_128_W, _IRA_OPERAND_MODRM_R_XMM, _IRA_NA, _IRA_NA },
	// VEX.128.0F 10 /r VMOVUPS xmm1,xmm2/m128
	// VEX.256.0F 10 /r VMOVUPS ymm1,ymm2/m256
	{ "vmovups", 0x0180, 0x00D88000, { 0x0F, 0x10, 0x00 }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_OPERAND_MODRM_RM_SIMD, _IRA_NA, _IRA_NA },
	// VEX.128.0F 11 /r VMOVUPS xmm2/m128,xmm1
	// VEX.256.0F 11 /r VMOVUPS ymm2/m256,ymm1
	{ "vmovups", 0x0180, 0x00D88000, { 0x0F, 0x11, 0x00 }, _IRA_OPERAND_MODRM_RM_SIMD_W, _IRA_OPERAND_MODRM_R_SIMD, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_MOVZX[] = {
	// 0F B6 /r MOVZX r16, r/m8 A Valid Valid Move byte to word with zero-extension.
	// 0F B6 /r MOVZX r32, r/m8 A Valid Valid Move byte to doubleword, zero-extension.
	// REX.W + 0F B6 /r MOVZX r64, r/m8* A Valid N.E. Move byte to quadword, zero-extension.
	{ NULL, 0x0001, 0x00D88000, { 0x0F, 0xB6, 0x00 }, _IRA_OPERAND_MODRM_R_W, _IRA_OPERAND_MODRM_RM_8, _IRA_NA, _IRA_NA },
	// 0F B7 /r MOVZX r32, r/m16 A Valid Valid Move word to doubleword, zero-extension.
	{ NULL, 0x0001, 0x03D88000, { 0x0F, 0xB7, 0x00 }, _IRA_OPERAND_MODRM_R_32_W, _IRA_OPERAND_MODRM_RM_16, _IRA_NA, _IRA_NA },
	// REX.W + 0F B7 /r MOVZX r64, r/m16 A Valid N.E. Move word to quadword, zero-extension.
	{ NULL, 0x0001, 0x04988000, { 0x0F, 0xB7, 0x00 }, _IRA_OPERAND_MODRM_R_64_W, _IRA_OPERAND_MODRM_RM_16, _IRA_NA, _IRA_NA },
};

struct ira_opcode_desc _ira_opcode_desc_MPSADBW[] = {
	// 66 0F 3A 42 /r ib MPSADBW xmm1, xmm2/m128, imm8 A Valid Valid Sums absolute 8-bit integer difference of adjacent groups of 4 byte integers in xmm1 and xmm2/m128 and writes the results in xmm1. Starting offsets within xmm1 and xmm2/m128 are determined by imm8.
	{ NULL, 0x1001, 0x00EC8000, { 0x0F, 0x3A, 0x42 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_OPERAND_IB, _IRA_NA },
	// VEX.NDS.128.66.0F3A 42 /r ib VMPSADBW xmm1,xmm2,xmm3/m128,imm8
	{ "vmpsadbw", 0x10C0, 0x00EC8000, { 0x0F, 0x3A, 0x42 }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_SIMD_64, _IRA_OPERAND_IB }
};

struct ira_opcode_desc _ira_opcode_desc_MUL[] = {
	// F6 /4 MUL r/m8 A Valid Valid Unsigned multiply (AX AL r/m8).
	// REX + F6 /4 MUL r/m8* A Valid N.E. Unsigned multiply (AX AL r/m8).
	{ NULL, 0x0001, 0x00C5A000, { 0xF6, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_8, _IRA_NA, _IRA_NA, _IRA_NA },
	// F7 /4 MUL r/m16 A Valid Valid Unsigned multiply (DX:AX AX r/m16).
	// F7 /4 MUL r/m32 A Valid Valid Unsigned multiply (EDX:EAX EAX r/m32).
	// REX.W + F7 /4 MUL r/m64 A Valid N.E. Unsigned multiply (RDX:RAX RAX r/m64.
	{ NULL, 0x0001, 0x00C5A000, { 0xF7, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM, _IRA_NA, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_MULPD[] = {
	// 66 0F 59 /r MULPD xmm1, xmm2/m128 A Valid Valid Multiply packed doubleprecision floating-point values in xmm2/m128 by xmm1.
	{ NULL, 0x1001, 0x00D88000, { 0x0F, 0x59, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA },
	// VEX.NDS.128.66.0F 59 /r VMULPD xmm1,xmm2,xmm3/m128
	// VEX.NDS.256.66.0F 59 /r VMULPD ymm1,ymm2,ymm3/m256
	{ "vmulpd", 0x1080, 0x00D88000, { 0x0F, 0x59, 0x00 }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_SIMD, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_MULPS[] = {
	// 0F 59 /r MULPS xmm1, xmm2/m128 A Valid Valid Multiply packed singleprecision floating-point values in xmm2/mem by xmm1.
	{ NULL, 0x0001, 0x00D88000, { 0x0F, 0x59, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA },
	// VEX.NDS.128.0F 59 /r VMULPS xmm1,xmm2,xmm3/m128
	// VEX.NDS.256.0F 59 /r VMULPS ymm1,ymm2,ymm3/m256
	{ "vmulps", 0x0080, 0x00D88000, { 0x0F, 0x59, 0x00 }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_SIMD, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_MULSD[] = {
	// F2 0F 59 /r MULSD xmm1, xmm2/m64 A Valid Valid Multiply the low doubleprecision floating-point value in xmm2/mem64 by low double-precision floating-point value in xmm1.
	{ NULL, 0x2001, 0x00D88000, { 0x0F, 0x59, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_64, _IRA_NA, _IRA_NA },
	// VEX.NDS.128.F2.0F 59 /r VMULSD xmm1,xmm2,xmm3/m64
	{ "vmulsd", 0x20C0, 0x00D88000, { 0x0F, 0x59, 0x00 }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_SIMD_64, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_MULSS[] = {
	// F3 0F 59 /r MULSS xmm1, xmm2/m32 A Valid Valid Multiply the low singleprecision floating-point value in xmm2/mem by the low single-precision floating-point value in xmm1.
	{ NULL, 0x4001, 0x00D88000, { 0x0F, 0x59, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_32, _IRA_NA, _IRA_NA },
	// VEX.NDS.128.F3.0F 59 /r VMULSS xmm1,xmm2,xmm3/m32
	{ "vmulsd", 0x40C0, 0x00D88000, { 0x0F, 0x59, 0x00 }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_SIMD_32, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_MWAIT[] = {
	// 0F 01 C9 MWAIT A Valid Valid A hint that allow the processor to stop instruction execution and enter an implementationdependent optimized state until occurrence of a class of events.
	{ NULL, 0x0001, 0x00EC8000, { 0x0F, 0x01, 0xC9 }, _IRA_NA, _IRA_NA, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_NEG[] = {
	// F6 /3 NEG r/m8 M Valid Valid Two's complement negate r/m8.
	// REX + F6 /3 NEG r/m8* M Valid N.E. Two's complement negate r/m8.
	{ NULL, 0x0001, 0x00C59800, { 0xF6, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_8_W, _IRA_NA, _IRA_NA, _IRA_NA },
	// F7 /3 NEG r/m16 M Valid Valid Two's complement negate r/m16.
	// F7 /3 NEG r/m32 M Valid Valid Two's complement negate r/m32.
	// REX.W + F7 /3 NEG r/m64 M Valid N.E. Two's complement negate r/m64.
	{ NULL, 0x0001, 0x00C59800, { 0xF7, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_W, _IRA_NA, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_NOP[] = {
	// 90 NOP NP Valid Valid One byte no-operation instruction.
	{ NULL, 0x0001, 0x00C40000, { 0x90, 0x00, 0x00 }, _IRA_NA, _IRA_NA, _IRA_NA, _IRA_NA },
	// 0F 1F /0 NOP r/m16 M Valid Valid Multi-byte no-operation instruction.
	// 0F 1F /0 NOP r/m32 M Valid Valid Multi-byte no-operation instruction.
	{ NULL, 0x0001, 0x00D98000, { 0x0F, 0x1F, 0x00 }, _IRA_OPERAND_MODRM_RM_W, _IRA_NA, _IRA_NA, _IRA_NA },
};

struct ira_opcode_desc _ira_opcode_desc_NOT[] = {
	// F6 /2 NOT r/m8 M Valid Valid Reverse each bit of r/m8.
	// REX + F6 /2 NOT r/m8* M Valid N.E. Reverse each bit of r/m8.
	{ NULL, 0x0001, 0x00C59000, { 0xF6, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_8_W, _IRA_NA, _IRA_NA, _IRA_NA },
	// F7 /2 NOT r/m16 M Valid Valid Reverse each bit of r/m16.
	// F7 /2 NOT r/m32 M Valid Valid Reverse each bit of r/m32.
	// REX.W + F7 /2 NOT r/m64 M Valid N.E. Reverse each bit of r/m64.
	{ NULL, 0x0001, 0x00C59000, { 0xF7, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_W, _IRA_NA, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_OR[] = {
	// 0C ib OR AL, imm8 I Valid Valid AL OR imm8.
	{ NULL, 0x0001, 0x00C40000, { 0x0C, 0x00, 0x00 }, _IRA_OPERAND_REG_ACCUMULATOR_8, _IRA_OPERAND_IB, _IRA_NA, _IRA_NA },
	// 0D iw OR AX, imm16 I Valid Valid AX OR imm16.
	// 0D id OR EAX, imm32 I Valid Valid EAX OR imm32.
	{ NULL, 0x0001, 0x03C40000, { 0x0D, 0x00, 0x00 }, _IRA_OPERAND_REG_ACCUMULATOR_OSA_W, _IRA_OPERAND_IMM_EOSA, _IRA_NA, _IRA_NA },
	// REX.W + 0D id OR RAX, imm32 I Valid N.E. RAX OR imm32 (sign-extended).
	{ NULL, 0x0001, 0x04840000, { 0x0D, 0x00, 0x00 }, _IRA_OPERAND_REG_ACCUMULATOR_OSA_W, _IRA_OPERAND_ID_EX_EOSA, _IRA_NA, _IRA_NA },
	// 80 /1 ib OR r/m8, imm8 MI Valid Valid r/m8 OR imm8.
	// REX + 80 /1 ib OR r/m8*, imm8 MI Valid N.E. r/m8 OR imm8.
	{ NULL, 0x0001, 0x00C58800, { 0x80, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_8_W, _IRA_OPERAND_IB, _IRA_NA, _IRA_NA },
	// 81 /1 iw OR r/m16, imm16 MI Valid Valid r/m16 OR imm16.
	// 81 /1 id OR r/m32, imm32 MI Valid Valid r/m32 OR imm32.
	{ NULL, 0x0001, 0x03C58800, { 0x81, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_W, _IRA_OPERAND_IMM_EOSA, _IRA_NA, _IRA_NA },
	// REX.W + 81 /1 id OR r/m64, imm32 MI Valid N.E. r/m64 OR imm32 (sign-extended).
	{ NULL, 0x0001, 0x04858800, { 0x81, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_W, _IRA_OPERAND_ID_EX_EOSA, _IRA_NA, _IRA_NA },
	// 83 /1 ib OR r/m16, imm8 MI Valid Valid r/m16 OR imm8 (sign-extended).
	// 83 /1 ib OR r/m32, imm8 MI Valid Valid r/m32 OR imm8 (sign-extended).
	{ NULL, 0x0001, 0x03C58800, { 0x83, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_W, _IRA_OPERAND_IB_EX_EOSA, _IRA_NA, _IRA_NA },
	// REX.W + 83 /1 ib OR r/m64, imm8 MI Valid N.E. r/m64 OR imm8 (sign-extended).
	{ NULL, 0x0001, 0x04858800, { 0x83, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_W, _IRA_OPERAND_IB_EX_EOSA, _IRA_NA, _IRA_NA },
	// 08 /r OR r/m8, r8 MR Valid Valid r/m8 OR r8.
	// REX + 08 /r OR r/m8*, r8* MR Valid N.E. r/m8 OR r8.
	{ NULL, 0x0001, 0x00C48000, { 0x08, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_8_W, _IRA_OPERAND_MODRM_R_8, _IRA_NA, _IRA_NA },
	// 09 /r OR r/m16, r16 MR Valid Valid r/m16 OR r16.
	// 09 /r OR r/m32, r32 MR Valid Valid r/m32 OR r32.
	// REX.W + 09 /r OR r/m64, r64 MR Valid N.E. r/m64 OR r64.
	{ NULL, 0x0001, 0x00C48000, { 0x09, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_W, _IRA_OPERAND_MODRM_R, _IRA_NA, _IRA_NA },
	// 0A /r OR r8, r/m8 RM Valid Valid r8 OR r/m8.
	// REX + 0A /r OR r8*, r/m8* RM Valid N.E. r8 OR r/m8.
	{ NULL, 0x0001, 0x00C48000, { 0x0A, 0x00, 0x00 }, _IRA_OPERAND_MODRM_R_8_W, _IRA_OPERAND_MODRM_RM_8, _IRA_NA, _IRA_NA },
	// 0B /r OR r16, r/m16 RM Valid Valid r16 OR r/m16.
	// 0B /r OR r32, r/m32 RM Valid Valid r32 OR r/m32.
	// REX.W + 0B /r OR r64, r/m64 RM Valid N.E. r64 OR r/m64.
	{ NULL, 0x0001, 0x00C48000, { 0x0B, 0x00, 0x00 }, _IRA_OPERAND_MODRM_R_W, _IRA_OPERAND_MODRM_RM, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_ORPD[] = {
	// 66 0F 56 /r ORPD xmm1,xmm2/m128
	{ NULL, 0x1001, 0x00D88000, { 0x0F, 0x56, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA },
	// VEX.NDS.128.66.0F 56 /r VORPD xmm1,xmm2,xmm3/m128
	// VEX.NDS.256.66.0F 56 /r VORPD ymm1,ymm2,ymm3/m256
	{ "vorpd", 0x1080, 0x00D88000, { 0x0F, 0x56, 0x00 }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_SIMD, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_ORPS[] = {
	// 0F 56 /r ORPS xmm1, xmm2/m128
	{ NULL, 0x0001, 0x00D88000, { 0x0F, 0x56, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA },
	// VEX.NDS.128.0F 56 /r VORPS xmm1,xmm2,xmm3/m128
	// VEX.NDS.256.0F 56 /r VORPS ymm1,ymm2,ymm3/m256
	{ "vorps", 0x0080, 0x00D88000, { 0x0F, 0x56, 0x00 }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_SIMD, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_OUT[] = {
	// E6 ib OUT imm8, AL I Valid Valid Output byte in AL to I/O port address imm8.
	{ NULL, 0x0001, 0x07C40000, { 0xE6, 0x00, 0x00 }, _IRA_OPERAND_IB, _IRA_EXPLICIT_REG( IRA_REG_GPR, _IRA_REG_AL, _IRA_OS_BYTE ), _IRA_NA, _IRA_NA },
	// E7 ib OUT imm8, AX I Valid Valid Output word in AX to I/O port address imm8.
	{ NULL, 0x0001, 0x01C40000, { 0xE7, 0x00, 0x00 }, _IRA_OPERAND_IB, _IRA_EXPLICIT_REG( IRA_REG_GPR, _IRA_REG_AL, _IRA_OS_WORD), _IRA_NA, _IRA_NA },
	// E7 ib OUT imm8, EAX I Valid Valid Output doubleword in EAX to I/O port address imm8.
	{ NULL, 0x0001, 0x06C40000, { 0xE7, 0x00, 0x00 }, _IRA_OPERAND_IB, _IRA_EXPLICIT_REG( IRA_REG_GPR, _IRA_REG_AL, _IRA_OS_DWORD), _IRA_NA, _IRA_NA },
	// EE OUT DX, AL NP Valid Valid Output byte in AL to I/O port address in DX.
	{ NULL, 0x0001, 0x07C40000, { 0xEE, 0x00, 0x00 }, _IRA_EXPLICIT_REG( IRA_REG_GPR, _IRA_REG_DX, _IRA_OS_WORD ), _IRA_EXPLICIT_REG( IRA_REG_GPR, _IRA_REG_AL, _IRA_OS_BYTE ), _IRA_NA, _IRA_NA },
	// EF OUT DX, AX NP Valid Valid Output word in AX to I/O port address in DX.
	{ NULL, 0x0001, 0x01C40000, { 0xEF, 0x00, 0x00 }, _IRA_EXPLICIT_REG( IRA_REG_GPR, _IRA_REG_DX, _IRA_OS_WORD ), _IRA_EXPLICIT_REG( IRA_REG_GPR, _IRA_REG_AL, _IRA_OS_WORD ), _IRA_NA, _IRA_NA },
	// EF OUT DX, EAX NP Valid Valid Output doubleword in EAX to I/O port address in DX.
	{ NULL, 0x0001, 0x06C40000, { 0xEF, 0x00, 0x00 }, _IRA_EXPLICIT_REG( IRA_REG_GPR, _IRA_REG_DX, _IRA_OS_WORD ), _IRA_EXPLICIT_REG( IRA_REG_GPR, _IRA_REG_AL, _IRA_OS_DWORD ), _IRA_NA, _IRA_NA }
};


struct ira_opcode_desc _ira_opcode_desc_OUTS[] = {
	// 6E OUTS DX, m8 NP Valid Valid Output byte from memory location specified in DS:(E)SI or RSI to I/O port specified in DX.
	{ NULL, 0x0001, 0x07C40000, { 0x6E, 0x00, 0x00 },
			_IRA_EXPLICIT_REG( IRA_REG_GPR, _IRA_REG_DX, _IRA_OS_WORD ),
			_IRA_EXPLICIT_GPS_REG_ADDRESSING( _IRA_REG_DI, _IRA_EOS_BYTE, _IRA_SEG_ENCODE_REGISTER( _IRA_REG_ES, _IRA_SEG_DENY_OVERRIDE ) ), _IRA_NA, _IRA_NA },
	// 6F OUTS DX, m16 NP Valid Valid Output word from memory location specified in DS:(E)SI or RSI to I/O port specified in DX.
	{ NULL, 0x0001, 0x01C40000, { 0x6F, 0x00, 0x00 },
			_IRA_EXPLICIT_REG( IRA_REG_GPR, _IRA_REG_DX, _IRA_OS_WORD ),
			_IRA_EXPLICIT_GPS_REG_ADDRESSING( _IRA_REG_DI, _IRA_EOS_WORD, _IRA_SEG_ENCODE_REGISTER( _IRA_REG_ES, _IRA_SEG_DENY_OVERRIDE ) ), _IRA_NA, _IRA_NA },
	// 6F OUTS DX, m32 NP Valid Valid Output doubleword from memory location specified in DS:(E)SI or RSI to I/O port specified in DX.
	{ NULL, 0x0001, 0x06C40000, { 0x6F, 0x00, 0x00 },
			_IRA_EXPLICIT_REG( IRA_REG_GPR, _IRA_REG_DX, _IRA_OS_WORD ),
			_IRA_EXPLICIT_GPS_REG_ADDRESSING( _IRA_REG_DI, _IRA_EOS_DWORD, _IRA_SEG_ENCODE_REGISTER( _IRA_REG_ES, _IRA_SEG_DENY_OVERRIDE ) ), _IRA_NA, _IRA_NA }
	// TODO: W przypadku assemblera trzeba to bedzie obsluzyc.
	// 6E OUTSB NP Valid Valid Output byte from memory location specified in DS:(E)SI or RSI to I/O port specified in DX.
	// 6F OUTSW NP Valid Valid Output word from memory location specified in DS:(E)SI or RSI to I/O port specified in DX.
	// 6F OUTSD NP Valid Valid Output doubleword from memory location specified in DS:(E)SI or RSI to I/O port specified in DX.
};

struct ira_opcode_desc _ira_opcode_desc_PABS[] = {
	// 0F 38 1C /r1 PABSB mm1,mm2/m64
	{ "pabsb", 0x0001, 0x00EC8000, { 0x0F, 0x38, 0x1C }, _IRA_OPERAND_MODRM_R_MMX_W, _IRA_OPERAND_MODRM_RM_MMX, _IRA_NA, _IRA_NA },
	// 0F 38 1D /r1 PABSW mm1,mm2/m64
	{ "pabsw", 0x0001, 0x00EC8000, { 0x0F, 0x38, 0x1D }, _IRA_OPERAND_MODRM_R_MMX_W, _IRA_OPERAND_MODRM_RM_MMX, _IRA_NA, _IRA_NA },
	// 0F 38 1E /r1 PABSD mm1,mm2/m64
	{ "pabsd", 0x0001, 0x00EC8000, { 0x0F, 0x38, 0x1E }, _IRA_OPERAND_MODRM_R_MMX_W, _IRA_OPERAND_MODRM_RM_MMX, _IRA_NA, _IRA_NA },
	// 66 0F 38 1C /r PABSB xmm1,xmm2/m128
	{ "pabsb", 0x1001, 0x00EC8000, { 0x0F, 0x38, 0x1C }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA },
	// 66 0F 38 1D /r PABSW xmm1,xmm2/m128
	{ "pabsw", 0x1001, 0x00EC8000, { 0x0F, 0x38, 0x1D }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA },
	// 66 0F 38 1E /r PABSD xmm1,xmm2/m128
	{ "pabsd", 0x1001, 0x00EC8000, { 0x0F, 0x38, 0x1E }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA },
	// VEX.128.66.0F38 1C /r VPABSB xmm1,xmm2/m128
	{ "vpabsb", 0x11C0, 0x00EC8000, { 0x0F, 0x38, 0x1C }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA },
	// VEX.128.66.0F38 1D /r VPABSW xmm1,xmm2/m128
	{ "vpabsw", 0x11C0, 0x00EC8000, { 0x0F, 0x38, 0x1D }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA },
	// VEX.128.66.0F38 1E /r VPABSD xmm1,xmm2/m128
	{ "vpabsd", 0x11C0, 0x00EC8000, { 0x0F, 0x38, 0x1E }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_PACKSS[] = {
	// 0F 63 /r1 PACKSSWB mm1,mm2/m64
	{ "packsswb", 0x0001, 0x00D88000, { 0x0F, 0x63, 0x00 }, _IRA_OPERAND_MODRM_R_MMX_W, _IRA_OPERAND_MODRM_RM_MMX, _IRA_NA, _IRA_NA },
	// 0F 6B /r1 PACKSSDW mm1,mm2/m64
	{ "packssdw", 0x0001, 0x00D88000, { 0x0F, 0x6B, 0x00 }, _IRA_OPERAND_MODRM_R_MMX_W, _IRA_OPERAND_MODRM_RM_MMX, _IRA_NA, _IRA_NA },
	// 66 0F 63 /r PACKSSWB xmm1,xmm2/m128
	{ "packsswb", 0x1001, 0x00D88000, { 0x0F, 0x63, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA },
	// 66 0F 6B /r PACKSSDW xmm1,xmm2/m128
	{ "packssdw", 0x1001, 0x00D88000, { 0x0F, 0x6B, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA },
	// VEX.NDS.128.66.0F.WIG 63 /r VPACKSSWB xmm1,xmm2,xmm3/m128
	{ "vpacksswb", 0x10C0, 0x00D88000, { 0x0F, 0x63, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA },
	// VEX.NDS.128.66.0F.WIG 6B /r VPACKSSDW xmm1,xmm2,xmm3/m128
	{ "vpackssdw", 0x10C0, 0x00D88000, { 0x0F, 0x6B, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA },
};

struct ira_opcode_desc _ira_opcode_desc_PACKUSD[] = {
	// 66 0F 38 2B /r PACKUSDW xmm1,xmm2/m128
	{ "packusdw", 0x1001, 0x00EC8000, { 0x0F, 0x38, 0x2B }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA },
	// VEX.NDS.128.66.0F38.WIG 2B /r VPACKUSDW xmm1,xmm2,xmm3/m128
	{ "vpackusdw", 0x10C0, 0x00EC8000, { 0x0F, 0x38, 0x2B }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_PACKUSW[] = {
	// 0F 67 /r1 PACKUSWB mm,mm/m64
	{ "packuswb", 0x0001, 0x00D88000, { 0x0F, 0x67, 0x00 }, _IRA_OPERAND_MODRM_R_MMX_W, _IRA_OPERAND_MODRM_RM_MMX, _IRA_NA, _IRA_NA },
	// 66 0F 67 /r PACKUSWB xmm1,xmm2/m128
	{ "packuswb", 0x1001, 0x00D88000, { 0x0F, 0x67, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA },
	// VEX.NDS.128.66.0F.WIG 67 /r VPACKUSWB xmm1,xmm2,xmm3/m128
	{ "vpackuswb", 0x10C0, 0x00D88000, { 0x0F, 0x67, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_PADD[] = {
	// 0F FC /r1 PADDB mm,mm/m64
	{ "paddb", 0x0001, 0x00D88000, { 0x0F, 0xFC, 0x00 }, _IRA_OPERAND_MODRM_R_MMX_W, _IRA_OPERAND_MODRM_RM_MMX, _IRA_NA, _IRA_NA },
	// 0F FD /r1 PADDW mm,mm/m64
	{ "paddw", 0x0001, 0x00D88000, { 0x0F, 0xFD, 0x00 }, _IRA_OPERAND_MODRM_R_MMX_W, _IRA_OPERAND_MODRM_RM_MMX, _IRA_NA, _IRA_NA },
	// 0F FE /r1 PADDD mm,mm/m64
	{ "paddd", 0x0001, 0x00D88000, { 0x0F, 0xFE, 0x00 }, _IRA_OPERAND_MODRM_R_MMX_W, _IRA_OPERAND_MODRM_RM_MMX, _IRA_NA, _IRA_NA },
	// 66 0F FC /r PADDB xmm1,xmm2/m128
	{ "paddb", 0x1001, 0x00D88000, { 0x0F, 0xFC, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA },
	// 66 0F FD /r PADDW xmm1,xmm2/m128
	{ "paddw", 0x1001, 0x00D88000, { 0x0F, 0xFD, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA },
	// 66 0F FE /r PADDD xmm1,xmm2/m128
	{ "paddd", 0x1001, 0x00D88000, { 0x0F, 0xFE, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA },
	// VEX.NDS.128.66.0F.WIG FC /r VPADDB xmm1,xmm2,xmm3/m128
	{ "vpaddb", 0x10C0, 0x00D88000, { 0x0F, 0xFC, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA },
	// VEX.NDS.128.66.0F.WIG FD /r VPADDW xmm1,xmm2,xmm3/m128
	{ "vpaddw", 0x10C0, 0x00D88000, { 0x0F, 0xFD, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA },
	// VEX.NDS.128.66.0F.WIG FE /r VPADDD xmm1,xmm2,xmm3/m128
	{ "vpaddd", 0x10C0, 0x00D88000, { 0x0F, 0xFE, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_PADDS[] = {
	// 0F EC /r1 PADDSB mm,mm/m64
	{ "paddsb", 0x0001, 0x00D88000, { 0x0F, 0xEC, 0x00 }, _IRA_OPERAND_MODRM_R_MMX_W, _IRA_OPERAND_MODRM_RM_MMX, _IRA_NA, _IRA_NA },
	// 0F ED /r1 PADDSW mm,mm/m64
	{ "paddsw", 0x0001, 0x00D88000, { 0x0F, 0xED, 0x00 }, _IRA_OPERAND_MODRM_R_MMX_W, _IRA_OPERAND_MODRM_RM_MMX, _IRA_NA, _IRA_NA },
	// 66 0F EC /r PADDSB xmm1,xmm2/m128
	{ "paddsb", 0x1001, 0x00D88000, { 0x0F, 0xEC, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA },
	// 66 0F ED /r PADDSW xmm1,xmm2/m128
	{ "paddsw", 0x1001, 0x00D88000, { 0x0F, 0xED, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA },
	// VEX.NDS.128.66.0F.WIG EC /r VPADDSB xmm1,xmm2,xmm3/m128
	{ "vpaddsb", 0x10C0, 0x00D88000, { 0x0F, 0xEC, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA },
	// VEX.NDS.128.66.0F.WIG ED /r VPADDSW xmm1,xmm2,xmm3/m128
	{ "vpaddsw", 0x10C0, 0x00D88000, { 0x0F, 0xED, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_PADDUS[] = {
	// 0F DC /r1 PADDUSB mm,mm/m64
	{ "paddusb", 0x0001, 0x00D88000, { 0x0F, 0xDC, 0x00 }, _IRA_OPERAND_MODRM_R_MMX_W, _IRA_OPERAND_MODRM_RM_MMX, _IRA_NA, _IRA_NA },
	// 0F DD /r1 PADDUSW mm,mm/m64
	{ "paddusw", 0x0001, 0x00D88000, { 0x0F, 0xDD, 0x00 }, _IRA_OPERAND_MODRM_R_MMX_W, _IRA_OPERAND_MODRM_RM_MMX, _IRA_NA, _IRA_NA },
	// 66 0F DC /r PADDUSB xmm1,xmm2/m128
	{ "paddusb", 0x1001, 0x00D88000, { 0x0F, 0xDC, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA },
	// 66 0F DD /r PADDUSW xmm1,xmm2/m128
	{ "paddusw", 0x1001, 0x00D88000, { 0x0F, 0xDD, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA },
	// VEX.NDS.128.660F.WIG DC /r VPADDUSB xmm1,xmm2,xmm3/m128
	{ "vpaddusb", 0x10C0, 0x00D88000, { 0x0F, 0xDC, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA },
	// VEX.NDS.128.66.0F.WIG DD /r VPADDUSW xmm1,xmm2,xmm3/m128
	{ "vpaddusw", 0x10C0, 0x00D88000, { 0x0F, 0xDD, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_PALIGNR[] = {
	// 0F 3A 0F PALIGNR mm1,mm2/m64,imm8
	{ NULL, 0x0001, 0x00EC8000, { 0x0F, 0x3A, 0x00F }, _IRA_OPERAND_MODRM_R_MMX_W, _IRA_OPERAND_MODRM_RM_MMX, _IRA_OPERAND_IB, _IRA_NA },
	// 66 0F 3A 0F PALIGNR xmm1,xmm2/m128,imm8
	{ NULL, 0x1001, 0x00EC8000, { 0x0F, 0x3A, 0x00F }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_OPERAND_IB, _IRA_NA },
	// VEX.NDS.128.66.0F3A.WIG 0F /r ib VPALIGNR xmm1,xmm2,xmm3/m128,imm8
	{ "vpalignr", 0x10C0, 0x00EC8000, { 0x0F, 0x3A, 0x0F }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_OPERAND_IB }
};

struct ira_opcode_desc _ira_opcode_desc_PAND[] = {
		// 0F DB /r PAND mm,mm/m64
		{ NULL, 0x0001, 0x00D88000, { 0x0F, 0xDB, 0x00 }, _IRA_OPERAND_MODRM_R_MMX_W, _IRA_OPERAND_MODRM_RM_MMX, _IRA_NA, _IRA_NA },
		// 66 0F DB /r PAND xmm1,xmm2/m128
		{ NULL, 0x1001, 0x00D88000, { 0x0F, 0xDB, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA },
		// VEX.NDS.128.66.0F.WIG DB /r VPAND xmm1,xmm2,xmm3/m128
		{ "vpand", 0x10C0, 0x00D88000, { 0x0F, 0xDB, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_PANDN[] = {
		// 0F DF /r PANDN mm,mm/m64
		{ NULL, 0x0001, 0x00D88000, { 0x0F, 0xDF, 0x00 }, _IRA_OPERAND_MODRM_R_MMX_W, _IRA_OPERAND_MODRM_RM_MMX, _IRA_NA, _IRA_NA },
		// 66 0F DF /r PANDN xmm1,xmm2/m128
		{ NULL, 0x1001, 0x00D88000, { 0x0F, 0xDF, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA },
		// VEX.NDS.128.66.0F.WIG DF /r VPANDN xmm1,xmm2,xmm3/m128
		{ "vpandn", 0x10C0, 0x00D88000, { 0x0F, 0xDF, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_PAUSE[] = {
	// F3 90 PAUSE
	{ NULL, 0x4001, 0x00C40000, { 0x90, 0x00, 0x00 }, _IRA_NA, _IRA_NA, _IRA_NA, _IRA_NA },
};

struct ira_opcode_desc _ira_opcode_desc_PAVG[] = {
	// 0F E0 /r1 PAVGB mm1,mm2/m64
	{ "pavgb", 0x0001, 0x00D88000, { 0x0F, 0xE0, 0x00 }, _IRA_OPERAND_MODRM_R_MMX_W, _IRA_OPERAND_MODRM_RM_MMX, _IRA_NA, _IRA_NA },
	// 0F E3 /r1 PAVGW mm1,mm2/m64
	{ "pavgw", 0x0001, 0x00D88000, { 0x0F, 0xE3, 0x00 }, _IRA_OPERAND_MODRM_R_MMX_W, _IRA_OPERAND_MODRM_RM_MMX, _IRA_NA, _IRA_NA },
	// 66 0F E0, /r PAVGB xmm1,xmm2/m128
	{ "pavgb", 0x1001, 0x00D88000, { 0x0F, 0xE0, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA },
	// 66 0F E3 /r PAVGW xmm1,xmm2/m128
	{ "pavgw", 0x1001, 0x00D88000, { 0x0F, 0xE3, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA },
	// VEX.NDS.128.66.0F.WIG E0 /r VPAVGB xmm1,xmm2,xmm3/m128
	{ "vpavgb", 0x10C0, 0x00D88000, { 0x0F, 0xE0, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA },
	// VEX.NDS.128.66.0F.WIG E3 /r VPAVGW xmm1,xmm2,xmm3/m128
	{ "vpavgw", 0x10C0, 0x00D88000, { 0x0F, 0xE3, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_PBLENDVB[] = {
	// 66 0F 38 10 /r PBLENDVB xmm1,xmm2/m128,<XMM0>
	{ NULL, 0x1001, 0x00EC8000, { 0x0F, 0x38, 0x10 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_EXPLICIT_REG( IRA_REG_SIMD, _IRA_REG_XMM0, _IRA_OS_XMMWORD ), _IRA_NA },
	// VEX.NDS.128.66.0F3A 4C /r /is4 VPBLENDVB xmm1,xmm2,xmm3/m128,xmm4
	{ "vpblendvb", 0x10C0, 0x00EC8000, { 0x0F, 0x3A, 0x4C }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_SIMD, _IRA_OPERAND_IS4 }
};

struct ira_opcode_desc _ira_opcode_desc_PBLENDW[] = {
	// 66 0F 3A 0E /r ib PBLENDW xmm1,xmm2/m128,imm8
	{ NULL, 0x1001, 0x00EC8000, { 0x0F, 0x3A, 0x0E }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_OPERAND_IB, _IRA_NA },
	// VEX.NDS.128.66.0F3A 0E /r ib VPBLENDW xmm1,xmm2,xmm3/m128,imm8
	{ "vpblendw", 0x10C0, 0x00EC8000, { 0x0F, 0x3A, 0x0E }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_OPERAND_IB }
};

struct ira_opcode_desc _ira_opcode_desc_PCLMULQDQ[] = {
	// 66 0F 3A 44 /r ib PCLMULQDQ xmm1,xmm2/m128,imm8
	{ NULL, 0x1001, 0x00EC8000, { 0x0F, 0x3A, 0x44 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_OPERAND_IB, _IRA_NA },
	// VEX.NDS.128.66.0F3A 44 /r ib VPCLMULQDQ xmm1,xmm2,xmm3/m128,imm8
	{ "vpclmulqdq", 0x10C0, 0x00EC8000, { 0x0F, 0x3A, 0x44 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_OPERAND_IB }
};

struct ira_opcode_desc _ira_opcode_desc_PCMPEQ[] = {
	// 0F 74 /r1 PCMPEQB mm,mm/m64
	{ "pcmpeqb", 0x0001, 0x00D88000, { 0x0F, 0x74, 0x00 }, _IRA_OPERAND_MODRM_R_MMX_W, _IRA_OPERAND_MODRM_RM_MMX, _IRA_NA, _IRA_NA },
	// 0F 75 /r1 PCMPEQW mm,mm/m64
	{ "pcmpeqw", 0x0001, 0x00D88000, { 0x0F, 0x75, 0x00 }, _IRA_OPERAND_MODRM_R_MMX_W, _IRA_OPERAND_MODRM_RM_MMX, _IRA_NA, _IRA_NA },
	// 0F 76 /r1 PCMPEQD mm,mm/m64
	{ "pcmpeqd", 0x0001, 0x00D88000, { 0x0F, 0x76, 0x00 }, _IRA_OPERAND_MODRM_R_MMX_W, _IRA_OPERAND_MODRM_RM_MMX, _IRA_NA, _IRA_NA },
	// 66 0F 74 /r PCMPEQB xmm1,xmm2/m128
	{ "pcmpeqb", 0x1001, 0x00D88000, { 0x0F, 0x74, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA },
	// 66 0F 75 /r PCMPEQW xmm1,xmm2/m128
	{ "pcmpeqw", 0x1001, 0x00D88000, { 0x0F, 0x75, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA },
	// 66 0F 76 /r PCMPEQD xmm1,xmm2/m128
	{ "pcmpeqd", 0x1001, 0x00D88000, { 0x0F, 0x76, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA },
	// VEX.NDS.128.66.0F.WIG 74 /r VPCMPEQB xmm1,xmm2,xmm3/m128
	{ "vpcmpeqb", 0x10C0, 0x00D88000, { 0x0F, 0x74, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA },
	// VEX.NDS.128.66.0F.WIG 75 /r VPCMPEQW xmm1,xmm2,xmm3/m128
	{ "vpcmpeqw", 0x10C0, 0x00D88000, { 0x0F, 0x75, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA },
	// VEX.NDS.128.66.0F.WIG 76 /r VPCMPEQD xmm1,xmm2,xmm3/m128
	{ "vpcmpeqd", 0x10C0, 0x00D88000, { 0x0F, 0x76, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_PCMPEQQ[] = {
	// 66 0F 38 29 /r PCMPEQQ xmm1,xmm2/m128
	{ NULL, 0x1001, 0x00EC8000, { 0x0F, 0x38, 0x29 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA },
	// VEX.NDS.128.66.0F38.WIG 29 /r VPCMPEQQ xmm1,xmm2,xmm3/m128
	{ "vpcmpeqq", 0x10C0, 0x00EC8000, { 0x0F, 0x38, 0x29 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_PCMPESTRI[] = {
	// 66 0F 3A 61 /r imm8 PCMPESTRI xmm1,xmm2/m128,imm8
	{ NULL, 0x1001, 0x00EC8000, { 0x0F, 0x3A, 0x61 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_OPERAND_IB, _IRA_NA },
	// VEX.128.66.0F3A.WIG 61 /r ib VPCMPESTRI xmm1,xmm2/m128,imm8
	{ "vpcmpestri", 0x11C0, 0x00EC8000, { 0x0F, 0x3A, 0x61 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_OPERAND_IB, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_PCMPESTRM[] = {
	// 66 0F 3A 60 /r imm8 PCMPESTRM xmm1,xmm2/m128,imm8
	{ NULL, 0x1001, 0x00EC8000, { 0x0F, 0x3A, 0x60 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_OPERAND_IB, _IRA_NA },
	// VEX.128.66.0F3A.WIG 60 /r ib VPCMPESTRM xmm1,xmm2/m128,imm8
	{ "vpcmpestrm", 0x11C0, 0x00EC8000, { 0x0F, 0x3A, 0x60 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_OPERAND_IB, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_PCMPGT[] = {
	// 0F 64 /r1 PCMPGTB mm,mm/m64
	// 0F 65 /r1 PCMPGTW mm,mm/m64
	// 0F 66 /r1 PCMPGTD mm,mm/m64
	{ "pcmpgtb", 0x0001, 0x00D88000, { 0x0F, 0x64, 0x00 }, _IRA_OPERAND_MODRM_R_MMX_W, _IRA_OPERAND_MODRM_RM_MMX, _IRA_NA, _IRA_NA },
	{ "pcmpgtw", 0x0001, 0x00D88000, { 0x0F, 0x65, 0x00 }, _IRA_OPERAND_MODRM_R_MMX_W, _IRA_OPERAND_MODRM_RM_MMX, _IRA_NA, _IRA_NA },
	{ "pcmpgtd", 0x0001, 0x00D88000, { 0x0F, 0x66, 0x00 }, _IRA_OPERAND_MODRM_R_MMX_W, _IRA_OPERAND_MODRM_RM_MMX, _IRA_NA, _IRA_NA },
	// 66 0F 64 /r PCMPGTB xmm1,xmm2/m128
	// 66 0F 65 /r PCMPGTW xmm1,xmm2/m128
	// 66 0F 66 /r PCMPGTD xmm1,xmm2/m128
	{ "pcmpgtb", 0x1001, 0x00D88000, { 0x0F, 0x64, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA },
	{ "pcmpgtw", 0x1001, 0x00D88000, { 0x0F, 0x65, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA },
	{ "pcmpgtd", 0x1001, 0x00D88000, { 0x0F, 0x66, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA },
	// VEX.NDS.128.66.0F.WIG 64 /r VPCMPGTB xmm1,xmm2,xmm3/m128
	// VEX.NDS.128.66.0F.WIG 65 /r VPCMPGTW xmm1,xmm2,xmm3/m128
	// VEX.NDS.128.66.0F.WIG 66 /r VPCMPGTD xmm1,xmm2,xmm3/m128
	{ "vpcmpgtb", 0x10C0, 0x00D88000, { 0x0F, 0x64, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA },
	{ "vpcmpgtw", 0x10C0, 0x00D88000, { 0x0F, 0x65, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA },
	{ "vpcmpgtd", 0x10C0, 0x00D88000, { 0x0F, 0x66, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_PCMPGTQ[] = {
	// 66 0F 38 37 /r PCMPGTQ xmm1,xmm2/m128
	{ NULL, 0x1001, 0x00EC8000, { 0x0F, 0x38, 0x37 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA },
	// VEX.NDS.128.66.0F38.WIG 37 /r VPCMPGTQ xmm1,xmm2,xmm3/m128
	{ "vpcmpgtq", 0x10C0, 0x00EC8000, { 0x0F, 0x38, 0x37 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_PCMPISTRI[] = {
	// 66 0F 3A 63 /r imm8 PCMPISTRI xmm1,xmm2/m128,imm8
	{ NULL, 0x1001, 0x00EC8000, { 0x0F, 0x3A, 0x63 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_OPERAND_IB, _IRA_NA },
	// VEX.128.66.0F3A.WIG 63 /r ib VPCMPISTRI xmm1,xmm2/m128,imm8
	{ "vpcmpistri", 0x11C0, 0x00EC8000, { 0x0F, 0x3A, 0x63 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_OPERAND_IB, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_PCMPISTRM[] = {
	// 66 0F 3A 62 /r imm8 PCMPISTRM xmm1,xmm2/m128,imm8
	{ NULL, 0x1001, 0x00EC8000, { 0x0F, 0x3A, 0x62 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_OPERAND_IB, _IRA_NA },
	// VEX.128.66.0F3A.WIG 62 /r ib VPCMPISTRM xmm1,xmm2/m128,imm8
	{ "vpcmpistrm", 0x11C0, 0x00EC8000, { 0x0F, 0x3A, 0x62 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_OPERAND_IB, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_PEXTR[] = {
	// 66 0F 3A 14 /r ib PEXTRB reg/m8,xmm2,imm8
	{ "pextrb", 0x1001, 0x40EC8000, { 0x0F, 0x3A, 0x14 }, _IRA_OPERAND_RM(IRA_REG_GPR, _IRA_EOS_EOSA, _IRA_EOS_BYTE, _IRA_RMF_RM ), _IRA_OPERAND_MODRM_R_XMM, _IRA_OPERAND_IB, _IRA_NA },
	// 66 0F 3A 16 /r ib PEXTRD r/m32, xmm2, imm8
	{ "pextrd", 0x1001, 0x40EC8000, { 0x0F, 0x3A, 0x16 }, _IRA_OPERAND_RM(IRA_REG_GPR, _IRA_EOS_EOSA, _IRA_EOS_DWORD, _IRA_RMF_RM ), _IRA_OPERAND_MODRM_R_XMM, _IRA_OPERAND_IB, _IRA_NA },
	// 66 REX.W 0F 3A 16 /r ib PEXTRQ r/m64, xmm2, imm8
	{ "pextrq", 0x1009, 0x04AC8000, { 0x0F, 0x3A, 0x16 }, _IRA_OPERAND_RM(IRA_REG_GPR, _IRA_EOS_QWORD, _IRA_EOS_QWORD, _IRA_RMF_RM ), _IRA_OPERAND_MODRM_R_XMM, _IRA_OPERAND_IB, _IRA_NA },
	// VEX.128.66.0F3A.W0 14 /r ib VPEXTRB reg/m8, xmm2, imm8
	{ "vpextrb", 0x13C0, 0x40EC8000, { 0x0F, 0x3A, 0x14 }, _IRA_OPERAND_RM(IRA_REG_GPR, _IRA_EOS_EOSA, _IRA_EOS_BYTE, _IRA_RMF_RM ), _IRA_OPERAND_MODRM_R_XMM, _IRA_OPERAND_IB, _IRA_NA },
	// VEX.128.66.0F3A.W0 16 /r ib VPEXTRD r32/m32, xmm2, imm8
	{ "vpextrd", 0x13D0, 0x40EC8000, { 0x0F, 0x3A, 0x16 }, _IRA_OPERAND_RM(IRA_REG_GPR, _IRA_EOS_EOSA, _IRA_EOS_DWORD, _IRA_RMF_RM ), _IRA_OPERAND_MODRM_R_XMM, _IRA_OPERAND_IB, _IRA_NA },
	// VEX.128.66.0F3A.W1 16 /r ib VPEXTRQ r64/m64, xmm2, imm8
	{ "vpextrq", 0x11C8, 0x04AC8000, { 0x0F, 0x3A, 0x16 }, _IRA_OPERAND_RM(IRA_REG_GPR, _IRA_EOS_QWORD, _IRA_EOS_QWORD, _IRA_RMF_RM ), _IRA_OPERAND_MODRM_R_XMM, _IRA_OPERAND_IB, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_PEXTRW[] = {
	// 0F C5 /r ib PEXTRW reg,mm,imm8
	{ NULL, 0x0001, 0x40DA8000, { 0x0F, 0xC5, 0x00 }, _IRA_OPERAND_R(IRA_REG_GPR, _IRA_OS_EOSA), _IRA_OPERAND_RM(IRA_REG_SIMD, _IRA_EOS_MMWORD, _IRA_EOS_UNDEFINED, _IRA_RMF_R ), _IRA_OPERAND_IB, _IRA_NA },
	// 66 0F C5 /r ib PEXTRW reg,xmm,imm8
	{ NULL, 0x1001, 0x40DA8000, { 0x0F, 0xC5, 0x00 }, _IRA_OPERAND_R(IRA_REG_GPR, _IRA_OS_EOSA), _IRA_OPERAND_RM(IRA_REG_SIMD, _IRA_EOS_XMMWORD, _IRA_EOS_UNDEFINED, _IRA_RMF_R ), _IRA_OPERAND_IB, _IRA_NA },
	// 66 0F 3A 15 /r ib PEXTRW reg/m16,xmm,imm8
	{ NULL, 0x1001, 0x40EC8000, { 0x0F, 0x3A, 0x15 }, _IRA_OPERAND_RM(IRA_REG_GPR, _IRA_EOS_EOSA, _IRA_EOS_WORD, _IRA_RMF_RM ), _IRA_OPERAND_R(IRA_REG_SIMD, _IRA_OS_XMMWORD), _IRA_OPERAND_IB, _IRA_NA },
	// VEX.128.66.0F.W0 C5 /r ib VPEXTRW reg,xmm1,imm8
	{ "vpextrw", 0x13C1, 0x40DA8000, { 0x0F, 0xC5, 0x00 }, _IRA_OPERAND_R(IRA_REG_GPR, _IRA_OS_EOSA), _IRA_OPERAND_RM(IRA_REG_SIMD, _IRA_EOS_XMMWORD, _IRA_EOS_UNDEFINED, _IRA_RMF_R ), _IRA_OPERAND_IB, _IRA_NA },
	// VEX.128.66.0F3A.W0 15 /r ib VPEXTRW reg/m16,xmm2,imm8
	{ "vpextrw", 0x13C1, 0x40EC8000, { 0x0F, 0x3A, 0x15 }, _IRA_OPERAND_RM(IRA_REG_GPR, _IRA_EOS_EOSA, _IRA_EOS_WORD, _IRA_RMF_RM ), _IRA_OPERAND_R(IRA_REG_SIMD, _IRA_OS_XMMWORD), _IRA_OPERAND_IB, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_PHADD[] = {
	// 0F 38 01 /r PHADDW mm1,mm2/m64
	{ "phaddw", 0x0001, 0x00EC8000, { 0x0F, 0x38, 0x01 }, _IRA_OPERAND_MODRM_R_MMX_W, _IRA_OPERAND_MODRM_RM_MMX, _IRA_NA, _IRA_NA },
	// 0F 38 02 /r PHADDD mm1,mm2/m64
	{ "phaddd", 0x0001, 0x00EC8000, { 0x0F, 0x38, 0x02 }, _IRA_OPERAND_MODRM_R_MMX_W, _IRA_OPERAND_MODRM_RM_MMX, _IRA_NA, _IRA_NA },
	// 66 0F 38 01 /r PHADDW xmm1,xmm2/m128
	{ "phaddw", 0x1001, 0x00EC8000, { 0x0F, 0x38, 0x01 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA },
	// 66 0F 38 02 /r PHADDD xmm1,xmm2/m128
	{ "phaddd", 0x1001, 0x00EC8000, { 0x0F, 0x38, 0x02 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA },
	// VEX.NDS.128.66.0F38.WIG 01 /r VPHADDW xmm1,xmm2,xmm3/m128
	{ "vphaddw", 0x10C0, 0x00EC8000, { 0x0F, 0x38, 0x01 }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_SIMD_128, _IRA_NA },
	// VEX.NDS.128.66.0F38.WIG 02 /r VPHADDD xmm1,xmm2,xmm3/m128
	{ "vphaddd", 0x10C0, 0x00EC8000, { 0x0F, 0x38, 0x02 }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_SIMD_128, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_PHADDSW[] = {
	// 0F 38 03 /r PHADDSW mm1,mm2/m64
	{ NULL, 0x0001, 0x00EC8000, { 0x0F, 0x38, 0x03 }, _IRA_OPERAND_MODRM_R_MMX_W, _IRA_OPERAND_MODRM_RM_MMX, _IRA_NA, _IRA_NA },
	// 66 0F 38 03 /r PHADDSW xmm1,xmm2/m128
	{ NULL, 0x1001, 0x00EC8000, { 0x0F, 0x38, 0x03 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA },
	// VEX.NDS.128.66.0F38.WIG 03 /r VPHADDSW xmm1,xmm2,xmm3/m128
	{ "vphaddsw", 0x10C0, 0x00EC8000, { 0x0F, 0x38, 0x03 }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_SIMD_128, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_PHMINPOSUW[] = {
	// 66 0F 38 41 /r PHMINPOSUW xmm1,xmm2/m128
	{ NULL, 0x1001, 0x00EC8000, { 0x0F, 0x38, 0x41 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA },
	// VEX.128.66.0F38.WIG 41 /r VPHMINPOSUW xmm1,xmm2/m128
	{ "vphminposuw", 0x11C0, 0x00EC8000, { 0x0F, 0x38, 0x41 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA },
};

struct ira_opcode_desc _ira_opcode_desc_PHSUB[] = {
	// 0F 38 05 /r1 PHSUBW mm1,mm2/m64
	{ "phsubw", 0x0001, 0x00EC8000, { 0x0F, 0x38, 0x05 }, _IRA_OPERAND_MODRM_R_MMX_W, _IRA_OPERAND_MODRM_RM_MMX, _IRA_NA, _IRA_NA },
	// 0F 38 06 /r PHSUBD mm1,mm2/m64
	{ "phsubd", 0x0001, 0x00EC8000, { 0x0F, 0x38, 0x06 }, _IRA_OPERAND_MODRM_R_MMX_W, _IRA_OPERAND_MODRM_RM_MMX, _IRA_NA, _IRA_NA },
	// 66 0F 38 05 /r PHSUBW xmm1,xmm2/m128
	{ "phsubw", 0x1001, 0x00EC8000, { 0x0F, 0x38, 0x05 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA },
	// 66 0F 38 06 /r PHSUBD xmm1,xmm2/m128
	{ "phsubd", 0x1001, 0x00EC8000, { 0x0F, 0x38, 0x06 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA },
	// VEX.NDS.128.66.0F38.WIG 05 /r VPHSUBW xmm1,xmm2,xmm3/m128
	{ "vphsubw", 0x10C0, 0x00EC8000, { 0x0F, 0x38, 0x05 }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_SIMD_128, _IRA_NA },
	// VEX.NDS.128.66.0F38.WIG 06 /r VPHSUBD xmm1,xmm2,xmm3/m128
	{ "vphsubd", 0x10C0, 0x00EC8000, { 0x0F, 0x38, 0x06 }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_SIMD_128, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_PHSUBSW[] = {
	// 0F 38 07 /r PHSUBSW mm1,mm2/m64
	{ NULL, 0x0001, 0x00EC8000, { 0x0F, 0x38, 0x07 }, _IRA_OPERAND_MODRM_R_MMX_W, _IRA_OPERAND_MODRM_RM_MMX, _IRA_NA, _IRA_NA },
	// 66 0F 38 07 /r PHSUBSW xmm1,xmm2/m128
	{ NULL, 0x1001, 0x00EC8000, { 0x0F, 0x38, 0x07 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA },
	// VEX.NDS.128.66.0F38.WIG 07 /r VPHSUBSW xmm1,xmm2,xmm3/m128
	{ "vphsubsw", 0x10C0, 0x00EC8000, { 0x0F, 0x38, 0x07 }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_SIMD_128, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_PINSR[] = {
	// 66 0F 3A 20 /r ib PINSRB xmm1,r32/m8,imm8
	{ "pinsrb", 0x1001, 0x00EC8000, { 0x0F, 0x3A, 0x20 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_RM(IRA_REG_GPR, _IRA_EOS_DWORD, _IRA_EOS_BYTE, _IRA_RMF_RM ), _IRA_OPERAND_IB, _IRA_NA },
	// 66 0F 3A 22 /r ib PINSRD xmm1,r/m32,imm8
	{ "pinsrd", 0x1001, 0x03EC8000, { 0x0F, 0x3A, 0x22 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_32, _IRA_OPERAND_IB, _IRA_NA },
	// 66 REX.W 0F 3A 22 /r ib PINSRQ xmm1,r/m64,imm8
	{ "pinsrq", 0x1009, 0x04AC8000, { 0x0F, 0x3A, 0x22 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_64, _IRA_OPERAND_IB, _IRA_NA },
	// VEX.NDS.128.66.0F3A.W0 20 /r ib VPINSRB xmm1,xmm2,r32/m8,imm8
	{ "vpinsrb", 0x10C0, 0x00EC8000, { 0x0F, 0x3A, 0x20 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_RM(IRA_REG_GPR, _IRA_EOS_DWORD, _IRA_EOS_BYTE, _IRA_RMF_RM ), _IRA_OPERAND_IB },
	// VEX.NDS.128.66.0F3A.W0 22 /r ib VPINSRD xmm1,xmm2,r32/m32,imm8
	{ "vpinsrd", 0x10D0, 0x00EC8000, { 0x0F, 0x3A, 0x22 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_32, _IRA_OPERAND_IB },
	// VEX.NDS.128.66.0F3A.W1 22 /r ib VPINSRQ xmm1,xmm2,r64/m64,imm8
	{ "vpinsrq", 0x10C8, 0x00EC8000, { 0x0F, 0x3A, 0x22 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_64, _IRA_OPERAND_IB }
};

struct ira_opcode_desc _ira_opcode_desc_PINSRW[] = {
	// 0F C4 /r ib PINSRW mm,r32/m16,imm8
	{ NULL, 0x0001, 0x00D88000, { 0x0F, 0xC4, 0x00 }, _IRA_OPERAND_MODRM_R_MMX_W, _IRA_OPERAND_RM(IRA_REG_GPR, _IRA_EOS_DWORD, _IRA_EOS_WORD, _IRA_RMF_RM ), _IRA_OPERAND_IB, _IRA_NA },
	// 66 0F C4 /r ib PINSRW xmm,r32/m16,imm8
	{ NULL, 0x1001, 0x00D88000, { 0x0F, 0xC4, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_RM(IRA_REG_GPR, _IRA_EOS_DWORD, _IRA_EOS_WORD, _IRA_RMF_RM ), _IRA_OPERAND_IB, _IRA_NA },
	// VEX.NDS.128.66.0F.W0 C4 /r ib VPINSRW xmm1,xmm2,r32/m16,imm8
	{ "vpinsrw", 0x10C0, 0x00D88000, { 0x0F, 0xC4, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_RM(IRA_REG_GPR, _IRA_EOS_DWORD, _IRA_EOS_WORD, _IRA_RMF_RM ), _IRA_OPERAND_IB }
};

struct ira_opcode_desc _ira_opcode_desc_PMADDUBSW[] = {
	// 0F 38 04 /r PMADDUBSW mm1,mm2/m64
	{ NULL, 0x0001, 0x00EC8000, { 0x0F, 0x38, 0x04 }, _IRA_OPERAND_MODRM_R_MMX_W, _IRA_OPERAND_MODRM_RM_MMX, _IRA_NA, _IRA_NA },
	// 66 0F 38 04 /r PMADDUBSW xmm1,xmm2/m128
	{ NULL, 0x1001, 0x00EC8000, { 0x0F, 0x38, 0x04 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA },
	// VEX.NDS.128.66.0F38.WIG 04 /r VPMADDUBSW xmm1,xmm2,xmm3/m128
	{ "vpmaddubsw", 0x10C0, 0x00EC8000, { 0x0F, 0x38, 0x04 }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_SIMD_128, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_PMADDWD[] = {
	// 0F F5 /r PMADDWD mm,mm/m64
	{ NULL, 0x0001, 0x00D88000, { 0x0F, 0xF5, 0x00 }, _IRA_OPERAND_MODRM_R_MMX_W, _IRA_OPERAND_MODRM_RM_MMX, _IRA_NA, _IRA_NA },
	// 66 0F F5 /r PMADDWD xmm1,xmm2/m128
	{ NULL, 0x1001, 0x00D88000, { 0x0F, 0xF5, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA },
	// VEX.NDS.128.66.0F.WIG F5 /r VPMADDWD xmm1,xmm2,xmm3/m128
	{ "vpmaddwd", 0x10C0, 0x00D88000, { 0x0F, 0xF5, 0x00 }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_SIMD_128, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_PMAXSB[] = {
	// 66 0F 38 3C /r PMAXSB xmm1,xmm2/m128
	{ NULL, 0x1001, 0x00EC8000, { 0x0F, 0x38, 0x3C }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA },
	// VEX.NDS.128.66.0F38.WIG 3C /r VPMAXSB xmm1,xmm2,xmm3/m128
	{ "vpmaxsb", 0x10C0, 0x00EC8000, { 0x0F, 0x38, 0x3C }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_SIMD_128, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_PMAXSD[] = {
	// 66 0F 38 3D /r PMAXSD xmm1,xmm2/m128
	{ NULL, 0x1001, 0x00EC8000, { 0x0F, 0x38, 0x3D }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA },
	// VEX.NDS.128.66.0F38.WIG 3D /r VPMAXSD xmm1,xmm2,xmm3/m128
	{ "vpmaxsd", 0x10C0, 0x00EC8000, { 0x0F, 0x38, 0x3D }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_SIMD_128, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_PMAXSW[] = {
	// 0F EE /r PMAXSW mm1,mm2/m64
	{ NULL, 0x0001, 0x00D88000, { 0x0F, 0xEE, 0x00 }, _IRA_OPERAND_MODRM_R_MMX_W, _IRA_OPERAND_MODRM_RM_MMX, _IRA_NA, _IRA_NA },
	// 66 0F EE /r PMAXSW xmm1,xmm2/m128
	{ NULL, 0x1001, 0x00D88000, { 0x0F, 0xEE, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA },
	// VEX.NDS.128.66.0F.WIG EE /r VPMAXSW xmm1,xmm2,xmm3/m128
	{ "vpmaxsw", 0x10C0, 0x00D88000, { 0x0F, 0xEE, 0x00 }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_SIMD_128, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_PMAXUB[] = {
	// 0F DE /r PMAXUB mm1,mm2/m64
	{ NULL, 0x0001, 0x00D88000, { 0x0F, 0xDE, 0x00 }, _IRA_OPERAND_MODRM_R_MMX_W, _IRA_OPERAND_MODRM_RM_MMX, _IRA_NA, _IRA_NA },
	// 66 0F DE /r PMAXUB xmm1,xmm2/m128
	{ NULL, 0x1001, 0x00D88000, { 0x0F, 0xDE, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA },
	// VEX.NDS.128.66.0F.WIG DE /r VPMAXUB xmm1,xmm2,xmm3/m128
	{ "vpmaxub", 0x10C0, 0x00D88000, { 0x0F, 0xDE, 0x00 }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_SIMD_128, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_PMAXUD[] = {
	// 66 0F 38 3F /r PMAXUD xmm1, xmm2/m128
	{ NULL, 0x1001, 0x00EC8000, { 0x0F, 0x38, 0x3F }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA },
	// VEX.NDS.128.66.0F38.WIG 3F /r VPMAXUD xmm1,xmm2,xmm3/m128
	{ "vpmaxud", 0x10C0, 0x00EC8000, { 0x0F, 0x38, 0x3F }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_SIMD_128, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_PMAXUW[] = {
	// 66 0F 38 3E /r PMAXUW xmm1,xmm2/m128
	{ NULL, 0x1001, 0x00EC8000, { 0x0F, 0x38, 0x3E }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA },
	// VEX.NDS.128.66.0F38.WIG 3E/r VPMAXUW xmm1,xmm2,xmm3/m128
	{ "vpmaxuw", 0x10C0, 0x00EC8000, { 0x0F, 0x38, 0x3E }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_SIMD_128, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_PMINSB[] = {
	// 66 0F 38 38 /r PMINSB xmm1,xmm2/m128
	{ NULL, 0x1001, 0x00EC8000, { 0x0F, 0x38, 0x38 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA },
	// VEX.NDS.128.66.0F38.WIG 38 /r VPMINSB xmm1,xmm2,xmm3/m128
	{ "vpminsb", 0x10C0, 0x00EC8000, { 0x0F, 0x38, 0x38 }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_SIMD_128, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_PMINSD[] = {
	// 66 0F 38 39 /r PMINSD xmm1, xmm2/m128
	{ NULL, 0x1001, 0x00EC8000, { 0x0F, 0x38, 0x39 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA },
	// VEX.NDS.128.66.0F38.WIG 39 /r VPMINSD xmm1, xmm2, xmm3/m128
	{ "vpminsd", 0x10C0, 0x00EC8000, { 0x0F, 0x38, 0x39 }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_SIMD_128, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_PMINSW[] = {
	// 0F EA /r PMINSW mm1,mm2/m64
	{ NULL, 0x0001, 0x00D88000, { 0x0F, 0xEA, 0x00 }, _IRA_OPERAND_MODRM_R_MMX_W, _IRA_OPERAND_MODRM_RM_MMX, _IRA_NA, _IRA_NA },
	// 66 0F EA /r PMINSW xmm1,xmm2/m128
	{ NULL, 0x1001, 0x00D88000, { 0x0F, 0xEA, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA },
	// VEX.NDS.128.66.0F.WIG EA /r VPMINSW xmm1,xmm2,xmm3/m128
	{ "vpminsw", 0x10C0, 0x00D88000, { 0x0F, 0xEA, 0x00 }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_SIMD_128, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_PMINUB[] = {
	// 0F DA /r PMINUB mm1,mm2/m64
	{ NULL, 0x0001, 0x00D88000, { 0x0F, 0xDA, 0x00 }, _IRA_OPERAND_MODRM_R_MMX_W, _IRA_OPERAND_MODRM_RM_MMX, _IRA_NA, _IRA_NA },
	// 66 0F DA /r PMINUB xmm1,xmm2/m128
	{ NULL, 0x1001, 0x00D88000, { 0x0F, 0xDA, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA },
	// VEX.NDS.128.66.0F.WIG DA /r VPMINUB xmm1,xmm2,xmm3/m128
	{ "vpminub", 0x10C0, 0x00D88000, { 0x0F, 0xDA, 0x00 }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_SIMD_128, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_PMINUW[] = {
	// 66 0F 38 3A /r PMINUW xmm1,xmm2/m128
	{ NULL, 0x1001, 0x00EC8000, { 0x0F, 0x38, 0x3A }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA },
	// VEX.NDS.128.66.0F38.WIG 3A /r VPMINUW xmm1,xmm2,xmm3/m128
	{ "vpminuw", 0x10C0, 0x00EC8000, { 0x0F, 0x38, 0x3A }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_SIMD_128, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_PMINUD[] = {
	// 66 0F 38 3B /r PMINUD xmm1,xmm2/m128
	{ NULL, 0x1001, 0x00EC8000, { 0x0F, 0x38, 0x3B }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA },
	// VEX.NDS.128.66.0F38.WIG 3B /r VPMINUD xmm1,xmm2,xmm3/m128
	{ "vpminud", 0x10C0, 0x00EC8000, { 0x0F, 0x38, 0x3B }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_SIMD_128, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_PMOVMSKB[] = {
	// 0F D7 /r1 PMOVMSKB reg, mm
	{ NULL, 0x0001, 0x40DA8000, { 0x0F, 0xD7, 0x00 }, _IRA_OPERAND_R(IRA_REG_GPR, _IRA_OS_EOSA), _IRA_OPERAND_RM(IRA_REG_SIMD, _IRA_EOS_MMWORD, _IRA_EOS_UNDEFINED, _IRA_RMF_R ), _IRA_NA, _IRA_NA },
	// 66 0F D7 /r PMOVMSKB reg, xmm
	{ NULL, 0x1001, 0x40DA8000, { 0x0F, 0xD7, 0x00 }, _IRA_OPERAND_R(IRA_REG_GPR, _IRA_OS_EOSA), _IRA_OPERAND_RM(IRA_REG_SIMD, _IRA_EOS_XMMWORD, _IRA_EOS_UNDEFINED, _IRA_RMF_R ), _IRA_NA, _IRA_NA },
	// VEX.128.66.0F.WIG D7 /r VPMOVMSKB reg, xmm1
	{ "vpmovmskb", 0x13C0, 0x40DA8000, { 0x0F, 0xD7, 0x22 }, _IRA_OPERAND_MODRM_R_W, _IRA_VEX_VVVV_REG, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_PMOVSX[] = {
	// 66 0f 38 20 /r PMOVSXBW xmm1,xmm2/m64
	{ "pmovsxbw", 0x1001, 0x00EC8000, { 0x0F, 0x38, 0x20 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_64, _IRA_NA, _IRA_NA },
	// 66 0f 38 21 /r PMOVSXBD xmm1,xmm2/m32
	{ "pmovsxbd", 0x1001, 0x00EC8000, { 0x0F, 0x38, 0x21 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_32, _IRA_NA, _IRA_NA },
	// 66 0f 38 22 /r PMOVSXBQ xmm1,xmm2/m16
	{ "pmovsxbq", 0x1001, 0x00EC8000, { 0x0F, 0x38, 0x22 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_16, _IRA_NA, _IRA_NA },
	// 66 0f 38 23 /r PMOVSXWD xmm1,xmm2/m64
	{ "pmovsxwd", 0x1001, 0x00EC8000, { 0x0F, 0x38, 0x23 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_64, _IRA_NA, _IRA_NA },
	// 66 0f 38 24 /r PMOVSXWQ xmm1,xmm2/m32
	{ "pmovsxwq", 0x1001, 0x00EC8000, { 0x0F, 0x38, 0x24 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_32, _IRA_NA, _IRA_NA },
	// 66 0f 38 25 /r PMOVSXDQ xmm1,xmm2/m64
	{ "pmovsxdq", 0x1001, 0x00EC8000, { 0x0F, 0x38, 0x25 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_64, _IRA_NA, _IRA_NA },
	// VEX.128.66.0F38.WIG 20 /r VPMOVSXBW xmm1,xmm2/m64
	{ "vpmovsxbw", 0x11C0, 0x00EC8000, { 0x0F, 0x38, 0x20 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_64, _IRA_NA, _IRA_NA },
	// VEX.128.66.0F38.WIG 21 /r VPMOVSXBD xmm1,xmm2/m32
	{ "vpmovsxbd", 0x11C0, 0x00EC8000, { 0x0F, 0x38, 0x21 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_32, _IRA_NA, _IRA_NA },
	// VEX.128.66.0F38.WIG 22 /r VPMOVSXBQ xmm1,xmm2/m16
	{ "vpmovsxbq", 0x11C0, 0x00EC8000, { 0x0F, 0x38, 0x22 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_16, _IRA_NA, _IRA_NA },
	// VEX.128.66.0F38.WIG 23 /r VPMOVSXWD xmm1,xmm2/m64
	{ "vpmovsxwd", 0x11C0, 0x00EC8000, { 0x0F, 0x38, 0x23 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_64, _IRA_NA, _IRA_NA },
	// VEX.128.66.0F38.WIG 24 /r VPMOVSXWQ xmm1,xmm2/m32
	{ "vpmovsxwq", 0x11C0, 0x00EC8000, { 0x0F, 0x38, 0x24 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_32, _IRA_NA, _IRA_NA },
	// VEX.128.66.0F38.WIG 25 /r VPMOVSXDQ xmm1,xmm2/m64
	{ "vpmovsxdq", 0x11C0, 0x00EC8000, { 0x0F, 0x38, 0x25 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_64, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_PMOVZX[] = {
	// 66 0f 38 30 /r PMOVZXBW xmm1,xmm2/m64
	{ "pmovzxbw", 0x1001, 0x00EC8000, { 0x0F, 0x38, 0x30 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_64, _IRA_NA, _IRA_NA },
	// 66 0f 38 31 /r PMOVZXBD xmm1,xmm2/m32
	{ "pmovzxbd", 0x1001, 0x00EC8000, { 0x0F, 0x38, 0x31 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_32, _IRA_NA, _IRA_NA },
	// 66 0f 38 32 /r PMOVZXBQ xmm1,xmm2/m16
	{ "pmovzxbq", 0x1001, 0x00EC8000, { 0x0F, 0x38, 0x32 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_16, _IRA_NA, _IRA_NA },
	// 66 0f 38 33 /r PMOVZXWD xmm1,xmm2/m64
	{ "pmovzxwd", 0x1001, 0x00EC8000, { 0x0F, 0x38, 0x33 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_64, _IRA_NA, _IRA_NA },
	// 66 0f 38 34 /r PMOVZXWQ xmm1,xmm2/m32
	{ "pmovzxwq", 0x1001, 0x00EC8000, { 0x0F, 0x38, 0x34 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_32, _IRA_NA, _IRA_NA },
	// 66 0f 38 35 /r PMOVZXDQ xmm1,xmm2/m64
	{ "pmovzxdq", 0x1001, 0x00EC8000, { 0x0F, 0x38, 0x35 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_64, _IRA_NA, _IRA_NA },
	// VEX.128.66.0F38.WIG 30 /r VPMOVZXBW xmm1,xmm2/m64
	{ "vpmovzxbw", 0x11C0, 0x00EC8000, { 0x0F, 0x38, 0x30 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_64, _IRA_NA, _IRA_NA },
	// VEX.128.66.0F38.WIG 31 /r VPMOVZXBD xmm1,xmm2/m32
	{ "vpmovzxbd", 0x11C0, 0x00EC8000, { 0x0F, 0x38, 0x31 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_32, _IRA_NA, _IRA_NA },
	// VEX.128.66.0F38.WIG 32 /r VPMOVZXBQ xmm1,xmm2/m16
	{ "vpmovzxbq", 0x11C0, 0x00EC8000, { 0x0F, 0x38, 0x32 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_16, _IRA_NA, _IRA_NA },
	// VEX.128.66.0F38.WIG 33 /r VPMOVZXWD xmm1,xmm2/m64
	{ "vpmovzxwd", 0x11C0, 0x00EC8000, { 0x0F, 0x38, 0x33 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_64, _IRA_NA, _IRA_NA },
	// VEX.128.66.0F38.WIG 34 /r VPMOVZXWQ xmm1,xmm2/m32
	{ "vpmovzxwq", 0x11C0, 0x00EC8000, { 0x0F, 0x38, 0x34 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_32, _IRA_NA, _IRA_NA },
	// VEX.128.66.0F38.WIG 35 /r VPMOVZXDQ xmm1,xmm2/m64
	{ "vpmovzxdq", 0x11C0, 0x00EC8000, { 0x0F, 0x38, 0x35 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_64, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_PMULDQ[] = {
	// 66 0F 38 28 /r PMULDQ xmm1,xmm2/m128
	{ NULL, 0x1001, 0x00EC8000, { 0x0F, 0x38, 0x28 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA },
	// VEX.NDS.128.66.0F38.WIG 28 /r VPMULDQ xmm1,xmm2,xmm3/m128
	{ "vpmuldq", 0x10C0, 0x00EC8000, { 0x0F, 0x38, 0x28 }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_SIMD_128, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_PMULHRSW[] = {
	// 0F 38 0B /r PMULHRSW mm1,mm2/m64
	{ NULL, 0x0001, 0x00EC8000, { 0x0F, 0x38, 0x0B }, _IRA_OPERAND_MODRM_R_MMX_W, _IRA_OPERAND_MODRM_RM_MMX, _IRA_NA, _IRA_NA },
	// 66 0F 38 0B /r PMULHRSW xmm1,xmm2/m128
	{ NULL, 0x1001, 0x00EC8000, { 0x0F, 0x38, 0x0B }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA },
	// VEX.NDS.128.66.0F38.WIG 0B /r VPMULHRSW xmm1,xmm2,xmm3/m128
	{ "vpmulhrsw", 0x10C0, 0x00EC8000, { 0x0F, 0x38, 0x0B }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_SIMD_128, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_PMULHUW[] = {
	// 0F E4 /r PMULHUW mm1,mm2/m64
	{ NULL, 0x0001, 0x00D88000, { 0x0F, 0xE4, 0x00 }, _IRA_OPERAND_MODRM_R_MMX_W, _IRA_OPERAND_MODRM_RM_MMX, _IRA_NA, _IRA_NA },
	// 66 0F E4 /r PMULHUW xmm1,xmm2/m128
	{ NULL, 0x1001, 0x00D88000, { 0x0F, 0xE4, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA },
	// VEX.NDS.128.66.0F.WIG E4 /r VPMULHUW xmm1,xmm2,xmm3/m128
	{ "vpmulhuw", 0x10C0, 0x00D88000, { 0x0F, 0xE4, 0x00 }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_SIMD_128, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_PMULHW[] = {
	// 0F E5 /r PMULHW mm,mm/m64
	{ NULL, 0x0001, 0x00D88000, { 0x0F, 0xE5, 0x00 }, _IRA_OPERAND_MODRM_R_MMX_W, _IRA_OPERAND_MODRM_RM_MMX, _IRA_NA, _IRA_NA },
	// 66 0F E5 /r PMULHW xmm1,xmm2/m128
	{ NULL, 0x1001, 0x00D88000, { 0x0F, 0xE5, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA },
	// VEX.NDS.128.66.0F.WIG E5 /r VPMULHW xmm1,xmm2,xmm3/m128
	{ "vpmulhw", 0x10C0, 0x00D88000, { 0x0F, 0xE5, 0x00 }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_SIMD_128, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_PMULUDQ[] = {
	// 0F F4 /r1 PMULUDQ mm1,mm2/m64
	{ NULL, 0x0001, 0x00D88000, { 0x0F, 0xF4, 0x00 }, _IRA_OPERAND_MODRM_R_MMX_W, _IRA_OPERAND_MODRM_RM_MMX, _IRA_NA, _IRA_NA },
	// 66 0F F4 /r PMULUDQ xmm1,xmm2/m128
	{ NULL, 0x1001, 0x00D88000, { 0x0F, 0xF4, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA },
	// VEX.NDS.128.66.0F.WIG F4 /r VPMULUDQ xmm1,xmm2,xmm3/m128
	{ "vpmuludq", 0x10C0, 0x00D88000, { 0x0F, 0xF4, 0x00 }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_SIMD_128, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_PMULLW[] = {
	// 0F D5 /r PMULLW mm,mm/m64
	{ NULL, 0x0001, 0x00D88000, { 0x0F, 0xD5, 0x00 }, _IRA_OPERAND_MODRM_R_MMX_W, _IRA_OPERAND_MODRM_RM_MMX, _IRA_NA, _IRA_NA },
	// 66 0F D5 /r PMULLW xmm1,xmm2/m128
	{ NULL, 0x1001, 0x00D88000, { 0x0F, 0xD5, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA },
	// VEX.NDS.128.66.0F.WIG D5 /r VPMULLW xmm1,xmm2,xmm3/m128
	{ "vpmullw", 0x10C0, 0x00D88000, { 0x0F, 0xD5, 0x00 }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_SIMD_128, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_PMULLD[] = {
	// 66 0F 38 40 /r PMULLD xmm1,xmm2/m128
	{ NULL, 0x1001, 0x00EC8000, { 0x0F, 0x38, 0x40 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA },
	// VEX.NDS.128.66.0F38.WIG 40 /r VPMULLD xmm1,xmm2,xmm3/m128
	{ "vpmulld", 0x10C0, 0x00EC8000, { 0x0F, 0x38, 0x40 }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_SIMD_128, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_POP[] = {
	// 8F /0 POP r/m16 M Valid Valid Pop top of stack into m16; increment stack pointer.
	// 8F /0 POP r/m32 M N.E. Valid Pop top of stack into m32; increment stack pointer.
	// 8F /0 POP r/m64 M Valid N.E. Pop top of stack into m64; increment stack pointer. Cannot encode 32-bit operand size.
	{ NULL, 0x0001, 0x00458000, { 0x8F, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_W, _IRA_NA, _IRA_NA, _IRA_NA },
	{ NULL, 0x0001, 0x01858000, { 0x8F, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_16_W, _IRA_NA, _IRA_NA, _IRA_NA },
	{ NULL, 0x0001, 0x06858000, { 0x8F, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_64_W, _IRA_NA, _IRA_NA, _IRA_NA },
	// 58+ rw POP r16 O Valid Valid Pop top of stack into r16; increment stack pointer.
	// 58+ rd POP r32 O N.E. Valid Pop top of stack into r32; increment stack pointer.
	// 58+ rd POP r64 O Valid N.E. Pop top of stack into r64; increment stack pointer. Cannot encode 32-bit operand size.
	{ NULL, 0x0001, 0x00440000, { 0x58, 0x00, 0x00 }, _IRA_OPERAND_OPCODE_REG( IRA_REG_GPR, _IRA_OS_EOSA), _IRA_NA, _IRA_NA, _IRA_NA },
	{ NULL, 0x0001, 0x01840000, { 0x58, 0x00, 0x00 }, _IRA_OPERAND_OPCODE_REG( IRA_REG_GPR, _IRA_OS_WORD ), _IRA_NA, _IRA_NA, _IRA_NA },
	{ NULL, 0x0001, 0x06840000, { 0x58, 0x00, 0x00 }, _IRA_OPERAND_OPCODE_REG( IRA_REG_GPR, _IRA_OS_QWORD ), _IRA_NA, _IRA_NA, _IRA_NA },
	// 1F POP DS NP Invalid Valid Pop top of stack into DS; increment stack pointer.
	// 07 POP ES NP Invalid Valid Pop top of stack into ES; increment stack pointer.
	// 17 POP SS NP Invalid Valid Pop top of stack into SS; increment stack pointer.
	{ NULL, 0x0001, 0x00440000, { 0x1F, 0x00, 0x00 }, _IRA_EXPLICIT_REG( IRA_REG_SEG, _IRA_REG_DS, _IRA_OS_UNDEFINED ), _IRA_NA, _IRA_NA, _IRA_NA },
	{ NULL, 0x0001, 0x00440000, { 0x07, 0x00, 0x00 }, _IRA_EXPLICIT_REG( IRA_REG_SEG, _IRA_REG_ES, _IRA_OS_UNDEFINED ), _IRA_NA, _IRA_NA, _IRA_NA },
	{ NULL, 0x0001, 0x00440000, { 0x17, 0x00, 0x00 }, _IRA_EXPLICIT_REG( IRA_REG_SEG, _IRA_REG_SS, _IRA_OS_UNDEFINED ), _IRA_NA, _IRA_NA, _IRA_NA },
	// 0F A1 POP FS NP Valid Valid Pop top of stack into FS; increment stack pointer by 16 bits.
	// 0F A1 POP FS NP N.E. Valid Pop top of stack into FS; increment stack pointer by 32 bits.
	// 0F A1 POP FS NP Valid N.E. Pop top of stack into FS; increment stack pointer by 64 bits.
	{ NULL, 0x0001, 0x00D80000, { 0x0F, 0xA1, 0x00 }, _IRA_EXPLICIT_REG( IRA_REG_SEG, _IRA_REG_FS, _IRA_OS_UNDEFINED ), _IRA_NA, _IRA_NA, _IRA_NA },
	// 0F A9 POP GS NP Valid Valid Pop top of stack into GS; increment stack pointer by 16 bits.
	// 0F A9 POP GS NP N.E. Valid Pop top of stack into GS; increment stack pointer by 32 bits.
	// 0F A9 POP GS NP Valid N.E. Pop top of stack into GS; increment stack pointer by 64 bits.
	{ NULL, 0x0001, 0x00D80000, { 0x0F, 0xA9, 0x00 }, _IRA_EXPLICIT_REG( IRA_REG_SEG, _IRA_REG_GS, _IRA_OS_UNDEFINED ), _IRA_NA, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_POPA[] = {
	// 61 POPA NP Invalid Valid Pop DI, SI, BP, BX, DX, CX, and AX.
	{ NULL, 0x0001, 0x01440000, { 0x61, 0x00, 0x00 }, _IRA_NA, _IRA_NA, _IRA_NA, _IRA_NA },
	// 61 POPAD NP Invalid Valid Pop EDI, ESI, EBP, EBX, EDX, ECX, and EAX.
	{ "popad", 0x0001, 0x02440000, { 0x61, 0x00, 0x00 }, _IRA_NA, _IRA_NA, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_POPCNT[] = {
	// F3 0F B8 /r POPCNT r16, r/m16 RM Valid Valid POPCNT on r/m16
	// F3 0F B8 /r POPCNT r32, r/m32 RM Valid Valid POPCNT on r/m32
	// F3 REX.W 0F B8 /r POPCNT r64, r/m64 RM Valid N.E. POPCNT on r/m64
	{ NULL, 0x4000, 0x00D88000, { 0x0F, 0xB8, 0x00 }, _IRA_OPERAND_MODRM_R_W, _IRA_OPERAND_MODRM_RM_W, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_POPF[] = {
	// 9D POPF NP Valid Valid Pop top of stack into lower 16 bits of EFLAGS.
	{ NULL, 0x0000, 0x01C40000, { 0x9D, 0x00, 0x00 }, _IRA_NA, _IRA_NA, _IRA_NA, _IRA_NA },
	// 9D POPFD NP N.E. Valid Pop top of stack into EFLAGS.
	{ "popfd", 0x0000, 0x02440000, { 0x9D, 0x00, 0x00 }, _IRA_NA, _IRA_NA, _IRA_NA, _IRA_NA },
	// REX.W + 9D POPFQ NP Valid N.E. Pop top of stack and zero-extend into RFLAGS.
	{ "popfq", 0x0000, 0x04840000, { 0x9D, 0x00, 0x00 }, _IRA_NA, _IRA_NA, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_POR[] = {
	// 0F EB /r1 POR mm,mm/m64
	{ NULL, 0x0001, 0x00D88000, { 0x0F, 0xEB, 0x00 }, _IRA_OPERAND_MODRM_R_MMX_W, _IRA_OPERAND_MODRM_RM_MMX, _IRA_NA, _IRA_NA },
	// 66 0F EB /r POR xmm1,xmm2/m128
	{ NULL, 0x1001, 0x00D88000, { 0x0F, 0xEB, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA },
	// VEX.NDS.128.66.0F.WIG EB /r VPOR xmm1,xmm2,xmm3/m128
	{ "vpor", 0x10C0, 0x00D88000, { 0x0F, 0xEB, 0x00 }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_SIMD_128, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_PREFETCHT[] = {
	// 0F 18 /1 PREFETCHT0 m8 M Valid Valid Move data from m8 closer to the processor using T0 hint.
	{ "prefetcht0", 0x0001, 0x80D98800, { 0x0F, 0x18, 0x00 }, _IRA_OPERAND_MODRM_M_8, _IRA_NA, _IRA_NA, _IRA_NA },
	// 0F 18 /2 PREFETCHT1 m8 M Valid Valid Move data from m8 closer to the processor using T1 hint.
	{ "prefetcht1", 0x0001, 0x80D99000, { 0x0F, 0x18, 0x00 }, _IRA_OPERAND_MODRM_M_8, _IRA_NA, _IRA_NA, _IRA_NA },
	// 0F 18 /3 PREFETCHT2 m8 M Valid Valid Move data from m8 closer to the processor using T2 hint.
	{ "prefetcht2", 0x0001, 0x80D99800, { 0x0F, 0x18, 0x00 }, _IRA_OPERAND_MODRM_M_8, _IRA_NA, _IRA_NA, _IRA_NA },
	// 0F 18 /0 PREFETCHNTA m8 M Valid Valid Move data from m8 closer to the processor using NTA hint.
	{ "prefetchnta", 0x0001, 0x80D98000, { 0x0F, 0x18, 0x00 }, _IRA_OPERAND_MODRM_M_8, _IRA_NA, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_PSADBW[] = {
	// 0F F6 /r PSADBW mm1,mm2/m64
	{ NULL, 0x0001, 0x00D88000, { 0x0F, 0xF6, 0x00 }, _IRA_OPERAND_MODRM_R_MMX_W, _IRA_OPERAND_MODRM_RM_MMX, _IRA_NA, _IRA_NA },
	// 66 0F F6 /r PSADBW xmm1,xmm2/m128
	{ NULL, 0x1001, 0x00D88000, { 0x0F, 0xF6, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA },
	// VEX.NDS.128.66.0F.WIG F6 /r VPSADBW xmm1,xmm2,xmm3/m128
	{ "vpsadbw", 0x10C0, 0x00D88000, { 0x0F, 0xF6, 0x00 }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_SIMD_128, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_PSHUFB[] = {
	// 0F 38 00 /r PSHUFB mm1,mm2/m64
	{ NULL, 0x0000, 0x00EC8000, { 0x0F, 0x38, 0x00 }, _IRA_OPERAND_MODRM_R_MMX_W, _IRA_OPERAND_MODRM_RM_MMX, _IRA_NA, _IRA_NA },
	// 66 0F 38 00 /r PSHUFB xmm1,xmm2/m128
	{ NULL, 0x1000, 0x00EC8000, { 0x0F, 0x38, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA },
	// VEX.NDS.128.66.0F38.WIG 00 /r VPSHUFB xmm1,xmm2,xmm3/m128
	{ "vpshufb", 0x10C0, 0x00EC8000, { 0x0F, 0x38, 0x00 }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_SIMD_128, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_PSHUFD[] = {
	// 66 0F 70 /r ib PSHUFD xmm1,xmm2/m128,imm8
	{ NULL, 0x1000, 0x00D88000, { 0x0F, 0x70, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_OPERAND_IB, _IRA_NA },
	// VEX.128.66.0F.WIG 70 /r ib VPSHUFD xmm1,xmm2/m128,imm8
	{ "vpshufd", 0x10C0, 0x00D88000, { 0x0F, 0x70, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_OPERAND_IB, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_PSHUFHW[] = {
	// F3 0F 70 /r ib PSHUFHW xmm1,xmm2/m128,imm8
	{ NULL, 0x4000, 0x00D88000, { 0x0F, 0x70, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_OPERAND_IB, _IRA_NA },
	// VEX.128.F3.0F.WIG 70 /r ib VPSHUFHW xmm1,xmm2/m128,imm8
	{ "vpshufhw", 0x40C0, 0x00D88000, { 0x0F, 0x70, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_OPERAND_IB, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_PSHUFLW[] = {
	// F2 0F 70 /r ib PSHUFLW xmm1,xmm2/m128,imm8
	{ NULL, 0x2000, 0x00D88000, { 0x0F, 0x70, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_OPERAND_IB, _IRA_NA },
	// VEX.128.F2.0F.WIG 70 /r ib VPSHUFLW xmm1,xmm2/m128,imm8
	{ "vpshuflw", 0x20C0, 0x00D88000, { 0x0F, 0x70, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_OPERAND_IB, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_PSHUFW[] = {
	// 0F 70 /r ib PSHUFW mm1,mm2/m64,imm8
	{ NULL, 0x0000, 0x00D88000, { 0x0F, 0x70, 0x00 }, _IRA_OPERAND_MODRM_R_MMX_W, _IRA_OPERAND_MODRM_RM_MMX, _IRA_OPERAND_IB, _IRA_NA },
};

struct ira_opcode_desc _ira_opcode_desc_PSIGN[] = {
	// 0F 38 08 /r PSIGNB mm1,mm2/m64
	{ "psignb", 0x0000, 0x00EC8000, { 0x0F, 0x38, 0x08 }, _IRA_OPERAND_MODRM_R_MMX_W, _IRA_OPERAND_MODRM_RM_MMX, _IRA_NA, _IRA_NA },
	// 0F 38 09 /r PSIGNW mm1,mm2/m64
	{ "psignw", 0x0000, 0x00EC8000, { 0x0F, 0x38, 0x09 }, _IRA_OPERAND_MODRM_R_MMX_W, _IRA_OPERAND_MODRM_RM_MMX, _IRA_NA, _IRA_NA },
	// 0F 38 0A /r PSIGND mm1,mm2/m64
	{ "psignd", 0x0000, 0x00EC8000, { 0x0F, 0x38, 0x0A }, _IRA_OPERAND_MODRM_R_MMX_W, _IRA_OPERAND_MODRM_RM_MMX, _IRA_NA, _IRA_NA },
	// 66 0F 38 08 /r PSIGNB xmm1,xmm2/m128
	{ "psignb", 0x1000, 0x00EC8000, { 0x0F, 0x38, 0x08 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA },
	// 66 0F 38 09 /r PSIGNW xmm1,xmm2/m128
	{ "psignw", 0x1000, 0x00EC8000, { 0x0F, 0x38, 0x09 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA },
	// 66 0F 38 0A /r PSIGND xmm1,xmm2/m128
	{ "psignd", 0x1000, 0x00EC8000, { 0x0F, 0x38, 0x0A }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA },
	// VEX.NDS.128.66.0F38.WIG 08 /r VPSIGNB xmm1,xmm2,xmm3/m128
	{ "vpsignb", 0x10C0, 0x00EC8000, { 0x0F, 0x38, 0x08 }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_SIMD_128, _IRA_NA },
	// VEX.NDS.128.66.0F38.WIG 09 /r VPSIGNW xmm1,xmm2,xmm3/m128
	{ "vpsignw", 0x10C0, 0x00EC8000, { 0x0F, 0x38, 0x09 }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_SIMD_128, _IRA_NA },
	// VEX.NDS.128.66.0F38.WIG 0A /r VPSIGND xmm1,xmm2,xmm3/m128
	{ "vpsignd", 0x10C0, 0x00EC8000, { 0x0F, 0x38, 0x0A }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_SIMD_128, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_PSRLDQ[] = {
	// 66 0F 73 /3 ib PSRLDQ xmm1, imm8
	{ NULL, 0x1000, 0x00DB9800, { 0x0F, 0x73, 0x00 }, _IRA_OPERAND_RM( IRA_REG_SIMD, _IRA_EOS_XMMWORD, _IRA_EOS_UNDEFINED, _IRA_RMF_R ), _IRA_OPERAND_IB, _IRA_NA, _IRA_NA },
	// VEX.NDD.128.66.0F.WIG 73 /3 ib VPSRLDQ xmm1, xmm2, imm8
	{ "vpsrldq", 0x10C0, 0x00DB9800, { 0x0F, 0x73, 0x00 }, _IRA_VEX_VVVV_REG | _IRA_WRITE, _IRA_OPERAND_RM( IRA_REG_SIMD, _IRA_EOS_XMMWORD, _IRA_EOS_UNDEFINED, _IRA_RMF_R ), _IRA_OPERAND_IB, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_PSRL[] = {
	// 0F D1 /r PSRLW mm,mm/m64
	{ "psrlw", 0x0000, 0x00D88000, { 0x0F, 0xD1, 0x00 }, _IRA_OPERAND_MODRM_R_MMX_W, _IRA_OPERAND_MODRM_RM_MMX, _IRA_NA, _IRA_NA },
	// 0F D2 /r PSRLD mm,mm/m64
	{ "psrld", 0x0000, 0x00D88000, { 0x0F, 0xD2, 0x00 }, _IRA_OPERAND_MODRM_R_MMX_W, _IRA_OPERAND_MODRM_RM_MMX, _IRA_NA, _IRA_NA },
	// 0F D3 /r PSRLQ mm,mm/m64
	{ "psrlq", 0x0000, 0x00D88000, { 0x0F, 0xD3, 0x00 }, _IRA_OPERAND_MODRM_R_MMX_W, _IRA_OPERAND_MODRM_RM_MMX, _IRA_NA, _IRA_NA },
	// 66 0F D1 /r PSRLW xmm1,xmm2/m128
	{ "psrlw", 0x1000, 0x00D88000, { 0x0F, 0xD1, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA },
	// 66 0F D2 /r PSRLD xmm1,xmm2/m128
	{ "psrld", 0x1000, 0x00D88000, { 0x0F, 0xD2, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA },
	// 66 0F D3 /r PSRLQ xmm1,xmm2/m128
	{ "psrlq", 0x1000, 0x00D88000, { 0x0F, 0xD3, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA },
	// 0F 71 /2 ib PSRLW mm,imm8
	{ "psrlw", 0x0000, 0x00DB9000, { 0x0F, 0x71, 0x00 }, _IRA_OPERAND_RM(IRA_REG_SIMD, _IRA_EOS_MMWORD, _IRA_EOS_UNDEFINED, _IRA_RMF_R ), _IRA_OPERAND_IB, _IRA_NA, _IRA_NA },
	// 0F 72 /2 ib PSRLD mm,imm8
	{ "psrld", 0x0000, 0x00DB9000, { 0x0F, 0x72, 0x00 }, _IRA_OPERAND_RM(IRA_REG_SIMD, _IRA_EOS_MMWORD, _IRA_EOS_UNDEFINED, _IRA_RMF_R ), _IRA_OPERAND_IB, _IRA_NA, _IRA_NA },
	// 0F 73 /2 ib PSRLQ mm,imm8
	{ "psrlq", 0x0000, 0x00DB9000, { 0x0F, 0x73, 0x00 }, _IRA_OPERAND_RM(IRA_REG_SIMD, _IRA_EOS_MMWORD, _IRA_EOS_UNDEFINED, _IRA_RMF_R ), _IRA_OPERAND_IB, _IRA_NA, _IRA_NA },
	// 66 0F 71 /2 ib PSRLW xmm1,imm8
	{ "psrlw", 0x1000, 0x00DB9000, { 0x0F, 0x71, 0x00 }, _IRA_OPERAND_RM(IRA_REG_SIMD, _IRA_EOS_XMMWORD, _IRA_EOS_UNDEFINED, _IRA_RMF_R ), _IRA_OPERAND_IB, _IRA_NA, _IRA_NA },
	// 66 0F 72 /2 ib PSRLD xmm1,imm8
	{ "psrld", 0x1000, 0x00DB9000, { 0x0F, 0x72, 0x00 }, _IRA_OPERAND_RM(IRA_REG_SIMD, _IRA_EOS_XMMWORD, _IRA_EOS_UNDEFINED, _IRA_RMF_R ), _IRA_OPERAND_IB, _IRA_NA, _IRA_NA },
	// 66 0F 73 /2 ib PSRLQ xmm1,imm8
	{ "psrlq", 0x1000, 0x00DB9000, { 0x0F, 0x73, 0x00 }, _IRA_OPERAND_RM(IRA_REG_SIMD, _IRA_EOS_XMMWORD, _IRA_EOS_UNDEFINED, _IRA_RMF_R ), _IRA_OPERAND_IB, _IRA_NA, _IRA_NA },
	// VEX.NDS.128.66.0F.WIG D1 /r VPSRLW xmm1,xmm2,xmm3/m128
	{ "vpsrlw", 0x10C0, 0x00D88000, { 0x0F, 0xD1, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA },
	// VEX.NDS.128.66.0F.WIG D2 /r VPSRLD xmm1,xmm2,xmm3/m128
	{ "vpsrld", 0x10C0, 0x00D88000, { 0x0F, 0xD2, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA },
	// VEX.NDS.128.66.0F.WIG D3 /r VPSRLQ xmm1,xmm2,xmm3/m128
	{ "vpsrlq", 0x10C0, 0x00D88000, { 0x0F, 0xD3, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA },
	// VEX.NDD.128.66.0F.WIG 71 /2 ib VPSRLW xmm1,xmm2,imm8
	{ "vpsrlw", 0x10C0, 0x00DB9000, { 0x0F, 0x71, 0x00 }, _IRA_VEX_VVVV_REG | _IRA_WRITE, _IRA_OPERAND_RM( IRA_REG_SIMD, _IRA_EOS_XMMWORD, _IRA_EOS_UNDEFINED, _IRA_RMF_R ), _IRA_OPERAND_IB, _IRA_NA },
	// VEX.NDD.128.66.0F.WIG 72 /2 ib VPSRLD xmm1,xmm2,imm8
	{ "vpsrld", 0x10C0, 0x00DB9000, { 0x0F, 0x72, 0x00 }, _IRA_VEX_VVVV_REG | _IRA_WRITE, _IRA_OPERAND_RM( IRA_REG_SIMD, _IRA_EOS_XMMWORD, _IRA_EOS_UNDEFINED, _IRA_RMF_R ), _IRA_OPERAND_IB, _IRA_NA },
	// VEX.NDD.128.66.0F.WIG 73 /2 ib VPSRLQ xmm1,xmm2,imm8
	{ "vpsrlq", 0x10C0, 0x00DB9000, { 0x0F, 0x73, 0x00 }, _IRA_VEX_VVVV_REG | _IRA_WRITE, _IRA_OPERAND_RM( IRA_REG_SIMD, _IRA_EOS_XMMWORD, _IRA_EOS_UNDEFINED, _IRA_RMF_R ), _IRA_OPERAND_IB, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_PSUB[] = {
	// 0F F8 /r PSUBB mm,mm/m64
	{ "psubb", 0x0000, 0x00D88000, { 0x0F, 0xF8, 0x00 }, _IRA_OPERAND_MODRM_R_MMX_W, _IRA_OPERAND_MODRM_RM_MMX, _IRA_NA, _IRA_NA },
	// 0F F9 /r PSUBW mm,mm/m64
	{ "psubw", 0x0000, 0x00D88000, { 0x0F, 0xF9, 0x00 }, _IRA_OPERAND_MODRM_R_MMX_W, _IRA_OPERAND_MODRM_RM_MMX, _IRA_NA, _IRA_NA },
	// 0F FA /r PSUBD mm,mm/m64
	{ "psubd", 0x0000, 0x00D88000, { 0x0F, 0xFA, 0x00 }, _IRA_OPERAND_MODRM_R_MMX_W, _IRA_OPERAND_MODRM_RM_MMX, _IRA_NA, _IRA_NA },
	// 66 0F F8 /r PSUBB xmm1,xmm2/m128
	{ "psubb", 0x1001, 0x00D88000, { 0x0F, 0xF8, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA },
	// 66 0F F9 /r PSUBW xmm1,xmm2/m128
	{ "psubw", 0x1001, 0x00D88000, { 0x0F, 0xF9, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA },
	// 66 0F FA /r PSUBD xmm1,xmm2/m128
	{ "psubd", 0x1001, 0x00D88000, { 0x0F, 0xFA, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA },
	// VEX.NDS.128.66.0F.WIG F8 /r VPSUBB xmm1,xmm2,xmm3/m128
	{ "vpsubb", 0x10C0, 0x00D88000, { 0x0F, 0xF8, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA },
	// VEX.NDS.128.66.0F.WIG F9 /r VPSUBW xmm1,xmm2,xmm3/m128
	{ "vpsubw", 0x10C0, 0x00D88000, { 0x0F, 0xF9, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA },
	// VEX.NDS.128.66.0F.WIG FA /r VPSUBD xmm1,xmm2,xmm3/m128
	{ "vpsubd", 0x10C0, 0x00D88000, { 0x0F, 0xFA, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_PSUBQ[] = {
	// 0F FB /r PSUBQ mm1,mm2/m64
	{ NULL, 0x0000, 0x00D88000, { 0x0F, 0xFB, 0x00 }, _IRA_OPERAND_MODRM_R_MMX_W, _IRA_OPERAND_MODRM_RM_MMX, _IRA_NA, _IRA_NA },
	// 66 0F FB /r PSUBQ xmm1,xmm2/m128
	{ NULL, 0x1000, 0x00D88000, { 0x0F, 0xFB, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA },
	// VEX.NDS.128.66.0F.WIG FB/r VPSUBQ xmm1,xmm2,xmm3/m128
	{ "vpsubq", 0x10C0, 0x00D88000, { 0x0F, 0xFB, 0x00 }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_SIMD_128, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_PSUBS[] = {
	// 0F E8 /r PSUBSB mm,mm/m64
	{ "psubsb", 0x0000, 0x00D88000, { 0x0F, 0xE8, 0x00 }, _IRA_OPERAND_MODRM_R_MMX_W, _IRA_OPERAND_MODRM_RM_MMX, _IRA_NA, _IRA_NA },
	// 0F E9 /r PSUBSW mm,mm/m64
	{ "psubsw", 0x0000, 0x00D88000, { 0x0F, 0xE9, 0x00 }, _IRA_OPERAND_MODRM_R_MMX_W, _IRA_OPERAND_MODRM_RM_MMX, _IRA_NA, _IRA_NA },
	// 66 0F E8 /r PSUBSB xmm1,xmm2/m128
	{ "psubsb", 0x1000, 0x00D88000, { 0x0F, 0xE8, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA },
	// 66 0F E9 /r PSUBSW xmm1,xmm2/m128
	{ "psubsw", 0x1000, 0x00D88000, { 0x0F, 0xE9, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA },
	// VEX.NDS.128.66.0F.WIG E8 /r VPSUBSB xmm1,xmm2,xmm3/m128
	{ "vpsubsb", 0x10C0, 0x00D88000, { 0x0F, 0xE8, 0x00 }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_SIMD_128, _IRA_NA },
	// VEX.NDS.128.66.0F.WIG E9 /r VPSUBSW xmm1,xmm2,xmm3/m128
	{ "vpsubsw", 0x10C0, 0x00D88000, { 0x0F, 0xE9, 0x00 }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_SIMD_128, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_PSUBUS[] = {
	// 0F D8 /r PSUBUSB mm,mm/m64
	{ "psubusb", 0x0000, 0x00D88000, { 0x0F, 0xD8, 0x00 }, _IRA_OPERAND_MODRM_R_MMX_W, _IRA_OPERAND_MODRM_RM_MMX, _IRA_NA, _IRA_NA },
	// 0F D9 /r1 PSUBUSW mm,mm/m64
	{ "psubusw", 0x0000, 0x00D88000, { 0x0F, 0xD9, 0x00 }, _IRA_OPERAND_MODRM_R_MMX_W, _IRA_OPERAND_MODRM_RM_MMX, _IRA_NA, _IRA_NA },
	// 66 0F D8 /r PSUBUSB xmm1,xmm2/m128
	{ "psubusb", 0x1000, 0x00D88000, { 0x0F, 0xD8, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA },
	// 66 0F D9 /r PSUBUSW xmm1,xmm2/m128
	{ "psubusw", 0x1000, 0x00D88000, { 0x0F, 0xD9, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA },
	// VEX.NDS.128.66.0F.WIG D8 /r VPSUBUSB xmm1,xmm2,xmm3/m128
	{ "vpsubusb", 0x10C0, 0x00D88000, { 0x0F, 0xD8, 0x00 }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_SIMD_128, _IRA_NA },
	// VEX.NDS.128.66.0F.WIG D9 /r VPSUBUSW xmm1,xmm2,xmm3/m128
	{ "vpsubusw", 0x10C0, 0x00D88000, { 0x0F, 0xD9, 0x00 }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_SIMD_128, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_PTEST[] = {
	// 66 0F 38 17 /r PTEST xmm1,xmm2/m128
	{ "ptest", 0x1000, 0x00EC8000, { 0x0F, 0x38, 0x17 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA },
	// VEX.128.66.0F38.WIG 17 /r VPTEST xmm1,xmm2/m128
	// VEX.256.66.0F38.WIG 17 /r VPTEST ymm1,ymm2/m256
	{ "vptest", 0x1180, 0x00EC8000, { 0x0F, 0x38, 0x17 }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_OPERAND_MODRM_RM_SIMD, _IRA_NA, _IRA_NA },
};

struct ira_opcode_desc _ira_opcode_desc_PUNPCKL[] = {
	// 0F 60 /r PUNPCKLBW mm,mm/m32
	{ "punpcklbw", 0x0000, 0x00D88000, { 0x0F, 0x60, 0x00 }, _IRA_OPERAND_MODRM_R_MMX_W, _IRA_OPERAND_MODRM_RM_MMX_32, _IRA_NA, _IRA_NA },
	// 0F 61 /r PUNPCKLWD mm,mm/m32
	{ "punpcklwd", 0x0000, 0x00D88000, { 0x0F, 0x61, 0x00 }, _IRA_OPERAND_MODRM_R_MMX_W, _IRA_OPERAND_MODRM_RM_MMX_32, _IRA_NA, _IRA_NA },
	// 0F 62 /r PUNPCKLDQ mm,mm/m32
	{ "punpckldq", 0x0000, 0x00D88000, { 0x0F, 0x62, 0x00 }, _IRA_OPERAND_MODRM_R_MMX_W, _IRA_OPERAND_MODRM_RM_MMX_32, _IRA_NA, _IRA_NA },
	// 66 0F 60 /r PUNPCKLBW xmm1,xmm2/m128
	{ "punpcklbw", 0x1000, 0x00D88000, { 0x0F, 0x60, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA },
	// 66 0F 61 /r PUNPCKLWD xmm1,xmm2/m128
	{ "punpcklwd", 0x1000, 0x00D88000, { 0x0F, 0x61, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA },
	// 66 0F 62 /r PUNPCKLDQ xmm1,xmm2/m128
	{ "punpckldq", 0x1000, 0x00D88000, { 0x0F, 0x62, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA },
	// 66 0F 6C /r PUNPCKLQDQ xmm1,xmm2/m128
	{ "punpcklqdq", 0x1000, 0x00D88000, { 0x0F, 0x6C, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA },
	// VEX.NDS.128.66.0F.WIG 60 /r VPUNPCKLBW xmm1,xmm2,xmm3/m128
	{ "vpunpcklbw", 0x10C0, 0x00D88000, { 0x0F, 0x60, 0x00 }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_SIMD_128, _IRA_NA },
	// VEX.NDS.128.66.0F.WIG 61 /r VPUNPCKLWD xmm1,xmm2,xmm3/m128
	{ "vpunpcklwd", 0x10C0, 0x00D88000, { 0x0F, 0x61, 0x00 }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_SIMD_128, _IRA_NA },
	// VEX.NDS.128.66.0F.WIG 62 /r VPUNPCKLDQ xmm1,xmm2,xmm3/m128
	{ "vpunpckldq", 0x10C0, 0x00D88000, { 0x0F, 0x62, 0x00 }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_SIMD_128, _IRA_NA },
	// VEX.NDS.128.66.0F.WIG 6C /r VPUNPCKLQDQ xmm1,xmm2,xmm3/m128
	{ "vpunpcklqdq", 0x10C0, 0x00D88000, { 0x0F, 0x6C, 0x00 }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_SIMD_128, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_PUNPCKH[] = {
	// 0F 68 /r PUNPCKHBW mm,mm/m64
	{ "punpckhbw", 0x0000, 0x00D88000, { 0x0F, 0x68, 0x00 }, _IRA_OPERAND_MODRM_R_MMX_W, _IRA_OPERAND_MODRM_RM_MMX, _IRA_NA, _IRA_NA },
	// 0F 69 /r PUNPCKHWD mm,mm/m64
	{ "punpckhwd", 0x0000, 0x00D88000, { 0x0F, 0x69, 0x00 }, _IRA_OPERAND_MODRM_R_MMX_W, _IRA_OPERAND_MODRM_RM_MMX, _IRA_NA, _IRA_NA },
	// 0F 6A /r PUNPCKHDQ mm,mm/m64
	{ "punpckhdq", 0x0000, 0x00D88000, { 0x0F, 0x6A, 0x00 }, _IRA_OPERAND_MODRM_R_MMX_W, _IRA_OPERAND_MODRM_RM_MMX, _IRA_NA, _IRA_NA },
	// 66 0F 68 /r PUNPCKHBW xmm1,xmm2/m128
	{ "punpckhbw", 0x1000, 0x00D88000, { 0x0F, 0x68, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA },
	// 66 0F 69 /r PUNPCKHWD xmm1,xmm2/m128
	{ "punpckhwd", 0x1000, 0x00D88000, { 0x0F, 0x69, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA },
	// 66 0F 6A /r PUNPCKHDQ xmm1,xmm2/m128
	{ "punpckhdq", 0x1000, 0x00D88000, { 0x0F, 0x6A, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA },
	// 66 0F 6D /r PUNPCKHQDQ xmm1,xmm2/m128
	{ "punpckhqdq", 0x1000, 0x00D88000, { 0x0F, 0x6D, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA },
	// VEX.NDS.128.66.0F.WIG 68 /r VPUNPCKHBW xmm1,xmm2,xmm3/m128
	{ "vpunpckhbw", 0x10C0, 0x00D88000, { 0x0F, 0x68, 0x00 }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_SIMD_128, _IRA_NA },
	// VEX.NDS.128.66.0F.WIG 69 /r VPUNPCKHWD xmm1,xmm2,xmm3/m128
	{ "vpunpckhwd", 0x10C0, 0x00D88000, { 0x0F, 0x69, 0x00 }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_SIMD_128, _IRA_NA },
	// VEX.NDS.128.66.0F.WIG 6A /r VPUNPCKHDQ xmm1,xmm2,xmm3/m128
	{ "vpunpckhdq", 0x10C0, 0x00D88000, { 0x0F, 0x6A, 0x00 }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_SIMD_128, _IRA_NA },
	// VEX.NDS.128.66.0F.WIG 6D /r VPUNPCKHQDQ xmm1,xmm2,xmm3/m128
	{ "vpunpckhqdq", 0x10C0, 0x00D88000, { 0x0F, 0x6D, 0x00 }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_SIMD_128, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_PUSH[] = {
	// FF /6 PUSH r/m16 M Valid Valid Push r/m16.
	// FF /6 PUSH r/m32 M N.E. Valid Push r/m32.
	// FF /6 PUSH r/m64 M Valid N.E. Push r/m64.
	{ NULL, 0x0001, 0x0045B000, { 0xFF, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_W, _IRA_NA, _IRA_NA, _IRA_NA },
	{ NULL, 0x0001, 0x0185B000, { 0xFF, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_16_W, _IRA_NA, _IRA_NA, _IRA_NA },
	{ NULL, 0x0001, 0x0685B000, { 0xfF, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_64_W, _IRA_NA, _IRA_NA, _IRA_NA },
	// 50+rw PUSH r16 O Valid Valid Push r16.
	// 50+rd PUSH r32 O N.E. Valid Push r32.
	// 50+rd PUSH r64 O Valid N.E. Push r64.
	{ NULL, 0x0001, 0x00440000, { 0x50, 0x00, 0x00 }, _IRA_OPERAND_OPCODE_REG( IRA_REG_GPR, _IRA_OS_EOSA), _IRA_NA, _IRA_NA, _IRA_NA },
	{ NULL, 0x0001, 0x01840000, { 0x50, 0x00, 0x00 }, _IRA_OPERAND_OPCODE_REG( IRA_REG_GPR, _IRA_OS_WORD ), _IRA_NA, _IRA_NA, _IRA_NA },
	{ NULL, 0x0001, 0x06840000, { 0x50, 0x00, 0x00 }, _IRA_OPERAND_OPCODE_REG( IRA_REG_GPR, _IRA_OS_QWORD ), _IRA_NA, _IRA_NA, _IRA_NA },
	// 6A PUSH imm8 I Valid Valid Push imm8.
	{ NULL, 0x0001, 0x00C40000, { 0x6A, 0x00, 0x00 }, _IRA_OPERAND_IB_EX_EOSA, _IRA_NA, _IRA_NA, _IRA_NA },
	// 68 PUSH imm16 I Valid Valid Push imm16.
	{ NULL, 0x0001, 0x01C40000, { 0x68, 0x00, 0x00 }, _IRA_OPERAND_IW_EX_EOSA, _IRA_NA, _IRA_NA, _IRA_NA },
	// 68 PUSH imm32 I Valid Valid Push imm32.
	{ NULL, 0x0001, 0x06C40000, { 0x68, 0x00, 0x00 }, _IRA_OPERAND_ID_EX_EOSA, _IRA_NA, _IRA_NA, _IRA_NA },
	// 1E PUSH DS NP Invalid Valid Push DS.
	// 06 PUSH ES NP Invalid Valid Push ES.
	// 16 PUSH SS NP Invalid Valid Push SS.
	// 0E PUSH CS NP Invalid Valid Push CS.
	{ NULL, 0x0001, 0x00440000, { 0x1E, 0x00, 0x00 }, _IRA_EXPLICIT_REG( IRA_REG_SEG, _IRA_REG_DS, _IRA_OS_UNDEFINED ), _IRA_NA, _IRA_NA, _IRA_NA },
	{ NULL, 0x0001, 0x00440000, { 0x06, 0x00, 0x00 }, _IRA_EXPLICIT_REG( IRA_REG_SEG, _IRA_REG_ES, _IRA_OS_UNDEFINED ), _IRA_NA, _IRA_NA, _IRA_NA },
	{ NULL, 0x0001, 0x00440000, { 0x16, 0x00, 0x00 }, _IRA_EXPLICIT_REG( IRA_REG_SEG, _IRA_REG_SS, _IRA_OS_UNDEFINED ), _IRA_NA, _IRA_NA, _IRA_NA },
	{ NULL, 0x0001, 0x00440000, { 0x0E, 0x00, 0x00 }, _IRA_EXPLICIT_REG( IRA_REG_SEG, _IRA_REG_CS, _IRA_OS_UNDEFINED ), _IRA_NA, _IRA_NA, _IRA_NA },
	// 0F A0 PUSH FS NP Valid Valid Push FS.
	{ NULL, 0x0001, 0x00D80000, { 0x0F, 0xA0, 0x00 }, _IRA_EXPLICIT_REG( IRA_REG_SEG, _IRA_REG_FS, _IRA_OS_UNDEFINED ), _IRA_NA, _IRA_NA, _IRA_NA },
	// 0F A8 PUSH GS NP Valid Valid Push GS.
	{ NULL, 0x0001, 0x00D80000, { 0x0F, 0xA8, 0x00 }, _IRA_EXPLICIT_REG( IRA_REG_SEG, _IRA_REG_GS, _IRA_OS_UNDEFINED ), _IRA_NA, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_PUSHA[] = {
	// 60 PUSHA NP Invalid Valid Push AX, CX, DX, BX, original SP, BP, SI, and DI.
	{ NULL, 0x0001, 0x01440000, { 0x60, 0x00, 0x00 }, _IRA_NA, _IRA_NA, _IRA_NA, _IRA_NA },
	// 60 PUSHAD NP Invalid Valid Push EAX, ECX, EDX, EBX, original ESP, EBP, ESI, and EDI.
	{ "pushad", 0x0001, 0x02440000, { 0x60, 0x00, 0x00 }, _IRA_NA, _IRA_NA, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_PUSHF[] = {
	// 9C PUSHF NP Valid Valid Push lower 16 bits of EFLAGS.
	{ NULL, 0x0000, 0x01C40000, { 0x9C, 0x00, 0x00 }, _IRA_NA, _IRA_NA, _IRA_NA, _IRA_NA },
	// 9C PUSHFD NP N.E. Valid Push EFLAGS.
	{ "pushfd", 0x0000, 0x02440000, { 0x9C, 0x00, 0x00 }, _IRA_NA, _IRA_NA, _IRA_NA, _IRA_NA },
	// 9C PUSHFQ NP Valid N.E. Push RFLAGS.
	{ "pushfq", 0x0000, 0x04840000, { 0x9C, 0x00, 0x00 }, _IRA_NA, _IRA_NA, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_PXOR[] = {
	// 0F EF /r PXOR mm,mm/m64
	{ NULL, 0x0001, 0x00D88000, { 0x0F, 0xEF, 0x00 }, _IRA_OPERAND_MODRM_R_MMX_W, _IRA_OPERAND_MODRM_RM_MMX, _IRA_NA, _IRA_NA },
	// 66 0F EF /r PXOR xmm1,xmm2/m128
	{ NULL, 0x1001, 0x00D88000, { 0x0F, 0xEF, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA },
	// VEX.NDS.128.66.0F.WIG EF /r VPXOR xmm1,xmm2,xmm3/m128
	{ "vpxor", 0x10C0, 0x00D88000, { 0x0F, 0xEF, 0x00 }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_SIMD_128, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_RCL[] = {
	// D0 /2 RCL r/m8, 1
	// REX + D0 /2 RCL r/m8, 1
	{ NULL, 0x0000, 0x00C59000, { 0xD0, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_8_W, _IRA_EXPLICIT_OPERAND_IB(1), _IRA_NA, _IRA_NA },
	// D2 /2 RCL r/m8, CL
	// REX + D2 /2 RCL r/m8, CL
	{ NULL, 0x0000, 0x00C59000, { 0xD2, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_8_W, _IRA_EXPLICIT_REG( IRA_REG_GPR, _IRA_REG_CL, _IRA_OS_BYTE ), _IRA_NA, _IRA_NA },
	// C0 /2 ib RCL r/m8, imm8
	// REX + C0 /2 ib RCL r/m8, imm8
	{ NULL, 0x0000, 0x00C59000, { 0xC0, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_8_W, _IRA_OPERAND_IB, _IRA_NA, _IRA_NA },
	// D1 /2 RCL r/m16, 1
	// D1 /2 RCL r/m32, 1
	// REX.W + D1 /2 RCL r/m64, 1
	{ NULL, 0x0000, 0x00C59000, { 0xD1, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_W, _IRA_EXPLICIT_OPERAND_IB(1), _IRA_NA, _IRA_NA },
	// D3 /2 RCL r/m16, CL
	// D3 /2 RCL r/m32, CL
	// REX.W + D3 /2 RCL r/m64, CL
	{ NULL, 0x0000, 0x00C59000, { 0xD3, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_W, _IRA_EXPLICIT_REG( IRA_REG_GPR, _IRA_REG_CL, _IRA_OS_BYTE ), _IRA_NA, _IRA_NA },
	// C1 /2 ib RCL r/m16, imm8
	// C1 /2 ib RCL r/m32, imm8
	// REX.W + C1 /2 ib RCL r/m64, imm8
	{ NULL, 0x0000, 0x00C59000, { 0xC1, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_W, _IRA_OPERAND_IB, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_RCR[] = {
	// D0 /3 RCR r/m8, 1
	// REX + D0 /3 RCR r/m8, 1
	{ NULL, 0x0000, 0x00C59800, { 0xD0, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_8_W, _IRA_EXPLICIT_OPERAND_IB(1), _IRA_NA, _IRA_NA },
	// D2 /3 RCR r/m8, CL
	// REX + D2 /3 RCR r/m8, CL
	{ NULL, 0x0000, 0x00C59800, { 0xD2, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_8_W, _IRA_EXPLICIT_REG( IRA_REG_GPR, _IRA_REG_CL, _IRA_OS_BYTE ), _IRA_NA, _IRA_NA },
	// C0 /3 ib RCR r/m8, imm8
	// REX + C0 /3 ib RCR r/m8, imm8
	{ NULL, 0x0000, 0x00C59800, { 0xC0, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_8_W, _IRA_OPERAND_IB, _IRA_NA, _IRA_NA },
	// D1 /3 RCR r/m16, 1
	// D1 /3 RCR r/m32, 1
	// REX.W + D1 /3 RCR r/m64, 1
	{ NULL, 0x0000, 0x00C59800, { 0xD1, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_W, _IRA_EXPLICIT_OPERAND_IB(1), _IRA_NA, _IRA_NA },
	// D3 /3 RCR r/m16, CL
	// D3 /3 RCR r/m32, CL
	// REX.W + D3 /3 RCR r/m64, CL
	{ NULL, 0x0000, 0x00C59800, { 0xD3, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_W, _IRA_EXPLICIT_REG( IRA_REG_GPR, _IRA_REG_CL, _IRA_OS_BYTE ), _IRA_NA, _IRA_NA },
	// C1 /3 ib RCR r/m16, imm8
	// C1 /3 ib RCR r/m32, imm8
	// REX.W + C1 /3 ib RCR r/m64, imm8
	{ NULL, 0x0000, 0x00C59800, { 0xC1, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_W, _IRA_OPERAND_IB, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_ROL[] = {
	// D0 /0 ROL r/m8, 1
	// REX + D0 /0 ROL r/m8, 1
	{ NULL, 0x0000, 0x00C58000, { 0xD0, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_8_W, _IRA_EXPLICIT_OPERAND_IB(1), _IRA_NA, _IRA_NA },
	// D2 /0 ROL r/m8, CL
	// REX + D2 /0 ROL r/m8, CL
	{ NULL, 0x0000, 0x00C58000, { 0xD2, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_8_W, _IRA_EXPLICIT_REG( IRA_REG_GPR, _IRA_REG_CL, _IRA_OS_BYTE ), _IRA_NA, _IRA_NA },
	// C0 /0 ib ROL r/m8, imm8
	// REX + C0 /0 ib ROL r/m8, imm8
	{ NULL, 0x0000, 0x00C58000, { 0xC0, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_8_W, _IRA_OPERAND_IB, _IRA_NA, _IRA_NA },
	// D1 /0 ROL r/m16, 1
	// D1 /0 ROL r/m32, 1
	// REX.W + D1 /0 ROL r/m64, 1
	{ NULL, 0x0000, 0x00C58000, { 0xD1, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_W, _IRA_EXPLICIT_OPERAND_IB(1), _IRA_NA, _IRA_NA },
	// D3 /0 ROL r/m16, CL
	// D3 /0 ROL r/m32, CL
	// REX.W + D3 /0 ROL r/m64, CL
	{ NULL, 0x0000, 0x00C58000, { 0xD3, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_W, _IRA_EXPLICIT_REG( IRA_REG_GPR, _IRA_REG_CL, _IRA_OS_BYTE ), _IRA_NA, _IRA_NA },
	// C1 /0 ib ROL r/m16, imm8
	// C1 /0 ib ROL r/m32, imm8
	// C1 /0 ib ROL r/m64, imm8
	{ NULL, 0x0000, 0x00C58000, { 0xC1, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_W, _IRA_OPERAND_IB, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_ROR[] = {
	// D0 /1 ROR r/m8, 1
	// REX + D0 /1 ROR r/m8, 1
	{ NULL, 0x0000, 0x00C58800, { 0xD0, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_8_W, _IRA_EXPLICIT_OPERAND_IB(1), _IRA_NA, _IRA_NA },
	// D2 /1 ROR r/m8, CL
	// REX + D2 /1 ROR r/m8, CL
	{ NULL, 0x0000, 0x00C58800, { 0xD2, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_8_W, _IRA_EXPLICIT_REG( IRA_REG_GPR, _IRA_REG_CL, _IRA_OS_BYTE ), _IRA_NA, _IRA_NA },
	// C0 /1 ib ROR r/m8, imm8
	// REX + C0 /1 ib ROR r/m8, imm8
	{ NULL, 0x0000, 0x00C58800, { 0xC0, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_8_W, _IRA_OPERAND_IB, _IRA_NA, _IRA_NA },
	// D1 /1 ROR r/m16, 1
	// D1 /1 ROR r/m32, 1
	// REX.W + D1 /1 ROR r/m64, 1
	{ NULL, 0x0000, 0x00C58800, { 0xD1, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_W, _IRA_EXPLICIT_OPERAND_IB(1), _IRA_NA, _IRA_NA },
	// D3 /1 ROR r/m16, CL
	// D3 /1 ROR r/m32, CL
	// REX.W + D3 /1 ROR r/m64, CL
	{ NULL, 0x0000, 0x00C58800, { 0xD3, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_W, _IRA_EXPLICIT_REG( IRA_REG_GPR, _IRA_REG_CL, _IRA_OS_BYTE ), _IRA_NA, _IRA_NA },
	// C1 /1 ib ROR r/m16, imm8
	// C1 /1 ib ROR r/m32, imm8
	// REX.W + C1 /1 ib ROR r/m64, imm8
	{ NULL, 0x0000, 0x00C58800, { 0xC1, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_W, _IRA_OPERAND_IB, _IRA_NA, _IRA_NA }
};

// XMMWORD
struct ira_opcode_desc _ira_opcode_desc_RCPPS[] = {
	// 0F 53 /r RCPPS xmm1,xmm2/m128
	{ NULL, 0x0001, 0x00D88000, { 0x0F, 0x53, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA },
	// VEX.128.0F.WIG 53 /r VRCPPS xmm1,xmm2/m128
	// VEX.256.0F.WIG 53 /r VRCPPS ymm1,ymm2/m256
	{ "vrcpps", 0x0181, 0x00D88000, { 0x0F, 0x53, 0x00 }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_OPERAND_MODRM_RM_SIMD, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_RCPSS[] = {
	// F3 0F 53 /r RCPSS xmm1,xmm2/m32
	{ NULL, 0x4000, 0x00D88000, { 0x0F, 0x53, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_32, _IRA_NA, _IRA_NA },
	// VEX.NDS.LIG.F3.0F.WIG 53 /r VRCPSS xmm1,xmm2,xmm3/m32
	{ "vrcpss", 0x40C0, 0x00D88000, { 0x0F, 0x53, 0x00 }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_SIMD_32, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_RDFSBASE[] = {
	// F3 0F AE /0 RDFSBASE r32
	// REX.W + F3 0F AE /0 RDFSBASE r64
	{ NULL, 0x4000, 0x039B8000, { 0x0F, 0xAE, 0x00 }, _IRA_OPERAND_RM( IRA_REG_GPR, _IRA_EOS_DWORD, _IRA_EOS_UNDEFINED, _IRA_RMF_R ) | _IRA_WRITE, _IRA_NA, _IRA_NA, _IRA_NA },
	{ NULL, 0x4000, 0x049B8000, { 0x0F, 0xAE, 0x00 }, _IRA_OPERAND_RM( IRA_REG_GPR, _IRA_EOS_QWORD, _IRA_EOS_UNDEFINED, _IRA_RMF_R ) | _IRA_WRITE, _IRA_NA, _IRA_NA, _IRA_NA },
	// F3 0F AE /1 RDGSBASE r32
	// REX.W + F3 0F AE /1 RDGSBASE r64
	{ "rdgsbase", 0x4000, 0x039B8800, { 0x0F, 0xAE, 0x00 }, _IRA_OPERAND_RM( IRA_REG_GPR, _IRA_EOS_DWORD, _IRA_EOS_UNDEFINED, _IRA_RMF_R ) | _IRA_WRITE, _IRA_NA, _IRA_NA, _IRA_NA },
	{ "rdgsbase", 0x4000, 0x049B8800, { 0x0F, 0xAE, 0x00 }, _IRA_OPERAND_RM( IRA_REG_GPR, _IRA_EOS_QWORD, _IRA_EOS_UNDEFINED, _IRA_RMF_R ) | _IRA_WRITE, _IRA_NA, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_RDRAND[] = {
	// 0F C7 /6 RDRAND r16
	// 0F C7 /6 RDRAND r32
	// REX.W + 0F C7 /6 RDRAND r64
	{ NULL, 0x0000, 0x00DBB000, { 0x0F, 0xC7, 0x00 }, _IRA_OPERAND_RM( IRA_REG_GPR, _IRA_EOS_EOSA, _IRA_EOS_UNDEFINED, _IRA_RMF_R ) | _IRA_WRITE, _IRA_NA, _IRA_NA, _IRA_NA },
};

struct ira_opcode_desc _ira_opcode_desc_RDTSCP[] = {
	// 0F 01 F9 RDTSCP
	{ NULL, 0x0000, 0x00EC0000, { 0x0F, 0x01, 0xF9 }, _IRA_NA, _IRA_NA, _IRA_NA, _IRA_NA },
};

struct ira_opcode_desc _ira_opcode_desc_RDTSC[] = {
	// 0F 31 RDTSC
	{ NULL, 0x0000, 0x00D80000, { 0x0F, 0x31, 0x00 }, _IRA_NA, _IRA_NA, _IRA_NA, _IRA_NA },
};

struct ira_opcode_desc _ira_opcode_desc_RDPMC[] = {
	// 0F 33 RDPMC
	{ NULL, 0x0000, 0x00D80000, { 0x0F, 0x33, 0x00 }, _IRA_NA, _IRA_NA, _IRA_NA, _IRA_NA },
};

struct ira_opcode_desc _ira_opcode_desc_RDMSR[] = {
	// 0F 32 RDMSR
	{ NULL, 0x0000, 0x00D80000, { 0x0F, 0x32, 0x00 }, _IRA_NA, _IRA_NA, _IRA_NA, _IRA_NA },
};

struct ira_opcode_desc _ira_opcode_desc_RET[] = {
	// C3 RET
	// CB RET
	{ NULL, 0x0000, 0x00C40000, { 0xC3, 0x00, 0x00 }, _IRA_NA, _IRA_NA, _IRA_NA, _IRA_NA },
	{ "retf", 0x0000, 0x00C40000, { 0xCB, 0x00, 0x00 }, _IRA_NA, _IRA_NA, _IRA_NA, _IRA_NA },
	// C2 iw RET imm16
	// CA iw RET imm16
	{ NULL, 0x0000, 0x00C40000, { 0xC2, 0x00, 0x00 }, _IRA_OPERAND_IW, _IRA_NA, _IRA_NA, _IRA_NA },
	{ "retf", 0x0000, 0x00C40000, { 0xCA, 0x00, 0x00 }, _IRA_OPERAND_IW, _IRA_NA, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_ROUNDPD[] = {
	// 66 0F 3A 09 /r ib ROUNDPD xmm1,xmm2/m128,imm8
	{ NULL, 0x1000, 0x00EC8000, { 0x0F, 0x3A, 0x09 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_OPERAND_IB, _IRA_NA },
	// VEX.128.66.0F3A.WIG 09 /r ib VROUNDPD xmm1,xmm2/m128,imm8
	// VEX.256.66.0F3A.WIG 09 /r ib VROUNDPD ymm1,ymm2/m256,imm8
	{ "vroundpd", 0x1180, 0x00EC8000, { 0x0F, 0x3A, 0x09 }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_OPERAND_MODRM_RM_SIMD, _IRA_OPERAND_IB, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_ROUNDPS[] = {
	// 66 0F 3A 08 /r ib ROUNDPS xmm1,xmm2/m128,imm8
	{ NULL, 0x1000, 0x00EC8000, { 0x0F, 0x3A, 0x08 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_OPERAND_IB, _IRA_NA },
	// VEX.128.66.0F3A.WIG 08 /r ib VROUNDPS xmm1,xmm2/m128,imm8
	// VEX.256.66.0F3A.WIG 08 /r ib VROUNDPS ymm1,ymm2/m256,imm8
	{ "vroundps", 0x1180, 0x00EC8000, { 0x0F, 0x3A, 0x08 }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_OPERAND_MODRM_RM_SIMD, _IRA_OPERAND_IB, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_ROUNDSD[] = {
	// 66 0F 3A 0B /r ib ROUNDSD xmm1,xmm2/m64,imm8
	{ NULL, 0x1000, 0x00EC8000, { 0x0F, 0x3A, 0x0B }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_64, _IRA_OPERAND_IB, _IRA_NA },
	// VEX.NDS.LIG.66.0F3A.WIG 0B /r ib VROUNDSD xmm1,xmm2,xmm3/m64,imm8
	{ "vroundsd", 0x10C0, 0x00EC8000, { 0x0F, 0x3A, 0x0B }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_SIMD_64, _IRA_OPERAND_IB }
};

struct ira_opcode_desc _ira_opcode_desc_ROUNDSS[] = {
	// 66 0F 3A 0A /r ib ROUNDSS xmm1,xmm2/m32,imm8
	{ NULL, 0x1000, 0x00EC8000, { 0x0F, 0x3A, 0x0A }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_32, _IRA_OPERAND_IB, _IRA_NA },
	// VEX.NDS.LIG.66.0F3A.WIG 0A ib VROUNDSS xmm1,xmm2,xmm3/m32,imm8
	{ "vroundss", 0x10C0, 0x00EC8000, { 0x0F, 0x3A, 0x0A }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_SIMD_32, _IRA_OPERAND_IB }
};

struct ira_opcode_desc _ira_opcode_desc_RSM[] = {
	// 0F AA RSM NP Invalid Valid Resume operation of interrupted program.
	{ NULL, 0x0000, 0x00580000, { 0x0F, 0xAA, 0x00 }, _IRA_NA, _IRA_NA, _IRA_NA, _IRA_NA },
};

struct ira_opcode_desc _ira_opcode_desc_RSQRTPS[] = {
	// 0F 52 /r RSQRTPS xmm1,xmm2/m128
	{ NULL, 0x0000, 0x00D88000, { 0x0F, 0x52, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA },
	// VEX.128.0F.WIG 52 /r VRSQRTPS xmm1,xmm2/m128
	// VEX.256.0F.WIG 52 /r VRSQRTPS ymm1,ymm2/m256
	{ "vrsqrtps", 0x0180, 0x00D88000, { 0x0F, 0x52, 0x00 }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_OPERAND_MODRM_RM_SIMD, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_RSQRTSS[] = {
	// F3 0F 52 /r RSQRTSS xmm1,xmm2/m32
	{ NULL, 0x4000, 0x00D88000, { 0x0F, 0x52, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_32, _IRA_NA, _IRA_NA },
	// VEX.NDS.LIG.F3.0F.WIG 52 /r VRSQRTSS xmm1,xmm2,xmm3/m32
	{ "vrsqrtss", 0x40C0, 0x00D88000, { 0x0F, 0x52, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_XMM_32, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_SAHF[] = {
	// 9E SAHF
	// TODO: Narazie dostepne w 64 bit, ale generalnie dostepne w 64 bit tylko jezeli CPUID jest odpowiednio ustawiony.
	// Jzeli bedziemy dodawali mozliwosc parametryzacji wynikow debugera poprzez dostarczanie CPUID, to trzeba to bedzie obsluzyc.
	{ NULL, 0x0000, 0x00C40000, { 0x9E, 0x00, 0x00 }, _IRA_NA, _IRA_NA, _IRA_NA, _IRA_NA }
};

// TODO: Zaimplementowac na cele assemblera dopiero. Jako ze tak samo sie koduje jak SHL.
// D0 /4 SAL r/m8, 1 M1 Valid Valid Multiply r/m8 by 2, once.
// REX + D0 /4 SAL r/m8**, 1 M1 Valid N.E. Multiply r/m8 by 2, once.
// D2 /4 SAL r/m8, CL MC Valid Valid Multiply r/m8 by 2, CL times.
// REX + D2 /4 SAL r/m8**, CL MC Valid N.E. Multiply r/m8 by 2, CL times.
// C0 /4 ib SAL r/m8, imm8 MI Valid Valid Multiply r/m8 by 2, imm8 times.
// REX + C0 /4 ib SAL r/m8**, imm8 MI Valid N.E. Multiply r/m8 by 2, imm8 times.
// D1 /4 SAL r/m16, 1 M1 Valid Valid Multiply r/m16 by 2, once.
// D1 /4 SAL r/m32, 1 M1 Valid Valid Multiply r/m32 by 2, once.
// REX.W + D1 /4 SAL r/m64, 1 M1 Valid N.E. Multiply r/m64 by 2, once.
// D3 /4 SAL r/m16, CL MC Valid Valid Multiply r/m16 by 2, CL times.
// D3 /4 SAL r/m32, CL MC Valid Valid Multiply r/m32 by 2, CL times.
// REX.W + D3 /4 SAL r/m64, CL MC Valid N.E. Multiply r/m64 by 2, CL times.
// C1 /4 ib SAL r/m16, imm8 MI Valid Valid Multiply r/m16 by 2, imm8 times.
// C1 /4 ib SAL r/m32, imm8 MI Valid Valid Multiply r/m32 by 2, imm8 times.
// REX.W + C1 /4 ib SAL r/m64, imm8 MI Valid N.E. Multiply r/m64 by 2, imm8 times.

struct ira_opcode_desc _ira_opcode_desc_SAR[] = {
	// D0 /7 SAR r/m8, 1
	// REX + D0 /7 SAR r/m8
	{ NULL, 0x0000, 0x00C5B800, { 0xD0, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_8_W, _IRA_EXPLICIT_OPERAND_IB(1), _IRA_NA, _IRA_NA },
	// D2 /7 SAR r/m8, CL MC Valid Valid Signed divide* r/m8 by 2, CL times.
	// REX + D2 /7 SAR r/m8**, CL MC Valid N.E. Signed divide* r/m8 by 2, CL times.
	{ NULL, 0x0000, 0x00C5B800, { 0xD2, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_8_W, _IRA_EXPLICIT_REG( IRA_REG_GPR, _IRA_REG_CL, _IRA_OS_BYTE ), _IRA_NA, _IRA_NA },
	// C0 /7 ib SAR r/m8, imm8 MI Valid Valid Signed divide* r/m8 by 2, imm8 time.
	// REX + C0 /7 ib SAR r/m8**, imm8 MI Valid N.E. Signed divide* r/m8 by 2, imm8 times.
	{ NULL, 0x0000, 0x00C5B800, { 0xC0, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_8_W, _IRA_OPERAND_IB, _IRA_NA, _IRA_NA },
	// D1 /7 SAR r/m16,1 M1 Valid Valid Signed divide* r/m16 by 2, once.
	// D1 /7 SAR r/m32, 1 M1 Valid Valid Signed divide* r/m32 by 2, once.
	// REX.W + D1 /7 SAR r/m64, 1 M1 Valid N.E. Signed divide* r/m64 by 2, once.
	{ NULL, 0x0000, 0x00C5B800, { 0xD1, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_W, _IRA_EXPLICIT_OPERAND_IB(1), _IRA_NA, _IRA_NA },
	// D3 /7 SAR r/m16, CL MC Valid Valid Signed divide* r/m16 by 2, CL times.
	// D3 /7 SAR r/m32, CL MC Valid Valid Signed divide* r/m32 by 2, CL times.
	// REX.W + D3 /7 SAR r/m64, CL MC Valid N.E. Signed divide* r/m64 by 2, CL times.
	{ NULL, 0x0000, 0x00C5B800, { 0xD3, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_W, _IRA_EXPLICIT_REG( IRA_REG_GPR, _IRA_REG_CL, _IRA_OS_BYTE ), _IRA_NA, _IRA_NA },
	// C1 /7 ib SAR r/m16, imm8 MI Valid Valid Signed divide* r/m16 by 2, imm8 times.
	// C1 /7 ib SAR r/m32, imm8 MI Valid Valid Signed divide* r/m32 by 2, imm8 times.
	// REX.W + C1 /7 ib SAR r/m64, imm8 MI Valid N.E. Signed divide* r/m64 by 2, imm8 times
	{ NULL, 0x0000, 0x00C5B800, { 0xC1, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_W, _IRA_OPERAND_IB, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_SHL[] = {
	// D0 /4 SHL r/m8,1
	// REX + D0 /4 SHL r/m8,1
	{ NULL, 0x0000, 0x00C5A000, { 0xD0, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_8_W, _IRA_EXPLICIT_OPERAND_IB(1), _IRA_NA, _IRA_NA },
	// D2 /4 SHL r/m8,CL
	// REX + D2 /4 SHL r/m8,CL
	{ NULL, 0x0000, 0x00C5A000, { 0xD2, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_8_W, _IRA_EXPLICIT_REG( IRA_REG_GPR, _IRA_REG_CL, _IRA_OS_BYTE ), _IRA_NA, _IRA_NA },
	// C0 /4 ib SHL r/m8,imm8
	// REX + C0 /4 ib SHL r/m8,imm8
	{ NULL, 0x0000, 0x00C5A000, { 0xC0, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_8_W, _IRA_OPERAND_IB, _IRA_NA, _IRA_NA },
	// D1 /4 SHL r/m16,1
	// D1 /4 SHL r/m32,1
	// REX.W + D1 /4 SHL r/m64,1
	{ NULL, 0x0000, 0x00C5A000, { 0xD1, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_W, _IRA_EXPLICIT_OPERAND_IB(1), _IRA_NA, _IRA_NA },
	// D3 /4 SHL r/m16,CL
	// D3 /4 SHL r/m32,CL
	// REX.W + D3 /4 SHL r/m64,CL
	{ NULL, 0x0000, 0x00C5A000, { 0xD3, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_W, _IRA_EXPLICIT_REG( IRA_REG_GPR, _IRA_REG_CL, _IRA_OS_BYTE ), _IRA_NA, _IRA_NA },
	// C1 /4 ib SHL r/m16,imm8
	// C1 /4 ib SHL r/m32,imm8
	// REX.W + C1 /4 ib SHL r/m64,imm8
	{ NULL, 0x0000, 0x00C5A000, { 0xC1, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_W, _IRA_OPERAND_IB, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_SHR[] = {
	// D0 /5 SHR r/m8,1
	// REX + D0 /5 SHR r/m8,1
	{ NULL, 0x0000, 0x00C5A800, { 0xD0, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_8_W, _IRA_EXPLICIT_OPERAND_IB(1), _IRA_NA, _IRA_NA },
	// D2 /5 SHR r/m8,CL
	// REX + D2 /5 SHR r/m8,CL
	{ NULL, 0x0000, 0x00C5A800, { 0xD2, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_8_W, _IRA_EXPLICIT_REG( IRA_REG_GPR, _IRA_REG_CL, _IRA_OS_BYTE ), _IRA_NA, _IRA_NA },
	// C0 /5 ib SHR r/m8,imm8
	// REX + C0 /5 ib SHR r/m8,imm8
	{ NULL, 0x0000, 0x00C5A800, { 0xC0, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_8_W, _IRA_OPERAND_IB, _IRA_NA, _IRA_NA },
	// D1 /5 SHR r/m16,1
	// D1 /5 SHR r/m32,1
	// REX.W + D1 /5 SHR r/m64,1
	{ NULL, 0x0000, 0x00C5A800, { 0xD1, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_W, _IRA_EXPLICIT_OPERAND_IB(1), _IRA_NA, _IRA_NA },
	// D3 /5 SHR r/m16,CL
	// D3 /5 SHR r/m32,CL
	// REX.W + D3 /5 SHR r/m64,CL
	{ NULL, 0x0000, 0x00C5A800, { 0xD3, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_W, _IRA_EXPLICIT_REG( IRA_REG_GPR, _IRA_REG_CL, _IRA_OS_BYTE ), _IRA_NA, _IRA_NA },
	// C1 /5 ib SHR r/m16,imm8
	// C1 /5 ib SHR r/m32,imm8
	// REX.W + C1 /5 ib SHR r/m64,imm8
	{ NULL, 0x0000, 0x00C5A800, { 0xC1, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_W, _IRA_OPERAND_IB, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_SBB[] = {
	// 1C ib SBB AL,imm8
	{ NULL, 0x0001, 0x00C40000, { 0x1C, 0x00, 0x00 }, _IRA_OPERAND_REG_ACCUMULATOR_8, _IRA_OPERAND_IB, _IRA_NA, _IRA_NA },
	// 1D iw SBB AX,imm16
	// 1D id SBB EAX,imm32
	{ NULL, 0x0001, 0x00C40000, { 0x1D, 0x00, 0x00 }, _IRA_OPERAND_REG_ACCUMULATOR_OSA_W, _IRA_OPERAND_IMM_EOSA, _IRA_NA, _IRA_NA },
	// REX.W + 1D id SBB RAX,imm32
	{ NULL, 0x0009, 0x00840000, { 0x1D, 0x00, 0x00 }, _IRA_OPERAND_REG_ACCUMULATOR_OSA_W, _IRA_OPERAND_ID_EX_EOSA, _IRA_NA, _IRA_NA },
	// 80 /3 ib SBB r/m8,imm8
	// REX + 80 /3 ib SBB r/m8,imm8
	{ NULL, 0x0001, 0x00C59800, { 0x80, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_8_W, _IRA_OPERAND_IB, _IRA_NA, _IRA_NA },
	// 81 /3 iw SBB r/m16,imm16
	// 81 /3 id SBB r/m32,imm32
	{ NULL, 0x0001, 0x00C59800, { 0x81, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_W, _IRA_OPERAND_IMM_EOSA, _IRA_NA, _IRA_NA },
	// REX.W + 81 /3 id SBB r/m64,imm32
	{ NULL, 0x0009, 0x00859800, { 0x81, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_W, _IRA_OPERAND_ID_EX_EOSA, _IRA_NA, _IRA_NA },
	// 83 /3 ib SBB r/m16,imm8
	// 83 /3 ib SBB r/m32,imm8
	{ NULL, 0x0001, 0x00C59800, { 0x83, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_W, _IRA_OPERAND_IB_EX_EOSA, _IRA_NA, _IRA_NA },
	// REX.W + 83 /3 ib SBB r/m64,imm8
	{ NULL, 0x0009, 0x00859800, { 0x83, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_W, _IRA_OPERAND_IB_EX_EOSA, _IRA_NA, _IRA_NA },
	// 18 /r SBB r/m8,r8
	// REX + 18 /r SBB r/m8,r8
	{ NULL, 0x0001, 0x00C48000, { 0x18, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_8_W, _IRA_OPERAND_MODRM_R_8, _IRA_NA, _IRA_NA },
	// 19 /r SBB r/m16,r16
	// 19 /r SBB r/m32,r32
	// REX.W + 19 /r SBB r/m64,r64
	{ NULL, 0x0001, 0x00C48000, { 0x19, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_W, _IRA_OPERAND_MODRM_R, _IRA_NA, _IRA_NA },
	// 1A /r SBB r8,r/m8
	// REX + 1A /r SBB r8,r/m8
	{ NULL, 0x0001, 0x00C48000, { 0x1A, 0x00, 0x00 }, _IRA_OPERAND_MODRM_R_8_W, _IRA_OPERAND_MODRM_RM_8, _IRA_NA, _IRA_NA },
	// 1B /r SBB r16,r/m16
	// 1B /r SBB r32,r/m32
	// REX.W + 1B /r SBB r64,r/m64
	{ NULL, 0x0001, 0x00C48000, { 0x1B, 0x00, 0x00 }, _IRA_OPERAND_MODRM_R_W, _IRA_OPERAND_MODRM_RM, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_SCAS[] = {
	// AE SCAS m8 NP Valid Valid Compare AL with byte at ES:(E)DI or RDI, then set status flags.*
	{ NULL, 0x0001, 0x00C40000, { 0xAE, 0x00, 0x00 },
				_IRA_EXPLICIT_GPS_REG_ADDRESSING( _IRA_REG_DI, _IRA_EOS_BYTE, _IRA_SEG_ENCODE_REGISTER( _IRA_REG_ES, _IRA_SEG_DENY_OVERRIDE ) ),
				_IRA_NA, _IRA_NA, _IRA_NA},
	// AF SCAS m16 NP Valid Valid Compare AX with word at ES:(E)DI or RDI, then set status flags.*
	// AF SCAS m32 NP Valid Valid Compare EAX with doubleword at ES(E)DI or RDI then set status flags.*
	// REX.W + AF SCAS m64 NP Valid N.E. Compare RAX with quadword at RDI or EDI then set status flags.
	{ NULL, 0x0001, 0x00C40000, { 0xAF, 0x00, 0x00 },
				_IRA_EXPLICIT_GPS_REG_ADDRESSING( _IRA_REG_DI, _IRA_EOS_EOSA,_IRA_SEG_ENCODE_REGISTER( _IRA_REG_ES, _IRA_SEG_DENY_OVERRIDE ) ),
				_IRA_NA, _IRA_NA, _IRA_NA }
	// TODO: Assembler.
	// AE SCASB NP Valid Valid Compare AL with byte at ES:(E)DI or RDI then set status flags.*
	// AF SCASW NP Valid Valid Compare AX with word at ES:(E)DI or RDI then set status flags.*
	// AF SCASD NP Valid Valid Compare EAX with doubleword at ES:(E)DI or RDI then set status flags.*
	// REX.W + AF SCASQ NP Valid N.E. Compare RAX with quadword at RDI or EDI then set status flags.
};


struct ira_opcode_desc _ira_opcode_desc_SETcc[] = {
	// 0F 97 SETA r/m8 M Valid Valid Set byte if above (CF=0 and ZF=0).
	// REX + 0F 97 SETA r/m8*
	{ NULL, 0x0001, 0x00D80040, { 0x0F, 0x97, 0x00 }, _IRA_OPERAND_MODRM_RM_8, _IRA_NA, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_SFENCE[] = {
	{ NULL, 0x0001, 0x00EC0000, { 0x0F, 0xAE, 0xF8 }, _IRA_NA, _IRA_NA, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_SGDT[] = {
	// 0F 01 /0 SGDT m
	{ NULL, 0x0000, 0x00D98000, { 0x0F, 0x01, 0x00 }, _IRA_OPERAND_MODRM_M_UNDEF, _IRA_NA, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_SHLD[] = {
	// 0F A4 SHLD r/m16,r16,imm8 MRI Valid Valid Shift r/m16 to left imm8 places while shifting bits from r16 in from the right.
	// 0F A4 SHLD r/m32,r32,imm8 MRI Valid Valid Shift r/m32 to left imm8 places while shifting bits from r32 in from the right.
	// REX.W + 0F A4 SHLD r/m64,r64, imm8 MRI Valid N.E. Shift r/m64 to left imm8 places while shifting bits from r64 in from the right.
	{ NULL, 0x0000, 0x00D88000, { 0x0F, 0xA4, 0x00 }, _IRA_OPERAND_MODRM_RM_W, _IRA_OPERAND_MODRM_R,_IRA_OPERAND_IB, _IRA_NA },
	// 0F A5 SHLD r/m16,r16,CL MRC Valid Valid Shift r/m16 to left CL places while shifting bits from r16 in from the right.
	// 0F A5 SHLD r/m32,r32,CL MRC Valid Valid Shift r/m32 to left CL places while shifting bits from r32 in from the right.
	// REX.W + 0F A5 SHLD r/m64,r64,CL MRC Valid N.E. Shift r/m64 to left CL places while shifting bits from r64 in from the right.
	{ NULL, 0x0000, 0x00D88000, { 0x0F, 0xA5, 0x00 }, _IRA_OPERAND_MODRM_RM_W, _IRA_OPERAND_MODRM_R,_IRA_EXPLICIT_REG( IRA_REG_GPR, _IRA_REG_CL, _IRA_OS_BYTE ), _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_SHRD[] = {
	// 0F AC SHRD r/m16, r16, imm8 MRI Valid Valid Shift r/m16 to right imm8 places while shifting bits from r16 in from the left.
	// 0F AC SHRD r/m32, r32, imm8 MRI Valid Valid Shift r/m32 to right imm8 places while shifting bits from r32 in from the left.
	// REX.W + 0F AC SHRD r/m64, r64, imm8 MRI Valid N.E. Shift r/m64 to right imm8 places while shifting bits from r64 in from the left.
	{ NULL, 0x0000, 0x00D88000, { 0x0F, 0xAC, 0x00 }, _IRA_OPERAND_MODRM_RM_W, _IRA_OPERAND_MODRM_R,_IRA_OPERAND_IB, _IRA_NA },
	// 0F AD SHRD r/m16, r16, CL MRC Valid Valid Shift r/m16 to right CL places while shifting bits from r16 in from the left.
	// 0F AD SHRD r/m32, r32, CL MRC Valid Valid Shift r/m32 to right CL places while shifting bits from r32 in from the left.
	// REX.W + 0F AD SHRD r/m64, r64, CL MRC Valid N.E. Shift r/m64 to right CL places while shifting bits from r64 in from the left.
	{ NULL, 0x0000, 0x00D88000, { 0x0F, 0xAD, 0x00 }, _IRA_OPERAND_MODRM_RM_W, _IRA_OPERAND_MODRM_R,_IRA_EXPLICIT_REG( IRA_REG_GPR, _IRA_REG_CL, _IRA_OS_BYTE ), _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_SHUFPD[] = {
	// 66 0F C6 /r ib SHUFPD xmm1, xmm2/m128, imm8 RMI V/V SSE2 Shuffle packed double-precision floatingpoint values selected by imm8 from xmm1 and xmm2/m128 to xmm1.
	{ NULL, 0x1000, 0x00D88000, { 0x0F, 0xC6, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_OPERAND_IB, _IRA_NA },
	// VEX.NDS.128.66.0F.WIG C6 /r ib VSHUFPD xmm1, xmm2, xmm3/m128, imm8 RVMI V/V AVX Shuffle Packed double-precision floatingpoint values selected by imm8 from xmm2 and xmm3/mem.
	// VEX.NDS.256.66.0F.WIG C6 /r ib VSHUFPD ymm1, ymm2, ymm3/m256, imm8 RVMI V/V AVX Shuffle Packed double-precision floatingpoint values selected by imm8 from ymm2 and ymm3/mem.
	{ "vshufpd", 0x1080, 0x00D88000, { 0x0F, 0xC6, 0x00 }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_SIMD, _IRA_OPERAND_IB }
};

struct ira_opcode_desc _ira_opcode_desc_SHUFPS[] = {
	// 0F C6 /r ib SHUFPS xmm1, xmm2/m128, imm8 RMI V/V SSE Shuffle packed single-precision floating-point values selected by imm8 from xmm1 and xmm1/m128 to xmm1.
	{ NULL, 0x0000, 0x00D88000, { 0x0F, 0xC6, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_OPERAND_IB, _IRA_NA },
	// VEX.NDS.128.0F.WIG C6 /r ib VSHUFPS xmm1, xmm2, xmm3/m128, imm8 RVMI V/V AVX Shuffle Packed single-precision floating-point values selected by imm8 from xmm2 and xmm3/mem.
	// VEX.NDS.256.0F.WIG C6 /r ib VSHUFPS ymm1, ymm2, ymm3/m256, imm8 RVMI V/V AVX Shuffle Packed single-precision floating-point values selected by imm8 from ymm2 and ymm3/mem.
	{ "vshufps", 0x0080, 0x00D88000, { 0x0F, 0xC6, 0x00 }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_SIMD, _IRA_OPERAND_IB }
};

struct ira_opcode_desc _ira_opcode_desc_SIDT[] = {
	// 0F 01 /1 SIDT m M Valid Valid Store IDTR to m.
	{ NULL, 0x0000, 0x00D98800, { 0x0F, 0x01, 0x00 }, _IRA_OPERAND_MODRM_M_UNDEF, _IRA_NA, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_SLDT[] = {
	// 0F 00 /0 SLDT r/m16 M Valid Valid Stores segment selector from LDTR in r/m16.
	{ NULL, 0x0010, 0x03D98000, { 0x0F, 0x00, 0x00 }, _IRA_OPERAND_MODRM_RM_16_W, _IRA_NA, _IRA_NA, _IRA_NA },
	// REX.W + 0F 00 /0 SLDT r64/m16 M Valid Valid Stores segment selector from LDTR in r64/m16.
	{ NULL, 0x0008, 0x04998000, { 0x0F, 0x00, 0x00 }, _IRA_OPERAND_RM( IRA_REG_GPR, _IRA_EOS_QWORD, _IRA_EOS_WORD, _IRA_RMF_RM ) | _IRA_WRITE, _IRA_NA, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_SMSW[] = {
	// 0F 01 /4 SMSW r/m16 M Valid Valid Store machine status word to r/m16.
	// 0F 01 /4 SMSW r32/m16 M Valid Valid Store machine status word in low-order 16 bits of r32/m16; high-order 16 bits of r32 are undefined.
	// REX.W + 0F 01 /4 SMSW r64/m16 M Valid Valid Store machine status word in low-order 16 bits of r64/m16; high-order 16 bits of r32 are undefined.
	{ NULL, 0x0000, 0x00D9A000, { 0x0F, 0x01, 0x00 }, _IRA_OPERAND_RM( IRA_REG_GPR, _IRA_EOS_EOSA, _IRA_EOS_WORD, _IRA_RMF_RM ) | _IRA_WRITE, _IRA_NA, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_SQRTPD[] = {
	// 66 0F 51 /r SQRTPD xmm1,xmm2/m128
	{ NULL, 0x1000, 0x00D88000, { 0x0F, 0x51, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA },
	// VEX.128.66.0F.WIG 51 /r VSQRTPD xmm1,xmm2/m128
	// VEX.256.66.0F.WIG 51 /r VSQRTPD ymm1,ymm2/m256
	{ "vsqrtpd", 0x1180, 0x00D88000, { 0x0F, 0x51, 0x00 }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_OPERAND_MODRM_RM_SIMD, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_SQRTPS[] = {
	// 0F 51 /r SQRTPS xmm1,xmm2/m128 RM V/V SSE Computes square roots of the packed singleprecision floating-point values in xmm2/m128 and stores the results in xmm1.
	{ NULL, 0x0000, 0x00D88000, { 0x0F, 0x51, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_128, _IRA_NA, _IRA_NA },
	// VEX.128.0F.WIG 51 /r VSQRTPS xmm1,xmm2/m128 RM V/V AVX Computes Square Roots of the packed singleprecision floating-point values in xmm2/m128 and stores the result in xmm1.
	// VEX.256.0F.WIG 51 /r VSQRTPS ymm1,ymm2/m256 RM V/V AVX Computes Square Roots of the packed singleprecision floating-point values in ymm2/m256 and stores the result in ymm1.
	{ "vsqrtps", 0x0180, 0x00D88000, { 0x0F, 0x51, 0x00 }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_OPERAND_MODRM_RM_SIMD, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_SQRTSD[] = {
	// F2 0F 51 /r SQRTSD xmm1,xmm2/m64 RM V/V SSE2 Computes square root of the low doubleprecision floating-point value in xmm2/m64 and stores the results in xmm1.
	{ NULL, 0x2001, 0x00D88000, { 0x0F, 0x51, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_64, _IRA_NA, _IRA_NA },
	// VEX.NDS.LIG.F2.0F.WIG 51 /r VSQRTSD xmm1,xmm2,xmm3/m64 RVM V/V AVX Computes square root of the low doubleprecision floating point value in xmm3/m64 and stores the results in xmm2. Also, upper double precision floating-point value (bits[127:64]) from xmm2 is copied to xmm1[127:64].
	{ "vsqrtsd", 0x20C0, 0x00D88000, { 0x0F, 0x51, 0x00 }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_SIMD_64, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_SQRTSS[] = {
	// F3 0F 51 /r SQRTSS xmm1, xmm2/m32 RM V/V SSE Computes square root of the low singleprecision floating-point value in xmm2/m32 and stores the results in xmm1.
	{ NULL, 0x4000, 0x00D88000, { 0x0F, 0x51, 0x00 }, _IRA_OPERAND_MODRM_R_XMM_W, _IRA_OPERAND_MODRM_RM_XMM_32, _IRA_NA, _IRA_NA },
	// VEX.NDS.LIG.F3.0F.WIG 51 VSQRTSS xmm1, xmm2, xmm3/m32 RVM V/V AVX Computes square root of the low singleprecision floating-point value in xmm3/m32 and stores the results in xmm1. Also, upper single precision floating-point values (bits[127:32]) from xmm2 are copied to xmm1[127:32].
	{ "vsqrtss", 0x40C0, 0x00D88000, { 0x0F, 0x51, 0x00 }, _IRA_OPERAND_MODRM_R_SIMD_W, _IRA_VEX_VVVV_REG, _IRA_OPERAND_MODRM_RM_SIMD_32, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_STC[] = {
	// F9 STC NP Valid Valid Set CF flag.
	{ NULL, 0x0000, 0x00C40000, { 0xF9, 0x00, 0x00 }, _IRA_NA, _IRA_NA, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_STD[] = {
	// FD STD NP Valid Valid Set DF flag.
	{ NULL, 0x0000, 0x00C40000, { 0xFD, 0x00, 0x00 }, _IRA_NA, _IRA_NA, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_STI[] = {
	// FB STI NP Valid Valid Set interrupt flag; external, maskable interrupts enabled at the end of the next instruction.
	{ NULL, 0x0000, 0x00C40000, { 0xFB, 0x00, 0x00 }, _IRA_NA, _IRA_NA, _IRA_NA, _IRA_NA }
};

struct ira_opcode_desc _ira_opcode_desc_STMXCSR[] = {
	// 0F AE /3 STMXCSR m32 M V/V SSE Store contents of MXCSR register to m32.
	{ NULL, 0x0000, 0x80D99800, { 0x0F, 0xAE, 0x00 }, _IRA_OPERAND_MODRM_M_32, _IRA_NA, _IRA_NA, _IRA_NA },
	// VEX.LZ.0F.WIG AE /3 VSTMXCSR m32 M V/V AVX Store contents of MXCSR register to m32.
	{ "vstmxcsr", 0x01C0, 0x80D99800, { 0x0F, 0xAE, 0x00 }, _IRA_OPERAND_MODRM_M_32, _IRA_NA, _IRA_NA, _IRA_NA }
};

/*
struct ira_instruction_desc _ira_instructions_desc[] = {
	_IA_INSTRUCTION( "blendpd", _ira_opcode_desc_BLENDPD ),
	{ NULL, 0, 0, NULL }
};
*/

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
		_IA_INSTRUCTION( "vbroadcastss", _ira_opcode_desc_VBROADCASTSS),
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
		_IA_INSTRUCTION( "vextractf128", _ira_opcode_desc_VEXTRACTF128),
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
		_IA_INSTRUCTION( "vinsertf128", _ira_opcode_desc_VINSERTF128 ),
		_IA_INSTRUCTION( "int", _ira_opcode_desc_INT ),
		_IA_INSTRUCTION( "invd", _ira_opcode_desc_INVD ),
		_IA_INSTRUCTION( "invlpg", _ira_opcode_desc_INVLPG ),
		_IA_INSTRUCTION( "invpcid", _ira_opcode_desc_INVPCID ),
		_IA_INSTRUCTION( "iret", _ira_opcode_desc_IRET ),
		_IA_INSTRUCTION( "jcxz", _ira_opcode_desc_JCXZ),
		_IA_INSTRUCTION( "j", _ira_opcode_desc_Jcc),
		_IA_INSTRUCTION( "jmp", _ira_opcode_desc_JMP),
		_IA_INSTRUCTION( "lahf", _ira_opcode_desc_LAHF),
		_IA_INSTRUCTION( "lar", _ira_opcode_desc_LAR),
		_IA_INSTRUCTION( "lddqu", _ira_opcode_desc_LDDQU),
		_IA_INSTRUCTION( "ldmxcsr", _ira_opcode_desc_LDMXCSR),
		_IA_INSTRUCTION( "vldmxcsr", _ira_opcode_desc_VLDMXCSR),
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
		_IA_INSTRUCTION( _IRA_EMPTY_MNEMONIC, _ira_opcode_desc_VMASKMOVP),
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
		_IA_INSTRUCTION( "mov", _ira_opcode_desc_MOV),
		_IA_INSTRUCTION( "mov", _ira_opcode_desc_MOV_CR),
		_IA_INSTRUCTION( "mov", _ira_opcode_desc_MOV_DR),
		_IA_INSTRUCTION( "movd", _ira_opcode_desc_MOVD),
		_IA_INSTRUCTION( "movddup", _ira_opcode_desc_MOVDDUP),
		_IA_INSTRUCTION( "movdqa", _ira_opcode_desc_MOVDQA),
		_IA_INSTRUCTION( "movdqu", _ira_opcode_desc_MOVDQU),
		_IA_INSTRUCTION( "movdq2q", _ira_opcode_desc_MOVDQ2Q),
		_IA_INSTRUCTION( "movhlps", _ira_opcode_desc_MOVHLPS),
		_IA_INSTRUCTION( "movhpd", _ira_opcode_desc_MOVHPD),
		_IA_INSTRUCTION( "movhps", _ira_opcode_desc_MOVHPS),
		_IA_INSTRUCTION( "movlhps", _ira_opcode_desc_MOVLHPS),
		_IA_INSTRUCTION( "movlpd", _ira_opcode_desc_MOVLPD),
		_IA_INSTRUCTION( "movlps", _ira_opcode_desc_MOVLPS),
		_IA_INSTRUCTION( "movmskpd", _ira_opcode_desc_MOVMSKPD),
		_IA_INSTRUCTION( "movmskps", _ira_opcode_desc_MOVMSKPS),
		_IA_INSTRUCTION( "movntdqa", _ira_opcode_desc_MOVNTDQA),
		_IA_INSTRUCTION( "movntdq", _ira_opcode_desc_MOVNTDQ),
		_IA_INSTRUCTION( "movnti", _ira_opcode_desc_MOVNTI),
		_IA_INSTRUCTION( "movntpd", _ira_opcode_desc_MOVNTPD),
		_IA_INSTRUCTION( "movntps", _ira_opcode_desc_MOVNTPS),
		_IA_INSTRUCTION( "movntq", _ira_opcode_desc_MOVNTQ),
		_IA_INSTRUCTION( "movq", _ira_opcode_desc_MOVQ),
		_IA_INSTRUCTION( "movq2dq", _ira_opcode_desc_MOVQ2DQ),
		_IA_INSTRUCTION( "movs", _ira_opcode_desc_MOVS),
		_IA_INSTRUCTION( "movsd", _ira_opcode_desc_MOVSD),
		_IA_INSTRUCTION( "movshdup", _ira_opcode_desc_MOVSHDUP),
		_IA_INSTRUCTION( "movsldup", _ira_opcode_desc_MOVSLDUP),
		_IA_INSTRUCTION( "movss", _ira_opcode_desc_MOVSS),
		_IA_INSTRUCTION( "movsx", _ira_opcode_desc_MOVSX),
		_IA_INSTRUCTION( "movupd", _ira_opcode_desc_MOVUPD),
		_IA_INSTRUCTION( "movups", _ira_opcode_desc_MOVUPS),
		_IA_INSTRUCTION( "movzx", _ira_opcode_desc_MOVZX),
		_IA_INSTRUCTION( "mpsadbw", _ira_opcode_desc_MPSADBW),
		_IA_INSTRUCTION( "mul", _ira_opcode_desc_MUL),
		_IA_INSTRUCTION( "mulpd", _ira_opcode_desc_MULPD),
		_IA_INSTRUCTION( "mulps", _ira_opcode_desc_MULPS),
		_IA_INSTRUCTION( "mulsd", _ira_opcode_desc_MULSD),
		_IA_INSTRUCTION( "mulss", _ira_opcode_desc_MULSS),
		_IA_INSTRUCTION( "mwait", _ira_opcode_desc_MWAIT),
		_IA_INSTRUCTION( "neg", _ira_opcode_desc_NEG),
		_IA_INSTRUCTION( "nop", _ira_opcode_desc_NOP),
		_IA_INSTRUCTION( "not", _ira_opcode_desc_NOT),
		_IA_INSTRUCTION( "or", _ira_opcode_desc_OR),
		_IA_INSTRUCTION( "orpd", _ira_opcode_desc_ORPD),
		_IA_INSTRUCTION( "orps", _ira_opcode_desc_ORPS),
		_IA_INSTRUCTION( "out", _ira_opcode_desc_OUT),
		_IA_INSTRUCTION( "outs", _ira_opcode_desc_OUTS),
		_IA_INSTRUCTION( _IRA_EMPTY_MNEMONIC, _ira_opcode_desc_PABS),
		_IA_INSTRUCTION( _IRA_EMPTY_MNEMONIC, _ira_opcode_desc_PACKSS),
		_IA_INSTRUCTION( _IRA_EMPTY_MNEMONIC, _ira_opcode_desc_PACKUSD),
		_IA_INSTRUCTION( _IRA_EMPTY_MNEMONIC, _ira_opcode_desc_PACKUSW),
		_IA_INSTRUCTION( _IRA_EMPTY_MNEMONIC, _ira_opcode_desc_PADD),
		_IA_INSTRUCTION( _IRA_EMPTY_MNEMONIC, _ira_opcode_desc_PADDS),
		_IA_INSTRUCTION( _IRA_EMPTY_MNEMONIC, _ira_opcode_desc_PADDUS),
		_IA_INSTRUCTION( "palignr", _ira_opcode_desc_PALIGNR),
		_IA_INSTRUCTION( "pand", _ira_opcode_desc_PAND),
		_IA_INSTRUCTION( "pandn", _ira_opcode_desc_PANDN),
		_IA_INSTRUCTION( "pause", _ira_opcode_desc_PAUSE),
		_IA_INSTRUCTION( _IRA_EMPTY_MNEMONIC, _ira_opcode_desc_PAVG),
		_IA_INSTRUCTION( "pblendvb", _ira_opcode_desc_PBLENDVB),
		_IA_INSTRUCTION( "pblendw", _ira_opcode_desc_PBLENDW),
		_IA_INSTRUCTION( "pclmulqdq", _ira_opcode_desc_PCLMULQDQ),
		_IA_INSTRUCTION( _IRA_EMPTY_MNEMONIC, _ira_opcode_desc_PCMPEQ),
		_IA_INSTRUCTION( "pcmpeqq", _ira_opcode_desc_PCMPEQQ),
		_IA_INSTRUCTION( "pcmpestri", _ira_opcode_desc_PCMPESTRI),
		_IA_INSTRUCTION( "pcmpestrm", _ira_opcode_desc_PCMPESTRM),
		_IA_INSTRUCTION( _IRA_EMPTY_MNEMONIC, _ira_opcode_desc_PCMPGT),
		_IA_INSTRUCTION( "pcmpgtq", _ira_opcode_desc_PCMPGTQ),
		_IA_INSTRUCTION( "pcmpistri", _ira_opcode_desc_PCMPISTRI),
		_IA_INSTRUCTION( "pcmpistrm", _ira_opcode_desc_PCMPISTRM),
		_IA_INSTRUCTION( "pextr", _ira_opcode_desc_PEXTR),
		_IA_INSTRUCTION( "pextrw", _ira_opcode_desc_PEXTRW),
		_IA_INSTRUCTION( _IRA_EMPTY_MNEMONIC, _ira_opcode_desc_PHADD),
		_IA_INSTRUCTION( "phaddsw", _ira_opcode_desc_PHADDSW),
		_IA_INSTRUCTION( "phminposuw", _ira_opcode_desc_PHMINPOSUW),
		_IA_INSTRUCTION( _IRA_EMPTY_MNEMONIC, _ira_opcode_desc_PHSUB),
		_IA_INSTRUCTION( "phsubsw", _ira_opcode_desc_PHSUBSW),
		_IA_INSTRUCTION( _IRA_EMPTY_MNEMONIC, _ira_opcode_desc_PINSR),
		_IA_INSTRUCTION( "pinsrw", _ira_opcode_desc_PINSRW),
		_IA_INSTRUCTION( "pmaddubsw", _ira_opcode_desc_PMADDUBSW),
		_IA_INSTRUCTION( "pmaddwd", _ira_opcode_desc_PMADDWD),
		_IA_INSTRUCTION( "pmaxsb", _ira_opcode_desc_PMAXSB),
		_IA_INSTRUCTION( "pmaxsd", _ira_opcode_desc_PMAXSD),
		_IA_INSTRUCTION( "pmaxsw", _ira_opcode_desc_PMAXSW),
		_IA_INSTRUCTION( "pmaxub", _ira_opcode_desc_PMAXUB),
		_IA_INSTRUCTION( "pmaxud", _ira_opcode_desc_PMAXUD),
		_IA_INSTRUCTION( "pmaxuw", _ira_opcode_desc_PMAXUW),
		_IA_INSTRUCTION( "pminsb", _ira_opcode_desc_PMINSB),
		_IA_INSTRUCTION( "pminsd", _ira_opcode_desc_PMINSD),
		_IA_INSTRUCTION( "pminsw", _ira_opcode_desc_PMINSW),
		_IA_INSTRUCTION( "pminuw", _ira_opcode_desc_PMINUW),
		_IA_INSTRUCTION( "pminub", _ira_opcode_desc_PMINUB),
		_IA_INSTRUCTION( "pminud", _ira_opcode_desc_PMINUD),
		_IA_INSTRUCTION( "pmovmskb", _ira_opcode_desc_PMOVMSKB),
		_IA_INSTRUCTION( _IRA_EMPTY_MNEMONIC, _ira_opcode_desc_PMOVSX),
		_IA_INSTRUCTION( _IRA_EMPTY_MNEMONIC, _ira_opcode_desc_PMOVZX),
		_IA_INSTRUCTION( "pmuldq", _ira_opcode_desc_PMULDQ),
		_IA_INSTRUCTION( "pmulhrsw", _ira_opcode_desc_PMULHRSW),
		_IA_INSTRUCTION( "pmulhuw", _ira_opcode_desc_PMULHUW),
		_IA_INSTRUCTION( "pmulhw", _ira_opcode_desc_PMULHW),
		_IA_INSTRUCTION( "pmuludq", _ira_opcode_desc_PMULUDQ),
		_IA_INSTRUCTION( "pmullw", _ira_opcode_desc_PMULLW),
		_IA_INSTRUCTION( "pmulld", _ira_opcode_desc_PMULLD),
		_IA_INSTRUCTION( "pop", _ira_opcode_desc_POP),
		_IA_INSTRUCTION( "popa", _ira_opcode_desc_POPA),
		_IA_INSTRUCTION( "popcnt", _ira_opcode_desc_POPCNT),
		_IA_INSTRUCTION( "popf", _ira_opcode_desc_POPF),
		_IA_INSTRUCTION( "por", _ira_opcode_desc_POR),
		_IA_INSTRUCTION( _IRA_EMPTY_MNEMONIC, _ira_opcode_desc_PREFETCHT),
		_IA_INSTRUCTION( "psadbw", _ira_opcode_desc_PSADBW),
		_IA_INSTRUCTION( "pshufb", _ira_opcode_desc_PSHUFB),
		_IA_INSTRUCTION( "pshufd", _ira_opcode_desc_PSHUFD),
		_IA_INSTRUCTION( "pshufhw", _ira_opcode_desc_PSHUFHW),
		_IA_INSTRUCTION( "pshuflw", _ira_opcode_desc_PSHUFLW),
		_IA_INSTRUCTION( "pshufw", _ira_opcode_desc_PSHUFW),
		_IA_INSTRUCTION( _IRA_EMPTY_MNEMONIC, _ira_opcode_desc_PSIGN),
		_IA_INSTRUCTION( "psrldq", _ira_opcode_desc_PSRLDQ),
		_IA_INSTRUCTION( _IRA_EMPTY_MNEMONIC, _ira_opcode_desc_PSRL),
		_IA_INSTRUCTION( _IRA_EMPTY_MNEMONIC, _ira_opcode_desc_PSUB),
		_IA_INSTRUCTION( "psubq", _ira_opcode_desc_PSUBQ),
		_IA_INSTRUCTION( _IRA_EMPTY_MNEMONIC, _ira_opcode_desc_PSUBS),
		_IA_INSTRUCTION( _IRA_EMPTY_MNEMONIC, _ira_opcode_desc_PSUBUS),
		_IA_INSTRUCTION( "ptest", _ira_opcode_desc_PTEST),
		_IA_INSTRUCTION( _IRA_EMPTY_MNEMONIC, _ira_opcode_desc_PUNPCKL),
		_IA_INSTRUCTION( _IRA_EMPTY_MNEMONIC, _ira_opcode_desc_PUNPCKH),
		_IA_INSTRUCTION( "push", _ira_opcode_desc_PUSH),
		_IA_INSTRUCTION( "pusha", _ira_opcode_desc_PUSHA),
		_IA_INSTRUCTION( "pushf", _ira_opcode_desc_PUSHF),
		_IA_INSTRUCTION( "pxor", _ira_opcode_desc_PXOR),
		_IA_INSTRUCTION( "rcl", _ira_opcode_desc_RCL),
		_IA_INSTRUCTION( "rcr", _ira_opcode_desc_RCR),
		_IA_INSTRUCTION( "rol", _ira_opcode_desc_ROL),
		_IA_INSTRUCTION( "ror", _ira_opcode_desc_ROR),
		_IA_INSTRUCTION( "rcpps", _ira_opcode_desc_RCPPS),
		_IA_INSTRUCTION( "rcpss", _ira_opcode_desc_RCPSS),
		_IA_INSTRUCTION( "rdfsbase", _ira_opcode_desc_RDFSBASE),
		_IA_INSTRUCTION( "rdrand", _ira_opcode_desc_RDRAND),
		_IA_INSTRUCTION( "rdtscp", _ira_opcode_desc_RDTSCP),
		_IA_INSTRUCTION( "rdtsc", _ira_opcode_desc_RDTSC),
		_IA_INSTRUCTION( "rdpmc", _ira_opcode_desc_RDPMC),
		_IA_INSTRUCTION( "rdmsr", _ira_opcode_desc_RDMSR),
		_IA_INSTRUCTION( "ret", _ira_opcode_desc_RET),
		_IA_INSTRUCTION( "roundpd", _ira_opcode_desc_ROUNDPD),
		_IA_INSTRUCTION( "roundps", _ira_opcode_desc_ROUNDPS),
		_IA_INSTRUCTION( "roundsd", _ira_opcode_desc_ROUNDSD),
		_IA_INSTRUCTION( "roundss", _ira_opcode_desc_ROUNDSS),
		_IA_INSTRUCTION( "rsm", _ira_opcode_desc_RSM),
		_IA_INSTRUCTION( "rsqrtps", _ira_opcode_desc_RSQRTPS),
		_IA_INSTRUCTION( "rsqrtss", _ira_opcode_desc_RSQRTSS),
		_IA_INSTRUCTION( "sahf", _ira_opcode_desc_SAHF),
		_IA_INSTRUCTION( "sar", _ira_opcode_desc_SAR),
		_IA_INSTRUCTION( "shl", _ira_opcode_desc_SHL),
		_IA_INSTRUCTION( "shr", _ira_opcode_desc_SHR),
		_IA_INSTRUCTION( "sbb", _ira_opcode_desc_SBB),
		_IA_INSTRUCTION( "scas", _ira_opcode_desc_SCAS),
		_IA_INSTRUCTION( "set", _ira_opcode_desc_SETcc),
		_IA_INSTRUCTION( "sfence", _ira_opcode_desc_SFENCE),
		_IA_INSTRUCTION( "sgdt", _ira_opcode_desc_SGDT),
		_IA_INSTRUCTION( "shld", _ira_opcode_desc_SHLD),
		_IA_INSTRUCTION( "shrd", _ira_opcode_desc_SHRD),
		_IA_INSTRUCTION( "shufpd", _ira_opcode_desc_SHUFPD),
		_IA_INSTRUCTION( "shufps", _ira_opcode_desc_SHUFPS),
		_IA_INSTRUCTION( "sidt", _ira_opcode_desc_SIDT),
		_IA_INSTRUCTION( "sldt", _ira_opcode_desc_SLDT),
		_IA_INSTRUCTION( "smsw", _ira_opcode_desc_SMSW),
		_IA_INSTRUCTION( "sqrtpd", _ira_opcode_desc_SQRTPD),
		_IA_INSTRUCTION( "sqrtps", _ira_opcode_desc_SQRTPS),
		_IA_INSTRUCTION( "sqrtsd", _ira_opcode_desc_SQRTSD),
		_IA_INSTRUCTION( "sqrtss", _ira_opcode_desc_SQRTSS),
		_IA_INSTRUCTION( "stc", _ira_opcode_desc_STC),
		_IA_INSTRUCTION( "std", _ira_opcode_desc_STD),
		_IA_INSTRUCTION( "sti", _ira_opcode_desc_STI),
		_IA_INSTRUCTION( "stmxcsr", _ira_opcode_desc_STMXCSR),
		{ NULL, 0, 0, NULL }
};
