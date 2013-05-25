/*
 * modrm_encoder_t.c
 *
 *  Created on: 23-05-2013
 *      Author: tAs
 */

#include "fcml_env.h"
#include "modrm_encoder_t.h"
#include "fcml_modrm_encoder.h"

int fcml_tf_modrm_encoder_suite_init(void) {
	return 0;
}

int fcml_tf_modrm_encoder_suite_cleanup(void) {
	return 0;
}

// [EAX]
void fcml_tf_modrm_encoder_test_1(void) {

	fcml_esa effective_address_size;

	fcml_st_modrm modrm;
	fcml_fn_env_memory_clean( &modrm, sizeof( modrm ) );

	modrm.base.type = FCML_REG_GPR;
	modrm.base.reg = FCML_REG_EAX;
	modrm.base.size = FCML_DS_32;

	fcml_ceh_error error = fcml_fn_modrm_calculate_efective_address_size( &modrm, &effective_address_size );

	CU_ASSERT_EQUAL( effective_address_size, FCML_ESA_SF_32 );
	CU_ASSERT_EQUAL( error, FCML_CEH_GEC_NO_ERROR );
}

// [RAX]
void fcml_tf_modrm_encoder_test_2(void) {

	fcml_esa effective_address_size;

	fcml_st_modrm modrm;
	fcml_fn_env_memory_clean( &modrm, sizeof( modrm ) );

	modrm.base.type = FCML_REG_GPR;
	modrm.base.reg = FCML_REG_RAX;
	modrm.base.size = FCML_DS_64;

	fcml_ceh_error error = fcml_fn_modrm_calculate_efective_address_size( &modrm, &effective_address_size );

	CU_ASSERT_EQUAL( effective_address_size, FCML_ESA_SF_64 );
	CU_ASSERT_EQUAL( error, FCML_CEH_GEC_NO_ERROR );
}

// [AX]
void fcml_tf_modrm_encoder_test_3(void) {

	fcml_esa effective_address_size;

	fcml_st_modrm modrm;
	fcml_fn_env_memory_clean( &modrm, sizeof( modrm ) );

	modrm.base.type = FCML_REG_GPR;
	modrm.base.reg = FCML_REG_AX;
	modrm.base.size = FCML_DS_16;

	fcml_ceh_error error = fcml_fn_modrm_calculate_efective_address_size( &modrm, &effective_address_size );

	CU_ASSERT_EQUAL( effective_address_size, FCML_ESA_SF_16 );
	CU_ASSERT_EQUAL( error, FCML_CEH_GEC_NO_ERROR );
}


// SIB index [AX]
void fcml_tf_modrm_encoder_test_4(void) {

	fcml_esa effective_address_size;

	fcml_st_modrm modrm;
	fcml_fn_env_memory_clean( &modrm, sizeof( modrm ) );

	modrm.index.type = FCML_REG_GPR;
	modrm.index.reg = FCML_REG_AX;
	modrm.index.size = FCML_DS_16;

	fcml_ceh_error error = fcml_fn_modrm_calculate_efective_address_size( &modrm, &effective_address_size );

	CU_ASSERT_EQUAL( effective_address_size, FCML_ESA_SF_16 );
	CU_ASSERT_EQUAL( error, FCML_CEH_GEC_NO_ERROR );
}

// SIB index [EAX]
void fcml_tf_modrm_encoder_test_5(void) {

	fcml_esa effective_address_size;

	fcml_st_modrm modrm;
	fcml_fn_env_memory_clean( &modrm, sizeof( modrm ) );

	modrm.index.type = FCML_REG_GPR;
	modrm.index.reg = FCML_REG_EAX;
	modrm.index.size = FCML_DS_32;

	fcml_ceh_error error = fcml_fn_modrm_calculate_efective_address_size( &modrm, &effective_address_size );

	CU_ASSERT_EQUAL( effective_address_size, FCML_ESA_SF_32 );
	CU_ASSERT_EQUAL( error, FCML_CEH_GEC_NO_ERROR );
}

// SIB index [RAX]
void fcml_tf_modrm_encoder_test_6(void) {

	fcml_esa effective_address_size;

	fcml_st_modrm modrm;
	fcml_fn_env_memory_clean( &modrm, sizeof( modrm ) );

	modrm.index.type = FCML_REG_GPR;
	modrm.index.reg = FCML_REG_RAX;
	modrm.index.size = FCML_DS_64;

	fcml_ceh_error error = fcml_fn_modrm_calculate_efective_address_size( &modrm, &effective_address_size );

	CU_ASSERT_EQUAL( effective_address_size, FCML_ESA_SF_64 );
	CU_ASSERT_EQUAL( error, FCML_CEH_GEC_NO_ERROR );
}

