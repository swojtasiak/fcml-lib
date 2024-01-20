/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
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
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Substitute the type names.  */
#define YYSTYPE         INTEL_STYPE
#define YYLTYPE         INTEL_LTYPE
/* Substitute the variable and function names.  */
#define yyparse         intel_parse
#define yylex           intel_lex
#define yyerror         intel_error
#define yydebug         intel_debug
#define yynerrs         intel_nerrs

/* First part of user prologue.  */
#line 32 "fcml_intel_parser_def.y"

  #include <stdio.h>   
  #include "fcml_parser_utils.h"
  
  /* Macro responsible for handling 'Out of memory' errors. */
  #define HANDLE_ERRORS(x) if( !x ) { yyerror(&yylloc, pd, "Out of memory."); \
   YYERROR; }
    
  /* Macro responsible for adding error messages to result. */
  #define ADD_ERROR_MSG(x) { yyerror(&yylloc, pd, x ); }  

#line 90 "fcml_intel_parser_def.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
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

/* Token kinds.  */
#ifndef INTEL_TOKENTYPE
# define INTEL_TOKENTYPE
  enum intel_tokentype
  {
    INTEL_EMPTY = -2,
    INTEL_EOF = 0,                 /* "end of file"  */
    INTEL_error = 256,             /* error  */
    INTEL_UNDEF = 257,             /* "invalid token"  */
    FCML_TK_UNEXPECTED = 258,      /* FCML_TK_UNEXPECTED  */
    FCML_TK_REG_GPR = 259,         /* FCML_TK_REG_GPR  */
    FCML_TK_REG_SIMD = 260,        /* FCML_TK_REG_SIMD  */
    FCML_TK_REG_FPU = 261,         /* FCML_TK_REG_FPU  */
    FCML_TK_REG_SEG = 262,         /* FCML_TK_REG_SEG  */
    FCML_TK_REG_OPMASK = 263,      /* FCML_TK_REG_OPMASK  */
    FCML_TK_REG_CR = 264,          /* FCML_TK_REG_CR  */
    FCML_TK_REG_DR = 265,          /* FCML_TK_REG_DR  */
    FCML_TK_REG_RIP = 266,         /* FCML_TK_REG_RIP  */
    FCML_TK_DECORATOR_BCAST = 267, /* FCML_TK_DECORATOR_BCAST  */
    FCML_TK_DECORATOR_ER = 268,    /* FCML_TK_DECORATOR_ER  */
    FCML_TK_DECORATOR_Z = 269,     /* FCML_TK_DECORATOR_Z  */
    FCML_TK_DECORATOR_SAE = 270,   /* FCML_TK_DECORATOR_SAE  */
    FCML_TK_OPMASK_REG_DECORATOR = 271, /* FCML_TK_OPMASK_REG_DECORATOR  */
    FCML_TK_INTEGER = 272,         /* FCML_TK_INTEGER  */
    FCML_TK_FLOAT = 273,           /* FCML_TK_FLOAT  */
    FCML_TK_SIZE_OPERATOR = 274,   /* FCML_TK_SIZE_OPERATOR  */
    FCML_TK_SYMBOL = 275,          /* FCML_TK_SYMBOL  */
    FCML_TK_HINTS = 276,           /* FCML_TK_HINTS  */
    FCML_TK_EAO_HINTS = 277,       /* FCML_TK_EAO_HINTS  */
    FCML_TK_SIB_HINT = 278,        /* FCML_TK_SIB_HINT  */
    FCML_TK_PREFIX = 279,          /* FCML_TK_PREFIX  */
    FCML_OP_UMINUS = 280           /* FCML_OP_UMINUS  */
  };
  typedef enum intel_tokentype intel_token_kind_t;
#endif
/* Token kinds.  */
#define INTEL_EMPTY -2
#define INTEL_EOF 0
#define INTEL_error 256
#define INTEL_UNDEF 257
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

#line 218 "fcml_intel_parser_def.c"

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

#line 251 "fcml_intel_parser_def.c"

#endif /* !YY_INTEL_FCML_INTEL_PARSER_DEF_H_INCLUDED  */
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_FCML_TK_UNEXPECTED = 3,         /* FCML_TK_UNEXPECTED  */
  YYSYMBOL_FCML_TK_REG_GPR = 4,            /* FCML_TK_REG_GPR  */
  YYSYMBOL_FCML_TK_REG_SIMD = 5,           /* FCML_TK_REG_SIMD  */
  YYSYMBOL_FCML_TK_REG_FPU = 6,            /* FCML_TK_REG_FPU  */
  YYSYMBOL_FCML_TK_REG_SEG = 7,            /* FCML_TK_REG_SEG  */
  YYSYMBOL_FCML_TK_REG_OPMASK = 8,         /* FCML_TK_REG_OPMASK  */
  YYSYMBOL_FCML_TK_REG_CR = 9,             /* FCML_TK_REG_CR  */
  YYSYMBOL_FCML_TK_REG_DR = 10,            /* FCML_TK_REG_DR  */
  YYSYMBOL_FCML_TK_REG_RIP = 11,           /* FCML_TK_REG_RIP  */
  YYSYMBOL_FCML_TK_DECORATOR_BCAST = 12,   /* FCML_TK_DECORATOR_BCAST  */
  YYSYMBOL_FCML_TK_DECORATOR_ER = 13,      /* FCML_TK_DECORATOR_ER  */
  YYSYMBOL_FCML_TK_DECORATOR_Z = 14,       /* FCML_TK_DECORATOR_Z  */
  YYSYMBOL_FCML_TK_DECORATOR_SAE = 15,     /* FCML_TK_DECORATOR_SAE  */
  YYSYMBOL_FCML_TK_OPMASK_REG_DECORATOR = 16, /* FCML_TK_OPMASK_REG_DECORATOR  */
  YYSYMBOL_FCML_TK_INTEGER = 17,           /* FCML_TK_INTEGER  */
  YYSYMBOL_FCML_TK_FLOAT = 18,             /* FCML_TK_FLOAT  */
  YYSYMBOL_FCML_TK_SIZE_OPERATOR = 19,     /* FCML_TK_SIZE_OPERATOR  */
  YYSYMBOL_FCML_TK_SYMBOL = 20,            /* FCML_TK_SYMBOL  */
  YYSYMBOL_FCML_TK_HINTS = 21,             /* FCML_TK_HINTS  */
  YYSYMBOL_FCML_TK_EAO_HINTS = 22,         /* FCML_TK_EAO_HINTS  */
  YYSYMBOL_FCML_TK_SIB_HINT = 23,          /* FCML_TK_SIB_HINT  */
  YYSYMBOL_FCML_TK_PREFIX = 24,            /* FCML_TK_PREFIX  */
  YYSYMBOL_25_ = 25,                       /* '-'  */
  YYSYMBOL_26_ = 26,                       /* '+'  */
  YYSYMBOL_27_ = 27,                       /* '*'  */
  YYSYMBOL_28_ = 28,                       /* '/'  */
  YYSYMBOL_FCML_OP_UMINUS = 29,            /* FCML_OP_UMINUS  */
  YYSYMBOL_30_ = 30,                       /* ':'  */
  YYSYMBOL_31_ = 31,                       /* ','  */
  YYSYMBOL_32_ = 32,                       /* '['  */
  YYSYMBOL_33_ = 33,                       /* ']'  */
  YYSYMBOL_34_ = 34,                       /* '('  */
  YYSYMBOL_35_ = 35,                       /* ')'  */
  YYSYMBOL_YYACCEPT = 36,                  /* $accept  */
  YYSYMBOL_start = 37,                     /* start  */
  YYSYMBOL_instruction = 38,               /* instruction  */
  YYSYMBOL_inst_prefixes = 39,             /* inst_prefixes  */
  YYSYMBOL_mnemonic = 40,                  /* mnemonic  */
  YYSYMBOL_hint_list = 41,                 /* hint_list  */
  YYSYMBOL_operand_list = 42,              /* operand_list  */
  YYSYMBOL_operand = 43,                   /* operand  */
  YYSYMBOL_effective_address = 44,         /* effective_address  */
  YYSYMBOL_effective_address_components = 45, /* effective_address_components  */
  YYSYMBOL_segment_selector = 46,          /* segment_selector  */
  YYSYMBOL_far_pointer = 47,               /* far_pointer  */
  YYSYMBOL_exp = 48,                       /* exp  */
  YYSYMBOL_reg = 49                        /* reg  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;


/* Second part of user prologue.  */
#line 142 "fcml_intel_parser_def.y"

    #include "fcml_intel_lexer.h"
    #define yyscanner ((yyscan_t)pd->scannerInfo)
    void intel_error(YYLTYPE *yyloc, struct fcml_st_parser_data *pd,
    	const char *error );

