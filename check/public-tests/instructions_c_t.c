/*
 * instructions.c
 *
 *  Created on: 01-06-2013
 *      Author: tAs
 */

#include <fcml_assembler.h>
#include <fcml_renderer.h>
#include "instructions_c_t.h"
#include "instructions_base_t.h"

void fcml_tf_instructions_c_suite_init(void) {
}

void fcml_tf_instructions_c_suite_cleanup(void) {
}

void fcml_tf_instruction_CALL(void) {
    /* m16:16,m16:32,m16:64*/
    FCML_I64_FAILED( "FAIL", 0x48, 0x66, 0xFF, 0x57, 0x01 );
    FCML_I32( "call far fword ptr [ebx+00000001h]", 0xFF, 0x5B, 0x01 );
    FCML_I32_RF( "call far fword ptr cs:[ebx+00000001h]", FCML_REND_FLAG_RENDER_DEFAULT_SEG, 0xFF, 0x5B, 0x01 );
    /* Segment register can not be overridden.*/
    FCML_I32_D_RF( "call far fword ptr cs:[ebx+00000001h]", FCML_REND_FLAG_RENDER_DEFAULT_SEG, 0x64, 0xFF, 0x5B, 0x01 );
    FCML_I32( "call far dword ptr [ebx+00000001h]", 0x66, 0xFF, 0x5B, 0x01 );
    FCML_I64_D( "call far tbyte ptr [rbx+0000000000000001h]", 0x66, 0x48, 0xFF, 0x5B, 0x01 ); /* Verified.*/
    FCML_I64_D( "call far dword ptr [rbx+0000000000000001h]", 0x66, 0x40, 0xFF, 0x5B, 0x01 ); /* Verified.*/
    FCML_I64( "call far tbyte ptr [rbx+0000000000000001h]", 0x48, 0xFF, 0x5B, 0x01 ); /* Verified.*/
    FCML_I64( "call far dword ptr [rbx+0000000000000001h]", 0x66, 0xFF, 0x5B, 0x01 ); /* Verified.*/
    FCML_I64( "call far dword ptr [ebx+00000001h]", 0x66, 0x67, 0xFF, 0x5B, 0x01 );
    FCML_I64( "call far fword ptr [rbx+0000000000000001h]", 0xFF, 0x5B, 0x01 );
    FCML_I64_D( "call far fword ptr [rbx+0000000000000001h]", 0x40, 0xFF, 0x5B, 0x01 );
    /* GAS*/
    FCML_A32( "lcall *0x00000001(%ebx)", 0xFF, 0x5B, 0x01 );
    FCML_A32( "lcallw *0x00000001(%ebx)", 0x66, 0xFF, 0x5B, 0x01 );
    FCML_A64( "lcallq *0x0000000000000001(%rbx)", 0x48, 0xFF, 0x5B, 0x01 );
    /* RIP addressing.*/
    FCML_A64( "lcallq *0x00000000(%rip)", 0x48, 0xFF, 0x1d, 0x00,0x00,0x00,0x00 );
    /* prt16:16 ptr16:32*/
    // TODO: Nie dzila liczenie najlpezebo OSA, patrz fcml_ifn_asm_operand_encoder_far_pointer., ddoac
    // mozliwosc wymuszania przykladowo fasm umozliwia taki zapis: "call dword 4433h:00002211h". At7&t juz obsluguje taki zapis
    // lcallw $0x4433,$0x2211.
    FCML_I32( "call far 6655h:44332211h", 0x9A, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66 );
    FCML_I32( "call far 4433h:2211h", 0x66, 0x9A, 0x11, 0x22, 0x33, 0x44 );
    FCML_I16( "call far 4433h:2211h", 0x9A, 0x11, 0x22, 0x33, 0x44 );
    /* GAS*/
    FCML_A32( "lcall $0x6655,$0x44332211", 0x9A, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66 );
	FCML_A32( "lcallw $0x4433,$0x2211", 0x66, 0x9A, 0x11, 0x22, 0x33, 0x44 );
    /* r/m32*/
    FCML_I32_M( "call dword ptr [edi+00000001h]", 2, FCML_MI( 0xFF, 0x57, 0x01 ), FCML_MI( 0x66, 0xff, 0x5f, 0x01 ) );
    FCML_I32_A( "call near dword ptr [edi+00000001h]", 0xFF, 0x57, 0x01 );
	/* r/m16*/
	FCML_I32( "call word ptr [edi+00000001h]", 0x66, 0xFF, 0x57, 0x01 );
	FCML_A32( "callw *0x00000001(%edi)", 0x66, 0xFF, 0x57, 0x01 );
	/* r/m64 (Size directives are the same for operand size 32 and 64 bits.)*/
	FCML_I64_D( "call qword ptr [rdi+0000000000000001h]", 0x66, 0x48, 0xFF, 0x57, 0x01 );
	FCML_I64_D( "call qword ptr [rdi+0000000000000001h]", 0x48, 0xFF, 0x57, 0x01 );
	FCML_I64_D( "call qword ptr [rdi+0000000000000001h]", 0xFF, 0x57, 0x01 );
	/* GAS*/
	/* osa forced to 64 bits for all near branches*/
	FCML_A64( "callq *0x0000000000000001(%rdi)", 0xFF, 0x57, 0x01 );
	FCML_A32( "call *0x00000001(%edi)", 0xFF, 0x57, 0x01 );
	FCML_A32( "callw *0x00000001(%edi)", 0x66, 0xFF, 0x57, 0x01 );
	/* rel16*/
	FCML_I32( "call 00001044h",  0x66, 0xE8, 0x40, 0x00 );
	FCML_A32_M( "callw 0x00001044", 2, FCML_MI( 0x66, 0xe8, 0x40, 0x00 ), FCML_MI( 0x66, 0xff, 0x15, 0x44, 0x10, 0x00, 0x00 ) );
    FCML_I32( "call 00001004h",  0x66, 0xE8, 0x00, 0x00 );
    FCML_I32( "call 00001003h",  0x66, 0xE8, 0xFF, 0xFF );
    FCML_I32( "call 00001084h",  0x66, 0xE8, 0x80, 0x00 );
    FCML_I32( "call 00009004h",  0x66, 0xE8, 0x00, 0x80 );
    FCML_I32( "call 0000809dh",  0x66, 0xE8, 0x99, 0x70 );
    /* rel32*/
    FCML_I32( "call 0ff701005h", 0xE8, 0x00, 0x00, 0x30, 0xFF );
    FCML_A32_M( "call 0xff701005", 2, FCML_MI( 0xe8, 0x00, 0x00, 0x30, 0xff ), FCML_MI( 0xff, 0x15, 0x05, 0x10, 0x70, 0xff ) );
    FCML_I32( "call 00401004h", 0xE8, 0xFF, 0xFF, 0xFF, 0xFF );
    FCML_I32( "call 00401006h", 0xE8, 0x01, 0x00, 0x00, 0x00 );
    FCML_I32( "call 80401005h", 0xE8, 0x00, 0x00, 0x00, 0x80 );
    FCML_I32( "call 79d9a99eh", 0xE8, 0x99, 0x99, 0x99, 0x79 );
    /* rel32 in 64 bits.*/
    FCML_I64_A_FAILED( "call 0000800500401005h", 0xE8, 0x00, 0x00, 0x00, 0x00 );
    FCML_I64( "call 0000800000401004h", 0xE8, 0xFF, 0xFF, 0xFF, 0xFF );
    FCML_I64( "call 00007fff80401005h", 0xE8, 0x00, 0x00, 0x00, 0x80 );
    FCML_A64( "callq 0x00007fff80401005", 0xE8, 0x00, 0x00, 0x00, 0x80 );
    FCML_I64( "call 0000800079d9a99eh", 0xE8, 0x99, 0x99, 0x99, 0x79 );
    /* Segment register are shown only in case of effective addresses.*/
    FCML_I64_RF( "call 0000800079d9a99eh", FCML_REND_FLAG_RENDER_DEFAULT_SEG, 0xE8, 0x99, 0x99, 0x99, 0x79 );
}

void fcml_tf_instruction_CBW_CWDE_CDQE(void) {
    FCML_I32( "cbw", 0x66, 0x98 );
    FCML_I32( "cwde", 0x98 );
    FCML_I64( "cdqe", 0x48, 0x98 );
    FCML_A32( "cbtw", 0x66, 0x98 );
	FCML_A32( "cwtl", 0x98 );
	FCML_A64( "cltq", 0x48, 0x98 );
}

void fcml_tf_instruction_CLC(void) {
    FCML_I32( "clc", 0xf8 );
    FCML_I64( "clc", 0xf8 );
    FCML_A32( "clc", 0xf8 );
    FCML_A64( "clc", 0xf8 );
}

void fcml_tf_instruction_CLD(void) {
    FCML_I3264( "cld", 0xfc );
    FCML_A3264( "cld", 0xfc );
}

void fcml_tf_instruction_CLFLUSH(void) {
    FCML_I32( "clflush byte ptr [esp+edx+00000020h]", 0x0F, 0xAE, 0x7C, 0x14, 0x20 );
    FCML_A32( "clflush 0x00000020(%esp,%edx)", 0x0F, 0xAE, 0x7C, 0x14, 0x20 );
    FCML_I32_D( "clflush byte ptr [esp+edx+00000020h]", 0x66, 0x0F, 0xAE, 0x7C, 0x14, 0x20 );
    FCML_I64( "clflush byte ptr [rsp+rdx+0000000000000020h]", 0x0F, 0xAE, 0x7C, 0x14, 0x20 );
    FCML_A64( "clflush 0x0000000000000020(%rsp,%rdx)", 0x0F, 0xAE, 0x7C, 0x14, 0x20 );
    FCML_I64_D( "clflush byte ptr [rsp+rdx+0000000000000020h]", 0x66, 0x0F, 0xAE, 0x7C, 0x14, 0x20 );
    FCML_I64( "clflush byte ptr [rbp+0000000000000001h]", 0x0F, 0xAE, 0x7D, 0x01 );
}

void fcml_tf_instruction_CLI(void) {
    FCML_I3264( "cli", 0xfa );
    FCML_A3264( "cli", 0xfa );
}

void fcml_tf_instruction_CLGI(void) {
    FCML_I3264( "clgi", 0x0F, 0x01, 0xDD );
    FCML_A3264( "clgi", 0x0F, 0x01, 0xDD );
}

void fcml_tf_instruction_CLTS(void) {
    FCML_I3264( "clts", 0x0f, 0x06 );
    FCML_A3264( "clts", 0x0f, 0x06 );
}

void fcml_tf_instruction_CMC(void) {
    FCML_I3264( "cmc", 0xf5 );
    FCML_A3264( "cmc", 0xf5 );
}

void fcml_tf_instruction_CMOV(void) {
    FCML_I32( "cmovo esp,dword ptr [ebp+04030201h]", 0x0f, 0x40, 0xa5, 0x01, 0x02, 0x03, 04 );
    FCML_A32( "cmovo 0x04030201(%ebp),%esp", 0x0f, 0x40, 0xa5, 0x01, 0x02, 0x03, 04 );
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
    FCML_A32( "cmovnc 0x04030201(%ebp),%esp", 0x0f, 0x43, 0xa5, 0x01, 0x02, 0x03, 04 );
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
    FCML_A32( "cmovnle 0x04030201(%ebp),%esp", 0x0f, 0x4f, 0xa5, 0x01, 0x02, 0x03, 04 );
}

