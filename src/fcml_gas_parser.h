/*
 * fcml_intel_asm_parser.h
 *
 *  Created on: 20-03-2013
 *      Author: tAs
 */

#ifndef FCML_X64ATT_ASM_PARSER_H_
#define FCML_X64ATT_ASM_PARSER_H_

#include "fcml_ceh.h"
#include "fcml_dialect.h"
#include "fcml_parser.h"
#include "fcml_types.h"

fcml_ceh_error fcml_gas_parse( fcml_st_parser_context *context, fcml_string instruction, fcml_st_parser_result *result_out );

#endif /* FCML_X64INTEL_ASM_PARSER_H_ */
