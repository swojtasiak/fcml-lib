/*
 * fcml_x64intel_asm_parser.h
 *
 *  Created on: 20-03-2013
 *      Author: tAs
 */

#ifndef FCML_X64INTEL_ASM_PARSER_H_
#define FCML_X64INTEL_ASM_PARSER_H_

#define FCML_X64IAP_MAX_INSTRUCTION_LEN		1024

#include "fcml_ceh.h"
#include "fcml_types.h"
#include "fcml_common.h"

typedef struct fcml_st_x64iap_parser_result {
	fcml_st_ceh_error_container errors;
	fcml_st_instruction *instruction;
} fcml_st_x64iap_parser_result;

fcml_ceh_error fcml_x64iap_parse( fcml_string instruction, fcml_st_x64iap_parser_result **result_out );
void fcml_x64iap_free( fcml_st_x64iap_parser_result *result );

#endif /* FCML_X64INTEL_ASM_PARSER_H_ */