// displacement 8
void fcml_tf_modrm_encoder_test_7(void) {

	fcml_esa effective_address_size;

	fcml_st_modrm modrm;
	fcml_fn_env_memory_clean( &modrm, sizeof( modrm ) );

	modrm.displacement.size = FCML_DS_8;

	fcml_ceh_error error = fcml_fn_modrm_calculate_efective_address_size( &modrm, &effective_address_size );

	CU_ASSERT( effective_address_size & FCML_ESA_SF_16 );
	CU_ASSERT( effective_address_size & FCML_ESA_SF_32 );
	CU_ASSERT( effective_address_size & FCML_ESA_SF_64 );
	CU_ASSERT_EQUAL( error, FCML_CEH_GEC_NO_ERROR );
}

// displacement 16
void fcml_tf_modrm_encoder_test_8(void) {

	fcml_esa effective_address_size;

	fcml_st_modrm modrm;
	fcml_fn_env_memory_clean( &modrm, sizeof( modrm ) );

	modrm.displacement.size = FCML_DS_16;

	fcml_ceh_error error = fcml_fn_modrm_calculate_efective_address_size( &modrm, &effective_address_size );

	CU_ASSERT( effective_address_size & FCML_ESA_SF_16 );
	CU_ASSERT( effective_address_size & FCML_ESA_SF_32 );
	CU_ASSERT( effective_address_size & FCML_ESA_SF_64 );
	CU_ASSERT_EQUAL( error, FCML_CEH_GEC_NO_ERROR );
}

// displacement 64
void fcml_tf_modrm_encoder_test_9(void) {

	fcml_esa effective_address_size;

	fcml_st_modrm modrm;
	fcml_fn_env_memory_clean( &modrm, sizeof( modrm ) );

	modrm.displacement.size = FCML_DS_32;

	fcml_ceh_error error = fcml_fn_modrm_calculate_efective_address_size( &modrm, &effective_address_size );

	CU_ASSERT( !(effective_address_size & FCML_ESA_SF_16) );
	CU_ASSERT( effective_address_size & FCML_ESA_SF_32 );
	CU_ASSERT( effective_address_size & FCML_ESA_SF_64 );
	CU_ASSERT_EQUAL( error, FCML_CEH_GEC_NO_ERROR );
}

// SIB index [XMM]
void fcml_tf_modrm_encoder_test_10(void) {

	fcml_esa effective_address_size;

	fcml_st_modrm modrm;
	fcml_fn_env_memory_clean( &modrm, sizeof( modrm ) );

	modrm.index.type = FCML_REG_SIMD;
	modrm.index.reg = FCML_REG_XMM1;
	modrm.index.size = FCML_DS_128;

	fcml_ceh_error error = fcml_fn_modrm_calculate_efective_address_size( &modrm, &effective_address_size );

	CU_ASSERT( !(effective_address_size & FCML_ESA_SF_16) );
	CU_ASSERT( effective_address_size & FCML_ESA_SF_32 );
	CU_ASSERT( effective_address_size & FCML_ESA_SF_64 );
	CU_ASSERT_EQUAL( error, FCML_CEH_GEC_NO_ERROR );
}

// SIB index [YMM]
void fcml_tf_modrm_encoder_test_11(void) {

	fcml_esa effective_address_size;

	fcml_st_modrm modrm;
	fcml_fn_env_memory_clean( &modrm, sizeof( modrm ) );

	modrm.index.type = FCML_REG_SIMD;
	modrm.index.reg = FCML_REG_XMM1;
	modrm.index.size = FCML_DS_256;

	fcml_ceh_error error = fcml_fn_modrm_calculate_efective_address_size( &modrm, &effective_address_size );

	CU_ASSERT( !(effective_address_size & FCML_ESA_SF_16) );
	CU_ASSERT( effective_address_size & FCML_ESA_SF_32 );
	CU_ASSERT( effective_address_size & FCML_ESA_SF_64 );
	CU_ASSERT_EQUAL( error, FCML_CEH_GEC_NO_ERROR );
}

// Encode disp16
void fcml_tf_modrm_encoder_test_12(void) {

	fcml_st_modrm modrm;
	fcml_fn_env_memory_clean( &modrm, sizeof( modrm ) );

	modrm.displacement.size = FCML_DS_16;
	modrm.displacement.dis16 = 0xF2F1;

	fcml_st_modrm_context context;
	context.effective_address_size = FCML_DS_16;

	fcml_st_encoded_modrm encoded_modrm;
	fcml_fn_env_memory_clean( &encoded_modrm, sizeof( encoded_modrm ) );

	fcml_ceh_error error = fcml_fn_modrm_encode( &context, &modrm, &encoded_modrm );

	CU_ASSERT_EQUAL( error, FCML_CEH_GEC_NO_ERROR );
	CU_ASSERT_EQUAL( encoded_modrm.displacement[0], 0xF1 );
	CU_ASSERT_EQUAL( encoded_modrm.displacement[1], 0xF2 );
	CU_ASSERT_EQUAL( encoded_modrm.displacement_size, 2 );
}

