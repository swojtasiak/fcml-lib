/*
 * instructions.c
 *
 *  Created on: 01-06-2013
 *      Author: tAs
 */

#include "fcml_env.h"
#include "fcml_assembler.h"
#include "instructions_g_t.h"

int fcml_tf_instructions_g_suite_init(void) {
	return 0;
}

int fcml_tf_instructions_g_suite_cleanup(void) {
	return 0;
}

void fcml_tf_instruction_GETSEC(void) {
    FCML_I3264( "getsec", 0x0F, 0x37 );
}

CU_TestInfo fctl_ti_instructions_g[] = {
    { "fcml_tf_instruction_GETSEC", fcml_tf_instruction_GETSEC },
    CU_TEST_INFO_NULL,
};

CU_SuiteInfo fctl_si_instructions_g[] = {
    { "suite-fctl_ti_instructions_g", fcml_tf_instructions_g_suite_init, fcml_tf_instructions_g_suite_cleanup, fctl_ti_instructions_g },
    CU_SUITE_INFO_NULL,
};
