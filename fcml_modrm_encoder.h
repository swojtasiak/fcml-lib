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

fcml_ceh_error fcml_fn_modrm_encode( fcml_st_modrm_context *context, const fcml_st_modrm *decoded_modrm, fcml_st_encoded_modrm *encoded_modrm );
fcml_ceh_error fcml_fn_modrm_calculate_efective_address_size( const fcml_st_modrm *decoded_modrm, fcml_esa *effective_address_size );

#endif /* FCML_MODRM_ENCODER_H_ */
