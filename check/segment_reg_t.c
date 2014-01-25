/*
 * segment_reg_t.c
 *
 *  Created on: Nov 11, 2013
 *      Author: tas
 */

#include "segment_reg_t.h"

#include <string.h>

#include <fcml_assembler.h>
#include <fcml_ceh.h>
#include <fcml_common.h>
#include <fcml_common_utils.h>

#include "instructions_base_t.h"

void fcml_tf_prefixes_segment_reg_suite_init(void) {
}

void fcml_tf_prefixes_segment_reg_suite_cleanup(void) {
}

void fcml_fn_segment_reg(void) {

	fcml_st_assembler_context context = {0};
	context.assembler = assembler_intel;
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

	fcml_st_assembler_result *result = NULL;

	if( !fcml_fn_assemble( &context, &instruction, &result ) ) {
		STF_ASSERT_PTR_NOT_NULL( result->chosen_instruction );
		if( result->chosen_instruction ) {
			STF_ASSERT_EQUAL( 1, result->chosen_instruction->code_length );
			if( result->chosen_instruction->code_length == 4 ) {
				STF_ASSERT_EQUAL( 0xA7, result->chosen_instruction->code[0] );
			}
		}
	} else {
		STF_FAIL("Can not assemble instruction.");
	}

	fcml_fn_assembler_result_free( result );

	// Now try to override ES.

	result = NULL;

	instruction.operands[1].address.segment_selector.segment_selector = fcml_reg_CS;

	if( fcml_fn_assemble( &context, &instruction, &result ) ) {

		STF_ASSERT_PTR_NOT_NULL( result->errors.last_error );
		if( result->errors.last_error ) {
			STF_ASSERT_STRING_EQUAL( "Segment register can not be overridden.", result->errors.last_error->message );
		}

	} else {
		STF_FAIL("Instruction should fail.");
	}

	fcml_fn_assembler_result_free( result );

}

fcml_stf_test_case fcml_ti_segment_reg[] = {
	{ "fcml_fn_segment_reg", fcml_fn_segment_reg },
	FCML_STF_NULL_TEST
};

fcml_stf_test_suite fcml_si_segment_reg = {
	"suite-fcml-segment_reg", fcml_tf_prefixes_segment_reg_suite_init, fcml_tf_prefixes_segment_reg_suite_cleanup, fcml_ti_segment_reg
};

