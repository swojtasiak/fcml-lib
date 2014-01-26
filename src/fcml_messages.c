/*
 * fcml_messages.c
 *
 *  Created on: Nov 10, 2013
 *      Author: tas
 */

#include "fcml_messages.h"

fcml_string fcml_iarr_messages[] = {
	FCML_TEXT("Invalid operand."),
	FCML_TEXT("Segment register can not be overridden."),
	FCML_TEXT("Invalid pseudo opcode value."),
	FCML_TEXT("HLA prefixes are not allowed for instruction."),
	FCML_TEXT("More than one HLA prefix."),
	FCML_TEXT("Segment register expected."),
	FCML_TEXT("Invalid input."),
	FCML_TEXT("Value out of range."),
	FCML_TEXT("Unsupported addressing mode."),
	FCML_TEXT("Unsupported operand type."),
	FCML_TEXT("Unknown mnemonic."),
	FCML_TEXT("Unsupported operand size."),
	FCML_TEXT("Unsupported address size."),
	FCML_TEXT("Unsupported addressing form."),
	FCML_TEXT(""),
	FCML_TEXT(""),
};

fcml_string fcml_fn_msg_get_message( fcml_en_msg_message_code code ) {
	return fcml_iarr_messages[code];
}
