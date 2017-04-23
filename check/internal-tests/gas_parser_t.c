/*
 * FCML - Free Code Manipulation Library.
 * Copyright (C) 2010-2015 Slawomir Wojtasiak
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

#include "gas_parser_t.h"

#include <string.h>

#include <fcml_ceh.h>
#include <fcml_common.h>
#include <fcml_types.h>
#include <fcml_errors.h>
#include <fcml_parser.h>
#include <fcml_gas_dialect.h>

fcml_st_dialect *internal_dialect_gas = NULL;
fcml_st_parser_context internal_gas_context = {0};

fcml_bool fcml_tf_gas_parser_suite_init(void) {
	fcml_fn_dialect_init_gas( FCML_GAS_DIALECT_CF_DEFAULT, &internal_dialect_gas );
	internal_gas_context.dialect = internal_dialect_gas;
	return internal_dialect_gas != NULL;
}

fcml_bool fcml_tf_gas_parser_suite_cleanup(void) {
    if( internal_dialect_gas ) {
        fcml_fn_dialect_free( internal_dialect_gas );
    }
    if( internal_gas_context.symbol_table ) {
    	fcml_fn_symbol_table_free( internal_gas_context.symbol_table );
    }
    return FCML_TRUE;
}

void fcml_tf_parser_gas_parse_test1(void) {
	fcml_st_parser_result result;
	fcml_fn_parser_result_prepare( &result );
	STF_ASSERT_EQUAL( fcml_fn_parse( &internal_gas_context, "mov $80-90", &result ), FCML_CEH_GEC_NO_ERROR );
	if( result.instruction != NULL ) {
		STF_ASSERT_EQUAL( result.instruction->operands[0].type, FCML_OT_IMMEDIATE );
		STF_ASSERT_EQUAL( result.instruction->operands[0].immediate.size, FCML_DS_8 );
		STF_ASSERT_EQUAL( result.instruction->operands[0].immediate.is_signed, FCML_TRUE );
		STF_ASSERT_EQUAL( result.instruction->operands[0].immediate.int8, (fcml_int8_t)-10 );
	} else {
        STF_FAIL();
    }
	fcml_fn_parser_result_free( &result );
}

void fcml_tf_parser_gas_parse_test2(void) {
	fcml_st_parser_result result;
	fcml_fn_parser_result_prepare( &result );
	STF_ASSERT_EQUAL( fcml_fn_parse( &internal_gas_context, "mov (%eax)", &result ), FCML_CEH_GEC_NO_ERROR );
	if( result.instruction != NULL ) {
		STF_ASSERT_EQUAL( result.instruction->operands[0].type, FCML_OT_ADDRESS );
		STF_ASSERT_EQUAL( result.instruction->operands[0].address.address_form, FCML_AF_COMBINED );
		STF_ASSERT_EQUAL( result.instruction->operands[0].address.effective_address.base.size, FCML_DS_32 );
		STF_ASSERT_EQUAL( result.instruction->operands[0].address.effective_address.base.reg, FCML_REG_EAX );
	} else {
        STF_FAIL();
    }
	fcml_fn_parser_result_free( &result );
}

void fcml_tf_parser_gas_parse_test3(void) {
	fcml_st_parser_result result;
	fcml_fn_parser_result_prepare( &result );
	STF_ASSERT_EQUAL( fcml_fn_parse( &internal_gas_context, "movq $1,%cs:(%rax)", &result ), FCML_CEH_GEC_NO_ERROR );
	if( result.instruction != NULL ) {
		STF_ASSERT_EQUAL( result.instruction->operands[0].type, FCML_OT_IMMEDIATE );
		STF_ASSERT_EQUAL( result.instruction->operands[0].immediate.size, FCML_DS_8 );
		STF_ASSERT_EQUAL( result.instruction->operands[0].immediate.is_signed, FCML_FALSE );
		STF_ASSERT_EQUAL( result.instruction->operands[0].immediate.int8, (fcml_uint8_t)(fcml_int8_t)1 );
		STF_ASSERT_EQUAL( result.instruction->operands[1].type, FCML_OT_ADDRESS );
		STF_ASSERT_EQUAL( result.instruction->operands[1].address.address_form, FCML_AF_COMBINED );
		STF_ASSERT_EQUAL( result.instruction->operands[1].address.effective_address.base.size, FCML_DS_64 );
		STF_ASSERT_EQUAL( result.instruction->operands[1].address.effective_address.base.reg, FCML_REG_RAX );
		STF_ASSERT_EQUAL( result.instruction->operands[1].address.segment_selector.segment_selector.reg, FCML_REG_CS );
	} else {
        STF_FAIL();
    }
	fcml_fn_parser_result_free( &result );
}

void fcml_tf_parser_gas_parse_test4(void) {
	fcml_st_parser_result result;
	fcml_fn_parser_result_prepare( &result );
	STF_ASSERT_EQUAL( fcml_fn_parse( &internal_gas_context, "movq $1,%cs:(%rax,%rbx)", &result ), FCML_CEH_GEC_NO_ERROR );
	if( result.instruction != NULL ) {
		STF_ASSERT_EQUAL( result.instruction->operands[0].type, FCML_OT_IMMEDIATE );
		STF_ASSERT_EQUAL( result.instruction->operands[0].immediate.size, FCML_DS_8 );
		STF_ASSERT_EQUAL( result.instruction->operands[0].immediate.is_signed, FCML_FALSE );
		STF_ASSERT_EQUAL( result.instruction->operands[0].immediate.int8, (fcml_int8_t)1 );
		STF_ASSERT_EQUAL( result.instruction->operands[1].type, FCML_OT_ADDRESS );
		STF_ASSERT_EQUAL( result.instruction->operands[1].address.address_form, FCML_AF_COMBINED );
		STF_ASSERT_EQUAL( result.instruction->operands[1].address.effective_address.base.size, FCML_DS_64 );
		STF_ASSERT_EQUAL( result.instruction->operands[1].address.effective_address.base.reg, FCML_REG_RAX );
		STF_ASSERT_EQUAL( result.instruction->operands[1].address.effective_address.index.size, FCML_DS_64 );
		STF_ASSERT_EQUAL( result.instruction->operands[1].address.effective_address.index.reg, FCML_REG_RBX );
		STF_ASSERT_EQUAL( result.instruction->operands[1].address.segment_selector.segment_selector.reg, FCML_REG_CS );
	} else {
        STF_FAIL();
    }
	fcml_fn_parser_result_free( &result );
}

void fcml_tf_parser_gas_parse_test5(void) {
	/* Index only.*/
	fcml_st_parser_result result;
	fcml_fn_parser_result_prepare( &result );
	STF_ASSERT_EQUAL( fcml_fn_parse( &internal_gas_context, "movq $1,%cs:(,%rbx)", &result ), FCML_CEH_GEC_NO_ERROR );
	if( result.instruction != NULL ) {
		STF_ASSERT_EQUAL( result.instruction->operands[0].type, FCML_OT_IMMEDIATE );
		STF_ASSERT_EQUAL( result.instruction->operands[0].immediate.size, FCML_DS_8 );
		STF_ASSERT_EQUAL( result.instruction->operands[0].immediate.is_signed, FCML_FALSE );
		STF_ASSERT_EQUAL( result.instruction->operands[0].immediate.int8, (fcml_int8_t)1 );
		STF_ASSERT_EQUAL( result.instruction->operands[1].type, FCML_OT_ADDRESS );
		STF_ASSERT_EQUAL( result.instruction->operands[1].address.address_form, FCML_AF_COMBINED );
		STF_ASSERT_EQUAL( result.instruction->operands[1].address.effective_address.base.size, FCML_DS_UNDEF );
		STF_ASSERT_EQUAL( result.instruction->operands[1].address.effective_address.base.reg, FCML_REG_UNDEFINED );
		STF_ASSERT_EQUAL( result.instruction->operands[1].address.effective_address.index.size, FCML_DS_64 );
		STF_ASSERT_EQUAL( result.instruction->operands[1].address.effective_address.index.reg, FCML_REG_RBX );
		STF_ASSERT_EQUAL( result.instruction->operands[1].address.segment_selector.segment_selector.reg, FCML_REG_CS );
	} else {
        STF_FAIL();
    }
	fcml_fn_parser_result_free( &result );
}

