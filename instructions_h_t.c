/*
 * instructions.c
 *
 *  Created on: 01-06-2013
 *      Author: tAs
 */

#include "fcml_env.h"
#include "fcml_assembler.h"
#include "instructions_h_t.h"

int fcml_tf_instructions_h_suite_init(void) {
	return 0;
}

int fcml_tf_instructions_h_suite_cleanup(void) {
	return 0;
}

void fcml_tf_instruction_HADDPD(void) {
    FCML_I64( "haddpd xmm0,oword ptr [rax+0000000000000020h]", 0x66, 0x0F, 0x7C, 0x40, 0x20 );
    FCML_I32( "haddpd xmm0,oword ptr [eax+00000020h]", 0x66, 0x0F, 0x7C, 0x40, 0x20 );
    // VEX.NDS.128.66.0F 7C /r VHADDPD xmm1,xmm2,xmm3/m128
    // VEX.NDS.256.66.0F 7C /r VHADDPD ymm1,ymm2,ymm3/m256
    FCML_I64( "vhaddpd ymm10,ymm14,ymmword ptr [r9+rax]", 0xC4, 0x41, 0x0D, 0x7C, 0x14, 0x01 );
    FCML_I32_D( "vhaddpd xmm2,xmm7,oword ptr [ecx+eax]", 0xC4, 0xC1, 0x41, 0x7C, 0x14, 0x01 );
    FCML_I32_D( "vhaddpd xmm2,xmm2,oword ptr [ecx+eax]", 0xC4, 0xC1, 0x69, 0x7C, 0x14, 0x01 );
    FCML_I32( "vhaddpd xmm2,xmm7,oword ptr [ecx+eax]", 0xc5, 0xc1, 0x7c, 0x14, 0x01 );
    FCML_I32( "vhaddpd xmm2,xmm2,oword ptr [ecx+eax]", 0xc5, 0xe9, 0x7c, 0x14, 0x01 );
}

void fcml_tf_instruction_HADDPS(void) {
    FCML_I64( "haddps xmm0,oword ptr [rax+0000000000000020h]", 0xF2, 0x0F, 0x7C, 0x40, 0x20 );
    FCML_I32( "haddps xmm0,oword ptr [eax+00000020h]", 0xF2, 0x0F, 0x7C, 0x40, 0x20 );
    // VEX.NDS.128.F2.0F 7C /r VHADDPS xmm1,xmm2,xmm3/m128
    // VEX.NDS.256.F2.0F 7C /r VHADDPS ymm1,ymm2,ymm3/m256
    FCML_I64( "vhaddps ymm10,ymm14,ymmword ptr [r9+rax]", 0xC4, 0x41, 0x0F, 0x7C, 0x14, 0x01 );
    FCML_I32_D( "vhaddps xmm2,xmm7,oword ptr [ecx+eax]", 0xC4, 0xC1, 0x43, 0x7C, 0x14, 0x01 );
    FCML_I32_D( "vhaddps xmm2,xmm2,oword ptr [ecx+eax]", 0xC4, 0xC1, 0x6B, 0x7C, 0x14, 0x01 );
    FCML_I32( "vhaddps xmm2,xmm7,oword ptr [ecx+eax]", 0xc5, 0xc3, 0x7c, 0x14, 0x01 );
    FCML_I32( "vhaddps xmm2,xmm2,oword ptr [ecx+eax]", 0xc5, 0xeb, 0x7c, 0x14, 0x01 );
}

void fcml_tf_instruction_HLT(void) {
    FCML_I3264( "hlt", 0xF4 );
}

void fcml_tf_instruction_HSUBPD(void) {
    FCML_I64( "hsubpd xmm0,oword ptr [rax+0000000000000020h]", 0x66, 0x0F, 0x7D, 0x40, 0x20 );
    FCML_I32( "hsubpd xmm0,oword ptr [eax+00000020h]", 0x66, 0x0F, 0x7D, 0x40, 0x20 );
    // VEX.NDS.128.66.0F 7D /r VHSUBPD xmm1,xmm2,xmm3/m128
    // VEX.NDS.256.66.0F 7D /r VHSUBPD ymm1,ymm2,ymm3/m256
    FCML_I64( "vhsubpd ymm10,ymm14,ymmword ptr [r9+rax]", 0xC4, 0x41, 0x0D, 0x7D, 0x14, 0x01 );
    FCML_I32_D( "vhsubpd xmm2,xmm7,oword ptr [ecx+eax]", 0xC4, 0xC1, 0x41, 0x7D, 0x14, 0x01 );
    FCML_I32( "vhsubpd xmm2,xmm7,oword ptr [ecx+eax]", 0xc5, 0xc1, 0x7d, 0x14, 0x01 );
}

void fcml_tf_instruction_HSUBPS(void) {
    // F2 0F 7D /r HSUBPS xmm1, xmm2/m128
    FCML_I64( "hsubps xmm0,oword ptr [rax+0000000000000020h]", 0xF2, 0x0F, 0x7D, 0x40, 0x20 );
    FCML_I32( "hsubps xmm0,oword ptr [eax+00000020h]", 0xF2, 0x0F, 0x7D, 0x40, 0x20 );
    // VEX.NDS.128.F2.0F 7D /r VHSUBPS xmm1,xmm2,xmm3/m128
    // VEX.NDS.256.F2.0F 7D /r VHSUBPS ymm1,ymm2,ymm3/m256
    FCML_I64( "vhsubps ymm10,ymm14,ymmword ptr [r9+rax]", 0xC4, 0x41, 0x0F, 0x7D, 0x14, 0x01 );
    FCML_I32_D( "vhsubps xmm2,xmm7,oword ptr [ecx+eax]", 0xC4, 0xC1, 0x43, 0x7D, 0x14, 0x01 );
    FCML_I32( "vhsubps xmm2,xmm7,oword ptr [ecx+eax]", 0xc5, 0xc3, 0x7d, 0x14, 0x01 );
}

CU_TestInfo fctl_ti_instructions_h[] = {
    { "fcml_tf_instruction_HADDPD", fcml_tf_instruction_HADDPD },
    { "fcml_tf_instruction_HADDPS", fcml_tf_instruction_HADDPS },
    { "fcml_tf_instruction_HLT", fcml_tf_instruction_HLT },
    { "fcml_tf_instruction_HSUBPD", fcml_tf_instruction_HSUBPD },
    { "fcml_tf_instruction_HSUBPS", fcml_tf_instruction_HSUBPS },
    CU_TEST_INFO_NULL,
};

CU_SuiteInfo fctl_si_instructions_h[] = {
    { "suite-fctl_ti_instructions_h", fcml_tf_instructions_h_suite_init, fcml_tf_instructions_h_suite_cleanup, fctl_ti_instructions_h },
    CU_SUITE_INFO_NULL,
};
