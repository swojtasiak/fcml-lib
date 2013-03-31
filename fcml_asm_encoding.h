/*
 * fcml_asm_encoding.h
 *
 *  Created on: 31-03-2013
 *      Author: tAs
 */

#ifndef FCML_ASM_ENCODING_H_
#define FCML_ASM_ENCODING_H_

#include "fcml_asm_int.h"
#include "fcml_ceh.h"

void fcml_fn_asm_init_instruction_encodings( fcml_ceh_error *error );
void fcml_fn_asm_free_instruction_encodings();
fcml_st_asm_instruction_encoding *fcml_fn_asm_get_instruction_encodings( fcml_string mnemonic, fcml_ceh_error *error );

#endif /* FCML_ASM_ENCODING_H_ */
