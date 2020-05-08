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
#include <string.h>

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

void fcml_tf_cpp_disassembleshould_convert_instruction_details_correctly(void) {

    fcml_st_instruction_details details = {};

    fcml_st_prefixes_details *prefixes_details = &(details.prefixes_details);
    prefixes_details->B = 1;
    prefixes_details->L = 2;
    prefixes_details->L_prim = 3;
    prefixes_details->R = 4;
    prefixes_details->R_prim = 5;
    prefixes_details->V_prim = 6;
    prefixes_details->W = 7;
    prefixes_details->X = 8;
    prefixes_details->aaa = 9;
    prefixes_details->avx_first_byte = 10;
    prefixes_details->b = 1;
    prefixes_details->is_avx = FCML_TRUE;
    prefixes_details->is_branch = FCML_TRUE;
    prefixes_details->is_evex = FCML_TRUE;
    prefixes_details->is_lock = FCML_TRUE;
    prefixes_details->is_nobranch = FCML_TRUE;
    prefixes_details->is_rep = FCML_TRUE;
    prefixes_details->is_repne = FCML_TRUE;
    prefixes_details->is_rex = FCML_TRUE;
    prefixes_details->is_vex = FCML_TRUE;
    prefixes_details->is_xacquire = FCML_TRUE;
    prefixes_details->is_xop = FCML_TRUE;
    prefixes_details->is_xrelease = FCML_TRUE;
    prefixes_details->mmmm = 12;
    prefixes_details->pp = 13;

    fcml_st_instruction_prefix *prefix = &(prefixes_details->prefixes[0]);
    prefix->prefix = 0x62;
    prefix->avx_bytes[0] = 0x31;
    prefix->avx_bytes[1] = 0x40;
    prefix->avx_bytes[2] = 0x64;
    prefix->prefix_type = FCML_PT_EVEX;
    prefix->mandatory_prefix = FCML_TRUE;

    prefixes_details->prefixes_bytes_count = 1;
    prefixes_details->prefixes_count = 8;
    prefixes_details->vvvv = 14;
    prefixes_details->z = 1;

    fcml_st_decoded_modrm_details *modrm_details = &(details.modrm_details);
    modrm_details->displacement.N.value = 8;
    modrm_details->displacement.N.is_not_null = FCML_TRUE;
    modrm_details->displacement.displacement.size = 32;
    modrm_details->displacement.displacement.int32= 0x12345678;
    modrm_details->is_modrm = FCML_TRUE;
    modrm_details->is_rip = FCML_TRUE;
    modrm_details->modrm = 0x40;
    modrm_details->sib.value = 0x20;
    modrm_details->sib.is_not_null = FCML_TRUE;

    details.operand_details[0].access_mode  = FCML_AM_READ_WRITE;
    details.operand_details[1].access_mode  = FCML_AM_READ;
    details.operand_details[2].access_mode  = FCML_AM_WRITE;
    details.operand_details[3].access_mode  = FCML_AM_READ_WRITE;
    details.operand_details[4].access_mode  = FCML_AM_READ_WRITE;

    details.is_shortcut = FCML_TRUE;
    details.is_pseudo_op = FCML_TRUE;
    details.instruction_code[0] = 0x01;
    details.instruction_code[FCML_INSTRUCTION_SIZE - 1] = 0xFF;

    details.instruction_size = 15;
    details.opcode_field_s_bit = FCML_TRUE;
    details.opcode_field_w_bit = FCML_TRUE;
    details.instruction = F_VAESDEC;
    details.pseudo_op = FP_DB;

    details.pseudo_op = FP_DB;
    details.addr_mode = 0x1111;
    details.instruction_group = FCML_AMT_GPI;
    details.tuple_type = FCML_TT_M128;

    InstructionDetails destDetails;

    DisassemblerTypeConverter::convert(details, destDetails);

    STF_ASSERT_EQUAL(destDetails.getPrefixesDetails().getB(), 1);
    STF_ASSERT_EQUAL(destDetails.getPrefixesDetails().getL(), 2);
    STF_ASSERT_EQUAL(destDetails.getPrefixesDetails().getLPrim(), 3);
    STF_ASSERT_EQUAL(destDetails.getPrefixesDetails().getR(), 4);
    STF_ASSERT_EQUAL(destDetails.getPrefixesDetails().getRPrim(), 5);
    STF_ASSERT_EQUAL(destDetails.getPrefixesDetails().getVPrim(), 6);
    STF_ASSERT_EQUAL(destDetails.getPrefixesDetails().getW(), 7);
    STF_ASSERT_EQUAL(destDetails.getPrefixesDetails().getX(), 8);
    STF_ASSERT_EQUAL(destDetails.getPrefixesDetails().getAaa(), 9);
    STF_ASSERT_EQUAL(destDetails.getPrefixesDetails().getAvxFirstByte(), 10);
    STF_ASSERT_EQUAL(destDetails.getPrefixesDetails().getBcast(), true);
    STF_ASSERT_EQUAL(destDetails.getPrefixesDetails().isAvx(), true);
    STF_ASSERT_EQUAL(destDetails.getPrefixesDetails().isBranch(), true);
    STF_ASSERT_EQUAL(destDetails.getPrefixesDetails().isEvex(), true);
    STF_ASSERT_EQUAL(destDetails.getPrefixesDetails().isLock(), true);
    STF_ASSERT_EQUAL(destDetails.getPrefixesDetails().isNobranch(), true);
    STF_ASSERT_EQUAL(destDetails.getPrefixesDetails().isRep(), true);
    STF_ASSERT_EQUAL(destDetails.getPrefixesDetails().isRepne(), true);
    STF_ASSERT_EQUAL(destDetails.getPrefixesDetails().isRex(), true);
    STF_ASSERT_EQUAL(destDetails.getPrefixesDetails().isVex(), true);
    STF_ASSERT_EQUAL(destDetails.getPrefixesDetails().isXacquire(), true);
    STF_ASSERT_EQUAL(destDetails.getPrefixesDetails().isXop(), true);
    STF_ASSERT_EQUAL(destDetails.getPrefixesDetails().isXrelease(), true);
    STF_ASSERT_EQUAL(destDetails.getPrefixesDetails().getMmmm(), 12);
    STF_ASSERT_EQUAL(destDetails.getPrefixesDetails().getPp(), 13);
    STF_ASSERT_EQUAL(destDetails.getPrefixesDetails().getPrefixesBytesCount(), 1);
    STF_ASSERT_EQUAL(destDetails.getPrefixesDetails().getPrefixesCount(), 8);
    STF_ASSERT_EQUAL(destDetails.getPrefixesDetails().getVvvv(), 14);
    STF_ASSERT_EQUAL(destDetails.getPrefixesDetails().getZ(), true);

    STF_ASSERT_EQUAL(destDetails.getPrefixesDetails().getPrefixes(0).getPrefix(), 0x62);
    STF_ASSERT_EQUAL(destDetails.getPrefixesDetails().getPrefixes(0).getAvxBytes()[0], 0x31);
    STF_ASSERT_EQUAL(destDetails.getPrefixesDetails().getPrefixes(0).getAvxBytes()[1], 0x40);
    STF_ASSERT_EQUAL(destDetails.getPrefixesDetails().getPrefixes(0).getAvxBytes()[2], 0x64);
    STF_ASSERT_EQUAL(destDetails.getPrefixesDetails().getPrefixes(0).getPrefixType(), InstructionPrefixDetails::PT_EVEX);
    STF_ASSERT_EQUAL(destDetails.getPrefixesDetails().getPrefixes(0).isMandatoryPrefix(), true);

    DecodedModRMDetails &modrmDetails = destDetails.getModRmDetails();
    STF_ASSERT(modrmDetails.getN() == Nullable<fcml_uint32_t>(8));
    STF_ASSERT(modrmDetails.getDisplacement() == Integer(fcml_int32_t(0x12345678)));
    STF_ASSERT(modrmDetails.getModRM() == Nullable<fcml_uint8_t>(0x40));
    STF_ASSERT(modrmDetails.isRip());
    STF_ASSERT(modrmDetails.getSib() == Nullable<fcml_uint8_t>(0x20));

    STF_ASSERT_EQUAL(destDetails.getOperandDetails(0).getAccessMode(), OperandDetails::AM_READ_WRITE);
    STF_ASSERT_EQUAL(destDetails.getOperandDetails(1).getAccessMode(), OperandDetails::AM_READ);
    STF_ASSERT_EQUAL(destDetails.getOperandDetails(2).getAccessMode(), OperandDetails::AM_WRITE);
    STF_ASSERT_EQUAL(destDetails.getOperandDetails(3).getAccessMode(), OperandDetails::AM_READ_WRITE);
    STF_ASSERT_EQUAL(destDetails.getOperandDetails(4).getAccessMode(), OperandDetails::AM_READ_WRITE);

    STF_ASSERT(destDetails.isShortcut());
    STF_ASSERT(destDetails.isPseudoOp());
    STF_ASSERT_EQUAL(destDetails.getInstructionCode()[0], 0x01);
    STF_ASSERT_EQUAL(destDetails.getInstructionCode()[FCML_INSTRUCTION_SIZE - 1], 0xFF);
    STF_ASSERT_EQUAL(destDetails.getInstructionSize(), 15);
    STF_ASSERT(destDetails.isOpcodeFieldSBit());
    STF_ASSERT(destDetails.isOpcodeFieldWBit());
    STF_ASSERT_EQUAL(destDetails.getInstruction(), F_VAESDEC);
    STF_ASSERT_EQUAL(destDetails.getPseudoOp(), FP_DB);
    STF_ASSERT(destDetails.getAddrMode() == 0x1111);
    STF_ASSERT(destDetails.getInstructionGroup() == FCML_AMT_GPI);
    STF_ASSERT(destDetails.getTupleType() == FCML_TT_M128);

    fcml_st_instruction_details det = {};

    DisassemblerTypeConverter::convert(destDetails, det);

    prefixes_details = &(det.prefixes_details);
    STF_ASSERT_EQUAL(prefixes_details->B, 1);
    STF_ASSERT_EQUAL(prefixes_details->L, 2);
    STF_ASSERT_EQUAL(prefixes_details->L_prim, 3);
    STF_ASSERT_EQUAL(prefixes_details->R, 4);
    STF_ASSERT_EQUAL(prefixes_details->R_prim, 5);
    STF_ASSERT_EQUAL(prefixes_details->V_prim, 6);
    STF_ASSERT_EQUAL(prefixes_details->W, 7);
    STF_ASSERT_EQUAL(prefixes_details->X, 8);
    STF_ASSERT_EQUAL(prefixes_details->aaa, 9);
    STF_ASSERT_EQUAL(prefixes_details->avx_first_byte, 10);
    STF_ASSERT(prefixes_details->b);
    STF_ASSERT(prefixes_details->is_avx);
    STF_ASSERT(prefixes_details->is_branch);
    STF_ASSERT(prefixes_details->is_evex);
    STF_ASSERT(prefixes_details->is_lock);
    STF_ASSERT(prefixes_details->is_nobranch);
    STF_ASSERT(prefixes_details->is_rep);
    STF_ASSERT(prefixes_details->is_repne);
    STF_ASSERT(prefixes_details->is_rex);
    STF_ASSERT(prefixes_details->is_vex);
    STF_ASSERT(prefixes_details->is_xacquire);
    STF_ASSERT(prefixes_details->is_xop);
    STF_ASSERT(prefixes_details->is_xrelease);
    STF_ASSERT_EQUAL(prefixes_details->mmmm, 12);
    STF_ASSERT_EQUAL(prefixes_details->pp, 13);

    prefix = &(prefixes_details->prefixes[0]);
    STF_ASSERT_EQUAL(prefix->prefix, 0x62);
    STF_ASSERT_EQUAL(prefix->avx_bytes[0], 0x31);
    STF_ASSERT_EQUAL(prefix->avx_bytes[1], 0x40);
    STF_ASSERT_EQUAL(prefix->avx_bytes[2], 0x64);
    STF_ASSERT_EQUAL(prefix->prefix_type, FCML_PT_EVEX);
    STF_ASSERT_EQUAL(prefix->mandatory_prefix, FCML_TRUE);

    STF_ASSERT_EQUAL(prefixes_details->prefixes_bytes_count, 1);
    STF_ASSERT_EQUAL(prefixes_details->prefixes_count, 8);
    STF_ASSERT_EQUAL(prefixes_details->vvvv, 14);
    STF_ASSERT_EQUAL(prefixes_details->z, 1);

    modrm_details = &(det.modrm_details);
    STF_ASSERT_EQUAL(modrm_details->displacement.N.value, 8);
    STF_ASSERT_EQUAL(modrm_details->displacement.N.is_not_null, FCML_TRUE);
    STF_ASSERT_EQUAL(modrm_details->displacement.displacement.size, 32);
    STF_ASSERT_EQUAL(modrm_details->displacement.displacement.int32, 0x12345678);
    STF_ASSERT_EQUAL(modrm_details->is_modrm, FCML_TRUE);
    STF_ASSERT_EQUAL(modrm_details->is_rip, FCML_TRUE);
    STF_ASSERT_EQUAL(modrm_details->modrm, 0x40);
    STF_ASSERT_EQUAL(modrm_details->sib.value, 0x20);
    STF_ASSERT_EQUAL(modrm_details->sib.is_not_null, FCML_TRUE);

    STF_ASSERT_EQUAL(det.operand_details[0].access_mode, FCML_AM_READ_WRITE);
    STF_ASSERT_EQUAL(det.operand_details[1].access_mode, FCML_AM_READ);
    STF_ASSERT_EQUAL(det.operand_details[2].access_mode, FCML_AM_WRITE);
    STF_ASSERT_EQUAL(det.operand_details[3].access_mode, FCML_AM_READ_WRITE);
    STF_ASSERT_EQUAL(det.operand_details[4].access_mode, FCML_AM_READ_WRITE);

    STF_ASSERT_EQUAL(det.is_shortcut, FCML_TRUE);
    STF_ASSERT_EQUAL(det.is_pseudo_op, FCML_TRUE);
    STF_ASSERT_EQUAL(det.instruction_code[0], 0x01);
    STF_ASSERT_EQUAL(det.instruction_code[FCML_INSTRUCTION_SIZE - 1], 0xFF);

    STF_ASSERT_EQUAL(det.instruction_size, 15);
    STF_ASSERT_EQUAL(det.opcode_field_s_bit, FCML_TRUE);
    STF_ASSERT_EQUAL(det.opcode_field_w_bit, FCML_TRUE);
    STF_ASSERT_EQUAL(det.instruction, F_VAESDEC);
    STF_ASSERT_EQUAL(det.pseudo_op, FP_DB);

    STF_ASSERT_EQUAL(det.pseudo_op, FP_DB);
    STF_ASSERT_EQUAL(det.addr_mode, 0x1111);
    STF_ASSERT_EQUAL(det.instruction_group, FCML_AMT_GPI);
    STF_ASSERT_EQUAL(det.tuple_type, FCML_TT_M128);

    // To make sure that all fields are taken into account while converting these structs.
    STF_ASSERT_EQUAL(memcmp(&det, &details, sizeof(details)), 0);
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

fcml_stf_test_case fcml_ti_cpp_disassembler[] = {
    { "fcml_tf_cpp_disassemble", fcml_tf_cpp_disassemble },
    { "fcml_tf_cpp_disassemble_instruction_buffer_disassemble_only", fcml_tf_cpp_disassemble_instruction_buffer_disassemble_only },
    { "fcml_tf_cpp_disassemble_instruction_buffer_disassemble_render", fcml_tf_cpp_disassemble_instruction_buffer_disassemble_render },
    { "fcml_tf_cpp_disassemble_instruction_buffer_disassemble_only_stream", fcml_tf_cpp_disassemble_instruction_buffer_disassemble_only_stream },
    { "fcml_tf_cpp_disassembleshould_convert_instruction_details_correctly", fcml_tf_cpp_disassembleshould_convert_instruction_details_correctly },
    { "fcml_tf_cpp_disassemble_avx512_disp8_bcast", fcml_tf_cpp_disassemble_avx512_disp8_bcast },
    FCML_STF_NULL_TEST
};

fcml_stf_test_suite fcml_si_cpp_disassembler = {
    "suite-fcml-cpp-disassembler", fcml_tf_cpp_disassembler_suite_init, fcml_tf_cpp_disassembler_suite_cleanup, fcml_ti_cpp_disassembler
};
