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

#include "hints_t.h"

#include <fcml_renderer.h>

#include "instructions_base_t.h"

fcml_bool fcml_tf_hints_suite_init(void) {
	return FCML_TRUE;
}

fcml_bool fcml_tf_hints_suite_cleanup(void) {
	return FCML_TRUE;
}

void fcml_fn_hints_sib(void) {
	FCML_I32( "add dword ptr [eax+00000001h],eax", 0x01, 0x40, 0x01 );
	FCML_A32( "add %eax,0x00000001(%eax)", 0x01, 0x40, 0x01 );
	FCML_I32_A( "add dword ptr [sib eax+00000001h],eax", 0x01, 0x44, 0x20, 0x01 );
	FCML_A32_D( "add %eax,0x00000001(%eax)", 0x01, 0x44, 0x20, 0x01 );
	FCML_I32( "add dword ptr [eax],eax", 0x01, 0x00 );
	FCML_I32_A( "add dword ptr [sib eax],eax", 0x01, 0x04, 0x20 );
}

void fcml_fn_hints_rip(void) {
	/* RIP enabled by default.*/
	FCML_I64_RIP_A( "rcl byte ptr [0000800000401007h],03h", 0xC0, 0x15, 0x00, 0x00, 0x00, 0x00, 0x03 );
	/* RIP by default, absolute forced, take into account that SIB encoding was used to encode it.*/
	FCML_I64_RIP_A( "rcl byte ptr [abs 0000000000401007h],03h", 0xc0, 0x14, 0x25, 0x07, 0x10, 0x40, 0x00, 0x03 );
	/* Offset is too big to be encoded as absolute offset.*/
	FCML_I64_A_FAILED( "rcl byte ptr [0000800000401007h],03h", 0xC0, 0x15, 0x00, 0x00, 0x00, 0x00, 0x03 );
	/* Absolute offset enabled by default.*/
	FCML_I64( "rcl byte ptr [0000000000401007h],03h", 0xc0, 0x14, 0x25, 0x07, 0x10, 0x40, 0x00, 0x03 );
	/* In 32 bit mode, SIB is not needed, so it is not used by default, but...*/
	FCML_I32( "rcl byte ptr [00401007h],03h", 0xc0, 0x15, 0x07, 0x10, 0x40, 0x00, 0x03 );
	/* we can force it.*/
	FCML_I32_A( "rcl byte ptr [sib 00401007h],03h", 0xc0, 0x14, 0x25, 0x07, 0x10, 0x40, 0x00, 0x03 );
	/* It's interesting combination. RIP should be used by default, but SIB hint was used. Hints have higher precedence*/
	/* so it forced absolute address to be used (Because absolute offset is encoded using SIB). In this case SIB hint works like the ABS one.*/
	FCML_I64_RIP_A( "rcl byte ptr [sib 00401007h],03h", 0xc0, 0x14, 0x25, 0x07, 0x10, 0x40, 0x00, 0x03 );
	/* Absolute by default but RIP forced.*/
	FCML_I64_A( "rcl byte ptr [rel 0000800000401007h],03h", 0xc0, 0x15, 0x00, 0x00, 0x00, 0x00, 0x03 );
	/* Hints rendering.*/
	FCML_I64_RF( "rcl byte ptr [rel 0000800000401007h],03h", FCML_REND_FLAG_RENDER_REL_HINT, 0xc0, 0x15, 0x00, 0x00, 0x00, 0x00, 0x03 );
	FCML_I64_RF( "rcl byte ptr [abs 0000000000401007h],03h", FCML_REND_FLAG_RENDER_ABS_HINT, 0xc0, 0x14, 0x25, 0x07, 0x10, 0x40, 0x00, 0x03 );
}

