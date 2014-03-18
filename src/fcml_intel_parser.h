/*
 * fcml_intel_asm_parser.h
 *
 *  Created on: 20-03-2013
 *      Author: tAs
 */

#ifndef FCML_X64INTEL_ASM_PARSER_H_
#define FCML_X64INTEL_ASM_PARSER_H_

#include "fcml_ceh.h"
#include "fcml_parser.h"
#include "fcml_parser_int.h"
#include "fcml_types.h"
#include "fcml_dialect.h"

fcml_ceh_error fcml_fn_intel_parse_instruction_to_ast( fcml_ip ip, fcml_string mnemonic, fcml_st_parser_ast *ast );

#endif /* FCML_X64INTEL_ASM_PARSER_H_ */
