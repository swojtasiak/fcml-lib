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

/** @file fcml_errors.h
 * Global error handling related declarations.
 * @copyright Copyright (C) 2010-2020 Slawomir Wojtasiak. All rights reserved.
 * This project is released under the GNU Lesser General Public License.
 */

#ifndef FCML_ASM_ERRORS_H_
#define FCML_ASM_ERRORS_H_

#include "fcml_lib_export.h"

#include "fcml_types.h"

/**
 * @defgroup ERRORS_GROUP Global error codes
 * Describes all available global error codes.
 * @{
 */

/** All global error codes are placed here. */
enum fcml_en_ceh_error_globals {
    /** Operation succeed. */
    FCML_CEH_GEC_NO_ERROR = 0,
    /** There is not enough memory to complete operation. */
    FCML_CEH_GEC_OUT_OF_MEMORY = 1,
    /** Invalid function arguments. */
    FCML_CEH_GEC_INVALID_INPUT = 2,
    /** An internal error occurred. Enable tracing in order to get more
     *  detailed information. */
    FCML_CEH_GEC_INTERNAL_ERROR = 3,
    /** Component hasn't been initialized yet. */
    FCML_CEH_GEC_NOT_INITIALIZED = 4,
    /** Incomplete instruction. */
    FCML_CEH_GEC_EOF = 5,
    /** Used mainly in case of integers and offsets. */
    FCML_CEH_GEC_VALUE_OUT_OF_RANGE = 6,
    /** Chosen operation is not supported in case of given configuration. */
    FCML_CEH_GEC_FEATURE_NOT_SUPPORTED = 7,
    /** Unsupported operating mode. For instance encoded instruction needs 16
     * bit operating mode, but we are in 64 bit mode. */
    FCML_CEH_GEC_INVALID_OPERATING_MODE = 8,
    /** Chosen addressing form can not be encoded as for example ModR/M field. */
    FCML_CEH_GEC_INVALID_ADDRESSING_FORM = 9,
    /** Unsupported instruction form (Instruction may be supported, but not
     * with given set of operands). */
    FCML_CEH_GEC_INVALID_INSTRUCTION_FORM = 10,
    /** Instruction do not support one of the defined operands. */
    FCML_CEH_GEC_INVALID_OPPERAND = 11,
    /** Unknown mnemonic. */
    FCML_CEH_GEC_UNKNOWN_MNEMONIC = 12,
    /** Operand size (Operand size attribute) is not allowed in given context. */
    FCML_CEH_GEC_INVALID_OPPERAND_SIZE = 13,
    /** Address size (Address size attribute) is not allowed in given context. */
    FCML_CEH_GEC_INVALID_ADDRESS_SIZE = 14,
    /** User chosen unsupported addressing form */
    FCML_CEH_GEC_UNKNOWN_INSTRUCTION = 15,
    /** Assembler can return this error code if there is not allowed prefix
     * defined for given instruction. */
    FCML_CEH_GEC_INVALID_PREFIX = 16,
    /** Wrong register type. */
    FCML_CEH_GEC_INVALID_REGISTER_TYPE = 17,
    /** Wrong register. */
    FCML_CEH_GEC_INVALID_REGISTER = 18,
    /** Error returned by parsers when there is undefined symbol used. */
    FCML_CEH_GEC_UNDEFINED_SYMBOL = 19,
    /** Labels are not supported. */
    FCML_CEH_GEC_UNSUPPORTED_LABEL_DECLARATION = 20,
    /** Required operand decorator is missing. */
    FCML_CEH_GEC_MISSING_DECORATOR = 21,
    /** Given operand decorator is not supported by operand. */
    FCML_CEH_GEC_NOT_SUPPORTED_DECORATOR = 22,
    /** Gap between operands found. */
    FCML_CEH_GEC_INVALID_INSTRUCTION_MODEL = 23,
    /* Decorator is invalid. For example wrong register type is used in
     * opmask decorator. */
    FCML_CEH_GEC_INVALID_OPERAND_DECORATOR = 24
};

/** @} */

