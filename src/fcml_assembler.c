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

#include <stddef.h>

#include <fcml_assembler.h>
#include <fcml_errors.h>

#include "fcml_dialect_int.h"
#include "fcml_encoding.h"
#include "fcml_env_int.h"
#include "fcml_utils.h"
#include "fcml_trace.h"
#include "fcml_coll.h"

/** Initialized assembler instance. */
typedef struct enc_assembler {
    /** Map of supported instructions, with mnemonic as key and
     * instructions addressing modes as values.
     */
    fcml_coll_map instructions_map;
    /** Map of supported pseudo operations */
    fcml_coll_map pseudo_operations_map;
    /** Dialect used to initialize assembler. */
    fcml_st_dialect_context_int *dialect_context;
} enc_assembler;

/** Type for pseudo operations encoders. */
typedef fcml_ceh_error (*pseudo_operation_encoder)(
        const fcml_st_instruction *instruction,
        fcml_st_assembler_result *result);

/** Holds definition of a pseudo operation encoder. */
typedef struct pseudo_operation_desc {
    /** ID of the pseudo operation. */
    fcml_en_pseudo_operations pseudo_operation;
    /** Function responsible for encoding pseudo operation. */
    pseudo_operation_encoder pseudo_operation_encoder;
} pseudo_operation_desc;

/** Pseudo operation encoder for "encode byte" (DB). */
static fcml_ceh_error db_pseudo_operation_encoder(const fcml_st_instruction*,
        fcml_st_assembler_result*);

/** Array of all supported pseudo operation encoders. */
static pseudo_operation_desc supported_pseudo_operations[] = {
    { FP_DB, &db_pseudo_operation_encoder },
    { FP_NO_PSEUDO_OP, NULL }
};

static fcml_bool verify_instruction(const fcml_st_instruction *instruction);

static void free_instruction_chain(fcml_st_assembled_instruction *chain);

static fcml_ceh_error encode_pseudo_operation(
        const fcml_st_assembler_context *asm_context,
        const fcml_coll_map pseudo_operations_map,
        const fcml_st_instruction *instruction,
        fcml_st_assembler_result *result);

static fcml_ceh_error init_pseudo_operation_encodings(
        fcml_st_dialect_context_int *dialect,
        fcml_coll_map *pseudo_operations_map);

static fcml_ceh_error assemble_core(fcml_st_assembler_context *asm_context,
        const fcml_st_instruction *instruction,
        fcml_st_assembler_result *result);

/** see documentation in header files */
fcml_ceh_error LIB_CALL fcml_fn_assembler_init(const fcml_st_dialect *dialect,
        fcml_st_assembler **assembler) {
    /* Allocate assembler instance.*/
    FCML_ENV_ALLOC_CLEAR(enc_asm, enc_assembler);
    if (!enc_asm) {
        return FCML_CEH_GEC_OUT_OF_MEMORY;
    }

    /* Initializes classic processor instructions encoding. */
    fcml_ceh_error error = fcml_fn_init_instructions_addr_modes(
            (fcml_st_dialect_context_int*) dialect,
            &(enc_asm->instructions_map));
    if (error) {
        fcml_fn_env_memory_free(enc_asm);
        return error;
    }

    /* Initialize pseudo operations encoding. */
    error = init_pseudo_operation_encodings(
            (fcml_st_dialect_context_int*) dialect,
            &(enc_asm->pseudo_operations_map));
    if (error) {
        fcml_fn_free_instructions_addr_modes(enc_asm->instructions_map);
        fcml_fn_env_memory_free(enc_asm);
        return error;
    }

    enc_asm->dialect_context = (fcml_st_dialect_context_int*) dialect;

    *assembler = (fcml_st_assembler*) enc_asm;

    return FCML_CEH_GEC_NO_ERROR;
}

