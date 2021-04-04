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

#include "fcml_encoding.h"

#include <stdio.h>
#include <fcml_dialect.h>
#include <fcml_errors.h>
#include <fcml_optimizers.h>
#include <fcml_choosers.h>
#include <fcml_assembler.h>

#include "fcml_def.h"
#include "fcml_env_int.h"
#include "fcml_hints.h"
#include "fcml_messages.h"
#include "fcml_mnemonic_parser.h"
#include "fcml_modrm.h"
#include "fcml_modrm_encoder.h"
#include "fcml_stream.h"
#include "fcml_trace.h"
#include "fcml_utils.h"

#define FCML_ASM_MAX_PART_PROCESSORS    40

/* REX prefix.*/
#define FCML_ENCODE_REX_BASE        0x40
#define FCML_ENCODE_REX_W(rex,w)    (rex | (w << 3))
#define FCML_ENCODE_REX_R(rex,r)    (rex | (r << 2))
#define FCML_ENCODE_REX_X(rex,x)    (rex | (x << 1))
#define FCML_ENCODE_REX_B(rex,b)    (rex | b)

/* XOP/VEX prefixes.*/
#define FCML_ENCODE_VEXOP_MMMM(vexop,x) ((vexop) | ((x) & 0x1F))
#define FCML_ENCODE_VEXOP_VVVV(vexop,x) ((vexop) | ((~(x) & 0x0F) << 3))
#define FCML_ENCODE_VEXOP_PP(vexop,x)   ((vexop) | ((x) & 0x03))
#define FCML_ENCODE_VEXOP_W(vexop,x)    ((vexop) | (((x) & 0x01) << 7))
#define FCML_ENCODE_VEXOP_L(vexop,x)    ((vexop) | (((x) & 0x01) << 2))

/* R,X and B are stored in 1's complement form.*/
#define FCML_ENCODE_VEXOP_R(vexop,x)    ((vexop) | ((~(x) & 0x01) << 7))
#define FCML_ENCODE_VEXOP_X(vexop,x)    ((vexop) | ((~(x) & 0x01) << 6))
#define FCML_ENCODE_VEXOP_B(vexop,x)    ((vexop) | ((~(x) & 0x01) << 5))

/* EVEX prefix */
#define FCML_ENCODE_EVEX_PREFIX_LENGTH      4

#define FCML_ENCODE_EVEX_P0_R(evex,x)       ((evex) | ((~(x) & 0x01) << 7))
#define FCML_ENCODE_EVEX_P0_X(evex,x)       ((evex) | ((~(x) & 0x01) << 6))
#define FCML_ENCODE_EVEX_P0_B(evex,x)       ((evex) | ((~(x) & 0x01) << 5))
#define FCML_ENCODE_EVEX_P0_R_prim(evex,x)  ((evex) | ((~(x) & 0x01) << 4))
#define FCML_ENCODE_EVEX_P0_mm(evex,x)      ((evex) | ((x) & 0x03))

#define FCML_ENCODE_EVEX_P1_W(evex,x)       ((evex) | (((x) & 0x01) << 7))
#define FCML_ENCODE_EVEX_P1_vvvv(evex,x)    FCML_ENCODE_VEXOP_VVVV(evex, x)
#define FCML_ENCODE_EVEX_P1_pp(evex,x)      FCML_ENCODE_VEXOP_PP(evex, x)

#define FCML_ENCODE_EVEX_P2_z(evex,x)       ((evex) | (((x) & 0x01) << 7))
#define FCML_ENCODE_EVEX_P2_b(evex,x)       ((evex) | (((x) & 0x01) << 4))
#define FCML_ENCODE_EVEX_P2_V_prim(evex,x)  ((evex) | ((~(x) & 0x01) << 3))
#define FCML_ENCODE_EVEX_P2_aaa(evex,x)     ((evex) | ((x) & 0x07))
#define FCML_ENCODE_EVEX_P2_LL(evex,x)      ((evex) | (((x) & 0x03) << 5))

#define FCML_ASM_FCF    16

/* Addressing mode processing phase. */
typedef enum addr_mode_proc_phase {
    AMPP_UNDEFINED,
    AMPP_ACCEPT,
    AMPP_PROCESS
} addr_mode_proc_phase;

/* An error container that holds an information whether errors messages are
   enabled or not. */
struct error_container {
    /** True if optional error and warning messages should be collected
     *  during processing. */
    fcml_bool enabled;
    /* A common error container. */
    fcml_st_ceh_error_container errors;
};

/*
 * This container holds errors collected while all addressing modes are
 * processed.
 */
typedef struct addr_mode_error {
    /** Addressing mode processing failed in the phase: */
    addr_mode_proc_phase phase;
    /** Error code */
    fcml_ceh_error error_code;
    /** Local errors container, dedicated to addressing mode processing. */
    struct error_container errors;
    /** Ordinal number of failed instruction part processor. */
    fcml_int ipp_failed;
} addr_mode_error;

typedef struct extension_prefixes_fields {
    /* VEX/XOP/EVEX.vvvv. */
    fcml_uint8_t vvvv;
    /* EVEX.V'. */
    fcml_uint8_t V_prim;
    /* VEX/XOP.mmmmm, EVEX.mm */
    fcml_uint8_t mmmm;
    /* EVEX.z field. */
    fcml_bool z;
    /* EVEX.b field. */
    fcml_bool b;
    /* EVEX.aaa. */
    fcml_uint8_t aaa;
    /* Embedded rounding mode. */
    fcml_nuint8_t er;
    /* Vector length explicitly set for instruction. Do not set L'L. */
    fcml_bool explicit_vector_length;
} extension_prefixes_fields;

/* Responsible for calculating memory data size. Custom calculators have \
 * to implement this function.
 */
typedef fcml_usize (*memory_data_size_calculator)(
        const fcml_st_instruction *instruction, fcml_ptr args);

typedef struct addr_mode_desc_details {
    /* Which OSA values are allowed for addressing mode. */
    fcml_flags allowed_osa;
    /* Which ASA values are allowed for addressing mode. */
    fcml_flags allowed_asa;
    /* Whether it's a conditional instruction or not. */
    fcml_bool is_conditional;
    /* Type of condition used for instruction. */
    fcml_st_condition condition;
    /* Optional custom memory data size calculator. */
    memory_data_size_calculator ds_calculator;
    /* Predefined calculator configuration. */
    fcml_ptr ds_calculator_args;
} addr_mode_desc_details;

/* Encoded operand register details. */
struct opcode_reg {
    fcml_uint8_t opcode_reg;
    fcml_uint8_t ext_b;
};

/* is5 encoder consists of two parts which need to exchange state. */
struct isX_state {
    fcml_uint8_t is5_byte;
};

/* Some hints which can be set by encoders in order to control
 * ModR/M encoding process. */
struct modrm_hints {
    fcml_bool is_sib_alternative_hint;
    fcml_bool is_rel_alternative_hint;
    fcml_bool is_abs_alternative_hint;
};

typedef struct encoding_context {
    /* Assembler configuration. */
    const fcml_st_assembler_context *assembler_context;
    /* Instruction being encoded. */
    const fcml_st_instruction *instruction;
    /* Mnemonic chosen for addressing mode being encoded. */
    const fcml_st_mp_mnemonic *mnemonic;
    /* All optimizer related control fields are stored here. */
    fcml_st_asm_optimizer_processing_details optimizer_processing_details;
    /* isX related state used to exchange information between is5 encoders. */
    struct isX_state isX_state;
    /* Prefixes fields set by encoders. Used to encode instruction prefixes. */
    extension_prefixes_fields epf;
    /* Used to force specific non-default segment register. */
    fcml_st_register segment_override;
    /* All encoders are allowed to fill ModR/M details which
     * are then used to encode ModR/M field. */
    fcml_st_modrm mod_rm;
    /* ModR/M related operand hints. */
    struct modrm_hints modrm_hints;
    /* ModR/M encoded into an intermediate form. All ModR/M fields
     * can be found here. Provided by 'ipp_ModRM_encoder'. */
    fcml_st_encoded_modrm encoded_mod_rm;
    /* Opcode register to be encoded directly in the opcode and REX field. */
    struct opcode_reg opcode_reg;
    /* Encoded instruction size in bytes. */
    fcml_nuint8_t instruction_size;
    /* Information for REX encoder that REX prefix is needed
     * to encode register opcode. */
    fcml_bool reg_opcode_needs_rex;
    /* Operand size calculator selected for processed addressing mode.*/
    memory_data_size_calculator ds_calculator;
    /* Arguments for data size calculator. */
    fcml_ptr ds_calculator_args;
    /* Error messages.*/
    struct error_container errors;
    /* Number of lastly proceeded instruction part processor. */
    fcml_int last_ipp;
#ifdef FCML_DEBUG
    fcml_int __def_index;
#endif
} encoding_context;

/** Optimizer context for acceptors. */
struct acceptor_optimizer_ctx {
    /** Allowed values of the operand size attribute calculated by the
     * assembler engine.
     * It is the optimizer who decides which one should be finally used.
     */
    fcml_st_nullable_size_flags allowed_eosa;
    /** Allowed values of the address size attribute calculated by the
     * assembler engine.
     * It is optimizer who decides which one should be finally used.
     */
    fcml_st_nullable_size_flags allowed_easa;
    /** Vector length of AVX instructions. Set to FCML_DS_UNDEF if not used. */
    fcml_usize vector_length;
};

struct acceptor_ctx {
    /** Assembler behavior can be configured here.*/
    const fcml_st_assembler_conf configuration;
    /* Instruction entry point configuration. */
    const fcml_st_entry_point *entry_point;
    /* Assembled instruction. */
    const fcml_st_instruction *instruction;
    /* Mnemonic chosen for addressing mode being encoded. */
    const fcml_st_mp_mnemonic *mnemonic;
    /* All optimizer related control fields are stored here. */
    struct acceptor_optimizer_ctx optimizer_ctx;
    /* Operand size calculator selected for processed addressing mode.*/
    memory_data_size_calculator ds_calculator;
    /* Arguments for data size calculator. */
    fcml_ptr ds_calculator_args;
    /* Error messages.*/
    struct error_container error_container;
    /* Number of lastly proceeded instruction part processor. */
    fcml_int last_ipp;
#ifdef FCML_DEBUG
    fcml_int __def_index;
#endif
};

struct inst_part;

/* Instruction part post processor. */
typedef fcml_ceh_error (*inst_part_post_processor)(encoding_context *context,
        struct inst_part *, fcml_ptr post_processor_args);

/* Represents a part of assembled instruction, for instance imm8 or ModRM part. */
typedef struct inst_part {
    fcml_uint8_t code[10];
    fcml_int code_length;
    fcml_ptr post_processor_args;
    inst_part_post_processor post_processor;
} inst_part;

typedef struct inst_part_container {
    /* Address of the instruction parts array.*/
    inst_part *parts;
    /* Number of instruction parts in the array.*/
    fcml_int count;
} inst_part_container;

struct inst_addr_modes;

typedef enum part_processor_phase {
    /* ModR/M and prefixes arguments filling. */
    IPPP_FIRST_PHASE,
    /* ModR/M encoding. */
    IPPP_SECOND_PHASE,
    /* Prefixes are applied in this phase. */
    IPPP_THIRD_PHASE
} part_processor_phase;

typedef struct init_context {
    fcml_coll_map inst_map;
    fcml_st_dialect_context_int *dialect_context;
} init_context;

/** Builds addressing mode encodings for given addressing mode.
 * All the built encodings are registered in the provided context. */
typedef fcml_ceh_error (*addr_mode_encoding_builder)(
        init_context*, const fcml_st_def_instruction_desc*,
        const fcml_st_def_addr_mode_desc*);

typedef struct operand_encoder_args {
    part_processor_phase phase;
    encoding_context *context;
    const fcml_st_def_addr_mode_desc *addr_mode_def;
    fcml_st_def_decoded_addr_mode *addr_mode;
    const fcml_st_operand *operand;
    inst_part *operand_enc;
} operand_encoder_args;

/* Encodes operand to a final array of bytes. */
typedef fcml_ceh_error (*operand_encoder)(operand_encoder_args*);

typedef struct operand_acceptor_args {
    struct acceptor_ctx *context;
    const fcml_st_operand *operand;
    const fcml_st_def_addr_mode_desc *addr_mode_desc;
    const addr_mode_desc_details *addr_mode_details;
    fcml_st_def_decoded_addr_mode *addr_mode;
    inst_part *operand_enc;
} operand_acceptor_args;

/* Checks if given instruction operand can be encoded for currently
 * considered instruction addressing mode. If all the operands are
 * accepted, the instruction addressing mode can be used to encode
 * instruction. */
typedef fcml_ceh_error (*operand_acceptor)(operand_acceptor_args *args);

/* Instruction part encoder arguments. */
typedef struct ipp_encoder_args {
    part_processor_phase phase;
    encoding_context *context;
    const addr_mode_desc_details *addr_mode_details;
    const fcml_st_def_addr_mode_desc *addr_mode_def;
    inst_part *instruction_part;
    fcml_ptr args;
} ipp_encoder_args;

typedef struct ipp_operand_wrapper_args {
    /* This value is set to true if operand is defined for given
     * instruction addressing mode. */
    fcml_bool operand_defined;
    /* Decoder operand addressing.*/
    fcml_st_def_decoded_addr_mode *decoded_addr_mode;
    /* Operands acceptor.*/
    operand_acceptor operand_acceptor;
    /* Function responsible for encoding operand.*/
    operand_encoder operand_encoder;
    /* Index of the operand to encode.*/
    int operand_index;
    /* Operand hints.*/
    fcml_hints hints;
} ipp_operand_wrapper_args;

/* Instruction part encoder.
 * After instruction part is accepted it is encoded to an array of bytes
 * by the encoder. */
typedef fcml_ceh_error (*ipp_encoder)(ipp_encoder_args *args);

/* Instruction part acceptors arguments. */
typedef struct ipp_acceptor_args {
    struct acceptor_ctx *context;
    const fcml_st_instruction *instruction;
    const addr_mode_desc_details *addr_mode_details;
    const fcml_st_def_addr_mode_desc *addr_mode_def;
    fcml_ptr args;
} ipp_acceptor_args;

/* Instruction part acceptor.
 * Responsible for checking if corresponding instruction part can be
 * encoded for the currently encoded instruction. */
typedef fcml_ceh_error (*ipp_acceptor)(ipp_acceptor_args*);

typedef struct operand_encoder_def {
    operand_encoder encoder;
    operand_acceptor acceptor;
    fcml_fp_hts_instruction_hints_calculator hints_calculator;
} operand_encoder_def;

typedef enum ipp_type {
    /* Instruction part processor is responsible only for verifying state,
     * so it doesn't build anything.  */
    IPPT_VERIFIER,
    /** Instruction part processor is responsible for building a part
     * of an instruction. */
    IPPT_ENCODER
} ipp_type;

/* Describes one instruction part processor. */
typedef struct ipp_desc {
    fcml_string ipp_name;
    ipp_encoder encoder;
    ipp_acceptor acceptor;
    ipp_type type;
    fcml_ptr args;
    fcml_fp_env_memory_free_handler args_deallocator;
    /* True if a given instruction part processor should be also invoked
     * for short instruction forms. */
    fcml_bool is_short_form_supported;
} ipp_desc;

typedef struct ipp_factory_args {
    fcml_uint32_t flags;
    const fcml_st_def_instruction_desc *instruction;
    const fcml_st_def_addr_mode_desc *addr_mode;
    /* Pointer to instruction level hints which may
     * be optionally set by IPP builders. */
    fcml_hints *hints;
} ipp_factory_args;

/* Prepares instruction part processor for given instruction's
 * addressing mode. */
typedef ipp_desc (*ipp_factory)(ipp_factory_args*, fcml_ceh_error*);

/* Chain of instruction part processors chosen for addressing mode. */
typedef struct ipp_chain {
    struct ipp_chain *next_processor;
    ipp_desc descriptor;
} ipp_chain;

/* Consists all information needed to encode given
 * instruction addressing mode. */
typedef struct addr_mode_encoding {
    /* Instruction code. */
    fcml_en_instruction instruction;
    /* Mnemonic configuration chosen for given addressing mode.*/
    const fcml_st_mp_mnemonic *mnemonic;
    /* Instruction definition.*/
    const fcml_st_def_addr_mode_desc *addr_mode_desc;
    /* Some pre-calculated information about instruction addressing mode.
     * This structure can be helpful, because some details of the addressing
     * mode can be pre-calculate while addressing mode is processed in
     * initialization mode. So we can get some performance improvements.
     */
    addr_mode_desc_details addr_mode_details;
    /* Chain of instruction part processors registered for
     * instruction addressing mode.
     */
    ipp_chain *ipp_chain;
    /* Number of instruction parts needed to assemble described instruction. */
    fcml_int instruction_parts;
    /* Addressing mode related hints. */
    fcml_hints hints;
    /* True if details are cloned for alternative mnemonics. */
    fcml_bool is_cloned;
} addr_mode_encoding;

typedef struct ipp_chain_builder_out {
    /* Generated instruction part processors chain for given
     * instruction's addressing mode. */
    ipp_chain *ipp_chain;
    /* Instruction level addressing mode related hints. */
    fcml_hints hints;
} ipp_chain_builder_out;

/* Builds a chain of instruction part processors responsible for
 * encoding given instruction's addressing mode. */
typedef fcml_ceh_error (*ipp_chain_builder)(const fcml_st_def_addr_mode_desc*,
        const fcml_st_def_instruction_desc*, ipp_chain_builder_out *out);

/** Used by addressing modes encoding builders to enrich encoders. */
typedef void (*addr_mode_encoding_enricher)(addr_mode_encoding*,
        fcml_ptr args);

static void free_instruction_addr_modes(
        fcml_st_instruction_addr_modes *addr_modes,
        fcml_st_dialect_context_int *dialect_context);

static inline fcml_bool is_short_form(const fcml_st_instruction *instruction,
        const fcml_st_mp_mnemonic *mnemonic);

/* Hints optimizer not to try another addressing mode but
 * to break processing immediately. It can be used in
 * case of incorrect instruction which would fail anyway
 * no matter what configuration was used by the optimizer.
 */
static void break_optimization(encoding_context *context);

/* *************************/
/* DEBUG related functions.*/
/* *************************/

#ifdef FCML_DEBUG

static fcml_char print_data_attr_flags_buff[64];

static fcml_string debug_print_attr_size_flags(fcml_flags flags) {
    int index = 0;
    if(flags == FCML_EN_ASF_ANY) {
        sprintf(print_data_attr_flags_buff, "ANY");
    } else {
        if(flags & FCML_EN_ASF_16) {
            index += sprintf(print_data_attr_flags_buff, "2");
        }
        if(flags & FCML_EN_ASF_32) {
            index += sprintf(print_data_attr_flags_buff + index, "4");
        }
        if(flags & FCML_EN_ASF_64) {
            index += sprintf(print_data_attr_flags_buff + index, "8");
        }
    }
    return print_data_attr_flags_buff;
}

static fcml_char print_data_flags_buff[512];

static fcml_string debug_print_size_flags(
        fcml_st_asm_optimizer_processing_details *size_flags) {

    int index = 0;

    /* Vector length. */
    if(size_flags->vector_length) {
        index += sprintf(print_data_flags_buff, "Vector length: %d, ",
                size_flags->vector_length);
    } else {
        index += sprintf(print_data_flags_buff, "L: NS, ");
    }

    /* Allowed EOSA.*/
    if(size_flags->allowed_eosa.is_set) {
        index += sprintf(print_data_flags_buff + index,
                "Allowed OSA: [%s], ",
                debug_print_attr_size_flags(
                        size_flags->allowed_eosa.flags));
    } else {
        index += sprintf(print_data_flags_buff + index,
                "Allowed OSA: NS, ");
    }

    /* Allowed EASA.*/
    if(size_flags->allowed_easa.is_set) {
        index += sprintf(print_data_flags_buff + index,
                "Allowed ASA: [%s], ", debug_print_attr_size_flags(
                        size_flags->allowed_easa.flags));
    } else {
        index += sprintf(print_data_flags_buff + index,
                "Allowed ASA: NS, ");
    }

    /* Chosen OSA.*/
    index += sprintf(print_data_flags_buff + index, "EOSA: %d, ",
            size_flags->eosa);

    /* Chosen OSA.*/
    index += sprintf(print_data_flags_buff + index, "EASA: %d",
            size_flags->easa);

    return print_data_flags_buff;
}

#endif

/***********************************/
/* Error handling helper functions */
/***********************************/

static void move_errors(struct error_container *destination,
        struct error_container *source) {
    fcml_fn_ceh_move_errors(&destination->errors, &source->errors);
}

static void free_errors(struct error_container *errors) {
    if (errors) {
        fcml_fn_ceh_free_errors_only(&errors->errors);
    }
}

static fcml_bool has_errors(struct error_container *errors) {
    return errors != NULL && errors->errors.errors != NULL;
}

static void add_error(struct error_container *errors, fcml_string message,
        fcml_ceh_error error_code) {
    if (errors->enabled) {
        fcml_bool add_error = FCML_TRUE;
        fcml_st_ceh_error_info *current = errors->errors.errors;
        // Only one error message is currently allowed.
        while (current) {
            if (current->code == FCML_EN_CEH_EL_ERROR) {
                add_error = FCML_FALSE;
                break;
            }
            current = current->next_error;
        }
        if (add_error) {
            fcml_fn_ceh_add_error(&errors->errors, message, error_code,
                    FCML_EN_CEH_EL_ERROR);
        }
    }
}

enum fcml_ien_asm_comparator_type {
    FCML_IEN_CT_EQUAL, FCML_IEN_CT_EQUAL_OR_LESS,
};

static void clean_context(encoding_context *context) {
    fcml_fn_env_memory_clear(&(context->optimizer_processing_details),
            sizeof(fcml_st_asm_optimizer_processing_details));
    /* Clears segment override set by acceptor functions.*/
    context->segment_override.reg = 0;
    context->segment_override.size = FCML_DS_UNDEF;
    context->segment_override.type = FCML_REG_UNDEFINED;
    context->segment_override.x64_exp = FCML_FALSE;
}

static fcml_st_memory_stream inst_part_stream(inst_part *inst_part) {
    fcml_st_memory_stream stream;
    stream.base_address = &(inst_part->code);
    stream.offset = 0;
    stream.size = sizeof(inst_part->code);
    return stream;
}

static fcml_usize get_effective_address_size(encoding_context *context) {
    if (context->optimizer_processing_details.easa) {
        return context->optimizer_processing_details.easa;
    }
    return context->assembler_context->entry_point.address_size_attribute;
}

static fcml_usize calculate_operand_size(const fcml_st_instruction *instruction,
        memory_data_size_calculator ds_calculator,
        fcml_ptr ds_calculator_args, fcml_usize size_operator,
        fcml_uint8_t encoded_size_operator) {
    /* Remember, some addressing modes use registers that do not match
     * memory data size. These addressing modes can accept unknown operand
     * size so we do not calculate size operators for them, because such
     * calculated size wouldn't match data size anyway.
     */
    if (size_operator == FCML_OS_UNDEFINED
            && !FCML_IS_EOS_OPT(encoded_size_operator)) {
        if (ds_calculator) {
            size_operator = ds_calculator(instruction, ds_calculator_args);
        }
    }
    return size_operator;
}

static void handle_segment_override(operand_encoder_args *args) {
    const fcml_st_operand *operand = args->operand;

    const fcml_st_register *base = &(operand->address.effective_address.base);
    const fcml_st_segment_selector *segment_selector =
            &(operand->address.segment_selector);
    const fcml_st_register *segment_register =
            &(segment_selector->segment_selector);

    if (segment_register->type == FCML_REG_SEG) {
        if (segment_register->type == FCML_REG_SEG) {
            if (!(args->addr_mode_def->instruction_group & FCML_AMT_BRANCH)
                    && !(base->type == FCML_REG_GPR
                            && (base->reg == FCML_REG_BP
                                    || base->reg == FCML_REG_SP))) {
                if (segment_register->reg != FCML_REG_DS) {
                    args->context->segment_override = *segment_register;
                }
            }
        }
    }
}

fcml_usize fcml_ifn_asm_non_standard_attribute_size_calculator(
        const fcml_st_entry_point *entry_point, fcml_usize operand_size, fcml_usize l,
        fcml_usize u, fcml_ceh_error *error) {
    fcml_usize attribute_size = 0;
    if (operand_size == l) {
        attribute_size = 16;
    } else if (operand_size == u) {
        if (entry_point->operand_size_attribute == FCML_DS_16) {
            FCML_TRACE_MSG("Addressing mode not available for 16 bit EOSA.");
            *error = FCML_CEH_GEC_INVALID_OPPERAND_SIZE;
        } else {
            attribute_size = entry_point->operand_size_attribute;
        }
    }
    return attribute_size;
}

