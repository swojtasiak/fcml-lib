/*
 * modrm_decoder.c
 *
 *  Created on: 04-02-2013
 *      Author: Slawomir Wojtasiak
 */

#include "modrm_decoder_t.h"

#include "fcml_modrm_decoder.h"
#include "fcml_env.h"

fcml_st_modrm_decoder_context fcml_ifn_modrm_decoder_alloc_ctx() {
	fcml_st_modrm_decoder_context context;
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

	fcml_st_modrm_decoder_context context = fcml_ifn_modrm_decoder_alloc_ctx();

	context.addr_form = FCML_AF_32_BIT;
	context.effective_address_size = FCML_DS_16;

	fcml_uint8_t buffer[] = {23};

	fcml_st_memory_stream stream;
	stream.base_address = &buffer;
	stream.size = sizeof( buffer );
	stream.offset = 0;

	fcml_st_modrm_source modrm_source = {0};
	modrm_source.ext_b = 0;
	modrm_source.ext_r = 0;
	modrm_source.ext_x = 0;
	modrm_source.stream = &stream;
	fcml_st_modrm decoded_modrm;

	fcml_ceh_error error = fcml_fn_modrm_decode( &context, &modrm_source, &decoded_modrm );

	CU_ASSERT_EQUAL( error, FCML_CEH_GEC_NO_ERROR );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.type, FCML_REG_GPR );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.reg, FCML_REG_BX );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.size, FCML_DS_16 );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.type, FCML_REG_UNDEFINED );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.reg, 0 );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.size, 0 );
	CU_ASSERT_EQUAL( decoded_modrm.reg_opcode, FCML_REG_DX );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.displacement.size, 0 );
	CU_ASSERT_EQUAL( decoded_modrm.reg.is_not_null, FCML_FALSE );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.scale_factor, 0 );

}

void fcml_tf_modrm_decoder_test_2(void) {

	fcml_st_modrm_decoder_context context = fcml_ifn_modrm_decoder_alloc_ctx();

	context.addr_form = FCML_AF_32_BIT;
	context.effective_address_size = FCML_DS_16;

	fcml_uint8_t buffer[] = {0x1E, 0x01, 0x02};

	fcml_st_memory_stream stream;
	stream.base_address = &buffer;
	stream.size = sizeof( buffer );
	stream.offset = 0;

	fcml_st_modrm_source modrm_source = {0};
	modrm_source.ext_b = 0;
	modrm_source.ext_r = 0;
	modrm_source.ext_x = 0;
	modrm_source.stream = &stream;
	fcml_st_modrm decoded_modrm;

	fcml_ceh_error error = fcml_fn_modrm_decode( &context, &modrm_source, &decoded_modrm );

	CU_ASSERT_EQUAL( error, FCML_CEH_GEC_NO_ERROR );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.type, FCML_REG_UNDEFINED );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.reg, 0 );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.size, 0 );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.type, FCML_REG_UNDEFINED );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.reg, 0 );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.size, 0 );
	CU_ASSERT_EQUAL( decoded_modrm.reg_opcode, FCML_REG_BX );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.displacement.size, FCML_DS_16 );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.displacement.dis16, 0x0201 );
	CU_ASSERT_EQUAL( decoded_modrm.reg.is_not_null, FCML_FALSE );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.scale_factor, 0 );

}

void fcml_tf_modrm_decoder_test_3(void) {

	fcml_st_modrm_decoder_context context = fcml_ifn_modrm_decoder_alloc_ctx();

	context.addr_form = FCML_AF_32_BIT;
	context.effective_address_size = FCML_DS_16;

	fcml_uint8_t buffer[] = {0x0B};

	fcml_st_memory_stream stream;
	stream.base_address = &buffer;
	stream.size = sizeof( buffer );
	stream.offset = 0;

	fcml_st_modrm_source modrm_source = {0};
	modrm_source.ext_b = 0;
	modrm_source.ext_r = 0;
	modrm_source.ext_x = 0;
	modrm_source.stream = &stream;
	fcml_st_modrm decoded_modrm;

	fcml_ceh_error error = fcml_fn_modrm_decode( &context, &modrm_source, &decoded_modrm );

	CU_ASSERT_EQUAL( error, FCML_CEH_GEC_NO_ERROR );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.type, FCML_REG_GPR );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.reg, FCML_REG_BP );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.size, FCML_DS_16 );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.type, FCML_REG_GPR );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.reg, FCML_REG_DI );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.size, FCML_DS_16 );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.displacement.size, 0 );
	CU_ASSERT_EQUAL( decoded_modrm.reg_opcode, FCML_REG_CX );
	CU_ASSERT_EQUAL( decoded_modrm.reg.is_not_null, FCML_FALSE );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.scale_factor, 0 );

}

void fcml_tf_modrm_decoder_test_4(void) {

	fcml_st_modrm_decoder_context context = fcml_ifn_modrm_decoder_alloc_ctx();

	context.addr_form = FCML_AF_32_BIT;
	context.effective_address_size = FCML_DS_16;

	fcml_uint8_t buffer[] = {0x14};

	fcml_st_memory_stream stream;
	stream.base_address = &buffer;
	stream.size = sizeof( buffer );
	stream.offset = 0;

	fcml_st_modrm_source modrm_source = {0};
	modrm_source.ext_b = 0;
	modrm_source.ext_r = 0;
	modrm_source.ext_x = 0;
	modrm_source.stream = &stream;
	fcml_st_modrm decoded_modrm;

	fcml_ceh_error error = fcml_fn_modrm_decode( &context, &modrm_source, &decoded_modrm );

	CU_ASSERT_EQUAL( error, FCML_CEH_GEC_NO_ERROR );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.type, FCML_REG_GPR );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.reg, FCML_REG_SI );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.size, FCML_DS_16 );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.type, FCML_REG_UNDEFINED );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.reg, 0 );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.size, 0 );
	CU_ASSERT_EQUAL( decoded_modrm.reg_opcode, FCML_REG_DX );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.displacement.size, 0 );
	CU_ASSERT_EQUAL( decoded_modrm.reg.is_not_null, FCML_FALSE );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.scale_factor, 0 );

}

void fcml_tf_modrm_decoder_test_5(void) {

	fcml_st_modrm_decoder_context context = fcml_ifn_modrm_decoder_alloc_ctx();

	context.addr_form = FCML_AF_64_BIT;
	context.effective_address_size = FCML_DS_16;

	fcml_uint8_t buffer[] = {0x14};

	fcml_st_memory_stream stream;
	stream.base_address = &buffer;
	stream.size = sizeof( buffer );
	stream.offset = 0;

	fcml_st_modrm_source modrm_source = {0};
	modrm_source.ext_b = 0;
	modrm_source.ext_r = 0;
	modrm_source.ext_x = 0;
	modrm_source.stream = &stream;
	fcml_st_modrm decoded_modrm;

	fcml_ceh_error error = fcml_fn_modrm_decode( &context, &modrm_source, &decoded_modrm );

	CU_ASSERT_EQUAL( error, FCML_EN_UNSUPPORTED_ADDRESSING_MODE );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.type, FCML_REG_UNDEFINED );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.reg, 0 );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.size, 0 );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.type, FCML_REG_UNDEFINED );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.reg, 0 );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.size, 0 );
	CU_ASSERT_EQUAL( decoded_modrm.reg_opcode, 0 );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.displacement.size, 0 );
	CU_ASSERT_EQUAL( decoded_modrm.reg.is_not_null, FCML_FALSE );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.scale_factor, 0 );

}