void fcml_tf_parser_gas_parse_test6(void) {
	/* Index only.*/
	fcml_st_parser_result result;
	fcml_fn_parser_result_prepare( &result );
	STF_ASSERT_EQUAL( fcml_fn_parse( &internal_gas_context, "movq $1,%cs:(,%rbx,4)", &result ), FCML_CEH_GEC_NO_ERROR );
	if( result.instruction != NULL ) {
		STF_ASSERT_EQUAL( result.instruction->operands[0].type, FCML_OT_IMMEDIATE );
		STF_ASSERT_EQUAL( result.instruction->operands[0].immediate.size, FCML_DS_8 );
		STF_ASSERT_EQUAL( result.instruction->operands[0].immediate.is_signed, FCML_FALSE );
		STF_ASSERT_EQUAL( result.instruction->operands[0].immediate.int8, (fcml_int8_t)1 );
		STF_ASSERT_EQUAL( result.instruction->operands[1].type, FCML_OT_ADDRESS );
		STF_ASSERT_EQUAL( result.instruction->operands[1].address.address_form, FCML_AF_COMBINED );
		STF_ASSERT_EQUAL( result.instruction->operands[1].address.effective_address.base.size, FCML_DS_UNDEF );
		STF_ASSERT_EQUAL( result.instruction->operands[1].address.effective_address.base.reg, FCML_REG_UNDEFINED );
		STF_ASSERT_EQUAL( result.instruction->operands[1].address.effective_address.index.size, FCML_DS_64 );
		STF_ASSERT_EQUAL( result.instruction->operands[1].address.effective_address.index.reg, FCML_REG_RBX );
		STF_ASSERT_EQUAL( result.instruction->operands[1].address.effective_address.scale_factor, 4 );
		STF_ASSERT_EQUAL( result.instruction->operands[1].address.segment_selector.segment_selector.reg, FCML_REG_CS );
	} else {
        STF_FAIL();
    }
	fcml_fn_parser_result_free( &result );
}

