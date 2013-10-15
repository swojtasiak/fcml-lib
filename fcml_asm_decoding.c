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
#include "fcml_modrm_decoder.h"
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
typedef fcml_ceh_error (*fcml_ifp_asm_dec_instruction_decoder)( fcml_st_asm_decoding_context *context, struct fcml_ceh_asm_dec_instruction_decoding_def *instruction_decoding_def, fcml_st_disassembler_result *result);

typedef fcml_bool (*fcml_ifp_asm_dec_instruction_acceptor)( fcml_st_asm_decoding_context *context, struct fcml_ceh_asm_dec_instruction_decoding_def *instruction_decoding_def );

typedef struct fcml_ist_asm_dec_addr_mode_acceptor_chain {
	struct fcml_ist_asm_dec_addr_mode_acceptor_chain *next;
	fcml_ifp_asm_dec_instruction_acceptor acceptor;
} fcml_ist_asm_dec_addr_mode_acceptor_chain;

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
	fcml_ist_asm_dec_addr_mode_acceptor_chain *instruction_acceptors_chain;
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


/*********************
 * Prefixes.
 *********************/

fcml_st_dasm_instruction_prefix* fcml_ifn_asm_dec_get_prefix_by_type( fcml_st_asm_decoding_context *context, fcml_st_dasm_prefix_types prefix_type ) {
	fcml_st_dasm_instruction_prefix* prefix = NULL;
	fcml_st_asm_dec_prefixes *prefixes = &(context->prefixes);
	fcml_int prefix_count = prefixes->prefixes_count;
	fcml_int i;
	for( i = 0; i < prefix_count; i++ ) {
		if( prefixes->prefixes[i].prefix_type == prefix_type ) {
			prefix = &(prefixes->prefixes[i]);
			break;
		}
	}
	return prefix;
}

fcml_st_dasm_instruction_prefix* fcml_ifn_asm_dec_get_prefix_if_available( fcml_st_asm_decoding_context *context, fcml_uint8_t prefix_value ) {
	fcml_st_dasm_instruction_prefix* prefix = NULL;
	fcml_st_asm_dec_prefixes *prefixes = &(context->prefixes);
	fcml_int prefix_count = prefixes->prefixes_count;
	fcml_int i;
	for( i = 0; i < prefix_count; i++ ) {
		if( prefixes->prefixes[i].prefix == prefix_value ) {
			prefix = &(prefixes->prefixes[i]);
			break;
		}
	}
	return prefix;
}

fcml_bool fcml_asm_dec_is_prefix_available( fcml_st_asm_decoding_context *context, uint8_t prefix, fcml_bool mandatory ) {
	fcml_st_asm_dec_prefixes *prefixes = &(context->prefixes);
	// Handle VEX mandatory prefixes.
	if( mandatory && prefixes->is_vex && prefixes->pp ) {
		if( prefixes->pp == 0x01 && prefix == 0x66 ) {
			return FCML_TRUE;
		}
		if( prefixes->pp == 0x02 && prefix == 0xF3 ) {
			return FCML_TRUE;
		}
		if( prefixes->pp == 0x03 && prefix == 0xF2 ) {
			return FCML_TRUE;
		}
	}
	fcml_st_dasm_instruction_prefix *found_prefix = fcml_ifn_asm_dec_get_prefix_if_available( context, prefix );
	return mandatory ? ( found_prefix != NULL && found_prefix->mandatory_prefix ) : ( found_prefix != NULL );
}

/******************************
 * Effective attributes sizes.
 ******************************/

fcml_data_size fcml_adm_sec_calculate_effective_asa( fcml_st_asm_decoding_context *context ) {

	fcml_st_disassembler_context *disassembler_context = context->disassembler_context;
	fcml_data_size effective_asa = disassembler_context->address_size_attribute;

	// Checks if address size attribute is overridden.
	if( fcml_asm_dec_is_prefix_available( context, 0x67, FCML_FALSE ) ) {
		switch( disassembler_context->addr_form ) {
		case FCML_AF_16_BIT:
		case FCML_AF_32_BIT:
			effective_asa = ( effective_asa == FCML_DS_32 ) ? FCML_DS_16 : FCML_DS_32;
			break;
		case FCML_AF_64_BIT:
			effective_asa = ( effective_asa == FCML_DS_32 ) ? FCML_DS_64 : FCML_DS_32;
			break;
		}
	}

	return effective_asa;
}

