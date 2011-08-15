
#include <string.h>
#include <stdlib.h>

#include "ira_int.h"
#include "ira.h"

#define _IRA_OPCODE_TABLE_SIZE	256

struct ira_diss_tree_opcode* _ira_disassemblation_tree[_IRA_OPCODE_TABLE_SIZE] = {NULL};

/* Validates and fills structure with data from user. */
void _ira_prepare_disassemble_info( struct ira_disassemble_info *info, struct ira_disassemble_result *result );

/* Adds new instructions to disassemblation tree. */
int _ira_update_disassemblation_tree( struct ira_instruction_desc *instruction_desc );

/* Add instruction decoding to disassemblation tree. */
int _ira_add_instruction_decoding( struct ira_diss_tree_opcode *inst_desc, struct ira_instruction_desc *instruction_desc, struct ira_opcode_desc *opcode_desc );

/* Free memory allocated during build phase of disassemblation tree. */
void _ira_free_disassemblation_tree( struct ira_diss_tree_opcode** disassemblation_tree );

/* Gets order of given decoding in the node of decoding tree. */
int _ira_get_decoding_order( struct ira_diss_tree_instruction_decoding* decoding );

/* Prepares disassemblation environment. */
int _ira_interpret_prefixes( struct ira_diss_context *context );

/* Interprets prefixes. */
int _ira_prepare_environment( struct ira_diss_context *context );

/* Default disassemblation when disassembler was unable to decode any instruction. */
int _ira_disassemble_default( struct ira_diss_context *context, struct ira_disassemble_result *result );

/* Instruction definitions. */
void _ira_identify_prefixes( struct ira_diss_context *context );

/* Maps internal error code to external error code. */
enum ira_result_code _ira_map_internall_error_code( int internal_error );

/* Chooses instruction variant for decoding. */
struct ira_diss_tree_instruction_decoding* _ira_choose_instruction( struct ira_diss_context *context, struct ira_diss_tree_instruction_decoding* instruction );

/* Factory method that returns operand decoder for given type. */
void _ira_prepare_operand_decoding( struct ira_operand_decoding *operand_decoding, uint8_t decoder_type );

/* Factory method that returns operand decoder for given type. */
ira_instruction_decoder _ira_choose_instruction_decoder( uint8_t instruction_type );

/* Returns 1 is there is given prefix found for given instruction. */
int _ira_diss_context_is_prefix_available( struct ira_diss_context *context, uint8_t prefix );

/* Gets prefix if it's available. */
struct ira_instruction_prefix* _ira_diss_context_get_prefix_if_available( struct ira_diss_context *context, uint8_t prefix );

/* Gets REX prefix. */
uint8_t _ira_diss_context_get_REX_prefix( struct ira_diss_context *context, int *found );

/* Maps OSA to general purpose register type. */
enum ira_register_type _ira_map_osa_to_register_type( struct ira_diss_context *context );

/* Instruction decoders. */

int _ira_instruction_decoder_IA( struct ira_diss_context *context, struct ira_diss_tree_instruction_decoding *instruction, struct ira_disassemble_result *result );

/* ModRM decoding */

/* Register configurations used for 16 bit addressing form decoding */

struct ira_register _ira_addressing_form_reg_array_16[8][2] = {
	{ { IRA_REG_GPR_16, _IRA_REG_BX }, { IRA_REG_GPR_16, _IRA_REG_SI } },
	{ { IRA_REG_GPR_16, _IRA_REG_BX }, { IRA_REG_GPR_16, _IRA_REG_DI } },
	{ { IRA_REG_GPR_16, _IRA_REG_BP }, { IRA_REG_GPR_16, _IRA_REG_SI } },
	{ { IRA_REG_GPR_16, _IRA_REG_BP }, { IRA_REG_GPR_16, _IRA_REG_DI } },
	{ { IRA_REG_GPR_16, _IRA_REG_SI }, { IRA_NO_REG, 0 } },
	{ { IRA_REG_GPR_16, _IRA_REG_DI }, { IRA_NO_REG, 0 } },
	{ { IRA_REG_GPR_16, _IRA_REG_BP }, { IRA_NO_REG, 0 } },
	{ { IRA_REG_GPR_16, _IRA_REG_BX }, { IRA_NO_REG, 0 } }
};

#define _IRA_MOD_RM_FLAGS_DECODE_ADDRESSING		1
#define _IRA_MOD_RM_FLAGS_DECODE_REG			2

int _ira_modrm_decoder( struct ira_diss_context *context, enum ira_register_type reg_type, int operand_size, uint8_t flags );

/* Opcode decoders. */

void _ira_opcode_decoder_reg( struct ira_instruction_operand *operand, enum ira_register_type reg_type, int reg );
int _ira_opcode_decoder_accumulator( struct ira_diss_context *context, struct ira_instruction_operand *operand, int args );
int _ira_opcode_decoder_immediate( struct ira_diss_context *context, struct ira_instruction_operand *operand, int args );
int _ira_opcode_decoder_immediate_extends_eosa( struct ira_diss_context *context, struct ira_instruction_operand *operand, int args );
int _ira_opcode_decoder_modrm_rm_8( struct ira_diss_context *context, struct ira_instruction_operand *operand, int args );
int _ira_opcode_decoder_modrm_rm( struct ira_diss_context *context, struct ira_instruction_operand *operand, enum ira_register_type reg_type, int operand_register_size );
int _ira_opcode_decoder_modrm_r_8( struct ira_diss_context *context, struct ira_instruction_operand *operand, int args );
int _ira_opcode_decoder_modrm_r( struct ira_diss_context *context, struct ira_instruction_operand *operand, enum ira_register_type reg_type, int operand_register_size );
int _ira_opcode_decoder_modrm_rm_easa( struct ira_diss_context *context, struct ira_instruction_operand *operand, int args );
int _ira_opcode_decoder_modrm_r_eosa( struct ira_diss_context *context, struct ira_instruction_operand *operand, int args );

/* Decoders' helpers methods. */

/* Maps decoded addressing form from ModR/M to given operand. */
int _ira_modrm_decoder_operand_fill_address( struct ira_diss_context *context, struct ira_instruction_operand *operand );

/* Maps decoded register from ModR/M to given operand. */
int _ira_modrm_decoder_operand_fill_register( struct ira_diss_context *context, struct ira_instruction_operand *operand );

/* Calculates effective address-size attribute */
int _ira_get_effective_asa( struct ira_diss_context *context );

/* Calculates effective operand-size attribute */
int _ira_get_effective_osa( struct ira_diss_context *context );

/* Decodes immediate data. */
int _ira_decode_immediate( struct ira_diss_context *context, struct ira_immediate_data *data, int size );

/* Decodes displacement */
int _ira_decode_displacement( struct ira_diss_context *context, struct ira_displacement *displacement, int size, int extension_size );

/* End of opcode decoders. */

