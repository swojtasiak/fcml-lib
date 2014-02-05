/*
 * fcml_chooser.h
 *
 *  Created on: Nov 7, 2013
 *      Author: tas
 */

#ifndef FCML_CHOOSER_H_
#define FCML_CHOOSER_H_

#include "fcml_lib_export.h"

#include <fcml_types.h>
#include <fcml_common.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Gets next instructions basing on the current one. */
typedef fcml_ptr (*fcml_fnp_chooser_next)( fcml_ptr instruction );

/* Gets instruction code from current abstract instruction pointer. */
typedef void (*fcml_fnp_chooser_extract)( fcml_ptr instruction, fcml_st_instruction_code *instruction_code );

/* Instruction chooser context used to communicate with environemnt. */
typedef struct fcml_st_chooser_context {
    /* First instruction.*/
    fcml_ptr instruction;
    /* Gets next instruction  code from iterator.*/
    fcml_fnp_chooser_next next;
    /* Extracts instruction code from abstract intruction pointer.*/
    fcml_fnp_chooser_extract extract;
} fcml_st_chooser_context;

/* Chooser function declaration. */
typedef LIB_CALL fcml_ptr (*fcml_fnp_asm_instruction_chooser)( fcml_st_chooser_context *chooser_context );

/* Default instruction chooser which chooses the shortest instruction available. */
fcml_ptr LIB_CALL LIB_EXPORT fcml_fn_asm_default_instruction_chooser( fcml_st_chooser_context *chooser_context );

/* NULL chooser which do not chose anything. */
fcml_ptr LIB_CALL LIB_EXPORT fcml_fn_asm_no_instruction_chooser( fcml_st_chooser_context *chooser_context );

#ifdef __cplusplus
}
#endif

#endif /* FCML_CHOOSER_H_ */
