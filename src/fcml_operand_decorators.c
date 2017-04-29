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

void fcml_fn_prepare_decorators_existence(fcml_operand_desc *operands,
        fcml_st_decorators_existence *dec_existence) {
    int i;
    for(i = 0; i < FCML_OPERANDS_COUNT; i++) {
        fcml_operand_decorators decorators = FCML_DECORATORS(operands[i]);
        if (FCML_IS_DECOR_BCAST(decorators)) {
            dec_existence->bcast = FCML_TRUE;
        }
        if (FCML_IS_DECOR_OPMASK_REG(decorators)) {
            dec_existence->opmask_reg = FCML_TRUE;
        }
        if (FCML_IS_DECOR_Z(decorators)) {
            dec_existence->z = FCML_TRUE;
        }
        if (FCML_IS_DECOR_ER(decorators)) {
            dec_existence->er = FCML_TRUE;
        }
        if (FCML_IS_DECOR_SAE(decorators)) {
            dec_existence->sea = FCML_TRUE;
        }
    }
}

fcml_ceh_error fcml_fn_op_decor_decode(
        fcml_st_decorators_prefix_flags *prefix_flags, fcml_bool reg_to_reg,
        fcml_usize vector_length, fcml_usize element_size,
        fcml_operand_decorators decorators_def, fcml_st_operand *operand) {

    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

    fcml_st_operand_decorators *decorators = &(operand->decorators);

    /* Sets broadcast decorator, but only if EVEX.b flag is set. */
    if (FCML_IS_DECOR_BCAST(decorators_def) && prefix_flags->b &&
            operand->type == FCML_OT_ADDRESS) {
        decorators->bcast.is_not_null = FCML_TRUE;
        decorators->bcast.value = vector_length / element_size;
    }

    /* Operand mask register. */
    if (FCML_IS_DECOR_OPMASK_REG(decorators_def) && prefix_flags->aaa > 0) {
        decorators->operand_mask_reg.type = FCML_REG_OPMASK;
        decorators->operand_mask_reg.size = FCML_DS_64;
        decorators->operand_mask_reg.x64_exp = FCML_FALSE;
        decorators->operand_mask_reg.reg = prefix_flags->aaa;
    }

    /* Zeroying. */
    if (FCML_IS_DECOR_Z(decorators_def) && prefix_flags->z) {
        decorators->z = FCML_TRUE;
    }

    if(operand->type == FCML_OT_NONE && reg_to_reg && prefix_flags->b &&
            (vector_length == FCML_DS_128 || vector_length == FCML_DS_512)) {

        /* Static rounding. */
        if (FCML_IS_DECOR_ER(decorators_def) ) {
            decorators->er.is_not_null = FCML_TRUE;
            decorators->er.value = prefix_flags->ll;
            operand->type = FCML_OT_VIRTUAL;
        }

        /* Suppress All Exceptions. */
        if (FCML_IS_DECOR_SAE(decorators_def) && prefix_flags->ll == 0) {
            decorators->sae = FCML_TRUE;
            operand->type = FCML_OT_VIRTUAL;
        }

    }

    return error;
}
