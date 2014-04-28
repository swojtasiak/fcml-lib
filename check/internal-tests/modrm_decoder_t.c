/*
 * modrm_decoder.c
 *
 *  Created on: 04-02-2013
 *      Author: Slawomir Wojtasiak
 */

#include "modrm_decoder_t.h"

#include <fcml_modrm_decoder.h>
#include <fcml_env.h>
#include <fcml_errors.h>

fcml_st_modrm_decoder_context fcml_ifn_modrm_decoder_alloc_ctx() {
	fcml_st_modrm_decoder_context context;
	fcml_fn_env_memory_clear( &context, sizeof( context ) );
	return context;
}

void fcml_tf_modrm_decoder_suite_init(void) {
}

void fcml_tf_modrm_decoder_suite_cleanup(void) {
}

void fcml_tf_modrm_decoder_test_1(void) {

	fcml_st_modrm_decoder_context context = fcml_ifn_modrm_decoder_alloc_ctx();

	context.op_mode = FCML_AF_32_BIT;
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

	fcml_st_modrm_details details;

	fcml_ceh_error error = fcml_fn_modrm_decode( &context, &modrm_source, &decoded_modrm, &details, 0 );

	STF_ASSERT_EQUAL( error, FCML_CEH_GEC_NO_ERROR );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.type, FCML_REG_GPR );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.reg, FCML_REG_BX );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.size, FCML_DS_16 );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.type, FCML_REG_UNDEFINED );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.reg, 0 );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.size, 0 );
	STF_ASSERT_EQUAL( decoded_modrm.reg_opcode, FCML_REG_DX );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.displacement.size, 0 );
	STF_ASSERT_EQUAL( decoded_modrm.reg.is_not_null, FCML_FALSE );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.scale_factor, 0 );

}

void fcml_tf_modrm_decoder_test_2(void) {

	fcml_st_modrm_decoder_context context = fcml_ifn_modrm_decoder_alloc_ctx();

	context.op_mode = FCML_AF_32_BIT;
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

	fcml_st_modrm_details details;
	fcml_ceh_error error = fcml_fn_modrm_decode( &context, &modrm_source, &decoded_modrm, &details, 0 );

	STF_ASSERT_EQUAL( error, FCML_CEH_GEC_NO_ERROR );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.type, FCML_REG_UNDEFINED );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.reg, 0 );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.size, 0 );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.type, FCML_REG_UNDEFINED );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.reg, 0 );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.size, 0 );
	STF_ASSERT_EQUAL( decoded_modrm.reg_opcode, FCML_REG_BX );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.displacement.size, FCML_DS_16 );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.displacement.int16, 0x0201 );
	STF_ASSERT_EQUAL( decoded_modrm.reg.is_not_null, FCML_FALSE );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.scale_factor, 0 );

}

void fcml_tf_modrm_decoder_test_3(void) {

	fcml_st_modrm_decoder_context context = fcml_ifn_modrm_decoder_alloc_ctx();

	context.op_mode = FCML_AF_32_BIT;
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

	fcml_st_modrm_details details;
	fcml_ceh_error error = fcml_fn_modrm_decode( &context, &modrm_source, &decoded_modrm, &details, 0 );

	STF_ASSERT_EQUAL( error, FCML_CEH_GEC_NO_ERROR );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.type, FCML_REG_GPR );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.reg, FCML_REG_BP );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.size, FCML_DS_16 );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.type, FCML_REG_GPR );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.reg, FCML_REG_DI );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.size, FCML_DS_16 );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.displacement.size, 0 );
	STF_ASSERT_EQUAL( decoded_modrm.reg_opcode, FCML_REG_CX );
	STF_ASSERT_EQUAL( decoded_modrm.reg.is_not_null, FCML_FALSE );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.scale_factor, 0 );

}

void fcml_tf_modrm_decoder_test_4(void) {

	fcml_st_modrm_decoder_context context = fcml_ifn_modrm_decoder_alloc_ctx();

	context.op_mode = FCML_AF_32_BIT;
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

	fcml_st_modrm_details details;

	fcml_ceh_error error = fcml_fn_modrm_decode( &context, &modrm_source, &decoded_modrm, &details, 0 );

	STF_ASSERT_EQUAL( error, FCML_CEH_GEC_NO_ERROR );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.type, FCML_REG_GPR );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.reg, FCML_REG_SI );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.size, FCML_DS_16 );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.type, FCML_REG_UNDEFINED );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.reg, 0 );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.size, 0 );
	STF_ASSERT_EQUAL( decoded_modrm.reg_opcode, FCML_REG_DX );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.displacement.size, 0 );
	STF_ASSERT_EQUAL( decoded_modrm.reg.is_not_null, FCML_FALSE );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.scale_factor, 0 );

}

