/*
 * fcml_mnemonic_parser.c
 *
 *  Created on: 5 wrz 2013
 *      Author: tAs
 */

#include "fcml_mnemonic_parser.h"

#include <stdlib.h>

#include "fcml_common.h"
#include "fcml_types.h"

enum fcml_ien_mp_parser_state {
    FCML_MP_PS_MNEMONIC,
    FCML_MP_PS_BETWEEN_MNEMONICS,
    FCML_MP_PS_ATTRIBUTE_KEY,
    FCML_MP_PS_ATTRIBUTE_VALUE
};

#define FCML_IDF_MP_BUFF_LEN 256

void fcml_ifn_mp_clean_mnemonic( fcml_st_mp_mnemonic *mnemonic ) {
    mnemonic->supported_osa = FCML_DS_UNDEF;
    mnemonic->supported_asa = FCML_DS_UNDEF;
    mnemonic->shortcut = FCML_FALSE;
    mnemonic->mnemonic = NULL;
    mnemonic->pseudo_op.is_not_null = FCML_FALSE;
    mnemonic->pseudo_op.value = 0x00;
}

fcml_ceh_error fcml_ifn_mp_dup_mnemonic( fcml_st_mp_mnemonic *parsed_mnemonic, fcml_st_coll_list *mnemonics, fcml_string mnemonic_buff, fcml_usize len ) {

    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

    // Allocate space for new mnemonic.
    fcml_st_mp_mnemonic *new_mnemonic =  fcml_fn_env_memory_alloc_clear( sizeof( fcml_st_mp_mnemonic ) );
    if( new_mnemonic == NULL ) {
        return FCML_CEH_GEC_OUT_OF_MEMORY;
    }

    // Prepare mnemonic string.
    *new_mnemonic = *parsed_mnemonic;

    new_mnemonic->mnemonic = fcml_fn_env_str_stralloc( len + 1 );
    if( new_mnemonic->mnemonic == NULL ) {
        fcml_fn_env_memory_free( new_mnemonic );
        return FCML_CEH_GEC_OUT_OF_MEMORY;
    } else {
        fcml_fn_env_str_strncpy( new_mnemonic->mnemonic, mnemonic_buff, len );
    }

    // Add mnemonic to list of already parsed mnemonics.
    if( !fcml_fn_coll_list_add_back( mnemonics, new_mnemonic ) ) {
        fcml_fn_env_str_strfree( new_mnemonic->mnemonic );
        fcml_fn_env_memory_free( new_mnemonic );
        error = FCML_CEH_GEC_OUT_OF_MEMORY;
    }

    return error;
}

fcml_ceh_error fcml_ifn_parse_attribute_size_flag( fcml_char flag_code, fcml_data_size *flags ) {
    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
    switch( flag_code ) {
    case 'w':
        *flags = FCML_DS_16;
        break;
    case 'd':
        *flags = FCML_DS_32;
        break;
    case 'q':
        *flags = FCML_DS_64;
        break;
    case '*':
        *flags = FCML_DS_UNDEF;
        break;
    default:
        error = FCML_CEH_GEC_INVALID_INPUT;
    }
    return error;
}

fcml_ceh_error fcml_ifn_handle_attribute_value( fcml_char attr_key, fcml_char *attr_value, int attr_value_len, fcml_st_mp_mnemonic *mnemonic ) {
    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
    // Handle attributes.
    switch( attr_key ) {
    case 't':
        if( attr_value[0] == 's' ) {
            mnemonic->shortcut = FCML_TRUE;
        } else {
            // Currently this attribute can be set to 's' only.
            error = FCML_CEH_GEC_INVALID_INPUT;
        }
        break;
    case 'o':
        error = fcml_ifn_parse_attribute_size_flag( attr_value[0], &mnemonic->supported_osa );
        break;
    case 'a':
        error = fcml_ifn_parse_attribute_size_flag( attr_value[0], &mnemonic->supported_asa );
        break;
    case 'p':
        if( attr_value_len == 2 ) {
            // TODO: Zmienic to na rozwiazanie abrdziej prznosnie, rozszrzeyc env o operacje na stringach.
            unsigned long val = strtoul(attr_value, NULL, 16);
            mnemonic->pseudo_op.value = (fcml_uint8_t)val;
            mnemonic->pseudo_op.is_not_null = FCML_TRUE;
        } else {
            error = FCML_CEH_GEC_INVALID_INPUT;;
        }
        break;
    default:
        // Unknown attribute key.
        error = FCML_CEH_GEC_INVALID_INPUT;
    }
    return error;
}

