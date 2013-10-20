/*
 * fcml_asm_dialect_intel.c
 *
 *  Created on: 1 wrz 2013
 *      Author: tAs
 */

#include "fcml_asm_dialect_intel.h"
#include "fcml_env.h"
#include "fcml_mnemonic_parser.h"
#include "fcml_rend_intel.h"

#include <string.h>

#define FCML_ASM_DIALECT_INTEL_GROUPS 3

fcml_string fcml_itb_intel_conditional_suffixes[3][16] = {
    { "o", "no",  "b",   "nb", "e", "ne", "be", "nbe", "s",  "ns", "p",  "np", "l",   "nl", "le", "nle" },
    { NULL, NULL, "nae", "ae", "z", "nz", "na", "a",   NULL, NULL, "pe", "po", "nge", "ge", "ng", "g"   },
    { NULL, NULL, "c",   "nc", NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,  NULL, NULL, NULL  }
};

void fcml_fnp_asm_dialect_free_mnemonic_intel( fcml_st_mp_mnemonic *mnemonic ) {
    // Do nothing.
    if( mnemonic ) {
        fcml_fn_asm_dialect_free_mnemonic( mnemonic );
    }
}

fcml_ceh_error fcml_fnp_asm_dialect_get_mnemonic_intel( fcml_st_def_instruction_description *instruction, fcml_st_def_addr_mode_desc *addr_mode, fcml_st_condition *condition, fcml_st_mp_mnemonic **mnemonics, int *mnemonics_counter ) {

    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

    fcml_string mnemonic_pattern;

    int counter = 0;

    // Clean mnemonic array.
    int i;
    for( i = 0; i < FCML_ASM_DIALECT_MAX_MNEMONIC_COUNT; i++ ) {
        mnemonics[i] = NULL;
    }

    // Choose best mnemonic for instruction.
    if( addr_mode->mnemonic_override ) {
        mnemonic_pattern = addr_mode->mnemonic_override;
    } else {
        mnemonic_pattern = instruction->mnemonic;
    }

    fcml_st_mp_mnemonic_set *mnemonic_set;
    error = fcml_fn_mp_parse_mnemonics( mnemonic_pattern, &mnemonic_set );
    if( error ) {
        return error;
    }

    fcml_st_coll_list_element *element = mnemonic_set->mnemonics->head;
    while( element ) {

        fcml_st_mp_mnemonic *mnemonic_def = (fcml_st_mp_mnemonic*)element->item;

        if( condition != NULL ) {
            // Conditional instructions.

            fcml_uint32_t suffix_nr = condition->condition_type * 2 + ( condition->is_negation ? 1 : 0 );

            for( i = 0; i < FCML_ASM_DIALECT_INTEL_GROUPS; i++ ) {
                fcml_string suffix = fcml_itb_intel_conditional_suffixes[i][suffix_nr];
                if( suffix ) {
                    mnemonics[counter] = fcml_fn_asm_dialect_alloc_mnemonic_with_suffix( mnemonic_def, suffix );
                    if( !mnemonics[counter] ) {
                        // Out of memory.
                        error = FCML_CEH_GEC_OUT_OF_MEMORY;
                        break;
                    }
                    counter++;
                }
            }

        } else {
            // Allocate new instance of mnemonic.
            mnemonics[counter] = fcml_fn_asm_dialect_alloc_mnemonic( mnemonic_def );
            if( mnemonics[counter] ) {
                counter++;
            } else {
                error = FCML_CEH_GEC_OUT_OF_MEMORY;
            }
        }

        element = element->next;

    }

    if( error ) {
        // Free all prepared mnemonics.
        int i;
        for( i = 0; i < counter; i++ ) {
            fcml_fnp_asm_dialect_free_mnemonic_intel( mnemonics[i] );
        }
    }

    fcml_fn_mp_free_mnemonics( mnemonic_set );

    *mnemonics_counter = counter;

    return error;
}

fcml_st_dialect_context fcml_fn_get_intel_dialect_context() {
    fcml_st_dialect_context context;
    context.get_mnemonic = &fcml_fnp_asm_dialect_get_mnemonic_intel;
    context.free_mnemonic = &fcml_fnp_asm_dialect_free_mnemonic_intel;
    context.instruction_renderer = &fcml_fn_rend_render_instruction_intel;
    return context;
}
