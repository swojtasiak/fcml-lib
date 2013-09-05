/*
 * instructions.c
 *
 *  Created on: 01-06-2013
 *      Author: tAs
 */

#include "fcml_env.h"
#include "fcml_assembler.h"
#include "instructions_b_t.h"

int fcml_tf_instructions_c_suite_init(void) {
	return 0;
}

int fcml_tf_instructions_c_suite_cleanup(void) {
	return 0;
}

void fcml_tf_instruction_CALL(void) {
    // m16:16,m16:32,m16:64
    FCML_I64_FAILED( "FAIL", 0x48, 0x66, 0xFF, 0x57, 0x01 );
    FCML_I32( "call far fword ptr [ebx+00000001h]", 0xFF, 0x5B, 0x01 );
    FCML_I32( "call far dword ptr [ebx+00000001h]", 0x66, 0xFF, 0x5B, 0x01 );
    FCML_I64_D( "call far tbyte ptr [rbx+0000000000000001h]", 0x66, 0x48, 0xFF, 0x5B, 0x01 ); // Verified.
    FCML_I64_D( "call far dword ptr [rbx+0000000000000001h]", 0x66, 0x40, 0xFF, 0x5B, 0x01 ); // Verified.
    FCML_I64( "call far tbyte ptr [rbx+0000000000000001h]", 0x48, 0xFF, 0x5B, 0x01 ); // Verified.
    FCML_I64( "call far dword ptr [rbx+0000000000000001h]", 0x66, 0xFF, 0x5B, 0x01 ); // Verified.
    FCML_I64( "call far dword ptr [ebx+00000001h]", 0x66, 0x67, 0xFF, 0x5B, 0x01 );
    FCML_I64( "call far fword ptr [rbx+0000000000000001h]", 0xFF, 0x5B, 0x01 );
    FCML_I64_D( "call far fword ptr [rbx+0000000000000001h]", 0x40, 0xFF, 0x5B, 0x01 );
    // prt16:16 ptr16:32
    FCML_I32( "call far 6655h:44332211h", 0x9A, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66 );
    FCML_I32( "call far 4433h:2211h", 0x66, 0x9A, 0x11, 0x22, 0x33, 0x44 );
    // r/m32
    FCML_I32_M( "call dword ptr [edi+00000001h]", 2, FCML_MI( 0xFF, 0x57, 0x01 ), FCML_MI( 0x66, 0xff, 0x5f, 0x01 ) );
    FCML_I32_A( "call near dword ptr [edi+00000001h]", 0xFF, 0x57, 0x01 );
	// r/m16
	FCML_I32( "call word ptr [edi+00000001h]", 0x66, 0xFF, 0x57, 0x01 );
	// r/m64 (Size directives are the same for operand size 32 and 64 bits.)
	FCML_I64_D( "call qword ptr [rdi+0000000000000001h]", 0x66, 0x48, 0xFF, 0x57, 0x01 );
	FCML_I64_D( "call qword ptr [rdi+0000000000000001h]", 0x48, 0xFF, 0x57, 0x01 );
	FCML_I64_D( "call qword ptr [rdi+0000000000000001h]", 0xFF, 0x57, 0x01 );
	// rel16
	FCML_I32_P( "call 00001044h",  0x66, 0xE8, 0x40, 0x00 );
    FCML_I32_P( "call 00001004h",  0x66, 0xE8, 0x00, 0x00 );
    FCML_I32_P( "call 00001003h",  0x66, 0xE8, 0xFF, 0xFF );
    FCML_I32_P( "call 00001084h",  0x66, 0xE8, 0x80, 0x00 );
    FCML_I32_P( "call 00009004h",  0x66, 0xE8, 0x00, 0x80 );
    FCML_I32_P( "call 0000809dh",  0x66, 0xE8, 0x99, 0x70 );
    // rel32
    FCML_I32_P( "call 0ff701005h", 0xE8, 0x00, 0x00, 0x30, 0xFF );
    FCML_I32_P( "call 00401004h", 0xE8, 0xFF, 0xFF, 0xFF, 0xFF );
    FCML_I32_P( "call 00401006h", 0xE8, 0x01, 0x00, 0x00, 0x00 );
    FCML_I32_P( "call 80401005h", 0xE8, 0x00, 0x00, 0x00, 0x80 );
    FCML_I32_P( "call 79d9a99eh", 0xE8, 0x99, 0x99, 0x99, 0x79 );
    // rel32 in 64 bits.
    FCML_I64_A_FAILED( "call 0000800500401005h", 0xE8, 0x00, 0x00, 0x00, 0x00 );
    FCML_I64_P( "call 0000800000401004h", 0xE8, 0xFF, 0xFF, 0xFF, 0xFF );
    FCML_I64_P( "call 00007fff80401005h", 0xE8, 0x00, 0x00, 0x00, 0x80 );
    FCML_I64_P( "call 0000800079d9a99eh", 0xE8, 0x99, 0x99, 0x99, 0x79 );
}

