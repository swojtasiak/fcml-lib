/*
 * ira_def.h
 *
 *  Created on: 27-12-2012
 *      Author: Slawomir Wojtasiak
 */

#ifndef FCML_DEF_H_
#define FCML_DEF_H_

#include "fcml_types.h"
#include "fcml_common.h"
#include "fcml_ceh.h"

/* Constants used to encode operand size on one byte. Used only in instruction descriptions. */

/* Take into account that every size is given in a number of bytes. */
#define FCML_EOS_UNDEFINED	0
#define FCML_EOS_512B		FCML_EOS_UNDEFINED
#define FCML_EOS_BYTE		1
#define FCML_EOS_WORD		2
#define FCML_EOS_DWORD		4
#define FCML_EOS_FWORD		6
#define FCML_EOS_QWORD		8
#define FCML_EOS_MWORD      8
#define FCML_EOS_TBYTE		10
#define FCML_EOS_OWORD		16
#define FCML_EOS_XWORD      16
#define FCML_EOS_YWORD		32

/* Dynamic encoded operand sizes calculated at runtime. */

#define FCML_EOS_DYNAMIC_BASE	0x70
#define FCML_EOS_OPT			0x80

/* Operand size calculated by Effective Operand Size Attribute and Effective Address Size Attribute. */
#define FCML_EOS_EOSA			0x7F
#define FCML_EOS_EASA			0x7E

/* Operand size calculated on L field. */
#define FCML_EOS_L				0x7D

/* Operand sizes that cannot be simply written as number of bytes.*/
#define FCML_EOS_14_28			0x7C
#define FCML_EOS_94_108			0x7B
#define FCML_EOS_32_64			0x7A

/* Far pointer indirect.*/
#define FCML_EOS_FPI			0x79

/* Far pointer.*/
#define FCML_EOS_FP				0x78

/* True if encoded operand size is a dynamic one.*/
#define FCML_IS_EOS_DYNAMIC(x)	( ( x & 0x40 ) != 0 )
#define FCML_IS_EOS_OPT(x)		( ( x & 0x80 ) != 0 )
#define FCML_GET_OS(x)			( ( x ) & ~FCML_EOS_OPT )

/* Instruction and addressing mode types. */

typedef enum fcml_en_def_instruction_type {
    /* Intel IA.*/
    FCML_EN_IT_IA
} fcml_en_def_instruction_type;

/****************/
/* Instructions */
/****************/

/* Multi instructions. */
#define FCML_MI_AMD3DNOW		0x0001

