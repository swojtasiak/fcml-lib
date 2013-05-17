/*
 * fcml_asm_encoding.c
 *
 *  Created on: 31-03-2013
 *      Author: tAs
 */

#include <string.h>

#include "fcml_asm_encoding.h"
#include "fcml_def.h"
#include "fcml_coll.h"
#include "fcml_env.h"
#include "fcml_asm_errors.h"

fcml_coll_map instructions_map = NULL;

/*********************************
 * Operand encoders.
 *********************************/

fcml_bool fcml_fnp_asm_operand_encoder_imm( fcml_ien_asm_part_processor_phase phase, fcml_st_asm_encoding_context *context, fcml_st_def_decoded_addr_mode *addr_mode, fcml_st_operand *operand_def, fcml_st_asm_instruction_part *operand_enc ) {
	return FCML_FALSE;
}

fcml_bool fcml_fnp_asm_operand_encoder_explicit_reg( fcml_ien_asm_part_processor_phase phase, fcml_st_asm_encoding_context *context, fcml_st_def_decoded_addr_mode *addr_mode, fcml_st_operand *operand_def, fcml_st_asm_instruction_part *operand_enc ) {
	return FCML_FALSE;
}

fcml_bool fcml_fnp_asm_operand_encoder_opcode_reg( fcml_ien_asm_part_processor_phase phase, fcml_st_asm_encoding_context *context, fcml_st_def_decoded_addr_mode *addr_mode, fcml_st_operand *operand_def, fcml_st_asm_instruction_part *operand_enc ) {
	return FCML_FALSE;
}

fcml_bool fcml_fnp_asm_operand_encoder_immediate_dis_relative( fcml_ien_asm_part_processor_phase phase, fcml_st_asm_encoding_context *context, fcml_st_def_decoded_addr_mode *addr_mode, fcml_st_operand *operand_def, fcml_st_asm_instruction_part *operand_enc ) {
	return FCML_FALSE;
}

fcml_bool fcml_fnp_asm_operand_encoder_far_pointer( fcml_ien_asm_part_processor_phase phase, fcml_st_asm_encoding_context *context, fcml_st_def_decoded_addr_mode *addr_mode, fcml_st_operand *operand_def, fcml_st_asm_instruction_part *operand_enc ) {
	return FCML_FALSE;
}

fcml_bool fcml_fnp_asm_operand_encoder_far_pointer_indirect( fcml_ien_asm_part_processor_phase phase, fcml_st_asm_encoding_context *context, fcml_st_def_decoded_addr_mode *addr_mode, fcml_st_operand *operand_def, fcml_st_asm_instruction_part *operand_enc ) {
	return FCML_FALSE;
}

fcml_bool fcml_fnp_asm_operand_encoder_explicit_gps_reg_addressing( fcml_ien_asm_part_processor_phase phase, fcml_st_asm_encoding_context *context, fcml_st_def_decoded_addr_mode *addr_mode, fcml_st_operand *operand_def, fcml_st_asm_instruction_part *operand_enc ) {
	return FCML_FALSE;
}

fcml_bool fcml_fnp_asm_operand_encoder_explicit_ib( fcml_ien_asm_part_processor_phase phase, fcml_st_asm_encoding_context *context, fcml_st_def_decoded_addr_mode *addr_mode, fcml_st_operand *operand_def, fcml_st_asm_instruction_part *operand_enc ) {
	return FCML_FALSE;
}

fcml_bool fcml_fnp_asm_operand_encoder_segment_relative_offset( fcml_ien_asm_part_processor_phase phase, fcml_st_asm_encoding_context *context, fcml_st_def_decoded_addr_mode *addr_mode, fcml_st_operand *operand_def, fcml_st_asm_instruction_part *operand_enc ) {
	return FCML_FALSE;
}

fcml_bool fcml_fnp_asm_operand_encoder_rm( fcml_ien_asm_part_processor_phase phase, fcml_st_asm_encoding_context *context, fcml_st_def_decoded_addr_mode *addr_mode, fcml_st_operand *operand_def, fcml_st_asm_instruction_part *operand_enc ) {
	return FCML_FALSE;
}

