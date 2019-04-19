/*
 * FCML - Free Code Manipulation Library.
 * Copyright (C) 2017 Slawomir Wojtasiak
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

#ifndef SRC_FCML_OPERAND_DECORATORS_H_
#define SRC_FCML_OPERAND_DECORATORS_H_

#include "fcml_common.h"
#include "fcml_def.h"

typedef struct fcml_st_decorators_existence {
    fcml_bool bcast;
    fcml_bool z;
    fcml_bool er;
    fcml_bool opmask_reg;
    fcml_bool sae;
} fcml_st_decorators_existence;

typedef struct fcml_st_decorators_prefix_flags {
    fcml_bool b;
    fcml_bool z;
    fcml_uint8_t aaa;
    fcml_uint8_t ll;
} fcml_st_decorators_prefix_flags;

void fcml_fn_prepare_decorators_existence(fcml_operand_desc *operands,
        fcml_st_decorators_existence *dec_existence);

/**
 * Decodes operand decorators for one operand.
 */
fcml_ceh_error fcml_fn_op_decor_decode(
        fcml_st_decorators_prefix_flags *prefix_flags,
        fcml_operand_decorators decorators_def, fcml_st_operand *operand);

#endif /* SRC_FCML_OPERAND_DECODERS_H_ */