void fcml_tf_instruction_CBW_CWDE_CDQE(void) {
    FCML_I32( "cbw", 0x66, 0x98 );
    FCML_I32( "cwde", 0x98 );
    FCML_I64( "cdqe", 0x48, 0x98 );
}

void fcml_tf_instruction_CLC(void) {
    FCML_I32( "clc", 0xf8 );
    FCML_I64( "clc", 0xf8 );
}

void fcml_tf_instruction_CLD(void) {
    FCML_I3264( "cld", 0xfc );
}

void fcml_tf_instruction_CLFLUSH(void) {
    FCML_I32( "clflush byte ptr [esp+edx+00000020h]", 0x0F, 0xAE, 0x7C, 0x14, 0x20 );
    FCML_I32_D( "clflush byte ptr [esp+edx+00000020h]", 0x66, 0x0F, 0xAE, 0x7C, 0x14, 0x20 );
    FCML_I64( "clflush byte ptr [rsp+rdx+0000000000000020h]", 0x0F, 0xAE, 0x7C, 0x14, 0x20 );
    FCML_I64_D( "clflush byte ptr [rsp+rdx+0000000000000020h]", 0x66, 0x0F, 0xAE, 0x7C, 0x14, 0x20 );
    FCML_I64( "clflush byte ptr [rbp+0000000000000001h]", 0x0F, 0xAE, 0x7D, 0x01 );
}

void fcml_tf_instruction_CLI(void) {
    FCML_I3264( "cli", 0xfa );
}

void fcml_tf_instruction_CLGI(void) {
    FCML_I3264( "clgi", 0x0F, 0x01, 0xDD );
}

void fcml_tf_instruction_CLTS(void) {
    FCML_I3264( "clts", 0x0f, 0x06 );
}

void fcml_tf_instruction_CMC(void) {
    FCML_I3264( "cmc", 0xf5 );
}