fcml_bool fcml_fnp_asm_operand_encoder_r( fcml_ien_asm_part_processor_phase phase, fcml_st_asm_encoding_context *context, fcml_st_def_decoded_addr_mode *addr_mode, fcml_st_operand *operand_def, fcml_st_asm_instruction_part *operand_enc ) {
	return FCML_FALSE;
}

fcml_bool fcml_fnp_asm_operand_encoder_vex_vvvv( fcml_ien_asm_part_processor_phase phase, fcml_st_asm_encoding_context *context, fcml_st_def_decoded_addr_mode *addr_mode, fcml_st_operand *operand_def, fcml_st_asm_instruction_part *operand_enc ) {
	return FCML_FALSE;
}

fcml_bool fcml_fnp_asm_operand_encoder_is4( fcml_ien_asm_part_processor_phase phase, fcml_st_asm_encoding_context *context, fcml_st_def_decoded_addr_mode *addr_mode, fcml_st_operand *operand_def, fcml_st_asm_instruction_part *operand_enc ) {
	return FCML_FALSE;
}

fcml_bool fcml_fnp_asm_operand_encoder_vsib( fcml_ien_asm_part_processor_phase phase, fcml_st_asm_encoding_context *context, fcml_st_def_decoded_addr_mode *addr_mode, fcml_st_operand *operand_def, fcml_st_asm_instruction_part *operand_enc ) {
	return FCML_FALSE;
}

fcml_fnp_asm_operand_encoder fcml_def_operand_encoders[] = {
	NULL,
	fcml_fnp_asm_operand_encoder_imm,
	fcml_fnp_asm_operand_encoder_explicit_reg,
	fcml_fnp_asm_operand_encoder_opcode_reg,
	fcml_fnp_asm_operand_encoder_immediate_dis_relative,
	fcml_fnp_asm_operand_encoder_far_pointer,
	fcml_fnp_asm_operand_encoder_far_pointer_indirect,
	fcml_fnp_asm_operand_encoder_explicit_gps_reg_addressing,
	fcml_fnp_asm_operand_encoder_explicit_ib,
	fcml_fnp_asm_operand_encoder_segment_relative_offset,
	fcml_fnp_asm_operand_encoder_rm,
	fcml_fnp_asm_operand_encoder_r,
	fcml_fnp_asm_operand_encoder_vex_vvvv,
	fcml_fnp_asm_operand_encoder_is4,
	fcml_fnp_asm_operand_encoder_vsib
};

/*********************************
 * Instruction encoders.
 *********************************/

void fcml_ifp_coll_list_action_free_instruction_part( fcml_ptr item_value, fcml_ptr *args ) {
	// Free instruction part.
	fcml_fn_env_memory_free( item_value );
}

void fcml_fn_free_instruction_parts( fcml_st_coll_list *instruction_parts ) {
	if( instruction_parts ) {
		fcml_fn_coll_list_free( instruction_parts, fcml_ifp_coll_list_action_free_instruction_part );
	}
}

fcml_ceh_error fcml_ifn_asm_alloc_instruction_part( fcml_st_asm_instruction_encoding_context *encoding_context, fcml_st_asm_instruction_part **part ) {
	if( !encoding_context->instruction_parts ) {
		encoding_context->instruction_parts = fcml_fn_coll_list_alloc();
		if( !encoding_context->instruction_parts ) {
			return FCML_CEH_GEC_OUT_OF_MEMORY;
		}
		*part = (fcml_st_asm_instruction_part *)fcml_fn_env_clear_memory_alloc( sizeof(fcml_st_asm_instruction_part) );
		if( !fcml_fn_coll_list_add_back( encoding_context->instruction_parts, *part ) ) {
			fcml_fn_free_instruction_parts( encoding_context->instruction_parts );
			encoding_context->instruction_parts = NULL;
			return FCML_CEH_GEC_OUT_OF_MEMORY;
		}
	}
	return FCML_CEH_GEC_NO_ERROR;
}