#line 320 "fcml_intel_parser_def.c"


#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined INTEL_LTYPE_IS_TRIVIAL && INTEL_LTYPE_IS_TRIVIAL \
             && defined INTEL_STYPE_IS_TRIVIAL && INTEL_STYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  8
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   232

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  36
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  14
/* YYNRULES -- Number of rules.  */
#define YYNRULES  72
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  115

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   280


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      34,    35,    27,    26,    31,    25,     2,    28,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    30,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    32,     2,    33,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      29
};

#if INTEL_DEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   156,   156,   157,   158,   159,   162,   163,   164,   165,
     166,   167,   170,   171,   174,   177,   178,   181,   182,   190,
     191,   192,   193,   194,   195,   196,   197,   198,   199,   200,
     201,   204,   205,   206,   207,   208,   211,   212,   213,   214,
     215,   216,   217,   218,   219,   220,   221,   222,   223,   224,
     225,   226,   227,   228,   229,   232,   235,   238,   239,   240,
     241,   242,   243,   244,   245,   246,   250,   251,   252,   253,
     254,   255,   256
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if INTEL_DEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "FCML_TK_UNEXPECTED",
  "FCML_TK_REG_GPR", "FCML_TK_REG_SIMD", "FCML_TK_REG_FPU",
  "FCML_TK_REG_SEG", "FCML_TK_REG_OPMASK", "FCML_TK_REG_CR",
  "FCML_TK_REG_DR", "FCML_TK_REG_RIP", "FCML_TK_DECORATOR_BCAST",
  "FCML_TK_DECORATOR_ER", "FCML_TK_DECORATOR_Z", "FCML_TK_DECORATOR_SAE",
  "FCML_TK_OPMASK_REG_DECORATOR", "FCML_TK_INTEGER", "FCML_TK_FLOAT",
  "FCML_TK_SIZE_OPERATOR", "FCML_TK_SYMBOL", "FCML_TK_HINTS",
  "FCML_TK_EAO_HINTS", "FCML_TK_SIB_HINT", "FCML_TK_PREFIX", "'-'", "'+'",
  "'*'", "'/'", "FCML_OP_UMINUS", "':'", "','", "'['", "']'", "'('", "')'",
  "$accept", "start", "instruction", "inst_prefixes", "mnemonic",
  "hint_list", "operand_list", "operand", "effective_address",
  "effective_address_components", "segment_selector", "far_pointer", "exp",
  "reg", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-31)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      -5,   -23,   -31,    14,   -31,    32,    83,    33,   -31,   -31,
     -31,    83,   -31,   -31,   -31,   -13,   -31,   -31,   -31,   -31,
     -31,   -31,   -31,    -4,   -31,   -31,    -7,   176,    -7,   114,
     -11,   -31,    -8,    -1,   -31,    34,    26,   -31,   114,   -11,
     -31,   -13,   176,    22,   -31,   -31,    37,    -7,   198,    41,
      42,    46,    20,   -31,   -11,   145,   -31,   -31,    63,   176,
      -7,    -7,    -7,    -7,    -7,   -31,    85,   -11,    64,   176,
      -7,    42,    42,     0,   -31,    -7,   198,    90,   -31,   -31,
     -31,    76,    56,    56,   -31,   -31,    42,   -31,   -31,    77,
      42,    -7,    -7,    42,    42,    55,    69,   -31,   -31,    42,
      42,    -7,    -7,    94,    -7,    -7,    42,    42,    80,    42,
      42,    -7,    -7,    42,    42
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       2,    14,    12,     0,     3,     0,     6,     4,     1,    14,
      13,     9,    66,    67,    68,    69,    70,    71,    72,    30,
      29,    57,    58,     0,    63,    15,     0,     0,     0,     0,
       7,    17,    21,     0,    20,    19,    25,     5,     0,    10,
      55,     0,     0,     0,    64,    69,    38,     0,     0,     0,
      52,    36,     0,    16,     8,     0,    35,    24,    22,     0,
       0,     0,     0,     0,     0,    28,    26,    11,     0,     0,
       0,    53,    54,    37,    31,     0,     0,     0,    65,    18,
      23,     0,    59,    60,    62,    61,    56,    27,    32,     0,
      48,     0,     0,    50,    47,    39,     0,    33,    34,    51,
      49,     0,     0,     0,     0,     0,    46,    45,    40,    44,
      43,     0,     0,    42,    41
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -31,   -31,   105,   -31,   108,   103,    -6,    61,   -31,   -30,
     102,   -31,   -26,   -18
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     3,     4,     5,     6,    29,    30,    31,    32,    49,
      33,    34,    35,    36
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      44,    50,    52,    41,    56,    39,    57,     7,    58,    51,
      21,    22,    68,    24,     8,     1,    50,    40,    26,     2,
      55,    71,    72,    54,    51,    91,    92,    28,    42,    81,
      73,    59,    67,    50,    82,    83,    84,    85,    86,    89,
      65,    51,    66,    50,    90,    60,    61,    62,    63,    93,
      94,    51,     9,     9,    69,    78,    10,     2,    95,    60,
      61,    62,    63,    70,    64,    99,   100,    60,    61,    62,
      63,    75,    76,    77,    74,   106,   107,    80,   109,   110,
     101,   102,   103,    62,    63,   113,   114,    12,    13,    14,
      15,    16,    17,    18,   104,   105,    19,    88,    20,    87,
      21,    22,    23,    24,    25,   111,   112,    96,    26,    97,
      98,   108,    37,    11,    38,    27,    79,    28,    12,    13,
      14,    15,    16,    17,    18,    43,     0,    19,     0,    20,
       0,    21,    22,    23,    24,    53,     0,     0,     0,    26,
       0,     0,     0,     0,     0,     0,    27,     0,    28,    12,
      13,    14,    15,    16,    17,    18,     0,     0,    19,     0,
      20,     0,    21,    22,    23,    24,     0,     0,     0,     0,
      26,     0,     0,     0,     0,     0,     0,    27,     0,    28,
      12,    13,    14,    45,    16,    17,    18,    46,     0,     0,
       0,     0,     0,    21,    22,     0,    24,     0,    47,    48,
       0,    26,    12,    13,    14,    45,    16,    17,    18,     0,
      28,     0,     0,     0,     0,    21,    22,     0,    24,     0,
       0,     0,     0,    26,     0,     0,     0,     0,     0,     0,
       0,     0,    28
};

