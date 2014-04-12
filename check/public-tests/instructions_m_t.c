/*
 * instructions.c
 *
 *  Created on: 01-06-2013
 *      Author: tAs
 */

#include <fcml_assembler.h>
#include "instructions_m_t.h"
#include "instructions_base_t.h"

void fcml_tf_instructions_m_suite_init(void) {
}

void fcml_tf_instructions_m_suite_cleanup(void) {
}

void fcml_tf_instruction_MASKMOVQ(void) {
    FCML_I64( "maskmovq mm3,mm0", 0x0F, 0xF7, 0xD8 );
    FCML_I32( "maskmovq mm4,mm0", 0x0F, 0xF7, 0xE0 );
    FCML_I32_FAILED( "FAIL", 0x0F, 0xF7, 0x40, 0x20 );
    /* GAS*/
    FCML_A64( "maskmovq %mm0,%mm3", 0x0f, 0xf7, 0xd8 );
}

void fcml_tf_instruction_MASKMOVDQU(void) {
    FCML_I64( "maskmovdqu xmm3,xmm0", 0x66, 0x0F, 0xF7, 0xD8 );
    FCML_I32( "maskmovdqu xmm4,xmm0", 0x66, 0x0F, 0xF7, 0xE0 );
    FCML_I32_FAILED( "FAIL", 0x66, 0x0F, 0xF7, 0x40, 0x20 );
    /* VEX.128.66.0F F7 /r VMASKMOVDQU xmm1,xmm2*/
	FCML_I3264( "vmaskmovdqu xmm3,xmm0", 0xc5, 0xf9, 0xf7, 0xd8 );
	/* GAS*/
	FCML_A3264( "maskmovdqu %xmm0,%xmm3", 0x66, 0x0f, 0xf7, 0xd8 );
	FCML_A3264( "vmaskmovdqu %xmm0,%xmm3", 0xc5, 0xf9, 0xf7, 0xd8 );
}

void fcml_tf_instruction_MAXPD(void) {
    FCML_I64( "maxpd xmm0,xmmword ptr [rax+0000000000000020h]", 0x66, 0x0F, 0x5F, 0x40, 0x20 );
    FCML_I32( "maxpd xmm0,xmm2", 0x66, 0x0F, 0x5F, 0xC2 );
    FCML_I32( "maxpd xmm0,xmmword ptr [eax+00000020h]", 0x66, 0x0F, 0x5F, 0x40, 0x20 );
    /* VEX.NDS.128.66.0F 5F /r VMAXPD xmm1,xmm2,xmm3/m128*/
    /* VEX.NDS.256.66.0F 5F /r VMAXPD ymm1,ymm2,ymm3/m256*/
    FCML_I64( "vmaxpd xmm3,xmm0,xmm0", 0xc5, 0xf9, 0x5f, 0xd8 );
    FCML_I32( "vmaxpd ymm3,ymm0,ymm0", 0xc5, 0xfd, 0x5f, 0xd8 );
    FCML_I32( "vmaxpd ymm3,ymm3,ymmword ptr [eax]", 0xc5, 0xe5, 0x5f, 0x18 );
    /* GAS*/
    FCML_A64( "maxpd 0x0000000000000020(%rax),%xmm0", 0x66, 0x0f, 0x5f, 0x40, 0x20 );
    FCML_A64( "vmaxpd %xmm0,%xmm0,%xmm3", 0xc5, 0xf9, 0x5f, 0xd8 );
}

void fcml_tf_instruction_MAXPS(void) {
    FCML_I64( "maxps xmm0,xmmword ptr [rax+0000000000000020h]", 0x0F, 0x5F, 0x40, 0x20 );
    FCML_I32( "maxps xmm0,xmm2", 0x0F, 0x5F, 0xC2 );
    FCML_I32( "maxps xmm0,xmmword ptr [eax+00000020h]", 0x0F, 0x5F, 0x40, 0x20 );
    /* VEX.NDS.128.0F 5F /r VMAXPS xmm1,xmm2,xmm3/m128*/
    /* VEX.NDS.256.0F 5F /r VMAXPS ymm1,ymm2,ymm3/m256*/
    FCML_I64( "vmaxps xmm3,xmm0,xmm0", 0xc5, 0xf8, 0x5f, 0xd8 );
    FCML_I32( "vmaxps ymm3,ymm0,ymm0", 0xc5, 0xfc, 0x5f, 0xd8 );
    FCML_I32( "vmaxps ymm3,ymm3,ymmword ptr [eax]", 0xc5, 0xe4, 0x5f, 0x18 );
    /* GAS*/
    FCML_A64( "maxps 0x0000000000000020(%rax),%xmm0", 0x0f, 0x5f, 0x40, 0x20 );
    FCML_A64( "vmaxps %xmm0,%xmm0,%xmm3", 0xc5, 0xf8, 0x5f, 0xd8 );
}

void fcml_tf_instruction_MAXSD(void) {
    FCML_I64( "maxsd xmm0,mmword ptr [rax+0000000000000020h]", 0xF2, 0x0F, 0x5F, 0x40, 0x20 );
    FCML_I32( "maxsd xmm0,xmm2", 0xF2, 0x0F, 0x5F, 0xC2 );
    FCML_I32( "maxsd xmm0,mmword ptr [eax+00000020h]", 0xF2, 0x0F, 0x5F, 0x40, 0x20 );
    /* VEX.NDS.128.F2.0F 5F /r VMAXSD xmm1,xmm2,xmm3/m64*/
    FCML_I64( "vmaxsd xmm3,xmm3,xmm0", 0xc5, 0xe3, 0x5f, 0xd8 );
    FCML_I32( "vmaxsd xmm3,xmm7,xmm0", 0xc5, 0xc3, 0x5f, 0xd8 );
    FCML_I32_A( "vmaxsd long_form xmm3,xmm7,xmm0", 0xc4, 0xe1, 0x43, 0x5f, 0xd8 );
    FCML_I32( "vmaxsd xmm3,xmm0,mmword ptr [eax]", 0xc5, 0xfb, 0x5f, 0x18 );
    /* GAS*/
    FCML_A64( "maxsd 0x0000000000000020(%rax),%xmm0", 0xf2, 0x0f, 0x5f, 0x40, 0x20 );
    FCML_A64( "vmaxsd %xmm0,%xmm3,%xmm3", 0xc5, 0xe3, 0x5f, 0xd8 );
}

void fcml_tf_instruction_MAXSS(void) {
    FCML_I64( "maxss xmm0,dword ptr [rax+0000000000000020h]", 0xF3, 0x0F, 0x5F, 0x40, 0x20 );
    FCML_I32( "maxss xmm0,xmm2", 0xF3, 0x0F, 0x5F, 0xC2 );
    FCML_I32( "maxss xmm0,dword ptr [eax+00000020h]", 0xF3, 0x0F, 0x5F, 0x40, 0x20 );
    /* VEX.NDS.128.F3.0F 5F /r VMAXSS xmm1, xmm2, xmm3/m32*/
    FCML_I64( "vmaxss xmm3,xmm3,xmm0", 0xc5, 0xe2, 0x5f, 0xd8 );
    FCML_I32( "vmaxss xmm3,xmm7,xmm0", 0xc5, 0xc2, 0x5f, 0xd8 );
    FCML_I32( "vmaxss xmm3,xmm0,dword ptr [eax]", 0xc5, 0xfa, 0x5f, 0x18 );
    /* GAS*/
    FCML_A64( "maxss 0x0000000000000020(%rax),%xmm0", 0xf3, 0x0f, 0x5f, 0x40, 0x20 );
    FCML_A64( "vmaxss %xmm0,%xmm3,%xmm3", 0xc5, 0xe2, 0x5f, 0xd8 );
}

void fcml_tf_instruction_MFENCE(void) {
    FCML_I3264( "mfence", 0x0F, 0xAE, 0xF0 );
    /* GAS*/
    FCML_A64( "mfence", 0x0f, 0xae, 0xf0 );
}

void fcml_tf_instruction_MINPD(void) {
    FCML_I64( "minpd xmm0,xmmword ptr [rax+0000000000000020h]", 0x66, 0x0F, 0x5D, 0x40, 0x20 );
    FCML_I32( "minpd xmm0,xmm2", 0x66, 0x0F, 0x5D, 0xC2 );
    FCML_I32( "minpd xmm0,xmmword ptr [eax+00000020h]", 0x66, 0x0F, 0x5D, 0x40, 0x20 );
    /* VEX.NDS.128.66.0F 5D /r VMINPD xmm1,xmm2,xmm3/m128*/
    /* VEX.NDS.256.66.0F 5D /r VMINPD ymm1,ymm2,ymm3/m256*/
    FCML_I64( "vminpd xmm3,xmm0,xmm0", 0xc5, 0xf9, 0x5d, 0xd8 );
    FCML_I32( "vminpd ymm3,ymm0,ymm0", 0xc5, 0xfd, 0x5d, 0xd8 );
    FCML_I32( "vminpd ymm3,ymm3,ymmword ptr [eax]", 0xc5, 0xe5, 0x5d, 0x18 );
    /* GAS*/
    FCML_A64( "minpd 0x0000000000000020(%rax),%xmm0", 0x66, 0x0f, 0x5d, 0x40, 0x20 );
    FCML_A64( "vminpd %xmm0,%xmm0,%xmm3", 0xc5, 0xf9, 0x5d, 0xd8 );
}

void fcml_tf_instruction_MINPS(void) {
    FCML_I64( "minps xmm0,xmmword ptr [rax+0000000000000020h]", 0x0F, 0x5D, 0x40, 0x20 );
    FCML_I32( "minps xmm0,xmm2", 0x0F, 0x5D, 0xC2 );
    FCML_I32( "minps xmm0,xmmword ptr [eax+00000020h]", 0x0F, 0x5D, 0x40, 0x20 );
    /* VEX.NDS.128.0F 5D /r VMINPS xmm1,xmm2,xmm3/m128*/
    /* VEX.NDS.256.0F 5D /r VMINPS ymm1,ymm2,ymm3/m256*/
    FCML_I64( "vminps xmm3,xmm0,xmm0", 0xc5, 0xf8, 0x5d, 0xd8 );
    FCML_I32( "vminps ymm3,ymm0,ymm0", 0xc5, 0xfc, 0x5d, 0xd8 );
    FCML_I32( "vminps ymm3,ymm3,ymmword ptr [eax]", 0xc5, 0xe4, 0x5d, 0x18 );
    /*GAS*/
    FCML_A64( "minps 0x0000000000000020(%rax),%xmm0", 0x0f, 0x5d, 0x40, 0x20 );
    FCML_A64( "vminps %xmm0,%xmm0,%xmm3", 0xc5, 0xf8, 0x5d, 0xd8 );
}

void fcml_tf_instruction_MINSD(void) {
    FCML_I64( "minsd xmm0,mmword ptr [rax+0000000000000020h]", 0xF2, 0x0F, 0x5D, 0x40, 0x20 );
    FCML_I32( "minsd xmm0,xmm2", 0xF2, 0x0F, 0x5D, 0xC2 );
    FCML_I32( "minsd xmm0,mmword ptr [eax+00000020h]", 0xF2, 0x0F, 0x5D, 0x40, 0x20 );
    /* VEX.NDS.128.F2.0F 5D /r VMINSD xmm1, xmm2, xmm3/m64*/
    FCML_I64( "vminsd xmm3,xmm0,xmm0", 0xc5, 0xfb, 0x5d, 0xd8 );
    FCML_I32( "vminsd xmm3,xmm0,xmm0", 0xc5, 0xfb, 0x5d, 0xd8 );
    FCML_I32( "vminsd xmm3,xmm3,mmword ptr [eax]", 0xc5, 0xe3, 0x5d, 0x18 );
    /* GAS*/
    FCML_A64( "minsd 0x0000000000000020(%rax),%xmm0", 0xf2, 0x0f, 0x5d, 0x40, 0x20 );
    FCML_A64( "vminsd %xmm0,%xmm0,%xmm3", 0xc5, 0xfb, 0x5d, 0xd8 );
}

void fcml_tf_instruction_MINSS(void) {
    FCML_I64( "minss xmm0,dword ptr [rax+0000000000000020h]", 0xF3, 0x0F, 0x5D, 0x40, 0x20 );
    FCML_I32( "minss xmm0,xmm2", 0xF3, 0x0F, 0x5D, 0xC2 );
    FCML_I32( "minss xmm0,dword ptr [eax+00000020h]", 0xF3, 0x0F, 0x5D, 0x40, 0x20 );
    /* VEX.NDS.128.F3.0F 5D /r VMINSS xmm1,xmm2,xmm3/m32*/
    FCML_I64( "vminss xmm3,xmm0,xmm0", 0xc5, 0xfa, 0x5d, 0xd8 );
    FCML_I32( "vminss xmm3,xmm0,xmm0", 0xc5, 0xfa, 0x5d, 0xd8 );
    /* GAS*/
    FCML_A64( "minss 0x0000000000000020(%rax),%xmm0", 0xf3, 0x0f, 0x5d, 0x40, 0x20 );
    FCML_A64( "vminss %xmm0,%xmm0,%xmm3", 0xc5, 0xfa, 0x5d, 0xd8 );
}

void fcml_tf_instruction_MONITOR(void) {
    FCML_I64( "monitor rax,rcx,rdx", 0x0F, 0x01, 0xC8 );
    FCML_I32_A( "monitor", 0x0F, 0x01, 0xC8 );
    /* GAS*/
    FCML_A64( "monitor %rax,%rcx,%rdx", 0x0f, 0x01, 0xc8 );
    FCML_I32_A( "monitor", 0x0F, 0x01, 0xC8 );
}

