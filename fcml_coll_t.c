/*
 * fcml_coll_t.c
 *
 *  Created on: 24-03-2013
 *      Author: tAs
 */

#include "fcml_coll_t.h"

#include <fcml_coll.h>

fcml_ptr last_free_key;
fcml_ptr last_free_value;

void fcml_itf_coll_map_entry_handler_test( fcml_ptr key, fcml_ptr value, fcml_ptr args ) {
	last_free_key = key;
	last_free_value = value;
}

int fcml_tf_coll_suite_init(void) {
	return 0;
}

int fcml_tf_coll_suite_cleanup(void) {
	return 0;
}

void fcml_tf_coll_test_put_the_same_key(void) {

	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

	fcml_coll_map *map = fcml_fn_coll_map_alloc(&fcml_coll_map_descriptor_string, 10, &error );
	if( map == NULL || error ) {
		CU_FAIL( "Can not create hash map." );
	} else {
		fcml_fn_coll_map_put( map, "KEY_1", "VALUE_1", &error );
		CU_ASSERT_STRING_EQUAL( fcml_fn_coll_map_get( map, "KEY_1" ), "VALUE_1" );
		fcml_fn_coll_map_put( map, "KEY_1", "VALUE_2", &error );
		CU_ASSERT_STRING_EQUAL( fcml_fn_coll_map_get( map, "KEY_1" ), "VALUE_2" );
		fcml_fn_coll_map_put( map, "KEY_1", "VALUE_3", &error );
		CU_ASSERT( fcml_fn_coll_map_size( map ) == 1 );
		CU_ASSERT_STRING_EQUAL( fcml_fn_coll_map_get( map, "KEY_1" ), "VALUE_3" );
	}

	fcml_fn_coll_map_free( map );
}

void fcml_tf_coll_test_put_different_keys(void) {

	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

	fcml_coll_map *map = fcml_fn_coll_map_alloc(&fcml_coll_map_descriptor_string, 10, &error );
	if( map == NULL || error ) {
		CU_FAIL( "Can not create hash map." );
	} else {
		// index 1.
		fcml_fn_coll_map_put( map, "KEY_A", "VALUE_A", &error );
		// Conflict, both of the following keys are conflicted, but take into account
		// that it depends on default builtin implementation of hashing function.
		fcml_fn_coll_map_put( map, "KEY_B", "VALUE_B", &error );
		fcml_fn_coll_map_put( map, "KEY_R", "VALUE_R", &error );
		fcml_fn_coll_map_put( map, "KEY_C", "VALUE_C", &error );
		fcml_fn_coll_map_put( map, "KEY_D", "VALUE_D", &error );
		fcml_fn_coll_map_put( map, "KEY_E", "VALUE_E", &error );
		fcml_fn_coll_map_put( map, "KEY_F", "VALUE_F", &error );
		fcml_fn_coll_map_put( map, "KEY_G", "VALUE_G", &error );
		fcml_fn_coll_map_put( map, "KEY_H", "VALUE_H", &error );
		CU_ASSERT( fcml_fn_coll_map_size( map ) == 9 );
		CU_ASSERT_STRING_EQUAL( fcml_fn_coll_map_get( map, "KEY_A" ), "VALUE_A" );
		CU_ASSERT_STRING_EQUAL( fcml_fn_coll_map_get( map, "KEY_B" ), "VALUE_B" );
		CU_ASSERT_STRING_EQUAL( fcml_fn_coll_map_get( map, "KEY_R" ), "VALUE_R" );
		CU_ASSERT_STRING_EQUAL( fcml_fn_coll_map_get( map, "KEY_C" ), "VALUE_C" );
		CU_ASSERT_STRING_EQUAL( fcml_fn_coll_map_get( map, "KEY_D" ), "VALUE_D" );
		CU_ASSERT_STRING_EQUAL( fcml_fn_coll_map_get( map, "KEY_E" ), "VALUE_E" );
		CU_ASSERT_STRING_EQUAL( fcml_fn_coll_map_get( map, "KEY_F" ), "VALUE_F" );
		CU_ASSERT_STRING_EQUAL( fcml_fn_coll_map_get( map, "KEY_G" ), "VALUE_G" );
		CU_ASSERT_STRING_EQUAL( fcml_fn_coll_map_get( map, "KEY_R" ), "VALUE_R" );
	}

	fcml_fn_coll_map_free( map );
}