void fcml_tf_modrm_decoder_test_6(void) {

	fcml_st_modrm_decoder_context context = fcml_ifn_modrm_decoder_alloc_ctx();

	context.addr_form = FCML_AF_32_BIT;
	context.effective_address_size = FCML_DS_16;

	fcml_uint8_t buffer[] = {0x73, 0x01};

	fcml_st_memory_stream stream;
	stream.base_address = &buffer;
	stream.size = sizeof( buffer );
	stream.offset = 0;

	fcml_st_modrm_source modrm_source = {0};
	modrm_source.ext_b = 0;
	modrm_source.ext_r = 0;
	modrm_source.ext_x = 0;
	modrm_source.stream = &stream;
	fcml_st_modrm decoded_modrm;

	fcml_ceh_error error = fcml_fn_modrm_decode( &context, &modrm_source, &decoded_modrm );

	CU_ASSERT_EQUAL( error, FCML_CEH_GEC_NO_ERROR );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.type, FCML_REG_GPR );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.reg, FCML_REG_BP );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.size, FCML_DS_16 );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.type, FCML_REG_GPR );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.reg, FCML_REG_DI );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.size, FCML_DS_16 );
	CU_ASSERT_EQUAL( decoded_modrm.reg_opcode, FCML_REG_SI );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.displacement.size, FCML_DS_8 );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.displacement.dis8, 0x01 );
	CU_ASSERT_EQUAL( decoded_modrm.reg.is_not_null, FCML_FALSE );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.scale_factor, 0 );

}

void fcml_tf_modrm_decoder_test_7(void) {

	fcml_st_modrm_decoder_context context = fcml_ifn_modrm_decoder_alloc_ctx();

	context.addr_form = FCML_AF_32_BIT;
	context.effective_address_size = FCML_DS_16;

	fcml_uint8_t buffer[] = {0x73};

	fcml_st_memory_stream stream;
	stream.base_address = &buffer;
	stream.size = sizeof( buffer );
	stream.offset = 0;

	fcml_st_modrm_source modrm_source = {0};
	modrm_source.ext_b = 0;
	modrm_source.ext_r = 0;
	modrm_source.ext_x = 0;
	modrm_source.stream = &stream;
	fcml_st_modrm decoded_modrm;

	fcml_ceh_error error = fcml_fn_modrm_decode( &context, &modrm_source, &decoded_modrm );

	CU_ASSERT_EQUAL( error, FCML_CEH_GEC_EOF );

}

// [EBX], EBX
void fcml_tf_modrm_3264_decoder_test_1(void) {

	fcml_st_modrm_decoder_context context = fcml_ifn_modrm_decoder_alloc_ctx();

	context.addr_form = FCML_AF_32_BIT;
	context.effective_address_size = FCML_DS_32;

	fcml_uint8_t buffer[] = {0x1B};

	fcml_st_memory_stream stream;
	stream.base_address = &buffer;
	stream.size = sizeof( buffer );
	stream.offset = 0;

	fcml_st_modrm_source modrm_source = {0};
	modrm_source.ext_b = 0;
	modrm_source.ext_r = 0;
	modrm_source.ext_x = 0;
	modrm_source.stream = &stream;
	fcml_st_modrm decoded_modrm;

	fcml_ceh_error error = fcml_fn_modrm_decode( &context, &modrm_source, &decoded_modrm );

	CU_ASSERT_EQUAL( error, FCML_CEH_GEC_NO_ERROR );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.type, FCML_REG_GPR );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.reg, FCML_REG_EBX );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.size, FCML_DS_32 );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.type, FCML_REG_UNDEFINED );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.reg, 0 );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.size, 0 );
	CU_ASSERT_EQUAL( decoded_modrm.reg_opcode, FCML_REG_EBX );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.displacement.size, 0 );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.displacement.dis8, 0 );
	CU_ASSERT_EQUAL( decoded_modrm.reg.is_not_null, FCML_FALSE );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.scale_factor, 0 );

}

// [04030201], EDX
void fcml_tf_modrm_3264_decoder_test_2(void) {

	fcml_st_modrm_decoder_context context = fcml_ifn_modrm_decoder_alloc_ctx();

	context.addr_form = FCML_AF_32_BIT;
	context.effective_address_size = FCML_DS_32;

	fcml_uint8_t buffer[] = {0x15, 0x01, 0x02, 0x03, 0x04};

	fcml_st_memory_stream stream;
	stream.base_address = &buffer;
	stream.size = sizeof( buffer );
	stream.offset = 0;

	fcml_st_modrm_source modrm_source = {0};
	modrm_source.ext_b = 0;
	modrm_source.ext_r = 0;
	modrm_source.ext_x = 0;
	modrm_source.stream = &stream;
	fcml_st_modrm decoded_modrm;

	fcml_ceh_error error = fcml_fn_modrm_decode( &context, &modrm_source, &decoded_modrm );

	CU_ASSERT_EQUAL( error, FCML_CEH_GEC_NO_ERROR );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.type, FCML_REG_UNDEFINED );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.reg, 0 );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.size, 0 );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.type, FCML_REG_UNDEFINED );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.reg, 0 );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.size, 0 );
	CU_ASSERT_EQUAL( decoded_modrm.reg_opcode, FCML_REG_EDX );
	CU_ASSERT_EQUAL( decoded_modrm.address.offset.size, FCML_DS_32 );
	CU_ASSERT_EQUAL( decoded_modrm.address.offset.off32, 0x04030201 );
	CU_ASSERT_EQUAL( decoded_modrm.address.offset.is_signed, FCML_TRUE );
	CU_ASSERT_EQUAL( decoded_modrm.reg.is_not_null, FCML_FALSE );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.scale_factor, 0 );
}

