/*
 * ira_def.c
 *
 *  Created on: 19-11-2010
 *      Author: Slawomir Wojtasiak
 */

#include "fcml_def.h"

// Instruction descriptions.

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_AAA[] = {
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00440000, { 0x37, 0x00, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_AAD[] = {
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00580000, { 0xD5, 0x0A, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00440000, { 0xD5, 0x00, 0x00 }, { FCML_OP_IB, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_AAM[] = {
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00580000, { 0xD4, 0x0A, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00440000, { 0xD4, 0x00, 0x00 }, { FCML_OP_IB, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_AAS[] = {
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00440000, { 0x3F, 0x00, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_ADC[] = {
	// 14 ib ADC AL, imm8 C Valid Valid Add with carry imm8 to AL.
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00C40000, { 0x14, 0x00, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_AL, FCML_EOS_BYTE ), FCML_OP_IB, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 15 iw ADC AX, imm16 C Valid Valid Add with carry imm16 to AX.
	// 15 id ADC EAX, imm32 C Valid Valid Add with carry imm32 to EAX.
	{ NULL, FCML_AMT_GPI, 0x0010, 0x00C40000, { 0x15, 0x00, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_AL, FCML_EOS_EOSA ) | FCML_OA_W, FCML_OP_IMM_EOSA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// REX.W + 15 id ADC RAX, imm32 C Valid N.E. Add with carry imm32 sign extended to 64-bits to RAX.
	{ NULL, FCML_AMT_GPI, 0x0008, 0x04840000, { 0x15, 0x00, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_AL, FCML_EOS_EOSA ) | FCML_OA_W, FCML_OP_ID_EX_EOSA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 80 /2 ib ADC r/m8, imm8 B Valid Valid Add with carry imm8 to r/m8.
	// REX + 80 /2 ib ADC r/m8*, imm8 B Valid N.E. Add with carry imm8 to r/m8.
	{ NULL, FCML_AMT_GPI, 0x0807, 0x00C59000, { 0x80, 0x00, 0x00 }, { FCML_OP_MODRM_RM_8_W, FCML_OP_IB, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 81 /2 iw ADC r/m16, imm16 B Valid Valid Add with carry imm16 to r/m16.
	// 81 /2 id ADC r/m32, imm32 B Valid Valid Add with CF imm32 to r/m32.
	{ NULL, FCML_AMT_GPI, 0x0817, 0x03C59000, { 0x81, 0x00, 0x00 }, { FCML_OP_MODRM_RM_W, FCML_OP_IMM_EOSA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// REX.W + 81 /2 id ADC r/m64, imm32 B Valid N.E. Add with CF imm32 sign extended to 64-bits to r/m64.
	{ NULL, FCML_AMT_GPI, 0x080F, 0x04859000, { 0x81, 0x00, 0x00 }, { FCML_OP_MODRM_RM_W, FCML_OP_ID_EX_EOSA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 83 /2 ib ADC r/m16, imm8 B Valid Valid Add with CF sign-extended imm8 to r/m16.
	// 83 /2 ib ADC r/m32, imm8 B Valid Valid Add with CF sign-extended imm8 into r/m32.
	{ NULL, FCML_AMT_GPI, 0x0817, 0x00C59000, { 0x83, 0x00, 0x00 }, { FCML_OP_MODRM_RM_W, FCML_OP_IB_EX_EOSA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// REX.W + 83 /2 ib ADC r/m64, imm8 B Valid N.E. Add with CF sign-extended imm8 into r/m64.
	{ NULL, FCML_AMT_GPI, 0x080F, 0x04859000, { 0x83, 0x00, 0x00 }, { FCML_OP_MODRM_RM_W, FCML_OP_IB_EX_EOSA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 10 /r ADC r/m8, r8 A Valid Valid Add with carry byte register to r/m8.
	// REX + 10 /r ADC r/m8*, r8* A Valid N.E. Add with carry byte register to r/m64.
	{ NULL, FCML_AMT_GPI, 0x0807, 0x00C48000, { 0x10, 0x00, 0x00 }, { FCML_OP_MODRM_RM_8_W, FCML_OP_MODRM_R_8, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 11 /r ADC r/m16, r16 A Valid Valid Add with carry r16 to r/m16.
	// 11 /r ADC r/m32, r32 A Valid Valid Add with CF r32 to r/m32.
	// REX.W + 11 /r ADC r/m64, r64 A Valid N.E. Add with CF r64 to r/m64.
	{ NULL, FCML_AMT_GPI, 0x0807, 0x00C48000, { 0x11, 0x00, 0x00 }, { FCML_OP_MODRM_RM_W, FCML_OP_MODRM_R, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 12 /r ADC r8, r/m8 A Valid Valid Add with carry r/m8 to byte register.
	// REX + 12 /r ADC r8*, r/m8* A Valid N.E. Add with carry r/m64 to byte register.
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00C48000, { 0x12, 0x00, 0x00 }, { FCML_OP_MODRM_R_8_W, FCML_OP_MODRM_RM_8, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 13 /r ADC r16, r/m16 A Valid Valid Add with carry r/m16 to r16.
	// 13 /r ADC r32, r/m32 A Valid Valid Add with CF r/m32 to r32.
	// REX.W + 13 /r ADC r64, r/m64 A Valid N.E. Add with CF r/m64 to r64.
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00C48000, { 0x13, 0x00, 0x00 }, { FCML_OP_MODRM_R_W, FCML_OP_MODRM_RM, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_ADD[] = {
	// 04 ib ADD AL, imm8 C Valid Valid Add imm8 to AL..
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00C40000, { 0x04, 0x00, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_AL, FCML_EOS_BYTE ), FCML_OP_IB, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 05 iw ADD AX, imm16 C Valid Valid Add imm16 to AX.
	// 05 id ADD EAX, imm32 C Valid Valid Add imm32 to EAX.
	{ NULL, FCML_AMT_GPI, 0x0010, 0x03C40000, { 0x05, 0x00, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_AL, FCML_EOS_EOSA ) | FCML_OA_W, FCML_OP_IMM_EOSA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// REX.W + 05 id ADD RAX, imm32 C Valid N.E. Add imm32 sign-extended to 64-bits to RAX.
	{ NULL, FCML_AMT_GPI, 0x0008, 0x04840000, { 0x05, 0x00, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_AL, FCML_EOS_EOSA ) | FCML_OA_W, FCML_OP_ID_EX_EOSA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 80 /0 ib ADD r/m8, imm8 B Valid Valid Add imm8 to r/m8.
	// REX + 80 /0 ib ADD r/m8*, imm8 B Valid N.E. Add sign-extended imm8 to r/m64.
	{ NULL, FCML_AMT_GPI, 0x0807, 0x00C58000, { 0x80, 0x00, 0x00 }, { FCML_OP_MODRM_RM_8_W, FCML_OP_IB, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 81 /0 iw ADD r/m16, imm16 B Valid Valid Add imm16 to r/m16.
	// 81 /0 id ADD r/m32, imm32 B Valid Valid Add imm32 to r/m32.
	{ NULL, FCML_AMT_GPI, 0x0817, 0x03C58000, { 0x81, 0x00, 0x00 }, { FCML_OP_MODRM_RM_W, FCML_OP_IMM_EOSA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// REX.W + 81 /0 id ADD r/m64, imm32 B Valid N.E. Add imm32 sign-extended to 64-bits to r/m64.
	{ NULL, FCML_AMT_GPI, 0x080F, 0x04858000, { 0x81, 0x00, 0x00 }, { FCML_OP_MODRM_RM_W, FCML_OP_ID_EX_EOSA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 83 /0 ib ADD r/m16, imm8 B Valid Valid Add sign-extended imm8 to r/m16.
	// 83 /0 ib ADD r/m32, imm8 B Valid Valid Add sign-extended imm8 to r/m32.
	{ NULL, FCML_AMT_GPI, 0x0817, 0x03C58000, { 0x83, 0x00, 0x00 }, { FCML_OP_MODRM_RM_W, FCML_OP_IB_EX_EOSA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// REX.W + 83 /0 ib ADD r/m64, imm8 B Valid N.E. Add sign-extended imm8 to r/m64.
	{ NULL, FCML_AMT_GPI, 0x080F, 0x04858000, { 0x83, 0x00, 0x00 }, { FCML_OP_MODRM_RM_W, FCML_OP_IB_EX_EOSA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 00 /r ADD r/m8, r8 A Valid Valid Add r8 to r/m8.
	// REX + 00 /r ADD r/m8*, r8* A Valid N.E. Add r8 to r/m8.
	{ NULL, FCML_AMT_GPI, 0x0807, 0x00C48000, { 0x00, 0x00, 0x00 }, { FCML_OP_MODRM_RM_8_W, FCML_OP_MODRM_R_8, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 01 /r ADD r/m16, r16 A Valid Valid Add r16 to r/m16.
	// 01 /r ADD r/m32, r32 A Valid Valid Add r32 to r/m32.
	// REX.W + 01 /r ADD r/m64, r64 A Valid N.E. Add r64 to r/m64.
	{ NULL, FCML_AMT_GPI, 0x0807, 0x00C48000, { 0x01, 0x00, 0x00 }, { FCML_OP_MODRM_RM_W, FCML_OP_MODRM_R, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 02 /r ADD r8, r/m8 A Valid Valid Add r/m8 to r8.
	// REX + 02 /r ADD r8*, r/m8* A Valid N.E. Add r/m8 to r8.
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00C48000, { 0x02, 0x00, 0x00 }, { FCML_OP_MODRM_R_8_W, FCML_OP_MODRM_RM_8, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 03 /r ADD r16, r/m16 A Valid Valid Add r/m16 to r16.
	// 03 /r ADD r32, r/m32 A Valid Valid Add r/m32 to r32.
	// REX.W + 03 /r ADD r64, r/m64 A Valid N.E. Add r/m64 to r64.
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00C48000, { 0x03, 0x00, 0x00 }, { FCML_OP_MODRM_R_W, FCML_OP_MODRM_RM, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_ADDPD[] = {
	// 66 0F 58 /r ADDPD xmm1, xmm2/m128 A Valid Valid Add packed double-precision floating-point values from xmm2/m128 to xmm1.
	{ NULL, FCML_AMT_SSE2_SIMD, 0x1000, 0x00D88000, { 0x0F, 0x58, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.66.0F.WIG 58 /r VADDPD xmm1, xmm2, xmm3/m128 V/V AVX Add packed double-precision floating-point values from xmm3/mem to xmm2 and stores result in xmm1.
	// VEX.NDS.256.66.0F.WIG 58 /r VADDPD ymm1, ymm2, ymm3/m256 Add packed double-precision floating-point values from ymm3/mem to ymm2 and stores result in ymm1.
	{ "vaddpd", FCML_AMT_AVX_SIMD, 0x1080, 0x00D88000, { 0x0F, 0x58, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_ADDPS[] = {
	// 0F 58 /r ADDPS xmm1, xmm2/m128 A Valid Valid Add packed single-precision floating-point values from xmm2/m128 to xmm1.
	{ NULL, FCML_AMT_SSE_SIMD, 0x0000, 0x00D88000, { 0x0F, 0x58, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.0F 58 /r VADDPS xmm1,xmm2, xmm3/m128
	// VEX.NDS.256.0F 58 /r VADDPS ymm1, ymm2, ymm3/m256
	{ "vaddps", FCML_AMT_AVX_SIMD, 0x0080, 0x00D88000, { 0x0F, 0x58, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_ADDSD[] = {
	// F2 0F 58 /r ADDSD xmm1, xmm2/m64 A Valid Valid Add the low doubleprecision floating-point value from xmm2/m64 to xmm1.
	{ NULL, FCML_AMT_SSE2_SIMD, 0x2000, 0x00D88000, { 0x0F, 0x58, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.F2.0F 58 /r VADDSD xmm1,xmm2,xmm3/m64
	{ "vaddsd", FCML_AMT_AVX_SIMD, 0x20C0, 0x00D88000, { 0x0F, 0x58, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L_64, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_ADDSS[] = {
	// F3 0F 58 /r ADDSS xmm1, xmm2/m32 A Valid Valid Add the low single-precision floating-point value from xmm2/m32 to xmm1.
	{ NULL, FCML_AMT_SSE_SIMD, 0x4000, 0x00D88000, { 0x0F, 0x58, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_32, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.F3.0F 58 /r VADDSS xmm1,xmm2, xmm3/m32
	{ "vaddss", FCML_AMT_AVX_SIMD, 0x40C0, 0x00D88000, { 0x0F, 0x58, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L_32, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_ADDSUBPD[] = {
	//66 0F D0 /r ADDSUBPD xmm1, xmm2/m128 A Valid Valid Add/subtract doubleprecision floating-point values from xmm2/m128 to xmm1.
	{ NULL, FCML_AMT_SSE3_SIMD, 0x1000, 0x00D88000, { 0x0F, 0xD0, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.66.0F D0 /r VADDSUBPD xmm1,xmm2,xmm3/m128
	// VEX.NDS.256.66.0F D0 /r VADDSUBPD ymm1,ymm2,ymm3/m256
	{ "vaddsubpd", FCML_AMT_AVX_SIMD, 0x1080, 0x00D88000, { 0x0F, 0xD0, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_ADDSUBPS[] = {
	// F2 0F D0 /r ADDSUBPS xmm1, xmm2/m128 A Valid Valid Add/subtract singleprecision floating-point values from xmm2/m128 to xmm1.
	{ NULL, FCML_AMT_SSE3_SIMD, 0x2000, 0x00D88000, { 0x0F, 0xD0, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.F2.0F D0 /r VADDSUBPS xmm1,xmm2,xmm3/m128
	// VEX.NDS.256.F2.0F D0 /r VADDSUBPS ymm1, ymm2,ymm3/m256
	{ "vaddsubps", FCML_AMT_AVX_SIMD, 0x2080, 0x00D88000, { 0x0F, 0xD0, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_AESDEC[] = {
	// 66 0F 38 DE /r AESDEC xmm1,xmm2/m128
	{ NULL, FCML_AMT_AES, 0x1000, 0x00EC8000, { 0x0F, 0x38, 0xDE }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.66.0F38.WIG DE /r VAESDEC xmm1,xmm2,xmm3/m128
	{ "vaesdec", FCML_AMT_AVX | FCML_AMT_AES, 0x10C0, 0x00EC8000, { 0x0F, 0x38, 0xDE }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_AESDECLAST[] = {
	// 66 0F 38 DF /r AESDECLAST xmm1,xmm2/m128
	{ NULL, FCML_AMT_AES, 0x1000, 0x00EC8000, { 0x0F, 0x38, 0xDF }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.66.0F38.WIG DF /r VAESDECLAST xmm1,xmm2,xmm3/m128
	{ "vaesdeclast", FCML_AMT_AVX | FCML_AMT_AES, 0x10C0, 0x00EC8000, { 0x0F, 0x38, 0xDF }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_AESENC[] = {
	// 66 0F 38 DC /r AESENC xmm1, xmm2/m128 A Valid Valid Perform one round of an AES encryption flow, operating on a 128-bit data (state) from xmm1 with a 128-bit round key from xmm2/m128.
	{ NULL, FCML_AMT_AES, 0x1000, 0x00EC8000, { 0x0F, 0x38, 0xDC }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.66.0F38.WIG DC /r VAESENC xmm1, xmm2, xmm3/m128
	{ "vaesenc", FCML_AMT_AVX | FCML_AMT_AES, 0x10C0, 0x00EC8000, { 0x0F, 0x38, 0xDC }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_AESENCLAST[] = {
	//66 0F 38 DD /r AESENCLAST xmm1, xmm2/m128 A Valid Valid Perform the last round of an AES encryption flow, operating on a 128-bit data (state) from xmm1 with a 128-bit round key from xmm2/m128.
	{ NULL, FCML_AMT_AES, 0x1000, 0x00EC8000, { 0x0F, 0x38, 0xDD }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.66.0F38.WIG DD /r VAESENCLAST xmm1,xmm2,xmm3/m128
	{ "vaesenclast", FCML_AMT_AVX | FCML_AMT_AES, 0x10C0, 0x00EC8000, { 0x0F, 0x38, 0xDD }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_AESIMC[] = {
	// 66 0F 38 DB /r AESIMC xmm1, xmm2/m128 A Valid Valid Perform the InvMixColumn transformation on a 128-bit round key from xmm2/m128 and store the result in xmm1.
	{ NULL, FCML_AMT_AES, 0x1000, 0x00EC8000, { 0x0F, 0x38, 0xDB }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.128.66.0F38.WIG DB /r VAESIMC xmm1, xmm2/m128
	{ "vaesimc", FCML_AMT_AVX | FCML_AMT_AES, 0x10C0, 0x00EC8000, { 0x0F, 0x38, 0xDB }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_AESKEYGENASSIST[] = {
	// 66 0F 3A DF /r ib AESKEYGENASSIST xmm1, xmm2/m128, imm8 A Valid Valid Assist in AES round key generation using an 8 bits Round Constant (RCON) specified in the immediate byte, operating on 128 bits of data specified in xmm2/m128 and stores the result in xmm1.
	{ NULL, FCML_AMT_AES, 0x1000, 0x00EC8000, { 0x0F, 0x3A, 0xDF }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.128.66.0F3A.WIG DF /r ib VAESKEYGENASSIST xmm1,xmm2/m128,imm8
	{ "vaeskeygenassist", FCML_AMT_AVX | FCML_AMT_AES, 0x11C0, 0x00EC8000, { 0x0F, 0x3A, 0xDF }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_AND[] = {
	// 24 ib AND AL, imm8 C Valid Valid AL AND imm8.
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00C40000, { 0x24, 0x00, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_AL, FCML_EOS_BYTE ), FCML_OP_IB, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 25 iw AND AX, imm16 C Valid Valid AX AND imm16.
	// 25 id AND EAX, imm32 C Valid Valid EAX AND imm32.
	{ NULL, FCML_AMT_GPI, 0x0010, 0x03C40000, { 0x25, 0x00, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_AL, FCML_EOS_EOSA ) | FCML_OA_W, FCML_OP_IMM_EOSA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// REX.W + 25 id AND RAX, imm32 C Valid N.E. RAX AND imm32 signextended to 64-bits.
	{ NULL, FCML_AMT_GPI, 0x0008, 0x04840000, { 0x25, 0x00, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_AL, FCML_EOS_EOSA ) | FCML_OA_W, FCML_OP_ID_EX_EOSA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 80 /4 ib AND r/m8, imm8 MR Valid Valid r/m8 AND imm8.
	// REX + 80 /4 ib AND r/m8*, imm8 MR Valid N.E. r/m8 AND imm8.
	{ NULL, FCML_AMT_GPI, 0x0807, 0x00C5A000, { 0x80, 0x00, 0x00 }, { FCML_OP_MODRM_RM_8_W, FCML_OP_IB, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 81 /4 iw AND r/m16, imm16 B Valid Valid r/m16 AND imm16.
	// 81 /4 id AND r/m32, imm32 B Valid Valid r/m32 AND imm32.
	{ NULL, FCML_AMT_GPI, 0x0817, 0x03C5A000, { 0x81, 0x00, 0x00 }, { FCML_OP_MODRM_RM_W, FCML_OP_IMM_EOSA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// REX.W + 81 /4 id AND r/m64, imm32 B Valid N.E. r/m64 AND imm32 sign extended to 64-bits.
	{ NULL, FCML_AMT_GPI, 0x080F, 0x0485A000, { 0x81, 0x00, 0x00 }, { FCML_OP_MODRM_RM_W, FCML_OP_ID_EX_EOSA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 83 /4 ib AND r/m16, imm8 B Valid Valid r/m16 AND imm8 (signextended).
	// 83 /4 ib AND r/m32, imm8 B Valid Valid r/m32 AND imm8 (signextended).
	{ NULL, FCML_AMT_GPI, 0x0817, 0x03C5A000, { 0x83, 0x00, 0x00 }, { FCML_OP_MODRM_RM_W, FCML_OP_IB_EX_EOSA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// REX.W + 83 /4 ib AND r/m64, imm8 B Valid N.E. r/m64 AND imm8 (signextended).
	{ NULL, FCML_AMT_GPI, 0x080F, 0x0485A000, { 0x83, 0x00, 0x00 }, { FCML_OP_MODRM_RM_W, FCML_OP_IB_EX_EOSA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 20 /r AND r/m8, r8 A Valid Valid r/m8 AND r8.
	// REX + 20 /r AND r/m8*, r8* A Valid N.E. r/m64 AND r8 (signextended).
	{ NULL, FCML_AMT_GPI, 0x0807, 0x00C48000, { 0x20, 0x00, 0x00 }, { FCML_OP_MODRM_RM_8_W, FCML_OP_MODRM_R_8, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 21 /r AND r/m16, r16 A Valid Valid r/m16 AND r16.
	// 21 /r AND r/m32, r32 A Valid Valid r/m32 AND r32.
	// REX.W + 21 /r AND r/m64, r64 A Valid N.E. r/m64 AND r32.
	{ NULL, FCML_AMT_GPI, 0x0807, 0x00C48000, { 0x21, 0x00, 0x00 }, { FCML_OP_MODRM_RM_W, FCML_OP_MODRM_R, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 22 /r AND r8, r/m8 A Valid Valid r8 AND r/m8.
	// REX + 22 /r AND r8*, r/m8* A Valid N.E. r/m64 AND r8 (signextended).
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00C48000, { 0x22, 0x00, 0x00 }, { FCML_OP_MODRM_R_8_W, FCML_OP_MODRM_RM_8, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 23 /r AND r16, r/m16 A Valid Valid r16 AND r/m16.
	// 23 /r AND r32, r/m32 A Valid Valid r32 AND r/m32.
	// REX.W + 23 /r AND r64, r/m64 A Valid N.E. r64 AND r/m64.
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00C48000, { 0x23, 0x00, 0x00 }, { FCML_OP_MODRM_R_W, FCML_OP_MODRM_RM, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_ANDPD[] = {
	// 66 0F 54 /r ANDPD xmm1, xmm2/m128 A Valid Valid Bitwise logical AND of xmm2/m128 and xmm1.
	{ NULL, FCML_AMT_SSE2_SIMD, 0x1000, 0x00D88000, { 0x0F, 0x54, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.66.0F 54 /r VANDPD xmm1,xmm2,xmm3/m128
	// VEX.NDS.256.66.0F 54 /r VANDPD ymm1,ymm2,ymm3/m256
	{ "vandpd", FCML_AMT_AVX_SIMD, 0x1080, 0x00D88000, { 0x0F, 0x54, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_ANDPS[] = {
	// 0F 54 /r ANDPS xmm1, xmm2/m128 A Valid Valid Bitwise logical AND of xmm2/m128 and xmm1.
	{ NULL, FCML_AMT_SSE_SIMD, 0x0000, 0x00D88000, { 0x0F, 0x54, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.0F 54 /r VANDPS xmm1,xmm2, xmm3/m128
	// VEX.NDS.256.0F 54 /r VANDPS ymm1, ymm2, ymm3/m256
	{ "vandps", FCML_AMT_AVX_SIMD, 0x0080, 0x00D88000, { 0x0F, 0x54, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_ANDNPD[] = {
	// 66 0F 55 /r ANDNPD xmm1, xmm2/m128 A Valid Valid Bitwise logical AND NOT of xmm2/m128 and xmm1.
	{ NULL, FCML_AMT_SSE2_SIMD, 0x1000, 0x00D88000, { 0x0F, 0x55, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.66.0F 55 /r VANDNPD xmm1,xmm2,xmm3/m128
	// VEX.NDS.256.66.0F 55 /r VANDNPD ymm1,ymm2,ymm3/m256
	{ "vandnpd", FCML_AMT_AVX_SIMD, 0x1080, 0x00D88000, { 0x0F, 0x55, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_ANDNPS[] = {
	// 0F 55 /r ANDNPS xmm1, xmm2/m128 A Valid Valid Bitwise logical AND NOT of xmm2/m128 and xmm1.
	{ NULL, FCML_AMT_SSE_SIMD, 0x0000, 0x00D88000, { 0x0F, 0x55, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.0F 55 /r VANDNPS xmm1,xmm2,xmm3/m128
	// VEX.NDS.256.0F 55 /r VANDNPS ymm1,ymm2,ymm3/m256
	{ "vandnps", FCML_AMT_AVX_SIMD, 0x0080, 0x00D88000, { 0x0F, 0x55, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_ARPL[] = {
	// 63 /r ARPL r/m16, r16 A N. E. Valid Adjust RPL of r/m16 to not less than RPL of r16.
	{ NULL, FCML_AMT_SYSTEM, 0x0000, 0x00448000, { 0x63, 0x00, 0x00 }, { FCML_OP_MODRM_RM_16, FCML_OP_MODRM_R_16, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_BLENDPD[] = {
	// 66 0F 3A 0D /r ib BLENDPD xmm1, xmm2/m128, imm8 A Valid Valid Select packed DP-FP values from xmm1 and xmm2/m128 from mask specified in imm8 and store the values into xmm1.
	{ NULL, FCML_AMT_SSE41_SIMD, 0x1000, 0x00EC8000, { 0x0F, 0x3A, 0x0D }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.66.0F3A 0D /r ib VBLENDPD xmm1,xmm2,xmm3/m128,imm8
	// VEX.NDS.256.66.0F3A 0D /r ib VBLENDPD ymm1,ymm2,ymm3/m256,imm8
	{ "vblendpd", FCML_AMT_AVX_SIMD, 0x1080, 0x00EC8000, { 0x0F, 0x3A, 0x0D }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L, FCML_OP_IB, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_BLENDPS[] = {
	// 66 0F 3A 0C /r ib BLENDPS xmm1, xmm2/m128, imm8 A Valid Valid Select packed single precision floating-point values from xmm1 and xmm2/m128 from mask specified in imm8 and store the values into xmm1.
	{ NULL, FCML_AMT_SSE41_SIMD, 0x1000, 0x00EC8000, { 0x0F, 0x3A, 0x0C }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.66.0F3A 0C /r ib VBLENDPS xmm1,xmm2,xmm3/m128,imm8
	// VEX.NDS.256.66.0F3A 0C /r ib VBLENDPS ymm1,ymm2,ymm3/m256,imm8
	{ "vblendps", FCML_AMT_AVX_SIMD, 0x1080, 0x00EC8000, { 0x0F, 0x3A, 0x0C }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L, FCML_OP_IB, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_BLENDVPD[] = {
	// 66 0F 38 15 /r BLENDVPD xmm1, xmm2/m128 , <XMM0> A Valid Valid Select packed DP FP values from xmm1 and xmm2 from mask specified in XMM0 and store the values in xmm1.
	{ NULL, FCML_AMT_SSE41_SIMD, 0x1000, 0x00EC8000, { 0x0F, 0x38, 0x15 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_OP_EXPLICIT_REG( FCML_REG_SIMD, FCML_REG_XMM0, FCML_EOS_OWORD ), FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.66.0F3A 4B /r /is4 VBLENDVPD xmm1, xmm2, xmm3/m128, xmm4
	// VEX.NDS.256.66.0F3A 4B /r /is4 VBLENDVPD ymm1, ymm2, ymm3/m256, ymm4
	{ "vblendvpd", FCML_AMT_AVX_SIMD, 0x1080, 0x00EC8000, { 0x0F, 0x3A, 0x4B }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L, FCML_OP_OPERAND_IS4, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_BLENDVPS[] = {
	// 66 0F 38 14 /r BLENDVPS xmm1, xmm2/m128, <XMM0> A Valid Valid Select packed single precision floating-point values from xmm1 and xmm2/m128 from mask specified in XMM0 and store the values into xmm1.
	{ NULL, FCML_AMT_SSE41_SIMD, 0x1000, 0x00EC8000, { 0x0F, 0x38, 0x14 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_OP_EXPLICIT_REG( FCML_REG_SIMD, FCML_REG_XMM0, FCML_EOS_OWORD ), FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.66.0F3A 4A /r /is4 VBLENDVPS xmm1, xmm2, xmm3/m128, xmm4
	// VEX.NDS.256.66.0F3A 4A /r /is4 VBLENDVPS ymm1, ymm2, ymm3/m256, ymm4
	{ "vblendvps", FCML_AMT_AVX_SIMD, 0x1080, 0x00EC8000, { 0x0F, 0x3A, 0x4A }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L, FCML_OP_OPERAND_IS4, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VMPTRLD[] = {
    // 0F C7 /6 VMPTRLD m64 Loads the current VMCS pointer from memory.
    { NULL, FCML_AMT_VMX, 0x0000, 0x8099B000, { 0x0F, 0xC7, 0x00 }, { FCML_OP_MODRM_M_64_W, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VMPTRST[] = {
    // 0F C7 /7 VMPTRST m64 Stores the current VMCS pointer into memory.
    { NULL, FCML_AMT_VMX, 0x0000, 0x8099B800, { 0x0F, 0xC7, 0x00 }, { FCML_OP_MODRM_M_64_W, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VMCLEAR[] = {
    // 66 0F C7 /6 VMCLEAR m64 Copy VMCS data to VMCS region in memory.
    { NULL, FCML_AMT_VMX, 0x1000, 0x8099B800, { 0x0F, 0xC7, 0x00 }, { FCML_OP_MODRM_M_64_W, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VMREAD[] = {
    // 0F 78 VMREAD r/m64, r64 Reads a specified VMCS field (in 64-bit mode).
    // 0F 78 VMREAD r/m32, r32 Reads a specified VMCS field (outside 64-bit mode).
    { NULL, FCML_AMT_VMX, 0x0000, 0x00588000, { 0x0F, 0x78, 0x00 }, { FCML_OP_MODRM_RM_32_W, FCML_OP_MODRM_R_32, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
    { NULL, FCML_AMT_VMX, 0x0000, 0x00988000, { 0x0F, 0x78, 0x00 }, { FCML_OP_MODRM_RM_64_W, FCML_OP_MODRM_R_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VMWRITE[] = {
    // 0F 79 VMWRITE r64, r/m64 Writes a specified VMCS field (in 64-bit mode)
    // 0F 79 VMWRITE r32, r/m32 Writes a specified VMCS field (outside 64-bit mode)
    { NULL, FCML_AMT_VMX, 0x0000, 0x00588000, { 0x0F, 0x79, 0x00 }, { FCML_OP_MODRM_RM_32_W, FCML_OP_MODRM_R_32, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
    { NULL, FCML_AMT_VMX, 0x0000, 0x00988000, { 0x0F, 0x79, 0x00 }, { FCML_OP_MODRM_RM_64_W, FCML_OP_MODRM_R_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VMLAUNCH[] = {
    // 0F 01 C2 VMLAUNCH Launch virtual machine managed by current VMCS.
    { NULL, FCML_AMT_VMX, 0x0000, 0x00AC0000, { 0x0F, 0x01, 0xC2 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VMRESUME[] = {
    // 0F 01 C3 VMRESUME Resume virtual machine managed by current VMCS.
    { NULL, FCML_AMT_VMX, 0x0000, 0x00AC0000, { 0x0F, 0x01, 0xC3 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VMXOFF[] = {
    // 0F 01 C4 VMXOFF Leaves VMX operation.
    { NULL, FCML_AMT_VMX, 0x0000, 0x00AC0000, { 0x0F, 0x01, 0xC4 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VMXON[] = {
    // F3 0F C7 /6 VMXON m64 Enter VMX root operation.
    { NULL, FCML_AMT_VMX, 0x4000, 0x8099B000, { 0x0F, 0xC7, 0x00 }, { FCML_OP_MODRM_M_64_W, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VMCALL[] = {
    // 0F 01 C1 VMCALL Call to VM monitor by causing VM exit.
    { NULL, FCML_AMT_VMX, 0x0000, 0x00AC0000, { 0x0F, 0x01, 0xC1 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VMFUNC[] = {
    // 0F 01 D4 VMFUNC Invoke VM function specified in EAX.
    { NULL, FCML_AMT_VMX, 0x0000, 0x00AC0000, { 0x0F, 0x01, 0xD4 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VBROADCASTSS[] = {
	// VEX.128.66.0F38 18 /r VBROADCASTSS xmm1, m32
	// VEX.256.66.0F38 18 /r VBROADCASTSS ymm1, m32
	{ NULL, FCML_AMT_AVX_SIMD, 0x1180, 0x80EC8000, { 0x0F, 0x38, 0x18 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_MODRM_M_32, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.256.66.0F38 19 /r VBROADCASTSD ymm1, m64
	{ "vbroadcastsd", FCML_AMT_AVX_SIMD, 0x11A0, 0x80EC8000, { 0x0F, 0x38, 0x19 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_MODRM_M_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.256.66.0F38.W0 1A /r VBROADCASTF128 ymm1,m128
	{ "vbroadcastf128", FCML_AMT_AVX_SIMD, 0x11B0, 0x80EC8000, { 0x0F, 0x38, 0x1A }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_MODRM_M_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.256.66.0F38.W0 5A /r VBROADCASTI128 ymm1,m128
	{ "vbroadcasti128", FCML_AMT_AVX2_SIMD, 0x11B0, 0x80EC8000, { 0x0F, 0x38, 0x5A }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_MODRM_M_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.128.66.0F38.W0 18 /r VBROADCASTSS xmm1,xmm2
	// VEX.256.66.0F38.W0 18 /r VBROADCASTSS ymm1,xmm2
	{ "vbroadcastss", FCML_AMT_AVX2_SIMD, 0x1180, 0x00EE8000, { 0x0F, 0x38, 0x18 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_RM( FCML_REG_SIMD, FCML_EOS_OWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.256.66.0F38.W0 19 /r VBROADCASTSD ymm1,xmm2
	{ "vbroadcastsd", FCML_AMT_AVX2_SIMD, 0x11A0, 0x00EE8000, { 0x0F, 0x38, 0x19 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_RM( FCML_REG_SIMD, FCML_EOS_OWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPBROADCAST[] = {
	// VEX.128.66.0F38.W0 78 /r VPBROADCASTB xmm1,xmm2/m8
	// VEX.256.66.0F38.W0 78 /r VPBROADCASTB ymm1,xmm2/m8
	{ "vpbroadcastb", FCML_AMT_AVX2_SIMD, 0x1190, 0x00EC8000, { 0x0F, 0x38, 0x78 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_MODRM_RM_SIMD_L_8, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.128.66.0F38.W0 79 /r VPBROADCASTW xmm1,xmm2/m16
	// VEX.256.66.0F38.W0 79 /r VPBROADCASTW ymm1,xmm2/m16
	{ "vpbroadcastw", FCML_AMT_AVX2_SIMD, 0x1190, 0x00EC8000, { 0x0F, 0x38, 0x79 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_MODRM_RM_SIMD_L_16, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.128.66.0F38.W0 58 /r VPBROADCASTD xmm1,xmm2/m32
	// VEX.256.66.0F38.W0 58 /r VPBROADCASTD ymm1,xmm2/m32
	{ "vpbroadcastd", FCML_AMT_AVX2_SIMD, 0x1190, 0x00EC8000, { 0x0F, 0x38, 0x58 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_MODRM_RM_SIMD_L_32, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.128.66.0F38.W0 59 /r VPBROADCASTQ xmm1,xmm2/m64
	// VEX.256.66.0F38.W0 59 /r VPBROADCASTQ ymm1,xmm2/m64
	{ "vpbroadcastq", FCML_AMT_AVX2_SIMD, 0x1190, 0x00EC8000, { 0x0F, 0x38, 0x59 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_MODRM_RM_SIMD_L_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_BOUND[] = {
	// 62 /r BOUND r16, m16&16 A Invalid Valid Check if r16 (array index) is within bounds specified by m16&16.
	// 62 /r BOUND r32, m32&32 A Invalid Valid Check if r32 (array index) is within bounds specified by m16&16.
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00448000, { 0x62 }, { FCML_OP_MODRM_R, FCML_OP_MODRM_MM_OSA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_BSF[] = {
	// 0F BC /r BSF r16, r/m16 A Valid Valid Bit scan forward on r/m16.
	// 0F BC /r BSF r32, r/m32 A Valid Valid Bit scan forward on r/m32.
	// REX.W + 0F BC BSF r64, r/m64 A Valid N.E. Bit scan forward on r/m64.
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00D88000, { 0x0F, 0xBC, 0x00 }, { FCML_OP_MODRM_R_W, FCML_OP_MODRM_RM, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_BSR[] = {
	// 0F BD /r BSR r16, r/m16 A Valid Valid Bit scan reverse on r/m16.
	// 0F BD /r BSR r32, r/m32 A Valid Valid Bit scan reverse on r/m32.
	// REX.W + 0F BD BSR r64, r/m64 A Valid N.E. Bit scan reverse on r/m64.
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00D88000, { 0x0F, 0xBC, 0x00 }, { FCML_OP_MODRM_R_W, FCML_OP_MODRM_RM, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_BSWAP[] = {
	// 0F C8+rd BSWAP r32 A Valid* Valid Reverses the byte order of a 32-bit register.
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00D80001, { 0x0F, 0xC8, 0x00 }, { FCML_OP_OPCODE_REG( FCML_REG_GPR, FCML_EOS_DWORD ), FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// REX.W + 0F C8+rd BSWAP r64 A Valid N.E. Reverses the byte order of a 64-bit register.
	{ NULL, FCML_AMT_GPI, 0x0008, 0x00980001, { 0x0F, 0xC8, 0x00 }, { FCML_OP_OPCODE_REG( FCML_REG_GPR, FCML_EOS_QWORD ), FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_BT[] = {
	// 0F A3 BT r/m16, r16 A Valid Valid Store selected bit in CF flag.
	// 0F A3 BT r/m32, r32 A Valid Valid Store selected bit in CF flag.
	// REX.W + 0F A3 BT r/m64, r64 A Valid N.E. Store selected bit in CF flag.
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00D88000, { 0x0F, 0xA3, 0x00 }, { FCML_OP_MODRM_RM_W, FCML_OP_MODRM_R, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 0F BA /4 ib BT r/m16, imm8 B Valid Valid Store selected bit in CF flag.
	// 0F BA /4 ib BT r/m32, imm8 B Valid Valid Store selected bit in CF flag.
	// REX.W + 0F BA /4 ib BT r/m64, imm8 B Valid N.E. Store selected bit in CF flag.
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00D9A000, { 0x0F, 0xBA, 0x00 }, { FCML_OP_MODRM_RM_W, FCML_OP_IB, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_BTC[] = {
	// 0F BB BTC r/m16, r16 A Valid Valid Store selected bit in CF flag and complement.
	// 0F BB BTC r/m32, r32 A Valid Valid Store selected bit in CF flag and complement.
	// REX.W + 0F BB BTC r/m64, r64 A Valid N.E. Store selected bit in CF flag and complement.
	{ NULL, FCML_AMT_GPI, 0x0807, 0x00D88000, { 0x0F, 0xBB, 0x00 }, { FCML_OP_MODRM_RM_W, FCML_OP_MODRM_R, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 0F BA /7 ib BTC r/m16, imm8 B Valid Valid Store selected bit in CF flag and complement.
	// 0F BA /7 ib BTC r/m32, imm8 B Valid Valid Store selected bit in CF flag and complement.
	// REX.W + 0F BA /7 ib BTC r/m64, imm8 B Valid N.E. Store selected bit in CF flag and complement.
	{ NULL, FCML_AMT_GPI, 0x0807, 0x00D9B800, { 0x0F, 0xBA, 0x00 }, { FCML_OP_MODRM_RM_W, FCML_OP_IB, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_BTR[] = {
	// 0F B3 BTR r/m16, r16 A Valid Valid Store selected bit in CF flag and clear.
	// 0F B3 BTR r/m32, r32 A Valid Valid Store selected bit in CF flag and clear.
	// REX.W + 0F B3 BTR r/m64, r64 A Valid N.E. Store selected bit in CF flag and clear.
	{ NULL, FCML_AMT_GPI, 0x0807, 0x00D88000, { 0x0F, 0xB3, 0x00 }, { FCML_OP_MODRM_RM_W, FCML_OP_MODRM_R, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 0F BA /6 ib BTR r/m16, imm8 B Valid Valid Store selected bit in CF flag and clear.
	// 0F BA /6 ib BTR r/m32, imm8 B Valid Valid Store selected bit in CF flag and clear.
	// REX.W + 0F BA /6 ib BTR r/m64, imm8 B Valid N.E. Store selected bit in CF flag and clear.
	{ NULL, FCML_AMT_GPI, 0x0807, 0x00D9B000, { 0x0F, 0xBA, 0x00 }, { FCML_OP_MODRM_RM_W, FCML_OP_IB, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_BTS[] = {
	// 0F AB BTS r/m16, r16 A Valid Valid Store selected bit in CF flag and set.
	// 0F AB BTS r/m32, r32 A Valid Valid Store selected bit in CF flag and set.
	// REX.W + 0F AB BTS r/m64, r64 A Valid N.E. Store selected bit in CF flag and set.
	{ NULL, FCML_AMT_GPI, 0x0807, 0x00D88000, { 0x0F, 0xAB, 0x00 }, { FCML_OP_MODRM_RM_W, FCML_OP_MODRM_R, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 0F BA /5 ib BTS r/m16, imm8 B Valid Valid Store selected bit in CF flag and set.
	// 0F BA /5 ib BTS r/m32, imm8 B Valid Valid Store selected bit in CF flag and set.
	// REX.W + 0F BA /5 ib BTS r/m64, imm8 B Valid N.E. Store selected bit in CF flag and set.
	{ NULL, FCML_AMT_GPI, 0x0807, 0x00D9A800, { 0x0F, 0xBA, 0x00 }, { FCML_OP_MODRM_RM_W, FCML_OP_IB, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_CALL[] = {
	// E8 cw CALL rel16 B N.S. Valid Call near, relative, displacement relative to next instruction.
	// E8 cd CALL rel32 B Valid Valid Call near, relative, displacement relative to next instruction.
	// 32-bit displacement sign extended to 64-bits in 64-bit mode.
	{ NULL, FCML_AMT_GPI, 0x0000, 0x40C40000, { 0xE8, 0x00, 0x00 }, { FCML_OP_IMMEDIATE_DIS_RELATIVE_EOSA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// FF /2 CALL r/m16 B N.E. Valid Call near, absolute indirect, address given in r/m16.
	// FF /2 CALL r/m32 B N.E. Valid Call near, absolute indirect, address given in r/m32.
	// FF /2 CALL r/m64 B Valid N.E. Call near, absolute indirect, address given in r/m64.
	{ NULL, FCML_AMT_GPI, 0x0000, 0x40C59000, { 0xFF, 0x00, 0x00 }, { FCML_OP_MODRM_RM, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 9A cd CALL ptr16:16 A Invalid Valid Call far, absolute, address given in operand.
	// 9A cp CALL ptr16:32 A Invalid Valid Call far, absolute, address given in operand.
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00440000, { 0x9A, 0x00, 0x00 }, { FCML_OP_FAR_POINTER, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// FF /3 CALL m16:16 B Valid Valid Call far, absolute indirect address given in m16:16.
	// FF /3 CALL m16:32 B Valid Valid In 64-bit mode.
	// REX.W + FF /3 CALL m16:64 B Valid N.E. In 64-bit mode.
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00C59800, { 0xFF, 0x00, 0x00 }, { FCML_OP_FAR_POINTER_INDIRECT, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_CBW[] = {
	// 98 CBW A Valid Valid AX  sign-extend of AL.
	{ "cbw", FCML_AMT_GPI, 0x0000, 0x01C40000, { 0x98, 0x00, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 98 CWDE A Valid Valid EAX  sign-extend of AX.
	{ "cwde", FCML_AMT_GPI, 0x0000, 0x02C40000, { 0x98, 0x00, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// REX.W + 98 CDQE A Valid N.E. RAX  sign-extend of EAX.
	{ "cdqe", FCML_AMT_GPI, 0x0000, 0x04C40000, { 0x98, 0x00, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_CLC[] = {
	// F8 CLC A Valid Valid Clear CF flag.
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00C40000, { 0xF8, 0x00, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_CLD[] = {
	// F8 CLC A Valid Valid Clear CF flag.
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00C40000, { 0xFC, 0x00, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_CLFLUSH[] = {
	// 0F AE /7 CLFLUSH m8 A Valid Valid Flushes cache line containing m8.
	{ NULL, FCML_AMT_SSE2, 0x0000, 0x00D9B800, { 0x0F, 0xAE, 0x00 }, { FCML_OP_MODRM_M_8_W, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_CLI[] = {
	// FA CLI A Valid Valid Clear interrupt flag interrupts disabled when interrupt flag cleared.
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00C40000, { 0xFA, 0x00, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_CLGI[] = {
	// CLGI 0F 01 DD Clears the global interrupt flag (GIF).
	{ NULL, FCML_AMT_SVM, 0x0000, 0x00EC0000, { 0x0F, 0x01, 0xDD }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_CLTS[] = {
	// 0F 06 CLTS A Valid Valid Clears TS flag in CR0.
	{ NULL, FCML_AMT_SYSTEM, 0x0000, 0x00D80000, { 0x0F, 0x06, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_CMC[] = {
	// F5 CMC A Valid Valid Complement CF flag. Op/En
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00C40000, { 0xF5, 0x00, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_CMOV[] = {
	// 0F 4X /r CMOVA r16, r/m16 A Valid Valid Move if above (CF=0 and ZF=0).
	// 0F 4X /r CMOVA r32, r/m32 A Valid Valid Move if above (CF=0 and ZF=0).
	// REX.W + 0F 4X /r CMOVA r64, r/m64 A Valid N.E. Move if above (CF=0 and ZF=0).
	{ NULL, FCML_AMT_EDX | FCML_AMT_GPI, 0x0000, 0x00D88040, { 0x0F, 0x40, 0x00 }, { FCML_OP_MODRM_R_W, FCML_OP_MODRM_RM, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_JCXZ[] = {
	// E3 cb JCXZ rel8 A N.E. Valid Jump short if CX register is 0.
	{ "jcxz", FCML_AMT_GPI, 0x0000, 0x08440000, { 0xE3, 0x00, 0x00 }, { FCML_OP_IMMEDIATE_DIS_RELATIVE_R_8, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// E3 cb JECXZ rel8 A Valid Valid Jump short if ECX register is 0.
	{ "jecxz", FCML_AMT_GPI, 0x0000, 0x50C40000, { 0xE3, 0x00, 0x00 }, { FCML_OP_IMMEDIATE_DIS_RELATIVE_R_8, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// E3 cb JRCXZ rel8 A Valid N.E. Jump short if RCX register is 0.
	{ "jrcxz", FCML_AMT_GPI, 0x0000, 0x60840000, { 0xE3, 0x00, 0x00 }, { FCML_OP_IMMEDIATE_DIS_RELATIVE_R_8, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_Jcc[] = {
	// JA rel8 A Valid Valid Jump short if ...
	{ NULL, FCML_AMT_GPI, 0x0000, 0x40C40040, { 0x70, 0x00, 0x00 }, { FCML_OP_IMMEDIATE_DIS_RELATIVE_R_8, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// JA rel32 A Valid Valid Jump near if ...
	// JAE rel16 A N.S. Valid Jump near if ...
	{ NULL, FCML_AMT_GPI, 0x0000, 0x40D80040, { 0x0F, 0x80, 0x00 }, { FCML_OP_IMMEDIATE_DIS_RELATIVE_EOSA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_JMP[] = {
	// EB cb JMP rel8 A Valid Valid Jump short, RIP = RIP + 8-bit displacement sign extended to 64-bits
	{ NULL, FCML_AMT_GPI, 0x0000, 0x40C40000, { 0xEB, 0x00, 0x00 }, { FCML_OP_IMMEDIATE_DIS_RELATIVE_R_8, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// E9 cw JMP rel16 A N.S. Valid Jump near, relative, displacement relative to next instruction. Not supported in 64-bit mode.
	// E9 cd JMP rel32 A Valid Valid Jump near, relative, RIP = RIP + 32-bit displacement sign extended to 64-bits
	{ NULL, FCML_AMT_GPI, 0x0000, 0x40C40000, { 0xE9, 0x00, 0x00 }, { FCML_OP_IMMEDIATE_DIS_RELATIVE_EOSA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// FF /4 JMP r/m16 B N.S. Valid Jump near, absolute indirect, address = zero-extended r/m16. Not supported in 64- bit mode.
	// FF /4 JMP r/m32 B N.S. Valid Jump near, absolute indirect, address given in r/m32. Not supported in 64-bit mode.
	// FF /4 JMP r/m64 B Valid N.E. Jump near, absolute indirect, RIP = 64-Bit offset from register or memory
	{ NULL, FCML_AMT_GPI, 0x0000, 0x40C5A000, { 0xFF, 0x00, 0x00 }, { FCML_OP_MODRM_RM, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// EA cd JMP ptr16:16 A Inv. Valid Jump far, absolute, address given in operand
	// EA cp JMP ptr16:32 A Inv. Valid Jump far, absolute, address given in operand
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00440000, { 0xEA, 0x00, 0x00 }, { FCML_OP_FAR_POINTER, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// FF /5 JMP m16:16 A Valid Valid Jump far, absolute indirect, address given in m16:16
	// FF /5 JMP m16:32 A Valid Valid Jump far, absolute indirect, address given in m16:32.
	// REX.W + FF /5 JMP m16:64 A Valid N.E. Jump far, absolute indirect, address given in m16:64.
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00C5A800, { 0xFF, 0x00, 0x00 }, { FCML_OP_FAR_POINTER_INDIRECT, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_CMP[] = {
	// 3C ib CMP AL, imm8 D Valid Valid Compare imm8 with AL.
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00C40000, { 0x3C, 0x00, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_AL, FCML_EOS_BYTE ), FCML_OP_IB, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 3D iw CMP AX, imm16 D Valid Valid Compare imm16 with AX.
	// 3D id CMP EAX, imm32 D Valid Valid Compare imm32 with EAX.
	{ NULL, FCML_AMT_GPI, 0x0010, 0x03C40000, { 0x3D, 0x00, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_AL, FCML_EOS_EOSA ) | FCML_OA_W, FCML_OP_IMM_EOSA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// REX.W + 3D id CMP RAX, imm32 D Valid N.E. Compare imm32 sign extended to 64-bits with RAX.
	{ NULL, FCML_AMT_GPI, 0x0008, 0x04840000, { 0x3D, 0x00, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_AL, FCML_EOS_EOSA ) | FCML_OA_W, FCML_OP_ID_EX_EOSA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 80 /7 ib CMP r/m8, imm8 C Valid Valid Compare imm8 with r/m8.
	// REX + 80 /7 ib CMP r/m8*, imm8 C Valid N.E. Compare imm8 with r/m8.
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00C5B800, { 0x80, 0x00, 0x00 }, { FCML_OP_MODRM_RM_8_W, FCML_OP_IB, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 81 /7 iw CMP r/m16, imm16 C Valid Valid Compare imm16 with r/m16.
	// 81 /7 id CMP r/m32, imm32 C Valid Valid Compare imm32 with r/m32.
	{ NULL, FCML_AMT_GPI, 0x0010, 0x03C5B800, { 0x81, 0x00, 0x00 }, { FCML_OP_MODRM_RM_W, FCML_OP_IMM_EOSA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// REX.W + 81 /7 id CMP r/m64, imm32 C Valid N.E. Compare imm32 sign extended to 64-bits with r/m64.
	{ NULL, FCML_AMT_GPI, 0x0008, 0x0485B800, { 0x81, 0x00, 0x00 }, { FCML_OP_MODRM_RM_W, FCML_OP_ID_EX_EOSA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 83 /7 ib CMP r/m16, imm8 C Valid Valid Compare imm8 with r/m16.
	// 83 /7 ib CMP r/m32, imm8 C Valid Valid Compare imm8 with r/m32.
	{ NULL, FCML_AMT_GPI, 0x0010, 0x03C5B800, { 0x83, 0x00, 0x00 }, { FCML_OP_MODRM_RM_W, FCML_OP_IB_EX_EOSA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// REX.W + 83 /7 ib CMP r/m64, imm8 C Valid N.E. Compare imm8 with r/m64.
	{ NULL, FCML_AMT_GPI, 0x0008, 0x0485B800, { 0x83, 0x00, 0x00 }, { FCML_OP_MODRM_RM_W, FCML_OP_IB_EX_EOSA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 38 /r CMP r/m8, r8 B Valid Valid Compare r8 with r/m8.
	// REX + 38 /r CMP r/m8*, r8* B Valid N.E. Compare r8 with r/m8.
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00C48000, { 0x38, 0x00, 0x00 }, { FCML_OP_MODRM_RM_8_W, FCML_OP_MODRM_R_8, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 39 /r CMP r/m16, r16 B Valid Valid Compare r16 with r/m16.
	// 39 /r CMP r/m32, r32 B Valid Valid Compare r32 with r/m32.
	// REX.W + 39 /r CMP r/m64,r64 B Valid N.E. Compare r64 with r/m64.
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00C48000, { 0x39, 0x00, 0x00 }, { FCML_OP_MODRM_RM_W, FCML_OP_MODRM_R, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 3A /r CMP r8, r/m8 A Valid Valid Compare r/m8 with r8.
	// REX + 3A /r CMP r8*, r/m8* A Valid N.E. Compare r/m8 with r8.
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00C48000, { 0x3A, 0x00, 0x00 }, { FCML_OP_MODRM_R_8_W, FCML_OP_MODRM_RM_8, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 3B /r CMP r16, r/m16 A Valid Valid Compare r/m16 with r16.
	// 3B /r CMP r32, r/m32 A Valid Valid Compare r/m32 with r32.
	// REX.W + 3B /r CMP r64, r/m64 A Valid N.E. Compare r/m64 with r64.
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00C48000, { 0x3B, 0x00, 0x00 }, { FCML_OP_MODRM_R_W, FCML_OP_MODRM_RM, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_CMPPD[] = {
	// 66 0F C2 /r ib CMPPD xmm1, xmm2/m128, imm8 A Valid Valid Compare packed doubleprecision floating-point values in xmm2/m128 and xmm1 using imm8 as comparison predicate.
	{ NULL, FCML_AMT_SSE2_SIMD, 0x1001, 0x00D88000, { 0x0F, 0xC2, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.66.0F C2 /r ib VCMPPD xmm1, xmm2, xmm3/m128, imm8
	// VEX.NDS.256.66.0F C2 /r ib VCMPPD ymm1, ymm2, ymm3/m256, imm8
	{ "vcmppd", FCML_AMT_AVX_SIMD, 0x1080, 0x00D88000, { 0x0F, 0xC2, 0x0C }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L, FCML_OP_IB, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_CMPPS[] = {
	// 0F C2 /r ib CMPPS xmm1, xmm2/m128, imm8 A Valid Valid Compare packed singleprecision floating-point values in xmm2/mem and xmm1 using imm8 as comparison predicate.
	{ NULL, FCML_AMT_SSE_SIMD, 0x0000, 0x00D88000, { 0x0F, 0xC2, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.0F C2 /r ib VCMPPS xmm1, xmm2, xmm3/m128, imm8
	// VEX.NDS.256.0F C2 /r ib VCMPPS ymm1, ymm2, ymm3/m256, imm8
	{ "vcmpps", FCML_AMT_AVX_SIMD, 0x0080, 0x00D88000, { 0x0F, 0xC2, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L, FCML_OP_IB, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_CMPS[] = {
	// A6 CMPS m8, m8 A Valid Valid For legacy mode, compare byte at address DS:(E)SI with byte at address ES:(E)DI; For 64-bit mode compare byte at address (R|E)SI to byte at address (R|E)DI. The status flags are set accordingly.
	{ "cmps;cmpsb[ts]", FCML_AMT_GPI, 0x0002, 0x00C40000, { 0xA6, 0x00, 0x00 },
			{ FCML_OP_EXPLICIT_GPS_REG_ADDRESSING( FCML_REG_SI, FCML_EOS_BYTE, FCML_SEG_ENCODE_REGISTER( FCML_REG_DS, FCML_SEG_ALLOW_OVERRIDE ) ),
			FCML_OP_EXPLICIT_GPS_REG_ADDRESSING( FCML_REG_DI, FCML_EOS_BYTE, FCML_SEG_ENCODE_REGISTER( FCML_REG_ES, FCML_SEG_DENY_OVERRIDE ) ),
			FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// A7 CMPS m16, m16 A Valid Valid For legacy mode, compare word at address DS:(E)SI with word at address ES:(E)DI; For 64-bit mode compare word at address (R|E)SI with word at address (R|E)DI. The status flags are set accordingly.
	// A7 CMPS m32, m32 A Valid Valid For legacy mode, compare dword at address DS:(E)SI at dword at address ES:(E)DI; For 64-bit mode compare dword at address (R|E)SI at dword at address (R|E)DI. The status flags are set accordingly.
	// REX.W + A7 CMPS m64, m64 A Valid N.E. Compares quadword at address (R|E)SI with quadword at address (R|E)DI and sets the status flags accordingly.
	{ "cmps;cmpsw[ts,ow,a*];cmpsd[ts,od,a*];cmpsq[ts,oq,a*]", FCML_AMT_GPI, 0x0002, 0x00C40000, { 0xA7, 0x00, 0x00 },
			{ FCML_OP_EXPLICIT_GPS_REG_ADDRESSING( FCML_REG_SI, FCML_EOS_EOSA, FCML_SEG_ENCODE_REGISTER( FCML_REG_DS, FCML_SEG_ALLOW_OVERRIDE ) ),
			FCML_OP_EXPLICIT_GPS_REG_ADDRESSING( FCML_REG_DI, FCML_EOS_EOSA, FCML_SEG_ENCODE_REGISTER( FCML_REG_ES, FCML_SEG_DENY_OVERRIDE ) ),
			FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_CMPSD[] = {
	// F2 0F C2 /r ib CMPSD xmm1, xmm2/m64, imm8 A Valid Valid Compare low double precision floating-point value in xmm2/m64 and xmm1 using imm8 as comparison predicate.
    // Compiler should treat reserved Imm8 values as illegal syntax, it's why appropriate mask is defined.
	{ "cmpsd", FCML_AMT_SSE2_SIMD, 0x2000, 0x80D88000, { 0x0F, 0xC2, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_M_XMM_64, FCML_OP_PSEUDO_OP( 0x07 ), FCML_NA, FCML_NA }, FCML_AM_NONE },
	{ "cmpsd;cmpeqsd[p00];cmpltsd[p01];cmplesd[p02];cmpunordsd[p03];cmpneqsd[p04];cmpnltsd[p05];cmpnlesd[p06];cmpordsd[p07]", FCML_AMT_SSE2_SIMD, 0x2000, 0x00DA8000, { 0x0F, 0xC2, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_RM( FCML_REG_SIMD, FCML_EOS_OWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_OP_PSEUDO_OP( 0x07 ), FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.F2.0F C2 /r ib VCMPSD xmm1, xmm2, xmm3/m64, imm8
	{ "vcmpsd", FCML_AMT_AVX_SIMD, 0x20C0, 0x80D88000, { 0x0F, 0xC2, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_M_XMM_64, FCML_OP_PSEUDO_OP( 0x0F ), FCML_NA }, FCML_AM_NONE },
	{ "cmpsd;vcmpeqsd[p00];vcmpltsd[p01];vcmplesd[p02];vcmpunordsd[p03];vcmpneqsd[p04];vcmpnltsd[p05];vcmpnlesd[p06];vcmpordsd[p07];vcmpeq_uqsd[p08];vcmpngesd[p09];vcmpngtsd[p0a];vcmpfalsesd[p0b];vcmpneq_oqsd[p0c];vcmpgesd[p0d];vcmpgtsd[p0e];vcmptruesd[p0f];vcmpeq_ossd[p10];vcmplt_oqsd[p11];vcmple_oqsd[p12];vcmpunord_ssd[p13];vcmpneq_ussd[p14];vcmpnlt_uqsd[p15];vcmpnle_uqsd[p16];vcmpord_ssd[p17];vcmpeq_ussd[p18];vcmpnge_uqsd[p19];vcmpngt_uqsd[p1a];vcmpfalse_ossd[p1b];vcmpneq_ossd[p1c];vcmpge_oqsd[p1d];vcmpgt_oqsd[p1e];vcmptrue_ussd[p1f]", FCML_AMT_AVX_SIMD, 0x20C0, 0x00DA8000, { 0x0F, 0xC2, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_OWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_OP_PSEUDO_OP( 0x1F ), FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_CMPSS[] = {
    // F3 0F C2 /r ib CMPSS xmm1, xmm2/m32, imm8 A Valid Valid Compare low singleprecision floating-point value in xmm2/m32 and xmm1 using imm8 as comparison predicate.
    { "cmpss", FCML_AMT_SSE_SIMD, 0x4000, 0x80D88000, { 0x0F, 0xC2, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_M_XMM_32, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_NONE },
    { "cmpss;cmpeqss[p00];cmpltss[p01];cmpless[p02];cmpunordss[p03];cmpneqss[p04];cmpnltss[p05];cmpnless[p06];cmpordss[p07]", FCML_AMT_SSE_SIMD, 0x4000, 0x00DA8000, { 0x0F, 0xC2, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_RM( FCML_REG_SIMD, FCML_EOS_OWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_OP_PSEUDO_OP( 0x07 ), FCML_NA, FCML_NA }, FCML_AM_NONE },
    // VEX.NDS.128.F3.0F C2 /r ib VCMPSS xmm1, xmm2, xmm3/m32, imm8
    { "vcmpss", FCML_AMT_AVX_SIMD, 0x40C0, 0x80D88000, { 0x0F, 0xC2, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_M_XMM_32, FCML_OP_IB, FCML_NA }, FCML_AM_NONE },
    { "vcmpss;vcmpeqss[p00];vcmpltss[p01];vcmpless[p02];vcmpunordss[p03];vcmpneqss[p04];vcmpnltss[p05];vcmpnless[p06];vcmpordss[p07];vcmpeq_uqss[p08];vcmpngess[p09];vcmpngtss[p0a];vcmpfalsess[p0b];vcmpneq_oqss[p0c];vcmpgess[p0d];vcmpgtss[p0e];vcmptruess[p0f];vcmpeq_osss[p10];vcmplt_oqss[p11];vcmple_oqss[p12];vcmpunord_sss[p13];vcmpneq_usss[p14];vcmpnlt_uqss[p15];vcmpnle_uqss[p16];vcmpord_sss[p17];vcmpeq_usss[p18];vcmpnge_uqss[p19];vcmpngt_uqss[p1a];vcmpfalse_osss[p1b];vcmpneq_osss[p1c];vcmpge_oqss[p1d];vcmpgt_oqss[p1e];vcmptrue_usss[p1f]", FCML_AMT_AVX_SIMD, 0x40C0, 0x00DA8000, { 0x0F, 0xC2, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_OWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_OP_PSEUDO_OP( 0x1F ), FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_CMPXCHG[] = {
	// 0F B0/r CMPXCHG r/m8, r8 A Valid Valid* Compare AL with r/m8. If equal, ZF is set and r8 is loaded into r/m8. Else, clear ZF and load r/m8 into AL.
	// REX + 0F B0/r CMPXCHG r/m8**,r8 A Valid N.E. Compare AL with r/m8. If equal, ZF is set and r8 is loaded into r/m8. Else, clear ZF and load r/m8 into AL.
	{ NULL, FCML_AMT_GPI, 0x0807, 0x00D88000, { 0x0F, 0xB0, 0x00 }, { FCML_OP_MODRM_RM_8_W, FCML_OP_MODRM_R_8, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 0F B1/r CMPXCHG r/m16, r16 A Valid Valid* Compare AX with r/m16. If equal, ZF is set and r16 is loaded into r/m16. Else, clear ZF and load r/m16 into AX.
	// 0F B1/r CMPXCHG r/m32, r32 A Valid Valid* Compare EAX with r/m32. If equal, ZF is set and r32 is loaded into r/m32. Else, clear ZF and load r/m32 into EAX.
	// REX.W + 0F B1/r CMPXCHG r/m64, r64 A Valid N.E. Compare RAX with r/m64. If equal, ZF is set and r64 is loaded into r/m64. Else, clear ZF and load r/m64 into RAX.
	{ NULL, FCML_AMT_GPI, 0x0807, 0x00D88000, { 0x0F, 0xB1, 0x00 }, { FCML_OP_MODRM_RM_W, FCML_OP_MODRM_R, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_CMPXCHGxB[] = {
	// 0F C7 /1 m64 CMPXCHG8B m64 A Valid Valid* Compare EDX:EAX with m64. If equal, set ZF and load ECX:EBX into m64. Else, clear ZF and load m64 into EDX:EAX.
	// REX.W + 0F C7 /1 m128 CMPXCHG16B m128 A Valid N.E. Compare RDX:RAX with m128. If equal, set ZF and load RCX:RBX into m128. Else, clear ZF and load m128 into RDX:RAX.
	{ "cmpxchg8b", FCML_AMT_GPI, 0x0807, 0x03D98800, { 0x0F, 0xC7, 0x00 }, { FCML_OP_MODRM_M_64_W, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	{ "cmpxchg16b", FCML_AMT_GPI, 0x0807, 0x04998800, { 0x0F, 0xC7, 0x00 }, { FCML_OP_MODRM_M_128_W, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_COMISD[] = {
	// 66 0F 2F /r COMISD xmm1, xmm2/m64 A Valid Valid Compare low doubleprecision floating-point values in xmm1 and xmm2/mem64 and set the EFLAGS flags accordingly.
	{ NULL, FCML_AMT_SSE2_SIMD, 0x1001, 0x00D88000, { 0x0F, 0x2F, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.128.66.0F 2F /r VCOMISD xmm1, xmm2/m64
	{ "vcomisd", FCML_AMT_AVX_SIMD, 0x11C1, 0x00D88000, { 0x0F, 0x2F, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_MODRM_RM_SIMD_L_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_COMISS[] = {
	// 0F 2F /r COMISS xmm1, xmm2/m32 A Valid Valid Compare low singleprecision floating-point values in xmm1 and xmm2/mem32 and set the EFLAGS flags accordingly.
	{ NULL, FCML_AMT_SSE_SIMD, 0x0000, 0x00D88000, { 0x0F, 0x2F, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_32, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.128.0F 2F /r VCOMISS xmm1, xmm2/m32
	{ "vcomiss", FCML_AMT_AVX_SIMD, 0x01C1, 0x00D88000, { 0x0F, 0x2F, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_MODRM_RM_SIMD_L_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_CPUID[] = {
	// 0F A2 CPUID A Valid Valid Returns processor identification and feature information to the EAX, EBX, ECX, and EDX registers, as determined by input entered in EAX (in some cases, ECX as well).
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00D80000, { 0x0F, 0xA2, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_CRC32[] = {
	// F2 0F 38 F0 /r CRC32 r32, r/m8 A Valid Valid Accumulate CRC32 on r/m8.
	// F2 REX 0F 38 F0 /r CRC32 r32, r/m8* A Valid N.E. Accumulate CRC32 on r/m8.
	{ NULL, FCML_AMT_SSE42, 0x2001, 0x03EC8000, { 0x0F, 0x38, 0xF0 }, { FCML_OP_MODRM_R_32_W, FCML_OP_MODRM_RM_8, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// F2 REX.W 0F 38 F0 /r CRC32 r64, r/m8 A Valid N.E. Accumulate CRC32 on r/m8.
	{ NULL, FCML_AMT_SSE42, 0x2009, 0x04AC8000, { 0x0F, 0x38, 0xF0 }, { FCML_OP_MODRM_R_64_W, FCML_OP_MODRM_RM_8, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// F2 0F 38 F1 /r CRC32 r32, r/m16 A Valid Valid Accumulate CRC32 on r/m16.
	// F2 0F 38 F1 /r CRC32 r32, r/m32 A Valid Valid Accumulate CRC32 on r/m32.
	{ NULL, FCML_AMT_SSE42, 0x2001, 0x03EC8000, { 0x0F, 0x38, 0xF1 }, { FCML_OP_MODRM_R_32_W, FCML_OP_MODRM_RM, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// F2 REX.W 0F 38 F1 /r CRC32 r64, r/m64 A Valid N.E. Accumulate CRC32 on r/m64.
	{ NULL, FCML_AMT_SSE42, 0x2009, 0x04AC8000, { 0x0F, 0x38, 0xF1 }, { FCML_OP_MODRM_R_64_W, FCML_OP_MODRM_RM, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_CVTDQ2PD[] = {
	// F3 0F E6 CVTDQ2PD xmm1, xmm2/m64 A Valid Valid Convert two packed signed doubleword integers from xmm2/m128 to two packed double-precision floatingpoint values in xmm1.
	{ NULL, FCML_AMT_SSE2_SIMD, 0x4001, 0x00D88000, { 0x0F, 0xE6, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.128.F3.0F E6 /r VCVTDQ2PD xmm1, xmm2/m64
	{ "vcvtdq2pd", FCML_AMT_AVX_SIMD, 0x41C1, 0x00D88000, { 0x0F, 0xE6, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_MODRM_RM_SIMD_L_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.256.F3.0F E6 /r VCVTDQ2PD ymm1, xmm2/m128
	{ "vcvtdq2pd", FCML_AMT_AVX_SIMD, 0x41A1, 0x00D88000, { 0x0F, 0xE6, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_MODRM_RM_SIMD_L_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

// XMMWORD
struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_CVTDQ2PS[] = {
	// 0F 5B /r CVTDQ2PS xmm1, xmm2/m128 A Valid Valid Convert four packed signed doubleword integers from xmm2/m128 to four packed single-precision floatingpoint
	{ NULL, FCML_AMT_SSE2_SIMD, 0x0000, 0x00D88000, { 0x0F, 0x5B, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.128.0F 5B /r VCVTDQ2PS xmm1, xmm2/m128
	// VEX.256.0F 5B /r VCVTDQ2PS ymm1, ymm2/m256
	{ "vcvtdq2ps", FCML_AMT_AVX_SIMD, 0x0181, 0x00D88000, { 0x0F, 0x5B, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_MODRM_RM_SIMD_L, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

// XMMWORD
struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_CVTPD2DQ[] = {
	// F2 0F E6 CVTPD2DQ xmm1, xmm2/m128 A Valid Valid Convert two packed doubleprecision floating-point values from xmm2/m128 to two packed signed doubleword integers in xmm1.
	{ NULL, FCML_AMT_SSE2_SIMD, 0x2001, 0x00D88000, { 0x0F, 0xE6, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.128.F2.0F E6 /r VCVTPD2DQ xmm1, xmm2/m128
	// VEX.256.F2.0F E6 /r VCVTPD2DQ xmm1, ymm2/m256
	{ "vcvtpd2dq", FCML_AMT_AVX_SIMD, 0x2181, 0x00D88000, { 0x0F, 0xE6, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_MODRM_RM_SIMD_L, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_CVTPD2PI[] = {
	// 66 0F 2D /r CVTPD2PI mm, xmm/m128 A Valid Valid Convert two packed doubleprecision floating-point values from xmm/m128 to two packed signed doubleword integers in mm.
	{ NULL, FCML_AMT_SSE2_SIMD, 0x1001, 0x00D88000, { 0x0F, 0x2D, 0x00 }, { FCML_OP_MODRM_R_MMX_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_CVTPD2PS[] = {
	// 66 0F 5A /r CVTPD2PS xmm1,xmm2/m128 A Valid Valid Convert two packed doubleprecision floating-point values in xmm2/m128 to two packed single-precision floating-point values in xmm1.
	{ NULL, FCML_AMT_SSE2_SIMD, 0x1001, 0x00D88000, { 0x0F, 0x5A, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.128.66.0F 5A /r VCVTPD2PS xmm1, xmm2/m128
	// VEX.256.66.0F 5A /r VCVTPD2PS xmm1, ymm2/m256
	{ "vcvtpd2ps", FCML_AMT_AVX_SIMD, 0x1181, 0x00D88000, { 0x0F, 0x5A, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_MODRM_RM_SIMD_L, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_CVTPI2PD[] = {
	// 66 0F 2A /r CVTPI2PD xmm, mm/m64* A Valid Valid Convert two packed signed doubleword integers from mm/mem64 to two packed double-precision floatingpoint values in xmm.
	{ NULL, FCML_AMT_SSE2_SIMD, 0x1001, 0x00D88000, { 0x0F, 0x2A, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_MMX, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_CVTPI2PS[] = {
	// 0F 2A /r CVTPI2PS xmm, mm/m64 A Valid Valid Convert two signed doubleword integers from mm/m64 to two singleprecision floating-point values in xmm.
	{ NULL, FCML_AMT_SSE_SIMD, 0x0000, 0x00D88000, { 0x0F, 0x2A, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_MMX, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_CVTPS2DQ[] = {
	// 66 0F 5B /r CVTPS2DQ xmm1, xmm2/m128 A Valid Valid Convert four packed singleprecision floating-point values from xmm2/m128 to four packed signed doubleword integers in xmm1.
	{ NULL, FCML_AMT_SSE2_SIMD, 0x1001, 0x00D88000, { 0x0F, 0x5B, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.128.66.0F 5B /r VCVTPS2DQ xmm1, xmm2/m128
	// VEX.256.66.0F 5B /r VCVTPS2DQ ymm1, ymm2/m256
	{ "vcvtps2dq", FCML_AMT_AVX_SIMD, 0x1180, 0x00D88000, { 0x0F, 0x5B, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_MODRM_RM_SIMD_L, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_CVTPS2PD[] = {
	// 0F 5A /r CVTPS2PD xmm1, xmm2/m64 A Valid Valid Convert two packed singleprecision floating-point values in xmm2/m64 to two packed double-precision floating-point values in xmm1.
	{ NULL, FCML_AMT_SSE2_SIMD, 0x0000, 0x00D88000, { 0x0F, 0x5A, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.128.0F 5A /r VCVTPS2PD xmm1, xmm2/m64
	// VEX.256.0F 5A /r VCVTPS2PD ymm1, xmm2/m128
	{ "vcvtps2pd", FCML_AMT_AVX_SIMD, 0x0180, 0x00D88000, { 0x0F, 0x5A, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_MODRM_RM_SIMD_L, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_CVTPS2PI[] = {
	// 0F 2D /r CVTPS2PI mm, xmm/m64 A Valid Valid Convert two packed singleprecision floating-point values from xmm/m64 to two packed signed doubleword integers in mm.
	{ NULL, FCML_AMT_SSE_SIMD, 0x0000, 0x00D88000, { 0x0F, 0x2D, 0x00 }, { FCML_OP_MODRM_R_MMX_W, FCML_OP_MODRM_RM_XMM_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_CVTSD2SI[] = {
	// F2 0F 2D /r CVTSD2SI r32, xmm/m64 A Valid Valid Convert one doubleprecision floating-point value from xmm/m64 to one signed doubleword integer r32.
	{ NULL, FCML_AMT_SSE2_SIMD, 0x2001, 0x03D88000, { 0x0F, 0x2D, 0x00 }, { FCML_OP_MODRM_R_32_W, FCML_OP_MODRM_RM_XMM_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// F2 REX.W 0F 2D /r CVTSD2SI r64, xmm/m64 A Valid N.E. Convert one doubleprecision floating-point value from xmm/m64 to one signed quadword integer sign-extended into r64.
	{ NULL, FCML_AMT_SSE2_SIMD, 0x2009, 0x04988000, { 0x0F, 0x2D, 0x00 }, { FCML_OP_MODRM_R_64_W, FCML_OP_MODRM_RM_XMM_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.128.F2.0F.W0 2D /r VCVTSD2SI r32, xmm1/m64
	{ "vcvtsd2si", FCML_AMT_AVX_SIMD, 0x21D0, 0x03D88000, { 0x0F, 0x2D, 0x00 }, { FCML_OP_MODRM_R_32_W, FCML_OP_MODRM_RM_SIMD_L_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.128.F2.0F.W1 2D /r VCVTSD2SI r64, xmm1/m64
	{ "vcvtsd2si", FCML_AMT_AVX_SIMD, 0x21C8, 0x04988000, { 0x0F, 0x2D, 0x00 }, { FCML_OP_MODRM_R_64_W, FCML_OP_MODRM_RM_SIMD_L_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_CVTSD2SS[] = {
	// F2 0F 5A /r CVTSD2SS xmm1, xmm2/m64 A Valid Valid Convert one doubleprecision floating-point value in xmm2/m64 to one single-precision floatingpoint value in xmm1.
	{ NULL, FCML_AMT_SSE2_SIMD, 0x2001, 0x00D88000, { 0x0F, 0x5A, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.F2.0F 5A /r VCVTSD2SS xmm1,xmm2,xmm3/m64
	{ "vcvtsd2ss", FCML_AMT_AVX_SIMD, 0x20C0, 0x00D88000, { 0x0F, 0x5A, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L_64, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_CVTSI2SD[] = {
	// F2 0F 2A /r CVTSI2SD xmm, r/m32 A Valid Valid Convert one signed doubleword integer from r/m32 to one doubleprecision floating-point value in xmm.
	{ NULL, FCML_AMT_SSE2_SIMD, 0x2001, 0x03D88000, { 0x0F, 0x2A, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_32, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// F2 REX.W 0F 2A /r CVTSI2SD xmm, r/m64 A Valid N.E. Convert one signed quadword integer from r/m64 to one doubleprecision floating-point value in xmm.
	{ NULL, FCML_AMT_SSE2_SIMD, 0x2009, 0x04988000, { 0x0F, 0x2A, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.F2.0F.W0 2A /r VCVTSI2SD xmm1, xmm2, r/m32
	{ "vcvtsi2sd", FCML_AMT_AVX_SIMD, 0x20D0, 0x03D88000, { 0x0F, 0x2A, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_32, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.F2.0F.W1 2A /r VCVTSI2SD xmm1, xmm2, r/m64
	{ "vcvtsi2sd", FCML_AMT_AVX_SIMD, 0x20C8, 0x04988000, { 0x0F, 0x2A, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_64, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_CVTSI2SS[] = {
	// F3 0F 2A /r CVTSI2SS xmm, r/m32 A Valid Valid Convert one signed doubleword integer from r/m32 to one singleprecision floating-point value in xmm.
	{ NULL, FCML_AMT_SSE_SIMD, 0x4010, 0x03D88000, { 0x0F, 0x2A, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_32, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// F3 REX.W 0F 2A /r CVTSI2SS xmm, r/m64 A Valid N.E. Convert one signed quadword integer from r/m64 to one singleprecision floating-point value in xmm.
	{ NULL, FCML_AMT_SSE_SIMD, 0x4008, 0x04988000, { 0x0F, 0x2A, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.F3.0F.W0 2A /r VCVTSI2SS xmm1, xmm2, r/m32
	{ "vcvtsi2ss", FCML_AMT_AVX_SIMD, 0x40D0, 0x03D88000, { 0x0F, 0x2A, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_32, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.F3.0F.W1 2A /r VCVTSI2SS xmm1, xmm2, r/m64
	{ "vcvtsi2ss", FCML_AMT_AVX_SIMD, 0x40C8, 0x04988000, { 0x0F, 0x2A, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_64, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_CVTSS2SD[] = {
	// F3 0F 5A /r CVTSS2SD xmm1, xmm2/m32 A Valid Valid Convert one single-precision floating-point value in xmm2/m32 to one doubleprecision floating-point value in xmm1.
	{ NULL, FCML_AMT_SSE2_SIMD, 0x4001, 0x00D88000, { 0x0F, 0x5A, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_32, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.F3.0F 5A /r VCVTSS2SD xmm1, xmm2, xmm3/m32
	{ "vcvtss2sd", FCML_AMT_AVX_SIMD, 0x40C0, 0x00D88000, { 0x0F, 0x5A, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_32, FCML_NA, FCML_NA }, FCML_AM_NONE },
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_CVTSS2SI[] = {
	// F3 0F 2D /r CVTSS2SI r32, xmm/m32 A Valid Valid Convert one single-precision floating-point value from xmm/m32 to one signed doubleword integer in r32.
	{ NULL, FCML_AMT_SSE_SIMD, 0x4010, 0x03D88000, { 0x0F, 0x2D, 0x00 }, { FCML_OP_MODRM_R_32_W, FCML_OP_MODRM_RM_XMM_32, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// F3 REX.W 0F 2D /r CVTSS2SI r64, xmm/m32 A Valid N.E. Convert one single-precision floating-point value from xmm/m32 to one signed quadword integer in r64.
	{ NULL, FCML_AMT_SSE_SIMD, 0x4008, 0x04988000, { 0x0F, 0x2D, 0x00 }, { FCML_OP_MODRM_R_64_W, FCML_OP_MODRM_RM_XMM_32, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.128.F3.0F.W0 2D /r VCVTSS2SI r32, xmm1/m32
	{ "vcvtss2si", FCML_AMT_AVX_SIMD, 0x41D0, 0x03D88000, { 0x0F, 0x2D, 0x00 }, { FCML_OP_MODRM_R_32_W, FCML_OP_MODRM_RM_SIMD_L_32, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.128.F3.0F.W1 2D /r VCVTSS2SI r64, xmm1/m32
	{ "vcvtss2si", FCML_AMT_AVX_SIMD, 0x41C8, 0x04988000, { 0x0F, 0x2D, 0x00 }, { FCML_OP_MODRM_R_64_W, FCML_OP_MODRM_RM_SIMD_L_32, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_CVTTPD2DQ[] = {
	// 66 0F E6 CVTTPD2DQ xmm1, xmm2/m128 A Valid Valid Convert two packed doubleprecision floating-point values from xmm2/m128 to two packed signed doubleword integers in xmm1 using truncation.
	{ NULL, FCML_AMT_SSE2_SIMD, 0x1001, 0x00D88000, { 0x0F, 0xE6, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.128.66.0F E6 /r VCVTTPD2DQ xmm1, xmm2/m128
	// VEX.256.66.0F E6 /r VCVTTPD2DQ xmm1, ymm2/m256
	{ "vcvttpd2dq", FCML_AMT_AVX_SIMD, 0x1180, 0x00D88000, { 0x0F, 0xE6, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_MODRM_RM_SIMD_L, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_CVTTPD2PI[] = {
	// 66 0F 2C /r CVTTPD2PI mm, xmm/m128 A Valid Valid Convert two packer doubleprecision floating-point values from xmm/m128 to two packed signed doubleword integers in mm using truncation.
	{ NULL, FCML_AMT_SSE2_SIMD, 0x1001, 0x00D88000, { 0x0F, 0x2C, 0x00 }, { FCML_OP_MODRM_R_MMX_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_CVTTPS2DQ[] = {
	// F3 0F 5B /r CVTTPS2DQ xmm1, xmm2/m128 A Valid Valid Convert four singleprecision floating-point values from xmm2/m128 to four signed doubleword integers in xmm1 using truncation.
	{ NULL, FCML_AMT_SSE2_SIMD, 0x4001, 0x00D88000, { 0x0F, 0x5B, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.128.F3.0F 5B /r VCVTTPS2DQ xmm1, xmm2/m128
	// VEX.256.F3.0F 5B /r VCVTTPS2DQ ymm1, ymm2/m256
	{ "vcvttps2dq", FCML_AMT_AVX_SIMD, 0x4180, 0x00D88000, { 0x0F, 0x5B, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_MODRM_RM_SIMD_L, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_CVTTPS2PI[] = {
	// 0F 2C /r CVTTPS2PI mm, xmm/m64 A Valid Valid Convert two singleprecision floating-point values from xmm/m64 to two signed doubleword signed integers in mm using truncation.
	{ NULL, FCML_AMT_SSE_SIMD, 0x0000, 0x00D88000, { 0x0F, 0x2C, 0x00 }, { FCML_OP_MODRM_R_MMX_W, FCML_OP_MODRM_RM_XMM_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_CVTTSD2SI[] = {
	// F2 0F 2C /r CVTTSD2SI r32, xmm/m64 A Valid Valid Convert one doubleprecision floating-point value from xmm/m64 to one signed doubleword integer in r32 using truncation.
	{ NULL, FCML_AMT_SSE2_SIMD, 0x2001, 0x03D88000, { 0x0F, 0x2C, 0x00 }, { FCML_OP_MODRM_R_32_W, FCML_OP_MODRM_RM_XMM_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// F2 REX.W 0F 2C /r CVTTSD2SI r64, xmm/m64 A Valid N.E. Convert one double precision floating-point value from xmm/m64 to one signedquad wordinteger in r64 using truncation.
	{ NULL, FCML_AMT_SSE2_SIMD, 0x2009, 0x04988000, { 0x0F, 0x2C, 0x00 }, { FCML_OP_MODRM_R_64_W, FCML_OP_MODRM_RM_XMM_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.128.F2.0F.W0 2C /r VCVTTSD2SI r32, xmm1/m64
	{ "vcvttsd2si", FCML_AMT_AVX_SIMD, 0x21D0, 0x03D88000, { 0x0F, 0x2C, 0x00 }, { FCML_OP_MODRM_R_32_W, FCML_OP_MODRM_RM_SIMD_L_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.128.F2.0F.W1 2C /r VCVTTSD2SI r64, xmm1/m64
	{ "vcvttsd2si", FCML_AMT_AVX_SIMD, 0x21C8, 0x04988000, { 0x0F, 0x2C, 0x00 }, { FCML_OP_MODRM_R_64_W, FCML_OP_MODRM_RM_SIMD_L_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

// MMWORD
struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_CVTTSS2SI[] = {
	// F3 0F 2C /r CVTTSS2SI r32, xmm/m32 A Valid Valid Convert one single-precision floating-point value from xmm/m32 to one signed doubleword integer in r32 using truncation.
	{ NULL, FCML_AMT_SSE_SIMD, 0x4010, 0x03D88000, { 0x0F, 0x2C, 0x00 }, { FCML_OP_MODRM_R_32_W, FCML_OP_MODRM_RM_XMM_32, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// F3 REX.W 0F 2C /r CVTTSS2SI r64, xmm/m32 A Valid N.E. Convert one single-precision floating-point value from xmm/m32 to one signed quadword integer in
	{ NULL, FCML_AMT_SSE_SIMD, 0x4008, 0x04988000, { 0x0F, 0x2C, 0x00 }, { FCML_OP_MODRM_R_64_W, FCML_OP_MODRM_RM_XMM_32, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.128.F3.0F.W0 2C /r VCVTTSS2SI r32, xmm1/m32
	{ "vcvttss2si", FCML_AMT_AVX_SIMD, 0x4390, 0x03D88000, { 0x0F, 0x2C, 0x00 }, { FCML_OP_MODRM_R_32_W, FCML_OP_MODRM_RM_SIMD_L_32, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.128.F3.0F.W1 2C /r VCVTTSS2SI r64, xmm1/m32
	{ "vcvttss2si", FCML_AMT_AVX_SIMD, 0x4388, 0x04988000, { 0x0F, 0x2C, 0x00 }, { FCML_OP_MODRM_R_64_W, FCML_OP_MODRM_RM_SIMD_L_32, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_CWD_CDQ_CQO[] = {
	// 99 CWD A Valid Valid DX:AX <- sign-extend of AX.
	{ "cwd", FCML_AMT_GPI, 0x0000, 0x01C40000, { 0x99, 0x00, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 99 CDQ A Valid Valid EDX:EAX <- sign-extend of EAX.
	{ "cdq", FCML_AMT_GPI, 0x0000, 0x02C40000, { 0x99, 0x00, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// REX.W + 99 CQO A Valid N.E. RDX:RAX <- sign-extend of RAX.
	{ "cqo", FCML_AMT_GPI, 0x0000, 0x04840000, { 0x99, 0x00, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_DAA[] = {
	// 27 DAA A Invalid Valid Decimal adjust AL after addition.
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00440000, { 0x27, 0x00, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_DAS[] = {
	// 2F DAS A Invalid Valid Decimal adjust AL after subtraction.
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00440000, { 0x2F, 0x00, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_DEC[] = {
	// FE /1 DEC r/m8 A Valid Valid Decrement r/m8 by 1.
	// REX + FE /1 DEC r/m8* A Valid N.E. Decrement r/m8 by 1.
	{ NULL, FCML_AMT_GPI, 0x0807, 0x00C58800, { 0xFE, 0x00, 0x00 }, { FCML_OP_MODRM_RM_8_W, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// FF /1 DEC r/m16 A Valid Valid Decrement r/m16 by 1.
	// FF /1 DEC r/m32 A Valid Valid Decrement r/m32 by 1.
	// REX.W + FF /1 DEC r/m64 A Valid N.E. Decrement r/m64 by 1.
	{ NULL, FCML_AMT_GPI, 0x0807, 0x00C58800, { 0xFF, 0x00, 0x00 }, { FCML_OP_MODRM_RM_W, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 48+rw DEC r16 B N.E. Valid Decrement r16 by 1.
	// 48+rd DEC r32 B N.E. Valid Decrement r32 by 1.
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00440001, { 0x48, 0x00, 0x00 }, { FCML_OP_OPCODE_REG( FCML_REG_GPR, FCML_EOS_EOSA ), FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_DIV[] = {
	// F6 /6 DIV r/m8 A Valid Valid Unsigned divide AX by r/m8,with result stored in AL Quotient, AH Remainder.
	// REX + F6 /6 DIV r/m8* A Valid N.E. Unsigned divide AX by r/m8, with result stored in AL Quotient, AH Remainder.
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00C5B000, { 0xF6, 0x00, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_AX, FCML_EOS_WORD ), FCML_OP_MODRM_RM_8_W, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// F7 /6 DIV r/m16 A Valid Valid Unsigned divide DX:AX by r/m16, with result stored in AX Quotient, DX Remainder.
	// F7 /6 DIV r/m32 A Valid Valid Unsigned divide EDX:EAX by r/m32, with result stored in EAX Quotient, EDX Remainder.
	// REX.W + F7 /6 DIV r/m64 A Valid N.E. Unsigned divide RDX:RAX by r/m64, with result stored in RAX Quotient, RDX Remainder.
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00C5B000, { 0xF7, 0x00, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_AL, FCML_EOS_EOSA ), FCML_OP_MODRM_RM_W, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_DIVPD[] = {
	// 66 0F 5E /r DIVPD xmm1, xmm2/m128 A Valid Valid Divide packed doubleprecision floating-point values in xmm1 by packed double-precision floatingpoint values xmm2/m128.
	{ NULL, FCML_AMT_SSE2_SIMD, 0x1001, 0x00D88000, { 0x0F, 0x5E, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.66.0F 5E /r VDIVPD xmm1, xmm2, xmm3/m128
	// VEX.NDS.256.66.0F 5E /r VDIVPD ymm1, ymm2, ymm3/m256
	{ "vdivpd", FCML_AMT_AVX_SIMD, 0x1080, 0x00D88000, { 0x0F, 0x5E, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_DIVPS[] = {
	// 0F 5E /r DIVPS xmm1, xmm2/m128 A Valid Valid Divide packed singleprecision floating-point values in xmm1 by packed single-precision floatingpoint values xmm2/m128.
	{ NULL, FCML_AMT_SSE_SIMD, 0x0000, 0x00D88000, { 0x0F, 0x5E, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.0F 5E /r VDIVPS xmm1, xmm2, xmm3/m128
	// VEX.NDS.256.0F 5E /r VDIVPS ymm1, ymm2, ymm3/m256
	{ "vdivps", FCML_AMT_AVX_SIMD, 0x0080, 0x00D88000, { 0x0F, 0x5E, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_DIVSD[] = {
	// F2 0F 5E /r DIVSD xmm1, xmm2/m64 A Valid Valid Divide low double-precision floating-point value n xmm1 by low double-precision floating-point value in xmm2/mem64.
	{ NULL, FCML_AMT_SSE2_SIMD, 0x2001, 0x00D88000, { 0x0F, 0x5E, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.F2.0F 5E /r VDIVSD xmm1, xmm2, xmm3/m64
	{ "vdivsd", FCML_AMT_AVX_SIMD, 0x20C0, 0x00D88000, { 0x0F, 0x5E, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L_64, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_DIVSS[] = {
	// F3 0F 5E /r DIVSS xmm1, xmm2/m32 A Valid Valid Divide low single-precision floating-point value in xmm1 by low singleprecision floating-point value in xmm2/m32.
	{ NULL, FCML_AMT_SSE_SIMD, 0x4001, 0x00D88000, { 0x0F, 0x5E, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_32, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.F3.0F 5E /r VDIVSS xmm1, xmm2, xmm3/m32
	{ "vdivss", FCML_AMT_AVX_SIMD, 0x40C0, 0x00D88000, { 0x0F, 0x5E, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L_32, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_DPPD[] = {
	// 66 0F 3A 41 /r ib DPPD xmm1, xmm2/m128, imm8 A Valid Valid Selectively multiply packed DP floating-point values from xmm1 with packed DP floating-point values from xmm2, add and selectively store the packed DP floating-point values to xmm1.
	{ NULL, FCML_AMT_SSE41_SIMD, 0x1001, 0x00EC8000, { 0x0F, 0x3A, 0x41 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.66.0F3A 41 /r ib VDPPD xmm1,xmm2,xmm3/m128,imm8
	{ "vdppd", FCML_AMT_AVX_SIMD, 0x10C0, 0x00EC8000, { 0x0F, 0x3A, 0x41 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L_128, FCML_OP_IB, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_DPPS[] = {
	// 66 0F 3A 40 /r ib DPPS xmm1, xmm2/m128, imm8 A Valid Valid Selectively multiply packed SP floating-point values from xmm1 with packed SP floating-point values from xmm2, add and selectively store the packed SP floating-point values or zero values to xmm1.
	{ NULL, FCML_AMT_SSE41_SIMD, 0x1001, 0x00EC8000, { 0x0F, 0x3A, 0x40 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.66.0F3A 40 /r ib VDPPS xmm1,xmm2,xmm3/m128,imm8
	// VEX.NDS.256.66.0F3A 40 /r ib VDPPS ymm1,ymm2,ymm3/m256,imm8
	{ "vdpps", FCML_AMT_AVX_SIMD, 0x1080, 0x00EC8000, { 0x0F, 0x3A, 0x40 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L, FCML_OP_IB, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VEXTRACTF128[] = {
	// VEX.256.66.0F3A 19 /r ib VEXTRACTF128 xmm1/m128,ymm2,imm8
	{ "vextractf128", FCML_AMT_AVX_SIMD, 0x11A0, 0x00EC8000, { 0x0F, 0x3A, 0x19 }, { FCML_OP_MODRM_RM_XMM_128_W, FCML_OP_MODRM_R_SIMD_L, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_EMMS[] = {
	// 0F 77 EMMS A Valid Valid Set the x87 FPU tag word to empty.
	{ NULL, FCML_AMT_MMX, 0x0000, 0x00D80000, { 0x0F, 0x77, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_ENTER[] = {
	// C8 iw 00 ENTER imm16, 0 A Valid Valid Create a stack frame for a procedure.
	// C8 iw 01 ENTER imm16, 1 A Valid Valid Create a nested stack frame for a procedure.
	// C8 iw ib ENTER imm16, imm8 A Valid Valid Create a nested stack frame for a procedure.
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00C40000, { 0xC8, 0x00, 0x00 }, { FCML_OP_IW | FCML_OA_W, FCML_OP_IB, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_EXTRACTPS[] = {
	// 66 0F 3A 17 /r ib EXTRACTPS reg/m32, xmm2, imm8 A Valid Valid Extract a single-precision floating-point value from xmm2 at the source offset specified by imm8 and store the result to reg or m32. The upper 32 bits of r64 is zeroed if reg is r64.,
	{ NULL, FCML_AMT_SSE41_SIMD, 0x1001, 0x00EC8000, { 0x0F, 0x3A, 0x17 }, { FCML_OP_MODRM_RM_32_W, FCML_OP_MODRM_R_XMM, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.128.66.0F3A 17 /r ib VEXTRACTPS r/m32, xmm1, imm8
	{ "vextractps", FCML_AMT_AVX_SIMD, 0x11C0, 0x00EC8000, { 0x0F, 0x3A, 0x17 }, { FCML_OP_MODRM_RM_32_W, FCML_OP_MODRM_R_XMM, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_EXTRQ[] = {
	// EXTRQ xmm1,imm8,imm8 66 0F 78 /0 ib ib
	{ NULL, FCML_AMT_SSE4A, 0x1000, 0x00DB8000, { 0x0F, 0x78, 0x00 }, { FCML_OP_RM( FCML_REG_SIMD, FCML_EOS_OWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_OP_IB, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// EXTRQ xmm1,xmm2 66 0F 79 /r
	{ NULL, FCML_AMT_SSE4A, 0x1000, 0x00DA8000, { 0x0F, 0x79, 0x00 }, { FCML_OP_MODRM_R_XMM, FCML_OP_RM( FCML_REG_SIMD, FCML_EOS_OWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_F2XM1[] = {
	// D9 F0 F2XM1 Valid Valid Replace ST(0) with (2ST(0)  1).
	{ NULL, FCML_AMT_FPU, 0x0000, 0x00D80000, { 0xD9, 0xF0, 0x17 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FABS[] = {
	// D9 E1 FABS Valid Valid Replace ST with its absolute value.
	{ NULL, FCML_AMT_FPU, 0x0000, 0x00D80000, { 0xD9, 0xE1, 0x17 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FADD[] = {
	// D8 /0 FADD m32fp Valid Valid Add m32fp to ST(0) and store result in ST(0).
	{ NULL, FCML_AMT_FPU, 0x0000, 0x00C58000, { 0xD8, 0x00, 0x00 }, { FCML_OP_MODRM_M_32, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// DC /0 FADD m64fp Valid Valid Add m64fp to ST(0) and store result in ST(0).
	{ NULL, FCML_AMT_FPU, 0x0000, 0x00C58000, { 0xDC, 0x00, 0x00 }, { FCML_OP_MODRM_M_64, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// D8 C0+i FADD ST(0), ST(i) Valid Valid Add ST(0) to ST(i) and store result in ST(0).
	{ NULL, FCML_AMT_FPU, 0x0000, 0x00D80001, { 0xD8, 0xC0, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_FPU, FCML_REG_ST0, FCML_EOS_UNDEFINED ), FCML_OP_OPCODE_REG( FCML_REG_FPU, FCML_EOS_UNDEFINED ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// DC C0+i FADD ST(i), ST(0) Valid Valid Add ST(i) to ST(0) and store result in ST(i).
	{ NULL, FCML_AMT_FPU, 0x0000, 0x00D80001, { 0xDC, 0xC0, 0x00 }, { FCML_OP_OPCODE_REG( FCML_REG_FPU, FCML_EOS_UNDEFINED ), FCML_OP_EXPLICIT_REG( FCML_REG_FPU, FCML_REG_ST0, FCML_EOS_UNDEFINED ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// DE C0+i FADDP ST(i), ST(0) Valid Valid Add ST(0) to ST(i), store result in ST(i), and pop the register stack.
	{ "faddp", FCML_AMT_FPU, 0x0000, 0x00D80001, { 0xDE, 0xC0, 0x00 }, { FCML_OP_OPCODE_REG( FCML_REG_FPU, FCML_EOS_UNDEFINED ), FCML_OP_EXPLICIT_REG( FCML_REG_FPU, FCML_REG_ST0, FCML_EOS_UNDEFINED ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// DA /0 FIADD m32int Valid Valid Add m32int to ST(0) and store result in ST(0).
	{ "fiadd", FCML_AMT_FPU, 0x0000, 0x00C58000, { 0xDA, 0x00, 0x00 }, { FCML_OP_MODRM_M_32, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// DE /0 FIADD m16int Valid Valid Add m16int to ST(0) and store result in ST(0).
	{ "fiadd", FCML_AMT_FPU, 0x0000, 0x00C58000, { 0xDE, 0x00, 0x00 }, { FCML_OP_MODRM_M_16, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// DE C1 FADDP
	{ "faddp", FCML_AMT_FPU, 0x0000, 0x00D80000, { 0xDE, 0xC1, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FBLD[] = {
	// DF /4 FBLD m80 dec Valid Valid Convert BCD value to floating-point and push onto the FPU stack.
	{ NULL, FCML_AMT_FPU, 0x0000, 0x00C5A000, { 0xDF, 0x00, 0x00 }, { FCML_OP_MODRM_M_80, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FBSTP[] = {
	// DF /6 FBSTP m80bcd Valid Valid Store ST(0) in m80bcd and pop ST(0).
	{ NULL, FCML_AMT_FPU, 0x0000, 0x00C5B000, { 0xDF, 0x00, 0x00 }, { FCML_OP_MODRM_M_80, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FCHS[] = {
	// D9 E0 FCHS Valid Valid Complements sign of ST(0).
	{ NULL, FCML_AMT_FPU, 0x0000, 0x00D80000, { 0xD9, 0xE0, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FCLEX[] = {
	// 9B DB E2 FCLEX Valid Valid Clear floating-point exception flags after checking for pending unmasked floatingpoint exceptions.
	{ NULL, FCML_AMT_FPU, 0x0000, 0x00EC0000, { 0x9B, 0xDB, 0xE2 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// DB E2 * Valid Valid Clear floating-point exception flags without checking for pending unmasked floating-point exceptions.
	{ "fnclex", FCML_AMT_FPU, 0x0000, 0x00D80000, { 0xDB, 0xE2, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FCMOV[] = {
	// DA C0+i FCMOVB ST(0), ST(i) Valid Valid Move if below (CF=1).
	{ "fcmovb", FCML_AMT_FPU, 0x0000, 0x00D80001, { 0xDA, 0xC0, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_FPU, FCML_REG_ST0, FCML_EOS_UNDEFINED ), FCML_OP_OPCODE_REG( FCML_REG_FPU, FCML_EOS_UNDEFINED ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// DA C8+i FCMOVE ST(0), ST(i) Valid Valid Move if equal (ZF=1).
	{ "fcmove", FCML_AMT_FPU, 0x0000, 0x00D80001, { 0xDA, 0xC8, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_FPU, FCML_REG_ST0, FCML_EOS_UNDEFINED ), FCML_OP_OPCODE_REG( FCML_REG_FPU, FCML_EOS_UNDEFINED ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// DA D0+i FCMOVBE ST(0), ST(i) Valid Valid Move if below or equal (CF=1 or ZF=1).
	{ "fcmovbe", FCML_AMT_FPU, 0x0000, 0x00D80001, { 0xDA, 0xD0, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_FPU, FCML_REG_ST0, FCML_EOS_UNDEFINED ), FCML_OP_OPCODE_REG( FCML_REG_FPU, FCML_EOS_UNDEFINED ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// DA D8+i FCMOVU ST(0), ST(i) Valid Valid Move if unordered (PF=1).
	{ "fcmovu", FCML_AMT_FPU, 0x0000, 0x00D80001, { 0xDA, 0xD8, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_FPU, FCML_REG_ST0, FCML_EOS_UNDEFINED ), FCML_OP_OPCODE_REG( FCML_REG_FPU, FCML_EOS_UNDEFINED ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// DB C0+i FCMOVNB ST(0), ST(i) Valid Valid Move if not below (CF=0).
	{ "fcmovnb", FCML_AMT_FPU, 0x0000, 0x00D80001, { 0xDB, 0xC0, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_FPU, FCML_REG_ST0, FCML_EOS_UNDEFINED ), FCML_OP_OPCODE_REG( FCML_REG_FPU, FCML_EOS_UNDEFINED ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// DB C8+i FCMOVNE ST(0), ST(i) Valid Valid Move if not equal (ZF=0).
	{ "fcmovne", FCML_AMT_FPU, 0x0000, 0x00D80001, { 0xDB, 0xC8, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_FPU, FCML_REG_ST0, FCML_EOS_UNDEFINED ), FCML_OP_OPCODE_REG( FCML_REG_FPU, FCML_EOS_UNDEFINED ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// DB D0+i FCMOVNBE ST(0), ST(i) Valid Valid Move if not below or equal (CF=0 and ZF=0).
	{ "fcmovnbe", FCML_AMT_FPU, 0x0000, 0x00D80001, { 0xDB, 0xD0, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_FPU, FCML_REG_ST0, FCML_EOS_UNDEFINED ), FCML_OP_OPCODE_REG( FCML_REG_FPU, FCML_EOS_UNDEFINED ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// DB D8+i FCMOVNU ST(0), ST(i) Valid Valid Move if not unordered (PF=0).
	{ "fcmovnu", FCML_AMT_FPU, 0x0000, 0x00D80001, { 0xDB, 0xD8, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_FPU, FCML_REG_ST0, FCML_EOS_UNDEFINED ), FCML_OP_OPCODE_REG( FCML_REG_FPU, FCML_EOS_UNDEFINED ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FCOM[] = {
	// D8 /2 FCOM m32fp
	{ "fcom", FCML_AMT_FPU, 0x0000, 0x00C59000, { 0xD8, 0x00, 0x00 }, { FCML_OP_MODRM_M_32, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// D8 /3 FCOMP m32fp
	{ "fcomp", FCML_AMT_FPU, 0x0000, 0x00C59800, { 0xD8, 0x00, 0x00 }, { FCML_OP_MODRM_M_32, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// DC /2 FCOM m64fp
	{ "fcom", FCML_AMT_FPU, 0x0000, 0x00C59000, { 0xDC, 0x00, 0x00 }, { FCML_OP_MODRM_M_64, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// DC /3 FCOMP m64fp
	{ "fcomp", FCML_AMT_FPU, 0x0000, 0x00C59800, { 0xDC, 0x00, 0x00 }, { FCML_OP_MODRM_M_64, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// D8 D0+i FCOM ST(i)
	{ "fcom", FCML_AMT_FPU, 0x0000, 0x00D80001, { 0xD8, 0xD0, 0x00 }, { FCML_OP_OPCODE_REG( FCML_REG_FPU, FCML_EOS_UNDEFINED ), FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// D8 D8+i FCOMP ST(i)
	{ "fcomp", FCML_AMT_FPU, 0x0000, 0x00D80001, { 0xD8, 0xD8, 0x00 }, { FCML_OP_OPCODE_REG( FCML_REG_FPU, FCML_EOS_UNDEFINED ), FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// DE D9 FCOMPP
	{ "fcompp", FCML_AMT_FPU, 0x0000, 0x00D80000, { 0xDE, 0xD9, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// D8 D1 FCOM
	{ "fcom", FCML_AMT_FPU, 0x0000, 0x00D80000, { 0xD8, 0xD1, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// D8 D9 FCOMP
	{ "fcomp", FCML_AMT_FPU, 0x0000, 0x00D80000, { 0xD8, 0xD9, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FCOMI[] = {
	// DB F0+i FCOMI ST, ST(i) Valid Valid Compare ST(0) with ST(i) and set status flags accordingly.
	{ "fcomi", FCML_AMT_FPU, 0x0000, 0x00D80001, { 0xDB, 0xF0, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_FPU, FCML_REG_ST0, FCML_EOS_UNDEFINED ), FCML_OP_OPCODE_REG( FCML_REG_FPU, FCML_EOS_UNDEFINED ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// DF F0+i FCOMIP ST, ST(i) Valid Valid Compare ST(0) with ST(i), set status flags accordingly, and pop register stack.
	{ "fcomip", FCML_AMT_FPU, 0x0000, 0x00D80001, { 0xDF, 0xF0, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_FPU, FCML_REG_ST0, FCML_EOS_UNDEFINED ), FCML_OP_OPCODE_REG( FCML_REG_FPU, FCML_EOS_UNDEFINED ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// DB E8+i FUCOMI ST, ST(i) Valid Valid Compare ST(0) with ST(i), check for ordered values, and set status flags accordingly.
	{ "fucomi", FCML_AMT_FPU, 0x0000, 0x00D80001, { 0xDB, 0xE8, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_FPU, FCML_REG_ST0, FCML_EOS_UNDEFINED ), FCML_OP_OPCODE_REG( FCML_REG_FPU, FCML_EOS_UNDEFINED ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// DF E8+i FUCOMIP ST, ST(i) Valid Valid Compare ST(0) with ST(i), check for ordered values, set status flags accordingly, and pop register stack.
	{ "fucomip", FCML_AMT_FPU, 0x0000, 0x00D80001, { 0xDF, 0xE8, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_FPU, FCML_REG_ST0, FCML_EOS_UNDEFINED ), FCML_OP_OPCODE_REG( FCML_REG_FPU, FCML_EOS_UNDEFINED ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FCOS[] = {
	// D9 FF FCOS Valid Valid Replace ST(0) with its cosine.
	{ NULL, FCML_AMT_FPU, 0x0000, 0x00D80000, { 0xD9, 0xFF, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FDECSTP[] = {
	// D9 F6 FDECSTP Valid Valid Decrement
	{ NULL, FCML_AMT_FPU, 0x0000, 0x00D80000, { 0xD9, 0xF6, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FDIV[] = {
	// D8 /6 FDIV m32fp Valid Valid Divide ST(0) by m32fp and store result in ST(0).
	{ NULL, FCML_AMT_FPU, 0x0000, 0x00C5B000, { 0xD8, 0x00, 0x00 }, { FCML_OP_MODRM_M_32, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// DC /6 FDIV m64fp Valid Valid Divide ST(0) by m64fp and store result in ST(0).
	{ NULL, FCML_AMT_FPU, 0x0000, 0x00C5B000, { 0xDC, 0x00, 0x00 }, { FCML_OP_MODRM_M_64, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// D8 F0+i FDIV ST(0), ST(i) Valid Valid Divide ST(0) by ST(i) and store result in ST(0).
	{ NULL, FCML_AMT_FPU, 0x0000, 0x00D80001, { 0xD8, 0xF0, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_FPU, FCML_REG_ST0, FCML_EOS_UNDEFINED ), FCML_OP_OPCODE_REG( FCML_REG_FPU, FCML_EOS_UNDEFINED ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// DC F8+i FDIV ST(i), ST(0) Valid Valid Divide ST(i) by ST(0) and store result in ST(i).
	{ NULL, FCML_AMT_FPU, 0x0000, 0x00D80001, { 0xDC, 0xF8, 0x00 }, { FCML_OP_OPCODE_REG( FCML_REG_FPU, FCML_EOS_UNDEFINED ), FCML_OP_EXPLICIT_REG( FCML_REG_FPU, FCML_REG_ST0, FCML_EOS_UNDEFINED ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// DE F8+i FDIVP ST(i), ST(0) Valid Valid Divide ST(i) by ST(0), store result in ST(i), and pop the register stack.
	{ "fdivp", FCML_AMT_FPU, 0x0000, 0x00D80001, { 0xDE, 0xF8, 0x00 }, { FCML_OP_OPCODE_REG( FCML_REG_FPU, FCML_EOS_UNDEFINED ), FCML_OP_EXPLICIT_REG( FCML_REG_FPU, FCML_REG_ST0, FCML_EOS_UNDEFINED ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// DA /6 FIDIV m32int Valid Valid Divide ST(0) by m32int and store result in ST(0).
	{ "fidiv", FCML_AMT_FPU, 0x0000, 0x00C5B000, { 0xDA, 0x00, 0x00 }, { FCML_OP_MODRM_M_32, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// DE /6 FIDIV m16int Valid Valid Divide ST(0) by m64int and store result in ST(0).
	{ "fidiv", FCML_AMT_FPU, 0x0000, 0x00C5B000, { 0xDE, 0x00, 0x00 }, { FCML_OP_MODRM_M_16, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// DE F9 FDIVP
	{ "fdivp", FCML_AMT_FPU, 0x0000, 0x00D80000, { 0xDE, 0xF9, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FDIVR[] = {
	// D8 /7 FDIVR m32fp Valid Valid Divide m32fp by ST(0) and store result in ST(0).
	{ NULL, FCML_AMT_FPU, 0x0000, 0x00C5B800, { 0xD8, 0x00, 0x00 }, { FCML_OP_MODRM_M_32, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// DC /7 FDIVR m64fp Valid Valid Divide m64fp by ST(0) and store result in ST(0).
	{ NULL, FCML_AMT_FPU, 0x0000, 0x00C5B800, { 0xDC, 0x00, 0x00 }, { FCML_OP_MODRM_M_64, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// D8 F8+i FDIVR ST(0), ST(i) Valid Valid Divide ST(i) by ST(0) and store result in ST(0).
	{ NULL, FCML_AMT_FPU, 0x0000, 0x00D80001, { 0xD8, 0xF8, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_FPU, FCML_REG_ST0, FCML_EOS_UNDEFINED ), FCML_OP_OPCODE_REG( FCML_REG_FPU, FCML_EOS_UNDEFINED ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// DC F0+i FDIVR ST(i), ST(0) Valid Valid Divide ST(0) by ST(i) and store result in ST(i).
	{ NULL, FCML_AMT_FPU, 0x0000, 0x00D80001, { 0xDC, 0xF0, 0x00 }, { FCML_OP_OPCODE_REG( FCML_REG_FPU, FCML_EOS_UNDEFINED ), FCML_OP_EXPLICIT_REG( FCML_REG_FPU, FCML_REG_ST0, FCML_EOS_UNDEFINED ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// DE F0+i FDIVRP ST(i), ST(0) Valid Valid Divide ST(0) by ST(i), store result in ST(i), and pop the register stack.
	{ "fdivrp", FCML_AMT_FPU, 0x0000, 0x00D80001, { 0xDE, 0xF0, 0x00 }, { FCML_OP_OPCODE_REG( FCML_REG_FPU, FCML_EOS_UNDEFINED ), FCML_OP_EXPLICIT_REG( FCML_REG_FPU, FCML_REG_ST0, FCML_EOS_UNDEFINED ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// DA /7 FIDIVR m32int Valid Valid Divide m32int by ST(0) and store result in ST(0).
	{ "fidivr", FCML_AMT_FPU, 0x0000, 0x00C5B800, { 0xDA, 0x00, 0x00 }, { FCML_OP_MODRM_M_32, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// DE /7 FIDIVR m16int Valid Valid Divide m16int by ST(0) and store result in ST(0).
	{ "fidivr", FCML_AMT_FPU, 0x0000, 0x00C5B800, { 0xDE, 0x00, 0x00 }, { FCML_OP_MODRM_M_16, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// DE F1 FDIVRP
	{ "fdivrp", FCML_AMT_FPU, 0x0000, 0x00D80000, { 0xDE, 0xF1, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FFREE[] = {
	// DD C0+i FFREE ST(i) Valid Valid Sets tag for ST(i) to empty.
	{ NULL, FCML_AMT_FPU, 0x0000, 0x00D80001, { 0xDD, 0xC0, 0x00 }, { FCML_OP_OPCODE_REG( FCML_REG_FPU, FCML_EOS_UNDEFINED ), FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FICOM[] = {
	// DE /2 FICOM m16int Valid Valid Compare ST(0) with m16int.
	{ NULL, FCML_AMT_FPU, 0x0000, 0x00C59000, { 0xDE, 0x00, 0x00 }, { FCML_OP_MODRM_M_16, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// DA /2 FICOM m32int Valid Valid Compare ST(0) with m32int.
	{ NULL, FCML_AMT_FPU, 0x0000, 0x00C59000, { 0xDA, 0x00, 0x00 }, { FCML_OP_MODRM_M_32, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// DE /3 FICOMP m16int Valid Valid Compare ST(0) with m16int and pop stack register.
	{ "ficomp", FCML_AMT_FPU, 0x0000, 0x00C59800, { 0xDE, 0x00, 0x00 }, { FCML_OP_MODRM_M_16, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// DA /3 FICOMP m32int Valid Valid Compare ST(0) with m32int and pop stack register.
	{ "ficomp", FCML_AMT_FPU, 0x0000, 0x00C59800, { 0xDA, 0x00, 0x00 }, { FCML_OP_MODRM_M_32, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FILD[] = {
	// DF /0 FILD m16int Valid Valid Push m16int onto the FPU register stack.
	{ NULL, FCML_AMT_FPU, 0x0000, 0x00C58000, { 0xDF, 0x00, 0x00 }, { FCML_OP_MODRM_M_16, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// DB /0 FILD m32int Valid Valid Push m32int onto the FPU register stack.
	{ NULL, FCML_AMT_FPU, 0x0000, 0x00C58000, { 0xDB, 0x00, 0x00 }, { FCML_OP_MODRM_M_32, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// DF /5 FILD m64int Valid Valid Push m64int onto the FPU register stack.
	{ NULL, FCML_AMT_FPU, 0x0000, 0x00C5A800, { 0xDF, 0x00, 0x00 }, { FCML_OP_MODRM_M_64, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FINCSTP[] = {
	// D9 F7 FINCSTP Valid Valid Increment the TOP field in the FPU status register.
	{ NULL, FCML_AMT_FPU, 0x0000, 0x00D80000, { 0xD9, 0xF7, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FINIT[] = {
	// 9B DB E3 FINIT Valid Valid Initialize FPU after checking for pending unmasked floating-point exceptions.
	{ NULL, FCML_AMT_FPU, 0x0000, 0x00EC0000, { 0x9B, 0xDB, 0xE3 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// DB E3 FNINIT* Valid Valid Initialize FPU without checking for pending unmasked floating-point exceptions.
	{ "fninit", FCML_AMT_FPU, 0x0000, 0x00D80000, { 0xDB, 0xE3, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FIST[] = {
	// DF /2 FIST m16int Valid Valid Store ST(0) in m16int.
	{ NULL, FCML_AMT_FPU, 0x0000, 0x00C59000, { 0xDF, 0x00, 0x00 }, { FCML_OP_MODRM_M_16, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// DB /2 FIST m32int Valid Valid Store ST(0) in m32int.
	{ NULL, FCML_AMT_FPU, 0x0000, 0x00C59000, { 0xDB, 0x00, 0x00 }, { FCML_OP_MODRM_M_32, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// DF /3 FISTP m16int Valid Valid Store ST(0) in m16int and pop register stack.
	{ "fistp", FCML_AMT_FPU, 0x0000, 0x00C59800, { 0xDF, 0x00, 0x00 }, { FCML_OP_MODRM_M_16, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// DB /3 FISTP m32int Valid Valid Store ST(0) in m32int and pop register stack.
	{ "fistp", FCML_AMT_FPU, 0x0000, 0x00C59800, { 0xDB, 0x00, 0x00 }, { FCML_OP_MODRM_M_32, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// DF /7 FISTP m64int Valid Valid Store ST(0) in m64int and pop register stack.
	{ "fistp", FCML_AMT_FPU, 0x0000, 0x00C5B800, { 0xDF, 0x00, 0x00 }, { FCML_OP_MODRM_M_64, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FISTTP[] = {
	// DF /1 FISTTP m16int Valid Valid Store ST(0) in m16int with truncation.
	{ NULL, FCML_AMT_SSE3 | FCML_AMT_FPU, 0x0000, 0x00C58800, { 0xDF, 0x00, 0x00 }, { FCML_OP_MODRM_M_16, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// DB /1 FISTTP m32int Valid Valid Store ST(0) in m32int with truncation.
	{ NULL, FCML_AMT_SSE3 | FCML_AMT_FPU, 0x0000, 0x00C58800, { 0xDB, 0x00, 0x00 }, { FCML_OP_MODRM_M_32, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// DD /1 FISTTP m64int Valid Valid Store ST(0) in m64int with truncation.
	{ NULL, FCML_AMT_SSE3 | FCML_AMT_FPU, 0x0000, 0x00C58800, { 0xDD, 0x00, 0x00 }, { FCML_OP_MODRM_M_64, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FLD[] = {
	// D9 /0 FLD m32fp Valid Valid Push m32fp onto the FPU register stack.
	{ NULL, FCML_AMT_FPU, 0x0000, 0x00C58000, { 0xD9, 0x00, 0x00 }, { FCML_OP_MODRM_M_32, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// DD /0 FLD m64fp Valid Valid Push m64fp onto the FPU register stack.
	{ NULL, FCML_AMT_FPU, 0x0000, 0x00C58000, { 0xDD, 0x00, 0x00 }, { FCML_OP_MODRM_M_64, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// DB /5 FLD m80fp Valid Valid Push m80fp onto the FPU register stack.
	{ NULL, FCML_AMT_FPU, 0x0000, 0x00C5A800, { 0xDB, 0x00, 0x00 }, { FCML_OP_MODRM_M_80, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// D9 C0+i FLD ST(i) Valid Valid Push ST(i) onto the FPU register stack.
	{ NULL, FCML_AMT_FPU, 0x0000, 0x00D80001, { 0xD9, 0xC0, 0x00 }, { FCML_OP_OPCODE_REG( FCML_REG_FPU, FCML_EOS_UNDEFINED ), FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FLDx[] = {
	// D9 E8 FLD1 Valid Valid Push +1.0 onto the FPU register stack.
	{ "fld1", FCML_AMT_FPU, 0x0000, 0x00D80000, { 0xD9, 0xE8, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// D9 E9 FLDL2T Valid Valid Push log210 onto the FPU register stack.
	{ "fldl2t", FCML_AMT_FPU, 0x0000, 0x00D80000, { 0xD9, 0xE9, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// D9 EA FLDL2E Valid Valid Push log2e onto the FPU register stack.
	{ "fldl2e", FCML_AMT_FPU, 0x0000, 0x00D80000, { 0xD9, 0xEA, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// D9 EB FLDPI Valid Valid Push onto the FPU register stack.
	{ "fldpi", FCML_AMT_FPU, 0x0000, 0x00D80000, { 0xD9, 0xEB, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// D9 EC FLDLG2 Valid Valid Push log102 onto the FPU register stack.
	{ "fldlg2", FCML_AMT_FPU, 0x0000, 0x00D80000, { 0xD9, 0xEC, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// D9 ED FLDLN2 Valid Valid Push loge2 onto the FPU register stack.
	{ "fldln2", FCML_AMT_FPU, 0x0000, 0x00D80000, { 0xD9, 0xED, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// D9 EE FLDZ Valid Valid Push +0.0 onto the FPU register stack.
	{ "fldz", FCML_AMT_FPU, 0x0000, 0x00D80000, { 0xD9, 0xEE, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FLDCW[] = {
	// D9 /5 FLDCW m2byte Valid Valid Load FPU control word from m2byte.
	{ NULL, FCML_AMT_FPU, 0x0000, 0x00C5A800, { 0xD9, 0x00, 0x00 }, { FCML_OP_MODRM_M_16, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FLDENV[] = {
	// D9 /4 FLDENV m14/28byte Valid Valid Load FPU environment from m14byte or m28byte.
	{ NULL, FCML_AMT_FPU, 0x0000, 0x00C5A000, { 0xD9, 0x00, 0x00 }, { FCML_OP_MODRM_M_14_28, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FMUL[] = {
	// D8 /1 FMUL m32fp Valid Valid Multiply ST(0) by m32fp and store result in ST(0).
	{ NULL, FCML_AMT_FPU, 0x0000, 0x00C58800, { 0xD8, 0x00, 0x00 }, { FCML_OP_MODRM_M_32, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// DC /1 FMUL m64fp Valid Valid Multiply ST(0) by m64fp and store result in ST(0).
	{ NULL, FCML_AMT_FPU, 0x0000, 0x00C58800, { 0xDC, 0x00, 0x00 }, { FCML_OP_MODRM_M_64, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// D8 C8+i FMUL ST(0), ST(i) Valid Valid Multiply ST(0) by ST(i) and store result in ST(0).
	{ NULL, FCML_AMT_FPU, 0x0000, 0x00D80001, { 0xD8, 0xC8, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_FPU, FCML_REG_ST0, FCML_EOS_UNDEFINED ), FCML_OP_OPCODE_REG( FCML_REG_FPU, FCML_EOS_UNDEFINED ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// DC C8+i FMUL ST(i), ST(0) Valid Valid Multiply ST(i) by ST(0) and store result in ST(i).
	{ NULL, FCML_AMT_FPU, 0x0000, 0x00D80001, { 0xDC, 0xC8, 0x00 }, { FCML_OP_OPCODE_REG( FCML_REG_FPU, FCML_EOS_UNDEFINED ), FCML_OP_EXPLICIT_REG( FCML_REG_FPU, FCML_REG_ST0, FCML_EOS_UNDEFINED ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// DE C8+i FMULP ST(i), ST(0) Valid Valid Multiply ST(i) by ST(0), store result in ST(i), and pop the register stack.
	{ "fmulp", FCML_AMT_FPU, 0x0000, 0x00D80001, { 0xDE, 0xC8, 0x00 }, { FCML_OP_OPCODE_REG( FCML_REG_FPU, FCML_EOS_UNDEFINED ), FCML_OP_EXPLICIT_REG( FCML_REG_FPU, FCML_REG_ST0, FCML_EOS_UNDEFINED ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// DA /1 FIMUL m32int Valid Valid Multiply ST(0) by m32int and store result in ST(0).
	{ "fimul", FCML_AMT_FPU, 0x0000, 0x00C58800, { 0xDA, 0x00, 0x00 }, { FCML_OP_MODRM_M_32, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// DE /1 FIMUL m16int Valid Valid Multiply ST(0) by m16int and store result in ST(0).
	{ "fimul", FCML_AMT_FPU, 0x0000, 0x00C58800, { 0xDE, 0x00, 0x00 }, { FCML_OP_MODRM_M_16, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// DE C9 FMULP
	{ "fmulp", FCML_AMT_FPU, 0x0000, 0x00D80000, { 0xDE, 0xC9, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FNOP[] = {
	// D9 D0 FNOP Valid Valid No operation is performed.
	{ NULL, FCML_AMT_FPU, 0x0000, 0x00D80000, { 0xD9, 0xD0, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FPATAN[] = {
	// D9 F3 FPATAN Valid Valid Replace ST(1) with arctan(ST(1) ST(0)) and pop the register stack.
	{ NULL, FCML_AMT_FPU, 0x0000, 0x00D80000, { 0xD9, 0xF3, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FPREM[] = {
	// D9 F8 FPREM Valid Valid Replace ST(0) with the remainder obtained from dividing ST(0) by ST(1).
	{ NULL, FCML_AMT_FPU, 0x0000, 0x00D80000, { 0xD9, 0xF8, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FPREM1[] = {
	// D9 F5 FPREM1 Valid Valid Replace ST(0) with the IEEE remainder obtained from dividing ST(0) by ST(1).
	{ NULL, FCML_AMT_FPU, 0x0000, 0x00D80000, { 0xD9, 0xF5, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FPTAN[] = {
	// D9 F2 FPTAN Valid Valid Replace ST(0) with its tangent and push 1 onto the FPU stack.
	{ NULL, FCML_AMT_FPU, 0x0000, 0x00D80000, { 0xD9, 0xF2, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FRNDINT[] = {
	// D9 FC FRNDINT Valid Valid Round ST(0) to an integer.
	{ NULL, FCML_AMT_FPU, 0x0000, 0x00D80000, { 0xD9, 0xFC, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FRSTOR[] = {
	// DD /4 FRSTOR m94/108byte Valid Valid Load FPU state from m94byte or m108byte.
	{ NULL, FCML_AMT_FPU, 0x0000, 0x00C5A000, { 0xDD, 0x00, 0x00 }, { FCML_OP_MODRM_M_94_108, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FSAVE[] = {
	// 9B DD /6 FSAVE m94/108byte Valid Valid Store FPU state to m94byte or m108byte after checking for pending unmasked floatingpoint exceptions. Then reinitialize the FPU.
	{ NULL, FCML_AMT_FPU, 0x0000, 0x00D9B000, { 0x9B, 0xDD, 0x00 }, { FCML_OP_MODRM_M_94_108, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// DD /6 FNSAVE* m94/108byte Valid Valid Store FPU environment to m94byte or m108byte without checking for pending unmasked floating-point exceptions.
	{ "fnsave", FCML_AMT_FPU, 0x0000, 0x00C5B000, { 0xDD, 0x00, 0x00 }, { FCML_OP_MODRM_M_94_108, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FSCALE[] = {
	// D9 FD FSCALE Valid Valid Scale ST(0) by ST(1).
	{ NULL, FCML_AMT_FPU, 0x0000, 0x00D80000, { 0xD9, 0xFD, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FSIN[] = {
	// D9 FE FSIN Valid Valid Replace ST(0) with its sine.
	{ NULL, FCML_AMT_FPU, 0x0000, 0x00D80000, { 0xD9, 0xFE, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FSINCOS[] = {
	// D9 FB FSINCOS Valid Valid Compute the sine and cosine of ST(0); replace ST(0) with the sine, and push the cosine onto the register stack.
	{ NULL, FCML_AMT_FPU, 0x0000, 0x00D80000, { 0xD9, 0xFB, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FSQRT[] = {
	// D9 FA FSQRT Valid Valid Computes square root of ST(0) and stores the result in ST(0).
	{ NULL, FCML_AMT_FPU, 0x0000, 0x00D80000, { 0xD9, 0xFA, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FST[] = {
	// D9 /2 FST m32fp Valid Valid Copy ST(0) to m32fp.
	{ NULL, FCML_AMT_FPU, 0x0000, 0x00C59000, { 0xD9, 0x00, 0x00 }, { FCML_OP_MODRM_M_32, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// DD /2 FST m64fp Valid Valid Copy ST(0) to m64fp.
	{ NULL, FCML_AMT_FPU, 0x0000, 0x00C59000, { 0xDD, 0x00, 0x00 }, { FCML_OP_MODRM_M_64, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// DD D0+i FST ST(i) Valid Valid Copy ST(0) to ST(i).
	{ NULL, FCML_AMT_FPU, 0x0000, 0x00D80001, { 0xDD, 0xD0, 0x00 }, { FCML_OP_OPCODE_REG( FCML_REG_FPU, FCML_EOS_UNDEFINED ), FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// D9 /3 FSTP m32fp Valid Valid Copy ST(0) to m32fp and pop register stack.
	{ "fstp", FCML_AMT_FPU, 0x0000, 0x00C59800, { 0xD9, 0x00, 0x00 }, { FCML_OP_MODRM_M_32, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// DD /3 FSTP m64fp Valid Valid Copy ST(0) to m64fp and pop register stack.
	{ "fstp", FCML_AMT_FPU, 0x0000, 0x00C59800, { 0xDD, 0x00, 0x00 }, { FCML_OP_MODRM_M_64, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// DB /7 FSTP m80fp Valid Valid Copy ST(0) to m80fp and pop register stack.
	{ "fstp", FCML_AMT_FPU, 0x0000, 0x00C5B800, { 0xDB, 0x00, 0x00 }, { FCML_OP_MODRM_M_80, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// DD D8+i FSTP ST(i) Valid Valid Copy ST(0) to ST(i) and pop register stack.
	{ "fstp", FCML_AMT_FPU, 0x0000, 0x00D80001, { 0xDD, 0xD8, 0x00 }, { FCML_OP_OPCODE_REG( FCML_REG_FPU, FCML_EOS_UNDEFINED ), FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FSTCW[] = {
	// 9B D9 /7 FSTCW m2byte Valid Valid Store FPU control word to m2byte after checking for pending unmasked floating-point exceptions.
	{ NULL, FCML_AMT_FPU, 0x0000, 0x00D9B800, { 0x9B, 0xD9, 0x00 }, { FCML_OP_MODRM_M_16_W, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// D9 /7 FNSTCW* m2byte Valid Valid Store FPU control word to m2byte without checking for pending unmasked floating-point exceptions.
	{ "fnstcw", FCML_AMT_FPU, 0x0000, 0x00C5B800, { 0xD9, 0x00, 0x00 }, { FCML_OP_MODRM_M_16_W, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FSTENV[] = {
	// 9B D9 /6 FSTENV m14/28byte Valid Valid Store FPU environment to m14byte or m28byte after checking for pending unmasked floating-point exceptions. Then mask all floatingpoint exceptions.
	{ NULL, FCML_AMT_FPU, 0x0000, 0x00D9B000, { 0x9B, 0xD9, 0x00 }, { FCML_OP_MODRM_M_14_28_W, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// D9 /6 FNSTENV* m14/28byte Valid Valid Store FPU environment to m14byte or m28byte without checking for pending unmasked floating-point exceptions. Then mask all floatingpoint exceptions.
	{ "fnstenv", FCML_AMT_FPU, 0x0000, 0x00C5B000, { 0xD9, 0x00, 0x00 }, { FCML_OP_MODRM_M_14_28_W, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FSTSW[] = {
	// 9B DD /7 FSTSW m2byte Valid Valid Store FPU status word at m2byte after checking for pending unmasked floatingpoint exceptions.
	{ NULL, FCML_AMT_FPU, 0x0000, 0x00D9B800, { 0x9B, 0xDD, 0x00 }, { FCML_OP_MODRM_M_16_W, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 9B DF E0 FSTSW AX Valid Valid Store FPU status word in AX register after checking for pending unmasked floatingpoint exceptions.
	{ NULL, FCML_AMT_FPU, 0x0000, 0x00EC0000, { 0x9B, 0xDF, 0xE0 }, { FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_AX, FCML_EOS_WORD ), FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// DD /7 FNSTSW* m2byte Valid Valid Store FPU status word at m2byte without checking for pending unmasked floatingpoint exceptions.
	{ "fnstsw", FCML_AMT_FPU, 0x0000, 0x00C5B800, { 0xDD, 0x00, 0x00 }, { FCML_OP_MODRM_M_16_W, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// DF E0 FNSTSW* AX Valid Valid Store FPU status word in AX register without checking for pending unmasked floatingpoint exceptions.
	{ "fnstsw", FCML_AMT_FPU, 0x0000, 0x00D80000, { 0xDF, 0xE0, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_AX, FCML_EOS_WORD ), FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FSUB[] = {
	// D8 /4 FSUB m32fp Valid Valid Subtract m32fp from ST(0) and store result in ST(0).
	{ NULL, FCML_AMT_FPU, 0x0000, 0x00C5A000, { 0xD8, 0x00, 0x00 }, { FCML_OP_MODRM_M_32, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// DC /4 FSUB m64fp Valid Valid Subtract m64fp from ST(0) and store result in ST(0).
	{ NULL, FCML_AMT_FPU, 0x0000, 0x00C5A000, { 0xDC, 0x00, 0x00 }, { FCML_OP_MODRM_M_64, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// D8 E0+i FSUB ST(0), ST(i) Valid Valid Subtract ST(i) from ST(0) and store result in ST(0).
	{ NULL, FCML_AMT_FPU, 0x0000, 0x00D80001, { 0xD8, 0xE0, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_FPU, FCML_REG_ST0, FCML_EOS_UNDEFINED ), FCML_OP_OPCODE_REG( FCML_REG_FPU, FCML_EOS_UNDEFINED ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// DC E8+i FSUB ST(i), ST(0) Valid Valid Subtract ST(0) from ST(i) and store result in ST(i).
	{ NULL, FCML_AMT_FPU, 0x0000, 0x00D80001, { 0xDC, 0xE8, 0x00 }, { FCML_OP_OPCODE_REG( FCML_REG_FPU, FCML_EOS_UNDEFINED ), FCML_OP_EXPLICIT_REG( FCML_REG_FPU, FCML_REG_ST0, FCML_EOS_UNDEFINED ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// DE E8+i FSUBP ST(i), ST(0) Valid Valid Subtract ST(0) from ST(i), store result in ST(i), and pop register stack.
	{ "fsubp", FCML_AMT_FPU, 0x0000, 0x00D80001, { 0xDE, 0xE8, 0x00 }, { FCML_OP_OPCODE_REG( FCML_REG_FPU, FCML_EOS_UNDEFINED ), FCML_OP_EXPLICIT_REG( FCML_REG_FPU, FCML_REG_ST0, FCML_EOS_UNDEFINED ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// DA /4 FISUB m32int Valid Valid Subtract m32int from ST(0) and store result in ST(0).
	{ "fisub", FCML_AMT_FPU, 0x0000, 0x00C5A000, { 0xDA, 0x00, 0x00 }, { FCML_OP_MODRM_M_32, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// DE /4 FISUB m16int Valid Valid Subtract m16int from ST(0) and store result in ST(0).
	{ "fisub", FCML_AMT_FPU, 0x0000, 0x00C5A000, { 0xDE, 0x00, 0x00 }, { FCML_OP_MODRM_M_16, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// DE E9 FSUBP
	{ "fsubp", FCML_AMT_FPU, 0x0000, 0x00D80000, { 0xDE, 0xE9, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FSUBR[] = {
	// D8 /5 FSUBR m32fp Valid Valid Subtract ST(0) from m32fp and store result in ST(0).
	{ NULL, FCML_AMT_FPU, 0x0000, 0x00C5A800, { 0xD8, 0x00, 0x00 }, { FCML_OP_MODRM_M_32, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// DC /5 FSUBR m64fp Valid Valid Subtract ST(0) from m64fp and store result in ST(0).
	{ NULL, FCML_AMT_FPU, 0x0000, 0x00C5A800, { 0xDC, 0x00, 0x00 }, { FCML_OP_MODRM_M_64, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// D8 E8+i FSUBR ST(0), ST(i) Valid Valid Subtract ST(0) from ST(i) and store result in ST(0).
	{ NULL, FCML_AMT_FPU, 0x0000, 0x00D80001, { 0xD8, 0xE8, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_FPU, FCML_REG_ST0, FCML_EOS_UNDEFINED ), FCML_OP_OPCODE_REG( FCML_REG_FPU, FCML_EOS_UNDEFINED ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// DC E0+i FSUBR ST(i), ST(0) Valid Valid Subtract ST(i) from ST(0) and store result in ST(i).
	{ NULL, FCML_AMT_FPU, 0x0000, 0x00D80001, { 0xDC, 0xE0, 0x00 }, { FCML_OP_OPCODE_REG( FCML_REG_FPU, FCML_EOS_UNDEFINED ), FCML_OP_EXPLICIT_REG( FCML_REG_FPU, FCML_REG_ST0, FCML_EOS_UNDEFINED ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// DE E0+i FSUBRP ST(i), ST(0) Valid Valid Subtract ST(i) from ST(0), store result in ST(i), and pop register stack.
	{ "fsubrp", FCML_AMT_FPU, 0x0000, 0x00D80001, { 0xDE, 0xE0, 0x00 }, { FCML_OP_OPCODE_REG( FCML_REG_FPU, FCML_EOS_UNDEFINED ), FCML_OP_EXPLICIT_REG( FCML_REG_FPU, FCML_REG_ST0, FCML_EOS_UNDEFINED ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// DA /5 FISUBR m32int Valid Valid Subtract ST(0) from m32int and store result in ST(0).
	{ "fisubr", FCML_AMT_FPU, 0x0000, 0x00C5A800, { 0xDA, 0x00, 0x00 }, { FCML_OP_MODRM_M_32, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// DE /5 FISUBR m16int Valid Valid Subtract ST(0) from m16int and store result in ST(0).
	{ "fisubr", FCML_AMT_FPU, 0x0000, 0x00C5A800, { 0xDE, 0x00, 0x00 }, { FCML_OP_MODRM_M_16, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// DE E1 FSUBRP
	{ "fsubrp", FCML_AMT_FPU, 0x0000, 0x00D80000, { 0xDE, 0xE1, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FTST[] = {
	// D9 E4 FTST Valid Valid Compare ST(0) with 0.0.
	{ NULL, FCML_AMT_FPU, 0x0000, 0x00D80000, { 0xD9, 0xE4, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FUCOM[] = {
	// DD E0+i FUCOM ST(i) Valid Valid Compare ST(0) with ST(i).
	{ NULL, FCML_AMT_FPU, 0x0000, 0x00D80001, { 0xDD, 0xE0, 0x00 }, { FCML_OP_OPCODE_REG( FCML_REG_FPU, FCML_EOS_UNDEFINED ), FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// DD E8+i FUCOMP ST(i) Valid Valid Compare ST(0) with ST(i) and pop register stack.
	{ "fucomp", FCML_AMT_FPU, 0x0000, 0x00D80001, { 0xDD, 0xE8, 0x00 }, { FCML_OP_OPCODE_REG( FCML_REG_FPU, FCML_EOS_UNDEFINED ), FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// DA E9 FUCOMPP Valid Valid Compare ST(0) with ST(1) and pop register stack twice.
	{ "fucompp", FCML_AMT_FPU, 0x0000, 0x00D80000, { 0xDA, 0xE9, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// DD E1 FUCOM
	{ "fucom", FCML_AMT_FPU, 0x0000, 0x00D80000, { 0xDD, 0xE1, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// DD E9 FUCOMP
	{ "fucomp", FCML_AMT_FPU, 0x0000, 0x00D80000, { 0xDD, 0xE9, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FXAM[] = {
	// D9 E5 FXAM Valid Valid Classify value or number in ST(0).
	{ NULL, FCML_AMT_FPU, 0x0000, 0x00D80000, { 0xD9, 0xE5, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FXCH[] = {
	// D9 C8+i FXCH ST(i) Valid Valid Exchange the contents of ST(0) and ST(i).
	{ NULL, FCML_AMT_FPU, 0x0000, 0x00D80001, { 0xD9, 0xC8, 0x00 }, { FCML_OP_OPCODE_REG( FCML_REG_FPU, FCML_EOS_UNDEFINED ), FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// D9 C9 FXCH
	{ NULL, FCML_AMT_FPU, 0x0000, 0x00D80000, { 0xD9, 0xC9, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FXRSTOR[] = {
	// 0F AE /1 FXRSTOR m512byte A Valid Valid Restore the x87 FPU, MMX, XMM, and MXCSR register state from m512byte.
	{ NULL, FCML_AMT_SIMD | FCML_AMT_FPU, 0x0000, 0x83D98800, { 0x0F, 0xAE, 0x00 }, { FCML_OP_MODRM_M_512B, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// REX.W+ 0F AE /1 FXRSTOR64 m512byte A Valid N.E. Restore the x87 FPU, MMX, XMM, and MXCSR register state from m512byte.
	{ "fxrstor64", FCML_AMT_SIMD | FCML_AMT_FPU, 0x0008, 0x84998800, { 0x0F, 0xAE, 0x00 }, { FCML_OP_MODRM_M_512B, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FXSAVE[] = {
	// 0F AE /0 FXSAVE m512byte A Valid Valid Save the x87 FPU, MMX, XMM, and MXCSR register state to m512byte.
	{ NULL, FCML_AMT_SIMD | FCML_AMT_FPU, 0x0000, 0x83D98000, { 0x0F, 0xAE, 0x00 }, { FCML_OP_MODRM_M_512B, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// REX.W+ 0F AE /0 FXSAVE64 m512byte A Valid N.E. Save the x87 FPU, MMX, XMM, and MXCSR register state to m512byte.
	{ "fxsave64", FCML_AMT_SIMD | FCML_AMT_FPU, 0x0008, 0x84998000, { 0x0F, 0xAE, 0x00 }, { FCML_OP_MODRM_M_512B, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FXTRACT[] = {
	// D9 F4 FXTRACT Valid Valid Separate value in ST(0) into exponent and significand, store exponent in ST(0), and push the significand onto the register stack.
	{ NULL, FCML_AMT_FPU, 0x0000, 0x00D80000, { 0xD9, 0xF4, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FYL2X[] = {
	// D9 F1 FYL2X Valid Valid Replace ST(1) with (ST(1) log2ST(0)) and pop the register stack.
	{ NULL, FCML_AMT_FPU, 0x0000, 0x00D80000, { 0xD9, 0xF1, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FYL2XP1[] = {
	// D9 F9 FYL2XP1 Valid Valid Replace ST(1) with ST(1) log2(ST(0) + 1.0) and pop the register stack.
	{ NULL, FCML_AMT_FPU, 0x0000, 0x00D80000, { 0xD9, 0xF9, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_GETSEC[] = {
    // 0F 37  GETSEC[X] Report the SMX capabilities.
    { NULL, FCML_AMT_SMX, 0x0000, 0x00D80000, { 0x0F, 0x37, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_HADDPD[] = {
	// 66 0F 7C /r HADDPD xmm1, xmm2/m128 A Valid Valid Horizontal add packed double-precision floatingpoint values from xmm2/m128 to xmm1.
	{ NULL, FCML_AMT_SSE3_SIMD, 0x1001, 0x00D88000, { 0x0F, 0x7C, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.66.0F 7C /r VHADDPD xmm1,xmm2,xmm3/m128
	// VEX.NDS.256.66.0F 7C /r VHADDPD ymm1,ymm2,ymm3/m256
	{ "vhaddpd", FCML_AMT_AVX_SIMD, 0x1080, 0x00D88000, { 0x0F, 0x7C, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_HADDPS[] = {
	// F2 0F 7C /r HADDPS xmm1, xmm2/m128 A Valid Valid Horizontal add packed single-precision floatingpoint values from xmm2/m128 to xmm1.
	{ NULL, FCML_AMT_SSE3_SIMD, 0x2001, 0x00D88000, { 0x0F, 0x7C, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.F2.0F 7C /r VHADDPS xmm1,xmm2,xmm3/m128
	// VEX.NDS.256.F2.0F 7C /r VHADDPS ymm1,ymm2,ymm3/m256
	{ "vhaddps", FCML_AMT_AVX_SIMD, 0x2080, 0x00D88000, { 0x0F, 0x7C, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_HLT[] = {
	// F4 HLT A Valid Valid Halt
	{ NULL, FCML_AMT_SYSTEM, 0x0000, 0x00C40000, { 0xF4, 0x00, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_HSUBPD[] = {
	// 66 0F 7D /r HSUBPD xmm1, xmm2/m128A Valid Valid Horizontal subtract packed double-precision floating pointvalues from xmm2/m128 to xmm1.
	{ NULL, FCML_AMT_SSE3_SIMD, 0x1001, 0x00D88000, { 0x0F, 0x7D, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.66.0F 7D /r VHSUBPD xmm1,xmm2,xmm3/m128
	// VEX.NDS.256.66.0F 7D /r VHSUBPD ymm1,ymm2,ymm3/m256
	{ "vhsubpd", FCML_AMT_AVX_SIMD, 0x1080, 0x00D88000, { 0x0F, 0x7D, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_HSUBPS[] = {
	// F2 0F 7D /r HSUBPS xmm1, xmm2/m128 A Valid Valid Horizontal subtract packedsingle-precision floatingpoint values from xmm2/m128 to xmm1.
	{ NULL, FCML_AMT_SSE3_SIMD, 0x2001, 0x00D88000, { 0x0F, 0x7D, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.F2.0F 7D /r VHSUBPS xmm1,xmm2,xmm3/m128
	// VEX.NDS.256.F2.0F 7D /r VHSUBPS ymm1,ymm2,ymm3/m256
	{ "vhsubps", FCML_AMT_AVX_SIMD, 0x2080, 0x00D88000, { 0x0F, 0x7D, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_INVEPT[] = {
    // 66 0F 38 80 INVEPT r64, m128 Invalidates EPT-derived entries in the TLBs and paging-structure caches (in 64-bit mode)
    // 66 0F 38 80 INVEPT r32, m128 Invalidates EPT-derived entries in the TLBs and paging-structure caches (outside 64-bit mode)
    { NULL, FCML_AMT_VMX, 0x1000, 0x806C8000, { 0x0F, 0x38, 0x80 }, { FCML_OP_MODRM_R_32, FCML_OP_MODRM_RM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
    { NULL, FCML_AMT_VMX, 0x1000, 0x80AC8000, { 0x0F, 0x38, 0x80 }, { FCML_OP_MODRM_R_64, FCML_OP_MODRM_RM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_INVVPID[] = {
    // 66 0F 38 81 INVVPID r64, m128 Invalidates entries in the TLBs and paging-structure caches based on VPID (in 64-bit mode)
    // 66 0F 38 81 INVVPID r32, m128 Invalidates entries in the TLBs and paging-structure caches based on VPID (outside 64-bit mode)
    { NULL, FCML_AMT_VMX, 0x1000, 0x806C8000, { 0x0F, 0x38, 0x81 }, { FCML_OP_MODRM_R_32, FCML_OP_MODRM_RM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
    { NULL, FCML_AMT_VMX, 0x1000, 0x80AC8000, { 0x0F, 0x38, 0x81 }, { FCML_OP_MODRM_R_64, FCML_OP_MODRM_RM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_IDIV[] = {
	// F6 /7 IDIV r/m8 A Valid Valid Signed divide AX by r/m8,with result stored in: AL Quotient, AH Remainder.
	// REX + F6 /7 IDIV r/m8* A Valid N.E. Signed divide AX by r/m8, with result stored in AL Quotient, AH Remainder.
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00C5B800, { 0xF6, 0x00, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_AX, FCML_EOS_WORD ), FCML_OP_MODRM_RM_8_W, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// F7 /7 IDIV r/m16 A Valid Valid Signed divide DX:AX by r/m16, with result stored in AX Quotient, DX Remainder.
	// F7 /7 IDIV r/m32 A Valid Valid Signed divide EDX:EAX by r/m32, with result stored in EAX Quotient, EDX Remainder.
	// REX.W + F7 /7 IDIV r/m64 A Valid N.E. Signed divide RDX:RAX by r/m64, with result stored in RAX Quotient, RDX Remainder.
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00C5B800, { 0xF7, 0x00, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_AL, FCML_EOS_EOSA ), FCML_OP_MODRM_RM_W, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

// ***********************************
// TODO: RWX(W) is not used from here!
// ***********************************

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_IMUL[] = {
	// F6 /5 IMUL r/m8* A Valid Valid AX AL r/m byte.
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00C5A800, { 0xF6, 0x00, 0x00 }, { FCML_OP_MODRM_RM_8_W, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// F7 /5 IMUL r/m16 A Valid Valid DX:AX AX r/m word.
	// F7 /5 IMUL r/m32 A Valid Valid EDX:EAX EAX r/m32.
	// REX.W + F7 /5 IMUL r/m64 A Valid N.E. RDX:RAX RAX r/m64.
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00C5A800, { 0xF7, 0x00, 0x00 }, { FCML_OP_MODRM_RM_W, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 0F AF /r IMUL r16, r/m16 B Valid Valid word register word register r/m16.
	// 0F AF /r IMUL r32, r/m32 B Valid Valid doubleword register doubleword register r/m32.
	// REX.W + 0F AF /r IMUL r64, r/m64 B Valid N.E. Quadword register Quadword register r/m64.
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00D88000, { 0x0F, 0xAF, 0x00 }, { FCML_OP_MODRM_R_W, FCML_OP_MODRM_RM,  FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 6B /r ib IMUL r16, r/m16, imm8 C Valid Valid word register r/m16 sign-extended immediate byte.
	// 6B /r ib IMUL r32, r/m32, imm8 C Valid Valid doubleword register r/m32 sign-extended immediate byte.
	// REX.W + 6B /r ib IMUL r64, r/m64, imm8 C Valid N.E. Quadword register r/m64 sign-extended immediate byte.
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00C48000, { 0x6B, 0x00, 0x00 }, { FCML_OP_MODRM_R_W, FCML_OP_MODRM_RM, FCML_OP_IB_EX_EOSA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 69 /r iw IMUL r16, r/m16, imm16 C Valid Valid word register r/m16 immediate word.
	// 69 /r id IMUL r32, r/m32, imm32 C Valid Valid doubleword register r/m32 immediate doubleword.
	{ NULL, FCML_AMT_GPI, 0x0010, 0x03C48000, { 0x69, 0x00, 0x00 }, { FCML_OP_MODRM_R_W, FCML_OP_MODRM_RM, FCML_OP_IMM_EOSA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// REX.W + 69 /r id IMUL r64, r/m64, imm32 C Valid N.E. Quadword register r/m64 immediate doubleword.
	{ NULL, FCML_AMT_GPI, 0x0008, 0x04848000, { 0x69, 0x00, 0x00 }, { FCML_OP_MODRM_R_W, FCML_OP_MODRM_RM, FCML_OP_ID_EX_EOSA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_IN[] = {
	// E4 ib IN AL, imm8 A Valid Valid Input byte from imm8 I/O port address into AL.
	{ NULL, FCML_AMT_GPI, 0x0000, 0x07C40000, { 0xE4, 0x00, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_AL, FCML_EOS_BYTE ), FCML_OP_IB, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// E5 ib IN AX, imm8 A Valid Valid Input word from imm8 I/O port address into AX.
	{ NULL, FCML_AMT_GPI, 0x0000, 0x01C40000, { 0xE5, 0x00, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_AL, FCML_EOS_WORD), FCML_OP_IB, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// E5 ib IN EAX, imm8 A Valid Valid Input dword from imm8 I/O port address into EAX.
	{ NULL, FCML_AMT_GPI, 0x0000, 0x06C40000, { 0xE5, 0x00, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_AL, FCML_EOS_DWORD), FCML_OP_IB, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// EC IN AL,DX B Valid Valid Input byte from I/O port in DX into AL.
	{ NULL, FCML_AMT_GPI, 0x0000, 0x07C40000, { 0xEC, 0x00, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_AL, FCML_EOS_BYTE ), FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_DX, FCML_EOS_WORD ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// ED IN AX,DX B Valid Valid Input word from I/O port in DX into AX.
	{ NULL, FCML_AMT_GPI, 0x0000, 0x01C40000, { 0xED, 0x00, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_AL, FCML_EOS_WORD ), FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_DX, FCML_EOS_WORD ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// ED IN EAX,DX B Valid Valid Input doubleword from I/O port in DX into EAX.
	{ NULL, FCML_AMT_GPI, 0x0000, 0x06C40000, { 0xED, 0x00, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_AL, FCML_EOS_DWORD ), FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_DX, FCML_EOS_WORD ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_INC[] = {
	// FE /0 INC r/m8 A Valid Valid Increment r/m byte by 1.
	// REX + FE /0 INC r/m8* A Valid N.E. Increment r/m byte by 1.
	{ NULL, FCML_AMT_GPI, 0x0807, 0x00C58000, { 0xFE, 0x00, 0x00 }, { FCML_OP_MODRM_RM_8_W, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// FF /0 INC r/m16 A Valid Valid Increment r/m word by 1.
	// FF /0 INC r/m32 A Valid Valid Increment r/m doubleword by 1.
	// REX.W + FF /0 INC r/m64 A Valid N.E. Increment r/m quadword by 1.
	{ NULL, FCML_AMT_GPI, 0x0807, 0x00C58000, { 0xFF, 0x00, 0x00 }, { FCML_OP_MODRM_RM_W, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 40+ rw** INC r16 B N.E. Valid Increment word register by 1.
	// 40+ rd INC r32 B N.E. Valid Increment doubleword register by 1.
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00440001, { 0x40, 0x00, 0x00 }, { FCML_OP_OPCODE_REG( FCML_REG_GPR, FCML_EOS_EOSA ), FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_INS[] = {
	// 6C INS m8, DX A Valid Valid Input byte from I/O port specified in DX into memory location specified in ES:(E)DI or RDI.*
	{ "ins;insb[ts]", FCML_AMT_GPI, 0x0004, 0x07C40000, { 0x6C, 0x00, 0x00 },
			{ FCML_OP_EXPLICIT_GPS_REG_ADDRESSING( FCML_REG_DI, FCML_EOS_BYTE, FCML_SEG_ENCODE_REGISTER( FCML_REG_ES, FCML_SEG_DENY_OVERRIDE ) ),
			FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_DX, FCML_EOS_WORD ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 6D INS m16, DX A Valid Valid Input word from I/O port specified in DX into memory location specified in ES:(E)DI or RDI.1
	{ "ins;insw[ts]", FCML_AMT_GPI, 0x0004, 0x01C40000, { 0x6D, 0x00, 0x00 },
			{ FCML_OP_EXPLICIT_GPS_REG_ADDRESSING( FCML_REG_DI, FCML_EOS_WORD, FCML_SEG_ENCODE_REGISTER( FCML_REG_ES, FCML_SEG_DENY_OVERRIDE ) ),
			FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_DX, FCML_EOS_WORD ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 6D INS m32, DX A Valid Valid Input doubleword from I/O port specified in DX into memory location specified in ES:(E)DI or RDI.1
	{ "ins;insd[ts]", FCML_AMT_GPI, 0x0004, 0x06C40000, { 0x6D, 0x00, 0x00 },
			{ FCML_OP_EXPLICIT_GPS_REG_ADDRESSING( FCML_REG_DI, FCML_EOS_DWORD, FCML_SEG_ENCODE_REGISTER( FCML_REG_ES, FCML_SEG_DENY_OVERRIDE ) ),
			FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_DX, FCML_EOS_WORD ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_INSERTPS[] = {
	// 66 0F 3A 21 /r ib INSERTPS xmm1, xmm2/m32, imm8 A Valid Valid Insert a single precision floating-point value selected by imm8 from xmm2/m32 into xmm1 at the specified destination element specified by imm8 and zero out destination elements in xmm1 as indicated in imm8.
	{ NULL, FCML_AMT_SSE41_SIMD, 0x1001, 0x00EC8000, { 0x0F, 0x3A, 0x021 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_32, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.66.0F3A 21 /r ib VINSERTPS xmm1,xmm2,xmm3/m32,imm8
	{ "vinsertps", FCML_AMT_AVX_SIMD, 0x10C0, 0x00EC8000, { 0x0F, 0x3A, 0x21 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_32, FCML_OP_IB, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_INSERTQ[] = {
	// INSERTQ xmm1, xmm2, imm8, imm8 F2 0F 78 /r ib ib
	{ NULL, FCML_AMT_SSE4A, 0x2000, 0x00DA8000, { 0x0F, 0x78, 0x00 }, { FCML_OP_MODRM_R_XMM, FCML_OP_RM( FCML_REG_SIMD, FCML_EOS_OWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_OP_IB, FCML_OP_IB, FCML_NA }, FCML_AM_NONE },
	// INSERTQ xmm1, xmm2 F2 0F 79 /r
	{ NULL, FCML_AMT_SSE4A, 0x2000, 0x00DA8000, { 0x0F, 0x79, 0x00 }, { FCML_OP_MODRM_R_XMM, FCML_OP_RM( FCML_REG_SIMD, FCML_EOS_OWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VINSERTF128[] = {
	// VEX.NDS.256.66.0F3A 18 /r ib VINSERTF128 ymm1,ymm2,xmm3/m128,imm8
	{ "vinsertf128", FCML_AMT_AVX_SIMD, 0x10A0, 0x00EC8000, { 0x0F, 0x3A, 0x18 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_128, FCML_OP_IB, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_INT[] = {
	// CC INT 3 A Valid Valid Interrupt 3trap to debugger.
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00C40000, { 0xCC, 0x00, 0x00 }, { FCML_OP_EXPLICIT_IB( 3 ), FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// CD ib INT imm8 B Valid Valid Interrupt vector number specified by immediate byte.
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00C40000, { 0xCD, 0x00, 0x00 }, { FCML_OP_IB, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// CE INTO A Invalid Valid Interrupt 4if overflow flag is 1.
	{ "into", FCML_AMT_GPI, 0x0000, 0x00C40000, { 0xCE, 0x00, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_INVD[] = {
	// 0F 08 INVD A Valid Valid Flush internal caches; initiate flushing of external caches.
	{ NULL, FCML_AMT_SYSTEM, 0x0000, 0x00D80000, { 0x0F, 0x08, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_INVLPG[] = {
	// 0F 01/7 INVLPG m A Valid Valid Invalidate TLB Entry for page that contains m.
	{ NULL, FCML_AMT_SYSTEM, 0x0000, 0x00D9B800, { 0x0F, 0x01, 0x00 }, { FCML_OP_MODRM_M_UNDEF, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_INVLPGA[] = {
	// INVLPGA rAX, ECX 0F 01 DF
	{ NULL, FCML_AMT_SVM, 0x0000, 0x00EC0000, { 0x0F, 0x01, 0xDF }, { FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_EAX, FCML_EOS_EASA ), FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_ECX, FCML_EOS_DWORD ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_INVPCID[] = {
	// 66 0F 38 82 /r INVPCID r32, m128 RM NE/V INVPCID Invalidates entries in the TLBs and paging-structure caches based on invalidation type in r32 and descriptor in m128.
	{ NULL, FCML_AMT_SYSTEM, 0x1001, 0x806C8000, { 0x0F, 0x38, 0x82 }, { FCML_OP_MODRM_R_32, FCML_OP_RM( FCML_REG_UNDEFINED, FCML_EOS_UNDEFINED, FCML_EOS_OWORD, FCML_RMF_M ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 66 0F 38 82 /r INVPCID r64, m128 RM V/NE INVPCID Invalidates entries in the TLBs and paging-structure caches based on invalidation type in r64 and descriptor in m128.
	{ NULL, FCML_AMT_SYSTEM, 0x1001, 0x80AC8000, { 0x0F, 0x38, 0x82 }, { FCML_OP_MODRM_R_64, FCML_OP_RM( FCML_REG_UNDEFINED, FCML_EOS_UNDEFINED, FCML_EOS_OWORD, FCML_RMF_M ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_IRET[] = {
	// CF IRET A Valid Valid Interrupt return (16-bit operand size).
	{ NULL, FCML_AMT_GPI, 0x0000, 0x01C40000, { 0xCF, 0x00, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// CF IRETD A Valid Valid Interrupt return (32-bit operand size).
	{ "iretd", FCML_AMT_GPI, 0x0000, 0x02C40000, { 0xCF, 0x00, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// REX.W + CF IRETQ A Valid N.E. Interrupt return (64-bit operand size).
	{ "iretq", FCML_AMT_GPI, 0x0000, 0x04C40000, { 0xCF, 0x00, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_LAHF[] = {
	// 9F LAHF A Invalid* Valid Load: AH EFLAGS(SF:ZF:0:AF:0:PF:1:CF).
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00C40000, { 0x9F, 0x00, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_LAR[] = {
	// 0F 02 /r LAR r16, r16/m16 A Valid Valid r16 r16/m16 masked by FF00H.
	// 0F 02 /r LAR r32, r32/m16 A Valid Valid r32 r32/m16 masked by 00FxFF00H
	{ NULL, FCML_AMT_SYSTEM, 0x0000, 0x03D88000, { 0x0F, 0x02, 0x00 }, { FCML_OP_MODRM_R_W, FCML_OP_RM( FCML_REG_GPR, FCML_EOS_EOSA, FCML_EOS_WORD, FCML_RMF_RM ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// REX.W + 0F 02 /r LAR r64, r32/m16 A Valid N.E. r64 r32/m16 masked by 00FxFF00H
	{ NULL, FCML_AMT_SYSTEM, 0x0000, 0x04988000, { 0x0F, 0x02, 0x00 }, { FCML_OP_MODRM_R_W, FCML_OP_RM( FCML_REG_GPR, FCML_EOS_DWORD, FCML_EOS_WORD, FCML_RMF_RM ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_LDDQU[] = {
	// F2 0F F0 /r LDDQU xmm1, mem A Valid Valid Load unaligned data from mem and return double quadword in xmm1.
	{ NULL, FCML_AMT_SSE3, 0x2001, 0x00D88000, { 0x0F, 0xF0, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_M_UNDEF, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.128.F2.0F F0 /r VLDDQU xmm1, m128
	// VEX.256.F2.0F F0 /r VLDDQU ymm1, m256
	{ "vlddqu", FCML_AMT_AVX_SIMD, 0x2180, 0x80D88000, { 0x0F, 0xF0, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_RM( FCML_REG_SIMD, FCML_EOS_UNDEFINED, FCML_EOS_L, FCML_RMF_M ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_LDMXCSR[] = {
	// 0F AE /2 LDMXCSR m32 A Valid Valid Load MXCSR register from m32.
	{ NULL, FCML_AMT_SSE, 0x0000, 0x00D99000, { 0x0F, 0xAE, 0x00 }, { FCML_OP_MODRM_M_32, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.128.0F AE /2 VLDMXCSR m32
    { "vldmxcsr", FCML_AMT_AVX, 0x01C0, 0x80D99000, { 0x0F, 0xAE, 0x00 }, { FCML_OP_RM( FCML_REG_UNDEFINED, FCML_EOS_UNDEFINED, FCML_EOS_DWORD, FCML_RMF_M ), FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_LDS[] = {
	// C5 /r LDS r16,m16:16 A Invalid Valid Load DS:r16 with far pointer from memory.
	// C5 /r LDS r32,m16:32 A Invalid Valid Load DS:r32 with far pointer from memory.
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00448000, { 0xC5, 0x00, 0x00 }, { FCML_OP_MODRM_R_W, FCML_OP_FAR_POINTER_INDIRECT, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 0F B2 /r LSS r16,m16:16 A Valid Valid Load SS:r16 with far pointer from memory.
	// 0F B2 /r LSS r32,m16:32 A Valid Valid Load SS:r32 with far pointer from memory.
	// REX + 0F B2 /r LSS r64,m16:64 A Valid N.E. Load SS:r64 with far pointer from memory.
	{ "lss", FCML_AMT_GPI, 0x0000, 0x00D88000, { 0x0F, 0xB2, 0x00 }, { FCML_OP_MODRM_R_W, FCML_OP_FAR_POINTER_INDIRECT, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// C4 /r LES r16,m16:16 A Invalid Valid Load ES:r16 with far pointer from memory.
	// C4 /r LES r32,m16:32 A Invalid Valid Load ES:r32 with far pointer from memory.
	{ "les", FCML_AMT_GPI, 0x0000, 0x00448000, { 0xC4, 0x00, 0x00 }, { FCML_OP_MODRM_R_W, FCML_OP_FAR_POINTER_INDIRECT, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 0F B4 /r LFS r16,m16:16 A Valid Valid Load FS:r16 with far pointer from memory.
	// 0F B4 /r LFS r32,m16:32 A Valid Valid Load FS:r32 with far pointer from memory.
	// REX + 0F B4 /r LFS r64,m16:64 A Valid N.E. Load FS:r64 with far pointer from memory.
	{ "lfs", FCML_AMT_GPI, 0x0000, 0x00D88000, { 0x0F, 0xB4, 0x00 }, { FCML_OP_MODRM_R_W, FCML_OP_FAR_POINTER_INDIRECT, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 0F B5 /r LGS r16,m16:16 A Valid Valid Load GS:r16 with far pointer from memory.
	// 0F B5 /r LGS r32,m16:32 A Valid Valid Load GS:r32 with far pointer from memory.
	// REX + 0F B5 /r LGS r64,m16:64 A Valid N.E. Load GS:r64 with far pointer from memory.
	{ "lgs", FCML_AMT_GPI, 0x0000, 0x00D88000, { 0x0F, 0xB5, 0x00 }, { FCML_OP_MODRM_R_W, FCML_OP_FAR_POINTER_INDIRECT, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_LEA[] = {
	// 8D /r LEA r16,m A Valid Valid Store effective address for m in register r16.
	// 8D /r LEA r32,m A Valid Valid Store effective address for m in register r32.
	// REX.W + 8D /r LEA r64,m A Valid N.E. Store effective address for m in register r64.
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00C48000, { 0x8D, 0x00, 0x00 }, { FCML_OP_MODRM_R_W, FCML_OP_MODRM_M_UNDEF, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_LEAVE[] = {
	// C9 LEAVE A Valid Valid Set SP to BP, then pop BP.
	// C9 LEAVE A N.E. Valid Set ESP to EBP, then pop EBP.
	// C9 LEAVE A Valid N.E. Set RSP
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00C40000, { 0xC9, 0x00, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_LFENCE[] = {
	// 0F AE /5 LFENCE A Valid Valid Serializes load operations.
	{ NULL, FCML_AMT_SSE2, 0x0000, 0x00EC0000, { 0x0F, 0xAE, 0xE8 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_LLWPCB[] = {
	// LLWPCB reg32 8F RXB.09 0.1111.0.00 12 /0
	{ NULL, FCML_AMT_LWP, 0x0450, 0x00DB8000, { 0x09, 0x12, 0x00 }, { FCML_OP_RM( FCML_REG_GPR, FCML_EOS_DWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// LLWPCB reg64 8F RXB.09 1.1111.0.00 12 /0
	{ NULL, FCML_AMT_LWP, 0x0448, 0x00DB8000, { 0x09, 0x12, 0x00 }, { FCML_OP_RM( FCML_REG_GPR, FCML_EOS_QWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_LGDT[] = {
	// 0F 01 /2 LGDT m16&32 A N.E. Valid Load m into GDTR.
	{ NULL, FCML_AMT_SYSTEM, 0x0000, 0x03D99000, { 0x0F, 0x01, 0x00 }, { FCML_OP_RM( FCML_REG_UNDEFINED, FCML_EOS_UNDEFINED, (FCML_EOS_WORD + FCML_EOS_DWORD), FCML_RMF_M ), FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 0F 01 /2 LGDT m16&64 A Valid N.E. Load m into GDTR.
	{ NULL, FCML_AMT_SYSTEM, 0x0000, 0x04999000, { 0x0F, 0x01, 0x00 }, { FCML_OP_RM( FCML_REG_UNDEFINED, FCML_EOS_UNDEFINED, (FCML_EOS_WORD + FCML_EOS_QWORD), FCML_RMF_M ), FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 0F 01 /3 LIDT m16&32 A N.E. Valid Load m into IDTR.
	{ "lidt", FCML_AMT_SYSTEM, 0x0000, 0x04999800, { 0x0F, 0x01, 0x00 }, { FCML_OP_RM( FCML_REG_UNDEFINED, FCML_EOS_UNDEFINED, (FCML_EOS_WORD + FCML_EOS_DWORD), FCML_RMF_M ), FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 0F 01 /3 LIDT m16&64 A Valid N.E. Load m into IDTR.
	{ "lidt", FCML_AMT_SYSTEM, 0x0000, 0x04980000, { 0x0F, 0x01, 0x00 }, { FCML_OP_RM( FCML_REG_UNDEFINED, FCML_EOS_UNDEFINED, (FCML_EOS_WORD + FCML_EOS_QWORD), FCML_RMF_M ), FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_LLDT[] = {
	// 0F 00 /2 LLDT r/m16 A Valid Valid Load segment selector r/m16 into LDTR.
	{ NULL, FCML_AMT_SYSTEM, 0x0000, 0x00D99000, { 0x0F, 0x00, 0x00 }, { FCML_OP_MODRM_RM_16, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_LMSW[] = {
	// 0F 01 /6 LMSW r/m16 A Valid Valid Loads r/m16 in machine status word of CR0.
	{ NULL, FCML_AMT_SYSTEM, 0x0000, 0x00D9B000, { 0x0F, 0x01, 0x00 }, { FCML_OP_MODRM_RM_16, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_LODS[] = {
	// AC LODS m8 A Valid Valid For legacy mode, Load byte at address DS:(E)SI into AL. For 64-bit mode load byte at address (R)SI into AL.
	{ "lods;lodsb[ts]", FCML_AMT_GPI, 0x0004, 0x00C40000, { 0xAC, 0x00, 0x00 },
			{ FCML_OP_EXPLICIT_GPS_REG_ADDRESSING( FCML_REG_SI, FCML_EOS_BYTE, FCML_SEG_ENCODE_REGISTER( FCML_REG_DS, FCML_SEG_ALLOW_OVERRIDE ) ),
			FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// AD LODS m16 A Valid Valid For legacy mode, Load word at address DS:(E)SI into AX. For 64-bit mode load word at address (R)SI into AX.
	// AD  LODS m32 A Valid Valid For legacy mode, Load dword at address DS:(E)SI into EAX. For 64-bit mode load dword at address (R)SI into EAX.
	// REX.W + AD LODS m64 A Valid N.E. Load qword at address (R)SI into RAX.
	{ "lods;lodsw[ts,ow,a*];lodsd[ts,od,a*];lodsq[ts,oq,a*]", FCML_AMT_GPI, 0x0004, 0x00C40000, { 0xAD, 0x00, 0x00 },
			{ FCML_OP_EXPLICIT_GPS_REG_ADDRESSING( FCML_REG_SI, FCML_EOS_EOSA,FCML_SEG_ENCODE_REGISTER( FCML_REG_DS, FCML_SEG_ALLOW_OVERRIDE ) ),
			FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_LOOP[] = {
	// E2 cb LOOP rel8 A Valid Valid Decrement count; jump short if count 0.
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00C40000, { 0xE2, 0x00, 0x00 }, { FCML_OP_IMMEDIATE_DIS_RELATIVE_R_8, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// E1 cb LOOPE rel8 A Valid Valid Decrement count; jump short if count 0 and ZF = 1.
	{ "loope;loopz", FCML_AMT_GPI, 0x0000, 0x00C40000, { 0xE1, 0x00, 0x00 }, { FCML_OP_IMMEDIATE_DIS_RELATIVE_R_8, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// E0 cb LOOPNE rel8 A Valid Valid Decrement count; jump short if count 0 and ZF = 0.
	{ "loopne;loopnz", FCML_AMT_GPI, 0x0000, 0x00C40000, { 0xE0, 0x00, 0x00 }, { FCML_OP_IMMEDIATE_DIS_RELATIVE_R_8, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_LWPINS[] = {
	// LWPINS reg32.vvvv, reg/mem32, imm32 8F RXB.0A 0.src1.0.00 12 /0 /imm32
	{ NULL, FCML_AMT_LWP, 0x0450, 0x00D98000, { 0x0A, 0x12, 0x00 }, { FCML_OP_VEX_VVVV_REG( FCML_REG_GPR, FCML_EOS_DWORD ) | FCML_OA_W, FCML_OP_MODRM_RM_32, FCML_OP_ID, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// LWPINS reg64.vvvv, reg/mem32, imm32 8F RXB.0A 1.src1.0.00 12 /0 /imm32
	{ NULL, FCML_AMT_LWP, 0x0448, 0x00D98000, { 0x0A, 0x12, 0x00 }, { FCML_OP_VEX_VVVV_REG( FCML_REG_GPR, FCML_EOS_QWORD ) | FCML_OA_W, FCML_OP_MODRM_RM_64, FCML_OP_ID, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_LWPVAL[] = {
	// LWPVAL reg32.vvvv, reg/mem32, imm32 8F RXB.0A 0.src1.0.00 12 /1 /imm32
	{ NULL, FCML_AMT_LWP, 0x0450, 0x00D98800, { 0x0A, 0x12, 0x00 }, { FCML_OP_VEX_VVVV_REG( FCML_REG_GPR, FCML_EOS_DWORD ) | FCML_OA_W, FCML_OP_MODRM_RM_32, FCML_OP_ID, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// LWPVAL reg64.vvvv, reg/mem32, imm32 8F RXB.0A 1.src1.0.00 12 /1 /imm32
	{ NULL, FCML_AMT_LWP, 0x0448, 0x00D98800, { 0x0A, 0x12, 0x00 }, { FCML_OP_VEX_VVVV_REG( FCML_REG_GPR, FCML_EOS_QWORD ) | FCML_OA_W, FCML_OP_MODRM_RM_64, FCML_OP_ID, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_LSL[] = {
	// 0F 03 /r LSL r16, r16/m16 A Valid Valid Load: r16 segment limit, selector r16/m16.
	// 0F 03 /r LSL r32, r32/m16* A Valid Valid Load: r32 segment limit, selector r32/m16.
	{ NULL, FCML_AMT_SYSTEM, 0x0000, 0x03D88000, { 0x0F, 0x03, 0x00 }, { FCML_OP_MODRM_R_W, FCML_OP_RM( FCML_REG_GPR, FCML_EOS_EOSA, FCML_EOS_WORD, FCML_RMF_RM ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// REX.W + 0F 03 /r LSL r64, r32/m16* A Valid Valid Load: r64 segment limit, selector r32/m16
	{ NULL, FCML_AMT_SYSTEM, 0x0000, 0x04988000, { 0x0F, 0x03, 0x00 }, { FCML_OP_MODRM_R_W, FCML_OP_RM( FCML_REG_GPR, FCML_EOS_DWORD, FCML_EOS_WORD, FCML_RMF_RM ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_LTR[] = {
	// 0F 00 /3 LTR r/m16 A Valid Valid Load r/m16 into task register.
	{ NULL, FCML_AMT_SYSTEM, 0x0000, 0x00D99800, { 0x0F, 0x00, 0x00 }, { FCML_OP_MODRM_RM_16, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_MASKMOVDQU[] = {
	// 66 0F F7 /r MASKMOVDQU xmm1, xmm2 A Valid Valid Selectively write bytes from xmm1 to memory location using the byte mask in xmm2. The default memory location is specified by DS:EDI/RDI.
	{ NULL, FCML_AMT_SSE2, 0x1001, 0x00DA8000, { 0x0F, 0xF7, 0x00 }, { FCML_OP_R( FCML_REG_SIMD, FCML_EOS_OWORD ), FCML_OP_RM( FCML_REG_SIMD, FCML_EOS_OWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.128.66.0F F7 /r VMASKMOVDQU xmm1,xmm2
	{ "vmaskmovdqu", FCML_AMT_AVX_SIMD, 0x11C0, 0x00DA8000, { 0x0F, 0xF7, 0x00 }, { FCML_OP_R( FCML_REG_SIMD, FCML_EOS_OWORD ), FCML_OP_RM( FCML_REG_SIMD, FCML_EOS_OWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VMASKMOVP[] = {
	// VEX.NDS.128.66.0F38 2C /r VMASKMOVPS xmm1,xmm2,m128
	// VEX.NDS.256.66.0F38 2C /r VMASKMOVPS ymm1,ymm2,m256
	{ "vmaskmovps", FCML_AMT_AVX_SIMD, 0x1080, 0x00EC8000, { 0x0F, 0x38, 0x2C }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_M_SIMD_L, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.66.0F38 2D /r VMASKMOVPD xmm1,xmm2,m128
	// VEX.NDS.256.66.0F38 2D /r VMASKMOVPD ymm1,ymm2,m256
	{ "vmaskmovpd", FCML_AMT_AVX_SIMD, 0x1080, 0x00EC8000, { 0x0F, 0x38, 0x2D }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_M_SIMD_L, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.66.0F38 2E /r VMASKMOVPS m128,xmm1,xmm2
	// VEX.NDS.256.66.0F38 2E /r VMASKMOVPS m256,ymm1,ymm2
	{ "vmaskmovps", FCML_AMT_AVX_SIMD, 0x1080, 0x00EC8000, { 0x0F, 0x38, 0x2E }, { FCML_OP_MODRM_M_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_R_SIMD_L, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.66.0F38 2F /r VMASKMOVPD m128,xmm1,xmm2
	// VEX.NDS.256.66.0F38 2F /r VMASKMOVPD m256,ymm1,ymm2
	{ "vmaskmovpd", FCML_AMT_AVX_SIMD, 0x1080, 0x00EC8000, { 0x0F, 0x38, 0x2F }, { FCML_OP_MODRM_M_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_R_SIMD_L, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPMASKMOVD[] = {
	// VEX.NDS.128.66.0F38.W0 8C /r VPMASKMOVD xmm1,xmm2,m128
	// VEX.NDS.256.66.0F38.W0 8C /r VPMASKMOVD ymm1,ymm2,m256
	{ "vpmaskmovd", FCML_AMT_AVX2_SIMD, 0x1090, 0x80EC8000, { 0x0F, 0x38, 0x8C }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_M_SIMD_L, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.66.0F38.W1 8C /r VPMASKMOVQ xmm1,xmm2,m128
	// VEX.NDS.256.66.0F38.W1 8C /r VPMASKMOVQ ymm1,ymm2,m256
	{ "vpmaskmovq", FCML_AMT_AVX2_SIMD, 0x1088, 0x80EC8000, { 0x0F, 0x38, 0x8C }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_M_SIMD_L, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.66.0F38.W0 8E /r VPMASKMOVD m128,xmm1,xmm2
	// VEX.NDS.256.66.0F38.W0 8E /r VPMASKMOVD m256,ymm1,ymm2
	{ "vpmaskmovd", FCML_AMT_AVX2_SIMD, 0x1090, 0x80EC8000, { 0x0F, 0x38, 0x8E }, { FCML_OP_MODRM_M_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_R_SIMD_L, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.66.0F38.W1 8E /r VPMASKMOVQ m128,xmm1,xmm2
	// VEX.NDS.256.66.0F38.W1 8E /r VPMASKMOVQ m256,ymm1,ymm2
	{ "vpmaskmovq", FCML_AMT_AVX2_SIMD, 0x1088, 0x80EC8000, { 0x0F, 0x38, 0x8E }, { FCML_OP_MODRM_M_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_R_SIMD_L, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_MASKMOVQ[] = {
	// 0F F7 /r MASKMOVQ mm1, mm2 A Valid Valid Selectively write bytes from mm1 to memory location using the byte mask in mm2. The default memory location is specified by DS:EDI/RDI.
	{ NULL, FCML_AMT_SSE_SIMD, 0x0000, 0x00DA8000, { 0x0F, 0xF7, 0x00 }, { FCML_OP_R( FCML_REG_SIMD, FCML_EOS_MWORD ), FCML_OP_RM( FCML_REG_SIMD, FCML_EOS_MWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_MAXPD[] = {
	// 66 0F 5F /r MAXPD xmm1, xmm2/m128 A Valid Valid Return the maximum double-precision floatingpoint values between xmm2/m128 and xmm1.
	{ NULL, FCML_AMT_SSE2_SIMD, 0x1001, 0x00D88000, { 0x0F, 0x5F, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.66.0F 5F /r VMAXPD xmm1,xmm2,xmm3/m128
	// VEX.NDS.256.66.0F 5F /r VMAXPD ymm1,ymm2,ymm3/m256
	{ "vmaxpd", FCML_AMT_AVX_SIMD, 0x1080, 0x00D88000, { 0x0F, 0x5F, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_MAXPS[] = {
	// 0F 5F /r MAXPS xmm1, xmm2/m128 A Valid Valid Return the maximum singleprecision floating-point values between xmm2/m128 and xmm1.
	{ NULL, FCML_AMT_SSE_SIMD, 0x0000, 0x00D88000, { 0x0F, 0x5F, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.0F 5F /r VMAXPS xmm1,xmm2,xmm3/m128
	// VEX.NDS.256.0F 5F /r VMAXPS ymm1,ymm2,ymm3/m256
	{ "vmaxps", FCML_AMT_AVX_SIMD, 0x0080, 0x00D88000, { 0x0F, 0x5F, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

// TODO: Zastanowic sie na dwiloscia operandu podawanego dla trubow FCML_OP_MODRM_R_, czy ma ona sens? Najprwdopodobniejnie ma to zadnego znaczenia przynajmniej z punktu widzenia assemblera, no moze tylko dla GPR tu ma.

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_MAXSD[] = {
	// F2 0F 5F /r MAXSD xmm1, xmm2/m64 A Valid Valid Return the maximum scalardouble-precision floatingpoint value between xmm2/mem64 and xmm1.
	{ NULL, FCML_AMT_SSE2_SIMD, 0x2001, 0x00D88000, { 0x0F, 0x5F, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.F2.0F 5F /r VMAXSD xmm1,xmm2,xmm3/m64
	{ "vmaxsd", FCML_AMT_AVX_SIMD, 0x20C0, 0x00D88000, { 0x0F, 0x5F, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_64, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_MAXSS[] = {
	// F3 0F 5F /r MAXSS xmm1, xmm2/m32 A Valid Valid Return the maximum scalarsingle-precision floatingpoint value between xmm2/mem32 and xmm1.
	{ NULL, FCML_AMT_SSE_SIMD, 0x4001, 0x00D88000, { 0x0F, 0x5F, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_32, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.F3.0F 5F /r VMAXSS xmm1, xmm2, xmm3/m32
	{ "vmaxss", FCML_AMT_AVX_SIMD, 0x40C0, 0x00D88000, { 0x0F, 0x5F, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_32, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_MFENCE[] = {
	// MFENCE 0F AE /6  A Valid Valid Serializes load and store operations.
	{ NULL, FCML_AMT_SSE2, 0x0000, 0x00EC0000, { 0x0F, 0xAE, 0xF0 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_MINPD[] = {
	// 66 0F 5D /r MINPD xmm1, xmm2/m128 A Valid Valid Return the minimum doubleprecision floating-point values between xmm2/m128 and xmm1.
	{ NULL, FCML_AMT_SSE2_SIMD, 0x1001, 0x00D88000, { 0x0F, 0x5D, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.66.0F 5D /r VMINPD xmm1,xmm2,xmm3/m128
	// VEX.NDS.256.66.0F 5D /r VMINPD ymm1,ymm2,ymm3/m256
	{ "vminpd", FCML_AMT_AVX_SIMD, 0x1080, 0x00D88000, { 0x0F, 0x5D, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_MINPS[] = {
	// 0F 5D /r MINPS xmm1, xmm2/m128 A Valid Valid Return the minimum singleprecision floating-point values between xmm2/m128 and xmm1.
	{ NULL, FCML_AMT_SSE_SIMD, 0x0000, 0x00D88000, { 0x0F, 0x5D, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.0F 5D /r VMINPS xmm1,xmm2,xmm3/m128
	// VEX.NDS.256.0F 5D /r VMINPS ymm1,ymm2,ymm3/m256
	{ "vminps", FCML_AMT_AVX_SIMD, 0x0080, 0x00D88000, { 0x0F, 0x5D, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_MINSD[] = {
	// F2 0F 5D /r MINSD xmm1, xmm2/m64 A Valid Valid Return the minimum scalar double-precision floatingpoint value between xmm2/mem64 and xmm1.
	{ NULL, FCML_AMT_SSE2_SIMD, 0x2001, 0x00D88000, { 0x0F, 0x5D, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.F2.0F 5D /r VMINSD xmm1, xmm2, xmm3/m64
	{ "vminsd", FCML_AMT_AVX_SIMD, 0x20C0, 0x00D88000, { 0x0F, 0x5D, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_64, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_MINSS[] = {
	// F3 0F 5D /r MINSS xmm1, xmm2/m32 A Valid Valid Return the minimum scalar single-precision floatingpoint value between xmm2/mem32 and xmm1.
	{ NULL, FCML_AMT_SSE_SIMD, 0x4001, 0x00D88000, { 0x0F, 0x5D, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_32, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.F3.0F 5D /r VMINSS xmm1,xmm2,xmm3/m32
	{ "vminss", FCML_AMT_AVX_SIMD, 0x40C0, 0x00D88000, { 0x0F, 0x5D, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_32, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_MONITOR[] = {
	// 0F 01 C8 MONITOR A Valid Valid Sets up a linear address range to be monitored by hardware and activates the monitor. The address range should be a write-back memory caching type. The address is DS:EAX
	{ NULL, FCML_AMT_SSE3, 0x0000, 0x006C0000, { 0x0F, 0x01, 0xC8 }, { FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_EAX, FCML_EOS_DWORD ),
		FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_ECX, FCML_EOS_DWORD ),
		FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_EDX, FCML_EOS_DWORD ), FCML_NA, FCML_NA }, FCML_AM_NONE },
	{ NULL, FCML_AMT_SSE3, 0x0000, 0x00AC0000, { 0x0F, 0x01, 0xC8 }, { FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_RAX, FCML_EOS_QWORD ),
		FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_RCX, FCML_EOS_QWORD ),
		FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_RDX, FCML_EOS_QWORD ), FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_MOV[] = {
	// 88 /r MOV r/m8,r8 A Valid Valid Move r8 to r/m8.
	// REX + 88 /r MOV r/m8***,r8*** A Valid N.E. Move r8 to r/m8.
	{ NULL, FCML_AMT_GPI, 0x0804, 0x00C48000, { 0x88, 0x00, 0x00 }, { FCML_OP_MODRM_RM_8_W, FCML_OP_MODRM_R_8, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 89 /r MOV r/m16,r16 A Valid Valid Move r16 to r/m16.
	// 89 /r MOV r/m32,r32 A Valid Valid Move r32 to r/m32.
	// REX.W + 89 /r MOV r/m64,r64 A Valid N.E. Move r64 to r/m64.
	{ NULL, FCML_AMT_GPI, 0x0804, 0x00C48000, { 0x89, 0x00, 0x00 }, { FCML_OP_MODRM_RM_W, FCML_OP_MODRM_R, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 8A /r MOV r8,r/m8 B Valid Valid Move r/m8 to r8.
	// REX + 8A /r MOV r8***,r/m8*** B Valid N.E. Move r/m8 to r8.
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00C48000, { 0x8A, 0x00, 0x00 }, { FCML_OP_MODRM_R_8_W, FCML_OP_MODRM_RM_8, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 8B /r MOV r16,r/m16 B Valid Valid Move r/m16 to r16.
	// 8B /r MOV r32,r/m32 B Valid Valid Move r/m32 to r32.
	// REX.W + 8B /r MOV r64,r/m64 B Valid N.E. Move r/m64 to r64.
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00C48000, { 0x8B, 0x00, 0x00 }, { FCML_OP_MODRM_R_W, FCML_OP_MODRM_RM, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 8C /r MOV r/m16,Sreg** A Valid Valid Move segment register to r/m16.
	{ NULL, FCML_AMT_GPI, 0x0010, 0x03C48000, { 0x8C, 0x00, 0x00 }, { FCML_OP_MODRM_RM_16_W, FCML_OP_R( FCML_REG_SEG, FCML_EOS_WORD ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// REX.W + 8C /r MOV r/m64,Sreg** A Valid Valid Move zero extended 16-bit segment register to r/m64.
	{ NULL, FCML_AMT_GPI, 0x0008, 0x04848000, { 0x8C, 0x00, 0x00 }, { FCML_OP_MODRM_RM_64_W, FCML_OP_R( FCML_REG_SEG, FCML_EOS_WORD ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 8E /r MOV Sreg,r/m16** RM Valid Valid Move r/m16 to segment register.
	{ NULL, FCML_AMT_GPI, 0x0010, 0x03C48000, { 0x8E, 0x00, 0x00 }, { FCML_OP_R( FCML_REG_SEG, FCML_EOS_WORD ), FCML_OP_MODRM_RM_16_W, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// REX.W + 8E /r MOV Sreg,r/m64** RM Valid Valid Move lower 16 bits of r/m64 to segment register.
	{ NULL, FCML_AMT_GPI, 0x0008, 0x04848000, { 0x8E, 0x00, 0x00 }, { FCML_OP_R( FCML_REG_SEG, FCML_EOS_WORD ), FCML_OP_MODRM_RM_64_W, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// A0 MOV AL,moffs8* C Valid Valid Move byte at (seg:offset) to AL.
	// REX.W + A0 MOV AL,moffs8* C Valid N.E. Move byte at (offset) to AL.
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00C40000, { 0xA0, 0x00, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_AL, FCML_EOS_BYTE ), FCML_OP_SEGMENT_RELATIVE_OFFSET( FCML_EOS_BYTE, FCML_SEG_ENCODE_REGISTER( FCML_REG_DS, FCML_SEG_ALLOW_OVERRIDE ) ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// A1 MOV AX,moffs16* C Valid Valid Move word at (seg:offset) to AX.
	// A1 MOV EAX,moffs32* C Valid Valid Move doubleword at (seg:offset) to EAX.
	// REX.W + A1 MOV RAX,moffs64* C Valid N.E. Move quadword at (offset) to RAX.
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00C40000, { 0xA1, 0x00, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_AL, FCML_EOS_EOSA ), FCML_OP_SEGMENT_RELATIVE_OFFSET( FCML_EOS_EOSA, FCML_SEG_ENCODE_REGISTER( FCML_REG_DS, FCML_SEG_ALLOW_OVERRIDE ) ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// A2 MOV moffs8,AL D Valid Valid Move AL to (seg:offset).
	// REX.W + A2 MOV moffs8***,AL D Valid N.E. Move AL to (offset).
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00C40000, { 0xA2, 0x00, 0x00 }, { FCML_OP_SEGMENT_RELATIVE_OFFSET( FCML_EOS_BYTE, FCML_SEG_ENCODE_REGISTER( FCML_REG_DS, FCML_SEG_ALLOW_OVERRIDE ) ), FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_AL, FCML_EOS_BYTE ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// A3 MOV moffs16*,AX D Valid Valid Move AX to (seg:offset).
	// A3 MOV moffs32*,EAX D Valid Valid Move EAX to (seg:offset).
	// REX.W + A3 MOV moffs64*,RAX D Valid N.E. Move RAX to (offset).
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00C40000, { 0xA3, 0x00, 0x00 }, { FCML_OP_SEGMENT_RELATIVE_OFFSET( FCML_EOS_EOSA, FCML_SEG_ENCODE_REGISTER( FCML_REG_DS, FCML_SEG_ALLOW_OVERRIDE ) ), FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_AL, FCML_EOS_EOSA ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// B0+ rb MOV r8, imm8 E Valid Valid Move imm8 to r8.
	// REX + B0+ rb MOV r8***, imm8 E Valid N.E. Move imm8 to r8.
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00C40001, { 0xB0, 0x00, 0x00 }, { FCML_OP_OPCODE_REG( FCML_REG_GPR, FCML_EOS_BYTE ) | FCML_OA_W, FCML_OP_IB, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// B8+ rw MOV r16, imm16 E Valid Valid Move imm16 to r16.
	// B8+ rd MOV r32, imm32 E Valid Valid Move imm32 to r32.
	// REX.W + B8+ rd MOV r64, imm64 E Valid N.E. Move imm64 to r64.
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00C40001, { 0xB8, 0x00, 0x00 }, { FCML_OP_OPCODE_REG( FCML_REG_GPR, FCML_EOS_EOSA ) | FCML_OA_W, FCML_OP_IMM_EOSA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// C6 /0 MOV r/m8, imm8 F Valid Valid Move imm8 to r/m8.
	// REX + C6 /0 MOV r/m8***, imm8 F Valid N.E. Move imm8 to r/m8.
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00C58000, { 0xC6, 0x00, 0x00 }, { FCML_OP_MODRM_RM_8_W, FCML_OP_IB, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// C7 /0 MOV r/m16, imm16 F Valid Valid Move imm16 to r/m16.
	// C7 /0 MOV r/m32, imm32 F Valid Valid Move imm32 to r/m32.
	{ NULL, FCML_AMT_GPI, 0x0010, 0x03C58000, { 0xC7, 0x00, 0x00 }, { FCML_OP_MODRM_RM_W, FCML_OP_IMM_EOSA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// REX.W + C7 /0 MOV r/m64, imm32 F Valid N.E. Move imm32 sign extended to 64-bits to r/m64.
	{ NULL, FCML_AMT_GPI, 0x0008, 0x04858000, { 0xC7, 0x00, 0x00 }, { FCML_OP_MODRM_RM_W, FCML_OP_ID_EX_EOSA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 0F 21/r MOV r32, DR0�DR7 A N.E. Valid Move debug register to r32
    { NULL, FCML_AMT_SYSTEM, 0x0000, 0x00588000, { 0x0F, 0x21, 0x00 }, { FCML_OP_RM( FCML_REG_GPR, FCML_EOS_DWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ) | FCML_OA_W, FCML_OP_R( FCML_REG_DR, FCML_EOS_DWORD ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
    // 0F 21/r MOV r64, DR0�DR7 A Valid N.E. Move extended debug register to r64.
    { NULL, FCML_AMT_SYSTEM, 0x0000, 0x00988000, { 0x0F, 0x21, 0x00 }, { FCML_OP_RM( FCML_REG_GPR, FCML_EOS_QWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ) | FCML_OA_W, FCML_OP_R( FCML_REG_DR, FCML_EOS_QWORD ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
    // 0F 23 /r MOV DR0�DR7, r32 A N.E. Valid Move r32 to debug register
    { NULL, FCML_AMT_SYSTEM, 0x0000, 0x00588000, { 0x0F, 0x23, 0x00 }, { FCML_OP_R( FCML_REG_DR, FCML_EOS_DWORD ) | FCML_OA_W, FCML_OP_RM( FCML_REG_GPR, FCML_EOS_DWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
    // 0F 23 /r MOV DR0�DR7, r64 A Valid N.E. Move r64 to extended debug register.
    { NULL, FCML_AMT_SYSTEM, 0x0000, 0x00988000, { 0x0F, 0x23, 0x00 }, { FCML_OP_R( FCML_REG_DR, FCML_EOS_QWORD ) | FCML_OA_W, FCML_OP_RM( FCML_REG_GPR, FCML_EOS_QWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 0F 20/r MOV r32, CR0�CR7 A N.E. Valid Move control register to r32
    { NULL, FCML_AMT_SYSTEM, 0x0000, 0x00588000, { 0x0F, 0x20, 0x00 }, { FCML_OP_RM( FCML_REG_GPR, FCML_EOS_DWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ) | FCML_OA_W, FCML_OP_R( FCML_REG_CR, FCML_EOS_DWORD ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
    // 0F 20/r MOV r64, CR0�CR7 A Valid N.E. Move extended control register to r64.
    // REX.R + 0F 20 /0 MOV r64, CR8 A Valid N.E. Move extended CR8 to r64.1
    { NULL, FCML_AMT_SYSTEM, 0x0000, 0x00988000, { 0x0F, 0x20, 0x00 }, { FCML_OP_RM( FCML_REG_GPR, FCML_EOS_QWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ) | FCML_OA_W, FCML_OP_R( FCML_REG_CR, FCML_EOS_QWORD ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
    // 0F 22 /r MOV CR0�CR7, r32 A N.E. Valid Move r32 to control register
    { NULL, FCML_AMT_SYSTEM, 0x0000, 0x00588000, { 0x0F, 0x22, 0x00 }, { FCML_OP_R( FCML_REG_CR, FCML_EOS_DWORD ) | FCML_OA_W, FCML_OP_RM( FCML_REG_GPR, FCML_EOS_DWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
    // 0F 22 /r MOV CR0�CR7, r64 A Valid N.E. Move r64 to extended control register.
    // REX.R + 0F 22 /0 MOV CR8, r64 A Valid N.E. Move r64 to extended CR8.1
    { NULL, FCML_AMT_SYSTEM, 0x0000, 0x00988000, { 0x0F, 0x22, 0x00 }, { FCML_OP_R( FCML_REG_CR, FCML_EOS_QWORD ) | FCML_OA_W, FCML_OP_RM( FCML_REG_GPR, FCML_EOS_QWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_MOVAPD[] = {
	// 66 0F 28 /r MOVAPD xmm1, xmm2/m128 A Valid Valid Move packed doubleprecision floating-point values from xmm2/m128 to xmm1.
	{ NULL, FCML_AMT_SSE2_SIMD, 0x1001, 0x00D88000, { 0x0F, 0x28, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 66 0F 29 /r MOVAPD xmm2/m128, xmm1 B Valid Valid Move packed doubleprecision floating-point values from xmm1 to xmm2/m128.
	{ NULL, FCML_AMT_SSE2_SIMD, 0x1001, 0x00D88000, { 0x0F, 0x29, 0x00 }, { FCML_OP_MODRM_RM_XMM_128_W, FCML_OP_MODRM_R_XMM, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.128.66.0F 28 /r VMOVAPD xmm1,xmm2/m128
	// VEX.256.66.0F 28 /r VMOVAPD ymm1,ymm2/m256
	{ "vmovapd", FCML_AMT_AVX_SIMD, 0x1180, 0x00D88000, { 0x0F, 0x28, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_MODRM_RM_SIMD_L, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.128.66.0F 29 /r VMOVAPD xmm2/m128,xmm1
	// VEX.256.66.0F 29 /r VMOVAPD ymm2/m256,ymm1
	{ "vmovapd", FCML_AMT_AVX_SIMD, 0x1180, 0x00D88000, { 0x0F, 0x29, 0x00 }, { FCML_OP_MODRM_RM_SIMD_L_W, FCML_OP_MODRM_R_SIMD_L, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_MOVAPS[] = {
	// 0F 28 /r MOVAPS xmm1, xmm2/m128 A Valid Valid Move packed singleprecision floating-point values from xmm2/m128 to xmm1.
	{ NULL, FCML_AMT_SSE_SIMD, 0x0000, 0x00D88000, { 0x0F, 0x28, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 0F 29 /r MOVAPS xmm2/m128, xmm1 B Valid Valid Move packed singleprecision floating-point values from xmm1 to xmm2/m128.
	{ NULL, FCML_AMT_SSE_SIMD, 0x0000, 0x00D88000, { 0x0F, 0x29, 0x00 }, { FCML_OP_MODRM_RM_XMM_128_W, FCML_OP_MODRM_R_XMM, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.128.0F 28 /r VMOVAPS xmm1,xmm2/m128
	// VEX.256.0F 28 /r VMOVAPS ymm1,ymm2/m256
	{ "vmovaps", FCML_AMT_AVX_SIMD, 0x0180, 0x00D88000, { 0x0F, 0x28, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_MODRM_RM_SIMD_L, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.128.0F 29 /r VMOVAPS xmm2/m128,xmm1
	// VEX.256.0F 29 /r VMOVAPS ymm2/m256,ymm1
	{ "vmovaps", FCML_AMT_AVX_SIMD, 0x0180, 0x00D88000, { 0x0F, 0x29, 0x00 }, { FCML_OP_MODRM_RM_SIMD_L_W, FCML_OP_MODRM_R_SIMD_L, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_MOVBE[] = {
	// 0F 38 F0 /r MOVBE r16, m16 A Valid Valid Reverse byte order in m16 and move to r16
	// 0F 38 F0 /r MOVBE r32, m32 A Valid Valid Reverse byte order in m32 and move to r32
	// REX.W + 0F 38 F0 /r MOVBE r64, m64 A Valid N.E. Reverse byte order in m64 and move to r64.
	{ NULL, FCML_AMT_GPI, 0x0000, 0x80EC8000, { 0x0F, 0x38, 0xF0 }, { FCML_OP_MODRM_R_W, FCML_OP_MODRM_M, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 0F 38 F1 /r MOVBE m16, r16 B Valid Valid Reverse byte order in r16 and move to m16
	// 0F 38 F1 /r MOVBE m32, r32 B Valid Valid Reverse byte order in r32 and move to m32
	// REX.W + 0F 38 F1 /r MOVBE m64, r64 B Valid N.E. Reverse byte order in
	{ NULL, FCML_AMT_GPI, 0x0000, 0x80EC8000, { 0x0F, 0x38, 0xF1 }, { FCML_OP_MODRM_M_W, FCML_OP_MODRM_R, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_MOVD[] = {
	// 0F 6E /r MOVD mm,r/m32 A Valid Valid Move doubleword from r/m32 to mm.
	{ NULL, FCML_AMT_MMX_SIMD, 0x0010, 0x03D88000, { 0x0F, 0x6E, 0x00 }, { FCML_OP_MODRM_R_MMX_W, FCML_OP_MODRM_RM_32, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// REX.W + 0F 6E /r MOVQ mm, r/m64 A Valid N.E. Move quadword from r/m64 to mm.
	{ "movq", FCML_AMT_MMX_SIMD, 0x0008, 0x04988000, { 0x0F, 0x6E, 0x00 }, { FCML_OP_MODRM_R_MMX_W, FCML_OP_MODRM_RM_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 0F 7E /r MOVD r/m32, mm B Valid Valid Move doubleword from mm to r/m32.
	{ NULL, FCML_AMT_MMX_SIMD, 0x0010, 0x03D88000, { 0x0F, 0x7E, 0x00 }, { FCML_OP_MODRM_RM_32_W, FCML_OP_MODRM_R_MMX, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// REX.W + 0F 7E /r MOVQ r/m64, mm B Valid N.E. Move quadword from mm to r/m64.
	{ "movq", FCML_AMT_MMX_SIMD, 0x0008, 0x04988000, { 0x0F, 0x7E, 0x00 }, { FCML_OP_MODRM_RM_64_W, FCML_OP_MODRM_R_MMX, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 66 0F 6E /r MOVD xmm, r/m32 A Valid Valid Move doubleword from r/m32 to xmm.
	{ NULL, FCML_AMT_SSE2_SIMD, 0x1010, 0x03D88000, { 0x0F, 0x6E, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_32, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 66 REX.W 0F 6E /r MOVQ xmm, r/m64 A Valid N.E. Move quadword from r/m64 to xmm.
	{ "movq", FCML_AMT_SSE2_SIMD, 0x1008, 0x04988000, { 0x0F, 0x6E, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 66 0F 7E /r MOVD r/m32, xmm B Valid Valid Move doubleword from xmm register to r/m32.
	{ NULL, FCML_AMT_SSE2_SIMD, 0x1010, 0x03D88000, { 0x0F, 0x7E, 0x00 }, { FCML_OP_MODRM_RM_32_W, FCML_OP_MODRM_R_XMM, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 66 REX.W 0F 7E /r MOVQ r/m64, xmm B Valid N.E. Move quadword from xmm register to r/m64.
	{ "movq", FCML_AMT_SSE2_SIMD, 0x1008, 0x04988000, { 0x0F, 0x7E, 0x00 }, { FCML_OP_MODRM_RM_64_W, FCML_OP_MODRM_R_XMM, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.128.66.0F.W0 6E /r VMOVD xmm1,r32/m32
	{ "vmovd", FCML_AMT_AVX_SIMD, 0x11D0, 0x03588000, { 0x0F, 0x6E, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_32, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.128.66.0F.W1 6E /r VMOVQ xmm1,r64/m64
	{ "vmovq", FCML_AMT_AVX_SIMD, 0x11C8, 0x04988000, { 0x0F, 0x6E, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.128.66.0F.W0 7E /r VMOVD r32/m32,xmm1
	{ "vmovd", FCML_AMT_AVX_SIMD, 0x11D0, 0x03588000, { 0x0F, 0x7E, 0x00 }, { FCML_OP_MODRM_RM_32_W, FCML_OP_MODRM_R_XMM, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.128.66.0F.W1 7E /r VMOVQ r64/m64,xmm1
	{ "vmovq", FCML_AMT_AVX_SIMD, 0x11C8, 0x04988000, { 0x0F, 0x7E, 0x00 }, { FCML_OP_MODRM_RM_64_W, FCML_OP_MODRM_R_XMM, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_MOVDDUP[] = {
	//F2 0F 12 /r MOVDDUP xmm1, xmm2/m64 A Valid Valid Move one double-precision floating-point value from the lower 64-bit operand in xmm2/m64 to xmm1 and duplicate.
	{ NULL, FCML_AMT_SSE3_SIMD, 0x2001, 0x00D88000, { 0x0F, 0x12, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.128.F2.0F 12 /r VMOVDDUP xmm1,xmm2/m64
	{ "vmovddup", FCML_AMT_AVX_SIMD, 0x21C0, 0x00D88000, { 0x0F, 0x12, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.256.F2.0F 12 /r VMOVDDUP ymm1,ymm2/m256
	{ "vmovddup", FCML_AMT_AVX_SIMD, 0x21A0, 0x00D88000, { 0x0F, 0x12, 0x00 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_MODRM_RM_YMM_256, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_MOVDQA[] = {
	// 66 0F 6F /r MOVDQA xmm1, xmm2/m128 A Valid Valid Move aligned double quadword from xmm2/m128 to xmm1.
	{ NULL, FCML_AMT_SSE2_SIMD, 0x1001, 0x00D88000, { 0x0F, 0x6F, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 66 0F 7F /r MOVDQA xmm2/m128, xmm1 B Valid Valid Move aligned double quadword from xmm1 to xmm2/m128.
	{ NULL, FCML_AMT_SSE2_SIMD, 0x1001, 0x00D88000, { 0x0F, 0x7F, 0x00 }, { FCML_OP_MODRM_RM_XMM_128_W, FCML_OP_MODRM_R_XMM, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.128.66.0F 6F /r VMOVDQA xmm1,xmm2/m128
	// VEX.256.66.0F 6F /r VMOVDQA ymm1,ymm2/m256
	{ "vmovdqa", FCML_AMT_AVX_SIMD, 0x1180, 0x00D88000, { 0x0F, 0x6F, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_MODRM_RM_SIMD_L, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.128.66.0F 7F /r VMOVDQA xmm2/m128,xmm1
	// VEX.256.66.0F 7F /r VMOVDQA ymm2/m256,ymm1
	{ "vmovdqa", FCML_AMT_AVX_SIMD, 0x1180, 0x00D88000, { 0x0F, 0x7F, 0x00 }, { FCML_OP_MODRM_RM_SIMD_L_W, FCML_OP_MODRM_R_SIMD_L, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_MOVDQU[] = {
	// F3 0F 6F /r MOVDQU xmm1, xmm2/m128 A Valid Valid Move unaligned double quadword from xmm2/m128 to xmm1.
	{ NULL, FCML_AMT_SSE2_SIMD, 0x4001, 0x00D88000, { 0x0F, 0x6F, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// F3 0F 7F /r MOVDQU xmm2/m128, xmm1 B Valid Valid Move unaligned double quadword from xmm1 to xmm2/m128.
	{ NULL, FCML_AMT_SSE2_SIMD, 0x4001, 0x00D88000, { 0x0F, 0x7F, 0x00 }, { FCML_OP_MODRM_RM_XMM_128_W, FCML_OP_MODRM_R_XMM, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.128.F3.0F 6F /r VMOVDQU xmm1,xmm2/m128
	// VEX.256.F3.0F 6F /r VMOVDQU ymm1,ymm2/m256
	{ "vmovdqu", FCML_AMT_AVX_SIMD, 0x4180, 0x00D88000, { 0x0F, 0x6F, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_MODRM_RM_SIMD_L, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.128.F3.0F 7F /r VMOVDQU xmm2/m128,xmm1
	// VEX.256.F3.0F 7F /r VMOVDQU ymm2/m256,ymm1
	{ "vmovdqu", FCML_AMT_AVX_SIMD, 0x4180, 0x00D88000, { 0x0F, 0x7F, 0x00 }, { FCML_OP_MODRM_RM_SIMD_L_W, FCML_OP_MODRM_R_SIMD_L, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_MOVDQ2Q[] = {
	// F2 0F D6 MOVDQ2Q mm, xmm A Valid Valid Move low quadword from xmm to mmx register.
	{ NULL, FCML_AMT_SSE2_SIMD, 0x2001, 0x00DA8000, { 0x0F, 0xD6, 0x00 }, { FCML_OP_MODRM_R_MMX_W, FCML_OP_RM( FCML_REG_SIMD, FCML_EOS_OWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_MOVHLPS[] = {
	// 0F 12 /r MOVHLPS xmm1, xmm2 A Valid Valid Move two packed singleprecision floating-point values from high quadword of xmm2 to low quadword of xmm1.
	{ NULL, FCML_AMT_SSE_SIMD, 0x0000, 0x00DA8000, { 0x0F, 0x12, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_RM( FCML_REG_SIMD, FCML_EOS_OWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.0F 12 /r VMOVHLPS xmm1, xmm2, xmm3
	{ "vmovhlps", FCML_AMT_AVX_SIMD, 0x00C0, 0x00DA8000, { 0x0F, 0x12, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_L, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_MOVHPD[] = {
	// 66 0F 16 /r MOVHPD xmm, m64 A Valid Valid Move double-precision floating-point value from m64 to high quadword of xmm.
	{ NULL, FCML_AMT_SSE2_SIMD, 0x1001, 0x80D88000, { 0x0F, 0x16, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_RM( FCML_REG_UNDEFINED, FCML_EOS_UNDEFINED, FCML_EOS_QWORD, FCML_RMF_M ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 66 0F 17 /r MOVHPD m64, xmm B Valid Valid Move double-precision floating-point value from high quadword of xmm to m64.
	{ NULL, FCML_AMT_SSE2_SIMD, 0x1001, 0x80D88000, { 0x0F, 0x17, 0x00 }, { FCML_OP_RM( FCML_REG_UNDEFINED, FCML_EOS_UNDEFINED, FCML_EOS_QWORD, FCML_RMF_M ) | FCML_OA_W, FCML_OP_MODRM_R_XMM, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.66.0F 16 /r VMOVHPD xmm2,xmm1,m64
	{ "vmovhpd", FCML_AMT_AVX_SIMD, 0x10C0, 0x80D88000, { 0x0F, 0x16, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_64, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX128.66.0F 17/r VMOVHPD m64, xmm1
	{ "vmovhpd", FCML_AMT_AVX_SIMD, 0x11C0, 0x80D88000, { 0x0F, 0x17, 0x00 }, { FCML_OP_MODRM_RM_64_W, FCML_OP_MODRM_R_SIMD_L_W, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_MOVHPS[] = {
	// 0F 16 /r MOVHPS xmm, m64 A Valid Valid Move two packed singleprecision floating-point values from m64 to high quadword of xmm.
	{ NULL, FCML_AMT_SSE_SIMD, 0x0000, 0x80D88000, { 0x0F, 0x16, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_RM( FCML_REG_UNDEFINED, FCML_EOS_UNDEFINED, FCML_EOS_MWORD, FCML_RMF_M ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 0F 17 /r MOVHPS m64, xmm B Valid Valid Move two packed singleprecision floating-point values from high quadword of xmm to m64.
	{ NULL, FCML_AMT_SSE_SIMD, 0x0000, 0x80D88000, { 0x0F, 0x17, 0x00 }, { FCML_OP_RM( FCML_REG_UNDEFINED, FCML_EOS_UNDEFINED, FCML_EOS_MWORD, FCML_RMF_M ) | FCML_OA_W, FCML_OP_MODRM_R_XMM, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.0F 16 /r VMOVHPS xmm2,xmm1,m64
	{ "vmovhps", FCML_AMT_AVX_SIMD, 0x00C0, 0x80D88000, { 0x0F, 0x16, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_64, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.128.0F 17 /r VMOVHPS m64,xmm1
	{ "vmovhps", FCML_AMT_AVX_SIMD, 0x01C0, 0x80D88000, { 0x0F, 0x17, 0x00 }, { FCML_OP_MODRM_RM_64_W, FCML_OP_MODRM_R_XMM, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_MOVLHPS[] = {
	// 0F 16 /r MOVLHPS xmm1, xmm2 A Valid Valid Move two packed singleprecision floating-point values from low quadword of xmm2 to high quadword of xmm1.
	{ NULL, FCML_AMT_SSE_SIMD, 0x0000, 0x00DA8000, { 0x0F, 0x16, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_RM( FCML_REG_SIMD, FCML_EOS_OWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.0F 16 /r VMOVLHPS xmm1,xmm2,xmm3
	{ "vmovlhps", FCML_AMT_AVX_SIMD, 0x00C0, 0x00DA8000, { 0x0F, 0x16, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_RM( FCML_REG_SIMD, FCML_EOS_OWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_MOVLPD[] = {
	// 66 0F 12 /r MOVLPD xmm, m64 A Valid Valid Move double-precision floating-point value from m64 to low quadword of xmm register.
	{ NULL, FCML_AMT_SSE2_SIMD, 0x1001, 0x80D88000, { 0x0F, 0x12, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_RM( FCML_REG_UNDEFINED, FCML_EOS_UNDEFINED, FCML_EOS_QWORD, FCML_RMF_M ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 66 0F 13 /r MOVLPD m64, xmm B Valid Valid Move double-precision floating-point nvalue from low quadword of xmm register to m64.
	{ NULL, FCML_AMT_SSE2_SIMD, 0x1001, 0x80D88000, { 0x0F, 0x13, 0x00 }, { FCML_OP_RM( FCML_REG_UNDEFINED, FCML_EOS_UNDEFINED, FCML_EOS_QWORD, FCML_RMF_M ) | FCML_OA_W, FCML_OP_MODRM_R_XMM, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.66.0F 12 /r VMOVLPD xmm2,xmm1,m64
	{ "vmovlpd", FCML_AMT_AVX_SIMD, 0x10C0, 0x80D88000, { 0x0F, 0x12, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_64, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.128.66.0F 13 /r VMOVLPD m64,xmm1
	{ "vmovlpd", FCML_AMT_AVX_SIMD, 0x11C0, 0x80D88000, { 0x0F, 0x13, 0x00 }, { FCML_OP_MODRM_RM_64_W, FCML_OP_MODRM_R_SIMD_L_W, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_MOVLPS[] = {
	// 0F 12 /r MOVLPS xmm, m64 A Valid Valid Move two packed singleprecision floating-point values from m64 to low quadword of xmm.
	{ NULL, FCML_AMT_SSE_SIMD, 0x0000, 0x80D88000, { 0x0F, 0x12, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_RM( FCML_REG_UNDEFINED, FCML_EOS_UNDEFINED, FCML_EOS_QWORD, FCML_RMF_M ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 0F 13 /r MOVLPS m64, xmm B Valid Valid Move two packed singleprecision floating-point values from low quadword of xmm to m64.
	{ NULL, FCML_AMT_SSE_SIMD, 0x0000, 0x80D88000, { 0x0F, 0x13, 0x00 }, { FCML_OP_RM( FCML_REG_UNDEFINED, FCML_EOS_UNDEFINED, FCML_EOS_QWORD, FCML_RMF_M ) | FCML_OA_W, FCML_OP_MODRM_R_XMM, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.0F 12 /r VMOVLPS xmm2,xmm1,m64
	{ "vmovlps", FCML_AMT_AVX_SIMD, 0x00C0, 0x80D88000, { 0x0F, 0x12, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_M_64, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.128.0F 13 /r VMOVLPS m64, xmm1
	{ "vmovlps", FCML_AMT_AVX_SIMD, 0x01C0, 0x80D88000, { 0x0F, 0x13, 0x00 }, { FCML_OP_MODRM_M_64_W, FCML_OP_MODRM_R_XMM, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_MOVMSKPD[] = {
	// 66 0F 50 /r MOVMSKPD reg, xmm A Valid Valid Extract 2-bit sign mask from xmm and store in reg. The upper bits of r32 or r64 are filled with zeros.
	{ NULL, FCML_AMT_SSE2_SIMD, 0x1000, 0x005A8000, { 0x0F, 0x50, 0x00 }, { FCML_OP_MODRM_R_32_W, FCML_OP_RM( FCML_REG_SIMD, FCML_EOS_OWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	{ NULL, FCML_AMT_SSE2_SIMD, 0x1000, 0x009A8000, { 0x0F, 0x50, 0x00 }, { FCML_OP_MODRM_R_64_W, FCML_OP_RM( FCML_REG_SIMD, FCML_EOS_OWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.128.66.0F 50 /r VMOVMSKPD reg,xmm2
	// VEX.256.66.0F 50 /r VMOVMSKPD reg,ymm2
	{ "vmovmskpd", FCML_AMT_AVX_SIMD, 0x1180, 0x005A8000, { 0x0F, 0x50, 0x00 }, { FCML_OP_MODRM_R_32_W, FCML_OP_RM( FCML_REG_SIMD, FCML_EOS_L, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	{ "vmovmskpd", FCML_AMT_AVX_SIMD, 0x1180, 0x009A8000, { 0x0F, 0x50, 0x00 }, { FCML_OP_MODRM_R_64_W, FCML_OP_RM( FCML_REG_SIMD, FCML_EOS_L, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_MOVMSKPS[] = {
	// 0F 50 /r MOVMSKPS reg, xmm A Valid Valid Extract 4-bit sign mask from xmm and store in reg. The upper bits of r32 or r64 are filled with zeros.
	{ NULL, FCML_AMT_SSE_SIMD, 0x0000, 0x005A8000, { 0x0F, 0x50, 0x00 }, { FCML_OP_MODRM_R_32_W, FCML_OP_RM( FCML_REG_SIMD, FCML_EOS_OWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	{ NULL, FCML_AMT_SSE_SIMD, 0x0000, 0x009A8000, { 0x0F, 0x50, 0x00 }, { FCML_OP_MODRM_R_64_W, FCML_OP_RM( FCML_REG_SIMD, FCML_EOS_OWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.128.0F 50 /r VMOVMSKPS reg,xmm2
	// VEX.256.0F 50 /r VMOVMSKPS reg,ymm2
	{ "vmovmskps", FCML_AMT_AVX_SIMD, 0x0180, 0x005A8000, { 0x0F, 0x50, 0x00 }, { FCML_OP_MODRM_R_32_W, FCML_OP_RM( FCML_REG_SIMD, FCML_EOS_L, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	{ "vmovmskps", FCML_AMT_AVX_SIMD, 0x0180, 0x009A8000, { 0x0F, 0x50, 0x00 }, { FCML_OP_MODRM_R_64_W, FCML_OP_RM( FCML_REG_SIMD, FCML_EOS_L, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_MOVNTDQA[] = {
	// 66 0F 38 2A /r MOVNTDQA xmm1, m128 A Valid Valid Move double quadword from m128 to xmm using non-temporal hint if WC memory type.
	{ NULL, FCML_AMT_SSE41_SIMD, 0x1001, 0x80EC8000, { 0x0F, 0x38, 0x2A }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_RM( FCML_REG_SIMD, FCML_EOS_UNDEFINED, FCML_EOS_OWORD, FCML_RMF_M ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.128.66.0F38 2A /r VMOVNTDQA xmm1,m128
	{ "vmovntdqa", FCML_AMT_AVX_SIMD, 0x11C0, 0x80EC8000, { 0x0F, 0x38, 0x2A }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_M_SIMD_L, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.256.66.0F38.WIG 2A /r VMOVNTDQA ymm1,m256
	{ "vmovntdqa", FCML_AMT_AVX2_SIMD, 0x11A0, 0x80EC8000, { 0x0F, 0x38, 0x2A }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_MODRM_M_SIMD_L, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_MOVNTDQ[] = {
	// 66 0F E7 /r MOVNTDQ m128, xmm A Valid Valid Move double quadword from xmm to m128 using non-temporal hint.
	{ NULL, FCML_AMT_SSE2, 0x1001, 0x80D88000, { 0x0F, 0xE7, 0x00 }, { FCML_OP_RM( FCML_REG_SIMD, FCML_EOS_UNDEFINED, FCML_EOS_XWORD, FCML_RMF_M ) | FCML_OA_W, FCML_OP_MODRM_R_XMM , FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.128.66.0F E7 /r VMOVNTDQ m128,xmm1
	{ "vmovntdq", FCML_AMT_AVX_SIMD, 0x11C0, 0x80D88000, { 0x0F, 0xE7, 0x00 }, { FCML_OP_MODRM_M_XMM_W, FCML_OP_MODRM_R_XMM, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_MOVNTI[] = {
	// 0F C3 /r MOVNTI m32, r32 A Valid Valid Move doubleword from r32 to m32 using non-temporal hint.
	{ NULL, FCML_AMT_SSE2, 0x0010, 0x83D88000, { 0x0F, 0xC3, 0x00 }, { FCML_OP_RM( FCML_REG_UNDEFINED, FCML_EOS_UNDEFINED, FCML_EOS_DWORD, FCML_RMF_M ) | FCML_OA_W, FCML_OP_MODRM_R_32 , FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// REX.W + 0F C3 /r MOVNTI m64, r64 A Valid N.E. Move quadword from r64 to m64 using non-temporal hint.
	{ NULL, FCML_AMT_SSE2, 0x0008, 0x84988000, { 0x0F, 0xC3, 0x00 }, { FCML_OP_RM( FCML_REG_UNDEFINED, FCML_EOS_UNDEFINED, FCML_EOS_QWORD, FCML_RMF_M ) | FCML_OA_W, FCML_OP_MODRM_R_64 , FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_MOVNTPD[] = {
	// 66 0F 2B /r MOVNTPD m128, xmm A Valid Valid Move packed doubleprecision floating-point values from xmm to m128 using non-temporal hint.
	{ NULL, FCML_AMT_SSE2, 0x1001, 0x80D88000, { 0x0F, 0x2B, 0x00 }, { FCML_OP_RM( FCML_REG_SIMD, FCML_EOS_UNDEFINED, FCML_EOS_XWORD, FCML_RMF_M ) | FCML_OA_W, FCML_OP_MODRM_R_XMM , FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.128.66.0F 2B /r VMOVNTPD m128,xmm1
	{ "vmovntpd", FCML_AMT_AVX_SIMD, 0x11C0, 0x80D88000, { 0x0F, 0x2B, 0x00 }, { FCML_OP_MODRM_M_XMM_W, FCML_OP_MODRM_R_XMM, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_MOVNTPS[] = {
	// 0F 2B /r MOVNTPS m128, xmm A Valid Valid Move packed singleprecision floating-point values from xmm to m128 using non-temporal hint.
	{ NULL, FCML_AMT_SSE_SIMD, 0x0000, 0x80D88000, { 0x0F, 0x2B, 0x00 }, { FCML_OP_RM( FCML_REG_SIMD, FCML_EOS_UNDEFINED, FCML_EOS_OWORD, FCML_RMF_M ) | FCML_OA_W, FCML_OP_MODRM_R_XMM , FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.128.0F 2B /r VMOVNTPS m128, xmm1
	{ "vmovntps", FCML_AMT_AVX_SIMD, 0x01C0, 0x80D88000, { 0x0F, 0x2B, 0x00 }, { FCML_OP_MODRM_M_XMM_W, FCML_OP_MODRM_R_XMM, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_MOVNTSD[] = {
	// MOVNTSD mem64, xmm F2 0F 2B /r
	{ NULL, FCML_AMT_SSE4A, 0x2000, 0x80D88000, { 0x0F, 0x2B, 0x00 }, { FCML_OP_RM( FCML_REG_UNDEFINED, FCML_EOS_UNDEFINED, FCML_EOS_QWORD, FCML_RMF_M ) | FCML_OA_W, FCML_OP_MODRM_R_XMM , FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_MOVNTSS[] = {
	// MOVNTSS mem32, xmm F3 0F 2B /r
	{ NULL, FCML_AMT_SSE4A, 0x4000, 0x80D88000, { 0x0F, 0x2B, 0x00 }, { FCML_OP_RM( FCML_REG_UNDEFINED, FCML_EOS_UNDEFINED, FCML_EOS_DWORD, FCML_RMF_M ) | FCML_OA_W, FCML_OP_MODRM_R_XMM , FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_MOVNTQ[] = {
	// 0F E7 /r MOVNTQ m64, mm A Valid Valid Move quadword from mm to m64 using non-temporal hint.
	{ NULL, FCML_AMT_SSE_SIMD, 0x0000, 0x80D88000, { 0x0F, 0xE7, 0x00 }, { FCML_OP_RM( FCML_REG_UNDEFINED, FCML_EOS_UNDEFINED, FCML_EOS_MWORD, FCML_RMF_M ) | FCML_OA_W, FCML_OP_MODRM_R_MMX , FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_MOVQ[] = {
	// 0F 6F /r MOVQ mm, mm/m64 A Valid Valid Move quadword from mm/m64 to mm.
	{ NULL, FCML_AMT_MMX_SIMD, 0x0000, 0x00D88000, { 0x0F, 0x6F, 0x00 }, { FCML_OP_MODRM_R_MMX_W, FCML_OP_MODRM_RM_MMX, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 0F 7F /r MOVQ mm/m64, mm B Valid Valid Move quadword from mm to mm/m64.
	{ NULL, FCML_AMT_MMX_SIMD, 0x0000, 0x00D88000, { 0x0F, 0x7F, 0x00 }, { FCML_OP_MODRM_RM_MMX_W, FCML_OP_MODRM_R_MMX, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// F3 0F 7E MOVQ xmm1, xmm2/m64 A Valid Valid Move quadword from xmm2/mem64 to xmm1.
	{ NULL, FCML_AMT_SSE2_SIMD, 0x4001, 0x00D88000, { 0x0F, 0x7E, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 66 0F D6 MOVQ xmm2/m64, xmm1 B Valid Valid Move quadword from xmm1 to xmm2/mem64.
	{ NULL, FCML_AMT_SSE2_SIMD, 0x1001, 0x00D88000, { 0x0F, 0xD6, 0x00 }, { FCML_OP_MODRM_RM_XMM_64_W, FCML_OP_MODRM_R_XMM, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.128.F3.0F 7E /r VMOVQ xmm1,xmm2
	// VEX.128.F3.0F 7E /r VMOVQ xmm1,m64
	{ "vmovq", FCML_AMT_AVX_SIMD, 0x41C0, 0x00D88000, { 0x0F, 0x7E, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.128.66.0F D6 /r VMOVQ xmm1/m64,xmm2
	{ "vmovq", FCML_AMT_AVX_SIMD, 0x41C0, 0x00D88000, { 0x0F, 0xD6, 0x00 }, { FCML_OP_MODRM_RM_XMM_64_W, FCML_OP_MODRM_R_XMM, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }

};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_MOVQ2DQ[] = {
	// F3 0F D6 MOVQ2DQ xmm, mm A Valid Valid Move quadword from mmx to low quadword of xmm.
	{ NULL, FCML_AMT_SSE2_SIMD, 0x4001, 0x00DA8000, { 0x0F, 0xD6, 0x00 }, { FCML_OP_RM( FCML_REG_SIMD, FCML_EOS_OWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ) | FCML_OA_W, FCML_OP_MODRM_R_MMX, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_MOVS[] = {
	// A4 MOVS m8, m8 A Valid Valid For legacy mode, Move byte from address DS:(E)SI to ES:(E)DI. For 64-bit mode move byte from address (R|E)SI to (R|E)DI.
    // A4 MOVSB A Valid Valid For legacy mode, Move byte from address DS:(E)SI to ES:(E)DI. For 64-bit mode move byte from address (R|E)SI to (R|E)DI.
	{ "movs;movsb[ts]", FCML_AMT_GPI, 0x0004, 0x00C40000, { 0xA4, 0x00, 0x00 },
			{ FCML_OP_EXPLICIT_GPS_REG_ADDRESSING( FCML_REG_SI, FCML_EOS_BYTE, FCML_SEG_ENCODE_REGISTER( FCML_REG_DS, FCML_SEG_ALLOW_OVERRIDE ) ),
			FCML_OP_EXPLICIT_GPS_REG_ADDRESSING( FCML_REG_DI, FCML_EOS_BYTE, FCML_SEG_ENCODE_REGISTER( FCML_REG_ES, FCML_SEG_DENY_OVERRIDE ) ),
			FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// A5 MOVS m16, m16 A Valid Valid For legacy mode, move word from address DS:(E)SI to ES:(E)DI. For 64-bit mode move word at address (R|E)SI to (R|E)DI.
	// A5 MOVS m32, m32 A Valid Valid For legacy mode, move dword from address DS:(E)SI to ES:(E)DI. For 64-bit mode move dword from address (R|E)SI to (R|E)DI.
	// REX.W + A5 MOVS m64, m64 A Valid N.E. Move qword from address (R|E)SI to (R|E)DI.
    // A5 MOVSW A Valid Valid For legacy mode, move word from address DS:(E)SI to ES:(E)DI. For 64-bit mode move word at address (R|E)SI to (R|E)DI.
    // A5 MOVSD A Valid Valid For legacy mode, move dword from address DS:(E)SI to ES:(E)DI. For 64-bit mode move dword from address (R|E)SI to (R|E)DI. REX.W + A5 MOVSQ A Valid N.E. Move qword from address
	{ "movs;movsw[ts,ow,a*];movsd[ts,od,a*];movsq[ts,oq,a*]", FCML_AMT_GPI, 0x0004, 0x00C40000, { 0xA5, 0x00, 0x00 },
			{ FCML_OP_EXPLICIT_GPS_REG_ADDRESSING( FCML_REG_SI, FCML_EOS_EOSA,FCML_SEG_ENCODE_REGISTER( FCML_REG_DS, FCML_SEG_ALLOW_OVERRIDE ) ),
			FCML_OP_EXPLICIT_GPS_REG_ADDRESSING( FCML_REG_DI, FCML_EOS_EOSA,FCML_SEG_ENCODE_REGISTER( FCML_REG_ES, FCML_SEG_DENY_OVERRIDE ) ),
			FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_MOVSD[] = {
	// F2 0F 10 /r MOVSD xmm1, xmm2/m64 A Valid Valid Move scalar doubleprecision floating-point value from xmm2/m64 to xmm1 register.
	{ NULL, FCML_AMT_SSE2_SIMD, 0x2000, 0x00D88000, { 0x0F, 0x10, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// F2 0F 11 /r MOVSD xmm2/m64, xmm1 B Valid Valid Move scalar doubleprecision floating-point value from xmm1 register to xmm2/m64.
	{ NULL, FCML_AMT_SSE2_SIMD, 0x2000, 0x00D88000, { 0x0F, 0x11, 0x00 }, { FCML_OP_MODRM_RM_XMM_64_W, FCML_OP_MODRM_R_XMM, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.F2.0F 10 /r VMOVSD xmm1,xmm2,xmm3
	{ "vmovsd", FCML_AMT_AVX_SIMD, 0x20C0, 0x00DA8000, { 0x0F, 0x10, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_RM( FCML_REG_SIMD, FCML_EOS_OWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.F2.0F 11 /r VMOVSD xmm1,xmm2,xmm3
	{ "vmovsd", FCML_AMT_AVX_SIMD, 0x20C0, 0x00DA8000, { 0x0F, 0x11, 0x00 }, { FCML_OP_RM( FCML_REG_SIMD, FCML_EOS_OWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ) | FCML_OA_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_R_XMM, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.128.F2.0F 10 /r VMOVSD xmm1,m64
	{ "vmovsd", FCML_AMT_AVX_SIMD, 0x21C0, 0x80D88000, { 0x0F, 0x10, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_M_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.128.F2.0F 11 /r VMOVSD m64,xmm1
	{ "vmovsd", FCML_AMT_AVX_SIMD, 0x21C0, 0x80D88000, { 0x0F, 0x11, 0x00 }, { FCML_OP_MODRM_M_64_W, FCML_OP_MODRM_R_XMM, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_MOVSHDUP[] = {
	// F3 0F 16 /r MOVSHDUP xmm1, xmm2/m128 A Valid Valid Move two single-precisionfloating-point values from the higher 32-bit operand of each qword in xmm2/m128 to xmm1 and duplicate each 32-bit operand to the lower 32-bits of each qword.
	{ NULL, FCML_AMT_SSE3_SIMD, 0x4001, 0x00D88000, { 0x0F, 0x16, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.128.F3.0F 16 /r VMOVSHDUP xmm1,xmm2/m128
	// VEX.256.F3.0F 16 /r VMOVSHDUP ymm1,ymm2/m256
	{ "vmovshdup", FCML_AMT_AVX_SIMD, 0x4180, 0x00D88000, { 0x0F, 0x16, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_MODRM_RM_SIMD_L, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_MOVSLDUP[] = {
	// F3 0F 12 /r MOVSLDUP xmm1, xmm2/m128 A Valid Valid Move two single-precision floating-point values from the lower 32-bit operand ofeach qword in xmm2/m128 to xmm1 and duplicate each 32-bit operand to the higher 32-bits of each qword.
	{ NULL, FCML_AMT_SSE3_SIMD, 0x4001, 0x00D88000, { 0x0F, 0x12, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.128.F3.0F 12 /r VMOVSLDUP xmm1,xmm2/m128
	// VEX.256.F3.0F 12 /r VMOVSLDUP ymm1,ymm2/m256
	{ "vmovsldup", FCML_AMT_AVX_SIMD, 0x4180, 0x00D88000, { 0x0F, 0x12, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_MODRM_RM_SIMD_L, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_MOVSS[] = {
	// F3 0F 10 /r MOVSS xmm1, xmm2/m32 A Valid Valid Move scalar single-precision floating-point value from xmm2/m32 to xmm1 register.
	{ NULL, FCML_AMT_SSE_SIMD, 0x4001, 0x00D88000, { 0x0F, 0x10, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_32, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// F3 0F 11 /r MOVSS xmm2/m32, xmm B Valid Valid Move scalar single-precision floating-point value from xmm1 register to
	{ NULL, FCML_AMT_SSE_SIMD, 0x4001, 0x00D88000, { 0x0F, 0x11, 0x00 }, { FCML_OP_MODRM_RM_XMM_32_W, FCML_OP_MODRM_R_XMM, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.F3.0F 10 /r VMOVSS xmm1,xmm2,xmm3
	{ "vmovss", FCML_AMT_AVX_SIMD, 0x40C0, 0x00DA8000, { 0x0F, 0x10, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_RM( FCML_REG_SIMD, FCML_EOS_OWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.F3.0F 11 /r VMOVSS xmm1,xmm2,xmm3
	{ "vmovss", FCML_AMT_AVX_SIMD, 0x40C0, 0x00DA8000, { 0x0F, 0x11, 0x00 }, { FCML_OP_RM( FCML_REG_SIMD, FCML_EOS_OWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ) | FCML_OA_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_R_XMM, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.128.F3.0F 10 /r VMOVSS xmm1,m32
	{ "vmovss", FCML_AMT_AVX_SIMD, 0x41C0, 0x80D88000, { 0x0F, 0x10, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_M_32, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.128.F3.0F 11 /r VMOVSS m32,xmm1
	{ "vmovss", FCML_AMT_AVX_SIMD, 0x41C0, 0x80D88000, { 0x0F, 0x11, 0x00 }, { FCML_OP_MODRM_M_32_W, FCML_OP_MODRM_R_XMM, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_MOVSX[] = {
	// 0F BE /r MOVSX r16, r/m8 A Valid Valid Move byte to word with sign-extension.
	// 0F BE /r MOVSX r32, r/m8 A Valid Valid Move byte to doubleword with sign-extension.
	// REX + 0F BE /r MOVSX r64, r/m8* A Valid N.E. Move byte to quadword with sign-extension.
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00D88000, { 0x0F, 0xBE, 0x00 }, { FCML_OP_MODRM_R_W, FCML_OP_MODRM_RM_8, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 0F BF /r MOVSX r32, r/m16 A Valid Valid Move word to doubleword, with sign-extension.
	{ NULL, FCML_AMT_GPI, 0x0000, 0x03D88000, { 0x0F, 0xBF, 0x00 }, { FCML_OP_MODRM_R_32_W, FCML_OP_MODRM_RM_16, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// REX.W + 0F BF /r MOVSX r64, r/m16 A Valid N.E. Move word to quadword with sign-extension.
	{ NULL, FCML_AMT_GPI, 0x0000, 0x04988000, { 0x0F, 0xBF, 0x00 }, { FCML_OP_MODRM_R_64_W, FCML_OP_MODRM_RM_16, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// REX.W** + 63 /r MOVSXD r64, r/m32 A Valid N.E. Move doubleword to quadword with signextension.
	{ "movsxd", FCML_AMT_GPI, 0x0000, 0x04848000, { 0x63, 0x00, 0x00 }, { FCML_OP_MODRM_R_64_W, FCML_OP_MODRM_RM_32, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_MOVUPD[] = {
	// 66 0F 10 /r MOVUPD xmm1, xmm2/m128 A Valid Valid Move packed doubleprecision floating-point values from xmm2/m128 to xmm1.
	{ NULL, FCML_AMT_SSE2_SIMD, 0x1001, 0x00D88000, { 0x0F, 0x10, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 66 0F 11 /r MOVUPD xmm2/m128, xmm B Valid Valid Move packed doubleprecision floating-point values from xmm1 to xmm2/m128.
	{ NULL, FCML_AMT_SSE2_SIMD, 0x1001, 0x00D88000, { 0x0F, 0x11, 0x00 }, { FCML_OP_MODRM_RM_XMM_128_W, FCML_OP_MODRM_R_XMM, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.128.66.0F 10 /r VMOVUPD xmm1,xmm2/m128
	// VEX.256.66.0F 10 /r VMOVUPD ymm1,ymm2/m256
	{ "vmovupd", FCML_AMT_AVX_SIMD, 0x1180, 0x00D88000, { 0x0F, 0x10, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_MODRM_RM_SIMD_L, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.128.66.0F 11 /r VMOVUPD xmm2/m128,xmm1
	// VEX.256.66.0F 11 /r VMOVUPD ymm2/m256,ymm1
	{ "vmovupd", FCML_AMT_AVX_SIMD, 0x1180, 0x00D88000, { 0x0F, 0x11, 0x00 }, { FCML_OP_MODRM_RM_SIMD_L_W, FCML_OP_MODRM_R_SIMD_L, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_MOVUPS[] = {
	// 0F 10 /r MOVUPS xmm1, xmm2/m128 A Valid Valid Move packed singleprecision floating-point values from xmm2/m128 to xmm1.
	{ NULL, FCML_AMT_SSE_SIMD, 0x0000, 0x00D88000, { 0x0F, 0x10, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 0F 11 /r MOVUPS xmm2/m128, xmm1 B Valid Valid Move packed singleprecision floating-point values from xmm1 to xmm2/m128.
	{ NULL, FCML_AMT_SSE_SIMD, 0x0000, 0x00D88000, { 0x0F, 0x11, 0x00 }, { FCML_OP_MODRM_RM_XMM_128_W, FCML_OP_MODRM_R_XMM, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.128.0F 10 /r VMOVUPS xmm1,xmm2/m128
	// VEX.256.0F 10 /r VMOVUPS ymm1,ymm2/m256
	{ "vmovups", FCML_AMT_AVX_SIMD, 0x0180, 0x00D88000, { 0x0F, 0x10, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_MODRM_RM_SIMD_L, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.128.0F 11 /r VMOVUPS xmm2/m128,xmm1
	// VEX.256.0F 11 /r VMOVUPS ymm2/m256,ymm1
	{ "vmovups", FCML_AMT_AVX_SIMD, 0x0180, 0x00D88000, { 0x0F, 0x11, 0x00 }, { FCML_OP_MODRM_RM_SIMD_L_W, FCML_OP_MODRM_R_SIMD_L, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_MOVZX[] = {
	// 0F B6 /r MOVZX r16, r/m8 A Valid Valid Move byte to word with zero-extension.
	// 0F B6 /r MOVZX r32, r/m8 A Valid Valid Move byte to doubleword, zero-extension.
	// REX.W + 0F B6 /r MOVZX r64, r/m8* A Valid N.E. Move byte to quadword, zero-extension.
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00D88000, { 0x0F, 0xB6, 0x00 }, { FCML_OP_MODRM_R_W, FCML_OP_MODRM_RM_8, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 0F B7 /r MOVZX r32, r/m16 A Valid Valid Move word to doubleword, zero-extension.
	{ NULL, FCML_AMT_GPI, 0x0000, 0x03D88000, { 0x0F, 0xB7, 0x00 }, { FCML_OP_MODRM_R_32_W, FCML_OP_MODRM_RM_16, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// REX.W + 0F B7 /r MOVZX r64, r/m16 A Valid N.E. Move word to quadword, zero-extension.
	{ NULL, FCML_AMT_GPI, 0x0000, 0x04988000, { 0x0F, 0xB7, 0x00 }, { FCML_OP_MODRM_R_64_W, FCML_OP_MODRM_RM_16, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_MPSADBW[] = {
	// 66 0F 3A 42 /r ib MPSADBW xmm1, xmm2/m128, imm8 A Valid Valid Sums absolute 8-bit integer difference of adjacent groups of 4 byte integers in xmm1 and xmm2/m128 and writes the results in xmm1. Starting offsets within xmm1 and xmm2/m128 are determined by imm8.
	{ NULL, FCML_AMT_SSE41_SIMD, 0x1001, 0x00EC8000, { 0x0F, 0x3A, 0x42 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.66.0F3A 42 /r ib VMPSADBW xmm1,xmm2,xmm3/m128,imm8
	{ "vmpsadbw", FCML_AMT_AVX_SIMD, 0x10C0, 0x00EC8000, { 0x0F, 0x3A, 0x42 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_128, FCML_OP_IB, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.256.66.0F3A.WIG 42 /r ib VMPSADBW ymm1,ymm2,ymm3/m256,imm8
	{ "vmpsadbw", FCML_AMT_AVX2_SIMD, 0x10A0, 0x00EC8000, { 0x0F, 0x3A, 0x42 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_YMM_256, FCML_OP_IB, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_MUL[] = {
	// F6 /4 MUL r/m8 A Valid Valid Unsigned multiply (AX AL r/m8).
	// REX + F6 /4 MUL r/m8* A Valid N.E. Unsigned multiply (AX AL r/m8).
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00C5A000, { 0xF6, 0x00, 0x00 }, { FCML_OP_MODRM_RM_8, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// F7 /4 MUL r/m16 A Valid Valid Unsigned multiply (DX:AX AX r/m16).
	// F7 /4 MUL r/m32 A Valid Valid Unsigned multiply (EDX:EAX EAX r/m32).
	// REX.W + F7 /4 MUL r/m64 A Valid N.E. Unsigned multiply (RDX:RAX RAX r/m64.
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00C5A000, { 0xF7, 0x00, 0x00 }, { FCML_OP_MODRM_RM, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_MULPD[] = {
	// 66 0F 59 /r MULPD xmm1, xmm2/m128 A Valid Valid Multiply packed doubleprecision floating-point values in xmm2/m128 by xmm1.
	{ NULL, FCML_AMT_SSE2_SIMD, 0x1001, 0x00D88000, { 0x0F, 0x59, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.66.0F 59 /r VMULPD xmm1,xmm2,xmm3/m128
	// VEX.NDS.256.66.0F 59 /r VMULPD ymm1,ymm2,ymm3/m256
	{ "vmulpd", FCML_AMT_AVX_SIMD, 0x1080, 0x00D88000, { 0x0F, 0x59, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_MULPS[] = {
	// 0F 59 /r MULPS xmm1, xmm2/m128 A Valid Valid Multiply packed singleprecision floating-point values in xmm2/mem by xmm1.
	{ NULL, FCML_AMT_SSE_SIMD, 0x0000, 0x00D88000, { 0x0F, 0x59, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.0F 59 /r VMULPS xmm1,xmm2,xmm3/m128
	// VEX.NDS.256.0F 59 /r VMULPS ymm1,ymm2,ymm3/m256
	{ "vmulps", FCML_AMT_AVX_SIMD, 0x0080, 0x00D88000, { 0x0F, 0x59, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_MULSD[] = {
	// F2 0F 59 /r MULSD xmm1, xmm2/m64 A Valid Valid Multiply the low doubleprecision floating-point value in xmm2/mem64 by low double-precision floating-point value in xmm1.
	{ NULL, FCML_AMT_SSE2_SIMD, 0x2001, 0x00D88000, { 0x0F, 0x59, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.F2.0F 59 /r VMULSD xmm1,xmm2,xmm3/m64
	{ "vmulsd", FCML_AMT_AVX_SIMD, 0x20C0, 0x00D88000, { 0x0F, 0x59, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L_64, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_MULSS[] = {
	// F3 0F 59 /r MULSS xmm1, xmm2/m32 A Valid Valid Multiply the low singleprecision floating-point value in xmm2/mem by the low single-precision floating-point value in xmm1.
	{ NULL, FCML_AMT_SSE_SIMD, 0x4001, 0x00D88000, { 0x0F, 0x59, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_32, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.F3.0F 59 /r VMULSS xmm1,xmm2,xmm3/m32
	{ "vmulss", FCML_AMT_AVX_SIMD, 0x40C0, 0x00D88000, { 0x0F, 0x59, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L_32, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_MWAIT[] = {
	// 0F 01 C9 MWAIT A Valid Valid A hint that allow the processor to stop instruction execution and enter an implementationdependent optimized state until occurrence of a class of events.
	{ NULL, FCML_AMT_SSE3, 0x0000, 0x00EC0000, { 0x0F, 0x01, 0xC9 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_NEG[] = {
	// F6 /3 NEG r/m8 M Valid Valid Two's complement negate r/m8.
	// REX + F6 /3 NEG r/m8* M Valid N.E. Two's complement negate r/m8.
	{ NULL, FCML_AMT_GPI, 0x0807, 0x00C59800, { 0xF6, 0x00, 0x00 }, { FCML_OP_MODRM_RM_8_W, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// F7 /3 NEG r/m16 M Valid Valid Two's complement negate r/m16.
	// F7 /3 NEG r/m32 M Valid Valid Two's complement negate r/m32.
	// REX.W + F7 /3 NEG r/m64 M Valid N.E. Two's complement negate r/m64.
	{ NULL, FCML_AMT_GPI, 0x0807, 0x00C59800, { 0xF7, 0x00, 0x00 }, { FCML_OP_MODRM_RM_W, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_NOP[] = {
	// 90 NOP NP Valid Valid One byte no-operation instruction.
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00C40000, { 0x90, 0x00, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 0F 1F /0 NOP r/m16 M Valid Valid Multi-byte no-operation instruction.
	// 0F 1F /0 NOP r/m32 M Valid Valid Multi-byte no-operation instruction.
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00D98000, { 0x0F, 0x1F, 0x00 }, { FCML_OP_MODRM_RM_W, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_NOT[] = {
	// F6 /2 NOT r/m8 M Valid Valid Reverse each bit of r/m8.
	// REX + F6 /2 NOT r/m8* M Valid N.E. Reverse each bit of r/m8.
	{ NULL, FCML_AMT_GPI, 0x0807, 0x00C59000, { 0xF6, 0x00, 0x00 }, { FCML_OP_MODRM_RM_8_W, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// F7 /2 NOT r/m16 M Valid Valid Reverse each bit of r/m16.
	// F7 /2 NOT r/m32 M Valid Valid Reverse each bit of r/m32.
	// REX.W + F7 /2 NOT r/m64 M Valid N.E. Reverse each bit of r/m64.
	{ NULL, FCML_AMT_GPI, 0x0807, 0x00C59000, { 0xF7, 0x00, 0x00 }, { FCML_OP_MODRM_RM_W, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_OR[] = {
	// 0C ib OR AL, imm8 I Valid Valid AL OR imm8.
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00C40000, { 0x0C, 0x00, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_AL, FCML_EOS_BYTE ), FCML_OP_IB, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 0D iw OR AX, imm16 I Valid Valid AX OR imm16.
	// 0D id OR EAX, imm32 I Valid Valid EAX OR imm32.
	{ NULL, FCML_AMT_GPI, 0x0010, 0x03C40000, { 0x0D, 0x00, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_AL, FCML_EOS_EOSA ) | FCML_OA_W, FCML_OP_IMM_EOSA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// REX.W + 0D id OR RAX, imm32 I Valid N.E. RAX OR imm32 (sign-extended).
	{ NULL, FCML_AMT_GPI, 0x0008, 0x04840000, { 0x0D, 0x00, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_AL, FCML_EOS_EOSA ) | FCML_OA_W, FCML_OP_ID_EX_EOSA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 80 /1 ib OR r/m8, imm8 MI Valid Valid r/m8 OR imm8.
	// REX + 80 /1 ib OR r/m8*, imm8 MI Valid N.E. r/m8 OR imm8.
	{ NULL, FCML_AMT_GPI, 0x0807, 0x00C58800, { 0x80, 0x00, 0x00 }, { FCML_OP_MODRM_RM_8_W, FCML_OP_IB, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 81 /1 iw OR r/m16, imm16 MI Valid Valid r/m16 OR imm16.
	// 81 /1 id OR r/m32, imm32 MI Valid Valid r/m32 OR imm32.
	{ NULL, FCML_AMT_GPI, 0x0817, 0x03C58800, { 0x81, 0x00, 0x00 }, { FCML_OP_MODRM_RM_W, FCML_OP_IMM_EOSA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// REX.W + 81 /1 id OR r/m64, imm32 MI Valid N.E. r/m64 OR imm32 (sign-extended).
	{ NULL, FCML_AMT_GPI, 0x080F, 0x04858800, { 0x81, 0x00, 0x00 }, { FCML_OP_MODRM_RM_W, FCML_OP_ID_EX_EOSA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 83 /1 ib OR r/m16, imm8 MI Valid Valid r/m16 OR imm8 (sign-extended).
	// 83 /1 ib OR r/m32, imm8 MI Valid Valid r/m32 OR imm8 (sign-extended).
	{ NULL, FCML_AMT_GPI, 0x0817, 0x03C58800, { 0x83, 0x00, 0x00 }, { FCML_OP_MODRM_RM_W, FCML_OP_IB_EX_EOSA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// REX.W + 83 /1 ib OR r/m64, imm8 MI Valid N.E. r/m64 OR imm8 (sign-extended).
	{ NULL, FCML_AMT_GPI, 0x080F, 0x04858800, { 0x83, 0x00, 0x00 }, { FCML_OP_MODRM_RM_W, FCML_OP_IB_EX_EOSA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 08 /r OR r/m8, r8 MR Valid Valid r/m8 OR r8.
	// REX + 08 /r OR r/m8*, r8* MR Valid N.E. r/m8 OR r8.
	{ NULL, FCML_AMT_GPI, 0x0807, 0x00C48000, { 0x08, 0x00, 0x00 }, { FCML_OP_MODRM_RM_8_W, FCML_OP_MODRM_R_8, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 09 /r OR r/m16, r16 MR Valid Valid r/m16 OR r16.
	// 09 /r OR r/m32, r32 MR Valid Valid r/m32 OR r32.
	// REX.W + 09 /r OR r/m64, r64 MR Valid N.E. r/m64 OR r64.
	{ NULL, FCML_AMT_GPI, 0x0807, 0x00C48000, { 0x09, 0x00, 0x00 }, { FCML_OP_MODRM_RM_W, FCML_OP_MODRM_R, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 0A /r OR r8, r/m8 RM Valid Valid r8 OR r/m8.
	// REX + 0A /r OR r8*, r/m8* RM Valid N.E. r8 OR r/m8.
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00C48000, { 0x0A, 0x00, 0x00 }, { FCML_OP_MODRM_R_8_W, FCML_OP_MODRM_RM_8, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 0B /r OR r16, r/m16 RM Valid Valid r16 OR r/m16.
	// 0B /r OR r32, r/m32 RM Valid Valid r32 OR r/m32.
	// REX.W + 0B /r OR r64, r/m64 RM Valid N.E. r64 OR r/m64.
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00C48000, { 0x0B, 0x00, 0x00 }, { FCML_OP_MODRM_R_W, FCML_OP_MODRM_RM, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_ORPD[] = {
	// 66 0F 56 /r ORPD xmm1,xmm2/m128
	{ NULL, FCML_AMT_SSE2_SIMD, 0x1001, 0x00D88000, { 0x0F, 0x56, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.66.0F 56 /r VORPD xmm1,xmm2,xmm3/m128
	// VEX.NDS.256.66.0F 56 /r VORPD ymm1,ymm2,ymm3/m256
	{ "vorpd", FCML_AMT_AVX_SIMD, 0x1080, 0x00D88000, { 0x0F, 0x56, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_ORPS[] = {
	// 0F 56 /r ORPS xmm1, xmm2/m128
	{ NULL, FCML_AMT_SSE_SIMD, 0x0000, 0x00D88000, { 0x0F, 0x56, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.0F 56 /r VORPS xmm1,xmm2,xmm3/m128
	// VEX.NDS.256.0F 56 /r VORPS ymm1,ymm2,ymm3/m256
	{ "vorps", FCML_AMT_AVX_SIMD, 0x0080, 0x00D88000, { 0x0F, 0x56, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_OUT[] = {
	// E6 ib OUT imm8, AL I Valid Valid Output byte in AL to I/O port address imm8.
	{ NULL, FCML_AMT_GPI, 0x0000, 0x07C40000, { 0xE6, 0x00, 0x00 }, { FCML_OP_IB, FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_AL, FCML_EOS_BYTE ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// E7 ib OUT imm8, AX I Valid Valid Output word in AX to I/O port address imm8.
	{ NULL, FCML_AMT_GPI, 0x0000, 0x01C40000, { 0xE7, 0x00, 0x00 }, { FCML_OP_IB, FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_AL, FCML_EOS_WORD), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// E7 ib OUT imm8, EAX I Valid Valid Output doubleword in EAX to I/O port address imm8.
	{ NULL, FCML_AMT_GPI, 0x0000, 0x06C40000, { 0xE7, 0x00, 0x00 }, { FCML_OP_IB, FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_AL, FCML_EOS_DWORD), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// EE OUT DX, AL NP Valid Valid Output byte in AL to I/O port address in DX.
	{ NULL, FCML_AMT_GPI, 0x0000, 0x07C40000, { 0xEE, 0x00, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_DX, FCML_EOS_WORD ), FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_AL, FCML_EOS_BYTE ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// EF OUT DX, AX NP Valid Valid Output word in AX to I/O port address in DX.
	{ NULL, FCML_AMT_GPI, 0x0000, 0x01C40000, { 0xEF, 0x00, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_DX, FCML_EOS_WORD ), FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_AL, FCML_EOS_WORD ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// EF OUT DX, EAX NP Valid Valid Output doubleword in EAX to I/O port address in DX.
	{ NULL, FCML_AMT_GPI, 0x0000, 0x06C40000, { 0xEF, 0x00, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_DX, FCML_EOS_WORD ), FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_AL, FCML_EOS_DWORD ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};


struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_OUTS[] = {
	// 6E OUTS DX, m8 NP Valid Valid Output byte from memory location specified in DS:(E)SI or RSI to I/O port specified in DX.
	{ "outs;outsb[ts]", FCML_AMT_GPI, 0x0004, 0x07C40000, { 0x6E, 0x00, 0x00 },
			{ FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_DX, FCML_EOS_WORD ),
			FCML_OP_EXPLICIT_GPS_REG_ADDRESSING( FCML_REG_DI, FCML_EOS_BYTE, FCML_SEG_ENCODE_REGISTER( FCML_REG_ES, FCML_SEG_DENY_OVERRIDE ) ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 6F OUTS DX, m16 NP Valid Valid Output word from memory location specified in DS:(E)SI or RSI to I/O port specified in DX.
	{ "outs;outsw[ts]", FCML_AMT_GPI, 0x0004, 0x01C40000, { 0x6F, 0x00, 0x00 },
			{ FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_DX, FCML_EOS_WORD ),
			FCML_OP_EXPLICIT_GPS_REG_ADDRESSING( FCML_REG_DI, FCML_EOS_WORD, FCML_SEG_ENCODE_REGISTER( FCML_REG_ES, FCML_SEG_DENY_OVERRIDE ) ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 6F OUTS DX, m32 NP Valid Valid Output doubleword from memory location specified in DS:(E)SI or RSI to I/O port specified in DX.
	{ "outs;outsd[ts]", FCML_AMT_GPI, 0x0004, 0x06C40000, { 0x6F, 0x00, 0x00 },
			{ FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_DX, FCML_EOS_WORD ),
			FCML_OP_EXPLICIT_GPS_REG_ADDRESSING( FCML_REG_DI, FCML_EOS_DWORD, FCML_SEG_ENCODE_REGISTER( FCML_REG_ES, FCML_SEG_DENY_OVERRIDE ) ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PABS[] = {
	// 0F 38 1C /r1 PABSB mm1,mm2/m64
	{ "pabsb", FCML_AMT_SSSE3_SIMD, 0x0000, 0x00EC8000, { 0x0F, 0x38, 0x1C }, { FCML_OP_MODRM_R_MMX_W, FCML_OP_MODRM_RM_MMX, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 0F 38 1D /r1 PABSW mm1,mm2/m64
	{ "pabsw", FCML_AMT_SSSE3_SIMD, 0x0000, 0x00EC8000, { 0x0F, 0x38, 0x1D }, { FCML_OP_MODRM_R_MMX_W, FCML_OP_MODRM_RM_MMX, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 0F 38 1E /r1 PABSD mm1,mm2/m64
	{ "pabsd", FCML_AMT_SSSE3_SIMD, 0x0000, 0x00EC8000, { 0x0F, 0x38, 0x1E }, { FCML_OP_MODRM_R_MMX_W, FCML_OP_MODRM_RM_MMX, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 66 0F 38 1C /r PABSB xmm1,xmm2/m128
	{ "pabsb", FCML_AMT_SSSE3_SIMD, 0x1001, 0x00EC8000, { 0x0F, 0x38, 0x1C }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 66 0F 38 1D /r PABSW xmm1,xmm2/m128
	{ "pabsw", FCML_AMT_SSSE3_SIMD, 0x1001, 0x00EC8000, { 0x0F, 0x38, 0x1D }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 66 0F 38 1E /r PABSD xmm1,xmm2/m128
	{ "pabsd", FCML_AMT_SSSE3_SIMD, 0x1001, 0x00EC8000, { 0x0F, 0x38, 0x1E }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.128.66.0F38 1C /r VPABSB xmm1,xmm2/m128
	{ "vpabsb", FCML_AMT_AVX_SIMD, 0x11C0, 0x00EC8000, { 0x0F, 0x38, 0x1C }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.128.66.0F38 1D /r VPABSW xmm1,xmm2/m128
	{ "vpabsw", FCML_AMT_AVX_SIMD, 0x11C0, 0x00EC8000, { 0x0F, 0x38, 0x1D }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.128.66.0F38 1E /r VPABSD xmm1,xmm2/m128
	{ "vpabsd", FCML_AMT_AVX_SIMD, 0x11C0, 0x00EC8000, { 0x0F, 0x38, 0x1E }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.256.66.0F38.WIG 1C /r VPABSB ymm1, ymm2/m256
	{ "vpabsb", FCML_AMT_AVX2_SIMD, 0x11A0, 0x00EC8000, { 0x0F, 0x38, 0x1C }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_MODRM_RM_YMM_256, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.256.66.0F38.WIG 1D /r VPABSW ymm1, ymm2/m256
	{ "vpabsw", FCML_AMT_AVX2_SIMD, 0x11A0, 0x00EC8000, { 0x0F, 0x38, 0x1D }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_MODRM_RM_YMM_256, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.256.66.0F38.WIG 1E /r VPABSD ymm1, ymm2/m256
	{ "vpabsd", FCML_AMT_AVX2_SIMD, 0x11A0, 0x00EC8000, { 0x0F, 0x38, 0x1E }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_MODRM_RM_YMM_256, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PACKSS[] = {
	// 0F 63 /r1 PACKSSWB mm1,mm2/m64
	{ "packsswb", FCML_AMT_MMX_SIMD, 0x0000, 0x00D88000, { 0x0F, 0x63, 0x00 }, { FCML_OP_MODRM_R_MMX_W, FCML_OP_MODRM_RM_MMX, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 0F 6B /r1 PACKSSDW mm1,mm2/m64
	{ "packssdw", FCML_AMT_MMX_SIMD, 0x0000, 0x00D88000, { 0x0F, 0x6B, 0x00 }, { FCML_OP_MODRM_R_MMX_W, FCML_OP_MODRM_RM_MMX, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 66 0F 63 /r PACKSSWB xmm1,xmm2/m128
	{ "packsswb", FCML_AMT_SSE2_SIMD, 0x1001, 0x00D88000, { 0x0F, 0x63, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 66 0F 6B /r PACKSSDW xmm1,xmm2/m128
	{ "packssdw", FCML_AMT_SSE2_SIMD, 0x1001, 0x00D88000, { 0x0F, 0x6B, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.66.0F.WIG 63 /r VPACKSSWB xmm1,xmm2,xmm3/m128
	{ "vpacksswb", FCML_AMT_AVX_SIMD, 0x10C0, 0x00D88000, { 0x0F, 0x63, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.66.0F.WIG 6B /r VPACKSSDW xmm1,xmm2,xmm3/m128
	{ "vpackssdw", FCML_AMT_AVX_SIMD, 0x10C0, 0x00D88000, { 0x0F, 0x6B, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.256.66.0F.WIG 63 /r VPACKSSWB ymm1,ymm2,ymm3/m256
	{ "vpacksswb", FCML_AMT_AVX2_SIMD, 0x10A0, 0x00D88000, { 0x0F, 0x63, 0x00 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_YMM_256, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.256.66.0F.WIG 6B /r VPACKSSDW ymm1,ymm2,ymm3/m256
	{ "vpackssdw", FCML_AMT_AVX2_SIMD, 0x10A0, 0x00D88000, { 0x0F, 0x6B, 0x00 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_YMM_256, FCML_NA, FCML_NA }, FCML_AM_NONE }

};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PACKUSD[] = {
	// 66 0F 38 2B /r PACKUSDW xmm1,xmm2/m128
	{ "packusdw", FCML_AMT_SSE41_SIMD, 0x1001, 0x00EC8000, { 0x0F, 0x38, 0x2B }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.66.0F38.WIG 2B /r VPACKUSDW xmm1,xmm2,xmm3/m128
	{ "vpackusdw", FCML_AMT_AVX_SIMD, 0x10C0, 0x00EC8000, { 0x0F, 0x38, 0x2B }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.256.66.0F38.WIG 2B /r VPACKUSDW ymm1,ymm2,ymm3/m256
	{ "vpackusdw", FCML_AMT_AVX2_SIMD, 0x10A0, 0x00EC8000, { 0x0F, 0x38, 0x2B }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_YMM_256, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PACKUSW[] = {
	// 0F 67 /r1 PACKUSWB mm,mm/m64
	{ "packuswb", FCML_AMT_MMX_SIMD, 0x0000, 0x00D88000, { 0x0F, 0x67, 0x00 }, { FCML_OP_MODRM_R_MMX_W, FCML_OP_MODRM_RM_MMX, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 66 0F 67 /r PACKUSWB xmm1,xmm2/m128
	{ "packuswb", FCML_AMT_SSE2_SIMD, 0x1001, 0x00D88000, { 0x0F, 0x67, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.66.0F.WIG 67 /r VPACKUSWB xmm1,xmm2,xmm3/m128
	{ "vpackuswb", FCML_AMT_AVX_SIMD, 0x10C0, 0x00D88000, { 0x0F, 0x67, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.256.66.0F.WIG 67 /r VPACKUSWB ymm1,ymm2,ymm3/m256
	{ "vpackuswb", FCML_AMT_AVX2_SIMD, 0x10A0, 0x00D88000, { 0x0F, 0x67, 0x00 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_YMM_256, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PADD[] = {
	// 0F FC /r1 PADDB mm,mm/m64
	{ "paddb", FCML_AMT_MMX_SIMD, 0x0000, 0x00D88000, { 0x0F, 0xFC, 0x00 }, { FCML_OP_MODRM_R_MMX_W, FCML_OP_MODRM_RM_MMX, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 0F FD /r1 PADDW mm,mm/m64
	{ "paddw", FCML_AMT_MMX_SIMD, 0x0000, 0x00D88000, { 0x0F, 0xFD, 0x00 }, { FCML_OP_MODRM_R_MMX_W, FCML_OP_MODRM_RM_MMX, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 0F FE /r1 PADDD mm,mm/m64
	{ "paddd", FCML_AMT_MMX_SIMD, 0x0000, 0x00D88000, { 0x0F, 0xFE, 0x00 }, { FCML_OP_MODRM_R_MMX_W, FCML_OP_MODRM_RM_MMX, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 66 0F FC /r PADDB xmm1,xmm2/m128
	{ "paddb", FCML_AMT_SSE2_SIMD, 0x1001, 0x00D88000, { 0x0F, 0xFC, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 66 0F FD /r PADDW xmm1,xmm2/m128
	{ "paddw", FCML_AMT_SSE2_SIMD, 0x1001, 0x00D88000, { 0x0F, 0xFD, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 66 0F FE /r PADDD xmm1,xmm2/m128
	{ "paddd", FCML_AMT_SSE2_SIMD, 0x1001, 0x00D88000, { 0x0F, 0xFE, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.66.0F.WIG FC /r VPADDB xmm1,xmm2,xmm3/m128
	{ "vpaddb", FCML_AMT_AVX_SIMD, 0x10C0, 0x00D88000, { 0x0F, 0xFC, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.66.0F.WIG FD /r VPADDW xmm1,xmm2,xmm3/m128
	{ "vpaddw", FCML_AMT_AVX_SIMD, 0x10C0, 0x00D88000, { 0x0F, 0xFD, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.66.0F.WIG FE /r VPADDD xmm1,xmm2,xmm3/m128
	{ "vpaddd", FCML_AMT_AVX_SIMD, 0x10C0, 0x00D88000, { 0x0F, 0xFE, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.256.66.0F.WIG FC /r VPADDB ymm1,ymm2,ymm3/m256
	{ "vpaddb", FCML_AMT_AVX2_SIMD, 0x10A0, 0x00D88000, { 0x0F, 0xFC, 0x00 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_YMM_256, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.256.66.0F.WIG FD /r VPADDW ymm1,ymm2,ymm3/m256
	{ "vpaddw", FCML_AMT_AVX2_SIMD, 0x10A0, 0x00D88000, { 0x0F, 0xFD, 0x00 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_YMM_256, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.256.66.0F.WIG FE /r VPADDD ymm1,ymm2,ymm3/m256
	{ "vpaddd", FCML_AMT_AVX2_SIMD, 0x10A0, 0x00D88000, { 0x0F, 0xFE, 0x00 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_YMM_256, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.256.66.0F.WIG D4 /r VPADDQ ymm1,ymm2,ymm3/m256
	{ "vpaddq", FCML_AMT_AVX2_SIMD, 0x10A0, 0x00D88000, { 0x0F, 0xD4, 0x00 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_YMM_256, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PADDS[] = {
	// 0F EC /r1 PADDSB mm,mm/m64
	{ "paddsb", FCML_AMT_MMX_SIMD, 0x0000, 0x00D88000, { 0x0F, 0xEC, 0x00 }, { FCML_OP_MODRM_R_MMX_W, FCML_OP_MODRM_RM_MMX, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 0F ED /r1 PADDSW mm,mm/m64
	{ "paddsw", FCML_AMT_MMX_SIMD, 0x0000, 0x00D88000, { 0x0F, 0xED, 0x00 }, { FCML_OP_MODRM_R_MMX_W, FCML_OP_MODRM_RM_MMX, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 66 0F EC /r PADDSB xmm1,xmm2/m128
	{ "paddsb", FCML_AMT_SSE2_SIMD, 0x1001, 0x00D88000, { 0x0F, 0xEC, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 66 0F ED /r PADDSW xmm1,xmm2/m128
	{ "paddsw", FCML_AMT_SSE2_SIMD, 0x1001, 0x00D88000, { 0x0F, 0xED, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.66.0F.WIG EC /r VPADDSB xmm1,xmm2,xmm3/m128
	{ "vpaddsb", FCML_AMT_AVX_SIMD, 0x10C0, 0x00D88000, { 0x0F, 0xEC, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.66.0F.WIG ED /r VPADDSW xmm1,xmm2,xmm3/m128
	{ "vpaddsw", FCML_AMT_AVX_SIMD, 0x10C0, 0x00D88000, { 0x0F, 0xED, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.256.66.0F.WIG EC /r VPADDSB ymm1,ymm2,ymm3/m256
	{ "vpaddsb", FCML_AMT_AVX2_SIMD, 0x10A0, 0x00D88000, { 0x0F, 0xEC, 0x00 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_YMM_256, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.256.66.0F.WIG ED /r VPADDSW ymm1,ymm2,ymm3/m256
	{ "vpaddsw", FCML_AMT_AVX2_SIMD, 0x10A0, 0x00D88000, { 0x0F, 0xED, 0x00 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_YMM_256, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PADDUS[] = {
	// 0F DC /r1 PADDUSB mm,mm/m64
	{ "paddusb", FCML_AMT_MMX_SIMD, 0x0000, 0x00D88000, { 0x0F, 0xDC, 0x00 }, { FCML_OP_MODRM_R_MMX_W, FCML_OP_MODRM_RM_MMX, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 0F DD /r1 PADDUSW mm,mm/m64
	{ "paddusw", FCML_AMT_MMX_SIMD, 0x0000, 0x00D88000, { 0x0F, 0xDD, 0x00 }, { FCML_OP_MODRM_R_MMX_W, FCML_OP_MODRM_RM_MMX, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 66 0F DC /r PADDUSB xmm1,xmm2/m128
	{ "paddusb", FCML_AMT_SSE2_SIMD, 0x1001, 0x00D88000, { 0x0F, 0xDC, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 66 0F DD /r PADDUSW xmm1,xmm2/m128
	{ "paddusw", FCML_AMT_SSE2_SIMD, 0x1001, 0x00D88000, { 0x0F, 0xDD, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.660F.WIG DC /r VPADDUSB xmm1,xmm2,xmm3/m128
	{ "vpaddusb", FCML_AMT_AVX_SIMD, 0x10C0, 0x00D88000, { 0x0F, 0xDC, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.66.0F.WIG DD /r VPADDUSW xmm1,xmm2,xmm3/m128
	{ "vpaddusw", FCML_AMT_AVX_SIMD, 0x10C0, 0x00D88000, { 0x0F, 0xDD, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.256.66.0F.WIG DC /r VPADDUSB ymm1,ymm2,ymm3/m256
	{ "vpaddusb", FCML_AMT_AVX2_SIMD, 0x10A0, 0x00D88000, { 0x0F, 0xDC, 0x00 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_YMM_256, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.256.66.0F.WIG DD /r VPADDUSW ymm1,ymm2,ymm3/m256
	{ "vpaddusw", FCML_AMT_AVX2_SIMD, 0x10A0, 0x00D88000, { 0x0F, 0xDD, 0x00 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_YMM_256, FCML_NA, FCML_NA }, FCML_AM_NONE },
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PADDQ[] = {
	// 0F D4 /r1 PADDQ mm1,mm2/m64
	{ NULL, FCML_AMT_SSE2_SIMD, 0x0000, 0x00D88000, { 0x0F, 0xD4, 0x00 }, { FCML_OP_MODRM_R_MMX_W, FCML_OP_MODRM_RM_MMX, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 66 0F D4 /r PADDQ xmm1,xmm2/m128
	{ NULL, FCML_AMT_SSE2_SIMD, 0x1000, 0x00D88000, { 0x0F, 0xD4, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.66.0F.WIG D4 /r VPADDQ xmm1,xmm2,xmm3/m128
	{ "vpaddq", FCML_AMT_AVX_SIMD, 0x10C0, 0x00D88000, { 0x0F, 0xD4, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PALIGNR[] = {
	// 0F 3A 0F PALIGNR mm1,mm2/m64,imm8
	{ NULL, FCML_AMT_SSSE3_SIMD, 0x0000, 0x00EC8000, { 0x0F, 0x3A, 0x00F }, { FCML_OP_MODRM_R_MMX_W, FCML_OP_MODRM_RM_MMX, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 66 0F 3A 0F PALIGNR xmm1,xmm2/m128,imm8
	{ NULL, FCML_AMT_SSSE3_SIMD, 0x1001, 0x00EC8000, { 0x0F, 0x3A, 0x00F }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.66.0F3A.WIG 0F /r ib VPALIGNR xmm1,xmm2,xmm3/m128,imm8
	{ "vpalignr", FCML_AMT_AVX_SIMD, 0x10C0, 0x00EC8000, { 0x0F, 0x3A, 0x0F }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_128, FCML_OP_IB, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.256.66.0F3A.WIG 0F /r ib VPALIGNR ymm1,ymm2,ymm3/m256,imm8
	{ "vpalignr", FCML_AMT_AVX2_SIMD, 0x10A0, 0x00EC8000, { 0x0F, 0x3A, 0x0F }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_YMM_256, FCML_OP_IB, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PAND[] = {
    // 0F DB /r PAND mm,mm/m64
    { NULL, FCML_AMT_MMX_SIMD, 0x0000, 0x00D88000, { 0x0F, 0xDB, 0x00 }, { FCML_OP_MODRM_R_MMX_W, FCML_OP_MODRM_RM_MMX, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
    // 66 0F DB /r PAND xmm1,xmm2/m128
    { NULL, FCML_AMT_SSE2_SIMD, 0x1001, 0x00D88000, { 0x0F, 0xDB, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
    // VEX.NDS.128.66.0F.WIG DB /r VPAND xmm1,xmm2,xmm3/m128
    { "vpand", FCML_AMT_AVX_SIMD, 0x10C0, 0x00D88000, { 0x0F, 0xDB, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA }, FCML_AM_NONE },
    // VEX.NDS.256.66.0F.WIG DB /r VPAND ymm1,ymm2,ymm3/m256
    { "vpand", FCML_AMT_AVX2_SIMD, 0x10A0, 0x00D88000, { 0x0F, 0xDB, 0x00 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_YMM_256, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PANDN[] = {
    // 0F DF /r PANDN mm,mm/m64
    { NULL, FCML_AMT_MMX_SIMD, 0x0000, 0x00D88000, { 0x0F, 0xDF, 0x00 }, { FCML_OP_MODRM_R_MMX_W, FCML_OP_MODRM_RM_MMX, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
    // 66 0F DF /r PANDN xmm1,xmm2/m128
    { NULL, FCML_AMT_SSE2_SIMD, 0x1001, 0x00D88000, { 0x0F, 0xDF, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
    // VEX.NDS.128.66.0F.WIG DF /r VPANDN xmm1,xmm2,xmm3/m128
    { "vpandn", FCML_AMT_AVX_SIMD, 0x10C0, 0x00D88000, { 0x0F, 0xDF, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA }, FCML_AM_NONE },
    // VEX.NDS.256.66.0F.WIG DF /r VPANDN ymm1,ymm2,ymm3/m256
    { "vpandn", FCML_AMT_AVX2_SIMD, 0x10A0, 0x00D88000, { 0x0F, 0xDF, 0x00 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_YMM_256, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PAUSE[] = {
	// F3 90 PAUSE
	{ NULL, FCML_AMT_SSE2, 0x4001, 0x00C40000, { 0x90, 0x00, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PAVG[] = {
	// 0F E0 /r1 PAVGB mm1,mm2/m64
	{ "pavgb", FCML_AMT_MMX, 0x0000, 0x00D88000, { 0x0F, 0xE0, 0x00 }, { FCML_OP_MODRM_R_MMX_W, FCML_OP_MODRM_RM_MMX, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 0F E3 /r1 PAVGW mm1,mm2/m64
	{ "pavgw", FCML_AMT_MMX, 0x0000, 0x00D88000, { 0x0F, 0xE3, 0x00 }, { FCML_OP_MODRM_R_MMX_W, FCML_OP_MODRM_RM_MMX, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 66 0F E0, /r PAVGB xmm1,xmm2/m128
	{ "pavgb", FCML_AMT_SSE_SIMD, 0x1000, 0x00D88000, { 0x0F, 0xE0, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 66 0F E3 /r PAVGW xmm1,xmm2/m128
	{ "pavgw", FCML_AMT_SSE_SIMD, 0x1000, 0x00D88000, { 0x0F, 0xE3, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.66.0F.WIG E0 /r VPAVGB xmm1,xmm2,xmm3/m128
	{ "vpavgb", FCML_AMT_AVX_SIMD, 0x10C0, 0x00D88000, { 0x0F, 0xE0, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.66.0F.WIG E3 /r VPAVGW xmm1,xmm2,xmm3/m128
	{ "vpavgw", FCML_AMT_AVX_SIMD, 0x10C0, 0x00D88000, { 0x0F, 0xE3, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.256.66.0F.WIG E0 /r VPAVGB ymm1,ymm2,ymm3/m256
	{ "vpavgb", FCML_AMT_AVX2_SIMD, 0x10A0, 0x00D88000, { 0x0F, 0xE0, 0x00 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_YMM_256, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.256.66.0F.WIG E3 /r VPAVGW ymm1,ymm2,ymm3/m256
	{ "vpavgw", FCML_AMT_AVX2_SIMD, 0x10A0, 0x00D88000, { 0x0F, 0xE3, 0x00 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_YMM_256, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PBLENDVB[] = {
	// 66 0F 38 10 /r PBLENDVB xmm1,xmm2/m128,<XMM0>
	{ NULL, FCML_AMT_SSE41_SIMD, 0x1001, 0x00EC8000, { 0x0F, 0x38, 0x10 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_OP_EXPLICIT_REG( FCML_REG_SIMD, FCML_REG_XMM0, FCML_EOS_OWORD ), FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.66.0F3A 4C /r /is4 VPBLENDVB xmm1,xmm2,xmm3/m128,xmm4
	{ "vpblendvb", FCML_AMT_AVX_SIMD, 0x10C0, 0x00EC8000, { 0x0F, 0x3A, 0x4C }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_128, FCML_OP_OPERAND_IS4, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.256.66.0F3A.W0 4C /r /is4 VPBLENDVB ymm1,ymm2,ymm3/m256,ymm4
	{ "vpblendvb", FCML_AMT_AVX2_SIMD, 0x10A0, 0x00EC8000, { 0x0F, 0x3A, 0x4C }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_YMM_256, FCML_OP_OPERAND_IS4, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PBLENDW[] = {
	// 66 0F 3A 0E /r ib PBLENDW xmm1,xmm2/m128,imm8
	{ NULL, FCML_AMT_SSE41_SIMD, 0x1001, 0x00EC8000, { 0x0F, 0x3A, 0x0E }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.66.0F3A 0E /r ib VPBLENDW xmm1,xmm2,xmm3/m128,imm8
	{ "vpblendw", FCML_AMT_AVX_SIMD, 0x10C0, 0x00EC8000, { 0x0F, 0x3A, 0x0E }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_128, FCML_OP_IB, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.256.66.0F3A.WIG 0E /r ib VPBLENDW ymm1,ymm2,ymm3/m256,imm8
	{ "vpblendw", FCML_AMT_AVX2_SIMD, 0x10A0, 0x00EC8000, { 0x0F, 0x3A, 0x0E }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_YMM_256, FCML_OP_IB, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPBLENDD[] = {
	// VEX.NDS.128.66.0F3A.W0 02 /r ib VPBLENDD xmm1,xmm2,xmm3/m128,imm8
	// VEX.NDS.256.66.0F3A.W0 02 /r ib VPBLENDD ymm1,ymm2,ymm3/m256,imm8
	{ NULL, FCML_AMT_AVX2_SIMD, 0x1090, 0x00EC8000, { 0x0F, 0x3A, 0x02 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L, FCML_OP_IB, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PCLMULQDQ[] = {
	// 66 0F 3A 44 /r ib PCLMULQDQ xmm1,xmm2/m128,imm8
	{ NULL, FCML_AMT_CLMUL, 0x1001, 0x00EC8000, { 0x0F, 0x3A, 0x44 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.66.0F3A 44 /r ib VPCLMULQDQ xmm1,xmm2,xmm3/m128,imm8
	{ "vpclmulqdq", FCML_AMT_AVX_SIMD | FCML_AMT_CLMUL, 0x10C0, 0x00EC8000, { 0x0F, 0x3A, 0x44 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_128, FCML_OP_IB, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PCMPEQ[] = {
	// 0F 74 /r1 PCMPEQB mm,mm/m64
	// 0F 75 /r1 PCMPEQW mm,mm/m64
	// 0F 76 /r1 PCMPEQD mm,mm/m64
	{ "pcmpeqb", FCML_AMT_MMX_SIMD, 0x0000, 0x00D88000, { 0x0F, 0x74, 0x00 }, { FCML_OP_MODRM_R_MMX_W, FCML_OP_MODRM_RM_MMX, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	{ "pcmpeqw", FCML_AMT_MMX_SIMD, 0x0000, 0x00D88000, { 0x0F, 0x75, 0x00 }, { FCML_OP_MODRM_R_MMX_W, FCML_OP_MODRM_RM_MMX, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	{ "pcmpeqd", FCML_AMT_MMX_SIMD, 0x0000, 0x00D88000, { 0x0F, 0x76, 0x00 }, { FCML_OP_MODRM_R_MMX_W, FCML_OP_MODRM_RM_MMX, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 66 0F 74 /r PCMPEQB xmm1,xmm2/m128
	// 66 0F 75 /r PCMPEQW xmm1,xmm2/m128
	// 66 0F 76 /r PCMPEQD xmm1,xmm2/m128
	{ "pcmpeqb", FCML_AMT_SSE2_SIMD, 0x1001, 0x00D88000, { 0x0F, 0x74, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	{ "pcmpeqw", FCML_AMT_SSE2_SIMD, 0x1001, 0x00D88000, { 0x0F, 0x75, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	{ "pcmpeqd", FCML_AMT_SSE2_SIMD, 0x1001, 0x00D88000, { 0x0F, 0x76, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.66.0F.WIG 74 /r VPCMPEQB xmm1,xmm2,xmm3/m128
	// VEX.NDS.128.66.0F.WIG 75 /r VPCMPEQW xmm1,xmm2,xmm3/m128
	// VEX.NDS.128.66.0F.WIG 76 /r VPCMPEQD xmm1,xmm2,xmm3/m128
	{ "vpcmpeqb", FCML_AMT_AVX_SIMD, 0x10C0, 0x00D88000, { 0x0F, 0x74, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA }, FCML_AM_NONE },
	{ "vpcmpeqw", FCML_AMT_AVX_SIMD, 0x10C0, 0x00D88000, { 0x0F, 0x75, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA }, FCML_AM_NONE },
	{ "vpcmpeqd", FCML_AMT_AVX_SIMD, 0x10C0, 0x00D88000, { 0x0F, 0x76, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.256.66.0F.WIG 74 /r VPCMPEQB ymm1,ymm2,ymm3/m256
	// VEX.NDS.256.66.0F.WIG 75 /r VPCMPEQW ymm1,ymm2,ymm3/m256
	// VEX.NDS.256.66.0F.WIG FCML_AMT_AVX_SIMD /r VPCMPEQD ymm1,ymm2,ymm3/m256
	{ "vpcmpeqb", FCML_AMT_AVX2_SIMD, 0x10A0, 0x00D88000, { 0x0F, 0x74, 0x00 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_YMM_256, FCML_NA, FCML_NA }, FCML_AM_NONE },
	{ "vpcmpeqw", FCML_AMT_AVX2_SIMD, 0x10A0, 0x00D88000, { 0x0F, 0x75, 0x00 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_YMM_256, FCML_NA, FCML_NA }, FCML_AM_NONE },
	{ "vpcmpeqd", FCML_AMT_AVX2_SIMD, 0x10A0, 0x00D88000, { 0x0F, 0x76, 0x00 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_YMM_256, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PCMPEQQ[] = {
	// 66 0F 38 29 /r PCMPEQQ xmm1,xmm2/m128
	{ NULL, FCML_AMT_SSE41_SIMD, 0x1001, 0x00EC8000, { 0x0F, 0x38, 0x29 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.66.0F38.WIG 29 /r VPCMPEQQ xmm1,xmm2,xmm3/m128
	{ "vpcmpeqq", FCML_AMT_AVX_SIMD, 0x10C0, 0x00EC8000, { 0x0F, 0x38, 0x29 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.256.66.0F38.WIG 29 /r VPCMPEQQ ymm1,ymm2,ymm3/m256
	{ "vpcmpeqq", FCML_AMT_AVX2_SIMD, 0x10A0, 0x00EC8000, { 0x0F, 0x38, 0x29 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_YMM_256, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PCMPESTRI[] = {
	// 66 0F 3A 61 /r imm8 PCMPESTRI xmm1,xmm2/m128,imm8
	{ NULL, FCML_AMT_SSE42_SIMD, 0x1001, 0x00EC8000, { 0x0F, 0x3A, 0x61 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.128.66.0F3A.WIG 61 /r ib VPCMPESTRI xmm1,xmm2/m128,imm8
	{ "vpcmpestri", FCML_AMT_AVX_SIMD, 0x11C0, 0x00EC8000, { 0x0F, 0x3A, 0x61 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PCMPESTRM[] = {
	// 66 0F 3A 60 /r imm8 PCMPESTRM xmm1,xmm2/m128,imm8
	{ NULL, FCML_AMT_SSE42_SIMD, 0x1001, 0x00EC8000, { 0x0F, 0x3A, 0x60 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.128.66.0F3A.WIG 60 /r ib VPCMPESTRM xmm1,xmm2/m128,imm8
	{ "vpcmpestrm", FCML_AMT_AVX_SIMD, 0x11C0, 0x00EC8000, { 0x0F, 0x3A, 0x60 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PCMPGT[] = {
	// 0F 64 /r1 PCMPGTB mm,mm/m64
	// 0F 65 /r1 PCMPGTW mm,mm/m64
	// 0F 66 /r1 PCMPGTD mm,mm/m64
	{ "pcmpgtb", FCML_AMT_MMX_SIMD, 0x0000, 0x00D88000, { 0x0F, 0x64, 0x00 }, { FCML_OP_MODRM_R_MMX_W, FCML_OP_MODRM_RM_MMX, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	{ "pcmpgtw", FCML_AMT_MMX_SIMD, 0x0000, 0x00D88000, { 0x0F, 0x65, 0x00 }, { FCML_OP_MODRM_R_MMX_W, FCML_OP_MODRM_RM_MMX, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	{ "pcmpgtd", FCML_AMT_MMX_SIMD, 0x0000, 0x00D88000, { 0x0F, 0x66, 0x00 }, { FCML_OP_MODRM_R_MMX_W, FCML_OP_MODRM_RM_MMX, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 66 0F 64 /r PCMPGTB xmm1,xmm2/m128
	// 66 0F 65 /r PCMPGTW xmm1,xmm2/m128
	// 66 0F 66 /r PCMPGTD xmm1,xmm2/m128
	{ "pcmpgtb", FCML_AMT_SSE2_SIMD, 0x1001, 0x00D88000, { 0x0F, 0x64, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	{ "pcmpgtw", FCML_AMT_SSE2_SIMD, 0x1001, 0x00D88000, { 0x0F, 0x65, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	{ "pcmpgtd", FCML_AMT_SSE2_SIMD, 0x1001, 0x00D88000, { 0x0F, 0x66, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.66.0F.WIG 64 /r VPCMPGTB xmm1,xmm2,xmm3/m128
	// VEX.NDS.128.66.0F.WIG 65 /r VPCMPGTW xmm1,xmm2,xmm3/m128
	// VEX.NDS.128.66.0F.WIG 66 /r VPCMPGTD xmm1,xmm2,xmm3/m128
	{ "vpcmpgtb", FCML_AMT_AVX_SIMD, 0x10C0, 0x00D88000, { 0x0F, 0x64, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA }, FCML_AM_NONE },
	{ "vpcmpgtw", FCML_AMT_AVX_SIMD, 0x10C0, 0x00D88000, { 0x0F, 0x65, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA }, FCML_AM_NONE },
	{ "vpcmpgtd", FCML_AMT_AVX_SIMD, 0x10C0, 0x00D88000, { 0x0F, 0x66, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.256.66.0F.WIG 64 /r VPCMPGTB ymm1,ymm2,ymm3/m256
	// VEX.NDS.256.66.0F.WIG 65 /r VPCMPGTW ymm1,ymm2,ymm3/m256
	// VEX.NDS.256.66.0F.WIG 66 /r VPCMPGTD ymm1,ymm2,ymm3/m256
	{ "vpcmpgtb", FCML_AMT_AVX2_SIMD, 0x10A0, 0x00D88000, { 0x0F, 0x64, 0x00 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_YMM_256, FCML_NA, FCML_NA }, FCML_AM_NONE },
	{ "vpcmpgtw", FCML_AMT_AVX2_SIMD, 0x10A0, 0x00D88000, { 0x0F, 0x65, 0x00 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_YMM_256, FCML_NA, FCML_NA }, FCML_AM_NONE },
	{ "vpcmpgtd", FCML_AMT_AVX2_SIMD, 0x10A0, 0x00D88000, { 0x0F, 0x66, 0x00 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_YMM_256, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PCMPGTQ[] = {
	// 66 0F 38 37 /r PCMPGTQ xmm1,xmm2/m128
	{ NULL, FCML_AMT_SSE42_SIMD, 0x1001, 0x00EC8000, { 0x0F, 0x38, 0x37 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.66.0F38.WIG 37 /r VPCMPGTQ xmm1,xmm2,xmm3/m128
	{ "vpcmpgtq", FCML_AMT_AVX_SIMD, 0x10C0, 0x00EC8000, { 0x0F, 0x38, 0x37 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.256.66.0F38.WIG 37 /r VPCMPGTQ ymm1,ymm2,ymm3/m256
	{ "vpcmpgtq", FCML_AMT_AVX2_SIMD, 0x10A0, 0x00EC8000, { 0x0F, 0x38, 0x37 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_YMM_256, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PCMPISTRI[] = {
	// 66 0F 3A 63 /r imm8 PCMPISTRI xmm1,xmm2/m128,imm8
	{ NULL, FCML_AMT_SSE42_SIMD, 0x1001, 0x00EC8000, { 0x0F, 0x3A, 0x63 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.128.66.0F3A.WIG 63 /r ib VPCMPISTRI xmm1,xmm2/m128,imm8
	{ "vpcmpistri", FCML_AMT_AVX_SIMD, 0x11C0, 0x00EC8000, { 0x0F, 0x3A, 0x63 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PCMPISTRM[] = {
	// 66 0F 3A 62 /r imm8 PCMPISTRM xmm1,xmm2/m128,imm8
	{ NULL, FCML_AMT_SSE42_SIMD, 0x1001, 0x00EC8000, { 0x0F, 0x3A, 0x62 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.128.66.0F3A.WIG 62 /r ib VPCMPISTRM xmm1,xmm2/m128,imm8
	{ "vpcmpistrm", FCML_AMT_AVX_SIMD, 0x11C0, 0x00EC8000, { 0x0F, 0x3A, 0x62 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PEXTR[] = {
	// 66 0F 3A 14 /r ib PEXTRB reg/m8,xmm2,imm8
	{ "pextrb", FCML_AMT_SSE41_SIMD, 0x1001, 0x40EC8000, { 0x0F, 0x3A, 0x14 }, { FCML_OP_RM(FCML_REG_GPR, FCML_EOS_EOSA, FCML_EOS_BYTE, FCML_RMF_RM ), FCML_OP_MODRM_R_XMM, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 66 0F 3A 16 /r ib PEXTRD r/m32, xmm2, imm8
	{ "pextrd", FCML_AMT_SSE41_SIMD, 0x1001, 0x40EC8000, { 0x0F, 0x3A, 0x16 }, { FCML_OP_RM(FCML_REG_GPR, FCML_EOS_EOSA, FCML_EOS_DWORD, FCML_RMF_RM ), FCML_OP_MODRM_R_XMM, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 66 REX.W 0F 3A 16 /r ib PEXTRQ r/m64, xmm2, imm8
	{ "pextrq", FCML_AMT_SSE41_SIMD, 0x1009, 0x04AC8000, { 0x0F, 0x3A, 0x16 }, { FCML_OP_RM(FCML_REG_GPR, FCML_EOS_QWORD, FCML_EOS_QWORD, FCML_RMF_RM ), FCML_OP_MODRM_R_XMM, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.128.66.0F3A.W0 14 /r ib VPEXTRB reg/m8, xmm2, imm8
	{ "vpextrb", FCML_AMT_AVX_SIMD, 0x13C0, 0x40EC8000, { 0x0F, 0x3A, 0x14 }, { FCML_OP_RM(FCML_REG_GPR, FCML_EOS_EOSA, FCML_EOS_BYTE, FCML_RMF_RM ), FCML_OP_MODRM_R_XMM, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.128.66.0F3A.W0 16 /r ib VPEXTRD r32/m32, xmm2, imm8
	{ "vpextrd", FCML_AMT_AVX_SIMD, 0x13D0, 0x40EC8000, { 0x0F, 0x3A, 0x16 }, { FCML_OP_RM(FCML_REG_GPR, FCML_EOS_EOSA, FCML_EOS_DWORD, FCML_RMF_RM ), FCML_OP_MODRM_R_XMM, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.128.66.0F3A.W1 16 /r ib VPEXTRQ r64/m64, xmm2, imm8
	{ "vpextrq", FCML_AMT_AVX_SIMD, 0x11C8, 0x04AC8000, { 0x0F, 0x3A, 0x16 }, { FCML_OP_RM(FCML_REG_GPR, FCML_EOS_QWORD, FCML_EOS_QWORD, FCML_RMF_RM ), FCML_OP_MODRM_R_XMM, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PEXTRW[] = {
	// 0F C5 /r ib PEXTRW reg,mm,imm8
	{ NULL, FCML_AMT_SSE_SIMD, 0x0000, 0x40DA8000, { 0x0F, 0xC5, 0x00 }, { FCML_OP_R(FCML_REG_GPR, FCML_EOS_EOSA), FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_QWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 66 0F C5 /r ib PEXTRW reg,xmm,imm8
	{ NULL, FCML_AMT_SSE_SIMD, 0x1000, 0x40DA8000, { 0x0F, 0xC5, 0x00 }, { FCML_OP_R(FCML_REG_GPR, FCML_EOS_EOSA), FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_OWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 66 0F 3A 15 /r ib PEXTRW reg/m16,xmm,imm8
	{ NULL, FCML_AMT_SSE41_SIMD, 0x1001, 0x40EC8000, { 0x0F, 0x3A, 0x15 }, { FCML_OP_RM(FCML_REG_GPR, FCML_EOS_EOSA, FCML_EOS_WORD, FCML_RMF_RM ), FCML_OP_R(FCML_REG_SIMD, FCML_EOS_OWORD), FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.128.66.0F.W0 C5 /r ib VPEXTRW reg,xmm1,imm8
	{ "vpextrw", FCML_AMT_AVX_SIMD, 0x13C1, 0x40DA8000, { 0x0F, 0xC5, 0x00 }, { FCML_OP_R(FCML_REG_GPR, FCML_EOS_EOSA), FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_OWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.128.66.0F3A.W0 15 /r ib VPEXTRW reg/m16,xmm2,imm8
	{ "vpextrw", FCML_AMT_AVX_SIMD, 0x13C1, 0x40EC8000, { 0x0F, 0x3A, 0x15 }, { FCML_OP_RM(FCML_REG_GPR, FCML_EOS_EOSA, FCML_EOS_WORD, FCML_RMF_RM ), FCML_OP_R(FCML_REG_SIMD, FCML_EOS_OWORD), FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PHADD[] = {
	// 0F 38 01 /r PHADDW mm1,mm2/m64
	{ "phaddw", FCML_AMT_SSSE3_SIMD, 0x0000, 0x00EC8000, { 0x0F, 0x38, 0x01 }, { FCML_OP_MODRM_R_MMX_W, FCML_OP_MODRM_RM_MMX, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 0F 38 02 /r PHADDD mm1,mm2/m64
	{ "phaddd", FCML_AMT_SSSE3_SIMD, 0x0000, 0x00EC8000, { 0x0F, 0x38, 0x02 }, { FCML_OP_MODRM_R_MMX_W, FCML_OP_MODRM_RM_MMX, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 66 0F 38 01 /r PHADDW xmm1,xmm2/m128
	{ "phaddw", FCML_AMT_SSSE3_SIMD, 0x1001, 0x00EC8000, { 0x0F, 0x38, 0x01 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 66 0F 38 02 /r PHADDD xmm1,xmm2/m128
	{ "phaddd", FCML_AMT_SSSE3_SIMD, 0x1001, 0x00EC8000, { 0x0F, 0x38, 0x02 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.66.0F38.WIG 01 /r VPHADDW xmm1,xmm2,xmm3/m128
	{ "vphaddw", FCML_AMT_AVX_SIMD, 0x10C0, 0x00EC8000, { 0x0F, 0x38, 0x01 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.66.0F38.WIG 02 /r VPHADDD xmm1,xmm2,xmm3/m128
	{ "vphaddd", FCML_AMT_AVX_SIMD, 0x10C0, 0x00EC8000, { 0x0F, 0x38, 0x02 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.256.66.0F38.WIG 01 /r VPHADDW ymm1,ymm2,ymm3/m256
	{ "vphaddw", FCML_AMT_AVX2_SIMD, 0x10A0, 0x00EC8000, { 0x0F, 0x38, 0x01 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_YMM_256, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.256.66.0F38.WIG 02 /r VPHADDD ymm1,ymm2,ymm3/m256
	{ "vphaddd", FCML_AMT_AVX2_SIMD, 0x10A0, 0x00EC8000, { 0x0F, 0x38, 0x02 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_YMM_256, FCML_NA, FCML_NA }, FCML_AM_NONE },
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PHADDSW[] = {
	// 0F 38 03 /r PHADDSW mm1,mm2/m64
	{ NULL, FCML_AMT_SSSE3_SIMD, 0x0000, 0x00EC8000, { 0x0F, 0x38, 0x03 }, { FCML_OP_MODRM_R_MMX_W, FCML_OP_MODRM_RM_MMX, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 66 0F 38 03 /r PHADDSW xmm1,xmm2/m128
	{ NULL, FCML_AMT_SSSE3_SIMD, 0x1001, 0x00EC8000, { 0x0F, 0x38, 0x03 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.66.0F38.WIG 03 /r VPHADDSW xmm1,xmm2,xmm3/m128
	{ "vphaddsw", FCML_AMT_AVX_SIMD, 0x10C0, 0x00EC8000, { 0x0F, 0x38, 0x03 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.256.66.0F38.WIG 03 /r VPHADDSW ymm1,ymm2,ymm3/m256
	{ "vphaddsw", FCML_AMT_AVX2_SIMD, 0x10A0, 0x00EC8000, { 0x0F, 0x38, 0x03 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_YMM_256, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PHMINPOSUW[] = {
	// 66 0F 38 41 /r PHMINPOSUW xmm1,xmm2/m128
	{ NULL, FCML_AMT_SSE41_SIMD, 0x1001, 0x00EC8000, { 0x0F, 0x38, 0x41 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.128.66.0F38.WIG 41 /r VPHMINPOSUW xmm1,xmm2/m128
	{ "vphminposuw", FCML_AMT_AVX_SIMD, 0x11C0, 0x00EC8000, { 0x0F, 0x38, 0x41 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PHSUB[] = {
	// 0F 38 05 /r1 PHSUBW mm1,mm2/m64
	{ "phsubw", FCML_AMT_SSSE3_SIMD, 0x0000, 0x00EC8000, { 0x0F, 0x38, 0x05 }, { FCML_OP_MODRM_R_MMX_W, FCML_OP_MODRM_RM_MMX, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 0F 38 06 /r PHSUBD mm1,mm2/m64
	{ "phsubd", FCML_AMT_SSSE3_SIMD, 0x0000, 0x00EC8000, { 0x0F, 0x38, 0x06 }, { FCML_OP_MODRM_R_MMX_W, FCML_OP_MODRM_RM_MMX, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 66 0F 38 05 /r PHSUBW xmm1,xmm2/m128
	{ "phsubw", FCML_AMT_SSSE3_SIMD, 0x1001, 0x00EC8000, { 0x0F, 0x38, 0x05 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 66 0F 38 06 /r PHSUBD xmm1,xmm2/m128
	{ "phsubd", FCML_AMT_SSSE3_SIMD, 0x1001, 0x00EC8000, { 0x0F, 0x38, 0x06 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.66.0F38.WIG 05 /r VPHSUBW xmm1,xmm2,xmm3/m128
	{ "vphsubw", FCML_AMT_AVX_SIMD, 0x10C0, 0x00EC8000, { 0x0F, 0x38, 0x05 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.66.0F38.WIG 06 /r VPHSUBD xmm1,xmm2,xmm3/m128
	{ "vphsubd", FCML_AMT_AVX_SIMD, 0x10C0, 0x00EC8000, { 0x0F, 0x38, 0x06 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.256.66.0F38.WIG 05 /r VPHSUBW ymm1,ymm2,ymm3/m256
	{ "vphsubw", FCML_AMT_AVX2_SIMD, 0x10A0, 0x00EC8000, { 0x0F, 0x38, 0x05 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_YMM_256, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.256.66.0F38.WIG 06 /r VPHSUBD ymm1,ymm2,ymm3/m256
	{ "vphsubd", FCML_AMT_AVX2_SIMD, 0x10A0, 0x00EC8000, { 0x0F, 0x38, 0x06 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_YMM_256, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PHSUBSW[] = {
	// 0F 38 07 /r PHSUBSW mm1,mm2/m64
	{ NULL, FCML_AMT_SSSE3_SIMD, 0x0000, 0x00EC8000, { 0x0F, 0x38, 0x07 }, { FCML_OP_MODRM_R_MMX_W, FCML_OP_MODRM_RM_MMX, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 66 0F 38 07 /r PHSUBSW xmm1,xmm2/m128
	{ NULL, FCML_AMT_SSSE3_SIMD, 0x1001, 0x00EC8000, { 0x0F, 0x38, 0x07 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.66.0F38.WIG 07 /r VPHSUBSW xmm1,xmm2,xmm3/m128
	{ "vphsubsw", FCML_AMT_AVX_SIMD, 0x10C0, 0x00EC8000, { 0x0F, 0x38, 0x07 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.256.66.0F38.WIG 07 /r VPHSUBSW ymm1,ymm2,ymm3/m256
	{ "vphsubsw", FCML_AMT_AVX2_SIMD, 0x10A0, 0x00EC8000, { 0x0F, 0x38, 0x07 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_YMM_256, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PINSR[] = {
	// 66 0F 3A 20 /r ib PINSRB xmm1,r32/m8,imm8
	{ "pinsrb", FCML_AMT_SSE41_SIMD, 0x1001, 0x00EC8000, { 0x0F, 0x3A, 0x20 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_RM(FCML_REG_GPR, FCML_EOS_DWORD, FCML_EOS_BYTE, FCML_RMF_RM ), FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 66 0F 3A 22 /r ib PINSRD xmm1,r/m32,imm8
	{ "pinsrd", FCML_AMT_SSE41_SIMD, 0x1001, 0x03EC8000, { 0x0F, 0x3A, 0x22 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_32, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 66 REX.W 0F 3A 22 /r ib PINSRQ xmm1,r/m64,imm8
	{ "pinsrq", FCML_AMT_SSE41_SIMD, 0x1009, 0x04AC8000, { 0x0F, 0x3A, 0x22 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_64, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.66.0F3A.W0 20 /r ib VPINSRB xmm1,xmm2,r32/m8,imm8
	{ "vpinsrb", FCML_AMT_AVX_SIMD, 0x10C0, 0x00EC8000, { 0x0F, 0x3A, 0x20 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_RM(FCML_REG_GPR, FCML_EOS_DWORD, FCML_EOS_BYTE, FCML_RMF_RM ), FCML_OP_IB, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.66.0F3A.W0 22 /r ib VPINSRD xmm1,xmm2,r32/m32,imm8
	{ "vpinsrd", FCML_AMT_AVX_SIMD, 0x10D0, 0x00EC8000, { 0x0F, 0x3A, 0x22 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_32, FCML_OP_IB, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.66.0F3A.W1 22 /r ib VPINSRQ xmm1,xmm2,r64/m64,imm8
	{ "vpinsrq", FCML_AMT_AVX_SIMD, 0x10C8, 0x00EC8000, { 0x0F, 0x3A, 0x22 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_64, FCML_OP_IB, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PINSRW[] = {
	// 0F C4 /r ib PINSRW mm,r32/m16,imm8
	{ NULL, FCML_AMT_SSE_SIMD, 0x0000, 0x00D88000, { 0x0F, 0xC4, 0x00 }, { FCML_OP_MODRM_R_MMX_W, FCML_OP_RM(FCML_REG_GPR, FCML_EOS_DWORD, FCML_EOS_WORD, FCML_RMF_RM ), FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 66 0F C4 /r ib PINSRW xmm,r32/m16,imm8
	{ NULL, FCML_AMT_SSE_SIMD, 0x1000, 0x00D88000, { 0x0F, 0xC4, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_RM(FCML_REG_GPR, FCML_EOS_DWORD, FCML_EOS_WORD, FCML_RMF_RM ), FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.66.0F.W0 C4 /r ib VPINSRW xmm1,xmm2,r32/m16,imm8
	{ "vpinsrw", FCML_AMT_AVX_SIMD, 0x10C0, 0x00D88000, { 0x0F, 0xC4, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_RM(FCML_REG_GPR, FCML_EOS_DWORD, FCML_EOS_WORD, FCML_RMF_RM ), FCML_OP_IB, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PMADDUBSW[] = {
	// 0F 38 04 /r PMADDUBSW mm1,mm2/m64
	{ NULL, FCML_AMT_SSSE3_SIMD, 0x0000, 0x00EC8000, { 0x0F, 0x38, 0x04 }, { FCML_OP_MODRM_R_MMX_W, FCML_OP_MODRM_RM_MMX, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 66 0F 38 04 /r PMADDUBSW xmm1,xmm2/m128
	{ NULL, FCML_AMT_SSSE3_SIMD, 0x1001, 0x00EC8000, { 0x0F, 0x38, 0x04 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.66.0F38.WIG 04 /r VPMADDUBSW xmm1,xmm2,xmm3/m128
	{ "vpmaddubsw", FCML_AMT_AVX_SIMD, 0x10C0, 0x00EC8000, { 0x0F, 0x38, 0x04 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.256.66.0F38.WIG 04 /r VPMADDUBSW ymm1,ymm2,ymm3/m256
	{ "vpmaddubsw", FCML_AMT_AVX2_SIMD, 0x10A0, 0x00EC8000, { 0x0F, 0x38, 0x04 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_YMM_256, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PMADDWD[] = {
	// 0F F5 /r PMADDWD mm,mm/m64
	{ NULL, FCML_AMT_MMX_SIMD, 0x0000, 0x00D88000, { 0x0F, 0xF5, 0x00 }, { FCML_OP_MODRM_R_MMX_W, FCML_OP_MODRM_RM_MMX, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 66 0F F5 /r PMADDWD xmm1,xmm2/m128
	{ NULL, FCML_AMT_SSE2_SIMD, 0x1001, 0x00D88000, { 0x0F, 0xF5, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.66.0F.WIG F5 /r VPMADDWD xmm1,xmm2,xmm3/m128
	{ "vpmaddwd", FCML_AMT_AVX_SIMD, 0x10C0, 0x00D88000, { 0x0F, 0xF5, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.256.66.0F.WIG F5 /r VPMADDWD ymm1,ymm2,ymm3/m256
	{ "vpmaddwd", FCML_AMT_AVX2_SIMD, 0x10A0, 0x00D88000, { 0x0F, 0xF5, 0x00 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_YMM_256, FCML_NA, FCML_NA }, FCML_AM_NONE }

};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PMAXSB[] = {
	// 66 0F 38 3C /r PMAXSB xmm1,xmm2/m128
	{ NULL, FCML_AMT_SSE41_SIMD, 0x1001, 0x00EC8000, { 0x0F, 0x38, 0x3C }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.66.0F38.WIG 3C /r VPMAXSB xmm1,xmm2,xmm3/m128
	{ "vpmaxsb", FCML_AMT_AVX_SIMD, 0x10C0, 0x00EC8000, { 0x0F, 0x38, 0x3C }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.256.66.0F38.WIG 3C /r VPMAXSB ymm1,ymm2,ymm3/m256
	{ "vpmaxsb", FCML_AMT_AVX2_SIMD, 0x10A0, 0x00EC8000, { 0x0F, 0x38, 0x3C }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_YMM_256, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PMAXSD[] = {
	// 66 0F 38 3D /r PMAXSD xmm1,xmm2/m128
	{ NULL, FCML_AMT_SSE41_SIMD, 0x1001, 0x00EC8000, { 0x0F, 0x38, 0x3D }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.66.0F38.WIG 3D /r VPMAXSD xmm1,xmm2,xmm3/m128
	{ "vpmaxsd", FCML_AMT_AVX_SIMD, 0x10C0, 0x00EC8000, { 0x0F, 0x38, 0x3D }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.256.66.0F38.WIG 3D /r VPMAXSD ymm1,ymm2,ymm3/m256
	{ "vpmaxsd", FCML_AMT_AVX2_SIMD, 0x10A0, 0x00EC8000, { 0x0F, 0x38, 0x3D }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_YMM_256, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PMAXSW[] = {
	// 0F EE /r PMAXSW mm1,mm2/m64
	{ NULL, FCML_AMT_MMX, 0x0000, 0x00D88000, { 0x0F, 0xEE, 0x00 }, { FCML_OP_MODRM_R_MMX_W, FCML_OP_MODRM_RM_MMX, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 66 0F EE /r PMAXSW xmm1,xmm2/m128
	{ NULL, FCML_AMT_SSE, 0x1001, 0x00D88000, { 0x0F, 0xEE, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.66.0F.WIG EE /r VPMAXSW xmm1,xmm2,xmm3/m128
	{ "vpmaxsw", FCML_AMT_AVX_SIMD, 0x10C0, 0x00D88000, { 0x0F, 0xEE, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.256.66.0F.WIG EE /r VPMAXSW ymm1,ymm2,ymm3/m256
	{ "vpmaxsw", FCML_AMT_AVX2_SIMD, 0x10A0, 0x00D88000, { 0x0F, 0xEE, 0x00 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_YMM_256, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PMAXUB[] = {
	// 0F DE /r PMAXUB mm1,mm2/m64
	{ NULL, FCML_AMT_SSE_SIMD, 0x0000, 0x00D88000, { 0x0F, 0xDE, 0x00 }, { FCML_OP_MODRM_R_MMX_W, FCML_OP_MODRM_RM_MMX, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 66 0F DE /r PMAXUB xmm1,xmm2/m128
	{ NULL, FCML_AMT_SSE_SIMD, 0x1000, 0x00D88000, { 0x0F, 0xDE, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.66.0F.WIG DE /r VPMAXUB xmm1,xmm2,xmm3/m128
	{ "vpmaxub", FCML_AMT_AVX_SIMD, 0x10C0, 0x00D88000, { 0x0F, 0xDE, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.256.66.0F.WIG DE /r VPMAXUB ymm1,ymm2,ymm3/m256
	{ "vpmaxub", FCML_AMT_AVX2_SIMD, 0x10A0, 0x00D88000, { 0x0F, 0xDE, 0x00 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_YMM_256, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PMAXUD[] = {
	// 66 0F 38 3F /r PMAXUD xmm1, xmm2/m128
	{ NULL, FCML_AMT_SSE41_SIMD, 0x1001, 0x00EC8000, { 0x0F, 0x38, 0x3F }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.66.0F38.WIG 3F /r VPMAXUD xmm1,xmm2,xmm3/m128
	{ "vpmaxud", FCML_AMT_AVX_SIMD, 0x10C0, 0x00EC8000, { 0x0F, 0x38, 0x3F }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.256.66.0F38.WIG 3F /r VPMAXUD ymm1,ymm2,ymm3/m256
	{ "vpmaxud", FCML_AMT_AVX2_SIMD, 0x10A0, 0x00EC8000, { 0x0F, 0x38, 0x3F }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_YMM_256, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PMAXUW[] = {
	// 66 0F 38 3E /r PMAXUW xmm1,xmm2/m128
	{ NULL, FCML_AMT_SSE41_SIMD, 0x1001, 0x00EC8000, { 0x0F, 0x38, 0x3E }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.66.0F38.WIG 3E/r VPMAXUW xmm1,xmm2,xmm3/m128
	{ "vpmaxuw", FCML_AMT_AVX_SIMD, 0x10C0, 0x00EC8000, { 0x0F, 0x38, 0x3E }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.256.66.0F38.WIG 3E /r VPMAXUW ymm1,ymm2,ymm3/m256
	{ "vpmaxuw", FCML_AMT_AVX2_SIMD, 0x10A0, 0x00EC8000, { 0x0F, 0x38, 0x3E }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_YMM_256, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PMINSB[] = {
	// 66 0F 38 38 /r PMINSB xmm1,xmm2/m128
	{ NULL, FCML_AMT_SSE41_SIMD, 0x1001, 0x00EC8000, { 0x0F, 0x38, 0x38 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.66.0F38.WIG 38 /r VPMINSB xmm1,xmm2,xmm3/m128
	{ "vpminsb", FCML_AMT_AVX_SIMD, 0x10C0, 0x00EC8000, { 0x0F, 0x38, 0x38 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.256.66.0F38.WIG 38 /r VPMINSB ymm1,ymm2,ymm3/m256
	{ "vpminsb", FCML_AMT_AVX2_SIMD, 0x10A0, 0x00EC8000, { 0x0F, 0x38, 0x38 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_YMM_256, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PMINSD[] = {
	// 66 0F 38 39 /r PMINSD xmm1, xmm2/m128
	{ NULL, FCML_AMT_SSE41_SIMD, 0x1001, 0x00EC8000, { 0x0F, 0x38, 0x39 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.66.0F38.WIG 39 /r VPMINSD xmm1, xmm2, xmm3/m128
	{ "vpminsd", FCML_AMT_AVX_SIMD, 0x10C0, 0x00EC8000, { 0x0F, 0x38, 0x39 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.256.66.0F38.WIG 39 /r VPMINSD ymm1,ymm2,ymm3/m256
	{ "vpminsd", FCML_AMT_AVX2_SIMD, 0x10A0, 0x00EC8000, { 0x0F, 0x38, 0x39 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_YMM_256, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PMINSW[] = {
	// 0F EA /r PMINSW mm1,mm2/m64
	{ NULL, FCML_AMT_SSE_SIMD, 0x0000, 0x00D88000, { 0x0F, 0xEA, 0x00 }, { FCML_OP_MODRM_R_MMX_W, FCML_OP_MODRM_RM_MMX, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 66 0F EA /r PMINSW xmm1,xmm2/m128
	{ NULL, FCML_AMT_SSE_SIMD, 0x1001, 0x00D88000, { 0x0F, 0xEA, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.66.0F.WIG EA /r VPMINSW xmm1,xmm2,xmm3/m128
	{ "vpminsw", FCML_AMT_AVX_SIMD, 0x10C0, 0x00D88000, { 0x0F, 0xEA, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.256.66.0F.WIG EA /r VPMINSW ymm1,ymm2,ymm3/m256
	{ "vpminsw", FCML_AMT_AVX2_SIMD, 0x10A0, 0x00D88000, { 0x0F, 0xEA, 0x00 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_YMM_256, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PMINUB[] = {
	// 0F DA /r PMINUB mm1,mm2/m64
	{ NULL, FCML_AMT_SSE_SIMD, 0x0000, 0x00D88000, { 0x0F, 0xDA, 0x00 }, { FCML_OP_MODRM_R_MMX_W, FCML_OP_MODRM_RM_MMX, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 66 0F DA /r PMINUB xmm1,xmm2/m128
	{ NULL, FCML_AMT_SSE_SIMD, 0x1001, 0x00D88000, { 0x0F, 0xDA, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.66.0F.WIG DA /r VPMINUB xmm1,xmm2,xmm3/m128
	{ "vpminub", FCML_AMT_AVX_SIMD, 0x10C0, 0x00D88000, { 0x0F, 0xDA, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.256.66.0F.WIG DA /r VPMINUB ymm1,ymm2,ymm3/m256
	{ "vpminub", FCML_AMT_AVX2_SIMD, 0x10A0, 0x00D88000, { 0x0F, 0xDA, 0x00 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_YMM_256, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PMINUW[] = {
	// 66 0F 38 3A /r PMINUW xmm1,xmm2/m128
	{ NULL, FCML_AMT_SSE41_SIMD, 0x1001, 0x00EC8000, { 0x0F, 0x38, 0x3A }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.66.0F38.WIG 3A /r VPMINUW xmm1,xmm2,xmm3/m128
	{ "vpminuw", FCML_AMT_AVX_SIMD, 0x10C0, 0x00EC8000, { 0x0F, 0x38, 0x3A }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.256.66.0F38.WIG 3A /r VPMINUW ymm1,ymm2,ymm3/m256
	{ "vpminuw", FCML_AMT_AVX_SIMD, 0x10A0, 0x00EC8000, { 0x0F, 0x38, 0x3A }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_YMM_256, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PMINUD[] = {
	// 66 0F 38 3B /r PMINUD xmm1,xmm2/m128
	{ NULL, FCML_AMT_SSE41_SIMD, 0x1001, 0x00EC8000, { 0x0F, 0x38, 0x3B }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.66.0F38.WIG 3B /r VPMINUD xmm1,xmm2,xmm3/m128
	{ "vpminud", FCML_AMT_AVX_SIMD, 0x10C0, 0x00EC8000, { 0x0F, 0x38, 0x3B }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.256.66.0F38.WIG 3B /r VPMINUD ymm1,ymm2,ymm3/m256
	{ "vpminud", FCML_AMT_AVX2_SIMD, 0x10A0, 0x00EC8000, { 0x0F, 0x38, 0x3B }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_YMM_256, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PMOVMSKB[] = {
	// 0F D7 /r1 PMOVMSKB reg, mm
	{ NULL, FCML_AMT_SSE_SIMD, 0x0000, 0x40DA8000, { 0x0F, 0xD7, 0x00 }, { FCML_OP_R(FCML_REG_GPR, FCML_EOS_EOSA), FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_MWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 66 0F D7 /r PMOVMSKB reg, xmm
	{ NULL, FCML_AMT_SSE_SIMD, 0x1001, 0x40DA8000, { 0x0F, 0xD7, 0x00 }, { FCML_OP_R(FCML_REG_GPR, FCML_EOS_EOSA), FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_OWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.128.66.0F.WIG D7 /r VPMOVMSKB reg,xmm1
	{ "vpmovmskb", FCML_AMT_AVX_SIMD, 0x13C0, 0x40DA8000, { 0x0F, 0xD7, 0x22 }, { FCML_OP_MODRM_R_W, FCML_OP_VEX_VVVV_REG( FCML_REG_SIMD, FCML_EOS_OWORD ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.256.66.0F.WIG D7 /r VPMOVMSKB reg,ymm1
	{ "vpmovmskb", FCML_AMT_AVX2_SIMD, 0x13A0, 0x40DA8000, { 0x0F, 0xD7, 0x22 }, { FCML_OP_MODRM_R_W, FCML_OP_VEX_VVVV_REG( FCML_REG_SIMD, FCML_EOS_YWORD ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PMOVSX[] = {
	// 66 0f 38 20 /r PMOVSXBW xmm1,xmm2/m64
	{ "pmovsxbw", FCML_AMT_SSE41_SIMD, 0x1001, 0x00EC8000, { 0x0F, 0x38, 0x20 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 66 0f 38 21 /r PMOVSXBD xmm1,xmm2/m32
	{ "pmovsxbd", FCML_AMT_SSE41_SIMD, 0x1001, 0x00EC8000, { 0x0F, 0x38, 0x21 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_32, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 66 0f 38 22 /r PMOVSXBQ xmm1,xmm2/m16
	{ "pmovsxbq", FCML_AMT_SSE41_SIMD, 0x1001, 0x00EC8000, { 0x0F, 0x38, 0x22 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_16, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 66 0f 38 23 /r PMOVSXWD xmm1,xmm2/m64
	{ "pmovsxwd", FCML_AMT_SSE41_SIMD, 0x1001, 0x00EC8000, { 0x0F, 0x38, 0x23 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 66 0f 38 24 /r PMOVSXWQ xmm1,xmm2/m32
	{ "pmovsxwq", FCML_AMT_SSE41_SIMD, 0x1001, 0x00EC8000, { 0x0F, 0x38, 0x24 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_32, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 66 0f 38 25 /r PMOVSXDQ xmm1,xmm2/m64
	{ "pmovsxdq", FCML_AMT_SSE41_SIMD, 0x1001, 0x00EC8000, { 0x0F, 0x38, 0x25 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.128.66.0F38.WIG 20 /r VPMOVSXBW xmm1,xmm2/m64
	{ "vpmovsxbw", FCML_AMT_AVX_SIMD, 0x11C0, 0x00EC8000, { 0x0F, 0x38, 0x20 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.128.66.0F38.WIG 21 /r VPMOVSXBD xmm1,xmm2/m32
	{ "vpmovsxbd", FCML_AMT_AVX_SIMD, 0x11C0, 0x00EC8000, { 0x0F, 0x38, 0x21 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_32, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.128.66.0F38.WIG 22 /r VPMOVSXBQ xmm1,xmm2/m16
	{ "vpmovsxbq", FCML_AMT_AVX_SIMD, 0x11C0, 0x00EC8000, { 0x0F, 0x38, 0x22 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_16, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.128.66.0F38.WIG 23 /r VPMOVSXWD xmm1,xmm2/m64
	{ "vpmovsxwd", FCML_AMT_AVX_SIMD, 0x11C0, 0x00EC8000, { 0x0F, 0x38, 0x23 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.128.66.0F38.WIG 24 /r VPMOVSXWQ xmm1,xmm2/m32
	{ "vpmovsxwq", FCML_AMT_AVX_SIMD, 0x11C0, 0x00EC8000, { 0x0F, 0x38, 0x24 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_32, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.128.66.0F38.WIG 25 /r VPMOVSXDQ xmm1,xmm2/m64
	{ "vpmovsxdq", FCML_AMT_AVX_SIMD, 0x11C0, 0x00EC8000, { 0x0F, 0x38, 0x25 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.256.66.0F38.WIG 20 /r VPMOVSXBW ymm1,xmm2/m128
	{ "vpmovsxbw", FCML_AMT_AVX2_SIMD, 0x11A0, 0x00EC8000, { 0x0F, 0x38, 0x20 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.256.66.0F38.WIG 21 /r VPMOVSXBD ymm1,xmm2/m64
	{ "vpmovsxbd", FCML_AMT_AVX2_SIMD, 0x11A0, 0x00EC8000, { 0x0F, 0x38, 0x21 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_MODRM_RM_XMM_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.256.66.0F38.WIG 22 /r VPMOVSXBQ ymm1,xmm2/m32
	{ "vpmovsxbq", FCML_AMT_AVX2_SIMD, 0x11A0, 0x00EC8000, { 0x0F, 0x38, 0x22 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_MODRM_RM_XMM_32, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PMOVZX[] = {
	// 66 0f 38 30 /r PMOVZXBW xmm1,xmm2/m64
	{ "pmovzxbw", FCML_AMT_SSE41_SIMD, 0x1001, 0x00EC8000, { 0x0F, 0x38, 0x30 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 66 0f 38 31 /r PMOVZXBD xmm1,xmm2/m32
	{ "pmovzxbd", FCML_AMT_SSE41_SIMD, 0x1001, 0x00EC8000, { 0x0F, 0x38, 0x31 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_32, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 66 0f 38 32 /r PMOVZXBQ xmm1,xmm2/m16
	{ "pmovzxbq", FCML_AMT_SSE41_SIMD, 0x1001, 0x00EC8000, { 0x0F, 0x38, 0x32 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_16, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 66 0f 38 33 /r PMOVZXWD xmm1,xmm2/m64
	{ "pmovzxwd", FCML_AMT_SSE41_SIMD, 0x1001, 0x00EC8000, { 0x0F, 0x38, 0x33 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 66 0f 38 34 /r PMOVZXWQ xmm1,xmm2/m32
	{ "pmovzxwq", FCML_AMT_SSE41_SIMD, 0x1001, 0x00EC8000, { 0x0F, 0x38, 0x34 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_32, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 66 0f 38 35 /r PMOVZXDQ xmm1,xmm2/m64
	{ "pmovzxdq", FCML_AMT_SSE41_SIMD, 0x1001, 0x00EC8000, { 0x0F, 0x38, 0x35 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.128.66.0F38.WIG 30 /r VPMOVZXBW xmm1,xmm2/m64
	{ "vpmovzxbw", FCML_AMT_AVX_SIMD, 0x11C0, 0x00EC8000, { 0x0F, 0x38, 0x30 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.128.66.0F38.WIG 31 /r VPMOVZXBD xmm1,xmm2/m32
	{ "vpmovzxbd", FCML_AMT_AVX_SIMD, 0x11C0, 0x00EC8000, { 0x0F, 0x38, 0x31 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_32, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.128.66.0F38.WIG 32 /r VPMOVZXBQ xmm1,xmm2/m16
	{ "vpmovzxbq", FCML_AMT_AVX_SIMD, 0x11C0, 0x00EC8000, { 0x0F, 0x38, 0x32 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_16, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.128.66.0F38.WIG 33 /r VPMOVZXWD xmm1,xmm2/m64
	{ "vpmovzxwd", FCML_AMT_AVX_SIMD, 0x11C0, 0x00EC8000, { 0x0F, 0x38, 0x33 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.128.66.0F38.WIG 34 /r VPMOVZXWQ xmm1,xmm2/m32
	{ "vpmovzxwq", FCML_AMT_AVX_SIMD, 0x11C0, 0x00EC8000, { 0x0F, 0x38, 0x34 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_32, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.128.66.0F38.WIG 35 /r VPMOVZXDQ xmm1,xmm2/m64
	{ "vpmovzxdq", FCML_AMT_AVX_SIMD, 0x11C0, 0x00EC8000, { 0x0F, 0x38, 0x35 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.256.66.0F38.WIG 30 /r VPMOVZXBW ymm1,xmm2/m128
	{ "vpmovzxbw", FCML_AMT_AVX_SIMD, 0x11A0, 0x00EC8000, { 0x0F, 0x38, 0x30 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.256.66.0F38.WIG 31FCML_AMT_AVX_SIMD/r VPMOVZXBD ymm1,xmm2/m64
	{ "vpmovzxbd", FCML_AMT_AVX2_SIMD, 0x11A0, 0x00EC8000, { 0x0F, 0x38, 0x31 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_MODRM_RM_XMM_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.256.66.0F38.WIG 32 /r VPMOVZXBQ ymm1,xmm2/m32
	{ "vpmovzxbq", FCML_AMT_AVX2_SIMD, 0x11A0, 0x00EC8000, { 0x0F, 0x38, 0x32 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_MODRM_RM_XMM_32, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.256.66.0F38.WIG 33 /r VPMOVZXWD ymm1,xmm2/m128
	{ "vpmovzxwd", FCML_AMT_AVX2_SIMD, 0x11A0, 0x00EC8000, { 0x0F, 0x38, 0x33 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PMULDQ[] = {
	// 66 0F 38 28 /r PMULDQ xmm1,xmm2/m128
	{ NULL, FCML_AMT_SSE41_SIMD, 0x1001, 0x00EC8000, { 0x0F, 0x38, 0x28 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.66.0F38.WIG 28 /r VPMULDQ xmm1,xmm2,xmm3/m128
	{ "vpmuldq", FCML_AMT_AVX_SIMD, 0x10C0, 0x00EC8000, { 0x0F, 0x38, 0x28 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.256.66.0F38.WIG 28 /r VPMULDQ ymm1,ymm2,ymm3/m256
	{ "vpmuldq", FCML_AMT_AVX2_SIMD, 0x10A0, 0x00EC8000, { 0x0F, 0x38, 0x28 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_YMM_256, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PMULHRSW[] = {
	// 0F 38 0B /r PMULHRSW mm1,mm2/m64
	{ NULL, FCML_AMT_SSSE3_SIMD, 0x0000, 0x00EC8000, { 0x0F, 0x38, 0x0B }, { FCML_OP_MODRM_R_MMX_W, FCML_OP_MODRM_RM_MMX, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 66 0F 38 0B /r PMULHRSW xmm1,xmm2/m128
	{ NULL, FCML_AMT_SSSE3_SIMD, 0x1001, 0x00EC8000, { 0x0F, 0x38, 0x0B }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.66.0F38.WIG 0B /r VPMULHRSW xmm1,xmm2,xmm3/m128
	{ "vpmulhrsw", FCML_AMT_AVX_SIMD, 0x10C0, 0x00EC8000, { 0x0F, 0x38, 0x0B }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.256.66.0F38.WIG 0B /r VPMULHRSW ymm1,ymm2,ymm3/m256
	{ "vpmulhrsw", FCML_AMT_AVX2_SIMD, 0x10A0, 0x00EC8000, { 0x0F, 0x38, 0x0B }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_YMM_256, FCML_NA, FCML_NA }, FCML_AM_NONE }

};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PMULHUW[] = {
	// 0F E4 /r PMULHUW mm1,mm2/m64
	{ NULL, FCML_AMT_SSE_SIMD, 0x0000, 0x00D88000, { 0x0F, 0xE4, 0x00 }, { FCML_OP_MODRM_R_MMX_W, FCML_OP_MODRM_RM_MMX, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 66 0F E4 /r PMULHUW xmm1,xmm2/m128
	{ NULL, FCML_AMT_SSE_SIMD, 0x1001, 0x00D88000, { 0x0F, 0xE4, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.66.0F.WIG E4 /r VPMULHUW xmm1,xmm2,xmm3/m128
	{ "vpmulhuw", FCML_AMT_AVX_SIMD, 0x10C0, 0x00D88000, { 0x0F, 0xE4, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.256.66.0F.WIG E4 /r VPMULHUW ymm1,ymm2,ymm3/m256
	{ "vpmulhuw", FCML_AMT_AVX2_SIMD, 0x10A0, 0x00D88000, { 0x0F, 0xE4, 0x00 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_YMM_256, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PMULHW[] = {
	// 0F E5 /r PMULHW mm,mm/m64
	{ NULL, FCML_AMT_MMX_SIMD, 0x0000, 0x00D88000, { 0x0F, 0xE5, 0x00 }, { FCML_OP_MODRM_R_MMX_W, FCML_OP_MODRM_RM_MMX, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 66 0F E5 /r PMULHW xmm1,xmm2/m128
	{ NULL, FCML_AMT_SSE2_SIMD, 0x1001, 0x00D88000, { 0x0F, 0xE5, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.66.0F.WIG E5 /r VPMULHW xmm1,xmm2,xmm3/m128
	{ "vpmulhw", FCML_AMT_AVX_SIMD, 0x10C0, 0x00D88000, { 0x0F, 0xE5, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.256.66.0F.WIG E5 /r VPMULHW ymm1,ymm2,ymm3/m256
	{ "vpmulhw", FCML_AMT_AVX2_SIMD, 0x10A0, 0x00D88000, { 0x0F, 0xE5, 0x00 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_YMM_256, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PMULUDQ[] = {
	// 0F F4 /r1 PMULUDQ mm1,mm2/m64
	{ NULL, FCML_AMT_SSE2_SIMD, 0x0000, 0x00D88000, { 0x0F, 0xF4, 0x00 }, { FCML_OP_MODRM_R_MMX_W, FCML_OP_MODRM_RM_MMX, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 66 0F F4 /r PMULUDQ xmm1,xmm2/m128
	{ NULL, FCML_AMT_SSE2_SIMD, 0x1001, 0x00D88000, { 0x0F, 0xF4, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.66.0F.WIG F4 /r VPMULUDQ xmm1,xmm2,xmm3/m128
	{ "vpmuludq", FCML_AMT_AVX_SIMD, 0x10C0, 0x00D88000, { 0x0F, 0xF4, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.256.66.0F.WIG F4 /r VPMULUDQ ymm1,ymm2,ymm3/m256
	{ "vpmuludq", FCML_AMT_AVX2_SIMD, 0x10A0, 0x00D88000, { 0x0F, 0xF4, 0x00 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_YMM_256, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PMULLW[] = {
	// 0F D5 /r PMULLW mm,mm/m64
	{ NULL, FCML_AMT_MMX_SIMD, 0x0000, 0x00D88000, { 0x0F, 0xD5, 0x00 }, { FCML_OP_MODRM_R_MMX_W, FCML_OP_MODRM_RM_MMX, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 66 0F D5 /r PMULLW xmm1,xmm2/m128
	{ NULL, FCML_AMT_SSE2_SIMD, 0x1001, 0x00D88000, { 0x0F, 0xD5, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.66.0F.WIG D5 /r VPMULLW xmm1,xmm2,xmm3/m128
	{ "vpmullw", FCML_AMT_AVX_SIMD, 0x10C0, 0x00D88000, { 0x0F, 0xD5, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.256.66.0F.WIG D5 /r VPMULLW ymm1,ymm2,ymm3/m256
	{ "vpmullw", FCML_AMT_AVX2_SIMD, 0x10A0, 0x00D88000, { 0x0F, 0xD5, 0x00 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_YMM_256, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PMULLD[] = {
	// 66 0F 38 40 /r PMULLD xmm1,xmm2/m128
	{ NULL, FCML_AMT_SSE41_SIMD, 0x1001, 0x00EC8000, { 0x0F, 0x38, 0x40 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.66.0F38.WIG 40 /r VPMULLD xmm1,xmm2,xmm3/m128
	{ "vpmulld", FCML_AMT_AVX_SIMD, 0x10C0, 0x00EC8000, { 0x0F, 0x38, 0x40 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.256.66.0F38.WIG 40 /r VPMULLD ymm1,ymm2,ymm3/m256
	{ "vpmulld", FCML_AMT_AVX_SIMD, 0x10A0, 0x00EC8000, { 0x0F, 0x38, 0x40 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_YMM_256, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_POP[] = {
	// 8F /0 POP r/m16 M Valid Valid Pop top of stack into m16; increment stack pointer.
	// 8F /0 POP r/m32 M N.E. Valid Pop top of stack into m32; increment stack pointer.
	// 8F /0 POP r/m64 M Valid N.E. Pop top of stack into m64; increment stack pointer. Cannot encode 32-bit operand size.
	{ NULL, FCML_AMT_GPI, 0x0010, 0x00458000, { 0x8F, 0x00, 0x00 }, { FCML_OP_MODRM_RM_W, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	{ NULL, FCML_AMT_GPI, 0x0010, 0x01858000, { 0x8F, 0x00, 0x00 }, { FCML_OP_MODRM_RM_16_W, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	{ NULL, FCML_AMT_GPI, 0x0000, 0x46858000, { 0x8F, 0x00, 0x00 }, { FCML_OP_MODRM_RM_64_W, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 58+ rw POP r16 O Valid Valid Pop top of stack into r16; increment stack pointer.
	// 58+ rd POP r32 O N.E. Valid Pop top of stack into r32; increment stack pointer.
	// 58+ rd POP r64 O Valid N.E. Pop top of stack into r64; increment stack pointer. Cannot encode 32-bit operand size.
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00440001, { 0x58, 0x00, 0x00 }, { FCML_OP_OPCODE_REG( FCML_REG_GPR, FCML_EOS_EOSA), FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	{ NULL, FCML_AMT_GPI, 0x0000, 0x01840001, { 0x58, 0x00, 0x00 }, { FCML_OP_OPCODE_REG( FCML_REG_GPR, FCML_EOS_WORD ), FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	{ NULL, FCML_AMT_GPI, 0x0000, 0x06840001, { 0x58, 0x00, 0x00 }, { FCML_OP_OPCODE_REG( FCML_REG_GPR, FCML_EOS_QWORD ), FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 1F POP DS NP Invalid Valid Pop top of stack into DS; increment stack pointer.
	// 07 POP ES NP Invalid Valid Pop top of stack into ES; increment stack pointer.
	// 17 POP SS NP Invalid Valid Pop top of stack into SS; increment stack pointer.
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00440000, { 0x1F, 0x00, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_SEG, FCML_REG_DS, FCML_EOS_UNDEFINED ), FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00440000, { 0x07, 0x00, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_SEG, FCML_REG_ES, FCML_EOS_UNDEFINED ), FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00440000, { 0x17, 0x00, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_SEG, FCML_REG_SS, FCML_EOS_UNDEFINED ), FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 0F A1 POP FS NP Valid Valid Pop top of stack into FS; increment stack pointer by 16 bits.
	// 0F A1 POP FS NP N.E. Valid Pop top of stack into FS; increment stack pointer by 32 bits.
	// 0F A1 POP FS NP Valid N.E. Pop top of stack into FS; increment stack pointer by 64 bits.
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00D80000, { 0x0F, 0xA1, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_SEG, FCML_REG_FS, FCML_EOS_UNDEFINED ), FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 0F A9 POP GS NP Valid Valid Pop top of stack into GS; increment stack pointer by 16 bits.
	// 0F A9 POP GS NP N.E. Valid Pop top of stack into GS; increment stack pointer by 32 bits.
	// 0F A9 POP GS NP Valid N.E. Pop top of stack into GS; increment stack pointer by 64 bits.
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00D80000, { 0x0F, 0xA9, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_SEG, FCML_REG_GS, FCML_EOS_UNDEFINED ), FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_POPA[] = {
	// 61 POPA NP Invalid Valid Pop DI, SI, BP, BX, DX, CX, and AX.
	{ NULL, FCML_AMT_GPI, 0x0000, 0x01440000, { 0x61, 0x00, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 61 POPAD NP Invalid Valid Pop EDI, ESI, EBP, EBX, EDX, ECX, and EAX.
	{ "popad", FCML_AMT_GPI, 0x0000, 0x02440000, { 0x61, 0x00, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_POPCNT[] = {
	// F3 0F B8 /r POPCNT r16, r/m16 RM Valid Valid POPCNT on r/m16
	// F3 0F B8 /r POPCNT r32, r/m32 RM Valid Valid POPCNT on r/m32
	// F3 REX.W 0F B8 /r POPCNT r64, r/m64 RM Valid N.E. POPCNT on r/m64
	{ NULL, FCML_AMT_POPCNT, 0x4000, 0x00D88000, { 0x0F, 0xB8, 0x00 }, { FCML_OP_MODRM_R_W, FCML_OP_MODRM_RM_W, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_POPF[] = {
	// 9D POPF NP Valid Valid Pop top of stack into lower 16 bits of EFLAGS.
	{ NULL, FCML_AMT_GPI, 0x0000, 0x01C40000, { 0x9D, 0x00, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 9D POPFD NP N.E. Valid Pop top of stack into EFLAGS.
	{ "popfd", FCML_AMT_GPI, 0x0000, 0x02440000, { 0x9D, 0x00, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// REX.W + 9D POPFQ NP Valid N.E. Pop top of stack and zero-extend into RFLAGS.
	{ "popfq", FCML_AMT_GPI, 0x0000, 0x04840000, { 0x9D, 0x00, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_POR[] = {
	// 0F EB /r1 POR mm,mm/m64
	{ NULL, FCML_AMT_MMX_SIMD, 0x0000, 0x00D88000, { 0x0F, 0xEB, 0x00 }, { FCML_OP_MODRM_R_MMX_W, FCML_OP_MODRM_RM_MMX, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 66 0F EB /r POR xmm1,xmm2/m128
	{ NULL, FCML_AMT_SSE2_SIMD, 0x1001, 0x00D88000, { 0x0F, 0xEB, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.66.0F.WIG EB /r VPOR xmm1,xmm2,xmm3/m128
	{ "vpor", FCML_AMT_AVX_SIMD, 0x10C0, 0x00D88000, { 0x0F, 0xEB, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.256.66.0F.WIG EB /r VPOR ymm1,ymm2,ymm3/m256
	{ "vpor", FCML_AMT_AVX2_SIMD, 0x10A0, 0x00D88000, { 0x0F, 0xEB, 0x00 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_YMM_256, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PREFETCHT[] = {
	// 0F 18 /1 PREFETCHT0 m8 M Valid Valid Move data from m8 closer to the processor using T0 hint.
	{ "prefetcht0", FCML_AMT_SSE, 0x0000, 0x80D98800, { 0x0F, 0x18, 0x00 }, { FCML_OP_MODRM_M_8, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 0F 18 /2 PREFETCHT1 m8 M Valid Valid Move data from m8 closer to the processor using T1 hint.
	{ "prefetcht1", FCML_AMT_SSE, 0x0000, 0x80D99000, { 0x0F, 0x18, 0x00 }, { FCML_OP_MODRM_M_8, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 0F 18 /3 PREFETCHT2 m8 M Valid Valid Move data from m8 closer to the processor using T2 hint.
	{ "prefetcht2", FCML_AMT_SSE, 0x0000, 0x80D99800, { 0x0F, 0x18, 0x00 }, { FCML_OP_MODRM_M_8, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 0F 18 /0 PREFETCHNTA m8 M Valid Valid Move data from m8 closer to the processor using NTA hint.
	{ "prefetchnta", FCML_AMT_SSE, 0x0000, 0x80D98000, { 0x0F, 0x18, 0x00 }, { FCML_OP_MODRM_M_8, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PSADBW[] = {
	// 0F F6 /r PSADBW mm1,mm2/m64
	{ NULL, FCML_AMT_SSE_SIMD, 0x0000, 0x00D88000, { 0x0F, 0xF6, 0x00 }, { FCML_OP_MODRM_R_MMX_W, FCML_OP_MODRM_RM_MMX, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 66 0F F6 /r PSADBW xmm1,xmm2/m128
	{ NULL, FCML_AMT_SSE_SIMD, 0x1001, 0x00D88000, { 0x0F, 0xF6, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.66.0F.WIG F6 /r VPSADBW xmm1,xmm2,xmm3/m128
	{ "vpsadbw", FCML_AMT_AVX_SIMD, 0x10C0, 0x00D88000, { 0x0F, 0xF6, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.256.66.0F.WIG F6 /r VPSADBW ymm1,ymm2,ymm3/m256
	{ "vpsadbw", FCML_AMT_AVX2_SIMD, 0x10A0, 0x00D88000, { 0x0F, 0xF6, 0x00 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_YMM_256, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PSHUFB[] = {
	// 0F 38 00 /r PSHUFB mm1,mm2/m64
	{ NULL, FCML_AMT_SSSE3_SIMD, 0x0000, 0x00EC8000, { 0x0F, 0x38, 0x00 }, { FCML_OP_MODRM_R_MMX_W, FCML_OP_MODRM_RM_MMX, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 66 0F 38 00 /r PSHUFB xmm1,xmm2/m128
	{ NULL, FCML_AMT_SSSE3_SIMD, 0x1000, 0x00EC8000, { 0x0F, 0x38, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.66.0F38.WIG 00 /r VPSHUFB xmm1,xmm2,xmm3/m128
	{ "vpshufb", FCML_AMT_AVX_SIMD, 0x10C0, 0x00EC8000, { 0x0F, 0x38, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.256.66.0F38.WIG 00 /r VPSHUFB ymm1,ymm2,ymm3/m256
	{ "vpshufb", FCML_AMT_AVX2_SIMD, 0x10A0, 0x00EC8000, { 0x0F, 0x38, 0x00 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_YMM_256, FCML_NA, FCML_NA }, FCML_AM_NONE }

};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PSHUFD[] = {
	// 66 0F 70 /r ib PSHUFD xmm1,xmm2/m128,imm8
	{ NULL, FCML_AMT_SSE2_SIMD, 0x1000, 0x00D88000, { 0x0F, 0x70, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.128.66.0F.WIG 70 /r ib VPSHUFD xmm1,xmm2/m128,imm8
	{ "vpshufd", FCML_AMT_AVX_SIMD, 0x10C0, 0x00D88000, { 0x0F, 0x70, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.256.66.0F.WIG 70 /r ib VPSHUFD ymm1,ymm2/m256,imm8
	{ "vpshufd", FCML_AMT_AVX2_SIMD, 0x10A0, 0x00D88000, { 0x0F, 0x70, 0x00 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_MODRM_RM_YMM_256, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PSHUFHW[] = {
	// F3 0F 70 /r ib PSHUFHW xmm1,xmm2/m128,imm8
	{ NULL, FCML_AMT_SSE2_SIMD, 0x4000, 0x00D88000, { 0x0F, 0x70, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.128.F3.0F.WIG 70 /r ib VPSHUFHW xmm1,xmm2/m128,imm8
	{ "vpshufhw", FCML_AMT_AVX_SIMD, 0x40C0, 0x00D88000, { 0x0F, 0x70, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.256.F3.0F.WIG 70 /r ib VPSHUFHW ymm1,ymm2/m256,imm8
	{ "vpshufhw", FCML_AMT_AVX2_SIMD, 0x40A0, 0x00D88000, { 0x0F, 0x70, 0x00 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_MODRM_RM_YMM_256, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PSHUFLW[] = {
	// F2 0F 70 /r ib PSHUFLW xmm1,xmm2/m128,imm8
	{ NULL, FCML_AMT_SSE2_SIMD, 0x2000, 0x00D88000, { 0x0F, 0x70, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.128.F2.0F.WIG 70 /r ib VPSHUFLW xmm1,xmm2/m128,imm8
	{ "vpshuflw", FCML_AMT_AVX_SIMD, 0x20C0, 0x00D88000, { 0x0F, 0x70, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.256.F2.0F.WIG 70 /r ib VPSHUFLW ymm1,ymm2/m256,imm8
	{ "vpshuflw", FCML_AMT_AVX2_SIMD, 0x20A0, 0x00D88000, { 0x0F, 0x70, 0x00 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_MODRM_RM_YMM_256, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PSHUFW[] = {
	// 0F 70 /r ib PSHUFW mm1,mm2/m64,imm8
	{ NULL, FCML_AMT_SSE_SIMD, 0x0000, 0x00D88000, { 0x0F, 0x70, 0x00 }, { FCML_OP_MODRM_R_MMX_W, FCML_OP_MODRM_RM_MMX, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_NONE },
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PSIGN[] = {
	// 0F 38 08 /r PSIGNB mm1,mm2/m64
	{ "psignb", FCML_AMT_SSSE3_SIMD, 0x0000, 0x00EC8000, { 0x0F, 0x38, 0x08 }, { FCML_OP_MODRM_R_MMX_W, FCML_OP_MODRM_RM_MMX, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 0F 38 09 /r PSIGNW mm1,mm2/m64
	{ "psignw", FCML_AMT_SSSE3_SIMD, 0x0000, 0x00EC8000, { 0x0F, 0x38, 0x09 }, { FCML_OP_MODRM_R_MMX_W, FCML_OP_MODRM_RM_MMX, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 0F 38 0A /r PSIGND mm1,mm2/m64
	{ "psignd", FCML_AMT_SSSE3_SIMD, 0x0000, 0x00EC8000, { 0x0F, 0x38, 0x0A }, { FCML_OP_MODRM_R_MMX_W, FCML_OP_MODRM_RM_MMX, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 66 0F 38 08 /r PSIGNB xmm1,xmm2/m128
	{ "psignb", FCML_AMT_SSSE3_SIMD, 0x1000, 0x00EC8000, { 0x0F, 0x38, 0x08 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 66 0F 38 09 /r PSIGNW xmm1,xmm2/m128
	{ "psignw", FCML_AMT_SSSE3_SIMD, 0x1000, 0x00EC8000, { 0x0F, 0x38, 0x09 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 66 0F 38 0A /r PSIGND xmm1,xmm2/m128
	{ "psignd", FCML_AMT_SSSE3_SIMD, 0x1000, 0x00EC8000, { 0x0F, 0x38, 0x0A }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.66.0F38.WIG 08 /r VPSIGNB xmm1,xmm2,xmm3/m128
	{ "vpsignb", FCML_AMT_AVX_SIMD, 0x10C0, 0x00EC8000, { 0x0F, 0x38, 0x08 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.66.0F38.WIG 09 /r VPSIGNW xmm1,xmm2,xmm3/m128
	{ "vpsignw", FCML_AMT_AVX_SIMD, 0x10C0, 0x00EC8000, { 0x0F, 0x38, 0x09 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.66.0F38.WIG 0A /r VPSIGND xmm1,xmm2,xmm3/m128
	{ "vpsignd", FCML_AMT_AVX_SIMD, 0x10C0, 0x00EC8000, { 0x0F, 0x38, 0x0A }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.256.66.0F38.WIG 08 /r VPSIGNB ymm1,ymm2,ymm3/m256
	{ "vpsignb", FCML_AMT_AVX2_SIMD, 0x10A0, 0x00EC8000, { 0x0F, 0x38, 0x08 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_YMM_256, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.256.66.0F38.WIG 09 /r VPSIGNW ymm1,ymm2,ymm3/m256
	{ "vpsignw", FCML_AMT_AVX2_SIMD, 0x10A0, 0x00EC8000, { 0x0F, 0x38, 0x09 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_YMM_256, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.256.66.0F38.WIG 0A /r VPSIGND ymm1,ymm2,ymm3/m256
	{ "vpsignd", FCML_AMT_AVX2_SIMD, 0x10A0, 0x00EC8000, { 0x0F, 0x38, 0x0A }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_YMM_256, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PSLLDQ[] = {
	// 66 0F 73 /7 ib PSLLDQ xmm1,imm8
	{ NULL, FCML_AMT_SSE2_SIMD, 0x1000, 0x00DBB800, { 0x0F, 0x73, 0x00 }, { FCML_OP_RM( FCML_REG_SIMD, FCML_EOS_OWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_OP_IB, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDD.128.66.0F.WIG 73 /7 ib VPSLLDQ xmm1,xmm2,imm8
	{ "vpslldq", FCML_AMT_AVX_SIMD, 0x10C0, 0x00DBB800, { 0x0F, 0x73, 0x00 }, { FCML_OP_VEX_VVVV_SIMD_REG | FCML_OA_W, FCML_OP_RM( FCML_REG_SIMD, FCML_EOS_OWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDD.256.66.0F.WIG 73 /7 ib VPSLLDQ ymm1,ymm2,imm8
	{ "vpslldq", FCML_AMT_AVX2_SIMD, 0x10A0, 0x00DBB800, { 0x0F, 0x73, 0x00 }, { FCML_OP_VEX_VVVV_SIMD_REG | FCML_OA_W, FCML_OP_RM( FCML_REG_SIMD, FCML_EOS_YWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PSLL[] = {
	// 0F F1 /r1 PSLLW mm,mm/m64
	{ "psllw", FCML_AMT_MMX_SIMD, 0x0000, 0x00D88000, { 0x0F, 0xF1, 0x00 }, { FCML_OP_MODRM_R_MMX_W, FCML_OP_MODRM_RM_MMX, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 0F F2 /r1 PSLLD mm,mm/m64
	{ "pslld", FCML_AMT_MMX_SIMD, 0x0000, 0x00D88000, { 0x0F, 0xF2, 0x00 }, { FCML_OP_MODRM_R_MMX_W, FCML_OP_MODRM_RM_MMX, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 0F F3 /r1 PSLLQ mm,mm/m64
	{ "psllq", FCML_AMT_MMX_SIMD, 0x0000, 0x00D88000, { 0x0F, 0xF3, 0x00 }, { FCML_OP_MODRM_R_MMX_W, FCML_OP_MODRM_RM_MMX, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 66 0F F1 /r PSLLW xmm1,xmm2/m128
	{ "psllw", FCML_AMT_SSE2_SIMD, 0x1000, 0x00D88000, { 0x0F, 0xF1, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 66 0F F2 /r PSLLD xmm1,xmm2/m128
	{ "pslld", FCML_AMT_SSE2_SIMD, 0x1000, 0x00D88000, { 0x0F, 0xF2, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 66 0F F3 /r PSLLQ xmm1,xmm2/m128
	{ "psllq", FCML_AMT_SSE2_SIMD, 0x1000, 0x00D88000, { 0x0F, 0xF3, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 0F 71 /6 ib PSLLW mm,imm8
	{ "psllw", FCML_AMT_MMX_SIMD, 0x0000, 0x00DBB000, { 0x0F, 0x71, 0x00 }, { FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_QWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_OP_IB, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 0F 72 /6 ib1 PSLLD mm,imm8
	{ "pslld", FCML_AMT_MMX_SIMD, 0x0000, 0x00DBB000, { 0x0F, 0x72, 0x00 }, { FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_QWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_OP_IB, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 0F 73 /6 ib1 PSLLQ mm,imm8
	{ "psllq", FCML_AMT_MMX_SIMD, 0x0000, 0x00DBB000, { 0x0F, 0x73, 0x00 }, { FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_QWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_OP_IB, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 66 0F 71 /6 ib PSLLW xmm1,imm8
	{ "psllw", FCML_AMT_SSE2_SIMD, 0x1000, 0x00DBB000, { 0x0F, 0x71, 0x00 }, { FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_OWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_OP_IB, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 66 0F 72 /6 ib PSLLD xmm1,imm8
	{ "pslld", FCML_AMT_SSE2_SIMD, 0x1000, 0x00DBB000, { 0x0F, 0x72, 0x00 }, { FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_OWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_OP_IB, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 66 0F 73 /6 ib PSLLQ xmm1,imm8
	{ "psllq", FCML_AMT_SSE2_SIMD, 0x1000, 0x00DBB000, { 0x0F, 0x73, 0x00 }, { FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_OWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_OP_IB, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.66.0F.WIG F1 /r VPSLLW xmm1,xmm2,xmm3/m128
	// VEX.NDS.256.66.0F.WIG F1 /r VPSLLW ymm1, ymm2, xmm3/m128
	{ "vpsllw", FCML_AMT_AVX_SIMD, 0x1080, 0x00D88000, { 0x0F, 0xF1, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.66.0F.WIG F2 /r VPSLLD xmm1,xmm2,xmm3/m128
	// VEX.NDS.256.66.0F.WIG F2 /r VPSLLD ymm1, ymm2, xmm3/m128
	{ "vpslld", FCML_AMT_AVX_SIMD, 0x1080, 0x00D88000, { 0x0F, 0xF2, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.66.0F.WIG F3 /r VPSLLQ xmm1,xmm2,xmm3/m128
	// VEX.NDS.256.66.0F.WIG F3 /r VPSLLQ ymm1, ymm2, xmm3/m128
	{ "vpsllq", FCML_AMT_AVX_SIMD, 0x1080, 0x00D88000, { 0x0F, 0xF3, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDD.128.66.0F.WIG 71 /6 ib VPSLLW xmm1,xmm2,imm8
	// VEX.NDD.256.66.0F.WIG 71 /6 ib VPSLLW ymm1, ymm2, imm8
	{ "vpsllw", FCML_AMT_AVX_SIMD, 0x1080, 0x00DBB000, { 0x0F, 0x71, 0x00 }, { FCML_OP_VEX_VVVV_SIMD_REG | FCML_OA_W, FCML_OP_RM( FCML_REG_SIMD, FCML_EOS_L, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDD.128.66.0F.WIG 72 /6 ib VPSLLD xmm1,xmm2,imm8
	// VEX.NDD.256.66.0F.WIG 72 /6 ib VPSLLD ymm1, ymm2, imm8
	{ "vpslld", FCML_AMT_AVX_SIMD, 0x1080, 0x00DBB000, { 0x0F, 0x72, 0x00 }, { FCML_OP_VEX_VVVV_SIMD_REG | FCML_OA_W, FCML_OP_RM( FCML_REG_SIMD, FCML_EOS_L, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDD.128.66.0F.WIG 73 /6 ib VPSLLQ xmm1,xmm2,imm8
	// VEX.NDD.256.66.0F.WIG 73 /6 ib VPSLLQ ymm1, ymm2, imm8
	{ "vpsllq", FCML_AMT_AVX_SIMD, 0x1080, 0x00DBB000, { 0x0F, 0x73, 0x00 }, { FCML_OP_VEX_VVVV_SIMD_REG | FCML_OA_W, FCML_OP_RM( FCML_REG_SIMD, FCML_EOS_L, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PSRA[] = {
	// 0F E1 /r1 PSRAW mm,mm/m64
	// 0F E2 /r1 PSRAD mm,mm/m64
	{ "psraw", FCML_AMT_MMX_SIMD, 0x0000, 0x00D88000, { 0x0F, 0xE1, 0x00 }, { FCML_OP_MODRM_R_MMX_W, FCML_OP_MODRM_RM_MMX, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	{ "psrad", FCML_AMT_MMX_SIMD, 0x0000, 0x00D88000, { 0x0F, 0xE2, 0x00 }, { FCML_OP_MODRM_R_MMX_W, FCML_OP_MODRM_RM_MMX, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 66 0F E1 /r PSRAW xmm1,xmm2/m128
	// 66 0F E2 /r PSRAD xmm1,xmm2/m128
	{ "psraw", FCML_AMT_SSE2_SIMD, 0x1000, 0x00D88000, { 0x0F, 0xE1, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	{ "psrad", FCML_AMT_SSE2_SIMD, 0x1000, 0x00D88000, { 0x0F, 0xE2, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.66.0F.WIG E1 /r VPSRAW xmm1,xmm2,xmm3/m128
	// VEX.NDS.128.66.0F.WIG E2 /r VPSRAD xmm1,xmm2,xmm3/m128
	{ "vpsraw", FCML_AMT_AVX_SIMD, 0x10C0, 0x00D88000, { 0x0F, 0xE1, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA }, FCML_AM_NONE },
	{ "vpsrad", FCML_AMT_AVX_SIMD, 0x10C0, 0x00D88000, { 0x0F, 0xE2, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.256.66.0F.WIG E1 /r VPSRAW ymm1, ymm2, xmm3/m128
	// VEX.NDS.256.66.0F.WIG E2 /r VPSRAD ymm1, ymm2, xmm3/m128
	{ "vpsraw", FCML_AMT_AVX2_SIMD, 0x10A0, 0x00D88000, { 0x0F, 0xE1, 0x00 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA }, FCML_AM_NONE },
	{ "vpsrad", FCML_AMT_AVX2_SIMD, 0x10A0, 0x00D88000, { 0x0F, 0xE2, 0x00 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 0F 71 /4 ib1 PSRAW mm,imm8
	// 0F 72 /4 ib1 PSRAD mm,imm8
	{ "psraw", FCML_AMT_MMX_SIMD, 0x0000, 0x00DBA000, { 0x0F, 0x71, 0x00 }, { FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_MWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_OP_IB, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	{ "psrad", FCML_AMT_MMX_SIMD, 0x0000, 0x00DBA000, { 0x0F, 0x72, 0x00 }, { FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_MWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_OP_IB, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 66 0F 71 /4 ib PSRAW xmm1,imm8
	// 66 0F 72 /4 ib PSRAD xmm1,imm8
	{ "psraw", FCML_AMT_SSE2_SIMD, 0x1000, 0x00DBA000, { 0x0F, 0x71, 0x00 }, { FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_OWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_OP_IB, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	{ "psrad", FCML_AMT_SSE2_SIMD, 0x1000, 0x00DBA000, { 0x0F, 0x72, 0x00 }, { FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_OWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_OP_IB, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDD.128.66.0F.WIG 71 /4 ib VPSRAW xmm1,xmm2,imm8
	// VEX.NDD.128.66.0F.WIG 72 /4 ib VPSRAD xmm1,xmm2,imm8
	{ "vpsraw", FCML_AMT_AVX_SIMD, 0x10C0, 0x00DBA000, { 0x0F, 0x71, 0x00 }, { FCML_OP_VEX_VVVV_SIMD_REG | FCML_OA_W, FCML_OP_RM( FCML_REG_SIMD, FCML_EOS_OWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_NONE },
	{ "vpsrad", FCML_AMT_AVX_SIMD, 0x10C0, 0x00DBA000, { 0x0F, 0x72, 0x00 }, { FCML_OP_VEX_VVVV_SIMD_REG | FCML_OA_W, FCML_OP_RM( FCML_REG_SIMD, FCML_EOS_OWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDD.256.66.0F.WIG 71 /4 ib VPSRAW ymm1,ymm2,imm8
	// VEX.NDD.256.66.0F.WIG 72 /4 ib VPSRAD ymm1,ymm2,imm8
	{ "vpsraw", FCML_AMT_AVX2_SIMD, 0x10A0, 0x00DBA000, { 0x0F, 0x71, 0x00 }, { FCML_OP_VEX_VVVV_SIMD_REG | FCML_OA_W, FCML_OP_RM( FCML_REG_SIMD, FCML_EOS_YWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_NONE },
	{ "vpsrad", FCML_AMT_AVX2_SIMD, 0x10A0, 0x00DBA000, { 0x0F, 0x72, 0x00 }, { FCML_OP_VEX_VVVV_SIMD_REG | FCML_OA_W, FCML_OP_RM( FCML_REG_SIMD, FCML_EOS_YWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PSRLDQ[] = {
	// 66 0F 73 /3 ib PSRLDQ xmm1,imm8
	{ NULL, FCML_AMT_SSE2_SIMD, 0x1000, 0x00DB9800, { 0x0F, 0x73, 0x00 }, { FCML_OP_RM( FCML_REG_SIMD, FCML_EOS_OWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_OP_IB, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDD.128.66.0F.WIG 73 /3 ib VPSRLDQ xmm1,xmm2,imm8
	{ "vpsrldq", FCML_AMT_AVX_SIMD, 0x10C0, 0x00DB9800, { 0x0F, 0x73, 0x00 }, { FCML_OP_VEX_VVVV_SIMD_REG | FCML_OA_W, FCML_OP_RM( FCML_REG_SIMD, FCML_EOS_OWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDD.256.66.0F.WIG 73 /3 ib VPSRLDQ ymm1,ymm2,imm8
	{ "vpsrldq", FCML_AMT_AVX2_SIMD, 0x10A0, 0x00DB9800, { 0x0F, 0x73, 0x00 }, { FCML_OP_VEX_VVVV_SIMD_REG | FCML_OA_W, FCML_OP_RM( FCML_REG_SIMD, FCML_EOS_YWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PSRL[] = {
	// 0F D1 /r PSRLW mm,mm/m64
	{ "psrlw", FCML_AMT_MMX_SIMD, 0x0000, 0x00D88000, { 0x0F, 0xD1, 0x00 }, { FCML_OP_MODRM_R_MMX_W, FCML_OP_MODRM_RM_MMX, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 0F D2 /r PSRLD mm,mm/m64
	{ "psrld", FCML_AMT_MMX_SIMD, 0x0000, 0x00D88000, { 0x0F, 0xD2, 0x00 }, { FCML_OP_MODRM_R_MMX_W, FCML_OP_MODRM_RM_MMX, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 0F D3 /r PSRLQ mm,mm/m64
	{ "psrlq", FCML_AMT_MMX_SIMD, 0x0000, 0x00D88000, { 0x0F, 0xD3, 0x00 }, { FCML_OP_MODRM_R_MMX_W, FCML_OP_MODRM_RM_MMX, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 66 0F D1 /r PSRLW xmm1,xmm2/m128
	{ "psrlw", FCML_AMT_SSE2_SIMD, 0x1000, 0x00D88000, { 0x0F, 0xD1, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 66 0F D2 /r PSRLD xmm1,xmm2/m128
	{ "psrld", FCML_AMT_SSE2_SIMD, 0x1000, 0x00D88000, { 0x0F, 0xD2, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 66 0F D3 /r PSRLQ xmm1,xmm2/m128
	{ "psrlq", FCML_AMT_SSE2_SIMD, 0x1000, 0x00D88000, { 0x0F, 0xD3, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 0F 71 /2 ib PSRLW mm,imm8
	{ "psrlw", FCML_AMT_MMX_SIMD, 0x0000, 0x00DB9000, { 0x0F, 0x71, 0x00 }, { FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_QWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_OP_IB, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 0F 72 /2 ib PSRLD mm,imm8
	{ "psrld", FCML_AMT_MMX_SIMD, 0x0000, 0x00DB9000, { 0x0F, 0x72, 0x00 }, { FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_QWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_OP_IB, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 0F 73 /2 ib PSRLQ mm,imm8
	{ "psrlq", FCML_AMT_MMX_SIMD, 0x0000, 0x00DB9000, { 0x0F, 0x73, 0x00 }, { FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_QWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_OP_IB, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 66 0F 71 /2 ib PSRLW xmm1,imm8
	{ "psrlw", FCML_AMT_SSE2_SIMD, 0x1000, 0x00DB9000, { 0x0F, 0x71, 0x00 }, { FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_OWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_OP_IB, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 66 0F 72 /2 ib PSRLD xmm1,imm8
	{ "psrld", FCML_AMT_SSE2_SIMD, 0x1000, 0x00DB9000, { 0x0F, 0x72, 0x00 }, { FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_OWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_OP_IB, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 66 0F 73 /2 ib PSRLQ xmm1,imm8
	{ "psrlq", FCML_AMT_SSE2_SIMD, 0x1000, 0x00DB9000, { 0x0F, 0x73, 0x00 }, { FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_OWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_OP_IB, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.66.0F.WIG D1 /r VPSRLW xmm1,xmm2,xmm3/m128
	{ "vpsrlw", FCML_AMT_AVX_SIMD, 0x10C0, 0x00D88000, { 0x0F, 0xD1, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.66.0F.WIG D2 /r VPSRLD xmm1,xmm2,xmm3/m128
	{ "vpsrld", FCML_AMT_AVX_SIMD, 0x10C0, 0x00D88000, { 0x0F, 0xD2, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.66.0F.WIG D3 /r VPSRLQ xmm1,xmm2,xmm3/m128
	{ "vpsrlq", FCML_AMT_AVX_SIMD, 0x10C0, 0x00D88000, { 0x0F, 0xD3, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.256.66.0F.WIG D1 /r VPSRLW ymm1,ymm2,xmm3/m128
	{ "vpsrlw", FCML_AMT_AVX2_SIMD, 0x10A0, 0x00D88000, { 0x0F, 0xD1, 0x00 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.256.66.0F.WIG D2 /r VPSRLD ymm1,ymm2,xmm3/m128
	{ "vpsrld", FCML_AMT_AVX2_SIMD, 0x10A0, 0x00D88000, { 0x0F, 0xD2, 0x00 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDD.128.66.0F.WIG 71 /2 ib VPSRLW xmm1,xmm2,imm8
	{ "vpsrlw", FCML_AMT_AVX_SIMD, 0x10C0, 0x00DB9000, { 0x0F, 0x71, 0x00 }, { FCML_OP_VEX_VVVV_SIMD_REG | FCML_OA_W, FCML_OP_RM( FCML_REG_SIMD, FCML_EOS_OWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDD.128.66.0F.WIG 72 /2 ib VPSRLD xmm1,xmm2,imm8
	{ "vpsrld", FCML_AMT_AVX_SIMD, 0x10C0, 0x00DB9000, { 0x0F, 0x72, 0x00 }, { FCML_OP_VEX_VVVV_SIMD_REG | FCML_OA_W, FCML_OP_RM( FCML_REG_SIMD, FCML_EOS_OWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDD.128.66.0F.WIG 73 /2 ib VPSRLQ xmm1,xmm2,imm8
	{ "vpsrlq", FCML_AMT_AVX_SIMD, 0x10C0, 0x00DB9000, { 0x0F, 0x73, 0x00 }, { FCML_OP_VEX_VVVV_SIMD_REG | FCML_OA_W, FCML_OP_RM( FCML_REG_SIMD, FCML_EOS_OWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDD.256.66.0F.WIG 71 /2 ib VPSRLW ymm1,ymm2,imm8
	{ "vpsrlw", FCML_AMT_AVX2_SIMD, 0x10A0, 0x00DB9000, { 0x0F, 0x71, 0x00 }, { FCML_OP_VEX_VVVV_SIMD_REG | FCML_OA_W, FCML_OP_RM( FCML_REG_SIMD, FCML_EOS_YWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PSUB[] = {
	// 0F F8 /r PSUBB mm,mm/m64
	{ "psubb", FCML_AMT_MMX_SIMD, 0x0000, 0x00D88000, { 0x0F, 0xF8, 0x00 }, { FCML_OP_MODRM_R_MMX_W, FCML_OP_MODRM_RM_MMX, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 0F F9 /r PSUBW mm,mm/m64
	{ "psubw", FCML_AMT_MMX_SIMD, 0x0000, 0x00D88000, { 0x0F, 0xF9, 0x00 }, { FCML_OP_MODRM_R_MMX_W, FCML_OP_MODRM_RM_MMX, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 0F FA /r PSUBD mm,mm/m64
	{ "psubd", FCML_AMT_MMX_SIMD, 0x0000, 0x00D88000, { 0x0F, 0xFA, 0x00 }, { FCML_OP_MODRM_R_MMX_W, FCML_OP_MODRM_RM_MMX, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 66 0F F8 /r PSUBB xmm1,xmm2/m128
	{ "psubb", FCML_AMT_SSE2_SIMD, 0x1001, 0x00D88000, { 0x0F, 0xF8, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 66 0F F9 /r PSUBW xmm1,xmm2/m128
	{ "psubw", FCML_AMT_SSE2_SIMD, 0x1001, 0x00D88000, { 0x0F, 0xF9, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 66 0F FA /r PSUBD xmm1,xmm2/m128
	{ "psubd", FCML_AMT_SSE2_SIMD, 0x1001, 0x00D88000, { 0x0F, 0xFA, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.66.0F.WIG F8 /r VPSUBB xmm1,xmm2,xmm3/m128
	{ "vpsubb", FCML_AMT_AVX_SIMD, 0x10C0, 0x00D88000, { 0x0F, 0xF8, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA }, FCML_AM_NONE },
    // VEX.NDS.128.66.0F.WIG F9 /r VPSUBW xmm1,xmm2,xmm3/m128
	{ "vpsubw", FCML_AMT_AVX_SIMD, 0x10C0, 0x00D88000, { 0x0F, 0xF9, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.66.0F.WIG FA /r VPSUBD xmm1,xmm2,xmm3/m128
	{ "vpsubd", FCML_AMT_AVX_SIMD, 0x10C0, 0x00D88000, { 0x0F, 0xFA, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.256.66.0F.WIG F8 /r VPSUBB ymm1,ymm2,ymm3/m256
	{ "vpsubb", FCML_AMT_AVX2_SIMD, 0x10A0, 0x00D88000, { 0x0F, 0xF8, 0x00 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_YMM_256, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.256.66.0F.WIG F9 /r VPSUBW ymm1,ymm2,ymm3/m256
	{ "vpsubw", FCML_AMT_AVX2_SIMD, 0x10A0, 0x00D88000, { 0x0F, 0xF9, 0x00 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_YMM_256, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.256.66.0F.WIG FA /r VPSUBD ymm1,ymm2,ymm3/m256
	{ "vpsubd", FCML_AMT_AVX2_SIMD, 0x10A0, 0x00D88000, { 0x0F, 0xFA, 0x00 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_YMM_256, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.256.66.0F.WIG FB /r VPSUBQ ymm1,ymm2,ymm3/m256
	{ "vpsubq", FCML_AMT_AVX2_SIMD, 0x10A0, 0x00D88000, { 0x0F, 0xFB, 0x00 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_YMM_256, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PSUBQ[] = {
	// 0F FB /r PSUBQ mm1,mm2/m64
	{ NULL, FCML_AMT_SSE2_SIMD, 0x0000, 0x00D88000, { 0x0F, 0xFB, 0x00 }, { FCML_OP_MODRM_R_MMX_W, FCML_OP_MODRM_RM_MMX, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 66 0F FB /r PSUBQ xmm1,xmm2/m128
	{ NULL, FCML_AMT_SSE2_SIMD, 0x1000, 0x00D88000, { 0x0F, 0xFB, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.66.0F.WIG FB/r VPSUBQ xmm1,xmm2,xmm3/m128
	{ "vpsubq", FCML_AMT_AVX_SIMD, 0x10C0, 0x00D88000, { 0x0F, 0xFB, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L_128, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PSUBS[] = {
	// 0F E8 /r PSUBSB mm,mm/m64
	{ "psubsb", FCML_AMT_MMX_SIMD, 0x0000, 0x00D88000, { 0x0F, 0xE8, 0x00 }, { FCML_OP_MODRM_R_MMX_W, FCML_OP_MODRM_RM_MMX, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 0F E9 /r PSUBSW mm,mm/m64
	{ "psubsw", FCML_AMT_MMX_SIMD, 0x0000, 0x00D88000, { 0x0F, 0xE9, 0x00 }, { FCML_OP_MODRM_R_MMX_W, FCML_OP_MODRM_RM_MMX, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 66 0F E8 /r PSUBSB xmm1,xmm2/m128
	{ "psubsb", FCML_AMT_SSE2_SIMD, 0x1000, 0x00D88000, { 0x0F, 0xE8, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 66 0F E9 /r PSUBSW xmm1,xmm2/m128
	{ "psubsw", FCML_AMT_SSE2_SIMD, 0x1000, 0x00D88000, { 0x0F, 0xE9, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.66.0F.WIG E8 /r VPSUBSB xmm1,xmm2,xmm3/m128
	{ "vpsubsb", FCML_AMT_AVX_SIMD, 0x10C0, 0x00D88000, { 0x0F, 0xE8, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.66.0F.WIG E9 /r VPSUBSW xmm1,xmm2,xmm3/m128
	{ "vpsubsw", FCML_AMT_AVX_SIMD, 0x10C0, 0x00D88000, { 0x0F, 0xE9, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.256.66.0F.WIG E8 /r VPSUBSB ymm1,ymm2,ymm3/m256
	{ "vpsubsb", FCML_AMT_AVX2_SIMD, 0x10A0, 0x00D88000, { 0x0F, 0xE8, 0x00 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_YMM_256, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.256.66.0F.WIG E9 /r VPSUBSW ymm1,ymm2,ymm3/m256
	{ "vpsubsw", FCML_AMT_AVX2_SIMD, 0x10A0, 0x00D88000, { 0x0F, 0xE9, 0x00 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_YMM_256, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PSUBUS[] = {
	// 0F D8 /r PSUBUSB mm,mm/m64
	{ "psubusb", FCML_AMT_MMX_SIMD, 0x0000, 0x00D88000, { 0x0F, 0xD8, 0x00 }, { FCML_OP_MODRM_R_MMX_W, FCML_OP_MODRM_RM_MMX, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 0F D9 /r1 PSUBUSW mm,mm/m64
	{ "psubusw", FCML_AMT_MMX_SIMD, 0x0000, 0x00D88000, { 0x0F, 0xD9, 0x00 }, { FCML_OP_MODRM_R_MMX_W, FCML_OP_MODRM_RM_MMX, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 66 0F D8 /r PSUBUSB xmm1,xmm2/m128
	{ "psubusb", FCML_AMT_SSE2_SIMD, 0x1000, 0x00D88000, { 0x0F, 0xD8, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 66 0F D9 /r PSUBUSW xmm1,xmm2/m128
	{ "psubusw", FCML_AMT_SSE2_SIMD, 0x1000, 0x00D88000, { 0x0F, 0xD9, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.66.0F.WIG D8 /r VPSUBUSB xmm1,xmm2,xmm3/m128
	{ "vpsubusb", FCML_AMT_AVX_SIMD, 0x10C0, 0x00D88000, { 0x0F, 0xD8, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.66.0F.WIG D9 /r VPSUBUSW xmm1,xmm2,xmm3/m128
	{ "vpsubusw", FCML_AMT_AVX_SIMD, 0x10C0, 0x00D88000, { 0x0F, 0xD9, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.256.66.0F.WIG D8 /r VPSUBUSB ymm1,ymm2,ymm3/m256
	{ "vpsubusb", FCML_AMT_AVX2_SIMD, 0x10A0, 0x00D88000, { 0x0F, 0xD8, 0x00 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_YMM_256, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.256.66.0F.WIG D9 /r VPSUBUSW ymm1,ymm2,ymm3/m256
	{ "vpsubusw", FCML_AMT_AVX2_SIMD, 0x10A0, 0x00D88000, { 0x0F, 0xD9, 0x00 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_YMM_256, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PTEST[] = {
	// 66 0F 38 17 /r PTEST xmm1,xmm2/m128
	{ "ptest", FCML_AMT_SSE41_SIMD, 0x1000, 0x00EC8000, { 0x0F, 0x38, 0x17 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.128.66.0F38.WIG 17 /r VPTEST xmm1,xmm2/m128
	// VEX.256.66.0F38.WIG 17 /r VPTEST ymm1,ymm2/m256
	{ "vptest", FCML_AMT_AVX_SIMD, 0x1180, 0x00EC8000, { 0x0F, 0x38, 0x17 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_MODRM_RM_SIMD_L, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PUNPCKL[] = {
	// 0F 60 /r PUNPCKLBW mm,mm/m32
	{ "punpcklbw", FCML_AMT_MMX_SIMD, 0x0000, 0x00D88000, { 0x0F, 0x60, 0x00 }, { FCML_OP_MODRM_R_MMX_W, FCML_OP_MODRM_RM_MMX_32, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 0F 61 /r PUNPCKLWD mm,mm/m32
	{ "punpcklwd", FCML_AMT_MMX_SIMD, 0x0000, 0x00D88000, { 0x0F, 0x61, 0x00 }, { FCML_OP_MODRM_R_MMX_W, FCML_OP_MODRM_RM_MMX_32, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 0F 62 /r PUNPCKLDQ mm,mm/m32
	{ "punpckldq", FCML_AMT_MMX_SIMD, 0x0000, 0x00D88000, { 0x0F, 0x62, 0x00 }, { FCML_OP_MODRM_R_MMX_W, FCML_OP_MODRM_RM_MMX_32, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 66 0F 60 /r PUNPCKLBW xmm1,xmm2/m128
	{ "punpcklbw", FCML_AMT_SSE2, 0x1000, 0x00D88000, { 0x0F, 0x60, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 66 0F 61 /r PUNPCKLWD xmm1,xmm2/m128
	{ "punpcklwd", FCML_AMT_SSE2, 0x1000, 0x00D88000, { 0x0F, 0x61, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 66 0F 62 /r PUNPCKLDQ xmm1,xmm2/m128
	{ "punpckldq", FCML_AMT_SSE2, 0x1000, 0x00D88000, { 0x0F, 0x62, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 66 0F 6C /r PUNPCKLQDQ xmm1,xmm2/m128
	{ "punpcklqdq", FCML_AMT_SSE2, 0x1000, 0x00D88000, { 0x0F, 0x6C, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.66.0F.WIG 60 /r VPUNPCKLBW xmm1,xmm2,xmm3/m128
	{ "vpunpcklbw", FCML_AMT_AVX_SIMD, 0x10C0, 0x00D88000, { 0x0F, 0x60, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.66.0F.WIG 61 /r VPUNPCKLWD xmm1,xmm2,xmm3/m128
	{ "vpunpcklwd", FCML_AMT_AVX_SIMD, 0x10C0, 0x00D88000, { 0x0F, 0x61, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.66.0F.WIG 62 /r VPUNPCKLDQ xmm1,xmm2,xmm3/m128
	{ "vpunpckldq", FCML_AMT_AVX_SIMD, 0x10C0, 0x00D88000, { 0x0F, 0x62, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.66.0F.WIG 6C /r VPUNPCKLQDQ xmm1,xmm2,xmm3/m128
	{ "vpunpcklqdq", FCML_AMT_AVX_SIMD, 0x10C0, 0x00D88000, { 0x0F, 0x6C, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.256.66.0F.WIG 60 /r VPUNPCKLBW ymm1,ymm2,ymm3/m256
	{ "vpunpcklbw", FCML_AMT_AVX2_SIMD, 0x10A0, 0x00D88000, { 0x0F, 0x60, 0x00 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_YMM_256, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.256.66.0F.WIG 61 /r VPUNPCKLWD ymm1,ymm2,ymm3/m256
	{ "vpunpcklwd", FCML_AMT_AVX2_SIMD, 0x10A0, 0x00D88000, { 0x0F, 0x61, 0x00 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_YMM_256, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.256.66.0F.WIG 62 /r VPUNPCKLDQ ymm1,ymm2,ymm3/m256
	{ "vpunpckldq", FCML_AMT_AVX2_SIMD, 0x10A0, 0x00D88000, { 0x0F, 0x62, 0x00 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_YMM_256, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.256.66.0F.WIG 6C /r VPUNPCKLQDQ ymm1,ymm2,ymm3/m256
	{ "vpunpcklqdq", FCML_AMT_AVX2_SIMD, 0x10A0, 0x00D88000, { 0x0F, 0x6C, 0x00 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_YMM_256, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PUNPCKH[] = {
	// 0F 68 /r PUNPCKHBW mm,mm/m64
	{ "punpckhbw", FCML_AMT_MMX_SIMD, 0x0000, 0x00D88000, { 0x0F, 0x68, 0x00 }, { FCML_OP_MODRM_R_MMX_W, FCML_OP_MODRM_RM_MMX, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 0F 69 /r PUNPCKHWD mm,mm/m64
	{ "punpckhwd", FCML_AMT_MMX_SIMD, 0x0000, 0x00D88000, { 0x0F, 0x69, 0x00 }, { FCML_OP_MODRM_R_MMX_W, FCML_OP_MODRM_RM_MMX, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 0F 6A /r PUNPCKHDQ mm,mm/m64
	{ "punpckhdq", FCML_AMT_MMX_SIMD, 0x0000, 0x00D88000, { 0x0F, 0x6A, 0x00 }, { FCML_OP_MODRM_R_MMX_W, FCML_OP_MODRM_RM_MMX, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 66 0F 68 /r PUNPCKHBW xmm1,xmm2/m128
	{ "punpckhbw", FCML_AMT_SSE2_SIMD, 0x1000, 0x00D88000, { 0x0F, 0x68, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 66 0F 69 /r PUNPCKHWD xmm1,xmm2/m128
	{ "punpckhwd", FCML_AMT_SSE2_SIMD, 0x1000, 0x00D88000, { 0x0F, 0x69, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 66 0F 6A /r PUNPCKHDQ xmm1,xmm2/m128
	{ "punpckhdq", FCML_AMT_SSE2_SIMD, 0x1000, 0x00D88000, { 0x0F, 0x6A, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 66 0F 6D /r PUNPCKHQDQ xmm1,xmm2/m128
	{ "punpckhqdq", FCML_AMT_SSE2_SIMD, 0x1000, 0x00D88000, { 0x0F, 0x6D, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.66.0F.WIG 68 /r VPUNPCKHBW xmm1,xmm2,xmm3/m128
	{ "vpunpckhbw", FCML_AMT_AVX_SIMD, 0x10C0, 0x00D88000, { 0x0F, 0x68, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.66.0F.WIG 69 /r VPUNPCKHWD xmm1,xmm2,xmm3/m128
	{ "vpunpckhwd", FCML_AMT_AVX_SIMD, 0x10C0, 0x00D88000, { 0x0F, 0x69, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.66.0F.WIG 6A /r VPUNPCKHDQ xmm1,xmm2,xmm3/m128
	{ "vpunpckhdq", FCML_AMT_AVX_SIMD, 0x10C0, 0x00D88000, { 0x0F, 0x6A, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.66.0F.WIG 6D /r VPUNPCKHQDQ xmm1,xmm2,xmm3/m128
	{ "vpunpckhqdq", FCML_AMT_AVX_SIMD, 0x10C0, 0x00D88000, { 0x0F, 0x6D, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.256.66.0F.WIG 68 /r VPUNPCKHBW ymm1,ymm2,ymm3/m256
	{ "vpunpckhbw", FCML_AMT_AVX2_SIMD, 0x10A0, 0x00D88000, { 0x0F, 0x68, 0x00 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_YMM_256, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.256.66.0F.WIG 69 /r VPUNPCKHWD ymm1,ymm2,ymm3/m256
	{ "vpunpckhwd", FCML_AMT_AVX2_SIMD, 0x10A0, 0x00D88000, { 0x0F, 0x69, 0x00 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_YMM_256, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.256.66.0F.WIG 6A /r VPUNPCKHDQ ymm1,ymm2,ymm3/m256
	{ "vpunpckhdq", FCML_AMT_AVX2_SIMD, 0x10A0, 0x00D88000, { 0x0F, 0x6A, 0x00 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_YMM_256, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.256.66.0F.WIG 6D /r VPUNPCKHQDQ ymm1,ymm2,ymm3/m256
	{ "vpunpckhqdq", FCML_AMT_AVX2_SIMD, 0x10A0, 0x00D88000, { 0x0F, 0x6D, 0x00 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_YMM_256, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PUSH[] = {
	// FF /6 PUSH r/m16 M Valid Valid Push r/m16.
	// FF /6 PUSH r/m32 M N.E. Valid Push r/m32.
	// FF /6 PUSH r/m64 M Valid N.E. Push r/m64.
	{ NULL, FCML_AMT_GPI, 0x0010, 0x0045B000, { 0xFF, 0x00, 0x00 }, { FCML_OP_MODRM_RM_W, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	{ NULL, FCML_AMT_GPI, 0x0010, 0x0185B000, { 0xFF, 0x00, 0x00 }, { FCML_OP_MODRM_RM_16_W, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	{ NULL, FCML_AMT_GPI, 0x0000, 0x4685B000, { 0xFF, 0x00, 0x00 }, { FCML_OP_MODRM_RM_64_W, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 50+rw PUSH r16 O Valid Valid Push r16.
	// 50+rd PUSH r32 O N.E. Valid Push r32.
	// 50+rd PUSH r64 O Valid N.E. Push r64.
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00440001, { 0x50, 0x00, 0x00 }, { FCML_OP_OPCODE_REG( FCML_REG_GPR, FCML_EOS_EOSA), FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	{ NULL, FCML_AMT_GPI, 0x0000, 0x01840001, { 0x50, 0x00, 0x00 }, { FCML_OP_OPCODE_REG( FCML_REG_GPR, FCML_EOS_WORD ), FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	{ NULL, FCML_AMT_GPI, 0x0000, 0x06840001, { 0x50, 0x00, 0x00 }, { FCML_OP_OPCODE_REG( FCML_REG_GPR, FCML_EOS_QWORD ), FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 6A PUSH imm8 I Valid Valid Push imm8.
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00C40000, { 0x6A, 0x00, 0x00 }, { FCML_OP_IB_EX_EOSA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 68 PUSH imm16 I Valid Valid Push imm16.
	{ NULL, FCML_AMT_GPI, 0x0000, 0x01C40000, { 0x68, 0x00, 0x00 }, { FCML_OP_IW_EX_EOSA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 68 PUSH imm32 I Valid Valid Push imm32.
	{ NULL, FCML_AMT_GPI, 0x0000, 0x06C40000, { 0x68, 0x00, 0x00 }, { FCML_OP_ID_EX_EOSA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 1E PUSH DS NP Invalid Valid Push DS.
	// 06 PUSH ES NP Invalid Valid Push ES.
	// 16 PUSH SS NP Invalid Valid Push SS.
	// 0E PUSH CS NP Invalid Valid Push CS.
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00440000, { 0x1E, 0x00, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_SEG, FCML_REG_DS, FCML_EOS_UNDEFINED ), FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00440000, { 0x06, 0x00, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_SEG, FCML_REG_ES, FCML_EOS_UNDEFINED ), FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00440000, { 0x16, 0x00, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_SEG, FCML_REG_SS, FCML_EOS_UNDEFINED ), FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00440000, { 0x0E, 0x00, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_SEG, FCML_REG_CS, FCML_EOS_UNDEFINED ), FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 0F A0 PUSH FS NP Valid Valid Push FS.
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00D80000, { 0x0F, 0xA0, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_SEG, FCML_REG_FS, FCML_EOS_UNDEFINED ), FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 0F A8 PUSH GS NP Valid Valid Push GS.
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00D80000, { 0x0F, 0xA8, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_SEG, FCML_REG_GS, FCML_EOS_UNDEFINED ), FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PUSHA[] = {
	// 60 PUSHA NP Invalid Valid Push AX, CX, DX, BX, original SP, BP, SI, and DI.
	{ NULL, FCML_AMT_GPI, 0x0000, 0x01440000, { 0x60, 0x00, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 60 PUSHAD NP Invalid Valid Push EAX, ECX, EDX, EBX, original ESP, EBP, ESI, and EDI.
	{ "pushad", FCML_AMT_GPI, 0x0000, 0x02440000, { 0x60, 0x00, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PUSHF[] = {
	// 9C PUSHF NP Valid Valid Push lower 16 bits of EFLAGS.
	{ NULL, FCML_AMT_GPI, 0x0000, 0x01C40000, { 0x9C, 0x00, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 9C PUSHFD NP N.E. Valid Push EFLAGS.
	{ "pushfd", FCML_AMT_GPI, 0x0000, 0x02440000, { 0x9C, 0x00, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 9C PUSHFQ NP Valid N.E. Push RFLAGS.
	{ "pushfq", FCML_AMT_GPI, 0x0000, 0x04840000, { 0x9C, 0x00, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PXOR[] = {
	// 0F EF /r PXOR mm,mm/m64
	{ NULL, FCML_AMT_MMX_SIMD, 0x0000, 0x00D88000, { 0x0F, 0xEF, 0x00 }, { FCML_OP_MODRM_R_MMX_W, FCML_OP_MODRM_RM_MMX, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 66 0F EF /r PXOR xmm1,xmm2/m128
	{ NULL, FCML_AMT_SSE2_SIMD, 0x1001, 0x00D88000, { 0x0F, 0xEF, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.66.0F.WIG EF /r VPXOR xmm1,xmm2,xmm3/m128
	{ "vpxor", FCML_AMT_AVX_SIMD, 0x10C0, 0x00D88000, { 0x0F, 0xEF, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.256.66.0F.WIG EF /r VPXOR ymm1,ymm2,ymm3/m256
	{ "vpxor", FCML_AMT_AVX2_SIMD, 0x10A0, 0x00D88000, { 0x0F, 0xEF, 0x00 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_YMM_256, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_RCL[] = {
	// D0 /2 RCL r/m8, 1
	// REX + D0 /2 RCL r/m8, 1
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00C59000, { 0xD0, 0x00, 0x00 }, { FCML_OP_MODRM_RM_8_W, FCML_OP_EXPLICIT_IB(1), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// D2 /2 RCL r/m8, CL
	// REX + D2 /2 RCL r/m8, CL
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00C59000, { 0xD2, 0x00, 0x00 }, { FCML_OP_MODRM_RM_8_W, FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_CL, FCML_EOS_BYTE ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// C0 /2 ib RCL r/m8, imm8
	// REX + C0 /2 ib RCL r/m8, imm8
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00C59000, { 0xC0, 0x00, 0x00 }, { FCML_OP_MODRM_RM_8_W, FCML_OP_IB, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// D1 /2 RCL r/m16, 1
	// D1 /2 RCL r/m32, 1
	// REX.W + D1 /2 RCL r/m64, 1
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00C59000, { 0xD1, 0x00, 0x00 }, { FCML_OP_MODRM_RM_W, FCML_OP_EXPLICIT_IB(1), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// D3 /2 RCL r/m16, CL
	// D3 /2 RCL r/m32, CL
	// REX.W + D3 /2 RCL r/m64, CL
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00C59000, { 0xD3, 0x00, 0x00 }, { FCML_OP_MODRM_RM_W, FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_CL, FCML_EOS_BYTE ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// C1 /2 ib RCL r/m16, imm8
	// C1 /2 ib RCL r/m32, imm8
	// REX.W + C1 /2 ib RCL r/m64, imm8
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00C59000, { 0xC1, 0x00, 0x00 }, { FCML_OP_MODRM_RM_W, FCML_OP_IB, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_RCR[] = {
	// D0 /3 RCR r/m8, 1
	// REX + D0 /3 RCR r/m8, 1
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00C59800, { 0xD0, 0x00, 0x00 }, { FCML_OP_MODRM_RM_8_W, FCML_OP_EXPLICIT_IB(1), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// D2 /3 RCR r/m8, CL
	// REX + D2 /3 RCR r/m8, CL
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00C59800, { 0xD2, 0x00, 0x00 }, { FCML_OP_MODRM_RM_8_W, FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_CL, FCML_EOS_BYTE ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// C0 /3 ib RCR r/m8, imm8
	// REX + C0 /3 ib RCR r/m8, imm8
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00C59800, { 0xC0, 0x00, 0x00 }, { FCML_OP_MODRM_RM_8_W, FCML_OP_IB, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// D1 /3 RCR r/m16, 1
	// D1 /3 RCR r/m32, 1
	// REX.W + D1 /3 RCR r/m64, 1
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00C59800, { 0xD1, 0x00, 0x00 }, { FCML_OP_MODRM_RM_W, FCML_OP_EXPLICIT_IB(1), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// D3 /3 RCR r/m16, CL
	// D3 /3 RCR r/m32, CL
	// REX.W + D3 /3 RCR r/m64, CL
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00C59800, { 0xD3, 0x00, 0x00 }, { FCML_OP_MODRM_RM_W, FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_CL, FCML_EOS_BYTE ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// C1 /3 ib RCR r/m16, imm8
	// C1 /3 ib RCR r/m32, imm8
	// REX.W + C1 /3 ib RCR r/m64, imm8
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00C59800, { 0xC1, 0x00, 0x00 }, { FCML_OP_MODRM_RM_W, FCML_OP_IB, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_ROL[] = {
	// D0 /0 ROL r/m8, 1
	// REX + D0 /0 ROL r/m8, 1
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00C58000, { 0xD0, 0x00, 0x00 }, { FCML_OP_MODRM_RM_8_W, FCML_OP_EXPLICIT_IB(1), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// D2 /0 ROL r/m8, CL
	// REX + D2 /0 ROL r/m8, CL
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00C58000, { 0xD2, 0x00, 0x00 }, { FCML_OP_MODRM_RM_8_W, FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_CL, FCML_EOS_BYTE ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// C0 /0 ib ROL r/m8, imm8
	// REX + C0 /0 ib ROL r/m8, imm8
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00C58000, { 0xC0, 0x00, 0x00 }, { FCML_OP_MODRM_RM_8_W, FCML_OP_IB, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// D1 /0 ROL r/m16, 1
	// D1 /0 ROL r/m32, 1
	// REX.W + D1 /0 ROL r/m64, 1
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00C58000, { 0xD1, 0x00, 0x00 }, { FCML_OP_MODRM_RM_W, FCML_OP_EXPLICIT_IB(1), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// D3 /0 ROL r/m16, CL
	// D3 /0 ROL r/m32, CL
	// REX.W + D3 /0 ROL r/m64, CL
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00C58000, { 0xD3, 0x00, 0x00 }, { FCML_OP_MODRM_RM_W, FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_CL, FCML_EOS_BYTE ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// C1 /0 ib ROL r/m16, imm8
	// C1 /0 ib ROL r/m32, imm8
	// C1 /0 ib ROL r/m64, imm8
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00C58000, { 0xC1, 0x00, 0x00 }, { FCML_OP_MODRM_RM_W, FCML_OP_IB, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_ROR[] = {
	// D0 /1 ROR r/m8, 1
	// REX + D0 /1 ROR r/m8, 1
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00C58800, { 0xD0, 0x00, 0x00 }, { FCML_OP_MODRM_RM_8_W, FCML_OP_EXPLICIT_IB(1), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// D2 /1 ROR r/m8, CL
	// REX + D2 /1 ROR r/m8, CL
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00C58800, { 0xD2, 0x00, 0x00 }, { FCML_OP_MODRM_RM_8_W, FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_CL, FCML_EOS_BYTE ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// C0 /1 ib ROR r/m8, imm8
	// REX + C0 /1 ib ROR r/m8, imm8
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00C58800, { 0xC0, 0x00, 0x00 }, { FCML_OP_MODRM_RM_8_W, FCML_OP_IB, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// D1 /1 ROR r/m16, 1
	// D1 /1 ROR r/m32, 1
	// REX.W + D1 /1 ROR r/m64, 1
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00C58800, { 0xD1, 0x00, 0x00 }, { FCML_OP_MODRM_RM_W, FCML_OP_EXPLICIT_IB(1), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// D3 /1 ROR r/m16, CL
	// D3 /1 ROR r/m32, CL
	// REX.W + D3 /1 ROR r/m64, CL
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00C58800, { 0xD3, 0x00, 0x00 }, { FCML_OP_MODRM_RM_W, FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_CL, FCML_EOS_BYTE ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// C1 /1 ib ROR r/m16, imm8
	// C1 /1 ib ROR r/m32, imm8
	// REX.W + C1 /1 ib ROR r/m64, imm8
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00C58800, { 0xC1, 0x00, 0x00 }, { FCML_OP_MODRM_RM_W, FCML_OP_IB, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_RCPPS[] = {
	// 0F 53 /r RCPPS xmm1,xmm2/m128
	{ NULL, FCML_AMT_SSE_SIMD, 0x0000, 0x00D88000, { 0x0F, 0x53, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.128.0F.WIG 53 /r VRCPPS xmm1,xmm2/m128
	// VEX.256.0F.WIG 53 /r VRCPPS ymm1,ymm2/m256
	{ "vrcpps", FCML_AMT_AVX_SIMD, 0x0181, 0x00D88000, { 0x0F, 0x53, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_MODRM_RM_SIMD_L, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_RCPSS[] = {
	// F3 0F 53 /r RCPSS xmm1,xmm2/m32
	{ NULL, FCML_AMT_SSE_SIMD, 0x4000, 0x00D88000, { 0x0F, 0x53, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_32, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.LIG.F3.0F.WIG 53 /r VRCPSS xmm1,xmm2,xmm3/m32
	{ "vrcpss", FCML_AMT_AVX_SIMD, 0x40C0, 0x00D88000, { 0x0F, 0x53, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L_32, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_RDFSBASE[] = {
	// F3 0F AE /0 RDFSBASE r32
	// REX.W + F3 0F AE /0 RDFSBASE r64
	{ NULL, FCML_AMT_SYSTEM, 0x4000, 0x039B8000, { 0x0F, 0xAE, 0x00 }, { FCML_OP_RM( FCML_REG_GPR, FCML_EOS_DWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ) | FCML_OA_W, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	{ NULL, FCML_AMT_SYSTEM, 0x4000, 0x049B8000, { 0x0F, 0xAE, 0x00 }, { FCML_OP_RM( FCML_REG_GPR, FCML_EOS_QWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ) | FCML_OA_W, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// F3 0F AE /1 RDGSBASE r32
	// REX.W + F3 0F AE /1 RDGSBASE r64
	{ "rdgsbase", FCML_AMT_SYSTEM, 0x4000, 0x039B8800, { 0x0F, 0xAE, 0x00 }, { FCML_OP_RM( FCML_REG_GPR, FCML_EOS_DWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ) | FCML_OA_W, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	{ "rdgsbase", FCML_AMT_SYSTEM, 0x4000, 0x049B8800, { 0x0F, 0xAE, 0x00 }, { FCML_OP_RM( FCML_REG_GPR, FCML_EOS_QWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ) | FCML_OA_W, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_RDRAND[] = {
	// 0F C7 /6 RDRAND r16
	// 0F C7 /6 RDRAND r32
	// REX.W + 0F C7 /6 RDRAND r64
	{ NULL, FCML_AMT_RDRAND, 0x0000, 0x00DBB000, { 0x0F, 0xC7, 0x00 }, { FCML_OP_RM( FCML_REG_GPR, FCML_EOS_EOSA, FCML_EOS_UNDEFINED, FCML_RMF_R ) | FCML_OA_W, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_RDTSCP[] = {
	// 0F 01 F9 RDTSCP
	{ NULL, FCML_AMT_SYSTEM, 0x0000, 0x00EC0000, { 0x0F, 0x01, 0xF9 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_RDTSC[] = {
	// 0F 31 RDTSC
	{ NULL, FCML_AMT_SYSTEM, 0x0000, 0x00D80000, { 0x0F, 0x31, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_RDPMC[] = {
	// 0F 33 RDPMC
	{ NULL, FCML_AMT_SYSTEM, 0x0000, 0x00D80000, { 0x0F, 0x33, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_RDMSR[] = {
	// 0F 32 RDMSR
	{ NULL, FCML_AMT_SYSTEM, 0x0000, 0x00D80000, { 0x0F, 0x32, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_RET[] = {
	// C3 RET
	// CB RET
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00C40000, { 0xC3, 0x00, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	{ "retf", FCML_AMT_GPI, 0x0000, 0x00C40000, { 0xCB, 0x00, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// C2 iw RET imm16
	// CA iw RET imm16
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00C40000, { 0xC2, 0x00, 0x00 }, { FCML_OP_IW, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	{ "retf", FCML_AMT_GPI, 0x0000, 0x00C40000, { 0xCA, 0x00, 0x00 }, { FCML_OP_IW, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_ROUNDPD[] = {
	// 66 0F 3A 09 /r ib ROUNDPD xmm1,xmm2/m128,imm8
	{ NULL, FCML_AMT_SSE41_SIMD, 0x1000, 0x00EC8000, { 0x0F, 0x3A, 0x09 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.128.66.0F3A.WIG 09 /r ib VROUNDPD xmm1,xmm2/m128,imm8
	// VEX.256.66.0F3A.WIG 09 /r ib VROUNDPD ymm1,ymm2/m256,imm8
	{ "vroundpd", FCML_AMT_AVX_SIMD, 0x1180, 0x00EC8000, { 0x0F, 0x3A, 0x09 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_MODRM_RM_SIMD_L, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_ROUNDPS[] = {
	// 66 0F 3A 08 /r ib ROUNDPS xmm1,xmm2/m128,imm8
	{ NULL, FCML_AMT_SSE41_SIMD, 0x1000, 0x00EC8000, { 0x0F, 0x3A, 0x08 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.128.66.0F3A.WIG 08 /r ib VROUNDPS xmm1,xmm2/m128,imm8
	// VEX.256.66.0F3A.WIG 08 /r ib VROUNDPS ymm1,ymm2/m256,imm8
	{ "vroundps", FCML_AMT_AVX_SIMD, 0x1180, 0x00EC8000, { 0x0F, 0x3A, 0x08 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_MODRM_RM_SIMD_L, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_ROUNDSD[] = {
	// 66 0F 3A 0B /r ib ROUNDSD xmm1,xmm2/m64,imm8
	{ NULL, FCML_AMT_SSE41_SIMD, 0x1000, 0x00EC8000, { 0x0F, 0x3A, 0x0B }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_64, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.LIG.66.0F3A.WIG 0B /r ib VROUNDSD xmm1,xmm2,xmm3/m64,imm8
	{ "vroundsd", FCML_AMT_AVX_SIMD, 0x10C0, 0x00EC8000, { 0x0F, 0x3A, 0x0B }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L_64, FCML_OP_IB, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_ROUNDSS[] = {
	// 66 0F 3A 0A /r ib ROUNDSS xmm1,xmm2/m32,imm8
	{ NULL, FCML_AMT_SSE41_SIMD, 0x1000, 0x00EC8000, { 0x0F, 0x3A, 0x0A }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_32, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.LIG.66.0F3A.WIG 0A ib VROUNDSS xmm1,xmm2,xmm3/m32,imm8
	{ "vroundss", FCML_AMT_AVX_SIMD, 0x10C0, 0x00EC8000, { 0x0F, 0x3A, 0x0A }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L_32, FCML_OP_IB, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_RSM[] = {
	// 0F AA RSM NP Invalid Valid Resume operation of interrupted program.
	{ NULL, FCML_AMT_SYSTEM, 0x0000, 0x00580000, { 0x0F, 0xAA, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_RSQRTPS[] = {
	// 0F 52 /r RSQRTPS xmm1,xmm2/m128
	{ NULL, FCML_AMT_SSE_SIMD, 0x0000, 0x00D88000, { 0x0F, 0x52, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.128.0F.WIG 52 /r VRSQRTPS xmm1,xmm2/m128
	// VEX.256.0F.WIG 52 /r VRSQRTPS ymm1,ymm2/m256
	{ "vrsqrtps", FCML_AMT_AVX_SIMD, 0x0180, 0x00D88000, { 0x0F, 0x52, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_MODRM_RM_SIMD_L, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_RSQRTSS[] = {
	// F3 0F 52 /r RSQRTSS xmm1,xmm2/m32
	{ NULL, FCML_AMT_SSE_SIMD, 0x4000, 0x00D88000, { 0x0F, 0x52, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_32, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.LIG.F3.0F.WIG 52 /r VRSQRTSS xmm1,xmm2,xmm3/m32
	{ "vrsqrtss", FCML_AMT_AVX_SIMD, 0x40C0, 0x00D88000, { 0x0F, 0x52, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_32, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_SAHF[] = {
    // It is valid in 64-bit mode only if CPUID.80000001H:ECX.LAHF-SAHF[bit 0] = 1.
	// 9E SAHF
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00C40000, { 0x9E, 0x00, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_SAR[] = {
	// D0 /7 SAR r/m8, 1
	// REX + D0 /7 SAR r/m8
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00C5B800, { 0xD0, 0x00, 0x00 }, { FCML_OP_MODRM_RM_8_W, FCML_OP_EXPLICIT_IB(1), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// D2 /7 SAR r/m8, CL MC Valid Valid Signed divide* r/m8 by 2, CL times.
	// REX + D2 /7 SAR r/m8**, CL MC Valid N.E. Signed divide* r/m8 by 2, CL times.
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00C5B800, { 0xD2, 0x00, 0x00 }, { FCML_OP_MODRM_RM_8_W, FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_CL, FCML_EOS_BYTE ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// C0 /7 ib SAR r/m8, imm8 MI Valid Valid Signed divide* r/m8 by 2, imm8 time.
	// REX + C0 /7 ib SAR r/m8**, imm8 MI Valid N.E. Signed divide* r/m8 by 2, imm8 times.
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00C5B800, { 0xC0, 0x00, 0x00 }, { FCML_OP_MODRM_RM_8_W, FCML_OP_IB, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// D1 /7 SAR r/m16,1 M1 Valid Valid Signed divide* r/m16 by 2, once.
	// D1 /7 SAR r/m32, 1 M1 Valid Valid Signed divide* r/m32 by 2, once.
	// REX.W + D1 /7 SAR r/m64, 1 M1 Valid N.E. Signed divide* r/m64 by 2, once.
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00C5B800, { 0xD1, 0x00, 0x00 }, { FCML_OP_MODRM_RM_W, FCML_OP_EXPLICIT_IB(1), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// D3 /7 SAR r/m16, CL MC Valid Valid Signed divide* r/m16 by 2, CL times.
	// D3 /7 SAR r/m32, CL MC Valid Valid Signed divide* r/m32 by 2, CL times.
	// REX.W + D3 /7 SAR r/m64, CL MC Valid N.E. Signed divide* r/m64 by 2, CL times.
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00C5B800, { 0xD3, 0x00, 0x00 }, { FCML_OP_MODRM_RM_W, FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_CL, FCML_EOS_BYTE ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// C1 /7 ib SAR r/m16, imm8 MI Valid Valid Signed divide* r/m16 by 2, imm8 times.
	// C1 /7 ib SAR r/m32, imm8 MI Valid Valid Signed divide* r/m32 by 2, imm8 times.
	// REX.W + C1 /7 ib SAR r/m64, imm8 MI Valid N.E. Signed divide* r/m64 by 2, imm8 times
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00C5B800, { 0xC1, 0x00, 0x00 }, { FCML_OP_MODRM_RM_W, FCML_OP_IB, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_SHL_SAL[] = {
	// D0 /4 SHL/SAL r/m8,1
	// REX + D0 /4 SHL/SAL r/m8,1
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00C5A000, { 0xD0, 0x00, 0x00 }, { FCML_OP_MODRM_RM_8_W, FCML_OP_EXPLICIT_IB(1), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// D2 /4 SHL/SAL r/m8,CL
	// REX + D2 /4 SHL/SAL r/m8,CL
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00C5A000, { 0xD2, 0x00, 0x00 }, { FCML_OP_MODRM_RM_8_W, FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_CL, FCML_EOS_BYTE ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// C0 /4 ib SHL/SAL r/m8,imm8
	// REX + C0 /4 ib SHL/SAL r/m8,imm8
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00C5A000, { 0xC0, 0x00, 0x00 }, { FCML_OP_MODRM_RM_8_W, FCML_OP_IB, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// D1 /4 SHL/SAL r/m16,1
	// D1 /4 SHL/SAL r/m32,1
	// REX.W + D1 /4 SHL/SAL r/m64,1
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00C5A000, { 0xD1, 0x00, 0x00 }, { FCML_OP_MODRM_RM_W, FCML_OP_EXPLICIT_IB(1), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// D3 /4 SHL/SAL r/m16,CL
	// D3 /4 SHL/SAL r/m32,CL
	// REX.W + D3 /4 SHL/SAL r/m64,CL
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00C5A000, { 0xD3, 0x00, 0x00 }, { FCML_OP_MODRM_RM_W, FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_CL, FCML_EOS_BYTE ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// C1 /4 ib SHL/SAL r/m16,imm8
	// C1 /4 ib SHL/SAL r/m32,imm8
	// REX.W + C1 /4 ib SHL/SAL r/m64,imm8
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00C5A000, { 0xC1, 0x00, 0x00 }, { FCML_OP_MODRM_RM_W, FCML_OP_IB, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_SHR[] = {
	// D0 /5 SHR r/m8,1
	// REX + D0 /5 SHR r/m8,1
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00C5A800, { 0xD0, 0x00, 0x00 }, { FCML_OP_MODRM_RM_8_W, FCML_OP_EXPLICIT_IB(1), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// D2 /5 SHR r/m8,CL
	// REX + D2 /5 SHR r/m8,CL
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00C5A800, { 0xD2, 0x00, 0x00 }, { FCML_OP_MODRM_RM_8_W, FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_CL, FCML_EOS_BYTE ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// C0 /5 ib SHR r/m8,imm8
	// REX + C0 /5 ib SHR r/m8,imm8
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00C5A800, { 0xC0, 0x00, 0x00 }, { FCML_OP_MODRM_RM_8_W, FCML_OP_IB, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// D1 /5 SHR r/m16,1
	// D1 /5 SHR r/m32,1
	// REX.W + D1 /5 SHR r/m64,1
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00C5A800, { 0xD1, 0x00, 0x00 }, { FCML_OP_MODRM_RM_W, FCML_OP_EXPLICIT_IB(1), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// D3 /5 SHR r/m16,CL
	// D3 /5 SHR r/m32,CL
	// REX.W + D3 /5 SHR r/m64,CL
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00C5A800, { 0xD3, 0x00, 0x00 }, { FCML_OP_MODRM_RM_W, FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_CL, FCML_EOS_BYTE ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// C1 /5 ib SHR r/m16,imm8
	// C1 /5 ib SHR r/m32,imm8
	// REX.W + C1 /5 ib SHR r/m64,imm8
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00C5A800, { 0xC1, 0x00, 0x00 }, { FCML_OP_MODRM_RM_W, FCML_OP_IB, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_SBB[] = {
	// 1C ib SBB AL,imm8
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00C40000, { 0x1C, 0x00, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_AL, FCML_EOS_BYTE ), FCML_OP_IB, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 1D iw SBB AX,imm16
	// 1D id SBB EAX,imm32
	{ NULL, FCML_AMT_GPI, 0x0010, 0x00C40000, { 0x1D, 0x00, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_AL, FCML_EOS_EOSA ) | FCML_OA_W, FCML_OP_IMM_EOSA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// REX.W + 1D id SBB RAX,imm32
	{ NULL, FCML_AMT_GPI, 0x0008, 0x00840000, { 0x1D, 0x00, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_AL, FCML_EOS_EOSA ) | FCML_OA_W, FCML_OP_ID_EX_EOSA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 80 /3 ib SBB r/m8,imm8
	// REX + 80 /3 ib SBB r/m8,imm8
	{ NULL, FCML_AMT_GPI, 0x0807, 0x00C59800, { 0x80, 0x00, 0x00 }, { FCML_OP_MODRM_RM_8_W, FCML_OP_IB, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 81 /3 iw SBB r/m16,imm16
	// 81 /3 id SBB r/m32,imm32
	{ NULL, FCML_AMT_GPI, 0x0817, 0x00C59800, { 0x81, 0x00, 0x00 }, { FCML_OP_MODRM_RM_W, FCML_OP_IMM_EOSA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// REX.W + 81 /3 id SBB r/m64,imm32
	{ NULL, FCML_AMT_GPI, 0x080F, 0x00859800, { 0x81, 0x00, 0x00 }, { FCML_OP_MODRM_RM_W, FCML_OP_ID_EX_EOSA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 83 /3 ib SBB r/m16,imm8
	// 83 /3 ib SBB r/m32,imm8
	{ NULL, FCML_AMT_GPI, 0x0817, 0x00C59800, { 0x83, 0x00, 0x00 }, { FCML_OP_MODRM_RM_W, FCML_OP_IB_EX_EOSA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// REX.W + 83 /3 ib SBB r/m64,imm8
	{ NULL, FCML_AMT_GPI, 0x080F, 0x00859800, { 0x83, 0x00, 0x00 }, { FCML_OP_MODRM_RM_W, FCML_OP_IB_EX_EOSA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 18 /r SBB r/m8,r8
	// REX + 18 /r SBB r/m8,r8
	{ NULL, FCML_AMT_GPI, 0x0807, 0x00C48000, { 0x18, 0x00, 0x00 }, { FCML_OP_MODRM_RM_8_W, FCML_OP_MODRM_R_8, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 19 /r SBB r/m16,r16
	// 19 /r SBB r/m32,r32
	// REX.W + 19 /r SBB r/m64,r64
	{ NULL, FCML_AMT_GPI, 0x0807, 0x00C48000, { 0x19, 0x00, 0x00 }, { FCML_OP_MODRM_RM_W, FCML_OP_MODRM_R, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 1A /r SBB r8,r/m8
	// REX + 1A /r SBB r8,r/m8
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00C48000, { 0x1A, 0x00, 0x00 }, { FCML_OP_MODRM_R_8_W, FCML_OP_MODRM_RM_8, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 1B /r SBB r16,r/m16
	// 1B /r SBB r32,r/m32
	// REX.W + 1B /r SBB r64,r/m64
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00C48000, { 0x1B, 0x00, 0x00 }, { FCML_OP_MODRM_R_W, FCML_OP_MODRM_RM, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_SCAS[] = {
	// AE SCAS m8 NP Valid Valid Compare AL with byte at ES:(E)DI or RDI, then set status flags.*
	{ "scas;scasb[ts]", FCML_AMT_GPI, 0x0002, 0x00C40000, { 0xAE, 0x00, 0x00 },
				{ FCML_OP_EXPLICIT_GPS_REG_ADDRESSING( FCML_REG_DI, FCML_EOS_BYTE, FCML_SEG_ENCODE_REGISTER( FCML_REG_ES, FCML_SEG_DENY_OVERRIDE ) ),
				FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// AF SCAS m16 NP Valid Valid Compare AX with word at ES:(E)DI or RDI, then set status flags.*
	// AF SCAS m32 NP Valid Valid Compare EAX with doubleword at ES(E)DI or RDI then set status flags.*
	// REX.W + AF SCAS m64 NP Valid N.E. Compare RAX with quadword at RDI or EDI then set status flags.
	{ "scas;scasw[ts,ow,a*];scasd[ts,od,a*];scasq[ts,oq,a*]", FCML_AMT_GPI, 0x0002, 0x00C40000, { 0xAF, 0x00, 0x00 },
				{ FCML_OP_EXPLICIT_GPS_REG_ADDRESSING( FCML_REG_DI, FCML_EOS_EOSA,FCML_SEG_ENCODE_REGISTER( FCML_REG_ES, FCML_SEG_DENY_OVERRIDE ) ),
				FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_SETcc[] = {
	// 0F 97 SETA r/m8 M Valid Valid Set byte if above (CF=0 and ZF=0).
	// REX + 0F 97 SETA r/m8*
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00D88040, { 0x0F, 0x90, 0x00 }, { FCML_OP_MODRM_RM_8, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_SFENCE[] = {
	{ NULL, FCML_AMT_SSE, 0x0000, 0x00EC0000, { 0x0F, 0xAE, 0xF8 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_SGDT[] = {
	// 0F 01 /0 SGDT m
	{ NULL, FCML_AMT_SYSTEM, 0x0000, 0x00D98000, { 0x0F, 0x01, 0x00 }, { FCML_OP_MODRM_M_UNDEF, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_SHLD[] = {
	// 0F A4 SHLD r/m16,r16,imm8 MRI Valid Valid Shift r/m16 to left imm8 places while shifting bits from r16 in from the right.
	// 0F A4 SHLD r/m32,r32,imm8 MRI Valid Valid Shift r/m32 to left imm8 places while shifting bits from r32 in from the right.
	// REX.W + 0F A4 SHLD r/m64,r64, imm8 MRI Valid N.E. Shift r/m64 to left imm8 places while shifting bits from r64 in from the right.
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00D88000, { 0x0F, 0xA4, 0x00 }, { FCML_OP_MODRM_RM_W, FCML_OP_MODRM_R,FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 0F A5 SHLD r/m16,r16,CL MRC Valid Valid Shift r/m16 to left CL places while shifting bits from r16 in from the right.
	// 0F A5 SHLD r/m32,r32,CL MRC Valid Valid Shift r/m32 to left CL places while shifting bits from r32 in from the right.
	// REX.W + 0F A5 SHLD r/m64,r64,CL MRC Valid N.E. Shift r/m64 to left CL places while shifting bits from r64 in from the right.
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00D88000, { 0x0F, 0xA5, 0x00 }, { FCML_OP_MODRM_RM_W, FCML_OP_MODRM_R,FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_CL, FCML_EOS_BYTE ), FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_SHRD[] = {
	// 0F AC SHRD r/m16, r16, imm8 MRI Valid Valid Shift r/m16 to right imm8 places while shifting bits from r16 in from the left.
	// 0F AC SHRD r/m32, r32, imm8 MRI Valid Valid Shift r/m32 to right imm8 places while shifting bits from r32 in from the left.
	// REX.W + 0F AC SHRD r/m64, r64, imm8 MRI Valid N.E. Shift r/m64 to right imm8 places while shifting bits from r64 in from the left.
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00D88000, { 0x0F, 0xAC, 0x00 }, { FCML_OP_MODRM_RM_W, FCML_OP_MODRM_R,FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 0F AD SHRD r/m16, r16, CL MRC Valid Valid Shift r/m16 to right CL places while shifting bits from r16 in from the left.
	// 0F AD SHRD r/m32, r32, CL MRC Valid Valid Shift r/m32 to right CL places while shifting bits from r32 in from the left.
	// REX.W + 0F AD SHRD r/m64, r64, CL MRC Valid N.E. Shift r/m64 to right CL places while shifting bits from r64 in from the left.
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00D88000, { 0x0F, 0xAD, 0x00 }, { FCML_OP_MODRM_RM_W, FCML_OP_MODRM_R,FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_CL, FCML_EOS_BYTE ), FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_SKINIT[] = {
	// SKINIT EAX 0F 01 DE Secure initialization and jump, with attestation.
	{ NULL, FCML_AMT_SVM, 0x0000, 0x00EC0000, { 0x0F, 0x01, 0xDE }, { FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_EAX, FCML_EOS_DWORD ), FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_SLWPCB[] = {
	// SLWPCB reg32 8F RXB.09 0.1111.0.00 12 /1
	{ NULL, FCML_AMT_LWP, 0x0450, 0x00DB8800, { 0x09, 0x12, 0x00 }, { FCML_OP_RM( FCML_REG_GPR, FCML_EOS_DWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// SLWPCB reg64 8F RXB.09 1.1111.0.00 12 /1
	{ NULL, FCML_AMT_LWP, 0x0448, 0x00DB8800, { 0x09, 0x12, 0x00 }, { FCML_OP_RM( FCML_REG_GPR, FCML_EOS_QWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_SHUFPD[] = {
	// 66 0F C6 /r ib SHUFPD xmm1, xmm2/m128, imm8 RMI V/V SSE2 Shuffle packed double-precision floatingpoint values selected by imm8 from xmm1 and xmm2/m128 to xmm1.
	{ NULL, FCML_AMT_SSE2_SIMD, 0x1000, 0x00D88000, { 0x0F, 0xC6, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.66.0F.WIG C6 /r ib VSHUFPD xmm1, xmm2, xmm3/m128, imm8 RVMI V/V AVX Shuffle Packed double-precision floatingpoint values selected by imm8 from xmm2 and xmm3/mem.
	// VEX.NDS.256.66.0F.WIG C6 /r ib VSHUFPD ymm1, ymm2, ymm3/m256, imm8 RVMI V/V AVX Shuffle Packed double-precision floatingpoint values selected by imm8 from ymm2 and ymm3/mem.
	{ "vshufpd", FCML_AMT_AVX_SIMD, 0x1080, 0x00D88000, { 0x0F, 0xC6, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L, FCML_OP_IB, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_SHUFPS[] = {
	// 0F C6 /r ib SHUFPS xmm1, xmm2/m128, imm8 RMI V/V SSE Shuffle packed single-precision floating-point values selected by imm8 from xmm1 and xmm1/m128 to xmm1.
	{ NULL, FCML_AMT_SSE_SIMD, 0x0000, 0x00D88000, { 0x0F, 0xC6, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.0F.WIG C6 /r ib VSHUFPS xmm1, xmm2, xmm3/m128, imm8 RVMI V/V AVX Shuffle Packed single-precision floating-point values selected by imm8 from xmm2 and xmm3/mem.
	// VEX.NDS.256.0F.WIG C6 /r ib VSHUFPS ymm1, ymm2, ymm3/m256, imm8 RVMI V/V AVX Shuffle Packed single-precision floating-point values selected by imm8 from ymm2 and ymm3/mem.
	{ "vshufps", FCML_AMT_AVX_SIMD, 0x0080, 0x00D88000, { 0x0F, 0xC6, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L, FCML_OP_IB, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_SIDT[] = {
	// 0F 01 /1 SIDT m M Valid Valid Store IDTR to m.
	{ NULL, FCML_AMT_SYSTEM, 0x0000, 0x80D98800, { 0x0F, 0x01, 0x00 }, { FCML_OP_MODRM_M_UNDEF, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_SLDT[] = {
	// 0F 00 /0 SLDT r/m16 M Valid Valid Stores segment selector from LDTR in r/m16.
	{ NULL, FCML_AMT_SYSTEM, 0x0010, 0x03D98000, { 0x0F, 0x00, 0x00 }, { FCML_OP_MODRM_RM_16_W, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// REX.W + 0F 00 /0 SLDT r64/m16 M Valid Valid Stores segment selector from LDTR in r64/m16.
	{ NULL, FCML_AMT_SYSTEM, 0x0008, 0x04998000, { 0x0F, 0x00, 0x00 }, { FCML_OP_RM( FCML_REG_GPR, FCML_EOS_QWORD, FCML_EOS_WORD, FCML_RMF_RM ) | FCML_OA_W, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_SMSW[] = {
	// 0F 01 /4 SMSW r/m16 M Valid Valid Store machine status word to r/m16.
	// 0F 01 /4 SMSW r32/m16 M Valid Valid Store machine status word in low-order 16 bits of r32/m16; high-order 16 bits of r32 are undefined.
	// REX.W + 0F 01 /4 SMSW r64/m16 M Valid Valid Store machine status word in low-order 16 bits of r64/m16; high-order 16 bits of r32 are undefined.
	{ NULL, FCML_AMT_SYSTEM, 0x0000, 0x00D9A000, { 0x0F, 0x01, 0x00 }, { FCML_OP_RM( FCML_REG_GPR, FCML_EOS_EOSA, FCML_EOS_WORD, FCML_RMF_RM ) | FCML_OA_W, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_SQRTPD[] = {
	// 66 0F 51 /r SQRTPD xmm1,xmm2/m128
	{ NULL, FCML_AMT_SSE2_SIMD, 0x1000, 0x00D88000, { 0x0F, 0x51, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.128.66.0F.WIG 51 /r VSQRTPD xmm1,xmm2/m128
	// VEX.256.66.0F.WIG 51 /r VSQRTPD ymm1,ymm2/m256
	{ "vsqrtpd", FCML_AMT_AVX_SIMD, 0x1180, 0x00D88000, { 0x0F, 0x51, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_MODRM_RM_SIMD_L, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_SQRTPS[] = {
	// 0F 51 /r SQRTPS xmm1,xmm2/m128 RM V/V SSE Computes square roots of the packed singleprecision floating-point values in xmm2/m128 and stores the results in xmm1.
	{ NULL, FCML_AMT_SSE_SIMD, 0x0000, 0x00D88000, { 0x0F, 0x51, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.128.0F.WIG 51 /r VSQRTPS xmm1,xmm2/m128 RM V/V AVX Computes Square Roots of the packed singleprecision floating-point values in xmm2/m128 and stores the result in xmm1.
	// VEX.256.0F.WIG 51 /r VSQRTPS ymm1,ymm2/m256 RM V/V AVX Computes Square Roots of the packed singleprecision floating-point values in ymm2/m256 and stores the result in ymm1.
	{ "vsqrtps", FCML_AMT_AVX_SIMD, 0x0180, 0x00D88000, { 0x0F, 0x51, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_MODRM_RM_SIMD_L, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_SQRTSD[] = {
	// F2 0F 51 /r SQRTSD xmm1,xmm2/m64 RM V/V SSE2 Computes square root of the low doubleprecision floating-point value in xmm2/m64 and stores the results in xmm1.
	{ NULL, FCML_AMT_SSE2_SIMD, 0x2001, 0x00D88000, { 0x0F, 0x51, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.LIG.F2.0F.WIG 51 /r VSQRTSD xmm1,xmm2,xmm3/m64 RVM V/V AVX Computes square root of the low doubleprecision floating point value in xmm3/m64 and stores the results in xmm2. Also, upper double precision floating-point value (bits[127:64]) from xmm2 is copied to xmm1[127:64].
	{ "vsqrtsd", FCML_AMT_AVX_SIMD, 0x20C0, 0x00D88000, { 0x0F, 0x51, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L_64, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_SQRTSS[] = {
	// F3 0F 51 /r SQRTSS xmm1, xmm2/m32 RM V/V SSE Computes square root of the low singleprecision floating-point value in xmm2/m32 and stores the results in xmm1.
	{ NULL, FCML_AMT_SSE_SIMD, 0x4000, 0x00D88000, { 0x0F, 0x51, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_32, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.LIG.F3.0F.WIG 51 VSQRTSS xmm1, xmm2, xmm3/m32 RVM V/V AVX Computes square root of the low singleprecision floating-point value in xmm3/m32 and stores the results in xmm1. Also, upper single precision floating-point values (bits[127:32]) from xmm2 are copied to xmm1[127:32].
	{ "vsqrtss", FCML_AMT_AVX_SIMD, 0x40C0, 0x00D88000, { 0x0F, 0x51, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L_32, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_STC[] = {
	// F9 STC NP Valid Valid Set CF flag.
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00C40000, { 0xF9, 0x00, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_STD[] = {
	// FD STD NP Valid Valid Set DF flag.
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00C40000, { 0xFD, 0x00, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_STGI[] = {
	// STGI 0F 01 DC Sets the global interrupt flag (GIF).
	{ NULL, FCML_AMT_SVM, 0x0000, 0x00EC0000, { 0x0F, 0x01, 0xDC }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_STI[] = {
	// FB STI NP Valid Valid Set interrupt flag; external, maskable interrupts enabled at the end of the next instruction.
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00C40000, { 0xFB, 0x00, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_STMXCSR[] = {
	// 0F AE /3 STMXCSR m32 M V/V SSE Store contents of MXCSR register to m32.
	{ NULL, FCML_AMT_SSE, 0x0000, 0x80D99800, { 0x0F, 0xAE, 0x00 }, { FCML_OP_MODRM_M_32, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.LZ.0F.WIG AE /3 VSTMXCSR m32 M V/V AVX Store contents of MXCSR register to m32.
	{ "vstmxcsr", FCML_AMT_AVX, 0x01C0, 0x80D99800, { 0x0F, 0xAE, 0x00 }, { FCML_OP_MODRM_M_32, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_STOS[] = {
	// AA STOS m8 NA Valid Valid For legacy mode, store AL at address ES:(E)DI; For 64-bit mode store AL at address RDI or EDI.
	{ "stos;stosb[ts]", FCML_AMT_GPI, 0x0004, 0x00C40000, { 0xAA, 0x00, 0x00 },
			{ FCML_OP_EXPLICIT_GPS_REG_ADDRESSING( FCML_REG_SI, FCML_EOS_BYTE, FCML_SEG_ENCODE_REGISTER( FCML_REG_DS, FCML_SEG_ALLOW_OVERRIDE ) ),
			FCML_OP_EXPLICIT_GPS_REG_ADDRESSING( FCML_REG_DI, FCML_EOS_BYTE, FCML_SEG_ENCODE_REGISTER( FCML_REG_ES, FCML_SEG_DENY_OVERRIDE ) ),
			FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// AB STOS m16 NA Valid Valid For legacy mode, store AX at address ES:(E)DI; For 64-bit mode store AX at address RDI or EDI.
	// AB STOS m32 NA Valid Valid For legacy mode, store EAX at address ES:(E)DI; For 64-bit mode store EAX at address RDI or EDI.
	// REX.W + AB STOS m64 NA Valid N.E. Store RAX at address RDI or EDI.
	{ "stos;stosw[ts,ow,a*];stosd[ts,od,a*];stosq[ts,oq,a*]", FCML_AMT_GPI, 0x0004, 0x00C40000, { 0xAB, 0x00, 0x00 },
			{ FCML_OP_EXPLICIT_GPS_REG_ADDRESSING( FCML_REG_SI, FCML_EOS_EOSA,FCML_SEG_ENCODE_REGISTER( FCML_REG_DS, FCML_SEG_ALLOW_OVERRIDE ) ),
			FCML_OP_EXPLICIT_GPS_REG_ADDRESSING( FCML_REG_DI, FCML_EOS_EOSA,FCML_SEG_ENCODE_REGISTER( FCML_REG_ES, FCML_SEG_DENY_OVERRIDE ) ),
			FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_STR[] = {
	// 0F 00 /1 STR r/m16 M Valid Valid Stores segment selector from TR in r/m16.
	{ NULL, FCML_AMT_SYSTEM, 0x0000, 0x00D98800, { 0x0F, 0x00, 0x00 }, { FCML_OP_MODRM_RM_16_W, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_SUB[] = {
	// 2C ib SUB AL, imm8 I Valid Valid Subtract imm8 from AL.
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00C40000, { 0x2C, 0x00, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_AL, FCML_EOS_BYTE ), FCML_OP_IB, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 2D iw SUB AX, imm16 I Valid Valid Subtract imm16 from AX.
	// 2D id SUB EAX, imm32 I Valid Valid Subtract imm32 from EAX.
	{ NULL, FCML_AMT_GPI, 0x0010, 0x00C40000, { 0x2D, 0x00, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_AL, FCML_EOS_EOSA ) | FCML_OA_W, FCML_OP_IMM_EOSA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// REX.W + 2D id SUB RAX, imm32 I Valid N.E. Subtract imm32 sign-extended to 64-bits from RAX.
	{ NULL, FCML_AMT_GPI, 0x0008, 0x00840000, { 0x2D, 0x00, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_AL, FCML_EOS_EOSA ) | FCML_OA_W, FCML_OP_ID_EX_EOSA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 80 /5 ib SUB r/m8, imm8 MI Valid Valid Subtract imm8 from r/m8.
	// REX + 80 /5 ib SUB r/m8*, imm8 MI Valid N.E. Subtract imm8 from r/m8.
	{ NULL, FCML_AMT_GPI, 0x0807, 0x00C5A800, { 0x80, 0x00, 0x00 }, { FCML_OP_MODRM_RM_8_W, FCML_OP_IB, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 81 /5 iw SUB r/m16, imm16 MI Valid Valid Subtract imm16 from r/m16.
	// 81 /5 id SUB r/m32, imm32 MI Valid Valid Subtract imm32 from r/m32.
	{ NULL, FCML_AMT_GPI, 0x0817, 0x00C5A800, { 0x81, 0x00, 0x00 }, { FCML_OP_MODRM_RM_W, FCML_OP_IMM_EOSA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// REX.W + 81 /5 id SUB r/m64, imm32 MI Valid N.E. Subtract imm32 sign-extended to 64-bits from r/m64.
	{ NULL, FCML_AMT_GPI, 0x080F, 0x0085A800, { 0x81, 0x00, 0x00 }, { FCML_OP_MODRM_RM_W, FCML_OP_ID_EX_EOSA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 83 /5 ib SUB r/m16, imm8 MI Valid Valid Subtract sign-extended imm8 from r/m16.
	// 83 /5 ib SUB r/m32, imm8 MI Valid Valid Subtract sign-extended imm8 from r/m32.
	{ NULL, FCML_AMT_GPI, 0x0817, 0x00C5A800, { 0x83, 0x00, 0x00 }, { FCML_OP_MODRM_RM_W, FCML_OP_IB_EX_EOSA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// REX.W + 83 /5 ib SUB r/m64, imm8 MI Valid N.E. Subtract sign-extended imm8 from r/m64.
	{ NULL, FCML_AMT_GPI, 0x080F, 0x0085A800, { 0x83, 0x00, 0x00 }, { FCML_OP_MODRM_RM_W, FCML_OP_IB_EX_EOSA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 28 /r SUB r/m8, r8 MR Valid Valid Subtract r8 from r/m8.
	// REX + 28 /r SUB r/m8*, r8* MR Valid N.E. Subtract r8 from r/m8.
	{ NULL, FCML_AMT_GPI, 0x0807, 0x00C48000, { 0x28, 0x00, 0x00 }, { FCML_OP_MODRM_RM_8_W, FCML_OP_MODRM_R_8, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 29 /r SUB r/m16, r16 MR Valid Valid Subtract r16 from r/m16.
	// 29 /r SUB r/m32, r32 MR Valid Valid Subtract r32 from r/m32.
	// REX.W + 29 /r SUB r/m64, r32 MR Valid N.E. Subtract r64 from r/m64.
	{ NULL, FCML_AMT_GPI, 0x0807, 0x00C48000, { 0x29, 0x00, 0x00 }, { FCML_OP_MODRM_RM_W, FCML_OP_MODRM_R, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 2A /r SUB r8, r/m8 RM Valid Valid Subtract r/m8 from r8.
	// REX + 2A /r SUB r8*, r/m8* RM Valid N.E. Subtract r/m8 from r8.
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00C48000, { 0x2A, 0x00, 0x00 }, { FCML_OP_MODRM_R_8_W, FCML_OP_MODRM_RM_8, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 2B /r SUB r16, r/m16 RM Valid Valid Subtract r/m16 from r16.
	// 2B /r SUB r32, r/m32 RM Valid Valid Subtract r/m32 from r32.
	// REX.W + 2B /r SUB r64, r/m64 RM Valid N.E. Subtract r/m64 from r64.
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00C48000, { 0x2B, 0x00, 0x00 }, { FCML_OP_MODRM_R_W, FCML_OP_MODRM_RM, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_T1MSKC[] = {
	// T1MSKC reg32, reg/mem32 8F RXB.09 0.dest.0.00 01 /7
	{ NULL, FCML_AMT_TBM, 0x0450, 0x00D9B800, { 0x09, 0x01, 0x00 }, { FCML_OP_VEX_VVVV_REG( FCML_REG_GPR, FCML_EOS_DWORD ) | FCML_OA_W, FCML_OP_MODRM_RM_32, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// T1MSKC reg64, reg/mem64 8F RXB.09 1.dest.0.00 01 /7
	{ NULL, FCML_AMT_TBM, 0x0448, 0x00D9B800, { 0x09, 0x01, 0x00 }, { FCML_OP_VEX_VVVV_REG( FCML_REG_GPR, FCML_EOS_QWORD ) | FCML_OA_W, FCML_OP_MODRM_RM_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_SUBPD[] = {
	// 66 0F 5C /r SUBPD xmm1,xmm2/m128 RM V/V SSE2 Subtract packed double-precision floatingpoint values in xmm2/m128 from xmm1.
	{ NULL, FCML_AMT_SSE2_SIMD, 0x1000, 0x00D88000, { 0x0F, 0x5C, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.66.0F.WIG 5C /r VSUBPD xmm1,xmm2,xmm3/m128 RVM V/V AVX Subtract packed double-precision floatingpoint values in xmm3/mem from xmm2 and stores result in xmm1.
	// VEX.NDS.256.66.0F.WIG 5C /r VSUBPD ymm1,ymm2,ymm3/m256 RVM V/V AVX Subtract packed double-precision floatingpoint values in ymm3/mem from ymm2 and stores result in ymm1.	_TEST32_VEX( "c4e149c6140120 vshufpd xmm2,xmm6,oword ptr [ecx+eax],20h", 0xC4, 0xE1, 0x49, 0xC6, 0x14, 0x01, 0x20 );
	{ "vsubpd", FCML_AMT_AVX_SIMD, 0x1080, 0x00D88000, { 0x0F, 0x5C, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_SUBPS[] = {
	// 0F 5C /r SUBPS xmm1,xmm2/m128 RM V/V SSE Subtract packed single-precision floating-point values in xmm2/mem from xmm1.
	{ NULL, FCML_AMT_SSE_SIMD, 0x0000, 0x00D88000, { 0x0F, 0x5C, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.0F.WIG 5C /r VSUBPS xmm1,xmm2,xmm3/m128 RVM V/V AVX Subtract packed single-precision floating-point values in xmm3/mem from xmm2 and stores result in xmm1.
	// VEX.NDS.256.0F.WIG 5C /r VSUBPS ymm1,ymm2,ymm3/m256 RVM V/V AVX Subtract packed single-precision floating-point values in ymm3/mem from ymm2 and stores result in ymm1.
	{ "vsubps", FCML_AMT_AVX_SIMD, 0x0080, 0x00D88000, { 0x0F, 0x5C, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_SUBSD[] = {
	// F2 0F 5C /r SUBSD xmm1,xmm2/m64 RM V/V SSE2 Subtracts the low double-precision floatingpoint values in xmm2/mem64 from xmm1.
	{ NULL, FCML_AMT_SSE2_SIMD, 0x2001, 0x00D88000, { 0x0F, 0x5C, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.LIG.F2.0F.WIG 5C /r VSUBSD xmm1,xmm2,xmm3/m64 RVM V/V AVX Subtract the low double-precision floatingpoint value in xmm3/mem from xmm2 and store the result in xmm1.
	{ "vsubsd", FCML_AMT_AVX_SIMD, 0x20C0, 0x00D88000, { 0x0F, 0x5C, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L_64, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_SUBSS[] = {
	// F3 0F 5C /r SUBSS xmm1,xmm2/m32
	{ NULL, FCML_AMT_SSE_SIMD, 0x4001, 0x00D88000, { 0x0F, 0x5C, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_32, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.LIG.F3.0F.WIG 5C /r VSUBSS xmm1,xmm2,xmm3/m32
	{ "vsubss", FCML_AMT_AVX_SIMD, 0x40C0, 0x00D88000, { 0x0F, 0x5C, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L_32, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_SWAPGS[] = {
	// 0F 01 F8 SWAPGS NP Valid Invalid Exchanges the current GS base register value with the value contained in MSR address C0000102H.
	{ NULL, FCML_AMT_SYSTEM, 0x0000, 0x00AC0000, { 0x0F, 0x01, 0xF8 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_SYSCALL[] = {
	// 0F 05 SYSCALL NP Valid Invalid Fast call to privilege level 0 system procedures.
	{ NULL, FCML_AMT_SYSTEM, 0x0000, 0x00980000, { 0x0F, 0x05, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_SYSENTER[] = {
	// 0F 34 SYSENTER NP Valid Valid Fast call to privilege level 0 system procedures.
	{ NULL, FCML_AMT_SYSTEM, 0x0000, 0x00D80000, { 0x0F, 0x34, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_SYSEXIT[] = {
	// 0F 35 SYSEXIT NP Valid Valid Fast return to privilege level 3 user code.
	// REX.W + 0F 35 SYSEXIT NP Valid Valid Fast return to 64-bit mode privilege level 3 user code.
	{ NULL, FCML_AMT_SYSTEM, 0x0000, 0x00D80000, { 0x0F, 0x35, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_SYSRET[] = {
	// 0F 07 SYSRET NP Valid Invalid Return to compatibility mode from fast system call
	// REX.W + 0F 07 SYSRET NP Valid Invalid Return to 64-bit mode from fast system call
	{ NULL, FCML_AMT_SYSTEM, 0x0000, 0x00980000, { 0x0F, 0x07, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_TEST[] = {
	// A8 ib TEST AL, imm8 I Valid Valid AND imm8 with AL; set SF, ZF, PF according to result.
	{ NULL, FCML_AMT_GPI, 0x0010, 0x00C40000, { 0xA8, 0x00, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_AL, FCML_EOS_BYTE ), FCML_OP_IB, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// A9 iw TEST AX, imm16 I Valid Valid AND imm16 with AX; set SF, ZF, PF according to result.
	// A9 id TEST EAX, imm32 I Valid Valid AND imm32 with EAX; set SF, ZF, PF according to result.
	{ NULL, FCML_AMT_GPI, 0x0010, 0x00C40000, { 0xA9, 0x00, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_AL, FCML_EOS_EOSA ) | FCML_OA_W, FCML_OP_IMM_EOSA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// REX.W + A9 id TEST RAX, imm32 I Valid N.E. AND imm32 sign-extended to 64-bits with RAX; set SF, ZF, PF according to result.
	{ NULL, FCML_AMT_GPI, 0x0008, 0x00840000, { 0xA9, 0x00, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_AL, FCML_EOS_EOSA ) | FCML_OA_W, FCML_OP_ID_EX_EOSA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// F6 /0 ib TEST r/m8, imm8 MI Valid Valid AND imm8 with r/m8; set SF, ZF, PF according to result.
	// REX + F6 /0 ib TEST r/m8*, imm8 MI Valid N.E. AND imm8 with r/m8; set SF, ZF, PF according to result.
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00C58000, { 0xF6, 0x00, 0x00 }, { FCML_OP_MODRM_RM_8_W, FCML_OP_IB, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// F7 /0 iw TEST r/m16, imm16 MI Valid Valid AND imm16 with r/m16; set SF, ZF, PF according to result.
	// F7 /0 id TEST r/m32, imm32 MI Valid Valid AND imm32 with r/m32; set SF, ZF, PF according to result.
	{ NULL, FCML_AMT_GPI, 0x0010, 0x00C58000, { 0xF7, 0x00, 0x00 }, { FCML_OP_MODRM_RM_W, FCML_OP_IMM_EOSA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// REX.W + F7 /0 id TEST r/m64, imm32 MI Valid N.E. AND imm32 sign-extended to 64-bits with r/m64; set SF, ZF, PF according to result.
	{ NULL, FCML_AMT_GPI, 0x0008, 0x00858000, { 0xF7, 0x00, 0x00 }, { FCML_OP_MODRM_RM_W, FCML_OP_ID_EX_EOSA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 84 /r TEST r/m8, r8 MR Valid Valid AND r8 with r/m8; set SF, ZF, PF according to result.
	// REX + 84 /r TEST r/m8*, r8* MR Valid N.E. AND r8 with r/m8; set SF, ZF, PF according to result.
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00C48000, { 0x84, 0x00, 0x00 }, { FCML_OP_MODRM_RM_8_W, FCML_OP_MODRM_R_8, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 85 /r TEST r/m16, r16 MR Valid Valid AND r16 with r/m16; set SF, ZF, PF according to result.
	// 85 /r TEST r/m32, r32 MR Valid Valid AND r32 with r/m32; set SF, ZF, PF according to result.
	// REX.W + 85 /r TEST r/m64, r64 MR Valid N.E. AND r64 with r/m64; set SF, ZF, PF according to result.
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00C48000, { 0x85, 0x00, 0x00 }, { FCML_OP_MODRM_RM_W, FCML_OP_MODRM_R, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_UCOMISD[] = {
	// 66 0F 2E /r UCOMISD xmm1,xmm2/m64 RM V/V SSE2 Compares (unordered) the low doubleprecision floating-point values in xmm1 and xmm2/m64 and set the EFLAGS accordingly.
	{ NULL, FCML_AMT_SSE2_SIMD, 0x1000, 0x00D88000, { 0x0F, 0x2E, 0x00 }, { FCML_OP_MODRM_R_XMM, FCML_OP_MODRM_RM_XMM_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.LIG.66.0F.WIG 2E /r VUCOMISD xmm1,xmm2/m64 RM V/V AVX Compare low double precision floating-point values in xmm1 and xmm2/mem64 and set the EFLAGS flags accordingly.
	{ "vucomisd", FCML_AMT_AVX_SIMD, 0x11C0, 0x00D88000, { 0x0F, 0x2E, 0x00 }, { FCML_OP_MODRM_R_XMM, FCML_OP_MODRM_RM_XMM_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_UCOMISS[] = {
	// 0F 2E /r UCOMISS xmm1,xmm2/m32 RM V/V SSE Compare lower single-precision floating-point value in xmm1 register with lower singleprecision floating-point value in xmm2/mem and set the status flags accordingly.
	{ NULL, FCML_AMT_SSE_SIMD, 0x0000, 0x00D88000, { 0x0F, 0x2E, 0x00 }, { FCML_OP_MODRM_R_XMM, FCML_OP_MODRM_RM_XMM_32, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.LIG.0F.WIG 2E /r VUCOMISS xmm1,xmm2/m32 RM V/V AVX Compare low single precision floating-point values in xmm1 and xmm2/mem32 and set the EFLAGS flags accordingly.
	{ "vucomiss", FCML_AMT_AVX_SIMD, 0x01C0, 0x00D88000, { 0x0F, 0x2E, 0x00 }, { FCML_OP_MODRM_R_XMM, FCML_OP_MODRM_RM_XMM_32, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_UD2[] = {
	// 0F 0B UD2 NP Valid Valid Raise invalid opcode exception.
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00D80000, { 0x0F, 0x0B, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_UNPCKHPD[] = {
	// 66 0F 15 /r UNPCKHPD xmm1,xmm2/m128 RM V/V SSE2 Unpacks and Interleaves double-precision floating-point values from high quadwords of xmm1 and xmm2/m128.
	{ NULL, FCML_AMT_SSE2_SIMD, 0x1000, 0x00D88000, { 0x0F, 0x15, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.66.0F.WIG 15 /r VUNPCKHPD xmm1,xmm2,xmm3/m128 RVM V/V AVX Unpacks and Interleaves double precision floating-point values from high quadwords of xmm2 and xmm3/m128.
	// VEX.NDS.256.66.0F.WIG 15 /r VUNPCKHPD ymm1,ymm2,ymm3/m256 RVM V/V AVX Unpacks and Interleaves double precision floating-point values from high quadwords of ymm2 and ymm3/m256.
	{ "vunpckhpd", FCML_AMT_AVX_SIMD, 0x1080, 0x00D88000, { 0x0F, 0x15, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_UNPCKHPS[] = {
	// 0F 15 /r UNPCKHPS xmm1, xmm2/m128 RM V/V SSE Unpacks and Interleaves single-precision floating-point values from high quadwords of xmm1 and xmm2/mem into xmm1.
	{ NULL, FCML_AMT_SSE_SIMD, 0x0000, 0x00D88000, { 0x0F, 0x15, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.0F.WIG 15 /r VUNPCKHPS xmm1,xmm2, xmm3/m128 RVM V/V AVX Unpacks and Interleaves single-precision floating-point values from high quadwords of xmm2 and xmm3/m128.
	// VEX.NDS.256.0F.WIG 15 /r VUNPCKHPS ymm1,ymm2,ymm3/m256 RVM V/V AVX Unpacks and Interleaves single-precision floating-point values from high quadwords of ymm2 and ymm3/m256.
	{ "vunpckhps", FCML_AMT_AVX_SIMD, 0x0080, 0x00D88000, { 0x0F, 0x15, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_UNPCKLPD[] = {
	// 66 0F 14 /r UNPCKLPD xmm1, xmm2/m128 RM V/V SSE2 Unpacks and Interleaves double-precision floating-point values from low quadwords of xmm1 and xmm2/m128.
	{ NULL, FCML_AMT_SSE2_SIMD, 0x1000, 0x00D88000, { 0x0F, 0x14, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.66.0F.WIG 14 /r VUNPCKLPD xmm1,xmm2, xmm3/m128 RVM V/V AVX Unpacks and Interleaves double precision floating-point values low high quadwords of xmm2 and xmm3/m128.
	// VEX.NDS.256.66.0F.WIG 14 /r VUNPCKLPD ymm1,ymm2, ymm3/m256 RVM V/V AVX Unpacks and Interleaves double precision floating-point values low high quadwords of ymm2 and ymm3/m256.
	{ "vunpcklpd", FCML_AMT_AVX_SIMD, 0x1080, 0x00D88000, { 0x0F, 0x14, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_UNPCKLPS[] = {
	// 0F 14 /r UNPCKLPS xmm1, xmm2/m128 RM V/V SSE Unpacks and Interleaves single-precision floating-point values from low quadwords of xmm1 and xmm2/mem into xmm1.
	{ NULL, FCML_AMT_SSE_SIMD, 0x0000, 0x00D88000, { 0x0F, 0x14, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.0F.WIG 14 /r VUNPCKLPS xmm1,xmm2, xmm3/m128 RVM V/V AVX Unpacks and Interleaves single-precision floating-point values from low quadwords of xmm2 and xmm3/m128.
	// VEX.NDS.256.0F.WIG 14 /r VUNPCKLPS ymm1,ymm2,ymm3/m256 RVM V/V AVX Unpacks and Interleaves single-precision floating-point values from low quadwords of ymm2 and ymm3/m256.
	{ "vunpcklps", FCML_AMT_AVX_SIMD, 0x0080, 0x00D88000, { 0x0F, 0x14, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VCVTPH2PS[] = {
	// VEX.128.66.0F38.W0 13 /r VCVTPH2PS xmm1,xmm2/m64 RM V/V F16C Convert four packed half precision (16-bit) floating-point values in xmm2/m64 to packed single-precision floating-point value in xmm1.
	{ NULL, FCML_AMT_F16C, 0x11D0, 0x00EC8000, { 0x0F, 0x38, 0x13 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.256.66.0F38.W0 13 /r VCVTPH2PS ymm1,xmm2/m128 RM V/V F16C Convert eight packed half precision (16-bit) floating-point values in xmm2/m128 to packed single-precision floating-point value in ymm1.
	{ NULL, FCML_AMT_F16C, 0x11B0, 0x00EC8000, { 0x0F, 0x38, 0x13 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VCVTPS2PH[] = {
	// VEX.128.66.0F3A.W0.1D /r VCVTPS2PH xmm1/m64,xmm2,imm8 ib MR V/V F16C Convert four packed single-precision floating-point value in xmm2 to packed halfprecision (16-bit) floating-point value in xmm1/mem. Imm8 provides rounding controls.
	{ NULL, FCML_AMT_F16C, 0x11D0, 0x00EC8000, { 0x0F, 0x3A, 0x1D }, { FCML_OP_MODRM_RM_XMM_64_W, FCML_OP_MODRM_R_XMM, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.256.66.0F3A.W0 1D /r VCVTPS2PH xmm1/m128,ymm2,imm8 ib MR V/V F16C Convert eight packed single-precision floating-point value in ymm2 to packed half-precision (16-bit) floating-point value in xmm1/mem. Imm8 provides rounding controls.
	{ NULL, FCML_AMT_F16C, 0x11B0, 0x00EC8000, { 0x0F, 0x3A, 0x1D }, { FCML_OP_MODRM_RM_XMM_128_W, FCML_OP_MODRM_R_YMM, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VERR[] = {
	// 0F 00 /4 VERR r/m16 M Valid Valid Set ZF=1 if segment specified with r/m16 can be read.
	{ NULL, FCML_AMT_SYSTEM, 0x0000, 0x00D9A000, { 0x0F, 0x00, 0x00 }, { FCML_OP_MODRM_RM_16, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VERW[] = {
	// 0F 00 /5 VERW r/m16 M Valid Valid Set ZF=1 if segment specified with r/m16 can be written.
	{ NULL, FCML_AMT_SYSTEM, 0x0000, 0x00D9A800, { 0x0F, 0x00, 0x00 }, { FCML_OP_MODRM_RM_16, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VMLOAD[] = {
	// VMLOAD rAX 0F 01 DA Load additional state from VMCB.
	{ NULL, FCML_AMT_SVM, 0x0000, 0x00EC0000, { 0x0F, 0x01, 0xDA }, { FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_EAX, FCML_EOS_EASA ), FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VMMCALL[] = {
	// VMMCALL 0F 01 D9 Explicit communication with the VMM.
	{ NULL, FCML_AMT_SVM, 0x0000, 0x00EC0000, { 0x0F, 0x01, 0xD9 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VMRUN[] = {
	// VMRUN rAX 0F 01 D8 Performs a world-switch to guest.
	{ NULL, FCML_AMT_SVM, 0x0000, 0x00EC0000, { 0x0F, 0x01, 0xD8 }, { FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_EAX, FCML_EOS_EASA ), FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VMSAVE[] = {
	// VMSAVE rAX 0F 01 DB Save additional guest state to VMCB.
	{ NULL, FCML_AMT_SVM, 0x0000, 0x00EC0000, { 0x0F, 0x01, 0xDB }, { FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_EAX, FCML_EOS_EASA ), FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPERMILPD[] = {
	// VEX.NDS.128.66.0F38.W0 0D /r VPERMILPD xmm1,xmm2,xmm3/m128 RVM V/V AVX Permute double-precision floating-point values in xmm2 using controls from xmm3/mem and store result in xmm1.
	// VEX.NDS.256.66.0F38.W0 0D /r VPERMILPD ymm1,ymm2,ymm3/m256 RVM V/V AVX Permute double-precision floating-point values in ymm2 using controls from ymm3/mem and store result in ymm1.
	{ NULL, FCML_AMT_AVX_SIMD, 0x1090, 0x00EC8000, { 0x0F, 0x38, 0x0D }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.128.66.0F3A.W0 05 /r ib VPERMILPD xmm1,xmm2/m128,imm8 RMI V/V AVX Permute double-precision floating-point values in xmm2/mem using controls from imm8.
	// VEX.256.66.0F3A.W0 05 /r ib VPERMILPD ymm1,ymm2/m256,imm8 RMI V/V AVX Permute double-precision floating-point values in ymm2/mem using controls from imm8.
	{ NULL, FCML_AMT_AVX_SIMD, 0x1090, 0x00EC8000, { 0x0F, 0x3A, 0x05 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_MODRM_RM_SIMD_L, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPERMILPS[] = {
	// VEX.NDS.128.66.0F38.W0 0C /r VPERMILPS xmm1,xmm2,xmm3/m128 RVM V/V AVX Permute single-precision floating-point values in xmm2 using controls from xmm3/mem and store result in xmm1.
	// VEX.NDS.256.66.0F38.W0 0C /r VPERMILPS ymm1,ymm2,ymm3/m256 RVM V/V AVX Permute single-precision floating-point values in ymm2 using controls from ymm3/mem and store result in ymm1.
	{ NULL, FCML_AMT_AVX_SIMD, 0x1090, 0x00EC8000, { 0x0F, 0x38, 0x0C }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.128.66.0F3A.W0 04 /r ib VPERMILPS xmm1,xmm2/m128,imm8 RMI V/V AVX Permute single-precision floating-point values in xmm2/mem using controls from imm8 and store result in xmm1.
	// VEX.256.66.0F3A.W0 04 /r ib VPERMILPS ymm1,ymm2/m256,imm8 RMI V/V AVX Permute single-precision floating-point values in ymm2/mem using controls from imm8 and store result in ymm1.
	{ NULL, FCML_AMT_AVX_SIMD, 0x1090, 0x00EC8000, { 0x0F, 0x3A, 0x04 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_MODRM_RM_SIMD_L, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPSLLVD[] = {
	// VEX.NDS.128.66.0F38.W0 47 /r VPSLLVD xmm1,xmm2,xmm3/m128
	// VEX.NDS.256.66.0F38.W0 47 /r VPSLLVD ymm1,ymm2,ymm3/m256
	{ NULL, FCML_AMT_AVX2_SIMD, 0x1090, 0x00EC8000, { 0x0F, 0x38, 0x47 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.66.0F38.W1 47 /r VPSLLVQ xmm1,xmm2,xmm3/m128
	// VEX.NDS.256.66.0F38.W1 47 /r VPSLLVQ ymm1,ymm2,ymm3/m256
	{ "vpsllvq", FCML_AMT_AVX2_SIMD, 0x1088, 0x00EC8000, { 0x0F, 0x38, 0x47 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPSRLVD[] = {
	// VEX.NDS.128.66.0F38.W0 45 /r VPSRLVD xmm1,xmm2,xmm3/m128
	// VEX.NDS.256.66.0F38.W0 45 /r VPSRLVD ymm1,ymm2,ymm3/m256
	{ NULL, FCML_AMT_AVX2_SIMD, 0x1090, 0x00EC8000, { 0x0F, 0x38, 0x45 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.66.0F38.W1 45 /r VPSRLVQ xmm1,xmm2,xmm3/m128
	// VEX.NDS.256.66.0F38.W1 45 /r VPSRLVQ ymm1,ymm2,ymm3/m256
	{ "vpsrlvq", FCML_AMT_AVX2_SIMD, 0x1088, 0x00EC8000, { 0x0F, 0x38, 0x45 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPSRAVD[] = {
	// VEX.NDS.128.66.0F38.W0 46 /r VPSRAVD xmm1,xmm2,xmm3/m128
	// VEX.NDS.256.66.0F38.W0 46 /r VPSRAVD ymm1,ymm2,ymm3/m256
	{ NULL, FCML_AMT_AVX2_SIMD, 0x1090, 0x00EC8000, { 0x0F, 0x38, 0x46 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L, FCML_NA, FCML_NA }, FCML_AM_NONE },
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPERMD[] = {
	// VEX.NDS.256.66.0F38.W0 36 /r VPERMD ymm1,ymm2,ymm3/m256
	{ NULL, FCML_AMT_AVX2_SIMD, 0x10B0, 0x00EC8000, { 0x0F, 0x38, 0x36 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_YMM_256, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPERMPD[] = {
	// VEX.256.66.0F3A.W1 01 /r ib VPERMPD ymm1,ymm2/m256,imm8
	{ NULL, FCML_AMT_AVX2_SIMD, 0x11A8, 0x00EC8000, { 0x0F, 0x3A, 0x01 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_MODRM_RM_YMM_256, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPERMQ[] = {
	// VEX.256.66.0F3A.W1 00 /r ib VPERMQ ymm1,ymm2/m256,imm8
	{ NULL, FCML_AMT_AVX2_SIMD, 0x11A8, 0x00EC8000, { 0x0F, 0x3A, 0x00 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_MODRM_RM_YMM_256, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPERMPS[] = {
	// VEX.NDS.256.66.0F38.W0 16 /r VPERMPS ymm1,ymm2,ymm3/m256
	{ NULL, FCML_AMT_AVX2_SIMD, 0x10B0, 0x00EC8000, { 0x0F, 0x38, 0x16 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_YMM_256, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPERM2F128[] = {
	// VEX.NDS.256.66.0F3A.W0 06 /r ib VPERM2F128 ymm1,ymm2,ymm3/m256,imm8 RVMI V/V AVX Permute 128-bit floating-point fields in ymm2 and ymm3/mem using controls from imm8 and store result in ymm1.
	{ NULL, FCML_AMT_AVX_SIMD, 0x10B0, 0x00EC8000, { 0x0F, 0x3A, 0x06 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_YMM_256, FCML_OP_IB, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPERM2I128[] = {
	// VEX.NDS.256.66.0F3A.W0 46 /r ib VPERM2I128 ymm1,ymm2,ymm3/m256,imm8
	{ NULL, FCML_AMT_AVX2_SIMD, 0x10B0, 0x00EC8000, { 0x0F, 0x3A, 0x46 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_YMM_256, FCML_OP_IB, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VEXTRACTI128[] = {
	// VEX.256.66.0F3A.W0 39 /r ib VEXTRACTI128 xmm1/m128,ymm2,imm8
	{ NULL, FCML_AMT_AVX2_SIMD, 0x11B0, 0x00EC8000, { 0x0F, 0x3A, 0x39 }, { FCML_OP_MODRM_RM_XMM_128_W, FCML_OP_MODRM_R_YMM, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VINSERTI128[] = {
	// VEX.NDS.256.66.0F3A.W0 38 /r ib VINSERTI128 ymm1,ymm2,xmm3/m128,imm8
	{ NULL, FCML_AMT_AVX2_SIMD, 0x10B0, 0x00EC8000, { 0x0F, 0x3A, 0x38 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_YMM_256, FCML_OP_IB, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VTESTPS[] = {
	// VEX.128.66.0F38.W0 0E /r VTESTPS xmm1,xmm2/m128 RM V/V AVX Set ZF and CF depending on sign bit AND and ANDN of packed single-precision floatingpoint sources.
	// VEX.256.66.0F38.W0 0E /r VTESTPS ymm1,ymm2/m256 RM V/V AVX Set ZF and CF depending on sign bit AND and ANDN of packed single-precision floatingpoint sources.
	{ NULL, FCML_AMT_AVX_SIMD, 0x1190, 0x00EC8000, { 0x0F, 0x38, 0x0E }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_MODRM_RM_SIMD_L, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.128.66.0F38.W0 0F /r VTESTPD xmm1,xmm2/m128 RM V/V AVX Set ZF and CF depending on sign bit AND and ANDN of packed double-precision floatingpoint sources.
	// VEX.256.66.0F38.W0 0F /r VTESTPD ymm1,ymm2/m256 RM V/V AVX Set ZF and CF depending on sign bit AND and ANDN of packed double-precision floatingpoint sources.
	{ "vtestpd", FCML_AMT_AVX_SIMD, 0x1190, 0x00EC8000, { 0x0F, 0x38, 0x0F }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_MODRM_RM_SIMD_L, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VGATHERDPD[] = {
	// VEX.DDS.128.66.0F38.W1 92 /r VGATHERDPD xmm1, vm32x, xmm2
	// VEX.DDS.256.66.0F38.W1 92 /r VGATHERDPD ymm1, vm32x, ymm2
	{ NULL, FCML_AMT_AVX2_SIMD, 0x1088, 0x00EC8000, { 0x0F, 0x38, 0x92 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VSIB(FCML_VSIB_XMM,FCML_EOS_DWORD), FCML_OP_VEX_VVVV_SIMD_REG, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.DDS.128.66.0F38.W1 93 /r VGATHERQPD xmm1, vm64x, xmm2
	{ "vgatherqpd", FCML_AMT_AVX2_SIMD, 0x10C8, 0x00EC8000, { 0x0F, 0x38, 0x93 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VSIB(FCML_VSIB_XMM,FCML_EOS_QWORD), FCML_OP_VEX_VVVV_SIMD_REG, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.DDS.256.66.0F38.W1 93 /r VGATHERQPD ymm1, vm64y, ymm2
	{ "vgatherqpd", FCML_AMT_AVX2_SIMD, 0x10A8, 0x00EC8000, { 0x0F, 0x38, 0x93 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VSIB(FCML_VSIB_YMM,FCML_EOS_QWORD), FCML_OP_VEX_VVVV_SIMD_REG, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VGATHERDPS[] = {
	// VEX.DDS.128.66.0F38.W0 92 /r VGATHERDPS xmm1,vm32x,xmm2
	{ NULL, FCML_AMT_AVX2_SIMD, 0x10D0, 0x00EC8000, { 0x0F, 0x38, 0x92 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VSIB(FCML_VSIB_XMM,FCML_EOS_DWORD), FCML_OP_VEX_VVVV_SIMD_REG, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.DDS.256.66.0F38.W0 92 /r VGATHERDPS ymm1,vm32y,ymm2
	{ NULL, FCML_AMT_AVX2_SIMD, 0x10B0, 0x00EC8000, { 0x0F, 0x38, 0x92 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VSIB(FCML_VSIB_YMM,FCML_EOS_DWORD), FCML_OP_VEX_VVVV_SIMD_REG, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.DDS.128.66.0F38.W0 93 /r VGATHERQPS xmm1,vm64x,xmm2
	{ "vgatherqps", FCML_AMT_AVX2_SIMD, 0x10D0, 0x00EC8000, { 0x0F, 0x38, 0x93 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VSIB(FCML_VSIB_XMM,FCML_EOS_QWORD), FCML_OP_VEX_VVVV_SIMD_REG, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.DDS.256.66.0F38.W0 93 /r VGATHERQPS xmm1,vm64y,xmm2
	{ "vgatherqps", FCML_AMT_AVX2_SIMD, 0x10B0, 0x00EC8000, { 0x0F, 0x38, 0x93 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VSIB(FCML_VSIB_YMM,FCML_EOS_QWORD), FCML_OP_VEX_VVVV_SIMD_REG, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPGATHERDD[] = {
	// VEX.DDS.128.66.0F38.W0 90 /r VPGATHERDD xmm1,vm32x,xmm2
	{ NULL, FCML_AMT_AVX2_SIMD, 0x10D0, 0x00EC8000, { 0x0F, 0x38, 0x90 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VSIB(FCML_VSIB_XMM,FCML_EOS_DWORD), FCML_OP_VEX_VVVV_SIMD_REG, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.DDS.256.66.0F38.W0 90 /r VPGATHERDD ymm1,vm32y,ymm2
	{ NULL, FCML_AMT_AVX2_SIMD, 0x10B0, 0x00EC8000, { 0x0F, 0x38, 0x90 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VSIB(FCML_VSIB_YMM,FCML_EOS_DWORD), FCML_OP_VEX_VVVV_SIMD_REG, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.DDS.128.66.0F38.W0 91 /r VPGATHERQD xmm1,vm64x,xmm2
	{ "vpgatherqd", FCML_AMT_AVX2_SIMD, 0x10D0, 0x00EC8000, { 0x0F, 0x38, 0x91 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VSIB(FCML_VSIB_XMM,FCML_EOS_QWORD), FCML_OP_VEX_VVVV_SIMD_REG, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.DDS.256.66.0F38.W0 91 /r VPGATHERQD xmm1,vm64y,xmm2
	{ "vpgatherqd", FCML_AMT_AVX2_SIMD, 0x10B0, 0x00EC8000, { 0x0F, 0x38, 0x91 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VSIB(FCML_VSIB_YMM,FCML_EOS_QWORD), FCML_OP_VEX_VVVV_SIMD_REG, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPGATHERDQ[] = {
	// VEX.DDS.128.66.0F38.W1 90 /r VPGATHERDQ xmm1,vm32x,xmm2
	// VEX.DDS.256.66.0F38.W1 90 /r VPGATHERDQ ymm1,vm32x,ymm2
	{ NULL, FCML_AMT_AVX2_SIMD, 0x1088, 0x00EC8000, { 0x0F, 0x38, 0x90 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VSIB(FCML_VSIB_XMM,FCML_EOS_DWORD), FCML_OP_VEX_VVVV_SIMD_REG, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.DDS.128.66.0F38.W1 91 /r VPGATHERQQ xmm1,vm64x,xmm2
	{ "vpgatherqq", FCML_AMT_AVX2_SIMD, 0x10C8, 0x00EC8000, { 0x0F, 0x38, 0x91 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VSIB(FCML_VSIB_XMM,FCML_EOS_QWORD), FCML_OP_VEX_VVVV_SIMD_REG, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.DDS.256.66.0F38.W1 91 /r VPGATHERQQ ymm1,vm64y,ymm2
	{ "vpgatherqq", FCML_AMT_AVX2_SIMD, 0x10A8, 0x00EC8000, { 0x0F, 0x38, 0x91 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VSIB(FCML_VSIB_YMM,FCML_EOS_QWORD), FCML_OP_VEX_VVVV_SIMD_REG, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VZEROALL[] = {
	// VEX.256.0F.WIG 77 VZEROALL NP V/V AVX Zero all YMM registers.
	{ NULL, FCML_AMT_AVX_SIMD, 0x01A0, 0x00D80000, { 0x0F, 0x77, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VZEROUPPER[] = {
	// VEX.128.0F.WIG 77 VZEROUPPER NP V/V AVX Zero upper 128 bits of all YMM registers.
	{ NULL, FCML_AMT_AVX_SIMD, 0x01C0, 0x00D80000, { 0x0F, 0x77, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_WAIT[] = {
	// 9B WAIT NP Valid Valid Check pending unmasked floating-point exceptions.
	// 9B FWAIT NP Valid Valid Check pending unmasked floating-point exceptions.
	{ NULL, FCML_AMT_FPU, 0x0000, 0x00C40000, { 0x9B, 0x00, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_WBINVD[] = {
	// 0F 09 WBINVD NP Valid Valid Write back and flush Internal caches; initiate writing-back and flushing of external caches.
	{ NULL, FCML_AMT_SYSTEM, 0x0000, 0x00D80000, { 0x0F, 0x09, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_WRFSBASE[] = {
	// F3 0F AE /2 WRFSBASE r32 M V/I FSGSBASE Load the FS base address with the 32-bit value in the source register.
	{ NULL, FCML_AMT_SYSTEM | FCML_AMT_FSGSBASE, 0x4010, 0x03DB9000, { 0x0F, 0xAE, 0x00 }, { FCML_OP_RM( FCML_REG_GPR, FCML_EOS_DWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_NA , FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// REX.W + F3 0F AE /2 WRFSBASE r64 M V/I FSGSBASE Load the FS base address with the 64-bit value in the source register.
	{ NULL, FCML_AMT_SYSTEM | FCML_AMT_FSGSBASE, 0x4008, 0x049B9000, { 0x0F, 0xAE, 0x00 }, { FCML_OP_RM( FCML_REG_GPR, FCML_EOS_QWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_NA , FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// F3 0F AE /3 WRGSBASE r32 M V/I FSGSBASE Load the GS base address with the 32-bit value in the source register.
	{ "wrgsbase", FCML_AMT_SYSTEM | FCML_AMT_FSGSBASE, 0x4010, 0x03DB9800, { 0x0F, 0xAE, 0x00 }, { FCML_OP_RM( FCML_REG_GPR, FCML_EOS_DWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_NA , FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// REX.W + F3 0F AE /3 WRGSBASE r64 M V/I FSGSBASE Load the GS base address with the 64-bit value in the source register.
	{ "wrgsbase", FCML_AMT_SYSTEM | FCML_AMT_FSGSBASE, 0x4008, 0x049B9800, { 0x0F, 0xAE, 0x00 }, { FCML_OP_RM( FCML_REG_GPR, FCML_EOS_QWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_NA , FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_WRMSR[] = {
	// 0F 30 WRMSR NP Valid Valid Write the value in EDX:EAX to MSR specified by ECX.
	{ NULL, FCML_AMT_SYSTEM, 0x0000, 0x00D80000, { 0x0F, 0x30, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_XADD[] = {
	// 0F C0 /r XADD r/m8,r8 MR Valid Valid Exchange r8 and r/m8; load sum into r/m8.
	// REX + 0F C0 /r XADD r/m8*,r8* MR Valid N.E. Exchange r8 and r/m8; load sum into r/m8.
	{ NULL, FCML_AMT_GPI, 0x0807, 0x00D88000, { 0x0F, 0xC0, 0x00 }, { FCML_OP_MODRM_RM_8_W, FCML_OP_MODRM_R_8, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 0F C1 /r XADD r/m16,r16 MR Valid Valid Exchange r16 and r/m16; load sum into r/m16.
	// 0F C1 /r XADD r/m32,r32 MR Valid Valid Exchange r32 and r/m32; load sum into r/m32.
	// REX.W + 0F C1 /r XADD r/m64,r64 MR Valid N.E. Exchange r64 and r/m64; load sum into r/m64.
	{ NULL, FCML_AMT_GPI, 0x0807, 0x00D88000, { 0x0F, 0xC1, 0x00 }, { FCML_OP_MODRM_RM_W, FCML_OP_MODRM_R, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_XCHG[] = {
	// 90+rw XCHG AX, r16 O Valid Valid Exchange r16 with AX.
	// 90+rw XCHG r16, AX O Valid Valid Exchange AX with r16.
	// 90+rd XCHG EAX, r32 O Valid Valid Exchange r32 with EAX.
	// 90+rd XCHG r32, EAX O Valid Valid Exchange EAX with r32.
	// REX.W + 90+rd XCHG RAX, r64 O Valid N.E. Exchange r64 with RAX.
	// REX.W + 90+rd XCHG r64, RAX O Valid N.E. Exchange RAX with r64.
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00C40001, { 0x90, 0x00, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_EAX, FCML_EOS_EOSA ) | FCML_OA_W, FCML_OP_OPCODE_REG( FCML_REG_GPR, FCML_EOS_EOSA) | FCML_OA_W, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00C40001, { 0x90, 0x00, 0x00 }, { FCML_OP_OPCODE_REG( FCML_REG_GPR, FCML_EOS_EOSA) | FCML_OA_W, FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_EAX, FCML_EOS_EOSA ) | FCML_OA_W, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 86 /r XCHG r/m8, r8 MR Valid Valid Exchange r8 (byte register) with byte from r/m8.
	// REX + 86 /r XCHG r/m8*, r8* MR Valid N.E. Exchange r8 (byte register) with byte from r/m8.
	// 86 /r XCHG r8, r/m8 RM Valid Valid Exchange byte from r/m8 with r8 (byte register).
	// REX + 86 /r XCHG r8*, r/m8* RM Valid N.E. Exchange byte from r/m8 with r8 (byte register).
	{ NULL, FCML_AMT_GPI, 0x0807, 0x00C48000, { 0x86, 0x00, 0x00 }, { FCML_OP_MODRM_RM_8_W, FCML_OP_MODRM_R_8_W, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	{ NULL, FCML_AMT_GPI, 0x0807, 0x00C48000, { 0x86, 0x00, 0x00 }, { FCML_OP_MODRM_R_8_W, FCML_OP_MODRM_RM_8_W, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 87 /r XCHG r/m16, r16 MR Valid Valid Exchange r16 with word from r/m16.
	// 87 /r XCHG r16, r/m16 RM Valid Valid Exchange word from r/m16 with r16.
	// 87 /r XCHG r/m32, r32 MR Valid Valid Exchange r32 with doubleword from r/m32.
	// 87 /r XCHG r32, r/m32 RM Valid Valid Exchange doubleword from r/m32 with r32.
	// REX.W + 87 /r XCHG r/m64, r64 MR Valid N.E. Exchange r64 with quadword from r/m64.
	// REX.W + 87 /r XCHG r64, r/m64 RM Valid N.E. Exchange quadword from r/m64 with r64.
	{ NULL, FCML_AMT_GPI, 0x0807, 0x00C48000, { 0x87, 0x00, 0x00 }, { FCML_OP_MODRM_RM_W, FCML_OP_MODRM_R_W, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	{ NULL, FCML_AMT_GPI, 0x0807, 0x00C48000, { 0x87, 0x00, 0x00 }, { FCML_OP_MODRM_R_W, FCML_OP_MODRM_RM_W, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_XGETBV[] = {
	// 0F 01 D0 XGETBV NP Valid Valid Reads an XCR specified by ECX into EDX:EAX.
	{ NULL, FCML_AMT_SYSTEM, 0x0000, 0x00EC0000, { 0x0F, 0x01, 0xD0 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_XLAT[] = {
	// D7 XLAT m8 NP Valid Valid Set AL to memory byte DS:[(E)BX + unsigned AL].
	// D7 XLATB NP Valid Valid Set AL to memory byte DS:[(E)BX + unsigned AL].
	// REX.W + D7 XLATB NP Valid N.E. Set AL to memory byte [RBX + unsigned AL].
	{ "xlat;xlatb[ts]", FCML_AMT_GPI, 0x0000, 0x00C40000, { 0xD7, 0x00, 0x00 },
			{ FCML_OP_EXPLICIT_GPS_REG_ADDRESSING( FCML_REG_BX, FCML_EOS_BYTE, FCML_SEG_ENCODE_REGISTER( FCML_REG_DS, FCML_SEG_ALLOW_OVERRIDE ) ),
			FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_XOR[] = {
	// 34 ib XOR AL, imm8 I Valid Valid AL XOR imm8.
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00C40000, { 0x34, 0x00, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_AL, FCML_EOS_BYTE ), FCML_OP_IB, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 35 iw XOR AX, imm16 I Valid Valid AX XOR imm16.
	// 35 id XOR EAX, imm32 I Valid Valid EAX XOR imm32.
	{ NULL, FCML_AMT_GPI, 0x0010, 0x03C40000, { 0x35, 0x00, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_AL, FCML_EOS_EOSA ) | FCML_OA_W, FCML_OP_IMM_EOSA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// REX.W + 35 id XOR RAX, imm32 I Valid N.E. RAX XOR imm32 (sign-extended).
	{ NULL, FCML_AMT_GPI, 0x0008, 0x04840000, { 0x35, 0x00, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_AL, FCML_EOS_EOSA ) | FCML_OA_W, FCML_OP_ID_EX_EOSA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 80 /6 ib XOR r/m8, imm8 MI Valid Valid r/m8 XOR imm8.
	// REX + 80 /6 ib XOR r/m8*, imm8 MI Valid N.E. r/m8 XOR imm8.
	{ NULL, FCML_AMT_GPI, 0x0807, 0x00C5B000, { 0x80, 0x00, 0x00 }, { FCML_OP_MODRM_RM_8_W, FCML_OP_IB, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 81 /6 iw XOR r/m16, imm16 MI Valid Valid r/m16 XOR imm16.
	// 81 /6 id XOR r/m32, imm32 MI Valid Valid r/m32 XOR imm32.
	{ NULL, FCML_AMT_GPI, 0x0817, 0x03C5B000, { 0x81, 0x00, 0x00 }, { FCML_OP_MODRM_RM_W, FCML_OP_IMM_EOSA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// REX.W + 81 /6 id XOR r/m64, imm32 MI Valid N.E. r/m64 XOR imm32 (sign-extended).
	{ NULL, FCML_AMT_GPI, 0x080F, 0x0485B000, { 0x81, 0x00, 0x00 }, { FCML_OP_MODRM_RM_W, FCML_OP_ID_EX_EOSA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 83 /6 ib XOR r/m16, imm8 MI Valid Valid r/m16 XOR imm8 (sign-extended).
	// 83 /6 ib XOR r/m32, imm8 MI Valid Valid r/m32 XOR imm8 (sign-extended).
	{ NULL, FCML_AMT_GPI, 0x0817, 0x03C5B000, { 0x83, 0x00, 0x00 }, { FCML_OP_MODRM_RM_W, FCML_OP_IB_EX_EOSA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// REX.W + 83 /6 ib XOR r/m64, imm8 MI Valid N.E. r/m64 XOR imm8 (sign-extended).
	{ NULL, FCML_AMT_GPI, 0x080F, 0x0485B000, { 0x83, 0x00, 0x00 }, { FCML_OP_MODRM_RM_W, FCML_OP_IB_EX_EOSA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 30 /r XOR r/m8, r8 MR Valid Valid r/m8 XOR r8.
	// REX + 30 /r XOR r/m8*, r8* MR Valid N.E. r/m8 XOR r8.
	{ NULL, FCML_AMT_GPI, 0x0807, 0x00C48000, { 0x30, 0x00, 0x00 }, { FCML_OP_MODRM_RM_8_W, FCML_OP_MODRM_R_8, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 31 /r XOR r/m16, r16 MR Valid Valid r/m16 XOR r16.
	// 31 /r XOR r/m32, r32 MR Valid Valid r/m32 XOR r32.
	// REX.W + 31 /r XOR r/m64, r64 MR Valid N.E. r/m64 XOR r64.
	{ NULL, FCML_AMT_GPI, 0x0807, 0x00C48000, { 0x31, 0x00, 0x00 }, { FCML_OP_MODRM_RM_W, FCML_OP_MODRM_R, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 32 /r XOR r8, r/m8 RM Valid Valid r8 XOR r/m8.
	// REX + 32 /r XOR r8*, r/m8* RM Valid N.E. r8 XOR r/m8.
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00C48000, { 0x32, 0x00, 0x00 }, { FCML_OP_MODRM_R_8_W, FCML_OP_MODRM_RM_8, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// 33 /r XOR r16, r/m16 RM Valid Valid r16 XOR r/m16.
	// 33 /r XOR r32, r/m32 RM Valid Valid r32 XOR r/m32.
	// REX.W + 33 /r XOR r64, r/m64 RM Valid N.E. r64 XOR r/m64.
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00C48000, { 0x33, 0x00, 0x00 }, { FCML_OP_MODRM_R_W, FCML_OP_MODRM_RM, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_XORPD[] = {
	// 66 0F 57 /r XORPD xmm1,xmm2/m128 RM V/V SSE2 Bitwise exclusive-OR of xmm2/m128 and xmm1.
	{ NULL, FCML_AMT_SSE2_SIMD, 0x1000, 0x00D88000, { 0x0F, 0x57, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.66.0F.WIG 57 /r VXORPD xmm1,xmm2,xmm3/m128 RVM V/V AVX Return the bitwise logical XOR of packed double-precision floating-point values in xmm2 and xmm3/mem.
	// VEX.NDS.256.66.0F.WIG 57 /r VXORPD ymm1,ymm2,ymm3/m256 RVM V/V AVX Return the bitwise logical XOR of packed double-precision floating-point values in ymm2 and ymm3/mem.
	{ "vxorpd", FCML_AMT_AVX_SIMD, 0x1080, 0x00D88000, { 0x0F, 0x57, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_XORPS[] = {
	// 0F 57 /r XORPS xmm1,xmm2/m128 RM V/V SSE Bitwise exclusive-OR of xmm2/m128 and xmm1.
	{ NULL, FCML_AMT_SSE_SIMD, 0x0000, 0x00D88000, { 0x0F, 0x57, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.128.0F.WIG 57 /r VXORPS xmm1,xmm2,xmm3/m128 RVM V/V AVX Return the bitwise logical XOR of packed single-precision floating-point values in xmm2 and xmm3/mem.
	// VEX.NDS.256.0F.WIG 57 /r VXORPS ymm1,ymm2,ymm3/m256 RVM V/V AVX Return the bitwise logical XOR of packed single-precision floating-point values in ymm2 and ymm3/mem.
	{ "vxorps", FCML_AMT_AVX_SIMD, 0x0080, 0x00D88000, { 0x0F, 0x57, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_XRSTOR[] = {
	// 0F AE /5 XRSTOR mem M Valid Valid Restore processor extended states from memory. The states are specified by EDX:EAX
	{ NULL, FCML_AMT_SYSTEM, 0x0010, 0x03D9A800, { 0x0F, 0xAE, 0x00 }, { FCML_OP_MODRM_M_512B, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// REX.W+ 0F AE /5 XRSTOR64 mem M Valid N.E. Restore processor extended states from memory. The states are specified by EDX:EAX
	{ "xrstor64", FCML_AMT_SYSTEM, 0x0008, 0x0499A800, { 0x0F, 0xAE, 0x00 }, { FCML_OP_MODRM_M_512B, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_XSAVE[] = {
	// 0F AE /4 XSAVE mem M Valid Valid Save processor extended states to memory. The states are specified by EDX:EAX
	{ NULL, FCML_AMT_SYSTEM, 0x0010, 0x03D9A000, { 0x0F, 0xAE, 0x00 }, { FCML_OP_MODRM_M_512B, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// REX.W+ 0F AE /4 XSAVE64 mem M Valid N.E. Save processor extended states to memory. The states are specified by EDX:EAX
	{ "xsave64", FCML_AMT_SYSTEM, 0x0008, 0x0499A000, { 0x0F, 0xAE, 0x00 }, { FCML_OP_MODRM_M_512B, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_XSAVEOPT[] = {
	// 0F AE /6 XSAVEOPT mem M V/V XSAVEOPT Save processor extended states specified in EDX:EAX to memory, optimizing the state save operation if possible.
	{ NULL, FCML_AMT_SYSTEM, 0x0010, 0x03D9B000, { 0x0F, 0xAE, 0x00 }, { FCML_OP_MODRM_M_UNDEF_W, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// REX.W + 0F AE /6 XSAVEOPT64 mem M V/V XSAVEOPT Save processor extended states specified in EDX:EAX to memory, optimizing the state save operation if possible.
	{ "xsaveopt64", FCML_AMT_SYSTEM, 0x0008, 0x0499B000, { 0x0F, 0xAE, 0x00 }, { FCML_OP_MODRM_M_UNDEF_W, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_XSETBV[] = {
	// 0F 01 D1 XSETBV NP Valid Valid Write the value in EDX:EAX to the XCR specified by ECX.
	{ NULL, FCML_AMT_SYSTEM, 0x0000, 0x00EC0000, { 0x0F, 0x01, 0xD1 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
};

/****************
 * AMD 3D Now!
 ****************/

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FEMMS[] = {
	// FEMMS 0F 0Eh Faster Enter/Exit of the MMX or floating-point state
	{ NULL, FCML_AMT_3DNOW, 0x0000, 0x00D80000, { 0x0F, 0x0E, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PAVGUSB[] = {
	// PAVGUSB mmreg1, mmreg2/mem64 0F 0Fh / BFh Average of unsigned packed 8-bit values
	{ NULL, FCML_AMT_3DNOW_SIMD, 0x0000, 0x00EC8000, { 0x0F, 0x0F, 0xBF }, { FCML_OP_MODRM_R_MMX_W, FCML_OP_MODRM_RM_MMX, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PF2ID[] = {
	// PF2ID mmreg1, mmreg2/mem64 0Fh 0Fh / 1Dh Converts packed floating-point operand to packed 32-bit integer
	{ NULL, FCML_AMT_3DNOW_SIMD, 0x0000, 0x00EC8000, { 0x0F, 0x0F, 0x1D }, { FCML_OP_MODRM_R_MMX_W, FCML_OP_MODRM_RM_MMX, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PFACC[] = {
	// PFACC mmreg1, mmreg2/mem64 0Fh 0Fh / AEh Floating-point accumulate
	{ NULL, FCML_AMT_3DNOW_SIMD, 0x0000, 0x00EC8000, { 0x0F, 0x0F, 0xAE }, { FCML_OP_MODRM_R_MMX_W, FCML_OP_MODRM_RM_MMX, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PFADD[] = {
	// PFADD mmreg1, mmreg2/mem64 0Fh 0Fh / 9Eh Packed, floating-point addition
	{ NULL, FCML_AMT_3DNOW_SIMD, 0x0000, 0x00EC8000, { 0x0F, 0x0F, 0x9E }, { FCML_OP_MODRM_R_MMX_W, FCML_OP_MODRM_RM_MMX, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PFCMPEQ[] = {
	// PFCMPEQ mmreg1, mmreg2/mem64 0Fh 0Fh / B0h Packed floating-point comparison, equal to
	{ NULL, FCML_AMT_3DNOW_SIMD, 0x0000, 0x00EC8000, { 0x0F, 0x0F, 0xB0 }, { FCML_OP_MODRM_R_MMX_W, FCML_OP_MODRM_RM_MMX, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PFCMPGE[] = {
	// PFCMPGE mmreg1, mmreg2/mem64 0Fh 0Fh / 90h Packed floating-point comparison, greater than or equal to
	{ NULL, FCML_AMT_3DNOW_SIMD, 0x0000, 0x00EC8000, { 0x0F, 0x0F, 0x90 }, { FCML_OP_MODRM_R_MMX_W, FCML_OP_MODRM_RM_MMX, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PFCMPGT[] = {
	// PFCMPGT mmreg1, mmreg2/mem64 0Fh 0Fh / A0h Packed floating-point comparison, greater than
	{ NULL, FCML_AMT_3DNOW_SIMD, 0x0000, 0x00EC8000, { 0x0F, 0x0F, 0xA0 }, { FCML_OP_MODRM_R_MMX_W, FCML_OP_MODRM_RM_MMX, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PFMAX[] = {
	// PFMAX mmreg1, mmreg2/mem64 0Fh 0Fh / A4h Packed floating-point maximum
	{ NULL, FCML_AMT_3DNOW_SIMD, 0x0000, 0x00EC8000, { 0x0F, 0x0F, 0xA4 }, { FCML_OP_MODRM_R_MMX_W, FCML_OP_MODRM_RM_MMX, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PFMIN[] = {
	// PFMIN mmreg1, mmreg2/mem64 0Fh 0Fh / 94h Packed floating-point minimum
	{ NULL, FCML_AMT_3DNOW_SIMD, 0x0000, 0x00EC8000, { 0x0F, 0x0F, 0x94 }, { FCML_OP_MODRM_R_MMX_W, FCML_OP_MODRM_RM_MMX, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PFMUL[] = {
	// PFMUL mmreg1, mmreg2/mem64 0Fh 0Fh / B4h Packed floating-point multiplication
	{ NULL, FCML_AMT_3DNOW_SIMD, 0x0000, 0x00EC8000, { 0x0F, 0x0F, 0xB4 }, { FCML_OP_MODRM_R_MMX_W, FCML_OP_MODRM_RM_MMX, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PFRCP[] = {
	// PFRCP mmreg1, mmreg2/mem64 0Fh 0Fh / 96h Floating-point reciprocal approximation
	{ NULL, FCML_AMT_3DNOW_SIMD, 0x0000, 0x00EC8000, { 0x0F, 0x0F, 0x96 }, { FCML_OP_MODRM_R_MMX_W, FCML_OP_MODRM_RM_MMX, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PFRCPIT1[] = {
	// PFRCPIT1 mmreg1, mmreg2/mem64 0Fh 0Fh / A6h Packed floating-point reciprocal, first iteration step
	{ NULL, FCML_AMT_3DNOW_SIMD, 0x0000, 0x00EC8000, { 0x0F, 0x0F, 0xA6 }, { FCML_OP_MODRM_R_MMX_W, FCML_OP_MODRM_RM_MMX, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PFRCPIT2[] = {
	// PFRCPIT2 mmreg1, mmreg2/mem64 0Fh 0Fh / B6h Packed floating-point reciprocal/reciprocal square root, second iteration step
	{ NULL, FCML_AMT_3DNOW_SIMD, 0x0000, 0x00EC8000, { 0x0F, 0x0F, 0xB6 }, { FCML_OP_MODRM_R_MMX_W, FCML_OP_MODRM_RM_MMX, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PFRSQIT1[] = {
	// PFRSQIT1 mmreg1, mmreg2/mem64 0Fh 0Fh / A7h Packed floating-point reciprocal square root, first iteration step
	{ NULL, FCML_AMT_3DNOW_SIMD, 0x0000, 0x00EC8000, { 0x0F, 0x0F, 0xA7 }, { FCML_OP_MODRM_R_MMX_W, FCML_OP_MODRM_RM_MMX, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PFRSQRT[] = {
	// PFRSQRT mmreg1, mmreg2/mem64 0Fh 0Fh / 97h Floating-point reciprocal square root approximation
	{ NULL, FCML_AMT_3DNOW_SIMD, 0x0000, 0x00EC8000, { 0x0F, 0x0F, 0x97 }, { FCML_OP_MODRM_R_MMX_W, FCML_OP_MODRM_RM_MMX, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PFSUB[] = {
	// PFSUB mmreg1, mmreg2/mem64 0Fh 0Fh / 9Ah Packed floating-point subtraction
	{ NULL, FCML_AMT_3DNOW_SIMD, 0x0000, 0x00EC8000, { 0x0F, 0x0F, 0x9A }, { FCML_OP_MODRM_R_MMX_W, FCML_OP_MODRM_RM_MMX, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PFSUBR[] = {
	// PFSUBR mmreg1, mmreg2/mem64 0Fh 0Fh / AAh Packed floating-point reverse subtraction
	{ NULL, FCML_AMT_3DNOW_SIMD, 0x0000, 0x00EC8000, { 0x0F, 0x0F, 0xAA }, { FCML_OP_MODRM_R_MMX_W, FCML_OP_MODRM_RM_MMX, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PI2FD[] = {
	// PI2FD mmreg1, mmreg2/mem64 0Fh 0Fh / 0Dh Packed 32-bit integer to floating-point conversion
	{ NULL, FCML_AMT_3DNOW_SIMD, 0x0000, 0x00EC8000, { 0x0F, 0x0F, 0x0D }, { FCML_OP_MODRM_R_MMX_W, FCML_OP_MODRM_RM_MMX, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PMULHRW[] = {
	// PMULHRW mmreg1, mmreg2/mem64 0F 0Fh/B7h Multiply signed packed 16-bit values with rounding and store the high 16 bits.
	{ NULL, FCML_AMT_3DNOW_SIMD, 0x0000, 0x00EC8000, { 0x0F, 0x0F, 0xB7 }, { FCML_OP_MODRM_R_MMX_W, FCML_OP_MODRM_RM_MMX, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PREFETCH[] = {
	// PREFETCH mem8 0F 0Dh Prefetch processor cache line into L1 data cache (Dcache)
	{ NULL, FCML_AMT_3DNOW | FCML_AMT_PRFCHW, 0x0000, 0x80D98000, { 0x0F, 0x0D, 0x00 }, { FCML_OP_MODRM_M_8, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// PREFETCHW mem8 0F 0Dh Prefetch processor cache line into L1 data cache (Dcache)
	{ "prefetchw", FCML_AMT_3DNOW | FCML_AMT_PRFCHW, 0x0000, 0x80D98800, { 0x0F, 0x0D, 0x00 }, { FCML_OP_MODRM_M_8, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

// Extensions to the 3DNow!

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PF2IW[] = {
	// PF2IW mmreg1, mmreg2/mem64 0Fh 0Fh / 1Ch Packed floating-point to integer word conversion with PF2IW sign extend
	{ NULL, FCML_AMT_3DNOW_SIMD, 0x0000, 0x00EC8000, { 0x0F, 0x0F, 0xC1 }, { FCML_OP_MODRM_R_MMX_W, FCML_OP_MODRM_RM_MMX, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PFNACC[] = {
	// PFNACC mmreg1, mmreg2/mem64 0Fh 0Fh / 8Ah Packed floating-point negative accumulate
	{ NULL, FCML_AMT_3DNOW_SIMD, 0x0000, 0x00EC8000, { 0x0F, 0x0F, 0x8A }, { FCML_OP_MODRM_R_MMX_W, FCML_OP_MODRM_RM_MMX, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PFPNACC[] = {
	// PFPNACC mmreg1, mmreg2/mem64 0Fh 0Fh / 8Eh Packed floating-point mixed positive-negative accumulate
	{ NULL, FCML_AMT_3DNOW_SIMD, 0x0000, 0x00EC8000, { 0x0F, 0x0F, 0x8E }, { FCML_OP_MODRM_R_MMX_W, FCML_OP_MODRM_RM_MMX, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PI2FW[] = {
	// PI2FW mmreg1, mmreg2/mem64 0Fh 0Fh / 0Ch Packed 16-bit integer to floating-point conversion
	{ NULL, FCML_AMT_3DNOW_SIMD, 0x0000, 0x00EC8000, { 0x0F, 0x0F, 0x0C }, { FCML_OP_MODRM_R_MMX_W, FCML_OP_MODRM_RM_MMX, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PSWAPD[] = {
	// PSWAPD mmreg1, mmreg2/mem64 0Fh 0Fh / BBh Packed swap doubleword
	{ NULL, FCML_AMT_3DNOW_SIMD, 0x0000, 0x00EC8000, { 0x0F, 0x0F, 0xBB }, { FCML_OP_MODRM_R_MMX_W, FCML_OP_MODRM_RM_MMX, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

/* FMA */

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VFMADDPD[] = {
	// VEX.DDS.128.66.0F38.W1 98 /r VFMADD132PD xmm0,xmm1,xmm2/m128
	// VEX.DDS.256.66.0F38.W1 98 /r VFMADD132PD ymm0,ymm1,ymm2/m256
	{ "vfmadd132pd", FCML_AMT_FMA, 0x1088, 0x00EC8000, { 0x0F, 0x38, 0x98 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.DDS.128.66.0F38.W1 A8 /r VFMADD213PD xmm0,xmm1,xmm2/m128
	// VEX.DDS.256.66.0F38.W1 A8 /r VFMADD213PD ymm0,ymm1,ymm2/m256
	{ "vfmadd213pd", FCML_AMT_FMA, 0x1088, 0x00EC8000, { 0x0F, 0x38, 0xA8 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.DDS.128.66.0F38.W1 B8 /r VFMADD231PD xmm0,xmm1,xmm2/m128
	// VEX.DDS.256.66.0F38.W1 B8 /r VFMADD231PD ymm0,ymm1,ymm2/m256
	{ "vfmadd231pd", FCML_AMT_FMA, 0x1088, 0x00EC8000, { 0x0F, 0x38, 0xB8 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VFMADDPD xmm1, xmm2, xmm3/mem128, xmm4 C4 RXB.00011 0.src.0.01 69 /r /is4
	// VFMADDPD ymm1, ymm2, ymm3/mem256, ymm4 C4 RXB.00011 0.src.1.01 69 /r /is4
	{ "vfmaddpd", FCML_AMT_FMA4, 0x1090, 0x00EC8000, { 0x0F, 0x3A, 0x69 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L, FCML_OP_OPERAND_IS4, FCML_NA }, FCML_AM_NONE },
	// VFMADDPD xmm1, xmm2, xmm3, xmm4/mem128 C4 RXB.00011 1.src.0.01 69 /r /is4
	// VFMADDPD ymm1, ymm2, ymm3, ymm4/mem256 C4 RXB.00011 1.src.1.01 69 /r /is4
	{ "vfmaddpd", FCML_AMT_FMA4, 0x1088, 0x00EC8000, { 0x0F, 0x3A, 0x69 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_OPERAND_IS4, FCML_OP_MODRM_RM_SIMD_L, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VFMADDPS[] = {
	// VEX.DDS.128.66.0F38.W0 98 /r VFMADD132PS xmm0,xmm1,xmm2/m128
	// VEX.DDS.256.66.0F38.W0 98 /r VFMADD132PS ymm0,ymm1,ymm2/m256
	{ "vfmadd132ps", FCML_AMT_FMA, 0x1090, 0x00EC8000, { 0x0F, 0x38, 0x98 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.DDS.128.66.0F38.W0 A8 /r VFMADD213PS xmm0,xmm1,xmm2/m128
	// VEX.DDS.256.66.0F38.W0 A8 /r VFMADD213PS ymm0,ymm1,ymm2/m256
	{ "vfmadd213ps", FCML_AMT_FMA, 0x1090, 0x00EC8000, { 0x0F, 0x38, 0xA8 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.DDS.128.66.0F38.W0 B8 /r VFMADD231PS xmm0,xmm1,xmm2/m128
	// VEX.DDS.256.66.0F38.W0 B8 /r VFMADD231PS ymm0,ymm1,ymm2/m256
	{ "vfmadd231ps", FCML_AMT_FMA, 0x1090, 0x00EC8000, { 0x0F, 0x38, 0xB8 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VFMADDPS xmm1, xmm2, xmm3/mem128, xmm4 C4 RXB.00011 0.src.0.01 68 /r /is4
	// VFMADDPS ymm1, ymm2, ymm3/mem256, ymm4 C4 RXB.00011 0.src.1.01 68 /r /is4
	{ "vfmaddps", FCML_AMT_FMA4, 0x1090, 0x00EC8000, { 0x0F, 0x3A, 0x68 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L, FCML_OP_OPERAND_IS4, FCML_NA }, FCML_AM_NONE },
	// VFMADDPS xmm1, xmm2, xmm3, xmm4/mem128 C4 RXB.00011 1.src.0.01 68 /r /is4
	// VFMADDPS ymm1, ymm2, ymm3, ymm4/mem256 C4 RXB.00011 1.src.1.01 68 /r /is4
	{ "vfmaddps", FCML_AMT_FMA4, 0x1088, 0x00EC8000, { 0x0F, 0x3A, 0x68 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_OPERAND_IS4, FCML_OP_MODRM_RM_SIMD_L, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VFMADDSD[] = {
	// VEX.DDS.LIG.128.66.0F38.W1 99 /r VFMADD132SD xmm0,xmm1,xmm2/m64
	{ "vfmadd132sd", FCML_AMT_FMA, 0x10C8, 0x00EC8000, { 0x0F, 0x38, 0x99 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_64, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.DDS.LIG.128.66.0F38.W1 A9 /r VFMADD213SD xmm0,xmm1,xmm2/m64
	{ "vfmadd213sd", FCML_AMT_FMA, 0x10C8, 0x00EC8000, { 0x0F, 0x38, 0xA9 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_64, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.DDS.LIG.128.66.0F38.W1 B9 /r VFMADD231SD xmm0,xmm1,xmm2/m64
	{ "vfmadd231sd", FCML_AMT_FMA, 0x10C8, 0x00EC8000, { 0x0F, 0x38, 0xB9 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_64, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VFMADDSD xmm1, xmm2, xmm3/mem128, xmm4 C4 RXB.00011 0.src.X.01 6B /r /is4
	{ "vfmaddsd", FCML_AMT_FMA4, 0x10D0, 0x00EC8000, { 0x0F, 0x3A, 0x6B }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_128, FCML_OP_OPERAND_IS4, FCML_NA }, FCML_AM_NONE },
	// VFMADDSD xmm1, xmm2, xmm3, xmm4/mem128 C4 RXB.00011 1.src.X.01 6B /r /is4
	{ "vfmaddsd", FCML_AMT_FMA4, 0x10C8, 0x00EC8000, { 0x0F, 0x3A, 0x6B }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_OPERAND_IS4, FCML_OP_MODRM_RM_XMM_128, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VFMADDSS[] = {
	// VEX.DDS.LIG.128.66.0F38.W0 99 /r VFMADD132SS xmm0,xmm1,xmm2/m32
	{ "vfmadd132ss", FCML_AMT_FMA, 0x10D0, 0x00EC8000, { 0x0F, 0x38, 0x99 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_32, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.DDS.LIG.128.66.0F38.W0 A9 /r VFMADD213SS xmm0,xmm1,xmm2/m32
	{ "vfmadd213ss", FCML_AMT_FMA, 0x10D0, 0x00EC8000, { 0x0F, 0x38, 0xA9 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_32, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.DDS.LIG.128.66.0F38.W0 B9 /r VFMADD231SS xmm0,xmm1,xmm2/m32
	{ "vfmadd231ss", FCML_AMT_FMA, 0x10D0, 0x00EC8000, { 0x0F, 0x38, 0xB9 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_32, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VFMADDSS xmm1, xmm2, xmm3/mem32, xmm4 C4 RXB.00011 0.src.X.01 6A /r /is4
	{ "vfmaddss", FCML_AMT_FMA4, 0x10D0, 0x00EC8000, { 0x0F, 0x3A, 0x6A }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_32, FCML_OP_OPERAND_IS4, FCML_NA }, FCML_AM_NONE },
	// VFMADDSS xmm1, xmm2, xmm3, xmm4/mem32 C4 RXB.00011 1.src.X.01 6A /r /is4
	{ "vfmaddss", FCML_AMT_FMA4, 0x10C8, 0x00EC8000, { 0x0F, 0x3A, 0x6A }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_OPERAND_IS4, FCML_OP_MODRM_RM_XMM_32, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VFMADDSUBPD[] = {
	// VEX.DDS.128.66.0F38.W1 96 /r VFMADDSUB132PD xmm0,xmm1,xmm2/m128
	// VEX.DDS.256.66.0F38.W1 96 /r VFMADDSUB132PD ymm0,ymm1,ymm2/m256
	{ "vfmaddsub132pd", FCML_AMT_FMA, 0x1088, 0x00EC8000, { 0x0F, 0x38, 0x96 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.DDS.128.66.0F38.W1 A6 /r VFMADDSUB213PD xmm0,xmm1,xmm2/m128
	// VEX.DDS.256.66.0F38.W1 A6 /r VFMADDSUB213PD ymm0,ymm1,ymm2/m256
	{ "vfmaddsub213pd", FCML_AMT_FMA, 0x1088, 0x00EC8000, { 0x0F, 0x38, 0xA6 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.DDS.128.66.0F38.W1 B6 /r VFMADDSUB231PD xmm0,xmm1,xmm2/m128
	// VEX.DDS.256.66.0F38.W1 B6 /r VFMADDSUB231PD ymm0,ymm1,ymm2/m256
	{ "vfmaddsub231pd", FCML_AMT_FMA, 0x1088, 0x00EC8000, { 0x0F, 0x38, 0xB6 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VFMADDSUBPD xmm1, xmm2, xmm3/mem128, xmm4 C4 RXB.00011 0.src.0.01 5D /r /is4
	// VFMADDSUBPD ymm1, ymm2, ymm3/mem256, ymm4 C4 RXB.00011 0.src.1.01 5D /r /is4
	{ "vfmaddsubpd", FCML_AMT_FMA4, 0x1090, 0x00EC8000, { 0x0F, 0x3A, 0x5D }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L, FCML_OP_OPERAND_IS4, FCML_NA }, FCML_AM_NONE },
	// VFMADDSUBPD xmm1, xmm2, xmm3, xmm4/mem128 C4 RXB.00011 1.src.0.01 5D /r /is4
	// VFMADDSUBPD ymm1, ymm2, ymm3, ymm4/mem256 C4 RXB.00011 1.src.1.01 5D /r /is4
	{ "vfmaddsubpd", FCML_AMT_FMA4, 0x1088, 0x00EC8000, { 0x0F, 0x3A, 0x5D }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_OPERAND_IS4, FCML_OP_MODRM_RM_SIMD_L, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VFMADDSUBPS[] = {
	// VEX.DDS.128.66.0F38.W0 96 /r VFMADDSUB132PS xmm0,xmm1,xmm2/m128
	// VEX.DDS.256.66.0F38.W0 96 /r VFMADDSUB132PS ymm0,ymm1,ymm2/m256
	{ "vfmaddsub132ps", FCML_AMT_FMA, 0x1090, 0x00EC8000, { 0x0F, 0x38, 0x96 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.DDS.128.66.0F38.W0 A6 /r VFMADDSUB213PS xmm0,xmm1,xmm2/m128
	// VEX.DDS.256.66.0F38.W0 A6 /r VFMADDSUB213PS ymm0,ymm1,ymm2/m256
	{ "vfmaddsub213ps", FCML_AMT_FMA, 0x1090, 0x00EC8000, { 0x0F, 0x38, 0xA6 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.DDS.128.66.0F38.W0 B6 /r VFMADDSUB231PS xmm0,xmm1,xmm2/m128
	// VEX.DDS.256.66.0F38.W0 B6 /r VFMADDSUB231PS ymm0,ymm1,ymm2/m256
	{ "vfmaddsub231ps", FCML_AMT_FMA, 0x1090, 0x00EC8000, { 0x0F, 0x38, 0xB6 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VFMADDSUBPS xmm1, xmm2, xmm3/mem128, xmm4 C4 RXB.00011 0.src.0.01 5C /r /is4
	// VFMADDSUBPS ymm1, ymm2, ymm3/mem256, ymm4 C4 RXB.00011 0.src.1.01 5C /r /is4
	{ "vfmaddsubps", FCML_AMT_FMA4, 0x1090, 0x00EC8000, { 0x0F, 0x3A, 0x5C }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L, FCML_OP_OPERAND_IS4, FCML_NA }, FCML_AM_NONE },
	// VFMADDSUBPS xmm1, xmm2, xmm3, xmm4/mem128 C4 RXB.00011 1.src.0.01 5C /r /is4
	// VFMADDSUBPS ymm1, ymm2, ymm3, ymm4/mem256 C4 RXB.00011 1.src.1.01 5C /r /is4
	{ "vfmaddsubps", FCML_AMT_FMA4, 0x1088, 0x00EC8000, { 0x0F, 0x3A, 0x5C }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_OPERAND_IS4, FCML_OP_MODRM_RM_SIMD_L, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VFMSUBADDPD[] = {
	// VEX.DDS.128.66.0F38.W1 97 /r VFMSUBADD132PD xmm0,xmm1,xmm2/m128
	{ "vfmsubadd132pd", FCML_AMT_FMA, 0x1088, 0x00EC8000, { 0x0F, 0x38, 0x97 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.DDS.128.66.0F38.W1 A7 /r VFMSUBADD213PD xmm0,xmm1,xmm2/m128
	// VEX.DDS.256.66.0F38.W1 A7 /r VFMSUBADD213PD ymm0,ymm1,ymm2/m256
	{ "vfmsubadd213pd", FCML_AMT_FMA, 0x1088, 0x00EC8000, { 0x0F, 0x38, 0xA7 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.DDS.128.66.0F38.W1 B7 /r VFMSUBADD231PD xmm0,xmm1,xmm2/m128
	// VEX.DDS.256.66.0F38.W1 B7 /r VFMSUBADD231PD ymm0,ymm1,ymm2/m256
	{ "vfmsubadd231pd", FCML_AMT_FMA, 0x1088, 0x00EC8000, { 0x0F, 0x38, 0xB7 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VFMSUBADDPD xmm1, xmm2, xmm3/mem128, xmm4 C4 RXB.00011 0.src.0.01 5F /r /is4
	// VFMSUBADDPD ymm1, ymm2, ymm3/mem256, ymm4 C4 RXB.00011 0.src.1.01 5F /r /is4
	{ "vfmsubaddpd", FCML_AMT_FMA4, 0x1090, 0x00EC8000, { 0x0F, 0x3A, 0x5F }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L, FCML_OP_OPERAND_IS4, FCML_NA }, FCML_AM_NONE },
	// VFMSUBADDPD xmm1, xmm2, xmm3, xmm4/mem128 C4 RXB.00011 1.src.0.01 5F /r /is4
	// VFMSUBADDPD ymm1, ymm2, ymm3, ymm4/mem256 C4 RXB.00011 1.src.1.01 5F /r /is4
	{ "vfmsubaddpd", FCML_AMT_FMA4, 0x1088, 0x00EC8000, { 0x0F, 0x3A, 0x5F }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_OPERAND_IS4, FCML_OP_MODRM_RM_SIMD_L, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VFMSUBADDPS[] = {
	// VEX.DDS.128.66.0F38.W0 97 /r VFMSUBADD132PS xmm0,xmm1,xmm2/m128
	// VEX.DDS.256.66.0F38.W0 97 /r VFMSUBADD132PS ymm0,ymm1,ymm2/m256
	{ "vfmsubadd132ps", FCML_AMT_FMA, 0x1090, 0x00EC8000, { 0x0F, 0x38, 0x97 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.DDS.128.66.0F38.W0 A7 /r VFMSUBADD213PS xmm0,xmm1,xmm2/m128
	// VEX.DDS.256.66.0F38.W0 A7 /r VFMSUBADD213PS ymm0,ymm1,ymm2/m256
	{ "vfmsubadd213ps", FCML_AMT_FMA, 0x1090, 0x00EC8000, { 0x0F, 0x38, 0xA7 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.DDS.128.66.0F38.W0 B7 /r VFMSUBADD231PS xmm0,xmm1,xmm2/m128
	// VEX.DDS.256.66.0F38.W0 B7 /r VFMSUBADD231PS ymm0,ymm1,ymm2/m256
	{ "vfmsubadd231ps", FCML_AMT_FMA, 0x1090, 0x00EC8000, { 0x0F, 0x38, 0xB7 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VFMSUBADDPS xmm1, xmm2, xmm3/mem128, xmm4 C4 RXB.00011 0.src.0.01 5E /r /is4
	// VFMSUBADDPS ymm1, ymm2, ymm3/mem256, ymm4 C4 RXB.00011 0.src.1.01 5E /r /is4
	{ "vfmsubaddps", FCML_AMT_FMA4, 0x1090, 0x00EC8000, { 0x0F, 0x3A, 0x5E }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L, FCML_OP_OPERAND_IS4, FCML_NA }, FCML_AM_NONE },
	// VFMSUBADDPS xmm1, xmm2, xmm3, xmm4/mem128 C4 RXB.00011 1.src.0.01 5E /r /is4
	// VFMSUBADDPS ymm1, ymm2, ymm3, ymm4/mem256 C4 RXB.00011 1.src.1.01 5E /r /is4
	{ "vfmsubaddps", FCML_AMT_FMA4, 0x1088, 0x00EC8000, { 0x0F, 0x3A, 0x5E }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_OPERAND_IS4, FCML_OP_MODRM_RM_SIMD_L, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VFMSUBPD[] = {
	// VEX.DDS.128.66.0F38.W1 9A /r VFMSUB132PD xmm0,xmm1,xmm2/m128
	// VEX.DDS.256.66.0F38.W1 9A /r VFMSUB132PD ymm0,ymm1,ymm2/m256
	{ "vfmsub132pd", FCML_AMT_FMA, 0x1088, 0x00EC8000, { 0x0F, 0x38, 0x9A }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.DDS.128.66.0F38.W1 AA /r VFMSUB213PD xmm0,xmm1,xmm2/m128
	// VEX.DDS.256.66.0F38.W1 AA /r VFMSUB213PD ymm0,ymm1,ymm2/m256
	{ "vfmsub213pd", FCML_AMT_FMA, 0x1088, 0x00EC8000, { 0x0F, 0x38, 0xAA }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.DDS.128.66.0F38.W1 BA /r VFMSUB231PD xmm0,xmm1,xmm2/m128
	// VEX.DDS.256.66.0F38.W1 BA /r VFMSUB231PD ymm0,ymm1,ymm2/m256
	{ "vfmsub231pd", FCML_AMT_FMA, 0x1088, 0x00EC8000, { 0x0F, 0x38, 0xBA }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VFMSUBPD xmm1, xmm2, xmm3/mem128, xmm4 C4 RXB.00011 0.src.0.01 6D /r /is4
	// VFMSUBPD ymm1, ymm2, ymm3/mem256, ymm4 C4 RXB.00011 0.src.1.01 6D /r /is4
	{ "vfmsubpd", FCML_AMT_FMA4, 0x1090, 0x00EC8000, { 0x0F, 0x3A, 0x6D }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L, FCML_OP_OPERAND_IS4, FCML_NA }, FCML_AM_NONE },
	// VFMSUBPD xmm1, xmm2, xmm3, xmm4/mem128 C4 RXB.00011 1.src.0.01 6D /r /is4
	// VFMSUBPD ymm1, ymm2, ymm3, ymm4/mem256 C4 RXB.00011 1.src.1.01 6D /r /is4
	{ "vfmsubpd", FCML_AMT_FMA4, 0x1088, 0x00EC8000, { 0x0F, 0x3A, 0x6D }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_OPERAND_IS4, FCML_OP_MODRM_RM_SIMD_L, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VFMSUBPS[] = {
	// VEX.DDS.128.66.0F38.W0 9A /r VFMSUB132PS xmm0,xmm1,xmm2/m128
	// VEX.DDS.256.66.0F38.W0 9A /r VFMSUB132PS ymm0,ymm1,ymm2/m256
	{ "vfmsub132ps", FCML_AMT_FMA, 0x1090, 0x00EC8000, { 0x0F, 0x38, 0x9A }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.DDS.128.66.0F38.W0 AA /r VFMSUB213PS xmm0,xmm1,xmm2/m128
	// VEX.DDS.256.66.0F38.W0 AA /r VFMSUB213PS ymm0,ymm1,ymm2/m256
	{ "vfmsub213ps", FCML_AMT_FMA, 0x1090, 0x00EC8000, { 0x0F, 0x38, 0xAA }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.DDS.128.66.0F38.W0 BA /r VFMSUB231PS xmm0,xmm1,xmm2/m128
	// VEX.DDS.256.66.0F38.W0 BA /r VFMSUB231PS ymm0,ymm1,ymm2/m256
	{ "vfmsub231ps", FCML_AMT_FMA, 0x1090, 0x00EC8000, { 0x0F, 0x38, 0xBA }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VFMSUBPS xmm1, xmm2, xmm3/mem128, xmm4 C4 RXB.00011 0.src.0.01 6C /r /is4
	// VFMSUBPS ymm1, ymm2, ymm3/mem256, ymm4 C4 RXB.00011 0.src.1.01 6C /r /is4
	{ "vfmsubps", FCML_AMT_FMA4, 0x1090, 0x00EC8000, { 0x0F, 0x3A, 0x6C }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L, FCML_OP_OPERAND_IS4, FCML_NA }, FCML_AM_NONE },
	// VFMSUBPS xmm1, xmm2, xmm3, xmm4/mem128 C4 RXB.00011 1.src.0.01 6C /r /is4
	// VFMSUBPS ymm1, ymm2, ymm3, ymm4/mem256 C4 RXB.00011 1.src.1.01 6C /r /is4
	{ "vfmsubps", FCML_AMT_FMA4, 0x1088, 0x00EC8000, { 0x0F, 0x3A, 0x6C }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_OPERAND_IS4, FCML_OP_MODRM_RM_SIMD_L, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VFMSUBSD[] = {
	// VEX.DDS.LIG.128.66.0F38.W1 9B /r VFMSUB132SD xmm0,xmm1,xmm2/m64
	{ "vfmsub132sd", FCML_AMT_FMA, 0x10C8, 0x00EC8000, { 0x0F, 0x38, 0x9B }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_64, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.DDS.LIG.128.66.0F38.W1 AB /r VFMSUB213SD xmm0,xmm1,xmm2/m64
	{ "vfmsub213sd", FCML_AMT_FMA, 0x10C8, 0x00EC8000, { 0x0F, 0x38, 0xAB }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_64, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.DDS.LIG.128.66.0F38.W1 BB /r VFMSUB231SD xmm0,xmm1,xmm2/m64
	{ "vfmsub231sd", FCML_AMT_FMA, 0x10C8, 0x00EC8000, { 0x0F, 0x38, 0xBB }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_64, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VFMSUBSD xmm1, xmm2, xmm3/mem64, xmm4 C4 RXB.00011 0.src.X.01 6F /r /is4
	{ "vfmsubsd", FCML_AMT_FMA4, 0x10D0, 0x00EC8000, { 0x0F, 0x3A, 0x6F }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_64, FCML_OP_OPERAND_IS4, FCML_NA }, FCML_AM_NONE },
	// VFMSUBSD xmm1, xmm2, xmm3, xmm4/mem64 C4 RXB.00011 1.src.X.01 6F /r /is4
	{ "vfmsubsd", FCML_AMT_FMA4, 0x10C8, 0x00EC8000, { 0x0F, 0x3A, 0x6F }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_OPERAND_IS4, FCML_OP_MODRM_RM_XMM_64, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VFMSUBSS[] = {
	// VEX.DDS.LIG.128.66.0F38.W0 9B /r VFMSUB132SS xmm0,xmm1,xmm2/m32
	{ "vfmsub132ss", FCML_AMT_FMA, 0x10D0, 0x00EC8000, { 0x0F, 0x38, 0x9B }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_32, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.DDS.LIG.128.66.0F38.W0 AB /r VFMSUB213SS xmm0,xmm1,xmm2/m32
	{ "vfmsub213ss", FCML_AMT_FMA, 0x10D0, 0x00EC8000, { 0x0F, 0x38, 0xAB }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_32, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.DDS.LIG.128.66.0F38.W0 BB /r VFMSUB231SS xmm0,xmm1,xmm2/m32
	{ "vfmsub231ss", FCML_AMT_FMA, 0x10D0, 0x00EC8000, { 0x0F, 0x38, 0xBB }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_32, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VFMSUBSS xmm1, xmm2, xmm3/mem32, xmm4 C4 RXB.00011 0.src.X.01 6E /r /is4
	{ "vfmsubss", FCML_AMT_FMA4, 0x10D0, 0x00EC8000, { 0x0F, 0x3A, 0x6E }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_32, FCML_OP_OPERAND_IS4, FCML_NA }, FCML_AM_NONE },
	// VFMSUBSS xmm1, xmm2, xmm3, xmm4/mem32 C4 RXB.00011 1.src.X.01 6E /r /is4
	{ "vfmsubss", FCML_AMT_FMA4, 0x10C8, 0x00EC8000, { 0x0F, 0x3A, 0x6E }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_OPERAND_IS4, FCML_OP_MODRM_RM_XMM_32, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VFNMADDPD[] = {
	// VEX.DDS.128.66.0F38.W1 9C /r VFNMADD132PD xmm0,xmm1,xmm2/m128
	// VEX.DDS.256.66.0F38.W1 9C /r VFNMADD132PD ymm0,ymm1,ymm2/m256
	{ "vfnmadd132pd", FCML_AMT_FMA, 0x1088, 0x00EC8000, { 0x0F, 0x38, 0x9C }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.DDS.128.66.0F38.W1 AC /r VFNMADD213PD xmm0,xmm1,xmm2/m128
	// VEX.DDS.256.66.0F38.W1 AC /r VFNMADD213PD ymm0,ymm1,ymm2/m256
	{ "vfnmadd213pd", FCML_AMT_FMA, 0x1088, 0x00EC8000, { 0x0F, 0x38, 0xAC }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.DDS.128.66.0F38.W1 BC /r VFNMADD231PD xmm0,xmm1,xmm2/m128
	// VEX.DDS.256.66.0F38.W1 BC /r VFNMADD231PD ymm0,ymm1,ymm2/m256
	{ "vfnmadd231pd", FCML_AMT_FMA, 0x1088, 0x00EC8000, { 0x0F, 0x38, 0xBC }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VFNMADDPD xmm1, xmm2, xmm3/mem128, xmm4 C4 RXB.00011 0.src.0.01 79 /r /is4
	// VFNMADDPD ymm1, ymm2, ymm3/mem256, ymm4 C4 RXB.00011 0.src.1.01 79 /r /is4
	{ "vfnmaddpd", FCML_AMT_FMA4, 0x1090, 0x00EC8000, { 0x0F, 0x3A, 0x79 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L, FCML_OP_OPERAND_IS4, FCML_NA }, FCML_AM_NONE },
	// VFNMADDPD xmm1, xmm2, xmm3, xmm4/mem128 C4 RXB.00011 1.src.0.01 79 /r /is4
	// VFNMADDPD ymm1, ymm2, ymm3, ymm4/mem256 C4 RXB.00011 1.src.1.01 79 /r /is4
	{ "vfnmaddpd", FCML_AMT_FMA4, 0x1088, 0x00EC8000, { 0x0F, 0x3A, 0x79 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_OPERAND_IS4, FCML_OP_MODRM_RM_SIMD_L, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VFNMADDPS[] = {
	// VEX.DDS.128.66.0F38.W0 9C /r VFNMADD132PS xmm0,xmm1,xmm2/m128
	// VEX.DDS.256.66.0F38.W0 9C /r VFNMADD132PS ymm0,ymm1,ymm2/m256
	{ "vfnmadd132ps", FCML_AMT_FMA, 0x1090, 0x00EC8000, { 0x0F, 0x38, 0x9C }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.DDS.128.66.0F38.W0 AC /r VFNMADD213PS xmm0,xmm1,xmm2/m128
	// VEX.DDS.256.66.0F38.W0 AC /r VFNMADD213PS ymm0,ymm1,ymm2/m256
	{ "vfnmadd213ps", FCML_AMT_FMA, 0x1090, 0x00EC8000, { 0x0F, 0x38, 0xAC }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.DDS.128.66.0F38.W0 BC /r VFNMADD231PS xmm0,xmm1,xmm2/m128
	// VEX.DDS.256.66.0F38.W0 BC /r VFNMADD231PS ymm0,ymm1,ymm2/m256
	{ "vfnmadd231ps", FCML_AMT_FMA, 0x1090, 0x00EC8000, { 0x0F, 0x38, 0xBC }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VFNMADDPS xmm1, xmm2, xmm3/mem128, xmm4 C4 RXB.00011 0.src.0.01 78 /r /is4
	// VFNMADDPS ymm1, ymm2, ymm3/mem256, ymm4 C4 RXB.00011 0.src.1.01 78 /r /is4
	{ "vfnmaddps", FCML_AMT_FMA4, 0x1090, 0x00EC8000, { 0x0F, 0x3A, 0x78 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L, FCML_OP_OPERAND_IS4, FCML_NA }, FCML_AM_NONE },
	// VFNMADDPS xmm1, xmm2, xmm3, xmm4/mem128 C4 RXB.00011 1.src.0.01 78 /r /is4
	// VFNMADDPS ymm1, ymm2, ymm3, ymm4/mem256 C4 RXB.00011 1.src.1.01 78 /r /is4
	{ "vfnmaddps", FCML_AMT_FMA4, 0x1088, 0x00EC8000, { 0x0F, 0x3A, 0x78 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_OPERAND_IS4, FCML_OP_MODRM_RM_SIMD_L, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VFNMADDSD[] = {
	// VEX.DDS.LIG.128.66.0F38.W1 9D /r VFNMADD132SD xmm0,xmm1,xmm2/m64
	{ "vfnmadd132sd", FCML_AMT_FMA, 0x10C8, 0x00EC8000, { 0x0F, 0x38, 0x9D }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_64, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.DDS.LIG.128.66.0F38.W1 AD /r VFNMADD213SD xmm0,xmm1,xmm2/m64
	{ "vfnmadd213sd", FCML_AMT_FMA, 0x10C8, 0x00EC8000, { 0x0F, 0x38, 0xAD }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_64, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.DDS.LIG.128.66.0F38.W1 BD /r VFNMADD231SD xmm0,xmm1,xmm2/m64
	{ "vfnmadd231sd", FCML_AMT_FMA, 0x10C8, 0x00EC8000, { 0x0F, 0x38, 0xBD }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_64, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VFNMADDSD xmm1, xmm2, xmm3/mem64, xmm4 C4 RXB.00011 0.src.X.01 7B /r /is4
	{ "vfnmaddsd", FCML_AMT_FMA4, 0x10D0, 0x00EC8000, { 0x0F, 0x3A, 0x7B }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_64, FCML_OP_OPERAND_IS4, FCML_NA }, FCML_AM_NONE },
	// VFNMADDSD xmm1, xmm2, xmm3, xmm4/mem64 C4 RXB.00011 1.src.X.01 7B /r /is4
	{ "vfnmaddsd", FCML_AMT_FMA4, 0x10C8, 0x00EC8000, { 0x0F, 0x3A, 0x7B }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_OPERAND_IS4, FCML_OP_MODRM_RM_XMM_64, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VFNMADDSS[] = {
	// VEX.DDS.LIG.128.66.0F38.W0 9D /r VFNMADD132SS xmm0,xmm1,xmm2/m32
	{ "vfnmadd132ss", FCML_AMT_FMA, 0x10D0, 0x00EC8000, { 0x0F, 0x38, 0x9D }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_32, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.DDS.LIG.128.66.0F38.W0 AD /r VFNMADD213SS xmm0,xmm1,xmm2/m32
	{ "vfnmadd213ss", FCML_AMT_FMA, 0x10D0, 0x00EC8000, { 0x0F, 0x38, 0xAD }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_32, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.DDS.LIG.128.66.0F38.W0 BD /r VFNMADD231SS xmm0,xmm1,xmm2/m32
	{ "vfnmadd231ss", FCML_AMT_FMA, 0x10D0, 0x00EC8000, { 0x0F, 0x38, 0xBD }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_32, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VFNMADDSS xmm1, xmm2, xmm3/mem32, xmm4 C4 RXB.00011 0.src.X.01 7A /r /is4
	{ "vfnmaddss", FCML_AMT_FMA4, 0x10D0, 0x00EC8000, { 0x0F, 0x3A, 0x7A }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_32, FCML_OP_OPERAND_IS4, FCML_NA }, FCML_AM_NONE },
	// VFNMADDSS xmm1, xmm2, xmm3, xmm4/mem32 C4 RXB.00011 1.src.X.01 7A /r /is4
	{ "vfnmaddss", FCML_AMT_FMA4, 0x10C8, 0x00EC8000, { 0x0F, 0x3A, 0x7A }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_OPERAND_IS4, FCML_OP_MODRM_RM_XMM_32, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VFNMSUBPD[] = {
	// VEX.DDS.128.66.0F38.W1 9E /r VFNMSUB132PD xmm0,xmm1,xmm2/m128
	// VEX.DDS.256.66.0F38.W1 9E /r VFNMSUB132PD ymm0,ymm1,ymm2/m256
	{ "vfnmsub132pd", FCML_AMT_FMA, 0x1088, 0x00EC8000, { 0x0F, 0x38, 0x9E }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.DDS.128.66.0F38.W1 AE /r VFNMSUB213PD xmm0,xmm1,xmm2/m128
	// VEX.DDS.256.66.0F38.W1 AE /r VFNMSUB213PD ymm0,ymm1,ymm2/m256
	{ "vfnmsub213pd", FCML_AMT_FMA, 0x1088, 0x00EC8000, { 0x0F, 0x38, 0xAE }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.DDS.128.66.0F38.W1 BE /r VFNMSUB231PD xmm0,xmm1,xmm2/m128
	// VEX.DDS.256.66.0F38.W1 BE /r VFNMSUB231PD ymm0,ymm1,ymm2/m256
	{ "vfnmsub231pd", FCML_AMT_FMA, 0x1088, 0x00EC8000, { 0x0F, 0x38, 0xBE }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VFNMSUBPD xmm1, xmm2, xmm3/mem128, xmm4 C4 RXB.00011 0.src.0.01 7D /r /is4
	// VFNMSUBPD ymm1, ymm2, ymm3/mem256, ymm4 C4 RXB.00011 0.src.1.01 7D /r /is4
	{ "vfnmsubpd", FCML_AMT_FMA4, 0x1090, 0x00EC8000, { 0x0F, 0x3A, 0x7D }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L, FCML_OP_OPERAND_IS4, FCML_NA }, FCML_AM_NONE },
	// VFNMSUBPD xmm1, xmm2, xmm3, xmm4/mem128 C4 RXB.00011 1.src.0.01 7D /r /is4
	// VFNMSUBPD ymm1, ymm2, ymm3, ymm4/mem256 C4 RXB.00011 1.src.1.01 7D /r /is4
	{ "vfnmsubpd", FCML_AMT_FMA4, 0x1088, 0x00EC8000, { 0x0F, 0x3A, 0x7D }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_OPERAND_IS4, FCML_OP_MODRM_RM_SIMD_L, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VFNMSUBPS[] = {
	// VEX.DDS.128.66.0F38.W0 9E /r VFNMSUB132PS xmm0,xmm1,xmm2/m128
	// VEX.DDS.256.66.0F38.W0 9E /r VFNMSUB132PS ymm0,ymm1,ymm2/m256
	{ "vfnmsub132ps", FCML_AMT_FMA, 0x1090, 0x00EC8000, { 0x0F, 0x38, 0x9E }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.DDS.128.66.0F38.W0 AE /r VFNMSUB213PS xmm0,xmm1,xmm2/m128
	// VEX.DDS.256.66.0F38.W0 AE /r VFNMSUB213PS ymm0,ymm1,ymm2/m256
	{ "vfnmsub213ps", FCML_AMT_FMA, 0x1090, 0x00EC8000, { 0x0F, 0x38, 0xAE }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.DDS.128.66.0F38.W0 BE /r VFNMSUB231PS xmm0,xmm1,xmm2/m128
	// VEX.DDS.256.66.0F38.W0 BE /r VFNMSUB231PS ymm0,ymm1,ymm2/m256
	{ "vfnmsub231ps", FCML_AMT_FMA, 0x1090, 0x00EC8000, { 0x0F, 0x38, 0xBE }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VFNMSUBPS xmm1, xmm2, xmm3/mem128, xmm4 C4 RXB.00011 0.src.0.01 7C /r /is4
	// VFNMSUBPS ymm1, ymm2, ymm3/mem256, ymm4 C4 RXB.00011 0.src.1.01 7C /r /is4
	{ "vfnmsubps", FCML_AMT_FMA4, 0x1090, 0x00EC8000, { 0x0F, 0x3A, 0x7C }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L, FCML_OP_OPERAND_IS4, FCML_NA }, FCML_AM_NONE },
	// VFNMSUBPS xmm1, xmm2, xmm3, xmm4/mem128 C4 RXB.00011 1.src.0.01 7C /r /is4
	// VFNMSUBPS ymm1, ymm2, ymm3, ymm4/mem256 C4 RXB.00011 1.src.1.01 7C /r /is4
	{ "vfnmsubps", FCML_AMT_FMA4, 0x1088, 0x00EC8000, { 0x0F, 0x3A, 0x7C }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_OPERAND_IS4, FCML_OP_MODRM_RM_SIMD_L, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VFNMSUBSD[] = {
	// VEX.DDS.LIG.128.66.0F38.W1 9F /r VFNMSUB132SD xmm0,xmm1,xmm2/m64
	{ "vfnmsub132sd", FCML_AMT_FMA, 0x10C8, 0x00EC8000, { 0x0F, 0x38, 0x9F }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_64, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.DDS.LIG.128.66.0F38.W1 AF /r VFNMSUB213SD xmm0,xmm1,xmm2/m64
	{ "vfnmsub213sd", FCML_AMT_FMA, 0x10C8, 0x00EC8000, { 0x0F, 0x38, 0xAF }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_64, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.DDS.LIG.128.66.0F38.W1 BF /r VFNMSUB231SD xmm0,xmm1,xmm2/m64
	{ "vfnmsub231sd", FCML_AMT_FMA, 0x10C8, 0x00EC8000, { 0x0F, 0x38, 0xBF }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_64, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VFNMSUBSD xmm1, xmm2, xmm3/mem64, xmm4 C4 RXB.00011 0.src.X.01 7F /r /is4
	{ "vfnmsubsd", FCML_AMT_FMA4, 0x10D0, 0x00EC8000, { 0x0F, 0x3A, 0x7F }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_64, FCML_OP_OPERAND_IS4, FCML_NA }, FCML_AM_NONE },
	// VFNMSUBSD xmm1, xmm2, xmm3, xmm4/mem64 C4 RXB.00011 1.src.X.01 7F /r /is4
	{ "vfnmsubsd", FCML_AMT_FMA4, 0x10C8, 0x00EC8000, { 0x0F, 0x3A, 0x7F }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_OPERAND_IS4, FCML_OP_MODRM_RM_XMM_64, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VFNMSUBSS[] = {
	// VEX.DDS.LIG.128.66.0F38.W0 9F /r VFNMSUB132SS xmm0,xmm1,xmm2/m32
	{ "vfnmsub132ss", FCML_AMT_FMA, 0x10D0, 0x00EC8000, { 0x0F, 0x38, 0x9F }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_32, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.DDS.LIG.128.66.0F38.W0 AF /r VFNMSUB213SS xmm0,xmm1,xmm2/m32
	{ "vfnmsub213ss", FCML_AMT_FMA, 0x10D0, 0x00EC8000, { 0x0F, 0x38, 0xAF }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_32, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.DDS.LIG.128.66.0F38.W0 BF /r VFNMSUB231SS xmm0,xmm1,xmm2/m32
	{ "vfnmsub231ss", FCML_AMT_FMA, 0x10D0, 0x00EC8000, { 0x0F, 0x38, 0xBF }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_32, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VFNMSUBSS xmm1, xmm2, xmm3/mem32, xmm4 C4 RXB.00011 0.src.X.01 7E /r /is4
	{ "vfnmsubss", FCML_AMT_FMA4, 0x10D0, 0x00EC8000, { 0x0F, 0x3A, 0x7E }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_32, FCML_OP_OPERAND_IS4, FCML_NA }, FCML_AM_NONE },
	// VFNMSUBSS xmm1, xmm2, xmm3, xmm4/mem32 C4 RXB.00011 1.src.X.01 7E /r /is4
	{ "vfnmsubss", FCML_AMT_FMA4, 0x10C8, 0x00EC8000, { 0x0F, 0x3A, 0x7E }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_OPERAND_IS4, FCML_OP_MODRM_RM_XMM_32, FCML_NA }, FCML_AM_NONE }
};

/* END OF FAM */

/* VEX-Encoded GPR instructions. */

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_ANDN[] = {
	// VEX.NDS.LZ.0F38.W0 F2 /r ANDN r32a, r32b, r/m32
	{ NULL, FCML_AMT_BMI1 | FCML_AMT_VEXx, 0x02D0, 0x00EC8000, { 0x0F, 0x38, 0xF2 }, { FCML_OP_MODRM_R_32_W, FCML_OP_VEX_VVVV_REG( FCML_REG_GPR, FCML_EOS_DWORD ), FCML_OP_MODRM_RM_32, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.LZ.0F38.W1 F2 /r ANDN r64a, r64b, r/m64
	{ NULL, FCML_AMT_BMI1 | FCML_AMT_VEXx, 0x02C8, 0x00EC8000, { 0x0F, 0x38, 0xF2 }, { FCML_OP_MODRM_R_64_W, FCML_OP_VEX_VVVV_REG( FCML_REG_GPR, FCML_EOS_QWORD ), FCML_OP_MODRM_RM_64, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_BEXR[] = {
	// VEX.NDS1.LZ.0F38.W0 F7 /r BEXR r32a, r/m32, r32b
	{ NULL, FCML_AMT_BMI1 | FCML_AMT_VEXx, 0x02D0, 0x00EC8000, { 0x0F, 0x38, 0xF7 }, { FCML_OP_MODRM_R_32_W, FCML_OP_MODRM_RM_32, FCML_OP_VEX_VVVV_REG( FCML_REG_GPR, FCML_EOS_DWORD ), FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS1.LZ.0F38.W1 F7 /r BEXR r64a, r/m64, r64b
	{ NULL, FCML_AMT_BMI1 | FCML_AMT_VEXx, 0x02C8, 0x00EC8000, { 0x0F, 0x38, 0xF7 }, { FCML_OP_MODRM_R_64_W, FCML_OP_MODRM_RM_64, FCML_OP_VEX_VVVV_REG( FCML_REG_GPR, FCML_EOS_QWORD ), FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_BEXTR[] = {
	// BEXTR reg32, reg/mem32, imm32 8F RXB.0A 0.1111.0.00 10 /r /id
	{ NULL, FCML_AMT_BMI1 | FCML_AMT_VEXx, 0x0550, 0x00D88000, { 0x0A, 0x10, 0x00 }, { FCML_OP_MODRM_R_32_W, FCML_OP_MODRM_RM_32, FCML_OP_ID, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// BEXTR reg64, reg/mem64, imm32 8F RXB.0A 1.1111.0.00 10 /r /id
	{ NULL, FCML_AMT_BMI1 | FCML_AMT_VEXx, 0x0548, 0x00D88000, { 0x0A, 0x10, 0x00 }, { FCML_OP_MODRM_R_64_W, FCML_OP_MODRM_RM_64, FCML_OP_ID, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_BLCFILL[] = {
	// BLCFILL reg32, reg/mem32 8F RXB.09 0.dest.0.00 01 /1
	{ NULL, FCML_AMT_TBM, 0x0450, 0x00D98800, { 0x09, 0x01, 0x00 }, { FCML_OP_VEX_VVVV_REG( FCML_REG_GPR, FCML_EOS_DWORD ) | FCML_OA_W, FCML_OP_MODRM_RM_32, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// BLCFILL reg64, reg/mem64 8F RXB.09 1.dest.0.00 01 /1
	{ NULL, FCML_AMT_TBM, 0x0448, 0x00D98800, { 0x09, 0x01, 0x00 }, { FCML_OP_VEX_VVVV_REG( FCML_REG_GPR, FCML_EOS_QWORD ) | FCML_OA_W, FCML_OP_MODRM_RM_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_BLCI[] = {
	// BLCI reg32, reg/mem32 8F RXB.09 0.dest.0.00 02 /6
	{ NULL, FCML_AMT_TBM, 0x0450, 0x00D9B000, { 0x09, 0x02, 0x00 }, { FCML_OP_VEX_VVVV_REG( FCML_REG_GPR, FCML_EOS_DWORD ) | FCML_OA_W, FCML_OP_MODRM_RM_32, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// BLCI reg64, reg/mem64 8F RXB.09 1.dest.0.00 02 /6
	{ NULL, FCML_AMT_TBM, 0x0448, 0x00D9B000, { 0x09, 0x02, 0x00 }, { FCML_OP_VEX_VVVV_REG( FCML_REG_GPR, FCML_EOS_QWORD ) | FCML_OA_W, FCML_OP_MODRM_RM_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_BLCIC[] = {
	// BLCIC reg32, reg/mem32 8F RXB.09 0.dest.0.00 01 /5
	{ NULL, FCML_AMT_TBM, 0x0450, 0x00D9A800, { 0x09, 0x01, 0x00 }, { FCML_OP_VEX_VVVV_REG( FCML_REG_GPR, FCML_EOS_DWORD ) | FCML_OA_W, FCML_OP_MODRM_RM_32, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// BLCIC reg64, reg/mem64 8F RXB.09 1.dest.0.00 01 /5
	{ NULL, FCML_AMT_TBM, 0x0448, 0x00D9A800, { 0x09, 0x01, 0x00 }, { FCML_OP_VEX_VVVV_REG( FCML_REG_GPR, FCML_EOS_QWORD ) | FCML_OA_W, FCML_OP_MODRM_RM_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_BLCMSK[] = {
	// BLCMSK reg32, reg/mem32 8F RXB.09 0.dest.0.00 02 /1
	{ NULL, FCML_AMT_TBM, 0x0450, 0x00D98800, { 0x09, 0x02, 0x00 }, { FCML_OP_VEX_VVVV_REG( FCML_REG_GPR, FCML_EOS_DWORD ) | FCML_OA_W, FCML_OP_MODRM_RM_32, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// BLCMSK reg64, reg/mem64 8F RXB.09 1.dest.0.00 02 /1
	{ NULL, FCML_AMT_TBM, 0x0448, 0x00D98800, { 0x09, 0x02, 0x00 }, { FCML_OP_VEX_VVVV_REG( FCML_REG_GPR, FCML_EOS_QWORD ) | FCML_OA_W, FCML_OP_MODRM_RM_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_BLCS[] = {
	// BLCS reg32, reg/mem32 8F RXB.09 0.dest.0.00 01 /3
	{ NULL, FCML_AMT_TBM, 0x0450, 0x00D99800, { 0x09, 0x01, 0x00 }, { FCML_OP_VEX_VVVV_REG( FCML_REG_GPR, FCML_EOS_DWORD ) | FCML_OA_W, FCML_OP_MODRM_RM_32, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// BLCS reg64, reg/mem64 8F RXB.09 1.dest.0.00 01 /3
	{ NULL, FCML_AMT_TBM, 0x0448, 0x00D99800, { 0x09, 0x01, 0x00 }, { FCML_OP_VEX_VVVV_REG( FCML_REG_GPR, FCML_EOS_QWORD ) | FCML_OA_W, FCML_OP_MODRM_RM_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_BLSFILL[] = {
	// BLSFILL reg32, reg/mem32 8F RXB.09 0.dest.0.00 01 /2
	{ NULL, FCML_AMT_TBM, 0x0450, 0x00D99000, { 0x09, 0x01, 0x00 }, { FCML_OP_VEX_VVVV_REG( FCML_REG_GPR, FCML_EOS_DWORD ) | FCML_OA_W, FCML_OP_MODRM_RM_32, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// BLSFILL reg64, reg/mem64 8F RXB.09 1.dest.0.00 01 /2
	{ NULL, FCML_AMT_TBM, 0x0448, 0x00D99000, { 0x09, 0x01, 0x00 }, { FCML_OP_VEX_VVVV_REG( FCML_REG_GPR, FCML_EOS_QWORD ) | FCML_OA_W, FCML_OP_MODRM_RM_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_BLSI[] = {
	// VEX.NDD.LZ.0F38.W0 F3 /3 BLSI r32, r/m32
	{ NULL, FCML_AMT_BMI1 | FCML_AMT_VEXx, 0x02D0, 0x00ED9800, { 0x0F, 0x38, 0xF3 }, { FCML_OP_VEX_VVVV_REG( FCML_REG_GPR, FCML_EOS_DWORD ) | FCML_OA_W, FCML_OP_MODRM_RM_32, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDD.LZ.0F38.W1 F3 /3 BLSI r64, r/m64
	{ NULL, FCML_AMT_BMI1 | FCML_AMT_VEXx, 0x02C8, 0x00ED9800, { 0x0F, 0x38, 0xF3 }, { FCML_OP_VEX_VVVV_REG( FCML_REG_GPR, FCML_EOS_QWORD ) | FCML_OA_W, FCML_OP_MODRM_RM_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_BLSIC[] = {
	// BLSIC reg32, reg/mem32 8F RXB.09 0.dest.0.00 01 /6
	{ NULL, FCML_AMT_TBM, 0x0450, 0x00D9B000, { 0x09, 0x01, 0x00 }, { FCML_OP_VEX_VVVV_REG( FCML_REG_GPR, FCML_EOS_DWORD ) | FCML_OA_W, FCML_OP_MODRM_RM_32, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// BLSIC reg64, reg/mem64 8F RXB.09 1.dest.0.00 01 /6
	{ NULL, FCML_AMT_TBM, 0x0448, 0x00D9B000, { 0x09, 0x01, 0x00 }, { FCML_OP_VEX_VVVV_REG( FCML_REG_GPR, FCML_EOS_QWORD ) | FCML_OA_W, FCML_OP_MODRM_RM_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_BLSMSK[] = {
	// VEX.NDD.LZ.0F38.W0 F3 /2 BLSMSK r32, r/m32
	{ NULL, FCML_AMT_BMI1 | FCML_AMT_VEXx, 0x02D0, 0x00ED9000, { 0x0F, 0x38, 0xF3 }, { FCML_OP_VEX_VVVV_REG( FCML_REG_GPR, FCML_EOS_DWORD ) | FCML_OA_W, FCML_OP_MODRM_RM_32, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDD.LZ.0F38.W1 F3 /2 BLSMSK r64, r/m64
	{ NULL, FCML_AMT_BMI1 | FCML_AMT_VEXx, 0x02C8, 0x00ED9000, { 0x0F, 0x38, 0xF3 }, { FCML_OP_VEX_VVVV_REG( FCML_REG_GPR, FCML_EOS_QWORD ) | FCML_OA_W, FCML_OP_MODRM_RM_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_BLSR[] = {
	// VEX.NDD.LZ.0F38.W0 F3 /1 BLSR r32, r/m32
	{ NULL, FCML_AMT_BMI1 | FCML_AMT_VEXx, 0x02D0, 0x00ED8800, { 0x0F, 0x38, 0xF3 }, { FCML_OP_VEX_VVVV_REG( FCML_REG_GPR, FCML_EOS_DWORD ) | FCML_OA_W, FCML_OP_MODRM_RM_32, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDD.LZ.0F38.W1 F3 /1 BLSR r64, r/m64
	{ NULL, FCML_AMT_BMI1 | FCML_AMT_VEXx, 0x02C8, 0x00ED8800, { 0x0F, 0x38, 0xF3 }, { FCML_OP_VEX_VVVV_REG( FCML_REG_GPR, FCML_EOS_QWORD ) | FCML_OA_W, FCML_OP_MODRM_RM_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_BZHI[] = {
	// VEX.NDS1.LZ.0F38.W0 F5 /r BZHI r32a, r/m32, r32b
	{ NULL, FCML_AMT_BMI1 | FCML_AMT_VEXx, 0x02D0, 0x00EC8000, { 0x0F, 0x38, 0xF5 }, { FCML_OP_MODRM_R_32_W, FCML_OP_MODRM_RM_32, FCML_OP_VEX_VVVV_REG( FCML_REG_GPR, FCML_EOS_DWORD ), FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS1.LZ.0F38.W1 F5 /r BZHI r64a, r/m64, r64b
	{ NULL, FCML_AMT_BMI1 | FCML_AMT_VEXx, 0x02C8, 0x00EC8000, { 0x0F, 0x38, 0xF5 }, { FCML_OP_MODRM_R_64_W, FCML_OP_MODRM_RM_64, FCML_OP_VEX_VVVV_REG( FCML_REG_GPR, FCML_EOS_QWORD ), FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_LZCNT[] = {
	// F3 0F BD /r LZCNT r16,r/m16
	// F3 0F BD /r LZCNT r32,r/m32
	// REX.W + F3 0F BD /r LZCNT r64,r/m64
	{ NULL, FCML_AMT_ABM, 0x4000, 0x00D88000, { 0x0F, 0xBD, 0x00 }, { FCML_OP_MODRM_R_W, FCML_OP_MODRM_RM, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_MULX[] = {
	// VEX.NDD.LZ.F2.0F38.W0 F6 /r MULX r32a, r32b, r/m32
	{ NULL, FCML_AMT_BMI1 | FCML_AMT_VEXx, 0x22D0, 0x00EC8000, { 0x0F, 0x38, 0xF6 }, { FCML_OP_MODRM_R_32_W, FCML_OP_VEX_VVVV_REG( FCML_REG_GPR, FCML_EOS_DWORD ), FCML_OP_MODRM_RM_32, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDD.LZ.F2.0F38.W1 F6 /r MULX r64a, r64b, r/m64
	{ NULL, FCML_AMT_BMI1 | FCML_AMT_VEXx, 0x22C8, 0x00EC8000, { 0x0F, 0x38, 0xF6 }, { FCML_OP_MODRM_R_64_W, FCML_OP_VEX_VVVV_REG( FCML_REG_GPR, FCML_EOS_QWORD ), FCML_OP_MODRM_RM_64, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PDEP[] = {
	// VEX.NDS.LZ.F2.0F38.W0 F5 /r PDEP r32a, r32b, r/m32
	{ NULL, FCML_AMT_BMI1 | FCML_AMT_VEXx, 0x22D0, 0x00EC8000, { 0x0F, 0x38, 0xF5 }, { FCML_OP_MODRM_R_32_W, FCML_OP_VEX_VVVV_REG( FCML_REG_GPR, FCML_EOS_DWORD ), FCML_OP_MODRM_RM_32, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.LZ.F2.0F38.W1 F5 /r PDEP r64a, r64b, r/m64
	{ NULL, FCML_AMT_BMI1 | FCML_AMT_VEXx, 0x22C8, 0x00EC8000, { 0x0F, 0x38, 0xF5 }, { FCML_OP_MODRM_R_64_W, FCML_OP_VEX_VVVV_REG( FCML_REG_GPR, FCML_EOS_QWORD ), FCML_OP_MODRM_RM_64, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PEXT[] = {
	// VEX.NDS.LZ.F3.0F38.W0 F5 /r PEXT r32a, r32b, r/m32
	{ NULL, FCML_AMT_BMI1 | FCML_AMT_VEXx, 0x42D0, 0x00EC8000, { 0x0F, 0x38, 0xF5 }, { FCML_OP_MODRM_R_32_W, FCML_OP_VEX_VVVV_REG( FCML_REG_GPR, FCML_EOS_DWORD ), FCML_OP_MODRM_RM_32, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS.LZ.F3.0F38.W1 F5 /r PEXT r64a, r64b, r/m64
	{ NULL, FCML_AMT_BMI1 | FCML_AMT_VEXx, 0x42C8, 0x00EC8000, { 0x0F, 0x38, 0xF5 }, { FCML_OP_MODRM_R_64_W, FCML_OP_VEX_VVVV_REG( FCML_REG_GPR, FCML_EOS_QWORD ), FCML_OP_MODRM_RM_64, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_RORX[] = {
	// VEX.LZ.F2.0F3A.W0 F0 /r ib RORX r32, r/m32, imm8
	{ NULL, FCML_AMT_BMI1 | FCML_AMT_VEXx, 0x22D0, 0x00EC8000, { 0x0F, 0x38, 0xF0 }, { FCML_OP_MODRM_R_32_W, FCML_OP_MODRM_RM_32, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.LZ.F2.0F3A.W1 F0 /r ib RORX r64, r/m64, imm8
	{ NULL, FCML_AMT_BMI1 | FCML_AMT_VEXx, 0x22C8, 0x00EC8000, { 0x0F, 0x38, 0xF0 }, { FCML_OP_MODRM_R_64_W, FCML_OP_MODRM_RM_64, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_SHLX[] = {
	// VEX.NDS1.LZ.66.0F38.W0 F7 /r SHLX r32a, r/m32, r32b
	{ NULL, FCML_AMT_GPI, 0x12D0, 0x00EC8000, { 0x0F, 0x38, 0xF7 }, { FCML_OP_MODRM_R_32_W, FCML_OP_MODRM_RM_32, FCML_OP_VEX_VVVV_REG( FCML_REG_GPR, FCML_EOS_DWORD ), FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS1.LZ.66.0F38.W1 F7 /r SHLX r64a, r/m64, r64b
	{ NULL, FCML_AMT_GPI, 0x12C8, 0x00EC8000, { 0x0F, 0x38, 0xF7 }, { FCML_OP_MODRM_R_64_W, FCML_OP_MODRM_RM_64, FCML_OP_VEX_VVVV_REG( FCML_REG_GPR, FCML_EOS_QWORD ), FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_SHRX[] = {
	// VEX.NDS1.LZ.F2.0F38.W0 F7 /r SHRX r32a, r/m32, r32b
	{ NULL, FCML_AMT_BMI1 | FCML_AMT_VEXx, 0x22D0, 0x00EC8000, { 0x0F, 0x38, 0xF7 }, { FCML_OP_MODRM_R_32_W, FCML_OP_MODRM_RM_32, FCML_OP_VEX_VVVV_REG( FCML_REG_GPR, FCML_EOS_DWORD ), FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS1.LZ.F2.0F38.W1 F7 /r SHRX r64a, r/m64, r64b
	{ NULL, FCML_AMT_BMI1 | FCML_AMT_VEXx, 0x22C8, 0x00EC8000, { 0x0F, 0x38, 0xF7 }, { FCML_OP_MODRM_R_64_W, FCML_OP_MODRM_RM_64, FCML_OP_VEX_VVVV_REG( FCML_REG_GPR, FCML_EOS_QWORD ), FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_SARX[] = {
	// VEX.NDS1.LZ.F3.0F38.W0 F7 /r SARX r32a, r/m32, r32b
	{ NULL, FCML_AMT_BMI1 | FCML_AMT_VEXx, 0x42D0, 0x00EC8000, { 0x0F, 0x38, 0xF7 }, { FCML_OP_MODRM_R_32_W, FCML_OP_MODRM_RM_32, FCML_OP_VEX_VVVV_REG( FCML_REG_GPR, FCML_EOS_DWORD ), FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VEX.NDS1.LZ.F3.0F38.W1 F7 /r SARX r64a, r/m64, r64b
	{ NULL, FCML_AMT_BMI1 | FCML_AMT_VEXx, 0x42C8, 0x00EC8000, { 0x0F, 0x38, 0xF7 }, { FCML_OP_MODRM_R_64_W, FCML_OP_MODRM_RM_64, FCML_OP_VEX_VVVV_REG( FCML_REG_GPR, FCML_EOS_QWORD ), FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_TZCNT[] = {
	// F3 0F BC /r TZCNT r16, r/m16
	// F3 0F BC /r TZCNT r32, r/m32
	// REX.W + F3 0F BC /r TZCNT r64, r/m64
	{ NULL, FCML_AMT_BMI1, 0x4000, 0x00D88000, { 0x0F, 0xBC, 0x00 }, { FCML_OP_MODRM_R_W, FCML_OP_MODRM_RM, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_TZMSK[] = {
	// TZMSK reg32, reg/mem32 8F RXB.09 0.dest.0.00 01 /4
	{ NULL, FCML_AMT_TBM, 0x0450, 0x00D9A000, { 0x09, 0x01, 0x00 }, { FCML_OP_VEX_VVVV_REG( FCML_REG_GPR, FCML_EOS_DWORD ) | FCML_OA_W, FCML_OP_MODRM_RM_32, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// TZMSK reg64, reg/mem64 8F RXB.09 1.dest.0.00 01 /4
	{ NULL, FCML_AMT_TBM, 0x0448, 0x00D9A000, { 0x09, 0x01, 0x00 }, { FCML_OP_VEX_VVVV_REG( FCML_REG_GPR, FCML_EOS_QWORD ) | FCML_OA_W, FCML_OP_MODRM_RM_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

/* END OF VEX-GPR */

/* HLE */

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_XABORT[] = {
	// C6 F8 ib XABORT imm8
	{ NULL, FCML_AMT_HLE, 0x0000, 0x00D80000, { 0xC6, 0xF8, 0x00 }, { FCML_OP_IB, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_XBEGIN[] = {
	// C7 F8 XBEGIN rel16
	// C7 F8 XBEGIN rel32
	{ NULL, FCML_AMT_HLE, 0x0000, 0x40D80000, { 0xC7, 0xF8, 0x00 }, { FCML_OP_IMMEDIATE_DIS_RELATIVE_EOSA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_XEND[] = {
	// 0F 01 D5 XEND
	{ NULL, FCML_AMT_HLE, 0x0000, 0x00EC0000, { 0x0F, 0x01, 0xD5 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_XTEST[] = {
	// 0F 01 D6 XTEST
	{ NULL, FCML_AMT_HLE, 0x0000, 0x00EC0000, { 0x0F, 0x01, 0xD6 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

/* END OF HLE */

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_ADCX[] = {
	// 66 0F 38 F6 /r ADCX r32, r/m32
	{ NULL, FCML_AMT_ADX, 0x1010, 0x00EC8000, { 0x0F, 0x38, 0xF6 }, { FCML_OP_MODRM_R_32_W, FCML_OP_MODRM_RM_32, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// REX.W + 66 0F 38 F6 /r ADCX r64, r/m64
	{ NULL, FCML_AMT_ADX, 0x1008, 0x00EC8000, { 0x0F, 0x38, 0xF6 }, { FCML_OP_MODRM_R_64_W, FCML_OP_MODRM_RM_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_ADOX[] = {
	// F3 0F 38 F6 /r ADOX r32, r/m32
	{ NULL, FCML_AMT_ADX, 0x4010, 0x00EC8000, { 0x0F, 0x38, 0xF6 }, { FCML_OP_MODRM_R_32_W, FCML_OP_MODRM_RM_32, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// REX.w + F3 0F 38 F6 /r ADOX r64, r/m64
	{ NULL, FCML_AMT_ADX, 0x4008, 0x00EC8000, { 0x0F, 0x38, 0xF6 }, { FCML_OP_MODRM_R_64_W, FCML_OP_MODRM_RM_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_RDSEED[] = {
	// 0F C7 /7 RDSEED r16
	// 0F C7 /7 RDSEED r32
	// REX.W + 0F C7 /7 RDSEED r64
	{ NULL, FCML_AMT_RDSEED, 0x0000, 0x00DBB800, { 0x0F, 0xC7, 0x00 }, { FCML_OP_RM( FCML_REG_GPR, FCML_EOS_EOSA, FCML_EOS_UNDEFINED, FCML_RMF_R ) | FCML_OA_W, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE },
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_CLAC[] = {
	// 0F 01 CA CLAC
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00EC0000, { 0x0F, 0x01, 0xCA }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_STAC[] = {
	// 0F 01 CB STAC
	{ NULL, FCML_AMT_GPI, 0x0000, 0x00EC0000, { 0x0F, 0x01, 0xCB }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

// XOP

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VFRCZPD[] = {
	// VFRCZPD xmm1, xmm2/mem128 8F RXB.01001 0.1111.0.00 81 /r
	// VFRCZPD ymm1, ymm2/mem256 8F RXB.01001 0.1111.1.00 81 /r
	{ NULL, FCML_AMT_XOP, 0x0510, 0x00D88000, { 0x09, 0x81, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_MODRM_RM_SIMD_L, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VFRCZPS[] = {
	// VFRCZPS xmm1, xmm2/mem128 8F RXB.01001 0.1111.0.00 80 /r
	// VFRCZPS ymm1, ymm2/mem256 8F RXB.01001 0.1111.1.00 80 /r
	{ NULL, FCML_AMT_XOP, 0x0510, 0x00D88000, { 0x09, 0x80, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_MODRM_RM_SIMD_L, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VFRCZSD[] = {
	// VFRCZSD xmm1,xmm2/mem64 8F RXB.01001 0.1111.0.00 83 /r
	{ NULL, FCML_AMT_XOP, 0x0550, 0x00D88000, { 0x09, 0x83, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VFRCZSS[] = {
	// VFRCZSS xmm1, xmm2/mem32 8F RXB.01001 0.1111.0.00 82 /r
	{ NULL, FCML_AMT_XOP, 0x0550, 0x00D88000, { 0x09, 0x82, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_32, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPCMOV[] = {
	// VPCMOV xmm1, xmm2, xmm3/mem128, xmm4 8F RXB.01000 0.src.0.00 A2 /r ib
	// VPCMOV ymm1, ymm2, ymm3/mem256, ymm4 8F RXB.01000 0.src.1.00 A2 /r ib
	{ NULL, FCML_AMT_XOP, 0x0410, 0x00D88000, { 0x08, 0xA2, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L, FCML_OP_OPERAND_IS4, FCML_NA }, FCML_AM_NONE },
	// VPCMOV xmm1, xmm2, xmm3, xmm4/mem128 8F RXB.01000 1.src.0.00 A2 /r ib
	// VPCMOV ymm1, ymm2, ymm3, ymm4/mem256 8F RXB.01000 1.src.1.00 A2 /r ib
	{ NULL, FCML_AMT_XOP, 0x0408, 0x00D88000, { 0x08, 0xA2, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_OPERAND_IS4, FCML_OP_MODRM_RM_SIMD_L, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPCOM[] = {
	// VPCOMB xmm1, xmm2, xmm3/mem128, imm8 8F RXB.01000 0.src.0.00 CC /r ib
	{ "vpcomb;vpcomltb[p00];vpcomleb[p01];vpcomgtb[p02];vpcomgeb[p03];vpcomeqb[p04];vpcomneqb[p05];vpcomfalseb[p06];vpcomtrueb[p07]", FCML_AMT_XOP, 0x0450, 0x00D88000, { 0x08, 0xCC, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_128, FCML_OP_PSEUDO_OP( 0x07 ), FCML_NA }, FCML_AM_NONE },
	// VPCOMW xmm1, xmm2, xmm3/mem128, imm8 8F RXB.01000 0.src.0.00 CD /r ib
	{ "vpcomw;vpcomltw[p00];vpcomlew[p01];vpcomgtw[p02];vpcomgew[p03];vpcomeqw[p04];vpcomneqw[p05];vpcomfalsew[p06];vpcomtruew[p07]", FCML_AMT_XOP, 0x0450, 0x00D88000, { 0x08, 0xCD, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_128, FCML_OP_PSEUDO_OP( 0x07 ), FCML_NA }, FCML_AM_NONE },
	// VPCOMD xmm1, xmm2, xmm3/mem128, imm8 8F RXB.01000 0.src.0.00 CE /r ib
	{ "vpcomd;vpcomltd[p00];vpcomled[p01];vpcomgtd[p02];vpcomged[p03];vpcomeqd[p04];vpcomneqd[p05];vpcomfalsed[p06];vpcomtrued[p07]", FCML_AMT_XOP, 0x0450, 0x00D88000, { 0x08, 0xCE, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_128, FCML_OP_PSEUDO_OP( 0x07 ), FCML_NA }, FCML_AM_NONE },
	// VPCOMQ xmm1, xmm2, xmm3/mem128, imm8 8F RXB.01000 0.src.0.00 CF /r ib
	{ "vpcomq;vpcomltq[p00];vpcomleq[p01];vpcomgtq[p02];vpcomgeq[p03];vpcomeqq[p04];vpcomneqq[p05];vpcomfalseq[p06];vpcomtrueq[p07]", FCML_AMT_XOP, 0x0450, 0x00D88000, { 0x08, 0xCF, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_128, FCML_OP_PSEUDO_OP( 0x07 ), FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPCOMU[] = {
	// VPCOMUB xmm1, xmm2, xmm3/mem128, imm8 8F RXB.01000 0.src.0.00 EC /r ib
	{ "vpcomub;vpcomltub[p00];vpcomleub[p01];vpcomgtub[p02];vpcomgeub[p03];vpcomequb[p04];vpcomnequb[p05];vpcomfalseub[p06];vpcomtrueub[p07]", FCML_AMT_XOP, 0x0450, 0x00D88000, { 0x08, 0xEC, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_128, FCML_OP_PSEUDO_OP( 0x07 ), FCML_NA }, FCML_AM_NONE },
	// VPCOMUW xmm1, xmm2, xmm3/mem128, imm8 8F RXB.01000 0.src.0.00 ED /r ib
	{ "vpcomuw;vpcomltuw[p00];vpcomleuw[p01];vpcomgtuw[p02];vpcomgeuw[p03];vpcomequw[p04];vpcomnequw[p05];vpcomfalseuw[p06];vpcomtrueuw[p07]", FCML_AMT_XOP, 0x0450, 0x00D88000, { 0x08, 0xED, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_128, FCML_OP_PSEUDO_OP( 0x07 ), FCML_NA }, FCML_AM_NONE },
	// VPCOMUD xmm1, xmm2, xmm3/mem128, imm8 8F RXB.01000 0.src.0.00 EE /r ib
	{ "vpcomud;vpcomltud[p00];vpcomleud[p01];vpcomgtud[p02];vpcomgeud[p03];vpcomequd[p04];vpcomnequd[p05];vpcomfalseud[p06];vpcomtrueud[p07]", FCML_AMT_XOP, 0x0450, 0x00D88000, { 0x08, 0xEE, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_128, FCML_OP_PSEUDO_OP( 0x07 ), FCML_NA }, FCML_AM_NONE },
	// VPCOMUQ xmm1, xmm2, xmm3/mem128, imm8 8F RXB.01000 0.src.0.00 EF /r ib
	{ "vpcomuq;vpcomltuq[p00];vpcomleuq[p01];vpcomgtuq[p02];vpcomgeuq[p03];vpcomequq[p04];vpcomnequq[p05];vpcomfalseuq[p06];vpcomtrueuq[p07]", FCML_AMT_XOP, 0x0450, 0x00D88000, { 0x08, 0xEF, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_128, FCML_OP_PSEUDO_OP( 0x07 ), FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPERMIL2PD[] = {
	// VPERMIL2PS xmm1, xmm2, xmm3/mem128, xmm4, m2z
	// VPERMIL2PS ymm1, ymm2, ymm3/mem256, ymm4, m2z
	{ NULL, FCML_AMT_XOP, 0x1090, 0x00EC8000, { 0x0F, 0x3A, 0x49 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L, FCML_OP_OPERAND_IS5( FCML_ISF_IS5_SRC ), FCML_OP_OPERAND_IS5( FCML_ISF_IS5_M2Z ) }, FCML_AM_NONE },
	// VPERMIL2PS xmm1, xmm2, xmm3, xmm4/mem128, m2z
	// VPERMIL2PS ymm1, ymm2, ymm3, ymm4/mem256, m2z
	{ NULL, FCML_AMT_XOP, 0x1088, 0x00EC8000, { 0x0F, 0x3A, 0x49 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_OPERAND_IS5( FCML_ISF_IS5_SRC ), FCML_OP_MODRM_RM_SIMD_L, FCML_OP_OPERAND_IS5( FCML_ISF_IS5_M2Z ) }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPERMIL2PS[] = {
	// VPERMIL2PS xmm1, xmm2, xmm3/mem128, xmm4, m2z
	// VPERMIL2PS ymm1, ymm2, ymm3/mem256, ymm4, m2z
	{ NULL, FCML_AMT_XOP, 0x1090, 0x00EC8000, { 0x0F, 0x3A, 0x48 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L, FCML_OP_OPERAND_IS5( FCML_ISF_IS5_SRC ), FCML_OP_OPERAND_IS5( FCML_ISF_IS5_M2Z ) }, FCML_AM_NONE },
	// VPERMIL2PS xmm1, xmm2, xmm3, xmm4/mem128, m2z
	// VPERMIL2PS ymm1, ymm2, ymm3, ymm4/mem256, m2z
	{ NULL, FCML_AMT_XOP, 0x1088, 0x00EC8000, { 0x0F, 0x3A, 0x48 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_OPERAND_IS5( FCML_ISF_IS5_SRC ), FCML_OP_MODRM_RM_SIMD_L, FCML_OP_OPERAND_IS5( FCML_ISF_IS5_M2Z ) }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPHADDBD[] = {
	// VPHADDBD xmm1, xmm2/mem128 8F RXB.01001 0.1111.0.00 C2 /r
	{ NULL, FCML_AMT_XOP, 0x0550, 0x00D88000, { 0x09, 0xC2, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPHADDBW[] = {
	// VPHADDBW xmm1, xmm2/mem128 8F RXB.01001 0.1111.0.00 C1 /r
	{ NULL, FCML_AMT_XOP, 0x0550, 0x00D88000, { 0x09, 0xC1, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPHADDBQ[] = {
	// VPHADDBQ xmm1, xmm2/mem128 8F RXB.01001 0.1111.0.00 C3 /r
	{ NULL, FCML_AMT_XOP, 0x0550, 0x00D88000, { 0x09, 0xC3, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPHADDDQ[] = {
	// VPHADDDQ xmm1, xmm2/mem128 8F RXB.01001 0.1111.0.00 CB /r
	{ NULL, FCML_AMT_XOP, 0x0550, 0x00D88000, { 0x09, 0xCB, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPHADDUBD[] = {
	// VPHADDUBD xmm1, xmm2/mem128 8F RXB.01001 0.1111.0.00 D2 /r
	{ NULL, FCML_AMT_XOP, 0x0550, 0x00D88000, { 0x09, 0xD2, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPHADDUBQ[] = {
	// VPHADDUBQ xmm1, xmm2/mem128 8F RXB.01001 0.1111.0.00 D3 /r
	{ NULL, FCML_AMT_XOP, 0x0550, 0x00D88000, { 0x09, 0xD3, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPHADDUBWD[] = {
	// VPHADDUBWD xmm1, xmm2/mem128 8F RXB.01001 0.1111.0.00 D1 /r
	{ NULL, FCML_AMT_XOP, 0x0550, 0x00D88000, { 0x09, 0xD1, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPHADDUDQ[] = {
	// VPHADDUDQ xmm1, xmm2/mem128 8F RXB.01001 0.1111.0.00 DB /r
	{ NULL, FCML_AMT_XOP, 0x0550, 0x00D88000, { 0x09, 0xDB, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPHADDUWD[] = {
	// VPHADDUWD xmm1, xmm2/mem128 8F RXB.01001 0.1111.0.00 D6 /r
	{ NULL, FCML_AMT_XOP, 0x0550, 0x00D88000, { 0x09, 0xD6, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPHADDUWQ[] = {
	// VPHADDUWQ xmm1, xmm2/mem128 8F RXB.01001 0.1111.0.00 D7 /r
	{ NULL, FCML_AMT_XOP, 0x0550, 0x00D88000, { 0x09, 0xD7, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPHADDWD[] = {
	// VPHADDWD xmm1, xmm2/mem128 8F RXB.01001 0.1111.0.00 C6 /r
	{ NULL, FCML_AMT_XOP, 0x0550, 0x00D88000, { 0x09, 0xC6, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPHADDWQ[] = {
	// VPHADDWQ xmm1, xmm2/mem128 8F RXB.01001 0.1111.0.00 C7 /r
	{ NULL, FCML_AMT_XOP, 0x0550, 0x00D88000, { 0x09, 0xC7, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPHSUBBW[] = {
	// VPHSUBBW xmm1, xmm2/mem128 8F RXB.01001 0.1111.0.00 E1 /r
	{ NULL, FCML_AMT_XOP, 0x0550, 0x00D88000, { 0x09, 0xE1, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPHSUBDQ[] = {
	// VPHSUBDQ xmm1, xmm2/mem128 8F RXB.01001 0.1111.0.00 E3 /r
	{ NULL, FCML_AMT_XOP, 0x0550, 0x00D88000, { 0x09, 0xE3, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPHSUBWD[] = {
	// VPHSUBWD xmm1, xmm2/mem128 8F RXB.01001 0.1111.0.00 E2 /r
	{ NULL, FCML_AMT_XOP, 0x0550, 0x00D88000, { 0x09, 0xE2, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPMACSDD[] = {
	// VPMACSDD xmm1, xmm2, xmm3/mem128, xmm4 8F RXB.01000 0.src.0.00 9E /r ib
	{ NULL, FCML_AMT_XOP, 0x0450, 0x00D88000, { 0x08, 0x9E, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_128, FCML_OP_OPERAND_IS4, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPMACSDQH[] = {
	// VPMACSDQH xmm1, xmm2, xmm3/mem128, xmm4 8F RXB.01000 0.src.0.00 9F /r ib
	{ NULL, FCML_AMT_XOP, 0x0450, 0x00D88000, { 0x08, 0x9F, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_128, FCML_OP_OPERAND_IS4, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPMACSDQL[] = {
	// VPMACSDQL xmm1, xmm2, xmm3/mem128, xmm4 8F RXB.01000 0.src.0.00 97 /r ib
	{ NULL, FCML_AMT_XOP, 0x0450, 0x00D88000, { 0x08, 0x97, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_128, FCML_OP_OPERAND_IS4, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPMACSSDD[] = {
	// VPMACSSDD xmm1, xmm2, xmm3/mem128, xmm4 8F RXB.01000 X.src.0.00 8E /r ib
	{ NULL, FCML_AMT_XOP, 0x0450, 0x00D88000, { 0x08, 0x8E, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_128, FCML_OP_OPERAND_IS4, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPMACSSDQH[] = {
	// VPMACSSDQH xmm1, xmm2, xmm3/mem128, xmm4 8F RXB.01000 0.src.0.00 8F /r ib
	{ NULL, FCML_AMT_XOP, 0x0450, 0x00D88000, { 0x08, 0x8F, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_128, FCML_OP_OPERAND_IS4, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPMACSSDQL[] = {
	// VPMACSSDQL xmm1, xmm2, xmm3/mem128, xmm4 8F RXB.01000 0.src.0.00 87 /r ib
	{ NULL, FCML_AMT_XOP, 0x0450, 0x00D88000, { 0x08, 0x87, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_128, FCML_OP_OPERAND_IS4, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPMACSSWD[] = {
	// VPMACSSWD xmm1, xmm2, xmm3/mem128, xmm4 8F RXB.01000 0.src.0.00 86 /r ib
	{ NULL, FCML_AMT_XOP, 0x0450, 0x00D88000, { 0x08, 0x86, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_128, FCML_OP_OPERAND_IS4, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPMACSSWW[] = {
	// VPMACSSWW xmm1, xmm2, xmm3/mem128, xmm4 8F RXB.01000 X.src.0.00 85 /r ib
	{ NULL, FCML_AMT_XOP, 0x0450, 0x00D88000, { 0x08, 0x85, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_128, FCML_OP_OPERAND_IS4, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPMACSWD[] = {
	// VPMACSWD xmm1, xmm2, xmm3/mem128, xmm4 8F RXB.01000 0.src.0.00 96 /r ib
	{ NULL, FCML_AMT_XOP, 0x0450, 0x00D88000, { 0x08, 0x96, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_128, FCML_OP_OPERAND_IS4, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPMACSWW[] = {
	// VPMACSWW xmm1, xmm2, xmm3/mem128, xmm4 8F RXB.01000 0.src.0.00 95 /r ib
	{ NULL, FCML_AMT_XOP, 0x0450, 0x00D88000, { 0x08, 0x95, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_128, FCML_OP_OPERAND_IS4, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPMADCSSWD[] = {
	// VPMADCSSWD xmm1, xmm2, xmm3/mem128, xmm4 8F RXB.01000 0.src.0.00 A6 /r ib
	{ NULL, FCML_AMT_XOP, 0x0450, 0x00D88000, { 0x08, 0xA6, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_128, FCML_OP_OPERAND_IS4, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPMADCSWD[] = {
	// VPMADCSWD xmm1, xmm2, xmm3/mem128, xmm4 8F RXB.01000 0.src.0.00 B6 /r ib
	{ NULL, FCML_AMT_XOP, 0x0450, 0x00D88000, { 0x08, 0xB6, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_128, FCML_OP_OPERAND_IS4, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPPERM[] = {
	// VPPERM xmm1, xmm2, xmm3/mem128, xmm4 8F RXB.01000 0.src.0.00 A3 /r ib
	{ NULL, FCML_AMT_XOP, 0x0450, 0x00D88000, { 0x08, 0xA3, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_128, FCML_OP_OPERAND_IS4, FCML_NA }, FCML_AM_NONE },
	// VPPERM xmm1, xmm2, xmm3, xmm4/mem128 8F RXB.01000 1.src.0.00 A3 /r ib
	{ NULL, FCML_AMT_XOP, 0x0448, 0x00D88000, { 0x08, 0xA3, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_OPERAND_IS4, FCML_OP_MODRM_RM_XMM_128, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPROTD[] = {
	// VPROTD xmm1, xmm2/mem128, xmm3 8F RXB.01001 0.src.0.00 92 /r
	{ NULL, FCML_AMT_XOP, 0x0450, 0x00D88000, { 0x09, 0x92, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_OP_VEX_VVVV_XMM_REG, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VPROTD xmm1, xmm2, xmm3/mem128 8F RXB.01001 1.src.0.00 92 /r
	{ NULL, FCML_AMT_XOP, 0x0448, 0x00D88000, { 0x09, 0x92, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VPROTD xmm1, xmm2/mem128, imm8 8F RXB.01000 0.1111.0.00 C2 /r ib
	{ NULL, FCML_AMT_XOP, 0x0550, 0x00D88000, { 0x08, 0xC2, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPROTB[] = {
	// VPROTB xmm1, xmm2/mem128, xmm3 8F RXB.01001 0.src.0.00 90 /r
	{ NULL, FCML_AMT_XOP, 0x0450, 0x00D88000, { 0x09, 0x90, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_OP_VEX_VVVV_XMM_REG, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VPROTB xmm1, xmm2, xmm3/mem128 8F RXB.01001 1.src.0.00 90 /r
	{ NULL, FCML_AMT_XOP, 0x0448, 0x00D88000, { 0x09, 0x90, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VPROTB xmm1, xmm2/mem128, imm8 8F RXB.01000 0.1111.0.00 C0 /r ib
	{ NULL, FCML_AMT_XOP, 0x0550, 0x00D88000, { 0x08, 0xC0, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPROTQ[] = {
	// VPROTQ xmm1, xmm2/mem128, xmm3 8F RXB.01001 0.src.0.00 93 /r
	{ NULL, FCML_AMT_XOP, 0x0450, 0x00D88000, { 0x09, 0x93, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_OP_VEX_VVVV_XMM_REG, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VPROTQ xmm1, xmm2, xmm3/mem128 8F RXB.01001 1.src.0.00 93 /r
	{ NULL, FCML_AMT_XOP, 0x0448, 0x00D88000, { 0x09, 0x93, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VPROTQ xmm1, xmm2/mem128, imm8 8F RXB.01000 0.1111.0.00 C3 /r ib
	{ NULL, FCML_AMT_XOP, 0x0550, 0x00D88000, { 0x08, 0xC3, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPROTW[] = {
	// VPROTW xmm1, xmm2/mem128, xmm3 8F RXB.01001 0.src.0.00 91 /r
	{ NULL, FCML_AMT_XOP, 0x0450, 0x00D88000, { 0x09, 0x91, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_OP_VEX_VVVV_XMM_REG, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VPROTW xmm1, xmm2, xmm3/mem128 8F RXB.01001 1.src.0.00 91 /r
	{ NULL, FCML_AMT_XOP, 0x0448, 0x00D88000, { 0x09, 0x91, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VPROTW xmm1, xmm2/mem128, imm8 8F RXB.01000 0.1111.0.00 C1 /r ib
	{ NULL, FCML_AMT_XOP, 0x0550, 0x00D88000, { 0x08, 0xC1, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_NONE }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPSHAB[] = {
	// VPSHAB xmm1, xmm2/mem128, xmm3 8F RXB.01001 0.src.0.00 98 /r
	{ NULL, FCML_AMT_XOP, 0x0450, 0x00D88000, { 0x09, 0x98, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_OP_VEX_VVVV_XMM_REG, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VPSHAB xmm1, xmm2, xmm3/mem128 8F RXB.01001 1.src.0.00 98 /r
	{ NULL, FCML_AMT_XOP, 0x0448, 0x00D88000, { 0x09, 0x98, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA }, FCML_AM_NONE },
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPSHAD[] = {
	// VPSHAD xmm1, xmm2/mem128, xmm3 8F RXB.01001 0.src.0.00 9A /r
	{ NULL, FCML_AMT_XOP, 0x0450, 0x00D88000, { 0x09, 0x9A, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_OP_VEX_VVVV_XMM_REG, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VPSHAD xmm1, xmm2, xmm3/mem128 8F RXB.01001 1.src.0.00 9A /r
	{ NULL, FCML_AMT_XOP, 0x0448, 0x00D88000, { 0x09, 0x9A, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA }, FCML_AM_NONE },
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPSHAQ[] = {
	// VPSHAQ xmm1, xmm2/mem128, xmm3 8F RXB.01001 0.src.0.00 9B /r
	{ NULL, FCML_AMT_XOP, 0x0450, 0x00D88000, { 0x09, 0x9B, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_OP_VEX_VVVV_XMM_REG, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VPSHAQ xmm1, xmm2, xmm3/mem128 8F RXB.01001 1.src.0.00 9B /r
	{ NULL, FCML_AMT_XOP, 0x0448, 0x00D88000, { 0x09, 0x9B, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA }, FCML_AM_NONE },
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPSHAW[] = {
	// VPSHAW xmm1, xmm2/mem128, xmm3 8F RXB.01001 0.src.0.00 99 /r
	{ NULL, FCML_AMT_XOP, 0x0450, 0x00D88000, { 0x09, 0x99, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_OP_VEX_VVVV_XMM_REG, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VPSHAW xmm1, xmm2, xmm3/mem128 8F RXB.01001 1.src.0.00 99 /r
	{ NULL, FCML_AMT_XOP, 0x0448, 0x00D88000, { 0x09, 0x99, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA }, FCML_AM_NONE },
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPSHLB[] = {
	// VPSHLB xmm1, xmm2/mem128, xmm3 8F RXB.01001 0.src.0.00 94 /r
	{ NULL, FCML_AMT_XOP, 0x0450, 0x00D88000, { 0x09, 0x94, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_OP_VEX_VVVV_XMM_REG, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VPSHLB xmm1, xmm2, xmm3/mem128 8F RXB.01001 1.src.0.00 94 /r
	{ NULL, FCML_AMT_XOP, 0x0448, 0x00D88000, { 0x09, 0x94, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA }, FCML_AM_NONE },
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPSHLD[] = {
	// VPSHLD xmm1, xmm3/mem128, xmm2 8F RXB.01001 0.src.0.00 96 /r
	{ NULL, FCML_AMT_XOP, 0x0450, 0x00D88000, { 0x09, 0x96, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_OP_VEX_VVVV_XMM_REG, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VPSHLD xmm1, xmm2, xmm3/mem128 8F RXB.01001 1.src.0.00 96 /r
	{ NULL, FCML_AMT_XOP, 0x0448, 0x00D88000, { 0x09, 0x96, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA }, FCML_AM_NONE },
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPSHLQ[] = {
	// VPSHLQ xmm1, xmm3/mem128, xmm2 8F RXB.01001 0.src.0.00 97 /r
	{ NULL, FCML_AMT_XOP, 0x0450, 0x00D88000, { 0x09, 0x97, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_OP_VEX_VVVV_XMM_REG, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VPSHLQ xmm1, xmm2, xmm3/mem128 8F RXB.01001 1.src.0.00 97 /r
	{ NULL, FCML_AMT_XOP, 0x0448, 0x00D88000, { 0x09, 0x97, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA }, FCML_AM_NONE },
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPSHLW[] = {
	// VPSHLW xmm1, xmm3/mem128, xmm2 8F RXB.01001 0.src.0.00 95 /r
	{ NULL, FCML_AMT_XOP, 0x0450, 0x00D88000, { 0x09, 0x95, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_128, FCML_OP_VEX_VVVV_XMM_REG, FCML_NA, FCML_NA }, FCML_AM_NONE },
	// VPSHLW xmm1, xmm2, xmm3/mem128 8F RXB.01001 1.src.0.00 95 /r
	{ NULL, FCML_AMT_XOP, 0x0448, 0x00D88000, { 0x09, 0x95, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA }, FCML_AM_NONE },
};

struct fcml_st_def_instruction_description fcml_ext_instructions_def[] = {
		FCML_IA_INSTRUCTION( F_AAA, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_AAA ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "aad", fcml_st_def_addr_mode_desc_AAD ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "aam", fcml_st_def_addr_mode_desc_AAM ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "aas", fcml_st_def_addr_mode_desc_AAS ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "adc", fcml_st_def_addr_mode_desc_ADC ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "add", fcml_st_def_addr_mode_desc_ADD ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "addpd", fcml_st_def_addr_mode_desc_ADDPD ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "addps", fcml_st_def_addr_mode_desc_ADDPS ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "addsd", fcml_st_def_addr_mode_desc_ADDSD ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "addss", fcml_st_def_addr_mode_desc_ADDSS ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "addsubpd", fcml_st_def_addr_mode_desc_ADDSUBPD ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "addsubps", fcml_st_def_addr_mode_desc_ADDSUBPS ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "aesdec", fcml_st_def_addr_mode_desc_AESDEC ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "aesdeclast", fcml_st_def_addr_mode_desc_AESDECLAST ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "aesenc", fcml_st_def_addr_mode_desc_AESENC ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "aesenclast", fcml_st_def_addr_mode_desc_AESENCLAST ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "aesimc", fcml_st_def_addr_mode_desc_AESIMC ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "aeskeygenassist", fcml_st_def_addr_mode_desc_AESKEYGENASSIST ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "and", fcml_st_def_addr_mode_desc_AND ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "andpd", fcml_st_def_addr_mode_desc_ANDPD ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "andps", fcml_st_def_addr_mode_desc_ANDPS ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "andnpd", fcml_st_def_addr_mode_desc_ANDNPD ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "andnps", fcml_st_def_addr_mode_desc_ANDNPS ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "arpl", fcml_st_def_addr_mode_desc_ARPL ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "blendpd", fcml_st_def_addr_mode_desc_BLENDPD),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "blendps", fcml_st_def_addr_mode_desc_BLENDPS),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "blendvpd", fcml_st_def_addr_mode_desc_BLENDVPD),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "blendvps", fcml_st_def_addr_mode_desc_BLENDVPS),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "vmptrld", fcml_st_def_addr_mode_desc_VMPTRLD),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "vmptrst", fcml_st_def_addr_mode_desc_VMPTRST),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "vmclear", fcml_st_def_addr_mode_desc_VMCLEAR),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "vmread", fcml_st_def_addr_mode_desc_VMREAD),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "vmwrite", fcml_st_def_addr_mode_desc_VMWRITE),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "vmlaunch", fcml_st_def_addr_mode_desc_VMLAUNCH),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "vmresume", fcml_st_def_addr_mode_desc_VMRESUME),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "vmxoff", fcml_st_def_addr_mode_desc_VMXOFF),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "vmxon", fcml_st_def_addr_mode_desc_VMXON),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "vmcall", fcml_st_def_addr_mode_desc_VMCALL),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "vmfunc", fcml_st_def_addr_mode_desc_VMFUNC),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "vbroadcastss", fcml_st_def_addr_mode_desc_VBROADCASTSS),
		FCML_IA_INSTRUCTION( F_UNKNOWN, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPBROADCAST),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "bound", fcml_st_def_addr_mode_desc_BOUND),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "bsf", fcml_st_def_addr_mode_desc_BSF),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "bsr", fcml_st_def_addr_mode_desc_BSR),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "bswap", fcml_st_def_addr_mode_desc_BSWAP),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "bt", fcml_st_def_addr_mode_desc_BT),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "btc", fcml_st_def_addr_mode_desc_BTC),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "btr", fcml_st_def_addr_mode_desc_BTR),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "bts", fcml_st_def_addr_mode_desc_BTS),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "call", fcml_st_def_addr_mode_desc_CALL),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "cbw", fcml_st_def_addr_mode_desc_CBW),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "clc", fcml_st_def_addr_mode_desc_CLC),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "cld", fcml_st_def_addr_mode_desc_CLD),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "clflush", fcml_st_def_addr_mode_desc_CLFLUSH),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "cli", fcml_st_def_addr_mode_desc_CLI),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "clgi", fcml_st_def_addr_mode_desc_CLGI),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "clts", fcml_st_def_addr_mode_desc_CLTS),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "cmc", fcml_st_def_addr_mode_desc_CMC),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "cmov", fcml_st_def_addr_mode_desc_CMOV),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "cmp", fcml_st_def_addr_mode_desc_CMP),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "cmppd", fcml_st_def_addr_mode_desc_CMPPD),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "cmpps", fcml_st_def_addr_mode_desc_CMPPS),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "cmps", fcml_st_def_addr_mode_desc_CMPS),
		FCML_IA_INSTRUCTION( F_UNKNOWN, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_CMPSD),
		FCML_IA_INSTRUCTION( F_UNKNOWN, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_CMPSS),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "cmpxchg", fcml_st_def_addr_mode_desc_CMPXCHG),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "cmpxchg8b", fcml_st_def_addr_mode_desc_CMPXCHGxB),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "comisd", fcml_st_def_addr_mode_desc_COMISD),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "comiss", fcml_st_def_addr_mode_desc_COMISS),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "cpuid", fcml_st_def_addr_mode_desc_CPUID),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "crc32", fcml_st_def_addr_mode_desc_CRC32),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "cvtdq2pd", fcml_st_def_addr_mode_desc_CVTDQ2PD),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "cvtdq2ps", fcml_st_def_addr_mode_desc_CVTDQ2PS),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "cvtpd2dq", fcml_st_def_addr_mode_desc_CVTPD2DQ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "cvtpd2pi", fcml_st_def_addr_mode_desc_CVTPD2PI),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "cvtpd2ps", fcml_st_def_addr_mode_desc_CVTPD2PS),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "cvtpi2pd", fcml_st_def_addr_mode_desc_CVTPI2PD),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "cvtpi2ps", fcml_st_def_addr_mode_desc_CVTPI2PS),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "cvtps2dq", fcml_st_def_addr_mode_desc_CVTPS2DQ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "cvtps2pd", fcml_st_def_addr_mode_desc_CVTPS2PD),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "cvtps2pi", fcml_st_def_addr_mode_desc_CVTPS2PI),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "cvtsd2si", fcml_st_def_addr_mode_desc_CVTSD2SI),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "cvtsd2ss", fcml_st_def_addr_mode_desc_CVTSD2SS),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "cvtsi2sd", fcml_st_def_addr_mode_desc_CVTSI2SD),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "cvtsi2ss", fcml_st_def_addr_mode_desc_CVTSI2SS),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "cvtss2sd", fcml_st_def_addr_mode_desc_CVTSS2SD),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "cvtss2si", fcml_st_def_addr_mode_desc_CVTSS2SI),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "cvttpd2dq", fcml_st_def_addr_mode_desc_CVTTPD2DQ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "cvttpd2pi", fcml_st_def_addr_mode_desc_CVTTPD2PI),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "cvttps2dq", fcml_st_def_addr_mode_desc_CVTTPS2DQ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "cvttps2pi", fcml_st_def_addr_mode_desc_CVTTPS2PI),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "cvttsd2si", fcml_st_def_addr_mode_desc_CVTTSD2SI),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "cvttss2si", fcml_st_def_addr_mode_desc_CVTTSS2SI),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "cwd", fcml_st_def_addr_mode_desc_CWD_CDQ_CQO),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "daa", fcml_st_def_addr_mode_desc_DAA),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "das", fcml_st_def_addr_mode_desc_DAS),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "dec", fcml_st_def_addr_mode_desc_DEC),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "div", fcml_st_def_addr_mode_desc_DIV),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "divpd", fcml_st_def_addr_mode_desc_DIVPD),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "divps", fcml_st_def_addr_mode_desc_DIVPS),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "divsd", fcml_st_def_addr_mode_desc_DIVSD),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "divss", fcml_st_def_addr_mode_desc_DIVSS),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "dppd", fcml_st_def_addr_mode_desc_DPPD),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "dpps", fcml_st_def_addr_mode_desc_DPPS),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "emms", fcml_st_def_addr_mode_desc_EMMS),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "vextractf128", fcml_st_def_addr_mode_desc_VEXTRACTF128),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "enter", fcml_st_def_addr_mode_desc_ENTER),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "extractps", fcml_st_def_addr_mode_desc_EXTRACTPS),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "extrq", fcml_st_def_addr_mode_desc_EXTRQ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "f2xm1", fcml_st_def_addr_mode_desc_F2XM1),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "fabs", fcml_st_def_addr_mode_desc_FABS),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "fadd", fcml_st_def_addr_mode_desc_FADD),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "fbld", fcml_st_def_addr_mode_desc_FBLD),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "fbstp", fcml_st_def_addr_mode_desc_FBSTP),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "fchs", fcml_st_def_addr_mode_desc_FCHS),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "fclex", fcml_st_def_addr_mode_desc_FCLEX),
		FCML_IA_INSTRUCTION( F_UNKNOWN, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_FCMOV),
		FCML_IA_INSTRUCTION( F_UNKNOWN, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_FCOM),
		FCML_IA_INSTRUCTION( F_UNKNOWN, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_FCOMI),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "fcos", fcml_st_def_addr_mode_desc_FCOS),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "fdecstp", fcml_st_def_addr_mode_desc_FDECSTP),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "fdiv", fcml_st_def_addr_mode_desc_FDIV),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "fdivr", fcml_st_def_addr_mode_desc_FDIVR),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "ffree", fcml_st_def_addr_mode_desc_FFREE ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "ficom", fcml_st_def_addr_mode_desc_FICOM ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "fild", fcml_st_def_addr_mode_desc_FILD ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "fincstp", fcml_st_def_addr_mode_desc_FINCSTP ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "finit", fcml_st_def_addr_mode_desc_FINIT ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "fist", fcml_st_def_addr_mode_desc_FIST ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "fisttp", fcml_st_def_addr_mode_desc_FISTTP ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "fld", fcml_st_def_addr_mode_desc_FLD ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_FLDx ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "fldcw", fcml_st_def_addr_mode_desc_FLDCW),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "fldenv", fcml_st_def_addr_mode_desc_FLDENV),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "fmul", fcml_st_def_addr_mode_desc_FMUL ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "fnop", fcml_st_def_addr_mode_desc_FNOP ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "fpatan", fcml_st_def_addr_mode_desc_FPATAN ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "fprem", fcml_st_def_addr_mode_desc_FPREM ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "fprem1", fcml_st_def_addr_mode_desc_FPREM1 ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "fptan", fcml_st_def_addr_mode_desc_FPTAN ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "frndint", fcml_st_def_addr_mode_desc_FRNDINT ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "frstor", fcml_st_def_addr_mode_desc_FRSTOR),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "fsave", fcml_st_def_addr_mode_desc_FSAVE ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "fscale", fcml_st_def_addr_mode_desc_FSCALE ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "fsin", fcml_st_def_addr_mode_desc_FSIN ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "fsincos", fcml_st_def_addr_mode_desc_FSINCOS ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "fsqrt", fcml_st_def_addr_mode_desc_FSQRT ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "fst", fcml_st_def_addr_mode_desc_FST ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "fstcw", fcml_st_def_addr_mode_desc_FSTCW ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "fstenv", fcml_st_def_addr_mode_desc_FSTENV ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "fstsw", fcml_st_def_addr_mode_desc_FSTSW ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "fsub", fcml_st_def_addr_mode_desc_FSUB ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "fsubr", fcml_st_def_addr_mode_desc_FSUBR ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "ftst", fcml_st_def_addr_mode_desc_FTST ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "fucom", fcml_st_def_addr_mode_desc_FUCOM ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "fxam", fcml_st_def_addr_mode_desc_FXAM ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "fxch", fcml_st_def_addr_mode_desc_FXCH ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "fxrstor", fcml_st_def_addr_mode_desc_FXRSTOR ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "fxsave", fcml_st_def_addr_mode_desc_FXSAVE ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "fxtract", fcml_st_def_addr_mode_desc_FXTRACT ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "fyl2x", fcml_st_def_addr_mode_desc_FYL2X ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "fyl2xp1", fcml_st_def_addr_mode_desc_FYL2XP1 ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "getsec", fcml_st_def_addr_mode_desc_GETSEC ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "haddpd", fcml_st_def_addr_mode_desc_HADDPD ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "haddps", fcml_st_def_addr_mode_desc_HADDPS ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "hlt", fcml_st_def_addr_mode_desc_HLT ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "hsubpd", fcml_st_def_addr_mode_desc_HSUBPD ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "hsubps", fcml_st_def_addr_mode_desc_HSUBPS ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "invept", fcml_st_def_addr_mode_desc_INVEPT ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "invvpid", fcml_st_def_addr_mode_desc_INVVPID ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "idiv", fcml_st_def_addr_mode_desc_IDIV ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "imul", fcml_st_def_addr_mode_desc_IMUL ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "in", fcml_st_def_addr_mode_desc_IN ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "inc", fcml_st_def_addr_mode_desc_INC ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "ins", fcml_st_def_addr_mode_desc_INS ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "insertps", fcml_st_def_addr_mode_desc_INSERTPS ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "insertq", fcml_st_def_addr_mode_desc_INSERTQ ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "vinsertf128", fcml_st_def_addr_mode_desc_VINSERTF128 ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "int", fcml_st_def_addr_mode_desc_INT ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "invd", fcml_st_def_addr_mode_desc_INVD ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "invlpg", fcml_st_def_addr_mode_desc_INVLPG ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "invlpga", fcml_st_def_addr_mode_desc_INVLPGA ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "invpcid", fcml_st_def_addr_mode_desc_INVPCID ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "iret", fcml_st_def_addr_mode_desc_IRET ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "jcxz", fcml_st_def_addr_mode_desc_JCXZ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "j", fcml_st_def_addr_mode_desc_Jcc),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "jmp", fcml_st_def_addr_mode_desc_JMP),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "lahf", fcml_st_def_addr_mode_desc_LAHF),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "lar", fcml_st_def_addr_mode_desc_LAR),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "lddqu", fcml_st_def_addr_mode_desc_LDDQU),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "ldmxcsr", fcml_st_def_addr_mode_desc_LDMXCSR),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "lds", fcml_st_def_addr_mode_desc_LDS),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "lea", fcml_st_def_addr_mode_desc_LEA),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "leave", fcml_st_def_addr_mode_desc_LEAVE),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "lfence", fcml_st_def_addr_mode_desc_LFENCE),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "llwpcb", fcml_st_def_addr_mode_desc_LLWPCB),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "lgdt", fcml_st_def_addr_mode_desc_LGDT),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "lldt", fcml_st_def_addr_mode_desc_LLDT),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "lmsw", fcml_st_def_addr_mode_desc_LMSW),
		FCML_IA_INSTRUCTION( F_UNKNOWN, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_LODS),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "loop", fcml_st_def_addr_mode_desc_LOOP),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "lwpins", fcml_st_def_addr_mode_desc_LWPINS),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "lwpval", fcml_st_def_addr_mode_desc_LWPVAL),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "lsl", fcml_st_def_addr_mode_desc_LSL),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "ltr", fcml_st_def_addr_mode_desc_LTR),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "maskmovdqu", fcml_st_def_addr_mode_desc_MASKMOVDQU),
		FCML_IA_INSTRUCTION( F_UNKNOWN, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VMASKMOVP),
		FCML_IA_INSTRUCTION( F_UNKNOWN, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPMASKMOVD),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "maskmovq", fcml_st_def_addr_mode_desc_MASKMOVQ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "maxpd", fcml_st_def_addr_mode_desc_MAXPD),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "maxps", fcml_st_def_addr_mode_desc_MAXPS),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "maxsd", fcml_st_def_addr_mode_desc_MAXSD),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "maxss", fcml_st_def_addr_mode_desc_MAXSS),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "mfence", fcml_st_def_addr_mode_desc_MFENCE),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "minpd", fcml_st_def_addr_mode_desc_MINPD),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "minps", fcml_st_def_addr_mode_desc_MINPS),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "minsd", fcml_st_def_addr_mode_desc_MINSD),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "minss", fcml_st_def_addr_mode_desc_MINSS),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "monitor;monitor[ts]", fcml_st_def_addr_mode_desc_MONITOR),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "movapd", fcml_st_def_addr_mode_desc_MOVAPD),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "movaps", fcml_st_def_addr_mode_desc_MOVAPS),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "movbe", fcml_st_def_addr_mode_desc_MOVBE),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "mov", fcml_st_def_addr_mode_desc_MOV),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "movd", fcml_st_def_addr_mode_desc_MOVD),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "movddup", fcml_st_def_addr_mode_desc_MOVDDUP),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "movdqa", fcml_st_def_addr_mode_desc_MOVDQA),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "movdqu", fcml_st_def_addr_mode_desc_MOVDQU),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "movdq2q", fcml_st_def_addr_mode_desc_MOVDQ2Q),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "movhlps", fcml_st_def_addr_mode_desc_MOVHLPS),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "movhpd", fcml_st_def_addr_mode_desc_MOVHPD),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "movhps", fcml_st_def_addr_mode_desc_MOVHPS),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "movlhps", fcml_st_def_addr_mode_desc_MOVLHPS),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "movlpd", fcml_st_def_addr_mode_desc_MOVLPD),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "movlps", fcml_st_def_addr_mode_desc_MOVLPS),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "movmskpd", fcml_st_def_addr_mode_desc_MOVMSKPD),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "movmskps", fcml_st_def_addr_mode_desc_MOVMSKPS),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "movntdqa", fcml_st_def_addr_mode_desc_MOVNTDQA),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "movntdq", fcml_st_def_addr_mode_desc_MOVNTDQ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "movnti", fcml_st_def_addr_mode_desc_MOVNTI),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "movntpd", fcml_st_def_addr_mode_desc_MOVNTPD),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "movntps", fcml_st_def_addr_mode_desc_MOVNTPS),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "movntsd", fcml_st_def_addr_mode_desc_MOVNTSD),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "movntss", fcml_st_def_addr_mode_desc_MOVNTSS),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "movntq", fcml_st_def_addr_mode_desc_MOVNTQ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "movq", fcml_st_def_addr_mode_desc_MOVQ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "movq2dq", fcml_st_def_addr_mode_desc_MOVQ2DQ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_MOVS),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "movsd", fcml_st_def_addr_mode_desc_MOVSD),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "movshdup", fcml_st_def_addr_mode_desc_MOVSHDUP),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "movsldup", fcml_st_def_addr_mode_desc_MOVSLDUP),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "movss", fcml_st_def_addr_mode_desc_MOVSS),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "movsx", fcml_st_def_addr_mode_desc_MOVSX),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "movupd", fcml_st_def_addr_mode_desc_MOVUPD),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "movups", fcml_st_def_addr_mode_desc_MOVUPS),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "movzx", fcml_st_def_addr_mode_desc_MOVZX),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "mpsadbw", fcml_st_def_addr_mode_desc_MPSADBW),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "mul", fcml_st_def_addr_mode_desc_MUL),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "mulpd", fcml_st_def_addr_mode_desc_MULPD),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "mulps", fcml_st_def_addr_mode_desc_MULPS),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "mulsd", fcml_st_def_addr_mode_desc_MULSD),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "mulss", fcml_st_def_addr_mode_desc_MULSS),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "mwait", fcml_st_def_addr_mode_desc_MWAIT),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "neg", fcml_st_def_addr_mode_desc_NEG),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "nop", fcml_st_def_addr_mode_desc_NOP),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "not", fcml_st_def_addr_mode_desc_NOT),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "or", fcml_st_def_addr_mode_desc_OR),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "orpd", fcml_st_def_addr_mode_desc_ORPD),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "orps", fcml_st_def_addr_mode_desc_ORPS),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "out", fcml_st_def_addr_mode_desc_OUT),
		FCML_IA_INSTRUCTION( F_UNKNOWN, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_OUTS),
		FCML_IA_INSTRUCTION( F_UNKNOWN, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PABS),
		FCML_IA_INSTRUCTION( F_UNKNOWN, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PACKSS),
		FCML_IA_INSTRUCTION( F_UNKNOWN, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PACKUSD),
		FCML_IA_INSTRUCTION( F_UNKNOWN, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PACKUSW),
		FCML_IA_INSTRUCTION( F_UNKNOWN, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PADD),
		FCML_IA_INSTRUCTION( F_UNKNOWN, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PADDS),
		FCML_IA_INSTRUCTION( F_UNKNOWN, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PADDUS),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "paddq", fcml_st_def_addr_mode_desc_PADDQ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "palignr", fcml_st_def_addr_mode_desc_PALIGNR),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "pand", fcml_st_def_addr_mode_desc_PAND),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "pandn", fcml_st_def_addr_mode_desc_PANDN),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "pause", fcml_st_def_addr_mode_desc_PAUSE),
		FCML_IA_INSTRUCTION( F_UNKNOWN, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PAVG),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "pblendvb", fcml_st_def_addr_mode_desc_PBLENDVB),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "pblendw", fcml_st_def_addr_mode_desc_PBLENDW),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "vpblendd", fcml_st_def_addr_mode_desc_VPBLENDD),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "pclmulqdq", fcml_st_def_addr_mode_desc_PCLMULQDQ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PCMPEQ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "pcmpeqq", fcml_st_def_addr_mode_desc_PCMPEQQ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "pcmpestri", fcml_st_def_addr_mode_desc_PCMPESTRI),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "pcmpestrm", fcml_st_def_addr_mode_desc_PCMPESTRM),
		FCML_IA_INSTRUCTION( F_UNKNOWN, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PCMPGT),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "pcmpgtq", fcml_st_def_addr_mode_desc_PCMPGTQ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "pcmpistri", fcml_st_def_addr_mode_desc_PCMPISTRI),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "pcmpistrm", fcml_st_def_addr_mode_desc_PCMPISTRM),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "pextr", fcml_st_def_addr_mode_desc_PEXTR),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "pextrw", fcml_st_def_addr_mode_desc_PEXTRW),
		FCML_IA_INSTRUCTION( F_UNKNOWN, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PHADD),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "phaddsw", fcml_st_def_addr_mode_desc_PHADDSW),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "phminposuw", fcml_st_def_addr_mode_desc_PHMINPOSUW),
		FCML_IA_INSTRUCTION( F_UNKNOWN, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PHSUB),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "phsubsw", fcml_st_def_addr_mode_desc_PHSUBSW),
		FCML_IA_INSTRUCTION( F_UNKNOWN, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PINSR),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "pinsrw", fcml_st_def_addr_mode_desc_PINSRW),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "pmaddubsw", fcml_st_def_addr_mode_desc_PMADDUBSW),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "pmaddwd", fcml_st_def_addr_mode_desc_PMADDWD),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "pmaxsb", fcml_st_def_addr_mode_desc_PMAXSB),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "pmaxsd", fcml_st_def_addr_mode_desc_PMAXSD),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "pmaxsw", fcml_st_def_addr_mode_desc_PMAXSW),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "pmaxub", fcml_st_def_addr_mode_desc_PMAXUB),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "pmaxud", fcml_st_def_addr_mode_desc_PMAXUD),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "pmaxuw", fcml_st_def_addr_mode_desc_PMAXUW),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "pminsb", fcml_st_def_addr_mode_desc_PMINSB),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "pminsd", fcml_st_def_addr_mode_desc_PMINSD),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "pminsw", fcml_st_def_addr_mode_desc_PMINSW),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "pminuw", fcml_st_def_addr_mode_desc_PMINUW),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "pminub", fcml_st_def_addr_mode_desc_PMINUB),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "pminud", fcml_st_def_addr_mode_desc_PMINUD),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "pmovmskb", fcml_st_def_addr_mode_desc_PMOVMSKB),
		FCML_IA_INSTRUCTION( F_UNKNOWN, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PMOVSX),
		FCML_IA_INSTRUCTION( F_UNKNOWN, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PMOVZX),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "pmuldq", fcml_st_def_addr_mode_desc_PMULDQ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "pmulhrsw", fcml_st_def_addr_mode_desc_PMULHRSW),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "pmulhuw", fcml_st_def_addr_mode_desc_PMULHUW),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "pmulhw", fcml_st_def_addr_mode_desc_PMULHW),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "pmuludq", fcml_st_def_addr_mode_desc_PMULUDQ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "pmullw", fcml_st_def_addr_mode_desc_PMULLW),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "pmulld", fcml_st_def_addr_mode_desc_PMULLD),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "pop", fcml_st_def_addr_mode_desc_POP),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "popa", fcml_st_def_addr_mode_desc_POPA),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "popcnt", fcml_st_def_addr_mode_desc_POPCNT),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "popf", fcml_st_def_addr_mode_desc_POPF),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "por", fcml_st_def_addr_mode_desc_POR),
		FCML_IA_INSTRUCTION( F_UNKNOWN, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PREFETCHT),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "psadbw", fcml_st_def_addr_mode_desc_PSADBW),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "pshufb", fcml_st_def_addr_mode_desc_PSHUFB),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "pshufd", fcml_st_def_addr_mode_desc_PSHUFD),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "pshufhw", fcml_st_def_addr_mode_desc_PSHUFHW),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "pshuflw", fcml_st_def_addr_mode_desc_PSHUFLW),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "pshufw", fcml_st_def_addr_mode_desc_PSHUFW),
		FCML_IA_INSTRUCTION( F_UNKNOWN, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PSIGN),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "pslldq", fcml_st_def_addr_mode_desc_PSLLDQ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PSLL),
		FCML_IA_INSTRUCTION( F_UNKNOWN, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PSRA),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "psrldq", fcml_st_def_addr_mode_desc_PSRLDQ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PSRL),
		FCML_IA_INSTRUCTION( F_UNKNOWN, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PSUB),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "psubq", fcml_st_def_addr_mode_desc_PSUBQ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PSUBS),
		FCML_IA_INSTRUCTION( F_UNKNOWN, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PSUBUS),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "ptest", fcml_st_def_addr_mode_desc_PTEST),
		FCML_IA_INSTRUCTION( F_UNKNOWN, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PUNPCKL),
		FCML_IA_INSTRUCTION( F_UNKNOWN, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PUNPCKH),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "push", fcml_st_def_addr_mode_desc_PUSH),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "pusha", fcml_st_def_addr_mode_desc_PUSHA),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "pushf", fcml_st_def_addr_mode_desc_PUSHF),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "pxor", fcml_st_def_addr_mode_desc_PXOR),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "rcl", fcml_st_def_addr_mode_desc_RCL),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "rcr", fcml_st_def_addr_mode_desc_RCR),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "rol", fcml_st_def_addr_mode_desc_ROL),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "ror", fcml_st_def_addr_mode_desc_ROR),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "rcpps", fcml_st_def_addr_mode_desc_RCPPS),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "rcpss", fcml_st_def_addr_mode_desc_RCPSS),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "rdfsbase", fcml_st_def_addr_mode_desc_RDFSBASE),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "rdrand", fcml_st_def_addr_mode_desc_RDRAND),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "rdtscp", fcml_st_def_addr_mode_desc_RDTSCP),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "rdtsc", fcml_st_def_addr_mode_desc_RDTSC),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "rdpmc", fcml_st_def_addr_mode_desc_RDPMC),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "rdmsr", fcml_st_def_addr_mode_desc_RDMSR),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "ret", fcml_st_def_addr_mode_desc_RET),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "roundpd", fcml_st_def_addr_mode_desc_ROUNDPD),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "roundps", fcml_st_def_addr_mode_desc_ROUNDPS),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "roundsd", fcml_st_def_addr_mode_desc_ROUNDSD),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "roundss", fcml_st_def_addr_mode_desc_ROUNDSS),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "rsm", fcml_st_def_addr_mode_desc_RSM),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "rsqrtps", fcml_st_def_addr_mode_desc_RSQRTPS),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "rsqrtss", fcml_st_def_addr_mode_desc_RSQRTSS),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "sahf", fcml_st_def_addr_mode_desc_SAHF),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "sar", fcml_st_def_addr_mode_desc_SAR),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "shl;sal", fcml_st_def_addr_mode_desc_SHL_SAL),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "shr", fcml_st_def_addr_mode_desc_SHR),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "sbb", fcml_st_def_addr_mode_desc_SBB),
		FCML_IA_INSTRUCTION( F_UNKNOWN, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_SCAS),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "set", fcml_st_def_addr_mode_desc_SETcc),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "sfence", fcml_st_def_addr_mode_desc_SFENCE),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "sgdt", fcml_st_def_addr_mode_desc_SGDT),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "shld", fcml_st_def_addr_mode_desc_SHLD),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "shrd", fcml_st_def_addr_mode_desc_SHRD),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "skinit", fcml_st_def_addr_mode_desc_SKINIT),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "slwpcb", fcml_st_def_addr_mode_desc_SLWPCB),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "shufpd", fcml_st_def_addr_mode_desc_SHUFPD),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "shufps", fcml_st_def_addr_mode_desc_SHUFPS),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "sidt", fcml_st_def_addr_mode_desc_SIDT),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "sldt", fcml_st_def_addr_mode_desc_SLDT),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "smsw", fcml_st_def_addr_mode_desc_SMSW),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "sqrtpd", fcml_st_def_addr_mode_desc_SQRTPD),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "sqrtps", fcml_st_def_addr_mode_desc_SQRTPS),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "sqrtsd", fcml_st_def_addr_mode_desc_SQRTSD),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "sqrtss", fcml_st_def_addr_mode_desc_SQRTSS),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "stc", fcml_st_def_addr_mode_desc_STC),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "std", fcml_st_def_addr_mode_desc_STD),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "stgi", fcml_st_def_addr_mode_desc_STGI),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "sti", fcml_st_def_addr_mode_desc_STI),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "stmxcsr", fcml_st_def_addr_mode_desc_STMXCSR),
		FCML_IA_INSTRUCTION( F_UNKNOWN, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_STOS),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "str", fcml_st_def_addr_mode_desc_STR),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "sub", fcml_st_def_addr_mode_desc_SUB),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "t1mskc", fcml_st_def_addr_mode_desc_T1MSKC),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "subpd", fcml_st_def_addr_mode_desc_SUBPD),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "subps", fcml_st_def_addr_mode_desc_SUBPS),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "subsd", fcml_st_def_addr_mode_desc_SUBSD),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "subss", fcml_st_def_addr_mode_desc_SUBSS),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "swapgs", fcml_st_def_addr_mode_desc_SWAPGS),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "syscall", fcml_st_def_addr_mode_desc_SYSCALL),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "sysenter", fcml_st_def_addr_mode_desc_SYSENTER),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "sysexit", fcml_st_def_addr_mode_desc_SYSEXIT),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "sysret", fcml_st_def_addr_mode_desc_SYSRET),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "test", fcml_st_def_addr_mode_desc_TEST),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "ucomisd", fcml_st_def_addr_mode_desc_UCOMISD),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "ucomiss", fcml_st_def_addr_mode_desc_UCOMISS),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "ud2", fcml_st_def_addr_mode_desc_UD2),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "unpckhpd", fcml_st_def_addr_mode_desc_UNPCKHPD),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "unpckhps", fcml_st_def_addr_mode_desc_UNPCKHPS),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "unpcklpd", fcml_st_def_addr_mode_desc_UNPCKLPD),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "unpcklps", fcml_st_def_addr_mode_desc_UNPCKLPS),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "vcvtph2ps", fcml_st_def_addr_mode_desc_VCVTPH2PS),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "vcvtps2ph", fcml_st_def_addr_mode_desc_VCVTPS2PH),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "verr", fcml_st_def_addr_mode_desc_VERR),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "verw", fcml_st_def_addr_mode_desc_VERW),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "vmload", fcml_st_def_addr_mode_desc_VMLOAD),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "vmmcall", fcml_st_def_addr_mode_desc_VMMCALL),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "vmrun", fcml_st_def_addr_mode_desc_VMRUN),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "vmsave", fcml_st_def_addr_mode_desc_VMSAVE),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "vpermilpd", fcml_st_def_addr_mode_desc_VPERMILPD),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "vpermilps", fcml_st_def_addr_mode_desc_VPERMILPS),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "vperm2f128", fcml_st_def_addr_mode_desc_VPERM2F128),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "vperm2i128", fcml_st_def_addr_mode_desc_VPERM2I128),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "vextracti128", fcml_st_def_addr_mode_desc_VEXTRACTI128),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "vinserti128", fcml_st_def_addr_mode_desc_VINSERTI128),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "vpsravd", fcml_st_def_addr_mode_desc_VPSRAVD),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "vpermd", fcml_st_def_addr_mode_desc_VPERMD),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "vpsllvd", fcml_st_def_addr_mode_desc_VPSLLVD),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "vpsrlvd", fcml_st_def_addr_mode_desc_VPSRLVD),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "vpermpd", fcml_st_def_addr_mode_desc_VPERMPD),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "vpermq", fcml_st_def_addr_mode_desc_VPERMQ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "vpermps", fcml_st_def_addr_mode_desc_VPERMPS),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "vtestps", fcml_st_def_addr_mode_desc_VTESTPS),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "vgatherdpd", fcml_st_def_addr_mode_desc_VGATHERDPD),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "vgatherdps", fcml_st_def_addr_mode_desc_VGATHERDPS),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "vpgatherdd", fcml_st_def_addr_mode_desc_VPGATHERDD),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "vpgatherdq", fcml_st_def_addr_mode_desc_VPGATHERDQ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "vzeroall", fcml_st_def_addr_mode_desc_VZEROALL),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "vzeroupper", fcml_st_def_addr_mode_desc_VZEROUPPER),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "wait;fwait", fcml_st_def_addr_mode_desc_WAIT),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "wbinvd", fcml_st_def_addr_mode_desc_WBINVD),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "wrfsbase", fcml_st_def_addr_mode_desc_WRFSBASE),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "wrmsr", fcml_st_def_addr_mode_desc_WRMSR),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "xadd", fcml_st_def_addr_mode_desc_XADD),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "xchg", fcml_st_def_addr_mode_desc_XCHG),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "xgetbv", fcml_st_def_addr_mode_desc_XGETBV),
		FCML_IA_INSTRUCTION( F_UNKNOWN, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_XLAT),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "xor", fcml_st_def_addr_mode_desc_XOR),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "xorpd", fcml_st_def_addr_mode_desc_XORPD),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "xorps", fcml_st_def_addr_mode_desc_XORPS),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "xrstor", fcml_st_def_addr_mode_desc_XRSTOR),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "xsave", fcml_st_def_addr_mode_desc_XSAVE),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "xsaveopt", fcml_st_def_addr_mode_desc_XSAVEOPT),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "xsetbv", fcml_st_def_addr_mode_desc_XSETBV),
		// AMD 3D Now!
		FCML_IA_INSTRUCTION( F_UNKNOWN, "femms", fcml_st_def_addr_mode_desc_FEMMS),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "pavgusb", fcml_st_def_addr_mode_desc_PAVGUSB),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "pf2id", fcml_st_def_addr_mode_desc_PF2ID),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "pfacc", fcml_st_def_addr_mode_desc_PFACC),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "pfadd", fcml_st_def_addr_mode_desc_PFADD),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "pfcmpeq", fcml_st_def_addr_mode_desc_PFCMPEQ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "pfcmpge", fcml_st_def_addr_mode_desc_PFCMPGE),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "pfcmpgt", fcml_st_def_addr_mode_desc_PFCMPGT),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "pfmax", fcml_st_def_addr_mode_desc_PFMAX),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "pfmin", fcml_st_def_addr_mode_desc_PFMIN),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "pfmul", fcml_st_def_addr_mode_desc_PFMUL),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "pfrcp", fcml_st_def_addr_mode_desc_PFRCP),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "pfrcpit1", fcml_st_def_addr_mode_desc_PFRCPIT1),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "pfrcpit2", fcml_st_def_addr_mode_desc_PFRCPIT2),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "pfrsqit1", fcml_st_def_addr_mode_desc_PFRSQIT1),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "pfrsqrt", fcml_st_def_addr_mode_desc_PFRSQRT),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "pfsub", fcml_st_def_addr_mode_desc_PFSUB),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "pfsubr", fcml_st_def_addr_mode_desc_PFSUBR),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "pi2fd", fcml_st_def_addr_mode_desc_PI2FD),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "pmulhrw", fcml_st_def_addr_mode_desc_PMULHRW),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "prefetch", fcml_st_def_addr_mode_desc_PREFETCH),
		// Extensions to the 3DNow!
		FCML_IA_INSTRUCTION( F_UNKNOWN, "pf2iw", fcml_st_def_addr_mode_desc_PF2IW),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "pfnacc", fcml_st_def_addr_mode_desc_PFNACC),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "pfpnacc", fcml_st_def_addr_mode_desc_PFPNACC),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "pi2fw", fcml_st_def_addr_mode_desc_PI2FW),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "pswapd", fcml_st_def_addr_mode_desc_PSWAPD),
		// FMA
		FCML_IA_INSTRUCTION( F_UNKNOWN, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VFMADDPD ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VFMADDPS ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VFMADDSD ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VFMADDSS ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VFMADDSUBPD ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VFMADDSUBPS ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VFMSUBADDPD ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VFMSUBADDPS ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VFMSUBPD ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VFMSUBPS ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VFMSUBSD ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VFMSUBSS ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VFNMADDPD ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VFNMADDPS ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VFNMADDSD ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VFNMADDSS ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VFNMSUBPD ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VFNMSUBPS ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VFNMSUBSD ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VFNMSUBSS ),
		// XOP
		FCML_IA_INSTRUCTION( F_UNKNOWN, "bextr", fcml_st_def_addr_mode_desc_BEXTR ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "blcfill", fcml_st_def_addr_mode_desc_BLCFILL ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "blci", fcml_st_def_addr_mode_desc_BLCI ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "blcic", fcml_st_def_addr_mode_desc_BLCIC ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "blcmsk", fcml_st_def_addr_mode_desc_BLCMSK ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "blcs", fcml_st_def_addr_mode_desc_BLCS ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "blsfill", fcml_st_def_addr_mode_desc_BLSFILL ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "blsic", fcml_st_def_addr_mode_desc_BLSIC ),
		// VEX/XOP-Encoded GPR instructions.
		FCML_IA_INSTRUCTION( F_UNKNOWN, "andn", fcml_st_def_addr_mode_desc_ANDN ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "bexr;bextr", fcml_st_def_addr_mode_desc_BEXR ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "blsi", fcml_st_def_addr_mode_desc_BLSI ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "blsmsk", fcml_st_def_addr_mode_desc_BLSMSK ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "blsr", fcml_st_def_addr_mode_desc_BLSR ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "bzhi", fcml_st_def_addr_mode_desc_BZHI ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "lzcnt", fcml_st_def_addr_mode_desc_LZCNT ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "mulx", fcml_st_def_addr_mode_desc_MULX ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "pdep", fcml_st_def_addr_mode_desc_PDEP ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "pext", fcml_st_def_addr_mode_desc_PEXT ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "rorx", fcml_st_def_addr_mode_desc_RORX ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "shlx", fcml_st_def_addr_mode_desc_SHLX ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "shrx", fcml_st_def_addr_mode_desc_SHRX ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "sarx", fcml_st_def_addr_mode_desc_SARX ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "tzcnt", fcml_st_def_addr_mode_desc_TZCNT ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "tzmsk", fcml_st_def_addr_mode_desc_TZMSK ),
		// HLE
		FCML_IA_INSTRUCTION( F_UNKNOWN, "xabort", fcml_st_def_addr_mode_desc_XABORT ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "xbegin", fcml_st_def_addr_mode_desc_XBEGIN ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "xend", fcml_st_def_addr_mode_desc_XEND ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "xtest", fcml_st_def_addr_mode_desc_XTEST ),
		// END OF HLE.
		FCML_IA_INSTRUCTION( F_UNKNOWN, "adcx", fcml_st_def_addr_mode_desc_ADCX ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "adox", fcml_st_def_addr_mode_desc_ADOX ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "rdseed", fcml_st_def_addr_mode_desc_RDSEED ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "clac", fcml_st_def_addr_mode_desc_CLAC ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "stac", fcml_st_def_addr_mode_desc_STAC ),
		// XOP
		FCML_IA_INSTRUCTION( F_UNKNOWN, "vfrczpd", fcml_st_def_addr_mode_desc_VFRCZPD ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "vfrczps", fcml_st_def_addr_mode_desc_VFRCZPS ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "vfrczsd", fcml_st_def_addr_mode_desc_VFRCZSD ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "vfrczss", fcml_st_def_addr_mode_desc_VFRCZSS ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "vpcmov", fcml_st_def_addr_mode_desc_VPCMOV ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPCOM ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPCOMU ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "vpermil2pd", fcml_st_def_addr_mode_desc_VPERMIL2PD ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "vpermil2ps", fcml_st_def_addr_mode_desc_VPERMIL2PS ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "vphaddbd", fcml_st_def_addr_mode_desc_VPHADDBD ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "vphaddbw", fcml_st_def_addr_mode_desc_VPHADDBW ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "vphaddbq", fcml_st_def_addr_mode_desc_VPHADDBQ ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "vphadddq", fcml_st_def_addr_mode_desc_VPHADDDQ ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "vphaddubd", fcml_st_def_addr_mode_desc_VPHADDUBD ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "vphaddubq", fcml_st_def_addr_mode_desc_VPHADDUBQ ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "vphaddubwd", fcml_st_def_addr_mode_desc_VPHADDUBWD ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "vphaddudq", fcml_st_def_addr_mode_desc_VPHADDUDQ ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "vphadduwd", fcml_st_def_addr_mode_desc_VPHADDUWD ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "vphadduwq", fcml_st_def_addr_mode_desc_VPHADDUWQ ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "vphaddwd", fcml_st_def_addr_mode_desc_VPHADDWD ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "vphaddwq", fcml_st_def_addr_mode_desc_VPHADDWQ ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "vphsubbw", fcml_st_def_addr_mode_desc_VPHSUBBW ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "vphsubdq", fcml_st_def_addr_mode_desc_VPHSUBDQ ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "vphsubdq", fcml_st_def_addr_mode_desc_VPHSUBDQ ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "vphsubwd", fcml_st_def_addr_mode_desc_VPHSUBWD ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "vpmacsdd", fcml_st_def_addr_mode_desc_VPMACSDD ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "vpmacsdqh", fcml_st_def_addr_mode_desc_VPMACSDQH ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "vpmacsdql", fcml_st_def_addr_mode_desc_VPMACSDQL ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "vpmacssdd", fcml_st_def_addr_mode_desc_VPMACSSDD ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "vpmacssdqh", fcml_st_def_addr_mode_desc_VPMACSSDQH ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "vpmacssdql", fcml_st_def_addr_mode_desc_VPMACSSDQL ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "vpmacsswd", fcml_st_def_addr_mode_desc_VPMACSSWD ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "vpmacssww", fcml_st_def_addr_mode_desc_VPMACSSWW ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "vpmacswd", fcml_st_def_addr_mode_desc_VPMACSWD ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "vpmacsww", fcml_st_def_addr_mode_desc_VPMACSWW ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "vpmadcsswd", fcml_st_def_addr_mode_desc_VPMADCSSWD ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "vpmadcswd", fcml_st_def_addr_mode_desc_VPMADCSWD ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "vpperm", fcml_st_def_addr_mode_desc_VPPERM ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "vprotd", fcml_st_def_addr_mode_desc_VPROTD ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "vprotb", fcml_st_def_addr_mode_desc_VPROTB ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "vprotq", fcml_st_def_addr_mode_desc_VPROTQ ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "vprotw", fcml_st_def_addr_mode_desc_VPROTW ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "vpshab", fcml_st_def_addr_mode_desc_VPSHAB ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "vpshad", fcml_st_def_addr_mode_desc_VPSHAD ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "vpshaq", fcml_st_def_addr_mode_desc_VPSHAQ ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "vpshaw", fcml_st_def_addr_mode_desc_VPSHAW ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "vpshlb", fcml_st_def_addr_mode_desc_VPSHLB ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "vpshld", fcml_st_def_addr_mode_desc_VPSHLD ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "vpshlq", fcml_st_def_addr_mode_desc_VPSHLQ ),
		FCML_IA_INSTRUCTION( F_UNKNOWN, "vpshlw", fcml_st_def_addr_mode_desc_VPSHLW ),
		{ NULL, 0, 0, NULL }
};

