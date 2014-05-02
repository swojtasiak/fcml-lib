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

#include "fcml_encoding.h"

#include <stdio.h>
#include <fcml_dialect.h>
#include <fcml_errors.h>
#include <fcml_optimizers.h>
#include <fcml_choosers.h>

#include "fcml_def.h"
#include "fcml_env_int.h"
#include "fcml_hints.h"
#include "fcml_messages.h"
#include "fcml_mnemonic_parser.h"
#include "fcml_modrm.h"
#include "fcml_modrm_encoder.h"
#include "fcml_stream.h"
#include "fcml_trace.h"
#include "fcml_utils.h"

#define FCML_ASM_MAX_PART_PROCESSORS	40

/* REX prefix.*/
#define FCML_ENCODE_REX_BASE		0x40
#define FCML_ENCODE_REX_W(rex,w)	( rex | ( w << 3 ) )
#define FCML_ENCODE_REX_R(rex,r)	( rex | ( r << 2 ) )
#define FCML_ENCODE_REX_X(rex,x)	( rex | ( x << 1 ) )
#define FCML_ENCODE_REX_B(rex,b)	( rex | b )

/* XOP/VEX prefixes.*/
#define FCML_ENCODE_VEXOP_MMMM(vexop,x)		( ( vexop ) | ( ( x ) & 0x1F ) )
#define FCML_ENCODE_VEXOP_VVVV(vexop,x)		( ( vexop ) | ( ( ~( x ) & 0x0F ) << 3 ) )
#define FCML_ENCODE_VEXOP_PP(vexop,x)		( ( vexop ) | ( ( x ) & 0x03 ) )
#define FCML_ENCODE_VEXOP_W(vexop,x)		( ( vexop ) | ( ( ( x ) & 0x01 ) << 7 ) )
#define FCML_ENCODE_VEXOP_L(vexop,x)		( ( vexop ) | ( ( ( x ) & 0x01 ) << 2 ) )

/* R,X and B are stored in 1's complement form.*/
#define FCML_ENCODE_VEXOP_R(vexop,x)		( ( vexop ) | ( ( ~( x ) & 0x01 ) << 7 ) )
#define FCML_ENCODE_VEXOP_X(vexop,x)		( ( vexop ) | ( ( ~( x ) & 0x01 ) << 6 ) )
#define FCML_ENCODE_VEXOP_B(vexop,x)		( ( vexop ) | ( ( ~( x ) & 0x01 ) << 5 ) )

#define FCML_ASM_FCF	16

typedef enum fcml_ist_addr_mode_processing_phase {
	FCML_AMPP_UNDEFINED,
	FCML_AMPP_ACCEPT,
	FCML_AMPP_PROCESS
} fcml_ist_addr_mode_processing_phase;

typedef struct fcml_ist_asm_addr_mode_error {
	/** Addressing mode processing failed in the phase: */
	fcml_ist_addr_mode_processing_phase phase;
	/** Error code */
	fcml_ceh_error error_code;
	/** Local errors container, dedicated to addressing mode processing. */
	fcml_st_ceh_error_container addr_mode_errors;
	/** Ordinal number of failed instruction part processor. */
	fcml_int ipp_failed;
} fcml_ist_asm_addr_mode_error;

typedef struct fcml_ist_asm_extension_prefixes_fields {
	fcml_uint8_t vvvv;
	fcml_uint8_t mmmm;
} fcml_ist_asm_extension_prefixes_fields;

typedef struct fcml_ist_asm_opcode_reg {
	fcml_uint8_t opcode_reg;
	fcml_uint8_t ext_b;
} fcml_ist_asm_opcode_reg;

typedef fcml_usize (*fcml_ifp_asm_memory_data_size_calculator)( fcml_st_instruction *instruction, fcml_ptr args );

typedef struct fcml_ist_asm_addr_mode_desc_details {
	/* Precalculated flags describing which ASA and OSA values are available for addressing mode.*/
    fcml_flags allowed_osa;
    fcml_flags allowed_asa;
	fcml_bool is_conditional;
	fcml_st_condition condition;
	fcml_ifp_asm_memory_data_size_calculator ds_calculator;
	fcml_ptr ds_calculator_args;
} fcml_ist_asm_addr_mode_desc_details;

typedef union fcml_ist_asm_part_processor_cache {
	fcml_uint8_t is5_m2z;
} fcml_ist_asm_part_processor_cache;

typedef struct fcml_ist_asm_part_processor_context {
	fcml_ist_asm_part_processor_cache cache[FCML_ASM_MAX_PART_PROCESSORS];
	fcml_int part_processor_index;
} fcml_ist_asm_part_processor_context;

typedef struct fcml_ist_asm_encoding_context {
	fcml_st_assembler_context *assembler_context;
	fcml_st_instruction *instruction;
	fcml_st_asm_encoder_result *encoder_result;
	fcml_st_asm_optimizer_processing_details optimizer_processing_details;
	fcml_st_mp_mnemonic *mnemonic;
	fcml_ist_asm_part_processor_context part_processor_context;
	fcml_ist_asm_extension_prefixes_fields epf;
	fcml_st_register segment_override;
	fcml_st_modrm mod_rm;
	/* ModR/M related operand hints.*/
	fcml_bool is_sib_alternative_hint;
	fcml_bool is_rel_alternative_hint;
	fcml_bool is_abs_alternative_hint;
	/* True if SIB alternative is available, but hasn't been chosen.*/
	fcml_bool is_sib_alternative_encoding;
	fcml_st_encoded_modrm encoded_mod_rm;
	fcml_ist_asm_opcode_reg opcode_reg;
	fcml_nuint8_t instruction_size;
	fcml_bool is_short_form;
	fcml_bool reg_opcode_needs_rex;
	fcml_uint8_t is5_byte;
	/* Operand size calculator selected for processed addressing mode.*/
	fcml_ifp_asm_memory_data_size_calculator ds_calculator;
	fcml_ptr ds_calculator_args;
	/* Error messages.*/
	fcml_st_ceh_error_container *error_container;
	/* Number of lastly proceeded instruction part processor. */
	fcml_int last_ipp;
#ifdef FCML_DEBUG
	fcml_int __def_index;
#endif
} fcml_ist_asm_encoding_context;

struct fcml_ist_asm_instruction_part;

typedef fcml_ceh_error (*fcml_st_asm_instruction_part_post_processor)( fcml_ist_asm_encoding_context *context, struct fcml_ist_asm_instruction_part *instruction_part, fcml_ptr post_processor_args );

typedef struct fcml_ist_asm_instruction_part {
	fcml_uint8_t code[10];
	fcml_int code_length;
	fcml_ptr post_processor_args;
	fcml_st_asm_instruction_part_post_processor post_processor;
} fcml_ist_asm_instruction_part;

typedef struct fcml_ist_asm_instruction_part_container {
	/* Address of the instruction parts array.*/
	fcml_ist_asm_instruction_part *instruction_parts;
	/* Number of instruction parts in the array.*/
	fcml_int count;
} fcml_ist_asm_instruction_part_container;

struct fcml_st_asm_instruction_addr_modes;

typedef enum fcml_ien_asm_part_processor_phase {
	/* ModR/M arguments filling.*/
	FCML_IEN_ASM_IPPP_FIRST_PHASE,
	/* ModR/M encoding.*/
	FCML_IEN_ASM_IPPP_SECOND_PHASE,
	/* Prefixes are applied in this phase.*/
	FCML_IEN_ASM_IPPP_THIRD_PHASE
} fcml_ien_asm_part_processor_phase;

typedef struct fcml_ist_asm_init_context {
	fcml_coll_map instructions_map;
	fcml_st_dialect_context_int *dialect_context;
} fcml_ist_asm_init_context;

typedef fcml_ceh_error (*fcml_ifp_asm_operand_encoder)( fcml_ien_asm_part_processor_phase phase, fcml_ist_asm_encoding_context *context, fcml_st_def_addr_mode_desc *addr_mode_desc, fcml_st_def_decoded_addr_mode *addr_mode, fcml_st_operand *operand_def, fcml_ist_asm_instruction_part *operand_enc );
typedef fcml_ceh_error (*fcml_ifp_asm_operand_acceptor)( fcml_ist_asm_encoding_context *context, fcml_ist_asm_addr_mode_desc_details *addr_mode_details, fcml_st_def_addr_mode_desc *addr_mode_desc, fcml_st_def_decoded_addr_mode *addr_mode, fcml_st_operand *operand_def, fcml_ist_asm_instruction_part *operand_enc );

typedef struct fcml_ist_asm_operand_encoder_def {
	fcml_ifp_asm_operand_encoder encoder;
	fcml_ifp_asm_operand_acceptor acceptor;
	fcml_fp_hts_instruction_hints_calculator hints_calculator;
} fcml_ist_asm_operand_encoder_def;

typedef enum fcml_ien_asm_instruction_part_processor_type {
	FCML_IEN_ASM_IPPT_VERIFIER,
	FCML_IEN_ASM_IPPT_ENCODER,
	FCML_IEN_ASM_IPPT_DECORATOR,
} fcml_ien_asm_instruction_part_processor_type;

typedef fcml_ceh_error (*fcml_ifp_asm_instruction_part_processor)( fcml_ien_asm_part_processor_phase phase, fcml_ist_asm_encoding_context *context, fcml_ist_asm_addr_mode_desc_details *addr_mode_details, fcml_st_def_addr_mode_desc *addr_mode_def, fcml_ist_asm_instruction_part *instruction_part, fcml_ptr args );
typedef fcml_ceh_error (*fcml_ifp_asm_instruction_part_processor_acceptor)( fcml_ist_asm_encoding_context *context, fcml_ist_asm_addr_mode_desc_details *addr_mode_details, fcml_st_def_addr_mode_desc *addr_mode_desc, fcml_st_instruction *instruction, fcml_ptr args );

typedef struct fcml_ist_asm_instruction_part_processor_descriptor {
	fcml_ifp_asm_instruction_part_processor processor_encoder;
	fcml_ifp_asm_instruction_part_processor_acceptor processor_acceptor;
	fcml_ien_asm_instruction_part_processor_type processor_type;
	fcml_ptr processor_args;
	fcml_fp_env_memory_free_handler processor_args_deallocator;
	fcml_bool is_short_form_supported;
} fcml_ist_asm_instruction_part_processor_descriptor;

typedef fcml_ist_asm_instruction_part_processor_descriptor (*fcml_ifp_asm_instruction_part_processor_factory)( fcml_uint32_t flags, fcml_st_def_instruction_desc *instruction, fcml_st_def_addr_mode_desc *addr_mode, fcml_hints *hints, fcml_ceh_error *error );

typedef struct fcml_ist_asm_instruction_part_processor_chain {
	struct fcml_ist_asm_instruction_part_processor_chain *next_processor;
	fcml_ist_asm_instruction_part_processor_descriptor processor_descriptor;
} fcml_ist_asm_instruction_part_processor_chain;

typedef fcml_ist_asm_instruction_part_processor_chain* (*fcml_ifp_asm_instruction_part_processor_factory_dispatcher)( fcml_st_def_instruction_desc *instruction, fcml_st_def_addr_mode_desc *addr_mode, int *parts, fcml_hints *hints, fcml_ceh_error *error );

typedef struct fcml_ist_asm_instruction_addr_mode_encoding_details {
    /* Mnemonic configuration chosen for given addressing mode.*/
    fcml_st_mp_mnemonic *mnemonic;
	/* Instruction definition.*/
	fcml_st_def_addr_mode_desc *addr_mode_desc;
	/* Some precalculated information about instruction addressing mode. This structure can be helpful, because*/
	/* some details of the addressing mode can be pre-calculate while addressing mode is processed in initialization mode.*/
	/* So we can get some performance improvements.*/
	fcml_ist_asm_addr_mode_desc_details addr_mode_details;
	/* Chain of instruction part processors registered for instruction addressing mode.*/
	fcml_ist_asm_instruction_part_processor_chain *part_processor_chain;
	/* Number of instruction parts needed to assemble described instruction.*/
	fcml_int instruction_parts;
	/* Addressing mode related hints.*/
	fcml_hints hints;
	/* True if details are cloned for alternative mnemonics.*/
	fcml_bool is_cloned;
} fcml_ist_asm_instruction_addr_mode_encoding_details;

/* *************************/
/* DEBUG related functions.*/
/* *************************/

#ifdef FCML_DEBUG

fcml_char fcml_idarr_asm_data_attr_flags_buff[64];

fcml_string fcml_idfn_asm_print_attr_size_flags( fcml_flags flags ) {
	int index = 0;
	if( flags == FCML_EN_ASF_ANY ) {
		sprintf( fcml_idarr_asm_data_attr_flags_buff, "ANY" );
	} else {
		if( flags & FCML_EN_ASF_16 ) {
			index += sprintf( fcml_idarr_asm_data_attr_flags_buff, "2" );
		}
		if( flags & FCML_EN_ASF_32 ) {
			index += sprintf( fcml_idarr_asm_data_attr_flags_buff + index, "4" );
		}
		if( flags & FCML_EN_ASF_64 ) {
			index += sprintf( fcml_idarr_asm_data_attr_flags_buff + index, "8" );
		}
	}
	return fcml_idarr_asm_data_attr_flags_buff;
}

fcml_char fcml_idarr_asm_data_flags_buff[512];

fcml_string fcml_idfn_asm_encode_size_flags( fcml_st_asm_optimizer_processing_details *size_flags ) {

	int index = 0;

	/* L flag.*/
	if( size_flags->l.is_not_null ) {
		index += sprintf( fcml_idarr_asm_data_flags_buff, "L: %d, ", size_flags->l.value );
	} else {
		index += sprintf( fcml_idarr_asm_data_flags_buff, "L: NS, " );
	}

	/* Allowed EOSA.*/
	if( size_flags->allowed_eosa.is_set ) {
		index += sprintf( fcml_idarr_asm_data_flags_buff + index, "Allowed OSA: [%s], ", fcml_idfn_asm_print_attr_size_flags( size_flags->allowed_eosa.flags ) );
	} else {
		index += sprintf( fcml_idarr_asm_data_flags_buff + index, "Allowed OSA: NS, " );
	}

	/* Allowed EASA.*/
	if( size_flags->allowed_easa.is_set ) {
		index += sprintf( fcml_idarr_asm_data_flags_buff + index, "Allowed ASA: [%s], ", fcml_idfn_asm_print_attr_size_flags( size_flags->allowed_easa.flags ) );
	} else {
		index += sprintf( fcml_idarr_asm_data_flags_buff + index, "Allowed ASA: NS, " );
	}

	/* Chosen OSA.*/
	index += sprintf( fcml_idarr_asm_data_flags_buff + index, "EOSA: %d, ", size_flags->eosa );

	/* Chosen OSA.*/
	index += sprintf( fcml_idarr_asm_data_flags_buff + index, "EASA: %d", size_flags->easa );

	return fcml_idarr_asm_data_flags_buff;
}

#endif

/***********************************/
/* Error handling helper functions */
/***********************************/

void fcml_ifn_ceh_asm_add_error_msg( fcml_ist_asm_encoding_context *context, fcml_string message, fcml_ceh_error error_code ) {
	if( context->assembler_context->configuration.enable_error_messages ) {
		fcml_bool add_error = FCML_TRUE;
		fcml_st_ceh_error_info *current = context->error_container->errors;
		// Only one error message is currently allowed.
		while( current ) {
			if( current->code == FCML_EN_CEH_EL_ERROR ) {
				add_error = FCML_FALSE;
				break;
			}
			current = current->next_error;
		}
		if( add_error ) {
			fcml_fn_ceh_add_error( context->error_container, message, error_code, FCML_EN_CEH_EL_ERROR );
		}
	}
}

void fcml_ifn_ceh_asm_add_warning_msg( fcml_ist_asm_encoding_context *context, fcml_string message, fcml_ceh_error error_code ) {
	if( context->assembler_context->configuration.enable_error_messages ) {
		fcml_fn_ceh_add_error( context->error_container, message, error_code, FCML_EN_CEH_EL_WARN );
	}
}

enum fcml_ien_asm_comparator_type {
	FCML_IEN_CT_EQUAL,
	FCML_IEN_CT_EQUAL_OR_LESS,
};

void fcml_ifn_asm_clean_context( fcml_ist_asm_encoding_context *context ) {
	fcml_st_asm_optimizer_processing_details *data_size_flags = &(context->optimizer_processing_details);
	data_size_flags->easa = FCML_DS_UNDEF;
	data_size_flags->eosa = FCML_DS_UNDEF;
	data_size_flags->l.is_not_null = FCML_FALSE;
	data_size_flags->l.value = 0;
	data_size_flags->allowed_easa.flags = FCML_EN_ASF_ANY;
	data_size_flags->allowed_easa.is_set = FCML_FALSE;
	data_size_flags->allowed_eosa.flags = FCML_EN_ASF_ANY;
	data_size_flags->allowed_eosa.is_set = FCML_FALSE;
	/* Clears segment override set by acceptor functions.*/
	context->segment_override.reg = 0;
	context->segment_override.size = FCML_DS_UNDEF;
	context->segment_override.type = FCML_REG_UNDEFINED;
	context->segment_override.x64_exp = FCML_FALSE;
}

fcml_st_memory_stream fcml_ifn_asm_instruction_part_stream( fcml_ist_asm_instruction_part *instruction_part ) {
	fcml_st_memory_stream stream;
	stream.base_address = &(instruction_part->code);
	stream.offset = 0;
	stream.size = sizeof(instruction_part->code);
	return stream;
}

fcml_usize fcml_ifn_asm_get_effective_address_size( fcml_ist_asm_encoding_context *context ) {
	if(context->optimizer_processing_details.easa ) {
		return context->optimizer_processing_details.easa;
	}
	return context->assembler_context->entry_point.address_size_attribute;
}

fcml_usize fcml_ifn_asm_calculate_operand_size( fcml_ist_asm_encoding_context *context, fcml_usize size_operator, fcml_uint8_t encoded_size_operator ) {
	/* Remember, some addressing modes use registers that do not match memory data size.
	 * These addressing modes can accept unknown operand size so we do not calculate
	 * size operators for them, because such calculated size wouldn't match data size anyway.
	 */
	if( size_operator == FCML_OS_UNDEFINED && !FCML_IS_EOS_OPT( encoded_size_operator ) ) {
		if( context->ds_calculator ) {
			size_operator = context->ds_calculator( context->instruction, context->ds_calculator_args );
		}
	}
	return size_operator;
}

fcml_usize fcml_ifn_asm_non_standard_attribute_size_calculator( fcml_st_entry_point *entry_point, fcml_usize operand_size, fcml_usize l, fcml_usize u, fcml_ceh_error *error ) {
	fcml_usize attribute_size = 0;
	if( operand_size == l ) {
		attribute_size = 16;
	} else if( operand_size == u ) {
		if( entry_point->operand_size_attribute == FCML_DS_16 ) {
			FCML_TRACE_MSG( "Addressing mode not available for 16 bit EOSA." );
			*error = FCML_CEH_GEC_INVALID_OPPERAND_SIZE;
		} else {
			attribute_size = entry_point->operand_size_attribute;
		}
	}
	return attribute_size;
}

fcml_ceh_error fcml_ifn_asm_decode_dynamic_operand_size( fcml_ist_asm_encoding_context *context, fcml_uint8_t encoded_operand_size, fcml_usize operand_size, fcml_usize *encoded_data_size, enum fcml_ien_asm_comparator_type comparator ) {

	fcml_st_entry_point *entry_point = &(context->assembler_context->entry_point);
	fcml_st_asm_optimizer_processing_details *flags = &(context->optimizer_processing_details);
	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
	fcml_usize effective_address_size = 0;
	fcml_usize effective_operand_size = 0;
	fcml_uint8_t encoded_static_operand_size = FCML_GET_OS( encoded_operand_size );
	fcml_nuint8_t l = { 0, FCML_FALSE };

	if( ( operand_size == FCML_OS_UNDEFINED ) && FCML_IS_EOS_OPT( encoded_operand_size ) ) {
		return error;
	}

	if( encoded_data_size != NULL ) {
		*encoded_data_size = operand_size;
	}

	switch( encoded_static_operand_size ) {
	case FCML_EOS_UNDEFINED:
		break;
	case FCML_EOS_L:
		l.is_not_null = FCML_TRUE;
		l.value = 0;
		if( operand_size == FCML_DS_256 ) {
			l.value = 1;
		} else if( operand_size != FCML_DS_128 ) {
			error = FCML_CEH_GEC_INVALID_OPPERAND_SIZE;
		}
		break;
	case FCML_EOS_EASA:
		if( operand_size == FCML_DS_16 || operand_size == FCML_DS_32 || operand_size == FCML_DS_64 ) {
			effective_address_size = operand_size;
		} else {
			FCML_TRACE_MSG( "Unsupported encoded EOSA size." );
			error = FCML_CEH_GEC_INVALID_OPPERAND_SIZE;
		}
		break;
	case FCML_EOS_EOSA:
		if( operand_size == FCML_DS_16 || operand_size == FCML_DS_32 || operand_size == FCML_DS_64 ) {
			effective_operand_size = operand_size;
		} else {
			FCML_TRACE_MSG( "Unsupported encoded EASA size." );
			error = FCML_CEH_GEC_INVALID_OPPERAND_SIZE;
		}
		break;
	case FCML_EOS_14_28:
		effective_operand_size = fcml_ifn_asm_non_standard_attribute_size_calculator( entry_point, operand_size, 14 * 8, 28 * 8, &error );
		break;
	case FCML_EOS_32_64:
		effective_operand_size = fcml_ifn_asm_non_standard_attribute_size_calculator( entry_point, operand_size, 16 * 8, 32 * 8, &error );
		break;
	case FCML_EOS_94_108:
		effective_operand_size = fcml_ifn_asm_non_standard_attribute_size_calculator( entry_point, operand_size, 94 * 8, 108 * 8, &error );
		break;
    case FCML_EOS_FPI:
    case FCML_EOS_FP:
        /* Far pointer indirect.*/
        effective_operand_size = operand_size - FCML_DS_16;
        break;
	default:
		if( operand_size || !FCML_IS_EOS_OPT( encoded_operand_size ) ) {
			if( comparator == FCML_IEN_CT_EQUAL ) {
				if ( encoded_static_operand_size * 8 != operand_size ) {
					FCML_TRACE( "Unsupported operand size. Expected %d got %d.", operand_size, encoded_static_operand_size * 8 );
					error = FCML_CEH_GEC_INVALID_OPPERAND_SIZE;
				}
			} else {
				if ( encoded_static_operand_size * 8 < operand_size ) {
					FCML_TRACE( "Unsupported operand size. Expected greater or equal to %d got %d.", operand_size, encoded_static_operand_size * 8 );
					error = FCML_CEH_GEC_INVALID_OPPERAND_SIZE;
				} else {
					if( encoded_data_size != NULL ) {
						*encoded_data_size = encoded_static_operand_size * 8;
					}
				}
			}
		}
		break;
	}

	if( !error ) {
		if( l.is_not_null ) {
			if( flags->l.is_not_null && flags->l.value != l.value ) {
				/* All dynamic operands have to be of the same size.*/
				FCML_TRACE( "L flag differs expected %d got %d.", flags->l.value, l.value );
				error = FCML_CEH_GEC_INVALID_OPPERAND_SIZE;
			} else {
				flags->l = l;
			}
		}
		if( effective_address_size ) {
			if( flags->easa && effective_address_size != flags->easa ) {
				FCML_TRACE( "Wrong encoded EASA size. Expected %d got %d.", flags->easa, effective_address_size );
				error = FCML_CEH_GEC_INVALID_OPPERAND_SIZE;
			} else {
				flags->easa = effective_address_size;
				if( encoded_data_size ) {
					*encoded_data_size = effective_address_size;
				}
			}
		}
		if( effective_operand_size ) {
			if( flags->eosa && effective_operand_size != flags->eosa ) {
				FCML_TRACE( "Wrong encoded EOSA size. Expected %d got %d.", flags->eosa, effective_operand_size );
				error = FCML_CEH_GEC_INVALID_OPPERAND_SIZE;
			} else {
				flags->eosa = effective_operand_size;
				if( encoded_data_size ) {
					*encoded_data_size = effective_operand_size;
				}
			}
		}
	}

	return error;
}

fcml_bool fcml_ifn_asm_set_size_flag( fcml_st_nullable_size_flags *nullable_flags, fcml_flags flags ) {
	if( nullable_flags->is_set ) {
		if( ( nullable_flags->flags & flags ) == 0 ) {
			/* We need flags that weren't allowed by previous operands or IPPs.*/
			return FCML_FALSE;
		}
		/* Set new set of flags, take into account that these might be a subset of existing ones.*/
		nullable_flags->flags = flags;
	} else {
		nullable_flags->flags = flags;
		nullable_flags->is_set = FCML_TRUE;
	}
	return FCML_TRUE;
}

fcml_ceh_error fcml_ifn_asm_accept_segment_register( fcml_ist_asm_encoding_context *context, fcml_st_register *segment_register, fcml_uint8_t encoded_segment_register ) {

	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

    if( segment_register->type == FCML_REG_UNDEFINED ) {
    	/* No mater what segment register we have expected, default one has been used.*/
    	error = FCML_CEH_GEC_NO_ERROR;
    } else {
		if( segment_register->type == FCML_REG_SEG ) {
			if( segment_register->reg != ( encoded_segment_register & 0x7F ) ) {
				if ( encoded_segment_register & FCML_SEG_ALLOW_OVERRIDE ) {
					context->segment_override = *segment_register;
				} else {
					/* Register can not be overridden.*/
					fcml_ifn_ceh_asm_add_error_msg( context, fcml_fn_msg_get_message( FCML_MC_SEGMENT_REGISTER_CAN_NOT_BE_OVERRIDDEN ), FCML_CEH_MEC_ERROR_ILLEGAL_SEG_REG_OVERRIDE );
					error = FCML_CEH_GEC_INVALID_REGISTER;
				}
			}
		} else {
			/* Wrong register type, segment register should be used.*/
			fcml_ifn_ceh_asm_add_error_msg( context, fcml_fn_msg_get_message( FCML_MC_SEGMENT_WRONG_REGISTER_TYPE_SEG ), FCML_CEH_MEC_ERROR_INVALID_REGISTER_TYPE_SEG );
			error = FCML_CEH_GEC_INVALID_REGISTER_TYPE;
		}
    }

    return error;
}

