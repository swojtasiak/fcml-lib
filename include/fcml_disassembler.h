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

/** @file fcml_disassembler.h
 * Structures and functions declarations related to FCML disassembler.
 * @copyright Copyright (C) 2010-2020 Slawomir Wojtasiak. All rights reserved.
 * This project is released under the GNU Lesser General Public License.
 */

#ifndef FCML_DISASSEMBLER_H_
#define FCML_DISASSEMBLER_H_

#include "fcml_lib_export.h"

#include "fcml_instructions.h"
#include "fcml_types.h"
#include "fcml_errors.h"
#include "fcml_common.h"
#include "fcml_dialect.h"

#ifdef __cplusplus
extern "C" {
#endif

/** Maximal number of instruction prefixes. */
#define FCML_DASM_PREFIXES_COUNT	12

/** First group of conditional suffixes (See FCML manual). */
#define FCML_DASM_CONDITIONAL_GROUP_1	0x00
/** Second group of conditional suffixes (See FCML manual). */
#define FCML_DASM_CONDITIONAL_GROUP_2	0x01

/** This structure and type declaration represents an abstract disassembler. */
typedef struct fcml_st_disassembler fcml_st_disassembler;

/** Disassembler configuration. */
typedef struct fcml_st_disassembler_conf {
    /** Set to true in order to make disassembler to increment IP address by
     * length of the disassembled instruction. */
    fcml_bool increment_ip;
    /** True if optional error and warning messages should be collected
     * during processing. */
    fcml_bool enable_error_messages;
    /** True if suffixes for carry flag has to be used by disassembler.*/
    fcml_bool carry_flag_conditional_suffix;
    /** There are two groups of suffixes for conditional instructions, you
     * can choose which one should be used. */
    fcml_uint8_t conditional_group;
    /** Set to true in order to use short forms.
     * For instance 'cmpsb' will be used instead of
     * 'cmps byte ptr [si],byte ptr [di]'
     */
    fcml_bool short_forms;
    /** True if displacement should be sign extended to effective
     * address size; otherwise false. */
    fcml_bool extend_disp_to_asa;
    /** If set to true assembler will return FCML_CEH_GEC_UNKNOWN_INSTRUCTION
     * error code if instruction is not known.
     */
    fcml_bool fail_if_unknown_instruction;
} fcml_st_disassembler_conf;

/** Disassembler context. */
typedef struct fcml_st_disassembler_context {
    /** Disassembler used to decode instructions. */
    fcml_st_disassembler *disassembler;
    /** Disassembler configuration. */
    fcml_st_disassembler_conf configuration;
    /** Instruction entry point configuration. */
    fcml_st_entry_point entry_point;
    /** Pointer to the encoded instruction. */
    fcml_ptr code;
    /** Size of the code in the buffer above. */
    fcml_usize code_length;
} fcml_st_disassembler_context;

/* Prefixes */

/** Available types of instruction prefixes. For more information see
 * Intel/AMD Architecture Manual. */
typedef enum fcml_en_prefix_types {
    FCML_PT_GROUP_UNKNOWN = 0,
    FCML_PT_GROUP_1 = 1,
    FCML_PT_GROUP_2,
    FCML_PT_GROUP_3,
    FCML_PT_GROUP_4,
    FCML_PT_REX,
    FCML_PT_VEX,
    FCML_PT_XOP,
    FCML_PT_EVEX
} fcml_en_prefix_types;

/** Describes one decoded prefix. */
typedef struct fcml_st_instruction_prefix {
    /** Prefix itself as raw byte. */
    fcml_uint8_t prefix;
    /** Type of the prefix. */
    fcml_en_prefix_types prefix_type;
    /** FCML_TRUE if prefix is treated as mandatory one. */
    fcml_bool mandatory_prefix;
    /** Place for additional bytes of VEX/EVEX/XOP prefix.
     * since 1.2.0
     */
    fcml_uint8_t avx_bytes[3];
} fcml_st_instruction_prefix;

/**
 * Contains some additional information about all decoded
 * instruction prefixes.
 */
typedef struct fcml_st_prefixes_details {
    /** Array with decoded prefixes. */
    fcml_st_instruction_prefix prefixes[FCML_DASM_PREFIXES_COUNT];
    /** Number of decoded prefixes. */
    fcml_int prefixes_count;
    /** Number of bytes used by all decoded prefixes. */
    fcml_int prefixes_bytes_count;
    /** FCML_TRUE if branch prefix exists. */
    fcml_bool is_branch;
    /** FCML_TRUE if nobranch prefix exists. */
    fcml_bool is_nobranch;
    /** FCML_TRUE if lock explicit prefix exists. */
    fcml_bool is_lock;
    /** FCML_TRUE if rep explicit prefix exists. */
    fcml_bool is_rep;
    /** FCML_TRUE if repne explicit prefix exists. */
    fcml_bool is_repne;
    /** FCML_TRUE if xrelease explicit prefix exists. */
    fcml_bool is_xrelease;
    /** FCML_TRUE if xacquire explicit prefix exists. */
    fcml_bool is_xacquire;
    /** FCML_TRUE if VEX prefix exists. */
    fcml_bool is_vex;
    /** FCML TRUE if EVEX prefix exists. */
    fcml_bool is_evex;
    /** FCML_TRUE if XOP prefix exists. */
    fcml_bool is_xop;
    /** True if it is an AVX instruction (VEX/XOP/EVEX). */
    fcml_bool is_avx;
    /** FCML_TRUE if REX prefix exists. */
    fcml_bool is_rex;
    /** First byte of AVX prefix. */
    fcml_uint8_t avx_first_byte;
    /** R field of REX,XOP or VEX prefix. */
    fcml_uint8_t R;
    /** EVEX R’ High-16 register specifier modifier. */
    fcml_uint8_t R_prim;
    /** X field of REX,XOP or VEX prefix. */
    fcml_uint8_t X;
    /** B field of REX,XOP or VEX prefix. */
    fcml_uint8_t B;
    /** b field of EVEX prefix. */
    fcml_uint8_t b;
    /** W field of REX,XOP or VEX/EVEX prefix. */
    fcml_uint8_t W;
    /** L field of XOP or VEX prefix. */
    fcml_uint8_t L;
    /** L’ field of EVEX prefix. */
    fcml_uint8_t L_prim;
    /** m-mmmm field of XOP or VEX prefix. */
    fcml_uint8_t mmmm;
    /** vvvv field of XOP or VEX prefix. */
    fcml_uint8_t vvvv;
    /** pp field of XOP or VEX/EVEX prefix. */
    fcml_uint8_t pp;
    /** z field of EVEX prefix */
    fcml_uint8_t z;
    /** V’ field of EVEX prefix. */
    fcml_uint8_t V_prim;
    /** Embedded opmask register specifier. */
    fcml_uint8_t aaa;
} fcml_st_prefixes_details;

/** Some additional disassembler specific information about decoded operands. */
typedef struct fcml_st_operand_details {
    /** Instruction operand access mode READ, WRITE or both. */
    fcml_en_access_mode access_mode;
} fcml_st_operand_details;

/**
 * Displacement in raw form.
 */
typedef struct fcml_st_raw_displacement {
    /** Displacement as encoded in disp8/disp16/disp32/disp8*N. */
    fcml_st_integer displacement;
    /** Scaling factor N in EVEX specific compressed disp8*N. */
    fcml_nuint32_t N;
} fcml_st_raw_displacement;

/** Some basic information about decoded ModR/M and SIB bytes. */
typedef struct fcml_st_decoded_modrm_details {
    /** ModR/M byte if exists.*/
    fcml_uint8_t modrm;
    /** SIB byte if exists.*/
    fcml_nuint8_t sib;
    /** True if RIP encoding is used by decoded instruction. This flag is
     * used only in 64 bit mode. */
    fcml_bool is_rip;
    /** True if ModR/M exists. */
    fcml_bool is_modrm;
    /** Raw displacement */
    fcml_st_raw_displacement displacement;
} fcml_st_decoded_modrm_details;

/** Additional instruction details provided by disassembler. */
typedef struct fcml_st_instruction_details {
    /** True if this is a shortcut.
     * A good example of such instruction is 'cmpsb' as opposed to
     * 'cmps byte ptr [si],byte ptr [di]'. It is very important to take this
     * information into consideration when instruction models are analyzed
     * because there is no operands in the GIM for shortcuts.
     */
    fcml_bool is_shortcut;
    /** True if given instruction is a short form of pseudo-ops instructions.
     * See 'vcmpunordsd' for instance. */
    fcml_bool is_pseudo_op;
    /** Code of the disassembled instruction. */
    fcml_uint8_t instruction_code[FCML_INSTRUCTION_SIZE];
    /** Instruction size in bytes. */
    fcml_usize instruction_size;
    /** Some additional information about decoded instruction prefixes. */
    fcml_st_prefixes_details prefixes_details;
    /** All disassembler specific information about operands going there. */
    fcml_st_operand_details operand_details[FCML_OPERANDS_COUNT];
    /** Details about decoded ModR/M and SIB bytes. */
    fcml_st_decoded_modrm_details modrm_details;
    /** Opcode field 's'.
     * This is set only for informational purpose only and you should not
     * use it for any critical functionality.
     */
    fcml_bool opcode_field_s_bit;
    /** Opcode field 'w'.
     * This is set only for informational purpose only and you should not
     * use it for any critical functionality.
     */
    fcml_bool opcode_field_w_bit;
    /** Instruction code/number. @see fcml_instructions.h header file. */
    fcml_en_instruction instruction;
    /** Pseudo operation code. */
    fcml_en_pseudo_operations pseudo_op;
    /** Code of the instruction form/addressing mode of the instruction
     *  above. */
    fcml_uint16_t addr_mode;
    /** Instruction group. */
    fcml_uint64_t instruction_group;
    /** avx-512 tuple type */
    fcml_uint8_t tuple_type;
} fcml_st_instruction_details;

/** Reusable disassembler result holder. */
typedef struct fcml_st_disassembler_result {
    /** All errors and warnings messages going here. */
    fcml_st_ceh_error_container errors;
    /** Additional disassembler specific information about decoded
     *  instruction. */
    fcml_st_instruction_details instruction_details;
    /** Decoded instruction in its generic form.*/
    fcml_st_instruction instruction;
} fcml_st_disassembler_result;

/**
 * Initializes disassembler instance.
 * Initializes disassembler instance for given dialect. Disassembler
 * initialized in such a way is dialect dependent and generates generic
 * instruction models compliant to the syntax supported by the dialect
 * (Intel, AT&T). Every disassembler instance has to be freed using
 * fcml_fn_disassembler_free() function as soon as it is not needed anymore.
 *
 * @param dialect Dialect for newly created disassembler.
 * @param[out] disassembler Initialized disassembler instance.
 * @return Error code or FCML_CEH_GEC_NO_ERROR.
 * @see fcml_fn_disassembler_free
 */
LIB_EXPORT fcml_ceh_error LIB_CALL fcml_fn_disassembler_init(
        const fcml_st_dialect *dialect, fcml_st_disassembler **disassembler);

/**
 * Disassembles one instruction from provided code buffer.
 * Disassembles the first instruction available in the provided code buffer
 * using disassembler instance, configuration and entry point accessible through
 * the disassembler context. Disassembled instruction model as well as potential
 * errors are returned in reusable result holder given in the second parameter.
 * Result holder has to be allocated by the user and appropriately prepared
 * using fcml_fn_disassembler_result_prepare() function. As long as the
 * instruction context and the result holder are not shared across multiple
 * function calls disassembling process is thread safe.
 *
 * @param context Disassembler context.
 * @param result Appropriately prepared result holder.
 * @return Error code or FCML_CEH_GEC_NO_ERROR.
 * @see fcml_fn_disassembler_result_free
 */
LIB_EXPORT fcml_ceh_error LIB_CALL fcml_fn_disassemble(
        fcml_st_disassembler_context *context,
        fcml_st_disassembler_result *result);

/**
 * Prepares reusable result holder for disassembler.
 * Every instance of fcml_st_disassembler_result structure is reusable from
 * the disassembler's point of view, so it has to be prepared in the right
 * way in order to allow disassembler to reuse it correctly. It is up to the
 * library user to allocate space for the holder itself. This function is only
 * responsible for cleaning the structure correctly and preparing it for first
 * disassembling process. Notice that disassembler has to clean the result
 * holder at the beginning so you can not pass an uninitialized memory
 * block because it can even cause a crash due to illegal memory access.
 *
 * @param result Result holder instance to be prepared.
 * @see fcml_fn_disassembler_result_free
 */
LIB_EXPORT void LIB_CALL fcml_fn_disassembler_result_prepare(
        fcml_st_disassembler_result *result);

/**
 * Cleans result holder.
 * Frees all memory blocks allocated by the disassembler and held inside
 * the result holder (Instructions, errors etc.). Notice that result holder
 * itself is not freed and can be even safety reused after calling this
 * function. In fact this function is also called internally by assembler in
 * order to clean result holder before reusing it.
 *
 * @param result Result holder to clean.
 */
LIB_EXPORT void LIB_CALL fcml_fn_disassembler_result_free(
        fcml_st_disassembler_result *result);

/**
 * Frees disassembler instance.
 * Every disassembler instance manages some resources internally and as
 * such it has to be deallocated as soon as it is not needed anymore.
 * @param disassembler Disassembler to be freed.
 */
LIB_EXPORT void LIB_CALL fcml_fn_disassembler_free(
        fcml_st_disassembler *disassembler);

#ifdef __cplusplus
}
#endif

#endif /* FCML_DISASSEMBLER_H_ */
