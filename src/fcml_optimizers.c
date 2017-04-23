/*
 * FCML - Free Code Manipulation Library.
 * Copyright (C) 2010-2017 Slawomir Wojtasiak
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

#include "fcml_optimizers.h"

#include <fcml_types.h>
#include <fcml_errors.h>
#include <fcml_common.h>

#include "fcml_trace.h"

typedef struct fcml_ist_asm_opt_optimization_path_element {
    fcml_flags flags;
	fcml_usize attribute_size;
} fcml_ist_asm_opt_optimization_path_element;

fcml_ist_asm_opt_optimization_path_element
fcml_iarr_asm_opt_16_32_bit_optimization_path_16[] = {
	{ FCML_EN_ASF_16, FCML_DS_16 },
	{ FCML_EN_ASF_32, FCML_DS_32 }
};

fcml_ist_asm_opt_optimization_path_element
fcml_iarr_asm_opt_16_32_bit_optimization_path_32[] = {
	{ FCML_EN_ASF_32, FCML_DS_32 },
	{ FCML_EN_ASF_16, FCML_DS_16 }
};

fcml_ist_asm_opt_optimization_path_element
fcml_iarr_asm_opt_64_bit_optimization_path_for_asa_64[] = {
	{ FCML_EN_ASF_64, FCML_DS_64 },
	{ FCML_EN_ASF_32, FCML_DS_32 }
};

fcml_ist_asm_opt_optimization_path_element
fcml_iarr_asm_opt_64_bit_optimization_path_for_asa_32[] = {
	{ FCML_EN_ASF_32, FCML_DS_32 },
	{ FCML_EN_ASF_64, FCML_DS_64 }
};

fcml_ist_asm_opt_optimization_path_element
fcml_iarr_asm_opt_64_bit_optimization_path_for_osa_16[] = {
	{ FCML_EN_ASF_16, FCML_DS_16 },
	{ FCML_EN_ASF_64, FCML_DS_64 },
	{ FCML_EN_ASF_32, FCML_DS_32 }
};

fcml_ist_asm_opt_optimization_path_element
fcml_iarr_asm_opt_64_bit_optimization_path_for_osa_32[] = {
	{ FCML_EN_ASF_32, FCML_DS_32 },
	{ FCML_EN_ASF_64, FCML_DS_64 },
	{ FCML_EN_ASF_16, FCML_DS_16 }
};

fcml_ist_asm_opt_optimization_path_element
fcml_iarr_asm_opt_64_bit_optimization_path_for_osa_64[] = {
	{ FCML_EN_ASF_64, FCML_DS_64 },
	{ FCML_EN_ASF_32, FCML_DS_32 },
	{ FCML_EN_ASF_16, FCML_DS_16 }
};

fcml_int fcml_ifn_asm_opt_go_through_the_optimization_path(fcml_flags flags,
        fcml_int path_length, fcml_ist_asm_opt_optimization_path_element *path,
        fcml_usize *attribute_dest) {
    int i, count = 0;
    for (i = 0; i < path_length; i++) {
        fcml_ist_asm_opt_optimization_path_element *element = &(path[i]);
        if ((flags & element->flags) || (flags == FCML_EN_ASF_ANY)) {
            attribute_dest[count++] = element->attribute_size;
        }
    }
    return count;
}

fcml_int fcml_ifn_asm_opt_try_setting_attribute_size(fcml_flags flags,
        fcml_uint16_t opt_flags, fcml_usize attribute_size,
        fcml_usize *attribute_dest) {
    if ((flags & opt_flags) || (flags == FCML_EN_ASF_ANY)) {
        *attribute_dest = attribute_size;
        return 1;
    }
    return 0;
}

fcml_ceh_error LIB_CALL fcml_fn_asm_default_optimizer(
        fcml_st_asm_optimizer_context *context,
        fcml_st_asm_optimizer_processing_details *ds_flags,
        fcml_fnp_asm_optimizer_callback callback, fcml_ptr callback_args) {

    fcml_ceh_error error = FCML_CEH_GEC_INVALID_ADDRESS_SIZE;

    fcml_usize easa[2];
    fcml_usize eosa[3];

    fcml_int easa_count = 0;
    fcml_int eosa_count = 0;

    fcml_ist_asm_opt_optimization_path_element *path;

    fcml_uint16_t opt_flags = context->optimizer_flags;

    /* Just in case. */
    if (ds_flags == NULL) {
        FCML_TRACE_MSG("Optimizer details flags haven't been set.");
        return FCML_CEH_GEC_INTERNAL_ERROR;
    }

    /* ASA */

    if (ds_flags->easa) {
        /* Effective address size has been already chosen and cannot
         * be changed.
         */
        easa[easa_count++] = ds_flags->easa;
    } else {
        /* Maybe user has already forced any address size attribute to
         * be chosen?
         */
        fcml_usize attr_size = 0;
        fcml_flags attr_size_flag = 0;
        switch (opt_flags & 0x000F) {
        case FCML_OPTF_ASA_16:
            attr_size = FCML_DS_16;
            attr_size_flag = FCML_EN_ASF_16;
            break;
        case FCML_OPTF_ASA_32:
            attr_size = FCML_DS_32;
            attr_size_flag = FCML_EN_ASF_32;
            break;
        case FCML_OPTF_ASA_64:
            attr_size = FCML_DS_64;
            attr_size_flag = FCML_EN_ASF_64;
            break;
        }
        if (attr_size) {
            easa_count = fcml_ifn_asm_opt_try_setting_attribute_size(
                    ds_flags->allowed_easa.flags, attr_size_flag, attr_size,
                    &(easa[easa_count]));
        }
    }

    /* OSA */

    if (ds_flags->eosa) {
        /* Effective address size has been already chosen and cannot
         * be changed.
         */
        eosa[eosa_count++] = ds_flags->eosa;
    } else {
        /* Maybe user has already forced any address size attribute to
         * be chosen?
         */
        fcml_usize attr_size = 0;
        fcml_flags attr_size_flag = 0;
        switch (opt_flags & 0x00F0) {
        case FCML_OPTF_OSA_16:
            attr_size = FCML_DS_16;
            attr_size_flag = FCML_EN_ASF_16;
            break;
        case FCML_OPTF_OSA_32:
            attr_size = FCML_DS_32;
            attr_size_flag = FCML_EN_ASF_32;
            break;
        case FCML_OPTF_OSA_64:
            attr_size = FCML_DS_64;
            attr_size_flag = FCML_EN_ASF_64;
            break;
        }
        if (attr_size) {
            eosa_count = fcml_ifn_asm_opt_try_setting_attribute_size(
                    ds_flags->allowed_eosa.flags, attr_size_flag, attr_size,
                    &(eosa[eosa_count]));
        }
    }

    /* Choosing the best optimization path for ASA.*/

    if (!easa_count) {
        switch (context->op_mode) {
        case FCML_OM_16_BIT:
        case FCML_OM_32_BIT:
            path = (context->asa == FCML_DS_16) ?
                    fcml_iarr_asm_opt_16_32_bit_optimization_path_16 :
                    fcml_iarr_asm_opt_16_32_bit_optimization_path_32;
            easa_count = fcml_ifn_asm_opt_go_through_the_optimization_path(
                    ds_flags->allowed_easa.flags, 2, path, easa);
            break;
        case FCML_OM_64_BIT:
            path = (context->asa == FCML_DS_32) ?
                    fcml_iarr_asm_opt_64_bit_optimization_path_for_asa_32 :
                    fcml_iarr_asm_opt_64_bit_optimization_path_for_asa_64;
            easa_count = fcml_ifn_asm_opt_go_through_the_optimization_path(
                    ds_flags->allowed_easa.flags, 2, path, easa);
            break;
        }
    }

    /* Choosing the best optimization path for OSA.*/

    if (!eosa_count) {
        switch (context->op_mode) {
        case FCML_OM_16_BIT:
        case FCML_OM_32_BIT:
            path = (context->osa == FCML_DS_16) ?
                    fcml_iarr_asm_opt_16_32_bit_optimization_path_16 :
                    fcml_iarr_asm_opt_16_32_bit_optimization_path_32;
            eosa_count = fcml_ifn_asm_opt_go_through_the_optimization_path(
                    ds_flags->allowed_eosa.flags, 2, path, eosa);
            break;
        case FCML_OM_64_BIT:
            switch (context->osa) {
            case FCML_DS_16:
                path =
                      &fcml_iarr_asm_opt_64_bit_optimization_path_for_osa_16[0];
                break;
            case FCML_DS_32:
                path =
                      &fcml_iarr_asm_opt_64_bit_optimization_path_for_osa_32[0];
                break;
            case FCML_DS_64:
                path =
                      &fcml_iarr_asm_opt_64_bit_optimization_path_for_osa_64[0];
                break;
            }
            eosa_count = fcml_ifn_asm_opt_go_through_the_optimization_path(
                    ds_flags->allowed_eosa.flags, 3, path, eosa);
            break;
        }
    }

    ds_flags->break_optimization = FCML_FALSE;

    int i, j;
    for (i = 0; i < easa_count &&
            ((opt_flags == FCML_OPTF_ALL_FORMS) || error) &&
            !ds_flags->break_optimization; i++) {
        ds_flags->easa = easa[i];
        for (j = 0; j < eosa_count &&
                ((opt_flags == FCML_OPTF_ALL_FORMS) || error) &&
                !ds_flags->break_optimization; j++) {
            ds_flags->eosa = eosa[j];
            error = callback(callback_args);
        }
    }

    return error;
}
