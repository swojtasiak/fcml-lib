
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

/* Chooses instruction variant for decoding. */
struct ira_diss_tree_instruction_decoding* _ira_choose_instruction( struct ira_diss_context *context, struct ira_diss_tree_instruction_decoding* instruction );

/* Factory method that returns operand decoder for given type. */
ira_operand_decoder _ira_choose_operand_decoder( uint8_t decoder_type );

/* Factory method that returns operand decoder for given type. */
ira_instruction_decoder _ira_choose_instruction_decoder( uint8_t instruction_type );

/* Returns 1 is there is given prefix found for given instruction. */
int _ira_diss_context_is_prefix_available( struct ira_diss_context *context, uint8_t prefix );

/* Gets REX prefix. */
uint8_t _ira_diss_context_get_REX_prefix( struct ira_diss_context *context, int *found );

/* Instruction decoders. */

void _ira_instruction_decoder_IA( struct ira_diss_context *context, struct ira_diss_tree_instruction_decoding *instruction, struct ira_disassemble_result *result );

/* Opcode decoders. */

struct ira_instruction_operand _ira_opcode_decoder_ib( struct ira_diss_context *context );
struct ira_instruction_operand _ira_opcode_decoder_iw( struct ira_diss_context *context );
struct ira_instruction_operand _ira_opcode_decoder_id( struct ira_diss_context *context );
struct ira_instruction_operand _ira_opcode_decoder_io( struct ira_diss_context *context );

/* Decoders' helpers methods. */

int _ira_decode_immediate( struct ira_diss_context *context, union ira_immediate_data *data, int size );

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

    // Start disassemblation.
    if( instruction != NULL ) {
    	// Choose appropriate instruction variant.
    	instruction = _ira_choose_instruction( &context, instruction );
    	if( instruction != NULL ) {
    		instruction->instruction_decoder( &context, instruction, result );
    	} else {
    		// Instruction is not decodable.
			if( _ira_disassemble_default( &context, result ) == _IRA_INT_ERROR_CODE_UNEXPECTED_EOS ) {
				result->code = RC_ERROR_INSTRUCTION_INCOMPLETE;
				return;
			}
    	}
    } else {
    	// Instruction wasn't found, so restore stream and start default disassemblation process.
    	_ira_stream_seek( context.stream, opcode_length * -1, IRA_CURRENT );
    	if( _ira_disassemble_default( &context, result ) == _IRA_INT_ERROR_CODE_UNEXPECTED_EOS ) {
    		result->code = RC_ERROR_INSTRUCTION_INCOMPLETE;
    		return;
    	}
    }
}

struct ira_diss_tree_instruction_decoding* _ira_choose_instruction( struct ira_diss_context *context, struct ira_diss_tree_instruction_decoding* instruction ) {

	struct ira_diss_tree_instruction_decoding *current = instruction;

	do {

		// Check mandatory prefixes.
		int prefixes_ok = 0;
		if( _IRA_PREFIX_REX( current->allowed_prefixes ) ) {
			// Check if there is REX prefix found.
			_ira_diss_context_get_REX_prefix(context, &prefixes_ok);
		} else if( _IRA_PREFIX_MANDATORY_66( current->allowed_prefixes ) ) {
			prefixes_ok = _ira_diss_context_is_prefix_available(context, 0x66);
		} else if( _IRA_PREFIX_MANDATORY_F2( current->allowed_prefixes ) ) {
			prefixes_ok = _ira_diss_context_is_prefix_available(context, 0xF2);
		} else if( _IRA_PREFIX_MANDATORY_F3( current->allowed_prefixes ) ) {
			prefixes_ok = _ira_diss_context_is_prefix_available(context, 0xF3);
		} else {
			prefixes_ok = 1;
		}
		if( !prefixes_ok ) {
			// Something wrong with prefixes, so go to next instruction.
			continue;
		}

		// Check opcode extension.
		int opcodes_ok = 0;
		if( _IRA_OPCODE_FLAGS_OPCODE_IS_EXT( current->opcode_flags ) ) {
			int result;
			uint8_t modrm = _ira_stream_peek(context->stream, &result );
			opcodes_ok = ( result && _IRA_MODRM_REG_OPCODE( modrm ) == _IRA_OPCODE_FLAGS_OPCODE_EXT(current->opcode_flags) );
		} else if( _IRA_OPCODE_FLAGS_OPCODE_IS_REX_EXT( current->opcode_flags ) ) {
			// TODO: Support fox REX opcode extension.
		} else {
			opcodes_ok = 1;
		}
		if( !opcodes_ok ) {
			// Something wrong with prefixes, so go to next instruction.
			continue;
		}

		break;

	} while( ( current = instruction->next_instruction_decoding ) != NULL );

