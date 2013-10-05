/*
 * instructions.c
 *
 *  Created on: 01-06-2013
 *      Author: tAs
 */

#include "fcml_env.h"
#include "fcml_assembler.h"
#include "instructions_s_t.h"

int fcml_tf_instructions_s_suite_init(void) {
	return 0;
}

int fcml_tf_instructions_s_suite_cleanup(void) {
	return 0;
}

void fcml_tf_instruction_SAHF(void) {
    // 9E SAHF
    FCML_I3264( "sahf", 0x9E );
}

void fcml_tf_instruction_SHL(void) {
    // D0 /4 SHL r/m8, 1 M1 Valid Valid Multiply r/m8 by 2, once.
    // REX + D0 /4 SHL r/m8**, 1 M1 Valid N.E. Multiply r/m8 by 2, once.
    FCML_I32_M( "shl byte ptr [eax],01h", 2, FCML_MI( 0xc0, 0x20, 0x01 ), FCML_MI( 0xd0, 0x20 ) );
    FCML_I32_M( "shl al,01h", 2, FCML_MI( 0xc0, 0xe0, 0x01 ), FCML_MI( 0xd0, 0xe0 ) );
    FCML_I64_D( "shl al,01h", 0x48, 0xD0, 0xE0 );
    // D2 /4 SHL r/m8, CL MC Valid Valid Multiply r/m8 by 2, CL times.
    // REX + D2 /4 SHL r/m8**, CL MC Valid N.E. Multiply r/m8 by 2, CL times.
    FCML_I32( "shl byte ptr [eax],cl", 0xD2, 0x20 );
    FCML_I32( "shl al,cl", 0xD2, 0xE0 );
    FCML_I64_D( "shl al,cl", 0x48, 0xD2, 0xE0 );
    // C0 /4 ib SHL r/m8, imm8 MI Valid Valid Multiply r/m8 by 2, imm8 times.
    // REX + C0 /4 ib SHL r/m8**, imm8 MI Valid N.E. Multiply r/m8 by 2, imm8 times.
    FCML_I32( "shl byte ptr [eax],0ffh", 0xC0, 0x20, 0xFF );
    FCML_I32( "shl al,0ffh", 0xC0, 0xE0, 0xFF );
    FCML_I64_D( "shl al,0ffh", 0x48, 0xC0, 0xE0, 0xFF );
    // D1 /4 SHL r/m16,1 M1 Valid Valid Multiply r/m16 by 2, once.
    // D1 /4 SHL r/m32,1 M1 Valid Valid Multiply r/m32 by 2, once.
    // REX.W + D1 /4 SHL r/m64,1 M1 Valid N.E. Multiply r/m64 by 2, once.
    FCML_I32_M( "shl dword ptr [eax],01h", 2, FCML_MI( 0xc1, 0x20, 0x01 ), FCML_MI( 0xd1, 0x20 ) );
    FCML_I32_M( "shl eax,01h", 2, FCML_MI( 0xc1, 0xe0, 0x01 ), FCML_MI( 0xd1, 0xe0 ) );
    FCML_I64_M( "shl rax,01h", 2, FCML_MI( 0x48, 0xc1, 0xe0, 0x01 ), FCML_MI( 0x48, 0xd1, 0xe0 ) );
    // D3 /4 SHL r/m16, CL MC Valid Valid Multiply r/m16 by 2, CL times.
    // D3 /4 SHL r/m32, CL MC Valid Valid Multiply r/m32 by 2, CL times.
    // REX.W + D3 /4 SHL r/m64, CL MC Valid N.E. Multiply r/m64 by 2, CL times.
    FCML_I32( "shl dword ptr [eax],cl", 0xD3, 0x20 );
    FCML_I32( "shl eax,cl", 0xD3, 0xE0 );
    FCML_I64( "shl rax,cl", 0x48, 0xD3, 0xE0 );
    // C1 /4 ib SHL r/m16, imm8 MI Valid Valid Multiply r/m16 by 2, imm8 times.
    // C1 /4 ib SHL r/m32, imm8 MI Valid Valid Multiply r/m32 by 2, imm8 times.
    // REX.W + C1 /4 ib SHL r/m64, imm8 MI Valid N.E. Multiply r/m64 by 2, imm8 times.
    FCML_I32( "shl dword ptr [eax],0ffh", 0xC1, 0x20, 0xff );
    FCML_I32( "shl eax,0ffh", 0xC1, 0xE0, 0xff );
    FCML_I64( "shl rax,0ffh", 0x48, 0xC1, 0xE0, 0xff );
}

