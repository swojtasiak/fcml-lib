/*
 * modrm_decoder.c
 *
 *  Created on: 04-02-2013
 *      Author: Slawomir Wojtasiak
 */

#include "modrm_decoder_t.h"

#include "fcml_modrm_decoder.h"
#include "fcml_env.h"

fcml_st_modrm_context fcml_ifn_modrm_decoder_alloc_ctx() {
	fcml_st_modrm_context context;
	fcml_fn_env_memory_clean( &context, sizeof( context ) );
	return context;
}

int fcml_tf_modrm_decoder_suite_init(void) {
	return 0;
}

int fcml_tf_modrm_decoder_suite_cleanup(void) {
	return 0;
}

void fcml_tf_modrm_decoder_test_1(void) {

	fcml_st_modrm_context context = fcml_ifn_modrm_decoder_alloc_ctx();

	context.addr_form = FCML_MODRM_AF_32_BIT;
	context.effective_address_size = FCML_DS_16;

	fcml_uint8_t buffer[] = {23};

	fcml_st_memory_stream stream;
	stream.base_address = &buffer;
	stream.size = sizeof( buffer );
	stream.offset = 0;

	fcml_st_modrm_source modrm_source;
	modrm_source.ext_b = 0;
	modrm_source.ext_r = 0;
	modrm_source.ext_x = 0;
	modrm_source.stream = stream;
	fcml_st_modrm decoded_modrm;

	fcml_ceh_error error = fcml_fn_modrm_decode( &context, &modrm_source, &decoded_modrm );

	CU_ASSERT_EQUAL( error, FCML_CEH_GEC_NO_ERROR );
	CU_ASSERT_EQUAL( decoded_modrm.base.type, FCML_REG_GPR );
	CU_ASSERT_EQUAL( decoded_modrm.base.reg, FCML_REG_BX );
	CU_ASSERT_EQUAL( decoded_modrm.base.size, FCML_DS_16 );
	CU_ASSERT_EQUAL( decoded_modrm.index.type, FCML_REG_UNDEFINED );
	CU_ASSERT_EQUAL( decoded_modrm.index.reg, 0 );
	CU_ASSERT_EQUAL( decoded_modrm.index.size, 0 );
	CU_ASSERT_EQUAL( decoded_modrm.reg_opcode, FCML_REG_DX );
	CU_ASSERT_EQUAL( decoded_modrm.displacement.size, 0 );
	CU_ASSERT_EQUAL( decoded_modrm.reg.is_not_null, FCML_FALSE );
	CU_ASSERT_EQUAL( decoded_modrm.scale_factor, 0 );

}

void fcml_tf_modrm_decoder_test_2(void) {

	fcml_st_modrm_context context = fcml_ifn_modrm_decoder_alloc_ctx();

	context.addr_form = FCML_MODRM_AF_32_BIT;
	context.effective_address_size = FCML_DS_16;

	fcml_uint8_t buffer[] = {0x1E, 0x01, 0x02};

	fcml_st_memory_stream stream;
	stream.base_address = &buffer;
	stream.size = sizeof( buffer );
	stream.offset = 0;

	fcml_st_modrm_source modrm_source;
	modrm_source.ext_b = 0;
	modrm_source.ext_r = 0;
	modrm_source.ext_x = 0;
	modrm_source.stream = stream;
	fcml_st_modrm decoded_modrm;

	fcml_ceh_error error = fcml_fn_modrm_decode( &context, &modrm_source, &decoded_modrm );

	CU_ASSERT_EQUAL( error, FCML_CEH_GEC_NO_ERROR );
	CU_ASSERT_EQUAL( decoded_modrm.base.type, FCML_REG_UNDEFINED );
	CU_ASSERT_EQUAL( decoded_modrm.base.reg, 0 );
	CU_ASSERT_EQUAL( decoded_modrm.base.size, 0 );
	CU_ASSERT_EQUAL( decoded_modrm.index.type, FCML_REG_UNDEFINED );
	CU_ASSERT_EQUAL( decoded_modrm.index.reg, 0 );
	CU_ASSERT_EQUAL( decoded_modrm.index.size, 0 );
	CU_ASSERT_EQUAL( decoded_modrm.reg_opcode, FCML_REG_BX );
	CU_ASSERT_EQUAL( decoded_modrm.displacement.size, FCML_DS_16 );
	CU_ASSERT_EQUAL( decoded_modrm.displacement.dis16, 0x0201 );
	CU_ASSERT_EQUAL( decoded_modrm.reg.is_not_null, FCML_FALSE );
	CU_ASSERT_EQUAL( decoded_modrm.scale_factor, 0 );

}

