
#include "ira_int.h"
#include "ira.h"

/* Validates and fills structure with data from user. */
void prepare_disassemble_info(struct disassemble_info *info, struct disassemble_result *result);

void ira_disassemble( struct disassemble_info *info, struct disassemble_result *result ) {

    // Validate info structure.
    prepare_disassemble_info( info, result );
    if( result->code != RC_OK ) {
        return;
    }

    // Prepare stream.
    struct memory_stream stream;
    stream.base_address = info->address;
    stream.size = info->size;
    stream.offset = 0;

    // Prepare disassemble context.
    struct diss_context context;
    context.stream = &stream;
    context.mode = info->mode;
    context.address_size_attribute = info->address_size_attribute;
    context.operand_size_attribute = info->operand_size_attribute;

    // Identify prefixes.
    identify_prefixes( &context );

    if( stream_size( &stream ) == 0 ) {
    	disassemble_default( &context, result );
    } else {

    }
}

/* Disassemblation. */

void identify_prefixes( struct diss_context *context ) {
    struct memory_stream *stream = context->stream;
    int result = 0;
    enum prefix_types prefix_type;
    int prefix_index = 0;
    uint8_t mandatory_prefix;
    do {
        prefix_type = 0;
        mandatory_prefix = 0;
        uint8_t prefix = stream_peek(stream, &result);
        if( result ) {
            struct instruction_prefix *prefix_desc = &(context->prefixes[prefix_index]);
            switch(prefix) {
                case 0xF0:
                    prefix_type = GROUP_1;
                    break;
                case 0xF2:
                case 0xF3:
                    mandatory_prefix = 1;
                    prefix_type = GROUP_1;
                    break;
                case 0x2E:
                case 0x36:
                case 0x3E:
                case 0x26:
                case 0x64:
                case 0x65:
                    prefix_type = GROUP_2;
                    break;
                break;
                case 0x66:
                    mandatory_prefix = 1;
                    prefix_type = GROUP_3;
                    break;
                case 0x67:
                    prefix_type = GROUP_4;
                    break;
                default:
                    if( context->mode == mod_64bit && prefix >= 0x40 && prefix <= 0x4F ) {
                        // REX prefix found.
                        prefix_type = REX;
                    }
                break;
            }
            if(prefix_type) {
                prefix_desc->prefix = prefix;
                prefix_desc->prefix_type = prefix_type;
                prefix_desc->mandatory_prefix = mandatory_prefix;
                stream_seek(stream, 1, CURRENT);
                prefix_index++;
            }
        }
    } while(prefix_type);

    context->instruction_prefix_count = prefix_index;

    // Check if prefixes marked as mandatory are really a mandatory ones.
    if(prefix_index > 0) {
        int found_plain_prefix = 0;
        int i;
        for( i = prefix_index; i > 0; i-- ) {
             if( found_plain_prefix ) {
                 context->prefixes[i - 1].mandatory_prefix = 0;
             } else {
                 // REX prefixes have to be preceded by mandatory prefixes if there are any.
                 struct instruction_prefix *prefix = &(context->prefixes[i - 1]);
                 if( !prefix->mandatory_prefix && prefix->prefix_type != REX ) {
                     found_plain_prefix = 1;
                 }
             }
        }
    }

}

void disassemble_default( struct diss_context *context, struct disassemble_result *result ) {

}


void prepare_disassemble_info(struct disassemble_info *info, struct disassemble_result *result) {
    /* Mode has to be set. */
    if( info->mode != mod_16bit && info->mode != mod_32bit && info->mode != mod_64bit ) {
        result->code = RC_ERROR_ILLEGAL_OPERATION_MODE;
        return;
    }
    /* 16 bit address size attribute is not supported in 64bit mode. */
    if( info->mode == mod_64bit && info->address_size_attribute == mod_16bit ) {
        result->code = RC_ERROR_ILLEGAL_ADDRESS_ATTRIBUTE_SIZE;
        return;
    }
    /* Check if attributes are valid and set them to default values. */
    if( info->address_size_attribute == 0 ) {
        switch(info->mode) {
            case mod_16bit:
                info->address_size_attribute = 16;
                break;
            case mod_32bit:
            case mod_64bit:
                info->address_size_attribute = 32;
                break;

        }
    }
    if( info->operand_size_attribute == 0 ) {
        switch(info->mode) {
            case mod_16bit:
                info->operand_size_attribute = 16;
                break;
            case mod_32bit:
                info->operand_size_attribute = 32;
                break;
            case mod_64bit:
                info->operand_size_attribute = 64;
                break;
        }
    }
    result->code = RC_OK;
}

/* Streaming. */

void stream_seek( struct memory_stream *stream, uint32_t offset, enum seek_type type ) {
    switch(type) {
        case START:
            stream->offset = offset;
        break;
        case CURRENT:
            stream->offset += offset;
        break;
        case END:
            stream->offset = (stream->size - offset);
        break;
    }
}

uint8_t stream_read( struct memory_stream *stream, int *result ) {
    uint8_t *base_address = (uint8_t *)stream->base_address;
    *result = ( stream->offset == stream->size ) ? 0 : 1;
    if( result )
        return base_address[stream->offset++];
    return 0;
}

uint8_t stream_peek( struct memory_stream *stream, int *result ) {
    uint8_t *base_address = (uint8_t *)stream->base_address;
    *result = ( stream->offset == stream->size ) ? 0 : 1;
    if( result )
        return base_address[stream->offset];
    return 0;
}

uint32_t stream_size( struct memory_stream *stream ) {
	return stream->size - stream->offset;
}

