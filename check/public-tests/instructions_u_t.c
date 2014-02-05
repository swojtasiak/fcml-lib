/*
 * instructions.c
 *
 *  Created on: 01-06-2013
 *      Author: tAs
 */

#include <fcml_assembler.h>
#include "instructions_u_t.h"
#include "instructions_base_t.h"

void fcml_tf_instructions_u_suite_init(void) {
}

void fcml_tf_instructions_u_suite_cleanup(void) {
}

void fcml_tf_instruction_UCOMISD(void) {
    /* 66 0F 2E /r UCOMISD xmm1,xmm2/m64 RM V/V SSE2 Compares (unordered) the low doubleprecision floating-point values in xmm1 and xmm2/m64 and set the EFLAGS accordingly.*/
    FCML_I32( "ucomisd xmm2,mmword ptr [ecx+eax]", 0x66, 0x0F, 0x2E, 0x14, 0x01 );
    FCML_I64( "ucomisd xmm2,mmword ptr [rcx+rax]", 0x66, 0x0F, 0x2E, 0x14, 0x01 );
    FCML_I64( "ucomisd xmm0,xmm0", 0x66, 0x0F, 0x2E, 0xC0 );
    /* VEX.LIG.66.0F.WIG 2E /r VUCOMISD xmm1,xmm2/m64 RM V/V AVX Compare low double precision floating-point values in xmm1 and xmm2/mem64 and set the EFLAGS flags accordingly.*/
    FCML_I32( "vucomisd xmm0,mmword ptr [eax]", 0xc5, 0xf9, 0x2e, 0x00 );
    FCML_I64( "vucomisd xmm0,xmm1", 0xc5, 0xf9, 0x2e, 0xc1 );
    /* GAS*/
    FCML_A64( "ucomisd (%rcx,%rax),%xmm2", 0x66, 0x0f, 0x2e, 0x14, 0x01 );
    FCML_A64( "ucomisd (%rcx,%rax),%xmm2", 0x66, 0x0f, 0x2e, 0x14, 0x01 );
    FCML_A64( "ucomisd %xmm0,%xmm0", 0x66, 0x0f, 0x2e, 0xc0 );
    FCML_A64( "vucomisd (%rax),%xmm0", 0xc5, 0xf9, 0x2e, 0x00 );
    FCML_A64( "vucomisd %xmm1,%xmm0", 0xc5, 0xf9, 0x2e, 0xc1 );
}

void fcml_tf_instruction_UCOMISS(void) {
    /* 0F 2E /r UCOMISS xmm1,xmm2/m32 RM V/V SSE Compare lower single-precision floating-point value in xmm1 register with lower singleprecision floating-point value in xmm2/mem and set the status flags accordingly.*/
    FCML_I32( "ucomiss xmm2,dword ptr [ecx+eax]", 0x0F, 0x2E, 0x14, 0x01 );
    FCML_I64( "ucomiss xmm2,dword ptr [rcx+rax]", 0x0F, 0x2E, 0x14, 0x01 );
    FCML_I64( "ucomiss xmm0,xmm0", 0x0F, 0x2E, 0xC0 );
    /* VEX.LIG.0F.WIG 2E /r VUCOMISS xmm1,xmm2/m32 RM V/V AVX Compare low single precision floating-point values in xmm1 and xmm2/mem32 and set the EFLAGS flags accordingly.*/
    FCML_I32( "vucomiss xmm0,dword ptr [eax]", 0xc5, 0xf8, 0x2e, 0x00 );
    FCML_I64( "vucomiss xmm0,xmm1", 0xc5, 0xf8, 0x2e, 0xc1 );
    /* GAS*/
    FCML_A64( "ucomiss (%rcx,%rax),%xmm2", 0x0f, 0x2e, 0x14, 0x01 );
    FCML_A64( "ucomiss (%rcx,%rax),%xmm2", 0x0f, 0x2e, 0x14, 0x01 );
    FCML_A64( "ucomiss %xmm0,%xmm0", 0x0f, 0x2e, 0xc0 );
    FCML_A64( "vucomiss (%rax),%xmm0", 0xc5, 0xf8, 0x2e, 0x00 );
    FCML_A64( "vucomiss %xmm1,%xmm0", 0xc5, 0xf8, 0x2e, 0xc1 );
}

