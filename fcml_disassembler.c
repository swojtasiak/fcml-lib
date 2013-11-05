/*
 * fcml_disassembler.c
 *
 *  Created on: Oct 13, 2013
 *      Author: tas
 */

#include "fcml_disassembler.h"

#include <stddef.h>

#include "fcml_coll.h"
#include "fcml_decoding_tree.h"
#include "fcml_def.h"
#include "fcml_env.h"
#include "fcml_errors.h"
#include "fcml_hints.h"
#include "fcml_mnemonic_parser.h"
#include "fcml_modrm.h"
#include "fcml_modrm_decoder.h"
#include "fcml_stream.h"
#include "fcml_utils.h"

// R,X and B are stored in 1's complement form.
#define FCML_VEX_W(x)				FCML_TP_GET_BIT(x, 7)
#define FCML_VEX_R(x)				!FCML_TP_GET_BIT(x, 7)
#define FCML_VEX_X(x)				!FCML_TP_GET_BIT(x, 6)
#define FCML_VEX_B(x)				!FCML_TP_GET_BIT(x, 5)
#define FCML_VEX_L(x)				FCML_TP_GET_BIT(x, 2)
#define FCML_VEX_MMMM(x)			( x & 0x1F )
#define FCML_VEX_VVVV(x)			( ~( ( x & 0x78 ) >> 3 ) & 0x00F )
#define FCML_VEX_PP(x)				( x & 0x03 )

// REX prefix fields.
#define FCML_REX_W(x)					FCML_TP_GET_BIT(x, 3)
#define FCML_REX_R(x)					FCML_TP_GET_BIT(x, 2)
#define FCML_REX_X(x)					FCML_TP_GET_BIT(x, 1)
#define FCML_REX_B(x)					FCML_TP_GET_BIT(x, 0)

typedef struct fcml_ist_dasm_operand_wrapper {
	fcml_st_operand operand;
	fcml_en_access_mode access_mode;
} fcml_ist_dasm_operand_wrapper;

typedef struct fcml_ist_dasm_decoding_context {
	fcml_st_dasm_disassembler_context *disassembler_context;
	fcml_st_memory_stream *stream;
	fcml_st_mp_mnemonic_set *mnemonics;
	fcml_data_size effective_address_size_attribute;
	fcml_data_size effective_operand_size_attribute;
	fcml_int calculated_instruction_size;
	fcml_uint8_t opcodes[FCML_OPCODES_NUM];
	fcml_uint8_t primary_opcode_byte;
	fcml_int opcodes_count;
	fcml_int virtual_opcodes_count;
	fcml_st_dasm_prefixes prefixes;
	fcml_ist_dasm_operand_wrapper operand_wrappers[FCML_OPERANDS_COUNT];
	fcml_st_modrm decoded_modrm;
	fcml_st_modrm_details decoded_modrm_details;
	fcml_hints instruction_hints;
	fcml_nuint8_t pseudo_opcode;
	// Opcode fields.
	fcml_st_condition condition;
	fcml_bool is_conditional;
	fcml_bool opcode_field_w_bit;
	fcml_bool opcode_field_s_bit;
	// is4/is5 byte.
	fcml_nuint8_t isX_byte;
} fcml_ist_dasm_decoding_context;

typedef struct fcml_ist_dasm_disassembler {
    fcml_st_dialect_context dialect_context;
    fcml_st_dt_decoding_tree *decoding_tree;
} fcml_ist_dasm_disassembler;

/* Decoders responsible for operand disassemblation. */
typedef fcml_ceh_error ( *fcml_ifp_dasm_operand_decoder )( struct fcml_ist_dasm_decoding_context *context, fcml_ist_dasm_operand_wrapper *operand, fcml_ptr args );

/* Calculates size of the encoded operand in bytes. */
typedef fcml_int ( *fcml_ifp_dasm_operand_size_calculator )( struct fcml_ist_dasm_decoding_context *context, fcml_ptr args );

// Definition is located below.
struct fcml_ist_dasm_instruction_decoding_def;

/* Decoders responsible for instruction disassemblation. */
typedef fcml_ceh_error (*fcml_ifp_dasm_instruction_decoder)( fcml_ist_dasm_decoding_context *context, struct fcml_ist_dasm_instruction_decoding_def *instruction_decoding_def );
typedef fcml_bool (*fcml_ifp_dasm_instruction_acceptor)( fcml_ist_dasm_decoding_context *context, struct fcml_ist_dasm_instruction_decoding_def *instruction_decoding_def );

typedef struct fcml_ist_dasm_addr_mode_acceptor_chain {
	struct fcml_ist_dasm_addr_mode_acceptor_chain *next;
	fcml_ifp_dasm_instruction_acceptor acceptor;
} fcml_ist_dasm_addr_mode_acceptor_chain;

typedef struct fcml_ist_dasm_operand_decoding {
	// Operand access mode.
	fcml_st_def_decoded_addr_mode *decoded_addr_mode;
	// Operand decoder.
	fcml_ifp_dasm_operand_decoder decoder;
	// Calculates size of the encoded operand in bytes.
	fcml_ifp_dasm_operand_size_calculator size_calculator;
	// Optional hints, if operand has any.
	fcml_hints hints;
} fcml_ist_dasm_operand_decoding;

typedef struct fcml_ist_dasm_modrm_decoding_details {
	fcml_bool is_vsib;
	fcml_data_size vsib_index_size;
} fcml_ist_dasm_modrm_decoding_details;

typedef struct fcml_ist_dasm_instruction_decoding_def {
	/* Instruction type. */
	fcml_uint16_t instruction;
	/* Opcodes. */
	uint8_t opcodes[FCML_OPCODES_NUM];
	/* Instruction mnemonic */
	fcml_st_mp_mnemonic_set *mnemonics;
	/* Flags that describe prefixes usage. */
	uint16_t prefixes_flags;
	/* Flags that describe some details of opcodes. */
	uint32_t opcode_flags;
	/* Instruction decoder. */
	fcml_ifp_dasm_instruction_decoder instruction_decoder;
	/* Chain of address mode acceptors registered for given addressing mode. */
	fcml_ist_dasm_addr_mode_acceptor_chain *instruction_acceptors_chain;
	/* Function used to decode instruction operands. */
	fcml_ist_dasm_operand_decoding operand_decodings[FCML_OPERANDS_COUNT];
	/* Instruction decoding order, for information purpose only. */
	fcml_int order;
	// Instruction level hints.
	fcml_hints hints;
	// ModRM details.
	fcml_ist_dasm_modrm_decoding_details modrm_details;
} fcml_ist_dasm_instruction_decoding_def;

// Instruction decoder for IA instruction set, currently it is the only one supported decoder.
fcml_ceh_error fcml_ifn_dasm_instruction_decoder_IA( fcml_ist_dasm_decoding_context *decoding_context, fcml_ist_dasm_instruction_decoding_def *instruction_decoding_def );

/*********************
 * Utility functions.
 *********************/

void fcml_ifn_dasm_utils_set_x64_exp( fcml_st_register *reg, fcml_bool is_rex ) {
	if( is_rex ) {
		reg->x64_exp = ( reg->type == FCML_REG_GPR && reg->size == FCML_DS_8 && reg->reg >= 4 && reg->reg <= 7 );
	} else {
		reg->x64_exp = FCML_FALSE;
	}
}

void fcml_ifn_dasm_utils_set_segment_selector( fcml_st_segment_selector *seg_sel, fcml_uint8_t seg_reg, fcml_bool is_default ) {
	seg_sel->is_default_reg = is_default;
	fcml_st_register *reg_seg = &(seg_sel->segment_selector);
	reg_seg->reg = seg_reg;
	reg_seg->size = FCML_DS_16;
	reg_seg->type = FCML_REG_SEG;
	reg_seg->x64_exp = FCML_FALSE;
}

fcml_uint8_t fcml_ifn_dasm_utils_override_segment_reg( fcml_ist_dasm_decoding_context *context, fcml_uint8_t reg ) {
	fcml_int i;
	for( i = 0; i < context->prefixes.prefixes_count; i++ ) {
		fcml_st_dasm_instruction_prefix *prefix = &(context->prefixes.prefixes[i]);
		if( prefix->prefix_type == FCML_PT_GROUP_2 && !prefix->mandatory_prefix ) {
			switch( prefix->prefix ) {
			case 0x2E:
				reg = FCML_REG_CS;
				break;
			case 0x36:
				reg = FCML_REG_SS;
				break;
			case 0x3E:
				reg = FCML_REG_DS;
				break;
			case 0x26:
				reg = FCML_REG_ES;
				break;
			case 0x64:
				reg = FCML_REG_FS;
				break;
			case 0x65:
				reg = FCML_REG_GS;
				break;
			}
		}
	}
	return reg;
}

fcml_ceh_error fcml_ifn_dasm_utils_decode_segment_selector( fcml_ist_dasm_decoding_context *context, fcml_st_segment_selector *selector, fcml_uint8_t encoded_segment_reg ) {
	fcml_uint8_t seg_reg = ~FCML_SEG_ALLOW_OVERRIDE & encoded_segment_reg;
	if( encoded_segment_reg & FCML_SEG_ALLOW_OVERRIDE ) {
		fcml_uint8_t tmp = seg_reg;
		seg_reg = fcml_ifn_dasm_utils_override_segment_reg( context, seg_reg );
		selector->is_default_reg = ( seg_reg == tmp );
	} else {
		selector->is_default_reg = FCML_TRUE;
	}
	selector->segment_selector.reg = seg_reg;
	selector->segment_selector.size = FCML_DS_16;
	selector->segment_selector.type = FCML_REG_SEG;
	selector->segment_selector.x64_exp = FCML_FALSE;
	return FCML_CEH_GEC_NO_ERROR;
}

fcml_data_size fcml_ifn_dasm_utils_decode_encoded_size_value( fcml_ist_dasm_decoding_context *context, fcml_uint8_t encoded_size ) {
	fcml_data_size result = 0;
	if( encoded_size >= FCML_EOS_DYNAMIC_BASE ) {
	switch( encoded_size ) {
	case FCML_EOS_EOSA:
		result = context->effective_operand_size_attribute;
		break;
	case FCML_EOS_EASA:
		result = context->effective_address_size_attribute;
		break;
	case FCML_EOS_L:
		result = ( context->prefixes.l ) ? FCML_DS_256 : FCML_DS_128;
		break;
	case FCML_EOS_14_28:
		result = ( context->effective_operand_size_attribute == FCML_DS_16 ) ? ( 14 * 8 ) : ( 28 * 8 );
		break;
	case FCML_EOS_94_108:
		result = ( context->effective_operand_size_attribute == FCML_DS_16 ) ? ( 94 * 8 ) : ( 108 * 8 );
		break;
	case FCML_EOS_32_64:
		result = ( context->effective_operand_size_attribute == FCML_DS_16 ) ? ( 16 * 2 ) : ( 32 * 2 );
		break;
	case FCML_EOS_FPI:
		result = context->effective_operand_size_attribute + 16;
		break;
	}
	} else {
		result = encoded_size * 8;
	}
	return result;
}

/***********************************
 * Decoding tree related functions.
 ***********************************/