void fcml_tf_modrm_decoder_test_3(void) {

	fcml_st_modrm_context context = fcml_ifn_modrm_decoder_alloc_ctx();

	context.addr_form = FCML_MODRM_AF_32_BIT;
	context.effective_address_size = FCML_DS_16;

	fcml_uint8_t buffer[] = {0x0B};

	fcml_st_memory_stream stream;
	stream.base_address = &buffer;
	stream.size = sizeof( buffer );
	stream.offset = 0;

	fcml_st_modrm_source modrm_source;
	modrm_source.ext_b = 0;
	modrm_source.ext_r = 0;
	modrm_source.ext_x = 0;
	modrm_source.stream = stream;
	fcml_st_modrm decoded_modrm;

	fcml_ceh_error error = fcml_fn_modrm_decode( &context, &modrm_source, &decoded_modrm );

	CU_ASSERT_EQUAL( error, FCML_CEH_GEC_NO_ERROR );
	CU_ASSERT_EQUAL( decoded_modrm.base.type, FCML_REG_GPR );
	CU_ASSERT_EQUAL( decoded_modrm.base.reg, FCML_REG_BP );
	CU_ASSERT_EQUAL( decoded_modrm.base.size, FCML_DS_16 );
	CU_ASSERT_EQUAL( decoded_modrm.index.type, FCML_REG_GPR );
	CU_ASSERT_EQUAL( decoded_modrm.index.reg, FCML_REG_DI );
	CU_ASSERT_EQUAL( decoded_modrm.index.size, FCML_DS_16 );
	CU_ASSERT_EQUAL( decoded_modrm.displacement.size, 0 );
	CU_ASSERT_EQUAL( decoded_modrm.reg_opcode, FCML_REG_CX );
	CU_ASSERT_EQUAL( decoded_modrm.reg.is_not_null, FCML_FALSE );
	CU_ASSERT_EQUAL( decoded_modrm.scale_factor, 0 );

}

void fcml_tf_modrm_decoder_test_4(void) {

	fcml_st_modrm_context context = fcml_ifn_modrm_decoder_alloc_ctx();

	context.addr_form = FCML_MODRM_AF_32_BIT;
	context.effective_address_size = FCML_DS_16;

	fcml_uint8_t buffer[] = {0x14};

	fcml_st_memory_stream stream;
	stream.base_address = &buffer;
	stream.size = sizeof( buffer );
	stream.offset = 0;

	fcml_st_modrm_source modrm_source;
	modrm_source.ext_b = 0;
	modrm_source.ext_r = 0;
	modrm_source.ext_x = 0;
	modrm_source.stream = stream;
	fcml_st_modrm decoded_modrm;

	fcml_ceh_error error = fcml_fn_modrm_decode( &context, &modrm_source, &decoded_modrm );

	CU_ASSERT_EQUAL( error, FCML_CEH_GEC_NO_ERROR );
	CU_ASSERT_EQUAL( decoded_modrm.base.type, FCML_REG_GPR );
	CU_ASSERT_EQUAL( decoded_modrm.base.reg, FCML_REG_SI );
	CU_ASSERT_EQUAL( decoded_modrm.base.size, FCML_DS_16 );
	CU_ASSERT_EQUAL( decoded_modrm.index.type, FCML_REG_UNDEFINED );
	CU_ASSERT_EQUAL( decoded_modrm.index.reg, 0 );
	CU_ASSERT_EQUAL( decoded_modrm.index.size, 0 );
	CU_ASSERT_EQUAL( decoded_modrm.reg_opcode, FCML_REG_DX );
	CU_ASSERT_EQUAL( decoded_modrm.displacement.size, 0 );
	CU_ASSERT_EQUAL( decoded_modrm.reg.is_not_null, FCML_FALSE );
	CU_ASSERT_EQUAL( decoded_modrm.scale_factor, 0 );

}

void fcml_tf_modrm_decoder_test_5(void) {

	fcml_st_modrm_context context = fcml_ifn_modrm_decoder_alloc_ctx();

	context.addr_form = FCML_MODRM_AF_64_BIT;
	context.effective_address_size = FCML_DS_16;

	fcml_uint8_t buffer[] = {0x14};

	fcml_st_memory_stream stream;
	stream.base_address = &buffer;
	stream.size = sizeof( buffer );
	stream.offset = 0;

	fcml_st_modrm_source modrm_source;
	modrm_source.ext_b = 0;
	modrm_source.ext_r = 0;
	modrm_source.ext_x = 0;
	modrm_source.stream = stream;
	fcml_st_modrm decoded_modrm;

	fcml_ceh_error error = fcml_fn_modrm_decode( &context, &modrm_source, &decoded_modrm );

	CU_ASSERT_EQUAL( error, FCML_EN_UNSUPPORTED_ADDRESSING_MODE );
	CU_ASSERT_EQUAL( decoded_modrm.base.type, FCML_REG_UNDEFINED );
	CU_ASSERT_EQUAL( decoded_modrm.base.reg, 0 );
	CU_ASSERT_EQUAL( decoded_modrm.base.size, 0 );
	CU_ASSERT_EQUAL( decoded_modrm.index.type, FCML_REG_UNDEFINED );
	CU_ASSERT_EQUAL( decoded_modrm.index.reg, 0 );
	CU_ASSERT_EQUAL( decoded_modrm.index.size, 0 );
	CU_ASSERT_EQUAL( decoded_modrm.reg_opcode, 0 );
	CU_ASSERT_EQUAL( decoded_modrm.displacement.size, 0 );
	CU_ASSERT_EQUAL( decoded_modrm.reg.is_not_null, FCML_FALSE );
	CU_ASSERT_EQUAL( decoded_modrm.scale_factor, 0 );

}

