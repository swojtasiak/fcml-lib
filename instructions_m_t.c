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

void fcml_tf_instruction_MONITOR(void) {
    FCML_I64( "monitor rax,rcx,rdx", 0x0F, 0x01, 0xC8 );
    FCML_I32_A( "monitor", 0x0F, 0x01, 0xC8 );
}

void fcml_tf_instruction_MOV(void) {
    // 0F 21/r MOV r32, DR0–DR7 A N.E. Valid Move debug register to r32
    FCML_I32( "mov eax,dr2", 0x0F, 0x21, 0xD0 );
    FCML_I32( "mov eax,dr2", 0x66, 0x0F, 0x21, 0xD0 );
    // 0F 21/r MOV r64, DR0–DR7 A Valid N.E. Move extended debug register to r64.
    FCML_I64_D( "mov rax,dr2", 0x66, 0x0F, 0x21, 0xD0 );
    FCML_I64_D( "mov rax,dr2", 0x48, 0x0F, 0x21, 0xD0 );
    FCML_I64( "mov rax,dr2", 0x0F, 0x21, 0xD0 );
    // 0F 23 /r MOV DR0–DR7, r32 A N.E. Valid Move r32 to debug register
    FCML_I32( "mov dr2,eax", 0x0F, 0x23, 0xD0 );
    FCML_I32( "mov dr2,eax", 0x66, 0x0F, 0x23, 0xD0 );
    // 0F 23 /r MOV DR0–DR7, r64 A Valid N.E. Move r64 to extended debug register.
    FCML_I64_D( "mov dr2,rax", 0x66, 0x0F, 0x23, 0xD0 );
    FCML_I64_D( "mov dr2,rax", 0x48, 0x0F, 0x23, 0xD0 );
    FCML_I64( "mov dr2,rax", 0x0F, 0x23, 0xD0 );

    FCML_I32( "mov eax,dr0", 0x0F, 0x21, 0xC0 );
    FCML_I32( "mov eax,dr1", 0x0F, 0x21, 0xC8 );
    FCML_I32( "mov eax,dr2", 0x0F, 0x21, 0xD0 );
    FCML_I32( "mov eax,dr3", 0x0F, 0x21, 0xD8 );
    FCML_I32( "mov eax,dr4", 0x0F, 0x21, 0xE0 );
    FCML_I32( "mov eax,dr5", 0x0F, 0x21, 0xE8 );
    FCML_I32( "mov eax,dr6", 0x0F, 0x21, 0xF0 );
    FCML_I32( "mov eax,dr7", 0x0F, 0x21, 0xF8 );
    FCML_I64_D( "mov rax,<unknown DR>", 0x44, 0x0F, 0x21, 0xC0 );
    FCML_I64_D( "mov rax,<unknown DR>", 0x44, 0x0F, 0x21, 0xC8 );
    FCML_I64_D( "mov rax,<unknown DR>", 0x44, 0x0F, 0x21, 0xD0 );
    FCML_I64_D( "mov rax,<unknown DR>", 0x44, 0x0F, 0x21, 0xD8 );
    FCML_I64_D( "mov rax,<unknown DR>", 0x44, 0x0F, 0x21, 0xE0 );
    FCML_I64_D( "mov rax,<unknown DR>", 0x44, 0x0F, 0x21, 0xE8 );
    FCML_I64_D( "mov rax,<unknown DR>", 0x44, 0x0F, 0x21, 0xF0 );
    FCML_I64_D( "mov rax,<unknown DR>", 0x44, 0x0F, 0x21, 0xF8 );

    // MOV (CR)
    // 0F 20/r MOV r32, CR0–CR7 A N.E. Valid Move control register to r32
    // 0F 20/r MOV r64, CR0–CR7 A Valid N.E. Move extended control register to r64.
    FCML_I32( "mov eax,cr2", 0x0F, 0x20, 0xD0 );
    FCML_I32( "mov eax,cr2", 0x66, 0x0F, 0x20, 0xD0 );
    // REX.R + 0F 20 /0 MOV r64, CR8 A Valid N.E. Move extended CR8 to r64.1
    FCML_I64_D( "mov rax,cr2", 0x66, 0x0F, 0x20, 0xD0 );
    FCML_I64_D( "mov rax,cr2", 0x48, 0x0F, 0x20, 0xD0 );
    FCML_I64( "mov rax,cr2", 0x0F, 0x20, 0xD0 );
    // 0F 22 /r MOV CR0–CR7, r32 A N.E. Valid Move r32 to control register
    // 0F 22 /r MOV CR0–CR7, r64 A Valid N.E. Move r64 to extended control register.
    FCML_I32( "mov cr2,eax", 0x0F, 0x22, 0xD0 );
    FCML_I32_D( "mov cr2,eax", 0x66, 0x0F, 0x22, 0xD0 );
    // REX.R + 0F 22 /0 MOV CR8, r64 A Valid N.E. Move r64 to extended CR8.1
    FCML_I64_D( "mov cr2,rax", 0x66, 0x0F, 0x22, 0xD0 );
    FCML_I64_D( "mov cr2,rax", 0x48, 0x0F, 0x22, 0xD0 );
    FCML_I64( "mov cr2,rax", 0x0F, 0x22, 0xD0 );
    FCML_I32_D( "mov eax,cr0", 0x0F, 0x20, 0xC0 );
    FCML_I32_D( "mov eax,<unknown CR>", 0x0F, 0x20, 0xC8 );
    FCML_I32_D( "mov eax,cr2", 0x0F, 0x20, 0xD0 );
    FCML_I32_D( "mov eax,cr3", 0x0F, 0x20, 0xD8 );
    FCML_I32_D( "mov eax,cr4", 0x0F, 0x20, 0xE0 );
    FCML_I32_D( "mov eax,<unknown CR>", 0x0F, 0x20, 0xE8 );
    FCML_I32_D( "mov eax,<unknown CR>", 0x0F, 0x20, 0xF0 );
    FCML_I32_D( "mov eax,<unknown CR>", 0x0F, 0x20, 0xF8 );
    FCML_I64_D( "mov rax,cr8", 0x44, 0x0F, 0x20, 0xC0 );
    FCML_I64_D( "mov rax,<unknown CR>", 0x44, 0x0F, 0x20, 0xC8 );
    FCML_I64_D( "mov rax,<unknown CR>", 0x44, 0x0F, 0x20, 0xD0 );
    FCML_I64_D( "mov rax,<unknown CR>", 0x44, 0x0F, 0x20, 0xD8 );
    FCML_I64_D( "mov rax,<unknown CR>", 0x44, 0x0F, 0x20, 0xE0 );
    FCML_I64_D( "mov rax,<unknown CR>", 0x44, 0x0F, 0x20, 0xE8 );
    FCML_I64_D( "mov rax,<unknown CR>", 0x44, 0x0F, 0x20, 0xF0 );
    FCML_I64_D( "mov rax,<unknown CR>", 0x44, 0x0F, 0x20, 0xF8 );


    // MOV
    // 88 /r MOV r/m8,r8 A Valid Valid Move r8 to r/m8.
    // REX + 88 /r MOV r/m8***,r8*** A Valid N.E. Move r8 to r/m8.
    FCML_I64_D( "mov byte ptr [rax],dl", 0x48, 0x88, 0x10 );
    FCML_I64( "mov byte ptr [rax],dl", 0x88, 0x10 );
    FCML_I32( "mov byte ptr [eax],dl", 0x88, 0x10 );
    // 89 /r MOV r/m16,r16 A Valid Valid Move r16 to r/m16.
    // 89 /r MOV r/m32,r32 A Valid Valid Move r32 to r/m32.
    // REX.W + 89 /r MOV r/m64,r64 A Valid N.E. Move r64 to r/m64.
    FCML_I64( "mov qword ptr [rax],rdx", 0x48, 0x89, 0x10 );
    FCML_I32( "mov dword ptr [eax],edx", 0x89, 0x10 );
    FCML_I32( "mov word ptr [eax],dx", 0x66, 0x89, 0x10 );
    // 8A /r MOV r8,r/m8 B Valid Valid Move r/m8 to r8.
    // REX + 8A /r MOV r8***,r/m8*** B Valid N.E. Move r/m8 to r8.
    FCML_I64_D( "mov dl,byte ptr [rax]", 0x48, 0x8A, 0x10 );
    FCML_I64( "mov dl,byte ptr [rax]", 0x8A, 0x10 );
    FCML_I32( "mov dl,byte ptr [eax]", 0x8A, 0x10 );
    // 8B /r MOV r16,r/m16 B Valid Valid Move r/m16 to r16.
    // 8B /r MOV r32,r/m32 B Valid Valid Move r/m32 to r32.
    // REX.W + 8B /r MOV r64,r/m64 B Valid N.E. Move r/m64 to r64.
    FCML_I64( "mov rdx,qword ptr [rax]", 0x48, 0x8B, 0x10 );
    FCML_I32( "mov edx,dword ptr [eax]", 0x8B, 0x10 );
    FCML_I32( "mov dx,word ptr [eax]", 0x66, 0x8B, 0x10 );
    // 8C /r MOV r/m16,Sreg** A Valid Valid Move segment register to r/m16.
    FCML_I32( "mov word ptr [eax],ss", 0x8C, 0x10 );
    FCML_I32_A( "mov word ptr [eax],ss", 0x8C, 0x10 );
    FCML_I32( "mov word ptr [eax],ss", 0x66, 0x8C, 0x10 );
    FCML_I64( "mov word ptr [rax],ss", 0x8C, 0x10 );
    // REX.W + 8C /r MOV r/m64,Sreg** A Valid Valid Move zero extended 16-bit segment register to r/m64.
    FCML_I64( "mov qword ptr [rax],ss", 0x48, 0x8C, 0x10 );
    // 8E /r MOV Sreg,r/m16** RM Valid Valid Move r/m16 to segment register.
    FCML_I32( "mov ds,bx", 0x8E, 0xDB );
    // REX.W + 8E /r MOV Sreg,r/m64** RM Valid Valid Move lower 16 bits of r/m64 to segment register.
    FCML_I64( "mov ds,rbx", 0x48, 0x8E, 0xDB );
    // A0 MOV AL,moffs8* C Valid Valid Move byte at (seg:offset) to AL.
    // REX.W + A0 MOV AL,moffs8* C Valid N.E. Move byte at (offset) to AL.
    FCML_I32_M( "mov al,byte ptr [40302010h]", 2, FCML_MI( 0xA0, 0x10, 0x20, 0x30, 0x40 ), FCML_MI( 0x8a, 0x05, 0x10, 0x20, 0x30, 0x40 ) );
    FCML_I32_M( "mov al,byte ptr [2010h]", 2, FCML_MI( 0x67, 0xA0, 0x10, 0x20 ), FCML_MI( 0x67, 0x8a, 0x06, 0x10, 0x20 ) )
    FCML_I64( "mov al,byte ptr [5352515040302010h]", 0xA0, 0x10, 0x20, 0x30, 0x40, 0x50, 0x51, 0x52, 0x53 );
    FCML_I64_M( "mov al,byte ptr [40302010h]", 2, FCML_MI( 0x67, 0xA0, 0x10, 0x20, 0x30, 0x40 ), FCML_MI( 0x67, 0x8a, 0x05, 0x10, 0x20, 0x30, 0x40 ) );
    // A1 MOV AX,moffs16* C Valid Valid Move word at (seg:offset) to AX.
    // A1 MOV EAX,moffs32* C Valid Valid Move doubleword at (seg:offset) to EAX.
    // REX.W + A1 MOV RAX,moffs64* C Valid N.E. Move quadword at (offset) to RAX.
    FCML_I32_M( "mov eax,dword ptr [40302010h]", 2, FCML_MI( 0xA1, 0x10, 0x20, 0x30, 0x40 ), FCML_MI( 0x8b, 0x05, 0x10, 0x20, 0x30, 0x40 ) );
    FCML_I32_M( "mov ax,word ptr [2010h]", 2, FCML_MI( 0x66, 0x67, 0xA1, 0x10, 0x20 ), FCML_MI( 0x66, 0x67, 0x8B, 0x06, 0x10, 0x20 ) );
    FCML_I32_M( "mov ax,word ptr [40302010h]", 2, FCML_MI( 0x66, 0xA1, 0x10, 0x20, 0x30, 0x040 ), FCML_MI( 0x66, 0x8B, 0x05, 0x10, 0x20, 0x30, 0x040 ) );
    FCML_I64( "mov eax,dword ptr [5352515040302010h]", 0xA1, 0x10, 0x20, 0x30, 0x40, 0x50, 0x51, 0x52, 0x53 );
    FCML_I64( "mov ax,word ptr [5352515040302010h]", 0x66, 0xA1, 0x10, 0x20, 0x30, 0x40, 0x50, 0x51, 0x52, 0x53 );
    FCML_I64( "mov rax,qword ptr [5352515040302010h]", 0x48, 0xA1, 0x10, 0x20, 0x30, 0x40, 0x50, 0x51, 0x52, 0x53 );
    FCML_I64_M( "mov ax,word ptr [40302010h]", 2, FCML_MI( 0x66, 0x67, 0xA1, 0x10, 0x20, 0x30, 0x40 ), FCML_MI( 0x66, 0x67, 0x8b, 0x05, 0x10, 0x20, 0x30, 0x40 ) );
    // A2 MOV moffs8,AL D Valid Valid Move AL to (seg:offset).
    // REX.W + A2 MOV moffs8***,AL D Valid N.E. Move AL to (offset).
    FCML_I32_M( "mov byte ptr [40302010h],al", 2, FCML_MI( 0xA2, 0x10, 0x20, 0x30, 0x40 ), FCML_MI( 0x88, 0x05, 0x10, 0x20, 0x30, 0x40 ) );
    FCML_I32_M( "mov byte ptr [2010h],al", 2, FCML_MI( 0x67, 0xA2, 0x10, 0x20 ), FCML_MI( 0x67, 0x88, 0x06, 0x10, 0x20 ) );
    FCML_I64( "mov byte ptr [5352515040302010h],al", 0xA2, 0x10, 0x20, 0x30, 0x40, 0x50, 0x51, 0x52, 0x53 );
    FCML_I64_M( "mov byte ptr [40302010h],al", 2, FCML_MI( 0x67, 0xA2, 0x10, 0x20, 0x30, 0x40 ), FCML_MI( 0x67, 0x88, 0x05, 0x10, 0x20, 0x30, 0x40 ) );
    // A3 MOV moffs16*,AX D Valid Valid Move AX to (seg:offset).
    // A3 MOV moffs32*,EAX D Valid Valid Move EAX to (seg:offset).
    // REX.W + A3 MOV moffs64*,RAX D Valid N.E. Move RAX to (offset).
    FCML_I32_M( "mov dword ptr [40302010h],eax", 2, FCML_MI( 0xA3, 0x10, 0x20, 0x30, 0x40 ), FCML_MI( 0x89, 0x05, 0x10, 0x20, 0x30, 0x40 ) );
    FCML_I32_M( "mov word ptr [2010h],ax", 2, FCML_MI( 0x66, 0x67, 0xA3, 0x10, 0x20 ), FCML_MI( 0x66, 0x67, 0x89, 0x06, 0x10, 0x20  ) );
    FCML_I32_M( "mov word ptr [40302010h],ax", 2, FCML_MI( 0x66, 0xA3, 0x10, 0x20, 0x30, 0x040 ), FCML_MI( 0x66, 0x89, 0x05, 0x10, 0x20, 0x30, 0x040 ) );
    FCML_I64( "mov dword ptr [5352515040302010h],eax", 0xA3, 0x10, 0x20, 0x30, 0x40, 0x50, 0x51, 0x52, 0x53 );
    FCML_I64( "mov word ptr [5352515040302010h],ax", 0x66, 0xA3, 0x10, 0x20, 0x30, 0x40, 0x50, 0x51, 0x52, 0x53 );
    FCML_I64( "mov qword ptr [5352515040302010h],rax", 0x48, 0xA3, 0x10, 0x20, 0x30, 0x40, 0x50, 0x51, 0x52, 0x53 );
    FCML_I64_M( "mov word ptr [40302010h],ax", 2, FCML_MI( 0x66, 0x67, 0xA3, 0x10, 0x20, 0x30, 0x40 ), FCML_MI( 0x66, 0x67, 0x89, 0x05, 0x10, 0x20, 0x30, 0x40 ) );
    // B0+ rb MOV r8, imm8 E Valid Valid Move imm8 to r8.
    // REX + B0+ rb MOV r8***, imm8 E Valid N.E. Move imm8 to r8.
    FCML_I32_M( "mov al,0d0h", 2, FCML_MI( 0xB0, 0xD0 ), FCML_MI( 0xC6, 0xC0, 0xD0 )  );
    FCML_I32_M( "mov cl,0d0h", 2, FCML_MI( 0xB1, 0xD0 ), FCML_MI( 0xC6, 0xC1, 0xD0 ) );
    FCML_I32_M( "mov al,0d0h", 2, FCML_MI( 0x66, 0xB0, 0xD0 ), FCML_MI( 0x66, 0xC6, 0xC0, 0xD0 ) );
    FCML_I64_M( "mov al,0d0h", 2, FCML_MI( 0xB0, 0xD0 ), FCML_MI( 0xC6, 0xC0, 0xD0 ) );
    // B8+ rw MOV r16, imm16 E Valid Valid Move imm16 to r16.
    // B8+ rd MOV r32, imm32 E Valid Valid Move imm32 to r32.
    // REX.W + B8+ rd MOV r64, imm64 E Valid N.E. Move imm64 to r64.
    FCML_I32_M( "mov eax,0d1d0d0d0h", 2, FCML_MI( 0xB8, 0xD0, 0xD0, 0xD0, 0xD1 ), FCML_MI( 0xC7, 0xC0, 0xD0, 0xD0, 0xD0, 0xD1 ) );
    FCML_I32_M( "mov ecx,0d1d0d0d0h", 2 ,FCML_MI( 0xB9, 0xD0, 0xD0, 0xD0, 0xD1 ), FCML_MI( 0xC7, 0xC1, 0xD0, 0xD0, 0xD0, 0xD1 ) );
    FCML_I32_M( "mov ax,0d1d0h", 2, FCML_MI( 0x66, 0xB8, 0xD0, 0xD1 ), FCML_MI( 0x66, 0xc7, 0xc0, 0xd0, 0xd1 ) );
    FCML_I64( "mov rax,0d1d0d0d0d1d0d0d0h", 0x48, 0xB8, 0xD0, 0xD0, 0xD0, 0xD1, 0xD0, 0xD0, 0xD0, 0xD1);
    FCML_I64_M( "mov ax,0d0d0h", 2, FCML_MI( 0x66, 0xB8, 0xD0, 0xD0 ), FCML_MI( 0x66, 0xc7, 0xc0, 0xd0, 0xd0 ) );
    // C6 /0 MOV r/m8, imm8 F Valid Valid Move imm8 to r/m8.
    // REX + C6 /0 MOV r/m8***, imm8 F Valid N.E. Move imm8 to r/m8.
    FCML_I32( "mov byte ptr [eax+00000010h],20h", 0xC6, 0x40, 0x10, 0x20 );
    FCML_I32( "mov byte ptr [eax+00000010h],20h", 0x66, 0xC6, 0x40, 0x10, 0x20  );
    FCML_I32_M( "mov al,20h", 2, FCML_MI( 0x66, 0xC6, 0xc0, 0x20 ), FCML_MI( 0x66, 0xb0, 0x20 ) );
    FCML_I64_D( "mov byte ptr [rax+0000000000000010h],20h", 0x48, 0xC6, 0x40, 0x10, 0x20);
    FCML_I64( "mov byte ptr [rax+0000000000000010h],20h", 0xC6, 0x40, 0x10, 0x20);
    // C7 /0 MOV r/m16, imm16 F Valid Valid Move imm16 to r/m16.
    // C7 /0 MOV r/m32, imm32 F Valid Valid Move imm32 to r/m32.
    // REX.W + C7 /0 MOV r/m64, imm32 F Valid N.E. Move imm32 sign extended to 64-bits to r/m64.
    FCML_I32( "mov dword ptr [eax+00000010h],40302010h", 0xC7, 0x40, 0x10, 0x10, 0x20, 0x30, 0x40 );
    FCML_I32( "mov word ptr [eax+00000010h],2010h", 0x66, 0xC7, 0x40, 0x10, 0x10, 0x20  );
    FCML_I32_M( "mov ax,2010h", 2, FCML_MI( 0x66, 0xb8, 0x10, 0x20 ), FCML_MI( 0x66, 0xc7, 0xc0, 0x10, 0x20 ) );
    FCML_I64( "mov qword ptr [rax+0000000000000010h],0000000040302010h", 0x48, 0xC7, 0x40, 0x10, 0x10, 0x20, 0x30, 0x40 );
    FCML_I64( "mov qword ptr [rbp+rbx*8+0000000040302010h],0ffffffff80706050h", 0x48, 0xC7, 0x84, 0xDD, 0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70, 0x80 );
}

