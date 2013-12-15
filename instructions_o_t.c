/*
 * instructions.c
 *
 *  Created on: 01-06-2013
 *      Author: tAs
 */

#include "fcml_env.h"
#include "fcml_assembler.h"
#include "instructions_o_t.h"
#include <fcml_rend.h>

int fcml_tf_instructions_o_suite_init(void) {
	return 0;
}

int fcml_tf_instructions_o_suite_cleanup(void) {
	return 0;
}

void fcml_tf_instruction_OR(void) {
    // 0C ib OR AL, imm8 I Valid Valid AL OR imm8.
    FCML_I32_M( "or al,42h", 2, FCML_MI( 0x80, 0xc8, 0x42 ), FCML_MI( 0x0c, 0x42 ) );
    FCML_I32_A_FAILED( "lock or al,42h", 0xF0, 0x80, 0xc8, 0x42 );
    FCML_I32_D( "lock or al,42h", 0xF0, 0x80, 0xc8, 0x42 );
    // 0D iw OR AX, imm16 I Valid Valid AX OR imm16.
    // 0D id OR EAX, imm32 I Valid Valid EAX OR imm32.
    FCML_I32_M( "or ax,8042h", 2, FCML_MI( 0x66, 0x81, 0xc8, 0x42, 0x80 ), FCML_MI( 0x66, 0x0d, 0x42, 0x80 ) );
    FCML_I32_M( "or eax,42806521h", 2, FCML_MI( 0x81, 0xc8, 0x21, 0x65, 0x80, 0x42 ), FCML_MI( 0x0d, 0x21, 0x65, 0x80, 0x42 ) );
    FCML_I64_M( "or rax,0000000042806521h", 2, FCML_MI( 0x48, 0x81, 0xc8, 0x21, 0x65, 0x80, 0x42 ), FCML_MI( 0x48, 0x0d, 0x21, 0x65, 0x80, 0x42 ) )
    FCML_I64_M( "or ax,6521h", 2, FCML_MI( 0x66, 0x81, 0xc8, 0x21, 0x65 ), FCML_MI( 0x66, 0x0d, 0x21, 0x65 ) );
    // REX.W + 0D id OR RAX, imm32 I Valid N.E. RAX OR imm32 (sign-extended).
    FCML_I64_M( "or rax,0000000042806521h", 2, FCML_MI( 0x48, 0x81, 0xc8, 0x21, 0x65, 0x80, 0x42 ), FCML_MI( 0x48, 0x0d, 0x21, 0x65, 0x80, 0x42 ) );
    FCML_I64_M( "or rax,0ffffffffffffffffh", 3, FCML_MI( 0x67, 0x48, 0x83, 0xc8, 0xff ), FCML_MI( 0x67, 0x48, 0x81, 0xc8, 0xff, 0xff, 0xff, 0xff ), FCML_MI( 0x67, 0x48, 0x0d, 0xff, 0xff, 0xff, 0xff ) );
    // 80 /1 ib OR r/m8, imm8 MI Valid Valid r/m8 OR imm8.
    // REX + 80 /1 ib OR r/m8*, imm8 MI Valid N.E. r/m8 OR imm8.
    FCML_I32( "lock or byte ptr [04030201h],0ffh", 0xF0, 0x80, 0x0d, 0x01, 0x02, 0x03, 0x04, 0xff );
    FCML_I32( "xacquire lock or byte ptr [04030201h],0ffh", 0xF2, 0xF0, 0x80, 0x0d, 0x01, 0x02, 0x03, 0x04, 0xff );
    FCML_I32( "xrelease lock or byte ptr [04030201h],0ffh", 0xF3, 0xF0, 0x80, 0x0d, 0x01, 0x02, 0x03, 0x04, 0xff );
    FCML_I32( "or byte ptr [esi+04030201h],0ffh", 0x80, 0x8e, 0x01, 0x02, 0x03, 0x04, 0xff );
    FCML_I32( "or byte ptr [ecx+eax+00000002h],03h", 0x80, 0x4c, 0x01, 0x02, 0x03 );
    // 81 /1 iw OR r/m16, imm16 MI Valid Valid r/m16 OR imm16.
    // 81 /1 id OR r/m32, imm32 MI Valid Valid r/m32 OR imm32.
    FCML_I32( "or ebp,04030201h", 0x81, 0xcd, 0x01, 0x02, 0x03, 0x04 );
    FCML_I32( "or bp,0201h", 0x66, 0x81, 0xcd, 0x01, 0x02 );
    FCML_I64( "or bp,0201h", 0x66, 0x67, 0x81, 0xcd, 0x01, 0x02 );
    // REX.W + 81 /1 id OR r/m64, imm32 MI Valid N.E. r/m64 OR imm32 (sign-extended).
    FCML_I64( "or rbp,0000000004030201h", 0x48, 0x81, 0xcd, 0x01, 0x02, 0x03, 0x04 );
    FCML_I64_M( "or rbp,0ffffffffffffffffh", 2, FCML_MI( 0x48, 0x83, 0xcd, 0xff ), FCML_MI( 0x48, 0x81, 0xcd, 0xff, 0xff, 0xff, 0xff ) );
    FCML_I64_M( "or rbp,0ffffffffffffffffh", 2, FCML_MI( 0x67, 0x48, 0x83, 0xcd, 0xff ), FCML_MI( 0x67, 0x48, 0x81, 0xcd, 0xff, 0xff, 0xff, 0xff ) );
    FCML_I64_M( "or rbp,0ffffffffffffffffh", 2, FCML_MI( 0x48, 0x83, 0xcd, 0xff ), FCML_MI( 0x48, 0x81, 0xcd, 0xff, 0xff, 0xff, 0xff ) );
    // 83 /1 ib OR r/m16, imm8 MI Valid Valid r/m16 OR imm8 (sign-extended).
    // 83 /1 ib OR r/m32, imm8 MI Valid Valid r/m32 OR imm8 (sign-extended).
    FCML_I32_M( "lock or dword ptr [esi],00000001h", 2, FCML_MI( 0xF0, 0x83, 0x0e, 0x01 ), FCML_MI( 0xF0, 0x81, 0x0e, 0x01, 0x00, 0x00, 0x00 ) );
    FCML_I32_M( "xacquire lock or dword ptr [esi],00000001h", 2, FCML_MI( 0xF2, 0xF0, 0x83, 0x0e, 0x01 ), FCML_MI( 0xF2, 0xF0, 0x81, 0x0e, 0x01, 0x00, 0x00, 0x00 ) );
    FCML_I32_M( "xrelease lock or dword ptr [esi],00000001h", 2, FCML_MI( 0xF3, 0xF0, 0x83, 0x0e, 0x01 ), FCML_MI( 0xF3, 0xF0, 0x81, 0x0e, 0x01, 0x00, 0x00, 0x00 ) );
    FCML_I32_M( "or word ptr [esi],0001h", 2, FCML_MI( 0x66, 0x83, 0x0e, 0x01 ), FCML_MI( 0x66, 0x81, 0x0e, 0x01, 0x00 ) );
    FCML_I32_M( "or dword ptr [0201h],00000003h", 2, FCML_MI( 0x67, 0x83, 0x0e, 0x01, 0x02, 0x03 ), FCML_MI( 0x67, 0x81, 0x0e, 0x01, 0x02, 0x03, 0x00, 0x00, 0x00 ) );
    // REX.W + 83 /1 ib OR r/m64, imm8 MI Valid N.E. r/m64 OR imm8 (sign-extended).
    FCML_I64_M( "or qword ptr [rdi+0000000004030201h],0000000000000005h", 2, FCML_MI( 0x48, 0x83, 0x8f, 0x01, 0x02, 0x03, 0x04, 0x05 ), FCML_MI( 0x48, 0x81, 0x8f, 0x01, 0x02, 0x03, 0x04, 0x05, 0x00, 0x00, 0x00 ) );
    FCML_I64_M( "or qword ptr [rdi+0000000004030201h],0ffffffffffffffffh", 2, FCML_MI( 0x48, 0x83, 0x8f, 0x01, 0x02, 0x03, 0x04, 0xff ), FCML_MI( 0x48, 0x81, 0x8f, 0x01, 0x02, 0x03, 0x04, 0xff, 0xff, 0xff, 0xff ) );
    // 08 /r OR r/m8, r8 MR Valid Valid r/m8 OR r8.
    // REX + 08 /r OR r/m8*, r8* MR Valid N.E. r/m8 OR r8.
    FCML_I32( "lock or byte ptr [ebp+04030201h],ah", 0xF0, 0x08, 0xa5, 0x01, 0x02, 0x03, 04 );
    FCML_I32( "xacquire lock or byte ptr [ebp+04030201h],ah", 0xF2, 0xF0, 0x08, 0xa5, 0x01, 0x02, 0x03, 04 );
    FCML_I32( "xrelease lock or byte ptr [ebp+04030201h],ah", 0xF3, 0xF0, 0x08, 0xa5, 0x01, 0x02, 0x03, 04 );
    FCML_I64( "or byte ptr [rbp+0000000004030201h],spl", 0x40, 0x08, 0xa5, 0x01, 0x02, 0x03, 0x04 );
    FCML_I64( "or byte ptr [rbp+0000000000000001h],spl", 0x40, 0x08, 0x65, 0x01 );
    // 09 /r OR r/m16, r16 MR Valid Valid r/m16 OR r16.
    // 09 /r OR r/m32, r32 MR Valid Valid r/m32 OR r32.
    // REX.W + 09 /r OR r/m64, r64 MR Valid N.E. r/m64 OR r64.
    FCML_I32( "lock or dword ptr [ebp+04030201h],esp", 0xF0, 0x09, 0xa5, 0x01, 0x02, 0x03, 04 );
    FCML_I32( "xacquire lock or dword ptr [ebp+04030201h],esp", 0xF2, 0xF0, 0x09, 0xa5, 0x01, 0x02, 0x03, 04 );
    FCML_I32( "xrelease lock or dword ptr [ebp+04030201h],esp", 0xF3, 0xF0, 0x09, 0xa5, 0x01, 0x02, 0x03, 04 );
    FCML_I32( "or word ptr [di+0201h],sp", 0x66, 0x67, 0x09, 0xa5, 0x01, 0x02 );
    FCML_I32( "or dword ptr [di+0201h],esp", 0x67, 0x09, 0xa5, 0x01, 0x02 );
    FCML_I64( "or qword ptr [r9+rcx*4+0000000000000001h],r12", 0x4D, 0x09, 0x64, 0x89, 0x01 );
    // 0A /r OR r8, r/m8 RM Valid Valid r8 OR r/m8.
    // REX + 0A /r OR r8*, r/m8* RM Valid N.E. r8 OR r/m8.
    FCML_I32( "or ah,byte ptr [ebp+04030201h]", 0x0a, 0xa5, 0x01, 0x02, 0x03, 04 );
    FCML_I64( "or spl,byte ptr [rbp+0000000004030201h]", 0x40, 0x0a, 0xa5, 0x01, 0x02, 0x03, 0x04 );
    FCML_I64( "or spl,byte ptr [rbp+0000000000000001h]", 0x40, 0x0a, 0x65, 0x01 );
    // 0B /r OR r16, r/m16 RM Valid Valid r16 OR r/m16.
    // 0B /r OR r32, r/m32 RM Valid Valid r32 OR r/m32.
    // REX.W + 0B /r OR r64, r/m64 RM Valid N.E. r64 OR r/m64.
    FCML_I32( "or esp,dword ptr [ebp+04030201h]", 0x0b, 0xa5, 0x01, 0x02, 0x03, 04 );
    FCML_I32( "or sp,word ptr [di+0201h]", 0x66, 0x67, 0x0b, 0xa5, 0x01, 0x02 );
    FCML_I32( "or esp,dword ptr [di+0201h]", 0x67, 0x0b, 0xa5, 0x01, 0x02 );
    FCML_I64( "or r12,qword ptr [r9+rcx*4+0000000000000001h]", 0x4D, 0x0b, 0x64, 0x89, 0x01 );
    // GAS
    FCML_A32_M( "or $0x42806521,%eax", 2, FCML_MI( 0x81, 0xc8, 0x21, 0x65, 0x80, 0x42 ), FCML_MI( 0x0d, 0x21, 0x65, 0x80, 0x42 ) );
	FCML_A64_M( "or $0x0000000042806521,%rax", 2, FCML_MI( 0x48, 0x81, 0xc8, 0x21, 0x65, 0x80, 0x42 ), FCML_MI( 0x48, 0x0d, 0x21, 0x65, 0x80, 0x42 ) )
	FCML_A64_M( "or $0x6521,%ax", 2, FCML_MI( 0x66, 0x81, 0xc8, 0x21, 0x65 ), FCML_MI( 0x66, 0x0d, 0x21, 0x65 ) );
	FCML_A32( "lock orb $0xff,0x04030201", 0xF0, 0x80, 0x0d, 0x01, 0x02, 0x03, 0x04, 0xff );
	FCML_A32( "xacquire lock orb $0xff,0x04030201", 0xF2, 0xF0, 0x80, 0x0d, 0x01, 0x02, 0x03, 0x04, 0xff );
	FCML_A64_M( "or $0x42,%al", 2, FCML_MI( 0x80, 0xc8, 0x42 ), FCML_MI( 0x0c, 0x42 ) );
	FCML_A64( "lock orb $0xff,0x04030201(%rip)", 0xf0, 0x80, 0x0d, 0x01, 0x02, 0x03, 0x04, 0xff );
	FCML_A64_M( "lock orl $0x00000001,(%rsi)", 2, FCML_MI( 0xf0, 0x83, 0x0e, 0x01 ), FCML_MI( 0xf0, 0x81, 0x0e, 0x01, 0x00, 0x00, 0x00 ) );
	FCML_A64_M( "lock orw $0x0001,(%rsi)", 2, FCML_MI( 0xf0, 0x66, 0x83, 0x0e, 0x01 ), FCML_MI( 0xf0, 0x66, 0x81, 0x0e, 0x01, 0x00 ) );
	FCML_A64( "or 0x0000000000000001(%r9,%rcx,4),%r12", 0x4d, 0x0b, 0x64, 0x89, 0x01 );
	FCML_A64_M( "orq $0xffffffffffffffff,0x0000000004030201(%rdi)", 2, FCML_MI( 0x48, 0x83, 0x8f, 0x01, 0x02, 0x03, 0x04, 0xff ), FCML_MI( 0x48, 0x81, 0x8f, 0x01, 0x02, 0x03, 0x04, 0xff, 0xff, 0xff, 0xff ) );
}

