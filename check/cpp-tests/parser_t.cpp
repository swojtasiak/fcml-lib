/*
 * parser_t.cpp
 *
 *  Created on: Aug 6, 2014
 *      Author: tas
 */

#include "parser_t.hpp"

#include <fcml_common.hpp>
#include <fcml_parser.hpp>
#include <fcml_intel_dialect.hpp>

using namespace fcml;

fcml_bool fcml_tf_cpp_parser_suite_init(void) {
    return FCML_TRUE;
}

fcml_bool fcml_tf_cpp_parser_suite_cleanup(void) {
    return FCML_TRUE;
}

void fcml_tf_cpp_parser(void) {

	try {

		IntelDialect dialect;

		ParserContext ctx(0x401000);

		Parser parser(dialect);

		ParserResult result;

		try {
			STF_ASSERT_EQUAL( parser.parse( ctx, _FT("mov eax, dword [0x0401000]"), result ), FCML_CEH_GEC_NO_ERROR );
			STF_ASSERT_EQUAL( parser.parse( ctx, _FT("mov eax, dword [0x0401000]"), result ), FCML_CEH_GEC_NO_ERROR );
			STF_ASSERT_EQUAL( parser.parse( ctx, _FT("mov eax, dword [0x0401000]"), result ), FCML_CEH_GEC_NO_ERROR );
			STF_ASSERT_EQUAL( parser.parse( ctx, _FT("mov eax, dword [0x0401000]"), result ), FCML_CEH_GEC_NO_ERROR );
		} catch( ParsingFailedException &exc ) {
			STF_FAIL("Parsing failed.");
		}

		const Instruction &instruction = result.getInstruction();
		STF_ASSERT_EQUAL( instruction.isConditional(), false );
		STF_ASSERT_EQUAL( instruction.getCondition().getConditionType(), Condition::CONDITION_O );
		STF_ASSERT_EQUAL( instruction.getMnemonic(), fcml_cstring( _FT("mov") ) );
		STF_ASSERT_EQUAL( instruction.getOperandsCount(), 2 );
		STF_ASSERT_EQUAL( instruction.getPrefixes(), 0 );

	} catch( std::exception &exc ) {
		STF_FAIL("Unexpected exception.");
	} catch( fcml::BaseException &exc ) {
		STF_FAIL("Unexpected exception.");
	}

}


void fcml_tf_cpp_parser_error(void) {

	try {

		IntelDialect dialect;

		ParserContext ctx(0x401000);

		Parser parser(dialect);

		ParserResult result;

		fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

		try {
			parser.parse( ctx, _FT("mov eax1, dword [0x0401000]"), result );
			STF_FAIL("Parsing failed.");
		} catch( ParsingFailedException &exc ) {
			error = exc.getError();
			STF_ASSERT_EQUAL( exc.getMsg(), FCML_TEXT( "Parsing failed: Undefined symbol: eax1." ) );
		}

		STF_ASSERT_EQUAL( result.getErrors().getFirstErrorMessage(), FCML_TEXT( "Undefined symbol: eax1." ) );
		STF_ASSERT_EQUAL( error, FCML_CEH_GEC_UNDEFINED_SYMBOL );

	} catch( std::exception &exc ) {
		STF_FAIL("Unexpected exception.");
	} catch( fcml::BaseException &exc ) {
		STF_FAIL("Unexpected exception.");
	}

}

fcml_stf_test_case fcml_ti_cpp_parser[] = {
    { "fcml_tf_cpp_parser", fcml_tf_cpp_parser },
    { "fcml_tf_cpp_parser_error", fcml_tf_cpp_parser_error },
    FCML_STF_NULL_TEST
};

fcml_stf_test_suite fcml_si_cpp_parser = {
    "suite-fcml-cpp-parser", fcml_tf_cpp_parser_suite_init, fcml_tf_cpp_parser_suite_cleanup, fcml_ti_cpp_parser
};
