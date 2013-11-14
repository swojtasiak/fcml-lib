/*
 * fcml_apc_ast.c
 *
 *  Created on: 10-03-2013
 *      Author: tAs
 */

#include <string.h>
#include "fcml_env.h"
#include "fcml_apc_ast.h"
#include "fcml_utils.h"
#include "fcml_errors.h"

fcml_st_ast_node *fcml_fn_ast_alloc_node_integer( fcml_st_ast_val_integer *integer_value ) {
	fcml_st_ast_node *node = malloc( sizeof( fcml_st_ast_node ) );
	if( !node ) {
		return NULL;
	}
	fcml_st_ast_node_value *value_node = malloc( sizeof( fcml_st_ast_node_value ) );
	if( !value_node ) {
		free(node);
		return NULL;
	}
	value_node->type = FCML_EN_ET_INTEGER;
	value_node->integer_value = *integer_value;
	node->type = FCML_EN_TN_VALUE;
	node->node = value_node;
	return node;
}

fcml_st_ast_node *fcml_fn_ast_alloc_node_float( fcml_st_ast_val_float *float_value ) {
	fcml_st_ast_node *node = malloc( sizeof( fcml_st_ast_node ) );
	if( !node ) {
		return NULL;
	}
	fcml_st_ast_node_value *exp_node = malloc( sizeof( fcml_st_ast_node_value ) );
	if( !exp_node ) {
		free(node);
		return NULL;
	}
	exp_node->type = FCML_EN_ET_FLOAT;
	exp_node->float_value = *float_value;
	node->type = FCML_EN_TN_VALUE;
	node->node = exp_node;
	return node;
}

fcml_st_ast_node *fcml_fn_ast_alloc_node_operand_list( fcml_st_ast_node *operand_l, fcml_st_ast_node *operand_r ) {
	fcml_st_ast_node *operand_list_node = NULL;
	fcml_st_ast_node_operand_list *operand_list = NULL;
	if( operand_l->type != FCML_EN_TN_OPERAND_LIST ) {
		operand_list_node = malloc( sizeof( fcml_st_ast_node ) );
		if( !operand_list_node ) {
			return NULL;
		}
		operand_list = malloc( sizeof( fcml_st_ast_node_operand_list ) );
		if( !operand_list ) {
			free(operand_list_node);
			return NULL;
		}
		operand_list_node->type = FCML_EN_TN_OPERAND_LIST;
		operand_list_node->node = operand_list;
		operand_list->operands = fcml_fn_coll_list_alloc();
		if( !operand_list->operands ) {
			free(operand_list_node);
			free(operand_list);
			return NULL;
		}
		if( !fcml_fn_coll_list_add_back( operand_list->operands, operand_l ) || ( operand_r != NULL && !fcml_fn_coll_list_add_back( operand_list->operands, operand_r ) ) ) {
			free(operand_list_node);
			free(operand_list);
			fcml_fn_coll_list_free( operand_list->operands, NULL, NULL );
			return NULL;
		}
	} else {
		operand_list_node = operand_l;
		operand_list = (fcml_st_ast_node_operand_list*)operand_l->node;
		if( !fcml_fn_coll_list_add_back( operand_list->operands, operand_r ) ) {
			return NULL;
		}
	}
	return operand_list_node;
}

fcml_st_ast_node *fcml_fn_ast_alloc_node_instruction( fcml_prefixes prefixes, fcml_string mnemonic, fcml_usize length, fcml_hints hints, fcml_st_ast_node *operands_list ) {
	fcml_st_ast_node *node = malloc( sizeof( fcml_st_ast_node ) );
	if( !node ) {
		return NULL;
	}
	fcml_st_ast_node_instruction *instruction_node = malloc( sizeof( fcml_st_ast_node_instruction ) );
	if( !instruction_node ) {
		free(node);
		return NULL;
	}
	instruction_node->mnemonic = (fcml_string)fcml_fn_env_str_strldup( mnemonic, length );
	if( !instruction_node->mnemonic ) {
		free(node);
		free(instruction_node);
		return NULL;
	}
	instruction_node->operands = operands_list;
	instruction_node->hints = hints;
	instruction_node->prefixes = prefixes;
	node->type = FCML_EN_TN_INSTRUCTION;
	node->node = instruction_node;
	return node;
}