void fcml_tf_coll_test_remove_keys(void) {

	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

	fcml_st_coll_map_descriptor descriptor = fcml_coll_map_descriptor_string;
	descriptor.entry_free_function = fcml_itf_coll_map_entry_handler_test;
	fcml_coll_map *map = fcml_fn_coll_map_alloc(&descriptor, 10, &error );
	if( map == NULL || error ) {
		CU_FAIL( "Can not create hash map." );
	} else {
		// index 1.
		fcml_fn_coll_map_put( map, "KEY_A", "VALUE_A", &error );
		// Conflict, both of the following keys are conflicted, but take into account
		// that it depends on default builtin implementation of hashing function.
		fcml_fn_coll_map_put( map, "KEY_B", "VALUE_B", &error );
		fcml_fn_coll_map_put( map, "KEY_R", "VALUE_R", &error );
		fcml_fn_coll_map_put( map, "KEY_C", "VALUE_C", &error );
		fcml_fn_coll_map_put( map, "KEY_D", "VALUE_D", &error );
		fcml_fn_coll_map_put( map, "KEY_E", "VALUE_E", &error );
		fcml_fn_coll_map_put( map, "KEY_F", "VALUE_F", &error );
		fcml_fn_coll_map_put( map, "KEY_G", "VALUE_G", &error );
		fcml_fn_coll_map_put( map, "KEY_H", "VALUE_H", &error );
		CU_ASSERT( fcml_fn_coll_map_size( map ) == 9 );
		CU_ASSERT_STRING_EQUAL( fcml_fn_coll_map_get( map, "KEY_A" ), "VALUE_A" );
		CU_ASSERT_STRING_EQUAL( fcml_fn_coll_map_get( map, "KEY_B" ), "VALUE_B" );
		CU_ASSERT_STRING_EQUAL( fcml_fn_coll_map_get( map, "KEY_R" ), "VALUE_R" );
		CU_ASSERT_STRING_EQUAL( fcml_fn_coll_map_get( map, "KEY_C" ), "VALUE_C" );
		CU_ASSERT_STRING_EQUAL( fcml_fn_coll_map_get( map, "KEY_D" ), "VALUE_D" );
		CU_ASSERT_STRING_EQUAL( fcml_fn_coll_map_get( map, "KEY_E" ), "VALUE_E" );
		CU_ASSERT_STRING_EQUAL( fcml_fn_coll_map_get( map, "KEY_F" ), "VALUE_F" );
		CU_ASSERT_STRING_EQUAL( fcml_fn_coll_map_get( map, "KEY_G" ), "VALUE_G" );
		// Remove KEY_A
		fcml_fn_coll_map_remove( map, "KEY_A" );
		// Check if memory was freed.
		CU_ASSERT_PTR_NOT_NULL( last_free_key );
		CU_ASSERT_PTR_NOT_NULL( last_free_value );
		if( last_free_key != NULL ) {
			CU_ASSERT_STRING_EQUAL( last_free_key, "KEY_A" );
		}
		if( last_free_value != NULL ) {
			CU_ASSERT_STRING_EQUAL( last_free_value, "VALUE_A" );
		}
		// Check if KEY_A has been sucesfully removed.
		CU_ASSERT_PTR_NULL( fcml_fn_coll_map_get( map, "KEY_A" ) );
		CU_ASSERT( fcml_fn_coll_map_size( map ) == 8 );
		// Check if the rest of keys are still there.
		CU_ASSERT_STRING_EQUAL( fcml_fn_coll_map_get( map, "KEY_B" ), "VALUE_B" );
		CU_ASSERT_STRING_EQUAL( fcml_fn_coll_map_get( map, "KEY_R" ), "VALUE_R" );
		CU_ASSERT_STRING_EQUAL( fcml_fn_coll_map_get( map, "KEY_C" ), "VALUE_C" );
		CU_ASSERT_STRING_EQUAL( fcml_fn_coll_map_get( map, "KEY_D" ), "VALUE_D" );
		CU_ASSERT_STRING_EQUAL( fcml_fn_coll_map_get( map, "KEY_E" ), "VALUE_E" );
		CU_ASSERT_STRING_EQUAL( fcml_fn_coll_map_get( map, "KEY_F" ), "VALUE_F" );
		CU_ASSERT_STRING_EQUAL( fcml_fn_coll_map_get( map, "KEY_G" ), "VALUE_G" );
		CU_ASSERT_STRING_EQUAL( fcml_fn_coll_map_get( map, "KEY_H" ), "VALUE_H" );
		// Remove all keys.
		fcml_fn_coll_map_remove( map, "KEY_B" );
		fcml_fn_coll_map_remove( map, "KEY_R" );
		fcml_fn_coll_map_remove( map, "KEY_C" );
		fcml_fn_coll_map_remove( map, "KEY_D" );
		fcml_fn_coll_map_remove( map, "KEY_E" );
		fcml_fn_coll_map_remove( map, "KEY_F" );
		fcml_fn_coll_map_remove( map, "KEY_G" );
		fcml_fn_coll_map_remove( map, "KEY_H" );
		// And check if they have been removed as well.
		CU_ASSERT_PTR_NULL( fcml_fn_coll_map_get( map, "KEY_B" ) );
		CU_ASSERT_PTR_NULL( fcml_fn_coll_map_get( map, "KEY_R" ) );
		CU_ASSERT_PTR_NULL( fcml_fn_coll_map_get( map, "KEY_C" ) );
		CU_ASSERT_PTR_NULL( fcml_fn_coll_map_get( map, "KEY_D" ) );
		CU_ASSERT_PTR_NULL( fcml_fn_coll_map_get( map, "KEY_E" ) );
		CU_ASSERT_PTR_NULL( fcml_fn_coll_map_get( map, "KEY_F" ) );
		CU_ASSERT_PTR_NULL( fcml_fn_coll_map_get( map, "KEY_G" ) );
		CU_ASSERT_PTR_NULL( fcml_fn_coll_map_get( map, "KEY_H" ) );
		CU_ASSERT( fcml_fn_coll_map_size( map ) == 0 );
	}

	fcml_fn_coll_map_free( map );
}


