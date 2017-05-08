/*
 * FCML - Free Code Manipulation Library.
 * Copyright (C) 2010-2017 Slawomir Wojtasiak
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
#include "instructions_k_t.h"
#include "instructions_base_t.h"

fcml_bool fcml_tf_instructions_k_suite_init(void) {
    return FCML_TRUE;
}

fcml_bool fcml_tf_instructions_k_suite_cleanup(void) {
    return FCML_TRUE;
}

void fcml_tf_instruction_KADDW(void) {
    FCML_I3264( "kaddw k1,k2,k3", 0xC5, 0xEC, 0x4A, 0xCB );
    FCML_A3264( "kaddw %k3,%k2,%k1", 0xC5, 0xEC, 0x4A, 0xCB );
    FCML_I3264( "kaddw k7,k7,k7", 0xC5, 0xC4, 0x4A, 0xFF );
    FCML_I64_A_FAILED( "kaddw k7,k7,qword [rax]", 0xC5, 0xC4, 0x4A, 0x38 );
}

void fcml_tf_instruction_KADDB(void) {
    FCML_I3264( "kaddb k1,k2,k3", 0xC5, 0xED, 0x4A, 0xCB );
    FCML_A3264( "kaddb %k3,%k2,%k1", 0xC5, 0xED, 0x4A, 0xCB );
}

void fcml_tf_instruction_KADDD(void) {
    FCML_I3264( "kaddd k1,k2,k3", 0xC4, 0xE1, 0xED, 0x4A, 0xCB );
    FCML_A3264( "kaddd %k3,%k2,%k1", 0xC4, 0xE1, 0xED, 0x4A, 0xCB );
}

void fcml_tf_instruction_KADDQ(void) {
    FCML_I3264( "kaddq k1,k2,k3", 0xC4, 0xE1, 0xEC, 0x4A, 0xCB );
    FCML_A3264( "kaddq %k3,%k2,%k1", 0xC4, 0xE1, 0xEC, 0x4A, 0xCB );
}

void fcml_tf_instruction_KANDW(void) {
    FCML_I3264( "kandw k1,k2,k3", 0xC5, 0xEC, 0x41, 0xCB );
    FCML_A3264( "kandw %k3,%k2,%k1", 0xC5, 0xEC, 0x41, 0xCB );
}

void fcml_tf_instruction_KANDB(void) {
    FCML_I3264( "kandb k1,k2,k3", 0xC5, 0xED, 0x41, 0xCB );
    FCML_A3264( "kandb %k3,%k2,%k1", 0xC5, 0xED, 0x41, 0xCB );
}

void fcml_tf_instruction_KANDD(void) {
    FCML_I3264( "kandd k1,k2,k3", 0xC4, 0xE1, 0xED, 0x41, 0xCB );
    FCML_A3264( "kandd %k3,%k2,%k1", 0xC4, 0xE1, 0xED, 0x41, 0xCB );
}

void fcml_tf_instruction_KANDQ(void) {
    FCML_I3264( "kandq k1,k2,k3", 0xC4, 0xE1, 0xEC, 0x41, 0xCB );
    FCML_A3264( "kandq %k3,%k2,%k1", 0xC4, 0xE1, 0xEC, 0x41, 0xCB );
}

void fcml_tf_instruction_KANDNW(void) {
    FCML_I3264( "kandnw k1,k2,k3", 0xC5, 0xEC, 0x42, 0xCB );
    FCML_A3264( "kandnw %k3,%k2,%k1", 0xC5, 0xEC, 0x42, 0xCB );
}

void fcml_tf_instruction_KANDNB(void) {
    FCML_I3264( "kandnb k1,k2,k3", 0xC5, 0xED, 0x42, 0xCB );
    FCML_A3264( "kandnb %k3,%k2,%k1", 0xC5, 0xED, 0x42, 0xCB );
}

void fcml_tf_instruction_KANDND(void) {
    FCML_I3264( "kandnd k1,k2,k3", 0xC4, 0xE1, 0xED, 0x42, 0xCB );
    FCML_A3264( "kandnd %k3,%k2,%k1", 0xC4, 0xE1, 0xED, 0x42, 0xCB );
}

void fcml_tf_instruction_KANDNQ(void) {
    FCML_I3264( "kandnq k1,k2,k3", 0xC4, 0xE1, 0xEC, 0x42, 0xCB );
    FCML_A3264( "kandnq %k3,%k2,%k1", 0xC4, 0xE1, 0xEC, 0x42, 0xCB );
}

void fcml_tf_instruction_KMOVB(void) {
    FCML_I32( "kmovb k1,byte ptr [eax]", 0xC5, 0xF9, 0x90, 0x08 );
    FCML_I64( "kmovb k1,byte ptr [rax]", 0xC5, 0xF9, 0x90, 0x08 );
    FCML_I64( "kmovb k1,k2", 0xC5, 0xF9, 0x90, 0xCA );
    FCML_I32_A( "kmovb k1,[eax]", 0xC5, 0xF9, 0x90, 0x08 );

    FCML_I32( "kmovb byte ptr [eax],k1", 0xC5, 0xF9, 0x91, 0x08 );
    FCML_I64( "kmovb byte ptr [rax],k1", 0xC5, 0xF9, 0x91, 0x08 );

    FCML_I3264( "kmovb k2,eax", 0xC5, 0xF9, 0x92, 0xD0 );
    FCML_I3264( "kmovb eax,k2", 0xC5, 0xF9, 0x93, 0xC2 );
}

void fcml_tf_instruction_KMOVW(void) {
    FCML_I32( "kmovw k1,word ptr [eax]", 0xC5, 0xF8, 0x90, 0x08 );
    FCML_I64( "kmovw k1,word ptr [rax]", 0xC5, 0xF8, 0x90, 0x08 );
    FCML_I64( "kmovw k1,k2", 0xC5, 0xF8, 0x90, 0xCA );
    FCML_I32_A( "kmovw k1,[eax]", 0xC5, 0xF8, 0x90, 0x08 );

    FCML_I32( "kmovw word ptr [eax],k1", 0xC5, 0xF8, 0x91, 0x08 );
    FCML_I64( "kmovw word ptr [rax],k1", 0xC5, 0xF8, 0x91, 0x08 );

    FCML_I3264( "kmovw k2,eax", 0xC5, 0xF8, 0x92, 0xD0 );
    FCML_I3264( "kmovw eax,k2", 0xC5, 0xF8, 0x93, 0xC2 );
}

void fcml_tf_instruction_KMOVD(void) {
    FCML_I32( "kmovd k1,dword ptr [eax]", 0xC4, 0xE1, 0xF9, 0x90, 0x08 );
    FCML_I64( "kmovd k1,dword ptr [rax]", 0xC4, 0xE1, 0xF9, 0x90, 0x08 );
    FCML_I64( "kmovd k1,k2", 0xC4, 0xE1, 0xF9, 0x90, 0xCA );
    FCML_I32_A( "kmovd k1,[eax]", 0xC4, 0xE1, 0xF9, 0x90, 0x08 );

    FCML_I32( "kmovd dword ptr [eax],k1", 0xC4, 0xE1, 0xF9, 0x91, 0x08 );
    FCML_I64( "kmovd dword ptr [rax],k1", 0xC4, 0xE1, 0xF9, 0x91, 0x08 );

    FCML_I3264( "kmovd k2,eax", 0xC5, 0xFB, 0x92, 0xD0 );
    FCML_I3264( "kmovd eax,k2", 0xC5, 0xFB, 0x93, 0xc2 );
}

void fcml_tf_instruction_KMOVQ(void) {
    FCML_I32( "kmovq k1,qword ptr [eax]", 0xC4, 0xE1, 0xF8, 0x90, 0x08 );
    FCML_I64( "kmovq k1,qword ptr [rax]", 0xC4, 0xE1, 0xF8, 0x90, 0x08 );
    FCML_I64( "kmovq k1,k2", 0xC4, 0xE1, 0xF8, 0x90, 0xCA );
    FCML_I32_A( "kmovq k1,[eax]", 0xC4, 0xE1, 0xF8, 0x90, 0x08 );

    FCML_I32( "kmovq qword ptr [eax],k1", 0xC4, 0xE1, 0xF8, 0x91, 0x08 );
    FCML_I64( "kmovq qword ptr [rax],k1", 0xC4, 0xE1, 0xF8, 0x91, 0x08 );

    FCML_I64( "kmovq k2,rax", 0xC4, 0xE1, 0xFB, 0x92, 0xD0 );
    FCML_I32_A_FAILED( "kmovq k2,rax", 0xC4, 0xE1, 0xFB, 0x92, 0xD0 );
    FCML_I64( "kmovq rdx,k0", 0xC4, 0xE1, 0xFB, 0x93, 0xD0 );
    FCML_I64_A_FAILED( "kmovq rdx,k0", 0xC4, 0xE1, 0xFB, 0x93, 0xD0 );
}

fcml_stf_test_case fctl_ti_instructions_k[] = {
    { "fcml_tf_instruction_KADDW", fcml_tf_instruction_KADDW },
    { "fcml_tf_instruction_KADDB", fcml_tf_instruction_KADDB },
    { "fcml_tf_instruction_KADDD", fcml_tf_instruction_KADDD },
    { "fcml_tf_instruction_KADDQ", fcml_tf_instruction_KADDQ },
    { "fcml_tf_instruction_KANDW", fcml_tf_instruction_KANDW },
    { "fcml_tf_instruction_KANDB", fcml_tf_instruction_KANDB },
    { "fcml_tf_instruction_KANDD", fcml_tf_instruction_KANDD },
    { "fcml_tf_instruction_KANDQ", fcml_tf_instruction_KANDQ },
    { "fcml_tf_instruction_KANDNW", fcml_tf_instruction_KANDNW },
    { "fcml_tf_instruction_KANDNB", fcml_tf_instruction_KANDNB },
    { "fcml_tf_instruction_KANDND", fcml_tf_instruction_KANDND },
    { "fcml_tf_instruction_KANDNQ", fcml_tf_instruction_KANDNQ },
    { "fcml_tf_instruction_KMOVB", fcml_tf_instruction_KMOVB },
    { "fcml_tf_instruction_KMOVW", fcml_tf_instruction_KMOVW },
    { "fcml_tf_instruction_KMOVD", fcml_tf_instruction_KMOVD },
    { "fcml_tf_instruction_KMOVQ", fcml_tf_instruction_KMOVQ },
    FCML_STF_NULL_TEST
};

fcml_stf_test_suite fctl_si_instructions_k = {
    "suite-fctl_ti_instructions_k", fcml_tf_instructions_k_suite_init,
    fcml_tf_instructions_k_suite_cleanup, fctl_ti_instructions_k
};


