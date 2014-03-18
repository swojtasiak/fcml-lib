/*
 * fcml_parser_common.h
 *
 *  Created on: 02-03-2013
 *      Author: tAs
 */

#ifndef FCML_PARSER_DATA_H_
#define FCML_PARSER_DATA_H_

#include "fcml_common.h"
#include "fcml_apc_ast.h"
#include "fcml_ceh.h"
#include "fcml_coll.h"

typedef struct fcml_st_parser_data {
	/* Lexer context. */
	void *scannerInfo;
	/* Instruction pointer used to declare symbols. */
	fcml_ip ip;
	/* Defined symbol. */
	fcml_st_symbol *symbol;
	/* Abstract syntax tree of parsed isntruction. */
	fcml_st_ast_node *tree;
	/* All potential errors going here. */
	fcml_st_ceh_error_container errors;
} fcml_st_parser_data;

#endif /* FCML_PARSER_DATA_H_ */
