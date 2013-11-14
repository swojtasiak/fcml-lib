/*
 * fcml_putils.h
 *
 *  Created on: 03-03-2013
 *      Author: tAs
 */

#ifndef FCML_PUTILS_H_
#define FCML_PUTILS_H_

#include "fcml_parser_data.h"

int fcml_fn_pu_parse_integer( const fcml_char *str, fcml_st_ast_val_integer *integer_value, int base );
int fcml_fn_pu_parse_float( const fcml_char *str, fcml_st_ast_val_float *float_value );
int fcml_fn_pu_parse_register( fcml_en_register type, fcml_data_size size, fcml_uint8_t num, fcml_bool x64_exp, fcml_st_register *reg_dest );
fcml_char *fcml_fn_pu_reg_type_to_string( fcml_en_register type );

#endif /* FCML_PUTILS_H_ */
