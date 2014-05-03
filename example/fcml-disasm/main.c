/*
 * FCML - Free Code Manipulation Library.
 * Copyright (C) 2010-2014 Slawomir Wojtasiak
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>

#include <fcml_intel_dialect.h>
#include <fcml_gas_dialect.h>
#include <fcml_disassembler.h>
#include <fcml_renderer.h>

fcml_string conditions[] = {
	"o", "b", "e", "be", "s", "p", "l", "le"
};

fcml_string prefix_types[] = {
	"FCML_PT_GROUP_UNKNOWN",
	"FCML_PT_GROUP_1",
	"FCML_PT_GROUP_2",
	"FCML_PT_GROUP_3",
	"FCML_PT_GROUP_4",
	"FCML_PT_REX",
	"FCML_PT_VEX",
	"FCML_PT_XOP",
};
fcml_string operand_types[] = {
	"FCML_EOT_NONE",
	"FCML_EOT_IMMEDIATE",
	"FCML_EOT_FAR_POINTER",
	"FCML_EOT_ADDRESS",
	"FCML_EOT_REGISTER"
};

fcml_string register_type[] = {
	"FCML_REG_UNDEFINED",
    "FCML_REG_GPR",
    "FCML_REG_SIMD",
    "FCML_REG_FPU",
    "FCML_REG_SEG",
    "FCML_REG_CR",
    "FCML_REG_DR",
    "FCML_REG_IP"
};

fcml_string fcml_reg_symbol_table[7][16] = {
	{ "<none>", "<none>", "<none>", "<none>", "<none>", "<none>", "<none>", "<none>", "<none>", "<none>", "<none>", "<none>", "<none>", "<none>", "<none>", "<none>" },
	{ "<unknown GPR>", "<unknown GPR>", "<unknown GPR>", "<unknown GPR>", "<unknown GPR>", "<unknown GPR>", "<unknown GPR>", "<unknown GPR>", "<unknown GPR>", "<unknown GPR>", "<unknown GPR>", "<unknown GPR>", "<unknown GPR>", "<unknown GPR>", "<unknown GPR>", "<unknown GPR>" },
	{ "<unknown SIMD>", "<unknown SIMD>", "<unknown SIMD>", "<unknown SIMD>", "<unknown SIMD>", "<unknown SIMD>", "<unknown SIMD>", "<unknown SIMD>", "<unknown SIMD>", "<unknown SIMD>", "<unknown SIMD>", "<unknown SIMD>", "<unknown SIMD>", "<unknown SIMD>", "<unknown SIMD>", "<unknown SIMD>" },
	{ "st(0)", "st(1)", "st(2)", "st(3)", "st(4)", "st(5)", "st(6)", "st(7)", "<unknown fpu>", "<unknown fpu>", "<unknown fpu>", "<unknown fpu>", "<unknown fpu>", "<unknown fpu>", "<unknown fpu>", "<unknown fpu>" },
	{ "es", "cs", "ss", "ds", "fs", "gs", "<unknown SR>", "<unknown SR>", "<unknown SR>", "<unknown SR>", "<unknown SR>", "<unknown SR>", "<unknown SR>", "<unknown SR>", "<unknown SR>", "<unknown SR>" },
	{ "cr0", "<unknown CR>", "cr2", "cr3", "cr4", "<unknown CR>", "<unknown CR>", "<unknown CR>", "cr8", "<unknown CR>", "<unknown CR>", "<unknown CR>", "<unknown CR>", "<unknown CR>", "<unknown CR>", "<unknown CR>" },
	{ "dr0", "dr1", "dr2", "dr3", "dr4", "dr5", "dr6", "dr7", "<unknown DR>", "<unknown DR>", "<unknown DR>", "<unknown DR>", "<unknown DR>", "<unknown DR>", "<unknown DR>", "<unknown DR>" }
};

fcml_string fcml_reg_gpr_symbol_table[4][16] = {
	{ "al", "cl", "dl", "bl", "ah", "ch", "dh", "bh", "r8l", "r9l", "r10l", "r11l", "r12l", "r13l", "r14l", "r15l" },
	{ "ax", "cx", "dx", "bx", "sp", "bp", "si", "di", "r8w", "r9w", "r10w", "r11w", "r12w", "r13w", "r14w", "r15w" },
	{ "eax", "ecx", "edx", "ebx", "esp", "ebp", "esi", "edi", "r8d", "r9d", "r10d", "r11d", "r12d", "r13d", "r14d", "r15d" },
	{ "rax", "rcx", "rdx", "rbx", "rsp", "rbp", "rsi", "rdi", "r8", "r9", "r10", "r11", "r12", "r13", "r14", "r15" }
};

fcml_string fcml_reg_symbol_table_rex[7][16] = {
	{ "<none>", "<none>", "<none>", "<none>", "<none>", "<none>", "<none>", "<none>", "<none>", "<none>", "<none>", "<none>", "<none>", "<none>", "<none>", "<none>" },
	{ "<unknown GPR>", "<unknown GPR>", "<unknown GPR>", "<unknown GPR>", "<unknown GPR>", "<unknown GPR>", "<unknown GPR>", "<unknown GPR>", "<unknown GPR>", "<unknown GPR>", "<unknown GPR>", "<unknown GPR>", "<unknown GPR>", "<unknown GPR>", "<unknown GPR>", "<unknown GPR>" },
	{ "<unknown SIMD>", "<unknown SIMD>", "<unknown SIMD>", "<unknown SIMD>", "<unknown SIMD>", "<unknown SIMD>", "<unknown SIMD>", "<unknown SIMD>", "<unknown SIMD>", "<unknown SIMD>", "<unknown SIMD>", "<unknown SIMD>", "<unknown SIMD>", "<unknown SIMD>", "<unknown SIMD>", "<unknown SIMD>" },
	{ "st(0)", "st(1)", "st(2)", "st(3)", "st(4)", "st(5)", "st(6)", "st(7)", "<unknown fpu>", "<unknown fpu>", "<unknown fpu>", "<unknown fpu>", "<unknown fpu>", "<unknown fpu>", "<unknown fpu>", "<unknown fpu>" },
	{ "es", "cs", "ss", "ds", "fs", "gs", "<unknown SR>", "<unknown SR>", "<unknown SR>", "<unknown SR>", "<unknown SR>", "<unknown SR>", "<unknown SR>", "<unknown SR>", "<unknown SR>", "<unknown SR>" },
	{ "cr0", "<unknown CR>", "cr2", "cr3", "cr4", "<unknown CR>", "<unknown CR>", "<unknown CR>", "cr8", "<unknown CR>", "<unknown CR>", "<unknown CR>", "<unknown CR>", "<unknown CR>", "<unknown CR>", "<unknown CR>" },
	{ "dr0", "dr1", "dr2", "dr3", "dr4", "dr5", "dr6", "dr7", "<unknown DR>", "<unknown DR>", "<unknown DR>", "<unknown DR>", "<unknown DR>", "<unknown DR>", "<unknown DR>", "<unknown DR>" }
};

fcml_string fcml_reg_gpr_symbol_table_ip[4] = {
	"<unknown ip>", "ip", "eip", "rip"
};

fcml_string fcml_reg_gpr_symbol_table_rex[4][16] = {
	{ "al", "cl", "dl", "bl", "spl", "bpl", "sil", "dil", "r8l", "r9l", "r10l", "r11l", "r12l", "r13l", "r14l", "r15l" },
	{ "ax", "cx", "dx", "bx", "sp", "bp", "si", "di", "r8w", "r9w", "r10w", "r11w", "r12w", "r13w", "r14w", "r15w" },
	{ "eax", "ecx", "edx", "ebx", "esp", "ebp", "esi", "edi", "r8d", "r9d", "r10d", "r11d", "r12d", "r13d", "r14d", "r15d" },
	{ "rax", "rcx", "rdx", "rbx", "rsp", "rbp", "rsi", "rdi", "r8", "r9", "r10", "r11", "r12", "r13", "r14", "r15" }
};

fcml_string fcml_reg_sidm_symbol_table[3][16] = {
	{ "mm0", "mm1", "mm2", "mm3", "mm4", "mm5", "mm6", "mm7", "<wrong register>", "<wrong register>", "<wrong register>", "<wrong register>", "<wrong register>", "<wrong register>", "<wrong register>", "<wrong register>" },
	{ "xmm0", "xmm1", "xmm2", "xmm3", "xmm4", "xmm5", "xmm6", "xmm7", "xmm8", "xmm9", "xmm10", "xmm11", "xmm12", "xmm13", "xmm14", "xmm15" },
	{ "ymm0", "ymm1", "ymm2", "ymm3", "ymm4", "ymm5", "ymm6", "ymm7", "ymm8", "ymm9", "ymm10", "ymm11", "ymm12", "ymm13", "ymm14", "ymm15" }
};

fcml_string get_register( const fcml_st_register *reg, fcml_bool is_rex ) {
	fcml_string printable_reg;
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
			printable_reg = fcml_reg_gpr_symbol_table_ip[rs];
		} else {
			if (is_rex) {
				if (reg->type == FCML_REG_GPR) {
					printable_reg = fcml_reg_gpr_symbol_table_rex[rs][reg->reg];
				} else {
					printable_reg = fcml_reg_symbol_table_rex[reg->type][reg->reg];
				}
			} else {
				if (reg->type == FCML_REG_GPR) {
					printable_reg = fcml_reg_gpr_symbol_table[rs][reg->reg];
				} else {
					printable_reg = fcml_reg_symbol_table[reg->type][reg->reg];
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
			return "Invalid register";
		}
		printable_reg = fcml_reg_sidm_symbol_table[rs][reg->reg];
	}
	return printable_reg;
}

void print_error_msg( fcml_st_ceh_error_container *errors ) {
	fcml_st_ceh_error_info *error = errors->errors;
	while( error ) {
		// Print error message.
		if( error->level == FCML_EN_CEH_EL_WARN ) {
			printf("WARN: ");
		} else if( error->level == FCML_EN_CEH_EL_ERROR ) {
			printf("ERROR: ");
		}
		printf("%3d: %s\n", error->code, error->message );
		error = error->next_error;
	}
}

fcml_string get_boolean( fcml_bool b ) {
	return b ? "true" : "false";
}

void print_address( fcml_st_address *address, fcml_bool is_rex ) {

	printf("    Address form: ");
	switch( address->address_form ) {
	case FCML_AF_UNDEFINED:
		printf("Undefined.\n");
		break;
	case FCML_AF_OFFSET:
		printf("Offset.\n");
		break;
	case FCML_AF_COMBINED:
		printf("Combined (Effective address).\n");
		break;
	default:
		printf("Unknown.\n");
	}
	printf("    Segment register: %s (default: %s)\n", get_register( &(address->segment_selector.segment_selector), is_rex ), get_boolean( address->segment_selector.is_default_reg ) );
	printf("    Size operator: %d\n", address->size_operator );
	if( address->address_form == FCML_AF_OFFSET ) {
		printf("    Offset:\n" );
		printf("     Size: %d\n", address->offset.size );
		printf("     Signed: %d\n", get_boolean( address->offset.is_signed ) );
		switch( address->offset.size ) {
		case FCML_DS_16:
			printf("     Value: 0x%04x\n", address->offset.off16 );
			break;
		case FCML_DS_32:
			printf("     Value: 0x%08x\n", address->offset.off32 );
			break;
		case FCML_DS_64:
			printf("     Value: 0x%016llx\n", address->offset.off64 );
			break;
		}
	} else if( address->address_form == FCML_AF_COMBINED ) {
		printf("    Effective address:\n" );
		printf("     Base: %s\n", get_register( &(address->effective_address.base), is_rex ) );
		printf("     Index: %s\n", get_register( &(address->effective_address.index), is_rex ) );
		printf("     Scale factor: %d\n", address->effective_address.scale_factor );
		fcml_st_integer *displacement = &(address->effective_address.displacement);
		printf("     Displacement:\n" );
		printf("      Size: %d\n", displacement->size );
		printf("      Signed: %s\n", get_boolean( displacement->is_signed ) );
		switch( displacement->size ) {
		case FCML_DS_8:
			printf("      Value: 0x%02x\n", displacement->int8 );
			break;
		case FCML_DS_16:
			printf("      Value: 0x%04x\n", displacement->int16 );
			break;
		case FCML_DS_32:
			printf("      Value: 0x%08x\n", displacement->int32 );
			break;
		case FCML_DS_64:
			printf("      Value: 0x%016llx\n", displacement->int64 );
			break;
		}
	}

}

void print_immediate( fcml_st_integer *immediate ) {
	printf("    Signed: %s\n", get_boolean( immediate->is_signed ) );
	printf("    Size: %d\n", immediate->size );
	printf("    Value: " );
	switch( immediate->size ) {
	case FCML_DS_8:
		printf("0x%02x\n", immediate->int8);
		break;
	case FCML_DS_16:
		printf("0x%04x\n", immediate->int16);
		break;
	case FCML_DS_32:
		printf("0x%08x\n", immediate->int32);
		break;
	case FCML_DS_64:
		printf("0x%016llx\n", immediate->int64);
		break;
	}
}

void print_far_pointer( fcml_st_far_pointer *far_pointer ) {
	printf("     Segment: 0x%04x\n", far_pointer->segment );
	printf("     Offset size: %d\n", far_pointer->offset_size );
	if( far_pointer->offset_size == FCML_DS_16 ) {
		printf("     Offset: 0x%04x\n", far_pointer->offset16 );
	}
	if( far_pointer->offset_size == FCML_DS_32 ) {
		printf("     Offset: 0x%08x\n", far_pointer->offset32 );
	}
}

void print_instruction_details( fcml_st_dialect *dialect, fcml_st_disassembler_result *result, fcml_st_render_config *render_config ) {

	int i;

	fcml_char buffer[FCML_REND_MAX_BUFF_LEN];

	fcml_ceh_error error = fcml_fn_render( dialect, render_config, buffer, sizeof( buffer ), result );
	if( error ) {
		printf( "Can not render instruction. Error code: %d\n", error );
		return;
	}

	printf("Basic information:\n");

	printf(" Disassembled instruction: %s\n", buffer);

	fcml_st_instruction *instruction = &(result->instruction);

	printf(" Mnemonic: %s\n", instruction->mnemonic );

	if( instruction->is_conditional ) {
		char neg[2] = {0};
		if( instruction->condition.is_negation ) {
			neg[0] = 'n';
		}
		printf(" Conditional instruction. Condition: \"%s%s\".\n", neg, conditions[ instruction->condition.condition_type ] );
	}

	if( instruction->hints ) {

		printf(" Instruction hints:");

		if( instruction->hints & FCML_HINT_FAR_POINTER ) {
			printf(" FCML_HINT_FAR_POINTER");
		}

		if( instruction->hints & FCML_HINT_NEAR_POINTER ) {
			printf(" FCML_HINT_NEAR_POINTER");
		}

		if( instruction->hints & FCML_HINT_LONG_FORM_POINTER ) {
			printf(" FCML_HINT_LONG_FORM_POINTER");
		}

		if( instruction->hints & FCML_HINT_INDIRECT_POINTER ) {
			printf(" FCML_HINT_INDIRECT_POINTER");
		}

		printf("\n");
	}

	if( instruction->prefixes ) {

		printf(" Explicit prefixes:");

		if( instruction->prefixes & FCML_PREFIX_LOCK ) {
			printf(" FCML_PREFIX_LOCK");
		}
		if( instruction->prefixes & FCML_PREFIX_REPNE ) {
			printf(" FCML_PREFIX_REPNE");
		}
		if( instruction->prefixes & FCML_PREFIX_REP ) {
			printf(" FCML_PREFIX_REP");
		}
		if( instruction->prefixes & FCML_PREFIX_XACQUIRE ) {
			printf(" FCML_PREFIX_XACQUIRE");
		}
		if( instruction->prefixes & FCML_PREFIX_XRELEASE ) {
			printf(" FCML_PREFIX_XRELEASE");
		}
		if( instruction->prefixes & FCML_PREFIX_BRANCH_HINT ) {
			printf(" FCML_PREFIX_BRANCH_HINT");
		}
		if( instruction->prefixes & FCML_PREFIX_NOBRANCH_HINT ) {
			printf(" FCML_PREFIX_NOBRANCH_HINT");
		}

		printf("\n");
	}

	printf( " Number of operands: %d\n", instruction->operands_count );

	printf( "  Operands:\n" );

	for( i = 0; i < instruction->operands_count; i++ ) {
		printf("   Operand: %d\n", i + 1 );
		fcml_st_operand *operand = &(instruction->operands[i]);
		printf("    Type: %s\n", operand_types[ operand->type ] );
		switch( operand->type ) {
		case FCML_EOT_IMMEDIATE: {
			print_immediate( &(operand->immediate) );
			break;
		}
		case FCML_EOT_FAR_POINTER: {
			print_far_pointer( &(operand->far_pointer) );
			break;
		}
		case FCML_EOT_ADDRESS: {
			print_address( &(operand->address), result->instruction_details.prefixes_details.is_rex );
			break;
		}
		case FCML_EOT_REGISTER:
			printf( "    Register: %s (Type: %s, Size: %d)\n", get_register( &(operand->reg), result->instruction_details.prefixes_details.is_rex ), register_type[operand->reg.type], operand->reg.size );
			break;
		}
	}

	printf( "Details:\n" );

	fcml_st_instruction_details *details = &(result->instruction_details);

	printf(" Instruction code: 0x");
	for( i = 0; i < details->instruction_size; i++ ) {
		printf( "%02x", details->instruction_code[i] );
	}
	printf("\n");

	printf( " Instruction code length: %d\n", details->instruction_size );
	printf( " Pseudo-op: %s\n", details->is_pseudo_op ? "true" : "false" );
	printf( " Shortcut: %s\n", details->is_shortcut ? "true" : "false" );

	/* ModR/M */

	fcml_st_decoded_modrm_details *modrm_details = &(details->modrm_details);
	if( modrm_details ) {
		printf( " ModR/M details:\n" );
		printf( "  Is RIP: %s\n", get_boolean( modrm_details->is_rip ) );
		printf( "  ModR/M byte: 0x%02x\n", modrm_details->modrm );
		if( modrm_details->sib.is_not_null ) {
			printf( "  SIB byte: 0x%02x\n", modrm_details->sib );
		}
	}

	/* Prefixes details. */

	fcml_st_prefixes_details *prefixes_details = &(details->prefixes_details);
	if( prefixes_details->prefixes_bytes_count ) {
		printf( " Prefixes details:\n" );
		printf( "  Prefixes size in bytes: %d\n", prefixes_details->prefixes_bytes_count );
		printf( "  Number of available prefixes: %d\n", prefixes_details->prefixes_count );
		printf( "  Available prefixes (flags):" );
		if( prefixes_details->is_branch ) {
			printf(" branch");
		}
		if( prefixes_details->is_lock ) {
			printf(" lock");
		}
		if( prefixes_details->is_nobranch ) {
			printf(" nobranch");
		}
		if( prefixes_details->is_rep ) {
			printf(" rep");
		}
		if( prefixes_details->is_repne ) {
			printf(" repne");
		}
		if( prefixes_details->is_rex ) {
			printf(" rex");
		}
		if( prefixes_details->is_vex ) {
			printf(" vex");
		}
		if( prefixes_details->is_xacquire ) {
			printf(" xacquire");
		}
		if( prefixes_details->is_xrelease ) {
			printf(" xrelease");
		}
		if( prefixes_details->is_xop ) {
			printf(" xop");
		}

		printf( "\n  Prefixes fields:");

		if( prefixes_details->is_vex || prefixes_details->is_xop )
			printf( " mmmm:%d", prefixes_details->mmmm );
		if( prefixes_details->is_vex || prefixes_details->is_xop || prefixes_details->is_rex )
			printf( " r:%d", prefixes_details->r );
		if( prefixes_details->is_vex || prefixes_details->is_xop || prefixes_details->is_rex )
			printf( " x:%d", prefixes_details->x );
		if( prefixes_details->is_vex || prefixes_details->is_xop || prefixes_details->is_rex )
			printf( " b:%d", prefixes_details->b );
		if( prefixes_details->is_vex || prefixes_details->is_xop || prefixes_details->is_rex )
			printf( " w:%d", prefixes_details->w );
		if( prefixes_details->is_vex || prefixes_details->is_xop )
			printf( " vvvv:%d", prefixes_details->vvvv );
		if( prefixes_details->is_vex || prefixes_details->is_xop )
			printf( " l:%d", prefixes_details->l );
		if( prefixes_details->is_vex || prefixes_details->is_xop )
			printf( " pp:%d", prefixes_details->pp );

		printf( "\n  Available prefixes (details):\n" );

		for( i = 0; i < prefixes_details->prefixes_count; i++ ) {
			fcml_st_instruction_prefix *prefix = &(prefixes_details->prefixes[i]);
			printf("   Byte: 0x%02x, Type %s, Mandatory: %s, XOP/VEX bytes: 0x%02x, 0x%02x.\n", prefix->prefix, prefix_types[ prefix->prefix_type ], get_boolean( prefix->mandatory_prefix ), prefix->vex_xop_bytes[0], prefix->vex_xop_bytes[1] );
		}

	}

	printf( " Operands details:\n" );

	for( i = 0; i < instruction->operands_count; i++ ) {
		printf("  Operand: %d\n", i + 1 );
		fcml_st_operand_details *operand_details = &(details->operand_details[i]);
		printf("   Access mode:" );
		if( operand_details->access_mode & FCML_AM_READ ) {
			printf( " FCML_AM_READ" );
		}
		if( operand_details->access_mode & FCML_AM_WRITE ) {
			printf( " FCML_AM_WRITE" );
		}
		printf("\n");
	}


}

