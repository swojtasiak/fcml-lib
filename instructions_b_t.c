/*
 * instructions.c
 *
 *  Created on: 01-06-2013
 *      Author: tAs
 */

#include "fcml_env.h"
#include "fcml_assembler.h"
#include "instructions_b_t.h"

int fcml_tf_instructions_b_suite_init(void) {
	return 0;
}

int fcml_tf_instructions_b_suite_cleanup(void) {
	return 0;
}

void fcml_tf_instruction_BLENDPD(void) {
	FCML_I32( "blendpd xmm2,oword ptr [ecx+eax],0ffh", 0x66, 0x0F, 0x3a, 0x0D, 0x14, 0x01, 0xFF );
	FCML_I64( "blendpd xmm2,oword ptr [rcx+rax],0ffh", 0x66, 0x0F, 0x3a, 0x0D, 0x14, 0x01, 0xFF );
	// VEX.NDS.128.66.0F3A 0D /r ib VBLENDPD xmm1,xmm2,xmm3/m128,imm8
	// VEX.NDS.256.66.0F3A 0D /r ib VBLENDPD ymm1,ymm2,ymm3/m256,imm8
	FCML_I64( "vblendpd ymm10,ymm14,ymmword ptr [r9+rax],20h", 0xC4, 0x43, 0x0D, 0x0D, 0x14, 0x01, 0x20 );
	FCML_I32_D( "vblendpd xmm2,xmm7,oword ptr [ecx+eax],20h", 0xC4, 0xC3, 0x41, 0x0D, 0x14, 0x01, 0x20 ); // REX.B ignored in 32bit mode.
	FCML_I32_D( "vblendpd xmm2,xmm2,oword ptr [ecx+eax],20h", 0xC4, 0xC3, 0x69, 0x0D, 0x14, 0x01, 0x20 ); // REX.B ignored in 32bit mode.
	FCML_I32( "vblendpd xmm2,xmm7,oword ptr [ecx+eax],20h", 0xC4, 0xE3, 0x41, 0x0D, 0x14, 0x01, 0x20 );
	FCML_I32( "vblendpd xmm2,xmm2,oword ptr [ecx+eax],20h", 0xC4, 0xE3, 0x69, 0x0D, 0x14, 0x01, 0x20 );
}

void fcml_tf_instruction_BLENDPS(void) {
	FCML_I32( "blendps xmm2,oword ptr [ecx+eax],0ffh", 0x66, 0x0F, 0x3a, 0x0C, 0x14, 0x01, 0xFF );
	FCML_I64( "blendps xmm2,oword ptr [rcx+rax],0ffh", 0x66, 0x0F, 0x3a, 0x0C, 0x14, 0x01, 0xFF );
	// VEX.NDS.128.66.0F3A 0C /r ib VBLENDPS xmm1,xmm2,xmm3/m128,imm8
	// VEX.NDS.256.66.0F3A 0C /r ib VBLENDPS ymm1,ymm2,ymm3/m256,imm8
	FCML_I64( "vblendps ymm10,ymm14,ymmword ptr [r9+rax],20h", 0xC4, 0x43, 0x0D, 0x0C, 0x14, 0x01, 0x20 );
	FCML_I32( "vblendps xmm2,xmm7,oword ptr [ecx+eax],20h", 0xC4, 0xE3, 0x41, 0x0C, 0x14, 0x01, 0x20 );
	FCML_I32( "vblendps xmm2,xmm2,oword ptr [ecx+eax],20h", 0xC4, 0xE3, 0x69, 0x0C, 0x14, 0x01, 0x20 );
}