void ira_disassemble( struct ira_disassemble_info *info, struct ira_disassemble_result *result ) {

    // Validate info structure.
    _ira_prepare_disassemble_info( info, result );
    if( result->code != RC_OK ) {
        return;
    }

    // Prepare stream.
    struct ira_memory_stream stream;
    stream.base_address = info->address;
    stream.size = info->size;
    stream.offset = 0;

    // Prepare disassemble context.
    struct ira_diss_context context = {0};
    context.stream = &stream;
    context.mode = info->mode;
    context.address_size_attribute = info->address_size_attribute;
    context.operand_size_attribute = info->operand_size_attribute;

    // Identify prefixes.
    _ira_identify_prefixes( &context );

    // Prepares environment for disassemblation.
    _ira_prepare_environment( &context );

    // Found instruction.
    struct ira_diss_tree_instruction_decoding *instruction = NULL;
    // Current opcode table used to find instruction description.
    struct ira_diss_tree_opcode** opcodes = _ira_disassemblation_tree;

    int opcode_length = 0;
    while( opcodes != NULL ) {
    	// Get next potential opcode byte from stream.
    	int result;
    	uint8_t opcode_byte =_ira_stream_peek( context.stream, &result );
    	if( result == 0 ) {
    		break;
    	}

    	// This length is used to restore stream position in some cases.
    	opcode_length++;

    	// Check if there is instruction for this opcode.
    	struct ira_diss_tree_opcode *opcode = opcodes[opcode_byte];
    	if( opcode != NULL ) {
    		// Last found instruction.
    		instruction = opcode->instructions;
    		opcodes = opcode->opcodes;
    		// Go to next opcode byte.
    		_ira_stream_seek( context.stream, 1, IRA_CURRENT );
    	} else {
    		break;
    	}
    }

    int default_diss = 1;

    // Start disassemblation.
    if( instruction != NULL ) {
    	// Choose appropriate instruction variant.
    	instruction = _ira_choose_instruction( &context, instruction );
    	if( instruction != NULL ) {
    		int rc = instruction->instruction_decoder( &context, instruction, result );
    		if( rc != _IRA_INT_ERROR_NO_ERROR ) {
    			if( rc != _IRA_INT_ERROR_CODE_UNEXPECTED_EOS ) {
    				result->code = _ira_map_internall_error_code( rc );
    				default_diss = 0;
    			}
    		} else {
    			default_diss = 0;
    		}
    	}
    }

    if( default_diss ) {
    	// Instruction wasn't found, so restore stream and start default disassemblation process.
    	_ira_stream_seek( context.stream, opcode_length * -1, IRA_CURRENT );
    	if( _ira_disassemble_default( &context, result ) == _IRA_INT_ERROR_CODE_UNEXPECTED_EOS ) {
    		result->code = RC_ERROR_INSTRUCTION_INCOMPLETE;
    		return;
    	}
    }

    // Calculate instruction size basing on the stream.
    result->instruction_size = stream.offset;

    // Copy instruction code.
    memcpy( result->instruction_code, stream.base_address, result->instruction_size );
}

enum ira_result_code _ira_map_internall_error_code( int internal_error ) {
	switch( internal_error ) {
	case _IRA_INT_ERROR_NO_ERROR:
		return RC_OK;
	case _IRA_INT_ERROR_CODE_UNEXPECTED_EOS:
		return RC_ERROR_INSTRUCTION_INCOMPLETE;
	case _IRA_INT_ERROR_OUT_OF_MEMORY:
		return RC_ERROR_OUT_OF_MEMORY;
	}
	return RC_ERROR_UNEXPECTED_INTERNAL_ERROR;
}

struct ira_diss_tree_instruction_decoding* _ira_choose_instruction( struct ira_diss_context *context, struct ira_diss_tree_instruction_decoding* instruction ) {

	struct ira_diss_tree_instruction_decoding *current = instruction;

	do {

		// Check prefixes.
		int prefixes_ok = 0;
		// TODO: These two following conditions are probably not necessary!
		/*if( _IRA_PREFIX_REX_W_0( current->allowed_prefixes ) ) {
			// REX prefix with W byte = 0 is allowed and is silently ignored.
			int rex_found = 0;
			uint8_t rex = _ira_diss_context_get_REX_prefix(context, &rex_found);
			prefixes_ok = ( !rex_found || !_IRA_REX_W( rex ) );
		} else*/

		if( _IRA_PREFIX_REX_W_1( current->allowed_prefixes ) ) {
			int rex_found = 0;
			uint8_t rex = _ira_diss_context_get_REX_prefix(context, &rex_found);
			prefixes_ok = ( rex_found && _IRA_REX_W( rex ) );
		} /*else if( !_IRA_PREFIX_REX( current->allowed_prefixes ) ) {
			// Check if REX prefix doesn't present. REX prefix can be identified only in
			// 64 bit mode, so there is no need to check mode.
			int found;
			_ira_diss_context_get_REX_prefix(context, &found);
			prefixes_ok = !found;
		}*/ else if( _IRA_PREFIX_MANDATORY_66( current->allowed_prefixes ) ) {
			prefixes_ok = _ira_diss_context_is_prefix_available(context, 0x66);
		} else if( _IRA_PREFIX_MANDATORY_F2( current->allowed_prefixes ) ) {
			prefixes_ok = _ira_diss_context_is_prefix_available(context, 0xF2);
		} else if( _IRA_PREFIX_MANDATORY_F3( current->allowed_prefixes ) ) {
			prefixes_ok = _ira_diss_context_is_prefix_available(context, 0xF3);
		} else {
			prefixes_ok = 1;
		}
		if( !prefixes_ok ) {
			// Something wrong with prefixes, so go to the next instruction.
			continue;
		}

		// Check opcode extension.
		int opcodes_ok = 0;
		if( _IRA_OPCODE_FLAGS_OPCODE_IS_REX_EXT( current->opcode_flags ) ) {
			// Instruction with ModRM opcode extension extended by R field of REX prefix.
			int rex_found = 0;
			int modrm_found = 0;
			uint8_t rex = _ira_diss_context_get_REX_prefix(context, &rex_found);
			uint8_t modrm = _ira_stream_peek(context->stream, &modrm_found );
			if( modrm_found && rex_found ) {
				uint8_t ext_reg_opcode = ( ( rex & 0x04 ) << 1 ) | ( _IRA_MODRM_REG_OPCODE( modrm ) );
				uint8_t expected_ext_reg_opcode = _IRA_OPCODE_FLAGS_OPCODE_REX_EXT(current->opcode_flags);
				opcodes_ok = ( ext_reg_opcode == expected_ext_reg_opcode );
			}
		} else if( _IRA_OPCODE_FLAGS_OPCODE_IS_EXT( current->opcode_flags ) ) {
			int modrm_found;
			uint8_t modrm = _ira_stream_peek(context->stream, &modrm_found );
			opcodes_ok = ( modrm_found && _IRA_MODRM_REG_OPCODE( modrm ) == _IRA_OPCODE_FLAGS_OPCODE_EXT(current->opcode_flags) );
		} else {
			opcodes_ok = 1;
		}
		if( !opcodes_ok ) {
			// Something wrong with prefixes, so go to the next instruction.
			continue;
		}

		// This is instruction we was looking for, so return it.
		break;

	} while( ( current = current->next_instruction_decoding ) != NULL );

	return current;
}

enum ira_result_code ira_init(void) {
	// Clear disassemblation tree.
	memset( _ira_disassemblation_tree, 0, sizeof( _ira_disassemblation_tree ) );
	// Builds disassemblation tree basing on predefined instruction set.
	return _ira_map_internall_error_code( _ira_update_disassemblation_tree( _ira_instructions_desc ) );
}

void ira_deinit(void) {
	// Free whole disassemblation tree.
	_ira_free_disassemblation_tree( _ira_disassemblation_tree );
}

/* Disassemblation. */

int _ira_prepare_environment( struct ira_diss_context *context ) {
	return _IRA_INT_ERROR_NO_ERROR;
}

int _ira_interpret_prefixes( struct ira_diss_context *context ) {
	return _IRA_INT_ERROR_NO_ERROR;
}

