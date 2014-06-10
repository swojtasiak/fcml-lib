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

#include "coll_t.h"

#include <fcml_coll.h>

fcml_ptr last_free_key;
fcml_ptr last_free_value;

void fcml_itf_coll_map_entry_handler_test( fcml_ptr key, fcml_ptr value, fcml_ptr args ) {
	last_free_key = key;
	last_free_value = value;
}

fcml_bool fcml_tf_coll_suite_init(void) {
	return FCML_TRUE;
}

fcml_bool fcml_tf_coll_suite_cleanup(void) {
	return FCML_TRUE;
}

void fcml_tf_coll_test_put_the_same_key(void) {

	fcml_int error = FCML_COLL_ERROR_NO_ERROR;

	fcml_coll_map *map = fcml_fn_coll_map_alloc(&fcml_coll_map_descriptor_string, 10, &error );
	if( map == NULL || error ) {
		STF_FAIL( "Can not create hash map." );
	} else {
		fcml_fn_coll_map_put( map, "KEY_1", "VALUE_1", &error );
		STF_ASSERT_STRING_EQUAL( fcml_fn_coll_map_get( map, "KEY_1" ), "VALUE_1" );
		fcml_fn_coll_map_put( map, "KEY_1", "VALUE_2", &error );
		STF_ASSERT_STRING_EQUAL( fcml_fn_coll_map_get( map, "KEY_1" ), "VALUE_2" );
		fcml_fn_coll_map_put( map, "KEY_1", "VALUE_3", &error );
		STF_ASSERT( fcml_fn_coll_map_size( map ) == 1 );
		STF_ASSERT_STRING_EQUAL( fcml_fn_coll_map_get( map, "KEY_1" ), "VALUE_3" );
	}

	fcml_fn_coll_map_free( map );
}

void fcml_tf_coll_test_put_different_keys(void) {

	fcml_int error = FCML_COLL_ERROR_NO_ERROR;

	fcml_coll_map *map = fcml_fn_coll_map_alloc(&fcml_coll_map_descriptor_string, 10, &error );
	if( map == NULL || error ) {
		STF_FAIL( "Can not create hash map." );
	} else {
		/* index 1.*/
		fcml_fn_coll_map_put( map, "KEY_A", "VALUE_A", &error );
		/* Conflict, both of the following keys are conflicted, but take into account*/
		/* that it depends on default built-in implementation of hashing function.*/
		fcml_fn_coll_map_put( map, "KEY_B", "VALUE_B", &error );
		fcml_fn_coll_map_put( map, "KEY_R", "VALUE_R", &error );
		fcml_fn_coll_map_put( map, "KEY_C", "VALUE_C", &error );
		fcml_fn_coll_map_put( map, "KEY_D", "VALUE_D", &error );
		fcml_fn_coll_map_put( map, "KEY_E", "VALUE_E", &error );
		fcml_fn_coll_map_put( map, "KEY_F", "VALUE_F", &error );
		fcml_fn_coll_map_put( map, "KEY_G", "VALUE_G", &error );
		fcml_fn_coll_map_put( map, "KEY_H", "VALUE_H", &error );
		STF_ASSERT( fcml_fn_coll_map_size( map ) == 9 );
		STF_ASSERT_STRING_EQUAL( fcml_fn_coll_map_get( map, "KEY_A" ), "VALUE_A" );
		STF_ASSERT_STRING_EQUAL( fcml_fn_coll_map_get( map, "KEY_B" ), "VALUE_B" );
		STF_ASSERT_STRING_EQUAL( fcml_fn_coll_map_get( map, "KEY_R" ), "VALUE_R" );
		STF_ASSERT_STRING_EQUAL( fcml_fn_coll_map_get( map, "KEY_C" ), "VALUE_C" );
		STF_ASSERT_STRING_EQUAL( fcml_fn_coll_map_get( map, "KEY_D" ), "VALUE_D" );
		STF_ASSERT_STRING_EQUAL( fcml_fn_coll_map_get( map, "KEY_E" ), "VALUE_E" );
		STF_ASSERT_STRING_EQUAL( fcml_fn_coll_map_get( map, "KEY_F" ), "VALUE_F" );
		STF_ASSERT_STRING_EQUAL( fcml_fn_coll_map_get( map, "KEY_G" ), "VALUE_G" );
		STF_ASSERT_STRING_EQUAL( fcml_fn_coll_map_get( map, "KEY_R" ), "VALUE_R" );
	}

	fcml_fn_coll_map_free( map );
}