fcml_bool fcml_ifn_asm_accept_data_size( fcml_ist_asm_encoding_context *context, fcml_st_def_addr_mode_desc *addr_mode_desc, fcml_uint8_t encoded_operand_size, fcml_usize operand_size, enum fcml_ien_asm_comparator_type comparator ) {

	fcml_st_entry_point *entry_point = &(context->assembler_context->entry_point);
	fcml_st_asm_optimizer_processing_details *data_size_flags = &(context->optimizer_processing_details);
	fcml_flags osa_flags = FCML_EN_ASF_ANY;
	fcml_flags asa_flags = FCML_EN_ASF_ANY;
	fcml_bool result = FCML_TRUE;

	if( ( operand_size == FCML_OS_UNDEFINED ) && FCML_IS_EOS_OPT( encoded_operand_size ) ) {
		/* If operand size is optional, we do not need to accept it.*/
		return FCML_TRUE;
	}

	switch( FCML_GET_OS( encoded_operand_size ) ) {
	case FCML_EOS_UNDEFINED:
		break;
	case FCML_EOS_L:
		if( FCML_DEF_PREFIX_L_IGNORE_OS( addr_mode_desc->allowed_prefixes ) ) {
			result = ( operand_size == entry_point->operand_size_attribute );
		} else {
			result = ( ( operand_size == FCML_DS_128 ) || ( operand_size == FCML_DS_256 ) );
		}
		break;
	case FCML_EOS_EASA:
		if( entry_point->op_mode == FCML_AF_32_BIT ) {
			result = ( ( operand_size == FCML_DS_16 ) || ( operand_size == FCML_DS_32 ) );
		} else {
			result = ( ( operand_size == FCML_DS_32 ) || ( operand_size == FCML_DS_64 ) );
		}
		if( result ) {
			asa_flags = (operand_size / FCML_ASM_FCF);
		}
		break;
	case FCML_EOS_EOSA:
		if( entry_point->op_mode == FCML_AF_32_BIT ) {
			result = ( ( operand_size == FCML_DS_16 ) || ( operand_size == FCML_DS_32 ) );
		} else {
			result = ( ( operand_size == FCML_DS_16 ) || ( operand_size == FCML_DS_32 ) || ( operand_size == FCML_DS_64 ) );
		}
		if( result ) {
			osa_flags = (operand_size / FCML_ASM_FCF);
		}
		break;
	case FCML_EOS_14_28:
		if( operand_size == 14 * 8 ) {
			osa_flags |= FCML_EN_ASF_16;
		} else if( operand_size == 28 * 8 ) {
			osa_flags |= ( FCML_EN_ASF_32 | FCML_EN_ASF_64 );
		} else {
			result = FCML_FALSE;
		}
		break;
	case FCML_EOS_32_64:
		if( ( operand_size == FCML_DS_16 * 2 ) || ( FCML_DS_32 * 2 ) || ( FCML_DS_64 * 2 ) ) {
			osa_flags = ( operand_size / 2 / FCML_ASM_FCF );
		} else {
			result = FCML_FALSE;
		}
		break;
	case FCML_EOS_94_108:
		if( operand_size == 94 * 8 ) {
			osa_flags |= FCML_EN_ASF_16;
		} else if( operand_size == 108 * 8 ) {
			osa_flags |= ( FCML_EN_ASF_32 | FCML_EN_ASF_64 );
		} else {
			result = FCML_FALSE;
		}
		break;
	case FCML_EOS_FPI:
	case FCML_EOS_FP:
	    /* Far pointer indirect.*/
	    switch( operand_size ) {
	    case FCML_DS_16 + FCML_DS_16:
            osa_flags |= FCML_EN_ASF_16;
            break;
	    case FCML_DS_32 + FCML_DS_16:
	        osa_flags |= FCML_EN_ASF_32;
	        break;
	    case FCML_DS_64 + FCML_DS_16:
            osa_flags |= FCML_EN_ASF_64;
            break;
	    default:
	        result = FCML_FALSE;
	    }
        break;
	default:
		if( comparator == FCML_IEN_CT_EQUAL ) {
			result = ( FCML_GET_OS( encoded_operand_size ) * 8 == operand_size );
		} else {
			result = ( FCML_GET_OS( encoded_operand_size ) * 8 >= operand_size );
		}
		if( !result && FCML_IS_EOS_OPT( encoded_operand_size ) && operand_size == 0 ) {
			/* Operand size is optional, so return TRUE anyway.*/
			result = FCML_TRUE;
		}
		break;
	}

	if( osa_flags && !fcml_ifn_asm_set_size_flag( &(data_size_flags->allowed_eosa), osa_flags ) ) {
		result = FCML_FALSE;
	}

	if( asa_flags && !fcml_ifn_asm_set_size_flag( &(data_size_flags->allowed_easa), asa_flags ) ) {
		result = FCML_FALSE;
	}

	return result;
}

/*********************************
 * Operand encoders.
 *********************************/

/*******************/
/* Immediate value */
/*******************/

fcml_bool fcml_ifn_asm_try_to_convert_integer_and_set_flag( const fcml_st_integer *source, fcml_st_integer *destination, fcml_usize expected_size, fcml_usize size, fcml_flags flag, fcml_flags *flags ) {

    /* We expect signed integers here, but of course user is not forced to provide values that match expected size.
     * In such cases values are converted to appropriate size using sign set by user. Anyway sometimes user is not
     * able to guess if values are signed or not in given context. Parsers might be a good example. To avoid sign
     * problem, if source operand has expected size (so conversion to the expected size is not necessary)
     * we can treat it like signed value.
     */

	fcml_st_integer tmp = *source;
	if( !expected_size ) {
		expected_size = size;
	} else {
		if( tmp.size == expected_size ) {
			tmp.is_signed = FCML_TRUE;
		}
	}

	fcml_ceh_error error = fcml_fn_utils_convert_integer_to_integer( &tmp, destination, expected_size, size );
	if( !error && flags ) {
		*flags |= flag;
	}

	return !error;
}

fcml_ceh_error fcml_ifn_asm_operand_acceptor_imm( fcml_ist_asm_encoding_context *context, fcml_ist_asm_addr_mode_desc_details *addr_mode_details, fcml_st_def_addr_mode_desc *addr_mode_desc, fcml_st_def_decoded_addr_mode *addr_mode, fcml_st_operand *operand_def, fcml_ist_asm_instruction_part *operand_enc ) {

	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

	if( operand_def->type == FCML_EOT_IMMEDIATE ) {

		fcml_st_integer destination = {0};

		fcml_flags flags = 0;

		fcml_sf_def_tma_imm *args = (fcml_sf_def_tma_imm*)addr_mode->addr_mode_args;
		fcml_uint8_t size = args->encoded_size;
		fcml_uint8_t size_ex = args->encoded_ex_size;
		fcml_st_integer *immediate = &(operand_def->immediate);
		fcml_en_operating_mode op_mode = context->assembler_context->entry_point.op_mode;
		fcml_bool is_convertable = FCML_FALSE;

		fcml_flags osa_flags = context->optimizer_processing_details.allowed_eosa.flags;
		if( !osa_flags ) {
			osa_flags = FCML_EN_ASF_ALL;
		}

		/* Not all EOSA values are available for every addressing mode. Additional flags can enable or disable some of them.*/

		if( size != FCML_EOS_EOSA && size_ex != FCML_EOS_EOSA ) {
			is_convertable |= fcml_ifn_asm_try_to_convert_integer_and_set_flag( immediate, &destination, FCML_GET_OS( size_ex ) * 8, FCML_GET_OS( size ) * 8, 0, NULL );
		} else if( size == FCML_EOS_EOSA && size_ex == FCML_EOS_EOSA ) {
			/* Destination size calculated by EOSA.*/
			if( osa_flags & FCML_EN_ASF_16 )
				is_convertable |= fcml_ifn_asm_try_to_convert_integer_and_set_flag( immediate, &destination, FCML_DS_16, FCML_DS_16, FCML_EN_ASF_16, &flags );
			if( osa_flags & FCML_EN_ASF_32 )
				is_convertable |= fcml_ifn_asm_try_to_convert_integer_and_set_flag( immediate, &destination, FCML_DS_32, FCML_DS_32, FCML_EN_ASF_32, &flags );
			if( ( osa_flags & FCML_EN_ASF_64 ) && op_mode == FCML_AF_64_BIT ) {
				is_convertable |= fcml_ifn_asm_try_to_convert_integer_and_set_flag( immediate, &destination, FCML_DS_64, ( args->is_64bit_imm_allowed ) ? FCML_DS_64 : FCML_DS_32, FCML_EN_ASF_64, &flags );
			}
		} else if( size == FCML_EOS_EOSA ) {
			if( osa_flags & FCML_EN_ASF_16 )
				is_convertable |= fcml_ifn_asm_try_to_convert_integer_and_set_flag( immediate, &destination, FCML_GET_OS( size_ex ) * 8, FCML_DS_16, FCML_EN_ASF_16, &flags );
			if( osa_flags & FCML_EN_ASF_32 )
				is_convertable |= fcml_ifn_asm_try_to_convert_integer_and_set_flag( immediate, &destination, FCML_GET_OS( size_ex ) * 8, FCML_DS_32, FCML_EN_ASF_32, &flags );
			if( ( osa_flags & FCML_EN_ASF_64 ) && op_mode == FCML_AF_64_BIT ) {
				is_convertable |= fcml_ifn_asm_try_to_convert_integer_and_set_flag( immediate, &destination, FCML_GET_OS( size_ex ) * 8, args->is_64bit_imm_allowed ? FCML_DS_64 : FCML_DS_32, FCML_EN_ASF_64, &flags );
			}
		} else {
			/* IMM extended to effective address size attribute.*/
			if( osa_flags & FCML_EN_ASF_16 )
				is_convertable |= fcml_ifn_asm_try_to_convert_integer_and_set_flag( immediate, &destination, FCML_DS_16, FCML_GET_OS( size ) * 8, FCML_EN_ASF_16, &flags );
			if( osa_flags & FCML_EN_ASF_32 )
				is_convertable |= fcml_ifn_asm_try_to_convert_integer_and_set_flag( immediate, &destination, FCML_DS_32, FCML_GET_OS( size ) * 8, FCML_EN_ASF_32, &flags );
			if( ( osa_flags & FCML_EN_ASF_64 ) && op_mode == FCML_AF_64_BIT ) {
				is_convertable |= fcml_ifn_asm_try_to_convert_integer_and_set_flag( immediate, &destination, FCML_DS_64, FCML_GET_OS( size ) * 8, FCML_EN_ASF_64, &flags );
			}
		}

		if( !is_convertable || ( flags && !fcml_ifn_asm_set_size_flag( &(context->optimizer_processing_details.allowed_eosa ), flags ) ) ) {
			FCML_TRACE_MSG("Accept IMM: Can not accept IMM value." );
			error = FCML_CEH_GEC_INVALID_OPPERAND;
		}

		return error;
	} else {
		error = FCML_CEH_GEC_INVALID_OPPERAND;
	}
	return error;
}

fcml_ceh_error fcml_ifn_asm_operand_encoder_imm( fcml_ien_asm_part_processor_phase phase, fcml_ist_asm_encoding_context *context, fcml_st_def_addr_mode_desc *addr_mode_desc, fcml_st_def_decoded_addr_mode *addr_mode, fcml_st_operand *operand_def, fcml_ist_asm_instruction_part *operand_enc ) {

	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

	if( phase == FCML_IEN_ASM_IPPP_FIRST_PHASE ) {

		fcml_sf_def_tma_imm *args = (fcml_sf_def_tma_imm*)addr_mode->addr_mode_args;
		fcml_uint8_t size = args->encoded_size;
		fcml_uint8_t size_ex = args->encoded_ex_size;

		fcml_st_integer *source_imm = &(operand_def->immediate);
		fcml_st_integer converted_source;

		fcml_usize eosa_size = context->optimizer_processing_details.eosa;

		/* Remember that only one addressing mode of MOV instruction for 64 bits mode can encode IMM64. */
		fcml_usize eosa_imm = eosa_size;
		if( !args->is_64bit_imm_allowed && eosa_size == FCML_DS_64 ) {
			eosa_imm = FCML_DS_32;
		}

		if( ( size == FCML_EOS_EOSA || size_ex == FCML_EOS_EOSA ) && !eosa_size ) {
			FCML_TRACE_MSG("EOSA size not set! Processing failed.");
			return FCML_CEH_GEC_INTERNAL_ERROR;
		}

		fcml_bool is_converted = FCML_FALSE;

		if( size != FCML_EOS_EOSA && size_ex != FCML_EOS_EOSA ) {
		    is_converted = fcml_ifn_asm_try_to_convert_integer_and_set_flag( source_imm, &converted_source, FCML_GET_OS( size_ex ) * 8, FCML_GET_OS( size ) * 8, 0, NULL );
		} else if( size == FCML_EOS_EOSA && size_ex == FCML_EOS_EOSA ) {
		    is_converted = fcml_ifn_asm_try_to_convert_integer_and_set_flag( source_imm, &converted_source, eosa_size, eosa_imm, 0, NULL );
		} else if( size == FCML_EOS_EOSA ) {
		    is_converted = fcml_ifn_asm_try_to_convert_integer_and_set_flag( source_imm, &converted_source, FCML_GET_OS( size_ex ) * 8, eosa_imm, 0, NULL );
		} else {
		    is_converted = fcml_ifn_asm_try_to_convert_integer_and_set_flag( source_imm, &converted_source, eosa_size, FCML_GET_OS( size ) * 8, 0, NULL );
		}

		if( !is_converted ) {
		    error = FCML_CEH_GEC_VALUE_OUT_OF_RANGE;
		}

		if( !error ) {
            fcml_st_memory_stream stream = { &(operand_enc->code), 0, sizeof( operand_enc->code ) };
            error = fcml_fn_utils_encode_integer( &stream, &converted_source );
            if( !error ) {
                operand_enc->code_length = stream.offset;
            }
		}
	}

	return error;
}

/*********************/
/* Explicit register */
/*********************/

fcml_ceh_error fcml_ifn_asm_operand_acceptor_explicit_reg( fcml_ist_asm_encoding_context *context, fcml_ist_asm_addr_mode_desc_details *addr_mode_details, fcml_st_def_addr_mode_desc *addr_mode_desc, fcml_st_def_decoded_addr_mode *addr_mode, fcml_st_operand *operand_def, fcml_ist_asm_instruction_part *operand_enc ) {
	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
	fcml_sf_def_tma_explicit_reg *args = (fcml_sf_def_tma_explicit_reg*)addr_mode->addr_mode_args;
	if( operand_def->type != FCML_EOT_REGISTER
			|| operand_def->reg.type != args->reg_type
			|| operand_def->reg.reg != args->reg_num
			|| !fcml_ifn_asm_accept_data_size( context, addr_mode_desc, args->encoded_reg_size, operand_def->reg.size, FCML_IEN_CT_EQUAL ) ) {
		error = FCML_CEH_GEC_INVALID_OPPERAND;
	}
	return error;
}

/* Example: FCML_OP_EXPLICIT_REG( FCML_REG_GPR, FCML_REG_AL, FCML_EOS_BYTE )*/
fcml_ceh_error fcml_ifn_asm_operand_encoder_explicit_reg( fcml_ien_asm_part_processor_phase phase, fcml_ist_asm_encoding_context *context, fcml_st_def_addr_mode_desc *addr_mode_desc, fcml_st_def_decoded_addr_mode *addr_mode, fcml_st_operand *operand_def, fcml_ist_asm_instruction_part *operand_enc ) {
	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
	if( phase == FCML_IEN_ASM_IPPP_FIRST_PHASE ) {
		fcml_sf_def_tma_explicit_reg *args = (fcml_sf_def_tma_explicit_reg*)addr_mode->addr_mode_args;
		fcml_st_register *reg = &(operand_def->reg);
		/* Encode IMM.*/
		fcml_usize encoded_size;
		error = fcml_ifn_asm_decode_dynamic_operand_size( context, args->encoded_reg_size, reg->size, &encoded_size, FCML_IEN_CT_EQUAL );
	}
	return error;
}

/*******************/
/* Opcode register */
/*******************/

fcml_ceh_error fcml_ifn_asm_operand_acceptor_opcode_reg( fcml_ist_asm_encoding_context *context, fcml_ist_asm_addr_mode_desc_details *addr_mode_details, fcml_st_def_addr_mode_desc *addr_mode_desc, fcml_st_def_decoded_addr_mode *addr_mode, fcml_st_operand *operand_def, fcml_ist_asm_instruction_part *operand_enc ) {
	fcml_sf_def_tma_opcode_reg *args = (fcml_sf_def_tma_opcode_reg*)addr_mode->addr_mode_args;
	if( operand_def->type != FCML_EOT_REGISTER || operand_def->reg.type != args->reg_type ) {
		return FCML_CEH_GEC_INVALID_OPPERAND;
	}
	if( !fcml_ifn_asm_accept_data_size( context, addr_mode_desc, args->encoded_reg_size, operand_def->reg.size, FCML_IEN_CT_EQUAL ) ) {
		return FCML_CEH_GEC_INVALID_OPPERAND;
	}
	return FCML_CEH_GEC_NO_ERROR;
}

fcml_ceh_error fcml_ifn_asm_operand_encoder_opcode_reg( fcml_ien_asm_part_processor_phase phase, fcml_ist_asm_encoding_context *context, fcml_st_def_addr_mode_desc *addr_mode_desc, fcml_st_def_decoded_addr_mode *addr_mode, fcml_st_operand *operand_def, fcml_ist_asm_instruction_part *operand_enc ) {
	if( phase == FCML_IEN_ASM_IPPP_FIRST_PHASE ) {
		if( operand_def->reg.reg > 7 ) {
			context->opcode_reg.opcode_reg = operand_def->reg.reg - 8;
			context->opcode_reg.ext_b = FCML_TRUE;
		} else {
			context->opcode_reg.opcode_reg = operand_def->reg.reg;
		}
		if( context->assembler_context->entry_point.op_mode == FCML_AF_64_BIT ) {
		    context->reg_opcode_needs_rex = operand_def->reg.x64_exp;
		}
	}
	return FCML_CEH_GEC_NO_ERROR;
}

/***********************************/
/* Immediate relative displacement */
/***********************************/

fcml_ceh_error fcml_ifn_asm_operand_acceptor_immediate_dis_relative( fcml_ist_asm_encoding_context *context, fcml_ist_asm_addr_mode_desc_details *addr_mode_details, fcml_st_def_addr_mode_desc *addr_mode_desc, fcml_st_def_decoded_addr_mode *addr_mode, fcml_st_operand *operand_def, fcml_ist_asm_instruction_part *operand_enc ) {
    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
	if ( ( operand_def->type == FCML_EOT_IMMEDIATE ) || ( operand_def->type == FCML_EOT_ADDRESS && operand_def->address.address_form == FCML_AF_OFFSET ) ) {
        fcml_flags flags = 0;
	    if( context->assembler_context->entry_point.op_mode == FCML_AF_64_BIT ) {
            /* In 64-bit mode OSA is fixed at 64 bits. Just in case, because addressing mode
             * acceptor is responsible for interpreting FCML_DEF_OPCODE_FLAGS_FORCE_64BITS_EOSA
	         * flag and forcing appropriate OSA size.
	         */
	        flags = FCML_EN_ASF_64;
	    } else {
	        flags = FCML_EN_ASF_32 | FCML_EN_ASF_16;
	    }
	    if( !fcml_ifn_asm_set_size_flag( &(context->optimizer_processing_details.allowed_eosa), flags ) ) {
            error = FCML_CEH_GEC_INVALID_OPPERAND;
        }
	} else {
	    error = FCML_CEH_GEC_INVALID_OPPERAND;
	}
	return error;
}

fcml_ceh_error fcml_ifn_asm_convert_to_requested_rel( fcml_st_integer *value, fcml_usize expected_size, fcml_uint8_t encoded_rel_size ) {
    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
    if( encoded_rel_size == FCML_EOS_BYTE ) {
        error = fcml_fn_utils_convert_integer_to_integer( value, value, expected_size, FCML_DS_8 );
        if( error ) {
            error = FCML_CEH_GEC_INVALID_OPPERAND_SIZE;
        }
    }
    return error;
}

int fcml_ifn_asm_calculate_size_for_encoded_rel( fcml_usize osa, fcml_uint8_t encoded_rel_size ) {
    if( encoded_rel_size == FCML_EOS_UNDEFINED ) {
        return ( osa == FCML_DS_64 ) ? 4 : osa / 8;
    } else {
        return encoded_rel_size;
    }
}

fcml_ceh_error fcml_ifn_asm_instruction_part_immediate_dis_relative_post_processor( fcml_ist_asm_encoding_context *context, fcml_ist_asm_instruction_part *instruction_part, fcml_ptr post_processor_args, fcml_uint8_t encoded_rel_size ) {

    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

    /* Sanity check.*/
    if( encoded_rel_size != FCML_EOS_UNDEFINED && encoded_rel_size != FCML_EOS_BYTE ) {
       return FCML_CEH_GEC_INVALID_OPPERAND;
    }

    if( context->instruction_size.is_not_null ) {

    	fcml_st_entry_point *entry_point = &(context->assembler_context->entry_point);

        /* Optimizer is responsible for setting optimal OSA value.*/
        fcml_usize osa = context->optimizer_processing_details.eosa;

        fcml_st_operand *operand_def = (fcml_st_operand*)post_processor_args;

        fcml_st_integer source;
        fcml_st_integer destination = {0};
        fcml_st_integer displacement = {0};

        int rel_size = fcml_ifn_asm_calculate_size_for_encoded_rel( osa, encoded_rel_size );

		if( operand_def->type == FCML_EOT_IMMEDIATE ) {
			source = operand_def->immediate;
		} else if( operand_def->type == FCML_EOT_ADDRESS && operand_def->address.address_form == FCML_AF_OFFSET ) {
			error = fcml_fn_utils_offset_to_integer( &(operand_def->address.offset), &source );
		} else {
			return FCML_CEH_GEC_INVALID_OPPERAND;
		}

        if( !error ) {

            displacement.is_signed = FCML_TRUE;

            if( fcml_fn_utils_convert_integer_to_integer( &source, &destination, osa, osa ) ) {
                error = FCML_CEH_GEC_INVALID_OPPERAND;
            }

            if( !error ) {

                switch( osa ) {
                    case FCML_DS_16: {

                        fcml_int16_t offset = destination.int16;
                        fcml_int16_t ip = (fcml_int16_t)( ( entry_point->ip + context->instruction_size.value + rel_size ) & 0x0000FFFF);
                        fcml_int16_t rel16 = offset - ip;

                        displacement.int16 = rel16;
                        displacement.size = FCML_DS_16;

                        error = fcml_ifn_asm_convert_to_requested_rel( &displacement, FCML_DS_16, encoded_rel_size );

                        break;
                    }
                    case FCML_DS_32: {

                        fcml_int32_t offset = destination.int32;
                        fcml_int32_t eip = (fcml_int32_t)( entry_point->ip + context->instruction_size.value + rel_size );
                        fcml_int32_t rel32 = offset - eip;

                        displacement.int32 = rel32;
                        displacement.size = FCML_DS_32;

                        error = fcml_ifn_asm_convert_to_requested_rel( &displacement, FCML_DS_32, encoded_rel_size );

                        break;
                    }
                    case FCML_DS_64: {

                        fcml_int64_t offset = (fcml_int64_t)destination.int64;
                        fcml_int64_t rip = (fcml_int64_t)( entry_point->ip + context->instruction_size.value + rel_size );
                        fcml_int64_t rel32 = offset - rip;

                        displacement.int32 = (fcml_int32_t)rel32;
                        displacement.size = FCML_DS_32;

                        error = fcml_ifn_asm_convert_to_requested_rel( &displacement, FCML_DS_32, encoded_rel_size );

                        break;
                    }
                }

                if( !error ) {
                    /* Encode ModR/M and displacement.*/
                    fcml_st_memory_stream stream = fcml_ifn_asm_instruction_part_stream( instruction_part );
                    fcml_fn_utils_encode_integer( &stream, &displacement );
                    instruction_part->code_length = stream.offset;
                } else if( error == FCML_CEH_GEC_INVALID_OPPERAND_SIZE && encoded_rel_size == 1 ) {
                	/* In this case we can hint optimizer not to try different ASA/OSA combinations, because it doesn't make sense. */
                	context->optimizer_processing_details.break_optimization = FCML_TRUE;
                }

            }

        }
    } else {
    	/* Should never happened.*/
		FCML_TRACE_MSG( "Instruction size can not be here." );
		error = FCML_CEH_GEC_INTERNAL_ERROR;
    }

    return error;
}

fcml_ceh_error fcml_ifn_asm_instruction_part_immediate_dis_relative_post_processor_8( fcml_ist_asm_encoding_context *context, fcml_ist_asm_instruction_part *instruction_part, fcml_ptr post_processor_args ) {
    return fcml_ifn_asm_instruction_part_immediate_dis_relative_post_processor( context, instruction_part, post_processor_args, FCML_EOS_BYTE );
}

fcml_ceh_error fcml_ifn_asm_instruction_part_immediate_dis_relative_post_processor_undef( fcml_ist_asm_encoding_context *context, fcml_ist_asm_instruction_part *instruction_part, fcml_ptr post_processor_args ) {
    return fcml_ifn_asm_instruction_part_immediate_dis_relative_post_processor( context, instruction_part, post_processor_args, FCML_EOS_UNDEFINED );
}

