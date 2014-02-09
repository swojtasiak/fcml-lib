/*
 * fcml_asm_dialect.h
 *
 *  Created on: 1 wrz 2013
 *      Author: tAs
 */

#ifndef FCML_ASM_DIALECT_INT_H_
#define FCML_ASM_DIALECT_INT_H_

#include <fcml_dialect.h>
#include <fcml_common.h>
#include <fcml_parser.h>
#include <fcml_renderer.h>
#include <fcml_assembler.h>
#include <fcml_disassembler.h>

#include "fcml_def.h"
#include "fcml_stream.h"
#include "fcml_mnemonic_parser.h"

#define FCML_ASM_DIALECT_MAX_MNEMONIC_COUNT 50

#define FCML_ASM_DIALECT_INSTRUCTION( x, y )	( ( ( x ) << 16 ) | ( y ) )
#define FCML_ASM_DIALECT_GET_INSTRUCTION( x )	( ( x ) >> 16 )
#define FCML_ASM_DIALECT_GET_ADDR_MODE( x )		( ( x ) & 0x0000FFFF )

typedef struct fcml_st_dialect_mnemonic {
	fcml_string mnemonic;
	fcml_uint32_t instruction;
	fcml_uint32_t flags;
} fcml_st_dialect_mnemonic;

typedef void (*fcml_fnp_asm_dialect_free_mnemonic)( fcml_st_mp_mnemonic *mnemonics );
typedef fcml_ceh_error (*fcml_fnp_asm_dialect_get_mnemonic)( const fcml_st_dialect *dialect, fcml_st_def_instruction_desc *instruction, fcml_st_def_addr_mode_desc *addr_mode, fcml_st_condition *condition, fcml_st_mp_mnemonic **mnemonics, int *mnemonic_counter );
typedef fcml_ceh_error (*fcml_fnp_asm_dialect_get_parsed_mnemonics)( const fcml_st_dialect *dialect, fcml_st_def_instruction_desc *instruction, fcml_st_def_addr_mode_desc *addr_mode, fcml_st_mp_mnemonic_set **mnemonics );
typedef fcml_string    (*fcml_fnp_asm_dialect_render_mnemonic)( fcml_string mnemonic, fcml_st_condition *condition, fcml_uint8_t conditional_group, fcml_bool show_carry );
typedef fcml_ceh_error (*fcml_fnp_asm_dialect_get_register)( const fcml_st_register *reg, fcml_string buffer, fcml_int buffer_length, fcml_bool is_rex );
typedef fcml_ceh_error (*fcml_fnp_asm_dialect_prepare_assembler_preprocessor)( const fcml_st_dialect *dialect, fcml_st_instruction *instrunction, fcml_st_def_addr_mode_desc *addr_mode_desc, fcml_st_mp_mnemonic *mnemonic, fcml_bool *has_been_changed );
typedef fcml_ceh_error (*fcml_fnp_asm_dialect_prepare_disassembler_postprocessor)( const fcml_st_mp_mnemonic *mnemonic, fcml_st_disassembler_result *disassembler_result );
typedef fcml_ceh_error (*fcml_fnp_parse_instruction)( fcml_st_dialect *dialect, fcml_string instruction, fcml_st_parser_result *result_out );
typedef fcml_ceh_error (*fcml_fnp_render_instruction)( fcml_st_dialect *dialect_context, fcml_st_render_config *config, fcml_st_memory_stream *output_stream, fcml_st_disassembler_result *result );

/* Internal representation of dialect context.*/
typedef struct fcml_st_dialect_context_int {
    fcml_coll_map dialect_mnemonics_lookup;
    fcml_fnp_asm_dialect_get_mnemonic get_mnemonic;
    fcml_fnp_asm_dialect_get_parsed_mnemonics get_parsed_mnemonics;
    fcml_fnp_asm_dialect_free_mnemonic free_mnemonic;
    fcml_fnp_asm_dialect_render_mnemonic render_mnemonic;
    fcml_fnp_asm_dialect_get_register get_register;
    fcml_fnp_asm_dialect_prepare_assembler_preprocessor assembler_preprocessor;
    fcml_fnp_asm_dialect_prepare_disassembler_postprocessor disassembler_postprocessor;
    fcml_fnp_render_instruction instruction_renderer;
    fcml_fnp_parse_instruction instruction_parser;
    fcml_uint32_t config_flags;
} fcml_st_dialect_context_int;

fcml_st_mp_mnemonic *fcml_fn_asm_dialect_alloc_mnemonic_with_suffix( fcml_st_mp_mnemonic *mnemonic, fcml_string suffix );
fcml_st_mp_mnemonic *fcml_fn_asm_dialect_alloc_mnemonic( fcml_st_mp_mnemonic *mnemonic );
void fcml_fn_asm_dialect_free_mnemonic( fcml_st_mp_mnemonic *mnemonic );
fcml_ceh_error fcml_fn_asm_dialect_alloc_mnemonic_lookup( fcml_st_dialect_context_int **dialect_context, fcml_st_dialect_mnemonic *mnemonic, fcml_usize capacity );
void fcml_fn_asm_dialect_free_mnemonic_lookup( fcml_st_dialect_context_int *dialect_context );

#endif /* FCML_ASM_DIALECT_INT_H_ */