void fcml_tf_parser_gas_parse_test7(void) {
	/* Index only.*/
	fcml_st_parser_result result;
	fcml_fn_parser_result_prepare( &result );
	STF_ASSERT_NOT_EQUAL( fcml_fn_parse( &internal_gas_context, "movq $1,%cs:(,%rbx,)", &result ), FCML_CEH_GEC_NO_ERROR );
	fcml_fn_parser_result_free( &result );
}

void fcml_tf_parser_gas_parse_test8(void) {
	/* Index only.*/
	fcml_st_parser_result result;
	fcml_fn_parser_result_prepare( &result );
	STF_ASSERT_EQUAL( fcml_fn_parse( &internal_gas_context, "movq $1,%cs:0x100(,%rbx,4)", &result ), FCML_CEH_GEC_NO_ERROR );
	if( result.instruction != NULL ) {
		STF_ASSERT_EQUAL( result.instruction->operands[0].type, FCML_OT_IMMEDIATE );
		STF_ASSERT_EQUAL( result.instruction->operands[0].immediate.size, FCML_DS_8 );
		STF_ASSERT_EQUAL( result.instruction->operands[0].immediate.is_signed, FCML_FALSE );
		STF_ASSERT_EQUAL( result.instruction->operands[0].immediate.int8, (fcml_int8_t)1 );
		STF_ASSERT_EQUAL( result.instruction->operands[1].type, FCML_OT_ADDRESS );
		STF_ASSERT_EQUAL( result.instruction->operands[1].address.address_form, FCML_AF_COMBINED );
		STF_ASSERT_EQUAL( result.instruction->operands[1].address.effective_address.base.size, FCML_DS_UNDEF );
		STF_ASSERT_EQUAL( result.instruction->operands[1].address.effective_address.base.reg, FCML_REG_UNDEFINED );
		STF_ASSERT_EQUAL( result.instruction->operands[1].address.effective_address.index.size, FCML_DS_64 );
		STF_ASSERT_EQUAL( result.instruction->operands[1].address.effective_address.index.reg, FCML_REG_RBX );
		STF_ASSERT_EQUAL( result.instruction->operands[1].address.effective_address.scale_factor, 4 );
		STF_ASSERT_EQUAL( result.instruction->operands[1].address.effective_address.displacement.size, FCML_DS_16 );
		STF_ASSERT_EQUAL( result.instruction->operands[1].address.effective_address.displacement.int16, (fcml_uint16_t)0x100 );
		STF_ASSERT_EQUAL( result.instruction->operands[1].address.segment_selector.segment_selector.reg, FCML_REG_CS );
	} else {
        STF_FAIL();
    }
	fcml_fn_parser_result_free( &result );
}

void fcml_tf_parser_gas_parse_test9(void) {
	/* Index only.*/
	fcml_st_parser_result result;
	fcml_fn_parser_result_prepare( &result );
	STF_ASSERT_EQUAL( fcml_fn_parse( &internal_gas_context, "movq $1,%cs:0x100", &result ), FCML_CEH_GEC_NO_ERROR );
	if( result.instruction != NULL ) {
		STF_ASSERT_EQUAL( result.instruction->operands[0].type, FCML_OT_IMMEDIATE );
		STF_ASSERT_EQUAL( result.instruction->operands[0].immediate.size, FCML_DS_8 );
		STF_ASSERT_EQUAL( result.instruction->operands[0].immediate.is_signed, FCML_FALSE );
		STF_ASSERT_EQUAL( result.instruction->operands[0].immediate.int8, (fcml_int8_t)1 );
		STF_ASSERT_EQUAL( result.instruction->operands[1].type, FCML_OT_ADDRESS );
		STF_ASSERT_EQUAL( result.instruction->operands[1].address.address_form, FCML_AF_OFFSET );
		STF_ASSERT_EQUAL( result.instruction->operands[1].address.offset.size, FCML_DS_16 );
		STF_ASSERT_EQUAL( result.instruction->operands[1].address.offset.off16, (fcml_uint16_t)0x100 );
		STF_ASSERT_EQUAL( result.instruction->operands[1].address.segment_selector.segment_selector.reg, FCML_REG_CS );
	} else {
        STF_FAIL();
    }
	fcml_fn_parser_result_free( &result );
}

