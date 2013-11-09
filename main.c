/*
 * main.c
 *
 *  Created on: 04-02-2013
 *      Author: Slawomir Wojtasiak
 */

#include <stdio.h>
#include <stdlib.h>

#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

#include "fcml_mnemonic_parser_t.h"
#include "modrm_encoder_t.h"
#include "modrm_decoder_t.h"
#include "stream_t.h"
#include "fcml_coll_t.h"
#include "fcml_utils_t.h"
#include "instructions_a_t.h"
#include "instructions_b_t.h"
#include "instructions_c_t.h"
#include "instructions_d_t.h"
#include "instructions_e_t.h"
#include "instructions_f_t.h"
#include "instructions_g_t.h"
#include "instructions_h_t.h"
#include "instructions_i_t.h"
#include "instructions_j_t.h"
#include "instructions_l_t.h"
#include "instructions_m_t.h"
#include "instructions_n_t.h"
#include "instructions_o_t.h"
#include "instructions_p_t.h"
#include "instructions_r_t.h"
#include "instructions_s_t.h"
#include "instructions_t_t.h"
#include "instructions_u_t.h"
#include "instructions_v_t.h"
#include "instructions_w_t.h"
#include "instructions_x_t.h"
#include "fcml_intel_parser_t.h"
#include "fcml_dialect_intel.h"
#include "hints_t.h"
#include "fcml_chooser_t.h"
#include "prefixes_t.h"

#include "fcml_assembler.h"
#include "fcml_disassembler.h"

#include "instructions_base_t.h"

CU_SuiteInfo *suites[] = {
	fctl_si_instructions_a,
	fctl_si_instructions_b,
	fctl_si_instructions_c,
	fctl_si_instructions_d,
	fctl_si_instructions_e,
	fctl_si_instructions_f,
	fctl_si_instructions_g,
	fctl_si_instructions_h,
	fctl_si_instructions_i,
	fctl_si_instructions_j,
	fctl_si_instructions_l,
	fctl_si_instructions_m,
	fctl_si_instructions_n,
	fctl_si_instructions_o,
	fctl_si_instructions_p,
	fctl_si_instructions_r,
	fctl_si_instructions_s,
	fctl_si_instructions_t,
	fctl_si_instructions_u,
	fctl_si_instructions_v,
	fctl_si_instructions_w,
	fctl_si_instructions_x,
	fctl_si_modrm_encoder,
    fctl_si_modrm_decoder,
    fctl_si_stream,
    fcml_si_coll,
    fcml_si_utils,
	fcml_si_intel_parser,
	fcml_si_mnemonic_parser,
	fcml_si_hints,
	fcml_si_chooser,
	fcml_si_prefixes,
    NULL
};

#include "fcml_disassembler.h"
#include "fcml_rend.h"

