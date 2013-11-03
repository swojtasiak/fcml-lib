/*
 * fcml_asm_dialect_intel.c
 *
 *  Created on: 1 wrz 2013
 *      Author: tAs
 */

#include <string.h>
#include <stdio.h>

#include "fcml_dialect_intel.h"
#include "fcml_mnemonic_parser.h"
#include "fcml_env.h"
#include "fcml_coll.h"
#include "fcml_rend_intel.h"

// *************
// * MNEMONICS *
// *************

fcml_coll_map *fcml_map_dialect_intel_mnemonics_lookup = NULL;

fcml_st_dialect_mnemonic fcml_arr_dialect_intel_mnemonics[] = {
	{ FCML_TEXT("aaa"), FCML_ASM_DIALECT_INSTRUCTION( F_AAA, FCML_AM_NONE ), 0 },
	{ NULL, 0, 0 }
};

// ********************
// * END OF MNEMONICS *
// ********************

#define FCML_ASM_DIALECT_INTEL_GROUPS 3

fcml_string fcml_itb_intel_conditional_suffixes[3][16] = {
    { "o", "no",  "b",   "nb", "e", "ne", "be", "nbe", "s",  "ns", "p",  "np", "l",   "nl", "le", "nle" },
    { NULL, NULL, "nae", "ae", "z", "nz", "na", "a",   NULL, NULL, "pe", "po", "nge", "ge", "ng", "g"   },
    { NULL, NULL, "c",   "nc", NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,  NULL, NULL, NULL  }
};

fcml_string fcml_itb_intel_conditional_suffixes_render[2][16] = {
	{ "o", "no", "b", "nb", "e", "ne", "be", "nbe", "s", "ns", "p", "np", "l", "nl", "le", "nle" },
	{ "o", "no", "nae", "ae", "z", "nz", "na", "a", "s", "ns", "pe", "po", "nge", "ge", "ng", "g" }
};

fcml_string fcml_fnp_asm_dialect_render_mnemonic_intel( fcml_string mnemonic, fcml_st_condition *condition, fcml_uint8_t conditional_group, fcml_bool show_carry ) {
	fcml_string rendered_mnemonic = NULL;
	if( condition ) {
		fcml_string suffix = NULL;
		fcml_int cond = ( condition->condition_type << 1 ) | ( ( condition->is_negation ) ? 1 : 0 );
		if( show_carry ) {
			if( cond == 2 ) {
				suffix = "c";
			} else if( cond == 3 ) {
				suffix = "nc";
			}
		}
		if( !suffix ) {
			suffix = fcml_itb_intel_conditional_suffixes_render[conditional_group][cond];
		}
		fcml_usize mnemonic_len = fcml_fn_env_str_strlen( mnemonic );
		fcml_usize len = mnemonic_len + fcml_fn_env_str_strlen( suffix ) ;
		rendered_mnemonic = fcml_fn_env_str_stralloc( len + 1 );
		if( rendered_mnemonic ) {
			fcml_fn_env_str_strcpy(rendered_mnemonic, mnemonic);
			fcml_fn_env_str_strcpy(rendered_mnemonic + mnemonic_len, suffix);
		}
	} else {
		rendered_mnemonic = fcml_fn_env_str_strdup( mnemonic );
	}
	return rendered_mnemonic;
}

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

fcml_ceh_error fcml_fn_init_intel_dialect(void) {

	fcml_ceh_error error;

	if( !fcml_map_dialect_intel_mnemonics_lookup ) {

		// Prepare mnemonic lookup.
		fcml_map_dialect_intel_mnemonics_lookup = fcml_fn_coll_map_alloc( &fcml_coll_map_descriptor_uint32, sizeof( fcml_arr_dialect_intel_mnemonics ) / sizeof( fcml_st_dialect_mnemonic ), &error );
		if( error ) {
			return error;
		}

		fcml_st_dialect_mnemonic *current = &(fcml_arr_dialect_intel_mnemonics[0]);
		while( current->mnemonic ) {
			fcml_fn_coll_map_put( fcml_map_dialect_intel_mnemonics_lookup, &(current->instruction), current, &error );
			if( error ) {
				fcml_fn_coll_map_free( fcml_map_dialect_intel_mnemonics_lookup );
				fcml_map_dialect_intel_mnemonics_lookup = NULL;
				break;
			}
			current++;
		}

	}

	return error;
}

void fcml_fn_intel_dialect_free(void) {
	if( fcml_map_dialect_intel_mnemonics_lookup ) {
		fcml_fn_coll_map_free( fcml_map_dialect_intel_mnemonics_lookup );
		fcml_map_dialect_intel_mnemonics_lookup = NULL;
	}
}