void fcml_tf_instruction_MOV(void) {
    /* 0F 21/r MOV r32, DR0�DR7 A N.E. Valid Move debug register to r32*/
    FCML_I32( "mov eax,dr2", 0x0F, 0x21, 0xD0 );
    FCML_I32( "mov eax,dr2", 0x66, 0x0F, 0x21, 0xD0 );
    /* 0F 21/r MOV r64, DR0�DR7 A Valid N.E. Move extended debug register to r64.*/
    FCML_I64_D( "mov rax,dr2", 0x66, 0x0F, 0x21, 0xD0 );
    FCML_I64_D( "mov rax,dr2", 0x48, 0x0F, 0x21, 0xD0 );
    FCML_I64( "mov rax,dr2", 0x0F, 0x21, 0xD0 );
    /* 0F 23 /r MOV DR0�DR7, r32 A N.E. Valid Move r32 to debug register*/
    FCML_I32( "mov dr2,eax", 0x0F, 0x23, 0xD0 );
    FCML_I32( "mov dr2,eax", 0x66, 0x0F, 0x23, 0xD0 );
    /* 0F 23 /r MOV DR0�DR7, r64 A Valid N.E. Move r64 to extended debug register.*/
    FCML_I64_D( "mov dr2,rax", 0x66, 0x0F, 0x23, 0xD0 );
    FCML_I64_D( "mov dr2,rax", 0x48, 0x0F, 0x23, 0xD0 );
    FCML_I64( "mov dr2,rax", 0x0F, 0x23, 0xD0 );

    /* GAS*/
    FCML_A64( "mov %db2,%rax", 0x0f, 0x21, 0xd0 );
    FCML_A64( "mov %rax,%db2", 0x0f, 0x23, 0xd0 );

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
    /* MOV (CR)*/
    /* 0F 20/r MOV r32, CR0�CR7 A N.E. Valid Move control register to r32*/
    /* 0F 20/r MOV r64, CR0�CR7 A Valid N.E. Move extended control register to r64.*/
    FCML_I32( "mov eax,cr2", 0x0F, 0x20, 0xD0 );
    FCML_I32( "mov eax,cr2", 0x66, 0x0F, 0x20, 0xD0 );
    /* REX.R + 0F 20 /0 MOV r64, CR8 A Valid N.E. Move extended CR8 to r64.1*/
    FCML_I64_D( "mov rax,cr2", 0x66, 0x0F, 0x20, 0xD0 );
    FCML_I64_D( "mov rax,cr2", 0x48, 0x0F, 0x20, 0xD0 );
    FCML_I64( "mov rax,cr2", 0x0F, 0x20, 0xD0 );
    /* 0F 22 /r MOV CR0�CR7, r32 A N.E. Valid Move r32 to control register*/
    /* 0F 22 /r MOV CR0�CR7, r64 A Valid N.E. Move r64 to extended control register.*/
    FCML_I32( "mov cr2,eax", 0x0F, 0x22, 0xD0 );
    FCML_I32_D( "mov cr2,eax", 0x66, 0x0F, 0x22, 0xD0 );
    /* REX.R + 0F 22 /0 MOV CR8, r64 A Valid N.E. Move r64 to extended CR8.1*/
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

    FCML_A64( "mov %cr2,%rax", 0x0f, 0x20, 0xd0 );
    FCML_A64( "mov %rax,%cr2", 0x0f, 0x22, 0xd0 );

    /* MOV*/
    /* 88 /r MOV r/m8,r8 A Valid Valid Move r8 to r/m8.*/
    /* REX + 88 /r MOV r/m8***,r8*** A Valid N.E. Move r8 to r/m8.*/
    FCML_I64_D( "mov byte ptr [rax],dl", 0x48, 0x88, 0x10 );
    FCML_I64( "mov byte ptr [rax],dl", 0x88, 0x10 );
    FCML_I32( "mov byte ptr [eax],dl", 0x88, 0x10 );
    FCML_I32( "xrelease mov byte ptr [eax],dl", 0xF3, 0x88, 0x10 );
    FCML_I32_A_FAILED( "xacquire mov byte ptr [eax],dl", 0xF2, 0x88, 0x10 );
    /* GAS*/
    FCML_A64( "mov %dl,(%rax)", 0x88, 0x10 );
    FCML_A64( "xrelease mov %dl,(%rax)", 0xf3, 0x88, 0x10 );
    /* 89 /r MOV r/m16,r16 A Valid Valid Move r16 to r/m16.*/
    /* 89 /r MOV r/m32,r32 A Valid Valid Move r32 to r/m32.*/
    /* REX.W + 89 /r MOV r/m64,r64 A Valid N.E. Move r64 to r/m64.*/
    FCML_I64( "mov qword ptr [rax],rdx", 0x48, 0x89, 0x10 );
    FCML_I32( "mov dword ptr [eax],edx", 0x89, 0x10 );
    FCML_I32( "mov word ptr [eax],dx", 0x66, 0x89, 0x10 );
    FCML_I32( "xrelease mov word ptr [eax],dx", 0xF3, 0x66, 0x89, 0x10 );
    FCML_I32_A_FAILED( "xacquire mov word ptr [eax],dx", 0xF2, 0x66, 0x89, 0x10 );
    /* GAS*/
    FCML_A64( "mov %rdx,(%rax)", 0x48, 0x89, 0x10 );
    FCML_A64( "xrelease mov %dx,(%rax)", 0xf3, 0x66, 0x89, 0x10 );
    /* 8A /r MOV r8,r/m8 B Valid Valid Move r/m8 to r8.*/
    /* REX + 8A /r MOV r8***,r/m8*** B Valid N.E. Move r/m8 to r8.*/
    FCML_I64_D( "mov dl,byte ptr [rax]", 0x48, 0x8A, 0x10 );
    FCML_I64( "mov dl,byte ptr [rax]", 0x8A, 0x10 );
    FCML_I32( "mov dl,byte ptr [eax]", 0x8A, 0x10 );
    /* GAS*/
    FCML_A64( "mov (%rax),%dl", 0x8a, 0x10 );
    /* 8B /r MOV r16,r/m16 B Valid Valid Move r/m16 to r16.*/
    /* 8B /r MOV r32,r/m32 B Valid Valid Move r/m32 to r32.*/
    /* REX.W + 8B /r MOV r64,r/m64 B Valid N.E. Move r/m64 to r64.*/
    FCML_I64( "mov rdx,qword ptr [rax]", 0x48, 0x8B, 0x10 );
    FCML_I32( "mov edx,dword ptr [eax]", 0x8B, 0x10 );
    FCML_I32( "mov dx,word ptr [eax]", 0x66, 0x8B, 0x10 );
    /* GAS*/
    FCML_A64( "mov (%rax),%rdx", 0x48, 0x8b, 0x10 );
    FCML_A64( "mov (%rax),%edx", 0x8b, 0x10 );
    /* 8C /r MOV r/m16,Sreg** A Valid Valid Move segment register to r/m16.*/
    FCML_I32( "mov eax,ss", 0x8C, 0xD0 );
    FCML_I32( "mov ax,ss", 0x66, 0x8C, 0xD0 );
    FCML_I64( "mov rax,ss", 0x48, 0x8C, 0xD0 );
    FCML_I32( "mov word ptr [eax],ss", 0x8C, 0x10 );
    FCML_I32_A( "mov word ptr [eax],ss", 0x8C, 0x10 );
    FCML_I32( "mov word ptr [eax],ss", 0x66, 0x8C, 0x10 );
    FCML_I64( "mov word ptr [rax],ss", 0x8C, 0x10 );
    /* GAS*/
    FCML_A32( "mov %ss,%eax", 0x8C, 0xD0 );
	FCML_A32( "mov %ss,%ax", 0x66, 0x8C, 0xD0 );
	FCML_A64( "mov %ss,%rax", 0x48, 0x8C, 0xD0 );
	FCML_A64( "mov %ss,(%rax)", 0x8C, 0x10 );
    /* REX.W + 8C /r MOV r/m64,Sreg** A Valid Valid Move zero extended 16-bit segment register to r/m64.*/
    FCML_I64( "mov rax,ss", 0x48, 0x8C, 0xD0 );
    /* 8E /r MOV Sreg,r/m16** RM Valid Valid Move r/m16 to segment register.*/
    FCML_I32( "mov ds,bx", 0x8E, 0xDB );
    /* REX.W + 8E /r MOV Sreg,r/m64** RM Valid Valid Move lower 16 bits of r/m64 to segment register.*/
    FCML_I64( "mov ds,bx", 0x8E, 0xDB );
    FCML_I64( "mov ds,word ptr [rbx]", 0x8E, 0x1B );
    FCML_I64_A( "mov ds,[rbx]", 0x8E, 0x1B );
    FCML_I64_A_FAILED( "mov ds,ebx", 0x8E, 0xDB );
    FCML_I64_A_FAILED( "mov ds,rbx", 0x48, 0x8E, 0xDB );
    /* GAS*/
    FCML_A32( "mov %bx,%ds", 0x8e, 0xdb );
    /* A0 MOV AL,moffs8* C Valid Valid Move byte at (seg:offset) to AL.*/
    /* REX.W + A0 MOV AL,moffs8* C Valid N.E. Move byte at (offset) to AL.*/
    FCML_I32_M( "mov al,byte ptr [40302010h]", 2, FCML_MI( 0xA0, 0x10, 0x20, 0x30, 0x40 ), FCML_MI( 0x8a, 0x05, 0x10, 0x20, 0x30, 0x40 ) );
    FCML_I32_M( "mov al,byte ptr [2010h]", 2, FCML_MI( 0x67, 0xA0, 0x10, 0x20 ), FCML_MI( 0x67, 0x8a, 0x06, 0x10, 0x20 ) );
    FCML_I64( "mov al,byte ptr [5352515040302010h]", 0xA0, 0x10, 0x20, 0x30, 0x40, 0x50, 0x51, 0x52, 0x53 );
    FCML_I64_M( "mov al,byte ptr [40302010h]", 2, FCML_MI( 0x67, 0xa0, 0x10, 0x20, 0x30, 0x40 ), FCML_MI( 0x67, 0x8a, 0x04, 0x25, 0x10, 0x20, 0x30, 0x40 ) );
    /* GAS*/
    FCML_A64( "movabs 0x5352515040302010,%al", 0xa0, 0x10, 0x20, 0x30, 0x40, 0x50, 0x51, 0x52, 0x53 );
    FCML_A64( "movabs 0x0000000089482010,%al", 0xa0, 0x10, 0x20, 0x48, 0x89, 0x00, 0x00, 0x00, 0x00 );
    FCML_A64_M( "mov 0x89482010,%al", 2, FCML_MI( 0x67, 0xa0, 0x10, 0x20, 0x48, 0x89 ), FCML_MI( 0x67, 0x8a, 0x04, 0x25, 0x10, 0x20, 0x48, 0x89 ) );
    FCML_A32_M_A( "mov 0x89482010,%al", 2, FCML_MI( 0xa0, 0x10, 0x20, 0x48, 0x89 ), FCML_MI( 0x8a, 0x05, 0x10, 0x20, 0x48, 0x89 ) );
    /* A1 MOV AX,moffs16* C Valid Valid Move word at (seg:offset) to AX.*/
    /* A1 MOV EAX,moffs32* C Valid Valid Move doubleword at (seg:offset) to EAX.*/
    /* REX.W + A1 MOV RAX,moffs64* C Valid N.E. Move quadword at (offset) to RAX.*/
    FCML_I32_M( "mov eax,dword ptr [40302010h]", 2, FCML_MI( 0xA1, 0x10, 0x20, 0x30, 0x40 ), FCML_MI( 0x8b, 0x05, 0x10, 0x20, 0x30, 0x40 ) );
    FCML_I32_M( "mov ax,word ptr [2010h]", 2, FCML_MI( 0x66, 0x67, 0xA1, 0x10, 0x20 ), FCML_MI( 0x66, 0x67, 0x8B, 0x06, 0x10, 0x20 ) );
    FCML_I32_M( "mov ax,word ptr [40302010h]", 2, FCML_MI( 0x66, 0xA1, 0x10, 0x20, 0x30, 0x040 ), FCML_MI( 0x66, 0x8B, 0x05, 0x10, 0x20, 0x30, 0x040 ) );
    FCML_I64( "mov eax,dword ptr [5352515040302010h]", 0xA1, 0x10, 0x20, 0x30, 0x40, 0x50, 0x51, 0x52, 0x53 );
    FCML_I64( "mov ax,word ptr [5352515040302010h]", 0x66, 0xA1, 0x10, 0x20, 0x30, 0x40, 0x50, 0x51, 0x52, 0x53 );
    FCML_I64( "mov rax,qword ptr [5352515040302010h]", 0x48, 0xA1, 0x10, 0x20, 0x30, 0x40, 0x50, 0x51, 0x52, 0x53 );
    FCML_I64_M( "mov ax,word ptr [40302010h]", 2, FCML_MI( 0x66, 0x67, 0xa1, 0x10, 0x20, 0x30, 0x40 ), FCML_MI( 0x66, 0x67, 0x8b, 0x04, 0x25, 0x10, 0x20, 0x30, 0x40 ) );
    /* GAS*/
    FCML_A64( "movabs 0x5352515040302010,%eax", 0xa1, 0x10, 0x20, 0x30, 0x40, 0x50, 0x51, 0x52, 0x53 );
    FCML_A64( "movabs 0x5352515040302010,%ax", 0x66, 0xa1, 0x10, 0x20, 0x30, 0x40, 0x50, 0x51, 0x52, 0x53 );
    FCML_A32_M_A( "mov 0x40302010,%eax", 2, FCML_MI( 0xa1, 0x10, 0x20, 0x30, 0x40 ), FCML_MI( 0x8b, 0x05, 0x10, 0x20, 0x30, 0x40 ) );
    /* A2 MOV moffs8,AL D Valid Valid Move AL to (seg:offset).*/
    /* REX.W + A2 MOV moffs8***,AL D Valid N.E. Move AL to (offset).*/
    FCML_I32_M( "mov byte ptr [40302010h],al", 2, FCML_MI( 0xA2, 0x10, 0x20, 0x30, 0x40 ), FCML_MI( 0x88, 0x05, 0x10, 0x20, 0x30, 0x40 ) );
    FCML_I32_M( "mov byte ptr [2010h],al", 2, FCML_MI( 0x67, 0xA2, 0x10, 0x20 ), FCML_MI( 0x67, 0x88, 0x06, 0x10, 0x20 ) );
    FCML_I64( "mov byte ptr [5352515040302010h],al", 0xA2, 0x10, 0x20, 0x30, 0x40, 0x50, 0x51, 0x52, 0x53 );
    FCML_I64_M( "mov byte ptr [40302010h],al", 2, FCML_MI( 0x67, 0xa2, 0x10, 0x20, 0x30, 0x40 ), FCML_MI( 0x67, 0x88, 0x04, 0x25, 0x10, 0x20, 0x30, 0x40 ) );
    /* GAS*/
    FCML_A32_M( "mov %al,0x2010", 3, FCML_MI( 0x67, 0xa2, 0x10, 0x20 ), FCML_MI( 0xa2, 0x10, 0x20, 0x00, 0x00 ), FCML_MI( 0x67, 0x88, 0x06, 0x10, 0x20 ) );
    FCML_A64( "movabs %al,0x5352515040302010", 0xA2, 0x10, 0x20, 0x30, 0x40, 0x50, 0x51, 0x52, 0x53 );
    /* A3 MOV moffs16*,AX D Valid Valid Move AX to (seg:offset).*/
    /* A3 MOV moffs32*,EAX D Valid Valid Move EAX to (seg:offset).*/
    /* REX.W + A3 MOV moffs64*,RAX D Valid N.E. Move RAX to (offset).*/
    FCML_I32_M( "mov dword ptr [40302010h],eax", 2, FCML_MI( 0xA3, 0x10, 0x20, 0x30, 0x40 ), FCML_MI( 0x89, 0x05, 0x10, 0x20, 0x30, 0x40 ) );
    FCML_I32_M( "mov word ptr [2010h],ax", 2, FCML_MI( 0x66, 0x67, 0xA3, 0x10, 0x20 ), FCML_MI( 0x66, 0x67, 0x89, 0x06, 0x10, 0x20  ) );
    FCML_I32_M( "mov word ptr [40302010h],ax", 2, FCML_MI( 0x66, 0xA3, 0x10, 0x20, 0x30, 0x040 ), FCML_MI( 0x66, 0x89, 0x05, 0x10, 0x20, 0x30, 0x040 ) );
    FCML_I64( "mov dword ptr [5352515040302010h],eax", 0xA3, 0x10, 0x20, 0x30, 0x40, 0x50, 0x51, 0x52, 0x53 );
    FCML_I64( "mov word ptr [5352515040302010h],ax", 0x66, 0xA3, 0x10, 0x20, 0x30, 0x40, 0x50, 0x51, 0x52, 0x53 );
    FCML_I64( "mov qword ptr [5352515040302010h],rax", 0x48, 0xA3, 0x10, 0x20, 0x30, 0x40, 0x50, 0x51, 0x52, 0x53 );
    FCML_I64_M( "mov word ptr [40302010h],ax", 2, FCML_MI( 0x66, 0x67, 0xa3, 0x10, 0x20, 0x30, 0x40 ), FCML_MI( 0x66, 0x67, 0x89, 0x04, 0x25, 0x10, 0x20, 0x30, 0x40 ) );
    /* GAS*/
    FCML_A32_M( "mov %ax,0x2010", 3, FCML_MI( 0x66, 0x67, 0xa3, 0x10, 0x20 ), FCML_MI( 0x66, 0xa3, 0x10, 0x20, 0x00, 0x00 ), FCML_MI( 0x66, 0x67, 0x89, 0x06, 0x10, 0x20 ) );
    FCML_A64( "movabs %rax,0x5352515040302010", 0x48, 0xA3, 0x10, 0x20, 0x30, 0x40, 0x50, 0x51, 0x52, 0x53 );
    /* B0+ rb MOV r8, imm8 E Valid Valid Move imm8 to r8.*/
    /* REX + B0+ rb MOV r8***, imm8 E Valid N.E. Move imm8 to r8.*/
    FCML_I32_M( "mov al,0d0h", 2, FCML_MI( 0xB0, 0xD0 ), FCML_MI( 0xC6, 0xC0, 0xD0 )  );
    FCML_I32_M( "mov cl,0d0h", 2, FCML_MI( 0xB1, 0xD0 ), FCML_MI( 0xC6, 0xC1, 0xD0 ) );
    FCML_I32_M( "mov al,0d0h", 2, FCML_MI( 0x66, 0xB0, 0xD0 ), FCML_MI( 0x66, 0xC6, 0xC0, 0xD0 ) );
    FCML_I64_M( "mov al,0d0h", 2, FCML_MI( 0xB0, 0xD0 ), FCML_MI( 0xC6, 0xC0, 0xD0 ) );
    /* GAS*/
    FCML_A32_M( "mov $0xd0,%al", 2, FCML_MI( 0xb0, 0xd0 ), FCML_MI( 0xc6, 0xc0, 0xd0 ) );
    /* B8+ rw MOV r16, imm16 E Valid Valid Move imm16 to r16.*/
    /* B8+ rd MOV r32, imm32 E Valid Valid Move imm32 to r32.*/
    /* REX.W + B8+ rd MOV r64, imm64 E Valid N.E. Move imm64 to r64.*/
    FCML_I32_M( "mov eax,0d1d0d0d0h", 2, FCML_MI( 0xB8, 0xD0, 0xD0, 0xD0, 0xD1 ), FCML_MI( 0xC7, 0xC0, 0xD0, 0xD0, 0xD0, 0xD1 ) );
    FCML_I32_M( "mov ecx,0d1d0d0d0h", 2 ,FCML_MI( 0xB9, 0xD0, 0xD0, 0xD0, 0xD1 ), FCML_MI( 0xC7, 0xC1, 0xD0, 0xD0, 0xD0, 0xD1 ) );
    FCML_I32_M( "mov ax,0d1d0h", 2, FCML_MI( 0x66, 0xB8, 0xD0, 0xD1 ), FCML_MI( 0x66, 0xc7, 0xc0, 0xd0, 0xd1 ) );
    FCML_I64( "mov rax,0d1d0d0d0d1d0d0d0h", 0x48, 0xB8, 0xD0, 0xD0, 0xD0, 0xD1, 0xD0, 0xD0, 0xD0, 0xD1);
    FCML_I64_M( "mov ax,0d0d0h", 2, FCML_MI( 0x66, 0xB8, 0xD0, 0xD0 ), FCML_MI( 0x66, 0xc7, 0xc0, 0xd0, 0xd0 ) );
    /* GAS*/
    FCML_A32_M( "mov $0xd1d0,%ax", 2, FCML_MI( 0x66, 0xB8, 0xD0, 0xD1 ), FCML_MI( 0x66, 0xc7, 0xc0, 0xd0, 0xd1 ) );
    FCML_A64( "movabs $0xd1d0d0d0d1d0d0d0,%rax", 0x48, 0xb8, 0xd0, 0xd0, 0xd0, 0xd1, 0xd0, 0xd0, 0xd0, 0xd1 );
    /* C6 /0 MOV r/m8, imm8 F Valid Valid Move imm8 to r/m8.*/
    /* REX + C6 /0 MOV r/m8***, imm8 F Valid N.E. Move imm8 to r/m8.*/
    FCML_I32( "mov byte ptr [eax+00000010h],20h", 0xC6, 0x40, 0x10, 0x20 );
    FCML_I32( "mov byte ptr [eax+00000010h],20h", 0x66, 0xC6, 0x40, 0x10, 0x20  );
    FCML_I32_M( "mov al,20h", 2, FCML_MI( 0x66, 0xC6, 0xc0, 0x20 ), FCML_MI( 0x66, 0xb0, 0x20 ) );
    FCML_I64_D( "mov byte ptr [rax+0000000000000010h],20h", 0x48, 0xC6, 0x40, 0x10, 0x20);
    FCML_I64( "mov byte ptr [rax+0000000000000010h],20h", 0xC6, 0x40, 0x10, 0x20);
    /* GAS*/
    FCML_A64( "movb $0x20,0x0000000000000010(%rax)", 0xc6, 0x40, 0x10, 0x20 );
    FCML_A32( "movb $0x20,%al", 0xC6, 0xc0, 0x20  );
    FCML_A32_M_A( "mov $0x20,%al", 2, FCML_MI( 0xc6, 0xc0, 0x20 ), FCML_MI( 0xb0, 0x20 ) );
    /* C7 /0 MOV r/m16, imm16 F Valid Valid Move imm16 to r/m16.*/
    /* C7 /0 MOV r/m32, imm32 F Valid Valid Move imm32 to r/m32.*/
    /* REX.W + C7 /0 MOV r/m64, imm32 F Valid N.E. Move imm32 sign extended to 64-bits to r/m64.*/
    FCML_I32( "mov dword ptr [eax+00000010h],40302010h", 0xC7, 0x40, 0x10, 0x10, 0x20, 0x30, 0x40 );
    FCML_I32( "mov word ptr [eax+00000010h],2010h", 0x66, 0xC7, 0x40, 0x10, 0x10, 0x20  );
    FCML_I32_M( "mov ax,2010h", 2, FCML_MI( 0x66, 0xb8, 0x10, 0x20 ), FCML_MI( 0x66, 0xc7, 0xc0, 0x10, 0x20 ) );
    FCML_I64( "mov qword ptr [rax+0000000000000010h],0000000040302010h", 0x48, 0xC7, 0x40, 0x10, 0x10, 0x20, 0x30, 0x40 );
    FCML_I64( "mov qword ptr [rbp+rbx*8+0000000040302010h],0ffffffff80706050h", 0x48, 0xC7, 0x84, 0xDD, 0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70, 0x80 );
    /* GAS*/
    FCML_A32( "movl $0x40302010,0x00000010(%eax)", 0xC7, 0x40, 0x10, 0x10, 0x20, 0x30, 0x40 );
    FCML_A32( "movw $0x2010,0x00000010(%eax)", 0x66, 0xC7, 0x40, 0x10, 0x10, 0x20  );
    FCML_A64( "movq $0xffffffff80706050,0x0000000040302010(%rbp,%rbx,8)", 0x48, 0xc7, 0x84, 0xdd, 0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70, 0x80 );
    FCML_A64_M( "mov $0x2010,%ax", 2, FCML_MI( 0x66, 0xb8, 0x10, 0x20 ), FCML_MI( 0x66, 0xc7, 0xc0, 0x10, 0x20 ) );
}