static const yytype_int8 yycheck[] =
{
      26,    27,    28,     7,    12,    11,    14,    30,    16,    27,
      17,    18,    42,    20,     0,    20,    42,    30,    25,    24,
      31,    47,    48,    29,    42,    25,    26,    34,    32,    59,
      48,    32,    38,    59,    60,    61,    62,    63,    64,    69,
      14,    59,    16,    69,    70,    25,    26,    27,    28,    75,
      76,    69,    20,    20,    32,    35,    24,    24,    76,    25,
      26,    27,    28,    26,    30,    91,    92,    25,    26,    27,
      28,    25,    26,    27,    33,   101,   102,    14,   104,   105,
      25,    26,    27,    27,    28,   111,   112,     4,     5,     6,
       7,     8,     9,    10,    25,    26,    13,    33,    15,    14,
      17,    18,    19,    20,    21,    25,    26,    17,    25,    33,
      33,    17,     7,     5,    11,    32,    55,    34,     4,     5,
       6,     7,     8,     9,    10,    23,    -1,    13,    -1,    15,
      -1,    17,    18,    19,    20,    21,    -1,    -1,    -1,    25,
      -1,    -1,    -1,    -1,    -1,    -1,    32,    -1,    34,     4,
       5,     6,     7,     8,     9,    10,    -1,    -1,    13,    -1,
      15,    -1,    17,    18,    19,    20,    -1,    -1,    -1,    -1,
      25,    -1,    -1,    -1,    -1,    -1,    -1,    32,    -1,    34,
       4,     5,     6,     7,     8,     9,    10,    11,    -1,    -1,
      -1,    -1,    -1,    17,    18,    -1,    20,    -1,    22,    23,
      -1,    25,     4,     5,     6,     7,     8,     9,    10,    -1,
      34,    -1,    -1,    -1,    -1,    17,    18,    -1,    20,    -1,
      -1,    -1,    -1,    25,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    34
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    20,    24,    37,    38,    39,    40,    30,     0,    20,
      24,    40,     4,     5,     6,     7,     8,     9,    10,    13,
      15,    17,    18,    19,    20,    21,    25,    32,    34,    41,
      42,    43,    44,    46,    47,    48,    49,    38,    41,    42,
      30,     7,    32,    46,    48,     7,    11,    22,    23,    45,
      48,    49,    48,    21,    42,    31,    12,    14,    16,    32,
      25,    26,    27,    28,    30,    14,    16,    42,    45,    32,
      26,    48,    48,    49,    33,    25,    26,    27,    35,    43,
      14,    45,    48,    48,    48,    48,    48,    14,    33,    45,
      48,    25,    26,    48,    48,    49,    17,    33,    33,    48,
      48,    25,    26,    27,    25,    26,    48,    48,    17,    48,
      48,    25,    26,    48,    48
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    36,    37,    37,    37,    37,    38,    38,    38,    38,
      38,    38,    39,    39,    40,    41,    41,    42,    42,    43,
      43,    43,    43,    43,    43,    43,    43,    43,    43,    43,
      43,    44,    44,    44,    44,    44,    45,    45,    45,    45,
      45,    45,    45,    45,    45,    45,    45,    45,    45,    45,
      45,    45,    45,    45,    45,    46,    47,    48,    48,    48,
      48,    48,    48,    48,    48,    48,    49,    49,    49,    49,
      49,    49,    49
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     1,     2,     3,     1,     2,     3,     2,
       3,     4,     1,     2,     1,     1,     2,     1,     3,     1,
       1,     1,     2,     3,     2,     1,     2,     3,     2,     1,
       1,     3,     4,     4,     5,     2,     1,     2,     1,     3,
       5,     7,     7,     5,     5,     5,     5,     3,     3,     4,
       3,     4,     1,     2,     2,     2,     3,     1,     1,     3,
       3,     3,     3,     1,     2,     3,     1,     1,     1,     1,
       1,     1,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = INTEL_EMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == INTEL_EMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (&yylloc, pd, YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use INTEL_error or INTEL_UNDEF. */
#define YYERRCODE INTEL_UNDEF

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if INTEL_DEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YYLOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YYLOCATION_PRINT

#  if defined YY_LOCATION_PRINT

   /* Temporary convenience wrapper in case some people defined the
      undocumented and private YY_LOCATION_PRINT macros.  */
#   define YYLOCATION_PRINT(File, Loc)  YY_LOCATION_PRINT(File, *(Loc))

#  elif defined INTEL_LTYPE_IS_TRIVIAL && INTEL_LTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
}

#   define YYLOCATION_PRINT  yy_location_print_

    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT(File, Loc)  YYLOCATION_PRINT(File, &(Loc))

#  else

#   define YYLOCATION_PRINT(File, Loc) ((void) 0)
    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT  YYLOCATION_PRINT

#  endif
# endif /* !defined YYLOCATION_PRINT */


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, Location, pd); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, struct fcml_st_parser_data *pd)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (yylocationp);
  YY_USE (pd);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  switch (yykind)
    {
    case YYSYMBOL_FCML_TK_REG_GPR: /* FCML_TK_REG_GPR  */
#line 123 "fcml_intel_parser_def.y"
         { YYFPRINTF(yyoutput, "Type: %s Size: %d Reg: %d x64_exp: %d", fcml_fn_pu_reg_type_to_string( ((*yyvaluep).reg_value).type ), ((*yyvaluep).reg_value).size, ((*yyvaluep).reg_value).reg, ((*yyvaluep).reg_value).x64_exp); }
#line 1085 "fcml_intel_parser_def.c"
        break;

    case YYSYMBOL_FCML_TK_REG_SIMD: /* FCML_TK_REG_SIMD  */
#line 123 "fcml_intel_parser_def.y"
         { YYFPRINTF(yyoutput, "Type: %s Size: %d Reg: %d x64_exp: %d", fcml_fn_pu_reg_type_to_string( ((*yyvaluep).reg_value).type ), ((*yyvaluep).reg_value).size, ((*yyvaluep).reg_value).reg, ((*yyvaluep).reg_value).x64_exp); }
#line 1091 "fcml_intel_parser_def.c"
        break;

    case YYSYMBOL_FCML_TK_REG_FPU: /* FCML_TK_REG_FPU  */
#line 123 "fcml_intel_parser_def.y"
         { YYFPRINTF(yyoutput, "Type: %s Size: %d Reg: %d x64_exp: %d", fcml_fn_pu_reg_type_to_string( ((*yyvaluep).reg_value).type ), ((*yyvaluep).reg_value).size, ((*yyvaluep).reg_value).reg, ((*yyvaluep).reg_value).x64_exp); }
#line 1097 "fcml_intel_parser_def.c"
        break;

    case YYSYMBOL_FCML_TK_REG_SEG: /* FCML_TK_REG_SEG  */
#line 123 "fcml_intel_parser_def.y"
         { YYFPRINTF(yyoutput, "Type: %s Size: %d Reg: %d x64_exp: %d", fcml_fn_pu_reg_type_to_string( ((*yyvaluep).reg_value).type ), ((*yyvaluep).reg_value).size, ((*yyvaluep).reg_value).reg, ((*yyvaluep).reg_value).x64_exp); }
#line 1103 "fcml_intel_parser_def.c"
        break;

    case YYSYMBOL_FCML_TK_REG_OPMASK: /* FCML_TK_REG_OPMASK  */
#line 123 "fcml_intel_parser_def.y"
         { YYFPRINTF(yyoutput, "Type: %s Size: %d Reg: %d x64_exp: %d", fcml_fn_pu_reg_type_to_string( ((*yyvaluep).reg_value).type ), ((*yyvaluep).reg_value).size, ((*yyvaluep).reg_value).reg, ((*yyvaluep).reg_value).x64_exp); }
#line 1109 "fcml_intel_parser_def.c"
        break;

    case YYSYMBOL_FCML_TK_REG_CR: /* FCML_TK_REG_CR  */
#line 123 "fcml_intel_parser_def.y"
         { YYFPRINTF(yyoutput, "Type: %s Size: %d Reg: %d x64_exp: %d", fcml_fn_pu_reg_type_to_string( ((*yyvaluep).reg_value).type ), ((*yyvaluep).reg_value).size, ((*yyvaluep).reg_value).reg, ((*yyvaluep).reg_value).x64_exp); }
#line 1115 "fcml_intel_parser_def.c"
        break;

    case YYSYMBOL_FCML_TK_REG_DR: /* FCML_TK_REG_DR  */
#line 123 "fcml_intel_parser_def.y"
         { YYFPRINTF(yyoutput, "Type: %s Size: %d Reg: %d x64_exp: %d", fcml_fn_pu_reg_type_to_string( ((*yyvaluep).reg_value).type ), ((*yyvaluep).reg_value).size, ((*yyvaluep).reg_value).reg, ((*yyvaluep).reg_value).x64_exp); }
#line 1121 "fcml_intel_parser_def.c"
        break;

    case YYSYMBOL_FCML_TK_REG_RIP: /* FCML_TK_REG_RIP  */
#line 123 "fcml_intel_parser_def.y"
         { YYFPRINTF(yyoutput, "Type: %s Size: %d Reg: %d x64_exp: %d", fcml_fn_pu_reg_type_to_string( ((*yyvaluep).reg_value).type ), ((*yyvaluep).reg_value).size, ((*yyvaluep).reg_value).reg, ((*yyvaluep).reg_value).x64_exp); }
#line 1127 "fcml_intel_parser_def.c"
        break;

    case YYSYMBOL_FCML_TK_OPMASK_REG_DECORATOR: /* FCML_TK_OPMASK_REG_DECORATOR  */
#line 123 "fcml_intel_parser_def.y"
         { YYFPRINTF(yyoutput, "Type: %s Size: %d Reg: %d x64_exp: %d", fcml_fn_pu_reg_type_to_string( ((*yyvaluep).reg_value).type ), ((*yyvaluep).reg_value).size, ((*yyvaluep).reg_value).reg, ((*yyvaluep).reg_value).x64_exp); }
#line 1133 "fcml_intel_parser_def.c"
        break;

    case YYSYMBOL_FCML_TK_INTEGER: /* FCML_TK_INTEGER  */
#line 120 "fcml_intel_parser_def.y"
         { YYFPRINTF(yyoutput, "Integer: %d Overflow: %d", ((*yyvaluep).integer_value).value, ((*yyvaluep).integer_value).overflow); }
#line 1139 "fcml_intel_parser_def.c"
        break;

    case YYSYMBOL_FCML_TK_FLOAT: /* FCML_TK_FLOAT  */
#line 121 "fcml_intel_parser_def.y"
         { YYFPRINTF(yyoutput, "Float: %f Overflow: %d", ((*yyvaluep).float_value).value, ((*yyvaluep).float_value).overflow); }
#line 1145 "fcml_intel_parser_def.c"
        break;

    case YYSYMBOL_instruction: /* instruction  */
#line 122 "fcml_intel_parser_def.y"
         { YYFPRINTF(yyoutput, "AST-Type: %d", ((*yyvaluep).ast)->type); }
#line 1151 "fcml_intel_parser_def.c"
        break;

    case YYSYMBOL_operand_list: /* operand_list  */
#line 122 "fcml_intel_parser_def.y"
         { YYFPRINTF(yyoutput, "AST-Type: %d", ((*yyvaluep).ast)->type); }
#line 1157 "fcml_intel_parser_def.c"
        break;

    case YYSYMBOL_operand: /* operand  */
#line 122 "fcml_intel_parser_def.y"
         { YYFPRINTF(yyoutput, "AST-Type: %d", ((*yyvaluep).ast)->type); }
#line 1163 "fcml_intel_parser_def.c"
        break;

    case YYSYMBOL_effective_address: /* effective_address  */
#line 122 "fcml_intel_parser_def.y"
         { YYFPRINTF(yyoutput, "AST-Type: %d", ((*yyvaluep).ast)->type); }
#line 1169 "fcml_intel_parser_def.c"
        break;

    case YYSYMBOL_effective_address_components: /* effective_address_components  */
#line 122 "fcml_intel_parser_def.y"
         { YYFPRINTF(yyoutput, "AST-Type: %d", ((*yyvaluep).ast)->type); }
#line 1175 "fcml_intel_parser_def.c"
        break;

    case YYSYMBOL_segment_selector: /* segment_selector  */
#line 123 "fcml_intel_parser_def.y"
         { YYFPRINTF(yyoutput, "Type: %s Size: %d Reg: %d x64_exp: %d", fcml_fn_pu_reg_type_to_string( ((*yyvaluep).reg_value).type ), ((*yyvaluep).reg_value).size, ((*yyvaluep).reg_value).reg, ((*yyvaluep).reg_value).x64_exp); }
#line 1181 "fcml_intel_parser_def.c"
        break;

    case YYSYMBOL_far_pointer: /* far_pointer  */
#line 122 "fcml_intel_parser_def.y"
         { YYFPRINTF(yyoutput, "AST-Type: %d", ((*yyvaluep).ast)->type); }
#line 1187 "fcml_intel_parser_def.c"
        break;

    case YYSYMBOL_exp: /* exp  */
#line 122 "fcml_intel_parser_def.y"
         { YYFPRINTF(yyoutput, "AST-Type: %d", ((*yyvaluep).ast)->type); }
#line 1193 "fcml_intel_parser_def.c"
        break;

    case YYSYMBOL_reg: /* reg  */
#line 123 "fcml_intel_parser_def.y"
         { YYFPRINTF(yyoutput, "Type: %s Size: %d Reg: %d x64_exp: %d", fcml_fn_pu_reg_type_to_string( ((*yyvaluep).reg_value).type ), ((*yyvaluep).reg_value).size, ((*yyvaluep).reg_value).reg, ((*yyvaluep).reg_value).x64_exp); }
#line 1199 "fcml_intel_parser_def.c"
        break;

      default:
        break;
    }
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, struct fcml_st_parser_data *pd)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YYLOCATION_PRINT (yyo, yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp, pd);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp,
                 int yyrule, struct fcml_st_parser_data *pd)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)],
                       &(yylsp[(yyi + 1) - (yynrhs)]), pd);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule, pd); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !INTEL_DEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !INTEL_DEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, struct fcml_st_parser_data *pd)
{
  YY_USE (yyvaluep);
  YY_USE (yylocationp);
  YY_USE (pd);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  switch (yykind)
    {
    case YYSYMBOL_instruction: /* instruction  */
#line 117 "fcml_intel_parser_def.y"
            { fcml_fn_ast_free_node(((*yyvaluep).ast)); }
#line 1334 "fcml_intel_parser_def.c"
        break;

    case YYSYMBOL_operand_list: /* operand_list  */
#line 117 "fcml_intel_parser_def.y"
            { fcml_fn_ast_free_node(((*yyvaluep).ast)); }
#line 1340 "fcml_intel_parser_def.c"
        break;

    case YYSYMBOL_operand: /* operand  */
#line 117 "fcml_intel_parser_def.y"
            { fcml_fn_ast_free_node(((*yyvaluep).ast)); }
#line 1346 "fcml_intel_parser_def.c"
        break;

    case YYSYMBOL_effective_address: /* effective_address  */
#line 117 "fcml_intel_parser_def.y"
            { fcml_fn_ast_free_node(((*yyvaluep).ast)); }
#line 1352 "fcml_intel_parser_def.c"
        break;

    case YYSYMBOL_effective_address_components: /* effective_address_components  */
#line 117 "fcml_intel_parser_def.y"
            { fcml_fn_ast_free_node(((*yyvaluep).ast)); }
#line 1358 "fcml_intel_parser_def.c"
        break;

    case YYSYMBOL_far_pointer: /* far_pointer  */
#line 117 "fcml_intel_parser_def.y"
            { fcml_fn_ast_free_node(((*yyvaluep).ast)); }
#line 1364 "fcml_intel_parser_def.c"
        break;

    case YYSYMBOL_exp: /* exp  */
#line 117 "fcml_intel_parser_def.y"
            { fcml_fn_ast_free_node(((*yyvaluep).ast)); }
#line 1370 "fcml_intel_parser_def.c"
        break;

      default:
        break;
    }
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}