void fcml_tf_coll_test_remove_keys(void) {

	fcml_int error = FCML_COLL_ERROR_NO_ERROR;

	fcml_st_coll_map_descriptor descriptor = fcml_coll_map_descriptor_string;
	descriptor.entry_free_function = fcml_itf_coll_map_entry_handler_test;
	fcml_coll_map *map = fcml_fn_coll_map_alloc(&descriptor, 10, &error );
	if( map == NULL || error ) {
		STF_FAIL( "Can not create hash map." );
	} else {
		/* index 1.*/
		fcml_fn_coll_map_put( map, "KEY_A", "VALUE_A", &error );
		/* Conflict, both of the following keys are conflicted, but take into account*/
		/* that it depends on default builtin implementation of hashing function.*/
		fcml_fn_coll_map_put( map, "KEY_B", "VALUE_B", &error );
		fcml_fn_coll_map_put( map, "KEY_R", "VALUE_R", &error );
		fcml_fn_coll_map_put( map, "KEY_C", "VALUE_C", &error );
		fcml_fn_coll_map_put( map, "KEY_D", "VALUE_D", &error );
		fcml_fn_coll_map_put( map, "KEY_E", "VALUE_E", &error );
		fcml_fn_coll_map_put( map, "KEY_F", "VALUE_F", &error );
		fcml_fn_coll_map_put( map, "KEY_G", "VALUE_G", &error );
		fcml_fn_coll_map_put( map, "KEY_H", "VALUE_H", &error );
		STF_ASSERT( fcml_fn_coll_map_size( map ) == 9 );
		STF_ASSERT_STRING_EQUAL( fcml_fn_coll_map_get( map, "KEY_A" ), "VALUE_A" );
		STF_ASSERT_STRING_EQUAL( fcml_fn_coll_map_get( map, "KEY_B" ), "VALUE_B" );
		STF_ASSERT_STRING_EQUAL( fcml_fn_coll_map_get( map, "KEY_R" ), "VALUE_R" );
		STF_ASSERT_STRING_EQUAL( fcml_fn_coll_map_get( map, "KEY_C" ), "VALUE_C" );
		STF_ASSERT_STRING_EQUAL( fcml_fn_coll_map_get( map, "KEY_D" ), "VALUE_D" );
		STF_ASSERT_STRING_EQUAL( fcml_fn_coll_map_get( map, "KEY_E" ), "VALUE_E" );
		STF_ASSERT_STRING_EQUAL( fcml_fn_coll_map_get( map, "KEY_F" ), "VALUE_F" );
		STF_ASSERT_STRING_EQUAL( fcml_fn_coll_map_get( map, "KEY_G" ), "VALUE_G" );
		/* Remove KEY_A*/
		fcml_fn_coll_map_remove( map, "KEY_A" );
		/* Check if memory was freed.*/
		STF_ASSERT_PTR_NOT_NULL( last_free_key );
		STF_ASSERT_PTR_NOT_NULL( last_free_value );
		if( last_free_key != NULL ) {
			STF_ASSERT_STRING_EQUAL( last_free_key, "KEY_A" );
		}
		if( last_free_value != NULL ) {
			STF_ASSERT_STRING_EQUAL( last_free_value, "VALUE_A" );
		}
		/* Check if KEY_A has been successfully removed.*/
		STF_ASSERT_PTR_NULL( fcml_fn_coll_map_get( map, "KEY_A" ) );
		STF_ASSERT( fcml_fn_coll_map_size( map ) == 8 );
		/* Check if the rest of keys are still there.*/
		STF_ASSERT_STRING_EQUAL( fcml_fn_coll_map_get( map, "KEY_B" ), "VALUE_B" );
		STF_ASSERT_STRING_EQUAL( fcml_fn_coll_map_get( map, "KEY_R" ), "VALUE_R" );
		STF_ASSERT_STRING_EQUAL( fcml_fn_coll_map_get( map, "KEY_C" ), "VALUE_C" );
		STF_ASSERT_STRING_EQUAL( fcml_fn_coll_map_get( map, "KEY_D" ), "VALUE_D" );
		STF_ASSERT_STRING_EQUAL( fcml_fn_coll_map_get( map, "KEY_E" ), "VALUE_E" );
		STF_ASSERT_STRING_EQUAL( fcml_fn_coll_map_get( map, "KEY_F" ), "VALUE_F" );
		STF_ASSERT_STRING_EQUAL( fcml_fn_coll_map_get( map, "KEY_G" ), "VALUE_G" );
		STF_ASSERT_STRING_EQUAL( fcml_fn_coll_map_get( map, "KEY_H" ), "VALUE_H" );
		/* Remove all keys.*/
		fcml_fn_coll_map_remove( map, "KEY_B" );
		fcml_fn_coll_map_remove( map, "KEY_R" );
		fcml_fn_coll_map_remove( map, "KEY_C" );
		fcml_fn_coll_map_remove( map, "KEY_D" );
		fcml_fn_coll_map_remove( map, "KEY_E" );
		fcml_fn_coll_map_remove( map, "KEY_F" );
		fcml_fn_coll_map_remove( map, "KEY_G" );
		fcml_fn_coll_map_remove( map, "KEY_H" );
		/* And check if they have been removed as well.*/
		STF_ASSERT_PTR_NULL( fcml_fn_coll_map_get( map, "KEY_B" ) );
		STF_ASSERT_PTR_NULL( fcml_fn_coll_map_get( map, "KEY_R" ) );
		STF_ASSERT_PTR_NULL( fcml_fn_coll_map_get( map, "KEY_C" ) );
		STF_ASSERT_PTR_NULL( fcml_fn_coll_map_get( map, "KEY_D" ) );
		STF_ASSERT_PTR_NULL( fcml_fn_coll_map_get( map, "KEY_E" ) );
		STF_ASSERT_PTR_NULL( fcml_fn_coll_map_get( map, "KEY_F" ) );
		STF_ASSERT_PTR_NULL( fcml_fn_coll_map_get( map, "KEY_G" ) );
		STF_ASSERT_PTR_NULL( fcml_fn_coll_map_get( map, "KEY_H" ) );
		STF_ASSERT( fcml_fn_coll_map_size( map ) == 0 );
	}

	fcml_fn_coll_map_free( map );
}


