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

#include <stdio.h>

#include <fcml_common.hpp>
#include <fcml_assembler.hpp>
#include <fcml_registers.hpp>
#include <fcml_lag_assembler.hpp>
#include <fcml_stateful_assembler.hpp>
#include <fcml_intel_dialect.hpp>
#include <fcml_intel_mnemonics.hpp>

using namespace fcml;
using namespace fcml::intel;

fcml_bool fcml_tf_cpp_assembler_suite_init(void) {
    return FCML_TRUE;
}

fcml_bool fcml_tf_cpp_assembler_suite_cleanup(void) {
    return FCML_TRUE;
}

void fcml_tf_cpp_assemble_instruction_long_form(void) {

    Instruction instruction;

    instruction.setMnemonic(fcml::intel::M_MOV);
    instruction.setHints(FCML_HINT_FAR_POINTER | FCML_HINT_LONG_FORM_POINTER);
    instruction.getCondition().setConditionType(Condition::CONDITION_BE);
    instruction.getCondition().setNegation(FCML_TRUE);
    instruction.setOperandsCount(2);
    instruction.setPrefixes(FCML_PREFIX_LOCK | FCML_PREFIX_REPE);

    instruction[0].setOperandType(Operand::OT_REGISTER);
	instruction[0].getRegister().setReg(FCML_REG_EAX);
	instruction[0].getRegister().setSize(FCML_DS_32);
	instruction[0].getRegister().setType(Register::REG_GPR);
	instruction[1].setOperandType(Operand::OT_ADDRESS);
	instruction[1].getAddress().setAddressForm(Address::AF_OFFSET);
	instruction[1].getAddress().getOffset().setSigned(FCML_TRUE);
	instruction[1].getAddress().getOffset().setInt32(0x401000);
	instruction[1].getAddress().getOffset().setSize(FCML_DS_32);
	instruction[1].getAddress().setSizeOperator(FCML_DS_32);

    fcml_st_instruction instStr;

    TypeConverter::convert( instruction, instStr );

    STF_ASSERT_EQUAL( instStr.mnemonic, M_MOV );
    STF_ASSERT_EQUAL( instStr.hints, FCML_HINT_FAR_POINTER | FCML_HINT_LONG_FORM_POINTER );
    STF_ASSERT_EQUAL( instStr.operands_count, 2 );
    STF_ASSERT_EQUAL( instStr.prefixes, FCML_PREFIX_LOCK | FCML_PREFIX_REPE );
    STF_ASSERT_EQUAL( instStr.condition.condition_type, static_cast<fcml_en_condition_type>( instruction.getCondition().getConditionType() ) );

    STF_ASSERT_EQUAL( FCML_OT_REGISTER, instStr.operands[0].type );
    STF_ASSERT_EQUAL( FCML_REG_EAX, instStr.operands[0].reg.reg );
    STF_ASSERT_EQUAL( FCML_DS_32, instStr.operands[0].reg.size );
    STF_ASSERT_EQUAL( FCML_REG_GPR, instStr.operands[0].reg.type );
    STF_ASSERT_EQUAL( FCML_OT_ADDRESS, instStr.operands[1].type );
    STF_ASSERT_EQUAL( FCML_AF_OFFSET, instStr.operands[1].address.address_form );
    STF_ASSERT_EQUAL( FCML_TRUE, instStr.operands[1].address.offset.is_signed );
    STF_ASSERT_EQUAL( 0x401000, instStr.operands[1].address.offset.off32 );
    STF_ASSERT_EQUAL( FCML_DS_32, instStr.operands[1].address.offset.size );
    STF_ASSERT_EQUAL( FCML_DS_32, instStr.operands[1].address.size_operator );

    TypeConverter::free( instStr );

}