/*----------.
| yyparse.  |
`----------*/

int
yyparse (struct fcml_st_parser_data *pd)
{
/* Lookahead token kind.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

/* Location data for the lookahead symbol.  */
static YYLTYPE yyloc_default
# if defined INTEL_LTYPE_IS_TRIVIAL && INTEL_LTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
YYLTYPE yylloc = yyloc_default;

    /* Number of syntax errors so far.  */
    int yynerrs = 0;

    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

    /* The location stack: array, bottom, top.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls = yylsa;
    YYLTYPE *yylsp = yyls;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[3];



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = INTEL_EMPTY; /* Cause a token to be read.  */


/* User initialization code.  */
#line 149 "fcml_intel_parser_def.y"
{ 
    /* Uncomment it in order to enable debugging */
    /* yydebug = 1; */
}

#line 1470 "fcml_intel_parser_def.c"

  yylsp[0] = yylloc;
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == INTEL_EMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex (&yylval, &yylloc, yyscanner);
    }

  if (yychar <= INTEL_EOF)
    {
      yychar = INTEL_EOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == INTEL_error)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = INTEL_UNDEF;
      yytoken = YYSYMBOL_YYerror;
      yyerror_range[1] = yylloc;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;

  /* Discard the shifted token.  */
  yychar = INTEL_EMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 3: /* start: instruction  */