void fcml_tf_coll_test_clear(void) {

	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

	fcml_st_coll_map_descriptor descriptor = fcml_coll_map_descriptor_string;
	descriptor.entry_free_function = fcml_itf_coll_map_entry_handler_test;
	fcml_coll_map *map = fcml_fn_coll_map_alloc(&descriptor, 10, &error );
	if( map == NULL || error ) {
		CU_FAIL( "Can not create hash map." );
	} else {
		// index 1.
		fcml_fn_coll_map_put( map, "KEY_A", "VALUE_A", &error );
		// Conflict, both of the following keys are conflicted, but take into account
		// that it depends on default builtin implementation of hashing function.
		fcml_fn_coll_map_put( map, "KEY_B", "VALUE_B", &error );
		fcml_fn_coll_map_put( map, "KEY_R", "VALUE_R", &error );
		fcml_fn_coll_map_put( map, "KEY_C", "VALUE_C", &error );
		fcml_fn_coll_map_put( map, "KEY_D", "VALUE_D", &error );
		fcml_fn_coll_map_put( map, "KEY_E", "VALUE_E", &error );
		fcml_fn_coll_map_put( map, "KEY_F", "VALUE_F", &error );
		fcml_fn_coll_map_put( map, "KEY_G", "VALUE_G", &error );
		fcml_fn_coll_map_put( map, "KEY_H", "VALUE_H", &error );
		CU_ASSERT( fcml_fn_coll_map_size( map ) == 9 );
		last_free_key = NULL;
		last_free_value = NULL;
		fcml_fn_coll_map_clear( map );
		CU_ASSERT_PTR_NOT_NULL( last_free_key );
		CU_ASSERT_PTR_NOT_NULL( last_free_value );
		// And check if they have been removed.
		CU_ASSERT_PTR_NULL( fcml_fn_coll_map_get( map, "KEY_A" ) );
		CU_ASSERT_PTR_NULL( fcml_fn_coll_map_get( map, "KEY_B" ) );
		CU_ASSERT_PTR_NULL( fcml_fn_coll_map_get( map, "KEY_R" ) );
		CU_ASSERT_PTR_NULL( fcml_fn_coll_map_get( map, "KEY_C" ) );
		CU_ASSERT_PTR_NULL( fcml_fn_coll_map_get( map, "KEY_D" ) );
		CU_ASSERT_PTR_NULL( fcml_fn_coll_map_get( map, "KEY_E" ) );
		CU_ASSERT_PTR_NULL( fcml_fn_coll_map_get( map, "KEY_F" ) );
		CU_ASSERT_PTR_NULL( fcml_fn_coll_map_get( map, "KEY_G" ) );
		CU_ASSERT_PTR_NULL( fcml_fn_coll_map_get( map, "KEY_H" ) );
		CU_ASSERT( fcml_fn_coll_map_size( map ) == 0 );
	}

	fcml_fn_coll_map_free( map );
}

int iterator_counter;
void fcml_itf_coll_test_iterate_handler( fcml_ptr key, fcml_ptr value, fcml_ptr args ) {
	iterator_counter++;
}

