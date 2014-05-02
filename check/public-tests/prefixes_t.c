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

#include "prefixes_t.h"

#include <fcml_assembler.h>
#include <fcml_choosers.h>
#include <fcml_intel_dialect.h>
#include <fcml_common_utils.h>

#include "instructions_base_t.h"

fcml_bool fcml_tf_prefixes_suite_init(void) {
	return FCML_TRUE;
}

fcml_bool fcml_tf_prefixes_suite_cleanup(void) {
	return FCML_TRUE;
}

void fcml_fn_prefixes_66(void) {

	/* Prefixes aren't needed.*/

	fcml_st_assembler_context context = {0};
	context.assembler = assembler_intel;
	context.entry_point.op_mode = FCML_AF_16_BIT;
	context.entry_point.ip = 0x00401000;

	fcml_st_instruction instruction = {0};
	instruction.mnemonic = "adc";
	instruction.operands[0] = FCML_REG( fcml_reg_BP );
	instruction.operands[1] = FCML_IMM16( 0x0201 );

	fcml_st_assembler_result result;

	fcml_fn_assembler_result_prepare( &result );

	if( !fcml_fn_assemble( &context, &instruction, &result ) ) {
		STF_ASSERT_PTR_NOT_NULL( result.chosen_instruction );
		if( result.chosen_instruction ) {
			STF_ASSERT_EQUAL( 4, result.chosen_instruction->code_length );
			if( result.chosen_instruction->code_length == 4 ) {
				STF_ASSERT_EQUAL( 0x81, result.chosen_instruction->code[0] );
				STF_ASSERT_EQUAL( 0xD5, result.chosen_instruction->code[1] );
				STF_ASSERT_EQUAL( 0x01, result.chosen_instruction->code[2] );
				STF_ASSERT_EQUAL( 0x02, result.chosen_instruction->code[3] );
			}
		}
		fcml_fn_assembler_result_free( &result );
	} else {
		STF_FAIL("Can not assemble instruction.");
	}

	/* Prefixes 0x66 is needed to change default operand size attribute back to 16 bits.*/

	context.entry_point.operand_size_attribute = FCML_DS_32;
	context.entry_point.op_mode = FCML_AF_16_BIT;
	context.entry_point.ip = 0x00401000;

	instruction.mnemonic = "adc";
	instruction.operands[0] = FCML_REG( fcml_reg_BP );
	instruction.operands[1] = FCML_IMM16( 0x0201 );

	if( !fcml_fn_assemble( &context, &instruction, &result ) ) {
		STF_ASSERT_PTR_NOT_NULL( result.chosen_instruction );
		if( result.chosen_instruction ) {
			STF_ASSERT_EQUAL( 5, result.chosen_instruction->code_length );
			if( result.chosen_instruction->code_length == 5 ) {
				STF_ASSERT_EQUAL( 0x66, result.chosen_instruction->code[0] );
				STF_ASSERT_EQUAL( 0x81, result.chosen_instruction->code[1] );
				STF_ASSERT_EQUAL( 0xD5, result.chosen_instruction->code[2] );
				STF_ASSERT_EQUAL( 0x01, result.chosen_instruction->code[3] );
				STF_ASSERT_EQUAL( 0x02, result.chosen_instruction->code[4] );
			}
		}
		fcml_fn_assembler_result_free( &result );
	} else {
		STF_FAIL("Can not assemble instruction.");
	}

	/* Prefixes 0x66 is needed to change default operand size attribute to 32 bits.*/

	context.entry_point.operand_size_attribute = FCML_DS_16;
	context.entry_point.op_mode = FCML_AF_16_BIT;
	context.entry_point.ip = 0x00401000;

	instruction.mnemonic = "adc";
	instruction.operands[0] = FCML_REG( fcml_reg_EBP );
	instruction.operands[1] = FCML_IMM32( 0x02010000 );

	if( !fcml_fn_assemble( &context, &instruction, &result ) ) {
		STF_ASSERT_PTR_NOT_NULL( result.chosen_instruction );
		if( result.chosen_instruction ) {
			STF_ASSERT_EQUAL( 7, result.chosen_instruction->code_length );
			if( result.chosen_instruction->code_length == 5 ) {
				STF_ASSERT_EQUAL( 0x66, result.chosen_instruction->code[0] );
				STF_ASSERT_EQUAL( 0x81, result.chosen_instruction->code[1] );
				STF_ASSERT_EQUAL( 0xD5, result.chosen_instruction->code[2] );
				STF_ASSERT_EQUAL( 0x00, result.chosen_instruction->code[3] );
				STF_ASSERT_EQUAL( 0x00, result.chosen_instruction->code[4] );
				STF_ASSERT_EQUAL( 0x01, result.chosen_instruction->code[3] );
				STF_ASSERT_EQUAL( 0x02, result.chosen_instruction->code[4] );
			}
		}
		fcml_fn_assembler_result_free( &result );
	} else {
		STF_FAIL("Can not assemble instruction.");
	}

	/* Prefixes 0x66 is needed to change default operand size attribute back to 32 bits.*/

	context.entry_point.operand_size_attribute = FCML_DS_16;
	context.entry_point.op_mode = FCML_AF_32_BIT;
	context.entry_point.ip = 0x00401000;

	instruction.mnemonic = "adc";
	instruction.operands[0] = FCML_REG( fcml_reg_EBP );
	instruction.operands[1] = FCML_IMM32( 0x02010000 );

	if( !fcml_fn_assemble( &context, &instruction, &result ) ) {
		STF_ASSERT_PTR_NOT_NULL( result.chosen_instruction );
		if( result.chosen_instruction ) {
			STF_ASSERT_EQUAL( 7, result.chosen_instruction->code_length );
			if( result.chosen_instruction->code_length == 5 ) {
				STF_ASSERT_EQUAL( 0x66, result.chosen_instruction->code[0] );
				STF_ASSERT_EQUAL( 0x81, result.chosen_instruction->code[1] );
				STF_ASSERT_EQUAL( 0xD5, result.chosen_instruction->code[2] );
				STF_ASSERT_EQUAL( 0x00, result.chosen_instruction->code[3] );
				STF_ASSERT_EQUAL( 0x00, result.chosen_instruction->code[4] );
				STF_ASSERT_EQUAL( 0x01, result.chosen_instruction->code[3] );
				STF_ASSERT_EQUAL( 0x02, result.chosen_instruction->code[4] );
			}
		}
		fcml_fn_assembler_result_free( &result );
	} else {
		STF_FAIL("Can not assemble instruction.");
	}

}

fcml_stf_test_case fcml_ti_prefixes[] = {
	{ "fcml_fn_prefixes_66", fcml_fn_prefixes_66 },
	FCML_STF_NULL_TEST
};

fcml_stf_test_suite fcml_si_prefixes = {
	"suite-fcml-prefixes", fcml_tf_prefixes_suite_init, fcml_tf_prefixes_suite_cleanup, fcml_ti_prefixes
};