void fcml_tf_instruction_BLENDVPD(void) {
	FCML_I32( "blendvpd xmm2,oword ptr [ecx+eax],xmm0", 0x66, 0x0F, 0x38, 0x15, 0x14, 0x01 );
	FCML_I64( "blendvpd xmm2,oword ptr [rcx+rax],xmm0", 0x66, 0x0F, 0x38, 0x15, 0x14, 0x01 );
	// VEX.NDS.128.66.0F3A 4B /r /is4 VBLENDVPD xmm1, xmm2, xmm3/m128, xmm4
	// VEX.NDS.256.66.0F3A 4B /r /is4 VBLENDVPD ymm1, ymm2, ymm3/m256, ymm4
	FCML_I64( "vblendvpd ymm10,ymm14,ymmword ptr [r9+rax],ymm2", 0xC4, 0x43, 0x0D, 0x4B, 0x14, 0x01, 0x20 );
	FCML_I32( "vblendvpd xmm2,xmm7,oword ptr [ecx+eax],xmm2", 0xC4, 0xE3, 0x41, 0x4B, 0x14, 0x01, 0x20 );
	FCML_I32_D( "vblendvpd xmm2,xmm2,oword ptr [ecx+eax],xmm2", 0xC4, 0xE3, 0x69, 0x4B, 0x14, 0x01, 0xA0 );
	FCML_I32( "vblendvpd xmm2,xmm2,oword ptr [ecx+eax],xmm2", 0xC4, 0xE3, 0x69, 0x4B, 0x14, 0x01, 0x20 );
}

void fcml_tf_instruction_BLENDVPS(void) {
	FCML_I32( "blendvps xmm2,oword ptr [ecx+eax],xmm0", 0x66, 0x0F, 0x38, 0x14, 0x14, 0x01 );
	FCML_I64( "blendvps xmm2,oword ptr [rcx+rax],xmm0", 0x66, 0x0F, 0x38, 0x14, 0x14, 0x01 );
	// VEX.NDS.128.66.0F3A 4A /r /is4 VBLENDVPS xmm1, xmm2, xmm3/m128, xmm4
	// VEX.NDS.256.66.0F3A 4A /r /is4 VBLENDVPS ymm1, ymm2, ymm3/m256, ymm4
	FCML_I64( "vblendvps ymm10,ymm14,ymmword ptr [r9+rax],ymm2", 0xC4, 0x43, 0x0D, 0x4A, 0x14, 0x01, 0x20 );
	FCML_I32( "vblendvps xmm2,xmm7,oword ptr [ecx+eax],xmm2", 0xC4, 0xE3, 0x41, 0x4A, 0x14, 0x01, 0x20 );
	FCML_I32_D( "vblendvps xmm2,xmm2,oword ptr [ecx+eax],xmm2", 0xC4, 0xC3, 0x69, 0x4A, 0x14, 0x01, 0xA0 );
	FCML_I32( "vblendvps xmm2,xmm2,oword ptr [ecx+eax],xmm2", 0xC4, 0xE3, 0x69, 0x4A, 0x14, 0x01, 0x20 );
}

void fcml_tf_instruction_BOUND(void) {
	FCML_I32( "bound esi,qword ptr [eax]", 0x62, 0x30 );
	FCML_I32( "bound si,dword ptr [eax]", 0x66, 0x62, 0x30 );
	FCML_I32( "bound si,dword ptr [bx+si]", 0x66, 0x67, 0x62, 0x30 );
	// Not supported in 64.
	FCML_I64_FAILED( "bound si,dword ptr [eax]", 0x62, 0x30 );
	// Addressing not supported, only memory addressing is allowed here.
	FCML_I64_FAILED( "bound si,dword ptr eax", 0x62, 0xc0 );
}

void fcml_tf_instruction_BSF(void) {
	FCML_I32( "bsf esp,dword ptr [ebp+04030201h]", 0x0f, 0xbc, 0xa5, 0x01, 0x02, 0x03, 04 );
	FCML_I32( "bsf sp,word ptr [di+0201h]", 0x66, 0x67, 0x0f, 0xbc, 0xa5, 0x01, 0x02 );
	FCML_I32( "bsf esp,dword ptr [di+0201h]", 0x67, 0x0f, 0xbc, 0xa5, 0x01, 0x02 );
	FCML_I64( "bsf r12,qword ptr [r9+rcx*4+0000000000000001h]", 0x4D, 0x0f, 0xbc, 0x64, 0x89, 0x01 );
}