// RIP-addressing.
// RIP: 401000h
// disp32: 0f1efbf00h
// [FFFFFFFFFF887766], EDX
void fcml_tf_modrm_3264_decoder_test_3(void) {

	fcml_st_modrm_decoder_context context = fcml_ifn_modrm_decoder_alloc_ctx();

	context.addr_form = FCML_AF_64_BIT;
	context.effective_address_size = FCML_DS_64;

	fcml_uint8_t buffer[] = {0x15, 0xfa, 0xf1, 0xbf, 0xff};

	fcml_st_memory_stream stream;
	stream.base_address = &buffer;
	stream.size = sizeof( buffer );
	stream.offset = 0;

	fcml_st_modrm_source modrm_source = {0};
	modrm_source.ext_b = 0;
	modrm_source.ext_r = 0;
	modrm_source.ext_x = 0;
	modrm_source.stream = &stream;
	fcml_st_modrm decoded_modrm;

	fcml_ceh_error error = fcml_fn_modrm_decode( &context, &modrm_source, &decoded_modrm );

	CU_ASSERT_EQUAL( error, FCML_CEH_GEC_NO_ERROR );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.type, FCML_REG_UNDEFINED );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.reg, 0 );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.size, 0 );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.type, FCML_REG_UNDEFINED );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.reg, 0 );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.size, 0 );
	CU_ASSERT_EQUAL( decoded_modrm.reg_opcode, FCML_REG_EDX );
	CU_ASSERT_EQUAL( decoded_modrm.address.offset.size, FCML_DS_32 );
	CU_ASSERT_EQUAL( decoded_modrm.address.offset.off32, 0xFFBFF1FA );
	CU_ASSERT_EQUAL( decoded_modrm.address.offset.is_signed, FCML_TRUE );
	CU_ASSERT_EQUAL( decoded_modrm.reg.is_not_null, FCML_FALSE );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.scale_factor, 0 );
	CU_ASSERT_EQUAL( context.is_rip, FCML_TRUE );

	fcml_st_offset address = {0};
	error = fcml_fn_modrm_decode_rip( 0x401000, FCML_DS_64, &(decoded_modrm.address.offset), &address );

	CU_ASSERT_EQUAL( address.size, FCML_DS_64 );
	CU_ASSERT_EQUAL( address.off64, 0x1faUL );

}

// [ECX]+0x66, EAX
void fcml_tf_modrm_3264_decoder_test_4(void) {

	fcml_st_modrm_decoder_context context = fcml_ifn_modrm_decoder_alloc_ctx();

	context.addr_form = FCML_AF_64_BIT;
	context.effective_address_size = FCML_DS_32;

	fcml_uint8_t buffer[] = {0x41, 0x66};

	fcml_st_memory_stream stream;
	stream.base_address = &buffer;
	stream.size = sizeof( buffer );
	stream.offset = 0;

	fcml_st_modrm_source modrm_source = {0};
	modrm_source.ext_b = 0;
	modrm_source.ext_r = 0;
	modrm_source.ext_x = 0;
	modrm_source.stream = &stream;
	fcml_st_modrm decoded_modrm;

	fcml_ceh_error error = fcml_fn_modrm_decode( &context, &modrm_source, &decoded_modrm );

	CU_ASSERT_EQUAL( error, FCML_CEH_GEC_NO_ERROR );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.type, FCML_REG_GPR );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.reg, FCML_REG_ECX );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.size, FCML_DS_32 );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.type, FCML_REG_UNDEFINED );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.reg, 0 );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.size, 0 );
	CU_ASSERT_EQUAL( decoded_modrm.reg_opcode, FCML_REG_EAX );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.displacement.size, FCML_DS_8 );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.displacement.dis8, 0x66 );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.displacement.is_signed, FCML_TRUE );
	CU_ASSERT_EQUAL( decoded_modrm.reg.is_not_null, FCML_FALSE );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.scale_factor, 0 );
}


// [ECX]+0x01020304, EAX
void fcml_tf_modrm_3264_decoder_test_5(void) {

	fcml_st_modrm_decoder_context context = fcml_ifn_modrm_decoder_alloc_ctx();

	context.addr_form = FCML_AF_64_BIT;
	context.effective_address_size = FCML_DS_32;

	fcml_uint8_t buffer[] = {0x81, 0x04, 0x03, 0x02, 0x01};

	fcml_st_memory_stream stream;
	stream.base_address = &buffer;
	stream.size = sizeof( buffer );
	stream.offset = 0;

	fcml_st_modrm_source modrm_source = {0};
	modrm_source.ext_b = 0;
	modrm_source.ext_r = 0;
	modrm_source.ext_x = 0;
	modrm_source.stream = &stream;
	fcml_st_modrm decoded_modrm;

	fcml_ceh_error error = fcml_fn_modrm_decode( &context, &modrm_source, &decoded_modrm );

	CU_ASSERT_EQUAL( error, FCML_CEH_GEC_NO_ERROR );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.type, FCML_REG_GPR );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.reg, FCML_REG_ECX );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.size, FCML_DS_32 );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.type, FCML_REG_UNDEFINED );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.reg, 0 );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.size, 0 );
	CU_ASSERT_EQUAL( decoded_modrm.reg_opcode, FCML_REG_EAX );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.displacement.size, FCML_DS_32 );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.displacement.dis32, 0x01020304 );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.displacement.is_signed, FCML_TRUE );
	CU_ASSERT_EQUAL( decoded_modrm.reg.is_not_null, FCML_FALSE );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.scale_factor, 0 );
}

// [R9]+0x01020304, R8
void fcml_tf_modrm_3264_decoder_test_6(void) {

	fcml_st_modrm_decoder_context context = fcml_ifn_modrm_decoder_alloc_ctx();

	context.addr_form = FCML_AF_64_BIT;
	context.effective_address_size = FCML_DS_64;

	fcml_uint8_t buffer[] = {0x81, 0x04, 0x03, 0x02, 0x01};

	fcml_st_memory_stream stream;
	stream.base_address = &buffer;
	stream.size = sizeof( buffer );
	stream.offset = 0;

	fcml_st_modrm_source modrm_source = {0};
	modrm_source.ext_b = 1;
	modrm_source.ext_r = 1;
	modrm_source.ext_x = 0;
	modrm_source.stream = &stream;
	fcml_st_modrm decoded_modrm;

	fcml_ceh_error error = fcml_fn_modrm_decode( &context, &modrm_source, &decoded_modrm );

	CU_ASSERT_EQUAL( error, FCML_CEH_GEC_NO_ERROR );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.type, FCML_REG_GPR );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.reg, FCML_REG_R9 );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.size, FCML_DS_64 );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.type, FCML_REG_UNDEFINED );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.reg, 0 );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.size, 0 );
	CU_ASSERT_EQUAL( decoded_modrm.reg_opcode, FCML_REG_R8 );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.displacement.size, FCML_DS_32 );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.displacement.dis32, 0x01020304 );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.displacement.is_signed, FCML_TRUE );
	CU_ASSERT_EQUAL( decoded_modrm.reg.is_not_null, FCML_FALSE );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.scale_factor, 0 );
}

// Illegal EASA size.
void fcml_tf_modrm_3264_decoder_test_7(void) {

	fcml_st_modrm_decoder_context context = fcml_ifn_modrm_decoder_alloc_ctx();

	context.addr_form = FCML_AF_64_BIT;
	context.effective_address_size = FCML_DS_16;

	fcml_uint8_t buffer[] = {0x81, 0x04, 0x03, 0x02, 0x01};

	fcml_st_memory_stream stream;
	stream.base_address = &buffer;
	stream.size = sizeof( buffer );
	stream.offset = 0;

	fcml_st_modrm_source modrm_source = {0};
	modrm_source.ext_b = 1;
	modrm_source.ext_r = 1;
	modrm_source.ext_x = 0;
	modrm_source.stream = &stream;
	fcml_st_modrm decoded_modrm;

	fcml_ceh_error error = fcml_fn_modrm_decode( &context, &modrm_source, &decoded_modrm );

	CU_ASSERT_EQUAL( error, FCML_EN_UNSUPPORTED_ADDRESSING_MODE );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.type, FCML_REG_UNDEFINED );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.reg, 0 );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.size, 0 );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.type, FCML_REG_UNDEFINED );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.reg, 0 );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.size, 0 );
	CU_ASSERT_EQUAL( decoded_modrm.reg_opcode, 0 );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.displacement.size, 0 );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.displacement.dis32, 0 );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.displacement.is_signed, FCML_FALSE );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.displacement.size, 0 );
    CU_ASSERT_EQUAL( decoded_modrm.address.offset.off32, 0 );
    CU_ASSERT_EQUAL( decoded_modrm.address.offset.is_signed, FCML_FALSE );
	CU_ASSERT_EQUAL( decoded_modrm.reg.is_not_null, FCML_FALSE );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.scale_factor, 0 );
}

