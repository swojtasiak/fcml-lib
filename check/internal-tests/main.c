/*
 * FCML - Free Code Manipulation Library.
 * Copyright (C) 2010-2021 Slawomir Wojtasiak
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
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
#include "env_t.h"
#include "ceh_t.h"
#include "common_utils_t.h"
#include "symbols_t.h"

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
    &fcml_si_env,
    &fcml_si_ceh,
    &fcml_si_common_utils,
    &fctl_si_symbols,
    FCML_STF_NULL_SUITE
};

int main(int argc, char **argv) {

    /* Run tests.*/
    fcml_bool result = fcml_stf_run_tests( FCML_TEXT( "Internal unit tests" ),
            fcml_arr_suites );

    exit( result ? 0 : 1 );
}