void fcml_tf_instruction_CMP(void) {
    /* 3C ib CMP AL, int8 D Valid Valid Compare int8 with AL.*/
    FCML_I32_M( "cmp al,42h", 2, FCML_MI( 0x3C, 0x42 ), FCML_MI( 0x80, 0xF8, 0x42 ) );
    /* 3D iw CMP AX, int16 D Valid Valid Compare int16 with AX.*/
    /* 3D id CMP EAX, int32 D Valid Valid Compare int32 with EAX.*/
    /* REX.W + 3D id CMP RAX, int32 D Valid N.E. Compare int32 sign extended to 64-bits with RAX.*/
    FCML_I32_M( "cmp eax,40302010h", 2, FCML_MI( 0x3D, 0x10, 0x20, 0x30, 0x40 ), FCML_MI( 0x81, 0xf8, 0x10, 0x20, 0x30, 0x40 ) );
    FCML_I32_M( "cmp ax,2010h", 2, FCML_MI( 0x66, 0x3D, 0x10, 0x20 ), FCML_MI( 0x66, 0x81, 0xf8, 0x10, 0x20 ) );
    FCML_I64_M( "cmp rax,0000000040302010h", 2, FCML_MI( 0x48, 0x3D, 0x10, 0x20, 0x30, 0x40 ), FCML_MI( 0x48, 0x81, 0xf8, 0x10, 0x20, 0x30, 0x40 ) );
    FCML_A64_M( "cmp $0x0000000040302010,%rax", 2, FCML_MI( 0x48, 0x3D, 0x10, 0x20, 0x30, 0x40 ), FCML_MI( 0x48, 0x81, 0xf8, 0x10, 0x20, 0x30, 0x40 ) );
    /* 80 /7 ib CMP r/m8, int8 C Valid Valid Compare int8 with r/m8.*/
    /* REX + 80 /7 ib CMP r/m8*, int8 C Valid N.E. Compare int8 with r/m8.*/
    FCML_I32( "cmp byte ptr [eax],20h", 0x80, 0x38, 0x20 );
    FCML_A32( "cmpb $0x20,(%eax)", 0x80, 0x38, 0x20 );
    FCML_I64_D( "cmp byte ptr [rax],20h", 0x48, 0x80, 0x38, 0x20 );
    /* 81 /7 iw CMP r/m16, int16 C Valid Valid Compare int16 with r/m16.*/
    /* 81 /7 id CMP r/m32, int32 C Valid Valid Compare int32 with r/m32.*/
    /* REX.W + 81 /7 id CMP r/m64, int32 C Valid N.E. Compare int32 sign extended to 64-bits with r/m64.*/
    FCML_I32( "cmp dword ptr [eax],40302010h", 0x81, 0x38, 0x10, 0x20, 0x30, 0x40 );
    FCML_A32( "cmpl $0x40302010,(%eax)", 0x81, 0x38, 0x10, 0x20, 0x30, 0x40 );
    FCML_I32( "cmp word ptr [eax],2010h", 0x66, 0x81, 0x38, 0x10, 0x20 );
    FCML_A32( "cmpw $0x2010,(%eax)", 0x66, 0x81, 0x38, 0x10, 0x20 );
    FCML_I64( "cmp qword ptr [rax],0000000040302010h", 0x48, 0x81, 0x38, 0x10, 0x20, 0x30, 0x40 );
    /* 83 /7 ib CMP r/m16, int8 C Valid Valid Compare int8 with r/m16.*/
    /* 83 /7 ib CMP r/m32, int8 C Valid Valid Compare int8 with r/m32.*/
    /* REX.W + 83 /7 ib CMP r/m64, int8 C Valid N.E. Compare int8 with r/m64.*/
    FCML_I32_M( "cmp dword ptr [eax],00000010h", 2, FCML_MI( 0x83, 0x38, 0x10 ), FCML_MI( 0x81, 0x38, 0x10, 0x00, 0x00, 0x00 ) );
    FCML_I32_M( "cmp word ptr [eax],0010h", 2, FCML_MI( 0x66, 0x83, 0x38, 0x10 ), FCML_MI( 0x66, 0x81, 0x38, 0x10, 0x00 ) );
    FCML_I64_M( "cmp qword ptr [rax],0000000000000010h", 2, FCML_MI( 0x48, 0x83, 0x38, 0x10 ), FCML_MI( 0x48, 0x81, 0x38, 0x10, 0x00, 0x00, 0x00 ) );
    FCML_A64_M( "cmpq $0x0000000000000010,(%rax)", 2, FCML_MI( 0x48, 0x83, 0x38, 0x10 ), FCML_MI( 0x48, 0x81, 0x38, 0x10, 0x00, 0x00, 0x00 ) );
    /* 38 /r CMP r/m8, r8 B Valid Valid Compare r8 with r/m8.*/
    /* REX + 38 /r CMP r/m8*, r8* B Valid N.E. Compare r8 with r/m8.*/
    FCML_I32( "cmp byte ptr [eax],dl", 0x38, 0x10 );
    FCML_I64_D( "cmp byte ptr [rax],dl", 0x48, 0x38, 0x10 );
    /* 39 /r CMP r/m16, r16 B Valid Valid Compare r16 with r/m16.*/
    /* 39 /r CMP r/m32, r32 B Valid Valid Compare r32 with r/m32.*/
    /* REX.W + 39 /r CMP r/m64,r64 B Valid N.E. Compare r64 with r/m64.*/
    FCML_I32( "cmp dword ptr [eax],edx", 0x39, 0x10 );
    FCML_I32( "cmp word ptr [eax],dx", 0x66, 0x39, 0x10 );
    FCML_I64( "cmp qword ptr [rax],rdx", 0x48, 0x39, 0x10 );
    /* 3A /r CMP r8, r/m8 A Valid Valid Compare r/m8 with r8.*/
    /* REX + 3A /r CMP r8*, r/m8* A Valid N.E. Compare r/m8 with r8.*/
    FCML_I32( "cmp dl,byte ptr [eax]", 0x3A, 0x10 );
    FCML_I64_D( "cmp dl,byte ptr [rax]", 0x48, 0x3A, 0x10 );
    /* 3B /r CMP r16, r/m16 A Valid Valid Compare r/m16 with r16.*/
    /* 3B /r CMP r32, r/m32 A Valid Valid Compare r/m32 with r32.*/
    /* REX.W + 3B /r CMP r64, r/m64 A Valid N.E. Compare r/m64 with r64.*/
    FCML_I32( "cmp edx,dword ptr [eax]", 0x3B, 0x10 );
    FCML_I32( "cmp dx,word ptr [eax]", 0x66, 0x3B, 0x10 );
    FCML_I64( "cmp rdx,qword ptr [rax]", 0x48, 0x3B, 0x10 );
    FCML_A64( "cmp (%rax),%rdx", 0x48, 0x3B, 0x10 );
}

void fcml_tf_instruction_CMPPD(void) {
    FCML_I32( "cmppd xmm2,xmmword ptr [ecx+eax],0ffh", 0x66, 0x0F, 0xC2, 0x14, 0x01, 0xFF );
    FCML_I64( "cmppd xmm2,xmmword ptr [rcx+rax],0ffh", 0x66, 0x0F, 0xC2, 0x14, 0x01, 0xFF );
    FCML_A64( "cmppd $0xff,(%rcx,%rax),%xmm2", 0x66, 0x0F, 0xC2, 0x14, 0x01, 0xFF );
    /* VEX.NDS.128.66.0F C2 /r ib VCMPPD xmm1, xmm2, xmm3/m128, int8*/
    /* VEX.NDS.256.66.0F C2 /r ib VCMPPD ymm1, ymm2, ymm3/m256, int8*/
    FCML_I64( "vcmppd ymm10,ymm14,ymmword ptr [r9+rax],20h", 0xC4, 0x41, 0x0D, 0xC2, 0x14, 0x01, 0x20 );
    FCML_A64( "vcmppd $0x20,(%r9,%rax),%ymm14,%ymm10", 0xC4, 0x41, 0x0D, 0xC2, 0x14, 0x01, 0x20 );
    FCML_I32( "vcmppd xmm2,xmm7,xmmword ptr [ecx+eax],20h", 0xc5, 0xC1, 0xC2, 0x14, 0x01, 0x20 );
    FCML_I32_D( "vcmppd xmm2,xmm7,xmmword ptr [ecx+eax],20h", 0xC4, 0xC1, 0x41, 0xC2, 0x14, 0x01, 0x20 );
    FCML_I32( "vcmppd xmm2,xmm2,xmmword ptr [ecx+eax],20h", 0xC5, 0xE9, 0xC2, 0x14, 0x01, 0x20 );
    FCML_I32_D( "vcmppd xmm2,xmm2,xmmword ptr [ecx+eax],20h", 0xC4, 0xC1, 0x69, 0xC2, 0x14, 0x01, 0x20 );
}

void fcml_tf_instruction_CMPPS(void) {
    FCML_I32( "cmpps xmm2,xmmword ptr [ecx+eax],0ffh", 0x0F, 0xC2, 0x14, 0x01, 0xFF );
    FCML_I64( "cmpps xmm2,xmmword ptr [rcx+rax],0ffh", 0x0F, 0xC2, 0x14, 0x01, 0xFF );
    FCML_A64( "cmpps $0xff,(%rcx,%rax),%xmm2", 0x0F, 0xC2, 0x14, 0x01, 0xFF );
    /* VEX.NDS.128.0F C2 /r ib VCMPPS xmm1, xmm2, xmm3/m128, int8*/
    /* VEX.NDS.256.0F C2 /r ib VCMPPS ymm1, ymm2, ymm3/m256, int8*/
    FCML_I64( "vcmpps ymm10,ymm14,ymmword ptr [r9+rax],20h", 0xC4, 0x41, 0x0C, 0xC2, 0x14, 0x01, 0x20 );
    FCML_I64( "vcmpps xmm2,xmm14,xmmword ptr [r9+rax],20h", 0xC4, 0xC1, 0x08, 0xC2, 0x14, 0x01, 0x20 );
    FCML_A64( "vcmpps $0x20,(%r9,%rax),%xmm14,%xmm2", 0xC4, 0xC1, 0x08, 0xC2, 0x14, 0x01, 0x20 );
    FCML_I32( "vcmpps xmm2,xmm2,xmmword ptr [ecx+eax],20h", 0xC5, 0xE8, 0xC2, 0x14, 0x01, 0x20 );
}