void fcml_tf_instruction_MOVAPD(void) {
    // 66 0F 28 /r MOVAPD xmm1, xmm2/m128 A Valid Valid Move packed doubleprecision floating-point values from xmm2/m128 to xmm1.
    FCML_I64( "movapd xmm0,oword ptr [rax+0000000000000020h]", 0x66, 0x0F, 0x28, 0x40, 0x20 );
    FCML_I64_D( "movapd xmm0,oword ptr [rax+0000000000000020h]", 0x66, 0x48, 0x0F, 0x28, 0x40, 0x20 );
    FCML_I32_M( "movapd xmm0,xmm2", 2, FCML_MI( 0x66, 0x0F, 0x28, 0xC2 ), FCML_MI( 0x66, 0x0f, 0x29, 0xd0 ) );
    FCML_I32( "movapd xmm0,oword ptr [eax+00000020h]", 0x66, 0x0F, 0x28, 0x40, 0x20 );
    // 66 0F 29 /r MOVAPD xmm2/m128, xmm1 B Valid Valid Move packed doubleprecision floating-point values from xmm1 to xmm2/m128.
    FCML_I64( "movapd oword ptr [rax+0000000000000020h],xmm0", 0x66, 0x0F, 0x29, 0x40, 0x20 );
    FCML_I64_D( "movapd oword ptr [rax+0000000000000020h],xmm0", 0x66, 0x48, 0x0F, 0x29, 0x40, 0x20 );
    FCML_I32_M( "movapd xmm2,xmm0", 2, FCML_MI( 0x66, 0x0F, 0x29, 0xC2 ), FCML_MI( 0x66, 0x0f, 0x28, 0xd0 ) );
    FCML_I32( "movapd oword ptr [eax+00000020h],xmm0", 0x66, 0x0F, 0x29, 0x40, 0x20 );
    // VEX.128.66.0F 28 /r VMOVAPD xmm1,xmm2/m128
    // VEX.256.66.0F 28 /r VMOVAPD ymm1,ymm2/m256
    FCML_I3264_M( "vmovapd xmm3,xmm0", 2, FCML_MI( 0xc5, 0xf9, 0x29, 0xc3 ), FCML_MI( 0xc5, 0xf9, 0x28, 0xd8 ) );
    FCML_I32( "vmovapd xmm0,oword ptr [eax]", 0xc5, 0xf9, 0x28, 0x00 );
    // VEX.128.66.0F 29 /r VMOVAPD xmm2/m128,xmm1
    // VEX.256.66.0F 29 /r VMOVAPD ymm2/m256,ymm1
    FCML_I64_M( "vmovapd xmm0,xmm3", 2, FCML_MI( 0xc5, 0xf9, 0x29, 0xd8 ), FCML_MI( 0xc5, 0xf9, 0x28, 0xc3 ) );
    FCML_I32_M( "vmovapd xmm0,xmm3", 2, FCML_MI( 0xc5, 0xf9, 0x29, 0xd8 ), FCML_MI( 0xc5, 0xf9, 0x28, 0xc3 ) );
    FCML_I32( "vmovapd oword ptr [eax],xmm0", 0xc5, 0xf9, 0x29, 0x00 );
}

