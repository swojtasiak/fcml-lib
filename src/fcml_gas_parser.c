/*
 * fcml_intel_asm_parser.c
 *
 *  Created on: 20-03-2013
 *      Author: tAs
 */

#include <string.h>
#include "fcml_ceh.h"
#include "fcml_env.h"
#include "fcml_common.h"
#include <fcml_errors.h>
#include "fcml_parser_data.h"
#include "fcml_gas_parser_def.h"
#include "fcml_gas_lexer.h"
#include "fcml_gas_parser.h"
#include "fcml_utils.h"
#include "fcml_messages.h"
#include "fcml_parser.h"
#include "fcml_parser_int.h"

void gas_error( struct fcml_st_parser_data *pd, const char *error ) {
	/* Stores parser error into standard container.*/
	fcml_fn_ceh_add_error( &(pd->errors), (const fcml_string)error, FCML_CEH_MEC_ERROR_INVALID_SYNTAX, FCML_EN_CEH_EL_ERROR );
}

fcml_ceh_error fcml_fn_gas_parse_instruction_to_ast( fcml_parser_ip ip, fcml_string mnemonic, fcml_st_parser_ast *ast ) {

	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

	/* Fill instruction pointer. */
	fcml_st_parser_data parser = {0};
	parser.ip = ip;

	/* Set up scanner. */
	if ( gas_lex_init_extra( &parser, &(parser.scannerInfo) ) ) {
		return FCML_CEH_GEC_OUT_OF_MEMORY;
	}

	/*Instruction size is limited to prevent from parser's stack and buffer overflow.*/
	if( fcml_fn_env_str_strlen( mnemonic ) > FCML_PARSER_MAX_INSTRUCTION_LEN ) {
		gas_lex_destroy( parser.scannerInfo );
		return FCML_CEH_GEC_INVALID_INPUT;
	}

	gas__scan_string( mnemonic, parser.scannerInfo );

	int yyresult = gas_parse(&parser);

	gas_lex_destroy( parser.scannerInfo );

	ast->errors = parser.errors;
	ast->symbol = parser.symbol;
	ast->tree = parser.tree;

	if( yyresult ) {
		switch( yyresult ) {
		case 1: /*Syntax error.*/
			error = FCML_CEH_GEC_INVALID_INPUT;
			break;
		case 2: /*Out of memory*/
			error = FCML_CEH_GEC_OUT_OF_MEMORY;
			break;
		}
	}

	return error;

}

