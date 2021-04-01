/*
 * FCML - Free Code Manipulation Library.
 * Copyright (C) 2010-2021 Slawomir Wojtasiak
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

#ifndef FCML_STF_H_
#define FCML_STF_H_

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#if _WIN32 || __CYGWIN__
#define LIB_CALL_STF   __stdcall
#ifdef DLL_EXPORT
#define LIB_EXPORT_STF __declspec(dllexport)
#else
#ifdef LIBSTF_DLL_IMPORT
#define LIB_EXPORT_STF __declspec(dllimport)
#endif
#endif
#endif

#ifndef LIB_EXPORT_STF
#define LIB_EXPORT_STF
#endif

#ifndef LIB_CALL_STF
#define LIB_CALL_STF
#endif

#define FCML_STF_NULL_SUITE		NULL
#define FCML_STF_NULL_TEST		{ NULL, NULL }

#include <fcml_types.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef fcml_bool (*fcml_stf_test_init_function)(void);
typedef void (*fcml_stf_test_case_function)(void);

typedef struct fcml_stf_test_case {
	const fcml_string name;
	fcml_stf_test_case_function test_function;
} fcml_stf_test_case;

typedef struct fcml_stf_test_suite {
	const fcml_string name;
	fcml_stf_test_init_function init_function;
	fcml_stf_test_init_function cleanup_function;
	fcml_stf_test_case *test_cases;
} fcml_stf_test_suite;

typedef struct fcml_stf_result_element {
	struct fcml_stf_result_element *next;
	fcml_int line;
	const fcml_string file;
	const fcml_string message;
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
	/* Counters.*/
	fcml_stf_test_counter suites;
	fcml_stf_test_counter tests;
	fcml_stf_test_counter asserts;
} fcml_stf_test_result;

extern fcml_stf_test_result fcml_gl_stf_test_result;

/* Asserts */

fcml_bool LIB_CALL_STF LIB_EXPORT_STF fcml_str_run_assert(fcml_bool condition,
        const fcml_string file, fcml_int line, const fcml_string message);

/* Equals.*/
#define STF_ASSERT_EQUAL(actual, expected)		\
	(fcml_str_run_assert((actual) == (expected), __FILE__, __LINE__, \
	        ("STF_ASSERT_EQUAL(" #actual "," #expected ")")))

/* Not equal.*/
#define STF_ASSERT_NOT_EQUAL(actual, expected)		\
	(fcml_str_run_assert((actual) != (expected), __FILE__, __LINE__, \
	        ("STF_ASSERT_NOT_EQUAL(" #actual "," #expected ")")))

/* Boolean.*/
#define STF_ASSERT(condition)		\
	fcml_str_run_assert((condition), __FILE__, __LINE__, \
	        ("STF_ASSERT(" #condition ")"))

/* Not NULL.*/
#define STF_ASSERT_PTR_NOT_NULL(value)		\
	fcml_str_run_assert((value) != NULL, __FILE__, __LINE__, \
	        ("STF_ASSERT_PTR_NOT_NULL(" #value ")") )

/* Not NULL.*/
#define STF_ASSERT_PTR_NULL(value)		\
	fcml_str_run_assert((value) == NULL, __FILE__, __LINE__, \
	        ("STF_ASSERT_PTR_NULL(" #value ")"))

/* Fail immediately. */
#define STF_FAIL(value)		\
	fcml_str_run_assert( FCML_FALSE, __FILE__, __LINE__, \
	        ("STF_FAIL(" #value ")"))

/* String equal.*/
#define STF_ASSERT_STRING_EQUAL(actual, expected)		\
	fcml_str_run_assert( (strcmp(actual,expected)==0), __FILE__, __LINE__, \
	        ("STF_ASSERT_STRING_EQUAL(" #actual "," #expected ")"))

fcml_bool LIB_CALL_STF LIB_EXPORT_STF fcml_stf_run_tests(
        const fcml_string test_name, fcml_stf_test_suite **suite);

#ifdef __cplusplus
}
#endif

#endif /* FCML_STF_H_ */