void fcml_tf_modrm_decoder_test_6(void) {

	fcml_st_modrm_context context = fcml_ifn_modrm_decoder_alloc_ctx();

	context.addr_form = FCML_MODRM_AF_32_BIT;
	context.effective_address_size = FCML_DS_16;

	fcml_uint8_t buffer[] = {0x73, 0x01};

	fcml_st_memory_stream stream;
	stream.base_address = &buffer;
	stream.size = sizeof( buffer );
	stream.offset = 0;

	fcml_st_modrm_source modrm_source;
	modrm_source.ext_b = 0;
	modrm_source.ext_r = 0;
	modrm_source.ext_x = 0;
	modrm_source.stream = stream;
	fcml_st_modrm decoded_modrm;

	fcml_ceh_error error = fcml_fn_modrm_decode( &context, &modrm_source, &decoded_modrm );

	CU_ASSERT_EQUAL( error, FCML_CEH_GEC_NO_ERROR );
	CU_ASSERT_EQUAL( decoded_modrm.base.type, FCML_REG_GPR );
	CU_ASSERT_EQUAL( decoded_modrm.base.reg, FCML_REG_BP );
	CU_ASSERT_EQUAL( decoded_modrm.base.size, FCML_DS_16 );
	CU_ASSERT_EQUAL( decoded_modrm.index.type, FCML_REG_GPR );
	CU_ASSERT_EQUAL( decoded_modrm.index.reg, FCML_REG_DI );
	CU_ASSERT_EQUAL( decoded_modrm.index.size, FCML_DS_16 );
	CU_ASSERT_EQUAL( decoded_modrm.reg_opcode, FCML_REG_SI );
	CU_ASSERT_EQUAL( decoded_modrm.displacement.size, FCML_DS_8 );
	CU_ASSERT_EQUAL( decoded_modrm.displacement.dis8, 0x01 );
	CU_ASSERT_EQUAL( decoded_modrm.reg.is_not_null, FCML_FALSE );
	CU_ASSERT_EQUAL( decoded_modrm.scale_factor, 0 );

}

void fcml_tf_modrm_decoder_test_7(void) {

	fcml_st_modrm_context context = fcml_ifn_modrm_decoder_alloc_ctx();

	context.addr_form = FCML_MODRM_AF_32_BIT;
	context.effective_address_size = FCML_DS_16;

	fcml_uint8_t buffer[] = {0x73};

	fcml_st_memory_stream stream;
	stream.base_address = &buffer;
	stream.size = sizeof( buffer );
	stream.offset = 0;

	fcml_st_modrm_source modrm_source;
	modrm_source.ext_b = 0;
	modrm_source.ext_r = 0;
	modrm_source.ext_x = 0;
	modrm_source.stream = stream;
	fcml_st_modrm decoded_modrm;

	fcml_ceh_error error = fcml_fn_modrm_decode( &context, &modrm_source, &decoded_modrm );

	CU_ASSERT_EQUAL( error, FCML_CEH_GEC_EOF );

}

CU_TestInfo fctl_ti_modrm_decoder[] = {
    { "fcml_tf_modrm_decoder_test_1", fcml_tf_modrm_decoder_test_1 },
    { "fcml_tf_modrm_decoder_test_2", fcml_tf_modrm_decoder_test_2 },
    { "fcml_tf_modrm_decoder_test_3", fcml_tf_modrm_decoder_test_3 },
    { "fcml_tf_modrm_decoder_test_4", fcml_tf_modrm_decoder_test_4 },
    { "fcml_tf_modrm_decoder_test_5", fcml_tf_modrm_decoder_test_5 },
    { "fcml_tf_modrm_decoder_test_6", fcml_tf_modrm_decoder_test_6 },
    { "fcml_tf_modrm_decoder_test_7", fcml_tf_modrm_decoder_test_7 },
    CU_TEST_INFO_NULL,
};

CU_SuiteInfo fctl_si_modrm_decoder[] = {
    { "suite-modrm", fcml_tf_modrm_decoder_suite_init, fcml_tf_modrm_decoder_suite_cleanup, fctl_ti_modrm_decoder },
    CU_SUITE_INFO_NULL,
};


