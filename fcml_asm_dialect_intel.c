/*
 * fcml_asm_dialect_intel.c
 *
 *  Created on: 1 wrz 2013
 *      Author: tAs
 */

#include "fcml_asm_dialect_intel.h"
#include "fcml_env.h"

#include <string.h>

#define FCML_ASM_DIALECT_INTEL_GROUPS 3

fcml_string fcml_itb_intel_conditional_suffixes[3][16] = {
    { "o", "no",  "b",   "nb", "e", "ne", "be", "nbe", "s",  "ns", "p",  "np", "l",   "nl", "le", "nle" },
    { NULL, NULL, "nae", "ae", "z", "nz", "na", "a",   NULL, NULL, "pe", "po", "nge", "ge", "ng", "g"   },
    { NULL, NULL, "c",   "nc", NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,  NULL, NULL, NULL  }
};

void fcml_fnp_asm_dialect_free_mnemonic_intel( fcml_string mnemonic ) {
    // Do nothing.
    if( mnemonic ) {
        fcml_fn_asm_dialect_free_mnemonic( mnemonic );
    }
}

int fcml_fnp_asm_dialect_get_mnemonic_intel( fcml_st_def_instruction_description *instruction, fcml_st_def_addr_mode_desc *addr_mode, fcml_st_condition *condition, fcml_string *mnemonics ) {

    int mnemonic_counter = 0;

    fcml_string mnemonic;

    // Clean mnemonic array.
    int i;
    for( i = 0; i < FCML_ASM_DIALECT_MAX_MNEMONIC_COUNT; i++ ) {
        mnemonics[i] = NULL;
    }

    // Choose best mnemonic for instruction.
    if( addr_mode->mnemonic_override ) {
        mnemonic = addr_mode->mnemonic_override;
    } else {
        mnemonic = instruction->mnemonic;
    }

    if( condition != NULL ) {
        // Conditional instructions.

        fcml_uint32_t suffix_nr = condition->condition_type * 2 + ( condition->is_negation ? 1 : 0 );

        for( i = 0; i < FCML_ASM_DIALECT_INTEL_GROUPS; i++ ) {
            fcml_string suffix = fcml_itb_intel_conditional_suffixes[i][suffix_nr];
            if( suffix ) {
                mnemonics[i] = fcml_fn_asm_dialect_alloc_mnemonic_with_suffix( mnemonic, suffix );
                if( !mnemonics[i] ) {
                    // Out of memory.
                    for( i--; i >= 0; i-- ) {
                        fcml_fnp_asm_dialect_free_mnemonic_intel( mnemonics[i] );
                    }
                    mnemonic = NULL;
                    break;
                }
                mnemonic_counter++;
            } else {
                mnemonics[i] = NULL;
            }
        }

    } else {
        // Allocate new instance of mnemonic.
        mnemonics[0] = fcml_fn_asm_dialect_alloc_mnemonic( mnemonic );
        if( mnemonics[0] ) {
            mnemonic_counter++;
        }
    }

    return mnemonic_counter;
}

fcml_st_dialect_context fcml_fn_get_intel_dialect_context() {
    fcml_st_dialect_context context;
    context.get_mnemonic = &fcml_fnp_asm_dialect_get_mnemonic_intel;
    context.free_mnemonic = &fcml_fnp_asm_dialect_free_mnemonic_intel;
    return context;
}