fcml_ceh_error fcml_fnp_asm_dialect_get_register_intel( const fcml_st_register *reg, fcml_string *printable_reg, fcml_bool is_rex) {
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

fcml_ceh_error fcml_fn_asm_dialect_get_parsed_mnemonics_intel( fcml_st_def_instruction_desc *instruction, fcml_st_def_addr_mode_desc *addr_mode, fcml_st_mp_mnemonic_set **mnemonics ) {

	fcml_string mnemonic_pattern = NULL;

	fcml_uint32_t keys[] = {
		FCML_ASM_DIALECT_INSTRUCTION( instruction->instruction, addr_mode->addr_mode ),
		FCML_ASM_DIALECT_INSTRUCTION( instruction->instruction, FCML_AM_NONE )
	};

	int i;
	for( i = 0; i < sizeof( keys ) / sizeof( fcml_uint32_t ) && !mnemonic_pattern; i++ ) {
		fcml_st_dialect_mnemonic *dialect_mnemonic = (fcml_st_dialect_mnemonic*)fcml_fn_coll_map_get( fcml_map_dialect_intel_mnemonics_lookup, &(keys[i]) );
		if( dialect_mnemonic ) {
			mnemonic_pattern = dialect_mnemonic->mnemonic;
		}
	}

	if( !mnemonic_pattern ) {
		// Choose best mnemonic for instruction.
		if( addr_mode->mnemonic_override ) {
			mnemonic_pattern = addr_mode->mnemonic_override;
		} else {
			mnemonic_pattern = instruction->mnemonic;
		}
	}

	return fcml_fn_mp_parse_mnemonics( mnemonic_pattern, mnemonics );
}

fcml_ceh_error fcml_fnp_asm_dialect_get_mnemonic_intel( fcml_st_def_instruction_desc *instruction, fcml_st_def_addr_mode_desc *addr_mode, fcml_st_condition *condition, fcml_st_mp_mnemonic **mnemonics, int *mnemonics_counter ) {

    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

    int counter = 0;

    fcml_st_mp_mnemonic_set *mnemonic_set;

    error = fcml_fn_asm_dialect_get_parsed_mnemonics_intel( instruction, addr_mode, &mnemonic_set );
    if( error ) {
        return error;
    }

    fcml_st_coll_list_element *element = mnemonic_set->mnemonics->head;
    while( element ) {

        fcml_st_mp_mnemonic *mnemonic_def = (fcml_st_mp_mnemonic*)element->item;

        if( condition != NULL ) {
            // Conditional instructions.

            fcml_uint32_t suffix_nr = condition->condition_type * 2 + ( condition->is_negation ? 1 : 0 );

            int i;
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

fcml_ceh_error fcml_fnp_asm_dialect_render_size_operator_intel( fcml_data_size size_operator, fcml_string buffer, fcml_usize buffer_len, fcml_bool is_media_instruction ) {

	fcml_string size_operator_printable = NULL;

	switch( size_operator ) {
	case 0:
		break;
	case 8:
		size_operator_printable = "byte ptr ";
		break;
	case 16:
		size_operator_printable = "word ptr ";
		break;
	case 32:
		size_operator_printable = "dword ptr ";
		break;
	case 48:
		size_operator_printable = "fword ptr ";
		break;
	case 64:
		size_operator_printable = is_media_instruction ? "mmword ptr " : "qword ptr ";
		break;
	case 80:
		size_operator_printable = "tbyte ptr ";
		break;
	case 128:
		size_operator_printable = is_media_instruction ? "xmmword ptr " : "oword ptr ";
		break;
	case 256:
		size_operator_printable = is_media_instruction ? "ymmword ptr " : "qqword ";
		break;
	default:
		snprintf( buffer, buffer_len, "%dbyte ptr ", size_operator / 8 );
	}

	if( size_operator_printable ) {
		fcml_fn_env_str_strncpy( buffer, size_operator_printable, buffer_len );
	}

	return FCML_CEH_GEC_NO_ERROR;
}

fcml_st_dialect_context fcml_fn_get_intel_dialect_context() {
    fcml_st_dialect_context context;
    context.get_mnemonic = &fcml_fnp_asm_dialect_get_mnemonic_intel;
    context.render_mnemonic = &fcml_fnp_asm_dialect_render_mnemonic_intel;
    context.get_parsed_mnemonics = &fcml_fn_asm_dialect_get_parsed_mnemonics_intel;
    context.free_mnemonic = &fcml_fnp_asm_dialect_free_mnemonic_intel;
    context.instruction_renderer = &fcml_fn_rend_render_instruction_intel;
    context.get_register = &fcml_fnp_asm_dialect_get_register_intel;
    context.size_operator_renderer = &fcml_fnp_asm_dialect_render_size_operator_intel;
    return context;
}