void fcml_tf_modrm_decoder_test_5(void) {

	fcml_st_modrm_decoder_context context = fcml_ifn_modrm_decoder_alloc_ctx();

	context.op_mode = FCML_AF_64_BIT;
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

	fcml_st_modrm_details details;

	fcml_ceh_error error = fcml_fn_modrm_decode( &context, &modrm_source, &decoded_modrm, &details, 0 );

	STF_ASSERT_EQUAL( error, FCML_CEH_GEC_INVALID_ADDRESSING_FORM );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.type, FCML_REG_UNDEFINED );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.reg, 0 );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.size, 0 );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.type, FCML_REG_UNDEFINED );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.reg, 0 );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.size, 0 );
	STF_ASSERT_EQUAL( decoded_modrm.reg_opcode, 0 );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.displacement.size, 0 );
	STF_ASSERT_EQUAL( decoded_modrm.reg.is_not_null, FCML_FALSE );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.scale_factor, 0 );

}

void fcml_tf_modrm_decoder_test_6(void) {

	fcml_st_modrm_decoder_context context = fcml_ifn_modrm_decoder_alloc_ctx();

	context.op_mode = FCML_AF_32_BIT;
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
	fcml_st_modrm_details details;

	fcml_ceh_error error = fcml_fn_modrm_decode( &context, &modrm_source, &decoded_modrm, &details, 0 );

	STF_ASSERT_EQUAL( error, FCML_CEH_GEC_NO_ERROR );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.type, FCML_REG_GPR );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.reg, FCML_REG_BP );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.size, FCML_DS_16 );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.type, FCML_REG_GPR );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.reg, FCML_REG_DI );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.size, FCML_DS_16 );
	STF_ASSERT_EQUAL( decoded_modrm.reg_opcode, FCML_REG_SI );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.displacement.size, FCML_DS_8 );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.displacement.int8, 0x01 );
	STF_ASSERT_EQUAL( decoded_modrm.reg.is_not_null, FCML_FALSE );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.scale_factor, 0 );

}

void fcml_tf_modrm_decoder_test_7(void) {

	fcml_st_modrm_decoder_context context = fcml_ifn_modrm_decoder_alloc_ctx();

	context.op_mode = FCML_AF_32_BIT;
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
	fcml_st_modrm_details details;

	fcml_ceh_error error = fcml_fn_modrm_decode( &context, &modrm_source, &decoded_modrm, &details, 0 );

	STF_ASSERT_EQUAL( error, FCML_CEH_GEC_EOF );

}

/* [EBX], EBX*/
void fcml_tf_modrm_3264_decoder_test_1(void) {

	fcml_st_modrm_decoder_context context = fcml_ifn_modrm_decoder_alloc_ctx();

	context.op_mode = FCML_AF_32_BIT;
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
	fcml_st_modrm_details details;

	fcml_ceh_error error = fcml_fn_modrm_decode( &context, &modrm_source, &decoded_modrm, &details, 0 );

	STF_ASSERT_EQUAL( error, FCML_CEH_GEC_NO_ERROR );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.type, FCML_REG_GPR );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.reg, FCML_REG_EBX );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.size, FCML_DS_32 );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.type, FCML_REG_UNDEFINED );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.reg, 0 );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.size, 0 );
	STF_ASSERT_EQUAL( decoded_modrm.reg_opcode, FCML_REG_EBX );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.displacement.size, 0 );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.displacement.int8, 0 );
	STF_ASSERT_EQUAL( decoded_modrm.reg.is_not_null, FCML_FALSE );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.scale_factor, 0 );

}

/* [04030201], EDX*/
void fcml_tf_modrm_3264_decoder_test_2(void) {

	fcml_st_modrm_decoder_context context = fcml_ifn_modrm_decoder_alloc_ctx();

	context.op_mode = FCML_AF_32_BIT;
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
	fcml_st_modrm_details details;

	fcml_ceh_error error = fcml_fn_modrm_decode( &context, &modrm_source, &decoded_modrm, &details, 0 );

	STF_ASSERT_EQUAL( error, FCML_CEH_GEC_NO_ERROR );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.type, FCML_REG_UNDEFINED );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.reg, 0 );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.size, 0 );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.type, FCML_REG_UNDEFINED );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.reg, 0 );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.size, 0 );
	STF_ASSERT_EQUAL( decoded_modrm.reg_opcode, FCML_REG_EDX );
	STF_ASSERT_EQUAL( decoded_modrm.address.offset.size, FCML_DS_32 );
	STF_ASSERT_EQUAL( decoded_modrm.address.offset.off32, 0x04030201 );
	STF_ASSERT_EQUAL( decoded_modrm.address.offset.is_signed, FCML_TRUE );
	STF_ASSERT_EQUAL( decoded_modrm.reg.is_not_null, FCML_FALSE );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.scale_factor, 0 );
}

