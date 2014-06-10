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

#include "assembler_t.h"

#include <fcml_assembler.h>
#include <fcml_intel_dialect.h>
#include <fcml_gas_dialect.h>
#include <fcml_common_utils.h>

/* Test suite initialization. */

fcml_bool fcml_tf_assembler_suite_init(void) {
	return FCML_TRUE;
}

fcml_bool fcml_tf_assembler_suite_cleanup(void) {
	return FCML_TRUE;
}

/* Tests. */

void fcml_tf_assembler_db_imm8(void) {

	fcml_ceh_error error;

	/* Initializes the Intel dialect instance. */
	fcml_st_dialect *dialect;
	if( ( error = fcml_fn_dialect_init_intel( FCML_INTEL_DIALECT_CF_DEFAULT, &dialect ) ) ) {
		STF_FAIL("Can not initialize Intel dialect.");
		return;
	}

	fcml_st_assembler *assembler;
	if( ( error = fcml_fn_assembler_init( dialect, &assembler ) ) ) {
		STF_FAIL("Can not initialize Intel assembler.");
		fcml_fn_dialect_free( dialect );
		return;
	}

	fcml_st_instruction instruction = {0};
	instruction.mnemonic = "db";
	instruction.operands[0] = FCML_IMM8( 0x23 );
	instruction.operands_count = 1;

	/* Prepares the result. */
	fcml_st_assembler_result asm_result;
	fcml_fn_assembler_result_prepare( &asm_result );

	fcml_st_assembler_context context = {0};
	context.assembler = assembler;
	context.entry_point.ip = 0x401000;
	context.entry_point.op_mode = FCML_OM_32_BIT;

	/* Assembles the given instruction. */
	if( ( error = fcml_fn_assemble( &context, &instruction, &asm_result ) ) ) {
		STF_FAIL("Can not assemble instruction.");
		fcml_fn_assembler_free( assembler );
		fcml_fn_dialect_free( dialect );
		return;
	}

	/* Prints the instruction code. */
	if( asm_result.chosen_instruction ) {
		fcml_st_assembled_instruction *ins_code = asm_result.chosen_instruction;
		STF_ASSERT_EQUAL( 1, asm_result.number_of_instructions );
		STF_ASSERT_EQUAL( 1, ins_code->code_length );
		STF_ASSERT_EQUAL( 0x23, ins_code->code[0] );
		STF_ASSERT_PTR_NULL( ins_code->next );
		STF_ASSERT_PTR_NULL( ins_code->warnings.errors );
		STF_ASSERT_PTR_NULL( ins_code->warnings.last_error );
	} else {
		STF_FAIL("Can not assemble instruction.");
	}

	fcml_fn_assembler_result_free( &asm_result );
	fcml_fn_assembler_free( assembler );
	fcml_fn_dialect_free( dialect );

}

void fcml_tf_assembler_byte_imm8(void) {

	fcml_ceh_error error;

	/* Initializes the Intel dialect instance. */
	fcml_st_dialect *dialect;
	if( ( error = fcml_fn_dialect_init_gas( FCML_GAS_DIALECT_CF_DEFAULT, &dialect ) ) ) {
		STF_FAIL("Can not initialize Intel dialect.");
		return;
	}

	fcml_st_assembler *assembler;
	if( ( error = fcml_fn_assembler_init( dialect, &assembler ) ) ) {
		STF_FAIL("Can not initialize Intel assembler.");
		fcml_fn_dialect_free( dialect );
		return;
	}

	fcml_st_instruction instruction = {0};
	instruction.mnemonic = ".byte";
	instruction.operands[0] = FCML_IMM8( 0x23 );
	instruction.operands_count = 1;

	/* Prepares the result. */
	fcml_st_assembler_result asm_result;
	fcml_fn_assembler_result_prepare( &asm_result );

	fcml_st_assembler_context context = {0};
	context.assembler = assembler;
	context.entry_point.ip = 0x401000;
	context.entry_point.op_mode = FCML_OM_32_BIT;

	/* Assembles the given instruction. */
	if( ( error = fcml_fn_assemble( &context, &instruction, &asm_result ) ) ) {
		STF_FAIL("Can not assemble instruction.");
		fcml_fn_assembler_free( assembler );
		fcml_fn_dialect_free( dialect );
		return;
	}

	/* Prints the instruction code. */
	if( asm_result.chosen_instruction ) {
		fcml_st_assembled_instruction *ins_code = asm_result.chosen_instruction;
		STF_ASSERT_EQUAL( 1, asm_result.number_of_instructions );
		STF_ASSERT_EQUAL( 1, ins_code->code_length );
		STF_ASSERT_EQUAL( 0x23, ins_code->code[0] );
		STF_ASSERT_PTR_NULL( ins_code->next );
		STF_ASSERT_PTR_NULL( ins_code->warnings.errors );
		STF_ASSERT_PTR_NULL( ins_code->warnings.last_error );
	} else {
		STF_FAIL("Can not assemble instruction.");
	}

	fcml_fn_assembler_result_free( &asm_result );
	fcml_fn_assembler_free( assembler );
	fcml_fn_dialect_free( dialect );

}

