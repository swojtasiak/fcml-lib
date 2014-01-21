/*
 * fcml_mnemonic_parser.h
 *
 *  Created on: 5 wrz 2013
 *      Author: tAs
 */

#ifndef FCML_MNEMONIC_PARSER_H_
#define FCML_MNEMONIC_PARSER_H_

#include "fcml_env.h"
#include "fcml_ceh.h"
#include "fcml_coll.h"

typedef struct fcml_st_mp_mnemonic {
    fcml_string mnemonic;
    fcml_bool is_shortcut;
    fcml_bool is_classic;
    fcml_bool is_mode_mem_only;
    fcml_bool is_mode_reg_only;
    fcml_data_size is_byte_ds;
    fcml_data_size is_full_ds;
    fcml_data_size supported_osa;
    fcml_data_size supported_asa;
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

fcml_ceh_error fcml_fn_mp_parse_mnemonics( fcml_string mnemonics_pattern, fcml_st_mp_mnemonic_set **mnemonics );
void fcml_fn_mp_free_mnemonics( fcml_st_mp_mnemonic_set *mnemonics );
fcml_st_mp_mnemonic *fcml_fn_mp_choose_mnemonic( fcml_st_mp_mnemonic_set *mnemonics, fcml_bool use_shortcut, fcml_nuint8_t pseudo_opcode, fcml_nuint8_t suffix, fcml_data_size osa, fcml_data_size asa, fcml_bool is_memory, fcml_data_size memory_data_size, fcml_nuint8_t l );

#endif /* FCML_MNEMONIC_PARSER_H_ */