#line 157 "fcml_intel_parser_def.y"
                                                { pd->tree = (yyvsp[0].ast); pd->symbol = NULL; }
#line 1683 "fcml_intel_parser_def.c"
    break;

  case 4: /* start: FCML_TK_SYMBOL ':'  */
#line 158 "fcml_intel_parser_def.y"
                                                { pd->tree = NULL; pd->symbol = fcml_fn_ast_alloc_node_define_symbol( pd->ip, (yyvsp[-1].symbol).text, (yyvsp[-1].symbol).length ); HANDLE_ERRORS( pd->symbol ); }
#line 1689 "fcml_intel_parser_def.c"
    break;

  case 5: /* start: FCML_TK_SYMBOL ':' instruction  */
#line 159 "fcml_intel_parser_def.y"
                                                { pd->tree = (yyvsp[0].ast); pd->symbol = fcml_fn_ast_alloc_node_define_symbol( pd->ip, (yyvsp[-2].symbol).text, (yyvsp[-2].symbol).length ); HANDLE_ERRORS( pd->symbol ); }
#line 1695 "fcml_intel_parser_def.c"
    break;

  case 6: /* instruction: mnemonic  */
#line 162 "fcml_intel_parser_def.y"
                                                { (yyval.ast) = fcml_fn_ast_alloc_node_instruction( 0, (yyvsp[0].symbol).text, (yyvsp[0].symbol).length, 0, NULL ); HANDLE_ERRORS((yyval.ast)); }
#line 1701 "fcml_intel_parser_def.c"
    break;

  case 7: /* instruction: mnemonic operand_list  */
#line 163 "fcml_intel_parser_def.y"
                                                { (yyval.ast) = fcml_fn_ast_alloc_node_instruction( 0, (yyvsp[-1].symbol).text, (yyvsp[-1].symbol).length, 0, (yyvsp[0].ast) ); HANDLE_ERRORS((yyval.ast)); }
#line 1707 "fcml_intel_parser_def.c"
    break;

  case 8: /* instruction: mnemonic hint_list operand_list  */
#line 164 "fcml_intel_parser_def.y"
                                                { (yyval.ast) = fcml_fn_ast_alloc_node_instruction( 0, (yyvsp[-2].symbol).text, (yyvsp[-2].symbol).length, (yyvsp[-1].hints), (yyvsp[0].ast) ); HANDLE_ERRORS((yyval.ast)); }
#line 1713 "fcml_intel_parser_def.c"
    break;

  case 9: /* instruction: inst_prefixes mnemonic  */