fcml_ceh_error fcml_fn_mp_parse_mnemonics( fcml_string mnemonics_pattern, fcml_st_mp_mnemonic_set **mnemonics_set ) {

    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
    fcml_char mnemonic_buff[FCML_IDF_MP_BUFF_LEN];
    int mnemonic_index = 0;

    fcml_st_mp_mnemonic_set *mnemonics = fcml_fn_env_memory_alloc_clear( sizeof( fcml_st_mp_mnemonic_set ) );
    if( !mnemonics ) {
        return FCML_CEH_GEC_OUT_OF_MEMORY;
    }

    mnemonics->mnemonics = fcml_fn_coll_list_alloc();
    if( !mnemonics->mnemonics ) {
        fcml_fn_env_memory_free( mnemonics );
        return FCML_CEH_GEC_OUT_OF_MEMORY;
    }

    fcml_usize len = fcml_fn_env_str_strlen( mnemonics_pattern );

    fcml_st_mp_mnemonic mnemonic;

    fcml_ifn_mp_clean_mnemonic( &mnemonic );

    enum fcml_ien_mp_parser_state state = FCML_MP_PS_MNEMONIC;
    fcml_char attr_key;
    int attr_value_index = 0;
    fcml_char attr_value[6];
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
                fcml_ifn_mp_clean_mnemonic( &mnemonic );
                mnemonic_index = 0;
            break;
            default:
                if( mnemonic_index < FCML_IDF_MP_BUFF_LEN && ( fcml_fn_env_is_alpha( c ) || fcml_fn_env_is_digit( c ) || c == '_' ) ) {
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
                if( state != FCML_MP_PS_ATTRIBUTE_VALUE || attr_value_index == 0 ) {
                    error = FCML_CEH_GEC_INVALID_INPUT;
                    break;
                }
                // Handle last mnemonic attribute.
                error = fcml_ifn_handle_attribute_value( attr_key, attr_value, attr_value_index, &mnemonic );
                attr_value_index = 0;
                state = FCML_MP_PS_BETWEEN_MNEMONICS;
                break;
            case ',':
                if( state != FCML_MP_PS_ATTRIBUTE_VALUE || attr_value_index == 0 ) {
                    error = FCML_CEH_GEC_INVALID_INPUT;
                    break;
                }
                error = fcml_ifn_handle_attribute_value( attr_key, attr_value, attr_value_index, &mnemonic );
                attr_value_index = 0;
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
                    if( ( fcml_fn_env_is_alpha( c ) || fcml_fn_env_is_digit( c ) || c == '*' ) && attr_value_index < 5 ) {
                        attr_value[attr_value_index++] = c;
                        attr_value[attr_value_index] = '\0';
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

fcml_st_mp_mnemonic *fcml_fn_mp_choose_mnemonic( fcml_st_mp_mnemonic_set *mnemonics, fcml_bool use_shortcut, fcml_nuint8_t pseudo_opcode, fcml_data_size osa, fcml_data_size asa ) {
    fcml_st_mp_mnemonic *chosen_mnemonic = NULL;
    if( mnemonics->mnemonics ) {
        fcml_st_coll_list_element *next = mnemonics->mnemonics->head;
        while( next ) {
            fcml_st_mp_mnemonic *mnemonic = next->item;
            if( !chosen_mnemonic && !mnemonic->shortcut ) {
                chosen_mnemonic = mnemonic;
            }
            if( fcml_fn_cmi_is_attribute_size_supported( mnemonic->supported_asa, asa ) && fcml_fn_cmi_is_attribute_size_supported( mnemonic->supported_osa, osa ) ) {
                if( ( mnemonic->shortcut == use_shortcut ) || ( use_shortcut && mnemonic->pseudo_op.is_not_null && mnemonic->pseudo_op.value == pseudo_opcode.value ) ) {
                    chosen_mnemonic = mnemonic;
                    break;
                }
            }
            next = next->next;
        }
    }
    return chosen_mnemonic;

}

void fcml_ifp_coll_list_action_free_mnemonic( fcml_ptr item_value, fcml_ptr args ) {
    if( item_value ) {
        fcml_st_mp_mnemonic *parsed_mnemonic = (fcml_st_mp_mnemonic *)item_value;
        if( parsed_mnemonic->mnemonic ) {
            fcml_fn_env_str_strfree( parsed_mnemonic->mnemonic );
        }
        fcml_fn_env_memory_free( parsed_mnemonic );
    }
}

void fcml_fn_mp_free_mnemonics( fcml_st_mp_mnemonic_set *mnemonics ) {
    if( mnemonics ) {
        if( mnemonics->mnemonics ) {
            fcml_fn_coll_list_free( mnemonics->mnemonics, &fcml_ifp_coll_list_action_free_mnemonic, NULL );
        }
        fcml_fn_env_memory_free( mnemonics );
    }
}
