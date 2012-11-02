/*
 * common.h
 *
 *  Created on: 07-10-2012
 *      Author: Slawomir Wojtasiak
 */

#ifndef COMMON_H_
#define COMMON_H_

#include <inttypes.h>

#include "ira.h"

/* Constants. */

// Operand size calculated by Effective Operand Size Attribute and Effective Address Size Attribute.

//TODO: Zunifikowac zapis wielkosci obliczanych na bazie EASA i EOSA, wykorzytac te stale

#define _IRA_OS_EOSA		0xFFFF
#define _IRA_OS_EASA		0xFFFE

/* Constants used to encode operand size on one byte. Used only in instruction descriptions. */

// Operand size calculated by Effective Operand Size Attribute and Effective Address Size Attribute.
#define _IRA_EOS_EOSA		0xFF
#define _IRA_EOS_EASA		0xFE

// Take into account that every size is given in a number of bytes.
#define _IRA_EOS_UNDEFINED	0
#define _IRA_EOS_BYTE		1
#define _IRA_EOS_WORD		2
#define _IRA_EOS_DWORD		4
#define _IRA_EOS_FWORD		6
#define _IRA_EOS_QWORD		8
#define _IRA_EOS_MMWORD		8
#define _IRA_EOS_TBYTE		10
#define _IRA_EOS_OWORD		16
#define _IRA_EOS_XMMWORD	16

/* Methods. */

//! Decoding given encoded operand size.
/*!
 * \brief Decodes given operand size using provided EOSA. Some functions have operand size described on 8 bits using
 * IRA_EOS_ constants. This form of operand size description notation is used to allow encoding more than 128
 * bits operand sizes using only one byte.
 *
 * \param encoded_operand_size Size directive to decode.
 * \return Decoded operand size.
 */
uint16_t _ira_common_decode_8b_operand_size( uint8_t encoded_operand_size );

#endif /* COMMON_H_ */
