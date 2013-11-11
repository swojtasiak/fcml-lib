/*
 * segment_reg_t.c
 *
 *  Created on: Nov 11, 2013
 *      Author: tas
 */

#include "segment_reg_t.h"

#include <CUnit/CUnit.h>
#include <CUnit/TestDB.h>
#include <CUnit/TestRun.h>
#include <fcml_assembler.h>
#include <fcml_ceh.h>
#include <fcml_common.h>
#include <fcml_common_utils.h>
#include <string.h>

#include "instructions_base_t.h"

int fcml_tf_prefixes_segment_reg_suite_init(void) {
	return 0;
}

int fcml_tf_prefixes_segment_reg_suite_cleanup(void) {
	return 0;
}

void fcml_fn_segment_reg(void) {

	fcml_st_asm_assembler_context context = {0};
	context.assembler = assembler;
	context.addr_form = FCML_AF_32_BIT;
	context.ip.eip = 0x00401000;

	fcml_st_instruction instruction = {0};
	instruction.mnemonic = "cmps";
	instruction.operands[0].type = FCML_EOT_ADDRESS;
	instruction.operands[0].address.segment_selector.segment_selector = fcml_reg_DS;
	instruction.operands[0].address.address_form = FCML_AF_COMBINED;
	instruction.operands[0].address.size_operator = FCML_DS_32;
	instruction.operands[0].address.effective_address.base = fcml_reg_ESI;
	instruction.operands[1].type = FCML_EOT_ADDRESS;
	instruction.operands[1].address.segment_selector.segment_selector = fcml_reg_ES;
	instruction.operands[1].address.address_form = FCML_AF_COMBINED;
	instruction.operands[1].address.size_operator = FCML_DS_32;
	instruction.operands[1].address.effective_address.base = fcml_reg_EDI;

	fcml_st_asm_assembler_result *result;

	if( !fcml_fn_asm_assemble( &context, &instruction, &result ) ) {
		CU_ASSERT_PTR_NOT_NULL( result->chosen_instruction );
		if( result->chosen_instruction ) {
			CU_ASSERT_EQUAL( 1, result->chosen_instruction->code_length );
			if( result->chosen_instruction->code_length == 4 ) {
				CU_ASSERT_EQUAL( 0xA7, result->chosen_instruction->code[0] );
			}
		}
	} else {
		CU_FAIL("Can not assemble instruction.");
	}

	fcml_fn_asm_assembler_result_free( result );

	// Now try to override ES.

	instruction.operands[1].address.segment_selector.segment_selector = fcml_reg_CS;

	if( fcml_fn_asm_assemble( &context, &instruction, &result ) ) {

		CU_ASSERT_PTR_NOT_NULL( result->errors.last_error );
		if( result->errors.last_error ) {
			CU_ASSERT_STRING_EQUAL( "Segment register can not be overridden.", result->errors.last_error->message );
		}

	} else {
		CU_FAIL("Instruction should fail.");
	}

	fcml_fn_asm_assembler_result_free( result );

}

CU_TestInfo fcml_ti_segment_reg[] = {
    { "fcml_fn_segment_reg", fcml_fn_segment_reg },
    CU_TEST_INFO_NULL,
};

CU_SuiteInfo fcml_si_segment_reg[] = {
    { "suite-fcml-segment_reg", fcml_tf_prefixes_segment_reg_suite_init, fcml_tf_prefixes_segment_reg_suite_cleanup, fcml_ti_segment_reg },
    CU_SUITE_INFO_NULL,
};
