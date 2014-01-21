/*
 * fcml_common_dialect.h
 *
 *  Created on: Nov 16, 2013
 *      Author: tas
 */

#ifndef FCML_COMMON_DIALECT_H_
#define FCML_COMMON_DIALECT_H_

#include "fcml_ceh.h"
#include "fcml_common.h"
#include "fcml_dialect.h"
#include "fcml_types.h"

extern fcml_string fcml_ar_asm_dialect_reg_symbol_table[7][16];
extern fcml_string fcml_ar_asm_dialect_reg_gpr_symbol_table[4][16];
extern fcml_string fcml_ar_asm_dialect_reg_symbol_table_rex[7][16];
extern fcml_string fcml_ar_asm_dialect_reg_gpr_symbol_table_rex[4][16];
extern fcml_string fcml_ar_asm_dialect_reg_sidm_symbol_table[3][16];

fcml_ceh_error fcml_fn_cmn_dialect_get_register( const fcml_st_register *reg, fcml_string *printable_reg, fcml_bool is_rex);
void fcml_fn_cmn_dialect_free( fcml_st_dialect *dialect );

#endif /* FCML_COMMON_DIALECT_H_ */
