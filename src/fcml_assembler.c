/*
 * FCML - Free Code Manipulation Library.
 * Copyright (C) 2010-2017 Slawomir Wojtasiak
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
typedef struct fcml_ist_asm_enc_assembler {
    /** Map of supported instructions, with mnemonic as key and
     * instructions addressing modes as values.
     */
    fcml_coll_map instructions_map;
    /** Map of supported pseudo operations */
    fcml_coll_map pseudo_operations_map;
    /** Dialect used to initialize assembler. */
    fcml_st_dialect_context_int *dialect_context;
} fcml_ist_asm_enc_assembler;

typedef fcml_ceh_error (*fcml_ifp_asm_encode_pseudo_operation)(
        const fcml_st_instruction *instruction,
        fcml_st_assembler_result *result);

typedef struct fcml_ist_asm_enc_pseudo_operation_desc {
    fcml_en_pseudo_operations pseudo_operation;
    fcml_ifp_asm_encode_pseudo_operation pseudo_operation_encoder;
} fcml_ist_asm_enc_pseudo_operation_desc;

fcml_ceh_error fcml_ifp_asm_encode_pseudo_operation_db_encoder(
        const fcml_st_instruction *instruction,
        fcml_st_assembler_result *result);

fcml_ist_asm_enc_pseudo_operation_desc
fcml_iarr_asm_supported_pseudo_operations[] = {
    {FP_DB, &fcml_ifp_asm_encode_pseudo_operation_db_encoder},
    {FP_NO_PSEUDO_OP, NULL }
};

/**********************
 * Pseudo operations. *
 **********************/

