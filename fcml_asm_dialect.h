/*
 * fcml_asm_dialect.h
 *
 *  Created on: 1 wrz 2013
 *      Author: tAs
 */

#ifndef FCML_ASM_DIALECT_H_
#define FCML_ASM_DIALECT_H_

#include "fcml_def.h"
#include "fcml_common.h"
#include "fcml_stream.h"
#include "fcml_mnemonic_parser.h"
#include "fcml_disassembler_result.h"

#define FCML_ASM_DIALECT_MAX_MNEMONIC_COUNT 50

struct fcml_st_dialect_context;

typedef fcml_ceh_error (*fcml_fnp_asm_dialect_get_mnemonic)( fcml_st_def_instruction_description *instruction, fcml_st_def_addr_mode_desc *addr_mode, fcml_st_condition *condition, fcml_st_mp_mnemonic **mnemonics, int *mnemonic_counter );

typedef void (*fcml_fnp_asm_dialect_free_mnemonic)( fcml_st_mp_mnemonic *mnemonics );

typedef fcml_ceh_error (*fcml_fnp_rend_render_instruction)( struct fcml_st_dialect_context *dialect_context, fcml_st_memory_stream *output_stream, fcml_st_disassembler_result *result, fcml_uint32_t render_flags );

typedef fcml_ceh_error (*fcml_fnp_asm_dialect_get_register)( fcml_st_register *reg, fcml_string *printable_reg, fcml_bool is_rex );

typedef fcml_ceh_error (*fcml_fnp_asm_dialect_render_size_operator)( fcml_data_size size_operator, fcml_string buffer, fcml_usize buffer_len, fcml_bool is_media_instruction );

typedef struct fcml_st_dialect_context {
    fcml_fnp_asm_dialect_get_mnemonic get_mnemonic;
    fcml_fnp_asm_dialect_free_mnemonic free_mnemonic;
    fcml_fnp_rend_render_instruction instruction_renderer;
    fcml_fnp_asm_dialect_render_size_operator size_operator_renderer;
    fcml_fnp_asm_dialect_get_register get_register;
} fcml_st_dialect_context;

fcml_st_mp_mnemonic *fcml_fn_asm_dialect_alloc_mnemonic_with_suffix( fcml_st_mp_mnemonic *mnemonic, fcml_string suffix );
fcml_st_mp_mnemonic *fcml_fn_asm_dialect_alloc_mnemonic( fcml_st_mp_mnemonic *mnemonic );
void fcml_fn_asm_dialect_free_mnemonic( fcml_st_mp_mnemonic *mnemonic );

#endif /* FCML_ASM_DIALECT_H_ */
