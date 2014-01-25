/*
 * instructions.c
 *
 *  Created on: 01-06-2013
 *      Author: tAs
 */

#include "fcml_env.h"
#include "fcml_assembler.h"
#include "instructions_g_t.h"
#include "instructions_base_t.h"

void fcml_tf_instructions_g_suite_init(void) {
}

void fcml_tf_instructions_g_suite_cleanup(void) {
}

void fcml_tf_instruction_GETSEC(void) {
    FCML_I3264( "getsec", 0x0F, 0x37 );
    FCML_A64( "getsec", 0x0f, 0x37 );
}

fcml_stf_test_case fctl_ti_instructions_g[] = {
	{ "fcml_tf_instruction_GETSEC", fcml_tf_instruction_GETSEC },
	FCML_STF_NULL_TEST
};

fcml_stf_test_suite fctl_si_instructions_g = {
	"suite-fctl_ti_instructions_g", fcml_tf_instructions_g_suite_init, fcml_tf_instructions_g_suite_cleanup, fctl_ti_instructions_g
};
