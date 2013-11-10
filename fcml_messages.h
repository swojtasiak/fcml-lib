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
	FCML_MC_INVALID_OPERAND
} fcml_en_msg_message_code;

fcml_string fcml_fn_msg_get_message( fcml_en_msg_message_code code );

#endif /* FCML_MESSAGES_H_ */
