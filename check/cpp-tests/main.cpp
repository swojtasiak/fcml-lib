/*
 * main.cpp
 *
 *  Created on: Jul 5, 2014
 *      Author: tas
 */

#include <stdlib.h>

#include <fcml_stf.h>

#include "dialect_t.hpp"
#include "struct_wrapper_t.hpp"
#include "assembler_t.hpp"

fcml_stf_test_suite *fcml_arr_cpp_suites[] = {
    &fcml_si_cpp_dialect,
    &fcml_si_cpp_struct_wrapper,
    &fcml_si_cpp_assembler,
    FCML_STF_NULL_SUITE
};

int main(int argc, char **argv) {

    /* Run tests.*/
    fcml_bool result = fcml_stf_run_tests( FCML_TEXT("CPP wrappers tests"), fcml_arr_cpp_suites );

    exit( result ? 0 : 1 );
}


