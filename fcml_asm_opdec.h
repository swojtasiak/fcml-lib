/*
 * fcml_asm_opdec.h
 *
 *  Created on: 14-04-2013
 *      Author: tAs
 */

#ifndef FCML_ASM_OPDEC_H_
#define FCML_ASM_OPDEC_H_

#include "fcml_asm_int.h"

// Operand encoder pointer.
typedef int (*fcml_fnp_asm_operand_encoder)(fcml_st_asm_encodeing_context *context, int operand_num, void *args);

#endif /* FCML_ASM_OPDEC_H_ */