/* RIP-addressing.*/
/* RIP: 401000h*/
/* disp32: 0f1efbf00h*/
/* [FFFFFFFFFF887766], EDX*/
void fcml_tf_modrm_3264_decoder_test_3(void) {

	fcml_st_modrm_decoder_context context = fcml_ifn_modrm_decoder_alloc_ctx();

	context.op_mode = FCML_AF_64_BIT;
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
	fcml_st_modrm_details details;

	fcml_ceh_error error = fcml_fn_modrm_decode( &context, &modrm_source, &decoded_modrm, &details, 0 );

	STF_ASSERT_EQUAL( error, FCML_CEH_GEC_NO_ERROR );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.type, FCML_REG_IP );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.reg, 0 );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.size, FCML_DS_64 );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.type, FCML_REG_UNDEFINED );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.reg, 0 );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.size, 0 );
	STF_ASSERT_EQUAL( decoded_modrm.reg_opcode, FCML_REG_EDX );
	STF_ASSERT_EQUAL( decoded_modrm.address.offset.size, FCML_DS_32 );
	STF_ASSERT_EQUAL( decoded_modrm.address.offset.off32, 0xFFBFF1FA );
	STF_ASSERT_EQUAL( decoded_modrm.address.offset.is_signed, FCML_TRUE );
	STF_ASSERT_EQUAL( decoded_modrm.reg.is_not_null, FCML_FALSE );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.scale_factor, 0 );
	STF_ASSERT_EQUAL( decoded_modrm.is_rip, FCML_TRUE );

	fcml_st_offset address = {0};
	error = fcml_fn_modrm_decode_rip( 0x401000, FCML_DS_64, &(decoded_modrm.address.offset), &address );

	STF_ASSERT_EQUAL( address.size, FCML_DS_64 );
	STF_ASSERT_EQUAL( address.off64, 0x1faUL );

}

/* [ECX]+0x66, EAX*/
void fcml_tf_modrm_3264_decoder_test_4(void) {

	fcml_st_modrm_decoder_context context = fcml_ifn_modrm_decoder_alloc_ctx();

	context.op_mode = FCML_AF_64_BIT;
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
	fcml_st_modrm_details details;

	fcml_ceh_error error = fcml_fn_modrm_decode( &context, &modrm_source, &decoded_modrm, &details, 0 );

	STF_ASSERT_EQUAL( error, FCML_CEH_GEC_NO_ERROR );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.type, FCML_REG_GPR );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.reg, FCML_REG_ECX );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.size, FCML_DS_32 );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.type, FCML_REG_UNDEFINED );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.reg, 0 );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.size, 0 );
	STF_ASSERT_EQUAL( decoded_modrm.reg_opcode, FCML_REG_EAX );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.displacement.size, FCML_DS_8 );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.displacement.int8, 0x66 );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.displacement.is_signed, FCML_TRUE );
	STF_ASSERT_EQUAL( decoded_modrm.reg.is_not_null, FCML_FALSE );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.scale_factor, 0 );
}


/* [ECX]+0x01020304, EAX*/
void fcml_tf_modrm_3264_decoder_test_5(void) {

	fcml_st_modrm_decoder_context context = fcml_ifn_modrm_decoder_alloc_ctx();

	context.op_mode = FCML_AF_64_BIT;
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
	fcml_st_modrm_details details;

	fcml_ceh_error error = fcml_fn_modrm_decode( &context, &modrm_source, &decoded_modrm, &details, 0 );

	STF_ASSERT_EQUAL( error, FCML_CEH_GEC_NO_ERROR );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.type, FCML_REG_GPR );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.reg, FCML_REG_ECX );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.size, FCML_DS_32 );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.type, FCML_REG_UNDEFINED );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.reg, 0 );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.size, 0 );
	STF_ASSERT_EQUAL( decoded_modrm.reg_opcode, FCML_REG_EAX );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.displacement.size, FCML_DS_32 );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.displacement.int32, 0x01020304 );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.displacement.is_signed, FCML_TRUE );
	STF_ASSERT_EQUAL( decoded_modrm.reg.is_not_null, FCML_FALSE );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.scale_factor, 0 );
}

/* [R9]+0x01020304, R8*/
void fcml_tf_modrm_3264_decoder_test_6(void) {

	fcml_st_modrm_decoder_context context = fcml_ifn_modrm_decoder_alloc_ctx();

	context.op_mode = FCML_AF_64_BIT;
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
	fcml_st_modrm_details details;

	fcml_ceh_error error = fcml_fn_modrm_decode( &context, &modrm_source, &decoded_modrm, &details, 0 );

	STF_ASSERT_EQUAL( error, FCML_CEH_GEC_NO_ERROR );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.type, FCML_REG_GPR );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.reg, FCML_REG_R9 );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.size, FCML_DS_64 );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.type, FCML_REG_UNDEFINED );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.reg, 0 );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.size, 0 );
	STF_ASSERT_EQUAL( decoded_modrm.reg_opcode, FCML_REG_R8 );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.displacement.size, FCML_DS_32 );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.displacement.int32, 0x01020304 );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.displacement.is_signed, FCML_TRUE );
	STF_ASSERT_EQUAL( decoded_modrm.reg.is_not_null, FCML_FALSE );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.scale_factor, 0 );
}

