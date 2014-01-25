/*
 * main.c
 *
 *  Created on: 04-02-2013
 *      Author: Slawomir Wojtasiak
 */

#include <stdio.h>
#include <stdlib.h>

#include "fcml_stf.h"

/* FCML.*/
#include <fcml_intel_dialect.h>
#include <fcml_gas_dialect.h>
#include <fcml_assembler.h>
#include <fcml_disassembler.h>
#include <fcml_rend.h>

/* Tests.*/
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
#include "hints_t.h"
#include "chooser_t.h"
#include "prefixes_t.h"
#include "segment_reg_t.h"
#include "mnemonic_parser_t.h"
#include "modrm_encoder_t.h"
#include "modrm_decoder_t.h"
#include "stream_t.h"
#include "coll_t.h"
#include "utils_t.h"
#include "intel_parser_t.h"
#include "gas_parser_t.h"

#include "instructions_base_t.h"

fcml_stf_test_suite *fcml_arr_suites[] = {
	&fctl_si_instructions_a,
	&fctl_si_instructions_b,
	&fctl_si_instructions_c,
	&fctl_si_instructions_d,
	&fctl_si_instructions_e,
	&fctl_si_instructions_f,
	&fctl_si_instructions_g,
	&fctl_si_instructions_h,
	&fctl_si_instructions_i,
	&fctl_si_instructions_j,
	&fctl_si_instructions_l,
	&fctl_si_instructions_m,
	&fctl_si_instructions_n,
	&fctl_si_instructions_o,
	&fctl_si_instructions_p,
	&fctl_si_instructions_r,
	&fctl_si_instructions_s,
	&fctl_si_instructions_t,
	&fctl_si_instructions_u,
	&fctl_si_instructions_v,
	&fctl_si_instructions_w,
	&fctl_si_instructions_x,
	&fctl_si_modrm_encoder,
    &fctl_si_modrm_decoder,
    &fctl_si_stream,
    &fcml_si_coll,
    &fcml_si_utils,
	&fcml_si_intel_parser,
	&fcml_si_gas_parser,
	&fcml_si_mnemonic_parser,
	&fcml_si_hints,
	&fcml_si_chooser,
	&fcml_si_prefixes,
	&fcml_si_segment_reg,
	&fcml_si_gas_parser,
	FCML_STF_NULL_SUITE
};

int main(int argc, char **argv) {

	fcml_ceh_error error;

 	error = fcml_fn_intel_dialect_init( FCML_INTEL_DIALECT_CF_DEFAULT, &dialect_intel );
	if( error ) {
		exit(1);
	}

	error = fcml_fn_gas_dialect_init( FCML_GAS_DIALECT_CF_DEFAULT, &dialect_gas );
	if( error ) {
		fcml_fn_intel_dialect_free( dialect_intel );
		exit(1);
	}

	assembler_intel = NULL;
	assembler_gas = NULL;

	error = fcml_fn_assembler_init( dialect_intel, &assembler_intel );
	if( error ) {
		fcml_fn_intel_dialect_free( dialect_intel );
		fcml_fn_gas_dialect_free( dialect_gas );
		printf("Can not initialize INTEL assembler.\n");
		exit(1);
	}

	error = fcml_fn_assembler_init( dialect_gas, &assembler_gas );
	if( error ) {
		fcml_fn_assembler_free( assembler_intel );
		fcml_fn_intel_dialect_free( dialect_intel );
		fcml_fn_gas_dialect_free( dialect_gas );
		printf("Can not initialize AT&T assembler.\n");
		exit(1);
	}

	error = fcml_fn_disassembler_init( dialect_intel, &disassembler_intel );
	if( error ) {
		/* Error.*/
		fcml_fn_assembler_free( assembler_intel );
		fcml_fn_assembler_free( assembler_gas );
		fcml_fn_intel_dialect_free( dialect_intel );
		fcml_fn_gas_dialect_free( dialect_gas );
		printf( "Can not allocate INTEL disassembler.\n" );
		exit(1);
	}

	error = fcml_fn_disassembler_init( dialect_gas, &disassembler_gas );
	if( error ) {
		/* Error.*/
		fcml_fn_disassembler_free( disassembler_intel );
		fcml_fn_assembler_free( assembler_intel );
		fcml_fn_assembler_free( assembler_gas );
		fcml_fn_intel_dialect_free( dialect_intel );
		fcml_fn_gas_dialect_free( dialect_gas );
		printf( "Can not allocate AT&T disassembler.\n" );
		exit(1);
	}

	/* Run tests.*/
	fcml_bool result = fcml_stf_run_tests( fcml_arr_suites );

    fcml_fn_disassembler_free( disassembler_intel );
    fcml_fn_disassembler_free( disassembler_gas );
    fcml_fn_assembler_free( assembler_intel );
    fcml_fn_assembler_free( assembler_gas );
    fcml_fn_intel_dialect_free( dialect_intel );
    fcml_fn_gas_dialect_free( dialect_gas );

    exit( result ? 0 : 1 );
}