void fcml_tf_cpp_assemble_instruction_short_form(void) {

    Instruction instruction;

    instruction.setMnemonic(FCML_TEXT("mov"));
    instruction.setHints(FCML_HINT_FAR_POINTER | FCML_HINT_LONG_FORM_POINTER);
    instruction.getCondition().setConditionType(Condition::CONDITION_BE);
    instruction.getCondition().setNegation(FCML_TRUE);
    instruction.setOperandsCount(2);
    instruction.setPrefixes(FCML_PREFIX_LOCK | FCML_PREFIX_REPE);

    instruction[0].reg( Register::EAX() );
	instruction[1].off( (fcml_int32_t)0x401000, FCML_DS_32 );

    fcml_st_instruction instStr;

    TypeConverter::convert( instruction, instStr );

    STF_ASSERT_STRING_EQUAL( instStr.mnemonic, FCML_TEXT("mov") );
    STF_ASSERT_EQUAL( instStr.hints, FCML_HINT_FAR_POINTER | FCML_HINT_LONG_FORM_POINTER );
    STF_ASSERT_EQUAL( instStr.operands_count, 2 );
    STF_ASSERT_EQUAL( instStr.prefixes, FCML_PREFIX_LOCK | FCML_PREFIX_REPE );
    STF_ASSERT_EQUAL( instStr.condition.condition_type, static_cast<fcml_en_condition_type>( instruction.getCondition().getConditionType() ) );

    STF_ASSERT_EQUAL( FCML_OT_REGISTER, instStr.operands[0].type );
    STF_ASSERT_EQUAL( FCML_REG_EAX, instStr.operands[0].reg.reg );
    STF_ASSERT_EQUAL( FCML_DS_32, instStr.operands[0].reg.size );
    STF_ASSERT_EQUAL( FCML_REG_GPR, instStr.operands[0].reg.type );
    STF_ASSERT_EQUAL( FCML_OT_ADDRESS, instStr.operands[1].type );
    STF_ASSERT_EQUAL( FCML_AF_OFFSET, instStr.operands[1].address.address_form );
    STF_ASSERT_EQUAL( FCML_TRUE, instStr.operands[1].address.offset.is_signed );
    STF_ASSERT_EQUAL( 0x401000, instStr.operands[1].address.offset.off32 );
    STF_ASSERT_EQUAL( FCML_DS_32, instStr.operands[1].address.offset.size );
    STF_ASSERT_EQUAL( FCML_DS_32, instStr.operands[1].address.size_operator );

    TypeConverter::free( instStr );

}

void fcml_tf_cpp_assemble_instruction_builder_short(void) {

    Instruction instruction;

    // Long form, don't be afraid short alternatives are presented below.
    instruction = IB::inst(_FT("mov")).farPtr().longFormPtr().lock().repe().reg( Register::EAX() ).off( (fcml_int32_t)0x401000, FCML_DS_32 ).build();

    fcml_st_instruction instStr;

    TypeConverter::convert( instruction, instStr );

    STF_ASSERT_STRING_EQUAL( instStr.mnemonic, FCML_TEXT("mov") );
    STF_ASSERT_EQUAL( instStr.hints, FCML_HINT_FAR_POINTER | FCML_HINT_LONG_FORM_POINTER );
    STF_ASSERT_EQUAL( instStr.operands_count, 2 );
    STF_ASSERT_EQUAL( instStr.prefixes, FCML_PREFIX_LOCK | FCML_PREFIX_REPE );
    STF_ASSERT_EQUAL( instStr.condition.condition_type, static_cast<fcml_en_condition_type>( instruction.getCondition().getConditionType() ) );

    STF_ASSERT_EQUAL( FCML_OT_REGISTER, instStr.operands[0].type );
    STF_ASSERT_EQUAL( FCML_REG_EAX, instStr.operands[0].reg.reg );
    STF_ASSERT_EQUAL( FCML_DS_32, instStr.operands[0].reg.size );
    STF_ASSERT_EQUAL( FCML_REG_GPR, instStr.operands[0].reg.type );
    STF_ASSERT_EQUAL( FCML_OT_ADDRESS, instStr.operands[1].type );
    STF_ASSERT_EQUAL( FCML_AF_OFFSET, instStr.operands[1].address.address_form );
    STF_ASSERT_EQUAL( FCML_TRUE, instStr.operands[1].address.offset.is_signed );
    STF_ASSERT_EQUAL( 0x401000, instStr.operands[1].address.offset.off32 );
    STF_ASSERT_EQUAL( FCML_DS_32, instStr.operands[1].address.offset.size );
    STF_ASSERT_EQUAL( FCML_DS_32, instStr.operands[1].address.size_operator );

    TypeConverter::free( instStr );

}