void fcml_tf_coll_test_clear(void) {

	fcml_int error = FCML_COLL_ERROR_NO_ERROR;

	fcml_st_coll_map_descriptor descriptor = fcml_coll_map_descriptor_string;
	descriptor.entry_free_function = fcml_itf_coll_map_entry_handler_test;
	fcml_coll_map *map = fcml_fn_coll_map_alloc(&descriptor, 10, &error );
	if( map == NULL || error ) {
		STF_FAIL( "Can not create hash map." );
	} else {
		/* index 1.*/
		fcml_fn_coll_map_put( map, "KEY_A", "VALUE_A", &error );
		/* Conflict, both of the following keys are conflicted, but take into account*/
		/* that it depends on default builtin implementation of hashing function.*/
		fcml_fn_coll_map_put( map, "KEY_B", "VALUE_B", &error );
		fcml_fn_coll_map_put( map, "KEY_R", "VALUE_R", &error );
		fcml_fn_coll_map_put( map, "KEY_C", "VALUE_C", &error );
		fcml_fn_coll_map_put( map, "KEY_D", "VALUE_D", &error );
		fcml_fn_coll_map_put( map, "KEY_E", "VALUE_E", &error );
		fcml_fn_coll_map_put( map, "KEY_F", "VALUE_F", &error );
		fcml_fn_coll_map_put( map, "KEY_G", "VALUE_G", &error );
		fcml_fn_coll_map_put( map, "KEY_H", "VALUE_H", &error );
		STF_ASSERT( fcml_fn_coll_map_size( map ) == 9 );
		last_free_key = NULL;
		last_free_value = NULL;
		fcml_fn_coll_map_clear( map );
		STF_ASSERT_PTR_NOT_NULL( last_free_key );
		STF_ASSERT_PTR_NOT_NULL( last_free_value );
		/* And check if they have been removed.*/
		STF_ASSERT_PTR_NULL( fcml_fn_coll_map_get( map, "KEY_A" ) );
		STF_ASSERT_PTR_NULL( fcml_fn_coll_map_get( map, "KEY_B" ) );
		STF_ASSERT_PTR_NULL( fcml_fn_coll_map_get( map, "KEY_R" ) );
		STF_ASSERT_PTR_NULL( fcml_fn_coll_map_get( map, "KEY_C" ) );
		STF_ASSERT_PTR_NULL( fcml_fn_coll_map_get( map, "KEY_D" ) );
		STF_ASSERT_PTR_NULL( fcml_fn_coll_map_get( map, "KEY_E" ) );
		STF_ASSERT_PTR_NULL( fcml_fn_coll_map_get( map, "KEY_F" ) );
		STF_ASSERT_PTR_NULL( fcml_fn_coll_map_get( map, "KEY_G" ) );
		STF_ASSERT_PTR_NULL( fcml_fn_coll_map_get( map, "KEY_H" ) );
		STF_ASSERT( fcml_fn_coll_map_size( map ) == 0 );
	}

	fcml_fn_coll_map_free( map );
}