void fcml_tf_instruction_CMPS(void) {
    /* A6*/
    FCML_I32( "repne cmps byte ptr [si],byte ptr [di]", 0xF2, 0x67, 0xA6 );
    FCML_I32( "cmps byte ptr [si],byte ptr [di]", 0x66, 0x67, 0xA6 );
    FCML_I32( "cmps byte ptr [esi],byte ptr [edi]", 0xA6 );
    FCML_I64_D( "cmps byte ptr [rsi],byte ptr [rdi]", 0x48, 0xA6 );
    FCML_I64( "cmps byte ptr [rsi],byte ptr [rdi]", 0xA6 );
    FCML_A64( "cmpsb (%rdi),(%rsi)", 0xA6 );
    FCML_A64_D_SHORT( "cmpsb", 0xA6 );
    FCML_I64_D( "cmps byte ptr [rsi],byte ptr [rdi]", 0x40, 0xA6 );
    FCML_I64( "cmps byte ptr [rsi],byte ptr [rdi]", 0xA6 );
    FCML_I64_D( "cmps byte ptr [esi],byte ptr [edi]", 0x67, 0x40, 0xA6 );
    FCML_I64( "cmps byte ptr [esi],byte ptr [edi]", 0x67, 0xA6 );
    FCML_I64_D( "cmps byte ptr [esi],byte ptr [edi]", 0x66, 0x67, 0x40, 0xA6 );
    FCML_I64( "cmps byte ptr [esi],byte ptr [edi]", 0x66, 0x67, 0xA6 );
    /* A7*/
    FCML_I32( "cmps dword ptr [si],dword ptr [di]", 0x67, 0xA7 );
    FCML_I64_A_FAILED( "cmps dword ptr [si],dword ptr [di]", 0x67, 0xA7 );
    FCML_I32( "cmps word ptr [si],word ptr [di]", 0x66, 0x67, 0xA7 );
    FCML_A32( "cmpsw (%di),(%si)", 0x66, 0x67, 0xA7 );
    FCML_A32_D_SHORT( "cmpsw", 0x66, 0x67, 0xA7 );
    FCML_I32( "cmps dword ptr [esi],dword ptr [edi]", 0xA7 );
    FCML_A32( "cmpsl (%edi),(%esi)", 0xA7 );
    FCML_A32_D_SHORT( "cmpsl", 0xA7 );
    FCML_I64( "cmps qword ptr [rsi],qword ptr [rdi]", 0x48, 0xA7 );
    FCML_I64_D( "cmps dword ptr [rsi],dword ptr [rdi]", 0x40, 0xA7 );
    FCML_I64( "cmps dword ptr [rsi],dword ptr [rdi]", 0xA7 );
    FCML_A64( "cmpsq (%rdi),(%rsi)", 0x48, 0xA7 );
    FCML_A64_D_SHORT( "cmpsq", 0x48, 0xA7 );
    FCML_I64_D( "cmps dword ptr [esi],dword ptr [edi]", 0x67, 0x40, 0xA7 );
    FCML_I64( "cmps dword ptr [esi],dword ptr [edi]", 0x67, 0xA7 );
    FCML_I64_D( "cmps word ptr [esi],word ptr [edi]", 0x66, 0x67, 0x40, 0xA7 );
    FCML_I64( "cmps word ptr [esi],word ptr [edi]", 0x66, 0x67, 0xA7 );
    /* Segment override.*/
    /* ES cannot be overridden.*/
    FCML_I32_A_FAILED( "cmps dword ptr ds:[si],dword ptr cs:[di]", 0x67, 0xA7 );
    FCML_I32_A_FAILED( "cmps dword ptr ds:[si],dword ptr ds:[di]", 0x67, 0xA7 );
    FCML_I32_A( "cmps dword ptr ds:[si],dword ptr es:[di]", 0x67, 0xA7 );
    /* DS can be.*/
    FCML_I32_A( "repne cmps dword ptr cs:[si],dword ptr es:[di]", 0xF2, 0x2E, 0x67, 0xA7 );
    FCML_I32_A( "cmps dword ptr ss:[si],dword ptr es:[di]", 0x36, 0x67, 0xA7 );
    FCML_I32_A( "cmps dword ptr es:[si],dword ptr es:[di]", 0x26, 0x67, 0xA7 );
    FCML_I32_A( "cmps dword ptr fs:[si],dword ptr es:[di]", 0x64, 0x67, 0xA7 );
    FCML_I32_A( "cmps dword ptr gs:[si],dword ptr es:[di]", 0x65, 0x67, 0xA7 );
    /* Short forms.*/
    FCML_A64_A( "cmpsb", 0xA6 );
	FCML_A32_A( "cmpsw", 0x66, 0xA7 );
	FCML_A32_A( "cmpsl", 0xA7 );
	FCML_A64_A( "cmpsq", 0x48, 0xA7 );
    FCML_I32_D_SHORT( "repne cmpsb", 0xF2, 0xA6 );
    FCML_I32_D_SHORT( "cmpsw", 0x66, 0xA7 );
    FCML_I32_D_SHORT( "cmpsd", 0xA7 );
    FCML_I64_D_SHORT( "cmpsq", 0x48, 0xA7 );
    FCML_I32_A( "cmpsb", 0xA6 );
    FCML_I32_A( "cmpsw", 0x66, 0xA7 );
    FCML_I32_A( "cmpsd", 0xA7 );
    FCML_I64_A( "cmpsq", 0x48, 0xA7 );
}

void fcml_tf_instruction_CMPSD(void) {
    /* Wrong comparison predicate.*/
    FCML_I32_A_FAILED( "cmpsd xmm0,mmword ptr [eax+00000020h],08h", 0xF2, 0x0F, 0xC2, 0x40, 0x20, 0x08 );
    FCML_I32( "cmpsd xmm0,mmword ptr [eax+00000020h],07h", 0xF2, 0x0F, 0xC2, 0x40, 0x20, 0x07 );
    FCML_A32( "cmpsd $0x07,0x00000020(%eax),%xmm0", 0xF2, 0x0F, 0xC2, 0x40, 0x20, 0x07 );
    FCML_I64( "cmpsd xmm0,mmword ptr [rax+0000000000000020h],06h", 0xF2, 0x0F, 0xC2, 0x40, 0x20, 0x06 );
    FCML_A32( "cmpsd $0x06,0x00000020(%eax),%xmm0", 0xf2, 0x0f, 0xc2, 0x40, 0x20, 0x06 );
    FCML_I32( "cmpsd xmm0,xmm1,00h", 0xf2, 0x0f, 0xc2, 0xc1, 0x00 );
    FCML_A32( "cmpsd $0x00,%xmm1,%xmm0", 0xf2, 0x0f, 0xc2, 0xc1, 0x00 );
    /* pseudo op.*/
    FCML_I3264_A( "cmpeqsd xmm0,xmm1", 0xf2, 0x0f, 0xc2, 0xc1, 0x00 );
    FCML_A32_D_SHORT( "cmpeqsd (%eax),%xmm0", 0xf2, 0x0f, 0xc2, 0x00, 0x00 );
    FCML_A3264_A( "cmpeqsd %xmm1,%xmm0", 0xf2, 0x0f, 0xc2, 0xc1, 0x00 );
    FCML_I3264_A( "cmpltsd xmm0,xmm1", 0xf2, 0x0f, 0xc2, 0xc1, 0x01 );
    FCML_I3264_A( "cmplesd xmm0,xmm1", 0xf2, 0x0f, 0xc2, 0xc1, 0x02 );
    FCML_I3264_A( "cmpunordsd xmm0,xmm1", 0xf2, 0x0f, 0xc2, 0xc1, 0x03 );
    FCML_A3264_A( "cmpunordsd %xmm1,%xmm0", 0xf2, 0x0f, 0xc2, 0xc1, 0x03 );
    FCML_A32_A( "cmpunordsd (%ecx),%xmm0", 0xf2, 0x0f, 0xc2, 0x01, 0x03 );
    FCML_A32_D_SHORT( "cmpunordsd (%ecx),%xmm0", 0xf2, 0x0f, 0xc2, 0x01, 0x03 );
    FCML_I3264_A( "cmpneqsd xmm0,xmm1", 0xf2, 0x0f, 0xc2, 0xc1, 0x04 );
    FCML_I3264_A( "cmpnltsd xmm0,xmm1", 0xf2, 0x0f, 0xc2, 0xc1, 0x05 );
    FCML_I3264_A( "cmpnlesd xmm0,xmm1", 0xf2, 0x0f, 0xc2, 0xc1, 0x06 );
    FCML_I3264_A( "cmpordsd xmm0,xmm1", 0xf2, 0x0f, 0xc2, 0xc1, 0x07 );
    /* Disassembling. */
    FCML_I32_D_SHORT( "cmpeqsd xmm0,xmm1", 0xf2, 0x0f, 0xc2, 0xc1, 0x00 );
    /* VEX.NDS.128.F2.0F C2 /r ib VCMPSD xmm1, xmm2, xmm3/m64, int8*/
    FCML_I32_A_FAILED( "vcmpsd xmm2,xmm7,mmword ptr [ecx+eax],20h", 0xc5, 0xc3, 0xc2, 0x14, 0x01, 0x20 );
    FCML_I32( "vcmpsd xmm2,xmm7,mmword ptr [ecx+eax],0fh", 0xc5, 0xc3, 0xc2, 0x14, 0x01, 0x0F );
    FCML_I64( "vcmpsd xmm10,xmm14,mmword ptr [r9+rax],00h", 0xC4, 0x41, 0x0B, 0xC2, 0x14, 0x01, 0x00 );
    /* pseudo op.*/
    FCML_I3264_A( "vcmpeqsd xmm0,xmm1,xmm2", 0xc5, 0xf3, 0xc2, 0xc2, 0x00 );
    FCML_I3264_A( "vcmpltsd xmm0,xmm1,xmm2", 0xc5, 0xf3, 0xc2, 0xc2, 0x01 );
    FCML_I3264_A( "vcmplesd xmm0,xmm1,xmm2", 0xc5, 0xf3, 0xc2, 0xc2, 0x02 );
    FCML_I3264_A( "vcmpunordsd xmm0,xmm1,xmm2", 0xc5, 0xf3, 0xc2, 0xc2, 0x03 );
    FCML_I3264_A( "vcmpneqsd xmm0,xmm1,xmm2", 0xc5, 0xf3, 0xc2, 0xc2, 0x04 );
    FCML_I3264_A( "vcmpnltsd xmm0,xmm1,xmm2", 0xc5, 0xf3, 0xc2, 0xc2, 0x05 );
    FCML_I3264_A( "vcmpnlesd xmm0,xmm1,xmm2", 0xc5, 0xf3, 0xc2, 0xc2, 0x06 );
    FCML_I3264_A( "vcmpordsd xmm0,xmm1,xmm2", 0xc5, 0xf3, 0xc2, 0xc2, 0x07 );
    FCML_I3264_A( "vcmpeq_uqsd xmm0,xmm1,xmm2", 0xc5, 0xf3, 0xc2, 0xc2, 0x08 );
    FCML_I3264_A( "vcmpngesd xmm0,xmm1,xmm2", 0xc5, 0xf3, 0xc2, 0xc2, 0x09 );
    FCML_I3264_A( "vcmpngtsd xmm0,xmm1,xmm2", 0xc5, 0xf3, 0xc2, 0xc2, 0x0A );
    FCML_I3264_A( "vcmpfalsesd xmm0,xmm1,xmm2", 0xc5, 0xf3, 0xc2, 0xc2, 0x0B );
    FCML_I3264_A( "vcmpneq_oqsd xmm0,xmm1,xmm2", 0xc5, 0xf3, 0xc2, 0xc2, 0x0C );
    FCML_I3264_A( "vcmpgesd xmm0,xmm1,xmm2", 0xc5, 0xf3, 0xc2, 0xc2, 0x0D );
    FCML_I3264_A( "vcmpgtsd xmm0,xmm1,xmm2", 0xc5, 0xf3, 0xc2, 0xc2, 0x0E );
    FCML_I3264_A( "vcmptruesd xmm0,xmm1,xmm2", 0xc5, 0xf3, 0xc2, 0xc2, 0x0F );
    FCML_I3264_A( "vcmpeq_ossd xmm0,xmm1,xmm2", 0xc5, 0xf3, 0xc2, 0xc2, 0x10 );
    FCML_I3264_A( "vcmplt_oqsd xmm0,xmm1,xmm2", 0xc5, 0xf3, 0xc2, 0xc2, 0x11 );
    FCML_I3264_A( "vcmple_oqsd xmm0,xmm1,xmm2", 0xc5, 0xf3, 0xc2, 0xc2, 0x12 );
    FCML_I3264_A( "vcmpunord_ssd xmm0,xmm1,xmm2", 0xc5, 0xf3, 0xc2, 0xc2, 0x13 );
    FCML_I3264_A( "vcmpneq_ussd xmm0,xmm1,xmm2", 0xc5, 0xf3, 0xc2, 0xc2, 0x14 );
    FCML_I3264_A( "vcmpnlt_uqsd xmm0,xmm1,xmm2", 0xc5, 0xf3, 0xc2, 0xc2, 0x15 );
    FCML_I3264_A( "vcmpnle_uqsd xmm0,xmm1,xmm2", 0xc5, 0xf3, 0xc2, 0xc2, 0x16 );
    FCML_I3264_A( "vcmpord_ssd xmm0,xmm1,xmm2", 0xc5, 0xf3, 0xc2, 0xc2, 0x17 );
    FCML_I3264_A( "vcmpeq_ussd xmm0,xmm1,xmm2", 0xc5, 0xf3, 0xc2, 0xc2, 0x18 );
    FCML_I3264_A( "vcmpnge_uqsd xmm0,xmm1,xmm2", 0xc5, 0xf3, 0xc2, 0xc2, 0x19 );
    FCML_I3264_A( "vcmpngt_uqsd xmm0,xmm1,xmm2", 0xc5, 0xf3, 0xc2, 0xc2, 0x1A );
    FCML_I3264_A( "vcmpfalse_ossd xmm0,xmm1,xmm2", 0xc5, 0xf3, 0xc2, 0xc2, 0x1B );
    FCML_I3264_A( "vcmpneq_ossd xmm0,xmm1,xmm2", 0xc5, 0xf3, 0xc2, 0xc2, 0x1C );
    FCML_I3264_A( "vcmpge_oqsd xmm0,xmm1,xmm2", 0xc5, 0xf3, 0xc2, 0xc2, 0x1D );
    FCML_I3264_A( "vcmpgt_oqsd xmm0,xmm1,xmm2", 0xc5, 0xf3, 0xc2, 0xc2, 0x1E );
    FCML_I3264_A( "vcmptrue_ussd xmm0,xmm1,xmm2", 0xc5, 0xf3, 0xc2, 0xc2, 0x1F );
    FCML_I3264_A_FAILED( "vcmptrue_ussd xmm0,xmm1,xmm2,01fh", 0xc5, 0xf3, 0xc2, 0xc2, 0x1F );
    /*gus*/
    FCML_A32_A( "vcmpord_ssd 0x14(%ecx),%xmm1,%xmm0", 0xc5, 0xf3, 0xc2, 0x41, 0x14, 0x17 );
    FCML_I32( "vcmpsd xmm2,xmm7,mmword ptr [ecx+eax],0fh", 0xc5, 0xc3, 0xc2, 0x14, 0x01, 0x0F );
    FCML_A32( "vcmpsd $0x0f,(%ecx,%eax),%xmm7,%xmm2", 0xc5, 0xc3, 0xc2, 0x14, 0x01, 0x0F );
}

