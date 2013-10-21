/*
 * fcml_asm_dialect_intel.c
 *
 *  Created on: 1 wrz 2013
 *      Author: tAs
 */

#include "fcml_asm_dialect_intel.h"
#include "fcml_env.h"
#include "fcml_mnemonic_parser.h"
#include "fcml_rend_intel.h"

#include <string.h>

#define FCML_ASM_DIALECT_INTEL_GROUPS 3

fcml_string fcml_itb_intel_conditional_suffixes[3][16] = {
    { "o", "no",  "b",   "nb", "e", "ne", "be", "nbe", "s",  "ns", "p",  "np", "l",   "nl", "le", "nle" },
    { NULL, NULL, "nae", "ae", "z", "nz", "na", "a",   NULL, NULL, "pe", "po", "nge", "ge", "ng", "g"   },
    { NULL, NULL, "c",   "nc", NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,  NULL, NULL, NULL  }
};

fcml_string fcml_ar_asm_dialect_reg_symbol_table[7][16] = {
	{ "<none>", "<none>", "<none>", "<none>", "<none>", "<none>", "<none>", "<none>", "<none>", "<none>", "<none>", "<none>", "<none>", "<none>", "<none>", "<none>" },
	{ "<unknown GPR>", "<unknown GPR>", "<unknown GPR>", "<unknown GPR>", "<unknown GPR>", "<unknown GPR>", "<unknown GPR>", "<unknown GPR>", "<unknown GPR>", "<unknown GPR>", "<unknown GPR>", "<unknown GPR>", "<unknown GPR>", "<unknown GPR>", "<unknown GPR>", "<unknown GPR>" },
	{ "<unknown SIMD>", "<unknown SIMD>", "<unknown SIMD>", "<unknown SIMD>", "<unknown SIMD>", "<unknown SIMD>", "<unknown SIMD>", "<unknown SIMD>", "<unknown SIMD>", "<unknown SIMD>", "<unknown SIMD>", "<unknown SIMD>", "<unknown SIMD>", "<unknown SIMD>", "<unknown SIMD>", "<unknown SIMD>" },
	{ "st(0)", "st(1)", "st(2)", "st(3)", "st(4)", "st(5)", "st(6)", "st(7)", "<unknown fpu>", "<unknown fpu>", "<unknown fpu>", "<unknown fpu>", "<unknown fpu>", "<unknown fpu>", "<unknown fpu>", "<unknown fpu>" },
	{ "es", "cs", "ss", "ds", "fs", "gs", "<unknown SR>", "<unknown SR>", "<unknown SR>", "<unknown SR>", "<unknown SR>", "<unknown SR>", "<unknown SR>", "<unknown SR>", "<unknown SR>", "<unknown SR>" },
	{ "cr0", "<unknown CR>", "cr2", "cr3", "cr4", "<unknown CR>", "<unknown CR>", "<unknown CR>", "cr8", "<unknown CR>", "<unknown CR>", "<unknown CR>", "<unknown CR>", "<unknown CR>", "<unknown CR>", "<unknown CR>" },
	{ "dr0", "dr1", "dr2", "dr3", "dr4", "dr5", "dr6", "dr7", "<unknown DR>", "<unknown DR>", "<unknown DR>", "<unknown DR>", "<unknown DR>", "<unknown DR>", "<unknown DR>", "<unknown DR>" }
};

fcml_string fcml_ar_asm_dialect_reg_gpr_symbol_table[4][16] = {
	{ "al", "cl", "dl", "bl", "ah", "ch", "dh", "bh", "r8l", "r9l", "r10l", "r11l", "r12l", "r13l", "r14l", "r15l" },
	{ "ax", "cx", "dx", "bx", "sp", "bp", "si", "di", "r8w", "r9w", "r10w", "r11w", "r12w", "r13w", "r14w", "r15w" },
	{ "eax", "ecx", "edx", "ebx", "esp", "ebp", "esi", "edi", "r8d", "r9d", "r10d", "r11d", "r12d", "r13d", "r14d", "r15d" },
	{ "rax", "rcx", "rdx", "rbx", "rsp", "rbp", "rsi", "rdi", "r8", "r9", "r10", "r11", "r12", "r13", "r14", "r15" }
};

