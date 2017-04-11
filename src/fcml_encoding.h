/*
 * fcml_asm_encoding.h
 *
 *  Created on: 31-03-2013
 *      Author: tAs
 */

#ifndef FCML_ASM_ENCODING_H_
#define FCML_ASM_ENCODING_H_

#include "fcml_assembler.h"
#include "fcml_ceh.h"
#include "fcml_coll.h"
#include "fcml_common.h"
#include "fcml_dialect_int.h"
#include "fcml_types.h"

typedef struct fcml_st_asm_encoder_result {
    fcml_st_ceh_error_container errors;
    fcml_st_assembled_instruction *instructions;
    fcml_st_assembled_instruction *chosen_instruction;
    fcml_usize number_of_instructions;
} fcml_st_asm_encoder_result;

struct fcml_st_asm_instruction_addr_modes;

typedef fcml_ceh_error (*fcml_fnp_asm_instruction_encoder)( fcml_st_assembler_context *context, fcml_st_dialect_context_int *dialect_context,
        fcml_st_instruction *instruction, fcml_st_asm_encoder_result *result, struct fcml_st_asm_instruction_addr_modes *addr_modes );

typedef struct fcml_st_asm_instruction_addr_modes {
    /* All addressing modes for given mnemonic are available in this list.*/
    fcml_st_coll_list *addr_modes;
    /* Mnemonic.*/
    fcml_string mnemonic;
    /* Instruction encoder.*/
    fcml_fnp_asm_instruction_encoder instruction_encoder;
} fcml_st_asm_instruction_addr_modes;

fcml_ceh_error fcml_fn_asm_init_instruction_encodings( fcml_st_dialect_context_int *context, fcml_coll_map *instructions_map );
fcml_ceh_error fcml_fn_asm_get_instruction_encodings( fcml_coll_map instructions_map, fcml_string mnemonic, fcml_st_asm_instruction_addr_modes ** );
void fcml_fn_asm_free_instruction_encodings( fcml_coll_map instructions_map );

#endif /* FCML_ASM_ENCODING_H_ */