void fcml_tf_instruction_MOVAPD(void) {
    /* 66 0F 28 /r MOVAPD xmm1, xmm2/m128 A Valid Valid Move packed doubleprecision floating-point values from xmm2/m128 to xmm1.*/
    FCML_I64( "movapd xmm0,xmmword ptr [rax+0000000000000020h]", 0x66, 0x0F, 0x28, 0x40, 0x20 );
    FCML_I64_D( "movapd xmm0,xmmword ptr [rax+0000000000000020h]", 0x66, 0x48, 0x0F, 0x28, 0x40, 0x20 );
    FCML_I32_M( "movapd xmm0,xmm2", 2, FCML_MI( 0x66, 0x0F, 0x28, 0xC2 ), FCML_MI( 0x66, 0x0f, 0x29, 0xd0 ) );
    FCML_I32( "movapd xmm0,xmmword ptr [eax+00000020h]", 0x66, 0x0F, 0x28, 0x40, 0x20 );
    /* 66 0F 29 /r MOVAPD xmm2/m128, xmm1 B Valid Valid Move packed doubleprecision floating-point values from xmm1 to xmm2/m128.*/
    FCML_I64( "movapd xmmword ptr [rax+0000000000000020h],xmm0", 0x66, 0x0F, 0x29, 0x40, 0x20 );
    FCML_I64_D( "movapd xmmword ptr [rax+0000000000000020h],xmm0", 0x66, 0x48, 0x0F, 0x29, 0x40, 0x20 );
    FCML_I32_M( "movapd xmm2,xmm0", 2, FCML_MI( 0x66, 0x0F, 0x29, 0xC2 ), FCML_MI( 0x66, 0x0f, 0x28, 0xd0 ) );
    FCML_I32( "movapd xmmword ptr [eax+00000020h],xmm0", 0x66, 0x0F, 0x29, 0x40, 0x20 );
    /* VEX.128.66.0F 28 /r VMOVAPD xmm1,xmm2/m128*/
    /* VEX.256.66.0F 28 /r VMOVAPD ymm1,ymm2/m256*/
    FCML_I3264_M( "vmovapd xmm3,xmm0", 2, FCML_MI( 0xc5, 0xf9, 0x29, 0xc3 ), FCML_MI( 0xc5, 0xf9, 0x28, 0xd8 ) );
    FCML_I32( "vmovapd xmm0,xmmword ptr [eax]", 0xc5, 0xf9, 0x28, 0x00 );
    /* VEX.128.66.0F 29 /r VMOVAPD xmm2/m128,xmm1*/
    /* VEX.256.66.0F 29 /r VMOVAPD ymm2/m256,ymm1*/
    FCML_I64_M( "vmovapd xmm0,xmm3", 2, FCML_MI( 0xc5, 0xf9, 0x29, 0xd8 ), FCML_MI( 0xc5, 0xf9, 0x28, 0xc3 ) );
    FCML_I32_M( "vmovapd xmm0,xmm3", 2, FCML_MI( 0xc5, 0xf9, 0x29, 0xd8 ), FCML_MI( 0xc5, 0xf9, 0x28, 0xc3 ) );
    FCML_I32( "vmovapd xmmword ptr [eax],xmm0", 0xc5, 0xf9, 0x29, 0x00 );
    /* GAS*/
    FCML_A64( "movapd 0x0000000000000020(%rax),%xmm0", 0x66, 0x0f, 0x28, 0x40, 0x20 );
    FCML_A64( "movapd %xmm0,0x0000000000000020(%rax)", 0x66, 0x0f, 0x29, 0x40, 0x20 );
    FCML_A64( "vmovapd (%rax),%xmm0", 0xc5, 0xf9, 0x28, 0x00 );
    FCML_A64( "vmovapd %xmm0,(%rax)", 0xc5, 0xf9, 0x29, 0x00 );
}

void fcml_tf_instruction_MOVAPS(void) {
    /* 66 0F 28 /r MOVAPD xmm1, xmm2/m128 A Valid Valid Move packed doubleprecision floating-point values from xmm2/m128 to xmm1.*/
    FCML_I64( "movaps xmm0,xmmword ptr [rax+0000000000000020h]", 0x0F, 0x28, 0x40, 0x20 );
    FCML_I32_M( "movaps xmm0,xmm2", 2, FCML_MI( 0x0f, 0x29, 0xd0 ), FCML_MI( 0x0f, 0x28, 0xc2 ) );
    FCML_I32( "movaps xmm0,xmmword ptr [eax+00000020h]", 0x0F, 0x28, 0x40, 0x20 );
    /* 66 0F 29 /r MOVAPD xmm2/m128, xmm1 B Valid Valid Move packed doubleprecision floating-point values from xmm1 to xmm2/m128.*/
    FCML_I64( "movaps xmmword ptr [rax+0000000000000020h],xmm0", 0x0F, 0x29, 0x40, 0x20 );
    FCML_I32_M( "movaps xmm2,xmm0", 2, FCML_MI( 0x0f, 0x29, 0xc2 ), FCML_MI( 0x0f, 0x28, 0xd0 ) );
    FCML_I32( "movaps xmmword ptr [eax+00000020h],xmm0", 0x0F, 0x29, 0x40, 0x20 );
    /* VEX.128.0F 28 /r VMOVAPS xmm1,xmm2/m128*/
    /* VEX.256.0F 28 /r VMOVAPS ymm1,ymm2/m256*/
    FCML_I64_M( "vmovaps xmm3,xmm0", 2, FCML_MI( 0xc5, 0xf8, 0x29, 0xc3 ), FCML_MI( 0xc5, 0xf8, 0x28, 0xd8 ) );
    FCML_I32_M( "vmovaps xmm3,xmm0", 2, FCML_MI( 0xc5, 0xf8, 0x29, 0xc3 ), FCML_MI( 0xc5, 0xf8, 0x28, 0xd8 ) );
    FCML_I32_M( "vmovaps ymm3,ymm0", 2, FCML_MI( 0xc5, 0xfc, 0x29, 0xc3 ), FCML_MI( 0xc5, 0xfc, 0x28, 0xd8 ) );
    FCML_I32( "vmovaps xmm0,xmmword ptr [eax]", 0xc5, 0xf8, 0x28, 0x00 );
    /* VEX.128.0F 29 /r VMOVAPS xmm2/m128,xmm1*/
    /* VEX.256.0F 29 /r VMOVAPS ymm2/m256,ymm1*/
    FCML_I64_M( "vmovaps xmm0,xmm3", 2, FCML_MI( 0xc5, 0xf8, 0x29, 0xd8 ), FCML_MI( 0xc5, 0xf8, 0x28, 0xc3 ) );
    FCML_I32_M( "vmovaps xmm0,xmm3", 2, FCML_MI( 0xc5, 0xf8, 0x29, 0xd8 ), FCML_MI( 0xc5, 0xf8, 0x28, 0xc3 ) );
    FCML_I32( "vmovaps xmmword ptr [eax],xmm0", 0xc5, 0xf8, 0x29, 0x00 );
    FCML_I32( "vmovaps ymmword ptr [eax],ymm0", 0xc5, 0xfc, 0x29, 0x00 );
    /* GAS*/
    FCML_A64( "movaps 0x0000000000000020(%rax),%xmm0", 0x0f, 0x28, 0x40, 0x20 );
    FCML_A64( "movaps %xmm0,0x0000000000000020(%rax)", 0x0f, 0x29, 0x40, 0x20 );
    FCML_A64( "vmovaps (%rax),%xmm0", 0xc5, 0xf8, 0x28, 0x00 );
    FCML_A64( "vmovaps %ymm0,(%rax)", 0xc5, 0xfc, 0x29, 0x00 );
}

void fcml_tf_instruction_MOVBE(void) {
    /* 0F 38 F0 /r MOVBE r16, m16 A Valid Valid Reverse byte order in m16 and move to r16*/
    /* 0F 38 F0 /r MOVBE r32, m32 A Valid Valid Reverse byte order in m32 and move to r32*/
    /* REX.W + 0F 38 F0 /r MOVBE r64, m64 A Valid N.E. Reverse byte order in m64 and move to r64.*/
    FCML_I64( "movbe edx,dword ptr [rax]", 0x0F, 0x38, 0xF0, 0x10 );
    FCML_I64( "movbe rdx,qword ptr [rax]", 0x48, 0x0F, 0x38, 0xF0, 0x10 );
    FCML_I32_FAILED( "movbe eax,edx", 0x0F, 0x38, 0xF0, 0xC2 );
    FCML_I32( "movbe dx,word ptr [eax]", 0x66, 0x0F, 0x38, 0xF0, 0x10 );
    /* 0F 38 F1 /r MOVBE m16, r16 B Valid Valid Reverse byte order in r16 and move to m16*/
    /* 0F 38 F1 /r MOVBE m32, r32 B Valid Valid Reverse byte order in r32 and move to m32*/
    /* REX.W + 0F 38 F1 /r MOVBE m64, r64 B Valid N.E. Reverse byte order in*/
    FCML_I64( "movbe dword ptr [rax],edx", 0x0F, 0x38, 0xF1, 0x10 );
    FCML_I64( "movbe qword ptr [rax],rdx", 0x48, 0x0F, 0x38, 0xF1, 0x10 );
    FCML_I32_FAILED( "movbe edx,eax", 0x0F, 0x38, 0xF1, 0xC2 );
    FCML_I32( "movbe word ptr [eax],dx", 0x66, 0x0F, 0x38, 0xF1, 0x10 );
    /* GAS*/
    FCML_A64( "movbe (%rax),%edx", 0x0f, 0x38, 0xf0, 0x10 );
    FCML_A64( "movbe %edx,(%rax)", 0x0f, 0x38, 0xf1, 0x10 );
}

