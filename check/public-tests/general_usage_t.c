/*
 * general_usage_t.h
 *
 *  Created on: May 25, 2014
 *      Author: tas
 */


#include "general_usage_t.h"

#include <fcml_gas_dialect.h>
#include <fcml_intel_dialect.h>
#include <fcml_assembler.h>
#include <fcml_disassembler.h>
#include <fcml_common_utils.h>

fcml_st_dialect *gu_intel_dialect;
fcml_st_dialect *gu_gas_dialect;

fcml_st_assembler *gu_intel_assembler;
fcml_st_assembler *gu_gas_assembler;

fcml_st_disassembler *gu_intel_disassembler;
fcml_st_disassembler *gu_gas_disassembler;

fcml_st_assembler_context gu_i32ctx = { 0 };
fcml_st_assembler_context gu_g32ctx = { 0 };
fcml_st_assembler_context gu_i64ctx = { 0 };
fcml_st_assembler_context gu_g64ctx = { 0 };

fcml_st_disassembler_context gu_di32ctx = { 0 };
fcml_st_disassembler_context gu_dg32ctx = { 0 };
fcml_st_disassembler_context gu_di64ctx = { 0 };
fcml_st_disassembler_context gu_dg64ctx = { 0 };

fcml_st_disassembler_result dis_result;
fcml_st_assembler_result asm_result;

fcml_bool fcml_tf_general_usage_suite_init(void) {

	fcml_fn_assembler_result_prepare( &asm_result );

	fcml_fn_disassembler_result_free( &dis_result );

	if( fcml_fn_dialect_init_intel( FCML_INTEL_DIALECT_CF_DEFAULT, &gu_intel_dialect ) ) {
		return FCML_FALSE;
	}

	if( fcml_fn_dialect_init_gas( FCML_GAS_DIALECT_CF_DEFAULT, &gu_gas_dialect ) ) {
		fcml_fn_dialect_free( gu_intel_dialect );
		return FCML_FALSE;
	}

	if( fcml_fn_assembler_init( gu_intel_dialect, &gu_intel_assembler ) ) {
		fcml_fn_dialect_free( gu_intel_dialect );
		fcml_fn_dialect_free( gu_gas_dialect );
		return FCML_FALSE;
	}

	if( fcml_fn_assembler_init( gu_gas_dialect, &gu_gas_assembler ) ) {
		fcml_fn_assembler_free( gu_intel_assembler );
		fcml_fn_dialect_free( gu_intel_dialect );
		fcml_fn_dialect_free( gu_gas_dialect );
		return FCML_FALSE;
	}

	if( fcml_fn_disassembler_init( gu_intel_dialect, &gu_intel_disassembler ) ) {
		fcml_fn_assembler_free( gu_intel_assembler );
		fcml_fn_assembler_free( gu_gas_assembler );
		fcml_fn_dialect_free( gu_intel_dialect );
		fcml_fn_dialect_free( gu_gas_dialect );
		return FCML_FALSE;
	}

	if( fcml_fn_disassembler_init( gu_gas_dialect, &gu_gas_disassembler ) ) {
		fcml_fn_disassembler_free( gu_intel_disassembler );
		fcml_fn_assembler_free( gu_intel_assembler );
		fcml_fn_assembler_free( gu_gas_assembler );
		fcml_fn_dialect_free( gu_intel_dialect );
		fcml_fn_dialect_free( gu_gas_dialect );
		return FCML_FALSE;
	}

	gu_i32ctx.assembler = gu_intel_assembler;
	gu_i32ctx.entry_point.ip = 0x00401000;
	gu_i32ctx.entry_point.op_mode = FCML_OM_32_BIT;

	gu_g32ctx.assembler = gu_gas_assembler;
	gu_g32ctx.entry_point.ip = 0x00401000;
	gu_g32ctx.entry_point.op_mode = FCML_OM_32_BIT;

	gu_i64ctx.assembler = gu_intel_assembler;
	gu_i64ctx.entry_point.ip = 0x000000013FB40000LL;
	gu_i64ctx.entry_point.op_mode = FCML_OM_64_BIT;

	gu_g64ctx.assembler = gu_gas_assembler;
	gu_g64ctx.entry_point.ip = 0x000000013FB40000LL;
	gu_g64ctx.entry_point.op_mode = FCML_OM_64_BIT;

	gu_di32ctx.disassembler = gu_intel_disassembler;
	gu_di32ctx.entry_point.ip = 0x00401000;
	gu_di32ctx.entry_point.op_mode = FCML_OM_32_BIT;

	gu_dg32ctx.disassembler = gu_gas_disassembler;
	gu_dg32ctx.entry_point.ip = 0x00401000;
	gu_dg32ctx.entry_point.op_mode = FCML_OM_32_BIT;

	gu_di64ctx.disassembler = gu_intel_disassembler;
	gu_di64ctx.entry_point.ip = 0x000000013FB40000LL;
	gu_di64ctx.entry_point.op_mode = FCML_OM_64_BIT;

	gu_dg64ctx.disassembler = gu_gas_disassembler;
	gu_dg64ctx.entry_point.ip = 0x000000013FB40000LL;
	gu_dg64ctx.entry_point.op_mode = FCML_OM_64_BIT;

	return FCML_TRUE;
}

