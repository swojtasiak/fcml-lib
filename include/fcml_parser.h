/*
 * fcml_parser.h
 *
 *  Created on: Nov 14, 2013
 *      Author: tas
 */

#ifndef FCML_PARSER_H_
#define FCML_PARSER_H_

#include "fcml_lib_export.h"

#include "fcml_types.h"
#include "fcml_errors.h"
#include "fcml_common.h"
#include "fcml_dialect.h"

#ifdef __cplusplus
extern "C" {
#endif

#define FCML_PARSER_MAX_INSTRUCTION_LEN	1024

typedef struct fcml_st_parser_result {
	fcml_st_ceh_error_container errors;
	fcml_st_instruction *instruction;
} fcml_st_parser_result;

fcml_ceh_error LIB_EXPORT fcml_fn_parse( fcml_st_dialect *dialect, fcml_string instruction, fcml_st_parser_result *result );
void LIB_EXPORT fcml_fn_parser_result_prepare( fcml_st_parser_result *result );
void LIB_EXPORT fcml_fn_parser_result_free( fcml_st_parser_result *result );

#ifdef __cplusplus
}
#endif

#endif /* FCML_PARSER_H_ */