fcml_string fcml_ar_asm_dialect_reg_symbol_table_rex[7][16] = {
	{ "<none>", "<none>", "<none>", "<none>", "<none>", "<none>", "<none>", "<none>", "<none>", "<none>", "<none>", "<none>", "<none>", "<none>", "<none>", "<none>" },
	{ "<unknown GPR>", "<unknown GPR>", "<unknown GPR>", "<unknown GPR>", "<unknown GPR>", "<unknown GPR>", "<unknown GPR>", "<unknown GPR>", "<unknown GPR>", "<unknown GPR>", "<unknown GPR>", "<unknown GPR>", "<unknown GPR>", "<unknown GPR>", "<unknown GPR>", "<unknown GPR>" },
	{ "<unknown SIMD>", "<unknown SIMD>", "<unknown SIMD>", "<unknown SIMD>", "<unknown SIMD>", "<unknown SIMD>", "<unknown SIMD>", "<unknown SIMD>", "<unknown SIMD>", "<unknown SIMD>", "<unknown SIMD>", "<unknown SIMD>", "<unknown SIMD>", "<unknown SIMD>", "<unknown SIMD>", "<unknown SIMD>" },
	{ "st(0)", "st(1)", "st(2)", "st(3)", "st(4)", "st(5)", "st(6)", "st(7)", "<unknown fpu>", "<unknown fpu>", "<unknown fpu>", "<unknown fpu>", "<unknown fpu>", "<unknown fpu>", "<unknown fpu>", "<unknown fpu>" },
	{ "es", "cs", "ss", "ds", "fs", "gs", "<unknown SR>", "<unknown SR>", "<unknown SR>", "<unknown SR>", "<unknown SR>", "<unknown SR>", "<unknown SR>", "<unknown SR>", "<unknown SR>", "<unknown SR>" },
	{ "cr0", "<unknown CR>", "cr2", "cr3", "cr4", "<unknown CR>", "<unknown CR>", "<unknown CR>", "cr8", "<unknown CR>", "<unknown CR>", "<unknown CR>", "<unknown CR>", "<unknown CR>", "<unknown CR>", "<unknown CR>" },
	{ "dr0", "dr1", "dr2", "dr3", "dr4", "dr5", "dr6", "dr7", "<unknown DR>", "<unknown DR>", "<unknown DR>", "<unknown DR>", "<unknown DR>", "<unknown DR>", "<unknown DR>", "<unknown DR>" }
};

fcml_string fcml_ar_asm_dialect_reg_gpr_symbol_table_rex[4][16] = {
	{ "al", "cl", "dl", "bl", "spl", "bpl", "sil", "dil", "r8l", "r9l", "r10l", "r11l", "r12l", "r13l", "r14l", "r15l" },
	{ "ax", "cx", "dx", "bx", "sp", "bp", "si", "di", "r8w", "r9w", "r10w", "r11w", "r12w", "r13w", "r14w", "r15w" },
	{ "eax", "ecx", "edx", "ebx", "esp", "ebp", "esi", "edi", "r8d", "r9d", "r10d", "r11d", "r12d", "r13d", "r14d", "r15d" },
	{ "rax", "rcx", "rdx", "rbx", "rsp", "rbp", "rsi", "rdi", "r8", "r9", "r10", "r11", "r12", "r13", "r14", "r15" }
};

fcml_string fcml_ar_asm_dialect_reg_sidm_symbol_table[3][16] = {
	{ "mm0", "mm1", "mm2", "mm3", "mm4", "mm5", "mm6", "mm7", "<wrong register>", "<wrong register>", "<wrong register>", "<wrong register>", "<wrong register>", "<wrong register>", "<wrong register>", "<wrong register>" },
	{ "xmm0", "xmm1", "xmm2", "xmm3", "xmm4", "xmm5", "xmm6", "xmm7", "xmm8", "xmm9", "xmm10", "xmm11", "xmm12", "xmm13", "xmm14", "xmm15" },
	{ "ymm0", "ymm1", "ymm2", "ymm3", "ymm4", "ymm5", "ymm6", "ymm7", "ymm8", "ymm9", "ymm10", "ymm11", "ymm12", "ymm13", "ymm14", "ymm15" }
};

