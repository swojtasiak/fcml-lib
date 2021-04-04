/*
 * FCML - Free Code Manipulation Library.
 * Copyright (C) 2010-2020 Slawomir Wojtasiak
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include <stdarg.h>

#include "fcml_messages.h"
#include "fcml_ceh.h"
#include "fcml_env_int.h"

#define FCML_MAX_MESSAGE_LENGTH		512

static fcml_string error_messages[] = {
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
	FCML_TEXT("Undefined symbol."),
	/* Messages for message error codes. */
	FCML_TEXT("Segment register can not be overridden."),
	FCML_TEXT("Invalid pseudo opcode value."),
	FCML_TEXT("HLA prefixes are not allowed for instruction."),
	FCML_TEXT("More than one HLA prefix."),
	FCML_TEXT("Segment register expected."),
	FCML_TEXT("Symbol already defined: %s."),
	FCML_TEXT("Undefined symbol: %s."),
	FCML_TEXT("Parsed line exceed maximum allowed length."),
	/* Messages for warnings. */
};

fcml_string fcml_fn_msg_get_message(fcml_en_msg_message_code code) {
    return error_messages[code];
}

void fcml_fn_msg_add_error_message(fcml_st_ceh_error_container *errors,
        fcml_en_msg_message_code msg_code, fcml_ceh_error code,
        fcml_en_ceh_error_level level, ...) {
    fcml_char buffer[FCML_MAX_MESSAGE_LENGTH];
    va_list args;
    va_start(args, level);
    fcml_fn_env_str_vsnprintf(buffer, sizeof(buffer),
            fcml_fn_msg_get_message(msg_code), args);
    va_end(args);
    fcml_fn_ceh_add_error(errors, (const fcml_string) buffer, code, level);
}