// RAX, EBX
void fcml_tf_modrm_3264_decoder_test_8(void) {

	fcml_st_modrm_decoder_context context = fcml_ifn_modrm_decoder_alloc_ctx();

	context.addr_form = FCML_AF_64_BIT;
	context.effective_address_size = FCML_DS_64;

	fcml_uint8_t buffer[] = {0xD8};

	fcml_st_memory_stream stream;
	stream.base_address = &buffer;
	stream.size = sizeof( buffer );
	stream.offset = 0;

	fcml_st_modrm_source modrm_source = {0};
	modrm_source.ext_b = 0;
	modrm_source.ext_r = 0;
	modrm_source.ext_x = 0;
	modrm_source.stream = &stream;
	fcml_st_modrm decoded_modrm;

	fcml_ceh_error error = fcml_fn_modrm_decode( &context, &modrm_source, &decoded_modrm );

	CU_ASSERT_EQUAL( error, FCML_CEH_GEC_NO_ERROR );
	CU_ASSERT_EQUAL( decoded_modrm.reg.value, FCML_REG_RAX );
	CU_ASSERT_EQUAL( decoded_modrm.reg.is_not_null, FCML_TRUE );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.type, FCML_REG_UNDEFINED );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.reg, 0 );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.size, 0 );
	CU_ASSERT_EQUAL( decoded_modrm.reg_opcode, FCML_REG_RBX );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.displacement.size, 0 );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.displacement.dis32, 0 );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.displacement.is_signed, FCML_FALSE );
	CU_ASSERT_EQUAL( decoded_modrm.address.offset.size, 0 );
    CU_ASSERT_EQUAL( decoded_modrm.address.offset.off32, 0 );
    CU_ASSERT_EQUAL( decoded_modrm.address.offset.is_signed, FCML_FALSE );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.scale_factor, 0 );
}

// R8, R11
void fcml_tf_modrm_3264_decoder_test_9(void) {

	fcml_st_modrm_decoder_context context = fcml_ifn_modrm_decoder_alloc_ctx();

	context.addr_form = FCML_AF_64_BIT;
	context.effective_address_size = FCML_DS_64;

	fcml_uint8_t buffer[] = {0xD8};

	fcml_st_memory_stream stream;
	stream.base_address = &buffer;
	stream.size = sizeof( buffer );
	stream.offset = 0;

	fcml_st_modrm_source modrm_source = {0};
	modrm_source.ext_b = 1;
	modrm_source.ext_r = 1;
	modrm_source.ext_x = 0;
	modrm_source.stream = &stream;
	fcml_st_modrm decoded_modrm;

	fcml_ceh_error error = fcml_fn_modrm_decode( &context, &modrm_source, &decoded_modrm );

	CU_ASSERT_EQUAL( error, FCML_CEH_GEC_NO_ERROR );
	CU_ASSERT_EQUAL( decoded_modrm.reg.value, FCML_REG_R8 );
	CU_ASSERT_EQUAL( decoded_modrm.reg.is_not_null, FCML_TRUE );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.type, FCML_REG_UNDEFINED );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.reg, 0 );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.size, 0 );
	CU_ASSERT_EQUAL( decoded_modrm.reg_opcode, FCML_REG_R11 );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.displacement.size, 0 );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.displacement.dis32, 0 );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.displacement.is_signed, FCML_FALSE );
	CU_ASSERT_EQUAL( decoded_modrm.address.offset.size, 0 );
    CU_ASSERT_EQUAL( decoded_modrm.address.offset.off64, 0 );
    CU_ASSERT_EQUAL( decoded_modrm.address.offset.is_signed, FCML_FALSE );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.scale_factor, 0 );
}


// RIP-addressing.
void fcml_tf_modrm_3264_decoder_test_10(void) {

	fcml_st_modrm_decoder_context context = fcml_ifn_modrm_decoder_alloc_ctx();

	context.addr_form = FCML_AF_64_BIT;
	context.effective_address_size = FCML_DS_64;

	fcml_uint8_t buffer[] = {0x15, 0xff, 0xff, 0xff, 0xff};

	fcml_st_memory_stream stream;
	stream.base_address = &buffer;
	stream.size = sizeof( buffer );
	stream.offset = 0;

	fcml_st_modrm_source modrm_source = {0};
	modrm_source.ext_b = 0;
	modrm_source.ext_r = 0;
	modrm_source.ext_x = 0;
	modrm_source.stream = &stream;
	fcml_st_modrm decoded_modrm;

	fcml_ceh_error error = fcml_fn_modrm_decode( &context, &modrm_source, &decoded_modrm );

	CU_ASSERT_EQUAL( error, FCML_CEH_GEC_NO_ERROR );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.type, FCML_REG_UNDEFINED );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.reg, 0 );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.size, 0 );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.type, FCML_REG_UNDEFINED );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.reg, 0 );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.size, 0 );
	CU_ASSERT_EQUAL( decoded_modrm.reg_opcode, FCML_REG_EDX );
	CU_ASSERT_EQUAL( decoded_modrm.address.offset.size, FCML_DS_32 );
	CU_ASSERT_EQUAL( decoded_modrm.address.offset.off32, 0xFFFFFFFF );
	CU_ASSERT_EQUAL( decoded_modrm.address.offset.is_signed, FCML_TRUE );
	CU_ASSERT_EQUAL( decoded_modrm.reg.is_not_null, FCML_FALSE );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.scale_factor, 0 );
	CU_ASSERT_EQUAL( context.is_rip, FCML_TRUE );

	fcml_st_offset address = {0};
	error = fcml_fn_modrm_decode_rip( 0x401000, FCML_DS_64, &(decoded_modrm.address.offset), &address );

	CU_ASSERT_EQUAL( address.size, FCML_DS_64 );
	CU_ASSERT_EQUAL( address.off64, 0x400fffUL );

}