void fcml_tf_parser_gas_parse_test10(void) {
	/* Index only.*/
	fcml_st_parser_result result;
	fcml_fn_parser_result_prepare( &result );
	STF_ASSERT_EQUAL( fcml_fn_parse( &internal_gas_context, "movq $1,%cs:0x100(%rax,%rbx,4)", &result ), FCML_CEH_GEC_NO_ERROR );
	if( result.instruction != NULL ) {
		STF_ASSERT_EQUAL( result.instruction->operands[0].type, FCML_OT_IMMEDIATE );
		STF_ASSERT_EQUAL( result.instruction->operands[0].immediate.size, FCML_DS_8 );
		STF_ASSERT_EQUAL( result.instruction->operands[0].immediate.is_signed, FCML_FALSE );
		STF_ASSERT_EQUAL( result.instruction->operands[0].immediate.int8, (fcml_int8_t)1 );
		STF_ASSERT_EQUAL( result.instruction->operands[1].type, FCML_OT_ADDRESS );
		STF_ASSERT_EQUAL( result.instruction->operands[1].address.address_form, FCML_AF_COMBINED );
		STF_ASSERT_EQUAL( result.instruction->operands[1].address.effective_address.base.size, FCML_DS_64 );
		STF_ASSERT_EQUAL( result.instruction->operands[1].address.effective_address.base.reg, FCML_REG_RAX );
		STF_ASSERT_EQUAL( result.instruction->operands[1].address.effective_address.index.size, FCML_DS_64 );
		STF_ASSERT_EQUAL( result.instruction->operands[1].address.effective_address.index.reg, FCML_REG_RBX );
		STF_ASSERT_EQUAL( result.instruction->operands[1].address.effective_address.scale_factor, 4 );
		STF_ASSERT_EQUAL( result.instruction->operands[1].address.effective_address.displacement.size, FCML_DS_16 );
		STF_ASSERT_EQUAL( result.instruction->operands[1].address.effective_address.displacement.int16, (fcml_uint16_t)0x100 );
		STF_ASSERT_EQUAL( result.instruction->operands[1].address.segment_selector.segment_selector.reg, FCML_REG_CS );
	} else {
		STF_FAIL();
	}
	fcml_fn_parser_result_free( &result );
}

void fcml_tf_parser_gas_parse_test11(void) {
	/* RIP only.*/
	fcml_st_parser_result result;
	fcml_fn_parser_result_prepare( &result );
	STF_ASSERT_EQUAL( fcml_fn_parse( &internal_gas_context, "movq $1,0x100(%rip)", &result ), FCML_CEH_GEC_NO_ERROR );
	if( result.instruction != NULL ) {
		STF_ASSERT_EQUAL( result.instruction->operands[0].type, FCML_OT_IMMEDIATE );
		STF_ASSERT_EQUAL( result.instruction->operands[0].immediate.size, FCML_DS_8 );
		STF_ASSERT_EQUAL( result.instruction->operands[0].immediate.is_signed, FCML_FALSE );
		STF_ASSERT_EQUAL( result.instruction->operands[0].immediate.int8, (fcml_int8_t)1 );
		STF_ASSERT_EQUAL( result.instruction->operands[1].type, FCML_OT_ADDRESS );
		STF_ASSERT_EQUAL( result.instruction->operands[1].address.address_form, FCML_AF_COMBINED );
		STF_ASSERT_EQUAL( result.instruction->operands[1].address.effective_address.base.reg, FCML_REG_UNDEFINED );
		STF_ASSERT_EQUAL( result.instruction->operands[1].address.effective_address.base.size, FCML_DS_64 );
		STF_ASSERT_EQUAL( result.instruction->operands[1].address.effective_address.base.type, FCML_REG_IP );
		STF_ASSERT_EQUAL( result.instruction->operands[1].address.effective_address.displacement.size, FCML_DS_16 );
		STF_ASSERT_EQUAL( result.instruction->operands[1].address.effective_address.displacement.int16, (fcml_uint16_t)0x100 );
	} else {
		STF_FAIL();
	}
	fcml_fn_parser_result_free( &result );
}

void fcml_tf_parser_gas_parse_test12(void) {
	fcml_st_parser_result result;
	fcml_fn_parser_result_prepare( &result );
	STF_ASSERT_EQUAL( fcml_fn_parse( &internal_gas_context, "mov *0x80", &result ), FCML_CEH_GEC_NO_ERROR );
	if( result.instruction != NULL ) {
		STF_ASSERT_EQUAL( result.instruction->operands[0].type, FCML_OT_ADDRESS );
		STF_ASSERT_EQUAL( result.instruction->hints, FCML_HINT_INDIRECT_POINTER );
	} else {
        STF_FAIL();
    }
	fcml_fn_parser_result_free( &result );
}

void fcml_tf_parser_gas_parse_test_symbols_1(void) {
	fcml_st_parser_result result;
	fcml_fn_parser_result_prepare( &result );
	fcml_st_parser_context context = {0};
	context.dialect = internal_dialect_gas;
	context.configuration.alloc_symbol_table_if_needed = FCML_TRUE;

	context.ip = 0x401000;

	STF_ASSERT_EQUAL( fcml_fn_parse( &context, FCML_TEXT( "label:" ), &result ), FCML_CEH_GEC_NO_ERROR );
	STF_ASSERT_PTR_NULL( result.instruction );
	STF_ASSERT_PTR_NOT_NULL( result.symbol );
	if( result.symbol ) {
		STF_ASSERT_EQUAL( result.symbol->value, 0x401000 );
		STF_ASSERT_STRING_EQUAL( result.symbol->symbol, FCML_TEXT( "label" ) );
	}

	STF_ASSERT_EQUAL( fcml_fn_parse( &context, FCML_TEXT( "_label:" ), &result ), FCML_CEH_GEC_NO_ERROR );
	STF_ASSERT_PTR_NULL( result.instruction );
	STF_ASSERT_PTR_NOT_NULL( result.symbol );
	if( result.symbol ) {
		STF_ASSERT_EQUAL( result.symbol->value, 0x401000 );
		STF_ASSERT_STRING_EQUAL( result.symbol->symbol, FCML_TEXT( "_label" ) );
	}

	fcml_fn_parser_result_free( &result );
	fcml_fn_symbol_table_free( context.symbol_table );
}