void fcml_tf_instruction_CMOV(void) {
    FCML_I32( "cmovo esp,dword ptr [ebp+04030201h]", 0x0f, 0x40, 0xa5, 0x01, 0x02, 0x03, 04 );
    FCML_I32( "cmovo sp,word ptr [di+0201h]", 0x66, 0x67, 0x0f, 0x40, 0xa5, 0x01, 0x02 );
    FCML_I32( "cmovo esp,dword ptr [di+0201h]", 0x67, 0x0f, 0x40, 0xa5, 0x01, 0x02 );
    FCML_I64( "cmovo r12,qword ptr [r9+rcx*4+0000000000000001h]", 0x4D, 0x0f, 0x40, 0x64, 0x89, 0x01 );
    FCML_I32( "cmovo esp,dword ptr [ebp+04030201h]", 0x0f, 0x40, 0xa5, 0x01, 0x02, 0x03, 04 );
    FCML_I32( "cmovno esp,dword ptr [ebp+04030201h]", 0x0f, 0x41, 0xa5, 0x01, 0x02, 0x03, 04 );
    FCML_I32_A( "cmovnae esp,dword ptr [ebp+04030201h]", 0x0f, 0x42, 0xa5, 0x01, 0x02, 0x03, 04 );
    FCML_I32_A( "cmovb esp,dword ptr [ebp+04030201h]", 0x0f, 0x42, 0xa5, 0x01, 0x02, 0x03, 04 );
    FCML_I32( "cmovc esp,dword ptr [ebp+04030201h]", 0x0f, 0x42, 0xa5, 0x01, 0x02, 0x03, 04 );
    FCML_I32_A( "cmovnb esp,dword ptr [ebp+04030201h]", 0x0f, 0x43, 0xa5, 0x01, 0x02, 0x03, 04 );
    FCML_I32_A( "cmovae esp,dword ptr [ebp+04030201h]", 0x0f, 0x43, 0xa5, 0x01, 0x02, 0x03, 04 );
    FCML_I32( "cmovnc esp,dword ptr [ebp+04030201h]", 0x0f, 0x43, 0xa5, 0x01, 0x02, 0x03, 04 );
    FCML_I32_A( "cmovz esp,dword ptr [ebp+04030201h]", 0x0f, 0x44, 0xa5, 0x01, 0x02, 0x03, 04 );
    FCML_I32( "cmove esp,dword ptr [ebp+04030201h]", 0x0f, 0x44, 0xa5, 0x01, 0x02, 0x03, 04 );
    FCML_I32_A( "cmovnz esp,dword ptr [ebp+04030201h]", 0x0f, 0x45, 0xa5, 0x01, 0x02, 0x03, 04 );
    FCML_I32( "cmovne esp,dword ptr [ebp+04030201h]", 0x0f, 0x45, 0xa5, 0x01, 0x02, 0x03, 04 );
    FCML_I32_A( "cmovna esp,dword ptr [ebp+04030201h]", 0x0f, 0x46, 0xa5, 0x01, 0x02, 0x03, 04 );
    FCML_I32( "cmovbe esp,dword ptr [ebp+04030201h]", 0x0f, 0x46, 0xa5, 0x01, 0x02, 0x03, 04 );
    FCML_I32_A( "cmova esp,dword ptr [ebp+04030201h]", 0x0f, 0x47, 0xa5, 0x01, 0x02, 0x03, 04 );
    FCML_I32( "cmovnbe esp,dword ptr [ebp+04030201h]", 0x0f, 0x47, 0xa5, 0x01, 0x02, 0x03, 04 );
    FCML_I32( "cmovs esp,dword ptr [ebp+04030201h]", 0x0f, 0x48, 0xa5, 0x01, 0x02, 0x03, 04 );
    FCML_I32( "cmovns esp,dword ptr [ebp+04030201h]", 0x0f, 0x49, 0xa5, 0x01, 0x02, 0x03, 04 );
    FCML_I32_A( "cmovpe esp,dword ptr [ebp+04030201h]", 0x0f, 0x4a, 0xa5, 0x01, 0x02, 0x03, 04 );
    FCML_I32( "cmovp esp,dword ptr [ebp+04030201h]", 0x0f, 0x4a, 0xa5, 0x01, 0x02, 0x03, 04 );
    FCML_I32_A( "cmovpo esp,dword ptr [ebp+04030201h]", 0x0f, 0x4b, 0xa5, 0x01, 0x02, 0x03, 04 );
    FCML_I32( "cmovnp esp,dword ptr [ebp+04030201h]", 0x0f, 0x4b, 0xa5, 0x01, 0x02, 0x03, 04 );
    FCML_I32_A( "cmovnge esp,dword ptr [ebp+04030201h]", 0x0f, 0x4c, 0xa5, 0x01, 0x02, 0x03, 04 );
    FCML_I32( "cmovl esp,dword ptr [ebp+04030201h]", 0x0f, 0x4c, 0xa5, 0x01, 0x02, 0x03, 04 );
    FCML_I32_A( "cmovge esp,dword ptr [ebp+04030201h]", 0x0f, 0x4d, 0xa5, 0x01, 0x02, 0x03, 04 );
    FCML_I32( "cmovnl esp,dword ptr [ebp+04030201h]", 0x0f, 0x4d, 0xa5, 0x01, 0x02, 0x03, 04 );
    FCML_I32_A( "cmovng esp,dword ptr [ebp+04030201h]", 0x0f, 0x4e, 0xa5, 0x01, 0x02, 0x03, 04 );
    FCML_I32( "cmovle esp,dword ptr [ebp+04030201h]", 0x0f, 0x4e, 0xa5, 0x01, 0x02, 0x03, 04 );
    FCML_I32_A( "cmovg esp,dword ptr [ebp+04030201h]", 0x0f, 0x4f, 0xa5, 0x01, 0x02, 0x03, 04 );
    FCML_I32( "cmovnle esp,dword ptr [ebp+04030201h]", 0x0f, 0x4f, 0xa5, 0x01, 0x02, 0x03, 04 );
}

