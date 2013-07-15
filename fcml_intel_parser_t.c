/*
 * fcml_intel_parser.c
 *
 *  Created on: 29-06-2013
 *      Author: tAs
 */

#include "fcml_intel_parser_t.h"

#include "fcml_x64intel_asm_parser.h"

int fcml_tf_parser_suite_init(void) {
	return 0;
}

int fcml_tf_parser_suite_cleanup(void) {
	return 0;
}

void fcml_tf_parser_int_parse_test1(void) {
	fcml_st_x64iap_parser_result *result;
	CU_ASSERT_EQUAL( fcml_x64iap_parse( "mov 80-90", &result ), FCML_CEH_GEC_NO_ERROR );
	if( result->instruction != NULL ) {
		CU_ASSERT_EQUAL( result->instruction->operands[0].type, FCML_EOT_IMMEDIATE );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.imm_size, FCML_DS_8 );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.is_signed, FCML_TRUE );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.imm8, (fcml_uint8_t)(fcml_int8_t)-10 );
	}
	fcml_x64iap_free( result );
}

void fcml_tf_parser_int_parse_test2(void) {
	fcml_st_x64iap_parser_result *result;
	CU_ASSERT_EQUAL( fcml_x64iap_parse( "mov 0xFF", &result ), FCML_CEH_GEC_NO_ERROR );
	if( result->instruction != NULL ) {
		CU_ASSERT_EQUAL( result->instruction->operands[0].type, FCML_EOT_IMMEDIATE );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.imm_size, FCML_DS_8 );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.is_signed, FCML_FALSE );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.imm8, 0xFF );
	}
	fcml_x64iap_free( result );
}

void fcml_tf_parser_int_parse_test3(void) {
	fcml_st_x64iap_parser_result *result;
	CU_ASSERT_EQUAL( fcml_x64iap_parse( "mov 0xFFF", &result ), FCML_CEH_GEC_NO_ERROR );
	if( result->instruction != NULL ) {
		CU_ASSERT_EQUAL( result->instruction->operands[0].type, FCML_EOT_IMMEDIATE );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.imm_size, FCML_DS_16 );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.is_signed, FCML_FALSE );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.imm16, (fcml_uint16_t)0x0FFF );
	}
	fcml_x64iap_free( result );
}

void fcml_tf_parser_int_parse_test4(void) {
	fcml_st_x64iap_parser_result *result;
	CU_ASSERT_EQUAL( fcml_x64iap_parse( "mov 0xFFFF", &result ), FCML_CEH_GEC_NO_ERROR );
	if( result->instruction != NULL ) {
		CU_ASSERT_EQUAL( result->instruction->operands[0].type, FCML_EOT_IMMEDIATE );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.imm_size, FCML_DS_16 );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.is_signed, FCML_FALSE );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.imm16, (fcml_uint16_t)0xFFFF );
	}
	fcml_x64iap_free( result );
}

void fcml_tf_parser_int_parse_test5(void) {
	fcml_st_x64iap_parser_result *result;
	CU_ASSERT_EQUAL( fcml_x64iap_parse( "mov 0xFFFFF", &result ), FCML_CEH_GEC_NO_ERROR );
	if( result->instruction != NULL ) {
		CU_ASSERT_EQUAL( result->instruction->operands[0].type, FCML_EOT_IMMEDIATE );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.imm_size, FCML_DS_32 );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.is_signed, FCML_FALSE );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.imm32, (fcml_uint32_t)0x000FFFFF );
	}
	fcml_x64iap_free( result );
}

void fcml_tf_parser_int_parse_test6(void) {
	fcml_st_x64iap_parser_result *result;
	CU_ASSERT_EQUAL( fcml_x64iap_parse( "mov 0xFFFFFFFF", &result ), FCML_CEH_GEC_NO_ERROR );
	if( result->instruction != NULL ) {
		CU_ASSERT_EQUAL( result->instruction->operands[0].type, FCML_EOT_IMMEDIATE );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.imm_size, FCML_DS_32 );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.is_signed, FCML_FALSE );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.imm32, (fcml_uint32_t)0xFFFFFFFF );
	}
	fcml_x64iap_free( result );
}

void fcml_tf_parser_int_parse_test7(void) {
	fcml_st_x64iap_parser_result *result;
	CU_ASSERT_EQUAL( fcml_x64iap_parse( "mov 0xFFFFFFFFFFFFFFFF", &result ), FCML_CEH_GEC_NO_ERROR );
	if( result->instruction != NULL ) {
		CU_ASSERT_EQUAL( result->instruction->operands[0].type, FCML_EOT_IMMEDIATE );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.imm_size, FCML_DS_64 );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.is_signed, FCML_FALSE );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.imm64, 0xFFFFFFFFFFFFFFFFUL );
	}
	fcml_x64iap_free( result );
}

