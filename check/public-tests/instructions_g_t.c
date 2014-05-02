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
#include "instructions_g_t.h"
#include "instructions_base_t.h"

fcml_bool fcml_tf_instructions_g_suite_init(void) {
	return FCML_TRUE;
}

fcml_bool fcml_tf_instructions_g_suite_cleanup(void) {
	return FCML_TRUE;
}

void fcml_tf_instruction_GETSEC(void) {
    FCML_I3264( "getsec", 0x0F, 0x37 );
    FCML_A64( "getsec", 0x0f, 0x37 );
}

fcml_stf_test_case fctl_ti_instructions_g[] = {
	{ "fcml_tf_instruction_GETSEC", fcml_tf_instruction_GETSEC },
	FCML_STF_NULL_TEST
};

fcml_stf_test_suite fctl_si_instructions_g = {
	"suite-fctl_ti_instructions_g", fcml_tf_instructions_g_suite_init, fcml_tf_instructions_g_suite_cleanup, fctl_ti_instructions_g
};
