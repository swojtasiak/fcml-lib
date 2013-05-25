/*
 * fcml_modrm.h
 *
 *  Created on: 19-05-2013
 *      Author: tAs
 */

#ifndef FCML_MODRM_H_
#define FCML_MODRM_H_

#include "fcml_errors.h"
#include "fcml_common.h"

// Effective size attribute ata type.

typedef fcml_uint8_t fcml_esa;

#define FCML_ESA_SF_16		0x01
#define FCML_ESA_SF_32		0x02
#define FCML_ESA_SF_64		0x04

typedef enum fcml_en_modrm_addr_form {
	FCML_MODRM_AF_16_BIT,
	FCML_MODRM_AF_32_BIT
} fcml_en_modrm_addr_form;

typedef struct fcml_st_encoded_modrm {
	fcml_uint8_t modrm;
	fcml_nuint8_t sib;
	fcml_uint8_t ext_reg;
	fcml_uint8_t ext_rm;
	fcml_uint8_t displacement[4];
	fcml_uint8_t displacement_size;
} fcml_st_encoded_modrm;

typedef struct fcml_st_modrm {
	// Register number specified by reg_opcode.
	fcml_uint8_t reg_opcode;
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
	// Sets 32 or 64 bit addressing mode.
	fcml_en_modrm_addr_form addr_form;
	// Effective addres size using to decode/encode ModR/M. It's very important to set this value properly,
	// because 16 and 32/64 addressing forms
	fcml_esa effective_address_size;
	// True if VSIB encoding is available. This flag should be only set for ModR/M
	// decoder to made it use SIMD register as index register. In case of encoder,
	// we really don't care if it's SIMD index register or not, because encoding
	// is similar to GPR index.
	fcml_bool is_vsib;
} fcml_st_modrm_context;

#endif /* FCML_MODRM_H_ */
