/*
 * fcml_common_lex.h
 *
 *  Created on: Nov 16, 2013
 *      Author: tas
 */

#ifndef FCML_COMMON_LEX_H_
#define FCML_COMMON_LEX_H_

#include "fcml_common.h"
#include "fcml_env.h"
#include "fcml_types.h"
#include "fcml_parser_utils.h"

/*GPR*/
#define FCML_FM_GPRS_8_REG(x)	fcml_fn_pu_parse_register( FCML_REG_GPR, FCML_DS_8, x, FCML_FALSE, &(yylval->reg_value) )
#define FCML_FM_GPRS_8_X_REG(x)	fcml_fn_pu_parse_register( FCML_REG_GPR, FCML_DS_8, x, FCML_TRUE, &(yylval->reg_value) )
#define FCML_FM_GPRS_16_REG(x)	fcml_fn_pu_parse_register( FCML_REG_GPR, FCML_DS_16, x, FCML_FALSE, &(yylval->reg_value) )
#define FCML_FM_GPRS_32_REG(x)	fcml_fn_pu_parse_register( FCML_REG_GPR, FCML_DS_32, x, FCML_FALSE, &(yylval->reg_value) )
#define FCML_FM_GPRS_64_REG(x)	fcml_fn_pu_parse_register( FCML_REG_GPR, FCML_DS_64, x, FCML_FALSE, &(yylval->reg_value) )
/*SIMD*/
#define FCML_FM_SIMD_64_REG(x)	fcml_fn_pu_parse_register( FCML_REG_SIMD, FCML_DS_64, x, FCML_FALSE, &(yylval->reg_value) )
#define FCML_FM_SIMD_128_REG(x)	fcml_fn_pu_parse_register( FCML_REG_SIMD, FCML_DS_128, x, FCML_FALSE, &(yylval->reg_value) )
#define FCML_FM_SIMD_256_REG(x)	fcml_fn_pu_parse_register( FCML_REG_SIMD, FCML_DS_256, x, FCML_FALSE, &(yylval->reg_value) )
/*FPU*/
#define FCML_FM_FPU_REG(x)		fcml_fn_pu_parse_register( FCML_REG_FPU, FCML_DS_UNDEF, x, FCML_FALSE, &(yylval->reg_value) )
/*Control registers.*/
#define FCML_FM_CR_REG(x)		fcml_fn_pu_parse_register( FCML_REG_CR, FCML_DS_UNDEF, x, FCML_FALSE, &(yylval->reg_value) )
/*Debug registers.*/
#define FCML_FM_DR_REG(x)		fcml_fn_pu_parse_register( FCML_REG_DR, FCML_DS_UNDEF, x, FCML_FALSE, &(yylval->reg_value) )
/*Segment registers.*/
#define FCML_FM_SEG_REG(x)		fcml_fn_pu_parse_register( FCML_REG_SEG, FCML_DS_UNDEF, x, FCML_FALSE, &(yylval->reg_value) )
/*Size operands.*/
#define FCML_FM_SIZE_OPERAND(x) { yylval->size_operator.size = x; yylval->size_operator.multimedia = FCML_FALSE; return FCML_TK_SIZE_OPERATOR;  }
#define FCML_FM_MULTIMEDIA_SIZE_OPERAND(x) { yylval->size_operator.size = x; yylval->size_operator.multimedia = FCML_TRUE; return FCML_TK_SIZE_OPERATOR; }

#endif /* FCML_COMMON_LEX_H_ */