fcml_ceh_error fcml_fnp_asm_dialect_get_register_intel(fcml_st_register *reg, fcml_string *printable_reg, fcml_bool is_rex) {
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
		default:
			return FCML_CEH_GEC_INVALID_INPUT;
		}
		if (is_rex) {
			if (reg->type == FCML_REG_GPR) {
				*printable_reg = fcml_ar_asm_dialect_reg_gpr_symbol_table_rex[rs][reg->reg];
			} else {
				*printable_reg = fcml_ar_asm_dialect_reg_symbol_table_rex[reg->type][reg->reg];
			}
		} else {
			if (reg->type == FCML_REG_GPR) {
				*printable_reg = fcml_ar_asm_dialect_reg_gpr_symbol_table[rs][reg->reg];
			} else {
				*printable_reg = fcml_ar_asm_dialect_reg_symbol_table[reg->type][reg->reg];
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
		default:
			return FCML_CEH_GEC_INVALID_INPUT;
		}
		*printable_reg = fcml_ar_asm_dialect_reg_sidm_symbol_table[rs][reg->reg];
	}
	return FCML_CEH_GEC_NO_ERROR;
}

void fcml_fnp_asm_dialect_free_mnemonic_intel( fcml_st_mp_mnemonic *mnemonic ) {
    // Do nothing.
    if( mnemonic ) {
        fcml_fn_asm_dialect_free_mnemonic( mnemonic );
    }
}

fcml_ceh_error fcml_fnp_asm_dialect_get_mnemonic_intel( fcml_st_def_instruction_description *instruction, fcml_st_def_addr_mode_desc *addr_mode, fcml_st_condition *condition, fcml_st_mp_mnemonic **mnemonics, int *mnemonics_counter ) {

    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

    fcml_string mnemonic_pattern;

    int counter = 0;

    // Clean mnemonic array.
    int i;
    for( i = 0; i < FCML_ASM_DIALECT_MAX_MNEMONIC_COUNT; i++ ) {
        mnemonics[i] = NULL;
    }

    // Choose best mnemonic for instruction.
    if( addr_mode->mnemonic_override ) {
        mnemonic_pattern = addr_mode->mnemonic_override;
    } else {
        mnemonic_pattern = instruction->mnemonic;
    }

    fcml_st_mp_mnemonic_set *mnemonic_set;
    error = fcml_fn_mp_parse_mnemonics( mnemonic_pattern, &mnemonic_set );
    if( error ) {
        return error;
    }

    fcml_st_coll_list_element *element = mnemonic_set->mnemonics->head;
    while( element ) {

        fcml_st_mp_mnemonic *mnemonic_def = (fcml_st_mp_mnemonic*)element->item;

        if( condition != NULL ) {
            // Conditional instructions.

            fcml_uint32_t suffix_nr = condition->condition_type * 2 + ( condition->is_negation ? 1 : 0 );

            for( i = 0; i < FCML_ASM_DIALECT_INTEL_GROUPS; i++ ) {
                fcml_string suffix = fcml_itb_intel_conditional_suffixes[i][suffix_nr];
                if( suffix ) {
                    mnemonics[counter] = fcml_fn_asm_dialect_alloc_mnemonic_with_suffix( mnemonic_def, suffix );
                    if( !mnemonics[counter] ) {
                        // Out of memory.
                        error = FCML_CEH_GEC_OUT_OF_MEMORY;
                        break;
                    }
                    counter++;
                }
            }

        } else {
            // Allocate new instance of mnemonic.
            mnemonics[counter] = fcml_fn_asm_dialect_alloc_mnemonic( mnemonic_def );
            if( mnemonics[counter] ) {
                counter++;
            } else {
                error = FCML_CEH_GEC_OUT_OF_MEMORY;
            }
        }

        element = element->next;

    }

    if( error ) {
        // Free all prepared mnemonics.
        int i;
        for( i = 0; i < counter; i++ ) {
            fcml_fnp_asm_dialect_free_mnemonic_intel( mnemonics[i] );
        }
    }

    fcml_fn_mp_free_mnemonics( mnemonic_set );

    *mnemonics_counter = counter;

    return error;
}

fcml_st_dialect_context fcml_fn_get_intel_dialect_context() {
    fcml_st_dialect_context context;
    context.get_mnemonic = &fcml_fnp_asm_dialect_get_mnemonic_intel;
    context.free_mnemonic = &fcml_fnp_asm_dialect_free_mnemonic_intel;
    context.instruction_renderer = &fcml_fn_rend_render_instruction_intel;
    context.get_register = &fcml_fnp_asm_dialect_get_register_intel;
    return context;
}
