/*
 * fcml_optimizers.h
 *
 *  Created on: 16-06-2013
 *      Author: tAs
 */

#ifndef FCML_OPTIMIZERS_H_
#define FCML_OPTIMIZERS_H_

#include "fcml_ceh.h"
#include "fcml_types.h"
#include "fcml_common.h"

typedef struct fcml_st_asm_optimizer_context {
    // Optimizer flags specified defined by assembler context.
    fcml_uint16_t optimizer_flags;
    // Processor addressing mode 16/32/64-bit.
    fcml_en_addr_form addr_form;
    // Default address/operand size attribute (See 'D' flag of segment descriptor.)
    fcml_data_size asa;
    fcml_data_size osa;
} fcml_st_asm_optimizer_context;

// Processing details for optimizers.
typedef struct fcml_st_asm_optimizer_processing_details {
    // Flags describing all EOSa sizes available for given addressing mode.
    fcml_st_nullable_size_flags allowed_eosa;
    fcml_st_nullable_size_flags allowed_easa;
    // Effective address/operand size chosen for currently processed address mode. If set can not be changed anymore.
    // It has higher priority than flags above.
    fcml_data_size easa;
    fcml_data_size eosa;
    // L bit from VEX like prefixes set for encoded instruction.
    fcml_nuint8_t l;
    // Set to true in order to break optimization process.
    fcml_bool break_optimization;
} fcml_st_asm_optimizer_processing_details;

typedef fcml_ceh_error (*fcml_fnp_asm_optimizer_callback)( fcml_ptr args );

typedef fcml_ceh_error (*fcml_fnp_asm_optimizer)( fcml_st_asm_optimizer_context *context, fcml_st_asm_optimizer_processing_details *ds_flags, fcml_fnp_asm_optimizer_callback callback, fcml_ptr args );

// Encodes instruction using given ASA and OSA.

#define FCML_OPTF_ASA_16        0x01
#define FCML_OPTF_ASA_32        0x02
#define FCML_OPTF_ASA_64        0x03
#define FCML_OPTF_OSA_16        0x10
#define FCML_OPTF_OSA_32        0x20
#define FCML_OPTF_OSA_64        0x30
#define FCML_OPTF_ALL_FORMS     0xFF

fcml_ceh_error fcml_fn_asm_default_optimizer( fcml_st_asm_optimizer_context *context, fcml_st_asm_optimizer_processing_details *ds_flags, fcml_fnp_asm_optimizer_callback callback, fcml_ptr callback_args );

#endif /* FCML_OPTIMIZERS_H_ */
