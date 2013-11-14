%{
	#include <stdio.h>
	#include <stdlib.h>
	#include "fcml_common.h"
	#include "fcml_env.h"
	#include "fcml_types.h"
	#include "fcml_parser_utils.h"
	#include "fcml_x64att_parser.tab.h"
%}

%option noyywrap
%option nounput
%option noinput
%option batch
%option nodefault
%option never-interactive
%option case-insensitive
%option 8bit 
%option reentrant
%option bison-bridge
%option outfile="fcml_x64att_lexer.c"
%option header-file="fcml_x64att_lexer.h"
%option nounistd
%option prefix="att_"

%option extra-type="struct fcml_st_parser_data *"

%{
	/*GPR*/
	#define FCML_FM_GPRS_8_REG(x)	fcml_fn_pu_parse_register( FCML_REG_GPR, FCML_DS_8, x, FCML_FALSE, &(yylval->reg_value) )
	#define FCML_FM_GPRS_8_X_REG(x)	fcml_fn_pu_parse_register( FCML_REG_GPR, FCML_DS_8, x, FCML_TRUE, &(yylval->reg_value) )
	#define FCML_FM_GPRS_16_REG(x)	fcml_fn_pu_parse_register( FCML_REG_GPR, FCML_DS_16, x, FCML_FALSE, &(yylval->reg_value) )
	#define FCML_FM_GPRS_32_REG(x)	fcml_fn_pu_parse_register( FCML_REG_GPR, FCML_DS_32, x, FCML_FALSE, &(yylval->reg_value) )
	#define FCML_FM_GPRS_64_REG(x)	fcml_fn_pu_parse_register( FCML_REG_GPR, FCML_DS_64, x, FCML_FALSE, &(yylval->reg_value) )
	/*SIMD*/
	#define FCML_FM_SIMD_64_REG(x)	fcml_fn_pu_parse_register( FCML_REG_SIMD, FCML_DS_64, x, FCML_FALSE, &(yylval->reg_value) )
	#define FCML_FM_SIMD_128_REG(x)	fcml_fn_pu_parse_register( FCML_REG_SIMD, FCML_DS_128, x, FCML_FALSE, &(yylval->reg_value) )
	#define FCML_FM_SIMD_256_REG(x)	fcml_fn_pu_parse_register( FCML_REG_SIMD, FCML_DS_256, x, FCML_FALSE, &(yylval->reg_value) )
	/*FPU*/
	#define FCML_FM_FPU_REG(x)		fcml_fn_pu_parse_register( FCML_REG_FPU, FCML_DS_UNDEF, x, FCML_FALSE, &(yylval->reg_value) )
	/*Control registers.*/
	#define FCML_FM_CR_REG(x)		fcml_fn_pu_parse_register( FCML_REG_CR, FCML_DS_UNDEF, x, FCML_FALSE, &(yylval->reg_value) )
	/*Debug registers.*/
	#define FCML_FM_DR_REG(x)		fcml_fn_pu_parse_register( FCML_REG_DR, FCML_DS_UNDEF, x, FCML_FALSE, &(yylval->reg_value) )
	/*Segment registers.*/
	#define FCML_FM_SEG_REG(x)		fcml_fn_pu_parse_register( FCML_REG_SEG, FCML_DS_UNDEF, x, FCML_FALSE, &(yylval->reg_value) )
	/*Size operands.*/
	#define FCML_FM_SIZE_OPERAND(x) { yylval->size_operator.size = x; yylval->size_operator.multimedia = FCML_FALSE; return FCML_TK_SIZE_OPERATOR;  }
	#define FCML_FM_MULTIMEDIA_SIZE_OPERAND(x) { yylval->size_operator.size = x; yylval->size_operator.multimedia = FCML_TRUE; return FCML_TK_SIZE_OPERATOR; }
%}

/*White spaces.*/
WS	[ \t]*
PTR	(" ptr")?

%%

 /*Decimal integers.*/
[0-9]+d? 				{ return fcml_fn_pu_parse_integer( yytext, &(yylval->integer_value), 10 ); }

 /*HEX integers.*/
