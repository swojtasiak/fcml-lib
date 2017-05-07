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

fcml_stf_test_case fctl_ti_instructions_k[] = {
    { "fcml_tf_instruction_KADDW", fcml_tf_instruction_KADDW },
    FCML_STF_NULL_TEST
};

fcml_stf_test_suite fctl_si_instructions_k = {
    "suite-fctl_ti_instructions_k", fcml_tf_instructions_k_suite_init,
    fcml_tf_instructions_k_suite_cleanup, fctl_ti_instructions_k
};


