/*
 * instructions.c
 *
 *  Created on: 01-06-2013
 *      Author: tAs
 */

#include "fcml_env.h"
#include "fcml_assembler.h"
#include "instructions_b_t.h"

int fcml_tf_instructions_b_suite_init(void) {
	return 0;
}

int fcml_tf_instructions_b_suite_cleanup(void) {
	return 0;
}

void fcml_tf_instruction_BBB(void) {
}

CU_TestInfo fctl_ti_instructions_b[] = {
    { "fcml_tf_instruction_BBB", fcml_tf_instruction_BBB },
    CU_TEST_INFO_NULL,
};

CU_SuiteInfo fctl_si_instructions_b[] = {
    { "suite-fctl_ti_instructions_b", fcml_tf_instructions_b_suite_init, fcml_tf_instructions_b_suite_cleanup, fctl_ti_instructions_b },
    CU_SUITE_INFO_NULL,
};
