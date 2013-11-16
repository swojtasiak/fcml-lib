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

#define FCML_ASM_DIALECT_MAX_MNEMONIC_COUNT 50

#define FCML_ASM_DIALECT_INSTRUCTION( x, y )	( ( ( x ) << 16 ) | ( y ) )
#define FCML_ASM_DIALECT_GET_INSTRUCTION( x )	( ( x ) >> 16 )
#define FCML_ASM_DIALECT_GET_ADDR_MODE( x )		( ( x ) & 0x0000FFFF )

/* Declared bellow. */
struct fcml_st_dialect_context;

/* Declared in fcml_disassembler.h */
struct fcml_st_dasm_disassembler_result;

typedef struct fcml_st_dialect_mnemonic {
	fcml_string mnemonic;
	fcml_uint32_t instruction;
	fcml_uint8_t flags;
} fcml_st_dialect_mnemonic;

typedef fcml_ceh_error (*fcml_fnp_asm_dialect_get_mnemonic)( fcml_st_def_instruction_desc *instruction, fcml_st_def_addr_mode_desc *addr_mode, fcml_st_condition *condition, fcml_st_mp_mnemonic **mnemonics, int *mnemonic_counter );
typedef fcml_ceh_error (*fcml_fnp_asm_dialect_get_parsed_mnemonics)( fcml_st_def_instruction_desc *instruction, fcml_st_def_addr_mode_desc *addr_mode, fcml_st_mp_mnemonic_set **mnemonics );
typedef void (*fcml_fnp_asm_dialect_free_mnemonic)( fcml_st_mp_mnemonic *mnemonics );
typedef fcml_string (*fcml_fnp_asm_dialect_render_mnemonic)( fcml_string mnemonic, fcml_st_condition *condition, fcml_uint8_t conditional_group, fcml_bool show_carry );
typedef fcml_ceh_error (*fcml_fnp_asm_dialect_get_register)( const fcml_st_register *reg, fcml_string *printable_reg, fcml_bool is_rex );
typedef fcml_ceh_error (*fcml_fnp_asm_dialect_render_size_operator)( fcml_data_size size_operator, fcml_string buffer, fcml_usize buffer_len, fcml_bool is_media_instruction );

typedef struct fcml_st_dialect_context {
    fcml_fnp_asm_dialect_get_mnemonic get_mnemonic;
    fcml_fnp_asm_dialect_get_parsed_mnemonics get_parsed_mnemonics;
    fcml_fnp_asm_dialect_free_mnemonic free_mnemonic;
    fcml_fnp_asm_dialect_render_mnemonic render_mnemonic;
    fcml_fnp_asm_dialect_render_size_operator size_operator_renderer;
    fcml_fnp_asm_dialect_get_register get_register;
    fcml_ptr instruction_renderer;
    fcml_ptr instruction_parser;
} fcml_st_dialect_context;

fcml_st_mp_mnemonic *fcml_fn_asm_dialect_alloc_mnemonic_with_suffix( fcml_st_mp_mnemonic *mnemonic, fcml_string suffix );
fcml_st_mp_mnemonic *fcml_fn_asm_dialect_alloc_mnemonic( fcml_st_mp_mnemonic *mnemonic );
void fcml_fn_asm_dialect_free_mnemonic( fcml_st_mp_mnemonic *mnemonic );

#endif /* FCML_ASM_DIALECT_H_ */
