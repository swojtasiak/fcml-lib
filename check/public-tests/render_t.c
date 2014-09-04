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

#include "render_t.h"

#include <stdio.h>
#include <string.h>

#include <fcml_renderer.h>
#include <fcml_intel_dialect.h>
#include <fcml_gas_dialect.h>

#include "instructions_base_t.h"

fcml_bool fcml_ifn_render_test_disassemble_intel( fcml_st_disassembler_result *dasm_result, fcml_uint8_t *code, fcml_usize code_size ) {

	fcml_st_disassembler_context d_context = {0};
	d_context.entry_point.op_mode = FCML_OM_32_BIT;
	d_context.entry_point.ip = 0x00401000;
	d_context.disassembler = disassembler_intel;
	d_context.code = code;
	d_context.code_length = code_size;

	fcml_fn_disassembler_result_prepare( dasm_result );

	fcml_ceh_error error = fcml_fn_disassemble( &d_context, dasm_result );
	if( error ) {
		STF_FAIL("Disassembling failed.");
		return FCML_FALSE;
	}

	return FCML_TRUE;
}

fcml_bool fcml_ifn_render_test_disassemble_gas( fcml_st_disassembler_result *dasm_result, fcml_uint8_t *code, fcml_usize code_size ) {

	fcml_st_disassembler_context d_context = {0};
	d_context.entry_point.op_mode = FCML_OM_32_BIT;
	d_context.entry_point.ip = 0x00401000;
	d_context.disassembler = disassembler_gas;
	d_context.code = code;
	d_context.code_length = code_size;

	fcml_fn_disassembler_result_prepare( dasm_result );

	fcml_ceh_error error = fcml_fn_disassemble( &d_context, dasm_result );
	if( error ) {
		STF_FAIL("Disassembling failed.");
		return FCML_FALSE;
	}

	return FCML_TRUE;
}

fcml_bool fcml_tf_render_suite_init(void) {
	return FCML_TRUE;
}

fcml_bool fcml_tf_render_suite_cleanup(void) {
	return FCML_TRUE;
}

void fcml_fn_render_paddings_leading_zeroes_intel(void) {

	fcml_uint8_t code[] = { 0x80, 0x54, 0x01, 0x02, 0x03 };

	fcml_st_disassembler_result dasm_result;

	if( !fcml_ifn_render_test_disassemble_intel( &dasm_result, code, sizeof( code ) ) ) {
		return;
	}

	fcml_st_render_config config = {0};
	config.render_flags = FCML_REND_FLAG_REMOVE_LEADING_ZEROS | FCML_REND_FLAG_HEX_IMM | FCML_REND_FLAG_HEX_DISPLACEMENT;

	fcml_char buffer[FCML_REND_MAX_BUFF_LEN];

	fcml_ceh_error error = fcml_fn_render( dialect_intel, &config, buffer, sizeof( buffer ), &dasm_result );
	if( error ) {
		STF_FAIL("Rendering failed.");
		return;
	}

	STF_ASSERT_STRING_EQUAL( buffer, "adc byte ptr [ecx+eax+2h],3h" );

	fcml_fn_disassembler_result_free( &dasm_result );
}

void fcml_fn_render_paddings_leading_zeroes_intel_2(void) {

	fcml_uint8_t code[] = { 0x83, 0x15, 0x00, 0x00, 0x00, 0x00, 0x03 };

	fcml_st_disassembler_result dasm_result;

	if( !fcml_ifn_render_test_disassemble_intel( &dasm_result, code, sizeof( code ) ) ) {
		return;
	}

	fcml_st_render_config config = {0};
	config.render_flags = FCML_REND_FLAG_REMOVE_LEADING_ZEROS | FCML_REND_FLAG_HEX_IMM | FCML_REND_FLAG_HEX_DISPLACEMENT;

	fcml_char buffer[FCML_REND_MAX_BUFF_LEN];

	fcml_ceh_error error = fcml_fn_render( dialect_intel, &config, buffer, sizeof( buffer ), &dasm_result );
	if( error ) {
		STF_FAIL("Rendering failed.");
		return;
	}

	STF_ASSERT_STRING_EQUAL( buffer, "adc dword ptr [0h],3h" );

	fcml_fn_disassembler_result_free( &dasm_result );
}