// RIP-addressing.
void fcml_tf_modrm_3264_decoder_test_11(void) {

	fcml_st_modrm_decoder_context context = fcml_ifn_modrm_decoder_alloc_ctx();

	context.addr_form = FCML_AF_64_BIT;
	context.effective_address_size = FCML_DS_64;

	fcml_uint8_t buffer[] = {0x15, 0x00, 0xE0, 0x7F, 0xFF};

	fcml_st_memory_stream stream;
	stream.base_address = &buffer;
	stream.size = sizeof( buffer );
	stream.offset = 0;

	fcml_st_modrm_source modrm_source = {0};
	modrm_source.ext_b = 0;
	modrm_source.ext_r = 0;
	modrm_source.ext_x = 0;
	modrm_source.stream = &stream;
	fcml_st_modrm decoded_modrm;

	fcml_ceh_error error = fcml_fn_modrm_decode( &context, &modrm_source, &decoded_modrm );

	CU_ASSERT_EQUAL( error, FCML_CEH_GEC_NO_ERROR );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.type, FCML_REG_UNDEFINED );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.reg, 0 );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.size, 0 );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.type, FCML_REG_UNDEFINED );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.reg, 0 );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.size, 0 );
	CU_ASSERT_EQUAL( decoded_modrm.reg_opcode, FCML_REG_EDX );
	CU_ASSERT_EQUAL( decoded_modrm.address.offset.size, FCML_DS_32 );
	CU_ASSERT_EQUAL( decoded_modrm.address.offset.off32, 0xFF7FE000 );
	CU_ASSERT_EQUAL( decoded_modrm.address.offset.is_signed, FCML_TRUE );
	CU_ASSERT_EQUAL( decoded_modrm.reg.is_not_null, FCML_FALSE );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.scale_factor, 0 );
	CU_ASSERT_EQUAL( context.is_rip, FCML_TRUE );

	fcml_st_offset address = {0};
	error = fcml_fn_modrm_decode_rip( 0x401000, FCML_DS_64, &(decoded_modrm.address.offset), &address );

	CU_ASSERT_EQUAL( address.size, FCML_DS_64 );
	CU_ASSERT_EQUAL( address.off64, 0xffffffffffbff000UL );

}

// RIP-addressing.
void fcml_tf_modrm_3264_decoder_test_12(void) {

	fcml_st_modrm_decoder_context context = fcml_ifn_modrm_decoder_alloc_ctx();

	context.addr_form = FCML_AF_64_BIT;
	context.effective_address_size = FCML_DS_32;

	fcml_uint8_t buffer[] = {0x15, 0x00, 0xE0, 0x7F, 0xFF};

	fcml_st_memory_stream stream;
	stream.base_address = &buffer;
	stream.size = sizeof( buffer );
	stream.offset = 0;

	fcml_st_modrm_source modrm_source = {0};
	modrm_source.ext_b = 0;
	modrm_source.ext_r = 0;
	modrm_source.ext_x = 0;
	modrm_source.stream = &stream;
	fcml_st_modrm decoded_modrm;

	fcml_ceh_error error = fcml_fn_modrm_decode( &context, &modrm_source, &decoded_modrm );

	CU_ASSERT_EQUAL( error, FCML_CEH_GEC_NO_ERROR );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.type, FCML_REG_UNDEFINED );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.reg, 0 );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.size, 0 );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.type, FCML_REG_UNDEFINED );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.reg, 0 );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.size, 0 );
	CU_ASSERT_EQUAL( decoded_modrm.reg_opcode, FCML_REG_EDX );
	CU_ASSERT_EQUAL( decoded_modrm.address.offset.size, FCML_DS_32 );
	CU_ASSERT_EQUAL( decoded_modrm.address.offset.off32, 0xFF7FE000 );
	CU_ASSERT_EQUAL( decoded_modrm.address.offset.is_signed, FCML_TRUE );
	CU_ASSERT_EQUAL( decoded_modrm.reg.is_not_null, FCML_FALSE );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.scale_factor, 0 );
	CU_ASSERT_EQUAL( context.is_rip, FCML_TRUE );

	fcml_st_offset address = {0};
	error = fcml_fn_modrm_decode_rip( 0x401000, FCML_DS_32, &(decoded_modrm.address.offset), &address );

	CU_ASSERT_EQUAL( address.size, FCML_DS_64 );
	CU_ASSERT_EQUAL( address.off64, 0x00000000ffbff000UL );

}

// [01020304], R8
void fcml_tf_modrm_3264_decoder_sib_test_1(void) {

	fcml_st_modrm_decoder_context context = fcml_ifn_modrm_decoder_alloc_ctx();

	context.addr_form = FCML_AF_64_BIT;
	context.effective_address_size = FCML_DS_64;

	fcml_uint8_t buffer[] = { 0x04, 0x25, 0x04, 0x03, 0x02, 0x01 };

	fcml_st_memory_stream stream;
	stream.base_address = &buffer;
	stream.size = sizeof( buffer );
	stream.offset = 0;

	fcml_st_modrm_source modrm_source = {0};
	modrm_source.ext_b = 1;
	modrm_source.ext_r = 1;
	modrm_source.ext_x = 0;
	modrm_source.stream = &stream;
	fcml_st_modrm decoded_modrm;

	fcml_ceh_error error = fcml_fn_modrm_decode( &context, &modrm_source, &decoded_modrm );

	CU_ASSERT_EQUAL( error, FCML_CEH_GEC_NO_ERROR );
	CU_ASSERT_EQUAL( decoded_modrm.reg.value, FCML_REG_UNDEFINED );
	CU_ASSERT_EQUAL( decoded_modrm.reg.is_not_null, FCML_FALSE );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.type, FCML_REG_UNDEFINED );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.reg, 0 );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.size, 0 );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.type, FCML_REG_UNDEFINED );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.reg, 0 );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.size, 0 );
	CU_ASSERT_EQUAL( decoded_modrm.reg_opcode, FCML_REG_R8 );
	CU_ASSERT_EQUAL( decoded_modrm.address.offset.size, FCML_DS_64 );
	CU_ASSERT_EQUAL( decoded_modrm.address.offset.off64, 0x01020304 );
	CU_ASSERT_EQUAL( decoded_modrm.address.offset.is_signed, FCML_TRUE );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.scale_factor, 0 );
}

// [EBX]+0x01020304, R8
void fcml_tf_modrm_3264_decoder_sib_test_2(void) {

	fcml_st_modrm_decoder_context context = fcml_ifn_modrm_decoder_alloc_ctx();

	context.addr_form = FCML_AF_64_BIT;
	context.effective_address_size = FCML_DS_64;

	fcml_uint8_t buffer[] = { 0x04, 0x1D, 0x04, 0x03, 0x02, 0x01 };

	fcml_st_memory_stream stream;
	stream.base_address = &buffer;
	stream.size = sizeof( buffer );
	stream.offset = 0;

	fcml_st_modrm_source modrm_source = {0};
	modrm_source.ext_b = 0;
	modrm_source.ext_r = 1;
	modrm_source.ext_x = 1;
	modrm_source.stream = &stream;
	fcml_st_modrm decoded_modrm;

	fcml_ceh_error error = fcml_fn_modrm_decode( &context, &modrm_source, &decoded_modrm );

	CU_ASSERT_EQUAL( error, FCML_CEH_GEC_NO_ERROR );
	CU_ASSERT_EQUAL( decoded_modrm.reg.value, FCML_REG_UNDEFINED );
	CU_ASSERT_EQUAL( decoded_modrm.reg.is_not_null, FCML_FALSE );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.type, FCML_REG_UNDEFINED );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.reg, 0 );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.size, 0 );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.type, FCML_REG_GPR );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.reg, FCML_REG_R11 );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.size, FCML_DS_64 );
	CU_ASSERT_EQUAL( decoded_modrm.reg_opcode, FCML_REG_R8 );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.displacement.size, 32 );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.displacement.dis32, 0x01020304 );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.displacement.is_signed, FCML_TRUE );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.scale_factor, 0 );
}