void fcml_fn_hints_indirect_addressing(void) {

	/* 1: 0xFF, 0x25, 0x01, 0x10, 0x40, 0x00 (jmp dword [00401001h])
	 * By default indirect addressing is chosen.
	 */

	fcml_st_assembler_context context = {0};
	context.assembler = assembler_intel;
	context.entry_point.op_mode = FCML_OM_32_BIT;
	context.entry_point.ip = 0x00401000;

	fcml_st_instruction instruction = {0};
	instruction.mnemonic = "jmp";
	instruction.operands[0].type = FCML_OT_ADDRESS;
	instruction.operands[0].address.address_form = FCML_AF_OFFSET;
	instruction.operands[0].address.size_operator = FCML_DS_32;
	instruction.operands[0].address.offset.off32 = 0x00401001;
	instruction.operands[0].address.offset.size = FCML_DS_32;
	instruction.operands_count = 1;

	fcml_st_assembler_result result;

	fcml_fn_assembler_result_prepare( &result );

	fcml_ceh_error error;
	if( !( error = fcml_fn_assemble( &context, &instruction, &result ) ) ) {
		STF_ASSERT_PTR_NOT_NULL( result.chosen_instruction );
		if( result.chosen_instruction ) {
			STF_ASSERT_EQUAL( 6, result.chosen_instruction->code_length );
			if( result.chosen_instruction->code_length == 6 ) {
				STF_ASSERT_EQUAL( 0xFF, result.chosen_instruction->code[0] );
				STF_ASSERT_EQUAL( 0x25, result.chosen_instruction->code[1] );
				STF_ASSERT_EQUAL( 0x01, result.chosen_instruction->code[2] );
				STF_ASSERT_EQUAL( 0x10, result.chosen_instruction->code[3] );
				STF_ASSERT_EQUAL( 0x40, result.chosen_instruction->code[4] );
				STF_ASSERT_EQUAL( 0x00, result.chosen_instruction->code[5] );
			}
		}
		fcml_fn_assembler_result_free( &result );
	} else {
		STF_FAIL("Can not assemble instruction.");
	}
}


void fcml_fn_hints_direct_addressing(void) {

	/* 1: 0xeb, 0xff (jmp 00401001h)
	 * Forcing indirect addressing.
	 */

	fcml_st_assembler_context context = {0};
	context.assembler = assembler_intel;
	context.entry_point.op_mode = FCML_OM_32_BIT;
	context.entry_point.ip = 0x00401000;

	fcml_st_instruction instruction = {0};
	instruction.mnemonic = "jmp";
	instruction.operands[0].type = FCML_OT_ADDRESS;
	instruction.operands[0].address.address_form = FCML_AF_OFFSET;
	instruction.operands[0].address.offset.off32 = 0x00401001;
	instruction.operands[0].address.offset.size = FCML_DS_32;
	instruction.hints |= FCML_HINT_DIRECT_POINTER;
	instruction.operands_count = 1;

	fcml_st_assembler_result result;

	fcml_fn_assembler_result_prepare( &result );

	fcml_ceh_error error;
	if( !( error = fcml_fn_assemble( &context, &instruction, &result ) ) ) {
		STF_ASSERT_PTR_NOT_NULL( result.chosen_instruction );
		if( result.chosen_instruction ) {
			STF_ASSERT_EQUAL( 2, result.chosen_instruction->code_length );
			if( result.chosen_instruction->code_length == 2 ) {
				STF_ASSERT_EQUAL( 0xEB, result.chosen_instruction->code[0] );
				STF_ASSERT_EQUAL( 0xFF, result.chosen_instruction->code[1] );
			}
		}
		fcml_fn_assembler_result_free( &result );
	} else {
		STF_FAIL("Can not assemble instruction.");
	}

}


fcml_stf_test_case fcml_ti_hints[] = {
	{ "fcml_fn_hints_sib", fcml_fn_hints_sib },
	{ "fcml_fn_hints_rip", fcml_fn_hints_rip },
	{ "fcml_fn_hints_indirect_addressing", fcml_fn_hints_indirect_addressing },
	{ "fcml_fn_hints_direct_addressing", fcml_fn_hints_direct_addressing },
	FCML_STF_NULL_TEST
};

fcml_stf_test_suite fcml_si_hints = {
	"suite-fcml-hints", fcml_tf_hints_suite_init, fcml_tf_hints_suite_cleanup, fcml_ti_hints
};



