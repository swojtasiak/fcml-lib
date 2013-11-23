/*
 * fcml_common_dialect.c
 *
 *  Created on: Nov 16, 2013
 *      Author: tas
 */

#include "fcml_ceh.h"
#include "fcml_common.h"
#include "fcml_types.h"

#include "fcml_common_dialect.h"

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

fcml_string fcml_ar_asm_dialect_reg_gpr_symbol_table_ip[4] = {
	"<unknown ip>", "ip", "eip", "rip"
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

fcml_ceh_error fcml_fn_cmn_dialect_get_register( const fcml_st_register *reg, fcml_string *printable_reg, fcml_bool is_rex) {
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
		if ( reg->type == FCML_REG_IP ) {
			*printable_reg = fcml_ar_asm_dialect_reg_gpr_symbol_table_ip[rs];
		} else {
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
