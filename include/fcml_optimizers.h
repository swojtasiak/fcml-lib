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

/** @file fcml_optimizers.h
 * API for assembler optimizers. For more details about optimizers see
 * FCML manual.
 *
 * @copyright Copyright (C) 2010-2020 Slawomir Wojtasiak. All rights reserved.
 * This project is released under the GNU Lesser General Public License.
 */
#ifndef FCML_OPTIMIZERS_H_
#define FCML_OPTIMIZERS_H_

#include "fcml_lib_export.h"

#include "fcml_types.h"
#include "fcml_errors.h"
#include "fcml_common.h"

#ifdef __cplusplus
extern "C" {
#endif

/** Optimizer context used as a connector with the environment. */
typedef struct fcml_st_asm_optimizer_context {
    /** Instruction's entry point provided by the caller. The
     * same which is available in the assembler context. */
    const fcml_st_entry_point *entry_point;
    /** Optimizer flags passed through the assembler context.
     * @see fcml_st_assembler_conf
     */
    fcml_uint16_t optimizer_flags;
} fcml_st_asm_optimizer_context;

/** Processing details for optimizers. */
typedef struct fcml_st_asm_optimizer_processing_details {
    /** Allowed values of the operand size attribute calculated by the
     * assembler engine.
     * It is the optimizer who decides which one should be finally used.
     */
    fcml_st_nullable_size_flags allowed_eosa;
    /** Allowed values of the address size attribute calculated by the
     * assembler engine.
     * It is optimizer who decides which one should be finally used.
     */
    fcml_st_nullable_size_flags allowed_easa;
    /** Effective address size attribute chosen for currently processed
     * instruction form.
     * If it is set it can not be changed anymore. It has
     * higher priority than flags above. Take into account that it is
     * effective attribute size attribute so it can be forced using instruction
     * prefixes to override the default attribute size.
     */
    fcml_usize easa;
    /** Effective operand size attribute chosen for currently processed
     * instruction form.
     * If it is set it can not be changed anymore. It has higher priority than
     * flags above. Take into account that it is effective operand size
     * attribute so it can be forced using instruction prefixes to override
     * the default attribute size.
     */
    fcml_usize eosa;
    /** Vector length of AVX instructions. Set to FCML_DS_UNDEF if not used. */
    fcml_usize vector_length;
    /** Set to true in order to break optimization process immediately. */
    fcml_bool break_optimization;
} fcml_st_asm_optimizer_processing_details;

/**
 * Callback used to invoke encoding process for given processing details
 * configuration.
 * @param args Arguments from optimizer.
 * @return Error code or FCML_CEH_GEC_NO_ERROR.
 */
typedef fcml_ceh_error (*fcml_fnp_asm_optimizer_callback)(fcml_ptr args);

/**
 * Function pointer declaration for optimizers.
 * @param context Optimizer context.
 * @param ds_flags Current instruction processing details.
 * @param callback Callback used to continue processing for configuration
 * prepared by optimizer.
 * @param args Arguments that should be passed to the callback.
 * @return Error code or FCML_CEH_GEC_NO_ERROR.
 */
typedef fcml_ceh_error (LIB_CALL *fcml_fnp_asm_optimizer)(
        fcml_st_asm_optimizer_context *context,
        fcml_st_asm_optimizer_processing_details *ds_flags,
        fcml_fnp_asm_optimizer_callback callback, fcml_ptr args);

/* Optimizers flags that can be used to configure optimization process. */
#define FCML_OPTF_ASA_16        0x01
#define FCML_OPTF_ASA_32        0x02
#define FCML_OPTF_ASA_64        0x03
#define FCML_OPTF_OSA_16        0x10
#define FCML_OPTF_OSA_32        0x20
#define FCML_OPTF_OSA_64        0x30
/* Do not choose the optimal form, but return all possibilities. */
#define FCML_OPTF_ALL_FORMS     0xFF

/**
 * Default optimizer implementation.
 * This implementation chooses the best combination of attributes for
 * current processor operating mode.
 * @param context Optimizer context.
 * @param ds_flags Current instruction processing details.
 * @param callback Callback used to continue processing for configuration
 * prepared by optimizer.
 * @param callback_args Arguments that should be passed to the callback.
 * @return Error code or FCML_CEH_GEC_NO_ERROR.
 */
LIB_EXPORT fcml_ceh_error LIB_CALL fcml_fn_asm_default_optimizer(
        fcml_st_asm_optimizer_context *context,
        fcml_st_asm_optimizer_processing_details *ds_flags,
        fcml_fnp_asm_optimizer_callback callback, fcml_ptr callback_args);

#ifdef __cplusplus
}
#endif

#endif /* FCML_OPTIMIZERS_H_ */
