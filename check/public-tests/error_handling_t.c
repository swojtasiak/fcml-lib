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

#include "error_handling_t.h"

#include <string.h>

#include "instructions_base_t.h"

#include <fcml_assembler.h>
#include <fcml_parser.h>

/* Helper methods */

fcml_st_assembler_context fcml_ifn_prepare_context( fcml_en_operating_mode op_mode ) {
	fcml_st_assembler_context context = {0};
	context.assembler = assembler_intel;
	context.entry_point.op_mode = op_mode;
	context.entry_point.ip = 0x00401000;
	context.configuration.enable_error_messages = FCML_TRUE;
	return context;
}

fcml_bool fcml_check_error_message( fcml_st_ceh_error_container errors, fcml_string message, fcml_ceh_error error_code ) {
	fcml_bool result = FCML_FALSE;
	fcml_st_ceh_error_info *error = errors.errors;
	while( error ) {
		if( error->code == error_code && strcmp( error->message, message ) == 0 ) {
			result = FCML_TRUE;
			break;
		}
		error = error->next_error;
	}
	return result;
}

fcml_bool fcml_tf_check_errors( fcml_string mnemonic, fcml_string message, fcml_ceh_error message_error_code, fcml_ceh_error error_code ) {

	fcml_bool result = FCML_TRUE;

	fcml_st_assembler_context context = fcml_ifn_prepare_context( FCML_OM_32_BIT );

	fcml_st_parser_result parsed_instruction;

	fcml_fn_parser_result_prepare( &parsed_instruction );

	fcml_st_assembler_result assembler_result;

	fcml_fn_assembler_result_prepare( &assembler_result );

	fcml_st_parser_context parser_context = {0};
	parser_context.dialect = dialect_intel;

	while( FCML_TRUE ) {

		if( fcml_fn_parse( &parser_context, mnemonic, &parsed_instruction ) ) {
			STF_FAIL("Parsing failed.");
			break;
		}

		fcml_ceh_error error = fcml_fn_assemble( &context, parsed_instruction.instruction, &assembler_result );

		if( error != error_code ) {
			result = FCML_FALSE;
		} else {
			result = fcml_check_error_message( assembler_result.errors, message, message_error_code );
		}

		break;
	}

	fcml_fn_parser_result_free( &parsed_instruction );

	fcml_fn_assembler_result_free( &assembler_result );

	fcml_fn_symbol_table_free( parser_context.symbol_table );

	return result;
}

/* Test suite initialization. */

fcml_bool fcml_tf_error_handling_suite_init(void) {
	return FCML_TRUE;
}

fcml_bool fcml_tf_error_handling_suite_cleanup(void) {
	return FCML_TRUE;
}

/* Tests. */

void fcml_tf_error_handling_explicit_reg_addressing(void) {
	STF_ASSERT( fcml_tf_check_errors( "repne cmps dword ptr [si],byte ptr cs:[di]", FCML_TEXT("Invalid operand size."), FCML_CEH_GEC_INVALID_OPPERAND_SIZE, FCML_CEH_GEC_INVALID_OPPERAND_SIZE ) );
	STF_ASSERT( fcml_tf_check_errors( "repne cmps byte ptr [si],byte ptr cs:[di]", FCML_TEXT("Segment register can not be overridden."), FCML_CEH_MEC_ERROR_ILLEGAL_SEG_REG_OVERRIDE, FCML_CEH_GEC_INVALID_REGISTER ) );
	STF_ASSERT( fcml_tf_check_errors( "repne cmps byte ptr [si],byte ptr [edi]", FCML_TEXT("Invalid address size."), FCML_CEH_GEC_INVALID_ADDRESS_SIZE, FCML_CEH_GEC_INVALID_ADDRESS_SIZE ) );
}

fcml_stf_test_case fcml_ti_error_handling[] = {
	{ "fcml_tf_error_handling_explicit_reg_addressing", fcml_tf_error_handling_explicit_reg_addressing },
	FCML_STF_NULL_TEST
};

fcml_stf_test_suite fcml_si_error_handling = {
	"suite-fcml-error-handling", fcml_tf_error_handling_suite_init, fcml_tf_error_handling_suite_cleanup, fcml_ti_error_handling
};