/* TODO: Refactoring - struct for bcast fields. Too complicated. */
static fcml_ceh_error decode_dynamic_operand_size_bcast(
        encoding_context *context,
        fcml_uint8_t encoded_operand_size, fcml_usize operand_size,
        const fcml_nuint8_t *bcast, fcml_usize element_size,
        fcml_usize *encoded_data_size,
        enum fcml_ien_asm_comparator_type comparator) {

    const fcml_st_entry_point *entry_point =
            &(context->assembler_context->entry_point);
    fcml_st_asm_optimizer_processing_details *flags =
            &(context->optimizer_processing_details);
    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
    fcml_usize effective_address_size = FCML_DS_UNDEF;
    fcml_usize effective_operand_size = FCML_DS_UNDEF;
    fcml_usize vector_length = FCML_DS_UNDEF;

    fcml_uint8_t encoded_static_operand_size =
            FCML_GET_OS(encoded_operand_size);

    if ((operand_size == FCML_OS_UNDEFINED)
            && FCML_IS_EOS_OPT(encoded_operand_size)) {
        /* Operand size is optional and does not have to be specified for
         * the addressing mode. */
        return error;
    }

    if (encoded_data_size != NULL) {
        *encoded_data_size = operand_size;
    }

    switch (encoded_static_operand_size) {
    case FCML_EOS_UNDEFINED:
        break;
    case FCML_EOS_L:
        vector_length = (bcast && bcast->is_not_null) ?
                bcast->value * element_size : operand_size;
        if (!fcml_fn_utils_validate_vector_len(vector_length)) {
            error = FCML_CEH_GEC_INVALID_OPPERAND_SIZE;
        }
        break;
    case FCML_EOS_EASA:
        if (operand_size == FCML_DS_16 || operand_size == FCML_DS_32
                || operand_size == FCML_DS_64) {
            effective_address_size = operand_size;
        } else {
            FCML_TRACE_MSG("Unsupported encoded EOSA size.");
            error = FCML_CEH_GEC_INVALID_OPPERAND_SIZE;
        }
        break;
    case FCML_EOS_EOSA:
        if (operand_size == FCML_DS_16 || operand_size == FCML_DS_32
                || operand_size == FCML_DS_64) {
            effective_operand_size = operand_size;
        } else {
            FCML_TRACE_MSG("Unsupported encoded EASA size.");
            error = FCML_CEH_GEC_INVALID_OPPERAND_SIZE;
        }
        break;
    case FCML_EOS_14_28:
        effective_operand_size =
                fcml_ifn_asm_non_standard_attribute_size_calculator(entry_point,
                        operand_size, 14 * 8, 28 * 8, &error);
        break;
    case FCML_EOS_32_64:
        effective_operand_size =
                fcml_ifn_asm_non_standard_attribute_size_calculator(entry_point,
                        operand_size, 16 * 8, 32 * 8, &error);
        break;
    case FCML_EOS_94_108:
        effective_operand_size =
                fcml_ifn_asm_non_standard_attribute_size_calculator(entry_point,
                        operand_size, 94 * 8, 108 * 8, &error);
        break;
    case FCML_EOS_FPI:
    case FCML_EOS_FP:
        /* Far pointer indirect.*/
        effective_operand_size = operand_size - FCML_DS_16;
        break;
    default:
        if (operand_size || !FCML_IS_EOS_OPT(encoded_operand_size)) {
            if (comparator == FCML_IEN_CT_EQUAL) {
                if (bcast && bcast->is_not_null) {
                    // Memory operand size in case of broadcast is always same
                    // as element size (input size) so the real memory operand
                    // size is multiplication of the element size and broadcast
                    // multiplier.
                    if (operand_size != element_size) {
                        FCML_TRACE("Unsupported broadcast operand size. " \
                                "Expected %d got %d.", operand_size,
                                encoded_static_operand_size * 8);
                        error = FCML_CEH_GEC_INVALID_OPPERAND_SIZE;
                    } else if (bcast->value * element_size !=
                            encoded_static_operand_size * 8) {
                        error = FCML_CEH_GEC_INVALID_OPPERAND_SIZE;
                    }
                } else if (encoded_static_operand_size * 8 != operand_size) {
                    FCML_TRACE("Unsupported operand size. Expected %d got %d.",
                            operand_size, encoded_static_operand_size * 8);
                    error = FCML_CEH_GEC_INVALID_OPPERAND_SIZE;
                }
            } else {
                if (encoded_static_operand_size * 8 < operand_size) {
                    FCML_TRACE("Unsupported operand size. Expected greater " \
                            "or equal to %d got %d.", operand_size,
                            encoded_static_operand_size * 8);
                    error = FCML_CEH_GEC_INVALID_OPPERAND_SIZE;
                } else {
                    if (encoded_data_size != NULL) {
                        *encoded_data_size = encoded_static_operand_size * 8;
                    }
                }
            }
        }
        break;
    }

    if (!error) {
        /* If size is not set yet it sets it to the calculated
         * value, but if it's already set it only checks if the newly
         * calculated one has the same size.
         */
        if (vector_length) {
            if (flags->vector_length && flags->vector_length != vector_length) {
                /* All dynamic operands have to be of the same size.*/
                FCML_TRACE("Vector length differs expected %d got %d.",
                        flags->vector_length, vector_length);
                error = FCML_CEH_GEC_INVALID_OPPERAND_SIZE;
            } else {
                flags->vector_length = vector_length;
            }
        }
    }

    return error;
}

static fcml_ceh_error decode_dynamic_operand_size(encoding_context *context,
        fcml_uint8_t encoded_operand_size, fcml_usize operand_size,
        fcml_usize *encoded_data_size,
        enum fcml_ien_asm_comparator_type comparator) {
    return decode_dynamic_operand_size_bcast(context,
            encoded_operand_size, operand_size, NULL, 0,
            encoded_data_size, comparator);
}

/**
 * Sets new vector length. If there is one already set it cannot be overridden.
 */
static fcml_bool set_vector_length(fcml_usize *dest_vector_length,
        fcml_flags vector_length) {
    fcml_bool result = FCML_TRUE;
    if (vector_length != FCML_DS_UNDEF) {
        if (*dest_vector_length) {
            if (*dest_vector_length != vector_length) {
                return FCML_FALSE;
            }
        } else {
            *dest_vector_length = vector_length;
        }
    }
    return result;
}

/**
 * Sets size flags that are needed to assemble processed instruction.
 * This function sets new set of flags or reduces existing set.
 */
static fcml_bool set_size_flags(fcml_st_nullable_size_flags *flags,
        fcml_flags allowed_flags) {
    /* If there are flags already set, just reduce them. */
    if (flags->is_set) {
        /* Common set of existing flags and the new ones. */
        fcml_flags reduced_flags = flags->flags & allowed_flags;
        if (!reduced_flags) {
            /* At least one allowed ASA size has to be left after
             * masking existing flags.
             */
            return FCML_FALSE;
        }
        /* Set new set of flags, take into account that these might be a
         * subset of existing ones.
         */
        flags->flags = reduced_flags;
    } else {
        flags->flags = allowed_flags;
        flags->is_set = FCML_TRUE;
    }
    return FCML_TRUE;
}

static inline fcml_flags allowed_flags_for_op_mode(const fcml_st_entry_point *entry_point) {
    switch (entry_point->op_mode) {
    case FCML_OM_64_BIT:
        return FCML_EN_ASF_ALL;
    case FCML_OM_32_BIT:
        return FCML_EN_ASF_16 | FCML_EN_ASF_32;
    case FCML_OM_16_BIT:
        return FCML_EN_ASF_16;
    }
    return FCML_EN_ASF_ANY;
}

static fcml_bool accept_data_size(struct acceptor_ctx *context,
        const fcml_st_def_addr_mode_desc *addr_mode_desc,
        fcml_uint8_t encoded_operand_size,
        fcml_usize operand_size, enum fcml_ien_asm_comparator_type comparator) {

    const fcml_st_entry_point *entry_point = context->entry_point;
    struct acceptor_optimizer_ctx *optimizer = &(context->optimizer_ctx);

    fcml_flags osa_flags = FCML_EN_ASF_ANY;
    fcml_flags asa_flags = FCML_EN_ASF_ANY;

    /* True if allowed addressing modes have been accepted. */
    fcml_bool accepted = FCML_TRUE;

    if ((operand_size == FCML_OS_UNDEFINED) &&
            FCML_IS_EOS_OPT(encoded_operand_size)) {
        /* If operand size is optional, we do not need to accept it.*/
        return FCML_TRUE;
    }

    switch (FCML_GET_OS(encoded_operand_size)) {
    case FCML_EOS_UNDEFINED:
        break;
    case FCML_EOS_L:
        if (FCML_DEF_PREFIX_L_IGNORE_OS(addr_mode_desc->allowed_prefixes)) {
            accepted = (operand_size == entry_point->operand_size_attribute);
        } else {
            accepted = ((operand_size == FCML_DS_128) ||
                    (operand_size == FCML_DS_256) ||
                    (operand_size == FCML_DS_512));
        }
        break;
    case FCML_EOS_EASA:
        if (entry_point->op_mode == FCML_OM_32_BIT) {
            accepted = ((operand_size == FCML_DS_16) ||
                    (operand_size == FCML_DS_32));
        } else {
            accepted = ((operand_size == FCML_DS_32) ||
                    (operand_size == FCML_DS_64));
        }
        if (accepted) {
            asa_flags = (operand_size / FCML_ASM_FCF);
        }
        break;
    case FCML_EOS_EOSA:
        if (entry_point->op_mode == FCML_OM_32_BIT) {
            accepted = ((operand_size == FCML_DS_16) ||
                    (operand_size == FCML_DS_32));
        } else {
            accepted = ((operand_size == FCML_DS_16) ||
                    (operand_size == FCML_DS_32) ||
                    (operand_size == FCML_DS_64));
        }
        if (accepted) {
            osa_flags = (operand_size / FCML_ASM_FCF);
        }
        break;
    case FCML_EOS_14_28:
        if (operand_size == 14 * 8) {
            osa_flags |= FCML_EN_ASF_16;
        } else if (operand_size == 28 * 8) {
            osa_flags |= (FCML_EN_ASF_32 | FCML_EN_ASF_64);
        } else {
            accepted = FCML_FALSE;
        }
        break;
    case FCML_EOS_32_64:
        if ((operand_size == FCML_DS_16 * 2) || (FCML_DS_32 * 2) ||
                (FCML_DS_64 * 2)) {
            osa_flags = (operand_size / 2 / FCML_ASM_FCF);
        } else {
            accepted = FCML_FALSE;
        }
        break;
    case FCML_EOS_94_108:
        if (operand_size == 94 * 8) {
            osa_flags |= FCML_EN_ASF_16;
        } else if (operand_size == 108 * 8) {
            osa_flags |= (FCML_EN_ASF_32 | FCML_EN_ASF_64);
        } else {
            accepted = FCML_FALSE;
        }
        break;
    case FCML_EOS_FPI:
    case FCML_EOS_FP:
        /* Far pointer indirect.*/
        switch (operand_size) {
        case FCML_DS_16 + FCML_DS_16:
            osa_flags |= FCML_EN_ASF_16;
            break;
        case FCML_DS_32 + FCML_DS_16:
            osa_flags |= FCML_EN_ASF_32;
            break;
        case FCML_DS_64 + FCML_DS_16:
            osa_flags |= FCML_EN_ASF_64;
            break;
        default:
            accepted = FCML_FALSE;
        }
        break;
    default:
        if (comparator == FCML_IEN_CT_EQUAL) {
            accepted = (FCML_GET_OS(encoded_operand_size) * 8 == operand_size);
        } else {
            accepted = (FCML_GET_OS(encoded_operand_size) * 8 >= operand_size);
        }
        if (!accepted && FCML_IS_EOS_OPT(encoded_operand_size) &&
                operand_size == 0) {
            /* Operand size is optional, so return TRUE anyway.*/
            accepted = FCML_TRUE;
        }
        break;
    }

    if (osa_flags && !set_size_flags(&(optimizer->allowed_eosa), osa_flags)) {
        accepted = FCML_FALSE;
    }

    if (asa_flags && !set_size_flags(&(optimizer->allowed_easa), asa_flags)) {
        accepted = FCML_FALSE;
    }

    return accepted;
}

/*********************************
 * Operand encoders.
 *********************************/

/*******************/
/* Immediate value */
/*******************/

/**
 * Converts an integer value being encoded to fit a destination IMM field.
 *
 * In general signed integer values are expected here, but of course user
 * has a freedom to provide unsigned values too. The values also do not have
 * to be of the same size as the IMM fields. Consequently, if size does not
 * match a conversion has to be carried out. It introduces an interesting
 * kind of problem. While the integer value is of the same size (in bytes) as
 * the destination IMM field or is smaller, then we can convert it without any
 * problems, but things get a bit more complicated when the value is stored
 * in a bigger field. For instance, in case when IMM field is 32-bit long and
 * the provided value has 64-bits. If we were sure that the provided sign was
 * correct we could do the needed conversions in the similar way as in the
 * previous case. Unfortunately it's not always the case. Consider parsing of
 * the following instruction:
 *
 * adc rbp,0ffffffffffffffffh
 *
 * (Disassembler may be configured to render sign-extended values)
 *
 * In such a case it's the parser that is responsible for converting the
 * given literal to an integer value. The parser is context less so
 * in case of hexadecimal values it's unable to infer the correct
 * sign. In this particular case the unsigned 64-bit integer is used
 * by the parser to represent the value while it should be considered
 * as signed one in this particular context - but we know that being
 * aware of the context. The algorithm here is a result of a trade off,
 * just to handle such cases correctly. Having said that, it's a subjective
 * decision and there is a chance that the algorithm will change in
 * the future.
 */
static fcml_bool conv_int_and_set_flag(const fcml_st_integer *value,
        fcml_st_integer *imm, fcml_usize imm_size, fcml_usize exp_size,
        fcml_flags flag, fcml_flags *flags) {
    /* exp_size - potentially sign-extended size expected by an instruction */
    fcml_st_integer tmp = *value;
    if (!exp_size) {
       /* In this case immediate values are not sign-extended
        * so integer value size expected by an instruction in the same
        * as the IMM field size. */
        exp_size = imm_size;
    } else {
        /* Real size is specified so most likely it's an instruction
         * which sign-extends the integer values from IMM fields before
         * usage. */
        if (tmp.size == exp_size) {
            /* Sizes are the same, so it's probably the case where
             * disassembler rendered sign-extended value in the first
             * place. So with high certainty we can treat it as a
             * signed value. */
            tmp.is_signed = FCML_TRUE;
        }
    }
    fcml_ceh_error error = fcml_fn_utils_conv_int_to_int(&tmp, imm, exp_size,
            imm_size);
    if (!error && flags) {
        *flags |= flag;
    }
    return !error;
}

/*
 * Checks if given integer encoded in fcml_st_integer structure fits
 * IMM field of given size. The rules of encoding such values
 * in respect to their signs and sizes are not so obvious and
 * to some respect subjective, so there is a risk of changes
 * in the future. Considering the fact that the accepting phase where
 * this function is used is in general a kind of optimization in order
 * to reject addressing modes which cannot be used to encode given instruction
 * as soon as possible it's not required to be 100% accurate. That is, it
 * cannot return false negatives but false positives are allowed because
 * such addressing modes will be rejected by encoders anyway.
 * Consequently, this implementation may return false positives in
 * some rare cases but it is fast and does not duplicate the logic
 * from encoding phase. It just rejects addressing modes which
 * are explicitly incorrect for given values.
 */
static fcml_bool int_fit_imm(const fcml_st_integer *value,
        fcml_usize imm_size) {
    fcml_uint64_t i64;
    fcml_uint32_t i32;
    fcml_uint16_t i16;
    /* Values which occupies less or same number of bytes that IMM
     * value always fits. */
    if (value->size > imm_size) {
        switch (imm_size) {
        case FCML_DS_8:
            switch (value->size) {
            case FCML_DS_64:
                i64 = (fcml_uint64_t)(value->int64 & 0xFFFFFFFFFFFFFF00UL);
                return i64 == 0x0UL || i64 == 0xFFFFFFFFFFFFFF00UL;
            case FCML_DS_32:
                i32 = (fcml_uint32_t)(value->int32 & 0xFFFFFF00);
                return i32 == 0 || i32 == 0xFFFFFF00;
            case FCML_DS_16:
                i16 = (fcml_uint16_t)(value->int16 & 0xFF00);
                return i16 == 0 || i16 == 0xFF00;
            }
            break;
        case FCML_DS_16:
            switch (value->size) {
            case FCML_DS_64:
                i64 = (fcml_uint64_t)(value->int64 & 0xFFFFFFFFFFFF0000UL);
                return i64 == 0x0UL || i64 == 0xFFFFFFFFFFFF0000UL;
            case FCML_DS_32:
                i32 = (fcml_uint32_t)(value->int32 & 0xFFFF0000);
                return i32 == 0 || i32 == 0xFFFF0000;
            }
            break;
        case FCML_DS_32:
            if (value->size == FCML_DS_64) {
                i64 = (fcml_uint64_t)(value->int64 & 0xFFFFFFFF00000000UL);
                return i64 == 0x0UL || i64 == 0xFFFFFFFF00000000UL;
            }
            break;
        }
    }
    return FCML_TRUE;
}

static fcml_ceh_error operand_acceptor_imm(operand_acceptor_args *args) {
    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
    struct acceptor_ctx *context = args->context;
    const fcml_st_operand *operand = args->operand;

    if (operand->type == FCML_OT_IMMEDIATE) {
        const fcml_st_def_tma_imm *addr_mode_args =
                (fcml_st_def_tma_imm*)args->addr_mode->addr_mode_args;
        const fcml_st_integer *imm = &(operand->immediate);

        /* EOSA flags potentially allowed for given addressing mode. */
        fcml_flags accepted_flags = 0;

        fcml_flags flags = context->optimizer_ctx.allowed_eosa.flags;
        if (!flags) {
            flags = allowed_flags_for_op_mode(context->entry_point);
        }

        fcml_uint8_t imm_size = addr_mode_args->encoded_size;
        fcml_bool fits = FCML_FALSE;

        /* At this point some EASA flags may be already rejected, we have to
         * take it into account and check these which are still valid.
         */
        if (imm_size != FCML_EOS_EOSA) {
            fits = int_fit_imm(imm, FCML_GET_OS(imm_size) * 8);
        } else if (imm_size == FCML_EOS_EOSA) {
            if ((flags & FCML_EN_ASF_16) && int_fit_imm(imm, FCML_DS_16)) {
                accepted_flags |= FCML_EN_ASF_16;
                fits |= FCML_TRUE;
            }
            if ((flags & FCML_EN_ASF_32) && int_fit_imm(imm, FCML_DS_32)) {
                accepted_flags |= FCML_EN_ASF_32;
                fits |= FCML_TRUE;
            }
            if ((flags & FCML_EN_ASF_64) && (int_fit_imm(imm, FCML_DS_32)
                    || addr_mode_args->is_64bit_imm_allowed)) {
                accepted_flags |= FCML_EN_ASF_64;
                fits |= FCML_TRUE;
            }
        }

        if (!fits || (accepted_flags && !set_size_flags(
                &(context->optimizer_ctx.allowed_eosa), accepted_flags))) {
            FCML_TRACE_MSG("Accept IMM: Can not accept IMM value.");
            error = FCML_CEH_GEC_INVALID_OPPERAND;
        }

        return error;
    } else {
        error = FCML_CEH_GEC_INVALID_OPPERAND;
    }

    return error;
}

static fcml_ceh_error operand_encoder_imm(operand_encoder_args *args) {
    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

    if (args->phase == IPPP_FIRST_PHASE) {
        fcml_st_def_tma_imm *addr_mode_args =
                (fcml_st_def_tma_imm*)args->addr_mode->addr_mode_args;
        /* Encoded size of IMM field. */
        fcml_uint8_t enc_imm_size = addr_mode_args->encoded_size;
        /* Encoded size of the value while it's interpreted by an instruction.
         * In some cases instruction extends the value encoded
         * in IMM field to larger values. For instance an 8-bit integer
         * value may be sign extended to 32-bites before its use. */
        fcml_uint8_t enc_ext_size = addr_mode_args->encoded_ex_size;
        fcml_usize eosa = args->context->optimizer_processing_details.eosa;

        /* Remember that only one addressing mode of MOV instruction for
         * 64 bits mode can encode IMM64. */
        fcml_usize imm_size_for_eosa = eosa;
        if (!addr_mode_args->is_64bit_imm_allowed && eosa == FCML_DS_64) {
            imm_size_for_eosa = FCML_DS_32;
        }

        if ((enc_imm_size == FCML_EOS_EOSA || enc_ext_size == FCML_EOS_EOSA)
                && !eosa) {
            FCML_TRACE_MSG("EOSA size not set! Processing failed.");
            return FCML_CEH_GEC_INTERNAL_ERROR;
        }

        fcml_bool fits = FCML_FALSE; /* True if offset fits IMM field. */
        const fcml_st_integer *imm = &(args->operand->immediate);

        fcml_usize imm_size = enc_imm_size == FCML_EOS_EOSA ?
                imm_size_for_eosa : FCML_GET_OS(enc_imm_size) * 8;
        fcml_usize operand_size = enc_ext_size == FCML_EOS_EOSA ?
                eosa : FCML_GET_OS(enc_ext_size) * 8;

        fcml_st_integer dest_imm;
        fits = conv_int_and_set_flag(imm, &dest_imm, imm_size, operand_size, 0, NULL);
        if (fits) {
            inst_part *operand_enc = args->operand_enc;
            fcml_st_memory_stream stream = fcml_fn_stream_init(
                    &(operand_enc->code), 0, sizeof(operand_enc->code));
            error = fcml_fn_utils_encode_integer(&stream, &dest_imm);
            if (!error) {
                operand_enc->code_length = stream.offset;
            }
        } else {
            error = FCML_CEH_GEC_VALUE_OUT_OF_RANGE;
        }
    }

    return error;
}

/*********************/
/* Explicit register */
/*********************/

static fcml_ceh_error operand_acceptor_explicit_reg(
        operand_acceptor_args *args) {
    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
    fcml_st_def_tma_explicit_reg *addr_mode_args =
            (fcml_st_def_tma_explicit_reg*)args->addr_mode->addr_mode_args;
    const fcml_st_operand *operand = args->operand;

    if (operand->type != FCML_OT_REGISTER
            || operand->reg.type != addr_mode_args->reg_type
            || operand->reg.reg != addr_mode_args->reg_num
            || !accept_data_size(args->context, args->addr_mode_desc,
                    addr_mode_args->encoded_reg_size,
                    operand->reg.size, FCML_IEN_CT_EQUAL)) {
        error = FCML_CEH_GEC_INVALID_OPPERAND;
    }

    return error;
}

/* Example: FCML_OP_EXPLICIT_REG(FCML_REG_GPR, FCML_REG_AL, FCML_EOS_BYTE)*/
static fcml_ceh_error operand_encoder_explicit_reg(operand_encoder_args *args) {
    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
    if (args->phase == IPPP_FIRST_PHASE) {
        fcml_st_def_tma_explicit_reg *addr_mode_args =
                (fcml_st_def_tma_explicit_reg*) args->addr_mode->addr_mode_args;
        const fcml_st_register *reg = &(args->operand->reg);
        /* Encode IMM.*/
        fcml_usize encoded_size;
        error = decode_dynamic_operand_size(args->context,
                addr_mode_args->encoded_reg_size, reg->size, &encoded_size,
                FCML_IEN_CT_EQUAL);
    }
    return error;
}

/*******************/
/* Opcode register */
/*******************/

static fcml_ceh_error operand_acceptor_opcode_reg(operand_acceptor_args *args) {

    const fcml_st_operand *operand = args->operand;
    fcml_st_def_tma_opcode_reg *addr_mode_args =
            (fcml_st_def_tma_opcode_reg*) args->addr_mode->addr_mode_args;

    if (operand->type != FCML_OT_REGISTER
            || operand->reg.type != addr_mode_args->reg_type) {
        return FCML_CEH_GEC_INVALID_OPPERAND;
    }

    if (!accept_data_size(args->context, args->addr_mode_desc,
            addr_mode_args->encoded_reg_size,
            operand->reg.size, FCML_IEN_CT_EQUAL)) {
        return FCML_CEH_GEC_INVALID_OPPERAND;
    }

    return FCML_CEH_GEC_NO_ERROR;
}

static fcml_ceh_error operand_encoder_opcode_reg(operand_encoder_args *args) {
    const fcml_st_operand *operand = args->operand;
    encoding_context *context = args->context;
    if (args->phase == IPPP_FIRST_PHASE) {
        if (operand->reg.reg > 7) {
            context->opcode_reg.opcode_reg = operand->reg.reg - 8;
            context->opcode_reg.ext_b = FCML_TRUE;
        } else {
            context->opcode_reg.opcode_reg = operand->reg.reg;
        }
        if (context->assembler_context->entry_point.op_mode == FCML_OM_64_BIT) {
            context->reg_opcode_needs_rex = operand->reg.x64_exp;
        }
    }
    return FCML_CEH_GEC_NO_ERROR;
}

/***********************************/
/* Immediate relative displacement */
/***********************************/

static fcml_ceh_error operand_acceptor_immediate_dis_relative(
        operand_acceptor_args *args) {
    /* In 64-bit mode OSA is fixed at 64 bits. Just in case,
     * because addressing mode acceptor is responsible for interpreting
     * FCML_DEF_OPCODE_FLAGS_FORCE_64BITS_EOSA flag and forcing appropriate
     * OSA size. */
    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
    struct acceptor_ctx *context = args->context;
    const fcml_st_operand *operand = args->operand;
    fcml_bool is_offset = (operand->type == FCML_OT_ADDRESS
            && operand->address.address_form == FCML_AF_OFFSET);
    fcml_bool is_imm = (operand->type == FCML_OT_IMMEDIATE);

    if (is_imm || is_offset) {
        fcml_flags flags = 0;
        if (context->entry_point->op_mode == FCML_OM_64_BIT) {
            flags = FCML_EN_ASF_64;
        } else {
            fcml_sf_def_tma_immediate_dis_relative *rel_args =
                    (fcml_sf_def_tma_immediate_dis_relative*)
                    args->addr_mode->addr_mode_args;
            if (is_imm || (rel_args->encoded_size != FCML_EOS_UNDEFINED)) {
                /* In case of IMM operand size operator is not available, so we
                 * have to try both operand size attributes.
                 */
                flags = FCML_EN_ASF_32 | FCML_EN_ASF_16;
            } else {
                fcml_usize size_operator = operand->address.size_operator;
                switch (size_operator) {
                case FCML_DS_UNDEF:
                    flags = FCML_EN_ASF_32 | FCML_EN_ASF_16;
                    break;
                case FCML_DS_16:
                    flags = FCML_EN_ASF_16;
                    break;
                case FCML_DS_32:
                    flags = FCML_EN_ASF_32;
                    break;
                case FCML_DS_64:
                    /* We are not in 64-bit mode. */
                    error = FCML_CEH_GEC_INVALID_OPPERAND;
                    break;
                }
            }
        }
        if (!set_size_flags(&(context->optimizer_ctx.allowed_eosa), flags)) {
            error = FCML_CEH_GEC_INVALID_OPPERAND;
        }
    } else {
        error = FCML_CEH_GEC_INVALID_OPPERAND;
    }

    return error;
}

static fcml_ceh_error convert_to_rel(fcml_st_integer *value,
        fcml_usize expected_size, fcml_uint8_t encoded_rel_size) {
    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
    if (encoded_rel_size == FCML_EOS_BYTE) {
        error = fcml_fn_utils_conv_int_to_int(value, value,
                expected_size, FCML_DS_8);
        if (error) {
            error = FCML_CEH_GEC_INVALID_OPPERAND_SIZE;
        }
    }
    return error;
}

static int disp_size_for_enc_rel(fcml_usize osa, fcml_uint8_t rel_size) {
    if (rel_size == FCML_EOS_UNDEFINED) {
        return (osa == FCML_DS_64) ? 4 : osa / 8;
    } else {
        return rel_size;
    }
}

/* Immediate address can be provided as an immediate operand value
 * or address offset. Both of them have to be converted to an integer
 * value for further processing.
 * */