void fcml_tf_instruction_CMPSS(void) {
    /* Wrong comparison predicate.*/
    FCML_I32_A_FAILED( "cmpss xmm0,dword ptr [eax+00000020h],08h", 0xf3, 0x0f, 0xc2, 0x40, 0x20, 0x08 );
    FCML_I32( "cmpss xmm0,dword ptr [eax+00000020h],07h", 0xf3, 0x0f, 0xc2, 0x40, 0x20, 0x07 );
    FCML_I64( "cmpss xmm0,dword ptr [rax+0000000000000020h],06h", 0xf3, 0x0f, 0xc2, 0x40, 0x20, 0x06 );
    /*FCML_I64( "cmpnless 0x20(%rax),%xmm0", 0xf3, 0x0f, 0xc2, 0x40, 0x20, 0x06 );*/
    FCML_A64( "cmpss $0x06,0x0000000000000020(%rax),%xmm0", 0xf3, 0x0f, 0xc2, 0x40, 0x20, 0x06 );
    /* pseudo op.*/
    FCML_I3264_A( "cmpeqss xmm0,xmm1", 0xf3, 0x0f, 0xc2, 0xc1, 0x00 );
    FCML_I3264_A( "cmpltss xmm0,xmm1", 0xf3, 0x0f, 0xc2, 0xc1, 0x01 );
    FCML_I3264_A( "cmpless xmm0,xmm1", 0xf3, 0x0f, 0xc2, 0xc1, 0x02 );
    FCML_I3264_A( "cmpunordss xmm0,xmm1", 0xf3, 0x0f, 0xc2, 0xc1, 0x03 );
    FCML_A3264_A( "cmpunordss %xmm1,%xmm0", 0xf3, 0x0f, 0xc2, 0xc1, 0x03 );
    FCML_I3264_A( "cmpneqss xmm0,xmm1", 0xf3, 0x0f, 0xc2, 0xc1, 0x04 );
    FCML_I3264_A( "cmpnltss xmm0,xmm1", 0xf3, 0x0f, 0xc2, 0xc1, 0x05 );
    FCML_I3264_A( "cmpnless xmm0,xmm1", 0xf3, 0x0f, 0xc2, 0xc1, 0x06 );
    FCML_I3264_A( "cmpordss xmm0,xmm1", 0xf3, 0x0f, 0xc2, 0xc1, 0x07 );
    /* pseudo opcode out of range.*/
    FCML_I32_A_FAILED( "vcmpss xmm2,xmm7,dword ptr [ecx+eax],20h", 0xc5, 0xc2, 0xc2, 0x14, 0x01, 0x20 );
    FCML_I32( "vcmpss xmm2,xmm7,dword ptr [ecx+eax],0fh", 0xc5, 0xc2, 0xc2, 0x14, 0x01, 0x0F );
    FCML_I64( "vcmpss xmm10,xmm14,dword ptr [r9+rax],00h", 0xC4, 0x41, 0x0A, 0xC2, 0x14, 0x01, 0x00 );
    /* pseudo op.*/
    FCML_I3264_A( "vcmpeqss xmm0,xmm1,xmm2", 0xc5, 0xf2, 0xc2, 0xc2, 0x00 );
    FCML_I3264_A( "vcmpltss xmm0,xmm1,xmm2", 0xc5, 0xf2, 0xc2, 0xc2, 0x01 );
    FCML_I3264_A( "vcmpless xmm0,xmm1,xmm2", 0xc5, 0xf2, 0xc2, 0xc2, 0x02 );
    FCML_I3264_A( "vcmpunordss xmm0,xmm1,xmm2", 0xc5, 0xf2, 0xc2, 0xc2, 0x03 );
    FCML_I3264_A( "vcmpneqss xmm0,xmm1,xmm2", 0xc5, 0xf2, 0xc2, 0xc2, 0x04 );
    FCML_I3264_A( "vcmpnltss xmm0,xmm1,xmm2", 0xc5, 0xf2, 0xc2, 0xc2, 0x05 );
    FCML_I3264_A( "vcmpnless xmm0,xmm1,xmm2", 0xc5, 0xf2, 0xc2, 0xc2, 0x06 );
    FCML_I3264_A( "vcmpordss xmm0,xmm1,xmm2", 0xc5, 0xf2, 0xc2, 0xc2, 0x07 );
    FCML_I3264_A( "vcmpeq_uqss xmm0,xmm1,xmm2", 0xc5, 0xf2, 0xc2, 0xc2, 0x08 );
    FCML_I3264_A( "vcmpngess xmm0,xmm1,xmm2", 0xc5, 0xf2, 0xc2, 0xc2, 0x09 );
    FCML_I3264_A( "vcmpngtss xmm0,xmm1,xmm2", 0xc5, 0xf2, 0xc2, 0xc2, 0x0A );
    FCML_I3264_A( "vcmpfalsess xmm0,xmm1,xmm2", 0xc5, 0xf2, 0xc2, 0xc2, 0x0B );
    FCML_I3264_A( "vcmpneq_oqss xmm0,xmm1,xmm2", 0xc5, 0xf2, 0xc2, 0xc2, 0x0C );
    FCML_I3264_A( "vcmpgess xmm0,xmm1,xmm2", 0xc5, 0xf2, 0xc2, 0xc2, 0x0D );
    FCML_I3264_A( "vcmpgtss xmm0,xmm1,xmm2", 0xc5, 0xf2, 0xc2, 0xc2, 0x0E );
    FCML_I3264_A( "vcmptruess xmm0,xmm1,xmm2", 0xc5, 0xf2, 0xc2, 0xc2, 0x0F );
    FCML_I3264_A( "vcmpeq_osss xmm0,xmm1,xmm2", 0xc5, 0xf2, 0xc2, 0xc2, 0x10 );
    FCML_I3264_A( "vcmplt_oqss xmm0,xmm1,xmm2", 0xc5, 0xf2, 0xc2, 0xc2, 0x11 );
    FCML_I3264_A( "vcmple_oqss xmm0,xmm1,xmm2", 0xc5, 0xf2, 0xc2, 0xc2, 0x12 );
    FCML_I3264_A( "vcmpunord_sss xmm0,xmm1,xmm2", 0xc5, 0xf2, 0xc2, 0xc2, 0x13 );
    FCML_I3264_A( "vcmpneq_usss xmm0,xmm1,xmm2", 0xc5, 0xf2, 0xc2, 0xc2, 0x14 );
    FCML_I3264_A( "vcmpnlt_uqss xmm0,xmm1,xmm2", 0xc5, 0xf2, 0xc2, 0xc2, 0x15 );
    FCML_I3264_A( "vcmpnle_uqss xmm0,xmm1,xmm2", 0xc5, 0xf2, 0xc2, 0xc2, 0x16 );
    FCML_I3264_A( "vcmpord_sss xmm0,xmm1,xmm2", 0xc5, 0xf2, 0xc2, 0xc2, 0x17 );
    FCML_I3264_A( "vcmpeq_usss xmm0,xmm1,xmm2", 0xc5, 0xf2, 0xc2, 0xc2, 0x18 );
    FCML_I3264_A( "vcmpnge_uqss xmm0,xmm1,xmm2", 0xc5, 0xf2, 0xc2, 0xc2, 0x19 );
    FCML_I3264_A( "vcmpngt_uqss xmm0,xmm1,xmm2", 0xc5, 0xf2, 0xc2, 0xc2, 0x1A );
    FCML_I3264_A( "vcmpfalse_osss xmm0,xmm1,xmm2", 0xc5, 0xf2, 0xc2, 0xc2, 0x1B );
    FCML_I3264_A( "vcmpneq_osss xmm0,xmm1,xmm2", 0xc5, 0xf2, 0xc2, 0xc2, 0x1C );
    FCML_I3264_A( "vcmpge_oqss xmm0,xmm1,xmm2", 0xc5, 0xf2, 0xc2, 0xc2, 0x1D );
    FCML_I3264_A( "vcmpgt_oqss xmm0,xmm1,xmm2", 0xc5, 0xf2, 0xc2, 0xc2, 0x1E );
    FCML_I3264_A( "vcmptrue_usss xmm0,xmm1,xmm2", 0xc5, 0xf2, 0xc2, 0xc2, 0x1F );
    FCML_I3264_A_FAILED( "vcmptrue_usss xmm0,xmm1,xmm2,01fh", 0xc5, 0xf2, 0xc2, 0xc2, 0x1F );
}

void fcml_tf_instruction_CMPXCHG(void) {
    /* 0F B0 /r CMPXCHG r/m8, r8*/
    /* REX + 0F B0/r CMPXCHG r/m8,r8*/
    FCML_I32( "lock cmpxchg byte ptr [eax],dl", 0xF0, 0x0F, 0xB0, 0x10 );
    FCML_A32( "lock cmpxchg %dl,(%eax)", 0xF0, 0x0F, 0xB0, 0x10 );
    FCML_I32( "xacquire lock cmpxchg byte ptr [eax],dl", 0xF2, 0xF0, 0x0F, 0xB0, 0x10 );
    FCML_I32( "xrelease lock cmpxchg byte ptr [eax],dl", 0xF3, 0xF0, 0x0F, 0xB0, 0x10 );
    FCML_A32( "xrelease lock cmpxchg %dl,(%eax)", 0xF3, 0xF0, 0x0F, 0xB0, 0x10 );
    FCML_I64( "cmpxchg byte ptr [rax],dl", 0x0F, 0xB0, 0x10 );
    FCML_A64( "cmpxchg %dl,(%rax)", 0x0F, 0xB0, 0x10 );
    FCML_I64_D( "cmpxchg byte ptr [rax],dl", 0x48,  0x0F, 0xB0, 0x10 );
    /* 0F B1/r CMPXCHG r/m16, r16*/
    /* 0F B1/r CMPXCHG r/m32, r32*/
    /* REX.W + 0F B1/r CMPXCHG r/m64, r64*/
    FCML_I32( "cmpxchg dword ptr [eax],edx", 0x0F, 0xB1, 0x10 );
    FCML_A32( "cmpxchg %edx,(%eax)", 0x0F, 0xB1, 0x10 );
    FCML_I32( "cmpxchg word ptr [eax],dx", 0x66, 0x0F, 0xB1, 0x10 );
    FCML_I64( "lock cmpxchg qword ptr [rax],rdx", 0xF0, 0x48,  0x0F, 0xB1, 0x10 );
    FCML_I64( "xacquire lock cmpxchg qword ptr [rax],rdx", 0xF2, 0xF0, 0x48,  0x0F, 0xB1, 0x10 );
    FCML_I64( "xrelease lock cmpxchg qword ptr [rax],rdx", 0xF3, 0xF0, 0x48,  0x0F, 0xB1, 0x10 );
    FCML_A64( "xrelease lock cmpxchg %rdx,(%rax)", 0xF3, 0xF0, 0x48,  0x0F, 0xB1, 0x10 );
}

