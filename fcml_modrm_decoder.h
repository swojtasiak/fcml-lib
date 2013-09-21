/*
 * fcml_modrm_decoder.h
 *
 *  Created on: 19-05-2013
 *      Author: tAs
 */

#ifndef FCML_MODRM_DECODER_H_
#define FCML_MODRM_DECODER_H_

#include "fcml_ceh.h"
#include "fcml_modrm.h"

// Macros.

#define FCML_MODRM_DEC_MOD(x)			( x >> 6 )
#define FCML_MODRM_DEC_REG_OPCODE(x)	( ( x & 0x38 ) >> 3 )
#define FCML_MODRM_DEC_RM(x)			( x & 0x07 )

#define FCML_MODRM_SIB_SS(x)			( x >> 6 )
#define FCML_MODRM_SIB_INDEX(x)			( ( x & 0x38 ) >> 3 )
#define FCML_MODRM_SIB_BASE(x)			( x & 0x07 )

typedef struct fcml_st_modrm_decoder_context {
	// Sets 32 or 64 bit addressing mode.
	fcml_en_addr_form addr_form;
	// Effective address size using to decode/encode ModR/M. It's very important to set this value properly,
	// because 16 and 32/64 addressing forms
	fcml_data_size effective_address_size;
	// True if VSIB encoding is available. This flag should be only set for ModR/M
	// decoder to made it use SIMD register as index register. In case of encoder,
	// we really don't care if it's SIMD index register or not, because encoding
	// is similar to GPR index.
	fcml_bool is_vsib;
	// This flag is set only by ModR/M encoder if there is alterative SIB encoding available,
	// but user chooses default ModR/M only encoding.
	fcml_bool is_sib_alternative;
	// This flag is used only by ModR/M encoder, and should be set to TRUE to force
	// using SIB encoding, if there is such alternative.
	fcml_bool choose_sib_encoding;
	// True if displacement should be used to calculate RIP-relative effective address.
	fcml_bool is_rip;
} fcml_st_modrm_decoder_context;

fcml_ceh_error fcml_fn_modrm_decode( fcml_st_modrm_decoder_context *context, fcml_st_modrm_source *modrm_source, fcml_st_modrm *decoded_modrm );
fcml_ceh_error fcml_fn_modrm_decode_rip( fcml_uint64_t rip, fcml_data_size effective_address_size, fcml_st_offset *offset, fcml_st_offset *address );

#endif /* FCML_MODRM_DECODER_H_ */