void fcml_tf_instruction_ORPD(void) {
    // 66 0F 56 /r ORPD xmm1,xmm2/m128
    FCML_I32( "orpd xmm2,xmmword ptr [eax]", 0x66, 0x0F, 0x56, 0x10 );
    FCML_I32( "orpd xmm3,xmm0", 0x66, 0x0F, 0x56, 0xD8 );
    FCML_I64( "orpd xmm2,xmmword ptr [rax]", 0x66, 0x0F, 0x56, 0x10 );
    // VEX.NDS.128.66.0F 56 /r VORPD xmm1,xmm2,xmm3/m128
    // VEX.NDS.256.66.0F 56 /r VORPD ymm1,ymm2,ymm3/m256
    FCML_I64( "vorpd xmm3,xmm1,xmm0", 0xc5, 0xf1, 0x56, 0xd8 );
    FCML_I32( "vorpd ymm3,ymm0,ymm0", 0xc5, 0xfd, 0x56, 0xd8 );
    FCML_I32( "vorpd ymm3,ymm3,ymmword ptr [eax]", 0xc5, 0xe5, 0x56, 0x18 );
    // GAS
    FCML_A64( "orpd (%rax),%xmm2", 0x66, 0x0f, 0x56, 0x10 );
    FCML_A64( "orpd %xmm0,%xmm3", 0x66, 0x0f, 0x56, 0xd8 );
    FCML_A64( "vorpd %xmm0,%xmm1,%xmm3", 0xc5, 0xf1, 0x56, 0xd8 );
    FCML_A64( "vorpd (%rax),%ymm3,%ymm3", 0xc5, 0xe5, 0x56, 0x18 );
}

