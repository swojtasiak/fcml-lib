/*
 * instructions.c
 *
 *  Created on: 01-06-2013
 *      Author: tAs
 */

#include <fcml_assembler.h>
#include "instructions_l_t.h"
#include "instructions_base_t.h"

fcml_bool fcml_tf_instructions_l_suite_init(void) {
	return FCML_TRUE;
}

fcml_bool fcml_tf_instructions_l_suite_cleanup(void) {
	return FCML_TRUE;
}

void fcml_tf_instruction_LAHF(void) {
    FCML_I3264( "lahf", 0x9F );
    FCML_A64( "lahf", 0x9f );
}

void fcml_tf_instruction_LAR(void) {
    /* 0F 02 /r LAR r16, r16/m16 A Valid Valid r16 r16/m16 masked by FF00H.*/
    /* 0F 02 /r LAR r32, r32/m16 A Valid Valid r32 r32/m16 masked by 00FxFF00H*/
    FCML_I32( "lar ebp,word ptr [eax+00000020h]", 0x0f, 0x02, 0x68, 0x20 );
    FCML_I32( "lar ecx,esp", 0x0f, 0x02, 0xcc );
    FCML_I32( "lar bp,word ptr [eax+00000020h]", 0x66, 0x0f, 0x02, 0x68, 0x20 );
    FCML_I32( "lar cx,sp", 0x66, 0x0f, 0x02, 0xcc );
    FCML_I64( "lar ebp,word ptr [rax+0000000000000020h]", 0x0f, 0x02, 0x68, 0x20 );
    FCML_I64( "lar ecx,esp", 0x0f, 0x02, 0xcc );
    /* REX.W + 0F 02 /r LAR r64, r32/m16 A Valid N.E. r64 r32/m16 masked by 00FxFF00H*/
    FCML_I64( "lar rbp,word ptr [rax+0000000000000020h]", 0x48, 0x0f, 0x02, 0x68, 0x20 );
    FCML_I64( "lar rcx,esp", 0x48, 0x0f, 0x02, 0xcc );
    /* GAS*/
    FCML_A32( "lar 0x00000020(%eax),%ebp", 0x0f, 0x02, 0x68, 0x20 );
    FCML_A32( "lar 0x00000020(%eax),%bp", 0x66, 0x0f, 0x02, 0x68, 0x20 );
    FCML_A64( "lar 0x0000000000000020(%rax),%rbp", 0x48, 0x0f, 0x02, 0x68, 0x20 );
    FCML_A64( "lar %sp,%cx", 0x66, 0x0f, 0x02, 0xcc );
}

void fcml_tf_instruction_LDDQU(void) {
    FCML_I32( "lddqu xmm5,[eax+00000020h]", 0xF2, 0x0F, 0xF0, 0x68, 0x20 );
    FCML_I64( "lddqu xmm5,[rax+0000000000000020h]", 0xF2, 0x0F, 0xF0, 0x68, 0x20 );
    /* VEX.128.F2.0F F0 /r VLDDQU xmm1, m128*/
    /* VEX.256.F2.0F F0 /r VLDDQU ymm1, m256*/
    FCML_I64( "vlddqu xmm8,xmmword ptr [r8]", 0xC4, 0x41, 0x7B, 0xF0, 0x00 );
    FCML_I32( "vlddqu ymm0,ymmword ptr [eax]", 0xc5, 0xff, 0xf0, 0x00 );
    /* GAS*/
    FCML_A64( "lddqu 0x0000000000000020(%rax),%xmm5", 0xf2, 0x0f, 0xf0, 0x68, 0x20 );
    FCML_A64( "vlddqu (%r8),%xmm8", 0xc4, 0x41, 0x7b, 0xf0, 0x00 );
    FCML_A64( "vlddqu (%rax),%ymm0", 0xc5, 0xff, 0xf0, 0x00 );
}

