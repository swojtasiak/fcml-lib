/*
 * FCML - Free Code Manipulation Library.
 * Copyright (C) 2010-2020 Slawomir Wojtasiak
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

#include "segment_reg_t.h"

#include <string.h>

#include <fcml_assembler.h>
#include <fcml_common.h>
#include <fcml_common_utils.h>

#include "instructions_base_t.h"

fcml_bool fcml_tf_prefixes_segment_reg_suite_init(void) {
	return FCML_TRUE;
}

fcml_bool fcml_tf_prefixes_segment_reg_suite_cleanup(void) {
	return FCML_TRUE;
}

void fcml_fn_segment_reg(void) {

	fcml_st_assembler_context context = {0};
	context.assembler = assembler_intel;
	context.entry_point.op_mode = FCML_OM_32_BIT;
	context.entry_point.ip = 0x00401000;
	context.configuration.enable_error_messages = FCML_TRUE;

	fcml_st_instruction instruction = {0};
	instruction.mnemonic = "cmps";
	instruction.operands[0].type = FCML_OT_ADDRESS;
	instruction.operands[0].address.segment_selector.segment_selector = fcml_reg_DS;
	instruction.operands[0].address.address_form = FCML_AF_COMBINED;
	instruction.operands[0].address.size_operator = FCML_DS_32;
	instruction.operands[0].address.effective_address.base = fcml_reg_ESI;
	instruction.operands[1].type = FCML_OT_ADDRESS;
	instruction.operands[1].address.segment_selector.segment_selector = fcml_reg_ES;
	instruction.operands[1].address.address_form = FCML_AF_COMBINED;
	instruction.operands[1].address.size_operator = FCML_DS_32;
	instruction.operands[1].address.effective_address.base = fcml_reg_EDI;

	fcml_st_assembler_result result;

	fcml_fn_assembler_result_prepare( &result );

	if( !fcml_fn_assemble( &context, &instruction, &result ) ) {
		STF_ASSERT_PTR_NOT_NULL( result.chosen_instruction );
		if( result.chosen_instruction ) {
			STF_ASSERT_EQUAL( 1, result.chosen_instruction->code_length );
			if( result.chosen_instruction->code_length == 4 ) {
				STF_ASSERT_EQUAL( 0xA7, result.chosen_instruction->code[0] );
			}
		}
	} else {
		STF_FAIL("Can not assemble instruction.");
	}

	fcml_fn_assembler_result_free( &result );

	/* Now try to override ES.*/

	instruction.operands[1].address.segment_selector.segment_selector = fcml_reg_CS;

	if( fcml_fn_assemble( &context, &instruction, &result ) ) {

		STF_ASSERT_PTR_NOT_NULL( result.errors.last_error );
		if( result.errors.last_error ) {
			STF_ASSERT_STRING_EQUAL( "Segment register can not be overridden.", result.errors.last_error->message );
		}

	} else {
		STF_FAIL("Instruction should fail.");
	}

	fcml_fn_assembler_result_free( &result );

}

fcml_stf_test_case fcml_ti_segment_reg[] = {
	{ "fcml_fn_segment_reg", fcml_fn_segment_reg },
	FCML_STF_NULL_TEST
};

fcml_stf_test_suite fcml_si_segment_reg = {
	"suite-fcml-segment_reg", fcml_tf_prefixes_segment_reg_suite_init, fcml_tf_prefixes_segment_reg_suite_cleanup, fcml_ti_segment_reg
};