void fcml_tf_instruction_UD2(void) {
    /* 0F 0B UD2 NP Valid Valid Raise invalid opcode exception.*/
    FCML_I3264( "ud2", 0x0F, 0x0B );
    FCML_A64( "ud2", 0x0f, 0x0b );
}

void fcml_tf_instruction_UNPCKHPD(void) {
    /* 66 0F 15 /r UNPCKHPD xmm1,xmm2/m128*/
    FCML_I32( "unpckhpd xmm0,xmmword ptr [eax]", 0x66, 0x0F, 0x15, 0x00 );
    FCML_I32( "unpckhpd xmm0,xmm0",  0x66, 0x0F, 0x15, 0xC0 );
    FCML_I64( "unpckhpd xmm0,xmmword ptr [rax]", 0x66, 0x0F, 0x15, 0x00 );
    /* VEX.NDS.128.66.0F.WIG 15 /r VUNPCKHPD xmm1,xmm2,xmm3/m128*/
    /* VEX.NDS.256.66.0F.WIG 15 /r VUNPCKHPD ymm1,ymm2,ymm3/m256*/
    FCML_I32( "vunpckhpd xmm0,xmm6,xmmword ptr [eax]", 0xc5, 0xc9, 0x15, 0x00 );
    FCML_I32( "vunpckhpd xmm0,xmm6,xmm0", 0xc5, 0xc9, 0x15, 0xc0 );
    FCML_I64( "vunpckhpd xmm0,xmm6,xmmword ptr [rax]", 0xc5, 0xc9, 0x15, 0x00 );
    FCML_I64( "vunpckhpd ymm0,ymm6,ymmword ptr [rax]", 0xc5, 0xcd, 0x15, 0x00 );
    /* GAS*/
    FCML_A64( "unpckhpd (%rax),%xmm0", 0x66, 0x0f, 0x15, 0x00 );
    FCML_A64( "unpckhpd %xmm0,%xmm0", 0x66, 0x0f, 0x15, 0xc0 );
    FCML_A64( "vunpckhpd %xmm0,%xmm6,%xmm0", 0xc5, 0xc9, 0x15, 0xc0 );
    FCML_A64( "vunpckhpd (%rax),%xmm6,%xmm0", 0xc5, 0xc9, 0x15, 0x00 );
    FCML_A64( "vunpckhpd (%rax),%ymm6,%ymm0", 0xc5, 0xcd, 0x15, 0x00 );
}

void fcml_tf_instruction_UNPCKHPS(void) {
    /* 0F 15 /r UNPCKHPS xmm1,xmm2/m128*/
    FCML_I32( "unpckhps xmm0,xmmword ptr [eax]", 0x0F, 0x15, 0x00 );
    FCML_I32( "unpckhps xmm0,xmm0", 0x0F, 0x15, 0xC0 );
    FCML_I64( "unpckhps xmm0,xmmword ptr [rax]", 0x0F, 0x15, 0x00 );
    /* VEX.NDS.128.0F.WIG 15 /r VUNPCKHPS xmm1,xmm2,xmm3/m128*/
    /* VEX.NDS.256.0F.WIG 15 /r VUNPCKHPS ymm1,ymm2,ymm3/m256*/
    FCML_I32( "vunpckhps xmm0,xmm6,xmmword ptr [eax]", 0xc5, 0xc8, 0x15, 0x00 );
    FCML_I32( "vunpckhps xmm0,xmm6,xmm0", 0xc5, 0xc8, 0x15, 0xc0 );
    FCML_I64( "vunpckhps xmm0,xmm6,xmmword ptr [rax]", 0xc5, 0xc8, 0x15, 0x00 );
    /* GAS*/
    FCML_A64( "unpckhps (%rax),%xmm0", 0x0f, 0x15, 0x00 );
    FCML_A64( "unpckhps %xmm0,%xmm0", 0x0f, 0x15, 0xc0 );
    FCML_A64( "vunpckhps (%rax),%xmm6,%xmm0", 0xc5, 0xc8, 0x15, 0x00 );
    FCML_A64( "vunpckhps %xmm0,%xmm6,%xmm0", 0xc5, 0xc8, 0x15, 0xc0 );
}

