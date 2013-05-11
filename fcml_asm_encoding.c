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
 * Instruction encoders.
 *********************************/

fcml_ceh_error fcml_fnp_asm_instruction_encoder_IA( fcml_st_asm_encoding_context *context, struct fcml_st_asm_instruction_addr_modes *addr_modes ) {
	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
	return error;
}

/****************************************
 * Processor part factories.
 ****************************************/

void fcml_ifn_asm_free_part_processor_chain( fcml_ifn_asm_instruction_part_processor_chain *chain ) {
	if( chain ) {
		fcml_ifn_asm_free_part_processor_chain( chain->next_processor );
		fcml_fn_env_memory_free( chain );
	}
}

// Simple operand encoder.
void fcml_ifn_asm_instruction_part_processor_simple_opcode_encoder( fcml_st_asm_encoding_context *context ) {
}

fcml_ifn_asm_instruction_part_processor fcml_ifn_asm_instruction_part_processor_factory_simple_opcode_encoder( fcml_st_def_instruction_description *instruction, fcml_st_def_addr_mode_desc *addr_mode, fcml_ien_asm_instruction_part_processor_type *processor_type ) {
	*processor_type = FCML_IEN_ASM_IPPT_ENCODER;
	return fcml_ifn_asm_instruction_part_processor_simple_opcode_encoder;
}

// List of instruction part encoders for IA instructions.
fcml_ifn_asm_instruction_part_processor_factory fcml_asm_instruction_part_processor_factories_for_IT[] = {
	fcml_ifn_asm_instruction_part_processor_factory_simple_opcode_encoder,
	NULL
};

fcml_ifn_asm_instruction_part_processor_chain* fcml_ifn_asm_instruction_part_processor_factory_dispatcher_IT( fcml_st_def_instruction_description *instruction, fcml_st_def_addr_mode_desc *addr_mode ) {
	fcml_ifn_asm_instruction_part_processor_chain *chain = fcml_fn_env_clear_memory_alloc( sizeof( fcml_ifn_asm_instruction_part_processor_chain ) );
	fcml_ifn_asm_instruction_part_processor_chain *current_chain = chain;
	if( !chain ) {
		return NULL;
	}
	fcml_ifn_asm_instruction_part_processor_factory *current_factory = &fcml_asm_instruction_part_processor_factories_for_IT[0];
	while( *current_factory ) {
		fcml_ien_asm_instruction_part_processor_type processor_type;
		fcml_ifn_asm_instruction_part_processor processor = (*current_factory)( instruction, addr_mode, &processor_type );
		if( processor ) {
			current_chain->processor = processor;
			current_chain->processor_type = processor_type;
			current_chain->next_processor = fcml_fn_env_clear_memory_alloc( sizeof( fcml_ifn_asm_instruction_part_processor_chain ) );
			current_chain = current_chain->next_processor;
			if( !current_chain ) {
				fcml_ifn_asm_free_part_processor_chain( chain );
				return NULL;
			}
		}
		current_factory++;
	}
	return chain;
}

fcml_ifn_asm_instruction_part_processor_factory_dispatcher fcml_ifn_get_instruction_part_processor_factory_dispatcher_for_instruction_type( fcml_en_def_instruction_type instruction_type ) {
	fcml_ifn_asm_instruction_part_processor_factory_dispatcher dispatcher = NULL;
	switch( instruction_type ) {
	case FCML_EN_IT_IA:
		dispatcher = fcml_ifn_asm_instruction_part_processor_factory_dispatcher_IT;
		break;
	}
	return dispatcher;
}

/*********************************
 * Operand encoders.
 *********************************/

fcml_bool fcml_fnp_asm_operand_encoder_imm( fcml_st_operand *operand_def, fcml_st_asm_encoded_operand *operand_enc ) {
	return FCML_FALSE;
}

fcml_bool fcml_fnp_asm_operand_encoder_explicit_reg( fcml_st_operand *operand_def, fcml_st_asm_encoded_operand *operand_enc ) {return FCML_FALSE;
	return FCML_FALSE;
}

fcml_bool fcml_fnp_asm_operand_encoder_opcode_reg( fcml_st_operand *operand_def, fcml_st_asm_encoded_operand *operand_enc ) {
	return FCML_FALSE;
}

fcml_bool fcml_fnp_asm_operand_encoder_immediate_dis_relative( fcml_st_operand *operand_def, fcml_st_asm_encoded_operand *operand_enc ) {
	return FCML_FALSE;
}

fcml_bool fcml_fnp_asm_operand_encoder_far_pointer( fcml_st_operand *operand_def, fcml_st_asm_encoded_operand *operand_enc ) {
	return FCML_FALSE;
}

fcml_bool fcml_fnp_asm_operand_encoder_far_pointer_indirect( fcml_st_operand *operand_def, fcml_st_asm_encoded_operand *operand_enc ) {
	return FCML_FALSE;
}