0x[0-9a-f]+ 			|
0[a-f][0-9a-f]+h		|
[0-9][0-9a-f]*h			{ return fcml_fn_pu_parse_integer( yytext, &(yylval->integer_value), 16 ); }

 /*Floating-points in IEEE 754.*/
([0-9]*\.[0-9]+|[0-9]+\.)(e[-+]?[0-9]+)?f? |
[0-9]+(e[-+]?[0-9]+)f?	{ return fcml_fn_pu_parse_float( yytext, &(yylval->float_value) ); }

 /*GPR.*/
"al"					{ return FCML_FM_GPRS_8_REG(FCML_REG_AL); }
"cl"					{ return FCML_FM_GPRS_8_REG(FCML_REG_CL); }
"dl"					{ return FCML_FM_GPRS_8_REG(FCML_REG_DL); }
"bl"					{ return FCML_FM_GPRS_8_REG(FCML_REG_BL); }
"ah"					{ return FCML_FM_GPRS_8_REG(FCML_REG_AH); }
"ch"					{ return FCML_FM_GPRS_8_REG(FCML_REG_CH); }
"dh"					{ return FCML_FM_GPRS_8_REG(FCML_REG_DH); }
"bh"					{ return FCML_FM_GPRS_8_REG(FCML_REG_BH); }
"r8l"					{ return FCML_FM_GPRS_8_REG(FCML_REG_R8L); }
"r9l"					{ return FCML_FM_GPRS_8_REG(FCML_REG_R9L); }
"r10l"					{ return FCML_FM_GPRS_8_REG(FCML_REG_R10L); }
"r11l"					{ return FCML_FM_GPRS_8_REG(FCML_REG_R11L); }
"r12l"					{ return FCML_FM_GPRS_8_REG(FCML_REG_R12L); }
"r13l"					{ return FCML_FM_GPRS_8_REG(FCML_REG_R13L); }
"r14l"					{ return FCML_FM_GPRS_8_REG(FCML_REG_R14L); }
"r15l"					{ return FCML_FM_GPRS_8_REG(FCML_REG_R15L); }

"spl"					{ return FCML_FM_GPRS_8_X_REG(FCML_REG_SPL); }
"bpl"					{ return FCML_FM_GPRS_8_X_REG(FCML_REG_BPL); }
"sil"					{ return FCML_FM_GPRS_8_X_REG(FCML_REG_SIL); }
"dil"					{ return FCML_FM_GPRS_8_X_REG(FCML_REG_DIL); }

"ax"					{ return FCML_FM_GPRS_16_REG(FCML_REG_AX); }
"cx"					{ return FCML_FM_GPRS_16_REG(FCML_REG_CX); }
"dx"					{ return FCML_FM_GPRS_16_REG(FCML_REG_DX); }
"bx"					{ return FCML_FM_GPRS_16_REG(FCML_REG_BX); }
"sp"					{ return FCML_FM_GPRS_16_REG(FCML_REG_SP); }
"bp"					{ return FCML_FM_GPRS_16_REG(FCML_REG_BP); }
"si"					{ return FCML_FM_GPRS_16_REG(FCML_REG_SI); }
"di"					{ return FCML_FM_GPRS_16_REG(FCML_REG_DI); }
"r8w"					{ return FCML_FM_GPRS_16_REG(FCML_REG_R8W); }
"r9w"					{ return FCML_FM_GPRS_16_REG(FCML_REG_R9W); }
"r10w"					{ return FCML_FM_GPRS_16_REG(FCML_REG_R10W); }
"r11w"					{ return FCML_FM_GPRS_16_REG(FCML_REG_R11W); }
"r12w"					{ return FCML_FM_GPRS_16_REG(FCML_REG_R12W); }
"r13w"					{ return FCML_FM_GPRS_16_REG(FCML_REG_R13W); }
"r14w"					{ return FCML_FM_GPRS_16_REG(FCML_REG_R14W); }
"r15w"					{ return FCML_FM_GPRS_16_REG(FCML_REG_R15W); }