void fcml_tf_instruction_MOVQ(void) {
	/* 0F 6F /r MOVQ mm, mm/m64 A Valid Valid Move quadword from mm/m64 to mm.*/
	FCML_I32( "movq mm0,mmword ptr [eax]", 0x0F, 0x6F, 0x00 );
	FCML_I64( "movq mm0,mmword ptr [rax]", 0x0F, 0x6F, 0x00 );
	FCML_I64_M_A( "movq mm0,[rax]", 2, FCML_MI( 0x0f, 0x6f, 0x00 ), FCML_MI( 0x48, 0x0f, 0x6e, 0x00 ) );
	FCML_I32_D( "movq mm0,mm2", 0x0f, 0x6f, 0xc2 );
	FCML_I64_M( "movq mm2,mm0", 2, FCML_MI( 0x0f, 0x6f, 0xd0 ), FCML_MI( 0x0f, 0x7f, 0xc2 ) );
	/* GAS (ambigous syntax)*/
	FCML_A64_M( "movq (%rax),%mm0", 2, FCML_MI( 0x0f, 0x6f, 0x00 ), FCML_MI( 0x48, 0x0f, 0x6e, 0x00 ) );
	FCML_A64_M( "movq %mm0,%mm0", 2, FCML_MI( 0x0f, 0x7f, 0xc0 ), FCML_MI( 0x0f, 0x6f, 0xc0 ) );
	/* 0F 7F /r MOVQ mm/m64, mm B Valid Valid Move quadword from mm to mm/m64.*/
	FCML_I32( "movq mmword ptr [eax],mm0", 0x0F, 0x7F, 0x00 );
	FCML_I64( "movq mmword ptr [rax],mm0",  0x0F, 0x7F, 0x00 );
	FCML_I64_M( "movq mm0,mm2", 2, FCML_MI( 0x0f, 0x7f, 0xd0 ), FCML_MI( 0x0f, 0x6f, 0xc2 ) );
	/* GAS*/
	FCML_A64_M( "movq %mm0,(%rax)", 2, FCML_MI( 0x0f, 0x7f, 0x00 ), FCML_MI( 0x48, 0x0f, 0x7e, 0x00 ) );
	/* REX.W + 0F 7E /r MOVQ r/m64, mm B Valid N.E. Move quadword from mm to r/m64.*/
	FCML_I64_A( "movq mmword ptr [rax],mm2", 0x0f, 0x7f, 0x10 );
	/* GAS*/
	FCML_A64_M( "movq %mm2,(%rax)", 2, FCML_MI( 0x0f, 0x7f, 0x10 ), FCML_MI( 0x48, 0x0f, 0x7e, 0x10 ) );
	/* F3 0F 7E MOVQ xmm1, xmm2/m64 A Valid Valid Move quadword from xmm2/mem64 to xmm1.*/
	FCML_I32( "movq xmm0,mmword ptr [eax]", 0xF3, 0x0F, 0x7E, 0x00 );
	FCML_I64( "movq xmm0,mmword ptr [rax]", 0xF3, 0x0F, 0x7E, 0x00 );
	FCML_I64_M( "movq xmm2,xmm0", 2, FCML_MI( 0x66, 0x0f, 0xd6, 0xc2 ), FCML_MI( 0xf3, 0x0f, 0x7e, 0xd0 ) );
	/* GAS*/
	FCML_A64_M( "movq (%rax),%xmm0", 2, FCML_MI( 0xf3, 0x0f, 0x7e, 0x00 ), FCML_MI( 0x66, 0x48, 0x0f, 0x6e, 0x00 ) );
	FCML_A64_M( "movq %xmm0,%xmm2", 2, FCML_MI( 0x66, 0x0f, 0xd6, 0xc2 ), FCML_MI( 0xf3, 0x0f, 0x7e, 0xd0 ) );
	/* 66 0F D6 MOVQ xmm2/m64, xmm1 B Valid Valid Move quadword from xmm1 to xmm2/mem64.*/
	FCML_I32( "movq mmword ptr [eax],xmm0", 0x66, 0x0F, 0xD6, 0x00 );
	FCML_I64( "movq mmword ptr [rax],xmm0", 0x66, 0x0F, 0xD6, 0x00 );
	FCML_I64_M( "movq xmm0,xmm2", 2, FCML_MI( 0x66, 0x0f, 0xd6, 0xd0 ), FCML_MI( 0xf3, 0x0f, 0x7e, 0xc2 ) );
	/* GAS*/
	FCML_A64_M( "movq %xmm0,(%rax)", 2, FCML_MI( 0x66, 0x0f, 0xd6, 0x00 ), FCML_MI( 0x66, 0x48, 0x0f, 0x7e, 0x00 ) );
	FCML_A64_M( "movq %xmm2,%xmm0", 2, FCML_MI( 0x66, 0x0f, 0xd6, 0xd0 ), FCML_MI( 0xf3, 0x0f, 0x7e, 0xc2 ) );
	/* VEX.128.F3.0F 7E /r VMOVQ xmm1,xmm2*/
	/* VEX.128.F3.0F 7E /r VMOVQ xmm1,m64*/
	FCML_I32( "vmovq xmm0,mmword ptr [eax]", 0xc5, 0xfa, 0x7e, 0x00 );
	FCML_I32_M( "vmovq xmm0,xmm0", 2, FCML_MI( 0xc5, 0xf9, 0xd6, 0xc0 ), FCML_MI( 0xc5, 0xfa, 0x7e, 0xc0 ) );
	/* GAS*/
	FCML_A32( "vmovq (%eax),%xmm0", 0xc5, 0xfa, 0x7e, 0x00 );
	/* VEX.128.66.0F D6 /r VMOVQ xmm1/m64,xmm2*/
	FCML_I32( "vmovq mmword ptr [eax],xmm0", 0xc5, 0xf9, 0xd6, 0x00 );
	FCML_I32_M( "vmovq xmm0,xmm0", 2, FCML_MI( 0xc5, 0xf9, 0xd6, 0xc0 ), FCML_MI( 0xc5, 0xfa, 0x7e, 0xc0 ) );
	/* GAS*/
	FCML_A32( "vmovq %xmm0,(%eax)", 0xc5, 0xf9, 0xd6, 0x00 );
	FCML_A32_M( "vmovq %xmm0,%xmm0", 2, FCML_MI( 0xc5, 0xf9, 0xd6, 0xc0 ), FCML_MI( 0xc5, 0xfa, 0x7e, 0xc0 ) );
	/* VEX.128.66.0F.W1 7E /r VMOVQ r64/m64,xmm1*/
	FCML_I64( "vmovq mmword ptr [rcx+rax],xmm2", 0xc5, 0xf9, 0xd6, 0x14, 0x01 );
	/* GAS*/
	FCML_A64_M( "vmovq %xmm2,(%rcx,%rax)", 2, FCML_MI( 0xc5, 0xf9, 0xd6, 0x14, 0x01 ), FCML_MI( 0xc4, 0xe1, 0xf9, 0x7e, 0x14, 0x01 ) );
	/* REX.W + 0F 6E /r MOVQ mm, r/m64 A Valid N.E. Move quadword from r/m64 to mm.*/
	FCML_I64_M( "movq mm2,qword ptr [rax]", 2, FCML_MI( 0x48, 0x0f, 0x6e, 0x10 ), FCML_MI( 0x0f, 0x6f, 0x10 ) );
	/*GAS*/
	FCML_A64_M( "movq (%rax),%mm2", 2,FCML_MI( 0x48, 0x0f, 0x6e, 0x10 ), FCML_MI( 0x0f, 0x6f, 0x10 ) );
	FCML_A64( "movq %rax,%mm0", 0x48, 0x0f, 0x6e, 0xc0 );
	/* 66 REX.W 0F 6E /r MOVQ xmm, r/m64 A Valid N.E. Move quadword from r/m64 to xmm.l*/
	FCML_I64_A( "movq xmm2,mmword ptr [rax]", 0xf3, 0x0f, 0x7e, 0x10 );
	/* GAS*/
	FCML_A64_M( "movq (%rax),%xmm2", 2, FCML_MI( 0xf3, 0x0f, 0x7e, 0x10 ), FCML_MI( 0x66, 0x48, 0x0f, 0x6e, 0x10 ) );
	/* 66 REX.W 0F 7E /r MOVQ r/m64, xmm B Valid N.E. Move quadword from xmm register to r/m64.*/
	FCML_I64_M( "movq qword ptr [rax],xmm2", 2, FCML_MI( 0x66, 0x48, 0x0f, 0x7e, 0x10 ), FCML_MI( 0x66, 0x0f, 0xd6, 0x10 ) );
	/* GAS*/
	FCML_A64_M( "movq %xmm2,(%rax)", 2, FCML_MI( 0x66, 0x48, 0x0f, 0x7e, 0x10 ), FCML_MI( 0x66, 0x0f, 0xd6, 0x10 ) );
	/* VEX.128.66.0F.W1 6E /r VMOVQ xmm1,r64/m64*/
	FCML_I64( "vmovq xmm2,mmword ptr [rcx+rax]", 0xc5, 0xfa, 0x7e, 0x14, 0x01 );
	/* GAS*/
	FCML_A64_M( "vmovq (%rcx,%rax),%xmm2", 2, FCML_MI( 0xc5, 0xfa, 0x7e, 0x14, 0x01 ), FCML_MI( 0xc4, 0xe1, 0xf9, 0x6e, 0x14, 0x01 ) );
}

void fcml_tf_instruction_MOVD(void) {
    /* 0F 6E /r MOVD mm,r/m32 A Valid Valid Move doubleword from r/m32 to mm.*/
    FCML_I32( "movd mm2,dword ptr [eax]", 0x0F, 0x6E, 0x10 );
    FCML_I64( "movd mm2,dword ptr [rax]", 0x0F, 0x6E, 0x10 );
    /* GAS*/
    FCML_A64( "movd (%rax),%mm2", 0x0f, 0x6e, 0x10 );
    FCML_A64( "movd %eax,%mm0", 0x0f, 0x6e, 0xc0 );
    /* 0F 7E /r MOVD r/m32, mm B Valid Valid Move doubleword from mm to r/m32.*/
    FCML_I32( "movd dword ptr [eax],mm2", 0x0F, 0x7E, 0x10 );
    FCML_I64( "movd dword ptr [rax],mm2", 0x0F, 0x7E, 0x10 );
    /* GAS*/
    FCML_A64( "movd %mm2,(%rax)", 0x0f, 0x7e, 0x10 );
    FCML_A64( "movd %mm0,%eax", 0x0f, 0x7e, 0xc0 );
    /* 66 0F 6E /r MOVD xmm, r/m32 A Valid Valid Move doubleword from r/m32 to xmm.*/
    FCML_I32( "movd xmm2,dword ptr [eax]", 0x66, 0x0F, 0x6E, 0x10 );
    FCML_I64( "movd xmm2,dword ptr [rax]", 0x66, 0x0F, 0x6E, 0x10 );
    /* GAS*/
    FCML_A64( "movd (%rax),%xmm2", 0x66, 0x0f, 0x6e, 0x10 );
    FCML_A64( "movd %eax,%xmm0", 0x66, 0x0f, 0x6e, 0xc0 );
    /* 66 0F 7E /r MOVD r/m32, xmm B Valid Valid Move doubleword from xmm register to r/m32.*/
    FCML_I32( "movd dword ptr [eax],xmm2", 0x66, 0x0F, 0x7E, 0x10 );
    FCML_I64( "movd dword ptr [rax],xmm2", 0x66, 0x0F, 0x7E, 0x10 );
    /* GAS*/
    FCML_A64( "movd %xmm2,(%rax)", 0x66, 0x0f, 0x7e, 0x10 );
    FCML_A64( "movd %xmm0,%eax", 0x66, 0x0f, 0x7e, 0xc0 );
    /* VEX.128.66.0F.W0 6E /r VMOVD xmm1,r32/m32*/
    FCML_I32( "vmovd xmm2,dword ptr [ecx+eax]", 0xc5, 0xf9, 0x6e, 0x14, 0x01 );
    /* GAS*/
    FCML_A64( "vmovd (%rcx,%rax),%xmm2", 0xc5, 0xf9, 0x6e, 0x14, 0x01 );
    FCML_A64( "vmovd (%rcx,%rax,8),%xmm2", 0xc5, 0xf9, 0x6e, 0x14, 0xc1 );
    FCML_A64( "vmovd %ecx,%xmm0", 0xc5, 0xf9, 0x6e, 0xc1 );
    /* VEX.128.66.0F.W0 7E /r VMOVD r32/m32,xmm1*/
    FCML_I32( "vmovd dword ptr [ecx+eax],xmm2", 0xc5, 0xf9, 0x7e, 0x14, 0x01 );
    /* GAS*/
    FCML_A64( "vmovd %xmm2,(%rcx,%rax)", 0xc5, 0xf9, 0x7e, 0x14, 0x01 );
    FCML_A64( "vmovd %xmm0,%ecx", 0xc5, 0xf9, 0x7e, 0xc1 );
}

void fcml_tf_instruction_MOVDDUP(void) {
    /* F2 0F 12 /r MOVDDUP xmm1, xmm2/m64 A Valid Valid Move one double-precision floating-point value from the lower 64-bit operand in xmm2/m64 to xmm1 and duplicate.*/
    FCML_I32( "movddup xmm2,mmword ptr [eax]", 0xF2, 0x0F, 0x12, 0x10 );
    FCML_I32( "movddup xmm3,xmm0", 0xF2, 0x0F, 0x12, 0xD8 );
    FCML_I64( "movddup xmm2,mmword ptr [rax]", 0xF2, 0x0F, 0x12, 0x10 );
    /* GAS*/
    FCML_A64( "movddup (%rax),%xmm2", 0xf2, 0x0f, 0x12, 0x10 );
    FCML_A64( "movddup %xmm0,%xmm3", 0xf2, 0x0f, 0x12, 0xd8 );
    /* VEX.128.F2.0F 12 /r VMOVDDUP xmm1,xmm2/m64*/
    /* VEX.256.F2.0F 12 /r VMOVDDUP ymm1,ymm2/m256*/
    FCML_I64( "vmovddup xmm3,xmm0", 0xc5, 0xfb, 0x12, 0xd8 );
    FCML_I32( "vmovddup xmm0,mmword ptr [eax]", 0xc5, 0xfb, 0x12, 0x00 );
    FCML_I32( "vmovddup ymm3,ymm0", 0xc5, 0xff, 0x12, 0xd8 );
    FCML_I64( "vmovddup ymm0,ymmword ptr [rax]", 0xc5, 0xff, 0x12, 0x00 );
    /* GAS*/
    FCML_A64( "vmovddup %ymm0,%ymm3", 0xc5, 0xff, 0x12, 0xd8 );
    FCML_A64( "vmovddup (%rax),%ymm0", 0xc5, 0xff, 0x12, 0x00 );
    /* VEX.128.F3.0F 6F /r VMOVDQU xmm1,xmm2/m128*/
    /* VEX.256.F3.0F 6F /r VMOVDQU ymm1,ymm2/m256*/
    FCML_I64_M( "vmovdqu xmm3,xmm0", 2, FCML_MI( 0xc5, 0xfa, 0x7f, 0xc3 ), FCML_MI( 0xc5, 0xfa, 0x6f, 0xd8 ) );
    FCML_I32( "vmovdqu ymm0,ymmword ptr [eax]", 0xc5, 0xfe, 0x6f, 0x00 );
    /* GAS*/
    FCML_A64_M( "vmovdqu %xmm0,%xmm3", 2, FCML_MI( 0xc5, 0xfa, 0x7f, 0xc3 ), FCML_MI( 0xc5, 0xfa, 0x6f, 0xd8 ) );
    FCML_A64( "vmovdqu (%rax),%ymm0", 0xc5, 0xfe, 0x6f, 0x00 );
    /* VEX.128.F3.0F 7F /r VMOVDQU xmm2/m128,xmm1*/
    /* VEX.256.F3.0F 7F /r VMOVDQU ymm2/m256,ymm1*/
    FCML_I32_M( "vmovdqu xmm0,xmm3", 2, FCML_MI( 0xc5, 0xfa, 0x7f, 0xd8 ), FCML_MI( 0xc5, 0xfa, 0x6f, 0xc3 ) );
    FCML_I64( "vmovdqu ymmword ptr [rax],ymm0", 0xc5, 0xfe, 0x7f, 0x00 );
    /* GAS*/
    FCML_A64_M( "vmovdqu %xmm3,%xmm0", 2, FCML_MI( 0xc5, 0xfa, 0x7f, 0xd8 ), FCML_MI( 0xc5, 0xfa, 0x6f, 0xc3 ) );
    FCML_A64( "vmovdqu %ymm0,(%rax)", 0xc5, 0xfe, 0x7f, 0x00 );
}