// [ECX+EBX]+0x01, R8
void fcml_tf_modrm_3264_decoder_sib_test_3(void) {

	fcml_st_modrm_decoder_context context = fcml_ifn_modrm_decoder_alloc_ctx();

	context.addr_form = FCML_AF_64_BIT;
	context.effective_address_size = FCML_DS_64;

	fcml_uint8_t buffer[] = { 0x04, 0x19 };

	fcml_st_memory_stream stream;
	stream.base_address = &buffer;
	stream.size = sizeof( buffer );
	stream.offset = 0;

	fcml_st_modrm_source modrm_source = {0};
	modrm_source.ext_b = 1;
	modrm_source.ext_r = 1;
	modrm_source.ext_x = 1;
	modrm_source.stream = &stream;
	fcml_st_modrm decoded_modrm;

	fcml_ceh_error error = fcml_fn_modrm_decode( &context, &modrm_source, &decoded_modrm );

	CU_ASSERT_EQUAL( error, FCML_CEH_GEC_NO_ERROR );
	CU_ASSERT_EQUAL( decoded_modrm.reg.value, FCML_REG_UNDEFINED );
	CU_ASSERT_EQUAL( decoded_modrm.reg.is_not_null, FCML_FALSE );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.type, FCML_REG_GPR );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.reg, FCML_REG_R9 );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.size, FCML_DS_64 );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.type, FCML_REG_GPR );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.reg, FCML_REG_R11 );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.size, FCML_DS_64 );
	CU_ASSERT_EQUAL( decoded_modrm.reg_opcode, FCML_REG_R8 );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.displacement.size, 0 );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.displacement.dis32, 0 );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.displacement.is_signed, FCML_FALSE );
	CU_ASSERT_EQUAL( decoded_modrm.address.offset.size, 0 );
    CU_ASSERT_EQUAL( decoded_modrm.address.offset.off32, 0 );
    CU_ASSERT_EQUAL( decoded_modrm.address.offset.is_signed, FCML_FALSE );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.scale_factor, 0 );
}

// [ECX+EBX*2]+0x01, R8
void fcml_tf_modrm_3264_decoder_sib_test_4(void) {

	fcml_st_modrm_decoder_context context = fcml_ifn_modrm_decoder_alloc_ctx();

	context.addr_form = FCML_AF_64_BIT;
	context.effective_address_size = FCML_DS_64;

	fcml_uint8_t buffer[] = { 0x04, 0x59 };

	fcml_st_memory_stream stream;
	stream.base_address = &buffer;
	stream.size = sizeof( buffer );
	stream.offset = 0;

	fcml_st_modrm_source modrm_source = {0};
	modrm_source.ext_b = 1;
	modrm_source.ext_r = 1;
	modrm_source.ext_x = 1;
	modrm_source.stream = &stream;
	fcml_st_modrm decoded_modrm;

	fcml_ceh_error error = fcml_fn_modrm_decode( &context, &modrm_source, &decoded_modrm );

	CU_ASSERT_EQUAL( error, FCML_CEH_GEC_NO_ERROR );
	CU_ASSERT_EQUAL( decoded_modrm.reg.value, FCML_REG_UNDEFINED );
	CU_ASSERT_EQUAL( decoded_modrm.reg.is_not_null, FCML_FALSE );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.type, FCML_REG_GPR );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.reg, FCML_REG_R9 );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.size, FCML_DS_64 );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.type, FCML_REG_GPR );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.reg, FCML_REG_R11 );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.size, FCML_DS_64 );
	CU_ASSERT_EQUAL( decoded_modrm.reg_opcode, FCML_REG_R8 );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.displacement.size, 0 );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.displacement.dis32, 0 );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.displacement.is_signed, FCML_FALSE );
	CU_ASSERT_EQUAL( decoded_modrm.address.offset.size, 0 );
    CU_ASSERT_EQUAL( decoded_modrm.address.offset.off32, 0 );
    CU_ASSERT_EQUAL( decoded_modrm.address.offset.is_signed, FCML_FALSE );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.scale_factor, 2 );
}

// [ECX+EBX*4], R8
void fcml_tf_modrm_3264_decoder_sib_test_5(void) {

	fcml_st_modrm_decoder_context context = fcml_ifn_modrm_decoder_alloc_ctx();

	context.addr_form = FCML_AF_64_BIT;
	context.effective_address_size = FCML_DS_64;

	fcml_uint8_t buffer[] = { 0x04, 0x99 };

	fcml_st_memory_stream stream;
	stream.base_address = &buffer;
	stream.size = sizeof( buffer );
	stream.offset = 0;

	fcml_st_modrm_source modrm_source = {0};
	modrm_source.ext_b = 1;
	modrm_source.ext_r = 1;
	modrm_source.ext_x = 1;
	modrm_source.stream = &stream;
	fcml_st_modrm decoded_modrm;

	fcml_ceh_error error = fcml_fn_modrm_decode( &context, &modrm_source, &decoded_modrm );

	CU_ASSERT_EQUAL( error, FCML_CEH_GEC_NO_ERROR );
	CU_ASSERT_EQUAL( decoded_modrm.reg.value, FCML_REG_UNDEFINED );
	CU_ASSERT_EQUAL( decoded_modrm.reg.is_not_null, FCML_FALSE );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.type, FCML_REG_GPR );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.reg, FCML_REG_R9 );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.size, FCML_DS_64 );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.type, FCML_REG_GPR );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.reg, FCML_REG_R11 );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.size, FCML_DS_64 );
	CU_ASSERT_EQUAL( decoded_modrm.reg_opcode, FCML_REG_R8 );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.displacement.size, 0 );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.displacement.dis32, 0 );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.displacement.is_signed, FCML_FALSE );
	CU_ASSERT_EQUAL( decoded_modrm.address.offset.size, 0 );
    CU_ASSERT_EQUAL( decoded_modrm.address.offset.off32, 0 );
    CU_ASSERT_EQUAL( decoded_modrm.address.offset.is_signed, FCML_FALSE );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.scale_factor, 4 );
}

// [ECX+EBX*8], R8
void fcml_tf_modrm_3264_decoder_sib_test_6(void) {

	fcml_st_modrm_decoder_context context = fcml_ifn_modrm_decoder_alloc_ctx();

	context.addr_form = FCML_AF_64_BIT;
	context.effective_address_size = FCML_DS_64;

	fcml_uint8_t buffer[] = { 0x04, 0xD9 };

	fcml_st_memory_stream stream;
	stream.base_address = &buffer;
	stream.size = sizeof( buffer );
	stream.offset = 0;

	fcml_st_modrm_source modrm_source = {0};
	modrm_source.ext_b = 1;
	modrm_source.ext_r = 1;
	modrm_source.ext_x = 1;
	modrm_source.stream = &stream;
	fcml_st_modrm decoded_modrm;

	fcml_ceh_error error = fcml_fn_modrm_decode( &context, &modrm_source, &decoded_modrm );

	CU_ASSERT_EQUAL( error, FCML_CEH_GEC_NO_ERROR );
	CU_ASSERT_EQUAL( decoded_modrm.reg.value, FCML_REG_UNDEFINED );
	CU_ASSERT_EQUAL( decoded_modrm.reg.is_not_null, FCML_FALSE );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.type, FCML_REG_GPR );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.reg, FCML_REG_R9 );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.size, FCML_DS_64 );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.type, FCML_REG_GPR );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.reg, FCML_REG_R11 );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.size, FCML_DS_64 );
	CU_ASSERT_EQUAL( decoded_modrm.reg_opcode, FCML_REG_R8 );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.displacement.size, 0 );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.displacement.dis32, 0 );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.displacement.is_signed, FCML_FALSE );
	CU_ASSERT_EQUAL( decoded_modrm.address.offset.size, 0 );
    CU_ASSERT_EQUAL( decoded_modrm.address.offset.off32, 0 );
    CU_ASSERT_EQUAL( decoded_modrm.address.offset.is_signed, FCML_FALSE );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.scale_factor, 8 );
}

