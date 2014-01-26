/*
 * fcml_messages.h
 *
 *  Created on: Nov 10, 2013
 *      Author: tas
 */

#ifndef FCML_MESSAGES_H_
#define FCML_MESSAGES_H_

#include "fcml_types.h"

typedef enum fcml_en_msg_message_code {
	FCML_MC_INVALID_OPERAND,
	FCML_MC_SEGMENT_REGISTER_CAN_NOT_BE_OVERRIDDEN,
	FCML_MC_SEGMENT_INVALID_PSEUDO_OPCODE_IMM,
	FCML_MC_SEGMENT_HLE_PREFIXES_NOT_ALLOWED,
	FCML_MC_SEGMENT_HLE_MORE_THAN_ONE_PREFIX,
	FCML_MC_SEGMENT_WRONG_REGISTER_TYPE_SEG
} fcml_en_msg_message_code;

fcml_string fcml_fn_msg_get_message( fcml_en_msg_message_code code );

#endif /* FCML_MESSAGES_H_ */