#line 165 "fcml_intel_parser_def.y"
                                                { (yyval.ast) = fcml_fn_ast_alloc_node_instruction( (yyvsp[-1].prefixes), (yyvsp[0].symbol).text, (yyvsp[0].symbol).length, 0, NULL ); HANDLE_ERRORS((yyval.ast)); }
#line 1719 "fcml_intel_parser_def.c"
    break;

  case 10: /* instruction: inst_prefixes mnemonic operand_list  */
#line 166 "fcml_intel_parser_def.y"
                                                { (yyval.ast) = fcml_fn_ast_alloc_node_instruction( (yyvsp[-2].prefixes), (yyvsp[-1].symbol).text, (yyvsp[-1].symbol).length, 0, (yyvsp[0].ast) ); HANDLE_ERRORS((yyval.ast)); }
#line 1725 "fcml_intel_parser_def.c"
    break;

  case 11: /* instruction: inst_prefixes mnemonic hint_list operand_list  */
#line 167 "fcml_intel_parser_def.y"
                                                { (yyval.ast) = fcml_fn_ast_alloc_node_instruction( (yyvsp[-3].prefixes), (yyvsp[-2].symbol).text, (yyvsp[-2].symbol).length, (yyvsp[-1].hints), (yyvsp[0].ast) ); HANDLE_ERRORS((yyval.ast)); }
#line 1731 "fcml_intel_parser_def.c"
    break;

  case 13: /* inst_prefixes: inst_prefixes FCML_TK_PREFIX  */
#line 171 "fcml_intel_parser_def.y"
                               { if( (yyvsp[-1].prefixes) & (yyvsp[0].prefixes) )  { ADD_ERROR_MSG( "Doubled prefixes." ); YYERROR; } else { (yyval.prefixes) = (yyvsp[-1].prefixes) | (yyvsp[0].prefixes); } }
#line 1737 "fcml_intel_parser_def.c"
    break;

  case 16: /* hint_list: hint_list FCML_TK_HINTS  */
#line 178 "fcml_intel_parser_def.y"
                                                { (yyval.hints) = (yyvsp[-1].hints) | (yyvsp[0].hints); }
#line 1743 "fcml_intel_parser_def.c"
    break;

  case 17: /* operand_list: operand  */
#line 181 "fcml_intel_parser_def.y"
                                                { (yyval.ast) = fcml_fn_ast_alloc_node_operand_list( (yyvsp[0].ast), NULL ); HANDLE_ERRORS((yyval.ast)); }
#line 1749 "fcml_intel_parser_def.c"
    break;

  case 18: /* operand_list: operand_list ',' operand  */
#line 182 "fcml_intel_parser_def.y"
                                                { (yyval.ast) = fcml_fn_ast_alloc_node_operand_list( (yyvsp[-2].ast), (yyvsp[0].ast) ); HANDLE_ERRORS((yyval.ast)); }
#line 1755 "fcml_intel_parser_def.c"
    break;

  case 22: /* operand: effective_address FCML_TK_OPMASK_REG_DECORATOR  */
#line 193 "fcml_intel_parser_def.y"
                                                                       { (yyval.ast) = fcml_fn_ast_decorate_effective_address((yyvsp[-1].ast), &(yyvsp[0].reg_value), FCML_FALSE); }
#line 1761 "fcml_intel_parser_def.c"
    break;

  case 23: /* operand: effective_address FCML_TK_OPMASK_REG_DECORATOR FCML_TK_DECORATOR_Z  */
#line 194 "fcml_intel_parser_def.y"
                                                                       { (yyval.ast) = fcml_fn_ast_decorate_effective_address((yyvsp[-2].ast), &(yyvsp[-1].reg_value), FCML_TRUE); }
#line 1767 "fcml_intel_parser_def.c"
    break;

  case 24: /* operand: effective_address FCML_TK_DECORATOR_Z  */
#line 195 "fcml_intel_parser_def.y"
                                                                       { (yyval.ast) = fcml_fn_ast_decorate_effective_address((yyvsp[-1].ast), NULL, FCML_TRUE); }
#line 1773 "fcml_intel_parser_def.c"
    break;

  case 25: /* operand: reg  */
#line 196 "fcml_intel_parser_def.y"
                                                                       { (yyval.ast) = fcml_fn_ast_alloc_node_register( &(yyvsp[0].reg_value), NULL, FCML_FALSE ); HANDLE_ERRORS((yyval.ast)); }
#line 1779 "fcml_intel_parser_def.c"
    break;

  case 26: /* operand: reg FCML_TK_OPMASK_REG_DECORATOR  */
#line 197 "fcml_intel_parser_def.y"
                                                                       { (yyval.ast) = fcml_fn_ast_alloc_node_register( &(yyvsp[-1].reg_value), &(yyvsp[0].reg_value), FCML_FALSE ); HANDLE_ERRORS((yyval.ast)); }
#line 1785 "fcml_intel_parser_def.c"
    break;

  case 27: /* operand: reg FCML_TK_OPMASK_REG_DECORATOR FCML_TK_DECORATOR_Z  */
#line 198 "fcml_intel_parser_def.y"
                                                                       { (yyval.ast) = fcml_fn_ast_alloc_node_register( &(yyvsp[-2].reg_value), &(yyvsp[-1].reg_value), FCML_TRUE ); HANDLE_ERRORS((yyval.ast)); }
#line 1791 "fcml_intel_parser_def.c"
    break;

  case 28: /* operand: reg FCML_TK_DECORATOR_Z  */
#line 199 "fcml_intel_parser_def.y"
                                                                       { (yyval.ast) = fcml_fn_ast_alloc_node_register( &(yyvsp[-1].reg_value), NULL, FCML_TRUE ); HANDLE_ERRORS((yyval.ast)); }
#line 1797 "fcml_intel_parser_def.c"
    break;

  case 29: /* operand: FCML_TK_DECORATOR_SAE  */
#line 200 "fcml_intel_parser_def.y"
                                                                       { (yyval.ast) = fcml_fn_ast_alloc_node_virtual( FCML_TRUE, FCML_FALSE, 0 ); HANDLE_ERRORS((yyval.ast)); }
#line 1803 "fcml_intel_parser_def.c"
    break;

  case 30: /* operand: FCML_TK_DECORATOR_ER  */
#line 201 "fcml_intel_parser_def.y"
                                                                       { (yyval.ast) = fcml_fn_ast_alloc_node_virtual( FCML_FALSE, FCML_TRUE, (yyvsp[0].int_value) ); HANDLE_ERRORS((yyval.ast)); }
#line 1809 "fcml_intel_parser_def.c"
    break;

  case 31: /* effective_address: '[' effective_address_components ']'  */
#line 204 "fcml_intel_parser_def.y"
                                                                              { (yyval.ast) = (yyvsp[-1].ast); }
#line 1815 "fcml_intel_parser_def.c"
    break;

  case 32: /* effective_address: FCML_TK_SIZE_OPERATOR '[' effective_address_components ']'  */