fcml_data_size fcml_adm_sec_calculate_effective_osa( fcml_st_asm_decoding_context *context, fcml_uint32_t opcode_flags ) {

	fcml_st_dasm_instruction_prefix *prefix;

	fcml_st_disassembler_context *disassembler_context = context->disassembler_context;
	fcml_st_asm_dec_prefixes *prefixes = &(context->prefixes);
	fcml_data_size osa = disassembler_context->operand_size_attribute;

	// Gets effective address-size attribute for used mode.
	switch( disassembler_context->addr_form ) {
	case FCML_AF_16_BIT:
	case FCML_AF_32_BIT:
		// In 16 and 32 bit mode only prefixes can change address-size attribute.
		prefix = fcml_ifn_asm_dec_get_prefix_if_available( context, 0x66 );
		if( prefix != NULL && !prefix->mandatory_prefix ) {
			osa = ( osa == FCML_DS_16 ) ? FCML_DS_32 : FCML_DS_16;
		}
		break;
	case FCML_AF_64_BIT:
		// For some instructions EOSA can be forced to 64 bits.
		if( FCML_DEF_OPCODE_FLAGS_FORCE_64BITS_EOSA( opcode_flags ) ) {
			osa = FCML_DS_64;
		} else {
			if( prefixes->w ) {
				// Prefixes can not override REX.W.
				osa = FCML_DS_64;
			} else {
				prefix = fcml_ifn_asm_dec_get_prefix_if_available( context, 0x66 );
				if( prefix != NULL && !prefix->mandatory_prefix ) {
					osa = ( osa == FCML_DS_16 ) ? FCML_DS_32 : FCML_DS_16;
				}
			}
		}
		break;
	}

	return osa;
}

/*********************
 * Acceptors.
 *********************/

typedef fcml_ifp_asm_dec_instruction_acceptor (*fcml_ifp_asm_dec_instruction_acceptor_factory)( fcml_st_def_addr_mode_desc *addr_mode_desc );

// ---------
// Prefixes.
// ---------

fcml_bool fcml_ifp_asm_dec_instruction_acceptor_prefixes( fcml_st_asm_decoding_context *context, fcml_ceh_asm_dec_instruction_decoding_def *instruction_decoding_def ) {

	// Prefixes.
	fcml_st_asm_dec_prefixes *prefixes = &(context->prefixes);

	// VEX required.
	if( FCML_DEF_PREFIX_VEX_REQ( instruction_decoding_def->prefixes_flags ) && !prefixes->is_vex  ) {
		// VEX prefix is required.
		return FCML_FALSE;
	}

	// XOP required.
	if( FCML_DEF_PREFIX_XOP_REQ( instruction_decoding_def->prefixes_flags ) && !prefixes->is_xop ) {
		// VEX prefix is required.
		return FCML_FALSE;
	}

	// Check if VVVV is set to 1111 if needed.
	if( FCML_DEF_PREFIX_VEXOP_VVVV( instruction_decoding_def->prefixes_flags ) && prefixes->vvvv != 0 ) {
		return FCML_FALSE;
	}

	// W field.
	if( ( FCML_DEF_PREFIX_W_0( instruction_decoding_def->prefixes_flags ) && prefixes->w ) ||
		( FCML_DEF_PREFIX_W_1( instruction_decoding_def->prefixes_flags ) && !prefixes->w ) ) {
		return FCML_FALSE;
	}

	// L field.
	if( ( FCML_DEF_PREFIX_L_1( instruction_decoding_def->prefixes_flags ) && ( !prefixes->is_vex || !prefixes->l ) ) ||
		( FCML_DEF_PREFIX_L_0( instruction_decoding_def->prefixes_flags ) && ( !prefixes->is_vex || prefixes->l ) ) ) {
		return FCML_FALSE;
	}

	// Mandatory prefixes.

	fcml_bool found = FCML_FALSE;
	if( FCML_DEF_PREFIX_MANDATORY_66( instruction_decoding_def->prefixes_flags ) ) {
		found = fcml_asm_dec_is_prefix_available(context, 0x66, FCML_TRUE);
	} else if( FCML_DEF_PREFIX_MANDATORY_F2( instruction_decoding_def->prefixes_flags ) ) {
		found = fcml_asm_dec_is_prefix_available(context, 0xF2, FCML_TRUE);
	} else if( FCML_DEF_PREFIX_MANDATORY_F3( instruction_decoding_def->prefixes_flags ) ) {
		found = fcml_asm_dec_is_prefix_available(context, 0xF3, FCML_TRUE);
	} else {
		// Mandatory prefixes not used.
		found = FCML_TRUE;
	}
	if( !found ) {
		// Mandatory prefixes not found.
		return FCML_FALSE;
	}

	return FCML_TRUE;
}

