/*
* fcml_def.c
*
*  Created on: 19-11-2010
*      Author: Slawomir Wojtasiak
*/

#include "fcml_def.h"

/* Instruction definitions.*/

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_AAA[] = {
    { FCML_AMT_GPI, 0x0000, 0x00440000, { 0x37, 0x00, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NO_OPERANS }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_AAD[] = {
    { FCML_AMT_GPI, 0x0000, 0x00580000, { 0xD5, 0x0A, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NO_OPERANS },
    { FCML_AMT_GPI, 0x0000, 0x00440000, { 0xD5, 0x00, 0x00 }, { FCML_OP_IB | FCML_OA_RW, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_IMM8 }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_AAM[] = {
    { FCML_AMT_GPI, 0x0000, 0x00580000, { 0xD4, 0x0A, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NO_OPERANS },
    { FCML_AMT_GPI, 0x0000, 0x00440000, { 0xD4, 0x00, 0x00 }, { FCML_OP_IB | FCML_OA_RW, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_IMM8 }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_AAS[] = {
    { FCML_AMT_GPI, 0x0000, 0x00440000, { 0x3F, 0x00, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_NO_OPERANS }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_ADC[] = {
	/* 14 ib ADC AL, int8 C Valid Valid Add with carry int8 to AL.*/
    { FCML_AMT_GPI, 0x0000, 0x00C40002, { 0x14, 0x00, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_AL, FCML_EOS_BYTE ) | FCML_OA_RW, FCML_OP_IB, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_ER8_IMM8 },
	/* 15 iw ADC AX, int16 C Valid Valid Add with carry int16 to AX.*/
	/* 15 id ADC EAX, int32 C Valid Valid Add with carry int32 to EAX.*/
	/* REX.W + 15 id ADC RAX, int32 C Valid N.E. Add with carry int32 sign extended to 64-bits to RAX.*/
    { FCML_AMT_GPI, 0x0000, 0x00C40002, { 0x15, 0x00, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_AL, FCML_EOS_EOSA ) | FCML_OA_RW, FCML_OP_EX_EOSA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_ERO_IMMO },
	/* 80 /2 ib ADC r/m8, int8 B Valid Valid Add with carry int8 to r/m8.*/
	/* REX + 80 /2 ib ADC r/m8*, int8 B Valid N.E. Add with carry int8 to r/m8.*/
    { FCML_AMT_GPI, 0x0807, 0x00C59006, { 0x80, 0x00, 0x00 }, { FCML_OP_MODRM_RM_8_RW, FCML_OP_IB, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RM8_IMM8 },
	/* 81 /2 iw ADC r/m16, int16 B Valid Valid Add with carry int16 to r/m16.*/
	/* 81 /2 id ADC r/m32, int32 B Valid Valid Add with CF int32 to r/m32.*/
	/* REX.W + 81 /2 id ADC r/m64, int32 B Valid N.E. Add with CF int32 sign extended to 64-bits to r/m64.*/
    { FCML_AMT_GPI, 0x0807, 0x00C59006, { 0x81, 0x00, 0x00 }, { FCML_OP_MODRM_RM_RW, FCML_OP_EX_EOSA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RMO_IMMO },
	/* 83 /2 ib ADC r/m16, int8 B Valid Valid Add with CF sign-extended int8 to r/m16.*/
	/* 83 /2 ib ADC r/m32, int8 B Valid Valid Add with CF sign-extended int8 into r/m32.*/
	/* REX.W + 83 /2 ib ADC r/m64, int8 B Valid N.E. Add with CF sign-extended int8 into r/m64.*/
    { FCML_AMT_GPI, 0x0807, 0x00C59006, { 0x83, 0x00, 0x00 }, { FCML_OP_MODRM_RM_RW, FCML_OP_IB_EX_EOSA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RMO_IMM8 },
	/* 10 /r ADC r/m8, r8 A Valid Valid Add with carry byte register to r/m8.*/
	/* REX + 10 /r ADC r/m8*, r8* A Valid N.E. Add with carry byte register to r/m64.*/
    { FCML_AMT_GPI, 0x0807, 0x00C48002, { 0x10, 0x00, 0x00 }, { FCML_OP_MODRM_RM_OP_8_RW, FCML_OP_MODRM_R_8, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RM8_R8 },
	/* 11 /r ADC r/m16, r16 A Valid Valid Add with carry r16 to r/m16.*/
	/* 11 /r ADC r/m32, r32 A Valid Valid Add with CF r32 to r/m32.*/
	/* REX.W + 11 /r ADC r/m64, r64 A Valid N.E. Add with CF r64 to r/m64.*/
    { FCML_AMT_GPI, 0x0807, 0x00C48002, { 0x11, 0x00, 0x00 }, { FCML_OP_MODRM_RM_OP_RW, FCML_OP_MODRM_R, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RMO_RO },
	/* 12 /r ADC r8, r/m8 A Valid Valid Add with carry r/m8 to byte register.*/
	/* REX + 12 /r ADC r8*, r/m8* A Valid N.E. Add with carry r/m64 to byte register.*/
    { FCML_AMT_GPI, 0x0000, 0x00C48002, { 0x12, 0x00, 0x00 }, { FCML_OP_MODRM_R_8_RW, FCML_OP_MODRM_RM_OP_8, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_R8_RM8 },
	/* 13 /r ADC r16, r/m16 A Valid Valid Add with carry r/m16 to r16.*/
	/* 13 /r ADC r32, r/m32 A Valid Valid Add with CF r/m32 to r32.*/
	/* REX.W + 13 /r ADC r64, r/m64 A Valid N.E. Add with CF r/m64 to r64.*/
    { FCML_AMT_GPI, 0x0000, 0x00C48002, { 0x13, 0x00, 0x00 }, { FCML_OP_MODRM_R_RW, FCML_OP_MODRM_RM_OP, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RO_RMO }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_ADD[] = {
	/* 04 ib ADD AL, int8 C Valid Valid Add int8 to AL..*/
    { FCML_AMT_GPI, 0x0000, 0x00C40002, { 0x04, 0x00, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_AL, FCML_EOS_BYTE ) | FCML_OA_RW, FCML_OP_IB, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_ER8_IMM8 },
	/* 05 iw ADD AX, int16 C Valid Valid Add int16 to AX.*/
	/* 05 id ADD EAX, int32 C Valid Valid Add int32 to EAX.*/
	/* REX.W + 05 id ADD RAX, int32 C Valid N.E. Add int32 sign-extended to 64-bits to RAX.*/
    { FCML_AMT_GPI, 0x0000, 0x00C40002, { 0x05, 0x00, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_AL, FCML_EOS_EOSA ) | FCML_OA_RW, FCML_OP_EX_EOSA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_ERO_IMMO },
	/* 80 /0 ib ADD r/m8, int8 B Valid Valid Add int8 to r/m8.*/
	/* REX + 80 /0 ib ADD r/m8*, int8 B Valid N.E. Add sign-extended int8 to r/m64.*/
    { FCML_AMT_GPI, 0x0807, 0x00C58006, { 0x80, 0x00, 0x00 }, { FCML_OP_MODRM_RM_8_RW, FCML_OP_IB, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RM8_IMM8 },
	/* 81 /0 iw ADD r/m16, int16 B Valid Valid Add int16 to r/m16.*/
	/* 81 /0 id ADD r/m32, int32 B Valid Valid Add int32 to r/m32.*/
	/* REX.W + 81 /0 id ADD r/m64, int32 B Valid N.E. Add int32 sign-extended to 64-bits to r/m64.*/
    { FCML_AMT_GPI, 0x0807, 0x00C58006, { 0x81, 0x00, 0x00 }, { FCML_OP_MODRM_RM_RW, FCML_OP_EX_EOSA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RMO_IMMO },
	/* 83 /0 ib ADD r/m16, int8 B Valid Valid Add sign-extended int8 to r/m16.*/
	/* 83 /0 ib ADD r/m32, int8 B Valid Valid Add sign-extended int8 to r/m32.*/
	/* REX.W + 83 /0 ib ADD r/m64, int8 B Valid N.E. Add sign-extended int8 to r/m64.*/
    { FCML_AMT_GPI, 0x0807, 0x00C58006, { 0x83, 0x00, 0x00 }, { FCML_OP_MODRM_RM_RW, FCML_OP_IB_EX_EOSA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RMO_IMM8 },
	/* 00 /r ADD r/m8, r8 A Valid Valid Add r8 to r/m8.*/
	/* REX + 00 /r ADD r/m8*, r8* A Valid N.E. Add r8 to r/m8.*/
    { FCML_AMT_GPI, 0x0807, 0x00C48002, { 0x00, 0x00, 0x00 }, { FCML_OP_MODRM_RM_8_RW, FCML_OP_MODRM_R_8, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RM8_R8 },
	/* 01 /r ADD r/m16, r16 A Valid Valid Add r16 to r/m16.*/
	/* 01 /r ADD r/m32, r32 A Valid Valid Add r32 to r/m32.*/
	/* REX.W + 01 /r ADD r/m64, r64 A Valid N.E. Add r64 to r/m64.*/
    { FCML_AMT_GPI, 0x0807, 0x00C48002, { 0x01, 0x00, 0x00 }, { FCML_OP_MODRM_RM_RW, FCML_OP_MODRM_R, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RMO_RO },
	/* 02 /r ADD r8, r/m8 A Valid Valid Add r/m8 to r8.*/
	/* REX + 02 /r ADD r8*, r/m8* A Valid N.E. Add r/m8 to r8.*/
    { FCML_AMT_GPI, 0x0000, 0x00C48002, { 0x02, 0x00, 0x00 }, { FCML_OP_MODRM_R_8_RW, FCML_OP_MODRM_RM_8, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_R8_RM8 },
	/* 03 /r ADD r16, r/m16 A Valid Valid Add r/m16 to r16.*/
	/* 03 /r ADD r32, r/m32 A Valid Valid Add r/m32 to r32.*/
	/* REX.W + 03 /r ADD r64, r/m64 A Valid N.E. Add r/m64 to r64.*/
    { FCML_AMT_GPI, 0x0000, 0x00C48002, { 0x03, 0x00, 0x00 }, { FCML_OP_MODRM_R_RW, FCML_OP_MODRM_RM, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RO_RMO }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_ADDPD[] = {
	/* 66 0F 58 /r ADDPD xmm1, xmm2/m128 A Valid Valid Add packed double-precision floating-point values from xmm2/m128 to xmm1.*/
    { FCML_AMT_SSE2_SIMD, 0x1000, 0x00D88000, { 0x0F, 0x58, 0x00 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VADDPD[] = {
	/* VEX.NDS.128.66.0F.WIG 58 /r VADDPD xmm1, xmm2, xmm3/m128 V/V AVX Add packed double-precision floating-point values from xmm3/mem to xmm2 and stores result in xmm1.*/
	/* VEX.NDS.256.66.0F.WIG 58 /r VADDPD ymm1, ymm2, ymm3/m256 Add packed double-precision floating-point values from ymm3/mem to ymm2 and stores result in ymm1.*/
    { FCML_AMT_AVX_SIMD, 0x1080, 0x00D88000, { 0x0F, 0x58, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_ADDPS[] = {
	/* 0F 58 /r ADDPS xmm1, xmm2/m128 A Valid Valid Add packed single-precision floating-point values from xmm2/m128 to xmm1.*/
    { FCML_AMT_SSE_SIMD, 0x0000, 0x00D88000, { 0x0F, 0x58, 0x00 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VADDPS[] = {
	/* VEX.NDS.128.0F 58 /r VADDPS xmm1,xmm2, xmm3/m128*/
	/* VEX.NDS.256.0F 58 /r VADDPS ymm1, ymm2, ymm3/m256*/
    { FCML_AMT_AVX_SIMD, 0x0080, 0x00D88000, { 0x0F, 0x58, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_ADDSD[] = {
	/* F2 0F 58 /r ADDSD xmm1, xmm2/m64 A Valid Valid Add the low doubleprecision floating-point value from xmm2/m64 to xmm1.*/
    { FCML_AMT_SSE2_SIMD, 0x2000, 0x00D88000, { 0x0F, 0x58, 0x00 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VADDSD[] = {
	/* VEX.NDS.128.F2.0F 58 /r VADDSD xmm1,xmm2,xmm3/m64*/
    { FCML_AMT_AVX_SIMD, 0x20C0, 0x00D88000, { 0x0F, 0x58, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_64, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_ADDSS[] = {
	/* F3 0F 58 /r ADDSS xmm1, xmm2/m32 A Valid Valid Add the low single-precision floating-point value from xmm2/m32 to xmm1.*/
    { FCML_AMT_SSE_SIMD, 0x4000, 0x00D88000, { 0x0F, 0x58, 0x00 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_32, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VADDSS[] = {
	/* VEX.NDS.128.F3.0F 58 /r VADDSS xmm1,xmm2, xmm3/m32*/
    { FCML_AMT_AVX_SIMD, 0x40C0, 0x00D88000, { 0x0F, 0x58, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_32, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_ADDSUBPD[] = {
	/*66 0F D0 /r ADDSUBPD xmm1, xmm2/m128 A Valid Valid Add/subtract doubleprecision floating-point values from xmm2/m128 to xmm1.*/
    { FCML_AMT_SSE3_SIMD, 0x1000, 0x00D88000, { 0x0F, 0xD0, 0x00 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VADDSUBPD[] = {
	/* VEX.NDS.128.66.0F D0 /r VADDSUBPD xmm1,xmm2,xmm3/m128*/
	/* VEX.NDS.256.66.0F D0 /r VADDSUBPD ymm1,ymm2,ymm3/m256*/
    { FCML_AMT_AVX_SIMD, 0x1080, 0x00D88000, { 0x0F, 0xD0, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_ADDSUBPS[] = {
	/* F2 0F D0 /r ADDSUBPS xmm1, xmm2/m128 A Valid Valid Add/subtract singleprecision floating-point values from xmm2/m128 to xmm1.*/
    { FCML_AMT_SSE3_SIMD, 0x2000, 0x00D88000, { 0x0F, 0xD0, 0x00 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VADDSUBPS[] = {
	/* VEX.NDS.128.F2.0F D0 /r VADDSUBPS xmm1,xmm2,xmm3/m128*/
	/* VEX.NDS.256.F2.0F D0 /r VADDSUBPS ymm1, ymm2,ymm3/m256*/
    { FCML_AMT_AVX_SIMD, 0x2080, 0x00D88000, { 0x0F, 0xD0, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_AESDEC[] = {
	/* 66 0F 38 DE /r AESDEC xmm1,xmm2/m128*/
    { FCML_AMT_AES, 0x1000, 0x00EC8000, { 0x0F, 0x38, 0xDE }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VAESDEC[] = {
	/* VEX.NDS.128.66.0F38.WIG DE /r VAESDEC xmm1,xmm2,xmm3/m128*/
    { FCML_AMT_AVX | FCML_AMT_AES, 0x10C0, 0x00EC8000, { 0x0F, 0x38, 0xDE }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_AESDECLAST[] = {
	/* 66 0F 38 DF /r AESDECLAST xmm1,xmm2/m128*/
    { FCML_AMT_AES, 0x1000, 0x00EC8000, { 0x0F, 0x38, 0xDF }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VAESDECLAST[] = {
	/* VEX.NDS.128.66.0F38.WIG DF /r VAESDECLAST xmm1,xmm2,xmm3/m128*/
    { FCML_AMT_AVX | FCML_AMT_AES, 0x10C0, 0x00EC8000, { 0x0F, 0x38, 0xDF }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_AESENC[] = {
	/* 66 0F 38 DC /r AESENC xmm1, xmm2/m128 A Valid Valid Perform one round of an AES encryption flow, operating on a 128-bit data (state) from xmm1 with a 128-bit round key from xmm2/m128.*/
    { FCML_AMT_AES, 0x1000, 0x00EC8000, { 0x0F, 0x38, 0xDC }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VAESENC[] = {
	/* VEX.NDS.128.66.0F38.WIG DC /r VAESENC xmm1, xmm2, xmm3/m128*/
    { FCML_AMT_AVX | FCML_AMT_AES, 0x10C0, 0x00EC8000, { 0x0F, 0x38, 0xDC }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_AESENCLAST[] = {
	/*66 0F 38 DD /r AESENCLAST xmm1, xmm2/m128 A Valid Valid Perform the last round of an AES encryption flow, operating on a 128-bit data (state) from xmm1 with a 128-bit round key from xmm2/m128.*/
    { FCML_AMT_AES, 0x1000, 0x00EC8000, { 0x0F, 0x38, 0xDD }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VAESENCLAST[] = {
	/* VEX.NDS.128.66.0F38.WIG DD /r VAESENCLAST xmm1,xmm2,xmm3/m128*/
    { FCML_AMT_AVX | FCML_AMT_AES, 0x10C0, 0x00EC8000, { 0x0F, 0x38, 0xDD }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_AESIMC[] = {
	/* 66 0F 38 DB /r AESIMC xmm1, xmm2/m128 A Valid Valid Perform the InvMixColumn transformation on a 128-bit round key from xmm2/m128 and store the result in xmm1.*/
    { FCML_AMT_AES, 0x1000, 0x00EC8000, { 0x0F, 0x38, 0xDB }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VAESIMC[] = {
	/* VEX.128.66.0F38.WIG DB /r VAESIMC xmm1, xmm2/m128*/
    { FCML_AMT_AVX | FCML_AMT_AES, 0x10C0, 0x00EC8000, { 0x0F, 0x38, 0xDB }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_AESKEYGENASSIST[] = {
	/* 66 0F 3A DF /r ib AESKEYGENASSIST xmm1, xmm2/m128, int8 A Valid Valid Assist in AES round key generation using an 8 bits Round Constant (RCON) specified in the immediate byte, operating on 128 bits of data specified in xmm2/m128 and stores the result in xmm1.*/
    { FCML_AMT_AES, 0x1000, 0x00EC8000, { 0x0F, 0x3A, 0xDF }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_OP_128, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VAESKEYGENASSIST[] = {
	/* VEX.128.66.0F3A.WIG DF /r ib VAESKEYGENASSIST xmm1,xmm2/m128,int8*/
    { FCML_AMT_AVX | FCML_AMT_AES, 0x10C0, 0x00EC8000, { 0x0F, 0x3A, 0xDF }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_OP_128, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_AND[] = {
	/* 24 ib AND AL, int8 C Valid Valid AL AND int8.*/
    { FCML_AMT_GPI, 0x0000, 0x00C40002, { 0x24, 0x00, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_AL, FCML_EOS_BYTE ) | FCML_OA_RW, FCML_OP_IB, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_ER8_IMM8 },
	/* 25 iw AND AX, int16 C Valid Valid AX AND int16.*/
	/* 25 id AND EAX, int32 C Valid Valid EAX AND int32.*/
	/* REX.W + 25 id AND RAX, int32 C Valid N.E. RAX AND int32 signextended to 64-bits.*/
    { FCML_AMT_GPI, 0x0000, 0x00C40002, { 0x25, 0x00, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_AL, FCML_EOS_EOSA ) | FCML_OA_RW, FCML_OP_EX_EOSA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_ERO_IMMO },
	/* 80 /4 ib AND r/m8, int8 MR Valid Valid r/m8 AND int8.*/
	/* REX + 80 /4 ib AND r/m8*, int8 MR Valid N.E. r/m8 AND int8.*/
    { FCML_AMT_GPI, 0x0807, 0x00C5A006, { 0x80, 0x00, 0x00 }, { FCML_OP_MODRM_RM_8_RW, FCML_OP_IB, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RM8_IMM8 },
	/* 81 /4 iw AND r/m16, int16 B Valid Valid r/m16 AND int16.*/
	/* 81 /4 id AND r/m32, int32 B Valid Valid r/m32 AND int32.*/
	/* REX.W + 81 /4 id AND r/m64, int32 B Valid N.E. r/m64 AND int32 sign extended to 64-bits.*/
    { FCML_AMT_GPI, 0x0807, 0x00C5A006, { 0x81, 0x00, 0x00 }, { FCML_OP_MODRM_RM_RW, FCML_OP_EX_EOSA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RMO_IMMO },
	/* 83 /4 ib AND r/m16, int8 B Valid Valid r/m16 AND int8 (signextended).*/
	/* 83 /4 ib AND r/m32, int8 B Valid Valid r/m32 AND int8 (signextended).*/
	/* REX.W + 83 /4 ib AND r/m64, int8 B Valid N.E. r/m64 AND int8 (signextended).*/
    { FCML_AMT_GPI, 0x0807, 0x00C5A006, { 0x83, 0x00, 0x00 }, { FCML_OP_MODRM_RM_RW, FCML_OP_IB_EX_EOSA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RMO_IMM8 },
	/* 20 /r AND r/m8, r8 A Valid Valid r/m8 AND r8.*/
	/* REX + 20 /r AND r/m8*, r8* A Valid N.E. r/m64 AND r8 (signextended).*/
    { FCML_AMT_GPI, 0x0807, 0x00C48002, { 0x20, 0x00, 0x00 }, { FCML_OP_MODRM_RM_OP_8_RW, FCML_OP_MODRM_R_8, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RM8_R8 },
	/* 21 /r AND r/m16, r16 A Valid Valid r/m16 AND r16.*/
	/* 21 /r AND r/m32, r32 A Valid Valid r/m32 AND r32.*/
	/* REX.W + 21 /r AND r/m64, r64 A Valid N.E. r/m64 AND r32.*/
    { FCML_AMT_GPI, 0x0807, 0x00C48002, { 0x21, 0x00, 0x00 }, { FCML_OP_MODRM_RM_OP_RW, FCML_OP_MODRM_R, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RMO_RO },
	/* 22 /r AND r8, r/m8 A Valid Valid r8 AND r/m8.*/
	/* REX + 22 /r AND r8*, r/m8* A Valid N.E. r/m64 AND r8 (signextended).*/
    { FCML_AMT_GPI, 0x0000, 0x00C48002, { 0x22, 0x00, 0x00 }, { FCML_OP_MODRM_R_8_RW, FCML_OP_MODRM_RM_OP_8, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_R8_RM8 },
	/* 23 /r AND r16, r/m16 A Valid Valid r16 AND r/m16.*/
	/* 23 /r AND r32, r/m32 A Valid Valid r32 AND r/m32.*/
	/* REX.W + 23 /r AND r64, r/m64 A Valid N.E. r64 AND r/m64.*/
    { FCML_AMT_GPI, 0x0000, 0x00C48002, { 0x23, 0x00, 0x00 }, { FCML_OP_MODRM_R_RW, FCML_OP_MODRM_RM_OP, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RO_RMO }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_ANDPD[] = {
	/* 66 0F 54 /r ANDPD xmm1, xmm2/m128 A Valid Valid Bitwise logical AND of xmm2/m128 and xmm1.*/
    { FCML_AMT_SSE2_SIMD, 0x1000, 0x00D88000, { 0x0F, 0x54, 0x00 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VANDPD[] = {
	/* VEX.NDS.128.66.0F 54 /r VANDPD xmm1,xmm2,xmm3/m128*/
	/* VEX.NDS.256.66.0F 54 /r VANDPD ymm1,ymm2,ymm3/m256*/
    { FCML_AMT_AVX_SIMD, 0x1080, 0x00D88000, { 0x0F, 0x54, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_ANDPS[] = {
	/* 0F 54 /r ANDPS xmm1, xmm2/m128 A Valid Valid Bitwise logical AND of xmm2/m128 and xmm1.*/
    { FCML_AMT_SSE_SIMD, 0x0000, 0x00D88000, { 0x0F, 0x54, 0x00 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VANDPS[] = {
	/* VEX.NDS.128.0F 54 /r VANDPS xmm1,xmm2, xmm3/m128*/
	/* VEX.NDS.256.0F 54 /r VANDPS ymm1, ymm2, ymm3/m256*/
    { FCML_AMT_AVX_SIMD, 0x0080, 0x00D88000, { 0x0F, 0x54, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_ANDNPD[] = {
	/* 66 0F 55 /r ANDNPD xmm1, xmm2/m128 A Valid Valid Bitwise logical AND NOT of xmm2/m128 and xmm1.*/
    { FCML_AMT_SSE2_SIMD, 0x1000, 0x00D88000, { 0x0F, 0x55, 0x00 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VANDNPD[] = {
	/* VEX.NDS.128.66.0F 55 /r VANDNPD xmm1,xmm2,xmm3/m128*/
	/* VEX.NDS.256.66.0F 55 /r VANDNPD ymm1,ymm2,ymm3/m256*/
    { FCML_AMT_AVX_SIMD, 0x1080, 0x00D88000, { 0x0F, 0x55, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_ANDNPS[] = {
	/* 0F 55 /r ANDNPS xmm1, xmm2/m128 A Valid Valid Bitwise logical AND NOT of xmm2/m128 and xmm1.*/
    { FCML_AMT_SSE_SIMD, 0x0000, 0x00D88000, { 0x0F, 0x55, 0x00 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VANDNPS[] = {
	/* VEX.NDS.128.0F 55 /r VANDNPS xmm1,xmm2,xmm3/m128*/
	/* VEX.NDS.256.0F 55 /r VANDNPS ymm1,ymm2,ymm3/m256*/
    { FCML_AMT_AVX_SIMD, 0x0080, 0x00D88000, { 0x0F, 0x55, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_ARPL[] = {
	/* 63 /r ARPL r/m16, r16 A N. E. Valid Adjust RPL of r/m16 to not less than RPL of r16.*/
    { FCML_AMT_SYSTEM, 0x0000, 0x00448000, { 0x63, 0x00, 0x00 }, { FCML_OP_MODRM_RM_OP_16_W, FCML_OP_MODRM_R_16, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_BLENDPD[] = {
	/* 66 0F 3A 0D /r ib BLENDPD xmm1, xmm2/m128, int8 A Valid Valid Select packed DP-FP values from xmm1 and xmm2/m128 from mask specified in int8 and store the values into xmm1.*/
    { FCML_AMT_SSE41_SIMD, 0x1000, 0x00EC8000, { 0x0F, 0x3A, 0x0D }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_128, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VBLENDPD[] = {
	/* VEX.NDS.128.66.0F3A 0D /r ib VBLENDPD xmm1,xmm2,xmm3/m128,int8*/
	/* VEX.NDS.256.66.0F3A 0D /r ib VBLENDPD ymm1,ymm2,ymm3/m256,int8*/
    { FCML_AMT_AVX_SIMD, 0x1080, 0x00EC8000, { 0x0F, 0x3A, 0x0D }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_OP_IB, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_BLENDPS[] = {
	/* 66 0F 3A 0C /r ib BLENDPS xmm1, xmm2/m128, int8 A Valid Valid Select packed single precision floating-point values from xmm1 and xmm2/m128 from mask specified in int8 and store the values into xmm1.*/
    { FCML_AMT_SSE41_SIMD, 0x1000, 0x00EC8000, { 0x0F, 0x3A, 0x0C }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_128, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VBLENDPS[] = {
	/* VEX.NDS.128.66.0F3A 0C /r ib VBLENDPS xmm1,xmm2,xmm3/m128,int8*/
	/* VEX.NDS.256.66.0F3A 0C /r ib VBLENDPS ymm1,ymm2,ymm3/m256,int8*/
    { FCML_AMT_AVX_SIMD, 0x1080, 0x00EC8000, { 0x0F, 0x3A, 0x0C }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_OP_IB, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_BLENDVPD[] = {
	/* 66 0F 38 15 /r BLENDVPD xmm1, xmm2/m128 , <XMM0> A Valid Valid Select packed DP FP values from xmm1 and xmm2 from mask specified in XMM0 and store the values in xmm1.*/
    { FCML_AMT_SSE41_SIMD, 0x1000, 0x00EC8000, { 0x0F, 0x38, 0x15 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_OP_128, FCML_OP_EXPLICIT_REG( FCML_REG_SIMD, FCML_REG_XMM0, FCML_EOS_XWORD ), FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VBLENDVPD[] = {
	/* VEX.NDS.128.66.0F3A 4B /r /is4 VBLENDVPD xmm1, xmm2, xmm3/m128, xmm4*/
	/* VEX.NDS.256.66.0F3A 4B /r /is4 VBLENDVPD ymm1, ymm2, ymm3/m256, ymm4*/
    { FCML_AMT_AVX_SIMD, 0x1080, 0x00EC8000, { 0x0F, 0x3A, 0x4B }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_OP_OPERAND_IS4, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_BLENDVPS[] = {
	/* 66 0F 38 14 /r BLENDVPS xmm1, xmm2/m128, <XMM0> A Valid Valid Select packed single precision floating-point values from xmm1 and xmm2/m128 from mask specified in XMM0 and store the values into xmm1.*/
    { FCML_AMT_SSE41_SIMD, 0x1000, 0x00EC8000, { 0x0F, 0x38, 0x14 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_128, FCML_OP_EXPLICIT_REG( FCML_REG_SIMD, FCML_REG_XMM0, FCML_EOS_XWORD ), FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VBLENDVPS[] = {
	/* VEX.NDS.128.66.0F3A 4A /r /is4 VBLENDVPS xmm1, xmm2, xmm3/m128, xmm4*/
	/* VEX.NDS.256.66.0F3A 4A /r /is4 VBLENDVPS ymm1, ymm2, ymm3/m256, ymm4*/
    { FCML_AMT_AVX_SIMD, 0x1080, 0x00EC8000, { 0x0F, 0x3A, 0x4A }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_OP_OPERAND_IS4, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_BOUND[] = {
	/* 62 /r BOUND r16, m16&16 A Invalid Valid Check if r16 (array index) is within bounds specified by m16&16.*/
	/* 62 /r BOUND r32, m32&32 A Invalid Valid Check if r32 (array index) is within bounds specified by m16&16.*/
    { FCML_AMT_GPI | FCML_AMT_CTI, 0x0000, 0x00448000, { 0x62, 0x00, 0x00 }, { FCML_OP_MODRM_R, FCML_OP_MODRM_MM_OP_OSA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_BSF[] = {
	/* 0F BC /r BSF r16, r/m16 A Valid Valid Bit scan forward on r/m16.*/
	/* 0F BC /r BSF r32, r/m32 A Valid Valid Bit scan forward on r/m32.*/
	/* REX.W + 0F BC BSF r64, r/m64 A Valid N.E. Bit scan forward on r/m64.*/
    { FCML_AMT_GPI, 0x0000, 0x00D88000, { 0x0F, 0xBC, 0x00 }, { FCML_OP_MODRM_R_W, FCML_OP_MODRM_RM_OP, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_BSR[] = {
	/* 0F BD /r BSR r16, r/m16 A Valid Valid Bit scan reverse on r/m16.*/
	/* 0F BD /r BSR r32, r/m32 A Valid Valid Bit scan reverse on r/m32.*/
	/* REX.W + 0F BD BSR r64, r/m64 A Valid N.E. Bit scan reverse on r/m64.*/
    { FCML_AMT_GPI, 0x0000, 0x00D88000, { 0x0F, 0xBC, 0x00 }, { FCML_OP_MODRM_R_W, FCML_OP_MODRM_RM_OP, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_BSWAP[] = {
	/* 0F C8+rd BSWAP r32 A Valid* Valid Reverses the byte order of a 32-bit register.*/
    { FCML_AMT_GPI, 0x0010, 0x03D80001, { 0x0F, 0xC8, 0x00 }, { FCML_OP_OPCODE_REG( FCML_REG_GPR, FCML_EOS_DWORD ) | FCML_OA_RW, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* REX.W + 0F C8+rd BSWAP r64 A Valid N.E. Reverses the byte order of a 64-bit register.*/
    { FCML_AMT_GPI, 0x0008, 0x04980001, { 0x0F, 0xC8, 0x00 }, { FCML_OP_OPCODE_REG( FCML_REG_GPR, FCML_EOS_QWORD ) | FCML_OA_RW, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_BT[] = {
	/* 0F A3 BT r/m16, r16 A Valid Valid Store selected bit in CF flag.*/
	/* 0F A3 BT r/m32, r32 A Valid Valid Store selected bit in CF flag.*/
	/* REX.W + 0F A3 BT r/m64, r64 A Valid N.E. Store selected bit in CF flag.*/
    { FCML_AMT_GPI, 0x0000, 0x00D88000, { 0x0F, 0xA3, 0x00 }, { FCML_OP_MODRM_RM_OP, FCML_OP_MODRM_R, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RMO_RO },
	/* 0F BA /4 ib BT r/m16, int8 B Valid Valid Store selected bit in CF flag.*/
	/* 0F BA /4 ib BT r/m32, int8 B Valid Valid Store selected bit in CF flag.*/
	/* REX.W + 0F BA /4 ib BT r/m64, int8 B Valid N.E. Store selected bit in CF flag.*/
    { FCML_AMT_GPI, 0x0000, 0x00D9A000, { 0x0F, 0xBA, 0x00 }, { FCML_OP_MODRM_RM, FCML_OP_IB, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RMO_IMM8 }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_BTC[] = {
	/* 0F BB BTC r/m16, r16 A Valid Valid Store selected bit in CF flag and complement.*/
	/* 0F BB BTC r/m32, r32 A Valid Valid Store selected bit in CF flag and complement.*/
	/* REX.W + 0F BB BTC r/m64, r64 A Valid N.E. Store selected bit in CF flag and complement.*/
    { FCML_AMT_GPI, 0x0807, 0x00D88000, { 0x0F, 0xBB, 0x00 }, { FCML_OP_MODRM_RM_OP, FCML_OP_MODRM_R, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RMO_RO },
	/* 0F BA /7 ib BTC r/m16, int8 B Valid Valid Store selected bit in CF flag and complement.*/
	/* 0F BA /7 ib BTC r/m32, int8 B Valid Valid Store selected bit in CF flag and complement.*/
	/* REX.W + 0F BA /7 ib BTC r/m64, int8 B Valid N.E. Store selected bit in CF flag and complement.*/
    { FCML_AMT_GPI, 0x0807, 0x00D9B800, { 0x0F, 0xBA, 0x00 }, { FCML_OP_MODRM_RM, FCML_OP_IB, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RMO_IMM8 }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_BTR[] = {
	/* 0F B3 BTR r/m16, r16 A Valid Valid Store selected bit in CF flag and clear.*/
	/* 0F B3 BTR r/m32, r32 A Valid Valid Store selected bit in CF flag and clear.*/
	/* REX.W + 0F B3 BTR r/m64, r64 A Valid N.E. Store selected bit in CF flag and clear.*/
    { FCML_AMT_GPI, 0x0807, 0x00D88000, { 0x0F, 0xB3, 0x00 }, { FCML_OP_MODRM_RM_RW, FCML_OP_MODRM_R, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RMO_RO },
	/* 0F BA /6 ib BTR r/m16, int8 B Valid Valid Store selected bit in CF flag and clear.*/
	/* 0F BA /6 ib BTR r/m32, int8 B Valid Valid Store selected bit in CF flag and clear.*/
	/* REX.W + 0F BA /6 ib BTR r/m64, int8 B Valid N.E. Store selected bit in CF flag and clear.*/
    { FCML_AMT_GPI, 0x0807, 0x00D9B000, { 0x0F, 0xBA, 0x00 }, { FCML_OP_MODRM_RM_RW, FCML_OP_IB, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RMO_IMM8 }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_BTS[] = {
	/* 0F AB BTS r/m16, r16 A Valid Valid Store selected bit in CF flag and set.*/
	/* 0F AB BTS r/m32, r32 A Valid Valid Store selected bit in CF flag and set.*/
	/* REX.W + 0F AB BTS r/m64, r64 A Valid N.E. Store selected bit in CF flag and set.*/
    { FCML_AMT_GPI, 0x0807, 0x00D88000, { 0x0F, 0xAB, 0x00 }, { FCML_OP_MODRM_RM_OP_RW, FCML_OP_MODRM_R, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RMO_RO },
	/* 0F BA /5 ib BTS r/m16, int8 B Valid Valid Store selected bit in CF flag and set.*/
	/* 0F BA /5 ib BTS r/m32, int8 B Valid Valid Store selected bit in CF flag and set.*/
	/* REX.W + 0F BA /5 ib BTS r/m64, int8 B Valid N.E. Store selected bit in CF flag and set.*/
    { FCML_AMT_GPI, 0x0807, 0x00D9A800, { 0x0F, 0xBA, 0x00 }, { FCML_OP_MODRM_RM_RW, FCML_OP_IB, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RMO_IMM8 }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_CALL[] = {
	/* E8 cw CALL rel16 B N.S. Valid Call near, relative, displacement relative to next instruction.*/
	/* E8 cd CALL rel32 B Valid Valid Call near, relative, displacement relative to next instruction.*/
	/* 32-bit displacement sign extended to 64-bits in 64-bit mode.*/
    { FCML_AMT_GPI | FCML_AMT_CTI | FCML_AMT_BRANCH, 0x0000, 0x40C40000, { 0xE8, 0x00, 0x00 }, { FCML_OP_IMMEDIATE_DIS_RELATIVE_EOSA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_REL0 },
	/* FF /2 CALL r/m16 B N.E. Valid Call near, absolute indirect, address given in r/m16.*/
	/* FF /2 CALL r/m32 B N.E. Valid Call near, absolute indirect, address given in r/m32.*/
	/* FF /2 CALL r/m64 B Valid N.E. Call near, absolute indirect, address given in r/m64.*/
    { FCML_AMT_GPI | FCML_AMT_CTI | FCML_AMT_BRANCH, 0x0000, 0x40C59000, { 0xFF, 0x00, 0x00 }, { FCML_OP_MODRM_RM_I, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RMO },
	/* 9A cd CALL ptr16:16 A Invalid Valid Call far, absolute, address given in operand.*/
	/* 9A cp CALL ptr16:32 A Invalid Valid Call far, absolute, address given in operand.*/
    { FCML_AMT_GPI | FCML_AMT_CTI | FCML_AMT_BRANCH, 0x0000, 0x00440000, { 0x9A, 0x00, 0x00 }, { FCML_OP_FAR_POINTER, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_PTR16_O },
	/* FF /3 CALL m16:16 B Valid Valid Call far, absolute indirect address given in m16:16.*/
	/* FF /3 CALL m16:32 B Valid Valid In 64-bit mode.*/
	/* REX.W + FF /3 CALL m16:64 B Valid N.E. In 64-bit mode.*/
    { FCML_AMT_GPI | FCML_AMT_CTI | FCML_AMT_BRANCH, 0x0000, 0x00C59800, { 0xFF, 0x00, 0x00 }, { FCML_OP_MODRM_M_FPI, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_M16_O }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_CBW[] = {
	/* 98 CBW A Valid Valid AX  sign-extend of AL.*/
    { FCML_AMT_GPI, 0x0000, 0x00C40000, { 0x98, 0x00, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_CLC[] = {
	/* F8 CLC A Valid Valid Clear CF flag.*/
    { FCML_AMT_GPI, 0x0000, 0x00C40000, { 0xF8, 0x00, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_CLD[] = {
	/* F8 CLC A Valid Valid Clear CF flag.*/
    { FCML_AMT_GPI, 0x0000, 0x00C40000, { 0xFC, 0x00, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_CLFLUSH[] = {
	/* 0F AE /7 CLFLUSH m8 A Valid Valid Flushes cache line containing m8.*/
    { FCML_AMT_SSE2, 0x0000, 0x00D9B800, { 0x0F, 0xAE, 0x00 }, { FCML_OP_MODRM_M_OP_8_W, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_CLI[] = {
	/* FA CLI A Valid Valid Clear interrupt flag interrupts disabled when interrupt flag cleared.*/
    { FCML_AMT_GPI, 0x0000, 0x00C40000, { 0xFA, 0x00, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_CLGI[] = {
	/* CLGI 0F 01 DD Clears the global interrupt flag (GIF).*/
    { FCML_AMT_SVM, 0x0000, 0x00EC0000, { 0x0F, 0x01, 0xDD }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_CLTS[] = {
	/* 0F 06 CLTS A Valid Valid Clears TS flag in CR0.*/
    { FCML_AMT_SYSTEM, 0x0000, 0x00D80000, { 0x0F, 0x06, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_CMC[] = {
	/* F5 CMC A Valid Valid Complement CF flag. Op/En*/
    { FCML_AMT_GPI, 0x0000, 0x00C40000, { 0xF5, 0x00, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_CMOV[] = {
	/* 0F 4X /r CMOVA r16, r/m16 A Valid Valid Move if above (CF=0 and ZF=0).*/
	/* 0F 4X /r CMOVA r32, r/m32 A Valid Valid Move if above (CF=0 and ZF=0).*/
	/* REX.W + 0F 4X /r CMOVA r64, r/m64 A Valid N.E. Move if above (CF=0 and ZF=0).*/
    { FCML_AMT_EDX | FCML_AMT_GPI, 0x0000, 0x00D88040, { 0x0F, 0x40, 0x00 }, { FCML_OP_MODRM_R_RW, FCML_OP_MODRM_RM_OP, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_JCXZ[] = {
	/* E3 cb JCXZ rel8 A N.E. Valid Jump short if CX register is 0.*/
	/* E3 cb JECXZ rel8 A Valid Valid Jump short if ECX register is 0.*/
	/* E3 cb JRCXZ rel8 A Valid N.E. Jump short if RCX register is 0.*/
    { FCML_AMT_GPI, 0x0000, 0x40C40000, { 0xE3, 0x00, 0x00 }, { FCML_OP_IMMEDIATE_DIS_RELATIVE_R_8, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_JCC[] = {
	/* JA rel8 A Valid Valid Jump short if ...*/
    { FCML_AMT_GPI | FCML_AMT_CTI | FCML_AMT_BRANCH, 0x0000, 0x40C40040, { 0x70, 0x00, 0x00 }, { FCML_OP_IMMEDIATE_DIS_RELATIVE_R_8, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* JA rel32 A Valid Valid Jump near if ...*/
	/* JAE rel16 A N.S. Valid Jump near if ...*/
    { FCML_AMT_GPI | FCML_AMT_CTI | FCML_AMT_BRANCH, 0x0000, 0x40D80040, { 0x0F, 0x80, 0x00 }, { FCML_OP_IMMEDIATE_DIS_RELATIVE_EOSA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_JMP[] = {
	/* EB cb JMP rel8 A Valid Valid Jump short, RIP = RIP + 8-bit displacement sign extended to 64-bits*/
    { FCML_AMT_GPI | FCML_AMT_CTI | FCML_AMT_BRANCH, 0x0000, 0x40C40000, { 0xEB, 0x00, 0x00 }, { FCML_OP_IMMEDIATE_DIS_RELATIVE_R_8, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_REL8 },
	/* E9 cw JMP rel16 A N.S. Valid Jump near, relative, displacement relative to next instruction. Not supported in 64-bit mode.*/
	/* E9 cd JMP rel32 A Valid Valid Jump near, relative, RIP = RIP + 32-bit displacement sign extended to 64-bits*/
    { FCML_AMT_GPI | FCML_AMT_CTI | FCML_AMT_BRANCH, 0x0000, 0x40C40000, { 0xE9, 0x00, 0x00 }, { FCML_OP_IMMEDIATE_DIS_RELATIVE_EOSA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_REL0 },
	/* FF /4 JMP r/m16 B N.S. Valid Jump near, absolute indirect, address = zero-extended r/m16. Not supported in 64- bit mode.*/
	/* FF /4 JMP r/m32 B N.S. Valid Jump near, absolute indirect, address given in r/m32. Not supported in 64-bit mode.*/
	/* FF /4 JMP r/m64 B Valid N.E. Jump near, absolute indirect, RIP = 64-Bit offset from register or memory*/
    { FCML_AMT_GPI | FCML_AMT_CTI | FCML_AMT_BRANCH, 0x0000, 0x40C5A000, { 0xFF, 0x00, 0x00 }, { FCML_OP_MODRM_RM_I, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RMO },
	/* EA cd JMP ptr16:16 A Inv. Valid Jump far, absolute, address given in operand*/
	/* EA cp JMP ptr16:32 A Inv. Valid Jump far, absolute, address given in operand*/
    { FCML_AMT_GPI | FCML_AMT_CTI | FCML_AMT_BRANCH, 0x0000, 0x00440000, { 0xEA, 0x00, 0x00 }, { FCML_OP_FAR_POINTER, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_PTR16_O },
	/* FF /5 JMP m16:16 A Valid Valid Jump far, absolute indirect, address given in m16:16*/
	/* FF /5 JMP m16:32 A Valid Valid Jump far, absolute indirect, address given in m16:32.*/
	/* REX.W + FF /5 JMP m16:64 A Valid N.E. Jump far, absolute indirect, address given in m16:64.*/
    { FCML_AMT_GPI | FCML_AMT_CTI | FCML_AMT_BRANCH, 0x0000, 0x00C5A800, { 0xFF, 0x00, 0x00 }, { FCML_OP_MODRM_M_FPI, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_M16_O }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_CMP[] = {
	/* 3C ib CMP AL, int8 D Valid Valid Compare int8 with AL.*/
    { FCML_AMT_GPI, 0x0000, 0x00C40002, { 0x3C, 0x00, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_AL, FCML_EOS_BYTE ) | FCML_OA_RW, FCML_OP_IB, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_ER8_IMM8 },
	/* 3D iw CMP AX, int16 D Valid Valid Compare int16 with AX.*/
	/* 3D id CMP EAX, int32 D Valid Valid Compare int32 with EAX.*/
	/* REX.W + 3D id CMP RAX, int32 D Valid N.E. Compare int32 sign extended to 64-bits with RAX.*/
    { FCML_AMT_GPI, 0x0000, 0x00C40002, { 0x3D, 0x00, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_AL, FCML_EOS_EOSA ) | FCML_OA_RW, FCML_OP_EX_EOSA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_ERO_IMMO },
	/* 80 /7 ib CMP r/m8, int8 C Valid Valid Compare int8 with r/m8.*/
	/* REX + 80 /7 ib CMP r/m8*, int8 C Valid N.E. Compare int8 with r/m8.*/
    { FCML_AMT_GPI, 0x0000, 0x00C5B806, { 0x80, 0x00, 0x00 }, { FCML_OP_MODRM_RM_8_RW, FCML_OP_IB, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RM8_IMM8 },
	/* 81 /7 iw CMP r/m16, int16 C Valid Valid Compare int16 with r/m16.*/
	/* 81 /7 id CMP r/m32, int32 C Valid Valid Compare int32 with r/m32.*/
	/* REX.W + 81 /7 id CMP r/m64, int32 C Valid N.E. Compare int32 sign extended to 64-bits with r/m64.*/
    { FCML_AMT_GPI, 0x0000, 0x00C5B806, { 0x81, 0x00, 0x00 }, { FCML_OP_MODRM_RM_RW, FCML_OP_EX_EOSA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RMO_IMMO },
	/* 83 /7 ib CMP r/m16, int8 C Valid Valid Compare int8 with r/m16.*/
	/* 83 /7 ib CMP r/m32, int8 C Valid Valid Compare int8 with r/m32.*/
	/* REX.W + 83 /7 ib CMP r/m64, int8 C Valid N.E. Compare int8 with r/m64.*/
    { FCML_AMT_GPI, 0x0000, 0x00C5B806, { 0x83, 0x00, 0x00 }, { FCML_OP_MODRM_RM_RW, FCML_OP_IB_EX_EOSA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RMO_IMM8 },
	/* 38 /r CMP r/m8, r8 B Valid Valid Compare r8 with r/m8.*/
	/* REX + 38 /r CMP r/m8*, r8* B Valid N.E. Compare r8 with r/m8.*/
    { FCML_AMT_GPI, 0x0000, 0x00C48002, { 0x38, 0x00, 0x00 }, { FCML_OP_MODRM_RM_OP_8_RW, FCML_OP_MODRM_R_8, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RM8_R8 },
	/* 39 /r CMP r/m16, r16 B Valid Valid Compare r16 with r/m16.*/
	/* 39 /r CMP r/m32, r32 B Valid Valid Compare r32 with r/m32.*/
	/* REX.W + 39 /r CMP r/m64,r64 B Valid N.E. Compare r64 with r/m64.*/
    { FCML_AMT_GPI, 0x0000, 0x00C48002, { 0x39, 0x00, 0x00 }, { FCML_OP_MODRM_RM_OP_RW, FCML_OP_MODRM_R, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RMO_RO },
	/* 3A /r CMP r8, r/m8 A Valid Valid Compare r/m8 with r8.*/
	/* REX + 3A /r CMP r8*, r/m8* A Valid N.E. Compare r/m8 with r8.*/
    { FCML_AMT_GPI, 0x0000, 0x00C48002, { 0x3A, 0x00, 0x00 }, { FCML_OP_MODRM_R_8_RW, FCML_OP_MODRM_RM_OP_8, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_R8_RM8 },
	/* 3B /r CMP r16, r/m16 A Valid Valid Compare r/m16 with r16.*/
	/* 3B /r CMP r32, r/m32 A Valid Valid Compare r/m32 with r32.*/
	/* REX.W + 3B /r CMP r64, r/m64 A Valid N.E. Compare r/m64 with r64.*/
    { FCML_AMT_GPI, 0x0000, 0x00C48002, { 0x3B, 0x00, 0x00 }, { FCML_OP_MODRM_R_RW, FCML_OP_MODRM_RM_OP, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RO_RMO }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_CMPPD[] = {
	/* 66 0F C2 /r ib CMPPD xmm1, xmm2/m128, int8 A Valid Valid Compare packed doubleprecision floating-point values in xmm2/m128 and xmm1 using int8 as comparison predicate.*/
    { FCML_AMT_SSE2_SIMD, 0x1000, 0x00D88000, { 0x0F, 0xC2, 0x00 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_128, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VCMPPD[] = {
	/* VEX.NDS.128.66.0F C2 /r ib VCMPPD xmm1, xmm2, xmm3/m128, int8*/
	/* VEX.NDS.256.66.0F C2 /r ib VCMPPD ymm1, ymm2, ymm3/m256, int8*/
    { FCML_AMT_AVX_SIMD, 0x1080, 0x00D88000, { 0x0F, 0xC2, 0x0C }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_OP_IB, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_CMPPS[] = {
	/* 0F C2 /r ib CMPPS xmm1, xmm2/m128, int8 A Valid Valid Compare packed singleprecision floating-point values in xmm2/mem and xmm1 using int8 as comparison predicate.*/
    { FCML_AMT_SSE_SIMD, 0x0000, 0x00D88000, { 0x0F, 0xC2, 0x00 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_128, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VCMPPS[] = {
	/* VEX.NDS.128.0F C2 /r ib VCMPPS xmm1, xmm2, xmm3/m128, int8*/
	/* VEX.NDS.256.0F C2 /r ib VCMPPS ymm1, ymm2, ymm3/m256, int8*/
    { FCML_AMT_AVX_SIMD, 0x0080, 0x00D88000, { 0x0F, 0xC2, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_OP_IB, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_CMPS[] = {
	/* A6 CMPS m8, m8 A Valid Valid For legacy mode, compare byte at address DS:(E)SI with byte at address ES:(E)DI; For 64-bit mode compare byte at address (R|E)SI to byte at address (R|E)DI. The status flags are set accordingly.*/
    { FCML_AMT_GPI, 0x0002, 0x00C40000, { 0xA6, 0x00, 0x00 }, { FCML_OP_EXPLICIT_GPS_REG_ADDRESSING( FCML_REG_SI, FCML_EOS_BYTE, FCML_SEG_ENCODE_REGISTER( FCML_REG_DS, FCML_SEG_ALLOW_OVERRIDE ) ), FCML_OP_EXPLICIT_GPS_REG_ADDRESSING( FCML_REG_DI, FCML_EOS_BYTE, FCML_SEG_ENCODE_REGISTER( FCML_REG_ES, FCML_SEG_DENY_OVERRIDE ) ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_M8_M8 },
	/* A7 CMPS m16, m16 A Valid Valid For legacy mode, compare word at address DS:(E)SI with word at address ES:(E)DI; For 64-bit mode compare word at address (R|E)SI with word at address (R|E)DI. The status flags are set accordingly.*/
	/* A7 CMPS m32, m32 A Valid Valid For legacy mode, compare dword at address DS:(E)SI at dword at address ES:(E)DI; For 64-bit mode compare dword at address (R|E)SI at dword at address (R|E)DI. The status flags are set accordingly.*/
	/* REX.W + A7 CMPS m64, m64 A Valid N.E. Compares quadword at address (R|E)SI with quadword at address (R|E)DI and sets the status flags accordingly.*/
    { FCML_AMT_GPI, 0x0002, 0x00C40000, { 0xA7, 0x00, 0x00 }, { FCML_OP_EXPLICIT_GPS_REG_ADDRESSING( FCML_REG_SI, FCML_EOS_EOSA, FCML_SEG_ENCODE_REGISTER( FCML_REG_DS, FCML_SEG_ALLOW_OVERRIDE ) ), FCML_OP_EXPLICIT_GPS_REG_ADDRESSING( FCML_REG_DI, FCML_EOS_EOSA, FCML_SEG_ENCODE_REGISTER( FCML_REG_ES, FCML_SEG_DENY_OVERRIDE ) ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_MO_MO }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_CMPSD[] = {
	/* F2 0F C2 /r ib CMPSD xmm1, xmm2/m64, int8 A Valid Valid Compare low double precision floating-point value in xmm2/m64 and xmm1 using int8 as comparison predicate.*/
    { FCML_AMT_SSE2_SIMD, 0x2000, 0x00D88000, { 0x0F, 0xC2, 0x00 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_64, FCML_OP_PSEUDO_OP( 0x07 ), FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VCMPSD[] = {
    /* VEX.NDS.128.F2.0F C2 /r ib VCMPSD xmm1, xmm2, xmm3/m64, int8*/
    { FCML_AMT_AVX_SIMD, 0x20C0, 0x00D88000, { 0x0F, 0xC2, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_64, FCML_OP_PSEUDO_OP( 0x1F ), FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_CMPSS[] = {
	/* F3 0F C2 /r ib CMPSS xmm1, xmm2/m32, int8 A Valid Valid Compare low singleprecision floating-point value in xmm2/m32 and xmm1 using int8 as comparison predicate.*/
    { FCML_AMT_SSE_SIMD, 0x4000, 0x00DA8000, { 0x0F, 0xC2, 0x00 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_32, FCML_OP_PSEUDO_OP( 0x07 ), FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VCMPSS[] = {
	/* VEX.NDS.128.F3.0F C2 /r ib VCMPSS xmm1, xmm2, xmm3/m32, int8*/
    { FCML_AMT_AVX_SIMD, 0x40C0, 0x00DA8000, { 0x0F, 0xC2, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_32, FCML_OP_PSEUDO_OP( 0x1F ), FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_CMPXCHG[] = {
	/* 0F B0/r CMPXCHG r/m8, r8 A Valid Valid* Compare AL with r/m8. If equal, ZF is set and r8 is loaded into r/m8. Else, clear ZF and load r/m8 into AL.*/
	/* REX + 0F B0/r CMPXCHG r/m8**,r8 A Valid N.E. Compare AL with r/m8. If equal, ZF is set and r8 is loaded into r/m8. Else, clear ZF and load r/m8 into AL.*/
    { FCML_AMT_GPI, 0x0807, 0x00D88000, { 0x0F, 0xB0, 0x00 }, { FCML_OP_MODRM_RM_OP_8_RW, FCML_OP_MODRM_R_8, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RM8_R8 },
	/* 0F B1/r CMPXCHG r/m16, r16 A Valid Valid* Compare AX with r/m16. If equal, ZF is set and r16 is loaded into r/m16. Else, clear ZF and load r/m16 into AX.*/
	/* 0F B1/r CMPXCHG r/m32, r32 A Valid Valid* Compare EAX with r/m32. If equal, ZF is set and r32 is loaded into r/m32. Else, clear ZF and load r/m32 into EAX.*/
	/* REX.W + 0F B1/r CMPXCHG r/m64, r64 A Valid N.E. Compare RAX with r/m64. If equal, ZF is set and r64 is loaded into r/m64. Else, clear ZF and load r/m64 into RAX.*/
    { FCML_AMT_GPI, 0x0807, 0x00D88000, { 0x0F, 0xB1, 0x00 }, { FCML_OP_MODRM_RM_OP_RW, FCML_OP_MODRM_R, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RMO_RO }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_CMPXCHGXB[] = {
	/* 0F C7 /1 m64 CMPXCHG8B m64 A Valid Valid* Compare EDX:EAX with m64. If equal, set ZF and load ECX:EBX into m64. Else, clear ZF and load m64 into EDX:EAX.*/
	/* REX.W + 0F C7 /1 m128 CMPXCHG16B m128 A Valid N.E. Compare RDX:RAX with m128. If equal, set ZF and load RCX:RBX into m128. Else, clear ZF and load m128 into RDX:RAX.*/
    { FCML_AMT_GPI, 0x0807, 0x03D98800, { 0x0F, 0xC7, 0x00 }, { FCML_OP_MODRM_M_OP_64_RW, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_M64 },
    { FCML_AMT_GPI, 0x0001, 0x04998800, { 0x0F, 0xC7, 0x00 }, { FCML_OP_MODRM_M_OP_128_RW, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_M128 }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_COMISD[] = {
	/* 66 0F 2F /r COMISD xmm1, xmm2/m64 A Valid Valid Compare low doubleprecision floating-point values in xmm1 and xmm2/mem64 and set the EFLAGS flags accordingly.*/
    { FCML_AMT_SSE2_SIMD, 0x1000, 0x00D88000, { 0x0F, 0x2F, 0x00 }, { FCML_OP_MODRM_R_XMM, FCML_OP_MODRM_RM_XMM_OP_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VCOMISD[] = {
	/* VEX.128.66.0F 2F /r VCOMISD xmm1, xmm2/m64*/
    { FCML_AMT_AVX_SIMD, 0x10C0, 0x00D88000, { 0x0F, 0x2F, 0x00 }, { FCML_OP_MODRM_R_XMM, FCML_OP_MODRM_RM_XMM_OP_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_COMISS[] = {
	/* 0F 2F /r COMISS xmm1, xmm2/m32 A Valid Valid Compare low singleprecision floating-point values in xmm1 and xmm2/mem32 and set the EFLAGS flags accordingly.*/
    { FCML_AMT_SSE_SIMD, 0x0000, 0x00D88000, { 0x0F, 0x2F, 0x00 }, { FCML_OP_MODRM_R_XMM, FCML_OP_MODRM_RM_XMM_OP_32, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VCOMISS[] = {
	/* VEX.128.0F 2F /r VCOMISS xmm1, xmm2/m32*/
    { FCML_AMT_AVX_SIMD, 0x00C0, 0x00D88000, { 0x0F, 0x2F, 0x00 }, { FCML_OP_MODRM_R_XMM, FCML_OP_MODRM_RM_XMM_OP_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_CPUID[] = {
	/* 0F A2 CPUID A Valid Valid Returns processor identification and feature information to the EAX, EBX, ECX, and EDX registers, as determined by input entered in EAX (in some cases, ECX as well).*/
    { FCML_AMT_GPI, 0x0000, 0x00D80000, { 0x0F, 0xA2, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_CRC32[] = {
	/* F2 0F 38 F0 /r CRC32 r32, r/m8 A Valid Valid Accumulate CRC32 on r/m8.*/
	/* F2 REX 0F 38 F0 /r CRC32 r32, r/m8* A Valid N.E. Accumulate CRC32 on r/m8.*/
    { FCML_AMT_SSE42, 0x2010, 0x03EC8000, { 0x0F, 0x38, 0xF0 }, { FCML_OP_MODRM_R_32_RW, FCML_OP_MODRM_RM_8, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RO_RM8 },
	/* F2 REX.W 0F 38 F0 /r CRC32 r64, r/m8 A Valid N.E. Accumulate CRC32 on r/m8.*/
    { FCML_AMT_SSE42, 0x2008, 0x04AC8000, { 0x0F, 0x38, 0xF0 }, { FCML_OP_MODRM_R_64_RW, FCML_OP_MODRM_RM_8, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RO_RM8 },
	/* F2 0F 38 F1 /r CRC32 r32, r/m16 A Valid Valid Accumulate CRC32 on r/m16.*/
	/* F2 0F 38 F1 /r CRC32 r32, r/m32 A Valid Valid Accumulate CRC32 on r/m32.*/
    { FCML_AMT_SSE42, 0x2010, 0x03EC8000, { 0x0F, 0x38, 0xF1 }, { FCML_OP_MODRM_R_32_RW, FCML_OP_MODRM_RM, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RO_RMO },
	/* F2 REX.W 0F 38 F1 /r CRC32 r64, r/m64 A Valid N.E. Accumulate CRC32 on r/m64.*/
    { FCML_AMT_SSE42, 0x2008, 0x04AC8000, { 0x0F, 0x38, 0xF1 }, { FCML_OP_MODRM_R_64_RW, FCML_OP_MODRM_RM, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RO_RMO }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_CVTDQ2PD[] = {
	/* F3 0F E6 CVTDQ2PD xmm1, xmm2/m64 A Valid Valid Convert two packed signed doubleword integers from xmm2/m128 to two packed double-precision floatingpoint values in xmm1.*/
    { FCML_AMT_SSE2_SIMD, 0x4000, 0x00D88000, { 0x0F, 0xE6, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_OP_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VCVTDQ2PD[] = {
	/* VEX.128.F3.0F E6 /r VCVTDQ2PD xmm1, xmm2/m64*/
    { FCML_AMT_AVX_SIMD, 0x40C0, 0x00D88000, { 0x0F, 0xE6, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_OP_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.256.F3.0F E6 /r VCVTDQ2PD ymm1, xmm2/m128*/
    { FCML_AMT_AVX_SIMD, 0x40A0, 0x00D88000, { 0x0F, 0xE6, 0x00 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_CVTDQ2PS[] = {
	/* 0F 5B /r CVTDQ2PS xmm1, xmm2/m128 A Valid Valid Convert four packed signed doubleword integers from xmm2/m128 to four packed single-precision floatingpoint*/
    { FCML_AMT_SSE2_SIMD, 0x0000, 0x00D88000, { 0x0F, 0x5B, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VCVTDQ2PS[] = {
	/* VEX.128.0F 5B /r VCVTDQ2PS xmm1, xmm2/m128*/
	/* VEX.256.0F 5B /r VCVTDQ2PS ymm1, ymm2/m256*/
    { FCML_AMT_AVX_SIMD, 0x0080, 0x00D88000, { 0x0F, 0x5B, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_CVTPD2DQ[] = {
	/* F2 0F E6 CVTPD2DQ xmm1, xmm2/m128 A Valid Valid Convert two packed doubleprecision floating-point values from xmm2/m128 to two packed signed doubleword integers in xmm1.*/
    { FCML_AMT_SSE2_SIMD, 0x2000, 0x00D88000, { 0x0F, 0xE6, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VCVTPD2DQ[] = {
	/* VEX.128.F2.0F E6 /r VCVTPD2DQ xmm1, xmm2/m128*/
	/* VEX.256.F2.0F E6 /r VCVTPD2DQ xmm1, ymm2/m256*/
    { FCML_AMT_AVX_SIMD, 0x2080, 0x00D88000, { 0x0F, 0xE6, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_CVTPD2PI[] = {
	/* 66 0F 2D /r CVTPD2PI mm, xmm/m128 A Valid Valid Convert two packed doubleprecision floating-point values from xmm/m128 to two packed signed doubleword integers in mm.*/
    { FCML_AMT_SSE2_SIMD, 0x1000, 0x00D88000, { 0x0F, 0x2D, 0x00 }, { FCML_OP_MODRM_R_MMX_W, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_CVTPD2PS[] = {
	/* 66 0F 5A /r CVTPD2PS xmm1,xmm2/m128 A Valid Valid Convert two packed doubleprecision floating-point values in xmm2/m128 to two packed single-precision floating-point values in xmm1.*/
    { FCML_AMT_SSE2_SIMD, 0x1000, 0x00D88000, { 0x0F, 0x5A, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VCVTPD2PS[] = {
	/* VEX.128.66.0F 5A /r VCVTPD2PS xmm1, xmm2/m128*/
	/* VEX.256.66.0F 5A /r VCVTPD2PS xmm1, ymm2/m256*/
    { FCML_AMT_AVX_SIMD, 0x1080, 0x00D88000, {0x0F, 0x5A, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_CVTPI2PD[] = {
	/* 66 0F 2A /r CVTPI2PD xmm, mm/m64* A Valid Valid Convert two packed signed doubleword integers from mm/mem64 to two packed double-precision floatingpoint values in xmm.*/
    { FCML_AMT_SSE2_SIMD, 0x1000, 0x00D88000, { 0x0F, 0x2A, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_MMX_OP, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_CVTPI2PS[] = {
	/* 0F 2A /r CVTPI2PS xmm, mm/m64 A Valid Valid Convert two signed doubleword integers from mm/m64 to two singleprecision floating-point values in xmm.*/
    { FCML_AMT_SSE_SIMD, 0x0000, 0x00D88000, { 0x0F, 0x2A, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_MMX_OP, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_CVTPS2DQ[] = {
	/* 66 0F 5B /r CVTPS2DQ xmm1, xmm2/m128 A Valid Valid Convert four packed singleprecision floating-point values from xmm2/m128 to four packed signed doubleword integers in xmm1.*/
    { FCML_AMT_SSE2_SIMD, 0x1000, 0x00D88000, { 0x0F, 0x5B, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VCVTPS2DQ[] = {
	/* VEX.128.66.0F 5B /r VCVTPS2DQ xmm1, xmm2/m128*/
	/* VEX.256.66.0F 5B /r VCVTPS2DQ ymm1, ymm2/m256*/
    { FCML_AMT_AVX_SIMD, 0x1080, 0x00D88000, { 0x0F, 0x5B, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_CVTPS2PD[] = {
	/* 0F 5A /r CVTPS2PD xmm1, xmm2/m64 A Valid Valid Convert two packed singleprecision floating-point values in xmm2/m64 to two packed double-precision floating-point values in xmm1.*/
    { FCML_AMT_SSE2_SIMD, 0x0000, 0x00D88000, { 0x0F, 0x5A, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_OP_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VCVTPS2PD[] = {
	/* VEX.128.0F 5A /r VCVTPS2PD xmm1, xmm2/m64*/
	/* VEX.256.0F 5A /r VCVTPS2PD ymm1, xmm2/m128*/
    { FCML_AMT_AVX_SIMD, 0x0080, 0x00D88000, { 0x0F, 0x5A, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_CVTPS2PI[] = {
	/* 0F 2D /r CVTPS2PI mm, xmm/m64 A Valid Valid Convert two packed singleprecision floating-point values from xmm/m64 to two packed signed doubleword integers in mm.*/
    { FCML_AMT_SSE_SIMD, 0x0000, 0x00D88000, { 0x0F, 0x2D, 0x00 }, { FCML_OP_MODRM_R_MMX_W, FCML_OP_MODRM_RM_XMM_OP_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_CVTSD2SI[] = {
	/* F2 0F 2D /r CVTSD2SI r32, xmm/m64 A Valid Valid Convert one doubleprecision floating-point value from xmm/m64 to one signed doubleword integer r32.*/
    { FCML_AMT_SSE2_SIMD, 0x2010, 0x03D88000, { 0x0F, 0x2D, 0x00 }, { FCML_OP_MODRM_R_32_W, FCML_OP_MODRM_RM_XMM_OP_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* F2 REX.W 0F 2D /r CVTSD2SI r64, xmm/m64 A Valid N.E. Convert one doubleprecision floating-point value from xmm/m64 to one signed quadword integer sign-extended into r64.*/
    { FCML_AMT_SSE2_SIMD, 0x2008, 0x04988000, { 0x0F, 0x2D, 0x00 }, { FCML_OP_MODRM_R_64_W, FCML_OP_MODRM_RM_XMM_OP_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VCVTSD2SI[] = {
	/* VEX.128.F2.0F.W0 2D /r VCVTSD2SI r32, xmm1/m64*/
    { FCML_AMT_AVX_SIMD, 0x20D0, 0x03D88000, { 0x0F, 0x2D, 0x00 }, { FCML_OP_MODRM_R_32_W, FCML_OP_MODRM_RM_XMM_OP_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.128.F2.0F.W1 2D /r VCVTSD2SI r64, xmm1/m64*/
    { FCML_AMT_AVX_SIMD, 0x20C8, 0x04988000, { 0x0F, 0x2D, 0x00 }, { FCML_OP_MODRM_R_64_W, FCML_OP_MODRM_RM_XMM_OP_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_CVTSD2SS[] = {
	/* F2 0F 5A /r CVTSD2SS xmm1, xmm2/m64 A Valid Valid Convert one doubleprecision floating-point value in xmm2/m64 to one single-precision floatingpoint value in xmm1.*/
    { FCML_AMT_SSE2_SIMD, 0x2000, 0x00D88000, { 0x0F, 0x5A, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_OP_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VCVTSD2SS[] = {
	/* VEX.NDS.128.F2.0F 5A /r VCVTSD2SS xmm1,xmm2,xmm3/m64*/
    { FCML_AMT_AVX_SIMD, 0x20C0, 0x00D88000, { 0x0F, 0x5A, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_64, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_CVTSI2SD[] = {
	/* F2 0F 2A /r CVTSI2SD xmm, r/m32 A Valid Valid Convert one signed doubleword integer from r/m32 to one doubleprecision floating-point value in xmm.*/
    { FCML_AMT_SSE2_SIMD, 0x2000, 0x03D88000, { 0x0F, 0x2A, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_32, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RX_RM32 },
	/* F2 REX.W 0F 2A /r CVTSI2SD xmm, r/m64 A Valid N.E. Convert one signed quadword integer from r/m64 to one doubleprecision floating-point value in xmm.*/
    { FCML_AMT_SSE2_SIMD, 0x2008, 0x04988000, { 0x0F, 0x2A, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RX_RM64 }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VCVTSI2SD[] = {
	/* VEX.NDS.128.F2.0F.W0 2A /r VCVTSI2SD xmm1, xmm2, r/m32*/
    { FCML_AMT_AVX_SIMD, 0x20D0, 0x03D88000, { 0x0F, 0x2A, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_32, FCML_NA, FCML_NA }, FCML_AM_RX_RX_RM32 },
	/* VEX.NDS.128.F2.0F.W1 2A /r VCVTSI2SD xmm1, xmm2, r/m64*/
    { FCML_AMT_AVX_SIMD, 0x20C8, 0x04988000, { 0x0F, 0x2A, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_64, FCML_NA, FCML_NA }, FCML_AM_RX_RX_RM64 }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_CVTSI2SS[] = {
	/* F3 0F 2A /r CVTSI2SS xmm, r/m32 A Valid Valid Convert one signed doubleword integer from r/m32 to one singleprecision floating-point value in xmm.*/
    { FCML_AMT_SSE_SIMD, 0x4010, 0x03D88000, { 0x0F, 0x2A, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_32, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RX_RM32 },
	/* F3 REX.W 0F 2A /r CVTSI2SS xmm, r/m64 A Valid N.E. Convert one signed quadword integer from r/m64 to one singleprecision floating-point value in xmm.*/
    { FCML_AMT_SSE_SIMD, 0x4008, 0x04988000, { 0x0F, 0x2A, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RX_RM64 }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VCVTSI2SS[] = {
	/* VEX.NDS.128.F3.0F.W0 2A /r VCVTSI2SS xmm1, xmm2, r/m32*/
    { FCML_AMT_AVX_SIMD, 0x40D0, 0x03D88000, { 0x0F, 0x2A, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_32, FCML_NA, FCML_NA }, FCML_AM_RX_RX_RM32 },
	/* VEX.NDS.128.F3.0F.W1 2A /r VCVTSI2SS xmm1, xmm2, r/m64*/
    { FCML_AMT_AVX_SIMD, 0x40C8, 0x04988000, { 0x0F, 0x2A, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_64, FCML_NA, FCML_NA }, FCML_AM_RX_RX_RM64 }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_CVTSS2SD[] = {
	/* F3 0F 5A /r CVTSS2SD xmm1, xmm2/m32 A Valid Valid Convert one single-precision floating-point value in xmm2/m32 to one doubleprecision floating-point value in xmm1.*/
    { FCML_AMT_SSE2_SIMD, 0x4000, 0x00D88000, { 0x0F, 0x5A, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_OP_32, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VCVTSS2SD[] = {
	/* VEX.NDS.128.F3.0F 5A /r VCVTSS2SD xmm1, xmm2, xmm3/m32*/
    { FCML_AMT_AVX_SIMD, 0x40C0, 0x00D88000, { 0x0F, 0x5A, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_OP_32, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_CVTSS2SI[] = {
	/* F3 0F 2D /r CVTSS2SI r32, xmm/m32 A Valid Valid Convert one single-precision floating-point value from xmm/m32 to one signed doubleword integer in r32.*/
    { FCML_AMT_SSE_SIMD, 0x4010, 0x03D88000, { 0x0F, 0x2D, 0x00 }, { FCML_OP_MODRM_R_32_W, FCML_OP_MODRM_RM_XMM_OP_32, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* F3 REX.W 0F 2D /r CVTSS2SI r64, xmm/m32 A Valid N.E. Convert one single-precision floating-point value from xmm/m32 to one signed quadword integer in r64.*/
    { FCML_AMT_SSE_SIMD, 0x4008, 0x04988000, { 0x0F, 0x2D, 0x00 }, { FCML_OP_MODRM_R_64_W, FCML_OP_MODRM_RM_XMM_OP_32, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VCVTSS2SI[] = {
	/* VEX.128.F3.0F.W0 2D /r VCVTSS2SI r32, xmm1/m32*/
    { FCML_AMT_AVX_SIMD, 0x40D0, 0x03D88000, { 0x0F, 0x2D, 0x00 }, { FCML_OP_MODRM_R_32_W, FCML_OP_MODRM_RM_XMM_OP_32, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.128.F3.0F.W1 2D /r VCVTSS2SI r64, xmm1/m32*/
    { FCML_AMT_AVX_SIMD, 0x40C8, 0x04988000, { 0x0F, 0x2D, 0x00 }, { FCML_OP_MODRM_R_64_W, FCML_OP_MODRM_RM_XMM_OP_32, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_CVTTPD2DQ[] = {
	/* 66 0F E6 CVTTPD2DQ xmm1, xmm2/m128 A Valid Valid Convert two packed doubleprecision floating-point values from xmm2/m128 to two packed signed doubleword integers in xmm1 using truncation.*/
    { FCML_AMT_SSE2_SIMD, 0x1000, 0x00D88000, { 0x0F, 0xE6, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VCVTTPD2DQ[] = {
	/* VEX.128.66.0F E6 /r VCVTTPD2DQ xmm1, xmm2/m128*/
	/* VEX.256.66.0F E6 /r VCVTTPD2DQ xmm1, ymm2/m256*/
    { FCML_AMT_AVX_SIMD, 0x1080, 0x00D88000, { 0x0F, 0xE6, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_SIMD_L, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_CVTTPD2PI[] = {
	/* 66 0F 2C /r CVTTPD2PI mm, xmm/m128 A Valid Valid Convert two packer doubleprecision floating-point values from xmm/m128 to two packed signed doubleword integers in mm using truncation.*/
    { FCML_AMT_SSE2_SIMD, 0x1000, 0x00D88000, { 0x0F, 0x2C, 0x00 }, { FCML_OP_MODRM_R_MMX_W, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_CVTTPS2DQ[] = {
	/* F3 0F 5B /r CVTTPS2DQ xmm1, xmm2/m128 A Valid Valid Convert four singleprecision floating-point values from xmm2/m128 to four signed doubleword integers in xmm1 using truncation.*/
    { FCML_AMT_SSE2_SIMD, 0x4000, 0x00D88000, { 0x0F, 0x5B, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VCVTTPS2DQ[] = {
	/* VEX.128.F3.0F 5B /r VCVTTPS2DQ xmm1, xmm2/m128*/
	/* VEX.256.F3.0F 5B /r VCVTTPS2DQ ymm1, ymm2/m256*/
    { FCML_AMT_AVX_SIMD, 0x4080, 0x00D88000, { 0x0F, 0x5B, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_CVTTPS2PI[] = {
	/* 0F 2C /r CVTTPS2PI mm, xmm/m64 A Valid Valid Convert two singleprecision floating-point values from xmm/m64 to two signed doubleword signed integers in mm using truncation.*/
    { FCML_AMT_SSE_SIMD, 0x0000, 0x00D88000, { 0x0F, 0x2C, 0x00 }, { FCML_OP_MODRM_R_MMX_W, FCML_OP_MODRM_RM_XMM_OP_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_CVTTSD2SI[] = {
	/* F2 0F 2C /r CVTTSD2SI r32, xmm/m64 A Valid Valid Convert one doubleprecision floating-point value from xmm/m64 to one signed doubleword integer in r32 using truncation.*/
    { FCML_AMT_SSE2_SIMD, 0x2000, 0x03D88000, { 0x0F, 0x2C, 0x00 }, { FCML_OP_MODRM_R_32_W, FCML_OP_MODRM_RM_XMM_OP_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_R32_RXM64 },
	/* F2 REX.W 0F 2C /r CVTTSD2SI r64, xmm/m64 A Valid N.E. Convert one double precision floating-point value from xmm/m64 to one signedquad wordinteger in r64 using truncation.*/
    { FCML_AMT_SSE2_SIMD, 0x2008, 0x04988000, { 0x0F, 0x2C, 0x00 }, { FCML_OP_MODRM_R_64_W, FCML_OP_MODRM_RM_XMM_OP_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_R64_RXM64 }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VCVTTSD2SI[] = {
	/* VEX.128.F2.0F.W0 2C /r VCVTTSD2SI r32, xmm1/m64*/
    { FCML_AMT_AVX_SIMD, 0x20D0, 0x03D88000, { 0x0F, 0x2C, 0x00 }, { FCML_OP_MODRM_R_32_W, FCML_OP_MODRM_RM_SIMD_L_OP_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_R32_RXM64 },
	/* VEX.128.F2.0F.W1 2C /r VCVTTSD2SI r64, xmm1/m64*/
    { FCML_AMT_AVX_SIMD, 0x20C8, 0x04988000, { 0x0F, 0x2C, 0x00 }, { FCML_OP_MODRM_R_64_W, FCML_OP_MODRM_RM_SIMD_L_OP_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_R64_RXM64 }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_CVTTSS2SI[] = {
	/* F3 0F 2C /r CVTTSS2SI r32, xmm/m32 A Valid Valid Convert one single-precision floating-point value from xmm/m32 to one signed doubleword integer in r32 using truncation.*/
    { FCML_AMT_SSE_SIMD, 0x4010, 0x03D88000, { 0x0F, 0x2C, 0x00 }, { FCML_OP_MODRM_R_32_W, FCML_OP_MODRM_RM_XMM_OP_32, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* F3 REX.W 0F 2C /r CVTTSS2SI r64, xmm/m32 A Valid N.E. Convert one single-precision floating-point value from xmm/m32 to one signed quadword integer in*/
    { FCML_AMT_SSE_SIMD, 0x4008, 0x04988000, { 0x0F, 0x2C, 0x00 }, { FCML_OP_MODRM_R_64_W, FCML_OP_MODRM_RM_XMM_OP_32, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VCVTTSS2SI[] = {
	/* VEX.128.F3.0F.W0 2C /r VCVTTSS2SI r32, xmm1/m32*/
    { FCML_AMT_AVX_SIMD, 0x4390, 0x03D88000, { 0x0F, 0x2C, 0x00 }, { FCML_OP_MODRM_R_32_W, FCML_OP_MODRM_RM_SIMD_L_OP_32, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.128.F3.0F.W1 2C /r VCVTTSS2SI r64, xmm1/m32*/
    { FCML_AMT_AVX_SIMD, 0x4388, 0x04988000, { 0x0F, 0x2C, 0x00 }, { FCML_OP_MODRM_R_64_W, FCML_OP_MODRM_RM_SIMD_L_OP_32, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_CWD_CDQ_CQO[] = {
	/* 99 CWD A Valid Valid DX:AX <- sign-extend of AX.*/
	/* 99 CDQ A Valid Valid EDX:EAX <- sign-extend of EAX.*/
	/* REX.W + 99 CQO A Valid N.E. RDX:RAX <- sign-extend of RAX.*/
    { FCML_AMT_GPI, 0x0000, 0x00C40000, { 0x99, 0x00, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_DAA[] = {
	/* 27 DAA A Invalid Valid Decimal adjust AL after addition.*/
    { FCML_AMT_GPI, 0x0000, 0x00440000, { 0x27, 0x00, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_DAS[] = {
	/* 2F DAS A Invalid Valid Decimal adjust AL after subtraction.*/
    { FCML_AMT_GPI, 0x0000, 0x00440000, { 0x2F, 0x00, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_DEC[] = {
	/* FE /1 DEC r/m8 A Valid Valid Decrement r/m8 by 1.*/
	/* REX + FE /1 DEC r/m8* A Valid N.E. Decrement r/m8 by 1.*/
    { FCML_AMT_GPI, 0x0807, 0x00C58800, { 0xFE, 0x00, 0x00 }, { FCML_OP_MODRM_RM_8_RW, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RM8 },
	/* FF /1 DEC r/m16 A Valid Valid Decrement r/m16 by 1.*/
	/* FF /1 DEC r/m32 A Valid Valid Decrement r/m32 by 1.*/
	/* REX.W + FF /1 DEC r/m64 A Valid N.E. Decrement r/m64 by 1.*/
    { FCML_AMT_GPI, 0x0807, 0x00C58800, { 0xFF, 0x00, 0x00 }, { FCML_OP_MODRM_RM_RW, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RMO },
	/* 48+rw DEC r16 B N.E. Valid Decrement r16 by 1.*/
	/* 48+rd DEC r32 B N.E. Valid Decrement r32 by 1.*/
    { FCML_AMT_GPI, 0x0000, 0x00440001, { 0x48, 0x00, 0x00 }, { FCML_OP_OPCODE_REG( FCML_REG_GPR, FCML_EOS_EOSA ) | FCML_OA_RW, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RO }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_DIV[] = {
	/* F6 /6 DIV r/m8 A Valid Valid Unsigned divide AX by r/m8,with result stored in AL Quotient, AH Remainder.*/
	/* REX + F6 /6 DIV r/m8* A Valid N.E. Unsigned divide AX by r/m8, with result stored in AL Quotient, AH Remainder.*/
    { FCML_AMT_GPI, 0x0000, 0x00C5B000, { 0xF6, 0x00, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_AL, FCML_EOS_WORD ), FCML_OP_MODRM_RM_8_W, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_R16_RM8 },
	/* F7 /6 DIV r/m16 A Valid Valid Unsigned divide DX:AX by r/m16, with result stored in AX Quotient, DX Remainder.*/
	/* F7 /6 DIV r/m32 A Valid Valid Unsigned divide EDX:EAX by r/m32, with result stored in EAX Quotient, EDX Remainder.*/
	/* REX.W + F7 /6 DIV r/m64 A Valid N.E. Unsigned divide RDX:RAX by r/m64, with result stored in RAX Quotient, RDX Remainder.*/
    { FCML_AMT_GPI, 0x0000, 0x00C5B000, { 0xF7, 0x00, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_AX, FCML_EOS_EOSA ), FCML_OP_MODRM_RM_W, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RO_RMO }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_DIVPD[] = {
	/* 66 0F 5E /r DIVPD xmm1, xmm2/m128 A Valid Valid Divide packed doubleprecision floating-point values in xmm1 by packed double-precision floatingpoint values xmm2/m128.*/
    { FCML_AMT_SSE2_SIMD, 0x1000, 0x00D88000, { 0x0F, 0x5E, 0x00 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VDIVPD[] = {
	/* VEX.NDS.128.66.0F 5E /r VDIVPD xmm1, xmm2, xmm3/m128*/
	/* VEX.NDS.256.66.0F 5E /r VDIVPD ymm1, ymm2, ymm3/m256*/
    { FCML_AMT_AVX_SIMD, 0x1080, 0x00D88000, { 0x0F, 0x5E, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_RW, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_DIVPS[] = {
	/* 0F 5E /r DIVPS xmm1, xmm2/m128 A Valid Valid Divide packed singleprecision floating-point values in xmm1 by packed single-precision floatingpoint values xmm2/m128.*/
    { FCML_AMT_SSE_SIMD, 0x0000, 0x00D88000, { 0x0F, 0x5E, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VDIVPS[] = {
	/* VEX.NDS.128.0F 5E /r VDIVPS xmm1, xmm2, xmm3/m128*/
	/* VEX.NDS.256.0F 5E /r VDIVPS ymm1, ymm2, ymm3/m256*/
    { FCML_AMT_AVX_SIMD, 0x0080, 0x00D88000, { 0x0F, 0x5E, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_DIVSD[] = {
	/* F2 0F 5E /r DIVSD xmm1, xmm2/m64 A Valid Valid Divide low double-precision floating-point value n xmm1 by low double-precision floating-point value in xmm2/mem64.*/
    { FCML_AMT_SSE2_SIMD, 0x2000, 0x00D88000, { 0x0F, 0x5E, 0x00 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VDIVSD[] = {
	/* VEX.NDS.128.F2.0F 5E /r VDIVSD xmm1, xmm2, xmm3/m64*/
    { FCML_AMT_AVX_SIMD, 0x20C0, 0x00D88000, { 0x0F, 0x5E, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_64, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_DIVSS[] = {
	/* F3 0F 5E /r DIVSS xmm1, xmm2/m32 A Valid Valid Divide low single-precision floating-point value in xmm1 by low singleprecision floating-point value in xmm2/m32.*/
    { FCML_AMT_SSE_SIMD, 0x4000, 0x00D88000, { 0x0F, 0x5E, 0x00 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_32, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VDIVSS[] = {
	/* VEX.NDS.128.F3.0F 5E /r VDIVSS xmm1, xmm2, xmm3/m32*/
    { FCML_AMT_AVX_SIMD, 0x40C0, 0x00D88000, { 0x0F, 0x5E, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_32, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_DPPD[] = {
	/* 66 0F 3A 41 /r ib DPPD xmm1, xmm2/m128, int8 A Valid Valid Selectively multiply packed DP floating-point values from xmm1 with packed DP floating-point values from xmm2, add and selectively store the packed DP floating-point values to xmm1.*/
    { FCML_AMT_SSE41_SIMD, 0x1000, 0x00EC8000, { 0x0F, 0x3A, 0x41 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_128, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VDPPD[] = {
	/* VEX.NDS.128.66.0F3A 41 /r ib VDPPD xmm1,xmm2,xmm3/m128,int8*/
    { FCML_AMT_AVX_SIMD, 0x10C0, 0x00EC8000, { 0x0F, 0x3A, 0x41 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_OP_IB, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_DPPS[] = {
	/* 66 0F 3A 40 /r ib DPPS xmm1, xmm2/m128, int8 A Valid Valid Selectively multiply packed SP floating-point values from xmm1 with packed SP floating-point values from xmm2, add and selectively store the packed SP floating-point values or zero values to xmm1.*/
    { FCML_AMT_SSE41_SIMD, 0x1000, 0x00EC8000, { 0x0F, 0x3A, 0x40 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_128, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VDPPS[] = {
	/* VEX.NDS.128.66.0F3A 40 /r ib VDPPS xmm1,xmm2,xmm3/m128,int8*/
	/* VEX.NDS.256.66.0F3A 40 /r ib VDPPS ymm1,ymm2,ymm3/m256,int8*/
    { FCML_AMT_AVX_SIMD, 0x1080, 0x00EC8000, { 0x0F, 0x3A, 0x40 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_OP_IB, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_EMMS[] = {
	/* 0F 77 EMMS A Valid Valid Set the x87 FPU tag word to empty.*/
    { FCML_AMT_MMX, 0x0000, 0x00D80000, { 0x0F, 0x77, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_ENTER[] = {
	/* C8 iw 00 ENTER int16, 0 A Valid Valid Create a stack frame for a procedure.*/
	/* C8 iw 01 ENTER int16, 1 A Valid Valid Create a nested stack frame for a procedure.*/
	/* C8 iw ib ENTER int16, int8 A Valid Valid Create a nested stack frame for a procedure.*/
    { FCML_AMT_GPI | FCML_AMT_CTI, 0x0000, 0x00C40000, { 0xC8, 0x00, 0x00 }, { FCML_OP_IW, FCML_OP_IB, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_EXTRACTPS[] = {
	/* 66 0F 3A 17 /r ib EXTRACTPS reg/m32, xmm2, int8 A Valid Valid Extract a single-precision floating-point value from xmm2 at the source offset specified by int8 and store the result to reg or m32. The upper 32 bits of r64 is zeroed if reg is r64.,*/
    { FCML_AMT_SSE41_SIMD, 0x1000, 0x00EC8000, { 0x0F, 0x3A, 0x17 }, { FCML_OP_MODRM_RM_OP_32_W, FCML_OP_MODRM_R_XMM, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VEXTRACTPS[] = {
	/* VEX.128.66.0F3A 17 /r ib VEXTRACTPS r/m32, xmm1, int8*/
    { FCML_AMT_AVX_SIMD, 0x10C0, 0x00EC8000, { 0x0F, 0x3A, 0x17 }, { FCML_OP_MODRM_RM_OP_32_W, FCML_OP_MODRM_R_XMM, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_EXTRQ[] = {
	/* EXTRQ xmm1,int8,int8 66 0F 78 /0 ib ib*/
    { FCML_AMT_SSE4A, 0x1000, 0x00D98000, { 0x0F, 0x78, 0x00 }, { FCML_OP_RM( FCML_REG_SIMD, FCML_EOS_XWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ) | FCML_OA_RW, FCML_OP_IB, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* EXTRQ xmm1,xmm2 66 0F 79 /r*/
    { FCML_AMT_SSE4A, 0x1000, 0x00D88000, { 0x0F, 0x79, 0x00 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_RM( FCML_REG_SIMD, FCML_EOS_XWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_F2XM1[] = {
	/* D9 F0 F2XM1 Valid Valid Replace ST(0) with (2ST(0)  1).*/
    { FCML_AMT_FPU, 0x0000, 0x00D80000, { 0xD9, 0xF0, 0x17 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FABS[] = {
	/* D9 E1 FABS Valid Valid Replace ST with its absolute value.*/
    { FCML_AMT_FPU, 0x0000, 0x00D80000, { 0xD9, 0xE1, 0x17 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

/* TODO: W przypadku operacji na rejesrach FPU, flagi READ/WRITE nie sa ustawiane, dodac informacje do dokumentacji.*/
struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FADD[] = {
	/* D8 /0 FADD m32fp Valid Valid Add m32fp to ST(0) and store result in ST(0).*/
    { FCML_AMT_FPU, 0x0000, 0x00C58000, { 0xD8, 0x00, 0x00 }, { FCML_OP_MODRM_M_32, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_M32 },
	/* DC /0 FADD m64fp Valid Valid Add m64fp to ST(0) and store result in ST(0).*/
    { FCML_AMT_FPU, 0x0000, 0x00C58000, { 0xDC, 0x00, 0x00 }, { FCML_OP_MODRM_M_64, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_M64 },
	/* D8 C0+i FADD ST(0), ST(i) Valid Valid Add ST(0) to ST(i) and store result in ST(0).*/
    { FCML_AMT_FPU, 0x0000, 0x00D80001, { 0xD8, 0xC0, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_FPU, FCML_REG_ST0, FCML_EOS_UNDEFINED ), FCML_OP_OPCODE_REG( FCML_REG_FPU, FCML_EOS_UNDEFINED ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_ST0_ST },
	/* DC C0+i FADD ST(i), ST(0) Valid Valid Add ST(i) to ST(0) and store result in ST(i).*/
    { FCML_AMT_FPU, 0x0000, 0x00D80001, { 0xDC, 0xC0, 0x00 }, { FCML_OP_OPCODE_REG( FCML_REG_FPU, FCML_EOS_UNDEFINED ), FCML_OP_EXPLICIT_REG( FCML_REG_FPU, FCML_REG_ST0, FCML_EOS_UNDEFINED ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_ST_ST0 }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FIADD[] = {
	/* DA /0 FIADD m32int Valid Valid Add m32int to ST(0) and store result in ST(0).*/
    { FCML_AMT_FPU, 0x0000, 0x00C58000, { 0xDA, 0x00, 0x00 }, { FCML_OP_MODRM_M_32, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* DE /0 FIADD m16int Valid Valid Add m16int to ST(0) and store result in ST(0).*/
    { FCML_AMT_FPU, 0x0000, 0x00C58000, { 0xDE, 0x00, 0x00 }, { FCML_OP_MODRM_M_16, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FADDP[] = {
	/* DE C0+i FADDP ST(i), ST(0) Valid Valid Add ST(0) to ST(i), store result in ST(i), and pop the register stack.*/
    { FCML_AMT_FPU, 0x0000, 0x00D80001, { 0xDE, 0xC0, 0x00 }, { FCML_OP_OPCODE_REG( FCML_REG_FPU, FCML_EOS_UNDEFINED ), FCML_OP_EXPLICIT_REG( FCML_REG_FPU, FCML_REG_ST0, FCML_EOS_UNDEFINED ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* DE C1 FADDP*/
    { FCML_AMT_FPU, 0x0000, 0x00D80000, { 0xDE, 0xC1, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FBLD[] = {
	/* DF /4 FBLD m80 dec Valid Valid Convert BCD value to floating-point and push onto the FPU stack.*/
    { FCML_AMT_FPU, 0x0000, 0x00C5A000, { 0xDF, 0x00, 0x00 }, { FCML_OP_MODRM_M_OP_80, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FBSTP[] = {
	/* DF /6 FBSTP m80bcd Valid Valid Store ST(0) in m80bcd and pop ST(0).*/
    { FCML_AMT_FPU, 0x0000, 0x00C5B000, { 0xDF, 0x00, 0x00 }, { FCML_OP_MODRM_M_OP_80, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FCHS[] = {
	/* D9 E0 FCHS Valid Valid Complements sign of ST(0).*/
    { FCML_AMT_FPU, 0x0000, 0x00D80000, { 0xD9, 0xE0, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FCLEX[] = {
	/* 9B DB E2 FCLEX Valid Valid Clear floating-point exception flags after checking for pending unmasked floatingpoint exceptions.*/
    { FCML_AMT_FPU, 0x0000, 0x00EC0000, { 0x9B, 0xDB, 0xE2 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FNCLEX[] = {
	/* DB E2 * Valid Valid Clear floating-point exception flags without checking for pending unmasked floating-point exceptions.*/
    { FCML_AMT_FPU, 0x0000, 0x00D80000, { 0xDB, 0xE2, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FCMOVB[] = {
	/* DA C0+i FCMOVB ST(0), ST(i) Valid Valid Move if below (CF=1).*/
    { FCML_AMT_FPU, 0x0000, 0x00D80001, { 0xDA, 0xC0, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_FPU, FCML_REG_ST0, FCML_EOS_UNDEFINED ), FCML_OP_OPCODE_REG( FCML_REG_FPU, FCML_EOS_UNDEFINED ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FCMOVE[] = {
	/* DA C8+i FCMOVE ST(0), ST(i) Valid Valid Move if equal (ZF=1).*/
    { FCML_AMT_FPU, 0x0000, 0x00D80001, { 0xDA, 0xC8, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_FPU, FCML_REG_ST0, FCML_EOS_UNDEFINED ), FCML_OP_OPCODE_REG( FCML_REG_FPU, FCML_EOS_UNDEFINED ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FCMOVBE[] = {
	/* DA D0+i FCMOVBE ST(0), ST(i) Valid Valid Move if below or equal (CF=1 or ZF=1).*/
    { FCML_AMT_FPU, 0x0000, 0x00D80001, { 0xDA, 0xD0, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_FPU, FCML_REG_ST0, FCML_EOS_UNDEFINED ), FCML_OP_OPCODE_REG( FCML_REG_FPU, FCML_EOS_UNDEFINED ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FCMOVU[] = {
	/* DA D8+i FCMOVU ST(0), ST(i) Valid Valid Move if unordered (PF=1).*/
    { FCML_AMT_FPU, 0x0000, 0x00D80001, { 0xDA, 0xD8, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_FPU, FCML_REG_ST0, FCML_EOS_UNDEFINED ), FCML_OP_OPCODE_REG( FCML_REG_FPU, FCML_EOS_UNDEFINED ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FCMOVNB[] = {
	/* DB C0+i FCMOVNB ST(0), ST(i) Valid Valid Move if not below (CF=0).*/
    { FCML_AMT_FPU, 0x0000, 0x00D80001, { 0xDB, 0xC0, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_FPU, FCML_REG_ST0, FCML_EOS_UNDEFINED ), FCML_OP_OPCODE_REG( FCML_REG_FPU, FCML_EOS_UNDEFINED ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FCMOVNE[] = {
	/* DB C8+i FCMOVNE ST(0), ST(i) Valid Valid Move if not equal (ZF=0).*/
    { FCML_AMT_FPU, 0x0000, 0x00D80001, { 0xDB, 0xC8, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_FPU, FCML_REG_ST0, FCML_EOS_UNDEFINED ), FCML_OP_OPCODE_REG( FCML_REG_FPU, FCML_EOS_UNDEFINED ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FCMOVNBE[] = {
	/* DB D0+i FCMOVNBE ST(0), ST(i) Valid Valid Move if not below or equal (CF=0 and ZF=0).*/
    { FCML_AMT_FPU, 0x0000, 0x00D80001, { 0xDB, 0xD0, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_FPU, FCML_REG_ST0, FCML_EOS_UNDEFINED ), FCML_OP_OPCODE_REG( FCML_REG_FPU, FCML_EOS_UNDEFINED ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FCMOVNU[] = {
	/* DB D8+i FCMOVNU ST(0), ST(i) Valid Valid Move if not unordered (PF=0).*/
    { FCML_AMT_FPU, 0x0000, 0x00D80001, { 0xDB, 0xD8, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_FPU, FCML_REG_ST0, FCML_EOS_UNDEFINED ), FCML_OP_OPCODE_REG( FCML_REG_FPU, FCML_EOS_UNDEFINED ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FCOM[] = {
	/* D8 /2 FCOM m32fp*/
    { FCML_AMT_FPU, 0x0000, 0x00C59000, { 0xD8, 0x00, 0x00 }, { FCML_OP_MODRM_M_32, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_M32 },
	/* DC /2 FCOM m64fp*/
    { FCML_AMT_FPU, 0x0000, 0x00C59000, { 0xDC, 0x00, 0x00 }, { FCML_OP_MODRM_M_64, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_M64 },
	/* D8 D0+i FCOM ST(i)*/
    { FCML_AMT_FPU, 0x0000, 0x00D80001, { 0xD8, 0xD0, 0x00 }, { FCML_OP_OPCODE_REG( FCML_REG_FPU, FCML_EOS_UNDEFINED ), FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_ST },
	/* D8 D1 FCOM*/
    { FCML_AMT_FPU, 0x0000, 0x00D80000, { 0xD8, 0xD1, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FCOMP[] = {
	/* D8 /3 FCOMP m32fp*/
    { FCML_AMT_FPU, 0x0000, 0x00C59800, { 0xD8, 0x00, 0x00 }, { FCML_OP_MODRM_M_32, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_M32 },
	/* DC /3 FCOMP m64fp*/
    { FCML_AMT_FPU, 0x0000, 0x00C59800, { 0xDC, 0x00, 0x00 }, { FCML_OP_MODRM_M_64, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_M64 },
	/* D8 D8+i FCOMP ST(i)*/
    { FCML_AMT_FPU, 0x0000, 0x00D80001, { 0xD8, 0xD8, 0x00 }, { FCML_OP_OPCODE_REG( FCML_REG_FPU, FCML_EOS_UNDEFINED ), FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_ST },
	/* D8 D9 FCOMP*/
    { FCML_AMT_FPU, 0x0000, 0x00D80000, { 0xD8, 0xD9, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FCOMPP[] = {
	/* DE D9 FCOMPP*/
    { FCML_AMT_FPU, 0x0000, 0x00D80000, { 0xDE, 0xD9, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FCOMI[] = {
	/* DB F0+i FCOMI ST, ST(i) Valid Valid Compare ST(0) with ST(i) and set status flags accordingly.*/
    { FCML_AMT_FPU, 0x0000, 0x00D80001, { 0xDB, 0xF0, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_FPU, FCML_REG_ST0, FCML_EOS_UNDEFINED ), FCML_OP_OPCODE_REG( FCML_REG_FPU, FCML_EOS_UNDEFINED ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FCOMIP[] = {
	/* DF F0+i FCOMIP ST, ST(i) Valid Valid Compare ST(0) with ST(i), set status flags accordingly, and pop register stack.*/
    { FCML_AMT_FPU, 0x0000, 0x00D80001, { 0xDF, 0xF0, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_FPU, FCML_REG_ST0, FCML_EOS_UNDEFINED ), FCML_OP_OPCODE_REG( FCML_REG_FPU, FCML_EOS_UNDEFINED ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FUCOMI[] = {
	/* DB E8+i FUCOMI ST, ST(i) Valid Valid Compare ST(0) with ST(i), check for ordered values, and set status flags accordingly.*/
    { FCML_AMT_FPU, 0x0000, 0x00D80001, { 0xDB, 0xE8, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_FPU, FCML_REG_ST0, FCML_EOS_UNDEFINED ), FCML_OP_OPCODE_REG( FCML_REG_FPU, FCML_EOS_UNDEFINED ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FUCOMIP[] = {
	/* DF E8+i FUCOMIP ST, ST(i) Valid Valid Compare ST(0) with ST(i), check for ordered values, set status flags accordingly, and pop register stack.*/
    { FCML_AMT_FPU, 0x0000, 0x00D80001, { 0xDF, 0xE8, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_FPU, FCML_REG_ST0, FCML_EOS_UNDEFINED ), FCML_OP_OPCODE_REG( FCML_REG_FPU, FCML_EOS_UNDEFINED ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FCOS[] = {
	/* D9 FF FCOS Valid Valid Replace ST(0) with its cosine.*/
    { FCML_AMT_FPU, 0x0000, 0x00D80000, { 0xD9, 0xFF, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FDECSTP[] = {
	/* D9 F6 FDECSTP Valid Valid Decrement*/
    { FCML_AMT_FPU, 0x0000, 0x00D80000, { 0xD9, 0xF6, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FDIV[] = {
	/* D8 /6 FDIV m32fp Valid Valid Divide ST(0) by m32fp and store result in ST(0).*/
    { FCML_AMT_FPU, 0x0000, 0x00C5B000, { 0xD8, 0x00, 0x00 }, { FCML_OP_MODRM_M_32, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_M32 },
	/* DC /6 FDIV m64fp Valid Valid Divide ST(0) by m64fp and store result in ST(0).*/
    { FCML_AMT_FPU, 0x0000, 0x00C5B000, { 0xDC, 0x00, 0x00 }, { FCML_OP_MODRM_M_64, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_M64 },
	/* D8 F0+i FDIV ST(0), ST(i) Valid Valid Divide ST(0) by ST(i) and store result in ST(0).*/
    { FCML_AMT_FPU, 0x0000, 0x00D80001, { 0xD8, 0xF0, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_FPU, FCML_REG_ST0, FCML_EOS_UNDEFINED ), FCML_OP_OPCODE_REG( FCML_REG_FPU, FCML_EOS_UNDEFINED ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_ST0_ST },
	/* DC F8+i FDIV ST(i), ST(0) Valid Valid Divide ST(i) by ST(0) and store result in ST(i).*/
    { FCML_AMT_FPU, 0x0000, 0x00D80001, { 0xDC, 0xF8, 0x00 }, { FCML_OP_OPCODE_REG( FCML_REG_FPU, FCML_EOS_UNDEFINED ), FCML_OP_EXPLICIT_REG( FCML_REG_FPU, FCML_REG_ST0, FCML_EOS_UNDEFINED ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_ST_ST0 }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FDIVP[] = {
	/* DE F8+i FDIVP ST(i), ST(0) Valid Valid Divide ST(i) by ST(0), store result in ST(i), and pop the register stack.*/
    { FCML_AMT_FPU, 0x0000, 0x00D80001, { 0xDE, 0xF8, 0x00 }, { FCML_OP_OPCODE_REG( FCML_REG_FPU, FCML_EOS_UNDEFINED ), FCML_OP_EXPLICIT_REG( FCML_REG_FPU, FCML_REG_ST0, FCML_EOS_UNDEFINED ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_ST_ST0 },
	/* DE F9 FDIVP*/
    { FCML_AMT_FPU, 0x0000, 0x00D80000, { 0xDE, 0xF9, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FIDIV[] = {
	/* DA /6 FIDIV m32int Valid Valid Divide ST(0) by m32int and store result in ST(0).*/
    { FCML_AMT_FPU, 0x0000, 0x00C5B000, { 0xDA, 0x00, 0x00 }, { FCML_OP_MODRM_M_32, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_M32 },
	/* DE /6 FIDIV m16int Valid Valid Divide ST(0) by m64int and store result in ST(0).*/
    { FCML_AMT_FPU, 0x0000, 0x00C5B000, { 0xDE, 0x00, 0x00 }, { FCML_OP_MODRM_M_16, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_M16 }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FDIVR[] = {
	/* D8 /7 FDIVR m32fp Valid Valid Divide m32fp by ST(0) and store result in ST(0).*/
    { FCML_AMT_FPU, 0x0000, 0x00C5B800, { 0xD8, 0x00, 0x00 }, { FCML_OP_MODRM_M_32, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_M32 },
	/* DC /7 FDIVR m64fp Valid Valid Divide m64fp by ST(0) and store result in ST(0).*/
    { FCML_AMT_FPU, 0x0000, 0x00C5B800, { 0xDC, 0x00, 0x00 }, { FCML_OP_MODRM_M_64, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_M64 },
	/* D8 F8+i FDIVR ST(0), ST(i) Valid Valid Divide ST(i) by ST(0) and store result in ST(0).*/
    { FCML_AMT_FPU, 0x0000, 0x00D80001, { 0xD8, 0xF8, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_FPU, FCML_REG_ST0, FCML_EOS_UNDEFINED ), FCML_OP_OPCODE_REG( FCML_REG_FPU, FCML_EOS_UNDEFINED ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_ST0_ST },
	/* DC F0+i FDIVR ST(i), ST(0) Valid Valid Divide ST(0) by ST(i) and store result in ST(i).*/
    { FCML_AMT_FPU, 0x0000, 0x00D80001, { 0xDC, 0xF0, 0x00 }, { FCML_OP_OPCODE_REG( FCML_REG_FPU, FCML_EOS_UNDEFINED ), FCML_OP_EXPLICIT_REG( FCML_REG_FPU, FCML_REG_ST0, FCML_EOS_UNDEFINED ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_ST_ST0 }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FDIVRP[] = {
	/* DE F0+i FDIVRP ST(i), ST(0) Valid Valid Divide ST(0) by ST(i), store result in ST(i), and pop the register stack.*/
    { FCML_AMT_FPU, 0x0000, 0x00D80001, { 0xDE, 0xF0, 0x00 }, { FCML_OP_OPCODE_REG( FCML_REG_FPU, FCML_EOS_UNDEFINED ), FCML_OP_EXPLICIT_REG( FCML_REG_FPU, FCML_REG_ST0, FCML_EOS_UNDEFINED ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_ST_ST0 },
	/* DE F1 FDIVRP*/
    { FCML_AMT_FPU, 0x0000, 0x00D80000, { 0xDE, 0xF1, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FIDIVR[] = {
	/* DA /7 FIDIVR m32int Valid Valid Divide m32int by ST(0) and store result in ST(0).*/
    { FCML_AMT_FPU, 0x0000, 0x00C5B800, { 0xDA, 0x00, 0x00 }, { FCML_OP_MODRM_M_32, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_M32 },
	/* DE /7 FIDIVR m16int Valid Valid Divide m16int by ST(0) and store result in ST(0).*/
    { FCML_AMT_FPU, 0x0000, 0x00C5B800, { 0xDE, 0x00, 0x00 }, { FCML_OP_MODRM_M_16, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_M16 }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FFREE[] = {
	/* DD C0+i FFREE ST(i) Valid Valid Sets tag for ST(i) to empty.*/
    { FCML_AMT_FPU, 0x0000, 0x00D80001, { 0xDD, 0xC0, 0x00 }, { FCML_OP_OPCODE_REG( FCML_REG_FPU, FCML_EOS_UNDEFINED ), FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FICOM[] = {
	/* DE /2 FICOM m16int Valid Valid Compare ST(0) with m16int.*/
    { FCML_AMT_FPU, 0x0000, 0x00C59000, { 0xDE, 0x00, 0x00 }, { FCML_OP_MODRM_M_16, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_M16 },
	/* DA /2 FICOM m32int Valid Valid Compare ST(0) with m32int.*/
    { FCML_AMT_FPU, 0x0000, 0x00C59000, { 0xDA, 0x00, 0x00 }, { FCML_OP_MODRM_M_32, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_M32 }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FICOMP[] = {
	/* DE /3 FICOMP m16int Valid Valid Compare ST(0) with m16int and pop stack register.*/
    { FCML_AMT_FPU, 0x0000, 0x00C59800, { 0xDE, 0x00, 0x00 }, { FCML_OP_MODRM_M_16, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_M16 },
	/* DA /3 FICOMP m32int Valid Valid Compare ST(0) with m32int and pop stack register.*/
    { FCML_AMT_FPU, 0x0000, 0x00C59800, { 0xDA, 0x00, 0x00 }, { FCML_OP_MODRM_M_32, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_M32 }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FILD[] = {
	/* DF /0 FILD m16int Valid Valid Push m16int onto the FPU register stack.*/
    { FCML_AMT_FPU, 0x0000, 0x00C58000, { 0xDF, 0x00, 0x00 }, { FCML_OP_MODRM_M_16, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_M16 },
	/* DB /0 FILD m32int Valid Valid Push m32int onto the FPU register stack.*/
    { FCML_AMT_FPU, 0x0000, 0x00C58000, { 0xDB, 0x00, 0x00 }, { FCML_OP_MODRM_M_32, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_M32 },
	/* DF /5 FILD m64int Valid Valid Push m64int onto the FPU register stack.*/
    { FCML_AMT_FPU, 0x0000, 0x00C5A800, { 0xDF, 0x00, 0x00 }, { FCML_OP_MODRM_M_64, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_M64 }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FINCSTP[] = {
	/* D9 F7 FINCSTP Valid Valid Increment the TOP field in the FPU status register.*/
    { FCML_AMT_FPU, 0x0000, 0x00D80000, { 0xD9, 0xF7, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FINIT[] = {
	/* 9B DB E3 FINIT Valid Valid Initialize FPU after checking for pending unmasked floating-point exceptions.*/
    { FCML_AMT_FPU, 0x0000, 0x00EC0000, { 0x9B, 0xDB, 0xE3 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FNINIT[] = {
	/* DB E3 FNINIT* Valid Valid Initialize FPU without checking for pending unmasked floating-point exceptions.*/
    { FCML_AMT_FPU, 0x0000, 0x00D80000, { 0xDB, 0xE3, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FIST[] = {
	/* DF /2 FIST m16int Valid Valid Store ST(0) in m16int.*/
    { FCML_AMT_FPU, 0x0000, 0x00C59000, { 0xDF, 0x00, 0x00 }, { FCML_OP_MODRM_M_16_W, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_M16 },
	/* DB /2 FIST m32int Valid Valid Store ST(0) in m32int.*/
    { FCML_AMT_FPU, 0x0000, 0x00C59000, { 0xDB, 0x00, 0x00 }, { FCML_OP_MODRM_M_32_W, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_M32 }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FISTP[] = {
	/* DF /3 FISTP m16int Valid Valid Store ST(0) in m16int and pop register stack.*/
    { FCML_AMT_FPU, 0x0000, 0x00C59800, { 0xDF, 0x00, 0x00 }, { FCML_OP_MODRM_M_16_W, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_M16 },
	/* DB /3 FISTP m32int Valid Valid Store ST(0) in m32int and pop register stack.*/
    { FCML_AMT_FPU, 0x0000, 0x00C59800, { 0xDB, 0x00, 0x00 }, { FCML_OP_MODRM_M_32_W, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_M32 },
	/* DF /7 FISTP m64int Valid Valid Store ST(0) in m64int and pop register stack.*/
    { FCML_AMT_FPU, 0x0000, 0x00C5B800, { 0xDF, 0x00, 0x00 }, { FCML_OP_MODRM_M_64_W, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_M64 }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FISTTP[] = {
	/* DF /1 FISTTP m16int Valid Valid Store ST(0) in m16int with truncation.*/
    { FCML_AMT_SSE3 | FCML_AMT_FPU, 0x0000, 0x00C58800, { 0xDF, 0x00, 0x00 }, { FCML_OP_MODRM_M_16_W, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* DB /1 FISTTP m32int Valid Valid Store ST(0) in m32int with truncation.*/
    { FCML_AMT_SSE3 | FCML_AMT_FPU, 0x0000, 0x00C58800, { 0xDB, 0x00, 0x00 }, { FCML_OP_MODRM_M_32_W, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* DD /1 FISTTP m64int Valid Valid Store ST(0) in m64int with truncation.*/
    { FCML_AMT_SSE3 | FCML_AMT_FPU, 0x0000, 0x00C58800, { 0xDD, 0x00, 0x00 }, { FCML_OP_MODRM_M_64_W, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FLD[] = {
	/* D9 /0 FLD m32fp Valid Valid Push m32fp onto the FPU register stack.*/
    { FCML_AMT_FPU, 0x0000, 0x00C58000, { 0xD9, 0x00, 0x00 }, { FCML_OP_MODRM_M_32, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_M32 },
	/* DD /0 FLD m64fp Valid Valid Push m64fp onto the FPU register stack.*/
    { FCML_AMT_FPU, 0x0000, 0x00C58000, { 0xDD, 0x00, 0x00 }, { FCML_OP_MODRM_M_64, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_M64 },
	/* DB /5 FLD m80fp Valid Valid Push m80fp onto the FPU register stack.*/
    { FCML_AMT_FPU, 0x0000, 0x00C5A800, { 0xDB, 0x00, 0x00 }, { FCML_OP_MODRM_M_80, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_M80 },
	/* D9 C0+i FLD ST(i) Valid Valid Push ST(i) onto the FPU register stack.*/
    { FCML_AMT_FPU, 0x0000, 0x00D80001, { 0xD9, 0xC0, 0x00 }, { FCML_OP_OPCODE_REG( FCML_REG_FPU, FCML_EOS_UNDEFINED ), FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_ST }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FLD1[] = {
	/* D9 E8 FLD1 Valid Valid Push +1.0 onto the FPU register stack.*/
    { FCML_AMT_FPU, 0x0000, 0x00D80000, { 0xD9, 0xE8, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FLDL2T[] = {
	/* D9 E9 FLDL2T Valid Valid Push log210 onto the FPU register stack.*/
    { FCML_AMT_FPU, 0x0000, 0x00D80000, { 0xD9, 0xE9, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FLDL2E[] = {
	/* D9 EA FLDL2E Valid Valid Push log2e onto the FPU register stack.*/
    { FCML_AMT_FPU, 0x0000, 0x00D80000, { 0xD9, 0xEA, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FLDPI[] = {
	/* D9 EB FLDPI Valid Valid Push onto the FPU register stack.*/
    { FCML_AMT_FPU, 0x0000, 0x00D80000, { 0xD9, 0xEB, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FLDLG2[] = {
	/* D9 EC FLDLG2 Valid Valid Push log102 onto the FPU register stack.*/
    { FCML_AMT_FPU, 0x0000, 0x00D80000, { 0xD9, 0xEC, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FLDLN2[] = {
	/* D9 ED FLDLN2 Valid Valid Push loge2 onto the FPU register stack.*/
    { FCML_AMT_FPU, 0x0000, 0x00D80000, { 0xD9, 0xED, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FLDZ[] = {
	/* D9 EE FLDZ Valid Valid Push +0.0 onto the FPU register stack.*/
    { FCML_AMT_FPU, 0x0000, 0x00D80000, { 0xD9, 0xEE, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FLDCW[] = {
	/* D9 /5 FLDCW m2byte Valid Valid Load FPU control word from m2byte.*/
    { FCML_AMT_FPU, 0x0000, 0x00C5A800, { 0xD9, 0x00, 0x00 }, { FCML_OP_MODRM_M_OP_16, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FLDENV[] = {
	/* D9 /4 FLDENV m14/28byte Valid Valid Load FPU environment from m14byte or m28byte.*/
    { FCML_AMT_FPU, 0x0000, 0x00C5A000, { 0xD9, 0x00, 0x00 }, { FCML_OP_MODRM_M_14_28, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FMUL[] = {
	/* D8 /1 FMUL m32fp Valid Valid Multiply ST(0) by m32fp and store result in ST(0).*/
    { FCML_AMT_FPU, 0x0000, 0x00C58800, { 0xD8, 0x00, 0x00 }, { FCML_OP_MODRM_M_32, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_M32 },
	/* DC /1 FMUL m64fp Valid Valid Multiply ST(0) by m64fp and store result in ST(0).*/
    { FCML_AMT_FPU, 0x0000, 0x00C58800, { 0xDC, 0x00, 0x00 }, { FCML_OP_MODRM_M_64, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_M64 },
	/* D8 C8+i FMUL ST(0), ST(i) Valid Valid Multiply ST(0) by ST(i) and store result in ST(0).*/
    { FCML_AMT_FPU, 0x0000, 0x00D80001, { 0xD8, 0xC8, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_FPU, FCML_REG_ST0, FCML_EOS_UNDEFINED ), FCML_OP_OPCODE_REG( FCML_REG_FPU, FCML_EOS_UNDEFINED ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_ST0_ST },
	/* DC C8+i FMUL ST(i), ST(0) Valid Valid Multiply ST(i) by ST(0) and store result in ST(i).*/
    { FCML_AMT_FPU, 0x0000, 0x00D80001, { 0xDC, 0xC8, 0x00 }, { FCML_OP_OPCODE_REG( FCML_REG_FPU, FCML_EOS_UNDEFINED ), FCML_OP_EXPLICIT_REG( FCML_REG_FPU, FCML_REG_ST0, FCML_EOS_UNDEFINED ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_ST_ST0 }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FMULP[] = {
	/* DE C8+i FMULP ST(i), ST(0) Valid Valid Multiply ST(i) by ST(0), store result in ST(i), and pop the register stack.*/
    { FCML_AMT_FPU, 0x0000, 0x00D80001, { 0xDE, 0xC8, 0x00 }, { FCML_OP_OPCODE_REG( FCML_REG_FPU, FCML_EOS_UNDEFINED ), FCML_OP_EXPLICIT_REG( FCML_REG_FPU, FCML_REG_ST0, FCML_EOS_UNDEFINED ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_ST_ST0 },
	/* DE C9 FMULP*/
    { FCML_AMT_FPU, 0x0000, 0x00D80000, { 0xDE, 0xC9, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FIMUL[] = {
	/* DA /1 FIMUL m32int Valid Valid Multiply ST(0) by m32int and store result in ST(0).*/
    { FCML_AMT_FPU, 0x0000, 0x00C58800, { 0xDA, 0x00, 0x00 }, { FCML_OP_MODRM_M_32, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_M32 },
	/* DE /1 FIMUL m16int Valid Valid Multiply ST(0) by m16int and store result in ST(0).*/
    { FCML_AMT_FPU, 0x0000, 0x00C58800, { 0xDE, 0x00, 0x00 }, { FCML_OP_MODRM_M_16, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_M16 }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FNOP[] = {
	/* D9 D0 FNOP Valid Valid No operation is performed.*/
    { FCML_AMT_FPU, 0x0000, 0x00D80000, { 0xD9, 0xD0, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FPATAN[] = {
	/* D9 F3 FPATAN Valid Valid Replace ST(1) with arctan(ST(1) ST(0)) and pop the register stack.*/
    { FCML_AMT_FPU, 0x0000, 0x00D80000, { 0xD9, 0xF3, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FPREM[] = {
	/* D9 F8 FPREM Valid Valid Replace ST(0) with the remainder obtained from dividing ST(0) by ST(1).*/
    { FCML_AMT_FPU, 0x0000, 0x00D80000, { 0xD9, 0xF8, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FPREM1[] = {
	/* D9 F5 FPREM1 Valid Valid Replace ST(0) with the IEEE remainder obtained from dividing ST(0) by ST(1).*/
    { FCML_AMT_FPU, 0x0000, 0x00D80000, { 0xD9, 0xF5, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FPTAN[] = {
	/* D9 F2 FPTAN Valid Valid Replace ST(0) with its tangent and push 1 onto the FPU stack.*/
    { FCML_AMT_FPU, 0x0000, 0x00D80000, { 0xD9, 0xF2, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FRNDINT[] = {
	/* D9 FC FRNDINT Valid Valid Round ST(0) to an integer.*/
    { FCML_AMT_FPU, 0x0000, 0x00D80000, { 0xD9, 0xFC, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FRSTOR[] = {
	/* DD /4 FRSTOR m94/108byte Valid Valid Load FPU state from m94byte or m108byte.*/
    { FCML_AMT_FPU, 0x0000, 0x00C5A000, { 0xDD, 0x00, 0x00 }, { FCML_OP_MODRM_M_94_108, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FSAVE[] = {
	/* 9B DD /6 FSAVE m94/108byte Valid Valid Store FPU state to m94byte or m108byte after checking for pending unmasked floatingpoint exceptions. Then reinitialize the FPU.*/
    { FCML_AMT_FPU, 0x0000, 0x00D9B000, { 0x9B, 0xDD, 0x00 }, { FCML_OP_MODRM_M_94_108_W, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FNSAVE[] = {
	/* DD /6 FNSAVE* m94/108byte Valid Valid Store FPU environment to m94byte or m108byte without checking for pending unmasked floating-point exceptions.*/
    { FCML_AMT_FPU, 0x0000, 0x00C5B000, { 0xDD, 0x00, 0x00 }, { FCML_OP_MODRM_M_94_108_W, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FSCALE[] = {
	/* D9 FD FSCALE Valid Valid Scale ST(0) by ST(1).*/
    { FCML_AMT_FPU, 0x0000, 0x00D80000, { 0xD9, 0xFD, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FSIN[] = {
	/* D9 FE FSIN Valid Valid Replace ST(0) with its sine.*/
    { FCML_AMT_FPU, 0x0000, 0x00D80000, { 0xD9, 0xFE, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FSINCOS[] = {
	/* D9 FB FSINCOS Valid Valid Compute the sine and cosine of ST(0); replace ST(0) with the sine, and push the cosine onto the register stack.*/
    { FCML_AMT_FPU, 0x0000, 0x00D80000, { 0xD9, 0xFB, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FSQRT[] = {
	/* D9 FA FSQRT Valid Valid Computes square root of ST(0) and stores the result in ST(0).*/
    { FCML_AMT_FPU, 0x0000, 0x00D80000, { 0xD9, 0xFA, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FST[] = {
	/* D9 /2 FST m32fp Valid Valid Copy ST(0) to m32fp.*/
    { FCML_AMT_FPU, 0x0000, 0x00C59000, { 0xD9, 0x00, 0x00 }, { FCML_OP_MODRM_M_32_W, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_M32 },
	/* DD /2 FST m64fp Valid Valid Copy ST(0) to m64fp.*/
    { FCML_AMT_FPU, 0x0000, 0x00C59000, { 0xDD, 0x00, 0x00 }, { FCML_OP_MODRM_M_64_W, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_M64 },
	/* DD D0+i FST ST(i) Valid Valid Copy ST(0) to ST(i).*/
    { FCML_AMT_FPU, 0x0000, 0x00D80001, { 0xDD, 0xD0, 0x00 }, { FCML_OP_OPCODE_REG( FCML_REG_FPU, FCML_EOS_UNDEFINED ), FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_ST }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FSTP[] = {
	/* D9 /3 FSTP m32fp Valid Valid Copy ST(0) to m32fp and pop register stack.*/
    { FCML_AMT_FPU, 0x0000, 0x00C59800, { 0xD9, 0x00, 0x00 }, { FCML_OP_MODRM_M_32_W, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_M32 },
	/* DD /3 FSTP m64fp Valid Valid Copy ST(0) to m64fp and pop register stack.*/
    { FCML_AMT_FPU, 0x0000, 0x00C59800, { 0xDD, 0x00, 0x00 }, { FCML_OP_MODRM_M_64_W, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_M64 },
	/* DB /7 FSTP m80fp Valid Valid Copy ST(0) to m80fp and pop register stack.*/
    { FCML_AMT_FPU, 0x0000, 0x00C5B800, { 0xDB, 0x00, 0x00 }, { FCML_OP_MODRM_M_80_W, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_M80 },
	/* DD D8+i FSTP ST(i) Valid Valid Copy ST(0) to ST(i) and pop register stack.*/
    { FCML_AMT_FPU, 0x0000, 0x00D80001, { 0xDD, 0xD8, 0x00 }, { FCML_OP_OPCODE_REG( FCML_REG_FPU, FCML_EOS_UNDEFINED ), FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_ST }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FSTCW[] = {
	/* 9B D9 /7 FSTCW m2byte Valid Valid Store FPU control word to m2byte after checking for pending unmasked floating-point exceptions.*/
    { FCML_AMT_FPU, 0x0000, 0x00D9B800, { 0x9B, 0xD9, 0x00 }, { FCML_OP_MODRM_M_OP_16_W, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FNSTCW[] = {
	/* D9 /7 FNSTCW* m2byte Valid Valid Store FPU control word to m2byte without checking for pending unmasked floating-point exceptions.*/
    { FCML_AMT_FPU, 0x0000, 0x00C5B800, { 0xD9, 0x00, 0x00 }, { FCML_OP_MODRM_M_OP_16_W, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FSTENV[] = {
	/* 9B D9 /6 FSTENV m14/28byte Valid Valid Store FPU environment to m14byte or m28byte after checking for pending unmasked floating-point exceptions. Then mask all floatingpoint exceptions.*/
    { FCML_AMT_FPU, 0x0000, 0x00D9B000, { 0x9B, 0xD9, 0x00 }, { FCML_OP_MODRM_M_14_28_W, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FNSTENV[] = {
	/* D9 /6 FNSTENV* m14/28byte Valid Valid Store FPU environment to m14byte or m28byte without checking for pending unmasked floating-point exceptions. Then mask all floatingpoint exceptions.*/
    { FCML_AMT_FPU, 0x0000, 0x00C5B000, { 0xD9, 0x00, 0x00 }, { FCML_OP_MODRM_M_14_28_W, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FSTSW[] = {
	/* 9B DD /7 FSTSW m2byte Valid Valid Store FPU status word at m2byte after checking for pending unmasked floatingpoint exceptions.*/
    { FCML_AMT_FPU, 0x0000, 0x00D9B800, { 0x9B, 0xDD, 0x00 }, { FCML_OP_MODRM_M_OP_16_W, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_M2BYTE },
	/* 9B DF E0 FSTSW AX Valid Valid Store FPU status word in AX register after checking for pending unmasked floatingpoint exceptions.*/
    { FCML_AMT_FPU, 0x0000, 0x00EC0000, { 0x9B, 0xDF, 0xE0 }, { FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_AX, FCML_EOS_WORD ), FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_AX }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FNSTSW[] = {
	/* DD /7 FNSTSW* m2byte Valid Valid Store FPU status word at m2byte without checking for pending unmasked floatingpoint exceptions.*/
    { FCML_AMT_FPU, 0x0000, 0x00C5B800, { 0xDD, 0x00, 0x00 }, { FCML_OP_MODRM_M_OP_16_W, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_M2BYTE },
	/* DF E0 FNSTSW* AX Valid Valid Store FPU status word in AX register without checking for pending unmasked floatingpoint exceptions.*/
    { FCML_AMT_FPU, 0x0000, 0x00D80000, { 0xDF, 0xE0, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_AX, FCML_EOS_WORD ), FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_AX }
};

/* TODO: opisac problem kompatybilnoci z system V.*/

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FSUB[] = {
	/* D8 /4 FSUB m32fp Valid Valid Subtract m32fp from ST(0) and store result in ST(0).*/
    { FCML_AMT_FPU, 0x0000, 0x00C5A000, { 0xD8, 0x00, 0x00 }, { FCML_OP_MODRM_M_32, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_M32 },
	/* DC /4 FSUB m64fp Valid Valid Subtract m64fp from ST(0) and store result in ST(0).*/
    { FCML_AMT_FPU, 0x0000, 0x00C5A000, { 0xDC, 0x00, 0x00 }, { FCML_OP_MODRM_M_64, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_M64 },
	/* D8 E0+i FSUB ST(0), ST(i) Valid Valid Subtract ST(i) from ST(0) and store result in ST(0).*/
    { FCML_AMT_FPU, 0x0000, 0x00D80001, { 0xD8, 0xE0, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_FPU, FCML_REG_ST0, FCML_EOS_UNDEFINED ), FCML_OP_OPCODE_REG( FCML_REG_FPU, FCML_EOS_UNDEFINED ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_ST0_ST },
	/* DC E8+i FSUB ST(i), ST(0) Valid Valid Subtract ST(0) from ST(i) and store result in ST(i).*/
    { FCML_AMT_FPU, 0x0000, 0x00D80001, { 0xDC, 0xE8, 0x00 }, { FCML_OP_OPCODE_REG( FCML_REG_FPU, FCML_EOS_UNDEFINED ), FCML_OP_EXPLICIT_REG( FCML_REG_FPU, FCML_REG_ST0, FCML_EOS_UNDEFINED ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_ST_ST0 }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FSUBP[] = {
	/* DE E8+i FSUBP ST(i), ST(0) Valid Valid Subtract ST(0) from ST(i), store result in ST(i), and pop register stack.*/
    { FCML_AMT_FPU, 0x0000, 0x00D80001, { 0xDE, 0xE8, 0x00 }, { FCML_OP_OPCODE_REG( FCML_REG_FPU, FCML_EOS_UNDEFINED ), FCML_OP_EXPLICIT_REG( FCML_REG_FPU, FCML_REG_ST0, FCML_EOS_UNDEFINED ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_ST_ST0 },
	/* DE E9 FSUBP*/
    { FCML_AMT_FPU, 0x0000, 0x00D80000, { 0xDE, 0xE9, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FISUB[] = {
	/* DA /4 FISUB m32int Valid Valid Subtract m32int from ST(0) and store result in ST(0).*/
    { FCML_AMT_FPU, 0x0000, 0x00C5A000, { 0xDA, 0x00, 0x00 }, { FCML_OP_MODRM_M_32, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_M32 },
	/* DE /4 FISUB m16int Valid Valid Subtract m16int from ST(0) and store result in ST(0).*/
    { FCML_AMT_FPU, 0x0000, 0x00C5A000, { 0xDE, 0x00, 0x00 }, { FCML_OP_MODRM_M_16, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_M16 }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FSUBR[] = {
	/* D8 /5 FSUBR m32fp Valid Valid Subtract ST(0) from m32fp and store result in ST(0).*/
    { FCML_AMT_FPU, 0x0000, 0x00C5A800, { 0xD8, 0x00, 0x00 }, { FCML_OP_MODRM_M_32, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_M32 },
	/* DC /5 FSUBR m64fp Valid Valid Subtract ST(0) from m64fp and store result in ST(0).*/
    { FCML_AMT_FPU, 0x0000, 0x00C5A800, { 0xDC, 0x00, 0x00 }, { FCML_OP_MODRM_M_64, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_M64 },
	/* D8 E8+i FSUBR ST(0), ST(i) Valid Valid Subtract ST(0) from ST(i) and store result in ST(0).*/
    { FCML_AMT_FPU, 0x0000, 0x00D80001, { 0xD8, 0xE8, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_FPU, FCML_REG_ST0, FCML_EOS_UNDEFINED ), FCML_OP_OPCODE_REG( FCML_REG_FPU, FCML_EOS_UNDEFINED ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_ST0_ST },
	/* DC E0+i FSUBR ST(i), ST(0) Valid Valid Subtract ST(i) from ST(0) and store result in ST(i).*/
    { FCML_AMT_FPU, 0x0000, 0x00D80001, { 0xDC, 0xE0, 0x00 }, { FCML_OP_OPCODE_REG( FCML_REG_FPU, FCML_EOS_UNDEFINED ), FCML_OP_EXPLICIT_REG( FCML_REG_FPU, FCML_REG_ST0, FCML_EOS_UNDEFINED ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_ST_ST0 }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FSUBRP[] = {
	/* DE E0+i FSUBRP ST(i), ST(0) Valid Valid Subtract ST(i) from ST(0), store result in ST(i), and pop register stack.*/
    { FCML_AMT_FPU, 0x0000, 0x00D80001, { 0xDE, 0xE0, 0x00 }, { FCML_OP_OPCODE_REG( FCML_REG_FPU, FCML_EOS_UNDEFINED ), FCML_OP_EXPLICIT_REG( FCML_REG_FPU, FCML_REG_ST0, FCML_EOS_UNDEFINED ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_ST_ST0 },
	/* DE E1 FSUBRP*/
    { FCML_AMT_FPU, 0x0000, 0x00D80000, { 0xDE, 0xE1, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FISUBR[] = {
	/* DE /5 FISUBR m16int Valid Valid Subtract ST(0) from m16int and store result in ST(0).*/
    { FCML_AMT_FPU, 0x0000, 0x00C5A800, { 0xDE, 0x00, 0x00 }, { FCML_OP_MODRM_M_16, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_M16 },
	/* DA /5 FISUBR m32int Valid Valid Subtract ST(0) from m32int and store result in ST(0).*/
    { FCML_AMT_FPU, 0x0000, 0x00C5A800, { 0xDA, 0x00, 0x00 }, { FCML_OP_MODRM_M_32, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_M32 }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FTST[] = {
	/* D9 E4 FTST Valid Valid Compare ST(0) with 0.0.*/
    { FCML_AMT_FPU, 0x0000, 0x00D80000, { 0xD9, 0xE4, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FUCOM[] = {
	/* DD E0+i FUCOM ST(i) Valid Valid Compare ST(0) with ST(i).*/
    { FCML_AMT_FPU, 0x0000, 0x00D80001, { 0xDD, 0xE0, 0x00 }, { FCML_OP_OPCODE_REG( FCML_REG_FPU, FCML_EOS_UNDEFINED ), FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_ST0_ST },
	/* DD E1 FUCOM*/
    { FCML_AMT_FPU, 0x0000, 0x00D80000, { 0xDD, 0xE1, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FUCOMP[] = {
	/* DD E8+i FUCOMP ST(i) Valid Valid Compare ST(0) with ST(i) and pop register stack.*/
    { FCML_AMT_FPU, 0x0000, 0x00D80001, { 0xDD, 0xE8, 0x00 }, { FCML_OP_OPCODE_REG( FCML_REG_FPU, FCML_EOS_UNDEFINED ), FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_ST0_ST },
	/* DD E9 FUCOMP*/
    { FCML_AMT_FPU, 0x0000, 0x00D80000, { 0xDD, 0xE9, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FUCOMPP[] = {
	/* DA E9 FUCOMPP Valid Valid Compare ST(0) with ST(1) and pop register stack twice.*/
    { FCML_AMT_FPU, 0x0000, 0x00D80000, { 0xDA, 0xE9, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_ST0_ST }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FXAM[] = {
	/* D9 E5 FXAM Valid Valid Classify value or number in ST(0).*/
    { FCML_AMT_FPU, 0x0000, 0x00D80000, { 0xD9, 0xE5, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FXCH[] = {
	/* D9 C8+i FXCH ST(i) Valid Valid Exchange the contents of ST(0) and ST(i).*/
    { FCML_AMT_FPU, 0x0000, 0x00D80001, { 0xD9, 0xC8, 0x00 }, { FCML_OP_OPCODE_REG( FCML_REG_FPU, FCML_EOS_UNDEFINED ), FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_ST0_ST },
	/* D9 C9 FXCH*/
    { FCML_AMT_FPU, 0x0000, 0x00D80000, { 0xD9, 0xC9, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FXRSTOR[] = {
	/* 0F AE /1 FXRSTOR m512byte A Valid Valid Restore the x87 FPU, MMX, XMM, and MXCSR register state from m512byte.*/
    { FCML_AMT_SIMD | FCML_AMT_FPU, 0x0000, 0x03D98800, { 0x0F, 0xAE, 0x00 }, { FCML_OP_MODRM_M_OP_512B, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FXRSTOR64[] = {
	/* REX.W+ 0F AE /1 FXRSTOR64 m512byte A Valid N.E. Restore the x87 FPU, MMX, XMM, and MXCSR register state from m512byte.*/
    { FCML_AMT_SIMD | FCML_AMT_FPU, 0x0008, 0x04998800, { 0x0F, 0xAE, 0x00 }, { FCML_OP_MODRM_M_OP_512B, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FXSAVE[] = {
	/* 0F AE /0 FXSAVE m512byte A Valid Valid Save the x87 FPU, MMX, XMM, and MXCSR register state to m512byte.*/
    { FCML_AMT_SIMD | FCML_AMT_FPU, 0x0000, 0x03D98000, { 0x0F, 0xAE, 0x00 }, { FCML_OP_MODRM_M_OP_512B_W, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FXSAVE64[] = {
	/* REX.W+ 0F AE /0 FXSAVE64 m512byte A Valid N.E. Save the x87 FPU, MMX, XMM, and MXCSR register state to m512byte.*/
    { FCML_AMT_SIMD | FCML_AMT_FPU, 0x0008, 0x04998000, { 0x0F, 0xAE, 0x00 }, { FCML_OP_MODRM_M_OP_512B_W, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FXTRACT[] = {
	/* D9 F4 FXTRACT Valid Valid Separate value in ST(0) into exponent and significand, store exponent in ST(0), and push the significand onto the register stack.*/
    { FCML_AMT_FPU, 0x0000, 0x00D80000, { 0xD9, 0xF4, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FYL2X[] = {
	/* D9 F1 FYL2X Valid Valid Replace ST(1) with (ST(1) log2ST(0)) and pop the register stack.*/
    { FCML_AMT_FPU, 0x0000, 0x00D80000, { 0xD9, 0xF1, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FYL2XP1[] = {
	/* D9 F9 FYL2XP1 Valid Valid Replace ST(1) with ST(1) log2(ST(0) + 1.0) and pop the register stack.*/
    { FCML_AMT_FPU, 0x0000, 0x00D80000, { 0xD9, 0xF9, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_GETSEC[] = {
	/* 0F 37  GETSEC[X] Report the SMX capabilities.*/
    { FCML_AMT_SMX, 0x0000, 0x00D80000, { 0x0F, 0x37, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_HADDPD[] = {
	/* 66 0F 7C /r HADDPD xmm1, xmm2/m128 A Valid Valid Horizontal add packed double-precision floatingpoint values from xmm2/m128 to xmm1.*/
    { FCML_AMT_SSE3_SIMD, 0x1000, 0x00D88000, { 0x0F, 0x7C, 0x00 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VHADDPD[] = {
	/* VEX.NDS.128.66.0F 7C /r VHADDPD xmm1,xmm2,xmm3/m128*/
	/* VEX.NDS.256.66.0F 7C /r VHADDPD ymm1,ymm2,ymm3/m256*/
    { FCML_AMT_AVX_SIMD, 0x1080, 0x00D88000, { 0x0F, 0x7C, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_HADDPS[] = {
	/* F2 0F 7C /r HADDPS xmm1, xmm2/m128 A Valid Valid Horizontal add packed single-precision floatingpoint values from xmm2/m128 to xmm1.*/
    { FCML_AMT_SSE3_SIMD, 0x2000, 0x00D88000, { 0x0F, 0x7C, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VHADDPS[] = {
	/* VEX.NDS.128.F2.0F 7C /r VHADDPS xmm1,xmm2,xmm3/m128*/
	/* VEX.NDS.256.F2.0F 7C /r VHADDPS ymm1,ymm2,ymm3/m256*/
    { FCML_AMT_AVX_SIMD, 0x2080, 0x00D88000, { 0x0F, 0x7C, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_HLT[] = {
	/* F4 HLT A Valid Valid Halt*/
    { FCML_AMT_SYSTEM, 0x0000, 0x00C40000, { 0xF4, 0x00, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_HSUBPD[] = {
	/* 66 0F 7D /r HSUBPD xmm1, xmm2/m128A Valid Valid Horizontal subtract packed double-precision floating pointvalues from xmm2/m128 to xmm1.*/
    { FCML_AMT_SSE3_SIMD, 0x1000, 0x00D88000, { 0x0F, 0x7D, 0x00 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VHSUBPD[] = {
	/* VEX.NDS.128.66.0F 7D /r VHSUBPD xmm1,xmm2,xmm3/m128*/
	/* VEX.NDS.256.66.0F 7D /r VHSUBPD ymm1,ymm2,ymm3/m256*/
    { FCML_AMT_AVX_SIMD, 0x1080, 0x00D88000, { 0x0F, 0x7D, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_HSUBPS[] = {
	/* F2 0F 7D /r HSUBPS xmm1, xmm2/m128 A Valid Valid Horizontal subtract packedsingle-precision floatingpoint values from xmm2/m128 to xmm1.*/
    { FCML_AMT_SSE3_SIMD, 0x2000, 0x00D88000, { 0x0F, 0x7D, 0x00 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VHSUBPS[] = {
	/* VEX.NDS.128.F2.0F 7D /r VHSUBPS xmm1,xmm2,xmm3/m128*/
	/* VEX.NDS.256.F2.0F 7D /r VHSUBPS ymm1,ymm2,ymm3/m256*/
    { FCML_AMT_AVX_SIMD, 0x2080, 0x00D88000, { 0x0F, 0x7D, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_INVEPT[] = {
	/* 66 0F 38 80 INVEPT r64, m128 Invalidates EPT-derived entries in the TLBs and paging-structure caches (in 64-bit mode)*/
	/* 66 0F 38 80 INVEPT r32, m128 Invalidates EPT-derived entries in the TLBs and paging-structure caches (outside 64-bit mode)*/
    { FCML_AMT_VMX, 0x1000, 0x006C8000, { 0x0F, 0x38, 0x80 }, { FCML_OP_MODRM_R_32, FCML_OP_MODRM_RM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_R32_M128 },
    { FCML_AMT_VMX, 0x1000, 0x00AC8000, { 0x0F, 0x38, 0x80 }, { FCML_OP_MODRM_R_64, FCML_OP_MODRM_RM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_R64_M128 }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_INVVPID[] = {
	/* 66 0F 38 81 INVVPID r64, m128 Invalidates entries in the TLBs and paging-structure caches based on VPID (in 64-bit mode)*/
	/* 66 0F 38 81 INVVPID r32, m128 Invalidates entries in the TLBs and paging-structure caches based on VPID (outside 64-bit mode)*/
    { FCML_AMT_VMX, 0x1000, 0x006C8000, { 0x0F, 0x38, 0x81 }, { FCML_OP_MODRM_R_32, FCML_OP_MODRM_RM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_R32_M128 },
    { FCML_AMT_VMX, 0x1000, 0x00AC8000, { 0x0F, 0x38, 0x81 }, { FCML_OP_MODRM_R_64, FCML_OP_MODRM_RM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_R64_M128 }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_IDIV[] = {
	/* F6 /7 IDIV r/m8 A Valid Valid Signed divide AX by r/m8,with result stored in: AL Quotient, AH Remainder.*/
	/* REX + F6 /7 IDIV r/m8* A Valid N.E. Signed divide AX by r/m8, with result stored in AL Quotient, AH Remainder.*/
    { FCML_AMT_GPI, 0x0000, 0x00C5B800, { 0xF6, 0x00, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_AX, FCML_EOS_WORD ), FCML_OP_MODRM_RM_8_W, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RM8 },
	/* F7 /7 IDIV r/m16 A Valid Valid Signed divide DX:AX by r/m16, with result stored in AX Quotient, DX Remainder.*/
	/* F7 /7 IDIV r/m32 A Valid Valid Signed divide EDX:EAX by r/m32, with result stored in EAX Quotient, EDX Remainder.*/
	/* REX.W + F7 /7 IDIV r/m64 A Valid N.E. Signed divide RDX:RAX by r/m64, with result stored in RAX Quotient, RDX Remainder.*/
    { FCML_AMT_GPI, 0x0000, 0x00C5B800, { 0xF7, 0x00, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_AL, FCML_EOS_EOSA ), FCML_OP_MODRM_RM_W, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RMO }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_IMUL[] = {
	/* F6 /5 IMUL r/m8* A Valid Valid AX AL r/m byte.*/
    { FCML_AMT_GPI, 0x0000, 0x00C5A800, { 0xF6, 0x00, 0x00 }, { FCML_OP_MODRM_RM_8_RW, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RM8 },
	/* F7 /5 IMUL r/m16 A Valid Valid DX:AX AX r/m word.*/
	/* F7 /5 IMUL r/m32 A Valid Valid EDX:EAX EAX r/m32.*/
	/* REX.W + F7 /5 IMUL r/m64 A Valid N.E. RDX:RAX RAX r/m64.*/
    { FCML_AMT_GPI, 0x0000, 0x00C5A800, { 0xF7, 0x00, 0x00 }, { FCML_OP_MODRM_RM_RW, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RMO },
	/* 0F AF /r IMUL r16, r/m16 B Valid Valid word register word register r/m16.*/
	/* 0F AF /r IMUL r32, r/m32 B Valid Valid doubleword register doubleword register r/m32.*/
	/* REX.W + 0F AF /r IMUL r64, r/m64 B Valid N.E. Quadword register Quadword register r/m64.*/
    { FCML_AMT_GPI, 0x0000, 0x00D88000, { 0x0F, 0xAF, 0x00 }, { FCML_OP_MODRM_R_RW, FCML_OP_MODRM_RM,  FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RMO_RO },
	/* 6B /r ib IMUL r16, r/m16, int8 C Valid Valid word register r/m16 sign-extended immediate byte.*/
	/* 6B /r ib IMUL r32, r/m32, int8 C Valid Valid doubleword register r/m32 sign-extended immediate byte.*/
	/* REX.W + 6B /r ib IMUL r64, r/m64, int8 C Valid N.E. Quadword register r/m64 sign-extended immediate byte.*/
    { FCML_AMT_GPI, 0x0000, 0x00C48004, { 0x6B, 0x00, 0x00 }, { FCML_OP_MODRM_R_RW, FCML_OP_MODRM_RM, FCML_OP_IB_EX_EOSA, FCML_NA, FCML_NA }, FCML_AM_RO_RMO_IMM8 },
	/* 69 /r iw IMUL r16, r/m16, int16 C Valid Valid word register r/m16 immediate word.*/
	/* 69 /r id IMUL r32, r/m32, int32 C Valid Valid doubleword register r/m32 immediate doubleword.*/
    { FCML_AMT_GPI, 0x0010, 0x03C48004, { 0x69, 0x00, 0x00 }, { FCML_OP_MODRM_R_RW, FCML_OP_MODRM_RM_OP, FCML_OP_IMM_EOSA, FCML_NA, FCML_NA }, FCML_AM_RO_RMO_IMMO },
	/* REX.W + 69 /r id IMUL r64, r/m64, int32 C Valid N.E. Quadword register r/m64 immediate doubleword.*/
    { FCML_AMT_GPI, 0x0008, 0x04848004, { 0x69, 0x00, 0x00 }, { FCML_OP_MODRM_R_RW, FCML_OP_MODRM_RM_OP, FCML_OP_ID, FCML_NA, FCML_NA }, FCML_AM_RO_RMO_IMMO }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_IN[] = {
	/* E4 ib IN AL, int8 A Valid Valid Input byte from int8 I/O port address into AL.*/
    { FCML_AMT_GPI, 0x0000, 0x07C40000, { 0xE4, 0x00, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_AL, FCML_EOS_BYTE ) | FCML_OA_W, FCML_OP_IB, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* E5 ib IN AX, int8 A Valid Valid Input word from int8 I/O port address into AX.*/
    { FCML_AMT_GPI, 0x0000, 0x01C40000, { 0xE5, 0x00, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_AL, FCML_EOS_WORD) | FCML_OA_W, FCML_OP_IB, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* E5 ib IN EAX, int8 A Valid Valid Input dword from int8 I/O port address into EAX.*/
    { FCML_AMT_GPI, 0x0000, 0x06C40000, { 0xE5, 0x00, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_AL, FCML_EOS_DWORD) | FCML_OA_W, FCML_OP_IB, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* EC IN AL,DX B Valid Valid Input byte from I/O port in DX into AL.*/
    { FCML_AMT_GPI, 0x0000, 0x07C40000, { 0xEC, 0x00, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_AL, FCML_EOS_BYTE ) | FCML_OA_W, FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_DX, FCML_EOS_WORD ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* ED IN AX,DX B Valid Valid Input word from I/O port in DX into AX.*/
    { FCML_AMT_GPI, 0x0000, 0x01C40000, { 0xED, 0x00, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_AL, FCML_EOS_WORD ) | FCML_OA_W, FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_DX, FCML_EOS_WORD ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* ED IN EAX,DX B Valid Valid Input doubleword from I/O port in DX into EAX.*/
    { FCML_AMT_GPI, 0x0000, 0x06C40000, { 0xED, 0x00, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_AL, FCML_EOS_DWORD ) | FCML_OA_W, FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_DX, FCML_EOS_WORD ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_INC[] = {
	/* FE /0 INC r/m8 A Valid Valid Increment r/m byte by 1.*/
	/* REX + FE /0 INC r/m8* A Valid N.E. Increment r/m byte by 1.*/
    { FCML_AMT_GPI, 0x0807, 0x00C58000, { 0xFE, 0x00, 0x00 }, { FCML_OP_MODRM_RM_8_RW, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RM8 },
	/* FF /0 INC r/m16 A Valid Valid Increment r/m word by 1.*/
	/* FF /0 INC r/m32 A Valid Valid Increment r/m doubleword by 1.*/
	/* REX.W + FF /0 INC r/m64 A Valid N.E. Increment r/m quadword by 1.*/
    { FCML_AMT_GPI, 0x0807, 0x00C58000, { 0xFF, 0x00, 0x00 }, { FCML_OP_MODRM_RM_RW, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RMO },
	/* 40+ rw** INC r16 B N.E. Valid Increment word register by 1.*/
	/* 40+ rd INC r32 B N.E. Valid Increment doubleword register by 1.*/
    { FCML_AMT_GPI, 0x0000, 0x00440001, { 0x40, 0x00, 0x00 }, { FCML_OP_OPCODE_REG( FCML_REG_GPR, FCML_EOS_EOSA ) | FCML_OA_RW, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RO }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_INS[] = {
	/* 6C INS m8, DX A Valid Valid Input byte from I/O port specified in DX into memory location specified in ES:(E)DI or RDI.**/
    { FCML_AMT_GPI, 0x0004, 0x07C40000, { 0x6C, 0x00, 0x00 }, { FCML_OP_EXPLICIT_GPS_REG_ADDRESSING( FCML_REG_DI, FCML_EOS_BYTE, FCML_SEG_ENCODE_REGISTER( FCML_REG_ES, FCML_SEG_DENY_OVERRIDE ) ), FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_DX, FCML_EOS_WORD ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_M8 },
	/* 6D INS m16, DX A Valid Valid Input word from I/O port specified in DX into memory location specified in ES:(E)DI or RDI.1*/
    { FCML_AMT_GPI, 0x0004, 0x01C40000, { 0x6D, 0x00, 0x00 }, { FCML_OP_EXPLICIT_GPS_REG_ADDRESSING( FCML_REG_DI, FCML_EOS_WORD, FCML_SEG_ENCODE_REGISTER( FCML_REG_ES, FCML_SEG_DENY_OVERRIDE ) ), FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_DX, FCML_EOS_WORD ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_M16 },
	/* 6D INS m32, DX A Valid Valid Input doubleword from I/O port specified in DX into memory location specified in ES:(E)DI or RDI.1*/
    { FCML_AMT_GPI, 0x0004, 0x06C40000, { 0x6D, 0x00, 0x00 }, { FCML_OP_EXPLICIT_GPS_REG_ADDRESSING( FCML_REG_DI, FCML_EOS_DWORD, FCML_SEG_ENCODE_REGISTER( FCML_REG_ES, FCML_SEG_DENY_OVERRIDE ) ), FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_DX, FCML_EOS_WORD ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_M32 }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_INSERTPS[] = {
	/* 66 0F 3A 21 /r ib INSERTPS xmm1, xmm2/m32, int8 A Valid Valid Insert a single precision floating-point value selected by int8 from xmm2/m32 into xmm1 at the specified destination element specified by int8 and zero out destination elements in xmm1 as indicated in int8.*/
    { FCML_AMT_SSE41_SIMD, 0x1000, 0x00EC8000, { 0x0F, 0x3A, 0x021 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_OP_32, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VINSERTPS[] = {
	/* VEX.NDS.128.66.0F3A 21 /r ib VINSERTPS xmm1,xmm2,xmm3/m32,int8*/
    { FCML_AMT_AVX_SIMD, 0x10C0, 0x00EC8000, { 0x0F, 0x3A, 0x21 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_32, FCML_OP_IB, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_INSERTQ[] = {
	/* INSERTQ xmm1, xmm2, int8, int8 F2 0F 78 /r ib ib*/
    { FCML_AMT_SSE4A, 0x2000, 0x00DA8000, { 0x0F, 0x78, 0x00 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_RM( FCML_REG_SIMD, FCML_EOS_OWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_OP_IB, FCML_OP_IB, FCML_NA }, FCML_AM_RX_RX_I8_I8 },
	/* INSERTQ xmm1, xmm2 F2 0F 79 /r*/
    { FCML_AMT_SSE4A, 0x2000, 0x00DA8000, { 0x0F, 0x79, 0x00 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_RM( FCML_REG_SIMD, FCML_EOS_OWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RX_RX }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VEXTRACTF128[] = {
	/* VEX.256.66.0F3A 19 /r ib VEXTRACTF128 xmm1/m128,ymm2,int8*/
    { FCML_AMT_AVX_SIMD, 0x10A0, 0x00EC8000, { 0x0F, 0x3A, 0x19 }, { FCML_OP_MODRM_RM_XMM_OP_128_W, FCML_OP_MODRM_R_YMM, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VINSERTF128[] = {
	/* VEX.NDS.256.66.0F3A 18 /r ib VINSERTF128 ymm1,ymm2,xmm3/m128,int8*/
    { FCML_AMT_AVX_SIMD, 0x10A0, 0x00EC8000, { 0x0F, 0x3A, 0x18 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_YMM_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_OP_IB, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_INT3[] = {
	/* CC INT 3 A Valid Valid Interrupt 3trap to debugger.*/
    { FCML_AMT_GPI | FCML_AMT_CTI, 0x0000, 0x00C40000, { 0xCC, 0x00, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_INT[] = {
	/* CD ib INT int8 B Valid Valid Interrupt vector number specified by immediate byte.*/
    { FCML_AMT_GPI | FCML_AMT_CTI, 0x0000, 0x00C40000, { 0xCD, 0x00, 0x00 }, { FCML_OP_IB, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_IMM8 }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_INTO[] = {
	/* CE INTO A Invalid Valid Interrupt 4if overflow flag is 1.*/
    { FCML_AMT_GPI | FCML_AMT_CTI, 0x0000, 0x00440000, { 0xCE, 0x00, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_INVD[] = {
	/* 0F 08 INVD A Valid Valid Flush internal caches; initiate flushing of external caches.*/
    { FCML_AMT_SYSTEM, 0x0000, 0x00D80000, { 0x0F, 0x08, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_INVLPG[] = {
	/* 0F 01/7 INVLPG m A Valid Valid Invalidate TLB Entry for page that contains m.*/
    { FCML_AMT_SYSTEM, 0x0000, 0x00D9B800, { 0x0F, 0x01, 0x00 }, { FCML_OP_MODRM_M_UNDEF_W, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_INVLPGA[] = {
	/* INVLPGA rAX, ECX 0F 01 DF*/
    { FCML_AMT_SVM, 0x0000, 0x00EC0000, { 0x0F, 0x01, 0xDF }, { FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_EAX, FCML_EOS_EASA ), FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_ECX, FCML_EOS_DWORD ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_INVPCID[] = {
	/* 66 0F 38 82 /r INVPCID r32, m128 RM NE/V INVPCID Invalidates entries in the TLBs and paging-structure caches based on invalidation type in r32 and descriptor in m128.*/
    { FCML_AMT_SYSTEM, 0x1000, 0x006C8000, { 0x0F, 0x38, 0x82 }, { FCML_OP_MODRM_R_32, FCML_OP_RM( FCML_REG_UNDEFINED, FCML_EOS_UNDEFINED, FCML_EOS_OWORD | FCML_EOS_OPT, FCML_RMF_M ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RO_MO },
	/* 66 0F 38 82 /r INVPCID r64, m128 RM V/NE INVPCID Invalidates entries in the TLBs and paging-structure caches based on invalidation type in r64 and descriptor in m128.*/
    { FCML_AMT_SYSTEM, 0x1000, 0x00AC8000, { 0x0F, 0x38, 0x82 }, { FCML_OP_MODRM_R_64, FCML_OP_RM( FCML_REG_UNDEFINED, FCML_EOS_UNDEFINED, FCML_EOS_OWORD | FCML_EOS_OPT, FCML_RMF_M ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RO_MO }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_IRET[] = {
	/* CF IRET A Valid Valid Interrupt return (16-bit operand size).*/
	/* CF IRETD A Valid Valid Interrupt return (32-bit operand size).*/
	/* REX.W + CF IRETQ A Valid N.E. Interrupt return (64-bit operand size).*/
    { FCML_AMT_GPI | FCML_AMT_CTI, 0x0000, 0x00C40000, { 0xCF, 0x00, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_LAHF[] = {
	/* 9F LAHF A Invalid* Valid Load: AH EFLAGS(SF:ZF:0:AF:0:PF:1:CF).*/
    { FCML_AMT_GPI, 0x0000, 0x00C40000, { 0x9F, 0x00, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_LAR[] = {
	/* 0F 02 /r LAR r16, r16/m16 A Valid Valid r16 r16/m16 masked by FF00H.*/
	/* 0F 02 /r LAR r32, r32/m16 A Valid Valid r32 r32/m16 masked by 00FxFF00H*/
    { FCML_AMT_SYSTEM, 0x0000, 0x03D88000, { 0x0F, 0x02, 0x00 }, { FCML_OP_MODRM_R_W, FCML_OP_RM( FCML_REG_GPR, FCML_EOS_EOSA, FCML_EOS_WORD | FCML_EOS_OPT, FCML_RMF_RM ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* REX.W + 0F 02 /r LAR r64, r32/m16 A Valid N.E. r64 r32/m16 masked by 00FxFF00H*/
    { FCML_AMT_SYSTEM, 0x0000, 0x04988000, { 0x0F, 0x02, 0x00 }, { FCML_OP_MODRM_R_W, FCML_OP_RM( FCML_REG_GPR, FCML_EOS_DWORD, FCML_EOS_WORD | FCML_EOS_OPT, FCML_RMF_RM ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_LDDQU[] = {
	/* F2 0F F0 /r LDDQU xmm1, mem A Valid Valid Load unaligned data from mem and return double quadword in xmm1.*/
    { FCML_AMT_SSE3, 0x2000, 0x00D88000, { 0x0F, 0xF0, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_M_UNDEF, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VLDDQU[] = {
	/* VEX.128.F2.0F F0 /r VLDDQU xmm1, m128*/
	/* VEX.256.F2.0F F0 /r VLDDQU ymm1, m256*/
    { FCML_AMT_AVX_SIMD, 0x2080, 0x00D88000, { 0x0F, 0xF0, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_RM( FCML_REG_SIMD, FCML_EOS_UNDEFINED, FCML_EOS_L | FCML_EOS_OPT, FCML_RMF_M ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_LDMXCSR[] = {
	/* 0F AE /2 LDMXCSR m32 A Valid Valid Load MXCSR register from m32.*/
    { FCML_AMT_SSE, 0x0000, 0x00D99000, { 0x0F, 0xAE, 0x00 }, { FCML_OP_MODRM_M_OP_32, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VLDMXCSR[] = {
	/* VEX.128.0F AE /2 VLDMXCSR m32*/
    { FCML_AMT_AVX, 0x00C0, 0x00D99000, { 0x0F, 0xAE, 0x00 }, { FCML_OP_RM( FCML_REG_UNDEFINED, FCML_EOS_UNDEFINED, FCML_EOS_DWORD | FCML_EOS_OPT, FCML_RMF_M ), FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_LDS[] = {
	/* C5 /r LDS r16,m16:16 A Invalid Valid Load DS:r16 with far pointer from memory.*/
	/* C5 /r LDS r32,m16:32 A Invalid Valid Load DS:r32 with far pointer from memory.*/
    { FCML_AMT_GPI, 0x0000, 0x00448000, { 0xC5, 0x00, 0x00 }, { FCML_OP_MODRM_R_W, FCML_OP_MODRM_M_OP_FP, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_LSS[] = {
	/* 0F B2 /r LSS r16,m16:16 A Valid Valid Load SS:r16 with far pointer from memory.*/
	/* 0F B2 /r LSS r32,m16:32 A Valid Valid Load SS:r32 with far pointer from memory.*/
	/* REX + 0F B2 /r LSS r64,m16:64 A Valid N.E. Load SS:r64 with far pointer from memory.*/
    { FCML_AMT_GPI, 0x0000, 0x00D88000, { 0x0F, 0xB2, 0x00 }, { FCML_OP_MODRM_R_W, FCML_OP_MODRM_M_OP_FP, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_LES[] = {
	/* C4 /r LES r16,m16:16 A Invalid Valid Load ES:r16 with far pointer from memory.*/
	/* C4 /r LES r32,m16:32 A Invalid Valid Load ES:r32 with far pointer from memory.*/
    { FCML_AMT_GPI, 0x0000, 0x00448000, { 0xC4, 0x00, 0x00 }, { FCML_OP_MODRM_R_W, FCML_OP_MODRM_M_OP_FP, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_LFS[] = {
	/* 0F B4 /r LFS r16,m16:16 A Valid Valid Load FS:r16 with far pointer from memory.*/
	/* 0F B4 /r LFS r32,m16:32 A Valid Valid Load FS:r32 with far pointer from memory.*/
	/* REX + 0F B4 /r LFS r64,m16:64 A Valid N.E. Load FS:r64 with far pointer from memory.*/
    { FCML_AMT_GPI, 0x0000, 0x00D88000, { 0x0F, 0xB4, 0x00 }, { FCML_OP_MODRM_R_W, FCML_OP_MODRM_M_OP_FP, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_LGS[] = {
	/* 0F B5 /r LGS r16,m16:16 A Valid Valid Load GS:r16 with far pointer from memory.*/
	/* 0F B5 /r LGS r32,m16:32 A Valid Valid Load GS:r32 with far pointer from memory.*/
	/* REX + 0F B5 /r LGS r64,m16:64 A Valid N.E. Load GS:r64 with far pointer from memory.*/
    { FCML_AMT_GPI, 0x0000, 0x00D88000, { 0x0F, 0xB5, 0x00 }, { FCML_OP_MODRM_R_W, FCML_OP_MODRM_M_OP_FP, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_LEA[] = {
	/* 8D /r LEA r16,m A Valid Valid Store effective address for m in register r16.*/
	/* 8D /r LEA r32,m A Valid Valid Store effective address for m in register r32.*/
	/* REX.W + 8D /r LEA r64,m A Valid N.E. Store effective address for m in register r64.*/
    { FCML_AMT_GPI, 0x0000, 0x00C48000, { 0x8D, 0x00, 0x00 }, { FCML_OP_MODRM_R_W, FCML_OP_MODRM_M_UNDEF, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_LEAVE[] = {
	/* C9 LEAVE A Valid Valid Set SP to BP, then pop BP.*/
	/* C9 LEAVE A N.E. Valid Set ESP to EBP, then pop EBP.*/
	/* C9 LEAVE A Valid N.E. Set RSP*/
    { FCML_AMT_GPI | FCML_AMT_CTI, 0x0000, 0x00C40000, { 0xC9, 0x00, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_LFENCE[] = {
    /* LFENCE 0F AE E8 Force strong ordering of (serialize) load operations.*/
    { FCML_AMT_SSE2, 0x0000, 0x00EC0000, { 0x0F, 0xAE, 0xE8 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_LLWPCB[] = {
	/* LLWPCB reg32 8F RXB.09 0.1111.0.00 12 /0*/
    { FCML_AMT_LWP, 0x0450, 0x00DB8000, { 0x09, 0x12, 0x00 }, { FCML_OP_RM( FCML_REG_GPR, FCML_EOS_DWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* LLWPCB reg64 8F RXB.09 1.1111.0.00 12 /0*/
    { FCML_AMT_LWP, 0x0448, 0x00DB8000, { 0x09, 0x12, 0x00 }, { FCML_OP_RM( FCML_REG_GPR, FCML_EOS_QWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_LGDT[] = {
	/* 0F 01 /2 LGDT m16&32 A N.E. Valid Load m into GDTR.*/
    { FCML_AMT_SYSTEM, 0x0000, 0x00599000, { 0x0F, 0x01, 0x00 }, { FCML_OP_RM( FCML_REG_UNDEFINED, FCML_EOS_UNDEFINED, (FCML_EOS_WORD + FCML_EOS_DWORD) | FCML_EOS_OPT, FCML_RMF_M ), FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* 0F 01 /2 LGDT m16&64 A Valid N.E. Load m into GDTR.*/
    { FCML_AMT_SYSTEM, 0x0000, 0x00999000, { 0x0F, 0x01, 0x00 }, { FCML_OP_RM( FCML_REG_UNDEFINED, FCML_EOS_UNDEFINED, (FCML_EOS_WORD + FCML_EOS_QWORD) | FCML_EOS_OPT, FCML_RMF_M ), FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_LIDT[] = {
	/* 0F 01 /3 LIDT m16&32 A N.E. Valid Load m into IDTR.*/
    { FCML_AMT_SYSTEM, 0x0000, 0x00599800, { 0x0F, 0x01, 0x00 }, { FCML_OP_RM( FCML_REG_UNDEFINED, FCML_EOS_UNDEFINED, (FCML_EOS_WORD + FCML_EOS_DWORD) | FCML_EOS_OPT, FCML_RMF_M ), FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* 0F 01 /3 LIDT m16&64 A Valid N.E. Load m into IDTR.*/
    { FCML_AMT_SYSTEM, 0x0000, 0x00999800, { 0x0F, 0x01, 0x00 }, { FCML_OP_RM( FCML_REG_UNDEFINED, FCML_EOS_UNDEFINED, (FCML_EOS_WORD + FCML_EOS_QWORD) | FCML_EOS_OPT, FCML_RMF_M ), FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_LLDT[] = {
	/* 0F 00 /2 LLDT r/m16 A Valid Valid Load segment selector r/m16 into LDTR.*/
    { FCML_AMT_SYSTEM, 0x0000, 0x00D99000, { 0x0F, 0x00, 0x00 }, { FCML_OP_MODRM_RM_OP_16, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_LMSW[] = {
	/* 0F 01 /6 LMSW r/m16 A Valid Valid Loads r/m16 in machine status word of CR0.*/
    { FCML_AMT_SYSTEM, 0x0000, 0x00D9B000, { 0x0F, 0x01, 0x00 }, { FCML_OP_MODRM_RM_OP_16, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_LODS[] = {
	/* AC LODS m8 A Valid Valid For legacy mode, Load byte at address DS:(E)SI into AL. For 64-bit mode load byte at address (R)SI into AL.*/
    { FCML_AMT_GPI, 0x0004, 0x00C40000, { 0xAC, 0x00, 0x00 }, { FCML_OP_EXPLICIT_GPS_REG_ADDRESSING( FCML_REG_SI, FCML_EOS_BYTE, FCML_SEG_ENCODE_REGISTER( FCML_REG_DS, FCML_SEG_ALLOW_OVERRIDE ) ), FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RM8 },
	/* AD LODS m16 A Valid Valid For legacy mode, Load word at address DS:(E)SI into AX. For 64-bit mode load word at address (R)SI into AX.*/
	/* AD  LODS m32 A Valid Valid For legacy mode, Load dword at address DS:(E)SI into EAX. For 64-bit mode load dword at address (R)SI into EAX.*/
	/* REX.W + AD LODS m64 A Valid N.E. Load qword at address (R)SI into RAX.*/
    { FCML_AMT_GPI, 0x0004, 0x00C40000, { 0xAD, 0x00, 0x00 }, { FCML_OP_EXPLICIT_GPS_REG_ADDRESSING( FCML_REG_SI, FCML_EOS_EOSA,FCML_SEG_ENCODE_REGISTER( FCML_REG_DS, FCML_SEG_ALLOW_OVERRIDE ) ), FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RMO }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_LOOP[] = {
	/* E2 cb LOOP rel8 A Valid Valid Decrement count; jump short if count 0.*/
    { FCML_AMT_GPI | FCML_AMT_CTI | FCML_AMT_BRANCH, 0x0000, 0x00C40000, { 0xE2, 0x00, 0x00 }, { FCML_OP_IMMEDIATE_DIS_RELATIVE_R_8, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_LOOPE[] = {
	/* E1 cb LOOPE rel8 A Valid Valid Decrement count; jump short if count 0 and ZF = 1.*/
    { FCML_AMT_GPI | FCML_AMT_CTI | FCML_AMT_BRANCH, 0x0000, 0x00C40000, { 0xE1, 0x00, 0x00 }, { FCML_OP_IMMEDIATE_DIS_RELATIVE_R_8, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_LOOPNE[] = {
	/* E0 cb LOOPNE rel8 A Valid Valid Decrement count; jump short if count 0 and ZF = 0.*/
    { FCML_AMT_GPI | FCML_AMT_CTI | FCML_AMT_BRANCH, 0x0000, 0x00C40000, { 0xE0, 0x00, 0x00 }, { FCML_OP_IMMEDIATE_DIS_RELATIVE_R_8, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_LWPINS[] = {
	/* LWPINS reg32.vvvv, reg/mem32, int32 8F RXB.0A 0.src1.0.00 12 /0 /int32*/
    { FCML_AMT_LWP, 0x0450, 0x00D98000, { 0x0A, 0x12, 0x00 }, { FCML_OP_VEX_VVVV_REG( FCML_REG_GPR, FCML_EOS_DWORD ) | FCML_OA_W, FCML_OP_MODRM_RM_OP_32, FCML_OP_ID, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* LWPINS reg64.vvvv, reg/mem32, int32 8F RXB.0A 1.src1.0.00 12 /0 /int32*/
    { FCML_AMT_LWP, 0x0448, 0x00D98000, { 0x0A, 0x12, 0x00 }, { FCML_OP_VEX_VVVV_REG( FCML_REG_GPR, FCML_EOS_QWORD ) | FCML_OA_W, FCML_OP_MODRM_RM_OP_32, FCML_OP_ID, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_LWPVAL[] = {
	/* LWPVAL reg32.vvvv, reg/mem32, int32 8F RXB.0A 0.src1.0.00 12 /1 /int32*/
    { FCML_AMT_LWP, 0x0450, 0x00D98800, { 0x0A, 0x12, 0x00 }, { FCML_OP_VEX_VVVV_REG( FCML_REG_GPR, FCML_EOS_DWORD ) | FCML_OA_W, FCML_OP_MODRM_RM_OP_32, FCML_OP_ID, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* LWPVAL reg64.vvvv, reg/mem32, int32 8F RXB.0A 1.src1.0.00 12 /1 /int32*/
    { FCML_AMT_LWP, 0x0448, 0x00D98800, { 0x0A, 0x12, 0x00 }, { FCML_OP_VEX_VVVV_REG( FCML_REG_GPR, FCML_EOS_QWORD ) | FCML_OA_W, FCML_OP_MODRM_RM_OP_32, FCML_OP_ID, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_LSL[] = {
	/* 0F 03 /r LSL r16, r16/m16 A Valid Valid Load: r16 segment limit, selector r16/m16.*/
	/* 0F 03 /r LSL r32, r32/m16* A Valid Valid Load: r32 segment limit, selector r32/m16.*/
	/* REX.W + 0F 03 /r LSL r64, r32/m16* A Valid Valid Load: r64 segment limit, selector r32/m16*/
    { FCML_AMT_SYSTEM, 0x0000, 0x00D88000, { 0x0F, 0x03, 0x00 }, { FCML_OP_MODRM_R_W, FCML_OP_MODRM_RM_OP_16, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_LTR[] = {
	/* 0F 00 /3 LTR r/m16 A Valid Valid Load r/m16 into task register.*/
    { FCML_AMT_SYSTEM, 0x0000, 0x00D99800, { 0x0F, 0x00, 0x00 }, { FCML_OP_MODRM_RM_OP_16, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_MASKMOVDQU[] = {
	/* 66 0F F7 /r MASKMOVDQU xmm1, xmm2 A Valid Valid Selectively write bytes from xmm1 to memory location using the byte mask in xmm2. The default memory location is specified by DS:EDI/RDI.*/
    { FCML_AMT_SSE2, 0x1000, 0x00DA8000, { 0x0F, 0xF7, 0x00 }, { FCML_OP_R( FCML_REG_SIMD, FCML_EOS_XWORD ) | FCML_OA_W, FCML_OP_RM( FCML_REG_SIMD, FCML_EOS_XWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VMASKMOVDQU[] = {
	/* VEX.128.66.0F F7 /r VMASKMOVDQU xmm1,xmm2*/
    { FCML_AMT_AVX_SIMD, 0x10C0, 0x00DA8000, { 0x0F, 0xF7, 0x00 }, { FCML_OP_R( FCML_REG_SIMD, FCML_EOS_XWORD ) | FCML_OA_W, FCML_OP_RM( FCML_REG_SIMD, FCML_EOS_XWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VMASKMOVPS[] = {
	/* VEX.NDS.128.66.0F38 2C /r VMASKMOVPS xmm1,xmm2,m128*/
	/* VEX.NDS.256.66.0F38 2C /r VMASKMOVPS ymm1,ymm2,m256*/
    { FCML_AMT_AVX_SIMD, 0x1080, 0x00EC8000, { 0x0F, 0x38, 0x2C }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_M_SIMD_OPL, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.NDS.128.66.0F38 2E /r VMASKMOVPS m128,xmm1,xmm2*/
	/* VEX.NDS.256.66.0F38 2E /r VMASKMOVPS m256,ymm1,ymm2*/
    { FCML_AMT_AVX_SIMD, 0x1080, 0x00EC8000, { 0x0F, 0x38, 0x2E }, { FCML_OP_MODRM_M_SIMD_OPL_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_R_SIMD_L, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VMASKMOVPD[] = {
	/* VEX.NDS.128.66.0F38 2D /r VMASKMOVPD xmm1,xmm2,m128*/
	/* VEX.NDS.256.66.0F38 2D /r VMASKMOVPD ymm1,ymm2,m256*/
    { FCML_AMT_AVX_SIMD, 0x1080, 0x00EC8000, { 0x0F, 0x38, 0x2D }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_M_SIMD_OPL, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.NDS.128.66.0F38 2F /r VMASKMOVPD m128,xmm1,xmm2*/
	/* VEX.NDS.256.66.0F38 2F /r VMASKMOVPD m256,ymm1,ymm2*/
    { FCML_AMT_AVX_SIMD, 0x1080, 0x00EC8000, { 0x0F, 0x38, 0x2F }, { FCML_OP_MODRM_M_SIMD_OPL_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_R_SIMD_L, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPMASKMOVD[] = {
	/* VEX.NDS.128.66.0F38.W0 8C /r VPMASKMOVD xmm1,xmm2,m128*/
	/* VEX.NDS.256.66.0F38.W0 8C /r VPMASKMOVD ymm1,ymm2,m256*/
    { FCML_AMT_AVX2_SIMD, 0x1090, 0x00EC8000, { 0x0F, 0x38, 0x8C }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_M_SIMD_OPL, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.NDS.128.66.0F38.W0 8E /r VPMASKMOVD m128,xmm1,xmm2*/
	/* VEX.NDS.256.66.0F38.W0 8E /r VPMASKMOVD m256,ymm1,ymm2*/
    { FCML_AMT_AVX2_SIMD, 0x1090, 0x00EC8000, { 0x0F, 0x38, 0x8E }, { FCML_OP_MODRM_M_SIMD_OPL_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_R_SIMD_L, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPMASKMOVQ[] = {
	/* VEX.NDS.128.66.0F38.W1 8C /r VPMASKMOVQ xmm1,xmm2,m128*/
	/* VEX.NDS.256.66.0F38.W1 8C /r VPMASKMOVQ ymm1,ymm2,m256*/
    { FCML_AMT_AVX2_SIMD, 0x1088, 0x00EC8000, { 0x0F, 0x38, 0x8C }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_M_SIMD_OPL, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.NDS.128.66.0F38.W1 8E /r VPMASKMOVQ m128,xmm1,xmm2*/
	/* VEX.NDS.256.66.0F38.W1 8E /r VPMASKMOVQ m256,ymm1,ymm2*/
    { FCML_AMT_AVX2_SIMD, 0x1088, 0x00EC8000, { 0x0F, 0x38, 0x8E }, { FCML_OP_MODRM_M_SIMD_OPL_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_R_SIMD_L, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_MASKMOVQ[] = {
	/* 0F F7 /r MASKMOVQ mm1, mm2 A Valid Valid Selectively write bytes from mm1 to memory location using the byte mask in mm2. The default memory location is specified by DS:EDI/RDI.*/
    { FCML_AMT_SSE_SIMD, 0x0000, 0x00DA8000, { 0x0F, 0xF7, 0x00 }, { FCML_OP_R( FCML_REG_SIMD, FCML_EOS_MWORD ), FCML_OP_RM( FCML_REG_SIMD, FCML_EOS_MWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_MAXPD[] = {
	/* 66 0F 5F /r MAXPD xmm1, xmm2/m128 A Valid Valid Return the maximum double-precision floatingpoint values between xmm2/m128 and xmm1.*/
    { FCML_AMT_SSE2_SIMD, 0x1000, 0x00D88000, { 0x0F, 0x5F, 0x00 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VMAXPD[] = {
	/* VEX.NDS.128.66.0F 5F /r VMAXPD xmm1,xmm2,xmm3/m128*/
	/* VEX.NDS.256.66.0F 5F /r VMAXPD ymm1,ymm2,ymm3/m256*/
    { FCML_AMT_AVX_SIMD, 0x1080, 0x00D88000, { 0x0F, 0x5F, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_MAXPS[] = {
	/* 0F 5F /r MAXPS xmm1, xmm2/m128 A Valid Valid Return the maximum singleprecision floating-point values between xmm2/m128 and xmm1.*/
    { FCML_AMT_SSE_SIMD, 0x0000, 0x00D88000, { 0x0F, 0x5F, 0x00 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VMAXPS[] = {
	/* VEX.NDS.128.0F 5F /r VMAXPS xmm1,xmm2,xmm3/m128*/
	/* VEX.NDS.256.0F 5F /r VMAXPS ymm1,ymm2,ymm3/m256*/
    { FCML_AMT_AVX_SIMD, 0x0080, 0x00D88000, { 0x0F, 0x5F, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_MAXSD[] = {
	/* F2 0F 5F /r MAXSD xmm1, xmm2/m64 A Valid Valid Return the maximum scalardouble-precision floatingpoint value between xmm2/mem64 and xmm1.*/
    { FCML_AMT_SSE2_SIMD, 0x2000, 0x00D88000, { 0x0F, 0x5F, 0x00 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VMAXSD[] = {
	/* VEX.NDS.128.F2.0F 5F /r VMAXSD xmm1,xmm2,xmm3/m64*/
    { FCML_AMT_AVX_SIMD, 0x20C0, 0x00D88000, { 0x0F, 0x5F, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_OP_64, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_MAXSS[] = {
	/* F3 0F 5F /r MAXSS xmm1, xmm2/m32 A Valid Valid Return the maximum scalarsingle-precision floatingpoint value between xmm2/mem32 and xmm1.*/
    { FCML_AMT_SSE_SIMD, 0x4000, 0x00D88000, { 0x0F, 0x5F, 0x00 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_32, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VMAXSS[] = {
	/* VEX.NDS.128.F3.0F 5F /r VMAXSS xmm1, xmm2, xmm3/m32*/
    { FCML_AMT_AVX_SIMD, 0x40C0, 0x00D88000, { 0x0F, 0x5F, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_OP_32, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_MFENCE[] = {
	/* MFENCE 0F AE /6  A Valid Valid Serializes load and store operations.*/
    { FCML_AMT_SSE2, 0x0000, 0x00EC0000, { 0x0F, 0xAE, 0xF0 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_MINPD[] = {
	/* 66 0F 5D /r MINPD xmm1, xmm2/m128 A Valid Valid Return the minimum doubleprecision floating-point values between xmm2/m128 and xmm1.*/
    { FCML_AMT_SSE2_SIMD, 0x1000, 0x00D88000, { 0x0F, 0x5D, 0x00 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VMINPD[] = {
	/* VEX.NDS.128.66.0F 5D /r VMINPD xmm1,xmm2,xmm3/m128*/
	/* VEX.NDS.256.66.0F 5D /r VMINPD ymm1,ymm2,ymm3/m256*/
    { FCML_AMT_AVX_SIMD, 0x1080, 0x00D88000, { 0x0F, 0x5D, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_MINPS[] = {
	/* 0F 5D /r MINPS xmm1, xmm2/m128 A Valid Valid Return the minimum singleprecision floating-point values between xmm2/m128 and xmm1.*/
    { FCML_AMT_SSE_SIMD, 0x0000, 0x00D88000, { 0x0F, 0x5D, 0x00 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VMINPS[] = {
	/* VEX.NDS.128.0F 5D /r VMINPS xmm1,xmm2,xmm3/m128*/
	/* VEX.NDS.256.0F 5D /r VMINPS ymm1,ymm2,ymm3/m256*/
    { FCML_AMT_AVX_SIMD, 0x0080, 0x00D88000, { 0x0F, 0x5D, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_MINSD[] = {
	/* F2 0F 5D /r MINSD xmm1, xmm2/m64 A Valid Valid Return the minimum scalar double-precision floatingpoint value between xmm2/mem64 and xmm1.*/
    { FCML_AMT_SSE2_SIMD, 0x2000, 0x00D88000, { 0x0F, 0x5D, 0x00 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VMINSD[] = {
	/* VEX.NDS.128.F2.0F 5D /r VMINSD xmm1, xmm2, xmm3/m64*/
    { FCML_AMT_AVX_SIMD, 0x20C0, 0x00D88000, { 0x0F, 0x5D, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_64, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_MINSS[] = {
	/* F3 0F 5D /r MINSS xmm1, xmm2/m32 A Valid Valid Return the minimum scalar single-precision floatingpoint value between xmm2/mem32 and xmm1.*/
    { FCML_AMT_SSE_SIMD, 0x4000, 0x00D88000, { 0x0F, 0x5D, 0x00 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_32, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VMINSS[] = {
	/* VEX.NDS.128.F3.0F 5D /r VMINSS xmm1,xmm2,xmm3/m32*/
    { FCML_AMT_AVX_SIMD, 0x40C0, 0x00D88000, { 0x0F, 0x5D, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_OP_32, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_MONITOR[] = {
	/* 0F 01 C8 MONITOR A Valid Valid Sets up a linear address range to be monitored by hardware and activates the monitor. The address range should be a write-back memory caching type. The address is DS:EAX*/
    { FCML_AMT_SSE3, 0x0000, 0x006C0000, { 0x0F, 0x01, 0xC8 }, { FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_EAX, FCML_EOS_DWORD ), FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_ECX, FCML_EOS_DWORD ), FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_EDX, FCML_EOS_DWORD ), FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
    { FCML_AMT_SSE3, 0x0000, 0x00AC0000, { 0x0F, 0x01, 0xC8 }, { FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_RAX, FCML_EOS_QWORD ), FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_RCX, FCML_EOS_QWORD ), FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_RDX, FCML_EOS_QWORD ), FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_MOV[] = {
	/* 88 /r MOV r/m8,r8 A Valid Valid Move r8 to r/m8.*/
	/* REX + 88 /r MOV r/m8***,r8*** A Valid N.E. Move r8 to r/m8.*/
    { FCML_AMT_GPI, 0x0804, 0x00C48000, { 0x88, 0x00, 0x00 }, { FCML_OP_MODRM_RM_OP_8_W, FCML_OP_MODRM_R_8, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RM8_R8 },
	/* 89 /r MOV r/m16,r16 A Valid Valid Move r16 to r/m16.*/
	/* 89 /r MOV r/m32,r32 A Valid Valid Move r32 to r/m32.*/
	/* REX.W + 89 /r MOV r/m64,r64 A Valid N.E. Move r64 to r/m64.*/
    { FCML_AMT_GPI, 0x0804, 0x00C48000, { 0x89, 0x00, 0x00 }, { FCML_OP_MODRM_RM_OP_W, FCML_OP_MODRM_R, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RMO_RO },
	/* 8A /r MOV r8,r/m8 B Valid Valid Move r/m8 to r8.*/
	/* REX + 8A /r MOV r8***,r/m8*** B Valid N.E. Move r/m8 to r8.*/
    { FCML_AMT_GPI, 0x0000, 0x00C48000, { 0x8A, 0x00, 0x00 }, { FCML_OP_MODRM_R_8_W, FCML_OP_MODRM_RM_OP_8, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_R8_RM8 },
	/* 8B /r MOV r16,r/m16 B Valid Valid Move r/m16 to r16.*/
	/* 8B /r MOV r32,r/m32 B Valid Valid Move r/m32 to r32.*/
	/* REX.W + 8B /r MOV r64,r/m64 B Valid N.E. Move r/m64 to r64.*/
    { FCML_AMT_GPI, 0x0000, 0x00C48000, { 0x8B, 0x00, 0x00 }, { FCML_OP_MODRM_R_W, FCML_OP_MODRM_RM_OP, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RO_RMO },
	/* MOV reg16/32/64/mem16,segReg*/
	/* 8C /r MOV r/m16,Sreg** A Valid Valid Move segment register to r/m16.*/
	/* REX.W + 8C /r MOV r/m64,Sreg** A Valid Valid Move zero extended 16-bit segment register to r/m64.*/
    { FCML_AMT_GPI, 0x0000, 0x00C48000, { 0x8C, 0x00, 0x00 }, { FCML_OP_RM( FCML_REG_GPR, FCML_EOS_EOSA, FCML_EOS_WORD | FCML_EOS_OPT, FCML_RMF_RM ) | FCML_OA_W, FCML_OP_R( FCML_REG_SEG, FCML_EOS_WORD ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RM_SR },
	/* MOV segReg, reg/mem16*/
	/* 8E /r MOV Sreg,r/m16** RM Valid Valid Move r/m16 to segment register.*/
	/* REX.W + 8E /r MOV Sreg,r/m64** RM Valid Valid Move lower 16 bits of r/m64 to segment register.*/
    { FCML_AMT_GPI, 0x0000, 0x00C48000, { 0x8E, 0x00, 0x00 }, { FCML_OP_R( FCML_REG_SEG, FCML_EOS_WORD ) | FCML_OA_W, FCML_OP_MODRM_RM_OP_16_W, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_SR_RM },
	/* A0 MOV AL,moffs8* C Valid Valid Move byte at (seg:offset) to AL.*/
	/* REX.W + A0 MOV AL,moffs8* C Valid N.E. Move byte at (offset) to AL.*/
    { FCML_AMT_GPI, 0x0000, 0x00C40000, { 0xA0, 0x00, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_AL, FCML_EOS_BYTE ) | FCML_OA_W, FCML_OP_SEGMENT_RELATIVE_OFFSET( FCML_EOS_BYTE, FCML_SEG_ENCODE_REGISTER( FCML_REG_DS, FCML_SEG_ALLOW_OVERRIDE ) ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_R8_MOFF8 },
	/* A1 MOV AX,moffs16* C Valid Valid Move word at (seg:offset) to AX.*/
	/* A1 MOV EAX,moffs32* C Valid Valid Move doubleword at (seg:offset) to EAX.*/
	/* REX.W + A1 MOV RAX,moffs64* C Valid N.E. Move quadword at (offset) to RAX.*/
    { FCML_AMT_GPI, 0x0000, 0x00C40000, { 0xA1, 0x00, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_AL, FCML_EOS_EOSA ) | FCML_OA_W, FCML_OP_SEGMENT_RELATIVE_OFFSET( FCML_EOS_EOSA, FCML_SEG_ENCODE_REGISTER( FCML_REG_DS, FCML_SEG_ALLOW_OVERRIDE ) ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RO_MOFFO },
	/* A2 MOV moffs8,AL D Valid Valid Move AL to (seg:offset).*/
	/* REX.W + A2 MOV moffs8***,AL D Valid N.E. Move AL to (offset).*/
    { FCML_AMT_GPI, 0x0000, 0x00C40000, { 0xA2, 0x00, 0x00 }, { FCML_OP_SEGMENT_RELATIVE_OFFSET( FCML_EOS_BYTE, FCML_SEG_ENCODE_REGISTER( FCML_REG_DS, FCML_SEG_ALLOW_OVERRIDE ) ) | FCML_OA_W, FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_AL, FCML_EOS_BYTE ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_MOFF8_R8 },
	/* A3 MOV moffs16*,AX D Valid Valid Move AX to (seg:offset).*/
	/* A3 MOV moffs32*,EAX D Valid Valid Move EAX to (seg:offset).*/
	/* REX.W + A3 MOV moffs64*,RAX D Valid N.E. Move RAX to (offset).*/
    { FCML_AMT_GPI, 0x0000, 0x00C40000, { 0xA3, 0x00, 0x00 }, { FCML_OP_SEGMENT_RELATIVE_OFFSET( FCML_EOS_EOSA, FCML_SEG_ENCODE_REGISTER( FCML_REG_DS, FCML_SEG_ALLOW_OVERRIDE ) ) | FCML_OA_W, FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_AL, FCML_EOS_EOSA ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_MOFFO_RO },
	/* B0+ rb MOV r8, int8 E Valid Valid Move int8 to r8.*/
	/* REX + B0+ rb MOV r8***, int8 E Valid N.E. Move int8 to r8.*/
    { FCML_AMT_GPI, 0x0000, 0x00C40001, { 0xB0, 0x00, 0x00 }, { FCML_OP_OPCODE_REG( FCML_REG_GPR, FCML_EOS_BYTE ) | FCML_OA_W, FCML_OP_IB, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_R8_IMM8 },
	/* B8+ rw MOV r16, int16 E Valid Valid Move int16 to r16.*/
	/* B8+ rd MOV r32, int32 E Valid Valid Move int32 to r32.*/
	/* REX.W + B8+ rd MOV r64, int64 E Valid N.E. Move int64 to r64.*/
    { FCML_AMT_GPI, 0x0000, 0x00C40001, { 0xB8, 0x00, 0x00 }, { FCML_OP_OPCODE_REG( FCML_REG_GPR, FCML_EOS_EOSA ) | FCML_OA_W, FCML_OP_IMM_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_R0_IMM0 },
	/* C6 /0 MOV r/m8, int8 F Valid Valid Move int8 to r/m8.*/
	/* REX + C6 /0 MOV r/m8***, int8 F Valid N.E. Move int8 to r/m8.*/
    { FCML_AMT_GPI, 0x0000, 0x00C58000, { 0xC6, 0x00, 0x00 }, { FCML_OP_MODRM_RM_8_W, FCML_OP_IB, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RM8_IMM8 },
	/* C7 /0 MOV r/m16, int16 F Valid Valid Move int16 to r/m16.*/
	/* C7 /0 MOV r/m32, int32 F Valid Valid Move int32 to r/m32.*/
    { FCML_AMT_GPI, 0x0010, 0x03C58000, { 0xC7, 0x00, 0x00 }, { FCML_OP_MODRM_RM_W, FCML_OP_IMM_EOSA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RMO_IMMO },
	/* REX.W + C7 /0 MOV r/m64, int32 F Valid N.E. Move int32 sign extended to 64-bits to r/m64.*/
    { FCML_AMT_GPI, 0x0008, 0x04858000, { 0xC7, 0x00, 0x00 }, { FCML_OP_MODRM_RM_W, FCML_OP_ID_EX_EOSA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RMO_IMMO },
	/* 0F 21/r MOV r32, DR0-DR7 A N.E. Valid Move debug register to r32*/
    { FCML_AMT_SYSTEM, 0x0000, 0x00588000, { 0x0F, 0x21, 0x00 }, { FCML_OP_RM( FCML_REG_GPR, FCML_EOS_DWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ) | FCML_OA_W, FCML_OP_R( FCML_REG_DR, FCML_EOS_DWORD ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_R32_DR },
	/* 0F 21/r MOV r64, DR0-DR7 A Valid N.E. Move extended debug register to r64.*/
    { FCML_AMT_SYSTEM, 0x0000, 0x00988000, { 0x0F, 0x21, 0x00 }, { FCML_OP_RM( FCML_REG_GPR, FCML_EOS_QWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ) | FCML_OA_W, FCML_OP_R( FCML_REG_DR, FCML_EOS_QWORD ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_R64_DR },
	/* 0F 23 /r MOV DR0-DR7, r32 A N.E. Valid Move r32 to debug register*/
    { FCML_AMT_SYSTEM, 0x0000, 0x00588000, { 0x0F, 0x23, 0x00 }, { FCML_OP_R( FCML_REG_DR, FCML_EOS_DWORD ) | FCML_OA_W, FCML_OP_RM( FCML_REG_GPR, FCML_EOS_DWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_DR_R32 },
	/* 0F 23 /r MOV DR0-DR7, r64 A Valid N.E. Move r64 to extended debug register.*/
    { FCML_AMT_SYSTEM, 0x0000, 0x00988000, { 0x0F, 0x23, 0x00 }, { FCML_OP_R( FCML_REG_DR, FCML_EOS_QWORD ) | FCML_OA_W, FCML_OP_RM( FCML_REG_GPR, FCML_EOS_QWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_DR_R64 },
	/* 0F 20/r MOV r32, CR0-CR7 A N.E. Valid Move control register to r32*/
    { FCML_AMT_SYSTEM, 0x0000, 0x00588000, { 0x0F, 0x20, 0x00 }, { FCML_OP_RM( FCML_REG_GPR, FCML_EOS_DWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ) | FCML_OA_W, FCML_OP_R( FCML_REG_CR, FCML_EOS_DWORD ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_R32_CR },
	/* 0F 20/r MOV r64, CR0-CR7 A Valid N.E. Move extended control register to r64.*/
	/* REX.R + 0F 20 /0 MOV r64, CR8 A Valid N.E. Move extended CR8 to r64.1*/
    { FCML_AMT_SYSTEM, 0x0000, 0x00988000, { 0x0F, 0x20, 0x00 }, { FCML_OP_RM( FCML_REG_GPR, FCML_EOS_QWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ) | FCML_OA_W, FCML_OP_R( FCML_REG_CR, FCML_EOS_QWORD ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_R64_CR },
	/* 0F 22 /r MOV CR0-CR7, r32 A N.E. Valid Move r32 to control register*/
    { FCML_AMT_SYSTEM, 0x0000, 0x00588000, { 0x0F, 0x22, 0x00 }, { FCML_OP_R( FCML_REG_CR, FCML_EOS_DWORD ) | FCML_OA_W, FCML_OP_RM( FCML_REG_GPR, FCML_EOS_DWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_CR_R32 },
	/* 0F 22 /r MOV CR0-CR7, r64 A Valid N.E. Move r64 to extended control register.*/
	/* REX.R + 0F 22 /0 MOV CR8, r64 A Valid N.E. Move r64 to extended CR8.1*/
    { FCML_AMT_SYSTEM, 0x0000, 0x00988000, { 0x0F, 0x22, 0x00 }, { FCML_OP_R( FCML_REG_CR, FCML_EOS_QWORD ) | FCML_OA_W, FCML_OP_RM( FCML_REG_GPR, FCML_EOS_QWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_CR_R64 }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_MOVAPD[] = {
	/* 66 0F 28 /r MOVAPD xmm1, xmm2/m128 A Valid Valid Move packed doubleprecision floating-point values from xmm2/m128 to xmm1.*/
    { FCML_AMT_SSE2_SIMD, 0x1000, 0x00D88000, { 0x0F, 0x28, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* 66 0F 29 /r MOVAPD xmm2/m128, xmm1 B Valid Valid Move packed doubleprecision floating-point values from xmm1 to xmm2/m128.*/
    { FCML_AMT_SSE2_SIMD, 0x1000, 0x00D88000, { 0x0F, 0x29, 0x00 }, { FCML_OP_MODRM_RM_XMM_OP_128_W, FCML_OP_MODRM_R_XMM, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VMOVAPD[] = {
	/* VEX.128.66.0F 28 /r VMOVAPD xmm1,xmm2/m128*/
	/* VEX.256.66.0F 28 /r VMOVAPD ymm1,ymm2/m256*/
    { FCML_AMT_AVX_SIMD, 0x1080, 0x00D88000, { 0x0F, 0x28, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.128.66.0F 29 /r VMOVAPD xmm2/m128,xmm1*/
	/* VEX.256.66.0F 29 /r VMOVAPD ymm2/m256,ymm1*/
    { FCML_AMT_AVX_SIMD, 0x1080, 0x00D88000, { 0x0F, 0x29, 0x00 }, { FCML_OP_MODRM_RM_SIMD_L_OP_W, FCML_OP_MODRM_R_SIMD_L, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_MOVAPS[] = {
	/* 0F 28 /r MOVAPS xmm1, xmm2/m128 A Valid Valid Move packed singleprecision floating-point values from xmm2/m128 to xmm1.*/
    { FCML_AMT_SSE_SIMD, 0x0000, 0x00D88000, { 0x0F, 0x28, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* 0F 29 /r MOVAPS xmm2/m128, xmm1 B Valid Valid Move packed singleprecision floating-point values from xmm1 to xmm2/m128.*/
    { FCML_AMT_SSE_SIMD, 0x0000, 0x00D88000, { 0x0F, 0x29, 0x00 }, { FCML_OP_MODRM_RM_XMM_OP_128_W, FCML_OP_MODRM_R_XMM, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VMOVAPS[] = {
	/* VEX.128.0F 28 /r VMOVAPS xmm1,xmm2/m128*/
	/* VEX.256.0F 28 /r VMOVAPS ymm1,ymm2/m256*/
    { FCML_AMT_AVX_SIMD, 0x0080, 0x00D88000, { 0x0F, 0x28, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.128.0F 29 /r VMOVAPS xmm2/m128,xmm1*/
	/* VEX.256.0F 29 /r VMOVAPS ymm2/m256,ymm1*/
    { FCML_AMT_AVX_SIMD, 0x0080, 0x00D88000, { 0x0F, 0x29, 0x00 }, { FCML_OP_MODRM_RM_SIMD_L_OP_W, FCML_OP_MODRM_R_SIMD_L, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_MOVBE[] = {
	/* 0F 38 F0 /r MOVBE r16, m16 A Valid Valid Reverse byte order in m16 and move to r16*/
	/* 0F 38 F0 /r MOVBE r32, m32 A Valid Valid Reverse byte order in m32 and move to r32*/
	/* REX.W + 0F 38 F0 /r MOVBE r64, m64 A Valid N.E. Reverse byte order in m64 and move to r64.*/
    { FCML_AMT_GPI, 0x0000, 0x00EC8000, { 0x0F, 0x38, 0xF0 }, { FCML_OP_MODRM_R_W, FCML_OP_MODRM_M_OP, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* 0F 38 F1 /r MOVBE m16, r16 B Valid Valid Reverse byte order in r16 and move to m16*/
	/* 0F 38 F1 /r MOVBE m32, r32 B Valid Valid Reverse byte order in r32 and move to m32*/
	/* REX.W + 0F 38 F1 /r MOVBE m64, r64 B Valid N.E. Reverse byte order in*/
    { FCML_AMT_GPI, 0x0000, 0x00EC8000, { 0x0F, 0x38, 0xF1 }, { FCML_OP_MODRM_M_OP_W, FCML_OP_MODRM_R, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_MOVD[] = {
	/* 0F 6E /r MOVD mm,r/m32 A Valid Valid Move doubleword from r/m32 to mm.*/
    { FCML_AMT_MMX_SIMD, 0x0010, 0x03D88000, { 0x0F, 0x6E, 0x00 }, { FCML_OP_MODRM_R_MMX_W, FCML_OP_MODRM_RM_OP_32, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* 0F 7E /r MOVD r/m32, mm B Valid Valid Move doubleword from mm to r/m32.*/
    { FCML_AMT_MMX_SIMD, 0x0010, 0x03D88000, { 0x0F, 0x7E, 0x00 }, { FCML_OP_MODRM_RM_OP_32_W, FCML_OP_MODRM_R_MMX, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* 66 0F 7E /r MOVD r/m32, xmm B Valid Valid Move doubleword from xmm register to r/m32.*/
    { FCML_AMT_SSE2_SIMD, 0x1010, 0x03D88000, { 0x0F, 0x7E, 0x00 }, { FCML_OP_MODRM_RM_OP_32_W, FCML_OP_MODRM_R_XMM, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* 66 0F 6E /r MOVD xmm, r/m32 A Valid Valid Move doubleword from r/m32 to xmm.*/
    { FCML_AMT_SSE2_SIMD, 0x1010, 0x03D88000, { 0x0F, 0x6E, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_OP_32, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VMOVD[] = {
	/* VEX.128.66.0F.W0 6E /r VMOVD xmm1,r32/m32*/
    { FCML_AMT_AVX_SIMD, 0x10D0, 0x00D88000, { 0x0F, 0x6E, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_OP_32, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.128.66.0F.W0 7E /r VMOVD r32/m32,xmm1*/
    { FCML_AMT_AVX_SIMD, 0x10D0, 0x00D88000, { 0x0F, 0x7E, 0x00 }, { FCML_OP_MODRM_RM_OP_32_W, FCML_OP_MODRM_R_XMM, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_MOVQ[] = {
	/* REX.W + 0F 6E /r MOVQ mm, r/m64 A Valid N.E. Move quadword from r/m64 to mm.*/
    { FCML_AMT_MMX_SIMD, 0x0008, 0x04988000, { 0x0F, 0x6E, 0x00 }, { FCML_OP_MODRM_R_MMX_W, FCML_OP_MODRM_RM_OP_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* 66 REX.W 0F 6E /r MOVQ xmm, r/m64 A Valid N.E. Move quadword from r/m64 to xmm.*/
    { FCML_AMT_SSE2_SIMD, 0x1008, 0x04988000, { 0x0F, 0x6E, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_OP_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* REX.W + 0F 7E /r MOVQ r/m64, mm B Valid N.E. Move quadword from mm to r/m64.*/
    { FCML_AMT_MMX_SIMD, 0x0008, 0x04988000, { 0x0F, 0x7E, 0x00 }, { FCML_OP_MODRM_RM_OP_64_W, FCML_OP_MODRM_R_MMX, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* 66 REX.W 0F 7E /r MOVQ r/m64, xmm B Valid N.E. Move quadword from xmm register to r/m64.*/
    { FCML_AMT_SSE2_SIMD, 0x1008, 0x04988000, { 0x0F, 0x7E, 0x00 }, { FCML_OP_MODRM_RM_OP_64_W, FCML_OP_MODRM_R_XMM, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* F3 0F 7E MOVQ xmm1, xmm2/m64 A Valid Valid Move quadword from xmm2/mem64 to xmm1.*/
    { FCML_AMT_SSE2_SIMD, 0x4000, 0x00D88000, { 0x0F, 0x7E, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_OP_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* 0F 6F /r MOVQ mm, mm/m64 A Valid Valid Move quadword from mm/m64 to mm.*/
    { FCML_AMT_MMX_SIMD, 0x0000, 0x00D88000, { 0x0F, 0x6F, 0x00 }, { FCML_OP_MODRM_R_MMX_W, FCML_OP_MODRM_RM_MMX_OP, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* 0F 7F /r MOVQ mm/m64, mm B Valid Valid Move quadword from mm to mm/m64.*/
    { FCML_AMT_MMX_SIMD, 0x0000, 0x00D88000, { 0x0F, 0x7F, 0x00 }, { FCML_OP_MODRM_RM_MMX_OP_W, FCML_OP_MODRM_R_MMX, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* 66 0F D6 MOVQ xmm2/m64, xmm1 B Valid Valid Move quadword from xmm1 to xmm2/mem64.*/
    { FCML_AMT_SSE2_SIMD, 0x1000, 0x00D88000, { 0x0F, 0xD6, 0x00 }, { FCML_OP_MODRM_RM_XMM_OP_64_W, FCML_OP_MODRM_R_XMM, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VMOVQ[] = {
	/* VEX.128.66.0F.W1 6E /r VMOVQ xmm1,r64/m64*/
    { FCML_AMT_AVX_SIMD, 0x10C8, 0x04988000, { 0x0F, 0x6E, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_OP_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.128.66.0F.W1 7E /r VMOVQ r64/m64,xmm1*/
    { FCML_AMT_AVX_SIMD, 0x10C8, 0x04988000, { 0x0F, 0x7E, 0x00 }, { FCML_OP_MODRM_RM_OP_64_W, FCML_OP_MODRM_R_XMM, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.128.F3.0F 7E /r VMOVQ xmm1,xmm2,m64*/
    { FCML_AMT_AVX_SIMD, 0x40C0, 0x00D88000, { 0x0F, 0x7E, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_OP_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.128.66.0F D6 /r VMOVQ xmm1/m64,xmm2*/
    { FCML_AMT_AVX_SIMD, 0x10C0, 0x00D88000, { 0x0F, 0xD6, 0x00 }, { FCML_OP_MODRM_RM_XMM_OP_64_W, FCML_OP_MODRM_R_XMM, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_MOVDDUP[] = {
	/*F2 0F 12 /r MOVDDUP xmm1, xmm2/m64 A Valid Valid Move one double-precision floating-point value from the lower 64-bit operand in xmm2/m64 to xmm1 and duplicate.*/
    { FCML_AMT_SSE3_SIMD, 0x2000, 0x00D88000, { 0x0F, 0x12, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_OP_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VMOVDDUP[] = {
	/* VEX.128.F2.0F 12 /r VMOVDDUP xmm1,xmm2/m64*/
    { FCML_AMT_AVX_SIMD, 0x20C0, 0x00D88000, { 0x0F, 0x12, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_OP_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.256.F2.0F 12 /r VMOVDDUP ymm1,ymm2/m256*/
    { FCML_AMT_AVX_SIMD, 0x20A0, 0x00D88000, { 0x0F, 0x12, 0x00 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_MODRM_RM_YMM_OP_256, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_MOVDQA[] = {
	/* 66 0F 6F /r MOVDQA xmm1, xmm2/m128 A Valid Valid Move aligned double quadword from xmm2/m128 to xmm1.*/
    { FCML_AMT_SSE2_SIMD, 0x1000, 0x00D88000, { 0x0F, 0x6F, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* 66 0F 7F /r MOVDQA xmm2/m128, xmm1 B Valid Valid Move aligned double quadword from xmm1 to xmm2/m128.*/
    { FCML_AMT_SSE2_SIMD, 0x1000, 0x00D88000, { 0x0F, 0x7F, 0x00 }, { FCML_OP_MODRM_RM_XMM_OP_128_W, FCML_OP_MODRM_R_XMM, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VMOVDQA[] = {
	/* VEX.128.66.0F 6F /r VMOVDQA xmm1,xmm2/m128*/
	/* VEX.256.66.0F 6F /r VMOVDQA ymm1,ymm2/m256*/
    { FCML_AMT_AVX_SIMD, 0x1080, 0x00D88000, { 0x0F, 0x6F, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.128.66.0F 7F /r VMOVDQA xmm2/m128,xmm1*/
	/* VEX.256.66.0F 7F /r VMOVDQA ymm2/m256,ymm1*/
    { FCML_AMT_AVX_SIMD, 0x1080, 0x00D88000, { 0x0F, 0x7F, 0x00 }, { FCML_OP_MODRM_RM_SIMD_L_OP_W, FCML_OP_MODRM_R_SIMD_L, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_MOVDQU[] = {
	/* F3 0F 6F /r MOVDQU xmm1, xmm2/m128 A Valid Valid Move unaligned double quadword from xmm2/m128 to xmm1.*/
    { FCML_AMT_SSE2_SIMD, 0x4000, 0x00D88000, { 0x0F, 0x6F, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* F3 0F 7F /r MOVDQU xmm2/m128, xmm1 B Valid Valid Move unaligned double quadword from xmm1 to xmm2/m128.*/
    { FCML_AMT_SSE2_SIMD, 0x4000, 0x00D88000, { 0x0F, 0x7F, 0x00 }, { FCML_OP_MODRM_RM_XMM_OP_128_W, FCML_OP_MODRM_R_XMM, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VMOVDQU[] = {
	/* VEX.128.F3.0F 6F /r VMOVDQU xmm1,xmm2/m128*/
	/* VEX.256.F3.0F 6F /r VMOVDQU ymm1,ymm2/m256*/
    { FCML_AMT_AVX_SIMD, 0x4080, 0x00D88000, { 0x0F, 0x6F, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.128.F3.0F 7F /r VMOVDQU xmm2/m128,xmm1*/
	/* VEX.256.F3.0F 7F /r VMOVDQU ymm2/m256,ymm1*/
    { FCML_AMT_AVX_SIMD, 0x4080, 0x00D88000, { 0x0F, 0x7F, 0x00 }, { FCML_OP_MODRM_RM_SIMD_L_OP_W, FCML_OP_MODRM_R_SIMD_L, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_MOVDQ2Q[] = {
	/* F2 0F D6 MOVDQ2Q mm, xmm A Valid Valid Move low quadword from xmm to mmx register.*/
    { FCML_AMT_SSE2_SIMD, 0x2000, 0x00DA8000, { 0x0F, 0xD6, 0x00 }, { FCML_OP_MODRM_R_MMX_W, FCML_OP_RM( FCML_REG_SIMD, FCML_EOS_XWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_MOVHLPS[] = {
	/* 0F 12 /r MOVHLPS xmm1, xmm2 A Valid Valid Move two packed singleprecision floating-point values from high quadword of xmm2 to low quadword of xmm1.*/
    { FCML_AMT_SSE_SIMD, 0x0000, 0x00DA8000, { 0x0F, 0x12, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_RM( FCML_REG_SIMD, FCML_EOS_XWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VMOVHLPS[] = {
	/* VEX.NDS.128.0F 12 /r VMOVHLPS xmm1, xmm2, xmm3*/
    { FCML_AMT_AVX_SIMD, 0x00C0, 0x00DA8000, { 0x0F, 0x12, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_XWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_MOVHPD[] = {
	/* 66 0F 16 /r MOVHPD xmm, m64 A Valid Valid Move double-precision floating-point value from m64 to high quadword of xmm.*/
    { FCML_AMT_SSE2_SIMD, 0x1000, 0x00D88000, { 0x0F, 0x16, 0x00 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_RM( FCML_REG_UNDEFINED, FCML_EOS_UNDEFINED, FCML_EOS_QWORD | FCML_EOS_OPT, FCML_RMF_M ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* 66 0F 17 /r MOVHPD m64, xmm B Valid Valid Move double-precision floating-point value from high quadword of xmm to m64.*/
    { FCML_AMT_SSE2_SIMD, 0x1000, 0x00D88000, { 0x0F, 0x17, 0x00 }, { FCML_OP_RM( FCML_REG_UNDEFINED, FCML_EOS_UNDEFINED, FCML_EOS_QWORD | FCML_EOS_OPT, FCML_RMF_M ) | FCML_OA_W, FCML_OP_MODRM_R_XMM, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VMOVHPD[] = {
	/* VEX.NDS.128.66.0F 16 /r VMOVHPD xmm2,xmm1,m64*/
    { FCML_AMT_AVX_SIMD, 0x10C0, 0x00D88000, { 0x0F, 0x16, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_OP_64, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX128.66.0F 17/r VMOVHPD m64, xmm1*/
    { FCML_AMT_AVX_SIMD, 0x10C0, 0x00D88000, { 0x0F, 0x17, 0x00 }, { FCML_OP_MODRM_RM_OP_64_W, FCML_OP_MODRM_R_XMM_W, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_MOVHPS[] = {
	/* 0F 16 /r MOVHPS xmm, m64 A Valid Valid Move two packed singleprecision floating-point values from m64 to high quadword of xmm.*/
    { FCML_AMT_SSE_SIMD, 0x0000, 0x00D88000, { 0x0F, 0x16, 0x00 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_RM( FCML_REG_UNDEFINED, FCML_EOS_UNDEFINED, FCML_EOS_MWORD | FCML_EOS_OPT, FCML_RMF_M ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* 0F 17 /r MOVHPS m64, xmm B Valid Valid Move two packed singleprecision floating-point values from high quadword of xmm to m64.*/
    { FCML_AMT_SSE_SIMD, 0x0000, 0x00D88000, { 0x0F, 0x17, 0x00 }, { FCML_OP_RM( FCML_REG_UNDEFINED, FCML_EOS_UNDEFINED, FCML_EOS_MWORD | FCML_EOS_OPT, FCML_RMF_M ) | FCML_OA_W, FCML_OP_MODRM_R_XMM, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VMOVHPS[] = {
	/* VEX.NDS.128.0F 16 /r VMOVHPS xmm2,xmm1,m64*/
    { FCML_AMT_AVX_SIMD, 0x00C0, 0x00D88000, { 0x0F, 0x16, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_M_OP_64, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.128.0F 17 /r VMOVHPS m64,xmm1*/
    { FCML_AMT_AVX_SIMD, 0x00C0, 0x00D88000, { 0x0F, 0x17, 0x00 }, { FCML_OP_MODRM_RM_OP_64_W, FCML_OP_MODRM_R_XMM, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_MOVLHPS[] = {
	/* 0F 16 /r MOVLHPS xmm1, xmm2 A Valid Valid Move two packed singleprecision floating-point values from low quadword of xmm2 to high quadword of xmm1.*/
    { FCML_AMT_SSE_SIMD, 0x0000, 0x00D88000, { 0x0F, 0x16, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_RM( FCML_REG_SIMD, FCML_EOS_XWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VMOVLHPS[] = {
	/* VEX.NDS.128.0F 16 /r VMOVLHPS xmm1,xmm2,xmm3*/
    { FCML_AMT_AVX_SIMD, 0x00C0, 0x00D88000, { 0x0F, 0x16, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_RM( FCML_REG_SIMD, FCML_EOS_XWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_MOVLPD[] = {
	/* 66 0F 12 /r MOVLPD xmm, m64 A Valid Valid Move double-precision floating-point value from m64 to low quadword of xmm register.*/
    { FCML_AMT_SSE2_SIMD, 0x1000, 0x00D88000, { 0x0F, 0x12, 0x00 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_RM( FCML_REG_UNDEFINED, FCML_EOS_UNDEFINED, FCML_EOS_QWORD | FCML_EOS_OPT, FCML_RMF_M ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* 66 0F 13 /r MOVLPD m64, xmm B Valid Valid Move double-precision floating-point nvalue from low quadword of xmm register to m64.*/
    { FCML_AMT_SSE2_SIMD, 0x1000, 0x00D88000, { 0x0F, 0x13, 0x00 }, { FCML_OP_RM( FCML_REG_UNDEFINED, FCML_EOS_UNDEFINED, FCML_EOS_QWORD | FCML_EOS_OPT, FCML_RMF_M ) | FCML_OA_W, FCML_OP_MODRM_R_XMM, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VMOVLPD[] = {
	/* VEX.NDS.128.66.0F 12 /r VMOVLPD xmm2,xmm1,m64*/
    { FCML_AMT_AVX_SIMD, 0x10C0, 0x00D88000, { 0x0F, 0x12, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_OP_64, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.128.66.0F 13 /r VMOVLPD m64,xmm1*/
    { FCML_AMT_AVX_SIMD, 0x10C0, 0x00D88000, { 0x0F, 0x13, 0x00 }, { FCML_OP_MODRM_RM_OP_64_W, FCML_OP_MODRM_R_XMM_W, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_MOVLPS[] = {
	/* 0F 12 /r MOVLPS xmm, m64 A Valid Valid Move two packed singleprecision floating-point values from m64 to low quadword of xmm.*/
    { FCML_AMT_SSE_SIMD, 0x0000, 0x00D88000, { 0x0F, 0x12, 0x00 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_RM( FCML_REG_UNDEFINED, FCML_EOS_UNDEFINED, FCML_EOS_QWORD | FCML_EOS_OPT, FCML_RMF_M ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* 0F 13 /r MOVLPS m64, xmm B Valid Valid Move two packed singleprecision floating-point values from low quadword of xmm to m64.*/
    { FCML_AMT_SSE_SIMD, 0x0000, 0x00D88000, { 0x0F, 0x13, 0x00 }, { FCML_OP_RM( FCML_REG_UNDEFINED, FCML_EOS_UNDEFINED, FCML_EOS_QWORD | FCML_EOS_OPT, FCML_RMF_M ) | FCML_OA_W, FCML_OP_MODRM_R_XMM, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VMOVLPS[] = {
	/* VEX.NDS.128.0F 12 /r VMOVLPS xmm2,xmm1,m64*/
    { FCML_AMT_AVX_SIMD, 0x00C0, 0x00D88000, { 0x0F, 0x12, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_M_OP_64, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.128.0F 13 /r VMOVLPS m64, xmm1*/
    { FCML_AMT_AVX_SIMD, 0x00C0, 0x00D88000, { 0x0F, 0x13, 0x00 }, { FCML_OP_MODRM_M_OP_64_W, FCML_OP_MODRM_R_XMM, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_MOVMSKPD[] = {
	/* 66 0F 50 /r MOVMSKPD reg, xmm A Valid Valid Extract 2-bit sign mask from xmm and store in reg. The upper bits of r32 or r64 are filled with zeros.*/
    { FCML_AMT_SSE2_SIMD, 0x1000, 0x005A8000, { 0x0F, 0x50, 0x00 }, { FCML_OP_MODRM_R_32_W, FCML_OP_RM( FCML_REG_SIMD, FCML_EOS_XWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
    { FCML_AMT_SSE2_SIMD, 0x1000, 0x009A8000, { 0x0F, 0x50, 0x00 }, { FCML_OP_MODRM_R_64_W, FCML_OP_RM( FCML_REG_SIMD, FCML_EOS_XWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VMOVMSKPD[] = {
	/* VEX.128.66.0F 50 /r VMOVMSKPD reg,xmm2*/
	/* VEX.256.66.0F 50 /r VMOVMSKPD reg,ymm2*/
    { FCML_AMT_AVX_SIMD, 0x1080, 0x00588000, { 0x0F, 0x50, 0x00 }, { FCML_OP_MODRM_R_32_W, FCML_OP_RM( FCML_REG_SIMD, FCML_EOS_L, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
    { FCML_AMT_AVX_SIMD, 0x1080, 0x00988000, { 0x0F, 0x50, 0x00 }, { FCML_OP_MODRM_R_64_W, FCML_OP_RM( FCML_REG_SIMD, FCML_EOS_L, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_MOVMSKPS[] = {
	/* 0F 50 /r MOVMSKPS reg, xmm A Valid Valid Extract 4-bit sign mask from xmm and store in reg. The upper bits of r32 or r64 are filled with zeros.*/
    { FCML_AMT_SSE_SIMD, 0x0000, 0x00588000, { 0x0F, 0x50, 0x00 }, { FCML_OP_MODRM_R_32_W, FCML_OP_RM( FCML_REG_SIMD, FCML_EOS_XWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
    { FCML_AMT_SSE_SIMD, 0x0000, 0x00988000, { 0x0F, 0x50, 0x00 }, { FCML_OP_MODRM_R_64_W, FCML_OP_RM( FCML_REG_SIMD, FCML_EOS_XWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VMOVMSKPS[] = {
	/* VEX.128.0F 50 /r VMOVMSKPS reg,xmm2*/
	/* VEX.256.0F 50 /r VMOVMSKPS reg,ymm2*/
    { FCML_AMT_AVX_SIMD, 0x0080, 0x00588000, { 0x0F, 0x50, 0x00 }, { FCML_OP_MODRM_R_32_W, FCML_OP_RM( FCML_REG_SIMD, FCML_EOS_L, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
    { FCML_AMT_AVX_SIMD, 0x0080, 0x00988000, { 0x0F, 0x50, 0x00 }, { FCML_OP_MODRM_R_64_W, FCML_OP_RM( FCML_REG_SIMD, FCML_EOS_L, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_MOVNTDQA[] = {
	/* 66 0F 38 2A /r MOVNTDQA xmm1, m128 A Valid Valid Move double quadword from m128 to xmm using non-temporal hint if WC memory type.*/
    { FCML_AMT_SSE41_SIMD, 0x1000, 0x00EC8000, { 0x0F, 0x38, 0x2A }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_RM( FCML_REG_SIMD, FCML_EOS_UNDEFINED, FCML_EOS_XWORD | FCML_EOS_OPT, FCML_RMF_M ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VMOVNTDQA[] = {
	/* VEX.128.66.0F38 2A /r VMOVNTDQA xmm1,m128*/
    { FCML_AMT_AVX_SIMD, 0x10C0, 0x00EC8000, { 0x0F, 0x38, 0x2A }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_M_OP_XMM, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.256.66.0F38.WIG 2A /r VMOVNTDQA ymm1,m256*/
    { FCML_AMT_AVX2_SIMD, 0x10A0, 0x00EC8000, { 0x0F, 0x38, 0x2A }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_MODRM_M_OP_YMM, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_MOVNTDQ[] = {
	/* 66 0F E7 /r MOVNTDQ m128, xmm A Valid Valid Move double quadword from xmm to m128 using non-temporal hint.*/
    { FCML_AMT_SSE2, 0x1000, 0x00D88000, { 0x0F, 0xE7, 0x00 }, { FCML_OP_RM( FCML_REG_SIMD, FCML_EOS_UNDEFINED, FCML_EOS_XWORD | FCML_EOS_OPT, FCML_RMF_M ) | FCML_OA_W, FCML_OP_MODRM_R_XMM , FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VMOVNTDQ[] = {
	/* VEX.128.66.0F E7 /r VMOVNTDQ m128,xmm1*/
    { FCML_AMT_AVX_SIMD, 0x10C0, 0x00D88000, { 0x0F, 0xE7, 0x00 }, { FCML_OP_MODRM_M_OP_XMM_W, FCML_OP_MODRM_R_XMM, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_MOVNTI[] = {
	/* 0F C3 /r MOVNTI m32, r32 A Valid Valid Move doubleword from r32 to m32 using non-temporal hint.*/
    { FCML_AMT_SSE2, 0x0010, 0x03D88000, { 0x0F, 0xC3, 0x00 }, { FCML_OP_RM( FCML_REG_UNDEFINED, FCML_EOS_UNDEFINED, FCML_EOS_DWORD | FCML_EOS_OPT, FCML_RMF_M ) | FCML_OA_W, FCML_OP_MODRM_R_32 , FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* REX.W + 0F C3 /r MOVNTI m64, r64 A Valid N.E. Move quadword from r64 to m64 using non-temporal hint.*/
    { FCML_AMT_SSE2, 0x0008, 0x04988000, { 0x0F, 0xC3, 0x00 }, { FCML_OP_RM( FCML_REG_UNDEFINED, FCML_EOS_UNDEFINED, FCML_EOS_QWORD | FCML_EOS_OPT, FCML_RMF_M ) | FCML_OA_W, FCML_OP_MODRM_R_64 , FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_MOVNTPD[] = {
	/* 66 0F 2B /r MOVNTPD m128, xmm A Valid Valid Move packed doubleprecision floating-point values from xmm to m128 using non-temporal hint.*/
    { FCML_AMT_SSE2, 0x1000, 0x00D88000, { 0x0F, 0x2B, 0x00 }, { FCML_OP_RM( FCML_REG_SIMD, FCML_EOS_UNDEFINED, FCML_EOS_XWORD | FCML_EOS_OPT, FCML_RMF_M ) | FCML_OA_W, FCML_OP_MODRM_R_XMM , FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VMOVNTPD[] = {
	/* VEX.128.66.0F 2B /r VMOVNTPD m128,xmm1*/
    { FCML_AMT_AVX_SIMD, 0x10C0, 0x00D88000, { 0x0F, 0x2B, 0x00 }, { FCML_OP_MODRM_M_OP_XMM_W, FCML_OP_MODRM_R_XMM, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_MOVNTPS[] = {
	/* 0F 2B /r MOVNTPS m128, xmm A Valid Valid Move packed singleprecision floating-point values from xmm to m128 using non-temporal hint.*/
    { FCML_AMT_SSE_SIMD, 0x0000, 0x00D88000, { 0x0F, 0x2B, 0x00 }, { FCML_OP_RM( FCML_REG_SIMD, FCML_EOS_UNDEFINED, FCML_EOS_XWORD | FCML_EOS_OPT, FCML_RMF_M ) | FCML_OA_W, FCML_OP_MODRM_R_XMM , FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VMOVNTPS[] = {
	/* VEX.128.0F 2B /r VMOVNTPS m128, xmm1*/
    { FCML_AMT_AVX_SIMD, 0x00C0, 0x00D88000, { 0x0F, 0x2B, 0x00 }, { FCML_OP_MODRM_M_OP_XMM_W, FCML_OP_MODRM_R_XMM, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_MOVNTSD[] = {
	/* MOVNTSD mem64, xmm F2 0F 2B /r*/
    { FCML_AMT_SSE4A, 0x2000, 0x00D88000, { 0x0F, 0x2B, 0x00 }, { FCML_OP_RM( FCML_REG_UNDEFINED, FCML_EOS_UNDEFINED, FCML_EOS_QWORD | FCML_EOS_OPT, FCML_RMF_M ) | FCML_OA_W, FCML_OP_MODRM_R_XMM , FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_MOVNTSS[] = {
	/* MOVNTSS mem32, xmm F3 0F 2B /r*/
    { FCML_AMT_SSE4A, 0x4000, 0x00D88000, { 0x0F, 0x2B, 0x00 }, { FCML_OP_RM( FCML_REG_UNDEFINED, FCML_EOS_UNDEFINED, FCML_EOS_DWORD | FCML_EOS_OPT, FCML_RMF_M ) | FCML_OA_W, FCML_OP_MODRM_R_XMM , FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_MOVNTQ[] = {
	/* 0F E7 /r MOVNTQ m64, mm A Valid Valid Move quadword from mm to m64 using non-temporal hint.*/
    { FCML_AMT_SSE_SIMD, 0x0000, 0x00D88000, { 0x0F, 0xE7, 0x00 }, { FCML_OP_RM( FCML_REG_UNDEFINED, FCML_EOS_UNDEFINED, FCML_EOS_MWORD | FCML_EOS_OPT, FCML_RMF_M ) | FCML_OA_W, FCML_OP_MODRM_R_MMX , FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_MOVQ2DQ[] = {
	/* F3 0F D6 MOVQ2DQ xmm, mm A Valid Valid Move quadword from mmx to low quadword of xmm.*/
    { FCML_AMT_SSE2_SIMD, 0x4000, 0x00D88000, { 0x0F, 0xD6, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_RM( FCML_REG_SIMD, FCML_EOS_MWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_MOVS[] = {
	/* A4 MOVS m8, m8 A Valid Valid For legacy mode, Move byte from address DS:(E)SI to ES:(E)DI. For 64-bit mode move byte from address (R|E)SI to (R|E)DI.*/
	/* A4 MOVSB A Valid Valid For legacy mode, Move byte from address DS:(E)SI to ES:(E)DI. For 64-bit mode move byte from address (R|E)SI to (R|E)DI.*/
    { FCML_AMT_GPI, 0x0004, 0x00C40000, { 0xA4, 0x00, 0x00 }, { FCML_OP_EXPLICIT_GPS_REG_ADDRESSING( FCML_REG_DI, FCML_EOS_BYTE, FCML_SEG_ENCODE_REGISTER( FCML_REG_DS, FCML_SEG_ALLOW_OVERRIDE ) ), FCML_OP_EXPLICIT_GPS_REG_ADDRESSING( FCML_REG_SI, FCML_EOS_BYTE, FCML_SEG_ENCODE_REGISTER( FCML_REG_ES, FCML_SEG_DENY_OVERRIDE ) ) | FCML_OA_W, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_M8_M8 },
	/* A5 MOVS m16, m16 A Valid Valid For legacy mode, move word from address DS:(E)SI to ES:(E)DI. For 64-bit mode move word at address (R|E)SI to (R|E)DI.*/
	/* A5 MOVS m32, m32 A Valid Valid For legacy mode, move dword from address DS:(E)SI to ES:(E)DI. For 64-bit mode move dword from address (R|E)SI to (R|E)DI.*/
	/* REX.W + A5 MOVS m64, m64 A Valid N.E. Move qword from address (R|E)SI to (R|E)DI.*/
	/* A5 MOVSW A Valid Valid For legacy mode, move word from address DS:(E)SI to ES:(E)DI. For 64-bit mode move word at address (R|E)SI to (R|E)DI.*/
	/* A5 MOVSD A Valid Valid For legacy mode, move dword from address DS:(E)SI to ES:(E)DI. For 64-bit mode move dword from address (R|E)SI to (R|E)DI. REX.W + A5 MOVSQ A Valid N.E. Move qword from address*/
    { FCML_AMT_GPI, 0x0004, 0x00C40000, { 0xA5, 0x00, 0x00 }, { FCML_OP_EXPLICIT_GPS_REG_ADDRESSING( FCML_REG_DI, FCML_EOS_EOSA,FCML_SEG_ENCODE_REGISTER( FCML_REG_DS, FCML_SEG_ALLOW_OVERRIDE ) ), FCML_OP_EXPLICIT_GPS_REG_ADDRESSING( FCML_REG_SI, FCML_EOS_EOSA,FCML_SEG_ENCODE_REGISTER( FCML_REG_ES, FCML_SEG_DENY_OVERRIDE ) ) | FCML_OA_W, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_MO_MO }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_MOVSD[] = {
	/* F2 0F 10 /r MOVSD xmm1, xmm2/m64 A Valid Valid Move scalar doubleprecision floating-point value from xmm2/m64 to xmm1 register.*/
    { FCML_AMT_SSE2_SIMD, 0x2000, 0x00D88000, { 0x0F, 0x10, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_OP_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* F2 0F 11 /r MOVSD xmm2/m64, xmm1 B Valid Valid Move scalar doubleprecision floating-point value from xmm1 register to xmm2/m64.*/
    { FCML_AMT_SSE2_SIMD, 0x2000, 0x00D88000, { 0x0F, 0x11, 0x00 }, { FCML_OP_MODRM_RM_XMM_OP_64_W, FCML_OP_MODRM_R_XMM, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VMOVSD[] = {
	/* VEX.NDS.128.F2.0F 10 /r VMOVSD xmm1,xmm2,xmm3*/
    { FCML_AMT_AVX_SIMD, 0x20C0, 0x00D88000, { 0x0F, 0x10, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_RM( FCML_REG_SIMD, FCML_EOS_XWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.NDS.128.F2.0F 11 /r VMOVSD xmm1,xmm2,xmm3*/
    { FCML_AMT_AVX_SIMD, 0x20C0, 0x00D88000, { 0x0F, 0x11, 0x00 }, { FCML_OP_RM( FCML_REG_SIMD, FCML_EOS_XWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ) | FCML_OA_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_R_XMM, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.128.F2.0F 10 /r VMOVSD xmm1,m64*/
    { FCML_AMT_AVX_SIMD, 0x20C0, 0x00D88000, { 0x0F, 0x10, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_M_OP_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.128.F2.0F 11 /r VMOVSD m64,xmm1*/
    { FCML_AMT_AVX_SIMD, 0x20C0, 0x00D88000, { 0x0F, 0x11, 0x00 }, { FCML_OP_MODRM_M_OP_64_W, FCML_OP_MODRM_R_XMM, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_MOVSHDUP[] = {
	/* F3 0F 16 /r MOVSHDUP xmm1, xmm2/m128 A Valid Valid Move two single-precisionfloating-point values from the higher 32-bit operand of each qword in xmm2/m128 to xmm1 and duplicate each 32-bit operand to the lower 32-bits of each qword.*/
    { FCML_AMT_SSE3_SIMD, 0x4000, 0x00D88000, { 0x0F, 0x16, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VMOVSHDUP[] = {
	/* VEX.128.F3.0F 16 /r VMOVSHDUP xmm1,xmm2/m128*/
	/* VEX.256.F3.0F 16 /r VMOVSHDUP ymm1,ymm2/m256*/
    { FCML_AMT_AVX_SIMD, 0x4080, 0x00D88000, { 0x0F, 0x16, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_MOVSLDUP[] = {
	/* F3 0F 12 /r MOVSLDUP xmm1, xmm2/m128 A Valid Valid Move two single-precision floating-point values from the lower 32-bit operand ofeach qword in xmm2/m128 to xmm1 and duplicate each 32-bit operand to the higher 32-bits of each qword.*/
    { FCML_AMT_SSE3_SIMD, 0x4000, 0x00D88000, { 0x0F, 0x12, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VMOVSLDUP[] = {
	/* VEX.128.F3.0F 12 /r VMOVSLDUP xmm1,xmm2/m128*/
	/* VEX.256.F3.0F 12 /r VMOVSLDUP ymm1,ymm2/m256*/
    { FCML_AMT_AVX_SIMD, 0x4080, 0x00D88000, { 0x0F, 0x12, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_MOVSS[] = {
	/* F3 0F 10 /r MOVSS xmm1, xmm2/m32 A Valid Valid Move scalar single-precision floating-point value from xmm2/m32 to xmm1 register.*/
    { FCML_AMT_SSE_SIMD, 0x4000, 0x00D88000, { 0x0F, 0x10, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_OP_32, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* F3 0F 11 /r MOVSS xmm2/m32, xmm B Valid Valid Move scalar single-precision floating-point value from xmm1 register to*/
    { FCML_AMT_SSE_SIMD, 0x4000, 0x00D88000, { 0x0F, 0x11, 0x00 }, { FCML_OP_MODRM_RM_XMM_OP_32_W, FCML_OP_MODRM_R_XMM, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VMOVSS[] = {
	/* VEX.NDS.128.F3.0F 10 /r VMOVSS xmm1,xmm2,xmm3*/
    { FCML_AMT_AVX_SIMD, 0x40C0, 0x00DA8000, { 0x0F, 0x10, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_RM( FCML_REG_SIMD, FCML_EOS_OWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.NDS.128.F3.0F 11 /r VMOVSS xmm1,xmm2,xmm3*/
    { FCML_AMT_AVX_SIMD, 0x40C0, 0x00DA8000, { 0x0F, 0x11, 0x00 }, { FCML_OP_RM( FCML_REG_SIMD, FCML_EOS_OWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ) | FCML_OA_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_R_XMM, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.128.F3.0F 10 /r VMOVSS xmm1,m32*/
    { FCML_AMT_AVX_SIMD, 0x40C0, 0x00D88000, { 0x0F, 0x10, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_M_OP_32, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.128.F3.0F 11 /r VMOVSS m32,xmm1*/
    { FCML_AMT_AVX_SIMD, 0x40C0, 0x00D88000, { 0x0F, 0x11, 0x00 }, { FCML_OP_MODRM_M_OP_32_W, FCML_OP_MODRM_R_XMM, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_MOVSX[] = {
	/* 0F BE /r MOVSX r16, r/m8 A Valid Valid Move byte to word with sign-extension.*/
	/* 0F BE /r MOVSX r32, r/m8 A Valid Valid Move byte to doubleword with sign-extension.*/
	/* REX + 0F BE /r MOVSX r64, r/m8* A Valid N.E. Move byte to quadword with sign-extension.*/
    { FCML_AMT_GPI, 0x0000, 0x00D88000, { 0x0F, 0xBE, 0x00 }, { FCML_OP_MODRM_R_W, FCML_OP_MODRM_RM_8, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RO_RM8 },
	/* 0F BF /r MOVSX r32, r/m16 A Valid Valid Move word to doubleword, with sign-extension.*/
    { FCML_AMT_GPI, 0x0000, 0x03D88000, { 0x0F, 0xBF, 0x00 }, { FCML_OP_MODRM_R_32_W, FCML_OP_MODRM_RM_16, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RO_RM16 },
	/* REX.W + 0F BF /r MOVSX r64, r/m16 A Valid N.E. Move word to quadword with sign-extension.*/
    { FCML_AMT_GPI, 0x0008, 0x04988000, { 0x0F, 0xBF, 0x00 }, { FCML_OP_MODRM_R_64_W, FCML_OP_MODRM_RM_16, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RO_RM16 }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_MOVSXD[] = {
	/* REX.W** + 63 /r MOVSXD r64, r/m32 A Valid N.E. Move doubleword to quadword with signextension.*/
    { FCML_AMT_GPI, 0x0008, 0x04848000, { 0x63, 0x00, 0x00 }, { FCML_OP_MODRM_R_64_W, FCML_OP_MODRM_RM_OP_32, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_MOVUPD[] = {
	/* 66 0F 10 /r MOVUPD xmm1, xmm2/m128 A Valid Valid Move packed doubleprecision floating-point values from xmm2/m128 to xmm1.*/
    { FCML_AMT_SSE2_SIMD, 0x1000, 0x00D88000, { 0x0F, 0x10, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* 66 0F 11 /r MOVUPD xmm2/m128, xmm B Valid Valid Move packed doubleprecision floating-point values from xmm1 to xmm2/m128.*/
    { FCML_AMT_SSE2_SIMD, 0x1000, 0x00D88000, { 0x0F, 0x11, 0x00 }, { FCML_OP_MODRM_RM_XMM_OP_128_W, FCML_OP_MODRM_R_XMM, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VMOVUPD[] = {
	/* VEX.128.66.0F 10 /r VMOVUPD xmm1,xmm2/m128*/
	/* VEX.256.66.0F 10 /r VMOVUPD ymm1,ymm2/m256*/
    { FCML_AMT_AVX_SIMD, 0x1080, 0x00D88000, { 0x0F, 0x10, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.128.66.0F 11 /r VMOVUPD xmm2/m128,xmm1*/
	/* VEX.256.66.0F 11 /r VMOVUPD ymm2/m256,ymm1*/
    { FCML_AMT_AVX_SIMD, 0x1080, 0x00D88000, { 0x0F, 0x11, 0x00 }, { FCML_OP_MODRM_RM_SIMD_L_OP_W, FCML_OP_MODRM_R_SIMD_L, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_MOVUPS[] = {
	/* 0F 10 /r MOVUPS xmm1, xmm2/m128 A Valid Valid Move packed singleprecision floating-point values from xmm2/m128 to xmm1.*/
    { FCML_AMT_SSE_SIMD, 0x0000, 0x00D88000, { 0x0F, 0x10, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* 0F 11 /r MOVUPS xmm2/m128, xmm1 B Valid Valid Move packed singleprecision floating-point values from xmm1 to xmm2/m128.*/
    { FCML_AMT_SSE_SIMD, 0x0000, 0x00D88000, { 0x0F, 0x11, 0x00 }, { FCML_OP_MODRM_RM_XMM_OP_128_W, FCML_OP_MODRM_R_XMM, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VMOVUPS[] = {
	/* VEX.128.0F 10 /r VMOVUPS xmm1,xmm2/m128*/
	/* VEX.256.0F 10 /r VMOVUPS ymm1,ymm2/m256*/
    { FCML_AMT_AVX_SIMD, 0x0080, 0x00D88000, { 0x0F, 0x10, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.128.0F 11 /r VMOVUPS xmm2/m128,xmm1*/
	/* VEX.256.0F 11 /r VMOVUPS ymm2/m256,ymm1*/
    { FCML_AMT_AVX_SIMD, 0x0080, 0x00D88000, { 0x0F, 0x11, 0x00 }, { FCML_OP_MODRM_RM_SIMD_L_OP_W, FCML_OP_MODRM_R_SIMD_L, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_MOVZX[] = {
	/* 0F B6 /r MOVZX r16, r/m8 A Valid Valid Move byte to word with zero-extension.*/
	/* 0F B6 /r MOVZX r32, r/m8 A Valid Valid Move byte to doubleword, zero-extension.*/
	/* REX.W + 0F B6 /r MOVZX r64, r/m8* A Valid N.E. Move byte to quadword, zero-extension.*/
    { FCML_AMT_GPI, 0x0000, 0x00D88000, { 0x0F, 0xB6, 0x00 }, { FCML_OP_MODRM_R_W, FCML_OP_MODRM_RM_8, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RO_RM8 },
	/* 0F B7 /r MOVZX r32, r/m16 A Valid Valid Move word to doubleword, zero-extension.*/
    { FCML_AMT_GPI, 0x0000, 0x03D88000, { 0x0F, 0xB7, 0x00 }, { FCML_OP_MODRM_R_32_W, FCML_OP_MODRM_RM_16, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RO_RM16 },
	/* REX.W + 0F B7 /r MOVZX r64, r/m16 A Valid N.E. Move word to quadword, zero-extension.*/
    { FCML_AMT_GPI, 0x0000, 0x04988000, { 0x0F, 0xB7, 0x00 }, { FCML_OP_MODRM_R_64_W, FCML_OP_MODRM_RM_16, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RO_RM16 }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_MPSADBW[] = {
	/* 66 0F 3A 42 /r ib MPSADBW xmm1, xmm2/m128, int8 A Valid Valid Sums absolute 8-bit integer difference of adjacent groups of 4 byte integers in xmm1 and xmm2/m128 and writes the results in xmm1. Starting offsets within xmm1 and xmm2/m128 are determined by int8.*/
    { FCML_AMT_SSE41_SIMD, 0x1000, 0x00EC8000, { 0x0F, 0x3A, 0x42 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_128, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VMPSADBW[] = {
	/* VEX.NDS.128.66.0F3A 42 /r ib VMPSADBW xmm1,xmm2,xmm3/m128,int8*/
    { FCML_AMT_AVX_SIMD, 0x10C0, 0x00EC8000, { 0x0F, 0x3A, 0x42 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_OP_IB, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.NDS.256.66.0F3A.WIG 42 /r ib VMPSADBW ymm1,ymm2,ymm3/m256,int8*/
    { FCML_AMT_AVX2_SIMD, 0x10A0, 0x00EC8000, { 0x0F, 0x3A, 0x42 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_YMM_REG, FCML_OP_MODRM_RM_YMM_OP_256, FCML_OP_IB, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_MUL[] = {
	/* F6 /4 MUL r/m8 A Valid Valid Unsigned multiply (AX AL r/m8).*/
	/* REX + F6 /4 MUL r/m8* A Valid N.E. Unsigned multiply (AX AL r/m8).*/
    { FCML_AMT_GPI, 0x0000, 0x00C5A000, { 0xF6, 0x00, 0x00 }, { FCML_OP_MODRM_RM_8, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RM8 },
	/* F7 /4 MUL r/m16 A Valid Valid Unsigned multiply (DX:AX AX r/m16).*/
	/* F7 /4 MUL r/m32 A Valid Valid Unsigned multiply (EDX:EAX EAX r/m32).*/
	/* REX.W + F7 /4 MUL r/m64 A Valid N.E. Unsigned multiply (RDX:RAX RAX r/m64.*/
    { FCML_AMT_GPI, 0x0000, 0x00C5A000, { 0xF7, 0x00, 0x00 }, { FCML_OP_MODRM_RM, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RMO }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_MULPD[] = {
	/* 66 0F 59 /r MULPD xmm1, xmm2/m128 A Valid Valid Multiply packed doubleprecision floating-point values in xmm2/m128 by xmm1.*/
    { FCML_AMT_SSE2_SIMD, 0x1000, 0x00D88000, { 0x0F, 0x59, 0x00 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VMULPD[] = {
	/* VEX.NDS.128.66.0F 59 /r VMULPD xmm1,xmm2,xmm3/m128*/
	/* VEX.NDS.256.66.0F 59 /r VMULPD ymm1,ymm2,ymm3/m256*/
    { FCML_AMT_AVX_SIMD, 0x1080, 0x00D88000, { 0x0F, 0x59, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_MULPS[] = {
	/* 0F 59 /r MULPS xmm1, xmm2/m128 A Valid Valid Multiply packed singleprecision floating-point values in xmm2/mem by xmm1.*/
    { FCML_AMT_SSE_SIMD, 0x0000, 0x00D88000, { 0x0F, 0x59, 0x00 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VMULPS[] = {
	/* VEX.NDS.128.0F 59 /r VMULPS xmm1,xmm2,xmm3/m128*/
	/* VEX.NDS.256.0F 59 /r VMULPS ymm1,ymm2,ymm3/m256*/
    { FCML_AMT_AVX_SIMD, 0x0080, 0x00D88000, { 0x0F, 0x59, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_MULSD[] = {
	/* F2 0F 59 /r MULSD xmm1, xmm2/m64 A Valid Valid Multiply the low doubleprecision floating-point value in xmm2/mem64 by low double-precision floating-point value in xmm1.*/
    { FCML_AMT_SSE2_SIMD, 0x2000, 0x00D88000, { 0x0F, 0x59, 0x00 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VMULSD[] = {
	/* VEX.NDS.128.F2.0F 59 /r VMULSD xmm1,xmm2,xmm3/m64*/
    { FCML_AMT_AVX_SIMD, 0x20C0, 0x00D88000, { 0x0F, 0x59, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_64, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_MULSS[] = {
	/* F3 0F 59 /r MULSS xmm1, xmm2/m32 A Valid Valid Multiply the low singleprecision floating-point value in xmm2/mem by the low single-precision floating-point value in xmm1.*/
    { FCML_AMT_SSE_SIMD, 0x4000, 0x00D88000, { 0x0F, 0x59, 0x00 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_32, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VMULSS[] = {
	/* VEX.NDS.128.F3.0F 59 /r VMULSS xmm1,xmm2,xmm3/m32*/
    { FCML_AMT_AVX_SIMD, 0x40C0, 0x00D88000, { 0x0F, 0x59, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_32, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_MWAIT[] = {
	/* 0F 01 C9 MWAIT A Valid Valid A hint that allow the processor to stop instruction execution and enter an implementationdependent optimized state until occurrence of a class of events.*/
    { FCML_AMT_SSE3, 0x0000, 0x00EC0000, { 0x0F, 0x01, 0xC9 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_NEG[] = {
	/* F6 /3 NEG r/m8 M Valid Valid Two's complement negate r/m8.*/
	/* REX + F6 /3 NEG r/m8* M Valid N.E. Two's complement negate r/m8.*/
    { FCML_AMT_GPI, 0x0807, 0x00C59800, { 0xF6, 0x00, 0x00 }, { FCML_OP_MODRM_RM_8_RW, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RM8 },
	/* F7 /3 NEG r/m16 M Valid Valid Two's complement negate r/m16.*/
	/* F7 /3 NEG r/m32 M Valid Valid Two's complement negate r/m32.*/
	/* REX.W + F7 /3 NEG r/m64 M Valid N.E. Two's complement negate r/m64.*/
    { FCML_AMT_GPI, 0x0807, 0x00C59800, { 0xF7, 0x00, 0x00 }, { FCML_OP_MODRM_RM_RW, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RMO }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_NOP[] = {
	/* 90 NOP NP Valid Valid One byte no-operation instruction.*/
    { FCML_AMT_GPI, 0x0000, 0x00C40000, { 0x90, 0x00, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* 0F 1F /0 NOP r/m16 M Valid Valid Multi-byte no-operation instruction.*/
	/* 0F 1F /0 NOP r/m32 M Valid Valid Multi-byte no-operation instruction.*/
    { FCML_AMT_GPI, 0x0000, 0x00D98000, { 0x0F, 0x1F, 0x00 }, { FCML_OP_MODRM_RM, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RMO }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_NOT[] = {
	/* F6 /2 NOT r/m8 M Valid Valid Reverse each bit of r/m8.*/
	/* REX + F6 /2 NOT r/m8* M Valid N.E. Reverse each bit of r/m8.*/
    { FCML_AMT_GPI, 0x0807, 0x00C59000, { 0xF6, 0x00, 0x00 }, { FCML_OP_MODRM_RM_8_RW, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RM8 },
	/* F7 /2 NOT r/m16 M Valid Valid Reverse each bit of r/m16.*/
	/* F7 /2 NOT r/m32 M Valid Valid Reverse each bit of r/m32.*/
	/* REX.W + F7 /2 NOT r/m64 M Valid N.E. Reverse each bit of r/m64.*/
    { FCML_AMT_GPI, 0x0807, 0x00C59000, { 0xF7, 0x00, 0x00 }, { FCML_OP_MODRM_RM_RW, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RMO }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_OR[] = {
	/* 0C ib OR AL, int8 I Valid Valid AL OR int8.*/
    { FCML_AMT_GPI, 0x0000, 0x00C40000, { 0x0C, 0x00, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_AL, FCML_EOS_BYTE ) | FCML_OA_RW, FCML_OP_IB, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_ER8_IMM8 },
	/* 0D iw OR AX, int16 I Valid Valid AX OR int16.*/
	/* 0D id OR EAX, int32 I Valid Valid EAX OR int32.*/
	/* REX.W + 0D id OR RAX, int32 I Valid N.E. RAX OR int32 (sign-extended).*/
    { FCML_AMT_GPI, 0x0000, 0x00C40000, { 0x0D, 0x00, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_AL, FCML_EOS_EOSA ) | FCML_OA_RW, FCML_OP_EX_EOSA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_ERO_IMMO },
	/* 80 /1 ib OR r/m8, int8 MI Valid Valid r/m8 OR int8.*/
	/* REX + 80 /1 ib OR r/m8*, int8 MI Valid N.E. r/m8 OR int8.*/
    { FCML_AMT_GPI, 0x0807, 0x00C58804, { 0x80, 0x00, 0x00 }, { FCML_OP_MODRM_RM_8_RW, FCML_OP_IB, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RM8_IMM8 },
	/* 81 /1 iw OR r/m16, int16 MI Valid Valid r/m16 OR int16.*/
	/* 81 /1 id OR r/m32, int32 MI Valid Valid r/m32 OR int32.*/
	/* REX.W + 81 /1 id OR r/m64, int32 MI Valid N.E. r/m64 OR int32 (sign-extended).*/
    { FCML_AMT_GPI, 0x0807, 0x00C58804, { 0x81, 0x00, 0x00 }, { FCML_OP_MODRM_RM_RW, FCML_OP_EX_EOSA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RMO_IMMO },
	/* 83 /1 ib OR r/m16, int8 MI Valid Valid r/m16 OR int8 (sign-extended).*/
	/* 83 /1 ib OR r/m32, int8 MI Valid Valid r/m32 OR int8 (sign-extended).*/
	/* REX.W + 83 /1 ib OR r/m64, int8 MI Valid N.E. r/m64 OR int8 (sign-extended).*/
    { FCML_AMT_GPI, 0x0807, 0x00C58804, { 0x83, 0x00, 0x00 }, { FCML_OP_MODRM_RM_RW, FCML_OP_IB_EX_EOSA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RMO_IMM8 },
	/* 08 /r OR r/m8, r8 MR Valid Valid r/m8 OR r8.*/
	/* REX + 08 /r OR r/m8*, r8* MR Valid N.E. r/m8 OR r8.*/
    { FCML_AMT_GPI, 0x0807, 0x00C48000, { 0x08, 0x00, 0x00 }, { FCML_OP_MODRM_RM_OP_8_RW, FCML_OP_MODRM_R_8, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RM8_R8 },
	/* 09 /r OR r/m16, r16 MR Valid Valid r/m16 OR r16.*/
	/* 09 /r OR r/m32, r32 MR Valid Valid r/m32 OR r32.*/
	/* REX.W + 09 /r OR r/m64, r64 MR Valid N.E. r/m64 OR r64.*/
    { FCML_AMT_GPI, 0x0807, 0x00C48000, { 0x09, 0x00, 0x00 }, { FCML_OP_MODRM_RM_OP_RW, FCML_OP_MODRM_R, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RMO_RO },
	/* 0A /r OR r8, r/m8 RM Valid Valid r8 OR r/m8.*/
	/* REX + 0A /r OR r8*, r/m8* RM Valid N.E. r8 OR r/m8.*/
    { FCML_AMT_GPI, 0x0000, 0x00C48000, { 0x0A, 0x00, 0x00 }, { FCML_OP_MODRM_R_8_RW, FCML_OP_MODRM_RM_OP_8, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_R8_RM8 },
	/* 0B /r OR r16, r/m16 RM Valid Valid r16 OR r/m16.*/
	/* 0B /r OR r32, r/m32 RM Valid Valid r32 OR r/m32.*/
	/* REX.W + 0B /r OR r64, r/m64 RM Valid N.E. r64 OR r/m64.*/
    { FCML_AMT_GPI, 0x0000, 0x00C48000, { 0x0B, 0x00, 0x00 }, { FCML_OP_MODRM_R_RW, FCML_OP_MODRM_RM_OP, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RO_RMO }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_ORPD[] = {
	/* 66 0F 56 /r ORPD xmm1,xmm2/m128*/
    { FCML_AMT_SSE2_SIMD, 0x1000, 0x00D88000, { 0x0F, 0x56, 0x00 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VORPD[] = {
	/* VEX.NDS.128.66.0F 56 /r VORPD xmm1,xmm2,xmm3/m128*/
	/* VEX.NDS.256.66.0F 56 /r VORPD ymm1,ymm2,ymm3/m256*/
    { FCML_AMT_AVX_SIMD, 0x1080, 0x00D88000, { 0x0F, 0x56, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_ORPS[] = {
	/* 0F 56 /r ORPS xmm1, xmm2/m128*/
    { FCML_AMT_SSE_SIMD, 0x0000, 0x00D88000, { 0x0F, 0x56, 0x00 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VORPS[] = {
	/* VEX.NDS.128.0F 56 /r VORPS xmm1,xmm2,xmm3/m128*/
	/* VEX.NDS.256.0F 56 /r VORPS ymm1,ymm2,ymm3/m256*/
    { FCML_AMT_AVX_SIMD, 0x0080, 0x00D88000, { 0x0F, 0x56, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_OUT[] = {
	/* E6 ib OUT int8, AL I Valid Valid Output byte in AL to I/O port address int8.*/
    { FCML_AMT_GPI, 0x0000, 0x07C40000, { 0xE6, 0x00, 0x00 }, { FCML_OP_IB, FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_AL, FCML_EOS_BYTE ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* E7 ib OUT int8, AX I Valid Valid Output word in AX to I/O port address int8.*/
    { FCML_AMT_GPI, 0x0000, 0x01C40000, { 0xE7, 0x00, 0x00 }, { FCML_OP_IB, FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_AL, FCML_EOS_WORD), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* E7 ib OUT int8, EAX I Valid Valid Output doubleword in EAX to I/O port address int8.*/
    { FCML_AMT_GPI, 0x0000, 0x06C40000, { 0xE7, 0x00, 0x00 }, { FCML_OP_IB, FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_AL, FCML_EOS_DWORD), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* EE OUT DX, AL NP Valid Valid Output byte in AL to I/O port address in DX.*/
    { FCML_AMT_GPI, 0x0000, 0x07C40000, { 0xEE, 0x00, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_DX, FCML_EOS_WORD ), FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_AL, FCML_EOS_BYTE ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* EF OUT DX, AX NP Valid Valid Output word in AX to I/O port address in DX.*/
    { FCML_AMT_GPI, 0x0000, 0x01C40000, { 0xEF, 0x00, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_DX, FCML_EOS_WORD ), FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_AL, FCML_EOS_WORD ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* EF OUT DX, EAX NP Valid Valid Output doubleword in EAX to I/O port address in DX.*/
    { FCML_AMT_GPI, 0x0000, 0x06C40000, { 0xEF, 0x00, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_DX, FCML_EOS_WORD ), FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_AL, FCML_EOS_DWORD ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_OUTS[] = {
	/* 6E OUTS DX, m8 NP Valid Valid Output byte from memory location specified in DS:(E)SI or RSI to I/O port specified in DX.*/
    { FCML_AMT_GPI, 0x0004, 0x07C40000, { 0x6E, 0x00, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_DX, FCML_EOS_WORD ), FCML_OP_EXPLICIT_GPS_REG_ADDRESSING( FCML_REG_SI, FCML_EOS_BYTE, FCML_SEG_ENCODE_REGISTER( FCML_REG_ES, FCML_SEG_DENY_OVERRIDE ) ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_M8 },
	/* 6F OUTS DX, m16 NP Valid Valid Output word from memory location specified in DS:(E)SI or RSI to I/O port specified in DX.*/
    { FCML_AMT_GPI, 0x0004, 0x01C40000, { 0x6F, 0x00, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_DX, FCML_EOS_WORD ), FCML_OP_EXPLICIT_GPS_REG_ADDRESSING( FCML_REG_SI, FCML_EOS_WORD, FCML_SEG_ENCODE_REGISTER( FCML_REG_ES, FCML_SEG_DENY_OVERRIDE ) ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_M16 },
	/* 6F OUTS DX, m32 NP Valid Valid Output doubleword from memory location specified in DS:(E)SI or RSI to I/O port specified in DX.*/
    { FCML_AMT_GPI, 0x0004, 0x06C40000, { 0x6F, 0x00, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_DX, FCML_EOS_WORD ), FCML_OP_EXPLICIT_GPS_REG_ADDRESSING( FCML_REG_SI, FCML_EOS_DWORD, FCML_SEG_ENCODE_REGISTER( FCML_REG_ES, FCML_SEG_DENY_OVERRIDE ) ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_M32 }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PABSW[] = {
	/* 0F 38 1D /r1 PABSW mm1,mm2/m64*/
    { FCML_AMT_SSSE3_SIMD, 0x0000, 0x00EC8000, { 0x0F, 0x38, 0x1D }, { FCML_OP_MODRM_R_MMX_W, FCML_OP_MODRM_RM_MMX_OP, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* 66 0F 38 1D /r PABSW xmm1,xmm2/m128*/
    { FCML_AMT_SSSE3_SIMD, 0x1000, 0x00EC8000, { 0x0F, 0x38, 0x1D }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PABSB[] = {
	/* 0F 38 1C /r1 PABSB mm1,mm2/m64*/
    { FCML_AMT_SSSE3_SIMD, 0x0000, 0x00EC8000, { 0x0F, 0x38, 0x1C }, { FCML_OP_MODRM_R_MMX_W, FCML_OP_MODRM_RM_MMX_OP, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* 66 0F 38 1C /r PABSB xmm1,xmm2/m128*/
    { FCML_AMT_SSSE3_SIMD, 0x1000, 0x00EC8000, { 0x0F, 0x38, 0x1C }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PABSD[] = {
	/* 0F 38 1E /r1 PABSD mm1,mm2/m64*/
    { FCML_AMT_SSSE3_SIMD, 0x0000, 0x00EC8000, { 0x0F, 0x38, 0x1E }, { FCML_OP_MODRM_R_MMX_W, FCML_OP_MODRM_RM_MMX_OP, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* 66 0F 38 1E /r PABSD xmm1,xmm2/m128*/
    { FCML_AMT_SSSE3_SIMD, 0x1000, 0x00EC8000, { 0x0F, 0x38, 0x1E }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPABSB[] = {
	/* VEX.128.66.0F38 1C /r VPABSB xmm1,xmm2/m128*/
    { FCML_AMT_AVX_SIMD, 0x10C0, 0x00EC8000, { 0x0F, 0x38, 0x1C }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.256.66.0F38.WIG 1C /r VPABSB ymm1, ymm2/m256*/
    { FCML_AMT_AVX2_SIMD, 0x10A0, 0x00EC8000, { 0x0F, 0x38, 0x1C }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_MODRM_RM_YMM_OP_256, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPABSW[] = {
	/* VEX.128.66.0F38 1D /r VPABSW xmm1,xmm2/m128*/
    { FCML_AMT_AVX_SIMD, 0x10C0, 0x00EC8000, { 0x0F, 0x38, 0x1D }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.256.66.0F38.WIG 1D /r VPABSW ymm1, ymm2/m256*/
    { FCML_AMT_AVX2_SIMD, 0x10A0, 0x00EC8000, { 0x0F, 0x38, 0x1D }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_MODRM_RM_YMM_OP_256, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPABSD[] = {
	/* VEX.128.66.0F38 1E /r VPABSD xmm1,xmm2/m128*/
    { FCML_AMT_AVX_SIMD, 0x10C0, 0x00EC8000, { 0x0F, 0x38, 0x1E }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.256.66.0F38.WIG 1E /r VPABSD ymm1, ymm2/m256*/
    { FCML_AMT_AVX2_SIMD, 0x10A0, 0x00EC8000, { 0x0F, 0x38, 0x1E }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_MODRM_RM_YMM_OP_256, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPACKSSWB[] = {
	/* VEX.NDS.128.66.0F.WIG 63 /r VPACKSSWB xmm1,xmm2,xmm3/m128*/
    { FCML_AMT_AVX_SIMD, 0x10C0, 0x00D88000, { 0x0F, 0x63, 0x00 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.NDS.256.66.0F.WIG 63 /r VPACKSSWB ymm1,ymm2,ymm3/m256*/
    { FCML_AMT_AVX2_SIMD, 0x10A0, 0x00D88000, { 0x0F, 0x63, 0x00 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_YMM_REG, FCML_OP_MODRM_RM_YMM_OP_256, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PACKSSWB[] = {
	/* 0F 63 /r1 PACKSSWB mm1,mm2/m64*/
    { FCML_AMT_MMX_SIMD, 0x0000, 0x00D88000, { 0x0F, 0x63, 0x00 }, { FCML_OP_MODRM_R_MMX_W, FCML_OP_MODRM_RM_MMX_OP, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* 66 0F 63 /r PACKSSWB xmm1,xmm2/m128*/
    { FCML_AMT_SSE2_SIMD, 0x1000, 0x00D88000, { 0x0F, 0x63, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPACKSSDW[] = {
	/* VEX.NDS.128.66.0F.WIG 6B /r VPACKSSDW xmm1,xmm2,xmm3/m128*/
    { FCML_AMT_AVX_SIMD, 0x10C0, 0x00D88000, { 0x0F, 0x6B, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.NDS.256.66.0F.WIG 6B /r VPACKSSDW ymm1,ymm2,ymm3/m256*/
    { FCML_AMT_AVX2_SIMD, 0x10A0, 0x00D88000, { 0x0F, 0x6B, 0x00 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_YMM_REG, FCML_OP_MODRM_RM_YMM_OP_256, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PACKSSDW[] = {
	/* 0F 6B /r1 PACKSSDW mm1,mm2/m64*/
    { FCML_AMT_MMX_SIMD, 0x0000, 0x00D88000, { 0x0F, 0x6B, 0x00 }, { FCML_OP_MODRM_R_MMX_RW, FCML_OP_MODRM_RM_MMX_OP, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* 66 0F 6B /r PACKSSDW xmm1,xmm2/m128*/
    { FCML_AMT_SSE2_SIMD, 0x1000, 0x00D88000, { 0x0F, 0x6B, 0x00 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PACKUSDW[] = {
	/* 66 0F 38 2B /r PACKUSDW xmm1,xmm2/m128*/
    { FCML_AMT_SSE41_SIMD, 0x1000, 0x00EC8000, { 0x0F, 0x38, 0x2B }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPACKUSDW[] = {
	/* VEX.NDS.128.66.0F38.WIG 2B /r VPACKUSDW xmm1,xmm2,xmm3/m128*/
    { FCML_AMT_AVX_SIMD, 0x10C0, 0x00EC8000, { 0x0F, 0x38, 0x2B }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.NDS.256.66.0F38.WIG 2B /r VPACKUSDW ymm1,ymm2,ymm3/m256*/
    { FCML_AMT_AVX2_SIMD, 0x10A0, 0x00EC8000, { 0x0F, 0x38, 0x2B }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_YMM_REG, FCML_OP_MODRM_RM_YMM_OP_256, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PACKUSWB[] = {
	/* 0F 67 /r1 PACKUSWB mm,mm/m64*/
    { FCML_AMT_MMX_SIMD, 0x0000, 0x00D88000, { 0x0F, 0x67, 0x00 }, { FCML_OP_MODRM_R_MMX_RW, FCML_OP_MODRM_RM_MMX_OP, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* 66 0F 67 /r PACKUSWB xmm1,xmm2/m128*/
    { FCML_AMT_SSE2_SIMD, 0x1000, 0x00D88000, { 0x0F, 0x67, 0x00 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPACKUSWB[] = {
	/* VEX.NDS.128.66.0F.WIG 67 /r VPACKUSWB xmm1,xmm2,xmm3/m128*/
    { FCML_AMT_AVX_SIMD, 0x10C0, 0x00D88000, { 0x0F, 0x67, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.NDS.256.66.0F.WIG 67 /r VPACKUSWB ymm1,ymm2,ymm3/m256*/
    { FCML_AMT_AVX2_SIMD, 0x10A0, 0x00D88000, { 0x0F, 0x67, 0x00 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_YMM_REG, FCML_OP_MODRM_RM_YMM_OP_256, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPADDW[] = {
	/* VEX.NDS.128.66.0F.WIG FD /r VPADDW xmm1,xmm2,xmm3/m128*/
    { FCML_AMT_AVX_SIMD, 0x10C0, 0x00D88000, { 0x0F, 0xFD, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.NDS.256.66.0F.WIG FD /r VPADDW ymm1,ymm2,ymm3/m256*/
    { FCML_AMT_AVX2_SIMD, 0x10A0, 0x00D88000, { 0x0F, 0xFD, 0x00 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_YMM_REG, FCML_OP_MODRM_RM_YMM_OP_256, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPADDQ[] = {
	/* VEX.NDS.128.66.0F.WIG D4 /r VPADDQ xmm1,xmm2,xmm3/m128*/
    { FCML_AMT_AVX_SIMD, 0x10C0, 0x00D88000, { 0x0F, 0xD4, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.NDS.256.66.0F.WIG D4 /r VPADDQ ymm1,ymm2,ymm3/m256*/
    { FCML_AMT_AVX2_SIMD, 0x10A0, 0x00D88000, { 0x0F, 0xD4, 0x00 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_YMM_REG, FCML_OP_MODRM_RM_YMM_OP_256, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PADDW[] = {
	/* 0F FD /r1 PADDW mm,mm/m64*/
    { FCML_AMT_MMX_SIMD, 0x0000, 0x00D88000, { 0x0F, 0xFD, 0x00 }, { FCML_OP_MODRM_R_MMX_RW, FCML_OP_MODRM_RM_MMX_OP, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* 66 0F FD /r PADDW xmm1,xmm2/m128*/
    { FCML_AMT_SSE2_SIMD, 0x1000, 0x00D88000, { 0x0F, 0xFD, 0x00 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPADDB[] = {
	/* VEX.NDS.128.66.0F.WIG FC /r VPADDB xmm1,xmm2,xmm3/m128*/
    { FCML_AMT_AVX_SIMD, 0x10C0, 0x00D88000, { 0x0F, 0xFC, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.NDS.256.66.0F.WIG FC /r VPADDB ymm1,ymm2,ymm3/m256*/
    { FCML_AMT_AVX2_SIMD, 0x10A0, 0x00D88000, { 0x0F, 0xFC, 0x00 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_YMM_REG, FCML_OP_MODRM_RM_YMM_OP_256, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPADDD[] = {
	/* VEX.NDS.128.66.0F.WIG FE /r VPADDD xmm1,xmm2,xmm3/m128*/
    { FCML_AMT_AVX_SIMD, 0x10C0, 0x00D88000, { 0x0F, 0xFE, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.NDS.256.66.0F.WIG FE /r VPADDD ymm1,ymm2,ymm3/m256*/
    { FCML_AMT_AVX2_SIMD, 0x10A0, 0x00D88000, { 0x0F, 0xFE, 0x00 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_YMM_OP_256, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PADDB[] = {
	/* 0F FC /r1 PADDB mm,mm/m64*/
    { FCML_AMT_MMX_SIMD, 0x0000, 0x00D88000, { 0x0F, 0xFC, 0x00 }, { FCML_OP_MODRM_R_MMX_RW, FCML_OP_MODRM_RM_MMX_OP, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* 66 0F FC /r PADDB xmm1,xmm2/m128*/
    { FCML_AMT_SSE2_SIMD, 0x1000, 0x00D88000, { 0x0F, 0xFC, 0x00 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PADDD[] = {
	/* 0F FE /r1 PADDD mm,mm/m64*/
    { FCML_AMT_MMX_SIMD, 0x0000, 0x00D88000, { 0x0F, 0xFE, 0x00 }, { FCML_OP_MODRM_R_MMX_RW, FCML_OP_MODRM_RM_MMX_OP, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* 66 0F FE /r PADDD xmm1,xmm2/m128*/
    { FCML_AMT_SSE2_SIMD, 0x1000, 0x00D88000, { 0x0F, 0xFE, 0x00 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPADDSW[] = {
	/* VEX.NDS.128.66.0F.WIG ED /r VPADDSW xmm1,xmm2,xmm3/m128*/
    { FCML_AMT_AVX_SIMD, 0x10C0, 0x00D88000, { 0x0F, 0xED, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.NDS.256.66.0F.WIG ED /r VPADDSW ymm1,ymm2,ymm3/m256*/
    { FCML_AMT_AVX2_SIMD, 0x10A0, 0x00D88000, { 0x0F, 0xED, 0x00 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_YMM_REG, FCML_OP_MODRM_RM_YMM_OP_256, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PADDSB[] = {
	/* 0F EC /r1 PADDSB mm,mm/m64*/
    { FCML_AMT_MMX_SIMD, 0x0000, 0x00D88000, { 0x0F, 0xEC, 0x00 }, { FCML_OP_MODRM_R_MMX_RW, FCML_OP_MODRM_RM_MMX_OP, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* 66 0F EC /r PADDSB xmm1,xmm2/m128*/
    { FCML_AMT_SSE2_SIMD, 0x1000, 0x00D88000, { 0x0F, 0xEC, 0x00 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PADDSW[] = {
	/* 0F ED /r1 PADDSW mm,mm/m64*/
    { FCML_AMT_MMX_SIMD, 0x0000, 0x00D88000, { 0x0F, 0xED, 0x00 }, { FCML_OP_MODRM_R_MMX_RW, FCML_OP_MODRM_RM_MMX_OP, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* 66 0F ED /r PADDSW xmm1,xmm2/m128*/
    { FCML_AMT_SSE2_SIMD, 0x1000, 0x00D88000, { 0x0F, 0xED, 0x00 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPADDSB[] = {
	/* VEX.NDS.128.66.0F.WIG EC /r VPADDSB xmm1,xmm2,xmm3/m128*/
    { FCML_AMT_AVX_SIMD, 0x10C0, 0x00D88000, { 0x0F, 0xEC, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.NDS.256.66.0F.WIG EC /r VPADDSB ymm1,ymm2,ymm3/m256*/
    { FCML_AMT_AVX2_SIMD, 0x10A0, 0x00D88000, { 0x0F, 0xEC, 0x00 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_YMM_REG, FCML_OP_MODRM_RM_YMM_OP_256, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PADDUSW[] = {
	/* 0F DD /r1 PADDUSW mm,mm/m64*/
    { FCML_AMT_MMX_SIMD, 0x0000, 0x00D88000, { 0x0F, 0xDD, 0x00 }, { FCML_OP_MODRM_R_MMX_RW, FCML_OP_MODRM_RM_MMX_OP, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* 66 0F DD /r PADDUSW xmm1,xmm2/m128*/
    { FCML_AMT_SSE2_SIMD, 0x1000, 0x00D88000, { 0x0F, 0xDD, 0x00 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PADDUSB[] = {
	/* 0F DC /r1 PADDUSB mm,mm/m64*/
    { FCML_AMT_MMX_SIMD, 0x0000, 0x00D88000, { 0x0F, 0xDC, 0x00 }, { FCML_OP_MODRM_R_MMX_RW, FCML_OP_MODRM_RM_MMX_OP, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* 66 0F DC /r PADDUSB xmm1,xmm2/m128*/
    { FCML_AMT_SSE2_SIMD, 0x1000, 0x00D88000, { 0x0F, 0xDC, 0x00 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPADDUSW[] = {
	/* VEX.NDS.128.66.0F.WIG DD /r VPADDUSW xmm1,xmm2,xmm3/m128*/
    { FCML_AMT_AVX_SIMD, 0x10C0, 0x00D88000, { 0x0F, 0xDD, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.NDS.256.66.0F.WIG DD /r VPADDUSW ymm1,ymm2,ymm3/m256*/
    { FCML_AMT_AVX2_SIMD, 0x10A0, 0x00D88000, { 0x0F, 0xDD, 0x00 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_YMM_REG, FCML_OP_MODRM_RM_YMM_OP_256, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPADDUSB[] = {
	/* VEX.NDS.128.660F.WIG DC /r VPADDUSB xmm1,xmm2,xmm3/m128*/
    { FCML_AMT_AVX_SIMD, 0x10C0, 0x00D88000, { 0x0F, 0xDC, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.NDS.256.66.0F.WIG DC /r VPADDUSB ymm1,ymm2,ymm3/m256*/
    { FCML_AMT_AVX2_SIMD, 0x10A0, 0x00D88000, { 0x0F, 0xDC, 0x00 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_YMM_REG, FCML_OP_MODRM_RM_YMM_OP_256, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PADDQ[] = {
	/* 0F D4 /r1 PADDQ mm1,mm2/m64*/
    { FCML_AMT_SSE2_SIMD, 0x0000, 0x00D88000, { 0x0F, 0xD4, 0x00 }, { FCML_OP_MODRM_R_MMX_RW, FCML_OP_MODRM_RM_MMX_OP, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* 66 0F D4 /r PADDQ xmm1,xmm2/m128*/
    { FCML_AMT_SSE2_SIMD, 0x1000, 0x00D88000, { 0x0F, 0xD4, 0x00 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PALIGNR[] = {
	/* 0F 3A 0F PALIGNR mm1,mm2/m64,int8*/
    { FCML_AMT_SSSE3_SIMD, 0x0000, 0x00EC8000, { 0x0F, 0x3A, 0x00F }, { FCML_OP_MODRM_R_MMX_RW, FCML_OP_MODRM_RM_MMX_OP, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* 66 0F 3A 0F PALIGNR xmm1,xmm2/m128,int8*/
    { FCML_AMT_SSSE3_SIMD, 0x1000, 0x00EC8000, { 0x0F, 0x3A, 0x00F }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_128, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPALIGNR[] = {
	/* VEX.NDS.128.66.0F3A.WIG 0F /r ib VPALIGNR xmm1,xmm2,xmm3/m128,int8*/
    { FCML_AMT_AVX_SIMD, 0x10C0, 0x00EC8000, { 0x0F, 0x3A, 0x0F }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_OP_IB, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.NDS.256.66.0F3A.WIG 0F /r ib VPALIGNR ymm1,ymm2,ymm3/m256,int8*/
    { FCML_AMT_AVX2_SIMD, 0x10A0, 0x00EC8000, { 0x0F, 0x3A, 0x0F }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_YMM_REG, FCML_OP_MODRM_RM_YMM_OP_256, FCML_OP_IB, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PAND[] = {
	/* 0F DB /r PAND mm,mm/m64*/
    { FCML_AMT_MMX_SIMD, 0x0000, 0x00D88000, { 0x0F, 0xDB, 0x00 }, { FCML_OP_MODRM_R_MMX_RW, FCML_OP_MODRM_RM_MMX_OP, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* 66 0F DB /r PAND xmm1,xmm2/m128*/
    { FCML_AMT_SSE2_SIMD, 0x1000, 0x00D88000, { 0x0F, 0xDB, 0x00 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPAND[] = {
	/* VEX.NDS.128.66.0F.WIG DB /r VPAND xmm1,xmm2,xmm3/m128*/
    { FCML_AMT_AVX_SIMD, 0x10C0, 0x00D88000, { 0x0F, 0xDB, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.NDS.256.66.0F.WIG DB /r VPAND ymm1,ymm2,ymm3/m256*/
    { FCML_AMT_AVX2_SIMD, 0x10A0, 0x00D88000, { 0x0F, 0xDB, 0x00 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_YMM_REG, FCML_OP_MODRM_RM_YMM_OP_256, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PANDN[] = {
	/* 0F DF /r PANDN mm,mm/m64*/
    { FCML_AMT_MMX_SIMD, 0x0000, 0x00D88000, { 0x0F, 0xDF, 0x00 }, { FCML_OP_MODRM_R_MMX_RW, FCML_OP_MODRM_RM_MMX_OP, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* 66 0F DF /r PANDN xmm1,xmm2/m128*/
    { FCML_AMT_SSE2_SIMD, 0x1000, 0x00D88000, { 0x0F, 0xDF, 0x00 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPANDN[] = {
	/* VEX.NDS.128.66.0F.WIG DF /r VPANDN xmm1,xmm2,xmm3/m128*/
    { FCML_AMT_AVX_SIMD, 0x10C0, 0x00D88000, { 0x0F, 0xDF, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.NDS.256.66.0F.WIG DF /r VPANDN ymm1,ymm2,ymm3/m256*/
    { FCML_AMT_AVX2_SIMD, 0x10A0, 0x00D88000, { 0x0F, 0xDF, 0x00 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_YMM_REG, FCML_OP_MODRM_RM_YMM_OP_256, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PAUSE[] = {
	/* F3 90 PAUSE*/
    { FCML_AMT_SSE2, 0x4000, 0x00C40000, { 0x90, 0x00, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PAVGW[] = {
	/* 0F E3 /r1 PAVGW mm1,mm2/m64*/
    { FCML_AMT_MMX, 0x0000, 0x00D88000, { 0x0F, 0xE3, 0x00 }, { FCML_OP_MODRM_R_MMX_RW, FCML_OP_MODRM_RM_MMX_OP, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* 66 0F E3 /r PAVGW xmm1,xmm2/m128*/
    { FCML_AMT_SSE_SIMD, 0x1000, 0x00D88000, { 0x0F, 0xE3, 0x00 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PAVGB[] = {
	/* 0F E0 /r1 PAVGB mm1,mm2/m64*/
    { FCML_AMT_MMX, 0x0000, 0x00D88000, { 0x0F, 0xE0, 0x00 }, { FCML_OP_MODRM_R_MMX_RW, FCML_OP_MODRM_RM_MMX_OP, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* 66 0F E0, /r PAVGB xmm1,xmm2/m128*/
    { FCML_AMT_SSE_SIMD, 0x1000, 0x00D88000, { 0x0F, 0xE0, 0x00 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPAVGW[] = {
	/* VEX.NDS.128.66.0F.WIG E3 /r VPAVGW xmm1,xmm2,xmm3/m128*/
    { FCML_AMT_AVX_SIMD, 0x10C0, 0x00D88000, { 0x0F, 0xE3, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.NDS.256.66.0F.WIG E3 /r VPAVGW ymm1,ymm2,ymm3/m256*/
    { FCML_AMT_AVX2_SIMD, 0x10A0, 0x00D88000, { 0x0F, 0xE3, 0x00 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_YMM_REG, FCML_OP_MODRM_RM_YMM_OP_256, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPAVGB[] = {
	/* VEX.NDS.128.66.0F.WIG E0 /r VPAVGB xmm1,xmm2,xmm3/m128*/
    { FCML_AMT_AVX_SIMD, 0x10C0, 0x00D88000, { 0x0F, 0xE0, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.NDS.256.66.0F.WIG E0 /r VPAVGB ymm1,ymm2,ymm3/m256*/
    { FCML_AMT_AVX2_SIMD, 0x10A0, 0x00D88000, { 0x0F, 0xE0, 0x00 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_YMM_REG, FCML_OP_MODRM_RM_YMM_OP_256, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PBLENDVB[] = {
	/* 66 0F 38 10 /r PBLENDVB xmm1,xmm2/m128,<XMM0>*/
    { FCML_AMT_SSE41_SIMD, 0x1000, 0x00EC8000, { 0x0F, 0x38, 0x10 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_128, FCML_OP_EXPLICIT_REG( FCML_REG_SIMD, FCML_REG_XMM0, FCML_EOS_OWORD ), FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPBLENDVB[] = {
	/* VEX.NDS.128.66.0F3A 4C /r /is4 VPBLENDVB xmm1,xmm2,xmm3/m128,xmm4*/
    { FCML_AMT_AVX_SIMD, 0x10C0, 0x00EC8000, { 0x0F, 0x3A, 0x4C }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_OP_OPERAND_IS4, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.NDS.256.66.0F3A.W0 4C /r /is4 VPBLENDVB ymm1,ymm2,ymm3/m256,ymm4*/
    { FCML_AMT_AVX2_SIMD, 0x10A0, 0x00EC8000, { 0x0F, 0x3A, 0x4C }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_YMM_REG, FCML_OP_MODRM_RM_YMM_OP_256, FCML_OP_OPERAND_IS4, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PBLENDW[] = {
	/* 66 0F 3A 0E /r ib PBLENDW xmm1,xmm2/m128,int8*/
    { FCML_AMT_SSE41_SIMD, 0x1000, 0x00EC8000, { 0x0F, 0x3A, 0x0E }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_128, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPBLENDW[] = {
	/* VEX.NDS.128.66.0F3A 0E /r ib VPBLENDW xmm1,xmm2,xmm3/m128,int8*/
    { FCML_AMT_AVX_SIMD, 0x10C0, 0x00EC8000, { 0x0F, 0x3A, 0x0E }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_OP_IB, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.NDS.256.66.0F3A.WIG 0E /r ib VPBLENDW ymm1,ymm2,ymm3/m256,int8*/
    { FCML_AMT_AVX2_SIMD, 0x10A0, 0x00EC8000, { 0x0F, 0x3A, 0x0E }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_YMM_REG, FCML_OP_MODRM_RM_YMM_OP_256, FCML_OP_IB, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPBLENDD[] = {
	/* VEX.NDS.128.66.0F3A.W0 02 /r ib VPBLENDD xmm1,xmm2,xmm3/m128,int8*/
	/* VEX.NDS.256.66.0F3A.W0 02 /r ib VPBLENDD ymm1,ymm2,ymm3/m256,int8*/
    { FCML_AMT_AVX2_SIMD, 0x1090, 0x00EC8000, { 0x0F, 0x3A, 0x02 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_OP_IB, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PCLMULQDQ[] = {
	/* 66 0F 3A 44 /r ib PCLMULQDQ xmm1,xmm2/m128,int8*/
    { FCML_AMT_CLMUL, 0x1000, 0x00EC8000, { 0x0F, 0x3A, 0x44 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_128, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPCLMULQDQ[] = {
	/* VEX.NDS.128.66.0F3A 44 /r ib VPCLMULQDQ xmm1,xmm2,xmm3/m128,int8*/
    { FCML_AMT_AVX_SIMD | FCML_AMT_CLMUL, 0x10C0, 0x00EC8000, { 0x0F, 0x3A, 0x44 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_OP_IB, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PCMPEQB[] = {
    /* 0F 74 /r1 PCMPEQB mm,mm/m64*/
    { FCML_AMT_MMX_SIMD, 0x0000, 0x00D88000, { 0x0F, 0x74, 0x00 }, { FCML_OP_MODRM_R_MMX_RW, FCML_OP_MODRM_RM_MMX_OP, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
    /* 66 0F 74 /r PCMPEQB xmm1,xmm2/m128*/
    { FCML_AMT_SSE2_SIMD, 0x1000, 0x00D88000, { 0x0F, 0x74, 0x00 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PCMPEQW[] = {
	/* 0F 75 /r1 PCMPEQW mm,mm/m64*/
    { FCML_AMT_MMX_SIMD, 0x0000, 0x00D88000, { 0x0F, 0x75, 0x00 }, { FCML_OP_MODRM_R_MMX_RW, FCML_OP_MODRM_RM_MMX_OP, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* 66 0F 75 /r PCMPEQW xmm1,xmm2/m128*/
    { FCML_AMT_SSE2_SIMD, 0x1000, 0x00D88000, { 0x0F, 0x75, 0x00 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PCMPEQD[] = {
	/* 0F 76 /r1 PCMPEQD mm,mm/m64*/
    { FCML_AMT_MMX_SIMD, 0x0000, 0x00D88000, { 0x0F, 0x76, 0x00 }, { FCML_OP_MODRM_R_MMX_RW, FCML_OP_MODRM_RM_MMX_OP, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* 66 0F 76 /r PCMPEQD xmm1,xmm2/m128*/
    { FCML_AMT_SSE2_SIMD, 0x1000, 0x00D88000, { 0x0F, 0x76, 0x00 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPCMPEQD[] = {
	/* VEX.NDS.128.66.0F.WIG 76 /r VPCMPEQD xmm1,xmm2,xmm3/m128*/
    { FCML_AMT_AVX_SIMD, 0x10C0, 0x00D88000, { 0x0F, 0x76, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.NDS.256.66.0F.WIG FCML_AMT_AVX_SIMD /r VPCMPEQD ymm1,ymm2,ymm3/m256*/
    { FCML_AMT_AVX2_SIMD, 0x10A0, 0x00D88000, { 0x0F, 0x76, 0x00 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_YMM_REG, FCML_OP_MODRM_RM_YMM_OP_256, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPCMPEQW[] = {
	/* VEX.NDS.128.66.0F.WIG 75 /r VPCMPEQW xmm1,xmm2,xmm3/m128*/
    { FCML_AMT_AVX_SIMD, 0x10C0, 0x00D88000, { 0x0F, 0x75, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.NDS.256.66.0F.WIG 75 /r VPCMPEQW ymm1,ymm2,ymm3/m256*/
    { FCML_AMT_AVX2_SIMD, 0x10A0, 0x00D88000, { 0x0F, 0x75, 0x00 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_YMM_REG, FCML_OP_MODRM_RM_YMM_OP_256, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPCMPEQB[] = {
	/* VEX.NDS.128.66.0F.WIG 74 /r VPCMPEQB xmm1,xmm2,xmm3/m128*/
    { FCML_AMT_AVX_SIMD, 0x10C0, 0x00D88000, { 0x0F, 0x74, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.NDS.256.66.0F.WIG 74 /r VPCMPEQB ymm1,ymm2,ymm3/m256*/
    { FCML_AMT_AVX2_SIMD, 0x10A0, 0x00D88000, { 0x0F, 0x74, 0x00 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_YMM_REG, FCML_OP_MODRM_RM_YMM_OP_256, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PCMPEQQ[] = {
	/* 66 0F 38 29 /r PCMPEQQ xmm1,xmm2/m128*/
    { FCML_AMT_SSE41_SIMD, 0x1000, 0x00EC8000, { 0x0F, 0x38, 0x29 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPCMPEQQ[] = {
	/* VEX.NDS.128.66.0F38.WIG 29 /r VPCMPEQQ xmm1,xmm2,xmm3/m128*/
    { FCML_AMT_AVX_SIMD, 0x10C0, 0x00EC8000, { 0x0F, 0x38, 0x29 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.NDS.256.66.0F38.WIG 29 /r VPCMPEQQ ymm1,ymm2,ymm3/m256*/
    { FCML_AMT_AVX2_SIMD, 0x10A0, 0x00EC8000, { 0x0F, 0x38, 0x29 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_YMM_REG, FCML_OP_MODRM_RM_YMM_OP_256, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PCMPESTRI[] = {
	/* 66 0F 3A 61 /r int8 PCMPESTRI xmm1,xmm2/m128,int8*/
    { FCML_AMT_SSE42_SIMD, 0x1000, 0x00EC8000, { 0x0F, 0x3A, 0x61 }, { FCML_OP_MODRM_R_XMM, FCML_OP_MODRM_RM_XMM_OP_128, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPCMPESTRI[] = {
	/* VEX.128.66.0F3A.WIG 61 /r ib VPCMPESTRI xmm1,xmm2/m128,int8*/
    { FCML_AMT_AVX_SIMD, 0x10C0, 0x00EC8000, { 0x0F, 0x3A, 0x61 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_OP_128, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PCMPESTRM[] = {
	/* 66 0F 3A 60 /r int8 PCMPESTRM xmm1,xmm2/m128,int8*/
    { FCML_AMT_SSE42_SIMD, 0x1000, 0x00EC8000, { 0x0F, 0x3A, 0x60 }, { FCML_OP_MODRM_R_XMM, FCML_OP_MODRM_RM_XMM_OP_128, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPCMPESTRM[] = {
	/* VEX.128.66.0F3A.WIG 60 /r ib VPCMPESTRM xmm1,xmm2/m128,int8*/
    { FCML_AMT_AVX_SIMD, 0x10C0, 0x00EC8000, { 0x0F, 0x3A, 0x60 }, { FCML_OP_MODRM_R_XMM, FCML_OP_MODRM_RM_XMM_OP_128, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PCMPGTW[] = {
	/* 0F 65 /r1 PCMPGTW mm,mm/m64*/
    { FCML_AMT_MMX_SIMD, 0x0000, 0x00D88000, { 0x0F, 0x65, 0x00 }, { FCML_OP_MODRM_R_MMX_RW, FCML_OP_MODRM_RM_MMX_OP, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* 66 0F 65 /r PCMPGTW xmm1,xmm2/m128*/
    { FCML_AMT_SSE2_SIMD, 0x1000, 0x00D88000, { 0x0F, 0x65, 0x00 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PCMPGTD[] = {
	/* 0F 66 /r1 PCMPGTD mm,mm/m64*/
    { FCML_AMT_MMX_SIMD, 0x0000, 0x00D88000, { 0x0F, 0x66, 0x00 }, { FCML_OP_MODRM_R_MMX_RW, FCML_OP_MODRM_RM_MMX_OP, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* 66 0F 66 /r PCMPGTD xmm1,xmm2/m128*/
    { FCML_AMT_SSE2_SIMD, 0x1000, 0x00D88000, { 0x0F, 0x66, 0x00 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PCMPGTB[] = {
	/* 0F 64 /r1 PCMPGTB mm,mm/m64*/
    { FCML_AMT_MMX_SIMD, 0x0000, 0x00D88000, { 0x0F, 0x64, 0x00 }, { FCML_OP_MODRM_R_MMX_RW, FCML_OP_MODRM_RM_MMX_OP, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* 66 0F 64 /r PCMPGTB xmm1,xmm2/m128*/
    { FCML_AMT_SSE2_SIMD, 0x1000, 0x00D88000, { 0x0F, 0x64, 0x00 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPCMPGTW[] = {
	/* VEX.NDS.128.66.0F.WIG 65 /r VPCMPGTW xmm1,xmm2,xmm3/m128*/
    { FCML_AMT_AVX_SIMD, 0x10C0, 0x00D88000, { 0x0F, 0x65, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.NDS.256.66.0F.WIG 65 /r VPCMPGTW ymm1,ymm2,ymm3/m256*/
    { FCML_AMT_AVX2_SIMD, 0x10A0, 0x00D88000, { 0x0F, 0x65, 0x00 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_YMM_REG, FCML_OP_MODRM_RM_YMM_OP_256, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPCMPGTD[] = {
	/* VEX.NDS.128.66.0F.WIG 66 /r VPCMPGTD xmm1,xmm2,xmm3/m128*/
    { FCML_AMT_AVX_SIMD, 0x10C0, 0x00D88000, { 0x0F, 0x66, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.NDS.256.66.0F.WIG 66 /r VPCMPGTD ymm1,ymm2,ymm3/m256*/
    { FCML_AMT_AVX2_SIMD, 0x10A0, 0x00D88000, { 0x0F, 0x66, 0x00 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_YMM_REG, FCML_OP_MODRM_RM_YMM_OP_256, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPCMPGTB[] = {
	/* VEX.NDS.128.66.0F.WIG 64 /r VPCMPGTB xmm1,xmm2,xmm3/m128*/
    { FCML_AMT_AVX_SIMD, 0x10C0, 0x00D88000, { 0x0F, 0x64, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.NDS.256.66.0F.WIG 64 /r VPCMPGTB ymm1,ymm2,ymm3/m256*/
    { FCML_AMT_AVX2_SIMD, 0x10A0, 0x00D88000, { 0x0F, 0x64, 0x00 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_YMM_REG, FCML_OP_MODRM_RM_YMM_OP_256, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PCMPGTQ[] = {
	/* 66 0F 38 37 /r PCMPGTQ xmm1,xmm2/m128*/
    { FCML_AMT_SSE42_SIMD, 0x1000, 0x00EC8000, { 0x0F, 0x38, 0x37 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPCMPGTQ[] = {
	/* VEX.NDS.128.66.0F38.WIG 37 /r VPCMPGTQ xmm1,xmm2,xmm3/m128*/
    { FCML_AMT_AVX_SIMD, 0x10C0, 0x00EC8000, { 0x0F, 0x38, 0x37 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.NDS.256.66.0F38.WIG 37 /r VPCMPGTQ ymm1,ymm2,ymm3/m256*/
    { FCML_AMT_AVX2_SIMD, 0x10A0, 0x00EC8000, { 0x0F, 0x38, 0x37 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_YMM_REG, FCML_OP_MODRM_RM_YMM_OP_256, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PCMPISTRI[] = {
	/* 66 0F 3A 63 /r int8 PCMPISTRI xmm1,xmm2/m128,int8*/
    { FCML_AMT_SSE42_SIMD, 0x1000, 0x00EC8000, { 0x0F, 0x3A, 0x63 }, { FCML_OP_MODRM_R_XMM, FCML_OP_MODRM_RM_XMM_OP_128, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPCMPISTRI[] = {
	/* VEX.128.66.0F3A.WIG 63 /r ib VPCMPISTRI xmm1,xmm2/m128,int8*/
    { FCML_AMT_AVX_SIMD, 0x10C0, 0x00EC8000, { 0x0F, 0x3A, 0x63 }, { FCML_OP_MODRM_R_XMM, FCML_OP_MODRM_RM_XMM_OP_128, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PCMPISTRM[] = {
	/* 66 0F 3A 62 /r int8 PCMPISTRM xmm1,xmm2/m128,int8*/
    { FCML_AMT_SSE42_SIMD, 0x1000, 0x00EC8000, { 0x0F, 0x3A, 0x62 }, { FCML_OP_MODRM_R_XMM, FCML_OP_MODRM_RM_XMM_OP_128, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPCMPISTRM[] = {
	/* VEX.128.66.0F3A.WIG 62 /r ib VPCMPISTRM xmm1,xmm2/m128,int8*/
    { FCML_AMT_AVX_SIMD, 0x10C0, 0x00EC8000, { 0x0F, 0x3A, 0x62 }, { FCML_OP_MODRM_R_XMM, FCML_OP_MODRM_RM_XMM_OP_128, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPEXTRB[] = {
	/* VEX.128.66.0F3A.W0 14 /r ib VPEXTRB reg/m8, xmm2, int8*/
    { FCML_AMT_AVX_SIMD, 0x12C0, 0x40EC8000, { 0x0F, 0x3A, 0x14 }, { FCML_OP_RM(FCML_REG_GPR, FCML_EOS_EOSA, FCML_EOS_BYTE | FCML_EOS_OPT, FCML_RMF_RM ) | FCML_OA_W, FCML_OP_MODRM_R_XMM, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPEXTRQ[] = {
	/* VEX.128.66.0F3A.W1 16 /r ib VPEXTRQ r64/m64, xmm2, int8*/
    { FCML_AMT_AVX_SIMD, 0x10C8, 0x04AC8000, { 0x0F, 0x3A, 0x16 }, { FCML_OP_RM(FCML_REG_GPR, FCML_EOS_QWORD, FCML_EOS_QWORD | FCML_EOS_OPT, FCML_RMF_RM ) | FCML_OA_W, FCML_OP_MODRM_R_XMM, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PEXTRQ[] = {
	/* 66 REX.W 0F 3A 16 /r ib PEXTRQ r/m64, xmm2, int8*/
    { FCML_AMT_SSE41_SIMD, 0x1008, 0x04AC8000, { 0x0F, 0x3A, 0x16 }, { FCML_OP_RM(FCML_REG_GPR, FCML_EOS_QWORD, FCML_EOS_QWORD | FCML_EOS_OPT, FCML_RMF_RM ) | FCML_OA_W, FCML_OP_MODRM_R_XMM, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PEXTRB[] = {
	/* 66 0F 3A 14 /r ib PEXTRB reg/m8,xmm2,int8*/
    { FCML_AMT_SSE41_SIMD, 0x1000, 0x40EC8000, { 0x0F, 0x3A, 0x14 }, { FCML_OP_RM(FCML_REG_GPR, FCML_EOS_EOSA, FCML_EOS_BYTE | FCML_EOS_OPT, FCML_RMF_RM ) | FCML_OA_W, FCML_OP_MODRM_R_XMM, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PEXTRD[] = {
	/* 66 0F 3A 16 /r ib PEXTRD r/m32, xmm2, int8*/
    { FCML_AMT_SSE41_SIMD, 0x1000, 0x40EC8000, { 0x0F, 0x3A, 0x16 }, { FCML_OP_RM(FCML_REG_GPR, FCML_EOS_EOSA, FCML_EOS_DWORD | FCML_EOS_OPT, FCML_RMF_RM ) | FCML_OA_W, FCML_OP_MODRM_R_XMM, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPEXTRD[] = {
	/* VEX.128.66.0F3A.W0 16 /r ib VPEXTRD r32/m32, xmm2, int8*/
    { FCML_AMT_AVX_SIMD, 0x13D0, 0x40EC8000, { 0x0F, 0x3A, 0x16 }, { FCML_OP_RM(FCML_REG_GPR, FCML_EOS_EOSA, FCML_EOS_DWORD | FCML_EOS_OPT, FCML_RMF_RM ) | FCML_OA_W, FCML_OP_MODRM_R_XMM, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PEXTRW[] = {
	/* 0F C5 /r ib PEXTRW reg,mm,int8*/
    { FCML_AMT_SSE_SIMD, 0x0000, 0x40D88000, { 0x0F, 0xC5, 0x00 }, { FCML_OP_R(FCML_REG_GPR, FCML_EOS_EOSA) | FCML_OA_W, FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_MWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* 66 0F C5 /r ib PEXTRW reg,xmm,int8*/
    { FCML_AMT_SSE_SIMD, 0x1000, 0x40D88000, { 0x0F, 0xC5, 0x00 }, { FCML_OP_R(FCML_REG_GPR, FCML_EOS_EOSA) | FCML_OA_W, FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_XWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* 66 0F 3A 15 /r ib PEXTRW reg/m16,xmm,int8*/
    { FCML_AMT_SSE41_SIMD, 0x1000, 0x40EC8000, { 0x0F, 0x3A, 0x15 }, { FCML_OP_RM(FCML_REG_GPR, FCML_EOS_EOSA, FCML_EOS_WORD | FCML_EOS_OPT, FCML_RMF_RM ) | FCML_OA_W, FCML_OP_R(FCML_REG_SIMD, FCML_EOS_XWORD), FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPEXTRW[] = {
	/* VEX.128.66.0F.W0 C5 /r ib VPEXTRW reg,xmm1,int8*/
    { FCML_AMT_AVX_SIMD, 0x13C0, 0x40D88000, { 0x0F, 0xC5, 0x00 }, { FCML_OP_R(FCML_REG_GPR, FCML_EOS_EOSA) | FCML_OA_W, FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_XWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.128.66.0F3A.W0 15 /r ib VPEXTRW reg/m16,xmm2,int8*/
    { FCML_AMT_AVX_SIMD, 0x13C0, 0x40EC8000, { 0x0F, 0x3A, 0x15 }, { FCML_OP_RM(FCML_REG_GPR, FCML_EOS_EOSA, FCML_EOS_WORD | FCML_EOS_OPT, FCML_RMF_RM ) | FCML_OA_W, FCML_OP_R(FCML_REG_SIMD, FCML_EOS_XWORD), FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPHADDW[] = {
	/* VEX.NDS.128.66.0F38.WIG 01 /r VPHADDW xmm1,xmm2,xmm3/m128*/
    { FCML_AMT_AVX_SIMD, 0x10C0, 0x00EC8000, { 0x0F, 0x38, 0x01 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.NDS.256.66.0F38.WIG 01 /r VPHADDW ymm1,ymm2,ymm3/m256*/
    { FCML_AMT_AVX2_SIMD, 0x10A0, 0x00EC8000, { 0x0F, 0x38, 0x01 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_YMM_REG, FCML_OP_MODRM_RM_YMM_OP_256, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPHADDD[] = {
	/* VEX.NDS.128.66.0F38.WIG 02 /r VPHADDD xmm1,xmm2,xmm3/m128*/
    { FCML_AMT_AVX_SIMD, 0x10C0, 0x00EC8000, { 0x0F, 0x38, 0x02 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.NDS.256.66.0F38.WIG 02 /r VPHADDD ymm1,ymm2,ymm3/m256*/
    { FCML_AMT_AVX2_SIMD, 0x10A0, 0x00EC8000, { 0x0F, 0x38, 0x02 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_YMM_REG, FCML_OP_MODRM_RM_YMM_OP_256, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PHADDD[] = {
	/* 0F 38 02 /r PHADDD mm1,mm2/m64*/
    { FCML_AMT_SSSE3_SIMD, 0x0000, 0x00EC8000, { 0x0F, 0x38, 0x02 }, { FCML_OP_MODRM_R_MMX_RW, FCML_OP_MODRM_RM_MMX_OP, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* 66 0F 38 02 /r PHADDD xmm1,xmm2/m128*/
    { FCML_AMT_SSSE3_SIMD, 0x1000, 0x00EC8000, { 0x0F, 0x38, 0x02 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PHADDW[] = {
	/* 0F 38 01 /r PHADDW mm1,mm2/m64*/
    { FCML_AMT_SSSE3_SIMD, 0x0000, 0x00EC8000, { 0x0F, 0x38, 0x01 }, { FCML_OP_MODRM_R_MMX_RW, FCML_OP_MODRM_RM_MMX_OP, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* 66 0F 38 01 /r PHADDW xmm1,xmm2/m128*/
    { FCML_AMT_SSSE3_SIMD, 0x1000, 0x00EC8000, { 0x0F, 0x38, 0x01 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PHADDSW[] = {
	/* 0F 38 03 /r PHADDSW mm1,mm2/m64*/
    { FCML_AMT_SSSE3_SIMD, 0x0000, 0x00EC8000, { 0x0F, 0x38, 0x03 }, { FCML_OP_MODRM_R_MMX_RW, FCML_OP_MODRM_RM_MMX_OP, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* 66 0F 38 03 /r PHADDSW xmm1,xmm2/m128*/
    { FCML_AMT_SSSE3_SIMD, 0x1000, 0x00EC8000, { 0x0F, 0x38, 0x03 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPHADDSW[] = {
	/* VEX.NDS.128.66.0F38.WIG 03 /r VPHADDSW xmm1,xmm2,xmm3/m128*/
    { FCML_AMT_AVX_SIMD, 0x10C0, 0x00EC8000, { 0x0F, 0x38, 0x03 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.NDS.256.66.0F38.WIG 03 /r VPHADDSW ymm1,ymm2,ymm3/m256*/
    { FCML_AMT_AVX2_SIMD, 0x10A0, 0x00EC8000, { 0x0F, 0x38, 0x03 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_YMM_REG, FCML_OP_MODRM_RM_YMM_OP_256, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PHMINPOSUW[] = {
	/* 66 0F 38 41 /r PHMINPOSUW xmm1,xmm2/m128*/
    { FCML_AMT_SSE41_SIMD, 0x1000, 0x00EC8000, { 0x0F, 0x38, 0x41 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPHMINPOSUW[] = {
	/* VEX.128.66.0F38.WIG 41 /r VPHMINPOSUW xmm1,xmm2/m128*/
    { FCML_AMT_AVX_SIMD, 0x10C0, 0x00EC8000, { 0x0F, 0x38, 0x41 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PHSUBD[] = {
	/* 0F 38 06 /r PHSUBD mm1,mm2/m64*/
    { FCML_AMT_SSSE3_SIMD, 0x0000, 0x00EC8000, { 0x0F, 0x38, 0x06 }, { FCML_OP_MODRM_R_MMX_RW, FCML_OP_MODRM_RM_MMX_OP, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* 66 0F 38 06 /r PHSUBD xmm1,xmm2/m128*/
    { FCML_AMT_SSSE3_SIMD, 0x1000, 0x00EC8000, { 0x0F, 0x38, 0x06 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PHSUBW[] = {
	/* 0F 38 05 /r1 PHSUBW mm1,mm2/m64*/
    { FCML_AMT_SSSE3_SIMD, 0x0000, 0x00EC8000, { 0x0F, 0x38, 0x05 }, { FCML_OP_MODRM_R_MMX_RW, FCML_OP_MODRM_RM_MMX_OP, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* 66 0F 38 05 /r PHSUBW xmm1,xmm2/m128*/
    { FCML_AMT_SSSE3_SIMD, 0x1000, 0x00EC8000, { 0x0F, 0x38, 0x05 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPHSUBD[] = {
	/* VEX.NDS.128.66.0F38.WIG 06 /r VPHSUBD xmm1,xmm2,xmm3/m128*/
    { FCML_AMT_AVX_SIMD, 0x10C0, 0x00EC8000, { 0x0F, 0x38, 0x06 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.NDS.256.66.0F38.WIG 06 /r VPHSUBD ymm1,ymm2,ymm3/m256*/
    { FCML_AMT_AVX2_SIMD, 0x10A0, 0x00EC8000, { 0x0F, 0x38, 0x06 }, { FCML_OP_MODRM_R_YMM_RW, FCML_OP_VEX_VVVV_YMM_REG, FCML_OP_MODRM_RM_YMM_OP_256, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPHSUBW[] = {
	/* VEX.NDS.128.66.0F38.WIG 05 /r VPHSUBW xmm1,xmm2,xmm3/m128*/
    { FCML_AMT_AVX_SIMD, 0x10C0, 0x00EC8000, { 0x0F, 0x38, 0x05 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.NDS.256.66.0F38.WIG 05 /r VPHSUBW ymm1,ymm2,ymm3/m256*/
    { FCML_AMT_AVX2_SIMD, 0x10A0, 0x00EC8000, { 0x0F, 0x38, 0x05 }, { FCML_OP_MODRM_R_YMM_RW, FCML_OP_VEX_VVVV_YMM_REG, FCML_OP_MODRM_RM_YMM_OP_256, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PHSUBSW[] = {
	/* 0F 38 07 /r PHSUBSW mm1,mm2/m64*/
    { FCML_AMT_SSSE3_SIMD, 0x0000, 0x00EC8000, { 0x0F, 0x38, 0x07 }, { FCML_OP_MODRM_R_MMX_RW, FCML_OP_MODRM_RM_MMX_OP, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* 66 0F 38 07 /r PHSUBSW xmm1,xmm2/m128*/
    { FCML_AMT_SSSE3_SIMD, 0x1000, 0x00EC8000, { 0x0F, 0x38, 0x07 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPHSUBSW[] = {
	/* VEX.NDS.128.66.0F38.WIG 07 /r VPHSUBSW xmm1,xmm2,xmm3/m128*/
    { FCML_AMT_AVX_SIMD, 0x10C0, 0x00EC8000, { 0x0F, 0x38, 0x07 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.NDS.256.66.0F38.WIG 07 /r VPHSUBSW ymm1,ymm2,ymm3/m256*/
    { FCML_AMT_AVX2_SIMD, 0x10A0, 0x00EC8000, { 0x0F, 0x38, 0x07 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_YMM_REG, FCML_OP_MODRM_RM_YMM_OP_256, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PINSRD[] = {
	/* 66 0F 3A 22 /r ib PINSRD xmm1,r/m32,int8*/
    { FCML_AMT_SSE41_SIMD, 0x1000, 0x03EC8000, { 0x0F, 0x3A, 0x22 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_OP_32, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPINSRQ[] = {
	/* VEX.NDS.128.66.0F3A.W1 22 /r ib VPINSRQ xmm1,xmm2,r64/m64,int8*/
    { FCML_AMT_AVX_SIMD, 0x10C8, 0x00EC8000, { 0x0F, 0x3A, 0x22 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_OP_64, FCML_OP_IB, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PINSRQ[] = {
	/* 66 REX.W 0F 3A 22 /r ib PINSRQ xmm1,r/m64,int8*/
    { FCML_AMT_SSE41_SIMD, 0x1008, 0x04AC8000, { 0x0F, 0x3A, 0x22 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_OP_64, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PINSRB[] = {
	/* 66 0F 3A 20 /r ib PINSRB xmm1,r32/m8,int8*/
    { FCML_AMT_SSE41_SIMD, 0x1000, 0x00EC8000, { 0x0F, 0x3A, 0x20 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_RM(FCML_REG_GPR, FCML_EOS_DWORD, FCML_EOS_BYTE | FCML_EOS_OPT, FCML_RMF_RM ), FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPINSRD[] = {
	/* VEX.NDS.128.66.0F3A.W0 22 /r ib VPINSRD xmm1,xmm2,r32/m32,int8*/
    { FCML_AMT_AVX_SIMD, 0x10D0, 0x00EC8000, { 0x0F, 0x3A, 0x22 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_OP_32, FCML_OP_IB, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPINSRB[] = {
	/* VEX.NDS.128.66.0F3A.W0 20 /r ib VPINSRB xmm1,xmm2,r32/m8,int8*/
    { FCML_AMT_AVX_SIMD, 0x10C0, 0x00EC8000, { 0x0F, 0x3A, 0x20 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_RM(FCML_REG_GPR, FCML_EOS_DWORD, FCML_EOS_BYTE | FCML_EOS_OPT, FCML_RMF_RM ), FCML_OP_IB, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PINSRW[] = {
	/* 0F C4 /r ib PINSRW mm,r32/m16,int8*/
    { FCML_AMT_SSE_SIMD, 0x0000, 0x00D88000, { 0x0F, 0xC4, 0x00 }, { FCML_OP_MODRM_R_MMX_W, FCML_OP_RM(FCML_REG_GPR, FCML_EOS_DWORD, FCML_EOS_WORD | FCML_EOS_OPT, FCML_RMF_RM ), FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* 66 0F C4 /r ib PINSRW xmm,r32/m16,int8*/
    { FCML_AMT_SSE_SIMD, 0x1000, 0x00D88000, { 0x0F, 0xC4, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_RM(FCML_REG_GPR, FCML_EOS_DWORD, FCML_EOS_WORD | FCML_EOS_OPT, FCML_RMF_RM ), FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPINSRW[] = {
	/* VEX.NDS.128.66.0F.W0 C4 /r ib VPINSRW xmm1,xmm2,r32/m16,int8*/
    { FCML_AMT_AVX_SIMD, 0x10C0, 0x00D88000, { 0x0F, 0xC4, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_RM(FCML_REG_GPR, FCML_EOS_DWORD, FCML_EOS_WORD | FCML_EOS_OPT, FCML_RMF_RM ), FCML_OP_IB, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PMADDUBSW[] = {
	/* 0F 38 04 /r PMADDUBSW mm1,mm2/m64*/
    { FCML_AMT_SSSE3_SIMD, 0x0000, 0x00EC8000, { 0x0F, 0x38, 0x04 }, { FCML_OP_MODRM_R_MMX_RW, FCML_OP_MODRM_RM_MMX_OP, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* 66 0F 38 04 /r PMADDUBSW xmm1,xmm2/m128*/
    { FCML_AMT_SSSE3_SIMD, 0x1000, 0x00EC8000, { 0x0F, 0x38, 0x04 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPMADDUBSW[] = {
	/* VEX.NDS.128.66.0F38.WIG 04 /r VPMADDUBSW xmm1,xmm2,xmm3/m128*/
    { FCML_AMT_AVX_SIMD, 0x10C0, 0x00EC8000, { 0x0F, 0x38, 0x04 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.NDS.256.66.0F38.WIG 04 /r VPMADDUBSW ymm1,ymm2,ymm3/m256*/
    { FCML_AMT_AVX2_SIMD, 0x10A0, 0x00EC8000, { 0x0F, 0x38, 0x04 }, { FCML_OP_MODRM_R_YMM_RW, FCML_OP_VEX_VVVV_YMM_REG, FCML_OP_MODRM_RM_YMM_OP_256, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PMADDWD[] = {
	/* 0F F5 /r PMADDWD mm,mm/m64*/
    { FCML_AMT_MMX_SIMD, 0x0000, 0x00D88000, { 0x0F, 0xF5, 0x00 }, { FCML_OP_MODRM_R_MMX_RW, FCML_OP_MODRM_RM_MMX_OP, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* 66 0F F5 /r PMADDWD xmm1,xmm2/m128*/
    { FCML_AMT_SSE2_SIMD, 0x1000, 0x00D88000, { 0x0F, 0xF5, 0x00 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPMADDWD[] = {
	/* VEX.NDS.128.66.0F.WIG F5 /r VPMADDWD xmm1,xmm2,xmm3/m128*/
    { FCML_AMT_AVX_SIMD, 0x10C0, 0x00D88000, { 0x0F, 0xF5, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.NDS.256.66.0F.WIG F5 /r VPMADDWD ymm1,ymm2,ymm3/m256*/
    { FCML_AMT_AVX2_SIMD, 0x10A0, 0x00D88000, { 0x0F, 0xF5, 0x00 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_YMM_REG, FCML_OP_MODRM_RM_YMM_OP_256, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PMAXSB[] = {
	/* 66 0F 38 3C /r PMAXSB xmm1,xmm2/m128*/
    { FCML_AMT_SSE41_SIMD, 0x1000, 0x00EC8000, { 0x0F, 0x38, 0x3C }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPMAXSB[] = {
	/* VEX.NDS.128.66.0F38.WIG 3C /r VPMAXSB xmm1,xmm2,xmm3/m128*/
    { FCML_AMT_AVX_SIMD, 0x10C0, 0x00EC8000, { 0x0F, 0x38, 0x3C }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.NDS.256.66.0F38.WIG 3C /r VPMAXSB ymm1,ymm2,ymm3/m256*/
    { FCML_AMT_AVX2_SIMD, 0x10A0, 0x00EC8000, { 0x0F, 0x38, 0x3C }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_YMM_REG, FCML_OP_MODRM_RM_YMM_OP_256, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PMAXSD[] = {
	/* 66 0F 38 3D /r PMAXSD xmm1,xmm2/m128*/
    { FCML_AMT_SSE41_SIMD, 0x1000, 0x00EC8000, { 0x0F, 0x38, 0x3D }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPMAXSD[] = {
	/* VEX.NDS.128.66.0F38.WIG 3D /r VPMAXSD xmm1,xmm2,xmm3/m128*/
    { FCML_AMT_AVX_SIMD, 0x10C0, 0x00EC8000, { 0x0F, 0x38, 0x3D }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.NDS.256.66.0F38.WIG 3D /r VPMAXSD ymm1,ymm2,ymm3/m256*/
    { FCML_AMT_AVX2_SIMD, 0x10A0, 0x00EC8000, { 0x0F, 0x38, 0x3D }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_YMM_REG, FCML_OP_MODRM_RM_YMM_OP_256, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PMAXSW[] = {
	/* 0F EE /r PMAXSW mm1,mm2/m64*/
    { FCML_AMT_MMX, 0x0000, 0x00D88000, { 0x0F, 0xEE, 0x00 }, { FCML_OP_MODRM_R_MMX_RW, FCML_OP_MODRM_RM_MMX_OP, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* 66 0F EE /r PMAXSW xmm1,xmm2/m128*/
    { FCML_AMT_SSE, 0x1000, 0x00D88000, { 0x0F, 0xEE, 0x00 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPMAXSW[] = {
	/* VEX.NDS.128.66.0F.WIG EE /r VPMAXSW xmm1,xmm2,xmm3/m128*/
    { FCML_AMT_AVX_SIMD, 0x10C0, 0x00D88000, { 0x0F, 0xEE, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.NDS.256.66.0F.WIG EE /r VPMAXSW ymm1,ymm2,ymm3/m256*/
    { FCML_AMT_AVX2_SIMD, 0x10A0, 0x00D88000, { 0x0F, 0xEE, 0x00 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_YMM_REG, FCML_OP_MODRM_RM_YMM_OP_256, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PMAXUB[] = {
	/* 0F DE /r PMAXUB mm1,mm2/m64*/
    { FCML_AMT_SSE_SIMD, 0x0000, 0x00D88000, { 0x0F, 0xDE, 0x00 }, { FCML_OP_MODRM_R_MMX_RW, FCML_OP_MODRM_RM_MMX_OP, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* 66 0F DE /r PMAXUB xmm1,xmm2/m128*/
    { FCML_AMT_SSE_SIMD, 0x1000, 0x00D88000, { 0x0F, 0xDE, 0x00 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPMAXUB[] = {
	/* VEX.NDS.128.66.0F.WIG DE /r VPMAXUB xmm1,xmm2,xmm3/m128*/
    { FCML_AMT_AVX_SIMD, 0x10C0, 0x00D88000, { 0x0F, 0xDE, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.NDS.256.66.0F.WIG DE /r VPMAXUB ymm1,ymm2,ymm3/m256*/
    { FCML_AMT_AVX2_SIMD, 0x10A0, 0x00D88000, { 0x0F, 0xDE, 0x00 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_YMM_REG, FCML_OP_MODRM_RM_YMM_OP_256, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PMAXUD[] = {
	/* 66 0F 38 3F /r PMAXUD xmm1, xmm2/m128*/
    { FCML_AMT_SSE41_SIMD, 0x1000, 0x00EC8000, { 0x0F, 0x38, 0x3F }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPMAXUD[] = {
	/* VEX.NDS.128.66.0F38.WIG 3F /r VPMAXUD xmm1,xmm2,xmm3/m128*/
    { FCML_AMT_AVX_SIMD, 0x10C0, 0x00EC8000, { 0x0F, 0x38, 0x3F }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.NDS.256.66.0F38.WIG 3F /r VPMAXUD ymm1,ymm2,ymm3/m256*/
    { FCML_AMT_AVX2_SIMD, 0x10A0, 0x00EC8000, { 0x0F, 0x38, 0x3F }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_YMM_REG, FCML_OP_MODRM_RM_YMM_OP_256, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PMAXUW[] = {
	/* 66 0F 38 3E /r PMAXUW xmm1,xmm2/m128*/
    { FCML_AMT_SSE41_SIMD, 0x1000, 0x00EC8000, { 0x0F, 0x38, 0x3E }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPMAXUW[] = {
	/* VEX.NDS.128.66.0F38.WIG 3E/r VPMAXUW xmm1,xmm2,xmm3/m128*/
    { FCML_AMT_AVX_SIMD, 0x10C0, 0x00EC8000, { 0x0F, 0x38, 0x3E }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.NDS.256.66.0F38.WIG 3E /r VPMAXUW ymm1,ymm2,ymm3/m256*/
    { FCML_AMT_AVX2_SIMD, 0x10A0, 0x00EC8000, { 0x0F, 0x38, 0x3E }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_YMM_OP_256, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PMINSB[] = {
	/* 66 0F 38 38 /r PMINSB xmm1,xmm2/m128*/
    { FCML_AMT_SSE41_SIMD, 0x1000, 0x00EC8000, { 0x0F, 0x38, 0x38 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPMINSB[] = {
	/* VEX.NDS.128.66.0F38.WIG 38 /r VPMINSB xmm1,xmm2,xmm3/m128*/
    { FCML_AMT_AVX_SIMD, 0x10C0, 0x00EC8000, { 0x0F, 0x38, 0x38 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.NDS.256.66.0F38.WIG 38 /r VPMINSB ymm1,ymm2,ymm3/m256*/
    { FCML_AMT_AVX2_SIMD, 0x10A0, 0x00EC8000, { 0x0F, 0x38, 0x38 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_YMM_REG, FCML_OP_MODRM_RM_YMM_OP_256, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PMINSD[] = {
	/* 66 0F 38 39 /r PMINSD xmm1, xmm2/m128*/
    { FCML_AMT_SSE41_SIMD, 0x1000, 0x00EC8000, { 0x0F, 0x38, 0x39 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPMINSD[] = {
	/* VEX.NDS.128.66.0F38.WIG 39 /r VPMINSD xmm1, xmm2, xmm3/m128*/
    { FCML_AMT_AVX_SIMD, 0x10C0, 0x00EC8000, { 0x0F, 0x38, 0x39 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.NDS.256.66.0F38.WIG 39 /r VPMINSD ymm1,ymm2,ymm3/m256*/
    { FCML_AMT_AVX2_SIMD, 0x10A0, 0x00EC8000, { 0x0F, 0x38, 0x39 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_YMM_REG, FCML_OP_MODRM_RM_YMM_OP_256, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PMINSW[] = {
	/* 0F EA /r PMINSW mm1,mm2/m64*/
    { FCML_AMT_SSE_SIMD, 0x0000, 0x00D88000, { 0x0F, 0xEA, 0x00 }, { FCML_OP_MODRM_R_MMX_RW, FCML_OP_MODRM_RM_MMX_OP, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* 66 0F EA /r PMINSW xmm1,xmm2/m128*/
    { FCML_AMT_SSE_SIMD, 0x1000, 0x00D88000, { 0x0F, 0xEA, 0x00 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPMINSW[] = {
	/* VEX.NDS.128.66.0F.WIG EA /r VPMINSW xmm1,xmm2,xmm3/m128*/
    { FCML_AMT_AVX_SIMD, 0x10C0, 0x00D88000, { 0x0F, 0xEA, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.NDS.256.66.0F.WIG EA /r VPMINSW ymm1,ymm2,ymm3/m256*/
    { FCML_AMT_AVX2_SIMD, 0x10A0, 0x00D88000, { 0x0F, 0xEA, 0x00 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_YMM_REG, FCML_OP_MODRM_RM_YMM_OP_256, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PMINUB[] = {
	/* 0F DA /r PMINUB mm1,mm2/m64*/
    { FCML_AMT_SSE_SIMD, 0x0000, 0x00D88000, { 0x0F, 0xDA, 0x00 }, { FCML_OP_MODRM_R_MMX_RW, FCML_OP_MODRM_RM_MMX_OP, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* 66 0F DA /r PMINUB xmm1,xmm2/m128*/
    { FCML_AMT_SSE_SIMD, 0x1000, 0x00D88000, { 0x0F, 0xDA, 0x00 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPMINUB[] = {
	/* VEX.NDS.128.66.0F.WIG DA /r VPMINUB xmm1,xmm2,xmm3/m128*/
    { FCML_AMT_AVX_SIMD, 0x10C0, 0x00D88000, { 0x0F, 0xDA, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.NDS.256.66.0F.WIG DA /r VPMINUB ymm1,ymm2,ymm3/m256*/
    { FCML_AMT_AVX2_SIMD, 0x10A0, 0x00D88000, { 0x0F, 0xDA, 0x00 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_YMM_REG, FCML_OP_MODRM_RM_YMM_OP_256, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PMINUW[] = {
	/* 66 0F 38 3A /r PMINUW xmm1,xmm2/m128*/
    { FCML_AMT_SSE41_SIMD, 0x1000, 0x00EC8000, { 0x0F, 0x38, 0x3A }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPMINUW[] = {
	/* VEX.NDS.128.66.0F38.WIG 3A /r VPMINUW xmm1,xmm2,xmm3/m128*/
    { FCML_AMT_AVX_SIMD, 0x10C0, 0x00EC8000, { 0x0F, 0x38, 0x3A }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.NDS.256.66.0F38.WIG 3A /r VPMINUW ymm1,ymm2,ymm3/m256*/
    { FCML_AMT_AVX_SIMD, 0x10A0, 0x00EC8000, { 0x0F, 0x38, 0x3A }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_YMM_REG, FCML_OP_MODRM_RM_YMM_OP_256, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PMINUD[] = {
	/* 66 0F 38 3B /r PMINUD xmm1,xmm2/m128*/
    { FCML_AMT_SSE41_SIMD, 0x1000, 0x00EC8000, { 0x0F, 0x38, 0x3B }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPMINUD[] = {
	/* VEX.NDS.128.66.0F38.WIG 3B /r VPMINUD xmm1,xmm2,xmm3/m128*/
    { FCML_AMT_AVX_SIMD, 0x10C0, 0x00EC8000, { 0x0F, 0x38, 0x3B }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.NDS.256.66.0F38.WIG 3B /r VPMINUD ymm1,ymm2,ymm3/m256*/
    { FCML_AMT_AVX2_SIMD, 0x10A0, 0x00EC8000, { 0x0F, 0x38, 0x3B }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_YMM_REG, FCML_OP_MODRM_RM_YMM_OP_256, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PMOVMSKB[] = {
	/* 0F D7 /r1 PMOVMSKB reg, mm*/
    { FCML_AMT_SSE_SIMD, 0x0000, 0x40D88000, { 0x0F, 0xD7, 0x00 }, { FCML_OP_R(FCML_REG_GPR, FCML_EOS_EOSA) | FCML_OA_W, FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_MWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* 66 0F D7 /r PMOVMSKB reg, xmm*/
    { FCML_AMT_SSE_SIMD, 0x1000, 0x40D88000, { 0x0F, 0xD7, 0x00 }, { FCML_OP_R(FCML_REG_GPR, FCML_EOS_EOSA) | FCML_OA_W, FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_XWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPMOVMSKB[] = {
	/* VEX.128.66.0F.WIG D7 /r VPMOVMSKB reg,xmm1*/
    { FCML_AMT_AVX_SIMD, 0x13C0, 0x40DA8000, { 0x0F, 0xD7, 0x22 }, { FCML_OP_MODRM_R_W, FCML_OP_VEX_VVVV_REG( FCML_REG_SIMD, FCML_EOS_XWORD ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.256.66.0F.WIG D7 /r VPMOVMSKB reg,ymm1*/
    { FCML_AMT_AVX2_SIMD, 0x13A0, 0x40DA8000, { 0x0F, 0xD7, 0x22 }, { FCML_OP_MODRM_R_W, FCML_OP_VEX_VVVV_REG( FCML_REG_SIMD, FCML_EOS_YWORD ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPMOVSXBQ[] = {
	/* VEX.128.66.0F38.WIG 22 /r VPMOVSXBQ xmm1,xmm2/m16*/
    { FCML_AMT_AVX_SIMD, 0x10C0, 0x00EC8000, { 0x0F, 0x38, 0x22 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_OP_16, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.256.66.0F38.WIG 22 /r VPMOVSXBQ ymm1,xmm2/m32*/
    { FCML_AMT_AVX2_SIMD, 0x10A0, 0x00EC8000, { 0x0F, 0x38, 0x22 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_MODRM_RM_XMM_OP_32, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PMOVSXBW[] = {
	/* 66 0f 38 20 /r PMOVSXBW xmm1,xmm2/m64*/
    { FCML_AMT_SSE41_SIMD, 0x1000, 0x00EC8000, { 0x0F, 0x38, 0x20 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_OP_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PMOVSXWQ[] = {
	/* 66 0f 38 24 /r PMOVSXWQ xmm1,xmm2/m32*/
    { FCML_AMT_SSE41_SIMD, 0x1000, 0x00EC8000, { 0x0F, 0x38, 0x24 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_OP_32, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPMOVSXWQ[] = {
	/* VEX.128.66.0F38.WIG 24 /r VPMOVSXWQ xmm1,xmm2/m32*/
    { FCML_AMT_AVX_SIMD, 0x10C0, 0x00EC8000, { 0x0F, 0x38, 0x24 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_OP_32, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PMOVSXWD[] = {
	/* 66 0f 38 23 /r PMOVSXWD xmm1,xmm2/m64*/
    { FCML_AMT_SSE41_SIMD, 0x1000, 0x00EC8000, { 0x0F, 0x38, 0x23 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_OP_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PMOVSXBD[] = {
	/* 66 0f 38 21 /r PMOVSXBD xmm1,xmm2/m32*/
    { FCML_AMT_SSE41_SIMD, 0x1000, 0x00EC8000, { 0x0F, 0x38, 0x21 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_OP_32, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPMOVSXDQ[] = {
	/* VEX.128.66.0F38.WIG 25 /r VPMOVSXDQ xmm1,xmm2/m64*/
    { FCML_AMT_AVX_SIMD, 0x10C0, 0x00EC8000, { 0x0F, 0x38, 0x25 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_OP_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPMOVSXWD[] = {
	/* VEX.128.66.0F38.WIG 23 /r VPMOVSXWD xmm1,xmm2/m64*/
    { FCML_AMT_AVX_SIMD, 0x10C0, 0x00EC8000, { 0x0F, 0x38, 0x23 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_OP_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PMOVSXBQ[] = {
	/* 66 0f 38 22 /r PMOVSXBQ xmm1,xmm2/m16*/
    { FCML_AMT_SSE41_SIMD, 0x1000, 0x00EC8000, { 0x0F, 0x38, 0x22 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_OP_16, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPMOVSXBW[] = {
	/* VEX.128.66.0F38.WIG 20 /r VPMOVSXBW xmm1,xmm2/m64*/
    { FCML_AMT_AVX_SIMD, 0x10C0, 0x00EC8000, { 0x0F, 0x38, 0x20 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_OP_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.256.66.0F38.WIG 20 /r VPMOVSXBW ymm1,xmm2/m128*/
    { FCML_AMT_AVX2_SIMD, 0x10A0, 0x00EC8000, { 0x0F, 0x38, 0x20 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PMOVSXDQ[] = {
	/* 66 0f 38 25 /r PMOVSXDQ xmm1,xmm2/m64*/
    { FCML_AMT_SSE41_SIMD, 0x1000, 0x00EC8000, { 0x0F, 0x38, 0x25 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_OP_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPMOVSXBD[] = {
	/* VEX.128.66.0F38.WIG 21 /r VPMOVSXBD xmm1,xmm2/m32*/
    { FCML_AMT_AVX_SIMD, 0x10C0, 0x00EC8000, { 0x0F, 0x38, 0x21 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_OP_32, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.256.66.0F38.WIG 21 /r VPMOVSXBD ymm1,xmm2/m64*/
    { FCML_AMT_AVX2_SIMD, 0x10A0, 0x00EC8000, { 0x0F, 0x38, 0x21 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_MODRM_RM_XMM_OP_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PMOVZXWD[] = {
	/* 66 0f 38 33 /r PMOVZXWD xmm1,xmm2/m64*/
    { FCML_AMT_SSE41_SIMD, 0x1000, 0x00EC8000, { 0x0F, 0x38, 0x33 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_OP_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PMOVZXDQ[] = {
	/* 66 0f 38 35 /r PMOVZXDQ xmm1,xmm2/m64*/
    { FCML_AMT_SSE41_SIMD, 0x1000, 0x00EC8000, { 0x0F, 0x38, 0x35 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_OP_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPMOVZXDQ[] = {
	/* VEX.128.66.0F38.WIG 35 /r VPMOVZXDQ xmm1,xmm2/m64*/
    { FCML_AMT_AVX_SIMD, 0x10C0, 0x00EC8000, { 0x0F, 0x38, 0x35 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_OP_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PMOVZXWQ[] = {
	/* 66 0f 38 34 /r PMOVZXWQ xmm1,xmm2/m32*/
    { FCML_AMT_SSE41_SIMD, 0x1000, 0x00EC8000, { 0x0F, 0x38, 0x34 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_OP_32, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPMOVZXBQ[] = {
	/* VEX.128.66.0F38.WIG 32 /r VPMOVZXBQ xmm1,xmm2/m16*/
    { FCML_AMT_AVX_SIMD, 0x10C0, 0x00EC8000, { 0x0F, 0x38, 0x32 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_OP_16, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.256.66.0F38.WIG 32 /r VPMOVZXBQ ymm1,xmm2/m32*/
    { FCML_AMT_AVX2_SIMD, 0x10A0, 0x00EC8000, { 0x0F, 0x38, 0x32 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_MODRM_RM_XMM_OP_32, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PMOVZXBQ[] = {
	/* 66 0f 38 32 /r PMOVZXBQ xmm1,xmm2/m16*/
    { FCML_AMT_SSE41_SIMD, 0x1000, 0x00EC8000, { 0x0F, 0x38, 0x32 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_OP_16, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPMOVZXWD[] = {
	/* VEX.128.66.0F38.WIG 33 /r VPMOVZXWD xmm1,xmm2/m64*/
    { FCML_AMT_AVX_SIMD, 0x10C0, 0x00EC8000, { 0x0F, 0x38, 0x33 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_OP_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.256.66.0F38.WIG 33 /r VPMOVZXWD ymm1,xmm2/m128*/
    { FCML_AMT_AVX2_SIMD, 0x10A0, 0x00EC8000, { 0x0F, 0x38, 0x33 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPMOVZXBD[] = {
	/* VEX.128.66.0F38.WIG 31 /r VPMOVZXBD xmm1,xmm2/m32*/
    { FCML_AMT_AVX_SIMD, 0x10C0, 0x00EC8000, { 0x0F, 0x38, 0x31 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_OP_32, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.256.66.0F38.WIG 31FCML_AMT_AVX_SIMD/r VPMOVZXBD ymm1,xmm2/m64*/
    { FCML_AMT_AVX2_SIMD, 0x10A0, 0x00EC8000, { 0x0F, 0x38, 0x31 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_MODRM_RM_XMM_OP_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPMOVZXWQ[] = {
	/* VEX.128.66.0F38.WIG 34 /r VPMOVZXWQ xmm1,xmm2/m32*/
    { FCML_AMT_AVX_SIMD, 0x10C0, 0x00EC8000, { 0x0F, 0x38, 0x34 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_OP_32, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PMOVZXBD[] = {
	/* 66 0f 38 31 /r PMOVZXBD xmm1,xmm2/m32*/
    { FCML_AMT_SSE41_SIMD, 0x1000, 0x00EC8000, { 0x0F, 0x38, 0x31 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_OP_32, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPMOVZXBW[] = {
	/* VEX.128.66.0F38.WIG 30 /r VPMOVZXBW xmm1,xmm2/m64*/
    { FCML_AMT_AVX_SIMD, 0x10C0, 0x00EC8000, { 0x0F, 0x38, 0x30 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_OP_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.256.66.0F38.WIG 30 /r VPMOVZXBW ymm1,xmm2/m128*/
    { FCML_AMT_AVX_SIMD, 0x10A0, 0x00EC8000, { 0x0F, 0x38, 0x30 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PMOVZXBW[] = {
	/* 66 0f 38 30 /r PMOVZXBW xmm1,xmm2/m64*/
    { FCML_AMT_SSE41_SIMD, 0x1000, 0x00EC8000, { 0x0F, 0x38, 0x30 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_OP_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PMULDQ[] = {
	/* 66 0F 38 28 /r PMULDQ xmm1,xmm2/m128*/
    { FCML_AMT_SSE41_SIMD, 0x1000, 0x00EC8000, { 0x0F, 0x38, 0x28 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPMULDQ[] = {
	/* VEX.NDS.128.66.0F38.WIG 28 /r VPMULDQ xmm1,xmm2,xmm3/m128*/
    { FCML_AMT_AVX_SIMD, 0x10C0, 0x00EC8000, { 0x0F, 0x38, 0x28 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.NDS.256.66.0F38.WIG 28 /r VPMULDQ ymm1,ymm2,ymm3/m256*/
    { FCML_AMT_AVX2_SIMD, 0x10A0, 0x00EC8000, { 0x0F, 0x38, 0x28 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_YMM_REG, FCML_OP_MODRM_RM_YMM_OP_256, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PMULHRSW[] = {
	/* 0F 38 0B /r PMULHRSW mm1,mm2/m64*/
    { FCML_AMT_SSSE3_SIMD, 0x0000, 0x00EC8000, { 0x0F, 0x38, 0x0B }, { FCML_OP_MODRM_R_MMX_RW, FCML_OP_MODRM_RM_MMX_OP, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* 66 0F 38 0B /r PMULHRSW xmm1,xmm2/m128*/
    { FCML_AMT_SSSE3_SIMD, 0x1000, 0x00EC8000, { 0x0F, 0x38, 0x0B }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPMULHRSW[] = {
	/* VEX.NDS.128.66.0F38.WIG 0B /r VPMULHRSW xmm1,xmm2,xmm3/m128*/
    { FCML_AMT_AVX_SIMD, 0x10C0, 0x00EC8000, { 0x0F, 0x38, 0x0B }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.NDS.256.66.0F38.WIG 0B /r VPMULHRSW ymm1,ymm2,ymm3/m256*/
    { FCML_AMT_AVX2_SIMD, 0x10A0, 0x00EC8000, { 0x0F, 0x38, 0x0B }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_YMM_REG, FCML_OP_MODRM_RM_YMM_OP_256, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPMULHUW[] = {
	/* VEX.NDS.128.66.0F.WIG E4 /r VPMULHUW xmm1,xmm2,xmm3/m128*/
    { FCML_AMT_AVX_SIMD, 0x10C0, 0x00D88000, { 0x0F, 0xE4, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.NDS.256.66.0F.WIG E4 /r VPMULHUW ymm1,ymm2,ymm3/m256*/
    { FCML_AMT_AVX2_SIMD, 0x10A0, 0x00D88000, { 0x0F, 0xE4, 0x00 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_YMM_REG, FCML_OP_MODRM_RM_YMM_OP_256, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PMULHUW[] = {
	/* 0F E4 /r PMULHUW mm1,mm2/m64*/
    { FCML_AMT_SSE_SIMD, 0x0000, 0x00D88000, { 0x0F, 0xE4, 0x00 }, { FCML_OP_MODRM_R_MMX_RW, FCML_OP_MODRM_RM_MMX_OP, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* 66 0F E4 /r PMULHUW xmm1,xmm2/m128*/
    { FCML_AMT_SSE_SIMD, 0x1000, 0x00D88000, { 0x0F, 0xE4, 0x00 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PMULHW[] = {
	/* 0F E5 /r PMULHW mm,mm/m64*/
    { FCML_AMT_MMX_SIMD, 0x0000, 0x00D88000, { 0x0F, 0xE5, 0x00 }, { FCML_OP_MODRM_R_MMX_RW, FCML_OP_MODRM_RM_MMX_OP, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* 66 0F E5 /r PMULHW xmm1,xmm2/m128*/
    { FCML_AMT_SSE2_SIMD, 0x1000, 0x00D88000, { 0x0F, 0xE5, 0x00 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPMULHW[] = {
	/* VEX.NDS.128.66.0F.WIG E5 /r VPMULHW xmm1,xmm2,xmm3/m128*/
    { FCML_AMT_AVX_SIMD, 0x10C0, 0x00D88000, { 0x0F, 0xE5, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.NDS.256.66.0F.WIG E5 /r VPMULHW ymm1,ymm2,ymm3/m256*/
    { FCML_AMT_AVX2_SIMD, 0x10A0, 0x00D88000, { 0x0F, 0xE5, 0x00 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_YMM_REG, FCML_OP_MODRM_RM_YMM_OP_256, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PMULUDQ[] = {
	/* 0F F4 /r1 PMULUDQ mm1,mm2/m64*/
    { FCML_AMT_SSE2_SIMD, 0x0000, 0x00D88000, { 0x0F, 0xF4, 0x00 }, { FCML_OP_MODRM_R_MMX_RW, FCML_OP_MODRM_RM_MMX_OP, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* 66 0F F4 /r PMULUDQ xmm1,xmm2/m128*/
    { FCML_AMT_SSE2_SIMD, 0x1000, 0x00D88000, { 0x0F, 0xF4, 0x00 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPMULUDQ[] = {
	/* VEX.NDS.128.66.0F.WIG F4 /r VPMULUDQ xmm1,xmm2,xmm3/m128*/
    { FCML_AMT_AVX_SIMD, 0x10C0, 0x00D88000, { 0x0F, 0xF4, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.NDS.256.66.0F.WIG F4 /r VPMULUDQ ymm1,ymm2,ymm3/m256*/
    { FCML_AMT_AVX2_SIMD, 0x10A0, 0x00D88000, { 0x0F, 0xF4, 0x00 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_YMM_REG, FCML_OP_MODRM_RM_YMM_OP_256, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PMULLW[] = {
	/* 0F D5 /r PMULLW mm,mm/m64*/
    { FCML_AMT_MMX_SIMD, 0x0000, 0x00D88000, { 0x0F, 0xD5, 0x00 }, { FCML_OP_MODRM_R_MMX_RW, FCML_OP_MODRM_RM_MMX_OP, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* 66 0F D5 /r PMULLW xmm1,xmm2/m128*/
    { FCML_AMT_SSE2_SIMD, 0x1000, 0x00D88000, { 0x0F, 0xD5, 0x00 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPMULLW[] = {
	/* VEX.NDS.128.66.0F.WIG D5 /r VPMULLW xmm1,xmm2,xmm3/m128*/
    { FCML_AMT_AVX_SIMD, 0x10C0, 0x00D88000, { 0x0F, 0xD5, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.NDS.256.66.0F.WIG D5 /r VPMULLW ymm1,ymm2,ymm3/m256*/
    { FCML_AMT_AVX2_SIMD, 0x10A0, 0x00D88000, { 0x0F, 0xD5, 0x00 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_YMM_REG, FCML_OP_MODRM_RM_YMM_OP_256, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PMULLD[] = {
	/* 66 0F 38 40 /r PMULLD xmm1,xmm2/m128*/
    { FCML_AMT_SSE41_SIMD, 0x1000, 0x00EC8000, { 0x0F, 0x38, 0x40 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPMULLD[] = {
	/* VEX.NDS.128.66.0F38.WIG 40 /r VPMULLD xmm1,xmm2,xmm3/m128*/
    { FCML_AMT_AVX_SIMD, 0x10C0, 0x00EC8000, { 0x0F, 0x38, 0x40 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.NDS.256.66.0F38.WIG 40 /r VPMULLD ymm1,ymm2,ymm3/m256*/
    { FCML_AMT_AVX_SIMD, 0x10A0, 0x00EC8000, { 0x0F, 0x38, 0x40 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_YMM_REG, FCML_OP_MODRM_RM_YMM_OP_256, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_POP[] = {
	/* 8F /0 POP r/m16 M Valid Valid Pop top of stack into m16; increment stack pointer.*/
	/* 8F /0 POP r/m32 M N.E. Valid Pop top of stack into m32; increment stack pointer.*/
	/* 8F /0 POP r/m64 M Valid N.E. Pop top of stack into m64; increment stack pointer. Cannot encode 32-bit operand size.*/
    { FCML_AMT_GPI, 0x0000, 0x00C58080, { 0x8F, 0x00, 0x00 }, { FCML_OP_MODRM_RM_W, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RMO },
	/* 58+ rw POP r16 O Valid Valid Pop top of stack into r16; increment stack pointer.*/
	/* 58+ rd POP r32 O N.E. Valid Pop top of stack into r32; increment stack pointer.*/
	/* 58+ rd POP r64 O Valid N.E. Pop top of stack into r64; increment stack pointer. Cannot encode 32-bit operand size.*/
    { FCML_AMT_GPI, 0x0000, 0x00C40081, { 0x58, 0x00, 0x00 }, { FCML_OP_OPCODE_REG( FCML_REG_GPR, FCML_EOS_EOSA) | FCML_OA_W, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RO },
	/* 1F POP DS NP Invalid Valid Pop top of stack into DS; increment stack pointer.*/
	/* 07 POP ES NP Invalid Valid Pop top of stack into ES; increment stack pointer.*/
	/* 17 POP SS NP Invalid Valid Pop top of stack into SS; increment stack pointer.*/
    { FCML_AMT_GPI, 0x0000, 0x00440000, { 0x1F, 0x00, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_SEG, FCML_REG_DS, FCML_EOS_UNDEFINED ) | FCML_OA_W, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_SRO },
    { FCML_AMT_GPI, 0x0000, 0x00440000, { 0x07, 0x00, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_SEG, FCML_REG_ES, FCML_EOS_UNDEFINED ) | FCML_OA_W, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_SRO },
    { FCML_AMT_GPI, 0x0000, 0x00440000, { 0x17, 0x00, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_SEG, FCML_REG_SS, FCML_EOS_UNDEFINED ) | FCML_OA_W, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_SRO },
	/* 0F A1 POP FS NP Valid Valid Pop top of stack into FS; increment stack pointer by 16 bits.*/
	/* 0F A1 POP FS NP N.E. Valid Pop top of stack into FS; increment stack pointer by 32 bits.*/
	/* 0F A1 POP FS NP Valid N.E. Pop top of stack into FS; increment stack pointer by 64 bits.*/
    { FCML_AMT_GPI, 0x0000, 0x00D80080, { 0x0F, 0xA1, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_SEG, FCML_REG_FS, FCML_EOS_UNDEFINED ) | FCML_OA_W, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_SR_FSGSO },
	/* 0F A9 POP GS NP Valid Valid Pop top of stack into GS; increment stack pointer by 16 bits.*/
	/* 0F A9 POP GS NP N.E. Valid Pop top of stack into GS; increment stack pointer by 32 bits.*/
	/* 0F A9 POP GS NP Valid N.E. Pop top of stack into GS; increment stack pointer by 64 bits.*/
    { FCML_AMT_GPI, 0x0000, 0x00D80080, { 0x0F, 0xA9, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_SEG, FCML_REG_GS, FCML_EOS_UNDEFINED ) | FCML_OA_W, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_SR_FSGSO }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_POPA[] = {
	/* 61 POPA NP Invalid Valid Pop DI, SI, BP, BX, DX, CX, and AX.*/
    { FCML_AMT_GPI, 0x0000, 0x01440000, { 0x61, 0x00, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_POPAD[] = {
	/* 61 POPAD NP Invalid Valid Pop EDI, ESI, EBP, EBX, EDX, ECX, and EAX.*/
    { FCML_AMT_GPI, 0x0000, 0x02440000, { 0x61, 0x00, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_POPCNT[] = {
	/* F3 0F B8 /r POPCNT r16, r/m16 RM Valid Valid POPCNT on r/m16*/
	/* F3 0F B8 /r POPCNT r32, r/m32 RM Valid Valid POPCNT on r/m32*/
	/* F3 REX.W 0F B8 /r POPCNT r64, r/m64 RM Valid N.E. POPCNT on r/m64*/
    { FCML_AMT_POPCNT, 0x4000, 0x00D88000, { 0x0F, 0xB8, 0x00 }, { FCML_OP_MODRM_R_W, FCML_OP_MODRM_RM_OP, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_POPF[] = {
	/* 9D POPF NP Valid Valid Pop top of stack into lower 16 bits of EFLAGS.*/
    { FCML_AMT_GPI, 0x0000, 0x01C40000, { 0x9D, 0x00, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_POPFQ[] = {
	/* REX.W + 9D POPFQ NP Valid N.E. Pop top of stack and zero-extend into RFLAGS.*/
    { FCML_AMT_GPI, 0x0000, 0x04840000, { 0x9D, 0x00, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_POPFD[] = {
	/* 9D POPFD NP N.E. Valid Pop top of stack into EFLAGS.*/
    { FCML_AMT_GPI, 0x0000, 0x02440000, { 0x9D, 0x00, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_POR[] = {
	/* 0F EB /r1 POR mm,mm/m64*/
    { FCML_AMT_MMX_SIMD, 0x0000, 0x00D88000, { 0x0F, 0xEB, 0x00 }, { FCML_OP_MODRM_R_MMX_RW, FCML_OP_MODRM_RM_MMX_OP, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* 66 0F EB /r POR xmm1,xmm2/m128*/
    { FCML_AMT_SSE2_SIMD, 0x1000, 0x00D88000, { 0x0F, 0xEB, 0x00 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPOR[] = {
	/* VEX.NDS.128.66.0F.WIG EB /r VPOR xmm1,xmm2,xmm3/m128*/
    { FCML_AMT_AVX_SIMD, 0x10C0, 0x00D88000, { 0x0F, 0xEB, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.NDS.256.66.0F.WIG EB /r VPOR ymm1,ymm2,ymm3/m256*/
    { FCML_AMT_AVX2_SIMD, 0x10A0, 0x00D88000, { 0x0F, 0xEB, 0x00 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_YMM_REG, FCML_OP_MODRM_RM_YMM_OP_256, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PREFETCHT2[] = {
	/* 0F 18 /3 PREFETCHT2 m8 M Valid Valid Move data from m8 closer to the processor using T2 hint.*/
    { FCML_AMT_SSE, 0x0000, 0x00D99800, { 0x0F, 0x18, 0x00 }, { FCML_OP_MODRM_M_OP_8, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PREFETCHT1[] = {
	/* 0F 18 /2 PREFETCHT1 m8 M Valid Valid Move data from m8 closer to the processor using T1 hint.*/
    { FCML_AMT_SSE, 0x0000, 0x00D99000, { 0x0F, 0x18, 0x00 }, { FCML_OP_MODRM_M_OP_8, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PREFETCHNTA[] = {
	/* 0F 18 /0 PREFETCHNTA m8 M Valid Valid Move data from m8 closer to the processor using NTA hint.*/
    { FCML_AMT_SSE, 0x0000, 0x00D98000, { 0x0F, 0x18, 0x00 }, { FCML_OP_MODRM_M_OP_8, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PREFETCHT0[] = {
	/* 0F 18 /1 PREFETCHT0 m8 M Valid Valid Move data from m8 closer to the processor using T0 hint.*/
    { FCML_AMT_SSE, 0x0000, 0x00D98800, { 0x0F, 0x18, 0x00 }, { FCML_OP_MODRM_M_OP_8, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PSADBW[] = {
	/* 0F F6 /r PSADBW mm1,mm2/m64*/
    { FCML_AMT_SSE_SIMD, 0x0000, 0x00D88000, { 0x0F, 0xF6, 0x00 }, { FCML_OP_MODRM_R_MMX_RW, FCML_OP_MODRM_RM_MMX_OP, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* 66 0F F6 /r PSADBW xmm1,xmm2/m128*/
    { FCML_AMT_SSE_SIMD, 0x1000, 0x00D88000, { 0x0F, 0xF6, 0x00 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPSADBW[] = {
	/* VEX.NDS.128.66.0F.WIG F6 /r VPSADBW xmm1,xmm2,xmm3/m128*/
    { FCML_AMT_AVX_SIMD, 0x10C0, 0x00D88000, { 0x0F, 0xF6, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.NDS.256.66.0F.WIG F6 /r VPSADBW ymm1,ymm2,ymm3/m256*/
    { FCML_AMT_AVX2_SIMD, 0x10A0, 0x00D88000, { 0x0F, 0xF6, 0x00 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_YMM_REG, FCML_OP_MODRM_RM_YMM_OP_256, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PSHUFB[] = {
	/* 0F 38 00 /r PSHUFB mm1,mm2/m64*/
    { FCML_AMT_SSSE3_SIMD, 0x0000, 0x00EC8000, { 0x0F, 0x38, 0x00 }, { FCML_OP_MODRM_R_MMX_RW, FCML_OP_MODRM_RM_MMX_OP, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* 66 0F 38 00 /r PSHUFB xmm1,xmm2/m128*/
    { FCML_AMT_SSSE3_SIMD, 0x1000, 0x00EC8000, { 0x0F, 0x38, 0x00 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPSHUFB[] = {
	/* VEX.NDS.128.66.0F38.WIG 00 /r VPSHUFB xmm1,xmm2,xmm3/m128*/
    { FCML_AMT_AVX_SIMD, 0x10C0, 0x00EC8000, { 0x0F, 0x38, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.NDS.256.66.0F38.WIG 00 /r VPSHUFB ymm1,ymm2,ymm3/m256*/
    { FCML_AMT_AVX2_SIMD, 0x10A0, 0x00EC8000, { 0x0F, 0x38, 0x00 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_YMM_REG, FCML_OP_MODRM_RM_YMM_OP_256, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PSHUFD[] = {
	/* 66 0F 70 /r ib PSHUFD xmm1,xmm2/m128,int8*/
    { FCML_AMT_SSE2_SIMD, 0x1000, 0x00D88000, { 0x0F, 0x70, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_OP_128, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPSHUFD[] = {
	/* VEX.128.66.0F.WIG 70 /r ib VPSHUFD xmm1,xmm2/m128,int8*/
    { FCML_AMT_AVX_SIMD, 0x10C0, 0x00D88000, { 0x0F, 0x70, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_OP_128, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.256.66.0F.WIG 70 /r ib VPSHUFD ymm1,ymm2/m256,int8*/
    { FCML_AMT_AVX2_SIMD, 0x10A0, 0x00D88000, { 0x0F, 0x70, 0x00 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_MODRM_RM_YMM_OP_256, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PSHUFHW[] = {
	/* F3 0F 70 /r ib PSHUFHW xmm1,xmm2/m128,int8*/
    { FCML_AMT_SSE2_SIMD, 0x4000, 0x00D88000, { 0x0F, 0x70, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_OP_128, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPSHUFHW[] = {
	/* VEX.128.F3.0F.WIG 70 /r ib VPSHUFHW xmm1,xmm2/m128,int8*/
    { FCML_AMT_AVX_SIMD, 0x40C0, 0x00D88000, { 0x0F, 0x70, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_OP_128, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.256.F3.0F.WIG 70 /r ib VPSHUFHW ymm1,ymm2/m256,int8*/
    { FCML_AMT_AVX2_SIMD, 0x40A0, 0x00D88000, { 0x0F, 0x70, 0x00 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_MODRM_RM_YMM_OP_256, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PSHUFLW[] = {
	/* F2 0F 70 /r ib PSHUFLW xmm1,xmm2/m128,int8*/
    { FCML_AMT_SSE2_SIMD, 0x2000, 0x00D88000, { 0x0F, 0x70, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_OP_128, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPSHUFLW[] = {
	/* VEX.128.F2.0F.WIG 70 /r ib VPSHUFLW xmm1,xmm2/m128,int8*/
    { FCML_AMT_AVX_SIMD, 0x20C0, 0x00D88000, { 0x0F, 0x70, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_OP_128, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.256.F2.0F.WIG 70 /r ib VPSHUFLW ymm1,ymm2/m256,int8*/
    { FCML_AMT_AVX2_SIMD, 0x20A0, 0x00D88000, { 0x0F, 0x70, 0x00 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_MODRM_RM_YMM_OP_256, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PSHUFW[] = {
	/* 0F 70 /r ib PSHUFW mm1,mm2/m64,int8*/
    { FCML_AMT_SSE_SIMD, 0x0000, 0x00D88000, { 0x0F, 0x70, 0x00 }, { FCML_OP_MODRM_R_MMX_W, FCML_OP_MODRM_RM_MMX_OP, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPSIGNB[] = {
	/* VEX.NDS.128.66.0F38.WIG 08 /r VPSIGNB xmm1,xmm2,xmm3/m128*/
    { FCML_AMT_AVX_SIMD, 0x10C0, 0x00EC8000, { 0x0F, 0x38, 0x08 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.NDS.256.66.0F38.WIG 08 /r VPSIGNB ymm1,ymm2,ymm3/m256*/
    { FCML_AMT_AVX2_SIMD, 0x10A0, 0x00EC8000, { 0x0F, 0x38, 0x08 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_YMM_REG, FCML_OP_MODRM_RM_YMM_OP_256, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPSIGND[] = {
	/* VEX.NDS.128.66.0F38.WIG 0A /r VPSIGND xmm1,xmm2,xmm3/m128*/
    { FCML_AMT_AVX_SIMD, 0x10C0, 0x00EC8000, { 0x0F, 0x38, 0x0A }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.NDS.256.66.0F38.WIG 0A /r VPSIGND ymm1,ymm2,ymm3/m256*/
    { FCML_AMT_AVX2_SIMD, 0x10A0, 0x00EC8000, { 0x0F, 0x38, 0x0A }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_YMM_REG, FCML_OP_MODRM_RM_YMM_OP_256, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PSIGNW[] = {
	/* 0F 38 09 /r PSIGNW mm1,mm2/m64*/
    { FCML_AMT_SSSE3_SIMD, 0x0000, 0x00EC8000, { 0x0F, 0x38, 0x09 }, { FCML_OP_MODRM_R_MMX_RW, FCML_OP_MODRM_RM_MMX_OP, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* 66 0F 38 09 /r PSIGNW xmm1,xmm2/m128*/
    { FCML_AMT_SSSE3_SIMD, 0x1000, 0x00EC8000, { 0x0F, 0x38, 0x09 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PSIGNB[] = {
	/* 0F 38 08 /r PSIGNB mm1,mm2/m64*/
    { FCML_AMT_SSSE3_SIMD, 0x0000, 0x00EC8000, { 0x0F, 0x38, 0x08 }, { FCML_OP_MODRM_R_MMX_RW, FCML_OP_MODRM_RM_MMX_OP, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* 66 0F 38 08 /r PSIGNB xmm1,xmm2/m128*/
    { FCML_AMT_SSSE3_SIMD, 0x1000, 0x00EC8000, { 0x0F, 0x38, 0x08 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPSIGNW[] = {
	/* VEX.NDS.128.66.0F38.WIG 09 /r VPSIGNW xmm1,xmm2,xmm3/m128*/
    { FCML_AMT_AVX_SIMD, 0x10C0, 0x00EC8000, { 0x0F, 0x38, 0x09 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.NDS.256.66.0F38.WIG 09 /r VPSIGNW ymm1,ymm2,ymm3/m256*/
    { FCML_AMT_AVX2_SIMD, 0x10A0, 0x00EC8000, { 0x0F, 0x38, 0x09 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_YMM_REG, FCML_OP_MODRM_RM_YMM_OP_256, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PSIGND[] = {
	/* 0F 38 0A /r PSIGND mm1,mm2/m64*/
    { FCML_AMT_SSSE3_SIMD, 0x0000, 0x00EC8000, { 0x0F, 0x38, 0x0A }, { FCML_OP_MODRM_R_MMX_RW, FCML_OP_MODRM_RM_MMX_OP, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* 66 0F 38 0A /r PSIGND xmm1,xmm2/m128*/
    { FCML_AMT_SSSE3_SIMD, 0x1000, 0x00EC8000, { 0x0F, 0x38, 0x0A }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PSLLDQ[] = {
	/* 66 0F 73 /7 ib PSLLDQ xmm1,int8*/
    { FCML_AMT_SSE2_SIMD, 0x1000, 0x00DBB800, { 0x0F, 0x73, 0x00 }, { FCML_OP_RM( FCML_REG_SIMD, FCML_EOS_XWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ) | FCML_OA_RW, FCML_OP_IB, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPSLLDQ[] = {
	/* VEX.NDD.128.66.0F.WIG 73 /7 ib VPSLLDQ xmm1,xmm2,int8*/
    { FCML_AMT_AVX_SIMD, 0x10C0, 0x00DBB800, { 0x0F, 0x73, 0x00 }, { FCML_OP_VEX_VVVV_SIMD_REG | FCML_OA_W, FCML_OP_RM( FCML_REG_SIMD, FCML_EOS_XWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.NDD.256.66.0F.WIG 73 /7 ib VPSLLDQ ymm1,ymm2,int8*/
    { FCML_AMT_AVX2_SIMD, 0x10A0, 0x00DBB800, { 0x0F, 0x73, 0x00 }, { FCML_OP_VEX_VVVV_SIMD_REG | FCML_OA_W, FCML_OP_RM( FCML_REG_SIMD, FCML_EOS_YWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PSLLW[] = {
    /* 0F F1 /r1 PSLLW mm,mm/m64*/
    { FCML_AMT_MMX_SIMD, 0x0000, 0x00D88000, { 0x0F, 0xF1, 0x00 }, { FCML_OP_MODRM_R_MMX_RW, FCML_OP_MODRM_RM_MMX_OP, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
    /* 66 0F F1 /r PSLLW xmm1,xmm2/m128*/
    { FCML_AMT_SSE2_SIMD, 0x1000, 0x00D88000, { 0x0F, 0xF1, 0x00 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
    /* 0F 71 /6 ib PSLLW mm,int8*/
    { FCML_AMT_MMX_SIMD, 0x0000, 0x00DBB000, { 0x0F, 0x71, 0x00 }, { FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_QWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ) | FCML_OA_RW, FCML_OP_IB, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
    /* 66 0F 71 /6 ib PSLLW xmm1,int8*/
    { FCML_AMT_SSE2_SIMD, 0x1000, 0x00DBB000, { 0x0F, 0x71, 0x00 }, { FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_OWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ) | FCML_OA_RW, FCML_OP_IB, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PSLLD[] = {
	/* 0F F2 /r1 PSLLD mm,mm/m64*/
    { FCML_AMT_MMX_SIMD, 0x0000, 0x00D88000, { 0x0F, 0xF2, 0x00 }, { FCML_OP_MODRM_R_MMX_RW, FCML_OP_MODRM_RM_MMX_OP, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* 66 0F F2 /r PSLLD xmm1,xmm2/m128*/
    { FCML_AMT_SSE2_SIMD, 0x1000, 0x00D88000, { 0x0F, 0xF2, 0x00 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* 0F 72 /6 ib1 PSLLD mm,int8*/
    { FCML_AMT_MMX_SIMD, 0x0000, 0x00DBB000, { 0x0F, 0x72, 0x00 }, { FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_MWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ) | FCML_OA_RW, FCML_OP_IB, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* 66 0F 72 /6 ib PSLLD xmm1,int8*/
    { FCML_AMT_SSE2_SIMD, 0x1000, 0x00DBB000, { 0x0F, 0x72, 0x00 }, { FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_XWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ) | FCML_OA_RW, FCML_OP_IB, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PSLLQ[] = {
    /* 0F F3 /r1 PSLLQ mm,mm/m64*/
    { FCML_AMT_MMX_SIMD, 0x0000, 0x00D88000, { 0x0F, 0xF3, 0x00 }, { FCML_OP_MODRM_R_MMX_RW, FCML_OP_MODRM_RM_MMX_OP, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
    /* 66 0F F3 /r PSLLQ xmm1,xmm2/m128*/
    { FCML_AMT_SSE2_SIMD, 0x1000, 0x00D88000, { 0x0F, 0xF3, 0x00 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
    /* 0F 73 /6 ib1 PSLLQ mm,int8*/
    { FCML_AMT_MMX_SIMD, 0x0000, 0x00DBB000, { 0x0F, 0x73, 0x00 }, { FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_MWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ) | FCML_OA_RW, FCML_OP_IB, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
    /* 66 0F 73 /6 ib PSLLQ xmm1,int8*/
    { FCML_AMT_SSE2_SIMD, 0x1000, 0x00DBB000, { 0x0F, 0x73, 0x00 }, { FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_XWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ) | FCML_OA_RW, FCML_OP_IB, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPSLLW[] = {
	/* VEX.NDS.128.66.0F.WIG F1 /r VPSLLW xmm1,xmm2,xmm3/m128*/
	/* VEX.NDS.256.66.0F.WIG F1 /r VPSLLW ymm1, ymm2, xmm3/m128*/
    { FCML_AMT_AVX_SIMD, 0x1080, 0x00D88000, { 0x0F, 0xF1, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.NDD.128.66.0F.WIG 71 /6 ib VPSLLW xmm1,xmm2,int8*/
	/* VEX.NDD.256.66.0F.WIG 71 /6 ib VPSLLW ymm1, ymm2, int8*/
    { FCML_AMT_AVX_SIMD, 0x1080, 0x00DBB000, { 0x0F, 0x71, 0x00 }, { FCML_OP_VEX_VVVV_SIMD_REG | FCML_OA_W, FCML_OP_RM( FCML_REG_SIMD, FCML_EOS_L, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPSLLD[] = {
    /* VEX.NDS.128.66.0F.WIG F2 /r VPSLLD xmm1,xmm2,xmm3/m128*/
    /* VEX.NDS.256.66.0F.WIG F2 /r VPSLLD ymm1, ymm2, xmm3/m128*/
    { FCML_AMT_AVX_SIMD, 0x1080, 0x00D88000, { 0x0F, 0xF2, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
    /* VEX.NDD.128.66.0F.WIG 72 /6 ib VPSLLD xmm1,xmm2,int8*/
    /* VEX.NDD.256.66.0F.WIG 72 /6 ib VPSLLD ymm1, ymm2, int8*/
    { FCML_AMT_AVX_SIMD, 0x1080, 0x00DBB000, { 0x0F, 0x72, 0x00 }, { FCML_OP_VEX_VVVV_SIMD_REG | FCML_OA_W, FCML_OP_RM( FCML_REG_SIMD, FCML_EOS_L, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPSLLQ[] = {
	/* VEX.NDS.128.66.0F.WIG F3 /r VPSLLQ xmm1,xmm2,xmm3/m128*/
	/* VEX.NDS.256.66.0F.WIG F3 /r VPSLLQ ymm1, ymm2, xmm3/m128*/
    { FCML_AMT_AVX_SIMD, 0x1080, 0x00D88000, { 0x0F, 0xF3, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.NDD.128.66.0F.WIG 73 /6 ib VPSLLQ xmm1,xmm2,int8*/
	/* VEX.NDD.256.66.0F.WIG 73 /6 ib VPSLLQ ymm1, ymm2, int8*/
    { FCML_AMT_AVX_SIMD, 0x1080, 0x00DBB000, { 0x0F, 0x73, 0x00 }, { FCML_OP_VEX_VVVV_SIMD_REG | FCML_OA_W, FCML_OP_RM( FCML_REG_SIMD, FCML_EOS_L, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPSRAW[] = {
	/* VEX.NDS.128.66.0F.WIG E1 /r VPSRAW xmm1,xmm2,xmm3/m128*/
    { FCML_AMT_AVX_SIMD, 0x10C0, 0x00D88000, { 0x0F, 0xE1, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.NDS.256.66.0F.WIG E1 /r VPSRAW ymm1, ymm2, xmm3/m128*/
    { FCML_AMT_AVX2_SIMD, 0x10A0, 0x00D88000, { 0x0F, 0xE1, 0x00 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.NDD.128.66.0F.WIG 71 /4 ib VPSRAW xmm1,xmm2,int8*/
    { FCML_AMT_AVX_SIMD, 0x10C0, 0x00DBA000, { 0x0F, 0x71, 0x00 }, { FCML_OP_VEX_VVVV_XMM_REG | FCML_OA_W, FCML_OP_RM( FCML_REG_SIMD, FCML_EOS_OWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.NDD.256.66.0F.WIG 71 /4 ib VPSRAW ymm1,ymm2,int8*/
    { FCML_AMT_AVX2_SIMD, 0x10A0, 0x00DBA000, { 0x0F, 0x71, 0x00 }, { FCML_OP_VEX_VVVV_YMM_REG | FCML_OA_W, FCML_OP_RM( FCML_REG_SIMD, FCML_EOS_YWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PSRAD[] = {
	/* 0F E2 /r1 PSRAD mm,mm/m64*/
    { FCML_AMT_MMX_SIMD, 0x0000, 0x00D88000, { 0x0F, 0xE2, 0x00 }, { FCML_OP_MODRM_R_MMX_RW, FCML_OP_MODRM_RM_MMX_OP, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* 66 0F E2 /r PSRAD xmm1,xmm2/m128*/
    { FCML_AMT_SSE2_SIMD, 0x1000, 0x00D88000, { 0x0F, 0xE2, 0x00 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* 0F 72 /4 ib1 PSRAD mm,int8*/
    { FCML_AMT_MMX_SIMD, 0x0000, 0x00DBA000, { 0x0F, 0x72, 0x00 }, { FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_MWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ) | FCML_OA_W, FCML_OP_IB, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* 66 0F 72 /4 ib PSRAD xmm1,int8*/
    { FCML_AMT_SSE2_SIMD, 0x1000, 0x00DBA000, { 0x0F, 0x72, 0x00 }, { FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_OWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ) | FCML_OA_W, FCML_OP_IB, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PSRAW[] = {
	/* 0F E1 /r1 PSRAW mm,mm/m64*/
    { FCML_AMT_MMX_SIMD, 0x0000, 0x00D88000, { 0x0F, 0xE1, 0x00 }, { FCML_OP_MODRM_R_MMX_RW, FCML_OP_MODRM_RM_MMX_OP, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* 66 0F E1 /r PSRAW xmm1,xmm2/m128*/
    { FCML_AMT_SSE2_SIMD, 0x1000, 0x00D88000, { 0x0F, 0xE1, 0x00 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* 0F 71 /4 ib1 PSRAW mm,int8*/
    { FCML_AMT_MMX_SIMD, 0x0000, 0x00DBA000, { 0x0F, 0x71, 0x00 }, { FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_MWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ) | FCML_OA_W, FCML_OP_IB, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* 66 0F 71 /4 ib PSRAW xmm1,int8*/
    { FCML_AMT_SSE2_SIMD, 0x1000, 0x00DBA000, { 0x0F, 0x71, 0x00 }, { FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_OWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ) | FCML_OA_W, FCML_OP_IB, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPSRAD[] = {
	/* VEX.NDS.128.66.0F.WIG E2 /r VPSRAD xmm1,xmm2,xmm3/m128*/
    { FCML_AMT_AVX_SIMD, 0x10C0, 0x00D88000, { 0x0F, 0xE2, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.NDS.256.66.0F.WIG E2 /r VPSRAD ymm1, ymm2, xmm3/m128*/
    { FCML_AMT_AVX2_SIMD, 0x10A0, 0x00D88000, { 0x0F, 0xE2, 0x00 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_YMM_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.NDD.128.66.0F.WIG 72 /4 ib VPSRAD xmm1,xmm2,int8*/
    { FCML_AMT_AVX_SIMD, 0x10C0, 0x00DBA000, { 0x0F, 0x72, 0x00 }, { FCML_OP_VEX_VVVV_XMM_REG | FCML_OA_W, FCML_OP_RM( FCML_REG_SIMD, FCML_EOS_XWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.NDD.256.66.0F.WIG 72 /4 ib VPSRAD ymm1,ymm2,int8*/
    { FCML_AMT_AVX2_SIMD, 0x10A0, 0x00DBA000, { 0x0F, 0x72, 0x00 }, { FCML_OP_VEX_VVVV_YMM_REG | FCML_OA_W, FCML_OP_RM( FCML_REG_SIMD, FCML_EOS_YWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PSRLDQ[] = {
	/* 66 0F 73 /3 ib PSRLDQ xmm1,int8*/
    { FCML_AMT_SSE2_SIMD, 0x1000, 0x00DB9800, { 0x0F, 0x73, 0x00 }, { FCML_OP_RM( FCML_REG_SIMD, FCML_EOS_XWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ) | FCML_OA_RW, FCML_OP_IB, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPSRLDQ[] = {
	/* VEX.NDD.128.66.0F.WIG 73 /3 ib VPSRLDQ xmm1,xmm2,int8*/
    { FCML_AMT_AVX_SIMD, 0x10C0, 0x00DB9800, { 0x0F, 0x73, 0x00 }, { FCML_OP_VEX_VVVV_XMM_REG | FCML_OA_W, FCML_OP_RM( FCML_REG_SIMD, FCML_EOS_XWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.NDD.256.66.0F.WIG 73 /3 ib VPSRLDQ ymm1,ymm2,int8*/
    { FCML_AMT_AVX2_SIMD, 0x10A0, 0x00DB9800, { 0x0F, 0x73, 0x00 }, { FCML_OP_VEX_VVVV_YMM_REG | FCML_OA_W, FCML_OP_RM( FCML_REG_SIMD, FCML_EOS_YWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPSRLQ[] = {
	/* VEX.NDS.128.66.0F.WIG D3 /r VPSRLQ xmm1,xmm2,xmm3/m128*/
    { FCML_AMT_AVX_SIMD, 0x10C0, 0x00D88000, { 0x0F, 0xD3, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.NDD.128.66.0F.WIG 73 /2 ib VPSRLQ xmm1,xmm2,int8*/
    { FCML_AMT_AVX_SIMD, 0x10C0, 0x00DB9000, { 0x0F, 0x73, 0x00 }, { FCML_OP_VEX_VVVV_XMM_REG | FCML_OA_W, FCML_OP_RM( FCML_REG_SIMD, FCML_EOS_OWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PSRLQ[] = {
	/* 0F D3 /r PSRLQ mm,mm/m64*/
    { FCML_AMT_MMX_SIMD, 0x0000, 0x00D88000, { 0x0F, 0xD3, 0x00 }, { FCML_OP_MODRM_R_MMX_RW, FCML_OP_MODRM_RM_MMX_OP, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* 66 0F D3 /r PSRLQ xmm1,xmm2/m128*/
    { FCML_AMT_SSE2_SIMD, 0x1000, 0x00D88000, { 0x0F, 0xD3, 0x00 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* 0F 73 /2 ib PSRLQ mm,int8*/
    { FCML_AMT_MMX_SIMD, 0x0000, 0x00DB9000, { 0x0F, 0x73, 0x00 }, { FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_MWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ) | FCML_OA_RW, FCML_OP_IB, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* 66 0F 73 /2 ib PSRLQ xmm1,int8*/
    { FCML_AMT_SSE2_SIMD, 0x1000, 0x00DB9000, { 0x0F, 0x73, 0x00 }, { FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_XWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ) | FCML_OA_RW, FCML_OP_IB, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PSRLD[] = {
	/* 0F D2 /r PSRLD mm,mm/m64*/
    { FCML_AMT_MMX_SIMD, 0x0000, 0x00D88000, { 0x0F, 0xD2, 0x00 }, { FCML_OP_MODRM_R_MMX_RW, FCML_OP_MODRM_RM_MMX_OP, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* 66 0F D2 /r PSRLD xmm1,xmm2/m128*/
    { FCML_AMT_SSE2_SIMD, 0x1000, 0x00D88000, { 0x0F, 0xD2, 0x00 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* 0F 72 /2 ib PSRLD mm,int8*/
    { FCML_AMT_MMX_SIMD, 0x0000, 0x00DB9000, { 0x0F, 0x72, 0x00 }, { FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_MWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ) | FCML_OA_RW, FCML_OP_IB, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* 66 0F 72 /2 ib PSRLD xmm1,int8*/
    { FCML_AMT_SSE2_SIMD, 0x1000, 0x00DB9000, { 0x0F, 0x72, 0x00 }, { FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_XWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ) | FCML_OA_RW, FCML_OP_IB, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PSRLW[] = {
	/* 0F D1 /r PSRLW mm,mm/m64*/
    { FCML_AMT_MMX_SIMD, 0x0000, 0x00D88000, { 0x0F, 0xD1, 0x00 }, { FCML_OP_MODRM_R_MMX_RW, FCML_OP_MODRM_RM_MMX_OP, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* 66 0F D1 /r PSRLW xmm1,xmm2/m128*/
    { FCML_AMT_SSE2_SIMD, 0x1000, 0x00D88000, { 0x0F, 0xD1, 0x00 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* 0F 71 /2 ib PSRLW mm,int8*/
    { FCML_AMT_MMX_SIMD, 0x0000, 0x00DB9000, { 0x0F, 0x71, 0x00 }, { FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_QWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_OP_IB, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* 66 0F 71 /2 ib PSRLW xmm1,int8*/
    { FCML_AMT_SSE2_SIMD, 0x1000, 0x00DB9000, { 0x0F, 0x71, 0x00 }, { FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_OWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_OP_IB, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPSRLD[] = {
	/* VEX.NDS.128.66.0F.WIG D2 /r VPSRLD xmm1,xmm2,xmm3/m128*/
    { FCML_AMT_AVX_SIMD, 0x10C0, 0x00D88000, { 0x0F, 0xD2, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.NDS.256.66.0F.WIG D2 /r VPSRLD ymm1,ymm2,xmm3/m128*/
    { FCML_AMT_AVX2_SIMD, 0x10A0, 0x00D88000, { 0x0F, 0xD2, 0x00 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.NDD.128.66.0F.WIG 72 /2 ib VPSRLD xmm1,xmm2,int8*/
    { FCML_AMT_AVX_SIMD, 0x10C0, 0x00DB9000, { 0x0F, 0x72, 0x00 }, { FCML_OP_VEX_VVVV_XMM_REG | FCML_OA_W, FCML_OP_RM( FCML_REG_SIMD, FCML_EOS_OWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPSRLW[] = {
	/* VEX.NDS.128.66.0F.WIG D1 /r VPSRLW xmm1,xmm2,xmm3/m128*/
    { FCML_AMT_AVX_SIMD, 0x10C0, 0x00D88000, { 0x0F, 0xD1, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.NDS.256.66.0F.WIG D1 /r VPSRLW ymm1,ymm2,xmm3/m128*/
    { FCML_AMT_AVX2_SIMD, 0x10A0, 0x00D88000, { 0x0F, 0xD1, 0x00 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.NDD.128.66.0F.WIG 71 /2 ib VPSRLW xmm1,xmm2,int8*/
    { FCML_AMT_AVX_SIMD, 0x10C0, 0x00DB9000, { 0x0F, 0x71, 0x00 }, { FCML_OP_VEX_VVVV_XMM_REG | FCML_OA_W, FCML_OP_RM( FCML_REG_SIMD, FCML_EOS_OWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.NDD.256.66.0F.WIG 71 /2 ib VPSRLW ymm1,ymm2,int8*/
    { FCML_AMT_AVX2_SIMD, 0x10A0, 0x00DB9000, { 0x0F, 0x71, 0x00 }, { FCML_OP_VEX_VVVV_YMM_REG | FCML_OA_W, FCML_OP_RM( FCML_REG_SIMD, FCML_EOS_YWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPSUBD[] = {
	/* VEX.NDS.128.66.0F.WIG FA /r VPSUBD xmm1,xmm2,xmm3/m128*/
    { FCML_AMT_AVX_SIMD, 0x10C0, 0x00D88000, { 0x0F, 0xFA, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.NDS.256.66.0F.WIG FA /r VPSUBD ymm1,ymm2,ymm3/m256*/
    { FCML_AMT_AVX2_SIMD, 0x10A0, 0x00D88000, { 0x0F, 0xFA, 0x00 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_YMM_OP_256, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PSUBD[] = {
	/* 0F FA /r PSUBD mm,mm/m64*/
    { FCML_AMT_MMX_SIMD, 0x0000, 0x00D88000, { 0x0F, 0xFA, 0x00 }, { FCML_OP_MODRM_R_MMX_RW, FCML_OP_MODRM_RM_MMX_OP, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* 66 0F FA /r PSUBD xmm1,xmm2/m128*/
    { FCML_AMT_SSE2_SIMD, 0x1000, 0x00D88000, { 0x0F, 0xFA, 0x00 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PSUBW[] = {
	/* 0F F9 /r PSUBW mm,mm/m64*/
    { FCML_AMT_MMX_SIMD, 0x0000, 0x00D88000, { 0x0F, 0xF9, 0x00 }, { FCML_OP_MODRM_R_MMX_RW, FCML_OP_MODRM_RM_MMX_OP, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* 66 0F F9 /r PSUBW xmm1,xmm2/m128*/
    { FCML_AMT_SSE2_SIMD, 0x1000, 0x00D88000, { 0x0F, 0xF9, 0x00 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPSUBB[] = {
	/* VEX.NDS.128.66.0F.WIG F8 /r VPSUBB xmm1,xmm2,xmm3/m128*/
    { FCML_AMT_AVX_SIMD, 0x10C0, 0x00D88000, { 0x0F, 0xF8, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.NDS.256.66.0F.WIG F8 /r VPSUBB ymm1,ymm2,ymm3/m256*/
    { FCML_AMT_AVX2_SIMD, 0x10A0, 0x00D88000, { 0x0F, 0xF8, 0x00 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_YMM_REG, FCML_OP_MODRM_RM_YMM_OP_256, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PSUBB[] = {
	/* 0F F8 /r PSUBB mm,mm/m64*/
    { FCML_AMT_MMX_SIMD, 0x0000, 0x00D88000, { 0x0F, 0xF8, 0x00 }, { FCML_OP_MODRM_R_MMX_RW, FCML_OP_MODRM_RM_MMX_OP, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* 66 0F F8 /r PSUBB xmm1,xmm2/m128*/
    { FCML_AMT_SSE2_SIMD, 0x1000, 0x00D88000, { 0x0F, 0xF8, 0x00 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPSUBW[] = {
	/* VEX.NDS.128.66.0F.WIG F9 /r VPSUBW xmm1,xmm2,xmm3/m128*/
    { FCML_AMT_AVX_SIMD, 0x10C0, 0x00D88000, { 0x0F, 0xF9, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.NDS.256.66.0F.WIG F9 /r VPSUBW ymm1,ymm2,ymm3/m256*/
    { FCML_AMT_AVX2_SIMD, 0x10A0, 0x00D88000, { 0x0F, 0xF9, 0x00 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_YMM_REG, FCML_OP_MODRM_RM_YMM_OP_256, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PSUBQ[] = {
	/* 0F FB /r PSUBQ mm1,mm2/m64*/
    { FCML_AMT_SSE2_SIMD, 0x0000, 0x00D88000, { 0x0F, 0xFB, 0x00 }, { FCML_OP_MODRM_R_MMX_RW, FCML_OP_MODRM_RM_MMX_OP, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* 66 0F FB /r PSUBQ xmm1,xmm2/m128*/
    { FCML_AMT_SSE2_SIMD, 0x1000, 0x00D88000, { 0x0F, 0xFB, 0x00 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPSUBQ[] = {
	/* VEX.NDS.128.66.0F.WIG FB/r VPSUBQ xmm1,xmm2,xmm3/m128*/
    { FCML_AMT_AVX_SIMD, 0x10C0, 0x00D88000, { 0x0F, 0xFB, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.NDS.256.66.0F.WIG FB /r VPSUBQ ymm1,ymm2,ymm3/m256*/
    { FCML_AMT_AVX2_SIMD, 0x10A0, 0x00D88000, { 0x0F, 0xFB, 0x00 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_YMM_REG, FCML_OP_MODRM_RM_YMM_OP_256, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PSUBSB[] = {
	/* 0F E8 /r PSUBSB mm,mm/m64*/
    { FCML_AMT_MMX_SIMD, 0x0000, 0x00D88000, { 0x0F, 0xE8, 0x00 }, { FCML_OP_MODRM_R_MMX_RW, FCML_OP_MODRM_RM_MMX_OP, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* 66 0F E8 /r PSUBSB xmm1,xmm2/m128*/
    { FCML_AMT_SSE2_SIMD, 0x1000, 0x00D88000, { 0x0F, 0xE8, 0x00 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPSUBSW[] = {
	/* VEX.NDS.128.66.0F.WIG E9 /r VPSUBSW xmm1,xmm2,xmm3/m128*/
    { FCML_AMT_AVX_SIMD, 0x10C0, 0x00D88000, { 0x0F, 0xE9, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.NDS.256.66.0F.WIG E9 /r VPSUBSW ymm1,ymm2,ymm3/m256*/
    { FCML_AMT_AVX2_SIMD, 0x10A0, 0x00D88000, { 0x0F, 0xE9, 0x00 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_YMM_REG, FCML_OP_MODRM_RM_YMM_OP_256, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPSUBSB[] = {
	/* VEX.NDS.128.66.0F.WIG E8 /r VPSUBSB xmm1,xmm2,xmm3/m128*/
    { FCML_AMT_AVX_SIMD, 0x10C0, 0x00D88000, { 0x0F, 0xE8, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.NDS.256.66.0F.WIG E8 /r VPSUBSB ymm1,ymm2,ymm3/m256*/
    { FCML_AMT_AVX2_SIMD, 0x10A0, 0x00D88000, { 0x0F, 0xE8, 0x00 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_YMM_REG, FCML_OP_MODRM_RM_YMM_OP_256, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PSUBSW[] = {
	/* 0F E9 /r PSUBSW mm,mm/m64*/
    { FCML_AMT_MMX_SIMD, 0x0000, 0x00D88000, { 0x0F, 0xE9, 0x00 }, { FCML_OP_MODRM_R_MMX_RW, FCML_OP_MODRM_RM_MMX_OP, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* 66 0F E9 /r PSUBSW xmm1,xmm2/m128*/
    { FCML_AMT_SSE2_SIMD, 0x1000, 0x00D88000, { 0x0F, 0xE9, 0x00 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPSUBUSW[] = {
	/* VEX.NDS.128.66.0F.WIG D9 /r VPSUBUSW xmm1,xmm2,xmm3/m128*/
    { FCML_AMT_AVX_SIMD, 0x10C0, 0x00D88000, { 0x0F, 0xD9, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.NDS.256.66.0F.WIG D9 /r VPSUBUSW ymm1,ymm2,ymm3/m256*/
    { FCML_AMT_AVX2_SIMD, 0x10A0, 0x00D88000, { 0x0F, 0xD9, 0x00 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_YMM_REG, FCML_OP_MODRM_RM_YMM_OP_256, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPSUBUSB[] = {
	/* VEX.NDS.128.66.0F.WIG D8 /r VPSUBUSB xmm1,xmm2,xmm3/m128*/
    { FCML_AMT_AVX_SIMD, 0x10C0, 0x00D88000, { 0x0F, 0xD8, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.NDS.256.66.0F.WIG D8 /r VPSUBUSB ymm1,ymm2,ymm3/m256*/
    { FCML_AMT_AVX2_SIMD, 0x10A0, 0x00D88000, { 0x0F, 0xD8, 0x00 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_YMM_OP_256, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PSUBUSB[] = {
	/* 0F D8 /r PSUBUSB mm,mm/m64*/
    { FCML_AMT_MMX_SIMD, 0x0000, 0x00D88000, { 0x0F, 0xD8, 0x00 }, { FCML_OP_MODRM_R_MMX_RW, FCML_OP_MODRM_RM_MMX_OP, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* 66 0F D8 /r PSUBUSB xmm1,xmm2/m128*/
    { FCML_AMT_SSE2_SIMD, 0x1000, 0x00D88000, { 0x0F, 0xD8, 0x00 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PSUBUSW[] = {
	/* 0F D9 /r1 PSUBUSW mm,mm/m64*/
    { FCML_AMT_MMX_SIMD, 0x0000, 0x00D88000, { 0x0F, 0xD9, 0x00 }, { FCML_OP_MODRM_R_MMX_RW, FCML_OP_MODRM_RM_MMX_OP, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* 66 0F D9 /r PSUBUSW xmm1,xmm2/m128*/
    { FCML_AMT_SSE2_SIMD, 0x1000, 0x00D88000, { 0x0F, 0xD9, 0x00 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPTEST[] = {
	/* VEX.128.66.0F38.WIG 17 /r VPTEST xmm1,xmm2/m128*/
	/* VEX.256.66.0F38.WIG 17 /r VPTEST ymm1,ymm2/m256*/
    { FCML_AMT_AVX_SIMD, 0x1080, 0x00EC8000, { 0x0F, 0x38, 0x17 }, { FCML_OP_MODRM_R_SIMD_L, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PTEST[] = {
	/* 66 0F 38 17 /r PTEST xmm1,xmm2/m128*/
    { FCML_AMT_SSE41_SIMD, 0x1000, 0x00EC8000, { 0x0F, 0x38, 0x17 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PUNPCKLBW[] = {
	/* 0F 60 /r PUNPCKLBW mm,mm/m32*/
    { FCML_AMT_MMX_SIMD, 0x0000, 0x00D88000, { 0x0F, 0x60, 0x00 }, { FCML_OP_MODRM_R_MMX_RW, FCML_OP_MODRM_RM_MMX_OP_32, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* 66 0F 60 /r PUNPCKLBW xmm1,xmm2/m128*/
    { FCML_AMT_SSE2, 0x1000, 0x00D88000, { 0x0F, 0x60, 0x00 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PUNPCKLQDQ[] = {
	/* 66 0F 6C /r PUNPCKLQDQ xmm1,xmm2/m128*/
    { FCML_AMT_SSE2, 0x1000, 0x00D88000, { 0x0F, 0x6C, 0x00 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPUNPCKLWD[] = {
	/* VEX.NDS.128.66.0F.WIG 61 /r VPUNPCKLWD xmm1,xmm2,xmm3/m128*/
    { FCML_AMT_AVX_SIMD, 0x10C0, 0x00D88000, { 0x0F, 0x61, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.NDS.256.66.0F.WIG 61 /r VPUNPCKLWD ymm1,ymm2,ymm3/m256*/
    { FCML_AMT_AVX2_SIMD, 0x10A0, 0x00D88000, { 0x0F, 0x61, 0x00 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_YMM_REG, FCML_OP_MODRM_RM_YMM_OP_256, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPUNPCKLQDQ[] = {
	/* VEX.NDS.128.66.0F.WIG 6C /r VPUNPCKLQDQ xmm1,xmm2,xmm3/m128*/
    { FCML_AMT_AVX_SIMD, 0x10C0, 0x00D88000, { 0x0F, 0x6C, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.NDS.256.66.0F.WIG 6C /r VPUNPCKLQDQ ymm1,ymm2,ymm3/m256*/
    { FCML_AMT_AVX2_SIMD, 0x10A0, 0x00D88000, { 0x0F, 0x6C, 0x00 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_YMM_REG, FCML_OP_MODRM_RM_YMM_OP_256, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPUNPCKLBW[] = {
	/* VEX.NDS.128.66.0F.WIG 60 /r VPUNPCKLBW xmm1,xmm2,xmm3/m128*/
    { FCML_AMT_AVX_SIMD, 0x10C0, 0x00D88000, { 0x0F, 0x60, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.NDS.256.66.0F.WIG 60 /r VPUNPCKLBW ymm1,ymm2,ymm3/m256*/
    { FCML_AMT_AVX2_SIMD, 0x10A0, 0x00D88000, { 0x0F, 0x60, 0x00 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_YMM_REG, FCML_OP_MODRM_RM_YMM_OP_256, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PUNPCKLWD[] = {
	/* 0F 61 /r PUNPCKLWD mm,mm/m32*/
    { FCML_AMT_MMX_SIMD, 0x0000, 0x00D88000, { 0x0F, 0x61, 0x00 }, { FCML_OP_MODRM_R_MMX_RW, FCML_OP_MODRM_RM_MMX_OP_32, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* 66 0F 61 /r PUNPCKLWD xmm1,xmm2/m128*/
    { FCML_AMT_SSE2, 0x1000, 0x00D88000, { 0x0F, 0x61, 0x00 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PUNPCKLDQ[] = {
	/* 0F 62 /r PUNPCKLDQ mm,mm/m32*/
    { FCML_AMT_MMX_SIMD, 0x0000, 0x00D88000, { 0x0F, 0x62, 0x00 }, { FCML_OP_MODRM_R_MMX_RW, FCML_OP_MODRM_RM_MMX_OP_32, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* 66 0F 62 /r PUNPCKLDQ xmm1,xmm2/m128*/
    { FCML_AMT_SSE2, 0x1000, 0x00D88000, { 0x0F, 0x62, 0x00 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPUNPCKLDQ[] = {
	/* VEX.NDS.128.66.0F.WIG 62 /r VPUNPCKLDQ xmm1,xmm2,xmm3/m128*/
    { FCML_AMT_AVX_SIMD, 0x10C0, 0x00D88000, { 0x0F, 0x62, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.NDS.256.66.0F.WIG 62 /r VPUNPCKLDQ ymm1,ymm2,ymm3/m256*/
    { FCML_AMT_AVX2_SIMD, 0x10A0, 0x00D88000, { 0x0F, 0x62, 0x00 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_YMM_REG, FCML_OP_MODRM_RM_YMM_OP_256, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPUNPCKHWD[] = {
	/* VEX.NDS.128.66.0F.WIG 69 /r VPUNPCKHWD xmm1,xmm2,xmm3/m128*/
    { FCML_AMT_AVX_SIMD, 0x10C0, 0x00D88000, { 0x0F, 0x69, 0x00 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.NDS.256.66.0F.WIG 69 /r VPUNPCKHWD ymm1,ymm2,ymm3/m256*/
    { FCML_AMT_AVX2_SIMD, 0x10A0, 0x00D88000, { 0x0F, 0x69, 0x00 }, { FCML_OP_MODRM_R_YMM_RW, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_YMM_OP_256, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PUNPCKHDQ[] = {
	/* 0F 6A /r PUNPCKHDQ mm,mm/m64*/
    { FCML_AMT_MMX_SIMD, 0x0000, 0x00D88000, { 0x0F, 0x6A, 0x00 }, { FCML_OP_MODRM_R_MMX_RW, FCML_OP_MODRM_RM_MMX_OP, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* 66 0F 6A /r PUNPCKHDQ xmm1,xmm2/m128*/
    { FCML_AMT_SSE2_SIMD, 0x1000, 0x00D88000, { 0x0F, 0x6A, 0x00 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PUNPCKHWD[] = {
	/* 0F 69 /r PUNPCKHWD mm,mm/m64*/
    { FCML_AMT_MMX_SIMD, 0x0000, 0x00D88000, { 0x0F, 0x69, 0x00 }, { FCML_OP_MODRM_R_MMX_RW, FCML_OP_MODRM_RM_MMX_OP, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* 66 0F 69 /r PUNPCKHWD xmm1,xmm2/m128*/
    { FCML_AMT_SSE2_SIMD, 0x1000, 0x00D88000, { 0x0F, 0x69, 0x00 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PUNPCKHQDQ[] = {
	/* 66 0F 6D /r PUNPCKHQDQ xmm1,xmm2/m128*/
    { FCML_AMT_SSE2_SIMD, 0x1000, 0x00D88000, { 0x0F, 0x6D, 0x00 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPUNPCKHQDQ[] = {
	/* VEX.NDS.128.66.0F.WIG 6D /r VPUNPCKHQDQ xmm1,xmm2,xmm3/m128*/
    { FCML_AMT_AVX_SIMD, 0x10C0, 0x00D88000, { 0x0F, 0x6D, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.NDS.256.66.0F.WIG 6D /r VPUNPCKHQDQ ymm1,ymm2,ymm3/m256*/
    { FCML_AMT_AVX2_SIMD, 0x10A0, 0x00D88000, { 0x0F, 0x6D, 0x00 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_YMM_REG, FCML_OP_MODRM_RM_YMM_OP_256, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPUNPCKHBW[] = {
	/* VEX.NDS.128.66.0F.WIG 68 /r VPUNPCKHBW xmm1,xmm2,xmm3/m128*/
    { FCML_AMT_AVX_SIMD, 0x10C0, 0x00D88000, { 0x0F, 0x68, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.NDS.256.66.0F.WIG 68 /r VPUNPCKHBW ymm1,ymm2,ymm3/m256*/
    { FCML_AMT_AVX2_SIMD, 0x10A0, 0x00D88000, { 0x0F, 0x68, 0x00 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_YMM_REG, FCML_OP_MODRM_RM_YMM_OP_256, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PUNPCKHBW[] = {
	/* 0F 68 /r PUNPCKHBW mm,mm/m64*/
    { FCML_AMT_MMX_SIMD, 0x0000, 0x00D88000, { 0x0F, 0x68, 0x00 }, { FCML_OP_MODRM_R_MMX_RW, FCML_OP_MODRM_RM_MMX_OP, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* 66 0F 68 /r PUNPCKHBW xmm1,xmm2/m128*/
    { FCML_AMT_SSE2_SIMD, 0x1000, 0x00D88000, { 0x0F, 0x68, 0x00 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPUNPCKHDQ[] = {
	/* VEX.NDS.128.66.0F.WIG 6A /r VPUNPCKHDQ xmm1,xmm2,xmm3/m128*/
    { FCML_AMT_AVX_SIMD, 0x10C0, 0x00D88000, { 0x0F, 0x6A, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.NDS.256.66.0F.WIG 6A /r VPUNPCKHDQ ymm1,ymm2,ymm3/m256*/
    { FCML_AMT_AVX2_SIMD, 0x10A0, 0x00D88000, { 0x0F, 0x6A, 0x00 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_YMM_REG, FCML_OP_MODRM_RM_YMM_OP_256, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PUSH[] = {
	/* FF /6 PUSH r/m16 M Valid Valid Push r/m16.*/
	/* FF /6 PUSH r/m32 M N.E. Valid Push r/m32.*/
	/* FF /6 PUSH r/m64 M Valid N.E. Push r/m64.*/
    { FCML_AMT_GPI, 0x0000, 0x00C5B080, { 0xFF, 0x00, 0x00 }, { FCML_OP_MODRM_RM, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RMO },
	/* 50+rw PUSH r16 O Valid Valid Push r16.*/
	/* 50+rd PUSH r32 O N.E. Valid Push r32.*/
	/* 50+rd PUSH r64 O Valid N.E. Push r64.*/
    { FCML_AMT_GPI, 0x0000, 0x00C40081, { 0x50, 0x00, 0x00 }, { FCML_OP_OPCODE_REG( FCML_REG_GPR, FCML_EOS_EOSA) | FCML_OA_W , FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RO },
	/* 6A PUSH int8 I Valid Valid Push int8.*/
    { FCML_AMT_GPI, 0x0000, 0x00C40004, { 0x6A, 0x00, 0x00 }, { FCML_OP_IB_EX_EOSA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_IMM8 },
	/* 68 PUSH int16 I Valid Valid Push int16.*/
	/* 68 PUSH int32 I Valid Valid Push int32.*/
    { FCML_AMT_GPI, 0x0000, 0x00C40084, { 0x68, 0x00, 0x00 }, { FCML_OP_EX_EOSA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_IMMO },
	/* 1E PUSH DS NP Invalid Valid Push DS.*/
	/* 06 PUSH ES NP Invalid Valid Push ES.*/
	/* 16 PUSH SS NP Invalid Valid Push SS.*/
	/* 0E PUSH CS NP Invalid Valid Push CS.*/
    { FCML_AMT_GPI, 0x0000, 0x00440000, { 0x1E, 0x00, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_SEG, FCML_REG_DS, FCML_EOS_UNDEFINED ), FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_SRO },
    { FCML_AMT_GPI, 0x0000, 0x00440000, { 0x06, 0x00, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_SEG, FCML_REG_ES, FCML_EOS_UNDEFINED ), FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_SRO },
    { FCML_AMT_GPI, 0x0000, 0x00440000, { 0x16, 0x00, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_SEG, FCML_REG_SS, FCML_EOS_UNDEFINED ), FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_SRO },
    { FCML_AMT_GPI, 0x0000, 0x00440000, { 0x0E, 0x00, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_SEG, FCML_REG_CS, FCML_EOS_UNDEFINED ), FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_SRO },
	/* 0F A0 PUSH FS NP Valid Valid Push FS.*/
    { FCML_AMT_GPI, 0x0000, 0x00D80080, { 0x0F, 0xA0, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_SEG, FCML_REG_FS, FCML_EOS_UNDEFINED ), FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_SR_FSGSO },
	/* 0F A8 PUSH GS NP Valid Valid Push GS.*/
    { FCML_AMT_GPI, 0x0000, 0x00D80080, { 0x0F, 0xA8, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_SEG, FCML_REG_GS, FCML_EOS_UNDEFINED ), FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_SR_FSGSO }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PUSHA[] = {
	/* 60 PUSHA NP Invalid Valid Push AX, CX, DX, BX, original SP, BP, SI, and DI.*/
    { FCML_AMT_GPI, 0x0000, 0x01440000, { 0x60, 0x00, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PUSHAD[] = {
	/* 60 PUSHAD NP Invalid Valid Push EAX, ECX, EDX, EBX, original ESP, EBP, ESI, and EDI.*/
    { FCML_AMT_GPI, 0x0000, 0x02440000, { 0x60, 0x00, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PUSHF[] = {
	/* 9C PUSHF NP Valid Valid Push lower 16 bits of EFLAGS.*/
    { FCML_AMT_GPI, 0x0000, 0x01C40000, { 0x9C, 0x00, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PUSHFQ[] = {
	/* 9C PUSHFQ NP Valid N.E. Push RFLAGS.*/
    { FCML_AMT_GPI, 0x0000, 0x00840080, { 0x9C, 0x00, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PUSHFD[] = {
	/* 9C PUSHFD NP N.E. Valid Push EFLAGS.*/
    { FCML_AMT_GPI, 0x0000, 0x02440000, { 0x9C, 0x00, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PXOR[] = {
	/* 0F EF /r PXOR mm,mm/m64*/
    { FCML_AMT_MMX_SIMD, 0x0000, 0x00D88000, { 0x0F, 0xEF, 0x00 }, { FCML_OP_MODRM_R_MMX_RW, FCML_OP_MODRM_RM_MMX_OP, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* 66 0F EF /r PXOR xmm1,xmm2/m128*/
    { FCML_AMT_SSE2_SIMD, 0x1000, 0x00D88000, { 0x0F, 0xEF, 0x00 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPXOR[] = {
	/* VEX.NDS.128.66.0F.WIG EF /r VPXOR xmm1,xmm2,xmm3/m128*/
    { FCML_AMT_AVX_SIMD, 0x10C0, 0x00D88000, { 0x0F, 0xEF, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.NDS.256.66.0F.WIG EF /r VPXOR ymm1,ymm2,ymm3/m256*/
    { FCML_AMT_AVX2_SIMD, 0x10A0, 0x00D88000, { 0x0F, 0xEF, 0x00 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_YMM_REG, FCML_OP_MODRM_RM_YMM_OP_256, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_RCL[] = {
	/* D0 /2 RCL r/m8, 1*/
	/* REX + D0 /2 RCL r/m8, 1*/
    { FCML_AMT_GPI, 0x0000, 0x00C59000, { 0xD0, 0x00, 0x00 }, { FCML_OP_MODRM_RM_8_W, FCML_OP_EXPLICIT_IB(1), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RM8 },
	/* D2 /2 RCL r/m8, CL*/
	/* REX + D2 /2 RCL r/m8, CL*/
    { FCML_AMT_GPI, 0x0000, 0x00C59000, { 0xD2, 0x00, 0x00 }, { FCML_OP_MODRM_RM_8_W, FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_CL, FCML_EOS_BYTE ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RM8 },
	/* C0 /2 ib RCL r/m8, int8*/
	/* REX + C0 /2 ib RCL r/m8, int8*/
    { FCML_AMT_GPI, 0x0000, 0x00C59000, { 0xC0, 0x00, 0x00 }, { FCML_OP_MODRM_RM_8_W, FCML_OP_IB, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RM8_IMM8 },
	/* D1 /2 RCL r/m16, 1*/
	/* D1 /2 RCL r/m32, 1*/
	/* REX.W + D1 /2 RCL r/m64, 1*/
    { FCML_AMT_GPI, 0x0000, 0x00C59000, { 0xD1, 0x00, 0x00 }, { FCML_OP_MODRM_RM_W, FCML_OP_EXPLICIT_IB(1), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RMO },
	/* D3 /2 RCL r/m16, CL*/
	/* D3 /2 RCL r/m32, CL*/
	/* REX.W + D3 /2 RCL r/m64, CL*/
    { FCML_AMT_GPI, 0x0000, 0x00C59000, { 0xD3, 0x00, 0x00 }, { FCML_OP_MODRM_RM_W, FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_CL, FCML_EOS_BYTE ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RMO },
	/* C1 /2 ib RCL r/m16, int8*/
	/* C1 /2 ib RCL r/m32, int8*/
	/* REX.W + C1 /2 ib RCL r/m64, int8*/
    { FCML_AMT_GPI, 0x0000, 0x00C59000, { 0xC1, 0x00, 0x00 }, { FCML_OP_MODRM_RM_W, FCML_OP_IB, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RMO_IMM8 }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_RCR[] = {
	/* D0 /3 RCR r/m8, 1*/
	/* REX + D0 /3 RCR r/m8, 1*/
    { FCML_AMT_GPI, 0x0000, 0x00C59800, { 0xD0, 0x00, 0x00 }, { FCML_OP_MODRM_RM_8_W, FCML_OP_EXPLICIT_IB(1), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RM8 },
	/* D2 /3 RCR r/m8, CL*/
	/* REX + D2 /3 RCR r/m8, CL*/
    { FCML_AMT_GPI, 0x0000, 0x00C59800, { 0xD2, 0x00, 0x00 }, { FCML_OP_MODRM_RM_8_W, FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_CL, FCML_EOS_BYTE ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RM8 },
	/* C0 /3 ib RCR r/m8, int8*/
	/* REX + C0 /3 ib RCR r/m8, int8*/
    { FCML_AMT_GPI, 0x0000, 0x00C59800, { 0xC0, 0x00, 0x00 }, { FCML_OP_MODRM_RM_8_W, FCML_OP_IB, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RM8_IMM8 },
	/* D1 /3 RCR r/m16, 1*/
	/* D1 /3 RCR r/m32, 1*/
	/* REX.W + D1 /3 RCR r/m64, 1*/
    { FCML_AMT_GPI, 0x0000, 0x00C59800, { 0xD1, 0x00, 0x00 }, { FCML_OP_MODRM_RM_W, FCML_OP_EXPLICIT_IB(1), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RMO },
	/* D3 /3 RCR r/m16, CL*/
	/* D3 /3 RCR r/m32, CL*/
	/* REX.W + D3 /3 RCR r/m64, CL*/
    { FCML_AMT_GPI, 0x0000, 0x00C59800, { 0xD3, 0x00, 0x00 }, { FCML_OP_MODRM_RM_W, FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_CL, FCML_EOS_BYTE ), FCML_NA, FCML_NA, FCML_NA },  FCML_AM_RMO },
	/* C1 /3 ib RCR r/m16, int8*/
	/* C1 /3 ib RCR r/m32, int8*/
	/* REX.W + C1 /3 ib RCR r/m64, int8*/
    { FCML_AMT_GPI, 0x0000, 0x00C59800, { 0xC1, 0x00, 0x00 }, { FCML_OP_MODRM_RM_W, FCML_OP_IB, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RMO_IMM8 }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_ROL[] = {
	/* D0 /0 ROL r/m8, 1*/
	/* REX + D0 /0 ROL r/m8, 1*/
    { FCML_AMT_GPI, 0x0000, 0x00C58000, { 0xD0, 0x00, 0x00 }, { FCML_OP_MODRM_RM_8_W, FCML_OP_EXPLICIT_IB(1), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RM8 },
	/* D2 /0 ROL r/m8, CL*/
	/* REX + D2 /0 ROL r/m8, CL*/
    { FCML_AMT_GPI, 0x0000, 0x00C58000, { 0xD2, 0x00, 0x00 }, { FCML_OP_MODRM_RM_8_W, FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_CL, FCML_EOS_BYTE ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RM8 },
	/* C0 /0 ib ROL r/m8, int8*/
	/* REX + C0 /0 ib ROL r/m8, int8*/
    { FCML_AMT_GPI, 0x0000, 0x00C58000, { 0xC0, 0x00, 0x00 }, { FCML_OP_MODRM_RM_8_W, FCML_OP_IB, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RM8_IMM8 },
	/* D1 /0 ROL r/m16, 1*/
	/* D1 /0 ROL r/m32, 1*/
	/* REX.W + D1 /0 ROL r/m64, 1*/
    { FCML_AMT_GPI, 0x0000, 0x00C58000, { 0xD1, 0x00, 0x00 }, { FCML_OP_MODRM_RM_W, FCML_OP_EXPLICIT_IB(1), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RMO },
	/* D3 /0 ROL r/m16, CL*/
	/* D3 /0 ROL r/m32, CL*/
	/* REX.W + D3 /0 ROL r/m64, CL*/
    { FCML_AMT_GPI, 0x0000, 0x00C58000, { 0xD3, 0x00, 0x00 }, { FCML_OP_MODRM_RM_W, FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_CL, FCML_EOS_BYTE ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RMO },
	/* C1 /0 ib ROL r/m16, int8*/
	/* C1 /0 ib ROL r/m32, int8*/
	/* C1 /0 ib ROL r/m64, int8*/
    { FCML_AMT_GPI, 0x0000, 0x00C58000, { 0xC1, 0x00, 0x00 }, { FCML_OP_MODRM_RM_W, FCML_OP_IB, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RMO_IMM8 }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_ROR[] = {
	/* D0 /1 ROR r/m8, 1*/
	/* REX + D0 /1 ROR r/m8, 1*/
    { FCML_AMT_GPI, 0x0000, 0x00C58800, { 0xD0, 0x00, 0x00 }, { FCML_OP_MODRM_RM_8_W, FCML_OP_EXPLICIT_IB(1), FCML_NA, FCML_NA, FCML_NA },  FCML_AM_RM8 },
	/* D2 /1 ROR r/m8, CL*/
	/* REX + D2 /1 ROR r/m8, CL*/
    { FCML_AMT_GPI, 0x0000, 0x00C58800, { 0xD2, 0x00, 0x00 }, { FCML_OP_MODRM_RM_8_W, FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_CL, FCML_EOS_BYTE ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RM8 },
	/* C0 /1 ib ROR r/m8, int8*/
	/* REX + C0 /1 ib ROR r/m8, int8*/
    { FCML_AMT_GPI, 0x0000, 0x00C58800, { 0xC0, 0x00, 0x00 }, { FCML_OP_MODRM_RM_8_W, FCML_OP_IB, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RM8_IMM8 },
	/* D1 /1 ROR r/m16, 1*/
	/* D1 /1 ROR r/m32, 1*/
	/* REX.W + D1 /1 ROR r/m64, 1*/
    { FCML_AMT_GPI, 0x0000, 0x00C58800, { 0xD1, 0x00, 0x00 }, { FCML_OP_MODRM_RM_W, FCML_OP_EXPLICIT_IB(1), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RMO },
	/* D3 /1 ROR r/m16, CL*/
	/* D3 /1 ROR r/m32, CL*/
	/* REX.W + D3 /1 ROR r/m64, CL*/
    { FCML_AMT_GPI, 0x0000, 0x00C58800, { 0xD3, 0x00, 0x00 }, { FCML_OP_MODRM_RM_W, FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_CL, FCML_EOS_BYTE ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RMO },
	/* C1 /1 ib ROR r/m16, int8*/
	/* C1 /1 ib ROR r/m32, int8*/
	/* REX.W + C1 /1 ib ROR r/m64, int8*/
    { FCML_AMT_GPI, 0x0000, 0x00C58800, { 0xC1, 0x00, 0x00 }, { FCML_OP_MODRM_RM_W, FCML_OP_IB, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RMO_IMM8 }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_RCPPS[] = {
	/* 0F 53 /r RCPPS xmm1,xmm2/m128*/
    { FCML_AMT_SSE_SIMD, 0x0000, 0x00D88000, { 0x0F, 0x53, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VRCPPS[] = {
	/* VEX.128.0F.WIG 53 /r VRCPPS xmm1,xmm2/m128*/
	/* VEX.256.0F.WIG 53 /r VRCPPS ymm1,ymm2/m256*/
    { FCML_AMT_AVX_SIMD, 0x0080, 0x00D88000, { 0x0F, 0x53, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_RCPSS[] = {
	/* F3 0F 53 /r RCPSS xmm1,xmm2/m32*/
    { FCML_AMT_SSE_SIMD, 0x4000, 0x00D88000, { 0x0F, 0x53, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_OP_32, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VRCPSS[] = {
	/* VEX.NDS.LIG.F3.0F.WIG 53 /r VRCPSS xmm1,xmm2,xmm3/m32*/
    { FCML_AMT_AVX_SIMD, 0x40C0, 0x00D88000, { 0x0F, 0x53, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_32, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_RDFSBASE[] = {
	/* F3 0F AE /0 RDFSBASE r32*/
	/* REX.W + F3 0F AE /0 RDFSBASE r64*/
    { FCML_AMT_SYSTEM, 0x4000, 0x03998000, { 0x0F, 0xAE, 0x00 }, { FCML_OP_RM( FCML_REG_GPR, FCML_EOS_DWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ) | FCML_OA_W, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
    { FCML_AMT_SYSTEM, 0x4000, 0x04998000, { 0x0F, 0xAE, 0x00 }, { FCML_OP_RM( FCML_REG_GPR, FCML_EOS_QWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ) | FCML_OA_W, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_RDGSBASE[] = {
	/* F3 0F AE /1 RDGSBASE r32*/
	/* REX.W + F3 0F AE /1 RDGSBASE r64*/
    { FCML_AMT_SYSTEM, 0x4000, 0x03998800, { 0x0F, 0xAE, 0x00 }, { FCML_OP_RM( FCML_REG_GPR, FCML_EOS_DWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ) | FCML_OA_W, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
    { FCML_AMT_SYSTEM, 0x4000, 0x04998800, { 0x0F, 0xAE, 0x00 }, { FCML_OP_RM( FCML_REG_GPR, FCML_EOS_QWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ) | FCML_OA_W, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_RDRAND[] = {
	/* 0F C7 /6 RDRAND r16*/
	/* 0F C7 /6 RDRAND r32*/
	/* REX.W + 0F C7 /6 RDRAND r64*/
    { FCML_AMT_RDRAND, 0x0000, 0x00DBB000, { 0x0F, 0xC7, 0x00 }, { FCML_OP_RM( FCML_REG_GPR, FCML_EOS_EOSA, FCML_EOS_UNDEFINED, FCML_RMF_R ) | FCML_OA_W, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_RDTSCP[] = {
	/* 0F 01 F9 RDTSCP*/
    { FCML_AMT_SYSTEM, 0x0000, 0x00EC0000, { 0x0F, 0x01, 0xF9 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_RDTSC[] = {
	/* 0F 31 RDTSC*/
    { FCML_AMT_SYSTEM, 0x0000, 0x00D80000, { 0x0F, 0x31, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_RDPMC[] = {
	/* 0F 33 RDPMC*/
    { FCML_AMT_SYSTEM, 0x0000, 0x00D80000, { 0x0F, 0x33, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_RDMSR[] = {
	/* 0F 32 RDMSR*/
    { FCML_AMT_SYSTEM, 0x0000, 0x00D80000, { 0x0F, 0x32, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_RET[] = {
	/* C3 RET*/
    { FCML_AMT_GPI | FCML_AMT_CTI, 0x0000, 0x00C40080, { 0xC3, 0x00, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* C2 iw RET int16*/
    { FCML_AMT_GPI | FCML_AMT_CTI, 0x0000, 0x00C40080, { 0xC2, 0x00, 0x00 }, { FCML_OP_IW, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_RETF[] = {
	/* CB RET*/
    { FCML_AMT_GPI | FCML_AMT_CTI, 0x0000, 0x00C40000, { 0xCB, 0x00, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* CA iw RET int16*/
    { FCML_AMT_GPI | FCML_AMT_CTI, 0x0000, 0x00C40000, { 0xCA, 0x00, 0x00 }, { FCML_OP_IW, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_ROUNDPD[] = {
	/* 66 0F 3A 09 /r ib ROUNDPD xmm1,xmm2/m128,int8*/
    { FCML_AMT_SSE41_SIMD, 0x1000, 0x00EC8000, { 0x0F, 0x3A, 0x09 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_OP_128, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VROUNDPD[] = {
	/* VEX.128.66.0F3A.WIG 09 /r ib VROUNDPD xmm1,xmm2/m128,int8*/
	/* VEX.256.66.0F3A.WIG 09 /r ib VROUNDPD ymm1,ymm2/m256,int8*/
    { FCML_AMT_AVX_SIMD, 0x1080, 0x00EC8000, { 0x0F, 0x3A, 0x09 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_ROUNDPS[] = {
	/* 66 0F 3A 08 /r ib ROUNDPS xmm1,xmm2/m128,int8*/
    { FCML_AMT_SSE41_SIMD, 0x1000, 0x00EC8000, { 0x0F, 0x3A, 0x08 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_OP_128, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VROUNDPS[] = {
	/* VEX.128.66.0F3A.WIG 08 /r ib VROUNDPS xmm1,xmm2/m128,int8*/
	/* VEX.256.66.0F3A.WIG 08 /r ib VROUNDPS ymm1,ymm2/m256,int8*/
    { FCML_AMT_AVX_SIMD, 0x1080, 0x00EC8000, { 0x0F, 0x3A, 0x08 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_ROUNDSD[] = {
	/* 66 0F 3A 0B /r ib ROUNDSD xmm1,xmm2/m64,int8*/
    { FCML_AMT_SSE41_SIMD, 0x1000, 0x00EC8000, { 0x0F, 0x3A, 0x0B }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_OP_64, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VROUNDSD[] = {
	/* VEX.NDS.LIG.66.0F3A.WIG 0B /r ib VROUNDSD xmm1,xmm2,xmm3/m64,int8*/
    { FCML_AMT_AVX_SIMD, 0x10C0, 0x00EC8000, { 0x0F, 0x3A, 0x0B }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_64, FCML_OP_IB, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_ROUNDSS[] = {
	/* 66 0F 3A 0A /r ib ROUNDSS xmm1,xmm2/m32,int8*/
    { FCML_AMT_SSE41_SIMD, 0x1000, 0x00EC8000, { 0x0F, 0x3A, 0x0A }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_OP_32, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VROUNDSS[] = {
	/* VEX.NDS.LIG.66.0F3A.WIG 0A ib VROUNDSS xmm1,xmm2,xmm3/m32,int8*/
    { FCML_AMT_AVX_SIMD, 0x10C0, 0x00EC8000, { 0x0F, 0x3A, 0x0A }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_32, FCML_OP_IB, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_RSM[] = {
	/* 0F AA RSM NP Invalid Valid Resume operation of interrupted program.*/
    { FCML_AMT_SYSTEM, 0x0000, 0x00580000, { 0x0F, 0xAA, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VRSQRTPS[] = {
	/* VEX.128.0F.WIG 52 /r VRSQRTPS xmm1,xmm2/m128*/
	/* VEX.256.0F.WIG 52 /r VRSQRTPS ymm1,ymm2/m256*/
    { FCML_AMT_AVX_SIMD, 0x0080, 0x00D88000, { 0x0F, 0x52, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_RSQRTPS[] = {
	/* 0F 52 /r RSQRTPS xmm1,xmm2/m128*/
    { FCML_AMT_SSE_SIMD, 0x0000, 0x00D88000, { 0x0F, 0x52, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_RSQRTSS[] = {
	/* F3 0F 52 /r RSQRTSS xmm1,xmm2/m32*/
    { FCML_AMT_SSE_SIMD, 0x4000, 0x00D88000, { 0x0F, 0x52, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_OP_32, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VRSQRTSS[] = {
	/* VEX.NDS.LIG.F3.0F.WIG 52 /r VRSQRTSS xmm1,xmm2,xmm3/m32*/
    { FCML_AMT_AVX_SIMD, 0x40C0, 0x00D88000, { 0x0F, 0x52, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_32, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_SAHF[] = {
	/* It is valid in 64-bit mode only if CPUID.80000001H:ECX.LAHF-SAHF[bit 0] = 1.*/
	/* 9E SAHF*/
    { FCML_AMT_GPI, 0x0000, 0x00C40000, { 0x9E, 0x00, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_SAR[] = {
	/* D0 /7 SAR r/m8, 1*/
	/* REX + D0 /7 SAR r/m8*/
    { FCML_AMT_GPI, 0x0000, 0x00C5B800, { 0xD0, 0x00, 0x00 }, { FCML_OP_MODRM_RM_8_RW, FCML_OP_EXPLICIT_IB(1), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RM8 },
	/* D2 /7 SAR r/m8, CL MC Valid Valid Signed divide* r/m8 by 2, CL times.*/
	/* REX + D2 /7 SAR r/m8**, CL MC Valid N.E. Signed divide* r/m8 by 2, CL times.*/
    { FCML_AMT_GPI, 0x0000, 0x00C5B800, { 0xD2, 0x00, 0x00 }, { FCML_OP_MODRM_RM_8_RW, FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_CL, FCML_EOS_BYTE ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RM8 },
	/* C0 /7 ib SAR r/m8, int8 MI Valid Valid Signed divide* r/m8 by 2, int8 time.*/
	/* REX + C0 /7 ib SAR r/m8**, int8 MI Valid N.E. Signed divide* r/m8 by 2, int8 times.*/
    { FCML_AMT_GPI, 0x0000, 0x00C5B800, { 0xC0, 0x00, 0x00 }, { FCML_OP_MODRM_RM_8_RW, FCML_OP_IB, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RM8_IMM8 },
	/* D1 /7 SAR r/m16,1 M1 Valid Valid Signed divide* r/m16 by 2, once.*/
	/* D1 /7 SAR r/m32, 1 M1 Valid Valid Signed divide* r/m32 by 2, once.*/
	/* REX.W + D1 /7 SAR r/m64, 1 M1 Valid N.E. Signed divide* r/m64 by 2, once.*/
    { FCML_AMT_GPI, 0x0000, 0x00C5B800, { 0xD1, 0x00, 0x00 }, { FCML_OP_MODRM_RM_RW, FCML_OP_EXPLICIT_IB(1), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RMO },
	/* D3 /7 SAR r/m16, CL MC Valid Valid Signed divide* r/m16 by 2, CL times.*/
	/* D3 /7 SAR r/m32, CL MC Valid Valid Signed divide* r/m32 by 2, CL times.*/
	/* REX.W + D3 /7 SAR r/m64, CL MC Valid N.E. Signed divide* r/m64 by 2, CL times.*/
    { FCML_AMT_GPI, 0x0000, 0x00C5B800, { 0xD3, 0x00, 0x00 }, { FCML_OP_MODRM_RM_RW, FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_CL, FCML_EOS_BYTE ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RMO },
	/* C1 /7 ib SAR r/m16, int8 MI Valid Valid Signed divide* r/m16 by 2, int8 times.*/
	/* C1 /7 ib SAR r/m32, int8 MI Valid Valid Signed divide* r/m32 by 2, int8 times.*/
	/* REX.W + C1 /7 ib SAR r/m64, int8 MI Valid N.E. Signed divide* r/m64 by 2, int8 times*/
    { FCML_AMT_GPI, 0x0000, 0x00C5B800, { 0xC1, 0x00, 0x00 }, { FCML_OP_MODRM_RM_RW, FCML_OP_IB, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RMO_IMM8 }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_SHL_SAL[] = {
	/* D0 /4 SHL/SAL r/m8,1*/
	/* REX + D0 /4 SHL/SAL r/m8,1*/
    { FCML_AMT_GPI, 0x0000, 0x00C5A000, { 0xD0, 0x00, 0x00 }, { FCML_OP_MODRM_RM_8_RW, FCML_OP_EXPLICIT_IB(1), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RM8 },
	/* D2 /4 SHL/SAL r/m8,CL*/
	/* REX + D2 /4 SHL/SAL r/m8,CL*/
    { FCML_AMT_GPI, 0x0000, 0x00C5A000, { 0xD2, 0x00, 0x00 }, { FCML_OP_MODRM_RM_8_RW, FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_CL, FCML_EOS_BYTE ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RM8 },
	/* C0 /4 ib SHL/SAL r/m8,int8*/
	/* REX + C0 /4 ib SHL/SAL r/m8,int8*/
    { FCML_AMT_GPI, 0x0000, 0x00C5A000, { 0xC0, 0x00, 0x00 }, { FCML_OP_MODRM_RM_8_RW, FCML_OP_IB, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RM8_IMM8 },
	/* D1 /4 SHL/SAL r/m16,1*/
	/* D1 /4 SHL/SAL r/m32,1*/
	/* REX.W + D1 /4 SHL/SAL r/m64,1*/
    { FCML_AMT_GPI, 0x0000, 0x00C5A000, { 0xD1, 0x00, 0x00 }, { FCML_OP_MODRM_RM_RW, FCML_OP_EXPLICIT_IB(1), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RMO },
	/* D3 /4 SHL/SAL r/m16,CL*/
	/* D3 /4 SHL/SAL r/m32,CL*/
	/* REX.W + D3 /4 SHL/SAL r/m64,CL*/
    { FCML_AMT_GPI, 0x0000, 0x00C5A000, { 0xD3, 0x00, 0x00 }, { FCML_OP_MODRM_RM_RW, FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_CL, FCML_EOS_BYTE ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RMO },
	/* C1 /4 ib SHL/SAL r/m16,int8*/
	/* C1 /4 ib SHL/SAL r/m32,int8*/
	/* REX.W + C1 /4 ib SHL/SAL r/m64,int8*/
    { FCML_AMT_GPI, 0x0000, 0x00C5A000, { 0xC1, 0x00, 0x00 }, { FCML_OP_MODRM_RM_RW, FCML_OP_IB, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RMO_IMM8 }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_SHR[] = {
	/* D0 /5 SHR r/m8,1*/
	/* REX + D0 /5 SHR r/m8,1*/
    { FCML_AMT_GPI, 0x0000, 0x00C5A800, { 0xD0, 0x00, 0x00 }, { FCML_OP_MODRM_RM_8_RW, FCML_OP_EXPLICIT_IB(1), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RM8 },
	/* D2 /5 SHR r/m8,CL*/
	/* REX + D2 /5 SHR r/m8,CL*/
    { FCML_AMT_GPI, 0x0000, 0x00C5A800, { 0xD2, 0x00, 0x00 }, { FCML_OP_MODRM_RM_8_RW, FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_CL, FCML_EOS_BYTE ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RM8 },
	/* C0 /5 ib SHR r/m8,int8*/
	/* REX + C0 /5 ib SHR r/m8,int8*/
    { FCML_AMT_GPI, 0x0000, 0x00C5A800, { 0xC0, 0x00, 0x00 }, { FCML_OP_MODRM_RM_8_RW, FCML_OP_IB, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RM8_IMM8 },
	/* D1 /5 SHR r/m16,1*/
	/* D1 /5 SHR r/m32,1*/
	/* REX.W + D1 /5 SHR r/m64,1*/
    { FCML_AMT_GPI, 0x0000, 0x00C5A800, { 0xD1, 0x00, 0x00 }, { FCML_OP_MODRM_RM_RW, FCML_OP_EXPLICIT_IB(1), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RMO },
	/* D3 /5 SHR r/m16,CL*/
	/* D3 /5 SHR r/m32,CL*/
	/* REX.W + D3 /5 SHR r/m64,CL*/
    { FCML_AMT_GPI, 0x0000, 0x00C5A800, { 0xD3, 0x00, 0x00 }, { FCML_OP_MODRM_RM_RW, FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_CL, FCML_EOS_BYTE ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RMO },
	/* C1 /5 ib SHR r/m16,int8*/
	/* C1 /5 ib SHR r/m32,int8*/
	/* REX.W + C1 /5 ib SHR r/m64,int8*/
    { FCML_AMT_GPI, 0x0000, 0x00C5A800, { 0xC1, 0x00, 0x00 }, { FCML_OP_MODRM_RM_RW, FCML_OP_IB, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RMO_IMM8 }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_SBB[] = {
	/* 1C ib SBB AL,int8*/
    { FCML_AMT_GPI, 0x0000, 0x00C40002, { 0x1C, 0x00, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_AL, FCML_EOS_BYTE ) | FCML_OA_W, FCML_OP_IB, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_ER8_IMM8 },
	/* 1D iw SBB AX,int16*/
	/* 1D id SBB EAX,int32*/
	/* REX.W + 1D id SBB RAX,int32*/
    { FCML_AMT_GPI, 0x0000, 0x00C40002, { 0x1D, 0x00, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_AL, FCML_EOS_EOSA ) | FCML_OA_W, FCML_OP_EX_EOSA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_ERO_IMMO },
	/* 80 /3 ib SBB r/m8,int8*/
	/* REX + 80 /3 ib SBB r/m8,int8*/
    { FCML_AMT_GPI, 0x0807, 0x00C59806, { 0x80, 0x00, 0x00 }, { FCML_OP_MODRM_RM_8_W, FCML_OP_IB, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RM8_IMM8 },
	/* 81 /3 iw SBB r/m16,int16*/
	/* 81 /3 id SBB r/m32,int32*/
	/* REX.W + 81 /3 id SBB r/m64,int32*/
    { FCML_AMT_GPI, 0x0807, 0x00C59806, { 0x81, 0x00, 0x00 }, { FCML_OP_MODRM_RM_W, FCML_OP_EX_EOSA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RMO_IMMO },
	/* 83 /3 ib SBB r/m16,int8*/
	/* 83 /3 ib SBB r/m32,int8*/
	/* REX.W + 83 /3 ib SBB r/m64,int8*/
    { FCML_AMT_GPI, 0x0807, 0x00C59806, { 0x83, 0x00, 0x00 }, { FCML_OP_MODRM_RM_W, FCML_OP_IB_EX_EOSA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RMO_IMM8 },
	/* 18 /r SBB r/m8,r8*/
	/* REX + 18 /r SBB r/m8,r8*/
    { FCML_AMT_GPI, 0x0807, 0x00C48002, { 0x18, 0x00, 0x00 }, { FCML_OP_MODRM_RM_OP_8_W, FCML_OP_MODRM_R_8, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RM8_R8 },
	/* 19 /r SBB r/m16,r16*/
	/* 19 /r SBB r/m32,r32*/
	/* REX.W + 19 /r SBB r/m64,r64*/
    { FCML_AMT_GPI, 0x0807, 0x00C48002, { 0x19, 0x00, 0x00 }, { FCML_OP_MODRM_RM_OP_W, FCML_OP_MODRM_R, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RMO_RO },
	/* 1A /r SBB r8,r/m8*/
	/* REX + 1A /r SBB r8,r/m8*/
    { FCML_AMT_GPI, 0x0000, 0x00C48002, { 0x1A, 0x00, 0x00 }, { FCML_OP_MODRM_R_8_W, FCML_OP_MODRM_RM_OP_8, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_R8_RM8 },
	/* 1B /r SBB r16,r/m16*/
	/* 1B /r SBB r32,r/m32*/
	/* REX.W + 1B /r SBB r64,r/m64*/
    { FCML_AMT_GPI, 0x0000, 0x00C48002, { 0x1B, 0x00, 0x00 }, { FCML_OP_MODRM_R_W, FCML_OP_MODRM_RM_OP, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RO_RMO }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_SCAS[] = {
	/* AE SCAS m8 NP Valid Valid Compare AL with byte at ES:(E)DI or RDI, then set status flags.**/
    { FCML_AMT_GPI, 0x0002, 0x00C40000, { 0xAE, 0x00, 0x00 }, { FCML_OP_EXPLICIT_GPS_REG_ADDRESSING( FCML_REG_DI, FCML_EOS_BYTE, FCML_SEG_ENCODE_REGISTER( FCML_REG_ES, FCML_SEG_DENY_OVERRIDE ) ), FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RM8 },
	/* AF SCAS m16 NP Valid Valid Compare AX with word at ES:(E)DI or RDI, then set status flags.**/
	/* AF SCAS m32 NP Valid Valid Compare EAX with doubleword at ES(E)DI or RDI then set status flags.**/
	/* REX.W + AF SCAS m64 NP Valid N.E. Compare RAX with quadword at RDI or EDI then set status flags.*/
    { FCML_AMT_GPI, 0x0002, 0x00C40000, { 0xAF, 0x00, 0x00 }, { FCML_OP_EXPLICIT_GPS_REG_ADDRESSING( FCML_REG_DI, FCML_EOS_EOSA,FCML_SEG_ENCODE_REGISTER( FCML_REG_ES, FCML_SEG_DENY_OVERRIDE ) ), FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RMO }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_SETCC[] = {
	/* 0F 97 SETA r/m8 M Valid Valid Set byte if above (CF=0 and ZF=0).*/
	/* REX + 0F 97 SETA r/m8**/
    { FCML_AMT_GPI, 0x0000, 0x00D88040, { 0x0F, 0x90, 0x00 }, { FCML_OP_MODRM_RM_OP_8_W, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_SFENCE[] = {
    { FCML_AMT_SSE, 0x0000, 0x00EC0000, { 0x0F, 0xAE, 0xF8 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_SGDT[] = {
	/* 0F 01 /0 SGDT m*/
    { FCML_AMT_SYSTEM, 0x0000, 0x00D98000, { 0x0F, 0x01, 0x00 }, { FCML_OP_MODRM_M_UNDEF, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_SHLD[] = {
	/* 0F A4 SHLD r/m16,r16,int8 MRI Valid Valid Shift r/m16 to left int8 places while shifting bits from r16 in from the right.*/
	/* 0F A4 SHLD r/m32,r32,int8 MRI Valid Valid Shift r/m32 to left int8 places while shifting bits from r32 in from the right.*/
	/* REX.W + 0F A4 SHLD r/m64,r64, int8 MRI Valid N.E. Shift r/m64 to left int8 places while shifting bits from r64 in from the right.*/
    { FCML_AMT_GPI, 0x0000, 0x00D88000, { 0x0F, 0xA4, 0x00 }, { FCML_OP_MODRM_RM_OP_W, FCML_OP_MODRM_R, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* 0F A5 SHLD r/m16,r16,CL MRC Valid Valid Shift r/m16 to left CL places while shifting bits from r16 in from the right.*/
	/* 0F A5 SHLD r/m32,r32,CL MRC Valid Valid Shift r/m32 to left CL places while shifting bits from r32 in from the right.*/
	/* REX.W + 0F A5 SHLD r/m64,r64,CL MRC Valid N.E. Shift r/m64 to left CL places while shifting bits from r64 in from the right.*/
    { FCML_AMT_GPI, 0x0000, 0x00D88000, { 0x0F, 0xA5, 0x00 }, { FCML_OP_MODRM_RM_OP_W, FCML_OP_MODRM_R, FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_CL, FCML_EOS_BYTE ), FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_SHRD[] = {
	/* 0F AC SHRD r/m16, r16, int8 MRI Valid Valid Shift r/m16 to right int8 places while shifting bits from r16 in from the left.*/
	/* 0F AC SHRD r/m32, r32, int8 MRI Valid Valid Shift r/m32 to right int8 places while shifting bits from r32 in from the left.*/
	/* REX.W + 0F AC SHRD r/m64, r64, int8 MRI Valid N.E. Shift r/m64 to right int8 places while shifting bits from r64 in from the left.*/
    { FCML_AMT_GPI, 0x0000, 0x00D88000, { 0x0F, 0xAC, 0x00 }, { FCML_OP_MODRM_RM_OP_W, FCML_OP_MODRM_R,FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* 0F AD SHRD r/m16, r16, CL MRC Valid Valid Shift r/m16 to right CL places while shifting bits from r16 in from the left.*/
	/* 0F AD SHRD r/m32, r32, CL MRC Valid Valid Shift r/m32 to right CL places while shifting bits from r32 in from the left.*/
	/* REX.W + 0F AD SHRD r/m64, r64, CL MRC Valid N.E. Shift r/m64 to right CL places while shifting bits from r64 in from the left.*/
    { FCML_AMT_GPI, 0x0000, 0x00D88000, { 0x0F, 0xAD, 0x00 }, { FCML_OP_MODRM_RM_OP_W, FCML_OP_MODRM_R,FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_CL, FCML_EOS_BYTE ), FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_SKINIT[] = {
	/* SKINIT EAX 0F 01 DE Secure initialization and jump, with attestation.*/
    { FCML_AMT_SVM, 0x0000, 0x00EC0000, { 0x0F, 0x01, 0xDE }, { FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_EAX, FCML_EOS_DWORD ), FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
    { FCML_AMT_SVM, 0x0000, 0x00EC0000, { 0x0F, 0x01, 0xDE }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_SLWPCB[] = {
	/* SLWPCB reg32 8F RXB.09 0.1111.0.00 12 /1*/
    { FCML_AMT_LWP, 0x0450, 0x00DB8800, { 0x09, 0x12, 0x00 }, { FCML_OP_RM( FCML_REG_GPR, FCML_EOS_DWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ) | FCML_OA_W, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* SLWPCB reg64 8F RXB.09 1.1111.0.00 12 /1*/
    { FCML_AMT_LWP, 0x0448, 0x00DB8800, { 0x09, 0x12, 0x00 }, { FCML_OP_RM( FCML_REG_GPR, FCML_EOS_QWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ) | FCML_OA_W, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_SHUFPD[] = {
	/* 66 0F C6 /r ib SHUFPD xmm1, xmm2/m128, int8 RMI V/V SSE2 Shuffle packed double-precision floatingpoint values selected by int8 from xmm1 and xmm2/m128 to xmm1.*/
    { FCML_AMT_SSE2_SIMD, 0x1000, 0x00D88000, { 0x0F, 0xC6, 0x00 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_128, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VSHUFPD[] = {
	/* VEX.NDS.128.66.0F.WIG C6 /r ib VSHUFPD xmm1, xmm2, xmm3/m128, int8 RVMI V/V AVX Shuffle Packed double-precision floatingpoint values selected by int8 from xmm2 and xmm3/mem.*/
	/* VEX.NDS.256.66.0F.WIG C6 /r ib VSHUFPD ymm1, ymm2, ymm3/m256, int8 RVMI V/V AVX Shuffle Packed double-precision floatingpoint values selected by int8 from ymm2 and ymm3/mem.*/
    { FCML_AMT_AVX_SIMD, 0x1080, 0x00D88000, { 0x0F, 0xC6, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_OP_IB, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_SHUFPS[] = {
	/* 0F C6 /r ib SHUFPS xmm1, xmm2/m128, int8 RMI V/V SSE Shuffle packed single-precision floating-point values selected by int8 from xmm1 and xmm1/m128 to xmm1.*/
    { FCML_AMT_SSE_SIMD, 0x0000, 0x00D88000, { 0x0F, 0xC6, 0x00 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_128, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VSHUFPS[] = {
	/* VEX.NDS.128.0F.WIG C6 /r ib VSHUFPS xmm1, xmm2, xmm3/m128, int8 RVMI V/V AVX Shuffle Packed single-precision floating-point values selected by int8 from xmm2 and xmm3/mem.*/
	/* VEX.NDS.256.0F.WIG C6 /r ib VSHUFPS ymm1, ymm2, ymm3/m256, int8 RVMI V/V AVX Shuffle Packed single-precision floating-point values selected by int8 from ymm2 and ymm3/mem.*/
    { FCML_AMT_AVX_SIMD, 0x0080, 0x00D88000, { 0x0F, 0xC6, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_OP_IB, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_SIDT[] = {
	/* 0F 01 /1 SIDT m M Valid Valid Store IDTR to m.*/
    { FCML_AMT_SYSTEM, 0x0000, 0x00D98800, { 0x0F, 0x01, 0x00 }, { FCML_OP_MODRM_M_UNDEF, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_SLDT[] = {
	/* 0F 00 /0 SLDT r/m16 M Valid Valid Stores segment selector from LDTR in r/m16.*/
	/* REX.W + 0F 00 /0 SLDT r64/m16 M Valid Valid Stores segment selector from LDTR in r64/m16.*/
    { FCML_AMT_SYSTEM, 0x0000, 0x00D98000, { 0x0F, 0x00, 0x00 }, { FCML_OP_RM( FCML_REG_GPR, FCML_EOS_EOSA, FCML_EOS_WORD | FCML_EOS_OPT, FCML_RMF_RM ) | FCML_OA_W, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_SMSW[] = {
	/* 0F 01 /4 SMSW r/m16 M Valid Valid Store machine status word to r/m16.*/
	/* 0F 01 /4 SMSW r32/m16 M Valid Valid Store machine status word in low-order 16 bits of r32/m16; high-order 16 bits of r32 are undefined.*/
	/* REX.W + 0F 01 /4 SMSW r64/m16 M Valid Valid Store machine status word in low-order 16 bits of r64/m16; high-order 16 bits of r32 are undefined.*/
    { FCML_AMT_SYSTEM, 0x0000, 0x00D9A000, { 0x0F, 0x01, 0x00 }, { FCML_OP_RM( FCML_REG_GPR, FCML_EOS_EOSA, FCML_EOS_WORD | FCML_EOS_OPT, FCML_RMF_RM ) | FCML_OA_W, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_SQRTPD[] = {
	/* 66 0F 51 /r SQRTPD xmm1,xmm2/m128*/
    { FCML_AMT_SSE2_SIMD, 0x1000, 0x00D88000, { 0x0F, 0x51, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VSQRTPD[] = {
	/* VEX.128.66.0F.WIG 51 /r VSQRTPD xmm1,xmm2/m128*/
	/* VEX.256.66.0F.WIG 51 /r VSQRTPD ymm1,ymm2/m256*/
    { FCML_AMT_AVX_SIMD, 0x1080, 0x00D88000, { 0x0F, 0x51, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_SQRTPS[] = {
	/* 0F 51 /r SQRTPS xmm1,xmm2/m128 RM V/V SSE Computes square roots of the packed singleprecision floating-point values in xmm2/m128 and stores the results in xmm1.*/
    { FCML_AMT_SSE_SIMD, 0x0000, 0x00D88000, { 0x0F, 0x51, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VSQRTPS[] = {
	/* VEX.128.0F.WIG 51 /r VSQRTPS xmm1,xmm2/m128 RM V/V AVX Computes Square Roots of the packed singleprecision floating-point values in xmm2/m128 and stores the result in xmm1.*/
	/* VEX.256.0F.WIG 51 /r VSQRTPS ymm1,ymm2/m256 RM V/V AVX Computes Square Roots of the packed singleprecision floating-point values in ymm2/m256 and stores the result in ymm1.*/
    { FCML_AMT_AVX_SIMD, 0x0080, 0x00D88000, { 0x0F, 0x51, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_SQRTSD[] = {
	/* F2 0F 51 /r SQRTSD xmm1,xmm2/m64 RM V/V SSE2 Computes square root of the low doubleprecision floating-point value in xmm2/m64 and stores the results in xmm1.*/
    { FCML_AMT_SSE2_SIMD, 0x2000, 0x00D88000, { 0x0F, 0x51, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_OP_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VSQRTSD[] = {
	/* VEX.NDS.LIG.F2.0F.WIG 51 /r VSQRTSD xmm1,xmm2,xmm3/m64 RVM V/V AVX Computes square root of the low doubleprecision floating point value in xmm3/m64 and stores the results in xmm2. Also, upper double precision floating-point value (bits[127:64]) from xmm2 is copied to xmm1[127:64].*/
    { FCML_AMT_AVX_SIMD, 0x20C0, 0x00D88000, { 0x0F, 0x51, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_64, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_SQRTSS[] = {
	/* F3 0F 51 /r SQRTSS xmm1, xmm2/m32 RM V/V SSE Computes square root of the low singleprecision floating-point value in xmm2/m32 and stores the results in xmm1.*/
    { FCML_AMT_SSE_SIMD, 0x4000, 0x00D88000, { 0x0F, 0x51, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_OP_32, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VSQRTSS[] = {
	/* VEX.NDS.LIG.F3.0F.WIG 51 VSQRTSS xmm1, xmm2, xmm3/m32 RVM V/V AVX Computes square root of the low singleprecision floating-point value in xmm3/m32 and stores the results in xmm1. Also, upper single precision floating-point values (bits[127:32]) from xmm2 are copied to xmm1[127:32].*/
    { FCML_AMT_AVX_SIMD, 0x40C0, 0x00D88000, { 0x0F, 0x51, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_32, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_STC[] = {
	/* F9 STC NP Valid Valid Set CF flag.*/
    { FCML_AMT_GPI, 0x0000, 0x00C40000, { 0xF9, 0x00, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_STD[] = {
	/* FD STD NP Valid Valid Set DF flag.*/
    { FCML_AMT_GPI, 0x0000, 0x00C40000, { 0xFD, 0x00, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_STGI[] = {
	/* STGI 0F 01 DC Sets the global interrupt flag (GIF).*/
    { FCML_AMT_SVM, 0x0000, 0x00EC0000, { 0x0F, 0x01, 0xDC }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_STI[] = {
	/* FB STI NP Valid Valid Set interrupt flag; external, maskable interrupts enabled at the end of the next instruction.*/
    { FCML_AMT_GPI, 0x0000, 0x00C40000, { 0xFB, 0x00, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_STMXCSR[] = {
	/* 0F AE /3 STMXCSR m32 M V/V SSE Store contents of MXCSR register to m32.*/
    { FCML_AMT_SSE, 0x0000, 0x00D99800, { 0x0F, 0xAE, 0x00 }, { FCML_OP_MODRM_M_OP_32_W, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VSTMXCSR[] = {
	/* VEX.LZ.0F.WIG AE /3 VSTMXCSR m32 M V/V AVX Store contents of MXCSR register to m32.*/
    { FCML_AMT_AVX, 0x00C0, 0x00D99800, { 0x0F, 0xAE, 0x00 }, { FCML_OP_MODRM_M_OP_32_W, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_STOS[] = {
	/* AA STOS m8 NA Valid Valid For legacy mode, store AL at address ES:(E)DI; For 64-bit mode store AL at address RDI or EDI.*/
    { FCML_AMT_GPI, 0x0004, 0x00C40000, { 0xAA, 0x00, 0x00 }, { FCML_OP_EXPLICIT_GPS_REG_ADDRESSING( FCML_REG_DI, FCML_EOS_BYTE, FCML_SEG_ENCODE_REGISTER( FCML_REG_ES, FCML_SEG_DENY_OVERRIDE ) ) | FCML_OA_W, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RM8 },
	/* AB STOS m16 NA Valid Valid For legacy mode, store AX at address ES:(E)DI; For 64-bit mode store AX at address RDI or EDI.*/
	/* AB STOS m32 NA Valid Valid For legacy mode, store EAX at address ES:(E)DI; For 64-bit mode store EAX at address RDI or EDI.*/
	/* REX.W + AB STOS m64 NA Valid N.E. Store RAX at address RDI or EDI.*/
    { FCML_AMT_GPI, 0x0004, 0x00C40000, { 0xAB, 0x00, 0x00 }, { FCML_OP_EXPLICIT_GPS_REG_ADDRESSING( FCML_REG_DI, FCML_EOS_EOSA,FCML_SEG_ENCODE_REGISTER( FCML_REG_ES, FCML_SEG_DENY_OVERRIDE ) ) | FCML_OA_W, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RMO }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_STR[] = {
	/* 0F 00 /1 STR r/m16 M Valid Valid Stores segment selector from TR in r/m16.*/
    { FCML_AMT_SYSTEM, 0x0000, 0x00D98800, { 0x0F, 0x00, 0x00 }, { FCML_OP_MODRM_RM_OP_16_W, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_SUB[] = {
	/* 2C ib SUB AL, int8 I Valid Valid Subtract int8 from AL.*/
    { FCML_AMT_GPI, 0x0000, 0x00C40002, { 0x2C, 0x00, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_AL, FCML_EOS_BYTE ) | FCML_OA_W, FCML_OP_IB, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_ER8_IMM8 },
	/* 2D iw SUB AX, int16 I Valid Valid Subtract int16 from AX.*/
	/* 2D id SUB EAX, int32 I Valid Valid Subtract int32 from EAX.*/
	/* REX.W + 2D id SUB RAX, int32 I Valid N.E. Subtract int32 sign-extended to 64-bits from RAX.*/
    { FCML_AMT_GPI, 0x0000, 0x00C40002, { 0x2D, 0x00, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_AL, FCML_EOS_EOSA ) | FCML_OA_W, FCML_OP_EX_EOSA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_ERO_IMMO },
	/* 80 /5 ib SUB r/m8, int8 MI Valid Valid Subtract int8 from r/m8.*/
	/* REX + 80 /5 ib SUB r/m8*, int8 MI Valid N.E. Subtract int8 from r/m8.*/
    { FCML_AMT_GPI, 0x0807, 0x00C5A806, { 0x80, 0x00, 0x00 }, { FCML_OP_MODRM_RM_8_W, FCML_OP_IB, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RM8_IMM8 },
	/* 81 /5 iw SUB r/m16, int16 MI Valid Valid Subtract int16 from r/m16.*/
	/* 81 /5 id SUB r/m32, int32 MI Valid Valid Subtract int32 from r/m32.*/
	/* REX.W + 81 /5 id SUB r/m64, int32 MI Valid N.E. Subtract int32 sign-extended to 64-bits from r/m64.*/
    { FCML_AMT_GPI, 0x0807, 0x00C5A806, { 0x81, 0x00, 0x00 }, { FCML_OP_MODRM_RM_W, FCML_OP_EX_EOSA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RMO_IMMO },
	/* 83 /5 ib SUB r/m16, int8 MI Valid Valid Subtract sign-extended int8 from r/m16.*/
	/* 83 /5 ib SUB r/m32, int8 MI Valid Valid Subtract sign-extended int8 from r/m32.*/
	/* REX.W + 83 /5 ib SUB r/m64, int8 MI Valid N.E. Subtract sign-extended int8 from r/m64.*/
    { FCML_AMT_GPI, 0x0807, 0x00C5A806, { 0x83, 0x00, 0x00 }, { FCML_OP_MODRM_RM_W, FCML_OP_IB_EX_EOSA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RMO_IMM8 },
	/* 28 /r SUB r/m8, r8 MR Valid Valid Subtract r8 from r/m8.*/
	/* REX + 28 /r SUB r/m8*, r8* MR Valid N.E. Subtract r8 from r/m8.*/
    { FCML_AMT_GPI, 0x0807, 0x00C48002, { 0x28, 0x00, 0x00 }, { FCML_OP_MODRM_RM_OP_8_W, FCML_OP_MODRM_R_8, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RM8_R8 },
	/* 29 /r SUB r/m16, r16 MR Valid Valid Subtract r16 from r/m16.*/
	/* 29 /r SUB r/m32, r32 MR Valid Valid Subtract r32 from r/m32.*/
	/* REX.W + 29 /r SUB r/m64, r32 MR Valid N.E. Subtract r64 from r/m64.*/
    { FCML_AMT_GPI, 0x0807, 0x00C48002, { 0x29, 0x00, 0x00 }, { FCML_OP_MODRM_RM_OP_W, FCML_OP_MODRM_R, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RMO_RO },
	/* 2A /r SUB r8, r/m8 RM Valid Valid Subtract r/m8 from r8.*/
	/* REX + 2A /r SUB r8*, r/m8* RM Valid N.E. Subtract r/m8 from r8.*/
    { FCML_AMT_GPI, 0x0000, 0x00C48002, { 0x2A, 0x00, 0x00 }, { FCML_OP_MODRM_R_8_W, FCML_OP_MODRM_RM_OP_8, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_R8_RM8 },
	/* 2B /r SUB r16, r/m16 RM Valid Valid Subtract r/m16 from r16.*/
	/* 2B /r SUB r32, r/m32 RM Valid Valid Subtract r/m32 from r32.*/
	/* REX.W + 2B /r SUB r64, r/m64 RM Valid N.E. Subtract r/m64 from r64.*/
    { FCML_AMT_GPI, 0x0000, 0x00C48002, { 0x2B, 0x00, 0x00 }, { FCML_OP_MODRM_R_W, FCML_OP_MODRM_RM_OP, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RO_RMO }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_SUBPD[] = {
	/* 66 0F 5C /r SUBPD xmm1,xmm2/m128 RM V/V SSE2 Subtract packed double-precision floatingpoint values in xmm2/m128 from xmm1.*/
    { FCML_AMT_SSE2_SIMD, 0x1000, 0x00D88000, { 0x0F, 0x5C, 0x00 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VSUBPD[] = {
	/* VEX.NDS.128.66.0F.WIG 5C /r VSUBPD xmm1,xmm2,xmm3/m128 RVM V/V AVX Subtract packed double-precision floatingpoint values in xmm3/mem from xmm2 and stores result in xmm1.*/
	/* VEX.NDS.256.66.0F.WIG 5C /r VSUBPD ymm1,ymm2,ymm3/m256 RVM V/V AVX Subtract packed double-precision floatingpoint values in ymm3/mem from ymm2 and stores result in ymm1.*/
    { FCML_AMT_AVX_SIMD, 0x1080, 0x00D88000, { 0x0F, 0x5C, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_SUBPS[] = {
	/* 0F 5C /r SUBPS xmm1,xmm2/m128 RM V/V SSE Subtract packed single-precision floating-point values in xmm2/mem from xmm1.*/
    { FCML_AMT_SSE_SIMD, 0x0000, 0x00D88000, { 0x0F, 0x5C, 0x00 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VSUBPS[] = {
	/* VEX.NDS.128.0F.WIG 5C /r VSUBPS xmm1,xmm2,xmm3/m128 RVM V/V AVX Subtract packed single-precision floating-point values in xmm3/mem from xmm2 and stores result in xmm1.*/
	/* VEX.NDS.256.0F.WIG 5C /r VSUBPS ymm1,ymm2,ymm3/m256 RVM V/V AVX Subtract packed single-precision floating-point values in ymm3/mem from ymm2 and stores result in ymm1.*/
    { FCML_AMT_AVX_SIMD, 0x0080, 0x00D88000, { 0x0F, 0x5C, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_SUBSD[] = {
	/* F2 0F 5C /r SUBSD xmm1,xmm2/m64 RM V/V SSE2 Subtracts the low double-precision floatingpoint values in xmm2/mem64 from xmm1.*/
    { FCML_AMT_SSE2_SIMD, 0x2000, 0x00D88000, { 0x0F, 0x5C, 0x00 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VSUBSD[] = {
	/* VEX.NDS.LIG.F2.0F.WIG 5C /r VSUBSD xmm1,xmm2,xmm3/m64 RVM V/V AVX Subtract the low double-precision floatingpoint value in xmm3/mem from xmm2 and store the result in xmm1.*/
    { FCML_AMT_AVX_SIMD, 0x20C0, 0x00D88000, { 0x0F, 0x5C, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_64, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_SUBSS[] = {
	/* F3 0F 5C /r SUBSS xmm1,xmm2/m32*/
    { FCML_AMT_SSE_SIMD, 0x4000, 0x00D88000, { 0x0F, 0x5C, 0x00 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_32, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VSUBSS[] = {
	/* VEX.NDS.LIG.F3.0F.WIG 5C /r VSUBSS xmm1,xmm2,xmm3/m32*/
    { FCML_AMT_AVX_SIMD, 0x40C0, 0x00D88000, { 0x0F, 0x5C, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_32, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_SWAPGS[] = {
	/* 0F 01 F8 SWAPGS NP Valid Invalid Exchanges the current GS base register value with the value contained in MSR address C0000102H.*/
    { FCML_AMT_SYSTEM, 0x0000, 0x00AC0000, { 0x0F, 0x01, 0xF8 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_SYSCALL[] = {
	/* 0F 05 SYSCALL NP Valid Invalid Fast call to privilege level 0 system procedures.*/
    { FCML_AMT_SYSTEM, 0x0000, 0x00980000, { 0x0F, 0x05, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_SYSENTER[] = {
	/* 0F 34 SYSENTER NP Valid Valid Fast call to privilege level 0 system procedures.*/
    { FCML_AMT_SYSTEM, 0x0000, 0x00D80000, { 0x0F, 0x34, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_SYSEXIT[] = {
	/* 0F 35 SYSEXIT NP Valid Valid Fast return to privilege level 3 user code.*/
	/* REX.W + 0F 35 SYSEXIT NP Valid Valid Fast return to 64-bit mode privilege level 3 user code.*/
    { FCML_AMT_SYSTEM, 0x0000, 0x00D80000, { 0x0F, 0x35, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_SYSRET[] = {
	/* 0F 07 SYSRET NP Valid Invalid Return to compatibility mode from fast system call*/
	/* REX.W + 0F 07 SYSRET NP Valid Invalid Return to 64-bit mode from fast system call*/
    { FCML_AMT_SYSTEM, 0x0000, 0x00980000, { 0x0F, 0x07, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_T1MSKC[] = {
    /* T1MSKC reg32, reg/mem32 8F RXB.09 0.dest.0.00 01 /7*/
    { FCML_AMT_TBM, 0x0450, 0x00D9B800, { 0x09, 0x01, 0x00 }, { FCML_OP_VEX_VVVV_REG( FCML_REG_GPR, FCML_EOS_DWORD ) | FCML_OA_W, FCML_OP_MODRM_RM_OP_32, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
    /* T1MSKC reg64, reg/mem64 8F RXB.09 1.dest.0.00 01 /7*/
    { FCML_AMT_TBM, 0x0448, 0x00D9B800, { 0x09, 0x01, 0x00 }, { FCML_OP_VEX_VVVV_REG( FCML_REG_GPR, FCML_EOS_QWORD ) | FCML_OA_W, FCML_OP_MODRM_RM_OP_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_TEST[] = {
	/* A8 ib TEST AL, int8 I Valid Valid AND int8 with AL; set SF, ZF, PF according to result.*/
    { FCML_AMT_GPI, 0x0000, 0x00C40000, { 0xA8, 0x00, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_AL, FCML_EOS_BYTE ) | FCML_OA_W, FCML_OP_IB, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_ER8_IMM8 },
	/* A9 iw TEST AX, int16 I Valid Valid AND int16 with AX; set SF, ZF, PF according to result.*/
	/* A9 id TEST EAX, int32 I Valid Valid AND int32 with EAX; set SF, ZF, PF according to result.*/
	/* REX.W + A9 id TEST RAX, int32 I Valid N.E. AND int32 sign-extended to 64-bits with RAX; set SF, ZF, PF according to result.*/
    { FCML_AMT_GPI, 0x0000, 0x00C40000, { 0xA9, 0x00, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_AL, FCML_EOS_EOSA ) | FCML_OA_W, FCML_OP_EX_EOSA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_ERO_IMMO },
	/* F6 /0 ib TEST r/m8, int8 MI Valid Valid AND int8 with r/m8; set SF, ZF, PF according to result.*/
	/* REX + F6 /0 ib TEST r/m8*, int8 MI Valid N.E. AND int8 with r/m8; set SF, ZF, PF according to result.*/
    { FCML_AMT_GPI, 0x0000, 0x00C58000, { 0xF6, 0x00, 0x00 }, { FCML_OP_MODRM_RM_8_W, FCML_OP_IB, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RM8_IMM8 },
	/* F7 /0 iw TEST r/m16, int16 MI Valid Valid AND int16 with r/m16; set SF, ZF, PF according to result.*/
	/* F7 /0 id TEST r/m32, int32 MI Valid Valid AND int32 with r/m32; set SF, ZF, PF according to result.*/
	/* REX.W + F7 /0 id TEST r/m64, int32 MI Valid N.E. AND int32 sign-extended to 64-bits with r/m64; set SF, ZF, PF according to result.*/
    { FCML_AMT_GPI, 0x0000, 0x00C58000, { 0xF7, 0x00, 0x00 }, { FCML_OP_MODRM_RM_W, FCML_OP_EX_EOSA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RMO_IMMO },
	/* 84 /r TEST r/m8, r8 MR Valid Valid AND r8 with r/m8; set SF, ZF, PF according to result.*/
	/* REX + 84 /r TEST r/m8*, r8* MR Valid N.E. AND r8 with r/m8; set SF, ZF, PF according to result.*/
    { FCML_AMT_GPI, 0x0000, 0x00C48000, { 0x84, 0x00, 0x00 }, { FCML_OP_MODRM_RM_OP_8_W, FCML_OP_MODRM_R_8, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RM8_R8 },
	/* 85 /r TEST r/m16, r16 MR Valid Valid AND r16 with r/m16; set SF, ZF, PF according to result.*/
	/* 85 /r TEST r/m32, r32 MR Valid Valid AND r32 with r/m32; set SF, ZF, PF according to result.*/
	/* REX.W + 85 /r TEST r/m64, r64 MR Valid N.E. AND r64 with r/m64; set SF, ZF, PF according to result.*/
    { FCML_AMT_GPI, 0x0000, 0x00C48000, { 0x85, 0x00, 0x00 }, { FCML_OP_MODRM_RM_OP_W, FCML_OP_MODRM_R, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RO_RMO }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_UCOMISD[] = {
	/* 66 0F 2E /r UCOMISD xmm1,xmm2/m64 RM V/V SSE2 Compares (unordered) the low doubleprecision floating-point values in xmm1 and xmm2/m64 and set the EFLAGS accordingly.*/
    { FCML_AMT_SSE2_SIMD, 0x1000, 0x00D88000, { 0x0F, 0x2E, 0x00 }, { FCML_OP_MODRM_R_XMM, FCML_OP_MODRM_RM_XMM_OP_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VUCOMISD[] = {
	/* VEX.LIG.66.0F.WIG 2E /r VUCOMISD xmm1,xmm2/m64 RM V/V AVX Compare low double precision floating-point values in xmm1 and xmm2/mem64 and set the EFLAGS flags accordingly.*/
    { FCML_AMT_AVX_SIMD, 0x10C0, 0x00D88000, { 0x0F, 0x2E, 0x00 }, { FCML_OP_MODRM_R_XMM, FCML_OP_MODRM_RM_XMM_OP_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_UCOMISS[] = {
	/* 0F 2E /r UCOMISS xmm1,xmm2/m32 RM V/V SSE Compare lower single-precision floating-point value in xmm1 register with lower singleprecision floating-point value in xmm2/mem and set the status flags accordingly.*/
    { FCML_AMT_SSE_SIMD, 0x0000, 0x00D88000, { 0x0F, 0x2E, 0x00 }, { FCML_OP_MODRM_R_XMM, FCML_OP_MODRM_RM_XMM_OP_32, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VUCOMISS[] = {
	/* VEX.LIG.0F.WIG 2E /r VUCOMISS xmm1,xmm2/m32 RM V/V AVX Compare low single precision floating-point values in xmm1 and xmm2/mem32 and set the EFLAGS flags accordingly.*/
    { FCML_AMT_AVX_SIMD, 0x00C0, 0x00D88000, { 0x0F, 0x2E, 0x00 }, { FCML_OP_MODRM_R_XMM, FCML_OP_MODRM_RM_XMM_OP_32, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_UD2[] = {
	/* 0F 0B UD2 NP Valid Valid Raise invalid opcode exception.*/
    { FCML_AMT_GPI, 0x0000, 0x00D80000, { 0x0F, 0x0B, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_UNPCKHPD[] = {
	/* 66 0F 15 /r UNPCKHPD xmm1,xmm2/m128 RM V/V SSE2 Unpacks and Interleaves double-precision floating-point values from high quadwords of xmm1 and xmm2/m128.*/
    { FCML_AMT_SSE2_SIMD, 0x1000, 0x00D88000, { 0x0F, 0x15, 0x00 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VUNPCKHPD[] = {
	/* VEX.NDS.128.66.0F.WIG 15 /r VUNPCKHPD xmm1,xmm2,xmm3/m128 RVM V/V AVX Unpacks and Interleaves double precision floating-point values from high quadwords of xmm2 and xmm3/m128.*/
	/* VEX.NDS.256.66.0F.WIG 15 /r VUNPCKHPD ymm1,ymm2,ymm3/m256 RVM V/V AVX Unpacks and Interleaves double precision floating-point values from high quadwords of ymm2 and ymm3/m256.*/
    { FCML_AMT_AVX_SIMD, 0x1080, 0x00D88000, { 0x0F, 0x15, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_UNPCKHPS[] = {
	/* 0F 15 /r UNPCKHPS xmm1, xmm2/m128 RM V/V SSE Unpacks and Interleaves single-precision floating-point values from high quadwords of xmm1 and xmm2/mem into xmm1.*/
    { FCML_AMT_SSE_SIMD, 0x0000, 0x00D88000, { 0x0F, 0x15, 0x00 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VUNPCKHPS[] = {
	/* VEX.NDS.128.0F.WIG 15 /r VUNPCKHPS xmm1,xmm2, xmm3/m128 RVM V/V AVX Unpacks and Interleaves single-precision floating-point values from high quadwords of xmm2 and xmm3/m128.*/
	/* VEX.NDS.256.0F.WIG 15 /r VUNPCKHPS ymm1,ymm2,ymm3/m256 RVM V/V AVX Unpacks and Interleaves single-precision floating-point values from high quadwords of ymm2 and ymm3/m256.*/
    { FCML_AMT_AVX_SIMD, 0x0080, 0x00D88000, { 0x0F, 0x15, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_UNPCKLPD[] = {
	/* 66 0F 14 /r UNPCKLPD xmm1, xmm2/m128 RM V/V SSE2 Unpacks and Interleaves double-precision floating-point values from low quadwords of xmm1 and xmm2/m128.*/
    { FCML_AMT_SSE2_SIMD, 0x1000, 0x00D88000, { 0x0F, 0x14, 0x00 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VUNPCKLPD[] = {
	/* VEX.NDS.128.66.0F.WIG 14 /r VUNPCKLPD xmm1,xmm2, xmm3/m128 RVM V/V AVX Unpacks and Interleaves double precision floating-point values low high quadwords of xmm2 and xmm3/m128.*/
	/* VEX.NDS.256.66.0F.WIG 14 /r VUNPCKLPD ymm1,ymm2, ymm3/m256 RVM V/V AVX Unpacks and Interleaves double precision floating-point values low high quadwords of ymm2 and ymm3/m256.*/
    { FCML_AMT_AVX_SIMD, 0x1080, 0x00D88000, { 0x0F, 0x14, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_UNPCKLPS[] = {
	/* 0F 14 /r UNPCKLPS xmm1, xmm2/m128 RM V/V SSE Unpacks and Interleaves single-precision floating-point values from low quadwords of xmm1 and xmm2/mem into xmm1.*/
    { FCML_AMT_SSE_SIMD, 0x0000, 0x00D88000, { 0x0F, 0x14, 0x00 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VUNPCKLPS[] = {
	/* VEX.NDS.128.0F.WIG 14 /r VUNPCKLPS xmm1,xmm2, xmm3/m128 RVM V/V AVX Unpacks and Interleaves single-precision floating-point values from low quadwords of xmm2 and xmm3/m128.*/
	/* VEX.NDS.256.0F.WIG 14 /r VUNPCKLPS ymm1,ymm2,ymm3/m256 RVM V/V AVX Unpacks and Interleaves single-precision floating-point values from low quadwords of ymm2 and ymm3/m256.*/
    { FCML_AMT_AVX_SIMD, 0x0080, 0x00D88000, { 0x0F, 0x14, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VMPTRLD[] = {
	/* 0F C7 /6 VMPTRLD m64 Loads the current VMCS pointer from memory.*/
    { FCML_AMT_VMX, 0x0000, 0x0099B000, { 0x0F, 0xC7, 0x00 }, { FCML_OP_MODRM_M_OP_64_W, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VMPTRST[] = {
	/* 0F C7 /7 VMPTRST m64 Stores the current VMCS pointer into memory.*/
    { FCML_AMT_VMX, 0x0000, 0x0099B800, { 0x0F, 0xC7, 0x00 }, { FCML_OP_MODRM_M_OP_64_W, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VMCLEAR[] = {
	/* 66 0F C7 /6 VMCLEAR m64 Copy VMCS data to VMCS region in memory.*/
    { FCML_AMT_VMX, 0x1000, 0x0099B800, { 0x0F, 0xC7, 0x00 }, { FCML_OP_MODRM_M_OP_64_W, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VMREAD[] = {
	/* 0F 78 VMREAD r/m64, r64 Reads a specified VMCS field (in 64-bit mode).*/
	/* 0F 78 VMREAD r/m32, r32 Reads a specified VMCS field (outside 64-bit mode).*/
    { FCML_AMT_VMX, 0x0000, 0x00588000, { 0x0F, 0x78, 0x00 }, { FCML_OP_MODRM_RM_OP_32_W, FCML_OP_MODRM_R_32, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
    { FCML_AMT_VMX, 0x0000, 0x00988000, { 0x0F, 0x78, 0x00 }, { FCML_OP_MODRM_RM_OP_64_W, FCML_OP_MODRM_R_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VMWRITE[] = {
	/* 0F 79 VMWRITE r64, r/m64 Writes a specified VMCS field (in 64-bit mode)*/
	/* 0F 79 VMWRITE r32, r/m32 Writes a specified VMCS field (outside 64-bit mode)*/
    { FCML_AMT_VMX, 0x0000, 0x00588000, { 0x0F, 0x79, 0x00 }, { FCML_OP_MODRM_R_32_W, FCML_OP_MODRM_RM_OP_32, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
    { FCML_AMT_VMX, 0x0000, 0x00988000, { 0x0F, 0x79, 0x00 }, { FCML_OP_MODRM_R_64_W, FCML_OP_MODRM_RM_OP_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VMLAUNCH[] = {
	/* 0F 01 C2 VMLAUNCH Launch virtual machine managed by current VMCS.*/
    { FCML_AMT_VMX, 0x0000, 0x00AC0000, { 0x0F, 0x01, 0xC2 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VMRESUME[] = {
	/* 0F 01 C3 VMRESUME Resume virtual machine managed by current VMCS.*/
    { FCML_AMT_VMX, 0x0000, 0x00AC0000, { 0x0F, 0x01, 0xC3 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VMXOFF[] = {
	/* 0F 01 C4 VMXOFF Leaves VMX operation.*/
    { FCML_AMT_VMX, 0x0000, 0x00AC0000, { 0x0F, 0x01, 0xC4 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VMXON[] = {
	/* F3 0F C7 /6 VMXON m64 Enter VMX root operation.*/
    { FCML_AMT_VMX, 0x4000, 0x0099B000, { 0x0F, 0xC7, 0x00 }, { FCML_OP_MODRM_M_OP_64_W, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VMCALL[] = {
	/* 0F 01 C1 VMCALL Call to VM monitor by causing VM exit.*/
    { FCML_AMT_VMX, 0x0000, 0x00AC0000, { 0x0F, 0x01, 0xC1 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VMFUNC[] = {
	/* 0F 01 D4 VMFUNC Invoke VM function specified in EAX.*/
    { FCML_AMT_VMX, 0x0000, 0x00AC0000, { 0x0F, 0x01, 0xD4 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VBROADCASTSD[] = {
	/* VEX.256.66.0F38 19 /r VBROADCASTSD ymm1, m64*/
    { FCML_AMT_AVX_SIMD, 0x10A0, 0x00EC8000, { 0x0F, 0x38, 0x19 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_MODRM_RM_XMM_OP_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.256.66.0F38.W0 19 /r VBROADCASTSD ymm1,xmm2*/
    { FCML_AMT_AVX2_SIMD, 0x10A0, 0x00EC8000, { 0x0F, 0x38, 0x19 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_RM( FCML_REG_SIMD, FCML_EOS_XWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VBROADCASTSS[] = {
	/* VEX.128.66.0F38 18 /r VBROADCASTSS xmm1, m32*/
	/* VEX.256.66.0F38 18 /r VBROADCASTSS ymm1, m32*/
    { FCML_AMT_AVX_SIMD, 0x1080, 0x00EC8000, { 0x0F, 0x38, 0x18 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_MODRM_M_OP_32, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.128.66.0F38.W0 18 /r VBROADCASTSS xmm1,xmm2*/
	/* VEX.256.66.0F38.W0 18 /r VBROADCASTSS ymm1,xmm2*/
    { FCML_AMT_AVX2_SIMD, 0x1080, 0x00EE8000, { 0x0F, 0x38, 0x18 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_RM( FCML_REG_SIMD, FCML_EOS_OWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VBROADCASTI128[] = {
	/* VEX.256.66.0F38.W0 5A /r VBROADCASTI128 ymm1,m128*/
    { FCML_AMT_AVX2_SIMD, 0x10B0, 0x00EC8000, { 0x0F, 0x38, 0x5A }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_MODRM_M_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VBROADCASTF128[] = {
	/* VEX.256.66.0F38.W0 1A /r VBROADCASTF128 ymm1,m128*/
    { FCML_AMT_AVX_SIMD, 0x10B0, 0x00EC8000, { 0x0F, 0x38, 0x1A }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_MODRM_M_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPBROADCASTB[] = {
	/* VEX.128.66.0F38.W0 78 /r VPBROADCASTB xmm1,xmm2/m8*/
	/* VEX.256.66.0F38.W0 78 /r VPBROADCASTB ymm1,xmm2/m8*/
    { FCML_AMT_AVX2_SIMD, 0x1090, 0x00EC8000, { 0x0F, 0x38, 0x78 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_MODRM_RM_XMM_OP_8, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPBROADCASTW[] = {
	/* VEX.128.66.0F38.W0 79 /r VPBROADCASTW xmm1,xmm2/m16*/
	/* VEX.256.66.0F38.W0 79 /r VPBROADCASTW ymm1,xmm2/m16*/
    { FCML_AMT_AVX2_SIMD, 0x1090, 0x00EC8000, { 0x0F, 0x38, 0x79 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_MODRM_RM_XMM_OP_16, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPBROADCASTD[] = {
	/* VEX.128.66.0F38.W0 58 /r VPBROADCASTD xmm1,xmm2/m32*/
	/* VEX.256.66.0F38.W0 58 /r VPBROADCASTD ymm1,xmm2/m32*/
    { FCML_AMT_AVX2_SIMD, 0x1090, 0x00EC8000, { 0x0F, 0x38, 0x58 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_MODRM_RM_XMM_OP_32, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPBROADCASTQ[] = {
	/* VEX.128.66.0F38.W0 59 /r VPBROADCASTQ xmm1,xmm2/m64*/
	/* VEX.256.66.0F38.W0 59 /r VPBROADCASTQ ymm1,xmm2/m64*/
    { FCML_AMT_AVX2_SIMD, 0x1090, 0x00EC8000, { 0x0F, 0x38, 0x59 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_MODRM_RM_XMM_OP_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VCVTPH2PS[] = {
	/* VEX.128.66.0F38.W0 13 /r VCVTPH2PS xmm1,xmm2/m64 RM V/V F16C Convert four packed half precision (16-bit) floating-point values in xmm2/m64 to packed single-precision floating-point value in xmm1.*/
    { FCML_AMT_F16C, 0x10D0, 0x00EC8000, { 0x0F, 0x38, 0x13 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_OP_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.256.66.0F38.W0 13 /r VCVTPH2PS ymm1,xmm2/m128 RM V/V F16C Convert eight packed half precision (16-bit) floating-point values in xmm2/m128 to packed single-precision floating-point value in ymm1.*/
    { FCML_AMT_F16C, 0x10B0, 0x00EC8000, { 0x0F, 0x38, 0x13 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VCVTPS2PH[] = {
	/* VEX.128.66.0F3A.W0.1D /r VCVTPS2PH xmm1/m64,xmm2,int8 ib MR V/V F16C Convert four packed single-precision floating-point value in xmm2 to packed halfprecision (16-bit) floating-point value in xmm1/mem. Imm8 provides rounding controls.*/
    { FCML_AMT_F16C, 0x10D0, 0x00EC8000, { 0x0F, 0x3A, 0x1D }, { FCML_OP_MODRM_RM_XMM_OP_64_W, FCML_OP_MODRM_R_XMM, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.256.66.0F3A.W0 1D /r VCVTPS2PH xmm1/m128,ymm2,int8 ib MR V/V F16C Convert eight packed single-precision floating-point value in ymm2 to packed half-precision (16-bit) floating-point value in xmm1/mem. Imm8 provides rounding controls.*/
    { FCML_AMT_F16C, 0x10B0, 0x00EC8000, { 0x0F, 0x3A, 0x1D }, { FCML_OP_MODRM_RM_XMM_OP_128_W, FCML_OP_MODRM_R_YMM, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VERR[] = {
	/* 0F 00 /4 VERR r/m16 M Valid Valid Set ZF=1 if segment specified with r/m16 can be read.*/
    { FCML_AMT_SYSTEM, 0x0000, 0x00D9A000, { 0x0F, 0x00, 0x00 }, { FCML_OP_MODRM_RM_OP_16, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VERW[] = {
	/* 0F 00 /5 VERW r/m16 M Valid Valid Set ZF=1 if segment specified with r/m16 can be written.*/
    { FCML_AMT_SYSTEM, 0x0000, 0x00D9A800, { 0x0F, 0x00, 0x00 }, { FCML_OP_MODRM_RM_OP_16, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VMLOAD[] = {
	/* VMLOAD rAX 0F 01 DA Load additional state from VMCB.*/
    { FCML_AMT_SVM, 0x0000, 0x00EC0000, { 0x0F, 0x01, 0xDA }, { FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_EAX, FCML_EOS_EASA ), FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VMMCALL[] = {
	/* VMMCALL 0F 01 D9 Explicit communication with the VMM.*/
    { FCML_AMT_SVM, 0x0000, 0x00EC0000, { 0x0F, 0x01, 0xD9 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VMRUN[] = {
	/* VMRUN rAX 0F 01 D8 Performs a world-switch to guest.*/
    { FCML_AMT_SVM, 0x0000, 0x00EC0000, { 0x0F, 0x01, 0xD8 }, { FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_EAX, FCML_EOS_EASA ), FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VMSAVE[] = {
	/* VMSAVE rAX 0F 01 DB Save additional guest state to VMCB.*/
    { FCML_AMT_SVM, 0x0000, 0x00EC0000, { 0x0F, 0x01, 0xDB }, { FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_EAX, FCML_EOS_EASA ), FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPERMILPD[] = {
	/* VEX.NDS.128.66.0F38.W0 0D /r VPERMILPD xmm1,xmm2,xmm3/m128 RVM V/V AVX Permute double-precision floating-point values in xmm2 using controls from xmm3/mem and store result in xmm1.*/
	/* VEX.NDS.256.66.0F38.W0 0D /r VPERMILPD ymm1,ymm2,ymm3/m256 RVM V/V AVX Permute double-precision floating-point values in ymm2 using controls from ymm3/mem and store result in ymm1.*/
    { FCML_AMT_AVX_SIMD, 0x1090, 0x00EC8000, { 0x0F, 0x38, 0x0D }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.128.66.0F3A.W0 05 /r ib VPERMILPD xmm1,xmm2/m128,int8 RMI V/V AVX Permute double-precision floating-point values in xmm2/mem using controls from int8.*/
	/* VEX.256.66.0F3A.W0 05 /r ib VPERMILPD ymm1,ymm2/m256,int8 RMI V/V AVX Permute double-precision floating-point values in ymm2/mem using controls from int8.*/
    { FCML_AMT_AVX_SIMD, 0x1090, 0x00EC8000, { 0x0F, 0x3A, 0x05 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPERMILPS[] = {
	/* VEX.NDS.128.66.0F38.W0 0C /r VPERMILPS xmm1,xmm2,xmm3/m128 RVM V/V AVX Permute single-precision floating-point values in xmm2 using controls from xmm3/mem and store result in xmm1.*/
	/* VEX.NDS.256.66.0F38.W0 0C /r VPERMILPS ymm1,ymm2,ymm3/m256 RVM V/V AVX Permute single-precision floating-point values in ymm2 using controls from ymm3/mem and store result in ymm1.*/
    { FCML_AMT_AVX_SIMD, 0x1090, 0x00EC8000, { 0x0F, 0x38, 0x0C }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.128.66.0F3A.W0 04 /r ib VPERMILPS xmm1,xmm2/m128,int8 RMI V/V AVX Permute single-precision floating-point values in xmm2/mem using controls from int8 and store result in xmm1.*/
	/* VEX.256.66.0F3A.W0 04 /r ib VPERMILPS ymm1,ymm2/m256,int8 RMI V/V AVX Permute single-precision floating-point values in ymm2/mem using controls from int8 and store result in ymm1.*/
    { FCML_AMT_AVX_SIMD, 0x1090, 0x00EC8000, { 0x0F, 0x3A, 0x04 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPSLLVQ[] = {
	/* VEX.NDS.128.66.0F38.W1 47 /r VPSLLVQ xmm1,xmm2,xmm3/m128*/
	/* VEX.NDS.256.66.0F38.W1 47 /r VPSLLVQ ymm1,ymm2,ymm3/m256*/
    { FCML_AMT_AVX2_SIMD, 0x1088, 0x00EC8000, { 0x0F, 0x38, 0x47 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPSLLVD[] = {
	/* VEX.NDS.128.66.0F38.W0 47 /r VPSLLVD xmm1,xmm2,xmm3/m128*/
	/* VEX.NDS.256.66.0F38.W0 47 /r VPSLLVD ymm1,ymm2,ymm3/m256*/
    { FCML_AMT_AVX2_SIMD, 0x1090, 0x00EC8000, { 0x0F, 0x38, 0x47 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPSRLVD[] = {
	/* VEX.NDS.128.66.0F38.W0 45 /r VPSRLVD xmm1,xmm2,xmm3/m128*/
	/* VEX.NDS.256.66.0F38.W0 45 /r VPSRLVD ymm1,ymm2,ymm3/m256*/
    { FCML_AMT_AVX2_SIMD, 0x1090, 0x00EC8000, { 0x0F, 0x38, 0x45 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPSRLVQ[] = {
	/* VEX.NDS.128.66.0F38.W1 45 /r VPSRLVQ xmm1,xmm2,xmm3/m128*/
	/* VEX.NDS.256.66.0F38.W1 45 /r VPSRLVQ ymm1,ymm2,ymm3/m256*/
    { FCML_AMT_AVX2_SIMD, 0x1088, 0x00EC8000, { 0x0F, 0x38, 0x45 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPSRAVD[] = {
	/* VEX.NDS.128.66.0F38.W0 46 /r VPSRAVD xmm1,xmm2,xmm3/m128*/
	/* VEX.NDS.256.66.0F38.W0 46 /r VPSRAVD ymm1,ymm2,ymm3/m256*/
    { FCML_AMT_AVX2_SIMD, 0x1090, 0x00EC8000, { 0x0F, 0x38, 0x46 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPERMD[] = {
	/* VEX.NDS.256.66.0F38.W0 36 /r VPERMD ymm1,ymm2,ymm3/m256*/
    { FCML_AMT_AVX2_SIMD, 0x10B0, 0x00EC8000, { 0x0F, 0x38, 0x36 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_YMM_OP_256, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPERMPD[] = {
	/* VEX.256.66.0F3A.W1 01 /r ib VPERMPD ymm1,ymm2/m256,int8*/
    { FCML_AMT_AVX2_SIMD, 0x10A8, 0x00EC8000, { 0x0F, 0x3A, 0x01 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_MODRM_RM_YMM_OP_256, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPERMQ[] = {
	/* VEX.256.66.0F3A.W1 00 /r ib VPERMQ ymm1,ymm2/m256,int8*/
    { FCML_AMT_AVX2_SIMD, 0x10A8, 0x00EC8000, { 0x0F, 0x3A, 0x00 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_MODRM_RM_YMM_OP_256, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPERMPS[] = {
	/* VEX.NDS.256.66.0F38.W0 16 /r VPERMPS ymm1,ymm2,ymm3/m256*/
    { FCML_AMT_AVX2_SIMD, 0x10B0, 0x00EC8000, { 0x0F, 0x38, 0x16 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_YMM_REG, FCML_OP_MODRM_RM_YMM_OP_256, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPERM2F128[] = {
	/* VEX.NDS.256.66.0F3A.W0 06 /r ib VPERM2F128 ymm1,ymm2,ymm3/m256,int8 RVMI V/V AVX Permute 128-bit floating-point fields in ymm2 and ymm3/mem using controls from int8 and store result in ymm1.*/
    { FCML_AMT_AVX_SIMD, 0x10B0, 0x00EC8000, { 0x0F, 0x3A, 0x06 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_YMM_REG, FCML_OP_MODRM_RM_YMM_OP_256, FCML_OP_IB, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPERM2I128[] = {
	/* VEX.NDS.256.66.0F3A.W0 46 /r ib VPERM2I128 ymm1,ymm2,ymm3/m256,int8*/
    { FCML_AMT_AVX2_SIMD, 0x10B0, 0x00EC8000, { 0x0F, 0x3A, 0x46 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_YMM_REG, FCML_OP_MODRM_RM_YMM_OP_256, FCML_OP_IB, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VEXTRACTI128[] = {
	/* VEX.256.66.0F3A.W0 39 /r ib VEXTRACTI128 xmm1/m128,ymm2,int8*/
    { FCML_AMT_AVX2_SIMD, 0x10B0, 0x00EC8000, { 0x0F, 0x3A, 0x39 }, { FCML_OP_MODRM_RM_XMM_OP_128_W, FCML_OP_MODRM_R_YMM, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VINSERTI128[] = {
	/* VEX.NDS.256.66.0F3A.W0 38 /r ib VINSERTI128 ymm1,ymm2,xmm3/m128,int8*/
    { FCML_AMT_AVX2_SIMD, 0x10B0, 0x00EC8000, { 0x0F, 0x3A, 0x38 }, { FCML_OP_MODRM_R_YMM_W, FCML_OP_VEX_VVVV_YMM_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_OP_IB, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VTESTPS[] = {
	/* VEX.128.66.0F38.W0 0E /r VTESTPS xmm1,xmm2/m128 RM V/V AVX Set ZF and CF depending on sign bit AND and ANDN of packed single-precision floatingpoint sources.*/
	/* VEX.256.66.0F38.W0 0E /r VTESTPS ymm1,ymm2/m256 RM V/V AVX Set ZF and CF depending on sign bit AND and ANDN of packed single-precision floatingpoint sources.*/
    { FCML_AMT_AVX_SIMD, 0x1090, 0x00EC8000, { 0x0F, 0x38, 0x0E }, { FCML_OP_MODRM_R_SIMD_L, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VTESTPD[] = {
	/* VEX.128.66.0F38.W0 0F /r VTESTPD xmm1,xmm2/m128 RM V/V AVX Set ZF and CF depending on sign bit AND and ANDN of packed double-precision floatingpoint sources.*/
	/* VEX.256.66.0F38.W0 0F /r VTESTPD ymm1,ymm2/m256 RM V/V AVX Set ZF and CF depending on sign bit AND and ANDN of packed double-precision floatingpoint sources.*/
    { FCML_AMT_AVX_SIMD, 0x1090, 0x00EC8000, { 0x0F, 0x38, 0x0F }, { FCML_OP_MODRM_R_SIMD_L, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VGATHERDPD[] = {
	/* VEX.DDS.128.66.0F38.W1 92 /r VGATHERDPD xmm1, vm32x, xmm2*/
	/* VEX.DDS.256.66.0F38.W1 92 /r VGATHERDPD ymm1, vm32x, ymm2*/
    { FCML_AMT_AVX2_SIMD, 0x1088, 0x00EC8000, { 0x0F, 0x38, 0x92 }, { FCML_OP_MODRM_R_SIMD_L_RW, FCML_OP_VSIB(FCML_VSIB_XMM,FCML_EOS_DWORD | FCML_EOS_OPT), FCML_OP_VEX_VVVV_SIMD_REG | FCML_OA_RW, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VGATHERQPD[] = {
	/* VEX.DDS.128.66.0F38.W1 93 /r VGATHERQPD xmm1, vm64x, xmm2*/
    { FCML_AMT_AVX2_SIMD, 0x10C8, 0x00EC8000, { 0x0F, 0x38, 0x93 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_VSIB(FCML_VSIB_XMM,FCML_EOS_QWORD | FCML_EOS_OPT), FCML_OP_VEX_VVVV_SIMD_REG | FCML_OA_RW, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.DDS.256.66.0F38.W1 93 /r VGATHERQPD ymm1, vm64y, ymm2*/
    { FCML_AMT_AVX2_SIMD, 0x10A8, 0x00EC8000, { 0x0F, 0x38, 0x93 }, { FCML_OP_MODRM_R_YMM_RW, FCML_OP_VSIB(FCML_VSIB_YMM,FCML_EOS_QWORD | FCML_EOS_OPT), FCML_OP_VEX_VVVV_SIMD_REG | FCML_OA_RW, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VGATHERDPS[] = {
	/* VEX.DDS.128.66.0F38.W0 92 /r VGATHERDPS xmm1,vm32x,xmm2*/
    { FCML_AMT_AVX2_SIMD, 0x10D0, 0x00EC8000, { 0x0F, 0x38, 0x92 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_VSIB(FCML_VSIB_XMM,FCML_EOS_DWORD | FCML_EOS_OPT), FCML_OP_VEX_VVVV_SIMD_REG | FCML_OA_RW, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.DDS.256.66.0F38.W0 92 /r VGATHERDPS ymm1,vm32y,ymm2*/
    { FCML_AMT_AVX2_SIMD, 0x10B0, 0x00EC8000, { 0x0F, 0x38, 0x92 }, { FCML_OP_MODRM_R_YMM_RW, FCML_OP_VSIB(FCML_VSIB_YMM,FCML_EOS_DWORD | FCML_EOS_OPT), FCML_OP_VEX_VVVV_SIMD_REG | FCML_OA_RW, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VGATHERQPS[] = {
	/* VEX.DDS.128.66.0F38.W0 93 /r VGATHERQPS xmm1,vm64x,xmm2*/
    { FCML_AMT_AVX2_SIMD, 0x10D0, 0x00EC8000, { 0x0F, 0x38, 0x93 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_VSIB(FCML_VSIB_XMM,FCML_EOS_QWORD | FCML_EOS_OPT), FCML_OP_VEX_VVVV_XMM_REG | FCML_OA_RW, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.DDS.256.66.0F38.W0 93 /r VGATHERQPS xmm1,vm64y,xmm2*/
    { FCML_AMT_AVX2_SIMD, 0x10B0, 0x00EC8000, { 0x0F, 0x38, 0x93 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_VSIB(FCML_VSIB_YMM,FCML_EOS_QWORD | FCML_EOS_OPT), FCML_OP_VEX_VVVV_XMM_REG | FCML_OA_RW, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPGATHERDD[] = {
	/* VEX.DDS.128.66.0F38.W0 90 /r VPGATHERDD xmm1,vm32x,xmm2*/
    { FCML_AMT_AVX2_SIMD, 0x10D0, 0x00EC8000, { 0x0F, 0x38, 0x90 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_VSIB(FCML_VSIB_XMM,FCML_EOS_DWORD | FCML_EOS_OPT), FCML_OP_VEX_VVVV_SIMD_REG | FCML_OA_RW, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.DDS.256.66.0F38.W0 90 /r VPGATHERDD ymm1,vm32y,ymm2*/
    { FCML_AMT_AVX2_SIMD, 0x10B0, 0x00EC8000, { 0x0F, 0x38, 0x90 }, { FCML_OP_MODRM_R_YMM_RW, FCML_OP_VSIB(FCML_VSIB_YMM,FCML_EOS_DWORD | FCML_EOS_OPT), FCML_OP_VEX_VVVV_SIMD_REG | FCML_OA_RW, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPGATHERQD[] = {
	/* VEX.DDS.128.66.0F38.W0 91 /r VPGATHERQD xmm1,vm64x,xmm2*/
    { FCML_AMT_AVX2_SIMD, 0x10D0, 0x00EC8000, { 0x0F, 0x38, 0x91 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_VSIB(FCML_VSIB_XMM,FCML_EOS_QWORD | FCML_EOS_OPT), FCML_OP_VEX_VVVV_XMM_REG | FCML_OA_RW, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.DDS.256.66.0F38.W0 91 /r VPGATHERQD xmm1,vm64y,xmm2*/
    { FCML_AMT_AVX2_SIMD, 0x10B0, 0x00EC8000, { 0x0F, 0x38, 0x91 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_VSIB(FCML_VSIB_YMM,FCML_EOS_QWORD | FCML_EOS_OPT), FCML_OP_VEX_VVVV_XMM_REG | FCML_OA_RW, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPGATHERDQ[] = {
	/* VEX.DDS.128.66.0F38.W1 90 /r VPGATHERDQ xmm1,vm32x,xmm2*/
	/* VEX.DDS.256.66.0F38.W1 90 /r VPGATHERDQ ymm1,vm32x,ymm2*/
    { FCML_AMT_AVX2_SIMD, 0x1088, 0x00EC8000, { 0x0F, 0x38, 0x90 }, { FCML_OP_MODRM_R_SIMD_L_RW, FCML_OP_VSIB(FCML_VSIB_XMM,FCML_EOS_DWORD | FCML_EOS_OPT), FCML_OP_VEX_VVVV_SIMD_REG | FCML_OA_RW, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPGATHERQQ[] = {
	/* VEX.DDS.128.66.0F38.W1 91 /r VPGATHERQQ xmm1,vm64x,xmm2*/
    { FCML_AMT_AVX2_SIMD, 0x10C8, 0x00EC8000, { 0x0F, 0x38, 0x91 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_VSIB(FCML_VSIB_XMM,FCML_EOS_QWORD | FCML_EOS_OPT), FCML_OP_VEX_VVVV_SIMD_REG | FCML_OA_RW, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.DDS.256.66.0F38.W1 91 /r VPGATHERQQ ymm1,vm64y,ymm2*/
    { FCML_AMT_AVX2_SIMD, 0x10A8, 0x00EC8000, { 0x0F, 0x38, 0x91 }, { FCML_OP_MODRM_R_YMM_RW, FCML_OP_VSIB(FCML_VSIB_YMM,FCML_EOS_QWORD | FCML_EOS_OPT), FCML_OP_VEX_VVVV_SIMD_REG | FCML_OA_RW, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VZEROALL[] = {
	/* VEX.256.0F.WIG 77 VZEROALL NP V/V AVX Zero all YMM registers.*/
    { FCML_AMT_AVX_SIMD, 0x00A0, 0x00D80000, { 0x0F, 0x77, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VZEROUPPER[] = {
	/* VEX.128.0F.WIG 77 VZEROUPPER NP V/V AVX Zero upper 128 bits of all YMM registers.*/
    { FCML_AMT_AVX_SIMD, 0x00C0, 0x00D80000, { 0x0F, 0x77, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_WAIT[] = {
	/* 9B WAIT NP Valid Valid Check pending unmasked floating-point exceptions.*/
	/* 9B FWAIT NP Valid Valid Check pending unmasked floating-point exceptions.*/
    { FCML_AMT_FPU, 0x0000, 0x00C40000, { 0x9B, 0x00, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_WBINVD[] = {
	/* 0F 09 WBINVD NP Valid Valid Write back and flush Internal caches; initiate writing-back and flushing of external caches.*/
    { FCML_AMT_SYSTEM, 0x0000, 0x00D80000, { 0x0F, 0x09, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_WRFSBASE[] = {
	/* F3 0F AE /2 WRFSBASE r32 M V/I FSGSBASE Load the FS base address with the 32-bit value in the source register.*/
    { FCML_AMT_SYSTEM | FCML_AMT_FSGSBASE, 0x4010, 0x03DB9000, { 0x0F, 0xAE, 0x00 }, { FCML_OP_RM( FCML_REG_GPR, FCML_EOS_DWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_NA , FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* REX.W + F3 0F AE /2 WRFSBASE r64 M V/I FSGSBASE Load the FS base address with the 64-bit value in the source register.*/
    { FCML_AMT_SYSTEM | FCML_AMT_FSGSBASE, 0x4008, 0x049B9000, { 0x0F, 0xAE, 0x00 }, { FCML_OP_RM( FCML_REG_GPR, FCML_EOS_QWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_NA , FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_WRGSBASE[] = {
	/* F3 0F AE /3 WRGSBASE r32 M V/I FSGSBASE Load the GS base address with the 32-bit value in the source register.*/
    { FCML_AMT_SYSTEM | FCML_AMT_FSGSBASE, 0x4010, 0x03DB9800, { 0x0F, 0xAE, 0x00 }, { FCML_OP_RM( FCML_REG_GPR, FCML_EOS_DWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_NA , FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* REX.W + F3 0F AE /3 WRGSBASE r64 M V/I FSGSBASE Load the GS base address with the 64-bit value in the source register.*/
    { FCML_AMT_SYSTEM | FCML_AMT_FSGSBASE, 0x4008, 0x049B9800, { 0x0F, 0xAE, 0x00 }, { FCML_OP_RM( FCML_REG_GPR, FCML_EOS_QWORD, FCML_EOS_UNDEFINED, FCML_RMF_R ), FCML_NA , FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_WRMSR[] = {
	/* 0F 30 WRMSR NP Valid Valid Write the value in EDX:EAX to MSR specified by ECX.*/
    { FCML_AMT_SYSTEM, 0x0000, 0x00D80000, { 0x0F, 0x30, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_XADD[] = {
	/* 0F C0 /r XADD r/m8,r8 MR Valid Valid Exchange r8 and r/m8; load sum into r/m8.*/
	/* REX + 0F C0 /r XADD r/m8*,r8* MR Valid N.E. Exchange r8 and r/m8; load sum into r/m8.*/
    { FCML_AMT_GPI, 0x0807, 0x00D88000, { 0x0F, 0xC0, 0x00 }, { FCML_OP_MODRM_RM_OP_8_RW, FCML_OP_MODRM_R_8, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RM8_R8 },
	/* 0F C1 /r XADD r/m16,r16 MR Valid Valid Exchange r16 and r/m16; load sum into r/m16.*/
	/* 0F C1 /r XADD r/m32,r32 MR Valid Valid Exchange r32 and r/m32; load sum into r/m32.*/
	/* REX.W + 0F C1 /r XADD r/m64,r64 MR Valid N.E. Exchange r64 and r/m64; load sum into r/m64.*/
    { FCML_AMT_GPI, 0x0807, 0x00D88000, { 0x0F, 0xC1, 0x00 }, { FCML_OP_MODRM_RM_OP_RW, FCML_OP_MODRM_R, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RMO_RO }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_XCHG[] = {
	/* 90+rw XCHG AX, r16 O Valid Valid Exchange r16 with AX.*/
	/* 90+rw XCHG r16, AX O Valid Valid Exchange AX with r16.*/
	/* 90+rd XCHG EAX, r32 O Valid Valid Exchange r32 with EAX.*/
	/* 90+rd XCHG r32, EAX O Valid Valid Exchange EAX with r32.*/
	/* REX.W + 90+rd XCHG RAX, r64 O Valid N.E. Exchange r64 with RAX.*/
	/* REX.W + 90+rd XCHG r64, RAX O Valid N.E. Exchange RAX with r64.*/
    { FCML_AMT_GPI, 0x0000, 0x00C40001, { 0x90, 0x00, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_EAX, FCML_EOS_EOSA ) | FCML_OA_RW, FCML_OP_OPCODE_REG( FCML_REG_GPR, FCML_EOS_EOSA) | FCML_OA_RW, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
    { FCML_AMT_GPI, 0x0000, 0x00C40001, { 0x90, 0x00, 0x00 }, { FCML_OP_OPCODE_REG( FCML_REG_GPR, FCML_EOS_EOSA) | FCML_OA_RW, FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_EAX, FCML_EOS_EOSA ) | FCML_OA_RW, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* 86 /r XCHG r/m8, r8 MR Valid Valid Exchange r8 (byte register) with byte from r/m8.*/
	/* REX + 86 /r XCHG r/m8*, r8* MR Valid N.E. Exchange r8 (byte register) with byte from r/m8.*/
	/* 86 /r XCHG r8, r/m8 RM Valid Valid Exchange byte from r/m8 with r8 (byte register).*/
	/* REX + 86 /r XCHG r8*, r/m8* RM Valid N.E. Exchange byte from r/m8 with r8 (byte register).*/
    { FCML_AMT_GPI, 0x0807, 0x00C48000, { 0x86, 0x00, 0x00 }, { FCML_OP_MODRM_RM_OP_8_RW, FCML_OP_MODRM_R_8_W, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
    { FCML_AMT_GPI, 0x0807, 0x00C48000, { 0x86, 0x00, 0x00 }, { FCML_OP_MODRM_R_8_W, FCML_OP_MODRM_RM_OP_8_W, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* 87 /r XCHG r/m16, r16 MR Valid Valid Exchange r16 with word from r/m16.*/
	/* 87 /r XCHG r16, r/m16 RM Valid Valid Exchange word from r/m16 with r16.*/
	/* 87 /r XCHG r/m32, r32 MR Valid Valid Exchange r32 with doubleword from r/m32.*/
	/* 87 /r XCHG r32, r/m32 RM Valid Valid Exchange doubleword from r/m32 with r32.*/
	/* REX.W + 87 /r XCHG r/m64, r64 MR Valid N.E. Exchange r64 with quadword from r/m64.*/
	/* REX.W + 87 /r XCHG r64, r/m64 RM Valid N.E. Exchange quadword from r/m64 with r64.*/
    { FCML_AMT_GPI, 0x0807, 0x00C48000, { 0x87, 0x00, 0x00 }, { FCML_OP_MODRM_RM_OP_RW, FCML_OP_MODRM_R_W, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
    { FCML_AMT_GPI, 0x0807, 0x00C48000, { 0x87, 0x00, 0x00 }, { FCML_OP_MODRM_R_W, FCML_OP_MODRM_RM_OP_W, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_XGETBV[] = {
	/* 0F 01 D0 XGETBV NP Valid Valid Reads an XCR specified by ECX into EDX:EAX.*/
    { FCML_AMT_SYSTEM, 0x0000, 0x00EC0000, { 0x0F, 0x01, 0xD0 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_XLAT[] = {
	/* D7 XLAT m8 NP Valid Valid Set AL to memory byte DS:[(E)BX + unsigned AL].*/
	/* D7 XLATB NP Valid Valid Set AL to memory byte DS:[(E)BX + unsigned AL].*/
	/* REX.W + D7 XLATB NP Valid N.E. Set AL to memory byte [RBX + unsigned AL].*/
    { FCML_AMT_GPI, 0x0000, 0x00C40000, { 0xD7, 0x00, 0x00 }, { FCML_OP_EXPLICIT_GPS_REG_ADDRESSING( FCML_REG_BX, FCML_EOS_BYTE, FCML_SEG_ENCODE_REGISTER( FCML_REG_DS, FCML_SEG_ALLOW_OVERRIDE ) ), FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_XOR[] = {
	/* 34 ib XOR AL, int8 I Valid Valid AL XOR int8.*/
    { FCML_AMT_GPI, 0x0000, 0x00C40002, { 0x34, 0x00, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_AL, FCML_EOS_BYTE ), FCML_OP_IB, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_ER8_IMM8 },
	/* 35 iw XOR AX, int16 I Valid Valid AX XOR int16.*/
	/* 35 id XOR EAX, int32 I Valid Valid EAX XOR int32.*/
	/* REX.W + 35 id XOR RAX, int32 I Valid N.E. RAX XOR int32 (sign-extended).*/
    { FCML_AMT_GPI, 0x0000, 0x00C40002, { 0x35, 0x00, 0x00 }, { FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_AL, FCML_EOS_EOSA ) | FCML_OA_W, FCML_OP_EX_EOSA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_ERO_IMMO },
	/* 80 /6 ib XOR r/m8, int8 MI Valid Valid r/m8 XOR int8.*/
	/* REX + 80 /6 ib XOR r/m8*, int8 MI Valid N.E. r/m8 XOR int8.*/
    { FCML_AMT_GPI, 0x0807, 0x00C5B006, { 0x80, 0x00, 0x00 }, { FCML_OP_MODRM_RM_8_W, FCML_OP_IB, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RM8_IMM8 },
	/* 81 /6 iw XOR r/m16, int16 MI Valid Valid r/m16 XOR int16.*/
	/* 81 /6 id XOR r/m32, int32 MI Valid Valid r/m32 XOR int32.*/
	/* REX.W + 81 /6 id XOR r/m64, int32 MI Valid N.E. r/m64 XOR int32 (sign-extended).*/
    { FCML_AMT_GPI, 0x0807, 0x00C5B006, { 0x81, 0x00, 0x00 }, { FCML_OP_MODRM_RM_W, FCML_OP_EX_EOSA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RMO_IMMO },
	/* 83 /6 ib XOR r/m16, int8 MI Valid Valid r/m16 XOR int8 (sign-extended).*/
	/* 83 /6 ib XOR r/m32, int8 MI Valid Valid r/m32 XOR int8 (sign-extended).*/
	/* REX.W + 83 /6 ib XOR r/m64, int8 MI Valid N.E. r/m64 XOR int8 (sign-extended).*/
    { FCML_AMT_GPI, 0x0807, 0x00C5B006, { 0x83, 0x00, 0x00 }, { FCML_OP_MODRM_RM_W, FCML_OP_IB_EX_EOSA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RMO_IMM8 },
	/* 30 /r XOR r/m8, r8 MR Valid Valid r/m8 XOR r8.*/
	/* REX + 30 /r XOR r/m8*, r8* MR Valid N.E. r/m8 XOR r8.*/
    { FCML_AMT_GPI, 0x0807, 0x00C48002, { 0x30, 0x00, 0x00 }, { FCML_OP_MODRM_RM_OP_8_W, FCML_OP_MODRM_R_8, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RM8_R8 },
	/* 31 /r XOR r/m16, r16 MR Valid Valid r/m16 XOR r16.*/
	/* 31 /r XOR r/m32, r32 MR Valid Valid r/m32 XOR r32.*/
	/* REX.W + 31 /r XOR r/m64, r64 MR Valid N.E. r/m64 XOR r64.*/
    { FCML_AMT_GPI, 0x0807, 0x00C48002, { 0x31, 0x00, 0x00 }, { FCML_OP_MODRM_RM_OP_W, FCML_OP_MODRM_R, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RMO_RO },
	/* 32 /r XOR r8, r/m8 RM Valid Valid r8 XOR r/m8.*/
	/* REX + 32 /r XOR r8*, r/m8* RM Valid N.E. r8 XOR r/m8.*/
    { FCML_AMT_GPI, 0x0000, 0x00C48002, { 0x32, 0x00, 0x00 }, { FCML_OP_MODRM_R_8_W, FCML_OP_MODRM_RM_OP_8, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_R8_RM8 },
	/* 33 /r XOR r16, r/m16 RM Valid Valid r16 XOR r/m16.*/
	/* 33 /r XOR r32, r/m32 RM Valid Valid r32 XOR r/m32.*/
	/* REX.W + 33 /r XOR r64, r/m64 RM Valid N.E. r64 XOR r/m64.*/
    { FCML_AMT_GPI, 0x0000, 0x00C48002, { 0x33, 0x00, 0x00 }, { FCML_OP_MODRM_R_W, FCML_OP_MODRM_RM_OP, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_RO_RMO }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_XORPD[] = {
	/* 66 0F 57 /r XORPD xmm1,xmm2/m128 RM V/V SSE2 Bitwise exclusive-OR of xmm2/m128 and xmm1.*/
    { FCML_AMT_SSE2_SIMD, 0x1000, 0x00D88000, { 0x0F, 0x57, 0x00 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VXORPD[] = {
	/* VEX.NDS.128.66.0F.WIG 57 /r VXORPD xmm1,xmm2,xmm3/m128 RVM V/V AVX Return the bitwise logical XOR of packed double-precision floating-point values in xmm2 and xmm3/mem.*/
	/* VEX.NDS.256.66.0F.WIG 57 /r VXORPD ymm1,ymm2,ymm3/m256 RVM V/V AVX Return the bitwise logical XOR of packed double-precision floating-point values in ymm2 and ymm3/mem.*/
    { FCML_AMT_AVX_SIMD, 0x1080, 0x00D88000, { 0x0F, 0x57, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_XORPS[] = {
	/* 0F 57 /r XORPS xmm1,xmm2/m128 RM V/V SSE Bitwise exclusive-OR of xmm2/m128 and xmm1.*/
    { FCML_AMT_SSE_SIMD, 0x0000, 0x00D88000, { 0x0F, 0x57, 0x00 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VXORPS[] = {
	/* VEX.NDS.128.0F.WIG 57 /r VXORPS xmm1,xmm2,xmm3/m128 RVM V/V AVX Return the bitwise logical XOR of packed single-precision floating-point values in xmm2 and xmm3/mem.*/
	/* VEX.NDS.256.0F.WIG 57 /r VXORPS ymm1,ymm2,ymm3/m256 RVM V/V AVX Return the bitwise logical XOR of packed single-precision floating-point values in ymm2 and ymm3/mem.*/
    { FCML_AMT_AVX_SIMD, 0x0080, 0x00D88000, { 0x0F, 0x57, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_XRSTOR[] = {
	/* 0F AE /5 XRSTOR mem M Valid Valid Restore processor extended states from memory. The states are specified by EDX:EAX*/
    { FCML_AMT_SYSTEM, 0x0010, 0x03D9A800, { 0x0F, 0xAE, 0x00 }, { FCML_OP_MODRM_M_OP_512B, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_XRSTOR64[] = {
	/* REX.W+ 0F AE /5 XRSTOR64 mem M Valid N.E. Restore processor extended states from memory. The states are specified by EDX:EAX*/
    { FCML_AMT_SYSTEM, 0x0008, 0x0499A800, { 0x0F, 0xAE, 0x00 }, { FCML_OP_MODRM_M_OP_512B, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_XSAVE[] = {
	/* 0F AE /4 XSAVE mem M Valid Valid Save processor extended states to memory. The states are specified by EDX:EAX*/
    { FCML_AMT_SYSTEM, 0x0010, 0x03D9A000, { 0x0F, 0xAE, 0x00 }, { FCML_OP_MODRM_M_OP_512B_W, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_XSAVE64[] = {
	/* REX.W+ 0F AE /4 XSAVE64 mem M Valid N.E. Save processor extended states to memory. The states are specified by EDX:EAX*/
    { FCML_AMT_SYSTEM, 0x0008, 0x0499A000, { 0x0F, 0xAE, 0x00 }, { FCML_OP_MODRM_M_OP_512B_W, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_XSAVEOPT[] = {
	/* 0F AE /6 XSAVEOPT mem M V/V XSAVEOPT Save processor extended states specified in EDX:EAX to memory, optimizing the state save operation if possible.*/
    { FCML_AMT_SYSTEM, 0x0010, 0x03D9B000, { 0x0F, 0xAE, 0x00 }, { FCML_OP_MODRM_M_UNDEF_W, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_XSAVEOPT64[] = {
	/* REX.W + 0F AE /6 XSAVEOPT64 mem M V/V XSAVEOPT Save processor extended states specified in EDX:EAX to memory, optimizing the state save operation if possible.*/
    { FCML_AMT_SYSTEM, 0x0008, 0x0499B000, { 0x0F, 0xAE, 0x00 }, { FCML_OP_MODRM_M_UNDEF_W, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_XSETBV[] = {
	/* 0F 01 D1 XSETBV NP Valid Valid Write the value in EDX:EAX to the XCR specified by ECX.*/
    { FCML_AMT_SYSTEM, 0x0000, 0x00EC0000, { 0x0F, 0x01, 0xD1 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

/****************
* AMD 3D Now!
****************/

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_FEMMS[] = {
	/* FEMMS 0F 0Eh Faster Enter/Exit of the MMX or floating-point state*/
    { FCML_AMT_3DNOW, 0x0000, 0x00D80000, { 0x0F, 0x0E, 0x00 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

fcml_st_def_instruction_code_desc fcml_st_def_instruction_code_def_AMD3DNOW[] = {
	{ F_PAVGUSB, 0xBF },
	{ F_PF2ID, 0x1D },
	{ F_PFACC, 0xAE },
	{ F_PFADD, 0x9E },
	{ F_PFCMPEQ, 0xB0 },
	{ F_PFCMPGE, 0x90 },
	{ F_PFCMPGT, 0xA0 },
	{ F_PFMAX, 0xA4 },
	{ F_PFMIN, 0x94 },
	{ F_PFMUL, 0xB4 },
	{ F_PFRCP, 0x96 },
	{ F_PFRCPIT1, 0xA6 },
	{ F_PFRCPIT2, 0xB6 },
	{ F_PFRSQIT1, 0xA7 },
	{ F_PFRSQRT, 0x97 },
	{ F_PFSUB, 0x9A },
	{ F_PFSUBR, 0xAA },
	{ F_PI2FD, 0x0D },
	{ F_PMULHRW, 0xB7 },
	{ F_PF2IW, 0x1C },
	{ F_PFNACC, 0x8A },
	{ F_PFPNACC, 0x8E },
	{ F_PI2FW, 0x0C },
	{ F_PSWAPD, 0xBB },
	{ 0, 0 }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_MI_AMD3DNOW[] = {
	/* PAVGUSB mmreg1, mmreg2/mem64 0F 0Fh / BFh Average of unsigned packed 8-bit values*/
    { FCML_AMT_3DNOW_SIMD, 0x8000, 0x00D88000, { 0x0F, 0x0F, 0x00 }, { FCML_OP_MODRM_R_MMX_W, FCML_OP_MODRM_RM_MMX_OP, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PREFETCH[] = {
	/* PREFETCH mem8 0F 0Dh Prefetch processor cache line into L1 data cache (Dcache)*/
    { FCML_AMT_3DNOW | FCML_AMT_PRFCHW, 0x0000, 0x00D98000, { 0x0F, 0x0D, 0x00 }, { FCML_OP_MODRM_M_OP_8, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PREFETCHW[] = {
	/* PREFETCHW mem8 0F 0Dh Prefetch processor cache line into L1 data cache (Dcache)*/
    { FCML_AMT_3DNOW | FCML_AMT_PRFCHW, 0x0000, 0x00D98800, { 0x0F, 0x0D, 0x00 }, { FCML_OP_MODRM_M_OP_8, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

/* FMA */

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VFMADD213PD[] = {
	/* VEX.DDS.128.66.0F38.W1 A8 /r VFMADD213PD xmm0,xmm1,xmm2/m128*/
	/* VEX.DDS.256.66.0F38.W1 A8 /r VFMADD213PD ymm0,ymm1,ymm2/m256*/
    { FCML_AMT_FMA, 0x1088, 0x00EC8000, { 0x0F, 0x38, 0xA8 }, { FCML_OP_MODRM_R_SIMD_L_RW, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VFMADDPD[] = {
	/* VFMADDPD xmm1, xmm2, xmm3/mem128, xmm4 C4 RXB.00011 0.src.0.01 69 /r /is4*/
	/* VFMADDPD ymm1, ymm2, ymm3/mem256, ymm4 C4 RXB.00011 0.src.1.01 69 /r /is4*/
    { FCML_AMT_FMA4, 0x1090, 0x00EC8000, { 0x0F, 0x3A, 0x69 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_OP_OPERAND_IS4, FCML_NA }, FCML_AM_UNKNOWN },
	/* VFMADDPD xmm1, xmm2, xmm3, xmm4/mem128 C4 RXB.00011 1.src.0.01 69 /r /is4*/
	/* VFMADDPD ymm1, ymm2, ymm3, ymm4/mem256 C4 RXB.00011 1.src.1.01 69 /r /is4*/
    { FCML_AMT_FMA4, 0x1088, 0x00EC8000, { 0x0F, 0x3A, 0x69 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_OPERAND_IS4, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VFMADD132PD[] = {
	/* VEX.DDS.128.66.0F38.W1 98 /r VFMADD132PD xmm0,xmm1,xmm2/m128*/
	/* VEX.DDS.256.66.0F38.W1 98 /r VFMADD132PD ymm0,ymm1,ymm2/m256*/
    { FCML_AMT_FMA, 0x1088, 0x00EC8000, { 0x0F, 0x38, 0x98 }, { FCML_OP_MODRM_R_SIMD_L_RW, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VFMADD231PD[] = {
	/* VEX.DDS.128.66.0F38.W1 B8 /r VFMADD231PD xmm0,xmm1,xmm2/m128*/
	/* VEX.DDS.256.66.0F38.W1 B8 /r VFMADD231PD ymm0,ymm1,ymm2/m256*/
    { FCML_AMT_FMA, 0x1088, 0x00EC8000, { 0x0F, 0x38, 0xB8 }, { FCML_OP_MODRM_R_SIMD_L_RW, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VFMADDPS[] = {
	/* VFMADDPS xmm1, xmm2, xmm3/mem128, xmm4 C4 RXB.00011 0.src.0.01 68 /r /is4*/
	/* VFMADDPS ymm1, ymm2, ymm3/mem256, ymm4 C4 RXB.00011 0.src.1.01 68 /r /is4*/
    { FCML_AMT_FMA4, 0x1090, 0x00EC8000, { 0x0F, 0x3A, 0x68 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_OP_OPERAND_IS4, FCML_NA }, FCML_AM_UNKNOWN },
	/* VFMADDPS xmm1, xmm2, xmm3, xmm4/mem128 C4 RXB.00011 1.src.0.01 68 /r /is4*/
	/* VFMADDPS ymm1, ymm2, ymm3, ymm4/mem256 C4 RXB.00011 1.src.1.01 68 /r /is4*/
    { FCML_AMT_FMA4, 0x1088, 0x00EC8000, { 0x0F, 0x3A, 0x68 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_OPERAND_IS4, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VFMADD231PS[] = {
	/* VEX.DDS.128.66.0F38.W0 B8 /r VFMADD231PS xmm0,xmm1,xmm2/m128*/
	/* VEX.DDS.256.66.0F38.W0 B8 /r VFMADD231PS ymm0,ymm1,ymm2/m256*/
    { FCML_AMT_FMA, 0x1090, 0x00EC8000, { 0x0F, 0x38, 0xB8 }, { FCML_OP_MODRM_R_SIMD_L_RW, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VFMADD132PS[] = {
	/* VEX.DDS.128.66.0F38.W0 98 /r VFMADD132PS xmm0,xmm1,xmm2/m128*/
	/* VEX.DDS.256.66.0F38.W0 98 /r VFMADD132PS ymm0,ymm1,ymm2/m256*/
    { FCML_AMT_FMA, 0x1090, 0x00EC8000, { 0x0F, 0x38, 0x98 }, { FCML_OP_MODRM_R_SIMD_L_RW, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VFMADD213PS[] = {
	/* VEX.DDS.128.66.0F38.W0 A8 /r VFMADD213PS xmm0,xmm1,xmm2/m128*/
	/* VEX.DDS.256.66.0F38.W0 A8 /r VFMADD213PS ymm0,ymm1,ymm2/m256*/
    { FCML_AMT_FMA, 0x1090, 0x00EC8000, { 0x0F, 0x38, 0xA8 }, { FCML_OP_MODRM_R_SIMD_L_RW, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VFMADD132SD[] = {
	/* VEX.DDS.LIG.128.66.0F38.W1 99 /r VFMADD132SD xmm0,xmm1,xmm2/m64*/
    { FCML_AMT_FMA, 0x10C8, 0x00EC8000, { 0x0F, 0x38, 0x99 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_64, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VFMADD213SD[] = {
	/* VEX.DDS.LIG.128.66.0F38.W1 A9 /r VFMADD213SD xmm0,xmm1,xmm2/m64*/
    { FCML_AMT_FMA, 0x10C8, 0x00EC8000, { 0x0F, 0x38, 0xA9 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_64, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VFMADDSD[] = {
	/* VFMADDSD xmm1, xmm2, xmm3/mem128, xmm4 C4 RXB.00011 0.src.X.01 6B /r /is4*/
    { FCML_AMT_FMA4, 0x10D0, 0x00EC8000, { 0x0F, 0x3A, 0x6B }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_OP_OPERAND_IS4, FCML_NA }, FCML_AM_UNKNOWN },
	/* VFMADDSD xmm1, xmm2, xmm3, xmm4/mem128 C4 RXB.00011 1.src.X.01 6B /r /is4*/
    { FCML_AMT_FMA4, 0x10C8, 0x00EC8000, { 0x0F, 0x3A, 0x6B }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_OPERAND_IS4, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VFMADD231SD[] = {
	/* VEX.DDS.LIG.128.66.0F38.W1 B9 /r VFMADD231SD xmm0,xmm1,xmm2/m64*/
    { FCML_AMT_FMA, 0x10C8, 0x00EC8000, { 0x0F, 0x38, 0xB9 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_64, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VFMADD132SS[] = {
	/* VEX.DDS.LIG.128.66.0F38.W0 99 /r VFMADD132SS xmm0,xmm1,xmm2/m32*/
    { FCML_AMT_FMA, 0x10D0, 0x00EC8000, { 0x0F, 0x38, 0x99 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_32, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VFMADD213SS[] = {
	/* VEX.DDS.LIG.128.66.0F38.W0 A9 /r VFMADD213SS xmm0,xmm1,xmm2/m32*/
    { FCML_AMT_FMA, 0x10D0, 0x00EC8000, { 0x0F, 0x38, 0xA9 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_32, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VFMADDSS[] = {
	/* VFMADDSS xmm1, xmm2, xmm3/mem32, xmm4 C4 RXB.00011 0.src.X.01 6A /r /is4*/
    { FCML_AMT_FMA4, 0x10D0, 0x00EC8000, { 0x0F, 0x3A, 0x6A }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_32, FCML_OP_OPERAND_IS4, FCML_NA }, FCML_AM_UNKNOWN },
	/* VFMADDSS xmm1, xmm2, xmm3, xmm4/mem32 C4 RXB.00011 1.src.X.01 6A /r /is4*/
    { FCML_AMT_FMA4, 0x10C8, 0x00EC8000, { 0x0F, 0x3A, 0x6A }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_OPERAND_IS4, FCML_OP_MODRM_RM_XMM_OP_32, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VFMADD231SS[] = {
	/* VEX.DDS.LIG.128.66.0F38.W0 B9 /r VFMADD231SS xmm0,xmm1,xmm2/m32*/
    { FCML_AMT_FMA, 0x10D0, 0x00EC8000, { 0x0F, 0x38, 0xB9 }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_32, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VFMADDSUB132PD[] = {
	/* VEX.DDS.128.66.0F38.W1 96 /r VFMADDSUB132PD xmm0,xmm1,xmm2/m128*/
	/* VEX.DDS.256.66.0F38.W1 96 /r VFMADDSUB132PD ymm0,ymm1,ymm2/m256*/
    { FCML_AMT_FMA, 0x1088, 0x00EC8000, { 0x0F, 0x38, 0x96 }, { FCML_OP_MODRM_R_SIMD_L_RW, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VFMADDSUB213PD[] = {
	/* VEX.DDS.128.66.0F38.W1 A6 /r VFMADDSUB213PD xmm0,xmm1,xmm2/m128*/
	/* VEX.DDS.256.66.0F38.W1 A6 /r VFMADDSUB213PD ymm0,ymm1,ymm2/m256*/
    { FCML_AMT_FMA, 0x1088, 0x00EC8000, { 0x0F, 0x38, 0xA6 }, { FCML_OP_MODRM_R_SIMD_L_RW, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VFMADDSUBPD[] = {
	/* VFMADDSUBPD xmm1, xmm2, xmm3/mem128, xmm4 C4 RXB.00011 0.src.0.01 5D /r /is4*/
	/* VFMADDSUBPD ymm1, ymm2, ymm3/mem256, ymm4 C4 RXB.00011 0.src.1.01 5D /r /is4*/
    { FCML_AMT_FMA4, 0x1090, 0x00EC8000, { 0x0F, 0x3A, 0x5D }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_OP_OPERAND_IS4, FCML_NA }, FCML_AM_UNKNOWN },
	/* VFMADDSUBPD xmm1, xmm2, xmm3, xmm4/mem128 C4 RXB.00011 1.src.0.01 5D /r /is4*/
	/* VFMADDSUBPD ymm1, ymm2, ymm3, ymm4/mem256 C4 RXB.00011 1.src.1.01 5D /r /is4*/
    { FCML_AMT_FMA4, 0x1088, 0x00EC8000, { 0x0F, 0x3A, 0x5D }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_OPERAND_IS4, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VFMADDSUB231PD[] = {
	/* VEX.DDS.128.66.0F38.W1 B6 /r VFMADDSUB231PD xmm0,xmm1,xmm2/m128*/
	/* VEX.DDS.256.66.0F38.W1 B6 /r VFMADDSUB231PD ymm0,ymm1,ymm2/m256*/
    { FCML_AMT_FMA, 0x1088, 0x00EC8000, { 0x0F, 0x38, 0xB6 }, { FCML_OP_MODRM_R_SIMD_L_RW, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VFMADDSUB231PS[] = {
	/* VEX.DDS.128.66.0F38.W0 B6 /r VFMADDSUB231PS xmm0,xmm1,xmm2/m128*/
	/* VEX.DDS.256.66.0F38.W0 B6 /r VFMADDSUB231PS ymm0,ymm1,ymm2/m256*/
    { FCML_AMT_FMA, 0x1090, 0x00EC8000, { 0x0F, 0x38, 0xB6 }, { FCML_OP_MODRM_R_SIMD_L_RW, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VFMADDSUBPS[] = {
	/* VFMADDSUBPS xmm1, xmm2, xmm3/mem128, xmm4 C4 RXB.00011 0.src.0.01 5C /r /is4*/
	/* VFMADDSUBPS ymm1, ymm2, ymm3/mem256, ymm4 C4 RXB.00011 0.src.1.01 5C /r /is4*/
    { FCML_AMT_FMA4, 0x1090, 0x00EC8000, { 0x0F, 0x3A, 0x5C }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_OP_OPERAND_IS4, FCML_NA }, FCML_AM_UNKNOWN },
	/* VFMADDSUBPS xmm1, xmm2, xmm3, xmm4/mem128 C4 RXB.00011 1.src.0.01 5C /r /is4*/
	/* VFMADDSUBPS ymm1, ymm2, ymm3, ymm4/mem256 C4 RXB.00011 1.src.1.01 5C /r /is4*/
    { FCML_AMT_FMA4, 0x1088, 0x00EC8000, { 0x0F, 0x3A, 0x5C }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_OPERAND_IS4, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VFMADDSUB132PS[] = {
	/* VEX.DDS.128.66.0F38.W0 96 /r VFMADDSUB132PS xmm0,xmm1,xmm2/m128*/
	/* VEX.DDS.256.66.0F38.W0 96 /r VFMADDSUB132PS ymm0,ymm1,ymm2/m256*/
    { FCML_AMT_FMA, 0x1090, 0x00EC8000, { 0x0F, 0x38, 0x96 }, { FCML_OP_MODRM_R_SIMD_L_RW, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VFMADDSUB213PS[] = {
	/* VEX.DDS.128.66.0F38.W0 A6 /r VFMADDSUB213PS xmm0,xmm1,xmm2/m128*/
	/* VEX.DDS.256.66.0F38.W0 A6 /r VFMADDSUB213PS ymm0,ymm1,ymm2/m256*/
    { FCML_AMT_FMA, 0x1090, 0x00EC8000, { 0x0F, 0x38, 0xA6 }, { FCML_OP_MODRM_R_SIMD_L_RW, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VFMSUBADDPD[] = {
	/* VFMSUBADDPD xmm1, xmm2, xmm3/mem128, xmm4 C4 RXB.00011 0.src.0.01 5F /r /is4*/
	/* VFMSUBADDPD ymm1, ymm2, ymm3/mem256, ymm4 C4 RXB.00011 0.src.1.01 5F /r /is4*/
    { FCML_AMT_FMA4, 0x1090, 0x00EC8000, { 0x0F, 0x3A, 0x5F }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_OP_OPERAND_IS4, FCML_NA }, FCML_AM_UNKNOWN },
	/* VFMSUBADDPD xmm1, xmm2, xmm3, xmm4/mem128 C4 RXB.00011 1.src.0.01 5F /r /is4*/
	/* VFMSUBADDPD ymm1, ymm2, ymm3, ymm4/mem256 C4 RXB.00011 1.src.1.01 5F /r /is4*/
    { FCML_AMT_FMA4, 0x1088, 0x00EC8000, { 0x0F, 0x3A, 0x5F }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_OPERAND_IS4, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VFMSUBADD213PD[] = {
	/* VEX.DDS.128.66.0F38.W1 A7 /r VFMSUBADD213PD xmm0,xmm1,xmm2/m128*/
	/* VEX.DDS.256.66.0F38.W1 A7 /r VFMSUBADD213PD ymm0,ymm1,ymm2/m256*/
    { FCML_AMT_FMA, 0x1088, 0x00EC8000, { 0x0F, 0x38, 0xA7 }, { FCML_OP_MODRM_R_SIMD_L_RW, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VFMSUBADD132PD[] = {
	/* VEX.DDS.128.66.0F38.W1 97 /r VFMSUBADD132PD xmm0,xmm1,xmm2/m128*/
    { FCML_AMT_FMA, 0x1088, 0x00EC8000, { 0x0F, 0x38, 0x97 }, { FCML_OP_MODRM_R_SIMD_L_RW, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VFMSUBADD231PD[] = {
	/* VEX.DDS.128.66.0F38.W1 B7 /r VFMSUBADD231PD xmm0,xmm1,xmm2/m128*/
	/* VEX.DDS.256.66.0F38.W1 B7 /r VFMSUBADD231PD ymm0,ymm1,ymm2/m256*/
    { FCML_AMT_FMA, 0x1088, 0x00EC8000, { 0x0F, 0x38, 0xB7 }, { FCML_OP_MODRM_R_SIMD_L_RW, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VFMSUBADDPS[] = {
	/* VFMSUBADDPS xmm1, xmm2, xmm3/mem128, xmm4 C4 RXB.00011 0.src.0.01 5E /r /is4*/
	/* VFMSUBADDPS ymm1, ymm2, ymm3/mem256, ymm4 C4 RXB.00011 0.src.1.01 5E /r /is4*/
    { FCML_AMT_FMA4, 0x1090, 0x00EC8000, { 0x0F, 0x3A, 0x5E }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_OP_OPERAND_IS4, FCML_NA }, FCML_AM_UNKNOWN },
	/* VFMSUBADDPS xmm1, xmm2, xmm3, xmm4/mem128 C4 RXB.00011 1.src.0.01 5E /r /is4*/
	/* VFMSUBADDPS ymm1, ymm2, ymm3, ymm4/mem256 C4 RXB.00011 1.src.1.01 5E /r /is4*/
    { FCML_AMT_FMA4, 0x1088, 0x00EC8000, { 0x0F, 0x3A, 0x5E }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_OPERAND_IS4, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VFMSUBADD213PS[] = {
	/* VEX.DDS.128.66.0F38.W0 A7 /r VFMSUBADD213PS xmm0,xmm1,xmm2/m128*/
	/* VEX.DDS.256.66.0F38.W0 A7 /r VFMSUBADD213PS ymm0,ymm1,ymm2/m256*/
    { FCML_AMT_FMA, 0x1090, 0x00EC8000, { 0x0F, 0x38, 0xA7 }, { FCML_OP_MODRM_R_SIMD_L_RW, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VFMSUBADD132PS[] = {
	/* VEX.DDS.128.66.0F38.W0 97 /r VFMSUBADD132PS xmm0,xmm1,xmm2/m128*/
	/* VEX.DDS.256.66.0F38.W0 97 /r VFMSUBADD132PS ymm0,ymm1,ymm2/m256*/
    { FCML_AMT_FMA, 0x1090, 0x00EC8000, { 0x0F, 0x38, 0x97 }, { FCML_OP_MODRM_R_SIMD_L_RW, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VFMSUBADD231PS[] = {
	/* VEX.DDS.128.66.0F38.W0 B7 /r VFMSUBADD231PS xmm0,xmm1,xmm2/m128*/
	/* VEX.DDS.256.66.0F38.W0 B7 /r VFMSUBADD231PS ymm0,ymm1,ymm2/m256*/
    { FCML_AMT_FMA, 0x1090, 0x00EC8000, { 0x0F, 0x38, 0xB7 }, { FCML_OP_MODRM_R_SIMD_L_RW, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VFMSUB213PD[] = {
	/* VEX.DDS.128.66.0F38.W1 AA /r VFMSUB213PD xmm0,xmm1,xmm2/m128*/
	/* VEX.DDS.256.66.0F38.W1 AA /r VFMSUB213PD ymm0,ymm1,ymm2/m256*/
    { FCML_AMT_FMA, 0x1088, 0x00EC8000, { 0x0F, 0x38, 0xAA }, { FCML_OP_MODRM_R_SIMD_L_RW, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VFMSUBPD[] = {
	/* VFMSUBPD xmm1, xmm2, xmm3/mem128, xmm4 C4 RXB.00011 0.src.0.01 6D /r /is4*/
	/* VFMSUBPD ymm1, ymm2, ymm3/mem256, ymm4 C4 RXB.00011 0.src.1.01 6D /r /is4*/
    { FCML_AMT_FMA4, 0x1090, 0x00EC8000, { 0x0F, 0x3A, 0x6D }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_OP_OPERAND_IS4, FCML_NA }, FCML_AM_UNKNOWN },
	/* VFMSUBPD xmm1, xmm2, xmm3, xmm4/mem128 C4 RXB.00011 1.src.0.01 6D /r /is4*/
	/* VFMSUBPD ymm1, ymm2, ymm3, ymm4/mem256 C4 RXB.00011 1.src.1.01 6D /r /is4*/
    { FCML_AMT_FMA4, 0x1088, 0x00EC8000, { 0x0F, 0x3A, 0x6D }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_OPERAND_IS4, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VFMSUB132PD[] = {
	/* VEX.DDS.128.66.0F38.W1 9A /r VFMSUB132PD xmm0,xmm1,xmm2/m128*/
	/* VEX.DDS.256.66.0F38.W1 9A /r VFMSUB132PD ymm0,ymm1,ymm2/m256*/
    { FCML_AMT_FMA, 0x1088, 0x00EC8000, { 0x0F, 0x38, 0x9A }, { FCML_OP_MODRM_R_SIMD_L_RW, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VFMSUB231PD[] = {
	/* VEX.DDS.128.66.0F38.W1 BA /r VFMSUB231PD xmm0,xmm1,xmm2/m128*/
	/* VEX.DDS.256.66.0F38.W1 BA /r VFMSUB231PD ymm0,ymm1,ymm2/m256*/
    { FCML_AMT_FMA, 0x1088, 0x00EC8000, { 0x0F, 0x38, 0xBA }, { FCML_OP_MODRM_R_SIMD_L_RW, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VFMSUB213PS[] = {
	/* VEX.DDS.128.66.0F38.W0 AA /r VFMSUB213PS xmm0,xmm1,xmm2/m128*/
	/* VEX.DDS.256.66.0F38.W0 AA /r VFMSUB213PS ymm0,ymm1,ymm2/m256*/
    { FCML_AMT_FMA, 0x1090, 0x00EC8000, { 0x0F, 0x38, 0xAA }, { FCML_OP_MODRM_R_SIMD_L_RW, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VFMSUBPS[] = {
	/* VFMSUBPS xmm1, xmm2, xmm3/mem128, xmm4 C4 RXB.00011 0.src.0.01 6C /r /is4*/
	/* VFMSUBPS ymm1, ymm2, ymm3/mem256, ymm4 C4 RXB.00011 0.src.1.01 6C /r /is4*/
    { FCML_AMT_FMA4, 0x1090, 0x00EC8000, { 0x0F, 0x3A, 0x6C }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_OP_OPERAND_IS4, FCML_NA }, FCML_AM_UNKNOWN },
	/* VFMSUBPS xmm1, xmm2, xmm3, xmm4/mem128 C4 RXB.00011 1.src.0.01 6C /r /is4*/
	/* VFMSUBPS ymm1, ymm2, ymm3, ymm4/mem256 C4 RXB.00011 1.src.1.01 6C /r /is4*/
    { FCML_AMT_FMA4, 0x1088, 0x00EC8000, { 0x0F, 0x3A, 0x6C }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_OPERAND_IS4, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VFMSUB132PS[] = {
	/* VEX.DDS.128.66.0F38.W0 9A /r VFMSUB132PS xmm0,xmm1,xmm2/m128*/
	/* VEX.DDS.256.66.0F38.W0 9A /r VFMSUB132PS ymm0,ymm1,ymm2/m256*/
    { FCML_AMT_FMA, 0x1090, 0x00EC8000, { 0x0F, 0x38, 0x9A }, { FCML_OP_MODRM_R_SIMD_L_RW, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VFMSUB231PS[] = {
	/* VEX.DDS.128.66.0F38.W0 BA /r VFMSUB231PS xmm0,xmm1,xmm2/m128*/
	/* VEX.DDS.256.66.0F38.W0 BA /r VFMSUB231PS ymm0,ymm1,ymm2/m256*/
    { FCML_AMT_FMA, 0x1090, 0x00EC8000, { 0x0F, 0x38, 0xBA }, { FCML_OP_MODRM_R_SIMD_L_RW, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VFMSUBSD[] = {
	/* VFMSUBSD xmm1, xmm2, xmm3/mem64, xmm4 C4 RXB.00011 0.src.X.01 6F /r /is4*/
    { FCML_AMT_FMA4, 0x10D0, 0x00EC8000, { 0x0F, 0x3A, 0x6F }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_64, FCML_OP_OPERAND_IS4, FCML_NA }, FCML_AM_UNKNOWN },
	/* VFMSUBSD xmm1, xmm2, xmm3, xmm4/mem64 C4 RXB.00011 1.src.X.01 6F /r /is4*/
    { FCML_AMT_FMA4, 0x10C8, 0x00EC8000, { 0x0F, 0x3A, 0x6F }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_OPERAND_IS4, FCML_OP_MODRM_RM_XMM_OP_64, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VFMSUB231SD[] = {
	/* VEX.DDS.LIG.128.66.0F38.W1 BB /r VFMSUB231SD xmm0,xmm1,xmm2/m64*/
    { FCML_AMT_FMA, 0x10C8, 0x00EC8000, { 0x0F, 0x38, 0xBB }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_OP_64, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VFMSUB132SD[] = {
	/* VEX.DDS.LIG.128.66.0F38.W1 9B /r VFMSUB132SD xmm0,xmm1,xmm2/m64*/
    { FCML_AMT_FMA, 0x10C8, 0x00EC8000, { 0x0F, 0x38, 0x9B }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_OP_64, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VFMSUB213SD[] = {
	/* VEX.DDS.LIG.128.66.0F38.W1 AB /r VFMSUB213SD xmm0,xmm1,xmm2/m64*/
    { FCML_AMT_FMA, 0x10C8, 0x00EC8000, { 0x0F, 0x38, 0xAB }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_OP_64, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VFMSUB231SS[] = {
	/* VEX.DDS.LIG.128.66.0F38.W0 BB /r VFMSUB231SS xmm0,xmm1,xmm2/m32*/
    { FCML_AMT_FMA, 0x10D0, 0x00EC8000, { 0x0F, 0x38, 0xBB }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_OP_32, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VFMSUB213SS[] = {
	/* VEX.DDS.LIG.128.66.0F38.W0 AB /r VFMSUB213SS xmm0,xmm1,xmm2/m32*/
    { FCML_AMT_FMA, 0x10D0, 0x00EC8000, { 0x0F, 0x38, 0xAB }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_OP_32, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VFMSUB132SS[] = {
	/* VEX.DDS.LIG.128.66.0F38.W0 9B /r VFMSUB132SS xmm0,xmm1,xmm2/m32*/
    { FCML_AMT_FMA, 0x10D0, 0x00EC8000, { 0x0F, 0x38, 0x9B }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_OP_32, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VFMSUBSS[] = {
	/* VFMSUBSS xmm1, xmm2, xmm3/mem32, xmm4 C4 RXB.00011 0.src.X.01 6E /r /is4*/
    { FCML_AMT_FMA4, 0x10D0, 0x00EC8000, { 0x0F, 0x3A, 0x6E }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_32, FCML_OP_OPERAND_IS4, FCML_NA }, FCML_AM_UNKNOWN },
	/* VFMSUBSS xmm1, xmm2, xmm3, xmm4/mem32 C4 RXB.00011 1.src.X.01 6E /r /is4*/
    { FCML_AMT_FMA4, 0x10C8, 0x00EC8000, { 0x0F, 0x3A, 0x6E }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_OPERAND_IS4, FCML_OP_MODRM_RM_XMM_OP_32, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VFNMADD231PD[] = {
	/* VEX.DDS.128.66.0F38.W1 BC /r VFNMADD231PD xmm0,xmm1,xmm2/m128*/
	/* VEX.DDS.256.66.0F38.W1 BC /r VFNMADD231PD ymm0,ymm1,ymm2/m256*/
    { FCML_AMT_FMA, 0x1088, 0x00EC8000, { 0x0F, 0x38, 0xBC }, { FCML_OP_MODRM_R_SIMD_L_RW, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VFNMADDPD[] = {
	/* VFNMADDPD xmm1, xmm2, xmm3/mem128, xmm4 C4 RXB.00011 0.src.0.01 79 /r /is4*/
	/* VFNMADDPD ymm1, ymm2, ymm3/mem256, ymm4 C4 RXB.00011 0.src.1.01 79 /r /is4*/
    { FCML_AMT_FMA4, 0x1090, 0x00EC8000, { 0x0F, 0x3A, 0x79 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_OP_OPERAND_IS4, FCML_NA }, FCML_AM_UNKNOWN },
	/* VFNMADDPD xmm1, xmm2, xmm3, xmm4/mem128 C4 RXB.00011 1.src.0.01 79 /r /is4*/
	/* VFNMADDPD ymm1, ymm2, ymm3, ymm4/mem256 C4 RXB.00011 1.src.1.01 79 /r /is4*/
    { FCML_AMT_FMA4, 0x1088, 0x00EC8000, { 0x0F, 0x3A, 0x79 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_OPERAND_IS4, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VFNMADD132PD[] = {
	/* VEX.DDS.128.66.0F38.W1 9C /r VFNMADD132PD xmm0,xmm1,xmm2/m128*/
	/* VEX.DDS.256.66.0F38.W1 9C /r VFNMADD132PD ymm0,ymm1,ymm2/m256*/
    { FCML_AMT_FMA, 0x1088, 0x00EC8000, { 0x0F, 0x38, 0x9C }, { FCML_OP_MODRM_R_SIMD_L_RW, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VFNMADD213PD[] = {
	/* VEX.DDS.128.66.0F38.W1 AC /r VFNMADD213PD xmm0,xmm1,xmm2/m128*/
	/* VEX.DDS.256.66.0F38.W1 AC /r VFNMADD213PD ymm0,ymm1,ymm2/m256*/
    { FCML_AMT_FMA, 0x1088, 0x00EC8000, { 0x0F, 0x38, 0xAC }, { FCML_OP_MODRM_R_SIMD_L_RW, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VFNMADD231PS[] = {
	/* VEX.DDS.128.66.0F38.W0 BC /r VFNMADD231PS xmm0,xmm1,xmm2/m128*/
	/* VEX.DDS.256.66.0F38.W0 BC /r VFNMADD231PS ymm0,ymm1,ymm2/m256*/
    { FCML_AMT_FMA, 0x1090, 0x00EC8000, { 0x0F, 0x38, 0xBC }, { FCML_OP_MODRM_R_SIMD_L_RW, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VFNMADD132PS[] = {
	/* VEX.DDS.128.66.0F38.W0 9C /r VFNMADD132PS xmm0,xmm1,xmm2/m128*/
	/* VEX.DDS.256.66.0F38.W0 9C /r VFNMADD132PS ymm0,ymm1,ymm2/m256*/
    { FCML_AMT_FMA, 0x1090, 0x00EC8000, { 0x0F, 0x38, 0x9C }, { FCML_OP_MODRM_R_SIMD_L_RW, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VFNMADD213PS[] = {
	/* VEX.DDS.128.66.0F38.W0 AC /r VFNMADD213PS xmm0,xmm1,xmm2/m128*/
	/* VEX.DDS.256.66.0F38.W0 AC /r VFNMADD213PS ymm0,ymm1,ymm2/m256*/
    { FCML_AMT_FMA, 0x1090, 0x00EC8000, { 0x0F, 0x38, 0xAC }, { FCML_OP_MODRM_R_SIMD_L_RW, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VFNMADDPS[] = {
	/* VFNMADDPS xmm1, xmm2, xmm3/mem128, xmm4 C4 RXB.00011 0.src.0.01 78 /r /is4*/
	/* VFNMADDPS ymm1, ymm2, ymm3/mem256, ymm4 C4 RXB.00011 0.src.1.01 78 /r /is4*/
    { FCML_AMT_FMA4, 0x1090, 0x00EC8000, { 0x0F, 0x3A, 0x78 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_OP_OPERAND_IS4, FCML_NA }, FCML_AM_UNKNOWN },
	/* VFNMADDPS xmm1, xmm2, xmm3, xmm4/mem128 C4 RXB.00011 1.src.0.01 78 /r /is4*/
	/* VFNMADDPS ymm1, ymm2, ymm3, ymm4/mem256 C4 RXB.00011 1.src.1.01 78 /r /is4*/
    { FCML_AMT_FMA4, 0x1088, 0x00EC8000, { 0x0F, 0x3A, 0x78 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_OPERAND_IS4, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VFNMADD213SD[] = {
	/* VEX.DDS.LIG.128.66.0F38.W1 AD /r VFNMADD213SD xmm0,xmm1,xmm2/m64*/
    { FCML_AMT_FMA, 0x10C8, 0x00EC8000, { 0x0F, 0x38, 0xAD }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_OP_64, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VFNMADDSD[] = {
	/* VFNMADDSD xmm1, xmm2, xmm3/mem64, xmm4 C4 RXB.00011 0.src.X.01 7B /r /is4*/
    { FCML_AMT_FMA4, 0x10D0, 0x00EC8000, { 0x0F, 0x3A, 0x7B }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_64, FCML_OP_OPERAND_IS4, FCML_NA }, FCML_AM_UNKNOWN },
	/* VFNMADDSD xmm1, xmm2, xmm3, xmm4/mem64 C4 RXB.00011 1.src.X.01 7B /r /is4*/
    { FCML_AMT_FMA4, 0x10C8, 0x00EC8000, { 0x0F, 0x3A, 0x7B }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_OPERAND_IS4, FCML_OP_MODRM_RM_XMM_OP_64, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VFNMADD231SD[] = {
	/* VEX.DDS.LIG.128.66.0F38.W1 BD /r VFNMADD231SD xmm0,xmm1,xmm2/m64*/
    { FCML_AMT_FMA, 0x10C8, 0x00EC8000, { 0x0F, 0x38, 0xBD }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_OP_64, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VFNMADD132SD[] = {
	/* VEX.DDS.LIG.128.66.0F38.W1 9D /r VFNMADD132SD xmm0,xmm1,xmm2/m64*/
    { FCML_AMT_FMA, 0x10C8, 0x00EC8000, { 0x0F, 0x38, 0x9D }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_OP_64, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VFNMADD213SS[] = {
	/* VEX.DDS.LIG.128.66.0F38.W0 AD /r VFNMADD213SS xmm0,xmm1,xmm2/m32*/
    { FCML_AMT_FMA, 0x10D0, 0x00EC8000, { 0x0F, 0x38, 0xAD }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_OP_32, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VFNMADDSS[] = {
	/* VFNMADDSS xmm1, xmm2, xmm3/mem32, xmm4 C4 RXB.00011 0.src.X.01 7A /r /is4*/
    { FCML_AMT_FMA4, 0x10D0, 0x00EC8000, { 0x0F, 0x3A, 0x7A }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_32, FCML_OP_OPERAND_IS4, FCML_NA }, FCML_AM_UNKNOWN },
	/* VFNMADDSS xmm1, xmm2, xmm3, xmm4/mem32 C4 RXB.00011 1.src.X.01 7A /r /is4*/
    { FCML_AMT_FMA4, 0x10C8, 0x00EC8000, { 0x0F, 0x3A, 0x7A }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_OPERAND_IS4, FCML_OP_MODRM_RM_XMM_OP_32, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VFNMADD231SS[] = {
	/* VEX.DDS.LIG.128.66.0F38.W0 BD /r VFNMADD231SS xmm0,xmm1,xmm2/m32*/
    { FCML_AMT_FMA, 0x10D0, 0x00EC8000, { 0x0F, 0x38, 0xBD }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_OP_32, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VFNMADD132SS[] = {
	/* VEX.DDS.LIG.128.66.0F38.W0 9D /r VFNMADD132SS xmm0,xmm1,xmm2/m32*/
    { FCML_AMT_FMA, 0x10D0, 0x00EC8000, { 0x0F, 0x38, 0x9D }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_OP_32, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VFNMSUB132PD[] = {
	/* VEX.DDS.128.66.0F38.W1 9E /r VFNMSUB132PD xmm0,xmm1,xmm2/m128*/
	/* VEX.DDS.256.66.0F38.W1 9E /r VFNMSUB132PD ymm0,ymm1,ymm2/m256*/
    { FCML_AMT_FMA, 0x1088, 0x00EC8000, { 0x0F, 0x38, 0x9E }, { FCML_OP_MODRM_R_SIMD_L_RW, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VFNMSUB213PD[] = {
	/* VEX.DDS.128.66.0F38.W1 AE /r VFNMSUB213PD xmm0,xmm1,xmm2/m128*/
	/* VEX.DDS.256.66.0F38.W1 AE /r VFNMSUB213PD ymm0,ymm1,ymm2/m256*/
    { FCML_AMT_FMA, 0x1088, 0x00EC8000, { 0x0F, 0x38, 0xAE }, { FCML_OP_MODRM_R_SIMD_L_RW, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VFNMSUB231PD[] = {
	/* VEX.DDS.128.66.0F38.W1 BE /r VFNMSUB231PD xmm0,xmm1,xmm2/m128*/
	/* VEX.DDS.256.66.0F38.W1 BE /r VFNMSUB231PD ymm0,ymm1,ymm2/m256*/
    { FCML_AMT_FMA, 0x1088, 0x00EC8000, { 0x0F, 0x38, 0xBE }, { FCML_OP_MODRM_R_SIMD_L_RW, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VFNMSUBPD[] = {
	/* VFNMSUBPD xmm1, xmm2, xmm3/mem128, xmm4 C4 RXB.00011 0.src.0.01 7D /r /is4*/
	/* VFNMSUBPD ymm1, ymm2, ymm3/mem256, ymm4 C4 RXB.00011 0.src.1.01 7D /r /is4*/
    { FCML_AMT_FMA4, 0x1090, 0x00EC8000, { 0x0F, 0x3A, 0x7D }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_OP_OPERAND_IS4, FCML_NA }, FCML_AM_UNKNOWN },
	/* VFNMSUBPD xmm1, xmm2, xmm3, xmm4/mem128 C4 RXB.00011 1.src.0.01 7D /r /is4*/
	/* VFNMSUBPD ymm1, ymm2, ymm3, ymm4/mem256 C4 RXB.00011 1.src.1.01 7D /r /is4*/
    { FCML_AMT_FMA4, 0x1088, 0x00EC8000, { 0x0F, 0x3A, 0x7D }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_OPERAND_IS4, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VFNMSUBPS[] = {
	/* VFNMSUBPS xmm1, xmm2, xmm3/mem128, xmm4 C4 RXB.00011 0.src.0.01 7C /r /is4*/
	/* VFNMSUBPS ymm1, ymm2, ymm3/mem256, ymm4 C4 RXB.00011 0.src.1.01 7C /r /is4*/
    { FCML_AMT_FMA4, 0x1090, 0x00EC8000, { 0x0F, 0x3A, 0x7C }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_OP_OPERAND_IS4, FCML_NA }, FCML_AM_UNKNOWN },
	/* VFNMSUBPS xmm1, xmm2, xmm3, xmm4/mem128 C4 RXB.00011 1.src.0.01 7C /r /is4*/
	/* VFNMSUBPS ymm1, ymm2, ymm3, ymm4/mem256 C4 RXB.00011 1.src.1.01 7C /r /is4*/
    { FCML_AMT_FMA4, 0x1088, 0x00EC8000, { 0x0F, 0x3A, 0x7C }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_OPERAND_IS4, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VFNMSUB213PS[] = {
	/* VEX.DDS.128.66.0F38.W0 AE /r VFNMSUB213PS xmm0,xmm1,xmm2/m128*/
	/* VEX.DDS.256.66.0F38.W0 AE /r VFNMSUB213PS ymm0,ymm1,ymm2/m256*/
    { FCML_AMT_FMA, 0x1090, 0x00EC8000, { 0x0F, 0x38, 0xAE }, { FCML_OP_MODRM_R_SIMD_L_RW, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VFNMSUB132PS[] = {
	/* VEX.DDS.128.66.0F38.W0 9E /r VFNMSUB132PS xmm0,xmm1,xmm2/m128*/
	/* VEX.DDS.256.66.0F38.W0 9E /r VFNMSUB132PS ymm0,ymm1,ymm2/m256*/
    { FCML_AMT_FMA, 0x1090, 0x00EC8000, { 0x0F, 0x38, 0x9E }, { FCML_OP_MODRM_R_SIMD_L_RW, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VFNMSUB231PS[] = {
	/* VEX.DDS.128.66.0F38.W0 BE /r VFNMSUB231PS xmm0,xmm1,xmm2/m128*/
	/* VEX.DDS.256.66.0F38.W0 BE /r VFNMSUB231PS ymm0,ymm1,ymm2/m256*/
    { FCML_AMT_FMA, 0x1090, 0x00EC8000, { 0x0F, 0x38, 0xBE }, { FCML_OP_MODRM_R_SIMD_L_RW, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VFNMSUBSD[] = {
	/* VFNMSUBSD xmm1, xmm2, xmm3/mem64, xmm4 C4 RXB.00011 0.src.X.01 7F /r /is4*/
    { FCML_AMT_FMA4, 0x10D0, 0x00EC8000, { 0x0F, 0x3A, 0x7F }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_64, FCML_OP_OPERAND_IS4, FCML_NA }, FCML_AM_UNKNOWN },
	/* VFNMSUBSD xmm1, xmm2, xmm3, xmm4/mem64 C4 RXB.00011 1.src.X.01 7F /r /is4*/
    { FCML_AMT_FMA4, 0x10C8, 0x00EC8000, { 0x0F, 0x3A, 0x7F }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_OPERAND_IS4, FCML_OP_MODRM_RM_XMM_OP_64, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VFNMSUB231SD[] = {
	/* VEX.DDS.LIG.128.66.0F38.W1 BF /r VFNMSUB231SD xmm0,xmm1,xmm2/m64*/
    { FCML_AMT_FMA, 0x10C8, 0x00EC8000, { 0x0F, 0x38, 0xBF }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_OP_64, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VFNMSUB213SD[] = {
	/* VEX.DDS.LIG.128.66.0F38.W1 AF /r VFNMSUB213SD xmm0,xmm1,xmm2/m64*/
    { FCML_AMT_FMA, 0x10C8, 0x00EC8000, { 0x0F, 0x38, 0xAF }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_OP_64, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VFNMSUB132SD[] = {
	/* VEX.DDS.LIG.128.66.0F38.W1 9F /r VFNMSUB132SD xmm0,xmm1,xmm2/m64*/
    { FCML_AMT_FMA, 0x10C8, 0x00EC8000, { 0x0F, 0x38, 0x9F }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_OP_64, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VFNMSUBSS[] = {
	/* VFNMSUBSS xmm1, xmm2, xmm3/mem32, xmm4 C4 RXB.00011 0.src.X.01 7E /r /is4*/
    { FCML_AMT_FMA4, 0x10D0, 0x00EC8000, { 0x0F, 0x3A, 0x7E }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_32, FCML_OP_OPERAND_IS4, FCML_NA }, FCML_AM_UNKNOWN },
	/* VFNMSUBSS xmm1, xmm2, xmm3, xmm4/mem32 C4 RXB.00011 1.src.X.01 7E /r /is4*/
    { FCML_AMT_FMA4, 0x10C8, 0x00EC8000, { 0x0F, 0x3A, 0x7E }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_OPERAND_IS4, FCML_OP_MODRM_RM_XMM_OP_32, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VFNMSUB132SS[] = {
	/* VEX.DDS.LIG.128.66.0F38.W0 9F /r VFNMSUB132SS xmm0,xmm1,xmm2/m32*/
    { FCML_AMT_FMA, 0x10D0, 0x00EC8000, { 0x0F, 0x38, 0x9F }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_OP_32, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VFNMSUB213SS[] = {
	/* VEX.DDS.LIG.128.66.0F38.W0 AF /r VFNMSUB213SS xmm0,xmm1,xmm2/m32*/
    { FCML_AMT_FMA, 0x10D0, 0x00EC8000, { 0x0F, 0x38, 0xAF }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_OP_32, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VFNMSUB231SS[] = {
	/* VEX.DDS.LIG.128.66.0F38.W0 BF /r VFNMSUB231SS xmm0,xmm1,xmm2/m32*/
    { FCML_AMT_FMA, 0x10D0, 0x00EC8000, { 0x0F, 0x38, 0xBF }, { FCML_OP_MODRM_R_XMM_RW, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_XMM_OP_32, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

/* END OF FAM */

/* VEX-Encoded GPR instructions. */

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_ANDN[] = {
	/* VEX.NDS.LZ.0F38.W0 F2 /r ANDN r32a, r32b, r/m32*/
    { FCML_AMT_BMI1 | FCML_AMT_VEXx, 0x02D0, 0x00EC8000, { 0x0F, 0x38, 0xF2 }, { FCML_OP_MODRM_R_32_RW, FCML_OP_VEX_VVVV_REG( FCML_REG_GPR, FCML_EOS_DWORD ), FCML_OP_MODRM_RM_OP_32, FCML_NA, FCML_NA }, FCML_AM_R32A_RM32_R32B },
	/* VEX.NDS.LZ.0F38.W1 F2 /r ANDN r64a, r64b, r/m64*/
    { FCML_AMT_BMI1 | FCML_AMT_VEXx, 0x02C8, 0x00EC8000, { 0x0F, 0x38, 0xF2 }, { FCML_OP_MODRM_R_64_RW, FCML_OP_VEX_VVVV_REG( FCML_REG_GPR, FCML_EOS_QWORD ), FCML_OP_MODRM_RM_OP_64, FCML_NA, FCML_NA }, FCML_AM_R64A_RM64_R64B }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_BEXR[] = {
	/* VEX.NDS1.LZ.0F38.W0 F7 /r BEXR r32a, r/m32, r32b*/
    { FCML_AMT_BMI1 | FCML_AMT_VEXx, 0x02D0, 0x00EC8000, { 0x0F, 0x38, 0xF7 }, { FCML_OP_MODRM_R_32_W, FCML_OP_MODRM_RM_OP_32, FCML_OP_VEX_VVVV_REG( FCML_REG_GPR, FCML_EOS_DWORD ), FCML_NA, FCML_NA }, FCML_AM_R32A_RM32_R32B },
	/* VEX.NDS1.LZ.0F38.W1 F7 /r BEXR r64a, r/m64, r64b*/
    { FCML_AMT_BMI1 | FCML_AMT_VEXx, 0x02C8, 0x00EC8000, { 0x0F, 0x38, 0xF7 }, { FCML_OP_MODRM_R_64_W, FCML_OP_MODRM_RM_OP_64, FCML_OP_VEX_VVVV_REG( FCML_REG_GPR, FCML_EOS_QWORD ), FCML_NA, FCML_NA }, FCML_AM_R64A_RM64_R64B }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_BEXTR[] = {
	/* BEXTR reg32, reg/mem32, int32 8F RXB.0A 0.1111.0.00 10 /r /id*/
    { FCML_AMT_BMI1 | FCML_AMT_VEXx, 0x0550, 0x00D88000, { 0x0A, 0x10, 0x00 }, { FCML_OP_MODRM_R_32_W, FCML_OP_MODRM_RM_OP_32, FCML_OP_ID, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* BEXTR reg64, reg/mem64, int32 8F RXB.0A 1.1111.0.00 10 /r /id*/
    { FCML_AMT_BMI1 | FCML_AMT_VEXx, 0x0548, 0x00D88000, { 0x0A, 0x10, 0x00 }, { FCML_OP_MODRM_R_64_W, FCML_OP_MODRM_RM_OP_64, FCML_OP_ID, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_BLCFILL[] = {
	/* BLCFILL reg32, reg/mem32 8F RXB.09 0.dest.0.00 01 /1*/
    { FCML_AMT_TBM, 0x0450, 0x00D98800, { 0x09, 0x01, 0x00 }, { FCML_OP_VEX_VVVV_REG( FCML_REG_GPR, FCML_EOS_DWORD ) | FCML_OA_W, FCML_OP_MODRM_RM_OP_32, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_R32_RM32 },
	/* BLCFILL reg64, reg/mem64 8F RXB.09 1.dest.0.00 01 /1*/
    { FCML_AMT_TBM, 0x0448, 0x00D98800, { 0x09, 0x01, 0x00 }, { FCML_OP_VEX_VVVV_REG( FCML_REG_GPR, FCML_EOS_QWORD ) | FCML_OA_W, FCML_OP_MODRM_RM_OP_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_R64_RM64 }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_BLCI[] = {
	/* BLCI reg32, reg/mem32 8F RXB.09 0.dest.0.00 02 /6*/
    { FCML_AMT_TBM, 0x0450, 0x00D9B000, { 0x09, 0x02, 0x00 }, { FCML_OP_VEX_VVVV_REG( FCML_REG_GPR, FCML_EOS_DWORD ) | FCML_OA_W, FCML_OP_MODRM_RM_OP_32, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_R32_RM32 },
	/* BLCI reg64, reg/mem64 8F RXB.09 1.dest.0.00 02 /6*/
    { FCML_AMT_TBM, 0x0448, 0x00D9B000, { 0x09, 0x02, 0x00 }, { FCML_OP_VEX_VVVV_REG( FCML_REG_GPR, FCML_EOS_QWORD ) | FCML_OA_W, FCML_OP_MODRM_RM_OP_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_R64_RM64 }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_BLCIC[] = {
	/* BLCIC reg32, reg/mem32 8F RXB.09 0.dest.0.00 01 /5*/
    { FCML_AMT_TBM, 0x0450, 0x00D9A800, { 0x09, 0x01, 0x00 }, { FCML_OP_VEX_VVVV_REG( FCML_REG_GPR, FCML_EOS_DWORD ) | FCML_OA_W, FCML_OP_MODRM_RM_OP_32, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_R32_RM32 },
	/* BLCIC reg64, reg/mem64 8F RXB.09 1.dest.0.00 01 /5*/
    { FCML_AMT_TBM, 0x0448, 0x00D9A800, { 0x09, 0x01, 0x00 }, { FCML_OP_VEX_VVVV_REG( FCML_REG_GPR, FCML_EOS_QWORD ) | FCML_OA_W, FCML_OP_MODRM_RM_OP_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_R64_RM64 }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_BLCMSK[] = {
	/* BLCMSK reg32, reg/mem32 8F RXB.09 0.dest.0.00 02 /1*/
    { FCML_AMT_TBM, 0x0450, 0x00D98800, { 0x09, 0x02, 0x00 }, { FCML_OP_VEX_VVVV_REG( FCML_REG_GPR, FCML_EOS_DWORD ) | FCML_OA_W, FCML_OP_MODRM_RM_OP_32, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_R32_RM32 },
	/* BLCMSK reg64, reg/mem64 8F RXB.09 1.dest.0.00 02 /1*/
    { FCML_AMT_TBM, 0x0448, 0x00D98800, { 0x09, 0x02, 0x00 }, { FCML_OP_VEX_VVVV_REG( FCML_REG_GPR, FCML_EOS_QWORD ) | FCML_OA_W, FCML_OP_MODRM_RM_OP_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_R64_RM64 }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_BLCS[] = {
	/* BLCS reg32, reg/mem32 8F RXB.09 0.dest.0.00 01 /3*/
    { FCML_AMT_TBM, 0x0450, 0x00D99800, { 0x09, 0x01, 0x00 }, { FCML_OP_VEX_VVVV_REG( FCML_REG_GPR, FCML_EOS_DWORD ) | FCML_OA_W, FCML_OP_MODRM_RM_OP_32, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_R32_RM32 },
	/* BLCS reg64, reg/mem64 8F RXB.09 1.dest.0.00 01 /3*/
    { FCML_AMT_TBM, 0x0448, 0x00D99800, { 0x09, 0x01, 0x00 }, { FCML_OP_VEX_VVVV_REG( FCML_REG_GPR, FCML_EOS_QWORD ) | FCML_OA_W, FCML_OP_MODRM_RM_OP_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_R64_RM64 }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_BLSFILL[] = {
	/* BLSFILL reg32, reg/mem32 8F RXB.09 0.dest.0.00 01 /2*/
    { FCML_AMT_TBM, 0x0450, 0x00D99000, { 0x09, 0x01, 0x00 }, { FCML_OP_VEX_VVVV_REG( FCML_REG_GPR, FCML_EOS_DWORD ) | FCML_OA_W, FCML_OP_MODRM_RM_OP_32, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_R32_RM32 },
	/* BLSFILL reg64, reg/mem64 8F RXB.09 1.dest.0.00 01 /2*/
    { FCML_AMT_TBM, 0x0448, 0x00D99000, { 0x09, 0x01, 0x00 }, { FCML_OP_VEX_VVVV_REG( FCML_REG_GPR, FCML_EOS_QWORD ) | FCML_OA_W, FCML_OP_MODRM_RM_OP_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_R64_RM64 }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_BLSI[] = {
	/* VEX.NDD.LZ.0F38.W0 F3 /3 BLSI r32, r/m32*/
    { FCML_AMT_BMI1 | FCML_AMT_VEXx, 0x02D0, 0x00ED9800, { 0x0F, 0x38, 0xF3 }, { FCML_OP_VEX_VVVV_REG( FCML_REG_GPR, FCML_EOS_DWORD ) | FCML_OA_W, FCML_OP_MODRM_RM_OP_32, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_R32_RM32 },
	/* VEX.NDD.LZ.0F38.W1 F3 /3 BLSI r64, r/m64*/
    { FCML_AMT_BMI1 | FCML_AMT_VEXx, 0x02C8, 0x00ED9800, { 0x0F, 0x38, 0xF3 }, { FCML_OP_VEX_VVVV_REG( FCML_REG_GPR, FCML_EOS_QWORD ) | FCML_OA_W, FCML_OP_MODRM_RM_OP_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_R64_RM64 }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_BLSIC[] = {
	/* BLSIC reg32, reg/mem32 8F RXB.09 0.dest.0.00 01 /6*/
    { FCML_AMT_TBM, 0x0450, 0x00D9B000, { 0x09, 0x01, 0x00 }, { FCML_OP_VEX_VVVV_REG( FCML_REG_GPR, FCML_EOS_DWORD ) | FCML_OA_W, FCML_OP_MODRM_RM_OP_32, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_R32_RM32 },
	/* BLSIC reg64, reg/mem64 8F RXB.09 1.dest.0.00 01 /6*/
    { FCML_AMT_TBM, 0x0448, 0x00D9B000, { 0x09, 0x01, 0x00 }, { FCML_OP_VEX_VVVV_REG( FCML_REG_GPR, FCML_EOS_QWORD ) | FCML_OA_W, FCML_OP_MODRM_RM_OP_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_R64_RM64 }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_BLSMSK[] = {
	/* VEX.NDD.LZ.0F38.W0 F3 /2 BLSMSK r32, r/m32*/
    { FCML_AMT_BMI1 | FCML_AMT_VEXx, 0x02D0, 0x00ED9000, { 0x0F, 0x38, 0xF3 }, { FCML_OP_VEX_VVVV_REG( FCML_REG_GPR, FCML_EOS_DWORD ) | FCML_OA_W, FCML_OP_MODRM_RM_OP_32, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_R32_RM32 },
	/* VEX.NDD.LZ.0F38.W1 F3 /2 BLSMSK r64, r/m64*/
    { FCML_AMT_BMI1 | FCML_AMT_VEXx, 0x02C8, 0x00ED9000, { 0x0F, 0x38, 0xF3 }, { FCML_OP_VEX_VVVV_REG( FCML_REG_GPR, FCML_EOS_QWORD ) | FCML_OA_W, FCML_OP_MODRM_RM_OP_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_R64_RM64 }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_BLSR[] = {
	/* VEX.NDD.LZ.0F38.W0 F3 /1 BLSR r32, r/m32*/
    { FCML_AMT_BMI1 | FCML_AMT_VEXx, 0x02D0, 0x00ED8800, { 0x0F, 0x38, 0xF3 }, { FCML_OP_VEX_VVVV_REG( FCML_REG_GPR, FCML_EOS_DWORD ) | FCML_OA_W, FCML_OP_MODRM_RM_OP_32, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_R32_RM32 },
	/* VEX.NDD.LZ.0F38.W1 F3 /1 BLSR r64, r/m64*/
    { FCML_AMT_BMI1 | FCML_AMT_VEXx, 0x02C8, 0x00ED8800, { 0x0F, 0x38, 0xF3 }, { FCML_OP_VEX_VVVV_REG( FCML_REG_GPR, FCML_EOS_QWORD ) | FCML_OA_W, FCML_OP_MODRM_RM_OP_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_R64_RM64 }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_BZHI[] = {
	/* VEX.NDS1.LZ.0F38.W0 F5 /r BZHI r32a, r/m32, r32b*/
    { FCML_AMT_BMI2 | FCML_AMT_VEXx, 0x02D0, 0x00EC8000, { 0x0F, 0x38, 0xF5 }, { FCML_OP_MODRM_R_32_W, FCML_OP_MODRM_RM_OP_32, FCML_OP_VEX_VVVV_REG( FCML_REG_GPR, FCML_EOS_DWORD ), FCML_NA, FCML_NA }, FCML_AM_R32_RM32_R32 },
	/* VEX.NDS1.LZ.0F38.W1 F5 /r BZHI r64a, r/m64, r64b*/
    { FCML_AMT_BMI2 | FCML_AMT_VEXx, 0x02C8, 0x00EC8000, { 0x0F, 0x38, 0xF5 }, { FCML_OP_MODRM_R_64_W, FCML_OP_MODRM_RM_OP_64, FCML_OP_VEX_VVVV_REG( FCML_REG_GPR, FCML_EOS_QWORD ), FCML_NA, FCML_NA }, FCML_AM_R64_RM64_R64 }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_LZCNT[] = {
	/* F3 0F BD /r LZCNT r16,r/m16*/
	/* F3 0F BD /r LZCNT r32,r/m32*/
	/* REX.W + F3 0F BD /r LZCNT r64,r/m64*/
    { FCML_AMT_ABM, 0x4000, 0x00D88000, { 0x0F, 0xBD, 0x00 }, { FCML_OP_MODRM_R_W, FCML_OP_MODRM_RM_OP, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_MULX[] = {
	/* VEX.NDD.LZ.F2.0F38.W0 F6 /r MULX r32a, r32b, r/m32*/
    { FCML_AMT_BMI2 | FCML_AMT_VEXx, 0x22D0, 0x00EC8000, { 0x0F, 0x38, 0xF6 }, { FCML_OP_MODRM_R_32_W, FCML_OP_VEX_VVVV_REG( FCML_REG_GPR, FCML_EOS_DWORD ), FCML_OP_MODRM_RM_OP_32, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.NDD.LZ.F2.0F38.W1 F6 /r MULX r64a, r64b, r/m64*/
    { FCML_AMT_BMI2 | FCML_AMT_VEXx, 0x22C8, 0x00EC8000, { 0x0F, 0x38, 0xF6 }, { FCML_OP_MODRM_R_64_W, FCML_OP_VEX_VVVV_REG( FCML_REG_GPR, FCML_EOS_QWORD ), FCML_OP_MODRM_RM_OP_64, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PDEP[] = {
	/* VEX.NDS.LZ.F2.0F38.W0 F5 /r PDEP r32a, r32b, r/m32*/
    { FCML_AMT_BMI2 | FCML_AMT_VEXx, 0x22D0, 0x00EC8000, { 0x0F, 0x38, 0xF5 }, { FCML_OP_MODRM_R_32_W, FCML_OP_VEX_VVVV_REG( FCML_REG_GPR, FCML_EOS_DWORD ), FCML_OP_MODRM_RM_OP_32, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.NDS.LZ.F2.0F38.W1 F5 /r PDEP r64a, r64b, r/m64*/
    { FCML_AMT_BMI2 | FCML_AMT_VEXx, 0x22C8, 0x00EC8000, { 0x0F, 0x38, 0xF5 }, { FCML_OP_MODRM_R_64_W, FCML_OP_VEX_VVVV_REG( FCML_REG_GPR, FCML_EOS_QWORD ), FCML_OP_MODRM_RM_OP_64, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_PEXT[] = {
	/* VEX.NDS.LZ.F3.0F38.W0 F5 /r PEXT r32a, r32b, r/m32*/
    { FCML_AMT_BMI2 | FCML_AMT_VEXx, 0x42D0, 0x00EC8000, { 0x0F, 0x38, 0xF5 }, { FCML_OP_MODRM_R_32_W, FCML_OP_VEX_VVVV_REG( FCML_REG_GPR, FCML_EOS_DWORD ), FCML_OP_MODRM_RM_OP_32, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.NDS.LZ.F3.0F38.W1 F5 /r PEXT r64a, r64b, r/m64*/
    { FCML_AMT_BMI2 | FCML_AMT_VEXx, 0x42C8, 0x00EC8000, { 0x0F, 0x38, 0xF5 }, { FCML_OP_MODRM_R_64_W, FCML_OP_VEX_VVVV_REG( FCML_REG_GPR, FCML_EOS_QWORD ), FCML_OP_MODRM_RM_OP_64, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_RORX[] = {
	/* VEX.LZ.F2.0F3A.W0 F0 /r ib RORX r32, r/m32, int8*/
    { FCML_AMT_BMI2 | FCML_AMT_VEXx, 0x22D0, 0x00EC8000, { 0x0F, 0x3A, 0xF0 }, { FCML_OP_MODRM_R_32_W, FCML_OP_MODRM_RM_OP_32, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.LZ.F2.0F3A.W1 F0 /r ib RORX r64, r/m64, int8*/
    { FCML_AMT_BMI2 | FCML_AMT_VEXx, 0x22C8, 0x00EC8000, { 0x0F, 0x3A, 0xF0 }, { FCML_OP_MODRM_R_64_W, FCML_OP_MODRM_RM_OP_64, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_SHLX[] = {
	/* VEX.NDS1.LZ.66.0F38.W0 F7 /r SHLX r32a, r/m32, r32b*/
    { FCML_AMT_GPI, 0x12D0, 0x00EC8000, { 0x0F, 0x38, 0xF7 }, { FCML_OP_MODRM_R_32_W, FCML_OP_MODRM_RM_OP_32, FCML_OP_VEX_VVVV_REG( FCML_REG_GPR, FCML_EOS_DWORD ), FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.NDS1.LZ.66.0F38.W1 F7 /r SHLX r64a, r/m64, r64b*/
    { FCML_AMT_GPI, 0x12C8, 0x00EC8000, { 0x0F, 0x38, 0xF7 }, { FCML_OP_MODRM_R_64_W, FCML_OP_MODRM_RM_OP_64, FCML_OP_VEX_VVVV_REG( FCML_REG_GPR, FCML_EOS_QWORD ), FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_SHRX[] = {
	/* VEX.NDS1.LZ.F2.0F38.W0 F7 /r SHRX r32a, r/m32, r32b*/
    { FCML_AMT_BMI2 | FCML_AMT_VEXx, 0x22D0, 0x00EC8000, { 0x0F, 0x38, 0xF7 }, { FCML_OP_MODRM_R_32_W, FCML_OP_MODRM_RM_OP_32, FCML_OP_VEX_VVVV_REG( FCML_REG_GPR, FCML_EOS_DWORD ), FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.NDS1.LZ.F2.0F38.W1 F7 /r SHRX r64a, r/m64, r64b*/
    { FCML_AMT_BMI2 | FCML_AMT_VEXx, 0x22C8, 0x00EC8000, { 0x0F, 0x38, 0xF7 }, { FCML_OP_MODRM_R_64_W, FCML_OP_MODRM_RM_OP_64, FCML_OP_VEX_VVVV_REG( FCML_REG_GPR, FCML_EOS_QWORD ), FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_SARX[] = {
	/* VEX.NDS1.LZ.F3.0F38.W0 F7 /r SARX r32a, r/m32, r32b*/
    { FCML_AMT_BMI2 | FCML_AMT_VEXx, 0x42D0, 0x00EC8000, { 0x0F, 0x38, 0xF7 }, { FCML_OP_MODRM_R_32_W, FCML_OP_MODRM_RM_OP_32, FCML_OP_VEX_VVVV_REG( FCML_REG_GPR, FCML_EOS_DWORD ), FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VEX.NDS1.LZ.F3.0F38.W1 F7 /r SARX r64a, r/m64, r64b*/
    { FCML_AMT_BMI2 | FCML_AMT_VEXx, 0x42C8, 0x00EC8000, { 0x0F, 0x38, 0xF7 }, { FCML_OP_MODRM_R_64_W, FCML_OP_MODRM_RM_OP_64, FCML_OP_VEX_VVVV_REG( FCML_REG_GPR, FCML_EOS_QWORD ), FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_TZCNT[] = {
	/* F3 0F BC /r TZCNT r16, r/m16*/
	/* F3 0F BC /r TZCNT r32, r/m32*/
	/* REX.W + F3 0F BC /r TZCNT r64, r/m64*/
    { FCML_AMT_BMI1, 0x4000, 0x00D88000, { 0x0F, 0xBC, 0x00 }, { FCML_OP_MODRM_R_W, FCML_OP_MODRM_RM_OP, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_TZMSK[] = {
	/* TZMSK reg32, reg/mem32 8F RXB.09 0.dest.0.00 01 /4*/
    { FCML_AMT_TBM, 0x0450, 0x00D9A000, { 0x09, 0x01, 0x00 }, { FCML_OP_VEX_VVVV_REG( FCML_REG_GPR, FCML_EOS_DWORD ) | FCML_OA_W, FCML_OP_MODRM_RM_OP_32, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* TZMSK reg64, reg/mem64 8F RXB.09 1.dest.0.00 01 /4*/
    { FCML_AMT_TBM, 0x0448, 0x00D9A000, { 0x09, 0x01, 0x00 }, { FCML_OP_VEX_VVVV_REG( FCML_REG_GPR, FCML_EOS_QWORD ) | FCML_OA_W, FCML_OP_MODRM_RM_OP_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

/* END OF VEX-GPR */

/* HLE */

/* TODO: Przyklaad instrukcji bez operandow ktora modyfikuje EAX, jako argument dlaczego wartosci R/W nie powinny byc uzywane.*/
struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_XABORT[] = {
	/* C6 F8 ib XABORT int8*/
    { FCML_AMT_RTM, 0x0000, 0x00D80000, { 0xC6, 0xF8, 0x00 }, { FCML_OP_IB, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_XBEGIN[] = {
	/* C7 F8 XBEGIN rel16*/
	/* C7 F8 XBEGIN rel32*/
    { FCML_AMT_RTM, 0x0000, 0x40D80000, { 0xC7, 0xF8, 0x00 }, { FCML_OP_IMMEDIATE_DIS_RELATIVE_EOSA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_XEND[] = {
	/* 0F 01 D5 XEND*/
    { FCML_AMT_RTM, 0x0000, 0x00EC0000, { 0x0F, 0x01, 0xD5 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_XTEST[] = {
	/* 0F 01 D6 XTEST*/
    { FCML_AMT_HLE | FCML_AMT_RTM, 0x0000, 0x00EC0000, { 0x0F, 0x01, 0xD6 }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

/* END OF HLE */

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_ADCX[] = {
	/* 66 0F 38 F6 /r ADCX r32, r/m32*/
	/* REX.W + 66 0F 38 F6 /r ADCX r64, r/m64*/
    { FCML_AMT_ADX, 0x1000, 0x00EC8000, { 0x0F, 0x38, 0xF6 }, { FCML_OP_MODRM_R_RW, FCML_OP_MODRM_RM, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_ADOX[] = {
	/* F3 0F 38 F6 /r ADOX r32, r/m32*/
	/* REX.w + F3 0F 38 F6 /r ADOX r64, r/m64*/
    { FCML_AMT_ADX, 0x4000, 0x00EC8000, { 0x0F, 0x38, 0xF6 }, { FCML_OP_MODRM_R_RW, FCML_OP_MODRM_RM_OP, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_RDSEED[] = {
	/* 0F C7 /7 RDSEED r16*/
	/* 0F C7 /7 RDSEED r32*/
	/* REX.W + 0F C7 /7 RDSEED r64*/
    { FCML_AMT_RDSEED, 0x0000, 0x00DBB800, { 0x0F, 0xC7, 0x00 }, { FCML_OP_RM( FCML_REG_GPR, FCML_EOS_EOSA, FCML_EOS_UNDEFINED, FCML_RMF_R ) | FCML_OA_W, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_CLAC[] = {
	/* 0F 01 CA CLAC*/
    { FCML_AMT_GPI, 0x0000, 0x00EC0000, { 0x0F, 0x01, 0xCA }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_STAC[] = {
	/* 0F 01 CB STAC*/
    { FCML_AMT_GPI, 0x0000, 0x00EC0000, { 0x0F, 0x01, 0xCB }, { FCML_NA, FCML_NA, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

/* XOP*/

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VFRCZPD[] = {
	/* VFRCZPD xmm1, xmm2/mem128 8F RXB.01001 0.1111.0.00 81 /r*/
	/* VFRCZPD ymm1, ymm2/mem256 8F RXB.01001 0.1111.1.00 81 /r*/
    { FCML_AMT_XOP, 0x0510, 0x00D88000, { 0x09, 0x81, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VFRCZPS[] = {
	/* VFRCZPS xmm1, xmm2/mem128 8F RXB.01001 0.1111.0.00 80 /r*/
	/* VFRCZPS ymm1, ymm2/mem256 8F RXB.01001 0.1111.1.00 80 /r*/
    { FCML_AMT_XOP, 0x0510, 0x00D88000, { 0x09, 0x80, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VFRCZSD[] = {
	/* VFRCZSD xmm1,xmm2/mem64 8F RXB.01001 0.1111.0.00 83 /r*/
    { FCML_AMT_XOP, 0x0550, 0x00D88000, { 0x09, 0x83, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_OP_64, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VFRCZSS[] = {
	/* VFRCZSS xmm1, xmm2/mem32 8F RXB.01001 0.1111.0.00 82 /r*/
    { FCML_AMT_XOP, 0x0550, 0x00D88000, { 0x09, 0x82, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_OP_32, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPCMOV[] = {
	/* VPCMOV xmm1, xmm2, xmm3/mem128, xmm4 8F RXB.01000 0.src.0.00 A2 /r ib*/
	/* VPCMOV ymm1, ymm2, ymm3/mem256, ymm4 8F RXB.01000 0.src.1.00 A2 /r ib*/
    { FCML_AMT_XOP, 0x0410, 0x00D88000, { 0x08, 0xA2, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_OP_OPERAND_IS4, FCML_NA }, FCML_AM_UNKNOWN },
	/* VPCMOV xmm1, xmm2, xmm3, xmm4/mem128 8F RXB.01000 1.src.0.00 A2 /r ib*/
	/* VPCMOV ymm1, ymm2, ymm3, ymm4/mem256 8F RXB.01000 1.src.1.00 A2 /r ib*/
    { FCML_AMT_XOP, 0x0408, 0x00D88000, { 0x08, 0xA2, 0x00 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_OPERAND_IS4, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPCOMB[] = {
	/* VPCOMB xmm1, xmm2, xmm3/mem128, int8 8F RXB.01000 0.src.0.00 CC /r ib*/
    { FCML_AMT_XOP, 0x0450, 0x00D88000, { 0x08, 0xCC, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_OP_PSEUDO_OP( 0x07 ), FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPCOMW[] = {
	/* VPCOMW xmm1, xmm2, xmm3/mem128, int8 8F RXB.01000 0.src.0.00 CD /r ib*/
    { FCML_AMT_XOP, 0x0450, 0x00D88000, { 0x08, 0xCD, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_OP_PSEUDO_OP( 0x07 ), FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPCOMD[] = {
	/* VPCOMD xmm1, xmm2, xmm3/mem128, int8 8F RXB.01000 0.src.0.00 CE /r ib*/
    { FCML_AMT_XOP, 0x0450, 0x00D88000, { 0x08, 0xCE, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_OP_PSEUDO_OP( 0x07 ), FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPCOMQ[] = {
	/* VPCOMQ xmm1, xmm2, xmm3/mem128, int8 8F RXB.01000 0.src.0.00 CF /r ib*/
    { FCML_AMT_XOP, 0x0450, 0x00D88000, { 0x08, 0xCF, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_OP_PSEUDO_OP( 0x07 ), FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPCOMUB[] = {
	/* VPCOMUB xmm1, xmm2, xmm3/mem128, int8 8F RXB.01000 0.src.0.00 EC /r ib*/
    { FCML_AMT_XOP, 0x0450, 0x00D88000, { 0x08, 0xEC, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_OP_PSEUDO_OP( 0x07 ), FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPCOMUW[] = {
	/* VPCOMUW xmm1, xmm2, xmm3/mem128, int8 8F RXB.01000 0.src.0.00 ED /r ib*/
    { FCML_AMT_XOP, 0x0450, 0x00D88000, { 0x08, 0xED, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_OP_PSEUDO_OP( 0x07 ), FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPCOMUD[] = {
	/* VPCOMUD xmm1, xmm2, xmm3/mem128, int8 8F RXB.01000 0.src.0.00 EE /r ib*/
    { FCML_AMT_XOP, 0x0450, 0x00D88000, { 0x08, 0xEE, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_OP_PSEUDO_OP( 0x07 ), FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPCOMUQ[] = {
	/* VPCOMUQ xmm1, xmm2, xmm3/mem128, int8 8F RXB.01000 0.src.0.00 EF /r ib*/
    { FCML_AMT_XOP, 0x0450, 0x00D88000, { 0x08, 0xEF, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_OP_PSEUDO_OP( 0x07 ), FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPERMIL2PD[] = {
	/* VPERMIL2PS xmm1, xmm2, xmm3/mem128, xmm4, m2z*/
	/* VPERMIL2PS ymm1, ymm2, ymm3/mem256, ymm4, m2z*/
    { FCML_AMT_XOP, 0x1090, 0x00EC8000, { 0x0F, 0x3A, 0x49 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_OP_OPERAND_IS5( FCML_ISF_IS5_SRC ), FCML_OP_OPERAND_IS5( FCML_ISF_IS5_M2Z ) }, FCML_AM_UNKNOWN },
	/* VPERMIL2PS xmm1, xmm2, xmm3, xmm4/mem128, m2z*/
	/* VPERMIL2PS ymm1, ymm2, ymm3, ymm4/mem256, m2z*/
    { FCML_AMT_XOP, 0x1088, 0x00EC8000, { 0x0F, 0x3A, 0x49 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_OPERAND_IS5( FCML_ISF_IS5_SRC ), FCML_OP_MODRM_RM_SIMD_L_OP, FCML_OP_OPERAND_IS5( FCML_ISF_IS5_M2Z ) }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPERMIL2PS[] = {
	/* VPERMIL2PS xmm1, xmm2, xmm3/mem128, xmm4, m2z*/
	/* VPERMIL2PS ymm1, ymm2, ymm3/mem256, ymm4, m2z*/
    { FCML_AMT_XOP, 0x1090, 0x00EC8000, { 0x0F, 0x3A, 0x48 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_MODRM_RM_SIMD_L_OP, FCML_OP_OPERAND_IS5( FCML_ISF_IS5_SRC ), FCML_OP_OPERAND_IS5( FCML_ISF_IS5_M2Z ) }, FCML_AM_UNKNOWN },
	/* VPERMIL2PS xmm1, xmm2, xmm3, xmm4/mem128, m2z*/
	/* VPERMIL2PS ymm1, ymm2, ymm3, ymm4/mem256, m2z*/
    { FCML_AMT_XOP, 0x1088, 0x00EC8000, { 0x0F, 0x3A, 0x48 }, { FCML_OP_MODRM_R_SIMD_L_W, FCML_OP_VEX_VVVV_SIMD_REG, FCML_OP_OPERAND_IS5( FCML_ISF_IS5_SRC ), FCML_OP_MODRM_RM_SIMD_L_OP, FCML_OP_OPERAND_IS5( FCML_ISF_IS5_M2Z ) }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPHADDBD[] = {
	/* VPHADDBD xmm1, xmm2/mem128 8F RXB.01001 0.1111.0.00 C2 /r*/
    { FCML_AMT_XOP, 0x0550, 0x00D88000, { 0x09, 0xC2, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPHADDBW[] = {
	/* VPHADDBW xmm1, xmm2/mem128 8F RXB.01001 0.1111.0.00 C1 /r*/
    { FCML_AMT_XOP, 0x0550, 0x00D88000, { 0x09, 0xC1, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPHADDBQ[] = {
	/* VPHADDBQ xmm1, xmm2/mem128 8F RXB.01001 0.1111.0.00 C3 /r*/
    { FCML_AMT_XOP, 0x0550, 0x00D88000, { 0x09, 0xC3, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPHADDDQ[] = {
	/* VPHADDDQ xmm1, xmm2/mem128 8F RXB.01001 0.1111.0.00 CB /r*/
    { FCML_AMT_XOP, 0x0550, 0x00D88000, { 0x09, 0xCB, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPHADDUBD[] = {
	/* VPHADDUBD xmm1, xmm2/mem128 8F RXB.01001 0.1111.0.00 D2 /r*/
    { FCML_AMT_XOP, 0x0550, 0x00D88000, { 0x09, 0xD2, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPHADDUBQ[] = {
	/* VPHADDUBQ xmm1, xmm2/mem128 8F RXB.01001 0.1111.0.00 D3 /r*/
    { FCML_AMT_XOP, 0x0550, 0x00D88000, { 0x09, 0xD3, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPHADDUBW[] = {
	/* VPHADDUBWD xmm1, xmm2/mem128 8F RXB.01001 0.1111.0.00 D1 /r*/
    { FCML_AMT_XOP, 0x0550, 0x00D88000, { 0x09, 0xD1, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPHADDUDQ[] = {
	/* VPHADDUDQ xmm1, xmm2/mem128 8F RXB.01001 0.1111.0.00 DB /r*/
    { FCML_AMT_XOP, 0x0550, 0x00D88000, { 0x09, 0xDB, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPHADDUWD[] = {
	/* VPHADDUWD xmm1, xmm2/mem128 8F RXB.01001 0.1111.0.00 D6 /r*/
    { FCML_AMT_XOP, 0x0550, 0x00D88000, { 0x09, 0xD6, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPHADDUWQ[] = {
	/* VPHADDUWQ xmm1, xmm2/mem128 8F RXB.01001 0.1111.0.00 D7 /r*/
    { FCML_AMT_XOP, 0x0550, 0x00D88000, { 0x09, 0xD7, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPHADDWD[] = {
	/* VPHADDWD xmm1, xmm2/mem128 8F RXB.01001 0.1111.0.00 C6 /r*/
    { FCML_AMT_XOP, 0x0550, 0x00D88000, { 0x09, 0xC6, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPHADDWQ[] = {
	/* VPHADDWQ xmm1, xmm2/mem128 8F RXB.01001 0.1111.0.00 C7 /r*/
    { FCML_AMT_XOP, 0x0550, 0x00D88000, { 0x09, 0xC7, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPHSUBBW[] = {
	/* VPHSUBBW xmm1, xmm2/mem128 8F RXB.01001 0.1111.0.00 E1 /r*/
    { FCML_AMT_XOP, 0x0550, 0x00D88000, { 0x09, 0xE1, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPHSUBDQ[] = {
	/* VPHSUBDQ xmm1, xmm2/mem128 8F RXB.01001 0.1111.0.00 E3 /r*/
    { FCML_AMT_XOP, 0x0550, 0x00D88000, { 0x09, 0xE3, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPHSUBWD[] = {
	/* VPHSUBWD xmm1, xmm2/mem128 8F RXB.01001 0.1111.0.00 E2 /r*/
    { FCML_AMT_XOP, 0x0550, 0x00D88000, { 0x09, 0xE2, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPMACSDD[] = {
	/* VPMACSDD xmm1, xmm2, xmm3/mem128, xmm4 8F RXB.01000 0.src.0.00 9E /r ib*/
    { FCML_AMT_XOP, 0x0450, 0x00D88000, { 0x08, 0x9E, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_OP_OPERAND_IS4, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPMACSDQH[] = {
	/* VPMACSDQH xmm1, xmm2, xmm3/mem128, xmm4 8F RXB.01000 0.src.0.00 9F /r ib*/
    { FCML_AMT_XOP, 0x0450, 0x00D88000, { 0x08, 0x9F, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_OP_OPERAND_IS4, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPMACSDQL[] = {
	/* VPMACSDQL xmm1, xmm2, xmm3/mem128, xmm4 8F RXB.01000 0.src.0.00 97 /r ib*/
    { FCML_AMT_XOP, 0x0450, 0x00D88000, { 0x08, 0x97, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_OP_OPERAND_IS4, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPMACSSDD[] = {
	/* VPMACSSDD xmm1, xmm2, xmm3/mem128, xmm4 8F RXB.01000 X.src.0.00 8E /r ib*/
    { FCML_AMT_XOP, 0x0450, 0x00D88000, { 0x08, 0x8E, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_OP_OPERAND_IS4, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPMACSSDQH[] = {
	/* VPMACSSDQH xmm1, xmm2, xmm3/mem128, xmm4 8F RXB.01000 0.src.0.00 8F /r ib*/
    { FCML_AMT_XOP, 0x0450, 0x00D88000, { 0x08, 0x8F, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_OP_OPERAND_IS4, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPMACSSDQL[] = {
	/* VPMACSSDQL xmm1, xmm2, xmm3/mem128, xmm4 8F RXB.01000 0.src.0.00 87 /r ib*/
    { FCML_AMT_XOP, 0x0450, 0x00D88000, { 0x08, 0x87, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_OP_OPERAND_IS4, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPMACSSWD[] = {
	/* VPMACSSWD xmm1, xmm2, xmm3/mem128, xmm4 8F RXB.01000 0.src.0.00 86 /r ib*/
    { FCML_AMT_XOP, 0x0450, 0x00D88000, { 0x08, 0x86, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_OP_OPERAND_IS4, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPMACSSWW[] = {
	/* VPMACSSWW xmm1, xmm2, xmm3/mem128, xmm4 8F RXB.01000 X.src.0.00 85 /r ib*/
    { FCML_AMT_XOP, 0x0450, 0x00D88000, { 0x08, 0x85, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_OP_OPERAND_IS4, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPMACSWD[] = {
	/* VPMACSWD xmm1, xmm2, xmm3/mem128, xmm4 8F RXB.01000 0.src.0.00 96 /r ib*/
    { FCML_AMT_XOP, 0x0450, 0x00D88000, { 0x08, 0x96, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_OP_OPERAND_IS4, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPMACSWW[] = {
	/* VPMACSWW xmm1, xmm2, xmm3/mem128, xmm4 8F RXB.01000 0.src.0.00 95 /r ib*/
    { FCML_AMT_XOP, 0x0450, 0x00D88000, { 0x08, 0x95, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_OP_OPERAND_IS4, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPMADCSSWD[] = {
	/* VPMADCSSWD xmm1, xmm2, xmm3/mem128, xmm4 8F RXB.01000 0.src.0.00 A6 /r ib*/
    { FCML_AMT_XOP, 0x0450, 0x00D88000, { 0x08, 0xA6, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_OP_OPERAND_IS4, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPMADCSWD[] = {
	/* VPMADCSWD xmm1, xmm2, xmm3/mem128, xmm4 8F RXB.01000 0.src.0.00 B6 /r ib*/
    { FCML_AMT_XOP, 0x0450, 0x00D88000, { 0x08, 0xB6, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_OP_OPERAND_IS4, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPPERM[] = {
	/* VPPERM xmm1, xmm2, xmm3/mem128, xmm4 8F RXB.01000 0.src.0.00 A3 /r ib*/
    { FCML_AMT_XOP, 0x0450, 0x00D88000, { 0x08, 0xA3, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_OP_OPERAND_IS4, FCML_NA }, FCML_AM_UNKNOWN },
	/* VPPERM xmm1, xmm2, xmm3, xmm4/mem128 8F RXB.01000 1.src.0.00 A3 /r ib*/
    { FCML_AMT_XOP, 0x0448, 0x00D88000, { 0x08, 0xA3, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_OPERAND_IS4, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPROTD[] = {
	/* VPROTD xmm1, xmm2/mem128, xmm3 8F RXB.01001 0.src.0.00 92 /r*/
    { FCML_AMT_XOP, 0x0450, 0x00D88000, { 0x09, 0x92, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_OP_128, FCML_OP_VEX_VVVV_XMM_REG, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VPROTD xmm1, xmm2, xmm3/mem128 8F RXB.01001 1.src.0.00 92 /r*/
    { FCML_AMT_XOP, 0x0448, 0x00D88000, { 0x09, 0x92, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VPROTD xmm1, xmm2/mem128, int8 8F RXB.01000 0.1111.0.00 C2 /r ib*/
    { FCML_AMT_XOP, 0x0550, 0x00D88000, { 0x08, 0xC2, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_OP_128, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPROTB[] = {
	/* VPROTB xmm1, xmm2/mem128, xmm3 8F RXB.01001 0.src.0.00 90 /r*/
    { FCML_AMT_XOP, 0x0450, 0x00D88000, { 0x09, 0x90, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_OP_128, FCML_OP_VEX_VVVV_XMM_REG, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VPROTB xmm1, xmm2, xmm3/mem128 8F RXB.01001 1.src.0.00 90 /r*/
    { FCML_AMT_XOP, 0x0448, 0x00D88000, { 0x09, 0x90, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VPROTB xmm1, xmm2/mem128, int8 8F RXB.01000 0.1111.0.00 C0 /r ib*/
    { FCML_AMT_XOP, 0x0550, 0x00D88000, { 0x08, 0xC0, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_OP_128, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPROTQ[] = {
	/* VPROTQ xmm1, xmm2/mem128, xmm3 8F RXB.01001 0.src.0.00 93 /r*/
    { FCML_AMT_XOP, 0x0450, 0x00D88000, { 0x09, 0x93, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_OP_128, FCML_OP_VEX_VVVV_XMM_REG, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VPROTQ xmm1, xmm2, xmm3/mem128 8F RXB.01001 1.src.0.00 93 /r*/
    { FCML_AMT_XOP, 0x0448, 0x00D88000, { 0x09, 0x93, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VPROTQ xmm1, xmm2/mem128, int8 8F RXB.01000 0.1111.0.00 C3 /r ib*/
    { FCML_AMT_XOP, 0x0550, 0x00D88000, { 0x08, 0xC3, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_OP_128, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPROTW[] = {
	/* VPROTW xmm1, xmm2/mem128, xmm3 8F RXB.01001 0.src.0.00 91 /r*/
    { FCML_AMT_XOP, 0x0450, 0x00D88000, { 0x09, 0x91, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_OP_128, FCML_OP_VEX_VVVV_XMM_REG, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VPROTW xmm1, xmm2, xmm3/mem128 8F RXB.01001 1.src.0.00 91 /r*/
    { FCML_AMT_XOP, 0x0448, 0x00D88000, { 0x09, 0x91, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VPROTW xmm1, xmm2/mem128, int8 8F RXB.01000 0.1111.0.00 C1 /r ib*/
    { FCML_AMT_XOP, 0x0550, 0x00D88000, { 0x08, 0xC1, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_OP_128, FCML_OP_IB, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPSHAB[] = {
	/* VPSHAB xmm1, xmm2/mem128, xmm3 8F RXB.01001 0.src.0.00 98 /r*/
    { FCML_AMT_XOP, 0x0450, 0x00D88000, { 0x09, 0x98, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_OP_128, FCML_OP_VEX_VVVV_XMM_REG, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VPSHAB xmm1, xmm2, xmm3/mem128 8F RXB.01001 1.src.0.00 98 /r*/
    { FCML_AMT_XOP, 0x0448, 0x00D88000, { 0x09, 0x98, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPSHAD[] = {
	/* VPSHAD xmm1, xmm2/mem128, xmm3 8F RXB.01001 0.src.0.00 9A /r*/
    { FCML_AMT_XOP, 0x0450, 0x00D88000, { 0x09, 0x9A, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_OP_128, FCML_OP_VEX_VVVV_XMM_REG, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VPSHAD xmm1, xmm2, xmm3/mem128 8F RXB.01001 1.src.0.00 9A /r*/
    { FCML_AMT_XOP, 0x0448, 0x00D88000, { 0x09, 0x9A, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPSHAQ[] = {
	/* VPSHAQ xmm1, xmm2/mem128, xmm3 8F RXB.01001 0.src.0.00 9B /r*/
    { FCML_AMT_XOP, 0x0450, 0x00D88000, { 0x09, 0x9B, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_OP_128, FCML_OP_VEX_VVVV_XMM_REG, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VPSHAQ xmm1, xmm2, xmm3/mem128 8F RXB.01001 1.src.0.00 9B /r*/
    { FCML_AMT_XOP, 0x0448, 0x00D88000, { 0x09, 0x9B, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPSHAW[] = {
	/* VPSHAW xmm1, xmm2/mem128, xmm3 8F RXB.01001 0.src.0.00 99 /r*/
    { FCML_AMT_XOP, 0x0450, 0x00D88000, { 0x09, 0x99, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_OP_128, FCML_OP_VEX_VVVV_XMM_REG, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VPSHAW xmm1, xmm2, xmm3/mem128 8F RXB.01001 1.src.0.00 99 /r*/
    { FCML_AMT_XOP, 0x0448, 0x00D88000, { 0x09, 0x99, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPSHLB[] = {
	/* VPSHLB xmm1, xmm2/mem128, xmm3 8F RXB.01001 0.src.0.00 94 /r*/
    { FCML_AMT_XOP, 0x0450, 0x00D88000, { 0x09, 0x94, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_OP_128, FCML_OP_VEX_VVVV_XMM_REG, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VPSHLB xmm1, xmm2, xmm3/mem128 8F RXB.01001 1.src.0.00 94 /r*/
    { FCML_AMT_XOP, 0x0448, 0x00D88000, { 0x09, 0x94, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPSHLD[] = {
	/* VPSHLD xmm1, xmm3/mem128, xmm2 8F RXB.01001 0.src.0.00 96 /r*/
    { FCML_AMT_XOP, 0x0450, 0x00D88000, { 0x09, 0x96, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_OP_128, FCML_OP_VEX_VVVV_XMM_REG, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VPSHLD xmm1, xmm2, xmm3/mem128 8F RXB.01001 1.src.0.00 96 /r*/
    { FCML_AMT_XOP, 0x0448, 0x00D88000, { 0x09, 0x96, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPSHLQ[] = {
	/* VPSHLQ xmm1, xmm3/mem128, xmm2 8F RXB.01001 0.src.0.00 97 /r*/
    { FCML_AMT_XOP, 0x0450, 0x00D88000, { 0x09, 0x97, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_OP_128, FCML_OP_VEX_VVVV_XMM_REG, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VPSHLQ xmm1, xmm2, xmm3/mem128 8F RXB.01001 1.src.0.00 97 /r*/
    { FCML_AMT_XOP, 0x0448, 0x00D88000, { 0x09, 0x97, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_addr_mode_desc fcml_st_def_addr_mode_desc_VPSHLW[] = {
	/* VPSHLW xmm1, xmm3/mem128, xmm2 8F RXB.01001 0.src.0.00 95 /r*/
    { FCML_AMT_XOP, 0x0450, 0x00D88000, { 0x09, 0x95, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_MODRM_RM_XMM_OP_128, FCML_OP_VEX_VVVV_XMM_REG, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN },
	/* VPSHLW xmm1, xmm2, xmm3/mem128 8F RXB.01001 1.src.0.00 95 /r*/
    { FCML_AMT_XOP, 0x0448, 0x00D88000, { 0x09, 0x95, 0x00 }, { FCML_OP_MODRM_R_XMM_W, FCML_OP_VEX_VVVV_XMM_REG, FCML_OP_MODRM_RM_XMM_OP_128, FCML_NA, FCML_NA }, FCML_AM_UNKNOWN }
};

struct fcml_st_def_instruction_desc fcml_ext_instructions_def[] = {
	FCML_IA_INSTRUCTION( F_AAA, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_AAA ),
	FCML_IA_INSTRUCTION( F_AAD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_AAD ),
	FCML_IA_INSTRUCTION( F_AAM, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_AAM ),
	FCML_IA_INSTRUCTION( F_AAS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_AAS ),
	FCML_IA_INSTRUCTION( F_ADC, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_ADC ),
	FCML_IA_INSTRUCTION( F_ADD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_ADD ),
	FCML_IA_INSTRUCTION( F_ADDPD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_ADDPD ),
	FCML_IA_INSTRUCTION( F_VADDPD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VADDPD ),
	FCML_IA_INSTRUCTION( F_ADDPS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_ADDPS ),
	FCML_IA_INSTRUCTION( F_VADDPS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VADDPS ),
	FCML_IA_INSTRUCTION( F_ADDSD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_ADDSD ),
	FCML_IA_INSTRUCTION( F_VADDSD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VADDSD ),
	FCML_IA_INSTRUCTION( F_ADDSS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_ADDSS ),
	FCML_IA_INSTRUCTION( F_VADDSS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VADDSS ),
	FCML_IA_INSTRUCTION( F_ADDSUBPD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_ADDSUBPD ),
	FCML_IA_INSTRUCTION( F_VADDSUBPD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VADDSUBPD ),
	FCML_IA_INSTRUCTION( F_ADDSUBPS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_ADDSUBPS ),
	FCML_IA_INSTRUCTION( F_VADDSUBPS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VADDSUBPS ),
	FCML_IA_INSTRUCTION( F_AESDEC, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_AESDEC ),
	FCML_IA_INSTRUCTION( F_VAESDEC, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VAESDEC ),
	FCML_IA_INSTRUCTION( F_AESDECLAST, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_AESDECLAST ),
	FCML_IA_INSTRUCTION( F_VAESDECLAST, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VAESDECLAST ),
	FCML_IA_INSTRUCTION( F_AESENC, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_AESENC ),
	FCML_IA_INSTRUCTION( F_VAESENC, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VAESENC ),
	FCML_IA_INSTRUCTION( F_AESENCLAST, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_AESENCLAST ),
	FCML_IA_INSTRUCTION( F_VAESENCLAST, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VAESENCLAST ),
	FCML_IA_INSTRUCTION( F_AESIMC, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_AESIMC ),
	FCML_IA_INSTRUCTION( F_VAESIMC, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VAESIMC ),
	FCML_IA_INSTRUCTION( F_AESKEYGENASSIST, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_AESKEYGENASSIST ),
	FCML_IA_INSTRUCTION( F_VAESKEYGENASSIST, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VAESKEYGENASSIST ),
	FCML_IA_INSTRUCTION( F_AND, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_AND ),
	FCML_IA_INSTRUCTION( F_ANDPD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_ANDPD ),
	FCML_IA_INSTRUCTION( F_VANDPD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VANDPD ),
	FCML_IA_INSTRUCTION( F_ANDPS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_ANDPS ),
	FCML_IA_INSTRUCTION( F_VANDPS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VANDPS ),
	FCML_IA_INSTRUCTION( F_ANDNPD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_ANDNPD ),
	FCML_IA_INSTRUCTION( F_VANDNPD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VANDNPD ),
	FCML_IA_INSTRUCTION( F_ANDNPS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_ANDNPS ),
	FCML_IA_INSTRUCTION( F_VANDNPS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VANDNPS ),
	FCML_IA_INSTRUCTION( F_ARPL, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_ARPL ),
	FCML_IA_INSTRUCTION( F_BLENDPD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_BLENDPD ),
	FCML_IA_INSTRUCTION( F_VBLENDPD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VBLENDPD ),
	FCML_IA_INSTRUCTION( F_BLENDPS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_BLENDPS ),
	FCML_IA_INSTRUCTION( F_VBLENDPS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VBLENDPS ),
	FCML_IA_INSTRUCTION( F_BLENDVPD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_BLENDVPD ),
	FCML_IA_INSTRUCTION( F_VBLENDVPD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VBLENDVPD ),
	FCML_IA_INSTRUCTION( F_BLENDVPS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_BLENDVPS ),
	FCML_IA_INSTRUCTION( F_VBLENDVPS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VBLENDVPS ),
	FCML_IA_INSTRUCTION( F_BOUND, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_BOUND ),
	FCML_IA_INSTRUCTION( F_BSF, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_BSF ),
	FCML_IA_INSTRUCTION( F_BSR, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_BSR ),
	FCML_IA_INSTRUCTION( F_BSWAP, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_BSWAP ),
	FCML_IA_INSTRUCTION( F_BT, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_BT ),
	FCML_IA_INSTRUCTION( F_BTC, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_BTC ),
	FCML_IA_INSTRUCTION( F_BTR, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_BTR ),
	FCML_IA_INSTRUCTION( F_BTS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_BTS ),
	FCML_IA_INSTRUCTION( F_CALL, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_CALL ),
	FCML_IA_INSTRUCTION( F_CBW, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_CBW ),
	FCML_IA_INSTRUCTION( F_CLC, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_CLC ),
	FCML_IA_INSTRUCTION( F_CLD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_CLD ),
	FCML_IA_INSTRUCTION( F_CLFLUSH, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_CLFLUSH ),
	FCML_IA_INSTRUCTION( F_CLI, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_CLI ),
	FCML_IA_INSTRUCTION( F_CLGI, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_CLGI ),
	FCML_IA_INSTRUCTION( F_CLTS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_CLTS ),
	FCML_IA_INSTRUCTION( F_CMC, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_CMC ),
	FCML_IA_INSTRUCTION( F_CMOV, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_CMOV ),
	FCML_IA_INSTRUCTION( F_CMP, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_CMP ),
	FCML_IA_INSTRUCTION( F_CMPPD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_CMPPD ),
	FCML_IA_INSTRUCTION( F_VCMPPD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VCMPPD ),
	FCML_IA_INSTRUCTION( F_CMPPS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_CMPPS ),
	FCML_IA_INSTRUCTION( F_VCMPPS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VCMPPS ),
	FCML_IA_INSTRUCTION( F_CMPS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_CMPS ),
	FCML_IA_INSTRUCTION( F_CMPSD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_CMPSD ),
	FCML_IA_INSTRUCTION( F_VCMPSD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VCMPSD ),
	FCML_IA_INSTRUCTION( F_CMPSS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_CMPSS ),
	FCML_IA_INSTRUCTION( F_VCMPSS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VCMPSS ),
	FCML_IA_INSTRUCTION( F_CMPXCHG, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_CMPXCHG ),
	FCML_IA_INSTRUCTION( F_CMPXCHGxB, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_CMPXCHGXB ),
	FCML_IA_INSTRUCTION( F_COMISD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_COMISD ),
	FCML_IA_INSTRUCTION( F_VCOMISD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VCOMISD ),
	FCML_IA_INSTRUCTION( F_COMISS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_COMISS ),
	FCML_IA_INSTRUCTION( F_VCOMISS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VCOMISS ),
	FCML_IA_INSTRUCTION( F_CPUID, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_CPUID ),
	FCML_IA_INSTRUCTION( F_CRC32, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_CRC32 ),
	FCML_IA_INSTRUCTION( F_CVTDQ2PD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_CVTDQ2PD ),
	FCML_IA_INSTRUCTION( F_VCVTDQ2PD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VCVTDQ2PD ),
	FCML_IA_INSTRUCTION( F_CVTDQ2PS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_CVTDQ2PS ),
	FCML_IA_INSTRUCTION( F_VCVTDQ2PS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VCVTDQ2PS ),
	FCML_IA_INSTRUCTION( F_CVTPD2DQ, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_CVTPD2DQ ),
	FCML_IA_INSTRUCTION( F_VCVTPD2DQ, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VCVTPD2DQ ),
	FCML_IA_INSTRUCTION( F_CVTPD2PI, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_CVTPD2PI ),
	FCML_IA_INSTRUCTION( F_CVTPD2PS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_CVTPD2PS ),
	FCML_IA_INSTRUCTION( F_VCVTPD2PS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VCVTPD2PS ),
	FCML_IA_INSTRUCTION( F_CVTPI2PD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_CVTPI2PD ),
	FCML_IA_INSTRUCTION( F_CVTPI2PS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_CVTPI2PS ),
	FCML_IA_INSTRUCTION( F_CVTPS2DQ, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_CVTPS2DQ ),
	FCML_IA_INSTRUCTION( F_VCVTPS2DQ, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VCVTPS2DQ ),
	FCML_IA_INSTRUCTION( F_CVTPS2PD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_CVTPS2PD ),
	FCML_IA_INSTRUCTION( F_VCVTPS2PD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VCVTPS2PD ),
	FCML_IA_INSTRUCTION( F_CVTPS2PI, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_CVTPS2PI ),
	FCML_IA_INSTRUCTION( F_CVTSD2SI, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_CVTSD2SI ),
	FCML_IA_INSTRUCTION( F_VCVTSD2SI, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VCVTSD2SI ),
	FCML_IA_INSTRUCTION( F_CVTSD2SS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_CVTSD2SS ),
	FCML_IA_INSTRUCTION( F_VCVTSD2SS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VCVTSD2SS ),
	FCML_IA_INSTRUCTION( F_CVTSI2SD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_CVTSI2SD ),
	FCML_IA_INSTRUCTION( F_VCVTSI2SD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VCVTSI2SD ),
	FCML_IA_INSTRUCTION( F_CVTSI2SS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_CVTSI2SS ),
	FCML_IA_INSTRUCTION( F_VCVTSI2SS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VCVTSI2SS ),
	FCML_IA_INSTRUCTION( F_CVTSS2SD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_CVTSS2SD ),
	FCML_IA_INSTRUCTION( F_VCVTSS2SD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VCVTSS2SD ),
	FCML_IA_INSTRUCTION( F_CVTSS2SI, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_CVTSS2SI ),
	FCML_IA_INSTRUCTION( F_VCVTSS2SI, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VCVTSS2SI ),
	FCML_IA_INSTRUCTION( F_CVTTPD2DQ, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_CVTTPD2DQ ),
	FCML_IA_INSTRUCTION( F_VCVTTPD2DQ, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VCVTTPD2DQ ),
	FCML_IA_INSTRUCTION( F_CVTTPD2PI, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_CVTTPD2PI ),
	FCML_IA_INSTRUCTION( F_CVTTPS2DQ, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_CVTTPS2DQ ),
	FCML_IA_INSTRUCTION( F_VCVTTPS2DQ, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VCVTTPS2DQ ),
	FCML_IA_INSTRUCTION( F_CVTTPS2PI, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_CVTTPS2PI ),
	FCML_IA_INSTRUCTION( F_CVTTSD2SI, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_CVTTSD2SI ),
	FCML_IA_INSTRUCTION( F_VCVTTSD2SI, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VCVTTSD2SI ),
	FCML_IA_INSTRUCTION( F_CVTTSS2SI, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_CVTTSS2SI ),
	FCML_IA_INSTRUCTION( F_VCVTTSS2SI, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VCVTTSS2SI ),
	FCML_IA_INSTRUCTION( F_CWD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_CWD_CDQ_CQO ),
	FCML_IA_INSTRUCTION( F_DAA, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_DAA ),
	FCML_IA_INSTRUCTION( F_DAS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_DAS ),
	FCML_IA_INSTRUCTION( F_DEC, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_DEC ),
	FCML_IA_INSTRUCTION( F_DIV, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_DIV ),
	FCML_IA_INSTRUCTION( F_DIVPD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_DIVPD ),
	FCML_IA_INSTRUCTION( F_VDIVPD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VDIVPD ),
	FCML_IA_INSTRUCTION( F_DIVPS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_DIVPS ),
	FCML_IA_INSTRUCTION( F_VDIVPS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VDIVPS ),
	FCML_IA_INSTRUCTION( F_DIVSD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_DIVSD ),
	FCML_IA_INSTRUCTION( F_VDIVSD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VDIVSD ),
	FCML_IA_INSTRUCTION( F_DIVSS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_DIVSS ),
	FCML_IA_INSTRUCTION( F_VDIVSS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VDIVSS ),
	FCML_IA_INSTRUCTION( F_DPPD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_DPPD ),
	FCML_IA_INSTRUCTION( F_VDPPD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VDPPD ),
	FCML_IA_INSTRUCTION( F_DPPS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_DPPS ),
	FCML_IA_INSTRUCTION( F_VDPPS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VDPPS ),
	FCML_IA_INSTRUCTION( F_EMMS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_EMMS ),
	FCML_IA_INSTRUCTION( F_ENTER, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_ENTER ),
	FCML_IA_INSTRUCTION( F_EXTRACTPS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_EXTRACTPS ),
	FCML_IA_INSTRUCTION( F_VEXTRACTPS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VEXTRACTPS ),
	FCML_IA_INSTRUCTION( F_EXTRQ, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_EXTRQ ),
	FCML_IA_INSTRUCTION( F_F2XM1, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_F2XM1 ),
	FCML_IA_INSTRUCTION( F_FABS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_FABS ),
	FCML_IA_INSTRUCTION( F_FADD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_FADD ),
	FCML_IA_INSTRUCTION( F_FIADD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_FIADD ),
	FCML_IA_INSTRUCTION( F_FADDP, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_FADDP ),
	FCML_IA_INSTRUCTION( F_FBLD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_FBLD ),
	FCML_IA_INSTRUCTION( F_FBSTP, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_FBSTP ),
	FCML_IA_INSTRUCTION( F_FCHS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_FCHS ),
	FCML_IA_INSTRUCTION( F_FCLEX, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_FCLEX ),
	FCML_IA_INSTRUCTION( F_FNCLEX, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_FNCLEX ),
	FCML_IA_INSTRUCTION( F_FCMOVB, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_FCMOVB ),
	FCML_IA_INSTRUCTION( F_FCMOVE, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_FCMOVE ),
	FCML_IA_INSTRUCTION( F_FCMOVBE, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_FCMOVBE ),
	FCML_IA_INSTRUCTION( F_FCMOVU, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_FCMOVU ),
	FCML_IA_INSTRUCTION( F_FCMOVNB, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_FCMOVNB ),
	FCML_IA_INSTRUCTION( F_FCMOVNE, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_FCMOVNE ),
	FCML_IA_INSTRUCTION( F_FCMOVNBE, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_FCMOVNBE ),
	FCML_IA_INSTRUCTION( F_FCMOVNU, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_FCMOVNU ),
	FCML_IA_INSTRUCTION( F_FCOM, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_FCOM ),
	FCML_IA_INSTRUCTION( F_FCOMP, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_FCOMP ),
	FCML_IA_INSTRUCTION( F_FCOMPP, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_FCOMPP ),
	FCML_IA_INSTRUCTION( F_FCOMI, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_FCOMI ),
	FCML_IA_INSTRUCTION( F_FCOMIP, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_FCOMIP ),
	FCML_IA_INSTRUCTION( F_FUCOMI, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_FUCOMI ),
	FCML_IA_INSTRUCTION( F_FUCOMIP, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_FUCOMIP ),
	FCML_IA_INSTRUCTION( F_FCOS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_FCOS ),
	FCML_IA_INSTRUCTION( F_FDECSTP, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_FDECSTP ),
	FCML_IA_INSTRUCTION( F_FDIV, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_FDIV ),
	FCML_IA_INSTRUCTION( F_FDIVP, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_FDIVP ),
	FCML_IA_INSTRUCTION( F_FIDIV, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_FIDIV ),
	FCML_IA_INSTRUCTION( F_FDIVR, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_FDIVR ),
	FCML_IA_INSTRUCTION( F_FDIVRP, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_FDIVRP ),
	FCML_IA_INSTRUCTION( F_FIDIVR, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_FIDIVR ),
	FCML_IA_INSTRUCTION( F_FFREE, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_FFREE ),
	FCML_IA_INSTRUCTION( F_FICOM, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_FICOM ),
	FCML_IA_INSTRUCTION( F_FICOMP, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_FICOMP ),
	FCML_IA_INSTRUCTION( F_FILD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_FILD ),
	FCML_IA_INSTRUCTION( F_FINCSTP, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_FINCSTP ),
	FCML_IA_INSTRUCTION( F_FINIT, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_FINIT ),
	FCML_IA_INSTRUCTION( F_FNINIT, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_FNINIT ),
	FCML_IA_INSTRUCTION( F_FIST, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_FIST ),
	FCML_IA_INSTRUCTION( F_FISTP, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_FISTP ),
	FCML_IA_INSTRUCTION( F_FISTTP, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_FISTTP ),
	FCML_IA_INSTRUCTION( F_FLD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_FLD ),
	FCML_IA_INSTRUCTION( F_FLD1, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_FLD1 ),
	FCML_IA_INSTRUCTION( F_FLDL2T, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_FLDL2T ),
	FCML_IA_INSTRUCTION( F_FLDL2E, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_FLDL2E ),
	FCML_IA_INSTRUCTION( F_FLDPI, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_FLDPI ),
	FCML_IA_INSTRUCTION( F_FLDLG2, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_FLDLG2 ),
	FCML_IA_INSTRUCTION( F_FLDLN2, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_FLDLN2 ),
	FCML_IA_INSTRUCTION( F_FLDZ, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_FLDZ ),
	FCML_IA_INSTRUCTION( F_FLDCW, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_FLDCW ),
	FCML_IA_INSTRUCTION( F_FLDENV, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_FLDENV ),
	FCML_IA_INSTRUCTION( F_FMUL, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_FMUL ),
	FCML_IA_INSTRUCTION( F_FMULP, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_FMULP ),
	FCML_IA_INSTRUCTION( F_FIMUL, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_FIMUL ),
	FCML_IA_INSTRUCTION( F_FNOP, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_FNOP ),
	FCML_IA_INSTRUCTION( F_FPATAN, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_FPATAN ),
	FCML_IA_INSTRUCTION( F_FPREM, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_FPREM ),
	FCML_IA_INSTRUCTION( F_FPREM1, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_FPREM1 ),
	FCML_IA_INSTRUCTION( F_FPTAN, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_FPTAN ),
	FCML_IA_INSTRUCTION( F_FRNDINT, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_FRNDINT ),
	FCML_IA_INSTRUCTION( F_FRSTOR, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_FRSTOR ),
	FCML_IA_INSTRUCTION( F_FSAVE, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_FSAVE ),
	FCML_IA_INSTRUCTION( F_FNSAVE, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_FNSAVE ),
	FCML_IA_INSTRUCTION( F_FSCALE, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_FSCALE ),
	FCML_IA_INSTRUCTION( F_FSIN, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_FSIN ),
	FCML_IA_INSTRUCTION( F_FSINCOS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_FSINCOS ),
	FCML_IA_INSTRUCTION( F_FSQRT, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_FSQRT ),
	FCML_IA_INSTRUCTION( F_FST, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_FST ),
	FCML_IA_INSTRUCTION( F_FSTP, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_FSTP ),
	FCML_IA_INSTRUCTION( F_FSTCW, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_FSTCW ),
	FCML_IA_INSTRUCTION( F_FNSTCW, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_FNSTCW ),
	FCML_IA_INSTRUCTION( F_FSTENV, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_FSTENV ),
	FCML_IA_INSTRUCTION( F_FNSTENV, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_FNSTENV ),
	FCML_IA_INSTRUCTION( F_FSTSW, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_FSTSW ),
	FCML_IA_INSTRUCTION( F_FNSTSW, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_FNSTSW ),
	FCML_IA_INSTRUCTION( F_FSUB, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_FSUB ),
	FCML_IA_INSTRUCTION( F_FSUBP, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_FSUBP ),
	FCML_IA_INSTRUCTION( F_FISUB, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_FISUB ),
	FCML_IA_INSTRUCTION( F_FSUBR, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_FSUBR ),
	FCML_IA_INSTRUCTION( F_FSUBRP, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_FSUBRP ),
	FCML_IA_INSTRUCTION( F_FISUBR, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_FISUBR ),
	FCML_IA_INSTRUCTION( F_FTST, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_FTST ),
	FCML_IA_INSTRUCTION( F_FUCOM, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_FUCOM ),
	FCML_IA_INSTRUCTION( F_FUCOMP, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_FUCOMP ),
	FCML_IA_INSTRUCTION( F_FUCOMPP, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_FUCOMPP ),
	FCML_IA_INSTRUCTION( F_FXAM, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_FXAM ),
	FCML_IA_INSTRUCTION( F_FXCH, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_FXCH ),
	FCML_IA_INSTRUCTION( F_FXRSTOR, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_FXRSTOR ),
	FCML_IA_INSTRUCTION( F_FXRSTOR64, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_FXRSTOR64 ),
	FCML_IA_INSTRUCTION( F_FXSAVE, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_FXSAVE ),
	FCML_IA_INSTRUCTION( F_FXSAVE64, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_FXSAVE64 ),
	FCML_IA_INSTRUCTION( F_FXTRACT, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_FXTRACT ),
	FCML_IA_INSTRUCTION( F_FYL2X, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_FYL2X ),
	FCML_IA_INSTRUCTION( F_FYL2XP1, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_FYL2XP1 ),
	FCML_IA_INSTRUCTION( F_GETSEC, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_GETSEC ),
	FCML_IA_INSTRUCTION( F_HADDPD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_HADDPD ),
	FCML_IA_INSTRUCTION( F_VHADDPD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VHADDPD ),
	FCML_IA_INSTRUCTION( F_HADDPS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_HADDPS ),
	FCML_IA_INSTRUCTION( F_VHADDPS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VHADDPS ),
	FCML_IA_INSTRUCTION( F_HLT, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_HLT ),
	FCML_IA_INSTRUCTION( F_HSUBPD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_HSUBPD ),
	FCML_IA_INSTRUCTION( F_VHSUBPD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VHSUBPD ),
	FCML_IA_INSTRUCTION( F_HSUBPS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_HSUBPS ),
	FCML_IA_INSTRUCTION( F_VHSUBPS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VHSUBPS ),
	FCML_IA_INSTRUCTION( F_INVEPT, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_INVEPT ),
	FCML_IA_INSTRUCTION( F_INVVPID, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_INVVPID ),
	FCML_IA_INSTRUCTION( F_IDIV, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_IDIV ),
	FCML_IA_INSTRUCTION( F_IMUL, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_IMUL ),
	FCML_IA_INSTRUCTION( F_IN, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_IN ),
	FCML_IA_INSTRUCTION( F_INC, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_INC ),
	FCML_IA_INSTRUCTION( F_INS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_INS ),
	FCML_IA_INSTRUCTION( F_INSERTPS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_INSERTPS ),
	FCML_IA_INSTRUCTION( F_VINSERTPS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VINSERTPS ),
	FCML_IA_INSTRUCTION( F_INSERTQ, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_INSERTQ ),
	FCML_IA_INSTRUCTION( F_VINSERTF128, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VINSERTF128 ),
	FCML_IA_INSTRUCTION( F_INT3, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_INT3 ),
	FCML_IA_INSTRUCTION( F_INT, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_INT ),
	FCML_IA_INSTRUCTION( F_INTO, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_INTO ),
	FCML_IA_INSTRUCTION( F_INVD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_INVD ),
	FCML_IA_INSTRUCTION( F_INVLPG, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_INVLPG ),
	FCML_IA_INSTRUCTION( F_INVLPGA, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_INVLPGA ),
	FCML_IA_INSTRUCTION( F_INVPCID, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_INVPCID ),
	FCML_IA_INSTRUCTION( F_IRET, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_IRET ),
	FCML_IA_INSTRUCTION( F_JCXZ, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_JCXZ ),
	FCML_IA_INSTRUCTION( F_JCC, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_JCC ),
	FCML_IA_INSTRUCTION( F_JMP, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_JMP ),
	FCML_IA_INSTRUCTION( F_LAHF, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_LAHF ),
	FCML_IA_INSTRUCTION( F_LAR, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_LAR ),
	FCML_IA_INSTRUCTION( F_LDDQU, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_LDDQU ),
	FCML_IA_INSTRUCTION( F_VLDDQU, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VLDDQU ),
	FCML_IA_INSTRUCTION( F_LDMXCSR, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_LDMXCSR ),
	FCML_IA_INSTRUCTION( F_VLDMXCSR, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VLDMXCSR ),
	FCML_IA_INSTRUCTION( F_LDS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_LDS ),
	FCML_IA_INSTRUCTION( F_LSS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_LSS ),
	FCML_IA_INSTRUCTION( F_LES, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_LES ),
	FCML_IA_INSTRUCTION( F_LFS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_LFS ),
	FCML_IA_INSTRUCTION( F_LGS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_LGS ),
	FCML_IA_INSTRUCTION( F_LEA, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_LEA ),
	FCML_IA_INSTRUCTION( F_LEAVE, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_LEAVE ),
	FCML_IA_INSTRUCTION( F_LFENCE, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_LFENCE ),
	FCML_IA_INSTRUCTION( F_LLWPCB, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_LLWPCB ),
	FCML_IA_INSTRUCTION( F_LGDT, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_LGDT ),
	FCML_IA_INSTRUCTION( F_LIDT, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_LIDT ),
	FCML_IA_INSTRUCTION( F_LLDT, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_LLDT ),
	FCML_IA_INSTRUCTION( F_LMSW, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_LMSW ),
	FCML_IA_INSTRUCTION( F_LODS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_LODS ),
	FCML_IA_INSTRUCTION( F_LOOP, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_LOOP ),
	FCML_IA_INSTRUCTION( F_LOOPE, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_LOOPE ),
	FCML_IA_INSTRUCTION( F_LOOPNE, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_LOOPNE ),
	FCML_IA_INSTRUCTION( F_LWPINS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_LWPINS ),
	FCML_IA_INSTRUCTION( F_LWPVAL, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_LWPVAL ),
	FCML_IA_INSTRUCTION( F_LSL, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_LSL ),
	FCML_IA_INSTRUCTION( F_LTR, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_LTR ),
	FCML_IA_INSTRUCTION( F_MASKMOVDQU, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_MASKMOVDQU ),
	FCML_IA_INSTRUCTION( F_VMASKMOVDQU, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VMASKMOVDQU ),
	FCML_IA_INSTRUCTION( F_VMASKMOVPS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VMASKMOVPS ),
	FCML_IA_INSTRUCTION( F_VMASKMOVPD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VMASKMOVPD ),
	FCML_IA_INSTRUCTION( F_VPMASKMOVD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPMASKMOVD ),
	FCML_IA_INSTRUCTION( F_VPMASKMOVQ, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPMASKMOVQ ),
	FCML_IA_INSTRUCTION( F_MASKMOVQ, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_MASKMOVQ ),
	FCML_IA_INSTRUCTION( F_MAXPD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_MAXPD ),
	FCML_IA_INSTRUCTION( F_VMAXPD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VMAXPD ),
	FCML_IA_INSTRUCTION( F_MAXPS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_MAXPS ),
	FCML_IA_INSTRUCTION( F_VMAXPS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VMAXPS ),
	FCML_IA_INSTRUCTION( F_MAXSD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_MAXSD ),
	FCML_IA_INSTRUCTION( F_VMAXSD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VMAXSD ),
	FCML_IA_INSTRUCTION( F_MAXSS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_MAXSS ),
	FCML_IA_INSTRUCTION( F_VMAXSS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VMAXSS ),
	FCML_IA_INSTRUCTION( F_MFENCE, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_MFENCE ),
	FCML_IA_INSTRUCTION( F_MINPD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_MINPD ),
	FCML_IA_INSTRUCTION( F_VMINPD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VMINPD ),
	FCML_IA_INSTRUCTION( F_MINPS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_MINPS ),
	FCML_IA_INSTRUCTION( F_VMINPS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VMINPS ),
	FCML_IA_INSTRUCTION( F_MINSD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_MINSD ),
	FCML_IA_INSTRUCTION( F_VMINSD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VMINSD ),
	FCML_IA_INSTRUCTION( F_MINSS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_MINSS ),
	FCML_IA_INSTRUCTION( F_VMINSS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VMINSS ),
	FCML_IA_INSTRUCTION( F_MONITOR, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_MONITOR ),
	FCML_IA_INSTRUCTION( F_MOVAPD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_MOVAPD ),
	FCML_IA_INSTRUCTION( F_VMOVAPD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VMOVAPD ),
	FCML_IA_INSTRUCTION( F_MOVAPS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_MOVAPS ),
	FCML_IA_INSTRUCTION( F_VMOVAPS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VMOVAPS ),
	FCML_IA_INSTRUCTION( F_MOVBE, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_MOVBE ),
	FCML_IA_INSTRUCTION( F_MOV, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_MOV ),
	FCML_IA_INSTRUCTION( F_MOVD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_MOVD ),
	FCML_IA_INSTRUCTION( F_VMOVD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VMOVD ),
	FCML_IA_INSTRUCTION( F_MOVQ, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_MOVQ ),
	FCML_IA_INSTRUCTION( F_VMOVQ, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VMOVQ ),
	FCML_IA_INSTRUCTION( F_MOVDDUP, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_MOVDDUP ),
	FCML_IA_INSTRUCTION( F_VMOVDDUP, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VMOVDDUP ),
	FCML_IA_INSTRUCTION( F_MOVDQA, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_MOVDQA ),
	FCML_IA_INSTRUCTION( F_VMOVDQA, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VMOVDQA ),
	FCML_IA_INSTRUCTION( F_MOVDQU, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_MOVDQU ),
	FCML_IA_INSTRUCTION( F_VMOVDQU, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VMOVDQU ),
	FCML_IA_INSTRUCTION( F_MOVDQ2Q, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_MOVDQ2Q ),
	FCML_IA_INSTRUCTION( F_MOVHLPS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_MOVHLPS ),
	FCML_IA_INSTRUCTION( F_VMOVHLPS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VMOVHLPS ),
	FCML_IA_INSTRUCTION( F_MOVHPD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_MOVHPD ),
	FCML_IA_INSTRUCTION( F_VMOVHPD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VMOVHPD ),
	FCML_IA_INSTRUCTION( F_MOVHPS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_MOVHPS ),
	FCML_IA_INSTRUCTION( F_VMOVHPS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VMOVHPS ),
	FCML_IA_INSTRUCTION( F_MOVLHPS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_MOVLHPS ),
	FCML_IA_INSTRUCTION( F_VMOVLHPS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VMOVLHPS ),
	FCML_IA_INSTRUCTION( F_MOVLPD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_MOVLPD ),
	FCML_IA_INSTRUCTION( F_VMOVLPD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VMOVLPD ),
	FCML_IA_INSTRUCTION( F_MOVLPS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_MOVLPS ),
	FCML_IA_INSTRUCTION( F_VMOVLPS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VMOVLPS ),
	FCML_IA_INSTRUCTION( F_MOVMSKPD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_MOVMSKPD ),
	FCML_IA_INSTRUCTION( F_VMOVMSKPD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VMOVMSKPD ),
	FCML_IA_INSTRUCTION( F_MOVMSKPS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_MOVMSKPS ),
	FCML_IA_INSTRUCTION( F_VMOVMSKPS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VMOVMSKPS ),
	FCML_IA_INSTRUCTION( F_MOVNTDQA, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_MOVNTDQA ),
	FCML_IA_INSTRUCTION( F_VMOVNTDQA, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VMOVNTDQA ),
	FCML_IA_INSTRUCTION( F_MOVNTDQ, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_MOVNTDQ ),
	FCML_IA_INSTRUCTION( F_VMOVNTDQ, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VMOVNTDQ ),
	FCML_IA_INSTRUCTION( F_MOVNTI, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_MOVNTI ),
	FCML_IA_INSTRUCTION( F_MOVNTPD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_MOVNTPD ),
	FCML_IA_INSTRUCTION( F_VMOVNTPD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VMOVNTPD ),
	FCML_IA_INSTRUCTION( F_MOVNTPS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_MOVNTPS ),
	FCML_IA_INSTRUCTION( F_VMOVNTPS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VMOVNTPS ),
	FCML_IA_INSTRUCTION( F_MOVNTSD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_MOVNTSD ),
	FCML_IA_INSTRUCTION( F_MOVNTSS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_MOVNTSS ),
	FCML_IA_INSTRUCTION( F_MOVNTQ, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_MOVNTQ ),
	FCML_IA_INSTRUCTION( F_MOVQ, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_MOVQ ),
	FCML_IA_INSTRUCTION( F_MOVQ2DQ, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_MOVQ2DQ ),
	FCML_IA_INSTRUCTION( F_MOVS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_MOVS ),
	FCML_IA_INSTRUCTION( F_MOVSD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_MOVSD ),
	FCML_IA_INSTRUCTION( F_VMOVSD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VMOVSD ),
	FCML_IA_INSTRUCTION( F_MOVSHDUP, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_MOVSHDUP ),
	FCML_IA_INSTRUCTION( F_VMOVSHDUP, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VMOVSHDUP ),
	FCML_IA_INSTRUCTION( F_MOVSLDUP, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_MOVSLDUP ),
	FCML_IA_INSTRUCTION( F_VMOVSLDUP, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VMOVSLDUP ),
	FCML_IA_INSTRUCTION( F_MOVSS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_MOVSS ),
	FCML_IA_INSTRUCTION( F_VMOVSS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VMOVSS ),
	FCML_IA_INSTRUCTION( F_MOVSX, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_MOVSX ),
	FCML_IA_INSTRUCTION( F_MOVSXD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_MOVSXD ),
	FCML_IA_INSTRUCTION( F_MOVUPD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_MOVUPD ),
	FCML_IA_INSTRUCTION( F_VMOVUPD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VMOVUPD ),
	FCML_IA_INSTRUCTION( F_MOVUPS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_MOVUPS ),
	FCML_IA_INSTRUCTION( F_VMOVUPS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VMOVUPS ),
	FCML_IA_INSTRUCTION( F_MOVZX, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_MOVZX ),
	FCML_IA_INSTRUCTION( F_MPSADBW, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_MPSADBW ),
	FCML_IA_INSTRUCTION( F_VMPSADBW, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VMPSADBW ),
	FCML_IA_INSTRUCTION( F_MUL, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_MUL ),
	FCML_IA_INSTRUCTION( F_MULPD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_MULPD ),
	FCML_IA_INSTRUCTION( F_VMULPD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VMULPD ),
	FCML_IA_INSTRUCTION( F_MULPS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_MULPS ),
	FCML_IA_INSTRUCTION( F_VMULPS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VMULPS ),
	FCML_IA_INSTRUCTION( F_MULSD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_MULSD ),
	FCML_IA_INSTRUCTION( F_VMULSD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VMULSD ),
	FCML_IA_INSTRUCTION( F_MULSS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_MULSS ),
	FCML_IA_INSTRUCTION( F_VMULSS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VMULSS ),
	FCML_IA_INSTRUCTION( F_MWAIT, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_MWAIT ),
	FCML_IA_INSTRUCTION( F_NEG, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_NEG ),
	FCML_IA_INSTRUCTION( F_NOP, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_NOP ),
	FCML_IA_INSTRUCTION( F_NOT, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_NOT ),
	FCML_IA_INSTRUCTION( F_OR, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_OR ),
	FCML_IA_INSTRUCTION( F_ORPD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_ORPD ),
	FCML_IA_INSTRUCTION( F_VORPD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VORPD ),
	FCML_IA_INSTRUCTION( F_ORPS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_ORPS ),
	FCML_IA_INSTRUCTION( F_VORPS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VORPS ),
	FCML_IA_INSTRUCTION( F_OUT, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_OUT ),
	FCML_IA_INSTRUCTION( F_OUTS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_OUTS ),
	FCML_IA_INSTRUCTION( F_PABSW, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PABSW),
	FCML_IA_INSTRUCTION( F_PABSB, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PABSB),
	FCML_IA_INSTRUCTION( F_PABSD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PABSD),
	FCML_IA_INSTRUCTION( F_VPABSB, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPABSB),
	FCML_IA_INSTRUCTION( F_VPABSW, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPABSW),
	FCML_IA_INSTRUCTION( F_VPABSD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPABSD),
	FCML_IA_INSTRUCTION( F_VPACKSSWB, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPACKSSWB),
	FCML_IA_INSTRUCTION( F_PACKSSWB, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PACKSSWB),
	FCML_IA_INSTRUCTION( F_VPACKSSDW, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPACKSSDW),
	FCML_IA_INSTRUCTION( F_PACKSSDW, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PACKSSDW),
	FCML_IA_INSTRUCTION( F_PACKUSDW, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PACKUSDW),
	FCML_IA_INSTRUCTION( F_VPACKUSDW, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPACKUSDW),
	FCML_IA_INSTRUCTION( F_PACKUSWB, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PACKUSWB),
	FCML_IA_INSTRUCTION( F_VPACKUSWB, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPACKUSWB),
	FCML_IA_INSTRUCTION( F_VPADDW, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPADDW),
	FCML_IA_INSTRUCTION( F_VPADDQ, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPADDQ),
	FCML_IA_INSTRUCTION( F_PADDW, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PADDW),
	FCML_IA_INSTRUCTION( F_VPADDB, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPADDB),
	FCML_IA_INSTRUCTION( F_VPADDD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPADDD),
	FCML_IA_INSTRUCTION( F_PADDB, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PADDB),
	FCML_IA_INSTRUCTION( F_PADDD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PADDD),
	FCML_IA_INSTRUCTION( F_VPADDSW, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPADDSW),
	FCML_IA_INSTRUCTION( F_PADDSB, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PADDSB),
	FCML_IA_INSTRUCTION( F_PADDSW, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PADDSW),
	FCML_IA_INSTRUCTION( F_VPADDSB, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPADDSB),
	FCML_IA_INSTRUCTION( F_PADDUSW, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PADDUSW),
	FCML_IA_INSTRUCTION( F_PADDUSB, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PADDUSB),
	FCML_IA_INSTRUCTION( F_VPADDUSW, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPADDUSW),
	FCML_IA_INSTRUCTION( F_VPADDUSB, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPADDUSB),
	FCML_IA_INSTRUCTION( F_PADDQ, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PADDQ),
	FCML_IA_INSTRUCTION( F_VPADDQ, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPADDQ),
	FCML_IA_INSTRUCTION( F_PALIGNR, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PALIGNR),
	FCML_IA_INSTRUCTION( F_VPALIGNR, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPALIGNR),
	FCML_IA_INSTRUCTION( F_PAND, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PAND),
	FCML_IA_INSTRUCTION( F_VPAND, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPAND),
	FCML_IA_INSTRUCTION( F_PANDN, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PANDN),
	FCML_IA_INSTRUCTION( F_VPANDN, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPANDN),
	FCML_IA_INSTRUCTION( F_PAUSE, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PAUSE),
	FCML_IA_INSTRUCTION( F_PAVGW, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PAVGW),
	FCML_IA_INSTRUCTION( F_PAVGB, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PAVGB),
	FCML_IA_INSTRUCTION( F_VPAVGW, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPAVGW),
	FCML_IA_INSTRUCTION( F_VPAVGB, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPAVGB),
	FCML_IA_INSTRUCTION( F_PBLENDVB, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PBLENDVB),
	FCML_IA_INSTRUCTION( F_VPBLENDVB, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPBLENDVB),
	FCML_IA_INSTRUCTION( F_PBLENDW, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PBLENDW),
	FCML_IA_INSTRUCTION( F_VPBLENDW, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPBLENDW),
	FCML_IA_INSTRUCTION( F_VPBLENDD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPBLENDD),
	FCML_IA_INSTRUCTION( F_PCLMULQDQ, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PCLMULQDQ),
	FCML_IA_INSTRUCTION( F_VPCLMULQDQ, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPCLMULQDQ),
	FCML_IA_INSTRUCTION( F_PCMPEQW, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PCMPEQW),
	FCML_IA_INSTRUCTION( F_PCMPEQB, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PCMPEQB),
	FCML_IA_INSTRUCTION( F_PCMPEQD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PCMPEQD),
	FCML_IA_INSTRUCTION( F_VPCMPEQD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPCMPEQD),
	FCML_IA_INSTRUCTION( F_VPCMPEQW, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPCMPEQW),
	FCML_IA_INSTRUCTION( F_VPCMPEQB, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPCMPEQB),
	FCML_IA_INSTRUCTION( F_PCMPEQQ, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PCMPEQQ),
	FCML_IA_INSTRUCTION( F_VPCMPEQQ, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPCMPEQQ),
	FCML_IA_INSTRUCTION( F_PCMPESTRI, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PCMPESTRI),
	FCML_IA_INSTRUCTION( F_VPCMPESTRI, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPCMPESTRI),
	FCML_IA_INSTRUCTION( F_PCMPESTRM, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PCMPESTRM),
	FCML_IA_INSTRUCTION( F_VPCMPESTRM, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPCMPESTRM),
	FCML_IA_INSTRUCTION( F_PCMPGTW, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PCMPGTW),
	FCML_IA_INSTRUCTION( F_PCMPGTD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PCMPGTD),
	FCML_IA_INSTRUCTION( F_PCMPGTB, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PCMPGTB),
	FCML_IA_INSTRUCTION( F_VPCMPGTW, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPCMPGTW),
	FCML_IA_INSTRUCTION( F_VPCMPGTD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPCMPGTD),
	FCML_IA_INSTRUCTION( F_VPCMPGTB, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPCMPGTB),
	FCML_IA_INSTRUCTION( F_PCMPGTQ, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PCMPGTQ),
	FCML_IA_INSTRUCTION( F_VPCMPGTQ, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPCMPGTQ),
	FCML_IA_INSTRUCTION( F_PCMPISTRI, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PCMPISTRI),
	FCML_IA_INSTRUCTION( F_VPCMPISTRI, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPCMPISTRI),
	FCML_IA_INSTRUCTION( F_PCMPISTRM, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PCMPISTRM),
	FCML_IA_INSTRUCTION( F_VPCMPISTRM, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPCMPISTRM),
	FCML_IA_INSTRUCTION( F_VPEXTRB, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPEXTRB),
	FCML_IA_INSTRUCTION( F_VPEXTRQ, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPEXTRQ),
	FCML_IA_INSTRUCTION( F_PEXTRQ, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PEXTRQ),
	FCML_IA_INSTRUCTION( F_PEXTRB, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PEXTRB),
	FCML_IA_INSTRUCTION( F_PEXTRD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PEXTRD),
	FCML_IA_INSTRUCTION( F_VPEXTRD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPEXTRD),
	FCML_IA_INSTRUCTION( F_PEXTRW, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PEXTRW),
	FCML_IA_INSTRUCTION( F_VPEXTRW, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPEXTRW),
	FCML_IA_INSTRUCTION( F_VPHADDW, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPHADDW),
	FCML_IA_INSTRUCTION( F_VPHADDD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPHADDD),
	FCML_IA_INSTRUCTION( F_PHADDD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PHADDD),
	FCML_IA_INSTRUCTION( F_PHADDW, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PHADDW),
	FCML_IA_INSTRUCTION( F_PHADDSW, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PHADDSW),
	FCML_IA_INSTRUCTION( F_VPHADDSW, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPHADDSW),
	FCML_IA_INSTRUCTION( F_PHMINPOSUW, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PHMINPOSUW),
	FCML_IA_INSTRUCTION( F_VPHMINPOSUW, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPHMINPOSUW),
	FCML_IA_INSTRUCTION( F_PHSUBD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PHSUBD),
	FCML_IA_INSTRUCTION( F_PHSUBW, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PHSUBW),
	FCML_IA_INSTRUCTION( F_VPHSUBD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPHSUBD),
	FCML_IA_INSTRUCTION( F_VPHSUBW, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPHSUBW),
	FCML_IA_INSTRUCTION( F_PHSUBSW, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PHSUBSW),
	FCML_IA_INSTRUCTION( F_VPHSUBSW, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPHSUBSW),
	FCML_IA_INSTRUCTION( F_PINSRD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PINSRD),
	FCML_IA_INSTRUCTION( F_VPINSRQ, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPINSRQ),
	FCML_IA_INSTRUCTION( F_PINSRQ, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PINSRQ),
	FCML_IA_INSTRUCTION( F_PINSRB, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PINSRB),
	FCML_IA_INSTRUCTION( F_VPINSRD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPINSRD),
	FCML_IA_INSTRUCTION( F_VPINSRB, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPINSRB),
	FCML_IA_INSTRUCTION( F_PINSRW, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PINSRW),
	FCML_IA_INSTRUCTION( F_VPINSRW, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPINSRW),
	FCML_IA_INSTRUCTION( F_PMADDUBSW, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PMADDUBSW),
	FCML_IA_INSTRUCTION( F_VPMADDUBSW, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPMADDUBSW),
	FCML_IA_INSTRUCTION( F_PMADDWD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PMADDWD),
	FCML_IA_INSTRUCTION( F_VPMADDWD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPMADDWD),
	FCML_IA_INSTRUCTION( F_PMAXSB, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PMAXSB),
	FCML_IA_INSTRUCTION( F_VPMAXSB, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPMAXSB),
	FCML_IA_INSTRUCTION( F_PMAXSD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PMAXSD),
	FCML_IA_INSTRUCTION( F_VPMAXSD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPMAXSD),
	FCML_IA_INSTRUCTION( F_PMAXSW, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PMAXSW),
	FCML_IA_INSTRUCTION( F_VPMAXSW, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPMAXSW),
	FCML_IA_INSTRUCTION( F_PMAXUB, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PMAXUB),
	FCML_IA_INSTRUCTION( F_VPMAXUB, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPMAXUB),
	FCML_IA_INSTRUCTION( F_PMAXUD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PMAXUD),
	FCML_IA_INSTRUCTION( F_VPMAXUD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPMAXUD),
	FCML_IA_INSTRUCTION( F_PMAXUW, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PMAXUW),
	FCML_IA_INSTRUCTION( F_VPMAXUW, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPMAXUW),
	FCML_IA_INSTRUCTION( F_PMINSB, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PMINSB),
	FCML_IA_INSTRUCTION( F_VPMINSB, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPMINSB),
	FCML_IA_INSTRUCTION( F_PMINSD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PMINSD),
	FCML_IA_INSTRUCTION( F_VPMINSD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPMINSD),
	FCML_IA_INSTRUCTION( F_PMINSW, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PMINSW),
	FCML_IA_INSTRUCTION( F_VPMINSW, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPMINSW),
	FCML_IA_INSTRUCTION( F_PMINUW, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PMINUW),
	FCML_IA_INSTRUCTION( F_VPMINUW, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPMINUW),
	FCML_IA_INSTRUCTION( F_PMINUB, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PMINUB),
	FCML_IA_INSTRUCTION( F_VPMINUB, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPMINUB),
	FCML_IA_INSTRUCTION( F_PMINUD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PMINUD),
	FCML_IA_INSTRUCTION( F_VPMINUD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPMINUD),
	FCML_IA_INSTRUCTION( F_PMOVMSKB, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PMOVMSKB),
	FCML_IA_INSTRUCTION( F_VPMOVMSKB, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPMOVMSKB),
	FCML_IA_INSTRUCTION( F_VPMOVSXBQ, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPMOVSXBQ),
	FCML_IA_INSTRUCTION( F_PMOVSXBW, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PMOVSXBW),
	FCML_IA_INSTRUCTION( F_PMOVSXWQ, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PMOVSXWQ),
	FCML_IA_INSTRUCTION( F_VPMOVSXWQ, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPMOVSXWQ),
	FCML_IA_INSTRUCTION( F_PMOVSXWD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PMOVSXWD),
	FCML_IA_INSTRUCTION( F_PMOVSXBD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PMOVSXBD),
	FCML_IA_INSTRUCTION( F_VPMOVSXDQ, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPMOVSXDQ),
	FCML_IA_INSTRUCTION( F_VPMOVSXWD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPMOVSXWD),
	FCML_IA_INSTRUCTION( F_PMOVSXBQ, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PMOVSXBQ),
	FCML_IA_INSTRUCTION( F_VPMOVSXBW, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPMOVSXBW),
	FCML_IA_INSTRUCTION( F_PMOVSXDQ, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PMOVSXDQ),
	FCML_IA_INSTRUCTION( F_VPMOVSXBD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPMOVSXBD),
	FCML_IA_INSTRUCTION( F_PMOVZXWD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PMOVZXWD),
	FCML_IA_INSTRUCTION( F_PMOVZXDQ, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PMOVZXDQ),
	FCML_IA_INSTRUCTION( F_VPMOVZXDQ, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPMOVZXDQ),
	FCML_IA_INSTRUCTION( F_PMOVZXWQ, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PMOVZXWQ),
	FCML_IA_INSTRUCTION( F_VPMOVZXBQ, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPMOVZXBQ),
	FCML_IA_INSTRUCTION( F_PMOVZXBQ, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PMOVZXBQ),
	FCML_IA_INSTRUCTION( F_VPMOVZXWD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPMOVZXWD),
	FCML_IA_INSTRUCTION( F_VPMOVZXBD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPMOVZXBD),
	FCML_IA_INSTRUCTION( F_VPMOVZXWQ, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPMOVZXWQ),
	FCML_IA_INSTRUCTION( F_PMOVZXBD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PMOVZXBD),
	FCML_IA_INSTRUCTION( F_VPMOVZXBW, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPMOVZXBW),
	FCML_IA_INSTRUCTION( F_PMOVZXBW, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PMOVZXBW),
	FCML_IA_INSTRUCTION( F_PMULDQ, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PMULDQ),
	FCML_IA_INSTRUCTION( F_PMULHRSW, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PMULHRSW),
	FCML_IA_INSTRUCTION( F_PMULHUW, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PMULHUW),
	FCML_IA_INSTRUCTION( F_VPMULDQ, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPMULDQ),
	FCML_IA_INSTRUCTION( F_VPMULHRSW, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPMULHRSW),
	FCML_IA_INSTRUCTION( F_VPMULHUW, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPMULHUW),
	FCML_IA_INSTRUCTION( F_PMULHW, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PMULHW),
	FCML_IA_INSTRUCTION( F_VPMULHW, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPMULHW),
	FCML_IA_INSTRUCTION( F_PMULUDQ, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PMULUDQ),
	FCML_IA_INSTRUCTION( F_VPMULUDQ, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPMULUDQ),
	FCML_IA_INSTRUCTION( F_PMULLW, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PMULLW),
	FCML_IA_INSTRUCTION( F_PMULLD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PMULLD),
	FCML_IA_INSTRUCTION( F_VPMULLD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPMULLD),
	FCML_IA_INSTRUCTION( F_VPMULLW, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPMULLW),
	FCML_IA_INSTRUCTION( F_POP, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_POP),
	FCML_IA_INSTRUCTION( F_POPA, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_POPA),
	FCML_IA_INSTRUCTION( F_POPAD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_POPAD),
	FCML_IA_INSTRUCTION( F_POPF, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_POPF),
	FCML_IA_INSTRUCTION( F_POPFQ, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_POPFQ),
	FCML_IA_INSTRUCTION( F_POPFD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_POPFD),
	FCML_IA_INSTRUCTION( F_POPCNT, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_POPCNT),
	FCML_IA_INSTRUCTION( F_POR, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_POR),
	FCML_IA_INSTRUCTION( F_VPOR, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPOR),
	FCML_IA_INSTRUCTION( F_PREFETCHT2, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PREFETCHT2),
	FCML_IA_INSTRUCTION( F_PREFETCHW, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PREFETCHW),
	FCML_IA_INSTRUCTION( F_PREFETCHT1, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PREFETCHT1),
	FCML_IA_INSTRUCTION( F_PREFETCHNTA, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PREFETCHNTA),
	FCML_IA_INSTRUCTION( F_PREFETCHT0, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PREFETCHT0),
	FCML_IA_INSTRUCTION( F_PSADBW, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PSADBW),
	FCML_IA_INSTRUCTION( F_VPSADBW, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPSADBW),
	FCML_IA_INSTRUCTION( F_PSHUFB, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PSHUFB),
	FCML_IA_INSTRUCTION( F_PSHUFD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PSHUFD),
	FCML_IA_INSTRUCTION( F_PSHUFHW, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PSHUFHW),
	FCML_IA_INSTRUCTION( F_VPSHUFD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPSHUFD),
	FCML_IA_INSTRUCTION( F_VPSHUFB, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPSHUFB),
	FCML_IA_INSTRUCTION( F_PSHUFLW, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PSHUFLW),
	FCML_IA_INSTRUCTION( F_PSHUFW, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PSHUFW),
	FCML_IA_INSTRUCTION( F_VPSHUFLW, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPSHUFLW),
	FCML_IA_INSTRUCTION( F_VPSHUFHW, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPSHUFHW),
	FCML_IA_INSTRUCTION( F_VPSIGNB, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPSIGNB),
	FCML_IA_INSTRUCTION( F_VPSIGND, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPSIGND),
	FCML_IA_INSTRUCTION( F_PSIGNW, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PSIGNW),
	FCML_IA_INSTRUCTION( F_PSIGNB, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PSIGNB),
	FCML_IA_INSTRUCTION( F_VPSIGNW, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPSIGNW),
	FCML_IA_INSTRUCTION( F_PSIGND, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PSIGND),
	FCML_IA_INSTRUCTION( F_PSLLDQ, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PSLLDQ),
	FCML_IA_INSTRUCTION( F_VPSLLDQ, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPSLLDQ),
	FCML_IA_INSTRUCTION( F_PSLLQ, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PSLLQ),
	FCML_IA_INSTRUCTION( F_PSLLD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PSLLD),
	FCML_IA_INSTRUCTION( F_VPSLLW, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPSLLW),
	FCML_IA_INSTRUCTION( F_VPSLLQ, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPSLLQ),
	FCML_IA_INSTRUCTION( F_PSLLW, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PSLLW),
	FCML_IA_INSTRUCTION( F_VPSLLD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPSLLD),
	FCML_IA_INSTRUCTION( F_VPSRAW, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPSRAW),
	FCML_IA_INSTRUCTION( F_PSRAD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PSRAD),
	FCML_IA_INSTRUCTION( F_PSRAW, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PSRAW),
	FCML_IA_INSTRUCTION( F_VPSRAD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPSRAD),
	FCML_IA_INSTRUCTION( F_PSRLDQ, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PSRLDQ),
	FCML_IA_INSTRUCTION( F_VPSRLDQ, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPSRLDQ),
	FCML_IA_INSTRUCTION( F_VPSRLQ, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPSRLQ),
	FCML_IA_INSTRUCTION( F_PSRLQ, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PSRLQ),
	FCML_IA_INSTRUCTION( F_PSRLD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PSRLD),
	FCML_IA_INSTRUCTION( F_PSRLW, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PSRLW),
	FCML_IA_INSTRUCTION( F_VPSRLD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPSRLD),
	FCML_IA_INSTRUCTION( F_VPSRLW, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPSRLW),
	FCML_IA_INSTRUCTION( F_VPSUBD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPSUBD),
	FCML_IA_INSTRUCTION( F_PSUBD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PSUBD),
	FCML_IA_INSTRUCTION( F_PSUBW, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PSUBW),
	FCML_IA_INSTRUCTION( F_VPSUBB, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPSUBB),
	FCML_IA_INSTRUCTION( F_VPSUBQ, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPSUBQ),
	FCML_IA_INSTRUCTION( F_PSUBB, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PSUBB),
	FCML_IA_INSTRUCTION( F_VPSUBW, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPSUBW),
	FCML_IA_INSTRUCTION( F_PSUBQ, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PSUBQ),
	FCML_IA_INSTRUCTION( F_PSUBSB, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PSUBSB),
	FCML_IA_INSTRUCTION( F_VPSUBSW, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPSUBSW),
	FCML_IA_INSTRUCTION( F_VPSUBSB, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPSUBSB),
	FCML_IA_INSTRUCTION( F_PSUBSW, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PSUBSW),
	FCML_IA_INSTRUCTION( F_VPSUBUSW, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPSUBUSW),
	FCML_IA_INSTRUCTION( F_VPSUBUSB, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPSUBUSB),
	FCML_IA_INSTRUCTION( F_PSUBUSB, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PSUBUSB),
	FCML_IA_INSTRUCTION( F_PSUBUSW, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PSUBUSW),
	FCML_IA_INSTRUCTION( F_VPTEST, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPTEST),
	FCML_IA_INSTRUCTION( F_PTEST, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PTEST),
	FCML_IA_INSTRUCTION( F_PUNPCKLBW, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PUNPCKLBW),
	FCML_IA_INSTRUCTION( F_PUNPCKLQDQ, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PUNPCKLQDQ),
	FCML_IA_INSTRUCTION( F_VPUNPCKLWD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPUNPCKLWD),
	FCML_IA_INSTRUCTION( F_VPUNPCKLQDQ, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPUNPCKLQDQ),
	FCML_IA_INSTRUCTION( F_VPUNPCKLBW, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPUNPCKLBW),
	FCML_IA_INSTRUCTION( F_PUNPCKLWD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PUNPCKLWD),
	FCML_IA_INSTRUCTION( F_PUNPCKLDQ, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PUNPCKLDQ),
	FCML_IA_INSTRUCTION( F_VPUNPCKLDQ, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPUNPCKLDQ),
	FCML_IA_INSTRUCTION( F_VPUNPCKHWD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPUNPCKHWD),
	FCML_IA_INSTRUCTION( F_PUNPCKHDQ, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PUNPCKHDQ),
	FCML_IA_INSTRUCTION( F_PUNPCKHWD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PUNPCKHWD),
	FCML_IA_INSTRUCTION( F_PUNPCKHQDQ, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PUNPCKHQDQ),
	FCML_IA_INSTRUCTION( F_VPUNPCKHQDQ, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPUNPCKHQDQ),
	FCML_IA_INSTRUCTION( F_VPUNPCKHBW, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPUNPCKHBW),
	FCML_IA_INSTRUCTION( F_PUNPCKHBW, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PUNPCKHBW),
	FCML_IA_INSTRUCTION( F_VPUNPCKHDQ, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPUNPCKHDQ),
	FCML_IA_INSTRUCTION( F_PUSH, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PUSH),
	FCML_IA_INSTRUCTION( F_PUSHA, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PUSHA),
	FCML_IA_INSTRUCTION( F_PUSHF, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PUSHF),
	FCML_IA_INSTRUCTION( F_PUSHAD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PUSHAD),
	FCML_IA_INSTRUCTION( F_PUSHFQ, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PUSHFQ),
	FCML_IA_INSTRUCTION( F_PUSHFD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PUSHFD),
	FCML_IA_INSTRUCTION( F_PXOR, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PXOR),
	FCML_IA_INSTRUCTION( F_VPXOR, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPXOR),
	FCML_IA_INSTRUCTION( F_RCL, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_RCL),
	FCML_IA_INSTRUCTION( F_RCR, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_RCR),
	FCML_IA_INSTRUCTION( F_ROL, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_ROL),
	FCML_IA_INSTRUCTION( F_ROR, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_ROR),
	FCML_IA_INSTRUCTION( F_RCPPS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_RCPPS),
	FCML_IA_INSTRUCTION( F_VRCPPS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VRCPPS),
	FCML_IA_INSTRUCTION( F_RCPSS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_RCPSS),
	FCML_IA_INSTRUCTION( F_VRCPSS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VRCPSS),
	FCML_IA_INSTRUCTION( F_RDFSBASE, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_RDFSBASE),
	FCML_IA_INSTRUCTION( F_RDGSBASE, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_RDGSBASE),
	FCML_IA_INSTRUCTION( F_RDRAND, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_RDRAND),
	FCML_IA_INSTRUCTION( F_RDTSCP, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_RDTSCP),
	FCML_IA_INSTRUCTION( F_RDTSC, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_RDTSC),
	FCML_IA_INSTRUCTION( F_RDPMC, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_RDPMC),
	FCML_IA_INSTRUCTION( F_RDMSR, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_RDMSR),
	FCML_IA_INSTRUCTION( F_RET, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_RET),
	FCML_IA_INSTRUCTION( F_RETF, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_RETF),
	FCML_IA_INSTRUCTION( F_ROUNDPD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_ROUNDPD),
	FCML_IA_INSTRUCTION( F_VROUNDPD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VROUNDPD),
	FCML_IA_INSTRUCTION( F_ROUNDPS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_ROUNDPS),
	FCML_IA_INSTRUCTION( F_VROUNDPS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VROUNDPS),
	FCML_IA_INSTRUCTION( F_ROUNDSD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_ROUNDSD),
	FCML_IA_INSTRUCTION( F_VROUNDSD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VROUNDSD),
	FCML_IA_INSTRUCTION( F_ROUNDSS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_ROUNDSS),
	FCML_IA_INSTRUCTION( F_VROUNDSS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VROUNDSS),
	FCML_IA_INSTRUCTION( F_RSM, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_RSM),
	FCML_IA_INSTRUCTION( F_RSQRTPS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_RSQRTPS),
	FCML_IA_INSTRUCTION( F_VRSQRTPS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VRSQRTPS),
	FCML_IA_INSTRUCTION( F_RSQRTSS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_RSQRTSS),
	FCML_IA_INSTRUCTION( F_VRSQRTSS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VRSQRTSS),
	FCML_IA_INSTRUCTION( F_SAHF, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_SAHF),
	FCML_IA_INSTRUCTION( F_SAR, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_SAR),
	FCML_IA_INSTRUCTION( F_SHL, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_SHL_SAL),
	FCML_IA_INSTRUCTION( F_SHR, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_SHR),
	FCML_IA_INSTRUCTION( F_SBB, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_SBB),
	FCML_IA_INSTRUCTION( F_SCAS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_SCAS ),
	FCML_IA_INSTRUCTION( F_SET, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_SETCC),
	FCML_IA_INSTRUCTION( F_SFENCE, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_SFENCE),
	FCML_IA_INSTRUCTION( F_SGDT, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_SGDT),
	FCML_IA_INSTRUCTION( F_SHLD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_SHLD),
	FCML_IA_INSTRUCTION( F_SHRD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_SHRD),
	FCML_IA_INSTRUCTION( F_SKINIT, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_SKINIT),
	FCML_IA_INSTRUCTION( F_SLWPCB, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_SLWPCB),
	FCML_IA_INSTRUCTION( F_SHUFPD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_SHUFPD),
	FCML_IA_INSTRUCTION( F_VSHUFPD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VSHUFPD),
	FCML_IA_INSTRUCTION( F_SHUFPS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_SHUFPS),
	FCML_IA_INSTRUCTION( F_VSHUFPS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VSHUFPS),
	FCML_IA_INSTRUCTION( F_SIDT, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_SIDT),
	FCML_IA_INSTRUCTION( F_SLDT, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_SLDT),
	FCML_IA_INSTRUCTION( F_SMSW, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_SMSW),
	FCML_IA_INSTRUCTION( F_SQRTPD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_SQRTPD),
	FCML_IA_INSTRUCTION( F_VSQRTPD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VSQRTPD),
	FCML_IA_INSTRUCTION( F_SQRTPS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_SQRTPS),
	FCML_IA_INSTRUCTION( F_VSQRTPS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VSQRTPS),
	FCML_IA_INSTRUCTION( F_SQRTSD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_SQRTSD),
	FCML_IA_INSTRUCTION( F_VSQRTSD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VSQRTSD),
	FCML_IA_INSTRUCTION( F_SQRTSS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_SQRTSS),
	FCML_IA_INSTRUCTION( F_VSQRTSS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VSQRTSS),
	FCML_IA_INSTRUCTION( F_STC, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_STC),
	FCML_IA_INSTRUCTION( F_STD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_STD),
	FCML_IA_INSTRUCTION( F_STGI, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_STGI),
	FCML_IA_INSTRUCTION( F_STI, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_STI),
	FCML_IA_INSTRUCTION( F_STMXCSR, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_STMXCSR),
	FCML_IA_INSTRUCTION( F_VSTMXCSR, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VSTMXCSR),
	FCML_IA_INSTRUCTION( F_STOS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_STOS ),
	FCML_IA_INSTRUCTION( F_STR, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_STR),
	FCML_IA_INSTRUCTION( F_SUB, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_SUB),
	FCML_IA_INSTRUCTION( F_SUBPD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_SUBPD),
	FCML_IA_INSTRUCTION( F_VSUBPD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VSUBPD),
	FCML_IA_INSTRUCTION( F_SUBPS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_SUBPS),
	FCML_IA_INSTRUCTION( F_VSUBPS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VSUBPS),
	FCML_IA_INSTRUCTION( F_SUBSD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_SUBSD),
	FCML_IA_INSTRUCTION( F_VSUBSD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VSUBSD),
	FCML_IA_INSTRUCTION( F_SUBSS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_SUBSS),
	FCML_IA_INSTRUCTION( F_VSUBSS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VSUBSS),
	FCML_IA_INSTRUCTION( F_SWAPGS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_SWAPGS),
	FCML_IA_INSTRUCTION( F_SYSCALL, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_SYSCALL),
	FCML_IA_INSTRUCTION( F_SYSENTER, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_SYSENTER),
	FCML_IA_INSTRUCTION( F_SYSEXIT, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_SYSEXIT),
	FCML_IA_INSTRUCTION( F_SYSRET, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_SYSRET),
	FCML_IA_INSTRUCTION( F_TEST, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_TEST),
	FCML_IA_INSTRUCTION( F_T1MSKC, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_T1MSKC),
	FCML_IA_INSTRUCTION( F_UCOMISD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_UCOMISD),
	FCML_IA_INSTRUCTION( F_VUCOMISD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VUCOMISD),
	FCML_IA_INSTRUCTION( F_UCOMISS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_UCOMISS),
	FCML_IA_INSTRUCTION( F_VUCOMISS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VUCOMISS),
	FCML_IA_INSTRUCTION( F_UD2, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_UD2),
	FCML_IA_INSTRUCTION( F_UNPCKHPD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_UNPCKHPD),
	FCML_IA_INSTRUCTION( F_VUNPCKHPD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VUNPCKHPD),
	FCML_IA_INSTRUCTION( F_UNPCKHPS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_UNPCKHPS),
	FCML_IA_INSTRUCTION( F_VUNPCKHPS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VUNPCKHPS),
	FCML_IA_INSTRUCTION( F_UNPCKLPD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_UNPCKLPD),
	FCML_IA_INSTRUCTION( F_VUNPCKLPD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VUNPCKLPD),
	FCML_IA_INSTRUCTION( F_UNPCKLPS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_UNPCKLPS),
	FCML_IA_INSTRUCTION( F_VUNPCKLPS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VUNPCKLPS),
	FCML_IA_INSTRUCTION( F_VPBROADCASTW, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPBROADCASTW),
	FCML_IA_INSTRUCTION( F_VPBROADCASTB, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPBROADCASTB),
	FCML_IA_INSTRUCTION( F_VPBROADCASTD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPBROADCASTD),
	FCML_IA_INSTRUCTION( F_VPBROADCASTQ, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPBROADCASTQ),
	FCML_IA_INSTRUCTION( F_VMPTRLD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VMPTRLD),
	FCML_IA_INSTRUCTION( F_VMPTRST, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VMPTRST),
	FCML_IA_INSTRUCTION( F_VMCLEAR, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VMCLEAR),
	FCML_IA_INSTRUCTION( F_VMREAD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VMREAD),
	FCML_IA_INSTRUCTION( F_VMWRITE, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VMWRITE),
	FCML_IA_INSTRUCTION( F_VMLAUNCH, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VMLAUNCH),
	FCML_IA_INSTRUCTION( F_VMRESUME, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VMRESUME),
	FCML_IA_INSTRUCTION( F_VMXOFF, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VMXOFF),
	FCML_IA_INSTRUCTION( F_VMXON, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VMXON),
	FCML_IA_INSTRUCTION( F_VMCALL, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VMCALL),
	FCML_IA_INSTRUCTION( F_VMFUNC, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VMFUNC),
	FCML_IA_INSTRUCTION( F_VBROADCASTSD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VBROADCASTSD),
	FCML_IA_INSTRUCTION( F_VBROADCASTSS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VBROADCASTSS),
	FCML_IA_INSTRUCTION( F_VBROADCASTI128, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VBROADCASTI128),
	FCML_IA_INSTRUCTION( F_VBROADCASTF128, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VBROADCASTF128),
	FCML_IA_INSTRUCTION( F_VCVTPH2PS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VCVTPH2PS),
	FCML_IA_INSTRUCTION( F_VCVTPS2PH, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VCVTPS2PH),
	FCML_IA_INSTRUCTION( F_VERR, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VERR),
	FCML_IA_INSTRUCTION( F_VERW, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VERW),
	FCML_IA_INSTRUCTION( F_VEXTRACTF128, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VEXTRACTF128 ),
	FCML_IA_INSTRUCTION( F_VMLOAD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VMLOAD),
	FCML_IA_INSTRUCTION( F_VMMCALL, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VMMCALL),
	FCML_IA_INSTRUCTION( F_VMRUN, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VMRUN),
	FCML_IA_INSTRUCTION( F_VMSAVE, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VMSAVE),
	FCML_IA_INSTRUCTION( F_VPERMILPD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPERMILPD),
	FCML_IA_INSTRUCTION( F_VPERMILPS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPERMILPS),
	FCML_IA_INSTRUCTION( F_VPSLLVQ, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPSLLVQ),
	FCML_IA_INSTRUCTION( F_VPERM2F128, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPERM2F128),
	FCML_IA_INSTRUCTION( F_VPERM2I128, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPERM2I128),
	FCML_IA_INSTRUCTION( F_VEXTRACTI128, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VEXTRACTI128),
	FCML_IA_INSTRUCTION( F_VINSERTI128, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VINSERTI128),
	FCML_IA_INSTRUCTION( F_VPSRAVD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPSRAVD),
	FCML_IA_INSTRUCTION( F_VPERMD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPERMD),
	FCML_IA_INSTRUCTION( F_VPSLLVD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPSLLVD),
	FCML_IA_INSTRUCTION( F_VPSRLVD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPSRLVD),
	FCML_IA_INSTRUCTION( F_VPSRLVQ, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPSRLVQ),
	FCML_IA_INSTRUCTION( F_VPERMPD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPERMPD),
	FCML_IA_INSTRUCTION( F_VPERMQ, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPERMQ),
	FCML_IA_INSTRUCTION( F_VPERMPS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPERMPS),
	FCML_IA_INSTRUCTION( F_VTESTPS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VTESTPS),
	FCML_IA_INSTRUCTION( F_VTESTPD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VTESTPD),
	FCML_IA_INSTRUCTION( F_VGATHERDPD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VGATHERDPD),
	FCML_IA_INSTRUCTION( F_VGATHERQPD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VGATHERQPD),
	FCML_IA_INSTRUCTION( F_VGATHERDPS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VGATHERDPS),
	FCML_IA_INSTRUCTION( F_VGATHERQPS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VGATHERQPS),
	FCML_IA_INSTRUCTION( F_VPGATHERDD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPGATHERDD),
	FCML_IA_INSTRUCTION( F_VPGATHERQD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPGATHERQD),
	FCML_IA_INSTRUCTION( F_VPGATHERDQ, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPGATHERDQ),
	FCML_IA_INSTRUCTION( F_VPGATHERQQ, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPGATHERQQ),
	FCML_IA_INSTRUCTION( F_VZEROALL, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VZEROALL),
	FCML_IA_INSTRUCTION( F_VZEROUPPER, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VZEROUPPER),
	FCML_IA_INSTRUCTION( F_WAIT, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_WAIT),
	FCML_IA_INSTRUCTION( F_WBINVD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_WBINVD),
	FCML_IA_INSTRUCTION( F_WRFSBASE, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_WRFSBASE),
	FCML_IA_INSTRUCTION( F_WRGSBASE, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_WRGSBASE),
	FCML_IA_INSTRUCTION( F_WRMSR, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_WRMSR),
	FCML_IA_INSTRUCTION( F_XADD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_XADD),
	FCML_IA_INSTRUCTION( F_XCHG, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_XCHG),
	FCML_IA_INSTRUCTION( F_XGETBV, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_XGETBV),
	FCML_IA_INSTRUCTION( F_XLAT, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_XLAT ),
	FCML_IA_INSTRUCTION( F_XOR, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_XOR),
	FCML_IA_INSTRUCTION( F_XORPD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_XORPD),
	FCML_IA_INSTRUCTION( F_VXORPD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VXORPD),
	FCML_IA_INSTRUCTION( F_XORPS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_XORPS),
	FCML_IA_INSTRUCTION( F_VXORPS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VXORPS),
	FCML_IA_INSTRUCTION( F_XRSTOR, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_XRSTOR),
	FCML_IA_INSTRUCTION( F_XRSTOR64, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_XRSTOR64),
	FCML_IA_INSTRUCTION( F_XSAVE, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_XSAVE),
	FCML_IA_INSTRUCTION( F_XSAVE64, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_XSAVE64),
	FCML_IA_INSTRUCTION( F_XSAVEOPT, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_XSAVEOPT),
	FCML_IA_INSTRUCTION( F_XSAVEOPT64, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_XSAVEOPT64),
	FCML_IA_INSTRUCTION( F_XSETBV, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_XSETBV),
	FCML_IA_INSTRUCTION( F_FEMMS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_FEMMS ),
	FCML_IA_MULTI_INSTRUCTION( FCML_MI_AMD3DNOW, fcml_st_def_instruction_code_def_AMD3DNOW, fcml_st_def_addr_mode_desc_MI_AMD3DNOW ),
	FCML_IA_INSTRUCTION( F_PREFETCH, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PREFETCH),
	FCML_IA_INSTRUCTION( F_VFMADD213PD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VFMADD213PD),
	FCML_IA_INSTRUCTION( F_VFMADDPD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VFMADDPD),
	FCML_IA_INSTRUCTION( F_VFMADD132PD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VFMADD132PD),
	FCML_IA_INSTRUCTION( F_VFMADD231PD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VFMADD231PD),
	FCML_IA_INSTRUCTION( F_VFMADDPS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VFMADDPS),
	FCML_IA_INSTRUCTION( F_VFMADD231PS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VFMADD231PS),
	FCML_IA_INSTRUCTION( F_VFMADD132PS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VFMADD132PS),
	FCML_IA_INSTRUCTION( F_VFMADD213PS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VFMADD213PS),
	FCML_IA_INSTRUCTION( F_VFMADD132SD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VFMADD132SD),
	FCML_IA_INSTRUCTION( F_VFMADD213SD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VFMADD213SD),
	FCML_IA_INSTRUCTION( F_VFMADDSD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VFMADDSD),
	FCML_IA_INSTRUCTION( F_VFMADD231SD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VFMADD231SD),
	FCML_IA_INSTRUCTION( F_VFMADD132SS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VFMADD132SS),
	FCML_IA_INSTRUCTION( F_VFMADD213SS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VFMADD213SS),
	FCML_IA_INSTRUCTION( F_VFMADDSS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VFMADDSS),
	FCML_IA_INSTRUCTION( F_VFMADD231SS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VFMADD231SS),
	FCML_IA_INSTRUCTION( F_VFMADDSUB132PD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VFMADDSUB132PD),
	FCML_IA_INSTRUCTION( F_VFMADDSUB213PD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VFMADDSUB213PD),
	FCML_IA_INSTRUCTION( F_VFMADDSUBPD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VFMADDSUBPD),
	FCML_IA_INSTRUCTION( F_VFMADDSUB231PD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VFMADDSUB231PD),
	FCML_IA_INSTRUCTION( F_VFMADDSUB231PS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VFMADDSUB231PS),
	FCML_IA_INSTRUCTION( F_VFMADDSUBPS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VFMADDSUBPS),
	FCML_IA_INSTRUCTION( F_VFMADDSUB132PS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VFMADDSUB132PS),
	FCML_IA_INSTRUCTION( F_VFMADDSUB213PS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VFMADDSUB213PS),
	FCML_IA_INSTRUCTION( F_VFMSUBADDPD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VFMSUBADDPD),
	FCML_IA_INSTRUCTION( F_VFMSUBADD213PD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VFMSUBADD213PD),
	FCML_IA_INSTRUCTION( F_VFMSUBADD132PD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VFMSUBADD132PD),
	FCML_IA_INSTRUCTION( F_VFMSUBADD231PD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VFMSUBADD231PD),
	FCML_IA_INSTRUCTION( F_VFMSUBADDPS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VFMSUBADDPS),
	FCML_IA_INSTRUCTION( F_VFMSUBADD213PS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VFMSUBADD213PS),
	FCML_IA_INSTRUCTION( F_VFMSUBADD132PS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VFMSUBADD132PS),
	FCML_IA_INSTRUCTION( F_VFMSUBADD231PS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VFMSUBADD231PS),
	FCML_IA_INSTRUCTION( F_VFMSUB213PD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VFMSUB213PD),
	FCML_IA_INSTRUCTION( F_VFMSUBPD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VFMSUBPD),
	FCML_IA_INSTRUCTION( F_VFMSUB132PD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VFMSUB132PD),
	FCML_IA_INSTRUCTION( F_VFMSUB231PD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VFMSUB231PD),
	FCML_IA_INSTRUCTION( F_VFMSUB213PS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VFMSUB213PS),
	FCML_IA_INSTRUCTION( F_VFMSUBPS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VFMSUBPS),
	FCML_IA_INSTRUCTION( F_VFMSUB132PS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VFMSUB132PS),
	FCML_IA_INSTRUCTION( F_VFMSUB231PS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VFMSUB231PS),
	FCML_IA_INSTRUCTION( F_VFMSUBSD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VFMSUBSD),
	FCML_IA_INSTRUCTION( F_VFMSUB231SD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VFMSUB231SD),
	FCML_IA_INSTRUCTION( F_VFMSUB132SD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VFMSUB132SD),
	FCML_IA_INSTRUCTION( F_VFMSUB213SD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VFMSUB213SD),
	FCML_IA_INSTRUCTION( F_VFMSUB231SS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VFMSUB231SS),
	FCML_IA_INSTRUCTION( F_VFMSUB213SS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VFMSUB213SS),
	FCML_IA_INSTRUCTION( F_VFMSUB132SS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VFMSUB132SS),
	FCML_IA_INSTRUCTION( F_VFMSUBSS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VFMSUBSS),
	FCML_IA_INSTRUCTION( F_VFNMADD231PD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VFNMADD231PD),
	FCML_IA_INSTRUCTION( F_VFNMADDPD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VFNMADDPD),
	FCML_IA_INSTRUCTION( F_VFNMADD132PD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VFNMADD132PD),
	FCML_IA_INSTRUCTION( F_VFNMADD213PD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VFNMADD213PD),
	FCML_IA_INSTRUCTION( F_VFNMADD231PS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VFNMADD231PS),
	FCML_IA_INSTRUCTION( F_VFNMADD132PS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VFNMADD132PS),
	FCML_IA_INSTRUCTION( F_VFNMADD213PS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VFNMADD213PS),
	FCML_IA_INSTRUCTION( F_VFNMADDPS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VFNMADDPS),
	FCML_IA_INSTRUCTION( F_VFNMADD213SD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VFNMADD213SD),
	FCML_IA_INSTRUCTION( F_VFNMADDSD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VFNMADDSD),
	FCML_IA_INSTRUCTION( F_VFNMADD231SD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VFNMADD231SD),
	FCML_IA_INSTRUCTION( F_VFNMADD132SD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VFNMADD132SD),
	FCML_IA_INSTRUCTION( F_VFNMADD213SS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VFNMADD213SS),
	FCML_IA_INSTRUCTION( F_VFNMADDSS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VFNMADDSS),
	FCML_IA_INSTRUCTION( F_VFNMADD231SS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VFNMADD231SS),
	FCML_IA_INSTRUCTION( F_VFNMADD132SS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VFNMADD132SS),
	FCML_IA_INSTRUCTION( F_VFNMSUB132PD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VFNMSUB132PD),
	FCML_IA_INSTRUCTION( F_VFNMSUB213PD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VFNMSUB213PD),
	FCML_IA_INSTRUCTION( F_VFNMSUB231PD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VFNMSUB231PD),
	FCML_IA_INSTRUCTION( F_VFNMSUBPD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VFNMSUBPD),
	FCML_IA_INSTRUCTION( F_VFNMSUBPS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VFNMSUBPS),
	FCML_IA_INSTRUCTION( F_VFNMSUB213PS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VFNMSUB213PS),
	FCML_IA_INSTRUCTION( F_VFNMSUB132PS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VFNMSUB132PS),
	FCML_IA_INSTRUCTION( F_VFNMSUB231PS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VFNMSUB231PS),
	FCML_IA_INSTRUCTION( F_VFNMSUBSD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VFNMSUBSD),
	FCML_IA_INSTRUCTION( F_VFNMSUB231SD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VFNMSUB231SD),
	FCML_IA_INSTRUCTION( F_VFNMSUB213SD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VFNMSUB213SD),
	FCML_IA_INSTRUCTION( F_VFNMSUB132SD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VFNMSUB132SD),
	FCML_IA_INSTRUCTION( F_VFNMSUBSS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VFNMSUBSS),
	FCML_IA_INSTRUCTION( F_VFNMSUB132SS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VFNMSUB132SS),
	FCML_IA_INSTRUCTION( F_VFNMSUB213SS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VFNMSUB213SS),
	FCML_IA_INSTRUCTION( F_VFNMSUB231SS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VFNMSUB231SS),
	FCML_IA_INSTRUCTION( F_BEXTR, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_BEXTR),
	FCML_IA_INSTRUCTION( F_BLCFILL, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_BLCFILL ),
	FCML_IA_INSTRUCTION( F_BLCI, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_BLCI ),
	FCML_IA_INSTRUCTION( F_BLCIC, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_BLCIC ),
	FCML_IA_INSTRUCTION( F_BLCMSK, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_BLCMSK ),
	FCML_IA_INSTRUCTION( F_BLCS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_BLCS ),
	FCML_IA_INSTRUCTION( F_BLSFILL, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_BLSFILL ),
	FCML_IA_INSTRUCTION( F_BLSIC, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_BLSIC ),
	FCML_IA_INSTRUCTION( F_ANDN, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_ANDN ),
	FCML_IA_INSTRUCTION( F_BEXR, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_BEXR ),
	FCML_IA_INSTRUCTION( F_BLSI, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_BLSI ),
	FCML_IA_INSTRUCTION( F_BLSMSK, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_BLSMSK ),
	FCML_IA_INSTRUCTION( F_BLSR, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_BLSR ),
	FCML_IA_INSTRUCTION( F_BZHI, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_BZHI ),
	FCML_IA_INSTRUCTION( F_LZCNT, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_LZCNT ),
	FCML_IA_INSTRUCTION( F_MULX, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_MULX),
	FCML_IA_INSTRUCTION( F_PDEP, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PDEP),
	FCML_IA_INSTRUCTION( F_PEXT, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_PEXT),
	FCML_IA_INSTRUCTION( F_RORX, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_RORX),
	FCML_IA_INSTRUCTION( F_SHLX, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_SHLX),
	FCML_IA_INSTRUCTION( F_SHRX, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_SHRX),
	FCML_IA_INSTRUCTION( F_SARX, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_SARX),
	FCML_IA_INSTRUCTION( F_TZCNT, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_TZCNT),
	FCML_IA_INSTRUCTION( F_TZMSK, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_TZMSK),
	FCML_IA_INSTRUCTION( F_XABORT, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_XABORT),
	FCML_IA_INSTRUCTION( F_XBEGIN, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_XBEGIN),
	FCML_IA_INSTRUCTION( F_XEND, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_XEND),
	FCML_IA_INSTRUCTION( F_XTEST, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_XTEST),
	FCML_IA_INSTRUCTION( F_ADCX, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_ADCX ),
	FCML_IA_INSTRUCTION( F_ADOX, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_ADOX ),
	FCML_IA_INSTRUCTION( F_RDSEED, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_RDSEED),
	FCML_IA_INSTRUCTION( F_CLAC, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_CLAC),
	FCML_IA_INSTRUCTION( F_STAC, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_STAC),
	FCML_IA_INSTRUCTION( F_VFRCZPD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VFRCZPD),
	FCML_IA_INSTRUCTION( F_VFRCZPS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VFRCZPS),
	FCML_IA_INSTRUCTION( F_VFRCZSD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VFRCZSD),
	FCML_IA_INSTRUCTION( F_VFRCZSS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VFRCZSS),
	FCML_IA_INSTRUCTION( F_VPCMOV, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPCMOV),
	FCML_IA_INSTRUCTION( F_VPCOMB, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPCOMB ),
	FCML_IA_INSTRUCTION( F_VPCOMW, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPCOMW ),
	FCML_IA_INSTRUCTION( F_VPCOMD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPCOMD ),
	FCML_IA_INSTRUCTION( F_VPCOMQ, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPCOMQ ),
	FCML_IA_INSTRUCTION( F_VPCOMUB, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPCOMUB ),
	FCML_IA_INSTRUCTION( F_VPCOMUW, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPCOMUW ),
	FCML_IA_INSTRUCTION( F_VPCOMUD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPCOMUD ),
	FCML_IA_INSTRUCTION( F_VPCOMUQ, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPCOMUQ ),
	FCML_IA_INSTRUCTION( F_VPERMIL2PD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPERMIL2PD),
	FCML_IA_INSTRUCTION( F_VPERMIL2PS, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPERMIL2PS),
	FCML_IA_INSTRUCTION( F_VPHADDBD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPHADDBD),
	FCML_IA_INSTRUCTION( F_VPHADDBW, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPHADDBW),
	FCML_IA_INSTRUCTION( F_VPHADDBQ, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPHADDBQ),
	FCML_IA_INSTRUCTION( F_VPHADDDQ, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPHADDDQ),
	FCML_IA_INSTRUCTION( F_VPHADDUBD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPHADDUBD),
	FCML_IA_INSTRUCTION( F_VPHADDUBQ, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPHADDUBQ),
	FCML_IA_INSTRUCTION( F_VPHADDUBW, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPHADDUBW),
	FCML_IA_INSTRUCTION( F_VPHADDUDQ, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPHADDUDQ),
	FCML_IA_INSTRUCTION( F_VPHADDUWD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPHADDUWD),
	FCML_IA_INSTRUCTION( F_VPHADDUWQ, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPHADDUWQ),
	FCML_IA_INSTRUCTION( F_VPHADDWD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPHADDWD),
	FCML_IA_INSTRUCTION( F_VPHADDWQ, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPHADDWQ),
	FCML_IA_INSTRUCTION( F_VPHSUBBW, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPHSUBBW),
	FCML_IA_INSTRUCTION( F_VPHSUBDQ, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPHSUBDQ),
	FCML_IA_INSTRUCTION( F_VPHSUBDQ, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPHSUBDQ),
	FCML_IA_INSTRUCTION( F_VPHSUBWD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPHSUBWD),
	FCML_IA_INSTRUCTION( F_VPMACSDD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPMACSDD),
	FCML_IA_INSTRUCTION( F_VPMACSDQH, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPMACSDQH),
	FCML_IA_INSTRUCTION( F_VPMACSDQL, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPMACSDQL),
	FCML_IA_INSTRUCTION( F_VPMACSSDD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPMACSSDD),
	FCML_IA_INSTRUCTION( F_VPMACSSDQH, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPMACSSDQH),
	FCML_IA_INSTRUCTION( F_VPMACSSDQL, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPMACSSDQL),
	FCML_IA_INSTRUCTION( F_VPMACSSWD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPMACSSWD),
	FCML_IA_INSTRUCTION( F_VPMACSSWW, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPMACSSWW),
	FCML_IA_INSTRUCTION( F_VPMACSWD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPMACSWD),
	FCML_IA_INSTRUCTION( F_VPMACSWW, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPMACSWW),
	FCML_IA_INSTRUCTION( F_VPMADCSSWD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPMADCSSWD),
	FCML_IA_INSTRUCTION( F_VPMADCSWD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPMADCSWD),
	FCML_IA_INSTRUCTION( F_VPPERM, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPPERM),
	FCML_IA_INSTRUCTION( F_VPROTD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPROTD),
	FCML_IA_INSTRUCTION( F_VPROTB, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPROTB),
	FCML_IA_INSTRUCTION( F_VPROTQ, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPROTQ),
	FCML_IA_INSTRUCTION( F_VPROTW, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPROTW),
	FCML_IA_INSTRUCTION( F_VPSHAB, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPSHAB),
	FCML_IA_INSTRUCTION( F_VPSHAD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPSHAD),
	FCML_IA_INSTRUCTION( F_VPSHAQ, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPSHAQ),
	FCML_IA_INSTRUCTION( F_VPSHAW, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPSHAW),
	FCML_IA_INSTRUCTION( F_VPSHLB, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPSHLB),
	FCML_IA_INSTRUCTION( F_VPSHLD, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPSHLD),
	FCML_IA_INSTRUCTION( F_VPSHLQ, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPSHLQ),
	FCML_IA_INSTRUCTION( F_VPSHLW, FCML_EMPTY_MNEMONIC, fcml_st_def_addr_mode_desc_VPSHLW),
	FCML_IA_INSTRUCTION( F_UNKNOWN, NULL, NULL )
};

