/*
 * fcml_messages.c
 *
 *  Created on: Nov 10, 2013
 *      Author: tas
 */

#include "fcml_messages.h"

fcml_string fcml_iarr_messages[] = {
	"Invalid operand.",
	"Segment register can not be overridden.",
	"Invalid pseudo opcode value.",
	"HLA prefixes are not allowed for instruction.",
	"More than one HLA prefix."
};

fcml_string fcml_fn_msg_get_message( fcml_en_msg_message_code code ) {
	return fcml_iarr_messages[code];
}
