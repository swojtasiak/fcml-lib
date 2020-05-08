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

#ifndef FCML_MNEMONIC_PARSER_H_
#define FCML_MNEMONIC_PARSER_H_

#include "fcml_env_int.h"
#include "fcml_ceh.h"
#include "fcml_coll.h"

typedef struct fcml_st_mp_mnemonic {
    fcml_string mnemonic;
    fcml_bool is_shortcut;
    fcml_bool is_classic;
    fcml_bool is_mode_mem_only;
    fcml_bool is_mode_reg_only;
    fcml_usize is_byte_ds;
    fcml_usize is_full_ds;
    fcml_usize supported_osa;
    fcml_usize supported_asa;
    fcml_nuint8_t suffix;
    fcml_nuint8_t pseudo_op;
    fcml_nuint8_t memory_data;
    fcml_bool is_default;
    fcml_nuint8_t l;
    fcml_uint32_t flags;
} fcml_st_mp_mnemonic;

typedef struct fcml_st_mp_mnemonic_set {
    fcml_st_coll_list *mnemonics;
} fcml_st_mp_mnemonic_set;

typedef struct fcml_st_mp_config {
    fcml_bool use_shortcut;
    fcml_nuint8_t pseudo_opcode;
    fcml_nuint8_t suffix;
    fcml_usize effective_osa;
    fcml_usize effective_asa;
    fcml_bool is_memory;
    fcml_usize memory_data_size;
    fcml_nuint8_t l;
} fcml_st_mp_config;

fcml_ceh_error fcml_fn_mp_parse_mnemonics(fcml_string mnemonics_pattern,
        fcml_st_mp_mnemonic_set **mnemonics);

void fcml_fn_mp_free_mnemonics(fcml_st_mp_mnemonic_set *mnemonics);

fcml_st_mp_mnemonic *fcml_fn_mp_choose_mnemonic(
        fcml_st_mp_mnemonic_set *mnemonics, fcml_st_mp_config *config);

fcml_usize fcml_fn_mp_l_to_vector_length(fcml_uint8_t l);

#endif /* FCML_MNEMONIC_PARSER_H_ */