fcml_bool fcml_fnp_asm_operand_encoder_explicit_gps_reg_addressing( fcml_st_operand *operand_def, fcml_st_asm_encoded_operand *operand_enc ) {
	return FCML_FALSE;
}

fcml_bool fcml_fnp_asm_operand_encoder_explicit_ib( fcml_st_operand *operand_def, fcml_st_asm_encoded_operand *operand_enc ) {
	return FCML_FALSE;
}

fcml_bool fcml_fnp_asm_operand_encoder_segment_relative_offset( fcml_st_operand *operand_def, fcml_st_asm_encoded_operand *operand_enc ) {
	return FCML_FALSE;
}

fcml_bool fcml_fnp_asm_operand_encoder_rm( fcml_st_operand *operand_def, fcml_st_asm_encoded_operand *operand_enc ) {
	return FCML_FALSE;
}

fcml_bool fcml_fnp_asm_operand_encoder_r( fcml_st_operand *operand_def, fcml_st_asm_encoded_operand *operand_enc ) {
	return FCML_FALSE;
}

fcml_bool fcml_fnp_asm_operand_encoder_vex_vvvv( fcml_st_operand *operand_def, fcml_st_asm_encoded_operand *operand_enc ) {
	return FCML_FALSE;
}

fcml_bool fcml_fnp_asm_operand_encoder_is4( fcml_st_operand *operand_def, fcml_st_asm_encoded_operand *operand_enc ) {
	return FCML_FALSE;
}

fcml_bool fcml_fnp_asm_operand_encoder_vsib( fcml_st_operand *operand_def, fcml_st_asm_encoded_operand *operand_enc ) {
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

fcml_st_asm_instruction_addr_mode *fcml_ifn_asm_prepare_addr_mode( fcml_st_def_addr_mode_desc *addr_mode_desc, fcml_ceh_error *error ) {

	fcml_st_asm_instruction_addr_mode *addr_mode = (fcml_st_asm_instruction_addr_mode *)fcml_fn_env_memory_alloc( sizeof( fcml_st_asm_instruction_addr_mode ) );
	if( !addr_mode ) {
		*error = FCML_CEH_GEC_OUT_OF_MEMORY;
		return NULL;
	}

	memset( addr_mode, 0, sizeof( fcml_st_asm_instruction_addr_mode ) );

	addr_mode->addr_mode_desc = addr_mode_desc;

	// Prepares operand encoders one by one.
	int i;
	for( i = 0; i < FCML_OPERANDS_COUNT; i++ ) {
		addr_mode->operand_encoders[i] = fcml_ifn_asm_prepare_operand_encoder( addr_mode_desc->opperands[i], error );
		if( *error ) {
			// Something failed, so break whole process.
			fcml_fn_env_memory_free(addr_mode);
			addr_mode = NULL;
			break;
		}
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
	fcml_ifn_asm_free_addr_mode( addr_mode );
}

void fcml_ifn_asm_free_instruction_entry( fcml_ptr key, fcml_ptr value ) {
	fcml_st_asm_instruction_addr_modes *addr_modes = (fcml_st_asm_instruction_addr_modes*)value;
	if( addr_modes ) {
		if( addr_modes->addr_modes ) {
			fcml_fn_coll_list_free( addr_modes->addr_modes, fcml_ifn_asm_free_instruction_addr_mode_item_handler );
		}
		if( addr_modes->part_processor_chain ) {
			fcml_ifn_asm_free_part_processor_chain( addr_modes->part_processor_chain );
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

			fcml_ifn_asm_instruction_part_processor_factory_dispatcher factory_dispatcher = fcml_ifn_get_instruction_part_processor_factory_dispatcher_for_instruction_type( instruction->instruction_type );

			addr_modes->mnemonic = mnemonic;
			addr_modes->instruction_encoder = fcml_ifn_asm_choose_instruction_encoder( instruction->instruction_type );
			addr_modes->part_processor_chain = factory_dispatcher( instruction, addr_mode_desc );

			if( !(addr_modes->part_processor_chain) ) {
				*error = FCML_CEH_GEC_OUT_OF_MEMORY;
				fcml_fn_coll_list_free( addr_modes->addr_modes, fcml_ifn_asm_free_instruction_addr_mode_item_handler );
				fcml_fn_env_memory_free(addr_modes);
				break;
			}

			// Puts prepared structure under mnemonic key.
			fcml_fn_coll_map_put( instructions_map, mnemonic, addr_modes, error );
			if( *error ) {
				fcml_fn_coll_list_free( addr_modes->addr_modes, fcml_ifn_asm_free_instruction_addr_mode_item_handler );
				fcml_fn_env_memory_free(addr_modes);
				break;
			}

		}

		fcml_st_asm_instruction_addr_mode *addr_mode = fcml_ifn_asm_prepare_addr_mode( addr_mode_desc, error );
		if( *error ) {
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

