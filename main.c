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

#include "modrm_decoder_t.h"
#include "stream_t.h"

CU_SuiteInfo *suites[] = {
    fctl_si_modrm_decoder,
    fctl_si_stream,
    NULL
};

int main(int argc, char **argv) {

    if (CU_initialize_registry()) {
        printf("Initialization of Test Registry failed.");
    } else {
        int i;
        for( i = 0; suites[i]; i++ ) {
            if (CU_register_suites(suites[i]) != CUE_SUCCESS) {
                fprintf(stderr, "suite registration failed - %s\n", CU_get_error_msg());
                exit(1);
            }
        }
        CU_basic_run_tests();
        CU_cleanup_registry();
    }

    exit(0);
}
