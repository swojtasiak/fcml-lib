/*
 * common.c
 *
 *  Created on: 07-10-2012
 *      Author: Slawomir Wojtasiak
 */

#include "common.h"

// Description in common.h
uint16_t _ira_common_decode_size_directive( uint8_t effective_operand_size_attribute, uint8_t effective_address_size_attribute, uint8_t encoded_operand_size ) {

	if( encoded_operand_size == _IRA_EOS_EASA ) {
		return effective_address_size_attribute;
	}

	if( encoded_operand_size == _IRA_EOS_EOSA ) {
		return effective_operand_size_attribute;
	}

	return encoded_operand_size * 8;
}
