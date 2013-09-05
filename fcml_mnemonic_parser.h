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
#include "fcml_common_int.h"

typedef struct fcml_mp_mnemonic {
    fcml_string mnemonic;
    fcml_bool shortcut;
    fcml_en_attribute_size_flag supported_osa;
    fcml_en_attribute_size_flag supported_asa;
} fcml_mp_mnemonic;

typedef struct fcml_mp_mnemonic_set {
    fcml_st_coll_list *mnemonics;
} fcml_mp_mnemonic_set;

fcml_ceh_error fcml_fn_mp_parse_mnemonics( fcml_string mnemonics_pattern, fcml_mp_mnemonic_set **mnemonics );

void fcml_fn_mp_free_mnemonics( fcml_mp_mnemonic_set *mnemonics );

#endif /* FCML_MNEMONIC_PARSER_H_ */