enum fcml_en_instruction_codes {
    F_UNKNOWN,
    F_AAA,
    F_JCC,
    F_AAD,
    F_AAM,
    F_AAS,
    F_ADC,
    F_ADD,
    F_ADDPD,
    F_VADDPD,
    F_ADDPS,
    F_VADDPS,
    F_ADDSD,
    F_VADDSD,
    F_ADDSS,
    F_VADDSS,
    F_ADDSUBPD,
    F_VADDSUBPD,
    F_ADDSUBPS,
    F_VADDSUBPS,
    F_AESDEC,
    F_VAESDEC,
    F_AESDECLAST,
    F_VAESDECLAST,
    F_AESENC,
    F_VAESENC,
    F_AESENCLAST,
    F_VAESENCLAST,
    F_AESIMC,
    F_VAESIMC,
    F_AESKEYGENASSIST,
    F_VAESKEYGENASSIST,
    F_AND,
    F_ANDPD,
    F_VANDPD,
    F_ANDPS,
    F_VANDPS,
    F_ANDNPD,
    F_VANDNPD,
    F_ANDNPS,
    F_VANDNPS,
    F_ARPL,
    F_ANDN,
    F_ADCX,
    F_ADOX,
    F_BLENDPD,
    F_VBLENDPD,
    F_BLENDPS,
    F_VBLENDPS,
    F_BLENDVPD,
    F_VBLENDVPD,
    F_BLENDVPS,
    F_VBLENDVPS,
    F_BOUND,
    F_BSF,
    F_BSR,
    F_BSWAP,
    F_BT,
    F_BTC,
    F_BTR,
    F_BTS,
    F_BEXR,
    F_BLCFILL,
    F_BLCI,
    F_BLCIC,
    F_BLCMSK,
    F_BLCS,
    F_BLSFILL,
    F_BLSI,
    F_BLSIC,
    F_BLSMSK,
    F_BLSR,
    F_BZHI,
    F_CALL,
    F_CBW,
    F_CWDE = F_CBW,
    F_CDQE = F_CBW,
    F_CLC,
    F_CLD,
    F_CLFLUSH,
    F_CLI,
    F_CLGI,
    F_CLTS,
    F_CMC,
    F_CMOV,
    F_CMP,
    F_CMPPD,
    F_VCMPPD,
    F_CMPPS,
    F_VCMPPS,
    F_CMPS,
    F_CMPSD,
    F_VCMPSD,
    F_CMPSS,
    F_VCMPSS,
    F_CMPXCHG,
    F_CMPXCHGxB,
    F_CPUID,
    F_CRC32,
    F_CVTDQ2PD,
    F_VCVTDQ2PD,
    F_CVTDQ2PS,
    F_VCVTDQ2PS,
    F_CVTPD2DQ,
    F_VCVTPD2DQ,
    F_CVTPD2PI,
    F_CVTPD2PS,
    F_VCVTPD2PS,
    F_CVTPI2PD,
    F_CVTPI2PS,
    F_CVTPS2DQ,
    F_VCVTPS2DQ,
    F_CVTPS2PD,
    F_VCVTPS2PD,
    F_CVTPS2PI,
    F_CVTSD2SI,
    F_VCVTSD2SI,
    F_CVTSD2SS,
    F_VCVTSD2SS,
    F_CVTSI2SD,
    F_VCVTSI2SD,
    F_CVTSI2SS,
    F_VCVTSI2SS,
    F_CVTSS2SD,
    F_VCVTSS2SD,
    F_CVTSS2SI,
    F_VCVTSS2SI,
    F_CVTTPD2DQ,
    F_VCVTTPD2DQ,
    F_CVTTPD2PI,
    F_CVTTPS2DQ,
    F_VCVTTPS2DQ,
    F_CVTTPS2PI,
    F_CVTTSD2SI,
    F_VCVTTSD2SI,
    F_CVTTSS2SI,
    F_VCVTTSS2SI,
    F_CWD,
    F_CDQ = F_CWD,
    F_CQO = F_CWD,
    F_COMISD,
    F_VCOMISD,
    F_COMISS,
    F_VCOMISS,
    F_DAA,
    F_DAS,
    F_DEC,
    F_DIV,
    F_DIVPD,
    F_VDIVPD,
    F_DIVPS,
    F_VDIVPS,
    F_DIVSD,
    F_VDIVSD,
    F_DIVSS,
    F_VDIVSS,
    F_DPPD,
    F_VDPPD,
    F_DPPS,
    F_VDPPS,
    F_EMMS,
    F_ENTER,
    F_EXTRACTPS,
    F_VEXTRACTPS,
    F_EXTRQ,
    F_F2XM1,
    F_FABS,
    F_FADD,
    F_FIADD,
    F_FADDP,
    F_FBLD,
    F_FBSTP,
    F_FCHS,
    F_FCLEX,
    F_FNCLEX,
    F_FCMOVB,
    F_FCMOVE,
    F_FCMOVBE,
    F_FCMOVU,
    F_FCMOVNB,
    F_FCMOVNE,
    F_FCMOVNBE,
    F_FCMOVNU,
    F_FCOS,
    F_FCOM,
    F_FCOMP,
    F_FCOMPP,
    F_FCOMI,
    F_FCOMIP,
    F_FUCOMI,
    F_FUCOMIP,
    F_FDECSTP,
    F_FDIV,
    F_FDIVP,
    F_FIDIV,
    F_FDIVR,
    F_FDIVRP,
    F_FIDIVR,
    F_FFREE,
    F_FICOM,
    F_FICOMP,
    F_FILD,
    F_FINCSTP,
    F_FINIT,
    F_FNINIT,
    F_FIST,
    F_FISTP,
    F_FLD,
    F_FLD1,
    F_FLDL2T,
    F_FLDL2E,
    F_FLDPI,
    F_FLDLG2,
    F_FLDLN2,
    F_FLDZ,
    F_FLDCW,
    F_FLDENV,
    F_FMUL,
    F_FMULP,
    F_FIMUL,
    F_FNOP,
    F_FPATAN,
    F_FPREM,
    F_FPREM1,
    F_FPTAN,
    F_FRNDINT,
    F_FRSTOR,
    F_FSAVE,
    F_FNSAVE,
    F_FSCALE,
    F_FSIN,
    F_FSINCOS,
    F_FSQRT,
    F_FST,
    F_FSTP,
    F_FSTCW,
    F_FNSTCW,
    F_FSTENV,
    F_FNSTENV,
    F_FSTSW,
    F_FNSTSW,
    F_FSUB,
    F_FSUBP,
    F_FISUB,
    F_FSUBR,
    F_FSUBRP,
    F_FISUBR,
    F_FTST,
    F_FUCOM,
    F_FUCOMP,
    F_FUCOMPP,
    F_FXAM,
    F_FXCH,
    F_FXRSTOR,
    F_FXRSTOR64,
    F_FXSAVE,
    F_FXSAVE64,
    F_FXTRACT,
    F_FYL2X,
    F_FYL2XP1,
    F_FEMMS,
    F_FISTTP,
    F_GETSEC,
    F_HADDPD,
    F_VHADDPD,
    F_HADDPS,
    F_VHADDPS,
    F_HLT,
    F_HSUBPD,
    F_VHSUBPD,
    F_HSUBPS,
    F_VHSUBPS,
    F_INVEPT,
    F_INVVPID,
    F_IDIV,
    F_IMUL,
    F_IN,
    F_INC,
    F_INS,
    F_INSERTPS,
    F_VINSERTPS,
    F_VEXTRACTF128,
    F_VINSERTF128,
    F_INSERTQ,
    F_INT3,
    F_INT,
    F_INTO,
    F_INVD,
    F_INVLPG,
    F_INVLPGA,
    F_INVPCID,
    F_IRET,
    F_JCXZ,
    F_JECXZ = F_JCXZ,
    F_JRCXZ = F_JCXZ,
    F_JMP,
    F_LAR,
    F_LAHF,
    F_LDDQU,
    F_VLDDQU,
    F_LDMXCSR,
    F_VLDMXCSR,
    F_LDS,
    F_LSS,
    F_LES,
    F_LFS,
    F_LGS,
    F_LEA,
    F_LEAVE,
    F_LFENCE,
    F_LLWPCB,
    F_LGDT,
    F_LIDT,
    F_LLDT,
    F_LMSW,
    F_LODS,
    F_LOOP,
    F_LOOPE,
    F_LOOPNE,
    F_LWPINS,
    F_LWPVAL,
    F_LSL,
    F_LTR,
    F_LZCNT,
    F_MASKMOVDQU,
    F_VMASKMOVDQU,
    F_MASKMOVQ,
    F_VMASKMOVPS,
    F_VMASKMOVPD,
    F_VPMASKMOVD,
    F_VPMASKMOV,
    F_VPMASKMOVQ,
    F_MAXPD,
    F_VMAXPD,
    F_MAXPS,
    F_VMAXPS,
    F_MAXSD,
    F_VMAXSD,
    F_MAXSS,
    F_VMAXSS,
    F_MFENCE,
    F_MINPD,
    F_VMINPD,
    F_MINPS,
    F_VMINPS,
    F_MINSD,
    F_VMINSD,
    F_MINSS,
    F_VMINSS,
    F_MONITOR,
    F_MOVAPD,
    F_VMOVAPD,
    F_MOVAPS,
    F_VMOVAPS,
    F_MOVBE,
    F_MOV,
    F_MOVD,
    F_VMOVD,
    F_MOVQ,
    F_VMOVQ,
    F_MOVDDUP,
    F_VMOVDDUP,
    F_MOVDQA,
    F_VMOVDQA,
    F_MOVDQU,
    F_VMOVDQU,
    F_MOVDQ2Q,
    F_MOVHLPS,
    F_VMOVHLPS,
    F_MOVHPD,
    F_VMOVHPD,
    F_MOVHPS,
    F_VMOVHPS,
    F_MOVLHPS,
    F_VMOVLHPS,
    F_MOVLPD,
    F_VMOVLPD,
    F_MOVLPS,
    F_VMOVLPS,
    F_MOVMSKPD,
    F_VMOVMSKPD,
    F_MOVMSKPS,
    F_VMOVMSKPS,
    F_MOVNTDQA,
    F_VMOVNTDQA,
    F_MOVNTDQ,
    F_VMOVNTDQ,
    F_MOVS,
    F_MOVNTI,
    F_MOVNTPD,
    F_VMOVNTPD,
    F_MOVNTPS,
    F_VMOVNTPS,
    F_MOVNTSD,
    F_MOVNTSS,
    F_MOVNTQ,
    F_MOVQ2DQ,
    F_MOVSD,
    F_VMOVSD,
    F_MOVSHDUP,
    F_VMOVSHDUP,
    F_MOVSLDUP,
    F_VMOVSLDUP,
    F_MOVSS,
    F_VMOVSS,
    F_MOVSX,
    F_MOVSXD,
    F_MOVUPD,
    F_VMOVUPD,
    F_MOVUPS,
    F_VMOVUPS,
    F_MOVZX,
    F_MPSADBW,
    F_VMPSADBW,
    F_MUL,
    F_MULPD,
    F_VMULPD,
    F_MULPS,
    F_VMULPS,
    F_MULSD,
    F_VMULSD,
    F_MULSS,
    F_VMULSS,
    F_MWAIT,
    F_NEG,
    F_NOP,
    F_NOT,
    F_OR,
    F_ORPD,
    F_VORPD,
    F_ORPS,
    F_VORPS,
    F_OUT,
    F_OUTS,
    F_PABSW,
    F_PABSB,
    F_PABSD,
    F_VPABSB,
    F_VPABSW,
    F_VPABSD,
    F_VPACKSSWB,
    F_PACKSSWB,
    F_VPACKSSDW,
    F_PACKSSDW,
    F_PACKUSDW,
    F_VPACKUSDW,
    F_PACKUSWB,
    F_VPACKUSWB,
    F_VPADDW,
    F_PADDW,
    F_VPADDB,
    F_VPADDD,
    F_PADDB,
    F_PADDD,
    F_VPADDSW,
    F_PADDSB,
    F_PADDSW,
    F_VPADDSB,
    F_PADDUSW,
    F_PADDUSB,
    F_VPADDUSW,
    F_PADDQ,
    F_VPADDUSB,
    F_VPADDQ,
    F_POP,
    F_PUSH,
    /* TODO: Opisac konflikt nazewnictwa pomiedzy GAS i Intel, inne kodowanie a ta sama mnemonika :/ byc moze uda sie zrobic z tego jedna instukcje.*/
    F_POPA,
    F_POPAD,
    F_POPF,
    F_POPFQ,
    F_POPFD,
    F_PUSHA,
    F_PUSHF,
    F_PUSHAD,
    F_PUSHFQ,
    F_PUSHFD,
    F_PAVGUSB,
    F_PF2ID,
    F_PFACC,
    F_PFADD,
    F_PFCMPEQ,
    F_PFCMPGE,
    F_PFCMPGT,
    F_PFMAX,
    F_PFMIN,
    F_PFMUL,
    F_PFRCP,
    F_PFRCPIT1,
    F_PFRCPIT2,
    F_PFRSQIT1,
    F_PFRSQRT,
    F_PFSUB,
    F_PFSUBR,
    F_PI2FD,
    F_PMULHRW,
    F_PF2IW,
    F_PFNACC,
    F_PFPNACC,
    F_PI2FW,
    F_PSWAPD,
    F_PALIGNR,
    F_VPALIGNR,
    F_PAND,
    F_VPAND,
    F_PANDN,
    F_VPANDN,
    F_PAUSE,
    F_PAVGW,
    F_PAVGB,
    F_VPAVGW,
    F_VPAVGB,
    F_PBLENDVB,
    F_VPBLENDVB,
    F_PBLENDW,
    F_VPBLENDW,
    F_VPBLENDD,
    F_PCLMULQDQ,
    F_VPCLMULQDQ,
    F_PCMPEQW,
    F_PCMPEQB,
    F_PCMPEQD,
    F_VPCMPEQD,
    F_VPCMPEQW,
    F_VPCMPEQB,
    F_PCMPEQQ,
    F_VPCMPEQQ,
    F_PCMPESTRI,
    F_VPCMPESTRI,
    F_PCMPESTRM,
    F_VPCMPESTRM,
    F_PCMPGTW,
    F_PCMPGTD,
    F_PCMPGTB,
    F_VPCMPGTW,
    F_VPCMPGTD,
    F_VPCMPGTB,
    F_PCMPGTQ,
    F_VPCMPGTQ,
    F_PCMPISTRI,
    F_VPCMPISTRI,
    F_PCMPISTRM,
    F_VPCMPISTRM,
    F_VPEXTRB,
    F_VPEXTRQ,
    F_PEXTRQ,
    F_PEXTRB,
    F_PEXTRD,
    F_VPEXTRD,
    F_PEXTRW,
    F_VPEXTRW,
    F_VPHADDW,
    F_VPHADDD,
    F_PHADDD,
    F_PHADDW,
    F_PHADDSW,
    F_VPHADDSW,
    F_PHMINPOSUW,
    F_VPHMINPOSUW,
    F_PHSUBD,
    F_PHSUBW,
    F_VPHSUBD,
    F_VPHSUBW,
    F_PHSUBSW,
    F_VPHSUBSW,
    F_PINSRD,
    F_VPINSRQ,
    F_PINSRQ,
    F_PINSRB,
    F_VPINSRD,
    F_VPINSRB,
    F_PINSRW,
    F_VPINSRW,
    F_PMADDUBSW,
    F_VPMADDUBSW,
    F_PMADDWD,
    F_VPMADDWD,
    F_PMAXSB,
    F_VPMAXSB,
    F_PMAXSD,
    F_VPMAXSD,
    F_PMAXSW,
    F_VPMAXSW,
    F_PMAXUB,
    F_VPMAXUB,
    F_PMAXUD,
    F_VPMAXUD,
    F_PMAXUW,
    F_VPMAXUW,
    F_PMINSB,
    F_VPMINSB,
    F_PMINSD,
    F_VPMINSD,
    F_PMINSW,
    F_VPMINSW,
    F_PMINUW,
    F_VPMINUW,
    F_PMINUB,
    F_VPMINUB,
    F_PMINUD,
    F_VPMINUD,
    F_PMOVMSKB,
    F_VPMOVMSKB,
    F_VPMOVSXBQ,
    F_PMOVSXBW,
    F_PMOVSXWQ,
    F_VPMOVSXWQ,
    F_PMOVSXWD,
    F_PMOVSXBD,
    F_VPMOVSXDQ,
    F_VPMOVSXWD,
    F_PMOVSXBQ,
    F_VPMOVSXBW,
    F_PMOVSXDQ,
    F_VPMOVSXBD,
    F_PMOVZXWD,
    F_PMOVZXDQ,
    F_VPMOVZXDQ,
    F_PMOVZXWQ,
    F_VPMOVZXBQ,
    F_PMOVZXBQ,
    F_VPMOVZXWD,
    F_VPMOVZXBD,
    F_VPMOVZXWQ,
    F_PMOVZXBD,
    F_VPMOVZXBW,
    F_PMOVZXBW,
    F_PMULDQ,
    F_PMULHRSW,
    F_PMULHUW,
    F_VPMULDQ,
    F_VPMULHRSW,
    F_VPMULHUW,
    F_PMULHW,
    F_VPMULHW,
    F_PMULUDQ,
    F_VPMULUDQ,
    F_PMULLW,
    F_PMULLD,
    F_VPMULLD,
    F_VPMULLW,
    F_POPCNT,
    F_POR,
    F_VPOR,
    F_PREFETCHT2,
    F_PREFETCHW,
    F_PREFETCHT1,
    F_PREFETCHNTA,
    F_PREFETCHT0,
    F_PSADBW,
    F_VPSADBW,
    F_PSHUFB,
    F_PSHUFD,
    F_PSHUFHW,
    F_VPSHUFD,
    F_VPSHUFB,
    F_PSHUFLW,
    F_PSHUFW,
    F_VPSHUFLW,
    F_VPSHUFHW,
    F_VPSIGNB,
    F_VPSIGND,
    F_PSIGNW,
    F_PSIGNB,
    F_VPSIGNW,
    F_PSIGND,
    F_PSLLDQ,
    F_VPSLLDQ,
    F_PSLLQ,
    F_PSLLD,
    F_VPSLLW,
    F_VPSLLQ,
    F_PSLLW,
    F_VPSLLD,
    F_VPSRAW,
    F_PSRAD,
    F_PSRAW,
    F_VPSRAD,
    F_PSRLDQ,
    F_VPSRLDQ,
    F_VPSRLQ,
    F_PSRLQ,
    F_PSRLD,
    F_PSRLW,
    F_VPSRLD,
    F_VPSRLW,
    F_VPSUBD,
    F_PSUBD,
    F_PSUBW,
    F_VPSUBB,
    F_VPSUBQ,
    F_PSUBB,
    F_VPSUBW,
    F_PSUBQ,
    F_PSUBSB,
    F_VPSUBSW,
    F_VPSUBSB,
    F_PSUBSW,
    F_VPSUBUSW,
    F_VPSUBUSB,
    F_PSUBUSB,
    F_PSUBUSW,
    F_VPTEST,
    F_PTEST,
    F_PUNPCKLBW,
    F_PUNPCKLQDQ,
    F_VPUNPCKLWD,
    F_VPUNPCKLQDQ,
    F_VPUNPCKLBW,
    F_PUNPCKLWD,
    F_PUNPCKLDQ,
    F_VPUNPCKLDQ,
    F_VPUNPCKHWD,
    F_PUNPCKHDQ,
    F_PUNPCKHWD,
    F_PUNPCKHQDQ,
    F_VPUNPCKHQDQ,
    F_VPUNPCKHBW,
    F_PUNPCKHBW,
    F_VPUNPCKHDQ,
    F_PXOR,
    F_VPXOR,
    F_PREFETCH,
    F_RCL,
    F_RCR,
    F_ROL,
    F_ROR,
    F_RET,
    F_RETF,
    F_RCPPS,
    F_VRCPPS,
    F_RCPSS,
    F_VRCPSS,
    F_RDFSBASE,
    F_RDGSBASE,
    F_RDRAND,
    F_RDTSCP,
    F_RDTSC,
    F_RDPMC,
    F_RDMSR,
    F_ROUNDPD,
    F_VROUNDPD,
    F_ROUNDPS,
    F_VROUNDPS,
    F_ROUNDSD,
    F_VROUNDSD,
    F_ROUNDSS,
    F_VROUNDSS,
    F_RSM,
    F_RSQRTPS,
    F_VRSQRTPS,
    F_RSQRTSS,
    F_VRSQRTSS,
    F_SAHF,
    F_SAR,
    F_SAL,
    F_SHL = F_SAL,
    F_SHR,
    F_SBB,
    F_SCAS,
    F_SET,
    F_STOS,
    F_SUB,
    F_SFENCE,
    F_SGDT,
    F_SHLD,
    F_SHRD,
    F_SKINIT,
    F_SLWPCB,
    F_SHUFPD,
    F_VSHUFPD,
    F_SHUFPS,
    F_VSHUFPS,
    F_SIDT,
    F_SLDT,
    F_SMSW,
    F_SQRTPD,
    F_VSQRTPD,
    F_SQRTPS,
    F_VSQRTPS,
    F_SQRTSD,
    F_VSQRTSD,
    F_SQRTSS,
    F_VSQRTSS,
    F_STC,
    F_STD,
    F_STGI,
    F_STI,
    F_STMXCSR,
    F_VSTMXCSR,
    F_STR,
    F_SUBPD,
    F_VSUBPD,
    F_SUBPS,
    F_VSUBPS,
    F_SUBSD,
    F_VSUBSD,
    F_SUBSS,
    F_VSUBSS,
    F_SWAPGS,
    F_SYSCALL,
    F_SYSENTER,
    F_SYSEXIT,
    F_SYSRET,
    F_TEST,
    F_T1MSKC,
    F_UCOMISD,
    F_VUCOMISD,
    F_UCOMISS,
    F_VUCOMISS,
    F_UD2,
    F_UNPCKHPD,
    F_VUNPCKHPD,
    F_UNPCKHPS,
    F_VUNPCKHPS,
    F_UNPCKLPD,
    F_VUNPCKLPD,
    F_UNPCKLPS,
    F_VUNPCKLPS,
    F_VMLOAD,
    F_VMRUN,
    F_VMSAVE,
    F_VFRCZPD,
    F_VFRCZPS,
    F_VFRCZSD,
    F_VFRCZSS,
    F_VPCMOV,
    F_VPERMIL2PD,
    F_VPERMIL2PS,
    F_VPHADDBD,
    F_VPHADDBW,
    F_VPHADDBQ,
    F_VPHADDDQ,
    F_VPHADDUBD,
    F_VPHADDUBQ,
    F_VPHADDUBW,
    F_VPHADDUDQ,
    F_VPHADDUWD,
    F_VPHADDUWQ,
    F_VPHADDWD,
    F_VPHADDWQ,
    F_VPHSUBBW,
    F_VPHSUBDQ,
    F_VPHSUBWD,
    F_VPMACSDD,
    F_VPMACSDQH,
    F_VPMACSDQL,
    F_VPMACSSDD,
    F_VPMACSSDQH,
    F_VPMACSSDQL,
    F_VPMACSSWD,
    F_VPMACSSWW,
    F_VPMACSWD,
    F_VPMACSWW,
    F_VPMADCSSWD,
    F_VPMADCSWD,
    F_VPPERM,
    F_VPROTD,
    F_VPROTB,
    F_VPROTQ,
    F_VPROTW,
    F_VPSHAB,
    F_VPSHAD,
    F_VPSHAQ,
    F_VPSHAW,
    F_VPSHLB,
    F_VPSHLD,
    F_VPSHLQ,
    F_VPSHLW,
    F_VFMADD213PD,
    F_VFMADDPD,
    F_VFMADD132PD,
    F_VFMADD231PD,
    F_VFMADDPS,
    F_VFMADD231PS,
    F_VFMADD132PS,
    F_VFMADD213PS,
    F_VFMADD132SD,
    F_VFMADD213SD,
    F_VFMADDSD,
    F_VFMADD231SD,
    F_VFMADD132SS,
    F_VFMADD213SS,
    F_VFMADDSS,
    F_VFMADD231SS,
    F_VFMADDSUB132PD,
    F_VFMADDSUB213PD,
    F_VFMADDSUBPD,
    F_VFMADDSUB231PD,
    F_VFMADDSUB231PS,
    F_VFMADDSUBPS,
    F_VFMADDSUB132PS,
    F_VFMADDSUB213PS,
    F_VFMSUBADDPD,
    F_VFMSUBADD213PD,
    F_VFMSUBADD132PD,
    F_VFMSUBADD231PD,
    F_VFMSUBADDPS,
    F_VFMSUBADD213PS,
    F_VFMSUBADD132PS,
    F_VFMSUBADD231PS,
    F_VFMSUB213PD,
    F_VFMSUBPD,
    F_VFMSUB132PD,
    F_VFMSUB231PD,
    F_VFMSUB213PS,
    F_VFMSUBPS,
    F_VFMSUB132PS,
    F_VFMSUB231PS,
    F_VFMSUBSD,
    F_VFMSUB231SD,
    F_VFMSUB132SD,
    F_VFMSUB213SD,
    F_VFMSUB231SS,
    F_VFMSUB213SS,
    F_VFMSUB132SS,
    F_VFMSUBSS,
    F_VFNMADD231PD,
    F_VFNMADDPD,
    F_VFNMADD132PD,
    F_VFNMADD213PD,
    F_VFNMADD231PS,
    F_VFNMADD132PS,
    F_VFNMADD213PS,
    F_VFNMADDPS,
    F_VFNMADD213SD,
    F_VFNMADDSD,
    F_VFNMADD231SD,
    F_VFNMADD132SD,
    F_VFNMADD213SS,
    F_VFNMADDSS,
    F_VFNMADD231SS,
    F_VFNMADD132SS,
    F_VFNMSUB132PD,
    F_VFNMSUB213PD,
    F_VFNMSUB231PD,
    F_VFNMSUBPD,
    F_VFNMSUBPS,
    F_VFNMSUB213PS,
    F_VFNMSUB132PS,
    F_VFNMSUB231PS,
    F_VFNMSUBSD,
    F_VFNMSUB231SD,
    F_VFNMSUB213SD,
    F_VFNMSUB132SD,
    F_VFNMSUBSS,
    F_VFNMSUB132SS,
    F_VFNMSUB213SS,
    F_VFNMSUB231SS,
    F_BEXTR,
    F_VPBROADCASTW,
    F_VPBROADCASTB,
    F_VPBROADCASTD,
    F_VPBROADCASTQ,
    F_VMPTRLD,
    F_VMPTRST,
    F_VMCLEAR,
    F_VMREAD,
    F_VMWRITE,
    F_VMLAUNCH,
    F_VMRESUME,
    F_VMXOFF,
    F_VMXON,
    F_VMCALL,
    F_VMFUNC,
    F_VBROADCASTSD,
    F_VBROADCASTSS,
    F_VBROADCASTI128,
    F_VBROADCASTF128,
    F_VCVTPH2PS,
    F_VCVTPS2PH,
    F_VERR,
    F_VERW,
    F_VMMCALL,
    F_VPERMILPD,
    F_VPERMILPS,
    F_VPSLLVQ,
    F_VPERM2F128,
    F_VPERM2I128,
    F_VEXTRACTI128,
    F_VINSERTI128,
    F_VPSRAVD,
    F_VPERMD,
    F_VPSLLVD,
    F_VPSRLVD,
    F_VPSRLVQ,
    F_VPERMPD,
    F_VPERMQ,
    F_VPERMPS,
    F_VTESTPS,
    F_VTESTPD,
    F_VGATHERDPD,
    F_VGATHERQPD,
    F_VGATHERDPS,
    F_VGATHERQPS,
    F_VPGATHERDD,
    F_VPGATHERQD,
    F_VPGATHERDQ,
    F_VPGATHERQQ,
    F_VZEROALL,
    F_VZEROUPPER,
    F_VPCOMB,
    F_VPCOMW,
    F_VPCOMD,
    F_VPCOMQ,
    F_VPCOMUB,
    F_VPCOMUW,
    F_VPCOMUD,
    F_VPCOMUQ,
    F_WAIT,
    F_FWAIT = F_WAIT,
    F_WBINVD,
    F_WRFSBASE,
    F_WRGSBASE,
    F_WRMSR,
    F_XLAT,
    F_XOR,
    F_XADD,
    F_XCHG,
    F_XGETBV,
    F_XORPD,
    F_VXORPD,
    F_XORPS,
    F_VXORPS,
    F_XRSTOR,
    F_XRSTOR64,
    F_XSAVE,
    F_XSAVE64,
    F_XSAVEOPT,
    F_XSAVEOPT64,
    F_XSETBV,
    F_MULX,
    F_PDEP,
    F_PEXT,
    F_RORX,
    F_SHLX,
    F_SHRX,
    F_SARX,
    F_TZCNT,
    F_TZMSK,
    F_XABORT,
    F_XBEGIN,
    F_XEND,
    F_XTEST,
    F_RDSEED,
    F_CLAC,
    F_STAC
};

