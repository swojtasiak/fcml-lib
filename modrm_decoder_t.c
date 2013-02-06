/*
 * modrm_decoder.c
 *
 *  Created on: 04-02-2013
 *      Author: Slawomir Wojtasiak
 */

#include "modrm_decoder_t.h"

int fcml_tf_modrm_suite_init(void) {
	return 0;
}

int fcml_tf_modrm_suite_cleanup(void) {
	return 0;
}

void fcml_tf_modrm_test_1(void) {
}

void fcml_tf_modrm_test_2(void) {
}

CU_TestInfo fctl_ti_modrm_decoder[] = {
    { "fcml_tf_modrm_test_1", fcml_tf_modrm_test_1 },
    { "fcml_tf_modrm_test_2", fcml_tf_modrm_test_2 },
    CU_TEST_INFO_NULL,
};

CU_SuiteInfo fctl_si_modrm_decoder[] = {
    { "suite-modrm", fcml_tf_modrm_suite_init, fcml_tf_modrm_suite_cleanup, fctl_ti_modrm_decoder },
    CU_SUITE_INFO_NULL,
};


