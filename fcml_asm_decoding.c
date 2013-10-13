/*
 * fcml_asm_decoding.c
 *
 *  Created on: Oct 13, 2013
 *      Author: tas
 */

#include <assert.h>

#include "fcml_ceh.h"
#include "fcml_env.h"
#include "fcml_def.h"
#include "fcml_common.h"
#include "fcml_disassembler.h"
#include "fcml_asm_decoding.h"
#include "fcml_asm_decoding_tree.h"
#include "fcml_mnemonic_parser.h"

/**************************
 * Structures.
 **************************/

typedef struct fcml_ist_asm_dec_operand_wrapper {
	fcml_st_operand operand;
} fcml_ist_asm_dec_operand_wrapper;

typedef struct fcml_ist_asm_dec_disassembler {
    fcml_st_dialect_context dialect_context;
    fcml_asm_dec_tree_decoding_tree *decoding_tree;
} fcml_ist_asm_dec_disassembler;

/* Decoders responsible for operand disassemblation. */
typedef fcml_ceh_error ( *fcml_ifp_asm_dec_operand_decoder )( struct fcml_st_asm_decoding_context *context, fcml_ist_asm_dec_operand_wrapper *operand, fcml_ptr args );

// Definition is located below.
struct fcml_ceh_asm_dec_instruction_decoding_def;

/* Decoders responsible for instruction disassemblation. */
typedef fcml_ceh_error (*fcml_ifp_asm_dec_instruction_decoder)(fcml_st_asm_decoding_context *context, struct fcml_ceh_asm_dec_instruction_decoding_def *instruction_decoding_def, fcml_st_disassembler_result *result);

typedef struct fcml_ist_asm_dec_operand_decoding {
	// Operand access mode.
	fcml_st_def_decoded_addr_mode *decoded_addr_mode;
	// Operand decoder.
	fcml_ifp_asm_dec_operand_decoder decoder;
	// Optional hints, if operand has any.
	fcml_hints hints;
} fcml_ist_asm_dec_operand_decoding;

typedef struct fcml_ceh_asm_dec_instruction_decoding_def {
	/* Opcodes. */
	uint8_t opcodes[3];
	/* Instruction mnemonic */
	fcml_st_mp_mnemonic_set *mnemonics;
	/* Flags that describe prefixes usage. */
	uint16_t prefixes_flags;
	/* Flags that describe some details of opcodes. */
	uint32_t opcode_flags;
	/* Instruction decoder. */
	fcml_ifp_asm_dec_instruction_decoder instruction_decoder;
	/* Function used to decode instruction operands. */
	fcml_ist_asm_dec_operand_decoding operand_decodings[FCML_OPERANDS_COUNT];
	/* Instruction decoding order, for information purpose only. */
	int order;
	// Instruction level hints.
	fcml_hints hints;
} fcml_ceh_asm_dec_instruction_decoding_def;

// Instruction decoder for IA instruction set, currently it is the only one supported decoder.
fcml_ceh_error fcml_fn_asm_dec_instruction_decoder_IA( fcml_st_asm_decoding_context *decoding_context, fcml_ceh_asm_dec_instruction_decoding_def *instruction_decoding_def, fcml_st_disassembler_result *result );

/***********************************
 * Decoding tree related functions.
 ***********************************/

