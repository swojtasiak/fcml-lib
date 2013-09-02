/*
 * fcml_asm_dialect.h
 *
 *  Created on: 1 wrz 2013
 *      Author: tAs
 */

#ifndef FCML_ASM_DIALECT_H_
#define FCML_ASM_DIALECT_H_

#include "fcml_def.h"
#include "fcml_common.h"

#define FCML_ASM_DIALECT_MAX_MNEMONIC_COUNT 10

typedef int (*fcml_fnp_asm_dialect_get_mnemonic)( fcml_st_def_instruction_description *instruction, fcml_st_def_addr_mode_desc *addr_mode, fcml_st_condition *condition, fcml_string *mnemonics );

typedef void (*fcml_fnp_asm_dialect_free_mnemonic)( fcml_string mnemonic );

typedef struct fcml_st_dialect_context {
    fcml_fnp_asm_dialect_get_mnemonic get_mnemonic;
    fcml_fnp_asm_dialect_free_mnemonic free_mnemonic;
} fcml_st_dialect_context;

fcml_string fcml_fn_asm_dialect_alloc_mnemonic_with_suffix( fcml_string mnemonic, fcml_string suffix );
fcml_string fcml_fn_asm_dialect_alloc_mnemonic( fcml_string mnemonic );
void fcml_fn_asm_dialect_free_mnemonic( fcml_string mnemonic );

#endif /* FCML_ASM_DIALECT_H_ */
