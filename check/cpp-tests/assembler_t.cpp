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

#include "assembler_t.hpp"

#include <fcml_common.hpp>
#include <fcml_assembler.hpp>

using namespace fcml;

fcml_bool fcml_tf_cpp_assembler_suite_init(void) {
    return FCML_TRUE;
}

fcml_bool fcml_tf_cpp_assembler_suite_cleanup(void) {
    return FCML_TRUE;
}

void fcml_tf_cpp_assemble(void) {

    try {

        IntelDialect intel;

        AssemblerContext ctx;

        EntryPoint &entryPoint = ctx.GetEntryPoint();
        entryPoint.setOpMode(FCML_OM_32_BIT);
        entryPoint.setIp(0x401000);

        AssemblerConf &config = ctx.GetAssemblerConf();
        config.setEnableErrorMessages(true);

        Assembler assembler(intel);

    } catch( BaseException &exc ) {
        STF_FAIL("Exception while assembling the code.");
    }
}

fcml_stf_test_case fcml_ti_cpp_assembler[] = {
    { "fcml_tf_cpp_assemble", fcml_tf_cpp_assemble },
    FCML_STF_NULL_TEST
};

fcml_stf_test_suite fcml_si_cpp_assembler = {
    "suite-fcml-cpp-assembler", fcml_tf_cpp_assembler_suite_init, fcml_tf_cpp_assembler_suite_cleanup, fcml_ti_cpp_assembler
};