fcml_bool fcml_ifn_asm_accept_addr_mode( fcml_ifn_asm_instruction_part_processor_chain *part_processor_chain, fcml_st_instruction *instruction ) {
	fcml_ifn_asm_instruction_part_processor_chain *current_processor = part_processor_chain;
	while(current_processor) {
		fcml_ifn_asm_instruction_part_processor_descriptor *descriptor = &(current_processor->processor_descriptor);
		if( !descriptor->processor_acceptor( instruction, descriptor->processor_args ) ) {
			return FCML_FALSE;
		}
		current_processor = current_processor->next_processor;
	}
	return FCML_TRUE;
}

fcml_ceh_error fcml_ifn_asm_process_addr_mode( fcml_st_asm_encoding_context *context, fcml_ifn_asm_instruction_part_processor_chain *part_processor_chain ) {

	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
	fcml_st_asm_instruction_encoding_context *encoding_context = &(context->instruction_context);

	// First phase.
	fcml_ifn_asm_instruction_part_processor_chain *current_processor = part_processor_chain;
	fcml_st_asm_instruction_part *instruction_part = NULL;
	while(current_processor) {
		fcml_ifn_asm_instruction_part_processor_descriptor *descriptor = &(current_processor->processor_descriptor);
		if( descriptor->processor_type == FCML_IEN_ASM_IPPT_ENCODER ) {
			if( instruction_part ) {
				error = fcml_ifn_asm_alloc_instruction_part( encoding_context, &instruction_part );
				if( error ) {
					break;
				}
			}
		}
		error = descriptor->processor( FCML_IEN_ASM_IPPP_FIRST_PHASE, context, instruction_part, descriptor->processor_args );
		if( error ) {
			// Something failed.
			break;
		}
		current_processor = current_processor->next_processor;
	}

	// Second phase.
	fcml_st_coll_list_element *current_part = NULL;
	current_processor = part_processor_chain->next_processor;
	while(current_processor) {
		fcml_ifn_asm_instruction_part_processor_descriptor *descriptor = &(current_processor->processor_descriptor);
		if( descriptor->processor_type == FCML_IEN_ASM_IPPT_ENCODER ) {
			if( !current_part ) {
				current_part = encoding_context->instruction_parts->head;
			} else {
				current_part = current_part->next;
			}
		}
		error = descriptor->processor( FCML_IEN_ASM_IPPP_SECOND_PHASE, context, (fcml_st_asm_instruction_part *)current_part->item, descriptor->processor_args );
		if( error ) {
			// Something failed.
			break;
		}
		current_processor = current_processor->next_processor;
	}

	return error;
}

fcml_ceh_error fcml_fnp_asm_instruction_encoder_IA( fcml_st_asm_encoding_context *context, struct fcml_st_asm_instruction_addr_modes *addr_modes ) {
	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
	if( addr_modes ) {
		fcml_st_asm_instruction_encoding_context instruction_context;
		fcml_mem_clear(&instruction_context, sizeof(fcml_st_asm_instruction_encoding_context));

		// Choose addressing mode.
		if( addr_modes->addr_modes->size ) {

			fcml_st_asm_instruction_addr_mode *chosen_addr_mode = NULL;

			fcml_st_coll_list_element *addr_mode_element = addr_modes->addr_modes->head;
			while( addr_mode_element ) {
				fcml_st_asm_instruction_addr_mode *addr_mode = (fcml_st_asm_instruction_addr_mode *)addr_mode_element->item;
				if( fcml_ifn_asm_accept_addr_mode( addr_mode->part_processor_chain, context->instruction ) ) {
					chosen_addr_mode = addr_mode;
					break;
				}
				addr_mode_element = addr_mode_element->next;
			}

			// Use chosen addressing mode to build instruction parts.
			if( chosen_addr_mode ) {
				error = fcml_ifn_asm_process_addr_mode( context, chosen_addr_mode->part_processor_chain );
			} else {
				error = FCML_EN_ASM_UNSUPPORTED_ADDRESSING_MODE;
			}

		} else {
			// There is no addressing mode for given instruction. It should never happened, so it's an internal bug.
			error = FCML_CEH_GEC_INTERNAL_BUG;
		}
	}
	return error;
}

/****************************************
 * Processor part factories.
 ****************************************/