fcml_st_ast_node *fcml_fn_ast_alloc_node_register( fcml_st_register *reg ) {
	fcml_st_ast_node *node = malloc( sizeof( fcml_st_ast_node ) );
	if( !node ) {
		return NULL;
	}
	fcml_st_ast_node_register *reg_node = malloc( sizeof( fcml_st_ast_node_register ) );
	if( !reg_node ) {
		free(node);
		return NULL;
	}
	reg_node->reg = *reg;
	node->type = FCML_EN_TN_REG;
	node->node = reg_node;
	return node;
}

fcml_st_ast_node *fcml_fn_ast_alloc_node_exp( fcml_en_ast_exp_node_operator operator, fcml_st_ast_node *exp_left, fcml_st_ast_node *exp_right ) {
	fcml_st_ast_node *node = malloc( sizeof( fcml_st_ast_node ) );
	if( !node ) {
		return NULL;
	}
	fcml_st_ast_node_exp *exp_node = malloc( sizeof( fcml_st_ast_node_exp ) );
	if( !exp_node ) {
		free(node);
		return NULL;
	}
	exp_node->l = exp_left;
	exp_node->r = exp_right;
	exp_node->operator = operator;
	node->type = FCML_EN_TN_EXP;
	node->node = exp_node;
	return node;
}

fcml_st_ast_node *fcml_fn_ast_alloc_node_far_pointer( fcml_st_ast_node *segment_selector, fcml_st_ast_node *offset ) {
	fcml_st_ast_node *node = malloc( sizeof( fcml_st_ast_node ) );
	if( !node ) {
		return NULL;
	}
	fcml_st_ast_node_far_pointer *fp_node = malloc( sizeof( fcml_st_ast_node_far_pointer ) );
	if( !fp_node ) {
		free(node);
		return NULL;
	}
	fp_node->segment_selector = segment_selector;
	fp_node->offset = offset;
	node->type = FCML_EN_TN_FAR_POINTER;
	node->node = fp_node;
	return node;
}

fcml_st_ast_node *fcml_fn_ast_set_effective_address_details( fcml_st_register *segment_selector, fcml_st_size_operator *size_operator, fcml_st_ast_node *effective_address_node ) {
	fcml_st_ast_node_effective_address *effective_address = (fcml_st_ast_node_effective_address *)effective_address_node->node;
	if( segment_selector ) {
		effective_address->segment_selector = *segment_selector;
	}
	effective_address->size_operator = size_operator->size;
	if( size_operator->multimedia ) {
		effective_address->addressing_hints |= FCML_OP_HINT_MULTIMEDIA_INSTRUCTION;
	}
	return effective_address_node;
}

fcml_st_ast_node *fcml_fn_ast_alloc_node_effective_address( fcml_st_register *base, fcml_st_register *index, fcml_st_ast_val_integer *scale_factor, fcml_st_ast_node *displacement, fcml_bool uminus_displacement, fcml_hints hints ) {
	fcml_st_ast_node *node = malloc( sizeof( fcml_st_ast_node ) );
	if( !node ) {
		return NULL;
	}
	fcml_st_ast_node_effective_address *ea_node = fcml_fn_env_memory_alloc_clear(sizeof( fcml_st_ast_node_effective_address ) );
	if( !ea_node ) {
		free(node);
		return NULL;
	}
	ea_node->addressing_hints = hints;
	if( base ) {
		ea_node->base = *base;
	}
	if( index ) {
		ea_node->index = *index;
	}
	if( scale_factor ) {
		ea_node->scale_factor = *scale_factor;
	}
	if( displacement ) {
		ea_node->displacement = ( uminus_displacement ) ? fcml_fn_ast_alloc_node_uminus( displacement ) : displacement;
	}
	node->node = ea_node;
	node->type = FCML_EN_TN_EFFECTIVE_ADDRESS;
	return node;
}

