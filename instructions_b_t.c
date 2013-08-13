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
	FCML_I32( "vblendvpd xmm2,xmm2,oword ptr [ecx+eax],xmm2", 0xC4, 0xE3, 0x69, 0x4B, 0x14, 0x01, 0xA0 );
}

CU_TestInfo fctl_ti_instructions_b[] = {
    { "fcml_tf_instruction_BLENDPD", fcml_tf_instruction_BLENDPD },
    { "fcml_tf_instruction_BLENDPS", fcml_tf_instruction_BLENDPS },
    { "fcml_tf_instruction_BLENDVPD", fcml_tf_instruction_BLENDVPD },
    CU_TEST_INFO_NULL,
};

CU_SuiteInfo fctl_si_instructions_b[] = {
    { "suite-fctl_ti_instructions_b", fcml_tf_instructions_b_suite_init, fcml_tf_instructions_b_suite_cleanup, fctl_ti_instructions_b },
    CU_SUITE_INFO_NULL,
};
