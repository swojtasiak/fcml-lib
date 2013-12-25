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

#include "fcml_dialect_intel.h"
#include "fcml_dialect_att.h"

#include "fcml_assembler.h"
#include "fcml_disassembler.h"

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
#include "fcml_att_parser_t.h"
#include "hints_t.h"
#include "fcml_chooser_t.h"
#include "prefixes_t.h"
#include "segment_reg_t.h"

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
	fcml_si_att_parser,
	fcml_si_mnemonic_parser,
	fcml_si_hints,
	fcml_si_chooser,
	fcml_si_prefixes,
	fcml_si_segment_reg,
	fcml_si_att_parser,
    NULL
};

#include "fcml_disassembler.h"
#include "fcml_rend.h"

int main(int argc, char **argv) {

	fcml_ceh_error error;

	error = fcml_fn_init_intel_dialect();
	if( error ) {
		return 1;
	}

	error = fcml_fn_init_att_dialect();
	if( error ) {
		fcml_fn_intel_dialect_free();
		return 1;
	}

	assembler_intel = NULL;
	assembler_att = NULL;

	error = fcml_fn_asm_assembler_init( fcml_fn_get_intel_dialect_context(), &assembler_intel );
	if( error ) {
		fcml_fn_intel_dialect_free();
		fcml_fn_att_dialect_free();
		printf("Can not initialize INTEL assembler.\n");
		return 1;
	}

	error = fcml_fn_asm_assembler_init( fcml_fn_get_att_dialect_context(), &assembler_att );
	if( error ) {
		fcml_fn_asm_assembler_free( assembler_intel );
		fcml_fn_intel_dialect_free();
		fcml_fn_att_dialect_free();
		printf("Can not initialize AT&T assembler.\n");
		return 1;
	}

	dialect_intel = fcml_fn_get_intel_dialect_context();
	dialect_att = fcml_fn_get_att_dialect_context();

	error = fcml_fn_dasm_disassembler_init( dialect_intel, &disassembler_intel );
	if( error ) {
		// Error.
		fcml_fn_asm_assembler_free( assembler_intel );
		fcml_fn_asm_assembler_free( assembler_att );
		fcml_fn_intel_dialect_free();
		fcml_fn_att_dialect_free();
		printf( "Can not allocate INTEL disassembler.\n" );
		return 1;
	}

	error = fcml_fn_dasm_disassembler_init( dialect_att, &disassembler_att );
	if( error ) {
		// Error.
		fcml_fn_dasm_disassembler_free( disassembler_intel );
		fcml_fn_asm_assembler_free( assembler_intel );
		fcml_fn_asm_assembler_free( assembler_att );
		fcml_fn_intel_dialect_free();
		fcml_fn_att_dialect_free();
		printf( "Can not allocate AT&T disassembler.\n" );
		return 1;
	}


	//FCML_I32_M( "push 11ffh", 2, FCML_MI( 0x66, 0x68, 0xff, 0x11 ), FCML_MI( 0x68, 0xff, 0x11, 0x00, 0x00 ) );

	/*FCML_A64_A_P( "movabs 0x89482010,%al", 0x67, 0xa0, 0x10, 0x20, 0x48, 0x89 );
	FCML_A64_A_P( "mov 0x89482010,%al", 0x67, 0xa0, 0x10, 0x20, 0x48, 0x89 );
	FCML_A32_A_P( "movabs 0x89482010,%al", 0x67, 0xa0, 0x10, 0x20, 0x48, 0x89 );
	FCML_A32_A_P( "mov 0x89482010,%al", 0x67, 0xa0, 0x10, 0x20, 0x48, 0x89 );
	return 0;
*/


	//FCML_A64_M_P( "mov $0x2010,%ax", 2, FCML_MI( 0x66, 0xb8, 0x10, 0x20 ), FCML_MI( 0x66, 0xc7, 0xc0, 0x10, 0x20 ) );


	// ea 11 22 33 44 55 66   ljmp   $0x6655,$0x44332211


	//FCML_I32_A_P( "call dword ptr [00001044h]",  0x66, 0xE8, 0x40, 0x00 );


	//FCML_I32_M_P( "adc al,42h", 2, FCML_MI( 0x14, 0x42 ), FCML_MI( 0x80, 0xD0, 0x42 ) );
	//FCML_A32_M_P( "adc $0x42,%al", 2, FCML_MI( 0x14, 0x42 ), FCML_MI( 0x80, 0xD0, 0x42 ) );
	//return 0;

	//FCML_A32_A_P( "jmp *0x90d11004", 0xff, 0x25, 0x04, 0x10, 0xd1, 0x90 );

	//FCML_A32_A_P( "jmp (%eax)", 0xff, 0x20 );

	//FCML_A32_M_A( "jmp (%eax)", 2, FCML_MI( 0xff, 0x20 ), FCML_MI( 0x66, 0xff, 0x28 ) );
	//return 0;

    //FCML_I32_A_P( "push 0ffffffffh", 3, FCML_MI( 0x68, 0xff, 0xff, 0xff, 0xff ), FCML_MI( 0x66, 0x68, 0xff, 0xff ), FCML_MI( 0x6a, 0xff ) );

    //FCML_A64_P( "vpsrlw (%rax),%xmm0,%xmm0", 0xc4, 0xe1, 0x79, 0xd1, 0x00 );
    //return 0;


    if (CU_initialize_registry()) {
        printf("Initialization of Test Registry failed.\n");
    } else {
        int i;
        for( i = 0; suites[i]; i++ ) {
            if (CU_register_suites(suites[i]) != CUE_SUCCESS) {
                fprintf(stderr, "suite registration failed - %s\n", CU_get_error_msg());
                fcml_fn_dasm_disassembler_free( disassembler_intel );
                fcml_fn_dasm_disassembler_free( disassembler_att );
                fcml_fn_asm_assembler_free( assembler_intel );
                fcml_fn_asm_assembler_free( assembler_att );
                fcml_fn_intel_dialect_free();
				fcml_fn_att_dialect_free();
                exit(1);
            }
        }
        CU_basic_run_tests();
        CU_cleanup_registry();
    }
    fcml_fn_dasm_disassembler_free( disassembler_intel );
    fcml_fn_dasm_disassembler_free( disassembler_att );
    fcml_fn_asm_assembler_free( assembler_intel );
    fcml_fn_asm_assembler_free( assembler_att );
    fcml_fn_intel_dialect_free();
    fcml_fn_att_dialect_free();
    exit(0);
}