/*******************/
/* Addressing mode */
/*******************/

/* Wild card for mnemonic used by default.*/
#define FCML_AM_ALL		0

enum fcml_en_instruction_addr_mode_codes {
    FCML_AM_UNKNOWN = 0, FCML_AM_NO_OPERANS,
    /* IMM*/
    FCML_AM_IMM8,
    FCML_AM_IMMO,
    /* REG, IMM*/
    FCML_AM_ER8_IMM8,
    FCML_AM_R8_IMM8,
    FCML_AM_ERO_IMMO,
    /* RM, IMM*/
    FCML_AM_RM8_IMM8,
    FCML_AM_RMO_IMMO,
    FCML_AM_R0_IMM0,
    FCML_AM_RMO_IMM8,
    /* RM, R / R, RM*/
    FCML_AM_RM8_R8,
    FCML_AM_R8_RM8,
    FCML_AM_R8_MOFF8,
    FCML_AM_MOFF8_R8,
    FCML_AM_R16_RM8,
    FCML_AM_RO_RM16,
    FCML_AM_RMO_RO,
    FCML_AM_RO_RMO,
    FCML_AM_RO_MOFFO,
    FCML_AM_RO_MO,
    FCML_AM_MOFFO_RO,
    FCML_AM_MO_RO,
    FCML_AM_RO_RM8,

    FCML_AM_RM_SR,
    FCML_AM_SR_RM,
    FCML_AM_R32_DR,
    FCML_AM_R64_DR,
    FCML_AM_DR_R32,
    FCML_AM_DR_R64,
    FCML_AM_R32_CR,
    FCML_AM_R64_CR,
    FCML_AM_CR_R32,
    FCML_AM_CR_R64,

    FCML_AM_RO_RMO_IMM8,
    FCML_AM_RO_RMO_IMMO,

    /**/
    R32A_RM32_R32B,
    R64A_RM64_R64B,
    FCML_R32_RM32,
    FCML_R64_RM64,
    FCML_R32_RM32_R32,
    FCML_R64_RM64_R64,
    FCML_REL16,
    FCML_PTR16_O,
    FCML_M16_O,
    FCML_M8_M8,
    FCML_MO_MO,
    FCML_M8,
    FCML_M16,
    FCML_M32,
    FCML_M64,
    FCML_M80,
    FCML_M128,
    FCML_RX_RM32,
    FCML_RX_RM64,
    FCML_RX_RX_RM32,
    FCML_RX_RX_RM64,
    FCML_R32_RXM64,
    FCML_R64_RXM64,
    FCML_RM8,
    FCML_RMO,
    FCML_RO,
    FCML_SRO,
    FCML_SR_FSGSO,
    FCML_ST0_ST,
    FCML_ST_ST0,
    FCML_ST,
    FCML_M2BYTE,
    FCML_AX,
    FCML_R64_M128,
    FCML_R32_M128,
    FCML_RX_RX_I8_I8,
    FCML_RX_RX,
    FCML_REL8,
    FCML_REL0
};

/*********************************************/
/* Instruction groups.                       */
/* Bit fields are not compatible with CPUID. */
/*********************************************/

#define    FCML_AMT_UNDEF      0x0000000000000000UL
/* Grouping.*/
#define    FCML_AMT_SSEx       0x0000000000000001UL
#define    FCML_AMT_VEXx       0x0000000000000002UL
#define    FCML_AMT_SIMD       0x0000000000000004UL
/* CPUID.*/
#define    FCML_AMT_GPI        0x0000000000000008UL
#define    FCML_AMT_FPU        0x0000000000000010UL
#define    FCML_AMT_MMX        0x0000000000000020UL | FCML_AMT_SSEx
#define    FCML_AMT_SSE        0x0000000000000040UL | FCML_AMT_SSEx
#define    FCML_AMT_SSE2       0x0000000000000080UL | FCML_AMT_SSEx
#define    FCML_AMT_SSE3       0x0000000000000100UL | FCML_AMT_SSEx
#define    FCML_AMT_SSSE3      0x0000000000000200UL | FCML_AMT_SSEx
#define    FCML_AMT_SSE41      0x0000000000000400UL | FCML_AMT_SSEx
#define    FCML_AMT_SSE42      0x0000000000000800UL | FCML_AMT_SSEx
#define    FCML_AMT_SSE4A      0x0000000000001000UL | FCML_AMT_SSEx
#define    FCML_AMT_AVX        0x0000000000002000UL | FCML_AMT_VEXx
#define    FCML_AMT_AVX2       0x0000000000004000UL | FCML_AMT_VEXx
#define    FCML_AMT_AES        0x0000000000008000UL
#define    FCML_AMT_SYSTEM     0x0000000000010000UL
#define    FCML_AMT_3DNOW      0x0000000000020000UL | FCML_AMT_MMX
#define    FCML_AMT_TBM        0x0000000000040000UL | FCML_AMT_VEXx
#define    FCML_AMT_BMI1       0x0000000000080000UL
#define    FCML_AMT_HLE        0x0000000000100000UL
#define    FCML_AMT_ADX        0x0000000000200000UL
#define    FCML_AMT_CLMUL      0x0000000000400000UL
#define    FCML_AMT_F16C       0x0000000000800000UL | FCML_AMT_VEXx
#define    FCML_AMT_RDRAND     0x0000000001000000UL
#define    FCML_AMT_RDSEED     0x0000000002000000UL
#define    FCML_AMT_PRFCHW     0x0000000004000000UL
#define    FCML_AMT_LWP        0x0000000008000000UL | FCML_AMT_SIMD
#define    FCML_AMT_SVM        0x0000000010000000UL
#define    FCML_AMT_FSGSBASE   0x0000000020000000UL
#define    FCML_AMT_FMA        0x0000000040000000UL | FCML_AMT_SIMD
#define    FCML_AMT_FMA4       0x0000000080000000UL | FCML_AMT_SIMD
#define    FCML_AMT_XOP        0x0000000100000000UL | FCML_AMT_SIMD
#define    FCML_AMT_EDX        0x0000000200000000UL
#define    FCML_AMT_ABM        0x0000000800000000UL
#define    FCML_AMT_VMX        0x0000001000000000UL
#define    FCML_AMT_SMX        0x0000002000000000UL
#define    FCML_AMT_POPCNT     0x0000004000000000UL
/* Control transfer instructions.*/
#define    FCML_AMT_CTI        0x0000008000000000UL
#define    FCML_AMT_BRANCH     0x0000010000000000UL
/* Shortcuts.*/
#define    FCML_AMT_MMX_SIMD   FCML_AMT_MMX   | FCML_AMT_SIMD
#define    FCML_AMT_SSE_SIMD   FCML_AMT_SSE   | FCML_AMT_SIMD
#define    FCML_AMT_SSE2_SIMD  FCML_AMT_SSE2  | FCML_AMT_SIMD
#define    FCML_AMT_SSE3_SIMD  FCML_AMT_SSE3  | FCML_AMT_SIMD
#define    FCML_AMT_SSSE3_SIMD FCML_AMT_SSSE3 | FCML_AMT_SIMD
#define    FCML_AMT_SSE41_SIMD FCML_AMT_SSE41 | FCML_AMT_SIMD
#define    FCML_AMT_SSE42_SIMD FCML_AMT_SSE42 | FCML_AMT_SIMD
#define    FCML_AMT_AVX_SIMD   FCML_AMT_AVX   | FCML_AMT_SIMD
#define    FCML_AMT_AVX2_SIMD  FCML_AMT_AVX2  | FCML_AMT_SIMD
#define    FCML_AMT_3DNOW_SIMD FCML_AMT_3DNOW | FCML_AMT_SIMD

