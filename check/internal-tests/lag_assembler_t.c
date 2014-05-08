/*
 * FCML - Free Code Manipulation Library.
 * Copyright (C) 2010-2014 Slawomir Wojtasiak
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include "lag_assembler_t.h"

#include <stdio.h>

#include <fcml_stf.h>
#include <fcml_gas_dialect.h>
#include <fcml_intel_dialect.h>
#include <fcml_lag_assembler.h>

fcml_bool fcml_tf_lag_assembler_suite_init(void) {
	return FCML_TRUE;
}

fcml_bool fcml_tf_lag_assembler_suite_cleanup(void) {
	return FCML_TRUE;
}

struct fcml_ist_t_lag_test_case {
	fcml_string  *code_str;
	fcml_uint8_t *code_bin;
	fcml_int     code_size;
};

fcml_string fcml_iarr_lag_assembler_code_1_src[] = {
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

fcml_uint8_t fcml_iarr_lag_assembler_code_1_bin[] = {
	0xBB, 0x01, 0x00, 0x00, 0x00,
	0x43,
	0x83, 0xFB, 0x0A,
	0x74, 0x0F,
	0xB8, 0x01, 0x00, 0x00, 0x00,
	0x40,
	0x83, 0xF8, 0x0A,
	0x74, 0x02,
	0xEB, 0xF8,
	0xEB, 0xEB,
	0xC3
};

fcml_string fcml_iarr_lag_assembler_code_2_src[] = {
	"jmp second",
	"start:  jmp finish",
	"        nop",
	"        nop",
	"        nop",
	"        nop",
	"        nop",
	"        nop",
	"        nop",
	"        nop",
	"        nop",
	"        nop",
	"        nop",
	"        nop",
	"        nop",
	"        nop",
	"        nop",
	"        nop",
	"        nop",
	"        nop",
	"        nop",
	"        nop",
	"        nop",
	"        nop",
	"        nop",
	"        nop",
	"        nop",
	"        nop",
	"        nop",
	"        nop",
	"        nop",
	"        nop",
	"        nop",
	"        nop",
	"        nop",
	"        nop",
	"        nop",
	"        nop",
	"        nop",
	"        nop",
	"        nop",
	"        nop",
	"        nop",
	"        nop",
	"        nop",
	"        nop",
	"        nop",
	"        nop",
	"        nop",
	"        nop",
	"        nop",
	"        nop",
	"        nop",
	"        nop",
	"        nop",
	"        nop",
	"        nop",
	"        nop",
	"        nop",
	"        nop",
	"        nop",
	"        nop",
	"        nop",
	"        nop",
	"        nop",
	"        nop",
	"        nop",
	"        nop",
	"        nop",
	"        nop",
	"        nop",
	"        nop",
	"        nop",
	"        nop",
	"        nop",
	"        nop",
	"        nop",
	"        nop",
	"        nop",
	"        nop",
	"        nop",
	"        nop",
	"        nop",
	"        nop",
	"        nop",
	"        nop",
	"        nop",
	"        nop",
	"        nop",
	"        nop",
	"        nop",
	"        nop",
	"        nop",
	"        nop",
	"        nop",
	"        nop",
	"        nop",
	"        nop",
	"        nop",
	"        nop",
	"        nop",
	"        nop",
	"        nop",
	"        nop",
	"        nop",
	"        nop",
	"        nop",
	"        nop",
	"        nop",
	"        nop",
	"        nop",
	"        nop",
	"        nop",
	"        nop",
	"        nop",
	"        nop",
	"        nop",
	"        nop",
	"        nop",
	"        nop",
	"        nop",
	"        nop",
	"        nop",
	"        nop",
	"        nop",
	"        nop",
	"        nop",
	"second: jmp second+249-(finish-start)",
	"finish: ret"
};

fcml_uint8_t fcml_iarr_lag_assembler_code_2_bin[] = {
	0xE9, 0x82, 0x00, 0x00, 0x00, 0xE9, 0x7F, 0x00, 0x00, 0x00, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90,
	0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90,
	0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90,
	0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90,
	0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90,
	0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90,
	0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90,
	0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90,
	0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0xEB, 0x73, 0xC3
};

fcml_string fcml_iarr_lag_assembler_code_3_src[] = {
	"je  finish",
	"ret",
	NULL
};

struct fcml_ist_t_lag_test_case fcml_iarr_lag_test_cases[] = {
	{  fcml_iarr_lag_assembler_code_1_src, fcml_iarr_lag_assembler_code_1_bin, sizeof( fcml_iarr_lag_assembler_code_1_bin ) },
	{  fcml_iarr_lag_assembler_code_2_src, fcml_iarr_lag_assembler_code_2_bin, sizeof( fcml_iarr_lag_assembler_code_2_bin ) },
	{ NULL, NULL, 0 }
};

fcml_bool fcml_fn_lag_assemble_result_check( fcml_st_lag_assembler_result *result, fcml_uint8_t *code, fcml_int size ) {
	fcml_int code_index = 0;
	fcml_st_assembled_instruction *current = result->instructions;
	while( current && code_index <= size ) {
		fcml_int code_length = current->code_length;
		int i;
		for( i = 0; i < code_length && code_index <= size; i++ ) {
			if( current->code[i] != code[code_index++] ) {
				printf( "Index %d should be: 0x%x was 0x%x.\n", code_index - 1, code[code_index - 1], current->code[i] );
				return FCML_FALSE;
			}
		}
		current = current->next;
	}
	if( code_index != size ) {
		printf( "Instruction code do not match." );
		return FCML_FALSE;
	}
	return FCML_TRUE;
}

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

	struct fcml_ist_t_lag_test_case *test_cases = &(fcml_iarr_lag_test_cases[0]);

	fcml_int counter = 0;

	while( test_cases->code_bin ) {

		fcml_st_lag_assembler_context context = {0};
		context.assembler = assembler;
		context.entry_point.op_mode = FCML_AF_32_BIT;
		context.entry_point.ip = 0x00401000;

		error = fcml_fn_lag_assemble( &context, test_cases->code_str, &result );
		if( error ) {
			STF_FAIL("Failed to assemble code.");
			return;
		}

		fcml_bool ok = fcml_fn_lag_assemble_result_check( &result, test_cases->code_bin, test_cases->code_size );
		STF_ASSERT( ok );
		if( !ok ) {
			printf("Failed instruction nr: %d.\n", counter );
		}

		fcml_fn_symbol_table_free( context.symbol_table );

		fcml_fn_lag_assembler_result_free( &result );

		test_cases++;

		counter++;
	}

	fcml_fn_assembler_free( assembler );

	fcml_fn_dialect_free( dialect );

}

void fcml_tf_lag_assembler_test_1(void) {

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
	context.configuration.enable_error_messages = FCML_TRUE;
	context.assembler = assembler;
	context.entry_point.op_mode = FCML_AF_32_BIT;
	context.entry_point.ip = 0x00401000;

	error = fcml_fn_lag_assemble( &context, fcml_iarr_lag_assembler_code_3_src, &result );
	STF_ASSERT_EQUAL( error, FCML_CEH_GEC_UNDEFINED_SYMBOL );
	STF_ASSERT_PTR_NOT_NULL( result.errors.errors );
	if( result.errors.errors ) {
		STF_ASSERT_STRING_EQUAL( result.errors.errors->message, FCML_TEXT( "Undefined symbol: finish." ) );
	}

	fcml_fn_symbol_table_free( context.symbol_table );

	fcml_fn_lag_assembler_result_free( &result );

	fcml_fn_assembler_free( assembler );

	fcml_fn_dialect_free( dialect );
}

fcml_stf_test_case fcml_ti_lag_assembler[] = {
	{ "fcml_tf_lag_assembler_test", fcml_tf_lag_assembler_test },
	{ "fcml_tf_lag_assembler_test_1", fcml_tf_lag_assembler_test_1 },
	FCML_STF_NULL_TEST
};

fcml_stf_test_suite fcml_si_lag_assembler = {
	"suite-fcml-lag-assembler", fcml_tf_lag_assembler_suite_init, fcml_tf_lag_assembler_suite_cleanup, fcml_ti_lag_assembler
};
