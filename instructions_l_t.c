/*
 * instructions.c
 *
 *  Created on: 01-06-2013
 *      Author: tAs
 */

#include "fcml_env.h"
#include "fcml_assembler.h"
#include "instructions_i_t.h"

int fcml_tf_instructions_l_suite_init(void) {
	return 0;
}

int fcml_tf_instructions_l_suite_cleanup(void) {
	return 0;
}

void fcml_tf_instruction_LAHF(void) {
    FCML_I3264( "lahf", 0x9F );
}

void fcml_tf_instruction_LAR(void) {
    // 0F 02 /r LAR r16, r16/m16 A Valid Valid r16 r16/m16 masked by FF00H.
    // 0F 02 /r LAR r32, r32/m16 A Valid Valid r32 r32/m16 masked by 00FxFF00H
    FCML_I32( "lar ebp,word ptr [eax+00000020h]", 0x0f, 0x02, 0x68, 0x20 );
    FCML_I32( "lar ecx,esp", 0x0f, 0x02, 0xcc );
    FCML_I32( "lar bp,word ptr [eax+00000020h]", 0x66, 0x0f, 0x02, 0x68, 0x20 );
    FCML_I32( "lar cx,sp", 0x66, 0x0f, 0x02, 0xcc );
    FCML_I64( "lar ebp,word ptr [rax+0000000000000020h]", 0x0f, 0x02, 0x68, 0x20 );
    FCML_I64( "lar ecx,esp", 0x0f, 0x02, 0xcc );
    // REX.W + 0F 02 /r LAR r64, r32/m16 A Valid N.E. r64 r32/m16 masked by 00FxFF00H
    FCML_I64( "lar rbp,word ptr [rax+0000000000000020h]", 0x48, 0x0f, 0x02, 0x68, 0x20 );
    FCML_I64( "lar rcx,esp", 0x48, 0x0f, 0x02, 0xcc );
}

void fcml_tf_instruction_LDDQU(void) {
    FCML_I32( "lddqu xmm5,[eax+00000020h]", 0xF2, 0x0F, 0xF0, 0x68, 0x20 );
    FCML_I64( "lddqu xmm5,[rax+0000000000000020h]", 0xF2, 0x0F, 0xF0, 0x68, 0x20 );
    // VEX.128.F2.0F F0 /r VLDDQU xmm1, m128
    // VEX.256.F2.0F F0 /r VLDDQU ymm1, m256
    FCML_I64( "vlddqu xmm8,oword ptr [r8]", 0xC4, 0x41, 0x7B, 0xF0, 0x00 );
    FCML_I32( "vlddqu ymm0,ymmword ptr [eax]", 0xc5, 0xff, 0xf0, 0x00 );
}

void fcml_tf_instruction_LDMXCSR(void) {
    FCML_I32( "ldmxcsr dword ptr [eax+00000020h]", 0x0F, 0xAE, 0x50, 0x20 );
    FCML_I64( "ldmxcsr dword ptr [rax+0000000000000020h]", 0x0F, 0xAE, 0x50, 0x20 );
}