void fcml_tf_instruction_MOVAPS(void) {
    // 66 0F 28 /r MOVAPD xmm1, xmm2/m128 A Valid Valid Move packed doubleprecision floating-point values from xmm2/m128 to xmm1.
    FCML_I64( "movaps xmm0,oword ptr [rax+0000000000000020h]", 0x0F, 0x28, 0x40, 0x20 );
    FCML_I32_M( "movaps xmm0,xmm2", 2, FCML_MI( 0x0f, 0x29, 0xd0 ), FCML_MI( 0x0f, 0x28, 0xc2 ) );
    FCML_I32( "movaps xmm0,oword ptr [eax+00000020h]", 0x0F, 0x28, 0x40, 0x20 );
    // 66 0F 29 /r MOVAPD xmm2/m128, xmm1 B Valid Valid Move packed doubleprecision floating-point values from xmm1 to xmm2/m128.
    FCML_I64( "movaps oword ptr [rax+0000000000000020h],xmm0", 0x0F, 0x29, 0x40, 0x20 );
    FCML_I32_M( "movaps xmm2,xmm0", 2, FCML_MI( 0x0f, 0x29, 0xc2 ), FCML_MI( 0x0f, 0x28, 0xd0 ) );
    FCML_I32( "movaps oword ptr [eax+00000020h],xmm0", 0x0F, 0x29, 0x40, 0x20 );
    // VEX.128.0F 28 /r VMOVAPS xmm1,xmm2/m128
    // VEX.256.0F 28 /r VMOVAPS ymm1,ymm2/m256
    FCML_I64_M( "vmovaps xmm3,xmm0", 2, FCML_MI( 0xc5, 0xf8, 0x29, 0xc3 ), FCML_MI( 0xc5, 0xf8, 0x28, 0xd8 ) );
    FCML_I32_M( "vmovaps xmm3,xmm0", 2, FCML_MI( 0xc5, 0xf8, 0x29, 0xc3 ), FCML_MI( 0xc5, 0xf8, 0x28, 0xd8 ) );
    FCML_I32_M( "vmovaps ymm3,ymm0", 2, FCML_MI( 0xc5, 0xfc, 0x29, 0xc3 ), FCML_MI( 0xc5, 0xfc, 0x28, 0xd8 ) );
    FCML_I32( "vmovaps xmm0,oword ptr [eax]", 0xc5, 0xf8, 0x28, 0x00 );
    // VEX.128.0F 29 /r VMOVAPS xmm2/m128,xmm1
    // VEX.256.0F 29 /r VMOVAPS ymm2/m256,ymm1
    FCML_I64_M( "vmovaps xmm0,xmm3", 2, FCML_MI( 0xc5, 0xf8, 0x29, 0xd8 ), FCML_MI( 0xc5, 0xf8, 0x28, 0xc3 ) );
    FCML_I32_M( "vmovaps xmm0,xmm3", 2, FCML_MI( 0xc5, 0xf8, 0x29, 0xd8 ), FCML_MI( 0xc5, 0xf8, 0x28, 0xc3 ) );
    FCML_I32( "vmovaps oword ptr [eax],xmm0", 0xc5, 0xf8, 0x29, 0x00 );
    FCML_I32( "vmovaps ymmword ptr [eax],ymm0", 0xc5, 0xfc, 0x29, 0x00 );
}

