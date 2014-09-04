/*
 * FCML - Free Code Manipulation Library.
 * Copyright (C) 2010-2014 Slawomir Wojtasiak
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef FCML_ASM_DIALECT_INT_H_
#define FCML_ASM_DIALECT_INT_H_

#include <fcml_dialect.h>
#include <fcml_common.h>
#include <fcml_parser.h>
#include <fcml_renderer.h>
#include <fcml_assembler.h>
#include <fcml_disassembler.h>

#include "fcml_parser_int.h"
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

typedef struct fcml_st_dialect_pseudpo_operation_mnemonic {
	fcml_string mnemonic;
	fcml_en_pseudo_operations pseudo_operation;
} fcml_st_dialect_pseudpo_operation_mnemonic;

typedef void (*fcml_fnp_asm_dialect_free_mnemonic)( fcml_st_mp_mnemonic *mnemonics );
typedef fcml_ceh_error (*fcml_fnp_asm_dialect_get_mnemonic)( const fcml_st_dialect *dialect, fcml_st_def_instruction_desc *instruction, fcml_st_def_addr_mode_desc *addr_mode, fcml_st_condition *condition, fcml_st_mp_mnemonic **mnemonics, int *mnemonic_counter );
typedef fcml_ceh_error (*fcml_fnp_asm_dialect_get_parsed_mnemonics)( const fcml_st_dialect *dialect, fcml_st_def_instruction_desc *instruction, fcml_st_def_addr_mode_desc *addr_mode, fcml_st_mp_mnemonic_set **mnemonics );
typedef fcml_string    (*fcml_fnp_asm_dialect_render_mnemonic)( fcml_string mnemonic, fcml_st_condition *condition, fcml_uint8_t conditional_group, fcml_bool show_carry );
typedef fcml_string    (*fcml_fnp_asm_dialect_get_pseudo_operation_mnemonic)( fcml_en_pseudo_operations pseudo_operation );
typedef fcml_ceh_error (*fcml_fnp_asm_dialect_get_register)( const fcml_st_register *reg, fcml_string buffer, fcml_int buffer_length, fcml_bool is_rex );
typedef fcml_ceh_error (*fcml_fnp_asm_dialect_prepare_assembler_preprocessor)( const fcml_st_assembler_conf *conf, const fcml_st_dialect *dialect, fcml_st_instruction *instrunction, fcml_st_def_addr_mode_desc *addr_mode_desc, fcml_en_instruction instruction, fcml_st_mp_mnemonic *mnemonic, fcml_bool *has_been_changed );
typedef fcml_ceh_error (*fcml_fnp_asm_dialect_prepare_disassembler_postprocessor)( const fcml_st_disassembler_conf *conf, const fcml_st_mp_mnemonic *mnemonic, fcml_st_disassembler_result *disassembler_result );
typedef fcml_ceh_error (*fcml_fnp_parse_instruction)( fcml_ip ip, const fcml_string asm_mnemonic, fcml_st_parser_ast *ast );
typedef fcml_ceh_error (*fcml_fnp_render_instruction)( const fcml_st_dialect *dialect, const fcml_st_render_config *config, fcml_st_memory_stream *output_stream, const fcml_st_disassembler_result *result );
typedef fcml_st_dialect_pseudpo_operation_mnemonic *(*fcml_fnp_asm_get_pseudo_operation_mnemonics)();
typedef void (*fcml_fnp_asm_dialect_free)( fcml_st_dialect *dialect );

/* Internal representation of dialect context.*/
typedef struct fcml_st_dialect_context_int {
    fcml_coll_map dialect_mnemonics_lookup;
    fcml_fnp_asm_dialect_get_mnemonic get_mnemonic;
    fcml_fnp_asm_get_pseudo_operation_mnemonics get_pseudo_operation_mnemonics;
    fcml_fnp_asm_dialect_get_parsed_mnemonics get_parsed_mnemonics;
    fcml_fnp_asm_dialect_get_pseudo_operation_mnemonic get_pseudo_operation_mnemonic;
    fcml_fnp_asm_dialect_free_mnemonic free_mnemonic;
    fcml_fnp_asm_dialect_render_mnemonic render_mnemonic;
    fcml_fnp_asm_dialect_get_register get_register;
    fcml_fnp_asm_dialect_prepare_assembler_preprocessor assembler_preprocessor;
    fcml_fnp_asm_dialect_prepare_disassembler_postprocessor disassembler_postprocessor;
    fcml_fnp_asm_dialect_free free_dialect;
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
