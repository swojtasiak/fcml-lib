/*
 * fcml_asm_dialect_intel.c
 *
 *  Created on: 1 wrz 2013
 *      Author: tAs
 */

#include <stdio.h>
//#include <string.h>

#include "fcml_ceh.h"
#include "fcml_coll.h"
#include "fcml_common.h"
#include "fcml_common_dialect.h"
#include "fcml_def.h"
#include "fcml_dialect.h"
#include "fcml_dialect_int.h"
//#include "fcml_dialect_intel.h"
#include "fcml_disassembler.h"
#include "fcml_env.h"
#include "fcml_errors.h"
#include "fcml_mnemonic_parser.h"
#include "fcml_rend_att.h"
#include "fcml_types.h"
#include "fcml_x64att_asm_parser.h"

// *************
// * MNEMONICS *
// *************

fcml_coll_map *fcml_map_dialect_att_mnemonics_lookup = NULL;

fcml_st_dialect_mnemonic fcml_arr_dialect_att_mnemonics[] = {
	{ FCML_TEXT("aaa"), FCML_ASM_DIALECT_INSTRUCTION( F_AAA, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("aad"), FCML_ASM_DIALECT_INSTRUCTION( F_AAD, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("aam"), FCML_ASM_DIALECT_INSTRUCTION( F_AAM, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("aas"), FCML_ASM_DIALECT_INSTRUCTION( F_AAS, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("adc"), FCML_ASM_DIALECT_INSTRUCTION( F_ADC, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("adcb[sb]"), FCML_ASM_DIALECT_INSTRUCTION( F_ADC, FCML_AM_RM8_IMM8 ), 0 },
	{ FCML_TEXT("adc;adcw[sf,ow,mm];adcl[sf,od,mm];adcq[sf,oq,mm]"), FCML_ASM_DIALECT_INSTRUCTION( F_ADC, FCML_AM_RMO_IMMO ), 0 },
	{ FCML_TEXT("adc;adcw[sf,ow,mm];adcl[sf,od,mm];adcq[sf,oq,mm]"), FCML_ASM_DIALECT_INSTRUCTION( F_ADC, FCML_AM_RMO_IMM8 ), 0 },
	{ FCML_TEXT("add"), FCML_ASM_DIALECT_INSTRUCTION( F_ADD, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("addb[sb]"), FCML_ASM_DIALECT_INSTRUCTION( F_ADD, FCML_AM_RM8_IMM8 ), 0 },
	{ FCML_TEXT("add;addw[sf,ow,mm];addl[sf,od,mm];addq[sf,oq,mm]"), FCML_ASM_DIALECT_INSTRUCTION( F_ADD, FCML_AM_RMO_IMMO ), 0 },
	{ FCML_TEXT("add;addw[sf,ow,mm];addl[sf,od,mm];addq[sf,oq,mm]"), FCML_ASM_DIALECT_INSTRUCTION( F_ADD, FCML_AM_RMO_IMM8 ), 0 },
	{ FCML_TEXT("addpd"), FCML_ASM_DIALECT_INSTRUCTION( F_ADDPD, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("vaddpd"), FCML_ASM_DIALECT_INSTRUCTION( F_VADDPD, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("addps"), FCML_ASM_DIALECT_INSTRUCTION( F_ADDPS, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("vaddps"), FCML_ASM_DIALECT_INSTRUCTION( F_VADDPS, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("addsd"), FCML_ASM_DIALECT_INSTRUCTION( F_ADDSD, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("vaddsd"), FCML_ASM_DIALECT_INSTRUCTION( F_VADDSD, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("addss"), FCML_ASM_DIALECT_INSTRUCTION( F_ADDSS, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("vaddss"), FCML_ASM_DIALECT_INSTRUCTION( F_VADDSS, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("addsubpd"), FCML_ASM_DIALECT_INSTRUCTION( F_ADDSUBPD, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("vaddsubpd"), FCML_ASM_DIALECT_INSTRUCTION( F_VADDSUBPD, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("addsubps"), FCML_ASM_DIALECT_INSTRUCTION( F_ADDSUBPS, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("vaddsubps"), FCML_ASM_DIALECT_INSTRUCTION( F_VADDSUBPS, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("aesdec"), FCML_ASM_DIALECT_INSTRUCTION( F_AESDEC, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("vaesdec"), FCML_ASM_DIALECT_INSTRUCTION( F_VAESDEC, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("aesdeclast"), FCML_ASM_DIALECT_INSTRUCTION( F_AESDECLAST, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("vaesdeclast"), FCML_ASM_DIALECT_INSTRUCTION( F_VAESDECLAST, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("aesenc"), FCML_ASM_DIALECT_INSTRUCTION( F_AESENC, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("vaesenc"), FCML_ASM_DIALECT_INSTRUCTION( F_VAESENC, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("aesenclast"), FCML_ASM_DIALECT_INSTRUCTION( F_AESENCLAST, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("vaesenclast"), FCML_ASM_DIALECT_INSTRUCTION( F_VAESENCLAST, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("aesimc"), FCML_ASM_DIALECT_INSTRUCTION( F_AESIMC, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("vaesimc"), FCML_ASM_DIALECT_INSTRUCTION( F_VAESIMC, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("aeskeygenassist"), FCML_ASM_DIALECT_INSTRUCTION( F_AESKEYGENASSIST, 0 ), 0 },
	{ FCML_TEXT("vaeskeygenassist"), FCML_ASM_DIALECT_INSTRUCTION( F_VAESKEYGENASSIST, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("and"), FCML_ASM_DIALECT_INSTRUCTION( F_AND, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("andb[sb]"), FCML_ASM_DIALECT_INSTRUCTION( F_AND, FCML_AM_RM8_IMM8 ), 0 },
	{ FCML_TEXT("and;andw[sf,ow,mm];andl[sf,od,mm];andq[sf,oq,mm]"), FCML_ASM_DIALECT_INSTRUCTION( F_AND, FCML_AM_RMO_IMMO ), 0 },
	{ FCML_TEXT("and;andw[sf,ow,mm];andl[sf,od,mm];andq[sf,oq,mm]"), FCML_ASM_DIALECT_INSTRUCTION( F_AND, FCML_AM_RMO_IMM8 ), 0 },
	{ FCML_TEXT("andpd"), FCML_ASM_DIALECT_INSTRUCTION( F_ANDPD, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("vandpd"), FCML_ASM_DIALECT_INSTRUCTION( F_VANDPD, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("andps"), FCML_ASM_DIALECT_INSTRUCTION( F_ANDPS, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("vandps"), FCML_ASM_DIALECT_INSTRUCTION( F_VANDPS, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("andnpd"), FCML_ASM_DIALECT_INSTRUCTION( F_ANDNPD, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("vandnpd"), FCML_ASM_DIALECT_INSTRUCTION( F_VANDNPD, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("andnps"), FCML_ASM_DIALECT_INSTRUCTION( F_ANDNPS, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("vandnps"), FCML_ASM_DIALECT_INSTRUCTION( F_VANDNPS, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("arpl"), FCML_ASM_DIALECT_INSTRUCTION( F_ARPL, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("andn"), FCML_ASM_DIALECT_INSTRUCTION( F_ANDN, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("adcx"), FCML_ASM_DIALECT_INSTRUCTION( F_ADCX, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("adox"), FCML_ASM_DIALECT_INSTRUCTION( F_ADOX, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("blendpd"), FCML_ASM_DIALECT_INSTRUCTION( F_BLENDPD, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("vblendpd"), FCML_ASM_DIALECT_INSTRUCTION( F_VBLENDPD, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("blendps"), FCML_ASM_DIALECT_INSTRUCTION( F_BLENDPS, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("vblendps"), FCML_ASM_DIALECT_INSTRUCTION( F_VBLENDPS, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("blendvpd"), FCML_ASM_DIALECT_INSTRUCTION( F_BLENDVPD, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("vblendvpd"), FCML_ASM_DIALECT_INSTRUCTION( F_VBLENDVPD, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("blendvps"), FCML_ASM_DIALECT_INSTRUCTION( F_BLENDVPS, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("vblendvps"), FCML_ASM_DIALECT_INSTRUCTION( F_VBLENDVPS, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("bound"), FCML_ASM_DIALECT_INSTRUCTION( F_BOUND, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("bsf"), FCML_ASM_DIALECT_INSTRUCTION( F_BSF, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("bsr"), FCML_ASM_DIALECT_INSTRUCTION( F_BSR, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("bswap"), FCML_ASM_DIALECT_INSTRUCTION( F_BSWAP, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("bt;btw[sf,ow,mm];btl[sf,od,mm];btq[sf,oq,mm]"), FCML_ASM_DIALECT_INSTRUCTION( F_BT, FCML_AM_RMO_IMM8 ), 0 },
	{ FCML_TEXT("bt"), FCML_ASM_DIALECT_INSTRUCTION( F_BT, FCML_AM_RMO_RO ), 0 },
	{ FCML_TEXT("btc;btcw[sf,ow,mm];btcl[sf,od,mm];btcq[sf,oq,mm]"), FCML_ASM_DIALECT_INSTRUCTION( F_BTC, FCML_AM_RMO_IMM8 ), 0 },
	{ FCML_TEXT("btc"), FCML_ASM_DIALECT_INSTRUCTION( F_BTC, FCML_AM_RMO_RO ), 0 },
	{ FCML_TEXT("btr;btrw[sf,ow,mm];btrl[sf,od,mm];btrq[sf,oq,mm]"), FCML_ASM_DIALECT_INSTRUCTION( F_BTR, FCML_AM_RMO_IMM8 ), 0 },
	{ FCML_TEXT("btr"), FCML_ASM_DIALECT_INSTRUCTION( F_BTR, FCML_AM_RMO_RO ), 0 },
	{ FCML_TEXT("bts;btsw[sf,ow,mm];btsl[sf,od,mm];btsq[sf,oq,mm]"), FCML_ASM_DIALECT_INSTRUCTION( F_BTS, FCML_AM_RMO_IMM8 ), 0 },
	{ FCML_TEXT("bts"), FCML_ASM_DIALECT_INSTRUCTION( F_BTS, FCML_AM_RMO_RO ), 0 },
	{ FCML_TEXT("bexr;bextr"), FCML_ASM_DIALECT_INSTRUCTION( F_BEXR, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("blcfill"), FCML_ASM_DIALECT_INSTRUCTION( F_BLCFILL, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("blci"), FCML_ASM_DIALECT_INSTRUCTION( F_BLCI, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("blcic"), FCML_ASM_DIALECT_INSTRUCTION( F_BLCIC, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("blcmsk"), FCML_ASM_DIALECT_INSTRUCTION( F_BLCMSK, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("blcs"), FCML_ASM_DIALECT_INSTRUCTION( F_BLCS, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("blsfill"), FCML_ASM_DIALECT_INSTRUCTION( F_BLSFILL, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("blsi"), FCML_ASM_DIALECT_INSTRUCTION( F_BLSI, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("blsic"), FCML_ASM_DIALECT_INSTRUCTION( F_BLSIC, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("blsmsk"), FCML_ASM_DIALECT_INSTRUCTION( F_BLSMSK, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("blsr"), FCML_ASM_DIALECT_INSTRUCTION( F_BLSR, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("bzhi"), FCML_ASM_DIALECT_INSTRUCTION( F_BZHI, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("call;callw[sf,ow];lcall[sf,od];callq[sf,oq]"), FCML_ASM_DIALECT_INSTRUCTION( F_CALL, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("cbtw[ow];cwtl[od];cltq[oq]"), FCML_ASM_DIALECT_INSTRUCTION( F_CBW, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("clc"), FCML_ASM_DIALECT_INSTRUCTION( F_CLC, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("cld"), FCML_ASM_DIALECT_INSTRUCTION( F_CLD, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("clflush[sb]"), FCML_ASM_DIALECT_INSTRUCTION( F_CLFLUSH, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("cli"), FCML_ASM_DIALECT_INSTRUCTION( F_CLI, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("clgi"), FCML_ASM_DIALECT_INSTRUCTION( F_CLGI, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("clts"), FCML_ASM_DIALECT_INSTRUCTION( F_CLTS, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("cmc"), FCML_ASM_DIALECT_INSTRUCTION( F_CMC, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("cmov"), FCML_ASM_DIALECT_INSTRUCTION( F_CMOV, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("cmp"), FCML_ASM_DIALECT_INSTRUCTION( F_CMP, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("cmp"), FCML_ASM_DIALECT_INSTRUCTION( F_CMP, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("cmpb[sb]"), FCML_ASM_DIALECT_INSTRUCTION( F_CMP, FCML_AM_RM8_IMM8 ), 0 },
	{ FCML_TEXT("cmp;cmpw[sf,ow,mm];cmpl[sf,od,mm];cmpq[sf,oq,mm]"), FCML_ASM_DIALECT_INSTRUCTION( F_CMP, FCML_AM_RMO_IMMO ), 0 },
	{ FCML_TEXT("cmp;cmpw[sf,ow,mm];cmpl[sf,od,mm];cmpq[sf,oq,mm]"), FCML_ASM_DIALECT_INSTRUCTION( F_CMP, FCML_AM_RMO_IMM8 ), 0 },
	{ FCML_TEXT("cmppd"), FCML_ASM_DIALECT_INSTRUCTION( F_CMPPD, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("vcmppd"), FCML_ASM_DIALECT_INSTRUCTION( F_VCMPPD, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("cmpps"), FCML_ASM_DIALECT_INSTRUCTION( F_CMPPS, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("vcmpps"), FCML_ASM_DIALECT_INSTRUCTION( F_VCMPPS, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("cmpsb[tb,sb]"), FCML_ASM_DIALECT_INSTRUCTION( F_CMPS, FCML_M8_M8 ), 0 },
	{ FCML_TEXT("cmpsw[ts,ow,a*];cmpsd[ts,od,a*];cmpsq[ts,oq,a*]"), FCML_ASM_DIALECT_INSTRUCTION( F_CMPS, FCML_MO_MO ), 0 },
	{ NULL, 0, 0 }
};

// ********************
// * END OF MNEMONICS *
// ********************

#define FCML_ASM_DIALECT_att_GROUPS 3

fcml_string fcml_itb_att_conditional_suffixes[3][16] = {
    { "o", "no",  "b",   "nb", "e", "ne", "be", "nbe", "s",  "ns", "p",  "np", "l",   "nl", "le", "nle" },
    { NULL, NULL, "nae", "ae", "z", "nz", "na", "a",   NULL, NULL, "pe", "po", "nge", "ge", "ng", "g"   },
    { NULL, NULL, "c",   "nc", NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,  NULL, NULL, NULL  }
};

fcml_string fcml_itb_att_conditional_suffixes_render[2][16] = {
	{ "o", "no", "b", "nb", "e", "ne", "be", "nbe", "s", "ns", "p", "np", "l", "nl", "le", "nle" },
	{ "o", "no", "nae", "ae", "z", "nz", "na", "a", "s", "ns", "pe", "po", "nge", "ge", "ng", "g" }
};

// Dialect instance is set up by "fcml_fn_init_att_dialect" method.
fcml_st_dialect_context_int fcml_dialect_context_att;

fcml_string fcml_ifn_asm_dialect_render_mnemonic_att( fcml_string mnemonic, fcml_st_condition *condition, fcml_uint8_t conditional_group, fcml_bool show_carry ) {
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
			suffix = fcml_itb_att_conditional_suffixes_render[conditional_group][cond];
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

void fcml_fn_att_dialect_free(void) {
	if( fcml_map_dialect_att_mnemonics_lookup ) {
		fcml_fn_coll_map_free( fcml_map_dialect_att_mnemonics_lookup );
		fcml_map_dialect_att_mnemonics_lookup = NULL;
	}
}

fcml_ceh_error fcml_ifn_asm_dialect_get_register_att( const fcml_st_register *reg, fcml_string buffer, fcml_int buffer_length, fcml_bool is_rex) {
	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
	fcml_string printable_reg;
	error = fcml_fn_cmn_dialect_get_register( reg, &printable_reg, is_rex );
	if( error ) {
		return error;
	}
	fcml_fn_env_str_snprintf( buffer, buffer_length, "%%%s", printable_reg );
	return error;
}

void fcml_ifn_asm_dialect_free_mnemonic_att( fcml_st_mp_mnemonic *mnemonic ) {
    // Do nothing.
    if( mnemonic ) {
        fcml_fn_asm_dialect_free_mnemonic( mnemonic );
    }
}

fcml_ceh_error fcml_fn_asm_dialect_get_parsed_mnemonics_att( fcml_st_def_instruction_desc *instruction, fcml_st_def_addr_mode_desc *addr_mode, fcml_st_mp_mnemonic_set **mnemonics ) {

	fcml_string mnemonic_pattern = NULL;

	fcml_uint32_t keys[] = {
		FCML_ASM_DIALECT_INSTRUCTION( instruction->instruction, addr_mode->addr_mode ),
		FCML_ASM_DIALECT_INSTRUCTION( instruction->instruction, FCML_AM_ALL )
	};

	int i;
	for( i = 0; i < sizeof( keys ) / sizeof( fcml_uint32_t ) && !mnemonic_pattern; i++ ) {
		fcml_st_dialect_mnemonic *dialect_mnemonic = (fcml_st_dialect_mnemonic*)fcml_fn_coll_map_get( fcml_map_dialect_att_mnemonics_lookup, &(keys[i]) );
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

fcml_ceh_error fcml_ifn_asm_dialect_get_mnemonic_att( fcml_st_def_instruction_desc *instruction, fcml_st_def_addr_mode_desc *addr_mode, fcml_st_condition *condition, fcml_st_mp_mnemonic **mnemonics, int *mnemonics_counter ) {

    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

    int counter = 0;

    fcml_st_mp_mnemonic_set *mnemonic_set;

    error = fcml_fn_asm_dialect_get_parsed_mnemonics_att( instruction, addr_mode, &mnemonic_set );
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
            for( i = 0; i < FCML_ASM_DIALECT_att_GROUPS; i++ ) {
                fcml_string suffix = fcml_itb_att_conditional_suffixes[i][suffix_nr];
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
            fcml_ifn_asm_dialect_free_mnemonic_att( mnemonics[i] );
        }
    }

    fcml_fn_mp_free_mnemonics( mnemonic_set );

    *mnemonics_counter = counter;

    return error;
}

// TODO: wywalis z dialekt do renderera, dialekt nie ma z tym nic wspolnego.
fcml_ceh_error fcml_ifn_asm_dialect_render_size_operator_att( fcml_data_size size_operator, fcml_string buffer, fcml_usize buffer_len, fcml_bool is_media_instruction ) {

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

void fcml_ifn_asm_dialect_att_revert_operands( fcml_st_operand *operands, fcml_int count ) {
	fcml_st_operand tmp_operand;
	fcml_int i;
	for( i = 0; i < count / 2; i++ ) {
		tmp_operand = operands[i];
		operands[i] = operands[count - i - 1];
		operands[count - i - 1] = tmp_operand;
	}
}

fcml_ceh_error fcml_ifn_asm_dialect_assembler_preprocessor_att( fcml_st_instruction *instrunction, fcml_st_mp_mnemonic *mnemonic, fcml_bool *has_been_changed ) {

	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

	fcml_bool changed = FCML_FALSE;

	if( !mnemonic ) {

		// Operands has to be reverted.
		if( instrunction->operands_count > 1 ) {
			fcml_ifn_asm_dialect_att_revert_operands( instrunction->operands, instrunction->operands_count );
			changed = FCML_TRUE;
		}

		// If there is memory operand without data size set, it has to be deduced using register given in another operand.
		/*int i;
		fcml_st_operand *operand_reg = NULL;
		fcml_st_operand *operand_mem = NULL;
		for( i = 0; i < FCML_OPERANDS_COUNT; i++ ) {
			fcml_st_operand *operand = &(instrunction->operands[i]);
			switch( operand->type ) {
			case FCML_EOT_REGISTER:
				operand_reg = operand;
				break;
			case FCML_EOT_ADDRESS:
				// If size operand has been set by user, we shouldn't correct it in any way.
				if( operand->address.size_operator == FCML_DS_UNDEF ) {
					operand_mem = operand;
				}
				break;
			default:
				break;
			}
		}

		if( operand_mem ) {
			// TODO: Sprawdzic jak sie zachowa z rejestrami CS,DS, DR0. CR0 itd.
			if( operand_reg && operand_reg->reg.size != FCML_DS_UNDEF ) {
				// Data size set basing on register size.
				operand_mem->address.size_operator = operand_reg->reg.size;
				changed = FCML_TRUE;
			} else {
				error = FCML_EN_UNKNOWN_DATA_SIZE_FOR_MEMORY_ADDRESSING;
			}
		}*/

	} else {
		// Mnemonic has been found, check if data size should be corrected for instruction. Take into account that data size specified by
		// mnemonic has greater priority than data size set directly by user.
		fcml_data_size data_size = FCML_DS_UNDEF;
		if( mnemonic->is_byte_ds ) {
			data_size = FCML_DS_8;
		} else if( mnemonic->is_full_ds ) {
			// Full data size is based on effective operand size attribute.
			data_size = mnemonic->supported_osa;
		}
		if( data_size != FCML_DS_UNDEF ) {
			// Find effective address and make a correction to size operator.
			int i;
			for( i = 0; i < instrunction->operands_count; i++ ) {
				fcml_st_operand *operand = &(instrunction->operands[i]);
				if( operand->type == FCML_EOT_ADDRESS ) {
					operand->address.size_operator = data_size;
					changed = FCML_TRUE;
				}
			}
		}
	}

	if( has_been_changed ) {
		*has_been_changed = changed;
	}

	return error;
}

fcml_ceh_error fcml_ifn_asm_dialect_disassembler_postprocessor_att( fcml_st_dasm_disassembler_result *disassembler_result ) {

	fcml_int operands_count = disassembler_result->instruction.operands_count;

	if( operands_count > 1 ) {

		// Revert operands.
		fcml_ifn_asm_dialect_att_revert_operands( disassembler_result->instruction.operands, operands_count );

		// Revert operand details.
		fcml_st_dasm_operand_details *operand_details = disassembler_result->instruction_details.operand_details;
		fcml_st_dasm_operand_details tmp_operand_details;
		fcml_int i;
		for( i = 0; i < operands_count / 2; i++ ) {
			tmp_operand_details = operand_details[i];
			operand_details[i] = operand_details[operands_count - i - 1];
			operand_details[operands_count - i - 1] = tmp_operand_details;
		}

	}

	return FCML_CEH_GEC_NO_ERROR;
}

fcml_st_dialect *fcml_fn_get_att_dialect_context() {
    return (fcml_st_dialect*)&fcml_dialect_context_att;
}

fcml_ceh_error fcml_fn_init_att_dialect(void) {

	fcml_ceh_error error;

	if( !fcml_map_dialect_att_mnemonics_lookup ) {

		// Prepare mnemonic lookup.
		fcml_map_dialect_att_mnemonics_lookup = fcml_fn_coll_map_alloc( &fcml_coll_map_descriptor_uint32, sizeof( fcml_arr_dialect_att_mnemonics ) / sizeof( fcml_st_dialect_mnemonic ), &error );
		if( error ) {
			return error;
		}

		fcml_st_dialect_mnemonic *current = &(fcml_arr_dialect_att_mnemonics[0]);
		while( current->mnemonic ) {
			fcml_fn_coll_map_put( fcml_map_dialect_att_mnemonics_lookup, &(current->instruction), current, &error );
			if( error ) {
				fcml_fn_coll_map_free( fcml_map_dialect_att_mnemonics_lookup );
				fcml_map_dialect_att_mnemonics_lookup = NULL;
				break;
			}
			current++;
		}

	}

	// Prepares dialect instance.
	fcml_dialect_context_att.get_mnemonic = &fcml_ifn_asm_dialect_get_mnemonic_att;
	fcml_dialect_context_att.render_mnemonic = &fcml_ifn_asm_dialect_render_mnemonic_att;
	fcml_dialect_context_att.get_parsed_mnemonics = &fcml_fn_asm_dialect_get_parsed_mnemonics_att;
	fcml_dialect_context_att.free_mnemonic = &fcml_ifn_asm_dialect_free_mnemonic_att;
	fcml_dialect_context_att.instruction_renderer = &fcml_fn_rend_render_instruction_att;
	fcml_dialect_context_att.instruction_parser = &fcml_x64_att_parse;
	fcml_dialect_context_att.get_register = &fcml_ifn_asm_dialect_get_register_att;
	fcml_dialect_context_att.size_operator_renderer = &fcml_ifn_asm_dialect_render_size_operator_att;
	fcml_dialect_context_att.assembler_preprocessor = &fcml_ifn_asm_dialect_assembler_preprocessor_att;
	fcml_dialect_context_att.disassembler_postprocessor = &fcml_ifn_asm_dialect_disassembler_postprocessor_att;

	return error;
}
