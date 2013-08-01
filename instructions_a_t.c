/*
 * instructions.c
 *
 *  Created on: 01-06-2013
 *      Author: tAs
 */

#include "fcml_env.h"
#include "fcml_assembler.h"
#include "instructions_a_t.h"

int fcml_tf_instructions_a_suite_init(void) {
	return 0;
}

int fcml_tf_instructions_a_suite_cleanup(void) {
	return 0;
}

void fcml_tf_instruction_AAA(void) {
	FCML_I32( "aaa", 0x37 );
}

void fcml_tf_instruction_AAD(void) {
	FCML_I32( "aad", 0xD5, 0x0A );
	FCML_I64_FAILED( "aad", 0xD5, 0x0A );
	FCML_I32( "aad 0ch", 0xD5, 0x0C );
	FCML_I64_FAILED( "aad 0ch", 0xD5, 0x0C );
}

void fcml_tf_instruction_AAM(void) {
	FCML_I32( "aam", 0xD4, 0x0A );
	FCML_I64_FAILED( "aam", 0xD4, 0x0A );
	FCML_I32( "aam 0ch", 0xD4, 0x0C );
	FCML_I64_FAILED( "aam 0ch", 0xD4, 0x0C );
}

void fcml_tf_instruction_AAS(void) {
	FCML_I32( "aas", 0x3F );
	FCML_I64_FAILED( "aas", 0x3F );
}