void fcml_tf_instruction_LDMXCSR(void) {
    FCML_I32( "ldmxcsr dword ptr [eax+00000020h]", 0x0F, 0xAE, 0x50, 0x20 );
    FCML_I64( "ldmxcsr dword ptr [rax+0000000000000020h]", 0x0F, 0xAE, 0x50, 0x20 );
    /* GAS*/
    FCML_A64( "ldmxcsr 0x0000000000000020(%rax)", 0x0f, 0xae, 0x50, 0x20 );
    FCML_A64( "vldmxcsr 0x0000000000000020(%rax)", 0xc5, 0xf8, 0xae, 0x50, 0x20 );
}

void fcml_tf_instruction_LDS(void) {
    /* C5 /r LDS r16,m16:16 A Invalid Valid Load DS:r16 with far pointer from memory.*/
    /* C5 /r LDS r32,m16:32 A Invalid Valid Load DS:r32 with far pointer from memory.*/
    FCML_I32( "lds far ebp,fword ptr [eax+00000020h]", 0xC5, 0x68, 0x20 );
    FCML_I32( "lds far bp,dword ptr [eax+00000020h]", 0x66, 0xc5, 0x68, 0x20 );
    /* GAS*/
    FCML_A32( "lds 0x00000020(%eax),%ebp", 0xC5, 0x68, 0x20 );
	FCML_A32( "lds 0x00000020(%eax),%bp", 0x66, 0xc5, 0x68, 0x20 );
    /* 0F B2 /r LSS r16,m16:16 A Valid Valid Load SS:r16 with far pointer from memory.*/
    /* 0F B2 /r LSS r32,m16:32 A Valid Valid Load SS:r32 with far pointer from memory.*/
    /* REX + 0F B2 /r LSS r64,m16:64 A Valid N.E. Load SS:r64 with far pointer from memory.*/
    FCML_I32( "lss far ebp,fword ptr [eax+00000020h]", 0x0F, 0xB2, 0x68, 0x20 );
    FCML_I64( "lss far ebp,fword ptr [rax+0000000000000020h]", 0x0F, 0xB2, 0x68, 0x20 );
    FCML_I32( "lss far bp,dword ptr [eax+00000020h]", 0x66, 0x0F, 0xB2, 0x68, 0x20 );
    FCML_I64( "lss far bp,dword ptr [rax+0000000000000020h]", 0x66, 0x0F, 0xB2, 0x68, 0x20 );
    FCML_I64( "lss far rbp,tbyte ptr [rax+0000000000000020h]", 0x48, 0x0F, 0xB2, 0x68, 0x20 );
    /* GAS*/
    FCML_A64( "lss 0x0000000000000020(%rax),%ebp", 0x0f, 0xb2, 0x68, 0x20 );
    FCML_A64( "lss 0x0000000000000020(%rax),%bp", 0x66, 0x0f, 0xb2, 0x68, 0x20 );
    FCML_A64( "lss 0x0000000000000020(%rax),%rbp", 0x48, 0x0f, 0xb2, 0x68, 0x20 );
    /* C4 /r LES r16,m16:16 A Invalid Valid Load ES:r16 with far pointer from memory.*/
    /* C4 /r LES r32,m16:32 A Invalid Valid Load ES:r32 with far pointer from memory.*/
    FCML_I32( "les far ebp,fword ptr [eax+00000020h]", 0xC4, 0x68, 0x20 );
    FCML_I32( "les far bp,dword ptr [eax+00000020h]", 0x66, 0xc4, 0x68, 0x20 );
    /* GAS*/
    FCML_A32( "les 0x00000020(%eax),%ebp", 0xC4, 0x68, 0x20 );
    FCML_A32( "les 0x00000020(%eax),%bp", 0x66, 0xc4, 0x68, 0x20 );
    /* 0F B4 /r LFS r16,m16:16 A Valid Valid Load FS:r16 with far pointer from memory.*/
    /* 0F B4 /r LFS r32,m16:32 A Valid Valid Load FS:r32 with far pointer from memory.*/
    /* REX + 0F B4 /r LFS r64,m16:64 A Valid N.E. Load FS:r64 with far pointer from memory.*/
    FCML_I32( "lfs far ebp,fword ptr [eax+00000020h]", 0x0F, 0xB4, 0x68, 0x20 );
    FCML_I64( "lfs far ebp,fword ptr [rax+0000000000000020h]", 0x0F, 0xB4, 0x68, 0x20 );
    FCML_I32( "lfs far bp,dword ptr [eax+00000020h]", 0x66, 0x0F, 0xB4, 0x68, 0x20 );
    FCML_I64( "lfs far bp,dword ptr [rax+0000000000000020h]", 0x66, 0x0F, 0xB4, 0x68, 0x20 );
    FCML_I64( "lfs far rbp,tbyte ptr [rax+0000000000000020h]", 0x48, 0x0F, 0xB4, 0x68, 0x20 );
    /* GAS*/
    FCML_A64( "lfs 0x0000000000000020(%rax),%ebp", 0x0f, 0xb4, 0x68, 0x20 );
    FCML_A64( "lfs 0x0000000000000020(%rax),%bp", 0x66, 0x0f, 0xb4, 0x68, 0x20 );
    FCML_A64( "lfs 0x0000000000000020(%rax),%rbp", 0x48, 0x0f, 0xb4, 0x68, 0x20 );
    /* 0F B5 /r LGS r16,m16:16 A Valid Valid Load GS:r16 with far pointer from memory.*/
    /* 0F B5 /r LGS r32,m16:32 A Valid Valid Load GS:r32 with far pointer from memory.*/
    /* REX + 0F B5 /r LGS r64,m16:64 A Valid N.E. Load GS:r64 with far pointer from memory.*/
    FCML_I32( "lgs far ebp,fword ptr [eax+00000020h]", 0x0F, 0xB5, 0x68, 0x20 );
    FCML_I64( "lgs far ebp,fword ptr [rax+0000000000000020h]", 0x0F, 0xB5, 0x68, 0x20 );
    FCML_I32( "lgs far bp,dword ptr [eax+00000020h]", 0x66, 0x0F, 0xB5, 0x68, 0x20 );
    FCML_I64( "lgs far bp,dword ptr [rax+0000000000000020h]", 0x66, 0x0F, 0xB5, 0x68, 0x20 );
    FCML_I64( "lgs far rbp,tbyte ptr [rax+0000000000000020h]", 0x48, 0x0F, 0xB5, 0x68, 0x20 );
    /* GAS*/
    FCML_A64( "lgs 0x0000000000000020(%rax),%ebp", 0x0f, 0xb5, 0x68, 0x20 );
    FCML_A64( "lgs 0x0000000000000020(%rax),%bp", 0x66, 0x0f, 0xb5, 0x68, 0x20 );
    FCML_A64( "lgs 0x0000000000000020(%rax),%rbp", 0x48, 0x0f, 0xb5, 0x68, 0x20 );
}

