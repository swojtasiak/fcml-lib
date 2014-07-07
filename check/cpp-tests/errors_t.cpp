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

/* Test suite initialization. */

#include "errors_t.hpp"

#include <fcml_common.hpp>
#include <fcml_errors.hpp>

using namespace fcml;

fcml_bool fcml_tf_cpp_errors_suite_init(void) {
    return FCML_TRUE;
}

fcml_bool fcml_tf_cpp_errors_suite_cleanup(void) {
    return FCML_TRUE;
}

void fcml_tf_cpp_errors(void) {

    fcml_st_ceh_error_info info1;
    info1.code = FCML_CEH_GEC_FEATURE_NOT_SUPPORTED;
    info1.level = FCML_EN_CEH_EL_WARN;
    info1.message = FCML_TEXT("Some error1");

    fcml_st_ceh_error_info info2;
    info2.code = FCML_CEH_GEC_FEATURE_NOT_SUPPORTED;
    info2.level = FCML_EN_CEH_EL_ERROR;
    info2.message = FCML_TEXT("Some error2");

    fcml_st_ceh_error_info info3;
    info3.code = FCML_CEH_GEC_FEATURE_NOT_SUPPORTED;
    info3.level = FCML_EN_CEH_EL_ERROR;
    info3.message = FCML_TEXT("Some error3");

    fcml_st_ceh_error_container errors;
    errors.errors = &info1;
    errors.last_error = &info3;

    info3.next_error = NULL;
    info2.next_error = &info3;
    info1.next_error = &info2;

    // Do not copy, just wrap.

    ErrorContainer container(&errors);

    fcml_st_ceh_error_container *errorsPtr = &container.getStruct();

    // Must be the same
    STF_ASSERT_EQUAL( errorsPtr, &errors );
    STF_ASSERT_EQUAL( errorsPtr->errors, errors.errors );
    STF_ASSERT_EQUAL( errorsPtr->last_error, errors.last_error );

    if( !container.isEmpty() ) {
        ErrorInfo &errorInfo = container.getFirstError();
        STF_ASSERT_EQUAL( &info1, &errorInfo.getStruct() );
        // We can always copy given error info.
        ErrorInfo copyPtr(errorInfo);
        STF_ASSERT_STRING_EQUAL( copyPtr.getMessage(), FCML_TEXT("Some error1") );
        STF_ASSERT_EQUAL( copyPtr.getLevel(), FCML_EN_CEH_EL_WARN );
        STF_ASSERT_EQUAL( copyPtr.getCode(), FCML_CEH_GEC_FEATURE_NOT_SUPPORTED );
        STF_ASSERT_NOT_EQUAL( (void*)copyPtr.getMessage(), (void*)errorInfo.getMessage() );
        STF_ASSERT_NOT_EQUAL( &copyPtr.getStruct(), &errorInfo.getStruct() );
    }

    // Iterating over the errors.
    if( !container.isEmpty() ) {
        STF_ASSERT_EQUAL( container.getSize(), 3 );
        for( fcml_usize i = 0; i < container.getSize(); i++ ) {
            ErrorInfo &info = container[i];
            switch(i) {
            case 0:
                STF_ASSERT_STRING_EQUAL( info.getMessage(), FCML_TEXT("Some error1") );
                STF_ASSERT_EQUAL( &info.getStruct(), &info1 );
                break;
            case 1:
                STF_ASSERT_STRING_EQUAL( info.getMessage(), FCML_TEXT("Some error2") );
                STF_ASSERT_EQUAL( &info.getStruct(), &info2 );
                break;
            case 2:
                STF_ASSERT_STRING_EQUAL( info.getMessage(), FCML_TEXT("Some error3") );
                STF_ASSERT_EQUAL( &info.getStruct(), &info3 );
                break;
            }
        }
    }

    // Now build new container using reference to the original structure, so the structure is going to bo copied now.
    ErrorContainer containerRef(errors);

    errorsPtr = &containerRef.getStruct();

    // Must not be the same
    STF_ASSERT_NOT_EQUAL( errorsPtr, &errors );
    STF_ASSERT_NOT_EQUAL( errorsPtr->errors, errors.errors );
    STF_ASSERT_NOT_EQUAL( errorsPtr->last_error, errors.last_error );

    // Iterate over the error infos.
    STF_ASSERT( !containerRef.isEmpty() );

    if( !containerRef.isEmpty() ) {

        ErrorInfo &errorInfo = containerRef.getFirstError();
        STF_ASSERT_STRING_EQUAL( errorInfo.getMessage(), FCML_TEXT("Some error1") );
        STF_ASSERT_EQUAL( errorInfo.getLevel(), FCML_EN_CEH_EL_WARN );
        STF_ASSERT_EQUAL( errorInfo.getCode(), FCML_CEH_GEC_FEATURE_NOT_SUPPORTED );
        // Error message has to be also duplicated in case of reference based container.
        STF_ASSERT_NOT_EQUAL( (void*)info1.message, (void*)errorInfo.getMessage() );

        // We can always copy given error info.
        ErrorInfo copy(errorInfo);
        STF_ASSERT_STRING_EQUAL( copy.getMessage(), FCML_TEXT("Some error1") );
        STF_ASSERT_EQUAL( copy.getLevel(), FCML_EN_CEH_EL_WARN );
        STF_ASSERT_EQUAL( copy.getCode(), FCML_CEH_GEC_FEATURE_NOT_SUPPORTED );
        STF_ASSERT_NOT_EQUAL( (void*)copy.getMessage(), (void*)errorInfo.getMessage() );
        STF_ASSERT_NOT_EQUAL( &copy.getStruct(), &errorInfo.getStruct() );
    }

}

fcml_stf_test_case fcml_ti_cpp_errors[] = {
    { "fcml_tf_cpp_errors", fcml_tf_cpp_errors },
    FCML_STF_NULL_TEST
};

fcml_stf_test_suite fcml_si_cpp_errors = {
    "suite-fcml-cpp-errors", fcml_tf_cpp_errors_suite_init, fcml_tf_cpp_errors_suite_cleanup, fcml_ti_cpp_errors
};