void fcml_tf_instruction_ADC(void) {
	// 14 ib ADC AL, imm8
	FCML_I3264( "adc al,42h", 0x14, 0x42 );
	FCML_I3264( "adc al,0ffh", 0x14, 0xFF );
	FCML_I3264( "adc al,00h", 0x14, 0x00 );
	// 15 iw ADC AX, imm16s
	// 15 id ADC EAX, imm32
	FCML_I3264( "adc ax,8042h",  0x66, 0x15, 0x42, 0x80 );
	FCML_I3264( "adc eax,42806521h", 0x15, 0x21, 0x65, 0x80, 0x42 );
	FCML_I64_D( "adc eax,42806521h", 0x40, 0x15, 0x21, 0x65, 0x80, 0x42 );
	FCML_I64_D( "adc ax,6521h", 0x66, 0x40, 0x15, 0x21, 0x65 );
	// REX.W + 15 id ADC RAX, imm32
	FCML_I64( "adc rax,0000000042806521h", 0x48, 0x15, 0x21, 0x65, 0x80, 0x42 );
	FCML_I64_D( "adc rax,0000000042806521h", 0x66, 0x48, 0x15, 0x21, 0x65, 0x80, 0x42 );
	FCML_I64_D( "adc rax,0000000042806521h", 0x67, 0x66, 0x48, 0x15, 0x21, 0x65, 0x80, 0x42 );
	FCML_I64_D( "adc rax,0ffffffffffffffffh", 0x67, 0x66, 0x48, 0x15, 0xff, 0xff, 0xff, 0xff );
	// 80 /2 ib ADC r/m8, imm8
	// REX + 80 /2 ib ADC r/m8
	FCML_I32( "adc byte ptr [04030201h],0ffh", 0x80, 0x15, 0x01, 0x02, 0x03, 0x04, 0xff );
	FCML_I32( "adc byte ptr [esi+04030201h],0ffh", 0x80, 0x96, 0x01, 0x02, 0x03, 0x04, 0xff );
	FCML_I32( "adc byte ptr [ecx+eax+00000002h],03h", 0x80, 0x54, 0x01, 0x02, 0x03 );
	// 81 /2 iw ADC r/m16, imm16
	// 81 /2 id ADC r/m32, imm32
	FCML_I3264( "adc ebp,04030201h", 0x81, 0xD5, 0x01, 0x02, 0x03, 0x04 );
	FCML_I3264( "adc bp,0201h", 0x66, 0x81, 0xD5, 0x01, 0x02 );
	FCML_I64_D( "adc bp,0201h", 0x67, 0x66, 0x40, 0x81, 0xD5, 0x01, 0x02 );
	// REX.W + 81 /2 id ADC r/m64, imm32 B Valid N.E. Add with CF imm32 sign extended to 64-bits to r/m64.
	FCML_I64( "adc rbp,0000000004030201h", 0x48, 0x81, 0xD5, 0x01, 0x02, 0x03, 0x04 );
	FCML_I64( "adc rbp,0ffffffffffffffffh", 0x48, 0x81, 0xD5, 0xff, 0xff, 0xff, 0xff );
	FCML_I64_D( "adc rbp,0ffffffffffffffffh", 0x67, 0x48, 0x81, 0xD5, 0xff, 0xff, 0xff, 0xff );
	FCML_I64_D( "adc rbp,0ffffffffffffffffh", 0x66, 0x48, 0x81, 0xD5, 0xff, 0xff, 0xff, 0xff );
	// 83 /2 ib ADC r/m16, imm8 B Valid Valid Add with CF sign-extended imm8 to r/m16.
	// 83 /2 ib ADC r/m32, imm8 B Valid Valid Add with CF sign-extended imm8 into r/m32.
	FCML_I32( "adc dword ptr [esi],00000001h", 0x83, 0x16, 0x01 );
	FCML_I32( "adc word ptr [esi],0001h", 0x66, 0x83, 0x16, 0x01 );
	FCML_I64( "adc word ptr [rsi],0001h", 0x66, 0x83, 0x16, 0x01 );
	FCML_I32( "adc dword ptr [0201h],00000003h", 0x67, 0x83, 0x16, 0x01, 0x02, 0x03 );
	FCML_I32( "adc word ptr [0201h],0ffffh", 0x66, 0x67, 0x83, 0x16, 0x01, 0x02, 0xFF );
	FCML_I32( "adc dword ptr [0201h],00000003h", 0x67, 0x83, 0x16, 0x01, 0x02, 0x03 );
	FCML_I64_RIP( "adc dword ptr [0000800000401007h],00000003h", 0x83, 0x15, 0x00, 0x00, 0x00, 0x00, 0x03 );
	// REX.W + 83 /2 ib ADC r/m64, imm8 B Valid N.E. Add with CF sign-extended imm8 into r/m64.
	FCML_I64( "adc qword ptr [rdi+0000000004030201h],0000000000000005h", 0x48, 0x83, 0x97, 0x01, 0x02, 0x03, 0x4, 0x05 );
	FCML_I64( "adc qword ptr [rdi+0000000004030201h],0ffffffffffffffffh", 0x48, 0x83, 0x97, 0x01, 0x02, 0x03, 0x4, 0xff );
	// 10 /r ADC r/m8, r8 A Valid Valid Add with carry byte register to r/m8.
	// REX + 10 /r ADC r/m8*, r8* A Valid N.E. Add with carry byte register to r/m64.
	FCML_I32( "adc byte ptr [ebp+04030201h],ah", 0x10, 0xa5, 0x01, 0x02, 0x03, 04 );
	FCML_I64( "adc byte ptr [rbp+0000000000000001h],ah", 0x10, 0x65, 0x01 );
	FCML_I64( "adc byte ptr [rbp+0000000000000001h],spl", 0x40, 0x10, 0x65, 0x01 );
	FCML_I64( "adc byte ptr [rbp+0000000000000001h],r12l", 0x44, 0x10, 0x65, 0x01 );
	FCML_I64_D( "adc byte ptr [rbp+0000000000000001h],spl", 0x48, 0x10, 0x64, 0xa5, 0x01 );
	FCML_I64_D( "adc byte ptr [rbp+0000000000000001h],spl", 0x40, 0x10, 0x64, 0xa5, 0x01 );
	FCML_I64_D( "adc byte ptr [rbp+0000000000000001h],ah", 0x10, 0x64, 0xa5, 0x01 );
	// 11 /r ADC r/m16, r16 A Valid Valid Add with carry r16 to r/m16.
	// 11 /r ADC r/m32, r32 A Valid Valid Add with CF r32 to r/m32.
	// REX.W + 11 /r ADC r/m64, r64 A Valid N.E. Add with CF r64 to r/m64.
	FCML_I32( "adc dword ptr [ebp+04030201h],esp", 0x11, 0xa5, 0x01, 0x02, 0x03, 04 );
	FCML_I32( "adc word ptr [di+0201h],sp", 0x66, 0x67, 0x11, 0xa5, 0x01, 0x02 );
	FCML_I32( "adc dword ptr [di+0201h],esp", 0x67, 0x11, 0xa5, 0x01, 0x02 );
	FCML_I64( "adc qword ptr [r9+rcx*4+0000000000000001h],r12", 0x4D, 0x11, 0x64, 0x89, 0x01 );
	// 12 /r ADC r8, r/m8 A Valid Valid Add with carry r/m8 to byte register.
	// REX + 12 /r ADC r8*, r/m8* A Valid N.E. Add with carry r/m64 to byte register.
	FCML_I32( "adc ah,byte ptr [ebp+04030201h]", 0x12, 0xa5, 0x01, 0x02, 0x03, 04 );
	FCML_I64_D( "adc spl,byte ptr [rbp+0000000004030201h]", 0x48, 0x12, 0xa5, 0x01, 0x02, 0x03, 04 );
	FCML_I64_D( "adc spl,byte ptr [rbp+0000000000000001h]", 0x48, 0x12, 0x64, 0xa5, 0x01 );
	FCML_I64_D( "adc ah,byte ptr [rbp+0000000000000001h]", 0x12, 0x64, 0xa5, 0x01 );
	FCML_I64( "adc spl,byte ptr [rbp+0000000004030201h]", 0x40, 0x12, 0xa5, 0x01, 0x02, 0x03, 04 );
	FCML_I64( "adc spl,byte ptr [rbp+0000000000000001h]", 0x40, 0x12, 0x65, 0x01 );
	// 13 /r ADC r16, r/m16 A Valid Valid Add with carry r/m16 to r16.
	// 13 /r ADC r32, r/m32 A Valid Valid Add with CF r/m32 to r32.
	// REX.W + 13 /r ADC r64, r/m64 A Valid N.E. Add with CF r/m64 to r64.
	FCML_I32( "adc esp,dword ptr [ebp+04030201h]", 0x13, 0xa5, 0x01, 0x02, 0x03, 04 );
	FCML_I32( "adc sp,word ptr [di+0201h]", 0x66, 0x67, 0x13, 0xa5, 0x01, 0x02 );
	FCML_I32( "adc esp,dword ptr [di+0201h]", 0x67, 0x13, 0xa5, 0x01, 0x02 );
	FCML_I64( "adc r12,qword ptr [r9+rcx*4+0000000000000001h]", 0x4D, 0x13, 0x64, 0x89, 0x01 );
}

