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

#include "intel_parser_t.h"

#include <string.h>

#include <fcml_ceh.h>
#include <fcml_common.h>
#include <fcml_types.h>
#include <fcml_errors.h>
#include <fcml_parser.h>
#include <fcml_parser_int.h>
#include <fcml_intel_dialect.h>

fcml_st_dialect *internal_dialect_intel = NULL;
fcml_st_parser_context internal_intel_context = {0};

fcml_bool fcml_tf_parser_suite_init(void) {
	fcml_fn_dialect_init_intel( FCML_INTEL_DIALECT_CF_DEFAULT, &internal_dialect_intel );
	internal_intel_context.dialect = internal_dialect_intel;
	return internal_dialect_intel != NULL;
}

fcml_bool fcml_tf_parser_suite_cleanup(void) {
	if( internal_dialect_intel ) {
		fcml_fn_dialect_free( internal_dialect_intel );
	}
	fcml_fn_symbol_table_free( internal_intel_context.symbol_table );
	return FCML_TRUE;
}

void fcml_tf_parser_int_parse_test1(void) {
	fcml_st_parser_result result;
	fcml_fn_parser_result_prepare( &result );
	STF_ASSERT_EQUAL( fcml_fn_parse( &internal_intel_context, "mov 80-90", &result ), FCML_CEH_GEC_NO_ERROR );
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

void fcml_tf_parser_int_parse_test2(void) {
	fcml_st_parser_result result;
	fcml_fn_parser_result_prepare( &result );
	STF_ASSERT_EQUAL( fcml_fn_parse( &internal_intel_context, "mov 0xFF", &result ), FCML_CEH_GEC_NO_ERROR );
	if( result.instruction != NULL ) {
		STF_ASSERT_EQUAL( result.instruction->operands[0].type, FCML_OT_IMMEDIATE );
		STF_ASSERT_EQUAL( result.instruction->operands[0].immediate.size, FCML_DS_8 );
		STF_ASSERT_EQUAL( result.instruction->operands[0].immediate.is_signed, FCML_FALSE );
		STF_ASSERT_EQUAL( result.instruction->operands[0].immediate.int8, (fcml_int8_t)0xFF );
	} else {
        STF_FAIL();
    }
	fcml_fn_parser_result_free( &result );
}

void fcml_tf_parser_int_parse_test3(void) {
	fcml_st_parser_result result;
	fcml_fn_parser_result_prepare( &result );
	STF_ASSERT_EQUAL( fcml_fn_parse( &internal_intel_context, "mov 0xFFF", &result ), FCML_CEH_GEC_NO_ERROR );
	if( result.instruction != NULL ) {
		STF_ASSERT_EQUAL( result.instruction->operands[0].type, FCML_OT_IMMEDIATE );
		STF_ASSERT_EQUAL( result.instruction->operands[0].immediate.size, FCML_DS_16 );
		STF_ASSERT_EQUAL( result.instruction->operands[0].immediate.is_signed, FCML_FALSE );
		STF_ASSERT_EQUAL( result.instruction->operands[0].immediate.int16, (fcml_uint16_t)0x0FFF );
	} else {
        STF_FAIL();
    }
	fcml_fn_parser_result_free( &result );
}

void fcml_tf_parser_int_parse_test4(void) {
	fcml_st_parser_result result;
	fcml_fn_parser_result_prepare( &result );
	STF_ASSERT_EQUAL( fcml_fn_parse( &internal_intel_context, "mov 0xFFFF", &result ), FCML_CEH_GEC_NO_ERROR );
	if( result.instruction != NULL ) {
		STF_ASSERT_EQUAL( result.instruction->operands[0].type, FCML_OT_IMMEDIATE );
		STF_ASSERT_EQUAL( result.instruction->operands[0].immediate.size, FCML_DS_16 );
		STF_ASSERT_EQUAL( result.instruction->operands[0].immediate.is_signed, FCML_FALSE );
		STF_ASSERT_EQUAL( result.instruction->operands[0].immediate.int16, (fcml_int16_t)0xFFFF );
	} else {
        STF_FAIL();
    }
	fcml_fn_parser_result_free( &result );
}

void fcml_tf_parser_int_parse_test5(void) {
	fcml_st_parser_result result;
	fcml_fn_parser_result_prepare( &result );
	STF_ASSERT_EQUAL( fcml_fn_parse( &internal_intel_context, "mov 0xFFFFF", &result ), FCML_CEH_GEC_NO_ERROR );
	if( result.instruction != NULL ) {
		STF_ASSERT_EQUAL( result.instruction->operands[0].type, FCML_OT_IMMEDIATE );
		STF_ASSERT_EQUAL( result.instruction->operands[0].immediate.size, FCML_DS_32 );
		STF_ASSERT_EQUAL( result.instruction->operands[0].immediate.is_signed, FCML_FALSE );
		STF_ASSERT_EQUAL( result.instruction->operands[0].immediate.int32, (fcml_uint32_t)0x000FFFFF );
	} else {
        STF_FAIL();
    }
	fcml_fn_parser_result_free( &result );
}

void fcml_tf_parser_int_parse_test6(void) {
	fcml_st_parser_result result;
	fcml_fn_parser_result_prepare( &result );
	STF_ASSERT_EQUAL( fcml_fn_parse( &internal_intel_context, "mov 0xFFFFFFFF", &result ), FCML_CEH_GEC_NO_ERROR );
	if( result.instruction != NULL ) {
		STF_ASSERT_EQUAL( result.instruction->operands[0].type, FCML_OT_IMMEDIATE );
		STF_ASSERT_EQUAL( result.instruction->operands[0].immediate.size, FCML_DS_32 );
		STF_ASSERT_EQUAL( result.instruction->operands[0].immediate.is_signed, FCML_FALSE );
		STF_ASSERT_EQUAL( result.instruction->operands[0].immediate.int32, (fcml_uint32_t)0xFFFFFFFF );
	} else {
	    STF_FAIL();
    }
	fcml_fn_parser_result_free( &result );
}

void fcml_tf_parser_int_parse_test7(void) {
	fcml_st_parser_result result;
	fcml_fn_parser_result_prepare( &result );
	STF_ASSERT_EQUAL( fcml_fn_parse( &internal_intel_context, "mov 0xFFFFFFFFFFFFFFFF", &result ), FCML_CEH_GEC_NO_ERROR );
	if( result.instruction != NULL ) {
		STF_ASSERT_EQUAL( result.instruction->operands[0].type, FCML_OT_IMMEDIATE );
		STF_ASSERT_EQUAL( result.instruction->operands[0].immediate.size, FCML_DS_64 );
		STF_ASSERT_EQUAL( result.instruction->operands[0].immediate.is_signed, FCML_FALSE );
		STF_ASSERT_EQUAL( result.instruction->operands[0].immediate.int64, 0xFFFFFFFFFFFFFFFFUL );
	} else {
        STF_FAIL();
    }
	fcml_fn_parser_result_free( &result );
}

void fcml_tf_parser_int_parse_test8(void) {
	fcml_st_parser_result result;
	fcml_fn_parser_result_prepare( &result );
	STF_ASSERT_EQUAL( fcml_fn_parse( &internal_intel_context, "mov -0xFFFFFFFFFFFFFFFF", &result ), FCML_CEH_GEC_NO_ERROR );
	if( result.instruction != NULL ) {
		STF_ASSERT_EQUAL( result.instruction->operands[0].type, FCML_OT_IMMEDIATE );
		STF_ASSERT_EQUAL( result.instruction->operands[0].immediate.size, FCML_DS_8 );
		STF_ASSERT_EQUAL( result.instruction->operands[0].immediate.is_signed, FCML_FALSE );
		STF_ASSERT_EQUAL( result.instruction->operands[0].immediate.int8, (fcml_uint8_t)(fcml_int8_t)1 );
	} else {
        STF_FAIL();
    }
	fcml_fn_parser_result_free( &result );
}

void fcml_tf_parser_int_parse_test9(void) {
	fcml_st_parser_result result;
	fcml_fn_parser_result_prepare( &result );
	STF_ASSERT_EQUAL( fcml_fn_parse( &internal_intel_context, "mov -0xFF", &result ), FCML_CEH_GEC_NO_ERROR );
	if( result.instruction != NULL ) {
		STF_ASSERT_EQUAL( result.instruction->operands[0].type, FCML_OT_IMMEDIATE );
		STF_ASSERT_EQUAL( result.instruction->operands[0].immediate.size, FCML_DS_16 );
		STF_ASSERT_EQUAL( result.instruction->operands[0].immediate.is_signed, FCML_TRUE );
		STF_ASSERT_EQUAL( result.instruction->operands[0].immediate.int16, (fcml_int16_t)-255 );
	} else {
        STF_FAIL();
    }
	fcml_fn_parser_result_free( &result );
}

void fcml_tf_parser_int_parse_test10(void) {
	fcml_st_parser_result result;
	fcml_fn_parser_result_prepare( &result );
	STF_ASSERT_EQUAL( fcml_fn_parse( &internal_intel_context, "mov 1+2", &result ), FCML_CEH_GEC_NO_ERROR );
	if( result.instruction != NULL ) {
		STF_ASSERT_EQUAL( result.instruction->operands[0].type, FCML_OT_IMMEDIATE );
		STF_ASSERT_EQUAL( result.instruction->operands[0].immediate.size, FCML_DS_8 );
		STF_ASSERT_EQUAL( result.instruction->operands[0].immediate.is_signed, FCML_FALSE );
		STF_ASSERT_EQUAL( result.instruction->operands[0].immediate.int8, (fcml_uint8_t)(fcml_int8_t)3 );
	} else {
        STF_FAIL();
    }
	fcml_fn_parser_result_free( &result );
}

void fcml_tf_parser_int_parse_test11(void) {
	fcml_st_parser_result result;
	fcml_fn_parser_result_prepare( &result );
	STF_ASSERT_EQUAL( fcml_fn_parse( &internal_intel_context, "mov 1+2*8/(15-13)-1", &result ), FCML_CEH_GEC_NO_ERROR );
	if( result.instruction != NULL ) {
		STF_ASSERT_EQUAL( result.instruction->operands[0].type, FCML_OT_IMMEDIATE );
		STF_ASSERT_EQUAL( result.instruction->operands[0].immediate.size, FCML_DS_8 );
		STF_ASSERT_EQUAL( result.instruction->operands[0].immediate.is_signed, FCML_FALSE );
		STF_ASSERT_EQUAL( result.instruction->operands[0].immediate.int8, (fcml_uint8_t)8 );
	} else {
        STF_FAIL();
    }
	fcml_fn_parser_result_free( &result );
}

void fcml_tf_parser_int_parse_test12(void) {
	fcml_st_parser_result result;
	fcml_fn_parser_result_prepare( &result );
	STF_ASSERT_EQUAL( fcml_fn_parse( &internal_intel_context, "mov 65535", &result ), FCML_CEH_GEC_NO_ERROR );
	if( result.instruction != NULL ) {
		STF_ASSERT_EQUAL( result.instruction->operands[0].type, FCML_OT_IMMEDIATE );
		STF_ASSERT_EQUAL( result.instruction->operands[0].immediate.size, FCML_DS_16 );
		STF_ASSERT_EQUAL( result.instruction->operands[0].immediate.is_signed, FCML_FALSE );
		STF_ASSERT_EQUAL( result.instruction->operands[0].immediate.int16, (fcml_int16_t)0xFFFF );
	} else {
        STF_FAIL();
    }
	fcml_fn_parser_result_free( &result );
}

void fcml_tf_parser_int_parse_test13(void) {
	fcml_st_parser_result result;
	fcml_fn_parser_result_prepare( &result );
	STF_ASSERT_EQUAL( fcml_fn_parse( &internal_intel_context, "mov -32768", &result ), FCML_CEH_GEC_NO_ERROR );
	if( result.instruction != NULL ) {
		STF_ASSERT_EQUAL( result.instruction->operands[0].type, FCML_OT_IMMEDIATE );
		STF_ASSERT_EQUAL( result.instruction->operands[0].immediate.size, FCML_DS_16 );
		STF_ASSERT_EQUAL( result.instruction->operands[0].immediate.is_signed, FCML_TRUE );
		STF_ASSERT_EQUAL( result.instruction->operands[0].immediate.int16, (fcml_int16_t)-32768 );
	} else {
        STF_FAIL();
    }
	fcml_fn_parser_result_free( &result );
}

void fcml_tf_parser_int_parse_test14(void) {
	fcml_st_parser_result result;
	fcml_fn_parser_result_prepare( &result );
	STF_ASSERT_EQUAL( fcml_fn_parse( &internal_intel_context, "mov (-2147483647 - 1)", &result ), FCML_CEH_GEC_NO_ERROR );
	STF_ASSERT_EQUAL( result.instruction->operands[0].type, FCML_OT_IMMEDIATE );
	STF_ASSERT_EQUAL( result.instruction->operands[0].immediate.size, FCML_DS_32 );
	STF_ASSERT_EQUAL( result.instruction->operands[0].immediate.is_signed, FCML_TRUE );
	STF_ASSERT_EQUAL( result.instruction->operands[0].immediate.int32, (fcml_uint32_t)(-2147483647 - 1) );
	fcml_fn_parser_result_free( &result );
}

void fcml_tf_parser_int_parse_test15(void) {
	fcml_st_parser_result result;
	fcml_fn_parser_result_prepare( &result );
	STF_ASSERT_EQUAL( fcml_fn_parse( &internal_intel_context, "mov (-9223372036854775807 - 1)", &result ), FCML_CEH_GEC_NO_ERROR );
	if( result.instruction != NULL ) {
		STF_ASSERT_EQUAL( result.instruction->operands[0].type, FCML_OT_IMMEDIATE );
		STF_ASSERT_EQUAL( result.instruction->operands[0].immediate.size, FCML_DS_64 );
		STF_ASSERT_EQUAL( result.instruction->operands[0].immediate.is_signed, FCML_TRUE );
		STF_ASSERT_EQUAL( result.instruction->operands[0].immediate.int64, (fcml_uint64_t)(-9223372036854775807LL - 1) );
	} else {
        STF_FAIL();
    }
	fcml_fn_parser_result_free( &result );
}

void fcml_tf_parser_int_parse_test16(void) {
	fcml_st_parser_result result;
	fcml_fn_parser_result_prepare( &result );
	STF_ASSERT_EQUAL( fcml_fn_parse( &internal_intel_context, "mov 18446744073709551615", &result ), FCML_CEH_GEC_NO_ERROR );
	if( result.instruction != NULL ) {
		STF_ASSERT_EQUAL( result.instruction->operands[0].type, FCML_OT_IMMEDIATE );
		STF_ASSERT_EQUAL( result.instruction->operands[0].immediate.size, FCML_DS_64 );
		STF_ASSERT_EQUAL( result.instruction->operands[0].immediate.is_signed, FCML_FALSE );
		STF_ASSERT_EQUAL( result.instruction->operands[0].immediate.int64, (fcml_uint64_t)18446744073709551615ULL );
	} else {
        STF_FAIL();
    }
	fcml_fn_parser_result_free( &result );
}

void fcml_tf_parser_int_parse_test17(void) {
	fcml_st_parser_result result;
	fcml_fn_parser_result_prepare( &result );
	STF_ASSERT_EQUAL( fcml_fn_parse( &internal_intel_context, "mov 5675", &result ), FCML_CEH_GEC_NO_ERROR );
	if( result.instruction != NULL ) {
		STF_ASSERT_EQUAL( result.instruction->operands[0].type, FCML_OT_IMMEDIATE );
		STF_ASSERT_EQUAL( result.instruction->operands[0].immediate.size, FCML_DS_16 );
		STF_ASSERT_EQUAL( result.instruction->operands[0].immediate.is_signed, FCML_FALSE );
		STF_ASSERT_EQUAL( result.instruction->operands[0].immediate.int16, (fcml_uint16_t)5675 );
	} else {
        STF_FAIL();
    }
	fcml_fn_parser_result_free( &result );
}

void fcml_tf_parser_int_parse_test18(void) {
	fcml_st_parser_result result;
	fcml_fn_parser_result_prepare( &result );
	STF_ASSERT_EQUAL( fcml_fn_parse( &internal_intel_context, "mov 2147483647", &result ), FCML_CEH_GEC_NO_ERROR );
	if( result.instruction != NULL ) {
		STF_ASSERT_EQUAL( result.instruction->operands[0].type, FCML_OT_IMMEDIATE );
		STF_ASSERT_EQUAL( result.instruction->operands[0].immediate.size, FCML_DS_32 );
		STF_ASSERT_EQUAL( result.instruction->operands[0].immediate.is_signed, FCML_FALSE );
		STF_ASSERT_EQUAL( result.instruction->operands[0].immediate.int32, (fcml_uint32_t)2147483647 );
	} else {
        STF_FAIL();
    }
	fcml_fn_parser_result_free( &result );
}

void fcml_tf_parser_int_parse_test19(void) {
	fcml_st_parser_result result;
	fcml_fn_parser_result_prepare( &result );
	STF_ASSERT_EQUAL( fcml_fn_parse( &internal_intel_context, "mov 4294967295", &result ), FCML_CEH_GEC_NO_ERROR );
	if( result.instruction != NULL ) {
		STF_ASSERT_EQUAL( result.instruction->operands[0].type, FCML_OT_IMMEDIATE );
		STF_ASSERT_EQUAL( result.instruction->operands[0].immediate.size, FCML_DS_32 );
		STF_ASSERT_EQUAL( result.instruction->operands[0].immediate.is_signed, FCML_FALSE );
		STF_ASSERT_EQUAL( result.instruction->operands[0].immediate.int32, (fcml_uint32_t)4294967295U );
	} else {
        STF_FAIL();
    }
	fcml_fn_parser_result_free( &result );
}

void fcml_tf_parser_int_parse_test20(void) {
	fcml_st_parser_result result;
	fcml_fn_parser_result_prepare( &result );
	STF_ASSERT_EQUAL( fcml_fn_parse( &internal_intel_context, "mov 4294967296", &result ), FCML_CEH_GEC_NO_ERROR );
	if( result.instruction != NULL ) {
		STF_ASSERT_EQUAL( result.instruction->operands[0].type, FCML_OT_IMMEDIATE );
		STF_ASSERT_EQUAL( result.instruction->operands[0].immediate.size, FCML_DS_64 );
		STF_ASSERT_EQUAL( result.instruction->operands[0].immediate.is_signed, FCML_FALSE );
		STF_ASSERT_EQUAL( result.instruction->operands[0].immediate.int64, (fcml_uint64_t)4294967296ULL );
	} else {
        STF_FAIL();
    }
	fcml_fn_parser_result_free( &result );
}

void fcml_tf_parser_int_parse_test21(void) {
	fcml_st_parser_result result;
	fcml_fn_parser_result_prepare( &result );
	STF_ASSERT_EQUAL( fcml_fn_parse( &internal_intel_context, "mov -0xFFFFFFFF", &result ), FCML_CEH_GEC_NO_ERROR );
	if( result.instruction != NULL ) {
		STF_ASSERT_EQUAL( result.instruction->operands[0].type, FCML_OT_IMMEDIATE );
		STF_ASSERT_EQUAL( result.instruction->operands[0].immediate.size, FCML_DS_64 );
		STF_ASSERT_EQUAL( result.instruction->operands[0].immediate.is_signed, FCML_TRUE );
		STF_ASSERT_EQUAL( result.instruction->operands[0].immediate.int64, (fcml_uint64_t)-4294967295LL );
	} else {
        STF_FAIL();
    }
	fcml_fn_parser_result_free( &result );
}

void fcml_tf_parser_int_parse_test22(void) {
	fcml_st_parser_result result;
	fcml_fn_parser_result_prepare( &result );
	STF_ASSERT_EQUAL( fcml_fn_parse( &internal_intel_context, "mov 255", &result ), FCML_CEH_GEC_NO_ERROR );
	if( result.instruction != NULL ) {
		STF_ASSERT_EQUAL( result.instruction->operands[0].type, FCML_OT_IMMEDIATE );
		STF_ASSERT_EQUAL( result.instruction->operands[0].immediate.size, FCML_DS_8 );
		STF_ASSERT_EQUAL( result.instruction->operands[0].immediate.is_signed, FCML_FALSE );
		STF_ASSERT_EQUAL( result.instruction->operands[0].immediate.int8, (fcml_int8_t)0xFF );
	} else {
        STF_FAIL();
    }
	fcml_fn_parser_result_free( &result );
}

void fcml_tf_parser_int_parse_test23(void) {
	fcml_st_parser_result result;
	fcml_fn_parser_result_prepare( &result );
	STF_ASSERT_EQUAL( fcml_fn_parse( &internal_intel_context, "mov 1", &result ), FCML_CEH_GEC_NO_ERROR );
	if( result.instruction != NULL ) {
		STF_ASSERT_EQUAL( result.instruction->operands[0].type, FCML_OT_IMMEDIATE );
		STF_ASSERT_EQUAL( result.instruction->operands[0].immediate.size, FCML_DS_8 );
		STF_ASSERT_EQUAL( result.instruction->operands[0].immediate.is_signed, FCML_FALSE );
		STF_ASSERT_EQUAL( result.instruction->operands[0].immediate.int8, 1 );
	} else {
        STF_FAIL();
    }
	fcml_fn_parser_result_free( &result );
}

void fcml_tf_parser_int_parse_test24(void) {
	fcml_st_parser_result result;
	fcml_fn_parser_result_prepare( &result );
    STF_ASSERT_EQUAL( fcml_fn_parse( &internal_intel_context, "mov dword ptr [0x0000FFFF]", &result ), FCML_CEH_GEC_NO_ERROR );
    if( result.instruction != NULL ) {
        STF_ASSERT_EQUAL( result.instruction->operands[0].type, FCML_OT_ADDRESS );
        STF_ASSERT_EQUAL( result.instruction->operands[0].address.address_form, FCML_AF_OFFSET );
        STF_ASSERT_EQUAL( result.instruction->operands[0].address.offset.size, FCML_DS_16 );
        STF_ASSERT_EQUAL( result.instruction->operands[0].address.offset.off16, (fcml_int16_t)0xFFFF );
    } else {
        STF_FAIL();
    }
    fcml_fn_parser_result_free( &result );
}

void fcml_tf_parser_int_parse_test25(void) {
	fcml_st_parser_result result;
	fcml_fn_parser_result_prepare( &result );
    STF_ASSERT_EQUAL( fcml_fn_parse( &internal_intel_context, "mov dword ptr [0xFF-1]", &result ), FCML_CEH_GEC_NO_ERROR );
    if( result.instruction != NULL ) {
        STF_ASSERT_EQUAL( result.instruction->operands[0].type, FCML_OT_ADDRESS );
        STF_ASSERT_EQUAL( result.instruction->operands[0].address.address_form, FCML_AF_OFFSET );
        STF_ASSERT_EQUAL( result.instruction->operands[0].address.offset.size, FCML_DS_16 );
        STF_ASSERT_EQUAL( result.instruction->operands[0].address.offset.off16, 254 );
    } else {
        STF_FAIL();
    }
    fcml_fn_parser_result_free( &result );
}

void fcml_tf_parser_int_parse_test26(void) {
	fcml_st_parser_result result;
	fcml_fn_parser_result_prepare( &result );
    STF_ASSERT_EQUAL( fcml_fn_parse( &internal_intel_context, "mov dword ptr [-1]", &result ), FCML_CEH_GEC_NO_ERROR );
    if( result.instruction != NULL ) {
        STF_ASSERT_EQUAL( result.instruction->operands[0].type, FCML_OT_ADDRESS );
        STF_ASSERT_EQUAL( result.instruction->operands[0].address.address_form, FCML_AF_OFFSET );
        STF_ASSERT_EQUAL( result.instruction->operands[0].address.offset.size, FCML_DS_16 );
        STF_ASSERT_EQUAL( result.instruction->operands[0].address.offset.off16, (fcml_int16_t)0xFFFF );
    } else {
        STF_FAIL();
    }
    fcml_fn_parser_result_free( &result );
}

void fcml_tf_parser_int_parse_test27(void) {
	fcml_st_parser_result result;
	fcml_fn_parser_result_prepare( &result );
    STF_ASSERT_EQUAL( fcml_fn_parse( &internal_intel_context, "mov dword ptr [0xFFFFFFFFFFFFFFFF]", &result ), FCML_CEH_GEC_NO_ERROR );
    if( result.instruction != NULL ) {
        STF_ASSERT_EQUAL( result.instruction->operands[0].type, FCML_OT_ADDRESS );
        STF_ASSERT_EQUAL( result.instruction->operands[0].address.address_form, FCML_AF_OFFSET );
        STF_ASSERT_EQUAL( result.instruction->operands[0].address.offset.size, FCML_DS_64 );
        STF_ASSERT_EQUAL( result.instruction->operands[0].address.offset.off64, 0xFFFFFFFFFFFFFFFFULL );
    } else {
        STF_FAIL();
    }
    fcml_fn_parser_result_free( &result );
}

void fcml_tf_parser_int_parse_test28(void) {
	fcml_st_parser_result result;
	fcml_fn_parser_result_prepare( &result );
    STF_ASSERT_EQUAL( fcml_fn_parse( &internal_intel_context, "mov dword ptr [eax+0xFFFFFFFFFFFFFFFF]", &result ), FCML_CEH_GEC_NO_ERROR );
    if( result.instruction != NULL ) {
        STF_ASSERT_EQUAL( result.instruction->operands[0].type, FCML_OT_ADDRESS );
        STF_ASSERT_EQUAL( result.instruction->operands[0].address.address_form, FCML_AF_COMBINED );
        STF_ASSERT_EQUAL( result.instruction->operands[0].address.effective_address.base.type, FCML_REG_GPR );
        STF_ASSERT_EQUAL( result.instruction->operands[0].address.effective_address.base.reg, FCML_REG_EAX );
        STF_ASSERT_EQUAL( result.instruction->operands[0].address.effective_address.displacement.size, FCML_DS_64 );
        STF_ASSERT_EQUAL( result.instruction->operands[0].address.effective_address.displacement.int64, 0xFFFFFFFFFFFFFFFFULL );
    } else {
        STF_FAIL();
    }
    fcml_fn_parser_result_free( &result );
}

void fcml_tf_parser_int_parse_test29(void) {
	fcml_st_parser_result result;
	fcml_fn_parser_result_prepare( &result );
    STF_ASSERT_EQUAL( fcml_fn_parse( &internal_intel_context, "mov xmmword ptr [eax+0xFFFFFFFFFFFFFFFF]", &result ), FCML_CEH_GEC_NO_ERROR );
    if( result.instruction != NULL ) {
        STF_ASSERT_EQUAL( result.instruction->operands[0].type, FCML_OT_ADDRESS );
        STF_ASSERT_EQUAL( result.instruction->operands[0].hints, FCML_OP_HINT_MULTIMEDIA_INSTRUCTION );
        STF_ASSERT_EQUAL( result.instruction->operands[0].address.address_form, FCML_AF_COMBINED );
        STF_ASSERT_EQUAL( result.instruction->operands[0].address.effective_address.base.type, FCML_REG_GPR );
        STF_ASSERT_EQUAL( result.instruction->operands[0].address.effective_address.base.reg, FCML_REG_EAX );
        STF_ASSERT_EQUAL( result.instruction->operands[0].address.effective_address.displacement.size, FCML_DS_64 );
        STF_ASSERT_EQUAL( result.instruction->operands[0].address.effective_address.displacement.int64, 0xFFFFFFFFFFFFFFFFULL );
    } else {
        STF_FAIL();
    }
    fcml_fn_parser_result_free( &result );
}

void fcml_tf_parser_int_parse_test30(void) {
	fcml_st_parser_result result;
	fcml_fn_parser_result_prepare( &result );
	STF_ASSERT_EQUAL( fcml_fn_parse( &internal_intel_context, "lock mov 1", &result ), FCML_CEH_GEC_NO_ERROR );
	if( result.instruction != NULL ) {
		STF_ASSERT_EQUAL( result.instruction->operands[0].type, FCML_OT_IMMEDIATE );
		STF_ASSERT_EQUAL( result.instruction->operands[0].immediate.size, FCML_DS_8 );
		STF_ASSERT_EQUAL( result.instruction->operands[0].immediate.is_signed, FCML_FALSE );
		STF_ASSERT_EQUAL( result.instruction->operands[0].immediate.int8, (fcml_uint8_t)1 );
		STF_ASSERT_EQUAL( result.instruction->prefixes, FCML_PREFIX_LOCK );
	} else {
        STF_FAIL();
    }
	fcml_fn_parser_result_free( &result );
}

void fcml_tf_parser_int_parse_test31(void) {
	/* Check if multiple prefixes are allowed.*/
	fcml_st_parser_result result;
	fcml_fn_parser_result_prepare( &result );
	STF_ASSERT_EQUAL( fcml_fn_parse( &internal_intel_context, "lock repne repe mov 1", &result ), FCML_CEH_GEC_NO_ERROR );
	if( result.instruction != NULL ) {
		STF_ASSERT_EQUAL( result.instruction->operands[0].type, FCML_OT_IMMEDIATE );
		STF_ASSERT_EQUAL( result.instruction->operands[0].immediate.size, FCML_DS_8 );
		STF_ASSERT_EQUAL( result.instruction->operands[0].immediate.is_signed, FCML_FALSE );
		STF_ASSERT_EQUAL( result.instruction->operands[0].immediate.int8, (fcml_uint8_t)1 );
		STF_ASSERT_EQUAL( result.instruction->prefixes, FCML_PREFIX_LOCK | FCML_PREFIX_REPE | FCML_PREFIX_REPNE );
	} else {
        STF_FAIL();
    }
	fcml_fn_parser_result_free( &result );
}

void fcml_tf_parser_int_parse_test32(void) {
	/* Duplicated prefixes aren't allowed.*/
	fcml_st_parser_result result;
	fcml_fn_parser_result_prepare( &result );
	STF_ASSERT_EQUAL( fcml_fn_parse( &internal_intel_context, "lock lock mov 1", &result ), FCML_CEH_GEC_INVALID_INPUT );
	if( result.instruction != NULL ) {
        STF_FAIL("Instruction should be NULL.");
	} else if( result.errors.errors ){
		fcml_st_ceh_error_container *cont = &(result.errors);
		STF_ASSERT_EQUAL( cont->errors->level, FCML_EN_CEH_EL_ERROR );
		STF_ASSERT_EQUAL( cont->errors->code, ( FCML_CEH_MEC_ERROR_INVALID_SYNTAX ) );
		STF_ASSERT_STRING_EQUAL( "Doubled prefixes.", cont->errors->message );
    } else {
    	STF_FAIL("Errors can not be null here.");
    }
	fcml_fn_parser_result_free( &result );
}

void fcml_tf_parser_int_parse_test_symbols_1(void) {
	fcml_st_parser_result result;
	fcml_fn_parser_result_prepare( &result );
	fcml_st_parser_context context = {0};
	context.dialect = internal_dialect_intel;
	context.ip = 0x401000;
	context.symbol_table = NULL;
	context.configuration.alloc_symbol_table_if_needed = FCML_TRUE;

	STF_ASSERT_EQUAL( fcml_fn_parse( &context, FCML_TEXT( "label:" ), &result ), FCML_CEH_GEC_NO_ERROR );
	STF_ASSERT_PTR_NULL( result.instruction );
	STF_ASSERT_PTR_NOT_NULL( result.symbol );
	STF_ASSERT_PTR_NOT_NULL( context.symbol_table );
	STF_ASSERT_EQUAL( result.symbol->value, 0x401000 );
	STF_ASSERT_STRING_EQUAL( result.symbol->symbol, FCML_TEXT( "label" ) );

	STF_ASSERT_EQUAL( fcml_fn_parse( &context, FCML_TEXT( "_label:" ), &result ), FCML_CEH_GEC_NO_ERROR );
	STF_ASSERT_PTR_NULL( result.instruction );
	STF_ASSERT_PTR_NOT_NULL( result.symbol );
	STF_ASSERT_EQUAL( result.symbol->value, 0x401000 );
	STF_ASSERT_STRING_EQUAL( result.symbol->symbol, FCML_TEXT( "_label" ) );

	fcml_fn_parser_result_free( &result );
	fcml_fn_symbol_table_free( context.symbol_table );
}

void fcml_tf_parser_int_parse_test_symbols_2(void) {
	fcml_st_parser_result result;
	fcml_fn_parser_result_prepare( &result );
	fcml_st_parser_context context = {0};
	context.dialect = internal_dialect_intel;
	context.configuration.override_labels = FCML_FALSE;
	context.configuration.alloc_symbol_table_if_needed = FCML_TRUE;
	context.ip = 0x401000;

	STF_ASSERT_EQUAL( fcml_fn_parse( &context, FCML_TEXT( "label: mov eax,1" ), &result ), FCML_CEH_GEC_NO_ERROR );
	STF_ASSERT_PTR_NOT_NULL( result.instruction );
	STF_ASSERT_STRING_EQUAL( result.instruction->mnemonic, "mov" );
	STF_ASSERT_PTR_NOT_NULL( result.symbol );
	STF_ASSERT_EQUAL( result.symbol->value, 0x401000 );
	STF_ASSERT_STRING_EQUAL( result.symbol->symbol, FCML_TEXT( "label" ) );

	fcml_fn_parser_result_free( &result );
	fcml_fn_symbol_table_free( context.symbol_table );
}

void fcml_tf_parser_int_parse_test_symbols_3(void) {

	fcml_st_parser_result result;

	fcml_fn_parser_result_prepare( &result );

	fcml_st_parser_context context = {0};
	context.dialect = internal_dialect_intel;
	context.configuration.override_labels = FCML_FALSE;
	context.ip = 0x401000;
	context.configuration.alloc_symbol_table_if_needed = FCML_TRUE;

	STF_ASSERT_EQUAL( fcml_fn_parse( &context, FCML_TEXT( "label: mov eax,1" ), &result ), FCML_CEH_GEC_NO_ERROR );
	STF_ASSERT_PTR_NOT_NULL( result.instruction );
	STF_ASSERT_STRING_EQUAL( result.instruction->mnemonic, "mov" );
	STF_ASSERT_PTR_NOT_NULL( result.symbol );
	STF_ASSERT_EQUAL( result.symbol->value, 0x401000 );
	STF_ASSERT_STRING_EQUAL( result.symbol->symbol, FCML_TEXT( "label" ) );

	/* Can not override symbol. */
	STF_ASSERT_EQUAL( fcml_fn_parse( &context, FCML_TEXT( "label: mov eax,1" ), &result ), FCML_CEH_GEC_INVALID_INPUT );

	fcml_st_ceh_error_info *error = result.errors.errors;
	STF_ASSERT_PTR_NOT_NULL( error );
	if( error ) {
		STF_ASSERT_EQUAL( error->code, FCML_CEH_MEC_ERROR_SYMBOL_ALREADY_DEFINED );
		STF_ASSERT_STRING_EQUAL( error->message, FCML_TEXT( "Symbol already defined: label." ) );
	}

	context.configuration.override_labels = FCML_TRUE;

	STF_ASSERT_EQUAL( fcml_fn_parse( &context, FCML_TEXT( "label: add eax,1" ), &result ), FCML_CEH_GEC_NO_ERROR );
	STF_ASSERT_PTR_NOT_NULL( result.instruction );
	STF_ASSERT_STRING_EQUAL( result.instruction->mnemonic, "add" );
	STF_ASSERT_PTR_NOT_NULL( result.symbol );
	STF_ASSERT_EQUAL( result.symbol->value, 0x401000 );
	STF_ASSERT_STRING_EQUAL( result.symbol->symbol, FCML_TEXT( "label" ) );

	fcml_fn_parser_result_free( &result );
	fcml_fn_symbol_table_free( context.symbol_table );
}


/* Undefined symbol. */
void fcml_tf_parser_int_parse_test_symbols_4(void) {
	fcml_st_parser_result result;
	fcml_fn_parser_result_prepare( &result );
	fcml_st_parser_context context = {0};
	context.dialect = internal_dialect_intel;
	context.ip = 0x401000;
	context.configuration.alloc_symbol_table_if_needed = FCML_TRUE;

	STF_ASSERT_EQUAL( fcml_fn_parse( &context, FCML_TEXT( "label: mov eax, symbol" ), &result ), FCML_CEH_GEC_UNDEFINED_SYMBOL );
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
void fcml_tf_parser_int_parse_test_symbols_5(void) {

	fcml_st_parser_result result;
	fcml_fn_parser_result_prepare( &result );
	fcml_st_parser_context context = {0};
	context.dialect = internal_dialect_intel;
	context.ip = 0x401000;
	context.configuration.ignore_undefined_symbols = FCML_TRUE;
	context.configuration.override_labels = FCML_TRUE;
	context.configuration.alloc_symbol_table_if_needed = FCML_TRUE;

	STF_ASSERT_EQUAL( fcml_fn_parse( &context, FCML_TEXT( "label: mov eax, symbol" ), &result ), FCML_CEH_GEC_NO_ERROR );
	STF_ASSERT_PTR_NOT_NULL( result.instruction );
	STF_ASSERT_PTR_NOT_NULL( result.symbol );

	if( result.instruction ) {
		fcml_st_instruction *instruction = result.instruction;
		STF_ASSERT_EQUAL( instruction->operands[1].type, FCML_OT_IMMEDIATE );
		STF_ASSERT_EQUAL( instruction->operands[1].immediate.size, FCML_DS_8 );
		STF_ASSERT_EQUAL( instruction->operands[1].immediate.int8, 0 );
		STF_ASSERT_EQUAL( instruction->operands[1].immediate.is_signed, FCML_TRUE );
	}

	fcml_fn_parser_result_free( &result );
	fcml_fn_symbol_table_free( context.symbol_table );
}

/* Use defined symbol in the instruction. */
void fcml_tf_parser_int_parse_test_symbols_6(void) {

	fcml_st_parser_result result;
	fcml_fn_parser_result_prepare( &result );
	fcml_st_parser_context context = {0};
	context.dialect = internal_dialect_intel;
	context.ip = 0x401000;
	context.configuration.ignore_undefined_symbols = FCML_TRUE;
	context.configuration.override_labels = FCML_TRUE;
	context.configuration.alloc_symbol_table_if_needed = FCML_TRUE;

	STF_ASSERT_EQUAL( fcml_fn_parse( &context, FCML_TEXT( "label: mov eax, label" ), &result ), FCML_CEH_GEC_NO_ERROR );
	STF_ASSERT_PTR_NOT_NULL( result.instruction );
	STF_ASSERT_PTR_NOT_NULL( result.symbol );

	if( result.instruction ) {
		fcml_st_instruction *instruction = result.instruction;
		STF_ASSERT_EQUAL( instruction->operands[1].type, FCML_OT_IMMEDIATE );
		STF_ASSERT_EQUAL( instruction->operands[1].immediate.size, FCML_DS_32 );
		STF_ASSERT_EQUAL( instruction->operands[1].immediate.int32, 0x401000 );
		// Symbols are always defined as signed values.
		STF_ASSERT_EQUAL( instruction->operands[1].immediate.is_signed, FCML_TRUE );
	}

	fcml_fn_parser_result_free( &result );
	fcml_fn_symbol_table_free( context.symbol_table );
}

/* Multpile symbols in expression. */
void fcml_tf_parser_int_parse_test_symbols_7(void) {

	fcml_st_parser_result result;
	fcml_fn_parser_result_prepare( &result );
	fcml_st_parser_context context = {0};
	context.dialect = internal_dialect_intel;
	context.ip = 0x401000;
	context.configuration.ignore_undefined_symbols = FCML_TRUE;
	context.configuration.override_labels = FCML_TRUE;
	context.symbol_table = fcml_fn_symbol_table_alloc();
	if( !context.symbol_table ) {
		STF_FAIL("Out of memory.");
		return;
	}

	STF_ASSERT_EQUAL( fcml_fn_symbol_add_raw( context.symbol_table, FCML_TEXT("symbol_1"), 10 ), FCML_CEH_GEC_NO_ERROR );
	STF_ASSERT_EQUAL( fcml_fn_symbol_add_raw( context.symbol_table, FCML_TEXT("symbol_2"), 5 ), FCML_CEH_GEC_NO_ERROR );
	STF_ASSERT_EQUAL( fcml_fn_symbol_add_raw( context.symbol_table, FCML_TEXT("symbol_3"), 2 ), FCML_CEH_GEC_NO_ERROR );

	STF_ASSERT_EQUAL( fcml_fn_parse( &context, FCML_TEXT( "label: mov eax, label + ( ( symbol_1 * symbol_2 ) / symbol_3 )" ), &result ), FCML_CEH_GEC_NO_ERROR );
	STF_ASSERT_PTR_NOT_NULL( result.instruction );
	STF_ASSERT_PTR_NOT_NULL( result.symbol );

	if( result.instruction ) {
		fcml_st_instruction *instruction = result.instruction;
		STF_ASSERT_EQUAL( instruction->operands[1].type, FCML_OT_IMMEDIATE );
		STF_ASSERT_EQUAL( instruction->operands[1].immediate.size, FCML_DS_32 );
		STF_ASSERT_EQUAL( instruction->operands[1].immediate.int32, 0x401000 + 25 );
		STF_ASSERT_EQUAL( instruction->operands[1].immediate.is_signed, FCML_FALSE );
	}

	fcml_fn_parser_result_free( &result );
	fcml_fn_symbol_table_free( context.symbol_table );
}

/* Extracting symbols. */
void fcml_tf_parser_int_parse_test_symbols_8(void) {

	fcml_st_parser_result result;

	fcml_fn_parser_result_prepare( &result );

	fcml_st_parser_context context = {0};
	context.dialect = internal_dialect_intel;
	context.ip = 0x401000;
	context.configuration.ignore_undefined_symbols = FCML_TRUE;
	context.configuration.override_labels = FCML_TRUE;
	context.symbol_table = fcml_fn_symbol_table_alloc();
	if( !context.symbol_table ) {
		STF_FAIL("Out of memory.");
		return;
	}

	STF_ASSERT_EQUAL( fcml_fn_symbol_add_raw( context.symbol_table, FCML_TEXT("symbol_1"), 10 ), FCML_CEH_GEC_NO_ERROR );
	STF_ASSERT_EQUAL( fcml_fn_symbol_add_raw( context.symbol_table, FCML_TEXT("symbol_2"), 5 ), FCML_CEH_GEC_NO_ERROR );
	STF_ASSERT_EQUAL( fcml_fn_symbol_add_raw( context.symbol_table, FCML_TEXT("symbol_3"), 2 ), FCML_CEH_GEC_NO_ERROR );

	fcml_st_parser_ast ast = {0};
	fcml_ceh_error error = fcml_fn_parse_to_ast( &context, FCML_TEXT( "label: mov eax, label + ( ( symbol_1 * symbol_2 ) / symbol_3 )" ), &ast );

	if( !error ) {

		STF_ASSERT_PTR_NOT_NULL( ast.symbol );
		STF_ASSERT_PTR_NOT_NULL( ast.tree );

		if( ast.tree ) {
			fcml_st_coll_list *list = NULL;
			error = fcml_fn_ast_extract_used_symbols( ast.tree, &list );
			if( !error ) {
				STF_ASSERT_EQUAL( list->size, 4 );
				fcml_fn_coll_list_free( list, NULL, NULL );
			}

		}

	}

	fcml_fn_parser_free_ast( &ast );
	fcml_fn_symbol_table_free( context.symbol_table );
}

void fcml_tf_parser_int_parse_test_symbols_9(void) {
	fcml_st_parser_result result;
	fcml_fn_parser_result_prepare( &result );
	fcml_st_parser_context context = {0};
	context.dialect = internal_dialect_intel;
	context.ip = 0x401000;
	context.symbol_table = NULL;
	context.configuration.disable_symbols_declaration = FCML_TRUE;

	STF_ASSERT_EQUAL( fcml_fn_parse( &context, FCML_TEXT( "label:" ), &result ), FCML_CEH_GEC_UNSUPPORTED_LABEL_DECLARATION );
	STF_ASSERT_PTR_NULL( result.instruction );
	STF_ASSERT_PTR_NULL( result.symbol );
	STF_ASSERT_PTR_NULL( result.errors.errors );
	STF_ASSERT_PTR_NULL( result.errors.last_error );

	fcml_fn_parser_result_free( &result );
}

void fcml_tf_parser_int_parse_test_symbols_10(void) {

	fcml_st_parser_result result;
	fcml_fn_parser_result_prepare( &result );
	fcml_st_parser_context context = {0};
	context.dialect = internal_dialect_intel;
	context.ip = 0x401000;
	context.symbol_table = NULL;
	context.configuration.disable_symbols_declaration = FCML_FALSE;
	context.configuration.alloc_symbol_table_if_needed = FCML_FALSE;

	STF_ASSERT_EQUAL( fcml_fn_parse( &context, FCML_TEXT( "label: mov eax, 1" ), &result ), FCML_CEH_GEC_NO_ERROR );
	STF_ASSERT_PTR_NOT_NULL( result.instruction );
	STF_ASSERT_PTR_NULL( result.symbol );
	STF_ASSERT_PTR_NULL( result.errors.errors );
	STF_ASSERT_PTR_NULL( result.errors.last_error );
	STF_ASSERT_PTR_NULL( context.symbol_table );

	fcml_fn_parser_result_free( &result );
}

void fcml_tf_parser_int_parse_test_symbols_11(void) {

	/* Symbol table not found and not allocated. */
	fcml_st_parser_result result;
	fcml_fn_parser_result_prepare( &result );
	fcml_st_parser_context context = {0};
	context.dialect = internal_dialect_intel;
	context.configuration.override_labels = FCML_FALSE;
	context.configuration.alloc_symbol_table_if_needed = FCML_FALSE;
	context.ip = 0x401000;

	STF_ASSERT_EQUAL( fcml_fn_parse( &context, FCML_TEXT( "label: mov eax,1" ), &result ), FCML_CEH_GEC_NO_ERROR );
	STF_ASSERT_PTR_NOT_NULL( result.instruction );
	STF_ASSERT_STRING_EQUAL( result.instruction->mnemonic, "mov" );
	STF_ASSERT_PTR_NULL( result.symbol );
	STF_ASSERT_PTR_NULL( context.symbol_table );

	fcml_fn_parser_result_free( &result );
}


/* Pseudo operations operands parsing. */
void fcml_tf_parser_intel_parse_test_pseudo_operation_1(void) {

	fcml_st_parser_result result;
	fcml_fn_parser_result_prepare( &result );
	fcml_st_parser_context context = {0};
	context.dialect = internal_dialect_intel;
	context.ip = 0x401000;
	context.configuration.ignore_undefined_symbols = FCML_TRUE;
	context.configuration.override_labels = FCML_TRUE;
	context.configuration.alloc_symbol_table_if_needed = FCML_TRUE;

	STF_ASSERT_EQUAL( fcml_fn_parse( &context, FCML_TEXT( "label: db 0x12" ), &result ), FCML_CEH_GEC_NO_ERROR );
	STF_ASSERT_PTR_NOT_NULL( result.instruction );
	STF_ASSERT_PTR_NOT_NULL( result.symbol );

	if( result.instruction ) {
		fcml_st_instruction *instruction = result.instruction;
		STF_ASSERT_STRING_EQUAL( "db", result.instruction->mnemonic );
		STF_ASSERT_EQUAL( 1, instruction->operands_count );
		STF_ASSERT_EQUAL( instruction->operands[0].type, FCML_OT_IMMEDIATE );
		STF_ASSERT_EQUAL( instruction->operands[0].immediate.size, FCML_DS_8 );
		STF_ASSERT_EQUAL( instruction->operands[0].immediate.int8, 0x12 );
		STF_ASSERT_EQUAL( instruction->operands[0].immediate.is_signed, FCML_FALSE );
	}

	fcml_fn_parser_result_free( &result );
	fcml_fn_symbol_table_free( context.symbol_table );
}

fcml_stf_test_case fcml_ti_parser[] = {
	{ "fcml_tf_parser_int_parse_test1", fcml_tf_parser_int_parse_test1 },
	{ "fcml_tf_parser_int_parse_test2", fcml_tf_parser_int_parse_test2 },
	{ "fcml_tf_parser_int_parse_test3", fcml_tf_parser_int_parse_test3 },
	{ "fcml_tf_parser_int_parse_test4", fcml_tf_parser_int_parse_test4 },
	{ "fcml_tf_parser_int_parse_test5", fcml_tf_parser_int_parse_test5 },
	{ "fcml_tf_parser_int_parse_test6", fcml_tf_parser_int_parse_test6 },
	{ "fcml_tf_parser_int_parse_test7", fcml_tf_parser_int_parse_test7 },
	{ "fcml_tf_parser_int_parse_test8", fcml_tf_parser_int_parse_test8 },
	{ "fcml_tf_parser_int_parse_test9", fcml_tf_parser_int_parse_test9 },
	{ "fcml_tf_parser_int_parse_test10", fcml_tf_parser_int_parse_test10 },
	{ "fcml_tf_parser_int_parse_test11", fcml_tf_parser_int_parse_test11 },
	{ "fcml_tf_parser_int_parse_test12", fcml_tf_parser_int_parse_test12 },
	{ "fcml_tf_parser_int_parse_test13", fcml_tf_parser_int_parse_test13 },
	{ "fcml_tf_parser_int_parse_test14", fcml_tf_parser_int_parse_test14 },
	{ "fcml_tf_parser_int_parse_test15", fcml_tf_parser_int_parse_test15 },
	{ "fcml_tf_parser_int_parse_test16", fcml_tf_parser_int_parse_test16 },
	{ "fcml_tf_parser_int_parse_test17", fcml_tf_parser_int_parse_test17 },
	{ "fcml_tf_parser_int_parse_test18", fcml_tf_parser_int_parse_test18 },
	{ "fcml_tf_parser_int_parse_test19", fcml_tf_parser_int_parse_test19 },
	{ "fcml_tf_parser_int_parse_test20", fcml_tf_parser_int_parse_test20 },
	{ "fcml_tf_parser_int_parse_test21", fcml_tf_parser_int_parse_test21 },
	{ "fcml_tf_parser_int_parse_test22", fcml_tf_parser_int_parse_test22 },
	{ "fcml_tf_parser_int_parse_test23", fcml_tf_parser_int_parse_test23 },
	{ "fcml_tf_parser_int_parse_test24", fcml_tf_parser_int_parse_test24 },
	{ "fcml_tf_parser_int_parse_test25", fcml_tf_parser_int_parse_test25 },
	{ "fcml_tf_parser_int_parse_test26", fcml_tf_parser_int_parse_test26 },
	{ "fcml_tf_parser_int_parse_test27", fcml_tf_parser_int_parse_test27 },
	{ "fcml_tf_parser_int_parse_test28", fcml_tf_parser_int_parse_test28 },
	{ "fcml_tf_parser_int_parse_test29", fcml_tf_parser_int_parse_test29 },
	{ "fcml_tf_parser_int_parse_test30", fcml_tf_parser_int_parse_test30 },
	{ "fcml_tf_parser_int_parse_test31", fcml_tf_parser_int_parse_test31 },
	{ "fcml_tf_parser_int_parse_test32", fcml_tf_parser_int_parse_test32 },
	{ "fcml_tf_parser_int_parse_test_symbols_1", fcml_tf_parser_int_parse_test_symbols_1 },
	{ "fcml_tf_parser_int_parse_test_symbols_2", fcml_tf_parser_int_parse_test_symbols_2 },
	{ "fcml_tf_parser_int_parse_test_symbols_3", fcml_tf_parser_int_parse_test_symbols_3 },
	{ "fcml_tf_parser_int_parse_test_symbols_4", fcml_tf_parser_int_parse_test_symbols_4 },
	{ "fcml_tf_parser_int_parse_test_symbols_5", fcml_tf_parser_int_parse_test_symbols_5 },
	{ "fcml_tf_parser_int_parse_test_symbols_6", fcml_tf_parser_int_parse_test_symbols_6 },
	{ "fcml_tf_parser_int_parse_test_symbols_7", fcml_tf_parser_int_parse_test_symbols_7 },
	{ "fcml_tf_parser_int_parse_test_symbols_8", fcml_tf_parser_int_parse_test_symbols_8 },
	{ "fcml_tf_parser_int_parse_test_symbols_9", fcml_tf_parser_int_parse_test_symbols_9 },
	{ "fcml_tf_parser_int_parse_test_symbols_10", fcml_tf_parser_int_parse_test_symbols_10 },
	{ "fcml_tf_parser_int_parse_test_symbols_11", fcml_tf_parser_int_parse_test_symbols_11 },
	{ "fcml_tf_parser_intel_parse_test_pseudo_operation_1", fcml_tf_parser_intel_parse_test_pseudo_operation_1 },
	FCML_STF_NULL_TEST
};

fcml_stf_test_suite fcml_si_intel_parser = {
	"suite-fcml-parser", fcml_tf_parser_suite_init, fcml_tf_parser_suite_cleanup, fcml_ti_parser
};

