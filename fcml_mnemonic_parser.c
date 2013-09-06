/*
 * fcml_mnemonic_parser.c
 *
 *  Created on: 5 wrz 2013
 *      Author: tAs
 */

#include "fcml_mnemonic_parser.h"

enum fcml_ien_mp_parser_state {
    FCML_MP_PS_MNEMONIC,
    FCML_MP_PS_BETWEEN_MNEMONICS,
    FCML_MP_PS_ATTRIBUTE_KEY,
    FCML_MP_PS_ATTRIBUTE_VALUE,
    FCML_MP_PS_BETWEEN_ATTRIBUTES
};

#define FCML_IDF_MP_BUFF_LEN 256

void fcml_ifn_mp_clean_mnemonic( fcml_st_mp_mnemonic *mnemonic ) {
    mnemonic->supported_osa = FCML_EN_ASF_ALL;
    mnemonic->supported_asa = FCML_EN_ASF_ALL;
    mnemonic->shortcut = FCML_FALSE;
    mnemonic->mnemonic = NULL;
}

fcml_ceh_error fcml_ifn_mp_dup_mnemonic( fcml_st_mp_mnemonic *parsed_mnemonic, fcml_st_coll_list *mnemonics, fcml_string mnemonic_buff, fcml_usize len ) {

    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

    // Allocate space for new mnemonic.
    fcml_st_mp_mnemonic *new_mnemonic =  fcml_fn_env_clear_memory_alloc( sizeof( fcml_st_mp_mnemonic ) );
    if( new_mnemonic == NULL ) {
        return FCML_CEH_GEC_OUT_OF_MEMORY;
    }

    // Prepare mnemonic string.
    *new_mnemonic = *parsed_mnemonic;

    new_mnemonic->mnemonic = fcml_fn_env_memory_stralloc( len + 1 );
    if( new_mnemonic->mnemonic == NULL ) {
        fcml_fn_env_memory_free( new_mnemonic );
        return FCML_CEH_GEC_OUT_OF_MEMORY;
    } else {
        fcml_fn_env_memory_strncpy( new_mnemonic->mnemonic, mnemonic_buff, len );
    }

    // Add mnemonic to list of already parsed mnemonics.
    if( !fcml_fn_coll_list_add_back( mnemonics, new_mnemonic ) ) {
        fcml_fn_env_memory_strfree( new_mnemonic->mnemonic );
        fcml_fn_env_memory_free( new_mnemonic );
        error = FCML_CEH_GEC_OUT_OF_MEMORY;
    }

    return error;
}

fcml_ceh_error fcml_ifn_parse_attribute_size_flag( fcml_char flag_code, fcml_en_attribute_size_flag *flags ) {
    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
    switch( flag_code ) {
    case 'w':
        *flags = FCML_EN_ASF_16;
        break;
    case 'd':
        *flags = FCML_EN_ASF_32;
        break;
    case 'q':
        *flags = FCML_EN_ASF_64;
        break;
    case '*':
        *flags = FCML_EN_ASF_ALL;
        break;
    default:
        error = FCML_CEH_GEC_INVALID_INPUT;
    }
    return error;
}

