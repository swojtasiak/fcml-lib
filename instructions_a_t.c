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

CU_TestInfo fctl_ti_instructions_a[] = {
    { "fcml_tf_instruction_AAA", fcml_tf_instruction_AAA },
    { "fcml_tf_instruction_AAD", fcml_tf_instruction_AAD },
    { "fcml_tf_instruction_AAM", fcml_tf_instruction_AAM },
    { "fcml_tf_instruction_AAS", fcml_tf_instruction_AAS },
    CU_TEST_INFO_NULL,
};

CU_SuiteInfo fctl_si_instructions_a[] = {
    { "suite-fctl_ti_instructions_a", fcml_tf_instructions_a_suite_init, fcml_tf_instructions_a_suite_cleanup, fctl_ti_instructions_a },
    CU_SUITE_INFO_NULL,
};
