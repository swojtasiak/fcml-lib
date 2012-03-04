
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include "ira_int.h"
#include "ira.h"

#include <assert.h>

#define _IRA_OPCODE_TABLE_SIZE	256

/* Callback used during disassemblation tree generation. */
typedef int ( *fp_ira_opcode_callback )( struct ira_instruction_desc *instruction_desc, struct ira_opcode_desc *opcode_desc, uint8_t opcode[3] );

struct ira_diss_tree_opcode* _ira_disassemblation_tree[_IRA_OPCODE_TABLE_SIZE] = {NULL};

/* Validates and fills structure with data from user. */
void _ira_prepare_disassemble_info( struct ira_disassemble_info *info, struct ira_disassemble_result *result );

/* Adds new instructions to disassemblation tree. */
int _ira_update_disassemblation_tree( struct ira_instruction_desc *instruction_desc );

/* Add instruction decoding to disassemblation tree. */
int _ira_add_instruction_decoding( struct ira_diss_tree_opcode *inst_desc, struct ira_instruction_desc *instruction_desc, struct ira_opcode_desc *opcode_desc );

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
int _ira_prepare_operand_decoding( struct ira_operand_decoding *operand_decoding, uint16_t decoder_type );

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

/* Sets opcode field into a opcode byte. */
uint8_t _ira_set_opcode_byte_field( uint8_t opcode_byte, int opcode_field_pos, int field_size, uint8_t field_value );

/* Gets opcode field from opcode byte. */
uint8_t _ira_get_opcode_byte_field( uint8_t opcode_byte, int opcode_field_pos, int field_size );

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
int _ira_opcode_decoder_implicit_register( struct ira_diss_context *context, struct ira_instruction_operand_wrapper *operand_wrapper, void *args );
int _ira_opcode_decoder_opcode_register( struct ira_diss_context *context, struct ira_instruction_operand_wrapper *operand_wrapper, void *args );
int _ira_opcode_decoder_immediate( struct ira_diss_context *context, struct ira_instruction_operand_wrapper *operand_wrapper, void *args );
int _ira_opcode_decoder_immediate_extends_eosa( struct ira_diss_context *context, struct ira_instruction_operand_wrapper *operand_wrapper, void *args );
int _ira_opcode_decoder_modrm_rm( struct ira_diss_context *context, struct ira_instruction_operand_wrapper *operand_wrapper, void *args );
int _ira_opcode_decoder_modrm_r( struct ira_diss_context *context, struct ira_instruction_operand_wrapper *operand_wrapper, void *args );
int _ira_opcode_decoder_modrm_m( struct ira_diss_context *context, struct ira_instruction_operand_wrapper *operand_wrapper, void *args );
int _ira_opcode_decoder_immediate_relative_dis_addressing( struct ira_diss_context *context, struct ira_instruction_operand_wrapper *operand_wrapper, void *args );
int _ira_opcode_decoder_call_rm( struct ira_diss_context *context, struct ira_instruction_operand_wrapper *operand_wrapper, void *args );
int _ira_opcode_decoder_far_pointer( struct ira_diss_context *context, struct ira_instruction_operand_wrapper *operand_wrapper, void *args );

/* Arguments allocators. */

void *_ira_alloc_reg_type_args( enum ira_register_type reg_type, int reg, int *result );
void *_ira_alloc_immediate_type_args( enum ira_immediate_data_type immediate_type, int *result );
void *_ira_alloc_modrm_decoding_args( enum ira_register_type reg_type, int operand_register_size, int size_directive, int *result );
void *_ira_alloc_modm_decoding_args( ira_size_directive_provider size_directive_provider, int *result );

// Size directive providers for memory based addressing decoders.

int ira_far_indirect_pointer_size_directive_provider( struct ira_diss_context *context );
int ira_mm_size_directive_provider( struct ira_diss_context *context );
int ira_m8_size_directive_provider( struct ira_diss_context *context );

/* Post processing handlers. */

int ira_relative_addressing_instruction_operand_handler( struct ira_diss_context *context, struct ira_instruction_operand *operand, struct ira_instruction_operand *istruction_operands[4] );

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
    context.instruction_pointer = info->instruction_pointer;

    // Identify prefixes.
    _ira_identify_prefixes( &context );

    // Prepares environment for disassemblation.
    _ira_prepare_environment( &context );

    // Found instruction.
    struct ira_diss_tree_instruction_decoding *instruction = NULL;
    // Current opcode table used to find instruction description.
    struct ira_diss_tree_opcode** opcodes = _ira_disassemblation_tree;

    struct ira_decoding_context *decoding_context = &(context.decoding_context);

    int opcode_num = 0;
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
    		// Store this opcode byte.
    		decoding_context->opcodes[opcode_num++] = opcode_byte;
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
    result->instruction_size = context.decoding_context.instruction_size;

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
	case _IRA_INT_ERROR_ILLEGAL_ARGUMENT:
		return RC_ERROR_UNEXPECTED_INTERNAL_ERROR;
	case _IRA_INT_ERROR_ILLEGAL_ADDRESSING:
		return RC_ERROR_ILLEGAL_ADDRESSING_MODE;
	case _IRA_INT_ERROR_INSTRUCTION_NOT_ENCODABLE:
		return RC_ERROR_INSTRUCTION_NOT_ENCODABLE;
	case _IRA_INT_ERROR_SYNTAX_NOT_SUPPORTED:
		return RC_ERROR_SYNTAX_NOT_SUPPORTED;
	case _IRA_INT_ERROR_ILLEGAL_INSTRUCTION:
		return RC_ERROR_ILLEGAL_INSTRUCTION;
	}
	return RC_ERROR_UNEXPECTED_INTERNAL_ERROR;
}

struct ira_diss_tree_instruction_decoding* _ira_choose_instruction( struct ira_diss_context *context, struct ira_diss_tree_instruction_decoding* instruction ) {

	struct ira_diss_tree_instruction_decoding *current = instruction;