int fcml_fn_asm_dec_dts_calculate_decoding_order( fcml_ceh_asm_dec_instruction_decoding_def *decoding ) {

	uint16_t prefixes = decoding->prefixes_flags;
	uint32_t opcodes = decoding->opcode_flags;

	int order = 0;

	// Mandatory prefix.
	if( FCML_DEF_PREFIX_MANDATORY_66( prefixes ) | FCML_DEF_PREFIX_MANDATORY_F2( prefixes ) | FCML_DEF_PREFIX_MANDATORY_F3( prefixes ) ) {
		order += 3;
	}

	// Opcode extension.
	if( FCML_DEF_OPCODE_FLAGS_OPCODE_IS_EXT(opcodes) ) {
		order++;
	}

	// VEX and XOP prefixes.
	if( FCML_DEF_PREFIX_VEX_REQ( prefixes ) || FCML_DEF_PREFIX_XOP_REQ( prefixes ) ) {
		order++;
	}

	// REX prefix.
	if( FCML_DEF_PREFIX_W_1( prefixes ) || FCML_DEF_PREFIX_W_0( prefixes ) || FCML_DEF_PREFIX_L_1( prefixes ) || FCML_DEF_PREFIX_L_0( prefixes ) ) {
		order += 2;
	}

	return order;
}

fcml_ifp_asm_dec_instruction_decoder fcml_ifn_asm_dec_dts_choose_instruction_decoder( fcml_uint8_t instruction_type ) {
	switch( instruction_type ) {
	case FCML_EN_IT_IA:
		// Currently only IA decoder is supported.
		return &fcml_fn_asm_dec_instruction_decoder_IA;
	}
	return NULL;
}

// *********************
// * Operand decoders. *
// *********************

fcml_ceh_error fcml_fnp_asm_dec_operand_decoder_imm( fcml_st_asm_decoding_context *context, fcml_ist_asm_dec_operand_wrapper *operand, fcml_ptr args ) {
	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
	return error;
}

fcml_ceh_error fcml_fnp_asm_dec_operand_decoder_explicit_reg( fcml_st_asm_decoding_context *context, fcml_ist_asm_dec_operand_wrapper *operand, fcml_ptr args ) {
	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
	return error;
}

fcml_ceh_error fcml_fnp_asm_dec_operand_decoder_explicit_gps_reg_addressing( fcml_st_asm_decoding_context *context, fcml_ist_asm_dec_operand_wrapper *operand, fcml_ptr args ) {
	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
	return error;
}

fcml_ceh_error fcml_fnp_asm_dec_operand_decoder_opcode_reg( fcml_st_asm_decoding_context *context, fcml_ist_asm_dec_operand_wrapper *operand, fcml_ptr args ) {
	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
	return error;
}

fcml_ceh_error fcml_fnp_asm_dec_operand_decoder_immediate_dis_relative( fcml_st_asm_decoding_context *context, fcml_ist_asm_dec_operand_wrapper *operand, fcml_ptr args ) {
	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
	return error;
}

fcml_ceh_error fcml_fnp_asm_dec_operand_decoder_far_pointer( fcml_st_asm_decoding_context *context, fcml_ist_asm_dec_operand_wrapper *operand, fcml_ptr args ) {
	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
	return error;
}

fcml_ceh_error fcml_fnp_asm_dec_operand_decoder_far_pointer_indirect( fcml_st_asm_decoding_context *context, fcml_ist_asm_dec_operand_wrapper *operand, fcml_ptr args ) {
	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
	return error;
}

fcml_ceh_error fcml_fnp_asm_dec_operand_decoder_explicit_ib( fcml_st_asm_decoding_context *context, fcml_ist_asm_dec_operand_wrapper *operand, fcml_ptr args ) {
	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
	return error;
}

fcml_ceh_error fcml_fnp_asm_dec_operand_decoder_segment_relative_offset( fcml_st_asm_decoding_context *context, fcml_ist_asm_dec_operand_wrapper *operand, fcml_ptr args ) {
	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
	return error;
}

fcml_ceh_error fcml_fnp_asm_dec_operand_decoder_rm( fcml_st_asm_decoding_context *context, fcml_ist_asm_dec_operand_wrapper *operand, fcml_ptr args ) {
	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
	return error;
}

fcml_ceh_error fcml_fnp_asm_dec_operand_decoder_r( fcml_st_asm_decoding_context *context, fcml_ist_asm_dec_operand_wrapper *operand, fcml_ptr args ) {
	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
	return error;
}