void _ira_identify_prefixes( struct ira_diss_context *context ) {
    struct ira_memory_stream *stream = context->stream;
    int result = 0;
    enum ira_prefix_types prefix_type;
    int prefix_index = 0;
    uint8_t mandatory_prefix;
    do {
        prefix_type = 0;
        mandatory_prefix = 0;
        uint8_t prefix = _ira_stream_peek(stream, &result);
        if( result ) {
            struct ira_instruction_prefix *prefix_desc = &(context->decoding_context.prefixes[prefix_index]);
            switch(prefix) {
                case 0xF0:
                    prefix_type = IRA_GROUP_1;
                    break;
                case 0xF2:
                case 0xF3:
                    mandatory_prefix = 1;
                    prefix_type = IRA_GROUP_1;
                    break;
                case 0x2E:
                case 0x36:
                case 0x3E:
                case 0x26:
                case 0x64:
                case 0x65:
                    prefix_type = IRA_GROUP_2;
                    break;
                break;
                case 0x66:
                    mandatory_prefix = 1;
                    prefix_type = IRA_GROUP_3;
                    break;
                case 0x67:
                    prefix_type = IRA_GROUP_4;
                    break;
                default:
                    if( context->mode == IRA_MOD_64BIT && prefix >= 0x40 && prefix <= 0x4F ) {
                        // REX prefix found.
                        prefix_type = IRA_REX;
                    }
                break;
            }
            if(prefix_type) {
                prefix_desc->prefix = prefix;
                prefix_desc->prefix_type = prefix_type;
                prefix_desc->mandatory_prefix = mandatory_prefix;
                _ira_stream_seek(stream, 1, IRA_CURRENT);
                prefix_index++;
            }
        }
    } while(prefix_type);

    context->decoding_context.instruction_prefix_count = prefix_index;

    // Check if prefixes marked as mandatory are really a mandatory ones.
    if(prefix_index > 0) {
        int found_plain_prefix = 0;
        int i;
        for( i = prefix_index; i > 0; i-- ) {
             if( found_plain_prefix ) {
                 context->decoding_context.prefixes[i - 1].mandatory_prefix = 0;
             } else {
                 // REX prefixes have to be preceded by mandatory prefixes if there are any.
                 struct ira_instruction_prefix *prefix = &(context->decoding_context.prefixes[i - 1]);
                 if( !prefix->mandatory_prefix && prefix->prefix_type != IRA_REX ) {
                     found_plain_prefix = 1;
                 }
             }
        }
    }

}

int _ira_disassemble_default( struct ira_diss_context *context, struct ira_disassemble_result *result ) {
	return _IRA_INT_ERROR_CODE_UNEXPECTED_EOS;
}

void _ira_prepare_disassemble_info(struct ira_disassemble_info *info, struct ira_disassemble_result *result) {

    /* Mode has to be set. */
    if( info->mode != IRA_MOD_16BIT && info->mode != IRA_MOD_32BIT && info->mode != IRA_MOD_64BIT ) {
        result->code = RC_ERROR_ILLEGAL_OPERATION_MODE;
        return;
    }
    /* 16 bit address size attribute is not supported in 64bit mode. */
    if( info->mode == IRA_MOD_64BIT && info->address_size_attribute == _IRA_ASA_16 ) {
        result->code = RC_ERROR_ILLEGAL_ADDRESS_SIZE_ATTRIBUTE;
        return;
    }
    /* Check if attributes are valid and set them to default values. */
    if( info->address_size_attribute == 0 ) {
        switch(info->mode) {
            case IRA_MOD_16BIT:
                info->address_size_attribute = _IRA_ASA_16;
                break;
            case IRA_MOD_32BIT:
            	info->address_size_attribute = _IRA_ASA_32;
            	break;
            case IRA_MOD_64BIT:
                info->address_size_attribute = _IRA_ASA_64;
                break;

        }
    }
    if( info->operand_size_attribute == 0 ) {
        switch(info->mode) {
            case IRA_MOD_16BIT:
                info->operand_size_attribute = _IRA_OSA_16;
                break;
            case IRA_MOD_32BIT:
                info->operand_size_attribute = _IRA_OSA_32;
                break;
            case IRA_MOD_64BIT:
                info->operand_size_attribute = _IRA_OSA_32;
                break;
        }
    }

    result->code = RC_OK;

    // Check if address size attribute is correct.
    switch( info->address_size_attribute ) {
    case _IRA_ASA_16:
    case _IRA_ASA_32:
    case _IRA_ASA_64:
    	break;
    default:
    	result->code = RC_ERROR_ILLEGAL_ADDRESS_SIZE_ATTRIBUTE;
    }

    // Check if operand size attribute is correct.
    switch( info->operand_size_attribute ) {
	case _IRA_OSA_16:
	case _IRA_OSA_32:
	case _IRA_OSA_64:
		break;
	default:
		result->code = RC_ERROR_ILLEGAL_OPERAND_SIZE_ATTRIBUTE;
	}
}

/* Initialization. */

void _ira_free_disassemblation_tree( struct ira_diss_tree_opcode** disassemblation_tree ) {

	int i = 0;
	for( i = 0; i < _IRA_OPCODE_TABLE_SIZE; i++ ) {
		struct ira_diss_tree_opcode *diss_tree_opcode = disassemblation_tree[i];
		if( diss_tree_opcode != NULL ) {
			struct ira_diss_tree_instruction_decoding *inst_decoding = diss_tree_opcode->instructions;
			while( inst_decoding != NULL ) {
				struct ira_diss_tree_instruction_decoding *current_inst_decoding = inst_decoding;
				inst_decoding = inst_decoding->next_instruction_decoding;
				// Free decoding details.
				free( current_inst_decoding );
			}
			_ira_free_disassemblation_tree( diss_tree_opcode->opcodes );
			free( diss_tree_opcode );
		}
	}

}

int _ira_update_disassemblation_tree( struct ira_instruction_desc *instruction_desc_src ) {

	// Get instruction description.
	int instruction_index = 0;
	while( instruction_desc_src[instruction_index].mnemonic != NULL ) {
		struct ira_instruction_desc *instruction_desc = &instruction_desc_src[instruction_index++];

		// Get description of the specific instruction form.
		int opcode_index = 0;
		for( opcode_index = 0; opcode_index < instruction_desc->opcode_desc_count; opcode_index++ ) {
			struct ira_opcode_desc *opcode_desc = &(instruction_desc->opcodes[opcode_index]);
			struct ira_diss_tree_opcode** current_diss_tree_opcode = _ira_disassemblation_tree;
			// Structure where instruction should be placed.
			struct ira_diss_tree_opcode *inst_desc;

			// Looking for structure where instruction should be placed, using instruction opcodes.
			int i;
			int opcode_num = _IRA_OPCODE_FLAGS_OPCODE_NUM( opcode_desc->opcode_flags );
			for( i = 0; i < opcode_num; i++ ) {
				uint8_t opcode = opcode_desc->opcode[i];
				inst_desc = current_diss_tree_opcode[opcode];
				if( inst_desc == NULL ) {
					inst_desc = malloc( sizeof(struct ira_diss_tree_opcode) );
					if( inst_desc == NULL ) {
						// Free disassemblation tree.
						_ira_free_disassemblation_tree( _ira_disassemblation_tree );
						// Return error.
						return _IRA_INT_ERROR_OUT_OF_MEMORY;
					}
					memset( inst_desc, 0, sizeof( struct ira_diss_tree_opcode ) );
					current_diss_tree_opcode[opcode] = inst_desc;
				}
				// Get next level of opcodes for the next loop.
				current_diss_tree_opcode = inst_desc->opcodes;
			}

			// Prepare instruction decoding.
			int error = _ira_add_instruction_decoding( inst_desc, instruction_desc, opcode_desc);
			if( error != _IRA_INT_ERROR_NO_ERROR ) {
				// Free disassemblation tree.
				_ira_free_disassemblation_tree( _ira_disassemblation_tree );
				// Return error.
				return error;
			}
		}
	}

	return _IRA_INT_ERROR_NO_ERROR;
}

