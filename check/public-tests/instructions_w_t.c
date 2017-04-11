/*
 * FCML - Free Code Manipulation Library.
 * Copyright (C) 2010-2014 Slawomir Wojtasiak
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

#include <fcml_assembler.h>
#include "instructions_w_t.h"
#include "instructions_base_t.h"

fcml_bool fcml_tf_instructions_w_suite_init(void) {
	return FCML_TRUE;
}

fcml_bool fcml_tf_instructions_w_suite_cleanup(void) {
	return FCML_TRUE;
}

void fcml_tf_instruction_WAIT(void) {

    FCML_I3264( "wait", 0x9B );

    FCML_A64( "wait", 0x9b );
    FCML_A64_A( "fwait", 0x9b );
}

void fcml_tf_instruction_WBINVD(void) {

    FCML_I3264( "wbinvd", 0x0F, 0x09 );

    FCML_A3264( "wbinvd", 0x0f, 0x09 );
}

void fcml_tf_instruction_WRFSBASE(void) {

    FCML_I64( "wrfsbase eax", 0xF3, 0x0F, 0xAE, 0xD0 );
    FCML_I64( "wrfsbase eax", 0x66, 0xF3, 0x0F, 0xAE, 0xD0 );
    FCML_I64( "wrfsbase rax", 0xF3, 0x48, 0x0F, 0xAE, 0xD0 );

    FCML_I64( "wrgsbase eax", 0xF3, 0x0F, 0xAE, 0xD8 );
    FCML_I64( "wrgsbase eax", 0x66, 0xF3, 0x0F, 0xAE, 0xD8 );
    FCML_I64( "wrgsbase rax", 0xF3, 0x48, 0x0F, 0xAE, 0xD8 );

    FCML_A64( "wrfsbase %eax", 0xf3, 0x0f, 0xae, 0xd0 );
    FCML_A64( "wrfsbase %rax", 0xf3, 0x48, 0x0f, 0xae, 0xd0 );
    FCML_A64( "wrgsbase %eax", 0xf3, 0x0f, 0xae, 0xd8 );
    FCML_A64( "wrgsbase %rax", 0xf3, 0x48, 0x0f, 0xae, 0xd8 );
}

void fcml_tf_instruction_WRMSR(void) {

    FCML_I32( "wrmsr", 0x0F, 0x30 );
    FCML_I64( "wrmsr", 0x0F, 0x30 );

    FCML_A64( "wrmsr", 0x0f, 0x30 );
    FCML_A64( "wrmsr", 0x0f, 0x30 );
}

fcml_stf_test_case fctl_ti_instructions_w[] = {
	{ "fcml_tf_instruction_WAIT", fcml_tf_instruction_WAIT },
	{ "fcml_tf_instruction_WBINVD", fcml_tf_instruction_WBINVD },
	{ "fcml_tf_instruction_WRFSBASE", fcml_tf_instruction_WRFSBASE },
	{ "fcml_tf_instruction_WRMSR", fcml_tf_instruction_WRMSR },
	FCML_STF_NULL_TEST
};

fcml_stf_test_suite fctl_si_instructions_w = {
	"suite-fctl_ti_instructions_w", fcml_tf_instructions_w_suite_init, fcml_tf_instructions_w_suite_cleanup, fctl_ti_instructions_w
};

