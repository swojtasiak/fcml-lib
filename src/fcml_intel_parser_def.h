/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_INTEL_FCML_INTEL_PARSER_DEF_H_INCLUDED
# define YY_INTEL_FCML_INTEL_PARSER_DEF_H_INCLUDED
/* Debug traces.  */
#ifndef INTEL_DEBUG
# if defined YYDEBUG
#if YYDEBUG
#   define INTEL_DEBUG 1
#  else
#   define INTEL_DEBUG 0
#  endif
# else /* ! defined YYDEBUG */
#  define INTEL_DEBUG 0
# endif /* ! defined YYDEBUG */
#endif  /* ! defined INTEL_DEBUG */
#if INTEL_DEBUG
extern int intel_debug;
#endif

/* Token type.  */
#ifndef INTEL_TOKENTYPE
# define INTEL_TOKENTYPE
  enum intel_tokentype
  {
    FCML_TK_UNEXPECTED = 258,
    FCML_TK_REG_GPR = 259,
    FCML_TK_REG_SIMD = 260,
    FCML_TK_REG_FPU = 261,
    FCML_TK_REG_SEG = 262,
    FCML_TK_REG_OPMASK = 263,
    FCML_TK_REG_CR = 264,
    FCML_TK_REG_DR = 265,
    FCML_TK_REG_RIP = 266,
    FCML_TK_DECORATOR_BCAST = 267,
    FCML_TK_DECORATOR_ER = 268,
    FCML_TK_DECORATOR_Z = 269,
    FCML_TK_DECORATOR_SAE = 270,
    FCML_TK_OPMASK_REG_DECORATOR = 271,
    FCML_TK_INTEGER = 272,
    FCML_TK_FLOAT = 273,
    FCML_TK_SIZE_OPERATOR = 274,
    FCML_TK_SYMBOL = 275,
    FCML_TK_HINTS = 276,
    FCML_TK_EAO_HINTS = 277,
    FCML_TK_SIB_HINT = 278,
    FCML_TK_PREFIX = 279,
    FCML_OP_UMINUS = 280
  };
#endif
/* Tokens.  */
#define FCML_TK_UNEXPECTED 258
#define FCML_TK_REG_GPR 259
#define FCML_TK_REG_SIMD 260
#define FCML_TK_REG_FPU 261
#define FCML_TK_REG_SEG 262
#define FCML_TK_REG_OPMASK 263
#define FCML_TK_REG_CR 264
#define FCML_TK_REG_DR 265
#define FCML_TK_REG_RIP 266
#define FCML_TK_DECORATOR_BCAST 267
#define FCML_TK_DECORATOR_ER 268
#define FCML_TK_DECORATOR_Z 269
#define FCML_TK_DECORATOR_SAE 270
#define FCML_TK_OPMASK_REG_DECORATOR 271
#define FCML_TK_INTEGER 272
#define FCML_TK_FLOAT 273
#define FCML_TK_SIZE_OPERATOR 274
#define FCML_TK_SYMBOL 275
#define FCML_TK_HINTS 276
#define FCML_TK_EAO_HINTS 277
#define FCML_TK_SIB_HINT 278
#define FCML_TK_PREFIX 279
#define FCML_OP_UMINUS 280

/* Value type.  */
#if ! defined INTEL_STYPE && ! defined INTEL_STYPE_IS_DECLARED
union INTEL_STYPE
{
#line 125 "fcml_intel_parser_def.y"

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
    fcml_bool bool_value;
    fcml_int int_value;

#line 132 "fcml_intel_parser_def.h"

};
typedef union INTEL_STYPE INTEL_STYPE;
# define INTEL_STYPE_IS_TRIVIAL 1
# define INTEL_STYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined INTEL_LTYPE && ! defined INTEL_LTYPE_IS_DECLARED
typedef struct INTEL_LTYPE INTEL_LTYPE;
struct INTEL_LTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define INTEL_LTYPE_IS_DECLARED 1
# define INTEL_LTYPE_IS_TRIVIAL 1
#endif



int intel_parse (struct fcml_st_parser_data *pd);
/* "%code provides" blocks.  */
#line 27 "fcml_intel_parser_def.y"

  #define YYSTYPE INTEL_STYPE
  #define YYLTYPE INTEL_LTYPE

#line 163 "fcml_intel_parser_def.h"

#endif /* !YY_INTEL_FCML_INTEL_PARSER_DEF_H_INCLUDED  */