/** see documentation in header files */
void LIB_CALL fcml_fn_assembler_instruction_detach(
        fcml_st_assembled_instruction **chain,
        fcml_st_assembled_instruction *instruction) {

    if (!chain || !instruction) {
        return;
    }

    fcml_st_assembled_instruction **current = chain;
    fcml_bool found = FCML_FALSE;

    do {
        if (*current == instruction) {
            *current = instruction->next;
            found = FCML_TRUE;
        }
        current = &((*current)->next);
    } while (!found && *current);
}

/** see documentation in header files */
void LIB_CALL fcml_fn_assembler_instruction_free(
        fcml_st_assembled_instruction *instruction) {
    if (instruction) {
        if (instruction->code) {
            fcml_fn_env_memory_free(instruction->code);
        }
        fcml_fn_ceh_free_errors_only(&(instruction->warnings));
        fcml_fn_env_memory_free(instruction);
    }
}

/** see documentation in header files */
void LIB_CALL fcml_fn_assembler_result_free(fcml_st_assembler_result *result) {
    if (result) {
        // Free errors but leave container as is.
        fcml_fn_ceh_free_errors_only(&(result->errors));
        // Free all available instructions in the chain.
        free_instruction_chain(result->instructions);
        // Prepare for next usage.
        fcml_fn_assembler_result_prepare(result);
    }
}

/** see documentation in header files */
void LIB_CALL fcml_fn_assembler_result_prepare(fcml_st_assembler_result *result) {
    // Clean assembler result container before it is first used.
    if (result) {
        fcml_fn_env_memory_clear(result, sizeof(fcml_st_assembler_result));
    }
}

fcml_ceh_error LIB_CALL fcml_fn_assemble(fcml_st_assembler_context *context,
        const fcml_st_instruction *instruction,
        fcml_st_assembler_result *result) {
    /* Check if there is something already available in the result and
     * free it in such a case.
     */
    fcml_fn_assembler_result_free(result);
    fcml_ceh_error error = assemble_core(context, instruction, result);
    if (error) {
        // Try to convert error code to error message if there is such need.
        fcml_fn_utils_conv_gec_to_error_info(
                context->configuration.enable_error_messages, &(result->errors),
                error);
    }
    return error;
}

void LIB_CALL fcml_fn_assembler_free(fcml_st_assembler *assembler) {
    if (assembler) {
        enc_assembler *enc_asm = (enc_assembler*) assembler;
        if (enc_asm->instructions_map) {
            fcml_fn_free_instructions_addr_modes(enc_asm->instructions_map);
        }
        /* Frees pseudo operations encoding. */
        if (enc_asm->pseudo_operations_map) {
            fcml_fn_coll_map_free(enc_asm->pseudo_operations_map);
        }
        /* Assembler is not the owner of the dialect context. */
        fcml_fn_env_memory_free(enc_asm);
    }
}

/** This is an internal function used by assembler
 * internals to extract dialect from the assembler instance. */
fcml_st_dialect* fcml_fn_assembler_extract_dialect(fcml_st_assembler *assembler) {
    fcml_st_dialect *dialect = NULL;
    if (assembler) {
        enc_assembler *enc_asm = (enc_assembler*) assembler;
        dialect = (fcml_st_dialect*) enc_asm->dialect_context;
    }
    return dialect;
}

static void free_instruction_chain(fcml_st_assembled_instruction *chain) {
    /* Free every instruction in the chain. */
    while (chain) {
        fcml_st_assembled_instruction *instruction = chain;
        chain = chain->next;
        fcml_fn_env_memory_free(instruction->code);
        fcml_fn_env_memory_free(instruction);
    }
}

