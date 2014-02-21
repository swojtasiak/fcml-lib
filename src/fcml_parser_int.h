/*
 * fcml_parser_int.h
 *
 *  Created on: Feb 20, 2014
 *      Author: tas
 */

#ifndef FCML_PARSER_INT_H_
#define FCML_PARSER_INT_H_

#include <fcml_parser.h>

#include "fcml_apc_ast.h"
#include "fcml_coll.h"
#include "fcml_ceh.h"

typedef struct fcml_st_parser_context_int {
	fcml_st_parser_context context;
	/* All symbols parser got or allocated are stored here. */
	fcml_coll_map symbols;
} fcml_st_parser_context_int;

typedef struct fcml_st_parser_ast {
	/* Defined symbol. */
	fcml_st_symbol *symbol;
	/* Abstract syntax tree of parsed isntruction. */
	fcml_st_ast_node *tree;
	/* All potential errors going here. */
	fcml_st_ceh_error_container errors;
} fcml_st_parser_ast;

fcml_ceh_error fcml_fn_parse_to_cif( fcml_st_parser_context *context, fcml_string instruction, fcml_st_parser_result *result_out );
fcml_ceh_error fcml_fn_parse_to_ast( fcml_st_parser_context *context, fcml_string instruction, fcml_st_parser_ast *ast_out );
fcml_ceh_error fcml_fn_parser_add_symbol_to_symbol_table( fcml_st_ceh_error_container *errors, fcml_coll_map symbol_table, fcml_st_symbol *symbol, fcml_bool allow_override );
void fcml_fn_parser_free_ast( fcml_st_parser_ast *ast );
void fcml_fn_parser_free_symbol( fcml_st_symbol *symbol );

#endif /* FCML_PARSER_INT_H_ */