"eax"					{ return FCML_FM_GPRS_32_REG(FCML_REG_EAX); }
"ecx"					{ return FCML_FM_GPRS_32_REG(FCML_REG_ECX); }
"edx"					{ return FCML_FM_GPRS_32_REG(FCML_REG_EDX); }
"ebx"					{ return FCML_FM_GPRS_32_REG(FCML_REG_EBX); }
"esp"					{ return FCML_FM_GPRS_32_REG(FCML_REG_ESP); }
"ebp"					{ return FCML_FM_GPRS_32_REG(FCML_REG_EBP); }
"esi"					{ return FCML_FM_GPRS_32_REG(FCML_REG_ESI); }
"edi"					{ return FCML_FM_GPRS_32_REG(FCML_REG_EDI); }
"r8d"					{ return FCML_FM_GPRS_32_REG(FCML_REG_R8D); }
"r9d"					{ return FCML_FM_GPRS_32_REG(FCML_REG_R9D); }
"r10d"					{ return FCML_FM_GPRS_32_REG(FCML_REG_R10D); }
"r11d"					{ return FCML_FM_GPRS_32_REG(FCML_REG_R11D); }
"r12d"					{ return FCML_FM_GPRS_32_REG(FCML_REG_R12D); }
"r13d"					{ return FCML_FM_GPRS_32_REG(FCML_REG_R13D); }
"r14d"					{ return FCML_FM_GPRS_32_REG(FCML_REG_R14D); }
"r15d"					{ return FCML_FM_GPRS_32_REG(FCML_REG_R15D); }

"rax"                   { return FCML_FM_GPRS_64_REG(FCML_REG_RAX); }
"rcx"                   { return FCML_FM_GPRS_64_REG(FCML_REG_RCX); }
"rdx"                   { return FCML_FM_GPRS_64_REG(FCML_REG_RDX); }
"rbx"                   { return FCML_FM_GPRS_64_REG(FCML_REG_RBX); }
"rsp"                   { return FCML_FM_GPRS_64_REG(FCML_REG_RSP); }
"rbp"                   { return FCML_FM_GPRS_64_REG(FCML_REG_RBP); }
"rsi"                   { return FCML_FM_GPRS_64_REG(FCML_REG_RSI); }
"rdi"                   { return FCML_FM_GPRS_64_REG(FCML_REG_RDI); }
"r8"                    { return FCML_FM_GPRS_64_REG(FCML_REG_R8); }
"r9"                    { return FCML_FM_GPRS_64_REG(FCML_REG_R9); }
"r10"                   { return FCML_FM_GPRS_64_REG(FCML_REG_R10); }
"r11"                   { return FCML_FM_GPRS_64_REG(FCML_REG_R11); }
"r12"                   { return FCML_FM_GPRS_64_REG(FCML_REG_R12); }
"r13"                   { return FCML_FM_GPRS_64_REG(FCML_REG_R13); }
"r14"                   { return FCML_FM_GPRS_64_REG(FCML_REG_R14); }
"r15"                   { return FCML_FM_GPRS_64_REG(FCML_REG_R15); }

 /*SIMD-MMX*/
"mm0"					{ return FCML_FM_SIMD_64_REG(FCML_REG_MM0); }
"mm1"					{ return FCML_FM_SIMD_64_REG(FCML_REG_MM1); }
"mm2"					{ return FCML_FM_SIMD_64_REG(FCML_REG_MM2); }
"mm3"					{ return FCML_FM_SIMD_64_REG(FCML_REG_MM3); }
"mm4"					{ return FCML_FM_SIMD_64_REG(FCML_REG_MM4); }
"mm5"					{ return FCML_FM_SIMD_64_REG(FCML_REG_MM5); }
"mm6"					{ return FCML_FM_SIMD_64_REG(FCML_REG_MM6); }
"mm7"					{ return FCML_FM_SIMD_64_REG(FCML_REG_MM7); }

 /*SIMD-XMM*/
