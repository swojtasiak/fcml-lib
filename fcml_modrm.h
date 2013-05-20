/*
 * fcml_modrm.h
 *
 *  Created on: 19-05-2013
 *      Author: tAs
 */

#ifndef FCML_MODRM_H_
#define FCML_MODRM_H_

#include "fcml_common.h"

typedef enum fcml_en_modrm_addr_form {
	FCML_MODRM_AF_16_BIT,
	FCML_MODRM_AF_32_BIT
} fcml_en_modrm_addr_form;

typedef struct fcml_st_encoded_modrm {
	fcml_uint8_t modrm;
	fcml_nuint8_t sib;
	fcml_uint8_t ext_reg;
	fcml_uint8_t ext_rm;
} fcml_st_encoded_modrm;

typedef struct fcml_st_modrm {
	// Register number specified by reg_opcode.
	fcml_nuint8_t reg_opcode;
	// Register number specified by r/m when mod == 3.
	fcml_nuint8_t reg;
	// Base register.
	fcml_st_register base;
	// Index register.
	fcml_st_register index;
	// Scale factor (SIB only)
	fcml_uint8_t scale_factor;
	// Displacement.
	fcml_st_displacement displacement;
} fcml_st_modrm;

typedef struct fcml_st_modrm_context {
	fcml_en_modrm_addr_form addr_form;
	fcml_esa eosa;
	fcml_esa easa;
} fcml_st_modrm_context;

#endif /* FCML_MODRM_H_ */
