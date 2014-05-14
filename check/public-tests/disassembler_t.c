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

#include "disassembler_t.h"

#include <fcml_disassembler.h>
#include <fcml_intel_dialect.h>

/* Test suite initialization. */

fcml_bool fcml_tf_disassembler_suite_init(void) {
	return FCML_TRUE;
}

fcml_bool fcml_tf_disassembler_suite_cleanup(void) {
	return FCML_TRUE;
}

/* Tests. */

void fcml_tf_disassembler_no_instruction_found(void) {

	fcml_int8_t code[] = { 0x48, 0x66, 0xFF, 0x57, 0x01 };

	fcml_ceh_error error;

	/* Initializes the Intel dialect instance. */
	fcml_st_dialect *dialect;
	if( ( error = fcml_fn_dialect_init_intel( FCML_INTEL_DIALECT_CF_DEFAULT, &dialect ) ) ) {
		STF_FAIL("Can not initialize Dialect.");
		return;
	}

	/* Initializes disassembler for the Intel dialect. */
	fcml_st_disassembler *disassembler;
	if( ( error = fcml_fn_disassembler_init( dialect, &disassembler ) ) ) {
		STF_FAIL("Can not initialize Intel.");
		fcml_fn_dialect_free( dialect );
		return;
	}

	/* Prepares disassembler result. */
	fcml_st_disassembler_result dis_result;
	fcml_fn_disassembler_result_prepare( &dis_result );

	/* Disassembles the code. */
	fcml_st_disassembler_context context = {0};
	context.disassembler = disassembler;
	context.configuration.fail_if_unknown_instruction = FCML_FALSE;
	context.entry_point.ip = 0x401000;
	context.entry_point.op_mode = FCML_AF_64_BIT;
	context.code = code;
	context.code_length = sizeof( code );

	if( ( error = fcml_fn_disassemble( &context, &dis_result ) ) ) {
		STF_FAIL("Disassembling failed.");
		fcml_fn_disassembler_free( disassembler );
		fcml_fn_dialect_free( dialect );
		return;
	}

	STF_ASSERT_EQUAL( 1, dis_result.instruction.operands_count );
	STF_ASSERT_EQUAL( FCML_EOT_IMMEDIATE, dis_result.instruction.operands[0].type );
	STF_ASSERT_EQUAL( FCML_DS_8, dis_result.instruction.operands[0].immediate.size );
	STF_ASSERT_EQUAL( 0x48, dis_result.instruction.operands[0].immediate.int8 );
	STF_ASSERT_EQUAL( FCML_FALSE, dis_result.instruction.operands[0].immediate.is_signed );
	STF_ASSERT_EQUAL( FCML_EOT_IMMEDIATE, dis_result.instruction.operands[0].type );
	STF_ASSERT_EQUAL( FP_DB, dis_result.instruction_details.pseudo_op );
	STF_ASSERT_EQUAL( FCML_FALSE, dis_result.instruction.is_conditional );
	STF_ASSERT_EQUAL( 0, dis_result.instruction.hints );
	STF_ASSERT_EQUAL( 0, dis_result.instruction.prefixes );
	STF_ASSERT_EQUAL( 0, dis_result.instruction_details.addr_mode );
	STF_ASSERT_EQUAL( 0, dis_result.instruction_details.instruction );
	STF_ASSERT_EQUAL( 1, dis_result.instruction_details.instruction_size );
	STF_ASSERT_EQUAL( FCML_FALSE, dis_result.instruction_details.is_shortcut );
	STF_ASSERT_EQUAL( FCML_FALSE, dis_result.instruction_details.modrm_details.is_modrm );
	STF_ASSERT_EQUAL( FCML_FALSE, dis_result.instruction_details.modrm_details.is_rip );
	STF_ASSERT_EQUAL( 0x00, dis_result.instruction_details.modrm_details.modrm );
	STF_ASSERT_EQUAL( FCML_FALSE, dis_result.instruction_details.modrm_details.sib.is_not_null );
	STF_ASSERT_EQUAL( 0x00, dis_result.instruction_details.opcode_field_s_bit );
	STF_ASSERT_EQUAL( 0x00, dis_result.instruction_details.opcode_field_w_bit );
	STF_ASSERT_EQUAL( 0, dis_result.instruction_details.prefixes_details.prefixes_count );

	STF_ASSERT_STRING_EQUAL( "db", dis_result.instruction.mnemonic );
	STF_ASSERT_PTR_NULL( dis_result.instruction_details.instruction );

	/* Free everything. */
	fcml_fn_disassembler_result_free( &dis_result );
	fcml_fn_disassembler_free( disassembler );
	fcml_fn_dialect_free( dialect );
}

fcml_stf_test_case fcml_ti_disassembler[] = {
	{ "fcml_tf_disassembler_no_instruction_found", fcml_tf_disassembler_no_instruction_found },
	FCML_STF_NULL_TEST
};

fcml_stf_test_suite fcml_si_disassembler = {
	"suite-fcml-disassembler", fcml_tf_disassembler_suite_init, fcml_tf_disassembler_suite_cleanup, fcml_ti_disassembler
};
