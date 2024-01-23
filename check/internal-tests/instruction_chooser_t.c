/*
 * FCML - Free Code Manipulation Library.
 * Copyright (C) 2010-2024 Slawomir Wojtasiak
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

#include "common_utils_t.h"

#include <fcml_assembler.h>
#include <fcml_choosers.h>

static void fcml_ifn_chooser_extract(fcml_ptr instruction,
        fcml_st_instruction_code *instruction_code) {
		fcml_st_assembled_instruction *inst = 
			  (fcml_st_assembled_instruction*)instruction;
		instruction_code->code = inst->code;
		instruction_code->code_length = inst->code_length;
		instruction_code->details = inst->details;
}

static fcml_ptr fcml_ifn_chooser_next(fcml_ptr instruction) {
	fcml_st_assembled_instruction *inst = 
			  (fcml_st_assembled_instruction*)instruction;
	return inst->next;
}

fcml_bool fcml_tf_instruction_chooser_suite_init(void) {
	return FCML_TRUE;
}

fcml_bool fcml_tf_instruction_chooser_suite_cleanup(void) {
	return FCML_TRUE;
}

void fcml_tf_instruction_chooser_no_override(void) {
	fcml_uint8_t code1[4] = {0x01, 0x02, 0x03, 0x04};
	fcml_st_assembled_instruction instruction1 = {0};
	instruction1.code = &code1[0];
	instruction1.code_length = 4;
	instruction1.details.asa_override = FCML_FALSE;
	instruction1.details.osa_override = FCML_FALSE;
	instruction1.details.instruction_group = FCML_AMT_GPI;

	fcml_uint8_t code2[3] = {0x01, 0x02, 0x03};
	fcml_st_assembled_instruction instruction2 = {0};
	instruction2.code = &code2[0];
	instruction2.code_length = 3;
	instruction2.details.asa_override = FCML_FALSE;
	instruction2.details.osa_override = FCML_FALSE;
	instruction2.details.instruction_group = FCML_AMT_GPI;

	fcml_uint8_t code3[5] = {0x01, 0x02, 0x03, 0x04, 0x05};
	fcml_st_assembled_instruction instruction3 = {0};
	instruction3.code = &code3[0];
	instruction3.code_length = 5;
	instruction3.details.asa_override = FCML_FALSE;
	instruction3.details.osa_override = FCML_FALSE;
	instruction3.details.instruction_group = FCML_AMT_GPI;

	instruction1.next = &instruction2;
	instruction2.next = &instruction3;

	fcml_st_chooser_context context = {0};
	context.extract = &fcml_ifn_chooser_extract;
	context.next = &fcml_ifn_chooser_next;
	context.instruction = &instruction1;

	fcml_ptr choosen = fcml_fn_asm_default_instruction_chooser(&context);

	STF_ASSERT_PTR_NOT_NULL( choosen );
	STF_ASSERT_EQUAL( choosen, &instruction2 );
}

void fcml_tf_instruction_chooser_no_override_one(void) {
	fcml_uint8_t code1[4] = {0x01, 0x02, 0x03, 0x04};
	fcml_st_assembled_instruction instruction1 = {0};
	instruction1.code = &code1[0];
	instruction1.code_length = 4;
	instruction1.details.asa_override = FCML_FALSE;
	instruction1.details.osa_override = FCML_FALSE;
	instruction1.details.instruction_group = FCML_AMT_GPI;

	fcml_st_chooser_context context = {0};
	context.extract = &fcml_ifn_chooser_extract;
	context.next = &fcml_ifn_chooser_next;
	context.instruction = &instruction1;

	fcml_ptr choosen = fcml_fn_asm_default_instruction_chooser(&context);

	STF_ASSERT_PTR_NOT_NULL( choosen );
	STF_ASSERT_EQUAL( choosen, &instruction1 );
}

void fcml_tf_instruction_chooser_no_override_has_higher_priority_osa(void) {
	fcml_uint8_t code1[4] = {0x01, 0x02, 0x03, 0x04};
	fcml_st_assembled_instruction instruction1 = {0};
	instruction1.code = &code1[0];
	instruction1.code_length = 4;
	instruction1.details.asa_override = FCML_FALSE;
	instruction1.details.osa_override = FCML_FALSE;
	instruction1.details.instruction_group = FCML_AMT_GPI;

	fcml_uint8_t code2[3] = {0x01, 0x02, 0x03};
	fcml_st_assembled_instruction instruction2 = {0};
	instruction2.code = &code2[0];
	instruction2.code_length = 3;
	instruction2.details.asa_override = FCML_TRUE;
	instruction2.details.osa_override = FCML_FALSE;
	instruction2.details.instruction_group = FCML_AMT_GPI;

	fcml_uint8_t code3[5] = {0x01, 0x02, 0x03, 0x04, 0x05};
	fcml_st_assembled_instruction instruction3 = {0};
	instruction3.code = &code3[0];
	instruction3.code_length = 5;
	instruction3.details.asa_override = FCML_FALSE;
	instruction3.details.osa_override = FCML_FALSE;
	instruction3.details.instruction_group = FCML_AMT_GPI;

	instruction1.next = &instruction2;
	instruction2.next = &instruction3;

	fcml_st_chooser_context context = {0};
	context.extract = &fcml_ifn_chooser_extract;
	context.next = &fcml_ifn_chooser_next;
	context.instruction = &instruction1;
	
	fcml_ptr choosen = fcml_fn_asm_default_instruction_chooser(&context);

	STF_ASSERT_PTR_NOT_NULL( choosen );
	STF_ASSERT_EQUAL( choosen, &instruction1 );
}

void fcml_tf_instruction_chooser_no_override_has_higher_priority_asa(void) {
	fcml_uint8_t code1[4] = {0x01, 0x02, 0x03, 0x04};
	fcml_st_assembled_instruction instruction1 = {0};
	instruction1.code = &code1[0];
	instruction1.code_length = 4;
	instruction1.details.asa_override = FCML_FALSE;
	instruction1.details.osa_override = FCML_FALSE;
	instruction1.details.instruction_group = FCML_AMT_GPI;

	fcml_uint8_t code2[3] = {0x01, 0x02, 0x03};
	fcml_st_assembled_instruction instruction2 = {0};
	instruction2.code = &code2[0];
	instruction2.code_length = 3;
	instruction2.details.asa_override = FCML_FALSE;
	instruction2.details.osa_override = FCML_TRUE;
	instruction2.details.instruction_group = FCML_AMT_GPI;

	fcml_uint8_t code3[5] = {0x01, 0x02, 0x03, 0x04, 0x05};
	fcml_st_assembled_instruction instruction3 = {0};
	instruction3.code = &code3[0];
	instruction3.code_length = 5;
	instruction3.details.asa_override = FCML_FALSE;
	instruction3.details.osa_override = FCML_FALSE;
	instruction3.details.instruction_group = FCML_AMT_GPI;

	instruction1.next = &instruction2;
	instruction2.next = &instruction3;

	fcml_st_chooser_context context = {0};
	context.extract = &fcml_ifn_chooser_extract;
	context.next = &fcml_ifn_chooser_next;
	context.instruction = &instruction1;
	
	fcml_ptr choosen = fcml_fn_asm_default_instruction_chooser(&context);

	STF_ASSERT_PTR_NOT_NULL( choosen );
	STF_ASSERT_EQUAL( choosen, &instruction1 );
}

void fcml_tf_instruction_chooser_no_override_has_higher_priority_one(void) {
	fcml_uint8_t code1[4] = {0x01, 0x02, 0x03, 0x04};
	fcml_st_assembled_instruction instruction1 = {0};
	instruction1.code = &code1[0];
	instruction1.code_length = 4;
	instruction1.details.asa_override = FCML_TRUE;
	instruction1.details.osa_override = FCML_TRUE;
	instruction1.details.instruction_group = FCML_AMT_GPI;

	fcml_st_chooser_context context = {0};
	context.extract = &fcml_ifn_chooser_extract;
	context.next = &fcml_ifn_chooser_next;
	context.instruction = &instruction1;
	
	fcml_ptr choosen = fcml_fn_asm_default_instruction_chooser(&context);

	STF_ASSERT_PTR_NOT_NULL( choosen );
	STF_ASSERT_EQUAL( choosen, &instruction1 );
}

void fcml_tf_instruction_chooser_ignore_override_for_non_gpi(void) {
	fcml_uint8_t code1[4] = {0x01, 0x02, 0x03, 0x04};
	fcml_st_assembled_instruction instruction1 = {0};
	instruction1.code = &code1[0];
	instruction1.code_length = 4;
	instruction1.details.asa_override = FCML_FALSE;
	instruction1.details.osa_override = FCML_FALSE;
	instruction1.details.instruction_group = FCML_AMT_AVX2;

	fcml_uint8_t code2[3] = {0x01, 0x02, 0x03};
	fcml_st_assembled_instruction instruction2 = {0};
	instruction2.code = &code2[0];
	instruction2.code_length = 3;
	instruction2.details.asa_override = FCML_TRUE;
	instruction2.details.osa_override = FCML_FALSE;
	instruction2.details.instruction_group = FCML_AMT_AVX2;

	fcml_uint8_t code3[5] = {0x01, 0x02, 0x03, 0x04, 0x05};
	fcml_st_assembled_instruction instruction3 = {0};
	instruction3.code = &code3[0];
	instruction3.code_length = 5;
	instruction3.details.asa_override = FCML_FALSE;
	instruction3.details.osa_override = FCML_FALSE;
	instruction3.details.instruction_group = FCML_AMT_AVX2;

	instruction1.next = &instruction2;
	instruction2.next = &instruction3;

	fcml_st_chooser_context context = {0};
	context.extract = &fcml_ifn_chooser_extract;
	context.next = &fcml_ifn_chooser_next;
	context.instruction = &instruction1;
	
	fcml_ptr choosen = fcml_fn_asm_default_instruction_chooser(&context);

	STF_ASSERT_PTR_NOT_NULL( choosen );
	STF_ASSERT_EQUAL( choosen, &instruction2 );
}

fcml_stf_test_case fcml_ti_instruction_chooser[] = {
	{ "fcml_tf_instruction_chooser_no_override", fcml_tf_instruction_chooser_no_override },
	{ "fcml_tf_instruction_chooser_no_override_has_higher_priority_osa", fcml_tf_instruction_chooser_no_override_has_higher_priority_osa },
	{ "fcml_tf_instruction_chooser_no_override_has_higher_priority_asa", fcml_tf_instruction_chooser_no_override_has_higher_priority_asa },
	{ "fcml_tf_instruction_chooser_ignore_override_for_non_gpi", fcml_tf_instruction_chooser_ignore_override_for_non_gpi },
	{ "fcml_tf_instruction_chooser_no_override_one", fcml_tf_instruction_chooser_no_override_one },
	{ "fcml_tf_instruction_chooser_no_override_has_higher_priority_one", fcml_tf_instruction_chooser_no_override_has_higher_priority_one },
	FCML_STF_NULL_TEST
};

fcml_stf_test_suite fcml_si_instruction_chooser = {
	"suite-fcml-instruction-chooser", fcml_tf_instruction_chooser_suite_init, fcml_tf_instruction_chooser_suite_cleanup, fcml_ti_instruction_chooser
};