// Encode disp8
void fcml_tf_modrm_encoder_test_13(void) {

	fcml_st_modrm modrm;
	fcml_fn_env_memory_clean( &modrm, sizeof( modrm ) );

	modrm.displacement.size = FCML_DS_8;
	modrm.displacement.dis8 = 0xF1;

	fcml_st_modrm_context context;
	context.effective_address_size = FCML_DS_16;

	fcml_st_encoded_modrm encoded_modrm;
	fcml_fn_env_memory_clean( &encoded_modrm, sizeof( encoded_modrm ) );

	fcml_ceh_error error = fcml_fn_modrm_encode( &context, &modrm, &encoded_modrm );

	CU_ASSERT_EQUAL( error, FCML_CEH_GEC_NO_ERROR );
	CU_ASSERT_EQUAL( encoded_modrm.displacement[0], 0xF1 );
	CU_ASSERT_EQUAL( encoded_modrm.displacement[1], 0xFF );
	CU_ASSERT_EQUAL( encoded_modrm.displacement_size, 2 );
}

// Encode disp8
void fcml_tf_modrm_encoder_16_bit_encoding_1(void) {

	fcml_st_modrm modrm;
	fcml_fn_env_memory_clean( &modrm, sizeof( modrm ) );
	fcml_st_encoded_modrm encoded_modrm;
	fcml_fn_env_memory_clean( &encoded_modrm, sizeof( encoded_modrm ) );
	fcml_st_modrm_context context;
	context.effective_address_size = FCML_DS_16;

	modrm.base.size = FCML_DS_16;
	modrm.base.reg = FCML_REG_BX;
	modrm.index.size = FCML_DS_16;
	modrm.index.reg = FCML_REG_SI;

	fcml_ceh_error error = fcml_fn_modrm_encode( &context, &modrm, &encoded_modrm );

	CU_ASSERT_EQUAL( error, FCML_CEH_GEC_NO_ERROR );
	CU_ASSERT_EQUAL( encoded_modrm.displacement_size, 0 );
	CU_ASSERT_EQUAL( encoded_modrm.ext_reg, 0 );
	CU_ASSERT_EQUAL( encoded_modrm.ext_rm, 0 );
	CU_ASSERT_EQUAL( encoded_modrm.sib.is_not_null, FCML_FALSE );
	CU_ASSERT_EQUAL( encoded_modrm.sib.value, 0 );
	CU_ASSERT_EQUAL( encoded_modrm.modrm, 0 );
}

CU_TestInfo fctl_ti_modrm_encoder[] = {
    { "fcml_tf_modrm_encoder_test_1", fcml_tf_modrm_encoder_test_1 },
    { "fcml_tf_modrm_encoder_test_2", fcml_tf_modrm_encoder_test_2 },
    { "fcml_tf_modrm_encoder_test_3", fcml_tf_modrm_encoder_test_3 },
    { "fcml_tf_modrm_encoder_test_4", fcml_tf_modrm_encoder_test_4 },
    { "fcml_tf_modrm_encoder_test_5", fcml_tf_modrm_encoder_test_5 },
    { "fcml_tf_modrm_encoder_test_6", fcml_tf_modrm_encoder_test_6 },
    { "fcml_tf_modrm_encoder_test_7", fcml_tf_modrm_encoder_test_7 },
    { "fcml_tf_modrm_encoder_test_8", fcml_tf_modrm_encoder_test_8 },
    { "fcml_tf_modrm_encoder_test_9", fcml_tf_modrm_encoder_test_9 },
    { "fcml_tf_modrm_encoder_test_10", fcml_tf_modrm_encoder_test_10 },
    { "fcml_tf_modrm_encoder_test_11", fcml_tf_modrm_encoder_test_11 },
    { "fcml_tf_modrm_encoder_test_12", fcml_tf_modrm_encoder_test_12 },
    { "fcml_tf_modrm_encoder_test_13", fcml_tf_modrm_encoder_test_13 },
    { "fcml_tf_modrm_encoder_16_bit_encoding_1", fcml_tf_modrm_encoder_16_bit_encoding_1 },
    CU_TEST_INFO_NULL,
};

CU_SuiteInfo fctl_si_modrm_encoder[] = {
    { "suite-modrm-encoder", fcml_tf_modrm_encoder_suite_init, fcml_tf_modrm_encoder_suite_cleanup, fctl_ti_modrm_encoder },
    CU_SUITE_INFO_NULL,
};


