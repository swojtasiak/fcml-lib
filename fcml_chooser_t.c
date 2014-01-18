/*
 * fcml_chooser_t.c
 *
 *  Created on: Nov 7, 2013
 *      Author: tas
 */

#include "fcml_chooser_t.h"

#include <CUnit/CUnit.h>
#include <CUnit/TestDB.h>
#include <CUnit/TestRun.h>
#include <fcml_assembler.h>
#include <fcml_ceh.h>
#include <fcml_choosers.h>
#include <fcml_coll.h>
#include <fcml_common.h>
#include <fcml_common_utils.h>
#include <fcml_disassembler.h>
#include <fcml_env.h>
#include <fcml_optimizers.h>
#include <fcml_rend.h>
#include <fcml_stream.h>
#include <fcml_types.h>
#include <stdio.h>

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
	context.assembler = assembler_intel;
	context.addr_form = FCML_AF_32_BIT;
	context.ip.eip = 0x00401000;

	fcml_st_instruction instruction = {0};
	instruction.mnemonic = "adc";
	instruction.operands[0] = FCML_REG( fcml_reg_AX );
	instruction.operands[1] = FCML_IMM16( 0x8042 );

	fcml_st_asm_assembler_result *result;

	if( !fcml_fn_assemble( &context, &instruction, &result ) ) {
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
		fcml_fn_assembler_result_free( result );
	} else {
		CU_FAIL("Can not assemble instruction.");
	}

}

void fcml_fn_chooser_null_optimizer_all_forms(void) {

    // Instruction "adc ax,8042h" can be assembled in two ways.
    // 1: 0x66, 0x15, 0x42, 0x80
    // 2: 0x66, 0x81, 0xd0, 0x42, 0x80
    // Null instruction chooser is responsible for choosing them all. Optimizer should also try all allowed ASA/OSA combinations.

    fcml_ceh_error error;

    fcml_st_asm_assembler_context context = {0};
    context.configuration.optimizer_flags = FCML_OPTF_ALL_FORMS;
    context.configuration.chooser = &fcml_fn_asm_no_instruction_chooser;
    context.assembler = assembler_intel;
    context.addr_form = FCML_AF_32_BIT;
    context.ip.eip = 0x00401000;

    fcml_st_instruction instruction = {0};
    instruction.mnemonic = "adc";
    instruction.operands[0] = FCML_REG( fcml_reg_AX );
    instruction.operands[1] = FCML_IMM16( 0x8042 );

    fcml_st_asm_assembler_result *result;

    if( !fcml_fn_assemble( &context, &instruction, &result ) ) {

        CU_ASSERT_PTR_NULL( result->chosen_instruction );

        // Disassemble and render every instruction available.

        fcml_st_dasm_disassembler_context d_context = {0};
        d_context.addr_form = FCML_AF_32_BIT;
        d_context.disassembler = disassembler_intel;
        d_context.ip.eip = 0x00401000;

        fcml_st_coll_list_element *current_instruction = result->instructions->head;

        fcml_int flags = 0;

        // Iterate over all instructions.
        while( current_instruction ) {

            fcml_st_asm_assembled_instruction *instruction = (fcml_st_asm_assembled_instruction*)current_instruction->item;

            // Disassemble instructions one by one.

            d_context.code = instruction->code;
            d_context.code_length = instruction->code_length;

            fcml_st_dasm_disassembler_result *result;

            error = fcml_fn_disassemble( &d_context, &result );
            if( error ) {
                break;
            }

            // Render instructions one by one.

            fcml_char buffer[512];

            fcml_st_memory_stream buffer_stream = fcml_fn_stream_wrap( buffer, sizeof( buffer ) );

            error = fcml_fn_render( dialect_intel, &buffer_stream, result, FCML_REND_FLAG_RENDER_CODE );
            if( error ) {
                // Free disassemblation result.
                fcml_fn_disassemble_result_free( result );
                break;
            }

            fcml_fn_disassemble_result_free( result );

            if( fcml_fn_env_str_strcmp( FCML_TEXT( "666781d04280 adc ax,32834" ), buffer ) ) {
                flags |= 0x01;
            }

            if( fcml_fn_env_str_strcmp( FCML_TEXT( "6681d04280 adc ax,32834" ), buffer ) ) {
                flags |= 0x02;
            }

            if( fcml_fn_env_str_strcmp( FCML_TEXT( "6667154280 adc ax,32834" ), buffer ) ) {
                flags |= 0x04;
            }

            if( fcml_fn_env_str_strcmp( FCML_TEXT( "66154280 adc ax,32834" ), buffer ) ) {
                flags |= 0x08;
            }

            current_instruction = current_instruction->next;
        }

        fcml_fn_assembler_result_free( result );

        CU_ASSERT_EQUAL( error, 0 );
        CU_ASSERT_EQUAL( flags, 0x0000000F );

    } else {
        CU_FAIL("Can not assemble instruction.");
    }

}

CU_TestInfo fcml_ti_chooser[] = {
    { "fcml_fn_chooser_default", fcml_fn_chooser_default },
    { "fcml_fn_chooser_null_optimizer_all_forms", fcml_fn_chooser_null_optimizer_all_forms },
    CU_TEST_INFO_NULL,
};

CU_SuiteInfo fcml_si_chooser[] = {
    { "suite-fcml-chooser", fcml_tf_chooser_suite_init, fcml_tf_chooser_suite_cleanup, fcml_ti_chooser },
    CU_SUITE_INFO_NULL,
};