/** The core assembling logic. */
static fcml_ceh_error assemble_core(fcml_st_assembler_context *asm_context,
        const fcml_st_instruction *instruction,
        fcml_st_assembler_result *result) {

    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

    /* Sanity check. */
    if (!result || !instruction || !instruction->mnemonic || !asm_context) {
        return FCML_CEH_GEC_INVALID_INPUT;
    }

    if (!verify_instruction(instruction)) {
        return FCML_CEH_GEC_INVALID_INSTRUCTION_MODEL;
    }

    /* Validate and prepare entry point. */
    error = fcml_fn_utils_prepare_entry_point(&(asm_context->entry_point));
    if (error) {
        return error;
    }

    /* Take into account that dialect can modify source instruction by
       preparing it for the assembler, so we have to use a local copy here. */
    fcml_st_instruction tmp_instruction = *instruction;

    enc_assembler *enc_asm = (enc_assembler*) asm_context->assembler;

    /* The first place where the dialect can interfere with the
       instruction definition. */
    fcml_fnp_asm_preprocessor preprocessor =
            enc_asm->dialect_context->asm_preprocessor;
    if (preprocessor) {
        preprocessor((fcml_st_dialect*) enc_asm->dialect_context,
                NULL, NULL, F_UNKNOWN, &tmp_instruction, NULL);
    }

    /* Find instruction addressing modes/forms. */
    fcml_st_instruction_addr_modes *addr_modes = NULL;
    error = fcml_fn_get_instruction_addr_modes(enc_asm->instructions_map,
            tmp_instruction.mnemonic, &addr_modes);
    if (error) {
        if (error == FCML_CEH_GEC_UNKNOWN_MNEMONIC) {
            return encode_pseudo_operation(asm_context,
                    enc_asm->pseudo_operations_map, instruction, result);
        } else {
            return error;
        }
    }

    /* Execute instruction encoder. */
    if (addr_modes) {
        if (addr_modes->encoder) {
            fcml_st_asm_encoder_result enc_result = { { 0 } };
            error = addr_modes->encoder(asm_context, enc_asm->dialect_context,
                    addr_modes, &tmp_instruction, &enc_result);
            if (!error) {
                result->instructions = enc_result.instructions;
                result->number_of_instructions =
                        enc_result.number_of_instructions;
                result->chosen_instruction = enc_result.chosen_instruction;
                /* Increment IP by chosen instruction length. */
                if (result->chosen_instruction
                        && asm_context->configuration.increment_ip) {
                    asm_context->entry_point.ip +=
                            result->chosen_instruction->code_length;
                }
            }
            /* Convert encoding result to assembler result. */
            result->errors = enc_result.errors;
        } else {
            FCML_TRACE_MSG( "Unavailable instruction encoder." );
            error = FCML_CEH_GEC_INTERNAL_ERROR;
        }
    } else {
        error = FCML_CEH_GEC_UNKNOWN_MNEMONIC;
    }

    /* Free results but only if assembling failed. */
    if (error) {
        /* Free only instructions, error messages should be returned to user. */
        free_instruction_chain(result->instructions);
        result->instructions = NULL;
        result->chosen_instruction = NULL;
        result->number_of_instructions = 0;
    }

    return error;
}

/** Allocates new instance of assembled instruction for given number
 * of machine code bytes.
 */
static fcml_st_assembled_instruction* allocate_assembled_instruction(
        fcml_usize size) {
    fcml_st_assembled_instruction *instruction =
            (fcml_st_assembled_instruction*) fcml_fn_env_memory_alloc_clear(
                    sizeof(fcml_st_assembled_instruction));
    if (!instruction) {
        return NULL;
    }

    instruction->code = (fcml_uint8_t*) fcml_fn_env_memory_alloc_clear(size);
    if (!instruction->code) {
        fcml_fn_env_memory_free(instruction);
        return NULL;
    }

    instruction->code_length = size;

    return instruction;
}