/* Illegal EASA size.*/
void fcml_tf_modrm_3264_decoder_test_7(void) {

	fcml_st_modrm_decoder_context context = fcml_ifn_modrm_decoder_alloc_ctx();

	context.op_mode = FCML_AF_64_BIT;
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
	fcml_st_modrm_details details;

	fcml_ceh_error error = fcml_fn_modrm_decode( &context, &modrm_source, &decoded_modrm, &details, 0 );

	STF_ASSERT_EQUAL( error, FCML_CEH_GEC_INVALID_ADDRESSING_FORM );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.type, FCML_REG_UNDEFINED );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.reg, 0 );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.size, 0 );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.type, FCML_REG_UNDEFINED );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.reg, 0 );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.size, 0 );
	STF_ASSERT_EQUAL( decoded_modrm.reg_opcode, 0 );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.displacement.size, 0 );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.displacement.int32, 0 );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.displacement.is_signed, FCML_FALSE );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.displacement.size, 0 );
    STF_ASSERT_EQUAL( decoded_modrm.address.offset.off32, 0 );
    STF_ASSERT_EQUAL( decoded_modrm.address.offset.is_signed, FCML_FALSE );
	STF_ASSERT_EQUAL( decoded_modrm.reg.is_not_null, FCML_FALSE );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.scale_factor, 0 );
}

/* RAX, EBX*/
void fcml_tf_modrm_3264_decoder_test_8(void) {

	fcml_st_modrm_decoder_context context = fcml_ifn_modrm_decoder_alloc_ctx();

	context.op_mode = FCML_AF_64_BIT;
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
	fcml_st_modrm_details details;

	fcml_ceh_error error = fcml_fn_modrm_decode( &context, &modrm_source, &decoded_modrm, &details, 0 );

	STF_ASSERT_EQUAL( error, FCML_CEH_GEC_NO_ERROR );
	STF_ASSERT_EQUAL( decoded_modrm.reg.value, FCML_REG_RAX );
	STF_ASSERT_EQUAL( decoded_modrm.reg.is_not_null, FCML_TRUE );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.type, FCML_REG_UNDEFINED );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.reg, 0 );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.size, 0 );
	STF_ASSERT_EQUAL( decoded_modrm.reg_opcode, FCML_REG_RBX );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.displacement.size, 0 );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.displacement.int32, 0 );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.displacement.is_signed, FCML_FALSE );
	STF_ASSERT_EQUAL( decoded_modrm.address.offset.size, 0 );
    STF_ASSERT_EQUAL( decoded_modrm.address.offset.off32, 0 );
    STF_ASSERT_EQUAL( decoded_modrm.address.offset.is_signed, FCML_FALSE );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.scale_factor, 0 );
}

/* R8, R11*/
void fcml_tf_modrm_3264_decoder_test_9(void) {

	fcml_st_modrm_decoder_context context = fcml_ifn_modrm_decoder_alloc_ctx();

	context.op_mode = FCML_AF_64_BIT;
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
	fcml_st_modrm_details details;

	fcml_ceh_error error = fcml_fn_modrm_decode( &context, &modrm_source, &decoded_modrm, &details, 0 );

	STF_ASSERT_EQUAL( error, FCML_CEH_GEC_NO_ERROR );
	STF_ASSERT_EQUAL( decoded_modrm.reg.value, FCML_REG_R8 );
	STF_ASSERT_EQUAL( decoded_modrm.reg.is_not_null, FCML_TRUE );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.type, FCML_REG_UNDEFINED );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.reg, 0 );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.size, 0 );
	STF_ASSERT_EQUAL( decoded_modrm.reg_opcode, FCML_REG_R11 );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.displacement.size, 0 );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.displacement.int32, 0 );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.displacement.is_signed, FCML_FALSE );
	STF_ASSERT_EQUAL( decoded_modrm.address.offset.size, 0 );
    STF_ASSERT_EQUAL( decoded_modrm.address.offset.off64, 0 );
    STF_ASSERT_EQUAL( decoded_modrm.address.offset.is_signed, FCML_FALSE );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.scale_factor, 0 );
}


/* RIP-addressing.*/
void fcml_tf_modrm_3264_decoder_test_10(void) {

	fcml_st_modrm_decoder_context context = fcml_ifn_modrm_decoder_alloc_ctx();

	context.op_mode = FCML_AF_64_BIT;
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
	fcml_st_modrm_details details;

	fcml_ceh_error error = fcml_fn_modrm_decode( &context, &modrm_source, &decoded_modrm, &details, 0 );

	STF_ASSERT_EQUAL( error, FCML_CEH_GEC_NO_ERROR );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.type, FCML_REG_IP );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.reg, 0 );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.size, FCML_DS_64 );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.type, FCML_REG_UNDEFINED );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.reg, 0 );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.size, 0 );
	STF_ASSERT_EQUAL( decoded_modrm.reg_opcode, FCML_REG_EDX );
	STF_ASSERT_EQUAL( decoded_modrm.address.offset.size, FCML_DS_32 );
	STF_ASSERT_EQUAL( decoded_modrm.address.offset.off32, 0xFFFFFFFF );
	STF_ASSERT_EQUAL( decoded_modrm.address.offset.is_signed, FCML_TRUE );
	STF_ASSERT_EQUAL( decoded_modrm.reg.is_not_null, FCML_FALSE );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.scale_factor, 0 );
	STF_ASSERT_EQUAL( decoded_modrm.is_rip, FCML_TRUE );

	fcml_st_offset address = {0};
	error = fcml_fn_modrm_decode_rip( 0x401000, FCML_DS_64, &(decoded_modrm.address.offset), &address );

	STF_ASSERT_EQUAL( address.size, FCML_DS_64 );
	STF_ASSERT_EQUAL( address.off64, 0x400fffUL );

}

