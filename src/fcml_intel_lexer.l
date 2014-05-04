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
  
%{
	#include <stdio.h>
	#include <stdlib.h>
	
	#include "fcml_common_lex.h"
	#include "fcml_intel_parser_def.h"
%}

%option noyywrap
%option nounput
%option noinput
%option noyyalloc
%option noyyrealloc
%option noyyfree
%option batch
%option nodefault
%option never-interactive
%option case-insensitive
%option 8bit 
%option reentrant
%option bison-bridge
%option outfile="fcml_intel_lexer.c"
%option header-file="fcml_intel_lexer.h"
%option nounistd
%option prefix="intel_"

%option extra-type="struct fcml_st_parser_data *"

%{
	#define FCML_FM_SIZE_OPERAND(x) 				{ yylval->size_operator.size = x; yylval->size_operator.multimedia = FCML_FALSE; return FCML_TK_SIZE_OPERATOR;  }
	#define FCML_FM_MULTIMEDIA_SIZE_OPERAND(x)		{ yylval->size_operator.size = x; yylval->size_operator.multimedia = FCML_TRUE; return FCML_TK_SIZE_OPERATOR; }
%}

/*White spaces.*/
WS	[ \t]*
PTR	(" ptr")?

%%

 /* Decimal integers. */
[0-9]+d? 				{ fcml_fn_pu_parse_integer( yytext, &(yylval->integer_value), 10 ); return FCML_TK_INTEGER; }

 /* HEX integers. */
0x[0-9a-f]+ 			|
0[a-f][0-9a-f]+h		|
[0-9][0-9a-f]*h			{ fcml_fn_pu_parse_integer( yytext, &(yylval->integer_value), 16 ); return FCML_TK_INTEGER; }

 /* Floating-points in IEEE 754.
 Floats are not supported yet.
([0-9]*\.[0-9]+|[0-9]+\.)(e[-+]?[0-9]+)?f? |
[0-9]+(e[-+]?[0-9]+)f?	{ fcml_fn_pu_parse_float( yytext, &(yylval->float_value) ); return FCML_TK_FLOAT; }
 */

 /* GPR. */
"al"					FCML_FM_GPRS_8_REG(FCML_REG_AL)
"cl"					FCML_FM_GPRS_8_REG(FCML_REG_CL)
"dl"					FCML_FM_GPRS_8_REG(FCML_REG_DL)
"bl"					FCML_FM_GPRS_8_REG(FCML_REG_BL)
"ah"					FCML_FM_GPRS_8_REG(FCML_REG_AH)
"ch"					FCML_FM_GPRS_8_REG(FCML_REG_CH)
"dh"					FCML_FM_GPRS_8_REG(FCML_REG_DH)
"bh"					FCML_FM_GPRS_8_REG(FCML_REG_BH)
"r8l"					FCML_FM_GPRS_8_REG(FCML_REG_R8L)
"r9l"					FCML_FM_GPRS_8_REG(FCML_REG_R9L)
"r10l"					FCML_FM_GPRS_8_REG(FCML_REG_R10L)
"r11l"					FCML_FM_GPRS_8_REG(FCML_REG_R11L)
"r12l"					FCML_FM_GPRS_8_REG(FCML_REG_R12L)
"r13l"					FCML_FM_GPRS_8_REG(FCML_REG_R13L)
"r14l"					FCML_FM_GPRS_8_REG(FCML_REG_R14L)
"r15l"					FCML_FM_GPRS_8_REG(FCML_REG_R15L)

"spl"					FCML_FM_GPRS_8_X_REG(FCML_REG_SPL)
"bpl"					FCML_FM_GPRS_8_X_REG(FCML_REG_BPL)
"sil"					FCML_FM_GPRS_8_X_REG(FCML_REG_SIL)
"dil"					FCML_FM_GPRS_8_X_REG(FCML_REG_DIL)

"ax"					FCML_FM_GPRS_16_REG(FCML_REG_AX)
"cx"					FCML_FM_GPRS_16_REG(FCML_REG_CX)
"dx"					FCML_FM_GPRS_16_REG(FCML_REG_DX)
"bx"					FCML_FM_GPRS_16_REG(FCML_REG_BX)
"sp"					FCML_FM_GPRS_16_REG(FCML_REG_SP)
"bp"					FCML_FM_GPRS_16_REG(FCML_REG_BP)
"si"					FCML_FM_GPRS_16_REG(FCML_REG_SI)
"di"					FCML_FM_GPRS_16_REG(FCML_REG_DI)
"r8w"					FCML_FM_GPRS_16_REG(FCML_REG_R8W)
"r9w"					FCML_FM_GPRS_16_REG(FCML_REG_R9W)
"r10w"					FCML_FM_GPRS_16_REG(FCML_REG_R10W)
"r11w"					FCML_FM_GPRS_16_REG(FCML_REG_R11W)
"r12w"					FCML_FM_GPRS_16_REG(FCML_REG_R12W)
"r13w"					FCML_FM_GPRS_16_REG(FCML_REG_R13W)
"r14w"					FCML_FM_GPRS_16_REG(FCML_REG_R14W)
"r15w"					FCML_FM_GPRS_16_REG(FCML_REG_R15W)

