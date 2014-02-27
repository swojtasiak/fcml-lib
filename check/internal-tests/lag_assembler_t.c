/*
 * fcml_lag_assembler.c
 *
 *  Created on: Feb 22, 2014
 *      Author: tas
 */

#include "lag_assembler_t.h"

#include <fcml_stf.h>
#include <fcml_gas_dialect.h>
#include <fcml_intel_dialect.h>
#include <fcml_lag_assembler.h>

void fcml_tf_lag_assembler_suite_init(void) {
}

void fcml_tf_lag_assembler_suite_cleanup(void) {
}

/*
 *         jmp second
start:  jmp finish
        rb  124
second: jmp 249-(finish-start)
finish: ret
 */


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

fcml_string fcml_iarr_lag_assembler_code_1[] = {
	"start:      mov ebx, 1",
	"loop_big:   inc ebx",
	"            cmp ebx, 10",
	"            je  finish",
	"loop_small: mov eax, 1",
	"increment:  inc eax",
	"            cmp eax, 10",
	"            je  finish_small",
	"            jmp increment",
	"finish_small:",
	"            jmp loop_big",
	"finish:     ret",
	NULL
};



void fcml_tf_lag_assembler_test(void) {

	fcml_ceh_error error;

	fcml_st_lag_assembler_result result;

	fcml_fn_lag_assembler_result_prepare( &result );

	fcml_st_dialect *dialect;

	//error = fcml_fn_dialect_init_gas( FCML_GAS_DIALECT_CF_DEFAULT, &dialect );
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

	fcml_st_lag_assembler_context context = {0};
	context.assembler = assembler;
	context.entry_point.addr_form = FCML_AF_32_BIT;
	context.entry_point.ip.eip = 0x00401000;
	context.dialect = dialect;

	error = fcml_fn_lag_assemble( &context, fcml_iarr_lag_assembler_code_1, &result );
	if( error ) {
		STF_FAIL("Failed to assemble code.");
		return;
	}

	fcml_fn_lag_assembler_result_free( &result );

	fcml_fn_assembler_free( assembler );

	fcml_fn_symbol_table_free( context.symbol_table );

	fcml_fn_dialect_free( dialect );

}

fcml_stf_test_case fcml_ti_lag_assembler[] = {
	{ "fcml_tf_lag_assembler_test", fcml_tf_lag_assembler_test },
	FCML_STF_NULL_TEST
};

fcml_stf_test_suite fcml_si_lag_assembler = {
	"suite-fcml-lag-assembler", fcml_tf_lag_assembler_suite_init, fcml_tf_lag_assembler_suite_cleanup, fcml_ti_lag_assembler
};