fcml_ceh_error fcml_fnp_asm_dec_operand_decoder_vex_vvvv( fcml_st_asm_decoding_context *context, fcml_ist_asm_dec_operand_wrapper *operand, fcml_ptr args ) {
	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
	return error;
}

fcml_ceh_error fcml_fnp_asm_dec_operand_decoder_is4( fcml_st_asm_decoding_context *context, fcml_ist_asm_dec_operand_wrapper *operand, fcml_ptr args ) {
	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
	return error;
}

fcml_ceh_error fcml_fnp_asm_dec_operand_decoder_pseudo_op( fcml_st_asm_decoding_context *context, fcml_ist_asm_dec_operand_wrapper *operand, fcml_ptr args ) {
	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
	return error;
}

// *********************
// * Hints calculators *
// *********************

// TODO: Mechanizm hintow jest taki sam dla assemblera i disassemblera, moze by go uwsponic i wspoldzielic.

typedef struct fcml_st_asm_dec_calculated_hints {
    fcml_hints instruction_hints;
    fcml_hints operand_hints;
} fcml_st_asm_dec_calculated_hints;

typedef fcml_st_asm_dec_calculated_hints (*fcml_fnp_asm_dec_instruction_hints_calculator)( fcml_st_def_addr_mode_desc *addr_mode, fcml_st_def_decoded_addr_mode *decoded_addr_mode );

typedef struct fcml_st_asm_dec_operand_decoder_def {
	fcml_ifp_asm_dec_operand_decoder decoder;
	fcml_fnp_asm_dec_instruction_hints_calculator hints_calculator;
} fcml_st_asm_dec_operand_decoder_def;

fcml_st_asm_dec_calculated_hints fcml_fnp_asm_dec_ihc_far_pointer( fcml_st_def_addr_mode_desc *addr_mode, fcml_st_def_decoded_addr_mode *decoded_addr_mode ) {
	fcml_st_asm_dec_calculated_hints hints;
    hints.instruction_hints = FCML_HINT_FAR_POINTER;
    hints.operand_hints = 0;
    return hints;
}

fcml_st_asm_dec_calculated_hints fcml_fnp_asm_dec_ihc_near_pointer( fcml_st_def_addr_mode_desc *addr_mode, fcml_st_def_decoded_addr_mode *decoded_addr_mode ) {
	fcml_st_asm_dec_calculated_hints hints;
    hints.instruction_hints = FCML_HINT_NEAR_POINTER;
    fcml_sf_def_tma_rm *rm_args = (fcml_sf_def_tma_rm*)decoded_addr_mode->addr_mode_args;
    if( rm_args->reg_type == FCML_REG_SIMD && ( rm_args->flags & FCML_RMF_M ) ) {
        hints.operand_hints = FCML_OP_HINT_MULTIMEDIA_INSTRUCTION;
    } else {
        hints.operand_hints = 0;
    }
    return hints;
}

fcml_st_asm_dec_operand_decoder_def fcml_def_operand_decoders[] = {
	{ NULL, NULL },
	{ fcml_fnp_asm_dec_operand_decoder_imm, NULL },
	{ fcml_fnp_asm_dec_operand_decoder_explicit_reg, NULL },
	{ fcml_fnp_asm_dec_operand_decoder_opcode_reg, NULL },
	{ fcml_fnp_asm_dec_operand_decoder_immediate_dis_relative, NULL },
	{ fcml_fnp_asm_dec_operand_decoder_far_pointer, fcml_fnp_asm_dec_ihc_far_pointer },
	{ fcml_fnp_asm_dec_operand_decoder_far_pointer_indirect, fcml_fnp_asm_dec_ihc_far_pointer },
	{ fcml_fnp_asm_dec_operand_decoder_explicit_gps_reg_addressing, NULL },
	{ fcml_fnp_asm_dec_operand_decoder_explicit_ib,  NULL },
	{ fcml_fnp_asm_dec_operand_decoder_segment_relative_offset,  NULL },
	{ fcml_fnp_asm_dec_operand_decoder_rm, fcml_fnp_asm_dec_ihc_near_pointer },
	{ fcml_fnp_asm_dec_operand_decoder_r, NULL },
	{ fcml_fnp_asm_dec_operand_decoder_vex_vvvv, NULL },
	{ fcml_fnp_asm_dec_operand_decoder_is4, NULL },
	{ fcml_fnp_asm_dec_operand_decoder_rm, NULL },
	{ fcml_fnp_asm_dec_operand_decoder_pseudo_op, NULL }
};

