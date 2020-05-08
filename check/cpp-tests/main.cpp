/*
 * FCML - Free Code Manipulation Library.
 * Copyright (C) 2010-2020 Slawomir Wojtasiak
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

#include <stdlib.h>

#include <fcml_stf.h>

// Include mnemonics and register definitions into the destination image file.
#include <fcml_registers.cpp>
#include <fcml_gas_mnemonics.cpp>
#include <fcml_intel_mnemonics.cpp>

#include "dialect_t.hpp"
#include "common_t.hpp"
#include "assembler_t.hpp"
#include "disassembler_t.hpp"
#include "errors_t.hpp"
#include "parser_t.hpp"

fcml_stf_test_suite *fcml_arr_cpp_suites[] = {
    &fcml_si_cpp_dialect,
    &fcml_si_cpp_common,
    &fcml_si_cpp_assembler,
    &fcml_si_cpp_disassembler,
    &fcml_si_cpp_errors,
    &fcml_si_cpp_parser,
    &fcml_si_cpp_assembler,
    FCML_STF_NULL_SUITE
};

#include <fcml_common.hpp>

using namespace fcml;

int main(int argc, char **argv) {

    /* Run tests.*/

    fcml_bool result = fcml_stf_run_tests( FCML_TEXT("CPP wrappers tests"), fcml_arr_cpp_suites );

    exit( result ? 0 : 1 );
}