"xmm0"					{ return FCML_FM_SIMD_128_REG(FCML_REG_XMM0); }
"xmm1"					{ return FCML_FM_SIMD_128_REG(FCML_REG_XMM1); }
"xmm2"					{ return FCML_FM_SIMD_128_REG(FCML_REG_XMM2); }
"xmm3"					{ return FCML_FM_SIMD_128_REG(FCML_REG_XMM3); }
"xmm4"					{ return FCML_FM_SIMD_128_REG(FCML_REG_XMM4); }
"xmm5"					{ return FCML_FM_SIMD_128_REG(FCML_REG_XMM5); }
"xmm6"					{ return FCML_FM_SIMD_128_REG(FCML_REG_XMM6); }
"xmm7"					{ return FCML_FM_SIMD_128_REG(FCML_REG_XMM7); }
"xmm8"					{ return FCML_FM_SIMD_128_REG(FCML_REG_XMM8); }
"xmm9"					{ return FCML_FM_SIMD_128_REG(FCML_REG_XMM9); }
"xmm10"					{ return FCML_FM_SIMD_128_REG(FCML_REG_XMM10); }
"xmm11"					{ return FCML_FM_SIMD_128_REG(FCML_REG_XMM11); }
"xmm12"					{ return FCML_FM_SIMD_128_REG(FCML_REG_XMM12); }
"xmm13"					{ return FCML_FM_SIMD_128_REG(FCML_REG_XMM13); }
"xmm14"					{ return FCML_FM_SIMD_128_REG(FCML_REG_XMM14); }
"xmm15"					{ return FCML_FM_SIMD_128_REG(FCML_REG_XMM15); }

 /*SIMD-YMM*/
"ymm0"                  { return FCML_FM_SIMD_256_REG(FCML_REG_YMM0); }
"ymm1"                  { return FCML_FM_SIMD_256_REG(FCML_REG_YMM1); }
"ymm2"                  { return FCML_FM_SIMD_256_REG(FCML_REG_YMM2); }
"ymm3"                  { return FCML_FM_SIMD_256_REG(FCML_REG_YMM3); }
"ymm4"                  { return FCML_FM_SIMD_256_REG(FCML_REG_YMM4); }
"ymm5"                  { return FCML_FM_SIMD_256_REG(FCML_REG_YMM5); }
"ymm6"                  { return FCML_FM_SIMD_256_REG(FCML_REG_YMM6); }
"ymm7"                  { return FCML_FM_SIMD_256_REG(FCML_REG_YMM7); }
"ymm8"                  { return FCML_FM_SIMD_256_REG(FCML_REG_YMM8); }
"ymm9"                  { return FCML_FM_SIMD_256_REG(FCML_REG_YMM9); }
"ymm10"                 { return FCML_FM_SIMD_256_REG(FCML_REG_YMM10); }
"ymm11"                 { return FCML_FM_SIMD_256_REG(FCML_REG_YMM11); }
"ymm12"                 { return FCML_FM_SIMD_256_REG(FCML_REG_YMM12); }
"ymm13"                 { return FCML_FM_SIMD_256_REG(FCML_REG_YMM13); }
"ymm14"                 { return FCML_FM_SIMD_256_REG(FCML_REG_YMM14); }
"ymm15"                 { return FCML_FM_SIMD_256_REG(FCML_REG_YMM15); }

 /*FPU*/
st{WS}("("{WS}0{WS}")"|0)	{ return FCML_FM_FPU_REG(FCML_REG_ST0); }				
st{WS}("("{WS}1{WS}")"|1)	{ return FCML_FM_FPU_REG(FCML_REG_ST1); }
st{WS}("("{WS}2{WS}")"|2)	{ return FCML_FM_FPU_REG(FCML_REG_ST2); }
st{WS}("("{WS}3{WS}")"|3)	{ return FCML_FM_FPU_REG(FCML_REG_ST3); }
st{WS}("("{WS}4{WS}")"|4)	{ return FCML_FM_FPU_REG(FCML_REG_ST4); }
st{WS}("("{WS}5{WS}")"|5)	{ return FCML_FM_FPU_REG(FCML_REG_ST5); }
st{WS}("("{WS}6{WS}")"|6)	{ return FCML_FM_FPU_REG(FCML_REG_ST6); }
st{WS}("("{WS}7{WS}")"|7)	{ return FCML_FM_FPU_REG(FCML_REG_ST7); }

 /*Control registers.*/
