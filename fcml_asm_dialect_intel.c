/*
 * fcml_asm_dialect_intel.c
 *
 *  Created on: 1 wrz 2013
 *      Author: tAs
 */

#include "fcml_asm_dialect_intel.h"

fcml_string fcml_fnp_asm_dialect_get_mnemonic_intel( fcml_st_def_instruction_description *instruction, fcml_st_def_addr_mode_desc *addr_mode, fcml_st_condition *condition ) {
    if( addr_mode->mnemonic_override ) {
        return addr_mode->mnemonic_override;
    }
    return instruction->mnemonic;
}

void fcml_fnp_asm_dialect_free_mnemonic_intel( fcml_string mnemonic ) {
    // Do nothing.
}

fcml_st_dialect_context fcml_fn_get_intel_dialect_context() {
    fcml_st_dialect_context context;
    context.get_mnemonic = &fcml_fnp_asm_dialect_get_mnemonic_intel;
    context.free_mnemonic = &fcml_fnp_asm_dialect_free_mnemonic_intel;
    return context;
}