int fcml_ifn_dasm_dts_calculate_decoding_order( fcml_ist_dasm_instruction_decoding_def *decoding ) {

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

fcml_ifp_dasm_instruction_decoder fcml_ifn_dasm_dts_choose_instruction_decoder( fcml_uint8_t instruction_type ) {
	switch( instruction_type ) {
	case FCML_EN_IT_IA:
		// Currently only IA decoder is supported.
		return &fcml_ifn_dasm_instruction_decoder_IA;
	}
	return NULL;
}

// *********************
// * Operand decoders. *
// *********************

fcml_ceh_error fcml_ifn_dasm_operand_decoder_imm( fcml_ist_dasm_decoding_context *context, fcml_ist_dasm_operand_wrapper *operand_wrapper, fcml_ptr args ) {

	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

	fcml_sf_def_tma_imm *imm_args = (fcml_sf_def_tma_imm *)args;
	fcml_st_operand *operand = &(operand_wrapper->operand);
	fcml_st_immediate *immediate = &(operand->immediate);
	fcml_st_memory_stream *stream = context->stream;

	operand->type = FCML_EOT_IMMEDIATE;

	fcml_data_size imm_size = fcml_ifn_dasm_utils_decode_encoded_size_value( context, imm_args->encoded_imm_size );
	fcml_data_size imm_size_ex = fcml_ifn_dasm_utils_decode_encoded_size_value( context, imm_args->encoded_ex_imm_size );
	if( imm_size_ex == FCML_DS_UNDEF ) {
		// check if S opcode field is set.
		if( imm_size == FCML_DS_8 && context->opcode_field_s_bit ) {
			imm_size_ex = context->effective_operand_size_attribute;
		} else {
			imm_size_ex = imm_size;
		}
	}

	fcml_st_integer integer;

	// All immediate integers are signed.
	integer.is_signed = FCML_TRUE;

	error = fcml_fn_utils_decode_integer( stream, &integer, imm_size );
	if( error ) {
		return error;
	}

	if( imm_size_ex != imm_size ) {
		error = fcml_fn_utils_convert_integer_to_integer( &integer, &integer, imm_size, imm_size_ex );
		if( error ) {
			return error;
		}
	}

	error = fcml_fn_utils_integer_to_imm( &integer, immediate );
	if( error ) {
		return error;
	}

	return error;
}

fcml_int fcml_ifn_dasm_operand_size_calculator_imm( fcml_ist_dasm_decoding_context *context, fcml_ptr args ) {
	fcml_sf_def_tma_imm *imm_args = (fcml_sf_def_tma_imm *)args;
	return fcml_ifn_dasm_utils_decode_encoded_size_value( context, imm_args->encoded_imm_size ) / 8;
}

fcml_ceh_error fcml_ifn_dasm_operand_decoder_explicit_reg( fcml_ist_dasm_decoding_context *context, fcml_ist_dasm_operand_wrapper *operand_wrapper, fcml_ptr args ) {

	fcml_st_operand *operand = &(operand_wrapper->operand);
	fcml_sf_def_tma_explicit_reg *reg_args = (fcml_sf_def_tma_explicit_reg*)args;

	operand->type = FCML_EOT_REGISTER;
	operand->reg.reg = reg_args->reg_num;
	operand->reg.type = reg_args->reg_type;
	operand->reg.size = fcml_ifn_dasm_utils_decode_encoded_size_value( context, reg_args->encoded_reg_size );

	return FCML_CEH_GEC_NO_ERROR;
}

fcml_ceh_error fcml_ifn_dasm_operand_decoder_explicit_gps_reg_addressing( fcml_ist_dasm_decoding_context *context, fcml_ist_dasm_operand_wrapper *operand_wrapper, fcml_ptr args ) {

	fcml_st_operand *operand = &(operand_wrapper->operand);
	fcml_st_address *address = &(operand->address);
	fcml_st_effective_address *effective_address = &(address->effective_address);

	operand->type = FCML_EOT_ADDRESS;
	address->address_form = FCML_AF_COMBINED;

	fcml_sf_def_tma_explicit_gps_reg_addressing *reg_addr_args = (fcml_sf_def_tma_explicit_gps_reg_addressing*)args;

	// Size operator.
	address->size_operator = fcml_ifn_dasm_utils_decode_encoded_size_value( context, reg_addr_args->encoded_operand_size );

	// Base register.
	effective_address->base.size = context->effective_address_size_attribute;
	effective_address->base.reg = reg_addr_args->reg_num;
	effective_address->base.type = FCML_REG_GPR;

	// Segment register.
	return fcml_ifn_dasm_utils_decode_segment_selector( context, &(address->segment_selector), reg_addr_args->encoded_segment_register );
}

fcml_ceh_error fcml_ifn_dasm_operand_decoder_opcode_reg( fcml_ist_dasm_decoding_context *context, fcml_ist_dasm_operand_wrapper *operand_wrapper, fcml_ptr args ) {

	fcml_sf_def_tma_opcode_reg *reg_args = (fcml_sf_def_tma_opcode_reg*)args;

	fcml_uint8_t reg_num = context->primary_opcode_byte & 0x07;

	if( context->prefixes.b ) {
		reg_num |= 0x08;
	}

	// Size operator.
	operand_wrapper->operand.type = FCML_EOT_REGISTER;
	fcml_st_register *reg = &(operand_wrapper->operand.reg);

	// Base register.
	reg->size = fcml_ifn_dasm_utils_decode_encoded_size_value( context, reg_args->encoded_reg_size );
	reg->type = reg_args->reg_type;
	reg->reg = reg_num;

	return FCML_CEH_GEC_NO_ERROR;
}

fcml_ceh_error fcml_ifn_dasm_operand_decoder_immediate_dis_relative( fcml_ist_dasm_decoding_context *context, fcml_ist_dasm_operand_wrapper *operand_wrapper, fcml_ptr args ) {

	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
	fcml_sf_def_tma_immediate_dis_relative *rel_args = (fcml_sf_def_tma_immediate_dis_relative*)args;
	fcml_data_size int_size = 0;
	fcml_int32_t offset32;
	fcml_int16_t offset16;

	if( FCML_IS_EOS_DYNAMIC( rel_args->encoded_imm_size ) ) {
		return FCML_EN_UNSUPPORTED_ADDRESSING_FORM;
	}

	if( rel_args->encoded_imm_size != FCML_EOS_UNDEFINED ) {
		int_size = rel_args->encoded_imm_size * 8;
	} else {

		if( context->effective_operand_size_attribute == FCML_DS_16 && context->disassembler_context->addr_form == FCML_AF_64_BIT ) {
			return FCML_EN_UNSUPPORTED_ADDRESSING_FORM;
		}

		int_size = FCML_DS_32;

		// For 32 and 64 bit addressing, 32 bit immediate value should be used.
		// Only for 16 bit addressing value differs and is equal to 16.
		if( context->effective_operand_size_attribute == FCML_DS_16 ) {
			int_size = FCML_DS_16;
		}

	}

	fcml_st_integer integer;
	integer.is_signed = FCML_TRUE;

	// Read displacement value from stream.
	error = fcml_fn_utils_decode_integer( context->stream, &integer, int_size );
	if( error ) {
		return error;
	}

	operand_wrapper->operand.type = FCML_EOT_ADDRESS;
	operand_wrapper->operand.address.address_form = FCML_AF_OFFSET;

	fcml_st_offset *offset = &(operand_wrapper->operand.address.offset);
	offset->is_signed = FCML_TRUE;

	// Calculate offset relative to IP.
	fcml_st_instruction_pointer *ip = &(context->disassembler_context->ip);

	switch( context->effective_operand_size_attribute ) {
	case FCML_DS_16:
		error = fcml_fn_utils_convert_integer_to_int16( &integer, &offset16 );
		if( !error ) {
			offset->off32 = ( (fcml_int32_t)ip->eip + context->calculated_instruction_size + offset16 ) & 0x0000FFFF;
			offset->size = FCML_DS_32;
		}
		break;
	case FCML_DS_32:
		error = fcml_fn_utils_convert_integer_to_int32( &integer, &offset32 );
		if( !error ) {
			offset->off32 = ( (fcml_int32_t)ip->eip + context->calculated_instruction_size + offset32 );
			offset->size = FCML_DS_32;
		}
		break;
	case FCML_DS_64:
		error = fcml_fn_utils_convert_integer_to_int32( &integer, &offset32 );
		if( !error ) {
			offset->off64 = ( (fcml_int64_t)ip->rip + context->calculated_instruction_size + offset32 );
			offset->size = FCML_DS_64;
		}
		break;
	}

	// Sets CS segment register.
	fcml_ifn_dasm_utils_set_segment_selector( &(operand_wrapper->operand.address.segment_selector), FCML_REG_CS, FCML_TRUE );

	return error;
}

fcml_int fcml_ifn_dasm_operand_size_calculator_immediate_dis_relative( fcml_ist_dasm_decoding_context *context, fcml_ptr args ) {
	fcml_sf_def_tma_immediate_dis_relative *rel_args = (fcml_sf_def_tma_immediate_dis_relative*)args;
	fcml_int size;
	if( rel_args->encoded_imm_size != FCML_EOS_UNDEFINED ) {
		size = rel_args->encoded_imm_size;;
	} else {
		size = ( context->effective_operand_size_attribute == FCML_DS_16 ) ? FCML_DS_16 / 8 : FCML_DS_32 / 8;
	}
	return size;
}

fcml_ceh_error fcml_ifn_dasm_operand_decoder_far_pointer( fcml_ist_dasm_decoding_context *context, fcml_ist_dasm_operand_wrapper *operand_wrapper, fcml_ptr args ) {

	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
	fcml_st_operand *operand = &(operand_wrapper->operand);
	fcml_st_far_pointer *far_pointer = &(operand->far_pointer);
	fcml_bool result;

	operand->type = FCML_EOT_FAR_POINTER;

	switch( context->effective_operand_size_attribute ) {
	case FCML_DS_16:
		far_pointer->offset16 = fcml_fn_stream_read_word( context->stream, &result );
		break;
	case FCML_DS_32:
		far_pointer->offset32 = fcml_fn_stream_read_dword( context->stream, &result );
		break;
	default:
		error = FCML_EN_UNSUPPORTED_ADDRESSING_MODE;
		break;
	}

	far_pointer->offset_size = context->effective_operand_size_attribute;

	far_pointer->segment = fcml_fn_stream_read_word( context->stream, &result );
	if( !result ) {
		return FCML_CEH_GEC_EOF;
	}

	if( !result ) {
		error = FCML_CEH_GEC_EOF;
	}

	return error;
}

fcml_int fcml_ifn_dasm_operand_size_calculator_far_pointer( fcml_ist_dasm_decoding_context *context, fcml_ptr args ) {
	return context->effective_operand_size_attribute / 8 + 2;
}

fcml_ceh_error fcml_ifn_dasm_operand_decoder_explicit_ib( fcml_ist_dasm_decoding_context *context, fcml_ist_dasm_operand_wrapper *operand_wrapper, fcml_ptr args ) {

	fcml_sf_def_tma_explicit_ib *imm_args = (fcml_sf_def_tma_explicit_ib*)args;

	fcml_st_operand *operand = &(operand_wrapper->operand);
	fcml_st_immediate *immediate = &(operand->immediate);

	operand->type = FCML_EOT_IMMEDIATE;
	immediate->is_signed = FCML_TRUE;
	immediate->imm_size = FCML_DS_8;
	immediate->imm8 = imm_args->ib;

	return FCML_CEH_GEC_NO_ERROR;
}

// -----------------------
// Segment relative offset
// -----------------------

fcml_ceh_error fcml_ifn_dasm_operand_decoder_segment_relative_offset( fcml_ist_dasm_decoding_context *context, fcml_ist_dasm_operand_wrapper *operand_wrapper, fcml_ptr args ) {

	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

	fcml_sf_def_tma_segment_relative_offset *seg_args = (fcml_sf_def_tma_segment_relative_offset*)args;

	fcml_st_operand *operand = &(operand_wrapper->operand);
	fcml_st_address *address = &(operand->address);
	fcml_st_offset *offset = &(address->offset);

	fcml_bool result;

	error = fcml_ifn_dasm_utils_decode_segment_selector( context, &(address->segment_selector), seg_args->encoded_segment_register );
	if( error ) {
		return error;
	}

	address->size_operator = fcml_ifn_dasm_utils_decode_encoded_size_value( context, seg_args->encoded_operand_size );

	operand->type = FCML_EOT_ADDRESS;

	switch( context->effective_address_size_attribute ) {
	case FCML_DS_16:
		offset->off16 = fcml_fn_stream_read_word( context->stream, &result );
		break;
	case FCML_DS_32:
		offset->off32 = fcml_fn_stream_read_dword( context->stream, &result );
		break;
	case FCML_DS_64:
		offset->off64 = fcml_fn_stream_read_qword( context->stream, &result );
		break;
	default:
		error = FCML_EN_UNSUPPORTED_ADDRESSING_MODE;
		break;
	}

	offset->size = context->effective_address_size_attribute;

	if( !result ) {
		error = FCML_CEH_GEC_EOF;
	}

	return error;
}

fcml_int fcml_ifn_dasm_operand_size_calculator_segment_relative_offset( fcml_ist_dasm_decoding_context *context, fcml_ptr args ) {
	return context->effective_address_size_attribute / 8;
}

// -----------
// ModRM - RM
// -----------

fcml_ceh_error fcml_ifn_dasm_operand_decoder_rm( fcml_ist_dasm_decoding_context *context, fcml_ist_dasm_operand_wrapper *operand_wrapper, fcml_ptr args ) {

	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

	fcml_st_modrm *decoded_modrm = &(context->decoded_modrm);
	fcml_st_operand *operand = &(operand_wrapper->operand);

	fcml_sf_def_tma_rm *rm_args = (fcml_sf_def_tma_rm*)args;

	if( ( rm_args->flags & FCML_RMF_R ) && decoded_modrm->reg.is_not_null ) {

		operand->type = FCML_EOT_REGISTER;
		operand->reg.reg = decoded_modrm->reg.value;
		operand->reg.type = rm_args->reg_type;
		operand->reg.size = fcml_ifn_dasm_utils_decode_encoded_size_value( context, rm_args->encoded_register_operand_size );

		fcml_ifn_dasm_utils_set_x64_exp( &(operand->reg), context->prefixes.is_rex );

	} else if ( rm_args->flags & FCML_RMF_M ) {

		operand->type = FCML_EOT_ADDRESS;

		fcml_st_address *address = &(operand->address);
		*address = decoded_modrm->address;

		address->size_operator = fcml_ifn_dasm_utils_decode_encoded_size_value( context, rm_args->encoded_memory_operand_size );

		if( decoded_modrm->is_rip ) {
			// We known instruction size, so post processing is not needed and RIP can be calculated now.
			error = fcml_fn_modrm_decode_rip( context->disassembler_context->ip.rip + context->calculated_instruction_size, context->effective_address_size_attribute, &(address->offset), &(address->offset) );
		}

		// Segment registers.

		fcml_st_effective_address *effective_address = &(address->effective_address);
		fcml_st_segment_selector *segment_selector = &(address->segment_selector);

		segment_selector->segment_selector.type = FCML_REG_SEG;
		segment_selector->segment_selector.size = FCML_DS_16;

		if( effective_address->base.type == FCML_REG_GPR && ( effective_address->base.reg == FCML_REG_BP || effective_address->base.reg == FCML_REG_SP ) ) {
			segment_selector->segment_selector.reg = FCML_REG_SS;
			segment_selector->is_default_reg = FCML_TRUE;
		} else {
			segment_selector->segment_selector.reg = fcml_ifn_dasm_utils_override_segment_reg( context, FCML_REG_DS );
			segment_selector->is_default_reg = ( segment_selector->segment_selector.reg == FCML_REG_DS ) ? FCML_TRUE : FCML_FALSE;
		}

		// These hints aren't used in 32 bit addressing mode.
		if( context->disassembler_context->addr_form == FCML_AF_64_BIT ) {
			operand->hints |= context->decoded_modrm.is_rip ? FCML_OP_HINT_RELATIVE_ADDRESSING : FCML_OP_HINT_ABSOLUTE_ADDRESSING;
		}

	} else {
		error = FCML_EN_UNSUPPORTED_ADDRESSING_MODE;
	}

	return error;
}

// --------------------
// Far pointer indirect
// --------------------

fcml_sf_def_tma_rm  fcml_isst_dasm_far_pointer_indirect_args = { FCML_REG_UNDEFINED, FCML_EOS_UNDEFINED, FCML_EOS_FPI, FCML_RMF_M, 0, FCML_FALSE };

fcml_ceh_error fcml_ifn_dasm_operand_decoder_far_pointer_indirect( fcml_ist_dasm_decoding_context *context, fcml_ist_dasm_operand_wrapper *operand_wrapper, fcml_ptr args ) {
	fcml_sf_def_tma_rm rm_args = fcml_isst_dasm_far_pointer_indirect_args;
	return fcml_ifn_dasm_operand_decoder_rm( context, operand_wrapper, &rm_args );
}

// ----------
// ModRM - R
// ----------

fcml_ceh_error fcml_ifn_dasm_operand_decoder_r( fcml_ist_dasm_decoding_context *context, fcml_ist_dasm_operand_wrapper *operand_wrapper, fcml_ptr args ) {

	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
	fcml_sf_def_tma_r *r_args = (fcml_sf_def_tma_r*)args;

	operand_wrapper->operand.type = FCML_EOT_REGISTER;
	fcml_st_register *reg = &(operand_wrapper->operand.reg);

	reg->reg = context->decoded_modrm.reg_opcode;
	reg->type = r_args->reg_type;
	reg->size = fcml_ifn_dasm_utils_decode_encoded_size_value( context, r_args->encoded_register_operand_size );

	fcml_ifn_dasm_utils_set_x64_exp( reg, context->prefixes.is_rex );

	return error;
}

// ----
// VVVV
// ----

fcml_ceh_error fcml_ifn_dasm_operand_decoder_vex_vvvv( fcml_ist_dasm_decoding_context *context, fcml_ist_dasm_operand_wrapper *operand_wrapper, fcml_ptr args ) {

	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

	fcml_sf_def_tma_vex_vvvv_reg *v_args = (fcml_sf_def_tma_vex_vvvv_reg*)args;

	operand_wrapper->operand.type = FCML_EOT_REGISTER;
	fcml_st_register *reg = &(operand_wrapper->operand.reg);

	reg->reg = context->prefixes.vvvv;
	reg->type = v_args->reg_type;
	reg->size = fcml_ifn_dasm_utils_decode_encoded_size_value( context, v_args->encoded_register_size );

	return error;
}

fcml_ceh_error fcml_ifn_dasm_operand_decoder_isX( fcml_ist_dasm_decoding_context *context, fcml_ist_dasm_operand_wrapper *operand_wrapper, fcml_ptr args ) {

	// IS4/IS5 byte is located just after ModR/M field, so it doesn't have to be read in any post processors.
	fcml_sf_def_tma_is *is_args = (fcml_sf_def_tma_is *)args;

	// Read isX byte from stream, or get cached value from context.
	fcml_uint8_t isX;
	if( context->isX_byte.is_not_null ) {
		isX = context->isX_byte.value;
	} else {
		fcml_bool result;
		isX = fcml_fn_stream_read( context->stream, &result );
		if( !result ) {
			return FCML_CEH_GEC_EOF;
		}
		context->isX_byte.is_not_null = FCML_TRUE;
		context->isX_byte.value = isX;
	}

	// IS4.
	if( ( is_args->flags & FCML_ISF_IS4 ) || ( is_args->flags & FCML_ISF_IS5_SRC ) ) {

		operand_wrapper->operand.type = FCML_EOT_REGISTER;
		fcml_st_register *reg = &(operand_wrapper->operand.reg);

		reg->reg = ( ( context->disassembler_context->addr_form == FCML_AF_32_BIT ) ? ( 0x70 & isX ) : ( 0xF0 & isX ) ) >> 4;
		reg->type = FCML_REG_SIMD;
		reg->size = context->prefixes.l ? FCML_OS_YWORD : FCML_OS_XWORD;
		reg->x64_exp = FCML_FALSE;

	} else {

		// IS5 - M2Z

		operand_wrapper->operand.type = FCML_EOT_IMMEDIATE;
		fcml_st_immediate *imm = &(operand_wrapper->operand.immediate);
		imm->is_signed = FCML_FALSE;
		imm->imm8 = isX & 0x03;
		imm->imm_size = FCML_DS_8;

	}

	return FCML_CEH_GEC_NO_ERROR;
}

fcml_int fcml_ifn_dasm_operand_size_calculator_isX( fcml_ist_dasm_decoding_context *context, fcml_ptr args ) {
	return 1;
}

fcml_ceh_error fcml_ifn_dasm_operand_decoder_pseudo_op( fcml_ist_dasm_decoding_context *context, fcml_ist_dasm_operand_wrapper *operand_wrapper, fcml_ptr args ) {

	fcml_bool result;
	fcml_uint8_t pseudo_op = fcml_fn_stream_read( context->stream, &result );
	if( !result ) {
		return FCML_CEH_GEC_EOF;
	}

	fcml_st_operand *operand = &(operand_wrapper->operand);
	fcml_st_immediate *immediate = &(operand->immediate);

	operand->type = FCML_EOT_IMMEDIATE;
	immediate->is_signed = FCML_TRUE;
	immediate->imm_size = FCML_DS_8;
	immediate->imm8 = pseudo_op;

	context->pseudo_opcode.is_not_null = FCML_TRUE;
	context->pseudo_opcode.value = pseudo_op;

	return FCML_CEH_GEC_NO_ERROR;
}

fcml_int fcml_ifn_dasm_operand_size_calculator_pseudo_op( fcml_ist_dasm_decoding_context *context, fcml_ptr args ) {
	return 1;
}

/****************************/
/* Operand decoders table. */
/****************************/

typedef struct fcml_ist_dasm_operand_decoder_def {
	fcml_ifp_dasm_operand_decoder decoder;
	fcml_ifp_dasm_operand_size_calculator size_calculator;
	fcml_fp_hts_instruction_hints_calculator hints_calculator;
} fcml_ist_dasm_operand_decoder_def;

fcml_ist_dasm_operand_decoder_def fcml_iarr_def_operand_decoders[] = {
	{ NULL, NULL },
	{ fcml_ifn_dasm_operand_decoder_imm, fcml_ifn_dasm_operand_size_calculator_imm, NULL },
	{ fcml_ifn_dasm_operand_decoder_explicit_reg, NULL, NULL },
	{ fcml_ifn_dasm_operand_decoder_opcode_reg, NULL, NULL },
	{ fcml_ifn_dasm_operand_decoder_immediate_dis_relative, fcml_ifn_dasm_operand_size_calculator_immediate_dis_relative, fcml_fn_hts_ihc_immediate_dis_relative },
	{ fcml_ifn_dasm_operand_decoder_far_pointer, fcml_ifn_dasm_operand_size_calculator_far_pointer, fcml_fn_hts_ihc_far_pointer },
	{ fcml_ifn_dasm_operand_decoder_far_pointer_indirect, NULL, fcml_fn_hts_ihc_far_pointer },
	{ fcml_ifn_dasm_operand_decoder_explicit_gps_reg_addressing, NULL, NULL },
	{ fcml_ifn_dasm_operand_decoder_explicit_ib, NULL, NULL },
	{ fcml_ifn_dasm_operand_decoder_segment_relative_offset, fcml_ifn_dasm_operand_size_calculator_segment_relative_offset, NULL },
	{ fcml_ifn_dasm_operand_decoder_rm, NULL, fcml_fn_hts_ihc_modrm_hints },
	{ fcml_ifn_dasm_operand_decoder_r, NULL, NULL },
	{ fcml_ifn_dasm_operand_decoder_vex_vvvv, NULL, NULL },
	{ fcml_ifn_dasm_operand_decoder_isX, fcml_ifn_dasm_operand_size_calculator_isX, NULL },
	{ fcml_ifn_dasm_operand_decoder_rm, NULL, NULL },
	{ fcml_ifn_dasm_operand_decoder_pseudo_op, fcml_ifn_dasm_operand_size_calculator_pseudo_op, fcml_fn_hts_ihc_pseudo_opcode }
};

void fcml_ifn_dasm_dts_free_operand_decoding( fcml_ist_dasm_operand_decoding *operand_decoding ) {
	if( operand_decoding->decoded_addr_mode ) {
		fcml_fnp_def_free_addr_mode( operand_decoding->decoded_addr_mode );
	}
}

fcml_ceh_error fcml_ifn_dasm_dts_prepare_operand_decoding( fcml_st_def_addr_mode_desc *addr_mode_desc, fcml_ist_dasm_operand_decoding *operand_decoding, fcml_uint32_t operand_def, fcml_hints *instruction_hints ) {

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

	fcml_ist_dasm_operand_decoder_def *operand_decoder_def = &(fcml_iarr_def_operand_decoders[ decoded_addr_mode->addr_mode ]);

	operand_decoding->decoder = operand_decoder_def->decoder;
	operand_decoding->size_calculator = operand_decoder_def->size_calculator;

	if( operand_decoder_def->hints_calculator ) {
		fcml_st_hts_calculated_hints hints = operand_decoder_def->hints_calculator( addr_mode_desc, decoded_addr_mode );
		operand_decoding->hints |= hints.operand_hints;
		*instruction_hints |= hints.instruction_hints;
	}

	return error;
}


/*********************
 * Prefixes.
 *********************/

fcml_st_dasm_instruction_prefix* fcml_ifn_dasm_get_prefix_by_type( fcml_ist_dasm_decoding_context *context, fcml_st_dasm_prefix_types prefix_type ) {
	fcml_st_dasm_instruction_prefix* prefix = NULL;
	fcml_st_dasm_prefixes *prefixes = &(context->prefixes);
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

fcml_st_dasm_instruction_prefix* fcml_ifn_dasm_get_prefix_if_available( fcml_ist_dasm_decoding_context *context, fcml_uint8_t prefix_value ) {
	fcml_st_dasm_instruction_prefix* prefix = NULL;
	fcml_st_dasm_prefixes *prefixes = &(context->prefixes);
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

fcml_bool fcml_ifn_dasm_is_prefix_available( fcml_ist_dasm_decoding_context *context, uint8_t prefix, fcml_bool mandatory ) {
	fcml_st_dasm_prefixes *prefixes = &(context->prefixes);
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
	fcml_st_dasm_instruction_prefix *found_prefix = fcml_ifn_dasm_get_prefix_if_available( context, prefix );
	return mandatory ? ( found_prefix != NULL && found_prefix->mandatory_prefix ) : ( found_prefix != NULL );
}

void fcml_ifn_dasm_clear_mandatory_flag( fcml_ist_dasm_decoding_context *context, uint8_t prefix_code ) {
	fcml_st_dasm_instruction_prefix *prefix = fcml_ifn_dasm_get_prefix_if_available( context, prefix_code );
	if( prefix ) {
		prefix->mandatory_prefix = FCML_FALSE;
	}
}

/******************************
 * Effective attributes sizes.
 ******************************/

fcml_data_size fcml_ifn_dasm_calculate_effective_asa( fcml_ist_dasm_decoding_context *context ) {

	fcml_st_dasm_disassembler_context *disassembler_context = context->disassembler_context;
	fcml_data_size effective_asa = disassembler_context->address_size_attribute;

	// Checks if address size attribute is overridden.
	if( fcml_ifn_dasm_is_prefix_available( context, 0x67, FCML_FALSE ) ) {
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

fcml_data_size fcml_ifn_dasm_calculate_effective_osa( fcml_ist_dasm_decoding_context *context, fcml_uint32_t opcode_flags ) {

	fcml_st_dasm_instruction_prefix *prefix;

	fcml_st_dasm_disassembler_context *disassembler_context = context->disassembler_context;
	fcml_st_dasm_prefixes *prefixes = &(context->prefixes);
	fcml_data_size osa = disassembler_context->operand_size_attribute;

	// Gets effective address-size attribute for used mode.
	switch( disassembler_context->addr_form ) {
	case FCML_AF_16_BIT:
	case FCML_AF_32_BIT:
		// In 16 and 32 bit mode only prefixes can change address-size attribute.
		prefix = fcml_ifn_dasm_get_prefix_if_available( context, 0x66 );
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
				prefix = fcml_ifn_dasm_get_prefix_if_available( context, 0x66 );
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

typedef fcml_ifp_dasm_instruction_acceptor (*fcml_ifp_dasm_instruction_acceptor_factory)( fcml_st_def_addr_mode_desc *addr_mode_desc );

// ---------
// Prefixes.
// ---------

fcml_bool fcml_ifn_dasm_instruction_acceptor_prefixes( fcml_ist_dasm_decoding_context *context, fcml_ist_dasm_instruction_decoding_def *instruction_decoding_def ) {

	// Prefixes.
	fcml_st_dasm_prefixes *prefixes = &(context->prefixes);

	// LOCK prefix.
	if( prefixes->is_lock && !FCML_DEF_PREFIX_LOCK_ALLOWED( instruction_decoding_def->prefixes_flags ) ) {
		// Lock prefix is not allowed.
		return FCML_FALSE;
	}

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
	if( ( FCML_DEF_PREFIX_L_1( instruction_decoding_def->prefixes_flags ) && ( !( prefixes->is_vex || prefixes->is_xop ) || !prefixes->l ) ) ||
		( FCML_DEF_PREFIX_L_0( instruction_decoding_def->prefixes_flags ) && ( !( prefixes->is_vex || prefixes->is_xop ) || prefixes->l ) ) ) {
		return FCML_FALSE;
	}

	// Mandatory prefixes.

	fcml_bool found = FCML_FALSE;
	if( FCML_DEF_PREFIX_MANDATORY_66( instruction_decoding_def->prefixes_flags ) ) {
		found = fcml_ifn_dasm_is_prefix_available(context, 0x66, FCML_TRUE);
	} else if( FCML_DEF_PREFIX_MANDATORY_F2( instruction_decoding_def->prefixes_flags ) ) {
		found = fcml_ifn_dasm_is_prefix_available(context, 0xF2, FCML_TRUE);
	} else if( FCML_DEF_PREFIX_MANDATORY_F3( instruction_decoding_def->prefixes_flags ) ) {
		found = fcml_ifn_dasm_is_prefix_available(context, 0xF3, FCML_TRUE);
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

fcml_ifp_dasm_instruction_acceptor fcml_ifn_dasm_instruction_acceptor_factory_prefixes( fcml_st_def_addr_mode_desc *addr_mode_desc ) {
	return fcml_ifn_dasm_instruction_acceptor_prefixes;
}

// ---------
// ModRM.
// ---------

fcml_bool fcml_ifn_dasm_instruction_acceptor_modrm( fcml_ist_dasm_decoding_context *context, fcml_ist_dasm_instruction_decoding_def *instruction_decoding_def ) {

	fcml_uint32_t opcode_flags = instruction_decoding_def->opcode_flags;
	fcml_st_memory_stream *code = context->stream;
	fcml_st_dasm_prefixes *prefixes = &(context->prefixes);

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

fcml_ifp_dasm_instruction_acceptor fcml_ifn_dasm_instruction_acceptor_factory_modrm( fcml_st_def_addr_mode_desc *addr_mode_desc ) {
	return fcml_ifn_dasm_instruction_acceptor_modrm;
}

// ----------------
// Size attributes.
// ----------------

fcml_bool fcml_ifn_dasm_instruction_acceptor_size_attributes_restrictions( fcml_ist_dasm_decoding_context *context, fcml_ist_dasm_instruction_decoding_def *instruction_decoding_def ) {

	// Check EOSA. These fields allow us to restrict instruction decoding only
	// to specific effective operand sizes. For instance we can define instruction
	// that can be chosen only if EOSA is equal to 16.
	if( FCML_DEF_OPCODE_FLAGS_IS_EOSA_RESTRICTION( instruction_decoding_def->opcode_flags ) ) {
		fcml_bool mandatory_prefix = FCML_FALSE;
		// Ignore 0x66 prefix if this instruction uses it as mandatory prefix. This correction is also
		// done in the next phase for already chosen instruction.
		fcml_st_dasm_instruction_prefix *prefix = fcml_ifn_dasm_get_prefix_if_available( context, 0x66 );
		// Set this prefix as a mandatory one if this instruction defines 66 as mandatory.
		// This is set temporarily, only to calculate correct EOSA for instruction.
		if( prefix != NULL ) {
			mandatory_prefix = prefix->mandatory_prefix;
			prefix->mandatory_prefix = FCML_DEF_PREFIX_MANDATORY_66( instruction_decoding_def->prefixes_flags );
		}
		fcml_data_size eosa = fcml_ifn_dasm_calculate_effective_osa( context, instruction_decoding_def->opcode_flags );
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
		fcml_data_size easa = fcml_ifn_dasm_calculate_effective_asa( context );
		if( !( ( FCML_DEF_OPCODE_FLAGS_EASA_16( instruction_decoding_def->opcode_flags ) && easa == FCML_DS_16 ) ||
			( FCML_DEF_OPCODE_FLAGS_EASA_32( instruction_decoding_def->opcode_flags ) && easa == FCML_DS_32 ) ||
			( FCML_DEF_OPCODE_FLAGS_EASA_64( instruction_decoding_def->opcode_flags ) && easa == FCML_DS_64 ) ) ) {
			// Wrong EASA, ignore instruction.
			return FCML_FALSE;
		}
	}

	return FCML_TRUE;
}

fcml_ifp_dasm_instruction_acceptor fcml_ifn_dasm_instruction_acceptor_factory_size_attributes_restrictions( fcml_st_def_addr_mode_desc *addr_mode_desc ) {
	return fcml_ifn_dasm_instruction_acceptor_size_attributes_restrictions;
}

// ----------------
// Addressing mode.
// ----------------

fcml_bool fcml_ifn_dasm_instruction_acceptor_addr_mode( fcml_ist_dasm_decoding_context *context, fcml_ist_dasm_instruction_decoding_def *instruction_decoding_def ) {

	fcml_st_dasm_disassembler_context *disassembler_context = context->disassembler_context;

	fcml_en_addr_form addr_form = disassembler_context->addr_form;

	return ( ( addr_form == FCML_AF_16_BIT || addr_form == FCML_AF_32_BIT ) && FCML_DEF_OPCODE_FLAGS_16_32_BIT_MODE_SUPPORTED( instruction_decoding_def->opcode_flags ) )
				|| ( addr_form == FCML_AF_64_BIT && FCML_DEF_OPCODE_FLAGS_64_BIT_MODE_SUPPORTED( instruction_decoding_def->opcode_flags ) );
}

fcml_ifp_dasm_instruction_acceptor fcml_ifn_dasm_instruction_acceptor_factory_addr_mode( fcml_st_def_addr_mode_desc *addr_mode_desc ) {
	return fcml_ifn_dasm_instruction_acceptor_addr_mode;
}

fcml_ifp_dasm_instruction_acceptor_factory fcml_iarr_dasm_dts_acceptor_factories[] = {
	fcml_ifn_dasm_instruction_acceptor_factory_prefixes,
	fcml_ifn_dasm_instruction_acceptor_factory_addr_mode,
	fcml_ifn_dasm_instruction_acceptor_factory_modrm,
	fcml_ifn_dasm_instruction_acceptor_factory_size_attributes_restrictions,
	NULL
};

void fcml_ifn_dasm_dts_free_acceptors_chain( fcml_ist_dasm_addr_mode_acceptor_chain *chain ) {
	if( !chain ) {
		return;
	}
	if( chain->next ) {
		fcml_ifn_dasm_dts_free_acceptors_chain( chain->next );
	}
	fcml_fn_env_memory_free( chain );
}

fcml_ceh_error fcml_ifn_dasm_dts_allocate_acceptors_chain( fcml_st_def_addr_mode_desc *addr_mode_desc, fcml_ist_dasm_addr_mode_acceptor_chain **chain ) {

	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

	fcml_ist_dasm_addr_mode_acceptor_chain *current = NULL, *chain_root = NULL;

	fcml_ifp_dasm_instruction_acceptor_factory *factory = &(fcml_iarr_dasm_dts_acceptor_factories[0]);

	while( *factory ) {
		fcml_ifp_dasm_instruction_acceptor acceptor = (*factory)( addr_mode_desc );
		if( acceptor ) {
			fcml_ist_dasm_addr_mode_acceptor_chain *chain_element = fcml_fn_env_memory_alloc_clear( sizeof( fcml_ist_dasm_addr_mode_acceptor_chain* ) );
			if( !chain_element ) {
				// Free already allocated chain.
				if( chain_root ) {
					fcml_ifn_dasm_dts_free_acceptors_chain( chain_root );
				}
				return FCML_CEH_GEC_OUT_OF_MEMORY;
			}
			chain_element->acceptor = acceptor;
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

void fcml_ifn_dasm_dts_dispose_instruction_decoding_callback_default( fcml_st_dialect_context *dialect, fcml_ptr decoding_ptr ) {

	fcml_ist_dasm_instruction_decoding_def *decoding = (fcml_ist_dasm_instruction_decoding_def *)decoding_ptr;

	if( decoding->mnemonics ) {
		fcml_fn_mp_free_mnemonics( decoding->mnemonics );
	}

	int i;
	for( i = 0; i < FCML_OPERANDS_COUNT; i++ ) {
		fcml_ifn_dasm_dts_free_operand_decoding( &(decoding->operand_decodings[i]) );
	}

	fcml_ifn_dasm_dts_free_acceptors_chain( decoding->instruction_acceptors_chain );

	fcml_fn_env_memory_free( decoding );
}

void fcml_ifn_dasm_dts_prepare_modrm_decoding_details( fcml_st_def_decoded_addr_mode *decoded_addr_mode, fcml_ist_dasm_modrm_decoding_details *modrm_details ) {
	if( decoded_addr_mode != NULL && decoded_addr_mode->addr_mode == ( FCML_OP_VSIB_BASE >> 24 ) ) {
		fcml_sf_def_tma_rm *rm_args = (fcml_sf_def_tma_rm *)decoded_addr_mode->addr_mode_args;
		modrm_details->is_vsib = FCML_TRUE;
		modrm_details->vsib_index_size = ( rm_args->vector_index_register ) == FCML_VSIB_XMM ? FCML_DS_128 : FCML_DS_256;
	}
}

fcml_ceh_error fcml_ifn_dasm_dts_prepare_instruction_decoding_callback_default( fcml_st_dialect_context *dialect, fcml_st_dt_diss_tree_element *element, fcml_st_def_instruction_desc *instruction_desc, fcml_st_def_addr_mode_desc *addr_mode_desc ) {

	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

	// Prepare instruction decoding structure.
	fcml_ist_dasm_instruction_decoding_def *decoding = fcml_fn_env_memory_alloc_clear( sizeof( fcml_ist_dasm_instruction_decoding_def ) );
	if( !decoding ) {
		return FCML_CEH_GEC_OUT_OF_MEMORY;
	}

	// Copy opcodes.
	int i;
	for( i = 0; i < sizeof( addr_mode_desc->opcode ); i++ ) {
		decoding->opcodes[i] = addr_mode_desc->opcode[i];
	}

	error = dialect->get_parsed_mnemonics( instruction_desc, addr_mode_desc, &(decoding->mnemonics) );
	if( error ) {
		fcml_fn_env_memory_free( decoding );
	    return FCML_CEH_GEC_INVALID_INPUT;
	}

	// Copy flags.
	decoding->prefixes_flags = addr_mode_desc->allowed_prefixes;
	decoding->opcode_flags = addr_mode_desc->opcode_flags;
	decoding->instruction = instruction_desc->instruction;

	error = fcml_ifn_dasm_dts_allocate_acceptors_chain( addr_mode_desc, &(decoding->instruction_acceptors_chain) );
	if( error ) {
		fcml_fn_mp_free_mnemonics( decoding->mnemonics );
		fcml_fn_env_memory_free( decoding );
		return error;
	}

	// Choose function used to disassemble instruction.
	decoding->instruction_decoder = fcml_ifn_dasm_dts_choose_instruction_decoder( instruction_desc->instruction_type );

	// Clear instruction level hints. Just to be sure.
	decoding->hints = 0;

	// Prepare operand decoders.
	for( i = 0; i < FCML_OPERANDS_COUNT; i++ ) {
		error = fcml_ifn_dasm_dts_prepare_operand_decoding( addr_mode_desc, &(decoding->operand_decodings[i]), addr_mode_desc->opperands[i], &(decoding->hints) );
		if( !error ) {
			fcml_ifn_dasm_dts_prepare_modrm_decoding_details( decoding->operand_decodings[i].decoded_addr_mode, &(decoding->modrm_details) );
		} else {
			fcml_ifn_dasm_dts_free_acceptors_chain( decoding->instruction_acceptors_chain );
			fcml_fn_mp_free_mnemonics( decoding->mnemonics );
			fcml_fn_env_memory_free( decoding );
			return error;
		}
	}

	// Insert it in appropriate order.
	int order = fcml_ifn_dasm_dts_calculate_decoding_order( decoding );

	decoding->order = order;

	fcml_st_coll_list *instruction_decoding_defs = element->instruction_decoding_defs;
	fcml_st_coll_list_element *current = instruction_decoding_defs->head;

	// Insert prepared instruction decoding in appropriate order.
	fcml_st_coll_list_element *prev = NULL;
	while( current ) {
		fcml_ist_dasm_instruction_decoding_def *decoding_def = (fcml_ist_dasm_instruction_decoding_def*)current->item;
		if( decoding_def && decoding_def->order < order ) {
			break;
		}
		prev = current;
		current = current->next;
	}

	if( !fcml_fn_coll_list_insert( instruction_decoding_defs, prev, decoding ) ) {
		fcml_ifn_dasm_dts_free_acceptors_chain( decoding->instruction_acceptors_chain );
		fcml_fn_mp_free_mnemonics( decoding->mnemonics );
		fcml_fn_env_memory_free( decoding );
		error = FCML_CEH_GEC_OUT_OF_MEMORY;
	}

	return error;
}

/*****************************
 * Opcode iterator.
 *****************************/

fcml_uint8_t fcml_iarr_dasm_escape_0f[] = { 0x0F };
fcml_uint8_t fcml_iarr_dasm_escape_0f38[] = { 0x0F, 0x38 };
fcml_uint8_t fcml_iarr_dasm_escape_0f3A[] = { 0x0F, 0x3A };

fcml_uint8_t *fcml_iarr_dasm_escape_opcode_table[3] = { fcml_iarr_dasm_escape_0f, fcml_iarr_dasm_escape_0f38, fcml_iarr_dasm_escape_0f3A };
fcml_uint8_t fcml_iarr_dasm_escape_size_tablee_table[] = { 1, 2, 2 };

struct fcml_ist_dasm_opcode_iterator;

typedef struct fcml_ist_dasm_opcode_iterator_impl {
	fcml_st_memory_stream stream;
	fcml_uint8_t is_virtual_opcode;
	fcml_uint8_t *virtual_opcode;
	fcml_int virtual_opcode_count;
	fcml_int virtual_opcode_offset;
} fcml_ist_dasm_opcode_iterator_impl;

fcml_int fcml_ifn_dasm_decode_escape_opcode_bytes( fcml_ist_dasm_decoding_context *decoding_context, fcml_uint8_t **virtual_opcode ) {
	fcml_st_dasm_prefixes *prefixes_fields = &(decoding_context->prefixes);
	fcml_int8_t size = 0;
	if( prefixes_fields->is_vex || prefixes_fields->is_xop ) {
		if( prefixes_fields->vex_xop_first_byte == 0xC4 ) {
			int index = prefixes_fields->mmmm - 1;
			*virtual_opcode = fcml_iarr_dasm_escape_opcode_table[index];
			size = fcml_iarr_dasm_escape_size_tablee_table[index];
		} else if( prefixes_fields->vex_xop_first_byte == 0x8F ) {
			*virtual_opcode = &(prefixes_fields->mmmm);
			size = 1;
		} else {
			*virtual_opcode = fcml_iarr_dasm_escape_0f;
			size = 1;
		}
	}
	return size;
}

fcml_ceh_error fcml_ifn_dasm_prepare_opcode_iterator( fcml_ist_dasm_decoding_context *decoding_context, struct fcml_ist_dasm_opcode_iterator **iterator_ptr ) {
	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
	fcml_ist_dasm_opcode_iterator_impl *iterator = (fcml_ist_dasm_opcode_iterator_impl*)fcml_fn_env_memory_alloc_clear( sizeof( fcml_ist_dasm_opcode_iterator_impl ) );
	if( iterator ) {
		// Prepare virtual opcodes.
		iterator->virtual_opcode_count = fcml_ifn_dasm_decode_escape_opcode_bytes( decoding_context, &(iterator->virtual_opcode) );
		iterator->virtual_opcode_offset = 0;
		iterator->stream = *decoding_context->stream;
		iterator->is_virtual_opcode = FCML_FALSE;
		// Prepare virtual opcodes.
		*iterator_ptr = (struct fcml_ist_dasm_opcode_iterator *)iterator;
	} else {
		error = FCML_CEH_GEC_OUT_OF_MEMORY;
	}
	return error;
}

fcml_bool fcml_ifn_dasm_opcode_iterator_has_next( struct fcml_ist_dasm_opcode_iterator *iterator_ptr ) {
	fcml_ist_dasm_opcode_iterator_impl *iterator = (fcml_ist_dasm_opcode_iterator_impl *)iterator_ptr;
	if( iterator->virtual_opcode_count > 0 && iterator->virtual_opcode_offset < iterator->virtual_opcode_count ) {
		// Virtual byte is available.
		return FCML_TRUE;
	} else if( fcml_fn_stream_size( &(iterator->stream) ) > 0 ) {
		return FCML_TRUE;
	}
	return FCML_FALSE;
}

fcml_bool fcml_ifn_dasm_opcode_iterator_is_virtual_opcode( struct fcml_ist_dasm_opcode_iterator *iterator_ptr ) {
	fcml_ist_dasm_opcode_iterator_impl *iterator = (fcml_ist_dasm_opcode_iterator_impl *)iterator_ptr;
	return iterator->is_virtual_opcode;
}

fcml_uint8_t fcml_ifn_dasm_opcode_iterator_next( struct fcml_ist_dasm_opcode_iterator *iterator_ptr ) {
	fcml_ist_dasm_opcode_iterator_impl *iterator = (fcml_ist_dasm_opcode_iterator_impl *)iterator_ptr;
	if( iterator->virtual_opcode_count > 0 && iterator->virtual_opcode_offset < iterator->virtual_opcode_count ) {
		iterator->is_virtual_opcode = FCML_TRUE;
		return iterator->virtual_opcode[ iterator->virtual_opcode_offset++ ];
	} else {
		fcml_bool result;
		fcml_uint8_t opcode_byte = fcml_fn_stream_read( &(iterator->stream), &result );
		if( result ) {
			iterator->is_virtual_opcode = FCML_FALSE;
		}
		return opcode_byte;
	}
	return FCML_FALSE;
}

void fcml_ifn_dasm_opcode_iterator_free( struct fcml_ist_dasm_opcode_iterator *iterator_ptr ) {
	if( iterator_ptr ) {
		fcml_fn_env_memory_free( iterator_ptr );
	}
}

/************************************
 * Instructions decoding.
 ************************************/

void fcml_ifn_dasm_decode_opcode_fields( fcml_ist_dasm_decoding_context *decoding_context, fcml_ist_dasm_instruction_decoding_def *instruction_decoding_def, fcml_uint8_t primary_opcode_byte ) {

	// TTTN.
	if( FCML_DEF_OPCODE_FLAGS_OPCODE_FIELD_TTTN( instruction_decoding_def->opcode_flags ) ) {
		fcml_uint8_t condition = primary_opcode_byte & 0x0F;
		decoding_context->is_conditional = FCML_TRUE;
		decoding_context->condition.condition_type = ( condition >> 1 );
		decoding_context->condition.is_negation = primary_opcode_byte & 0x01;
	} else {
		decoding_context->is_conditional = FCML_FALSE;
	}

	// W.
	if( FCML_DEF_OPCODE_FLAGS_OPCODE_FIELD_W( instruction_decoding_def->opcode_flags ) ) {
		decoding_context->opcode_field_w_bit = primary_opcode_byte & 0x01;
	}

	// S.
	if( FCML_DEF_OPCODE_FLAGS_OPCODE_FIELD_S( instruction_decoding_def->opcode_flags ) ) {
		decoding_context->opcode_field_s_bit = primary_opcode_byte & 0x02;
	}
}

fcml_ceh_error fcml_ifn_dasm_instruction_decoder_IA( fcml_ist_dasm_decoding_context *decoding_context, fcml_ist_dasm_instruction_decoding_def *instruction_decoding_def ) {

	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

	// Instruction hints.

	decoding_context->instruction_hints = instruction_decoding_def->hints;

	// Change prefixes to mandatory one if needed.

	if( !FCML_DEF_PREFIX_MANDATORY_66( instruction_decoding_def->prefixes_flags ) ) {
		fcml_ifn_dasm_clear_mandatory_flag( decoding_context, 0x66 );
	}

	if( !FCML_DEF_PREFIX_MANDATORY_F2( instruction_decoding_def->prefixes_flags ) ) {
		fcml_ifn_dasm_clear_mandatory_flag( decoding_context, 0xF2 );
	} else {
		decoding_context->prefixes.is_repne = FCML_FALSE;
	}

	if( !FCML_DEF_PREFIX_MANDATORY_F3( instruction_decoding_def->prefixes_flags ) ) {
		fcml_ifn_dasm_clear_mandatory_flag( decoding_context, 0xF3 );
	} else {
		decoding_context->prefixes.is_rep = FCML_FALSE;
	}

	// Branches.
	if( instruction_decoding_def->instruction != F_JCC ) {
		decoding_context->prefixes.is_branch = FCML_FALSE;
		decoding_context->prefixes.is_nobranch = FCML_FALSE;
	}

	// Change REP/REPNE prefixes to XACQUIRE/XRELEASE if instruction support them.
	if( FCML_DEF_PREFIX_HLE_ENABLED( instruction_decoding_def->prefixes_flags ) ) {
		if( decoding_context->prefixes.is_rep ) {
			decoding_context->prefixes.is_xrelease = FCML_TRUE;
			decoding_context->prefixes.is_rep = FCML_FALSE;
		}
		if( decoding_context->prefixes.is_repne ) {
			decoding_context->prefixes.is_xacquire = FCML_TRUE;
			decoding_context->prefixes.is_repne = FCML_FALSE;
		}
	}

	decoding_context->calculated_instruction_size = decoding_context->prefixes.prefixes_bytes_count + decoding_context->opcodes_count;

	// Calculates effective operand sizes. It's not important if they will be used or not.
	decoding_context->effective_address_size_attribute = fcml_ifn_dasm_calculate_effective_asa( decoding_context );
	decoding_context->effective_operand_size_attribute = fcml_ifn_dasm_calculate_effective_osa( decoding_context, instruction_decoding_def->opcode_flags );

	fcml_ist_dasm_operand_wrapper *operand_wrappers = &(decoding_context->operand_wrappers[0]);
	fcml_ist_dasm_modrm_decoding_details *modrm_details = &(instruction_decoding_def->modrm_details);
	fcml_st_dasm_prefixes *prefixes = &(decoding_context->prefixes);

	// Decode ModRM field if there is any.

	if( FCML_DEF_OPCODE_FLAGS_OPCODE_IS_MODRM( instruction_decoding_def->opcode_flags ) ) {

		fcml_st_memory_stream *stream = decoding_context->stream;

		fcml_uint32_t offset = stream->offset;

		fcml_st_modrm_decoder_context modrm_context;
		modrm_context.addr_form = decoding_context->disassembler_context->addr_form;
		modrm_context.effective_address_size = decoding_context->effective_address_size_attribute;

		fcml_st_modrm_source modrm_source;
		modrm_source.is_vsib = modrm_details->is_vsib;
		modrm_source.vsib_index_size = modrm_details->vsib_index_size;
		modrm_source.ext_b = prefixes->b;
		modrm_source.ext_r = prefixes->r;
		modrm_source.ext_x = prefixes->x;
		modrm_source.stream = decoding_context->stream;

		fcml_uint8_t flags = 0;
		if( decoding_context->disassembler_context->configuration.extend_displacement_to_asa ) {
			flags |= FCML_MODRM_DEC_FLAG_EXTEND_DISPLACEMENT_TO_ASA;
		}

		error = fcml_fn_modrm_decode( &modrm_context, &modrm_source, &(decoding_context->decoded_modrm), &(decoding_context->decoded_modrm_details), flags );
		if( error ) {
			return error;
		}

		decoding_context->calculated_instruction_size += stream->offset - offset;

	}

	// Calculate operands size.
	fcml_int i, operands_size = 0;
	for( i = 0; i < FCML_OPERANDS_COUNT; i++ ) {
		fcml_ist_dasm_operand_decoding *operand_decoding = &(instruction_decoding_def->operand_decodings[i]);
		fcml_st_def_decoded_addr_mode *decoded_addr_mode = operand_decoding->decoded_addr_mode;
		if( operand_decoding->size_calculator ) {
			operands_size += operand_decoding->size_calculator( decoding_context, decoded_addr_mode->addr_mode_args );
		}
	}

	decoding_context->calculated_instruction_size += operands_size;
	decoding_context->mnemonics = instruction_decoding_def->mnemonics;

	// Store primary opcode byte.
	fcml_int opcode_num = FCML_DEF_OPCODE_FLAGS_PRIMARY_OPCODE( instruction_decoding_def->opcode_flags );
	decoding_context->primary_opcode_byte = decoding_context->opcodes[ opcode_num - decoding_context->virtual_opcodes_count ];

	// Decode opcode fields.
	fcml_ifn_dasm_decode_opcode_fields( decoding_context, instruction_decoding_def, decoding_context->primary_opcode_byte );

	// Decode operands.
	for( i = 0; i < FCML_OPERANDS_COUNT; i++ ) {
		fcml_ist_dasm_operand_decoding *operand_decoding = &(instruction_decoding_def->operand_decodings[i]);
		fcml_st_def_decoded_addr_mode *decoded_addr_mode = operand_decoding->decoded_addr_mode;
		if( operand_decoding->decoder ) {
			error = operand_decoding->decoder( decoding_context, operand_wrappers, decoded_addr_mode->addr_mode_args );
			if( error ) {
				break;
			}
			operand_wrappers->operand.hints |= operand_decoding->hints;
			operand_wrappers->access_mode = decoded_addr_mode->access_mode;
			operand_wrappers++;
		} else {
			// First operand without decoder is the last one.
			break;
		}
	}

	return error;
}

fcml_ceh_error fcml_ifn_dasm_decode_instruction( fcml_ist_dasm_decoding_context *context ) {

	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

	fcml_ist_dasm_disassembler *disassembler = (fcml_ist_dasm_disassembler *)context->disassembler_context->disassembler;

	fcml_st_dt_decoding_tree *decoding_tree = disassembler->decoding_tree;

	// Prepare opcode iterator.
	struct fcml_ist_dasm_opcode_iterator *iterator;
	error = fcml_ifn_dasm_prepare_opcode_iterator( context, &iterator );
	if( error ) {
		return error;
	}

	struct fcml_st_dt_diss_tree_element **opcodes = &(decoding_tree->opcode[0]);

	// Found instruction addressing modes going here.
	fcml_st_dt_diss_tree_element* tree_element = NULL;

	while( fcml_ifn_dasm_opcode_iterator_has_next( iterator ) ) {

		// Get next instructions opcode.
		fcml_uint8_t opcode_byte = fcml_ifn_dasm_opcode_iterator_next( iterator );

		// Get instruction for given opcode.
		fcml_st_dt_diss_tree_element *current = opcodes[opcode_byte];

		if( current ) {
			// There is something for given opcode byte, so save it.
			tree_element = current;
			// Store all non virtual opcode bytes inside context.
			if( !fcml_ifn_dasm_opcode_iterator_is_virtual_opcode( iterator ) ) {
				context->opcodes[context->opcodes_count++] = opcode_byte;
			} else {
				context->virtual_opcodes_count++;
			}
			opcodes = &(tree_element->opcodes[0]);
		} else {
			break;
		}

	}

	// Free opcode iterator.
	fcml_ifn_dasm_opcode_iterator_free( iterator );

	// Skip opcode bytes.
	fcml_fn_stream_seek( context->stream, context->opcodes_count, FCML_EN_ST_CURRENT );

	fcml_bool found = FCML_FALSE;

	// Disassemble instruction using most appropriate addressing mode from disassemblation tree.
	if( tree_element ) {

		fcml_st_coll_list_element *current = tree_element->instruction_decoding_defs->head;
		while( current ) {
			fcml_ist_dasm_instruction_decoding_def *decoding_def = (fcml_ist_dasm_instruction_decoding_def*)current->item;
			if( decoding_def ) {
				// Try to accept this addressing mode.
				fcml_bool accept = FCML_TRUE;
				fcml_ist_dasm_addr_mode_acceptor_chain *chain = decoding_def->instruction_acceptors_chain;
				while( chain ) {
					if( chain->acceptor && !chain->acceptor( context, decoding_def ) ) {
						accept = FCML_FALSE;
						break;
					}
					chain = chain->next;
				}
				if( accept ) {
					error = decoding_def->instruction_decoder( context, decoding_def );
					if( !error ) {
						found = FCML_TRUE;
						break;
					}
				}
			}
			current = current->next;
		}

	} else {
		// Unknown instruction.
		error = FCML_EN_UNKNOWN_INSTRUCTION;
	}

	if( !found ) {
		error = FCML_EN_UNKNOWN_INSTRUCTION;
	}

	return error;
}

/**************************
 * Input validation
 **************************/

fcml_ceh_error fcml_ifn_dasm_validate_and_prepare_context( fcml_st_dasm_disassembler_context *context ) {

	/* Mode has to be set. */
    if( context->addr_form != FCML_AF_16_BIT && context->addr_form != FCML_AF_32_BIT && context->addr_form != FCML_AF_64_BIT ) {
        return FCML_EN_UNSUPPORTED_ADDRESSING_FORM;
    }

    /* 16 bit address size attribute is not supported in 64bit mode. */
    if( context->addr_form == FCML_AF_64_BIT && context->address_size_attribute == FCML_DS_16 ) {
        return FCML_EN_UNSUPPORTED_ADDRESS_SIZE;
    }

    /* Check if attributes are valid and set them to default values. */
    if( !context->address_size_attribute ) {
        switch( context->addr_form ) {
		case FCML_AF_16_BIT:
			context->address_size_attribute = FCML_DS_16;
			break;
		case FCML_AF_32_BIT:
			context->address_size_attribute = FCML_DS_32;
			break;
		case FCML_AF_64_BIT:
			context->address_size_attribute = FCML_DS_64;
			break;
        }
    }

    if( !context->operand_size_attribute ) {
        switch( context->addr_form ) {
		case FCML_AF_16_BIT:
			context->operand_size_attribute = FCML_DS_16;
			break;
		case FCML_AF_32_BIT:
			context->operand_size_attribute = FCML_DS_32;
			break;
		case FCML_AF_64_BIT:
			context->operand_size_attribute = FCML_DS_32;
			break;
        }
    }

    // Check if ASA is value.
    fcml_data_size asa = context->address_size_attribute;
    if( asa != FCML_DS_16 && asa != FCML_DS_32 && asa != FCML_DS_64 ) {
		return FCML_EN_UNSUPPORTED_ADDRESS_SIZE;
	}

    // Check if OSA is value.
    fcml_data_size osa = context->operand_size_attribute;
    if( osa != FCML_DS_16 && osa != FCML_DS_32 && osa != FCML_DS_64 ) {
   		return FCML_EN_UNSUPPORTED_OPPERAND_SIZE;
   	}

    return FCML_CEH_GEC_NO_ERROR;
}

/****************************
 * Prefixes decoding.
 ****************************/

fcml_ceh_error fcml_ifn_dasm_decode_prefixes( fcml_ist_dasm_decoding_context *decoding_context) {

	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

	fcml_st_dasm_prefixes *prefixes = &(decoding_context->prefixes);
	fcml_st_memory_stream *stream = decoding_context->stream;
	fcml_en_addr_form addr_form = decoding_context->disassembler_context->addr_form;
	fcml_st_dasm_prefixes *prefixes_details = &(decoding_context->prefixes);

	fcml_bool result = FCML_FALSE;
	fcml_int prefix_index = 0, prefix_size, xop_vex_prefix_size = 0;
	fcml_st_dasm_prefix_types prefix_type;
	fcml_bool is_mandatory_candidate, is_xop_vex_allowed = FCML_TRUE, is_last_prefix = FCML_FALSE;
	fcml_bool is_vex, is_xop, is_lock, is_rep_xrelease, is_repne_xacquire, is_branch, is_nobranch;

	do {
		prefix_type = FCML_PT_GROUP_UNKNOWN;
		is_mandatory_candidate = FCML_FALSE;
		is_lock = FCML_FALSE;
		is_rep_xrelease = FCML_FALSE;
		is_repne_xacquire = FCML_FALSE;
		is_vex = FCML_FALSE;
		is_xop = FCML_FALSE;
		is_branch = FCML_FALSE;
		is_nobranch = FCML_FALSE;
		// Almost all prefixes are one byte length, so it's a reasonable default here.
		prefix_size = 1;
		fcml_uint8_t prefix = fcml_fn_stream_peek(stream, &result);
		if( result ) {
			fcml_st_dasm_instruction_prefix *prefix_details = &(prefixes->prefixes[prefix_index]);
			switch(prefix) {
				case 0xF0:
					prefix_type = FCML_PT_GROUP_1;
					is_xop_vex_allowed = FCML_FALSE;
					is_lock = FCML_TRUE;
					break;
				case 0xF2:
					is_repne_xacquire = FCML_TRUE;
					is_mandatory_candidate = FCML_TRUE;
					prefix_type = FCML_PT_GROUP_1;
					is_xop_vex_allowed = FCML_FALSE;
					break;
				case 0xF3:
					is_rep_xrelease = FCML_TRUE;
					is_mandatory_candidate = FCML_TRUE;
					prefix_type = FCML_PT_GROUP_1;
					is_xop_vex_allowed = FCML_FALSE;
					break;
				case 0x2E:
					is_nobranch = FCML_TRUE;
					prefix_type = FCML_PT_GROUP_2;
					break;
				case 0x3E:
					is_branch = FCML_TRUE;
					prefix_type = FCML_PT_GROUP_2;
					break;
				case 0x26:
				case 0x36:
				case 0x64:
				case 0x65:
					prefix_type = FCML_PT_GROUP_2;
					break;
				break;
				case 0x66:
					is_mandatory_candidate = FCML_TRUE;
					prefix_type = FCML_PT_GROUP_3;
					is_xop_vex_allowed = FCML_FALSE;
					break;
				case 0x67:
					prefix_type = FCML_PT_GROUP_4;
					break;
				case 0xC5:
					xop_vex_prefix_size = 1;
					prefix_type = FCML_PT_VEX;
					is_vex = FCML_TRUE;
					is_last_prefix = FCML_TRUE;
					break;
				case 0x8F:
					xop_vex_prefix_size = 2;
					prefix_type = FCML_PT_XOP;
					is_xop = FCML_TRUE;
					is_last_prefix = FCML_TRUE;
					break;
				case 0xC4:
					xop_vex_prefix_size = 2;
					prefix_type = FCML_PT_VEX;
					is_vex = FCML_TRUE;
					is_last_prefix = FCML_TRUE;
					break;
				default:
					// REX prefix is the last one, so we have to break this loop after finding one.
					if( addr_form == FCML_AF_64_BIT && prefix >= 0x40 && prefix <= 0x4F ) {
						// REX prefix found.
						prefix_type = FCML_PT_REX;
						// Decode fields.
						prefixes_details->is_rex = FCML_TRUE;
						prefixes_details->w = FCML_REX_W(prefix);
						prefixes_details->r = FCML_REX_R(prefix);
						prefixes_details->x = FCML_REX_X(prefix);
						prefixes_details->b = FCML_REX_B(prefix);
						// REX can not be used together with the VEX at the moment.
						is_xop_vex_allowed = FCML_TRUE;
						is_last_prefix = FCML_TRUE;
					}
				break;
			}

			// Handle VEX/XOP prefixes.
			if( prefix_type == FCML_PT_VEX || prefix_type == FCML_PT_XOP ) {

				if( is_xop_vex_allowed ) {

					fcml_stream_pointer sp = fcml_fn_stream_save_point( stream );

					// Skip to the second byte of VEX prefix.
					fcml_fn_stream_seek(stream, 1, FCML_EN_ST_CURRENT);

					if( addr_form == FCML_AF_32_BIT ) {
						// Check if it is really a VEX/XOP prefix.
						fcml_uint8_t second_byte = fcml_fn_stream_peek(stream, &result);
						// VEX.R/XOP.R and VEX.X/XOP.X has to be set to 11 in 32bit mode.
						if( !result || ( second_byte & 0xC0 ) != 0xC0 ) {
							fcml_fn_stream_restore_point( stream, sp );
							prefix_type = FCML_PT_GROUP_UNKNOWN;
						}
						// In case of XOP prefix, if the MMMMM field is less than 8 then these two bytes are a form of the POP instruction rather than an XOP prefix.
						if( prefix_type == FCML_PT_XOP && FCML_VEX_MMMM( second_byte ) < 0x08) {
							fcml_fn_stream_restore_point( stream, sp );
							prefix_type = FCML_PT_GROUP_UNKNOWN;
						}
					}

					// Copy rest of the VEX prefixes.
					if( prefix_type != FCML_PT_GROUP_UNKNOWN ) {

						fcml_int nbytes = fcml_fn_stream_read_bytes( stream, &(prefix_details->vex_xop_bytes), xop_vex_prefix_size );
						if( nbytes != xop_vex_prefix_size ) {
							// Stream is incomplete, so we can not treat it as a VEX/XOP.
							prefix_type = FCML_PT_GROUP_UNKNOWN;
						} else {
							// Decodes VEX/XOP fields.
							switch( prefix ) {
							case 0x8F:
								// XOP is encoded like 3 bytes VEX prefix.
							case 0xC4:
								if( prefix_type == FCML_PT_XOP && FCML_VEX_MMMM( prefix_details->vex_xop_bytes[0] ) < 0x08 ) {
									prefix_type = 0;
									break;
								}
								prefixes_details->r = FCML_VEX_R(prefix_details->vex_xop_bytes[0]);
								prefixes_details->x = FCML_VEX_X(prefix_details->vex_xop_bytes[0]);
								prefixes_details->b = ( addr_form == FCML_AF_64_BIT ) ? FCML_VEX_B(prefix_details->vex_xop_bytes[0]) : 0;
								prefixes_details->w = FCML_VEX_W(prefix_details->vex_xop_bytes[1]);
								prefixes_details->l = FCML_VEX_L(prefix_details->vex_xop_bytes[1]);
								prefixes_details->pp = FCML_VEX_PP(prefix_details->vex_xop_bytes[1]);
								prefixes_details->mmmm = FCML_VEX_MMMM(prefix_details->vex_xop_bytes[0]);
								prefixes_details->vvvv = FCML_VEX_VVVV(prefix_details->vex_xop_bytes[1]);
								break;
							case 0xC5:
								prefixes_details->r = FCML_VEX_R(prefix_details->vex_xop_bytes[0]);
								prefixes_details->l = FCML_VEX_L(prefix_details->vex_xop_bytes[0]);
								prefixes_details->vvvv = FCML_VEX_VVVV(prefix_details->vex_xop_bytes[0]);
								prefixes_details->pp = FCML_VEX_PP(prefix_details->vex_xop_bytes[0]);
								break;
							}

							if( addr_form == FCML_AF_32_BIT && prefixes_details->vvvv > 7 ) {
								prefix_type = 0;
							}

							prefixes_details->vex_xop_first_byte = prefix;

							prefix_size += xop_vex_prefix_size;
						}

						fcml_fn_stream_restore_point( stream, sp );
					}

				} else {
					// If 0xC5 and 0xC4 can not be treated as a VEX prefix, it
					// should be treated just as instruction opcode.
					prefix_type = FCML_PT_GROUP_UNKNOWN;
				}
			}

			if( prefix_type != FCML_PT_GROUP_UNKNOWN) {
				prefix_details->prefix = prefix;
				prefix_details->prefix_type = prefix_type;
				prefix_details->mandatory_prefix = is_mandatory_candidate;
				prefixes_details->is_vex = is_vex;
				prefixes_details->is_xop = is_xop;
				prefixes_details->prefixes_bytes_count += prefix_size;
				// TODO: moze lepiej zamienic to na takie flagi jak w instrukcji latwij operowac i chyba spojiej.
				if( is_lock ) {
					prefixes_details->is_lock = FCML_TRUE;
				}
				if( is_rep_xrelease ) {
					prefixes_details->is_rep = FCML_TRUE;
				}
				if( is_repne_xacquire ) {
					prefixes_details->is_repne = FCML_TRUE;
				}
				if( is_branch ) {
					prefixes_details->is_branch = FCML_TRUE;
				}
				if( is_nobranch ) {
					prefixes_details->is_nobranch = FCML_TRUE;
				}
				fcml_fn_stream_seek(stream, prefix_size, FCML_EN_ST_CURRENT);
				prefix_index++;
			} else {
				is_last_prefix = FCML_FALSE;
			}

		}
		// Break loop if REX or VEX prefix is already found.
	} while( prefix_type != FCML_PT_GROUP_UNKNOWN && !is_last_prefix );

	prefixes_details->prefixes_count = prefix_index;

	// Check if prefixes marked as mandatory are really a mandatory ones.
	// VEX and XOP prefixes don't allow any mandatory prefixes, so following
	// code has nothing to do if there is VEX or XOP.
	if( prefix_index > 0 && prefix_type != FCML_PT_VEX && prefix_type != FCML_PT_XOP ) {
		fcml_bool found_plain_prefix = FCML_FALSE;
		fcml_int i;
		for( i = prefix_index; i > 0; i-- ) {
			 if( found_plain_prefix ) {
				 prefixes->prefixes[i - 1].mandatory_prefix = FCML_FALSE;
			 } else {
				 // REX prefixes have to be preceded by mandatory and optional prefixes if there are any.
				 fcml_st_dasm_instruction_prefix *prefix = &(prefixes->prefixes[i - 1]);
				 if( !prefix->mandatory_prefix && prefix->prefix_type != FCML_PT_REX ) {
					 found_plain_prefix = FCML_TRUE;
				 }
			 }
		}
	}

	return error;
}

fcml_prefixes fcml_ifn_dasm_convert_prefixes_to_generic_prefixes( fcml_st_dasm_prefixes *prefixes ) {
	fcml_prefixes gen_prefixes = 0;
	if( prefixes ) {
		if( prefixes->is_rep ) {
			gen_prefixes |= FCML_PREFIX_REP;
		}
		if( prefixes->is_repne ) {
			gen_prefixes |= FCML_PREFIX_REPNE;
		}
		if( prefixes->is_lock ) {
			gen_prefixes |= FCML_PREFIX_LOCK;
		}
		if( prefixes->is_xacquire ) {
			gen_prefixes |= FCML_PREFIX_XACQUIRE;
		}
		if( prefixes->is_xrelease ) {
			gen_prefixes |= FCML_PREFIX_XRELEASE;
		}
		if( prefixes->is_branch ) {
			gen_prefixes |= FCML_PREFIX_BRANCH_HINT;
		}
		if( prefixes->is_nobranch ) {
			gen_prefixes |= FCML_PREFIX_NOBRANCH_HINT;
		}
	}
	return gen_prefixes;
}

/****************************
 * API.
 ****************************/

fcml_ceh_error fcml_fn_dasm_disassembler_init( fcml_st_dialect_context *context, fcml_st_dasm_disassembler **disassembler ) {

	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

	fcml_ist_dasm_disassembler *int_disasm = fcml_fn_env_memory_alloc_clear( sizeof( fcml_ist_dasm_disassembler ) );
	if( int_disasm ) {

		int_disasm->dialect_context = *context;
		error = fcml_fn_dt_dts_tree_init( context, &(int_disasm->decoding_tree), &fcml_ifn_dasm_dts_prepare_instruction_decoding_callback_default, &fcml_ifn_dasm_dts_dispose_instruction_decoding_callback_default );
		if( !error ) {
			*disassembler = (fcml_st_dasm_disassembler*)int_disasm;
		}

	} else {
		error = FCML_CEH_GEC_OUT_OF_MEMORY;
	}

	return error;
}

fcml_ceh_error fcml_fn_dasm_disassemble( fcml_st_dasm_disassembler_context *context, fcml_st_dasm_disassembler_result **result ) {

	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

	*result = NULL;

	error = fcml_ifn_dasm_validate_and_prepare_context( context );
	if( error ) {
		return error;
	}

	// Prepare stream.
	fcml_st_memory_stream stream;
	stream.base_address = context->code_address;
	stream.size = context->code_size;
	stream.offset = 0;

	// Prepare disassemble context.
	fcml_ist_dasm_decoding_context decoding_context = {0};
	decoding_context.disassembler_context = context;
	decoding_context.effective_address_size_attribute = context->address_size_attribute;
	decoding_context.effective_operand_size_attribute = context->operand_size_attribute;

	decoding_context.stream = &stream;

	error = fcml_ifn_dasm_decode_prefixes( &decoding_context );
	if( error ) {
		return error;
	}

	error =  fcml_ifn_dasm_decode_instruction( &decoding_context );

	if( !error ) {
		fcml_st_dasm_disassembler_result *dis_res = fcml_fn_env_memory_alloc_clear( sizeof( fcml_st_dasm_disassembler_result ) );
		if( dis_res ) {

			fcml_st_instruction *instruction = &(dis_res->instruction);
			fcml_st_dasm_instruction_details *instruction_details = &(dis_res->instruction_details);

			// Prepare operands.
			fcml_int i;
			for( i = 0; i < FCML_OPERANDS_COUNT; i++ ) {
				fcml_ist_dasm_operand_wrapper *operand_wrapper = &(decoding_context.operand_wrappers[i]);
				if( operand_wrapper->operand.type != FCML_EOT_NONE ) {
					instruction->operands[i] = operand_wrapper->operand;
					instruction_details->operand_details[i].access_mode = operand_wrapper->access_mode;
				} else {
					break;
				}
			}

			instruction->operands_count = i;

			// ModR/M details.
			fcml_st_dasm_modrm_details *modrm_details = &(instruction_details->modrm_details);
			modrm_details->modrm = decoding_context.decoded_modrm_details.modrm;
			modrm_details->sib = decoding_context.decoded_modrm_details.sib;
			modrm_details->is_rip = decoding_context.decoded_modrm.is_rip;

			// Prefixes.
			instruction_details->prefixes = decoding_context.prefixes;

			instruction->prefixes = fcml_ifn_dasm_convert_prefixes_to_generic_prefixes( &(decoding_context.prefixes) );

			// Copy instruction hints.
			instruction->hints = decoding_context.instruction_hints;

			// Instruction code.
			instruction_details->instruction_size = decoding_context.calculated_instruction_size;
			fcml_fn_env_memory_copy( &instruction_details->instruction_code, context->code_address, instruction_details->instruction_size > FCML_INSTRUCTION_SIZE ? FCML_INSTRUCTION_SIZE : instruction_details->instruction_size );

			// Conditions.
			if( decoding_context.is_conditional ) {
				instruction->is_conditional = FCML_TRUE;
				instruction->condition = decoding_context.condition;
			} else {
				instruction->is_conditional = FCML_FALSE;
			}

			// Opcode fields.
			instruction_details->opcode_field_s_bit = decoding_context.opcode_field_s_bit;
			instruction_details->opcode_field_w_bit = decoding_context.opcode_field_w_bit;

			// Mnemonic.
			fcml_bool shortform = decoding_context.disassembler_context->configuration.use_short_form_mnemonics;
			fcml_st_mp_mnemonic *mnemonic = fcml_fn_mp_choose_mnemonic( decoding_context.mnemonics, shortform, decoding_context.pseudo_opcode, decoding_context.effective_operand_size_attribute, decoding_context.effective_address_size_attribute );
			if( mnemonic ) {
				instruction_details->is_pseudo_op_shortcut = mnemonic->pseudo_op.is_not_null;
				instruction_details->is_shortcut = mnemonic->shortcut;
				// Render mnemonic using provided dialect.
				fcml_ist_dasm_disassembler *int_disasm = (fcml_ist_dasm_disassembler *)context->disassembler;
				fcml_st_dialect_context *dialect_context = &(int_disasm->dialect_context);
				instruction->mnemonic = dialect_context->render_mnemonic( mnemonic->mnemonic, decoding_context.is_conditional ? &(decoding_context.condition) : NULL, context->configuration.conditional_group, context->configuration.choose_carry_conditional_mnemonic );
			} else {
				// Mnemonic not found.
				return FCML_CEH_GEC_ILLEGAL_STATE_EXCEPTION;
			}

			*result = dis_res;

		} else {
			error = FCML_CEH_GEC_OUT_OF_MEMORY;
		}
	}

	return error;
}

void fcml_fn_dasm_disassemble_result_free( fcml_st_dasm_disassembler_result *result ) {
	if( result ) {
		if( result->errors ) {
			fcml_fn_ceh_free_error_container( result->errors );
		}
		if( result->instruction.mnemonic ) {
			fcml_fn_env_str_strfree( result->instruction.mnemonic );
		}
		fcml_fn_env_memory_free( result );
	}
}

void fcml_fn_dasm_disassembler_free( fcml_st_dasm_disassembler *disassembler ) {
	fcml_ist_dasm_disassembler *dec_disasm = (fcml_ist_dasm_disassembler*)disassembler;
	if( dec_disasm ) {
		if( dec_disasm->decoding_tree ) {
			fcml_fn_dt_dts_tree_free( &(dec_disasm->dialect_context), dec_disasm->decoding_tree );
		}
		fcml_fn_env_memory_free( dec_disasm );
	}
}
