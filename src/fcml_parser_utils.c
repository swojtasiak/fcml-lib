/*
 * FCML - Free Code Manipulation Library.
 * Copyright (C) 2010-2020 Slawomir Wojtasiak
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include "fcml_parser_utils.h"

#include <stdlib.h>
#include <errno.h>

void fcml_fn_pu_parse_integer(const fcml_char *str,
        fcml_st_ast_val_integer *integer_value, int base) {
#ifdef FCML_MSCC
    fcml_uint64_t value = _strtoui64( str, NULL, base );
#else
    fcml_uint64_t value = strtoull(str, NULL, base);
#endif
    integer_value->overflow = ( errno == ERANGE);
    integer_value->value = value;
    integer_value->is_signed = FCML_FALSE;
}

void fcml_fn_pu_parse_float(const fcml_char *str,
        fcml_st_ast_val_float *float_value) {
    // Floats are not supported yet.
#ifdef FCML_MSCC
    float_value->value = (float)strtod( str, NULL );
#else
    float_value->value = strtof(str, NULL);
#endif
    float_value->overflow = ( errno == ERANGE) ? FCML_TRUE : FCML_FALSE;
}

void fcml_fn_pu_parse_register(fcml_en_register type, fcml_usize size,
        fcml_uint8_t reg, fcml_bool x64_exp, fcml_st_register *reg_dest) {
    reg_dest->type = type;
    reg_dest->size = size;
    reg_dest->reg = reg;
    reg_dest->x64_exp = x64_exp;
}

fcml_char* fcml_fn_pu_reg_type_to_string(fcml_en_register type) {
    fcml_char *desc;
    switch (type) {
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

