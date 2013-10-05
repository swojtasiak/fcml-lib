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
#include "instructions_x_t.h"
#include "instructions_u_t.h"
#include "fcml_intel_parser_t.h"
#include "fcml_asm_dialect_intel.h"

#include "fcml_assembler.h"
#include "ira.h"

#include "instructions_base_t.h"

CU_SuiteInfo *suites[] = {
	fctl_si_instructions_a,
	fctl_si_instructions_b,
	fctl_si_instructions_c,
	fctl_si_instructions_d,
	fctl_si_instructions_e,
	fctl_si_instructions_f,
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
	fctl_si_instructions_x,
	fctl_si_instructions_u,
	fctl_si_modrm_encoder,
    fctl_si_modrm_decoder,
    fctl_si_stream,
    fcml_si_coll,
    fcml_si_utils,
	fcml_si_intel_parser,
	fcml_si_mnemonic_parser,
    NULL
};

int main(int argc, char **argv) {

	fcml_ceh_error error = fcml_fn_asm_init( fcml_fn_get_intel_dialect_context(), &assembler );
	if( error ) {
		printf("Can not initialize assembler.\n");
		return 1;
	}
	ira_init();

	// , FCML_MI( 0xd0, 0x10 )


	//return 0;
	//  FCML_I64_P( "cmps byte ptr [rsi],byte ptr [rdi]", 0x48, 0xA6 );
  //  return 0;

    if (CU_initialize_registry()) {
        printf("Initialization of Test Registry failed.");
    } else {
        int i;
        for( i = 0; suites[i]; i++ ) {
            if (CU_register_suites(suites[i]) != CUE_SUCCESS) {
                fprintf(stderr, "suite registration failed - %s\n", CU_get_error_msg());
                ira_deinit();
                fcml_fn_asm_free( assembler );
                exit(1);
            }
        }
        CU_basic_run_tests();
        CU_cleanup_registry();
    }
    fcml_fn_asm_free( assembler );
    ira_deinit();
    exit(0);
}