fcml_ceh_error fcml_ifn_asm_operand_encoder_immediate_dis_relative( fcml_ien_asm_part_processor_phase phase, fcml_ist_asm_encoding_context *context, fcml_st_def_addr_mode_desc *addr_mode_desc, fcml_st_def_decoded_addr_mode *addr_mode, fcml_st_operand *operand_def, fcml_ist_asm_instruction_part *operand_enc ) {

    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

    if( phase == FCML_IEN_ASM_IPPP_SECOND_PHASE ) {

        fcml_sf_def_tma_immediate_dis_relative *args = (fcml_sf_def_tma_immediate_dis_relative*)addr_mode->addr_mode_args;

        operand_enc->code_length = 0;

        if( args->encoded_size == FCML_EOS_BYTE ) {
            operand_enc->post_processor = fcml_ifn_asm_instruction_part_immediate_dis_relative_post_processor_8;
        } else if( args->encoded_size == FCML_EOS_UNDEFINED ) {
            operand_enc->post_processor = fcml_ifn_asm_instruction_part_immediate_dis_relative_post_processor_undef;
        } else {
            /* Unsupported operand size encoded in operand arguments.*/
            error = FCML_CEH_GEC_INVALID_OPPERAND;
        }

        operand_enc->post_processor_args = operand_def;

    }

	return error;
}

/***************/
/* Far pointer */
/***************/

fcml_ceh_error fcml_ifn_asm_operand_acceptor_far_pointer( fcml_ist_asm_encoding_context *context, fcml_ist_asm_addr_mode_desc_details *addr_mode_details, fcml_st_def_addr_mode_desc *addr_mode_desc, fcml_st_def_decoded_addr_mode *addr_mode, fcml_st_operand *operand_def, fcml_ist_asm_instruction_part *operand_enc ) {
    fcml_ceh_error result = FCML_CEH_GEC_NO_ERROR;
    if( operand_def->type != FCML_EOT_FAR_POINTER ) {
        return FCML_CEH_GEC_INVALID_OPPERAND;
    }
    switch( context->assembler_context->entry_point.op_mode ) {
    case FCML_AF_16_BIT:
        if( operand_def->far_pointer.offset_size == FCML_DS_16 ) {
            if( !fcml_ifn_asm_set_size_flag( &(context->optimizer_processing_details.allowed_eosa), FCML_EN_ASF_16 ) ) {
                /* Size can not be used by this operand. */
                result = FCML_CEH_GEC_INVALID_OPPERAND;
            }
        } else {
            /* 32 bit offset is not supported in 16 bit mode. */
            result = FCML_CEH_GEC_INVALID_OPPERAND;
        }
        break;
    case FCML_AF_32_BIT:
        if( !fcml_ifn_asm_set_size_flag( &(context->optimizer_processing_details.allowed_eosa), ( operand_def->far_pointer.offset_size == FCML_DS_16 ) ? ( FCML_EN_ASF_16 | FCML_EN_ASF_32 ) : FCML_EN_ASF_32 ) ) {
            /* Size can not be used by this operand. */
            result = FCML_CEH_GEC_INVALID_OPPERAND;
        }
        break;
    case FCML_AF_64_BIT:
        result = FCML_CEH_GEC_INVALID_OPPERAND;
        break;
    }
	return result;
}

fcml_ceh_error fcml_ifn_asm_operand_encoder_far_pointer( fcml_ien_asm_part_processor_phase phase, fcml_ist_asm_encoding_context *context, fcml_st_def_addr_mode_desc *addr_mode_desc, fcml_st_def_decoded_addr_mode *addr_mode, fcml_st_operand *operand_def, fcml_ist_asm_instruction_part *operand_enc ) {

    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

    if( phase == FCML_IEN_ASM_IPPP_FIRST_PHASE ) {

        /* Prepare stream to instruction part's buffer. */
        fcml_st_memory_stream stream = fcml_ifn_asm_instruction_part_stream( operand_enc );

        /* Write offset.*/
        if( operand_def->far_pointer.offset_size == FCML_DS_16 ) {
            fcml_fn_stream_write_word( &stream, (fcml_uint16_t)operand_def->far_pointer.offset16 );
            operand_enc->code_length = 4;
        } else {
            fcml_fn_stream_write_dword( &stream, (fcml_uint32_t)operand_def->far_pointer.offset32 );
            operand_enc->code_length = 6;
        }

        /* Write segment.*/
        fcml_fn_stream_write_word( &stream, operand_def->far_pointer.segment );

    }
	return error;

}

/************************************/
/* Explicit GPR register addressing */
/************************************/

fcml_ceh_error fcml_ifn_asm_operand_acceptor_explicit_gps_reg_addressing( fcml_ist_asm_encoding_context *context, fcml_ist_asm_addr_mode_desc_details *addr_mode_details, fcml_st_def_addr_mode_desc *addr_mode_desc, fcml_st_def_decoded_addr_mode *addr_mode, fcml_st_operand *operand_def, fcml_ist_asm_instruction_part *operand_enc ) {

    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

    fcml_sf_def_tma_explicit_gps_reg_addressing *args = (fcml_sf_def_tma_explicit_gps_reg_addressing*)addr_mode->addr_mode_args;

    if( ( operand_def->type != FCML_EOT_ADDRESS ) || ( operand_def->address.effective_address.base.reg != args->reg_num ) ) {
    	error = FCML_CEH_GEC_INVALID_OPPERAND;
    } else if( !fcml_ifn_asm_accept_data_size( context, addr_mode_desc, FCML_EOS_EASA, operand_def->address.effective_address.base.size, FCML_IEN_CT_EQUAL ) ) {
    	error = FCML_CEH_GEC_INVALID_ADDRESS_SIZE;
    } else if( !fcml_ifn_asm_accept_data_size( context, addr_mode_desc, args->encoded_operand_size, operand_def->address.size_operator, FCML_IEN_CT_EQUAL ) ) {
    	error = FCML_CEH_GEC_INVALID_OPPERAND_SIZE;
    } else {
    	error = fcml_ifn_asm_accept_segment_register( context, &(operand_def->address.segment_selector.segment_selector), args->encoded_segment_register );
    }

    return error;
}

/***************/
/* Explicit IB */
/***************/

fcml_ceh_error fcml_ifn_asm_operand_acceptor_explicit_ib( fcml_ist_asm_encoding_context *context, fcml_ist_asm_addr_mode_desc_details *addr_mode_details, fcml_st_def_addr_mode_desc *addr_mode_desc, fcml_st_def_decoded_addr_mode *addr_mode, fcml_st_operand *operand_def, fcml_ist_asm_instruction_part *operand_enc ) {
    fcml_ceh_error error = FCML_CEH_GEC_INVALID_OPPERAND;
    if( operand_def->type == FCML_EOT_IMMEDIATE ) {
        fcml_st_integer dest;
		/* We are interested in errors only here. */
		error = fcml_fn_utils_convert_integer_to_integer( &(operand_def->immediate), &dest, FCML_DS_8, FCML_DS_8 );
    }
	return error;
}

fcml_ceh_error fcml_ifn_asm_operand_encoder_explicit_ib( fcml_ien_asm_part_processor_phase phase, fcml_ist_asm_encoding_context *context, fcml_st_def_addr_mode_desc *addr_mode_desc, fcml_st_def_decoded_addr_mode *addr_mode, fcml_st_operand *operand_def, fcml_ist_asm_instruction_part *operand_enc ) {
    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
    if( phase == FCML_IEN_ASM_IPPP_FIRST_PHASE ) {
        error = FCML_CEH_GEC_INVALID_OPPERAND;
        fcml_sf_def_tma_explicit_ib *exp_ib = (fcml_sf_def_tma_explicit_ib*)addr_mode->addr_mode_args;
        fcml_st_integer dest;
		fcml_ceh_error res = fcml_fn_utils_convert_integer_to_integer( &(operand_def->immediate), &dest, FCML_DS_8, FCML_DS_8 );
		if( !res ) {
			if( exp_ib->ib == (fcml_uint8_t)dest.int8 ) {
				error = FCML_CEH_GEC_NO_ERROR;
			}
		}
    }
    return error;
}

/***************************/
/* Segment relative offset */
/***************************/

fcml_ceh_error fcml_ifn_asm_operand_acceptor_segment_relative_offset( fcml_ist_asm_encoding_context *context, fcml_ist_asm_addr_mode_desc_details *addr_mode_details, fcml_st_def_addr_mode_desc *addr_mode_desc, fcml_st_def_decoded_addr_mode *addr_mode, fcml_st_operand *operand_def, fcml_ist_asm_instruction_part *operand_enc ) {

    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

    if ( operand_def->type == FCML_EOT_ADDRESS ) {

        fcml_sf_def_tma_segment_relative_offset *args = (fcml_sf_def_tma_segment_relative_offset*)addr_mode->addr_mode_args;

        fcml_st_address *address = &(operand_def->address);

        if( address->address_form != FCML_AF_OFFSET ) {
            return FCML_CEH_GEC_INVALID_OPPERAND;
        }

        if( operand_def->address.size_operator != FCML_OS_UNDEFINED ) {
			if( !fcml_ifn_asm_accept_data_size( context, addr_mode_desc, args->encoded_operand_size, operand_def->address.size_operator, FCML_IEN_CT_EQUAL ) ) {
			   return FCML_CEH_GEC_INVALID_OPPERAND;
			}
        }

        fcml_bool is_convertable = FCML_FALSE;
        fcml_flags flags = FCML_EN_ASF_ANY;
        fcml_st_integer source_address = {0}, converted_address = {0};

        /* Convert IMM value to address. */
        error = fcml_fn_utils_offset_to_integer( &(address->offset ), &source_address );
        if( error ) {
           return FCML_CEH_GEC_INVALID_OPPERAND;
        }

        /* Check if address can be converted to 16, 32 or 64 bits. */
        source_address.is_signed = FCML_TRUE;

        is_convertable |= fcml_ifn_asm_try_to_convert_integer_and_set_flag( &source_address, &converted_address, FCML_DS_32, FCML_DS_32, FCML_EN_ASF_32, &flags );
        if( context->assembler_context->entry_point.op_mode == FCML_AF_64_BIT ) {
           is_convertable |= fcml_ifn_asm_try_to_convert_integer_and_set_flag( &source_address, &converted_address, FCML_DS_64, FCML_DS_64, FCML_EN_ASF_64, &flags );
        } else {
           is_convertable |= fcml_ifn_asm_try_to_convert_integer_and_set_flag( &source_address, &converted_address, FCML_DS_16, FCML_DS_16, FCML_EN_ASF_16, &flags );
        }

        if( !fcml_ifn_asm_set_size_flag( &(context->optimizer_processing_details.allowed_easa), flags ) ) {
           error = FCML_CEH_GEC_INVALID_OPPERAND;
        }

    } else {
        error = FCML_CEH_GEC_INVALID_OPPERAND;
    }

    return error;
}

fcml_ceh_error fcml_ifn_asm_operand_encoder_segment_relative_offset( fcml_ien_asm_part_processor_phase phase, fcml_ist_asm_encoding_context *context, fcml_st_def_addr_mode_desc *addr_mode_desc, fcml_st_def_decoded_addr_mode *addr_mode, fcml_st_operand *operand_def, fcml_ist_asm_instruction_part *operand_enc ) {

	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

    if( phase == FCML_IEN_ASM_IPPP_FIRST_PHASE ) {

        fcml_usize asa =  context->optimizer_processing_details.easa;

        if( asa != FCML_DS_UNDEF ) {

            fcml_st_address *address = &(operand_def->address);

            /* Convert IMM value to address. */
            fcml_st_integer offset = {0};
            error = fcml_fn_utils_offset_to_integer( &(address->offset ), &offset );
            if( !error ) {

                /* Convert address to size indicated by ASA.*/
                error = fcml_fn_utils_convert_integer_to_integer( &offset, &offset, asa, asa );
                if( !error ) {

                    /* Encode offset.*/
                    fcml_st_memory_stream stream = fcml_ifn_asm_instruction_part_stream( operand_enc );
                    fcml_fn_utils_encode_integer( &stream, &offset );
                    operand_enc->code_length = stream.offset;
                }

            }

        } else {
            /* ASA should be set by optimizer.*/
            error = FCML_CEH_GEC_INVALID_OPPERAND;
        }
    }
    return error;
}

/***************/
/* ModR/M - rm */
/***************/

fcml_ceh_error fcml_ifn_asm_operand_acceptor_rm( fcml_ist_asm_encoding_context *context, fcml_ist_asm_addr_mode_desc_details *addr_mode_details, fcml_st_def_addr_mode_desc *addr_mode_desc, fcml_st_def_decoded_addr_mode *addr_mode, fcml_st_operand *operand_def, fcml_ist_asm_instruction_part *operand_enc ) {
	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
	fcml_bool is_reg = FCML_FALSE;
	fcml_bool is_mem = FCML_FALSE;
	fcml_sf_def_tma_rm *args = (fcml_sf_def_tma_rm*)addr_mode->addr_mode_args;
	is_mem = operand_def->type == FCML_EOT_ADDRESS;
	is_reg = operand_def->type == FCML_EOT_REGISTER;

	/* Check operand type.*/
	fcml_bool result = ( ( args->flags & FCML_RMF_R ) && is_reg ) || ( ( args->flags & FCML_RMF_M ) && is_mem );

	if( result ) {
		if( is_reg ) {
			if( args->reg_type != operand_def->reg.type ) {
				/* Different register type.*/
				error = FCML_CEH_GEC_INVALID_OPPERAND;
			} else if( ( context->instruction->prefixes & FCML_PREFIX_LOCK ) && addr_mode->access_mode == FCML_AM_WRITE ) {
				/* Lock prefixes are only allowed for destination memory operands.*/
				error = FCML_CEH_GEC_INVALID_OPPERAND;
			} else {
				if( !fcml_ifn_asm_accept_data_size( context, addr_mode_desc, args->encoded_register_operand_size, operand_def->reg.size, FCML_IEN_CT_EQUAL ) ) {
					FCML_TRACE_MSG( "Unsupported register size." );
					error = FCML_CEH_GEC_INVALID_OPPERAND_SIZE;
				}
			}
		}
		if( is_mem ) {
			/* OSA.*/
			fcml_usize mem_data_size = fcml_ifn_asm_calculate_operand_size( context, operand_def->address.size_operator, args->encoded_memory_operand_size );
			if( !fcml_ifn_asm_accept_data_size( context, addr_mode_desc, args->encoded_memory_operand_size, mem_data_size, FCML_IEN_CT_EQUAL ) ) {
				FCML_TRACE_MSG( "Unsupported memory operand size." );
				error = FCML_CEH_GEC_INVALID_OPPERAND_SIZE;
			}
			if( !error ) {

			    /* Check VSIB.*/
			    if( args->is_vsib ) {
			        fcml_st_register *index = &(operand_def->address.effective_address.index);
			        if( index->type == FCML_REG_SIMD ) {
			            fcml_usize vsib_reg_size = args->vector_index_register == FCML_VSIB_XMM ? FCML_DS_128 : FCML_DS_256;
			            if( vsib_reg_size != index->size ) {
			                FCML_TRACE_MSG( "Wrong VSIB size." );
			                error = FCML_CEH_GEC_INVALID_OPPERAND_SIZE;
			            }
			        } else {
			            FCML_TRACE_MSG( "VSIB encoding needs SIMD index register." );
			            error = FCML_CEH_GEC_INVALID_OPPERAND_SIZE;
			        }
			    }

				/* Accept segment registers if any of them have been set.*/
			    if( !error ) {

					fcml_st_effective_address *effective_address = &(operand_def->address.effective_address);
					fcml_st_segment_selector *segment_selector = &(operand_def->address.segment_selector);
					fcml_st_register *segment_register = &(segment_selector->segment_selector);

					if( segment_register->reg != FCML_REG_UNDEFINED ) {
						if( segment_register->type == FCML_REG_SEG ) {
							/* Segment register set, so it has to be accepted.*/
							if( addr_mode_desc->instruction_group & FCML_AMT_BRANCH ) {
								/* For branch instructions only CS register can be used and override is not acceptable.*/
								if( segment_register->reg != FCML_REG_CS ) {
									error = FCML_CEH_GEC_INVALID_OPPERAND;
								}
							} else if( ( effective_address->base.type == FCML_REG_GPR ) && ( effective_address->base.reg == FCML_REG_BP || effective_address->base.reg == FCML_REG_SP ) ) {
								/* For SP/BP registers SS segment register has to be used.*/
								if( segment_register->reg != FCML_REG_SS ) {
									error = FCML_CEH_GEC_INVALID_OPPERAND;
								}
							} else {
								if( segment_register->reg != FCML_REG_DS ) {
									context->segment_override = *segment_register;
								}
							}
							if( error ) {
								/* Segment register can not be overridden. */
								fcml_ifn_ceh_asm_add_error_msg( context, fcml_fn_msg_get_message( FCML_MC_SEGMENT_REGISTER_CAN_NOT_BE_OVERRIDDEN ), FCML_CEH_MEC_ERROR_ILLEGAL_SEG_REG_OVERRIDE );
							}
						} else {
							/* Wrong register type. */
							fcml_ifn_ceh_asm_add_error_msg( context, fcml_fn_msg_get_message( FCML_MC_SEGMENT_WRONG_REGISTER_TYPE_SEG ), FCML_CEH_MEC_ERROR_INVALID_REGISTER_TYPE_SEG );
						}
					}
			    }

			    if( !error ) {

                    /* ASA.*/
                    fcml_en_operating_mode op_mode = context->assembler_context->entry_point.op_mode;

                    fcml_st_modrm mod_rm = {0};
                    mod_rm.address = operand_def->address;

                    fcml_flags esa;
                    fcml_fn_modrm_calculate_effective_address_size( &mod_rm, &esa );

                    if( ( esa & FCML_EN_ASF_16 ) && op_mode != FCML_AF_64_BIT ) {
                        context->optimizer_processing_details.allowed_easa.flags |= FCML_EN_ASF_16;
                    }

                    if( esa & FCML_EN_ASF_32 ) {
                        context->optimizer_processing_details.allowed_easa.flags |= FCML_EN_ASF_32;
                    }

                    if( ( esa & FCML_EN_ASF_64 ) && op_mode != FCML_AF_16_BIT ) {
                        context->optimizer_processing_details.allowed_easa.flags |= FCML_EN_ASF_64;
                    }
			    }
			}

		}
	} else {
		error = FCML_CEH_GEC_INVALID_OPPERAND;
	}
	return error;
}

fcml_ceh_error fcml_ifn_asm_operand_encoder_rm( fcml_ien_asm_part_processor_phase phase, fcml_ist_asm_encoding_context *context, fcml_st_def_addr_mode_desc *addr_mode_desc, fcml_st_def_decoded_addr_mode *addr_mode, fcml_st_operand *operand_def, fcml_ist_asm_instruction_part *operand_enc ) {

	fcml_st_entry_point *entry_point = &(context->assembler_context->entry_point);
	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
	fcml_sf_def_tma_rm *args = (fcml_sf_def_tma_rm*)addr_mode->addr_mode_args;

	if( phase == FCML_IEN_ASM_IPPP_FIRST_PHASE ) {

		if( operand_def->type == FCML_EOT_REGISTER ) {

			context->mod_rm.reg.is_not_null = FCML_TRUE;
			context->mod_rm.reg.value = operand_def->reg.reg;

			if( entry_point->op_mode == FCML_AF_64_BIT ) {
			    context->mod_rm.reg_opcode_needs_rex = operand_def->reg.x64_exp;
			}

			/* Modify data size flags if there is such need.*/
			error = fcml_ifn_asm_decode_dynamic_operand_size( context, args->encoded_register_operand_size, operand_def->reg.size, NULL,FCML_IEN_CT_EQUAL );

		} else {
			/* Set hints for ModR/M instruction part encoder.*/
			context->is_sib_alternative_hint = ( operand_def->hints & FCML_OP_HINT_SIB_ENCODING );

			if( entry_point->op_mode == FCML_AF_64_BIT ) {
				context->is_abs_alternative_hint = ( operand_def->hints & FCML_OP_HINT_ABSOLUTE_ADDRESSING );
				context->is_rel_alternative_hint = ( operand_def->hints & FCML_OP_HINT_RELATIVE_ADDRESSING );
			} else {
				context->is_abs_alternative_hint = FCML_FALSE;
				context->is_rel_alternative_hint = FCML_FALSE;
			}

		    context->mod_rm.address = operand_def->address;
		    fcml_usize mem_data_size = fcml_ifn_asm_calculate_operand_size( context, operand_def->address.size_operator, args->encoded_memory_operand_size );
			error = fcml_ifn_asm_decode_dynamic_operand_size( context, args->encoded_memory_operand_size, mem_data_size, NULL, FCML_IEN_CT_EQUAL );

		}
	}

	return error;
}

/**************/
/* ModR/M - r */
/**************/

fcml_ceh_error fcml_ifn_asm_operand_acceptor_r( fcml_ist_asm_encoding_context *context, fcml_ist_asm_addr_mode_desc_details *addr_mode_details, fcml_st_def_addr_mode_desc *addr_mode_desc, fcml_st_def_decoded_addr_mode *addr_mode, fcml_st_operand *operand_def, fcml_ist_asm_instruction_part *operand_enc ) {
	fcml_sf_def_tma_r *args = (fcml_sf_def_tma_r*)addr_mode->addr_mode_args;
	if( operand_def->type != FCML_EOT_REGISTER || operand_def->reg.type != args->reg_type  ) {
		return FCML_CEH_GEC_INVALID_OPPERAND;
	}
	/* Some registers allow UNDEF size to be defined for them.*/
	if( ( operand_def->reg.type != FCML_REG_DR && operand_def->reg.type != FCML_REG_CR ) && operand_def->reg.size != FCML_DS_UNDEF ) {
        if( !fcml_ifn_asm_accept_data_size( context, addr_mode_desc, args->encoded_register_operand_size, operand_def->reg.size, FCML_IEN_CT_EQUAL ) ) {
            return FCML_CEH_GEC_INVALID_OPPERAND;
        }
	}
	return FCML_CEH_GEC_NO_ERROR;
}

fcml_ceh_error fcml_ifn_asm_operand_encoder_r( fcml_ien_asm_part_processor_phase phase, fcml_ist_asm_encoding_context *context, fcml_st_def_addr_mode_desc *addr_mode_desc, fcml_st_def_decoded_addr_mode *addr_mode, fcml_st_operand *operand_def, fcml_ist_asm_instruction_part *operand_enc ) {

	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

	if( phase == FCML_IEN_ASM_IPPP_FIRST_PHASE ) {

		fcml_sf_def_tma_r *args = (fcml_sf_def_tma_r*)addr_mode->addr_mode_args;
		context->mod_rm.reg_opcode = operand_def->reg.reg;

		if( context->assembler_context->entry_point.op_mode == FCML_AF_64_BIT ) {
		    context->mod_rm.reg_opcode_needs_rex = operand_def->reg.x64_exp;
		}

		if( ( operand_def->reg.type != FCML_REG_DR && operand_def->reg.type != FCML_REG_CR ) && operand_def->reg.size != FCML_DS_UNDEF ) {
            error = fcml_ifn_asm_decode_dynamic_operand_size( context, args->encoded_register_operand_size, operand_def->reg.size, NULL, FCML_IEN_CT_EQUAL );
            if( error ) {
                error = FCML_CEH_GEC_INVALID_OPPERAND;
            }
		}

	}

	return error;
}

/************************/
/* Far pointer indirect */
/************************/

fcml_sf_def_tma_rm fcml_isst_asm_far_pointer_indirect_args = { FCML_REG_UNDEFINED, FCML_EOS_UNDEFINED, FCML_EOS_FPI, FCML_RMF_M };

fcml_ceh_error fcml_ifn_asm_operand_acceptor_far_pointer_indirect( fcml_ist_asm_encoding_context *context, fcml_ist_asm_addr_mode_desc_details *addr_mode_details, fcml_st_def_addr_mode_desc *addr_mode_desc, fcml_st_def_decoded_addr_mode *addr_mode, fcml_st_operand *operand_def, fcml_ist_asm_instruction_part *operand_enc ) {
    /* Prepare modified addressing mode for*/
    fcml_st_def_decoded_addr_mode l_addr_mode = *addr_mode;
    l_addr_mode.addr_mode_args = &fcml_isst_asm_far_pointer_indirect_args;
    return fcml_ifn_asm_operand_acceptor_rm( context, addr_mode_details, addr_mode_desc, &l_addr_mode, operand_def, operand_enc );
}

fcml_ceh_error fcml_ifn_asm_operand_encoder_far_pointer_indirect( fcml_ien_asm_part_processor_phase phase, fcml_ist_asm_encoding_context *context, fcml_st_def_addr_mode_desc *addr_mode_desc, fcml_st_def_decoded_addr_mode *addr_mode, fcml_st_operand *operand_def, fcml_ist_asm_instruction_part *operand_enc ) {
    /* Prepare modified addressing mode for*/
	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
	if( phase == FCML_IEN_ASM_IPPP_FIRST_PHASE ) {
		fcml_st_def_decoded_addr_mode l_addr_mode = *addr_mode;
		l_addr_mode.addr_mode_args = &fcml_isst_asm_far_pointer_indirect_args;
		error = fcml_ifn_asm_operand_encoder_rm( phase, context, addr_mode_desc, &l_addr_mode, operand_def, operand_enc );
	}
	return error;
}

/********/
/* VVVV */
/********/

