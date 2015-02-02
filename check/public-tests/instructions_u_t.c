/*
 * FCML - Free Code Manipulation Library.
 * Copyright (C) 2010-2015 Slawomir Wojtasiak
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include <fcml_assembler.h>
#include "instructions_u_t.h"
#include "instructions_base_t.h"

fcml_bool fcml_tf_instructions_u_suite_init(void) {
	return FCML_TRUE;
}

fcml_bool fcml_tf_instructions_u_suite_cleanup(void) {
	return FCML_TRUE;
}

void fcml_tf_instruction_UCOMISD(void) {

    FCML_I32( "ucomisd xmm2,mmword ptr [ecx+eax]", 0x66, 0x0F, 0x2E, 0x14, 0x01 );
    FCML_I64( "ucomisd xmm2,mmword ptr [rcx+rax]", 0x66, 0x0F, 0x2E, 0x14, 0x01 );
    FCML_I64( "ucomisd xmm0,xmm0", 0x66, 0x0F, 0x2E, 0xC0 );

    FCML_I32( "vucomisd xmm0,mmword ptr [eax]", 0xc5, 0xf9, 0x2e, 0x00 );
    FCML_I64( "vucomisd xmm0,xmm1", 0xc5, 0xf9, 0x2e, 0xc1 );

    FCML_A64( "ucomisd (%rcx,%rax),%xmm2", 0x66, 0x0f, 0x2e, 0x14, 0x01 );
    FCML_A64( "ucomisd (%rcx,%rax),%xmm2", 0x66, 0x0f, 0x2e, 0x14, 0x01 );
    FCML_A64( "ucomisd %xmm0,%xmm0", 0x66, 0x0f, 0x2e, 0xc0 );
    FCML_A64( "vucomisd (%rax),%xmm0", 0xc5, 0xf9, 0x2e, 0x00 );
    FCML_A64( "vucomisd %xmm1,%xmm0", 0xc5, 0xf9, 0x2e, 0xc1 );
}

void fcml_tf_instruction_UCOMISS(void) {

    FCML_I32( "ucomiss xmm2,dword ptr [ecx+eax]", 0x0F, 0x2E, 0x14, 0x01 );
    FCML_I64( "ucomiss xmm2,dword ptr [rcx+rax]", 0x0F, 0x2E, 0x14, 0x01 );
    FCML_I64( "ucomiss xmm0,xmm0", 0x0F, 0x2E, 0xC0 );

    FCML_I32( "vucomiss xmm0,dword ptr [eax]", 0xc5, 0xf8, 0x2e, 0x00 );
    FCML_I64( "vucomiss xmm0,xmm1", 0xc5, 0xf8, 0x2e, 0xc1 );

    FCML_A64( "ucomiss (%rcx,%rax),%xmm2", 0x0f, 0x2e, 0x14, 0x01 );
    FCML_A64( "ucomiss (%rcx,%rax),%xmm2", 0x0f, 0x2e, 0x14, 0x01 );
    FCML_A64( "ucomiss %xmm0,%xmm0", 0x0f, 0x2e, 0xc0 );
    FCML_A64( "vucomiss (%rax),%xmm0", 0xc5, 0xf8, 0x2e, 0x00 );
    FCML_A64( "vucomiss %xmm1,%xmm0", 0xc5, 0xf8, 0x2e, 0xc1 );
}

void fcml_tf_instruction_UD2(void) {

    FCML_I3264( "ud2", 0x0F, 0x0B );
    FCML_A64( "ud2", 0x0f, 0x0b );
}

void fcml_tf_instruction_UNPCKHPD(void) {

    FCML_I32( "unpckhpd xmm0,xmmword ptr [eax]", 0x66, 0x0F, 0x15, 0x00 );
    FCML_I32( "unpckhpd xmm0,xmm0",  0x66, 0x0F, 0x15, 0xC0 );
    FCML_I64( "unpckhpd xmm0,xmmword ptr [rax]", 0x66, 0x0F, 0x15, 0x00 );

    FCML_I32( "vunpckhpd xmm0,xmm6,xmmword ptr [eax]", 0xc5, 0xc9, 0x15, 0x00 );
    FCML_I32( "vunpckhpd xmm0,xmm6,xmm0", 0xc5, 0xc9, 0x15, 0xc0 );
    FCML_I64( "vunpckhpd xmm0,xmm6,xmmword ptr [rax]", 0xc5, 0xc9, 0x15, 0x00 );
    FCML_I64( "vunpckhpd ymm0,ymm6,ymmword ptr [rax]", 0xc5, 0xcd, 0x15, 0x00 );

    FCML_A64( "unpckhpd (%rax),%xmm0", 0x66, 0x0f, 0x15, 0x00 );
    FCML_A64( "unpckhpd %xmm0,%xmm0", 0x66, 0x0f, 0x15, 0xc0 );
    FCML_A64( "vunpckhpd %xmm0,%xmm6,%xmm0", 0xc5, 0xc9, 0x15, 0xc0 );
    FCML_A64( "vunpckhpd (%rax),%xmm6,%xmm0", 0xc5, 0xc9, 0x15, 0x00 );
    FCML_A64( "vunpckhpd (%rax),%ymm6,%ymm0", 0xc5, 0xcd, 0x15, 0x00 );
}

void fcml_tf_instruction_UNPCKHPS(void) {

    FCML_I32( "unpckhps xmm0,xmmword ptr [eax]", 0x0F, 0x15, 0x00 );
    FCML_I32( "unpckhps xmm0,xmm0", 0x0F, 0x15, 0xC0 );
    FCML_I64( "unpckhps xmm0,xmmword ptr [rax]", 0x0F, 0x15, 0x00 );

    FCML_I32( "vunpckhps xmm0,xmm6,xmmword ptr [eax]", 0xc5, 0xc8, 0x15, 0x00 );
    FCML_I32( "vunpckhps xmm0,xmm6,xmm0", 0xc5, 0xc8, 0x15, 0xc0 );
    FCML_I64( "vunpckhps xmm0,xmm6,xmmword ptr [rax]", 0xc5, 0xc8, 0x15, 0x00 );

    FCML_A64( "unpckhps (%rax),%xmm0", 0x0f, 0x15, 0x00 );
    FCML_A64( "unpckhps %xmm0,%xmm0", 0x0f, 0x15, 0xc0 );
    FCML_A64( "vunpckhps (%rax),%xmm6,%xmm0", 0xc5, 0xc8, 0x15, 0x00 );
    FCML_A64( "vunpckhps %xmm0,%xmm6,%xmm0", 0xc5, 0xc8, 0x15, 0xc0 );
}

void fcml_tf_instruction_UNPCKLPD(void) {

    FCML_I32( "unpcklpd xmm0,xmmword ptr [eax]", 0x66, 0x0F, 0x14, 0x00 );
    FCML_I32( "unpcklpd xmm0,xmm0",  0x66, 0x0F, 0x14, 0xC0 );
    FCML_I64( "unpcklpd xmm0,xmmword ptr [rax]", 0x66, 0x0F, 0x14, 0x00 );

    FCML_I32( "vunpcklpd xmm0,xmm6,xmmword ptr [eax]", 0xc5, 0xc9, 0x14, 0x00 );
    FCML_I32( "vunpcklpd xmm0,xmm6,xmm0", 0xc5, 0xc9, 0x14, 0xc0 );
    FCML_I64( "vunpcklpd xmm0,xmm6,xmmword ptr [rax]", 0xc5, 0xc9, 0x14, 0x00 );

    FCML_A64( "unpcklpd %xmm0,%xmm0", 0x66, 0x0f, 0x14, 0xc0 );
    FCML_A64( "unpcklpd (%rax),%xmm0", 0x66, 0x0f, 0x14, 0x00 );
    FCML_A64( "vunpcklpd %xmm0,%xmm6,%xmm0", 0xc5, 0xc9, 0x14, 0xc0 );
    FCML_A64( "vunpcklpd (%rax),%xmm6,%xmm0", 0xc5, 0xc9, 0x14, 0x00 );
}

void fcml_tf_instruction_UNPCKLPS(void) {

    FCML_I32( "unpcklps xmm0,xmmword ptr [eax]", 0x0F, 0x14, 0x00 );
    FCML_I32( "unpcklps xmm0,xmm0", 0x0F, 0x14, 0xC0 );
    FCML_I64( "unpcklps xmm0,xmmword ptr [rax]", 0x0F, 0x14, 0x00 );

    FCML_I32( "vunpcklps xmm0,xmm6,xmmword ptr [eax]", 0xc5, 0xc8, 0x14, 0x00 );
    FCML_I32( "vunpcklps xmm0,xmm6,xmm0", 0xc5, 0xc8, 0x14, 0xc0 );
    FCML_I64( "vunpcklps xmm0,xmm6,xmmword ptr [rax]", 0xc5, 0xc8, 0x14, 0x00 );

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


