/*
 * fcml_putils.c
 *
 *  Created on: 03-03-2013
 *      Author: tAs
 */

#include "fcml_parser_utils.h"

#include "fcml_x64intel_parser.tab.h"

#include <stdlib.h>
#include <errno.h>

int fcml_fn_pu_parse_integer( const fcml_char *str, fcml_st_ast_val_integer *integer_value, int base ) {
	uint64_t value = strtoull( str, NULL, base );
	if( errno == ERANGE ) {
		integer_value->overflow = FCML_TRUE;
	}
	integer_value->value = value;
	integer_value->is_signed = FCML_FALSE;
	return FCML_TK_INTEGER;
}

int fcml_fn_pu_parse_float( const fcml_char *str, fcml_st_ast_val_float *float_value ) {
	float_value->value = strtof( str, NULL );
	float_value->overflow = ( errno == ERANGE ) ? FCML_TRUE : FCML_FALSE;
	return FCML_TK_FLOAT;
}

int fcml_fn_pu_parse_register( fcml_en_register type, fcml_data_size size, fcml_uint8_t reg, fcml_bool x64_exp, fcml_st_register *reg_dest ) {
	int token = 0;
	reg_dest->type = type;
	reg_dest->size = size;
	reg_dest->reg = reg;
	reg_dest->x64_exp = x64_exp;
	switch(type) {
	case FCML_REG_GPR:
		token = FCML_TK_REG_GPR;
		break;
	case FCML_REG_SIMD:
		token = FCML_TK_REG_SIMD;
		break;
	case FCML_REG_FPU:
		token = FCML_TK_REG_FPU;
		break;
	case FCML_REG_SEG:
		token = FCML_TK_REG_SEG;
		break;
	case FCML_REG_DR:
		token = FCML_TK_REG_DR;
		break;
	case FCML_REG_CR:
		token = FCML_TK_REG_CR;
		break;
	default:
		// Unexpected register type is treated as unexpected token,
		// anyway it should never happened.
		token = FCML_TK_UNEXPECTED;
		break;
	}
	return token;
}

fcml_char *fcml_fn_pu_reg_type_to_string( fcml_en_register type ) {
	fcml_char *desc;
	switch(type) {
	case FCML_REG_GPR:
		desc = "GPR";
		break;
	case FCML_REG_SIMD:
		desc = "SIMD";
		break;
	case FCML_REG_FPU:
		desc = "FPU";
		break;
	case FCML_REG_SEG:
		desc = "SEG";
		break;
	case FCML_REG_DR:
		desc = "DR";
		break;
	case FCML_REG_CR:
		desc = "CR";
		break;
	default:
		desc = "Unknown";
		break;
	}
	return desc;
}