#define FCML_IS_MULTI_INSTRUCTION(x)		( 0x8000 & ( x ) )
#define FCML_MULTI_INSTRUCTION(x)			( 0x8000 | ( x ) )

/* Structures used to describe instructions with they all allowed addressing modes. */
typedef struct fcml_st_def_addr_mode_desc {
    /* Mnemonic, if there is another mnemonic available for this opcode.*/
    fcml_string mnemonic_override;
    /* Addressing mode type.*/
    fcml_uint64_t instruction_group;
    /* Flags describing allowed prefixes.*/
    fcml_uint16_t allowed_prefixes;
    /* Some flags that contains various information about opcode.*/
    fcml_uint32_t opcode_flags;
    /* Opcode bytes.*/
    fcml_uint8_t opcode[3];
    /* Addressing of instruction operands.*/
    fcml_uint32_t opperands[FCML_OPERANDS_COUNT];
    /* Addressing mode.*/
    fcml_uint16_t addr_mode;
} fcml_st_def_addr_mode_desc;

/* Instruction code definition for multi instructions. Currently only  the instructions with suffixes uses this mechanism.*/
typedef struct fcml_st_def_instruction_code_desc {
    /* Instruction code.*/
    fcml_uint16_t instruction;
    /* Suffix.*/
    fcml_uint8_t suffix;
} fcml_st_def_instruction_code_desc;

/* Describes one addressing mode of instruction. */
typedef struct fcml_st_def_instruction_desc {
    /* Instruction code.*/
    fcml_uint16_t instruction;
    /* Optional array of multi instruction codes.*/
    fcml_st_def_instruction_code_desc *multi_instruction;
    /* Mnemonic.*/
    fcml_string mnemonic;
    /* Type of the instruction.*/
    fcml_en_def_instruction_type instruction_type;
    /* Number of opcodes' descriptions.*/
    fcml_uint8_t opcode_desc_count;
    /* Opcodes' descriptions.*/
    fcml_st_def_addr_mode_desc *addr_modes;
} fcml_st_def_instruction_desc;

/* Operands encoding */

#define FCML_IA_INSTRUCTION(i,x,y) 			{ i, NULL, x, FCML_EN_IT_IA, ( sizeof( y ) / sizeof( struct fcml_st_def_addr_mode_desc ) ), y }
#define FCML_IA_MULTI_INSTRUCTION(i,x,y)	{ FCML_MULTI_INSTRUCTION( i ), x, FCML_EMPTY_MNEMONIC, FCML_EN_IT_IA, ( sizeof( y ) / sizeof( struct fcml_st_def_addr_mode_desc ) ), y }

#define FCML_REG_FIELD_NUMBER_OF_REGISTERS				8
#define FCML_REG_FIELD_NUMBER_OF_CONDITIONS				16

/*********************************
 * Prefix fields.
 *********************************/

#define FCML_DEF_PREFIX_LOCK_ALLOWED(x)						FCML_TP_GET_BIT(x,0)
#define FCML_DEF_PREFIX_REPNE_XACQUIRE_ALLOWED(x)			FCML_TP_GET_BIT(x,1)
#define FCML_DEF_PREFIX_REP_XRELEASE_ALLOWED(x)				FCML_TP_GET_BIT(x,2)
#define FCML_DEF_PREFIX_W_1(x)								FCML_TP_GET_BIT(x,3)
#define FCML_DEF_PREFIX_W_0(x)								FCML_TP_GET_BIT(x,4)
#define FCML_DEF_PREFIX_L_1(x)								FCML_TP_GET_BIT(x,5)
#define FCML_DEF_PREFIX_L_0(x)								FCML_TP_GET_BIT(x,6)
#define FCML_DEF_PREFIX_VEX_REQ(x)							FCML_TP_GET_BIT(x,7)
#define FCML_DEF_PREFIX_VEXOP_VVVV(x)						FCML_TP_GET_BIT(x,8)
#define FCML_DEF_PREFIX_L_IGNORE_OS(x)						FCML_TP_GET_BIT(x,9)
#define FCML_DEF_PREFIX_XOP_REQ(x)							FCML_TP_GET_BIT(x,10)
#define FCML_DEF_PREFIX_HLE_ENABLED(x)						FCML_TP_GET_BIT(x,11)
#define FCML_DEF_PREFIX_MANDATORY_66(x) 					FCML_TP_GET_BIT(x,12)
#define FCML_DEF_PREFIX_MANDATORY_F2(x) 					FCML_TP_GET_BIT(x,13)
#define FCML_DEF_PREFIX_MANDATORY_F3(x) 					FCML_TP_GET_BIT(x,14)
#define FCML_DEF_PREFIX_SUFFIX(x)		 					FCML_TP_GET_BIT(x,15)

/*********************************
 * Opcode fields extractors.
 *********************************/

#define FCML_DEF_OPCODE_FLAGS_OPCODE_FIELD_REG(x)			( x & 0x00000001 )
#define FCML_DEF_OPCODE_FLAGS_OPCODE_FIELD_W(x)				( x & 0x00000002 )
#define FCML_DEF_OPCODE_FLAGS_OPCODE_FIELD_S(x)				( x & 0x00000004 )
#define FCML_DEF_OPCODE_FLAGS_OPCODE_FIELD_TTTN(x)			( x & 0x00000040 )
#define FCML_DEF_OPCODE_FLAGS_64BITS_EOSA_BY_DEFAULT(x)		( x & 0x00000080 )
#define FCML_DEF_OPCODE_FLAGS_POS(x)						( ( x & 0x00000700 ) >> 8 )
#define FCML_DEF_OPCODE_FLAGS_OPCODE_EXT(x)					( ( x & 0x00007800 ) >> 11 )
#define FCML_DEF_OPCODE_FLAGS_OPCODE_IS_MODRM(x) 			FCML_TP_GET_BIT(x,15)
#define FCML_DEF_OPCODE_FLAGS_OPCODE_IS_EXT(x) 				FCML_TP_GET_BIT(x,16)
#define FCML_DEF_OPCODE_FLAGS_OPCODE_NUM(x) 				( ( x & 0x000C0000 ) >> 18 )
#define FCML_DEF_OPCODE_FLAGS_PRIMARY_OPCODE(x) 			( ( x & 0x00300000 ) >> 20 )
#define FCML_DEF_OPCODE_FLAGS_64_BIT_MODE_SUPPORTED(x)		( x & 0x00800000 )
#define FCML_DEF_OPCODE_FLAGS_16_32_BIT_MODE_SUPPORTED(x)	( x & 0x00400000 )
#define FCML_DEF_OPCODE_FLAGS_EOSA_16(x)					( x & 0x01000000 )
#define FCML_DEF_OPCODE_FLAGS_EOSA_32(x)					( x & 0x02000000 )
#define FCML_DEF_OPCODE_FLAGS_EOSA_64(x)					( x & 0x04000000 )
#define FCML_DEF_OPCODE_FLAGS_IS_EOSA_RESTRICTION(x)		( x & 0x07000000 )
#define FCML_DEF_OPCODE_FLAGS_EASA_16(x)					( x & 0x08000000 )
#define FCML_DEF_OPCODE_FLAGS_EASA_32(x)					( x & 0x10000000 )
#define FCML_DEF_OPCODE_FLAGS_EASA_64(x)					( x & 0x20000000 )
#define FCML_DEF_OPCODE_FLAGS_IS_EASA_RESTRICTION(x)		( x & 0x38000000 )
#define FCML_DEF_OPCODE_FLAGS_FORCE_64BITS_EOSA(x)			( x & 0x40000000 )

/*********************************
 * Addressing modes.
 *********************************/

/* Operand access mode (source/destination).*/
#define FCML_OA_R		0x80000000
#define FCML_OA_W		0x40000000
#define FCML_OA_RW		( FCML_OA_R | FCML_OA_W )

#define FCML_NA			0x00000000

/* Immediate data.*/
#define FCML_OP_IMM_BASE											0x01000000
#define FCML_OP_IMM(encoded_imm_size, encoded_ex_imm_size)			( FCML_OP_IMM_BASE | ( encoded_imm_size ) << 8 | ( encoded_ex_imm_size ) )
#define FCML_OP_IMM_64												( FCML_OP_IMM_BASE | ( 1 << 16 ) | ( FCML_EOS_EOSA ) << 8 | ( FCML_EOS_UNDEFINED ) )

/* Register explicitly set.*/
#define FCML_OP_EXPLICIT_REG_BASE									0x02000000
#define FCML_OP_EXPLICIT_REG(reg_type, reg_num, encoded_reg_size)	( FCML_OP_EXPLICIT_REG_BASE | ( reg_type ) << 12 | ( reg_num ) << 8 | encoded_reg_size )

/* Register field in opcode byte.*/
#define FCML_OP_OPCODE_REG_BASE										0x03000000
#define FCML_OP_OPCODE_REG(reg_type, encoded_reg_size)				( FCML_OP_OPCODE_REG_BASE | ( reg_type ) << 8 | encoded_reg_size )

/* Relative addressing.*/
#define FCML_OP_IMMEDIATE_DIS_RELATIVE_BASE							0x04000000
#define FCML_OP_IMMEDIATE_DIS_RELATIVE( encoded_imm_size )			( FCML_OP_IMMEDIATE_DIS_RELATIVE_BASE | encoded_imm_size )

/* Far pointers.*/
#define FCML_OP_FAR_POINTER											0x05000000

/* Addressing by explicit GPR register. (Used by CMPS for instance.)*/
#define FCML_OP_EXPLICIT_GPS_REG_ADDRESSING_BASE					0x06000000
#define FCML_OP_EXPLICIT_GPS_REG_ADDRESSING(reg_num, encoded_operand_size, encoded_segment_register)	( FCML_OP_EXPLICIT_GPS_REG_ADDRESSING_BASE | ( reg_num ) << 16 | ( encoded_operand_size ) << 8 | ( encoded_segment_register ) )

/* It allows defining explicit IMM8 operand type. See INT instruction.*/
#define FCML_OP_EXPLICIT_IB_BASE									0x07000000
#define FCML_OP_EXPLICIT_IB(value)									( FCML_OP_EXPLICIT_IB_BASE | value )

/* Segment relative addressing.*/
#define FCML_OP_SEGMENT_RELATIVE_OFFSET_BASE						0x08000000
#define FCML_OP_SEGMENT_RELATIVE_OFFSET( operand_size, encoded_segment_register )	( FCML_OP_SEGMENT_RELATIVE_OFFSET_BASE | ( operand_size ) << 8 | ( encoded_segment_register ) )

/********************************/
/*      ModR/M encoding.        */
/********************************/

/* Allows to encode all common ModR/M based addressing modes using only one macro.*/
/* Only register addressing is allowed.*/
#define FCML_RMF_R		0x01
/* Only memory addressing is allowed.*/
#define FCML_RMF_M		0x02
/* Indirect addressing.*/
#define FCML_RMF_I		0x04
/* Shortcut, operand acts as source and destination.*/
#define FCML_RMF_RM		( FCML_RMF_R | FCML_RMF_M )

#define FCML_OP_RM_BASE								0x09000000
#define FCML_OP_RM(reg_type, encoded_register_operand_size, encoded_memory_operand_size, flags )		( FCML_OP_RM_BASE | ( ( encoded_memory_operand_size ) << 16 ) | ( ( encoded_register_operand_size ) << 8 ) | ( ( reg_type ) << 4 ) | ( flags ) )
#define FCML_OP_RM_W(reg_type, encoded_register_operand_size, encoded_memory_operand_size, flags )		( FCML_OP_RM(reg_type, encoded_register_operand_size, encoded_memory_operand_size, flags) | FCML_OA_W )

#define FCML_OP_R_BASE								0x0A000000
#define FCML_OP_R( reg_type, encoded_register_operand_size )	( FCML_OP_R_BASE | ( encoded_register_operand_size << 4 ) | reg_type )

/******************************/
/* XOP/VEX specific encoding. */
/******************************/

#define FCML_OP_VEX_VVVV_REG_BASE						0x0B000000
#define FCML_OP_VEX_VVVV_REG( reg_type, encoded_register_size )	( FCML_OP_VEX_VVVV_REG_BASE | ( encoded_register_size << 4 ) | reg_type )

/*****************************/
/* IS4/IS5 operand decoding. */
/*****************************/

