/*
 * fcml_asm_encoding.h
 *
 *  Created on: 31-03-2013
 *      Author: tAs
 */

#ifndef FCML_ASM_ENCODING_H_
#define FCML_ASM_ENCODING_H_

#include "fcml_def.h"
#include "fcml_asm_int.h"
#include "fcml_ceh.h"
#include "fcml_coll.h"

typedef struct fcml_st_asm_instruction_addr_modes {
	// All addressing modes for given mnemonic are available in this list.
	fcml_st_coll_list *addr_modes;
	// Mnemonic.
	fcml_string mnemonic;
} fcml_st_asm_instruction_addr_modes;

typedef struct fcml_st_asm_instruction_addr_mode {
	fcml_st_def_addr_mode_desc *addr_mode_desc;
} fcml_st_asm_instruction_addr_mode;

void fcml_fn_asm_init_instruction_encodings( fcml_ceh_error *error );
void fcml_fn_asm_free_instruction_encodings();
fcml_st_asm_instruction_encoding *fcml_fn_asm_get_instruction_encodings( fcml_string mnemonic, fcml_ceh_error *error );

#endif /* FCML_ASM_ENCODING_H_ */
