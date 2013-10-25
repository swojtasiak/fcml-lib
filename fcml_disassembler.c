/*
 * fcml_disassembler.c
 *
 *  Created on: Oct 13, 2013
 *      Author: tas
 */

#include "fcml_modrm_decoder.h"
#include "fcml_stream.h"
#include "fcml_disassembler.h"
#include "fcml_asm_decoding.h"
#include "fcml_env.h"

/**************************
 * Input validation
 **************************/

fcml_ceh_error fcml_ifn_dasm_validate_and_prepare_context( fcml_st_disassembler_context *context ) {

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

fcml_ceh_error fcml_fn_dasm_decode_prefixes( fcml_st_asm_decoding_context *decoding_context) {

	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

	fcml_st_asm_dec_prefixes *prefixes = &(decoding_context->prefixes);
	fcml_st_memory_stream *stream = decoding_context->stream;
	fcml_en_addr_form addr_form = decoding_context->disassembler_context->addr_form;
	fcml_st_asm_dec_prefixes *prefixes_details = &(decoding_context->prefixes);

	fcml_bool result = FCML_FALSE;
	fcml_int prefix_index = 0;
	fcml_int prefix_size;
	fcml_st_dasm_prefix_types prefix_type;
	fcml_bool is_mandatory_candidate;
	fcml_bool is_xop_vex_allowed = FCML_TRUE;
	fcml_bool is_last_prefix = FCML_FALSE;
	fcml_int xop_vex_prefix_size = 0;

	do {
		prefix_type = FCML_PT_GROUP_UNKNOWN;
		is_mandatory_candidate = FCML_FALSE;
		// Almost all prefixes are one byte length, so it's a reasonable default here.
		prefix_size = 1;
		fcml_uint8_t prefix = fcml_fn_stream_peek(stream, &result);
		if( result ) {
			fcml_st_dasm_instruction_prefix *prefix_details = &(prefixes->prefixes[prefix_index]);
			switch(prefix) {
				case 0xF0:
					prefix_type = FCML_PT_GROUP_1;
					is_xop_vex_allowed = FCML_FALSE;
					break;
				case 0xF2:
				case 0xF3:
					is_mandatory_candidate = FCML_TRUE;
					prefix_type = FCML_PT_GROUP_1;
					is_xop_vex_allowed = FCML_FALSE;
					break;
				case 0x2E:
				case 0x36:
				case 0x3E:
				case 0x26:
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
					prefixes_details->is_vex = FCML_TRUE;
					is_last_prefix = FCML_TRUE;
					break;
				case 0x8F:
					xop_vex_prefix_size = 2;
					prefix_type = FCML_PT_XOP;
					prefixes_details->is_xop = FCML_TRUE;
					is_last_prefix = FCML_TRUE;
					break;
				case 0xC4:
					xop_vex_prefix_size = 2;
					prefix_type = FCML_PT_VEX;
					prefixes_details->is_vex = FCML_TRUE;
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
					fcml_fn_stream_seek(stream, 1, IRA_CURRENT);

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
				prefixes_details->prefixes_bytes_count += prefix_size;
				fcml_fn_stream_seek(stream, prefix_size, IRA_CURRENT);
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
				 prefixes->prefixes[prefix_index].mandatory_prefix = FCML_FALSE;
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

/****************************
 * API.
 ****************************/

fcml_ceh_error fcml_fn_disassembler_init( fcml_st_dialect_context *context, fcml_st_disassembler **disassembler ) {
	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

	*disassembler = fcml_fn_env_memory_alloc( sizeof( fcml_st_disassembler ) );
	if( *disassembler ) {
		error = fcml_fn_asm_init_instruction_decodings( context, disassembler );
	} else {
		error = FCML_CEH_GEC_OUT_OF_MEMORY;
	}

	return error;
}

fcml_ceh_error fcml_fn_disassemble( fcml_st_disassembler_context *context, fcml_st_disassembler_result **result ) {

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
	fcml_st_asm_decoding_context decoding_context = {0};
	decoding_context.disassembler_context = context;
	decoding_context.effective_address_size_attribute = context->address_size_attribute;
	decoding_context.effective_operand_size_attribute = context->operand_size_attribute;

	decoding_context.stream = &stream;

	error = fcml_fn_dasm_decode_prefixes( &decoding_context );
	if( error ) {
		return error;
	}

	error =  fcml_fn_asm_decode_instruction( &decoding_context );

	if( !error ) {
		fcml_st_disassembler_result *dis_res = fcml_fn_env_clear_memory_alloc( sizeof( fcml_st_disassembler_result ) );
		if( dis_res ) {

			// Prepare operands.
			int i;
			for( i = 0; i < FCML_OPERANDS_COUNT; i++ ) {
				fcml_ist_asm_dec_operand_wrapper *operand_wrapper = &(decoding_context.operand_wrappers[i]);
				if( operand_wrapper->operand.type != FCML_EOT_NONE ) {
					dis_res->operands[i] = operand_wrapper->operand;
					dis_res->operand_details[i].access_mode = operand_wrapper->access_mode;
				} else {
					break;
				}
			}

			// Prefixes.
			dis_res->prefixes = decoding_context.prefixes;

			// Copy instruction hints.
			dis_res->hints = decoding_context.instruction_hints;

			// Instruction code.
			dis_res->instruction_size = decoding_context.calculated_instruction_size;
			fcml_fn_env_memory_copy( &dis_res->instruction_code, context->code_address, dis_res->instruction_size > FCML_INSTRUCTION_SIZE ? FCML_INSTRUCTION_SIZE : dis_res->instruction_size );

			// Conditions.
			if( decoding_context.is_conditional ) {
				dis_res->is_conditional = FCML_TRUE;
				dis_res->condition = decoding_context.condition;
			} else {
				dis_res->is_conditional = FCML_FALSE;
			}

			// Mnemonic.
			fcml_bool shortform = decoding_context.disassembler_context->configuration.use_short_form_mnemonics;
			fcml_st_mp_mnemonic *mnemonic = fcml_fn_mp_choose_mnemonic( decoding_context.mnemonics, shortform, decoding_context.pseudo_opcode, decoding_context.effective_operand_size_attribute, decoding_context.effective_address_size_attribute );
			if( mnemonic ) {
				dis_res->is_pseudo_op_shortcut = mnemonic->pseudo_op.is_not_null;
				dis_res->is_shortcut = mnemonic->shortcut;
				dis_res->mnemonic = mnemonic->mnemonic;
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

void fcml_fn_disassemble_result_free( fcml_st_disassembler_result *result ) {
	if( result ) {
		if( result->errors ) {
			fcml_fn_ceh_free_error_container( result->errors );
		}
		fcml_fn_env_memory_free( result );
	}
}

void fcml_fn_disassembler_free( fcml_st_disassembler *disassembler ) {
	fcml_fn_asm_free_instruction_decodings( disassembler );
}