void fcml_tf_parser_gas_parse_test_symbols_2(void) {
	fcml_st_parser_result result;
	fcml_fn_parser_result_prepare( &result );
	fcml_st_parser_context context = {0};
	context.dialect = internal_dialect_gas;
	context.configuration.override_labels = FCML_FALSE;
	context.configuration.alloc_symbol_table_if_needed = FCML_TRUE;
	context.ip = 0x401000;

	STF_ASSERT_EQUAL( fcml_fn_parse( &context, FCML_TEXT( "label: mov %eax,1" ), &result ), FCML_CEH_GEC_NO_ERROR );
	STF_ASSERT_PTR_NOT_NULL( result.instruction );
	if( result.instruction ) {
		STF_ASSERT_STRING_EQUAL( result.instruction->mnemonic, "mov" );
	}
	STF_ASSERT_PTR_NOT_NULL( result.symbol );
	if( result.symbol ) {
		STF_ASSERT_EQUAL( result.symbol->value, 0x401000 );
		STF_ASSERT_STRING_EQUAL( result.symbol->symbol, FCML_TEXT( "label" ) );
	}

	fcml_fn_parser_result_free( &result );
	fcml_fn_symbol_table_free( context.symbol_table );
}

void fcml_tf_parser_gas_parse_test_symbols_3(void) {

	fcml_st_parser_result result;

	fcml_fn_parser_result_prepare( &result );

	fcml_st_parser_context context = {0};
	context.dialect = internal_dialect_gas;
	context.configuration.override_labels = FCML_FALSE;
	context.configuration.alloc_symbol_table_if_needed = FCML_TRUE;
	context.ip = 0x401000;

	STF_ASSERT_EQUAL( fcml_fn_parse( &context, FCML_TEXT( "label: mov %eax,1" ), &result ), FCML_CEH_GEC_NO_ERROR );
	STF_ASSERT_PTR_NOT_NULL( result.instruction );
	if( result.instruction ) {
		STF_ASSERT_STRING_EQUAL( result.instruction->mnemonic, "mov" );
	}
	STF_ASSERT_PTR_NOT_NULL( result.symbol );
	if( result.symbol ) {
		STF_ASSERT_EQUAL( result.symbol->value, 0x401000 );
		STF_ASSERT_STRING_EQUAL( result.symbol->symbol, FCML_TEXT( "label" ) );
	}

	STF_ASSERT_EQUAL( fcml_fn_parse( &context, FCML_TEXT( "label: mov %eax,1" ), &result ), FCML_CEH_GEC_INVALID_INPUT );

	fcml_st_ceh_error_info *error = result.errors.errors;
	STF_ASSERT_PTR_NOT_NULL( error );
	if( error ) {
		STF_ASSERT_EQUAL( error->code, FCML_CEH_MEC_ERROR_SYMBOL_ALREADY_DEFINED );
		STF_ASSERT_STRING_EQUAL( error->message, FCML_TEXT( "Symbol already defined: label." ) );
	}

	context.configuration.override_labels = FCML_TRUE;

	STF_ASSERT_EQUAL( fcml_fn_parse( &context, FCML_TEXT( "label: add %eax,1" ), &result ), FCML_CEH_GEC_NO_ERROR );
	STF_ASSERT_PTR_NOT_NULL( result.instruction );
	if( result.instruction ) {
		STF_ASSERT_STRING_EQUAL( result.instruction->mnemonic, "add" );
	}
	STF_ASSERT_PTR_NOT_NULL( result.symbol );
	if( result.symbol ) {
		STF_ASSERT_EQUAL( result.symbol->value, 0x401000 );
		STF_ASSERT_STRING_EQUAL( result.symbol->symbol, FCML_TEXT( "label" ) );
	}

	fcml_fn_parser_result_free( &result );
	fcml_fn_symbol_table_free( context.symbol_table );
}

/* Undefined symbol. */
void fcml_tf_parser_gas_parse_test_symbols_4(void) {
	fcml_st_parser_result result;
	fcml_fn_parser_result_prepare( &result );
	fcml_st_parser_context context = {0};
	context.dialect = internal_dialect_gas;
	context.configuration.alloc_symbol_table_if_needed = FCML_TRUE;
	context.ip = 0x401000;

	STF_ASSERT_EQUAL( fcml_fn_parse( &context, FCML_TEXT( "label: mov %eax, symbol" ), &result ), FCML_CEH_GEC_UNDEFINED_SYMBOL );
	STF_ASSERT_PTR_NULL( result.instruction );
	STF_ASSERT_PTR_NULL( result.symbol );

	fcml_st_ceh_error_info *error = result.errors.errors;
	STF_ASSERT_PTR_NOT_NULL( error );
	if( error ) {
		STF_ASSERT_EQUAL( error->code, FCML_CEH_MEC_ERROR_UNDEFINED_SYMBOL );
		STF_ASSERT_STRING_EQUAL( error->message, FCML_TEXT( "Undefined symbol: symbol." ) );
	}

	fcml_fn_parser_result_free( &result );
	fcml_fn_symbol_table_free( context.symbol_table );
}

