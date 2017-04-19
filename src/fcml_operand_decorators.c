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

#include "fcml_operand_decorators.h"
#include "fcml_def.h"

fcml_ceh_error fcml_fn_op_decor_decode(fcml_bool evex_b, fcml_bool evex_z,
        fcml_uint8_t evex_aaa, fcml_uint8_t evex_ll, fcml_bool reg_to_reg,
        fcml_usize vector_length, fcml_operand_decorators decorators_def,
        fcml_st_operand *operand) {

    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

    fcml_st_operand_decorators *decorators = &(operand->decorators);

    /* Sets broadcast decorator, but only if EVEX.b flag is set. */
    if (FCML_IS_DECOR_BCAST(decorators_def) && evex_b &&
            operand->type == FCML_OT_ADDRESS) {
        fcml_uint8_t bcast_size = FCML_GET_DECOR_BCAST_ELEMENT_SIZE(
                decorators_def);
        decorators->bcast.is_not_null = FCML_TRUE;
        decorators->bcast.value = vector_length / bcast_size;
    }

    /* Operand mask register. */
    if (FCML_IS_DECOR_K1(decorators_def) && evex_aaa > 0) {
        decorators->operand_mask_reg.type = FCML_REG_OPMASK;
        decorators->operand_mask_reg.size = FCML_DS_64;
        decorators->operand_mask_reg.x64_exp = FCML_FALSE;
        decorators->operand_mask_reg.reg = evex_aaa;
    }

    /* Zeroying. */
    if (FCML_IS_DECOR_Z(decorators_def) && evex_z) {
        decorators->z = FCML_TRUE;
    }

    /* Static rounding. */
    if (FCML_IS_DECOR_ER(decorators_def) && evex_b && reg_to_reg &&
            operand->type == FCML_OT_VIRTUAL) {
        decorators->er.is_not_null = FCML_TRUE;
        decorators->er.value = evex_ll;
    }

    return error;
}