void new_disassembler_test(void) {

	fcml_ceh_error error;

	error = fcml_fn_init_intel_dialect();
	if( error ) {
		return;
	}

	fcml_st_dialect_context dialect = fcml_fn_get_intel_dialect_context();

	fcml_st_dasm_disassembler *disassembler;
	error = fcml_fn_dasm_disassembler_init( &dialect, &disassembler );
	if( error ) {
		// Error.
		return;
	}


	// db 080h, 0D0h, 042h
	// adc    al,42h
	// adc    $0x42,%al

	//0x80, 0x54, 0x01, 0x02, 0x03
	//adc byte ptr [ecx+eax+00000002h],03h
    //adcb   $0x3,0x2(%rcx,%rax,1)

	// adc al,42h

	//fcml_uint8_t code[] = { 0x80, 0x54, 0x01, 0x02, 0x03 };
	// ff5b01 call far fword ptr [ebx+1]

	// FCML_I32( "call far 6655h:44332211h", 0x9A, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66 );
	// 9a112233445566 call far 2211h:66554433h

	//FCML_I3264_M( "adc al,42h", 2, FCML_MI( 0x14, 0x42 ), FCML_MI( 0x80, 0xD0, 0x42 ) );
	// 1442 adc al,42h

	// FCML_I32( "cmps byte ptr [si],byte ptr [di]", 0x67, 0xA6 );
	// 67a6 cmps byte ptr [si],byte ptr [di]

	//FCML_I3264( "bswap esp", 0x0f, 0xcc );
	// 0fcc bswap esp

	// FCML_I3264_M( "int 03h", 2, FCML_MI( 0xCC ), FCML_MI( 0xCD, 0x03 ) );
	// cc int 03h

	// FCML_I32_M( "mov al,byte ptr [40302010h]", 2, FCML_MI( 0xA0, 0x10, 0x20, 0x30, 0x40 ), FCML_MI( 0x8a, 0x05, 0x10, 0x20, 0x30, 0x40 ) );
	// a010203040 mov al,byte ptr [40302010h]

	// FCML_I32( "call 00001044h",  0x66, 0xE8, 0x40, 0x00 );
	// 66e84000 call 00001044h

	// FCML_I32( "call 00401004h", 0xE8, 0xFF, 0xFF, 0xFF, 0xFF );
	// e8ffffffff call 00401004h

	// FCML_I64( "call 0000800000401004h", 0xE8, 0xFF, 0xFF, 0xFF, 0xFF );
	// e8ffffffff call 0000800000401004h

	// FCML_I32( "add edx,esp", 0x01, 0xe2 );
	// 01e2 add edx,esp


	// FCML_I64( "vaddpd ymm10,ymm14,ymmword ptr [r9+r8]", 0xC4, 0x01, 0x0D, 0x58, 0x14, 0x01 );
	// c4010d581401 vaddpd ymm10,ymm14,ymmword ptr [r9d+r8d] (ASA - 32 bity.)

	// FCML_I64( "vblendvpd ymm10,ymm14,ymmword ptr [r9+rax],ymm2", 0xC4, 0x43, 0x0D, 0x4B, 0x14, 0x01, 0x20 );
	// c4430d4b140120 vblendvpd ymm10,ymm14,ymmword ptr [r9d+eax],ymm2

	// FCML_I32( "cmpsd xmm0,mmword ptr [eax+00000020h],07h", 0xF2, 0x0F, 0xC2, 0x40, 0x20, 0x07 );
	// f20fc2402007 cmpsd xmm0,mmword ptr [eax+32],07h

	// FCML_I3264_A( "cmpltsd xmm0,xmm1", 0xf2, 0x0f, 0xc2, 0xc1, 0x01 );
	// f20fc2c101 cmpltsd xmm0,xmm1

	//FCML_I32( "jnc 00000204h", 0x66, 0x0f, 0x83, 0xff, 0xf1 );
	// 660f83fff1 jnc 00000204h

	fcml_uint8_t code[] = {  0x66, 0x81, 0xD5, 0x01, 0x02 };

	fcml_st_dasm_disassembler_context context;
	context.configuration.use_short_form_mnemonics = FCML_FALSE;
	context.disassembler = disassembler;
	context.addr_form = FCML_AF_32_BIT;
	context.address_size_attribute = 0;
	context.operand_size_attribute = 0;
	context.code_address = code;
	context.code_size = sizeof( code );
	context.ip.rip = 0x00401000;

/*	fcml_st_disassembler_context context;
		context.disassembler = disassembler;
		context.addr_form = FCML_AF_64_BIT;
		context.address_size_attribute = FCML_DS_32;
		context.operand_size_attribute = FCML_DS_32;
		context.code_address = code;
		context.code_size = sizeof( code );
		context.ip.rip = 0x0000800000401000LL;*/

	fcml_st_dasm_disassembler_result *result;
	error = fcml_fn_dasm_disassemble( &context, &result );
	if( !error ) {

		fcml_char buffer[256];

		fcml_fn_env_memory_clear( buffer, sizeof( buffer ) );

		fcml_st_memory_stream stream;
		stream.base_address = buffer;
		stream.offset = 0;
		stream.size = sizeof( buffer );

		if( !fcml_fn_rend_render_instruction( &dialect, &stream, result, FCML_REND_FLAG_RENDER_CODE | FCML_REND_FLAG_HEX_IMM | FCML_REND_FLAG_COND_SHOW_CARRY ) ) {
			printf( "%s\n", buffer );
		}

	}

	if( disassembler ) {
		fcml_fn_dasm_disassembler_free( disassembler );
	}

	fcml_fn_intel_dialect_free();

}