fcml_ceh_error fcml_ifn_asm_operand_acceptor_vex_vvvv( fcml_ist_asm_encoding_context *context, fcml_ist_asm_addr_mode_desc_details *addr_mode_details, fcml_st_def_addr_mode_desc *addr_mode_desc, fcml_st_def_decoded_addr_mode *addr_mode, fcml_st_operand *operand_def, fcml_ist_asm_instruction_part *operand_enc ) {
	fcml_sf_def_tma_vex_vvvv_reg *args = (fcml_sf_def_tma_vex_vvvv_reg*)addr_mode->addr_mode_args;
	if( operand_def->type != FCML_EOT_REGISTER || operand_def->reg.type != args->reg_type ) {
		return FCML_CEH_GEC_INVALID_OPPERAND;
	}
	if( !fcml_ifn_asm_accept_data_size( context, addr_mode_desc, args->encoded_register_size, operand_def->reg.size, FCML_IEN_CT_EQUAL ) ) {
		return FCML_CEH_GEC_INVALID_OPPERAND;
	}
	return FCML_CEH_GEC_NO_ERROR;
}

fcml_ceh_error fcml_ifn_asm_operand_encoder_vex_vvvv( fcml_ien_asm_part_processor_phase phase, fcml_ist_asm_encoding_context *context, fcml_st_def_addr_mode_desc *addr_mode_desc, fcml_st_def_decoded_addr_mode *addr_mode, fcml_st_operand *operand_def, fcml_ist_asm_instruction_part *operand_enc ) {
	if( phase == FCML_IEN_ASM_IPPP_FIRST_PHASE ) {
		fcml_ist_asm_extension_prefixes_fields *epf = &(context->epf);
		fcml_st_register *reg = &(operand_def->reg);
		epf->vvvv = reg->reg;
	}
	return FCML_CEH_GEC_NO_ERROR;
}

/*--------*/
/* is4/is5*/
/*--------*/

fcml_ceh_error fcml_ifn_asm_operand_acceptor_isX( fcml_ist_asm_encoding_context *context, fcml_ist_asm_addr_mode_desc_details *addr_mode_details, fcml_st_def_addr_mode_desc *addr_mode_desc, fcml_st_def_decoded_addr_mode *addr_mode, fcml_st_operand *operand_def, fcml_ist_asm_instruction_part *operand_enc ) {
	fcml_sf_def_tma_is *is_args = (fcml_sf_def_tma_is*)addr_mode->addr_mode_args;
	if( ( is_args->flags & FCML_ISF_IS4 ) || ( is_args->flags & FCML_ISF_IS5_SRC ) ) {
		/* IS4/IS5(src) */
		if( operand_def->type != FCML_EOT_REGISTER || operand_def->reg.type != FCML_REG_SIMD ) {
			return FCML_CEH_GEC_INVALID_OPPERAND;
		}
		if( !fcml_ifn_asm_accept_data_size( context, addr_mode_desc, FCML_EOS_L, operand_def->reg.size, FCML_IEN_CT_EQUAL ) ) {
			return FCML_CEH_GEC_INVALID_OPPERAND;
		}
	} else if( operand_def->type == FCML_EOT_IMMEDIATE ) {
		/* IS5 - m2z */
		fcml_int8_t imm_value;
		fcml_ceh_error error = fcml_fn_utils_convert_integer_to_int8( &(operand_def->immediate), &imm_value );
		if( error ) {
			return FCML_CEH_GEC_INVALID_OPPERAND;
		}
		if( imm_value > 3 ) {
			return FCML_CEH_GEC_INVALID_OPPERAND;
		}
		/* Store converted value for future use in order to avoid further conversions.*/
		context->part_processor_context.cache[context->part_processor_context.part_processor_index].is5_m2z = imm_value;
	} else {
		return FCML_CEH_GEC_INVALID_OPPERAND;
	}
	return FCML_CEH_GEC_NO_ERROR;
}

fcml_ceh_error fcml_ifn_asm_operand_encoder_isX( fcml_ien_asm_part_processor_phase phase, fcml_ist_asm_encoding_context *context, fcml_st_def_addr_mode_desc *addr_mode_desc, fcml_st_def_decoded_addr_mode *addr_mode, fcml_st_operand *operand_def, fcml_ist_asm_instruction_part *operand_enc ) {
	if( phase == FCML_IEN_ASM_IPPP_FIRST_PHASE ) {
		fcml_sf_def_tma_is *is_args = (fcml_sf_def_tma_is*)addr_mode->addr_mode_args;
		if( is_args->flags & FCML_ISF_IS4 ) {
			/* is4*/
			operand_enc->code[0] = operand_def->reg.reg << 4;
			operand_enc->code_length = 1;
		} else if( is_args->flags & FCML_ISF_IS5_SRC ) {
			/* Store is5 source register for last is5 instruction part encoder.*/
			context->is5_byte = operand_def->reg.reg << 4;
		} else {
			/* is5-m2z*/
			operand_enc->code[0] = context->is5_byte | context->part_processor_context.cache[context->part_processor_context.part_processor_index].is5_m2z;
			operand_enc->code_length = 1;
		}
	}
	return FCML_CEH_GEC_NO_ERROR;
}

/**************/
/* Pseudo-Op. */
/**************/

fcml_ceh_error fcml_ifn_asm_operand_acceptor_pseudo_op( fcml_ist_asm_encoding_context *context, fcml_ist_asm_addr_mode_desc_details *addr_mode_details, fcml_st_def_addr_mode_desc *addr_mode_desc, fcml_st_def_decoded_addr_mode *addr_mode, fcml_st_operand *operand_def, fcml_ist_asm_instruction_part *operand_enc ) {

    fcml_sf_def_tma_pseudo_op *pseudo_op_args = (fcml_sf_def_tma_pseudo_op*)addr_mode->addr_mode_args;
    fcml_bool is_pseudo_op = context->mnemonic->pseudo_op.is_not_null;

    if( operand_def->type == FCML_EOT_IMMEDIATE && !is_pseudo_op ) {

        /* IMM8 encoding is given directly in operand.*/
        fcml_st_integer destination;
        if( !fcml_ifn_asm_try_to_convert_integer_and_set_flag( &(operand_def->immediate), &destination, FCML_DS_8, FCML_DS_8, 0, NULL ) ) {
            return FCML_CEH_GEC_INVALID_OPPERAND;
        }

        if( destination.int8 & ( ~pseudo_op_args->mask ) ) {
        	fcml_ifn_ceh_asm_add_error_msg( context, fcml_fn_msg_get_message( FCML_MC_SEGMENT_INVALID_PSEUDO_OPCODE_IMM ), FCML_CEH_MEC_ERROR_INVALID_PSEUDO_OPCODE_VALUE );
            return FCML_CEH_GEC_INVALID_OPPERAND;
        }

    } else if ( !is_pseudo_op || operand_def->type != FCML_EOT_NONE ) {
        /* IMM8 is not available in operand, so its value should be given in mnemonic configuration. In such case, operand shouldn't exist.*/
        return FCML_CEH_GEC_INVALID_OPPERAND;
    }
    return FCML_CEH_GEC_NO_ERROR;
}

fcml_ceh_error fcml_ifn_asm_operand_encoder_pseudo_op( fcml_ien_asm_part_processor_phase phase, fcml_ist_asm_encoding_context *context, fcml_st_def_addr_mode_desc *addr_mode_desc, fcml_st_def_decoded_addr_mode *addr_mode, fcml_st_operand *operand_def, fcml_ist_asm_instruction_part *operand_enc ) {
	if( phase == FCML_IEN_ASM_IPPP_FIRST_PHASE ) {
		if( operand_def->type == FCML_EOT_IMMEDIATE ) {

			/* IMM8 encoding is given directly in operand.*/
			fcml_st_integer destination;
			if( !fcml_ifn_asm_try_to_convert_integer_and_set_flag( &(operand_def->immediate), &destination, FCML_DS_8, FCML_DS_8, 0, NULL ) ) {
				return FCML_CEH_GEC_INVALID_OPPERAND;
			}

			operand_enc->code[0] = destination.int8;

		} else if ( context->mnemonic->pseudo_op.is_not_null ) {
			/* IMM8 is not available in operand, so its value should be given in mnemonic configuration.*/
			operand_enc->code[0] = context->mnemonic->pseudo_op.value;
		}
		operand_enc->code_length = 1;
	}
    return FCML_CEH_GEC_NO_ERROR;
}

fcml_ist_asm_operand_encoder_def fcml_iarr_asm_def_operand_encoders[] = {
	{ NULL, NULL, NULL },
	{ fcml_ifn_asm_operand_encoder_imm, fcml_ifn_asm_operand_acceptor_imm, NULL },
	{ fcml_ifn_asm_operand_encoder_explicit_reg, fcml_ifn_asm_operand_acceptor_explicit_reg, NULL },
	{ fcml_ifn_asm_operand_encoder_opcode_reg, fcml_ifn_asm_operand_acceptor_opcode_reg, NULL },
	{ fcml_ifn_asm_operand_encoder_immediate_dis_relative, fcml_ifn_asm_operand_acceptor_immediate_dis_relative, NULL },
	{ fcml_ifn_asm_operand_encoder_far_pointer, fcml_ifn_asm_operand_acceptor_far_pointer, fcml_fn_hts_ihc_far_pointer },
	{ NULL, fcml_ifn_asm_operand_acceptor_explicit_gps_reg_addressing, NULL },
	{ fcml_ifn_asm_operand_encoder_explicit_ib, fcml_ifn_asm_operand_acceptor_explicit_ib, NULL },
	{ fcml_ifn_asm_operand_encoder_segment_relative_offset, fcml_ifn_asm_operand_acceptor_segment_relative_offset, NULL },
	{ fcml_ifn_asm_operand_encoder_rm, fcml_ifn_asm_operand_acceptor_rm, fcml_fn_hts_ihc_modrm_hints },
	{ fcml_ifn_asm_operand_encoder_r, fcml_ifn_asm_operand_acceptor_r, NULL },
	{ fcml_ifn_asm_operand_encoder_vex_vvvv, fcml_ifn_asm_operand_acceptor_vex_vvvv, NULL },
	{ fcml_ifn_asm_operand_encoder_isX, fcml_ifn_asm_operand_acceptor_isX, NULL },
	{ fcml_ifn_asm_operand_encoder_rm, fcml_ifn_asm_operand_acceptor_rm, NULL },
	{ fcml_ifn_asm_operand_encoder_pseudo_op, fcml_ifn_asm_operand_acceptor_pseudo_op, NULL }
};

/*************************
 * Instruction encoders. *
 *************************/

fcml_ceh_error fcml_ifn_asm_accept_addr_mode( fcml_ist_asm_encoding_context *context, fcml_ist_asm_instruction_addr_mode_encoding_details *addr_mode, fcml_st_instruction *instruction ) {

	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

#ifdef FCML_DEBUG
	FCML_TRACE( "Accepting addressing mode: %d", context->__def_index );
#endif

	int index = 0;

	fcml_ist_asm_instruction_part_processor_chain *current_processor = addr_mode->part_processor_chain;
	while( current_processor ) {
		context->last_ipp = index;
		fcml_ist_asm_instruction_part_processor_descriptor *descriptor = &(current_processor->processor_descriptor);
		context->part_processor_context.part_processor_index = index;
		if( !context->is_short_form || ( context->is_short_form && descriptor->is_short_form_supported ) ) {
            if( descriptor->processor_acceptor != NULL && ( error = descriptor->processor_acceptor( context, &(addr_mode->addr_mode_details), addr_mode->addr_mode_desc, instruction, descriptor->processor_args ) ) != FCML_CEH_GEC_NO_ERROR ) {
                FCML_TRACE( "Addressing mode not accepted. Acceptor failed: %d", index );
                return error;
            }
		}
		current_processor = current_processor->next_processor;
		index++;
	}

#ifdef FCML_DEBUG
	FCML_TRACE( "Accepted addressing mode %d - prefixes: 0x%04X, opcode: 0x%02X.", context->__def_index, addr_mode->addr_mode_desc->allowed_prefixes, addr_mode->addr_mode_desc->opcode_flags );
#endif

	return error;
}

/* All currently supported encoding phases. */
fcml_ien_asm_part_processor_phase fcml_iarr_asm_executed_phases[] = {
	FCML_IEN_ASM_IPPP_FIRST_PHASE,
	FCML_IEN_ASM_IPPP_SECOND_PHASE,
	FCML_IEN_ASM_IPPP_THIRD_PHASE
};

fcml_nuint8_t fcml_ifn_asm_calculate_instruction_parts_length( fcml_ist_asm_instruction_part *instruction_part, fcml_int parts_num ) {
	fcml_nuint8_t length = { 0, FCML_TRUE };
	while( parts_num-- > 0 ) {
		length.value += instruction_part++->code_length;
	}
	return length;
}

/* Responsible for assembling given addressing mode using attributes provided by context.*/
fcml_ceh_error fcml_ifn_asm_process_addr_mode( fcml_ist_asm_encoding_context *context, fcml_ist_asm_instruction_addr_mode_encoding_details *addr_mode, fcml_ist_asm_instruction_part_container *instruction_part_container ) {

	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

	/* Allocate instruction parts.*/
	fcml_ist_asm_instruction_part *instruction_part = (fcml_ist_asm_instruction_part*)fcml_fn_env_memory_alloc_clear(sizeof( fcml_ist_asm_instruction_part ) * addr_mode->instruction_parts );
	if( !instruction_part ) {
		return FCML_CEH_GEC_OUT_OF_MEMORY;
	}

	int i;
	for( i = 0; !error && i < sizeof( fcml_iarr_asm_executed_phases ) / sizeof( fcml_ien_asm_part_processor_phase ); i++ ) {
		fcml_ist_asm_instruction_part *current_instruction_part = instruction_part;
		fcml_ist_asm_instruction_part_processor_chain *current_processor = addr_mode->part_processor_chain;
		fcml_bool first = FCML_TRUE;
		int index = 0;
		while( current_processor ) {
			context->last_ipp = index;
			fcml_ist_asm_instruction_part_processor_descriptor *descriptor = &(current_processor->processor_descriptor);
			if( descriptor->processor_encoder && ( !context->is_short_form || ( context->is_short_form && descriptor->is_short_form_supported ) ) ) {
				if( !first && descriptor->processor_type == FCML_IEN_ASM_IPPT_ENCODER ) {
					current_instruction_part++;
				}
				first = FCML_FALSE;
				context->part_processor_context.part_processor_index = index;
				error = descriptor->processor_encoder( fcml_iarr_asm_executed_phases[i], context, &(addr_mode->addr_mode_details), addr_mode->addr_mode_desc, descriptor->processor_type == FCML_IEN_ASM_IPPT_VERIFIER ? NULL : current_instruction_part, descriptor->processor_args );
				if( error ) {
					/* Something failed.*/
					break;
				}
			}
			current_processor = current_processor->next_processor;
			index++;
		}
	}

	if( !error ) {

		/* Calculate instruction size.*/
		context->instruction_size = fcml_ifn_asm_calculate_instruction_parts_length( instruction_part, addr_mode->instruction_parts );

		fcml_bool recalculate_size = FCML_FALSE;

		/* Execute potential post processors.*/
		for( i = 0; i < addr_mode->instruction_parts; i++ ) {
			fcml_ist_asm_instruction_part *ip = &(instruction_part[i]);
			if( ip->post_processor ) {
				error = ip->post_processor( context, ip, ip->post_processor_args );
				if( error ) {
					break;
				}
				recalculate_size = FCML_TRUE;
			}
		}

		if( recalculate_size ) {
			context->instruction_size = fcml_ifn_asm_calculate_instruction_parts_length( instruction_part, addr_mode->instruction_parts );
		}

#ifdef FCML_DEBUG
		FCML_TRACE( "Proceeded addressing mode %d - prefixes: 0x%04X, opcode: 0x%02X (%s).", context->__def_index, addr_mode->addr_mode_desc->allowed_prefixes, addr_mode->addr_mode_desc->opcode_flags, fcml_idfn_asm_encode_size_flags( &(context->optimizer_processing_details) ) );
#endif
	} else {
#ifdef FCML_DEBUG
		FCML_TRACE( "Failed to process addressing mode %d - prefixes: 0x%04X, opcode: 0x%02X (%s).", context->__def_index, addr_mode->addr_mode_desc->allowed_prefixes, addr_mode->addr_mode_desc->opcode_flags, fcml_idfn_asm_encode_size_flags( &(context->optimizer_processing_details) ) );
#endif
	}

	if( error ) {
		fcml_fn_env_memory_free( instruction_part );
	} else {
		instruction_part_container->instruction_parts = instruction_part;
		instruction_part_container->count = addr_mode->instruction_parts;
	}

	return error;
}

void fcml_ifn_asm_assemble_instruction_parts( fcml_st_assembled_instruction *assembled_instruction, fcml_ist_asm_instruction_part_container *instruction_part_container ) {
	int i, count = instruction_part_container->count;
	int offset = 0;
	for( i = 0; i < count; i++ ) {
		fcml_ist_asm_instruction_part *part = &(instruction_part_container->instruction_parts[i]);
		if( part->code_length > 0 ) {
			fcml_fn_env_memory_copy( assembled_instruction->code + offset, part->code, part->code_length );
			offset += part->code_length;
		}
	}
	/* Just to be consequent.*/
	assembled_instruction->code_length = offset;
}

void fcml_ifn_asm_free_assembled_instruction( fcml_st_assembled_instruction *assembled_instruction ) {
	if( assembled_instruction ) {
		if( assembled_instruction->code ) {
			fcml_fn_env_memory_free( assembled_instruction->code );
		}
		fcml_fn_ceh_free_errors_only( &(assembled_instruction->warnings) );
		fcml_fn_env_memory_free( assembled_instruction );
	}
}

fcml_ceh_error fcml_ifn_asm_assemble_instruction( fcml_ist_asm_encoding_context *context, fcml_ist_asm_instruction_addr_mode_encoding_details *addr_mode, fcml_st_assembled_instruction **assembled_instruction ) {

	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

	fcml_ist_asm_instruction_part_container instruction_part_container = {0};

	/* Prepares encoded instruction parts. */
	error = fcml_ifn_asm_process_addr_mode( context, addr_mode, &instruction_part_container );

	/* Assemble instruction parts.*/
	if( !error ) {

		fcml_usize code_length = context->instruction_size.value;

		/* Allocate memory block for assembled code.*/
		fcml_st_assembled_instruction *asm_inst = (fcml_st_assembled_instruction*)fcml_fn_env_memory_alloc_clear( sizeof( fcml_st_assembled_instruction ) );
		if( asm_inst ) {
			asm_inst->code = (fcml_uint8_t*)fcml_fn_env_memory_alloc( code_length );
			if( asm_inst->code ) {
				asm_inst->code_length = code_length;
				/* Copies instruction parts to the destination code array. */
				fcml_ifn_asm_assemble_instruction_parts( asm_inst, &instruction_part_container );
				*assembled_instruction = asm_inst;
			} else {
				error = FCML_CEH_GEC_OUT_OF_MEMORY;
			}
		} else {
			error = FCML_CEH_GEC_OUT_OF_MEMORY;
		}

		if( error && asm_inst ) {
			fcml_fn_env_memory_free( asm_inst );
		}

	}

	/* Always free instruction parts when they are not needed anymore. */
	if( instruction_part_container.instruction_parts ) {
		fcml_fn_env_memory_free( instruction_part_container.instruction_parts );
	}

	return error;
}

/** Arguments passed through the optimization process. */
typedef struct fcml_ist_asm_enc_optimizer_callback_args {
	/** Currently processed addressing mode. */
	fcml_ist_asm_instruction_addr_mode_encoding_details *addr_mode;
	/** Encoding context instance. */
	fcml_ist_asm_encoding_context *context;
} fcml_ist_asm_enc_optimizer_callback_args;

/** Assembles instruction and puts it to the instructions chain. */
fcml_ceh_error fcml_ifn_asm_assemble_and_collect_instruction( fcml_ptr args ) {

	/* Restore important information from callback arguments.*/
	fcml_ist_asm_enc_optimizer_callback_args *callback_args = (fcml_ist_asm_enc_optimizer_callback_args*)args;
	fcml_ist_asm_encoding_context *context = callback_args->context;
	fcml_ist_asm_instruction_addr_mode_encoding_details *addr_mode = callback_args->addr_mode;
	fcml_st_asm_encoder_result *encoding_result = context->encoder_result;

	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

	fcml_st_assembled_instruction *assembled_instruction;

	error = fcml_ifn_asm_assemble_instruction( context, addr_mode, &assembled_instruction );
	if( !error ) {

		#ifdef FCML_DEBUG
			assembled_instruction->__def_index = context->__def_index;
		#endif

		fcml_bool ignore = FCML_FALSE;

		/* Check if such instruction has been already assembled. */
		fcml_st_assembled_instruction *instruction = encoding_result->instructions;
		while( instruction ) {
		    if( instruction->code_length == assembled_instruction->code_length && fcml_fn_env_memory_cmp( instruction->code, assembled_instruction->code, instruction->code_length ) ) {
		        /* Instructions are the same.*/
		        ignore = FCML_TRUE;
		        break;
		    }
		    instruction = instruction->next;
		}

		if( !ignore ) {

			/* Insert newly assembled instruction to the front of the instructions chain. */
			fcml_st_assembled_instruction *instructions = encoding_result->instructions;
			encoding_result->instructions = assembled_instruction;
			assembled_instruction->next = instructions;

			encoding_result->number_of_instructions++;

		} else {
		    /* Free ignored instruction.*/
		    fcml_ifn_asm_free_assembled_instruction( assembled_instruction );
		}
	}

	return error;
}

fcml_bool fcml_ifn_asm_accept_instruction_hints( fcml_hints addr_mode_dest_hints, fcml_hints instruction_hints ) {
	if( ( instruction_hints & FCML_HINT_INDIRECT_POINTER ) && !( addr_mode_dest_hints & FCML_HINT_INDIRECT_POINTER ) ) {
		FCML_TRACE_MSG("Addressing mode doesn't support indirect addressing.");
		return FCML_FALSE;
	}
	if( instruction_hints & FCML_HINT_FAR_POINTER ) {
		return addr_mode_dest_hints & FCML_HINT_FAR_POINTER;
	}
	if( instruction_hints & FCML_HINT_NEAR_POINTER ) {
		return addr_mode_dest_hints & FCML_HINT_NEAR_POINTER;
	}
	return FCML_TRUE;
}

void fcml_ifn_asm_set_attribute_size_flag_for_size( fcml_usize attribute_size, fcml_st_nullable_size_flags *flags ) {
    fcml_flags flag = 0;
    switch( attribute_size ) {
    case FCML_DS_16:
        flag = FCML_EN_ASF_16;
        break;
    case FCML_DS_32:
        flag = FCML_EN_ASF_32;
        break;
    case FCML_DS_64:
        flag = FCML_EN_ASF_64;
        break;
    }
    if( flag ) {
        flags->flags |= flag;
        flags->is_set = FCML_TRUE;
    }
}

void fcml_ifn_prepare_optimizer_context( fcml_st_asm_optimizer_context *optimizer_context, fcml_st_assembler_context *assembler_context ) {
	fcml_st_entry_point *entry_point = &(assembler_context->entry_point);
    optimizer_context->op_mode = entry_point->op_mode;
    optimizer_context->optimizer_flags = assembler_context->configuration.optimizer_flags;
    optimizer_context->asa = entry_point->address_size_attribute;
    optimizer_context->osa = entry_point->operand_size_attribute;
}

void fcml_ifn_chooser_extract( fcml_ptr instruction_ptr, fcml_st_instruction_code *instruction_code ) {
    if( instruction_ptr ) {
        fcml_st_assembled_instruction *instruction = (fcml_st_assembled_instruction*)instruction_ptr;
        instruction_code->code = instruction->code;
        instruction_code->code_length = instruction->code_length;
    }
}

fcml_ptr fcml_ifn_chooser_next( fcml_ptr instruction_ptr ) {
    if( instruction_ptr ) {
        fcml_st_assembled_instruction *instruction = (fcml_st_assembled_instruction*)instruction_ptr;
        return instruction->next;
    }
    return NULL;
}

void fcml_fcml_ifn_prepare_chooser_context( fcml_st_chooser_context *context, fcml_st_assembled_instruction *instructions ) {
    if( context ) {
        context->extract = &fcml_ifn_chooser_extract;
        context->next = &fcml_ifn_chooser_next;
        context->instruction = instructions;
    }
}

void fcml_ifn_prepare_optimizer_processing_details( fcml_st_asm_optimizer_processing_details *processing_details, fcml_ist_asm_instruction_addr_mode_encoding_details *addr_mode ) {

	/* Apply address attribute size restrictions from mnemonic definition.*/
	fcml_usize asa = addr_mode->mnemonic->supported_asa;
	processing_details->easa = asa;
	if( asa ) {
		fcml_ifn_asm_set_attribute_size_flag_for_size( asa, &(processing_details->allowed_easa) );
	}

	/* Apply operand attribute size restrictions from mnemonic definition.*/
	fcml_usize osa = addr_mode->mnemonic->supported_osa;
	processing_details->eosa = osa;
	if( osa ) {
		fcml_ifn_asm_set_attribute_size_flag_for_size( osa, &(processing_details->allowed_eosa) );
	}

	/* Apply L fields restrictions from mnemonic definition. */
	processing_details->l = addr_mode->mnemonic->l;

}