void fcml_tf_instruction_CMP(void) {
    // 3C ib CMP AL, imm8 D Valid Valid Compare imm8 with AL.
    FCML_I32_M( "cmp al,42h", 2, FCML_MI( 0x3C, 0x42 ), FCML_MI( 0x80, 0xF8, 0x42 ) );
    // 3D iw CMP AX, imm16 D Valid Valid Compare imm16 with AX.
    // 3D id CMP EAX, imm32 D Valid Valid Compare imm32 with EAX.
    // REX.W + 3D id CMP RAX, imm32 D Valid N.E. Compare imm32 sign extended to 64-bits with RAX.
    FCML_I32_M( "cmp eax,40302010h", 2, FCML_MI( 0x3D, 0x10, 0x20, 0x30, 0x40 ), FCML_MI( 0x81, 0xf8, 0x10, 0x20, 0x30, 0x40 ) );
    FCML_I32_M( "cmp ax,2010h", 2, FCML_MI( 0x66, 0x3D, 0x10, 0x20 ), FCML_MI( 0x66, 0x81, 0xf8, 0x10, 0x20 ) );
    FCML_I64_M( "cmp rax,0000000040302010h", 2, FCML_MI( 0x48, 0x3D, 0x10, 0x20, 0x30, 0x40 ), FCML_MI( 0x48, 0x81, 0xf8, 0x10, 0x20, 0x30, 0x40 ) );
    // 80 /7 ib CMP r/m8, imm8 C Valid Valid Compare imm8 with r/m8.
    // REX + 80 /7 ib CMP r/m8*, imm8 C Valid N.E. Compare imm8 with r/m8.
    FCML_I32( "cmp byte ptr [eax],20h", 0x80, 0x38, 0x20 );
    FCML_I64_D( "cmp byte ptr [rax],20h", 0x48, 0x80, 0x38, 0x20 );
    // 81 /7 iw CMP r/m16, imm16 C Valid Valid Compare imm16 with r/m16.
    // 81 /7 id CMP r/m32, imm32 C Valid Valid Compare imm32 with r/m32.
    // REX.W + 81 /7 id CMP r/m64, imm32 C Valid N.E. Compare imm32 sign extended to 64-bits with r/m64.
    FCML_I32( "cmp dword ptr [eax],40302010h", 0x81, 0x38, 0x10, 0x20, 0x30, 0x40 );
    FCML_I32( "cmp word ptr [eax],2010h", 0x66, 0x81, 0x38, 0x10, 0x20 );
    FCML_I64( "cmp qword ptr [rax],0000000040302010h", 0x48, 0x81, 0x38, 0x10, 0x20, 0x30, 0x40 );
    // 83 /7 ib CMP r/m16, imm8 C Valid Valid Compare imm8 with r/m16.
    // 83 /7 ib CMP r/m32, imm8 C Valid Valid Compare imm8 with r/m32.
    // REX.W + 83 /7 ib CMP r/m64, imm8 C Valid N.E. Compare imm8 with r/m64.
    FCML_I32_M( "cmp dword ptr [eax],00000010h", 2, FCML_MI( 0x83, 0x38, 0x10 ), FCML_MI( 0x81, 0x38, 0x10, 0x00, 0x00, 0x00 ) );
    FCML_I32_M( "cmp word ptr [eax],0010h", 2, FCML_MI( 0x66, 0x83, 0x38, 0x10 ), FCML_MI( 0x66, 0x81, 0x38, 0x10, 0x00 ) );
    FCML_I64_M( "cmp qword ptr [rax],0000000000000010h", 2, FCML_MI( 0x48, 0x83, 0x38, 0x10 ), FCML_MI( 0x48, 0x81, 0x38, 0x10, 0x00, 0x00, 0x00 ) );
    // 38 /r CMP r/m8, r8 B Valid Valid Compare r8 with r/m8.
    // REX + 38 /r CMP r/m8*, r8* B Valid N.E. Compare r8 with r/m8.
    FCML_I32( "cmp byte ptr [eax],dl", 0x38, 0x10 );
    FCML_I64_D( "cmp byte ptr [rax],dl", 0x48, 0x38, 0x10 );
    // 39 /r CMP r/m16, r16 B Valid Valid Compare r16 with r/m16.
    // 39 /r CMP r/m32, r32 B Valid Valid Compare r32 with r/m32.
    // REX.W + 39 /r CMP r/m64,r64 B Valid N.E. Compare r64 with r/m64.
    FCML_I32( "cmp dword ptr [eax],edx", 0x39, 0x10 );
    FCML_I32( "cmp word ptr [eax],dx", 0x66, 0x39, 0x10 );
    FCML_I64( "cmp qword ptr [rax],rdx", 0x48, 0x39, 0x10 );
    // 3A /r CMP r8, r/m8 A Valid Valid Compare r/m8 with r8.
    // REX + 3A /r CMP r8*, r/m8* A Valid N.E. Compare r/m8 with r8.
    FCML_I32( "cmp dl,byte ptr [eax]", 0x3A, 0x10 );
    FCML_I64_D( "cmp dl,byte ptr [rax]", 0x48, 0x3A, 0x10 );
    // 3B /r CMP r16, r/m16 A Valid Valid Compare r/m16 with r16.
    // 3B /r CMP r32, r/m32 A Valid Valid Compare r/m32 with r32.
    // REX.W + 3B /r CMP r64, r/m64 A Valid N.E. Compare r/m64 with r64.
    FCML_I32( "cmp edx,dword ptr [eax]", 0x3B, 0x10 );
    FCML_I32( "cmp dx,word ptr [eax]", 0x66, 0x3B, 0x10 );
    FCML_I64( "cmp rdx,qword ptr [rax]", 0x48, 0x3B, 0x10 );
}

