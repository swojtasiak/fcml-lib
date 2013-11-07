/*
 * fcml_chooser_t.c
 *
 *  Created on: Nov 7, 2013
 *      Author: tas
 */

#include "fcml_chooser_t.h"

#include <fcml_assembler.h>
#include <fcml_choosers.h>
#include <fcml_dialect_intel.h>
#include <fcml_common_utils.h>

#include "instructions_base_t.h"

int fcml_tf_chooser_suite_init(void) {
	return 0;
}

int fcml_tf_chooser_suite_cleanup(void) {
	return 0;
}

void fcml_fn_chooser_default(void) {

	// Instruction "adc ax,8042h" can be assembled in two ways.
	// 1: 0x66, 0x15, 0x42, 0x80
	// 2: 0x66, 0x81, 0xd0, 0x42, 0x80
	// Default instruction chooser is responsible for choosing the shortest form.

	fcml_st_asm_assembler_context context = {0};
	context.assembler = assembler;
	context.addr_form = FCML_AF_32_BIT;
	context.ip.eip = 0x00401000;

	fcml_st_instruction instruction = {0};
	instruction.mnemonic = "adc";
	instruction.operands[0] = FCML_REG( fcml_reg_AX );
	instruction.operands[1] = FCML_IMM16( 0x8042 );

	fcml_st_asm_assembler_result *result;

	if( !fcml_fn_asm_assemble( &context, &instruction, &result ) ) {
		CU_ASSERT_PTR_NOT_NULL( result->chosen_instruction );
		if( result->chosen_instruction ) {
			CU_ASSERT_EQUAL( 4, result->chosen_instruction->code_length );
			if( result->chosen_instruction->code_length == 4 ) {
				CU_ASSERT_EQUAL( 0x66, result->chosen_instruction->code[0] );
				CU_ASSERT_EQUAL( 0x15, result->chosen_instruction->code[1] );
				CU_ASSERT_EQUAL( 0x42, result->chosen_instruction->code[2] );
				CU_ASSERT_EQUAL( 0x80, result->chosen_instruction->code[3] );
			}
		}
		fcml_fn_asm_assembler_result_free( result );
	} else {
		CU_FAIL("Can not assemble instruction.");
	}

}

CU_TestInfo fcml_ti_chooser[] = {
    { "fcml_fn_chooser_default", fcml_fn_chooser_default },
    CU_TEST_INFO_NULL,
};

CU_SuiteInfo fcml_si_chooser[] = {
    { "suite-fcml-chooser", fcml_tf_chooser_suite_init, fcml_tf_chooser_suite_cleanup, fcml_ti_chooser },
    CU_SUITE_INFO_NULL,
};
