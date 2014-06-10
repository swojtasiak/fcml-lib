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

#include <stdlib.h>

#include "symbols_t.h"

#include <fcml_symbols.h>

fcml_bool fcml_tf_symbols_suite_init(void) {
	return FCML_TRUE;
}

fcml_bool fcml_tf_symbols_suite_cleanup(void) {
	return FCML_TRUE;
}

void fcml_tf_symbols_alloc() {
	fcml_st_symbol_table table = fcml_fn_symbol_table_alloc();
	STF_ASSERT_PTR_NOT_NULL( table );
	if( table ) {
		fcml_st_symbol *symbol = fcml_fn_symbol_alloc( "MAX_PATH", 256 );
		STF_ASSERT_PTR_NOT_NULL( symbol );
		if( symbol ) {
			STF_ASSERT_EQUAL( fcml_fn_symbol_add( table, symbol ), FCML_CEH_GEC_NO_ERROR );
		}
		fcml_fn_symbol_table_free( table );
	}
}

fcml_stf_test_case fctl_ti_symbols[] = {
	{ "fcml_tf_symbols_alloc", fcml_tf_symbols_alloc },
};

fcml_stf_test_suite fctl_si_symbols = {
	"suite-symbols", fcml_tf_symbols_suite_init, fcml_tf_symbols_suite_cleanup, fctl_ti_symbols
};


