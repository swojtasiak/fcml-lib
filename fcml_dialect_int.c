/*
 * fcml_asm_dialect.c
 *
 *  Created on: 2 wrz 2013
 *      Author: tAs
 */

#include "fcml_dialect_int.h"
#include "fcml_env.h"

fcml_st_mp_mnemonic *fcml_fn_asm_dialect_alloc_mnemonic_with_suffix( fcml_st_mp_mnemonic *mnemonic, fcml_string suffix ) {

    if( !suffix ) {
        return fcml_fn_asm_dialect_alloc_mnemonic( mnemonic );
    }

    fcml_st_mp_mnemonic *new_mnemonic = fcml_fn_env_memory_alloc( sizeof( fcml_st_mp_mnemonic ) );
    if( !new_mnemonic ) {
        // Out of memory.
        return NULL;
    }

    *new_mnemonic = *mnemonic;

    fcml_usize mnemonic_len = fcml_fn_env_str_strlen( mnemonic->mnemonic );
    fcml_usize suffix_len = fcml_fn_env_str_strlen( suffix );
    fcml_string dest_mnemonic = fcml_fn_env_str_stralloc( mnemonic_len + suffix_len + 1 );
    if( dest_mnemonic ) {
        fcml_fn_env_str_strncpy( dest_mnemonic, mnemonic->mnemonic, mnemonic_len );
        fcml_fn_env_str_strncpy( dest_mnemonic + mnemonic_len, suffix, suffix_len );
        new_mnemonic->mnemonic = dest_mnemonic;
    } else {
        // Out of memory, free allocated mnemonic.
        fcml_fn_env_memory_free( new_mnemonic );
        new_mnemonic = NULL;
    }

    return new_mnemonic;
}

fcml_st_mp_mnemonic *fcml_fn_asm_dialect_alloc_mnemonic( fcml_st_mp_mnemonic *mnemonic ) {

    fcml_st_mp_mnemonic *new_mnemonic = fcml_fn_env_memory_alloc( sizeof( fcml_st_mp_mnemonic ) );
    if( !new_mnemonic ) {
        // Out of memory.
        return NULL;
    }

    *new_mnemonic = *mnemonic;

    fcml_string dest_mnemonic = fcml_fn_env_str_strdup( mnemonic->mnemonic );
    if( dest_mnemonic ) {
        new_mnemonic->mnemonic = dest_mnemonic;
    } else {
        // Out of memory, free allocated mnemonic.
        fcml_fn_env_memory_free( new_mnemonic );
        new_mnemonic = NULL;
    }

    return new_mnemonic;
}

void fcml_fn_asm_dialect_free_mnemonic( fcml_st_mp_mnemonic *mnemonic ) {
    if( mnemonic ) {
        if( mnemonic->mnemonic ) {
            fcml_fn_env_str_strfree( mnemonic->mnemonic );
        }
        fcml_fn_env_memory_free( mnemonic );
    }
}
