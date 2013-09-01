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

CU_TestInfo fctl_ti_instructions_c[] = {
    { "fcml_tf_instruction_CALL", fcml_tf_instruction_CALL },
    CU_TEST_INFO_NULL,
};

CU_SuiteInfo fctl_si_instructions_c[] = {
    { "suite-fctl_ti_instructions_c", fcml_tf_instructions_c_suite_init, fcml_tf_instructions_c_suite_cleanup, fctl_ti_instructions_c },
    CU_SUITE_INFO_NULL,
};
