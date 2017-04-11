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

#include "utils_t.h"

#include <fcml_utils.h>

fcml_bool fcml_tf_utils_suite_init(void) {
	return FCML_TRUE;
}

fcml_bool fcml_tf_utils_suite_cleanup(void) {
	return FCML_TRUE;
}

void fcml_fn_utils_test_sign_convert_imm_to_int8(void) {

	fcml_int8_t value;

	fcml_st_integer imm;

	imm.size = FCML_DS_8;
	imm.int8 = (fcml_int8_t)0xFF;
	imm.is_signed = FCML_FALSE;
	STF_ASSERT_EQUAL( fcml_fn_utils_convert_integer_to_int8( &imm, &value ), FCML_CEH_GEC_NO_ERROR );
	STF_ASSERT_EQUAL( value, (fcml_int8_t)-1 );

	imm.size = FCML_DS_8;
	imm.int8 = 45;
	STF_ASSERT_EQUAL( fcml_fn_utils_convert_integer_to_int8( &imm, &value ), FCML_CEH_GEC_NO_ERROR );
	STF_ASSERT_EQUAL( value, (fcml_int8_t)45 );

	imm.size = FCML_DS_16;
	imm.int16 = (fcml_int16_t)0xFFFF;
	imm.is_signed = FCML_FALSE;
	STF_ASSERT_EQUAL( fcml_fn_utils_convert_integer_to_int8( &imm, &value ), FCML_CEH_GEC_VALUE_OUT_OF_RANGE );

	imm.size = FCML_DS_16;
	imm.int16 = (fcml_int16_t)0xFFFF;
	imm.is_signed = FCML_TRUE;
	STF_ASSERT_EQUAL( fcml_fn_utils_convert_integer_to_int8( &imm, &value ), FCML_CEH_GEC_NO_ERROR );
	STF_ASSERT_EQUAL( value, (fcml_int8_t)-1 );

	imm.size = FCML_DS_32;
	imm.int32 = 0xFFFFFFFF;
	imm.is_signed = FCML_FALSE;
	STF_ASSERT_EQUAL( fcml_fn_utils_convert_integer_to_int8( &imm, &value ), FCML_CEH_GEC_VALUE_OUT_OF_RANGE );

	imm.size = FCML_DS_32;
	imm.int32 = 0xFFFFFFFF;
	imm.is_signed = FCML_TRUE;
	STF_ASSERT_EQUAL( fcml_fn_utils_convert_integer_to_int8( &imm, &value ), FCML_CEH_GEC_NO_ERROR );
	STF_ASSERT_EQUAL( value, (fcml_int8_t)-1 );

	imm.size = FCML_DS_32;
	imm.int32 = 0x00FFFFFF;
	imm.is_signed = FCML_FALSE;
	STF_ASSERT_EQUAL( fcml_fn_utils_convert_integer_to_int8( &imm, &value ), FCML_CEH_GEC_VALUE_OUT_OF_RANGE );

	imm.size = FCML_DS_16;
	imm.int16 = 129;
	imm.is_signed = FCML_TRUE;
	STF_ASSERT_EQUAL( fcml_fn_utils_convert_integer_to_int8( &imm, &value ), FCML_CEH_GEC_VALUE_OUT_OF_RANGE );

	imm.size = FCML_DS_32;
	imm.int32 = 129;
	imm.is_signed = FCML_FALSE;
	STF_ASSERT_EQUAL( fcml_fn_utils_convert_integer_to_int8( &imm, &value ), FCML_CEH_GEC_VALUE_OUT_OF_RANGE );

}