void fcml_ifn_asm_handle_addr_mode_errors( fcml_ist_asm_addr_mode_error *addr_mode_errors, fcml_st_ceh_error_container *addr_mode_error_container, fcml_ceh_error error_code, fcml_int ipp_failed, fcml_ist_addr_mode_processing_phase phase ) {

	fcml_bool choose_error = FCML_FALSE;

	/* Priorities are as follows: phase, number of failed ipp, error codes. */

	/* Phase. */
	if( phase == addr_mode_errors->phase ) {
		/* IPP ordinal. */
		if( ipp_failed == addr_mode_errors->ipp_failed ) {
			/* Error code. */
			fcml_ceh_error cec = addr_mode_errors->error_code;
			if( cec == FCML_CEH_GEC_NO_ERROR || ( cec == FCML_CEH_GEC_INVALID_OPPERAND && ( cec != error_code ) ) ) {
				choose_error = FCML_TRUE;
			}
		} else if( ipp_failed > addr_mode_errors->ipp_failed ) {
			choose_error = FCML_TRUE;
		}
	} else if( phase > addr_mode_errors->phase ) {
		choose_error = FCML_TRUE;
	}

	if( choose_error ) {
		/* Treat current error as most important one. */
		fcml_fn_ceh_free_errors_only( &(addr_mode_errors->addr_mode_errors) );
		addr_mode_errors->addr_mode_errors = *addr_mode_error_container;
		addr_mode_errors->error_code = error_code;
		addr_mode_errors->ipp_failed = ipp_failed;
		addr_mode_errors->phase = phase;
		addr_mode_error_container->errors = NULL;
		addr_mode_error_container->last_error = NULL;
	}

}

fcml_ceh_error fcml_ifn_asm_encode_addressing_mode_core( fcml_ist_asm_encoding_context *context, fcml_ist_asm_instruction_addr_mode_encoding_details *addr_mode, fcml_ist_asm_addr_mode_error *addr_mode_errors ) {

	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

	fcml_st_asm_optimizer_context optimizer_context = {0};

	fcml_st_ceh_error_container *global_error_container = context->error_container;

	/* Errors container for current processing. */
	fcml_st_ceh_error_container addr_mode_error_container = {0};

	context->error_container = &addr_mode_error_container;

	/* Check if addressing mode matches the hints, if there are any. */
	if( !context->instruction->hints || fcml_ifn_asm_accept_instruction_hints( addr_mode->hints, context->instruction->hints ) ) {

		error = fcml_ifn_asm_accept_addr_mode( context, addr_mode, context->instruction );

		if( !error ) {

			fcml_ist_asm_enc_optimizer_callback_args args;
			args.addr_mode = addr_mode;
			args.context = context;

			fcml_ifn_prepare_optimizer_context( &optimizer_context, context->assembler_context );

			/* Optimizer implementation can be provided by user. */
			fcml_fnp_asm_optimizer optimizer = context->assembler_context->configuration.optimizer;
			if( !optimizer ) {
				optimizer = &fcml_fn_asm_default_optimizer;
			}

			error = optimizer( &optimizer_context, &(context->optimizer_processing_details), fcml_ifn_asm_assemble_and_collect_instruction, &args );

		}

		if( error ) {
			/* Addressing mode hasn't been proceeded, so handle errors. */
			fcml_ifn_asm_handle_addr_mode_errors( addr_mode_errors, &addr_mode_error_container, error, context->last_ipp, FCML_AMPP_PROCESS );
		}

	} else {
		FCML_TRACE_MSG( "Addressing mode ignored due to hints incompatibility." );
	}

	/* Free errors stored in local container. See: fcml_ifn_asm_handle_addr_mode_errors function for more details
	 * about how they are handled.
	 */
	fcml_fn_ceh_free_errors_only( &addr_mode_error_container );

	context->error_container = global_error_container;

	return error;
}

fcml_ceh_error fcml_ifn_asm_instruction_encoder_IA( fcml_st_assembler_context *asm_context, fcml_st_dialect_context_int *dialect_context, fcml_st_instruction *instruction, fcml_st_asm_encoder_result *result, struct fcml_st_asm_instruction_addr_modes *addr_modes ) {

	/* Make a local copy of instruction because it still can be changed by preprocessor.*/
	fcml_st_instruction tmp_instruction = *instruction;

	/* Container for errors related to addressing mode processing. */
	fcml_ist_asm_addr_mode_error addr_mode_errors = {FCML_AMPP_UNDEFINED};

	fcml_ist_asm_encoding_context context = {0};
	context.assembler_context = asm_context;
	context.instruction = &tmp_instruction;
	context.encoder_result = result;

	/* Global errors container is set directly to error container from results. */
	context.error_container = &(result->errors);

	fcml_bool instruction_has_been_changed;

	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

	if( addr_modes ) {

		/* Check if there are any operands available. The short form can be used only if there are no operands set.*/
		fcml_bool no_operands = context.instruction->operands[0].type == FCML_EOT_NONE;

		/* Choose addressing mode.*/
		if( addr_modes->addr_modes->size ) {

			/* Gets first addressing mode available for chosen instruction definition. */
			fcml_st_coll_list_element *addr_mode_element = addr_modes->addr_modes->head;

#ifdef FCML_DEBUG
			int index = 0;
#endif
			/* This loop iterates through all available addressing modes one by one. */
			while( addr_mode_element ) {

				/* This flag is used by preprocessor to signal the fact that instruction has been changed. */
				instruction_has_been_changed = FCML_FALSE;

				error = FCML_CEH_GEC_NO_ERROR;

				fcml_ist_asm_instruction_addr_mode_encoding_details *addr_mode = (fcml_ist_asm_instruction_addr_mode_encoding_details*)addr_mode_element->item;

				/* Encoding context has to be prepared for new addressing mode because it is reused. */
				fcml_ifn_asm_clean_context( &context );

				/* Call instruction preprocessor again, passing found mnemonic definition this time.
				 * Parsed mnemonic can contain some dialect specific information, so we have to provide
				 * dialect a way to modify instruction definition basing on that information.
				 */
				fcml_fnp_asm_dialect_prepare_assembler_preprocessor assembler_preprocessor = dialect_context->assembler_preprocessor;
				if( assembler_preprocessor ) {
					assembler_preprocessor( (fcml_st_dialect*)dialect_context, &tmp_instruction, addr_mode->addr_mode_desc, addr_mode->mnemonic, &instruction_has_been_changed );
				}

				/* This information is necessary to ignore operands encoding process.*/

				/* Ignore all short forms if there are operands available.*/

				fcml_bool is_short_form = addr_mode->mnemonic->is_shortcut && no_operands;

				context.is_short_form = is_short_form;

				/* Prepare processing context for optimizer using currently used addressing mode. */
				fcml_ifn_prepare_optimizer_processing_details( &(context.optimizer_processing_details), addr_mode );

				/* Make it accessible through encoding context. Certain encoders might need this information. */
				context.mnemonic = addr_mode->mnemonic;

#ifdef FCML_DEBUG
				context.__def_index = index;
#endif

				/* Every addressing mode has its own data size calculators. */
				context.ds_calculator = addr_mode->addr_mode_details.ds_calculator;
				context.ds_calculator_args = addr_mode->addr_mode_details.ds_calculator_args;

				/* Try to encode prepared addressing mode. */
				error = fcml_ifn_asm_encode_addressing_mode_core( &context, addr_mode, &addr_mode_errors );

				addr_mode_element = addr_mode_element->next;

#ifdef FCML_DEBUG
				index++;
#endif
				/* Restore instruction if preprocessor has changed anything.*/
				if( instruction_has_been_changed ) {
					tmp_instruction = *instruction;
				}

			}

			/* Addressing modes related errors have higher priority than any others. */
			if( addr_mode_errors.addr_mode_errors.errors ) {

				/* There might be something collected before addressing mode
				 * processing took place, so is has to be free'd.
				 */
				fcml_fn_ceh_free_errors_only( context.error_container );

				*(context.error_container) = addr_mode_errors.addr_mode_errors;
			}

			/* Set current error code to the best error collected while
			 * processing addressing modes.
			 */
			if( addr_mode_errors.error_code ) {
				error = addr_mode_errors.error_code;
			}

			/* Check if there is at least one assembled instruction.*/
			if( result->number_of_instructions == 0 ) {

				/* Instruction has been found but can not be assembled in this form or addressing mode. */
				if( !error ) {
					/* Just in case. Use more general error code, but in theory it should
					 * never happened because acceptors and optimizers should return more
					 * accurate error codes.
					 */
					error = FCML_CEH_GEC_INVALID_INSTRUCTION_FORM;
				}

			} else {

				/* Assemblation succeed so free errors but leave warning as they are. */
				fcml_fn_ceh_free_errors_only_with_level( context.error_container, FCML_EN_CEH_EL_ERROR );

				/* Last error code should be also cleaned. */
				error = FCML_CEH_GEC_NO_ERROR;

			}

			if( !error ) {

				/* Choose instruction.*/
				fcml_fnp_asm_instruction_chooser chooser = asm_context->configuration.chooser;
				if( !chooser ) {
					chooser = &fcml_fn_asm_default_instruction_chooser;
				}

				if( result->number_of_instructions == 1 ) {

					/* There is only one instruction so chooser is not needed. */
					result->chosen_instruction = (fcml_st_assembled_instruction*)result->instructions;

				} else {

					/* Prepares chooser context. */
					fcml_st_chooser_context chooser_context;
					fcml_fcml_ifn_prepare_chooser_context( &chooser_context, result->instructions );

					/* Chooses most appropriate instruction. */
					result->chosen_instruction = (fcml_st_assembled_instruction*)chooser( &chooser_context );
				}

			}

		} else {
			FCML_TRACE_MSG( "There is no addressing mode for given instruction. It should never happened, so it's an internal bug." );
			error = FCML_CEH_GEC_INTERNAL_ERROR;
		}
	}

	return error;
}

/*****************************/
/* Processor part factories. */
/*****************************/

void fcml_ifn_asm_free_part_processor_chain( fcml_ist_asm_instruction_part_processor_chain *chain ) {
	if( chain ) {
		fcml_ifn_asm_free_part_processor_chain( chain->next_processor );
		fcml_ist_asm_instruction_part_processor_descriptor *descriptor = &(chain->processor_descriptor);
		if( descriptor->processor_args_deallocator ) {
			descriptor->processor_args_deallocator( descriptor->processor_args );
		}
		fcml_fn_env_memory_free( chain );
	}
}

/************************************/
/* Operand encoder wrapper factory. */
/************************************/

struct fcml_ist_asm_operand_encoder_wrapper_args {
	/* Decoder operand addressing.*/
	fcml_st_def_decoded_addr_mode *decoded_addr_mode;
	/* Operands acceptor.*/
	fcml_ifp_asm_operand_acceptor operand_acceptor;
	/* Function responsible for encoding operand.*/
	fcml_ifp_asm_operand_encoder operand_encoder;
	/* Index of the operand to encode.*/
	int operand_index;
	/* Operand hints.*/
	fcml_hints hints;
};

void fcml_ifn_asm_processor_operand_encoder_args_deallocator( fcml_ptr ptr ) {
	struct fcml_ist_asm_operand_encoder_wrapper_args *wrapper_wrgs = (struct fcml_ist_asm_operand_encoder_wrapper_args*)ptr;
	if( wrapper_wrgs->decoded_addr_mode ) {
		fcml_fnp_def_free_addr_mode( wrapper_wrgs->decoded_addr_mode );
	}
	fcml_fn_env_memory_free( wrapper_wrgs );
}

fcml_bool fcml_ifn_asm_accept_operand_hints( fcml_hints addr_mode_desc_operand_hints, fcml_hints operand_hints ) {
	if( ( operand_hints & FCML_OP_HINT_MULTIMEDIA_INSTRUCTION ) && !(addr_mode_desc_operand_hints & FCML_OP_HINT_MULTIMEDIA_INSTRUCTION) ) {
		return FCML_FALSE;
	}
	return FCML_TRUE;
}

fcml_ceh_error fcml_ifn_asm_instruction_part_processor_acceptor_operand_encoder_wrapper( fcml_ist_asm_encoding_context *context, fcml_ist_asm_addr_mode_desc_details *addr_mode_details, fcml_st_def_addr_mode_desc *addr_mode_desc, fcml_st_instruction *instruction, fcml_ptr args ) {
	struct fcml_ist_asm_operand_encoder_wrapper_args *wrapper_args = (struct fcml_ist_asm_operand_encoder_wrapper_args*)args;
	fcml_st_operand *operand = &(instruction->operands[wrapper_args->operand_index]);
	if( wrapper_args->operand_acceptor ) {
	    /* Check hints.*/
	    fcml_hints operand_hints = operand->hints;
	    if( !operand_hints || fcml_ifn_asm_accept_operand_hints( wrapper_args->hints, operand_hints ) ) {
	        return wrapper_args->operand_acceptor( context, addr_mode_details, addr_mode_desc, wrapper_args->decoded_addr_mode, operand, NULL );
	    } else {
	    	FCML_TRACE_MSG( "Hints do not match." );
	        return FCML_CEH_GEC_INVALID_OPPERAND;
	    }
	} else {
		/* This operand shouldn't be defined.*/
		if( instruction->operands[wrapper_args->operand_index].type != FCML_EOT_NONE ) {
			return FCML_CEH_GEC_INVALID_OPPERAND;
		}
		return FCML_CEH_GEC_NO_ERROR;
	}
}

fcml_ceh_error fcml_ifn_asm_instruction_part_processor_operand_encoder_wrapper( fcml_ien_asm_part_processor_phase phase, fcml_ist_asm_encoding_context *context, fcml_ist_asm_addr_mode_desc_details *addr_mode_details, fcml_st_def_addr_mode_desc *addr_mode_def, fcml_ist_asm_instruction_part *instruction_part, fcml_ptr args ) {
	struct fcml_ist_asm_operand_encoder_wrapper_args *wrapper_args = (struct fcml_ist_asm_operand_encoder_wrapper_args*)args;
	fcml_st_operand *operand = &(context->instruction->operands[wrapper_args->operand_index]);
	if( wrapper_args->operand_encoder ) {
		return wrapper_args->operand_encoder( phase, context, addr_mode_def, wrapper_args->decoded_addr_mode, operand, instruction_part );
	} else {
		return FCML_CEH_GEC_NO_ERROR;
	}
}

fcml_ist_asm_instruction_part_processor_descriptor fcml_ifn_asm_instruction_part_processor_factory_operand_encoder_wrapper( fcml_uint32_t flags, fcml_st_def_instruction_desc *instruction, fcml_st_def_addr_mode_desc *addr_mode, fcml_hints *hints, fcml_ceh_error *error ) {

	fcml_ist_asm_instruction_part_processor_descriptor descriptor = {0};

	struct fcml_ist_asm_operand_encoder_wrapper_args *wrapper_args = (struct fcml_ist_asm_operand_encoder_wrapper_args*)fcml_fn_env_memory_alloc_clear( sizeof( struct fcml_ist_asm_operand_encoder_wrapper_args ) );
	if( !wrapper_args ) {
		*error = FCML_CEH_GEC_OUT_OF_MEMORY;
		return descriptor;
	}

	if( addr_mode->opperands[flags] != FCML_NA ) {

		wrapper_args->decoded_addr_mode = fcml_fnp_def_decode_addr_mode_args( addr_mode->opperands[flags], error );
		if( *error ) {
			fcml_fn_env_memory_free( wrapper_args );
			return descriptor;
		}

		fcml_ist_asm_operand_encoder_def *encoders_def = &(fcml_iarr_asm_def_operand_encoders[wrapper_args->decoded_addr_mode->addr_mode]);
		wrapper_args->operand_encoder = encoders_def->encoder;
		wrapper_args->operand_acceptor = encoders_def->acceptor;

		if( encoders_def->hints_calculator ) {
			fcml_st_hts_calculated_hints calculated_hints = encoders_def->hints_calculator( addr_mode, wrapper_args->decoded_addr_mode );
			*hints |= calculated_hints.instruction_hints;
			wrapper_args->hints = calculated_hints.operand_hints;
		}

		descriptor.processor_type = FCML_IEN_ASM_IPPT_ENCODER;
	} else {
		descriptor.processor_type = FCML_IEN_ASM_IPPT_VERIFIER;
	}

	wrapper_args->operand_index = flags;

	descriptor.processor_args_deallocator = fcml_ifn_asm_processor_operand_encoder_args_deallocator;
	descriptor.processor_encoder = fcml_ifn_asm_instruction_part_processor_operand_encoder_wrapper;
	descriptor.processor_acceptor = fcml_ifn_asm_instruction_part_processor_acceptor_operand_encoder_wrapper;
	descriptor.processor_args = wrapper_args;

	return descriptor;
}

/***********************************/
/* XOP/VEX opcode encoder factory. */
/***********************************/

fcml_ceh_error fcml_ifn_asm_instruction_part_processor_XOP_VEX_opcode_encoder( fcml_ien_asm_part_processor_phase phase, fcml_ist_asm_encoding_context *context, fcml_ist_asm_addr_mode_desc_details *addr_mode_details, fcml_st_def_addr_mode_desc *addr_mode_def, fcml_ist_asm_instruction_part *instruction_part, fcml_ptr args ) {
	if( phase == FCML_IEN_ASM_IPPP_FIRST_PHASE ) {
		/* Encoder has to set some flags for XOP/VEX prefix encoder. */
		fcml_ist_asm_extension_prefixes_fields *epf = &(context->epf);
		int opcode_bytes = FCML_DEF_OPCODE_FLAGS_OPCODE_NUM( addr_mode_def->opcode_flags );
		int i = 0;
		int code_index = 0;
		fcml_uint8_t opcode_byte = addr_mode_def->opcode[i++];
		switch( opcode_byte ) {
		case 0x0F: {
			opcode_byte = addr_mode_def->opcode[i++];
			switch( opcode_byte ) {
			case 0x38:
				epf->mmmm = 0x02;
				break;
			case 0x3A:
				epf->mmmm = 0x03;
				break;
			default:
				instruction_part->code[code_index++] = opcode_byte;
				epf->mmmm = 0x01;
				break;
			}
			break;
		}
		case 0x08:
		case 0x09:
		case 0x0A:
			epf->mmmm = opcode_byte;
			break;
		}
		for( ; i < opcode_bytes; i++ ) {
			instruction_part->code[code_index++] = addr_mode_def->opcode[i];
		}
		instruction_part->code_length = code_index;
	}
	return  FCML_CEH_GEC_NO_ERROR;
}

fcml_ist_asm_instruction_part_processor_descriptor fcml_ifn_asm_instruction_part_processor_factory_XOP_VEX_opcode_encoder( fcml_uint32_t flags, fcml_st_def_instruction_desc *instruction, fcml_st_def_addr_mode_desc *addr_mode, fcml_hints *hints, fcml_ceh_error *error ) {
	fcml_ist_asm_instruction_part_processor_descriptor descriptor = {0};
	if( FCML_DEF_PREFIX_VEX_REQ( addr_mode->allowed_prefixes ) || FCML_DEF_PREFIX_XOP_REQ( addr_mode->allowed_prefixes ) ) {
		descriptor.processor_type = FCML_IEN_ASM_IPPT_ENCODER;
		descriptor.processor_args = NULL;
		descriptor.processor_encoder = fcml_ifn_asm_instruction_part_processor_XOP_VEX_opcode_encoder;
		descriptor.processor_acceptor = NULL;
	}
	return descriptor;
}

/***********************************/
/* Generic primary opcode encoder. */
/***********************************/

typedef fcml_uint8_t (*fcml_ifp_asm_primary_opcode_byte_encoder)( fcml_ist_asm_encoding_context *context, fcml_ist_asm_addr_mode_desc_details *addr_mode_details, fcml_st_def_addr_mode_desc *addr_mode_def, fcml_uint8_t opcode );

struct fcml_ist_opcode_byte_encoder_function_wrapper {
	fcml_ifp_asm_primary_opcode_byte_encoder opcode_byte_encoder;
};

fcml_ceh_error fcml_ifn_asm_instruction_part_processor_generic_primary_opcode_encoder( fcml_ien_asm_part_processor_phase phase, fcml_ist_asm_encoding_context *context, fcml_ist_asm_addr_mode_desc_details *addr_mode_details, fcml_st_def_addr_mode_desc *addr_mode_def, fcml_ist_asm_instruction_part *instruction_part, fcml_ptr args ) {
    if( phase == FCML_IEN_ASM_IPPP_SECOND_PHASE ) {
    	fcml_ifp_asm_primary_opcode_byte_encoder opcode_byte_encoder = NULL;
    	struct fcml_ist_opcode_byte_encoder_function_wrapper *wrapper = (struct fcml_ist_opcode_byte_encoder_function_wrapper*)args;
    	if( wrapper ) {
    		opcode_byte_encoder = wrapper->opcode_byte_encoder;
    	}
        int opcode_bytes = FCML_DEF_OPCODE_FLAGS_OPCODE_NUM( addr_mode_def->opcode_flags );
        int primary_opcode = FCML_DEF_OPCODE_FLAGS_PRIMARY_OPCODE( addr_mode_def->opcode_flags );
        int i;
        for( i = 0; i < opcode_bytes; i++ ) {
            fcml_uint8_t opcode_byte = addr_mode_def->opcode[i];
            instruction_part->code[i] = ( i == primary_opcode ) ? opcode_byte_encoder( context, addr_mode_details, addr_mode_def, opcode_byte ) : opcode_byte;
        }
        instruction_part->code_length = opcode_bytes;
    }
    return  FCML_CEH_GEC_NO_ERROR;
}

/**************************************************/
/* Opcode with condition encoded encoder factory. */
/**************************************************/

fcml_uint8_t fcml_ifp_asm_conditional_primary_opcode_byte_encoder( fcml_ist_asm_encoding_context *context, fcml_ist_asm_addr_mode_desc_details *addr_mode_details, fcml_st_def_addr_mode_desc *addr_mode_def, fcml_uint8_t opcode ) {
	return ( opcode + addr_mode_details->condition.condition_type * 2 + ( addr_mode_details->condition.is_negation ? 1 : 0 ) );
}

struct fcml_ist_opcode_byte_encoder_function_wrapper fcml_conditional_opcode_encoder_wrapper = {
	&fcml_ifp_asm_conditional_primary_opcode_byte_encoder
};

fcml_ist_asm_instruction_part_processor_descriptor fcml_ifn_asm_instruction_part_processor_factory_conditional_opcode_encoder( fcml_uint32_t flags, fcml_st_def_instruction_desc *instruction, fcml_st_def_addr_mode_desc *addr_mode, fcml_hints *hints, fcml_ceh_error *error ) {
    fcml_ist_asm_instruction_part_processor_descriptor descriptor = {0};
    if( FCML_DEF_OPCODE_FLAGS_OPCODE_FIELD_TTTN( addr_mode->opcode_flags ) ) {
        descriptor.processor_type = FCML_IEN_ASM_IPPT_ENCODER;
        descriptor.processor_args = &fcml_conditional_opcode_encoder_wrapper;
        descriptor.processor_encoder = fcml_ifn_asm_instruction_part_processor_generic_primary_opcode_encoder;
        descriptor.processor_acceptor = NULL;
    }
    return descriptor;
}

/**************************************************/
/* Opcode with register encoded encoder factory.  */
/**************************************************/

fcml_uint8_t fcml_ifp_asm_reg_primary_opcode_byte_encoder( fcml_ist_asm_encoding_context *context, fcml_ist_asm_addr_mode_desc_details *addr_mode_details, fcml_st_def_addr_mode_desc *addr_mode_def, fcml_uint8_t opcode ) {
	return opcode + context->opcode_reg.opcode_reg;
}

struct fcml_ist_opcode_byte_encoder_function_wrapper fcml_primary_opcode_encoder_wrapper = {
	&fcml_ifp_asm_reg_primary_opcode_byte_encoder
};

fcml_ist_asm_instruction_part_processor_descriptor fcml_ifn_asm_instruction_part_processor_factory_reg_opcode_encoder( fcml_uint32_t flags, fcml_st_def_instruction_desc *instruction, fcml_st_def_addr_mode_desc *addr_mode, fcml_hints *hints, fcml_ceh_error *error ) {
	fcml_ist_asm_instruction_part_processor_descriptor descriptor = {0};
	if( FCML_DEF_OPCODE_FLAGS_OPCODE_FIELD_REG( addr_mode->opcode_flags ) ) {
		descriptor.processor_type = FCML_IEN_ASM_IPPT_ENCODER;
		descriptor.processor_args = &fcml_primary_opcode_encoder_wrapper;
		descriptor.processor_encoder = fcml_ifn_asm_instruction_part_processor_generic_primary_opcode_encoder;
		descriptor.processor_acceptor = NULL;
	}
	return descriptor;
}

/**********************************/
/* Simple opcode encoder factory. */
/**********************************/

fcml_ceh_error fcml_ifn_asm_instruction_part_processor_simple_opcode_encoder( fcml_ien_asm_part_processor_phase phase, fcml_ist_asm_encoding_context *context, fcml_ist_asm_addr_mode_desc_details *addr_mode_details, fcml_st_def_addr_mode_desc *addr_mode_def, fcml_ist_asm_instruction_part *instruction_part, fcml_ptr args ) {
	if( phase == FCML_IEN_ASM_IPPP_FIRST_PHASE ) {
		int opcode_bytes = FCML_DEF_OPCODE_FLAGS_OPCODE_NUM( addr_mode_def->opcode_flags );
		int i;
		for( i = 0; i < opcode_bytes; i++ ) {
			instruction_part->code[i] = addr_mode_def->opcode[i];
		}
		instruction_part->code_length = opcode_bytes;
	}
	return  FCML_CEH_GEC_NO_ERROR;
}

fcml_ist_asm_instruction_part_processor_descriptor fcml_ifn_asm_instruction_part_processor_factory_simple_opcode_encoder( fcml_uint32_t flags, fcml_st_def_instruction_desc *instruction, fcml_st_def_addr_mode_desc *addr_mode, fcml_hints *hints, fcml_ceh_error *error ) {
	fcml_ist_asm_instruction_part_processor_descriptor descriptor = {0};
	descriptor.processor_type = FCML_IEN_ASM_IPPT_ENCODER;
	descriptor.processor_args = NULL;
	descriptor.processor_encoder = fcml_ifn_asm_instruction_part_processor_simple_opcode_encoder;
	descriptor.processor_acceptor = NULL;
	return descriptor;
}

/*******************/
/* Suffix encoder. */
/*******************/

