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

#ifndef FCML_COMMON_DIALECT_H_
#define FCML_COMMON_DIALECT_H_

#include <fcml_common.h>
#include <fcml_dialect.h>
#include <fcml_types.h>

#include "fcml_ceh.h"
#include "fcml_mnemonic_parser.h"

fcml_ceh_error fcml_fn_cmn_dialect_get_mnemonic(const fcml_st_dialect *dialect,
        fcml_st_mp_mnemonic_set *mnemonic_set, fcml_st_mp_mnemonic **mnemonics,
        const fcml_st_condition *condition, int *mnemonics_counter);

fcml_string fcml_fn_cmn_dialect_render_mnemonic(fcml_string mnemonic,
        fcml_st_condition *condition, fcml_uint8_t conditional_group,
        fcml_bool show_carry);

fcml_ceh_error fcml_fn_cmn_dialect_get_register(const fcml_st_register *reg,
        fcml_string *printable_reg, fcml_bool is_rex);

void fcml_fn_cmn_dialect_free(fcml_st_dialect *dialect);

#endif /* FCML_COMMON_DIALECT_H_ */