void fcml_fn_render_paddings_leading_zeroes_gas(void) {

	fcml_uint8_t code[] = { 0x80, 0x54, 0x01, 0x02, 0x03 };

	fcml_st_disassembler_result dasm_result;

	if( !fcml_ifn_render_test_disassemble_gas( &dasm_result, code, sizeof( code ) ) ) {
		return;
	}

	fcml_st_render_config config = {0};
	config.render_flags = FCML_REND_FLAG_REMOVE_LEADING_ZEROS | FCML_REND_FLAG_HEX_IMM | FCML_REND_FLAG_HEX_DISPLACEMENT;

	fcml_char buffer[FCML_REND_MAX_BUFF_LEN];

	fcml_ceh_error error = fcml_fn_render( dialect_gas, &config, buffer, sizeof( buffer ), &dasm_result );
	if( error ) {
		STF_FAIL("Rendering failed.");
		return;
	}

	STF_ASSERT_STRING_EQUAL( buffer, "adcb $0x3,0x2(%ecx,%eax)" );

	fcml_fn_disassembler_result_free( &dasm_result );
}

void fcml_fn_render_paddings_intel(void) {

	fcml_uint8_t code[] = { 0x66, 0x81, 0xd0, 0x42, 0x80 };

	fcml_st_disassembler_result dasm_result;

	if( !fcml_ifn_render_test_disassemble_intel( &dasm_result, code, sizeof( code ) ) ) {
		return;
	}

	fcml_st_render_config config = {0};
	config.render_flags = FCML_REND_FLAG_CODE_PADDING | FCML_REND_FLAG_MNEMONIC_PADDING | FCML_REND_FLAG_RENDER_CODE;
	config.prefered_code_padding = 10;
	config.prefered_mnemonic_padding = 8;

	fcml_char buffer[FCML_REND_MAX_BUFF_LEN];

	fcml_ceh_error error = fcml_fn_render( dialect_intel, &config, buffer, sizeof( buffer ), &dasm_result );
	if( error ) {
		STF_FAIL("Rendering failed.");
		return;
	}

	STF_ASSERT_STRING_EQUAL( buffer, "6681d04280          adc     ax,-32702" );

	// Padding length equal to code and mnemonic.

	config.prefered_code_padding = 5;
	config.prefered_mnemonic_padding = 3;

	error = fcml_fn_render( dialect_intel, &config, buffer, sizeof( buffer ), &dasm_result );
	if( error ) {
		STF_FAIL("Rendering failed.");
		return;
	}

	STF_ASSERT_STRING_EQUAL( buffer, "6681d04280 adc ax,-32702" );

	// Paddings less than rendered mnemonic and code.

	config.prefered_code_padding = 1;
	config.prefered_mnemonic_padding = 1;

	error = fcml_fn_render( dialect_intel, &config, buffer, sizeof( buffer ), &dasm_result );
	if( error ) {
		STF_FAIL("Rendering failed.");
		return;
	}

	STF_ASSERT_STRING_EQUAL( buffer, "6681d04280 adc ax,-32702" );

	fcml_fn_disassembler_result_free( &dasm_result );
}