	return current;
}

void ira_init(void) {
	// Clear disassemblation tree.
	memset( _ira_disassemblation_tree, 0, sizeof( _ira_disassemblation_tree ) );
	// Builds disassemblation tree basing on predefined instruction set.
	_ira_update_disassemblation_tree( _ira_instructions_desc );
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
    if( info->mode == IRA_MOD_64BIT && info->address_size_attribute == IRA_MOD_16BIT ) {
        result->code = RC_ERROR_ILLEGAL_ADDRESS_ATTRIBUTE_SIZE;
        return;
    }
    /* Check if attributes are valid and set them to default values. */
    if( info->address_size_attribute == 0 ) {
        switch(info->mode) {
            case IRA_MOD_16BIT:
                info->address_size_attribute = 16;
                break;
            case IRA_MOD_32BIT:
            case IRA_MOD_64BIT:
                info->address_size_attribute = 32;
                break;

        }
    }
    if( info->operand_size_attribute == 0 ) {
        switch(info->mode) {
            case IRA_MOD_16BIT:
                info->operand_size_attribute = 16;
                break;
            case IRA_MOD_32BIT:
                info->operand_size_attribute = 32;
                break;
            case IRA_MOD_64BIT:
                info->operand_size_attribute = 64;
                break;
        }
    }
    result->code = RC_OK;
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
			if( error != _IRA_INT_ERROR_OUT_OF_MEMORY ) {
				// Free disassemblation tree.
				_ira_free_disassemblation_tree( _ira_disassemblation_tree );
				// Return error.
				return error;
			}
		}
	}

	return _IRA_INT_ERROR_OUT_OF_MEMORY;

}