void fcml_tf_instruction_BSR(void) {
	// We can only assemble BSR instructions, because they are always disassembled to BSF.
	FCML_I32_A( "bsr esp,dword ptr [ebp+04030201h]", 0x0f, 0xbc, 0xa5, 0x01, 0x02, 0x03, 04 );
	FCML_I32_A( "bsr sp,word ptr [di+0201h]", 0x66, 0x67, 0x0f, 0xbc, 0xa5, 0x01, 0x02 );
	FCML_I32_A( "bsr esp,dword ptr [di+0201h]", 0x67, 0x0f, 0xbc, 0xa5, 0x01, 0x02 );
	FCML_I64_A( "bsr r12,qword ptr [r9+rcx*4+0000000000000001h]", 0x4D, 0x0f, 0xbc, 0x64, 0x89, 0x01 );
}

void fcml_tf_instruction_BSWAP(void) {

	FCML_I3264( "bswap eax", 0x0f, 0xc8 );
	FCML_I3264( "bswap ecx", 0x0f, 0xc9 );
	FCML_I3264( "bswap edx", 0x0f, 0xca );
	FCML_I3264( "bswap ebx", 0x0f, 0xcb );
	FCML_I3264( "bswap esp", 0x0f, 0xcc );
	FCML_I3264( "bswap ebp", 0x0f, 0xcd );
	FCML_I3264( "bswap esi", 0x0f, 0xce );
	FCML_I3264( "bswap edi", 0x0f, 0xcf );

	FCML_I3264_D( "bswap eax", 0x66, 0x0f, 0xc8 );
	FCML_I3264_D( "bswap ecx", 0x66, 0x0f, 0xc9 );
	FCML_I3264_D( "bswap edx", 0x66, 0x0f, 0xca );
	FCML_I3264_D( "bswap ebx", 0x66, 0x0f, 0xcb );
	FCML_I3264_D( "bswap esp", 0x66, 0x0f, 0xcc );
	FCML_I3264_D( "bswap ebp", 0x66, 0x0f, 0xcd );
	FCML_I3264_D( "bswap esi", 0x66, 0x0f, 0xce );
	FCML_I3264_D( "bswap edi", 0x66, 0x0f, 0xcf );

	// only REX.R
	FCML_I64( "bswap r8", 0x49, 0x0f, 0xc8 );
	FCML_I64( "bswap r9", 0x49, 0x0f, 0xc9 );
	FCML_I64( "bswap r10", 0x49, 0x0f, 0xca );
	FCML_I64( "bswap r11", 0x49, 0x0f, 0xcb );
	FCML_I64( "bswap r12", 0x49, 0x0f, 0xcc );
	FCML_I64( "bswap r13", 0x49, 0x0f, 0xcd );
	FCML_I64( "bswap r14", 0x49, 0x0f, 0xce );
	FCML_I64( "bswap r15", 0x49, 0x0f, 0xcf );
}

CU_TestInfo fctl_ti_instructions_b[] = {
    { "fcml_tf_instruction_BLENDPD", fcml_tf_instruction_BLENDPD },
    { "fcml_tf_instruction_BLENDPS", fcml_tf_instruction_BLENDPS },
    { "fcml_tf_instruction_BLENDVPD", fcml_tf_instruction_BLENDVPD },
    { "fcml_tf_instruction_BLENDVPS", fcml_tf_instruction_BLENDVPS },
    { "fcml_tf_instruction_BOUND", fcml_tf_instruction_BOUND },
    { "fcml_tf_instruction_BSF", fcml_tf_instruction_BSF },
    { "fcml_tf_instruction_BSR", fcml_tf_instruction_BSR },
    { "fcml_tf_instruction_BSWAP", fcml_tf_instruction_BSWAP },
    CU_TEST_INFO_NULL,
};

CU_SuiteInfo fctl_si_instructions_b[] = {
    { "suite-fctl_ti_instructions_b", fcml_tf_instructions_b_suite_init, fcml_tf_instructions_b_suite_cleanup, fctl_ti_instructions_b },
    CU_SUITE_INFO_NULL,
};