void fcml_tf_instruction_CMPXCHG16B_CMPXCHG8B(void) {
    /* REX.W + 0F C7 /1 m128 CMPXCHG16B m128 A Valid N.E. Compare RDX:RAX with m128. If equal, set ZF and load RCX:RBX into m128. Else, clear ZF and load m128 into RDX:RAX.*/
    FCML_I64( "cmpxchg16b oword ptr [rcx+0ffffffffffffffffh]", 0x48, 0x0F, 0xC7, 0x49, 0xFF );
    FCML_A64( "cmpxchg16b 0xffffffffffffffff(%rcx)", 0x48, 0x0F, 0xC7, 0x49, 0xFF );
    FCML_I64( "lock cmpxchg16b oword ptr [rcx+0ffffffffffffffffh]", 0xF0, 0x48, 0x0F, 0xC7, 0x49, 0xFF );
    FCML_I64_D_FAILED( "xacquire lock cmpxchg16b oword ptr [rcx+0ffffffffffffffffh]", 0xF2, 0xF0, 0x48, 0x0F, 0xC7, 0x49, 0xFF );
    FCML_I64_D_FAILED( "xrelease lock cmpxchg16b oword ptr [rcx+0ffffffffffffffffh]", 0xF3, 0xF0, 0x48, 0x0F, 0xC7, 0x49, 0xFF );
    FCML_A64_A_FAILED( "xrelease lock cmpxchg16b 0xffffffffffffffff(%rcx)", 0xF3, 0xF0, 0x48, 0x0F, 0xC7, 0x49, 0xFF );
    /* 0F C7 /1 m64 CMPXCHG8B m64 A Valid Valid* Compare EDX:EAX with m64. If equal, set ZF and load ECX:EBX into m64. Else, clear ZF and load m64 into EDX:EAX.*/
    FCML_I64( "cmpxchg8b qword ptr [rcx+0ffffffffffffffffh]", 0x0F, 0xC7, 0x49, 0xFF );
    FCML_I32( "lock cmpxchg8b qword ptr [ecx+0ffffffffh]", 0xF0, 0x0F, 0xC7, 0x49, 0xFF );
    FCML_I32( "xacquire lock cmpxchg8b qword ptr [ecx+0ffffffffh]", 0xF2, 0xF0, 0x0F, 0xC7, 0x49, 0xFF );
    FCML_I32( "xrelease lock cmpxchg8b qword ptr [ecx+0ffffffffh]", 0xF3, 0xF0, 0x0F, 0xC7, 0x49, 0xFF );
    FCML_A32( "xrelease lock cmpxchg8b 0xffffffff(%ecx)", 0xF3, 0xF0, 0x0F, 0xC7, 0x49, 0xFF );
}

void fcml_tf_instruction_CPUID(void) {
    FCML_I3264( "cpuid", 0x0F, 0xA2 );
    FCML_A3264( "cpuid", 0x0F, 0xA2 );
}

void fcml_tf_instruction_CRC32(void) {
    /* F2 0F 38 F0 /r CRC32 r32, r/m8 A Valid Valid Accumulate CRC32 on r/m8.*/
    /* F2 REX 0F 38 F0 /r CRC32 r32, r/m8* A Valid N.E. Accumulate CRC32 on r/m8.*/
    FCML_I64_D( "crc32 eax,byte ptr [rax+0000000000000020h]", 0xF2, 0x40, 0x0F, 0x38, 0xF0, 0x40, 0x20 );
    FCML_I64_D( "crc32 eax,byte ptr [rax+0000000000000020h]", 0x66, 0xF2, 0x0F, 0x38, 0xF0, 0x40, 0x20 );
    FCML_I64( "crc32 eax,byte ptr [rax+0000000000000020h]", 0xF2, 0x0F, 0x38, 0xF0, 0x40, 0x20 );
    FCML_I32( "crc32 eax,byte ptr [eax+00000020h]", 0xF2, 0x0F, 0x38, 0xF0, 0x40, 0x20 );
    FCML_A32( "crc32b 0x00000020(%eax),%eax", 0xF2, 0x0F, 0x38, 0xF0, 0x40, 0x20 );
    /* F2 REX.W 0F 38 F0 /r CRC32 r64, r/m8 A Valid N.E. Accumulate CRC32 on r/m8.*/
    FCML_I64( "crc32 rax,byte ptr [rax+0000000000000020h]", 0xF2, 0x48, 0x0F, 0x38, 0xF0, 0x40, 0x20 );
    FCML_A32( "crc32w 0x00000020(%eax),%eax", 0x66, 0xf2, 0x0f, 0x38, 0xf1, 0x40, 0x20 );
    FCML_A32( "crc32l 0x00000020(%eax),%eax", 0xf2, 0x0f, 0x38, 0xf1, 0x40, 0x20 );
    FCML_A64( "crc32q 0x0000000000000020(%rax),%rax", 0xf2, 0x48, 0x0f, 0x38, 0xf1, 0x40, 0x20 );
}

void fcml_tf_instruction_CVTDQ2PD(void) {
    FCML_I64( "cvtdq2pd xmm0,mmword ptr [rax+0000000000000020h]", 0xF3, 0x0F, 0xE6, 0x40, 0x20 );
    FCML_A64( "cvtdq2pd 0x0000000000000020(%rax),%xmm0", 0xF3, 0x0F, 0xE6, 0x40, 0x20 );
    FCML_I32( "cvtdq2pd xmm0,xmm2", 0xF3, 0x0F, 0xE6, 0xC2 );
    FCML_I32( "cvtdq2pd xmm0,mmword ptr [eax+00000020h]", 0xF3, 0x0F, 0xE6, 0x40, 0x20 );
    FCML_A32( "cvtdq2pd 0x00000020(%eax),%xmm0", 0xF3, 0x0F, 0xE6, 0x40, 0x20 );
    /* VEX.128.F3.0F E6 /r VCVTDQ2PD xmm1, xmm2/m64*/
    FCML_I32( "vcvtdq2pd xmm2,mmword ptr [ecx+eax]", 0xc5, 0xfa, 0xe6, 0x14, 0x01 );
    FCML_I64( "vcvtdq2pd xmm10,mmword ptr [r9+rax]", 0xC4, 0x41, 0x7A, 0xE6, 0x14, 0x01 );
    FCML_A64( "vcvtdq2pd (%rcx,%rax),%xmm2", 0xc5, 0xfa, 0xe6, 0x14, 0x01 );
    FCML_A64( "vcvtdq2pd %xmm1,%xmm0", 0xc5, 0xfa, 0xe6, 0xc1 );
    /* VEX.256.F3.0F E6 /r VCVTDQ2PD ymm1, xmm2/m128*/
    FCML_I32( "vcvtdq2pd ymm2,xmmword ptr [ecx+eax]", 0xc5, 0xfe, 0xe6, 0x14, 0x01 );
    FCML_I64( "vcvtdq2pd ymm10,xmmword ptr [r9+rax]", 0xC4, 0x41, 0x7E, 0xE6, 0x14, 0x01 );
    FCML_A64( "vcvtdq2pd (%r9,%rax),%ymm10", 0xC4, 0x41, 0x7E, 0xE6, 0x14, 0x01 );
    FCML_A64( "vcvtdq2pd %xmm1,%ymm0", 0xc5, 0xfe, 0xe6, 0xc1 );
}

void fcml_tf_instruction_CVTDQ2PS(void) {
    FCML_I64( "cvtdq2ps xmm0,xmmword ptr [rax+0000000000000020h]", 0x0F, 0x5b, 0x40, 0x20 );
    FCML_A64( "cvtdq2ps 0x0000000000000020(%rax),%xmm0", 0x0F, 0x5b, 0x40, 0x20 );
    FCML_I32( "cvtdq2ps xmm0,xmm2", 0x0F, 0x5b, 0xC2 );
    FCML_I32( "cvtdq2ps xmm0,xmmword ptr [eax+00000020h]", 0x0F, 0x5b, 0x40, 0x20 );
    /* VEX.128.0F 5B /r VCVTDQ2PS xmm1, xmm2/m128*/
    /* VEX.256.0F 5B /r VCVTDQ2PS ymm1, ymm2/m256*/
    FCML_I32( "vcvtdq2ps xmm2,xmmword ptr [ecx+eax]", 0xc5, 0xf8, 0x5b, 0x14, 0x01 );
    FCML_A64( "vcvtdq2ps (%rcx,%rax),%ymm2", 0xc5, 0xfc, 0x5b, 0x14, 0x01 );
}

void fcml_tf_instruction_CVTPD2DQ(void) {
    FCML_I64( "cvtpd2dq xmm0,xmmword ptr [rax+0000000000000020h]", 0xF2, 0x0F, 0xE6, 0x40, 0x20 );
    FCML_A64( "cvtpd2dq 0x0000000000000020(%rax),%xmm0", 0xF2, 0x0F, 0xE6, 0x40, 0x20 );
    FCML_I32( "cvtpd2dq xmm0,xmm2", 0xF2, 0x0F, 0xE6, 0xC2 );
    FCML_I32( "cvtpd2dq xmm0,xmmword ptr [eax+00000020h]", 0xF2, 0x0F, 0xE6, 0x40, 0x20 );
    /* VEX.128.F2.0F E6 /r VCVTPD2DQ xmm1, xmm2/m128*/
    /* VEX.256.F2.0F E6 /r VCVTPD2DQ xmm1, ymm2/m256*/
    FCML_I32( "vcvtpd2dq xmm2,xmmword ptr [ecx+eax]", 0xc5, 0xfb, 0xe6, 0x14, 0x01 );
    FCML_I64( "vcvtpd2dq ymm2,ymmword ptr [rcx+rax]", 0xc5, 0xff, 0xe6, 0x14, 0x01 );
    FCML_A64( "vcvtpd2dq (%rcx,%rax),%ymm2", 0xc5, 0xff, 0xe6, 0x14, 0x01 );
}

void fcml_tf_instruction_CVTPD2PI(void) {
    FCML_I64( "cvtpd2pi mm0,xmmword ptr [rax+0000000000000020h]", 0x66, 0x0F, 0x2D, 0x40, 0x20 );
    FCML_A64( "cvtpd2pi 0x0000000000000020(%rax),%mm0", 0x66, 0x0F, 0x2D, 0x40, 0x20 );
    FCML_I32( "cvtpd2pi mm0,xmm2", 0x66, 0x0F, 0x2D, 0xC2 );
    FCML_I32( "cvtpd2pi mm0,xmmword ptr [eax+00000020h]", 0x66, 0x0F, 0x2D, 0x40, 0x20 );
}

void fcml_tf_instruction_CVTPD2PS(void) {
    /* 66 0F 5A /r CVTPD2PS xmm1,xmm2/m128 A Valid Valid Convert two packed doubleprecision floating-point values in xmm2/m128 to two packed single-precision floating-point values in xmm1.*/
    FCML_I64( "cvtpd2ps xmm0,xmmword ptr [rax+0000000000000020h]", 0x66, 0x0F, 0x5A, 0x40, 0x20 );
    FCML_I32( "cvtpd2ps xmm0,xmm2", 0x66, 0x0F, 0x5A, 0xC2 );
    FCML_I32( "cvtpd2ps xmm0,xmmword ptr [eax+00000020h]", 0x66, 0x0F, 0x5A, 0x40, 0x20 );
    /* VEX.128.66.0F 5A /r VCVTPD2PS xmm1, xmm2/m128*/
    /* VEX.256.66.0F 5A /r VCVTPD2PS xmm1, ymm2/m256*/
    FCML_I32( "vcvtpd2ps xmm0,xmm1", 0xc5, 0xf9, 0x5a, 0xc1 );
    FCML_I32_D( "vcvtpd2ps xmm2,xmmword ptr [ecx+eax]", 0xC4, 0xE1, 0x79, 0x5A, 0x14, 0x01 );
    FCML_I64_D( "vcvtpd2ps xmm2,ymmword ptr [rcx+rax]", 0xC4, 0xE1, 0x7D, 0x5A, 0x14, 0x01 );
    FCML_I32( "vcvtpd2ps xmm2,xmmword ptr [ecx+eax]", 0xc5, 0xf9, 0x5a, 0x14, 0x01 );
    FCML_I64( "vcvtpd2ps xmm2,ymmword ptr [rcx+rax]", 0xc5, 0xfd, 0x5a, 0x14, 0x01 );
    /* GAS*/
    FCML_A32( "vcvtpd2psx %xmm1,%xmm0", 0xc5, 0xf9, 0x5a, 0xc1 );
    FCML_A64( "vcvtpd2psx (%rcx,%rax),%xmm2", 0xc5, 0xf9, 0x5a, 0x14, 0x01 );
    FCML_A64( "vcvtpd2psy (%rcx,%rax),%xmm2", 0xc5, 0xfd, 0x5a, 0x14, 0x01 );
}

