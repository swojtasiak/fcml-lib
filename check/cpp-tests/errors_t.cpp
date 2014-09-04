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

    ErrorContainer container;

    ErrorTypeConverter::convert( errors, container );

    if( !container.isEmpty() ) {
        ErrorInfo &errorInfo = container.getFirstError();
        STF_ASSERT_EQUAL( errorInfo.getMessage(), fcml_cstring( FCML_TEXT("Some error1") ) );
        STF_ASSERT_EQUAL( errorInfo.getLevel(), ErrorInfo::EL_WARN );
        STF_ASSERT_EQUAL( errorInfo.getCode(), FCML_CEH_GEC_FEATURE_NOT_SUPPORTED );
    }

    // Iterating over the errors.
    if( !container.isEmpty() ) {
        STF_ASSERT_EQUAL( container.getSize(), 3 );
        for( fcml_usize i = 0; i < container.getSize(); i++ ) {
            const ErrorInfo &info = container[i];
            switch(i) {
            case 0:
                STF_ASSERT_EQUAL( info.getMessage(), FCML_TEXT("Some error1") );
                break;
            case 1:
                STF_ASSERT_EQUAL( info.getMessage(), FCML_TEXT("Some error2") );
                break;
            case 2:
                STF_ASSERT_EQUAL( info.getMessage(), FCML_TEXT("Some error3") );
                break;
            }
        }
    }

}

fcml_stf_test_case fcml_ti_cpp_errors[] = {
    { "fcml_tf_cpp_errors", fcml_tf_cpp_errors },
    FCML_STF_NULL_TEST
};

fcml_stf_test_suite fcml_si_cpp_errors = {
    "suite-fcml-cpp-errors", fcml_tf_cpp_errors_suite_init, fcml_tf_cpp_errors_suite_cleanup, fcml_ti_cpp_errors
};
