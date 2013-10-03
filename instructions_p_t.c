/*
 * instructions.c
 *
 *  Created on: 01-06-2013
 *      Author: tAs
 */

#include "fcml_env.h"
#include "fcml_assembler.h"
#include "instructions_n_t.h"

int fcml_tf_instructions_p_suite_init(void) {
	return 0;
}

int fcml_tf_instructions_p_suite_cleanup(void) {
	return 0;
}

void fcml_tf_instruction_PABS(void) {
    // 0F 38 1C /r1 PABSB mm1,mm2/m64
    // 0F 38 1D /r1 PABSW mm1,mm2/m64
    // 0F 38 1E /r1 PABSD mm1,mm2/m64
    FCML_I64( "pabsb mm0,mmword ptr [rax]", 0x0F, 0x38, 0x1C, 0x00 );
    FCML_I32( "pabsb mm0,mm1", 0x0F, 0x38, 0x1C, 0xC1 );
    FCML_I64( "pabsw mm0,mmword ptr [rax]", 0x0F, 0x38, 0x1D, 0x00 );
    FCML_I32( "pabsw mm0,mm1", 0x0F, 0x38, 0x1D, 0xC1 );
    FCML_I64( "pabsd mm0,mmword ptr [rax]", 0x0F, 0x38, 0x1E, 0x00 );
    FCML_I32( "pabsd mm0,mm1", 0x0F, 0x38, 0x1E, 0xC1 );
    // 66 0F 38 1C /r PABSB xmm1,xmm2/m128
    // 66 0F 38 1D /r PABSW xmm1,xmm2/m128
    // 66 0F 38 1E /r PABSD xmm1,xmm2/m128
    FCML_I64( "pabsb xmm0,xmmword ptr [rax]", 0x66, 0x0F, 0x38, 0x1C, 0x00 );
    FCML_I32( "pabsb xmm0,xmm1", 0x66, 0x0F, 0x38, 0x1C, 0xC1 );
    FCML_I64( "pabsw xmm0,xmmword ptr [rax]", 0x66, 0x0F, 0x38, 0x1D, 0x00 );
    FCML_I32( "pabsw xmm0,xmm1", 0x66, 0x0F, 0x38, 0x1D, 0xC1 );
    FCML_I64( "pabsd xmm0,xmmword ptr [rax]", 0x66, 0x0F, 0x38, 0x1E, 0x00 );
    FCML_I32( "pabsd xmm0,xmm1", 0x66, 0x0F, 0x38, 0x1E, 0xC1 );
    // VEX.128.66.0F38 1C /r VPABSB xmm1,xmm2/m128
    // VEX.128.66.0F38 1D /r VPABSW xmm1,xmm2/m128
    // VEX.128.66.0F38 1E /r VPABSD xmm1,xmm2/m128
    FCML_I64( "vpabsb xmm0,xmmword ptr [rax]", 0xC4, 0xE2, 0x79, 0x1C, 0x00 );
    FCML_I32( "vpabsb xmm0,xmm1", 0xC4, 0xE2, 0x79, 0x1C, 0xC1 );
    FCML_I64( "vpabsw xmm0,xmmword ptr [rax]", 0xC4, 0xE2, 0x79, 0x1D, 0x00 );
    FCML_I32( "vpabsw xmm0,xmm1", 0xC4, 0xE2, 0x79, 0x1D, 0xC1 );
    FCML_I64( "vpabsd xmm0,xmmword ptr [rax]", 0xC4, 0xE2, 0x79, 0x1E, 0x00 );
    FCML_I32( "vpabsd xmm0,xmm1", 0xC4, 0xE2, 0x79, 0x1E, 0xC1 );
    // VEX.256.66.0F38.WIG 1C /r VPABSB ymm1, ymm2/m256
    // VEX.256.66.0F38.WIG 1D /r VPABSW ymm1, ymm2/m256
    // VEX.256.66.0F38.WIG 1E /r VPABSD ymm1, ymm2/m256
    FCML_I64( "vpabsb ymm0,ymmword ptr [rax]", 0xC4, 0xE2, 0x7D, 0x1C, 0x00 );
    FCML_I32( "vpabsb ymm0,ymm1", 0xC4, 0xE2, 0x7D, 0x1C, 0xC1 );
    FCML_I64( "vpabsw ymm0,ymmword ptr [rax]", 0xC4, 0xE2, 0x7D, 0x1D, 0x00 );
    FCML_I32( "vpabsw ymm0,ymm1", 0xC4, 0xE2, 0x7D, 0x1D, 0xC1 );
    FCML_I64( "vpabsd ymm0,ymmword ptr [rax]", 0xC4, 0xE2, 0x7D, 0x1E, 0x00 );
    FCML_I32( "vpabsd ymm0,ymm1", 0xC4, 0xE2, 0x7D, 0x1E, 0xC1 );
}

CU_TestInfo fctl_ti_instructions_p[] = {
    { "fcml_tf_instruction_PABS", fcml_tf_instruction_PABS },
    CU_TEST_INFO_NULL,
};

CU_SuiteInfo fctl_si_instructions_p[] = {
    { "suite-fctl_ti_instructions_p", fcml_tf_instructions_p_suite_init, fcml_tf_instructions_p_suite_cleanup, fctl_ti_instructions_p },
    CU_SUITE_INFO_NULL,
};