void fcml_tf_instruction_CVTPI2PD(void) {
    FCML_I64( "cvtpi2pd xmm0,mmword ptr [rax+0000000000000020h]", 0x66, 0x0F, 0x2A, 0x40, 0x20 );
    FCML_A64( "cvtpi2pd 0x0000000000000020(%rax),%xmm0", 0x66, 0x0F, 0x2A, 0x40, 0x20 );
    FCML_I32( "cvtpi2pd xmm0,mm2", 0x66, 0x0F, 0x2A, 0xC2 );
    FCML_I32( "cvtpi2pd xmm0,mmword ptr [eax+00000020h]", 0x66, 0x0F, 0x2A, 0x40, 0x20 );
}

void fcml_tf_instruction_CVTPI2PS(void) {
    FCML_I64( "cvtpi2ps xmm0,mmword ptr [rax+0000000000000020h]", 0x0F, 0x2A, 0x40, 0x20 );
    FCML_A64( "cvtpi2ps 0x0000000000000020(%rax),%xmm0", 0x0F, 0x2A, 0x40, 0x20 );
    FCML_I32( "cvtpi2ps xmm0,mm2", 0x0F, 0x2A, 0xC2 );
    FCML_I32( "cvtpi2ps xmm0,mmword ptr [eax+00000020h]", 0x0F, 0x2A, 0x40, 0x20 );
}

void fcml_tf_instruction_CVTPS2DQ(void) {
    FCML_I64( "cvtps2dq xmm0,xmmword ptr [rax+0000000000000020h]", 0x66, 0x0F, 0x5B, 0x40, 0x20 );
    FCML_A64( "cvtps2dq 0x0000000000000020(%rax),%xmm0", 0x66, 0x0F, 0x5B, 0x40, 0x20 );
    FCML_I32( "cvtps2dq xmm0,xmm2", 0x66, 0x0F, 0x5B, 0xC2 );
    FCML_I32( "cvtps2dq xmm0,xmmword ptr [eax+00000020h]", 0x66, 0x0F, 0x5B, 0x40, 0x20 );
    /* VEX.128.66.0F 5B /r VCVTPS2DQ xmm1, xmm2/m128*/
    /* VEX.256.66.0F 5B /r VCVTPS2DQ ymm1, ymm2/m256*/
    FCML_I32_D( "vcvtps2dq xmm2,xmmword ptr [ecx+eax]", 0xC4, 0xE1, 0x79, 0x5B, 0x14, 0x01 );
    FCML_I64_D( "vcvtps2dq ymm2,ymmword ptr [rcx+rax]", 0xC4, 0xE1, 0x7D, 0x5B, 0x14, 0x01 );
    FCML_I32( "vcvtps2dq xmm2,xmmword ptr [ecx+eax]", 0xc5, 0xf9, 0x5b, 0x14, 0x01 );
    FCML_I64( "vcvtps2dq ymm2,ymmword ptr [rcx+rax]", 0xc5, 0xfd, 0x5b, 0x14, 0x01 );
    FCML_A64( "vcvtps2dq (%rcx,%rax),%ymm2", 0xc5, 0xfd, 0x5b, 0x14, 0x01 );
}

void fcml_tf_instruction_CVTPS2PD(void) {
    FCML_I64( "cvtps2pd xmm0,mmword ptr [rax+0000000000000020h]", 0x0F, 0x5A, 0x40, 0x20 );
    FCML_A64( "cvtps2pd 0x0000000000000020(%rax),%xmm0", 0x0F, 0x5A, 0x40, 0x20 );
    FCML_I32( "cvtps2pd xmm0,xmm2", 0x0F, 0x5A, 0xC2 );
    FCML_I32( "cvtps2pd xmm0,mmword ptr [eax+00000020h]", 0x0F, 0x5A, 0x40, 0x20 );
    /* VEX.128.0F 5A /r VCVTPS2PD xmm1, xmm2/m64*/
    /* VEX.256.0F 5A /r VCVTPS2PD ymm1, xmm2/m128*/
    FCML_I32_D( "vcvtps2pd xmm2,xmmword ptr [ecx+eax]", 0xC4, 0xE1, 0x78, 0x5A, 0x14, 0x01 );
    FCML_I64_D( "vcvtps2pd ymm2,ymmword ptr [rcx+rax]", 0xC4, 0xE1, 0x7C, 0x5A, 0x14, 0x01 );
    FCML_I32( "vcvtps2pd xmm2,xmmword ptr [ecx+eax]", 0xc5, 0xf8, 0x5a, 0x14, 0x01 );
    FCML_I64( "vcvtps2pd ymm2,ymmword ptr [rcx+rax]", 0xc5, 0xfc, 0x5a, 0x14, 0x01 );
    FCML_A64( "vcvtps2pd (%rcx,%rax),%ymm2", 0xc5, 0xfc, 0x5a, 0x14, 0x01 );
}

void fcml_tf_instruction_CVTPS2PI(void) {
    FCML_I64( "cvtps2pi mm0,mmword ptr [rax+0000000000000020h]", 0x0F, 0x2D, 0x40, 0x20 );
    FCML_A64( "cvtps2pi 0x0000000000000020(%rax),%mm0", 0x0F, 0x2D, 0x40, 0x20 );
    FCML_I32( "cvtps2pi mm0,xmm2", 0x0F, 0x2D, 0xC2 );
    FCML_I32( "cvtps2pi mm0,mmword ptr [eax+00000020h]", 0x0F, 0x2D, 0x40, 0x20 );
}

void fcml_tf_instruction_CVTSD2SI(void) {
    FCML_I64( "cvtsd2si eax,mmword ptr [rax+0000000000000020h]", 0xF2, 0x0F, 0x2D, 0x40, 0x20 );
    FCML_A64( "cvtsd2si 0x0000000000000020(%rax),%eax", 0xF2, 0x0F, 0x2D, 0x40, 0x20 );
    FCML_I32( "cvtsd2si eax,xmm2", 0xF2, 0x0F, 0x2D, 0xC2 );
    FCML_I32( "cvtsd2si eax,mmword ptr [eax+00000020h]", 0xF2, 0x0F, 0x2D, 0x40, 0x20 );
    FCML_I64( "cvtsd2si rax,mmword ptr [rax+0000000000000020h]", 0xF2, 0x48, 0x0F, 0x2D, 0x40, 0x20 );
    /* VEX.128.F2.0F.W0 2D /r VCVTSD2SI r32, xmm1/m64*/
    FCML_I32_D( "vcvtsd2si edx,mmword ptr [ecx+eax]", 0xC4, 0xE1, 0x7B, 0x2D, 0x14, 0x01 );
    FCML_I64_D( "vcvtsd2si edx,mmword ptr [rcx+rax]", 0xC4, 0xE1, 0x7B, 0x2D, 0x14, 0x01 );
    FCML_I32( "vcvtsd2si edx,mmword ptr [ecx+eax]", 0xc5, 0xfb, 0x2d, 0x14, 0x01 );
    FCML_I64( "vcvtsd2si edx,mmword ptr [rcx+rax]", 0xc5, 0xfb, 0x2d, 0x14, 0x01 );
    /* VEX.128.F2.0F.W1 2D /r VCVTSD2SI r64, xmm1/m64*/
    FCML_I64( "vcvtsd2si rdx,mmword ptr [rcx+rax]", 0xC4, 0xE1, 0xFB, 0x2D, 0x14, 0x01 );
    FCML_A64( "vcvtsd2si (%rcx,%rax),%rdx", 0xC4, 0xE1, 0xFB, 0x2D, 0x14, 0x01 );
}

void fcml_tf_instruction_CVTSD2SS(void) {
    FCML_I64( "cvtsd2ss xmm0,mmword ptr [rax+0000000000000020h]", 0xF2, 0x0F, 0x5A, 0x40, 0x20 );
    FCML_A64( "cvtsd2ss 0x0000000000000020(%rax),%xmm0", 0xF2, 0x0F, 0x5A, 0x40, 0x20 );
    FCML_I32( "cvtsd2ss xmm0,xmm2", 0xF2, 0x0F, 0x5A, 0xC2 );
    FCML_I32( "cvtsd2ss xmm0,mmword ptr [eax+00000020h]", 0xF2, 0x0F, 0x5A, 0x40, 0x20 );
    /* VEX.NDS.128.F2.0F 5A /r VCVTSD2SS xmm1,xmm2,xmm3/m64*/
    FCML_I32_D( "vcvtsd2ss xmm2,xmm6,mmword ptr [ecx+eax]", 0xC4, 0xE1, 0x4B, 0x5A, 0x14, 0x01 );
    FCML_I64_D( "vcvtsd2ss xmm2,xmm6,mmword ptr [rcx+rax]", 0xC4, 0xE1, 0x4B, 0x5A, 0x14, 0x01 );
    FCML_I32( "vcvtsd2ss xmm2,xmm6,mmword ptr [ecx+eax]", 0xc5, 0xcb, 0x5a, 0x14, 0x01 );
    FCML_I64( "vcvtsd2ss xmm2,xmm6,mmword ptr [rcx+rax]", 0xc5, 0xcb, 0x5a, 0x14, 0x01 );
    FCML_A64( "vcvtsd2ss (%rcx,%rax),%xmm6,%xmm2", 0xc5, 0xcb, 0x5a, 0x14, 0x01 );
}

void fcml_tf_instruction_CVTSI2SD(void) {
    FCML_I64( "cvtsi2sd xmm0,dword ptr [rax+0000000000000020h]", 0xF2, 0x0F, 0x2A, 0x40, 0x20 );
    FCML_A64( "cvtsi2sdl 0x0000000000000020(%rax),%xmm0", 0xF2, 0x0F, 0x2A, 0x40, 0x20 );
    FCML_I32( "cvtsi2sd xmm0,edx", 0xF2, 0x0F, 0x2A, 0xC2 );
    FCML_I32( "cvtsi2sd xmm0,dword ptr [eax+00000020h]", 0xF2, 0x0F, 0x2A, 0x40, 0x20 );
    FCML_I64( "cvtsi2sd xmm0,dword ptr [rax+0000000000000020h]", 0xF2, 0x0F, 0x2A, 0x40, 0x20 );
    FCML_I64( "cvtsi2sd xmm0,edx", 0xF2, 0x0F, 0x2A, 0xC2 );
    FCML_I64( "cvtsi2sd xmm0,rdx", 0xF2, 0x48, 0x0F, 0x2A, 0xC2 );
    /* VEX.NDS.128.F2.0F.W0 2A /r VCVTSI2SD xmm1, xmm2, r/m32*/
    FCML_I32( "vcvtsi2sd xmm2,xmm7,dword ptr [ecx+eax]", 0xc5, 0xc3, 0x2a, 0x14, 0x01 );
    FCML_A32( "vcvtsi2sdl (%ecx,%eax),%xmm7,%xmm2", 0xc5, 0xc3, 0x2a, 0x14, 0x01 );
    FCML_I64( "vcvtsi2sd xmm2,xmm7,dword ptr [rcx+rax]", 0xc5, 0xc3, 0x2a, 0x14, 0x01 );
    /* VEX.NDS.128.F2.0F.W1 2A /r VCVTSI2SD xmm1, xmm2, r/m64*/
    FCML_I64( "vcvtsi2sd xmm2,xmm7,qword ptr [rcx+rax]", 0xC4, 0xE1, 0xC3, 0x2A, 0x14, 0x01 );
    FCML_A64( "vcvtsi2sdq (%rcx,%rax),%xmm7,%xmm2", 0xC4, 0xE1, 0xC3, 0x2A, 0x14, 0x01 );
}