void fcml_tf_coll_test_iterate(void) {

	iterator_counter = 0;

	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

	fcml_st_coll_map_descriptor descriptor = fcml_coll_map_descriptor_string;
	descriptor.entry_free_function = fcml_itf_coll_map_entry_handler_test;
	fcml_coll_map *map = fcml_fn_coll_map_alloc(&descriptor, 10, &error );
	if( map == NULL || error ) {
		CU_FAIL( "Can not create hash map." );
	} else {
		// index 1.
		fcml_fn_coll_map_put( map, "KEY_A", "VALUE_A", &error );
		// Conflict, both of the following keys are conflicted, but take into account
		// that it depends on default builtin implementation of hashing function.
		fcml_fn_coll_map_put( map, "KEY_B", "VALUE_B", &error );
		fcml_fn_coll_map_put( map, "KEY_R", "VALUE_R", &error );
		fcml_fn_coll_map_put( map, "KEY_C", "VALUE_C", &error );
		fcml_fn_coll_map_put( map, "KEY_D", "VALUE_D", &error );
		fcml_fn_coll_map_put( map, "KEY_E", "VALUE_E", &error );
		fcml_fn_coll_map_put( map, "KEY_F", "VALUE_F", &error );
		fcml_fn_coll_map_put( map, "KEY_G", "VALUE_G", &error );
		fcml_fn_coll_map_put( map, "KEY_H", "VALUE_H", &error );
		fcml_fn_coll_map_iterate( map, fcml_itf_coll_test_iterate_handler );
		CU_ASSERT_EQUAL( iterator_counter, 9 );
		iterator_counter = 0;
		fcml_fn_coll_map_clear( map );
		fcml_fn_coll_map_iterate( map, fcml_itf_coll_test_iterate_handler );
		CU_ASSERT_EQUAL( iterator_counter, 0 );
	}

	fcml_fn_coll_map_free( map );
}

void fcml_tf_coll_test_extend(void) {

	iterator_counter = 0;

	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

	fcml_coll_map *map = fcml_fn_coll_map_alloc(&fcml_coll_map_descriptor_string, 2, &error );
	if( map == NULL || error ) {
		CU_FAIL( "Can not create hash map." );
	} else {
		// index 1.
		fcml_fn_coll_map_put( map, "KEY_A", "VALUE_A", &error );
		fcml_fn_coll_map_put( map, "KEY_B", "VALUE_B", &error );
		fcml_fn_coll_map_put( map, "KEY_R", "VALUE_R", &error );
		fcml_fn_coll_map_put( map, "KEY_C", "VALUE_C", &error );
		fcml_fn_coll_map_put( map, "KEY_D", "VALUE_D", &error );
		fcml_fn_coll_map_put( map, "KEY_E", "VALUE_E", &error );
		fcml_fn_coll_map_put( map, "KEY_F", "VALUE_F", &error );
		fcml_fn_coll_map_put( map, "KEY_G", "VALUE_G", &error );
		fcml_fn_coll_map_put( map, "KEY_H", "VALUE_H", &error );
		CU_ASSERT_STRING_EQUAL( fcml_fn_coll_map_get( map, "KEY_A" ), "VALUE_A" );
		CU_ASSERT_STRING_EQUAL( fcml_fn_coll_map_get( map, "KEY_B" ), "VALUE_B" );
		CU_ASSERT_STRING_EQUAL( fcml_fn_coll_map_get( map, "KEY_R" ), "VALUE_R" );
		CU_ASSERT_STRING_EQUAL( fcml_fn_coll_map_get( map, "KEY_C" ), "VALUE_C" );
		CU_ASSERT_STRING_EQUAL( fcml_fn_coll_map_get( map, "KEY_D" ), "VALUE_D" );
		CU_ASSERT_STRING_EQUAL( fcml_fn_coll_map_get( map, "KEY_E" ), "VALUE_E" );
		CU_ASSERT_STRING_EQUAL( fcml_fn_coll_map_get( map, "KEY_F" ), "VALUE_F" );
		CU_ASSERT_STRING_EQUAL( fcml_fn_coll_map_get( map, "KEY_G" ), "VALUE_G" );
		CU_ASSERT_STRING_EQUAL( fcml_fn_coll_map_get( map, "KEY_H" ), "VALUE_H" );
	}

	fcml_fn_coll_map_free( map );
}

CU_TestInfo fcml_ti_coll[] = {
    { "fcml_tf_coll_test_put_the_same_key", fcml_tf_coll_test_put_the_same_key },
    { "fcml_tf_coll_test_put_different_keys", fcml_tf_coll_test_put_different_keys },
    { "fcml_tf_coll_test_remove_keys", fcml_tf_coll_test_remove_keys },
	{ "fcml_tf_coll_test_clear", fcml_tf_coll_test_clear },
	{ "fcml_tf_coll_test_iterate", fcml_tf_coll_test_iterate },
	{ "fcml_tf_coll_test_extend", fcml_tf_coll_test_extend },
    CU_TEST_INFO_NULL,
};

CU_SuiteInfo fcml_si_coll[] = {
    { "suite-fcml-coll", fcml_tf_coll_suite_init, fcml_tf_coll_suite_cleanup, fcml_ti_coll },
    CU_SUITE_INFO_NULL,
};
