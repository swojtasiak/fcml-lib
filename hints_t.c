/*
 * hints_t.c
 *
 *  Created on: Nov 3, 2013
 *      Author: tas
 */

#include "hints_t.h"

#include "instructions_base_t.h"

#include <fcml_rend.h>

int fcml_tf_hints_suite_init(void) {
	return 0;
}

int fcml_tf_hints_suite_cleanup(void) {
	return 0;
}

void fcml_fn_hints_sib(void) {
	FCML_I32( "add dword ptr [eax+00000001h],eax", 0x01, 0x40, 0x01 );
	FCML_A32( "add %eax,0x00000001(%eax)", 0x01, 0x40, 0x01 );
	FCML_I32_A( "add dword ptr [sib eax+00000001h],eax", 0x01, 0x44, 0x20, 0x01 );
	FCML_A32_D( "add %eax,0x00000001(%eax)", 0x01, 0x44, 0x20, 0x01 );
	FCML_I32( "add dword ptr [eax],eax", 0x01, 0x00 );
	FCML_I32_A( "add dword ptr [sib eax],eax", 0x01, 0x04, 0x20 );
}

void fcml_fn_hints_rip(void) {
	// RIP enabled by default.
	FCML_I64_RIP_A( "rcl byte ptr [0000800000401007h],03h", 0xC0, 0x15, 0x00, 0x00, 0x00, 0x00, 0x03 );
	// RIP by default, absolute forced, take into account that SIB encoding was used to encode it.
	FCML_I64_RIP_A( "rcl byte ptr [abs 0000000000401007h],03h", 0xc0, 0x14, 0x25, 0x07, 0x10, 0x40, 0x00, 0x03 );
	// Offset is too big to be encoded as absolute offset.
	FCML_I64_A_FAILED( "rcl byte ptr [0000800000401007h],03h", 0xC0, 0x15, 0x00, 0x00, 0x00, 0x00, 0x03 );
	// Absolute offset enabled by default.
	FCML_I64( "rcl byte ptr [0000000000401007h],03h", 0xc0, 0x14, 0x25, 0x07, 0x10, 0x40, 0x00, 0x03 );
	// In 32 bit mode, SIB is not needed, so it is not used by default, but...
	FCML_I32( "rcl byte ptr [00401007h],03h", 0xc0, 0x15, 0x07, 0x10, 0x40, 0x00, 0x03 );
	// we can force it.
	FCML_I32_A( "rcl byte ptr [sib 00401007h],03h", 0xc0, 0x14, 0x25, 0x07, 0x10, 0x40, 0x00, 0x03 );
	// It's interesting combination. RIP should be used by default, but SIB hint was used. Hints have higher precedence
	// so it forced absolute address to be used (Because absolute offset is encoded using SIB). In this case SIB hint works like the ABS one.
	FCML_I64_RIP_A( "rcl byte ptr [sib 00401007h],03h", 0xc0, 0x14, 0x25, 0x07, 0x10, 0x40, 0x00, 0x03 );
	// Absolute by default but RIP forced.
	FCML_I64_A( "rcl byte ptr [rel 0000800000401007h],03h", 0xc0, 0x15, 0x00, 0x00, 0x00, 0x00, 0x03 );
	// Hints rendering.
	FCML_I64_RF( "rcl byte ptr [rel 0000800000401007h],03h", FCML_REND_FLAG_RENDER_REL_HINT, 0xc0, 0x15, 0x00, 0x00, 0x00, 0x00, 0x03 );
	FCML_I64_RF( "rcl byte ptr [abs 0000000000401007h],03h", FCML_REND_FLAG_RENDER_ABS_HINT, 0xc0, 0x14, 0x25, 0x07, 0x10, 0x40, 0x00, 0x03 );
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
