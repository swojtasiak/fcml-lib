
#include <string.h>

#include "ira_int.h"
#include "ira.h"

struct ira_diss_tree_opcode* _ira_disassemblation_tree[256];

/* Validates and fills structure with data from user. */
void ira_prepare_disassemble_info(struct ira_disassemble_info *info, struct ira_disassemble_result *result);

/* Adds new instructions to disassemblation tree. */
void ira_update_disassemblation_tree( struct ira_instruction_desc *instruction_desc );

void ira_disassemble( struct ira_disassemble_info *info, struct ira_disassemble_result *result ) {

    // Validate info structure.
    ira_prepare_disassemble_info( info, result );
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
    ira_identify_prefixes( &context );

    if( ira_stream_size( &stream ) == 0 ) {
    	ira_disassemble_default( &context, result );
    } else {

    }
}

void ira_init(void) {

	memset( _ira_disassemblation_tree, 0, sizeof( _ira_disassemblation_tree ) );

	ira_update_disassemblation_tree( _ira_instructions_desc );

}

void ira_deinit(void) {

}

/* Initialization. */

void ira_update_disassemblation_tree( struct ira_instruction_desc *instruction_desc ) {

	// Get instruction description.
	int instruction_index = 0;
	while( instruction_desc[instruction_index].name != NULL ) {
		struct ira_instruction_desc *instruction_desc = &instruction_desc[instruction_index++];

		// Get description of the specific instruction form.
		int opcode_index = 0;
		for( opcode_index = 0; opcode_index < instruction_desc->opcode_desc_count; opcode_index++ ) {
			struct ira_opcode_desc *opcode_desc = &(instruction_desc->opcodes[opcode_index]);

			struct ira_diss_tree_opcode** current_diss_tree_opcode = _ira_disassemblation_tree;

			// Get opcodes of the
			int i;
			for( i = 0; i < _IRA_OPCODE_FLAGS_OPCODE_NUM( opcode_desc->opcode_flags ); i++ ) {

				uint8_t opcode = opcode_desc->opcode[i];

				struct ira_diss_tree_opcode *inst_desc = current_diss_tree_opcode[opcode];
				if( inst_desc == NULL ) {
					// Create new node for this opcode.
				}

				//_ira_disassemblation_tree->

			}
		}

	}

}

/* Disassemblation. */

void ira_identify_prefixes( struct ira_diss_context *context ) {
    struct ira_memory_stream *stream = context->stream;
    int result = 0;
    enum ira_prefix_types prefix_type;
    int prefix_index = 0;
    uint8_t mandatory_prefix;
    do {
        prefix_type = 0;
        mandatory_prefix = 0;
        uint8_t prefix = ira_stream_peek(stream, &result);
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
                ira_stream_seek(stream, 1, IRA_CURRENT);
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

void ira_disassemble_default( struct ira_diss_context *context, struct ira_disassemble_result *result ) {

}


void ira_prepare_disassemble_info(struct ira_disassemble_info *info, struct ira_disassemble_result *result) {
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

/* Streaming. */

void ira_stream_seek( struct ira_memory_stream *stream, uint32_t offset, enum ira_seek_type type ) {
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

uint8_t ira_stream_read( struct ira_memory_stream *stream, int *result ) {
    uint8_t *base_address = (uint8_t *)stream->base_address;
    *result = ( stream->offset == stream->size ) ? 0 : 1;
    if( result )
        return base_address[stream->offset++];
    return 0;
}

uint8_t ira_stream_peek( struct ira_memory_stream *stream, int *result ) {
    uint8_t *base_address = (uint8_t *)stream->base_address;
    *result = ( stream->offset == stream->size ) ? 0 : 1;
    if( result )
        return base_address[stream->offset];
    return 0;
}

uint32_t ira_stream_size( struct ira_memory_stream *stream ) {
	return stream->size - stream->offset;
}