/* RIP-addressing.*/
void fcml_tf_modrm_3264_decoder_test_11(void) {

	fcml_st_modrm_decoder_context context = fcml_ifn_modrm_decoder_alloc_ctx();

	context.op_mode = FCML_AF_64_BIT;
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
	fcml_st_modrm_details details;

	fcml_ceh_error error = fcml_fn_modrm_decode( &context, &modrm_source, &decoded_modrm, &details, 0 );

	STF_ASSERT_EQUAL( error, FCML_CEH_GEC_NO_ERROR );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.type, FCML_REG_IP );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.reg, 0 );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.size, FCML_DS_64 );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.type, FCML_REG_UNDEFINED );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.reg, 0 );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.size, 0 );
	STF_ASSERT_EQUAL( decoded_modrm.reg_opcode, FCML_REG_EDX );
	STF_ASSERT_EQUAL( decoded_modrm.address.offset.size, FCML_DS_32 );
	STF_ASSERT_EQUAL( decoded_modrm.address.offset.off32, 0xFF7FE000 );
	STF_ASSERT_EQUAL( decoded_modrm.address.offset.is_signed, FCML_TRUE );
	STF_ASSERT_EQUAL( decoded_modrm.reg.is_not_null, FCML_FALSE );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.scale_factor, 0 );
	STF_ASSERT_EQUAL( decoded_modrm.is_rip, FCML_TRUE );

	fcml_st_offset address = {0};
	error = fcml_fn_modrm_decode_rip( 0x401000, FCML_DS_64, &(decoded_modrm.address.offset), &address );

	STF_ASSERT_EQUAL( address.size, FCML_DS_64 );
	STF_ASSERT_EQUAL( address.off64, 0xffffffffffbff000UL );

}

/* RIP-addressing.*/
void fcml_tf_modrm_3264_decoder_test_12(void) {

	fcml_st_modrm_decoder_context context = fcml_ifn_modrm_decoder_alloc_ctx();

	context.op_mode = FCML_AF_64_BIT;
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
	fcml_st_modrm_details details;

	fcml_ceh_error error = fcml_fn_modrm_decode( &context, &modrm_source, &decoded_modrm, &details, 0 );

	STF_ASSERT_EQUAL( error, FCML_CEH_GEC_NO_ERROR );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.type, FCML_REG_IP );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.reg, 0 );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.size, FCML_DS_64 );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.type, FCML_REG_UNDEFINED );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.reg, 0 );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.size, 0 );
	STF_ASSERT_EQUAL( decoded_modrm.reg_opcode, FCML_REG_EDX );
	STF_ASSERT_EQUAL( decoded_modrm.address.offset.size, FCML_DS_32 );
	STF_ASSERT_EQUAL( decoded_modrm.address.offset.off32, 0xFF7FE000 );
	STF_ASSERT_EQUAL( decoded_modrm.address.offset.is_signed, FCML_TRUE );
	STF_ASSERT_EQUAL( decoded_modrm.reg.is_not_null, FCML_FALSE );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.scale_factor, 0 );
	STF_ASSERT_EQUAL( decoded_modrm.is_rip, FCML_TRUE );

	fcml_st_offset address = {0};
	error = fcml_fn_modrm_decode_rip( 0x401000, FCML_DS_32, &(decoded_modrm.address.offset), &address );

	STF_ASSERT_EQUAL( address.size, FCML_DS_64 );
	STF_ASSERT_EQUAL( address.off64, 0x00000000ffbff000UL );

}

/* [01020304], R8*/
void fcml_tf_modrm_3264_decoder_sib_test_1(void) {

	fcml_st_modrm_decoder_context context = fcml_ifn_modrm_decoder_alloc_ctx();

	context.op_mode = FCML_AF_64_BIT;
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
	fcml_st_modrm_details details;

	fcml_ceh_error error = fcml_fn_modrm_decode( &context, &modrm_source, &decoded_modrm, &details, 0 );

	STF_ASSERT_EQUAL( error, FCML_CEH_GEC_NO_ERROR );
	STF_ASSERT_EQUAL( decoded_modrm.reg.value, FCML_REG_UNDEFINED );
	STF_ASSERT_EQUAL( decoded_modrm.reg.is_not_null, FCML_FALSE );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.type, FCML_REG_UNDEFINED );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.reg, 0 );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.size, 0 );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.type, FCML_REG_UNDEFINED );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.reg, 0 );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.size, 0 );
	STF_ASSERT_EQUAL( decoded_modrm.reg_opcode, FCML_REG_R8 );
	STF_ASSERT_EQUAL( decoded_modrm.address.offset.size, FCML_DS_64 );
	STF_ASSERT_EQUAL( decoded_modrm.address.offset.off64, 0x01020304 );
	STF_ASSERT_EQUAL( decoded_modrm.address.offset.is_signed, FCML_TRUE );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.scale_factor, 0 );
}

