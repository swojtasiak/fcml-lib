/*
 * fcml_assembler.h
 *
 *  Created on: 08-02-2013
 *      Author: tAs
 */

#ifndef FCML_ASSEMBLER_H_
#define FCML_ASSEMBLER_H_

#include "fcml_common.h"
#include "fcml_asm_errors.h"

fcml_ceh_error fcml_fn_asm_init();
fcml_ceh_error fcml_fn_assemble( fcml_st_instruction *instruction, fcml_st_ceh_error_container *errors );
void fcml_fn_asm_free();

#endif /* FCML_ASSEMBLER_H_ */