fcml_st_assembled_instruction *fcml_ifn_asm_alloc_assembled_instruction(
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

fcml_ceh_error fcml_ifp_asm_encode_pseudo_operation_db_encoder(
        const fcml_st_instruction *instruction,
        fcml_st_assembler_result *result) {

    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

    if (instruction->operands_count == 1
            && instruction->operands[0].type == FCML_OT_IMMEDIATE) {

        fcml_uint8_t value;
        error = fcml_fn_utils_convert_integer_to_uint8(
                &(instruction->operands[0].immediate), &value);
        if (error) {
            return FCML_CEH_GEC_VALUE_OUT_OF_RANGE;
        }

        result->instructions = fcml_ifn_asm_alloc_assembled_instruction(1);
        if (!result->instructions) {
            return FCML_CEH_GEC_OUT_OF_MEMORY;
        }

        result->instructions->code[0] = value;

    } else {
        error = FCML_CEH_GEC_INVALID_OPPERAND;
    }

    return error;

}



fcml_ist_asm_enc_pseudo_operation_desc *
fcml_ifn_asm_prepare_pseudo_operation_encoding(
        fcml_en_pseudo_operations pseudo_operation) {
    fcml_ist_asm_enc_pseudo_operation_desc *desc =
            fcml_iarr_asm_supported_pseudo_operations;
    while (desc->pseudo_operation != FP_NO_PSEUDO_OP) {
        if (desc->pseudo_operation == pseudo_operation) {
            return desc;
        }
    }
    return NULL;
}

fcml_ceh_error fcml_fn_asm_init_pseudo_operation_encodings(
        fcml_st_dialect_context_int *dialect,
        fcml_coll_map *pseudo_operations_map) {

    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

    fcml_int map_error;
    fcml_coll_map po_map = fcml_fn_coll_map_alloc(
            &fcml_coll_map_descriptor_string, 10, &map_error);
    if (map_error) {
        return fcml_fn_utils_convert_map_error(map_error);
    }

    fcml_st_dialect_pseudpo_operation_mnemonic *mnemonics_map =
            dialect->get_pseudo_operation_mnemonics();
    if (mnemonics_map) {
        while (mnemonics_map->mnemonic) {
            fcml_ist_asm_enc_pseudo_operation_desc *desc =
                    fcml_ifn_asm_prepare_pseudo_operation_encoding(
                            mnemonics_map->pseudo_operation);
            if (desc) {
                fcml_fn_coll_map_put(po_map, mnemonics_map->mnemonic, desc,
                        &map_error);
                if (map_error) {
                    fcml_fn_coll_map_free(po_map);
                    return fcml_fn_utils_convert_map_error(map_error);
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

fcml_ceh_error fcml_ifn_asm_handle_pseudo_operations(
        fcml_st_assembler_context *asm_context,
        fcml_coll_map pseudo_operations_map,
        const fcml_st_instruction *instruction,
        fcml_st_assembler_result *result) {
    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
    fcml_ist_asm_enc_pseudo_operation_desc *desc =
            (fcml_ist_asm_enc_pseudo_operation_desc*) fcml_fn_coll_map_get(
                    pseudo_operations_map, instruction->mnemonic);
    if (desc) {
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

fcml_bool fcml_ifn_verify_instruction(const fcml_st_instruction *instruction) {

    int i;
    fcml_bool last_found = FCML_FALSE;
    fcml_bool result = FCML_TRUE;

    /* Check if there are no operator gaps. */
    for(i = 0; i < FCML_OPERANDS_COUNT; i++) {
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

/*****************************
 * Assembler initialization. *
 *****************************/

fcml_ceh_error LIB_CALL fcml_fn_assembler_init(const fcml_st_dialect *dialect,
        fcml_st_assembler **assembler) {

    /* Allocate assembler instance.*/
    fcml_ist_asm_enc_assembler *enc_asm =
            (fcml_ist_asm_enc_assembler*) fcml_fn_env_memory_alloc_clear(
                    sizeof(fcml_ist_asm_enc_assembler));
    if (!enc_asm) {
        return FCML_CEH_GEC_OUT_OF_MEMORY;
    }

    /* Initializes classic processor instructions encoding. */
    fcml_ceh_error error = fcml_fn_asm_init_instruction_encodings(
            (fcml_st_dialect_context_int*) dialect,
            &(enc_asm->instructions_map));
    if (error) {
        fcml_fn_env_memory_free(enc_asm);
        return error;
    }

    /* Initialize pseudo operations encoding. */
    error = fcml_fn_asm_init_pseudo_operation_encodings(
            (fcml_st_dialect_context_int*) dialect,
            &(enc_asm->pseudo_operations_map));
    if (error) {
        fcml_fn_asm_free_instruction_encodings(enc_asm->instructions_map);
        fcml_fn_env_memory_free(enc_asm);
        return error;
    }

    enc_asm->dialect_context = (fcml_st_dialect_context_int*) dialect;

    *assembler = (fcml_st_assembler *) enc_asm;

    return FCML_CEH_GEC_NO_ERROR;
}

void fcml_ifn_asm_free_instruction_chain(fcml_st_assembled_instruction *chain) {

    /* Free every instruction in the chain. */
    while (chain) {
        fcml_st_assembled_instruction *instruction = chain;
        chain = chain->next;
        fcml_fn_env_memory_free(instruction->code);
        fcml_fn_env_memory_free(instruction);
    }

}

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

void LIB_CALL fcml_fn_assembler_result_free(fcml_st_assembler_result *result) {
    if (result) {
        // Free errors but leave container as is.
        fcml_fn_ceh_free_errors_only(&(result->errors));
        // Free all available instructions in the chain.
        fcml_ifn_asm_free_instruction_chain(result->instructions);
        // Prepare for next usage.
        fcml_fn_assembler_result_prepare(result);
    }
}

void LIB_CALL fcml_fn_assembler_result_prepare(
        fcml_st_assembler_result *result) {
    // Clean assembler result container before it is first used.
    if (result) {
        fcml_fn_env_memory_clear(result, sizeof(fcml_st_assembler_result));
    }
}



fcml_ceh_error fcml_ifn_assemble_core(fcml_st_assembler_context *asm_context,
        const fcml_st_instruction *instruction,
        fcml_st_assembler_result *result) {

    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

    // Sanity check.
    if (!result || !instruction || !instruction->mnemonic || !asm_context) {
        return FCML_CEH_GEC_INVALID_INPUT;
    }

    if (!fcml_ifn_verify_instruction(instruction)) {
        return FCML_CEH_GET_INVALID_INSTRUCTION_MODEL;
    }

    /* Validate and prepare entry point. */
    error = fcml_fn_prepare_entry_point(&(asm_context->entry_point));
    if (error) {
        return error;
    }

    /* Take into account that dialect can modify source instruction by
     * preparing it for the assembler, so we have to use a local copy here.
     */
    fcml_st_instruction tmp_instruction = *instruction;

    fcml_ist_asm_enc_assembler *enc_asm =
            (fcml_ist_asm_enc_assembler*) asm_context->assembler;

    /* The first place where the dialect can interfere with the
     * instruction definition.
     */
    fcml_fnp_asm_dialect_prepare_assembler_preprocessor assembler_preprocessor =
            enc_asm->dialect_context->assembler_preprocessor;
    if (assembler_preprocessor) {
        assembler_preprocessor(&(asm_context->configuration),
                (fcml_st_dialect*) enc_asm->dialect_context, &tmp_instruction,
                NULL, F_UNKNOWN, NULL, NULL);
    }

    /* Find instruction addressing modes/forms. */
    fcml_st_asm_instruction_addr_modes *addr_modes = NULL;
    error = fcml_fn_asm_get_instruction_encodings(enc_asm->instructions_map,
            tmp_instruction.mnemonic, &addr_modes);
    if (error) {
        if (error == FCML_CEH_GEC_UNKNOWN_MNEMONIC) {
            return fcml_ifn_asm_handle_pseudo_operations(asm_context,
                    enc_asm->pseudo_operations_map, instruction, result);
        } else {
            return error;
        }
    }

    /* Execute instruction encoder. */
    if (addr_modes) {

        if (addr_modes->instruction_encoder) {

            fcml_st_asm_encoder_result enc_result = { { 0 } };

            error = addr_modes->instruction_encoder(asm_context,
                    enc_asm->dialect_context, &tmp_instruction, &enc_result,
                    addr_modes);
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
        fcml_ifn_asm_free_instruction_chain(result->instructions);
        result->instructions = NULL;
        result->chosen_instruction = NULL;
        result->number_of_instructions = 0;
    }

    return error;
}

fcml_ceh_error LIB_CALL fcml_fn_assemble(fcml_st_assembler_context *context,
        const fcml_st_instruction *instruction,
        fcml_st_assembler_result *result) {

    /* Check if there is something already available in the result and
     * free it in such a cache.
     */
    fcml_fn_assembler_result_free(result);

    fcml_ceh_error error = fcml_ifn_assemble_core(context, instruction, result);
    if (error) {
        // Try to convert error code to error message if there is such need.
        fcml_fn_utils_convert_gec_to_error_info(
                context->configuration.enable_error_messages, &(result->errors),
                error);
    }

    return error;
}

void LIB_CALL fcml_fn_assembler_free(fcml_st_assembler *assembler) {

    if (assembler) {

        fcml_ist_asm_enc_assembler *enc_asm =
                (fcml_ist_asm_enc_assembler *) assembler;

        if (enc_asm->instructions_map) {
            fcml_fn_asm_free_instruction_encodings(enc_asm->instructions_map);
        }

        /* Frees pseudo operations encoding. */
        if (enc_asm->pseudo_operations_map) {
            fcml_fn_coll_map_free(enc_asm->pseudo_operations_map);
        }

        /* Assembler is not the owner of the dialect context. */
        fcml_fn_env_memory_free(enc_asm);
    }

}

fcml_st_dialect *fcml_fn_assembler_extract_dialect(
        fcml_st_assembler *assembler) {

    fcml_st_dialect *dialect = NULL;

    if (assembler) {
        fcml_ist_asm_enc_assembler *enc_asm =
                (fcml_ist_asm_enc_assembler*) assembler;
        dialect = (fcml_st_dialect*) enc_asm->dialect_context;
    }

    return dialect;
}

