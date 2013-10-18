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
#include "fcml_stream.h"

// Effective size attribute ata type.

typedef fcml_uint8_t fcml_esa;

#define FCML_ESA_SF_16		0x01
#define FCML_ESA_SF_32		0x02
#define FCML_ESA_SF_64		0x04

typedef struct fcml_st_modrm_source {
	fcml_uint8_t ext_r;
	fcml_uint8_t ext_x;
	fcml_uint8_t ext_b;
	fcml_bool is_vsib;
	fcml_usize vsib_index_size;
	fcml_st_memory_stream *stream;
} fcml_st_modrm_source;

typedef struct fcml_st_encoded_modrm {
	fcml_uint8_t modrm;
	fcml_nuint8_t sib;
	fcml_uint8_t ext_r;
	fcml_uint8_t ext_x;
	fcml_uint8_t ext_b;
	fcml_uint8_t displacement[4];
	fcml_uint8_t displacement_size;
	fcml_bool is_rip;
	fcml_int64_t rip_address;
} fcml_st_encoded_modrm;

typedef struct fcml_st_modrm {
	// Register number specified by reg_opcode.
	fcml_uint8_t reg_opcode;
	// True if register needs REX prefix to be encoded.
	fcml_bool reg_opcode_needs_rex;
	// Register number specified by r/m when mod == 3.
	fcml_nuint8_t reg;
	// Effective address.
	fcml_st_address address;
} fcml_st_modrm;

fcml_ceh_error fcml_fn_modrm_write_encoded_modrm( fcml_st_encoded_modrm *encoded_modrm, fcml_st_memory_stream *stream );

#endif /* FCML_MODRM_H_ */