fcml_ceh_error fcml_fn_mp_parse_mnemonics( fcml_string mnemonics_pattern, fcml_st_mp_mnemonic_set **mnemonics_set ) {

    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
    fcml_char mnemonic_buff[FCML_IDF_MP_BUFF_LEN];
    int mnemonic_index = 0;

    fcml_st_mp_mnemonic_set *mnemonics = fcml_fn_env_clear_memory_alloc( sizeof( fcml_st_mp_mnemonic_set ) );
    if( !mnemonics ) {
        return FCML_CEH_GEC_OUT_OF_MEMORY;
    }

    mnemonics->mnemonics = fcml_fn_coll_list_alloc();
    if( !mnemonics->mnemonics ) {
        fcml_fn_env_memory_free( mnemonics );
        return FCML_CEH_GEC_OUT_OF_MEMORY;
    }

    fcml_usize len = fcml_fn_env_memory_strlen( mnemonics_pattern );

    fcml_st_mp_mnemonic mnemonic;

    fcml_ifn_mp_clean_mnemonic( &mnemonic );

    enum fcml_ien_mp_parser_state state = FCML_MP_PS_MNEMONIC;
    fcml_char attr_key;
    fcml_char attr_value;
    fcml_usize i;

    // Main loop of simple finite-state machine parser.
    for( i = 0; i < len && !error; i++ ) {

        fcml_char c = mnemonics_pattern[i];

        if( state == FCML_MP_PS_MNEMONIC ) {
            switch( c ) {
            case '[':
                if( mnemonic_index > 0 ) {
                    state = FCML_MP_PS_ATTRIBUTE_KEY;
                } else {
                    // empty mnemonic.
                    error = FCML_CEH_GEC_INVALID_INPUT;
                }
            break;
            case ';':
                if( mnemonic_index > 0 ) {
                    error = fcml_ifn_mp_dup_mnemonic( &mnemonic, mnemonics->mnemonics, mnemonic_buff, mnemonic_index );
                } else {
                    // empty mnemonic.
                    error = FCML_CEH_GEC_INVALID_INPUT;
                }
                mnemonic_index = 0;
            break;
            default:
                if( mnemonic_index < FCML_IDF_MP_BUFF_LEN && ( fcml_fn_env_is_alpha( c ) || fcml_fn_env_is_digit( c ) ) ) {
                    mnemonic_buff[mnemonic_index++] = c;
                } else {
                    error = FCML_CEH_GEC_INVALID_INPUT;
                }
                break;
            }
        } else if( state == FCML_MP_PS_BETWEEN_MNEMONICS ) {

            if( c != ';' ) {
                error = FCML_CEH_GEC_INVALID_INPUT;
                break;
            }

            error = fcml_ifn_mp_dup_mnemonic( &mnemonic, mnemonics->mnemonics, mnemonic_buff, mnemonic_index );

            mnemonic_index = 0;

            state = FCML_MP_PS_MNEMONIC;

        } else {
            switch( c ) {
            case ']':
                if( state != FCML_MP_PS_BETWEEN_ATTRIBUTES ) {
                    error = FCML_CEH_GEC_INVALID_INPUT;
                    break;
                }
                state = FCML_MP_PS_BETWEEN_MNEMONICS;
                break;
            case ',':
                if( state != FCML_MP_PS_BETWEEN_ATTRIBUTES ) {
                    error = FCML_CEH_GEC_INVALID_INPUT;
                    break;
                }
                state = FCML_MP_PS_ATTRIBUTE_KEY;
                break;
            default:
                if( state != FCML_MP_PS_ATTRIBUTE_KEY && state != FCML_MP_PS_ATTRIBUTE_VALUE ) {
                    error = FCML_CEH_GEC_INVALID_INPUT;
                    break;
                }
                if( state == FCML_MP_PS_ATTRIBUTE_KEY ) {
                    if( fcml_fn_env_is_alpha( c ) ) {
                        attr_key = c;
                        state = FCML_MP_PS_ATTRIBUTE_VALUE;
                    } else {
                        error = FCML_CEH_GEC_INVALID_INPUT;
                    }
                } else if( state == FCML_MP_PS_ATTRIBUTE_VALUE ) {
                    if( fcml_fn_env_is_alpha( c ) || fcml_fn_env_is_digit( c ) || c == '*' ) {
                        attr_value = c;

                        // Handle attributes.
                        switch( attr_key ) {
                        case 't':
                        if( attr_value == 's' ) {
                            mnemonic.shortcut = FCML_TRUE;
                        } else {
                            // Currently this attribute can be set to 's' only.
                            error = FCML_CEH_GEC_INVALID_INPUT;
                        }
                        break;
                        case 'o':
                            error = fcml_ifn_parse_attribute_size_flag( attr_value, &mnemonic.supported_osa );
                        break;
                        case 'a':
                            error = fcml_ifn_parse_attribute_size_flag( attr_value, &mnemonic.supported_asa );
                        break;
                        default:
                            // Unknown attribute key.
                            error = FCML_CEH_GEC_INVALID_INPUT;
                        }

                        state = FCML_MP_PS_BETWEEN_ATTRIBUTES;

                    } else {
                        error = FCML_CEH_GEC_INVALID_INPUT;
                    }
                }
            }
        }
    }

    if( state != FCML_MP_PS_MNEMONIC && state != FCML_MP_PS_BETWEEN_MNEMONICS ) {
        error = FCML_CEH_GEC_INVALID_INPUT;
    }

    if( !error && mnemonic_index ) {
        error = fcml_ifn_mp_dup_mnemonic( &mnemonic, mnemonics->mnemonics, mnemonic_buff, mnemonic_index );
    }

    if( error ) {
        fcml_fn_mp_free_mnemonics( mnemonics );
    } else {
        if( mnemonics->mnemonics->size ) {
            *mnemonics_set = mnemonics;
        } else {
            // There is no mnemonic in the list.
            fcml_fn_mp_free_mnemonics( mnemonics );
            error = FCML_CEH_GEC_INVALID_INPUT;
        }
    }

    return error;
}

fcml_st_mp_mnemonic *fcml_fn_mp_choose_mnemonic( fcml_st_mp_mnemonic_set *mnemonics, fcml_bool use_shortcut, fcml_data_size osa, fcml_data_size asa ) {
    fcml_st_mp_mnemonic *chosen_mnemonic = NULL;
    if( mnemonics->mnemonics ) {
        fcml_st_coll_list_element *next = mnemonics->mnemonics->head;
        while( next ) {
            fcml_st_mp_mnemonic *mnemonic = next->item;
            if( !chosen_mnemonic && !mnemonic->shortcut ) {
                chosen_mnemonic = mnemonic;
            }
            if( fcml_fn_cmi_is_attribute_size_supported( mnemonic->supported_asa, asa ) && fcml_fn_cmi_is_attribute_size_supported( mnemonic->supported_osa, osa ) ) {
                if( mnemonic->shortcut == use_shortcut ) {
                    chosen_mnemonic = mnemonic;
                    break;
                }
            }
            next = next->next;
        }
    }
    return chosen_mnemonic;

}

void fcml_ifp_coll_list_action_free_mnemonic( fcml_ptr item_value, fcml_ptr *args ) {
    if( item_value ) {
        fcml_st_mp_mnemonic *parsed_mnemonic = (fcml_st_mp_mnemonic *)item_value;
        if( parsed_mnemonic->mnemonic ) {
            fcml_fn_env_memory_strfree( parsed_mnemonic->mnemonic );
        }
        fcml_fn_env_memory_free( parsed_mnemonic );
    }
}

void fcml_fn_mp_free_mnemonics( fcml_st_mp_mnemonic_set *mnemonics ) {
    if( mnemonics ) {
        if( mnemonics->mnemonics ) {
            fcml_fn_coll_list_free( mnemonics->mnemonics, &fcml_ifp_coll_list_action_free_mnemonic );
        }
        fcml_fn_env_memory_free( mnemonics );
    }
}
