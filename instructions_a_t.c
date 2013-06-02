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

/*
 * // ADC
	_TEST32( "801501020304ff adc byte ptr [04030201h],0ffh", 0x80, 0x15, 0x01, 0x02, 0x03, 0x04, 0xff );
	// 14 ib ADC AL, imm8 C Valid Valid Add with carry imm8 to AL.
	_TEST32( "1442 adc al,42h", 0x14, 0x42 );
	_TEST32( "1400 adc al,00h", 0x14, 0x00 );
	_TEST32( "14ff adc al,0ffh", 0x14, 0xff );
	_TEST64( "1442 adc al,42h", 0x14, 0x42 );
	_TEST64( "1400 adc al,00h", 0x14, 0x00 );
	_TEST64( "14ff adc al,0ffh", 0x14, 0xff );
	// 15 iw ADC AX, imm16 C Valid Valid Add with carry imm16 to AX.
	// 15 id ADC EAX, imm32 C Valid Valid Add with carry imm32 to EAX.
	_TEST32( "66154280 adc ax,8042h", 0x66, 0x15, 0x42, 0x80 );
	_TEST32( "1521658042 adc eax,42806521h", 0x15, 0x21, 0x65, 0x80, 0x42 );
	_TEST64( "401521658042 adc eax,42806521h", 0x40, 0x15, 0x21, 0x65, 0x80, 0x42 );
	_TEST64( "6640152165 adc ax,6521h", 0x66, 0x40, 0x15, 0x21, 0x65, 0x80, 0x42 );
	// REX.W + 15 id ADC RAX, imm32 C Valid N.E. Add with carry imm32 sign extended to 64-bits to RAX.
	_TEST64( "481521658042 adc rax,0000000042806521h", 0x48, 0x15, 0x21, 0x65, 0x80, 0x42 );
	_TEST64( "66481521658042 adc rax,0000000042806521h", 0x66, 0x48, 0x15, 0x21, 0x65, 0x80, 0x42 );
	_TEST64( "6766481521658042 adc rax,0000000042806521h", 0x67, 0x66, 0x48, 0x15, 0x21, 0x65, 0x80, 0x42 );
	_TEST64( "67664815ffffffff adc rax,0ffffffffffffffffh", 0x67, 0x66, 0x48, 0x15, 0xff, 0xff, 0xff, 0xff );
	// 80 /2 ib ADC r/m8, imm8 B Valid Valid Add with carry imm8 to r/m8.
	// REX + 80 /2 ib ADC r/m8*, imm8 B Valid N.E. Add with carry imm8 to r/m8.
	_TEST32( "801501020304ff adc byte ptr [04030201h],0ffh", 0x80, 0x15, 0x01, 0x02, 0x03, 0x04, 0xff );
	_TEST32( "809601020304ff adc byte ptr [esi+04030201h],0ffh", 0x80, 0x96, 0x01, 0x02, 0x03, 0x04, 0xff, 0x00, 0x00 );
	_TEST32( "8054010203 adc byte ptr [ecx+eax+00000002h],03h", 0x80, 0x54, 0x01, 0x02, 0x03 );
	// 81 /2 iw ADC r/m16, imm16 B Valid Valid Add with carry imm16 to r/m16.
	// 81 /2 id ADC r/m32, imm32 B Valid Valid Add with CF imm32 to r/m32.
	_TEST32( "81d501020304 adc ebp,04030201h", 0x81, 0xD5, 0x01, 0x02, 0x03, 0x04 );
	_TEST32( "6681d50102 adc bp,0201h", 0x66, 0x81, 0xD5, 0x01, 0x02 );
	_TEST64( "67664081d50102 adc bp,0201h", 0x67, 0x66, 0x40, 0x81, 0xD5, 0x01, 0x02 ); // 32 bit mode doesn't not allow REX.
	// REX.W + 81 /2 id ADC r/m64, imm32 B Valid N.E. Add with CF imm32 sign extended to 64-bits to r/m64.
	_TEST64( "4881d501020304 adc rbp,0000000004030201h", 0x48, 0x81, 0xD5, 0x01, 0x02, 0x03, 0x04 );
	_TEST64( "4881d5ffffffff adc rbp,0ffffffffffffffffh", 0x48, 0x81, 0xD5, 0xff, 0xff, 0xff, 0xff );
	_TEST64( "674881d5ffffffff adc rbp,0ffffffffffffffffh", 0x67, 0x48, 0x81, 0xD5, 0xff, 0xff, 0xff, 0xff );
	_TEST64( "664881d5ffffffff adc rbp,0ffffffffffffffffh", 0x66, 0x48, 0x81, 0xD5, 0xff, 0xff, 0xff, 0xff );
	// 83 /2 ib ADC r/m16, imm8 B Valid Valid Add with CF sign-extended imm8 to r/m16.
	// 83 /2 ib ADC r/m32, imm8 B Valid Valid Add with CF sign-extended imm8 into r/m32.
	_TEST32( "831601 adc dword ptr [esi],00000001h", 0x83, 0x16, 0x01, 0x02, 0x03, 0x04 );
	_TEST32( "66831601 adc word ptr [esi],0001h", 0x66, 0x83, 0x16, 0x01, 0x02, 0x03, 0x04 );
	_TEST32( "678316010203 adc dword ptr [0201h],00000003h", 0x67, 0x83, 0x16, 0x01, 0x02, 0x03 );
	// REX.W + 83 /2 ib ADC r/m64, imm8 B Valid N.E. Add with CF sign-extended imm8 into r/m64.
	_TEST64( "4883970102030405 adc qword ptr [rdi+0000000004030201h],0000000000000005h", 0x48, 0x83, 0x97, 0x01, 0x02, 0x03, 0x4, 0x05 );
	_TEST64( "48839701020304ff adc qword ptr [rdi+0000000004030201h],0ffffffffffffffffh", 0x48, 0x83, 0x97, 0x01, 0x02, 0x03, 0x4, 0xff );
	// 10 /r ADC r/m8, r8 A Valid Valid Add with carry byte register to r/m8.
	// REX + 10 /r ADC r/m8*, r8* A Valid N.E. Add with carry byte register to r/m64.
	_TEST32( "10a501020304 adc byte ptr [ebp+04030201h],ah", 0x10, 0xa5, 0x01, 0x02, 0x03, 04 );
	_TEST64( "4810a501020304 adc byte ptr [rbp+0000000004030201h],spl", 0x48, 0x10, 0xa5, 0x01, 0x02, 0x03, 04 );
	_TEST64( "481064a501 adc byte ptr [rbp+0000000000000001h],spl", 0x48, 0x10, 0x64, 0xa5, 0x01, 0x02, 0x03, 04 );
	// 11 /r ADC r/m16, r16 A Valid Valid Add with carry r16 to r/m16.
	// 11 /r ADC r/m32, r32 A Valid Valid Add with CF r32 to r/m32.
	// REX.W + 11 /r ADC r/m64, r64 A Valid N.E. Add with CF r64 to r/m64.
	_TEST32( "11a501020304 adc dword ptr [ebp+04030201h],esp", 0x11, 0xa5, 0x01, 0x02, 0x03, 04 );
	_TEST32( "676611a50102 adc word ptr [di+0201h],sp", 0x67, 0x66, 0x11, 0xa5, 0x01, 0x02 );
	_TEST32( "6711a50102 adc dword ptr [di+0201h],esp", 0x67, 0x11, 0xa5, 0x01, 0x02 );
	_TEST64( "4d11648901 adc qword ptr [r9+rcx*4+0000000000000001h],r12", 0x4D, 0x11, 0x64, 0x89, 0x01 );
	// 12 /r ADC r8, r/m8 A Valid Valid Add with carry r/m8 to byte register.
	// REX + 12 /r ADC r8*, r/m8* A Valid N.E. Add with carry r/m64 to byte register.
	_TEST32( "12a501020304 adc ah,byte ptr [ebp+04030201h]", 0x12, 0xa5, 0x01, 0x02, 0x03, 04 );
	_TEST64( "4812a501020304 adc spl,byte ptr [rbp+0000000004030201h]", 0x48, 0x12, 0xa5, 0x01, 0x02, 0x03, 04 );
	_TEST64( "481264a501 adc spl,byte ptr [rbp+0000000000000001h]", 0x48, 0x12, 0x64, 0xa5, 0x01, 0x02, 0x03, 04 );
	// 13 /r ADC r16, r/m16 A Valid Valid Add with carry r/m16 to r16.
	// 13 /r ADC r32, r/m32 A Valid Valid Add with CF r/m32 to r32.
	// REX.W + 13 /r ADC r64, r/m64 A Valid N.E. Add with CF r/m64 to r64.
	_TEST32( "13a501020304 adc esp,dword ptr [ebp+04030201h]", 0x13, 0xa5, 0x01, 0x02, 0x03, 04 );
	_TEST32( "676613a50102 adc sp,word ptr [di+0201h]", 0x67, 0x66, 0x13, 0xa5, 0x01, 0x02 );
	_TEST32( "6713a50102 adc esp,dword ptr [di+0201h]", 0x67, 0x13, 0xa5, 0x01, 0x02 );
	_TEST64( "4d13648901 adc r12,qword ptr [r9+rcx*4+0000000000000001h]", 0x4D, 0x13, 0x64, 0x89, 0x01 );
 */