fcml_st_ast_node *fcml_fn_ast_alloc_node_uminus( fcml_st_ast_node *exp ) {

	fcml_st_ast_node *node;
	fcml_st_ast_node_uminus *uminus_node;

	// Two unary minuses, so they can be reduced here.
	if( exp->type == FCML_EN_TN_UMINUS ) {
		uminus_node = (fcml_st_ast_node_uminus*)exp->node;
		node = uminus_node->exp;
		free( exp );
		free( uminus_node );
		return node;
	}

	node = malloc( sizeof( fcml_st_ast_node ) );
	if( !node ) {
		return NULL;
	}
	uminus_node = malloc( sizeof( fcml_st_ast_node_uminus ) );
	if( !uminus_node ) {
		free(node);
		return NULL;
	}
	uminus_node->exp = exp;
	node->node = uminus_node;
	node->type = FCML_EN_TN_UMINUS;
	return node;

}

void fcml_ifn_ast_free_operand_node_list_action( fcml_ptr item_value, fcml_ptr args ) {
	fcml_st_ast_node *node = (fcml_st_ast_node*)item_value;
	fcml_fn_ast_free_node( node );
}

void fcml_fn_ast_free_node( fcml_st_ast_node *exp ) {
	if( exp ) {
		switch( exp->type ) {
			case FCML_EN_TN_INSTRUCTION: {
					fcml_st_ast_node_instruction *instruction = (fcml_st_ast_node_instruction*)exp->node;
					if( instruction->mnemonic ) {
						fcml_fn_env_str_strfree( instruction->mnemonic );
					}
					fcml_fn_ast_free_node( instruction->operands );
					break;
				}
			case FCML_EN_TN_OPERAND_LIST: {
					fcml_st_ast_node_operand_list *operand_list = (fcml_st_ast_node_operand_list*)exp->node;
					fcml_fn_coll_list_free( operand_list->operands, fcml_ifn_ast_free_operand_node_list_action, NULL );
					break;
				}
			break;
			case FCML_EN_TN_EXP: {
					fcml_st_ast_node_exp *expr = (fcml_st_ast_node_exp*)exp->node;
					fcml_fn_ast_free_node( expr->l );
					fcml_fn_ast_free_node( expr->r );
					break;
				}
			break;
			case FCML_EN_TN_UMINUS: {
					fcml_st_ast_node_uminus *uminus = (fcml_st_ast_node_uminus*)exp->node;
					fcml_fn_ast_free_node( uminus->exp );
					break;
				}
			break;
			case FCML_EN_TN_FAR_POINTER: {
					fcml_st_ast_node_far_pointer *far_pointer = (fcml_st_ast_node_far_pointer*)exp->node;
					fcml_fn_ast_free_node( far_pointer->offset );
					fcml_fn_ast_free_node( far_pointer->segment_selector );
					break;
				}
				break;
			case FCML_EN_TN_EFFECTIVE_ADDRESS: {
					fcml_st_ast_node_effective_address *effective_address = (fcml_st_ast_node_effective_address*)exp->node;
					fcml_fn_ast_free_node( effective_address->displacement );
					break;
				}
				break;
			default:
				break;
		}
		if( exp->node ) {
			free(exp->node);
		}
		free(exp);
	}
}

fcml_ceh_error fcml_ifn_ast_handle_ast_node( fcml_st_instruction *cif_instruction, fcml_st_operand *current_operand, fcml_st_ast_node *ast_node, fcml_st_ceh_error_container *error_container );

fcml_ceh_error fcml_fn_ast_to_cif_converter( fcml_st_ast_node *ast_instruction_node, fcml_st_ceh_error_container *out_error_container, fcml_st_instruction **out_instruction ) {
	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
	fcml_st_instruction *instruction = (fcml_st_instruction*)fcml_fn_env_memory_alloc( sizeof( fcml_st_instruction ) );
	if( instruction ) {
		memset( instruction, 0, sizeof( fcml_st_instruction ) );
		error =  fcml_ifn_ast_handle_ast_node( instruction, NULL, ast_instruction_node, out_error_container );
		if( error ) {
			fcml_fn_ast_free_converted_cif( instruction );
		} else {
			*out_instruction = instruction;
		}
	}
	return error;
}