void fcml_tf_parser_int_parse_test8(void) {
	fcml_st_x64iap_parser_result *result;
	CU_ASSERT_EQUAL( fcml_x64iap_parse( "mov -0xFFFFFFFFFFFFFFFF", &result ), FCML_CEH_GEC_NO_ERROR );
	if( result->instruction != NULL ) {
		CU_ASSERT_EQUAL( result->instruction->operands[0].type, FCML_EOT_IMMEDIATE );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.imm_size, FCML_DS_8 );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.is_signed, FCML_FALSE );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.imm8, (fcml_uint8_t)(fcml_int8_t)1 );
	}
	fcml_x64iap_free( result );
}

void fcml_tf_parser_int_parse_test9(void) {
	fcml_st_x64iap_parser_result *result;
	CU_ASSERT_EQUAL( fcml_x64iap_parse( "mov -0xFF", &result ), FCML_CEH_GEC_NO_ERROR );
	if( result->instruction != NULL ) {
		CU_ASSERT_EQUAL( result->instruction->operands[0].type, FCML_EOT_IMMEDIATE );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.imm_size, FCML_DS_16 );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.is_signed, FCML_TRUE );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.imm16, (fcml_uint16_t)(fcml_int16_t)-255 );
	}
	fcml_x64iap_free( result );
}

void fcml_tf_parser_int_parse_test10(void) {
	fcml_st_x64iap_parser_result *result;
	CU_ASSERT_EQUAL( fcml_x64iap_parse( "mov 1+2", &result ), FCML_CEH_GEC_NO_ERROR );
	if( result->instruction != NULL ) {
		CU_ASSERT_EQUAL( result->instruction->operands[0].type, FCML_EOT_IMMEDIATE );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.imm_size, FCML_DS_8 );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.is_signed, FCML_FALSE );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.imm8, (fcml_uint8_t)(fcml_int8_t)3 );
	}
	fcml_x64iap_free( result );
}

void fcml_tf_parser_int_parse_test11(void) {
	fcml_st_x64iap_parser_result *result;
	CU_ASSERT_EQUAL( fcml_x64iap_parse( "mov 1+2*8/(15-13)-1", &result ), FCML_CEH_GEC_NO_ERROR );
	if( result->instruction != NULL ) {
		CU_ASSERT_EQUAL( result->instruction->operands[0].type, FCML_EOT_IMMEDIATE );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.imm_size, FCML_DS_8 );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.is_signed, FCML_FALSE );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.imm8, (fcml_uint8_t)8 );
	}
	fcml_x64iap_free( result );
}

void fcml_tf_parser_int_parse_test12(void) {
	fcml_st_x64iap_parser_result *result;
	CU_ASSERT_EQUAL( fcml_x64iap_parse( "mov 65535", &result ), FCML_CEH_GEC_NO_ERROR );
	if( result->instruction != NULL ) {
		CU_ASSERT_EQUAL( result->instruction->operands[0].type, FCML_EOT_IMMEDIATE );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.imm_size, FCML_DS_16 );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.is_signed, FCML_FALSE );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.imm16, (fcml_uint16_t)0xFFFF );
	}
	fcml_x64iap_free( result );
}

void fcml_tf_parser_int_parse_test13(void) {
	fcml_st_x64iap_parser_result *result;
	CU_ASSERT_EQUAL( fcml_x64iap_parse( "mov -32768", &result ), FCML_CEH_GEC_NO_ERROR );
	if( result->instruction != NULL ) {
		CU_ASSERT_EQUAL( result->instruction->operands[0].type, FCML_EOT_IMMEDIATE );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.imm_size, FCML_DS_16 );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.is_signed, FCML_TRUE );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.imm16, (fcml_uint16_t)-32768 );
	}
	fcml_x64iap_free( result );
}

void fcml_tf_parser_int_parse_test14(void) {
	fcml_st_x64iap_parser_result *result;
	CU_ASSERT_EQUAL( fcml_x64iap_parse( "mov (-2147483647 - 1)", &result ), FCML_CEH_GEC_NO_ERROR );
	CU_ASSERT_EQUAL( result->instruction->operands[0].type, FCML_EOT_IMMEDIATE );
	CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.imm_size, FCML_DS_32 );
	CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.is_signed, FCML_TRUE );
	CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.imm32, (fcml_uint32_t)(-2147483647 - 1) );
	fcml_x64iap_free( result );
}

void fcml_tf_parser_int_parse_test15(void) {
	fcml_st_x64iap_parser_result *result;
	CU_ASSERT_EQUAL( fcml_x64iap_parse( "mov (-9223372036854775807 - 1)", &result ), FCML_CEH_GEC_NO_ERROR );
	if( result->instruction != NULL ) {
		CU_ASSERT_EQUAL( result->instruction->operands[0].type, FCML_EOT_IMMEDIATE );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.imm_size, FCML_DS_64 );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.is_signed, FCML_TRUE );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.imm64, (fcml_uint64_t)(-9223372036854775807LL - 1) );
	}
	fcml_x64iap_free( result );
}

