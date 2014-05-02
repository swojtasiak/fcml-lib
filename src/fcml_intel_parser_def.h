/* A Bison parser, made by GNU Bison 2.7.12-4996.  */

/* Bison interface for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_INTEL_Y_TAB_H_INCLUDED
# define YY_INTEL_Y_TAB_H_INCLUDED
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int intel_debug;
#endif

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     FCML_TK_UNEXPECTED = 258,
     FCML_TK_REG_GPR = 259,
     FCML_TK_REG_SIMD = 260,
     FCML_TK_REG_FPU = 261,
     FCML_TK_REG_SEG = 262,
     FCML_TK_REG_CR = 263,
     FCML_TK_REG_DR = 264,
     FCML_TK_REG_RIP = 265,
     FCML_TK_INTEGER = 266,
     FCML_TK_FLOAT = 267,
     FCML_TK_SIZE_OPERATOR = 268,
     FCML_TK_SYMBOL = 269,
     FCML_TK_HINTS = 270,
     FCML_TK_EAO_HINTS = 271,
     FCML_TK_SIB_HINT = 272,
     FCML_TK_PREFIX = 273,
     FCML_OP_UMINUS = 274
   };
#endif
/* Tokens.  */
#define FCML_TK_UNEXPECTED 258
#define FCML_TK_REG_GPR 259
#define FCML_TK_REG_SIMD 260
#define FCML_TK_REG_FPU 261
#define FCML_TK_REG_SEG 262
#define FCML_TK_REG_CR 263
#define FCML_TK_REG_DR 264
#define FCML_TK_REG_RIP 265
#define FCML_TK_INTEGER 266
#define FCML_TK_FLOAT 267
#define FCML_TK_SIZE_OPERATOR 268
#define FCML_TK_SYMBOL 269
#define FCML_TK_HINTS 270
#define FCML_TK_EAO_HINTS 271
#define FCML_TK_SIB_HINT 272
#define FCML_TK_PREFIX 273
#define FCML_OP_UMINUS 274



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
/* Line 2053 of yacc.c  */
#line 83 "fcml_intel_parser_def.y"

	/*Complex values.*/
	fcml_st_ast_val_integer integer_value;
	fcml_st_ast_val_float float_value;
	fcml_st_register reg_value;
	fcml_st_ast_node *ast;
	struct {
		fcml_string text;
		int length;
	} symbol;
	fcml_st_size_operator size_operator;
	fcml_hints hints;
	fcml_prefixes prefixes;


/* Line 2053 of yacc.c  */
#line 111 "fcml_intel_parser_def.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int intel_parse (void *YYPARSE_PARAM);
#else
int intel_parse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int intel_parse (struct fcml_st_parser_data *pd);
#else
int intel_parse ();
#endif
#endif /* ! YYPARSE_PARAM */

#endif /* !YY_INTEL_Y_TAB_H_INCLUDED  */
