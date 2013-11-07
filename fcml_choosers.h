/*
 * fcml_chooser.h
 *
 *  Created on: Nov 7, 2013
 *      Author: tas
 */

#ifndef FCML_CHOOSER_H_
#define FCML_CHOOSER_H_

#include "fcml_assembler.h"

fcml_st_asm_assembled_instruction *fcml_fn_asm_default_instruction_chooser( fcml_st_coll_list *instructions );
fcml_st_asm_assembled_instruction *fcml_fn_asm_no_instruction_chooser( fcml_st_coll_list *instructions );

#endif /* FCML_CHOOSER_H_ */
