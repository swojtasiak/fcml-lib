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

#include "common_t.hpp"

#include <fcml_errors.h>
#include <fcml_common.hpp>
#include <fcml_errors.hpp>

using namespace fcml;

struct fcml_st_example_strcture {
    fcml_int value;
};

fcml_bool fcml_tf_cpp_common_suite_init(void) {
    return FCML_TRUE;
}

fcml_bool fcml_tf_cpp_common_suite_cleanup(void) {
    return FCML_TRUE;
}

/**** Structure Wrapper ****/

class ExampleStructureWrapper : public StructureWrapper<fcml_st_example_strcture> {
public:
    ExampleStructureWrapper() {}
    ExampleStructureWrapper( const ExampleStructureWrapper &cpy ) : StructureWrapper(cpy) {}
    ExampleStructureWrapper( fcml_st_example_strcture *wrapped ) : StructureWrapper(wrapped) {}
    ExampleStructureWrapper( fcml_st_example_strcture &wrapped ) : StructureWrapper(wrapped) {}
};

void fcml_tf_cpp_structure_wrapper(void) {

    // Default constructor.
    ExampleStructureWrapper wrapper;
    STF_ASSERT_PTR_NOT_NULL( &wrapper.getStruct() );

    fcml_st_example_strcture &value = wrapper.getStruct();
    value.value = 5;

    // Copy constructor.
    ExampleStructureWrapper wrapperCopy(wrapper);
    STF_ASSERT_EQUAL( wrapper.getStruct().value, wrapperCopy.getStruct().value );

    // The internal structure has to be copied, so pointers must differ.
    STF_ASSERT_NOT_EQUAL( &wrapper.getStruct(), &wrapperCopy.getStruct() );

    // Wrap existing structure without allocating the new one.
    fcml_st_example_strcture existing;
    existing.value = 128;

    // By reference, so the structure has to be copied anyway.
    ExampleStructureWrapper existingWrapperRef(existing);
    STF_ASSERT_NOT_EQUAL( &existingWrapperRef.getStruct(), &existing );

    // By pointer, so the structure has to be just wrapped. In this case
    // the object is not an owner of the provided structure, so dectructor will not
    // free it when the object is being destroyed.
    ExampleStructureWrapper existingWrapperPtr(&existing);
    STF_ASSERT_EQUAL( &existingWrapperPtr.getStruct(), &existing );
}

fcml_stf_test_case fcml_ti_cpp_common[] = {
    { "fcml_tf_cpp_structure_wrapper", fcml_tf_cpp_structure_wrapper },
    FCML_STF_NULL_TEST
};

fcml_stf_test_suite fcml_si_cpp_common = {
    "suite-fcml-cpp-common", fcml_tf_cpp_common_suite_init, fcml_tf_cpp_common_suite_cleanup, fcml_ti_cpp_common
};