void fcml_tf_instruction_LEA(void) {
    FCML_I32( "lea ebp,[eax+00000020h]", 0x8D, 0x68, 0x20 );
    FCML_I32( "lea bp,[eax+00000020h]", 0x66, 0x8D, 0x68, 0x20 );
    FCML_I64( "lea rbp,[rax+0000000000000020h]", 0x48, 0x8D, 0x68, 0x20 );
    /* GAS*/
    FCML_A32( "lea 0x00000020(%eax),%ebp", 0x8D, 0x68, 0x20 );
	FCML_A32( "lea 0x00000020(%eax),%bp", 0x66, 0x8D, 0x68, 0x20 );
	FCML_A64( "lea 0x0000000000000020(%rax),%rbp", 0x48, 0x8d, 0x68, 0x20 );
}

void fcml_tf_instruction_LEAVE(void) {
    FCML_I3264( "leave", 0xc9 );
    FCML_A3264( "leave", 0xc9 );
}

void fcml_tf_instruction_LFENCE(void) {
    FCML_I3264("lfence", 0x0F, 0xAE, 0xE8);
    FCML_A3264("lfence", 0x0F, 0xAE, 0xE8);
}

void fcml_tf_instruction_LLWPCB(void) {
    /* LLWPCB reg32 8F RXB.09 0.1111.0.00 12 /0*/
    /* vvvv - should be 1*/
    FCML_I32_D( "llwpcb eax", 0x8F, 0xE9, 0x60, 0x12, 0xC0 );
    FCML_I32( "llwpcb eax", 0x8F, 0xE9, 0x78, 0x12, 0xC0 );
    /* LLWPCB reg64 8F RXB.09 1.1111.0.00 12 /0*/
    FCML_I64_D( "llwpcb rax", 0x8F, 0xE9, 0xE0, 0x12, 0xC0 );
    FCML_I64( "llwpcb rax", 0x8F, 0xE9, 0xF8, 0x12, 0xC0 );
    /* GAS*/
    FCML_A32( "llwpcb %eax", 0x8f, 0xe9, 0x78, 0x12, 0xc0 );
    FCML_A64( "llwpcb %rax", 0x8f, 0xe9, 0xf8, 0x12, 0xc0 );
}

