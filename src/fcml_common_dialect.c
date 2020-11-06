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

#include "fcml_common_dialect.h"

#include <fcml_common.h>
#include <fcml_dialect.h>
#include <fcml_types.h>

#include "fcml_ceh.h"
#include "fcml_dialect_int.h"
#include "fcml_env_int.h"

#define FCML_CMN_DIALECT_CND_GROUPS 3

static fcml_string conditional_suffixes[3][16] = {
    {
            FCML_TEXT("o"), FCML_TEXT("no"),  FCML_TEXT("b"),
            FCML_TEXT("nb"), FCML_TEXT("e"), FCML_TEXT("ne"),
            FCML_TEXT("be"), FCML_TEXT("nbe"), FCML_TEXT("s"),
            FCML_TEXT("ns"), FCML_TEXT("p"),  FCML_TEXT("np"),
            FCML_TEXT("l"),   FCML_TEXT("nl"), FCML_TEXT("le"),
            FCML_TEXT("nle")
    },
    {
            NULL, NULL, FCML_TEXT("nae"), FCML_TEXT("ae"),
            FCML_TEXT("z"), FCML_TEXT("nz"), FCML_TEXT("na"),
            FCML_TEXT("a"),   NULL, NULL, FCML_TEXT("pe"),
            FCML_TEXT("po"), FCML_TEXT("nge"), FCML_TEXT("ge"),
            FCML_TEXT("ng"), FCML_TEXT("g")
    },
    {
            NULL, NULL, FCML_TEXT("c"), FCML_TEXT("nc"), NULL, NULL, NULL, NULL,
            NULL, NULL, NULL, NULL, NULL,  NULL, NULL, NULL
    }
};

static fcml_string conditional_suffixes_render[2][16] = {
	{
	        FCML_TEXT("o"), FCML_TEXT("no"), FCML_TEXT("b"), FCML_TEXT("nb"),
	        FCML_TEXT("e"), FCML_TEXT("ne"), FCML_TEXT("be"), FCML_TEXT("nbe"),
	        FCML_TEXT("s"), FCML_TEXT("ns"), FCML_TEXT("p"), FCML_TEXT("np"),
	        FCML_TEXT("l"), FCML_TEXT("nl"), FCML_TEXT("le"), FCML_TEXT("nle")
	},
	{
	        FCML_TEXT("o"), FCML_TEXT("no"), FCML_TEXT("nae"), FCML_TEXT("ae"),
	        FCML_TEXT("z"), FCML_TEXT("nz"), FCML_TEXT("na"), FCML_TEXT("a"),
	        FCML_TEXT("s"), FCML_TEXT("ns"), FCML_TEXT("pe"), FCML_TEXT("po"),
	        FCML_TEXT("nge"), FCML_TEXT("ge"), FCML_TEXT("ng"), FCML_TEXT("g")
	}
};

static fcml_string reg_symbol_table[7][16] = {
	{
	        "<none>", "<none>", "<none>", "<none>", "<none>", "<none>", "<none>",
	        "<none>", "<none>", "<none>", "<none>", "<none>", "<none>",
	        "<none>", "<none>", "<none>"
	},
	{
	        "<unknown GPR>", "<unknown GPR>", "<unknown GPR>", "<unknown GPR>",
	        "<unknown GPR>", "<unknown GPR>", "<unknown GPR>", "<unknown GPR>",
	        "<unknown GPR>", "<unknown GPR>", "<unknown GPR>", "<unknown GPR>",
	        "<unknown GPR>", "<unknown GPR>", "<unknown GPR>", "<unknown GPR>"
	},
	{
	        "<unknown SIMD>", "<unknown SIMD>", "<unknown SIMD>", "<unknown SIMD>",
	        "<unknown SIMD>", "<unknown SIMD>", "<unknown SIMD>", "<unknown SIMD>",
	        "<unknown SIMD>", "<unknown SIMD>", "<unknown SIMD>", "<unknown SIMD>",
	        "<unknown SIMD>", "<unknown SIMD>", "<unknown SIMD>", "<unknown SIMD>"
	},
	{
	        "st(0)", "st(1)", "st(2)", "st(3)", "st(4)", "st(5)", "st(6)", "st(7)",
	        "<unknown fpu>", "<unknown fpu>", "<unknown fpu>", "<unknown fpu>",
	        "<unknown fpu>", "<unknown fpu>", "<unknown fpu>", "<unknown fpu>"
	},
	{
	        "es", "cs", "ss", "ds", "fs", "gs", "<unknown SR>", "<unknown SR>",
	        "<unknown SR>", "<unknown SR>", "<unknown SR>", "<unknown SR>",
	        "<unknown SR>", "<unknown SR>", "<unknown SR>", "<unknown SR>"
	},
	{
	        "cr0", "<unknown CR>", "cr2", "cr3", "cr4", "<unknown CR>",
	        "<unknown CR>", "<unknown CR>", "cr8", "<unknown CR>",
	        "<unknown CR>", "<unknown CR>", "<unknown CR>", "<unknown CR>",
	        "<unknown CR>", "<unknown CR>"
	},
	{
	        "dr0", "dr1", "dr2", "dr3", "dr4", "dr5", "dr6", "dr7", "<unknown DR>",
	        "<unknown DR>", "<unknown DR>", "<unknown DR>", "<unknown DR>",
	        "<unknown DR>", "<unknown DR>", "<unknown DR>"
	}
};