void fcml_tf_instruction_ADD(void) {
	// 04 ib ADD AL, imm8 C Valid Valid Add imm8 to AL..
	FCML_I32( "add al,42h", 0x04, 0x42 );
	FCML_I32( "add al,0ffh", 0x04, 0xff );
	FCML_I64( "add al,42h", 0x04, 0x42 );
	FCML_I64( "add al,00h", 0x04, 0x00 );
	FCML_I64( "add al,0ffh", 0x04, 0xff );
	// 05 iw ADD AX, imm16 C Valid Valid Add imm16 to AX.
	// 05 id ADD EAX, imm32 C Valid Valid Add imm32 to EAX.
	FCML_I32( "add ax,8042h", 0x66, 0x05, 0x42, 0x80 );
	FCML_I32( "add eax,42806521h", 0x05, 0x21, 0x65, 0x80, 0x42 );
	FCML_I64_D( "add eax,42806521h", 0x40, 0x05, 0x21, 0x65, 0x80, 0x42 );
	FCML_I64( "add eax,42806521h", 0x05, 0x21, 0x65, 0x80, 0x42 );
	FCML_I64_D( "add ax,6521h", 0x66, 0x40, 0x05, 0x21, 0x65 );
	FCML_I64( "add ax,6521h", 0x66, 0x05, 0x21, 0x65 );
	// REX.W + 05 id ADD RAX, imm32 C Valid N.E. Add imm32 sign-extended to 64-bits to RAX.
	FCML_I64_D( "add rax,0000000042806521h", 0x48, 0x05, 0x21, 0x65, 0x80, 0x42 );
	FCML_I64_D( "add rax,0000000042806521h", 0x66, 0x48, 0x05, 0x21, 0x65, 0x80, 0x42 );
	FCML_I64_D( "add rax,0000000042806521h", 0x67, 0x66, 0x48, 0x05, 0x21, 0x65, 0x80, 0x42 );
	FCML_I64_D( "add rax,0ffffffffffffffffh", 0x66, 0x67, 0x48, 0x05, 0xff, 0xff, 0xff, 0xff );
	FCML_I64( "add rax,0000000042806521h", 0x48, 0x05, 0x21, 0x65, 0x80, 0x42 );
	FCML_I64( "add rax,0ffffffffffffffffh", 0x48, 0x05, 0xff, 0xff, 0xff, 0xff );
	// 80 /0 ib ADD r/m8, imm8 B Valid Valid Add imm8 to r/m8.
	// REX + 80 /0 ib ADD r/m8*, imm8 B Valid N.E. Add sign-extended imm8 to r/m64.
	FCML_I32( "add byte ptr [04030201h],0ffh", 0x80, 0x05, 0x01, 0x02, 0x03, 0x04, 0xff );
	FCML_I32( "add byte ptr [esi+04030201h],0ffh", 0x80, 0x86, 0x01, 0x02, 0x03, 0x04, 0xff );
	FCML_I32( "add byte ptr [ecx+eax+00000002h],03h", 0x80, 0x44, 0x01, 0x02, 0x03 );
	FCML_I64( "add byte ptr [rcx+rax+0000000000000002h],03h", 0x80, 0x44, 0x01, 0x02, 0x03 );
	// 81 /0 iw ADD r/m16, imm16 B Valid Valid Add imm16 to r/m16.
	// 81 /0 id ADD r/m32, imm32 B Valid Valid Add imm32 to r/m32.
	FCML_I32( "add ebp,04030201h", 0x81, 0xc5, 0x01, 0x02, 0x03, 0x04 );
	FCML_I32( "add bp,0201h", 0x66, 0x81, 0xc5, 0x01, 0x02 );
	FCML_I64_D( "add bp,0201h", 0x67, 0x66, 0x40, 0x81, 0xc5, 0x01, 0x02 );
	FCML_I64( "add bp,0201h", 0x66, 0x67, 0x81, 0xc5, 0x01, 0x02 );
	// REX.W + 81 /0 id ADD r/m64, imm32 B Valid N.E. Add imm32 sign-extended to 64-bits to r/m64.
	FCML_I64_D( "add rbp,0000000004030201h", 0x48, 0x81, 0xc5, 0x01, 0x02, 0x03, 0x04 );
	FCML_I64_D( "add rbp,0ffffffffffffffffh", 0x48, 0x81, 0xc5, 0xff, 0xff, 0xff, 0xff );
	FCML_I64_D( "add rbp,0ffffffffffffffffh", 0x67, 0x48, 0x81, 0xc5, 0xff, 0xff, 0xff, 0xff );
	FCML_I64_D( "add rbp,0ffffffffffffffffh", 0x66, 0x48, 0x81, 0xc5, 0xff, 0xff, 0xff, 0xff );
	FCML_I64( "add rbp,0000000004030201h", 0x48, 0x81, 0xc5, 0x01, 0x02, 0x03, 0x04 );
	FCML_I64( "add rbp,0ffffffffffffffffh", 0x48, 0x81, 0xc5, 0xff, 0xff, 0xff, 0xff );
	// 83 /0 ib ADD r/m16, imm8 B Valid Valid Add sign-extended imm8 to r/m16.
	// 83 /0 ib ADD r/m32, imm8 B Valid Valid Add sign-extended imm8 to r/m32.
	FCML_I32( "add dword ptr [esi],00000001h", 0x83, 0x06, 0x01 );
	FCML_I32( "add word ptr [esi],0001h", 0x66, 0x83, 0x06, 0x01 );
	FCML_I32( "add dword ptr [0201h],00000003h", 0x67, 0x83, 0x06, 0x01, 0x02, 0x03 );
	// REX.W + 83 /0 ib ADD r/m64, imm8 B Valid N.E. Add sign-extended imm8 to r/m64.
	FCML_I64( "add qword ptr [rdi+0000000004030201h],0000000000000005h", 0x48, 0x83, 0x87, 0x01, 0x02, 0x03, 0x4, 0x05 );
	FCML_I64( "add qword ptr [rdi+0000000004030201h],0ffffffffffffffffh", 0x48, 0x83, 0x87, 0x01, 0x02, 0x03, 0x4, 0xff );
	// 00 /r ADD r/m8, r8 A Valid Valid Add r8 to r/m8.
	// REX + 00 /r ADD r/m8*, r8* A Valid N.E. Add r8 to r/m8.
	FCML_I32( "add byte ptr [ebp+04030201h],ah", 0x00, 0xa5, 0x01, 0x02, 0x03, 04 );
	FCML_I64( "add byte ptr [rbp+0000000004030201h],spl", 0x40, 0x00, 0xa5, 0x01, 0x02, 0x03, 04 );
	FCML_I64( "add byte ptr [rbp+0000000000000001h],spl", 0x40, 0x00, 0x65, 0x01 );
	// 01 /r ADD r/m16, r16 A Valid Valid Add r16 to r/m16.
	// 01 /r ADD r/m32, r32 A Valid Valid Add r32 to r/m32.
	// REX.W + 01 /r ADD r/m64, r64 A Valid N.E. Add r64 to r/m64.
	FCML_I32( "add dword ptr [ebp+04030201h],esp", 0x01, 0xa5, 0x01, 0x02, 0x03, 04 );
	FCML_I32( "add word ptr [di+0201h],sp", 0x66, 0x67, 0x01, 0xa5, 0x01, 0x02 );
	FCML_I32( "add dword ptr [di+0201h],esp", 0x67, 0x01, 0xa5, 0x01, 0x02 );
	FCML_I64( "add qword ptr [r9+rcx*4+0000000000000001h],r12", 0x4D, 0x01, 0x64, 0x89, 0x01 );
	// 02 /r ADD r8, r/m8 A Valid Valid Add r/m8 to r8.
	// REX + 02 /r ADD r8*, r/m8* A Valid N.E. Add r/m8 to r8.
	FCML_I32( "add ah,byte ptr [ebp+04030201h]", 0x02, 0xa5, 0x01, 0x02, 0x03, 04 );
	FCML_I64( "add spl,byte ptr [rbp+0000000004030201h]", 0x40, 0x02, 0xa5, 0x01, 0x02, 0x03, 04 );
	FCML_I64( "add spl,byte ptr [rbp+0000000000000001h]", 0x40, 0x02, 0x65, 0x01 );
	// 03 /r ADD r16, r/m16 A Valid Valid Add r/m16 to r16.
	// 03 /r ADD r32, r/m32 A Valid Valid Add r/m32 to r32.
	// REX.W + 03 /r ADD r64, r/m64 A Valid N.E. Add r/m64 to r64.
	FCML_I32( "add esp,dword ptr [ebp+04030201h]", 0x03, 0xa5, 0x01, 0x02, 0x03, 04 );
	FCML_I32( "add sp,word ptr [di+0201h]", 0x66, 0x67, 0x03, 0xa5, 0x01, 0x02 );
	FCML_I32( "add esp,dword ptr [di+0201h]", 0x67, 0x03, 0xa5, 0x01, 0x02 );
	FCML_I64( "add r12,qword ptr [r9+rcx*4+0000000000000001h]", 0x4D, 0x03, 0x64, 0x89, 0x01 );
}