void fcml_tf_assembler_db_imm32(void) {

	fcml_ceh_error error;

	/* Initializes the Intel dialect instance. */
	fcml_st_dialect *dialect;
	if( ( error = fcml_fn_dialect_init_intel( FCML_INTEL_DIALECT_CF_DEFAULT, &dialect ) ) ) {
		STF_FAIL("Can not initialize Intel dialect.");
		return;
	}

	fcml_st_assembler *assembler;
	if( ( error = fcml_fn_assembler_init( dialect, &assembler ) ) ) {
		STF_FAIL("Can not initialize Intel assembler.");
		fcml_fn_dialect_free( dialect );
		return;
	}

	fcml_st_instruction instruction = {0};
	instruction.mnemonic = "db";
	instruction.operands[0] = FCML_IMM32( 0x23 );
	instruction.operands_count = 1;

	/* Prepares the result. */
	fcml_st_assembler_result asm_result;
	fcml_fn_assembler_result_prepare( &asm_result );

	fcml_st_assembler_context context = {0};
	context.assembler = assembler;
	context.entry_point.ip = 0x401000;
	context.entry_point.op_mode = FCML_OM_32_BIT;

	/* Assembles the given instruction. */
	if( ( error = fcml_fn_assemble( &context, &instruction, &asm_result ) ) ) {
		STF_FAIL("Can not assemble instruction.");
		fcml_fn_assembler_free( assembler );
		fcml_fn_dialect_free( dialect );
		return;
	}

	/* Prints the instruction code. */
	if( asm_result.chosen_instruction ) {
		fcml_st_assembled_instruction *ins_code = asm_result.chosen_instruction;
		STF_ASSERT_EQUAL( 1, asm_result.number_of_instructions );
		STF_ASSERT_EQUAL( 1, ins_code->code_length );
		STF_ASSERT_EQUAL( 0x23, ins_code->code[0] );
		STF_ASSERT_PTR_NULL( ins_code->next );
		STF_ASSERT_PTR_NULL( ins_code->warnings.errors );
		STF_ASSERT_PTR_NULL( ins_code->warnings.last_error );
	} else {
		STF_FAIL("Can not assemble instruction.");
	}

	fcml_fn_assembler_result_free( &asm_result );
	fcml_fn_assembler_free( assembler );
	fcml_fn_dialect_free( dialect );

}

void fcml_tf_assembler_db_imm32_value_out_of_bound(void) {

	fcml_ceh_error error;

	/* Initializes the Intel dialect instance. */
	fcml_st_dialect *dialect;
	if( ( error = fcml_fn_dialect_init_intel( FCML_INTEL_DIALECT_CF_DEFAULT, &dialect ) ) ) {
		STF_FAIL("Can not initialize Intel dialect.");
		return;
	}

	fcml_st_assembler *assembler;
	if( ( error = fcml_fn_assembler_init( dialect, &assembler ) ) ) {
		STF_FAIL("Can not initialize Intel assembler.");
		fcml_fn_dialect_free( dialect );
		return;
	}

	fcml_st_instruction instruction = {0};
	instruction.mnemonic = "db";
	instruction.operands[0] = FCML_IMM32( 0x2323 );
	instruction.operands_count = 1;

	/* Prepares the result. */
	fcml_st_assembler_result asm_result;
	fcml_fn_assembler_result_prepare( &asm_result );

	fcml_st_assembler_context context = {0};
	context.assembler = assembler;
	context.entry_point.ip = 0x401000;
	context.entry_point.op_mode = FCML_OM_32_BIT;

	/* Assembles the given instruction. */
	error = fcml_fn_assemble( &context, &instruction, &asm_result );

	STF_ASSERT_EQUAL( FCML_CEH_GEC_VALUE_OUT_OF_RANGE, error );

	fcml_fn_assembler_result_free( &asm_result );
	fcml_fn_assembler_free( assembler );
	fcml_fn_dialect_free( dialect );

}

fcml_stf_test_case fcml_ti_assembler[] = {
	{ "fcml_tf_assembler_db_imm8", fcml_tf_assembler_db_imm8 },
	{ "fcml_tf_assembler_byte_imm8", fcml_tf_assembler_byte_imm8 },
	{ "fcml_tf_assembler_db_imm32", fcml_tf_assembler_db_imm32 },
	{ "fcml_tf_assembler_db_imm32_value_out_of_bound", fcml_tf_assembler_db_imm32_value_out_of_bound },
	FCML_STF_NULL_TEST
};

fcml_stf_test_suite fcml_si_assembler = {
	"suite-fcml-assembler", fcml_tf_assembler_suite_init, fcml_tf_assembler_suite_cleanup, fcml_ti_assembler
};