void fcml_tf_instruction_LGDT(void) {
    FCML_I32( "lgdt fword ptr [eax+00000020h]", 0x0F, 0x01, 0x50, 0x20 );
    FCML_I32( "lgdt fword ptr [eax+00000020h]", 0x66, 0x0F, 0x01, 0x50, 0x20 );
    FCML_I64_D( "lgdt tbyte ptr [rax+0000000000000020h]", 0x66, 0x0F, 0x01, 0x50, 0x20 );
    FCML_I64_D( "lgdt tbyte ptr [rax+0000000000000020h]", 0x48, 0x0F, 0x01, 0x50, 0x20 );
    FCML_I64( "lgdt tbyte ptr [rax+0000000000000020h]", 0x0F, 0x01, 0x50, 0x20 );
    /* GAS*/
    FCML_A32( "lgdt 0x00000020(%eax)", 0x0f, 0x01, 0x50, 0x20 );
    FCML_A64( "lgdt 0x0000000000000020(%rax)", 0x0f, 0x01, 0x50, 0x20 );
	FCML_A32( "lgdt 0x00000020(%eax)", 0x0f, 0x01, 0x50, 0x20 );
	FCML_A64( "lgdt 0x0000000000000020(%rax)", 0x0f, 0x01, 0x50, 0x20 );
}

void fcml_tf_instruction_LIDT(void) {
    FCML_I32( "lidt fword ptr [eax+00000020h]", 0x0F, 0x01, 0x58, 0x20 );
    FCML_I32( "lidt fword ptr [eax+00000020h]", 0x66, 0x0F, 0x01, 0x58, 0x20 );
    FCML_I64_D( "lidt tbyte ptr [rax+0000000000000020h]", 0x66, 0x0F, 0x01, 0x58, 0x20 );
    FCML_I64_D( "lidt tbyte ptr [rax+0000000000000020h]", 0x48, 0x0F, 0x01, 0x58, 0x20 );
    FCML_I64( "lidt tbyte ptr [rax+0000000000000020h]", 0x0F, 0x01, 0x58, 0x20 );
    /* GAS*/
    FCML_A32( "lidt 0x00000020(%eax)", 0x0f, 0x01, 0x58, 0x20 );
    FCML_A64( "lidt 0x0000000000000020(%rax)", 0x0f, 0x01, 0x58, 0x20 );
	FCML_A32( "lidt 0x00000020(%eax)", 0x0f, 0x01, 0x58, 0x20 );
	FCML_A64( "lidt 0x0000000000000020(%rax)", 0x0f, 0x01, 0x58, 0x20 );
}

