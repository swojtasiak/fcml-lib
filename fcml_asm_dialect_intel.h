/*
 * fcml_asm_dialect_intel.h
 *
 *  Created on: 1 wrz 2013
 *      Author: tAs
 */

#ifndef FCML_ASM_DIALECT_INTEL_H_
#define FCML_ASM_DIALECT_INTEL_H_

#include "fcml_ceh.h"
#include "fcml_asm_dialect.h"

fcml_ceh_error fcml_fn_init_intel_dialect(void);
void fcml_fn_intel_dialect_free(void);
fcml_st_dialect_context fcml_fn_get_intel_dialect_context();

#endif /* FCML_ASM_DIALECT_INTEL_H_ */