void fcml_tf_instruction_CMPPD(void) {
    FCML_I32( "cmppd xmm2,oword ptr [ecx+eax],0ffh", 0x66, 0x0F, 0xC2, 0x14, 0x01, 0xFF );
    FCML_I64( "cmppd xmm2,oword ptr [rcx+rax],0ffh", 0x66, 0x0F, 0xC2, 0x14, 0x01, 0xFF );
    // VEX.NDS.128.66.0F C2 /r ib VCMPPD xmm1, xmm2, xmm3/m128, imm8
    // VEX.NDS.256.66.0F C2 /r ib VCMPPD ymm1, ymm2, ymm3/m256, imm8
    FCML_I64( "vcmppd ymm10,ymm14,ymmword ptr [r9+rax],20h", 0xC4, 0x41, 0x0D, 0xC2, 0x14, 0x01, 0x20 );
    FCML_I32( "vcmppd xmm2,xmm7,oword ptr [ecx+eax],20h", 0xc5, 0xC1, 0xC2, 0x14, 0x01, 0x20 );
    FCML_I32_D( "vcmppd xmm2,xmm7,oword ptr [ecx+eax],20h", 0xC4, 0xC1, 0x41, 0xC2, 0x14, 0x01, 0x20 );
    FCML_I32( "vcmppd xmm2,xmm2,oword ptr [ecx+eax],20h", 0xC5, 0xE9, 0xC2, 0x14, 0x01, 0x20 );
    FCML_I32_D( "vcmppd xmm2,xmm2,oword ptr [ecx+eax],20h", 0xC4, 0xC1, 0x69, 0xC2, 0x14, 0x01, 0x20 );
}

void fcml_tf_instruction_CMPPS(void) {
    FCML_I32( "cmpps xmm2,oword ptr [ecx+eax],0ffh", 0x0F, 0xC2, 0x14, 0x01, 0xFF );
    FCML_I64( "cmpps xmm2,oword ptr [rcx+rax],0ffh", 0x0F, 0xC2, 0x14, 0x01, 0xFF );
    // VEX.NDS.128.0F C2 /r ib VCMPPS xmm1, xmm2, xmm3/m128, imm8
    // VEX.NDS.256.0F C2 /r ib VCMPPS ymm1, ymm2, ymm3/m256, imm8
    FCML_I64( "vcmpps ymm10,ymm14,ymmword ptr [r9+rax],20h", 0xC4, 0x41, 0x0C, 0xC2, 0x14, 0x01, 0x20 );
    FCML_I64( "vcmpps xmm2,xmm14,oword ptr [r9+rax],20h", 0xC4, 0xC1, 0x08, 0xC2, 0x14, 0x01, 0x20 );
    FCML_I32( "vcmpps xmm2,xmm2,oword ptr [ecx+eax],20h", 0xC5, 0xE8, 0xC2, 0x14, 0x01, 0x20 );
}

