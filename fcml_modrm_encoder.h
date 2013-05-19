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

fcml_ceh_error fcml_fn_modrm_encode( fcml_st_modrm_context context, const fcml_st_modrm *decoded_modrm, fcml_st_encoded_modrm *encoded_modrm );

#endif /* FCML_MODRM_ENCODER_H_ */