void fcml_tf_instruction_SAL(void) {
    // D0 /4 SAL r/m8, 1 M1 Valid Valid Multiply r/m8 by 2, once.
    // REX + D0 /4 SAL r/m8**, 1 M1 Valid N.E. Multiply r/m8 by 2, once.
    FCML_I32_M_A( "sal byte ptr [eax],01h", 2, FCML_MI( 0xc0, 0x20, 0x01 ), FCML_MI( 0xd0, 0x20 ) );
    FCML_I32_M_A( "sal al,01h", 2, FCML_MI( 0xc0, 0xe0, 0x01 ), FCML_MI( 0xd0, 0xe0 ) );
    // D2 /4 SAL r/m8, CL MC Valid Valid Multiply r/m8 by 2, CL times.
    // REX + D2 /4 SAL r/m8**, CL MC Valid N.E. Multiply r/m8 by 2, CL times.
    FCML_I32_A( "sal byte ptr [eax],cl", 0xD2, 0x20 );
    FCML_I32_A( "sal al,cl", 0xD2, 0xE0 );
    // C0 /4 ib SAL r/m8, imm8 MI Valid Valid Multiply r/m8 by 2, imm8 times.
    // REX + C0 /4 ib SAL r/m8**, imm8 MI Valid N.E. Multiply r/m8 by 2, imm8 times.
    FCML_I32_A( "sal byte ptr [eax],0ffh", 0xC0, 0x20, 0xFF );
    FCML_I32_A( "sal al,0ffh", 0xC0, 0xE0, 0xFF );
    // D1 /4 SAL r/m16,1 M1 Valid Valid Multiply r/m16 by 2, once.
    // D1 /4 SAL r/m32,1 M1 Valid Valid Multiply r/m32 by 2, once.
    // REX.W + D1 /4 SAL r/m64,1 M1 Valid N.E. Multiply r/m64 by 2, once.
    FCML_I32_M_A( "sal dword ptr [eax],01h", 2, FCML_MI( 0xc1, 0x20, 0x01 ), FCML_MI( 0xd1, 0x20 ) );
    FCML_I32_M_A( "sal eax,01h", 2, FCML_MI( 0xc1, 0xe0, 0x01 ), FCML_MI( 0xd1, 0xe0 ) );
    FCML_I64_M_A( "sal rax,01h", 2, FCML_MI( 0x48, 0xc1, 0xe0, 0x01 ), FCML_MI( 0x48, 0xd1, 0xe0 ) );
    // D3 /4 SAL r/m16, CL MC Valid Valid Multiply r/m16 by 2, CL times.
    // D3 /4 SAL r/m32, CL MC Valid Valid Multiply r/m32 by 2, CL times.
    // REX.W + D3 /4 SAL r/m64, CL MC Valid N.E. Multiply r/m64 by 2, CL times.
    FCML_I32_A( "sal dword ptr [eax],cl", 0xD3, 0x20 );
    FCML_I32_A( "sal eax,cl", 0xD3, 0xE0 );
    FCML_I64_A( "sal rax,cl", 0x48, 0xD3, 0xE0 );
    // C1 /4 ib SAL r/m16, imm8 MI Valid Valid Multiply r/m16 by 2, imm8 times.
    // C1 /4 ib SAL r/m32, imm8 MI Valid Valid Multiply r/m32 by 2, imm8 times.
    // REX.W + C1 /4 ib SAL r/m64, imm8 MI Valid N.E. Multiply r/m64 by 2, imm8 times.
    FCML_I32_A( "sal dword ptr [eax],0ffh", 0xC1, 0x20, 0xff );
    FCML_I32_A( "sal eax,0ffh", 0xC1, 0xE0, 0xff );
    FCML_I64_A( "sal rax,0ffh", 0x48, 0xC1, 0xE0, 0xff );
}

CU_TestInfo fctl_ti_instructions_s[] = {
    { "fcml_tf_instruction_SAHF", fcml_tf_instruction_SAHF },
    { "fcml_tf_instruction_SHL", fcml_tf_instruction_SHL },
    { "fcml_tf_instruction_SAL", fcml_tf_instruction_SAL },
    CU_TEST_INFO_NULL,
};

CU_SuiteInfo fctl_si_instructions_s[] = {
    { "suite-fctl_ti_instructions_s", fcml_tf_instructions_s_suite_init, fcml_tf_instructions_s_suite_cleanup, fctl_ti_instructions_s },
    CU_SUITE_INFO_NULL,
};