void fcml_tf_instruction_MOVBE(void) {
    // 0F 38 F0 /r MOVBE r16, m16 A Valid Valid Reverse byte order in m16 and move to r16
    // 0F 38 F0 /r MOVBE r32, m32 A Valid Valid Reverse byte order in m32 and move to r32
    // REX.W + 0F 38 F0 /r MOVBE r64, m64 A Valid N.E. Reverse byte order in m64 and move to r64.
    FCML_I64( "movbe edx,dword ptr [rax]", 0x0F, 0x38, 0xF0, 0x10 );
    FCML_I64( "movbe rdx,qword ptr [rax]", 0x48, 0x0F, 0x38, 0xF0, 0x10 );
    FCML_I32_FAILED( "movbe eax,edx", 0x0F, 0x38, 0xF0, 0xC2 );
    FCML_I32( "movbe dx,word ptr [eax]", 0x66, 0x0F, 0x38, 0xF0, 0x10 );
    // 0F 38 F1 /r MOVBE m16, r16 B Valid Valid Reverse byte order in r16 and move to m16
    // 0F 38 F1 /r MOVBE m32, r32 B Valid Valid Reverse byte order in r32 and move to m32
    // REX.W + 0F 38 F1 /r MOVBE m64, r64 B Valid N.E. Reverse byte order in
    FCML_I64( "movbe dword ptr [rax],edx", 0x0F, 0x38, 0xF1, 0x10 );
    FCML_I64( "movbe qword ptr [rax],rdx", 0x48, 0x0F, 0x38, 0xF1, 0x10 );
    FCML_I32_FAILED( "movbe edx,eax", 0x0F, 0x38, 0xF1, 0xC2 );
    FCML_I32( "movbe word ptr [eax],dx", 0x66, 0x0F, 0x38, 0xF1, 0x10 );
}

