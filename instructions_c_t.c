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

    /*



	// r/m32
	FCML_I32( "call dword ptr [edi+00000001h]", 0xFF, 0x57, 0x01 );
	// r/m16
	FCML_I32( "call word ptr [edi+00000001h]", 0x66, 0xFF, 0x57, 0x01 );
	// r/m64 (Size directives are the same for operand size 32 and 64 bits.)
	FCML_I64( "call qword ptr [rdi+0000000000000001h]", 0x66, 0x48, 0xFF, 0x57, 0x01 );
	// Look at the position of REX prefix, it has to fail.
	FCML_I64( "FAIL", 0x48, 0x66, 0xFF, 0x57, 0x01 );
	FCML_I64( "call qword ptr [rdi+0000000000000001h]", 0x66, 0xFF, 0x57, 0x01 );
	FCML_I32( "call 0ff701005h", 0xE8, 0x00, 0x00, 0x30, 0xFF );

	*/
}

CU_TestInfo fctl_ti_instructions_c[] = {
    { "fcml_tf_instruction_CALL", fcml_tf_instruction_CALL },
    CU_TEST_INFO_NULL,
};

CU_SuiteInfo fctl_si_instructions_c[] = {
    { "suite-fctl_ti_instructions_c", fcml_tf_instructions_c_suite_init, fcml_tf_instructions_c_suite_cleanup, fctl_ti_instructions_c },
    CU_SUITE_INFO_NULL,
};