int _ira_add_instruction_decoding( struct ira_diss_tree_opcode *inst_desc, struct ira_instruction_desc *instruction_desc, struct ira_opcode_desc *opcode_desc ) {

	// Prepare instruction decoding structure.
	struct ira_diss_tree_instruction_decoding* decoding = malloc( sizeof( struct ira_diss_tree_instruction_decoding ) );
	if( decoding == NULL ) {
		return _IRA_INT_ERROR_OUT_OF_MEMORY;
	}

	// Copy opcodes.
	int i;
	for( i = 0; i < 3; i++ ) {
		decoding->opcodes[i] = opcode_desc->opcode[i];
	}

	// Choose instruction mnemonic.
	decoding->mnemonic = instruction_desc->mnemonic;
	if( opcode_desc->mnemonic_override != NULL ) {
		decoding->mnemonic = opcode_desc->mnemonic_override ;
	}

	// Copy flags.
	decoding->allowed_prefixes = opcode_desc->allowed_prefixes;
	decoding->opcode_flags = opcode_desc->opcode_flags;

	// Choose function used to disassemble instruction.
	decoding->instruction_decoder = _ira_choose_instruction_decoder( instruction_desc->instruction_type );

	// Choose functions used to decode operands.
	_ira_prepare_operand_decoding( &(decoding->operand_decodings[0]), opcode_desc->opperand_1 );
	_ira_prepare_operand_decoding( &(decoding->operand_decodings[1]), opcode_desc->opperand_2 );
	_ira_prepare_operand_decoding( &(decoding->operand_decodings[2]), opcode_desc->opperand_3 );
	_ira_prepare_operand_decoding( &(decoding->operand_decodings[3]), opcode_desc->opperand_4 );

	// Insert it in appropriate order.
	int order = _ira_get_decoding_order( decoding );

	struct ira_diss_tree_instruction_decoding **next_decoding_addr = &(inst_desc->instructions);

	while( *next_decoding_addr != NULL && _ira_get_decoding_order( *next_decoding_addr ) >= order ) {
		next_decoding_addr = &((*next_decoding_addr)->next_instruction_decoding);
	}

	decoding->next_instruction_decoding = *next_decoding_addr;
	*next_decoding_addr = decoding;

	return _IRA_INT_ERROR_NO_ERROR;
}

int _ira_get_decoding_order( struct ira_diss_tree_instruction_decoding* decoding ) {

	uint16_t prefixes = decoding->allowed_prefixes;
	uint32_t opcodes = decoding->opcode_flags;

	int order = 0;

	// Mandatory prefix.
	if( _IRA_PREFIX_MANDATORY_66(prefixes) | _IRA_PREFIX_MANDATORY_F2(prefixes) | _IRA_PREFIX_MANDATORY_F3(prefixes) ) {
		order++;
	}

	// Opcode extension.
	if( _IRA_OPCODE_FLAGS_OPCODE_IS_EXT(opcodes) ) {
		order++;
	}

	// REX prefix.
	// TODO: Remove it when it is really not necessary.
	if( /*_IRA_PREFIX_REX(prefixes) ||*/ _IRA_PREFIX_REX_W_1(prefixes) /* || _IRA_PREFIX_REX_W_0(prefixes)*/ ) {
		order += 2;
	}

	return order;
}

void _ira_prepare_operand_decoding( struct ira_operand_decoding *operand_decoding, uint8_t decoder_type ) {

	// Store access mode for this operand decoding.
	operand_decoding->access_mode = ( decoder_type & _IRA_W ) ? IRA_WRITE : IRA_READ;

	// Clear access mode.
	decoder_type &= ~_IRA_W;

	switch( decoder_type ) {
	case _IRA_OPERAND_REG_ACCUMULATOR_8:
		operand_decoding->decoder = &_ira_opcode_decoder_accumulator;
		operand_decoding->args = IRA_REG_GPR_8;
		break;
	case _IRA_OPERAND_REG_ACCUMULATOR_OSA:
		operand_decoding->decoder = &_ira_opcode_decoder_accumulator;
		operand_decoding->args = IRA_REG_GPR; // EOSA.
		break;
	case _IRA_OPERAND_IB:
		operand_decoding->decoder = &_ira_opcode_decoder_immediate;
		operand_decoding->args = IRA_IMMEDIATE_8;
		break;
	case _IRA_OPERAND_IB_EX_EOSA:
		operand_decoding->decoder = &_ira_opcode_decoder_immediate_extends_eosa;
		operand_decoding->args = IRA_IMMEDIATE_8;
		break;
	case _IRA_OPERAND_IW:
		operand_decoding->decoder = &_ira_opcode_decoder_immediate;
		operand_decoding->args = IRA_IMMEDIATE_16;
		break;
	case _IRA_OPERAND_IW_EX_EOSA:
		operand_decoding->decoder = &_ira_opcode_decoder_immediate_extends_eosa;
		operand_decoding->args = IRA_IMMEDIATE_16;
		break;
	case _IRA_OPERAND_ID:
		operand_decoding->decoder = &_ira_opcode_decoder_immediate;
		operand_decoding->args = IRA_IMMEDIATE_32;
		break;
	case _IRA_OPERAND_ID_EX_EOSA:
		operand_decoding->decoder = &_ira_opcode_decoder_immediate_extends_eosa;
		operand_decoding->args = IRA_IMMEDIATE_32;
		break;
	case _IRA_OPERAND_IMM_EOSA:
		operand_decoding->decoder = &_ira_opcode_decoder_immediate;
		operand_decoding->args = 0; // EOSA.
		break;
	case _IRA_OPERAND_IO:
		operand_decoding->decoder = &_ira_opcode_decoder_immediate;
		operand_decoding->args = IRA_IMMEDIATE_64;
		break;
	case _IRA_OPERAND_IO_EOSA:
		operand_decoding->decoder = &_ira_opcode_decoder_immediate_extends_eosa;
		operand_decoding->args = IRA_IMMEDIATE_64;
		break;
	case _IRA_OPERAND_MODRM_RM_8:
		operand_decoding->decoder = &_ira_opcode_decoder_modrm_rm_8;
		break;
	case _IRA_OPERAND_MODRM_R_8:
		operand_decoding->decoder = &_ira_opcode_decoder_modrm_r_8;
		break;
	case _IRA_OPERAND_MODRM_RM_ASA:
		operand_decoding->decoder = &_ira_opcode_decoder_modrm_rm_easa;
		break;
	case _IRA_OPERAND_MODRM_R_OSA:
		operand_decoding->decoder = &_ira_opcode_decoder_modrm_r_eosa;
		break;
	default:
		operand_decoding->decoder = NULL;
		operand_decoding->access_mode = IRA_ACCESS_MODE_UNDEFINED;
		return;
	}
}

ira_instruction_decoder _ira_choose_instruction_decoder( uint8_t instruction_type ) {
	switch( instruction_type ) {
	case _IRA_IT_IA:
		// Currently only IA decoder is supported.
		return &_ira_instruction_decoder_IA;
	}
	return NULL;
}

/* Helpers for disassemblation context. */

uint8_t _ira_diss_context_get_REX_prefix( struct ira_diss_context *context, int *found ) {
	struct ira_decoding_context *decoding_context = &(context->decoding_context);
	int prefix_count = decoding_context->instruction_prefix_count;
	*found = 0;
	int i;
	uint8_t rex = 0;
	for( i = 0; i < prefix_count; i++ ) {
		if( decoding_context->prefixes[i].prefix_type == IRA_REX ) {
			*found = 1;
			rex = decoding_context->prefixes[i].prefix;
			break;
		}
	}
	return rex;
}

struct ira_instruction_prefix* _ira_diss_context_get_prefix_if_available( struct ira_diss_context *context, uint8_t prefix_value ) {
	struct ira_instruction_prefix* prefix = NULL;
	struct ira_decoding_context *decoding_context = &(context->decoding_context);
	int prefix_count = decoding_context->instruction_prefix_count;
	int i;
	for( i = 0; i < prefix_count; i++ ) {
		if( decoding_context->prefixes[i].prefix == prefix_value ) {
			prefix = &(decoding_context->prefixes[i]);
			break;
		}
	}
	return prefix;
}