/* Ignore symbols. */
void fcml_tf_parser_gas_parse_test_symbols_5(void) {

	fcml_st_parser_result result;
	fcml_fn_parser_result_prepare( &result );
	fcml_st_parser_context context = {0};
	context.dialect = internal_dialect_gas;
	context.ip = 0x401000;
	context.configuration.ignore_undefined_symbols = FCML_TRUE;
	context.configuration.alloc_symbol_table_if_needed = FCML_TRUE;
	context.configuration.override_labels = FCML_TRUE;

	STF_ASSERT_EQUAL( fcml_fn_parse( &context, FCML_TEXT( "label: mov %eax, $symbol" ), &result ), FCML_CEH_GEC_NO_ERROR );
	STF_ASSERT_PTR_NOT_NULL( result.instruction );
	STF_ASSERT_PTR_NOT_NULL( result.symbol );

	if( result.instruction ) {
		fcml_st_instruction *instruction = result.instruction;
		STF_ASSERT_EQUAL( instruction->operands[1].type, FCML_OT_IMMEDIATE );
		STF_ASSERT_EQUAL( instruction->operands[1].immediate.size, FCML_DS_8 );
		STF_ASSERT_EQUAL( instruction->operands[1].immediate.int8, 0 );
		STF_ASSERT_EQUAL( instruction->operands[1].immediate.is_signed, FCML_TRUE );
	}

	/* Label will be overriden. */
	STF_ASSERT_EQUAL( fcml_fn_parse( &context, FCML_TEXT( "label: mov %eax, symbol" ), &result ), FCML_CEH_GEC_NO_ERROR );
	STF_ASSERT_PTR_NOT_NULL( result.instruction );
	STF_ASSERT_PTR_NOT_NULL( result.symbol );

	if( result.instruction ) {
		fcml_st_instruction *instruction = result.instruction;
		STF_ASSERT_EQUAL( instruction->operands[1].type, FCML_OT_ADDRESS );
		STF_ASSERT_EQUAL( instruction->operands[1].address.address_form, FCML_AF_OFFSET );
	}

	fcml_fn_parser_result_free( &result );
	fcml_fn_symbol_table_free( context.symbol_table );
}

/* Use defined symbol in the instruction. */
void fcml_tf_parser_gas_parse_test_symbols_6(void) {

	fcml_st_parser_result result;
	fcml_fn_parser_result_prepare( &result );
	fcml_st_parser_context context = {0};
	context.dialect = internal_dialect_gas;
	context.ip = 0x401000;
	context.configuration.ignore_undefined_symbols = FCML_TRUE;
	context.configuration.override_labels = FCML_TRUE;
	context.configuration.alloc_symbol_table_if_needed = FCML_TRUE;

	STF_ASSERT_EQUAL( fcml_fn_parse( &context, FCML_TEXT( "label: mov %eax, $label" ), &result ), FCML_CEH_GEC_NO_ERROR );
	STF_ASSERT_PTR_NOT_NULL( result.instruction );
	STF_ASSERT_PTR_NOT_NULL( result.symbol );

	if( result.instruction ) {
		fcml_st_instruction *instruction = result.instruction;
		STF_ASSERT_EQUAL( instruction->operands[1].type, FCML_OT_IMMEDIATE );
		STF_ASSERT_EQUAL( instruction->operands[1].immediate.size, FCML_DS_32 );
		STF_ASSERT_EQUAL( instruction->operands[1].immediate.int32, 0x401000 );
		STF_ASSERT_EQUAL( instruction->operands[1].immediate.is_signed, FCML_TRUE );
	}

	fcml_fn_parser_result_free( &result );
	fcml_fn_symbol_table_free( context.symbol_table );
}

/* Pseudo operations operands parsing. */
void fcml_tf_parser_gas_parse_test_pseudo_operation_1(void) {

	fcml_st_parser_result result;
	fcml_fn_parser_result_prepare( &result );
	fcml_st_parser_context context = {0};
	context.dialect = internal_dialect_gas;
	context.ip = 0x401000;
	context.configuration.ignore_undefined_symbols = FCML_TRUE;
	context.configuration.override_labels = FCML_TRUE;
	context.configuration.alloc_symbol_table_if_needed = FCML_TRUE;

	STF_ASSERT_EQUAL( fcml_fn_parse( &context, FCML_TEXT( "label: .byte 0x12" ), &result ), FCML_CEH_GEC_NO_ERROR );
	STF_ASSERT_PTR_NOT_NULL( result.instruction );
	STF_ASSERT_PTR_NOT_NULL( result.symbol );

	if( result.instruction ) {
		fcml_st_instruction *instruction = result.instruction;
		STF_ASSERT_STRING_EQUAL( ".byte", result.instruction->mnemonic );
		STF_ASSERT_EQUAL( 1, instruction->operands_count );
		STF_ASSERT_EQUAL( instruction->operands[0].type, FCML_OT_IMMEDIATE );
		STF_ASSERT_EQUAL( instruction->operands[0].immediate.size, FCML_DS_8 );
		STF_ASSERT_EQUAL( instruction->operands[0].immediate.int8, 0x12 );
		STF_ASSERT_EQUAL( instruction->operands[0].immediate.is_signed, FCML_FALSE );
	}

	fcml_fn_parser_result_free( &result );
	fcml_fn_symbol_table_free( context.symbol_table );
}

