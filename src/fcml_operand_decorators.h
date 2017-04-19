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

/**
 * Decodes operand decorators for one operand.
 */
fcml_ceh_error fcml_fn_op_decor_decode(
        fcml_bool evex_b,
        fcml_bool evex_z,
        fcml_uint8_t evex_aaa,
        fcml_usize vector_length,
        fcml_operand_decorators decorators_def,
        fcml_st_operand_decorators *decorators);

#endif /* SRC_FCML_OPERAND_DECODERS_H_ */