void fcml_tf_instruction_MOVDQA(void) {
    /* 66 0F 6F /r MOVDQA xmm1, xmm2/m128 A Valid Valid Move aligned double quadword from xmm2/m128 to xmm1.*/
    FCML_I32( "movdqa xmm2,xmmword ptr [eax]", 0x66, 0x0F, 0x6F, 0x10 );
    FCML_I32_M( "movdqa xmm3,xmm0", 2, FCML_MI( 0x66, 0x0f, 0x7f, 0xc3 ), FCML_MI( 0x66, 0x0f, 0x6f, 0xd8 ) );
    FCML_I64( "movdqa xmm2,xmmword ptr [rax]", 0x66, 0x0F, 0x6F, 0x10 );
    /* GAS*/
    FCML_A64( "movdqa (%rax),%xmm2", 0x66, 0x0f, 0x6f, 0x10 );
    FCML_A64_M( "movdqa %xmm0,%xmm3", 2, FCML_MI( 0x66, 0x0f, 0x7f, 0xc3 ), FCML_MI( 0x66, 0x0f, 0x6f, 0xd8 ) );
    /* 66 0F 7F /r MOVDQA xmm2/m128, xmm1 B Valid Valid Move aligned double quadword from xmm1 to xmm2/m128.*/
    FCML_I32( "movdqa xmmword ptr [eax],xmm2", 0x66, 0x0F, 0x7F, 0x10 );
    FCML_I32_M( "movdqa xmm0,xmm3", 2, FCML_MI( 0x66, 0x0f, 0x7f, 0xd8 ), FCML_MI( 0x66, 0x0f, 0x6f, 0xc3 ) );
    FCML_I64( "movdqa xmmword ptr [rax],xmm2", 0x66, 0x0F, 0x7F, 0x10 );
    /* GAS*/
    FCML_A64( "movdqa %xmm2,(%rax)", 0x66, 0x0f, 0x7f, 0x10 );
    /* VEX.128.66.0F 6F /r VMOVDQA xmm1,xmm2/m128*/
    /* VEX.256.66.0F 6F /r VMOVDQA ymm1,ymm2/m256*/
    FCML_I64_M( "vmovdqa xmm3,xmm0", 2, FCML_MI( 0xc5, 0xf9, 0x7f, 0xc3 ), FCML_MI( 0xc5, 0xf9, 0x6f, 0xd8 ) );
    FCML_I32( "vmovdqa ymm0,ymmword ptr [eax]", 0xc5, 0xfd, 0x6f, 0x00 );
    /* GAS*/
    FCML_A64( "vmovdqa (%rax),%ymm0", 0xc5, 0xfd, 0x6f, 0x00 );
    /* VEX.128.66.0F 7F /r VMOVDQA xmm2/m128,xmm1*/
    /* VEX.256.66.0F 7F /r VMOVDQA ymm2/m256,ymm1*/
    FCML_I32_M( "vmovdqa xmm0,xmm3", 2, FCML_MI( 0xc5, 0xf9, 0x7f, 0xd8 ), FCML_MI( 0xc5, 0xf9, 0x6f, 0xc3 ) );
    FCML_I64( "vmovdqa ymmword ptr [rax],ymm0", 0xc5, 0xfd, 0x7f, 0x00 );
    /* GAS*/
    FCML_A64( "vmovdqa %ymm0,(%rax)", 0xc5, 0xfd, 0x7f, 0x00 );
}

void fcml_tf_instruction_MOVDQU(void) {
    /* F3 0F 6F /r MOVDQU xmm1, xmm2/m128 A Valid Valid Move unaligned double quadword from xmm2/m128 to xmm1.*/
    FCML_I32( "movdqu xmm2,xmmword ptr [eax]", 0xF3, 0x0F, 0x6F, 0x10 );
    FCML_I32_M( "movdqu xmm3,xmm0", 2, FCML_MI( 0xf3, 0x0f, 0x7f, 0xc3 ), FCML_MI( 0xf3, 0x0f, 0x6f, 0xd8 ) );
    FCML_I64( "movdqu xmm2,xmmword ptr [rax]", 0xF3, 0x0F, 0x6F, 0x10 );
    /* GAS*/
    FCML_A64_M( "movdqu %xmm0,%xmm3", 2, FCML_MI( 0xf3, 0x0f, 0x7f, 0xc3 ), FCML_MI( 0xf3, 0x0f, 0x6f, 0xd8 ) );
    FCML_A64( "movdqu (%rax),%xmm2", 0xf3, 0x0f, 0x6f, 0x10 );
    /* F3 0F 7F /r MOVDQU xmm2/m128, xmm1 B Valid Valid Move unaligned double quadword from xmm1 to xmm2/m128.*/
    FCML_I32( "movdqu xmmword ptr [eax],xmm2", 0xF3, 0x0F, 0x7F, 0x10 );
    FCML_I32_M( "movdqu xmm0,xmm3", 2, FCML_MI( 0xf3, 0x0f, 0x7f, 0xd8 ), FCML_MI( 0xf3, 0x0f, 0x6f, 0xc3 ) );
    FCML_I64( "movdqu xmmword ptr [rax],xmm2", 0xF3, 0x0F, 0x7F, 0x10 );
    /* GAS*/
    FCML_A64( "movdqu %xmm2,(%rax)", 0xf3, 0x0f, 0x7f, 0x10 );
}

void fcml_tf_instruction_MOVDQ2Q(void) {
    /* F2 0F D6 MOVDQ2Q mm, xmm A Valid Valid Move low quadword from xmm to mmx register.*/
    FCML_I32( "movdq2q mm2,xmm0", 0xF2, 0x0F, 0xD6, 0xD0 );
    FCML_I32( "movdq2q mm3,xmm0", 0xF2, 0x0F, 0xD6, 0xD8 );
    FCML_I64( "movdq2q mm2,xmm0", 0xF2, 0x0F, 0xD6, 0xD0 );
    /* GAS*/
    FCML_A64( "movdq2q %xmm0,%mm3", 0xf2, 0x0f, 0xd6, 0xd8 );
}

void fcml_tf_instruction_MOVHLPS(void) {
    /* 0F 12 /r MOVHLPS xmm1, xmm2 A Valid Valid Move two packed singleprecision floating-point values from high quadword of xmm2 to low quadword of xmm1.*/
    FCML_I32( "movhlps xmm2,xmm0", 0x0F, 0x12, 0xD0 );
    FCML_I32( "movhlps xmm3,xmm0", 0x0F, 0x12, 0xD8 );
    FCML_I64( "movhlps xmm2,xmm0", 0x0F, 0x12, 0xD0 );
    /* GAS*/
    FCML_A64( "movhlps %xmm0,%xmm3", 0x0f, 0x12, 0xd8 );
    /* VEX.NDS.128.0F 12 /r VMOVHLPS xmm1, xmm2, xmm3*/
    FCML_I32( "vmovhlps xmm3,xmm0,xmm0", 0xc5, 0xf8, 0x12, 0xd8 );
    FCML_I64( "vmovhlps xmm3,xmm0,xmm1", 0xc5, 0xf8, 0x12, 0xd9 );
    FCML_I64( "vmovhlps xmm3,xmm15,xmm1", 0xc5, 0x80, 0x12, 0xd9 );
    /* GAS*/
    FCML_A64( "vmovhlps %xmm1,%xmm0,%xmm3", 0xc5, 0xf8, 0x12, 0xd9 );
}

void fcml_tf_instruction_MOVHPD(void) {
    /* 66 0F 16 /r MOVHPD xmm, m64 A Valid Valid Move double-precision floating-point value from m64 to high quadword of xmm.*/
    FCML_I32( "movhpd xmm1,qword ptr [eax]", 0x66, 0x0F, 0x16, 0x08 );
    FCML_I64( "movhpd xmm1,qword ptr [rax]", 0x66, 0x0F, 0x16, 0x08 );
    /* 66 0F 17 /r MOVHPD m64, xmm B Valid Valid Move double-precision floating-point value from high quadword of xmm to m64.*/
    FCML_I32( "movhpd qword ptr [eax],xmm1", 0x66, 0x0F, 0x17, 0x08 );
    FCML_I64( "movhpd qword ptr [rax],xmm1", 0x66, 0x0F, 0x17, 0x08 );
    /* VEX.NDS.128.66.0F 16 /r VMOVHPD xmm2,xmm1,m64*/
    FCML_I32( "vmovhpd xmm2,xmm1,qword ptr [eax]", 0xC5, 0xF1, 0x16, 0x10 );
    FCML_I64( "vmovhpd xmm0,xmm5,qword ptr [rax]", 0xc5, 0xd1, 0x16, 0x00 );
    /* VEX128.66.0F 17/r VMOVHPD m64, xmm1*/
    FCML_I64( "vmovhpd qword ptr [rax],xmm0", 0xc5, 0xf9, 0x17, 0x00 );
    /* GAS*/
    FCML_A64( "movhpd (%rax),%xmm1", 0x66, 0x0f, 0x16, 0x08 );
    FCML_A64( "movhpd %xmm1,(%rax)", 0x66, 0x0f, 0x17, 0x08 );
    FCML_A64( "vmovhpd (%rax),%xmm5,%xmm0", 0xc5, 0xd1, 0x16, 0x00 );
    FCML_A64( "vmovhpd %xmm0,(%rax)", 0xc5, 0xf9, 0x17, 0x00 );
}

void fcml_tf_instruction_MOVHPS(void) {
    /* 0F 16 /r MOVHPS xmm, m64 A Valid Valid Move two packed singleprecision floating-point values from m64 to high quadword of xmm.*/
    FCML_I32( "movhps xmm1,qword ptr [eax]", 0x0F, 0x16, 0x08 );
    FCML_I64( "movhps xmm1,qword ptr [rax]", 0x0F, 0x16, 0x08 );
    /* 0F 17 /r MOVHPS m64, xmm B Valid Valid Move two packed singleprecision floating-point values from high quadword of xmm to m64.*/
    FCML_I32( "movhps qword ptr [eax],xmm1", 0x0F, 0x17, 0x08 );
    FCML_I64( "movhps qword ptr [rax],xmm1", 0x0F, 0x17, 0x08 );
    /* VEX.NDS.128.0F 16 /r VMOVHPS xmm2,xmm1,m64*/
    FCML_I32( "vmovhps xmm2,xmm1,qword ptr [eax]", 0xC5, 0xF0, 0x16, 0x10 );
    FCML_I64( "vmovhps xmm0,xmm5,qword ptr [rax]", 0xc5, 0xd0, 0x16, 0x00 );
    /* VEX.128.0F 17 /r VMOVHPS m64,xmm1*/
    FCML_I64( "vmovhps qword ptr [rax],xmm0", 0xc5, 0xf8, 0x17, 0x00 );
    /* GAS*/
    FCML_A64( "movhps (%rax),%xmm1", 0x0f, 0x16, 0x08 );
    FCML_A64( "movhps %xmm1,(%rax)", 0x0f, 0x17, 0x08 );
    FCML_A64( "vmovhps (%rax),%xmm5,%xmm0", 0xc5, 0xd0, 0x16, 0x00 );
    FCML_A64( "vmovhps %xmm0,(%rax)", 0xc5, 0xf8, 0x17, 0x00 );
}

void fcml_tf_instruction_MOVLHPS(void) {
    /* 0F 16 /r MOVLHPS xmm1, xmm2 A Valid Valid Move two packed singleprecision floating-point values from low quadword of xmm2 to high quadword of xmm1.*/
    FCML_I32( "movlhps xmm2,xmm0", 0x0F, 0x16, 0xD0 );
    FCML_I32( "movlhps xmm3,xmm0", 0x0F, 0x16, 0xD8 );
    FCML_I64( "movlhps xmm2,xmm0", 0x0F, 0x16, 0xD0 );
    /* VEX.NDS.128.0F 16 /r VMOVLHPS xmm1,xmm2,xmm3*/
    FCML_I32( "vmovlhps xmm2,xmm5,xmm0", 0xC5, 0xD0, 0x16, 0xD0 );
    FCML_I64( "vmovlhps xmm0,xmm6,xmm0", 0xc5, 0xc8, 0x16, 0xc0 );
    /* GAS*/
    FCML_A64( "movlhps %xmm0,%xmm2", 0x0f, 0x16, 0xd0 );
    FCML_A64( "vmovlhps %xmm0,%xmm5,%xmm2", 0xc5, 0xd0, 0x16, 0xd0 );
}

void fcml_tf_instruction_MOVLPD(void) {
    /* 66 0F 12 /r MOVLPD xmm, m64*/
    FCML_I32( "movlpd xmm0,qword ptr [eax]", 0x66, 0x0F, 0x12, 0x00 );
    FCML_I64( "movlpd xmm0,qword ptr [rax]", 0x66, 0x0F, 0x12, 0x00 );
    /* 66 0F 13 /r MOVLPD m64,xmm*/
    FCML_I32( "movlpd qword ptr [eax],xmm0", 0x66, 0x0F, 0x13, 0x00 );
    FCML_I64( "movlpd qword ptr [rax],xmm0", 0x66, 0x0F, 0x13, 0x00 );
    /* VEX.NDS.128.66.0F 12 /r VMOVLPD xmm2,xmm1,m64*/
    FCML_I32( "vmovlpd xmm2,xmm1,qword ptr [eax]", 0xC5, 0xF1, 0x12, 0x10 );
    FCML_I64( "vmovlpd xmm0,xmm5,qword ptr [rax]", 0xc5, 0xd1, 0x12, 0x00 );
    /* VEX.128.66.0F 13 /r VMOVLPD m64,xmm1*/
    FCML_I64( "vmovlpd qword ptr [rax],xmm0", 0xc5, 0xf9, 0x13, 0x00 );
    /* GAS*/
    FCML_A64( "movlpd (%rax),%xmm0", 0x66, 0x0f, 0x12, 0x00 );
    FCML_A64( "movlpd %xmm0,(%rax)", 0x66, 0x0f, 0x13, 0x00 );
    FCML_A64( "vmovlpd (%rax),%xmm5,%xmm0", 0xc5, 0xd1, 0x12, 0x00 );
    FCML_A64( "vmovlpd %xmm0,(%rax)", 0xc5, 0xf9, 0x13, 0x00 );
}

void fcml_tf_instruction_MOVLPS(void) {
    /* 0F 12 /r MOVLPS xmm, m64*/
    FCML_I32( "movlps xmm0,qword ptr [eax]", 0x0F, 0x12, 0x00 );
    FCML_I64( "movlps xmm0,qword ptr [rax]", 0x0F, 0x12, 0x00 );
    /* 0F 13 /r MOVLPS m64, xmm*/
    FCML_I32( "movlps qword ptr [eax],xmm0", 0x0F, 0x13, 0x00 );
    FCML_I64( "movlps qword ptr [rax],xmm0",  0x0F, 0x13, 0x00 );
    /* VEX.NDS.128.0F 12 /r VMOVLPS xmm2, xmm1, m64*/
    FCML_I32( "vmovlps xmm2,xmm1,qword ptr [eax]", 0xC5, 0xF0, 0x12, 0x10 );
    FCML_I64( "vmovlps xmm0,xmm5,qword ptr [rax]", 0xc5, 0xd0, 0x12, 0x00 );
    /* VEX.128.0F 13/r VMOVLPS m64, xmm1*/
    FCML_I64( "vmovlps qword ptr [rax],xmm0", 0xc5, 0xf8, 0x13, 0x00 );
    /* GAS*/
    FCML_A64( "movlps (%rax),%xmm0", 0x0f, 0x12, 0x00 );
    FCML_A64( "movlps %xmm0,(%rax)", 0x0f, 0x13, 0x00 );
    FCML_A64( "vmovlps (%rax),%xmm5,%xmm0", 0xc5, 0xd0, 0x12, 0x00 );
    FCML_A64( "vmovlps %xmm0,(%rax)", 0xc5, 0xf8, 0x13, 0x00 );
}

void fcml_tf_instruction_MOVMSKPD(void) {
    /* 66 0F 50 /r MOVMSKPD reg, xmm*/
    FCML_I32( "movmskpd edx,xmm0", 0x66, 0x0F, 0x50, 0xD0 );
    FCML_I32( "movmskpd ebx,xmm0", 0x66, 0x0F, 0x50, 0xD8 );
    FCML_I64( "movmskpd rdx,xmm0", 0x66, 0x0F, 0x50, 0xD0 );
    /* VEX.128.66.0F 50 /r VMOVMSKPD reg, xmm2*/
    /* VEX.256.66.0F 50 /r VMOVMSKPD reg, ymm2*/
    FCML_I32( "vmovmskpd edx,xmm0", 0xc5, 0xf9, 0x50, 0xd0 );
    FCML_I32( "vmovmskpd ebx,xmm0", 0xc5, 0xf9, 0x50, 0xd8 );
    FCML_I64( "vmovmskpd rdx,ymm0", 0xc5, 0xfd, 0x50, 0xd0 );
    FCML_I64( "vmovmskpd rdx,ymm0", 0xc5, 0xfd, 0x50, 0xd0 );
    FCML_I32( "vmovmskpd ebx,ymm0", 0xc5, 0xfd, 0x50, 0xd8 );
    /* GAS*/
    FCML_A64( "movmskpd %xmm0,%rdx", 0x66, 0x0f, 0x50, 0xd0 );
    FCML_A64( "vmovmskpd %ymm0,%rbx", 0xc5, 0xfd, 0x50, 0xd8 );
}

