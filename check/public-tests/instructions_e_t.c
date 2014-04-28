/*
 * instructions.c
 *
 *  Created on: 01-06-2013
 *      Author: tAs
 */

#include <fcml_assembler.h>
#include "instructions_e_t.h"
#include "instructions_base_t.h"

void fcml_tf_instructions_e_suite_init(void) {
}

void fcml_tf_instructions_e_suite_cleanup(void) {
}

void fcml_tf_instruction_EMMS(void) {
    FCML_I3264( "emms", 0x0F, 0x77 );
    FCML_A64( "emms", 0x0f, 0x77 );
}

void fcml_tf_instruction_ENTER(void) {
    FCML_I32( "enter 0ffeeh,55h", 0xc8, 0xEE, 0xFF, 0x55 );
    FCML_I32( "enter 0ffeeh,55h", 0x66, 0xc8, 0xEE, 0xFF, 0x55 );
    FCML_I64( "enter 0ffeeh,55h", 0xc8, 0xEE, 0xFF, 0x55 );
    FCML_I64( "enter 0ffeeh,55h", 0x66, 0xc8, 0xEE, 0xFF, 0x55 );
    FCML_I64_D( "enter 0ffeeh,55h", 0x66, 0x48, 0xc8, 0xEE, 0xFF, 0x55 );
    FCML_I32( "enter 0ffeeh,00h", 0xc8, 0xEE, 0xFF, 0x00 );
    FCML_I32( "enter 0ffeeh,01h", 0xc8, 0xEE, 0xFF, 0x01 );
    /* GAS*/
    FCML_A64( "enter $0xffee,$0x55", 0xc8, 0xee, 0xff, 0x55 );
    FCML_A64( "enter $0xffee,$0x00", 0xc8, 0xee, 0xff, 0x00 );
    FCML_A64( "enter $0xffee,$0x01", 0xc8, 0xee, 0xff, 0x01 );
}

void fcml_tf_instruction_EXTRACTPS(void) {
    FCML_I64( "extractps dword ptr [rax+0000000000000020h],xmm0,50h", 0x66, 0x0F, 0x3A, 0x17, 0x40, 0x20, 0x50 );
    FCML_A64( "extractps $0x50,%xmm0,0x0000000000000020(%rax)", 0x66, 0x0f, 0x3a, 0x17, 0x40, 0x20, 0x50 );
    FCML_I32( "extractps dword ptr [eax+00000020h],xmm0,50h", 0x66, 0x0F, 0x3A, 0x17, 0x40, 0x20, 0x50 );
    /* VEX.128.66.0F3A 17 /r ib VEXTRACTPS r/m32, xmm1, int8*/
    FCML_I32( "vextractps dword ptr [ecx+eax],xmm2,20h", 0xC4, 0xE3, 0x79, 0x17, 0x14, 0x01, 0x20 );
    FCML_I64( "vextractps eax,xmm0,20h", 0xC4, 0xE3, 0x79, 0x17, 0xC0, 0x20 );
    FCML_A64( "vextractps $0x20,%xmm0,%eax", 0xc4, 0xe3, 0x79, 0x17, 0xc0, 0x20 );
}

void fcml_tf_instruction_EXTRQ(void) {
    /* EXTRQ xmm1,int8,int8 66 0F 78 /0 ib ib*/
    FCML_I32( "extrq xmm1,01h,02h", 0x66, 0x0F, 0x78, 0xC1, 0x01, 0x02 );
    FCML_I32( "extrq xmm2,01h,02h", 0x66, 0x0F, 0x78, 0xC2, 0x01, 0x02 );
    FCML_I64( "extrq xmm1,01h,02h", 0x66, 0x0F, 0x78, 0xC1, 0x01, 0x02 );
    FCML_I64( "extrq xmm2,01h,02h", 0x66, 0x0F, 0x78, 0xC2, 0x01, 0x02 );
    FCML_A64( "extrq $0x02,$0x01,%xmm1", 0x66, 0x0f, 0x78, 0xc1, 0x01, 0x02 );
    /* EXTRQ xmm1,xmm2 66 0F 79 /r*/
    FCML_I32( "extrq xmm0,xmm5", 0x66, 0x0F, 0x79, 0xC5 );
    FCML_I32( "extrq xmm4,xmm1", 0x66, 0x0F, 0x79, 0xE1 );
    FCML_I64( "extrq xmm0,xmm5", 0x66, 0x0F, 0x79, 0xC5 );
    FCML_I64( "extrq xmm4,xmm1", 0x66, 0x0F, 0x79, 0xE1 );
    FCML_A64( "extrq %xmm1,%xmm4", 0x66, 0x0f, 0x79, 0xe1 );
}

fcml_stf_test_case fctl_ti_instructions_e[] = {
	{ "fcml_tf_instruction_EMMS", fcml_tf_instruction_EMMS },
	{ "fcml_tf_instruction_ENTER", fcml_tf_instruction_ENTER },
	{ "fcml_tf_instruction_EXTRACTPS", fcml_tf_instruction_EXTRACTPS },
	{ "fcml_tf_instruction_EXTRQ", fcml_tf_instruction_EXTRQ },
	FCML_STF_NULL_TEST
};

fcml_stf_test_suite fctl_si_instructions_e = {
	"suite-fctl_ti_instructions_e", fcml_tf_instructions_e_suite_init, fcml_tf_instructions_e_suite_cleanup, fctl_ti_instructions_e
};