void fcml_tf_instruction_LDS(void) {
    // C5 /r LDS r16,m16:16 A Invalid Valid Load DS:r16 with far pointer from memory.
    // C5 /r LDS r32,m16:32 A Invalid Valid Load DS:r32 with far pointer from memory.
    FCML_I32( "lds far ebp,fword ptr [eax+00000020h]", 0xC5, 0x68, 0x20 );
    FCML_I32( "lds far bp,dword ptr [eax+00000020h]", 0x66, 0xc5, 0x68, 0x20 );
    // 0F B2 /r LSS r16,m16:16 A Valid Valid Load SS:r16 with far pointer from memory.
    // 0F B2 /r LSS r32,m16:32 A Valid Valid Load SS:r32 with far pointer from memory.
    // REX + 0F B2 /r LSS r64,m16:64 A Valid N.E. Load SS:r64 with far pointer from memory.
    FCML_I32( "lss far ebp,fword ptr [eax+00000020h]", 0x0F, 0xB2, 0x68, 0x20 );
    FCML_I64( "lss far ebp,fword ptr [rax+0000000000000020h]", 0x0F, 0xB2, 0x68, 0x20 );
    FCML_I32( "lss far bp,dword ptr [eax+00000020h]", 0x66, 0x0F, 0xB2, 0x68, 0x20 );
    FCML_I64( "lss far bp,dword ptr [rax+0000000000000020h]", 0x66, 0x0F, 0xB2, 0x68, 0x20 );
    FCML_I64( "lss far rbp,tbyte ptr [rax+0000000000000020h]", 0x48, 0x0F, 0xB2, 0x68, 0x20 );
    // C4 /r LES r16,m16:16 A Invalid Valid Load ES:r16 with far pointer from memory.
    // C4 /r LES r32,m16:32 A Invalid Valid Load ES:r32 with far pointer from memory.
    FCML_I32( "les far ebp,fword ptr [eax+00000020h]", 0xC4, 0x68, 0x20 );
    FCML_I32( "les far bp,dword ptr [eax+00000020h]", 0x66, 0xc4, 0x68, 0x20 );
    // 0F B4 /r LFS r16,m16:16 A Valid Valid Load FS:r16 with far pointer from memory.
    // 0F B4 /r LFS r32,m16:32 A Valid Valid Load FS:r32 with far pointer from memory.
    // REX + 0F B4 /r LFS r64,m16:64 A Valid N.E. Load FS:r64 with far pointer from memory.
    FCML_I32( "lfs far ebp,fword ptr [eax+00000020h]", 0x0F, 0xB4, 0x68, 0x20 );
    FCML_I64( "lfs far ebp,fword ptr [rax+0000000000000020h]", 0x0F, 0xB4, 0x68, 0x20 );
    FCML_I32( "lfs far bp,dword ptr [eax+00000020h]", 0x66, 0x0F, 0xB4, 0x68, 0x20 );
    FCML_I64( "lfs far bp,dword ptr [rax+0000000000000020h]", 0x66, 0x0F, 0xB4, 0x68, 0x20 );
    FCML_I64( "lfs far rbp,tbyte ptr [rax+0000000000000020h]", 0x48, 0x0F, 0xB4, 0x68, 0x20 );
    // 0F B5 /r LGS r16,m16:16 A Valid Valid Load GS:r16 with far pointer from memory.
    // 0F B5 /r LGS r32,m16:32 A Valid Valid Load GS:r32 with far pointer from memory.
    // REX + 0F B5 /r LGS r64,m16:64 A Valid N.E. Load GS:r64 with far pointer from memory.
    FCML_I32( "lgs far ebp,fword ptr [eax+00000020h]", 0x0F, 0xB5, 0x68, 0x20 );
    FCML_I64( "lgs far ebp,fword ptr [rax+0000000000000020h]", 0x0F, 0xB5, 0x68, 0x20 );
    FCML_I32( "lgs far bp,dword ptr [eax+00000020h]", 0x66, 0x0F, 0xB5, 0x68, 0x20 );
    FCML_I64( "lgs far bp,dword ptr [rax+0000000000000020h]", 0x66, 0x0F, 0xB5, 0x68, 0x20 );
    FCML_I64( "lgs far rbp,tbyte ptr [rax+0000000000000020h]", 0x48, 0x0F, 0xB5, 0x68, 0x20 );
}

void fcml_tf_instruction_LEA(void) {
    FCML_I32( "lea ebp,[eax+00000020h]", 0x8D, 0x68, 0x20 );
    FCML_I32( "lea bp,[eax+00000020h]", 0x66, 0x8D, 0x68, 0x20 );
    FCML_I64( "lea rbp,[rax+0000000000000020h]", 0x48, 0x8D, 0x68, 0x20 );
}

void fcml_tf_instruction_LEAVE(void) {
    FCML_I3264( "leave", 0xc9 );
}

void fcml_tf_instruction_LFENCE(void) {
    FCML_I3264("lfence", 0x0F, 0xAE, 0xE8);
}

void fcml_tf_instruction_LLWPCB(void) {
    // LLWPCB reg32 8F RXB.09 0.1111.0.00 12 /0
    // vvvv - should be 1
    FCML_I32_D( "llwpcb eax", 0x8F, 0xE9, 0x60, 0x12, 0xC0 );
    FCML_I32( "llwpcb eax", 0x8F, 0xE9, 0x78, 0x12, 0xC0 );
    // LLWPCB reg64 8F RXB.09 1.1111.0.00 12 /0
    FCML_I32_D( "llwpcb rax", 0x8F, 0xE9, 0xE0, 0x12, 0xC0 );
    FCML_I32( "llwpcb rax", 0x8F, 0xE9, 0xF8, 0x12, 0xC0 );
}

