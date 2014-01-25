/*
 * instructions.c
 *
 *  Created on: 01-06-2013
 *      Author: tAs
 */

#include <fcml_env.h>
#include <fcml_assembler.h>
#include "instructions_n_t.h"
#include "instructions_base_t.h"

void fcml_tf_instructions_n_suite_init(void) {
}

void fcml_tf_instructions_n_suite_cleanup(void) {
}

void fcml_tf_instruction_NEG(void) {
    /* F6 /3 NEG r/m8 M Valid Valid Two's complement negate r/m8.*/
    /* REX + F6 /3 NEG r/m8* M Valid N.E. Two's complement negate r/m8.*/
    FCML_I32( "lock neg byte ptr [eax]", 0xF0, 0xF6, 0x18 );
    FCML_I32( "xacquire lock neg byte ptr [eax]", 0xF2, 0xF0, 0xF6, 0x18 );
    FCML_I32( "xrelease lock neg byte ptr [eax]", 0xF3, 0xF0, 0xF6, 0x18 );
    FCML_I64_D( "neg byte ptr [rax]", 0x48, 0xF6, 0x18);
    FCML_I64( "neg byte ptr [rax]", 0xF6, 0x18);
    /* F7 /3 NEG r/m16 M Valid Valid Two's complement negate r/m16.*/
    /* F7 /3 NEG r/m32 M Valid Valid Two's complement negate r/m32.*/
    /* REX.W + F7 /3 NEG r/m64 M Valid N.E. Two's complement negate r/m64.*/
    FCML_I32( "lock neg word ptr [eax]", 0xF0, 0x66, 0xF7, 0x18 );
    FCML_I32( "xacquire lock neg word ptr [eax]", 0xF2, 0xF0, 0x66, 0xF7, 0x18 );
    FCML_I32( "xrelease lock neg word ptr [eax]", 0xF3, 0xF0, 0x66, 0xF7, 0x18 );
    FCML_I32( "neg dword ptr [eax]", 0xF7, 0x18 );
    FCML_I64( "neg qword ptr [rax]", 0x48, 0xF7, 0x18 );
    /* GAS*/
    FCML_A64( "lock negb (%rax)", 0xf0, 0xf6, 0x18 );
    FCML_A64( "xacquire lock negb (%rax)", 0xf2, 0xf0, 0xf6, 0x18 );
    FCML_A64( "lock negw (%rax)", 0xf0, 0x66, 0xf7, 0x18 );
    FCML_A64( "negl (%rax)", 0xf7, 0x18 );
    FCML_A64( "negq (%rax)", 0x48, 0xf7, 0x18 );
}

void fcml_tf_instruction_NOP(void) {
    /* 90 NOP NP Valid Valid One byte no-operation instruction.*/
    FCML_I32( "nop", 0x90 );
    FCML_I64( "nop", 0x90 );
    /* 0F 1F /0 NOP r/m16 M Valid Valid Multi-byte no-operation instruction.*/
    /* 0F 1F /0 NOP r/m32 M Valid Valid Multi-byte no-operation instruction.*/
    FCML_I32( "nop word ptr [eax]", 0x66, 0x0f, 0x1f, 0x00 );
    FCML_I32( "nop dword ptr [eax]", 0x0f, 0x1f, 0x00 );
    FCML_I64( "nop qword ptr [rax]", 0x48, 0x0f, 0x1f, 0x00 );
    /* GAS*/
    FCML_A64( "nop", 0x90 );
    FCML_A64( "nopw (%rax)", 0x66, 0x0f, 0x1f, 0x00 );
    FCML_A64( "nopl (%rax)", 0x0f, 0x1f, 0x00 );
    FCML_A64( "nop %eax", 0x0f, 0x1f, 0xc0 );
    FCML_A64( "nopq (%rax)", 0x48, 0x0f, 0x1f, 0x00 );
    FCML_A64( "add %cl,(%rdi)", 0x00, 0x0f );
}

void fcml_tf_instruction_NOT(void) {
    /* F6 /2 NOT r/m8 M Valid Valid Reverse each bit of r/m8.*/
    /* REX + F6 /2 NOT r/m8* M Valid N.E. Reverse each bit of r/m8.*/
    FCML_I32( "lock not byte ptr [eax]", 0xF0, 0xF6, 0x10 );
    FCML_I32( "xacquire lock not byte ptr [eax]", 0xF2, 0xF0, 0xF6, 0x10 );
    FCML_I32( "xrelease lock not byte ptr [eax]", 0xF3, 0xF0, 0xF6, 0x10 );
    FCML_I64_D( "not byte ptr [rax]", 0x48, 0xF6, 0x10 );
    FCML_I64( "not byte ptr [rax]", 0xF6, 0x10 );
    /* F7 /2 NOT r/m16 M Valid Valid Reverse each bit of r/m16.*/
    /* F7 /2 NOT r/m32 M Valid Valid Reverse each bit of r/m32.*/
    /* REX.W + F7 /2 NOT r/m64 M Valid N.E. Reverse each bit of r/m64.*/
    FCML_I32( "lock not word ptr [eax]", 0xF0, 0x66, 0xF7, 0x10 );
    FCML_I32( "xacquire lock not word ptr [eax]", 0xF2, 0xF0, 0x66, 0xF7, 0x10 );
    FCML_I32( "xrelease lock not word ptr [eax]", 0xF3, 0xF0, 0x66, 0xF7, 0x10 );
    FCML_I32( "not dword ptr [eax]", 0xF7, 0x10 );
    FCML_I64( "not qword ptr [rax]", 0x48, 0xF7, 0x10 );
    /* GAS*/
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