#line 205 "fcml_intel_parser_def.y"
                                                                              { (yyval.ast) = fcml_fn_ast_set_effective_address_details( NULL, &(yyvsp[-3].size_operator), 0, (yyvsp[-1].ast) ); }
#line 1821 "fcml_intel_parser_def.c"
    break;

  case 33: /* effective_address: segment_selector '[' effective_address_components ']'  */
#line 206 "fcml_intel_parser_def.y"
                                                                              { (yyval.ast) = fcml_fn_ast_set_effective_address_details( &(yyvsp[-3].reg_value), FCML_OS_UNDEFINED, 0, (yyvsp[-1].ast) ); }
#line 1827 "fcml_intel_parser_def.c"
    break;

  case 34: /* effective_address: FCML_TK_SIZE_OPERATOR segment_selector '[' effective_address_components ']'  */
#line 207 "fcml_intel_parser_def.y"
                                                                              { (yyval.ast) = fcml_fn_ast_set_effective_address_details( &(yyvsp[-3].reg_value), &(yyvsp[-4].size_operator), 0, (yyvsp[-1].ast) ); }
#line 1833 "fcml_intel_parser_def.c"
    break;

  case 35: /* effective_address: effective_address FCML_TK_DECORATOR_BCAST  */
#line 208 "fcml_intel_parser_def.y"
                                                                              { (yyval.ast) = fcml_fn_ast_set_effective_address_details( NULL, FCML_OS_UNDEFINED, (yyvsp[0].int_value), (yyvsp[-1].ast) ); }
#line 1839 "fcml_intel_parser_def.c"
    break;

  case 36: /* effective_address_components: reg  */
#line 211 "fcml_intel_parser_def.y"
                                              { (yyval.ast) = fcml_fn_ast_alloc_node_effective_address( &(yyvsp[0].reg_value), NULL, NULL, NULL, FCML_FALSE, 0 ); }
#line 1845 "fcml_intel_parser_def.c"
    break;

  case 37: /* effective_address_components: FCML_TK_SIB_HINT reg  */
#line 212 "fcml_intel_parser_def.y"
                                              { (yyval.ast) = fcml_fn_ast_alloc_node_effective_address( &(yyvsp[0].reg_value), NULL, NULL, NULL, FCML_FALSE, (yyvsp[-1].hints) ); }
#line 1851 "fcml_intel_parser_def.c"
    break;

  case 38: /* effective_address_components: FCML_TK_REG_RIP  */
#line 213 "fcml_intel_parser_def.y"
                                              { (yyval.ast) = fcml_fn_ast_alloc_node_effective_address( &(yyvsp[0].reg_value), NULL, NULL, NULL, FCML_FALSE, 0 ); }
#line 1857 "fcml_intel_parser_def.c"
    break;

  case 39: /* effective_address_components: reg '+' reg  */
#line 214 "fcml_intel_parser_def.y"
                                              { (yyval.ast) = fcml_fn_ast_alloc_node_effective_address( &(yyvsp[-2].reg_value), &(yyvsp[0].reg_value), NULL, NULL, FCML_FALSE, 0 ); }
#line 1863 "fcml_intel_parser_def.c"
    break;

  case 40: /* effective_address_components: reg '+' reg '*' FCML_TK_INTEGER  */
#line 215 "fcml_intel_parser_def.y"
                                              { (yyval.ast) = fcml_fn_ast_alloc_node_effective_address( &(yyvsp[-4].reg_value), &(yyvsp[-2].reg_value), &(yyvsp[0].integer_value), NULL, FCML_FALSE, 0 ); }
#line 1869 "fcml_intel_parser_def.c"
    break;

  case 41: /* effective_address_components: reg '+' reg '*' FCML_TK_INTEGER '+' exp  */
#line 216 "fcml_intel_parser_def.y"
                                              { (yyval.ast) = fcml_fn_ast_alloc_node_effective_address( &(yyvsp[-6].reg_value), &(yyvsp[-4].reg_value), &(yyvsp[-2].integer_value), (yyvsp[0].ast), FCML_FALSE, 0 ); }
#line 1875 "fcml_intel_parser_def.c"
    break;

  case 42: /* effective_address_components: reg '+' reg '*' FCML_TK_INTEGER '-' exp  */
#line 217 "fcml_intel_parser_def.y"
                                              { (yyval.ast) = fcml_fn_ast_alloc_node_effective_address( &(yyvsp[-6].reg_value), &(yyvsp[-4].reg_value), &(yyvsp[-2].integer_value), (yyvsp[0].ast), FCML_TRUE, 0 ); }
#line 1881 "fcml_intel_parser_def.c"
    break;

  case 43: /* effective_address_components: reg '*' FCML_TK_INTEGER '+' exp  */
#line 218 "fcml_intel_parser_def.y"
                                              { (yyval.ast) = fcml_fn_ast_alloc_node_effective_address( NULL, &(yyvsp[-4].reg_value), &(yyvsp[-2].integer_value), (yyvsp[0].ast), FCML_FALSE, 0 ); }
#line 1887 "fcml_intel_parser_def.c"
    break;

  case 44: /* effective_address_components: reg '*' FCML_TK_INTEGER '-' exp  */
#line 219 "fcml_intel_parser_def.y"
                                              { (yyval.ast) = fcml_fn_ast_alloc_node_effective_address( NULL, &(yyvsp[-4].reg_value), &(yyvsp[-2].integer_value), (yyvsp[0].ast), FCML_TRUE, 0 ); }
#line 1893 "fcml_intel_parser_def.c"
    break;

  case 45: /* effective_address_components: reg '+' reg '+' exp  */
#line 220 "fcml_intel_parser_def.y"
                                              { (yyval.ast) = fcml_fn_ast_alloc_node_effective_address( &(yyvsp[-4].reg_value), &(yyvsp[-2].reg_value), NULL, (yyvsp[0].ast), FCML_FALSE, 0 ); }
#line 1899 "fcml_intel_parser_def.c"
    break;

  case 46: /* effective_address_components: reg '+' reg '-' exp  */
#line 221 "fcml_intel_parser_def.y"
                                              { (yyval.ast) = fcml_fn_ast_alloc_node_effective_address( &(yyvsp[-4].reg_value), &(yyvsp[-2].reg_value), NULL, (yyvsp[0].ast), FCML_TRUE, 0 ); }
#line 1905 "fcml_intel_parser_def.c"
    break;

  case 47: /* effective_address_components: reg '+' exp  */
#line 222 "fcml_intel_parser_def.y"
                                              { (yyval.ast) = fcml_fn_ast_alloc_node_effective_address( &(yyvsp[-2].reg_value), NULL, NULL, (yyvsp[0].ast), FCML_FALSE, 0 ); }
#line 1911 "fcml_intel_parser_def.c"
    break;

  case 48: /* effective_address_components: FCML_TK_REG_RIP '+' exp  */
#line 223 "fcml_intel_parser_def.y"
                                              { (yyval.ast) = fcml_fn_ast_alloc_node_effective_address( &(yyvsp[-2].reg_value), NULL, NULL, (yyvsp[0].ast), FCML_FALSE, 0 ); }