"cr0"	{ return FCML_FM_CR_REG(FCML_REG_CR0); }
"cr2"	{ return FCML_FM_CR_REG(FCML_REG_CR2); }
"cr3"	{ return FCML_FM_CR_REG(FCML_REG_CR3); }
"cr4"	{ return FCML_FM_CR_REG(FCML_REG_CR4); }
"cr8"	{ return FCML_FM_CR_REG(FCML_REG_CR8); }

 /*Debug registers.*/
"dr0"	{ return FCML_FM_DR_REG(FCML_REG_DR0); }
"dr1"	{ return FCML_FM_DR_REG(FCML_REG_DR1); }
"dr2"	{ return FCML_FM_DR_REG(FCML_REG_DR2); }
"dr3"	{ return FCML_FM_DR_REG(FCML_REG_DR3); }
"dr4"	{ return FCML_FM_DR_REG(FCML_REG_DR4); }
"dr5"	{ return FCML_FM_DR_REG(FCML_REG_DR5); }
"dr6"	{ return FCML_FM_DR_REG(FCML_REG_DR6); }
"dr7"	{ return FCML_FM_DR_REG(FCML_REG_DR7); }

 /*Segment registers.*/
"es"	{ return FCML_FM_SEG_REG(FCML_REG_ES); }
"cs"	{ return FCML_FM_SEG_REG(FCML_REG_CS); }
"ss"	{ return FCML_FM_SEG_REG(FCML_REG_SS); }
"ds"	{ return FCML_FM_SEG_REG(FCML_REG_DS); }
"fs"	{ return FCML_FM_SEG_REG(FCML_REG_FS); }
"gs"	{ return FCML_FM_SEG_REG(FCML_REG_GS); }

 /*Size operators.*/
"byte"{PTR}									{ FCML_FM_SIZE_OPERAND( 8 ); }
"word"{PTR}									{ FCML_FM_SIZE_OPERAND( 16 ); }
"dword"{PTR}								{ FCML_FM_SIZE_OPERAND( 32 ); }
("fword"|"pword"){PTR}						{ FCML_FM_SIZE_OPERAND( 48 ); }
"qword"{PTR}								{ FCML_FM_SIZE_OPERAND( 64 ); }
("tbyte"|"tword"){PTR}						{ FCML_FM_SIZE_OPERAND( 80 ); }
("dqword"|"oword"){PTR}						{ FCML_FM_SIZE_OPERAND( 128 ); }
"qqword"{PTR} 								{ FCML_FM_SIZE_OPERAND( 256 ); }
"mmword"{PTR}								{ FCML_FM_MULTIMEDIA_SIZE_OPERAND( 64 ); }
("xword"|"xmmword"){PTR}					{ FCML_FM_MULTIMEDIA_SIZE_OPERAND( 128 ); }
("yword"|"ymmword"){PTR} 					{ FCML_FM_MULTIMEDIA_SIZE_OPERAND( 256 ); }
("14byte"){PTR} 							{ FCML_FM_SIZE_OPERAND( 14 * 8 ); }
("28byte"){PTR} 							{ FCML_FM_SIZE_OPERAND( 28 * 8 ); }
("94byte"){PTR} 							{ FCML_FM_SIZE_OPERAND( 94 * 8 ); }
("108byte"){PTR} 							{ FCML_FM_SIZE_OPERAND( 108 * 8 ); }

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
[a-z][0-9a-z_]*	{
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

 /*Anything else is not expected.*/
.		{ return FCML_TK_UNEXPECTED; }

 /*Ignore like white spaces.*/
\n		

%%