void fcml_tf_instruction_ORPS(void) {
    // 0F 56 /r ORPS xmm1, xmm2/m128
    FCML_I32( "orps xmm2,xmmword ptr [eax]", 0x0F, 0x56, 0x10 );
    FCML_I32( "orps xmm3,xmm0", 0x0F, 0x56, 0xD8 );
    FCML_I64( "orps xmm2,xmmword ptr [rax]", 0x0F, 0x56, 0x10 );
    // VEX.NDS.128.0F 56 /r VORPS xmm1,xmm2,xmm3/m128
    // VEX.NDS.256.0F 56 /r VORPS ymm1,ymm2,ymm3/m256
    FCML_I64( "vorps xmm3,xmm1,xmm0", 0xc5, 0xf0, 0x56, 0xd8 );
    FCML_I32( "vorps ymm3,ymm0,ymm0", 0xc5, 0xfc, 0x56, 0xd8 );
    FCML_I32( "vorps ymm3,ymm3,ymmword ptr [eax]", 0xc5, 0xe4, 0x56, 0x18 );
    // GAS
    FCML_A64( "orps (%rax),%xmm2", 0x0f, 0x56, 0x10 );
    FCML_A64( "orps %xmm0,%xmm3", 0x0f, 0x56, 0xd8 );
    FCML_A64( "vorps %ymm0,%ymm0,%ymm3", 0xc5, 0xfc, 0x56, 0xd8 );
    FCML_A64( "vorps (%rax),%ymm3,%ymm3", 0xc5, 0xe4, 0x56, 0x18 );
}

