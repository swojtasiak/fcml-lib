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

#include "common_utils_t.h"

#include <fcml_common_utils.h>

fcml_bool fcml_tf_common_utils_suite_init(void) {
	return FCML_TRUE;
}

fcml_bool fcml_tf_common_utils_suite_cleanup(void) {
	return FCML_TRUE;
}

void fcml_tf_common_utils_instruction_cloning(void) {

	fcml_st_instruction instruction = {0};
	instruction.mnemonic = "adc";

	fcml_st_instruction *cloned = (fcml_st_instruction*)fcml_fn_cu_clone_instruction( &instruction );
	STF_ASSERT_PTR_NOT_NULL( cloned );
	STF_ASSERT_STRING_EQUAL( "adc", cloned->mnemonic );

	fcml_fn_cu_free_instruction( cloned );
}

fcml_stf_test_case fcml_ti_common_utils[] = {
	{ "fcml_tf_common_utils_instruction_cloning", fcml_tf_common_utils_instruction_cloning },
	FCML_STF_NULL_TEST
};

fcml_stf_test_suite fcml_si_common_utils = {
	"suite-fcml-common-utils", fcml_tf_common_utils_suite_init, fcml_tf_common_utils_suite_cleanup, fcml_ti_common_utils
};