int _ira_diss_context_is_prefix_available( struct ira_diss_context *context, uint8_t prefix ) {
	return _ira_diss_context_get_prefix_if_available( context, prefix ) != NULL;
}

/* Streaming. */

void _ira_stream_seek( struct ira_memory_stream *stream, uint32_t offset, enum ira_seek_type type ) {
    switch(type) {
        case IRA_START:
            stream->offset = offset;
        break;
        case IRA_CURRENT:
            stream->offset += offset;
        break;
        case IRA_END:
            stream->offset = (stream->size - offset);
        break;
    }
}

uint8_t _ira_stream_read( struct ira_memory_stream *stream, int *result ) {
    uint8_t *base_address = (uint8_t *)stream->base_address;
    *result = ( stream->offset == stream->size ) ? 0 : 1;
    if( *result )
        return base_address[stream->offset++];
    return 0;
}

uint8_t _ira_stream_peek( struct ira_memory_stream *stream, int *result ) {
    uint8_t *base_address = (uint8_t *)stream->base_address;
    *result = ( stream->offset == stream->size ) ? 0 : 1;
    if( *result )
        return base_address[stream->offset];
    return 0;
}

uint32_t _ira_stream_size( struct ira_memory_stream *stream ) {
	return stream->size - stream->offset;
}

int _ira_stream_read_bytes( struct ira_memory_stream *stream, void *buffer , int size) {
	if( size == 0 ) {
		return 0;
	}
	uint8_t *destination_buffer = (uint8_t*)buffer;
	int i = 0;
	while( stream->offset < stream->size && i < size ) {
		destination_buffer[i++] = ((uint8_t*)stream->base_address)[stream->offset++];
	}
	return i;
}

uint16_t _ira_stream_read_word( struct ira_memory_stream *stream, int *result ) {
	uint16_t value = 0;
	*result = stream->size - stream->offset >= sizeof(uint16_t);
	if( *result ) {
		value = (((uint16_t*)((uint8_t*)stream->base_address + stream->offset))[0]);
		stream->offset += sizeof(uint16_t);
	}
	return value;
}

uint32_t _ira_stream_read_dword( struct ira_memory_stream *stream, int *result ) {
	uint32_t value = 0;
	*result = stream->size - stream->offset >= sizeof(uint32_t);
	if( *result ) {
		value = (((uint32_t*)((uint8_t*)stream->base_address + stream->offset))[0]);
		stream->offset += sizeof(uint32_t);
	}
	return value;
}

/* Instruction decoders. */

int _ira_instruction_decoder_IA( struct ira_diss_context *context, struct ira_diss_tree_instruction_decoding *instruction, struct ira_disassemble_result *result ) {

	int i, rc;

	// Set mnemonic of disassembled instruction.
	result->mnemonic = instruction->mnemonic;

	// Copy prefixes.
	result->prefixes_count = context->decoding_context.instruction_prefix_count;

	for( i = 0; i < result->prefixes_count && i < _IRA_PREFIXES_COUNT; i++ ) {
		struct ira_instruction_prefix *prefix = &context->decoding_context.prefixes[i];
		// Check if 66 prefix is mandatory one. It has to be done here because prefix 66 is always
		// treated as mandatory one in first phase.
		if( prefix->prefix == 0x66 && !_IRA_PREFIX_MANDATORY_66( instruction->allowed_prefixes ) ) {
			prefix->mandatory_prefix = 0;
		}
		result->prefixes[i] = context->decoding_context.prefixes[i];
	}

	// Copy opcodes.
	result->opcodes_count = _IRA_OPCODE_FLAGS_OPCODE_NUM( instruction->opcode_flags );

	for( i = 0; i < sizeof( instruction->opcodes ) ; i++ ) {
		result->opcodes[i] = instruction->opcodes[i];
	}

	// Calculates effective operand sizes. It's not important if they will be used or not.
	struct ira_decoding_context *decoding_context = &(context->decoding_context);
	decoding_context->effective_address_size_attribute = _ira_get_effective_asa( context );
	decoding_context->effective_operand_size_attribute = _ira_get_effective_osa( context );

	// Decode operands, one by one.
	for( i = 0; i < _IRA_OPERANDS_COUNT; i++ ) {
		struct ira_operand_decoding *decoding = &instruction->operand_decodings[i];
		ira_operand_decoder decoder = decoding->decoder;
		if( decoder != NULL ) {
			rc = decoder( context, &(result->operands[i]), decoding->args );
			if( rc != _IRA_INT_ERROR_NO_ERROR ) {
				return rc;
			}
			// Copy access mode to decoded operand.
			result->operands[i].access_mode = instruction->operand_decodings[i].access_mode;
		} else {
			struct ira_instruction_operand *operand = &(result->operands[i]);
			memset( operand, 0, sizeof( struct ira_instruction_operand ) );
			operand->operand_type = IRA_NONE;
		}
	}

	// Store REX in result if exists.
	result->rex = context->decoding_context.mod_rm.raw_rex;

	result->code = RC_OK;

	return _IRA_INT_ERROR_NO_ERROR;
}

/* Operand decoders. */

void _ira_opcode_decoder_reg( struct ira_instruction_operand *operand, enum ira_register_type reg_type, int reg ) {
	operand->operand_type = IRA_REGISTER;
	operand->reg.reg_type = reg_type;
	operand->reg.reg = reg;
}

/* Decodes accumulator register. */
int _ira_opcode_decoder_accumulator( struct ira_diss_context *context, struct ira_instruction_operand *operand, int args ) {
	enum ira_register_type reg_type = args;
	if( args == IRA_REG_GPR ) {
		// A general purpose register, we should calculate it's size basing on EOSA.
		reg_type = _ira_map_osa_to_register_type( context );
	}
	_ira_opcode_decoder_reg( operand, reg_type, _IRA_REG_AL );
	return _IRA_INT_ERROR_NO_ERROR;
}

/* Decodes immediate value and extends it to the effective operand size. */
int _ira_opcode_decoder_immediate_extends_eosa( struct ira_diss_context *context, struct ira_instruction_operand *operand, int args ) {
	int result = _ira_opcode_decoder_immediate( context, operand, args );
	if( result != _IRA_INT_ERROR_NO_ERROR ) {
		return result;
	}
	// Set extension size.
	operand->immediate.extension_size = context->decoding_context.effective_operand_size_attribute;
	return result;
}

int _ira_opcode_decoder_immediate( struct ira_diss_context *context, struct ira_instruction_operand *operand, int args ) {
	int size = args;
	if( size == 0 ) {
		// If size is not specified use EOSA.
		size = context->decoding_context.effective_operand_size_attribute;
	}
	int result = _ira_decode_immediate( context, &(operand->immediate), size );
	if( result != _IRA_INT_ERROR_NO_ERROR ) {
		return result;
	}
	operand->operand_type = IRA_IMMEDIATE_DATA;
	operand->immediate.extension_size = 0;
	return _IRA_INT_ERROR_NO_ERROR;
}

// TODO: Change this model, see there instruction pairs are identical!

int _ira_opcode_decoder_modrm_rm_8( struct ira_diss_context *context, struct ira_instruction_operand *operand, int args ) {
	return _ira_opcode_decoder_modrm_rm( context, operand, IRA_REG_GPR, _IRA_OR_8 );
}

int _ira_opcode_decoder_modrm_r_8( struct ira_diss_context *context, struct ira_instruction_operand *operand, int args ) {
	return _ira_opcode_decoder_modrm_r( context, operand, IRA_REG_GPR, _IRA_OR_8 );
}

int _ira_opcode_decoder_modrm_rm_easa( struct ira_diss_context *context, struct ira_instruction_operand *operand, int args ) {
	return _ira_opcode_decoder_modrm_rm( context, operand, IRA_REG_GPR, _IRA_OR_DEFAULT );
}

