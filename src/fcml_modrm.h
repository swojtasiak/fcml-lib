/*
 * fcml_modrm.h
 *
 *  Created on: 19-05-2013
 *      Author: tAs
 */

#ifndef FCML_MODRM_H_
#define FCML_MODRM_H_

#include "fcml_common.h"
#include "fcml_types.h"

typedef struct fcml_st_modrm {
	// Register number specified by reg_opcode.
	fcml_uint8_t reg_opcode;
	// True if register needs REX prefix to be encoded.
	fcml_bool reg_opcode_needs_rex;
	// Register number specified by r/m when mod == 3.
	fcml_nuint8_t reg;
	// Effective address.
	fcml_st_address address;
	// True if RIP encoding is used.
	fcml_bool is_rip;
} fcml_st_modrm;

#endif /* FCML_MODRM_H_ */