void fcml_fn_render_paddings_intel_lock(void) {

	fcml_uint8_t code[] = { 0xF0, 0x80, 0x15, 0x01, 0x02, 0x03, 0x04, 0xff };

	fcml_st_disassembler_result dasm_result;

	if( !fcml_ifn_render_test_disassemble_intel( &dasm_result, code, sizeof( code ) ) ) {
		return;
	}

	fcml_st_render_config config = {0};
	config.render_flags = FCML_REND_FLAG_CODE_PADDING | FCML_REND_FLAG_MNEMONIC_PADDING | FCML_REND_FLAG_RENDER_CODE;
	config.prefered_code_padding = 10;
	config.prefered_mnemonic_padding = 8;

	fcml_char buffer[FCML_REND_MAX_BUFF_LEN];

	fcml_ceh_error error = fcml_fn_render( dialect_intel, &config, buffer, sizeof( buffer ), &dasm_result );
	if( error ) {
		STF_FAIL("Rendering failed.");
		return;
	}

	STF_ASSERT_STRING_EQUAL( buffer, "f0801501020304ff    lock adc byte ptr [04030201h],-1" );

	fcml_fn_disassembler_result_free( &dasm_result );
}

void fcml_fn_render_paddings_gas(void) {

	fcml_uint8_t code[] = { 0x66, 0x81, 0xd0, 0x42, 0x80 };

	fcml_st_disassembler_result dasm_result;

	if( !fcml_ifn_render_test_disassemble_gas( &dasm_result, code, sizeof( code ) ) ) {
		return;
	}

	fcml_st_render_config config = {0};
	config.render_flags = FCML_REND_FLAG_CODE_PADDING | FCML_REND_FLAG_MNEMONIC_PADDING | FCML_REND_FLAG_RENDER_CODE;
	config.prefered_code_padding = 10;
	config.prefered_mnemonic_padding = 8;

	fcml_char buffer[FCML_REND_MAX_BUFF_LEN];

	fcml_ceh_error error = fcml_fn_render( dialect_gas, &config, buffer, sizeof( buffer ), &dasm_result );
	if( error ) {
		STF_FAIL("Rendering failed.");
		return;
	}

	STF_ASSERT_STRING_EQUAL( buffer, "6681d04280          adc     $-32702,%ax" );

	// Padding length equal to code and mnemonic.

	config.prefered_code_padding = 5;
	config.prefered_mnemonic_padding = 3;

	error = fcml_fn_render( dialect_gas, &config, buffer, sizeof( buffer ), &dasm_result );
	if( error ) {
		STF_FAIL("Rendering failed.");
		return;
	}

	STF_ASSERT_STRING_EQUAL( buffer, "6681d04280 adc $-32702,%ax" );

	// Paddings less than rendered mnemonic and code.

	config.prefered_code_padding = 1;
	config.prefered_mnemonic_padding = 1;

	error = fcml_fn_render( dialect_gas, &config, buffer, sizeof( buffer ), &dasm_result );
	if( error ) {
		STF_FAIL("Rendering failed.");
		return;
	}

	STF_ASSERT_STRING_EQUAL( buffer, "6681d04280 adc $-32702,%ax" );

	fcml_fn_disassembler_result_free( &dasm_result );
}

fcml_stf_test_case fcml_ti_render[] = {
	{ "fcml_fn_render_paddings_leading_zeroes_intel", fcml_fn_render_paddings_leading_zeroes_intel },
	{ "fcml_fn_render_paddings_leading_zeroes_intel_2", fcml_fn_render_paddings_leading_zeroes_intel_2 },
	{ "fcml_fn_render_paddings_leading_zeroes_gas", fcml_fn_render_paddings_leading_zeroes_gas },
	{ "fcml_fn_render_paddings_intel", fcml_fn_render_paddings_intel },
	{ "fcml_fn_render_paddings_intel_lock", fcml_fn_render_paddings_intel_lock },
	{ "fcml_fn_render_paddings_gas", fcml_fn_render_paddings_gas },
	FCML_STF_NULL_TEST
};

fcml_stf_test_suite fcml_si_render = {
	"suite-fcml-render", fcml_tf_render_suite_init, fcml_tf_render_suite_cleanup, fcml_ti_render
};