static fcml_ceh_error convert_operand_to_offset(
        const fcml_st_operand *operand, fcml_st_integer *offset,
        fcml_usize osa) {

    fcml_st_integer addr = { 0 };

    if (operand->type == FCML_OT_IMMEDIATE) {
        addr = operand->immediate;
    } else if (operand->type == FCML_OT_ADDRESS &&
            operand->address.address_form == FCML_AF_OFFSET) {
        fcml_ceh_error error = fcml_fn_utils_offset_to_integer(
                &(operand->address.offset), &addr);
        if (error) {
            return error;
        }
    } else {
        return FCML_CEH_GEC_INVALID_OPPERAND;
    }

    if (fcml_fn_utils_conv_int_to_int(&addr, offset, osa, osa)) {
        return FCML_CEH_GEC_INVALID_OPPERAND;
    }

    return FCML_CEH_GEC_NO_ERROR;
}

/* It's implemented as post processor because final instruction size is
 * needed to calculate displacements. */
static fcml_ceh_error ipp_imm_dis_rel_post_processor(
        encoding_context *context, inst_part *inst_part,
        fcml_ptr args, fcml_uint8_t enc_rel_size) {

    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

    /* Sanity checks */
    if (enc_rel_size != FCML_EOS_UNDEFINED && enc_rel_size != FCML_EOS_BYTE) {
        FCML_TRACE_MSG("Wrong size of encoded relative address.");
        return FCML_CEH_GEC_INVALID_OPPERAND;
    } else if (FCML_IS_NULL(context->instruction_size)) {
        /* Should never happened.*/
        return FCML_CEH_GEC_INTERNAL_ERROR;
    }

    /* Optimizer is responsible for setting optimal OSA value.*/
    fcml_usize osa = context->optimizer_processing_details.eosa;

    fcml_st_integer offset = { 0 };
    error = convert_operand_to_offset((fcml_st_operand*) args, &offset, osa);
    if (error) {
        return error;
    }

    fcml_st_integer disp = {0};
    fcml_uint8_t inst_size = context->instruction_size.value;
    fcml_ip ip  = context->assembler_context->entry_point.ip;

    disp.is_signed = FCML_TRUE;

    int disp_size = disp_size_for_enc_rel(osa, enc_rel_size);
    switch (osa) {
        case FCML_DS_16: {
            /* There are some inconsistencies around this addressing mode
             * in the Intel manual. The solution applied here is the result of
             * checking how processors tend to interpret it in practice. In
             * general it's consistent with the pseudo-code for the JMP
             * instruction in the Intel manual. */
            fcml_int16_t offset16 = offset.int16;
            /* 16 higher bits of 32-bit EIP should be cut off here. */
            fcml_int32_t eip = (fcml_int32_t) (ip + inst_size + disp_size);
            fcml_int16_t rel16 = offset16 - (fcml_int16_t)eip;
            disp.int16 = rel16;
            disp.size = FCML_DS_16;
            error = convert_to_rel(&disp, FCML_DS_16, enc_rel_size);
            break;
        }
        case FCML_DS_32: {
            fcml_int32_t offset32 = offset.int32;
            fcml_int32_t eip = (fcml_int32_t) (ip + inst_size + disp_size);
            disp.int32 = offset32 - eip;
            disp.size = FCML_DS_32;
            error = convert_to_rel(&disp, FCML_DS_32, enc_rel_size);
            break;
        }
        case FCML_DS_64: {
            fcml_int64_t offset64 = offset.int64;
            fcml_int64_t rip = ip + inst_size + disp_size;
            fcml_int64_t rel = offset64 - rip;
            if (!safe_cast_i6432(rel)) {
                return FCML_CEH_GEC_INVALID_OPPERAND;
            }
            disp.int32 = (fcml_int32_t)(offset64 - rip);
            disp.size = FCML_DS_32;
            error = convert_to_rel(&disp, FCML_DS_32, enc_rel_size);
            break;
        }
    }

    if (error) {
        if (error == FCML_CEH_GEC_INVALID_OPPERAND_SIZE &&
                enc_rel_size == FCML_EOS_BYTE) {
            /* In this case we can hint optimizer not to try different
               ASA/OSA combinations, because it doesn't make sense
               anyway. They will fail too. */
            break_optimization(context);
        }
        return error;
    }

    /* Encode ModR/M and displacement.*/
    fcml_st_memory_stream stream = inst_part_stream(inst_part);
    fcml_fn_utils_encode_integer(&stream, &disp);
    inst_part->code_length = stream.offset;

    return error;
}

static fcml_ceh_error ipp_imm_disp_rel_post_processor_8(
        encoding_context *context, inst_part *instruction_part,
        fcml_ptr post_processor_args) {
    return ipp_imm_dis_rel_post_processor(context, instruction_part,
            post_processor_args, FCML_EOS_BYTE);
}

static fcml_ceh_error ipp_imm_disp_rel_post_processor_undef(
        encoding_context *context, inst_part *instruction_part,
        fcml_ptr post_processor_args) {
    return ipp_imm_dis_rel_post_processor(context, instruction_part,
            post_processor_args, FCML_EOS_UNDEFINED);
}

static fcml_ceh_error operand_encoder_imm_disp_relative(
        operand_encoder_args *args) {

    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
    inst_part *operand_enc = args->operand_enc;

    if (args->phase == IPPP_SECOND_PHASE) {
        fcml_sf_def_tma_immediate_dis_relative *addr_mode_args =
                (fcml_sf_def_tma_immediate_dis_relative*)
                args->addr_mode->addr_mode_args;

        operand_enc->code_length = 0;

        if (addr_mode_args->encoded_size == FCML_EOS_BYTE) {
            operand_enc->post_processor = ipp_imm_disp_rel_post_processor_8;
        } else if (addr_mode_args->encoded_size == FCML_EOS_UNDEFINED) {
            operand_enc->post_processor = ipp_imm_disp_rel_post_processor_undef;
        } else {
            /* Unsupported operand size encoded in operand arguments.*/
            error = FCML_CEH_GEC_INVALID_OPPERAND;
        }

        operand_enc->post_processor_args = (fcml_ptr)args->operand;
    }

    return error;
}

/***************/
/* Far pointer */
/***************/

static fcml_ceh_error operand_acceptor_far_pointer(
        operand_acceptor_args *args) {
    fcml_ceh_error result = FCML_CEH_GEC_NO_ERROR;
    const fcml_st_operand *operand = args->operand;
    struct acceptor_ctx *context = args->context;
    if (operand->type != FCML_OT_FAR_POINTER) {
        return FCML_CEH_GEC_INVALID_OPPERAND;
    }
    switch (context->entry_point->op_mode) {
    case FCML_OM_16_BIT:
        if (operand->far_pointer.offset_size == FCML_DS_16) {
            if (!set_size_flags(&(context->optimizer_ctx.allowed_eosa),
                    FCML_EN_ASF_16)) {
                /* Size can not be used by this operand. */
                result = FCML_CEH_GEC_INVALID_OPPERAND;
            }
        } else {
            /* 32 bit offset is not supported in 16 bit mode. */
            result = FCML_CEH_GEC_INVALID_OPPERAND;
        }
        break;
    case FCML_OM_32_BIT:
        if (!set_size_flags(&(context->optimizer_ctx.allowed_eosa),
                (operand->far_pointer.offset_size == FCML_DS_16) ?
                        (FCML_EN_ASF_16 | FCML_EN_ASF_32) : FCML_EN_ASF_32)) {
            /* Size can not be used by this operand. */
            result = FCML_CEH_GEC_INVALID_OPPERAND;
        }
        break;
    case FCML_OM_64_BIT:
        result = FCML_CEH_GEC_INVALID_OPPERAND;
        break;
    }
    return result;
}

static fcml_ceh_error operand_encoder_far_pointer(operand_encoder_args *args) {
    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

    if (args->phase == IPPP_FIRST_PHASE) {
        /* Prepare stream to instruction part's buffer. */
        fcml_st_memory_stream stream = inst_part_stream(args->operand_enc);

        /* Write offset.*/
        if (args->operand->far_pointer.offset_size == FCML_DS_16) {
            fcml_fn_stream_write_word(&stream, (fcml_uint16_t) args->
                    operand->far_pointer.offset16);
            args->operand_enc->code_length = 4;
        } else {
            fcml_fn_stream_write_dword(&stream,(fcml_uint32_t) args->
                    operand->far_pointer.offset32);
            args->operand_enc->code_length = 6;
        }

        /* Write segment.*/
        fcml_fn_stream_write_word(&stream,
                args->operand->far_pointer.segment);
    }
    return error;
}

/************************************/
/* Explicit GPR register addressing */
/************************************/

static fcml_ceh_error accept_segment_register(
        struct acceptor_ctx *context,
        const fcml_st_register *segment_register,
        fcml_uint8_t encoded_segment_register) {

    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

    /* If custom segment register has been chosen, check if
     * it's allowed in the given context. */
    if (segment_register->type != FCML_REG_UNDEFINED) {
        if (segment_register->type == FCML_REG_SEG) {
            if (segment_register->reg !=
                    FCML_SEG_GET_REG(encoded_segment_register)) {
                if (!(encoded_segment_register & FCML_SEG_ALLOW_OVERRIDE)) {
                    /* Register can not be overridden. */
                    add_error(&context->error_container,
                            fcml_fn_msg_get_message(
                                FCML_MC_SEGMENT_REGISTER_CAN_NOT_BE_OVERRIDDEN),
                            FCML_CEH_MEC_ERROR_ILLEGAL_SEG_REG_OVERRIDE);
                    error = FCML_CEH_GEC_INVALID_REGISTER;
                }
            }
        } else {
            /* Wrong register type, segment register should be used. */
            add_error(&context->error_container,
                    fcml_fn_msg_get_message(
                            FCML_MC_SEGMENT_WRONG_REGISTER_TYPE_SEG),
                    FCML_CEH_MEC_ERROR_INVALID_REGISTER_TYPE_SEG);
            error = FCML_CEH_GEC_INVALID_REGISTER_TYPE;
        }
    }

    return error;
}

static fcml_ceh_error operand_acceptor_explicit_gps_reg_addressing(
        operand_acceptor_args *args) {

    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
    const fcml_st_operand *operand = args->operand;
    fcml_st_def_tma_explicit_gps_reg_addressing *addr_mode_args =
            (fcml_st_def_tma_explicit_gps_reg_addressing*)
            args->addr_mode->addr_mode_args;

    if ((operand->type != FCML_OT_ADDRESS)
            || (operand->address.effective_address.base.reg !=
                    addr_mode_args->reg_num)) {
        error = FCML_CEH_GEC_INVALID_OPPERAND;
    } else if (!accept_data_size(args->context, args->addr_mode_desc,
            FCML_EOS_EASA, operand->address.effective_address.base.size,
            FCML_IEN_CT_EQUAL)) {
        error = FCML_CEH_GEC_INVALID_ADDRESS_SIZE;
    } else if (!accept_data_size(args->context, args->addr_mode_desc,
            addr_mode_args->encoded_operand_size, operand->address.size_operator,
            FCML_IEN_CT_EQUAL)) {
        error = FCML_CEH_GEC_INVALID_OPPERAND_SIZE;
    } else {
        error = accept_segment_register(args->context,
                &(operand->address.segment_selector.segment_selector),
                addr_mode_args->encoded_segment_register);
    }

    return error;
}

static fcml_ceh_error operand_encoder_explicit_gps_reg_addressing(operand_encoder_args *args) {
    const fcml_st_operand *operand = args->operand;

    /* We don't care here if the segment register is valid or not.
     * It's acceptor that is responsible for rejecting invalid segment
     * register in the first place. */
    if (args->phase == IPPP_FIRST_PHASE) {
        fcml_st_def_tma_explicit_gps_reg_addressing *addr_mode_args =
                    (fcml_st_def_tma_explicit_gps_reg_addressing*)
                    args->addr_mode->addr_mode_args;
        fcml_uint8_t encoded_segment_register = addr_mode_args->encoded_segment_register;
        const fcml_st_register *segment_register = &(operand->address.segment_selector.segment_selector);
        if (segment_register->type == FCML_REG_SEG) {
            if (segment_register->reg != (encoded_segment_register & 0x7F)) {
                if (encoded_segment_register & FCML_SEG_ALLOW_OVERRIDE) {
                    args->context->segment_override = *segment_register;
                }
            }
        }
    }
    return FCML_CEH_GEC_NO_ERROR;
}

/***************/
/* Explicit IB */
/***************/

static fcml_ceh_error operand_acceptor_explicit_ib(
        operand_acceptor_args *args) {
    fcml_ceh_error error = FCML_CEH_GEC_INVALID_OPPERAND;
    const fcml_st_operand *operand = args->operand;
    if (operand->type == FCML_OT_IMMEDIATE) {
        fcml_st_integer dest;
        /* We are interested in errors only here. */
        error = fcml_fn_utils_conv_int_to_int(
                &(operand->immediate), &dest, FCML_DS_8, FCML_DS_8);
    }
    return error;
}

static fcml_ceh_error operand_encoder_explicit_ib(operand_encoder_args *args) {
    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
    if (args->phase == IPPP_FIRST_PHASE) {
        error = FCML_CEH_GEC_INVALID_OPPERAND;
        fcml_st_def_tma_explicit_ib *exp_ib =
                (fcml_st_def_tma_explicit_ib*) args->addr_mode->addr_mode_args;
        fcml_st_integer dest;
        fcml_ceh_error res = fcml_fn_utils_conv_int_to_int(
                &(args->operand->immediate), &dest, FCML_DS_8, FCML_DS_8);
        if (!res) {
            if (exp_ib->ib == (fcml_uint8_t) dest.int8) {
                error = FCML_CEH_GEC_NO_ERROR;
            }
        }
    }
    return error;
}

/***************************/
/* Segment relative offset */
/***************************/

static fcml_ceh_error operand_acceptor_segment_relative_offset(
        operand_acceptor_args *args) {

    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

    const fcml_st_operand *operand = args->operand;
    if (operand->type == FCML_OT_ADDRESS) {

        fcml_st_def_tma_segment_relative_offset *addr_mode_args =
                (fcml_st_def_tma_segment_relative_offset*)
                args->addr_mode->addr_mode_args;

        const fcml_st_address *address = &(operand->address);

        if (address->address_form != FCML_AF_OFFSET) {
            return FCML_CEH_GEC_INVALID_OPPERAND;
        }

        struct acceptor_ctx *context = args->context;
        if (operand->address.size_operator != FCML_OS_UNDEFINED) {
            if (!accept_data_size(context, args->addr_mode_desc,
                    addr_mode_args->encoded_operand_size,
                    operand->address.size_operator, FCML_IEN_CT_EQUAL)) {
                return FCML_CEH_GEC_INVALID_OPPERAND;
            }
        }

        fcml_bool is_convertable = FCML_FALSE;
        fcml_flags flags = FCML_EN_ASF_ANY;
        fcml_st_integer src_addr = { 0 }, conv_addr = { 0 };

        /* Convert IMM value to address. */
        error = fcml_fn_utils_offset_to_integer(&(address->offset), &src_addr);
        if (error) {
            return FCML_CEH_GEC_INVALID_OPPERAND;
        }

        /* Check if address can be converted to 16, 32 or 64 bits. */
        src_addr.is_signed = FCML_TRUE;

        /* TODO: change to: int_fit_imm */
        is_convertable |= conv_int_and_set_flag(&src_addr, &conv_addr,
                FCML_DS_32, FCML_DS_32, FCML_EN_ASF_32, &flags);
        if (context->entry_point->op_mode == FCML_OM_64_BIT) {
            is_convertable |= conv_int_and_set_flag(&src_addr, &conv_addr,
                    FCML_DS_64, FCML_DS_64, FCML_EN_ASF_64, &flags);
        } else {
            is_convertable |= conv_int_and_set_flag(&src_addr, &conv_addr,
                    FCML_DS_16, FCML_DS_16, FCML_EN_ASF_16, &flags);
        }

        if (!set_size_flags(&(context->optimizer_ctx.allowed_easa), flags)) {
            error = FCML_CEH_GEC_INVALID_OPPERAND;
        }

    } else {
        error = FCML_CEH_GEC_INVALID_OPPERAND;
    }

    return error;
}

static fcml_ceh_error operand_encoder_segment_relative_offset(
        operand_encoder_args *args) {
    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

    if (args->phase == IPPP_FIRST_PHASE) {
        fcml_usize asa = args->context->optimizer_processing_details.easa;

        if (asa != FCML_DS_UNDEF) {
            const fcml_st_address *address = &(args->operand->address);

            /* Convert IMM value to address. */
            fcml_st_integer offset = { 0 };
            error = fcml_fn_utils_offset_to_integer(&(address->offset),
                    &offset);
            if (!error) {
                /* Convert address to size indicated by ASA.*/
                error = fcml_fn_utils_conv_int_to_int(&offset,
                        &offset, asa, asa);
                if (!error) {

                    /* Encode offset.*/
                    fcml_st_memory_stream stream = inst_part_stream(args->operand_enc);
                    fcml_fn_utils_encode_integer(&stream, &offset);
                    args->operand_enc->code_length = stream.offset;
                }
            }
        } else {
            /* ASA should be set by optimizer.*/
            error = FCML_CEH_GEC_INVALID_OPPERAND;
        }

        if (!error) {
        	handle_segment_override(args);
        }
    }
    return error;
}

/***************/
/* ModR/M - rm */
/***************/

/* TODO: Move to fcml_operand_decorators. */
static fcml_ceh_error accept_bcast_decorator(fcml_bool is_bcast_supported,
        fcml_nuint8_t bcast, fcml_usize element_size,
        struct acceptor_optimizer_ctx *optimizer_ctx,
        fcml_uint8_t encoded_memory_operand_size) {

    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

    if (!bcast.is_not_null || !is_bcast_supported) {
        return FCML_CEH_GEC_NOT_SUPPORTED_DECORATOR;
    }

    fcml_usize noe = bcast.value;

    /* Check if broadcast size is correct. */
    if (noe != 2 && noe != 4 && noe != 8 && noe != 16 && noe != 32
            && noe != 64) {
        return FCML_CEH_GEC_INVALID_OPERAND_DECORATOR;
    }

    fcml_usize bcast_accessed_mem_size = noe * element_size;
    fcml_uint8_t encoded_static_operand_size =
            FCML_GET_OS(encoded_memory_operand_size);

    switch (encoded_static_operand_size) {
    case FCML_EOS_L: {
        /* Force vector length basing on broadcast element size and number
         * of such elements. */
        fcml_usize vector_length = bcast_accessed_mem_size;
        if (!set_vector_length(&(optimizer_ctx->vector_length),
                vector_length)) {
            FCML_TRACE("Vector length differs expected %d got %d.",
                    vector_length, optimizer_ctx->vector_length);
            error = FCML_CEH_GEC_INVALID_OPPERAND_SIZE;
        }
        break;
    }
    default:
        /* Take into account only directly encoded sizes. */
        if (encoded_memory_operand_size < FCML_EOS_DYNAMIC_BASE) {
            if (encoded_static_operand_size * 8 != bcast_accessed_mem_size) {
                FCML_TRACE("Unsupported broadcast operand size. "
                        "Expected %d got %d.", bcast_accessed_mem_size,
                        encoded_static_operand_size * 8);
                error = FCML_CEH_GEC_INVALID_OPPERAND_SIZE;
            }
        }
        break;
    }

    return error;
}

static fcml_ceh_error operand_acceptor_rm(operand_acceptor_args *args) {

    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
    struct acceptor_ctx *context = args->context;
    const fcml_st_operand *operand = args->operand;
    const fcml_st_def_tma_rm *addr_mode_args = (fcml_st_def_tma_rm*)
            args->addr_mode->addr_mode_args;

    fcml_bool is_reg = operand->type == FCML_OT_REGISTER;
    fcml_bool is_mem = operand->type == FCML_OT_ADDRESS;;
    fcml_bool result = ((addr_mode_args->flags & FCML_RMF_R) && is_reg) ||
            ((addr_mode_args->flags & FCML_RMF_M) && is_mem);

    if (result) {
        if (is_reg) {
            if (addr_mode_args->reg_type != operand->reg.type) {
                /* Different register type.*/
                error = FCML_CEH_GEC_INVALID_OPPERAND;
            } else if ((context->instruction->prefixes & FCML_PREFIX_LOCK)
                    && args->addr_mode->access_mode == FCML_AM_WRITE) {
                /* Lock prefixes are only allowed for destination
                 * memory operands. */
                error = FCML_CEH_GEC_INVALID_OPPERAND;
            } else {
                if (!accept_data_size(context, args->addr_mode_desc,
                        addr_mode_args->encoded_register_operand_size,
                        operand->reg.size, FCML_IEN_CT_EQUAL)) {
                    FCML_TRACE_MSG("Unsupported register size.");
                    error = FCML_CEH_GEC_INVALID_OPPERAND_SIZE;
                }
            }
        }
        if (is_mem) {

            /* OSA. */

            /* TODO: Refactoring - this piece of code is getting too
             * complicated. */

            /* TODO: Move it to accept_data_size. */
            if (operand->decorators.bcast.is_not_null) {

                fcml_usize element_size =
                        FCML_GET_SIMD_ELEMENT_SIZE(args->addr_mode_desc->details);

                /* AVX-512 Broadcast decorator. */
                error = accept_bcast_decorator(
                        addr_mode_args->is_bcast, operand->decorators.bcast,
                        element_size, &(context->optimizer_ctx),
                        addr_mode_args->encoded_memory_operand_size);

                /* Accept broadcast memory location size. */
                if (operand->address.size_operator &&
                        element_size != operand->address.size_operator) {
                    FCML_TRACE_MSG("Unsupported memory operand size.");
                    error = FCML_CEH_GEC_INVALID_OPPERAND_SIZE;
                }
            } else {
                fcml_usize mem_data_size = calculate_operand_size(context->instruction,
                        context->ds_calculator, context->ds_calculator_args,
                        operand->address.size_operator,
                        addr_mode_args->encoded_memory_operand_size);
                if (!accept_data_size(context, args->addr_mode_desc,
                        addr_mode_args->encoded_memory_operand_size, mem_data_size,
                        FCML_IEN_CT_EQUAL)) {
                    FCML_TRACE_MSG("Unsupported memory operand size.");
                    error = FCML_CEH_GEC_INVALID_OPPERAND_SIZE;
                }
            }

            /* Check VSIB. */
            if (!error && addr_mode_args->is_vsib) {
                const fcml_st_register *index =
                        &(operand->address.effective_address.index);
                if (index->type == FCML_REG_SIMD) {
                    fcml_usize vsib_reg_size = fcml_fn_def_vsib_reg_to_ds(
                            addr_mode_args->vector_index_register);
                    if (vsib_reg_size != FCML_DS_UNDEF &&
                            vsib_reg_size != index->size) {
                        FCML_TRACE_MSG("Wrong VSIB size.");
                        error = FCML_CEH_GEC_INVALID_OPPERAND_SIZE;
                    }
                } else {
                    FCML_TRACE_MSG("VSIB encoding needs SIMD index" \
                            " register.");
                    error = FCML_CEH_GEC_INVALID_OPPERAND_SIZE;
                }
            }

            /* Accept segment registers if any of them have been set. */
            if (!error) {

                const fcml_st_effective_address *effective_address =
                        &(operand->address.effective_address);
                const fcml_st_segment_selector *segment_selector =
                        &(operand->address.segment_selector);
                const fcml_st_register *segment_register =
                        &(segment_selector->segment_selector);

                if (segment_register->type == FCML_REG_SEG) {
                    /* Segment register set, so it has to be accepted.*/
                    if (args->addr_mode_desc->instruction_group
                            & FCML_AMT_BRANCH) {
                        /* For branch instructions only CS register
                         * can be used and override is not acceptable.
                         */
                        if (segment_register->reg != FCML_REG_CS) {
                            error = FCML_CEH_GEC_INVALID_OPPERAND;
                        }
                    } else if ((effective_address->base.type
                            == FCML_REG_GPR)
                            && (effective_address->base.reg
                                    == FCML_REG_BP
                                    || effective_address->base.reg
                                            == FCML_REG_SP)) {
                        /* For SP/BP registers SS segment register has
                         * to be used.
                         */
                        if (segment_register->reg != FCML_REG_SS) {
                            error = FCML_CEH_GEC_INVALID_OPPERAND;
                        }
                    }
                    if (error) {
                        /* Segment register can not be overridden. */
                        add_error(&context->error_container,
                                fcml_fn_msg_get_message(
                        FCML_MC_SEGMENT_REGISTER_CAN_NOT_BE_OVERRIDDEN),
                           FCML_CEH_MEC_ERROR_ILLEGAL_SEG_REG_OVERRIDE);
                    }
                } else if(segment_register->type != FCML_REG_UNDEFINED) {
                    /* Wrong register type. */
                    add_error(&context->error_container,
                            fcml_fn_msg_get_message(
                               FCML_MC_SEGMENT_WRONG_REGISTER_TYPE_SEG),
                          FCML_CEH_MEC_ERROR_INVALID_REGISTER_TYPE_SEG);
                }
            }

            if (!error) {

                /* ASA. */
                fcml_en_operating_mode op_mode = context->entry_point->op_mode;

                fcml_st_modrm mod_rm = { 0 };
                mod_rm.address = operand->address;

                fcml_flags easa_flags = 0;
                error = fcml_fn_modrm_calculate_effective_address_size(
                        &mod_rm, &easa_flags);

                if (!error) {

                    /* Potential 16-bit ASA is not available in
                       64-bit mode. */
                    if (op_mode == FCML_OM_64_BIT) {
                        easa_flags &= ~FCML_EN_ASF_16;
                    }

                    /* Potential 64-bit ASA is not available in
                       16-bit mode. */
                    if (op_mode == FCML_OM_16_BIT) {
                        easa_flags &= ~FCML_EN_ASF_64;
                    }

                    if(!set_size_flags(&(context->optimizer_ctx.allowed_easa),
                            easa_flags)) {
                        FCML_TRACE_MSG("Accept ModR/M: Can not accept " \
                                "ASA size.");
                        error = FCML_CEH_GEC_INVALID_OPPERAND;
                    }
                }
            }
        }
    } else {
        error = FCML_CEH_GEC_INVALID_OPPERAND;
    }
    return error;
}