void fcml_tf_instruction_OUT(void) {
    // E6 ib OUT imm8, AL I Valid Valid Output byte in AL to I/O port address imm8.
    // E7 ib OUT imm8, AX I Valid Valid Output word in AX to I/O port address imm8.
    // E7 ib OUT imm8, EAX I Valid Valid Output doubleword in EAX to I/O port address imm8.
    FCML_I64( "out 20h,al", 0x66, 0xE6, 0x20 );
    FCML_I32( "out 20h,eax", 0xE7, 0x20 );
    FCML_I32( "out 20h,ax", 0x66, 0xE7, 0x20 );
    FCML_I64_D( "out 20h,eax", 0x48, 0xE7, 0x20 );
    FCML_I64( "out 20h,eax", 0xE7, 0x20 );
    // EE OUT DX, AL NP Valid Valid Output byte in AL to I/O port address in DX.
    // EF OUT DX, AX NP Valid Valid Output word in AX to I/O port address in DX.
    // EF OUT DX, EAX NP Valid Valid Output doubleword in EAX to I/O port address in DX.
    FCML_I32( "out dx,al", 0xEE );
    FCML_I64( "out dx,al", 0x66, 0xEE );
    FCML_I32( "out dx,eax", 0xEF );
    FCML_I32( "out dx,ax", 0x66, 0xEF );
    FCML_I64_D( "out dx,eax", 0x48, 0xEF );
    FCML_I64( "out dx,eax", 0xEF );
    // GAS
    // TODO: Gas troche inaczej disassembluje z nawiasami, mozna pomyslec czy nie zrpbowac dodac opcji takiej.
    FCML_A64( "out %al,$0x20", 0xe6, 0x20 );
    FCML_A64( "out %eax,$0x20", 0xe7, 0x20 );
    FCML_A64( "out %al,%dx", 0xee );
    FCML_A64( "out %ax,%dx", 0x66, 0xef );
}