int _ira_opcode_decoder_modrm_r_eosa( struct ira_diss_context *context, struct ira_instruction_operand *operand, int args ) {
	return _ira_opcode_decoder_modrm_r( context, operand, IRA_REG_GPR, _IRA_OR_DEFAULT );
}

//! Generic ModR/M addressing mode decoder.
/*!
 * \brief Generic ModR/M addressing mode decoder. This is a generic decoder that should be only used in functions
 * that are prepared to decode specific addressing modes.
 *
 * \param context Disassembling context.
 * \param operand Destination operand.
 * \param reg_type Register type used if "Mod" field of ModR/M is 3.
 * \param operand_register_size Register size used if "Mod" field of ModR/M is 3.
 * \return Error code.
 */
int _ira_opcode_decoder_modrm_rm( struct ira_diss_context *context, struct ira_instruction_operand *operand, enum ira_register_type reg_type, int operand_register_size ) {

	// Decode ModR/M.
	int result = _ira_modrm_decoder( context, reg_type, operand_register_size, _IRA_MOD_RM_FLAGS_DECODE_ADDRESSING );
	if( result != _IRA_INT_ERROR_NO_ERROR ) {
		return result;
	}

	// Prepare operand using decoded ModRM.
	result = _ira_modrm_decoder_operand_fill_address( context, operand );
	if( result != _IRA_INT_ERROR_NO_ERROR ) {
		return result;
	}

	return _IRA_INT_ERROR_NO_ERROR;
}

int _ira_opcode_decoder_modrm_r( struct ira_diss_context *context, struct ira_instruction_operand *operand, enum ira_register_type reg_type, int operand_register_size ) {

	// Decode ModR/M.
	int result = _ira_modrm_decoder( context, reg_type, operand_register_size, _IRA_MOD_RM_FLAGS_DECODE_REG );
	if( result != _IRA_INT_ERROR_NO_ERROR ) {
		return result;
	}

	// Prepare operand using decoded ModRM.
	result = _ira_modrm_decoder_operand_fill_register( context, operand );
	if( result != _IRA_INT_ERROR_NO_ERROR ) {
		return result;
	}

	return _IRA_INT_ERROR_NO_ERROR;
}

/* ModRM decoding. */

int _ira_modrm_decoder_operand_fill_register( struct ira_diss_context *context, struct ira_instruction_operand *operand ) {
	int result = _IRA_INT_ERROR_ILLEGAL_ARGUMENT;
	struct ira_decoded_mod_rm *decoded_mod_rm = &(context->decoding_context.mod_rm);
	if( decoded_mod_rm->decoded_reg ) {
		operand->operand_type = IRA_REGISTER;
		operand->reg = decoded_mod_rm->operand_reg;
		result = _IRA_INT_ERROR_NO_ERROR;
	}
	return result;
}

int _ira_modrm_decoder_operand_fill_address( struct ira_diss_context *context, struct ira_instruction_operand *operand ) {
	// IAE because we shouldn't call this method if ModRM hasn't been decoded.
	int result = _IRA_INT_ERROR_ILLEGAL_ARGUMENT;
	struct ira_decoded_mod_rm *decoded_mod_rm = &(context->decoding_context.mod_rm);
	if( decoded_mod_rm->decoded_addressing ) {

		// Check if there is register or memory address encoded in ModR/M.
		if( decoded_mod_rm->reg.reg_type != IRA_NO_REG ) {
			// There is just plain register (mod = 3).
			_ira_opcode_decoder_reg( operand, decoded_mod_rm->reg.reg_type, decoded_mod_rm->reg.reg );
		} else {
			operand->operand_type = IRA_ADDRESS;
			operand->addressing.addressing_type = IRA_MOD_RM;
			struct ira_mod_rm_addressing *mod_rm = &(operand->addressing.mod_rm);
			// Copy all needed fields.
			mod_rm->raw_mod_rm = decoded_mod_rm->raw_mod_rm;
			mod_rm->raw_sib = decoded_mod_rm->raw_sib;
			mod_rm->raw_rex = decoded_mod_rm->raw_rex;
			mod_rm->base_reg = decoded_mod_rm->base_reg;
			mod_rm->index_reg = decoded_mod_rm->index_reg;
			mod_rm->scale = decoded_mod_rm->scale;
			mod_rm->displacement = decoded_mod_rm->displacement;
		}

		result = _IRA_INT_ERROR_NO_ERROR;
	}
	return result;
}

int _ira_modrm_decoder_get_modrm( struct ira_diss_context *context, struct ira_decoded_mod_rm *decoded_mod_rm ) {
	// Get ModRM byte if it has not been got yet.
	if( !decoded_mod_rm->raw_mod_rm.is_not_null ) {
		int result;
		uint8_t mod_rm = _ira_stream_read( context->stream, &result );
		if( result ) {
			decoded_mod_rm->raw_mod_rm.value = mod_rm;
			decoded_mod_rm->raw_mod_rm.is_not_null = _IRA_TRUE;
		} else {
			return _IRA_INT_ERROR_CODE_UNEXPECTED_EOS;
		}
	}
	return _IRA_INT_ERROR_NO_ERROR;
}


int _ira_modrm_decoder_get_rex( struct ira_diss_context *context, struct ira_decoded_mod_rm *decoded_mod_rm ) {
	int rex_found = decoded_mod_rm->raw_rex.is_not_null;
	// Check if there is REX register.
	if( context->mode == IRA_MOD_64BIT && !rex_found ) {
		uint8_t rex = _ira_diss_context_get_REX_prefix( context, &rex_found );
		if( rex_found ) {
			// Store its value in decoded ModRM structure.
			decoded_mod_rm->raw_rex.value = rex;
			decoded_mod_rm->raw_rex.is_not_null = _IRA_TRUE;
		}
	}
	return rex_found;
}

struct ira_register _ira_modrm_decode_register( struct ira_diss_context *context, enum ira_register_type reg_type, int operand_register_size, int reg ) {
	int type = reg_type;
	if( reg_type == IRA_REG_GPR && operand_register_size == _IRA_OR_8 ) {
		type = IRA_REG_GPR_8;
	} else if( reg_type == IRA_REG_GPR ) {
		switch( context->decoding_context.effective_operand_size_attribute ) {
		case _IRA_OSA_16:
			type = IRA_REG_GPR_16;
			break;
		case _IRA_OSA_32:
			type = IRA_REG_GPR_32;
			break;
		case _IRA_OSA_64:
			type = IRA_REG_GPR_64;
			break;
		}
	}
	struct ira_register result_reg = {0};

	// There are no MMX registers for reg > 7.
	if( !( reg_type == IRA_REG_MMX && reg > 7 ) ) {
		result_reg.reg = reg;
		result_reg.reg_type = type;
	}

	return result_reg;
}