void fcml_tf_instruction_UNPCKLPD(void) {
    /* 66 0F 14 /r UNPCKLPD xmm1,xmm2/m128*/
    FCML_I32( "unpcklpd xmm0,xmmword ptr [eax]", 0x66, 0x0F, 0x14, 0x00 );
    FCML_I32( "unpcklpd xmm0,xmm0",  0x66, 0x0F, 0x14, 0xC0 );
    FCML_I64( "unpcklpd xmm0,xmmword ptr [rax]", 0x66, 0x0F, 0x14, 0x00 );
    /* VEX.NDS.128.66.0F.WIG 14 /r VUNPCKLPD xmm1,xmm2,xmm3/m128*/
    /* VEX.NDS.256.66.0F.WIG 14 /r VUNPCKLPD ymm1,ymm2,ymm3/m256*/
    FCML_I32( "vunpcklpd xmm0,xmm6,xmmword ptr [eax]", 0xc5, 0xc9, 0x14, 0x00 );
    FCML_I32( "vunpcklpd xmm0,xmm6,xmm0", 0xc5, 0xc9, 0x14, 0xc0 );
    FCML_I64( "vunpcklpd xmm0,xmm6,xmmword ptr [rax]", 0xc5, 0xc9, 0x14, 0x00 );
    /* GAS*/
    FCML_A64( "unpcklpd %xmm0,%xmm0", 0x66, 0x0f, 0x14, 0xc0 );
    FCML_A64( "unpcklpd (%rax),%xmm0", 0x66, 0x0f, 0x14, 0x00 );
    FCML_A64( "vunpcklpd %xmm0,%xmm6,%xmm0", 0xc5, 0xc9, 0x14, 0xc0 );
    FCML_A64( "vunpcklpd (%rax),%xmm6,%xmm0", 0xc5, 0xc9, 0x14, 0x00 );
}

void fcml_tf_instruction_UNPCKLPS(void) {
    /* 0F 14 /r UNPCKLPS xmm1,xmm2/m128*/
    FCML_I32( "unpcklps xmm0,xmmword ptr [eax]", 0x0F, 0x14, 0x00 );
    FCML_I32( "unpcklps xmm0,xmm0", 0x0F, 0x14, 0xC0 );
    FCML_I64( "unpcklps xmm0,xmmword ptr [rax]", 0x0F, 0x14, 0x00 );
    /* VEX.NDS.128.0F.WIG 14 /r VUNPCKLPS xmm1,xmm2,xmm3/m128*/
    /* VEX.NDS.256.0F.WIG 14 /r VUNPCKLPS ymm1,ymm2,ymm3/m256*/
    FCML_I32( "vunpcklps xmm0,xmm6,xmmword ptr [eax]", 0xc5, 0xc8, 0x14, 0x00 );
    FCML_I32( "vunpcklps xmm0,xmm6,xmm0", 0xc5, 0xc8, 0x14, 0xc0 );
    FCML_I64( "vunpcklps xmm0,xmm6,xmmword ptr [rax]", 0xc5, 0xc8, 0x14, 0x00 );
    /* GAS*/
    FCML_A64( "unpcklps %xmm0,%xmm0", 0x0f, 0x14, 0xc0 );
    FCML_A64( "unpcklps (%rax),%xmm0", 0x0f, 0x14, 0x00 );
    FCML_A64( "vunpcklps %xmm0,%xmm6,%xmm0", 0xc5, 0xc8, 0x14, 0xc0 );
    FCML_A64( "vunpcklps (%rax),%xmm6,%xmm0", 0xc5, 0xc8, 0x14, 0x00 );
}

fcml_stf_test_case fctl_ti_instructions_u[] = {
	{ "fcml_tf_instruction_UCOMISD", fcml_tf_instruction_UCOMISD },
	{ "fcml_tf_instruction_UCOMISS", fcml_tf_instruction_UCOMISS },
	{ "fcml_tf_instruction_UD2", fcml_tf_instruction_UD2 },
	{ "fcml_tf_instruction_UNPCKHPD", fcml_tf_instruction_UNPCKHPD },
	{ "fcml_tf_instruction_UNPCKHPS", fcml_tf_instruction_UNPCKHPS },
	{ "fcml_tf_instruction_UNPCKLPD", fcml_tf_instruction_UNPCKLPD },
	{ "fcml_tf_instruction_UNPCKLPS", fcml_tf_instruction_UNPCKLPS },
	FCML_STF_NULL_TEST
};

fcml_stf_test_suite fctl_si_instructions_u = {
	"suite-fctl_ti_instructions_u", fcml_tf_instructions_u_suite_init, fcml_tf_instructions_u_suite_cleanup, fctl_ti_instructions_u
};