void fcml_ifn_asm_dec_dts_free_operand_decoding( fcml_ist_asm_dec_operand_decoding *operand_decoding ) {
	if( operand_decoding->decoded_addr_mode ) {
		fcml_fnp_def_free_addr_mode( operand_decoding->decoded_addr_mode );
	}
}

fcml_ceh_error fcml_ifn_asm_dec_dts_prepare_operand_decoding( fcml_st_def_addr_mode_desc *addr_mode_desc, fcml_ist_asm_dec_operand_decoding *operand_decoding, fcml_uint32_t operand_def, fcml_hints *instruction_hints ) {

	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

	if( operand_def == FCML_NA ) {
		return error;
	}

	operand_decoding->hints = 0;

	fcml_st_def_decoded_addr_mode *decoded_addr_mode = fcml_fnp_def_decode_addr_mode_args( operand_def, &error );
	if( error ) {
		return error;
	}

	operand_decoding->decoded_addr_mode = decoded_addr_mode;

	fcml_st_asm_dec_operand_decoder_def *operand_decoder_def = &(fcml_def_operand_decoders[ decoded_addr_mode->addr_mode ]);

	operand_decoding->decoder = operand_decoder_def->decoder;
	if( operand_decoder_def->hints_calculator ) {
		fcml_st_asm_dec_calculated_hints hints = operand_decoder_def->hints_calculator( addr_mode_desc, decoded_addr_mode );
		operand_decoding->hints |= hints.operand_hints;
		*instruction_hints |= hints.instruction_hints;
	}

	return error;
}

void fcml_ifn_asm_dec_dts_dispose_instruction_decoding_callback_default( fcml_st_dialect_context *dialect, fcml_ptr decoding_ptr ) {

	fcml_ceh_asm_dec_instruction_decoding_def *decoding = (fcml_ceh_asm_dec_instruction_decoding_def *)decoding_ptr;

	if( decoding->mnemonics ) {
		fcml_fn_mp_free_mnemonics( decoding->mnemonics );
	}

	int i;
	for( i = 0; i < FCML_OPERANDS_COUNT; i++ ) {
		fcml_ifn_asm_dec_dts_free_operand_decoding( &(decoding->operand_decodings[i]) );
	}

	fcml_fn_env_memory_free( decoding );
}

