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

#include "fcml_optimizers.h"

#include <fcml_types.h>
#include <fcml_errors.h>
#include <fcml_common.h>

#include "fcml_trace.h"

typedef struct opt_path_element {
    fcml_flags flags;
	fcml_usize attribute_size;
} opt_path_element;

static opt_path_element opt_16_32_bit_path_16[] = {
	{ FCML_EN_ASF_16, FCML_DS_16 },
	{ FCML_EN_ASF_32, FCML_DS_32 }
};

static opt_path_element opt_16_32_bit_path_32[] = {
	{ FCML_EN_ASF_32, FCML_DS_32 },
	{ FCML_EN_ASF_16, FCML_DS_16 }
};

static opt_path_element opt_64_bit_path_for_asa_64[] = {
	{ FCML_EN_ASF_64, FCML_DS_64 },
	{ FCML_EN_ASF_32, FCML_DS_32 }
};

static opt_path_element opt_64_bit_path_for_asa_32[] = {
	{ FCML_EN_ASF_32, FCML_DS_32 },
	{ FCML_EN_ASF_64, FCML_DS_64 }
};

static opt_path_element opt_64_bit_path_for_osa_16[] = {
	{ FCML_EN_ASF_16, FCML_DS_16 },
	{ FCML_EN_ASF_64, FCML_DS_64 },
	{ FCML_EN_ASF_32, FCML_DS_32 }
};

static opt_path_element opt_64_bit_path_for_osa_32[] = {
	{ FCML_EN_ASF_32, FCML_DS_32 },
	{ FCML_EN_ASF_64, FCML_DS_64 },
	{ FCML_EN_ASF_16, FCML_DS_16 }
};

static opt_path_element opt_64_bit_path_for_osa_64[] = {
	{ FCML_EN_ASF_64, FCML_DS_64 },
	{ FCML_EN_ASF_32, FCML_DS_32 },
	{ FCML_EN_ASF_16, FCML_DS_16 }
};

static fcml_int go_through_opt_path(fcml_flags flags, fcml_int path_length,
        opt_path_element *path, fcml_usize *attribute_dest) {
    int i, count = 0;
    for (i = 0; i < path_length; i++) {
        opt_path_element *element = &(path[i]);
        if ((flags & element->flags) || (flags == FCML_EN_ASF_ANY)) {
            attribute_dest[count++] = element->attribute_size;
        }
    }
    return count;
}