void fcml_tf_instruction_MOVD(void) {
    // 0F 6E /r MOVD mm,r/m32 A Valid Valid Move doubleword from r/m32 to mm.
    FCML_I32( "movd mm2,dword ptr [eax]", 0x0F, 0x6E, 0x10 );
    FCML_I64( "movd mm2,dword ptr [rax]", 0x0F, 0x6E, 0x10 );
    // REX.W + 0F 6E /r MOVQ mm, r/m64 A Valid N.E. Move quadword from r/m64 to mm.
    FCML_I64_A( "movq mm2,mmword ptr [rax]", 0x0f, 0x6f, 0x10 );
    FCML_I64_M( "movq mm2,qword ptr [rax]", 2, FCML_MI( 0x0f, 0x6f, 0x10 ), FCML_MI( 0x48, 0x0f, 0x6e, 0x10 ) );
    // 0F 7E /r MOVD r/m32, mm B Valid Valid Move doubleword from mm to r/m32.
    FCML_I32( "movd dword ptr [eax],mm2", 0x0F, 0x7E, 0x10 );
    FCML_I64( "movd dword ptr [rax],mm2", 0x0F, 0x7E, 0x10 );
    // REX.W + 0F 7E /r MOVQ r/m64, mm B Valid N.E. Move quadword from mm to r/m64.
    FCML_I64_M( "movq qword ptr [rax],mm2", 2, FCML_MI( 0x0f, 0x7f, 0x10 ), FCML_MI( 0x48, 0x0f, 0x7e, 0x10 ) );
    FCML_I64_A( "movq mmword ptr [rax],mm2", 0x0f, 0x7f, 0x10 );
    // 66 0F 6E /r MOVD xmm, r/m32 A Valid Valid Move doubleword from r/m32 to xmm.
    FCML_I32( "movd xmm2,dword ptr [eax]", 0x66, 0x0F, 0x6E, 0x10 );
    FCML_I64( "movd xmm2,dword ptr [rax]", 0x66, 0x0F, 0x6E, 0x10 );
    // 66 REX.W 0F 6E /r MOVQ xmm, r/m64 A Valid N.E. Move quadword from r/m64 to xmm.
    FCML_I64_M( "movq xmm2,qword ptr [rax]", 2, FCML_MI( 0xf3, 0x0f, 0x7e, 0x10 ), FCML_MI( 0x66, 0x48, 0x0f, 0x6e, 0x10 ) );
    FCML_I64_A( "movq xmm2,mmword ptr [rax]", 0xf3, 0x0f, 0x7e, 0x10 );
    // 66 0F 7E /r MOVD r/m32, xmm B Valid Valid Move doubleword from xmm register to r/m32.
    FCML_I32( "movd dword ptr [eax],xmm2", 0x66, 0x0F, 0x7E, 0x10 );
    FCML_I64( "movd dword ptr [rax],xmm2", 0x66, 0x0F, 0x7E, 0x10 );
    // 66 REX.W 0F 7E /r MOVQ r/m64, xmm B Valid N.E. Move quadword from xmm register to r/m64.
    FCML_I64_M( "movq qword ptr [rax],xmm2", 2, FCML_MI( 0x66, 0x0f, 0xd6, 0x10 ), FCML_MI( 0x66, 0x48, 0x0f, 0x7e, 0x10 ) );
    // VEX.128.66.0F.W0 6E /r VMOVD xmm1,r32/m32
    FCML_I32( "vmovd xmm2,dword ptr [ecx+eax]", 0xc5, 0xf9, 0x6e, 0x14, 0x01 );
    // VEX.128.66.0F.W1 6E /r VMOVQ xmm1,r64/m64
    FCML_I64_M( "vmovq xmm2,qword ptr [rcx+rax]", 2, FCML_MI( 0xc5, 0xfa, 0x7e, 0x14, 0x01 ), FCML_MI( 0xc4, 0xe1, 0xf9, 0x6e, 0x14, 0x01 ) );
    // VEX.128.66.0F.W0 7E /r VMOVD r32/m32,xmm1
    FCML_I32( "vmovd dword ptr [ecx+eax],xmm2", 0xc5, 0xf9, 0x7e, 0x14, 0x01 );
    // VEX.128.66.0F.W1 7E /r VMOVQ r64/m64,xmm1
    FCML_I64_M( "vmovq qword ptr [rcx+rax],xmm2", 2, FCML_MI( 0xc5, 0xfa, 0xd6, 0x14, 0x01 ), FCML_MI( 0xc4, 0xe1, 0xf9, 0x7e, 0x14, 0x01 ) );
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
    { "fcml_tf_instruction_MONITOR", fcml_tf_instruction_MONITOR },
    { "fcml_tf_instruction_MOV", fcml_tf_instruction_MOV },
    { "fcml_tf_instruction_MOVAPD", fcml_tf_instruction_MOVAPD },
    { "fcml_tf_instruction_MOVAPS", fcml_tf_instruction_MOVAPS },
    { "fcml_tf_instruction_MOVBE", fcml_tf_instruction_MOVBE },
    { "fcml_tf_instruction_MOVD", fcml_tf_instruction_MOVD },
    CU_TEST_INFO_NULL,
};

CU_SuiteInfo fctl_si_instructions_m[] = {
    { "suite-fctl_ti_instructions_m", fcml_tf_instructions_m_suite_init, fcml_tf_instructions_m_suite_cleanup, fctl_ti_instructions_m },
    CU_SUITE_INFO_NULL,
};