"eax"					FCML_FM_GPRS_32_REG(FCML_REG_EAX)
"ecx"					FCML_FM_GPRS_32_REG(FCML_REG_ECX)
"edx"					FCML_FM_GPRS_32_REG(FCML_REG_EDX)
"ebx"					FCML_FM_GPRS_32_REG(FCML_REG_EBX)
"esp"					FCML_FM_GPRS_32_REG(FCML_REG_ESP)
"ebp"					FCML_FM_GPRS_32_REG(FCML_REG_EBP)
"esi"					FCML_FM_GPRS_32_REG(FCML_REG_ESI)
"edi"					FCML_FM_GPRS_32_REG(FCML_REG_EDI)
"r8d"					FCML_FM_GPRS_32_REG(FCML_REG_R8D)
"r9d"					FCML_FM_GPRS_32_REG(FCML_REG_R9D)
"r10d"					FCML_FM_GPRS_32_REG(FCML_REG_R10D)
"r11d"					FCML_FM_GPRS_32_REG(FCML_REG_R11D)
"r12d"					FCML_FM_GPRS_32_REG(FCML_REG_R12D)
"r13d"					FCML_FM_GPRS_32_REG(FCML_REG_R13D)
"r14d"					FCML_FM_GPRS_32_REG(FCML_REG_R14D)
"r15d"					FCML_FM_GPRS_32_REG(FCML_REG_R15D)

"rax"                   FCML_FM_GPRS_64_REG(FCML_REG_RAX)
"rcx"                   FCML_FM_GPRS_64_REG(FCML_REG_RCX)
"rdx"                   FCML_FM_GPRS_64_REG(FCML_REG_RDX)
"rbx"                   FCML_FM_GPRS_64_REG(FCML_REG_RBX)
"rsp"                   FCML_FM_GPRS_64_REG(FCML_REG_RSP)
"rbp"                   FCML_FM_GPRS_64_REG(FCML_REG_RBP)
"rsi"                   FCML_FM_GPRS_64_REG(FCML_REG_RSI)
"rdi"                   FCML_FM_GPRS_64_REG(FCML_REG_RDI)
"r8"                    FCML_FM_GPRS_64_REG(FCML_REG_R8)
"r9"                    FCML_FM_GPRS_64_REG(FCML_REG_R9)
"r10"                   FCML_FM_GPRS_64_REG(FCML_REG_R10)
"r11"                   FCML_FM_GPRS_64_REG(FCML_REG_R11)
"r12"                   FCML_FM_GPRS_64_REG(FCML_REG_R12)
"r13"                   FCML_FM_GPRS_64_REG(FCML_REG_R13)
"r14"                   FCML_FM_GPRS_64_REG(FCML_REG_R14)
"r15"                   FCML_FM_GPRS_64_REG(FCML_REG_R15)

 /* SIMD-MMX */
"mm0"					FCML_FM_SIMD_64_REG(FCML_REG_MM0)
"mm1"					FCML_FM_SIMD_64_REG(FCML_REG_MM1)
"mm2"					FCML_FM_SIMD_64_REG(FCML_REG_MM2)
"mm3"					FCML_FM_SIMD_64_REG(FCML_REG_MM3)
"mm4"					FCML_FM_SIMD_64_REG(FCML_REG_MM4)
"mm5"					FCML_FM_SIMD_64_REG(FCML_REG_MM5)
"mm6"					FCML_FM_SIMD_64_REG(FCML_REG_MM6)
"mm7"					FCML_FM_SIMD_64_REG(FCML_REG_MM7)

 /* SIMD-XMM */