void fcml_tf_instruction_MOVMSKPS(void) {
    /* 0F 50 /r MOVMSKPS reg,xmm*/
    FCML_I32( "movmskps edx,xmm0", 0x0F, 0x50, 0xD0 );
    FCML_I32( "movmskps ebx,xmm0", 0x0F, 0x50, 0xD8 );
    FCML_I64( "movmskps rdx,xmm0", 0x0F, 0x50, 0xD0 );
    /* VEX.128.0F 50 /r VMOVMSKPS reg,xmm2*/
    /* VEX.256.0F 50 /r VMOVMSKPS reg,ymm2*/
    FCML_I32( "vmovmskps edx,xmm0", 0xc5, 0xf8, 0x50, 0xd0 );
    FCML_I32( "vmovmskps ebx,xmm0", 0xc5, 0xf8, 0x50, 0xd8 );
    FCML_I64( "vmovmskps rdx,ymm0", 0xc5, 0xfc, 0x50, 0xd0 );
    FCML_I64( "vmovmskps rdx,ymm0", 0xc5, 0xfc, 0x50, 0xd0 );
    FCML_I32( "vmovmskps ebx,ymm0", 0xc5, 0xfc, 0x50, 0xd8 );
    /* GAS*/
    FCML_A64( "movmskps %xmm0,%rdx", 0x0f, 0x50, 0xd0 );
    FCML_A64( "vmovmskps %ymm0,%rdx", 0xc5, 0xfc, 0x50, 0xd0 );
}

void fcml_tf_instruction_MOVNTDQA(void) {
    /* 66 0F 38 2A /r MOVNTDQA xmm1, m128*/
    FCML_I32( "movntdqa xmm0,xmmword ptr [eax]", 0x66, 0x0F, 0x38, 0x2A, 0x00 );
    FCML_I64( "movntdqa xmm0,xmmword ptr [rax]", 0x66, 0x0F, 0x38, 0x2A, 0x00 );
    /* VEX.128.66.0F38 2A /r VMOVNTDQA xmm1,m128*/
    FCML_I64( "vmovntdqa xmm0,xmmword ptr [rax]", 0xC4, 0xE2, 0x79, 0x2A, 0x00 );
    /* VEX.256.66.0F38.WIG 2A /r VMOVNTDQA ymm1,m256*/
    FCML_I64( "vmovntdqa ymm0,ymmword ptr [rax]", 0xC4, 0xE2, 0x7D, 0x2A, 0x00 );
    /* GAS*/
    FCML_A64( "movntdqa (%rax),%xmm0", 0x66, 0x0f, 0x38, 0x2a, 0x00 );
    FCML_A64( "vmovntdqa (%rax),%xmm0", 0xc4, 0xe2, 0x79, 0x2a, 0x00 );
    FCML_A64( "vmovntdqa (%rax),%ymm0", 0xc4, 0xe2, 0x7d, 0x2a, 0x00 );
}

void fcml_tf_instruction_MOVNTDQ(void) {
    /* 66 0F E7 /r MOVNTDQ m128,xmm*/
    FCML_I32( "movntdq xmmword ptr [eax],xmm0", 0x66, 0x0F, 0xE7, 0x00 );
    FCML_I64( "movntdq xmmword ptr [rax],xmm0", 0x66, 0x0F, 0xE7, 0x00 );
    /* VEX.128.66.0F E7 /r VMOVNTDQ m128,xmm1*/
    FCML_I64( "vmovntdq xmmword ptr [rax],xmm0", 0xc5, 0xf9, 0xe7, 0x00 );
    /* GAS*/
    FCML_A64( "movntdq %xmm0,(%rax)", 0x66, 0x0f, 0xe7, 0x00 );
    FCML_A64( "vmovntdq %xmm0,(%rax)", 0xc5, 0xf9, 0xe7, 0x00 );
}

void fcml_tf_instruction_MOVNTI(void) {
    /* 0F C3 /r MOVNTI m32, r32*/
    /* REX.W + 0F C3 /r MOVNTI m64, r64*/
    FCML_I32( "movnti dword ptr [eax],eax", 0x0F, 0xC3, 0x00 );
    FCML_I32( "movnti dword ptr [eax],eax", 0x66, 0x0F, 0xC3, 0x00 );
    FCML_I64( "movnti dword ptr [rax],eax", 0x0F, 0xC3, 0x00 );
    FCML_I64( "movnti qword ptr [rax],rax", 0x48, 0x0F, 0xC3, 0x00 );
    /* GAS*/
    FCML_A64( "movnti %eax,(%rax)", 0x0f, 0xc3, 0x00 );
    FCML_A64( "movnti %rax,(%rax)", 0x48, 0x0f, 0xc3, 0x00 );
}

void fcml_tf_instruction_MOVNTPD(void) {
    /* 66 0F 2B /r MOVNTPD m128,xmm*/
    FCML_I32( "movntpd xmmword ptr [eax],xmm0", 0x66, 0x0F, 0x2B, 0x00 );
    FCML_I64( "movntpd xmmword ptr [rax],xmm0", 0x66, 0x0F, 0x2B, 0x00 );
    /* VEX.128.66.0F 2B /r VMOVNTPD m128, xmm1*/
    FCML_I64( "vmovntpd xmmword ptr [rax],xmm0", 0xc5, 0xf9, 0x2b, 0x00 );
    /* GAS*/
    FCML_A64( "movntpd %xmm0,(%rax)", 0x66, 0x0f, 0x2b, 0x00 );
    FCML_A64( "vmovntpd %xmm0,(%rax)", 0xc5, 0xf9, 0x2b, 0x00 );
}

void fcml_tf_instruction_MOVNTPS(void) {
    /* 0F 2B /r MOVNTPS m128,xmm*/
    FCML_I32( "movntps xmmword ptr [eax],xmm0", 0x0F, 0x2B, 0x00 );
    FCML_I64( "movntps xmmword ptr [rax],xmm0", 0x0F, 0x2B, 0x00 );
    /* VEX.128.0F 2B /r VMOVNTPS m128, xmm1*/
    FCML_I64( "vmovntps xmmword ptr [rax],xmm0", 0xc5, 0xf8, 0x2b, 0x00 );
    FCML_I32( "vmovntps xmmword ptr [eax],xmm0", 0xc5, 0xf8, 0x2b, 0x00 );
    /* GAS*/
    FCML_A64( "movntps %xmm0,(%rax)", 0x0f, 0x2b, 0x00 );
    FCML_A64( "vmovntps %xmm0,(%rax)", 0xc5, 0xf8, 0x2b, 0x00 );
}

void fcml_tf_instruction_MOVNTSD(void) {
    /* MOVNTSD mem64, xmm F2 0F 2B /r*/
    FCML_I32( "movntsd qword ptr [eax],xmm0", 0xF2, 0x0F, 0x2B, 0x00 );
    FCML_I64( "movntsd qword ptr [rax],xmm0", 0xF2, 0x0F, 0x2B, 0x00 );
    FCML_I32_FAILED( "FAIL", 0xF2, 0x0F, 0x2B, 0xC0 );
    /* GAS*/
    FCML_A64( "movntsd %xmm0,(%rax)", 0xf2, 0x0f, 0x2b, 0x00 );
}

void fcml_tf_instruction_MOVNTSS(void) {
    /* MOVNTSS mem32, xmm F3 0F 2B /r*/
    FCML_I32( "movntss dword ptr [eax],xmm0", 0xF3, 0x0F, 0x2B, 0x00 );
    FCML_I64( "movntss dword ptr [rax],xmm0", 0xF3, 0x0F, 0x2B, 0x00 );
    FCML_I32_FAILED( "FAIL", 0xF3, 0x0F, 0x2B, 0xC0 );
    /* GAS*/
    FCML_A64( "movntss %xmm0,(%rax)", 0xf3, 0x0f, 0x2b, 0x00 );
}

void fcml_tf_instruction_MOVNTQ(void) {
    /* 0F E7 /r MOVNTQ m64,mm*/
    FCML_I32( "movntq qword ptr [eax],mm0", 0x0F, 0xE7, 0x00 );
    FCML_I64( "movntq qword ptr [rax],mm0",  0x0F, 0xE7, 0x00 );
    /* GAS*/
    FCML_A64( "movntq %mm0,(%rax)", 0x0f, 0xe7, 0x00 );
}

void fcml_tf_instruction_MOVQ2DQ(void) {
    /* F3 0F D6 MOVQ2DQ xmm,mm*/
    FCML_I32( "movq2dq xmm2,mm0", 0xF3, 0x0F, 0xD6, 0xD0 );
    FCML_I32( "movq2dq xmm3,mm0", 0xF3, 0x0F, 0xD6, 0xD8 );
    FCML_I64( "movq2dq xmm2,mm0", 0xF3, 0x0F, 0xD6, 0xD0 );
    /* GAS*/
    FCML_A64( "movq2dq %mm0,%xmm2", 0xf3, 0x0f, 0xd6, 0xd0 );
}

void fcml_tf_instruction_MOVS(void) {
    /* A4 MOVS m8, m8*/
    FCML_I32( "rep movs byte ptr [di],byte ptr [si]", 0xF3, 0x67, 0xA4 );
    FCML_I32( "movs byte ptr [di],byte ptr [si]", 0x66, 0x67, 0xA4 );
    FCML_I32( "movs byte ptr [edi],byte ptr [esi]", 0xA4 );
    FCML_I64( "movs byte ptr [rdi],byte ptr [rsi]", 0xA4 );
    FCML_I64_A( "movsb", 0xA4 );
    FCML_I64_D( "movs byte ptr [rdi],byte ptr [rsi]", 0x40, 0xA4 );
    FCML_I64_D( "movs byte ptr [edi],byte ptr [esi]", 0x67, 0x40, 0xA4 );
    FCML_I64_D( "movs byte ptr [edi],byte ptr [esi]", 0x66, 0x67, 0x40, 0xA4 );
    /* GAS*/
    FCML_A64( "movsb (%rsi),(%rdi)", 0xa4 );
    FCML_A64( "movsb (%esi),(%edi)", 0x67, 0xa4 );
    FCML_A64_A( "movsb", 0xA4 );
    /* A5 MOVS m16, m16*/
    /* A5 MOVS m32, m32*/
    /* REX.W + A5 MOVS m64, m64*/
    FCML_I32( "rep movs dword ptr [di],dword ptr [si]", 0xF3, 0x67, 0xA5 );
    FCML_I32( "movs word ptr [di],word ptr [si]", 0x66, 0x67, 0xA5 );
    FCML_I32( "movs dword ptr [edi],dword ptr [esi]", 0xA5 );
    FCML_I64( "movs qword ptr [rdi],qword ptr [rsi]", 0x48, 0xA5 );
    FCML_I64( "movs dword ptr [rdi],dword ptr [rsi]", 0xA5 );
    FCML_I64_A( "movsw", 0x66, 0xA5 );
    FCML_I64_A( "movsd", 0xA5 );
    FCML_I64_A( "movsq", 0x48, 0xA5 );
    FCML_I64_D( "movs dword ptr [rdi],dword ptr [rsi]", 0x40, 0xA5 );
    FCML_I64_D( "movs dword ptr [edi],dword ptr [esi]", 0x67, 0x40, 0xA5 );
    FCML_I64_D( "movs word ptr [edi],word ptr [esi]", 0x66, 0x67, 0x40, 0xA5 );
    /* GAS*/
    FCML_A32( "rep movsl (%si),(%di)", 0xF3, 0x67, 0xA5 );
	FCML_A32( "movsw (%si),(%di)", 0x66, 0x67, 0xA5 );
	FCML_A32( "movsl (%esi),(%edi)", 0xA5 );
    FCML_A64_A( "movsw", 0x66, 0xA5 );
	FCML_A64_A( "movsl", 0xA5 );
	FCML_A64_A( "movsq", 0x48, 0xA5 );
}

void fcml_tf_instruction_MOVSD(void) {
    /* F2 0F 10 /r MOVSD xmm1,xmm2/m64*/
    FCML_I32( "movsd xmm2,mmword ptr [eax]", 0xF2, 0x0F, 0x10, 0x10 );
    FCML_I32_M( "movsd xmm3,xmm0", 2, FCML_MI( 0xf2, 0x0f, 0x11, 0xc3 ), FCML_MI( 0xf2, 0x0f, 0x10, 0xd8 ) );
    FCML_I64( "movsd xmm2,mmword ptr [rax]", 0xF2, 0x0F, 0x10, 0x10 );
    /* F2 0F 11 /r MOVSD xmm2/m64, xmm1*/
    FCML_I32( "movsd mmword ptr [eax],xmm2", 0xF2, 0x0F, 0x11, 0x10 );
    FCML_I32_M( "movsd xmm0,xmm3", 2, FCML_MI( 0xf2, 0x0f, 0x11, 0xd8 ), FCML_MI( 0xf2, 0x0f, 0x10, 0xc3 ) );
    FCML_I64( "movsd mmword ptr [rax],xmm2", 0xF2, 0x0F, 0x11, 0x10 );
    /* These two encodings are functionally equivalent. See: 26568_APM_v4.pdf*/
    /* VEX.NDS.128.F2.0F 10 /r VMOVSD xmm1, xmm2, xmm3*/
    FCML_I32_M( "vmovsd xmm1,xmm3,xmm0", 2, FCML_MI( 0xc5, 0xe3, 0x11, 0xc1 ), FCML_MI( 0xc5, 0xe3, 0x10, 0xc8 ) );
    FCML_I64_M( "vmovsd xmm1,xmm3,xmm0", 2, FCML_MI( 0xc5, 0xe3, 0x11, 0xc1 ), FCML_MI( 0xc5, 0xe3, 0x10, 0xc8 ) );
    /* VEX.NDS.128.F2.0F 11 /r VMOVSD xmm1, xmm2, xmm3*/
    FCML_I64_M( "vmovsd xmm1,xmm3,xmm0", 2, FCML_MI( 0xc5, 0xe3, 0x11, 0xc1 ), FCML_MI( 0xc5, 0xe3, 0x10, 0xc8 ) );
    FCML_I32_M( "vmovsd xmm0,xmm3,xmm1", 2, FCML_MI( 0xc5, 0xe3, 0x11, 0xc8 ), FCML_MI( 0xc5, 0xe3, 0x10, 0xc1 ) );
    /* VEX.128.F2.0F 10 /r VMOVSD xmm1, m64*/
    FCML_I32( "vmovsd xmm0,qword ptr [eax]", 0xc5, 0xfb, 0x10, 0x00 );
    /* VEX.128.F2.0F 11 /r VMOVSD m64, xmm1*/
    FCML_I32( "vmovsd qword ptr [eax],xmm0", 0xc5, 0xfb, 0x11, 0x00 );
    /* GAS*/
    FCML_A64( "movsd (%rax),%xmm2", 0xf2, 0x0f, 0x10, 0x10 );
    FCML_A64( "movsd %xmm2,(%rax)", 0xf2, 0x0f, 0x11, 0x10 );
    FCML_A64_M( "movsd %xmm3,%xmm0", 2, FCML_MI( 0xf2, 0x0f, 0x11, 0xd8 ), FCML_MI( 0xf2, 0x0f, 0x10, 0xc3 ) );
    FCML_A64_M( "vmovsd %xmm0,%xmm3,%xmm1", 2, FCML_MI( 0xc5, 0xe3, 0x11, 0xc1 ), FCML_MI( 0xc5, 0xe3, 0x10, 0xc8 ) );
    FCML_A64_M( "vmovsd %xmm1,%xmm3,%xmm0", 2, FCML_MI( 0xc5, 0xe3, 0x11, 0xc8 ), FCML_MI( 0xc5, 0xe3, 0x10, 0xc1 ) );
    FCML_A64( "vmovsd %xmm0,(%rax)", 0xc5, 0xfb, 0x11, 0x00 );
}

