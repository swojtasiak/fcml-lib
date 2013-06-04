/*
 * fcml_modrm_encoder.h
 *
 *  Created on: 19-05-2013
 *      Author: tAs
 */

#ifndef FCML_MODRM_ENCODER_H_
#define FCML_MODRM_ENCODER_H_

#include "fcml_ceh.h"
#include "fcml_modrm.h"

// Macros.

#define FCML_MODRM_ENC_MOD(x)				( x << 6 )
#define FCML_MODRM_ENC_REG_OPCODE(x)		( x << 3 )
#define FCML_MODRM_ENC_RM(x)				( x )
#define FCML_MODRM_ENC(mod,reg,rm)			( FCML_MODRM_ENC_MOD( mod ) | FCML_MODRM_ENC_REG_OPCODE( reg ) | FCML_MODRM_ENC_RM( rm ) )

#define FCML_MODRM_ENC_SIB_SS(x)			( x << 6 )
#define FCML_MODRM_ENC_SIB_INDEX(x)			( x << 3 )
#define FCML_MODRM_ENC_SIB_BASE(x)			( x )
#define FCML_MODRM_SIB_ENC(ss,index,base)	( FCML_MODRM_ENC_SIB_SS( ss ) | FCML_MODRM_ENC_SIB_INDEX( index ) | FCML_MODRM_ENC_SIB_BASE( base ) )

typedef struct fcml_st_modrm_encoder_context {
	// Sets 32 or 64 bit addressing mode.
	fcml_en_addr_form addr_form;
	// Prefered effective addres size that should be used to encode ModR/M.
	fcml_data_size effective_address_size;
	// Effective address size ModR/M was encoded for. For example "effective_address_size" might
	// be set to 32 bits, but [BX+SI] encoding needs 16 bit encoding.
	fcml_data_size chosen_effective_address_size;
	// This flag is set only by ModR/M encoder if there is alterative SIB encoding available,
	// but user chooses default ModR/M only encoding.
	fcml_bool is_sib_alternative;
	// This flag is used only by ModR/M encoder, and should be set to TRUE to force
	// using SIB encoding, if there is such alternative.
	fcml_bool choose_sib_encoding;
} fcml_st_modrm_encoder_context;

fcml_ceh_error fcml_fn_modrm_encode( fcml_st_modrm_encoder_context *context, const fcml_st_modrm *decoded_modrm, fcml_st_encoded_modrm *encoded_modrm );
fcml_ceh_error fcml_fn_modrm_calculate_efective_address_size( const fcml_st_modrm *decoded_modrm, fcml_esa *effective_address_size );

#endif /* FCML_MODRM_ENCODER_H_ */
