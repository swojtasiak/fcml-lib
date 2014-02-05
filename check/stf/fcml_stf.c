/*
 * fcml_stf.c
 *
 *  Created on: Jan 23, 2014
 *      Author: tas
 */

#include "fcml_stf.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* Failed asserts and counters are stored here.*/
fcml_stf_test_result fcml_gl_stf_test_result = { 0 };

/* Assert's counters for running test.*/
fcml_stf_test_counter current_test_counters = { 0 };

/* Tested suite.*/
fcml_stf_test_suite *current_suite;

/* tested test case.*/
fcml_stf_test_case *current_test;

void LIB_CALL_STF fcml_str_run_assert( fcml_bool condition, fcml_string file, fcml_int line, fcml_string message ) {

	if( !condition ) {

		/* Assert failed, so allocate and save some information about this event.*/
		fcml_stf_result_element *element = malloc( sizeof( fcml_stf_result_element ) );
		if( !element ) {
			printf("Can not allocate memory for assert result.");
			return;
		}

		memset( element, 0, sizeof( fcml_stf_result_element ) );

		element->file = file;
		element->line = line;
		element->message = message;
		element->test_case = current_test;
		element->suite = current_suite;

		if( !fcml_gl_stf_test_result.first ) {
			fcml_gl_stf_test_result.first = element;
		} else {
			fcml_gl_stf_test_result.last->next = element;
		}

		fcml_gl_stf_test_result.last = element;

		current_test_counters.failed++;
	} else {
		current_test_counters.passed++;
	}

}

fcml_bool LIB_CALL_STF fcml_stf_run_tests( fcml_string test_name, fcml_stf_test_suite **suite ) {

	/* Execute suites one by one.*/

	fcml_stf_test_suite **current = suite;
	while( *current ) {

		fcml_stf_test_suite *suite = *current;

		fcml_stf_test_case *test_case = suite->test_cases;

		current_suite = suite;

		/* Check if there are any test cases for current suite.*/
		if( test_case ) {

			/* Initialize test suit.*/
			if( suite->init_function ) {
				suite->init_function();
			}

			/* True if at least one test failed.*/
			fcml_bool test_failed = FCML_FALSE;

			/* Last test which is also an array guard has NULL name.*/
			while( test_case->name ) {

				current_test = test_case;

				/* Clear current counters.*/
				current_test_counters.failed = 0;
				current_test_counters.passed = 0;

				/* Run test function.*/
				if( test_case->test_function ) {
					test_case->test_function();
				}

				fcml_gl_stf_test_result.asserts.failed += current_test_counters.failed;
				fcml_gl_stf_test_result.asserts.passed += current_test_counters.passed;

				if( current_test_counters.failed ) {
					/* There are assert failures, so test has failed.*/
					fcml_gl_stf_test_result.tests.failed++;
					test_failed = FCML_TRUE;
				} else {
					fcml_gl_stf_test_result.tests.passed++;
				}

				test_case++;
			}

			/* Count suites.*/
			if( test_failed ) {
				fcml_gl_stf_test_result.suites.failed++;
			} else {
				fcml_gl_stf_test_result.suites.passed++;
			}

			/* Cleanup test suite.*/
			if( suite->cleanup_function ) {
				suite->cleanup_function();
			}

		} else {
			/* Guard.*/
			break;
		}

		current++;
	}

	/* Report first 100 asserts errors.*/

	printf("\nTest [%s]:", test_name );

	current_suite = NULL;
	current_test = NULL;

	int counter = 0;
	int asserts_counter = 0;

	fcml_stf_result_element *assert = fcml_gl_stf_test_result.first;
	while( assert && counter <= 100 ) {

		fcml_stf_test_suite *suite = assert->suite;
		fcml_stf_test_case *test_case = assert->test_case;

		if( current_suite != suite || current_test != test_case ) {
			current_suite = suite;
			current_test = test_case;
			asserts_counter = 0;
		}

		if( asserts_counter == 0 ) {
			printf( "\nSuite %s, Test %s had failures:\n", current_suite->name, current_test->name );
		}

		printf( "  %4d. %s:%-6d \"%s\"\n", asserts_counter+++1, assert->file, assert->line, assert->message );

		assert = assert->next;

		counter++;
	}

	/* Print counters report.*/

	fcml_stf_test_counter suites = fcml_gl_stf_test_result.suites;
	fcml_stf_test_counter tests = fcml_gl_stf_test_result.tests;
	fcml_stf_test_counter asserts = fcml_gl_stf_test_result.asserts;

	printf("\nRun Summary:      Type         Ran     Passed     Failed\n");
	printf("                suites  %10d %10d %10d\n", suites.failed + suites.passed, suites.passed, suites.failed );
	printf("                 tests  %10d %10d %10d\n", tests.failed + tests.passed, tests.passed, tests.failed );
	printf("               asserts  %10d %10d %10d\n", asserts.failed + asserts.passed, asserts.passed, asserts.failed );

	/* Free all reported asserts.*/
	fcml_stf_result_element *element = fcml_gl_stf_test_result.first;
	while( element ) {
		fcml_stf_result_element *tmp = element;
		element = tmp->next;
		free( tmp );
	}

	return fcml_gl_stf_test_result.suites.failed == 0;
}