int iterator_counter;

void fcml_itf_coll_test_iterate_handler( fcml_ptr key, fcml_ptr value, fcml_ptr args ) {
	iterator_counter++;
}

void fcml_tf_coll_test_iterate(void) {

	iterator_counter = 0;

	fcml_int error = FCML_COLL_ERROR_NO_ERROR;

	fcml_st_coll_map_descriptor descriptor = fcml_coll_map_descriptor_string;
	descriptor.entry_free_function = fcml_itf_coll_map_entry_handler_test;
	fcml_coll_map *map = fcml_fn_coll_map_alloc(&descriptor, 10, &error );
	if( map == NULL || error ) {
		STF_FAIL( "Can not create hash map." );
	} else {
		/* index 1.*/
		fcml_fn_coll_map_put( map, "KEY_A", "VALUE_A", &error );
		/* Conflict, both of the following keys are conflicted, but take into account*/
		/* that it depends on default built-in implementation of hashing function.*/
		fcml_fn_coll_map_put( map, "KEY_B", "VALUE_B", &error );
		fcml_fn_coll_map_put( map, "KEY_R", "VALUE_R", &error );
		fcml_fn_coll_map_put( map, "KEY_C", "VALUE_C", &error );
		fcml_fn_coll_map_put( map, "KEY_D", "VALUE_D", &error );
		fcml_fn_coll_map_put( map, "KEY_E", "VALUE_E", &error );
		fcml_fn_coll_map_put( map, "KEY_F", "VALUE_F", &error );
		fcml_fn_coll_map_put( map, "KEY_G", "VALUE_G", &error );
		fcml_fn_coll_map_put( map, "KEY_H", "VALUE_H", &error );
		fcml_fn_coll_map_iterate( map, fcml_itf_coll_test_iterate_handler );
		STF_ASSERT_EQUAL( iterator_counter, 9 );
		iterator_counter = 0;
		fcml_fn_coll_map_clear( map );
		fcml_fn_coll_map_iterate( map, fcml_itf_coll_test_iterate_handler );
		STF_ASSERT_EQUAL( iterator_counter, 0 );
	}

	fcml_fn_coll_map_free( map );
}