static fcml_int try_set_attribute_size(fcml_flags flags,
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

    const fcml_st_entry_point *entry_point = context->entry_point;

    fcml_usize ep_asa = entry_point->address_size_attribute;
    fcml_usize ep_osa = entry_point->operand_size_attribute;

    /* TODO: Maybe we should also try different vector lengths if there is
       such a possibility. */
    fcml_usize easa[2];
    fcml_usize eosa[3];

    fcml_int easa_count = 0;
    fcml_int eosa_count = 0;

    opt_path_element *path;

    fcml_uint16_t opt_flags = context->optimizer_flags;

    /* Just in case. */
    if (ds_flags == NULL) {
        FCML_TRACE_MSG("Optimizer details flags haven't been set.");
        return FCML_CEH_GEC_INTERNAL_ERROR;
    }

    FCML_TRACE("Allowed ASA set: %d, flags: 0x%02X.",
                    ds_flags->allowed_easa.is_set,
                    ds_flags->allowed_easa.flags);

    FCML_TRACE("Allowed OSA set: %d, flags: 0x%02X.",
                    ds_flags->allowed_eosa.is_set,
                    ds_flags->allowed_eosa.flags);

    /* ASA */

    if (ds_flags->easa) {
        /* Effective address size has been already chosen and cannot
         * be changed.
         */
        FCML_TRACE("ASA forced to %d bits by addr mode acceptors.",
                ds_flags->easa);
        easa[easa_count++] = ds_flags->easa;
    } else {
        /* Maybe user has already forced any address size attribute to
         * be chosen?
         */
        fcml_usize attr_size = 0;
        fcml_flags attr_size_flag = 0;
        switch (opt_flags & 0x000F) {
        case FCML_OPTF_ASA_16:
            FCML_TRACE("ASA forced to 16 bits by optimizer_flags (config).");
            attr_size = FCML_DS_16;
            attr_size_flag = FCML_EN_ASF_16;
            break;
        case FCML_OPTF_ASA_32:
            FCML_TRACE("ASA forced to 32 bits by optimizer_flags (config).");
            attr_size = FCML_DS_32;
            attr_size_flag = FCML_EN_ASF_32;
            break;
        case FCML_OPTF_ASA_64:
            FCML_TRACE("ASA forced to 64 bits by optimizer_flags (config).");
            attr_size = FCML_DS_64;
            attr_size_flag = FCML_EN_ASF_64;
            break;
        }
        if (attr_size) {
            easa_count = try_set_attribute_size(
                    ds_flags->allowed_easa.flags, attr_size_flag, attr_size,
                    &(easa[easa_count]));
        }
    }

    /* OSA */

    if (ds_flags->eosa) {
        /* Effective address size has been already chosen and cannot
         * be changed.
         */
        FCML_TRACE("OSA forced to %d bits by addr mode acceptors.",
                ds_flags->eosa);
        eosa[eosa_count++] = ds_flags->eosa;
    } else {
        /* Maybe user has already forced any address size attribute to
         * be chosen?
         */
        fcml_usize attr_size = 0;
        fcml_flags attr_size_flag = 0;
        switch (opt_flags & 0x00F0) {
        case FCML_OPTF_OSA_16:
            FCML_TRACE("OSA forced to 16 bits by optimizer_flags (config).");
            attr_size = FCML_DS_16;
            attr_size_flag = FCML_EN_ASF_16;
            break;
        case FCML_OPTF_OSA_32:
            FCML_TRACE("OSA forced to 32 bits by optimizer_flags (config).");
            attr_size = FCML_DS_32;
            attr_size_flag = FCML_EN_ASF_32;
            break;
        case FCML_OPTF_OSA_64:
            FCML_TRACE("OSA forced to 64 bits by optimizer_flags (config).");
            attr_size = FCML_DS_64;
            attr_size_flag = FCML_EN_ASF_64;
            break;
        }
        if (attr_size) {
            eosa_count = try_set_attribute_size(
                    ds_flags->allowed_eosa.flags, attr_size_flag, attr_size,
                    &(eosa[eosa_count]));
        }
    }

    /* Choosing the best optimization path for ASA.*/

    if (!easa_count) {
        switch (entry_point->op_mode) {
        case FCML_OM_16_BIT:
        case FCML_OM_32_BIT:
            path = (ep_asa == FCML_DS_16) ? opt_16_32_bit_path_16 :
                    opt_16_32_bit_path_32;
            easa_count = go_through_opt_path(
                    ds_flags->allowed_easa.flags, 2, path, easa);
            break;
        case FCML_OM_64_BIT:
            path = (ep_asa == FCML_DS_32) ? opt_64_bit_path_for_asa_32 :
                    opt_64_bit_path_for_asa_64;
            easa_count = go_through_opt_path(
                    ds_flags->allowed_easa.flags, 2, path, easa);
            break;
        }
    }

    /* Choosing the best optimization path for OSA.*/

    if (!eosa_count) {
        switch (entry_point->op_mode) {
        case FCML_OM_16_BIT:
        case FCML_OM_32_BIT:
            path = (ep_osa == FCML_DS_16) ? opt_16_32_bit_path_16 :
                    opt_16_32_bit_path_32;
            eosa_count = go_through_opt_path(
                    ds_flags->allowed_eosa.flags, 2, path, eosa);
            break;
        case FCML_OM_64_BIT:
            switch (ep_osa) {
            case FCML_DS_16:
                path = &opt_64_bit_path_for_osa_16[0];
                break;
            case FCML_DS_32:
                path = &opt_64_bit_path_for_osa_32[0];
                break;
            case FCML_DS_64:
                path = &opt_64_bit_path_for_osa_64[0];
                break;
            }
            eosa_count = go_through_opt_path(
                    ds_flags->allowed_eosa.flags, 3, path, eosa);
            break;
        }
    }

    ds_flags->break_optimization = FCML_FALSE;

    /* If true all addressing modes of given instruction will
     * be encoded not only the optimal one.
     */
    fcml_bool all_forms = opt_flags == FCML_OPTF_ALL_FORMS;

    int i, j;
    for (i = 0; i < easa_count && (all_forms || error) &&
            !ds_flags->break_optimization; i++) {
        ds_flags->easa = easa[i];
        for (j = 0; j < eosa_count && (all_forms || error) &&
                !ds_flags->break_optimization; j++) {
            ds_flags->eosa = eosa[j];
            FCML_TRACE("Optimizing for (EASA: %d, EOSA: %d).",
                    ds_flags->easa, ds_flags->eosa);
            error = callback(callback_args);
        }
    }

    return error;
}
