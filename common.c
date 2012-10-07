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

// Description in common.h
enum ira_register_type _ira_common_decode_gpr_type( uint16_t operand_size ) {
	enum ira_register_type reg_type = IRA_REG_GPR;
	switch( operand_size ) {
	case _IRA_OS_BYTE:
		reg_type = IRA_REG_GPR_8;
		break;
	case _IRA_OS_WORD:
		reg_type = IRA_REG_GPR_16;
		break;
	case _IRA_OS_DWORD:
		reg_type = IRA_REG_GPR_32;
		break;
	case _IRA_OS_QWORD:
		reg_type = IRA_REG_GPR_64;
		break;
	}
	return reg_type;
}