#define FCML_ISF_IS4		0x01
#define FCML_ISF_IS5		0x02
#define FCML_ISF_IS5_SRC	0x10
#define FCML_ISF_IS5_M2Z	0x20

#define FCML_OP_OPERAND_ISx_BASE						0x0C000000
#define FCML_OP_OPERAND_IS4								( FCML_OP_OPERAND_ISx_BASE | FCML_ISF_IS4 )
#define FCML_OP_OPERAND_IS5( flags )					( FCML_OP_OPERAND_ISx_BASE | FCML_ISF_IS5 | flags )

/**************************/
/* VSIB operand decoding. */
/**************************/

/* Vector index register.*/
#define FCML_VSIB_XMM	0x01
#define FCML_VSIB_YMM	0x02

#define FCML_OP_VSIB_BASE						    	0x0D000000
#define FCML_OP_VSIB( vector_index_register, encoded_index_value_size )		( FCML_OP_VSIB_BASE | ( vector_index_register ) << 8 | encoded_index_value_size )

/**************/
/* Pseudo-Op. */
/**************/

#define FCML_OP_PSEUDO_OP_BASE                      	0x0E000000
#define FCML_OP_PSEUDO_OP( mask )                   	( FCML_OP_PSEUDO_OP_BASE | ( mask ) )

/*******************************/
/* Segment registers encoding. */
/*******************************/

#define FCML_SEG_ALLOW_OVERRIDE								0x80
#define FCML_SEG_DENY_OVERRIDE								0x00
#define FCML_SEG_ENCODE_REGISTER( reg_num, override )		( reg_num | override )
#define FCML_SEG_DECODE_IS_OVERRIDE_ALLOWED( encoded )		( FCML_SEG_ALLOW_OVERRIDE & encoded )
#define FCML_SEG_DECODE_REGISTER( encoded )					( encoded & ~FCML_SEG_ALLOW_OVERRIDE )

/* Useful macros related to addressing modes.*/

#define FCMP_DEF_IS_ADDR_MODE( x, y )						( ( x ) == ( ( y ) >> 24 ) )

/* Shorthands*/

#define FCML_OP_MODRM_RM_8              FCML_OP_RM(FCML_REG_GPR, FCML_EOS_BYTE, FCML_EOS_BYTE, FCML_RMF_RM )
#define FCML_OP_MODRM_RM_8_W            ( FCML_OP_MODRM_RM_8 | FCML_OA_W )
#define FCML_OP_MODRM_RM_8_RW           ( FCML_OP_MODRM_RM_8 | FCML_OA_RW )
#define FCML_OP_MODRM_RM_16             FCML_OP_RM(FCML_REG_GPR, FCML_EOS_WORD, FCML_EOS_WORD, FCML_RMF_RM )
#define FCML_OP_MODRM_RM_16_W			( FCML_OP_MODRM_RM_16 | FCML_OA_W )
#define FCML_OP_MODRM_RM_16_RW			( FCML_OP_MODRM_RM_16 | FCML_OA_RW )
#define FCML_OP_MODRM_RM_32             FCML_OP_RM(FCML_REG_GPR, FCML_EOS_DWORD, FCML_EOS_DWORD, FCML_RMF_RM )
#define FCML_OP_MODRM_RM_32_W			( FCML_OP_MODRM_RM_32 | FCML_OA_W )
#define FCML_OP_MODRM_RM_32_RW			( FCML_OP_MODRM_RM_32 | FCML_OA_RW )
#define FCML_OP_MODRM_RM_64             FCML_OP_RM(FCML_REG_GPR, FCML_EOS_QWORD, FCML_EOS_QWORD, FCML_RMF_RM )
#define FCML_OP_MODRM_RM_64_W			( FCML_OP_MODRM_RM_64 | FCML_OA_W )
#define FCML_OP_MODRM_RM_64_RW			( FCML_OP_MODRM_RM_64 | FCML_OA_RW )
#define FCML_OP_MODRM_RM_128            FCML_OP_RM(FCML_REG_GPR, FCML_EOS_OWORD, FCML_EOS_OWORD, FCML_RMF_RM )
#define FCML_OP_MODRM_RM_128_W          ( FCML_OP_MODRM_RM_128 | FCML_OA_W )
#define FCML_OP_MODRM_RM_128_RW         ( FCML_OP_MODRM_RM_128 | FCML_OA_RW )
#define FCML_OP_MODRM_RM_OP_8           FCML_OP_RM(FCML_REG_GPR, FCML_EOS_BYTE, FCML_EOS_BYTE | FCML_EOS_OPT, FCML_RMF_RM )
#define FCML_OP_MODRM_RM_OP_8_W         ( FCML_OP_MODRM_RM_OP_8 | FCML_OA_W )
#define FCML_OP_MODRM_RM_OP_8_RW        ( FCML_OP_MODRM_RM_OP_8 | FCML_OA_RW )
#define FCML_OP_MODRM_RM_OP_16          FCML_OP_RM(FCML_REG_GPR, FCML_EOS_WORD, FCML_EOS_WORD | FCML_EOS_OPT, FCML_RMF_RM )
#define FCML_OP_MODRM_RM_OP_16_W		( FCML_OP_MODRM_RM_OP_16 | FCML_OA_W )
#define FCML_OP_MODRM_RM_OP_16_RW		( FCML_OP_MODRM_RM_OP_16 | FCML_OA_RW )
#define FCML_OP_MODRM_RM_OP_32          FCML_OP_RM(FCML_REG_GPR, FCML_EOS_DWORD, FCML_EOS_DWORD | FCML_EOS_OPT, FCML_RMF_RM )
#define FCML_OP_MODRM_RM_OP_32_W		( FCML_OP_MODRM_RM_OP_32 | FCML_OA_W )
#define FCML_OP_MODRM_RM_OP_32_RW		( FCML_OP_MODRM_RM_OP_32 | FCML_OA_RW )
#define FCML_OP_MODRM_RM_OP_64          FCML_OP_RM(FCML_REG_GPR, FCML_EOS_QWORD, FCML_EOS_QWORD | FCML_EOS_OPT, FCML_RMF_RM )
#define FCML_OP_MODRM_RM_OP_64_W		( FCML_OP_MODRM_RM_OP_64 | FCML_OA_W )
#define FCML_OP_MODRM_RM_OP_64_RW		( FCML_OP_MODRM_RM_OP_64 | FCML_OA_RW )
#define FCML_OP_MODRM_RM_OP_128         FCML_OP_RM(FCML_REG_GPR, FCML_EOS_OWORD, FCML_EOS_OWORD | FCML_EOS_OPT, FCML_RMF_RM )
#define FCML_OP_MODRM_RM_OP_128_W       ( FCML_OP_MODRM_RM_OP_128 | FCML_OA_W )
#define FCML_OP_MODRM_RM_OP_128_RW      ( FCML_OP_MODRM_RM_OP_128 | FCML_OA_RW )
#define FCML_OP_MODRM_RM				FCML_OP_RM(FCML_REG_GPR, FCML_EOS_EOSA, FCML_EOS_EOSA, FCML_RMF_RM )
#define FCML_OP_MODRM_RM_W				( FCML_OP_MODRM_RM | FCML_OA_W )
#define FCML_OP_MODRM_RM_RW				( FCML_OP_MODRM_RM | FCML_OA_RW )
#define FCML_OP_MODRM_RM_I				FCML_OP_RM(FCML_REG_GPR, FCML_EOS_EOSA, FCML_EOS_EOSA, FCML_RMF_RM | FCML_RMF_I )
#define FCML_OP_MODRM_RM_I_W			( FCML_OP_MODRM_RM | FCML_OA_W )
#define FCML_OP_MODRM_RM_I_RW			( FCML_OP_MODRM_RM | FCML_OA_RW )
#define FCML_OP_MODRM_R_8				FCML_OP_R(FCML_REG_GPR, FCML_EOS_BYTE )
#define FCML_OP_MODRM_R_8_W             ( FCML_OP_MODRM_R_8 | FCML_OA_W )
#define FCML_OP_MODRM_R_8_RW            ( FCML_OP_MODRM_R_8 | FCML_OA_RW )
#define FCML_OP_MODRM_R_16				FCML_OP_R(FCML_REG_GPR, FCML_EOS_WORD )
#define FCML_OP_MODRM_R_16_W			( FCML_OP_MODRM_R_16 | FCML_OA_W )
#define FCML_OP_MODRM_R_16_RW			( FCML_OP_MODRM_R_16 | FCML_OA_RW )
#define FCML_OP_MODRM_R_32				FCML_OP_R(FCML_REG_GPR, FCML_EOS_DWORD )
#define FCML_OP_MODRM_R_32_W			( FCML_OP_MODRM_R_32 | FCML_OA_W )
#define FCML_OP_MODRM_R_32_RW			( FCML_OP_MODRM_R_32 | FCML_OA_RW )
#define FCML_OP_MODRM_R_64				FCML_OP_R(FCML_REG_GPR, FCML_EOS_QWORD )
#define FCML_OP_MODRM_R_64_W			( FCML_OP_MODRM_R_64 | FCML_OA_W )
#define FCML_OP_MODRM_R_64_RW			( FCML_OP_MODRM_R_64 | FCML_OA_RW )
#define FCML_OP_MODRM_R                 FCML_OP_R(FCML_REG_GPR, FCML_EOS_EOSA )
#define FCML_OP_MODRM_R_W				( FCML_OP_MODRM_R | FCML_OA_W )
#define FCML_OP_MODRM_R_RW				( FCML_OP_MODRM_R | FCML_OA_RW )
#define FCML_OP_MODRM_M                 FCML_OP_RM(FCML_REG_UNDEFINED, FCML_EOS_UNDEFINED, FCML_EOS_EOSA, FCML_RMF_M )
#define FCML_OP_MODRM_M_W               (FCML_OP_MODRM_M | FCML_OA_W)
#define FCML_OP_MODRM_M_RW              (FCML_OP_MODRM_M | FCML_OA_RW)
#define FCML_OP_MODRM_M_8				FCML_OP_RM(FCML_REG_UNDEFINED, FCML_EOS_UNDEFINED, FCML_EOS_BYTE, FCML_RMF_M )
#define FCML_OP_MODRM_M_8_W             (FCML_OP_MODRM_M_8 | FCML_OA_W)
#define FCML_OP_MODRM_M_8_RW            (FCML_OP_MODRM_M_8 | FCML_OA_RW)
#define FCML_OP_MODRM_M_16				FCML_OP_RM(FCML_REG_UNDEFINED, FCML_EOS_UNDEFINED, FCML_EOS_WORD, FCML_RMF_M )
#define FCML_OP_MODRM_M_16_W			(FCML_OP_MODRM_M_16 | FCML_OA_W)
#define FCML_OP_MODRM_M_16_RW			(FCML_OP_MODRM_M_16 | FCML_OA_RW)
#define FCML_OP_MODRM_M_32				FCML_OP_RM(FCML_REG_UNDEFINED, FCML_EOS_UNDEFINED, FCML_EOS_DWORD, FCML_RMF_M )
#define FCML_OP_MODRM_M_32_W			(FCML_OP_MODRM_M_32 | FCML_OA_W)
#define FCML_OP_MODRM_M_32_RW			(FCML_OP_MODRM_M_32 | FCML_OA_RW)
#define FCML_OP_MODRM_M_64				FCML_OP_RM(FCML_REG_UNDEFINED, FCML_EOS_UNDEFINED, FCML_EOS_QWORD, FCML_RMF_M )
#define FCML_OP_MODRM_M_64_W			(FCML_OP_MODRM_M_64 | FCML_OA_W)
#define FCML_OP_MODRM_M_64_RW			(FCML_OP_MODRM_M_64 | FCML_OA_RW)
#define FCML_OP_MODRM_M_80				FCML_OP_RM(FCML_REG_UNDEFINED, FCML_EOS_UNDEFINED, FCML_EOS_TBYTE, FCML_RMF_M )
#define FCML_OP_MODRM_M_80_W			(FCML_OP_MODRM_M_80 | FCML_OA_W)
#define FCML_OP_MODRM_M_80_RW			(FCML_OP_MODRM_M_80 | FCML_OA_RW)
#define FCML_OP_MODRM_M_128             FCML_OP_RM(FCML_REG_UNDEFINED, FCML_EOS_UNDEFINED, FCML_EOS_OWORD, FCML_RMF_M )
#define FCML_OP_MODRM_M_128_W			(FCML_OP_MODRM_M_128 | FCML_OA_W)
#define FCML_OP_MODRM_M_128_RW			(FCML_OP_MODRM_M_128 | FCML_OA_RW)
#define FCML_OP_MODRM_M_256             FCML_OP_RM(FCML_REG_UNDEFINED, FCML_EOS_UNDEFINED, FCML_EOS_YWORD, FCML_RMF_M )
#define FCML_OP_MODRM_M_256_W			(FCML_OP_MODRM_M_256 | FCML_OA_W)
#define FCML_OP_MODRM_M_256_RW			(FCML_OP_MODRM_M_256 | FCML_OA_RW)
#define FCML_OP_MODRM_M_XMM             FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_UNDEFINED, FCML_EOS_OWORD, FCML_RMF_M )
#define FCML_OP_MODRM_M_XMM_W           (FCML_OP_MODRM_M_XMM | FCML_OA_W)
#define FCML_OP_MODRM_M_XMM_RW          (FCML_OP_MODRM_M_XMM | FCML_OA_RW)
#define FCML_OP_MODRM_M_YMM             FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_UNDEFINED, FCML_EOS_YWORD, FCML_RMF_M )
#define FCML_OP_MODRM_M_YMM_W           (FCML_OP_MODRM_M_YMM | FCML_OA_W)
#define FCML_OP_MODRM_M_YMM_RW          (FCML_OP_MODRM_M_YMM | FCML_OA_RW)
#define FCML_OP_MODRM_M_14_28			FCML_OP_RM(FCML_REG_UNDEFINED, FCML_EOS_UNDEFINED, FCML_EOS_14_28, FCML_RMF_M )
#define FCML_OP_MODRM_M_14_28_W         (FCML_OP_MODRM_M_14_28 | FCML_OA_W)
#define FCML_OP_MODRM_M_14_28_RW        (FCML_OP_MODRM_M_14_28 | FCML_OA_RW)
#define FCML_OP_MODRM_M_94_108			FCML_OP_RM(FCML_REG_UNDEFINED, FCML_EOS_UNDEFINED, FCML_EOS_94_108, FCML_RMF_M )
#define FCML_OP_MODRM_M_94_108_W		(FCML_OP_MODRM_M_94_108 | FCML_OA_W)
#define FCML_OP_MODRM_M_94_108_RW		(FCML_OP_MODRM_M_94_108 | FCML_OA_RW)
#define FCML_OP_MODRM_M_FP				FCML_OP_RM(FCML_REG_UNDEFINED, FCML_EOS_UNDEFINED, FCML_EOS_FP, FCML_RMF_M )
#define FCML_OP_MODRM_M_FP_W		    (FCML_OP_MODRM_M_FP | FCML_OA_W)
#define FCML_OP_MODRM_M_FP_RW		    (FCML_OP_MODRM_M_FP | FCML_OA_RW)
#define FCML_OP_MODRM_M_FPI				FCML_OP_RM(FCML_REG_UNDEFINED, FCML_EOS_UNDEFINED, FCML_EOS_FPI, FCML_RMF_M )
#define FCML_OP_MODRM_M_FPI_W		    (FCML_OP_MODRM_M_FPI | FCML_OA_W)
#define FCML_OP_MODRM_M_FPI_RW		    (FCML_OP_MODRM_M_FPI | FCML_OA_RW)
#define FCML_OP_MODRM_M_512B			FCML_OP_RM(FCML_REG_UNDEFINED, FCML_EOS_UNDEFINED, FCML_EOS_512B, FCML_RMF_M )
#define FCML_OP_MODRM_M_512B_W			(FCML_OP_MODRM_M_512B | FCML_OA_W)
#define FCML_OP_MODRM_M_512B_RW			(FCML_OP_MODRM_M_512B | FCML_OA_RW)
#define FCML_OP_MODRM_M_UNDEF			FCML_OP_RM(FCML_REG_UNDEFINED, FCML_EOS_UNDEFINED, FCML_EOS_UNDEFINED, FCML_RMF_M )
#define FCML_OP_MODRM_M_UNDEF_W         (FCML_OP_MODRM_M_UNDEF | FCML_OA_W)
#define FCML_OP_MODRM_M_UNDEF_RW        (FCML_OP_MODRM_M_UNDEF | FCML_OA_RW)
#define FCML_OP_MODRM_M_FPI             FCML_OP_RM(FCML_REG_UNDEFINED, FCML_EOS_UNDEFINED, FCML_EOS_FPI, FCML_RMF_M )
#define FCML_OP_MODRM_RM_OP				FCML_OP_RM(FCML_REG_GPR, FCML_EOS_EOSA, FCML_EOS_EOSA | FCML_EOS_OPT, FCML_RMF_RM )
#define FCML_OP_MODRM_RM_OP_W			( FCML_OP_MODRM_RM_OP | FCML_OA_W )
#define FCML_OP_MODRM_RM_OP_RW			( FCML_OP_MODRM_RM_OP | FCML_OA_RW )
#define FCML_OP_MODRM_M_OP              FCML_OP_RM(FCML_REG_UNDEFINED, FCML_EOS_UNDEFINED, FCML_EOS_EOSA | FCML_EOS_OPT, FCML_RMF_M )
#define FCML_OP_MODRM_M_OP_W            (FCML_OP_MODRM_M_OP | FCML_OA_W)
#define FCML_OP_MODRM_M_OP_RW           (FCML_OP_MODRM_M_OP | FCML_OA_RW)
#define FCML_OP_MODRM_M_OP_8			FCML_OP_RM(FCML_REG_UNDEFINED, FCML_EOS_UNDEFINED, FCML_EOS_BYTE | FCML_EOS_OPT, FCML_RMF_M )
#define FCML_OP_MODRM_M_OP_8_W          (FCML_OP_MODRM_M_OP_8 | FCML_OA_W)
#define FCML_OP_MODRM_M_OP_8_RW         (FCML_OP_MODRM_M_OP_8 | FCML_OA_RW)
#define FCML_OP_MODRM_M_OP_16			FCML_OP_RM(FCML_REG_UNDEFINED, FCML_EOS_UNDEFINED, FCML_EOS_WORD | FCML_EOS_OPT, FCML_RMF_M )
#define FCML_OP_MODRM_M_OP_16_W			(FCML_OP_MODRM_M_OP_16 | FCML_OA_W)
#define FCML_OP_MODRM_M_OP_16_RW		(FCML_OP_MODRM_M_OP_16 | FCML_OA_RW)
#define FCML_OP_MODRM_M_OP_32			FCML_OP_RM(FCML_REG_UNDEFINED, FCML_EOS_UNDEFINED, FCML_EOS_DWORD | FCML_EOS_OPT, FCML_RMF_M )
#define FCML_OP_MODRM_M_OP_32_W			(FCML_OP_MODRM_M_OP_32 | FCML_OA_W)
#define FCML_OP_MODRM_M_OP_32_RW		(FCML_OP_MODRM_M_OP_32 | FCML_OA_RW)
#define FCML_OP_MODRM_M_OP_64			FCML_OP_RM(FCML_REG_UNDEFINED, FCML_EOS_UNDEFINED, FCML_EOS_QWORD | FCML_EOS_OPT, FCML_RMF_M )
#define FCML_OP_MODRM_M_OP_64_W			(FCML_OP_MODRM_M_OP_64 | FCML_OA_W)
#define FCML_OP_MODRM_M_OP_64_RW		(FCML_OP_MODRM_M_OP_64 | FCML_OA_RW)
#define FCML_OP_MODRM_M_OP_80			FCML_OP_RM(FCML_REG_UNDEFINED, FCML_EOS_UNDEFINED, FCML_EOS_TBYTE | FCML_EOS_OPT, FCML_RMF_M )
#define FCML_OP_MODRM_M_OP_80_W			(FCML_OP_MODRM_M_OP_80 | FCML_OA_W)
#define FCML_OP_MODRM_M_OP_80_RW		(FCML_OP_MODRM_M_OP_80 | FCML_OA_RW)
#define FCML_OP_MODRM_M_OP_128          FCML_OP_RM(FCML_REG_UNDEFINED, FCML_EOS_UNDEFINED, FCML_EOS_OWORD | FCML_EOS_OPT, FCML_RMF_M )
#define FCML_OP_MODRM_M_OP_128_W		(FCML_OP_MODRM_M_OP_128 | FCML_OA_W)
#define FCML_OP_MODRM_M_OP_128_RW		(FCML_OP_MODRM_M_OP_128 | FCML_OA_RW)
#define FCML_OP_MODRM_M_OP_XMM          FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_UNDEFINED, FCML_EOS_XWORD | FCML_EOS_OPT, FCML_RMF_M )
#define FCML_OP_MODRM_M_OP_XMM_W        (FCML_OP_MODRM_M_OP_XMM | FCML_OA_W)
#define FCML_OP_MODRM_M_OP_XMM_RW       (FCML_OP_MODRM_M_OP_XMM | FCML_OA_RW)
#define FCML_OP_MODRM_M_OP_YMM          FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_UNDEFINED, FCML_EOS_YWORD | FCML_EOS_OPT, FCML_RMF_M )
#define FCML_OP_MODRM_M_OP_YMM_W        (FCML_OP_MODRM_M_OP_YMM | FCML_OA_W)
#define FCML_OP_MODRM_M_OP_YMM_RW       (FCML_OP_MODRM_M_OP_YMM | FCML_OA_RW)
#define FCML_OP_MODRM_M_OP_14_28		FCML_OP_RM(FCML_REG_UNDEFINED, FCML_EOS_UNDEFINED, FCML_EOS_14_28 | FCML_EOS_OPT, FCML_RMF_M )
#define FCML_OP_MODRM_M_OP_14_28_W      (FCML_OP_MODRM_M_OP_14_28 | FCML_OA_W)
#define FCML_OP_MODRM_M_OP_14_28_RW     (FCML_OP_MODRM_M_OP_14_28 | FCML_OA_RW)
#define FCML_OP_MODRM_M_OP_FP			FCML_OP_RM(FCML_REG_UNDEFINED, FCML_EOS_UNDEFINED, FCML_EOS_FP | FCML_EOS_OPT, FCML_RMF_M )
#define FCML_OP_MODRM_M_OP_FP_W		    (FCML_OP_MODRM_M_OP_FP | FCML_OA_W)
#define FCML_OP_MODRM_M_OP_FP_RW		(FCML_OP_MODRM_M_OP_FP | FCML_OA_RW)
#define FCML_OP_MODRM_M_OP_512B			FCML_OP_RM(FCML_REG_UNDEFINED, FCML_EOS_UNDEFINED, FCML_EOS_512B | FCML_EOS_OPT, FCML_RMF_M )
#define FCML_OP_MODRM_M_OP_512B_W		(FCML_OP_MODRM_M_OP_512B | FCML_OA_W)
#define FCML_OP_MODRM_M_OP_512B_RW		(FCML_OP_MODRM_M_OP_512B | FCML_OA_RW)

