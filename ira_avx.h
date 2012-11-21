/*
 * ira_avx.h
 *
 *  Created on: 18-11-2012
 *      Author: Slawomir Wojtasiak
 */

#ifndef IRA_AVX_H_
#define IRA_AVX_H_

#include "ira_int.h"

uint8_t *_ira_avx_decode_escape_opcode_bytes( struct ira_decoding_context *decoding_context, uint8_t *number_of_opcode_bytes );
void _ira_avx_free_escape_opcode_bytes( uint8_t *escape_opcode_bytes );

#endif /* IRA_AVX_H_ */