fcml_ceh_error fcml_ifn_asm_instruction_part_processor_instruction_suffix_encoder( fcml_ien_asm_part_processor_phase phase, fcml_ist_asm_encoding_context *context, fcml_ist_asm_addr_mode_desc_details *addr_mode_details, fcml_st_def_addr_mode_desc *addr_mode_def, fcml_ist_asm_instruction_part *instruction_part, fcml_ptr args ) {
	if( phase == FCML_IEN_ASM_IPPP_FIRST_PHASE ) {
		if( context->mnemonic->suffix.is_not_null ) {
			instruction_part->code[0] = context->mnemonic->suffix.value;
			instruction_part->code_length = 1;
		}
	}
	return FCML_CEH_GEC_NO_ERROR;
}

fcml_ist_asm_instruction_part_processor_descriptor fcml_ifn_asm_instruction_part_processor_factory_suffix_encoder( fcml_uint32_t flags, fcml_st_def_instruction_desc *instruction, fcml_st_def_addr_mode_desc *addr_mode, fcml_hints *hints, fcml_ceh_error *error ) {
	fcml_ist_asm_instruction_part_processor_descriptor descriptor = {0};
	if( FCML_DEF_PREFIX_SUFFIX( addr_mode->allowed_prefixes ) ) {
		descriptor.processor_type = FCML_IEN_ASM_IPPT_ENCODER;
		descriptor.processor_args = NULL;
		descriptor.processor_encoder = fcml_ifn_asm_instruction_part_processor_instruction_suffix_encoder;
		descriptor.processor_acceptor = NULL;
	}
	return descriptor;
}

/*******************************/
/* Prefixes encoder factories. */
/*******************************/

/* Branch hints.*/

fcml_ceh_error fcml_ifn_asm_instruction_part_processor_branch_hints_prefix_encoder( fcml_ien_asm_part_processor_phase phase, fcml_ist_asm_encoding_context *context, fcml_ist_asm_addr_mode_desc_details *addr_mode_details, fcml_st_def_addr_mode_desc *addr_mode_def, fcml_ist_asm_instruction_part *instruction_part, fcml_ptr args ) {
    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
    if( phase == FCML_IEN_ASM_IPPP_THIRD_PHASE ) {
    	fcml_st_instruction *instruction = context->instruction;
        if( instruction->prefixes & FCML_PREFIX_BRANCH_HINT ) {
        	instruction_part->code[0] = 0x3E;
			instruction_part->code_length = 1;
        } else if( instruction->prefixes & FCML_PREFIX_NOBRANCH_HINT ) {
        	instruction_part->code[0] = 0x2E;
			instruction_part->code_length = 1;
        }
    }
    return error;
}

fcml_ist_asm_instruction_part_processor_descriptor fcml_ifn_asm_instruction_part_processor_factory_branch_hints_prefix_encoder( fcml_uint32_t flags, fcml_st_def_instruction_desc *instruction, fcml_st_def_addr_mode_desc *addr_mode, fcml_hints *hints, fcml_ceh_error *error ) {
    fcml_ist_asm_instruction_part_processor_descriptor descriptor = {0};
    /* Branch hints are allowed only for JCC instructions.*/
    if( instruction->instruction == F_JCC ) {
		descriptor.processor_type = FCML_IEN_ASM_IPPT_ENCODER;
		descriptor.processor_args = NULL;
		descriptor.processor_encoder = fcml_ifn_asm_instruction_part_processor_branch_hints_prefix_encoder;
		descriptor.processor_acceptor = NULL;
    }
    return descriptor;
}

/* REP prefix.*/

fcml_ceh_error fcml_ifn_asm_instruction_part_processor_rep_prefix_encoder( fcml_ien_asm_part_processor_phase phase, fcml_ist_asm_encoding_context *context, fcml_ist_asm_addr_mode_desc_details *addr_mode_details, fcml_st_def_addr_mode_desc *addr_mode_def, fcml_ist_asm_instruction_part *instruction_part, fcml_ptr args ) {
    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
    if( phase == FCML_IEN_ASM_IPPP_THIRD_PHASE ) {
        if( context->instruction->prefixes & FCML_PREFIX_REP ) {
			instruction_part->code[0] = 0xF3;
			instruction_part->code_length = 1;
        }
    }
    return error;
}

fcml_ist_asm_instruction_part_processor_descriptor fcml_ifn_asm_instruction_part_processor_factory_rep_prefix_encoder( fcml_uint32_t flags, fcml_st_def_instruction_desc *instruction, fcml_st_def_addr_mode_desc *addr_mode, fcml_hints *hints, fcml_ceh_error *error ) {
    fcml_ist_asm_instruction_part_processor_descriptor descriptor = {0};
    if( FCML_DEF_PREFIX_REP_XRELEASE_ALLOWED( addr_mode->allowed_prefixes ) && !FCML_DEF_PREFIX_HLE_ENABLED( addr_mode->allowed_prefixes ) ) {
		descriptor.processor_type = FCML_IEN_ASM_IPPT_ENCODER;
		descriptor.processor_args = NULL;
		descriptor.processor_encoder = fcml_ifn_asm_instruction_part_processor_rep_prefix_encoder;
		descriptor.processor_acceptor = NULL;
    }
    return descriptor;
}

/* REPNE prefix.*/

fcml_ceh_error fcml_ifn_asm_instruction_part_processor_repne_prefix_encoder( fcml_ien_asm_part_processor_phase phase, fcml_ist_asm_encoding_context *context, fcml_ist_asm_addr_mode_desc_details *addr_mode_details, fcml_st_def_addr_mode_desc *addr_mode_def, fcml_ist_asm_instruction_part *instruction_part, fcml_ptr args ) {
    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
    if( phase == FCML_IEN_ASM_IPPP_THIRD_PHASE ) {
        if( context->instruction->prefixes & FCML_PREFIX_REPNE ) {
			instruction_part->code[0] = 0xF2;
			instruction_part->code_length = 1;
        }
    }
    return error;
}

fcml_ist_asm_instruction_part_processor_descriptor fcml_ifn_asm_instruction_part_processor_factory_repne_prefix_encoder( fcml_uint32_t flags, fcml_st_def_instruction_desc *instruction, fcml_st_def_addr_mode_desc *addr_mode, fcml_hints *hints, fcml_ceh_error *error ) {
    fcml_ist_asm_instruction_part_processor_descriptor descriptor = {0};
    if( FCML_DEF_PREFIX_REPNE_XACQUIRE_ALLOWED( addr_mode->allowed_prefixes ) && !FCML_DEF_PREFIX_HLE_ENABLED( addr_mode->allowed_prefixes ) ) {
		descriptor.processor_type = FCML_IEN_ASM_IPPT_ENCODER;
		descriptor.processor_args = NULL;
		descriptor.processor_encoder = fcml_ifn_asm_instruction_part_processor_repne_prefix_encoder;
		descriptor.processor_acceptor = NULL;
    }
    return descriptor;
}

/* HLE prefixes.*/

fcml_ceh_error fcml_ifn_asm_instruction_part_processor_hle_prefixes_prefix_encoder( fcml_ien_asm_part_processor_phase phase, fcml_ist_asm_encoding_context *context, fcml_ist_asm_addr_mode_desc_details *addr_mode_details, fcml_st_def_addr_mode_desc *addr_mode_def, fcml_ist_asm_instruction_part *instruction_part, fcml_ptr args ) {
    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
    if( phase == FCML_IEN_ASM_IPPP_THIRD_PHASE ) {
    	fcml_bool found = FCML_FALSE;
        if( context->instruction->prefixes & FCML_PREFIX_XACQUIRE ) {
        	if( FCML_DEF_PREFIX_REPNE_XACQUIRE_ALLOWED( addr_mode_def->allowed_prefixes ) ) {
				instruction_part->code[0] = 0xF2;
				instruction_part->code_length = 1;
				found = FCML_TRUE;
        	} else {
        		fcml_ifn_ceh_asm_add_error_msg( context, fcml_fn_msg_get_message( FCML_MC_SEGMENT_HLE_PREFIXES_NOT_ALLOWED ), FCML_CEH_MEC_ERROR_HLE_PREFIX_NOT_ALLOWED );
        		return FCML_CEH_GEC_INVALID_PREFIX;
        	}
        }
        if( context->instruction->prefixes & FCML_PREFIX_XRELEASE ) {
        	if( found ) {
        		/* Only one HLA prefix is allowed for instruction.*/
        		fcml_ifn_ceh_asm_add_error_msg( context, fcml_fn_msg_get_message( FCML_MC_SEGMENT_HLE_MORE_THAN_ONE_PREFIX ), FCML_CEH_MEC_ERROR_HLE_MORE_THAN_ONE_PREFIX );
        		return FCML_CEH_GEC_INVALID_PREFIX;
        	}
        	if( FCML_DEF_PREFIX_REP_XRELEASE_ALLOWED( addr_mode_def->allowed_prefixes ) ) {
				instruction_part->code[0] = 0xF3;
				instruction_part->code_length = 1;
        	} else {
        		fcml_ifn_ceh_asm_add_error_msg( context, fcml_fn_msg_get_message( FCML_MC_SEGMENT_HLE_PREFIXES_NOT_ALLOWED ), FCML_CEH_MEC_ERROR_HLE_PREFIX_NOT_ALLOWED );
        		return FCML_CEH_GEC_INVALID_PREFIX;
        	}
		}
    }
    return error;
}

fcml_ist_asm_instruction_part_processor_descriptor fcml_ifn_asm_instruction_part_processor_factory_hle_prefixes_encoder( fcml_uint32_t flags, fcml_st_def_instruction_desc *instruction, fcml_st_def_addr_mode_desc *addr_mode, fcml_hints *hints, fcml_ceh_error *error ) {
    fcml_ist_asm_instruction_part_processor_descriptor descriptor = {0};
    if( FCML_DEF_PREFIX_HLE_ENABLED( addr_mode->allowed_prefixes ) ) {
		descriptor.processor_type = FCML_IEN_ASM_IPPT_ENCODER;
		descriptor.processor_args = NULL;
		descriptor.processor_encoder = fcml_ifn_asm_instruction_part_processor_hle_prefixes_prefix_encoder;
		descriptor.processor_acceptor = NULL;
    }
    return descriptor;
}

/* Lock prefix.*/

fcml_ceh_error fcml_ifn_asm_instruction_part_processor_lock_prefix_encoder( fcml_ien_asm_part_processor_phase phase, fcml_ist_asm_encoding_context *context, fcml_ist_asm_addr_mode_desc_details *addr_mode_details, fcml_st_def_addr_mode_desc *addr_mode_def, fcml_ist_asm_instruction_part *instruction_part, fcml_ptr args ) {
    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
    if( phase == FCML_IEN_ASM_IPPP_THIRD_PHASE ) {
    	/* For instruction that supports LOCK prefixes as well as HLA ones,*/
    	/* LOCK prefix is mandatory. XCHG is only one exception from that rule, and in its case*/
    	/* lock prefix can be ignored.*/
    	if( FCML_DEF_PREFIX_HLE_ENABLED( addr_mode_def->allowed_prefixes ) && ( ( context->instruction->prefixes & FCML_PREFIX_XACQUIRE ) || ( context->instruction->prefixes & FCML_PREFIX_XRELEASE ) ) ) {
    		if( !( context->instruction->prefixes & FCML_PREFIX_LOCK ) ) {
    			/* XCHG instruction do not need LOCK prefix.*/
    			if( addr_mode_def->opcode[0] != 0x86 && addr_mode_def->opcode[0] != 0x87 ) {
    				return FCML_CEH_GEC_INVALID_PREFIX;
    			}
    		}
    	}
        if( context->instruction->prefixes & FCML_PREFIX_LOCK ) {
			instruction_part->code[0] = 0xF0;
			instruction_part->code_length = 1;
        }
    }
    return error;
}

fcml_ist_asm_instruction_part_processor_descriptor fcml_ifn_asm_instruction_part_processor_factory_lock_prefix_encoder( fcml_uint32_t flags, fcml_st_def_instruction_desc *instruction, fcml_st_def_addr_mode_desc *addr_mode, fcml_hints *hints, fcml_ceh_error *error ) {
    fcml_ist_asm_instruction_part_processor_descriptor descriptor = {0};
    if( FCML_DEF_PREFIX_LOCK_ALLOWED( addr_mode->allowed_prefixes ) ) {
		descriptor.processor_type = FCML_IEN_ASM_IPPT_ENCODER;
		descriptor.processor_args = NULL;
		descriptor.processor_encoder = fcml_ifn_asm_instruction_part_processor_lock_prefix_encoder;
		descriptor.processor_acceptor = NULL;
    }
    return descriptor;
}

/* Segment override prefix.*/

fcml_uint8_t fcml_iarr_asm_prefix_override_mapping[] = {
    0x26,
    0x2e,
    0x36,
    0x3e,
    0x64,
    0x65
};

fcml_ceh_error fcml_ifn_asm_instruction_part_processor_segment_override_prefix_encoder( fcml_ien_asm_part_processor_phase phase, fcml_ist_asm_encoding_context *context, fcml_ist_asm_addr_mode_desc_details *addr_mode_details, fcml_st_def_addr_mode_desc *addr_mode_def, fcml_ist_asm_instruction_part *instruction_part, fcml_ptr args ) {
    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
    if( phase == FCML_IEN_ASM_IPPP_THIRD_PHASE ) {
        if( context->segment_override.type == FCML_REG_SEG ) {
            fcml_uint8_t seg_reg_num = context->segment_override.reg;
            if( seg_reg_num <= 5) {
                instruction_part->code[0] = fcml_iarr_asm_prefix_override_mapping[ seg_reg_num ];
                instruction_part->code_length = 1;
            } else {
            	/* Wrong register type. This check is done just is case, this code should never be invoked due to earlier sanity checks. */
            	FCML_TRACE_MSG( "Unknown segment register found." );
                error = FCML_CEH_GEC_INTERNAL_ERROR;
            }
        }
    }
    return error;
}

fcml_ist_asm_instruction_part_processor_descriptor fcml_ifn_asm_instruction_part_processor_factory_segment_override_prefix_encoder( fcml_uint32_t flags, fcml_st_def_instruction_desc *instruction, fcml_st_def_addr_mode_desc *addr_mode, fcml_hints *hints, fcml_ceh_error *error ) {
    fcml_ist_asm_instruction_part_processor_descriptor descriptor = {0};
    descriptor.processor_type = FCML_IEN_ASM_IPPT_ENCODER;
    descriptor.processor_args = NULL;
    descriptor.processor_encoder = fcml_ifn_asm_instruction_part_processor_segment_override_prefix_encoder;
    descriptor.processor_acceptor = NULL;
    return descriptor;
}

/* Mandatory prefixes.*/

fcml_ceh_error fcml_ifn_asm_instruction_part_processor_mandatory_prefixes_encoder( fcml_ien_asm_part_processor_phase phase, fcml_ist_asm_encoding_context *context, fcml_ist_asm_addr_mode_desc_details *addr_mode_details, fcml_st_def_addr_mode_desc *addr_mode_def, fcml_ist_asm_instruction_part *instruction_part, fcml_ptr args ) {
	if( phase == FCML_IEN_ASM_IPPP_THIRD_PHASE ) {
		fcml_uint8_t prefix = 0x66;
		if( FCML_DEF_PREFIX_MANDATORY_F2( addr_mode_def->allowed_prefixes ) ) {
			prefix = 0xF2;
		} else if( FCML_DEF_PREFIX_MANDATORY_F3( addr_mode_def->allowed_prefixes ) ) {
			prefix = 0xF3;
		}
		instruction_part->code[0] = prefix;
		instruction_part->code_length = 1;
	}
	return FCML_CEH_GEC_NO_ERROR;
}

fcml_ist_asm_instruction_part_processor_descriptor fcml_ifn_asm_instruction_part_processor_factory_mandatory_prefixes_encoder( fcml_uint32_t flags, fcml_st_def_instruction_desc *instruction, fcml_st_def_addr_mode_desc *addr_mode, fcml_hints *hints, fcml_ceh_error *error ) {
	fcml_ist_asm_instruction_part_processor_descriptor descriptor = {0};
	fcml_bool is_mandatory = FCML_DEF_PREFIX_MANDATORY_66( addr_mode->allowed_prefixes ) || FCML_DEF_PREFIX_MANDATORY_F2( addr_mode->allowed_prefixes ) || FCML_DEF_PREFIX_MANDATORY_F3( addr_mode->allowed_prefixes );
	/* Mandatory prefixes can be applied to instructions without neither XOP nor VEX prefixes.*/
	if( is_mandatory && !FCML_DEF_PREFIX_VEX_REQ( addr_mode->allowed_prefixes ) && !FCML_DEF_PREFIX_XOP_REQ( addr_mode->allowed_prefixes ) ) {
		descriptor.processor_type = FCML_IEN_ASM_IPPT_ENCODER;
		descriptor.processor_args = NULL;
		descriptor.processor_encoder = fcml_ifn_asm_instruction_part_processor_mandatory_prefixes_encoder;
		descriptor.processor_acceptor = NULL;
	}
	return descriptor;
}

/* 66 prefix.*/

fcml_ceh_error fcml_ifn_asm_instruction_part_processor_66_prefix_encoder( fcml_ien_asm_part_processor_phase phase, fcml_ist_asm_encoding_context *context, fcml_ist_asm_addr_mode_desc_details *addr_mode_details, fcml_st_def_addr_mode_desc *addr_mode_def, fcml_ist_asm_instruction_part *instruction_part, fcml_ptr args ) {
	if( phase == FCML_IEN_ASM_IPPP_THIRD_PHASE ) {
		fcml_bool encode = FCML_FALSE;
		fcml_uint64_t addr_type = addr_mode_def->instruction_group;
		/* Mandatory 0x66 prefix is encoded in different way in case of VEX encoded instructions.*/
		if( !( addr_type & FCML_AMT_VEXx ) ) {
            if( FCML_DEF_PREFIX_MANDATORY_66( addr_mode_def->allowed_prefixes ) ) {
                encode = FCML_TRUE;
			/* SIMD instructions do not need 0x66 to change EOSA.*/
            } else if ( !( addr_type & FCML_AMT_SIMD ) ) {
            	fcml_st_entry_point *entry_point = &(context->assembler_context->entry_point);
            	encode =
					( entry_point->operand_size_attribute == FCML_DS_16 && context->optimizer_processing_details.eosa == FCML_DS_32 ) ||
					( entry_point->operand_size_attribute == FCML_DS_32 && context->optimizer_processing_details.eosa == FCML_DS_16 ) ||
					( entry_point->operand_size_attribute == FCML_DS_64 && context->optimizer_processing_details.eosa == FCML_DS_32 );
            }
            if( encode ) {
                instruction_part->code[0] = 0x66;
                instruction_part->code_length = 1;
            }
		}
	}
	return FCML_CEH_GEC_NO_ERROR;
}

fcml_ist_asm_instruction_part_processor_descriptor fcml_ifn_asm_instruction_part_processor_factory_66_prefix_encoder( fcml_uint32_t flags, fcml_st_def_instruction_desc *instruction, fcml_st_def_addr_mode_desc *addr_mode, fcml_hints *hints, fcml_ceh_error *error ) {
	fcml_ist_asm_instruction_part_processor_descriptor descriptor = {0};
	/* Mandatory prefixes are handled by dedicated IPP.*/
	if( !FCML_DEF_PREFIX_MANDATORY_66( addr_mode->allowed_prefixes ) && !FCML_DEF_PREFIX_VEX_REQ( addr_mode->allowed_prefixes ) && !FCML_DEF_PREFIX_XOP_REQ( addr_mode->allowed_prefixes ) ) {
		descriptor.processor_type = FCML_IEN_ASM_IPPT_ENCODER;
		descriptor.processor_args = NULL;
		descriptor.processor_encoder = fcml_ifn_asm_instruction_part_processor_66_prefix_encoder;
		descriptor.processor_acceptor = NULL;
	}
	return descriptor;
}

/* 67 prefix. */

fcml_ceh_error fcml_ifn_asm_instruction_part_processor_67_prefix_encoder( fcml_ien_asm_part_processor_phase phase, fcml_ist_asm_encoding_context *context, fcml_ist_asm_addr_mode_desc_details *addr_mode_details, fcml_st_def_addr_mode_desc *addr_mode_def, fcml_ist_asm_instruction_part *instruction_part, fcml_ptr args ) {

	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

	if( phase == FCML_IEN_ASM_IPPP_THIRD_PHASE ) {
	    /* If effective address size is not set, it means that instruction is not interested in ASA and just doesn't use it.*/
		fcml_st_entry_point *entry_point = &(context->assembler_context->entry_point);
		if( context->optimizer_processing_details.easa && ( entry_point->address_size_attribute != context->optimizer_processing_details.easa ) ) {
			fcml_bool encode =
				( entry_point->address_size_attribute == FCML_DS_16 && context->optimizer_processing_details.easa == FCML_DS_32 ) ||
				( entry_point->address_size_attribute == FCML_DS_32 && context->optimizer_processing_details.easa == FCML_DS_16 ) ||
				( entry_point->address_size_attribute == FCML_DS_64 && context->optimizer_processing_details.easa == FCML_DS_32 );
			if( encode ) {
				instruction_part->code[0] = 0x67;
				instruction_part->code_length = 1;
			} else {
				error = FCML_CEH_GEC_INVALID_ADDRESS_SIZE;
			}
		}
	}

	return error;
}

fcml_ist_asm_instruction_part_processor_descriptor fcml_ifn_asm_instruction_part_processor_factory_67_prefix_encoder( fcml_uint32_t flags, fcml_st_def_instruction_desc *instruction, fcml_st_def_addr_mode_desc *addr_mode, fcml_hints *hints, fcml_ceh_error *error ) {

	fcml_ist_asm_instruction_part_processor_descriptor descriptor = {0};

	/* 67 prefix can be applied to instructions without neither XOP nor VEX prefixes.*/
	if( !FCML_DEF_PREFIX_VEX_REQ( addr_mode->allowed_prefixes ) && !FCML_DEF_PREFIX_XOP_REQ( addr_mode->allowed_prefixes ) ) {
		descriptor.processor_type = FCML_IEN_ASM_IPPT_ENCODER;
		descriptor.processor_args = NULL;
		descriptor.processor_encoder = fcml_ifn_asm_instruction_part_processor_67_prefix_encoder;
		descriptor.processor_acceptor = NULL;
	}

	return descriptor;
}

/********************/
/** VEX/XOP Prefix **/
/********************/

fcml_ceh_error fcml_ifn_asm_instruction_part_processor_VEX_XOP_prefix_encoder( fcml_ien_asm_part_processor_phase phase, fcml_ist_asm_encoding_context *context, fcml_ist_asm_addr_mode_desc_details *addr_mode_details, fcml_st_def_addr_mode_desc *addr_mode_def, fcml_ist_asm_instruction_part *instruction_part, fcml_ptr args ) {

	if( phase == FCML_IEN_ASM_IPPP_FIRST_PHASE ) {

		if( FCML_DEF_PREFIX_L_1( addr_mode_def->allowed_prefixes ) ) {
			context->optimizer_processing_details.l.is_not_null = FCML_TRUE;
			context->optimizer_processing_details.l.value = 0x01;
		} else if ( FCML_DEF_PREFIX_L_0( addr_mode_def->allowed_prefixes ) ) {
			context->optimizer_processing_details.l.is_not_null = FCML_TRUE;
			context->optimizer_processing_details.l.value = 0x00;
		}

	} if( phase == FCML_IEN_ASM_IPPP_THIRD_PHASE ) {

		fcml_ist_asm_extension_prefixes_fields *epf = &(context->epf);
		fcml_st_encoded_modrm *encoded_mod_rm = &(context->encoded_mod_rm);

		/* Check if one byte VEX encoding can be used.*/
		fcml_bool is_vex = FCML_DEF_PREFIX_VEX_REQ( addr_mode_def->allowed_prefixes );

		/* Remember, the 2-byte VEX implies a leading 0Fh opcode byte, it's why "m-mmmm" field should be 1.*/
		fcml_bool is_two_bytes_vex = ( !context->assembler_context->configuration.force_three_byte_VEX && is_vex && epf->mmmm == 0x01 && !FCML_DEF_PREFIX_W_1( addr_mode_def->allowed_prefixes ) && !encoded_mod_rm->ext_x && !encoded_mod_rm->ext_b );

		fcml_uint8_t prefix_bytes[3];
		fcml_uint8_t prefix_size = 0;

		/* Encode PP.*/
		fcml_uint8_t pp = 0;
		if( FCML_DEF_PREFIX_MANDATORY_66( addr_mode_def->allowed_prefixes ) ) {
			pp = 0x01;
		} else if( FCML_DEF_PREFIX_MANDATORY_F2( addr_mode_def->allowed_prefixes ) ) {
			pp = 0x03;
		} else if( FCML_DEF_PREFIX_MANDATORY_F3( addr_mode_def->allowed_prefixes ) ) {
			pp = 0x02;
		}

		fcml_uint8_t prefix = 0;

		/* If an instruction syntax can be encoded using the two-byte form, it can also be encoded using the three byte form of VEX.*/
		/* Three byte VEX can be forced using configuration or "long_form" instruction level hint.*/
		if( context->assembler_context->configuration.force_three_byte_VEX || ( context->instruction->hints & FCML_HINT_LONG_FORM_POINTER ) ) {
			is_two_bytes_vex = FCML_FALSE;
		}

		if( is_two_bytes_vex ) {
			/* Two bytes VEX prefix.*/
			prefix = FCML_ENCODE_VEXOP_R( prefix, encoded_mod_rm->ext_r );
			prefix = FCML_ENCODE_VEXOP_VVVV( prefix, epf->vvvv );
			if( context->optimizer_processing_details.l.is_not_null ) {
				prefix = FCML_ENCODE_VEXOP_L( prefix, context->optimizer_processing_details.l.value );
			}
			prefix = FCML_ENCODE_VEXOP_PP( prefix, pp );
			prefix_bytes[0] = 0xC5;
			prefix_bytes[1] = prefix;
			prefix_size = 2;
		} else {
			/* Three bytes VEX or XOP prefix. */
			prefix_bytes[0] = ( is_vex ) ? 0xC4 : 0x8F;
			prefix = FCML_ENCODE_VEXOP_R( prefix, encoded_mod_rm->ext_r );
			prefix = FCML_ENCODE_VEXOP_X( prefix, encoded_mod_rm->ext_x );
			prefix = FCML_ENCODE_VEXOP_B( prefix, encoded_mod_rm->ext_b );
			prefix = FCML_ENCODE_VEXOP_MMMM( prefix, epf->mmmm );
			prefix_bytes[1] = prefix;
			prefix = 0;
			prefix = FCML_ENCODE_VEXOP_W( prefix, FCML_DEF_PREFIX_W_1( addr_mode_def->allowed_prefixes ) );
			prefix = FCML_ENCODE_VEXOP_VVVV( prefix, epf->vvvv );
			if( context->optimizer_processing_details.l.is_not_null ) {
				prefix = FCML_ENCODE_VEXOP_L( prefix, context->optimizer_processing_details.l.value );
			}
			prefix = FCML_ENCODE_VEXOP_PP( prefix, pp );
			prefix_bytes[2] = prefix;
			prefix_size = 3;
		}

		int i;
		for( i = 0; i < prefix_size; i++ ) {
			instruction_part->code[i] = prefix_bytes[i];
		}
		instruction_part->code_length = prefix_size;

	}

	return FCML_CEH_GEC_NO_ERROR;
}

