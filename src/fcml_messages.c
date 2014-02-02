/*
 * fcml_messages.c
 *
 *  Created on: Nov 10, 2013
 *      Author: tas
 */

#include "fcml_messages.h"

fcml_string fcml_iarr_messages[] = {
	/* Messages for global error codes. */
	FCML_TEXT("No error."),
	FCML_TEXT("Out of memory."),
	FCML_TEXT("Invalid input."),
	FCML_TEXT("Internal error."),
	FCML_TEXT("Not initialized."),
	FCML_TEXT("Unexpected end of data."),
	FCML_TEXT("Value out of range."),
	FCML_TEXT("Feature not supported."),
	FCML_TEXT("Invalid addressing mode."),
	FCML_TEXT("Invalid addressing form."),
	FCML_TEXT("Invalid instruction form."),
	FCML_TEXT("Invalid operand."),
	FCML_TEXT("Unknown mnemonic."),
	FCML_TEXT("Invalid operand size."),
	FCML_TEXT("Invalid address size."),
	FCML_TEXT("Unknown instruction."),
	FCML_TEXT("Invalid prefix."),
	FCML_TEXT("Invalid register type."),
	FCML_TEXT("Invalid register."),
	/* Messages for message error codes. */
	FCML_TEXT("Segment register can not be overridden."),
	FCML_TEXT("Invalid pseudo opcode value."),
	FCML_TEXT("HLA prefixes are not allowed for instruction."),
	FCML_TEXT("More than one HLA prefix."),
	FCML_TEXT("Segment register expected."),
	/* Messages for warnings. */
};

fcml_string fcml_fn_msg_get_message( fcml_en_msg_message_code code ) {
	return fcml_iarr_messages[code];
}
