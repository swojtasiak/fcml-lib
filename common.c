/*
 * common.c
 *
 *  Created on: 07-10-2012
 *      Author: Slawomir Wojtasiak
 */

#include "common.h"

// Description in common.h
uint16_t _ira_common_decode_8b_operand_size( uint8_t encoded_operand_size ) {

	if( encoded_operand_size == _IRA_EOS_EASA ) {
		return _IRA_OS_EASA;
	}

	if( encoded_operand_size == _IRA_EOS_EOSA ) {
		return _IRA_OS_EOSA;
	}

	return encoded_operand_size * 8;
}
