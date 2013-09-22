/*
 * instructions.c
 *
 *  Created on: 01-06-2013
 *      Author: tAs
 */

#include "fcml_env.h"
#include "fcml_assembler.h"
#include "instructions_i_t.h"

int fcml_tf_instructions_j_suite_init(void) {
	return 0;
}

int fcml_tf_instructions_j_suite_cleanup(void) {
	return 0;
}

void fcml_tf_instruction_JCXZ(void) {
    FCML_I64( "jrcxz 0000800000401002h", 0x66, 0xe3, 0xff );
    FCML_I64( "jecxz 0000800000401003h", 0x66, 0x67, 0xe3, 0xff );
    FCML_I64( "jrcxz 0000800000401002h", 0x48, 0xe3, 0xff );
    FCML_I32( "jcxz 00001003h", 0x66, 0x67, 0xe3, 0xff );
    FCML_I32( "jcxz 00401002h", 0x67, 0xe3, 0xff );
    FCML_I32( "jecxz 00401001h", 0xe3, 0xff );
}

CU_TestInfo fctl_ti_instructions_j[] = {
    { "fcml_tf_instruction_JCXZ", fcml_tf_instruction_JCXZ },
    CU_TEST_INFO_NULL,
};

CU_SuiteInfo fctl_si_instructions_j[] = {
    { "suite-fctl_ti_instructions_j", fcml_tf_instructions_j_suite_init, fcml_tf_instructions_j_suite_cleanup, fctl_ti_instructions_j },
    CU_SUITE_INFO_NULL,
};