void fcml_fn_ast_free_converted_cif( fcml_st_instruction *cif_instruction ) {
	if( cif_instruction ) {
		if( cif_instruction->mnemonic ) {
			fcml_fn_env_str_strfree(cif_instruction->mnemonic);
		}
		fcml_fn_env_memory_free( cif_instruction );
	}
}

float fcml_ifn_ast_get_float_value( fcml_st_ast_node_value *value ) {
	float val;
	if( value->type == FCML_EN_ET_FLOAT ) {
		val = value->float_value.value;
	} else {
		val = (float)value->integer_value.value;
	}
	return val;
}

fcml_int64_t fcml_ifn_ast_get_integer_value( fcml_st_ast_node_value *value ) {
	fcml_int64_t val;
	if( value->type == FCML_EN_ET_FLOAT ) {
		val = (fcml_int64_t)value->float_value.value;
	} else {
		val = (fcml_int64_t)value->integer_value.value;
	}
	return val;
}

fcml_st_ast_val_integer fcml_ifn_ast_convert_to_val_integer( fcml_int64_t val ) {
	fcml_st_ast_val_integer int_value;
	int_value.value = (fcml_uint64_t)val;
	int_value.is_signed = val < 0;
	return int_value;
}

fcml_ceh_error fcml_ifn_ast_eval_exp( fcml_st_ast_node *exp, fcml_st_ceh_error_container *error_container, fcml_st_ast_node_value *result ) {
	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
	switch( exp->type ) {
	case FCML_EN_TN_VALUE: {
		*result = *((fcml_st_ast_node_value*)exp->node);
		break;
	}
	case FCML_EN_TN_UMINUS: {
		error = fcml_ifn_ast_eval_exp( ((fcml_st_ast_node_uminus*)exp->node)->exp, error_container, result );
		if( error ) {
			return error;
		}
		if( result->type == FCML_EN_ET_INTEGER ) {
			if( result->integer_value.overflow ) {
				fcml_fn_ceh_add_error( error_container, "Value out of range.", FCML_EN_APC_AST_WARN_VALUE_OUT_OF_RANGE, FCML_EN_CEH_EL_WARN );
			}
			result->integer_value = fcml_ifn_ast_convert_to_val_integer( -((fcml_int64_t)result->integer_value.value) );
		} else {
			result->float_value.value = -result->float_value.value;
		}
		break;
	}
	case FCML_EN_TN_EXP: {
		fcml_st_ast_node_exp *exp_node = (fcml_st_ast_node_exp*)exp->node;
		fcml_st_ast_node_value lval = { 0 };
		fcml_st_ast_node_value rval = { 0 };
		fcml_ceh_error error;
		error = fcml_ifn_ast_eval_exp( exp_node->l, error_container, &lval );
		if( error ) {
			return error;
		}
		error = fcml_ifn_ast_eval_exp( exp_node->r, error_container, &rval );
		if( error ) {
			return error;
		}
		fcml_bool is_float = FCML_FALSE;
		result->type = FCML_EN_ET_INTEGER;
		if( lval.type == FCML_EN_ET_FLOAT || rval.type == FCML_EN_ET_FLOAT ) {
			result->type = FCML_EN_ET_FLOAT;
			is_float = FCML_TRUE;
		}
		switch( exp_node->operator ) {
		case FCML_EN_EXN_SUB:
			if( is_float ) {
				result->float_value.value = fcml_ifn_ast_get_float_value( &lval ) - fcml_ifn_ast_get_float_value( &rval );
			} else {
				result->integer_value = fcml_ifn_ast_convert_to_val_integer( fcml_ifn_ast_get_integer_value( &lval ) - fcml_ifn_ast_get_integer_value( &rval ) );
			}
			break;
		case FCML_EN_EXN_ADD:
			if( is_float ) {
				result->float_value.value = fcml_ifn_ast_get_float_value( &lval ) + fcml_ifn_ast_get_float_value( &rval );
			} else {
				result->integer_value = fcml_ifn_ast_convert_to_val_integer( fcml_ifn_ast_get_integer_value( &lval ) + fcml_ifn_ast_get_integer_value( &rval ) );
			}
			break;
		case FCML_EN_EXN_MUL:
			if( is_float ) {
				result->float_value.value = fcml_ifn_ast_get_float_value( &lval ) * fcml_ifn_ast_get_float_value( &rval );
			} else {
				result->integer_value = fcml_ifn_ast_convert_to_val_integer( fcml_ifn_ast_get_integer_value( &lval ) * fcml_ifn_ast_get_integer_value( &rval ) );
			}
			break;
		case FCML_EN_EXN_DIV:
			if( is_float ) {
				result->float_value.value = fcml_ifn_ast_get_float_value( &lval ) / fcml_ifn_ast_get_float_value( &rval );
			} else {
				fcml_int64_t divisor = fcml_ifn_ast_get_integer_value( &rval );
				if( divisor == 0 ) {
					if( fcml_fn_ceh_add_error( error_container, "Division by zero.", FCML_EN_APC_AST_ERROR_UNSUPPORTED_NODE_IN_EXPRESSION, FCML_EN_CEH_EL_ERROR ) ) {
						error = FCML_CEH_GEC_DATA_ERROR;
					} else {
						error = FCML_CEH_GEC_OUT_OF_MEMORY;
					}
				} else {
					result->integer_value = fcml_ifn_ast_convert_to_val_integer( fcml_ifn_ast_get_integer_value( &lval ) / divisor );
				}
			}
			break;
		}
		break;
	}
	default:
		if( fcml_fn_ceh_add_error( error_container, "Unsupported node in expression.", FCML_EN_APC_AST_ERROR_UNSUPPORTED_NODE_IN_EXPRESSION, FCML_EN_CEH_EL_ERROR ) ) {
			error = FCML_CEH_GEC_INTERNAL_BUG;
		} else {
			error = FCML_CEH_GEC_OUT_OF_MEMORY;
		}
		break;
	}

	return error;
}