// [ECX+EBX*8]+0x55, R8
void fcml_tf_modrm_3264_decoder_sib_test_7(void) {

	fcml_st_modrm_decoder_context context = fcml_ifn_modrm_decoder_alloc_ctx();

	context.addr_form = FCML_AF_64_BIT;
	context.effective_address_size = FCML_DS_64;

	fcml_uint8_t buffer[] = { 0x44, 0xD9, 0x55 };

	fcml_st_memory_stream stream;
	stream.base_address = &buffer;
	stream.size = sizeof( buffer );
	stream.offset = 0;

	fcml_st_modrm_source modrm_source = {0};
	modrm_source.ext_b = 1;
	modrm_source.ext_r = 1;
	modrm_source.ext_x = 1;
	modrm_source.stream = &stream;
	fcml_st_modrm decoded_modrm;

	fcml_ceh_error error = fcml_fn_modrm_decode( &context, &modrm_source, &decoded_modrm );

	CU_ASSERT_EQUAL( error, FCML_CEH_GEC_NO_ERROR );
	CU_ASSERT_EQUAL( decoded_modrm.reg.value, FCML_REG_UNDEFINED );
	CU_ASSERT_EQUAL( decoded_modrm.reg.is_not_null, FCML_FALSE );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.type, FCML_REG_GPR );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.reg, FCML_REG_R9 );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.size, FCML_DS_64 );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.type, FCML_REG_GPR );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.reg, FCML_REG_R11 );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.size, FCML_DS_64 );
	CU_ASSERT_EQUAL( decoded_modrm.reg_opcode, FCML_REG_R8 );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.displacement.size, FCML_DS_8 );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.displacement.dis8, 0x55 );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.displacement.is_signed, FCML_TRUE );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.scale_factor, 8 );
}

// [ECX+EBX*8]+0x01020304, R8
void fcml_tf_modrm_3264_decoder_sib_test_8(void) {

	fcml_st_modrm_decoder_context context = fcml_ifn_modrm_decoder_alloc_ctx();

	context.addr_form = FCML_AF_64_BIT;
	context.effective_address_size = FCML_DS_64;

	fcml_uint8_t buffer[] = { 0x84, 0xD9, 0x04, 0x03, 0x02, 0x01 };

	fcml_st_memory_stream stream;
	stream.base_address = &buffer;
	stream.size = sizeof( buffer );
	stream.offset = 0;

	fcml_st_modrm_source modrm_source = {0};
	modrm_source.ext_b = 1;
	modrm_source.ext_r = 1;
	modrm_source.ext_x = 1;
	modrm_source.stream = &stream;
	fcml_st_modrm decoded_modrm;

	fcml_ceh_error error = fcml_fn_modrm_decode( &context, &modrm_source, &decoded_modrm );

	CU_ASSERT_EQUAL( error, FCML_CEH_GEC_NO_ERROR );
	CU_ASSERT_EQUAL( decoded_modrm.reg.value, FCML_REG_UNDEFINED );
	CU_ASSERT_EQUAL( decoded_modrm.reg.is_not_null, FCML_FALSE );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.type, FCML_REG_GPR );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.reg, FCML_REG_R9 );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.size, FCML_DS_64 );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.type, FCML_REG_GPR );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.reg, FCML_REG_R11 );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.size, FCML_DS_64 );
	CU_ASSERT_EQUAL( decoded_modrm.reg_opcode, FCML_REG_R8 );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.displacement.size, FCML_DS_32 );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.displacement.dis32, 0x01020304 );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.displacement.is_signed, FCML_TRUE );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.scale_factor, 8 );
}

// [R9]+0x01020304, R8
void fcml_tf_modrm_3264_decoder_sib_test_9(void) {

	fcml_st_modrm_decoder_context context = fcml_ifn_modrm_decoder_alloc_ctx();

	context.addr_form = FCML_AF_64_BIT;
	context.effective_address_size = FCML_DS_64;

	fcml_uint8_t buffer[] = { 0x84, 0xE1, 0x04, 0x03, 0x02, 0x01 };

	fcml_st_memory_stream stream;
	stream.base_address = &buffer;
	stream.size = sizeof( buffer );
	stream.offset = 0;

	fcml_st_modrm_source modrm_source = {0};
	modrm_source.ext_b = 1;
	modrm_source.ext_r = 1;
	modrm_source.ext_x = 1;
	modrm_source.stream = &stream;
	fcml_st_modrm decoded_modrm;

	fcml_ceh_error error = fcml_fn_modrm_decode( &context, &modrm_source, &decoded_modrm );

	CU_ASSERT_EQUAL( error, FCML_CEH_GEC_NO_ERROR );
	CU_ASSERT_EQUAL( decoded_modrm.reg.value, FCML_REG_UNDEFINED );
	CU_ASSERT_EQUAL( decoded_modrm.reg.is_not_null, FCML_FALSE );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.type, FCML_REG_GPR );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.reg, FCML_REG_R9 );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.size, FCML_DS_64 );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.type, FCML_REG_UNDEFINED );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.reg, 0 );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.size, 0 );
	CU_ASSERT_EQUAL( decoded_modrm.reg_opcode, FCML_REG_R8 );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.displacement.size, FCML_DS_32 );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.displacement.dis32, 0x01020304 );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.displacement.is_signed, FCML_TRUE );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.scale_factor, 0 );
}