"xmm0"					FCML_FM_SIMD_128_REG(FCML_REG_XMM0)
"xmm1"					FCML_FM_SIMD_128_REG(FCML_REG_XMM1)
"xmm2"					FCML_FM_SIMD_128_REG(FCML_REG_XMM2)
"xmm3"					FCML_FM_SIMD_128_REG(FCML_REG_XMM3)
"xmm4"					FCML_FM_SIMD_128_REG(FCML_REG_XMM4)
"xmm5"					FCML_FM_SIMD_128_REG(FCML_REG_XMM5)
"xmm6"					FCML_FM_SIMD_128_REG(FCML_REG_XMM6)
"xmm7"					FCML_FM_SIMD_128_REG(FCML_REG_XMM7)
"xmm8"					FCML_FM_SIMD_128_REG(FCML_REG_XMM8)
"xmm9"					FCML_FM_SIMD_128_REG(FCML_REG_XMM9)
"xmm10"					FCML_FM_SIMD_128_REG(FCML_REG_XMM10)
"xmm11"					FCML_FM_SIMD_128_REG(FCML_REG_XMM11)
"xmm12"					FCML_FM_SIMD_128_REG(FCML_REG_XMM12)
"xmm13"					FCML_FM_SIMD_128_REG(FCML_REG_XMM13)
"xmm14"					FCML_FM_SIMD_128_REG(FCML_REG_XMM14)
"xmm15"					FCML_FM_SIMD_128_REG(FCML_REG_XMM15)

 /* SIMD-YMM */
"ymm0"                  FCML_FM_SIMD_256_REG(FCML_REG_YMM0)
"ymm1"                  FCML_FM_SIMD_256_REG(FCML_REG_YMM1)
"ymm2"                  FCML_FM_SIMD_256_REG(FCML_REG_YMM2)
"ymm3"                  FCML_FM_SIMD_256_REG(FCML_REG_YMM3)
"ymm4"                  FCML_FM_SIMD_256_REG(FCML_REG_YMM4)
"ymm5"                  FCML_FM_SIMD_256_REG(FCML_REG_YMM5)
"ymm6"                  FCML_FM_SIMD_256_REG(FCML_REG_YMM6)
"ymm7"                  FCML_FM_SIMD_256_REG(FCML_REG_YMM7)
"ymm8"                  FCML_FM_SIMD_256_REG(FCML_REG_YMM8)
"ymm9"                  FCML_FM_SIMD_256_REG(FCML_REG_YMM9)
"ymm10"                 FCML_FM_SIMD_256_REG(FCML_REG_YMM10)
"ymm11"                 FCML_FM_SIMD_256_REG(FCML_REG_YMM11)
"ymm12"                 FCML_FM_SIMD_256_REG(FCML_REG_YMM12)
"ymm13"                 FCML_FM_SIMD_256_REG(FCML_REG_YMM13)
"ymm14"                 FCML_FM_SIMD_256_REG(FCML_REG_YMM14)
"ymm15"                 FCML_FM_SIMD_256_REG(FCML_REG_YMM15)

 /* FPU */
st{WS}("("{WS}0{WS}")"|0)	FCML_FM_FPU_REG(FCML_REG_ST0)				
st{WS}("("{WS}1{WS}")"|1)	FCML_FM_FPU_REG(FCML_REG_ST1)
st{WS}("("{WS}2{WS}")"|2)	FCML_FM_FPU_REG(FCML_REG_ST2)
st{WS}("("{WS}3{WS}")"|3)	FCML_FM_FPU_REG(FCML_REG_ST3)
st{WS}("("{WS}4{WS}")"|4)	FCML_FM_FPU_REG(FCML_REG_ST4)
st{WS}("("{WS}5{WS}")"|5)	FCML_FM_FPU_REG(FCML_REG_ST5)
st{WS}("("{WS}6{WS}")"|6)	FCML_FM_FPU_REG(FCML_REG_ST6)
st{WS}("("{WS}7{WS}")"|7)	FCML_FM_FPU_REG(FCML_REG_ST7)

 /* Control registers. */
"cr0"			FCML_FM_CR_REG(FCML_REG_CR0)
"cr2"			FCML_FM_CR_REG(FCML_REG_CR2)
"cr3"			FCML_FM_CR_REG(FCML_REG_CR3)
"cr4"			FCML_FM_CR_REG(FCML_REG_CR4)
"cr8"			FCML_FM_CR_REG(FCML_REG_CR8)

 /* Debug registers. */
"dr0"			FCML_FM_DR_REG(FCML_REG_DR0)
"dr1"			FCML_FM_DR_REG(FCML_REG_DR1)
"dr2"			FCML_FM_DR_REG(FCML_REG_DR2)
"dr3"			FCML_FM_DR_REG(FCML_REG_DR3)
"dr4"			FCML_FM_DR_REG(FCML_REG_DR4)
"dr5"			FCML_FM_DR_REG(FCML_REG_DR5)
"dr6"			FCML_FM_DR_REG(FCML_REG_DR6)
"dr7"			FCML_FM_DR_REG(FCML_REG_DR7)

 /* Segment registers. */
"es"			FCML_FM_SEG_REG(FCML_REG_ES)
"cs"			FCML_FM_SEG_REG(FCML_REG_CS)
"ss"			FCML_FM_SEG_REG(FCML_REG_SS)
"ds"			FCML_FM_SEG_REG(FCML_REG_DS)
"fs"			FCML_FM_SEG_REG(FCML_REG_FS)
"gs"			FCML_FM_SEG_REG(FCML_REG_GS)

 /* RIP */
