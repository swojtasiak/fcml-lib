/*
 * FCML - Free Code Manipulation Library.
 * Copyright (C) 2010-2020 Slawomir Wojtasiak
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

/*
 * mm - Mnemonic for addressing mode using memory addressing.
 * mr - Mnemonic for addressing mode without memory addressing.
 * sb - Sets memory data size to one byte.
 * sf - Sets memory data size to "supported_osa" which can be set using "oX"
 *      mnemonic attributes.
 * oX (X=dwq) - Sets supported operand size attribute to 16, 32 or 64 bits.
 * aX (X=dwq) - Sets supported address size attribute to 16, 32 or 64 bits.
 * ts - Sets "shortcut" flags for mnemonic.
 * tb - Sets "shortcut/classic" flag for mnemonic.
 * pXX - Sets pseudo opcode value for mnemonic.
 * dXX - Sets memory data size to specified number of bytes. It has greater
 *       priority than "sb" and "sf".
 * l0 - Mnemonic for L flag set to 0.
 * l1 - Mnemonic for L flag set to 1.
 * Sxx - One byte instruction suffix, used by AMD 3DNow for instance.
 *
 */

#include "fcml_mnemonic_parser.h"

#include <stdlib.h>

#include <fcml_common.h>
#include <fcml_types.h>

enum parser_state {
    FCML_MP_PS_MNEMONIC,
    FCML_MP_PS_BETWEEN_MNEMONICS,
    FCML_MP_PS_ATTRIBUTE_KEY,
    FCML_MP_PS_ATTRIBUTE_VALUE
};

#define FCML_IDF_MP_BUFF_LEN 256

static void clean_mnemonic(fcml_st_mp_mnemonic *mnemonic) {
    mnemonic->supported_osa = FCML_DS_UNDEF;
    mnemonic->supported_asa = FCML_DS_UNDEF;
    mnemonic->mnemonic = NULL;
    mnemonic->pseudo_op.is_not_null = FCML_FALSE;
    mnemonic->pseudo_op.value = 0x00;
    mnemonic->memory_data.is_not_null = FCML_FALSE;
    mnemonic->memory_data.value = 0x00;
    mnemonic->is_shortcut = FCML_FALSE;
    mnemonic->is_classic = FCML_TRUE;
    mnemonic->is_byte_ds = FCML_FALSE;
    mnemonic->is_full_ds = FCML_FALSE;
    mnemonic->is_mode_mem_only = FCML_FALSE;
    mnemonic->is_mode_reg_only = FCML_FALSE;
    mnemonic->is_default = FCML_TRUE;
    mnemonic->l.value = 0;
    mnemonic->l.is_not_null = FCML_FALSE;
    mnemonic->suffix.is_not_null = FCML_FALSE;
    mnemonic->suffix.value = 0x00;
}

static fcml_ceh_error dup_mnemonic(fcml_st_mp_mnemonic *parsed_mnemonic,
        fcml_st_coll_list *mnemonics, fcml_string mnemonic_buff, fcml_usize len) {

    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

    /* Allocate space for new mnemonic.*/
    fcml_st_mp_mnemonic *new_mnemonic =
            (fcml_st_mp_mnemonic*) fcml_fn_env_memory_alloc_clear(
                    sizeof(fcml_st_mp_mnemonic));
    if (new_mnemonic == NULL) {
        return FCML_CEH_GEC_OUT_OF_MEMORY;
    }

    /* Prepare mnemonic string.*/
    *new_mnemonic = *parsed_mnemonic;

    new_mnemonic->mnemonic = fcml_fn_env_str_stralloc(len + 1);
    if (new_mnemonic->mnemonic == NULL) {
        fcml_fn_env_memory_free(new_mnemonic);
        return FCML_CEH_GEC_OUT_OF_MEMORY;
    } else {
        fcml_fn_env_str_strncpy(new_mnemonic->mnemonic, mnemonic_buff, len);
    }

    /* Add mnemonic to list of already parsed mnemonics.*/
    if (!fcml_fn_coll_list_add_back(mnemonics, new_mnemonic)) {
        fcml_fn_env_str_strfree(new_mnemonic->mnemonic);
        fcml_fn_env_memory_free(new_mnemonic);
        error = FCML_CEH_GEC_OUT_OF_MEMORY;
    }

    return error;
}

