/*
 * fcml_lag_assembler.c
 *
 *  Created on: Feb 22, 2014
 *      Author: tas
 */

#include "lag_assembler_t.h"

#include <fcml_stf.h>
#include <fcml_intel_dialect.h>
#include <fcml_lag_assembler.h>

void fcml_tf_lag_assembler_suite_init(void) {
}

void fcml_tf_lag_assembler_suite_cleanup(void) {
}

fcml_string fcml_iarr_lag_assembler_code[] = {
	"movl   $4, %eax",
	"movl   $2, %ebx",
	"movl   $0, %ecx",
	"movl   $text, %edx",
	"int    $0x80",
	"movl   $1, %eax",
	"xorl   %ebx, %ebx",
	"int    $0x80",
	"retq",
	NULL
};

void fcml_tf_lag_assembler_test(void) {

	fcml_ceh_error error;

	fcml_st_lag_assembler_result result;

	fcml_fn_lag_assembler_result_prepare( &result );

	fcml_st_dialect *dialect;

	error = fcml_fn_dialect_init_intel( FCML_INTEL_DIALECT_CF_DEFAULT, &dialect );
	if( error ) {
		STF_FAIL("Can not initialize dialect.");
		return;
	}

	fcml_st_assembler *assembler;

	error = fcml_fn_assembler_init( dialect, &assembler );
	if( error ) {
		STF_FAIL("Can not initialize assembler.");
		return;
	}

	fcml_st_assembler_context context = {0};
	context.assembler = assembler;
	context.entry_point.addr_form = FCML_AF_32_BIT;
	context.entry_point.ip.eip = 0x00401000;

	error = fcml_fn_lag_assemble( &context, fcml_iarr_lag_assembler_code, &result );
	if( error ) {
		STF_FAIL("Failed to assemble code.");
		return;
	}

	fcml_fn_assembler_free( assembler );

	fcml_fn_dialect_free( dialect );

}

fcml_stf_test_case fcml_ti_lag_assembler[] = {
	{ "fcml_tf_lag_assembler_test", fcml_tf_lag_assembler_test },
	FCML_STF_NULL_TEST
};

fcml_stf_test_suite fcml_si_lag_assembler = {
	"suite-fcml-lag-assembler", fcml_tf_lag_assembler_suite_init, fcml_tf_lag_assembler_suite_cleanup, fcml_ti_lag_assembler
};
