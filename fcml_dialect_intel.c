/*
 * fcml_asm_dialect_intel.c
 *
 *  Created on: 1 wrz 2013
 *      Author: tAs
 */

#include <string.h>
#include <stdio.h>

#include "fcml_dialect_int.h"
#include "fcml_dialect_intel.h"
#include "fcml_mnemonic_parser.h"
#include "fcml_env.h"
#include "fcml_coll.h"
#include "fcml_rend_intel.h"
#include "fcml_x64intel_asm_parser.h"
#include "fcml_common_dialect.h"

// *************
// * MNEMONICS *
// *************

fcml_coll_map *fcml_map_dialect_intel_mnemonics_lookup = NULL;

fcml_st_dialect_mnemonic fcml_arr_dialect_intel_mnemonics[] = {
	{ FCML_TEXT("aaa"), FCML_ASM_DIALECT_INSTRUCTION( F_AAA, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("aad"), FCML_ASM_DIALECT_INSTRUCTION( F_AAD, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("aam"), FCML_ASM_DIALECT_INSTRUCTION( F_AAM, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("aas"), FCML_ASM_DIALECT_INSTRUCTION( F_AAS, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("adc"), FCML_ASM_DIALECT_INSTRUCTION( F_ADC, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("add"), FCML_ASM_DIALECT_INSTRUCTION( F_ADD, FCML_AM_ALL ), 0 },
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
	{ FCML_TEXT("aeskeygenassist"), FCML_ASM_DIALECT_INSTRUCTION( F_AESKEYGENASSIST, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("vaeskeygenassist"), FCML_ASM_DIALECT_INSTRUCTION( F_VAESKEYGENASSIST, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("and"), FCML_ASM_DIALECT_INSTRUCTION( F_AND, FCML_AM_ALL ), 0 },
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
	{ FCML_TEXT("bt"), FCML_ASM_DIALECT_INSTRUCTION( F_BT, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("btc"), FCML_ASM_DIALECT_INSTRUCTION( F_BTC, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("btr"), FCML_ASM_DIALECT_INSTRUCTION( F_BTR, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("bts"), FCML_ASM_DIALECT_INSTRUCTION( F_BTS, FCML_AM_ALL ), 0 },
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
	{ FCML_TEXT("call"), FCML_ASM_DIALECT_INSTRUCTION( F_CALL, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("cbw[ow];cwde[od];cdqe[oq]"), FCML_ASM_DIALECT_INSTRUCTION( F_CBW, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("clc"), FCML_ASM_DIALECT_INSTRUCTION( F_CLC, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("cld"), FCML_ASM_DIALECT_INSTRUCTION( F_CLD, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("clflush"), FCML_ASM_DIALECT_INSTRUCTION( F_CLFLUSH, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("cli"), FCML_ASM_DIALECT_INSTRUCTION( F_CLI, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("clgi"), FCML_ASM_DIALECT_INSTRUCTION( F_CLGI, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("clts"), FCML_ASM_DIALECT_INSTRUCTION( F_CLTS, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("cmc"), FCML_ASM_DIALECT_INSTRUCTION( F_CMC, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("cmov"), FCML_ASM_DIALECT_INSTRUCTION( F_CMOV, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("cmp"), FCML_ASM_DIALECT_INSTRUCTION( F_CMP, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("cmppd"), FCML_ASM_DIALECT_INSTRUCTION( F_CMPPD, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("vcmppd"), FCML_ASM_DIALECT_INSTRUCTION( F_VCMPPD, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("cmpps"), FCML_ASM_DIALECT_INSTRUCTION( F_CMPPS, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("vcmpps"), FCML_ASM_DIALECT_INSTRUCTION( F_VCMPPS, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("cmps;cmpsb[ts]"), FCML_ASM_DIALECT_INSTRUCTION( F_CMPS, FCML_M8_M8 ), 0 },
	{ FCML_TEXT("cmps;cmpsw[ts,ow,a*];cmpsd[ts,od,a*];cmpsq[ts,oq,a*]"), FCML_ASM_DIALECT_INSTRUCTION( F_CMPS, FCML_MO_MO ), 0 },
	{ FCML_TEXT("cmpsd;cmpeqsd[p00];cmpltsd[p01];cmplesd[p02];cmpunordsd[p03];cmpneqsd[p04];cmpnltsd[p05];cmpnlesd[p06];cmpordsd[p07]"), FCML_ASM_DIALECT_INSTRUCTION( F_CMPSD, FCML_RXO_RMX64_OP ), 0 },
	{ FCML_TEXT("vcmpsd;vcmpeqsd[p00];vcmpltsd[p01];vcmplesd[p02];vcmpunordsd[p03];vcmpneqsd[p04];vcmpnltsd[p05];vcmpnlesd[p06];vcmpordsd[p07];vcmpeq_uqsd[p08];vcmpngesd[p09];vcmpngtsd[p0a];vcmpfalsesd[p0b];vcmpneq_oqsd[p0c];vcmpgesd[p0d];vcmpgtsd[p0e];vcmptruesd[p0f];vcmpeq_ossd[p10];vcmplt_oqsd[p11];vcmple_oqsd[p12];vcmpunord_ssd[p13];vcmpneq_ussd[p14];vcmpnlt_uqsd[p15];vcmpnle_uqsd[p16];vcmpord_ssd[p17];vcmpeq_ussd[p18];vcmpnge_uqsd[p19];vcmpngt_uqsd[p1a];vcmpfalse_ossd[p1b];vcmpneq_ossd[p1c];vcmpge_oqsd[p1d];vcmpgt_oqsd[p1e];vcmptrue_ussd[p1f]"), FCML_ASM_DIALECT_INSTRUCTION( F_CMPSD, FCML_RXO_RXO_RMX64_OP ), 0 },
	{ FCML_TEXT("cmpss;cmpeqss[p00];cmpltss[p01];cmpless[p02];cmpunordss[p03];cmpneqss[p04];cmpnltss[p05];cmpnless[p06];cmpordss[p07]"), FCML_ASM_DIALECT_INSTRUCTION( F_CMPSS, FCML_RXO_RMX32_OP ), 0 },
	{ FCML_TEXT("vcmpss;vcmpeqss[p00];vcmpltss[p01];vcmpless[p02];vcmpunordss[p03];vcmpneqss[p04];vcmpnltss[p05];vcmpnless[p06];vcmpordss[p07];vcmpeq_uqss[p08];vcmpngess[p09];vcmpngtss[p0a];vcmpfalsess[p0b];vcmpneq_oqss[p0c];vcmpgess[p0d];vcmpgtss[p0e];vcmptruess[p0f];vcmpeq_osss[p10];vcmplt_oqss[p11];vcmple_oqss[p12];vcmpunord_sss[p13];vcmpneq_usss[p14];vcmpnlt_uqss[p15];vcmpnle_uqss[p16];vcmpord_sss[p17];vcmpeq_usss[p18];vcmpnge_uqss[p19];vcmpngt_uqss[p1a];vcmpfalse_osss[p1b];vcmpneq_osss[p1c];vcmpge_oqss[p1d];vcmpgt_oqss[p1e];vcmptrue_usss[p1f]"), FCML_ASM_DIALECT_INSTRUCTION( F_CMPSS, FCML_RXO_RXO_RMX32_OP ), 0 },
	{ FCML_TEXT("cmpxchg"), FCML_ASM_DIALECT_INSTRUCTION( F_CMPXCHG, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("cmpxchg8b"), FCML_ASM_DIALECT_INSTRUCTION( F_CMPXCHGxB, FCML_M64 ), 0 },
	{ FCML_TEXT("cmpxchg16b"), FCML_ASM_DIALECT_INSTRUCTION( F_CMPXCHGxB, FCML_M128 ), 0 },
	{ FCML_TEXT("cpuid"), FCML_ASM_DIALECT_INSTRUCTION( F_CPUID, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("crc32"), FCML_ASM_DIALECT_INSTRUCTION( F_CRC32, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("cvtdq2pd"), FCML_ASM_DIALECT_INSTRUCTION( F_CVTDQ2PD, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("vcvtdq2pd"), FCML_ASM_DIALECT_INSTRUCTION( F_VCVTDQ2PD, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("cvtdq2ps"), FCML_ASM_DIALECT_INSTRUCTION( F_CVTDQ2PS, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("vcvtdq2ps"), FCML_ASM_DIALECT_INSTRUCTION( F_VCVTDQ2PS, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("cvtpd2dq"), FCML_ASM_DIALECT_INSTRUCTION( F_CVTPD2DQ, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("vcvtpd2dq"), FCML_ASM_DIALECT_INSTRUCTION( F_VCVTPD2DQ, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("cvtpd2pi"), FCML_ASM_DIALECT_INSTRUCTION( F_CVTPD2PI, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("cvtpd2ps"), FCML_ASM_DIALECT_INSTRUCTION( F_CVTPD2PS, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("vcvtpd2ps"), FCML_ASM_DIALECT_INSTRUCTION( F_VCVTPD2PS, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("cvtpi2pd"), FCML_ASM_DIALECT_INSTRUCTION( F_CVTPI2PD, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("cvtpi2ps"), FCML_ASM_DIALECT_INSTRUCTION( F_CVTPI2PS, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("cvtps2dq"), FCML_ASM_DIALECT_INSTRUCTION( F_CVTPS2DQ, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("vcvtps2dq"), FCML_ASM_DIALECT_INSTRUCTION( F_VCVTPS2DQ, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("cvtps2pd"), FCML_ASM_DIALECT_INSTRUCTION( F_CVTPS2PD, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("vcvtps2pd"), FCML_ASM_DIALECT_INSTRUCTION( F_VCVTPS2PD, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("cvtps2pi"), FCML_ASM_DIALECT_INSTRUCTION( F_CVTPS2PI, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("cvtsd2si"), FCML_ASM_DIALECT_INSTRUCTION( F_CVTSD2SI, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("vcvtsd2si"), FCML_ASM_DIALECT_INSTRUCTION( F_VCVTSD2SI, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("cvtsd2ss"), FCML_ASM_DIALECT_INSTRUCTION( F_CVTSD2SS, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("vcvtsd2ss"), FCML_ASM_DIALECT_INSTRUCTION( F_VCVTSD2SS, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("cvtsi2sd"), FCML_ASM_DIALECT_INSTRUCTION( F_CVTSI2SD, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("vcvtsi2sd"), FCML_ASM_DIALECT_INSTRUCTION( F_VCVTSI2SD, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("cvtsi2ss"), FCML_ASM_DIALECT_INSTRUCTION( F_CVTSI2SS, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("vcvtsi2ss"), FCML_ASM_DIALECT_INSTRUCTION( F_VCVTSI2SS, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("cvtss2sd"), FCML_ASM_DIALECT_INSTRUCTION( F_CVTSS2SD, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("vcvtss2sd"), FCML_ASM_DIALECT_INSTRUCTION( F_VCVTSS2SD, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("cvtss2si"), FCML_ASM_DIALECT_INSTRUCTION( F_CVTSS2SI, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("vcvtss2si"), FCML_ASM_DIALECT_INSTRUCTION( F_VCVTSS2SI, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("cvttpd2dq"), FCML_ASM_DIALECT_INSTRUCTION( F_CVTTPD2DQ, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("vcvttpd2dq"), FCML_ASM_DIALECT_INSTRUCTION( F_VCVTTPD2DQ, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("cvttpd2pi"), FCML_ASM_DIALECT_INSTRUCTION( F_CVTTPD2PI, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("cvttps2dq"), FCML_ASM_DIALECT_INSTRUCTION( F_CVTTPS2DQ, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("vcvttps2dq"), FCML_ASM_DIALECT_INSTRUCTION( F_VCVTTPS2DQ, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("cvttps2pi"), FCML_ASM_DIALECT_INSTRUCTION( F_CVTTPS2PI, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("cvttsd2si"), FCML_ASM_DIALECT_INSTRUCTION( F_CVTTSD2SI, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("vcvttsd2si"), FCML_ASM_DIALECT_INSTRUCTION( F_VCVTTSD2SI, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("cvttss2si"), FCML_ASM_DIALECT_INSTRUCTION( F_CVTTSS2SI, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("vcvttss2si"), FCML_ASM_DIALECT_INSTRUCTION( F_VCVTTSS2SI, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("cwd[ow];cdq[od];cqo[oq]"), FCML_ASM_DIALECT_INSTRUCTION( F_CWD, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("comisd"), FCML_ASM_DIALECT_INSTRUCTION( F_COMISD, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("vcomisd"), FCML_ASM_DIALECT_INSTRUCTION( F_VCOMISD, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("comiss"), FCML_ASM_DIALECT_INSTRUCTION( F_COMISS, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("vcomiss"), FCML_ASM_DIALECT_INSTRUCTION( F_VCOMISS, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("daa"), FCML_ASM_DIALECT_INSTRUCTION( F_DAA, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("das"), FCML_ASM_DIALECT_INSTRUCTION( F_DAS, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("dec"), FCML_ASM_DIALECT_INSTRUCTION( F_DEC, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("div"), FCML_ASM_DIALECT_INSTRUCTION( F_DIV, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("divpd"), FCML_ASM_DIALECT_INSTRUCTION( F_DIVPD, FCML_AM_ALL ), 0 },
	{ FCML_TEXT("vdivpd"), FCML_ASM_DIALECT_INSTRUCTION( F_VDIVPD, FCML_AM_ALL ), 0 },
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

fcml_st_dialect_context_int fcml_dialect_context_intel;

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


void fcml_fn_intel_dialect_free(void) {
	if( fcml_map_dialect_intel_mnemonics_lookup ) {
		fcml_fn_coll_map_free( fcml_map_dialect_intel_mnemonics_lookup );
		fcml_map_dialect_intel_mnemonics_lookup = NULL;
	}
}

fcml_ceh_error fcml_fnp_asm_dialect_get_register_intel( const fcml_st_register *reg, fcml_string buffer, fcml_int buffer_length, fcml_bool is_rex) {
	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
	fcml_string printable_reg;
	error = fcml_fn_cmn_dialect_get_register( reg, &printable_reg, is_rex );
	if( error ) {
		return error;
	}
	fcml_fn_env_str_strncpy( buffer, printable_reg, buffer_length );
	return error;
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
		FCML_ASM_DIALECT_INSTRUCTION( instruction->instruction, FCML_AM_ALL )
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

	fcml_dialect_context_intel.get_mnemonic = &fcml_fnp_asm_dialect_get_mnemonic_intel;
	fcml_dialect_context_intel.render_mnemonic = &fcml_fnp_asm_dialect_render_mnemonic_intel;
	fcml_dialect_context_intel.get_parsed_mnemonics = &fcml_fn_asm_dialect_get_parsed_mnemonics_intel;
	fcml_dialect_context_intel.free_mnemonic = &fcml_fnp_asm_dialect_free_mnemonic_intel;
	fcml_dialect_context_intel.instruction_renderer = &fcml_fn_rend_render_instruction_intel;
	fcml_dialect_context_intel.instruction_parser = &fcml_x64intel_parse;
	fcml_dialect_context_intel.get_register = &fcml_fnp_asm_dialect_get_register_intel;
	fcml_dialect_context_intel.size_operator_renderer = &fcml_fnp_asm_dialect_render_size_operator_intel;
	fcml_dialect_context_intel.assembler_preprocessor = NULL;
	fcml_dialect_context_intel.disassembler_postprocessor = NULL;

	return error;
}

fcml_st_dialect *fcml_fn_get_intel_dialect_context() {
    return (fcml_st_dialect*)&fcml_dialect_context_intel;
}