void fcml_tf_instruction_CVTSI2SS(void) {
    FCML_I64( "cvtsi2ss xmm0,rdx", 0xF3, 0x48, 0x0F, 0x2A, 0xC2 );
    FCML_I64( "cvtsi2ss xmm0,dword ptr [rax+0000000000000020h]", 0xF3, 0x0F, 0x2A, 0x40, 0x20 );
    FCML_A64( "cvtsi2ssl 0x0000000000000020(%rax),%xmm0", 0xF3, 0x0F, 0x2A, 0x40, 0x20 );
    FCML_I32( "cvtsi2ss xmm0,edx", 0xF3, 0x0F, 0x2A, 0xC2 );
    FCML_I32( "cvtsi2ss xmm0,dword ptr [eax+00000020h]", 0xF3, 0x0F, 0x2A, 0x40, 0x20 );
    FCML_I64( "cvtsi2ss xmm0,dword ptr [rax+0000000000000020h]", 0xF3, 0x0F, 0x2A, 0x40, 0x20 );
    FCML_I64( "cvtsi2ss xmm0,edx", 0xF3, 0x0F, 0x2A, 0xC2 );
    /* VEX.NDS.128.F3.0F.W0 2A /r VCVTSI2SS xmm1, xmm2, r/m32*/
    FCML_I32_D( "vcvtsi2ss xmm2,xmm7,dword ptr [ecx+eax]", 0xC4, 0xE1, 0x42, 0x2A, 0x14, 0x01 );
    FCML_I64_D( "vcvtsi2ss xmm2,xmm7,dword ptr [rcx+rax]", 0xC4, 0xE1, 0x42, 0x2A, 0x14, 0x01 );
    FCML_I32( "vcvtsi2ss xmm2,xmm7,dword ptr [ecx+eax]", 0xc5, 0xc2, 0x2a, 0x14, 0x01 );
    FCML_I64( "vcvtsi2ss xmm2,xmm7,dword ptr [rcx+rax]", 0xc5, 0xc2, 0x2a, 0x14, 0x01 );
    /* VEX.NDS.128.F3.0F.W1 2A /r VCVTSI2SS xmm1, xmm2, r/m64*/
    FCML_I64( "vcvtsi2ss xmm2,xmm7,qword ptr [rcx+rax]", 0xC4, 0xE1, 0xC2, 0x2A, 0x14, 0x01 );
    FCML_A64( "vcvtsi2ssq (%rcx,%rax),%xmm7,%xmm2", 0xC4, 0xE1, 0xC2, 0x2A, 0x14, 0x01 );
}

void fcml_tf_instruction_CVTSS2SD(void) {
    FCML_I64( "cvtss2sd xmm0,dword ptr [rax+0000000000000020h]", 0xF3, 0x0F, 0x5A, 0x40, 0x20 );
    FCML_A64( "cvtss2sd 0x0000000000000020(%rax),%xmm0", 0xF3, 0x0F, 0x5A, 0x40, 0x20 );
    FCML_I32( "cvtss2sd xmm0,xmm2", 0xF3, 0x0F, 0x5A, 0xC2 );
    FCML_I32( "cvtss2sd xmm0,dword ptr [eax+00000020h]", 0xF3, 0x0F, 0x5A, 0x40, 0x20 );
    /* VEX.NDS.128.F3.0F 5A /r VCVTSS2SD xmm1, xmm2, xmm3/m32*/
    FCML_I32_D( "vcvtss2sd xmm2,xmm1,dword ptr [ecx+eax]", 0xC4, 0xE1, 0x72, 0x5A, 0x14, 0x01 );
    FCML_I64_D( "vcvtss2sd xmm2,xmm3,dword ptr [rcx+rax]", 0xC4, 0xE1, 0x62, 0x5A, 0x14, 0x01 );
    FCML_I32( "vcvtss2sd xmm2,xmm1,dword ptr [ecx+eax]", 0xc5, 0xf2, 0x5a, 0x14, 0x01 );
    FCML_A64( "vcvtss2sd (%rcx,%rax),%xmm3,%xmm2", 0xc5, 0xe2, 0x5a, 0x14, 0x01 );
}

void fcml_tf_instruction_CVTSS2SI(void) {
    FCML_I64( "cvtss2si rax,xmm2", 0xF3, 0x48, 0x0F, 0x2D, 0xC2 );
    FCML_I64( "cvtss2si eax,dword ptr [rax+0000000000000020h]", 0xF3, 0x0F, 0x2D, 0x40, 0x20 );
    FCML_A64( "cvtss2si 0x0000000000000020(%rax),%eax", 0xF3, 0x0F, 0x2D, 0x40, 0x20 );
    FCML_I32( "cvtss2si eax,xmm2", 0xF3, 0x0F, 0x2D, 0xC2 );
    FCML_I32( "cvtss2si eax,dword ptr [eax+00000020h]", 0xF3, 0x0F, 0x2D, 0x40, 0x20 );
    FCML_I64( "cvtss2si eax,dword ptr [rax+0000000000000020h]", 0xF3, 0x0F, 0x2D, 0x40, 0x20 );
    FCML_I64( "cvtss2si eax,xmm2", 0xF3, 0x0F, 0x2D, 0xC2 );
    /* VEX.128.F3.0F.W0 2D /r VCVTSS2SI r32, xmm1/m32*/
    FCML_I32_D( "vcvtss2si edx,dword ptr [ecx+eax]", 0xC4, 0xE1, 0x7A, 0x2D, 0x14, 0x01 );
    FCML_I64_D( "vcvtss2si edx,dword ptr [rcx+rax]", 0xC4, 0xE1, 0x7A, 0x2D, 0x14, 0x01 );
    FCML_I32( "vcvtss2si edx,dword ptr [ecx+eax]", 0xc5, 0xfa, 0x2d, 0x14, 0x01 );
    FCML_I64( "vcvtss2si edx,dword ptr [rcx+rax]", 0xc5, 0xfa, 0x2d, 0x14, 0x01 );
    /* VEX.128.F3.0F.W1 2D /r VCVTSS2SI r64, xmm1/m32*/
    FCML_I64( "vcvtss2si rdx,dword ptr [rcx+rax]", 0xC4, 0xE1, 0xFA, 0x2D, 0x14, 0x01 );
    FCML_A64( "vcvtss2si (%rcx,%rax),%rdx", 0xC4, 0xE1, 0xFA, 0x2D, 0x14, 0x01 );
}

void fcml_tf_instruction_CVTTPD2DQ(void) {
    FCML_I64( "cvttpd2dq xmm0,xmmword ptr [rax+0000000000000020h]", 0x66, 0x0F, 0xE6, 0x40, 0x20 );
    FCML_A64( "cvttpd2dq 0x0000000000000020(%rax),%xmm0", 0x66, 0x0F, 0xE6, 0x40, 0x20 );
    FCML_I32( "cvttpd2dq xmm0,xmm2", 0x66, 0x0F, 0xE6, 0xC2 );
    FCML_I32( "cvttpd2dq xmm0,xmmword ptr [eax+00000020h]", 0x66, 0x0F, 0xE6, 0x40, 0x20 );
    /* VEX.128.66.0F E6 /r VCVTTPD2DQ xmm1, xmm2/m128*/
    /* VEX.256.66.0F E6 /r VCVTTPD2DQ xmm1, ymm2/m256*/
    FCML_I32_D( "vcvttpd2dq xmm2,xmmword ptr [ecx+eax]", 0xC4, 0xE1, 0x79, 0xE6, 0x14, 0x01 );
    FCML_I64_D( "vcvttpd2dq xmm2,ymmword ptr [rcx+rax]", 0xC4, 0xE1, 0x7D, 0xE6, 0x14, 0x01 );
    FCML_I32( "vcvttpd2dq xmm2,xmmword ptr [ecx+eax]", 0xc5, 0xf9, 0xe6, 0x14, 0x01 );
    FCML_I64( "vcvttpd2dq xmm2,ymmword ptr [rcx+rax]", 0xc5, 0xfd, 0xe6, 0x14, 0x01 );
    FCML_A64( "vcvttpd2dqx (%rcx,%rax),%xmm2", 0xc5, 0xf9, 0xe6, 0x14, 0x01 );
    FCML_A64( "vcvttpd2dqy (%rcx,%rax),%xmm2", 0xc5, 0xfd, 0xe6, 0x14, 0x01 );
}

void fcml_tf_instruction_CVTTPD2PI(void) {
    FCML_I64( "cvttpd2pi mm0,xmmword ptr [rax+0000000000000020h]", 0x66, 0x0F, 0x2C, 0x40, 0x20 );
    FCML_A64( "cvttpd2pi 0x0000000000000020(%rax),%mm0", 0x66, 0x0F, 0x2C, 0x40, 0x20 );
    FCML_I32( "cvttpd2pi mm0,xmm2", 0x66, 0x0F, 0x2C, 0xC2 );
    FCML_I32( "cvttpd2pi mm0,xmmword ptr [eax+00000020h]", 0x66, 0x0F, 0x2C, 0x40, 0x20 );
}

void fcml_tf_instruction_CVTTPS2DQ(void) {
    FCML_I64( "cvttps2dq xmm0,xmmword ptr [rax+0000000000000020h]", 0xF3, 0x0F, 0x5B, 0x40, 0x20 );
    FCML_A64( "cvttps2dq 0x0000000000000020(%rax),%xmm0", 0xF3, 0x0F, 0x5B, 0x40, 0x20 );
    FCML_I32( "cvttps2dq xmm0,xmm2", 0xF3, 0x0F, 0x5B, 0xC2 );
    FCML_I32( "cvttps2dq xmm0,xmmword ptr [eax+00000020h]", 0xF3, 0x0F, 0x5B, 0x40, 0x20 );
    /* VEX.128.F3.0F 5B /r VCVTTPS2DQ xmm1, xmm2/m128*/
    /* VEX.256.F3.0F 5B /r VCVTTPS2DQ ymm1, ymm2/m256*/
    FCML_I32_D( "vcvttps2dq xmm2,xmmword ptr [ecx+eax]", 0xC4, 0xE1, 0x7A, 0x5B, 0x14, 0x01 );
    FCML_I64_D( "vcvttps2dq ymm2,ymmword ptr [rcx+rax]", 0xC4, 0xE1, 0x7E, 0x5B, 0x14, 0x01 );
    FCML_I32( "vcvttps2dq xmm2,xmmword ptr [ecx+eax]", 0xc5, 0xfa, 0x5b, 0x14, 0x01 );
    FCML_A32( "vcvttps2dq (%ecx,%eax),%xmm2", 0xc5, 0xfa, 0x5b, 0x14, 0x01 );
    FCML_I64( "vcvttps2dq ymm2,ymmword ptr [rcx+rax]", 0xc5, 0xfe, 0x5b, 0x14, 0x01 );
    FCML_A64( "vcvttps2dq (%rcx,%rax),%ymm2", 0xc5, 0xfe, 0x5b, 0x14, 0x01 );
}

void fcml_tf_instruction_CVTTPS2PI(void) {
    FCML_I64( "cvttps2pi mm0,mmword ptr [rax+0000000000000020h]", 0x0F, 0x2C, 0x40, 0x20 );
    FCML_A64( "cvttps2pi 0x0000000000000020(%rax),%mm0", 0x0F, 0x2C, 0x40, 0x20 );
    FCML_I32( "cvttps2pi mm0,xmm2", 0x0F, 0x2C, 0xC2 );
    FCML_I32( "cvttps2pi mm0,mmword ptr [eax+00000020h]", 0x0F, 0x2C, 0x40, 0x20 );
}