/* [EBX]+0x01020304, R8*/
void fcml_tf_modrm_3264_decoder_sib_test_2(void) {

	fcml_st_modrm_decoder_context context = fcml_ifn_modrm_decoder_alloc_ctx();

	context.op_mode = FCML_AF_64_BIT;
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
	fcml_st_modrm_details details;

	fcml_ceh_error error = fcml_fn_modrm_decode( &context, &modrm_source, &decoded_modrm, &details, 0 );

	STF_ASSERT_EQUAL( error, FCML_CEH_GEC_NO_ERROR );
	STF_ASSERT_EQUAL( decoded_modrm.reg.value, FCML_REG_UNDEFINED );
	STF_ASSERT_EQUAL( decoded_modrm.reg.is_not_null, FCML_FALSE );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.type, FCML_REG_UNDEFINED );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.reg, 0 );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.size, 0 );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.type, FCML_REG_GPR );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.reg, FCML_REG_R11 );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.size, FCML_DS_64 );
	STF_ASSERT_EQUAL( decoded_modrm.reg_opcode, FCML_REG_R8 );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.displacement.size, 32 );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.displacement.int32, 0x01020304 );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.displacement.is_signed, FCML_TRUE );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.scale_factor, 0 );
}

/* [ECX+EBX]+0x01, R8*/
void fcml_tf_modrm_3264_decoder_sib_test_3(void) {

	fcml_st_modrm_decoder_context context = fcml_ifn_modrm_decoder_alloc_ctx();

	context.op_mode = FCML_AF_64_BIT;
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
	fcml_st_modrm_details details;

	fcml_ceh_error error = fcml_fn_modrm_decode( &context, &modrm_source, &decoded_modrm, &details, 0 );

	STF_ASSERT_EQUAL( error, FCML_CEH_GEC_NO_ERROR );
	STF_ASSERT_EQUAL( decoded_modrm.reg.value, FCML_REG_UNDEFINED );
	STF_ASSERT_EQUAL( decoded_modrm.reg.is_not_null, FCML_FALSE );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.type, FCML_REG_GPR );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.reg, FCML_REG_R9 );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.size, FCML_DS_64 );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.type, FCML_REG_GPR );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.reg, FCML_REG_R11 );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.size, FCML_DS_64 );
	STF_ASSERT_EQUAL( decoded_modrm.reg_opcode, FCML_REG_R8 );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.displacement.size, 0 );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.displacement.int32, 0 );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.displacement.is_signed, FCML_FALSE );
	STF_ASSERT_EQUAL( decoded_modrm.address.offset.size, 0 );
    STF_ASSERT_EQUAL( decoded_modrm.address.offset.off32, 0 );
    STF_ASSERT_EQUAL( decoded_modrm.address.offset.is_signed, FCML_FALSE );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.scale_factor, 0 );
}

/* [ECX+EBX*2]+0x01, R8*/
void fcml_tf_modrm_3264_decoder_sib_test_4(void) {

	fcml_st_modrm_decoder_context context = fcml_ifn_modrm_decoder_alloc_ctx();

	context.op_mode = FCML_AF_64_BIT;
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
	fcml_st_modrm_details details;

	fcml_ceh_error error = fcml_fn_modrm_decode( &context, &modrm_source, &decoded_modrm, &details, 0 );

	STF_ASSERT_EQUAL( error, FCML_CEH_GEC_NO_ERROR );
	STF_ASSERT_EQUAL( decoded_modrm.reg.value, FCML_REG_UNDEFINED );
	STF_ASSERT_EQUAL( decoded_modrm.reg.is_not_null, FCML_FALSE );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.type, FCML_REG_GPR );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.reg, FCML_REG_R9 );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.size, FCML_DS_64 );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.type, FCML_REG_GPR );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.reg, FCML_REG_R11 );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.size, FCML_DS_64 );
	STF_ASSERT_EQUAL( decoded_modrm.reg_opcode, FCML_REG_R8 );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.displacement.size, 0 );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.displacement.int32, 0 );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.displacement.is_signed, FCML_FALSE );
	STF_ASSERT_EQUAL( decoded_modrm.address.offset.size, 0 );
    STF_ASSERT_EQUAL( decoded_modrm.address.offset.off32, 0 );
    STF_ASSERT_EQUAL( decoded_modrm.address.offset.is_signed, FCML_FALSE );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.scale_factor, 2 );
}