void fcml_tf_util_check_instruction( Instruction &instruction ) {

	fcml_st_instruction instStr;

	TypeConverter::convert( instruction, instStr );

	STF_ASSERT_STRING_EQUAL( instStr.mnemonic, FCML_TEXT("mov") );
	STF_ASSERT_EQUAL( instStr.hints, 0 );
	STF_ASSERT_EQUAL( instStr.operands_count, 2 );
	STF_ASSERT_EQUAL( instStr.prefixes, 0 );
	STF_ASSERT_EQUAL( instStr.condition.condition_type, static_cast<fcml_en_condition_type>( instruction.getCondition().getConditionType() ) );

	STF_ASSERT_EQUAL( FCML_OT_ADDRESS, instStr.operands[0].type );
	STF_ASSERT_EQUAL( FCML_AF_COMBINED, instStr.operands[0].address.address_form );
	STF_ASSERT_EQUAL( FCML_REG_EAX, instStr.operands[0].address.effective_address.base.reg );
	STF_ASSERT_EQUAL( FCML_DS_32, instStr.operands[0].address.effective_address.base.size );
	STF_ASSERT_EQUAL( FCML_REG_GPR, instStr.operands[0].address.effective_address.base.type );
	STF_ASSERT_EQUAL( FCML_FALSE, instStr.operands[0].address.effective_address.base.x64_exp );
	STF_ASSERT_EQUAL( FCML_DS_8, instStr.operands[0].address.size_operator );

	STF_ASSERT_EQUAL( FCML_OT_REGISTER, instStr.operands[1].type );
	STF_ASSERT_EQUAL( FCML_REG_ECX, instStr.operands[1].reg.reg );
	STF_ASSERT_EQUAL( FCML_DS_32, instStr.operands[1].reg.size );
	STF_ASSERT_EQUAL( FCML_REG_GPR, instStr.operands[1].reg.type );

	TypeConverter::free( instStr );

}

void fcml_tf_cpp_assemble_instruction_builder_shortest(void) {

    Instruction instruction;

    instruction = IB(M_MOV).eff( EAX, 8 ).reg( ECX ).build();

    fcml_tf_util_check_instruction( instruction );

    instruction = IB::inst(M_MOV).eff( EAX, 8 ).reg( ECX ).build();

	fcml_tf_util_check_instruction( instruction );

	instruction = IB::inst(M_MOV).eff( EAX, 8 ).reg( ECX );

	fcml_tf_util_check_instruction( instruction );

	instruction = IB(M_MOV).eff( EAX, 8 ).reg( ECX );

	instruction = IB(M_MOV) << OB::eff( EAX, 8 ) << OB::reg( ECX );

	fcml_tf_util_check_instruction( instruction );

	instruction = IB(M_MOV) << OB::effb( EAX ) << OB::reg( ECX );

	fcml_tf_util_check_instruction( instruction );

}

void fcml_tf_cpp_assemble_instruction_builder_hints_prefixes(void) {

	Instruction instruction;

	instruction = IB(M_MOV) << IB::LOCK() << IB::REP() << IB::INDIRECT_PTR() << IB::NEAR_PTR() << OB::effb( EAX ) << OB::reg( ECX );

	STF_ASSERT( instruction.getMnemonic() == fcml_cstring(FCML_TEXT("mov")) );
	STF_ASSERT( instruction.getMnemonic() == M_MOV );
	STF_ASSERT_EQUAL( instruction.getPrefixes(), FCML_PREFIX_LOCK | FCML_PREFIX_REP );
	STF_ASSERT( instruction.isLock() );
	STF_ASSERT( instruction.isRep() );
	STF_ASSERT_EQUAL( instruction.getHints(), FCML_HINT_INDIRECT_POINTER | FCML_HINT_NEAR_POINTER );
	STF_ASSERT( instruction.isIndirectPointer() );
	STF_ASSERT( instruction.isNearPointer() );
}

fcml_bool fcml_tf_cmp_instruction( const AssembledInstruction *assembledInstruction, fcml_uint8_t *instruction, fcml_usize len ) {
	if( !assembledInstruction ) {
		return FCML_FALSE;
	}
	if( assembledInstruction->getCodeLength() == len ) {
		for( fcml_usize i = 0; i < len; i++ ) {
			if( assembledInstruction->getCode()[i] != instruction[i] ) {
				return FCML_FALSE;
			}
		}
		return FCML_TRUE;
	}
	return FCML_FALSE;
}