void fcml_tf_instruction_MOVSHDUP(void) {
    /* F3 0F 16 /r MOVSHDUP xmm1,xmm2/m128*/
    FCML_I32( "movshdup xmm2,xmmword ptr [eax]", 0xF3, 0x0F, 0x16, 0x10 );
    FCML_I32( "movshdup xmm3,xmm0", 0xF3, 0x0F, 0x16, 0xD8 );
    FCML_I64( "movshdup xmm2,xmmword ptr [rax]", 0xF3, 0x0F, 0x16, 0x10 );
    /* VEX.128.F3.0F 16 /r VMOVSHDUP xmm1,xmm2/m128*/
    /* VEX.256.F3.0F 16 /r VMOVSHDUP ymm1,ymm2/m256*/
    FCML_I64( "vmovshdup xmm3,xmm0", 0xc5, 0xfa, 0x16, 0xd8 );
    FCML_I32( "vmovshdup ymm0,ymmword ptr [eax]", 0xc5, 0xfe, 0x16, 0x00 );
    /* GAS*/
    FCML_A64( "movshdup %xmm0,%xmm3", 0xf3, 0x0f, 0x16, 0xd8 );
    FCML_A64( "movshdup (%rax),%xmm2", 0xf3, 0x0f, 0x16, 0x10 );
    FCML_A64( "vmovshdup (%rax),%ymm0", 0xc5, 0xfe, 0x16, 0x00 );
}

void fcml_tf_instruction_MOVSLDUP(void) {
    /* F3 0F 12 /r MOVSLDUP xmm1,xmm2/m128*/
    FCML_I32( "movsldup xmm2,xmmword ptr [eax]", 0xF3, 0x0F, 0x12, 0x10 );
    FCML_I32( "movsldup xmm3,xmm0", 0xF3, 0x0F, 0x12, 0xD8 );
    FCML_I64( "movsldup xmm2,xmmword ptr [rax]", 0xF3, 0x0F, 0x12, 0x10 );
    /* VEX.128.F3.0F 12 /r VMOVSLDUP xmm1,xmm2/m128*/
    /* VEX.256.F3.0F 12 /r VMOVSLDUP ymm1,ymm2/m256*/
    FCML_I64( "vmovsldup xmm3,xmm0", 0xc5, 0xfa, 0x12, 0xd8 );
    FCML_I32( "vmovsldup ymm0,ymmword ptr [eax]", 0xc5, 0xfe, 0x12, 0x00 );
    /* GAS*/
    FCML_A64( "movsldup %xmm0,%xmm3", 0xf3, 0x0f, 0x12, 0xd8 );
    FCML_A64( "vmovsldup (%rax),%ymm0", 0xc5, 0xfe, 0x12, 0x00 );
}

void fcml_tf_instruction_MOVSS(void) {
    /* F3 0F 10 /r MOVSS xmm1,xmm2/m32*/
    FCML_I32( "movss xmm2,dword ptr [eax]", 0xF3, 0x0F, 0x10, 0x10 );
    FCML_I32_M( "movss xmm3,xmm0", 2, FCML_MI( 0xf3, 0x0f, 0x11, 0xc3 ), FCML_MI( 0xf3, 0x0f, 0x10, 0xd8 ) );
    FCML_I64( "movss xmm2,dword ptr [rax]", 0xF3, 0x0F, 0x10, 0x10 );
    /* F3 0F 11 /r MOVSS xmm2/m32, xmm*/
    FCML_I32( "movss dword ptr [eax],xmm2", 0xF3, 0x0F, 0x11, 0x10 );
    FCML_I32_M( "movss xmm0,xmm3", 2, FCML_MI( 0xf3, 0x0f, 0x11, 0xd8 ), FCML_MI( 0xf3, 0x0f, 0x10, 0xc3 ) );
    FCML_I64( "movss dword ptr [rax],xmm2", 0xF3, 0x0F, 0x11, 0x10 );
    /* VEX.NDS.128.F3.0F 10 /r VMOVSS xmm1,xmm2,xmm3*/
    FCML_I32_M( "vmovss xmm1,xmm3,xmm0", 2, FCML_MI( 0xc5, 0xe2, 0x11, 0xc1 ), FCML_MI( 0xc5, 0xe2, 0x10, 0xc8 ) );
    FCML_I64_M( "vmovss xmm1,xmm3,xmm0", 2, FCML_MI( 0xc5, 0xe2, 0x11, 0xc1 ), FCML_MI( 0xc5, 0xe2, 0x10, 0xc8 ) );
    /* VEX.NDS.128.F3.0F 11 /r VMOVSS xmm1,xmm2,xmm3*/
    FCML_I32_M( "vmovss xmm0,xmm3,xmm1", 2, FCML_MI( 0xc5, 0xe2, 0x11, 0xc8 ), FCML_MI( 0xc5, 0xe2, 0x10, 0xc1 ) );
    FCML_I64_M( "vmovss xmm0,xmm3,xmm1", 2, FCML_MI( 0xc5, 0xe2, 0x11, 0xc8 ), FCML_MI( 0xc5, 0xe2, 0x10, 0xc1 ) );
    /* VEX.128.F3.0F 10 /r VMOVSS xmm1,m32*/
    FCML_I32( "vmovss xmm0,dword ptr [eax]", 0xc5, 0xfa, 0x10, 0x00 );
    /* VEX.128.F3.0F 11 /r VMOVSS m32,xmm1*/
    FCML_I32( "vmovss dword ptr [eax],xmm0", 0xc5, 0xfa, 0x11, 0x00 );
    /* GAS*/
    FCML_A64( "movss (%rax),%xmm2", 0xf3, 0x0f, 0x10, 0x10 );
    FCML_A64( "movss %xmm2,(%rax)", 0xf3, 0x0f, 0x11, 0x10 );
    FCML_A64_M( "vmovss %xmm1,%xmm3,%xmm0", 2, FCML_MI( 0xc5, 0xe2, 0x11, 0xc8 ), FCML_MI( 0xc5, 0xe2, 0x10, 0xc1 ) );
    FCML_A64( "vmovss %xmm0,(%rax)", 0xc5, 0xfa, 0x11, 0x00 );
}

void fcml_tf_instruction_MOVSX(void) {
    /* 0F BE /r MOVSX r16, r/m8*/
    /* 0F BE /r MOVSX r32, r/m8*/
    /* REX + 0F BE /r MOVSX r64, r/m8*/
    FCML_I32( "movsx dx,byte ptr [eax]", 0x66, 0x0F, 0xBE, 0x10 );
    FCML_I32( "movsx edx,byte ptr [eax]", 0x0F, 0xBE, 0x10 );
    FCML_I64( "movsx dx,byte ptr [rax]", 0x66, 0x0F, 0xBE, 0x10 );
    FCML_I64( "movsx edx,byte ptr [rax]", 0x0F, 0xBE, 0x10 );
    FCML_I64( "movsx rdx,byte ptr [rax]", 0x48, 0x0F, 0xBE, 0x10 );
    /* GAS*/
    FCML_A64( "movsbw (%rax),%dx", 0x66, 0x0f, 0xbe, 0x10 );
    FCML_A64( "movsbl (%rax),%edx", 0x0f, 0xbe, 0x10 );
    FCML_A64( "movsbl %al,%eax", 0x0f, 0xbe, 0xc0 );
    FCML_A64( "movsbq (%rax),%rdx", 0x48, 0x0f, 0xbe, 0x10 );
    /* 0F BF /r MOVSX r32, r/m16*/
    /* REX.W + 0F BF /r MOVSX r64, r/m16*/
    FCML_I32( "movsx edx,word ptr [eax]", 0x66, 0x0F, 0xBF, 0x10 );
    FCML_I32( "movsx edx,word ptr [eax]", 0x0F, 0xBF, 0x10 );
    FCML_I64( "movsx rdx,word ptr [rax]", 0x48, 0x0F, 0xBF, 0x10 );
    /* GAS*/
    FCML_A64( "movsww (%rax),%edx", 0x66, 0x0f, 0xbf, 0x10 );
    FCML_A64( "movswl (%rax),%edx", 0x0f, 0xbf, 0x10 );
    FCML_A64( "movswl %ax,%eax", 0x0f, 0xbf, 0xc0 );
    FCML_A64( "movswq (%rax),%rdx", 0x48, 0x0f, 0xbf, 0x10 );
    /* REX.W** + 63 /r MOVSXD r64, r/m32*/
    FCML_I64( "movsxd rdx,dword ptr [rax]", 0x48, 0x63, 0x10 );
}

void fcml_tf_instruction_MOVUPD(void) {
    /* 66 0F 10 /r MOVUPD xmm1,xmm2/m128*/
    FCML_I32( "movupd xmm2,xmmword ptr [eax]", 0x66, 0x0F, 0x10, 0x10 );
    FCML_I32_M( "movupd xmm3,xmm0", 2, FCML_MI( 0x66, 0x0f, 0x11, 0xc3 ), FCML_MI( 0x66, 0x0f, 0x10, 0xd8 ) );
    FCML_I64( "movupd xmm2,xmmword ptr [rax]", 0x66, 0x0F, 0x10, 0x10 );
    /* 66 0F 11 /r MOVUPD xmm2/m128,xmm*/
    FCML_I32( "movupd xmmword ptr [eax],xmm2", 0x66, 0x0F, 0x11, 0x10 );
    FCML_I32_M( "movupd xmm0,xmm3", 2, FCML_MI( 0x66, 0x0f, 0x11, 0xd8 ), FCML_MI( 0x66, 0x0f, 0x10, 0xc3 ) );
    FCML_I64( "movupd xmmword ptr [rax],xmm2", 0x66, 0x0F, 0x11, 0x10 );
    /* VEX.128.66.0F 10 /r VMOVUPD xmm1,xmm2/m128*/
    /* VEX.256.66.0F 10 /r VMOVUPD ymm1,ymm2/m256*/
    FCML_I3264_M( "vmovupd xmm3,xmm0", 2, FCML_MI( 0xc5, 0xf9, 0x11, 0xc3 ), FCML_MI( 0xc5, 0xf9, 0x10, 0xd8 ) );
    FCML_I32( "vmovupd xmm0,xmmword ptr [eax]", 0xc5, 0xf9, 0x10, 0x00 );
    /* VEX.128.66.0F 11 /r VMOVUPD xmm2/m128,xmm1*/
    /* VEX.256.66.0F 11 /r VMOVUPD ymm2/m256,ymm1*/
    FCML_I64_M( "vmovupd xmm0,xmm3", 2, FCML_MI( 0xc5, 0xf9, 0x11, 0xd8 ), FCML_MI( 0xc5, 0xf9, 0x10, 0xc3 ) );
    FCML_I32_M( "vmovupd xmm0,xmm3", 2, FCML_MI( 0xc5, 0xf9, 0x11, 0xd8 ), FCML_MI( 0xc5, 0xf9, 0x10, 0xc3 ) );
    FCML_I32( "vmovupd xmmword ptr [eax],xmm0", 0xc5, 0xf9, 0x11, 0x00 );
    /* GAS*/
    FCML_A64( "movupd (%rax),%xmm2", 0x66, 0x0f, 0x10, 0x10 );
    FCML_A64_M( "movupd %xmm3,%xmm0", 2, FCML_MI( 0x66, 0x0f, 0x11, 0xd8 ), FCML_MI( 0x66, 0x0f, 0x10, 0xc3 ) );
    FCML_A64( "vmovupd (%rax),%xmm0", 0xc5, 0xf9, 0x10, 0x00 );
    FCML_A64_M( "vmovupd %xmm3,%xmm0", 2, FCML_MI( 0xc5, 0xf9, 0x11, 0xd8 ), FCML_MI( 0xc5, 0xf9, 0x10, 0xc3 ) );
}

void fcml_tf_instruction_MOVUPS(void) {
    /* 0F 10 /r MOVUPS xmm1,xmm2/m128*/
    FCML_I32( "movups xmm2,xmmword ptr [eax]", 0x0F, 0x10, 0x10 );
    FCML_I32_M( "movups xmm3,xmm0", 2, FCML_MI( 0x0f, 0x11, 0xc3 ), FCML_MI( 0x0f, 0x10, 0xd8 ) );
    FCML_I64( "movups xmm2,xmmword ptr [rax]",0x0F, 0x10, 0x10 );
    /* 0F 11 /r MOVUPS xmm2/m128, xmm1*/
    FCML_I32( "movups xmmword ptr [eax],xmm2", 0x0F, 0x11, 0x10 );
    FCML_I32_M( "movups xmm0,xmm3", 2, FCML_MI( 0x0f, 0x11, 0xd8 ), FCML_MI( 0x0f, 0x10, 0xc3 ) );
    FCML_I64( "movups xmmword ptr [rax],xmm2", 0x0F, 0x11, 0x10 );
    /* VEX.128.0F 10 /r VMOVUPS xmm1,xmm2/m128*/
    /* VEX.256.0F 10 /r VMOVUPS ymm1,ymm2/m256*/
    FCML_I3264_M( "vmovups xmm3,xmm0", 2, FCML_MI( 0xc5, 0xf8, 0x11, 0xc3 ), FCML_MI( 0xc5, 0xf8, 0x10, 0xd8 ) );
    FCML_I32( "vmovups xmm0,xmmword ptr [eax]", 0xc5, 0xf8, 0x10, 0x00 );
    /* VEX.128.0F 11 /r VMOVUPS xmm2/m128,xmm1*/
    /* VEX.256.0F 11 /r VMOVUPS ymm2/m256,ymm1*/
    FCML_I3264_M( "vmovups xmm0,xmm3", 2, FCML_MI( 0xc5, 0xf8, 0x11, 0xd8 ), FCML_MI( 0xc5, 0xf8, 0x10, 0xc3 ) );
    FCML_I32( "vmovups xmmword ptr [eax],xmm0", 0xc5, 0xf8, 0x11, 0x00 );
    /* GAS*/
    FCML_A64( "movups (%rax),%xmm2", 0x0f, 0x10, 0x10 );
    FCML_A64_M( "movups %xmm3,%xmm0", 2, FCML_MI( 0x0f, 0x11, 0xd8 ), FCML_MI( 0x0f, 0x10, 0xc3 ) );
    FCML_A64( "vmovups (%rax),%xmm0", 0xc5, 0xf8, 0x10, 0x00 );
    FCML_A64_M( "vmovups %xmm3,%xmm0", 2, FCML_MI( 0xc5, 0xf8, 0x11, 0xd8 ), FCML_MI( 0xc5, 0xf8, 0x10, 0xc3 ) );
}

void fcml_tf_instruction_MOVZX(void) {
    /* 0F B6 /r MOVZX r16, r/m8*/
    /* 0F B6 /r MOVZX r32, r/m8*/
    /* REX.W + 0F B6 /r MOVZX r64, r/m8*/
    FCML_I32( "movzx dx,byte ptr [eax]", 0x66, 0x0F, 0xB6, 0x10 );
    FCML_I32( "movzx edx,byte ptr [eax]", 0x0F, 0xB6, 0x10 );
    FCML_I64( "movzx dx,byte ptr [rax]", 0x66, 0x0F, 0xB6, 0x10 );
    FCML_I64( "movzx edx,byte ptr [rax]", 0x0F, 0xB6, 0x10 );
    FCML_I64( "movzx rdx,byte ptr [rax]", 0x48, 0x0F, 0xB6, 0x10 );
    /* GAS*/
    FCML_A64( "movzbw (%rax),%dx", 0x66, 0x0f, 0xb6, 0x10 );
    FCML_A64( "movzbl (%rax),%edx", 0x0f, 0xb6, 0x10 );
    FCML_A64( "movzbl %al,%eax", 0x0f, 0xb6, 0xc0 );
    FCML_A64( "movzbq (%rax),%rdx", 0x48, 0x0f, 0xb6, 0x10 );
    /* 0F B7 /r MOVZX r32,r/m16*/
    /* REX.W + 0F B7 /r MOVZX r64,r/m16*/
    FCML_I32( "movzx edx,word ptr [eax]", 0x66, 0x0F, 0xB7, 0x10 );
    FCML_I32( "movzx edx,word ptr [eax]", 0x0F, 0xB7, 0x10 );
    FCML_I64( "movzx edx,word ptr [rax]", 0x66, 0x0F, 0xB7, 0x10 );
    FCML_I64( "movzx rdx,word ptr [rax]", 0x48, 0x0F, 0xB7, 0x10 );
    /* GAS*/
    FCML_A64( "movzww (%rax),%edx", 0x66, 0x0f, 0xb7, 0x10 );
    FCML_A64( "movzwl (%rax),%edx", 0x0f, 0xb7, 0x10 );
    FCML_A64( "movzwl %ax,%eax", 0x0f, 0xb7, 0xc0 );
    FCML_A64( "movzwq (%rax),%rdx", 0x48, 0x0f, 0xb7, 0x10 );
}

