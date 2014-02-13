/*
 * fcml_dialect.h
 *
 *  Created on: Nov 21, 2013
 *      Author: tas
 */

#ifndef FCML_DIALECT_H_
#define FCML_DIALECT_H_

#include "fcml_lib_export.h"

/* Assembler dialect.*/
typedef struct fcml_st_dialect fcml_st_dialect;

#ifdef __cplusplus
extern "C" {
#endif

LIB_EXPORT void LIB_CALL fcml_fn_dialect_free(fcml_st_dialect *dialect);

#ifdef __cplusplus
}
#endif

#endif /* FCML_DIALECT_H_ */
