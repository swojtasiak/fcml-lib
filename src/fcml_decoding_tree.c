/*
 * fcml_asm_decoding_tree.c
 *
 *  Created on: Oct 13, 2013
 *      Author: tas
 */

#include <assert.h>
#include <math.h>

#include "fcml_env.h"
#include "fcml_decoding_tree.h"
#include "fcml_def.h"

/*********************************
 * Disassemblation tree support. *
 *********************************/

#define FCML_IDF_REG_FIELD_SIZE								3
#define FCML_IDF_CONDITION_FIELD_SIZE						4
#define FCML_IDF_REG_FIELD_POS								0

typedef struct fcml_ist_dt_dts_opcodes {
	fcml_uint8_t opcode_bytes[FCML_OPCODES_NUM];
} fcml_ist_dt_dts_opcodes;

typedef fcml_ceh_error ( *fcml_ifp_dt_dts_opcode_callback )( fcml_st_dt_decoding_tree *dec_tree, fcml_st_def_instruction_desc *instruction_desc, fcml_st_def_addr_mode_desc *opcode_desc, fcml_ist_dt_dts_opcodes *opcodes );

/* Sets opcode field into a opcode byte. */
fcml_uint8_t fcml_ifn_dt_dts_utils_set_opcode_byte_field( fcml_uint8_t opcode_byte, int opcode_field_pos, int field_size, fcml_uint8_t field_value ) {

	// Mask for opcode field.
	fcml_uint8_t bit_mask = 0x00;
	int i = 0;
	for( i = 0; i < field_size; i++ ) {
		bit_mask <<= 1;
		bit_mask |= 0x01;
	}
	bit_mask = ~bit_mask;

	// Preparing opcode with opcode_filed set.
	return ( opcode_byte & bit_mask ) | ( field_value << opcode_field_pos );
}

fcml_ceh_error fcml_ifn_dt_dts_default_opcode_callback( fcml_st_dt_decoding_tree *dec_tree, fcml_st_def_instruction_desc *instruction_desc, fcml_st_def_addr_mode_desc *opcode_desc, fcml_ist_dt_dts_opcodes *opcodes ) {

	fcml_st_dt_diss_tree_element **current_elements = &(dec_tree->opcode[0]);
	fcml_st_dt_diss_tree_element *element = NULL;

	// Looking for a node in the instruction tree where new instruction should be placed. If there is no
	// appropriate node a new one is allocated.
	int i;
	int opcode_num = FCML_DEF_OPCODE_FLAGS_OPCODE_NUM( opcode_desc->opcode_flags );
	for( i = 0; i < opcode_num; i++ ) {
		fcml_uint8_t opcode = opcodes->opcode_bytes[i];
		element = current_elements[opcode];
		if( !element ) {
			element = (fcml_st_dt_diss_tree_element*)fcml_fn_env_memory_alloc_clear( sizeof( fcml_st_dt_diss_tree_element ) );
			if( !element ) {
				return FCML_CEH_GEC_OUT_OF_MEMORY;
			}
			current_elements[opcode] = element;
		}
		// Get next level of opcodes for the next loop.
		current_elements = &(element->opcodes[0]);
	}

	if( !element->instruction_decoding_defs ) {
		element->instruction_decoding_defs = fcml_fn_coll_list_alloc();
		if( !element->instruction_decoding_defs ) {
			return FCML_CEH_GEC_OUT_OF_MEMORY;
		}
	}

	// Prepare instruction decoding.
	return dec_tree->prepare_callback( dec_tree->dialect_context, element, instruction_desc, opcode_desc );
}