void fcml_tf_instruction_ADDPD(void) {

	// 66 0F 58 /r ADDPD xmm1, xmm2/m128
	FCML_I32( "addpd xmm2,oword ptr [ecx+eax]", 0x66, 0x0F, 0x58, 0x14, 0x01 );
	FCML_I64( "addpd xmm2,oword ptr [rcx+rax]", 0x66, 0x0F, 0x58, 0x14, 0x01 );

	/*
	// ADDPD

	// VADDPD
	// VEX.NDS.128.66.0F 58 /r VADDPD xmm1,xmm2, xmm3/m128
	// VAX.X
	_TEST64_VEX( "c4010d581401 vaddpd ymm10,ymm14,ymmword ptr [r9+r8]", 0xC4, 0x01, 0x0D, 0x58, 0x14, 0x01 );
	// VAX.R VAX.B (3 byte VAX prefix.)
	_TEST64_VEX( "c4410d581401 vaddpd ymm10,ymm14,ymmword ptr [r9+rax]", 0xC4, 0x41, 0x0D, 0x58, 0x14, 0x01 );
	_TEST64_VEX( "c4c109581401 vaddpd xmm2,xmm14,oword ptr [r9+rax]", 0xC4, 0xC1, 0x09, 0x58, 0x14, 0x01 );
	_TEST32_VEX( "c4c169581401 vaddpd xmm2,xmm2,oword ptr [ecx+eax]", 0xC4, 0xC1, 0x69, 0x58, 0x14, 0x01 );
	// VAX.mmmm
	_TEST32_VEX( "c4c16d581401 vaddpd ymm2,ymm2,ymmword ptr [ecx+eax]", 0xC4, 0xC1, 0x6D, 0x58, 0x14, 0x01 );
	// VAX.L (0)
	_TEST32_VEX( "c5f9581401 vaddpd xmm2,xmm0,oword ptr [ecx+eax]", 0xC5, 0xF9, 0x58, 0x14, 0x01 );
	/// VAX.R (2 byte VAX prefix.)
	_TEST64_VEX( "c55d581401 vaddpd ymm10,ymm4,ymmword ptr [rcx+rax]", 0xC5, 0x5D, 0x58, 0x14, 0x01 );
	// VAX.vvvv, VAX.L(1), VAX.pp
	_TEST32_VEX( "c5fd581401 vaddpd ymm2,ymm0,ymmword ptr [ecx+eax]", 0xC5, 0xFD, 0x58, 0x14, 0x01 );
	*/

}

CU_TestInfo fctl_ti_instructions_a[] = {
    { "fcml_tf_instruction_AAA", fcml_tf_instruction_AAA },
    { "fcml_tf_instruction_AAD", fcml_tf_instruction_AAD },
    { "fcml_tf_instruction_AAM", fcml_tf_instruction_AAM },
    { "fcml_tf_instruction_AAS", fcml_tf_instruction_AAS },
    { "fcml_tf_instruction_ADC", fcml_tf_instruction_ADC },
    { "fcml_tf_instruction_ADD", fcml_tf_instruction_ADD },
    { "fcml_tf_instruction_ADDPD", fcml_tf_instruction_ADDPD },
    CU_TEST_INFO_NULL,
};

CU_SuiteInfo fctl_si_instructions_a[] = {
    { "suite-fctl_ti_instructions_a", fcml_tf_instructions_a_suite_init, fcml_tf_instructions_a_suite_cleanup, fctl_ti_instructions_a },
    CU_SUITE_INFO_NULL,
};
