/*
 * FCML - Free Code Manipulation Library.
 * Copyright (C) 2010-2019 Slawomir Wojtasiak
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

#include "avx512_t.hpp"

#include <fcml_common.hpp>
#include <fcml_disassembler.hpp>
#include <fcml_renderer.hpp>
#include <fcml_registers.hpp>
#include <fcml_intel_dialect.hpp>
#include <fcml_intel_dialect.hpp>
#include <fcml_stateful_disassembler.hpp>
#include <fcml_intel_mnemonics.hpp>

using namespace fcml;
using namespace fcml::intel;

fcml_bool fcml_tf_cpp_avx152_suite_init(void) {
    return FCML_TRUE;
}

fcml_bool fcml_tf_cpp_acx512_suite_cleanup(void) {
    return FCML_TRUE;
}

void fcml_tf_cpp_disassemble_avx512_disp8_bcast(void) {


    fcml_uint8_t code[] = {0x62, 0xf2, 0xed, 0x58, 0x0d, 0x4c, 0x24, 0x08};

    try {

        IntelDialect dialect;

        Disassembler disassembler( dialect );

        DisassemblerContext ctx( code , sizeof( code ) );
        ctx.setIP(0x401000);
        ctx.setOperatingMode(EntryPoint::OM_64_BIT);
        ctx.setAddressSizeAttribute(64);
        ctx.setOperandSizeAttribute(64);

        DisassemblerResult result;

        disassembler.disassemble( ctx, result );

        const Instruction &instruction = result.getInstruction();
        const InstructionDetails &details = result.getInstructionDetails();

        STF_ASSERT( instruction.getMnemonic() == M_VPERMILPD );

        STF_ASSERT_EQUAL(instruction[2].getAddress().getEffectiveAddress().getDisplacement(), 64);
        STF_ASSERT_EQUAL(instruction[2].getDecorators().getBcast(), fcml::Nullable<fcml_uint8_t>(8, true));
        STF_ASSERT_EQUAL(details.getModRmDetails().getN(), fcml::Nullable<fcml_uint32_t>(8, true));

        Renderer renderer( dialect );

        RenderConfig config;

        fcml_cstring instructionMnemonic;

        renderer.render( config, result, instructionMnemonic );

        STF_ASSERT_STRING_EQUAL( instructionMnemonic.c_str(), FCML_TEXT("vpermilpd zmm1,zmm2,mmword ptr [rsp+64]{1to8}") );

    } catch( BaseException &exc ) {
        STF_FAIL("Exception while disassembling the code.");
    }
}

fcml_stf_test_case fcml_ti_cpp_avx512[] = {
    { "fcml_tf_cpp_disassemble_avx512_disp8_bcast", fcml_tf_cpp_disassemble_avx512_disp8_bcast },
    FCML_STF_NULL_TEST
};

fcml_stf_test_suite fcml_si_cpp_avx512 = {
    "suite-fcml-cpp-avx512", fcml_tf_cpp_avx152_suite_init, fcml_tf_cpp_acx512_suite_cleanup, fcml_ti_cpp_avx512
};



