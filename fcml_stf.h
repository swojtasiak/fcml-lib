/*
 * fcml_stf.h
 *
 *  Created on: Jan 23, 2014
 *      Author: tas
 */

#ifndef FCML_STF_H_
#define FCML_STF_H_

#define FCML_STF_NULL_SUITE		NULL
#define FCML_STF_NULL_TEST		{ NULL, NULL }

#include <fcml_types.h>
#include <string.h>

typedef void (*fcml_stf_test_function)(void);

typedef struct fcml_stf_test_case {
	fcml_string name;
	fcml_stf_test_function test_function;
} fcml_stf_test_case;

typedef struct fcml_stf_test_suite {
	fcml_string name;
	fcml_stf_test_function init_function;
	fcml_stf_test_function cleanup_function;
	fcml_stf_test_case *test_cases;
} fcml_stf_test_suite;

typedef struct fcml_stf_result_element {
	struct fcml_stf_result_element *next;
	fcml_int line;
	fcml_string file;
	fcml_string message;
	fcml_stf_test_case *test_case;
	fcml_stf_test_suite *suite;
} fcml_stf_result_element;

typedef struct fcml_stf_test_counter {
	fcml_int passed;
	fcml_int failed;
} fcml_stf_test_counter;

typedef struct fcml_stf_test_result {
	fcml_stf_result_element *first;
	fcml_stf_result_element *last;
	// Counters.
	fcml_stf_test_counter suites;
	fcml_stf_test_counter tests;
	fcml_stf_test_counter asserts;
} fcml_stf_test_result;

extern fcml_stf_test_result fcml_gl_stf_test_result;

/* Asserts */

void fcml_str_run_assert( fcml_bool condition, fcml_string file, fcml_int line, fcml_string message );

// Equals.
#define STF_ASSERT_EQUAL(actual, expected)		\
	( fcml_str_run_assert( (actual) == (expected), __FILE__, __LINE__, ("STF_ASSERT_EQUAL(" #actual "," #expected ")") ) )

// Not equal.
#define STF_ASSERT_NOT_EQUAL(actual, expected)		\
	( fcml_str_run_assert( (actual) != (expected), __FILE__, __LINE__, ("STF_ASSERT_NOT_EQUAL(" #actual "," #expected ")") ) )

// Boolean.
#define STF_ASSERT(condition)		\
	fcml_str_run_assert( (condition), __FILE__, __LINE__, ("STF_ASSERT(" #condition ")") )

// Not NULL.
#define STF_ASSERT_PTR_NOT_NULL(value)		\
	fcml_str_run_assert( ( value ) != NULL, __FILE__, __LINE__, ("STF_ASSERT_PTR_NOT_NULL(" #value ")") )

// Not NULL.
#define STF_ASSERT_PTR_NULL(value)		\
	fcml_str_run_assert( ( value ) == NULL, __FILE__, __LINE__, ("STF_ASSERT_PTR_NULL(" #value ")") )

// Fail immediate.
#define STF_FAIL(value)		\
	fcml_str_run_assert( FCML_FALSE, __FILE__, __LINE__, ("STF_FAIL()") )

// String equal.
#define STF_ASSERT_STRING_EQUAL(actual, expected)		\
	fcml_str_run_assert( (strcmp(actual,expected)==0), __FILE__, __LINE__, ("STF_ASSERT_STRING_EQUAL(" #actual "," #expected ")") )

void fcml_stf_run_tests( fcml_stf_test_suite **suite );

#endif /* FCML_STF_H_ */