fcml_bool fcml_tf_general_usage_suite_cleanup(void) {
	fcml_fn_assembler_result_free( &asm_result );
	fcml_fn_disassembler_result_free( &dis_result );
	fcml_fn_disassembler_free( gu_intel_disassembler );
	fcml_fn_disassembler_free( gu_gas_disassembler );
	fcml_fn_assembler_free( gu_intel_assembler );
	fcml_fn_assembler_free( gu_gas_assembler );
	fcml_fn_dialect_free( gu_intel_dialect );
	fcml_fn_dialect_free( gu_gas_dialect );
	return FCML_TRUE;
}

fcml_uint8_t fcml_iarr_general_usage_disassemble_multiple_code[] = {
    0x3F,
    0x80, 0xD0, 0x42,
    0x66, 0x81, 0xd0, 0x42, 0x80
};

void fcml_fn_general_usage_disassemble_multiple() {

    fcml_usize code_length = sizeof( fcml_iarr_general_usage_disassemble_multiple_code );

    gu_di32ctx.configuration.increment_ip = FCML_TRUE;
    gu_di32ctx.code = fcml_iarr_general_usage_disassemble_multiple_code;
    gu_di32ctx.code_length = code_length;
    gu_di32ctx.entry_point.ip = 0x401000;

    STF_ASSERT_EQUAL( fcml_fn_disassemble( &gu_di32ctx, &dis_result ), FCML_CEH_GEC_NO_ERROR );

    STF_ASSERT_EQUAL( gu_di32ctx.code_length, 8 );
    STF_ASSERT_EQUAL( gu_di32ctx.entry_point.ip, 0x00401001 );

    STF_ASSERT_EQUAL( fcml_fn_disassemble( &gu_di32ctx, &dis_result ), FCML_CEH_GEC_NO_ERROR );

    STF_ASSERT_EQUAL( gu_di32ctx.code_length, 5 );
    STF_ASSERT_EQUAL( gu_di32ctx.entry_point.ip, 0x00401004 );

    STF_ASSERT_EQUAL( fcml_fn_disassemble( &gu_di32ctx, &dis_result ), FCML_CEH_GEC_NO_ERROR );

    STF_ASSERT_EQUAL( gu_di32ctx.code_length, 0 );
    STF_ASSERT_EQUAL( gu_di32ctx.entry_point.ip, 0x00401009 );

    STF_ASSERT_EQUAL( fcml_fn_disassemble( &gu_di32ctx, &dis_result ), FCML_CEH_GEC_EOF );

    fcml_fn_disassembler_result_free( &dis_result );

}

fcml_uint8_t fcml_iarr_general_usage_disassemble_unknown_instruction[] = {
    0x3F,
    0x82, // Unknown instruction disassembled to "db".
    0x80, 0xD0, 0x42,
    0x66, 0x81, 0xd0, 0x42, 0x80
};