/**
 * @defgroup MESSAGE_ERRORS_GROUP Error codes for textual messages
 * Describes all available error codes dedicated to textual errors.
 * @{
 */

/** Error codes dedicated to textual messages.
 * In some cases they are a bit more detailed than corresponding
 * global error codes returned in case of errors. Remember that global
 * error codes also can be used in place of error codes for textual
 * messages. It is why they use different code ranges.
 */
enum fcml_en_ceh_message_errors {
    /** Segment register can not be overridden. */
    FCML_CEH_MEC_ERROR_ILLEGAL_SEG_REG_OVERRIDE = 1000,
    /** To many operands passed to parser. */
    FCML_CEH_MEC_ERROR_TO_MANY_OPERANDS = 1001,
    /** Unsupported pseudo-op value. */
    FCML_CEH_MEC_ERROR_INVALID_PSEUDO_OPCODE_VALUE = 1002,
    /** HLE prefix is not allowed in given context. */
    FCML_CEH_MEC_ERROR_HLE_PREFIX_NOT_ALLOWED = 1003,
    /** There is more than one HLE prefix. */
    FCML_CEH_MEC_ERROR_HLE_MORE_THAN_ONE_PREFIX = 1004,
    /** Expression attempts to divide by 0 */
    FCML_CEH_MEC_ERROR_DIVISION_BY_0 = 1005,
    /** Wrong value type used in given context. For example float used
     * in place of integer. */
    FCML_CEH_MEC_ERROR_WRONG_VALUE_FORMAT = 1006,
    /** Value out of range, for example 32 bit value used as
     * segment selector. */
    FCML_CEH_MEC_ERROR_VALUE_OUT_OF_RANGE = 1007,
    /** Syntax error from parser. */
    FCML_CEH_MEC_ERROR_INVALID_SYNTAX = 1008,
    /** Wrong register type used in place of segment register. */
    FCML_CEH_MEC_ERROR_INVALID_REGISTER_TYPE_SEG = 1009,
    /** Symbol is already defined in parser's symbol table. */
    FCML_CEH_MEC_ERROR_SYMBOL_ALREADY_DEFINED = 1010,
    /** Symbol is undefined. */
    FCML_CEH_MEC_ERROR_UNDEFINED_SYMBOL = 1011,
    /** Parsed line exceed maximal allowed length. */
    FCML_CEH_MEC_ERROR_PARSED_LINE_TOO_LONG = 1012,
    /** Invalid vector length size. */
    FCML_CEH_MEC_ERROR_INVALID_VECTOR_LENGTH = 1013
};

/** Codes for textual warnings. */
enum fcml_en_ceh_message_warnings {
    /** Value out of range  */
    FCML_CEH_MEW_WARN_VALUE_OUT_OF_RANGE = 2000,
    /** Invalid addressing mode. */
    FCML_CEH_MEW_WARN_INVALID_ADDRESSING_MODE = 2001
};

/** @} */

/** All error codes should be held in variables of this type. */
typedef fcml_uint16_t fcml_ceh_error;

/** Error levels. */
typedef enum fcml_en_ceh_error_level {
    /** Warnings are reported when processing does not need to be stopped. */
    FCML_EN_CEH_EL_WARN,
    /** Errors are reported when something more important happened and
     * processing should be stopped. */
    FCML_EN_CEH_EL_ERROR
} fcml_en_ceh_error_level;

/** Information about one particular error/warning. */
typedef struct fcml_st_ceh_error_info {
    /** Next error/warning on the list. */
    struct fcml_st_ceh_error_info *next_error;
    /** Error message. */
    fcml_string message;
    /** Error code */
    fcml_ceh_error code;
    /** Error level. */
    fcml_en_ceh_error_level level;
} fcml_st_ceh_error_info;

/** Container for all collected errors and warnings. */
typedef struct fcml_st_ceh_error_container {
    /** All errors and warnings going here. */
    fcml_st_ceh_error_info *errors;
    /** Pointer to the last error/warning on the list. */
    fcml_st_ceh_error_info *last_error;
} fcml_st_ceh_error_container;

#endif /* FCML_ASM_ERRORS_H_ */
