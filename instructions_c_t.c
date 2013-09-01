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
   /* FCML_I32( "cmovo esp,dword ptr [ebp+04030201h]", 0x0f, 0x40, 0xa5, 0x01, 0x02, 0x03, 04 );
    FCML_I32( "cmovo sp,word ptr [di+0201h]", 0x67, 0x66, 0x0f, 0x40, 0xa5, 0x01, 0x02 );
    FCML_I32( "cmovo esp,dword ptr [di+0201h]", 0x67, 0x0f, 0x40, 0xa5, 0x01, 0x02 );
    FCML_I64( "cmovo r12,qword ptr [r9+rcx*4+0000000000000001h]", 0x4D, 0x0f, 0x40, 0x64, 0x89, 0x01 );
    FCML_I32( "cmovo esp,dword ptr [ebp+04030201h]", 0x0f, 0x40, 0xa5, 0x01, 0x02, 0x03, 04 );
    FCML_I32( "cmovno esp,dword ptr [ebp+04030201h]", 0x0f, 0x41, 0xa5, 0x01, 0x02, 0x03, 04 );
    FCML_I32( "cmovc esp,dword ptr [ebp+04030201h]", 0x0f, 0x42, 0xa5, 0x01, 0x02, 0x03, 04 );
    FCML_I32( "cmovnc esp,dword ptr [ebp+04030201h]", 0x0f, 0x43, 0xa5, 0x01, 0x02, 0x03, 04 );
    FCML_I32( "cmove esp,dword ptr [ebp+04030201h]", 0x0f, 0x44, 0xa5, 0x01, 0x02, 0x03, 04 );
    FCML_I32( "cmovne esp,dword ptr [ebp+04030201h]", 0x0f, 0x45, 0xa5, 0x01, 0x02, 0x03, 04 );
    FCML_I32( "cmovbe esp,dword ptr [ebp+04030201h]", 0x0f, 0x46, 0xa5, 0x01, 0x02, 0x03, 04 );
    FCML_I32( "cmovnbe esp,dword ptr [ebp+04030201h]", 0x0f, 0x47, 0xa5, 0x01, 0x02, 0x03, 04 );
    FCML_I32( "cmovs esp,dword ptr [ebp+04030201h]", 0x0f, 0x48, 0xa5, 0x01, 0x02, 0x03, 04 );
    FCML_I32( "cmovns esp,dword ptr [ebp+04030201h]", 0x0f, 0x49, 0xa5, 0x01, 0x02, 0x03, 04 );
    FCML_I32( "cmovp esp,dword ptr [ebp+04030201h]", 0x0f, 0x4a, 0xa5, 0x01, 0x02, 0x03, 04 );
    FCML_I32( "cmovnp esp,dword ptr [ebp+04030201h]", 0x0f, 0x4b, 0xa5, 0x01, 0x02, 0x03, 04 );
    FCML_I32( "cmovl esp,dword ptr [ebp+04030201h]", 0x0f, 0x4c, 0xa5, 0x01, 0x02, 0x03, 04 );
    FCML_I32( "cmovnl esp,dword ptr [ebp+04030201h]", 0x0f, 0x4d, 0xa5, 0x01, 0x02, 0x03, 04 );
    FCML_I32( "cmovle esp,dword ptr [ebp+04030201h]", 0x0f, 0x4e, 0xa5, 0x01, 0x02, 0x03, 04 );
    FCML_I32( "cmovnle esp,dword ptr [ebp+04030201h]", 0x0f, 0x4f, 0xa5, 0x01, 0x02, 0x03, 04 );*/
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
    CU_TEST_INFO_NULL,
};

CU_SuiteInfo fctl_si_instructions_c[] = {
    { "suite-fctl_ti_instructions_c", fcml_tf_instructions_c_suite_init, fcml_tf_instructions_c_suite_cleanup, fctl_ti_instructions_c },
    CU_SUITE_INFO_NULL,
};