void fcml_fn_utils_test_sign_convert_imm_to_int16(void) {

	fcml_int16_t value;

	fcml_st_integer imm;

	imm.size = FCML_DS_8;
	imm.int8 = (fcml_int8_t)0xFF;
	imm.is_signed = FCML_TRUE;
	STF_ASSERT_EQUAL( fcml_fn_utils_convert_integer_to_int16( &imm, &value ), FCML_CEH_GEC_NO_ERROR );
	STF_ASSERT_EQUAL( value, (fcml_int16_t)-1 );

	imm.size = FCML_DS_8;
	imm.int8 = 45;
	imm.is_signed = FCML_TRUE;
	STF_ASSERT_EQUAL( fcml_fn_utils_convert_integer_to_int16( &imm, &value ), FCML_CEH_GEC_NO_ERROR );
	STF_ASSERT_EQUAL( value, (fcml_int16_t)45 );

	imm.size = FCML_DS_16;
	imm.int16 = (fcml_int16_t)0xFFFF;
	imm.is_signed = FCML_TRUE;
	STF_ASSERT_EQUAL( fcml_fn_utils_convert_integer_to_int16( &imm, &value ), FCML_CEH_GEC_NO_ERROR );
	STF_ASSERT_EQUAL( value, (fcml_int16_t)-1 );

	imm.size = FCML_DS_16;
	imm.int16 = (fcml_int16_t)0xFFFF;
	imm.is_signed = FCML_FALSE;
	STF_ASSERT_EQUAL( fcml_fn_utils_convert_integer_to_int16( &imm, &value ), FCML_CEH_GEC_NO_ERROR );
	STF_ASSERT_EQUAL( value, (fcml_int16_t)-1 );

	imm.size = FCML_DS_32;
	imm.int32 = 0xFFFFFFFF;
	imm.is_signed = FCML_TRUE;
	STF_ASSERT_EQUAL( fcml_fn_utils_convert_integer_to_int16( &imm, &value ), FCML_CEH_GEC_NO_ERROR );
	STF_ASSERT_EQUAL( value, (fcml_int16_t)-1 );

	imm.size = FCML_DS_32;
	imm.int32 = 0x00FFFFFF;
	imm.is_signed = FCML_TRUE;
	STF_ASSERT_EQUAL( fcml_fn_utils_convert_integer_to_int16( &imm, &value ), FCML_CEH_GEC_VALUE_OUT_OF_RANGE );

	imm.size = FCML_DS_32;
	imm.int32 = 32768;
	imm.is_signed = FCML_TRUE;
	STF_ASSERT_EQUAL( fcml_fn_utils_convert_integer_to_int16( &imm, &value ), FCML_CEH_GEC_VALUE_OUT_OF_RANGE );

}

void fcml_fn_utils_test_sign_convert_imm_to_int32(void) {

	fcml_int32_t value;

	fcml_st_integer imm;

	imm.size = FCML_DS_8;
	imm.int8 = (fcml_int8_t)0xFF;
	imm.is_signed = FCML_TRUE;
	STF_ASSERT_EQUAL( fcml_fn_utils_convert_integer_to_int32( &imm, &value ), FCML_CEH_GEC_NO_ERROR );
	STF_ASSERT_EQUAL( value, (fcml_int32_t)-1 );

	imm.size = FCML_DS_8;
	imm.int8 = 45;
	imm.is_signed = FCML_TRUE;
	STF_ASSERT_EQUAL( fcml_fn_utils_convert_integer_to_int32( &imm, &value ), FCML_CEH_GEC_NO_ERROR );
	STF_ASSERT_EQUAL( value, (fcml_int32_t)45 );

	imm.size = FCML_DS_16;
	imm.int16 = (fcml_int16_t)0xFFFF;
	imm.is_signed = FCML_TRUE;
	STF_ASSERT_EQUAL( fcml_fn_utils_convert_integer_to_int32( &imm, &value ), FCML_CEH_GEC_NO_ERROR );
	STF_ASSERT_EQUAL( value, (fcml_int32_t)-1 );

	imm.size = FCML_DS_32;
	imm.int32 = 0xFFFFFFFF;
	imm.is_signed = FCML_TRUE;
	STF_ASSERT_EQUAL( fcml_fn_utils_convert_integer_to_int32( &imm, &value ), FCML_CEH_GEC_NO_ERROR );
	STF_ASSERT_EQUAL( value, (fcml_int32_t)-1 );

	imm.size = FCML_DS_32;
	imm.int32 = 0x00FFFFFF;
	imm.is_signed = FCML_TRUE;
	STF_ASSERT_EQUAL( fcml_fn_utils_convert_integer_to_int32( &imm, &value ), FCML_CEH_GEC_NO_ERROR );
	STF_ASSERT_EQUAL( value, (fcml_int32_t)0x00FFFFFF );

}

fcml_stf_test_case fcml_ti_utils[] = {
	{ "fcml_fn_utils_test_sign_convert_imm_to_int8", fcml_fn_utils_test_sign_convert_imm_to_int8 },
	{ "fcml_fn_utils_test_sign_convert_imm_to_int16", fcml_fn_utils_test_sign_convert_imm_to_int16 },
	{ "fcml_fn_utils_test_sign_convert_imm_to_int32", fcml_fn_utils_test_sign_convert_imm_to_int32 },
	FCML_STF_NULL_TEST
};

fcml_stf_test_suite fcml_si_utils = {
	"suite-fcml-utils", fcml_tf_utils_suite_init, fcml_tf_utils_suite_cleanup, fcml_ti_utils
};