void fcml_tf_instruction_LGDT(void) {
    FCML_I32( "lgdt fword ptr [eax+00000020h]", 0x0F, 0x01, 0x50, 0x20 );
    FCML_I32( "lgdt fword ptr [eax+00000020h]", 0x66, 0x0F, 0x01, 0x50, 0x20 );
    FCML_I64( "lgdt fword ptr [rax+0000000000000020h]", 0x0F, 0x01, 0x50, 0x20 );
    FCML_I64( "lgdt fword ptr [rax+0000000000000020h]", 0x66, 0x0F, 0x01, 0x50, 0x20 );
    FCML_I64( "lgdt tbyte ptr [rax+0000000000000020h]", 0x48, 0x0F, 0x01, 0x50, 0x20 );
}

void fcml_tf_instruction_LLDT(void) {
    FCML_I32( "lldt word ptr [eax+00000020h]", 0x0F, 0x00, 0x50, 0x20 );
    FCML_I32( "lldt word ptr [eax+00000020h]", 0x66, 0x0F, 0x00, 0x50, 0x20 );
    FCML_I64( "lldt word ptr [rax+0000000000000020h]", 0x0F, 0x00, 0x50, 0x20 );
}

void fcml_tf_instruction_LMSW(void) {
    FCML_I32( "lmsw word ptr [eax+00000020h]", 0x0F, 0x01, 0x70, 0x20 );
    FCML_I32( "lmsw word ptr [eax+00000020h]", 0x66, 0x0F, 0x01, 0x70, 0x20 );
    FCML_I64( "lmsw word ptr [rax+0000000000000020h]", 0x0F, 0x01, 0x70, 0x20 );
}

void fcml_tf_instruction_LODS(void) {
    FCML_I32( "lods byte ptr es:[esi]", 0x26, 0xAC );
    FCML_I32( "lods byte ptr [esi]", 0xAC );
    FCML_I32( "lods dword ptr [esi]", 0xAD );
    FCML_I32( "lods word ptr [si]",0x66, 0x67, 0xAD );
    FCML_I64( "lods word ptr [rsi]",0x66, 0xAD );
    FCML_I64( "lods qword ptr [rsi]", 0x48, 0xAD );
    FCML_I32_A( "lodsb", 0xAC );
    FCML_I32_A( "lodsw", 0x66, 0xAD );
    FCML_I32_A( "lodsd", 0xAD );
    FCML_I64_A( "lodsw", 0x66, 0xAD );
    FCML_I64_A( "lodsd", 0xAD );
    FCML_I64_A( "lodsq", 0x48, 0xAD );
}

CU_TestInfo fctl_ti_instructions_l[] = {
    { "fcml_tf_instruction_LAHF", fcml_tf_instruction_LAHF },
    { "fcml_tf_instruction_LAR", fcml_tf_instruction_LAR },
    { "fcml_tf_instruction_LDDQU", fcml_tf_instruction_LDDQU },
    { "fcml_tf_instruction_LDMXCSR", fcml_tf_instruction_LDMXCSR },
    { "fcml_tf_instruction_LDS", fcml_tf_instruction_LDS },
    { "fcml_tf_instruction_LEA", fcml_tf_instruction_LEA },
    { "fcml_tf_instruction_LEAVE", fcml_tf_instruction_LEAVE },
    { "fcml_tf_instruction_LFENCE", fcml_tf_instruction_LFENCE },
    { "fcml_tf_instruction_LLWPCB", fcml_tf_instruction_LLWPCB },
    { "fcml_tf_instruction_LGDT", fcml_tf_instruction_LGDT },
    { "fcml_tf_instruction_LLDT", fcml_tf_instruction_LLDT },
    { "fcml_tf_instruction_LMSW", fcml_tf_instruction_LMSW },
    { "fcml_tf_instruction_LODS", fcml_tf_instruction_LODS },
    CU_TEST_INFO_NULL,
};

CU_SuiteInfo fctl_si_instructions_l[] = {
    { "suite-fctl_ti_instructions_l", fcml_tf_instructions_l_suite_init, fcml_tf_instructions_l_suite_cleanup, fctl_ti_instructions_l },
    CU_SUITE_INFO_NULL,
};
