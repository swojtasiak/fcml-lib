/*
 * FCML - Free Code Manipulation Library.
 * Copyright (C) 2010-2015 Slawomir Wojtasiak
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
#include "instructions_n_t.h"
#include "instructions_base_t.h"

fcml_bool fcml_tf_instructions_n_suite_init(void) {
	return FCML_TRUE;
}

fcml_bool fcml_tf_instructions_n_suite_cleanup(void) {
	return FCML_TRUE;
}

void fcml_tf_instruction_NEG(void) {

    FCML_I32( "lock neg byte ptr [eax]", 0xF0, 0xF6, 0x18 );
    FCML_I32( "xacquire lock neg byte ptr [eax]", 0xF2, 0xF0, 0xF6, 0x18 );
    FCML_I32( "xrelease lock neg byte ptr [eax]", 0xF3, 0xF0, 0xF6, 0x18 );
    FCML_I64_D( "neg byte ptr [rax]", 0x48, 0xF6, 0x18);
    FCML_I64( "neg byte ptr [rax]", 0xF6, 0x18);

    FCML_I32( "lock neg word ptr [eax]", 0xF0, 0x66, 0xF7, 0x18 );
    FCML_I32( "xacquire lock neg word ptr [eax]", 0xF2, 0xF0, 0x66, 0xF7, 0x18 );
    FCML_I32( "xrelease lock neg word ptr [eax]", 0xF3, 0xF0, 0x66, 0xF7, 0x18 );
    FCML_I32( "neg dword ptr [eax]", 0xF7, 0x18 );
    FCML_I64( "neg qword ptr [rax]", 0x48, 0xF7, 0x18 );

    FCML_A64( "lock negb (%rax)", 0xf0, 0xf6, 0x18 );
    FCML_A64( "xacquire lock negb (%rax)", 0xf2, 0xf0, 0xf6, 0x18 );
    FCML_A64( "lock negw (%rax)", 0xf0, 0x66, 0xf7, 0x18 );
    FCML_A64( "negl (%rax)", 0xf7, 0x18 );
    FCML_A64( "negq (%rax)", 0x48, 0xf7, 0x18 );
}

void fcml_tf_instruction_NOP(void) {

    FCML_I32( "nop", 0x90 );
    FCML_I64( "nop", 0x90 );

    FCML_I32( "nop word ptr [eax]", 0x66, 0x0f, 0x1f, 0x00 );
    FCML_I32( "nop dword ptr [eax]", 0x0f, 0x1f, 0x00 );
    FCML_I64( "nop qword ptr [rax]", 0x48, 0x0f, 0x1f, 0x00 );

    FCML_A64( "nop", 0x90 );
    FCML_A64( "nopw (%rax)", 0x66, 0x0f, 0x1f, 0x00 );
    FCML_A64( "nopl (%rax)", 0x0f, 0x1f, 0x00 );
    FCML_A64( "nop %eax", 0x0f, 0x1f, 0xc0 );
    FCML_A64( "nopq (%rax)", 0x48, 0x0f, 0x1f, 0x00 );
    FCML_A64( "add %cl,(%rdi)", 0x00, 0x0f );
}

void fcml_tf_instruction_NOT(void) {

    FCML_I32( "lock not byte ptr [eax]", 0xF0, 0xF6, 0x10 );
    FCML_I32( "xacquire lock not byte ptr [eax]", 0xF2, 0xF0, 0xF6, 0x10 );
    FCML_I32( "xrelease lock not byte ptr [eax]", 0xF3, 0xF0, 0xF6, 0x10 );
    FCML_I64_D( "not byte ptr [rax]", 0x48, 0xF6, 0x10 );
    FCML_I64( "not byte ptr [rax]", 0xF6, 0x10 );

    FCML_I32( "lock not word ptr [eax]", 0xF0, 0x66, 0xF7, 0x10 );
    FCML_I32( "xacquire lock not word ptr [eax]", 0xF2, 0xF0, 0x66, 0xF7, 0x10 );
    FCML_I32( "xrelease lock not word ptr [eax]", 0xF3, 0xF0, 0x66, 0xF7, 0x10 );
    FCML_I32( "not dword ptr [eax]", 0xF7, 0x10 );
    FCML_I64( "not qword ptr [rax]", 0x48, 0xF7, 0x10 );

    FCML_A64( "lock notb (%rax)", 0xf0, 0xf6, 0x10 );
    FCML_A64( "notb (%rax)", 0xf6, 0x10 );
    FCML_A64( "lock notw (%rax)", 0xf0, 0x66, 0xf7, 0x10 );
    FCML_A64( "xacquire lock notw (%rax)", 0xf2, 0xf0, 0x66, 0xf7, 0x10 );
    FCML_A64( "notl (%rax)", 0xf7, 0x10 );
    FCML_A64( "notq (%rax)", 0x48, 0xf7, 0x10 );
    FCML_A64( "not %eax", 0xf7, 0xd0 );
    FCML_A64_A( "notl %eax", 0xf7, 0xd0 );
}

fcml_stf_test_case fctl_ti_instructions_n[] = {
	{ "fcml_tf_instruction_NEG", fcml_tf_instruction_NEG },
	{ "fcml_tf_instruction_NOP", fcml_tf_instruction_NOP },
	{ "fcml_tf_instruction_NOT", fcml_tf_instruction_NOT },
	FCML_STF_NULL_TEST
};

fcml_stf_test_suite fctl_si_instructions_n = {
	"suite-fctl_ti_instructions_n", fcml_tf_instructions_n_suite_init, fcml_tf_instructions_n_suite_cleanup, fctl_ti_instructions_n
};