/* Pseudo operations operands parsing. */
void fcml_tf_parser_gas_parse_test_pseudo_operation_2(void) {

	fcml_st_parser_result result;
	fcml_fn_parser_result_prepare( &result );
	fcml_st_parser_context context = {0};
	context.dialect = internal_dialect_gas;
	context.ip = 0x401000;
	context.configuration.ignore_undefined_symbols = FCML_TRUE;
	context.configuration.override_labels = FCML_TRUE;
	context.configuration.alloc_symbol_table_if_needed = FCML_TRUE;

	STF_ASSERT_EQUAL( fcml_fn_parse( &context, FCML_TEXT( "label: .byte %rax" ), &result ), FCML_CEH_GEC_INVALID_INPUT );
	STF_ASSERT_PTR_NULL( result.instruction );
	STF_ASSERT_PTR_NULL( result.symbol );

	fcml_fn_parser_result_free( &result );
	fcml_fn_symbol_table_free( context.symbol_table );
}

void fcml_tf_parser_gas_parse_test_decorator_bcast(void) {
    fcml_st_parser_result result;
    fcml_fn_parser_result_prepare(&result);
    STF_ASSERT_EQUAL(
            fcml_fn_parse(&internal_gas_context, "vaddpd (%eax){1to8}",
                    &result), FCML_CEH_GEC_NO_ERROR);
    if (result.instruction != NULL) {
        fcml_st_operand *operand = &(result.instruction->operands[0]);
        STF_ASSERT_EQUAL(operand->type, FCML_OT_ADDRESS);
        STF_ASSERT_EQUAL(operand->address.address_form, FCML_AF_COMBINED);
        STF_ASSERT_EQUAL(operand->address.effective_address.base.type,
                FCML_REG_GPR);
        STF_ASSERT_EQUAL(operand->address.effective_address.base.reg,
                FCML_REG_EAX);
        STF_ASSERT_EQUAL(operand->decorators.bcast.is_not_null, FCML_TRUE);
        STF_ASSERT_EQUAL(operand->decorators.bcast.value, 8);
    } else {
        STF_FAIL();
    }
    fcml_fn_parser_result_free(&result);
}

void fcml_tf_parser_gas_parse_test_decorator_opmask(void) {
    fcml_st_parser_result result;
    fcml_fn_parser_result_prepare(&result);
    STF_ASSERT_EQUAL(
            fcml_fn_parse(&internal_gas_context, "vaddpd %zmm1{%k1}",
                    &result), FCML_CEH_GEC_NO_ERROR);
    if (result.instruction != NULL) {
        fcml_st_operand *operand = &(result.instruction->operands[0]);
        STF_ASSERT_EQUAL(operand->type, FCML_OT_REGISTER);
        STF_ASSERT_EQUAL(operand->reg.type, FCML_REG_SIMD);
        STF_ASSERT_EQUAL(operand->reg.reg, FCML_REG_ZMM1);
        STF_ASSERT_EQUAL(operand->reg.size, FCML_DS_512);
        STF_ASSERT_EQUAL(operand->decorators.operand_mask_reg.type,
                FCML_REG_OPMASK);
        STF_ASSERT_EQUAL(operand->decorators.operand_mask_reg.size,
                FCML_DS_64);
        STF_ASSERT_EQUAL(operand->decorators.operand_mask_reg.reg,
                FCML_REG_K1);
        STF_ASSERT_EQUAL(operand->decorators.z, FCML_FALSE);

    } else {
        STF_FAIL();
    }
    fcml_fn_parser_result_free(&result);
}

void fcml_tf_parser_gas_parse_test_decorator_opmask_k(void) {
    fcml_st_parser_result result;
    fcml_fn_parser_result_prepare(&result);
    STF_ASSERT_EQUAL(
            fcml_fn_parse(&internal_gas_context, "vaddpd %zmm31{%k4}{z}",
                    &result), FCML_CEH_GEC_NO_ERROR);
    if (result.instruction != NULL) {
        fcml_st_operand *operand = &(result.instruction->operands[0]);
        STF_ASSERT_EQUAL(operand->type, FCML_OT_REGISTER);
        STF_ASSERT_EQUAL(operand->reg.type, FCML_REG_SIMD);
        STF_ASSERT_EQUAL(operand->reg.reg, FCML_REG_ZMM31);
        STF_ASSERT_EQUAL(operand->reg.size, FCML_DS_512);
        STF_ASSERT_EQUAL(operand->decorators.operand_mask_reg.type,
                FCML_REG_OPMASK);
        STF_ASSERT_EQUAL(operand->decorators.operand_mask_reg.size,
                FCML_DS_64);
        STF_ASSERT_EQUAL(operand->decorators.operand_mask_reg.reg,
                FCML_REG_K4);
        STF_ASSERT_EQUAL(operand->decorators.z, FCML_TRUE);
    } else {
        STF_FAIL();
    }
    fcml_fn_parser_result_free(&result);
}

