/**
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

#include <fcml_assembler.h>
#include <fcml_parser.h>
#include <fcml_gas_dialect.h>
#include <fcml_intel_dialect.h>

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

void print_error_msg(fcml_st_ceh_error_container *errors) {
    fcml_st_ceh_error_info *error = errors->errors;
    while (error) {
        // Print error message.
        if (error->level == FCML_EN_CEH_EL_WARN) {
            printf("WARN: ");
        } else if (error->level == FCML_EN_CEH_EL_ERROR) {
            printf("ERROR: ");
        }
        printf("%3d: %s\n", error->code, error->message);
        error = error->next_error;
    }
}

int main(int argc, char **argv) {

    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

    /* Interpret arguments. */

    if (argc <= 1) {
        printf("Bad arguments.\n");
        exit(1);
    }

    fcml_st_assembler_context context = { 0 };
    context.configuration.enable_error_messages = FCML_TRUE;

    fcml_bool gas_dialect = 0;

    fcml_ip ip = 0;

    fcml_string instruction = NULL;

    int i;
    for (i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-m16") == 0) {
            context.entry_point.op_mode = FCML_OM_16_BIT;
        } else if (strcmp(argv[i], "-m32") == 0) {
            context.entry_point.op_mode = FCML_OM_32_BIT;
        } else if (strcmp(argv[i], "-m64") == 0) {
            context.entry_point.op_mode = FCML_OM_64_BIT;
        } else if (strcmp(argv[i], "-asa16") == 0) {
            context.entry_point.address_size_attribute = FCML_DS_16;
        } else if (strcmp(argv[i], "-asa32") == 0) {
            context.entry_point.address_size_attribute = FCML_DS_32;
        } else if (strcmp(argv[i], "-asa64") == 0) {
            context.entry_point.address_size_attribute = FCML_DS_64;
        } else if (strcmp(argv[i], "-osa16") == 0) {
            context.entry_point.operand_size_attribute = FCML_DS_16;
        } else if (strcmp(argv[i], "-osa32") == 0) {
            context.entry_point.operand_size_attribute = FCML_DS_32;
        } else if (strcmp(argv[i], "-osa64") == 0) {
            context.entry_point.operand_size_attribute = FCML_DS_64;
        } else if (strcmp(argv[i], "-ip") == 0) {
            if (++i < argc) {
                char *res;
                errno = 0;
                ip = strtoll(argv[i], &res, 16);
                if ((errno == ERANGE
                        && (ip == FCML_INT64_MAX || ip == FCML_INT64_MIN))
                        || (errno != 0 && ip == 0) || (argv[i] == res)) {
                    perror("Wrong instruction pointer.");
                    exit(EXIT_FAILURE);
                }
            } else {
                printf("IP not set.\n");
                exit(1);
            }
        } else if (strcmp(argv[i], "-abs") == 0) {
            context.configuration.choose_abs_encoding = FCML_TRUE;
        } else if (strcmp(argv[i], "-sib") == 0) {
            context.configuration.choose_sib_encoding = FCML_TRUE;
        } else if (strcmp(argv[i], "-rex") == 0) {
            context.configuration.force_rex_prefix = FCML_TRUE;
        } else if (strcmp(argv[i], "-3b") == 0) {
            context.configuration.force_three_byte_VEX = FCML_TRUE;
        } else if (strcmp(argv[i], "-gas") == 0) {
            gas_dialect = FCML_TRUE;
        } else if (strcmp(argv[i], "-all") == 0) {
            context.configuration.optimizer_flags = FCML_OPTF_ALL_FORMS;
        } else if (strcmp(argv[i], "--help") == 0) {
            printf(
                    "usage: fcml_asm [-abs] [-sib] [-rex] [-gas] [-asa<size>] [-osa<size>]\n"
                            "       <-m<size>> <-ip address> <instruction>\n\n"
                            "       -m16      16 bit addressing mode\n"
                            "       -m32      32 bit addressing mode\n"
                            "       -m64      64 bit addressing mode\n"
                            "       -asa16    16 bit address size attribute\n"
                            "       -asa32    32 bit address size attribute\n"
                            "       -asa64    63 bit address size attribute\n"
                            "       -osa16    16 bit operand size attribute\n"
                            "       -osa32    32 bit operand size attribute\n"
                            "       -osa64    64 bit operand size attribute\n"
                            "       -ip       Instruction pointer address (IP/EIP/RIP register)\n"
                            "       -abs      Choose absolute memory addressing if there is any choice\n"
                            "                 (Especially useful in 64 bit mode, see RIP addressing.)\n"
                            "       -sib      If instruction can be encoded using SIB byte do it\n"
                            "       -rex      Use REX prefix even if it is optional for assembled instruction\n"
                            "       -all      Return all possible forms of the instruction\n"
                            "       -gas      Use GNU assembler/AT&T dialect (Intel dialect is used by default)\n\n"
                            "example: fcml_asm -m32 -ip 0x4001000 \"add eax,1\"\n\n");
            exit(0);
        } else if (i + 1 == argc) {
            // Instruction mnemonic.
            instruction = argv[i];
        }
    }

    if (!instruction) {
        printf("Instruction mnemonic not found.\n");
        exit(EXIT_FAILURE);
    }

    context.entry_point.ip = ip;

    /* Initialize dialect to use with assembler/parser. */

    fcml_st_dialect *dialect;

    if (gas_dialect) {
        error = fcml_fn_dialect_init_gas( FCML_GAS_DIALECT_CF_DEFAULT,
                &dialect);
    } else {
        error = fcml_fn_dialect_init_intel( FCML_INTEL_DIALECT_CF_DEFAULT,
                &dialect);
    }

    if (error) {
        printf("Can not initialize a dialect, error: %d\n", error);
        exit(EXIT_FAILURE);
    }

    /* Initialize parser. */

    fcml_st_parser_context parser_context = { 0 };
    parser_context.dialect = dialect;
    parser_context.ip = ip;
    parser_context.symbol_table = NULL; /* We do not use symbols in case of one line assembler. */
    parser_context.configuration.ignore_undefined_symbols = FCML_FALSE;

    /* Parse instruction mnemonic. */

    fcml_st_parser_result parser_result;

    fcml_fn_parser_result_prepare(&parser_result);

    error = fcml_fn_parse(&parser_context, instruction, &parser_result);
    if (error) {
        fcml_fn_dialect_free(dialect);
        printf("Can not parse the instruction mnemonic, error: %d\n", error);
        print_error_msg(&(parser_result.errors));
        exit(EXIT_FAILURE);
    }

    /* Assemble parsed instruction. */

    fcml_st_assembler *assembler;

    error = fcml_fn_assembler_init(dialect, &assembler);
    if (error) {
        fcml_fn_parser_result_free(&parser_result);
        fcml_fn_dialect_free(dialect);
        printf("Can not initialize the assembler, error: %d\n", error);
        print_error_msg(&(parser_result.errors));
        exit(EXIT_FAILURE);
    }

    context.assembler = assembler;

    fcml_st_assembler_result asm_result;

    fcml_fn_assembler_result_prepare(&asm_result);

    error = fcml_fn_assemble(&context, parser_result.instruction, &asm_result);
    if (error) {
        fcml_fn_assembler_free(assembler);
        fcml_fn_parser_result_free(&parser_result);
        fcml_fn_dialect_free(dialect);
        printf("Can not assemble the instruction, error: %d\n", error);
        print_error_msg(&(parser_result.errors));
        exit(EXIT_FAILURE);
    }

    /* Print result. */

    printf("Number of the assembled instructions: %d\n",
            asm_result.number_of_instructions);

    fcml_st_assembled_instruction *assembled_instruction =
            asm_result.instructions;

    int chosen = 0;
    int index = 0;
    while (assembled_instruction) {
        int i;
        printf("Instruction: %d\n", ++index);
        printf(" Code: ");
        for (i = 0; i < assembled_instruction->code_length; i++) {
            printf("%02x", assembled_instruction->code[i]);
        }
        printf("\n Code length: %d\n", assembled_instruction->code_length);
        if (assembled_instruction == asm_result.chosen_instruction) {
            chosen = index;
        }
        assembled_instruction = assembled_instruction->next;
    }

    if (chosen) {
        printf("Best instruction chosen by the assembler: %d\n", chosen);
    }

    fcml_fn_assembler_result_free(&asm_result);

    fcml_fn_assembler_free(assembler);

    fcml_fn_parser_result_free(&parser_result);

    fcml_fn_dialect_free(dialect);

}