#define FCML_OP_MODRM_MM_OSA			FCML_OP_RM(FCML_REG_UNDEFINED, FCML_EOS_UNDEFINED, FCML_EOS_32_64, FCML_RMF_M )
#define FCML_OP_MODRM_MM_OSA_W			( FCML_OP_MODRM_MM_OSA | FCML_OA_W )
#define FCML_OP_MODRM_MM_OSA_RW			( FCML_OP_MODRM_MM_OSA | FCML_OA_RW )
#define FCML_OP_MODRM_MM_OP_OSA			FCML_OP_RM(FCML_REG_UNDEFINED, FCML_EOS_UNDEFINED, FCML_EOS_32_64 | FCML_EOS_OPT, FCML_RMF_M )
#define FCML_OP_MODRM_MM_OP_OSA_W		( FCML_OP_MODRM_MM_OP_OSA | FCML_OA_W )
#define FCML_OP_MODRM_MM_OP_OSA_RW		( FCML_OP_MODRM_MM_OP_OSA | FCML_OA_RW )
#define FCML_OP_MODRM_RM_MMX_OP			FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_QWORD, FCML_EOS_QWORD | FCML_EOS_OPT, FCML_RMF_RM )
#define FCML_OP_MODRM_RM_MMX_OP_W		( FCML_OP_MODRM_RM_MMX_OP | FCML_OA_W )
#define FCML_OP_MODRM_RM_MMX_OP_RW		( FCML_OP_MODRM_RM_MMX_OP | FCML_OA_RW )
#define FCML_OP_MODRM_RM_MMX			FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_QWORD, FCML_EOS_QWORD, FCML_RMF_RM )
#define FCML_OP_MODRM_RM_MMX_W			( FCML_OP_MODRM_RM_MMX | FCML_OA_W )
#define FCML_OP_MODRM_RM_MMX_RW			( FCML_OP_MODRM_RM_MMX | FCML_OA_RW )
#define FCML_OP_MODRM_RM_MMX_32         FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_QWORD, FCML_EOS_DWORD, FCML_RMF_RM )
#define FCML_OP_MODRM_RM_MMX_32_W       ( FCML_OP_MODRM_RM_MMX_32 | FCML_OA_W )
#define FCML_OP_MODRM_RM_MMX_32_RW      ( FCML_OP_MODRM_RM_MMX_32 | FCML_OA_RW )
#define FCML_OP_MODRM_R_MMX             FCML_OP_R(FCML_REG_SIMD, FCML_EOS_QWORD )
#define FCML_OP_MODRM_R_MMX_W			( FCML_OP_MODRM_R_MMX | FCML_OA_W )
#define FCML_OP_MODRM_R_MMX_RW			( FCML_OP_MODRM_R_MMX | FCML_OA_RW )
#define FCML_OP_MODRM_RM_YMM_256		FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_YWORD, FCML_EOS_YWORD, FCML_RMF_RM )
#define FCML_OP_MODRM_RM_YMM_256_W		( FCML_OP_MODRM_RM_YMM_256 | FCML_OA_W )
#define FCML_OP_MODRM_RM_YMM_256_RW		( FCML_OP_MODRM_RM_YMM_256 | FCML_OA_RW )
#define FCML_OP_MODRM_RM_XMM_128		FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_OWORD, FCML_EOS_OWORD, FCML_RMF_RM )
#define FCML_OP_MODRM_RM_XMM_128_W		( FCML_OP_MODRM_RM_XMM_128 | FCML_OA_W )
#define FCML_OP_MODRM_RM_XMM_128_RW		( FCML_OP_MODRM_RM_XMM_128 | FCML_OA_RW )
#define FCML_OP_MODRM_RM_XMM_64         FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_OWORD, FCML_EOS_QWORD, FCML_RMF_RM )
#define FCML_OP_MODRM_RM_XMM_64_W		( FCML_OP_MODRM_RM_XMM_64 | FCML_OA_W )
#define FCML_OP_MODRM_RM_XMM_64_RW		( FCML_OP_MODRM_RM_XMM_64 | FCML_OA_RW )
#define FCML_OP_MODRM_RM_XMM_32         FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_OWORD, FCML_EOS_DWORD, FCML_RMF_RM )
#define FCML_OP_MODRM_RM_XMM_32_W		( FCML_OP_MODRM_RM_XMM_32 | FCML_OA_W )
#define FCML_OP_MODRM_RM_XMM_32_RW		( FCML_OP_MODRM_RM_XMM_32 | FCML_OA_RW )
#define FCML_OP_MODRM_RM_XMM_8          FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_OWORD, FCML_EOS_BYTE, FCML_RMF_RM )
#define FCML_OP_MODRM_RM_XMM_8_W		( FCML_OP_MODRM_RM_XMM_8 | FCML_OA_W )
#define FCML_OP_MODRM_RM_XMM_8_RW		( FCML_OP_MODRM_RM_XMM_8 | FCML_OA_RW )
#define FCML_OP_MODRM_RM_XMM_16         FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_OWORD, FCML_EOS_WORD, FCML_RMF_RM )
#define FCML_OP_MODRM_RM_XMM_16_W		( FCML_OP_MODRM_RM_XMM_16 | FCML_OA_W )
#define FCML_OP_MODRM_RM_XMM_16_RW		( FCML_OP_MODRM_RM_XMM_16 | FCML_OA_RW )
#define FCML_OP_MODRM_RM_XMM_OP_64      FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_OWORD, FCML_EOS_QWORD | FCML_EOS_OPT, FCML_RMF_RM )
#define FCML_OP_MODRM_RM_XMM_OP_64_W	( FCML_OP_MODRM_RM_XMM_OP_64 | FCML_OA_W )
#define FCML_OP_MODRM_RM_XMM_OP_64_RW	( FCML_OP_MODRM_RM_XMM_OP_64 | FCML_OA_RW )
#define FCML_OP_MODRM_RM_XMM_OP_128		FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_OWORD, FCML_EOS_OWORD | FCML_EOS_OPT, FCML_RMF_RM )
#define FCML_OP_MODRM_RM_XMM_OP_128_W	( FCML_OP_MODRM_RM_XMM_OP_128 | FCML_OA_W )
#define FCML_OP_MODRM_RM_XMM_OP_128_RW	( FCML_OP_MODRM_RM_XMM_OP_128 | FCML_OA_RW )
#define FCML_OP_MODRM_RM_YMM_OP_256		FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_YWORD, FCML_EOS_YWORD | FCML_EOS_OPT, FCML_RMF_RM )
#define FCML_OP_MODRM_RM_YMM_OP_256_W	( FCML_OP_MODRM_RM_YMM_OP_256 | FCML_OA_W )
#define FCML_OP_MODRM_RM_YMM_OP_256_RW	( FCML_OP_MODRM_RM_YMM_OP_256 | FCML_OA_RW )
#define FCML_OP_MODRM_RM_MMX_OP_32      FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_QWORD, FCML_EOS_DWORD | FCML_EOS_OPT, FCML_RMF_RM )
#define FCML_OP_MODRM_RM_MMX_OP_32_W    ( FCML_OP_MODRM_RM_MMX_OP_32 | FCML_OA_W )
#define FCML_OP_MODRM_RM_MMX_OP_32_RW    ( FCML_OP_MODRM_RM_MMX_OP_32 | FCML_OA_RW )
#define FCML_OP_MODRM_RM_XMM_OP_32      FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_OWORD, FCML_EOS_DWORD | FCML_EOS_OPT, FCML_RMF_RM )
#define FCML_OP_MODRM_RM_XMM_OP_32_W	( FCML_OP_MODRM_RM_XMM_OP_32 | FCML_OA_W )
#define FCML_OP_MODRM_RM_XMM_OP_32_RW	( FCML_OP_MODRM_RM_XMM_OP_32 | FCML_OA_RW )
#define FCML_OP_MODRM_RM_XMM_OP_16      FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_OWORD, FCML_EOS_WORD | FCML_EOS_OPT, FCML_RMF_RM )
#define FCML_OP_MODRM_RM_XMM_OP_16_W	( FCML_OP_MODRM_RM_XMM_OP_16 | FCML_OA_W )
#define FCML_OP_MODRM_RM_XMM_OP_16_RW	( FCML_OP_MODRM_RM_XMM_OP_16 | FCML_OA_RW )
#define FCML_OP_MODRM_RM_XMM_OP_8       FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_OWORD, FCML_EOS_BYTE | FCML_EOS_OPT, FCML_RMF_RM )
#define FCML_OP_MODRM_RM_XMM_OP_8_W		( FCML_OP_MODRM_RM_XMM_OP_8 | FCML_OA_W )
#define FCML_OP_MODRM_RM_XMM_OP_8_RW	( FCML_OP_MODRM_RM_XMM_OP_8 | FCML_OA_RW )
#define FCML_OP_MODRM_M_YMM_256			FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_YWORD, FCML_EOS_YWORD, FCML_RMF_M )
#define FCML_OP_MODRM_M_YMM_256_W		( FCML_OP_MODRM_RM_YMM_256 | FCML_OA_W )
#define FCML_OP_MODRM_M_YMM_256_RW		( FCML_OP_MODRM_RM_YMM_256 | FCML_OA_RW )
#define FCML_OP_MODRM_M_XMM_128			FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_OWORD, FCML_EOS_OWORD, FCML_RMF_M )
#define FCML_OP_MODRM_M_XMM_128_W		( FCML_OP_MODRM_RM_XMM_128 | FCML_OA_W )
#define FCML_OP_MODRM_M_XMM_128_RW		( FCML_OP_MODRM_RM_XMM_128 | FCML_OA_RW )
#define FCML_OP_MODRM_M_XMM_64			FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_OWORD, FCML_EOS_QWORD, FCML_RMF_M )
#define FCML_OP_MODRM_M_XMM_64_W		( FCML_OP_MODRM_RM_XMM_64 | FCML_OA_W )
#define FCML_OP_MODRM_M_XMM_64_RW		( FCML_OP_MODRM_RM_XMM_64 | FCML_OA_RW )
#define FCML_OP_MODRM_M_XMM_32			FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_OWORD, FCML_EOS_DWORD, FCML_RMF_M )
#define FCML_OP_MODRM_M_XMM_32_W		( FCML_OP_MODRM_RM_XMM_32 | FCML_OA_W )
#define FCML_OP_MODRM_M_XMM_32_RW		( FCML_OP_MODRM_RM_XMM_32 | FCML_OA_RW )
#define FCML_OP_MODRM_M_XMM_16			FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_OWORD, FCML_EOS_WORD, FCML_RMF_M )
#define FCML_OP_MODRM_M_XMM_16_W		( FCML_OP_MODRM_RM_XMM_16 | FCML_OA_W )
#define FCML_OP_MODRM_M_XMM_16_RW		( FCML_OP_MODRM_RM_XMM_16 | FCML_OA_RW )