static fcml_string reg_gpr_symbol_table[4][16] = {
	{
	        "al", "cl", "dl", "bl", "ah", "ch", "dh", "bh", "r8l", "r9l",
	        "r10l", "r11l", "r12l", "r13l", "r14l", "r15l"
	},
	{
	        "ax", "cx", "dx", "bx", "sp", "bp", "si", "di", "r8w",
	        "r9w", "r10w", "r11w", "r12w", "r13w", "r14w", "r15w"
	},
	{
	        "eax", "ecx", "edx", "ebx", "esp", "ebp", "esi", "edi",
	        "r8d", "r9d", "r10d", "r11d", "r12d", "r13d", "r14d", "r15d"
	},
	{
	        "rax", "rcx", "rdx", "rbx", "rsp", "rbp", "rsi", "rdi",
	        "r8", "r9", "r10", "r11", "r12", "r13", "r14", "r15"
	}
};

static fcml_string reg_symbol_table_rex[7][16] = {
	{
	        "<none>", "<none>", "<none>", "<none>", "<none>", "<none>",
	        "<none>", "<none>", "<none>", "<none>", "<none>", "<none>",
	        "<none>", "<none>", "<none>", "<none>"
	},
	{
	        "<unknown GPR>", "<unknown GPR>", "<unknown GPR>", "<unknown GPR>",
	        "<unknown GPR>", "<unknown GPR>", "<unknown GPR>", "<unknown GPR>",
	        "<unknown GPR>", "<unknown GPR>", "<unknown GPR>", "<unknown GPR>",
	        "<unknown GPR>", "<unknown GPR>", "<unknown GPR>", "<unknown GPR>"
	},
	{
	        "<unknown SIMD>", "<unknown SIMD>", "<unknown SIMD>",
	        "<unknown SIMD>", "<unknown SIMD>", "<unknown SIMD>",
	        "<unknown SIMD>", "<unknown SIMD>", "<unknown SIMD>",
	        "<unknown SIMD>", "<unknown SIMD>", "<unknown SIMD>",
	        "<unknown SIMD>", "<unknown SIMD>", "<unknown SIMD>",
	        "<unknown SIMD>"
	},
	{
	        "st(0)", "st(1)", "st(2)", "st(3)", "st(4)", "st(5)", "st(6)",
	        "st(7)", "<unknown fpu>", "<unknown fpu>", "<unknown fpu>",
	        "<unknown fpu>", "<unknown fpu>", "<unknown fpu>", "<unknown fpu>",
	        "<unknown fpu>"
	},
	{
	        "es", "cs", "ss", "ds", "fs", "gs", "<unknown SR>", "<unknown SR>",
	        "<unknown SR>", "<unknown SR>", "<unknown SR>", "<unknown SR>",
	        "<unknown SR>", "<unknown SR>", "<unknown SR>", "<unknown SR>"
	},
	{
	        "cr0", "<unknown CR>", "cr2", "cr3", "cr4", "<unknown CR>",
	        "<unknown CR>", "<unknown CR>", "cr8", "<unknown CR>",
	        "<unknown CR>", "<unknown CR>", "<unknown CR>", "<unknown CR>",
	        "<unknown CR>", "<unknown CR>"
	},
	{
	        "dr0", "dr1", "dr2", "dr3", "dr4", "dr5", "dr6", "dr7",
	        "<unknown DR>", "<unknown DR>", "<unknown DR>", "<unknown DR>",
	        "<unknown DR>", "<unknown DR>", "<unknown DR>", "<unknown DR>"
	}
};