int main(int argc, char **argv) {

	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

	/* Interpret arguments. */

	if( argc <= 1 ) {
		printf("Bad arguments.\n");
		exit(1);
	}

	fcml_st_disassembler_context context = {0};

	fcml_st_render_config render_config = {0};

	fcml_bool gas_dialect = 0;

	fcml_uint8_t code[FCML_INSTRUCTION_SIZE] = {0};

	fcml_int code_length = 0;

	int i;
	for( i = 1; i < argc; i++ ) {
		if( strcmp( argv[i], "-m16" ) == 0 ) {
			context.entry_point.op_mode = FCML_AF_16_BIT;
		} else if( strcmp( argv[i], "-m32" ) == 0 ) {
			context.entry_point.op_mode = FCML_AF_32_BIT;
		} else if( strcmp( argv[i], "-m64" ) == 0 ) {
			context.entry_point.op_mode = FCML_AF_64_BIT;
		} else if( strcmp( argv[i], "-asa16" ) == 0 ) {
			context.entry_point.address_size_attribute = FCML_DS_16;
		} else if( strcmp( argv[i], "-asa32" ) == 0 ) {
			context.entry_point.address_size_attribute = FCML_DS_32;
		} else if( strcmp( argv[i], "-asa64" ) == 0 ) {
			context.entry_point.address_size_attribute = FCML_DS_64;
		} else if( strcmp( argv[i], "-osa16" ) == 0 ) {
			context.entry_point.operand_size_attribute = FCML_DS_16;
		} else if( strcmp( argv[i], "-osa32" ) == 0 ) {
			context.entry_point.operand_size_attribute = FCML_DS_32;
		} else if( strcmp( argv[i], "-osa64" ) == 0 ) {
			context.entry_point.operand_size_attribute = FCML_DS_64;
		} else if( strcmp( argv[i], "-ip" ) == 0 ) {
			if( ++i < argc ) {
				char *res;
				errno = 0;
				context.entry_point.ip = strtoll( argv[i], &res, 16 );
				if ((errno == ERANGE && (context.entry_point.ip == FCML_INT64_MAX || context.entry_point.ip == FCML_INT64_MIN)) || (errno != 0 && context.entry_point.ip == 0) || (argv[i] == res) ) {
				   perror("Wrong instruction pointer.");
				   exit(EXIT_FAILURE);
			    }
			} else {
				printf("IP not set.\n");
				exit(1);
			}
		} else if( strcmp( argv[i], "-s" ) == 0 ) {
			context.configuration.short_forms = FCML_TRUE;
		} else if( strcmp( argv[i], "-e" ) == 0 ) {
			context.configuration.extend_disp_to_asa = FCML_TRUE;
		} else if( strcmp( argv[i], "-rc" ) == 0 ) {
			render_config.render_flags |= FCML_REND_FLAG_RENDER_CODE;
		} else if( strcmp( argv[i], "-rh" ) == 0 ) {
			render_config.render_flags |= FCML_REND_FLAG_HEX_IMM | FCML_REND_FLAG_HEX_DISPLACEMENT;
		} else if( strcmp( argv[i], "-rz" ) == 0 ) {
			render_config.render_flags |= FCML_REND_FLAG_REMOVE_LEADING_ZEROS;
		} else if( strcmp( argv[i], "-rs" ) == 0 ) {
			render_config.render_flags |= FCML_REND_FLAG_RENDER_DEFAULT_SEG;
		} else if( strcmp( argv[i], "-gas" ) == 0 ) {
			gas_dialect = FCML_TRUE;
		} else if( strcmp( argv[i], "--help" ) == 0 ) {
			printf("usage: fcml_disasm [-s] [-e] [-rc] [-rh] [-rz] [-rs] [-gas] \n" \
                   "       [-asa<size>] [-osa<size>] <-m<size>> <-ip address> <code>\n\n" \
                   "       -m16      16 bit addressing mode\n" \
                   "       -m32      32 bit addressing mode\n" \
                   "       -m64      64 bit addressing mode\n" \
                   "       -asa16    16 bit address size attribute\n" \
                   "       -asa32    32 bit address size attribute\n" \
                   "       -asa64    63 bit address size attribute\n" \
                   "       -osa16    16 bit operand size attribute\n" \
                   "       -osa32    32 bit operand size attribute\n" \
                   "       -osa64    63 bit operand size attribute\n" \
                   "       -ip       Instruction pointer address\n" \
                   "       -s        Prefer short instruction forms\n" \
                   "       -e        Extend displacement size to address size attribute\n" \
                   "       -rc       Render instruction code\n" \
                   "       -rh       Render immediate values and displacement as HEX\n" \
                   "       -rz       Remove leading zeros\n" \
                   "       -gas      Use GNU assembler/AT&T dialect (Intel dialect is used by default)\n\n" \
                   "example: fcml_disasm -m32 -ip 0x4001000 0x678316010203\n\n" \
                   );
			exit(0);
		} else if( i + 1 == argc ) {
			/* Parse instruction code. */
			char buff[3] = {0};
			char *code_str = argv[i];
			fcml_int code_str_size = strlen( code_str );
			fcml_int j, index = 0;
			for( j = 0; j < code_str_size; j += 2 ) {
				buff[0] = code_str[j];
				buff[1] = 0;
				if( j + 2 <= code_str_size ) {
					buff[1] = code_str[j + 1];
				}
				if( j == 0 && strcmp( buff, "0x" ) == 0 ) {
					continue;
				}
				char *res;
				errno = 0;
				code[index++] = (fcml_uint8_t)strtol( buff, &res, 16 );
				fcml_int8_t code_byte = code[index - 1];
				if ((errno == ERANGE && (code_byte == FCML_INT8_MAX || code_byte == FCML_INT8_MIN)) || (errno != 0 && code_byte == 0) || (buff == res) ) {
				   printf("Wrong instruction code: %s\n", code_str );
				   exit(EXIT_FAILURE);
				}
			}
			code_length = index;
		}
	}

	context.configuration.enable_error_messages = FCML_TRUE;

	if( !context.entry_point.op_mode ) {
		printf("Addressing mode not specified.\n");
		exit(1);
	}

	if( !code_length ) {
		printf("Instruction code not specified.\n");
		exit(1);
	}

	/* Initialize dialect to use with disassembler. */

	fcml_st_dialect *dialect;

	if( gas_dialect ) {
		error = fcml_fn_dialect_init_gas( FCML_GAS_DIALECT_CF_DEFAULT, &dialect );
	} else {
		error = fcml_fn_dialect_init_intel( FCML_INTEL_DIALECT_CF_DEFAULT, &dialect );
	}

	if( error ) {
		printf( "Can not initialize dialect, error: %d\n", error );
		exit(1);
	}

	/* Initialize disassembler for used dialect. */

	fcml_st_disassembler *disassembler;

	error = fcml_fn_disassembler_init( dialect, &disassembler );
	if( error ) {
		fcml_fn_dialect_free( dialect );
		printf( "Can not initialize assembler, error: %d\n", error );
		exit(1);
	}

	/* Prepare disassembler context. */

	context.disassembler = disassembler;
	context.code = code;
	context.code_length = code_length;

	fcml_st_disassembler_result result;

	fcml_fn_disassembler_result_prepare( &result );

	error = fcml_fn_disassemble( &context, &result );
	if( !error ) {
		print_instruction_details( dialect, &result, &render_config );
	} else {
		printf("Disassembling failed with error code: %d\n", error );
		print_error_msg( &(result.errors) );
	}

	fcml_fn_disassembler_result_free( &result );

	/* Free everything. */

	fcml_fn_disassembler_free( disassembler );

	fcml_fn_dialect_free( dialect );

	return 0;
}