	do {

		// Check prefixes.
		int prefixes_ok = 0;
		if( _IRA_PREFIX_REX_W_1( current->allowed_prefixes ) ) {
			int rex_found = 0;
			uint8_t rex = _ira_diss_context_get_REX_prefix(context, &rex_found);
			prefixes_ok = ( rex_found && _IRA_REX_W( rex ) );
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
			// Something wrong with prefixes, so go to the next instruction.
			continue;
		}

		// Check opcode extension.
		int opcodes_ok = 0;
		if( _IRA_OPCODE_FLAGS_OPCODE_IS_EXT( current->opcode_flags ) ) {
			int modrm_found = 0;
			uint8_t modrm = _ira_stream_peek(context->stream, &modrm_found );
			if( modrm_found ) {
				int rex_found = 0;
				uint8_t rex = _ira_diss_context_get_REX_prefix(context, &rex_found);
				if( rex_found ) {
					uint8_t ext_reg_opcode = ( ( rex & 0x04 ) << 1 ) | ( _IRA_MODRM_REG_OPCODE( modrm ) );
					uint8_t expected_ext_reg_opcode = _IRA_OPCODE_FLAGS_OPCODE_REX_EXT(current->opcode_flags);
					opcodes_ok = ( ext_reg_opcode == expected_ext_reg_opcode );
				} else {
					opcodes_ok = ( modrm_found && _IRA_MODRM_REG_OPCODE( modrm ) == _IRA_OPCODE_FLAGS_OPCODE_EXT(current->opcode_flags) );
				}
			}
		} else {
			opcodes_ok = 1;
		}
		if( !opcodes_ok ) {
			// Something wrong with prefixes, so go to the next instruction.
			continue;
		}

		// Check EOSA. These fields allow us to restrict instruction decoding only
		// to specific effective operand sizes. For instance we can define instruction
		// that can be chosen only if EOSA is equal to 16.
		if( _IRA_OPCODE_FLAGS_IS_EOSA_RESTRICTION(current->opcode_flags) ) {
			int mandatory_prefix = 0;
			// Ignore 0x66 prefix if this instruction uses it as mandatory prefix. This correction is also
			// done in the next phase for already chosen instruction.
			struct ira_instruction_prefix *prefix = _ira_diss_context_get_prefix_if_available( context, 0x66 );
			// Set this prefix as a mandatory one if this instruction defines 66 as mandatory.
			// This is set temporarily, only to calculate correct EOSA for instruction.
			if( prefix != NULL ) {
				mandatory_prefix = prefix->mandatory_prefix;
				prefix->mandatory_prefix = _IRA_PREFIX_MANDATORY_66( instruction->allowed_prefixes );
			}
			int eosa = _ira_get_effective_osa( context );
			if( prefix != NULL ) {
				prefix->mandatory_prefix = mandatory_prefix;
			}
			if( ( _IRA_OPCODE_FLAGS_EOSA_16( current->opcode_flags ) && eosa != 16 ) ||
				( _IRA_OPCODE_FLAGS_EOSA_32( current->opcode_flags ) && eosa != 32 ) ||
				( _IRA_OPCODE_FLAGS_EOSA_64( current->opcode_flags ) && eosa != 64 ) ) {
				// Wrong EOSA, ignore instruction.
				continue;
			}
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
                	// REX prefix is the last one, so we have to break this loop after finding one.
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
        // Break loop if REX prefix is already found.
    } while(prefix_type && prefix_type != IRA_REX);

    context->decoding_context.instruction_prefix_count = prefix_index;

    // Check if prefixes marked as mandatory are really a mandatory ones.
    if(prefix_index > 0) {
        int found_plain_prefix = 0;
        int i;
        for( i = prefix_index; i > 0; i-- ) {
             if( found_plain_prefix ) {
                 context->decoding_context.prefixes[i - 1].mandatory_prefix = 0;
             } else {
                 // REX prefixes have to be preceded by mandatory and optional prefixes if there are any.
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

/****************************************/
/* Disassemblation tree initialization. */
/****************************************/

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
				int i;
				for( i = 0; i < sizeof(current_inst_decoding->operand_decodings) / sizeof( struct ira_operand_decoding ); i++ ) {
					if( current_inst_decoding->operand_decodings[i].args != NULL ) {
						free( current_inst_decoding->operand_decodings[i].args );
					}
				}
				free( current_inst_decoding );
			}
			_ira_free_disassemblation_tree( diss_tree_opcode->opcodes );
			free( diss_tree_opcode );
		}
	}
}

/* Sets opcode field into a opcode byte. */
uint8_t _ira_set_opcode_byte_field( uint8_t opcode_byte, int opcode_field_pos, int field_size, uint8_t field_value ) {
	uint8_t bit_mask = ~( (int)pow( 2, field_size ) - 1 );
	return ( opcode_byte & bit_mask ) | ( field_value << opcode_field_pos );
}

/* Gets opcode field from opcode byte. */
uint8_t _ira_get_opcode_byte_field( uint8_t opcode_byte, int opcode_field_pos, int field_size ) {
	uint8_t bit_mask = (int)pow( 2, field_size ) - 1;
	return ( opcode_byte & bit_mask ) >> opcode_field_pos;
}

/* Function used to calculate all instruction opcode bytes using recursion. */
int _ira_handle_next_opcode_byte( struct ira_instruction_desc *instruction_desc, struct ira_opcode_desc *opcode_desc, uint8_t opcode_bytes[3], fp_ira_opcode_callback callback, int opcode_bytes_count, int opcode_byte_num, int primary_opcode_byte_num ) {

	// Get next opcode byte from instruction.
	if( opcode_byte_num == opcode_bytes_count ) {
		// There is no more opcode bytes available.
		int error = callback( instruction_desc, opcode_desc, opcode_bytes );
		return error;
	}

	uint8_t opcode_byte = opcode_desc->opcode[opcode_byte_num];

	// Check if this is an opcode with opcode fields.
	if( opcode_byte_num == primary_opcode_byte_num ) {

		uint32_t opcode_flags = opcode_desc->opcode_flags;

		int opcode_flags_pos = _IRA_OPCODE_FLAGS_POS( opcode_flags );

		// Opcode field: REG
		if( _IRA_OPCODE_FLAGS_OPCODE_FIELD_REG( opcode_flags ) ) {

			int i;
			for( i = 0; i < _IRA_REG_FIELD_NUMBER_OF_REGISTERS; i++ ) {
				// Prepare opcode byte with reg field.
				uint8_t opcode_byte_with_field = _ira_set_opcode_byte_field( opcode_byte, opcode_flags_pos, _IRA_REG_FIELD_SIZE, (uint8_t)i );
				opcode_bytes[opcode_byte_num] = opcode_byte_with_field;
				// Handle next opcode byte.
				_ira_handle_next_opcode_byte( instruction_desc, opcode_desc, opcode_bytes, callback, opcode_bytes_count, opcode_byte_num + 1, primary_opcode_byte_num );
			}

			return _IRA_INT_ERROR_NO_ERROR;
		}

		// Opcode field: TTTN
		else if( _IRA_OPCODE_FLAGS_OPCODE_FIELD_TTTN( opcode_flags ) ) {


			return _IRA_INT_ERROR_NO_ERROR;
		}
	}

	// This is a plain opcode byte that shouldn't be modified in any way.
	opcode_bytes[opcode_byte_num] = opcode_byte;
	// Handle next opcode byte.
	return _ira_handle_next_opcode_byte( instruction_desc, opcode_desc, opcode_bytes, callback, opcode_bytes_count, opcode_byte_num + 1, primary_opcode_byte_num );
}

int _ira_iterate_through_all_opcodes( struct ira_instruction_desc *instruction_desc, struct ira_opcode_desc *opcode_desc, fp_ira_opcode_callback callback ) {

	// Number of opcode bytes.
	int opcode_bytes_count = _IRA_OPCODE_FLAGS_OPCODE_NUM( opcode_desc->opcode_flags );

	// Opcode byte with potential flags.
	int primary_opcode_byte_num = _IRA_OPCODE_FLAGS_PRIMARY_OPCODE(opcode_desc->opcode_flags );

	assert( primary_opcode_byte_num < opcode_bytes_count );

	uint8_t opcode_bytes[3] = {0};

	// Handle all opcode bytes.
	return _ira_handle_next_opcode_byte( instruction_desc, opcode_desc, opcode_bytes, callback, opcode_bytes_count, 0, primary_opcode_byte_num );
}

int _ira_default_opcode_callback( struct ira_instruction_desc *instruction_desc, struct ira_opcode_desc *opcode_desc, uint8_t opcode_bytes[3] ) {

	struct ira_diss_tree_opcode** current_diss_tree_opcode = _ira_disassemblation_tree;
	struct ira_diss_tree_opcode* inst_desc = NULL;

	// Looking for a node in the instruction tree where now instruction should be placed. If there is no
	// appropriate node a new one is allocated.
	int i;
	int opcode_num = _IRA_OPCODE_FLAGS_OPCODE_NUM( opcode_desc->opcode_flags );
	for( i = 0; i < opcode_num; i++ ) {
		uint8_t opcode = opcode_bytes[i];
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

	return error;
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

			// Iterate through all opcode combination for this instruction form.
			int error = _ira_iterate_through_all_opcodes( instruction_desc, opcode_desc, &_ira_default_opcode_callback );
			if( error != _IRA_INT_ERROR_NO_ERROR ) {
				return error;
			}
		}
	}

