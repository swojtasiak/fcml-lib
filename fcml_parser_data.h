/*
 * fcml_parser_common.h
 *
 *  Created on: 02-03-2013
 *      Author: tAs
 */

#ifndef FCML_PARSER_COMMON_H_
#define FCML_PARSER_COMMON_H_

#include "fcml_common.h"
#include "fcml_apc_ast.h"
#include "fcml_ceh.h"

typedef struct fcml_st_parser_data {
	void *scannerInfo;
	fcml_st_ast_node *tree;
	fcml_st_ceh_error_container errors;

} fcml_st_parser_data;

#endif /* FCML_PARSER_COMMON_H_ */