void fcml_tf_instruction_LLDT(void) {
    FCML_I32( "lldt word ptr [eax+00000020h]", 0x0F, 0x00, 0x50, 0x20 );
    FCML_I32( "lldt word ptr [eax+00000020h]", 0x66, 0x0F, 0x00, 0x50, 0x20 );
    FCML_I64( "lldt word ptr [rax+0000000000000020h]", 0x0F, 0x00, 0x50, 0x20 );
    /* GAS*/
    FCML_A32( "lldt 0x00000020(%eax)", 0x0F, 0x00, 0x50, 0x20 );
    FCML_A64( "lldt 0x0000000000000020(%rax)", 0x0f, 0x00, 0x50, 0x20 );
}

void fcml_tf_instruction_LMSW(void) {
    FCML_I32( "lmsw word ptr [eax+00000020h]", 0x0F, 0x01, 0x70, 0x20 );
    FCML_I32( "lmsw word ptr [eax+00000020h]", 0x66, 0x0F, 0x01, 0x70, 0x20 );
    FCML_I64( "lmsw word ptr [rax+0000000000000020h]", 0x0F, 0x01, 0x70, 0x20 );
}

void fcml_tf_instruction_LODS(void) {
    FCML_I32( "rep lods byte ptr es:[esi]", 0xF3, 0x26, 0xAC );
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
    /* GAS*/
    FCML_A32( "rep lodsb %es:(%esi)", 0xF3, 0x26, 0xAC );
	FCML_A32( "lodsb (%esi)", 0xAC );
	FCML_A32( "lodsl (%esi)", 0xAD );
	FCML_A32( "lodsw (%si)",0x66, 0x67, 0xAD );
	FCML_A64( "lodsq (%rsi)", 0x48, 0xAD );
	FCML_A32_A( "lodsb", 0xAC );
	FCML_A32_A( "lodsl", 0xAD );
	FCML_A32_A( "lodsw",0x66, 0xAD );
	FCML_A64_A( "lodsq", 0x48, 0xAD );
}

void fcml_tf_instruction_LOOP(void) {
    FCML_I32( "loop 00401012h", 0xE2, 0x10);
    FCML_I32( "loop 00401013h", 0x67, 0xE2, 0x10);
    FCML_I64( "loop 0000800000401013h", 0x48, 0xE2, 0x10);
    FCML_I32( "loope 00401012h", 0xE1, 0x10);
    FCML_I32( "loope 00401013h", 0x67, 0xE1, 0x10);
    FCML_I64( "loope 0000800000401013h", 0x48, 0xE1, 0x10);
    FCML_I32( "loopne 00401012h", 0xE0, 0x10);
    FCML_I32_A( "loopz 00401012h", 0xE1, 0x10);
    FCML_I32( "loopne 00401013h", 0x67, 0xE0, 0x10);
    FCML_I64( "loopne 0000800000401013h", 0x48, 0xE0, 0x10);
    FCML_I32_A( "loopnz 00401012h", 0xE0, 0x10);
    /* GAS*/
    FCML_A64( "loop 0x0000800000401013", 0x48, 0xE2, 0x10);
    FCML_A64( "loope 0x0000800000401013", 0x48, 0xE1, 0x10);
    FCML_A64( "loopne 0x0000800000401013", 0x48, 0xE0, 0x10);
}