void fcml_ifn_asm_free_part_processor_chain( fcml_ifn_asm_instruction_part_processor_chain *chain ) {
	if( chain ) {
		fcml_ifn_asm_free_part_processor_chain( chain->next_processor );
		fcml_ifn_asm_instruction_part_processor_descriptor *descriptor = &(chain->processor_descriptor);
		if( descriptor->processor_args_deallocator ) {
			descriptor->processor_args_deallocator( descriptor->processor_args );
		}
		fcml_fn_env_memory_free( chain );
	}
}

//////////////////////////////////////
// Operand encoder wrapper factory. //
//////////////////////////////////////

struct fcml_ist_asm_operand_encoder_wrapper_args {
	// Decoder operand addressing.
	fcml_st_def_decoded_addr_mode *decoded_addr_mode;
	// Function responsible for encoding operand.
	fcml_fnp_asm_operand_encoder operand_encoder;
	// Index of the operand to encode.
	int operand_index;
};

void fcml_ifn_asm_processor_operand_encoder_args_deallocator( fcml_ptr ptr ) {
	struct fcml_ist_asm_operand_encoder_wrapper_args *wrapper_wrgs = (struct fcml_ist_asm_operand_encoder_wrapper_args*)ptr;
	if( wrapper_wrgs->decoded_addr_mode ) {
		fcml_fnp_def_free_addr_mode( wrapper_wrgs->decoded_addr_mode );
	}
	fcml_fn_env_memory_free( wrapper_wrgs );
}

fcml_bool fcml_ifn_asm_instruction_part_processor_acceptor_operand_encoder_wrapper( fcml_st_instruction *instruction, fcml_ptr args ) {
	struct fcml_ist_asm_operand_encoder_wrapper_args *wrapper_args = (struct fcml_ist_asm_operand_encoder_wrapper_args*)args;
	fcml_st_operand *operand = &(instruction->operands[wrapper_args->operand_index]);
	return wrapper_args->operand_encoder( FCML_IEN_ASM_IPPP_ACCEPT, NULL, wrapper_args->decoded_addr_mode, operand, NULL );
}

fcml_ceh_error fcml_ifn_asm_instruction_part_processor_operand_encoder_wrapper( fcml_ien_asm_part_processor_phase phase, fcml_st_asm_encoding_context *context, fcml_st_asm_instruction_part *instruction_part, fcml_ptr args ) {
	struct fcml_ist_asm_operand_encoder_wrapper_args *wrapper_args = (struct fcml_ist_asm_operand_encoder_wrapper_args*)args;
	fcml_st_operand *operand = &(context->instruction->operands[wrapper_args->operand_index]);
	return wrapper_args->operand_encoder( phase, context, wrapper_args->decoded_addr_mode, operand, instruction_part );
}

fcml_ifn_asm_instruction_part_processor_descriptor fcml_ifn_asm_instruction_part_processor_factory_operand_encoder_wrapper( fcml_uint32_t flags, fcml_st_def_instruction_description *instruction, fcml_st_def_addr_mode_desc *addr_mode, fcml_ceh_error *error ) {

	fcml_ifn_asm_instruction_part_processor_descriptor descriptor = {0};

	struct fcml_ist_asm_operand_encoder_wrapper_args *wrapper_args = fcml_fn_env_clear_memory_alloc( sizeof( struct fcml_ist_asm_operand_encoder_wrapper_args ) );
	if( !wrapper_args ) {
		*error = FCML_CEH_GEC_OUT_OF_MEMORY;
		return descriptor;
	}

	wrapper_args->decoded_addr_mode = fcml_fnp_def_decode_addr_mode_args( addr_mode->opperands[flags], error );
	if( *error ) {
		return descriptor;
	}

	wrapper_args->operand_encoder = fcml_def_operand_encoders[wrapper_args->decoded_addr_mode->addr_mode];
	wrapper_args->operand_index = flags;

	descriptor.processor_args_deallocator = fcml_ifn_asm_processor_operand_encoder_args_deallocator;
	descriptor.processor_type = FCML_IEN_ASM_IPPT_ENCODER;
	descriptor.processor = fcml_ifn_asm_instruction_part_processor_operand_encoder_wrapper;
	descriptor.processor_acceptor = fcml_ifn_asm_instruction_part_processor_acceptor_operand_encoder_wrapper;
	return descriptor;
}

////////////////////////////////////
// Simple opcode encoder factory. //
////////////////////////////////////