void fcml_tf_instruction_MPSADBW(void) {
    /* 66 0F 3A 42 /r ib MPSADBW xmm1, xmm2/m128, imm8*/
    FCML_I32( "mpsadbw xmm2,xmmword ptr [eax],20h", 0x66, 0x0F, 0x3A, 0x42, 0x10, 0x20 );
    FCML_I32( "mpsadbw xmm2,xmm6,20h", 0x66, 0x0F, 0x3A, 0x42, 0xD6, 0x20 );
    FCML_I64( "mpsadbw xmm2,xmmword ptr [rax],20h", 0x66, 0x0F, 0x3A, 0x42, 0x10, 0x20 );
    FCML_I64( "mpsadbw xmm2,xmmword ptr [rax],20h", 0x66, 0x0F, 0x3A, 0x42, 0x10, 0x20 );
    /* VEX.NDS.128.66.0F3A 42 /r ib VMPSADBW xmm1,xmm2,xmm3/m128,imm8*/
    FCML_I32( "vmpsadbw xmm2,xmm6,xmmword ptr [ecx+eax],20h", 0xC4, 0xE3, 0x49, 0x42, 0x14, 0x01, 0x20 );
    FCML_I64( "vmpsadbw xmm2,xmm6,xmmword ptr [rcx+rax],20h", 0xC4, 0xE3, 0x49, 0x42, 0x14, 0x01, 0x20 );
    /* VEX.NDS.256.66.0F3A.WIG 42 /r ib VMPSADBW ymm1,ymm2,ymm3/m256,imm8*/
    FCML_I32( "vmpsadbw ymm2,ymm6,ymmword ptr [ecx+eax],20h", 0xC4, 0xE3, 0x4D, 0x42, 0x14, 0x01, 0x20 );
    FCML_I64( "vmpsadbw ymm2,ymm6,ymmword ptr [rcx+rax],20h", 0xC4, 0xE3, 0x4D, 0x42, 0x14, 0x01, 0x20 );
    /* GAS*/
    FCML_A64( "mpsadbw $0x20,(%rax),%xmm2", 0x66, 0x0f, 0x3a, 0x42, 0x10, 0x20 );
    FCML_A64( "mpsadbw $0x20,%xmm6,%xmm2", 0x66, 0x0f, 0x3a, 0x42, 0xd6, 0x20 );
    FCML_A64( "vmpsadbw $0x20,(%rcx,%rax),%xmm6,%xmm2", 0xc4, 0xe3, 0x49, 0x42, 0x14, 0x01, 0x20 );
    FCML_A64( "vmpsadbw $0x20,(%rcx,%rax),%ymm6,%ymm2", 0xc4, 0xe3, 0x4d, 0x42, 0x14, 0x01, 0x20 );
}

void fcml_tf_instruction_MUL(void) {
    /* F6 /4 MUL r/m8*/
    /* REX + F6 /4 MUL r/m8*/
    FCML_I32_D( "mul byte ptr [eax]", 0x66, 0xF6, 0x20 );
    FCML_I32( "mul byte ptr [eax]", 0xF6, 0x20 );
    FCML_I64_D( "mul byte ptr [rax]", 0x66, 0xF6, 0x20 );
    FCML_I64( "mul byte ptr [rax]", 0xF6, 0x20 );
    FCML_I64_D( "mul byte ptr [rax]", 0x48, 0xF6, 0x20 );
    /* F7 /4 MUL r/m16*/
    /* F7 /4 MUL r/m32*/
    /* REX.W + F7 /4 MUL r/m64*/
    FCML_I32_D( "mul word ptr [eax]", 0x66, 0xF7, 0x20 );
    FCML_I32( "mul dword ptr [eax]", 0xF7, 0x20 );
    FCML_I64_D( "mul word ptr [rax]", 0x66, 0xF7, 0x20 );
    FCML_I64( "mul dword ptr [rax]", 0xF7, 0x20 );
    FCML_I64_D( "mul qword ptr [rax]", 0x48, 0xF7, 0x20 );
    /* GAS*/
    FCML_A64( "mulb (%rax)", 0xf6, 0x20 );
    FCML_A64_A( "mul %dl", 0xf6, 0xe2 );
    FCML_A64( "mulw (%rax)", 0x66, 0xf7, 0x20 );
    FCML_A64( "mull (%rax)", 0xf7, 0x20 );
    FCML_A64( "mulq (%rax)", 0x48, 0xf7, 0x20 );
    FCML_A64_A( "mul %edx", 0xf7, 0xe2 );
}

void fcml_tf_instruction_MULPD(void) {
    /* 66 0F 59 /r MULPD xmm1,xmm2/m128*/
    FCML_I32( "mulpd xmm2,xmmword ptr [eax]", 0x66, 0x0F, 0x59, 0x10 );
    FCML_I64( "vmulpd xmm3,xmm0,xmm0", 0xc5, 0xf9, 0x59, 0xd8 );
    FCML_I64( "mulpd xmm2,xmmword ptr [rax]", 0x66, 0x0F, 0x59, 0x10 );
    /* VEX.NDS.128.66.0F 59 /r VMULPD xmm1,xmm2,xmm3/m128*/
    /* VEX.NDS.256.66.0F 59 /r VMULPD ymm1,ymm2,ymm3/m256*/
    FCML_I64( "vmulpd xmm3,xmm0,xmm0", 0xc5, 0xf9, 0x59, 0xd8 );
    FCML_I32( "vmulpd ymm3,ymm0,ymm0", 0xc5, 0xfd, 0x59, 0xd8 );
    FCML_I32( "vmulpd ymm3,ymm3,ymmword ptr [eax]", 0xc5, 0xe5, 0x59, 0x18 );
    /* GAS*/
    FCML_A64( "mulpd (%rax),%xmm2", 0x66, 0x0f, 0x59, 0x10 );
    FCML_A64( "vmulpd %xmm0,%xmm0,%xmm3", 0xc5, 0xf9, 0x59, 0xd8 );
    FCML_A64( "vmulpd (%rax),%ymm3,%ymm3", 0xc5, 0xe5, 0x59, 0x18 );
}

void fcml_tf_instruction_MULPS(void) {
    /* 0F 59 /r MULPS xmm1,xmm2/m128*/
    FCML_I32( "mulps xmm2,xmmword ptr [eax]", 0x0F, 0x59, 0x10 );
    FCML_I32( "mulps xmm3,xmm0", 0x0F, 0x59, 0xD8 );
    FCML_I64( "mulps xmm2,xmmword ptr [rax]", 0x0F, 0x59, 0x10 );
    /* VEX.NDS.128.0F 59 /r VMULPS xmm1,xmm2,xmm3/m128*/
    /* VEX.NDS.256.0F 59 /r VMULPS ymm1,ymm2,ymm3/m256*/
    FCML_I64( "vmulps xmm3,xmm0,xmm0", 0xc5, 0xf8, 0x59, 0xd8 );
    FCML_I32( "vmulps ymm3,ymm0,ymm0", 0xc5, 0xfc, 0x59, 0xd8 );
    FCML_I32( "vmulps ymm3,ymm3,ymmword ptr [eax]", 0xc5, 0xe4, 0x59, 0x18 );
    /* GAS*/
    FCML_A64( "mulps (%rax),%xmm2", 0x0f, 0x59, 0x10 );
    FCML_A64( "mulps %xmm0,%xmm3", 0x0f, 0x59, 0xd8 );
    FCML_A64( "vmulps (%rax),%ymm3,%ymm3", 0xc5, 0xe4, 0x59, 0x18 );
}

void fcml_tf_instruction_MULSD(void) {
    /*F2 0F 59 /r MULSD xmm1,xmm2/m64*/
    FCML_I32( "mulsd xmm2,mmword ptr [eax]", 0xF2, 0x0F, 0x59, 0x10 );
    FCML_I32( "mulsd xmm3,xmm0", 0xF2, 0x0F, 0x59, 0xD8 );
    FCML_I64( "mulsd xmm2,mmword ptr [rax]", 0xF2, 0x0F, 0x59, 0x10 );
    /* VEX.NDS.128.F2.0F 59 /r VMULSD xmm1,xmm2,xmm3/m64*/
    FCML_I3264( "vmulsd xmm3,xmm3,xmm0", 0xc5, 0xe3, 0x59, 0xd8 );
    FCML_I32( "vmulsd xmm3,xmm0,mmword ptr [eax]", 0xc5, 0xfb, 0x59, 0x18 );
    /* GAS*/
    FCML_A64( "mulsd (%rax),%xmm2", 0xf2, 0x0f, 0x59, 0x10 );
    FCML_A64( "mulsd %xmm0,%xmm3", 0xf2, 0x0f, 0x59, 0xd8 );
    FCML_A64( "vmulsd (%rax),%xmm0,%xmm3", 0xc5, 0xfb, 0x59, 0x18 );
}

void fcml_tf_instruction_MULSS(void) {
    /* F3 0F 59 /r MULSS xmm1,xmm2/m32*/
    FCML_I32( "mulss xmm2,dword ptr [eax]", 0xF3, 0x0F, 0x59, 0x10 );
    FCML_I32( "mulss xmm3,xmm0", 0xF3, 0x0F, 0x59, 0xD8 );
    FCML_I64( "mulss xmm2,dword ptr [rax]", 0xF3, 0x0F, 0x59, 0x10 );
    /* VEX.NDS.128.F3.0F 59 /r VMULSS xmm1,xmm2,xmm3/m32*/
    FCML_I3264( "vmulss xmm3,xmm7,xmm0", 0xc5, 0xc2, 0x59, 0xd8 );
    FCML_I32( "vmulss xmm3,xmm0,dword ptr [eax]", 0xc5, 0xfa, 0x59, 0x18 );
    /* GAS*/
    FCML_A64( "mulss %xmm0,%xmm3", 0xf3, 0x0f, 0x59, 0xd8 );
    FCML_A64( "mulss (%rax),%xmm2", 0xf3, 0x0f, 0x59, 0x10 );
    FCML_A64( "vmulss (%rax),%xmm0,%xmm3", 0xc5, 0xfa, 0x59, 0x18 );
}

void fcml_tf_instruction_MWAIT(void) {
    /* 0F 01 C9*/
    FCML_I3264( "mwait", 0x0F, 0x01, 0xC9 );
    /* GAS*/
    FCML_A64( "mwait", 0x0f, 0x01, 0xc9 );
}

void fcml_tf_instruction_MULX(void) {
	/* MULX*/
	/* VEX.NDD.LZ.F2.0F38.W0 F6 /r MULX r32a, r32b, r/m32*/
	FCML_I32( "mulx eax,edi,dword ptr [eax]", 0xC4, 0xE2, 0x43, 0xF6, 0x00 );
	FCML_I32( "mulx eax,edi,eax", 0xC4, 0xE2, 0x43, 0xF6, 0xC0 );
	/* VEX.NDD.LZ.F2.0F38.W1 F6 /r MULX r64a, r64b, r/m64*/
	FCML_I64( "mulx rax,rdi,qword ptr [rax]", 0xC4, 0xE2, 0xC3, 0xF6, 0x00 );
	FCML_I64( "mulx rax,rdi,rax", 0xC4, 0xE2, 0xC3, 0xF6, 0xC0 );
	/* GAS*/
	FCML_A64( "mulx (%rax),%rdi,%rax", 0xc4, 0xe2, 0xc3, 0xf6, 0x00 );
	FCML_A64( "mulx %rax,%rdi,%rax", 0xc4, 0xe2, 0xc3, 0xf6, 0xc0 );
}

fcml_stf_test_case fctl_ti_instructions_m[] = {
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
	{ "fcml_tf_instruction_MOVQ", fcml_tf_instruction_MOVQ },
	{ "fcml_tf_instruction_MOVDDUP", fcml_tf_instruction_MOVDDUP },
	{ "fcml_tf_instruction_MOVDQA", fcml_tf_instruction_MOVDQA },
	{ "fcml_tf_instruction_MOVDQU", fcml_tf_instruction_MOVDQU },
	{ "fcml_tf_instruction_MOVDQ2Q", fcml_tf_instruction_MOVDQ2Q },
	{ "fcml_tf_instruction_MOVHLPS", fcml_tf_instruction_MOVHLPS },
	{ "fcml_tf_instruction_MOVHPD", fcml_tf_instruction_MOVHPD },
	{ "fcml_tf_instruction_MOVHPS", fcml_tf_instruction_MOVHPS },
	{ "fcml_tf_instruction_MOVLHPS", fcml_tf_instruction_MOVLHPS },
	{ "fcml_tf_instruction_MOVLPD", fcml_tf_instruction_MOVLPD },
	{ "fcml_tf_instruction_MOVLPS", fcml_tf_instruction_MOVLPS },
	{ "fcml_tf_instruction_MOVMSKPD", fcml_tf_instruction_MOVMSKPD },
	{ "fcml_tf_instruction_MOVMSKPS", fcml_tf_instruction_MOVMSKPS },
	{ "fcml_tf_instruction_MOVNTDQA", fcml_tf_instruction_MOVNTDQA },
	{ "fcml_tf_instruction_MOVNTDQ", fcml_tf_instruction_MOVNTDQ },
	{ "fcml_tf_instruction_MOVNTI", fcml_tf_instruction_MOVNTI },
	{ "fcml_tf_instruction_MOVNTPD", fcml_tf_instruction_MOVNTPD },
	{ "fcml_tf_instruction_MOVNTPS", fcml_tf_instruction_MOVNTPS },
	{ "fcml_tf_instruction_MOVNTSD", fcml_tf_instruction_MOVNTSD },
	{ "fcml_tf_instruction_MOVNTSS", fcml_tf_instruction_MOVNTSS },
	{ "fcml_tf_instruction_MOVNTQ", fcml_tf_instruction_MOVNTQ },
	{ "fcml_tf_instruction_MOVQ2DQ", fcml_tf_instruction_MOVQ2DQ },
	{ "fcml_tf_instruction_MOVS", fcml_tf_instruction_MOVS },
	{ "fcml_tf_instruction_MOVSD", fcml_tf_instruction_MOVSD },
	{ "fcml_tf_instruction_MOVSHDUP", fcml_tf_instruction_MOVSHDUP },
	{ "fcml_tf_instruction_MOVSLDUP", fcml_tf_instruction_MOVSLDUP },
	{ "fcml_tf_instruction_MOVSS", fcml_tf_instruction_MOVSS },
	{ "fcml_tf_instruction_MOVSX", fcml_tf_instruction_MOVSX },
	{ "fcml_tf_instruction_MOVUPD", fcml_tf_instruction_MOVUPD },
	{ "fcml_tf_instruction_MOVUPS", fcml_tf_instruction_MOVUPS },
	{ "fcml_tf_instruction_MOVZX", fcml_tf_instruction_MOVZX },
	{ "fcml_tf_instruction_MPSADBW", fcml_tf_instruction_MPSADBW },
	{ "fcml_tf_instruction_MUL", fcml_tf_instruction_MUL },
	{ "fcml_tf_instruction_MULPD", fcml_tf_instruction_MULPD },
	{ "fcml_tf_instruction_MULPS", fcml_tf_instruction_MULPS },
	{ "fcml_tf_instruction_MULSD", fcml_tf_instruction_MULSD },
	{ "fcml_tf_instruction_MULSS", fcml_tf_instruction_MULSS },
	{ "fcml_tf_instruction_MWAIT", fcml_tf_instruction_MWAIT },
	{ "fcml_tf_instruction_MULX", fcml_tf_instruction_MULX },
	FCML_STF_NULL_TEST
};

fcml_stf_test_suite fctl_si_instructions_m = {
	"suite-fctl_ti_instructions_m", fcml_tf_instructions_m_suite_init, fcml_tf_instructions_m_suite_cleanup, fctl_ti_instructions_m
};