/* Function used to calculate all instruction opcode bytes using recursion. */
fcml_ceh_error fcml_ifn_dt_dts_handle_next_opcode_byte( fcml_st_dt_decoding_tree *dec_tree, fcml_st_def_instruction_desc *instruction_desc, fcml_st_def_addr_mode_desc *opcode_desc, fcml_ist_dt_dts_opcodes *opcodes, fcml_ifp_dt_dts_opcode_callback callback, int opcode_bytes_count, int opcode_byte_num, int primary_opcode_byte_num ) {

	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

	// Get next opcode byte from instruction.
	if( opcode_byte_num == opcode_bytes_count ) {
		// There is no more opcode bytes available.
		return callback( dec_tree, instruction_desc, opcode_desc, opcodes );
	}

	fcml_uint8_t opcode_byte = opcode_desc->opcode[opcode_byte_num];

	// Check if this is an opcode with opcode fields.
	if( opcode_byte_num == primary_opcode_byte_num ) {

		fcml_uint32_t opcode_flags = opcode_desc->opcode_flags;

		int opcode_flags_pos = FCML_DEF_OPCODE_FLAGS_POS( opcode_flags );

		// Opcode field: REG and TTTN.
		if( FCML_DEF_OPCODE_FLAGS_OPCODE_FIELD_REG( opcode_flags ) || FCML_DEF_OPCODE_FLAGS_OPCODE_FIELD_TTTN( opcode_flags ) ) {

			int number_of_opcodes = 0;
			int field_size = 0;
			if( FCML_DEF_OPCODE_FLAGS_OPCODE_FIELD_REG( opcode_flags ) ) {
				number_of_opcodes = FCML_REG_FIELD_NUMBER_OF_REGISTERS;
				field_size = FCML_IDF_REG_FIELD_SIZE;
			} else if( FCML_DEF_OPCODE_FLAGS_OPCODE_FIELD_TTTN( opcode_flags ) ) {
				number_of_opcodes = FCML_REG_FIELD_NUMBER_OF_CONDITIONS;
				field_size = FCML_IDF_CONDITION_FIELD_SIZE;
			}

			int i;
			for( i = 0; i < number_of_opcodes && !error; i++ ) {
				// Prepare opcode byte with register/condition field.
				fcml_uint8_t encoded_opcode_byte = fcml_ifn_dt_dts_utils_set_opcode_byte_field( opcode_byte, opcode_flags_pos, field_size, (fcml_uint8_t)i );
				opcodes->opcode_bytes[opcode_byte_num] = encoded_opcode_byte;
				// Handle next opcode byte.
				error = fcml_ifn_dt_dts_handle_next_opcode_byte( dec_tree, instruction_desc, opcode_desc, opcodes, callback, opcode_bytes_count, opcode_byte_num + 1, primary_opcode_byte_num );
			}

			return error;
		}
	}

	// This is a plain opcode byte that shouldn't be modified in any way.
	opcodes->opcode_bytes[opcode_byte_num] = opcode_byte;
	// Handle next opcode byte.
	return fcml_ifn_dt_dts_handle_next_opcode_byte( dec_tree, instruction_desc, opcode_desc, opcodes, callback, opcode_bytes_count, opcode_byte_num + 1, primary_opcode_byte_num );
}

fcml_ceh_error fcml_ifn_dt_dts_iterate_through_all_opcodes( fcml_st_dt_decoding_tree *dec_tree, fcml_st_def_instruction_desc *instruction_desc, fcml_st_def_addr_mode_desc *opcode_desc, fcml_ifp_dt_dts_opcode_callback callback ) {

	// Number of opcode bytes.
	int opcode_bytes_count = FCML_DEF_OPCODE_FLAGS_OPCODE_NUM( opcode_desc->opcode_flags );

	// Opcode byte with potential flags.
	int primary_opcode_byte_num = FCML_DEF_OPCODE_FLAGS_PRIMARY_OPCODE(opcode_desc->opcode_flags );

	assert( primary_opcode_byte_num < opcode_bytes_count );

	fcml_ist_dt_dts_opcodes opcode = {{0}};

	// Handle all opcode bytes.
	return fcml_ifn_dt_dts_handle_next_opcode_byte( dec_tree, instruction_desc, opcode_desc, &opcode, callback, opcode_bytes_count, 0, primary_opcode_byte_num );
}