static fcml_string reg_gpr_symbol_table_ip[4] = {
	"<unknown ip>", "ip", "eip", "rip"
};

static fcml_string reg_operand_mask_symbol_table[8] = {
    "k0", "k1", "k2", "k3", "k4", "k5", "k6", "k7"
};

static fcml_string reg_gpr_symbol_table_rex[4][16] = {
	{
	        "al", "cl", "dl", "bl", "spl", "bpl", "sil", "dil", "r8l", "r9l",
	        "r10l", "r11l", "r12l", "r13l", "r14l", "r15l"
	},
	{
	        "ax", "cx", "dx", "bx", "sp", "bp", "si", "di", "r8w", "r9w",
	        "r10w", "r11w", "r12w", "r13w", "r14w", "r15w"
	},
	{
	        "eax", "ecx", "edx", "ebx", "esp", "ebp", "esi", "edi", "r8d",
	        "r9d", "r10d", "r11d", "r12d", "r13d", "r14d", "r15d"
	},
	{
	        "rax", "rcx", "rdx", "rbx", "rsp", "rbp", "rsi", "rdi", "r8",
	        "r9", "r10", "r11", "r12", "r13", "r14", "r15"
	}
};

static fcml_string reg_sidm_symbol_table[4][32] = {
	{
	  "mm0", "mm1", "mm2", "mm3", "mm4", "mm5", "mm6", "mm7",
	  "<wrong register>", "<wrong register>", "<wrong register>",
	  "<wrong register>", "<wrong register>", "<wrong register>",
	  "<wrong register>", "<wrong register>", "<wrong register>",
	  "<wrong register>", "<wrong register>", "<wrong register>",
	  "<wrong register>", "<wrong register>", "<wrong register>",
	  "<wrong register>", "<wrong register>", "<wrong register>",
	  "<wrong register>", "<wrong register>", "<wrong register>",
	  "<wrong register>", "<wrong register>", "<wrong register>"
	},
	{
	  "xmm0",  "xmm1",  "xmm2",  "xmm3",  "xmm4",  "xmm5",  "xmm6",  "xmm7",
	  "xmm8",  "xmm9",  "xmm10", "xmm11", "xmm12", "xmm13", "xmm14", "xmm15",
	  "xmm16", "xmm17", "xmm18", "xmm19", "xmm20", "xmm21", "xmm22", "xmm23",
	  "xmm24", "xmm25", "xmm26", "xmm27", "xmm28", "xmm29", "xmm30", "xmm31"
	},
	{
	  "ymm0",  "ymm1",  "ymm2",  "ymm3",  "ymm4",  "ymm5",  "ymm6",  "ymm7",
	  "ymm8",  "ymm9",  "ymm10", "ymm11", "ymm12", "ymm13", "ymm14", "ymm15",
	  "ymm16", "ymm17", "ymm18", "ymm19", "ymm20", "ymm21", "ymm22", "ymm23",
	  "ymm24", "ymm25", "ymm26", "ymm27", "ymm28", "ymm29", "ymm30", "ymm31"
	},
	{
      "zmm0",  "zmm1",  "zmm2",  "zmm3",  "zmm4",  "zmm5",  "zmm6",  "zmm7",
      "zmm8",  "zmm9",  "zmm10", "zmm11", "zmm12", "zmm13", "zmm14", "zmm15",
      "zmm16", "zmm17", "zmm18", "zmm19", "zmm20", "zmm21", "zmm22", "zmm23",
      "zmm24", "zmm25", "zmm26", "zmm27", "zmm28", "zmm29", "zmm30", "zmm31"
    }
};

fcml_string fcml_fn_cmn_dialect_render_mnemonic(fcml_string mnemonic,
        fcml_st_condition *condition, fcml_uint8_t conditional_group,
        fcml_bool show_carry) {

    fcml_string rendered_mnemonic = NULL;

    if (condition) {

        fcml_string suffix = NULL;
        fcml_int cond = (condition->condition_type << 1)
                | ((condition->is_negation) ? 1 : 0);

        if (show_carry) {
            if (cond == 2) {
                suffix = FCML_TEXT("c");
            } else if (cond == 3) {
                suffix = FCML_TEXT("nc");
            }
        }

        if (!suffix) {
            suffix = conditional_suffixes_render[conditional_group][cond];
        }

        fcml_usize mnemonic_len = fcml_fn_env_str_strlen(mnemonic);
        fcml_usize len = mnemonic_len + fcml_fn_env_str_strlen(suffix);
        rendered_mnemonic = fcml_fn_env_str_stralloc(len + 1);

        if (rendered_mnemonic) {
            fcml_fn_env_str_strcpy(rendered_mnemonic, mnemonic);
            fcml_fn_env_str_strcpy(rendered_mnemonic + mnemonic_len, suffix);
        }

    } else {
        rendered_mnemonic = fcml_fn_env_str_strdup(mnemonic);
    }

    return rendered_mnemonic;
}