fcml_ceh_error fcml_ifn_ast_util_convert_value_to_immediate( fcml_st_ast_node_value *value, fcml_st_immediate *immediate ) {
	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
	immediate->is_signed = FCML_FALSE;
	if( value->type == FCML_EN_ET_FLOAT ) {
		fcml_uint32_t ieee754float = *((uint32_t*)&(value->float_value.value));
		immediate->imm32 = ieee754float;
		immediate->imm_size = FCML_DS_32;
	} else if( value->type == FCML_EN_ET_INTEGER ) {
		fcml_uint64_t imm = value->integer_value.value;
		fcml_bool is_signed = value->integer_value.is_signed;
		if( is_signed ) {
			// Optimized for 32 bit processors.
			if( ( imm & 0xFFFFFFFF80000000UL ) == 0xFFFFFFFF80000000UL || ( imm & 0xFFFFFFFF00000000UL ) == 0x0000000000000000UL ) {
				fcml_int32_t s_imm = (fcml_int32_t)imm;
				if( ( s_imm & 0xFFFFFF80 ) == 0xFFFFFF80 || ( s_imm & 0xFFFFFF00 ) == 0x00000000 ) {
					immediate->imm8 = (fcml_uint8_t)(fcml_int8_t)s_imm;
					immediate->imm_size = FCML_DS_8;
				} else if( ( s_imm & 0xFFFF8000 ) == 0xFFFF8000 || ( s_imm & 0xFFFF0000 ) == 0x00000000 ) {
					immediate->imm16 = (fcml_uint16_t)(fcml_int16_t)s_imm;
					immediate->imm_size = FCML_DS_16;
				} else {
					immediate->imm32 = (fcml_uint32_t)(fcml_int32_t)s_imm;
					immediate->imm_size = FCML_DS_32;
				}
			} else {
				immediate->imm64 = imm;
				immediate->imm_size = FCML_DS_64;
			}
			immediate->is_signed = FCML_TRUE;
		} else {
			if( imm <= FCML_UINT8_MAX ) {
				immediate->imm8 = (fcml_uint8_t)imm;
				immediate->imm_size = FCML_DS_8;
			} else if( imm <= FCML_UINT16_MAX ) {
				immediate->imm16 = (fcml_uint16_t)imm;
				immediate->imm_size = FCML_DS_16;
			} else if( imm <= FCML_UINT32_MAX ) {
				immediate->imm32 = (fcml_uint32_t)imm;
				immediate->imm_size = FCML_DS_32;
			} else {
				immediate->imm64 = imm;
				immediate->imm_size = FCML_DS_64;
			}
		}

	} else {
		// Unknown value type.
		error = FCML_CEH_GEC_INTERNAL_BUG;
	}
	return error;
}

