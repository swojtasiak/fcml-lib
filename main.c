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

	FCML_I64_P( "adc rbp,0ffffffffffffffffh", 0x48, 0x81, 0xD5, 0xff, 0xff, 0xff, 0xff );

	//FCML_I32_P( "adc word ptr [0201h],0ffffh", 0x66, 0x67, 0x83, 0x16, 0x01, 0x02, 0xFF );

	//FCML_I32_P( "adc dword ptr [0201h],00000003h", 0x67, 0x83, 0x16, 0x01, 0x02, 0x03 );

	//FCML_I64_RIP_P( "adc dword ptr [0000800000401007h],00000003h", 0x83, 0x15, 0x00, 0x00, 0x00, 0x00, 0x03 );

	//FCML_I64_P( "adc word ptr [0x12FF88FF88FF88],0001h", 0x66, 0x83, 0x16, 0x01 );

	///FCML_I64_P( "adc ebp,04030201h", 0x81, 0xD5, 0x01, 0x02, 0x03, 0x04 );

	//FCML_I32_P( "adc byte ptr [04030201h],0ffh", 0x80, 0x15, 0x01, 0x02, 0x03, 0x04, 0xff );

//	FCML_I64_P( "adc eax,42806521h", 0x15, 0x21, 0x65, 0x80, 0x42 );
	//FCML_I64_P( "adc rax,0000000042806521h", 0x48, 0x15, 0x21, 0x65, 0x80, 0x42 );

	return 0;

//	return 0;

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
