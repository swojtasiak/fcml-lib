/*
 * instructions.c
 *
 *  Created on: 01-06-2013
 *      Author: tAs
 */

#include <fcml_env.h>
#include <fcml_assembler.h>
#include "instructions_w_t.h"
#include "instructions_base_t.h"

void fcml_tf_instructions_w_suite_init(void) {
}

void fcml_tf_instructions_w_suite_cleanup(void) {
}

void fcml_tf_instruction_WAIT(void) {
    // 9B WAIT NP Valid Valid Check pending unmasked floating-point exceptions.
    // 9B FWAIT NP Valid Valid Check pending unmasked floating-point exceptions.
    FCML_I3264( "wait", 0x9B );
    // GAS
    FCML_A64( "wait", 0x9b );
    FCML_A64_A( "fwait", 0x9b );
}

void fcml_tf_instruction_WBINVD(void) {
    // 0F 09 WBINVD NP Valid Valid Write back and flush Internal caches; initiate writing-back and flushing of external caches.
    FCML_I3264( "wbinvd", 0x0F, 0x09 );
    // GAS
    FCML_A3264( "wbinvd", 0x0f, 0x09 );
}

void fcml_tf_instruction_WRFSBASE(void) {
    // F3 0F AE /2 WRFSBASE r32 M V/I FSGSBASE Load the FS base address with the 32-bit value in the source register.
    // REX.W + F3 0F AE /2 WRFSBASE r64 M V/I FSGSBASE Load the FS base address with the 64-bit value in the source register.
    FCML_I64( "wrfsbase eax", 0xF3, 0x0F, 0xAE, 0xD0 );
    FCML_I64( "wrfsbase eax", 0x66, 0xF3, 0x0F, 0xAE, 0xD0 );
    FCML_I64( "wrfsbase rax", 0xF3, 0x48, 0x0F, 0xAE, 0xD0 );
    // F3 0F AE /3 WRGSBASE r32 M V/I FSGSBASE Load the GS base address with the 32-bit value in the source register.
    // REX.W + F3 0F AE /3 WRGSBASE r64 M V/I FSGSBASE Load the GS base address with the 64-bit value in the source register.
    FCML_I64( "wrgsbase eax", 0xF3, 0x0F, 0xAE, 0xD8 );
    FCML_I64( "wrgsbase eax", 0x66, 0xF3, 0x0F, 0xAE, 0xD8 );
    FCML_I64( "wrgsbase rax", 0xF3, 0x48, 0x0F, 0xAE, 0xD8 );
    // GAS
    FCML_A64( "wrfsbase %eax", 0xf3, 0x0f, 0xae, 0xd0 );
    FCML_A64( "wrfsbase %rax", 0xf3, 0x48, 0x0f, 0xae, 0xd0 );
    FCML_A64( "wrgsbase %eax", 0xf3, 0x0f, 0xae, 0xd8 );
    FCML_A64( "wrgsbase %rax", 0xf3, 0x48, 0x0f, 0xae, 0xd8 );
}

void fcml_tf_instruction_WRMSR(void) {
    // 0F 30 WRMSR NP Valid Valid Write the value in EDX:EAX to MSR specified by ECX.
    FCML_I32( "wrmsr", 0x0F, 0x30 );
    FCML_I64( "wrmsr", 0x0F, 0x30 );
    // GAS
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