void fcml_tf_instruction_ADC(void) {
	// 14 ib ADC AL, imm8
	FCML_I3264( "adc al,42h", 0x14, 0x42 );
	FCML_I3264( "adc al,0ffh", 0x14, 0xFF );
	FCML_I3264( "adc al,00h", 0x14, 0x00 );
	// 15 iw ADC AX, imm16
	// 15 id ADC EAX, imm32
	FCML_I3264( "adc ax,8042h",  0x66, 0x15, 0x42, 0x80 );
}

CU_TestInfo fctl_ti_instructions_a[] = {
    { "fcml_tf_instruction_AAA", fcml_tf_instruction_AAA },
    { "fcml_tf_instruction_AAD", fcml_tf_instruction_AAD },
    { "fcml_tf_instruction_AAM", fcml_tf_instruction_AAM },
    { "fcml_tf_instruction_AAS", fcml_tf_instruction_AAS },
    { "fcml_tf_instruction_ADC", fcml_tf_instruction_ADC },
    CU_TEST_INFO_NULL,
};

CU_SuiteInfo fctl_si_instructions_a[] = {
    { "suite-fctl_ti_instructions_a", fcml_tf_instructions_a_suite_init, fcml_tf_instructions_a_suite_cleanup, fctl_ti_instructions_a },
    CU_SUITE_INFO_NULL,
};