fcml_ifp_asm_dec_instruction_acceptor fcml_ifp_asm_dec_instruction_acceptor_factory_prefixes( fcml_st_def_addr_mode_desc *addr_mode_desc ) {
	return fcml_ifp_asm_dec_instruction_acceptor_prefixes;
}

// ---------
// ModRM.
// ---------

fcml_bool fcml_ifp_asm_dec_instruction_acceptor_modrm( fcml_st_asm_decoding_context *context, fcml_ceh_asm_dec_instruction_decoding_def *instruction_decoding_def ) {

	fcml_uint32_t opcode_flags = instruction_decoding_def->opcode_flags;
	fcml_st_memory_stream *code = context->disassembler_context->code_address;
	fcml_st_asm_dec_prefixes *prefixes = &(context->prefixes);

	// Check addressing mode for ModRM opcodes.
	if( FCML_DEF_OPCODE_FLAGS_MODRM_M( opcode_flags ) ) {
		fcml_bool modrm_found = FCML_FALSE;
		uint8_t modrm = fcml_fn_stream_peek(code, &modrm_found );
		if( !modrm_found || FCML_MODRM_DEC_MOD( modrm ) == 3 ) {
			return FCML_FALSE;
		}
	}
	if( FCML_DEF_OPCODE_FLAGS_MODRM_R( opcode_flags ) ) {
		fcml_bool modrm_found = FCML_FALSE;
		uint8_t modrm = fcml_fn_stream_peek(code, &modrm_found );
		if( !modrm_found || FCML_MODRM_DEC_MOD( modrm ) != 3 ) {
			return FCML_FALSE;
		}
	}

	// Check opcode extension. We have to access ModRM byte directly here.
	fcml_bool opcodes_valid = FCML_FALSE;
	if( FCML_DEF_OPCODE_FLAGS_OPCODE_IS_EXT( opcode_flags ) ) {
		fcml_bool modrm_found = FCML_FALSE;
		fcml_uint8_t modrm = fcml_fn_stream_peek(code, &modrm_found );
		if( modrm_found ) {
			fcml_uint8_t ext_reg_opcode = ( ( prefixes->r << 4 ) | ( FCML_MODRM_DEC_REG_OPCODE( modrm ) ) );
			fcml_uint8_t expected_ext_reg_opcode = FCML_DEF_OPCODE_FLAGS_OPCODE_EXT( opcode_flags );
			opcodes_valid = ( ext_reg_opcode == expected_ext_reg_opcode );
		}
	} else {
		opcodes_valid = FCML_TRUE;
	}

	if( !opcodes_valid ) {
		return FCML_FALSE;
	}

	return FCML_TRUE;
}

fcml_ifp_asm_dec_instruction_acceptor fcml_ifp_asm_dec_instruction_acceptor_factory_modrm( fcml_st_def_addr_mode_desc *addr_mode_desc ) {
	return fcml_ifp_asm_dec_instruction_acceptor_modrm;
}

// ----------------
// Size attributes.
// ----------------

fcml_bool fcml_ifp_asm_dec_instruction_acceptor_size_attributes_restrictions( fcml_st_asm_decoding_context *context, fcml_ceh_asm_dec_instruction_decoding_def *instruction_decoding_def ) {

	// Check EOSA. These fields allow us to restrict instruction decoding only
	// to specific effective operand sizes. For instance we can define instruction
	// that can be chosen only if EOSA is equal to 16.
	if( FCML_DEF_OPCODE_FLAGS_IS_EOSA_RESTRICTION( instruction_decoding_def->opcode_flags ) ) {
		fcml_bool mandatory_prefix = FCML_FALSE;
		// Ignore 0x66 prefix if this instruction uses it as mandatory prefix. This correction is also
		// done in the next phase for already chosen instruction.
		fcml_st_dasm_instruction_prefix *prefix = fcml_ifn_asm_dec_get_prefix_if_available( context, 0x66 );
		// Set this prefix as a mandatory one if this instruction defines 66 as mandatory.
		// This is set temporarily, only to calculate correct EOSA for instruction.
		if( prefix != NULL ) {
			mandatory_prefix = prefix->mandatory_prefix;
			prefix->mandatory_prefix = FCML_DEF_PREFIX_MANDATORY_66( instruction_decoding_def->prefixes_flags );
		}
		fcml_data_size eosa = fcml_adm_sec_calculate_effective_osa( context, instruction_decoding_def->opcode_flags );
		if( prefix != NULL ) {
			prefix->mandatory_prefix = mandatory_prefix;
		}
		if( !( ( FCML_DEF_OPCODE_FLAGS_EOSA_16( instruction_decoding_def->opcode_flags ) && eosa == FCML_DS_16 ) ||
			( FCML_DEF_OPCODE_FLAGS_EOSA_32( instruction_decoding_def->opcode_flags ) && eosa == FCML_DS_32 ) ||
			( FCML_DEF_OPCODE_FLAGS_EOSA_64( instruction_decoding_def->opcode_flags ) && eosa == FCML_DS_64 ) ) ) {
			// Wrong EOSA, ignore instruction.
			return FCML_FALSE;
		}
	}

	// Check EASA. These fields allow us to restrict instruction decoding only
	// to specific effective address sizes. For instance we can define instruction
	// that can be chosen only if EASA is equal to 16.
	if( FCML_DEF_OPCODE_FLAGS_IS_EASA_RESTRICTION( instruction_decoding_def->opcode_flags ) ) {
		fcml_data_size easa = fcml_adm_sec_calculate_effective_asa( context );
		if( !( ( FCML_DEF_OPCODE_FLAGS_EASA_16( instruction_decoding_def->opcode_flags ) && easa == FCML_DS_16 ) ||
			( FCML_DEF_OPCODE_FLAGS_EASA_32( instruction_decoding_def->opcode_flags ) && easa == FCML_DS_32 ) ||
			( FCML_DEF_OPCODE_FLAGS_EASA_64( instruction_decoding_def->opcode_flags ) && easa == FCML_DS_64 ) ) ) {
			// Wrong EASA, ignore instruction.
			return FCML_FALSE;
		}
	}

	return FCML_TRUE;
}