void fcml_tf_instruction_CMPS(void) {
    // TODO: Zastosowac skroty, czyli jezeli wszystko sie zgadza to asz do wyboru albo pokazac mnemonike 1, ze wszsytkii operandami, albo
    // alternatywnie mnemonike skrotu, czyli w taim przypaku jezeli wystepuje mnemoika skrotu to ja nalezy zastosowac jezeli konfiguracja przewiduje krotsza alternatywe.
    // oczywiscie assembler obsluguje obie formy.
    // A6
   /* FCML_I32( "cmps byte ptr [si],byte ptr [di]", 0x67, 0xA6 );
    FCML_I32( "cmps byte ptr [si],byte ptr [di]", 0x66, 0x67, 0xA6 );
    FCML_I32( "cmps byte ptr [esi],byte ptr [edi]", 0xA6 );
    FCML_I64( "cmps byte ptr [rsi],byte ptr [rdi]", 0x48, 0xA6 );
    FCML_I64( "cmps byte ptr [rsi],byte ptr [rdi]", 0x40, 0xA6 );
    FCML_I64( "cmps byte ptr [esi],byte ptr [edi]", 0x67, 0x40, 0xA6 );
    FCML_I64( "cmps byte ptr [esi],byte ptr [edi]", 0x66, 0x67, 0x40, 0xA6 );
    // A7
    FCML_I32( "cmps dword ptr [si],dword ptr [di]", 0x67, 0xA7 );
    FCML_I32( "cmps word ptr [si],word ptr [di]", 0x66, 0x67, 0xA7 );
    FCML_I32( "cmps dword ptr [esi],dword ptr [edi]", 0xA7 );
    FCML_I64( "cmps qword ptr [rsi],qword ptr [rdi]", 0x48, 0xA7 );
    FCML_I64( "cmps dword ptr [rsi],dword ptr [rdi]", 0x40, 0xA7 );
    FCML_I64( "cmps dword ptr [esi],dword ptr [edi]", 0x67, 0x40, 0xA7 );
    FCML_I64( "cmps word ptr [esi],word ptr [edi]", 0x66, 0x67, 0x40, 0xA7 );*/
}

CU_TestInfo fctl_ti_instructions_c[] = {
    { "fcml_tf_instruction_CALL", fcml_tf_instruction_CALL },
    { "fcml_tf_instruction_CBW_CWDE_CDQE", fcml_tf_instruction_CBW_CWDE_CDQE },
    { "fcml_tf_instruction_CLC", fcml_tf_instruction_CLC },
    { "fcml_tf_instruction_CLD", fcml_tf_instruction_CLD },
    { "fcml_tf_instruction_CLFLUSH", fcml_tf_instruction_CLFLUSH },
    { "fcml_tf_instruction_CLI", fcml_tf_instruction_CLI },
    { "fcml_tf_instruction_CLGI", fcml_tf_instruction_CLGI },
    { "fcml_tf_instruction_CLTS", fcml_tf_instruction_CLTS },
    { "fcml_tf_instruction_CMC", fcml_tf_instruction_CMC },
    { "fcml_tf_instruction_CMOV", fcml_tf_instruction_CMOV },
    { "fcml_tf_instruction_CMP", fcml_tf_instruction_CMP },
    { "fcml_tf_instruction_CMPPD", fcml_tf_instruction_CMPPD },
    { "fcml_tf_instruction_CMPPS", fcml_tf_instruction_CMPPS },
    { "fcml_tf_instruction_CMPS", fcml_tf_instruction_CMPS },
    CU_TEST_INFO_NULL,
};

CU_SuiteInfo fctl_si_instructions_c[] = {
    { "suite-fctl_ti_instructions_c", fcml_tf_instructions_c_suite_init, fcml_tf_instructions_c_suite_cleanup, fctl_ti_instructions_c },
    CU_SUITE_INFO_NULL,
};