const fcml_string fcml_iarr_lag_assembler_code_src[] = {
	"start:      mov ebx, 1",
	"loop_big:   inc ebx",
	"            cmp ebx, 10",
	"            je  finish",
	"loop_small: mov eax, 1",
	"increment:  inc eax",
	"            cmp eax, 10",
	"            je  finish_small",
	"            jmp increment",
	"finish_small:",
	"            jmp loop_big",
	"finish:     ret",
	NULL
};

const fcml_uint8_t fcml_iarr_lag_assembler_code_bin[] = {
	0xBB, 0x01, 0x00, 0x00, 0x00,
	0x43,
	0x83, 0xFB, 0x0A,
	0x74, 0x0F,
	0xB8, 0x01, 0x00, 0x00, 0x00,
	0x40,
	0x83, 0xF8, 0x0A,
	0x74, 0x02,
	0xEB, 0xF8,
	0xEB, 0xEB,
	0xC3
};

const fcml_string fcml_iarr_lag_assembler_code_src_error[] = {
	"start:      mov ebx, 1",
	"loop_big:   inc ebx",
	"            cmp ebx, 10",
	"            je  finish_xxxxxx", // Unknown symbol.
	"loop_small: mov eax, 1",
	"increment:  inc eax",
	"            cmp eax, 10",
	"            je  finish_small",
	"            jmp increment",
	"finish_small:",
	"            jmp loop_big",
	"finish:     ret",
	NULL
};

const fcml_string fcml_iarr_lag_assembler_code_src_error_1[] = {
	"start:      mov ebx, 1",
	"loop_big:   inc eb, p][]s ddx", // Syntax error.
	"            cmp ebx, 10",
	"            je  finish", // Unknown symbol.
	"loop_small: mov eax, 1",
	"increment:  inc eax",
	"            cmp eax, 10",
	"            je  finish_small",
	"            jmp increment",
	"finish_small:",
	"            jmp loop_big",
	"finish:     ret",
	NULL
};


void fcml_tf_cpp_multi_pass_assemble(void) {

	fcml_ceh_error error;

	try {

		IntelDialect dialect;

		MultiPassAssemblerContext ctx( EntryPoint::OM_32_BIT, 0x401000 );

		MultiPassAssemblerResult result;

		MultiPassAssembler assembler(dialect);

		error = assembler.assemble( ctx, fcml_iarr_lag_assembler_code_src, result );

		STF_ASSERT_EQUAL( error, FCML_CEH_GEC_NO_ERROR );

		if( !error ) {

			fcml_int i = 0;
			CodeIterator it = result.getCodeIterator();
			while( it.hasNext() ) {
				fcml_uint8_t codeByte = it.next();
				if( codeByte != fcml_iarr_lag_assembler_code_bin[i++] ) {
					STF_FAIL( "Assembled code is not the same." );
				}
			}

			if( i != sizeof( fcml_iarr_lag_assembler_code_bin ) ) {
				STF_FAIL( "Assembled code is not the same." );
			}

		}

	} catch( BaseException &exc ) {
		STF_FAIL("Exception while assembling the code.");
	}

}

void fcml_tf_cpp_multi_pass_assemble_error(void) {

	try {

		IntelDialect dialect;

		MultiPassAssemblerContext ctx( EntryPoint::OM_32_BIT, 0x401000 );

		MultiPassAssemblerResult result;

		MultiPassAssembler assembler(dialect);

		try {
			assembler.assemble( ctx, fcml_iarr_lag_assembler_code_src_error, result );
			STF_FAIL( "Should fail!" );
		} catch( AssemblingFailedException &exc ) {
			// Undefined symbol, see the assembled source code.
			STF_ASSERT_EQUAL( exc.getMsg(), fcml_cstring( FCML_TEXT( "Assembling failed: Undefined symbol: finish_xxxxxx." ) ) );
			STF_ASSERT_EQUAL( exc.getError(), FCML_CEH_GEC_UNDEFINED_SYMBOL );
			STF_ASSERT( true ); // OK.
		}


	} catch( BaseException &exc ) {
		STF_FAIL("Exception while assembling the code.");
	}

}

