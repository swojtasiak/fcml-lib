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

#ifndef FCML_MESSAGES_H_
#define FCML_MESSAGES_H_

#include <fcml_errors.h>
#include <fcml_types.h>

#define FCML_MESSAGE_MAX	512

typedef enum fcml_en_msg_message_code {
    /* Global error codes. */
    FCML_MC_CEH_GEC_NO_ERROR = 0,
    FCML_MC_CEH_GEC_OUT_OF_MEMORY = 1,
    FCML_MC_CEH_GEC_INVALID_INPUT = 2,
    FCML_MC_CEH_GEC_INTERNAL_ERROR = 3,
    FCML_MC_CEH_GEC_NOT_INITIALIZED = 4,
    FCML_MC_CEH_GEC_EOF = 5,
    FCML_MC_CEH_GEC_VALUE_OUT_OF_RANGE = 6,
    FCML_MC_CEH_GEC_FEATURE_NOT_SUPPORTED = 7,
    FCML_MC_CEH_GEC_INVALID_ADDRESSING_MODE = 8,
    FCML_MC_CEH_GEC_INVALID_ADDRESSING_FORM = 9,
    FCML_MC_CEH_GEC_INVALID_INSTRUCTION_FORM = 10,
    FCML_MC_CEH_GEC_INVALID_OPPERAND = 11,
    FCML_MC_CEH_GEC_UNKNOWN_MNEMONIC = 12,
    FCML_MC_CEH_GEC_INVALID_OPPERAND_SIZE = 13,
    FCML_MC_CEH_GEC_INVALID_ADDRESS_SIZE = 14,
    FCML_MC_CEH_GEC_UNKNOWN_INSTRUCTION = 15,
    FCML_MC_CEH_GEC_INVALID_PREFIX = 16,
    FCML_MC_CEH_GEC_INVALID_REGISTER_TYPE = 17,
    FCML_MC_CEH_GEC_INVALID_REGISTER = 18,
    FCML_MC_CEH_GEC_UNDEFINED_SYMBOL = 19,
    /* Message error codes. */
    FCML_MC_SEGMENT_REGISTER_CAN_NOT_BE_OVERRIDDEN,
    FCML_MC_SEGMENT_INVALID_PSEUDO_OPCODE_IMM,
    FCML_MC_SEGMENT_HLE_PREFIXES_NOT_ALLOWED,
    FCML_MC_SEGMENT_HLE_MORE_THAN_ONE_PREFIX,
    FCML_MC_SEGMENT_WRONG_REGISTER_TYPE_SEG,
    FCML_MC_SEGMENT_SYMBOL_ALREADY_DEFINED,
    FCML_MC_SEGMENT_UNDEFINED_SYMBOL,
    FCML_MC_SEGMENT_PARSED_LINE_TO_LONG
} fcml_en_msg_message_code;

fcml_string fcml_fn_msg_get_message(fcml_en_msg_message_code code);

void fcml_fn_msg_add_error_message(fcml_st_ceh_error_container *errors,
        fcml_en_msg_message_code msg_code, fcml_ceh_error code,
        fcml_en_ceh_error_level level, ...);

#endif /* FCML_MESSAGES_H_ */
