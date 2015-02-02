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

#include <fcml_env.h>

#include "env_t.h"

#include <fcml_symbols.h>

#include "fcml_env_int.h"

fcml_int counter = 0;

fcml_int realloc_counter = 0;

fcml_fp_env_memory_alloc_handler default_alloc;

fcml_fp_env_memory_realloc_handler default_realloc;

fcml_fp_env_memory_free_handler default_free;

fcml_ptr fcml_tf_env_memory_alloc_handler_counter( fcml_usize size ) {
	counter += 1;
	return default_alloc( size );
}

fcml_ptr fcml_tf_env_memory_realloc_handler_counter( fcml_ptr ptr, fcml_usize size ) {
	realloc_counter += 1;
	return default_realloc( ptr, size );
}

void fcml_tf_env_memory_free_handler_counter( fcml_ptr ptr ) {
	counter -= 1;
	default_free( ptr );
}

fcml_bool fcml_tf_env_suite_init(void) {
	default_alloc = fcml_fn_env_register_memory_alloc_handler( &fcml_tf_env_memory_alloc_handler_counter );
	default_realloc = fcml_fn_env_register_memory_realloc_handler( &fcml_tf_env_memory_realloc_handler_counter );
	default_free = fcml_fn_env_register_memory_free_handler( &fcml_tf_env_memory_free_handler_counter );
	return FCML_TRUE;
}

fcml_bool fcml_tf_env_suite_cleanup(void) {
	fcml_fn_env_register_memory_alloc_handler( default_alloc );
	fcml_fn_env_register_memory_realloc_handler( default_realloc );
	fcml_fn_env_register_memory_free_handler( default_free );
	return FCML_TRUE;
}

void fcml_fn_env_test_memory_alloc(void) {
	fcml_st_symbol *symbol = (fcml_st_symbol*)fcml_fn_symbol_alloc( "TEST", 1 );
	STF_ASSERT_PTR_NOT_NULL( symbol );
	if( symbol ) {
		STF_ASSERT_EQUAL( counter, 2 ); // symbol+symbol_name string
		fcml_fn_symbol_free( symbol );
		STF_ASSERT_EQUAL( counter, 0 );
	}
}

void fcml_fn_env_test_memory_realloc(void) {

	fcml_ptr block = fcml_fn_env_memory_alloc( 100 );
	STF_ASSERT_PTR_NOT_NULL( block );
	if( block ) {
		STF_ASSERT_EQUAL( counter, 1 );
		fcml_ptr block_realloc = fcml_fn_env_memory_realloc( block, 200 );
		fcml_fn_env_memory_clear( block_realloc, 200 );
		STF_ASSERT_PTR_NOT_NULL( block_realloc );
		STF_ASSERT_EQUAL( realloc_counter, 1 );
		fcml_fn_symbol_free( block_realloc );
		STF_ASSERT_EQUAL( counter, 0 );
	}

}

fcml_stf_test_case fcml_ti_env[] = {
	{ "fcml_fn_env_test_memory_alloc", fcml_fn_env_test_memory_alloc },
	{ "fcml_fn_env_test_memory_realloc", fcml_fn_env_test_memory_realloc },
	FCML_STF_NULL_TEST
};

fcml_stf_test_suite fcml_si_env = {
	"suite-fcml-env", fcml_tf_env_suite_init, fcml_tf_env_suite_cleanup, fcml_ti_env
};