void fcml_tf_parser_int_parse_test16(void) {
	fcml_st_x64iap_parser_result *result;
	CU_ASSERT_EQUAL( fcml_x64iap_parse( "mov 18446744073709551615", &result ), FCML_CEH_GEC_NO_ERROR );
	if( result->instruction != NULL ) {
		CU_ASSERT_EQUAL( result->instruction->operands[0].type, FCML_EOT_IMMEDIATE );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.imm_size, FCML_DS_64 );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.is_signed, FCML_FALSE );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.imm64, (fcml_uint64_t)18446744073709551615ULL );
	}
	fcml_x64iap_free( result );
}

void fcml_tf_parser_int_parse_test17(void) {
	fcml_st_x64iap_parser_result *result;
	CU_ASSERT_EQUAL( fcml_x64iap_parse( "mov 5675", &result ), FCML_CEH_GEC_NO_ERROR );
	if( result->instruction != NULL ) {
		CU_ASSERT_EQUAL( result->instruction->operands[0].type, FCML_EOT_IMMEDIATE );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.imm_size, FCML_DS_16 );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.is_signed, FCML_FALSE );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.imm16, (fcml_uint16_t)5675 );
	}
	fcml_x64iap_free( result );
}

void fcml_tf_parser_int_parse_test18(void) {
	fcml_st_x64iap_parser_result *result;
	CU_ASSERT_EQUAL( fcml_x64iap_parse( "mov 2147483647", &result ), FCML_CEH_GEC_NO_ERROR );
	if( result->instruction != NULL ) {
		CU_ASSERT_EQUAL( result->instruction->operands[0].type, FCML_EOT_IMMEDIATE );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.imm_size, FCML_DS_32 );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.is_signed, FCML_FALSE );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.imm32, (fcml_uint32_t)2147483647 );
	}
	fcml_x64iap_free( result );
}

void fcml_tf_parser_int_parse_test19(void) {
	fcml_st_x64iap_parser_result *result;
	CU_ASSERT_EQUAL( fcml_x64iap_parse( "mov 4294967295", &result ), FCML_CEH_GEC_NO_ERROR );
	if( result->instruction != NULL ) {
		CU_ASSERT_EQUAL( result->instruction->operands[0].type, FCML_EOT_IMMEDIATE );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.imm_size, FCML_DS_32 );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.is_signed, FCML_FALSE );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.imm32, (fcml_uint32_t)4294967295U );
	}
	fcml_x64iap_free( result );
}

void fcml_tf_parser_int_parse_test20(void) {
	fcml_st_x64iap_parser_result *result;
	CU_ASSERT_EQUAL( fcml_x64iap_parse( "mov 4294967296", &result ), FCML_CEH_GEC_NO_ERROR );
	if( result->instruction != NULL ) {
		CU_ASSERT_EQUAL( result->instruction->operands[0].type, FCML_EOT_IMMEDIATE );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.imm_size, FCML_DS_64 );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.is_signed, FCML_FALSE );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.imm64, (fcml_uint64_t)4294967296ULL );
	}
	fcml_x64iap_free( result );
}

void fcml_tf_parser_int_parse_test21(void) {
	fcml_st_x64iap_parser_result *result;
	CU_ASSERT_EQUAL( fcml_x64iap_parse( "mov -0xFFFFFFFF", &result ), FCML_CEH_GEC_NO_ERROR );
	if( result->instruction != NULL ) {
		CU_ASSERT_EQUAL( result->instruction->operands[0].type, FCML_EOT_IMMEDIATE );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.imm_size, FCML_DS_64 );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.is_signed, FCML_TRUE );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.imm64, (fcml_uint64_t)-4294967295LL );
	}
	fcml_x64iap_free( result );
}

void fcml_tf_parser_int_parse_test22(void) {
	fcml_st_x64iap_parser_result *result;
	CU_ASSERT_EQUAL( fcml_x64iap_parse( "mov 255", &result ), FCML_CEH_GEC_NO_ERROR );
	if( result->instruction != NULL ) {
		CU_ASSERT_EQUAL( result->instruction->operands[0].type, FCML_EOT_IMMEDIATE );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.imm_size, FCML_DS_8 );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.is_signed, FCML_FALSE );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.imm8, 0xFF );
	}
	fcml_x64iap_free( result );
}

void fcml_tf_parser_int_parse_test23(void) {
	fcml_st_x64iap_parser_result *result;
	CU_ASSERT_EQUAL( fcml_x64iap_parse( "mov 1", &result ), FCML_CEH_GEC_NO_ERROR );
	if( result->instruction != NULL ) {
		CU_ASSERT_EQUAL( result->instruction->operands[0].type, FCML_EOT_IMMEDIATE );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.imm_size, FCML_DS_8 );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.is_signed, FCML_FALSE );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.imm8, 1 );
	}
	fcml_x64iap_free( result );
}

CU_TestInfo fcml_ti_parser[] = {
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
    CU_TEST_INFO_NULL,
};

CU_SuiteInfo fcml_si_intel_parser[] = {
    { "suite-fcml-parser", fcml_tf_parser_suite_init, fcml_tf_parser_suite_cleanup, fcml_ti_parser },
    CU_SUITE_INFO_NULL,
};