#define FCML_OP_MODRM_R_XMM             FCML_OP_R(FCML_REG_SIMD, FCML_EOS_OWORD )
#define FCML_OP_MODRM_R_XMM_W           ( FCML_OP_MODRM_R_XMM | FCML_OA_W )
#define FCML_OP_MODRM_R_XMM_RW          ( FCML_OP_MODRM_R_XMM | FCML_OA_RW )
#define FCML_OP_MODRM_R_YMM             FCML_OP_R(FCML_REG_SIMD, FCML_EOS_YWORD )
#define FCML_OP_MODRM_R_YMM_W           ( FCML_OP_MODRM_R_YMM | FCML_OA_W )
#define FCML_OP_MODRM_R_YMM_RW          ( FCML_OP_MODRM_R_YMM | FCML_OA_RW )

#define FCML_OP_MODRM_RM_SIMD_L         	FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_L, FCML_EOS_L, FCML_RMF_RM )
#define FCML_OP_MODRM_RM_SIMD_L_W			( FCML_OP_MODRM_RM_SIMD_L | FCML_OA_W )
#define FCML_OP_MODRM_RM_SIMD_L_RW			( FCML_OP_MODRM_RM_SIMD_L | FCML_OA_RW )
#define FCML_OP_MODRM_RM_SIMD_L_128	    	FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_L, FCML_EOS_OWORD, FCML_RMF_RM )
#define FCML_OP_MODRM_RM_SIMD_L_128_W		( FCML_OP_MODRM_RM_SIMD_L_128 | FCML_OA_W )
#define FCML_OP_MODRM_RM_SIMD_L_128_RW		( FCML_OP_MODRM_RM_SIMD_L_128 | FCML_OA_RW )
#define FCML_OP_MODRM_RM_SIMD_L_64			FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_L, FCML_EOS_QWORD, FCML_RMF_RM )
#define FCML_OP_MODRM_RM_SIMD_L_64_W		( FCML_OP_MODRM_RM_SIMD_L_64 | FCML_OA_W )
#define FCML_OP_MODRM_RM_SIMD_L_64_RW		( FCML_OP_MODRM_RM_SIMD_L_64 | FCML_OA_RW )
#define FCML_OP_MODRM_RM_SIMD_L_32			FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_L, FCML_EOS_DWORD, FCML_RMF_RM )
#define FCML_OP_MODRM_RM_SIMD_L_32_W		( FCML_OP_MODRM_RM_SIMD_L_32 | FCML_OA_W )
#define FCML_OP_MODRM_RM_SIMD_L_32_RW		( FCML_OP_MODRM_RM_SIMD_L_32 | FCML_OA_RW )
#define FCML_OP_MODRM_RM_SIMD_L_16			FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_L, FCML_EOS_WORD, FCML_RMF_RM )
#define FCML_OP_MODRM_RM_SIMD_L_16_W		( FCML_OP_MODRM_RM_SIMD_L_16 | FCML_OA_W )
#define FCML_OP_MODRM_RM_SIMD_L_16_RW		( FCML_OP_MODRM_RM_SIMD_L_16 | FCML_OA_RW )
#define FCML_OP_MODRM_RM_SIMD_L_8			FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_L, FCML_EOS_BYTE, FCML_RMF_RM )
#define FCML_OP_MODRM_RM_SIMD_L_8_W	    	( FCML_OP_MODRM_RM_SIMD_L_8 | FCML_OA_W )
#define FCML_OP_MODRM_RM_SIMD_L_8_RW	    ( FCML_OP_MODRM_RM_SIMD_L_8 | FCML_OA_RW )
#define FCML_OP_MODRM_RM_SIMD_L_OP      	FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_L, FCML_EOS_L | FCML_EOS_OPT, FCML_RMF_RM )
#define FCML_OP_MODRM_RM_SIMD_L_OP_W		( FCML_OP_MODRM_RM_SIMD_L_OP | FCML_OA_W )
#define FCML_OP_MODRM_RM_SIMD_L_OP_RW		( FCML_OP_MODRM_RM_SIMD_L_OP | FCML_OA_RW )
#define FCML_OP_MODRM_RM_SIMD_L_OP_128		FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_L, FCML_EOS_OWORD | FCML_EOS_OPT, FCML_RMF_RM )
#define FCML_OP_MODRM_RM_SIMD_L_OP_128_W	( FCML_OP_MODRM_RM_SIMD_L_OP_128 | FCML_OA_W )
#define FCML_OP_MODRM_RM_SIMD_L_OP_128_RW	( FCML_OP_MODRM_RM_SIMD_L_OP_128 | FCML_OA_RW )
#define FCML_OP_MODRM_RM_SIMD_L_OP_64		FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_L, FCML_EOS_QWORD | FCML_EOS_OPT, FCML_RMF_RM )
#define FCML_OP_MODRM_RM_SIMD_L_OP_64_W		( FCML_OP_MODRM_RM_SIMD_L_OP_64 | FCML_OA_W )
#define FCML_OP_MODRM_RM_SIMD_L_OP_64_RW	( FCML_OP_MODRM_RM_SIMD_L_OP_64 | FCML_OA_RW )
#define FCML_OP_MODRM_RM_SIMD_L_OP_32		FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_L, FCML_EOS_DWORD | FCML_EOS_OPT, FCML_RMF_RM )
#define FCML_OP_MODRM_RM_SIMD_L_OP_32_W		( FCML_OP_MODRM_RM_SIMD_L_OP_32 | FCML_OA_W )
#define FCML_OP_MODRM_RM_SIMD_L_OP_32_RW	( FCML_OP_MODRM_RM_SIMD_L_OP_32 | FCML_OA_RW )
#define FCML_OP_MODRM_RM_SIMD_L_OP_16		FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_L, FCML_EOS_WORD | FCML_EOS_OPT, FCML_RMF_RM )
#define FCML_OP_MODRM_RM_SIMD_L_OP_16_W		( FCML_OP_MODRM_RM_SIMD_L_OP_16 | FCML_OA_W )
#define FCML_OP_MODRM_RM_SIMD_L_OP_16_RW	( FCML_OP_MODRM_RM_SIMD_L_OP_16 | FCML_OA_RW )
#define FCML_OP_MODRM_RM_SIMD_L_OP_8		FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_L, FCML_EOS_BYTE | FCML_EOS_OPT, FCML_RMF_RM )
#define FCML_OP_MODRM_RM_SIMD_L_OP_8_W		( FCML_OP_MODRM_RM_SIMD_L_OP_8 | FCML_OA_W )
#define FCML_OP_MODRM_RM_SIMD_L_OP_8_RW		( FCML_OP_MODRM_RM_SIMD_L_OP_8 | FCML_OA_RW )

