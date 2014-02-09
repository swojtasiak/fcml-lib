/*
 * fcml_asm_dialect.c
 *
 *  Created on: 2 wrz 2013
 *      Author: tAs
 */

#include "fcml_dialect_int.h"

#include <stddef.h>

#include "fcml_ceh.h"
#include "fcml_coll.h"
#include "fcml_env.h"
#include "fcml_types.h"
#include "fcml_utils.h"

fcml_st_mp_mnemonic *fcml_fn_asm_dialect_alloc_mnemonic_with_suffix( fcml_st_mp_mnemonic *mnemonic, fcml_string suffix ) {

    if( !suffix ) {
        return fcml_fn_asm_dialect_alloc_mnemonic( mnemonic );
    }

    fcml_st_mp_mnemonic *new_mnemonic = (fcml_st_mp_mnemonic*)fcml_fn_env_memory_alloc( sizeof( fcml_st_mp_mnemonic ) );
    if( !new_mnemonic ) {
        /* Out of memory.*/
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
        /* Out of memory, free allocated mnemonic.*/
        fcml_fn_env_memory_free( new_mnemonic );
        new_mnemonic = NULL;
    }

    return new_mnemonic;
}

fcml_st_mp_mnemonic *fcml_fn_asm_dialect_alloc_mnemonic( fcml_st_mp_mnemonic *mnemonic ) {

    fcml_st_mp_mnemonic *new_mnemonic = (fcml_st_mp_mnemonic*)fcml_fn_env_memory_alloc( sizeof( fcml_st_mp_mnemonic ) );
    if( !new_mnemonic ) {
        /* Out of memory.*/
        return NULL;
    }

    *new_mnemonic = *mnemonic;

    fcml_string dest_mnemonic = fcml_fn_env_str_strdup( mnemonic->mnemonic );
    if( dest_mnemonic ) {
        new_mnemonic->mnemonic = dest_mnemonic;
    } else {
        /* Out of memory, free allocated mnemonic.*/
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

fcml_ceh_error fcml_fn_asm_dialect_alloc_mnemonic_lookup( fcml_st_dialect_context_int **out_dialect_context, fcml_st_dialect_mnemonic *mnemonic, fcml_usize capacity ) {

    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

    fcml_st_dialect_context_int *dialect_context = (fcml_st_dialect_context_int*)fcml_fn_env_memory_alloc_clear( sizeof( fcml_st_dialect_context_int ) );
    if( !dialect_context ) {
        return FCML_CEH_GEC_OUT_OF_MEMORY;
    }

    /* Prepare mnemonic lookup.*/
    fcml_int map_error;
    dialect_context->dialect_mnemonics_lookup = fcml_fn_coll_map_alloc( &fcml_coll_map_descriptor_uint32, capacity, &map_error );
    if( map_error ) {
        fcml_fn_env_memory_free( dialect_context );
        return fcml_fn_utils_convert_map_error( map_error );
    }

    fcml_st_dialect_mnemonic *current = mnemonic;
    while( current->mnemonic ) {
        fcml_fn_coll_map_put( dialect_context->dialect_mnemonics_lookup, &(current->instruction), current, &map_error );
        if( map_error ) {
            fcml_fn_coll_map_free( dialect_context->dialect_mnemonics_lookup );
            fcml_fn_env_memory_free( dialect_context );
            return fcml_fn_utils_convert_map_error( map_error );
        }
        current++;
    }

    *out_dialect_context = dialect_context;

    return error;
}

void fcml_fn_asm_dialect_free_mnemonic_lookup( fcml_st_dialect_context_int *dialect_context ) {
    if( dialect_context && dialect_context->dialect_mnemonics_lookup ) {
        fcml_fn_coll_map_free( dialect_context->dialect_mnemonics_lookup );
    }
}