fcml_ceh_error fcml_ifn_ast_util_convert_far_pointer_node_to_operand( fcml_st_ast_node_far_pointer *far_pointer_node, fcml_st_far_pointer *far_pointer_operand, fcml_st_ceh_error_container *error_container ) {

    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
	fcml_st_ast_node *segment_selector_node = far_pointer_node->segment_selector;
	fcml_st_ast_node *offset_node = far_pointer_node->offset;
	fcml_st_ast_node_value segment_selector_value;
	fcml_st_ast_node_value offset_value;

	// Evaluate expressions.

	if( ( error = fcml_ifn_ast_eval_exp( segment_selector_node, error_container, &segment_selector_value ) ) ) {
		return error;
	}

	if( ( error = fcml_ifn_ast_eval_exp( offset_node, error_container, &offset_value ) ) ) {
		return error;
	}

	// Segment selector and offset have to be integers.
	if( segment_selector_value.type != FCML_EN_ET_INTEGER || offset_value.type != FCML_EN_ET_INTEGER ) {
		// Only integer values are supported here.
		if( !fcml_fn_ceh_add_error( error_container, "Segment selector and offset have to be an integer values.", FCML_EN_APC_AST_ERROR_WRONG_VALUE_FORMAT, FCML_EN_CEH_EL_ERROR ) ) {
			error = FCML_CEH_GEC_OUT_OF_MEMORY;
		} else {
			error = FCML_CEH_GEC_DATA_ERROR;
		}
		return error;
	}

	// Set segment selector.
	fcml_bool overflow = FCML_FALSE;

	if( segment_selector_value.integer_value.is_signed ) {
	    fcml_int64_t segment = (fcml_int64_t)segment_selector_value.integer_value.value;
	    if( segment <= FCML_INT16_MAX && segment >= FCML_INT16_MIN ) {
            far_pointer_operand->segment = (fcml_int16_t)segment;
        } else {
            overflow = FCML_TRUE;
        }
	} else {
        if( segment_selector_value.integer_value.value <= FCML_UINT16_MAX ) {
            far_pointer_operand->segment = (fcml_uint16_t)segment_selector_value.integer_value.value;
        } else {
            overflow = FCML_TRUE;
        }
	}

	if( overflow ) {
	    if( !fcml_fn_ceh_add_error( error_container, "Segment selector out of range.", FCML_EN_APC_AST_ERROR_VALUE_OUT_OF_RANGE, FCML_EN_CEH_EL_ERROR ) ) {
            error = FCML_CEH_GEC_OUT_OF_MEMORY;
        } else {
            error = FCML_CEH_GEC_VALUE_OUT_OF_RANGE;
        }
        return error;
	}

	// Set offset.
	if( offset_value.integer_value.is_signed ) {
	    fcml_int64_t offset = (fcml_int64_t)offset_value.integer_value.value;
	    if( offset <= FCML_INT16_MAX && offset >= FCML_INT16_MIN ) {
	        far_pointer_operand->offset16 = (fcml_int16_t)offset;
            far_pointer_operand->offset_size = FCML_DS_16;
	    } else if( offset <= FCML_INT32_MAX && offset >= FCML_INT32_MIN ) {
            far_pointer_operand->offset32 = (fcml_int32_t)offset;
            far_pointer_operand->offset_size = FCML_DS_32;
        } else {
            overflow = FCML_TRUE;
	    }
	} else {
	    fcml_uint64_t offset = offset_value.integer_value.value;
        if( offset <= FCML_UINT16_MAX ) {
            far_pointer_operand->offset16 = (fcml_uint16_t)offset_value.integer_value.value;
            far_pointer_operand->offset_size = FCML_DS_16;
        } else if( offset <= FCML_UINT32_MAX ) {
            far_pointer_operand->offset32 = (fcml_uint32_t)offset_value.integer_value.value;
            far_pointer_operand->offset_size = FCML_DS_32;
        } else {
            overflow = FCML_TRUE;
        }
	}

	if( overflow ) {
        if( !fcml_fn_ceh_add_error( error_container, "Offset out of range.", FCML_EN_APC_AST_ERROR_VALUE_OUT_OF_RANGE, FCML_EN_CEH_EL_ERROR ) ) {
            error = FCML_CEH_GEC_OUT_OF_MEMORY;
        } else {
            error = FCML_CEH_GEC_VALUE_OUT_OF_RANGE;
        }
    }

	return error;
}