void fcml_tf_coll_test_extend(void) {

	iterator_counter = 0;

	fcml_int error = FCML_COLL_ERROR_NO_ERROR;

	fcml_coll_map *map = fcml_fn_coll_map_alloc(&fcml_coll_map_descriptor_string, 2, &error );
	if( map == NULL || error ) {
		STF_FAIL( "Can not create hash map." );
	} else {
		/* index 1.*/
		fcml_fn_coll_map_put( map, "KEY_A", "VALUE_A", &error );
		fcml_fn_coll_map_put( map, "KEY_B", "VALUE_B", &error );
		fcml_fn_coll_map_put( map, "KEY_R", "VALUE_R", &error );
		fcml_fn_coll_map_put( map, "KEY_C", "VALUE_C", &error );
		fcml_fn_coll_map_put( map, "KEY_D", "VALUE_D", &error );
		fcml_fn_coll_map_put( map, "KEY_E", "VALUE_E", &error );
		fcml_fn_coll_map_put( map, "KEY_F", "VALUE_F", &error );
		fcml_fn_coll_map_put( map, "KEY_G", "VALUE_G", &error );
		fcml_fn_coll_map_put( map, "KEY_H", "VALUE_H", &error );
		STF_ASSERT_STRING_EQUAL( fcml_fn_coll_map_get( map, "KEY_A" ), "VALUE_A" );
		STF_ASSERT_STRING_EQUAL( fcml_fn_coll_map_get( map, "KEY_B" ), "VALUE_B" );
		STF_ASSERT_STRING_EQUAL( fcml_fn_coll_map_get( map, "KEY_R" ), "VALUE_R" );
		STF_ASSERT_STRING_EQUAL( fcml_fn_coll_map_get( map, "KEY_C" ), "VALUE_C" );
		STF_ASSERT_STRING_EQUAL( fcml_fn_coll_map_get( map, "KEY_D" ), "VALUE_D" );
		STF_ASSERT_STRING_EQUAL( fcml_fn_coll_map_get( map, "KEY_E" ), "VALUE_E" );
		STF_ASSERT_STRING_EQUAL( fcml_fn_coll_map_get( map, "KEY_F" ), "VALUE_F" );
		STF_ASSERT_STRING_EQUAL( fcml_fn_coll_map_get( map, "KEY_G" ), "VALUE_G" );
		STF_ASSERT_STRING_EQUAL( fcml_fn_coll_map_get( map, "KEY_H" ), "VALUE_H" );
	}

	fcml_fn_coll_map_free( map );
}

fcml_stf_test_case fcml_ti_coll[] = {
	{ "fcml_tf_coll_test_put_the_same_key", fcml_tf_coll_test_put_the_same_key },
	{ "fcml_tf_coll_test_put_different_keys", fcml_tf_coll_test_put_different_keys },
	{ "fcml_tf_coll_test_remove_keys", fcml_tf_coll_test_remove_keys },
	{ "fcml_tf_coll_test_clear", fcml_tf_coll_test_clear },
	{ "fcml_tf_coll_test_iterate", fcml_tf_coll_test_iterate },
	{ "fcml_tf_coll_test_extend", fcml_tf_coll_test_extend },
	FCML_STF_NULL_TEST
};

fcml_stf_test_suite fcml_si_coll = {
	"suite-fcml-coll", fcml_tf_coll_suite_init, fcml_tf_coll_suite_cleanup, fcml_ti_coll
};