static fcml_ceh_error operand_encoder_rm(operand_encoder_args *args) {

    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
    const fcml_st_operand *operand = args->operand;
    encoding_context *context = args->context;
    const fcml_st_entry_point *entry_point =
            &(context->assembler_context->entry_point);
    fcml_st_def_tma_rm *addr_mode_args = (fcml_st_def_tma_rm*)
            args->addr_mode->addr_mode_args;

    if (args->phase == IPPP_FIRST_PHASE) {

        if (operand->type == FCML_OT_REGISTER) {
            context->mod_rm.reg.is_not_null = FCML_TRUE;
            context->mod_rm.reg.value = operand->reg.reg;

            if (entry_point->op_mode == FCML_OM_64_BIT) {
                context->mod_rm.reg_opcode_needs_rex = operand->reg.x64_exp;
            }

            /* Modify data size flags if there is such need.*/
            error = decode_dynamic_operand_size(context,
                    addr_mode_args->encoded_register_operand_size, operand->reg.size,
                    NULL, FCML_IEN_CT_EQUAL);

        } else {
            /* Set hints for ModR/M instruction part encoder.*/
            context->modrm_hints.is_sib_alternative_hint = (operand->hints
                    & FCML_OP_HINT_SIB_ENCODING);

            if (entry_point->op_mode == FCML_OM_64_BIT) {
                context->modrm_hints.is_abs_alternative_hint = (operand->hints
                        & FCML_OP_HINT_ABSOLUTE_ADDRESSING);
                context->modrm_hints.is_rel_alternative_hint = (operand->hints
                        & FCML_OP_HINT_RELATIVE_ADDRESSING);
            } else {
                context->modrm_hints.is_abs_alternative_hint = FCML_FALSE;
                context->modrm_hints.is_rel_alternative_hint = FCML_FALSE;
            }

            context->mod_rm.address = operand->address;

            /* Do not calculate vector length, if broadcast is used. */
            fcml_usize mem_data_size = calculate_operand_size(context->instruction,
                    context->ds_calculator, context->ds_calculator_args, 
                    operand->address.size_operator,
                    addr_mode_args->encoded_memory_operand_size);

            fcml_size element_size = FCML_GET_SIMD_ELEMENT_SIZE(
                    args->addr_mode_def->details);

            error = decode_dynamic_operand_size_bcast(context,
                    addr_mode_args->encoded_memory_operand_size, mem_data_size,
                    &(operand->decorators.bcast), element_size,
                    NULL, FCML_IEN_CT_EQUAL);

            /* Encode broadcast. */
            if (!error && operand->decorators.bcast.is_not_null) {
                context->epf.b = FCML_TRUE;
            }

            /* Encode VSIB */
            if (!error && addr_mode_args->is_vsib) {
                const fcml_st_register *index =
                        &(operand->address.effective_address.index);
                if (index->type == FCML_REG_SIMD) {
                    if (addr_mode_args->vector_index_register == FCML_VSIB_UNDEF &&
                            !set_vector_length(
                            &(context->optimizer_processing_details.vector_length),
                            index->size)) {
                        error = FCML_CEH_GEC_INVALID_OPPERAND_SIZE;
                    }
                } else {
                    FCML_TRACE_MSG("VSIB encoding needs SIMD index"
                            " register.");
                    error = FCML_CEH_GEC_INVALID_OPPERAND_SIZE;
                }
            }

            if (!error) {
                handle_segment_override(args);
            }
        }
    }

    return error;
}

/**************/
/* ModR/M - r */
/**************/

static fcml_ceh_error operand_acceptor_r(operand_acceptor_args *args) {
    fcml_st_def_tma_r *addr_mode_args = (fcml_st_def_tma_r*)
            args->addr_mode->addr_mode_args;
    const fcml_st_operand *operand = args->operand;

    if (operand->type != FCML_OT_REGISTER
            || operand->reg.type != addr_mode_args->reg_type) {
        return FCML_CEH_GEC_INVALID_OPPERAND;
    }

    /* Some registers allow UNDEF size to be defined for them. */
    if ((operand->reg.type != FCML_REG_DR
            && operand->reg.type != FCML_REG_CR)
            && operand->reg.size != FCML_DS_UNDEF) {
        if (!accept_data_size(args->context, args->addr_mode_desc,
                addr_mode_args->encoded_register_operand_size, operand->reg.size,
                FCML_IEN_CT_EQUAL)) {
            return FCML_CEH_GEC_INVALID_OPPERAND;
        }
    }

    return FCML_CEH_GEC_NO_ERROR;
}

static fcml_ceh_error operand_encoder_r(operand_encoder_args *args) {
    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
    encoding_context *context = args->context;
    const fcml_st_operand *operand = args->operand;

    if (args->phase == IPPP_FIRST_PHASE) {
        fcml_st_def_tma_r *addr_mode_args = (fcml_st_def_tma_r*)
                args->addr_mode->addr_mode_args;
        context->mod_rm.reg_opcode = operand->reg.reg;

        if (context->assembler_context->entry_point.op_mode == FCML_OM_64_BIT) {
            context->mod_rm.reg_opcode_needs_rex = operand->reg.x64_exp;
        }

        if ((operand->reg.type != FCML_REG_DR
                && operand->reg.type != FCML_REG_CR)
                && operand->reg.size != FCML_DS_UNDEF) {
            error = decode_dynamic_operand_size(context,
                    addr_mode_args->encoded_register_operand_size,
                    operand->reg.size, NULL, FCML_IEN_CT_EQUAL);
            if (error) {
                error = FCML_CEH_GEC_INVALID_OPPERAND;
            }
        }
    }

    return error;
}

/********/
/* VVVV */
/********/

static fcml_ceh_error operand_acceptor_vex_vvvv(operand_acceptor_args *args) {
    fcml_st_def_tma_vex_vvvv_reg *addr_mode_args =
            (fcml_st_def_tma_vex_vvvv_reg*) args->addr_mode->addr_mode_args;
    const fcml_st_operand *operand = args->operand;

    if (operand->type != FCML_OT_REGISTER
            || operand->reg.type != addr_mode_args->reg_type) {
        return FCML_CEH_GEC_INVALID_OPPERAND;
    }

    if (!accept_data_size(args->context, args->addr_mode_desc,
            addr_mode_args->encoded_register_size, operand->reg.size,
            FCML_IEN_CT_EQUAL)) {
        return FCML_CEH_GEC_INVALID_OPPERAND;
    }

    return FCML_CEH_GEC_NO_ERROR;
}

static fcml_ceh_error operand_encoder_vex_vvvv(operand_encoder_args *args) {
    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
    encoding_context *context = args->context;
    const fcml_st_operand *operand = args->operand;

    if (args->phase == IPPP_FIRST_PHASE) {
        extension_prefixes_fields *epf = &(context->epf);
        const fcml_st_register *reg = &(operand->reg);
        /* Only 16 registers can be encoded using VEX/XOP/EVEX.vvvv field. */
        epf->vvvv = reg->reg & 0x0F;
        /* High 16 registers has to be encoded using EVEX.V'. */
        epf->V_prim = (reg->reg >> 4) & 0x01;

        fcml_st_def_tma_vex_vvvv_reg *addr_mode_args =
                (fcml_st_def_tma_vex_vvvv_reg*)args->addr_mode->addr_mode_args;

        // TODO: The same piece of code is used in ModRM:reg encoder.
        if ((operand->reg.type != FCML_REG_DR
                && operand->reg.type != FCML_REG_CR)
                && operand->reg.size != FCML_DS_UNDEF) {
            error = decode_dynamic_operand_size(context,
                    addr_mode_args->encoded_register_size, operand->reg.size,
                    NULL, FCML_IEN_CT_EQUAL);
            if (error) {
                error = FCML_CEH_GEC_INVALID_OPPERAND;
            }
        }
    }

    return error;
}

/*--------*/
/* is4/is5*/
/*--------*/

static fcml_ceh_error operand_acceptor_isX(operand_acceptor_args *args) {
    struct acceptor_ctx *context = args->context;
    const fcml_st_operand *operand = args->operand;
    const fcml_st_def_tma_is *is_args = (fcml_st_def_tma_is*)
            args->addr_mode->addr_mode_args;

    if (((is_args->flags & FCML_ISF_IS4) || (is_args->flags & FCML_ISF_IS5_SRC))
            && is_simd_reg(operand)) {
        if (!accept_data_size(context, args->addr_mode_desc, FCML_EOS_L,
                operand->reg.size, FCML_IEN_CT_EQUAL)) {
            return FCML_CEH_GEC_INVALID_OPPERAND;
        }
    } else if ((is_args->flags & FCML_ISF_IS5_M2Z) && is_imm(operand)) {
        fcml_int8_t imm_value;
        fcml_ceh_error error = fcml_fn_utils_conv_int_to_int8(
                &(operand->immediate), &imm_value);
        if (error || imm_value > 3) {
            return FCML_CEH_GEC_INVALID_OPPERAND;
        }
    } else {
        return FCML_CEH_GEC_INVALID_OPPERAND;
    }

    return FCML_CEH_GEC_NO_ERROR;
}

static fcml_ceh_error operand_encoder_isX(operand_encoder_args *args) {
    inst_part *operand_enc = args->operand_enc;
    encoding_context *context = args->context;
    fcml_st_def_tma_is *is_args = (fcml_st_def_tma_is*)
                    args->addr_mode->addr_mode_args;

    if (args->phase == IPPP_FIRST_PHASE) {
        if (is_args->flags & FCML_ISF_IS4) {
            operand_enc->code[0] = args->operand->reg.reg << 4;
            operand_enc->code_length = 1;
        } else if (is_args->flags & FCML_ISF_IS5) {
            if (is_args->flags & FCML_ISF_IS5_SRC) {
                /* Store is5 source register for last is5 instruction
                 * part encoder. */
                context->isX_state.is5_byte = args->operand->reg.reg << 4;
            } else if (is_args->flags & FCML_ISF_IS5_M2Z) {
                fcml_int8_t m2z;
                fcml_ceh_error error = fcml_fn_utils_conv_int_to_int8(
                        &(args->operand->immediate), &m2z);
                if (error) {
                    return FCML_CEH_GEC_INVALID_OPPERAND;
                }
                operand_enc->code[0] = context->isX_state.is5_byte | m2z;
                operand_enc->code_length = 1;
            } else {
                return FCML_CEH_GEC_INTERNAL_ERROR;
            }
        } else {
            return FCML_CEH_GEC_INTERNAL_ERROR;
        }
    }

    return FCML_CEH_GEC_NO_ERROR;
}

/**************/
/* Pseudo-Op. */
/**************/

static fcml_ceh_error operand_acceptor_pseudo_op(operand_acceptor_args *args) {
    struct acceptor_ctx *context = args->context;
    const fcml_st_operand *operand = args->operand;
    fcml_st_def_tma_pseudo_op *pseudo_op_args =
            (fcml_st_def_tma_pseudo_op*) args->addr_mode->addr_mode_args;
    fcml_bool is_pseudo_op = context->mnemonic->pseudo_op.is_not_null;

    if (operand->type == FCML_OT_IMMEDIATE && !is_pseudo_op) {
        /* IMM8 encoding is given directly in operand.*/
        fcml_st_integer destination;
        /* TODO: change to: int_fit_imm */
        if (!conv_int_and_set_flag(
                &(operand->immediate), &destination, FCML_DS_8, FCML_DS_8,
                0, NULL)) {
            return FCML_CEH_GEC_INVALID_OPPERAND;
        }
        if (destination.int8 & (~pseudo_op_args->mask)) {
            add_error(&context->error_container,
                    fcml_fn_msg_get_message(
                            FCML_MC_SEGMENT_INVALID_PSEUDO_OPCODE_IMM),
                    FCML_CEH_MEC_ERROR_INVALID_PSEUDO_OPCODE_VALUE);
            return FCML_CEH_GEC_INVALID_OPPERAND;
        }
    } else if (!is_pseudo_op || operand->type != FCML_OT_NONE) {
        /* IMM8 is not available in operand, so its value should be given
         * in mnemonic configuration. In such case, operand
         * shouldn't exist.
         */
        return FCML_CEH_GEC_INVALID_OPPERAND;
    }

    return FCML_CEH_GEC_NO_ERROR;
}

static fcml_ceh_error operand_encoder_pseudo_op(operand_encoder_args *args ) {
    inst_part *operand_enc = args->operand_enc;
    const fcml_st_operand *operand = args->operand;
    encoding_context *context = args->context;
    if (args->phase == IPPP_FIRST_PHASE) {
        if (operand->type == FCML_OT_IMMEDIATE) {
            /* IMM8 encoding is given directly in operand.*/
            fcml_st_integer destination;
            /* TODO: change to: int_fit_imm */
            if (!conv_int_and_set_flag(
                    &(operand->immediate), &destination, FCML_DS_8,
                    FCML_DS_8, 0, NULL)) {
                return FCML_CEH_GEC_INVALID_OPPERAND;
            }
            operand_enc->code[0] = destination.int8;
        } else if (context->mnemonic->pseudo_op.is_not_null) {
            /* IMM8 is not available in operand, so its value should
             * be given in mnemonic configuration. */
            operand_enc->code[0] = context->mnemonic->pseudo_op.value;
        }
        operand_enc->code_length = 1;
    }
    return FCML_CEH_GEC_NO_ERROR;
}

/********************/
/* Virtual operand. */
/********************/

static fcml_ceh_error operand_acceptor_virtual_op(operand_acceptor_args *args) {
    struct acceptor_ctx *context = args->context;
    const fcml_st_operand *operand = args->operand;
    fcml_st_def_tma_virtual_op *addr_mode_args =
            (fcml_st_def_tma_virtual_op*)args->addr_mode->addr_mode_args;
    struct acceptor_optimizer_ctx *optimizer_ctx = &(context->optimizer_ctx);

    if (operand->type != FCML_OT_NONE &&
            operand->type != FCML_OT_VIRTUAL) {
        return FCML_CEH_GEC_INVALID_OPPERAND;
    }

    if (FCML_IS_DECOR_SAE_REQ(addr_mode_args->decorators) &&
            !operand->decorators.sae) {
        return FCML_CEH_GEC_MISSING_DECORATOR;
    }

    /* Handle explicit vector length for SAE and ER aware instructions. */
    if (operand->decorators.sae || operand->decorators.er.is_not_null) {

        fcml_uint8_t tuple_type =
                FCML_GET_SIMD_TUPLETYPE(args->addr_mode_desc->details);

        fcml_usize vector_length = FCML_DS_UNDEF;

        /* For the following kind of SIMD instructions vector length
           is explicitly set. */
        if(tuple_type == FCML_TT_FV) {
            vector_length = FCML_DS_512;
        } else if (tuple_type == FCML_TT_T1S || tuple_type == FCML_TT_T1F) {
            vector_length = FCML_DS_128;
        }

        if (!set_vector_length(&(optimizer_ctx->vector_length), vector_length)) {
            FCML_TRACE("Vector length differs expected %d got %d.",
                    optimizer_ctx->vector_length, vector_length);
            return FCML_CEH_GEC_INVALID_OPPERAND_SIZE;
        }
    }

    return FCML_CEH_GEC_NO_ERROR;
}

static fcml_ceh_error operand_encoder_virtual_op(operand_encoder_args *args) {
    encoding_context *context = args->context;
    const fcml_st_operand *operand = args->operand;

    if (args->phase == IPPP_FIRST_PHASE) {
        if (operand->decorators.sae) {
            context->epf.b = FCML_TRUE;
            context->epf.er.value = 0;
            context->epf.er.is_not_null = FCML_TRUE;
        }
        if (operand->decorators.er.is_not_null) {
            context->epf.er = operand->decorators.er;
            context->epf.b = FCML_TRUE;
        }
    } else if (args->phase == IPPP_THIRD_PHASE) {
        /* Make sure that register to register addressing mode is used, when
         * SAE or ER decorators are used. */
        fcml_st_def_tma_virtual_op *addr_mode_args =
                (fcml_st_def_tma_virtual_op*) args->addr_mode->addr_mode_args;
        if ((FCML_IS_DECOR_SAE(addr_mode_args->decorators) &&
                operand->decorators.sae)
                || (FCML_IS_DECOR_ER(addr_mode_args->decorators)
                        && operand->decorators.er.is_not_null)) {
            if (!context->mod_rm.reg.is_not_null) {
                return FCML_CEH_GEC_INVALID_OPPERAND;
            }
        }
    }

    return FCML_CEH_GEC_NO_ERROR;
}

static operand_encoder_def operand_encoders[] = {
        { NULL, NULL, NULL },
        { operand_encoder_imm, operand_acceptor_imm, NULL },
        { operand_encoder_explicit_reg, operand_acceptor_explicit_reg, NULL },
        { operand_encoder_opcode_reg, operand_acceptor_opcode_reg, NULL },
        { operand_encoder_imm_disp_relative,
                operand_acceptor_immediate_dis_relative, NULL },
        { operand_encoder_far_pointer, operand_acceptor_far_pointer,
                fcml_fn_hts_ihc_far_pointer },
        { operand_encoder_explicit_gps_reg_addressing,
                operand_acceptor_explicit_gps_reg_addressing, NULL },
        { operand_encoder_explicit_ib, operand_acceptor_explicit_ib, NULL },
        { operand_encoder_segment_relative_offset,
                operand_acceptor_segment_relative_offset, NULL },
        { operand_encoder_rm, operand_acceptor_rm,
                fcml_fn_hts_ihc_modrm_hints },
        { operand_encoder_r, operand_acceptor_r, NULL },
        { operand_encoder_vex_vvvv, operand_acceptor_vex_vvvv, NULL },
        { operand_encoder_isX, operand_acceptor_isX, NULL },
        { operand_encoder_rm, operand_acceptor_rm,
                fcml_fn_hts_ihc_modrm_hints },
        { operand_encoder_pseudo_op, operand_acceptor_pseudo_op, NULL },
        { operand_encoder_virtual_op, operand_acceptor_virtual_op, NULL }
};

/*************************
 * Instruction encoders. *
 *************************/

static fcml_ceh_error accept_addr_mode(struct acceptor_ctx *ctx,
        const addr_mode_encoding *addr_mode) {

    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

    const fcml_st_instruction *instruction = ctx->instruction;

#ifdef FCML_DEBUG
    FCML_TRACE("Accepting addressing mode: %d, prefixes: 0x%08X, opcode: 0x%08X.", ctx->__def_index, \
            addr_mode->addr_mode_desc->allowed_prefixes, \
            addr_mode->addr_mode_desc->opcode_flags);
#endif

    int index = 0;

    ipp_acceptor_args acceptor_args = {0};
    acceptor_args.context = ctx;
    acceptor_args.instruction = instruction;
    acceptor_args.addr_mode_details = &(addr_mode->addr_mode_details);
    acceptor_args.addr_mode_def = addr_mode->addr_mode_desc;

    ipp_chain *current_processor = addr_mode->ipp_chain;
    while (current_processor) {
        ipp_desc *descriptor = &(current_processor->descriptor);
        ctx->last_ipp = index;
        if (!is_short_form(ctx->instruction, ctx->mnemonic)
                || descriptor->is_short_form_supported) {
            if (descriptor->acceptor) {
                acceptor_args.args = descriptor->args;
                error = descriptor->acceptor(&acceptor_args);
                if (error != FCML_CEH_GEC_NO_ERROR) {
                    FCML_TRACE("Addressing mode not accepted. Acceptor (%s) "
                            "failed: %d",
                            descriptor->ipp_name, index);
                    break;
                }
            }
        }
        current_processor = current_processor->next_processor;
        index++;
    }

#ifdef FCML_DEBUG
    if(error == FCML_CEH_GEC_NO_ERROR) {
        FCML_TRACE("Accepted addressing mode %d - prefixes: 0x%04X, opcode:" \
                " 0x%02X.", ctx->__def_index,
                addr_mode->addr_mode_desc->allowed_prefixes,
                addr_mode->addr_mode_desc->opcode_flags);
    }
#endif

    return error;
}

/* All currently supported encoding phases. */
static part_processor_phase execution_phases[] = {
        IPPP_FIRST_PHASE,
        IPPP_SECOND_PHASE,
        IPPP_THIRD_PHASE
};

static fcml_uint8_t inst_parts_len(inst_part *inst_part, fcml_int count) {
    fcml_uint8_t length = 0;
    while (count-- > 0) {
        length += inst_part++->code_length;
    }
    return length;
}

/* Responsible for assembling given addressing mode using attributes
 * provided by the context.
 */
fcml_ceh_error fcml_ifn_asm_process_addr_mode(encoding_context *context,
        addr_mode_encoding *addr_mode,
        inst_part_container *inst_part_container) {

    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

    /* Allocate instruction parts.*/
    inst_part *part = (inst_part*)fcml_fn_env_memory_alloc_clear(
            sizeof(inst_part) * addr_mode->instruction_parts);
    if (!part) {
        return FCML_CEH_GEC_OUT_OF_MEMORY;
    }

    ipp_encoder_args encoder_args = { IPPP_FIRST_PHASE };
    encoder_args.context = context;
    encoder_args.addr_mode_details = &(addr_mode->addr_mode_details);
    encoder_args.addr_mode_def = addr_mode->addr_mode_desc;

    int i;
    int size = sizeof(execution_phases) /
            sizeof(part_processor_phase);
    for (i = 0; !error && i < size; i++) {
        inst_part *current_instruction_part = part;
        ipp_chain *current_processor = addr_mode->ipp_chain;
        fcml_bool first = FCML_TRUE;
        int index = 0;
        while (current_processor) {
            context->last_ipp = index;
            ipp_desc *descriptor = &(current_processor->descriptor);
            if (descriptor->encoder &&
                    (!is_short_form(context->instruction, context->mnemonic)
                            || descriptor->is_short_form_supported)) {
                if (!first && descriptor->type == IPPT_ENCODER) {
                    current_instruction_part++;
                }
                first = FCML_FALSE;
                encoder_args.phase = execution_phases[i];
                encoder_args.args = descriptor->args;
                /* If IPP is just a verifier, do not pass instruction part
                 * there. It's not needed because IPP doesn't encode any
                 * bytes anyway. */
                encoder_args.instruction_part = descriptor->type ==
                        IPPT_VERIFIER ? NULL : current_instruction_part;;
                error = descriptor->encoder(&encoder_args);
                if (error) {
#ifdef FCML_DEBUG
    FCML_TRACE("Processor failed (%s) %d - prefixes: 0x%04X, opcode: 0x%02X: %d",
            descriptor->ipp_name,
            context->__def_index,
            addr_mode->addr_mode_desc->allowed_prefixes,
            addr_mode->addr_mode_desc->opcode_flags, error);
#endif
                    /* Something failed.*/
                    break;
                }
            } else if(descriptor->encoder == NULL &&
                    descriptor->acceptor == NULL) {
                break;
            }

            current_processor = current_processor->next_processor;
            index++;
        }
    }

    if (!error) {

        /* Calculate instruction size.*/
        FCML_SET_VALUE(context->instruction_size,
                inst_parts_len(part, addr_mode->instruction_parts));

        fcml_bool recalculate_size = FCML_FALSE;

        /* Execute potential post processors.*/
        for (i = 0; i < addr_mode->instruction_parts; i++) {
            inst_part *ip = &(part[i]);
            if (ip->post_processor) {
                error = ip->post_processor(context, ip,
                        ip->post_processor_args);
                if (error) {
                    break;
                }
                recalculate_size = FCML_TRUE;
            }
        }

        if (recalculate_size) {
            FCML_SET_VALUE(context->instruction_size,
                    inst_parts_len(part, addr_mode->instruction_parts));
        }

#ifdef FCML_DEBUG
        FCML_TRACE("Proceeded addressing mode %d - prefixes: 0x%04X, opcode:" \
                " 0x%02X (%s).", context->__def_index,
                addr_mode->addr_mode_desc->allowed_prefixes,
                addr_mode->addr_mode_desc->opcode_flags,
                debug_print_size_flags(
                        &(context->optimizer_processing_details)));
#endif
    } else {
#ifdef FCML_DEBUG
        FCML_TRACE("Failed to process addressing mode %d - prefixes: 0x%04X," \
                " opcode: 0x%02X (%s).", context->__def_index,
                addr_mode->addr_mode_desc->allowed_prefixes,
                addr_mode->addr_mode_desc->opcode_flags,
                debug_print_size_flags(
                        &(context->optimizer_processing_details)));
#endif
    }

    if (error) {
        fcml_fn_env_memory_free(part);
    } else {
        inst_part_container->parts = part;
        inst_part_container->count = addr_mode->instruction_parts;
    }

    return error;
}

void fcml_ifn_asm_assemble_instruction_parts(
        fcml_st_assembled_instruction *assembled_instruction,
        inst_part_container *instruction_part_container) {
    int i, count = instruction_part_container->count;
    int offset = 0;
    for (i = 0; i < count; i++) {
        inst_part *part =
                &(instruction_part_container->parts[i]);
        if (part->code_length > 0) {
            fcml_fn_env_memory_copy(assembled_instruction->code + offset,
                    part->code, part->code_length);
            offset += part->code_length;
        }
    }
    /* Just to be consequent.*/
    assembled_instruction->code_length = offset;
}

void fcml_ifn_asm_free_assembled_instruction(
        fcml_st_assembled_instruction *assembled_instruction) {
    if (assembled_instruction) {
        if (assembled_instruction->code) {
            fcml_fn_env_memory_free(assembled_instruction->code);
        }
        fcml_fn_ceh_free_errors_only(&(assembled_instruction->warnings));
        fcml_fn_env_memory_free(assembled_instruction);
    }
}

fcml_ceh_error fcml_ifn_asm_assemble_instruction(
        encoding_context *context,
        addr_mode_encoding *addr_mode,
        fcml_st_assembled_instruction **assembled_instruction) {

    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

    inst_part_container instruction_part_container = { 0 };

    /* Prepares encoded instruction parts. */
    error = fcml_ifn_asm_process_addr_mode(context, addr_mode,
            &instruction_part_container);

    /* Assemble instruction parts.*/
    if (!error) {

        fcml_usize code_length = context->instruction_size.value;

        /* Allocate memory block for assembled code.*/
        FCML_ENV_ALLOC_CLEAR(asm_inst, fcml_st_assembled_instruction);
        if (asm_inst) {
            asm_inst->code = (fcml_uint8_t*) fcml_fn_env_memory_alloc(
                    code_length);
            if (asm_inst->code) {
                asm_inst->code_length = code_length;
                /* Copies instruction parts to the destination code array. */
                fcml_ifn_asm_assemble_instruction_parts(asm_inst,
                        &instruction_part_container);
                *assembled_instruction = asm_inst;
            } else {
                error = FCML_CEH_GEC_OUT_OF_MEMORY;
            }
        } else {
            error = FCML_CEH_GEC_OUT_OF_MEMORY;
        }

        if (error && asm_inst) {
            fcml_fn_env_memory_free(asm_inst);
        }

    }

    /* Always free instruction parts when they are not needed anymore. */
    if (instruction_part_container.parts) {
        fcml_fn_env_memory_free(instruction_part_container.parts);
    }

    return error;
}

