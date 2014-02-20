/*
 * fcml_parser_int.h
 *
 *  Created on: Feb 20, 2014
 *      Author: tas
 */

#ifndef FCML_PARSER_INT_H_
#define FCML_PARSER_INT_H_

#include <fcml_parser.h>

#include "fcml_coll.h"

typedef struct fcml_st_parser_context_int {
	fcml_st_parser_context context;
	/* All symbols parser got or allocated are stored here. */
	fcml_coll_map symbols;
} fcml_st_parser_context_int;

#endif /* FCML_PARSER_INT_H_ */