/* [ECX+EBX*4], R8*/
void fcml_tf_modrm_3264_decoder_sib_test_5(void) {

	fcml_st_modrm_decoder_context context = fcml_ifn_modrm_decoder_alloc_ctx();

	context.op_mode = FCML_AF_64_BIT;
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
	fcml_st_modrm_details details;

	fcml_ceh_error error = fcml_fn_modrm_decode( &context, &modrm_source, &decoded_modrm, &details, 0 );

	STF_ASSERT_EQUAL( error, FCML_CEH_GEC_NO_ERROR );
	STF_ASSERT_EQUAL( decoded_modrm.reg.value, FCML_REG_UNDEFINED );
	STF_ASSERT_EQUAL( decoded_modrm.reg.is_not_null, FCML_FALSE );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.type, FCML_REG_GPR );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.reg, FCML_REG_R9 );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.size, FCML_DS_64 );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.type, FCML_REG_GPR );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.reg, FCML_REG_R11 );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.size, FCML_DS_64 );
	STF_ASSERT_EQUAL( decoded_modrm.reg_opcode, FCML_REG_R8 );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.displacement.size, 0 );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.displacement.int32, 0 );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.displacement.is_signed, FCML_FALSE );
	STF_ASSERT_EQUAL( decoded_modrm.address.offset.size, 0 );
    STF_ASSERT_EQUAL( decoded_modrm.address.offset.off32, 0 );
    STF_ASSERT_EQUAL( decoded_modrm.address.offset.is_signed, FCML_FALSE );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.scale_factor, 4 );
}

/* [ECX+EBX*8], R8*/
void fcml_tf_modrm_3264_decoder_sib_test_6(void) {

	fcml_st_modrm_decoder_context context = fcml_ifn_modrm_decoder_alloc_ctx();

	context.op_mode = FCML_AF_64_BIT;
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
	fcml_st_modrm_details details;

	fcml_ceh_error error = fcml_fn_modrm_decode( &context, &modrm_source, &decoded_modrm, &details, 0 );

	STF_ASSERT_EQUAL( error, FCML_CEH_GEC_NO_ERROR );
	STF_ASSERT_EQUAL( decoded_modrm.reg.value, FCML_REG_UNDEFINED );
	STF_ASSERT_EQUAL( decoded_modrm.reg.is_not_null, FCML_FALSE );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.type, FCML_REG_GPR );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.reg, FCML_REG_R9 );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.size, FCML_DS_64 );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.type, FCML_REG_GPR );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.reg, FCML_REG_R11 );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.size, FCML_DS_64 );
	STF_ASSERT_EQUAL( decoded_modrm.reg_opcode, FCML_REG_R8 );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.displacement.size, 0 );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.displacement.int32, 0 );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.displacement.is_signed, FCML_FALSE );
	STF_ASSERT_EQUAL( decoded_modrm.address.offset.size, 0 );
    STF_ASSERT_EQUAL( decoded_modrm.address.offset.off32, 0 );
    STF_ASSERT_EQUAL( decoded_modrm.address.offset.is_signed, FCML_FALSE );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.scale_factor, 8 );
}

/* [ECX+EBX*8]+0x55, R8*/
void fcml_tf_modrm_3264_decoder_sib_test_7(void) {

	fcml_st_modrm_decoder_context context = fcml_ifn_modrm_decoder_alloc_ctx();

	context.op_mode = FCML_AF_64_BIT;
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
	fcml_st_modrm_details details;

	fcml_ceh_error error = fcml_fn_modrm_decode( &context, &modrm_source, &decoded_modrm, &details, 0 );

	STF_ASSERT_EQUAL( error, FCML_CEH_GEC_NO_ERROR );
	STF_ASSERT_EQUAL( decoded_modrm.reg.value, FCML_REG_UNDEFINED );
	STF_ASSERT_EQUAL( decoded_modrm.reg.is_not_null, FCML_FALSE );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.type, FCML_REG_GPR );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.reg, FCML_REG_R9 );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.size, FCML_DS_64 );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.type, FCML_REG_GPR );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.reg, FCML_REG_R11 );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.size, FCML_DS_64 );
	STF_ASSERT_EQUAL( decoded_modrm.reg_opcode, FCML_REG_R8 );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.displacement.size, FCML_DS_8 );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.displacement.int8, 0x55 );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.displacement.is_signed, FCML_TRUE );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.scale_factor, 8 );
}