/** Arguments passed through the optimization process. */
typedef struct fcml_st_asm_enc_optimizer_callback_args {
    /** Currently processed addressing mode. */
    addr_mode_encoding *addr_mode;
    /** Encoding context instance. */
    encoding_context *context;
    /** All assembled instructions end up here. */
    fcml_st_asm_encoder_result *result;
} fcml_st_asm_enc_optimizer_callback_args;

/** Assembles instruction and puts it to the instructions chain. */
static fcml_ceh_error assemble_and_collect_instruction(fcml_ptr args) {

    /* Restore important information from callback arguments.*/
    fcml_st_asm_enc_optimizer_callback_args *callback_args =
            (fcml_st_asm_enc_optimizer_callback_args*)args;
    encoding_context *context = callback_args->context;
    addr_mode_encoding *addr_mode = callback_args->addr_mode;
    fcml_st_asm_encoder_result *result = callback_args->result;

    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

    fcml_st_assembled_instruction *assembled_instruction;

    error = fcml_ifn_asm_assemble_instruction(context, addr_mode,
            &assembled_instruction);
    if (!error) {

#ifdef FCML_DEBUG
        assembled_instruction->__def_index = context->__def_index;
#endif

        fcml_bool ignore = FCML_FALSE;

        /* Check if such instruction has been already assembled. */
        fcml_st_assembled_instruction *instruction = result->instructions;
        while (instruction) {
            if (instruction->code_length == assembled_instruction->code_length
                    && fcml_fn_env_memory_cmp(instruction->code,
                            assembled_instruction->code,
                            instruction->code_length)) {
                /* Instructions are the same.*/
                ignore = FCML_TRUE;
                break;
            }
            instruction = instruction->next;
        }

        if (!ignore) {

            /* Insert newly assembled instruction to the front of the
             * instructions chain.
             */
            fcml_st_assembled_instruction *instructions =
                    result->instructions;
            result->instructions = assembled_instruction;
            assembled_instruction->next = instructions;

            result->number_of_instructions++;

        } else {
            /* Free ignored instruction.*/
            fcml_ifn_asm_free_assembled_instruction(assembled_instruction);
        }
    }

    return error;
}

static fcml_bool accept_instruction_hints(fcml_hints addr_mode_dest_hints,
        fcml_hints instruction_hints) {
    if ((instruction_hints & FCML_HINT_INDIRECT_POINTER)
            && !(addr_mode_dest_hints & FCML_HINT_INDIRECT_POINTER)) {
        FCML_TRACE_MSG("Addressing mode doesn't support indirect addressing.");
        return FCML_FALSE;
    }
    if ((instruction_hints & FCML_HINT_DIRECT_POINTER)
            && !(addr_mode_dest_hints & FCML_HINT_DIRECT_POINTER)) {
        FCML_TRACE_MSG("Addressing mode doesn't support direct addressing.");
        return FCML_FALSE;
    }
    if (instruction_hints & FCML_HINT_FAR_POINTER) {
        return addr_mode_dest_hints & FCML_HINT_FAR_POINTER;
    }
    if (instruction_hints & FCML_HINT_NEAR_POINTER) {
        return addr_mode_dest_hints & FCML_HINT_NEAR_POINTER;
    }
    return FCML_TRUE;
}

/* Sets attribute size flag for given real size. */
static void set_attribute_size_flag(fcml_usize attribute_size,
        fcml_st_nullable_size_flags *flags) {
    fcml_flags flag = 0;
    switch (attribute_size) {
    case FCML_DS_16:
        flag = FCML_EN_ASF_16;
        break;
    case FCML_DS_32:
        flag = FCML_EN_ASF_32;
        break;
    case FCML_DS_64:
        flag = FCML_EN_ASF_64;
        break;
    }
    if (flag) {
        flags->flags |= flag;
        flags->is_set = FCML_TRUE;
    }
}

void fcml_ifn_chooser_extract(fcml_ptr instruction_ptr,
        fcml_st_instruction_code *instruction_code) {
    if (instruction_ptr) {
        fcml_st_assembled_instruction *instruction =
                (fcml_st_assembled_instruction*) instruction_ptr;
        instruction_code->code = instruction->code;
        instruction_code->code_length = instruction->code_length;
    }
}

fcml_ptr fcml_ifn_chooser_next(fcml_ptr instruction_ptr) {
    if (instruction_ptr) {
        fcml_st_assembled_instruction *instruction =
                (fcml_st_assembled_instruction*) instruction_ptr;
        return instruction->next;
    }
    return NULL;
}

static fcml_st_chooser_context prepare_chooser_context(
        fcml_st_assembled_instruction *instructions) {
    fcml_st_chooser_context context;
    context.extract = &fcml_ifn_chooser_extract;
    context.next = &fcml_ifn_chooser_next;
    context.instruction = instructions;
    return context;
}

static void prepare_optimizer_processing_details(
        const addr_mode_encoding *addr_mode,
        fcml_st_asm_optimizer_processing_details *processing_details) {

    const fcml_st_mp_mnemonic *mnemonic =  addr_mode->mnemonic;

    /* Apply address attribute size restrictions from mnemonic definition.*/
    fcml_usize asa = mnemonic->supported_asa;
    processing_details->easa = asa;
    if (asa) {
        set_attribute_size_flag(asa, &(processing_details->allowed_easa));
    }

    /* Apply operand attribute size restrictions from mnemonic definition.*/
    fcml_usize osa = mnemonic->supported_osa;
    processing_details->eosa = osa;
    if (osa) {
        set_attribute_size_flag(osa, &(processing_details->allowed_eosa));
    }

    /* Apply L fields restrictions from mnemonic definition. */
    if (mnemonic->l.is_not_null) {
        processing_details->vector_length =
                fcml_fn_mp_l_to_vector_length(mnemonic->l.value);
    }
}

static struct acceptor_ctx prep_acceptor_ctx(encoding_context *context) {
    struct acceptor_optimizer_ctx optimizer_ctx = {
        context->optimizer_processing_details.allowed_eosa,
        context->optimizer_processing_details.allowed_easa,
        context->optimizer_processing_details.vector_length
    };
    /* This error container is here to collect errors from acceptors
     * invoked for only one addressing mode being considered by
     * the processor. */
    struct error_container ctx_error_container = {
        context->assembler_context->configuration.enable_error_messages,
        { NULL, NULL }
    };
    struct acceptor_ctx acceptor_ctx = {
        context->assembler_context->configuration,
        &(context->assembler_context->entry_point),
        context->instruction,
        context->mnemonic,
        optimizer_ctx,
        context->ds_calculator,
        context->ds_calculator_args,
        ctx_error_container
    };
    return acceptor_ctx;
}

static void handle_addr_mode_errors(
        addr_mode_error *addr_modes_errors,
        struct error_container *local_errors,
        fcml_ceh_error error_code, fcml_int ipp_failed,
        addr_mode_proc_phase phase) {

    fcml_bool choose_error = FCML_FALSE;

    /* Priorities are as follows: phase, number of failed ipp, error codes. */

    /* Phase. */
    if (phase == addr_modes_errors->phase) {
        /* IPP ordinal. */
        if (ipp_failed == addr_modes_errors->ipp_failed) {
            /* Error code. */
            fcml_ceh_error cec = addr_modes_errors->error_code;
            if (cec == FCML_CEH_GEC_NO_ERROR
                    || (cec == FCML_CEH_GEC_INVALID_OPPERAND
                            && (cec != error_code))) {
                choose_error = FCML_TRUE;
            }
        } else if (ipp_failed > addr_modes_errors->ipp_failed) {
            choose_error = FCML_TRUE;
        }
    } else if (phase > addr_modes_errors->phase) {
        choose_error = FCML_TRUE;
    }

    if (choose_error) {
        /* Move all errors from the local errors container prepared for the
         * currently processed addressing mode to the one shared by all the
         * addressing modes being considered.
         */
        move_errors(&addr_modes_errors->errors, local_errors);
        addr_modes_errors->error_code = error_code;
        addr_modes_errors->ipp_failed = ipp_failed;
        addr_modes_errors->phase = phase;
    }
}

static fcml_ceh_error encode_addressing_mode_core(
        encoding_context *context, addr_mode_encoding *addr_mode,
        addr_mode_error *addr_mode_errors, fcml_st_asm_encoder_result *result) {

    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

    const fcml_st_assembler_context *asm_ctx = context->assembler_context;

    /* Check if addressing mode matches the hints, if there are any. */
    if (!context->instruction->hints || accept_instruction_hints(
            addr_mode->hints, context->instruction->hints)) {

        /* Prepare processing context for optimizer using currently
          used addressing mode. */
        prepare_optimizer_processing_details(addr_mode,
                &(context->optimizer_processing_details));

        struct acceptor_ctx acceptor_ctx = prep_acceptor_ctx(context);
        error = accept_addr_mode(&acceptor_ctx, addr_mode);
        if (!error) {

            fcml_st_asm_enc_optimizer_callback_args args;
            args.addr_mode = addr_mode;
            args.context = context;
            args.result = result;

            fcml_st_asm_optimizer_context optimizer_context = { NULL };
            optimizer_context.entry_point = &(asm_ctx->entry_point);
            optimizer_context.optimizer_flags =
                    asm_ctx->configuration.optimizer_flags;

            /* Optimizer implementation can be provided by user. */
            fcml_fnp_asm_optimizer optimizer =
                    asm_ctx->configuration.optimizer;
            if (!optimizer) {
                optimizer = &fcml_fn_asm_default_optimizer;
            }

            fcml_st_asm_optimizer_processing_details *optimizer_details =
                    &(context->optimizer_processing_details);

            optimizer_details->allowed_eosa =
                    acceptor_ctx.optimizer_ctx.allowed_eosa;
            optimizer_details->allowed_easa =
                    acceptor_ctx.optimizer_ctx.allowed_easa;
            optimizer_details->vector_length =
                    acceptor_ctx.optimizer_ctx.vector_length;

            error = optimizer(&optimizer_context,
                    &(context->optimizer_processing_details),
                    assemble_and_collect_instruction, &args);
        } else {
            /* Addressing mode hasn't been proceeded, so handle errors. */
            handle_addr_mode_errors(addr_mode_errors,
                    &acceptor_ctx.error_container, error, acceptor_ctx.last_ipp,
                    AMPP_PROCESS);
        }

        /* If there are any locally collected errors left (haven't been moved
         * to the shared container) just free them.
         * See: handle_addr_mode_errors. */
        free_errors(&acceptor_ctx.error_container);
    } else {
        FCML_TRACE_MSG("Addressing mode ignored due to hints incompatibility.");
    }

    return error;
}

static fcml_usize count_operands(fcml_st_instruction *instruction) {
    fcml_int i;
    fcml_usize count = 0;
    /* Check if there are no operator gaps. */
    for(i = 0; i < FCML_OPERANDS_COUNT; i++) {
        if (instruction->operands[i].type == FCML_OT_NONE) {
            break;
        } else {
            count++;
        }
    }
    return count;
}

static fcml_ceh_error instruction_encoder_IA(
        fcml_st_assembler_context *asm_context,
        fcml_st_dialect_context_int *dialect_context,
        fcml_st_instruction_addr_modes *addr_modes,
        fcml_st_instruction *instruction,
        fcml_st_asm_encoder_result *result) {

    /* Make a local copy of the instruction, because it still can be
       changed by the preprocessor. */
    fcml_st_instruction tmp_instruction = *instruction;
    fcml_usize operands_count = count_operands(&tmp_instruction);
    fcml_bool errors_enabled = asm_context->configuration.enable_error_messages;

    encoding_context context = { 0 };
    context.assembler_context = asm_context;
    context.instruction = &tmp_instruction;
    /* Share the global errors container in order to extend it instead of
     * rewriting it with the local errors only. */
    context.errors.enabled = errors_enabled;
    context.errors.errors = result->errors;

    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

    if (addr_modes) {
        /* Choose addressing mode.*/
        if (addr_modes->addr_modes_encodings->size) {
            /* Container for errors related to addressing modes processing.
             * It's shared by all the addressing modes. */
            addr_mode_error addr_mode_errors = { AMPP_UNDEFINED,
                   FCML_CEH_GEC_NO_ERROR, { errors_enabled, {NULL} }, 0};

            /* Gets first addressing mode available for chosen instruction
               definition. */
            fcml_st_coll_list_element *addr_mode_elem =
                    addr_modes->addr_modes_encodings->head;

#ifdef FCML_DEBUG
            int index = 0;
#endif
            /* This loop iterates through all available addressing
               modes one by one. */
            while (addr_mode_elem) {
                error = FCML_CEH_GEC_NO_ERROR;
                addr_mode_encoding *addr_mode = (addr_mode_encoding*)
                        addr_mode_elem->item;

                /* Encoding context has to be prepared for new addressing
                   mode because it is reused. */
                clean_context(&context);

                /* This flag is used by preprocessor to signal the fact
                   that instruction has been changed. */
                fcml_bool inst_changed = FCML_FALSE;
                /* Call instruction preprocessor again, passing found mnemonic
                   definition this time. Parsed mnemonic can contain some
                   dialect specific information, so we have to provide
                   dialect a way to modify instruction definition basing
                   on that information. */
                fcml_fnp_asm_preprocessor preprocessor =
                        dialect_context->asm_preprocessor;
                if (preprocessor) {
                    preprocessor((fcml_st_dialect*) dialect_context,
                            addr_mode->addr_mode_desc, addr_mode->mnemonic,
                            addr_mode->instruction, &tmp_instruction,
                            &inst_changed);
                }

                /* Make it accessible through encoding context. Certain
                   encoders might need this information. */
                context.mnemonic = addr_mode->mnemonic;

#ifdef FCML_DEBUG
                context.__def_index = index;
#endif

                /* Every addressing mode has its own data size calculators. */
                context.ds_calculator =
                        addr_mode->addr_mode_details.ds_calculator;
                context.ds_calculator_args =
                        addr_mode->addr_mode_details.ds_calculator_args;

                /* Try to encode prepared addressing mode. */
                error = encode_addressing_mode_core(&context, addr_mode,
                        &addr_mode_errors, result);

                addr_mode_elem = addr_mode_elem->next;

#ifdef FCML_DEBUG
                index++;
#endif
                /* Restore instruction if preprocessor has changed anything.*/
                if (inst_changed) {
                    tmp_instruction = *instruction;
                }
            }
            /* Addressing modes related errors have higher priority than
               any others. */
            if (has_errors(&addr_mode_errors.errors)) {
                /* Move collected errors to the global context. */
                move_errors(&context.errors, &addr_mode_errors.errors);
            }
            /* Set current error code to the best error collected while
               processing addressing modes. */
            if (addr_mode_errors.error_code) {
                error = addr_mode_errors.error_code;
            }
            /* Check if there is at least one assembled instruction.*/
            if (result->number_of_instructions == 0) {
                /* Instruction has been found but can not be assembled in
                   this form or addressing mode. */
                if (!error) {
                    /* Just in case. Use more general error code, but in
                       theory it should never happened because acceptors and
                       optimizers should return more accurate error codes. */
                    error = FCML_CEH_GEC_INVALID_INSTRUCTION_FORM;
                }
            } else {
                /* Assembling process has succeed so free errors but leave
                   warning as they are. */
                fcml_fn_ceh_free_errors_only_with_level(&context.errors.errors,
                        FCML_EN_CEH_EL_ERROR);
                /* Last error code should be also cleaned. */
                error = FCML_CEH_GEC_NO_ERROR;
            }

            if (!error) {
                /* Choose instruction.*/
                fcml_fnp_asm_instruction_chooser chooser =
                        asm_context->configuration.chooser;
                if (!chooser) {
                    chooser = &fcml_fn_asm_default_instruction_chooser;
                }

                if (result->number_of_instructions == 1) {
                    /* There is only one instruction so chooser is
                       not needed. */
                    result->chosen_instruction = result->instructions;
                } else {
                    /* Prepares chooser context. */
                    fcml_st_chooser_context chooser_context =
                            prepare_chooser_context(result->instructions);
                    /* Chooses most appropriate instruction. */
                    result->chosen_instruction =
                            (fcml_st_assembled_instruction*) chooser(
                                    &chooser_context);
                }
            }
        } else {
            FCML_TRACE_MSG("There is no addressing mode for given " \
                    "instruction. It should never happened, so it's an" \
                    " internal bug.");
            error = FCML_CEH_GEC_INTERNAL_ERROR;
        }
    }

    /* Make sure collected errors have been copied to the result. */
    result->errors = context.errors.errors;

    return error;
}

static void free_ipp_desc(ipp_desc desc) {
    if (desc.args_deallocator) {
        desc.args_deallocator(desc.args);
    }
}

static void free_ipp_chain(ipp_chain *chain) {
    if (chain) {
        free_ipp_chain(chain->next_processor);
        free_ipp_desc(chain->descriptor);
        fcml_fn_env_memory_free(chain);
    }
}

static void ipp_operand_wrapper_args_deallocator(fcml_ptr ptr) {
    ipp_operand_wrapper_args *wrapper_wrgs =
            (ipp_operand_wrapper_args*) ptr;
    if (wrapper_wrgs->decoded_addr_mode) {
        fcml_fnp_def_free_addr_mode(wrapper_wrgs->decoded_addr_mode);
    }
    fcml_fn_env_memory_free(wrapper_wrgs);
}

static fcml_bool accept_operand_hints(fcml_hints addr_mode_hints,
        fcml_hints operand_hints) {
    /** If caller expects SIMD addressing mode to be chosen, then
     * reject all non SIMD ones. */
    if ((operand_hints & FCML_OP_HINT_MULTIMEDIA_INSTRUCTION)
            && !(addr_mode_hints & FCML_OP_HINT_MULTIMEDIA_INSTRUCTION)) {
        return FCML_FALSE;
    }
    return FCML_TRUE;
}

static fcml_ceh_error ipp_operand_wrapper_acceptor(
        ipp_acceptor_args *args) {
    const fcml_st_instruction *instruction = args->instruction;
    ipp_operand_wrapper_args *wrapper_args =
            (ipp_operand_wrapper_args*) args->args;
    const fcml_st_operand *operand =
            &(instruction->operands[wrapper_args->operand_index]);
    if (wrapper_args->operand_acceptor) {
        /* Check hints.*/
        fcml_hints operand_hints = operand->hints;
        if (!operand_hints || accept_operand_hints(
                wrapper_args->hints, operand_hints)) {
            operand_acceptor_args acceptor_args = {0};
            acceptor_args.context = args->context,
            acceptor_args.addr_mode_details = args->addr_mode_details;
            acceptor_args.addr_mode_desc = args->addr_mode_def;
            acceptor_args.addr_mode = wrapper_args->decoded_addr_mode;
            acceptor_args.operand = operand;
            acceptor_args.operand_enc = NULL;
            return wrapper_args->operand_acceptor(&acceptor_args);
        } else {
            FCML_TRACE_MSG("Hints do not match.");
            return FCML_CEH_GEC_INVALID_OPPERAND;
        }
    } else {
        if (!wrapper_args->operand_defined) {
            /* This operand shouldn't be set for the instruction being
             * encoded. */
            if (operand->type != FCML_OT_NONE) {
                return FCML_CEH_GEC_INVALID_OPPERAND;
            }
        }
        return FCML_CEH_GEC_NO_ERROR;
    }
}

static fcml_ceh_error ipp_operand_wrapper_encoder(ipp_encoder_args *args) {
    ipp_operand_wrapper_args *wrapper_args =
            (ipp_operand_wrapper_args*) args->args;
    const fcml_st_operand *operand = &(args->context->instruction->
            operands[wrapper_args->operand_index]);
    if (wrapper_args->operand_encoder) {
        operand_encoder_args wrapped_encoder_args = { IPPP_FIRST_PHASE };
        wrapped_encoder_args.phase = args->phase;
        wrapped_encoder_args.context = args->context;
        wrapped_encoder_args.addr_mode_def = args->addr_mode_def;
        wrapped_encoder_args.addr_mode = wrapper_args->decoded_addr_mode;
        wrapped_encoder_args.operand = operand;
        wrapped_encoder_args.operand_enc = args->instruction_part;
        return wrapper_args->operand_encoder(&wrapped_encoder_args);
    } else {
        return FCML_CEH_GEC_NO_ERROR;
    }
}

static ipp_desc ipp_operand_wrapper_factory(ipp_factory_args *args,
        fcml_ceh_error *error) {

    ipp_desc descriptor = { 0 };

    FCML_ENV_ALLOC_CLEAR(wrapper_args, ipp_operand_wrapper_args);
    if (!wrapper_args) {
        *error = FCML_CEH_GEC_OUT_OF_MEMORY;
        return descriptor;
    }

    fcml_uint32_t operand_index = args->flags;
    fcml_operand_desc operand_desc = args->addr_mode->operands[operand_index];

    if (operand_desc != FCML_NA) {
        *error = fcml_fn_def_decode_addr_mode_args(operand_desc,
                &(wrapper_args->decoded_addr_mode));
        if (*error) {
            fcml_fn_env_memory_free(wrapper_args);
            return descriptor;
        }

        operand_encoder_def *def =
                &operand_encoders[wrapper_args->decoded_addr_mode->addr_mode];

        wrapper_args->operand_encoder = def->encoder;
        wrapper_args->operand_acceptor = def->acceptor;
        wrapper_args->operand_defined = FCML_TRUE;

        if (def->hints_calculator) {
            fcml_st_hts_calculated_hints hints = def->hints_calculator(
                    args->addr_mode, wrapper_args->decoded_addr_mode);
            *args->hints |= hints.instruction_hints;
            wrapper_args->hints = hints.operand_hints;
        }

        descriptor.type = IPPT_ENCODER;
    } else {
        wrapper_args->operand_defined = FCML_FALSE;
        /* This operand is not defined for the given instruction,
         * so let's treat this IPP as a verifier just in order
         * to allow the wrapper to verify if the operand it handles
         * is not set for an instruction being encoded. The
         * acceptor will be called in order to verify that, but
         * instruction part won't be generated for this IPP, because
         * encoder won't be even called.
         */
        descriptor.type = IPPT_VERIFIER;
    }

    descriptor.args_deallocator = ipp_operand_wrapper_args_deallocator;
    descriptor.args = wrapper_args;
    descriptor.encoder = ipp_operand_wrapper_encoder;
    descriptor.acceptor = ipp_operand_wrapper_acceptor;
    wrapper_args->operand_index = operand_index;
    return descriptor;
}

/***********************************/
/* XOP/VEX opcode encoder factory. */
/***********************************/

static fcml_ceh_error ipp_AVX_opcode_encoder(ipp_encoder_args *args) {
    const fcml_st_def_addr_mode_desc *addr_mode_def = args->addr_mode_def;
    inst_part *instruction_part = args->instruction_part;
    if (args->phase == IPPP_FIRST_PHASE) {
        /* Encoder has to set some flags for XOP/VEX prefix encoder. */
        extension_prefixes_fields *epf = &(args->context->epf);
        int opcode_bytes = FCML_DEF_OPCODE_FLAGS_OPCODE_NUM(
                addr_mode_def->opcode_flags);
        int i = 0;
        int code_index = 0;
        fcml_uint8_t opcode_byte = addr_mode_def->opcode[i++];
        switch (opcode_byte) {
        case 0x0F: {
            opcode_byte = addr_mode_def->opcode[i++];
            switch (opcode_byte) {
            case 0x38:
                epf->mmmm = 0x02;
                break;
            case 0x3A:
                epf->mmmm = 0x03;
                break;
            default:
                instruction_part->code[code_index++] = opcode_byte;
                epf->mmmm = 0x01;
                break;
            }
            break;
        }
        case 0x08:
        case 0x09:
        case 0x0A:
            epf->mmmm = opcode_byte;
            break;
        }
        for (; i < opcode_bytes; i++) {
            instruction_part->code[code_index++] = addr_mode_def->opcode[i];
        }
        instruction_part->code_length = code_index;
    }
    return FCML_CEH_GEC_NO_ERROR;
}

static ipp_desc ipp_AVX_opcode_encoder_factory(ipp_factory_args *args,
        fcml_ceh_error *error) {
    ipp_desc descriptor = { 0 };
    if (FCML_DEF_PREFIX_IS_AVX_REQ(args->addr_mode->allowed_prefixes)) {
        descriptor.type = IPPT_ENCODER;
        descriptor.args = NULL;
        descriptor.encoder = ipp_AVX_opcode_encoder;
        descriptor.acceptor = NULL;
    }
    return descriptor;
}

/***********************************/
/* Generic primary opcode encoder. */
/***********************************/

typedef fcml_uint8_t (*opcode_byte_encoder)(encoding_context*,
        const addr_mode_desc_details*, const fcml_st_def_addr_mode_desc*,
        fcml_uint8_t opcode);

typedef struct opcode_byte_encoder_wrapper {
    opcode_byte_encoder opcode_byte_encoder;
} opcode_byte_encoder_wrapper;

static fcml_ceh_error ipp_generic_primary_opcode_encoder(ipp_encoder_args *args) {
    const fcml_st_def_addr_mode_desc *addr_mode_def = args->addr_mode_def;
    inst_part *instruction_part = args->instruction_part;
    if (args->phase == IPPP_SECOND_PHASE) {
        opcode_byte_encoder opcode_byte_encoder = NULL;
        opcode_byte_encoder_wrapper *wrapper = (opcode_byte_encoder_wrapper*)args->args;
        if (wrapper) {
            opcode_byte_encoder = wrapper->opcode_byte_encoder;
        }
        int opcode_bytes = FCML_DEF_OPCODE_FLAGS_OPCODE_NUM(
                addr_mode_def->opcode_flags);
        int primary_opcode = FCML_DEF_OPCODE_FLAGS_PRIMARY_OPCODE(
                addr_mode_def->opcode_flags);
        int i;
        for (i = 0; i < opcode_bytes; i++) {
            fcml_uint8_t opcode_byte = addr_mode_def->opcode[i];
            instruction_part->code[i] = (i == primary_opcode) ?
                    opcode_byte_encoder(args->context, args->addr_mode_details,
                            addr_mode_def, opcode_byte) : opcode_byte;
        }
        instruction_part->code_length = opcode_bytes;
    }

    return FCML_CEH_GEC_NO_ERROR;
}

/*********************************************************/
/* Opcode with condition encoded (tttn) encoder factory. */
/*********************************************************/

static fcml_uint8_t conditional_primary_opcode_byte_encoder(
        encoding_context *context,
        const addr_mode_desc_details *addr_mode_details,
        const fcml_st_def_addr_mode_desc *addr_mode_def, fcml_uint8_t opcode) {
    return opcode + addr_mode_details->condition.condition_type * 2 +
            (addr_mode_details->condition.is_negation ? 1 : 0);
}