void fcml_tf_instruction_OUTS(void) {

	// Rep rendering.
	FCML_I32_D_RF( "repe outs dx,byte ptr [esi]", FCML_REND_FLAG_REP_PREFIX_GROUP_1, 0xF3, 0x6e );
	FCML_I32_D_RF( "repz outs dx,byte ptr [esi]", FCML_REND_FLAG_REP_PREFIX_GROUP_2, 0xF3, 0x6e );

    // 6E OUTS DX, m8 NP Valid Valid Output byte from memory location specified in DS:(E)SI or RSI to I/O port specified in DX.
    FCML_I32( "outs dx,byte ptr [esi]", 0x6e );
    FCML_I32( "rep outs dx,byte ptr [esi]", 0xF3, 0x6e );
    FCML_I32_A( "repz outs dx,byte ptr [esi]", 0xF3, 0x6e );
    FCML_I32_A( "repe outs dx,byte ptr [esi]", 0xF3, 0x6e );
    FCML_I64( "outs dx,byte ptr [rsi]", 0x6e );
    FCML_I64_D( "outs dx,byte ptr [esi]", 0x67, 0x6e );
    FCML_I64_A( "outsb", 0x6e );
    // 6F OUTS DX, m16 NP Valid Valid Output word from memory location specified in DS:(E)SI or RSI to I/O port specified in DX.
    // 6F OUTS DX, m32 NP Valid Valid Output doubleword from memory location specified in DS:(E)SI or RSI to I/O port specified in DX.
    FCML_I32( "outs dx,dword ptr [esi]", 0x6f );
    FCML_I64( "outs dx,dword ptr [rsi]", 0x6f );
    FCML_I64( "outs dx,dword ptr [esi]", 0x67, 0x6f );
    FCML_I64( "outs dx,word ptr [esi]", 0x66, 0x67, 0x6f );
    FCML_I64_A( "outsw", 0x66, 0x6f );
    FCML_I64_D( "outs dx,dword ptr [rsi]", 0x48, 0x6f );
    FCML_I64( "outs dx,dword ptr [rsi]", 0x6f );
    FCML_I64_A( "outsd", 0x6f );
    // GAS
    FCML_A64( "outsb (%rsi),%dx", 0x6e );
    FCML_A64( "outsb (%esi),%dx", 0x67, 0x6e );
    FCML_A64( "outsl (%rsi),%dx", 0x6f );
    FCML_A64( "outsl (%esi),%dx", 0x67, 0x6f );
    FCML_A64( "outsw (%esi),%dx", 0x66, 0x67, 0x6f );
}

CU_TestInfo fctl_ti_instructions_o[] = {
    { "fcml_tf_instruction_OR", fcml_tf_instruction_OR },
    { "fcml_tf_instruction_ORPD", fcml_tf_instruction_ORPD },
    { "fcml_tf_instruction_ORPS", fcml_tf_instruction_ORPS },
    { "fcml_tf_instruction_OUT", fcml_tf_instruction_OUT },
    { "fcml_tf_instruction_OUTS", fcml_tf_instruction_OUTS },
    CU_TEST_INFO_NULL,
};

CU_SuiteInfo fctl_si_instructions_o[] = {
    { "suite-fctl_ti_instructions_o", fcml_tf_instructions_o_suite_init, fcml_tf_instructions_o_suite_cleanup, fctl_ti_instructions_o },
    CU_SUITE_INFO_NULL,
};
