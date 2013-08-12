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

#include "modrm_encoder_t.h"
#include "modrm_decoder_t.h"
#include "stream_t.h"
#include "fcml_coll_t.h"
#include "fcml_utils_t.h"
#include "instructions_a_t.h"
#include "fcml_intel_parser_t.h"

#include "fcml_assembler.h"
#include "ira.h"

#include "instructions_base_t.h"

CU_SuiteInfo *suites[] = {
	fctl_si_instructions_a,
	fctl_si_modrm_encoder,
    fctl_si_modrm_decoder,
    fctl_si_stream,
    fcml_si_coll,
    fcml_si_utils,
	fcml_si_intel_parser,
    NULL
};

int main(int argc, char **argv) {
	ira_init();

	fcml_ceh_error error = fcml_fn_asm_init();
	if( error ) {
		printf("Can not initialize assembler.\n");
		return 1;
	}

	FCML_I32_P( "andn eax,edi,dword ptr [eax]", 0xC4, 0xE2, 0x40, 0xF2, 0x00 );
	//FCML_I32_P( "andn eax,edi,eax", 0xC4, 0xE2, 0x40, 0xF2, 0xC0 );
	//FCML_I32_P( "andn rax,rdi,qword ptr [eax]", 0xC4, 0xE2, 0xC0, 0xF2, 0x00 );
	//FCML_I32_P( "andn rax,rdi,rax", 0xC4, 0xE2, 0xC0, 0xF2, 0xC0 );

	return 0;

	//FCML_I32_P( "arpl word ptr [ecx+eax],dx", 0x66, 0x63, 0x14, 0x01 );
	//FCML_I32_P( "arpl word ptr [si],dx", 0x67, 0x63, 0x14 );
	//return 0;

	//FCML_I32_P( "vandnps xmm2,xmm7,oword ptr [ecx+eax]", 0xC4, 0xC1, 0x40, 0x55, 0x14, 0x01 );
	//FCML_I32_P( "vandnps xmm2,xmm2,oword ptr [ecx+eax]", 0xC4, 0xC1, 0x68, 0x55, 0x14, 0x01 );

	//FCML_I32_P( "vandnpd xmm2,xmm7,oword ptr [ecx+eax]", 0xC4, 0xC1, 0x41, 0x55, 0x14, 0x01 );
	//FCML_I32_P( "vandnpd xmm2,xmm2,oword ptr [ecx+eax]", 0xC4, 0xC1, 0x69, 0x55, 0x14, 0x01 );


	//return 0;

    if (CU_initialize_registry()) {
        printf("Initialization of Test Registry failed.");
    } else {
        int i;
        for( i = 0; suites[i]; i++ ) {
            if (CU_register_suites(suites[i]) != CUE_SUCCESS) {
                fprintf(stderr, "suite registration failed - %s\n", CU_get_error_msg());
                ira_deinit();
                fcml_fn_asm_free();
                exit(1);
            }
        }
        CU_basic_run_tests();
        CU_cleanup_registry();
    }
    ira_deinit();
    fcml_fn_asm_free();
    exit(0);
}
