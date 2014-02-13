/*
 * fcml_asm_dialect_intel.h
 *
 *  Created on: 1 wrz 2013
 *      Author: tAs
 */

#ifndef FCML_ASM_DIALECT_INTEL_H_
#define FCML_ASM_DIALECT_INTEL_H_

#include "fcml_lib_export.h"

#include "fcml_errors.h"
#include "fcml_dialect.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Default combination of configuration flags.*/
#define FCML_INTEL_DIALECT_CF_DEFAULT           0

LIB_EXPORT fcml_ceh_error LIB_CALL fcml_fn_dialect_init_intel( fcml_uint32_t config_flags, fcml_st_dialect **dialect );

#ifdef __cplusplus
}
#endif

#endif /* FCML_ASM_DIALECT_INTEL_H_ */
