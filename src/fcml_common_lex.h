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

#ifndef FCML_COMMON_LEX_H_
#define FCML_COMMON_LEX_H_

#include <fcml_common.h>
#include <fcml_types.h>

#include "fcml_env_int.h"
#include "fcml_parser_utils.h"

/* GPR */
#define FCML_FM_GPRS_8_REG(x)       { fcml_fn_pu_parse_register(FCML_REG_GPR, \
        FCML_DS_8, x, FCML_FALSE, &(yylval->reg_value) ); \
        return FCML_TK_REG_GPR; }

#define FCML_FM_GPRS_8_X_REG(x)     { fcml_fn_pu_parse_register(FCML_REG_GPR, \
        FCML_DS_8, x, FCML_TRUE, &(yylval->reg_value) ); \
        return FCML_TK_REG_GPR; }

#define FCML_FM_GPRS_16_REG(x)      { fcml_fn_pu_parse_register(FCML_REG_GPR, \
        FCML_DS_16, x, FCML_FALSE, &(yylval->reg_value) ); \
        return FCML_TK_REG_GPR; }

#define FCML_FM_GPRS_32_REG(x)      { fcml_fn_pu_parse_register(FCML_REG_GPR, \
        FCML_DS_32, x, FCML_FALSE, &(yylval->reg_value) ); \
        return FCML_TK_REG_GPR; }

#define FCML_FM_GPRS_64_REG(x)      { fcml_fn_pu_parse_register(FCML_REG_GPR, \
        FCML_DS_64, x, FCML_FALSE, &(yylval->reg_value) ); \
        return FCML_TK_REG_GPR; }

/* SIMD */
#define FCML_FM_SIMD_64_REG(x)      { fcml_fn_pu_parse_register(FCML_REG_SIMD, \
        FCML_DS_64, x, FCML_FALSE, &(yylval->reg_value) ); \
        return FCML_TK_REG_SIMD; }

#define FCML_FM_SIMD_128_REG(x)     { fcml_fn_pu_parse_register(FCML_REG_SIMD, \
        FCML_DS_128, x, FCML_FALSE, &(yylval->reg_value) ); \
        return FCML_TK_REG_SIMD; }

#define FCML_FM_SIMD_256_REG(x)     { fcml_fn_pu_parse_register(FCML_REG_SIMD, \
        FCML_DS_256, x, FCML_FALSE, &(yylval->reg_value) ); \
        return FCML_TK_REG_SIMD; }

#define FCML_FM_SIMD_512_REG(x)     { fcml_fn_pu_parse_register(FCML_REG_SIMD, \
        FCML_DS_512, x, FCML_FALSE, &(yylval->reg_value) ); \
        return FCML_TK_REG_SIMD; }

/* FPU */
#define FCML_FM_FPU_REG(x)          { fcml_fn_pu_parse_register(FCML_REG_FPU, \
        FCML_DS_UNDEF, x, FCML_FALSE, &(yylval->reg_value) ); \
        return FCML_TK_REG_FPU; }

/* Control registers. */
#define FCML_FM_CR_REG(x)           { fcml_fn_pu_parse_register(FCML_REG_CR, \
        FCML_DS_UNDEF, x, FCML_FALSE, &(yylval->reg_value) ); \
        return FCML_TK_REG_CR; }

/* Debug registers. */
#define FCML_FM_DR_REG(x)           { fcml_fn_pu_parse_register(FCML_REG_DR, \
        FCML_DS_UNDEF, x, FCML_FALSE, &(yylval->reg_value) ); \
        return FCML_TK_REG_DR; }

/* Segment registers. */
#define FCML_FM_SEG_REG(x)          { fcml_fn_pu_parse_register(FCML_REG_SEG, \
        FCML_DS_UNDEF, x, FCML_FALSE, &(yylval->reg_value) ); \
        return FCML_TK_REG_SEG; }

/* Opmask registers. */
#define FCML_FM_OPMASK_REG(x)    { fcml_fn_pu_parse_register(FCML_REG_OPMASK, \
        FCML_DS_64, x, FCML_FALSE, &(yylval->reg_value) ); \
        return FCML_TK_REG_OPMASK; }

/* RIP */
#define FCML_FM_RIP                 { fcml_fn_pu_parse_register(FCML_REG_IP, \
        FCML_DS_64, FCML_REG_UNDEFINED, FCML_FALSE, &(yylval->reg_value) ); \
        return FCML_TK_REG_RIP; }

/* AVX-512 Broadcast. */
#define FCML_FM_BCAST_DECORATOR(x)     { yylval->int_value = x; \
    return FCML_TK_DECORATOR_BCAST; }

/* AVX-512 Embedded rounding. */
#define FCML_FM_ER_DECORATOR(x)     { yylval->int_value = x; \
    return FCML_TK_DECORATOR_ER; }

/* AVX-512 Opmask registers decorators. */
#define FCML_FM_OPMASK_REG_DECORATOR(x)    { \
    fcml_fn_pu_parse_register(FCML_REG_OPMASK, \
            FCML_DS_64, x, FCML_FALSE, &(yylval->reg_value) ); \
            return FCML_TK_OPMASK_REG_DECORATOR; }

#define YY_USER_ACTION \
    yylloc->first_line = yylloc->last_line; \
    yylloc->first_column = yylloc->last_column; \
    for(int i = 0; yytext[i] != '\0'; i++) { \
        if(yytext[i] == '\n') { \
            yylloc->last_line++; \
            yylloc->last_column = 0; \
        } \
        else { \
            yylloc->last_column++; \
        } \
    }

#endif /* FCML_COMMON_LEX_H_ */