static opcode_byte_encoder_wrapper conditional_opcode_encoder_wrapper = {
        &conditional_primary_opcode_byte_encoder
};

static ipp_desc ipp_conditional_opcode_encoder_factory(ipp_factory_args *args,
        fcml_ceh_error *error) {
    ipp_desc descriptor = { 0 };
    if (FCML_DEF_OPCODE_FLAGS_OPCODE_FIELD_TTTN(args->addr_mode->opcode_flags)) {
        descriptor.type = IPPT_ENCODER;
        descriptor.args = &conditional_opcode_encoder_wrapper;
        descriptor.encoder = ipp_generic_primary_opcode_encoder;
        descriptor.acceptor = NULL;
    }
    return descriptor;
}

/**************************************************/
/* Opcode with register encoded encoder factory.  */
/**************************************************/

static fcml_uint8_t reg_primary_opcode_byte_encoder(
        encoding_context *context,
        const addr_mode_desc_details *addr_mode_details,
        const fcml_st_def_addr_mode_desc *addr_mode_def, fcml_uint8_t opcode) {
    return opcode + context->opcode_reg.opcode_reg;
}

static opcode_byte_encoder_wrapper primary_opcode_encoder_wrapper = {
        &reg_primary_opcode_byte_encoder
};

static ipp_desc ipp_reg_opcode_encoder_factory(ipp_factory_args *args,
        fcml_ceh_error *error) {
    ipp_desc descriptor = { 0 };
    if (FCML_DEF_OPCODE_FLAGS_OPCODE_FIELD_REG(args->addr_mode->opcode_flags)) {
        descriptor.type = IPPT_ENCODER;
        descriptor.args = &primary_opcode_encoder_wrapper;
        descriptor.encoder = ipp_generic_primary_opcode_encoder;
        descriptor.acceptor = NULL;
    }
    return descriptor;
}

/**********************************/
/* Simple opcode encoder factory. */
/**********************************/

static fcml_ceh_error ipp_simple_opcode_encoder(ipp_encoder_args *args) {
    inst_part *instruction_part = args->instruction_part;
    if (args->phase == IPPP_FIRST_PHASE) {
        int opcode_bytes = FCML_DEF_OPCODE_FLAGS_OPCODE_NUM(
                args->addr_mode_def->opcode_flags);
        int i;
        for (i = 0; i < opcode_bytes; i++) {
            instruction_part->code[i] = args->addr_mode_def->opcode[i];
        }
        instruction_part->code_length = opcode_bytes;
    }
    return FCML_CEH_GEC_NO_ERROR;
}

static ipp_desc ipp_simple_opcode_encoder_factory(ipp_factory_args *args,
        fcml_ceh_error *error) {
    ipp_desc descriptor = { 0 };
    descriptor.type = IPPT_ENCODER;
    descriptor.args = NULL;
    descriptor.encoder = ipp_simple_opcode_encoder;
    descriptor.acceptor = NULL;
    return descriptor;
}

/*******************/
/* Suffix encoder. */
/*******************/

static fcml_ceh_error ipp_instruction_suffix_encoder(ipp_encoder_args *args) {
    inst_part *instruction_part = args->instruction_part;
    if (args->phase == IPPP_FIRST_PHASE) {
        if (args->context->mnemonic->suffix.is_not_null) {
            instruction_part->code[0] = args->context->mnemonic->suffix.value;
            instruction_part->code_length = 1;
        }
    }
    return FCML_CEH_GEC_NO_ERROR;
}

static ipp_desc ipp_suffix_encoder_factory(ipp_factory_args *args,
        fcml_ceh_error *error) {
    ipp_desc descriptor = { 0 };
    if (FCML_DEF_PREFIX_SUFFIX(args->addr_mode->allowed_prefixes)) {
        descriptor.type = IPPT_ENCODER;
        descriptor.args = NULL;
        descriptor.encoder = ipp_instruction_suffix_encoder;
        descriptor.acceptor = NULL;
    }
    return descriptor;
}

/*******************************/
/* Prefixes encoder factories. */
/*******************************/

/* Branch hints.*/

static fcml_ceh_error ipp_branch_hints_prefix_encoder(ipp_encoder_args *args) {
    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
    inst_part *instruction_part = args->instruction_part;
    if (args->phase == IPPP_THIRD_PHASE) {
        const fcml_st_instruction *instruction = args->context->instruction;
        if (instruction->prefixes & FCML_PREFIX_BRANCH_HINT) {
            instruction_part->code[0] = 0x3E;
            instruction_part->code_length = 1;
        } else if (instruction->prefixes & FCML_PREFIX_NOBRANCH_HINT) {
            instruction_part->code[0] = 0x2E;
            instruction_part->code_length = 1;
        }
    }
    return error;
}

static ipp_desc ipp_branch_hints_prefix_encoder_factory(
        ipp_factory_args *args, fcml_ceh_error *error) {
    ipp_desc descriptor = { 0 };
    /* Branch hints are allowed only for JCC instructions.*/
    if (args->instruction->instruction == F_JCC) {
        descriptor.type = IPPT_ENCODER;
        descriptor.args = NULL;
        descriptor.encoder = ipp_branch_hints_prefix_encoder;
        descriptor.acceptor = NULL;
    }
    return descriptor;
}

/* REP prefix.*/

static fcml_ceh_error ipp_rep_prefix_encoder(ipp_encoder_args *args) {
    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
    inst_part *instruction_part = args->instruction_part;
    if (args->phase == IPPP_THIRD_PHASE) {
        if (args->context->instruction->prefixes & FCML_PREFIX_REP) {
            instruction_part->code[0] = 0xF3;
            instruction_part->code_length = 1;
        }
    }
    return error;
}

static ipp_desc ipp_rep_prefix_encoder_factory(ipp_factory_args *args,
        fcml_ceh_error *error) {
    ipp_desc descriptor = { 0 };
    if (FCML_DEF_PREFIX_REP_XRELEASE_ALLOWED(
            args->addr_mode->allowed_prefixes) &&
            !FCML_DEF_PREFIX_HLE_ENABLED(args->addr_mode->allowed_prefixes)) {
        descriptor.type = IPPT_ENCODER;
        descriptor.args = NULL;
        descriptor.encoder = ipp_rep_prefix_encoder;
        descriptor.acceptor = NULL;
    }
    return descriptor;
}

/* REPNE prefix.*/

static fcml_ceh_error ipp_repne_prefix_encoder(ipp_encoder_args *args) {
    inst_part *instruction_part = args->instruction_part;
    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
    if (args->phase == IPPP_THIRD_PHASE) {
        if (args->context->instruction->prefixes & FCML_PREFIX_REPNE) {
            instruction_part->code[0] = 0xF2;
            instruction_part->code_length = 1;
        }
    }
    return error;
}

static ipp_desc ipp_repne_prefix_encoder_factory(ipp_factory_args *args,
        fcml_ceh_error *error) {
    ipp_desc descriptor = { 0 };
    if (FCML_DEF_PREFIX_REPNE_XACQUIRE_ALLOWED(
            args->addr_mode->allowed_prefixes) &&
            !FCML_DEF_PREFIX_HLE_ENABLED(args->addr_mode->allowed_prefixes)) {
        descriptor.type = IPPT_ENCODER;
        descriptor.args = NULL;
        descriptor.encoder = ipp_repne_prefix_encoder;
        descriptor.acceptor = NULL;
    }
    return descriptor;
}

/* HLE prefixes.*/

static fcml_ceh_error ipp_hle_prefixes_prefix_encoder(ipp_encoder_args *args) {
    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
    encoding_context *context = args->context;
    const fcml_st_def_addr_mode_desc *addr_mode_def = args->addr_mode_def;
    inst_part *instruction_part = args->instruction_part;
    if (args->phase == IPPP_THIRD_PHASE) {
        fcml_bool found = FCML_FALSE;
        if (context->instruction->prefixes & FCML_PREFIX_XACQUIRE) {
            if (FCML_DEF_PREFIX_REPNE_XACQUIRE_ALLOWED(
                    addr_mode_def->allowed_prefixes)) {
                instruction_part->code[0] = 0xF2;
                instruction_part->code_length = 1;
                found = FCML_TRUE;
            } else {
                add_error(&context->errors,
                        fcml_fn_msg_get_message(
                                FCML_MC_SEGMENT_HLE_PREFIXES_NOT_ALLOWED),
                        FCML_CEH_MEC_ERROR_HLE_PREFIX_NOT_ALLOWED);
                return FCML_CEH_GEC_INVALID_PREFIX;
            }
        }
        if (context->instruction->prefixes & FCML_PREFIX_XRELEASE) {
            if (found) {
                /* Only one HLA prefix is allowed for instruction.*/
                add_error(&context->errors,
                        fcml_fn_msg_get_message(
                                FCML_MC_SEGMENT_HLE_MORE_THAN_ONE_PREFIX),
                        FCML_CEH_MEC_ERROR_HLE_MORE_THAN_ONE_PREFIX);
                return FCML_CEH_GEC_INVALID_PREFIX;
            }
            if (FCML_DEF_PREFIX_REP_XRELEASE_ALLOWED(
                    addr_mode_def->allowed_prefixes)) {
                instruction_part->code[0] = 0xF3;
                instruction_part->code_length = 1;
            } else {
                add_error(&context->errors,
                        fcml_fn_msg_get_message(
                                FCML_MC_SEGMENT_HLE_PREFIXES_NOT_ALLOWED),
                        FCML_CEH_MEC_ERROR_HLE_PREFIX_NOT_ALLOWED);
                return FCML_CEH_GEC_INVALID_PREFIX;
            }
        }
    }
    return error;
}

static ipp_desc ipp_hle_prefixes_encoder_factory(ipp_factory_args *args,
        fcml_ceh_error *error) {
    ipp_desc descriptor = { 0 };
    if (FCML_DEF_PREFIX_HLE_ENABLED(args->addr_mode->allowed_prefixes)) {
        descriptor.type = IPPT_ENCODER;
        descriptor.args = NULL;
        descriptor.encoder = ipp_hle_prefixes_prefix_encoder;
        descriptor.acceptor = NULL;
    }
    return descriptor;
}

/* Lock prefix.*/

static fcml_ceh_error ipp_lock_prefix_encoder(ipp_encoder_args *args) {
    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
    encoding_context *context = args->context;
    const fcml_st_def_addr_mode_desc *addr_mode_def = args->addr_mode_def;
    inst_part *instruction_part = args->instruction_part;
    if (args->phase == IPPP_THIRD_PHASE) {
        /* For instruction that supports LOCK prefixes as well as HLA ones,
         * LOCK prefix is mandatory. XCHG is only one exception from
         * that rule, and in its case
         * lock prefix can be ignored.
         */
        if (FCML_DEF_PREFIX_HLE_ENABLED(addr_mode_def->allowed_prefixes)
                && ((context->instruction->prefixes & FCML_PREFIX_XACQUIRE)
                        || (context->instruction->prefixes
                                & FCML_PREFIX_XRELEASE))) {
            if (!(context->instruction->prefixes & FCML_PREFIX_LOCK)) {
                /* XCHG instruction do not need LOCK prefix.*/
                if (addr_mode_def->opcode[0] != 0x86
                        && addr_mode_def->opcode[0] != 0x87) {
                    return FCML_CEH_GEC_INVALID_PREFIX;
                }
            }
        }
        if (context->instruction->prefixes & FCML_PREFIX_LOCK) {
            instruction_part->code[0] = 0xF0;
            instruction_part->code_length = 1;
        }
    }
    return error;
}

static ipp_desc ipp_lock_prefix_encoder_factory(ipp_factory_args *args,
        fcml_ceh_error *error) {
    ipp_desc descriptor = { 0 };
    if (FCML_DEF_PREFIX_LOCK_ALLOWED(args->addr_mode->allowed_prefixes)) {
        descriptor.type = IPPT_ENCODER;
        descriptor.args = NULL;
        descriptor.encoder = ipp_lock_prefix_encoder;
        descriptor.acceptor = NULL;
    }
    return descriptor;
}

/* Segment override prefix.*/

static fcml_uint8_t prefix_override_map[] = {
        0x26, 0x2e, 0x36, 0x3e, 0x64, 0x65
};

static fcml_ceh_error ipp_segment_override_prefix_encoder(
        ipp_encoder_args *args) {
    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
    inst_part *instruction_part = args->instruction_part;
    if (args->phase == IPPP_THIRD_PHASE) {
        if (args->context->segment_override.type == FCML_REG_SEG) {
            fcml_uint8_t seg_reg_num = args->context->segment_override.reg;
            if (seg_reg_num <= 5) {
                instruction_part->code[0] = prefix_override_map[seg_reg_num];
                instruction_part->code_length = 1;
            } else {
                /* Wrong register type. This check is done just is case,
                 * this code should never be invoked due to earlier
                 * sanity checks. */
                FCML_TRACE_MSG("Unknown segment register found.");
                error = FCML_CEH_GEC_INTERNAL_ERROR;
            }
        }
    }
    return error;
}

static ipp_desc ipp_segment_override_prefix_encoder_factory(
        ipp_factory_args *args, fcml_ceh_error *error) {
    ipp_desc descriptor = { 0 };
    descriptor.type = IPPT_ENCODER;
    descriptor.args = NULL;
    descriptor.encoder = ipp_segment_override_prefix_encoder;
    descriptor.acceptor = NULL;
    return descriptor;
}

/* Mandatory prefixes.*/

static fcml_ceh_error ipp_mandatory_prefixes_encoder(
        ipp_encoder_args *args) {
    const fcml_st_def_addr_mode_desc *addr_mode_def = args->addr_mode_def;
    inst_part *instruction_part = args->instruction_part;
    if (args->phase == IPPP_THIRD_PHASE) {
        fcml_uint8_t prefix = 0x66;
        if (FCML_DEF_PREFIX_MANDATORY_F2(addr_mode_def->allowed_prefixes)) {
            prefix = 0xF2;
        } else if (FCML_DEF_PREFIX_MANDATORY_F3(
                addr_mode_def->allowed_prefixes)) {
            prefix = 0xF3;
        }
        instruction_part->code[0] = prefix;
        instruction_part->code_length = 1;
    }
    return FCML_CEH_GEC_NO_ERROR;
}

static ipp_desc ipp_mandatory_prefixes_encoder_factory(ipp_factory_args *args,
        fcml_ceh_error *error) {

    ipp_desc descriptor = { 0 };
    const fcml_st_def_addr_mode_desc *addr_mode = args->addr_mode;

    fcml_bool is_mandatory =
            FCML_DEF_PREFIX_MANDATORY_66(addr_mode->allowed_prefixes) ||
            FCML_DEF_PREFIX_MANDATORY_F2(addr_mode->allowed_prefixes) ||
            FCML_DEF_PREFIX_MANDATORY_F3(addr_mode->allowed_prefixes);

    /* Mandatory prefixes cannot be applied to AVX instructions. */
    if (is_mandatory &&
            !FCML_DEF_PREFIX_IS_AVX_REQ(addr_mode->allowed_prefixes)) {
        descriptor.type = IPPT_ENCODER;
        descriptor.args = NULL;
        descriptor.encoder = ipp_mandatory_prefixes_encoder;
        descriptor.acceptor = NULL;
    }

    return descriptor;
}

/* 66 prefix.*/

static fcml_ceh_error ipp_66_prefix_encoder(ipp_encoder_args *args) {
    encoding_context *context = args->context;
    const fcml_st_def_addr_mode_desc *addr_mode_def = args->addr_mode_def;
    inst_part *instruction_part = args->instruction_part;
    if (args->phase == IPPP_THIRD_PHASE) {
        fcml_bool encode = FCML_FALSE;
        fcml_uint64_t addr_type = addr_mode_def->instruction_group;
        /* Mandatory 0x66 prefix is encoded in different way in case of
         * VEX encoded instructions. */
        if (!(addr_type & FCML_AMT_VEXx)) {
            if (FCML_DEF_PREFIX_MANDATORY_66(addr_mode_def->allowed_prefixes)) {
                encode = FCML_TRUE;
                /* SIMD instructions do not need 0x66 to change EOSA.*/
            } else if (!(addr_type & FCML_AMT_SIMD)) {
                const fcml_st_entry_point *entry_point =
                        &(context->assembler_context->entry_point);
                fcml_usize osa = entry_point->operand_size_attribute;
                fcml_usize eosa = context->optimizer_processing_details.eosa;
                encode = (osa == FCML_DS_16 && eosa == FCML_DS_32)
                        || (osa == FCML_DS_32 && eosa == FCML_DS_16)
                        || (osa == FCML_DS_64 && eosa == FCML_DS_32);
            }
            if (encode) {
                instruction_part->code[0] = 0x66;
                instruction_part->code_length = 1;
            }
        }
    }
    return FCML_CEH_GEC_NO_ERROR;
}

static ipp_desc ipp_66_prefix_encoder_factory(
        ipp_factory_args *args, fcml_ceh_error *error) {
    ipp_desc descriptor = { 0 };
    /* Mandatory prefixes are handled by dedicated IPP. */
    if (!FCML_DEF_PREFIX_MANDATORY_66(args->addr_mode->allowed_prefixes) &&
            !FCML_DEF_PREFIX_IS_AVX_REQ(args->addr_mode->allowed_prefixes)) {
        descriptor.type = IPPT_ENCODER;
        descriptor.args = NULL;
        descriptor.encoder = ipp_66_prefix_encoder;
        descriptor.acceptor = NULL;
    }
    return descriptor;
}

/* 67 prefix. */

static fcml_ceh_error ipp_67_prefix_encoder(ipp_encoder_args *args) {
    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
    encoding_context *context = args->context;
    inst_part *instruction_part = args->instruction_part;
    if (args->phase == IPPP_THIRD_PHASE) {
        /* If effective address size is not set, it means that instruction
         * is not interested in ASA and just doesn't use it. */
        const fcml_st_entry_point *entry_point =
                &(context->assembler_context->entry_point);
        fcml_usize asa = entry_point->address_size_attribute;
        fcml_usize easa = context->optimizer_processing_details.easa;
        if (easa && (asa != easa)) {
            if ((asa == FCML_DS_16 && easa == FCML_DS_32)
                    || (asa == FCML_DS_32 && easa == FCML_DS_16)
                    || (asa == FCML_DS_64 && easa == FCML_DS_32)) {
                instruction_part->code[0] = 0x67;
                instruction_part->code_length = 1;
            } else {
                error = FCML_CEH_GEC_INVALID_ADDRESS_SIZE;
            }
        }
    }
    return error;
}

static ipp_desc ipp_67_prefix_encoder_factory(ipp_factory_args *args,
        fcml_ceh_error *error) {
    ipp_desc descriptor = { 0 };
    /* 67 prefix cannot be applied to AVX instructions. */
    if (!FCML_DEF_PREFIX_IS_AVX_REQ(args->addr_mode->allowed_prefixes)) {
        descriptor.type = IPPT_ENCODER;
        descriptor.args = NULL;
        descriptor.encoder = ipp_67_prefix_encoder;
        descriptor.acceptor = NULL;
    }
    return descriptor;
}

/************/
/**  EVEX  **/
/************/

static fcml_uint8_t encode_pp_prefix_field(fcml_uint32_t allowed_prefixes) {
    fcml_uint8_t pp = 0;
    if (FCML_DEF_PREFIX_MANDATORY_66(allowed_prefixes)) {
        pp = 0x01;
    } else if (FCML_DEF_PREFIX_MANDATORY_F2(allowed_prefixes)) {
        pp = 0x03;
    } else if (FCML_DEF_PREFIX_MANDATORY_F3(allowed_prefixes)) {
        pp = 0x02;
    }
    return pp;
}

/* Encodes decorators if there are any defined for an operand. */
static void encode_decorators(encoding_context *context,
        const fcml_st_def_addr_mode_desc *addr_mode_def,
        fcml_operand_decorators decorators,
        const fcml_st_operand *operand) {


    /* Opmask decorator. */
    if (FCML_IS_DECOR_OPMASK_REG(decorators)) {
        if (operand->decorators.operand_mask_reg.type == FCML_REG_OPMASK) {
            context->epf.aaa = operand->decorators.operand_mask_reg.reg;
        }
    }

    /* Zeroing-masking is not supported by instructions that write to memory. */
    if (operand->type == FCML_OT_REGISTER && FCML_IS_DECOR_Z(decorators)) {
        context->epf.z = operand->decorators.z;
    }

    if (FCML_IS_DECOR_SAE(decorators) || FCML_IS_DECOR_ER(decorators)) {
        fcml_uint8_t tuple_type = FCML_GET_SIMD_TUPLETYPE(addr_mode_def->details);
        /* For these tuple types vector length is explicitly set and
         * and there is no need to set L, L' flags. */
        if(tuple_type == FCML_TT_FV || tuple_type == FCML_TT_T1S || tuple_type == FCML_TT_T1F) {
            context->epf.explicit_vector_length = FCML_TRUE;
        }
    }
}

static fcml_ceh_error ipp_EVEX_prefix_encoder(ipp_encoder_args *args) {
    encoding_context *context = args->context;
    const fcml_st_def_addr_mode_desc *addr_mode_def = args->addr_mode_def;
    inst_part *instruction_part = args->instruction_part;

    if (args->phase == IPPP_FIRST_PHASE) {
        fcml_bool l0 = FCML_DEF_PREFIX_L_0(addr_mode_def->allowed_prefixes);
        fcml_bool l1 = FCML_DEF_PREFIX_L_1(addr_mode_def->allowed_prefixes);
        fcml_bool l_prim_0 = FCML_DEF_PREFIX_L_prim_0(addr_mode_def->allowed_prefixes);
        fcml_bool l_prim_1 = FCML_DEF_PREFIX_L_prim_1(addr_mode_def->allowed_prefixes);

        if (!l_prim_1) {
            if (l1) {
                context->optimizer_processing_details.vector_length = FCML_DS_256;
            } else if (l0) {
                context->optimizer_processing_details.vector_length = FCML_DS_128;
            }
        } else if (!l1) {
            context->optimizer_processing_details.vector_length = FCML_DS_512;
        }

        // Some decorators can be encoded here globally, as we do not need any
        // custom code dedicated for given operand type. The only information
        // which is needed here is a list of supported decorators and actual
        // decorators from the instruction model for a given operand. In fact
        // we don't even care if we are dealing with a register operand or a
        // memory addressing as long as the operand supports decorators.
        for (int i = 0; i < context->instruction->operands_count; i++) {
            fcml_operand_decorators supported_decorators =
                    FCML_DECORATORS(addr_mode_def->operands[i]);
            const fcml_st_operand *operand = &context->instruction->operands[i];
            encode_decorators(context, addr_mode_def, supported_decorators, operand);
        }
    }

    if (args->phase == IPPP_SECOND_PHASE) {
        /* If vector length wasn't set in the first phase, we have to assume
         * that 128-bit vector length is used. Properly set vector length is
         * needed to encode compressed disp8 for instance. */
        // TODO: Vector length is used by fcml_ifn_asm_ipp_ModRM_encoder in the second phase.
        // We should consider moving this code there or somewhere else to make sure
        // it's properly set in the second phase.
        if (!context->optimizer_processing_details.vector_length) {
            context->optimizer_processing_details.vector_length = FCML_DS_128;
        }
    }

    if (args->phase == IPPP_THIRD_PHASE) {

        extension_prefixes_fields *epf = &(context->epf);
        fcml_st_encoded_modrm *encoded_mod_rm = &(context->encoded_mod_rm);

        fcml_uint8_t p0 = 0;
        p0 = FCML_ENCODE_EVEX_P0_R(p0, encoded_mod_rm->ext_R);
        p0 = FCML_ENCODE_EVEX_P0_X(p0, encoded_mod_rm->ext_X);
        p0 = FCML_ENCODE_EVEX_P0_B(p0, encoded_mod_rm->ext_B);
        p0 = FCML_ENCODE_EVEX_P0_R_prim(p0, encoded_mod_rm->ext_R_prim);
        p0 = FCML_ENCODE_EVEX_P0_mm(p0, epf->mmmm);

        /* Third bit of P1 is always set to 1. */
        fcml_uint8_t p1 = 0x04;
        p1 = FCML_ENCODE_EVEX_P1_W(p1, FCML_DEF_PREFIX_W_1(
                addr_mode_def->allowed_prefixes));
        p1 = FCML_ENCODE_EVEX_P1_vvvv(p1, epf->vvvv);
        p1 = FCML_ENCODE_EVEX_P1_pp(p1, encode_pp_prefix_field(
                addr_mode_def->allowed_prefixes));

        fcml_uint8_t p2 = 0;
        p2 = FCML_ENCODE_EVEX_P2_z(p2, epf->z);

        if (epf->er.is_not_null) {
            /* Embedded rounding mode is encoded on EVEX.L'L. */
            p2 = FCML_ENCODE_EVEX_P2_LL(p2, epf->er.value);
        } else {
            fcml_uint8_t LL = 0;
            if (!context->epf.explicit_vector_length) {
                switch(context->optimizer_processing_details.vector_length) {
                case FCML_DS_256:
                    LL = 0x01;
                    break;
                case FCML_DS_512:
                    LL = 0x02;
                    break;
                }
            }
            p2 = FCML_ENCODE_EVEX_P2_LL(p2, LL);
        }

        p2 = FCML_ENCODE_EVEX_P2_b(p2, epf->b);
        /* EVEX.V' is used by extended VSIB encoding and direct register
           encoding. */
        p2 = FCML_ENCODE_EVEX_P2_V_prim(p2, encoded_mod_rm->ext_V_prim |
                epf->V_prim);
        p2 = FCML_ENCODE_EVEX_P2_aaa(p2, epf->aaa);

        instruction_part->code[0] = 0x62;
        instruction_part->code[1] = p0;
        instruction_part->code[2] = p1;
        instruction_part->code[3] = p2;
        instruction_part->code_length = FCML_ENCODE_EVEX_PREFIX_LENGTH;
    }

    return FCML_CEH_GEC_NO_ERROR;
}

static ipp_desc ipp_EVEX_prefix_encoder_factory(ipp_factory_args *args,
        fcml_ceh_error *error) {
    ipp_desc descriptor = { 0 };
    if (FCML_DEF_PREFIX_EVEX_REQ(args->addr_mode->allowed_prefixes)) {
        descriptor.type = IPPT_ENCODER;
        descriptor.args = NULL;
        descriptor.encoder = ipp_EVEX_prefix_encoder;
        descriptor.acceptor = NULL;
    }
    return descriptor;
}

/********************/
/** VEX/XOP Prefix **/
/********************/