int _ira_add_instruction_decoding( struct ira_diss_tree_opcode *inst_desc, struct ira_instruction_desc *instruction_desc, struct ira_opcode_desc *opcode_desc ) {

	// Prepare instruction decoding structure.
	struct ira_diss_tree_instruction_decoding* decoding = malloc( sizeof( struct ira_diss_tree_instruction_decoding ) );
	if( decoding == NULL ) {
		return _IRA_INT_ERROR_OUT_OF_MEMORY;
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
	decoding->operand_decoders[0] = _ira_choose_operand_decoder( opcode_desc->opperand_1 );
	decoding->operand_decoders[1] = _ira_choose_operand_decoder( opcode_desc->opperand_2 );
	decoding->operand_decoders[2] = _ira_choose_operand_decoder( opcode_desc->opperand_3 );
	decoding->operand_decoders[3] = _ira_choose_operand_decoder( opcode_desc->opperand_4 );

	// Insert it in appropriate order.
	int order = _ira_get_decoding_order( decoding );

	struct ira_diss_tree_instruction_decoding **next_decoding_addr = &(inst_desc->instructions);

	while( *next_decoding_addr != NULL && _ira_get_decoding_order( *next_decoding_addr ) >= order ) {
		next_decoding_addr = &((*next_decoding_addr)->next_instruction_decoding);
	}

	decoding->next_instruction_decoding = *next_decoding_addr;
	*next_decoding_addr = decoding;

	return _IRA_INT_ERROR_OUT_OF_MEMORY;
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
	if( _IRA_PREFIX_REX(prefixes) ) {
		order += 2;
	}

	return order;
}

ira_operand_decoder _ira_choose_operand_decoder( uint8_t decoder_type ) {
	switch( decoder_type ) {
	case _IRA_OPERAND_IB:
		return &_ira_opcode_decoder_ib;
	case _IRA_OPERAND_IW:
		return &_ira_opcode_decoder_iw;
	case _IRA_OPERAND_ID:
		return &_ira_opcode_decoder_id;
	case _IRA_OPERAND_IO:
		return &_ira_opcode_decoder_io;
	}
	return NULL;
}

ira_instruction_decoder _ira_choose_instruction_decoder( uint8_t instruction_type ) {
	switch( instruction_type ) {
	case _IRA_IT_IA:
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

int _ira_diss_context_is_prefix_available( struct ira_diss_context *context, uint8_t prefix ) {
	struct ira_decoding_context *decoding_context = &(context->decoding_context);
	int prefix_count = decoding_context->instruction_prefix_count;
	int i, found = 0;
	for( i = 0; i < prefix_count; i++ ) {
		if( decoding_context->prefixes[i].prefix == prefix ) {
			found = 1;
			break;
		}
	}
	return found;
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
    if( result )
        return base_address[stream->offset++];
    return 0;
}

uint8_t _ira_stream_peek( struct ira_memory_stream *stream, int *result ) {
    uint8_t *base_address = (uint8_t *)stream->base_address;
    *result = ( stream->offset == stream->size ) ? 0 : 1;
    if( result )
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

/* Instruction decoders. */

void _ira_instruction_decoder_IA( struct ira_diss_context *context, struct ira_diss_tree_instruction_decoding *instruction, struct ira_disassemble_result *result ) {

	// Set mnemonic of disassembled instruction.
	result->mnemonic = instruction->mnemonic;

	// Copy prefixes.
	result->prefixes_count = context->decoding_context.instruction_prefix_count;

	int i;
	for( i = 0; i < result->prefixes_count && i < _IRA_PREFIXES_COUNT; i++ ) {
		result->prefixes[i] = context->decoding_context.prefixes[i];
	}

	// Copy opcodes.
	result->opcodes_count = instruction->

	for( i = 0; i < result->opcodes_count && i < _IRA_PREFIXES_COUNT; i++ ) {

	// Decode operands, one by one.
	for( i = 0; i < _IRA_OPERANDS_COUNT; i++ ) {
		ira_operand_decoder decoder = instruction->operand_decoders[i];
		if( decoder != NULL ) {
			result->operands[i] = decoder( context );
		} else {
			struct ira_instruction_operand *operand = &(result->operands[i]);
			memset( operand, 0, sizeof( struct ira_instruction_operand ) );
			operand->operand_type = IRA_NONE;
		}
	}

	result->code = RC_OK;
}

/* Operand decoders. */

struct ira_instruction_operand _ira_opcode_decoder_ib( struct ira_diss_context *context ) {
	struct ira_instruction_operand io = {0};
	_ira_decode_immediate( context, &(io.immediate), 8 );
	io.operand_type = IRA_IMMEDIATE_DATA_8;
	return io;
}

struct ira_instruction_operand _ira_opcode_decoder_iw( struct ira_diss_context *context ) {
	struct ira_instruction_operand io = {0};
	_ira_decode_immediate( context, &(io.immediate), 16 );
	io.operand_type = IRA_IMMEDIATE_DATA_16;
	return io;
}

struct ira_instruction_operand _ira_opcode_decoder_id( struct ira_diss_context *context ) {
	struct ira_instruction_operand io = {0};
	_ira_decode_immediate( context, &(io.immediate), 32 );
		io.operand_type = IRA_IMMEDIATE_DATA_32;
	return io;
}

struct ira_instruction_operand _ira_opcode_decoder_io( struct ira_diss_context *context ) {
	struct ira_instruction_operand io;
	_ira_decode_immediate( context, &(io.immediate), 64 );
		io.operand_type = IRA_IMMEDIATE_DATA_64;
	return io;
}

/* Helpers used to decode operands. */

int _ira_decode_immediate( struct ira_diss_context *context, union ira_immediate_data *data, int size ) {
	int result = 0;
	switch(size) {
	case 8:
		data->immediate_8 =_ira_stream_read( context->stream, &result );
		if( !result ) {
			return _IRA_INT_ERROR_CODE_UNEXPECTED_EOS;
		}
		break;
	case 16:
		if( !_ira_stream_read_bytes( context->stream, &(data->immediate_16), sizeof(uint16_t) ) ) {
			return _IRA_INT_ERROR_CODE_UNEXPECTED_EOS;
		}
		break;
	case 32:
		if( !_ira_stream_read_bytes( context->stream, &(data->immediate_32), sizeof(uint32_t) ) ) {
			return _IRA_INT_ERROR_CODE_UNEXPECTED_EOS;
		}
		break;
	case 64:
		if( !_ira_stream_read_bytes( context->stream, &(data->immediate_64), sizeof(uint64_t) ) ) {
			return _IRA_INT_ERROR_CODE_UNEXPECTED_EOS;
		}
		break;
	default:
		return _IRA_INT_ERROR_ILLEGAL_ARGUMENT;
	}
	return _IRA_INT_ERROR_NO_ERROR;
}
