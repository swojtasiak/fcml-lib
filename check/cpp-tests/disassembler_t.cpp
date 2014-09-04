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

#include "disassembler_t.hpp"

#include <fcml_common.hpp>
#include <fcml_disassembler.hpp>
#include <fcml_renderer.hpp>
#include <fcml_registers.hpp>
#include <fcml_intel_dialect.hpp>
#include <fcml_gas_dialect.hpp>
#include <fcml_stateful_disassembler.hpp>
#include <fcml_gas_mnemonics.hpp>

using namespace fcml;
using namespace fcml::gas;

fcml_bool fcml_tf_cpp_disassembler_suite_init(void) {
    return FCML_TRUE;
}

fcml_bool fcml_tf_cpp_disassembler_suite_cleanup(void) {
    return FCML_TRUE;
}

void fcml_tf_cpp_disassemble(void) {

	fcml_uint8_t code[] = {0x80, 0x54, 0x01, 0x02, 0x03};

	try {

		IntelDialect dialect;

		Disassembler disassembler( dialect );

		DisassemblerContext ctx( code , sizeof( code ) );
		ctx.setIP(0x401000);
		ctx.setOperatingMode(EntryPoint::OM_32_BIT);

		DisassemblerResult result;

		disassembler.disassemble( ctx, result );

		const Instruction &instruction = result.getInstruction();

		STF_ASSERT( instruction.getMnemonic() == M_ADC );

		Renderer renderer( dialect );

		RenderConfig config;

		fcml_cstring instructionMnemonic;

		renderer.render( config, result, instructionMnemonic );

		STF_ASSERT_STRING_EQUAL( instructionMnemonic.c_str(), FCML_TEXT("adc byte ptr [ecx+eax+2],3") );

	} catch( BaseException &exc ) {
		STF_FAIL("Exception while disassembling the code.");
	}

}

/* A 64-bit GDB dump used as an example.
Dump of assembler code for function main(int, char**):
0x0000000000404ddc <+0>:     55              push   %rbp
0x0000000000404ddd <+1>:     48 89 e5        mov    %rsp,%rbp
0x0000000000404de0 <+4>:     48 83 ec 20     sub    $0x20,%rsp
0x0000000000404de4 <+8>:     89 7d ec        mov    %edi,-0x14(%rbp)
0x0000000000404de7 <+11>:    48 89 75 e0     mov    %rsi,-0x20(%rbp)
0x0000000000404deb <+15>:    be 60 d2 62 00  mov    $0x62d260,%esi
0x0000000000404df0 <+20>:    bf e8 db 41 00  mov    $0x41dbe8,%edi
0x0000000000404df5 <+25>:    e8 1f 89 01 00  callq  0x41d719
*/

fcml_uint8_t fcml_iarr_instruction_buffer_binary_code[] = {
    0x55,
    0x48, 0x89, 0xe5,
    0x48, 0x83, 0xec, 0x20,
    0x89, 0x7d, 0xec,
    0x48, 0x89, 0x75, 0xe0,
    0xbe, 0x60, 0xd2, 0x62, 0x00,
    0xbf, 0xe8, 0xdb, 0x41, 0x00,
    0xe8, 0x1f, 0x89, 0x01, 0x00
};

void fcml_tf_cpp_disassemble_instruction_buffer_disassemble_only(void) {

    try {

        GASDialect dialect;

        Disassembler disassembler( dialect );

        DisassemblerContext ctx( fcml_iarr_instruction_buffer_binary_code , sizeof( fcml_iarr_instruction_buffer_binary_code ) );
        ctx.setIP(0x404ddc);
        ctx.setOperatingMode(EntryPoint::OM_64_BIT);

        StatefulDisassembler disas( disassembler, ctx, true );

        Instruction instruction;

        disas >> instruction;
        STF_ASSERT( instruction.getMnemonic() == M_PUSH );
        disas >> instruction;
        STF_ASSERT( instruction.getMnemonic() == M_MOV );

    } catch( BaseException &exc ) {
        STF_FAIL("Exception while disassembling the code.");
    }

}

void fcml_tf_cpp_disassemble_instruction_buffer_disassemble_render(void) {

    try {

        GASDialect dialect;

        Disassembler disassembler( dialect );

        DisassemblerContext ctx( fcml_iarr_instruction_buffer_binary_code , sizeof( fcml_iarr_instruction_buffer_binary_code ) );
        ctx.setIP(0x404ddc);
        ctx.setOperatingMode(EntryPoint::OM_64_BIT);

        StatefulDisassembler disas( disassembler, ctx, true );

        fcml_cstring instruction;

        disas >> instruction;
        STF_ASSERT( instruction == FCML_TEXT( "push %rbp" ) );
        disas >> instruction;
        STF_ASSERT( instruction == FCML_TEXT( "mov %rsp,%rbp" ) );
        disas >> instruction;
        STF_ASSERT( instruction == FCML_TEXT( "sub $32,%rsp" ) );
        disas >> instruction;
        STF_ASSERT( instruction == FCML_TEXT( "mov %edi,-20(%ebp)" ) );
        disas >> instruction;
        STF_ASSERT( instruction == FCML_TEXT( "mov %rsi,-32(%ebp)" ) );
        disas >> instruction;
        STF_ASSERT( instruction == FCML_TEXT( "mov $6476384,%esi" ) );
        disas >> instruction;
        STF_ASSERT( instruction == FCML_TEXT( "mov $4316136,%edi" ) );
        disas >> instruction;
        STF_ASSERT( instruction == FCML_TEXT( "callq 0x000000000041d719" ) );

    } catch( BaseException &exc ) {
        STF_FAIL("Exception while disassembling the code.");
    }

}

void fcml_tf_cpp_disassemble_instruction_buffer_disassemble_only_stream(void) {

    try {

        GASDialect dialect;

        Disassembler disassembler( dialect );

        DisassemblerContext ctx( fcml_iarr_instruction_buffer_binary_code , sizeof( fcml_iarr_instruction_buffer_binary_code ) );
        ctx.setIP(0x404ddc);
        ctx.setOperatingMode(EntryPoint::OM_64_BIT);

        StatefulDisassembler disas( disassembler, ctx, true );

        fcml_costream ostream;

        disas >> ostream;
        disas >> ostream;

        fcml_cstring src = ostream.str();

#if defined(_WIN32)
		STF_ASSERT( src == _FT("push %rbp\r\nmov %rsp,%rbp\r\n") );
#else
        STF_ASSERT( src == _FT("push %rbp\nmov %rsp,%rbp\n") );
#endif

    } catch( BaseException &exc ) {
        STF_FAIL("Exception while disassembling the code.");
    }

}


fcml_stf_test_case fcml_ti_cpp_disassembler[] = {
    { "fcml_tf_cpp_disassemble", fcml_tf_cpp_disassemble },
    { "fcml_tf_cpp_disassemble_instruction_buffer_disassemble_only", fcml_tf_cpp_disassemble_instruction_buffer_disassemble_only },
    { "fcml_tf_cpp_disassemble_instruction_buffer_disassemble_render", fcml_tf_cpp_disassemble_instruction_buffer_disassemble_render },
    { "fcml_tf_cpp_disassemble_instruction_buffer_disassemble_only_stream", fcml_tf_cpp_disassemble_instruction_buffer_disassemble_only_stream },
    FCML_STF_NULL_TEST
};

fcml_stf_test_suite fcml_si_cpp_disassembler = {
    "suite-fcml-cpp-disassembler", fcml_tf_cpp_disassembler_suite_init, fcml_tf_cpp_disassembler_suite_cleanup, fcml_ti_cpp_disassembler
};
