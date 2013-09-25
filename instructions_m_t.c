/*
 * instructions.c
 *
 *  Created on: 01-06-2013
 *      Author: tAs
 */

#include "fcml_env.h"
#include "fcml_assembler.h"
#include "instructions_i_t.h"

int fcml_tf_instructions_m_suite_init(void) {
	return 0;
}

int fcml_tf_instructions_m_suite_cleanup(void) {
	return 0;
}

void fcml_tf_instruction_MASKMOVQ(void) {
    FCML_I64( "maskmovq mm3,mm0", 0x0F, 0xF7, 0xD8 );
    FCML_I32( "maskmovq mm4,mm0", 0x0F, 0xF7, 0xE0 );
    FCML_I32_FAILED( "FAIL", 0x0F, 0xF7, 0x40, 0x20 );
    // VEX.128.66.0F F7 /r VMASKMOVDQU xmm1,xmm2
    FCML_I3264( "vmaskmovdqu xmm3,xmm0", 0xc5, 0xf9, 0xf7, 0xd8 );
}

void fcml_tf_instruction_MASKMOVDQU(void) {
    FCML_I64( "maskmovdqu xmm3,xmm0", 0x66, 0x0F, 0xF7, 0xD8 );
    FCML_I32( "maskmovdqu xmm4,xmm0", 0x66, 0x0F, 0xF7, 0xE0 );
    FCML_I32_FAILED( "FAIL", 0x66, 0x0F, 0xF7, 0x40, 0x20 );
}

void fcml_tf_instruction_MAXPD(void) {
    FCML_I64( "maxpd xmm0,oword ptr [rax+0000000000000020h]", 0x66, 0x0F, 0x5F, 0x40, 0x20 );
    FCML_I32( "maxpd xmm0,xmm2", 0x66, 0x0F, 0x5F, 0xC2 );
    FCML_I32( "maxpd xmm0,oword ptr [eax+00000020h]", 0x66, 0x0F, 0x5F, 0x40, 0x20 );
    // VEX.NDS.128.66.0F 5F /r VMAXPD xmm1,xmm2,xmm3/m128
    // VEX.NDS.256.66.0F 5F /r VMAXPD ymm1,ymm2,ymm3/m256
    FCML_I64( "vmaxpd xmm3,xmm0,xmm0", 0xc5, 0xf9, 0x5f, 0xd8 );
    FCML_I32( "vmaxpd ymm3,ymm0,ymm0", 0xc5, 0xfd, 0x5f, 0xd8 );
    FCML_I32( "vmaxpd ymm3,ymm3,ymmword ptr [eax]", 0xc5, 0xe5, 0x5f, 0x18 );
}

void fcml_tf_instruction_MAXPS(void) {
    FCML_I64( "maxps xmm0,oword ptr [rax+0000000000000020h]", 0x0F, 0x5F, 0x40, 0x20 );
    FCML_I32( "maxps xmm0,xmm2", 0x0F, 0x5F, 0xC2 );
    FCML_I32( "maxps xmm0,oword ptr [eax+00000020h]", 0x0F, 0x5F, 0x40, 0x20 );
    // VEX.NDS.128.0F 5F /r VMAXPS xmm1,xmm2,xmm3/m128
    // VEX.NDS.256.0F 5F /r VMAXPS ymm1,ymm2,ymm3/m256
    FCML_I64( "vmaxps xmm3,xmm0,xmm0", 0xc5, 0xf8, 0x5f, 0xd8 );
    FCML_I32( "vmaxps ymm3,ymm0,ymm0", 0xc5, 0xfc, 0x5f, 0xd8 );
    FCML_I32( "vmaxps ymm3,ymm3,ymmword ptr [eax]", 0xc5, 0xe4, 0x5f, 0x18 );
}

void fcml_tf_instruction_MAXSD(void) {
    FCML_I64( "maxsd xmm0,qword ptr [rax+0000000000000020h]", 0xF2, 0x0F, 0x5F, 0x40, 0x20 );
    FCML_I32( "maxsd xmm0,xmm2", 0xF2, 0x0F, 0x5F, 0xC2 );
    FCML_I32( "maxsd xmm0,qword ptr [eax+00000020h]", 0xF2, 0x0F, 0x5F, 0x40, 0x20 );
    // VEX.NDS.128.F2.0F 5F /r VMAXSD xmm1,xmm2,xmm3/m64
    FCML_I64( "vmaxsd xmm3,xmm3,xmm0", 0xc5, 0xe3, 0x5f, 0xd8 );
    FCML_I32( "vmaxsd xmm3,xmm7,xmm0", 0xc5, 0xc3, 0x5f, 0xd8 );
    FCML_I32( "vmaxsd xmm3,xmm0,qword ptr [eax]", 0xc5, 0xfb, 0x5f, 0x18 );
}

void fcml_tf_instruction_MAXSS(void) {
    FCML_I64( "maxss xmm0,dword ptr [rax+0000000000000020h]", 0xF3, 0x0F, 0x5F, 0x40, 0x20 );
    FCML_I32( "maxss xmm0,xmm2", 0xF3, 0x0F, 0x5F, 0xC2 );
    FCML_I32( "maxss xmm0,dword ptr [eax+00000020h]", 0xF3, 0x0F, 0x5F, 0x40, 0x20 );
    // VEX.NDS.128.F3.0F 5F /r VMAXSS xmm1, xmm2, xmm3/m32
    FCML_I64( "vmaxss xmm3,xmm3,xmm0", 0xc5, 0xe2, 0x5f, 0xd8 );
    FCML_I32( "vmaxss xmm3,xmm7,xmm0", 0xc5, 0xc2, 0x5f, 0xd8 );
    FCML_I32( "vmaxss xmm3,xmm0,dword ptr [eax]", 0xc5, 0xfa, 0x5f, 0x18 );
}