	return _IRA_INT_ERROR_NO_ERROR;
}

int _ira_add_instruction_decoding( struct ira_diss_tree_opcode *inst_desc, struct ira_instruction_desc *instruction_desc, struct ira_opcode_desc *opcode_desc ) {

	int result = _IRA_INT_ERROR_NO_ERROR;

	// Prepare instruction decoding structure.
	struct ira_diss_tree_instruction_decoding* decoding = malloc( sizeof( struct ira_diss_tree_instruction_decoding ) );
	if( decoding == NULL ) {
		return _IRA_INT_ERROR_OUT_OF_MEMORY;
	}

	memset( decoding, 0, sizeof( struct ira_diss_tree_instruction_decoding ) );

	// Copy opcodes.
	int i;
	for( i = 0; i < sizeof( opcode_desc->opcode ); i++ ) {
		decoding->opcodes[i] = opcode_desc->opcode[i];
	}

	// Choose instruction mnemonic.
	decoding->mnemonic = instruction_desc->mnemonic;
	if( opcode_desc->mnemonic_override != NULL ) {
		decoding->mnemonic = opcode_desc->mnemonic_override;
	}

	// Copy flags.
	decoding->allowed_prefixes = opcode_desc->allowed_prefixes;
	decoding->opcode_flags = opcode_desc->opcode_flags;

	// Choose function used to disassemble instruction.
	decoding->instruction_decoder = _ira_choose_instruction_decoder( instruction_desc->instruction_type );

	// Choose functions used to decode operands.
	result = _ira_prepare_operand_decoding( &(decoding->operand_decodings[0]), opcode_desc->opperand_1 );
	if( result != _IRA_INT_ERROR_NO_ERROR ) {
		return result;
	}
	result = _ira_prepare_operand_decoding( &(decoding->operand_decodings[1]), opcode_desc->opperand_2 );
	if( result != _IRA_INT_ERROR_NO_ERROR ) {
		return result;
	}
	result = _ira_prepare_operand_decoding( &(decoding->operand_decodings[2]), opcode_desc->opperand_3 );
	if( result != _IRA_INT_ERROR_NO_ERROR ) {
		return result;
	}
	result = _ira_prepare_operand_decoding( &(decoding->operand_decodings[3]), opcode_desc->opperand_4 );
	if( result != _IRA_INT_ERROR_NO_ERROR ) {
		return result;
	}

	// Insert it in appropriate order.
	int order = _ira_get_decoding_order( decoding );

	struct ira_diss_tree_instruction_decoding **next_decoding_addr = &(inst_desc->instructions);

	while( *next_decoding_addr != NULL && _ira_get_decoding_order( *next_decoding_addr ) >= order ) {
		next_decoding_addr = &((*next_decoding_addr)->next_instruction_decoding);
	}

	decoding->next_instruction_decoding = *next_decoding_addr;
	*next_decoding_addr = decoding;

	return result;
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
	if( _IRA_PREFIX_REX_W_1( prefixes ) ) {
		order += 2;
	}

	return order;
}

void *_ira_alloc_reg_type_args( enum ira_register_type reg_type, int reg, int *result ) {
	struct ira_reg_type_args *args = (struct ira_reg_type_args*)malloc( sizeof( struct ira_reg_type_args ) );
	if( args != NULL ) {
		args->reg_type = reg_type;
		args->reg = reg;
	}
	*result = ( args == NULL ) ? _IRA_INT_ERROR_OUT_OF_MEMORY : _IRA_INT_ERROR_NO_ERROR;
	return args;
}

void *_ira_alloc_immediate_type_args( enum ira_immediate_data_type immediate_type, int *result ) {
	struct ira_immediate_type_args *args = (struct ira_immediate_type_args*)malloc( sizeof( struct ira_immediate_type_args ) );
	if( args != NULL ) {
		args->immediate_data_type = immediate_type;
	}
	*result = ( args == NULL ) ? _IRA_INT_ERROR_OUT_OF_MEMORY : _IRA_INT_ERROR_NO_ERROR;
	return args;
}