fcml_bool fcml_ifn_asm_instruction_part_processor_simple_opcode_encoder_acceptor( fcml_st_instruction *instruction, fcml_ptr args ) {
	// Simple opcode encoder can be always applied.
	return FCML_TRUE;
}

fcml_ceh_error fcml_ifn_asm_instruction_part_processor_simple_opcode_encoder( fcml_ien_asm_part_processor_phase phase, fcml_st_asm_encoding_context *context, fcml_st_asm_instruction_part *instruction_part, fcml_ptr args ) {
	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
	return error;
}

fcml_ifn_asm_instruction_part_processor_descriptor fcml_ifn_asm_instruction_part_processor_factory_simple_opcode_encoder( fcml_uint32_t flags, fcml_st_def_instruction_description *instruction, fcml_st_def_addr_mode_desc *addr_mode, fcml_ceh_error *error ) {
	fcml_ifn_asm_instruction_part_processor_descriptor descriptor = {0};
	descriptor.processor_type = FCML_IEN_ASM_IPPT_ENCODER;
	descriptor.processor_args = NULL;
	descriptor.processor = fcml_ifn_asm_instruction_part_processor_simple_opcode_encoder;
	descriptor.processor_acceptor = fcml_ifn_asm_instruction_part_processor_simple_opcode_encoder_acceptor;
	return descriptor;
}

typedef struct fcml_ist_asm_instruction_part_factory_details {
	fcml_ifn_asm_instruction_part_processor_factory factory;
	uint32_t flags;
} fcml_ist_asm_instruction_part_factory_details;

typedef struct fcml_ist_asm_instruction_part_factory_sequence {
	fcml_ist_asm_instruction_part_factory_details *details;
} fcml_ist_asm_instruction_part_factory_sequence;

// List of instruction part encoders for instruction opcode.
fcml_ist_asm_instruction_part_factory_details fcml_asm_instruction_part_processor_factories_opcode_for_IA[] = {
	{ fcml_ifn_asm_instruction_part_processor_factory_simple_opcode_encoder, 0 },
	{ NULL, 0 }
};

// List of instruction part encoders for instruction prefixes.
fcml_ist_asm_instruction_part_factory_details fcml_asm_instruction_part_processor_factories_prefixes_for_IA[] = {
	{ NULL, 0 }
};

// List of instruction part encoders for instruction operands.
fcml_ist_asm_instruction_part_factory_details fcml_asm_instruction_part_processor_factories_operands_for_IA[] = {
	{ NULL, 0 }
};

fcml_ist_asm_instruction_part_factory_sequence fcml_asm_instruction_part_processor_factory_sequences_for_IA[] = {
	{ fcml_asm_instruction_part_processor_factories_opcode_for_IA },
	{ fcml_asm_instruction_part_processor_factories_prefixes_for_IA },
	{ fcml_asm_instruction_part_processor_factories_operands_for_IA },
	{ NULL }
};

