/*
 * fcml_x64intel_asm_parser.h
 *
 *  Created on: 20-03-2013
 *      Author: tAs
 */

#ifndef FCML_X64INTEL_ASM_PARSER_H_
#define FCML_X64INTEL_ASM_PARSER_H_

#include "fcml_ceh.h"
#include "fcml_parser.h"
#include "fcml_types.h"
#include "fcml_dialect.h"

fcml_ceh_error fcml_x64intel_parse( fcml_st_dialect *dialect, fcml_string instruction, fcml_st_parser_result **result_out );

#endif /* FCML_X64INTEL_ASM_PARSER_H_ */