int main(int argc, char **argv) {

	fcml_ceh_error error;

	error = fcml_fn_init_intel_dialect();
	if( error ) {
		return 1;
	}

	error = fcml_fn_asm_assembler_init( fcml_fn_get_intel_dialect_context(), &assembler );
	if( error ) {
		printf("Can not initialize assembler.\n");
		return 1;
	}

	dialect = fcml_fn_get_intel_dialect_context();

	error = fcml_fn_dasm_disassembler_init( &dialect, &disassembler );
	if( error ) {
		// Error.
		printf( "Can not allocate disassembler." );
		return 1;
	}

	//FCML_I64_RF( "rcl byte ptr [rel 0000800000401007h],03h", FCML_REND_FLAG_RENDER_REL_HINT, 0xc0, 0x15, 0x00, 0x00, 0x00, 0x00, 0x03 );
	//return 0;

	//FCML_I64_M_P( "mov al,byte ptr [40302010h]", 2, FCML_MI( 0x67, 0xA0, 0x10, 0x20, 0x30, 0x40 ), FCML_MI( 0x67, 0x8a, 0x05, 0x10, 0x20, 0x30, 0x40 ) );

	//return 0;
    //FCML_I64_A_P( "movq mm2,mmword ptr [rax]", 0x0f, 0x6f, 0x10 );
    //return 0;

	//FCML_I32_P( "add dword ptr [eax],eax", 0x01, 0x00 );
	//FCML_I32_A_P( "add dword ptr [eax],eax", 0x01, 0x04, 0x20 );
	//FCML_I32_P( "add dword ptr [eax+00000001h],eax", 0x01, 0x40, 0x01 );
	//FCML_I32_P( "add dword ptr [eax+00000001h],eax", 0x01, 0x44, 0x20, 0x01 );

	//FCML_I32_A_P( "add dword ptr [sib eax+00000001h],eax", 0x01, 0x44, 0x20, 0x01 );
	//FCML_I32_A_P( "add dword ptr [eax+00000001h],eax", 0x01, 0x44, 0x20, 0x01 );
	//FCML_I64_RF( "rcl byte ptr [abs 0000000000401007h],03h", FCML_REND_FLAG_RENDER_ABS_HINT, 0xc0, 0x15, 0x07, 0x10, 0x40, 0x00, 0x03 );
	//return 0;

	// TODO: sprz<awdzic assemblacje prefixow do zmiany rjestrow segmentowych, ten niby nie assembleuje domyslnego ale czy swiadomie?

	///FCML_I32_A_P( "call far fword ptr cs:[ebx+00000001h]", 0x64, 0xFF, 0x5B, 0x01 );
	//return 0;

    if (CU_initialize_registry()) {
        printf("Initialization of Test Registry failed.");
    } else {
        int i;
        for( i = 0; suites[i]; i++ ) {
            if (CU_register_suites(suites[i]) != CUE_SUCCESS) {
                fprintf(stderr, "suite registration failed - %s\n", CU_get_error_msg());
                fcml_fn_dasm_disassembler_free( disassembler );
                fcml_fn_asm_assembler_free( assembler );
                fcml_fn_intel_dialect_free();
                exit(1);
            }
        }
        CU_basic_run_tests();
        CU_cleanup_registry();
    }
    fcml_fn_dasm_disassembler_free( disassembler );
    fcml_fn_asm_assembler_free( assembler );
    fcml_fn_intel_dialect_free();
    exit(0);
}