void *_ira_alloc_modrm_decoding_args( enum ira_register_type reg_type, int operand_register_size, int size_directive, int *result ) {
	struct ira_modrm_decoding_args *args = (struct ira_modrm_decoding_args*)malloc( sizeof( struct ira_modrm_decoding_args ) );
	if( args != NULL ) {
		args->reg_type = reg_type;
		args->operand_register_size = operand_register_size;
		args->size_directive = size_directive;
	}
	*result = ( args == NULL ) ? _IRA_INT_ERROR_OUT_OF_MEMORY : _IRA_INT_ERROR_NO_ERROR;
	return args;
}

void *_ira_alloc_modm_decoding_args( ira_size_directive_provider size_directive_provider, int *result ) {
	struct ira_modm_decoding_args *args = (struct ira_modm_decoding_args*)malloc( sizeof( struct ira_modm_decoding_args ) );
	if( args != NULL ) {
		args->size_directive_provider = size_directive_provider;
	}
	*result = ( args == NULL ) ? _IRA_INT_ERROR_OUT_OF_MEMORY : _IRA_INT_ERROR_NO_ERROR;
	return args;
}

int _ira_prepare_operand_decoding( struct ira_operand_decoding *operand_decoding, uint16_t decoding ) {

	int result = _IRA_INT_ERROR_NO_ERROR;

	// Store access mode for this operand decoding.
	operand_decoding->access_mode = ( decoding & _IRA_WRITE ) ? IRA_WRITE : IRA_READ;

	// Clear access mode.
	decoding &= ~_IRA_WRITE;

	uint16_t decoder_type = decoding & 0xFF00;

	operand_decoding->args = NULL;

	switch( decoder_type ) {
	case _IRA_OPERAND_REG_ACCUMULATOR_8:
		operand_decoding->decoder = &_ira_opcode_decoder_implicit_register;
		operand_decoding->args = _ira_alloc_reg_type_args( IRA_REG_GPR_8, _IRA_REG_AL, &result );
		break;
	case _IRA_OPERAND_REG_ACCUMULATOR_OSA:
		operand_decoding->decoder = &_ira_opcode_decoder_implicit_register;
		operand_decoding->args = _ira_alloc_reg_type_args( IRA_REG_GPR, _IRA_REG_AL, &result ); // EOSA.
		break;
	case _IRA_OPERAND_IB:
		operand_decoding->decoder = &_ira_opcode_decoder_immediate;
		operand_decoding->args = _ira_alloc_immediate_type_args( IRA_IMMEDIATE_8, &result );
		break;
	case _IRA_OPERAND_IB_EX_EOSA:
		operand_decoding->decoder = &_ira_opcode_decoder_immediate_extends_eosa;
		operand_decoding->args = _ira_alloc_immediate_type_args( IRA_IMMEDIATE_8, &result );
		break;
	case _IRA_OPERAND_IW:
		operand_decoding->decoder = &_ira_opcode_decoder_immediate;
		operand_decoding->args = _ira_alloc_immediate_type_args( IRA_IMMEDIATE_16, &result );
		break;
	case _IRA_OPERAND_IW_EX_EOSA:
		operand_decoding->decoder = &_ira_opcode_decoder_immediate_extends_eosa;
		operand_decoding->args = _ira_alloc_immediate_type_args( IRA_IMMEDIATE_16, &result );
		break;
	case _IRA_OPERAND_ID:
		operand_decoding->decoder = &_ira_opcode_decoder_immediate;
		operand_decoding->args = _ira_alloc_immediate_type_args( IRA_IMMEDIATE_32, &result );
		break;
	case _IRA_OPERAND_ID_EX_EOSA:
		operand_decoding->decoder = &_ira_opcode_decoder_immediate_extends_eosa;
		operand_decoding->args = _ira_alloc_immediate_type_args( IRA_IMMEDIATE_32, &result );
		break;
	case _IRA_OPERAND_IMM_EOSA:
		operand_decoding->decoder = &_ira_opcode_decoder_immediate;
		operand_decoding->args = _ira_alloc_immediate_type_args( 0, &result ); // EOSA.
		break;
	case _IRA_OPERAND_IO:
		operand_decoding->decoder = &_ira_opcode_decoder_immediate;
		operand_decoding->args = _ira_alloc_immediate_type_args( IRA_IMMEDIATE_64, &result );
		break;
	case _IRA_OPERAND_IO_EOSA:
		operand_decoding->decoder = &_ira_opcode_decoder_immediate_extends_eosa;
		operand_decoding->args = _ira_alloc_immediate_type_args( IRA_IMMEDIATE_64, &result );
		break;
	case _IRA_OPERAND_IMMEDIATE_DIS_RELATIVE:
		operand_decoding->decoder = &_ira_opcode_decoder_immediate_relative_dis_addressing;
		break;
	case _IRA_OPERAND_CALL_RM:
		operand_decoding->decoder = &_ira_opcode_decoder_call_rm;
		break;
	case _IRA_OPERAND_FAR_POINTER:
		operand_decoding->decoder = &_ira_opcode_decoder_far_pointer;
		break;
	case _IRA_OPERAND_FAR_POINTER_INDIRECT:
		operand_decoding->decoder = &_ira_opcode_decoder_modrm_m;
		operand_decoding->args = _ira_alloc_modm_decoding_args( &ira_far_indirect_pointer_size_directive_provider, &result );
		break;
	case _IRA_MODRM_BASE:

		// Gets appropriate ModR/M decoder.
		switch( decoding & 0x00FF ) {
		case _IRA_RM_8:
			operand_decoding->decoder = &_ira_opcode_decoder_modrm_rm;
			operand_decoding->args = _ira_alloc_modrm_decoding_args( IRA_REG_GPR, _IRA_OR_8, 8, &result );
			break;
		case _IRA_R_8:
			operand_decoding->decoder = &_ira_opcode_decoder_modrm_r;
			operand_decoding->args = _ira_alloc_modrm_decoding_args( IRA_REG_GPR, _IRA_OR_8, 8, &result );
			break;
		case _IRA_RM_16:
			operand_decoding->decoder = &_ira_opcode_decoder_modrm_rm;
			operand_decoding->args = _ira_alloc_modrm_decoding_args( IRA_REG_GPR, _IRA_OR_16, 16, &result );
			break;
		case _IRA_R_16:
			operand_decoding->decoder = &_ira_opcode_decoder_modrm_r;
			operand_decoding->args = _ira_alloc_modrm_decoding_args( IRA_REG_GPR, _IRA_OR_16, 16, &result );
			break;
		case _IRA_RM:
			operand_decoding->decoder = &_ira_opcode_decoder_modrm_rm;
			operand_decoding->args = _ira_alloc_modrm_decoding_args( IRA_REG_GPR, _IRA_OR_DEFAULT, _IRA_DEFAULT_SIZE_DIRECTIVE, &result );
			break;
		case _IRA_R:
			operand_decoding->decoder = &_ira_opcode_decoder_modrm_r;
			operand_decoding->args = _ira_alloc_modrm_decoding_args( IRA_REG_GPR, _IRA_OR_DEFAULT, _IRA_DEFAULT_SIZE_DIRECTIVE, &result );
			break;
		case _IRA_RM_MMX:
			operand_decoding->decoder = &_ira_opcode_decoder_modrm_rm;
			operand_decoding->args = _ira_alloc_modrm_decoding_args( IRA_REG_MMX, _IRA_OR_DEFAULT, _IRA_DEFAULT_SIZE_DIRECTIVE, &result );
			break;
		case _IRA_R_MMX:
			operand_decoding->decoder = &_ira_opcode_decoder_modrm_r;
			operand_decoding->args = _ira_alloc_modrm_decoding_args( IRA_REG_MMX, _IRA_OR_DEFAULT, _IRA_DEFAULT_SIZE_DIRECTIVE, &result );
			break;
		case _IRA_RM_XMM_128:
			operand_decoding->decoder = &_ira_opcode_decoder_modrm_rm;
			operand_decoding->args = _ira_alloc_modrm_decoding_args( IRA_REG_XMM, _IRA_OR_DEFAULT, 128, &result );
			break;
		case _IRA_R_XMM_128:
			operand_decoding->decoder = &_ira_opcode_decoder_modrm_r;
			operand_decoding->args = _ira_alloc_modrm_decoding_args( IRA_REG_XMM, _IRA_OR_DEFAULT, 128, &result );
			break;
		case _IRA_RM_XMM_64:
			operand_decoding->decoder = &_ira_opcode_decoder_modrm_rm;
			operand_decoding->args = _ira_alloc_modrm_decoding_args( IRA_REG_XMM, _IRA_OR_DEFAULT, 64, &result );
			break;
		case _IRA_R_XMM_64:
			operand_decoding->decoder = &_ira_opcode_decoder_modrm_r;
			operand_decoding->args = _ira_alloc_modrm_decoding_args( IRA_REG_XMM, _IRA_OR_DEFAULT, 64, &result );
			break;
		case _IRA_RM_XMM_32:
			operand_decoding->decoder = &_ira_opcode_decoder_modrm_rm;
			operand_decoding->args = _ira_alloc_modrm_decoding_args( IRA_REG_XMM, _IRA_OR_DEFAULT, 32, &result );
			break;
		case _IRA_R_XMM_32:
			operand_decoding->decoder = &_ira_opcode_decoder_modrm_r;
			operand_decoding->args = _ira_alloc_modrm_decoding_args( IRA_REG_XMM, _IRA_OR_DEFAULT, 32, &result );
			break;
		case _IRA_OSA_MM:
			operand_decoding->decoder = &_ira_opcode_decoder_modrm_m;
			operand_decoding->args = _ira_alloc_modm_decoding_args( &ira_mm_size_directive_provider, &result );
			break;
		case _IRA_M_8:
			operand_decoding->decoder = &_ira_opcode_decoder_modrm_m;
			operand_decoding->args = _ira_alloc_modm_decoding_args( &ira_m8_size_directive_provider, &result );
			break;
		}

		break;
	case _IRA_IMPLICIT_REG_BASE:
		operand_decoding->decoder = &_ira_opcode_decoder_implicit_register;
		operand_decoding->args = _ira_alloc_reg_type_args( ( decoding & 0x00F0 ) >> 4, ( decoding & 0x000F ), &result );
		break;
	case _IRA_OPERAND_OPCODE_REG_BASE:
		operand_decoding->decoder = &_ira_opcode_decoder_opcode_register;
		operand_decoding->args = _ira_alloc_reg_type_args( ( decoding & 0x00FF ), 0 /*From opcode.*/, &result );
		break;
	default:
		operand_decoding->decoder = NULL;
		operand_decoding->access_mode = IRA_ACCESS_MODE_UNDEFINED;
	}

	return result;
}

