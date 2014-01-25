/*
 * prefixes_t.c
 *
 *  Created on: Nov 9, 2013
 *      Author: tas
 */

#include "prefixes_t.h"

#include <fcml_assembler.h>
#include <fcml_choosers.h>
#include <fcml_intel_dialect.h>
#include <fcml_common_utils.h>

#include "instructions_base_t.h"

void fcml_tf_prefixes_suite_init(void) {
}

void fcml_tf_prefixes_suite_cleanup(void) {
}

void fcml_fn_prefixes_66(void) {

	/* Prefixes aren't needed.*/

	fcml_st_assembler_context context = {0};
	context.assembler = assembler_intel;
	context.addr_form = FCML_AF_16_BIT;
	context.ip.eip = 0x00401000;

	fcml_st_instruction instruction = {0};
	instruction.mnemonic = "adc";
	instruction.operands[0] = FCML_REG( fcml_reg_BP );
	instruction.operands[1] = FCML_IMM16( 0x0201 );

	fcml_st_assembler_result *result;

	if( !fcml_fn_assemble( &context, &instruction, &result ) ) {
		STF_ASSERT_PTR_NOT_NULL( result->chosen_instruction );
		if( result->chosen_instruction ) {
			STF_ASSERT_EQUAL( 4, result->chosen_instruction->code_length );
			if( result->chosen_instruction->code_length == 4 ) {
				STF_ASSERT_EQUAL( 0x81, result->chosen_instruction->code[0] );
				STF_ASSERT_EQUAL( 0xD5, result->chosen_instruction->code[1] );
				STF_ASSERT_EQUAL( 0x01, result->chosen_instruction->code[2] );
				STF_ASSERT_EQUAL( 0x02, result->chosen_instruction->code[3] );
			}
		}
		fcml_fn_assembler_result_free( result );
	} else {
		STF_FAIL("Can not assemble instruction.");
	}

	/* Prefixes 0x66 is needed to change default operand size attribute back to 16 bits.*/

	context.operand_size_attribute = FCML_DS_32;
	context.addr_form = FCML_AF_16_BIT;
	context.ip.eip = 0x00401000;

	instruction.mnemonic = "adc";
	instruction.operands[0] = FCML_REG( fcml_reg_BP );
	instruction.operands[1] = FCML_IMM16( 0x0201 );

	if( !fcml_fn_assemble( &context, &instruction, &result ) ) {
		STF_ASSERT_PTR_NOT_NULL( result->chosen_instruction );
		if( result->chosen_instruction ) {
			STF_ASSERT_EQUAL( 5, result->chosen_instruction->code_length );
			if( result->chosen_instruction->code_length == 5 ) {
				STF_ASSERT_EQUAL( 0x66, result->chosen_instruction->code[0] );
				STF_ASSERT_EQUAL( 0x81, result->chosen_instruction->code[1] );
				STF_ASSERT_EQUAL( 0xD5, result->chosen_instruction->code[2] );
				STF_ASSERT_EQUAL( 0x01, result->chosen_instruction->code[3] );
				STF_ASSERT_EQUAL( 0x02, result->chosen_instruction->code[4] );
			}
		}
		fcml_fn_assembler_result_free( result );
	} else {
		STF_FAIL("Can not assemble instruction.");
	}

	/* Prefixes 0x66 is needed to change default operand size attribute to 32 bits.*/

	context.operand_size_attribute = FCML_DS_16;
	context.addr_form = FCML_AF_16_BIT;
	context.ip.eip = 0x00401000;

	instruction.mnemonic = "adc";
	instruction.operands[0] = FCML_REG( fcml_reg_EBP );
	instruction.operands[1] = FCML_IMM32( 0x02010000 );

	if( !fcml_fn_assemble( &context, &instruction, &result ) ) {
		STF_ASSERT_PTR_NOT_NULL( result->chosen_instruction );
		if( result->chosen_instruction ) {
			STF_ASSERT_EQUAL( 7, result->chosen_instruction->code_length );
			if( result->chosen_instruction->code_length == 5 ) {
				STF_ASSERT_EQUAL( 0x66, result->chosen_instruction->code[0] );
				STF_ASSERT_EQUAL( 0x81, result->chosen_instruction->code[1] );
				STF_ASSERT_EQUAL( 0xD5, result->chosen_instruction->code[2] );
				STF_ASSERT_EQUAL( 0x00, result->chosen_instruction->code[3] );
				STF_ASSERT_EQUAL( 0x00, result->chosen_instruction->code[4] );
				STF_ASSERT_EQUAL( 0x01, result->chosen_instruction->code[3] );
				STF_ASSERT_EQUAL( 0x02, result->chosen_instruction->code[4] );
			}
		}
		fcml_fn_assembler_result_free( result );
	} else {
		STF_FAIL("Can not assemble instruction.");
	}

	/* Prefixes 0x66 is needed to change default operand size attribute back to 32 bits.*/

	context.operand_size_attribute = FCML_DS_16;
	context.addr_form = FCML_AF_32_BIT;
	context.ip.eip = 0x00401000;

	instruction.mnemonic = "adc";
	instruction.operands[0] = FCML_REG( fcml_reg_EBP );
	instruction.operands[1] = FCML_IMM32( 0x02010000 );

	if( !fcml_fn_assemble( &context, &instruction, &result ) ) {
		STF_ASSERT_PTR_NOT_NULL( result->chosen_instruction );
		if( result->chosen_instruction ) {
			STF_ASSERT_EQUAL( 7, result->chosen_instruction->code_length );
			if( result->chosen_instruction->code_length == 5 ) {
				STF_ASSERT_EQUAL( 0x66, result->chosen_instruction->code[0] );
				STF_ASSERT_EQUAL( 0x81, result->chosen_instruction->code[1] );
				STF_ASSERT_EQUAL( 0xD5, result->chosen_instruction->code[2] );
				STF_ASSERT_EQUAL( 0x00, result->chosen_instruction->code[3] );
				STF_ASSERT_EQUAL( 0x00, result->chosen_instruction->code[4] );
				STF_ASSERT_EQUAL( 0x01, result->chosen_instruction->code[3] );
				STF_ASSERT_EQUAL( 0x02, result->chosen_instruction->code[4] );
			}
		}
		fcml_fn_assembler_result_free( result );
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