/* [ECX+EBX*8]+0x01020304, R8*/
void fcml_tf_modrm_3264_decoder_sib_test_8(void) {

	fcml_st_modrm_decoder_context context = fcml_ifn_modrm_decoder_alloc_ctx();

	context.op_mode = FCML_AF_64_BIT;
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
	fcml_st_modrm_details details;

	fcml_ceh_error error = fcml_fn_modrm_decode( &context, &modrm_source, &decoded_modrm, &details, 0 );

	STF_ASSERT_EQUAL( error, FCML_CEH_GEC_NO_ERROR );
	STF_ASSERT_EQUAL( decoded_modrm.reg.value, FCML_REG_UNDEFINED );
	STF_ASSERT_EQUAL( decoded_modrm.reg.is_not_null, FCML_FALSE );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.type, FCML_REG_GPR );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.reg, FCML_REG_R9 );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.size, FCML_DS_64 );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.type, FCML_REG_GPR );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.reg, FCML_REG_R11 );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.size, FCML_DS_64 );
	STF_ASSERT_EQUAL( decoded_modrm.reg_opcode, FCML_REG_R8 );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.displacement.size, FCML_DS_32 );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.displacement.int32, 0x01020304 );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.displacement.is_signed, FCML_TRUE );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.scale_factor, 8 );
}

/* [R9]+0x01020304, R8*/
void fcml_tf_modrm_3264_decoder_sib_test_9(void) {

	fcml_st_modrm_decoder_context context = fcml_ifn_modrm_decoder_alloc_ctx();

	context.op_mode = FCML_AF_64_BIT;
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
	fcml_st_modrm_details details;

	fcml_ceh_error error = fcml_fn_modrm_decode( &context, &modrm_source, &decoded_modrm, &details, 0 );

	STF_ASSERT_EQUAL( error, FCML_CEH_GEC_NO_ERROR );
	STF_ASSERT_EQUAL( decoded_modrm.reg.value, FCML_REG_UNDEFINED );
	STF_ASSERT_EQUAL( decoded_modrm.reg.is_not_null, FCML_FALSE );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.type, FCML_REG_GPR );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.reg, FCML_REG_R9 );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.size, FCML_DS_64 );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.type, FCML_REG_UNDEFINED );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.reg, 0 );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.size, 0 );
	STF_ASSERT_EQUAL( decoded_modrm.reg_opcode, FCML_REG_R8 );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.displacement.size, FCML_DS_32 );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.displacement.int32, 0x01020304 );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.displacement.is_signed, FCML_TRUE );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.scale_factor, 0 );
}

/* [ECX+XMM1*8]+0x01020304, R8*/
void fcml_tf_modrm_3264_decoder_sib_test_10(void) {

	fcml_st_modrm_decoder_context context = fcml_ifn_modrm_decoder_alloc_ctx();

	context.op_mode = FCML_AF_64_BIT;
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
	fcml_st_modrm_details details;

	fcml_ceh_error error = fcml_fn_modrm_decode( &context, &modrm_source, &decoded_modrm, &details, 0 );

	STF_ASSERT_EQUAL( error, FCML_CEH_GEC_NO_ERROR );
	STF_ASSERT_EQUAL( decoded_modrm.reg.value, FCML_REG_UNDEFINED );
	STF_ASSERT_EQUAL( decoded_modrm.reg.is_not_null, FCML_FALSE );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.type, FCML_REG_GPR );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.reg, FCML_REG_R9 );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.size, FCML_DS_64 );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.type, FCML_REG_SIMD );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.reg, FCML_REG_XMM11 );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.size, FCML_DS_128 );
	STF_ASSERT_EQUAL( decoded_modrm.reg_opcode, FCML_REG_R8 );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.displacement.size, FCML_DS_32 );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.displacement.int32, 0x01020304 );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.displacement.is_signed, FCML_TRUE );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.scale_factor, 8 );
}

/* [ECX+YMM1*8]+0x01020304, R8*/
void fcml_tf_modrm_3264_decoder_sib_test_11(void) {

	fcml_st_modrm_decoder_context context = fcml_ifn_modrm_decoder_alloc_ctx();

	context.op_mode = FCML_AF_64_BIT;
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
	fcml_st_modrm_details details;

	fcml_ceh_error error = fcml_fn_modrm_decode( &context, &modrm_source, &decoded_modrm, &details, 0 );

	STF_ASSERT_EQUAL( error, FCML_CEH_GEC_NO_ERROR );
	STF_ASSERT_EQUAL( decoded_modrm.reg.value, FCML_REG_UNDEFINED );
	STF_ASSERT_EQUAL( decoded_modrm.reg.is_not_null, FCML_FALSE );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.type, FCML_REG_GPR );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.reg, FCML_REG_R9 );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.base.size, FCML_DS_64 );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.type, FCML_REG_SIMD );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.reg, FCML_REG_XMM11 );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.index.size, FCML_DS_256 );
	STF_ASSERT_EQUAL( decoded_modrm.reg_opcode, FCML_REG_R8 );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.displacement.size, FCML_DS_32 );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.displacement.int32, 0x01020304 );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.displacement.is_signed, FCML_TRUE );
	STF_ASSERT_EQUAL( decoded_modrm.address.effective_address.scale_factor, 8 );
}

fcml_stf_test_case fctl_ti_modrm_decoder[] = {
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
	FCML_STF_NULL_TEST
};

fcml_stf_test_suite fctl_si_modrm_decoder = {
	"suite-modrm", fcml_tf_modrm_decoder_suite_init, fcml_tf_modrm_decoder_suite_cleanup, fctl_ti_modrm_decoder
};