ira_instruction_decoder _ira_choose_instruction_decoder( uint8_t instruction_type ) {
	switch( instruction_type ) {
	case _IRA_IT_IA:
		// Currently only IA decoder is supported.
		return &_ira_instruction_decoder_IA;
	}
	return NULL;
}

/***********************************************/
/* End of disassemblation tree initialization. */
/***********************************************/

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
		int offset = stream->offset;
		value |= ((uint8_t*)stream->base_address)[offset];
		value |= ((uint8_t*)stream->base_address)[offset + 1] << 8;
		stream->offset += sizeof(uint16_t);
	}
	return value;
}

uint32_t _ira_stream_read_dword( struct ira_memory_stream *stream, int *result ) {
	uint32_t value = 0;
	*result = stream->size - stream->offset >= sizeof(uint32_t);
	if( *result ) {
		int offset = stream->offset;
		value |= ((uint8_t*)stream->base_address)[offset];
		value |= ((uint8_t*)stream->base_address)[offset + 1] << 8;
		value |= ((uint8_t*)stream->base_address)[offset + 2] << 16;
		value |= ((uint8_t*)stream->base_address)[offset + 3] << 24;
		stream->offset += sizeof(uint32_t);
	}
	return value;
}

uint64_t _ira_stream_read_qword( struct ira_memory_stream *stream, int *result ) {
	// TODO: test it!
	uint64_t value = 0;
	*result = stream->size - stream->offset >= sizeof(uint64_t);
	if( *result ) {
		int i;
		int offset = stream->offset;
		for( i = 0; i < sizeof(uint64_t); i++ ) {
			value |= ((uint8_t*)stream->base_address)[offset + i] << ( i << 3 );
		}
		stream->offset += sizeof(uint64_t);
	}
	return value;
}

/* Instruction decoders. */