fcml_ist_asm_instruction_part_processor_descriptor fcml_ifn_asm_instruction_part_processor_factory_VEX_XOP_prefix_encoder( fcml_uint32_t flags, fcml_st_def_instruction_desc *instruction, fcml_st_def_addr_mode_desc *addr_mode, fcml_hints *hints, fcml_ceh_error *error ) {
	fcml_ist_asm_instruction_part_processor_descriptor descriptor = {0};
	if( FCML_DEF_PREFIX_VEX_REQ( addr_mode->allowed_prefixes ) || FCML_DEF_PREFIX_XOP_REQ( addr_mode->allowed_prefixes ) ) {
		descriptor.processor_type = FCML_IEN_ASM_IPPT_ENCODER;
		descriptor.processor_args = NULL;
		descriptor.processor_encoder = fcml_ifn_asm_instruction_part_processor_VEX_XOP_prefix_encoder;
		descriptor.processor_acceptor = NULL;
	}
	return descriptor;
}

/* REX prefix.*/

fcml_ceh_error fcml_ifn_asm_instruction_part_processor_REX_prefix_encoder( fcml_ien_asm_part_processor_phase phase, fcml_ist_asm_encoding_context *context, fcml_ist_asm_addr_mode_desc_details *addr_mode_details, fcml_st_def_addr_mode_desc *addr_mode_def, fcml_ist_asm_instruction_part *instruction_part, fcml_ptr args ) {

	if( phase == FCML_IEN_ASM_IPPP_FIRST_PHASE ) {

		if( FCML_DEF_PREFIX_W_1( addr_mode_def->allowed_prefixes ) ) {
			context->optimizer_processing_details.eosa = FCML_DS_64;
		}

	} if( phase == FCML_IEN_ASM_IPPP_THIRD_PHASE ) {

		/* REX prefix is only available in 64 bit mode. Neither VEX nor XOP are allowed here,*/
		/* but it's checked before this encoder is registered for*/
		if( context->assembler_context->entry_point.op_mode == FCML_AF_64_BIT ) {

			fcml_uint8_t rex = FCML_ENCODE_REX_BASE;

			fcml_st_asm_optimizer_processing_details *size_flags = &(context->optimizer_processing_details);
			fcml_st_encoded_modrm *encoded_mod_rm = &(context->encoded_mod_rm);
			fcml_st_modrm *mod_rm = &(context->mod_rm);

			/* W field.*/
			fcml_usize eosa = size_flags->eosa;
			if( FCML_DEF_PREFIX_W_1( addr_mode_def->allowed_prefixes ) ) {
				if( eosa != 0 && eosa != FCML_DS_64  ) {
					/* Operand size should be 64 bits.*/
					return FCML_CEH_GEC_INVALID_OPPERAND_SIZE;
				}
				rex = FCML_ENCODE_REX_W( rex, 1 );
			} else if( eosa == FCML_DS_64 && !FCML_DEF_OPCODE_FLAGS_FORCE_64BITS_EOSA( addr_mode_def->opcode_flags ) && !FCML_DEF_OPCODE_FLAGS_64BITS_EOSA_BY_DEFAULT( addr_mode_def->opcode_flags ) ) {
			    /* When OSA is forced to 64 bits, W flag is needless.*/
				rex = FCML_ENCODE_REX_W( rex, 1 );
			}

			/* Fields.*/
			rex = FCML_ENCODE_REX_R( rex, encoded_mod_rm->ext_r );
			rex = FCML_ENCODE_REX_X( rex, encoded_mod_rm->ext_x );
			rex = FCML_ENCODE_REX_B( rex, encoded_mod_rm->ext_b );
			rex = FCML_ENCODE_REX_B( rex, context->opcode_reg.ext_b );

			/* Assembler configuration.*/
			fcml_st_assembler_conf *cfg = &(context->assembler_context->configuration);

			/* Even if REX do not contains any flags set in some cases registers BPL, SPL, DIL, SIL needs REX to be defined.*/
			/* Additionally we can force it to occur by setting a configuration flag.*/
			if( rex != FCML_ENCODE_REX_BASE || ( FCML_DEF_OPCODE_FLAGS_OPCODE_IS_MODRM( addr_mode_def->opcode_flags ) && cfg->force_rex_prefix ) || mod_rm->reg_opcode_needs_rex || context->reg_opcode_needs_rex ) {
				instruction_part->code[0] = rex;
				instruction_part->code_length = 1;
			}

		}
	}

	return FCML_CEH_GEC_NO_ERROR;
}

fcml_ist_asm_instruction_part_processor_descriptor fcml_ifn_asm_instruction_part_processor_factory_REX_prefix_encoder( fcml_uint32_t flags, fcml_st_def_instruction_desc *instruction, fcml_st_def_addr_mode_desc *addr_mode, fcml_hints *hints, fcml_ceh_error *error ) {
	fcml_ist_asm_instruction_part_processor_descriptor descriptor = {0};
	/* 66 prefix can be applied to instructions without neither XOP nor VEX prefixes. Remember that this prefix can bes mandatory one.*/
	if( FCML_DEF_OPCODE_FLAGS_64_BIT_MODE_SUPPORTED( addr_mode->opcode_flags ) && !( FCML_DEF_PREFIX_VEX_REQ( addr_mode->allowed_prefixes ) || FCML_DEF_PREFIX_XOP_REQ( addr_mode->allowed_prefixes ) ) ) {
		descriptor.processor_type = FCML_IEN_ASM_IPPT_ENCODER;
		descriptor.processor_args = NULL;
		descriptor.processor_encoder = fcml_ifn_asm_instruction_part_processor_REX_prefix_encoder;
		descriptor.processor_acceptor = NULL;
	}
	return descriptor;
}

/*****************************/
/* ModR/M encoder factories. */
/*****************************/

fcml_ceh_error fcml_ifn_asm_instruction_part_rip_post_processor( fcml_ist_asm_encoding_context *context, fcml_ist_asm_instruction_part *instruction_part, fcml_ptr post_processor_args ) {

	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

	fcml_st_assembler_context *assembler_context = context->assembler_context;
	fcml_st_encoded_modrm *encoded_mod_rm = &(context->encoded_mod_rm);

	if( !context->instruction_size.is_not_null ) {
		/* Should never happened.*/
		FCML_TRACE_MSG( "instruction can not be null here." );
		error = FCML_CEH_GEC_INTERNAL_ERROR;
	} else {
		/* Encode ModR/M and displacement.*/
		fcml_st_memory_stream stream = fcml_ifn_asm_instruction_part_stream( instruction_part );
		fcml_fn_stream_write( &stream, encoded_mod_rm->modrm );
		error = fcml_fn_modrm_encode_rip_offset( &stream, assembler_context->entry_point.ip, context->instruction_size.value, encoded_mod_rm );
	}

	return error;
}

fcml_ceh_error fcml_ifn_asm_instruction_part_processor_ModRM_encoder( fcml_ien_asm_part_processor_phase phase, fcml_ist_asm_encoding_context *context, fcml_ist_asm_addr_mode_desc_details *addr_mode_details, fcml_st_def_addr_mode_desc *addr_mode_def, fcml_ist_asm_instruction_part *instruction_part, fcml_ptr args ) {

	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

	fcml_st_assembler_context *assembler_context = context->assembler_context;

	if( phase == FCML_IEN_ASM_IPPP_SECOND_PHASE ) {

		fcml_st_modrm_encoder_context ctx;
		ctx.op_mode = assembler_context->entry_point.op_mode;

		/* Hints have higher precedence than configuration.*/

		/* Chooses relative or absolute addressing. Configuration as well as rel/abs hints take*/
		/* effect only in 64 bit addressing mode.*/

		ctx.choose_rip_encoding = !assembler_context->configuration.choose_abs_encoding;
		ctx.choose_sib_encoding = assembler_context->configuration.choose_sib_encoding;

		if( context->is_sib_alternative_hint ) {
			ctx.choose_sib_encoding = FCML_TRUE;
			/* SIB hint has higher precedence than RIP configuration. There is no way to encode RIP using SIB, so*/
			/* RIP flag has to be cleared in order to encode absolute offset using requested SIB encoding.*/
			ctx.choose_rip_encoding = FCML_FALSE;
		}

		if( context->is_rel_alternative_hint ) {
			/* RIP encoding has been forced by using "rel" hint.*/
			ctx.choose_rip_encoding = FCML_TRUE;
		}

		if( context->is_abs_alternative_hint ) {
			/* Absolute offset encoding has been forced by using "abs" hint.*/
			ctx.choose_rip_encoding = FCML_FALSE;
		}

		ctx.chosen_effective_address_size = 0;
		ctx.effective_address_size = fcml_ifn_asm_get_effective_address_size( context );
		ctx.is_sib_alternative = FCML_FALSE;

		if( FCML_DEF_OPCODE_FLAGS_OPCODE_IS_EXT( addr_mode_def->opcode_flags ) ) {
			context->mod_rm.reg_opcode = FCML_DEF_OPCODE_FLAGS_OPCODE_EXT( addr_mode_def->opcode_flags );
		}

		/* Encodes ModR/M bytes.*/
		error = fcml_fn_modrm_encode( &ctx, &(context->mod_rm), &(context->encoded_mod_rm) );
		if( !error ) {
			if( context->optimizer_processing_details.easa == ctx.chosen_effective_address_size ) {
				if( context->encoded_mod_rm.is_rip && !context->encoded_mod_rm.is_rip_encoded ) {
					/* ModR/M + 4bytes displacement.*/
					instruction_part->code_length = 5;
					instruction_part->post_processor = fcml_ifn_asm_instruction_part_rip_post_processor;
					instruction_part->post_processor_args = NULL;
				} else {
					fcml_st_memory_stream stream = fcml_ifn_asm_instruction_part_stream( instruction_part );
					fcml_st_encoded_modrm *encoded_modrm = &(context->encoded_mod_rm);
					fcml_fn_stream_write( &stream, encoded_modrm->modrm );
					if( encoded_modrm->sib.is_not_null ) {
						fcml_fn_stream_write( &stream, encoded_modrm->sib.value );
					}
					if( encoded_modrm->displacement_size ) {
						fcml_fn_stream_write_bytes( &stream, &(encoded_modrm->displacement), encoded_modrm->displacement_size );
					}
					instruction_part->code_length = stream.offset;
				}
				context->is_sib_alternative_encoding = ctx.is_sib_alternative;
			} else {
				/* ModRM encoded to the form not supported by current addressing mode. For example, addressing mode needs ASA 32, but asembled ModRM required 16 bit ASA.*/
				error = FCML_CEH_GEC_INVALID_ADDRESS_SIZE;
			}
		}

	}
	return error;
}

fcml_ist_asm_instruction_part_processor_descriptor fcml_ifn_asm_instruction_part_processor_factory_ModRM_encoder( fcml_uint32_t flags, fcml_st_def_instruction_desc *instruction, fcml_st_def_addr_mode_desc *addr_mode, fcml_hints *hints, fcml_ceh_error *error ) {
	fcml_ist_asm_instruction_part_processor_descriptor descriptor = {0};
	/* Check if instruction has ModR/M byte.*/
	if( FCML_DEF_OPCODE_FLAGS_OPCODE_IS_MODRM( addr_mode->opcode_flags ) ) {
		descriptor.processor_type = FCML_IEN_ASM_IPPT_ENCODER;
		descriptor.processor_args = NULL;
		descriptor.processor_encoder = fcml_ifn_asm_instruction_part_processor_ModRM_encoder;
		descriptor.processor_acceptor = NULL;
	}
	return descriptor;
}

/*******************************/
/* Addressing mode validators. */
/*******************************/

fcml_ceh_error fcml_ifn_asm_instruction_part_processor_addr_mode_acceptor( fcml_ist_asm_encoding_context *context, fcml_ist_asm_addr_mode_desc_details *addr_mode_details, fcml_st_def_addr_mode_desc *addr_mode_def, fcml_st_instruction *instruction, fcml_ptr args ) {

	fcml_en_operating_mode op_mode = context->assembler_context->entry_point.op_mode;

	if( !FCML_DEF_OPCODE_FLAGS_64_BIT_MODE_SUPPORTED( addr_mode_def->opcode_flags ) && op_mode == FCML_AF_64_BIT ) {
		return FCML_CEH_GEC_INVALID_ADDRESSING_MODE;
	} else if ( !FCML_DEF_OPCODE_FLAGS_16_32_BIT_MODE_SUPPORTED( addr_mode_def->opcode_flags ) && ( op_mode == FCML_AF_16_BIT || op_mode == FCML_AF_32_BIT ) ) {
		return FCML_CEH_GEC_INVALID_ADDRESSING_MODE;
	}

	/* Set restrictions if there are any.*/
	if( addr_mode_details->allowed_osa != FCML_EN_ASF_ANY ) {
		context->optimizer_processing_details.allowed_eosa.flags = addr_mode_details->allowed_osa;
		context->optimizer_processing_details.allowed_eosa.is_set = FCML_TRUE;
	}
	if( addr_mode_details->allowed_asa != FCML_EN_ASF_ANY ) {
		context->optimizer_processing_details.allowed_easa.flags = addr_mode_details->allowed_asa;
		context->optimizer_processing_details.allowed_easa.is_set = FCML_TRUE;
	}

	/* Force 64 bit OSA in 64 bit addressing mode.*/
	if( op_mode == FCML_AF_64_BIT ) {
		if( FCML_DEF_OPCODE_FLAGS_FORCE_64BITS_EOSA( addr_mode_def->opcode_flags ) ) {
			context->optimizer_processing_details.allowed_eosa.flags = FCML_EN_ASF_64;
			context->optimizer_processing_details.allowed_eosa.is_set = FCML_TRUE;
		} else if( FCML_DEF_OPCODE_FLAGS_64BITS_EOSA_BY_DEFAULT( addr_mode_def->opcode_flags ) ) {
			/* Remember, if 64 bit EOSA is used by default it can be overridden to 16 bits only. */
			context->optimizer_processing_details.allowed_eosa.flags = ( FCML_EN_ASF_64 | FCML_EN_ASF_16 );
			context->optimizer_processing_details.allowed_eosa.is_set = FCML_TRUE;
		}
	}

	return FCML_CEH_GEC_NO_ERROR;
}

fcml_ist_asm_instruction_part_processor_descriptor fcml_ifn_asm_instruction_part_processor_factory_addr_mode_acceptor( fcml_uint32_t flags, fcml_st_def_instruction_desc *instruction, fcml_st_def_addr_mode_desc *addr_mode, fcml_hints *hints, fcml_ceh_error *error ) {
	fcml_ist_asm_instruction_part_processor_descriptor descriptor = {0};
	descriptor.processor_type = FCML_IEN_ASM_IPPT_VERIFIER;
	descriptor.processor_args = NULL;
	descriptor.processor_encoder = NULL;
	descriptor.processor_acceptor = fcml_ifn_asm_instruction_part_processor_addr_mode_acceptor;
	return descriptor;
}

/************************/
/* Prefixes validators. */
/************************/

fcml_ceh_error fcml_ifn_asm_instruction_part_processor_prefixes_acceptor( fcml_ist_asm_encoding_context *context, fcml_ist_asm_addr_mode_desc_details *addr_mode_details, fcml_st_def_addr_mode_desc *addr_mode_def, fcml_st_instruction *instruction, fcml_ptr args ) {
	/* Check if LOCK prefix is allowed for given addressing mode.*/
	if( instruction->prefixes ) {
		if( ( instruction->prefixes & FCML_PREFIX_LOCK ) && !FCML_DEF_PREFIX_LOCK_ALLOWED( addr_mode_def->allowed_prefixes ) ) {
			return FCML_CEH_GEC_INVALID_PREFIX;
		}
		/* Check if REP prefix is allowed for given addressing mode.*/
		if( ( instruction->prefixes & FCML_PREFIX_REP ) && !FCML_DEF_PREFIX_REP_XRELEASE_ALLOWED( addr_mode_def->allowed_prefixes ) ) {
			return FCML_CEH_GEC_INVALID_PREFIX;
		}
		/* Check if REPNE prefix is allowed for given addressing mode.*/
		if( ( instruction->prefixes & FCML_PREFIX_REPNE ) && !FCML_DEF_PREFIX_REPNE_XACQUIRE_ALLOWED( addr_mode_def->allowed_prefixes ) ) {
			return FCML_CEH_GEC_INVALID_PREFIX;
		}
		/* Check if XACQUIRED prefix is allowed for given addressing mode.*/
		if( ( instruction->prefixes & FCML_PREFIX_XACQUIRE ) && ( !FCML_DEF_PREFIX_HLE_ENABLED( addr_mode_def->allowed_prefixes ) || !FCML_DEF_PREFIX_REPNE_XACQUIRE_ALLOWED( addr_mode_def->allowed_prefixes ) ) ) {
			return FCML_CEH_GEC_INVALID_PREFIX;
		}
		/* Check if XRELEASE prefix is allowed for given addressing mode.*/
		if( ( instruction->prefixes & FCML_PREFIX_XRELEASE ) && ( !FCML_DEF_PREFIX_HLE_ENABLED( addr_mode_def->allowed_prefixes ) || !FCML_DEF_PREFIX_REP_XRELEASE_ALLOWED( addr_mode_def->allowed_prefixes ) ) ) {
			return FCML_CEH_GEC_INVALID_PREFIX;
		}
	}
	return FCML_CEH_GEC_NO_ERROR;
}

fcml_ist_asm_instruction_part_processor_descriptor fcml_ifn_asm_instruction_part_processor_factory_prefixes_acceptor( fcml_uint32_t flags, fcml_st_def_instruction_desc *instruction, fcml_st_def_addr_mode_desc *addr_mode, fcml_hints *hints, fcml_ceh_error *error ) {
	fcml_ist_asm_instruction_part_processor_descriptor descriptor = {0};
	descriptor.processor_type = FCML_IEN_ASM_IPPT_VERIFIER;
	descriptor.processor_args = NULL;
	descriptor.processor_encoder = NULL;
	descriptor.processor_acceptor = fcml_ifn_asm_instruction_part_processor_prefixes_acceptor;
	return descriptor;
}

/********************************************/
/* Instruction parts factories definitions. */
/********************************************/

typedef struct fcml_ist_asm_instruction_part_factory_details {
	fcml_ifp_asm_instruction_part_processor_factory factory;
	fcml_uint32_t flags;
} fcml_ist_asm_instruction_part_factory_details;

typedef enum fcml_ist_instruction_part_choice_type {
	FCML_IPCT_ONE,
	FCML_IPCT_ALL,
} fcml_ist_instruction_part_choice_type;

typedef struct fcml_ist_asm_instruction_part_factory_sequence {
	fcml_ist_asm_instruction_part_factory_details *details;
	fcml_ist_instruction_part_choice_type choice_type;
	fcml_bool is_short_form_supported;
} fcml_ist_asm_instruction_part_factory_sequence;

/* List of instruction part encoders for instruction opcode.*/
fcml_ist_asm_instruction_part_factory_details fcml_iarr_asm_instruction_part_processor_factories_opcode_for_IA[] = {
	{ fcml_ifn_asm_instruction_part_processor_factory_XOP_VEX_opcode_encoder, 0 },
	{ fcml_ifn_asm_instruction_part_processor_factory_reg_opcode_encoder, 0 },
	{ fcml_ifn_asm_instruction_part_processor_factory_conditional_opcode_encoder, 0 },
	{ fcml_ifn_asm_instruction_part_processor_factory_simple_opcode_encoder, 0 },
	{ NULL, 0 }
};

/* List of instruction addressing mode acceptors.*/
fcml_ist_asm_instruction_part_factory_details fcml_iarr_asm_instruction_part_processor_factories_acceptors_IA[] = {
	{ fcml_ifn_asm_instruction_part_processor_factory_addr_mode_acceptor, 0 },
	{ fcml_ifn_asm_instruction_part_processor_factory_prefixes_acceptor, 0 },
	{ NULL, 0 }
};

/* List of instruction part encoders for instruction prefixes.*/
fcml_ist_asm_instruction_part_factory_details fcml_iarr_asm_instruction_part_processor_factories_prefixes_for_IA[] = {
	{ fcml_ifn_asm_instruction_part_processor_factory_branch_hints_prefix_encoder, 0 },
	{ fcml_ifn_asm_instruction_part_processor_factory_rep_prefix_encoder, 0 },
	{ fcml_ifn_asm_instruction_part_processor_factory_repne_prefix_encoder, 0 },
	{ fcml_ifn_asm_instruction_part_processor_factory_hle_prefixes_encoder, 0 },
	{ fcml_ifn_asm_instruction_part_processor_factory_lock_prefix_encoder, 0 },
    { fcml_ifn_asm_instruction_part_processor_factory_segment_override_prefix_encoder, 0 },
	{ fcml_ifn_asm_instruction_part_processor_factory_66_prefix_encoder, 0 },
	{ fcml_ifn_asm_instruction_part_processor_factory_67_prefix_encoder, 0 },
	{ fcml_ifn_asm_instruction_part_processor_factory_mandatory_prefixes_encoder, 0 },
	{ fcml_ifn_asm_instruction_part_processor_factory_REX_prefix_encoder, 0 },
	{ fcml_ifn_asm_instruction_part_processor_factory_VEX_XOP_prefix_encoder, 0 },
	{ NULL, 0 }
};

/* ModR/M byte encoder.*/
fcml_ist_asm_instruction_part_factory_details fcml_iarr_asm_instruction_part_processor_factories_ModRM_for_IA[] = {
	{ fcml_ifn_asm_instruction_part_processor_factory_ModRM_encoder, 0 },
	{ NULL, 0 }
};

/* List of instruction part encoders for instruction operands.*/
fcml_ist_asm_instruction_part_factory_details fcml_iarr_asm_instruction_part_processor_factories_operands_for_IA[] = {
	{ fcml_ifn_asm_instruction_part_processor_factory_operand_encoder_wrapper, 0 },
	{ fcml_ifn_asm_instruction_part_processor_factory_operand_encoder_wrapper, 1 },
	{ fcml_ifn_asm_instruction_part_processor_factory_operand_encoder_wrapper, 2 },
	{ fcml_ifn_asm_instruction_part_processor_factory_operand_encoder_wrapper, 3 },
	{ fcml_ifn_asm_instruction_part_processor_factory_operand_encoder_wrapper, 4 },
	{ NULL, 0 }
};

fcml_ist_asm_instruction_part_factory_details fcml_iarr_asm_instruction_part_processor_factories_suffixes_for_IA[] = {
	{ fcml_ifn_asm_instruction_part_processor_factory_suffix_encoder, 0 },
	{ NULL, 0 }
};

fcml_ist_asm_instruction_part_factory_sequence fcml_iarr_asm_instruction_part_processor_factory_sequences_for_IA[] = {
	{ fcml_iarr_asm_instruction_part_processor_factories_acceptors_IA, FCML_IPCT_ALL, FCML_TRUE },
	{ fcml_iarr_asm_instruction_part_processor_factories_prefixes_for_IA, FCML_IPCT_ALL, FCML_TRUE },
	{ fcml_iarr_asm_instruction_part_processor_factories_opcode_for_IA, FCML_IPCT_ONE, FCML_TRUE },
	{ fcml_iarr_asm_instruction_part_processor_factories_ModRM_for_IA, FCML_IPCT_ALL, FCML_FALSE },
	{ fcml_iarr_asm_instruction_part_processor_factories_operands_for_IA, FCML_IPCT_ALL, FCML_FALSE },
	{ fcml_iarr_asm_instruction_part_processor_factories_suffixes_for_IA, FCML_IPCT_ALL, FCML_FALSE },
	{ NULL }
};

