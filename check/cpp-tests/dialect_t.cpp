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

/* Test suite initialization. */

#include "dialect_t.hpp"

#include <fcml_common.hpp>
#include <fcml_intel_dialect.hpp>

using namespace fcml;

class DialectExtractor: public DialectAware {
};

fcml_bool fcml_tf_cpp_dialect_suite_init(void) {
    return FCML_TRUE;
}

fcml_bool fcml_tf_cpp_dialect_suite_cleanup(void) {
    return FCML_TRUE;
}

void fcml_tf_cpp_init_intel(void) {
    IntelDialect intel;
    DialectExtractor extractor;
    STF_ASSERT_PTR_NOT_NULL( extractor.extractDialect( intel ) );
    IntelDialect *intelPTR = new IntelDialect(FCML_INTEL_DIALECT_CF_DEFAULT);
    STF_ASSERT_PTR_NOT_NULL( extractor.extractDialect( *intelPTR ) );
    delete intelPTR;
}

void fcml_tf_cpp_init_gas(void) {
}

fcml_stf_test_case fcml_ti_cpp_dialect[] = {
    { "fcml_tf_cpp_init_intel", fcml_tf_cpp_init_intel },
    { "fcml_tf_cpp_init_gas", fcml_tf_cpp_init_gas },
    FCML_STF_NULL_TEST
};

fcml_stf_test_suite fcml_si_cpp_dialect = {
    "suite-fcml-cpp-dialect", fcml_tf_cpp_dialect_suite_init, fcml_tf_cpp_dialect_suite_cleanup, fcml_ti_cpp_dialect
};
