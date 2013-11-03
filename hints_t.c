/*
 * hints_t.c
 *
 *  Created on: Nov 3, 2013
 *      Author: tas
 */

#include "hints_t.h"

#include "instructions_base_t.h"

int fcml_tf_hints_suite_init(void) {
	return 0;
}

int fcml_tf_hints_suite_cleanup(void) {
	return 0;
}

void fcml_fn_hints_sib(void) {
	FCML_I32( "add dword ptr [eax+00000001h],eax", 0x01, 0x40, 0x01 );
	FCML_I32_A( "add dword ptr [sib eax+00000001h],eax", 0x01, 0x44, 0x20, 0x01 );
	FCML_I32( "add dword ptr [eax],eax", 0x01, 0x00 );
	FCML_I32_A( "add dword ptr [sib eax],eax", 0x01, 0x04, 0x20 );
}

void fcml_fn_hints_rip(void) {
	FCML_I32( "add dword ptr [eax+00000001h],eax", 0x01, 0x40, 0x01 );
	FCML_I32_A( "add dword ptr [sib eax+00000001h],eax", 0x01, 0x44, 0x20, 0x01 );
	FCML_I32( "add dword ptr [eax],eax", 0x01, 0x00 );
	FCML_I32_A( "add dword ptr [sib eax],eax", 0x01, 0x04, 0x20 );
}

CU_TestInfo fcml_ti_hints[] = {
    { "fcml_fn_hints_sib", fcml_fn_hints_sib },
    { "fcml_fn_hints_rip", fcml_fn_hints_rip },
    CU_TEST_INFO_NULL,
};

CU_SuiteInfo fcml_si_hints[] = {
    { "suite-fcml-hints", fcml_tf_hints_suite_init, fcml_tf_hints_suite_cleanup, fcml_ti_hints },
    CU_SUITE_INFO_NULL,
};