/** Encodes "encode byte" (DB) pseudo operation. */
static fcml_ceh_error db_pseudo_operation_encoder(
        const fcml_st_instruction *instruction,
        fcml_st_assembler_result *result) {

    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

    if (instruction->operands_count == 1
            && instruction->operands[0].type == FCML_OT_IMMEDIATE) {

        fcml_uint8_t value;
        error = fcml_fn_utils_conv_int_to_uint8(
                &(instruction->operands[0].immediate), &value);
        if (error) {
            return FCML_CEH_GEC_VALUE_OUT_OF_RANGE;
        }

        result->instructions = allocate_assembled_instruction(1);
        if (!result->instructions) {
            return FCML_CEH_GEC_OUT_OF_MEMORY;
        }

        result->instructions->code[0] = value;
    } else {
        error = FCML_CEH_GEC_INVALID_OPPERAND;
    }

    return error;
}

/** Goes through the array of pseudo operations descriptors in order to find
 * one for the given pseudo operation ID. */
static pseudo_operation_desc* find_desc_for_pseudo_operation(
        fcml_en_pseudo_operations pseudo_operation) {
    pseudo_operation_desc *desc = supported_pseudo_operations;
    while (desc->pseudo_operation != FP_NO_PSEUDO_OP) {
        if (desc->pseudo_operation == pseudo_operation) {
            return desc;
        }
        desc++;
    }
    return NULL;
}

/** Initializes encoding map for pseudo operations. */
static fcml_ceh_error init_pseudo_operation_encodings(
        fcml_st_dialect_context_int *dialect,
        fcml_coll_map *pseudo_operations_map) {

    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

    fcml_int map_error;
    fcml_coll_map po_map = fcml_fn_coll_map_alloc(
            &fcml_coll_map_descriptor_string, 10, &map_error);
    if (map_error) {
        return fcml_fn_utils_conv_map_error(map_error);
    }

    fcml_st_dialect_pseudo_op_mnemonic *mnemonics_map =
            dialect->get_pseudo_op_mnemonics();
    if (mnemonics_map) {
        while (mnemonics_map->mnemonic) {
            pseudo_operation_desc *desc = find_desc_for_pseudo_operation(
                    mnemonics_map->pseudo_operation);
            if (desc) {
                fcml_fn_coll_map_put(po_map, mnemonics_map->mnemonic, desc,
                        &map_error);
                if (map_error) {
                    fcml_fn_coll_map_free(po_map);
                    return fcml_fn_utils_conv_map_error(map_error);
                }
            } else {
                FCML_TRACE( "Unsupported pseudo operation code: %d.",
                        mnemonics_map->pseudo_operation );
            }
            mnemonics_map++;
        }
    }

    *pseudo_operations_map = po_map;

    return error;
}

/** If the given instruction holds pseudo operation,
 * this function tries to encode it.
 */
static fcml_ceh_error encode_pseudo_operation(
        const fcml_st_assembler_context *asm_context,
        const fcml_coll_map pseudo_operations_map,
        const fcml_st_instruction *instruction,
        fcml_st_assembler_result *result) {

    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

    pseudo_operation_desc *desc = (pseudo_operation_desc*)
            fcml_fn_coll_map_get(pseudo_operations_map, instruction->mnemonic);

    if (desc) {
        /* There is a pseudo operation encoder for the mnemonic,
         * so try to encode it. */
        error = desc->pseudo_operation_encoder(instruction, result);
        if (!error) {
            result->chosen_instruction = result->instructions;
            result->number_of_instructions = 1;
        }
    } else {
        error = FCML_CEH_GEC_UNKNOWN_MNEMONIC;
    }

    return error;
}

/** A basic check for the instructions provided by the callers. */
static fcml_bool verify_instruction(const fcml_st_instruction *instruction) {
    int i;
    fcml_bool last_found = FCML_FALSE;
    fcml_bool result = FCML_TRUE;

    /* Check if there are no operator gaps. */
    for (i = 0; i < FCML_OPERANDS_COUNT; i++) {
        if (instruction->operands[i].type == FCML_OT_NONE) {
            last_found = FCML_TRUE;
        } else {
            if (last_found) {
                result = FCML_FALSE;
                break;
            }
        }
    }

    return result;
}