void fcml_tf_instruction_CVTTSD2SI(void) {
    FCML_I64( "cvttsd2si rax,xmm2", 0xF2, 0x48, 0x0F, 0x2C, 0xC2 );
    FCML_A64( "cvttsd2si %xmm2,%rax", 0xF2, 0x48, 0x0F, 0x2C, 0xC2 );
    FCML_I64( "cvttsd2si eax,mmword ptr [rax+0000000000000020h]", 0xF2, 0x0F, 0x2C, 0x40, 0x20 );
    FCML_A64( "cvttsd2si 0x0000000000000020(%rax),%eax", 0xF2, 0x0F, 0x2C, 0x40, 0x20 );
    FCML_I32( "cvttsd2si eax,xmm2", 0xF2, 0x0F, 0x2C, 0xC2 );
    FCML_I32( "cvttsd2si eax,mmword ptr [eax+00000020h]", 0xF2, 0x0F, 0x2C, 0x40, 0x20 );
    FCML_I64( "cvttsd2si eax,mmword ptr [rax+0000000000000020h]", 0xF2, 0x0F, 0x2C, 0x40, 0x20 );
    FCML_I64( "cvttsd2si eax,xmm2", 0xF2, 0x0F, 0x2C, 0xC2 );
    /* VEX.128.F2.0F.W0 2C /r VCVTTSD2SI r32, xmm1/m64*/
    FCML_I32_D( "vcvttsd2si edx,mmword ptr [ecx+eax]", 0xC4, 0xE1, 0x7B, 0x2C, 0x14, 0x01 );
    FCML_I64_D( "vcvttsd2si edx,mmword ptr [rcx+rax]", 0xC4, 0xE1, 0x7B, 0x2C, 0x14, 0x01 );
    FCML_I32( "vcvttsd2si edx,mmword ptr [ecx+eax]", 0xc5, 0xfb, 0x2c, 0x14, 0x01 );
    FCML_I64( "vcvttsd2si edx,mmword ptr [rcx+rax]", 0xc5, 0xfb, 0x2c, 0x14, 0x01 );
    FCML_A64( "vcvttsd2si (%rcx,%rax),%edx", 0xc5, 0xfb, 0x2c, 0x14, 0x01 );
    /* VEX.128.F2.0F.W1 2C /r VCVTTSD2SI r64, xmm1/m64*/
    FCML_I64( "vcvttsd2si rdx,mmword ptr [rcx+rax]", 0xC4, 0xE1, 0xFB, 0x2C, 0x14, 0x01 );
}

void fcml_tf_instruction_CVTTSS2SI(void) {
    FCML_I64( "cvttss2si rax,xmm2", 0xF3, 0x48, 0x0F, 0x2C, 0xC2 );
    FCML_I64( "cvttss2si eax,dword ptr [rax+0000000000000020h]", 0xF3, 0x0F, 0x2C, 0x40, 0x20 );
    FCML_A64( "cvttss2si 0x0000000000000020(%rax),%eax", 0xF3, 0x0F, 0x2C, 0x40, 0x20 );
    FCML_I32( "cvttss2si eax,xmm2", 0xF3, 0x0F, 0x2C, 0xC2 );
    FCML_I32( "cvttss2si eax,dword ptr [eax+00000020h]", 0xF3, 0x0F, 0x2C, 0x40, 0x20 );
    FCML_I64( "cvttss2si eax,dword ptr [rax+0000000000000020h]", 0xF3, 0x0F, 0x2C, 0x40, 0x20 );
    FCML_I64( "cvttss2si eax,xmm2", 0xF3, 0x0F, 0x2C, 0xC2 );
    /* VEX.128.F3.0F.W0 2C /r VCVTTSS2SI r32, xmm1/m32*/
    FCML_I32_D( "vcvttss2si edx,dword ptr [ecx+eax]", 0xC4, 0xE1, 0x7A, 0x2C, 0x14, 0x01 );
    FCML_I64_D( "vcvttss2si edx,dword ptr [rcx+rax]", 0xC4, 0xE1, 0x7A, 0x2C, 0x14, 0x01 );
    FCML_I32( "vcvttss2si edx,dword ptr [ecx+eax]", 0xc5, 0xfa, 0x2c, 0x14, 0x01 );
    FCML_I64( "vcvttss2si edx,dword ptr [rcx+rax]", 0xc5, 0xfa, 0x2c, 0x14, 0x01 );
    /* VEX.128.F3.0F.W1 2C /r VCVTTSS2SI r64, xmm1/m32*/
    FCML_I64( "vcvttss2si rdx,dword ptr [rcx+rax]", 0xC4, 0xE1, 0xFA, 0x2C, 0x14, 0x01 );
    FCML_A64( "vcvttss2si (%rcx,%rax),%rdx", 0xC4, 0xE1, 0xFA, 0x2C, 0x14, 0x01 );
}

void fcml_tf_instruction_CWD_CDQ_CQO(void) {
    FCML_I32( "cdq", 0x99 );
    FCML_I32( "cwd", 0x66, 0x99 );
    FCML_I64( "cdq", 0x99 );
    FCML_I64( "cwd", 0x66, 0x99 );
    FCML_I64_D( "cqo", 0x66, 0x48, 0x99 );
    FCML_I64( "cqo", 0x48, 0x99 );
    FCML_I64_D( "cdq", 0x40, 0x99 );
    FCML_I64( "cdq", 0x99 );
    FCML_A32( "cltd", 0x99 );
    FCML_A32( "cwtd", 0x66, 0x99 );
    FCML_A64( "cqto", 0x48, 0x99 );
}

void fcml_tf_instruction_CLAC(void) {
    FCML_I3264( "clac", 0x0F, 0x01, 0xCA );
    /* GAS*/
    FCML_A3264( "clac", 0x0F, 0x01, 0xCA );
}

void fcml_tf_instruction_COMISD() {
	FCML_I64( "comisd xmm0,xmm2", 0x66, 0x0F, 0x2F, 0xC2 );
	FCML_I64( "comisd xmm0,mmword ptr [rax+0000000000000020h]", 0x66, 0x0F, 0x2F, 0x40, 0x20 );
	FCML_A64( "comisd 0x0000000000000020(%rax),%xmm0", 0x66, 0x0F, 0x2F, 0x40, 0x20 );
	FCML_I32( "comisd xmm0,xmm2", 0x66, 0x0F, 0x2F, 0xC2 );
	FCML_I32( "comisd xmm0,mmword ptr [eax+00000020h]", 0x66, 0x0F, 0x2F, 0x40, 0x20 );
	/* VEX.128.66.0F 2F /r VCOMISD xmm1, xmm2/m64*/
	FCML_I32( "vcomisd xmm2,mmword ptr [ecx+eax]", 0xc5, 0xf9, 0x2f, 0x14, 0x01 );
	FCML_I64( "vcomisd xmm10,mmword ptr [r9+rax]", 0xC4, 0x41, 0x79, 0x2F, 0x14, 0x01 );
	FCML_A64( "vcomisd (%r9,%rax),%xmm10", 0xC4, 0x41, 0x79, 0x2F, 0x14, 0x01 );
}

void fcml_tf_instruction_COMISS() {
	FCML_I64( "comiss xmm0,xmm2", 0x0F, 0x2F, 0xC2 );
	FCML_I64( "comiss xmm0,dword ptr [rax+0000000000000020h]", 0x0F, 0x2F, 0x40, 0x20 );
	FCML_A64( "comiss 0x0000000000000020(%rax),%xmm0", 0x0F, 0x2F, 0x40, 0x20 );
	FCML_I32( "comiss xmm0,xmm2", 0x0F, 0x2F, 0xC2 );
	FCML_I32( "comiss xmm0,dword ptr [eax+00000020h]", 0x0F, 0x2F, 0x40, 0x20 );
	/* VEX.128.0F 2F /r VCOMISS xmm1, xmm2/m32*/
	FCML_I32( "vcomiss xmm2,mmword ptr [ecx+eax]", 0xc5, 0xf8, 0x2f, 0x14, 0x01 );
	FCML_I64( "vcomiss xmm10,mmword ptr [r9+rax]", 0xC4, 0x41, 0x78, 0x2F, 0x14, 0x01 );
	FCML_A64( "vcomiss (%r9,%rax),%xmm10", 0xC4, 0x41, 0x78, 0x2F, 0x14, 0x01 );
}

fcml_stf_test_case fctl_ti_instructions_c[] = {
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
	{ "fcml_tf_instruction_CMPSD", fcml_tf_instruction_CMPSD },
	{ "fcml_tf_instruction_CMPSS", fcml_tf_instruction_CMPSS },
	{ "fcml_tf_instruction_CMPXCHG", fcml_tf_instruction_CMPXCHG },
	{ "fcml_tf_instruction_CMPXCHG16B_CMPXCHG8B", fcml_tf_instruction_CMPXCHG16B_CMPXCHG8B },
	{ "fcml_tf_instruction_CPUID", fcml_tf_instruction_CPUID },
	{ "fcml_tf_instruction_CRC32", fcml_tf_instruction_CRC32 },
	{ "fcml_tf_instruction_CVTDQ2PD", fcml_tf_instruction_CVTDQ2PD },
	{ "fcml_tf_instruction_CVTDQ2PS", fcml_tf_instruction_CVTDQ2PS },
	{ "fcml_tf_instruction_CVTPD2DQ", fcml_tf_instruction_CVTPD2DQ },
	{ "fcml_tf_instruction_CVTPD2PI", fcml_tf_instruction_CVTPD2PI },
	{ "fcml_tf_instruction_CVTPD2PS", fcml_tf_instruction_CVTPD2PS },
	{ "fcml_tf_instruction_CVTPI2PD", fcml_tf_instruction_CVTPI2PD },
	{ "fcml_tf_instruction_CVTPI2PS", fcml_tf_instruction_CVTPI2PS },
	{ "fcml_tf_instruction_CVTPS2DQ", fcml_tf_instruction_CVTPS2DQ },
	{ "fcml_tf_instruction_CVTPS2PD", fcml_tf_instruction_CVTPS2PD },
	{ "fcml_tf_instruction_CVTPS2PI", fcml_tf_instruction_CVTPS2PI },
	{ "fcml_tf_instruction_CVTSD2SI", fcml_tf_instruction_CVTSD2SI },
	{ "fcml_tf_instruction_CVTSD2SS", fcml_tf_instruction_CVTSD2SS },
	{ "fcml_tf_instruction_CVTSI2SD", fcml_tf_instruction_CVTSI2SD },
	{ "fcml_tf_instruction_CVTSI2SS", fcml_tf_instruction_CVTSI2SS },
	{ "fcml_tf_instruction_CVTSS2SD", fcml_tf_instruction_CVTSS2SD },
	{ "fcml_tf_instruction_CVTSS2SI", fcml_tf_instruction_CVTSS2SI },
	{ "fcml_tf_instruction_CVTTPD2DQ", fcml_tf_instruction_CVTTPD2DQ },
	{ "fcml_tf_instruction_CVTTPD2PI", fcml_tf_instruction_CVTTPD2PI },
	{ "fcml_tf_instruction_CVTTPS2DQ", fcml_tf_instruction_CVTTPS2DQ },
	{ "fcml_tf_instruction_CVTTPS2PI", fcml_tf_instruction_CVTTPS2PI },
	{ "fcml_tf_instruction_CVTTSD2SI", fcml_tf_instruction_CVTTSD2SI },
	{ "fcml_tf_instruction_CVTTSS2SI", fcml_tf_instruction_CVTTSS2SI },
	{ "fcml_tf_instruction_CWD_CDQ_CQO", fcml_tf_instruction_CWD_CDQ_CQO },
	{ "fcml_tf_instruction_CLAC", fcml_tf_instruction_CLAC },
	{ "fcml_tf_instruction_COMISD", fcml_tf_instruction_COMISD },
	{ "fcml_tf_instruction_COMISS", fcml_tf_instruction_COMISS },
	FCML_STF_NULL_TEST
};

fcml_stf_test_suite fctl_si_instructions_c = {
	"suite-fctl_ti_instructions_c", fcml_tf_instructions_c_suite_init, fcml_tf_instructions_c_suite_cleanup, fctl_ti_instructions_c
};