int fcml_ifn_dt_dts_update_disassemblation_tree( fcml_st_def_instruction_desc *instruction_desc_src, fcml_st_dt_decoding_tree *dec_tree ) {

	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

	// Get instruction description.
	int instruction_index = 0;
	while( instruction_desc_src[instruction_index].mnemonic != NULL && !error ) {
		struct fcml_st_def_instruction_desc *instruction_desc = &instruction_desc_src[instruction_index++];

		// Get description of the specific instruction form.
		int opcode_index = 0;
		for( opcode_index = 0; opcode_index < instruction_desc->opcode_desc_count; opcode_index++ ) {
			struct fcml_st_def_addr_mode_desc *opcode_desc = &(instruction_desc->addr_modes[opcode_index]);

			// Iterate through all opcode combination for this instruction form.
			int error = fcml_ifn_dt_dts_iterate_through_all_opcodes( dec_tree, instruction_desc, opcode_desc, &fcml_ifn_dt_dts_default_opcode_callback );
			if( error ) {
				break;
			}
		}
	}

	return error;
}

void fcml_ifn_dt_dts_free_instruction_decoding_element_handler( fcml_ptr item_value, fcml_ptr args ) {
	fcml_st_dt_decoding_tree *tree = (fcml_st_dt_decoding_tree *)args;
	if( tree->dispose_callback ) {
		tree->dispose_callback( tree->dialect_context, item_value );
	}
}

fcml_ceh_error fcml_fn_dt_dts_tree_init( fcml_st_dialect_context_int *dialect_context, fcml_st_dt_decoding_tree **tree, fcml_fp_dt_prepare_instruction_decoding_callback prepare_callback, fcml_fp_dt_dispose_instruction_decoding_callback dispose_callback ) {
	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

	fcml_st_dt_decoding_tree *dec_tree = fcml_fn_env_memory_alloc_clear( sizeof( fcml_st_dt_decoding_tree ) );
	if( dec_tree ) {
		dec_tree->dialect_context = dialect_context;
		dec_tree->prepare_callback = prepare_callback;
		dec_tree->dispose_callback = dispose_callback;
		error = fcml_ifn_dt_dts_update_disassemblation_tree( fcml_ext_instructions_def, dec_tree );
		if( !error ) {
			*tree = dec_tree;
		} else {
			fcml_fn_dt_dts_tree_free( dialect_context, dec_tree );
		}
	} else {
		error = FCML_CEH_GEC_OUT_OF_MEMORY;
	}

	return error;
}

void fcml_fn_dt_dts_tree_element_free( fcml_st_dialect_context_int *dialect_context, fcml_st_dt_decoding_tree *tree, fcml_st_dt_diss_tree_element *element ) {
	int i = 0;
	// Free all child elements.
	for( i = 0; i < FCML_DT_TREE_OPCODE_ARRAY_SIZE; i++ ) {
		fcml_st_dt_diss_tree_element *child_element = element->opcodes[i];
		if( child_element ) {
			fcml_fn_dt_dts_tree_element_free( dialect_context, tree, child_element );
		}
	}
	// Free element itself.
	fcml_st_coll_list *instruction_decoding_defs = element->instruction_decoding_defs;
	if( instruction_decoding_defs ) {
		fcml_fn_coll_list_free( instruction_decoding_defs, &fcml_ifn_dt_dts_free_instruction_decoding_element_handler, tree );
	}
	fcml_fn_env_memory_free( element );
}

void fcml_fn_dt_dts_tree_free( fcml_st_dialect_context_int *dialect_context, fcml_st_dt_decoding_tree *tree ) {
	int i = 0;
	// Free all child elements.
	for( i = 0; i < FCML_DT_TREE_OPCODE_ARRAY_SIZE; i++ ) {
		fcml_st_dt_diss_tree_element *element = tree->opcode[i];
		if( element ) {
			fcml_fn_dt_dts_tree_element_free( dialect_context, tree, element );
		}
	}
	// Free tree.
	fcml_fn_env_memory_free( tree );
}

#undef FCML_IDF_REG_FIELD_SIZE
#undef FCML_IDF_CONDITION_FIELD_SIZE
#undef FCML_IDF_REG_FIELD_POS
