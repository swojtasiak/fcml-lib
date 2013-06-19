/*
 * fcml_optimizers.h
 *
 *  Created on: 16-06-2013
 *      Author: tAs
 */

#ifndef FCML_OPTIMIZERS_H_
#define FCML_OPTIMIZERS_H_

#include "fcml_asm_encoding.h"
#include "fcml_ceh.h"

extern fcml_fnp_asm_optimizer fcml_ar_optimizers[];

fcml_ceh_error fcml_fnp_asm_default_optimizer( fcml_st_asm_encoding_context *context, fcml_st_asm_instruction_addr_mode *addr_mode, fcml_fnp_asm_optimizer_callback callback, fcml_ptr args );

#endif /* FCML_OPTIMIZERS_H_ */