void fcml_tf_parser_gas_parse_test_decorator_er(void) {
    fcml_st_parser_result result;
    fcml_fn_parser_result_prepare(&result);
    STF_ASSERT_EQUAL(
            fcml_fn_parse(&internal_gas_context, "vaddpd {ru-sae}",
                    &result), FCML_CEH_GEC_NO_ERROR);
    if (result.instruction != NULL) {
        fcml_st_operand *operand = &(result.instruction->operands[0]);
        STF_ASSERT_EQUAL(operand->type, FCML_OT_VIRTUAL);
        STF_ASSERT_EQUAL(operand->decorators.er.is_not_null, FCML_TRUE);
        STF_ASSERT_EQUAL(operand->decorators.er.value, FCML_ER_RU_SAE);
    } else {
        STF_FAIL();
    }
    fcml_fn_parser_result_free(&result);
}

void fcml_tf_parser_gas_parse_test_decorator_sae(void) {
    fcml_st_parser_result result;
    fcml_fn_parser_result_prepare(&result);
    STF_ASSERT_EQUAL(
            fcml_fn_parse(&internal_gas_context, "vaddpd {sae}",
                    &result), FCML_CEH_GEC_NO_ERROR);
    if (result.instruction != NULL) {
        fcml_st_operand *operand = &(result.instruction->operands[0]);
        STF_ASSERT_EQUAL(operand->type, FCML_OT_VIRTUAL);
        STF_ASSERT_EQUAL(operand->decorators.sea, FCML_TRUE);
    } else {
        STF_FAIL();
    }
    fcml_fn_parser_result_free(&result);
}

fcml_stf_test_case fcml_ti_parser_gas[] = {
	{ "fcml_tf_parser_gas_parse_test1", fcml_tf_parser_gas_parse_test1 },
	{ "fcml_tf_parser_gas_parse_test2", fcml_tf_parser_gas_parse_test2 },
	{ "fcml_tf_parser_gas_parse_test3", fcml_tf_parser_gas_parse_test3 },
	{ "fcml_tf_parser_gas_parse_test4", fcml_tf_parser_gas_parse_test4 },
	{ "fcml_tf_parser_gas_parse_test5", fcml_tf_parser_gas_parse_test5 },
	{ "fcml_tf_parser_gas_parse_test6", fcml_tf_parser_gas_parse_test6 },
	{ "fcml_tf_parser_gas_parse_test7", fcml_tf_parser_gas_parse_test7 },
	{ "fcml_tf_parser_gas_parse_test8", fcml_tf_parser_gas_parse_test8 },
	{ "fcml_tf_parser_gas_parse_test9", fcml_tf_parser_gas_parse_test9 },
	{ "fcml_tf_parser_gas_parse_test10", fcml_tf_parser_gas_parse_test10 },
	{ "fcml_tf_parser_gas_parse_test11", fcml_tf_parser_gas_parse_test11 },
	{ "fcml_tf_parser_gas_parse_test12", fcml_tf_parser_gas_parse_test12 },
	{ "fcml_tf_parser_gas_parse_test_symbols_1", fcml_tf_parser_gas_parse_test_symbols_1 },
	{ "fcml_tf_parser_gas_parse_test_symbols_2", fcml_tf_parser_gas_parse_test_symbols_2 },
	{ "fcml_tf_parser_gas_parse_test_symbols_3", fcml_tf_parser_gas_parse_test_symbols_3 },
	{ "fcml_tf_parser_gas_parse_test_symbols_4", fcml_tf_parser_gas_parse_test_symbols_4 },
	{ "fcml_tf_parser_gas_parse_test_symbols_5", fcml_tf_parser_gas_parse_test_symbols_5 },
	{ "fcml_tf_parser_gas_parse_test_symbols_6", fcml_tf_parser_gas_parse_test_symbols_6 },
	{ "fcml_tf_parser_gas_parse_test_pseudo_operation_1", fcml_tf_parser_gas_parse_test_pseudo_operation_1 },
	{ "fcml_tf_parser_gas_parse_test_pseudo_operation_2", fcml_tf_parser_gas_parse_test_pseudo_operation_2 },
	{ "fcml_tf_parser_gas_parse_test_decorator_bcast",
            fcml_tf_parser_gas_parse_test_decorator_bcast },
    { "fcml_tf_parser_gas_parse_test_decorator_opmask",
            fcml_tf_parser_gas_parse_test_decorator_opmask },
    { "fcml_tf_parser_gas_parse_test_decorator_opmask_k",
            fcml_tf_parser_gas_parse_test_decorator_opmask_k },
    { "fcml_tf_parser_gas_parse_test_decorator_er",
            fcml_tf_parser_gas_parse_test_decorator_er },
    { "fcml_tf_parser_gas_parse_test_decorator_sae",
            fcml_tf_parser_gas_parse_test_decorator_sae },
	FCML_STF_NULL_TEST
};

fcml_stf_test_suite fcml_si_gas_parser = {
	"suite-fcml-parser-gas", fcml_tf_gas_parser_suite_init, fcml_tf_gas_parser_suite_cleanup, fcml_ti_parser_gas
};