fcml_ist_asm_instruction_part_processor_chain* fcml_ifn_asm_instruction_part_processor_factory_dispatcher_IA( fcml_st_def_instruction_desc *instruction, fcml_st_def_addr_mode_desc *addr_mode, int *parts, fcml_hints *hints, fcml_ceh_error *error ) {

	int instruction_parts = 0;

	fcml_ist_asm_instruction_part_processor_chain *chain = NULL;
	fcml_ist_asm_instruction_part_processor_chain *current_chain = NULL;
	fcml_ist_asm_instruction_part_factory_sequence *current_factories_sequence = &fcml_iarr_asm_instruction_part_processor_factory_sequences_for_IA[0];

	while( current_factories_sequence->details ) {

		int processor_counter = 0;

		fcml_ist_instruction_part_choice_type choice = current_factories_sequence->choice_type;
		fcml_ist_asm_instruction_part_factory_details *current_factory = current_factories_sequence->details;

		while( current_factory->factory ) {

			fcml_ist_asm_instruction_part_processor_descriptor descriptor = current_factory->factory( current_factory->flags, instruction, addr_mode, hints, error );
			if( descriptor.processor_encoder || descriptor.processor_acceptor ) {

				processor_counter++;

				descriptor.is_short_form_supported = current_factories_sequence->is_short_form_supported;

				/* Check max number of the instruction part processors.*/
				if( processor_counter > FCML_ASM_MAX_PART_PROCESSORS ) {
					FCML_TRACE_MSG("Max number of instructions part processors has been reached.");
					*error = FCML_CEH_GEC_INTERNAL_ERROR;
					/* Free processor arguments if there are any in the descriptor. */
					if( descriptor.processor_args_deallocator ) {
						descriptor.processor_args_deallocator( descriptor.processor_args );
					}
					fcml_ifn_asm_free_part_processor_chain( chain );
					return NULL;
				}

				/* Allocate chain element for new instruction part encoder.*/
				fcml_ist_asm_instruction_part_processor_chain *new_chain = (fcml_ist_asm_instruction_part_processor_chain*)fcml_fn_env_memory_alloc_clear( sizeof( fcml_ist_asm_instruction_part_processor_chain ) );
				if( !new_chain ) {
					*error = FCML_CEH_GEC_OUT_OF_MEMORY;
					if( descriptor.processor_args_deallocator ) {
						descriptor.processor_args_deallocator( descriptor.processor_args );
					}
					fcml_ifn_asm_free_part_processor_chain( chain );
					return NULL;
				}

				if( !chain ) {
					chain = new_chain;
					current_chain = new_chain;
				} else {
					current_chain->next_processor = new_chain;
					current_chain = new_chain;
				}

				current_chain->processor_descriptor = descriptor;

				if( descriptor.processor_type == FCML_IEN_ASM_IPPT_ENCODER ) {
					instruction_parts++;
				}

				if( choice == FCML_IPCT_ONE ) {
					break;
				}
			}
			if( *error ) {
				fcml_ifn_asm_free_part_processor_chain( chain );
				return NULL;
			}
			current_factory++;
		}

		current_factories_sequence++;
	}

	*parts = instruction_parts;

	return chain;
}

fcml_ifp_asm_instruction_part_processor_factory_dispatcher fcml_ifn_get_instruction_part_processor_factory_dispatcher_for_instruction_type( fcml_en_def_instruction_type instruction_type ) {
	fcml_ifp_asm_instruction_part_processor_factory_dispatcher dispatcher = NULL;
	switch( instruction_type ) {
	case FCML_EN_IT_IA:
		dispatcher = fcml_ifn_asm_instruction_part_processor_factory_dispatcher_IA;
		break;
	}
	return dispatcher;
}

/* Default data size calculator. */

typedef struct fcml_ist_asm_def_data_size_calc_args {
	fcml_int mem_index;
	fcml_int reg_index;
} fcml_ist_asm_def_data_size_calc_args;

fcml_usize fcml_ifp_asm_default_reg_based_memory_data_size_calculator( fcml_st_instruction *instruction, fcml_ptr args ) {
	fcml_usize data = FCML_DS_UNDEF;
	fcml_ist_asm_def_data_size_calc_args *dsc_args = (fcml_ist_asm_def_data_size_calc_args*)args;
	if( instruction->operands_count >= dsc_args->reg_index + 1 ) {
		fcml_st_operand *operand = &(instruction->operands[dsc_args->reg_index]);
		if( operand->type == FCML_EOT_REGISTER ) {
			return operand->reg.size;
		}
	}
	return data;
}

fcml_ceh_error fcml_ifn_asm_prepare_mem_data_size_calculator( fcml_st_def_addr_mode_desc *addr_mode_desc, fcml_ist_asm_addr_mode_desc_details *details ) {

	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

	fcml_int mem_index = -1;
	fcml_int reg_index = -1;

	/* Just in case.*/
	details->ds_calculator = NULL;
	details->ds_calculator_args = NULL;

	fcml_int i;
	for( i = 0; i < FCML_OPERANDS_COUNT; i++ ) {
		fcml_uint32_t addr_mode = addr_mode_desc->opperands[i];
		if( addr_mode == FCML_NA ) {
			break;
		}
		if( FCMP_DEF_IS_ADDR_MODE( FCML_GET_ADDR_MODE( addr_mode ), FCML_OP_RM_BASE ) ) {
			fcml_st_def_decoded_addr_mode *dec_addr_mode = fcml_fnp_def_decode_addr_mode_args( addr_mode, &error );
			if( error ) {
				return error;
			}
			fcml_sf_def_tma_rm *rm_args = (fcml_sf_def_tma_rm*)dec_addr_mode->addr_mode_args;
			if( !rm_args  ) {
				return FCML_CEH_GEC_OUT_OF_MEMORY;
			}
			if( rm_args->flags & FCML_RMF_M ) {
				mem_index = i;
			}
			fcml_fnp_def_free_addr_mode( dec_addr_mode );
		}
		if( FCMP_DEF_IS_ADDR_MODE( FCML_GET_ADDR_MODE( addr_mode ), FCML_OP_R_BASE )
				|| FCMP_DEF_IS_ADDR_MODE( FCML_GET_ADDR_MODE( addr_mode ), FCML_OP_OPCODE_REG_BASE )
				|| FCMP_DEF_IS_ADDR_MODE( FCML_GET_ADDR_MODE( addr_mode ), FCML_OP_EXPLICIT_REG_BASE )
				|| FCMP_DEF_IS_ADDR_MODE( FCML_GET_ADDR_MODE( addr_mode ), FCML_OP_VEX_VVVV_REG_BASE ) ) {
			reg_index = i;
		}
	}

	if( mem_index != -1 && reg_index != -1 ) {
		fcml_ist_asm_def_data_size_calc_args *args = (fcml_ist_asm_def_data_size_calc_args*)fcml_fn_env_memory_alloc_clear( sizeof( fcml_ist_asm_def_data_size_calc_args ) );
		if( !args ) {
			return FCML_CEH_GEC_OUT_OF_MEMORY;
		}
		args->mem_index = mem_index;
		args->reg_index = reg_index;
		details->ds_calculator = &fcml_ifp_asm_default_reg_based_memory_data_size_calculator;
		details->ds_calculator_args = args;
	}

	return error;
}

/* Precalculates some data using given addressing mode. By precalculating them we can
 * get some performance benefits further.
 */
fcml_ceh_error fcml_ifn_asm_precalculate_addr_mode( fcml_st_def_addr_mode_desc *addr_mode_desc, fcml_ist_asm_addr_mode_desc_details *details ) {

	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

	fcml_uint16_t allowed_prefixes = addr_mode_desc->allowed_prefixes;

	fcml_uint32_t opcode_flags = addr_mode_desc->opcode_flags;

	/* Calculate OSA and ASA flags.*/

	fcml_flags osa_flags = FCML_EN_ASF_ANY;
	fcml_flags asa_flags = FCML_EN_ASF_ANY;

	if( !( addr_mode_desc->instruction_group & FCML_AMT_SIMD ) ) {
		if( FCML_DEF_PREFIX_W_1( allowed_prefixes ) ) {
			osa_flags |= FCML_EN_ASF_64;
			asa_flags |= ( FCML_EN_ASF_32 | FCML_EN_ASF_64 );
		}
		if( FCML_DEF_PREFIX_W_0( allowed_prefixes ) ) {
			osa_flags |= ( FCML_EN_ASF_32 | FCML_EN_ASF_16 );
		}
	}

	if( FCML_DEF_OPCODE_FLAGS_IS_EOSA_RESTRICTION( opcode_flags ) ) {
		fcml_flags osa_restriction_flags = FCML_EN_ASF_ANY;
		if( FCML_DEF_OPCODE_FLAGS_EOSA_16( opcode_flags ) ) {
			osa_restriction_flags |= FCML_EN_ASF_16;
		}
		if( FCML_DEF_OPCODE_FLAGS_EOSA_32( opcode_flags ) ) {
			osa_restriction_flags |= FCML_EN_ASF_32;
		}
		if( FCML_DEF_OPCODE_FLAGS_EOSA_64( opcode_flags ) ) {
			osa_restriction_flags |= FCML_EN_ASF_64;
		}
		osa_flags = ( osa_flags == FCML_EN_ASF_ANY ) ? osa_restriction_flags : osa_flags & osa_restriction_flags;
	}

	if( FCML_DEF_OPCODE_FLAGS_IS_EASA_RESTRICTION( opcode_flags ) ) {
		fcml_flags asa_restriction_flags = FCML_EN_ASF_ANY;
		if( FCML_DEF_OPCODE_FLAGS_EASA_16( opcode_flags ) ) {
			asa_restriction_flags |= FCML_EN_ASF_16;
		}
		if( FCML_DEF_OPCODE_FLAGS_EASA_32( opcode_flags ) ) {
			asa_restriction_flags |= FCML_EN_ASF_32;
		}
		if( FCML_DEF_OPCODE_FLAGS_EASA_64( opcode_flags ) ) {
			asa_restriction_flags |= FCML_EN_ASF_64;
		}
		asa_flags = ( asa_flags == FCML_EN_ASF_ANY ) ? asa_restriction_flags : asa_flags & asa_restriction_flags;
	}

	/* Sets calculated values in details.*/

	details->allowed_asa = asa_flags;
	details->allowed_osa = osa_flags;

	return error;
}

void fcml_ifn_asm_free_instruction_addr_mode_item_handler( fcml_ptr item_value, fcml_ptr args ) {

    fcml_ist_asm_instruction_addr_mode_encoding_details *addr_mode = (fcml_ist_asm_instruction_addr_mode_encoding_details*)item_value;

    /* Do not free clones. Processor chains and calculator arguments are shared. */
    if( !addr_mode->is_cloned ) {
        /* Free processor chain.*/
        if( addr_mode->part_processor_chain ) {
            fcml_ifn_asm_free_part_processor_chain( addr_mode->part_processor_chain );
        }
        /* Free arguments allocated for memory data size calculator if there are any.*/
        if( addr_mode->addr_mode_details.ds_calculator_args ) {
            fcml_fn_env_memory_free( addr_mode->addr_mode_details.ds_calculator_args );
        }
    }

    fcml_st_dialect_context_int *dialect_context = (fcml_st_dialect_context_int*)args;

    /* Free all mnemonics.*/
    if( addr_mode->mnemonic ) {
        dialect_context->free_mnemonic( addr_mode->mnemonic );
    }

    fcml_fn_env_memory_free( addr_mode );

}

void fcml_ifn_asm_free_instruction_entry( fcml_ptr key, fcml_ptr value, fcml_ptr args ) {
    fcml_st_asm_instruction_addr_modes *addr_modes = (fcml_st_asm_instruction_addr_modes*)value;
    if( addr_modes ) {
        if( addr_modes->addr_modes ) {
            fcml_fn_coll_list_free( addr_modes->addr_modes, fcml_ifn_asm_free_instruction_addr_mode_item_handler, args );
        }
        fcml_fn_env_memory_free( addr_modes );
    }
}

fcml_fnp_asm_instruction_encoder fcml_ifn_asm_choose_instruction_encoder( fcml_en_def_instruction_type instruction_type ) {
    fcml_fnp_asm_instruction_encoder encoder = NULL;
    switch( instruction_type ) {
    case FCML_EN_IT_IA:
        encoder = fcml_ifn_asm_instruction_encoder_IA;
        break;
    }
    return encoder;
}

/* *******************************************/
/* Addressing mode encoding details builders.*/
/* *******************************************/

typedef fcml_ceh_error (*fcml_ifp_asm_instruction_addr_mode_encoding_details_handler)( fcml_ist_asm_init_context *init_context, fcml_st_def_instruction_desc *instruction, fcml_st_def_addr_mode_desc *addr_mode_desc, fcml_ist_asm_instruction_addr_mode_encoding_details *addr_mode );

typedef fcml_ceh_error (*fcml_ifp_asm_addr_mode_encoding_details_builder)( fcml_ist_asm_init_context *init_context, fcml_st_def_instruction_desc *instruction, fcml_st_def_addr_mode_desc *addr_mode_desc, fcml_ifp_asm_instruction_addr_mode_encoding_details_handler addr_mode_handler );

typedef void (*fcml_ifp_asm_generic_addr_mode_encoding_details_enricher)( fcml_ist_asm_instruction_addr_mode_encoding_details *addr_mode, fcml_ptr args );

fcml_ceh_error fcml_ifn_asm_generic_addr_mode_encoding_details_builder( fcml_ist_asm_init_context *init_context, fcml_st_def_instruction_desc *instruction, fcml_st_def_addr_mode_desc *addr_mode_desc, fcml_ifp_asm_instruction_addr_mode_encoding_details_handler addr_mode_handler, fcml_ifp_asm_generic_addr_mode_encoding_details_enricher enricher, fcml_ptr enricher_args ) {

    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

	fcml_ist_asm_instruction_addr_mode_encoding_details *addr_mode = (fcml_ist_asm_instruction_addr_mode_encoding_details *)fcml_fn_env_memory_alloc_clear( sizeof( fcml_ist_asm_instruction_addr_mode_encoding_details ) );
	if( !addr_mode ) {
		return FCML_CEH_GEC_OUT_OF_MEMORY;
	}

	addr_mode->addr_mode_desc = addr_mode_desc;

	/* Prepare addressing mode details.*/
	error = fcml_ifn_asm_precalculate_addr_mode( addr_mode_desc, &(addr_mode->addr_mode_details) );
	if( error ) {
		fcml_fn_env_memory_free(addr_mode);
		return error;
	}

	error = fcml_ifn_asm_prepare_mem_data_size_calculator( addr_mode_desc, &(addr_mode->addr_mode_details) );
	if( error ) {
		fcml_fn_env_memory_free(addr_mode);
		return error;
	}

	if( enricher ) {
		enricher( addr_mode, enricher_args );
	}

	int instruction_parts;

	fcml_ifp_asm_instruction_part_processor_factory_dispatcher factory_dispatcher = fcml_ifn_get_instruction_part_processor_factory_dispatcher_for_instruction_type( instruction->instruction_type );

	addr_mode->part_processor_chain = factory_dispatcher( instruction, addr_mode_desc, &instruction_parts, &(addr_mode->hints), &error );
	if( !error ) {
		addr_mode->instruction_parts = instruction_parts;
		error = addr_mode_handler( init_context, instruction, addr_mode_desc, addr_mode );
		if( error ) {
			fcml_ifn_asm_free_part_processor_chain( addr_mode->part_processor_chain );
			if( addr_mode->addr_mode_details.ds_calculator_args ) {
				fcml_fn_env_memory_free( addr_mode->addr_mode_details.ds_calculator_args );
			}
			fcml_fn_env_memory_free(addr_mode);
		}
	} else {
		if( addr_mode->addr_mode_details.ds_calculator_args ) {
			fcml_fn_env_memory_free( addr_mode->addr_mode_details.ds_calculator_args );
		}
		fcml_fn_env_memory_free(addr_mode);
	}

	return error;
}

typedef struct fcml_ist_sonditional_anricher_args {
	/* Instruction condition code. */
	fcml_int condition_num;
} fcml_ist_sonditional_anricher_args;

void fcml_ifn_asm_generic_addr_more_conditional_enricher( fcml_ist_asm_instruction_addr_mode_encoding_details *addr_mode, fcml_ptr args ) {
	fcml_ist_sonditional_anricher_args *enricher_args = (fcml_ist_sonditional_anricher_args*)args;
	fcml_ist_asm_addr_mode_desc_details *addr_mode_details = &(addr_mode->addr_mode_details);
	addr_mode_details->is_conditional = FCML_TRUE;
	addr_mode_details->condition.is_negation = ( enricher_args->condition_num % 2 == 1 );
	addr_mode_details->condition.condition_type = (fcml_en_condition_type)( enricher_args->condition_num / 2 );
}

fcml_ceh_error fcml_ifn_asm_conditional_instruction_addr_mode_encoding_details_builder( fcml_ist_asm_init_context *init_context, fcml_st_def_instruction_desc *instruction, fcml_st_def_addr_mode_desc *addr_mode_desc, fcml_ifp_asm_instruction_addr_mode_encoding_details_handler addr_mode_handler ) {

    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

    int i;
    for( i = 0; i < FCML_NUMBER_OF_CONDITIONS * 2 && !error; i++ ) {

    	fcml_ist_sonditional_anricher_args enricher_args;
    	enricher_args.condition_num = i;

        error = fcml_ifn_asm_generic_addr_mode_encoding_details_builder( init_context, instruction, addr_mode_desc, addr_mode_handler, &fcml_ifn_asm_generic_addr_more_conditional_enricher, &enricher_args );
    }

    return error;
}

fcml_ceh_error fcml_ifn_asm_default_addr_mode_encoding_details_builder( fcml_ist_asm_init_context *init_context, fcml_st_def_instruction_desc *instruction, fcml_st_def_addr_mode_desc *addr_mode_desc, fcml_ifp_asm_instruction_addr_mode_encoding_details_handler addr_mode_handler ) {
    return fcml_ifn_asm_generic_addr_mode_encoding_details_builder( init_context, instruction, addr_mode_desc, addr_mode_handler, NULL, NULL );
}

fcml_ifp_asm_addr_mode_encoding_details_builder fcml_ifn_asm_conditional_instruction_addr_mode_encoding_details_builder_factory( fcml_st_def_addr_mode_desc *addr_mode_desc ) {
    if( FCML_DEF_OPCODE_FLAGS_OPCODE_FIELD_TTTN( addr_mode_desc->opcode_flags ) ) {
        return &fcml_ifn_asm_conditional_instruction_addr_mode_encoding_details_builder;
    }
    return &fcml_ifn_asm_default_addr_mode_encoding_details_builder;
}

/* *******************************************/
/* Addressing mode encoding details handlers.*/
/* *******************************************/

fcml_ceh_error fcml_ifn_asm_encoded_handle_instruction_addr_mode_decoding( fcml_ist_asm_init_context *init_context, fcml_st_def_instruction_desc *instruction, fcml_st_def_addr_mode_desc *addr_mode_desc, fcml_ist_asm_instruction_addr_mode_encoding_details *addr_mode ) {

    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

    /* Space for mnemonics.*/
    fcml_st_mp_mnemonic *mnemonics[FCML_ASM_DIALECT_MAX_MNEMONIC_COUNT];

    /* Instruction can be registered for more than one mnemonic.*/
    int mnemonic_count = 0;
    error = init_context->dialect_context->get_mnemonic( (fcml_st_dialect*)init_context->dialect_context, instruction, addr_mode_desc, addr_mode->addr_mode_details.is_conditional ? &(addr_mode->addr_mode_details.condition) : NULL, mnemonics, &mnemonic_count );
    if( error ) {
        return error;
    }

    /* Prepare addressing mode encoders for every mnemonic.*/
    int i;
    for( i = 0; i < mnemonic_count && !error; i++ ) {

        fcml_st_asm_instruction_addr_modes *addr_modes = (fcml_st_asm_instruction_addr_modes*)fcml_fn_coll_map_get( init_context->instructions_map, mnemonics[i]->mnemonic );
        if( !addr_modes ) {

            /* Allocate space for new mnemonic.*/
            addr_modes = (fcml_st_asm_instruction_addr_modes*)fcml_fn_env_memory_alloc( sizeof(fcml_st_asm_instruction_addr_modes) );
            if( addr_modes ) {

                /* Allocate list for addressing modes.*/
                addr_modes->addr_modes = fcml_fn_coll_list_alloc();
                if( addr_modes->addr_modes ) {
                    /* Do not care about freeing this piece of memory. Procedure responsible for freeing addressing mode is responsible for it.*/
                    addr_modes->mnemonic = mnemonics[i]->mnemonic;
                    addr_modes->instruction_encoder = fcml_ifn_asm_choose_instruction_encoder( instruction->instruction_type );

                    /* Puts prepared structure under mnemonic key.*/
                    fcml_int map_error;
                    fcml_fn_coll_map_put( init_context->instructions_map, mnemonics[i]->mnemonic, addr_modes, &map_error );
                    if( map_error ) {
                        fcml_fn_coll_list_free( addr_modes->addr_modes, fcml_ifn_asm_free_instruction_addr_mode_item_handler, &(init_context->dialect_context) );
                        fcml_fn_env_memory_free(addr_modes);
                        error = fcml_fn_utils_convert_map_error( map_error );
                    }

                } else {
                    fcml_fn_env_memory_free(addr_modes);
                    error = FCML_CEH_GEC_OUT_OF_MEMORY;
                }

            } else {
                /* Out of memory.*/
                error = FCML_CEH_GEC_OUT_OF_MEMORY;
            }
        }

        if( !error ) {

            fcml_bool is_cloned = ( i > 0 );

            fcml_ist_asm_instruction_addr_mode_encoding_details *addr_mode_encoding_details = addr_mode;

            if( is_cloned ) {

                /* Clone encoding details for secondary mnemonics.*/
                fcml_ist_asm_instruction_addr_mode_encoding_details *clone_addr_mode_enc_details = (fcml_ist_asm_instruction_addr_mode_encoding_details*)fcml_fn_env_memory_alloc_clear( sizeof( fcml_ist_asm_instruction_addr_mode_encoding_details ) );
                if( clone_addr_mode_enc_details ) {
                    *clone_addr_mode_enc_details = *addr_mode_encoding_details;
                    clone_addr_mode_enc_details->is_cloned = FCML_TRUE;
                    addr_mode_encoding_details = clone_addr_mode_enc_details;
                } else {
                    error = FCML_CEH_GEC_OUT_OF_MEMORY;
                }

            }

            /* Every addressing mode has its own mnemonic configuration, it doesn't matter if it is cloned addressing mode or not*/
            /* it is responsible for deallocating it.*/
            addr_mode_encoding_details->mnemonic = mnemonics[i];

            if( !error && !fcml_fn_coll_list_add_back( addr_modes->addr_modes, addr_mode_encoding_details ) ) {
                /* Free holder allocated earlier.*/
                if( is_cloned ) {
                    fcml_fn_env_memory_free( addr_mode_encoding_details );
                }
                error = FCML_CEH_GEC_OUT_OF_MEMORY;
            }

        }

        if( error ) {
            /* In case of error free all mnemonics which haven't been added to the addressing mode list.*/
            for( ; i < mnemonic_count; i++ ) {
               fcml_fn_asm_dialect_free_mnemonic( mnemonics[i] );
           }
        }

    }

    return error;
}

/* *****************************************/
/* Addressing mode encoders initialization.*/
/* *****************************************/

void fcml_ifn_asm_prepare_instruction_encoding_details( fcml_ist_asm_init_context *init_context, fcml_st_def_instruction_desc *instruction, fcml_ceh_error *error ) {

    /* Prepare encoders for given instruction.*/
    int i;
    for( i = 0; i < instruction->opcode_desc_count; i++ ) {

        fcml_st_def_addr_mode_desc *addr_mode_desc = &(instruction->addr_modes[i]);

        fcml_ifp_asm_addr_mode_encoding_details_builder encoding_details_builder = fcml_ifn_asm_conditional_instruction_addr_mode_encoding_details_builder_factory( addr_mode_desc );

        /* Prepare encoders for given addressing mode.*/
        *error = encoding_details_builder( init_context, instruction, addr_mode_desc, &fcml_ifn_asm_encoded_handle_instruction_addr_mode_decoding );
        if( *error ) {
            break;
        }

        addr_mode_desc++;
    }
}

fcml_ceh_error fcml_fn_asm_init_instruction_encodings( fcml_st_dialect_context_int *dialect_context, fcml_coll_map *inst_map ) {

	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

	fcml_coll_map instructions_map;

	/* Allocate map for all instructions.*/
	fcml_st_coll_map_descriptor inst_map_desc = fcml_coll_map_descriptor_string;
	inst_map_desc.entry_free_function = fcml_ifn_asm_free_instruction_entry;
	inst_map_desc.entry_free_args = dialect_context;

	fcml_int map_error;
	instructions_map = fcml_fn_coll_map_alloc( &inst_map_desc, 64, &map_error );
	if( map_error ) {
		return fcml_fn_utils_convert_map_error( map_error );
	}

	fcml_ist_asm_init_context init_context;
	init_context.dialect_context = dialect_context;
	init_context.instructions_map = instructions_map;

	int i = 0;
	fcml_st_def_instruction_desc *instruction = &(fcml_ext_instructions_def[i++]);
	while( instruction->mnemonic && !error ) {
	    fcml_ifn_asm_prepare_instruction_encoding_details( &init_context, instruction, &error );
		instruction = &(fcml_ext_instructions_def[i++]);
	}

	if( error ) {
		/* Something failed, so free everything that have been properly allocated.*/
		fcml_fn_coll_map_free( instructions_map );
	}

	*inst_map = instructions_map;

	return error;

}

void fcml_fn_asm_free_instruction_encodings( fcml_coll_map instructions_map ) {
	if( instructions_map ) {
		fcml_fn_coll_map_free( instructions_map );
	}
}

fcml_ceh_error fcml_fn_asm_get_instruction_encodings( fcml_coll_map instructions_map, fcml_string mnemonic, fcml_st_asm_instruction_addr_modes **addr_modes ) {

	if( !instructions_map ) {
		return FCML_CEH_GEC_NOT_INITIALIZED;
	}

	*addr_modes = (fcml_st_asm_instruction_addr_modes*)fcml_fn_coll_map_get( instructions_map, mnemonic );
	if( !*addr_modes ) {
		return FCML_CEH_GEC_UNKNOWN_MNEMONIC;
	}

	return FCML_CEH_GEC_NO_ERROR;
}