fcml_ifp_asm_dec_instruction_acceptor fcml_ifp_asm_dec_instruction_acceptor_factory_size_attributes_restrictions( fcml_st_def_addr_mode_desc *addr_mode_desc ) {
	return fcml_ifp_asm_dec_instruction_acceptor_size_attributes_restrictions;
}


// ----------------
// Addressing mode.
// ----------------

fcml_bool fcml_ifp_asm_dec_instruction_acceptor_addr_mode( fcml_st_asm_decoding_context *context, struct fcml_ceh_asm_dec_instruction_decoding_def *instruction_decoding_def ) {

	fcml_st_disassembler_context *disassembler_context = context->disassembler_context;

	fcml_en_addr_form addr_form = disassembler_context->addr_form;

	return ( ( addr_form == FCML_AF_16_BIT || addr_form == FCML_AF_32_BIT ) && FCML_DEF_OPCODE_FLAGS_16_32_BIT_MODE_SUPPORTED( instruction_decoding_def->opcode_flags ) )
				|| ( addr_form == FCML_AF_64_BIT && FCML_DEF_OPCODE_FLAGS_64_BIT_MODE_SUPPORTED( instruction_decoding_def->opcode_flags ) );
}

fcml_ifp_asm_dec_instruction_acceptor fcml_ifp_asm_dec_instruction_acceptor_factory_addr_mode( fcml_st_def_addr_mode_desc *addr_mode_desc ) {
	return fcml_ifp_asm_dec_instruction_acceptor_addr_mode;
}

fcml_ifp_asm_dec_instruction_acceptor_factory fcml_asm_dec_dts_acceptor_factories[] = {
	fcml_ifp_asm_dec_instruction_acceptor_factory_prefixes,
	fcml_ifp_asm_dec_instruction_acceptor_factory_addr_mode,
	fcml_ifp_asm_dec_instruction_acceptor_factory_modrm,
	fcml_ifp_asm_dec_instruction_acceptor_factory_size_attributes_restrictions,
	NULL
};

void fcml_ifn_asm_dec_dts_free_acceptors_chain( fcml_ist_asm_dec_addr_mode_acceptor_chain *chain ) {
	if( !chain ) {
		return;
	}
	if( chain->next ) {
		fcml_ifn_asm_dec_dts_free_acceptors_chain( chain->next );
	}
	fcml_fn_env_memory_free( chain );
}

fcml_ceh_error fcml_ifn_asm_dec_dts_allocate_acceptors_chain( fcml_st_def_addr_mode_desc *addr_mode_desc, fcml_ist_asm_dec_addr_mode_acceptor_chain **chain ) {

	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

	fcml_ist_asm_dec_addr_mode_acceptor_chain *current = NULL, *chain_root = NULL;

	fcml_ifp_asm_dec_instruction_acceptor_factory *factory = &(fcml_asm_dec_dts_acceptor_factories[0]);

	while( *factory ) {
		fcml_ifp_asm_dec_instruction_acceptor acceptor = (*factory)( addr_mode_desc );
		if( acceptor ) {
			fcml_ist_asm_dec_addr_mode_acceptor_chain *chain_element = fcml_fn_env_clear_memory_alloc( sizeof( fcml_ist_asm_dec_addr_mode_acceptor_chain* ) );
			if( !chain_element ) {
				// Free already allocated chain.
				if( chain_root ) {
					fcml_ifn_asm_dec_dts_free_acceptors_chain( chain_root );
				}
				return FCML_CEH_GEC_OUT_OF_MEMORY;
			}
			if( !chain_root ) {
				chain_root = chain_element;
			}
			if( current ) {
				current->next = chain_element;
			}
			current = chain_element;
		}
		factory++;
	}

	*chain = chain_root;

	return error;
}