int _ira_modrm_addressing_decoder_16_bit( struct ira_diss_context *context, enum ira_register_type reg_type, int operand_register_size, uint8_t flags ) {

	int result = _IRA_INT_ERROR_NO_ERROR;

	// ModR/M.
	uint8_t mod, rm;

	struct ira_decoding_context *decoding_context = &(context->decoding_context);
	struct ira_decoded_mod_rm *decoded_mod_rm = &(decoding_context->mod_rm);

	// Get raw ModR/M byte to decode it.
	uint8_t mod_rm = context->decoding_context.mod_rm.raw_mod_rm.value;

	// Decode ModRM.
	mod = _IRA_MODRM_MOD(mod_rm);
	rm = _IRA_MODRM_RM(mod_rm);

	if( mod == 0 && rm == 6 ) {
		// disp16.
		result = _ira_decode_displacement( context, &(decoded_mod_rm->displacement), IRA_DISPLACEMENT_16, IRA_DISPLACEMENT_EXT_SIZE_16 );
	} else if( mod < 3 ) {
		decoded_mod_rm->base_reg = _ira_addressing_form_reg_array_16[rm][0];
		decoded_mod_rm->index_reg = _ira_addressing_form_reg_array_16[rm][1];
		if( mod > 0 ) {
			result = _ira_decode_displacement( context, &(decoded_mod_rm->displacement), ( mod == 1 ) ? IRA_DISPLACEMENT_8 : IRA_DISPLACEMENT_16, IRA_DISPLACEMENT_EXT_SIZE_16 );
		}
	} else {
		// Straight copy of registers.
		decoded_mod_rm->reg = _ira_modrm_decode_register( context, reg_type, operand_register_size, rm );
	}

	// Decode register if something needs it.
	if ( flags & _IRA_MOD_RM_FLAGS_DECODE_REG ) {
		decoded_mod_rm->operand_reg = _ira_modrm_decode_register( context, reg_type, operand_register_size, _IRA_MODRM_REG_OPCODE(mod_rm) );
		decoded_mod_rm->decoded_reg = _IRA_TRUE;
	}

	return result;
}

int _ira_modrm_addressing_decoder_sib( struct ira_diss_context *context, enum ira_register_type reg_type, int operand_size ) {

	uint8_t scale, index, base;

	int result = _IRA_INT_ERROR_NO_ERROR;

	// ModR/M.
	uint8_t mod;

	struct ira_decoding_context *decoding_context = &(context->decoding_context);
	struct ira_decoded_mod_rm *decoded_mod_rm = &(decoding_context->mod_rm);

	// Get raw ModR/M and SIB bytes to decode them.
	uint8_t mod_rm = context->decoding_context.mod_rm.raw_mod_rm.value;

	// Get SIB.
	uint8_t sib = _ira_stream_read( context->stream, &result );
	if( result ) {
		decoded_mod_rm->raw_sib.value = sib;
		decoded_mod_rm->raw_sib.is_not_null = _IRA_TRUE;
	} else {
		return _IRA_INT_ERROR_CODE_UNEXPECTED_EOS;
	}

	base = _IRA_SIB_BASE(sib);
	index = _IRA_SIB_INDEX(sib);
	scale = _IRA_SIB_SS(sib);

	if( context->mode == IRA_MOD_64BIT && decoded_mod_rm->raw_rex.is_not_null ) {
		uint8_t rex = decoded_mod_rm->raw_rex.value;
		base |= ( _IRA_REX_B(rex) << 3 );
		index |= ( _IRA_REX_X(rex) << 3 );
	}

	// Decode ModRM.
	mod = _IRA_MODRM_MOD(mod_rm);

	// Index register and scale.
	if( index != 4 ) {
		// Effective address size affects index register.
		uint8_t effective_address_size = decoding_context->effective_address_size_attribute;
		decoded_mod_rm->index_reg.reg_type = (effective_address_size == _IRA_ASA_64) ? IRA_REG_GPR_64 : IRA_REG_GPR_32;
		decoded_mod_rm->index_reg.reg = index;
		// Scale.
		decoded_mod_rm->scale.value = scale ? 1 << scale : 0; // scale * 2
		decoded_mod_rm->scale.is_not_null = _IRA_TRUE;
	}

	// Base register and displacement.
	if( mod == 0 && _IRA_SIB_BASE(sib) == 5 ) {
		// In this case base register doesn't exist.
		result = _ira_decode_displacement( context, &(decoded_mod_rm->displacement), IRA_DISPLACEMENT_32,
						( context->mode == IRA_MOD_64BIT ) ? IRA_DISPLACEMENT_EXT_SIZE_64 : IRA_DISPLACEMENT_EXT_SIZE_32 );
	} else {
		// Effective address size affects base register.
		uint8_t effective_address_size = decoding_context->effective_address_size_attribute;
		decoded_mod_rm->base_reg.reg_type = (effective_address_size == _IRA_ASA_64) ? IRA_REG_GPR_64 : IRA_REG_GPR_32;
		decoded_mod_rm->base_reg.reg = base;

		// Displacement.
		result = _ira_decode_displacement( context, &(decoded_mod_rm->displacement), ( mod == 1 ) ? IRA_DISPLACEMENT_8 : IRA_DISPLACEMENT_32,
						( context->mode == IRA_MOD_64BIT ) ? IRA_DISPLACEMENT_EXT_SIZE_64 : IRA_DISPLACEMENT_EXT_SIZE_32 );
	}

	return _IRA_INT_ERROR_NO_ERROR;
}

int _ira_modrm_addressing_decoder_32_64_bit( struct ira_diss_context *context, enum ira_register_type reg_type, int operand_register_size, uint8_t flags ) {

	int result = _IRA_INT_ERROR_NO_ERROR;

	// ModR/M.
	uint8_t mod, rm;

	struct ira_decoding_context *decoding_context = &(context->decoding_context);
	struct ira_decoded_mod_rm *decoded_mod_rm = &(decoding_context->mod_rm);

	// Get raw ModR/M byte to decode it.
	uint8_t mod_rm = context->decoding_context.mod_rm.raw_mod_rm.value;

	// Decode ModRM.
	mod = _IRA_MODRM_MOD(mod_rm);
	rm = _IRA_MODRM_RM(mod_rm);

	uint8_t rex;

	// Check if there is REX register and get it.
	if( _ira_modrm_decoder_get_rex(context, decoded_mod_rm) ) {
		rex = decoded_mod_rm->raw_rex.value;
		rm |= ( _IRA_REX_B(rex) << 3 );
	}

	if( mod == 3 ) {
		// Registers.
		decoded_mod_rm->reg = _ira_modrm_decode_register( context, reg_type, operand_register_size, rm );
	} else if( _IRA_MODRM_RM(mod_rm) == 4 ) {
		// Decode SIB addressing format.
		result = _ira_modrm_addressing_decoder_sib( context, reg_type, operand_register_size );
	} else if( mod == 0 && _IRA_MODRM_RM(mod_rm) == 5 ) {
		// disp32.
		result = _ira_decode_displacement( context, &(decoded_mod_rm->displacement), IRA_DISPLACEMENT_32,
				( context->mode == IRA_MOD_64BIT ) ? IRA_DISPLACEMENT_EXT_SIZE_64 : IRA_DISPLACEMENT_EXT_SIZE_32 );
	} else {
		// Base register.
		uint8_t effective_address_size = decoding_context->effective_address_size_attribute;
		decoded_mod_rm->base_reg.reg_type = (effective_address_size == _IRA_ASA_64) ? IRA_REG_GPR_64 : IRA_REG_GPR_32;
		decoded_mod_rm->base_reg.reg = rm;
		// Displacement.
		if( mod != 0 ) {
			result = _ira_decode_displacement( context, &(decoded_mod_rm->displacement), ( mod == 1 ) ? IRA_DISPLACEMENT_8 : IRA_DISPLACEMENT_32,
					( context->mode == IRA_MOD_64BIT ) ? IRA_DISPLACEMENT_EXT_SIZE_64 : IRA_DISPLACEMENT_EXT_SIZE_32 );
		}
	}

	// Decodes register if something needs it.
	if ( flags & _IRA_MOD_RM_FLAGS_DECODE_REG ) {
		uint8_t reg = _IRA_MODRM_REG_OPCODE(mod_rm);
		if( decoded_mod_rm->raw_rex.is_not_null ) {
			reg |= ( _IRA_REX_R(rex) << 3 );
		}
		decoded_mod_rm->operand_reg = _ira_modrm_decode_register( context, reg_type, operand_register_size, reg );
		decoded_mod_rm->decoded_reg = _IRA_TRUE;
	}

	return result;
}

