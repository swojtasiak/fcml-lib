/*
 * fcml_asm_decoding.h
 *
 *  Created on: Oct 13, 2013
 *      Author: tas
 */

#ifndef FCML_ASM_DECODING_H_
#define FCML_ASM_DECODING_H_

#include "fcml_disassembler.h"
#include "fcml_asm_dialect.h"

typedef struct fcml_st_asm_decoding_context {

} fcml_st_asm_decoding_context;

fcml_ceh_error fcml_fn_asm_init_instruction_decodings( fcml_st_dialect_context *dialect_context, fcml_st_disassembler **disassembler );

void fcml_fn_asm_free_instruction_decodings( fcml_st_disassembler *disassembler );

#endif /* FCML_ASM_DECODING_H_ */