"rip"			FCML_FM_RIP

 /* Size operators. */
"byte"{PTR}						FCML_FM_SIZE_OPERAND( 8 )
"word"{PTR}						FCML_FM_SIZE_OPERAND( 16 )
"dword"{PTR}					FCML_FM_SIZE_OPERAND( 32 )
("fword"|"pword"){PTR}			FCML_FM_SIZE_OPERAND( 48 )
"qword"{PTR}					FCML_FM_SIZE_OPERAND( 64 )
("tbyte"|"tword"){PTR}			FCML_FM_SIZE_OPERAND( 80 )
("dqword"|"oword"){PTR}			FCML_FM_SIZE_OPERAND( 128 )
"qqword"{PTR} 					FCML_FM_SIZE_OPERAND( 256 )
"mmword"{PTR}					FCML_FM_MULTIMEDIA_SIZE_OPERAND( 64 )
("xword"|"xmmword"){PTR}		FCML_FM_MULTIMEDIA_SIZE_OPERAND( 128 )
("yword"|"ymmword"){PTR} 		FCML_FM_MULTIMEDIA_SIZE_OPERAND( 256 )
("14byte"){PTR} 				FCML_FM_SIZE_OPERAND( 14 * 8 )
("28byte"){PTR} 				FCML_FM_SIZE_OPERAND( 28 * 8 )
("94byte"){PTR} 				FCML_FM_SIZE_OPERAND( 94 * 8 )
("108byte"){PTR} 				FCML_FM_SIZE_OPERAND( 108 * 8 )

 /* Prefixes */
 
"lock"			{
					yylval->prefixes = FCML_PREFIX_LOCK;
					return FCML_TK_PREFIX;
				}
				
"repne"|"repnz" {
					yylval->prefixes = FCML_PREFIX_REPNE;
					return FCML_TK_PREFIX;
				}
				
"repe"|"repz"|"rep" {
					yylval->prefixes = FCML_PREFIX_REPE;
					return FCML_TK_PREFIX;
				}
				
"xacquire"      {
					yylval->prefixes = FCML_PREFIX_XACQUIRE;
					return FCML_TK_PREFIX;
				}
				
"xrelease"      {
					yylval->prefixes = FCML_PREFIX_XRELEASE;
					return FCML_TK_PREFIX;
				}
				
"branch"		{
					yylval->hints = FCML_PREFIX_BRANCH_HINT;
					return FCML_TK_PREFIX;
				}

"nobranch"		{
					yylval->hints = FCML_PREFIX_NOBRANCH_HINT;
					return FCML_TK_PREFIX;
				}
				
 /* Hints */

"far"			{
					yylval->hints = FCML_HINT_FAR_POINTER;
					return FCML_TK_HINTS;
				} 
				
"near"			{
					yylval->hints = FCML_HINT_NEAR_POINTER;
					return FCML_TK_HINTS;
				}
				
"long_form"		{
					yylval->hints = FCML_HINT_LONG_FORM_POINTER;
					return FCML_TK_HINTS;
				}
				
"indirect"		{
					yylval->hints = FCML_HINT_INDIRECT_POINTER;
					return FCML_TK_HINTS;
				}
				
"direct"        {
                    yylval->hints = FCML_HINT_DIRECT_POINTER;
                    return FCML_TK_HINTS;
                }

"rel"			{
					yylval->hints = FCML_OP_HINT_RELATIVE_ADDRESSING;
					return FCML_TK_EAO_HINTS;
				}
				
"abs"			{
					yylval->hints = FCML_OP_HINT_ABSOLUTE_ADDRESSING;
					return FCML_TK_EAO_HINTS;
				}
				
"sib"			{
					yylval->hints = FCML_OP_HINT_SIB_ENCODING;
					return FCML_TK_SIB_HINT;
				}

 /* Identifiers. */
[a-z_][0-9a-z_]*	{
					yylval->symbol.text = (fcml_string)yytext;
					yylval->symbol.length = yyleng;
					return FCML_TK_SYMBOL; 
				}

 /* Operators and parentheses. */
","		{ return ','; }
"+"		{ return '+'; }
"-"		{ return '-'; }
"*"		{ return '*'; }
"/"		{ return '/'; }
"["		{ return '['; }
"]"		{ return ']'; }
"("		{ return '('; }
")"		{ return ')'; }
":"		{ return ':'; }

 /* Ignore white spaces. */
{WS}	

 /* Anything else is not expected. */
.		{ return FCML_TK_UNEXPECTED; }

 /* Ignore like white spaces. */
\n		

%%