int _ira_modrm_decoder( struct ira_diss_context *context, enum ira_register_type reg_type, int operand_register_size, uint8_t flags ) {

	int result;

	struct ira_decoding_context *decoding_context = &(context->decoding_context);
	struct ira_decoded_mod_rm *decoded_mod_rm = &(decoding_context->mod_rm);

	if( flags & _IRA_MOD_RM_FLAGS_DECODE_ADDRESSING ) {

		// Decodes addressing mode and optionally register.
		// Check if ModRM addressing has already been decoded.
		if( !decoded_mod_rm->decoded_addressing ) {

			// Get ModRM byte.
			result = _ira_modrm_decoder_get_modrm( context, decoded_mod_rm );
			if( result != _IRA_INT_ERROR_NO_ERROR ) {
				return result;
			}

			uint8_t effective_asa = decoding_context->effective_address_size_attribute;

			if( effective_asa == _IRA_ASA_16 ) {
				result = _ira_modrm_addressing_decoder_16_bit(context, reg_type, operand_register_size, flags);
			} else {
				result = _ira_modrm_addressing_decoder_32_64_bit(context, reg_type, operand_register_size, flags);
			}

			if( result != _IRA_INT_ERROR_NO_ERROR ) {
				return result;
			}

			decoded_mod_rm->decoded_addressing = _IRA_TRUE;
		}

	}

	if ( flags & _IRA_MOD_RM_FLAGS_DECODE_REG ) {

		// Decodes only register ignoring addressing mode. There are commands that
		// do not need addressing form decoded. In such cases we only perform register
		// decoding.
		if( !decoded_mod_rm->decoded_reg ) {

			// Get ModRM byte.
			result = _ira_modrm_decoder_get_modrm( context, decoded_mod_rm );
			if( result != _IRA_INT_ERROR_NO_ERROR ) {
				return result;
			}

			uint8_t reg = _IRA_MODRM_REG_OPCODE(decoded_mod_rm->raw_mod_rm.value);

			// Check if there is REX prefix that can extend register and get it.
			if( _ira_modrm_decoder_get_rex( context, decoded_mod_rm ) ) {
				reg |= ( _IRA_REX_R(decoded_mod_rm->raw_rex.value) << 3 );
			}

			decoded_mod_rm->operand_reg = _ira_modrm_decode_register( context, reg_type, operand_register_size, reg );

			decoded_mod_rm->decoded_reg = _IRA_TRUE;
		}
	}

	return _IRA_INT_ERROR_NO_ERROR;
}

/* Helpers used to decode operands. */

int _ira_get_effective_asa( struct ira_diss_context *context ) {

	uint16_t effective_asa = context->address_size_attribute;

	// Checks if address size attribute is overridden.
	if( _ira_diss_context_is_prefix_available(context, 0x67) ) {
		switch( context->mode ) {
		case IRA_MOD_16BIT:
		case IRA_MOD_32BIT:
			effective_asa = ( effective_asa == _IRA_ASA_32 ) ? _IRA_ASA_16 : _IRA_ASA_32;
			break;
		case IRA_MOD_64BIT:
			effective_asa = ( effective_asa == _IRA_ASA_32 ) ? _IRA_ASA_64 : _IRA_ASA_32;
			break;
		}
	}

	return effective_asa;
}

int _ira_get_effective_osa( struct ira_diss_context *context ) {

	struct ira_instruction_prefix *prefix;
	int rex_w = 0, result;
	uint8_t rex;

	uint16_t effective_osa = context->operand_size_attribute;

	// Gets effective address-size attribute for used mode.
	switch( context->mode ) {
	case IRA_MOD_16BIT:
	case IRA_MOD_32BIT:
		// In 16 and 32 bit mode only prefixes can change address-size attribute.
		prefix = _ira_diss_context_get_prefix_if_available( context, 0x66 );
		if( prefix != NULL && !prefix->mandatory_prefix ) {
			effective_osa = ( effective_osa == _IRA_OSA_16 ) ? _IRA_OSA_32 : _IRA_OSA_16;
		}
		break;
	case IRA_MOD_64BIT:
		// 0 = Operand Size determined by CS.D, 1 = 64 Bit Operand Size.
		rex = _ira_diss_context_get_REX_prefix( context, &result );
		if( result ) {
			// REX prefix is available, so get W bit.
			rex_w = _IRA_REX_W( rex );
		}
		if( rex_w ) {
			// Prefixes can not override REX.W.
			effective_osa = _IRA_OSA_64;
		} else {
			prefix = _ira_diss_context_get_prefix_if_available( context, 0x66 );
			if( prefix != NULL && !prefix->mandatory_prefix ) {
				effective_osa = ( effective_osa == _IRA_OSA_16 ) ? _IRA_OSA_32 : _IRA_OSA_16;
			}
		}
		break;
	}

	return effective_osa;
}

int _ira_decode_displacement( struct ira_diss_context *context, struct ira_displacement *displacement, int size, int extension_size ) {
	int result = 0;
	switch(size) {
	case 8:
		displacement->displacement.displacement_8 = _ira_stream_read( context->stream, &result );
		if( !result ) {
			return _IRA_INT_ERROR_CODE_UNEXPECTED_EOS;
		}
		displacement->displacement_type = IRA_DISPLACEMENT_8;
		break;
	case 16:
		displacement->displacement.displacement_16 = _ira_stream_read_word( context->stream, &result );
		if( !result ) {
			return _IRA_INT_ERROR_CODE_UNEXPECTED_EOS;
		}
		displacement->displacement_type = IRA_DISPLACEMENT_16;
		break;
	case 32:
		displacement->displacement.displacement_32 = _ira_stream_read_dword( context->stream, &result );
		if( !result ) {
			return _IRA_INT_ERROR_CODE_UNEXPECTED_EOS;
		}
		displacement->displacement_type = IRA_DISPLACEMENT_32;
		break;
	default:
		return _IRA_INT_ERROR_ILLEGAL_ARGUMENT;
	}
	displacement->extension_size = extension_size;
	return _IRA_INT_ERROR_NO_ERROR;
}

int _ira_decode_immediate( struct ira_diss_context *context, struct ira_immediate_data *data, int size ) {
	int result = 0;
	switch(size) {
	case 8:
		data->immediate_data.immediate_8 =_ira_stream_read( context->stream, &result );
		if( !result ) {
			return _IRA_INT_ERROR_CODE_UNEXPECTED_EOS;
		}
		break;
	case 16:
		if( _ira_stream_read_bytes( context->stream, &(data->immediate_data.immediate_16), sizeof(uint16_t) ) < sizeof(uint16_t) ) {
			return _IRA_INT_ERROR_CODE_UNEXPECTED_EOS;
		}
		break;
	case 32:
		if( _ira_stream_read_bytes( context->stream, &(data->immediate_data.immediate_32), sizeof(uint32_t) ) < sizeof(uint32_t) ) {
			return _IRA_INT_ERROR_CODE_UNEXPECTED_EOS;
		}
		break;
	case 64:
		if( _ira_stream_read_bytes( context->stream, &(data->immediate_data.immediate_64), sizeof(uint64_t) ) < sizeof(uint64_t) ) {
			return _IRA_INT_ERROR_CODE_UNEXPECTED_EOS;
		}
		break;
	default:
		return _IRA_INT_ERROR_ILLEGAL_ARGUMENT;
	}
	data->immediate_data_type = size;
	return _IRA_INT_ERROR_NO_ERROR;
}

enum ira_register_type _ira_map_osa_to_register_type( struct ira_diss_context *context ) {
	enum ira_register_type reg_type = IRA_REG_GPR;
	switch( context->decoding_context.effective_operand_size_attribute ) {
	case _IRA_OSA_16:
		reg_type = IRA_REG_GPR_16;
		break;
	case _IRA_OSA_32:
		reg_type = IRA_REG_GPR_32;
		break;
	case _IRA_OSA_64:
		reg_type = IRA_REG_GPR_64;
		break;
	}
	return reg_type;
}