fcml_ifn_asm_instruction_part_processor_chain* fcml_ifn_asm_instruction_part_processor_factory_dispatcher_IA( fcml_st_def_instruction_description *instruction, fcml_st_def_addr_mode_desc *addr_mode, fcml_ceh_error *error ) {
	fcml_ifn_asm_instruction_part_processor_chain *chain = NULL;
	fcml_ifn_asm_instruction_part_processor_chain *current_chain = NULL;
	fcml_ist_asm_instruction_part_factory_sequence *current_factories_sequence = &fcml_asm_instruction_part_processor_factory_sequences_for_IA[0];
	while( current_factories_sequence->details ) {

		fcml_ist_asm_instruction_part_factory_details *current_factory = current_factories_sequence->details;
		while( current_factory->factory ) {
			fcml_ifn_asm_instruction_part_processor_descriptor descriptor = current_factory->factory( current_factory->flags, instruction, addr_mode, error );
			if( descriptor.processor ) {

				// Allocate chain element for new instruction part encoder.
				fcml_ifn_asm_instruction_part_processor_chain *new_chain = fcml_fn_env_clear_memory_alloc( sizeof( fcml_ifn_asm_instruction_part_processor_chain ) );
				if( !new_chain ) {
					*error = FCML_CEH_GEC_OUT_OF_MEMORY;
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

				break;
			}
			if( *error ) {
				fcml_ifn_asm_free_part_processor_chain( chain );
				return NULL;
			}
			current_factory++;
		}

		current_factories_sequence++;
	}
	return chain;
}

fcml_ifn_asm_instruction_part_processor_factory_dispatcher fcml_ifn_get_instruction_part_processor_factory_dispatcher_for_instruction_type( fcml_en_def_instruction_type instruction_type ) {
	fcml_ifn_asm_instruction_part_processor_factory_dispatcher dispatcher = NULL;
	switch( instruction_type ) {
	case FCML_EN_IT_IA:
		dispatcher = fcml_ifn_asm_instruction_part_processor_factory_dispatcher_IA;
		break;
	}
	return dispatcher;
}


/*

fcml_st_asm_operand_encoder fcml_ifn_asm_prepare_operand_encoder( fcml_uint32_t encoded_operand, fcml_ceh_error *error ) {
	fcml_st_asm_operand_encoder encoder = {0};
	if( encoded_operand != FCML_NA ) {
		encoder.decoded_addr_mode = fcml_fnp_def_decode_addr_mode_args(encoded_operand, error );
		if( !*error ) {
			// Choose operand encoder.
			encoder.operand_encoder = fcml_def_operand_encoders[encoder.decoded_addr_mode->addr_mode];
		}
	}
	return encoder;
}
*/

fcml_st_asm_instruction_addr_mode *fcml_ifn_asm_prepare_addr_mode( fcml_st_def_instruction_description *instruction, fcml_st_def_addr_mode_desc *addr_mode_desc, fcml_ceh_error *error ) {

	fcml_st_asm_instruction_addr_mode *addr_mode = (fcml_st_asm_instruction_addr_mode *)fcml_fn_env_clear_memory_alloc( sizeof( fcml_st_asm_instruction_addr_mode ) );
	if( !addr_mode ) {
		*error = FCML_CEH_GEC_OUT_OF_MEMORY;
		return NULL;
	}

	addr_mode->addr_mode_desc = addr_mode_desc;

	fcml_ifn_asm_instruction_part_processor_factory_dispatcher factory_dispatcher = fcml_ifn_get_instruction_part_processor_factory_dispatcher_for_instruction_type( instruction->instruction_type );
	addr_mode->part_processor_chain = factory_dispatcher( instruction, addr_mode_desc, error );
	if( *error ) {
		fcml_fn_env_memory_free(addr_mode);
		addr_mode = NULL;
	}

	return addr_mode;
}

void fcml_ifn_asm_free_addr_mode( fcml_st_asm_instruction_addr_mode *addr_mode ) {
	if( addr_mode ) {
		fcml_fn_env_memory_free( addr_mode );
	}
}

void fcml_ifn_asm_free_instruction_addr_mode_item_handler( fcml_ptr item_value, fcml_ptr *args ) {
	fcml_st_asm_instruction_addr_mode *addr_mode = (fcml_st_asm_instruction_addr_mode*)item_value;
	if( addr_mode->part_processor_chain ) {
		fcml_ifn_asm_free_part_processor_chain( addr_mode->part_processor_chain );
	}
	fcml_ifn_asm_free_addr_mode( addr_mode );
}

void fcml_ifn_asm_free_instruction_entry( fcml_ptr key, fcml_ptr value ) {
	fcml_st_asm_instruction_addr_modes *addr_modes = (fcml_st_asm_instruction_addr_modes*)value;
	if( addr_modes ) {
		if( addr_modes->addr_modes ) {
			fcml_fn_coll_list_free( addr_modes->addr_modes, fcml_ifn_asm_free_instruction_addr_mode_item_handler );
		}
		fcml_fn_env_memory_free( addr_modes );
	}
}

fcml_fnp_asm_instruction_encoder fcml_ifn_asm_choose_instruction_encoder( fcml_en_def_instruction_type instruction_type ) {
	fcml_fnp_asm_instruction_encoder encoder = NULL;
	switch( instruction_type ) {
	case FCML_EN_IT_IA:
		encoder = fcml_fnp_asm_instruction_encoder_IA;
		break;
	}
	return encoder;
}

void fcml_ifn_asm_add_instruction_encoding( fcml_st_def_instruction_description *instruction, fcml_ceh_error *error ) {

	// Prepare encoders for given instruction.
	int i;
	for( i = 0; i < instruction->opcode_desc_count; i++ ) {

		fcml_st_def_addr_mode_desc *addr_mode_desc = &(instruction->addr_modes[i]);

		fcml_string mnemonic = addr_mode_desc->mnemonic_override;
		if( !mnemonic ) {
			mnemonic = instruction->mnemonic;
		}

		fcml_st_asm_instruction_addr_modes *addr_modes = (fcml_st_asm_instruction_addr_modes*)fcml_fn_coll_map_get( instructions_map, mnemonic );
		if( !addr_modes ) {

			// Allocate space for new mnemonic.
			addr_modes = fcml_fn_env_memory_alloc( sizeof(fcml_st_asm_instruction_addr_modes) );
			if( !addr_modes ) {
				// Out of memory.
				*error = FCML_CEH_GEC_OUT_OF_MEMORY;
				break;
			}

			// Allocate list for addresing modes.
			addr_modes->addr_modes = fcml_fn_coll_list_alloc();
			if( !(addr_modes->addr_modes) ) {
				fcml_fn_env_memory_free(addr_modes);
				*error = FCML_CEH_GEC_OUT_OF_MEMORY;
				break;
			}

			addr_modes->mnemonic = mnemonic;
			addr_modes->instruction_encoder = fcml_ifn_asm_choose_instruction_encoder( instruction->instruction_type );

			// Puts prepared structure under mnemonic key.
			fcml_fn_coll_map_put( instructions_map, mnemonic, addr_modes, error );
			if( *error ) {
				fcml_fn_coll_list_free( addr_modes->addr_modes, fcml_ifn_asm_free_instruction_addr_mode_item_handler );
				fcml_fn_env_memory_free(addr_modes);
				break;
			}

		}

		fcml_st_asm_instruction_addr_mode *addr_mode = fcml_ifn_asm_prepare_addr_mode( instruction, addr_mode_desc, error );
		if( !*error ) {
			if( !fcml_fn_coll_list_add_front( addr_modes->addr_modes, addr_mode ) ) {
				*error = FCML_CEH_GEC_OUT_OF_MEMORY;
				fcml_ifn_asm_free_addr_mode( addr_mode );
				break;
			}
		} else {
			break;
		}

		addr_mode_desc++;
	}
}

fcml_ceh_error fcml_fn_asm_init_instruction_encodings() {

	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

	// Allocate map for all instructions.
	fcml_st_coll_map_descriptor inst_map_desc = fcml_coll_map_descriptor_string;
	inst_map_desc.entry_free_function = fcml_ifn_asm_free_instruction_entry;

	instructions_map = fcml_fn_coll_map_alloc( &inst_map_desc, 64, &error );
	if( !instructions_map ) {
		return error;
	}

	int i = 0;
	fcml_st_def_instruction_description *instruction = &(fcml_ext_instructions_def[i++]);
	while( instruction->mnemonic && !error ) {
		fcml_ifn_asm_add_instruction_encoding( instruction, &error );
		instruction = &(fcml_ext_instructions_def[i++]);
	}

	if( error ) {
		// Something failed, so free everything that have been properly allocated.
		fcml_fn_asm_free_instruction_encodings();
	}

	return error;

}

void fcml_fn_asm_free_instruction_encodings() {
	if( instructions_map ) {
		fcml_fn_coll_map_free( instructions_map );
		instructions_map = NULL;
	}
}

fcml_ceh_error fcml_fn_asm_get_instruction_encodings( fcml_string mnemonic, fcml_st_asm_instruction_addr_modes **addr_modes ) {

	if( !instructions_map ) {
		return FCML_CEH_GEC_NOT_INITIALIZED;
	}

	*addr_modes = (fcml_st_asm_instruction_addr_modes*)fcml_fn_coll_map_get( instructions_map, mnemonic );
	if( !*addr_modes ) {
		return FCML_EN_ASM_UNKNOWN_MNEMONIC;
	}

	return FCML_CEH_GEC_NO_ERROR;
}