// [ECX+XMM1*8]+0x01020304, R8
void fcml_tf_modrm_3264_decoder_sib_test_10(void) {

	fcml_st_modrm_decoder_context context = fcml_ifn_modrm_decoder_alloc_ctx();

	context.addr_form = FCML_AF_64_BIT;
	context.effective_address_size = FCML_DS_64;

	fcml_uint8_t buffer[] = { 0x84, 0xD9, 0x04, 0x03, 0x02, 0x01 };

	fcml_st_memory_stream stream;
	stream.base_address = &buffer;
	stream.size = sizeof( buffer );
	stream.offset = 0;

	fcml_st_modrm_source modrm_source = {0};
	modrm_source.ext_b = 1;
	modrm_source.ext_r = 1;
	modrm_source.ext_x = 1;
	modrm_source.stream = &stream;
	modrm_source.is_vsib = FCML_TRUE;
	modrm_source.vsib_index_size = FCML_DS_128;
	fcml_st_modrm decoded_modrm;

	fcml_ceh_error error = fcml_fn_modrm_decode( &context, &modrm_source, &decoded_modrm );

	CU_ASSERT_EQUAL( error, FCML_CEH_GEC_NO_ERROR );
	CU_ASSERT_EQUAL( decoded_modrm.reg.value, FCML_REG_UNDEFINED );
	CU_ASSERT_EQUAL( decoded_modrm.reg.is_not_null, FCML_FALSE );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.type, FCML_REG_GPR );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.reg, FCML_REG_R9 );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.size, FCML_DS_64 );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.type, FCML_REG_SIMD );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.reg, FCML_REG_XMM11 );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.size, FCML_DS_128 );
	CU_ASSERT_EQUAL( decoded_modrm.reg_opcode, FCML_REG_R8 );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.displacement.size, FCML_DS_32 );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.displacement.dis32, 0x01020304 );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.displacement.is_signed, FCML_TRUE );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.scale_factor, 8 );
}

// [ECX+YMM1*8]+0x01020304, R8
void fcml_tf_modrm_3264_decoder_sib_test_11(void) {

	fcml_st_modrm_decoder_context context = fcml_ifn_modrm_decoder_alloc_ctx();

	context.addr_form = FCML_AF_64_BIT;
	context.effective_address_size = FCML_DS_64;

	fcml_uint8_t buffer[] = { 0x84, 0xD9, 0x04, 0x03, 0x02, 0x01 };

	fcml_st_memory_stream stream;
	stream.base_address = &buffer;
	stream.size = sizeof( buffer );
	stream.offset = 0;

	fcml_st_modrm_source modrm_source = {0};
	modrm_source.ext_b = 1;
	modrm_source.ext_r = 1;
	modrm_source.ext_x = 1;
	modrm_source.stream = &stream;
	modrm_source.is_vsib = FCML_TRUE;
	modrm_source.vsib_index_size = FCML_DS_256;
	fcml_st_modrm decoded_modrm;

	fcml_ceh_error error = fcml_fn_modrm_decode( &context, &modrm_source, &decoded_modrm );

	CU_ASSERT_EQUAL( error, FCML_CEH_GEC_NO_ERROR );
	CU_ASSERT_EQUAL( decoded_modrm.reg.value, FCML_REG_UNDEFINED );
	CU_ASSERT_EQUAL( decoded_modrm.reg.is_not_null, FCML_FALSE );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.type, FCML_REG_GPR );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.reg, FCML_REG_R9 );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.size, FCML_DS_64 );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.type, FCML_REG_SIMD );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.reg, FCML_REG_XMM11 );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.size, FCML_DS_256 );
	CU_ASSERT_EQUAL( decoded_modrm.reg_opcode, FCML_REG_R8 );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.displacement.size, FCML_DS_32 );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.displacement.dis32, 0x01020304 );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.displacement.is_signed, FCML_TRUE );
	CU_ASSERT_EQUAL( decoded_modrm.address.effective_address.scale_factor, 8 );
}

CU_TestInfo fctl_ti_modrm_decoder[] = {
    { "fcml_tf_modrm_decoder_test_1", fcml_tf_modrm_decoder_test_1 },
    { "fcml_tf_modrm_decoder_test_2", fcml_tf_modrm_decoder_test_2 },
    { "fcml_tf_modrm_decoder_test_3", fcml_tf_modrm_decoder_test_3 },
    { "fcml_tf_modrm_decoder_test_4", fcml_tf_modrm_decoder_test_4 },
    { "fcml_tf_modrm_decoder_test_5", fcml_tf_modrm_decoder_test_5 },
    { "fcml_tf_modrm_decoder_test_6", fcml_tf_modrm_decoder_test_6 },
    { "fcml_tf_modrm_decoder_test_7", fcml_tf_modrm_decoder_test_7 },
    { "fcml_tf_modrm_3264_decoder_test_1", fcml_tf_modrm_3264_decoder_test_1 },
    { "fcml_tf_modrm_3264_decoder_test_2", fcml_tf_modrm_3264_decoder_test_2 },
    { "fcml_tf_modrm_3264_decoder_test_3", fcml_tf_modrm_3264_decoder_test_3 },
    { "fcml_tf_modrm_3264_decoder_test_4", fcml_tf_modrm_3264_decoder_test_4 },
    { "fcml_tf_modrm_3264_decoder_test_5", fcml_tf_modrm_3264_decoder_test_5 },
    { "fcml_tf_modrm_3264_decoder_test_6", fcml_tf_modrm_3264_decoder_test_6 },
    { "fcml_tf_modrm_3264_decoder_test_7", fcml_tf_modrm_3264_decoder_test_7 },
    { "fcml_tf_modrm_3264_decoder_test_8", fcml_tf_modrm_3264_decoder_test_8 },
    { "fcml_tf_modrm_3264_decoder_test_9", fcml_tf_modrm_3264_decoder_test_9 },
    { "fcml_tf_modrm_3264_decoder_test_10", fcml_tf_modrm_3264_decoder_test_10 },
    { "fcml_tf_modrm_3264_decoder_test_11", fcml_tf_modrm_3264_decoder_test_11 },
    { "fcml_tf_modrm_3264_decoder_test_12", fcml_tf_modrm_3264_decoder_test_12 },
    { "fcml_tf_modrm_3264_decoder_sib_test_1", fcml_tf_modrm_3264_decoder_sib_test_1 },
    { "fcml_tf_modrm_3264_decoder_sib_test_2", fcml_tf_modrm_3264_decoder_sib_test_2 },
    { "fcml_tf_modrm_3264_decoder_sib_test_3", fcml_tf_modrm_3264_decoder_sib_test_3 },
    { "fcml_tf_modrm_3264_decoder_sib_test_4", fcml_tf_modrm_3264_decoder_sib_test_4 },
    { "fcml_tf_modrm_3264_decoder_sib_test_5", fcml_tf_modrm_3264_decoder_sib_test_5 },
    { "fcml_tf_modrm_3264_decoder_sib_test_6", fcml_tf_modrm_3264_decoder_sib_test_6 },
    { "fcml_tf_modrm_3264_decoder_sib_test_7", fcml_tf_modrm_3264_decoder_sib_test_7 },
    { "fcml_tf_modrm_3264_decoder_sib_test_8", fcml_tf_modrm_3264_decoder_sib_test_8 },
    { "fcml_tf_modrm_3264_decoder_sib_test_9", fcml_tf_modrm_3264_decoder_sib_test_9 },
    { "fcml_tf_modrm_3264_decoder_sib_test_10", fcml_tf_modrm_3264_decoder_sib_test_10 },
    { "fcml_tf_modrm_3264_decoder_sib_test_11", fcml_tf_modrm_3264_decoder_sib_test_11 },
    CU_TEST_INFO_NULL,
};

CU_SuiteInfo fctl_si_modrm_decoder[] = {
    { "suite-modrm", fcml_tf_modrm_decoder_suite_init, fcml_tf_modrm_decoder_suite_cleanup, fctl_ti_modrm_decoder },
    CU_SUITE_INFO_NULL,
};


