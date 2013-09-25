/*
 * instructions.c
 *
 *  Created on: 01-06-2013
 *      Author: tAs
 */

#include "fcml_env.h"
#include "fcml_assembler.h"
#include "instructions_i_t.h"

int fcml_tf_instructions_j_suite_init(void) {
	return 0;
}

int fcml_tf_instructions_j_suite_cleanup(void) {
	return 0;
}

void fcml_tf_instruction_JCXZ(void) {
    FCML_I64( "jrcxz 0000800000401001h", 0xe3, 0xff );
    FCML_I32( "jecxz 00401001h", 0xe3, 0xff );
    FCML_I64_D( "jrcxz 0000800000401002h", 0x66, 0xe3, 0xff );
    FCML_I64_D( "jecxz 0000800000401003h", 0x66, 0x67, 0xe3, 0xff );
    FCML_I64_D( "jrcxz 0000800000401002h", 0x48, 0xe3, 0xff );
    FCML_I32_D( "jcxz 00001003h", 0x66, 0x67, 0xe3, 0xff );
    FCML_I32_D( "jcxz 00401002h", 0x67, 0xe3, 0xff );
}

void fcml_tf_instruction_Jcc(void) {
    FCML_I64_D( "jnc 0000800000401002h", 0x66, 0x73, 0xff );
    FCML_I64_D( "jnc 0000800000401003h", 0x66, 0x67, 0x73, 0xff );
    FCML_I64_D( "jnc 0000800000401002h", 0x48, 0x73, 0xff );
    FCML_I64_M( "jnc 0000800000401001h", 2, FCML_MI( 0x73, 0xff ), FCML_MI( 0x0f, 0x83, 0xf7, 0xff, 0xff, 0xff ) );
    FCML_I32_D( "jnc 00001003h", 0x66, 0x67, 0x73, 0xff );
    FCML_I32_M( "jnc 00001002h", 2, FCML_MI( 0x66, 0x73, 0xff ), FCML_MI( 0x66, 0x0f, 0x83, 0xfd, 0xff ) );
    FCML_I32_D( "jnc 00401002h", 0x67, 0x73, 0xff );
    FCML_I32_M( "jnc 00401001h", 2, FCML_MI( 0x73, 0xff ), FCML_MI( 0x0f, 0x83, 0xfb, 0xff, 0xff, 0xff ) );
    // OSA 32
    FCML_I32( "jnc 003f3005h", 0x0f, 0x83, 0xff, 0x1f, 0xff, 0xff );
    // OSA 16
    FCML_I32( "jnc 00000204h", 0x66, 0x0f, 0x83, 0xff, 0xf1 );
}

void fcml_tf_instruction_JMP(void) {
    FCML_I32_M( "jmp 00401001h", 2, FCML_MI( 0xeb, 0xff ), FCML_MI( 0xe9, 0xfc, 0xff, 0xff, 0xff ) );
    // E9 cw JMP rel16 A N.S. Valid Jump near, relative, displacement relative to next instruction. Not supported in 64-bit mode.
    // E9 cd JMP rel32 A Valid Valid Jump near, relative, RIP = RIP + 32-bit displacement sign extended to 64-bits
    FCML_I32( "jmp 90d11004h", 0xe9, 0xff,0xff, 0x90, 0x90 );
    FCML_I32( "jmp 0000a103h", 0x66, 0xe9, 0xff, 0x90 );
    // FF /4 JMP r/m16 B N.S. Valid Jump near, absolute indirect, address = zero-extended r/m16. Not supported in 64- bit mode.
    // FF /4 JMP r/m32 B N.S. Valid Jump near, absolute indirect, address given in r/m32. Not supported in 64-bit mode.
    // FF /4 JMP r/m64 B Valid N.E. Jump near, absolute indirect, RIP = 64-Bit offset from register or memory
    FCML_I32( "jmp ebp", 0xff, 0xe5 );
    FCML_I32( "jmp bp", 0x66, 0xff, 0xe5 );
    FCML_I64_D( "jmp rbp", 0x66, 0x67, 0x40, 0xff, 0xe5 ); // 32 bit mode doesn't not allow REX.
    FCML_I64( "jmp rbp", 0xff, 0xe5 );
    FCML_I32( "jmp far 6655h:44332211h", 0xEA, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66 );
    FCML_I32( "jmp far 4433h:2211h", 0x66, 0xEA, 0x11, 0x22, 0x33, 0x44 );
    // m16:16,m16:32,m16:64
    FCML_I32( "jmp far fword ptr [ebx+00000001h]", 0xFF, 0x6B, 0x01 );
    FCML_I32( "jmp far dword ptr [ebx+00000001h]", 0x66, 0xFF, 0x6B, 0x01 );
    FCML_I64_D( "jmp far tbyte ptr [rbx+0000000000000001h]", 0x66, 0x48, 0xFF, 0x6B, 0x01 ); // Verified.
    FCML_I64( "jmp far tbyte ptr [rbx+0000000000000001h]", 0x48, 0xFF, 0x6B, 0x01 ); // Verified.
    FCML_I64_D( "jmp far dword ptr [rbx+0000000000000001h]", 0x66, 0x40, 0xFF, 0x6B, 0x01 ); // Verified.
    FCML_I64( "jmp far dword ptr [rbx+0000000000000001h]", 0x66, 0xFF, 0x6B, 0x01 ); // Verified.
    FCML_I64_D( "jmp far fword ptr [rbx+0000000000000001h]", 0x40, 0xFF, 0x6B, 0x01 );
    FCML_I64( "jmp far fword ptr [rbx+0000000000000001h]", 0xFF, 0x6B, 0x01 );
    FCML_I64_D( "jmp far dword ptr [ebx+00000001h]", 0x66, 0x67, 0x40, 0xFF, 0x6B, 0x01 );
    FCML_I64( "jmp far dword ptr [ebx+00000001h]", 0x66, 0x67, 0xFF, 0x6B, 0x01 );
}

CU_TestInfo fctl_ti_instructions_j[] = {
    { "fcml_tf_instruction_JCXZ", fcml_tf_instruction_JCXZ },
    { "fcml_tf_instruction_Jcc", fcml_tf_instruction_Jcc },
    { "fcml_tf_instruction_JMP", fcml_tf_instruction_JMP },
    CU_TEST_INFO_NULL,
};

CU_SuiteInfo fctl_si_instructions_j[] = {
    { "suite-fctl_ti_instructions_j", fcml_tf_instructions_j_suite_init, fcml_tf_instructions_j_suite_cleanup, fctl_ti_instructions_j },
    CU_SUITE_INFO_NULL,
};