fcml_ceh_error fcml_ifn_ast_util_convert_effective_address_node_to_operand( fcml_st_ast_node_effective_address *effective_address_node, fcml_en_effective_address_form address_form, fcml_st_operand *operand, fcml_st_ceh_error_container *error_container ) {

    fcml_st_address *address = &(operand->address);

    operand->hints |= effective_address_node->addressing_hints;

    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

	fcml_st_effective_address *effective_address = &(address->effective_address);

	fcml_bool is_combined = !( fcml_fn_utils_is_reg_undef( &(effective_address_node->base) ) && fcml_fn_utils_is_reg_undef( &(effective_address_node->index) ) );

    address->address_form = is_combined ? FCML_AF_COMBINED : FCML_AF_OFFSET;

	// Evaluate displacement.
	if( effective_address_node->displacement != NULL ) {

		fcml_st_ast_node_value value;

		if( ( error = fcml_ifn_ast_eval_exp( effective_address_node->displacement, error_container, &value ) ) ) {
			return error;
		}

		if( value.type != FCML_EN_ET_INTEGER ) {
			if( !fcml_fn_ceh_add_error( error_container, "Displacement has to be an integer value.", FCML_EN_APC_AST_ERROR_WRONG_VALUE_FORMAT, FCML_EN_CEH_EL_ERROR ) ) {
				error = FCML_CEH_GEC_OUT_OF_MEMORY;
			} else {
				error = FCML_CEH_GEC_DATA_ERROR;
			}
			return error;
		}

		fcml_st_integer disp_value;

		error = fcml_fn_utils_int64_to_integer( value.integer_value.value, value.integer_value.is_signed, &disp_value, is_combined ? FCML_ENUSF_ALL : ( FCML_ENUSF_16 | FCML_ENUSF_32 | FCML_ENUSF_64 ) );
		if( error ) {
		    return error;
		}

		if( is_combined ) {
            error = fcml_fn_utils_integer_to_displacement( &disp_value, &(effective_address->displacement ) );
            if( error ) {
                return error;
            }
		} else {
		    error = fcml_fn_utils_integer_to_offset( &disp_value, &(address->offset ) );
            if( error ) {
                return error;
            }
		}

	}

	if( is_combined ) {

        effective_address->base = effective_address_node->base;
        effective_address->index = effective_address_node->index;

        fcml_uint32_t scale_factor = effective_address_node->scale_factor.value;
        if( (scale_factor == 0 || scale_factor == 1 || scale_factor == 2 || scale_factor == 4 || scale_factor == 8 ) ) {
            effective_address->scale_factor = (fcml_uint8_t)scale_factor;
        } else {
            if( !fcml_fn_ceh_add_error( error_container, "Wrong scale factor value.", FCML_EN_APC_AST_ERROR_WRONG_VALUE_FORMAT, FCML_EN_CEH_EL_ERROR ) ) {
                error = FCML_CEH_GEC_OUT_OF_MEMORY;
            } else {
                error = FCML_CEH_GEC_DATA_ERROR;
            }
            return error;
        }

	}

	address->segment_selector.segment_selector = effective_address_node->segment_selector;
	address->size_operator = effective_address_node->size_operator;

	return error;
}