void fcml_tf_cpp_multi_pass_assemble_error_1(void) {

	try {

		IntelDialect dialect;

		MultiPassAssemblerContext ctx( EntryPoint::OM_32_BIT, 0x401000 );

		MultiPassAssemblerResult result;

		MultiPassAssembler assembler(dialect);

		try {
			assembler.assemble( ctx, fcml_iarr_lag_assembler_code_src_error_1, result );
			STF_FAIL( "Should fail!" );
		} catch( AssemblingFailedException &exc ) {
			// Undefined symbol, see the assembled source code.
			STF_ASSERT_EQUAL( exc.getMsg(), fcml_cstring( FCML_TEXT( "Assembling failed: syntax error" ) ) );
			STF_ASSERT_EQUAL( exc.getError(), FCML_CEH_GEC_INVALID_INPUT );
			STF_ASSERT( true ); // OK.
		}

	} catch( BaseException &exc ) {
		STF_FAIL("Exception while assembling the code.");
	}

}

void fcml_tf_cpp_assemble(void) {

	fcml_ceh_error error;

	try {

		IntelDialect dialect;

		AssemblerContext ctx( EntryPoint::OM_32_BIT, 0x401000 );

		AssemblerResult result;

		Assembler assembler(dialect);

		Instruction instruction = IB(M_MOV) << OB::reg(EAX) << OB::offd( 0x40302010 );

		error = assembler.assemble( ctx, instruction, result );
		STF_ASSERT_EQUAL( error, FCML_CEH_GEC_NO_ERROR );

		if( !error ) {
			fcml_uint8_t inst[] = {0xA1, 0x10, 0x20, 0x30, 0x40};
			STF_ASSERT( fcml_tf_cmp_instruction( result.getChosenInstruction(), inst, 5 ) );

			// Checks access to the constant assembled instruction.
			const AssembledInstruction chosenInstruction = *result.getChosenInstruction();
			const fcml_uint8_t *buffer = chosenInstruction.getCode();
			STF_ASSERT_PTR_NOT_NULL( buffer );
			fcml_usize len = chosenInstruction.getCodeLength();
			STF_ASSERT_EQUAL( len, 5 );
			const ErrorContainer &errors = chosenInstruction.getWarningContainer();
			STF_ASSERT_EQUAL( errors.getSize(), 0 );
			try {
			    errors.getFirstError();
			    STF_FAIL("Container is empty.");
			} catch( IllegalStateException &exc ) {
			    STF_ASSERT( true );
			}
            STF_ASSERT("" == errors.getFirstErrorMessage() );
		}

	} catch( BaseException &exc ) {
		STF_FAIL("Exception while assembling the code.");
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

fcml_uint8_t fcml_iarr_stateful_assembler_result_expected[] = {
    0x55,
    0x48, 0x8b, 0xec, // (It's just a different way to encode "mov %rsp,%rbp", everything is OK.)
    0x48, 0x83, 0xec, 0x20,
    0x89, 0x7d, 0xec,
    0x48, 0x89, 0x75, 0xe0,
    0xbe, 0x60, 0xd2, 0x62, 0x00,
    0xbf, 0xe8, 0xdb, 0x41, 0x00,
    0xe8, 0x1f, 0x89, 0x01, 0x00
};

/* Tests CodeBuffer helper class. */
void fcml_tf_cpp_assemble_statefull_assembler(void) {

    try {

        // Only because Intel mnemonics had been already included.
        IntelDialect dialect;

        AssemblerContext ctx( EntryPoint::OM_64_BIT, 0x404ddc );

        Assembler assembler(dialect);

        StatefulAssembler sasm(assembler, ctx);

        sasm << M_PUSH << OB::reg(RBP);
        sasm << M_MOV  << OB::reg(RBP) << OB::reg(RSP);
        // Check direct use of the immediate and register operands.
        sasm << M_SUB  << RSP << 0x20;
        sasm << M_MOV  << OB::effd(RBP,-0x14) << OB::reg(EDI);
        sasm << M_MOV  << OB::effq(RBP,-0x20) << OB::reg(RSI);
        sasm << M_MOV  << OB::reg(ESI) << OB::imm(0x62d260);
        // And using plain methods.
        sasm.inst(M_MOV).op(EDI).op(0x41dbe8);
        // Flush instruction builder immediately.
        sasm << M_CALL << InstructionHint::DIRECT_POINTER() << OB::offq(0x41d719) << StatefulAssembler::FLUSH();

        fcml_uint8_t *result_bytes = fcml_iarr_stateful_assembler_result_expected;

        bool failed = false;

        CodeIterator it = sasm.getCodeIterator();
        while( it.hasNext() ) {
            fcml_uint8_t b = it.next();
            if( *result_bytes++ != b ) {
                failed = true;
                break;
            }
        }

        if( failed ) {
            STF_FAIL( "Assembled code and result differs." );
        } else {
            STF_ASSERT( true );
        }

    } catch( BaseException &exc ) {
        STF_FAIL("Exception while assembling the code.");
    }

}

/* Tests CodeBuffer helper class. */
void fcml_tf_cpp_assemble_stateful_assembler_with_parser(void) {

    try {

        // Only because Intel mnemonics had been already included.
        IntelDialect dialect;

        AssemblerContext ctx( EntryPoint::OM_64_BIT, 0x404ddc );

        Assembler assembler(dialect);

        StatefulAssembler sasm(assembler, ctx, true);

        // Enable symbols support.
        sasm.getParserConfig().setDisableSymbolsDeclaration(false);

        // By the way, check if symbols works as expected.
        SymbolTable st;
        st.add( _FT("_start"), 0x41d719 );
        sasm.setSymbolTable( &st );

        sasm << _FT( "push rbp" );
        sasm << _FT( "mov rbp, rsp" );
        sasm << _FT( "sub rsp, 0x20" );
        sasm << _FT( "_label: mov dword [rbp-0x14], edi" );
        sasm << _FT( "mov qword [rbp-0x20], rsi" );
        sasm << _FT( "mov esi, 0x62d260" );
        sasm << _FT( "mov edi, 0x41dbe8" );
        sasm << _FT( "call _start" );

        Symbol symbol = st.get( _FT("_label") );
        const Symbol symbolConst = symbol;
        STF_ASSERT( !symbolConst.isEmpty() );
        STF_ASSERT_EQUAL( symbolConst.getValue(), 0x404de4 );

        const SymbolTable &stConst = st;

        fcml_int64_t label = stConst.get( _FT("_label") );
        STF_ASSERT_EQUAL( label, 0x404de4 );

        // Check if generated code is the same as expected one.

        fcml_uint8_t *result_bytes = fcml_iarr_stateful_assembler_result_expected;

        bool failed = false;

        CodeIterator it = sasm.getCodeIterator();
        while( it.hasNext() ) {
            fcml_uint8_t b = it.next();
            if( *result_bytes++ != b ) {
                failed = true;
                break;
            }
        }

        if( failed ) {
            STF_FAIL( "Assembled code and result differs." );
        } else {
            STF_ASSERT( true );
        }

        std::vector<AssembledInstruction>& instructions = sasm.getAssembledInstructions();
        STF_ASSERT_EQUAL( instructions.size(), 8 );

    } catch( BaseException &exc ) {
        STF_FAIL("Exception while assembling the code.");
    }

}

fcml_stf_test_case fcml_ti_cpp_assembler[] = {
    { "fcml_tf_cpp_assemble_instruction_long_form", fcml_tf_cpp_assemble_instruction_long_form },
    { "fcml_tf_cpp_assemble_instruction_short_form", fcml_tf_cpp_assemble_instruction_short_form },
    { "fcml_tf_cpp_assemble_instruction_builder_short", fcml_tf_cpp_assemble_instruction_builder_short },
    { "fcml_tf_cpp_assemble_instruction_builder_shortest", fcml_tf_cpp_assemble_instruction_builder_shortest },
    { "fcml_tf_cpp_assemble_instruction_builder_hints_prefixes", fcml_tf_cpp_assemble_instruction_builder_hints_prefixes },
    { "fcml_tf_cpp_multi_pass_assemble", fcml_tf_cpp_multi_pass_assemble },
    { "fcml_tf_cpp_multi_pass_assemble_error", fcml_tf_cpp_multi_pass_assemble_error },
    { "fcml_tf_cpp_multi_pass_assemble_error_1", fcml_tf_cpp_multi_pass_assemble_error_1 },
    { "fcml_tf_cpp_assemble", fcml_tf_cpp_assemble },
    { "fcml_tf_cpp_assemble_statefull_assembler", fcml_tf_cpp_assemble_statefull_assembler },
    { "fcml_tf_cpp_assemble_stateful_assembler_with_parser", fcml_tf_cpp_assemble_stateful_assembler_with_parser },
    FCML_STF_NULL_TEST
};

fcml_stf_test_suite fcml_si_cpp_assembler = {
    "suite-fcml-cpp-assembler", fcml_tf_cpp_assembler_suite_init, fcml_tf_cpp_assembler_suite_cleanup, fcml_ti_cpp_assembler
};