void fcml_fn_general_usage_unknown_instruction() {

    fcml_usize code_length = sizeof( fcml_iarr_general_usage_disassemble_unknown_instruction );

    gu_di32ctx.configuration.increment_ip = FCML_TRUE;
    gu_di32ctx.configuration.fail_if_unknown_instruction = FCML_FALSE;
    gu_di32ctx.code = fcml_iarr_general_usage_disassemble_unknown_instruction;
    gu_di32ctx.code_length = code_length;
    gu_di32ctx.entry_point.ip = 0x401000;

    STF_ASSERT_EQUAL( fcml_fn_disassemble( &gu_di32ctx, &dis_result ), FCML_CEH_GEC_NO_ERROR );

    STF_ASSERT_EQUAL( gu_di32ctx.code_length, 9 );
    STF_ASSERT_EQUAL( gu_di32ctx.entry_point.ip, 0x00401001 );

    STF_ASSERT_EQUAL( fcml_fn_disassemble( &gu_di32ctx, &dis_result ), FCML_CEH_GEC_NO_ERROR );

    STF_ASSERT_EQUAL( gu_di32ctx.code_length, 8 );
    STF_ASSERT_EQUAL( gu_di32ctx.entry_point.ip, 0x00401002 );

    STF_ASSERT_EQUAL( fcml_fn_disassemble( &gu_di32ctx, &dis_result ), FCML_CEH_GEC_NO_ERROR );

    STF_ASSERT_EQUAL( gu_di32ctx.code_length, 5 );
    STF_ASSERT_EQUAL( gu_di32ctx.entry_point.ip, 0x00401005 );

    STF_ASSERT_EQUAL( fcml_fn_disassemble( &gu_di32ctx, &dis_result ), FCML_CEH_GEC_NO_ERROR );

    STF_ASSERT_EQUAL( gu_di32ctx.code_length, 0 );
    STF_ASSERT_EQUAL( gu_di32ctx.entry_point.ip, 0x0040100A );

    STF_ASSERT_EQUAL( fcml_fn_disassemble( &gu_di32ctx, &dis_result ), FCML_CEH_GEC_EOF );

    fcml_fn_disassembler_result_free( &dis_result );

}

void fcml_fn_general_usage_change_offset(void) {

	fcml_ceh_error error;

	// Before:
	//  adc byte ptr [04030201h],0ffh (0x80, 0x15, 0x01, 0x02, 0x03, 0x04, 0xff)
	// After:
	//  adc byte ptr [05000000h],0ffh (0x80, 0x15, 0x00, 0x00, 0x00, 0x05, 0xFF)

	fcml_uint8_t code[] = { 0x80, 0x15, 0x01, 0x02, 0x03, 0x04, 0xff };

	gu_di32ctx.code = code;
	gu_di32ctx.code_length = sizeof( code );

	error = fcml_fn_disassemble( &gu_di32ctx, &dis_result );
	STF_ASSERT_EQUAL( FCML_CEH_GEC_NO_ERROR, error );

	if( !error ) {

		STF_ASSERT( dis_result.instruction_details.instruction_group & FCML_AMT_GPI );
		STF_ASSERT( FCML_IS_INSTRUCTION_GROUP( dis_result, FCML_AMT_GPI ) );
		STF_ASSERT( !FCML_IS_INSTRUCTION_GROUP( dis_result, FCML_AMT_FPU ) );
		STF_ASSERT( FCML_IS_INSTRUCTION_CODE( dis_result, F_ADC ) );
		STF_ASSERT( !FCML_IS_INSTRUCTION_CODE( dis_result, F_MOV ) );
		STF_ASSERT_EQUAL( F_ADC, dis_result.instruction_details.instruction );

		fcml_st_operand *operand = fcml_fn_cu_find_operand( &(dis_result.instruction ), FCML_OT_ADDRESS );
		if( operand && operand->address.address_form == FCML_AF_OFFSET ) {

			*operand = fcml_fn_cu_operand_addr_offset_32( 0x05000000, operand->address.size_operator );

			error = fcml_fn_assemble( &gu_i32ctx, &(dis_result.instruction), &asm_result );
			if( !error ) {
				fcml_st_assembled_instruction *chosen_instruction = asm_result.chosen_instruction;
				STF_ASSERT_EQUAL( 0x80, chosen_instruction->code[0] );
				STF_ASSERT_EQUAL( 0x15, chosen_instruction->code[1] );
				STF_ASSERT_EQUAL( 0x00, chosen_instruction->code[2] );
				STF_ASSERT_EQUAL( 0x00, chosen_instruction->code[3] );
				STF_ASSERT_EQUAL( 0x00, chosen_instruction->code[4] );
				STF_ASSERT_EQUAL( 0x05, chosen_instruction->code[5] );
				STF_ASSERT_EQUAL( 0xFF, chosen_instruction->code[6] );
			} else {
				STF_FAIL("Can not assemble instruction.");
			}
		} else {
			STF_FAIL("Address operand not found.");
		}

	}

}

fcml_stf_test_case fcml_ti_general_usage[] = {
	{ "fcml_fn_general_usage_change_offset", fcml_fn_general_usage_change_offset },
	{ "fcml_fn_general_usage_disassemble_multiple", fcml_fn_general_usage_disassemble_multiple },
	{ "fcml_fn_general_usage_unknown_instruction", fcml_fn_general_usage_unknown_instruction },
	FCML_STF_NULL_TEST
};

fcml_stf_test_suite fcml_si_general_usage = {
	"suite-fcml-general-usage", fcml_tf_general_usage_suite_init, fcml_tf_general_usage_suite_cleanup, fcml_ti_general_usage
};