void fcml_tf_instruction_LWPINS(void) {
    /* LWPINS reg32.vvvv, reg/mem32, int32 8F RXB.0A 0.src1.0.00 12 /0 /int32*/
    FCML_I32( "lwpins ebx,dword ptr [eax],33221100h", 0x8F, 0xEA, 0x60, 0x12, 0x00, 0x00, 0x11, 0x22, 0x33 );
    FCML_I32( "lwpins ebx,eax,33221100h", 0x8F, 0xEA, 0x60, 0x12, 0xC0, 0x00, 0x11, 0x22, 0x33 );
    /* LWPINS reg64.vvvv, reg/mem32, int32 8F RXB.0A 1.src1.0.00 12 /0 /int32*/
    FCML_I64( "lwpins rbx,dword ptr [rax],33221100h", 0x8F, 0xEA, 0xE0, 0x12, 0x00, 0x00, 0x11, 0x22, 0x33 );
    FCML_I64( "lwpins rbx,eax,33221100h", 0x8F, 0xEA, 0xE0, 0x12, 0xC0, 0x00, 0x11, 0x22, 0x33 );
    /* GAS*/
    FCML_A32( "lwpins $0x33221100,(%eax),%ebx", 0x8f, 0xea, 0x60, 0x12, 0x00, 0x00, 0x11, 0x22, 0x33 );
    FCML_A64( "lwpins $0x33221100,%eax,%rbx", 0x8f, 0xea, 0xe0, 0x12, 0xc0, 0x00, 0x11, 0x22, 0x33 );
}

void fcml_tf_instruction_LWPVAL(void) {
    /* LWPVAL reg32.vvvv, reg/mem32, int32 8F RXB.0A 0.src1.0.00 12 /1 /int32*/
    FCML_I32( "lwpval ebx,dword ptr [eax],33221100h", 0x8F, 0xEA, 0x60, 0x12, 0x08, 0x00, 0x11, 0x22, 0x33 );
    FCML_I32( "lwpval ebx,eax,33221100h", 0x8F, 0xEA, 0x60, 0x12, 0xC8, 0x00, 0x11, 0x22, 0x33 );
    /* LWPVAL reg64.vvvv, reg/mem32, int32 8F RXB.0A 1.src1.0.00 12 /1 /int32*/
    FCML_I64( "lwpval rbx,dword ptr [rax],33221100h", 0x8F, 0xEA, 0xE0, 0x12, 0x08, 0x00, 0x11, 0x22, 0x33 );
    FCML_I64( "lwpval rbx,eax,33221100h", 0x8F, 0xEA, 0xE0, 0x12, 0xC8, 0x00, 0x11, 0x22, 0x33 );
    /* GAS*/
    FCML_A32( "lwpval $0x33221100,(%eax),%ebx", 0x8f, 0xea, 0x60, 0x12, 0x08, 0x00, 0x11, 0x22, 0x33 );
    FCML_A64( "lwpval $0x33221100,%eax,%rbx", 0x8f, 0xea, 0xe0, 0x12, 0xc8, 0x00, 0x11, 0x22, 0x33 );
}

void fcml_tf_instruction_LSL(void) {
    /* 0F 03 /r LSL r16, r16/m16 A Valid Valid Load: r16 segment limit, selector r16/m16.*/
    /* 0F 03 /r LSL r32, r32/m16*A Valid Valid Load: r32 segment limit, selector r32/m16.*/
    FCML_I32( "lsl ebp,word ptr [eax+00000020h]", 0x0f, 0x03, 0x68, 0x20 );
    FCML_I32( "lsl ecx,sp", 0x0f, 0x03, 0xcc );
    FCML_I32( "lsl bp,word ptr [eax+00000020h]", 0x66, 0x0f, 0x03, 0x68, 0x20 );
    FCML_I32( "lsl cx,sp", 0x66, 0x0f, 0x03, 0xcc );
    FCML_I64( "lsl ebp,word ptr [rax+0000000000000020h]", 0x0f, 0x03, 0x68, 0x20 );
    FCML_I64( "lsl ecx,sp", 0x0f, 0x03, 0xcc );
    /* REX.W + 0F 03 /r LSL r64, r32/m16*A Valid Valid Load: r64 segment limit, selector r32/m16*/
    FCML_I64( "lsl rbp,word ptr [rax+0000000000000020h]", 0x48, 0x0f, 0x03, 0x68, 0x20 );
    FCML_I64( "lsl rcx,sp", 0x48, 0x0f, 0x03, 0xcc );
    /* GAS*/
    FCML_A32( "lsl 0x00000020(%eax),%ebp", 0x0f, 0x03, 0x68, 0x20 );
	FCML_A32( "lsl %sp,%ecx", 0x0f, 0x03, 0xcc );
	FCML_A32( "lsl 0x00000020(%eax),%bp", 0x66, 0x0f, 0x03, 0x68, 0x20 );
    FCML_A32( "lsl %sp,%cx", 0x66, 0x0f, 0x03, 0xcc );
    FCML_A64( "lsl 0x0000000000000020(%rax),%rbp", 0x48, 0x0f, 0x03, 0x68, 0x20 );
}