#line 1917 "fcml_intel_parser_def.c"
    break;

  case 49: /* effective_address_components: FCML_TK_SIB_HINT reg '+' exp  */
#line 224 "fcml_intel_parser_def.y"
                                              { (yyval.ast) = fcml_fn_ast_alloc_node_effective_address( &(yyvsp[-2].reg_value), NULL, NULL, (yyvsp[0].ast), FCML_FALSE, (yyvsp[-3].hints) ); }
#line 1923 "fcml_intel_parser_def.c"
    break;

  case 50: /* effective_address_components: reg '-' exp  */
#line 225 "fcml_intel_parser_def.y"
                                              { (yyval.ast) = fcml_fn_ast_alloc_node_effective_address( &(yyvsp[-2].reg_value), NULL, NULL, (yyvsp[0].ast), FCML_TRUE, 0 ); }
#line 1929 "fcml_intel_parser_def.c"
    break;

  case 51: /* effective_address_components: FCML_TK_SIB_HINT reg '-' exp  */
#line 226 "fcml_intel_parser_def.y"
                                              { (yyval.ast) = fcml_fn_ast_alloc_node_effective_address( &(yyvsp[-2].reg_value), NULL, NULL, (yyvsp[0].ast), FCML_TRUE, (yyvsp[-3].hints) ); }
#line 1935 "fcml_intel_parser_def.c"
    break;

  case 52: /* effective_address_components: exp  */
#line 227 "fcml_intel_parser_def.y"
                                              { (yyval.ast) = fcml_fn_ast_alloc_node_effective_address( NULL, NULL, NULL, (yyvsp[0].ast), FCML_FALSE, 0); }
#line 1941 "fcml_intel_parser_def.c"
    break;

  case 53: /* effective_address_components: FCML_TK_EAO_HINTS exp  */
#line 228 "fcml_intel_parser_def.y"
                                              { (yyval.ast) = fcml_fn_ast_alloc_node_effective_address( NULL, NULL, NULL, (yyvsp[0].ast), FCML_FALSE, (yyvsp[-1].hints)); }
#line 1947 "fcml_intel_parser_def.c"
    break;

  case 54: /* effective_address_components: FCML_TK_SIB_HINT exp  */
#line 229 "fcml_intel_parser_def.y"
                                              { (yyval.ast) = fcml_fn_ast_alloc_node_effective_address( NULL, NULL, NULL, (yyvsp[0].ast), FCML_FALSE, (yyvsp[-1].hints)); }
#line 1953 "fcml_intel_parser_def.c"
    break;

  case 55: /* segment_selector: FCML_TK_REG_SEG ':'  */
#line 232 "fcml_intel_parser_def.y"
                                              { (yyval.reg_value) = (yyvsp[-1].reg_value); }
#line 1959 "fcml_intel_parser_def.c"
    break;

  case 56: /* far_pointer: exp ':' exp  */
#line 235 "fcml_intel_parser_def.y"
                         { (yyval.ast) = fcml_fn_ast_alloc_node_far_pointer( (yyvsp[-2].ast), (yyvsp[0].ast) ); HANDLE_ERRORS((yyval.ast)); }
#line 1965 "fcml_intel_parser_def.c"
    break;

  case 57: /* exp: FCML_TK_INTEGER  */
#line 238 "fcml_intel_parser_def.y"
                                              { (yyval.ast) = fcml_fn_ast_alloc_node_integer( &(yyvsp[0].integer_value) ); HANDLE_ERRORS((yyval.ast)); }
#line 1971 "fcml_intel_parser_def.c"
    break;

  case 58: /* exp: FCML_TK_FLOAT  */
#line 239 "fcml_intel_parser_def.y"
                                              { (yyval.ast) = fcml_fn_ast_alloc_node_float( &(yyvsp[0].float_value) ); HANDLE_ERRORS((yyval.ast)); }
#line 1977 "fcml_intel_parser_def.c"
    break;

  case 59: /* exp: exp '-' exp  */
#line 240 "fcml_intel_parser_def.y"
                                              { (yyval.ast) = fcml_fn_ast_alloc_node_exp( FCML_EN_EXN_SUB, (yyvsp[-2].ast), (yyvsp[0].ast) ); HANDLE_ERRORS((yyval.ast)); }
#line 1983 "fcml_intel_parser_def.c"
    break;

  case 60: /* exp: exp '+' exp  */
#line 241 "fcml_intel_parser_def.y"
                                              { (yyval.ast) = fcml_fn_ast_alloc_node_exp( FCML_EN_EXN_ADD, (yyvsp[-2].ast), (yyvsp[0].ast) ); HANDLE_ERRORS((yyval.ast)); }
#line 1989 "fcml_intel_parser_def.c"
    break;

  case 61: /* exp: exp '/' exp  */
#line 242 "fcml_intel_parser_def.y"
                                              { (yyval.ast) = fcml_fn_ast_alloc_node_exp( FCML_EN_EXN_DIV, (yyvsp[-2].ast), (yyvsp[0].ast) ); HANDLE_ERRORS((yyval.ast)); }
#line 1995 "fcml_intel_parser_def.c"
    break;

  case 62: /* exp: exp '*' exp  */
#line 243 "fcml_intel_parser_def.y"
                                              { (yyval.ast) = fcml_fn_ast_alloc_node_exp( FCML_EN_EXN_MUL, (yyvsp[-2].ast), (yyvsp[0].ast) ); HANDLE_ERRORS((yyval.ast)); }
#line 2001 "fcml_intel_parser_def.c"
    break;

  case 63: /* exp: FCML_TK_SYMBOL  */
#line 244 "fcml_intel_parser_def.y"
                                              { (yyval.ast) = fcml_fn_ast_alloc_node_use_symbol( (yyvsp[0].symbol).text, (yyvsp[0].symbol).length ); HANDLE_ERRORS((yyval.ast)); }
#line 2007 "fcml_intel_parser_def.c"
    break;

  case 64: /* exp: '-' exp  */
#line 245 "fcml_intel_parser_def.y"
                                              { (yyval.ast) = fcml_fn_ast_alloc_node_uminus( (yyvsp[0].ast) ); HANDLE_ERRORS((yyval.ast)); }
#line 2013 "fcml_intel_parser_def.c"
    break;

  case 65: /* exp: '(' exp ')'  */
#line 246 "fcml_intel_parser_def.y"
                                              { (yyval.ast) = (yyvsp[-1].ast); }
#line 2019 "fcml_intel_parser_def.c"
    break;


#line 2023 "fcml_intel_parser_def.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == INTEL_EMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (&yylloc, pd, YY_("syntax error"));
    }

  yyerror_range[1] = yylloc;
  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= INTEL_EOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == INTEL_EOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, &yylloc, pd);
          yychar = INTEL_EMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp, pd);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  ++yylsp;
  YYLLOC_DEFAULT (*yylsp, yyerror_range, 2);

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (&yylloc, pd, YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != INTEL_EMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc, pd);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp, pd);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 259 "fcml_intel_parser_def.y"