fcml_ceh_error fcml_ifn_asm_dec_dts_prepare_instruction_decoding_callback_default( fcml_st_dialect_context *dialect, fcml_ceh_asm_dec_tree_diss_tree_element *element, fcml_st_def_instruction_description *instruction_desc, fcml_st_def_addr_mode_desc *opcode_desc ) {

	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

	// Prepare instruction decoding structure.
	fcml_ceh_asm_dec_instruction_decoding_def *decoding = fcml_fn_env_clear_memory_alloc( sizeof( struct fcml_ceh_asm_dec_instruction_decoding_def ) );
	if( !decoding ) {
		return FCML_CEH_GEC_OUT_OF_MEMORY;
	}

	// Copy opcodes.
	int i;
	for( i = 0; i < sizeof( opcode_desc->opcode ); i++ ) {
		decoding->opcodes[i] = opcode_desc->opcode[i];
	}

	// Choose instruction mnemonic.
	fcml_string mnemonic = instruction_desc->mnemonic;
    if( opcode_desc->mnemonic_override != NULL ) {
        mnemonic = opcode_desc->mnemonic_override;
    }

	error = fcml_fn_mp_parse_mnemonics( mnemonic, &(decoding->mnemonics) );
	if( error ) {
	    return FCML_CEH_GEC_INVALID_INPUT;
	}

	// Copy flags.
	decoding->prefixes_flags = opcode_desc->allowed_prefixes;
	decoding->opcode_flags = opcode_desc->opcode_flags;

	// Choose function used to disassemble instruction.
	decoding->instruction_decoder = fcml_ifn_asm_dec_dts_choose_instruction_decoder( instruction_desc->instruction_type );

	// Clear instruction level hints. Just to be sure.
	decoding->hints = 0;

	// Prepare operand decoders.
	for( i = 0; i < FCML_OPERANDS_COUNT; i++ ) {
		error = fcml_ifn_asm_dec_dts_prepare_operand_decoding( opcode_desc, &(decoding->operand_decodings[i]), opcode_desc->opperands[i], &(decoding->hints) );
		if( error ) {
			return error;
		}
	}

	// Insert it in appropriate order.
	int order = fcml_fn_asm_dec_dts_calculate_decoding_order( decoding );

	decoding->order = order;

	fcml_st_coll_list *instruction_decoding_defs = element->instruction_decoding_defs;
	fcml_st_coll_list_element *current = instruction_decoding_defs->head;

	// Insert prepared instruction decoding in appropriate order.
	fcml_st_coll_list_element *prev = NULL;
	while( current ) {
		fcml_ceh_asm_dec_instruction_decoding_def *decoding_def = (fcml_ceh_asm_dec_instruction_decoding_def*)current->item;
		if( decoding_def && decoding_def->order < order ) {
			break;
		}
		prev = current;
		current = current->next;
	}

	if( !fcml_fn_coll_list_insert( instruction_decoding_defs, prev, decoding ) ) {
		fcml_fn_env_memory_free( decoding );
		error = FCML_CEH_GEC_OUT_OF_MEMORY;
	}

	return error;
}

/************************************
 * Instructions decoding.
 ************************************/

fcml_ceh_error fcml_fn_asm_dec_instruction_decoder_IA( fcml_st_asm_decoding_context *decoding_context, fcml_ceh_asm_dec_instruction_decoding_def *instruction_decoding_def, fcml_st_disassembler_result *result ) {
	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
	return error;
}

fcml_ceh_error fcml_fn_asm_init_instruction_decodings( fcml_st_dialect_context *dialect_context, fcml_st_disassembler **disassembler ) {
	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

	fcml_ist_asm_dec_disassembler *int_disasm = fcml_fn_env_clear_memory_alloc( sizeof( fcml_ist_asm_dec_disassembler ) );
	if( int_disasm ) {

		int_disasm->dialect_context = *dialect_context;
		error = fcml_fn_asm_dec_tree_init( dialect_context, &(int_disasm->decoding_tree), &fcml_ifn_asm_dec_dts_prepare_instruction_decoding_callback_default, &fcml_ifn_asm_dec_dts_dispose_instruction_decoding_callback_default );
		if( !error ) {
			*disassembler = (fcml_st_disassembler*)int_disasm;
		}

	} else {
		error = FCML_CEH_GEC_OUT_OF_MEMORY;
	}

	return error;
}

void fcml_fn_asm_free_instruction_decodings( fcml_st_disassembler *disassembler ) {
	fcml_ist_asm_dec_disassembler *dec_disasm = (fcml_ist_asm_dec_disassembler*)disassembler;
    if( dec_disasm ) {
    	if( dec_disasm->decoding_tree ) {
    		fcml_fn_asm_dec_tree_free( &(dec_disasm->dialect_context), dec_disasm->decoding_tree );
    	}
        fcml_fn_env_memory_free( dec_disasm );
    }
}