int _ira_instruction_decoder_IA( struct ira_diss_context *context, struct ira_diss_tree_instruction_decoding *instruction, struct ira_disassemble_result *result ) {

	int i, rc;

	// Check if this instruction is supported in this mode.
	uint32_t opcode_flags = instruction->opcode_flags;

	enum ira_operation_mode mode = context->mode;

	if( ( ( mode == IRA_MOD_16BIT || mode == IRA_MOD_32BIT ) && !_IRA_OPCODE_FLAGS_16_32_BIT_MODE_SUPPORTED( opcode_flags ) )
			|| ( mode == IRA_MOD_64BIT && !_IRA_OPCODE_FLAGS_64_BIT_MODE_SUPPORTED( opcode_flags ) ) ) {
		// TODO: Czy zawsze not encodable? Moze w niektorych przypadkach jest invalid, albo cos w tym rodzaju?
		return _IRA_INT_ERROR_INSTRUCTION_NOT_ENCODABLE;
	}

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

	// Prepare decoding context.
	struct ira_decoding_context *decoding_context = &(context->decoding_context);

	for( i = 0; i < sizeof( instruction->opcodes ) ; i++ ) {
		decoding_context->base_opcodes[i] = instruction->opcodes[i];
	}

	for( i = 0; i < sizeof( result->opcodes ) ; i++ ) {
		result->opcodes[i] = decoding_context->opcodes[i];
	}

	// Copy opcodes' details.
	decoding_context->opcodes_count = _IRA_OPCODE_FLAGS_OPCODE_NUM( instruction->opcode_flags );
	decoding_context->primary_opcode_index = _IRA_OPCODE_FLAGS_PRIMARY_OPCODE( instruction->opcode_flags );

	result->opcodes_count = decoding_context->opcodes_count;
	result->primary_opcode_index = decoding_context->primary_opcode_index;

	// Calculates effective operand sizes. It's not important if they will be used or not.
	decoding_context->effective_address_size_attribute = _ira_get_effective_asa( context );
	decoding_context->effective_operand_size_attribute = _ira_get_effective_osa( context );

	struct ira_instruction_operand_wrapper operand_wrappers[4];

	memset( &operand_wrappers, 0, sizeof(operand_wrappers) );

	// Decode operands, one by one.
	for( i = 0; i < _IRA_OPERANDS_COUNT; i++ ) {
		struct ira_operand_decoding *decoding = &instruction->operand_decodings[i];
		ira_operand_decoder decoder = decoding->decoder;
		if( decoder != NULL ) {
			rc = decoder( context, &(operand_wrappers[i]), decoding->args );
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

	// Instruction size can be calculated here, and used during post processing phase.
	// This value can be used for instance to calculate relative addresses.
	context->decoding_context.instruction_size = context->stream->offset;

	// Array with all operands. It can be used by post processing handlers.
	struct ira_instruction_operand *istruction_operands[4];

	for( i = 0; i < _IRA_OPERANDS_COUNT; i++ ) {
		istruction_operands[i] = &(operand_wrappers[i].operand);
	}

	// Post processing.
	for( i = 0; i < _IRA_OPERANDS_COUNT; i++ ) {
		if( operand_wrappers[i].post_processor != NULL ) {
			operand_wrappers[i].post_processor(context, istruction_operands[i], istruction_operands );
		}
		result->operands[i] = operand_wrappers[i].operand;
	}
	return _IRA_INT_ERROR_NO_ERROR;
}

/* Operand decoders. */

void _ira_opcode_decoder_reg( struct ira_instruction_operand *operand, enum ira_register_type reg_type, int reg ) {
	operand->operand_type = IRA_REGISTER;
	operand->reg.reg_type = reg_type;
	operand->reg.reg = reg;
}

/* Decodes accumulator register. */
int _ira_opcode_decoder_implicit_register( struct ira_diss_context *context, struct ira_instruction_operand_wrapper *operand_wrapper, void *args ) {
	struct ira_reg_type_args *reg_type_args = (struct ira_reg_type_args*)args;
	enum ira_register_type reg_type = reg_type_args->reg_type;
	if( reg_type == IRA_REG_GPR ) {
		// A general purpose register, we should calculate it's size basing on EOSA.
		reg_type = _ira_map_osa_to_register_type( context );
	}
	_ira_opcode_decoder_reg( &(operand_wrapper->operand), reg_type, reg_type_args->reg );
	return _IRA_INT_ERROR_NO_ERROR;
}

/* Decodes opcode register. */
int _ira_opcode_decoder_opcode_register( struct ira_diss_context *context, struct ira_instruction_operand_wrapper *operand_wrapper, void *args ) {
	struct ira_reg_type_args *reg_type_args = (struct ira_reg_type_args*)args;
	enum ira_register_type reg_type = reg_type_args->reg_type;
	if( reg_type == IRA_REG_GPR ) {
		// A general purpose register, we should calculate it's size basing on EOSA.
		reg_type = _ira_map_osa_to_register_type( context );
	}
	struct ira_decoding_context *decoding_context = &(context->decoding_context);

	// We need primary opcode to calculate register.
	uint8_t primary_opcode_byte = decoding_context->opcodes[decoding_context->primary_opcode_index];

	uint8_t reg = _ira_get_opcode_byte_field( primary_opcode_byte, _IRA_REG_FIELD_POS, _IRA_REG_FIELD_SIZE );

	// TODO: Get it out of here...it should be in some utility function.
	int rex_found;
	uint8_t rex = _ira_diss_context_get_REX_prefix( context, &rex_found );
	if( context->mode == IRA_MOD_64BIT && rex_found ) {
		if( _IRA_REX_R( rex ) ) {
			reg |= 0x08;
		}
	}

	_ira_opcode_decoder_reg( &(operand_wrapper->operand), reg_type, reg );

	return _IRA_INT_ERROR_NO_ERROR;
}

// This decoding mode is used by CALL and JMP instructions.
int _ira_opcode_decoder_far_pointer( struct ira_diss_context *context, struct ira_instruction_operand_wrapper *operand_wrapper, void *args ) {

	struct ira_decoding_context *decoding_context = &(context->decoding_context);
	struct ira_instruction_operand *operand = &(operand_wrapper->operand);

	operand->operand_type = IRA_ADDRESS;

	struct ira_addressing *addressing = &(operand->addressing);

	addressing->addressing_type = IRA_FAR_POINTER;

	// Decoding offset.
	int result;

	switch( decoding_context->effective_operand_size_attribute ) {
	case 16:
		addressing->address_size = IRA_ADDRESS_16;
		addressing->address_value.address_16 = _ira_stream_read_word( context->stream, &result );
		break;
	case 32:
		addressing->address_size = IRA_ADDRESS_32;
		addressing->address_value.address_32 = _ira_stream_read_dword( context->stream, &result );
		break;
	case 64:
		addressing->address_size = IRA_ADDRESS_64;
		addressing->address_value.address_64 = _ira_stream_read_qword( context->stream, &result );
		break;
	}

	if( !result ) {
		return _IRA_INT_ERROR_CODE_UNEXPECTED_EOS;
	}

	// Decoding value for code segment register.
	struct ira_segment_selector *segment_selector = &(addressing->segment_selector);

	// This register cannot be overridden.
	segment_selector->segment_register = _IRA_SEG_REG_CS;

	segment_selector->segment_register_value = _ira_stream_read_word( context->stream, &result );
	if( !result ) {
		return _IRA_INT_ERROR_CODE_UNEXPECTED_EOS;
	}

	return _IRA_INT_ERROR_NO_ERROR;
}

int _ira_opcode_decoder_call_rm( struct ira_diss_context *context, struct ira_instruction_operand_wrapper *operand_wrapper, void *args ) {

	struct ira_decoding_context *decoding_context = &(context->decoding_context);

	// The operand-size attribute determines the size of the target operand (16, 32 or 64 bits).
	int operand_size = decoding_context->effective_operand_size_attribute;

	// When in 64-bit mode, the operand size for near call (and all near branches) is forced to 64-bits.
	if( context->mode == IRA_MOD_64BIT ) {
		operand_size = 64;
	}

	struct ira_modrm_decoding_args modrm_args;
	modrm_args.reg_type = IRA_REG_GPR;
	modrm_args.operand_register_size = operand_size;
	modrm_args.size_directive = operand_size;

	return _ira_opcode_decoder_modrm_rm( context, operand_wrapper, &modrm_args );
}

int _ira_opcode_decoder_immediate_relative_dis_addressing( struct ira_diss_context *context, struct ira_instruction_operand_wrapper *operand_wrapper, void *args ) {

	struct ira_decoding_context *decoding_context = &(context->decoding_context);

	// 16 bit relative addressing is not available in 64 bit mode.
	if( decoding_context->effective_operand_size_attribute == _IRA_OSA_16 && context->mode == IRA_MOD_64BIT ) {
		return _IRA_INT_ERROR_SYNTAX_NOT_SUPPORTED;
	}

	struct ira_instruction_operand *operand = &(operand_wrapper->operand);

	// Calculate size of immediate value that should be used to calculate relative address.
	struct ira_immediate_type_args immediate_args;

	immediate_args.immediate_data_type = IRA_IMMEDIATE_32;

	// For 32 and 64 bit addressing, 32 bit immediate value should be used.
	// Only for 16 bit addressing value differs and is equal to 16.
	if( context->decoding_context.effective_operand_size_attribute == 16 ) {
		immediate_args.immediate_data_type = IRA_IMMEDIATE_16;
	}

	// Read immediate value used then to calculate relative address.
	int result = _ira_opcode_decoder_immediate( context, operand_wrapper, &immediate_args );
	if( result != _IRA_INT_ERROR_NO_ERROR ) {
		return result;
	}

	// Set extension size. It's not used in next phases, it's for informational purpose only.
	operand->immediate.extension_size = context->decoding_context.effective_operand_size_attribute;

	// This handler is responsible for calculating address in post processing phase when
	// instruction size is already available.
	operand_wrapper->post_processor = &ira_relative_addressing_instruction_operand_handler;

	return _IRA_INT_ERROR_NO_ERROR;
}

/* Decodes immediate value and extends it to the effective operand size. */
int _ira_opcode_decoder_immediate_extends_eosa( struct ira_diss_context *context, struct ira_instruction_operand_wrapper *operand_wrapper, void *args ) {
	int result = _ira_opcode_decoder_immediate( context, operand_wrapper, args );
	if( result != _IRA_INT_ERROR_NO_ERROR ) {
		return result;
	}
	// Set extension size.
	operand_wrapper->operand.immediate.extension_size = context->decoding_context.effective_operand_size_attribute;
	return result;
}

int _ira_opcode_decoder_immediate( struct ira_diss_context *context, struct ira_instruction_operand_wrapper *operand_wrapper, void *args ) {
	struct ira_immediate_type_args *immediate_type_args = (struct ira_immediate_type_args*)args;
	int size = immediate_type_args->immediate_data_type;
	if( size == IRA_NO_IMMEDIATE_DATA ) {
		// If size is not specified use EOSA.
		size = context->decoding_context.effective_operand_size_attribute;
	}
	struct ira_instruction_operand *operand = &(operand_wrapper->operand);
	int result = _ira_decode_immediate( context, &(operand->immediate), size );
	if( result != _IRA_INT_ERROR_NO_ERROR ) {
		return result;
	}
	operand->operand_type = IRA_IMMEDIATE_DATA;
	operand->immediate.extension_size = 0;
	return _IRA_INT_ERROR_NO_ERROR;
}

// Memory addressing decoder. It is based on Mod/RM but registers aren't allowed ( R/M != 3 ).
int _ira_opcode_decoder_modrm_m( struct ira_diss_context *context, struct ira_instruction_operand_wrapper *operand_wrapper, void *args ) {

	struct ira_modm_decoding_args *register_type_size_args = (struct ira_modm_decoding_args*)args;
	struct ira_instruction_operand *operand = &(operand_wrapper->operand);
	struct ira_decoding_context *decoding_context = &(context->decoding_context);

	int size_directive;
	// Size directive can be provided but calculated using effective operand size attribute.
	if( register_type_size_args != NULL && register_type_size_args->size_directive_provider != NULL ) {
		size_directive = register_type_size_args->size_directive_provider( context );
	} else {
		// By default size directive is based on effective operand size attribute.
		size_directive = decoding_context->effective_operand_size_attribute;
	}

	operand->addressing.size_directive = size_directive;

	int result = _ira_modrm_decoder( context, IRA_REG_GPR, _IRA_OR_DEFAULT, _IRA_MOD_RM_FLAGS_DECODE_ADDRESSING );
	if( result != _IRA_INT_ERROR_NO_ERROR ) {
		return result;
	}

	struct ira_decoded_mod_rm *decoded_mod_rm = &(decoding_context->mod_rm);

	// By choosing this addressing decoder one has to be aware that
	// registers are not allowed here.
	if( _IRA_MODRM_MOD( decoded_mod_rm->raw_mod_rm.value ) == 3 ) {
		return _IRA_INT_ERROR_ILLEGAL_ADDRESSING;
	}

	// Prepare operand using decoded ModRM.
	result = _ira_modrm_decoder_operand_fill_address( context, &(operand_wrapper->operand) );
	if( result != _IRA_INT_ERROR_NO_ERROR ) {
		return result;
	}

	return _IRA_INT_ERROR_NO_ERROR;
}

//! Generic ModR/M addressing mode decoder.
/*!
 * \brief Generic ModR/M addressing mode decoder. This is a generic decoder that should be only used in functions
 * that are prepared to decode specific addressing modes.
 *
 * \param context Disassembling context.
 * \param operand Destination operand.
 * \param args Decoding arguments.
 * \return Error code.
 */
int _ira_opcode_decoder_modrm_rm( struct ira_diss_context *context, struct ira_instruction_operand_wrapper *operand_wrapper, void *args ) {

	struct ira_modrm_decoding_args *register_type_size_args = (struct ira_modrm_decoding_args*)args;

	struct ira_instruction_operand *operand = &(operand_wrapper->operand);

	// Setting size directive for addressing.
	int size_directive = register_type_size_args->size_directive;
	if( size_directive == _IRA_DEFAULT_SIZE_DIRECTIVE ) {
		operand->addressing.size_directive = context->decoding_context.effective_operand_size_attribute;
	} else {
		operand->addressing.size_directive = size_directive;
	}

	// Decode ModR/M.
	int result = _ira_modrm_decoder( context, register_type_size_args->reg_type, register_type_size_args->operand_register_size, _IRA_MOD_RM_FLAGS_DECODE_ADDRESSING );
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

int _ira_opcode_decoder_modrm_r( struct ira_diss_context *context, struct ira_instruction_operand_wrapper *operand_wrapper, void *args ) {

	struct ira_modrm_decoding_args *register_type_size_args = (struct ira_modrm_decoding_args*)args;

	// Decode ModR/M.
	int result = _ira_modrm_decoder( context, register_type_size_args->reg_type, register_type_size_args->operand_register_size, _IRA_MOD_RM_FLAGS_DECODE_REG );
	if( result != _IRA_INT_ERROR_NO_ERROR ) {
		return result;
	}

	struct ira_instruction_operand *operand = &(operand_wrapper->operand);

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
	if( reg_type == IRA_REG_GPR && operand_register_size != _IRA_OR_DEFAULT ) {
		switch( operand_register_size ) {
		case _IRA_OR_8:
			type = IRA_REG_GPR_8;
			break;
		case _IRA_OR_16:
			type = IRA_REG_GPR_16;
			break;
		}
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
		uint8_t effective_address_size = decoding_context->effective_address_size_attribute;
		result = _ira_decode_displacement( context, &(decoded_mod_rm->displacement), IRA_DISPLACEMENT_32,
						( effective_address_size == _IRA_ASA_64 ) ? IRA_DISPLACEMENT_EXT_SIZE_64 : IRA_DISPLACEMENT_EXT_SIZE_32 );
	} else {
		// Effective address size affects base register.
		uint8_t effective_address_size = decoding_context->effective_address_size_attribute;
		decoded_mod_rm->base_reg.reg_type = (effective_address_size == _IRA_ASA_64) ? IRA_REG_GPR_64 : IRA_REG_GPR_32;
		decoded_mod_rm->base_reg.reg = base;

		// There i no displacement for mod == 0.
		// TODO: Sprawdzic jak sie to ma do r/m == 5 przy dekodowaniu 32 bitowym.
		if( mod > 0 ) {
			result = _ira_decode_displacement( context, &(decoded_mod_rm->displacement), ( mod == 1 ) ? IRA_DISPLACEMENT_8 : IRA_DISPLACEMENT_32,
						( effective_address_size == _IRA_ASA_64 ) ? IRA_DISPLACEMENT_EXT_SIZE_64 : IRA_DISPLACEMENT_EXT_SIZE_32 );
		}
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
		uint8_t effective_address_size = decoding_context->effective_address_size_attribute;
		result = _ira_decode_displacement( context, &(decoded_mod_rm->displacement), IRA_DISPLACEMENT_32,
				( effective_address_size == _IRA_ASA_64 ) ? IRA_DISPLACEMENT_EXT_SIZE_64 : IRA_DISPLACEMENT_EXT_SIZE_32 );
	} else {
		// Base register.
		uint8_t effective_address_size = decoding_context->effective_address_size_attribute;
		decoded_mod_rm->base_reg.reg_type = (effective_address_size == _IRA_ASA_64) ? IRA_REG_GPR_64 : IRA_REG_GPR_32;
		decoded_mod_rm->base_reg.reg = rm;
		// Displacement.
		if( mod != 0 ) {
			result = _ira_decode_displacement( context, &(decoded_mod_rm->displacement), ( mod == 1 ) ? IRA_DISPLACEMENT_8 : IRA_DISPLACEMENT_32,
					( effective_address_size == _IRA_ASA_64 ) ? IRA_DISPLACEMENT_EXT_SIZE_64 : IRA_DISPLACEMENT_EXT_SIZE_32 );
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

// Post processor handlers.

int ira_relative_addressing_instruction_operand_handler( struct ira_diss_context *context, struct ira_instruction_operand *operand, struct ira_instruction_operand *istruction_operands[4] ) {

	struct ira_decoding_context *decoding_context = &(context->decoding_context);
	struct ira_immediate_data *immediate_data = &(operand->immediate);
	struct ira_addressing *addressing = &(operand->addressing);

	operand->operand_type = IRA_ADDRESS;

	addressing->addressing_type = IRA_RELATIVE_ADDRESS;

	int instruction_size = decoding_context->instruction_size;

	switch( decoding_context->effective_operand_size_attribute ) {
	case 16:
		{
			// 16 bit addressing.
			int16_t address = immediate_data->immediate_data.immediate_16;
			addressing->address_size = IRA_ADDRESS_32;
			addressing->address_value.address_32 = ((int32_t)(context->instruction_pointer.eip + instruction_size) + address) & 0x0000FFFF;
			break;
		}
		case 32:
		{
			// 32 bit addressing.
			int32_t address = immediate_data->immediate_data.immediate_32;
			addressing->address_size = IRA_ADDRESS_32;
			addressing->address_value.address_32 = (int32_t)(context->instruction_pointer.eip + instruction_size) + address;
			break;
		}
		case 64:
		{
			// 64 bit addressing.
			int64_t address = (int32_t)immediate_data->immediate_data.immediate_32;
			addressing->address_size = IRA_ADDRESS_64;
			addressing->address_value.address_64 = (int64_t)(context->instruction_pointer.rip + (int64_t)instruction_size) + (int64_t)address;
			break;
		}
	}

	return _IRA_INT_ERROR_NO_ERROR;
}

/*
 * Size directive providers for memory based addressing decoders.
 */

int ira_far_indirect_pointer_size_directive_provider( struct ira_diss_context *context ) {
	struct ira_decoding_context *decoding_context = &(context->decoding_context);
	return decoding_context->effective_operand_size_attribute + 16;
}

int ira_mm_size_directive_provider( struct ira_diss_context *context ) {
	struct ira_decoding_context *decoding_context = &(context->decoding_context);
	return decoding_context->effective_operand_size_attribute * 2;
}

int ira_m8_size_directive_provider( struct ira_diss_context *context ) {
	return 8;
}

