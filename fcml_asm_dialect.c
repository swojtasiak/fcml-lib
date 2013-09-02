/*
 * fcml_asm_dialect.c
 *
 *  Created on: 2 wrz 2013
 *      Author: tAs
 */

#include "fcml_asm_dialect.h"
#include "fcml_env.h"

fcml_string fcml_fn_asm_dialect_alloc_mnemonic_with_suffix( fcml_string mnemonic, fcml_string suffix ) {
    if( !mnemonic ) {
        return NULL;
    }
    if( !suffix ) {
        return fcml_fn_asm_dialect_alloc_mnemonic( mnemonic );
    }
    fcml_usize mnemonic_len = fcml_fn_env_memory_strlen( mnemonic );
    fcml_usize suffix_len = fcml_fn_env_memory_strlen( suffix );
    fcml_string dest_mnemonic = fcml_fn_env_clear_memory_alloc( mnemonic_len + suffix_len + 1 );
    if( dest_mnemonic != NULL ) {
        fcml_fn_env_memory_copy( dest_mnemonic, mnemonic, mnemonic_len );
        fcml_fn_env_memory_copy( dest_mnemonic + mnemonic_len, suffix, suffix_len );
    }
    return dest_mnemonic;
}

fcml_string fcml_fn_asm_dialect_alloc_mnemonic( fcml_string mnemonic ) {
    if( !mnemonic ) {
        return NULL;
    }
    fcml_usize len = fcml_fn_env_memory_strlen( mnemonic );
    fcml_string dest_mnemonic = fcml_fn_env_clear_memory_alloc( len + 1 );
    if( dest_mnemonic != NULL ) {
        fcml_fn_env_memory_copy( dest_mnemonic, mnemonic, len );
    }
    return dest_mnemonic;
}

void fcml_fn_asm_dialect_free_mnemonic( fcml_string mnemonic ) {
    if( mnemonic ) {
        fcml_fn_env_memory_free( mnemonic );
    }
}