void fcml_tf_instruction_MFENCE(void) {
    FCML_I3264( "mfence", 0x0F, 0xAE, 0xF0 );
}

void fcml_tf_instruction_MINPD(void) {
    FCML_I64( "minpd xmm0,oword ptr [rax+0000000000000020h]", 0x66, 0x0F, 0x5D, 0x40, 0x20 );
    FCML_I32( "minpd xmm0,xmm2", 0x66, 0x0F, 0x5D, 0xC2 );
    FCML_I32( "minpd xmm0,oword ptr [eax+00000020h]", 0x66, 0x0F, 0x5D, 0x40, 0x20 );
    // VEX.NDS.128.66.0F 5D /r VMINPD xmm1,xmm2,xmm3/m128
    // VEX.NDS.256.66.0F 5D /r VMINPD ymm1,ymm2,ymm3/m256
    FCML_I64( "vminpd xmm3,xmm0,xmm0", 0xc5, 0xf9, 0x5d, 0xd8 );
    FCML_I32( "vminpd ymm3,ymm0,ymm0", 0xc5, 0xfd, 0x5d, 0xd8 );
    FCML_I32( "vminpd ymm3,ymm3,ymmword ptr [eax]", 0xc5, 0xe5, 0x5d, 0x18 );
}

void fcml_tf_instruction_MINPS(void) {
    FCML_I64( "minps xmm0,oword ptr [rax+0000000000000020h]", 0x0F, 0x5D, 0x40, 0x20 );
    FCML_I32( "minps xmm0,xmm2", 0x0F, 0x5D, 0xC2 );
    FCML_I32( "minps xmm0,oword ptr [eax+00000020h]", 0x0F, 0x5D, 0x40, 0x20 );
    // VEX.NDS.128.0F 5D /r VMINPS xmm1,xmm2,xmm3/m128
    // VEX.NDS.256.0F 5D /r VMINPS ymm1,ymm2,ymm3/m256
    FCML_I64( "vminps xmm3,xmm0,xmm0", 0xc5, 0xf8, 0x5d, 0xd8 );
    FCML_I32( "vminps ymm3,ymm0,ymm0", 0xc5, 0xfc, 0x5d, 0xd8 );
    FCML_I32( "vminps ymm3,ymm3,ymmword ptr [eax]", 0xc5, 0xe4, 0x5d, 0x18 );
}

void fcml_tf_instruction_MINSD(void) {
    FCML_I64( "minsd xmm0,qword ptr [rax+0000000000000020h]", 0xF2, 0x0F, 0x5D, 0x40, 0x20 );
    FCML_I32( "minsd xmm0,xmm2", 0xF2, 0x0F, 0x5D, 0xC2 );
    FCML_I32( "minsd xmm0,qword ptr [eax+00000020h]", 0xF2, 0x0F, 0x5D, 0x40, 0x20 );
    // VEX.NDS.128.F2.0F 5D /r VMINSD xmm1, xmm2, xmm3/m64
    FCML_I64( "vminsd xmm3,xmm0,xmm0", 0xc5, 0xfb, 0x5d, 0xd8 );
    FCML_I32( "vminsd xmm3,xmm0,xmm0", 0xc5, 0xfb, 0x5d, 0xd8 );
    FCML_I32( "vminsd xmm3,xmm3,qword ptr [eax]", 0xc5, 0xe3, 0x5d, 0x18 );
}

void fcml_tf_instruction_MINSS(void) {
    FCML_I64( "minss xmm0,dword ptr [rax+0000000000000020h]", 0xF3, 0x0F, 0x5D, 0x40, 0x20 );
    FCML_I32( "minss xmm0,xmm2", 0xF3, 0x0F, 0x5D, 0xC2 );
    FCML_I32( "minss xmm0,dword ptr [eax+00000020h]", 0xF3, 0x0F, 0x5D, 0x40, 0x20 );
    // VEX.NDS.128.F3.0F 5D /r VMINSS xmm1,xmm2,xmm3/m32
    FCML_I64( "vminss xmm3,xmm0,xmm0", 0xc5, 0xfa, 0x5d, 0xd8 );
    FCML_I32( "vminss xmm3,xmm0,xmm0", 0xc5, 0xfa, 0x5d, 0xd8 );
}

CU_TestInfo fctl_ti_instructions_m[] = {
    { "fcml_tf_instruction_MASKMOVQ", fcml_tf_instruction_MASKMOVQ },
    { "fcml_tf_instruction_MASKMOVDQU", fcml_tf_instruction_MASKMOVDQU },
    { "fcml_tf_instruction_MAXPD", fcml_tf_instruction_MAXPD },
    { "fcml_tf_instruction_MAXPS", fcml_tf_instruction_MAXPS },
    { "fcml_tf_instruction_MAXSD", fcml_tf_instruction_MAXSD },
    { "fcml_tf_instruction_MAXSS", fcml_tf_instruction_MAXSS },
    { "fcml_tf_instruction_MFENCE", fcml_tf_instruction_MFENCE },
    { "fcml_tf_instruction_MINPD", fcml_tf_instruction_MINPD },
    { "fcml_tf_instruction_MINPS", fcml_tf_instruction_MINPS },
    { "fcml_tf_instruction_MINSD", fcml_tf_instruction_MINSD },
    { "fcml_tf_instruction_MINSS", fcml_tf_instruction_MINSS },
    CU_TEST_INFO_NULL,
};

CU_SuiteInfo fctl_si_instructions_m[] = {
    { "suite-fctl_ti_instructions_m", fcml_tf_instructions_m_suite_init, fcml_tf_instructions_m_suite_cleanup, fctl_ti_instructions_m },
    CU_SUITE_INFO_NULL,
};