static fcml_ceh_error ipp_VEX_XOP_prefix_encoder(ipp_encoder_args *args) {

    encoding_context *context = args->context;
    const fcml_st_def_addr_mode_desc *addr_mode_def = args->addr_mode_def;
    inst_part *instruction_part = args->instruction_part;

    if (args->phase == IPPP_FIRST_PHASE) {
        if (FCML_DEF_PREFIX_L_1(addr_mode_def->allowed_prefixes)) {
            context->optimizer_processing_details.vector_length = FCML_DS_256;
        } else if (FCML_DEF_PREFIX_L_0(addr_mode_def->allowed_prefixes)) {
            context->optimizer_processing_details.vector_length = FCML_DS_128;
        }
    } else if (args->phase == IPPP_THIRD_PHASE) {
        extension_prefixes_fields *epf = &(context->epf);
        fcml_st_encoded_modrm *encoded_mod_rm = &(context->encoded_mod_rm);
        /* Check if one byte VEX encoding can be used.*/
        fcml_bool is_vex = FCML_DEF_PREFIX_VEX_REQ(
                addr_mode_def->allowed_prefixes);
        /* Remember, the 2-byte VEX implies a leading 0Fh opcode byte,
         * it's why "m-mmmm" field should be 1. */
        fcml_bool is_two_bytes_vex =
                (!context->assembler_context->configuration.force_three_byte_VEX
                        && is_vex && epf->mmmm == 0x01
                        && !FCML_DEF_PREFIX_W_1(addr_mode_def->allowed_prefixes)
                        && !encoded_mod_rm->ext_X && !encoded_mod_rm->ext_B);

        fcml_uint8_t prefix_bytes[3];
        fcml_uint8_t prefix_size = 0;

        /* Encode PP.*/
        fcml_uint8_t pp = encode_pp_prefix_field(
                addr_mode_def->allowed_prefixes);

        fcml_uint8_t prefix = 0;

        /* If an instruction syntax can be encoded using the two-byte form,
         * it can also be encoded using the three byte form of VEX. Three byte
         * VEX can be forced using configuration or "long_form"
         * instruction level hint. */
        if (context->assembler_context->configuration.force_three_byte_VEX
                || (context->instruction->hints &
                        FCML_HINT_LONG_FORM_POINTER)) {
            is_two_bytes_vex = FCML_FALSE;
        }

        fcml_usize vector_length =
                context->optimizer_processing_details.vector_length;

        /* VEX/XOP supports 128/256 vector length only. */
        if (vector_length > FCML_DS_256) {
            add_error(&context->errors,
                    fcml_fn_msg_get_message(
                            FCML_MC_CEH_GEC_INVALID_OPPERAND_SIZE),
                            FCML_CEH_MEC_ERROR_INVALID_VECTOR_LENGTH);
            return FCML_CEH_GEC_INVALID_OPPERAND_SIZE;
        }

        if (is_two_bytes_vex) {
            /* Two bytes VEX prefix.*/
            prefix = FCML_ENCODE_VEXOP_R(prefix, encoded_mod_rm->ext_R);
            prefix = FCML_ENCODE_VEXOP_VVVV(prefix, epf->vvvv);
            if (vector_length == FCML_DS_256) {
                prefix = FCML_ENCODE_VEXOP_L(prefix, 0x01);
            }
            prefix = FCML_ENCODE_VEXOP_PP(prefix, pp);
            prefix_bytes[0] = 0xC5;
            prefix_bytes[1] = prefix;
            prefix_size = 2;
        } else {
            /* Three bytes VEX or XOP prefix. */
            prefix_bytes[0] = (is_vex) ? 0xC4 : 0x8F;
            prefix = FCML_ENCODE_VEXOP_R(prefix, encoded_mod_rm->ext_R);
            prefix = FCML_ENCODE_VEXOP_X(prefix, encoded_mod_rm->ext_X);
            prefix = FCML_ENCODE_VEXOP_B(prefix, encoded_mod_rm->ext_B);
            prefix = FCML_ENCODE_VEXOP_MMMM(prefix, epf->mmmm);
            prefix_bytes[1] = prefix;
            prefix = 0;
            prefix = FCML_ENCODE_VEXOP_W(prefix,
                    FCML_DEF_PREFIX_W_1(addr_mode_def->allowed_prefixes));
            prefix = FCML_ENCODE_VEXOP_VVVV(prefix, epf->vvvv);
            if (vector_length == FCML_DS_256) {
                prefix = FCML_ENCODE_VEXOP_L(prefix, 0x01);
            }
            prefix = FCML_ENCODE_VEXOP_PP(prefix, pp);
            prefix_bytes[2] = prefix;
            prefix_size = 3;
        }

        int i;
        for (i = 0; i < prefix_size; i++) {
            instruction_part->code[i] = prefix_bytes[i];
        }
        instruction_part->code_length = prefix_size;
    }

    return FCML_CEH_GEC_NO_ERROR;
}

static ipp_desc ipp_VEX_XOP_prefix_encoder_factory(
        ipp_factory_args *args, fcml_ceh_error *error) {
    ipp_desc descriptor = { 0 };
    if (FCML_DEF_PREFIX_VEX_REQ(args->addr_mode->allowed_prefixes) ||
            FCML_DEF_PREFIX_XOP_REQ(args->addr_mode->allowed_prefixes)) {
        descriptor.type = IPPT_ENCODER;
        descriptor.args = NULL;
        descriptor.encoder = ipp_VEX_XOP_prefix_encoder;
        descriptor.acceptor = NULL;
    }
    return descriptor;
}

/* REX prefix.*/

static fcml_ceh_error ipp_REX_prefix_encoder(ipp_encoder_args *args) {
    encoding_context *context = args->context;
    const fcml_st_def_addr_mode_desc *addr_mode_def = args->addr_mode_def;
    inst_part *instruction_part = args->instruction_part;

    if (args->phase == IPPP_THIRD_PHASE) {
        /* REX prefix is only available in 64 bit mode. Neither VEX nor
         * XOP are allowed here, but it's checked before this encoder
         * is registered for
         */
        if (context->assembler_context->entry_point.op_mode == FCML_OM_64_BIT) {

            fcml_uint8_t rex = FCML_ENCODE_REX_BASE;
            fcml_st_asm_optimizer_processing_details *size_flags =
                    &(context->optimizer_processing_details);
            fcml_st_encoded_modrm *encoded_mod_rm = &(context->encoded_mod_rm);
            fcml_st_modrm *mod_rm = &(context->mod_rm);

            /* W field.*/
            fcml_usize eosa = size_flags->eosa;
            if (FCML_DEF_PREFIX_W_1(addr_mode_def->allowed_prefixes)) {
                if (eosa != 0 && eosa != FCML_DS_64) {
                    /* Operand size should be 64 bits.*/
                    return FCML_CEH_GEC_INVALID_OPPERAND_SIZE;
                }
                rex = FCML_ENCODE_REX_W(rex, 1);
            } else if (eosa == FCML_DS_64
                    && !FCML_DEF_OPCODE_FLAGS_FORCE_64BITS_EOSA(
                            addr_mode_def->opcode_flags) &&
                            !FCML_DEF_OPCODE_FLAGS_64BITS_EOSA_BY_DEFAULT(
                                    addr_mode_def->opcode_flags)) {
                /* When OSA is forced to 64 bits, W flag is needless. */
                rex = FCML_ENCODE_REX_W(rex, 1);
            }

            /* Fields.*/
            rex = FCML_ENCODE_REX_R(rex, encoded_mod_rm->ext_R);
            rex = FCML_ENCODE_REX_X(rex, encoded_mod_rm->ext_X);
            rex = FCML_ENCODE_REX_B(rex, encoded_mod_rm->ext_B);
            rex = FCML_ENCODE_REX_B(rex, context->opcode_reg.ext_b);

            /* Assembler configuration.*/
            const fcml_st_assembler_conf *cfg =
                    &(context->assembler_context->configuration);

            /* Even if REX do not contains any flags set in some cases
             * registers BPL, SPL, DIL, SIL needs REX to be defined.
             * Additionally we can force it to occur by setting a
             * configuration flag. */
            if (rex != FCML_ENCODE_REX_BASE
                    || (FCML_DEF_OPCODE_FLAGS_OPCODE_IS_MODRM(
                            addr_mode_def->opcode_flags)
                            && cfg->force_rex_prefix)
                    || mod_rm->reg_opcode_needs_rex
                    || context->reg_opcode_needs_rex) {
                instruction_part->code[0] = rex;
                instruction_part->code_length = 1;
            }
        }
    }

    return FCML_CEH_GEC_NO_ERROR;
}

static ipp_desc ipp_REX_prefix_encoder_factory(ipp_factory_args *args,
        fcml_ceh_error *error) {

    ipp_desc descriptor = { 0 };

    /* 66 prefix cannot be applied to AVX instructions.
     * Remember that this prefix can be a mandatory one.
     */
    if (FCML_DEF_OPCODE_FLAGS_64_BIT_MODE_SUPPORTED(args->addr_mode->opcode_flags)
            && !FCML_DEF_PREFIX_IS_AVX_REQ(args->addr_mode->allowed_prefixes)) {
        descriptor.type = IPPT_ENCODER;
        descriptor.args = NULL;
        descriptor.encoder = ipp_REX_prefix_encoder;
        descriptor.acceptor = NULL;
    }

    return descriptor;
}

/*****************************/
/* ModR/M encoder factories. */
/*****************************/

static fcml_ceh_error ipp_rip_post_processor(encoding_context *context,
        inst_part *instruction_part, fcml_ptr post_processor_args) {

    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
    const fcml_st_assembler_context *assembler_context =
            context->assembler_context;
    fcml_st_encoded_modrm *encoded_mod_rm = &(context->encoded_mod_rm);

    if (FCML_IS_NULL(context->instruction_size)) {
        /* Should never happened.*/
        FCML_TRACE_MSG("instruction size has to be set here.");
        error = FCML_CEH_GEC_INTERNAL_ERROR;
    } else {
        /* Encode ModR/M and displacement.*/
        fcml_st_memory_stream stream = inst_part_stream(
                instruction_part);
        fcml_fn_stream_write(&stream, encoded_mod_rm->modrm);
        error = fcml_fn_modrm_encode_rip_offset(&stream,
                assembler_context->entry_point.ip,
                context->instruction_size.value, encoded_mod_rm);
    }
    return error;
}

static fcml_ceh_error ipp_ModRM_encoder(ipp_encoder_args *args) {
    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
    encoding_context *context = args->context;
    const fcml_st_def_addr_mode_desc *addr_mode_def = args->addr_mode_def;
    const fcml_st_assembler_context *assembler_context =
            context->assembler_context;
    inst_part *instruction_part = args->instruction_part;

    if (args->phase == IPPP_SECOND_PHASE) {
        fcml_st_modrm_encoder_context ctx;
        ctx.op_mode = assembler_context->entry_point.op_mode;
        /* Chooses relative or absolute addressing. Configuration as well
         * as rel/abs hints take effect only in 64 bit addressing mode. */
        ctx.choose_rip_encoding = !assembler_context->configuration.choose_abs_encoding;
        ctx.choose_sib_encoding = assembler_context->configuration.choose_sib_encoding;

        /* Hints have higher precedence than configuration. */
        if (context->modrm_hints.is_sib_alternative_hint) {
            ctx.choose_sib_encoding = FCML_TRUE;
            /* SIB hint has higher precedence than RIP configuration. There
             * is no way to encode RIP using SIB, so RIP flag has to be
             * cleared in order to encode absolute offset using requested
             * SIB encoding. */
            ctx.choose_rip_encoding = FCML_FALSE;
        }

        if (context->modrm_hints.is_rel_alternative_hint) {
            /* RIP encoding has been forced by using "rel" hint. */
            ctx.choose_rip_encoding = FCML_TRUE;
        }

        if (context->modrm_hints.is_abs_alternative_hint) {
            /* Absolute offset encoding has been forced by using "abs" hint. */
            ctx.choose_rip_encoding = FCML_FALSE;
        }

        ctx.chosen_effective_address_size = 0;
        ctx.effective_address_size = get_effective_address_size(context);
        ctx.input_size = FCML_GET_SIMD_ELEMENT_SIZE(addr_mode_def->details);
        ctx.vector_length = context->optimizer_processing_details.vector_length;
        ctx.is_sib_alternative = FCML_FALSE;

        /* EVEX, compressed disp8. */
        ctx.b = context->epf.b;
        ctx.is_evex = FCML_DEF_PREFIX_EVEX_REQ(addr_mode_def->allowed_prefixes);
        ctx.tuple_type = FCML_GET_SIMD_TUPLETYPE(addr_mode_def->details);

        if (FCML_DEF_OPCODE_FLAGS_OPCODE_IS_EXT(addr_mode_def->opcode_flags)) {
            context->mod_rm.reg_opcode = FCML_DEF_OPCODE_FLAGS_OPCODE_EXT(
                    addr_mode_def->opcode_flags);
        }

        /* Encodes ModR/M bytes.*/
        error = fcml_fn_modrm_encode(&ctx, &(context->mod_rm),
                &(context->encoded_mod_rm));
        if (!error) {
            if (context->optimizer_processing_details.easa
                    == ctx.chosen_effective_address_size) {
                if (context->encoded_mod_rm.is_rip
                        && !context->encoded_mod_rm.is_rip_encoded) {
                    /* ModR/M + 4bytes displacement.*/
                    instruction_part->code_length = 5;
                    instruction_part->post_processor = ipp_rip_post_processor;
                    instruction_part->post_processor_args = NULL;
                } else {
                    fcml_st_memory_stream stream =
                            inst_part_stream(instruction_part);
                    fcml_st_encoded_modrm *encoded_modrm =
                            &(context->encoded_mod_rm);
                    fcml_fn_stream_write(&stream, encoded_modrm->modrm);
                    if (encoded_modrm->sib.is_not_null) {
                        fcml_fn_stream_write(&stream, encoded_modrm->sib.value);
                    }
                    if (encoded_modrm->displacement_size) {
                        fcml_fn_stream_write_bytes(&stream,
                                &(encoded_modrm->displacement),
                                encoded_modrm->displacement_size);
                    }
                    instruction_part->code_length = stream.offset;
                }
            } else {
                /* ModRM encoded to the form not supported by current
                 * addressing mode. For example, addressing mode needs ASA 32,
                 * but assembled ModRM required 16 bit ASA. */
                error = FCML_CEH_GEC_INVALID_ADDRESS_SIZE;
            }
        }
    }
    return error;
}

static ipp_desc ipp_ModRM_encoder_factory(ipp_factory_args *args,
        fcml_ceh_error *error) {
    ipp_desc descriptor = { 0 };
    /* Check if instruction has ModR/M byte.*/
    if (FCML_DEF_OPCODE_FLAGS_OPCODE_IS_MODRM(args->addr_mode->opcode_flags)) {
        descriptor.type = IPPT_ENCODER;
        descriptor.args = NULL;
        descriptor.encoder = ipp_ModRM_encoder;
        descriptor.acceptor = NULL;
    }
    return descriptor;
}

/*******************************/
/* Addressing mode validators. */
/*******************************/

static fcml_ceh_error ipp_addr_mode_acceptor(ipp_acceptor_args *args) {
    struct acceptor_ctx *context = args->context;
    const fcml_st_def_addr_mode_desc *addr_mode_def = args->addr_mode_def;
    const addr_mode_desc_details *addr_mode_details = args->addr_mode_details;
    fcml_en_operating_mode op_mode = context->entry_point->op_mode;
    struct acceptor_optimizer_ctx *optimizer_ctx = &(context->optimizer_ctx);
    fcml_uint32_t opcode_flags = addr_mode_def->opcode_flags;

    if (!FCML_DEF_OPCODE_FLAGS_64_BIT_MODE_SUPPORTED(opcode_flags)
            && op_mode == FCML_OM_64_BIT) {
        return FCML_CEH_GEC_INVALID_OPERATING_MODE;
    } else if (!FCML_DEF_OPCODE_FLAGS_16_32_BIT_MODE_SUPPORTED(opcode_flags)
            && (op_mode == FCML_OM_16_BIT || op_mode == FCML_OM_32_BIT)) {
        return FCML_CEH_GEC_INVALID_OPERATING_MODE;
    }

    /* Set restrictions if there are any.*/
    if (addr_mode_details->allowed_osa != FCML_EN_ASF_ANY) {
        optimizer_ctx->allowed_eosa.flags = addr_mode_details->allowed_osa;
        optimizer_ctx->allowed_eosa.is_set = FCML_TRUE;
    }

    if (addr_mode_details->allowed_asa != FCML_EN_ASF_ANY) {
        optimizer_ctx->allowed_easa.flags = addr_mode_details->allowed_asa;
        optimizer_ctx->allowed_easa.is_set = FCML_TRUE;
    }

    /* Force 64 bit OSA in 64 bit addressing mode.*/
    if (op_mode == FCML_OM_64_BIT) {
        if (FCML_DEF_OPCODE_FLAGS_FORCE_64BITS_EOSA(opcode_flags)) {
            optimizer_ctx->allowed_eosa.flags = FCML_EN_ASF_64;
            optimizer_ctx->allowed_eosa.is_set = FCML_TRUE;
        } else if (FCML_DEF_OPCODE_FLAGS_64BITS_EOSA_BY_DEFAULT(opcode_flags)) {
            /* Remember, if 64 bit EOSA is used by default it can
             * be overridden to 16 bits only. */
            optimizer_ctx->allowed_eosa.flags =
                    (FCML_EN_ASF_64 | FCML_EN_ASF_16);
            optimizer_ctx->allowed_eosa.is_set = FCML_TRUE;
        }
    }
    return FCML_CEH_GEC_NO_ERROR;
}

static ipp_desc ipp_addr_mode_acceptor_factory(ipp_factory_args *args,
        fcml_ceh_error *error) {
    ipp_desc descriptor = { 0 };
    descriptor.type = IPPT_VERIFIER;
    descriptor.args = NULL;
    descriptor.encoder = NULL;
    descriptor.acceptor = ipp_addr_mode_acceptor;
    return descriptor;
}

/************************/
/* Prefixes validators. */
/************************/

static fcml_ceh_error ipp_prefixes_acceptor(ipp_acceptor_args *args) {
    /* Check if LOCK prefix is allowed for given addressing mode.*/
    const fcml_st_instruction *instruction = args->instruction;
    const fcml_st_def_addr_mode_desc *addr_mode_def = args->addr_mode_def;
    if (instruction->prefixes) {
        if ((instruction->prefixes & FCML_PREFIX_LOCK)
                && !FCML_DEF_PREFIX_LOCK_ALLOWED(
                        addr_mode_def->allowed_prefixes)) {
            return FCML_CEH_GEC_INVALID_PREFIX;
        }
        /* Check if REP prefix is allowed for given addressing mode.*/
        if ((instruction->prefixes & FCML_PREFIX_REP)
                && !FCML_DEF_PREFIX_REP_XRELEASE_ALLOWED(
                        addr_mode_def->allowed_prefixes)) {
            return FCML_CEH_GEC_INVALID_PREFIX;
        }
        /* Check if REPNE prefix is allowed for given addressing mode.*/
        if ((instruction->prefixes & FCML_PREFIX_REPNE)
                && !FCML_DEF_PREFIX_REPNE_XACQUIRE_ALLOWED(
                        addr_mode_def->allowed_prefixes)) {
            return FCML_CEH_GEC_INVALID_PREFIX;
        }
        /* Check if XACQUIRED prefix is allowed for given addressing mode.*/
        if ((instruction->prefixes & FCML_PREFIX_XACQUIRE)
                && (!FCML_DEF_PREFIX_HLE_ENABLED(
                        addr_mode_def->allowed_prefixes)
                        || !FCML_DEF_PREFIX_REPNE_XACQUIRE_ALLOWED(
                                addr_mode_def->allowed_prefixes))) {
            return FCML_CEH_GEC_INVALID_PREFIX;
        }
        /* Check if XRELEASE prefix is allowed for given addressing mode.*/
        if ((instruction->prefixes & FCML_PREFIX_XRELEASE)
                && (!FCML_DEF_PREFIX_HLE_ENABLED(
                        addr_mode_def->allowed_prefixes)
                        || !FCML_DEF_PREFIX_REP_XRELEASE_ALLOWED(
                                addr_mode_def->allowed_prefixes))) {
            return FCML_CEH_GEC_INVALID_PREFIX;
        }
    }
    return FCML_CEH_GEC_NO_ERROR;
}

static ipp_desc ipp_prefixes_acceptor_factory( ipp_factory_args *args,
        fcml_ceh_error *error) {
    ipp_desc descriptor = { 0 };
    descriptor.type = IPPT_VERIFIER;
    descriptor.args = NULL;
    descriptor.encoder = NULL;
    descriptor.acceptor = ipp_prefixes_acceptor;
    return descriptor;
}

/*********************************/
/* Operand decorators acceptors. */
/*********************************/

/**
 * Decorators should be accepted here. If a given rule cannot be
 * generalized and there is a need to handle it in a concrete operator
 * acceptor of course it is fine, but we advice to consider this function
 * first in order not to spread decorators acceptance rules all around.
 */
static fcml_ceh_error ipp_op_decorator_acceptor(ipp_acceptor_args *args) {
    const fcml_st_def_addr_mode_desc *addr_mode_def = args->addr_mode_def;
    const fcml_st_instruction *instruction = args->instruction;

    int i;
    for(i = 0; i < FCML_OPERANDS_COUNT; i++) {
        fcml_operand_decorators decorators =
                FCML_DECORATORS(addr_mode_def->operands[i]);
        const fcml_st_operand *operand = &(instruction->operands[i]);
        const fcml_st_operand_decorators *opcode_dec = &(operand->decorators);

        if (opcode_dec->bcast.is_not_null &&
                !FCML_IS_DECOR_BCAST(decorators)) {
            return FCML_CEH_GEC_NOT_SUPPORTED_DECORATOR;
        }

        /* Opmask register */
        const fcml_st_register *opmask_reg = &opcode_dec->operand_mask_reg;
        if (opmask_reg->type != FCML_REG_UNDEFINED) {
            /* k0 register cannot be addressed as a predicate operand */
            if (opmask_reg->type != FCML_REG_OPMASK ||
                    opmask_reg->reg == FCML_REG_K0) {
                return FCML_CEH_GEC_INVALID_OPERAND_DECORATOR;
            }
            if (!FCML_IS_DECOR_OPMASK_REG(decorators)) {
                return FCML_CEH_GEC_NOT_SUPPORTED_DECORATOR;
            }
        }
        /* Opmask register can be mandatory for some instructions. */
        if (FCML_IS_DECOR_OPMASK_REG_REQ(decorators) &&
                opmask_reg->type != FCML_REG_OPMASK) {
            return FCML_CEH_GEC_INVALID_OPERAND_DECORATOR;
        }
        /* Zeroing-masking */
        if (opcode_dec->z) {
            /* Zeroing-masking is not supported for memory addressing.
             * At the moment it's supported only by register operands. */
            if (!FCML_IS_DECOR_Z(decorators) ||
                    operand->type != FCML_OT_REGISTER ||
                    // Zeroing-masking is allowed only if write
                    // mask is defined.
                    opmask_reg->type == FCML_REG_UNDEFINED) {
                return FCML_CEH_GEC_NOT_SUPPORTED_DECORATOR;
            }
        }

        if (opcode_dec->sae && !FCML_IS_DECOR_SAE(decorators)) {
            return FCML_CEH_GEC_NOT_SUPPORTED_DECORATOR;
        }
        if (opcode_dec->er.is_not_null && !FCML_IS_DECOR_ER(decorators)) {
            return FCML_CEH_GEC_NOT_SUPPORTED_DECORATOR;
        }

        /* Sets vector length for SAE and ER decorators. We net this piece of
         * code here in order to have vector length properly set before the
         * first operand is proceeded. */
        if (FCML_IS_DECOR_SAE(decorators) || FCML_IS_DECOR_ER(decorators)) {
            fcml_bool er_or_sae = opcode_dec->sae || opcode_dec->er.is_not_null;
            if (er_or_sae) {
                fcml_usize vector_length = FCML_DS_UNDEF;
                fcml_uint8_t tuple_type =
                        FCML_GET_SIMD_TUPLETYPE(addr_mode_def->details);
                /* For the following kind of SIMD instructions vector length
                   is explicitly set. */
                if(tuple_type == FCML_TT_FV) {
                    vector_length = FCML_DS_512;
                } else if (tuple_type == FCML_TT_T1S || tuple_type == FCML_TT_T1F) {
                    vector_length = FCML_DS_128;
                }

                if (!set_vector_length(
                        &(args->context->optimizer_ctx.vector_length),
                        vector_length)) {
                    FCML_TRACE("Vector length differs expected %d got %d.",
                            args->context->optimizer_ctx.vector_length, vector_length);
                    return FCML_CEH_GEC_INVALID_OPPERAND_SIZE;
                }
            }
        }
    }

    return FCML_CEH_GEC_NO_ERROR;
}

static ipp_desc ipp_op_decorators_acceptor_factory(ipp_factory_args *args,
        fcml_ceh_error *error) {
    ipp_desc descriptor = { 0 };
    descriptor.type = IPPT_VERIFIER;
    descriptor.args = NULL;
    descriptor.encoder = NULL;
    descriptor.acceptor = ipp_op_decorator_acceptor;
    return descriptor;
}

/********************************************/
/* Instruction parts factories definitions. */
/********************************************/

typedef struct ipp_factory_details {
    ipp_factory factory;
    fcml_string ipp_name;
    fcml_uint32_t flags;
} ipp_factory_details;

typedef enum ipp_choice_type {
    /* Only one instruction part processor from the given sequence may
     * be chosen for given addressing mode encoding. */
    FCML_IPCT_ONE,
    /* All instruction part processors from given sequence may be added
     * to given addressing mode encoding. */
    FCML_IPCT_ALL
} ipp_choice_type;

typedef struct ipp_factory_sequence {
    ipp_factory_details *details;
    ipp_choice_type choice_type;
    fcml_bool is_short_form_supported;
} ipp_factory_sequence;

#define FCML_IPP_FACTORY(fn, flags)     { fn, #fn "-" #flags, flags }

/* List of instruction part encoders for instruction opcode. */
static ipp_factory_details ipp_factories_opcode_for_IA[] = {
    FCML_IPP_FACTORY(ipp_AVX_opcode_encoder_factory, 0),
    FCML_IPP_FACTORY(ipp_reg_opcode_encoder_factory, 0),
    FCML_IPP_FACTORY(ipp_conditional_opcode_encoder_factory, 0),
    FCML_IPP_FACTORY(ipp_simple_opcode_encoder_factory,  0 ),
    { NULL, NULL, 0 }
};