void fcml_tf_instruction_LTR(void) {
    FCML_I32( "ltr word ptr [eax+00000020h]", 0x0F, 0x00, 0x58, 0x20 );
    FCML_I32( "ltr ax", 0x0F, 0x00, 0xD8);
    FCML_I64( "ltr word ptr [rax+0000000000000020h]", 0x0F, 0x00, 0x58, 0x20 );
    /* GAS*/
    FCML_A32( "ltr 0x00000020(%eax)", 0x0f, 0x00, 0x58, 0x20 );
    FCML_A64( "ltr 0x0000000000000020(%rax)", 0x0f, 0x00, 0x58, 0x20 );
}

void fcml_tf_instruction_LZCNT(void) {
    /* F3 0F BD /r LZCNT r16,r/m16*/
    /* F3 0F BD /r LZCNT r32,r/m32*/
    /* REX.W + F3 0F BD /r LZCNT r64,r/m64*/
    FCML_I32( "lzcnt eax,dword ptr [eax]", 0xF3, 0x0F, 0xBD, 0x00 );
    FCML_I32( "lzcnt ax,word ptr [eax]", 0x66, 0xF3, 0x0F, 0xBD, 0x00 );
    FCML_I32( "lzcnt ax,ax", 0x66, 0xF3, 0x0F, 0xBD, 0xC0 );
    FCML_I64( "lzcnt rax,qword ptr [rax]", 0xF3, 0x48, 0x0F, 0xBD, 0x00 );
    /* GAS*/
    FCML_A32( "lzcnt %ax,%ax", 0x66, 0xF3, 0x0F, 0xBD, 0xC0 );
    FCML_A32( "lzcnt (%eax),%eax", 0xf3, 0x0f, 0xbd, 0x00 );
    FCML_A64( "lzcnt (%rax),%rax", 0xf3, 0x48, 0x0f, 0xbd, 0x00 );
}

fcml_stf_test_case fctl_ti_instructions_l[] = {
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
	{ "fcml_tf_instruction_LIDT", fcml_tf_instruction_LIDT },
	{ "fcml_tf_instruction_LLDT", fcml_tf_instruction_LLDT },
	{ "fcml_tf_instruction_LMSW", fcml_tf_instruction_LMSW },
	{ "fcml_tf_instruction_LODS", fcml_tf_instruction_LODS },
	{ "fcml_tf_instruction_LOOP", fcml_tf_instruction_LOOP },
	{ "fcml_tf_instruction_LWPINS", fcml_tf_instruction_LWPINS },
	{ "fcml_tf_instruction_LWPVAL", fcml_tf_instruction_LWPVAL },
	{ "fcml_tf_instruction_LSL", fcml_tf_instruction_LSL },
	{ "fcml_tf_instruction_LTR", fcml_tf_instruction_LTR },
	{ "fcml_tf_instruction_LZCNT", fcml_tf_instruction_LZCNT },
	FCML_STF_NULL_TEST
};

fcml_stf_test_suite fctl_si_instructions_l = {
	"suite-fctl_ti_instructions_l", fcml_tf_instructions_l_suite_init, fcml_tf_instructions_l_suite_cleanup, fctl_ti_instructions_l
};


