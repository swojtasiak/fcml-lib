/*
 * main.c
 *
 *  Created on: 04-02-2013
 *      Author: Slawomir Wojtasiak
 */

#include <stdio.h>
#include <stdlib.h>

#include <fcml_stf.h>

/* Tests.*/
#include "modrm_encoder_t.h"
#include "modrm_decoder_t.h"
#include "stream_t.h"
#include "coll_t.h"
#include "utils_t.h"
#include "intel_parser_t.h"
#include "gas_parser_t.h"
#include "mnemonic_parser_t.h"
#include "lag_assembler_t.h"

fcml_stf_test_suite *fcml_arr_suites[] = {
	&fctl_si_modrm_encoder,
    &fctl_si_modrm_decoder,
    &fctl_si_stream,
    &fcml_si_coll,
    &fcml_si_utils,
	&fcml_si_intel_parser,
	&fcml_si_gas_parser,
	&fcml_si_mnemonic_parser,
	&fcml_si_lag_assembler,
	FCML_STF_NULL_SUITE
};

int main(int argc, char **argv) {

	/* Run tests.*/
	fcml_bool result = fcml_stf_run_tests( "Internal unit tests", fcml_arr_suites );

	exit( result ? 0 : 1 );
}