/* List of instruction addressing mode acceptors. */
static ipp_factory_details ipp_factories_acceptors_IA[] = {
    FCML_IPP_FACTORY(ipp_addr_mode_acceptor_factory, 0),
    FCML_IPP_FACTORY(ipp_prefixes_acceptor_factory, 0),
    FCML_IPP_FACTORY(ipp_op_decorators_acceptor_factory, 0),
    { NULL, NULL, 0 }
};

/* List of instruction part encoders for instruction prefixes. */
static ipp_factory_details ipp_factories_prefixes_for_IA[] = {
    FCML_IPP_FACTORY(ipp_branch_hints_prefix_encoder_factory, 0),
    FCML_IPP_FACTORY(ipp_rep_prefix_encoder_factory, 0),
    FCML_IPP_FACTORY(ipp_repne_prefix_encoder_factory, 0),
    FCML_IPP_FACTORY(ipp_hle_prefixes_encoder_factory, 0),
    FCML_IPP_FACTORY(ipp_lock_prefix_encoder_factory, 0),
    FCML_IPP_FACTORY(ipp_segment_override_prefix_encoder_factory, 0),
    FCML_IPP_FACTORY(ipp_66_prefix_encoder_factory, 0),
    FCML_IPP_FACTORY(ipp_67_prefix_encoder_factory, 0),
    FCML_IPP_FACTORY(ipp_mandatory_prefixes_encoder_factory, 0),
    FCML_IPP_FACTORY(ipp_REX_prefix_encoder_factory, 0),
    FCML_IPP_FACTORY(ipp_VEX_XOP_prefix_encoder_factory, 0),
    FCML_IPP_FACTORY(ipp_EVEX_prefix_encoder_factory, 0),
    { NULL, NULL, 0 }
};

/* ModR/M byte encoder.*/
static ipp_factory_details ipp_factories_ModRM_for_IA[] = {
    FCML_IPP_FACTORY(ipp_ModRM_encoder_factory, 0),
    { NULL, NULL, 0 }
};

/* List of instruction part encoders for instruction operands.*/
static ipp_factory_details ipp_factories_operands_for_IA[] = {
    FCML_IPP_FACTORY(ipp_operand_wrapper_factory, 0),
    FCML_IPP_FACTORY(ipp_operand_wrapper_factory, 1),
    FCML_IPP_FACTORY(ipp_operand_wrapper_factory, 2),
    FCML_IPP_FACTORY(ipp_operand_wrapper_factory, 3),
    FCML_IPP_FACTORY(ipp_operand_wrapper_factory, 4),
    { NULL, NULL, 0 }
};

static ipp_factory_details ipp_factories_suffixes_for_IA[] = {
    FCML_IPP_FACTORY(ipp_suffix_encoder_factory, 0),
    { NULL, NULL, 0 }
};

static ipp_factory_sequence ipp_factory_sequences_for_IA[] = {
    { ipp_factories_acceptors_IA, FCML_IPCT_ALL, FCML_TRUE },
    { ipp_factories_prefixes_for_IA, FCML_IPCT_ALL, FCML_TRUE },
    { ipp_factories_opcode_for_IA, FCML_IPCT_ONE, FCML_TRUE },
    { ipp_factories_ModRM_for_IA, FCML_IPCT_ALL, FCML_FALSE },
    { ipp_factories_operands_for_IA, FCML_IPCT_ALL, FCML_FALSE },
    { ipp_factories_suffixes_for_IA, FCML_IPCT_ALL, FCML_FALSE },
    { NULL }
};

/* Instruction part processors chain builder dedicated for
 * Intel and AMD processors. */
static fcml_ceh_error ipp_chain_builder_for_IA(
        const fcml_st_def_addr_mode_desc *addr_mode_desc,
        const fcml_st_def_instruction_desc *instruction,
        ipp_chain_builder_out *out) {

    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
    int instruction_parts = 0;
    ipp_chain *chain = NULL;
    ipp_chain *current_chain = NULL;
    ipp_factory_sequence *sequence = &ipp_factory_sequences_for_IA[0];

    while (sequence->details) {
        int ipp_counter = 0;
        ipp_choice_type choice = sequence->choice_type;
        ipp_factory_details *factory = sequence->details;

        while (factory->factory) {
            ipp_factory_args factory_args = { 0 };
            factory_args.flags = factory->flags;
            factory_args.instruction = instruction;
            factory_args.addr_mode = addr_mode_desc;
            factory_args.hints = &(out->hints);

            ipp_desc desc = factory->factory(&factory_args, &error);
            if (!error && (desc.encoder || desc.acceptor)) {
                ipp_counter++;
                desc.ipp_name = factory->ipp_name;
                desc.is_short_form_supported = sequence->
                        is_short_form_supported;

                /* Check max number of the instruction part processors.*/
                if (ipp_counter > FCML_ASM_MAX_PART_PROCESSORS) {
                    FCML_TRACE_MSG("Max number of instructions part processors" \
                            " has been reached.");
                    free_ipp_desc(desc);
                    free_ipp_chain(chain);
                    return FCML_CEH_GEC_INTERNAL_ERROR;
                }

                /* Allocate chain element for new instruction part encoder.*/
                FCML_ENV_ALLOC_CLEAR(new_chain, ipp_chain);
                if (!new_chain) {
                    free_ipp_desc(desc);
                    free_ipp_chain(chain);
                    return FCML_CEH_GEC_OUT_OF_MEMORY;
                }

                if (!chain) {
                    chain = new_chain;
                    current_chain = new_chain;
                } else {
                    current_chain->next_processor = new_chain;
                    current_chain = new_chain;
                }

                current_chain->descriptor = desc;

                if (choice == FCML_IPCT_ONE) {
                    break;
                }
            }

            if (error) {
                free_ipp_chain(chain);
                return error;
            }
            factory++;
        }
        sequence++;
    }

    out->ipp_chain = chain;

    return error;
}

/* Chooses instruction part processor factory for given instruction type. */
static ipp_chain_builder choose_ipp_chain_builder(
        fcml_en_def_instruction_type type) {
    ipp_chain_builder builder = NULL;
    switch (type) {
    case FCML_EN_IT_IA:
        builder = ipp_chain_builder_for_IA;
        break;
    }
    return builder;
}

/* Default data size calculator. */

typedef struct data_size_calc_args {
    fcml_int reg_index;
} data_size_calc_args;

static fcml_usize reg_based_memory_data_size_calculator(
        const fcml_st_instruction *instruction, fcml_ptr args) {
    fcml_usize data = FCML_DS_UNDEF;
    data_size_calc_args *dsc_args = (data_size_calc_args*) args;
    if (instruction->operands_count > dsc_args->reg_index) {
        const fcml_st_operand *operand =
                &(instruction->operands[dsc_args->reg_index]);
        if (operand->type == FCML_OT_REGISTER) {
            return operand->reg.size;
        }
    }
    return data;
}

static fcml_ceh_error prepare_mem_data_size_calculator(
        const fcml_st_def_addr_mode_desc *addr_mode_desc,
        addr_mode_desc_details *details) {

    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
    fcml_bool mem_access = FCML_FALSE;
    fcml_int reg_index = -1;

    /* Just in case.*/
    details->ds_calculator = NULL;
    details->ds_calculator_args = NULL;

    fcml_int i;
    for (i = 0; i < FCML_OPERANDS_COUNT; i++) {
        fcml_operand_desc operand_desc = addr_mode_desc->operands[i];
        fcml_uint64_t addr_mode = FCML_GET_ADDR_MODE(operand_desc);
        if (addr_mode == FCML_NA) {
            break;
        }
        if (FCMP_DEF_IS_ADDR_MODE(addr_mode, FCML_OP_RM_BASE) &&
                (operand_desc & FCML_RMF_M)) {
            mem_access = FCML_TRUE;
        }
        if (FCMP_DEF_IS_ADDR_MODE(addr_mode, FCML_OP_R_BASE)
                || FCMP_DEF_IS_ADDR_MODE(addr_mode, FCML_OP_OPCODE_REG_BASE)
                || FCMP_DEF_IS_ADDR_MODE(addr_mode, FCML_OP_EXPLICIT_REG_BASE)
                || FCMP_DEF_IS_ADDR_MODE(addr_mode,
                        FCML_OP_VEX_VVVV_REG_BASE)) {
            reg_index = i;
        }
    }

    /* We check for memory access existence, because it makes no sense
     * to register custom memory operand size calculator if there
     * is no memory access there. */
    if (mem_access && reg_index != -1) {
        FCML_ENV_ALLOC_CLEAR(args, data_size_calc_args);
        if (!args) {
            return FCML_CEH_GEC_OUT_OF_MEMORY;
        }
        args->reg_index = reg_index;
        details->ds_calculator = &reg_based_memory_data_size_calculator;
        details->ds_calculator_args = args;
    }

    return error;
}

/* Calculates some flags basing on addressing modes descriptions
 * in order to get some performance benefits further.
 */
static fcml_ceh_error precalculate_addr_mode(
        const fcml_st_def_addr_mode_desc *addr_mode_desc,
        addr_mode_desc_details *details) {

    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
    fcml_uint32_t allowed_prefixes = addr_mode_desc->allowed_prefixes;
    fcml_uint32_t opcode_flags = addr_mode_desc->opcode_flags;

    /* Calculate OSA and ASA flags.*/

    fcml_flags osa_flags = FCML_EN_ASF_ANY;
    fcml_flags asa_flags = FCML_EN_ASF_ANY;

    if (!(addr_mode_desc->instruction_group & FCML_AMT_SIMD)) {
        if (FCML_DEF_PREFIX_W_1(allowed_prefixes)) {
            osa_flags |= FCML_EN_ASF_64;
            asa_flags |= (FCML_EN_ASF_32 | FCML_EN_ASF_64);
        }
        if (FCML_DEF_PREFIX_W_0(allowed_prefixes)) {
            osa_flags |= (FCML_EN_ASF_32 | FCML_EN_ASF_16);
        }
    }

    if (FCML_DEF_OPCODE_FLAGS_IS_EOSA_RESTRICTION(opcode_flags)) {
        fcml_flags osa_restriction_flags = FCML_EN_ASF_ANY;
        if (FCML_DEF_OPCODE_FLAGS_EOSA_16(opcode_flags)) {
            osa_restriction_flags |= FCML_EN_ASF_16;
        }
        if (FCML_DEF_OPCODE_FLAGS_EOSA_32(opcode_flags)) {
            osa_restriction_flags |= FCML_EN_ASF_32;
        }
        if (FCML_DEF_OPCODE_FLAGS_EOSA_64(opcode_flags)) {
            osa_restriction_flags |= FCML_EN_ASF_64;
        }
        osa_flags = (osa_flags == FCML_EN_ASF_ANY) ?
                        osa_restriction_flags :
                        osa_flags & osa_restriction_flags;
    }

    if (FCML_DEF_OPCODE_FLAGS_IS_EASA_RESTRICTION(opcode_flags)) {
        fcml_flags asa_restriction_flags = FCML_EN_ASF_ANY;
        if (FCML_DEF_OPCODE_FLAGS_EASA_16(opcode_flags)) {
            asa_restriction_flags |= FCML_EN_ASF_16;
        }
        if (FCML_DEF_OPCODE_FLAGS_EASA_32(opcode_flags)) {
            asa_restriction_flags |= FCML_EN_ASF_32;
        }
        if (FCML_DEF_OPCODE_FLAGS_EASA_64(opcode_flags)) {
            asa_restriction_flags |= FCML_EN_ASF_64;
        }
        asa_flags = (asa_flags == FCML_EN_ASF_ANY) ?
                        asa_restriction_flags :
                        asa_flags & asa_restriction_flags;
    }

    /* Sets calculated values in details.*/
    details->allowed_asa = asa_flags;
    details->allowed_osa = osa_flags;

    return error;
}

static void free_addr_mode_encoding(
        fcml_st_dialect_context_int *dialect_context,
        addr_mode_encoding *addr_mode) {
    /* Processor chains and calculator arguments are shared for clones
     * so do not free them. */
    if (addr_mode) {
        if (!addr_mode->is_cloned) {
            if (addr_mode->ipp_chain) {
                free_ipp_chain(addr_mode->ipp_chain);
            }
            /* Free arguments allocated for memory data size
             * calculator if there are any. */
            fcml_ptr args = addr_mode->addr_mode_details.ds_calculator_args;
            if (args) {
                fcml_fn_env_memory_free(args);
            }
        }
        if (addr_mode->mnemonic) {
            dialect_context->free_mnemonic(
                    (fcml_st_mp_mnemonic*)addr_mode->mnemonic);
        }
        fcml_fn_env_memory_free(addr_mode);
    }
}

/* A freeing handler dedicated for map holding instruction addressing modes containers. */
static void free_instruction_entry(fcml_ptr key, fcml_ptr value,
        fcml_ptr args) {
    free_instruction_addr_modes((fcml_st_instruction_addr_modes*) value,
            (fcml_st_dialect_context_int*) args);
}

/* Handler for hash map responsible for freeing addressing modes. */
static void free_addr_mode_item_handler(fcml_ptr item_value, fcml_ptr args) {
    addr_mode_encoding *addr_mode =
            (addr_mode_encoding*) item_value;
    fcml_st_dialect_context_int *dialect_context =
                (fcml_st_dialect_context_int*) args;
    free_addr_mode_encoding(dialect_context, addr_mode);
}

static fcml_fp_instruction_encoder choose_instruction_encoder(
        fcml_en_def_instruction_type instruction_type) {
    fcml_fp_instruction_encoder encoder = NULL;
    switch (instruction_type) {
    case FCML_EN_IT_IA:
        encoder = instruction_encoder_IA;
        break;
    }
    return encoder;
}

/* Frees instruction addressing modes container and all addressing modes stored there. */
static void free_instruction_addr_modes(
        fcml_st_instruction_addr_modes *addr_modes,
        fcml_st_dialect_context_int *dialect_context) {
    if (addr_modes) {
        if (addr_modes->addr_modes_encodings) {
            fcml_fn_coll_list_free(addr_modes->addr_modes_encodings,
                    free_addr_mode_item_handler, dialect_context);
        }
        fcml_fn_env_memory_free(addr_modes);
    }
}

/* Allocates container for addressing modes related to given mnemonic. */
static fcml_ceh_error alloc_instruction_addr_modes(
        const fcml_string mnemonic,
        const fcml_st_def_instruction_desc *instruction,
        fcml_st_instruction_addr_modes **out_addr_modes) {
    FCML_ENV_ALLOC_CLEAR(addr_modes, fcml_st_instruction_addr_modes);
    if (addr_modes) {
        /* Allocate list for addressing modes. */
        addr_modes->addr_modes_encodings = fcml_fn_coll_list_alloc();
        if (addr_modes->addr_modes_encodings) {
            /* Do not care about freeing this piece of memory.
             * Procedure responsible for freeing addressing mode is
             * responsible for it. */
            addr_modes->mnemonic = mnemonic;
            addr_modes->encoder = choose_instruction_encoder(
                    instruction->instruction_type);
            *out_addr_modes = addr_modes;
            return FCML_CEH_GEC_NO_ERROR;
        } else {
            fcml_fn_env_memory_free(addr_modes);
            return FCML_CEH_GEC_OUT_OF_MEMORY;
        }
    } else {
        /* Out of memory.*/
        return FCML_CEH_GEC_OUT_OF_MEMORY;
    }
}

/* Prepares addressing modes encoders for all mnemonics associated with given instruction. */
static fcml_ceh_error build_addr_modes_encodings_for_mnemonics(
        init_context *init_context,
        const fcml_st_def_instruction_desc *instruction,
        const fcml_st_def_addr_mode_desc *addr_mode_desc,
        addr_mode_encoding *addr_mode) {

    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

    fcml_st_condition *condition = NULL;
    if (addr_mode->addr_mode_details.is_conditional) {
        condition = &(addr_mode->addr_mode_details.condition);
    }

    /* Space for mnemonics.*/
    fcml_st_mp_mnemonic *mnemonics[FCML_ASM_DIALECT_MAX_MNEMONIC_COUNT];

    /* Instruction can be registered for more than one mnemonic.*/
    int mnemonic_count = 0;

    error = init_context->dialect_context->get_mnemonic(
            (fcml_st_dialect*) init_context->dialect_context, instruction,
            addr_mode_desc, condition, mnemonics, &mnemonic_count);
    if (error) {
        return error;
    }

    /* Prepare addressing mode encoders for every mnemonic. */
    int i;
    for (i = 0; i < mnemonic_count && !error; i++) {

        fcml_st_instruction_addr_modes *addr_modes =
                (fcml_st_instruction_addr_modes*) fcml_fn_coll_map_get(
                        init_context->inst_map, mnemonics[i]->mnemonic);
        if (!addr_modes) {
            /* Allocates new instruction addressing modes container for
             * the new mnemonic. */
            error = alloc_instruction_addr_modes(mnemonics[i]->mnemonic,
                    instruction, &addr_modes);
            if (error) {
                return error;
            }
            /* Puts prepared structure under mnemonic key.*/
            fcml_int map_error;
            fcml_fn_coll_map_put(init_context->inst_map,
                   mnemonics[i]->mnemonic, addr_modes, &map_error);
            if (map_error) {
                free_instruction_addr_modes(addr_modes, init_context->dialect_context);
                error = fcml_fn_utils_conv_map_error(map_error);
            }
        }

        if (!error) {
            fcml_bool is_cloned = (i > 0);
            addr_mode_encoding *encoding_for_mnemonic = addr_mode;

            if (is_cloned) {
                /* Clone encoding details for secondary mnemonics.*/
                FCML_ENV_ALLOC_CLEAR(encoding_clone, addr_mode_encoding);
                if (encoding_clone) {
                    *encoding_clone = *encoding_for_mnemonic;
                    encoding_clone->is_cloned = FCML_TRUE;
                    encoding_for_mnemonic = encoding_clone;
                } else {
                    error = FCML_CEH_GEC_OUT_OF_MEMORY;
                }
            }

            if (!error) {
                /* Every addressing mode has its own mnemonic configuration,
                 * it doesn't matter if it is cloned addressing mode or not
                 * it is responsible for deallocating it.
                 */
                encoding_for_mnemonic->mnemonic = mnemonics[i];
                if (!fcml_fn_coll_list_add_back(
                        addr_modes->addr_modes_encodings,
                        encoding_for_mnemonic)) {
                    /* Free holder allocated earlier.*/
                    if (is_cloned) {
                        fcml_fn_env_memory_free(encoding_for_mnemonic);
                    }
                    error = FCML_CEH_GEC_OUT_OF_MEMORY;
                }
            }
        }

        if (error) {
            /* In case of error free all mnemonics which haven't been
             * added to the addressing mode list.
             */
            for (; i < mnemonic_count; i++) {
                fcml_fn_asm_dialect_free_mnemonic(mnemonics[i]);
            }
        }
    }

    return error;
}

/* Returns a number of instruction parts needed to encode instruction using
 * given instruction part processors chain. Only encoders need instruction
 * parts as they generate real instruction bytes. */
static int inst_parts_for_chain(ipp_chain *chain) {
    int parts = 0;
    while(chain) {
        if (chain->descriptor.type == IPPT_ENCODER) {
            parts++;
        }
        chain = chain->next_processor;
    }
    return parts;
}

static fcml_ceh_error generic_addr_mode_encoding_builder(
        init_context *init_context,
        const fcml_st_def_instruction_desc *instruction,
        const fcml_st_def_addr_mode_desc *addr_mode_desc,
        addr_mode_encoding_enricher enricher, fcml_ptr enricher_args) {

    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

    FCML_ENV_ALLOC_CLEAR(addr_mode, addr_mode_encoding);

    if (!addr_mode) {
        return FCML_CEH_GEC_OUT_OF_MEMORY;
    }

    /* Copy instruction hints from instruction form definition. */
    addr_mode->hints = addr_mode_desc->instruction_hints;
    addr_mode->addr_mode_desc = addr_mode_desc;
    addr_mode->instruction = instruction->instruction;

    /* Prepare addressing mode details.*/
    addr_mode_desc_details *details = &(addr_mode->addr_mode_details);

    error = precalculate_addr_mode(addr_mode_desc, details);
    if (error) {
        free_addr_mode_encoding(init_context->dialect_context, addr_mode);
        return error;
    }

    error = prepare_mem_data_size_calculator(addr_mode_desc, details);
    if (error) {
        free_addr_mode_encoding(init_context->dialect_context, addr_mode);
        return error;
    }

    if (enricher) {
        enricher(addr_mode, enricher_args);
    }

    ipp_chain_builder builder = choose_ipp_chain_builder(
            instruction->instruction_type);

    /* Populates addressing mode encoding with instruction
     * part processors and instruction level hints. */
    ipp_chain_builder_out out = {NULL};
    error = builder(addr_mode_desc, instruction, &out);
    if (error) {
        free_addr_mode_encoding(init_context->dialect_context, addr_mode);
        return error;
    }

    addr_mode->ipp_chain = out.ipp_chain;
    addr_mode->instruction_parts = inst_parts_for_chain(out.ipp_chain);
    addr_mode->hints = out.hints | addr_mode_desc->instruction_hints;

    /* The addressing mode encoder built above is a generic one for the
     * processed instruction, bet be have to provide specific parameterized
     * encoders for every mnemonic which represents given instruction.
     * The function below is responsible for that. */
    error = build_addr_modes_encodings_for_mnemonics(init_context,
            instruction, addr_mode_desc, addr_mode);
    if (error) {
        free_addr_mode_encoding(init_context->dialect_context, addr_mode);
        return error;
    }

    return error;
}

typedef struct cond_enricher_args {
    /* Instruction condition code. */
    fcml_int condition_num;
} cond_enricher_args;

/* Enriches addressing mode encoder by adding details about
 * instruction condition. */
static void conditional_addr_more_encoding_enricher(
        addr_mode_encoding *addr_mode, fcml_ptr args) {
    cond_enricher_args *enricher_args = (cond_enricher_args*) args;
    addr_mode_desc_details *details = &(addr_mode->addr_mode_details);
    details->is_conditional = FCML_TRUE;
    details->condition.is_negation = (enricher_args->condition_num % 2 == 1);
    details->condition.condition_type = (fcml_en_condition_type)
            (enricher_args->condition_num / 2);
}

/* Builder for conditional instructions (tttn) */
static fcml_ceh_error conditional_addr_mode_encoding_builder(
        init_context *init_context,
        const fcml_st_def_instruction_desc *instruction,
        const fcml_st_def_addr_mode_desc *addr_mode_desc) {
    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
    int i;
    for (i = 0; i < FCML_NUMBER_OF_CONDITIONS * 2 && !error; i++) {
        cond_enricher_args enricher_args = { 0 };
        enricher_args.condition_num = i;
        error = generic_addr_mode_encoding_builder(
                init_context, instruction, addr_mode_desc,
                &conditional_addr_more_encoding_enricher,
                &enricher_args);
    }
    return error;
}

static fcml_ceh_error default_addr_mode_encoding_builder(
        init_context *init_context,
        const fcml_st_def_instruction_desc *instruction,
        const fcml_st_def_addr_mode_desc *addr_mode) {
    return generic_addr_mode_encoding_builder(init_context, instruction,
            addr_mode, NULL, NULL);
}

static addr_mode_encoding_builder encoding_builder_factory(
        fcml_st_def_addr_mode_desc *addr_mode) {
    if (FCML_DEF_OPCODE_FLAGS_OPCODE_FIELD_TTTN(addr_mode->opcode_flags)) {
        return &conditional_addr_mode_encoding_builder;
    }
    return &default_addr_mode_encoding_builder;
}

/* All the generated addressing modes encodings are registered in
 * instruction map see: init_context. */
static fcml_ceh_error build_instruction_addr_modes_encodings(
        init_context *init_context,
        fcml_st_def_instruction_desc *instruction) {
    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
    int i;
    for (i = 0; i < instruction->opcode_desc_count && !error; i++) {
        fcml_st_def_addr_mode_desc *addr_mode = &(instruction->addr_modes[i]);
        /* Prepare encoders for given addressing mode.*/
        addr_mode_encoding_builder builder =
                encoding_builder_factory(addr_mode);
        error = builder(init_context, instruction, addr_mode);
    }
    return error;
}

fcml_ceh_error fcml_fn_init_instructions_addr_modes(
        fcml_st_dialect_context_int *dialect_context,
        fcml_coll_map *inst_map) {

    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
    fcml_coll_map instructions_map;
    /* Allocate map for all instructions.*/
    fcml_st_coll_map_descriptor inst_map_desc =
            fcml_coll_map_descriptor_string;

    inst_map_desc.entry_free_function = free_instruction_entry;
    inst_map_desc.entry_free_args = dialect_context;

    fcml_int map_error;
    instructions_map = fcml_fn_coll_map_alloc(&inst_map_desc, 64, &map_error);
    if (map_error) {
        return fcml_fn_utils_conv_map_error(map_error);
    }

    init_context init_context;
    init_context.dialect_context = dialect_context;
    init_context.inst_map = instructions_map;

    int i = 0;
    fcml_st_def_instruction_desc *inst = &(fcml_ext_instructions_def[i++]);
    while (inst->instruction != F_UNKNOWN && !error) {
        /* Adds all addressing modes  */
        error = build_instruction_addr_modes_encodings(&init_context, inst);
        inst = &(fcml_ext_instructions_def[i++]);
    }

    if (error) {
        /* Free everything that have been properly allocated. */
        fcml_fn_coll_map_free(instructions_map);
        instructions_map = NULL;
    }

    *inst_map = instructions_map;

    return error;
}

void fcml_fn_free_instructions_addr_modes(fcml_coll_map instructions_map) {
    if (instructions_map) {
        fcml_fn_coll_map_free(instructions_map);
    }
}

fcml_ceh_error fcml_fn_get_instruction_addr_modes(
        fcml_coll_map instructions_map, fcml_string mnemonic,
        fcml_st_instruction_addr_modes **addr_modes) {

    if (!instructions_map) {
        return FCML_CEH_GEC_NOT_INITIALIZED;
    }

    *addr_modes = (fcml_st_instruction_addr_modes*)
            fcml_fn_coll_map_get(instructions_map, mnemonic);
    if (!*addr_modes) {
        return FCML_CEH_GEC_UNKNOWN_MNEMONIC;
    }

    return FCML_CEH_GEC_NO_ERROR;
}

static void break_optimization(encoding_context *context) {
    context->optimizer_processing_details.break_optimization = FCML_TRUE;
}

static inline fcml_bool is_short_form(const fcml_st_instruction *instruction,
        const fcml_st_mp_mnemonic *mnemonic) {
    return mnemonic->is_shortcut && instruction->operands_count == 0;
}