#define FCML_OP_MODRM_RM_SIMD_E			FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_EOSA, FCML_EOS_EOSA, FCML_RMF_RM )
#define FCML_OP_MODRM_RM_SIMD_E_W		( FCML_OP_MODRM_RM_SIMD_E | FCML_OA_W )
#define FCML_OP_MODRM_RM_SIMD_E_RW		( FCML_OP_MODRM_RM_SIMD_E | FCML_OA_RW )
#define FCML_OP_MODRM_RM_SIMD_E_128		FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_EOSA, FCML_EOS_OWORD, FCML_RMF_RM )
#define FCML_OP_MODRM_RM_SIMD_E_128_W	( FCML_OP_MODRM_RM_SIMD_E_128 | FCML_OA_W )
#define FCML_OP_MODRM_RM_SIMD_E_128_RW	( FCML_OP_MODRM_RM_SIMD_E_128 | FCML_OA_RW )
#define FCML_OP_MODRM_RM_SIMD_E_64		FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_EOSA, FCML_EOS_QWORD, FCML_RMF_RM )
#define FCML_OP_MODRM_RM_SIMD_E_64_W	( FCML_OP_MODRM_RM_SIMD_E_64 | FCML_OA_W )
#define FCML_OP_MODRM_RM_SIMD_E_64_RW	( FCML_OP_MODRM_RM_SIMD_E_64 | FCML_OA_RW )
#define FCML_OP_MODRM_RM_SIMD_E_32		FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_EOSA, FCML_EOS_DWORD, FCML_RMF_RM )
#define FCML_OP_MODRM_RM_SIMD_E_32_W	( FCML_OP_MODRM_RM_SIMD_E_32 | FCML_OA_W )
#define FCML_OP_MODRM_RM_SIMD_E_32_RW	( FCML_OP_MODRM_RM_SIMD_E_32 | FCML_OA_RW )
#define FCML_OP_MODRM_RM_SIMD_E_16		FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_EOSA, FCML_EOS_WORD, FCML_RMF_RM )
#define FCML_OP_MODRM_RM_SIMD_E_16_W	( FCML_OP_MODRM_RM_SIMD_E_16 | FCML_OA_W )
#define FCML_OP_MODRM_RM_SIMD_E_16_RW	( FCML_OP_MODRM_RM_SIMD_E_16 | FCML_OA_RW )
#define FCML_OP_MODRM_RM_SIMD_E_8		FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_EOSA, FCML_EOS_BYTE, FCML_RMF_RM )
#define FCML_OP_MODRM_RM_SIMD_E_8_W		( FCML_OP_MODRM_RM_SIMD_E_8 | FCML_OA_W )
#define FCML_OP_MODRM_RM_SIMD_E_8_RW	( FCML_OP_MODRM_RM_SIMD_E_8 | FCML_OA_RW )

#define FCML_OP_MODRM_R_SIMD_L			FCML_OP_R(FCML_REG_SIMD, FCML_EOS_L )
#define FCML_OP_MODRM_R_SIMD_L_W		( FCML_OP_MODRM_R_SIMD_L | FCML_OA_W )
#define FCML_OP_MODRM_R_SIMD_L_RW		( FCML_OP_MODRM_R_SIMD_L | FCML_OA_RW )
#define FCML_OP_MODRM_R_SIMD_E			FCML_OP_R(FCML_REG_SIMD, FCML_EOS_EOSA )
#define FCML_OP_MODRM_R_SIMD_E_W		( FCML_OP_MODRM_R_SIMD_E | FCML_OA_W )
#define FCML_OP_MODRM_R_SIMD_E_RW		( FCML_OP_MODRM_R_SIMD_E | FCML_OA_RW )
#define FCML_OP_MODRM_M_SIMD_L			FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_UNDEFINED, FCML_EOS_L, FCML_RMF_M )
#define FCML_OP_MODRM_M_SIMD_L_W		( FCML_OP_MODRM_M_SIMD_L | FCML_OA_W )
#define FCML_OP_MODRM_M_SIMD_L_RW		( FCML_OP_MODRM_M_SIMD_L | FCML_OA_RW )
#define FCML_OP_MODRM_M_SIMD_E			FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_UNDEFINED, FCML_EOS_EOSA, FCML_RMF_M )
#define FCML_OP_MODRM_M_SIMD_E_W		( FCML_OP_MODRM_M_SIMD | FCML_OA_W )
#define FCML_OP_MODRM_M_SIMD_E_RW		( FCML_OP_MODRM_M_SIMD | FCML_OA_RW )
#define FCML_OP_MODRM_M_SIMD_OPL		FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_UNDEFINED, FCML_EOS_L | FCML_EOS_OPT, FCML_RMF_M )
#define FCML_OP_MODRM_M_SIMD_OPL_W		( FCML_OP_MODRM_M_SIMD_OPL | FCML_OA_W )
#define FCML_OP_MODRM_M_SIMD_OPL_RW		( FCML_OP_MODRM_M_SIMD_OPL | FCML_OA_RW )
#define FCML_OP_MODRM_M_SIMD_OPE		FCML_OP_RM(FCML_REG_SIMD, FCML_EOS_UNDEFINED, FCML_EOS_EOSA | FCML_EOS_OPT, FCML_RMF_M )
#define FCML_OP_MODRM_M_SIMD_OPE_W		( FCML_OP_MODRM_M_SIMD_OPE | FCML_OA_W )
#define FCML_OP_MODRM_M_SIMD_OPE_RW		( FCML_OP_MODRM_M_SIMD_OPE | FCML_OA_RW )

/* Shorthands for relative addressing.*/

#define FCML_OP_IMMEDIATE_DIS_RELATIVE_EOSA		FCML_OP_IMMEDIATE_DIS_RELATIVE( FCML_EOS_UNDEFINED )
#define FCML_OP_IMMEDIATE_DIS_RELATIVE_R_8		FCML_OP_IMMEDIATE_DIS_RELATIVE( FCML_EOS_BYTE )

/* Shorthands for VVVV addressing.*/

#define FCML_OP_VEX_VVVV_SIMD_REG		FCML_OP_VEX_VVVV_REG( FCML_REG_SIMD, FCML_EOS_L )
#define FCML_OP_VEX_VVVV_XMM_REG		FCML_OP_VEX_VVVV_REG( FCML_REG_SIMD, FCML_EOS_OWORD )
#define FCML_OP_VEX_VVVV_YMM_REG		FCML_OP_VEX_VVVV_REG( FCML_REG_SIMD, FCML_EOS_YWORD )

/* Shorthands for IMM.*/

#define FCML_OP_IB						FCML_OP_IMM( FCML_EOS_BYTE, FCML_EOS_UNDEFINED )
#define FCML_OP_IB_EX_EOSA				FCML_OP_IMM( FCML_EOS_BYTE, FCML_EOS_EOSA )
#define FCML_OP_IW						FCML_OP_IMM( FCML_EOS_WORD, FCML_EOS_UNDEFINED )
#define FCML_OP_IW_EX_EOSA				FCML_OP_IMM( FCML_EOS_WORD, FCML_EOS_EOSA )
#define FCML_OP_ID						FCML_OP_IMM( FCML_EOS_DWORD, FCML_EOS_UNDEFINED )
#define FCML_OP_ID_EX_EOSA				FCML_OP_IMM( FCML_EOS_DWORD, FCML_EOS_EOSA )
#define FCML_OP_EX_EOSA					FCML_OP_IMM( FCML_EOS_EOSA, FCML_EOS_EOSA )
#define FCML_OP_IMM_EOSA				FCML_OP_IMM( FCML_EOS_EOSA, FCML_EOS_UNDEFINED )

/* Externals. */

extern struct fcml_st_def_instruction_desc fcml_ext_instructions_def[];

#define FCML_EMPTY_MNEMONIC	FCML_TEXT("")

/* Addressing modes arguments encoders. */

typedef struct fcml_st_def_decoded_addr_mode {
    /* Code of the addressing mode.*/
    fcml_uint8_t addr_mode;
    fcml_en_access_mode access_mode;
    /* Decoded arguments.*/
    fcml_ptr addr_mode_args;
} fcml_st_def_decoded_addr_mode;

fcml_st_def_decoded_addr_mode* fcml_fnp_def_decode_addr_mode_args(
        fcml_uint32_t encoded_addr_mode, fcml_ceh_error *error);

void fcml_fnp_def_free_addr_mode(
        fcml_st_def_decoded_addr_mode *decoded_addr_mode);

/* Addressing modes arguments. */

#define FCML_GET_ADDR_MODE(x) 	( ( x ) & 0x3F000000 ) >> 24

typedef struct fcml_sf_def_tma_imm {
    fcml_uint8_t encoded_imm_size;
    fcml_uint8_t encoded_ex_imm_size;
    fcml_bool is_64bit_imm_allowed;
} fcml_sf_def_tma_imm;

typedef struct fcml_sf_def_tma_explicit_reg {
    fcml_uint8_t reg_type;
    fcml_uint8_t reg_num;
    fcml_uint8_t encoded_reg_size;
} fcml_sf_def_tma_explicit_reg;

typedef struct fcml_sf_def_tma_opcode_reg {
    fcml_uint8_t reg_type;
    fcml_uint8_t encoded_reg_size;
} fcml_sf_def_tma_opcode_reg;

typedef struct fcml_sf_def_tma_immediate_dis_relative {
    fcml_uint8_t encoded_imm_size;
} fcml_sf_def_tma_immediate_dis_relative;

typedef struct fcml_sf_def_tma_explicit_gps_reg_addressing {
    fcml_uint8_t reg_num;
    fcml_uint8_t encoded_operand_size;
    fcml_uint8_t encoded_segment_register;
} fcml_sf_def_tma_explicit_gps_reg_addressing;

typedef struct fcml_sf_def_tma_explicit_ib {
    fcml_uint8_t ib;
} fcml_sf_def_tma_explicit_ib;

typedef struct fcml_sf_def_tma_segment_relative_offset {
    fcml_uint8_t encoded_operand_size;
    fcml_uint8_t encoded_segment_register;
} fcml_sf_def_tma_segment_relative_offset;

typedef struct fcml_sf_def_tma_rm {
    fcml_uint8_t reg_type;
    fcml_uint8_t encoded_register_operand_size;
    fcml_uint8_t encoded_memory_operand_size;
    fcml_uint8_t flags;
    fcml_uint8_t vector_index_register;
    fcml_bool is_vsib;
} fcml_sf_def_tma_rm;

typedef struct fcml_sf_def_tma_r {
    fcml_en_register reg_type;
    fcml_uint8_t encoded_register_operand_size;
} fcml_sf_def_tma_r;

typedef struct fcml_sf_def_tma_vex_vvvv_reg {
    fcml_uint8_t reg_type;
    fcml_uint8_t encoded_register_size;
} fcml_sf_def_tma_vex_vvvv_reg;

typedef struct fcml_sf_def_tma_pseudo_op {
    fcml_uint8_t mask;
} fcml_sf_def_tma_pseudo_op;

typedef struct fcml_sf_def_tma_is {
    fcml_uint8_t flags;
} fcml_sf_def_tma_is;

#endif /* FCML_DEF_H_ */