static fcml_ceh_error parse_attribute_size_flag(fcml_char flag_code,
        fcml_usize *flags) {
    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
    switch (flag_code) {
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

static fcml_ceh_error handle_attribute_value(fcml_char attr_key,
        fcml_char *attr_value, int attr_value_len,
        fcml_st_mp_mnemonic *mnemonic) {
    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
    /* Handle attributes. */
    switch (attr_key) {
    case 'l':
        if (attr_value[0] == '0') {
            mnemonic->l.value = 0;
        } else if (attr_value[0] == '1') {
            mnemonic->l.value = 1;
        } else if (attr_value[0] == '2') {
            mnemonic->l.value = 2;
        }
        mnemonic->l.is_not_null = FCML_TRUE;
        break;
    case 'm':
        if (attr_value[0] == 'm') {
            mnemonic->is_mode_mem_only = FCML_TRUE;
        } else if (attr_value[0] == 'r') {
            mnemonic->is_mode_reg_only = FCML_TRUE;
        }
        break;
    case 's':
        if (attr_value[0] == 'b') {
            mnemonic->is_byte_ds = FCML_TRUE;
        } else if (attr_value[0] == 'f') {
            mnemonic->is_full_ds = FCML_TRUE;
        }
        break;
    case 'S':
        if (attr_value_len == 2) {
            unsigned long int val = strtoul(attr_value, NULL, 16);
            mnemonic->suffix.value = (fcml_uint8_t) val;
            mnemonic->suffix.is_not_null = FCML_TRUE;
        } else {
            error = FCML_CEH_GEC_INVALID_INPUT;
        }
        break;
    case 't':
        if (attr_value[0] == 's') {
            mnemonic->is_shortcut = FCML_TRUE;
            mnemonic->is_classic = FCML_FALSE;
        } else if (attr_value[0] == 'b') {
            mnemonic->is_shortcut = FCML_TRUE;
            mnemonic->is_classic = FCML_TRUE;
        } else {
            /* Currently this attribute can be set to 's' only.*/
            error = FCML_CEH_GEC_INVALID_INPUT;
        }
        break;
    case 'o':
        error = parse_attribute_size_flag(attr_value[0],
                &mnemonic->supported_osa);
        break;
    case 'a':
        error = parse_attribute_size_flag(attr_value[0],
                &mnemonic->supported_asa);
        break;
    case 'd':
        if (attr_value_len == 2) {
            unsigned long int val = strtoul(attr_value, NULL, 16);
            mnemonic->memory_data.value = (fcml_uint8_t) val;
            mnemonic->memory_data.is_not_null = FCML_TRUE;
        } else {
            error = FCML_CEH_GEC_INVALID_INPUT;
        }
        break;
    case 'p':
        if (attr_value_len == 2) {
            unsigned long int val = strtoul(attr_value, NULL, 16);
            mnemonic->pseudo_op.value = (fcml_uint8_t) val;
            mnemonic->pseudo_op.is_not_null = FCML_TRUE;
        } else {
            error = FCML_CEH_GEC_INVALID_INPUT;
        }
        break;
    default:
        /* Unknown attribute key.*/
        error = FCML_CEH_GEC_INVALID_INPUT;
    }
    return error;
}

static fcml_bool is_attribute_size_supported(
        fcml_usize supported_attribute_size, fcml_usize attribute_size) {
    if (supported_attribute_size == FCML_DS_UNDEF) {
        return FCML_TRUE;
    }
    return supported_attribute_size == attribute_size;
}

static void coll_list_action_free_mnemonic(fcml_ptr item_value, fcml_ptr args) {
    if (item_value) {
        fcml_st_mp_mnemonic *parsed_mnemonic = (fcml_st_mp_mnemonic*) item_value;
        if (parsed_mnemonic->mnemonic) {
            fcml_fn_env_str_strfree(parsed_mnemonic->mnemonic);
        }
        fcml_fn_env_memory_free(parsed_mnemonic);
    }
}

fcml_ceh_error fcml_fn_mp_parse_mnemonics(fcml_string mnemonics_pattern,
        fcml_st_mp_mnemonic_set **mnemonics_set) {

    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
    fcml_char mnemonic_buff[FCML_IDF_MP_BUFF_LEN];
    int mnemonic_index = 0;

    fcml_st_mp_mnemonic_set *mnemonics =
            (fcml_st_mp_mnemonic_set*) fcml_fn_env_memory_alloc_clear(
                    sizeof(fcml_st_mp_mnemonic_set));
    if (!mnemonics) {
        return FCML_CEH_GEC_OUT_OF_MEMORY;
    }

    mnemonics->mnemonics = fcml_fn_coll_list_alloc();
    if (!mnemonics->mnemonics) {
        fcml_fn_env_memory_free(mnemonics);
        return FCML_CEH_GEC_OUT_OF_MEMORY;
    }

    fcml_usize len = fcml_fn_env_str_strlen(mnemonics_pattern);

    fcml_st_mp_mnemonic mnemonic;

    clean_mnemonic(&mnemonic);

    enum parser_state state = FCML_MP_PS_MNEMONIC;
    fcml_char attr_key;
    int attr_value_index = 0;
    fcml_char attr_value[6];
    fcml_usize i;

    /* Main loop of simple finite-state machine parser.*/
    for (i = 0; i < len && !error; i++) {

        fcml_char c = mnemonics_pattern[i];

        if (state == FCML_MP_PS_MNEMONIC) {
            switch (c) {
            case '[':
                if (mnemonic_index > 0) {
                    state = FCML_MP_PS_ATTRIBUTE_KEY;
                    mnemonic.is_default = FCML_FALSE;
                } else {
                    /* empty mnemonic.*/
                    error = FCML_CEH_GEC_INVALID_INPUT;
                }
                break;
            case ';':
                if (mnemonic_index > 0) {
                    error = dup_mnemonic(&mnemonic, mnemonics->mnemonics,
                            mnemonic_buff, mnemonic_index);
                } else {
                    /* empty mnemonic.*/
                    error = FCML_CEH_GEC_INVALID_INPUT;
                }
                clean_mnemonic(&mnemonic);
                mnemonic_index = 0;
                break;
            default:
                if (mnemonic_index < FCML_IDF_MP_BUFF_LEN
                        && (fcml_fn_env_is_alpha(c) || fcml_fn_env_is_digit(c)
                                || c == '_')) {
                    mnemonic_buff[mnemonic_index++] = c;
                } else {
                    error = FCML_CEH_GEC_INVALID_INPUT;
                }
                break;
            }
        } else if (state == FCML_MP_PS_BETWEEN_MNEMONICS) {

            if (c != ';') {
                error = FCML_CEH_GEC_INVALID_INPUT;
                break;
            }

            error = dup_mnemonic(&mnemonic, mnemonics->mnemonics, mnemonic_buff,
                    mnemonic_index);

            clean_mnemonic(&mnemonic);
            mnemonic_index = 0;

            state = FCML_MP_PS_MNEMONIC;

        } else {
            switch (c) {
            case ']':
                if (state != FCML_MP_PS_ATTRIBUTE_VALUE
                        || attr_value_index == 0) {
                    error = FCML_CEH_GEC_INVALID_INPUT;
                    break;
                }
                /* Handle last mnemonic attribute.*/
                error = handle_attribute_value(attr_key, attr_value,
                        attr_value_index, &mnemonic);
                attr_value_index = 0;
                state = FCML_MP_PS_BETWEEN_MNEMONICS;
                break;
            case ',':
                if (state != FCML_MP_PS_ATTRIBUTE_VALUE
                        || attr_value_index == 0) {
                    error = FCML_CEH_GEC_INVALID_INPUT;
                    break;
                }
                error = handle_attribute_value(attr_key, attr_value,
                        attr_value_index, &mnemonic);
                attr_value_index = 0;
                state = FCML_MP_PS_ATTRIBUTE_KEY;
                break;
            default:
                if (state != FCML_MP_PS_ATTRIBUTE_KEY
                        && state != FCML_MP_PS_ATTRIBUTE_VALUE) {
                    error = FCML_CEH_GEC_INVALID_INPUT;
                    break;
                }
                if (state == FCML_MP_PS_ATTRIBUTE_KEY) {
                    if (fcml_fn_env_is_alpha(c)) {
                        attr_key = c;
                        state = FCML_MP_PS_ATTRIBUTE_VALUE;
                    } else {
                        error = FCML_CEH_GEC_INVALID_INPUT;
                    }
                } else if (state == FCML_MP_PS_ATTRIBUTE_VALUE) {
                    if ((fcml_fn_env_is_alpha(c) || fcml_fn_env_is_digit(c)
                            || c == '*') && attr_value_index < 5) {
                        attr_value[attr_value_index++] = c;
                        attr_value[attr_value_index] = '\0';
                    } else {
                        error = FCML_CEH_GEC_INVALID_INPUT;
                    }
                }
            }
        }
    }

    if (state != FCML_MP_PS_MNEMONIC && state != FCML_MP_PS_BETWEEN_MNEMONICS) {
        error = FCML_CEH_GEC_INVALID_INPUT;
    }

    if (!error && mnemonic_index) {
        error = dup_mnemonic(&mnemonic, mnemonics->mnemonics, mnemonic_buff,
                mnemonic_index);
    }

    if (error) {
        fcml_fn_mp_free_mnemonics(mnemonics);
    } else {
        if (mnemonics->mnemonics->size) {
            *mnemonics_set = mnemonics;
        } else {
            /* There is no mnemonic in the list.*/
            fcml_fn_mp_free_mnemonics(mnemonics);
            error = FCML_CEH_GEC_INVALID_INPUT;
        }
    }

    return error;
}

fcml_st_mp_mnemonic* fcml_fn_mp_choose_mnemonic(
        fcml_st_mp_mnemonic_set *mnemonics, fcml_st_mp_config *config) {

    fcml_st_mp_mnemonic *chosen_mnemonic = NULL;

    if (mnemonics->mnemonics) {

        fcml_st_coll_list_element *next = mnemonics->mnemonics->head;

        while (next) {

            fcml_st_mp_mnemonic *mnemonic = (fcml_st_mp_mnemonic*) next->item;

            /* Set default mnemonic only if there is no mnemonic yet.
             * Default mnemonics can not have any attributes defined,
             * so we do not need to check anything.
             */
            if (!chosen_mnemonic && !mnemonic->is_shortcut
                    && mnemonic->is_default) {
                chosen_mnemonic = mnemonic;
            }

            /* Size attributes.*/
            if (is_attribute_size_supported(mnemonic->supported_asa,
                    config->effective_asa)
                    && is_attribute_size_supported(
                            mnemonic->supported_osa, config->effective_osa)) {

                /* Memory data size.*/
                if (!mnemonic->memory_data.is_not_null
                        || (mnemonic->memory_data.value
                                == (config->memory_data_size / 8))) {

                    /* Suffix.*/
                    if ((mnemonic->suffix.is_not_null
                            == config->suffix.is_not_null)
                            && (!config->suffix.is_not_null
                                    || (config->suffix.value
                                            == mnemonic->suffix.value))) {

                        /* L flag.*/
                        if ((!config->l.is_not_null && !mnemonic->l.is_not_null)
                                || (config->l.value == mnemonic->l.value)) {

                            /* Shortcuts. Pseudo opcode mnemonic is also
                             * treated as a shortcut by disassembler.
                             */
                            if ((config->use_shortcut
                                    && ((mnemonic->pseudo_op.is_not_null
                                            && mnemonic->pseudo_op.value
                                                    == config->pseudo_opcode.value)
                                            || mnemonic->is_shortcut))
                                    || (!config->use_shortcut
                                            && !mnemonic->pseudo_op.is_not_null
                                            && (!mnemonic->is_shortcut
                                                    || mnemonic->is_classic))) {

                                /* Addressing mode: See "mm","mr"
                                 * mnemonic attribute.
                                 */
                                fcml_bool is_mode_ok =
                                        ((!mnemonic->is_mode_mem_only
                                                && !mnemonic->is_mode_reg_only)
                                                || (mnemonic->is_mode_mem_only
                                                        && config->is_memory)
                                                || (mnemonic->is_mode_reg_only
                                                        && !config->is_memory));
                                if (is_mode_ok) {

                                    /* Default mnemonic can not be overridden
                                     * by another default.
                                     */
                                    if (!chosen_mnemonic
                                            || !mnemonic->is_default) {
                                        chosen_mnemonic = mnemonic;
                                        break;
                                    }

                                }
                            }
                        }
                    }
                }
            }

            next = next->next;
        }
    }
    return chosen_mnemonic;

}

void fcml_fn_mp_free_mnemonics(fcml_st_mp_mnemonic_set *mnemonics) {
    if (mnemonics) {
        if (mnemonics->mnemonics) {
            fcml_fn_coll_list_free(mnemonics->mnemonics,
                    &coll_list_action_free_mnemonic, NULL);
        }
        fcml_fn_env_memory_free(mnemonics);
    }
}

fcml_usize fcml_fn_mp_l_to_vector_length(fcml_uint8_t l) {
    fcml_usize vector_length = FCML_DS_UNDEF;
    switch (l) {
    case 0x00:
        vector_length = FCML_DS_128;
        break;
    case 0x01:
        vector_length = FCML_DS_256;
        break;
    case 0x02:
        vector_length = FCML_DS_512;
        break;
    }
    return vector_length;
}