fcml_ceh_error fcml_fn_cmn_dialect_get_mnemonic(const fcml_st_dialect *dialect,
        fcml_st_mp_mnemonic_set *mnemonic_set, fcml_st_mp_mnemonic **mnemonics,
        const fcml_st_condition *condition, int *mnemonics_counter) {

    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
    fcml_int counter = 0;
    fcml_st_coll_list_element *element = mnemonic_set->mnemonics->head;

    while (element) {

        fcml_st_mp_mnemonic *mnemonic_def = (fcml_st_mp_mnemonic*) element->item;

        if (condition != NULL) {
            /* Conditional instructions.*/

            fcml_uint32_t suffix_nr = condition->condition_type * 2
                    + (condition->is_negation ? 1 : 0);

            int i;
            for (i = 0; i < FCML_CMN_DIALECT_CND_GROUPS; i++) {
                fcml_string suffix = conditional_suffixes[i][suffix_nr];
                if (suffix) {
                    mnemonics[counter] =
                            fcml_fn_asm_dialect_alloc_mnemonic_with_suffix(
                                    mnemonic_def, suffix);
                    if (!mnemonics[counter]) {
                        /* Out of memory.*/
                        error = FCML_CEH_GEC_OUT_OF_MEMORY;
                        break;
                    }
                    counter++;
                }
            }
        } else {
            /* Allocate new instance of mnemonic.*/
            mnemonics[counter] = fcml_fn_asm_dialect_alloc_mnemonic(
                    mnemonic_def);

            if (mnemonics[counter]) {
                counter++;
            } else {
                error = FCML_CEH_GEC_OUT_OF_MEMORY;
            }
        }

        element = element->next;

    }

    if (error) {
        /* Free all prepared mnemonics.*/
        for (int i = 0; i < counter; i++) {
            fcml_fn_asm_dialect_free_mnemonic(mnemonics[i]);
        }
    }

    *mnemonics_counter = counter;

    return error;
}

fcml_ceh_error fcml_fn_cmn_dialect_get_register(const fcml_st_register *reg,
        fcml_string *printable_reg, fcml_bool is_rex) {

    fcml_int rs = 0;

    if (reg->type != FCML_REG_SIMD) {
        switch (reg->size) {
        case 8:
            rs = 0;
            break;
        case 16:
            rs = 1;
            break;
        case 32:
            rs = 2;
            break;
        case 64:
            rs = 3;
            break;
        }
        if (reg->type == FCML_REG_OPMASK) {
            *printable_reg = reg_operand_mask_symbol_table[reg->reg];
        } else if (reg->type == FCML_REG_IP) {
            *printable_reg = reg_gpr_symbol_table_ip[rs];
        } else {
            if (is_rex) {
                if (reg->type == FCML_REG_GPR) {
                    *printable_reg = reg_gpr_symbol_table_rex[rs][reg->reg];
                } else {
                    *printable_reg = reg_symbol_table_rex[reg->type][reg->reg];
                }
            } else {
                if (reg->type == FCML_REG_GPR) {
                    *printable_reg = reg_gpr_symbol_table[rs][reg->reg];
                } else {
                    *printable_reg = reg_symbol_table[reg->type][reg->reg];
                }
            }
        }
    } else {
        switch (reg->size) {
        case 64:
            rs = 0;
            break;
        case 128:
            rs = 1;
            break;
        case 256:
            rs = 2;
            break;
        case 512:
            rs = 3;
            break;
        default:
            return FCML_CEH_GEC_INVALID_INPUT;
        }
        *printable_reg = reg_sidm_symbol_table[rs][reg->reg];
    }

    return FCML_CEH_GEC_NO_ERROR;
}

void fcml_fn_cmn_dialect_free(fcml_st_dialect *dialect) {
    if (dialect) {
        fcml_st_dialect_context_int *dialect_context =
                (fcml_st_dialect_context_int*) dialect;
        fcml_fn_asm_dialect_free_mnemonic_lookup(dialect_context);
        fcml_fn_env_memory_free(dialect_context);
    }
}