/*********************
 * Decoding callbacks.
 *********************/

void fcml_ifn_asm_dec_dts_dispose_instruction_decoding_callback_default( fcml_st_dialect_context *dialect, fcml_ptr decoding_ptr ) {

	fcml_ceh_asm_dec_instruction_decoding_def *decoding = (fcml_ceh_asm_dec_instruction_decoding_def *)decoding_ptr;

	if( decoding->mnemonics ) {
		fcml_fn_mp_free_mnemonics( decoding->mnemonics );
	}

	int i;
	for( i = 0; i < FCML_OPERANDS_COUNT; i++ ) {
		fcml_ifn_asm_dec_dts_free_operand_decoding( &(decoding->operand_decodings[i]) );
	}

	fcml_ifn_asm_dec_dts_free_acceptors_chain( decoding->instruction_acceptors_chain );

	fcml_fn_env_memory_free( decoding );
}

fcml_ceh_error fcml_ifn_asm_dec_dts_prepare_instruction_decoding_callback_default( fcml_st_dialect_context *dialect, fcml_ceh_asm_dec_tree_diss_tree_element *element, fcml_st_def_instruction_description *instruction_desc, fcml_st_def_addr_mode_desc *addr_mode_desc ) {

	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

	// Prepare instruction decoding structure.
	fcml_ceh_asm_dec_instruction_decoding_def *decoding = fcml_fn_env_clear_memory_alloc( sizeof( struct fcml_ceh_asm_dec_instruction_decoding_def ) );
	if( !decoding ) {
		return FCML_CEH_GEC_OUT_OF_MEMORY;
	}

	// Copy opcodes.
	int i;
	for( i = 0; i < sizeof( addr_mode_desc->opcode ); i++ ) {
		decoding->opcodes[i] = addr_mode_desc->opcode[i];
	}

	// Choose instruction mnemonic.
	fcml_string mnemonic = instruction_desc->mnemonic;
    if( addr_mode_desc->mnemonic_override != NULL ) {
        mnemonic = addr_mode_desc->mnemonic_override;
    }

	error = fcml_fn_mp_parse_mnemonics( mnemonic, &(decoding->mnemonics) );
	if( error ) {
		fcml_fn_env_memory_free( decoding );
	    return FCML_CEH_GEC_INVALID_INPUT;
	}

	// Copy flags.
	decoding->prefixes_flags = addr_mode_desc->allowed_prefixes;
	decoding->opcode_flags = addr_mode_desc->opcode_flags;

	error = fcml_ifn_asm_dec_dts_allocate_acceptors_chain( addr_mode_desc, &(decoding->instruction_acceptors_chain) );
	if( error ) {
		fcml_fn_mp_free_mnemonics( decoding->mnemonics );
		fcml_fn_env_memory_free( decoding );
		return error;
	}

	// Choose function used to disassemble instruction.
	decoding->instruction_decoder = fcml_ifn_asm_dec_dts_choose_instruction_decoder( instruction_desc->instruction_type );

	// Clear instruction level hints. Just to be sure.
	decoding->hints = 0;

	// Prepare operand decoders.
	for( i = 0; i < FCML_OPERANDS_COUNT; i++ ) {
		error = fcml_ifn_asm_dec_dts_prepare_operand_decoding( addr_mode_desc, &(decoding->operand_decodings[i]), addr_mode_desc->opperands[i], &(decoding->hints) );
		if( error ) {
			fcml_ifn_asm_dec_dts_free_acceptors_chain( decoding->instruction_acceptors_chain );
			fcml_fn_mp_free_mnemonics( decoding->mnemonics );
			fcml_fn_env_memory_free( decoding );
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
		fcml_ifn_asm_dec_dts_free_acceptors_chain( decoding->instruction_acceptors_chain );
		fcml_fn_mp_free_mnemonics( decoding->mnemonics );
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

fcml_ceh_error fcml_fn_asm_decode_instruction( fcml_st_asm_decoding_context *context ) {
	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
	return error;
}