fcml_ceh_error fcml_ifn_ast_handle_ast_node( fcml_st_instruction *cif_instruction, fcml_st_operand *current_operand, fcml_st_ast_node *ast_node, fcml_st_ceh_error_container *error_container ) {
	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
	switch( ast_node->type ) {
		case FCML_EN_TN_INSTRUCTION: {
			fcml_st_ast_node_instruction *node_instruction = (fcml_st_ast_node_instruction*)ast_node->node;
			// Handle mnemonic.
			cif_instruction->prefixes = node_instruction->prefixes;
			cif_instruction->hints = node_instruction->hints;
			cif_instruction->mnemonic = fcml_fn_env_str_strdup( node_instruction->mnemonic );
			// Handle operands.
			if( node_instruction->operands ) {
				error = fcml_ifn_ast_handle_ast_node( cif_instruction, NULL, node_instruction->operands, error_container );
			}
			break;
		}
		case FCML_EN_TN_OPERAND_LIST: {
			fcml_st_ast_node_operand_list *operand_list = (fcml_st_ast_node_operand_list*)ast_node->node;
			if( operand_list->operands->size > FCML_OPERANDS_COUNT ) {
				if( !fcml_fn_ceh_add_error( error_container, "To many operands.", FCML_EN_APC_AST_ERROR_TO_MANY_OPERANDS, FCML_EN_CEH_EL_ERROR ) ) {
					error = FCML_CEH_GEC_OUT_OF_MEMORY;
				} else {
					error = FCML_CEH_GEC_DATA_ERROR;
				}
			} else {
				fcml_st_coll_list_element *current = operand_list->operands->head;
				int i = 0;
				while( current && i < FCML_OPERANDS_COUNT ) {
					error = fcml_ifn_ast_handle_ast_node( cif_instruction, &(cif_instruction->operands[i++]), (fcml_st_ast_node*)current->item, error_container );
					if( error ) {
						return error;
					}
					current = current->next;
				}
			}
			break;
		}
		case FCML_EN_TN_EXP:
		case FCML_EN_TN_VALUE:
		case FCML_EN_TN_UMINUS: {
			fcml_st_ast_node_value value;
			error = fcml_ifn_ast_eval_exp( ast_node, error_container, &value );
			if( !error ) {
				if( current_operand != NULL ) {
					// Convert value to immediate operand.
					error = fcml_ifn_ast_util_convert_value_to_immediate( &value, &(current_operand->immediate) );
					if( !error ) {
						current_operand->type = FCML_EOT_IMMEDIATE;
					}
				} else {
					// Operand is mandatory here.
					error = FCML_CEH_GEC_INTERNAL_BUG;
				}
			}
			break;
		}
		case FCML_EN_TN_REG: {
			fcml_st_ast_node_register *node_register = (fcml_st_ast_node_register*)ast_node->node;
			current_operand->reg = node_register->reg;
			current_operand->type = FCML_EOT_REGISTER;
			break;
		}
		case FCML_EN_TN_FAR_POINTER: {
			fcml_st_ast_node_far_pointer *far_pointer_node = (fcml_st_ast_node_far_pointer*)ast_node->node;
			error = fcml_ifn_ast_util_convert_far_pointer_node_to_operand( far_pointer_node, &(current_operand->far_pointer), error_container );
			current_operand->type = FCML_EOT_FAR_POINTER;
			break;
		}
		case FCML_EN_TN_EFFECTIVE_ADDRESS: {
			fcml_st_ast_node_effective_address *effective_address_node = (fcml_st_ast_node_effective_address*)ast_node->node;
			error = fcml_ifn_ast_util_convert_effective_address_node_to_operand( effective_address_node, effective_address_node->address_form, current_operand, error_container );
			current_operand->type = FCML_EOT_ADDRESS;
			break;
		}
		default:
			break;
	}
	return error;

}

