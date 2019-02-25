/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1


/* Substitute the variable and function names.  */
#define yyparse         gas_parse
#define yylex           gas_lex
#define yyerror         gas_error
#define yydebug         gas_debug
#define yynerrs         gas_nerrs


/* Copy the first part of user declarations.  */
#line 26 "fcml_gas_parser_def.y" /* yacc.c:339  */

    #include <stdio.h>
    
    #include "fcml_parser_utils.h"
    
    /* Macro responsible for handling 'Out of memory' errors. */
    #define HANDLE_ERRORS(x) if( !x ) { yyerror(&yylloc, pd, \
        "Out of memory."); YYERROR; }
    
    /* Macro responsible for adding error messages to result. */
    #define ADD_ERROR_MSG(x) { yyerror(&yylloc, pd, x); }
    

#line 86 "fcml_gas_parser_def.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "y.tab.h".  */
#ifndef YY_GAS_FCML_GAS_PARSER_DEF_H_INCLUDED
# define YY_GAS_FCML_GAS_PARSER_DEF_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int gas_debug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
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
    FCML_TK_SYMBOL = 273,
    FCML_TK_PREFIX = 274,
    FCML_TK_PO_BYTE = 275,
    FCML_OP_UMINUS = 276
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
#define FCML_TK_SYMBOL 273
#define FCML_TK_PREFIX 274
#define FCML_TK_PO_BYTE 275
#define FCML_OP_UMINUS 276

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 113 "fcml_gas_parser_def.y" /* yacc.c:355  */

    /*Complex values.*/
    fcml_st_ast_val_integer integer_value;
    fcml_st_register reg_value;
    fcml_st_ast_node *ast;
    struct {
        fcml_string text;
        int length;
    } symbol;
    fcml_hints hints;
    fcml_prefixes prefixes;
    fcml_bool bool_value;
    fcml_int int_value;

#line 183 "fcml_gas_parser_def.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif



int gas_parse (struct fcml_st_parser_data *pd);

#endif /* !YY_GAS_FCML_GAS_PARSER_DEF_H_INCLUDED  */

/* Copy the second part of user declarations.  */
#line 128 "fcml_gas_parser_def.y" /* yacc.c:358  */

    #include "fcml_gas_lexer.h"
    #define yyscanner ((yyscan_t)pd->scannerInfo)
    void gas_error(YYLTYPE *yyloc, struct fcml_st_parser_data *pd,
    	const char *error );

#line 219 "fcml_gas_parser_def.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

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

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
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


#if ! defined yyoverflow || YYERROR_VERBOSE

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
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
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
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  15
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   124

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  31
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  14
/* YYNRULES -- Number of rules.  */
#define YYNRULES  57
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  86

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   276

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,    28,     2,     2,     2,
      29,    30,    23,    22,    27,    21,     2,    24,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    26,     2,
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
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    25
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,   142,   142,   143,   144,   145,   146,   147,   150,   151,
     152,   153,   156,   157,   160,   163,   164,   167,   168,   169,
     170,   171,   172,   173,   174,   175,   176,   177,   178,   181,
     182,   183,   187,   188,   189,   193,   194,   195,   196,   197,
     198,   201,   205,   206,   207,   208,   209,   210,   211,   212,
     216,   217,   218,   219,   220,   221,   222,   227
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "FCML_TK_UNEXPECTED", "FCML_TK_REG_GPR",
  "FCML_TK_REG_SIMD", "FCML_TK_REG_FPU", "FCML_TK_REG_SEG",
  "FCML_TK_REG_OPMASK", "FCML_TK_REG_CR", "FCML_TK_REG_DR",
  "FCML_TK_REG_RIP", "FCML_TK_DECORATOR_BCAST", "FCML_TK_DECORATOR_ER",
  "FCML_TK_DECORATOR_Z", "FCML_TK_DECORATOR_SAE",
  "FCML_TK_OPMASK_REG_DECORATOR", "FCML_TK_INTEGER", "FCML_TK_SYMBOL",
  "FCML_TK_PREFIX", "FCML_TK_PO_BYTE", "'-'", "'+'", "'*'", "'/'",
  "FCML_OP_UMINUS", "':'", "','", "'$'", "'('", "')'", "$accept", "start",
  "instruction", "inst_prefixes", "mnemonic", "operand_list", "operand",
  "effective_address", "effective_address_components",
  "effective_address_components_without_dis", "segment_selector", "exp",
  "reg", "pseudo_operation", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,    45,    43,    42,    47,   276,    58,    44,    36,    40,
      41
};
# endif

#define YYPACT_NINF -27

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-27)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int8 yypact[] =
{
     -12,   -24,   -27,     2,    25,   -27,    11,    43,   -27,    19,
     -27,   -27,     2,     2,    46,   -27,   -27,   -27,    43,   -27,
     -27,   -27,    29,   -27,   -27,   -27,   -27,   -27,    15,     2,
      69,    18,   -27,   -11,   -27,   -27,    64,    82,    49,   -27,
     -27,   -27,    78,     2,     2,     2,     2,    18,   -27,    29,
      76,    46,   -27,    59,   108,    -6,    43,   -27,   -27,    77,
     -27,     7,   -27,   -27,    80,   -27,    60,    60,   -27,   -27,
     -27,    27,   108,   -27,   -27,   -27,   -27,    75,   -27,    32,
      65,    90,   -27,   -27,    67,   -27
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,    14,    12,     0,     0,     3,     0,     8,     4,     5,
      42,    47,     0,     0,    57,     1,    14,    13,    10,    50,
      51,    52,    53,    54,    55,    56,    28,    27,     0,     0,
       0,     9,    15,    18,    29,    32,     0,    34,    23,     6,
       7,    48,     0,     0,     0,     0,     0,    11,    41,     0,
      22,    17,    53,     0,     0,     0,     0,    31,    21,    19,
      30,     0,    33,    26,    24,    49,    43,    44,    46,    45,
      35,     0,     0,    36,    16,    20,    25,     0,    38,     0,
       0,     0,    37,    40,     0,    39
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -27,   -27,   100,   -27,   104,   101,    66,    92,    85,    86,
     -27,    -3,   -26,   115
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     4,     5,     6,     7,    31,    32,    33,    34,    35,
      36,    37,    38,     8
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      14,    57,     9,    58,    55,    59,     1,     2,     3,    41,
      42,    19,    20,    21,    52,    23,    24,    25,    53,    10,
      11,    72,    49,    12,    73,    15,    51,    42,    71,    16,
      17,    13,    10,    11,    54,    55,    12,    16,     2,     3,
      66,    67,    68,    69,    30,    56,    79,    19,    20,    21,
      22,    23,    24,    25,    77,    48,    26,    78,    27,    81,
      10,    11,    82,    63,    12,    64,    28,    43,    44,    45,
      46,    29,    30,    19,    20,    21,    52,    23,    24,    25,
      53,    10,    11,    45,    46,    12,    10,    11,    57,    70,
      12,    75,    80,    30,    76,    83,    54,    85,    13,    43,
      44,    45,    46,    43,    44,    45,    46,    84,    65,    39,
      18,    61,    19,    20,    21,    52,    23,    24,    25,    47,
      50,    60,    74,    62,    40
};

static const yytype_uint8 yycheck[] =
{
       3,    12,    26,    14,    30,    16,    18,    19,    20,    12,
      13,     4,     5,     6,     7,     8,     9,    10,    11,    17,
      18,    27,     7,    21,    30,     0,    29,    30,    54,    18,
      19,    29,    17,    18,    27,    61,    21,    18,    19,    20,
      43,    44,    45,    46,    29,    27,    72,     4,     5,     6,
       7,     8,     9,    10,    27,    26,    13,    30,    15,    27,
      17,    18,    30,    14,    21,    16,    23,    21,    22,    23,
      24,    28,    29,     4,     5,     6,     7,     8,     9,    10,
      11,    17,    18,    23,    24,    21,    17,    18,    12,    30,
      21,    14,    17,    29,    14,    30,    27,    30,    29,    21,
      22,    23,    24,    21,    22,    23,    24,    17,    30,     9,
       6,    29,     4,     5,     6,     7,     8,     9,    10,    18,
      28,    36,    56,    37,     9
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    18,    19,    20,    32,    33,    34,    35,    44,    26,
      17,    18,    21,    29,    42,     0,    18,    19,    35,     4,
       5,     6,     7,     8,     9,    10,    13,    15,    23,    28,
      29,    36,    37,    38,    39,    40,    41,    42,    43,    33,
      44,    42,    42,    21,    22,    23,    24,    36,    26,     7,
      38,    42,     7,    11,    27,    43,    27,    12,    14,    16,
      39,    29,    40,    14,    16,    30,    42,    42,    42,    42,
      30,    43,    27,    30,    37,    14,    14,    27,    30,    43,
      17,    27,    30,    30,    17,    30
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    31,    32,    32,    32,    32,    32,    32,    33,    33,
      33,    33,    34,    34,    35,    36,    36,    37,    37,    37,
      37,    37,    37,    37,    37,    37,    37,    37,    37,    38,
      38,    38,    39,    39,    39,    40,    40,    40,    40,    40,
      40,    41,    42,    42,    42,    42,    42,    42,    42,    42,
      43,    43,    43,    43,    43,    43,    43,    44
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     1,     1,     2,     3,     3,     1,     2,
       2,     3,     1,     2,     1,     1,     3,     2,     1,     2,
       3,     2,     2,     1,     2,     3,     2,     1,     1,     1,
       2,     2,     1,     2,     1,     3,     3,     5,     4,     7,
       6,     2,     1,     3,     3,     3,     3,     1,     2,     3,
       1,     1,     1,     1,     1,     1,     1,     2
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
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

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256


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
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static unsigned
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  unsigned res = 0;
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

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, Location, pd); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, struct fcml_st_parser_data *pd)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  YYUSE (yylocationp);
  YYUSE (pd);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  switch (yytype)
    {
          case 4: /* FCML_TK_REG_GPR  */
#line 111 "fcml_gas_parser_def.y" /* yacc.c:684  */
      { YYFPRINTF(yyoutput, "Type: %s Size: %d Reg: %d x64_exp: %d", fcml_fn_pu_reg_type_to_string( ((*yyvaluep).reg_value).type ), ((*yyvaluep).reg_value).size, ((*yyvaluep).reg_value).reg, ((*yyvaluep).reg_value).x64_exp); }
#line 845 "fcml_gas_parser_def.c" /* yacc.c:684  */
        break;

    case 5: /* FCML_TK_REG_SIMD  */
#line 111 "fcml_gas_parser_def.y" /* yacc.c:684  */
      { YYFPRINTF(yyoutput, "Type: %s Size: %d Reg: %d x64_exp: %d", fcml_fn_pu_reg_type_to_string( ((*yyvaluep).reg_value).type ), ((*yyvaluep).reg_value).size, ((*yyvaluep).reg_value).reg, ((*yyvaluep).reg_value).x64_exp); }
#line 851 "fcml_gas_parser_def.c" /* yacc.c:684  */
        break;

    case 6: /* FCML_TK_REG_FPU  */
#line 111 "fcml_gas_parser_def.y" /* yacc.c:684  */
      { YYFPRINTF(yyoutput, "Type: %s Size: %d Reg: %d x64_exp: %d", fcml_fn_pu_reg_type_to_string( ((*yyvaluep).reg_value).type ), ((*yyvaluep).reg_value).size, ((*yyvaluep).reg_value).reg, ((*yyvaluep).reg_value).x64_exp); }
#line 857 "fcml_gas_parser_def.c" /* yacc.c:684  */
        break;

    case 7: /* FCML_TK_REG_SEG  */
#line 111 "fcml_gas_parser_def.y" /* yacc.c:684  */
      { YYFPRINTF(yyoutput, "Type: %s Size: %d Reg: %d x64_exp: %d", fcml_fn_pu_reg_type_to_string( ((*yyvaluep).reg_value).type ), ((*yyvaluep).reg_value).size, ((*yyvaluep).reg_value).reg, ((*yyvaluep).reg_value).x64_exp); }
#line 863 "fcml_gas_parser_def.c" /* yacc.c:684  */
        break;

    case 8: /* FCML_TK_REG_OPMASK  */
#line 111 "fcml_gas_parser_def.y" /* yacc.c:684  */
      { YYFPRINTF(yyoutput, "Type: %s Size: %d Reg: %d x64_exp: %d", fcml_fn_pu_reg_type_to_string( ((*yyvaluep).reg_value).type ), ((*yyvaluep).reg_value).size, ((*yyvaluep).reg_value).reg, ((*yyvaluep).reg_value).x64_exp); }
#line 869 "fcml_gas_parser_def.c" /* yacc.c:684  */
        break;

    case 9: /* FCML_TK_REG_CR  */
#line 111 "fcml_gas_parser_def.y" /* yacc.c:684  */
      { YYFPRINTF(yyoutput, "Type: %s Size: %d Reg: %d x64_exp: %d", fcml_fn_pu_reg_type_to_string( ((*yyvaluep).reg_value).type ), ((*yyvaluep).reg_value).size, ((*yyvaluep).reg_value).reg, ((*yyvaluep).reg_value).x64_exp); }
#line 875 "fcml_gas_parser_def.c" /* yacc.c:684  */
        break;

    case 10: /* FCML_TK_REG_DR  */
#line 111 "fcml_gas_parser_def.y" /* yacc.c:684  */
      { YYFPRINTF(yyoutput, "Type: %s Size: %d Reg: %d x64_exp: %d", fcml_fn_pu_reg_type_to_string( ((*yyvaluep).reg_value).type ), ((*yyvaluep).reg_value).size, ((*yyvaluep).reg_value).reg, ((*yyvaluep).reg_value).x64_exp); }
#line 881 "fcml_gas_parser_def.c" /* yacc.c:684  */
        break;

    case 11: /* FCML_TK_REG_RIP  */
#line 111 "fcml_gas_parser_def.y" /* yacc.c:684  */
      { YYFPRINTF(yyoutput, "Type: %s Size: %d Reg: %d x64_exp: %d", fcml_fn_pu_reg_type_to_string( ((*yyvaluep).reg_value).type ), ((*yyvaluep).reg_value).size, ((*yyvaluep).reg_value).reg, ((*yyvaluep).reg_value).x64_exp); }
#line 887 "fcml_gas_parser_def.c" /* yacc.c:684  */
        break;

    case 16: /* FCML_TK_OPMASK_REG_DECORATOR  */
#line 111 "fcml_gas_parser_def.y" /* yacc.c:684  */
      { YYFPRINTF(yyoutput, "Type: %s Size: %d Reg: %d x64_exp: %d", fcml_fn_pu_reg_type_to_string( ((*yyvaluep).reg_value).type ), ((*yyvaluep).reg_value).size, ((*yyvaluep).reg_value).reg, ((*yyvaluep).reg_value).x64_exp); }
#line 893 "fcml_gas_parser_def.c" /* yacc.c:684  */
        break;

    case 17: /* FCML_TK_INTEGER  */
#line 109 "fcml_gas_parser_def.y" /* yacc.c:684  */
      { YYFPRINTF(yyoutput, "Integer: %ld Overflow: %d", ((*yyvaluep).integer_value).value, ((*yyvaluep).integer_value).overflow); }
#line 899 "fcml_gas_parser_def.c" /* yacc.c:684  */
        break;

    case 33: /* instruction  */
#line 110 "fcml_gas_parser_def.y" /* yacc.c:684  */
      { YYFPRINTF(yyoutput, "AST-Type: %d", ((*yyvaluep).ast)->type); }
#line 905 "fcml_gas_parser_def.c" /* yacc.c:684  */
        break;

    case 36: /* operand_list  */
#line 110 "fcml_gas_parser_def.y" /* yacc.c:684  */
      { YYFPRINTF(yyoutput, "AST-Type: %d", ((*yyvaluep).ast)->type); }
#line 911 "fcml_gas_parser_def.c" /* yacc.c:684  */
        break;

    case 37: /* operand  */
#line 110 "fcml_gas_parser_def.y" /* yacc.c:684  */
      { YYFPRINTF(yyoutput, "AST-Type: %d", ((*yyvaluep).ast)->type); }
#line 917 "fcml_gas_parser_def.c" /* yacc.c:684  */
        break;

    case 38: /* effective_address  */
#line 110 "fcml_gas_parser_def.y" /* yacc.c:684  */
      { YYFPRINTF(yyoutput, "AST-Type: %d", ((*yyvaluep).ast)->type); }
#line 923 "fcml_gas_parser_def.c" /* yacc.c:684  */
        break;

    case 39: /* effective_address_components  */
#line 110 "fcml_gas_parser_def.y" /* yacc.c:684  */
      { YYFPRINTF(yyoutput, "AST-Type: %d", ((*yyvaluep).ast)->type); }
#line 929 "fcml_gas_parser_def.c" /* yacc.c:684  */
        break;

    case 40: /* effective_address_components_without_dis  */
#line 110 "fcml_gas_parser_def.y" /* yacc.c:684  */
      { YYFPRINTF(yyoutput, "AST-Type: %d", ((*yyvaluep).ast)->type); }
#line 935 "fcml_gas_parser_def.c" /* yacc.c:684  */
        break;

    case 41: /* segment_selector  */
#line 111 "fcml_gas_parser_def.y" /* yacc.c:684  */
      { YYFPRINTF(yyoutput, "Type: %s Size: %d Reg: %d x64_exp: %d", fcml_fn_pu_reg_type_to_string( ((*yyvaluep).reg_value).type ), ((*yyvaluep).reg_value).size, ((*yyvaluep).reg_value).reg, ((*yyvaluep).reg_value).x64_exp); }
#line 941 "fcml_gas_parser_def.c" /* yacc.c:684  */
        break;

    case 42: /* exp  */
#line 110 "fcml_gas_parser_def.y" /* yacc.c:684  */
      { YYFPRINTF(yyoutput, "AST-Type: %d", ((*yyvaluep).ast)->type); }
#line 947 "fcml_gas_parser_def.c" /* yacc.c:684  */
        break;

    case 43: /* reg  */
#line 111 "fcml_gas_parser_def.y" /* yacc.c:684  */
      { YYFPRINTF(yyoutput, "Type: %s Size: %d Reg: %d x64_exp: %d", fcml_fn_pu_reg_type_to_string( ((*yyvaluep).reg_value).type ), ((*yyvaluep).reg_value).size, ((*yyvaluep).reg_value).reg, ((*yyvaluep).reg_value).x64_exp); }
#line 953 "fcml_gas_parser_def.c" /* yacc.c:684  */
        break;

    case 44: /* pseudo_operation  */
#line 110 "fcml_gas_parser_def.y" /* yacc.c:684  */
      { YYFPRINTF(yyoutput, "AST-Type: %d", ((*yyvaluep).ast)->type); }
#line 959 "fcml_gas_parser_def.c" /* yacc.c:684  */
        break;


      default:
        break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, struct fcml_st_parser_data *pd)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp, pd);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule, struct fcml_st_parser_data *pd)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                       , &(yylsp[(yyi + 1) - (yynrhs)])                       , pd);
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
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, struct fcml_st_parser_data *pd)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  YYUSE (pd);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  switch (yytype)
    {
          case 33: /* instruction  */
#line 106 "fcml_gas_parser_def.y" /* yacc.c:1257  */
      { fcml_fn_ast_free_node(((*yyvaluep).ast)); }
#line 1309 "fcml_gas_parser_def.c" /* yacc.c:1257  */
        break;

    case 36: /* operand_list  */
#line 106 "fcml_gas_parser_def.y" /* yacc.c:1257  */
      { fcml_fn_ast_free_node(((*yyvaluep).ast)); }
#line 1315 "fcml_gas_parser_def.c" /* yacc.c:1257  */
        break;

    case 37: /* operand  */
#line 106 "fcml_gas_parser_def.y" /* yacc.c:1257  */
      { fcml_fn_ast_free_node(((*yyvaluep).ast)); }
#line 1321 "fcml_gas_parser_def.c" /* yacc.c:1257  */
        break;

    case 38: /* effective_address  */
#line 106 "fcml_gas_parser_def.y" /* yacc.c:1257  */
      { fcml_fn_ast_free_node(((*yyvaluep).ast)); }
#line 1327 "fcml_gas_parser_def.c" /* yacc.c:1257  */
        break;

    case 39: /* effective_address_components  */
#line 106 "fcml_gas_parser_def.y" /* yacc.c:1257  */
      { fcml_fn_ast_free_node(((*yyvaluep).ast)); }
#line 1333 "fcml_gas_parser_def.c" /* yacc.c:1257  */
        break;

    case 40: /* effective_address_components_without_dis  */
#line 106 "fcml_gas_parser_def.y" /* yacc.c:1257  */
      { fcml_fn_ast_free_node(((*yyvaluep).ast)); }
#line 1339 "fcml_gas_parser_def.c" /* yacc.c:1257  */
        break;

    case 42: /* exp  */
#line 106 "fcml_gas_parser_def.y" /* yacc.c:1257  */
      { fcml_fn_ast_free_node(((*yyvaluep).ast)); }
#line 1345 "fcml_gas_parser_def.c" /* yacc.c:1257  */
        break;

    case 44: /* pseudo_operation  */
#line 106 "fcml_gas_parser_def.y" /* yacc.c:1257  */
      { fcml_fn_ast_free_node(((*yyvaluep).ast)); }
#line 1351 "fcml_gas_parser_def.c" /* yacc.c:1257  */
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
/* The lookahead symbol.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

/* Location data for the lookahead symbol.  */
static YYLTYPE yyloc_default
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
YYLTYPE yylloc = yyloc_default;

    /* Number of syntax errors so far.  */
    int yynerrs;

    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.
       'yyls': related to locations.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

/* User initialization code.  */
#line 135 "fcml_gas_parser_def.y" /* yacc.c:1429  */
{ 
    /* Uncomment it in order to enable debugging */
    /* gas_debug = 1; */
}

#line 1465 "fcml_gas_parser_def.c" /* yacc.c:1429  */
  yylsp[0] = yylloc;
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yyls1, yysize * sizeof (*yylsp),
                    &yystacksize);

        yyls = yyls1;
        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex (&yylval, &yylloc, yyscanner);
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;
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
| yyreduce -- Do a reduction.  |
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

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 3:
#line 143 "fcml_gas_parser_def.y" /* yacc.c:1646  */
    { pd->tree = (yyvsp[0].ast);   pd->symbol = NULL; }
#line 1654 "fcml_gas_parser_def.c" /* yacc.c:1646  */
    break;

  case 4:
#line 144 "fcml_gas_parser_def.y" /* yacc.c:1646  */
    { pd->tree = (yyvsp[0].ast);   pd->symbol = NULL; }
#line 1660 "fcml_gas_parser_def.c" /* yacc.c:1646  */
    break;

  case 5:
#line 145 "fcml_gas_parser_def.y" /* yacc.c:1646  */
    { pd->tree = NULL; pd->symbol = fcml_fn_ast_alloc_node_define_symbol( pd->ip, (yyvsp[-1].symbol).text, (yyvsp[-1].symbol).length ); HANDLE_ERRORS( pd->symbol ); }
#line 1666 "fcml_gas_parser_def.c" /* yacc.c:1646  */
    break;

  case 6:
#line 146 "fcml_gas_parser_def.y" /* yacc.c:1646  */
    { pd->tree = (yyvsp[0].ast);   pd->symbol = fcml_fn_ast_alloc_node_define_symbol( pd->ip, (yyvsp[-2].symbol).text, (yyvsp[-2].symbol).length ); HANDLE_ERRORS( pd->symbol ); }
#line 1672 "fcml_gas_parser_def.c" /* yacc.c:1646  */
    break;

  case 7:
#line 147 "fcml_gas_parser_def.y" /* yacc.c:1646  */
    { pd->tree = (yyvsp[0].ast);   pd->symbol = fcml_fn_ast_alloc_node_define_symbol( pd->ip, (yyvsp[-2].symbol).text, (yyvsp[-2].symbol).length ); HANDLE_ERRORS( pd->symbol ); }
#line 1678 "fcml_gas_parser_def.c" /* yacc.c:1646  */
    break;

  case 8:
#line 150 "fcml_gas_parser_def.y" /* yacc.c:1646  */
    { (yyval.ast) = fcml_fn_ast_alloc_node_instruction( 0, (yyvsp[0].symbol).text, (yyvsp[0].symbol).length, 0, NULL ); HANDLE_ERRORS((yyval.ast)); }
#line 1684 "fcml_gas_parser_def.c" /* yacc.c:1646  */
    break;

  case 9:
#line 151 "fcml_gas_parser_def.y" /* yacc.c:1646  */
    { (yyval.ast) = fcml_fn_ast_alloc_node_instruction( 0, (yyvsp[-1].symbol).text, (yyvsp[-1].symbol).length, 0, (yyvsp[0].ast) ); HANDLE_ERRORS((yyval.ast)); }
#line 1690 "fcml_gas_parser_def.c" /* yacc.c:1646  */
    break;

  case 10:
#line 152 "fcml_gas_parser_def.y" /* yacc.c:1646  */
    { (yyval.ast) = fcml_fn_ast_alloc_node_instruction( (yyvsp[-1].prefixes), (yyvsp[0].symbol).text, (yyvsp[0].symbol).length, 0, NULL ); HANDLE_ERRORS((yyval.ast)); }
#line 1696 "fcml_gas_parser_def.c" /* yacc.c:1646  */
    break;

  case 11:
#line 153 "fcml_gas_parser_def.y" /* yacc.c:1646  */
    { (yyval.ast) = fcml_fn_ast_alloc_node_instruction( (yyvsp[-2].prefixes), (yyvsp[-1].symbol).text, (yyvsp[-1].symbol).length, 0, (yyvsp[0].ast) ); HANDLE_ERRORS((yyval.ast)); }
#line 1702 "fcml_gas_parser_def.c" /* yacc.c:1646  */
    break;

  case 13:
#line 157 "fcml_gas_parser_def.y" /* yacc.c:1646  */
    { if( (yyvsp[-1].prefixes) & (yyvsp[0].prefixes) ) { ADD_ERROR_MSG( "Doubled prefixes." ); YYERROR; } else { (yyval.prefixes) = (yyvsp[-1].prefixes) | (yyvsp[0].prefixes); } }
#line 1708 "fcml_gas_parser_def.c" /* yacc.c:1646  */
    break;

  case 15:
#line 163 "fcml_gas_parser_def.y" /* yacc.c:1646  */
    { (yyval.ast) = fcml_fn_ast_alloc_node_operand_list( (yyvsp[0].ast), NULL ); HANDLE_ERRORS((yyval.ast)); }
#line 1714 "fcml_gas_parser_def.c" /* yacc.c:1646  */
    break;

  case 16:
#line 164 "fcml_gas_parser_def.y" /* yacc.c:1646  */
    { (yyval.ast) = fcml_fn_ast_alloc_node_operand_list( (yyvsp[-2].ast), (yyvsp[0].ast) ); HANDLE_ERRORS((yyval.ast)); }
#line 1720 "fcml_gas_parser_def.c" /* yacc.c:1646  */
    break;

  case 17:
#line 167 "fcml_gas_parser_def.y" /* yacc.c:1646  */
    { (yyval.ast) = (yyvsp[0].ast); }
#line 1726 "fcml_gas_parser_def.c" /* yacc.c:1646  */
    break;

  case 19:
#line 169 "fcml_gas_parser_def.y" /* yacc.c:1646  */
    { (yyval.ast) = fcml_fn_ast_decorate_effective_address((yyvsp[-1].ast), &(yyvsp[0].reg_value), FCML_FALSE); }
#line 1732 "fcml_gas_parser_def.c" /* yacc.c:1646  */
    break;

  case 20:
#line 170 "fcml_gas_parser_def.y" /* yacc.c:1646  */
    { (yyval.ast) = fcml_fn_ast_decorate_effective_address((yyvsp[-2].ast), &(yyvsp[-1].reg_value), FCML_TRUE); }
#line 1738 "fcml_gas_parser_def.c" /* yacc.c:1646  */
    break;

  case 21:
#line 171 "fcml_gas_parser_def.y" /* yacc.c:1646  */
    { (yyval.ast) = fcml_fn_ast_decorate_effective_address((yyvsp[-1].ast), NULL, FCML_TRUE); }
#line 1744 "fcml_gas_parser_def.c" /* yacc.c:1646  */
    break;

  case 22:
#line 172 "fcml_gas_parser_def.y" /* yacc.c:1646  */
    { (yyval.ast) = fcml_fn_ast_set_effective_address_hins( (yyvsp[0].ast), FCML_HINT_INDIRECT_POINTER ); }
#line 1750 "fcml_gas_parser_def.c" /* yacc.c:1646  */
    break;

  case 23:
#line 173 "fcml_gas_parser_def.y" /* yacc.c:1646  */
    { (yyval.ast) = fcml_fn_ast_alloc_node_register( &(yyvsp[0].reg_value), NULL, FCML_FALSE ); HANDLE_ERRORS((yyval.ast)); }
#line 1756 "fcml_gas_parser_def.c" /* yacc.c:1646  */
    break;

  case 24:
#line 174 "fcml_gas_parser_def.y" /* yacc.c:1646  */
    { (yyval.ast) = fcml_fn_ast_alloc_node_register( &(yyvsp[-1].reg_value), &(yyvsp[0].reg_value), FCML_FALSE ); HANDLE_ERRORS((yyval.ast)); }
#line 1762 "fcml_gas_parser_def.c" /* yacc.c:1646  */
    break;

  case 25:
#line 175 "fcml_gas_parser_def.y" /* yacc.c:1646  */
    { (yyval.ast) = fcml_fn_ast_alloc_node_register( &(yyvsp[-2].reg_value), &(yyvsp[-1].reg_value), FCML_TRUE ); HANDLE_ERRORS((yyval.ast)); }
#line 1768 "fcml_gas_parser_def.c" /* yacc.c:1646  */
    break;

  case 26:
#line 176 "fcml_gas_parser_def.y" /* yacc.c:1646  */
    { (yyval.ast) = fcml_fn_ast_alloc_node_register( &(yyvsp[-1].reg_value), NULL, FCML_TRUE ); HANDLE_ERRORS((yyval.ast)); }
#line 1774 "fcml_gas_parser_def.c" /* yacc.c:1646  */
    break;

  case 27:
#line 177 "fcml_gas_parser_def.y" /* yacc.c:1646  */
    { (yyval.ast) = fcml_fn_ast_alloc_node_virtual( FCML_TRUE, FCML_FALSE, 0 ); HANDLE_ERRORS((yyval.ast)); }
#line 1780 "fcml_gas_parser_def.c" /* yacc.c:1646  */
    break;

  case 28:
#line 178 "fcml_gas_parser_def.y" /* yacc.c:1646  */
    { (yyval.ast) = fcml_fn_ast_alloc_node_virtual( FCML_FALSE, FCML_TRUE, (yyvsp[0].int_value) ); HANDLE_ERRORS((yyval.ast)); }
#line 1786 "fcml_gas_parser_def.c" /* yacc.c:1646  */
    break;

  case 30:
#line 182 "fcml_gas_parser_def.y" /* yacc.c:1646  */
    { (yyval.ast) = fcml_fn_ast_set_effective_address_details( &(yyvsp[-1].reg_value), FCML_OS_UNDEFINED, 0, (yyvsp[0].ast) ); }
#line 1792 "fcml_gas_parser_def.c" /* yacc.c:1646  */
    break;

  case 31:
#line 183 "fcml_gas_parser_def.y" /* yacc.c:1646  */
    { (yyval.ast) = fcml_fn_ast_set_effective_address_details( NULL, FCML_OS_UNDEFINED, (yyvsp[0].int_value), (yyvsp[-1].ast) ); }
#line 1798 "fcml_gas_parser_def.c" /* yacc.c:1646  */
    break;

  case 33:
#line 188 "fcml_gas_parser_def.y" /* yacc.c:1646  */
    { (yyval.ast) = fcml_fn_ast_set_displacemnt( (yyvsp[-1].ast), (yyvsp[0].ast) ); }
#line 1804 "fcml_gas_parser_def.c" /* yacc.c:1646  */
    break;

  case 34:
#line 189 "fcml_gas_parser_def.y" /* yacc.c:1646  */
    { (yyval.ast) = fcml_fn_ast_alloc_node_effective_address( NULL, NULL, NULL, (yyvsp[0].ast), FCML_FALSE, 0); }
#line 1810 "fcml_gas_parser_def.c" /* yacc.c:1646  */
    break;

  case 35:
#line 193 "fcml_gas_parser_def.y" /* yacc.c:1646  */
    { (yyval.ast) = fcml_fn_ast_alloc_node_effective_address( &(yyvsp[-1].reg_value), NULL, NULL, NULL, FCML_FALSE, 0 ); }
#line 1816 "fcml_gas_parser_def.c" /* yacc.c:1646  */
    break;

  case 36:
#line 194 "fcml_gas_parser_def.y" /* yacc.c:1646  */
    { (yyval.ast) = fcml_fn_ast_alloc_node_effective_address( &(yyvsp[-1].reg_value), NULL, NULL, NULL, FCML_FALSE, 0 ); }
#line 1822 "fcml_gas_parser_def.c" /* yacc.c:1646  */
    break;

  case 37:
#line 195 "fcml_gas_parser_def.y" /* yacc.c:1646  */
    { (yyval.ast) = fcml_fn_ast_alloc_node_effective_address( &(yyvsp[-3].reg_value), &(yyvsp[-1].reg_value), NULL, NULL, FCML_FALSE, 0 ); }
#line 1828 "fcml_gas_parser_def.c" /* yacc.c:1646  */
    break;

  case 38:
#line 196 "fcml_gas_parser_def.y" /* yacc.c:1646  */
    { (yyval.ast) = fcml_fn_ast_alloc_node_effective_address( NULL, &(yyvsp[-1].reg_value), NULL, NULL, FCML_FALSE, 0 ); }
#line 1834 "fcml_gas_parser_def.c" /* yacc.c:1646  */
    break;

  case 39:
#line 197 "fcml_gas_parser_def.y" /* yacc.c:1646  */
    { (yyval.ast) = fcml_fn_ast_alloc_node_effective_address( &(yyvsp[-5].reg_value), &(yyvsp[-3].reg_value), &(yyvsp[-1].integer_value), NULL, FCML_FALSE, 0 ); }
#line 1840 "fcml_gas_parser_def.c" /* yacc.c:1646  */
    break;

  case 40:
#line 198 "fcml_gas_parser_def.y" /* yacc.c:1646  */
    { (yyval.ast) = fcml_fn_ast_alloc_node_effective_address( NULL, &(yyvsp[-3].reg_value), &(yyvsp[-1].integer_value), NULL, FCML_FALSE, 0 ); }
#line 1846 "fcml_gas_parser_def.c" /* yacc.c:1646  */
    break;

  case 41:
#line 201 "fcml_gas_parser_def.y" /* yacc.c:1646  */
    { (yyval.reg_value) = (yyvsp[-1].reg_value); }
#line 1852 "fcml_gas_parser_def.c" /* yacc.c:1646  */
    break;

  case 42:
#line 205 "fcml_gas_parser_def.y" /* yacc.c:1646  */
    { (yyval.ast) = fcml_fn_ast_alloc_node_integer( &(yyvsp[0].integer_value) ); HANDLE_ERRORS((yyval.ast)); }
#line 1858 "fcml_gas_parser_def.c" /* yacc.c:1646  */
    break;

  case 43:
#line 206 "fcml_gas_parser_def.y" /* yacc.c:1646  */
    { (yyval.ast) = fcml_fn_ast_alloc_node_exp( FCML_EN_EXN_SUB, (yyvsp[-2].ast), (yyvsp[0].ast) ); HANDLE_ERRORS((yyval.ast)); }
#line 1864 "fcml_gas_parser_def.c" /* yacc.c:1646  */
    break;

  case 44:
#line 207 "fcml_gas_parser_def.y" /* yacc.c:1646  */
    { (yyval.ast) = fcml_fn_ast_alloc_node_exp( FCML_EN_EXN_ADD, (yyvsp[-2].ast), (yyvsp[0].ast) ); HANDLE_ERRORS((yyval.ast)); }
#line 1870 "fcml_gas_parser_def.c" /* yacc.c:1646  */
    break;

  case 45:
#line 208 "fcml_gas_parser_def.y" /* yacc.c:1646  */
    { (yyval.ast) = fcml_fn_ast_alloc_node_exp( FCML_EN_EXN_DIV, (yyvsp[-2].ast), (yyvsp[0].ast) ); HANDLE_ERRORS((yyval.ast)); }
#line 1876 "fcml_gas_parser_def.c" /* yacc.c:1646  */
    break;

  case 46:
#line 209 "fcml_gas_parser_def.y" /* yacc.c:1646  */
    { (yyval.ast) = fcml_fn_ast_alloc_node_exp( FCML_EN_EXN_MUL, (yyvsp[-2].ast), (yyvsp[0].ast) ); HANDLE_ERRORS((yyval.ast)); }
#line 1882 "fcml_gas_parser_def.c" /* yacc.c:1646  */
    break;

  case 47:
#line 210 "fcml_gas_parser_def.y" /* yacc.c:1646  */
    { (yyval.ast) = fcml_fn_ast_alloc_node_use_symbol( (yyvsp[0].symbol).text, (yyvsp[0].symbol).length ); HANDLE_ERRORS((yyval.ast)); }
#line 1888 "fcml_gas_parser_def.c" /* yacc.c:1646  */
    break;

  case 48:
#line 211 "fcml_gas_parser_def.y" /* yacc.c:1646  */
    { (yyval.ast) = fcml_fn_ast_alloc_node_uminus( (yyvsp[0].ast) ); HANDLE_ERRORS((yyval.ast)); }
#line 1894 "fcml_gas_parser_def.c" /* yacc.c:1646  */
    break;

  case 49:
#line 212 "fcml_gas_parser_def.y" /* yacc.c:1646  */
    { (yyval.ast) = (yyvsp[-1].ast); }
#line 1900 "fcml_gas_parser_def.c" /* yacc.c:1646  */
    break;

  case 57:
#line 227 "fcml_gas_parser_def.y" /* yacc.c:1646  */
    { (yyval.ast) = fcml_fn_ast_alloc_node_pseudo_operation( (yyvsp[-1].symbol).text, (yyvsp[-1].symbol).length, (yyvsp[0].ast) ); HANDLE_ERRORS((yyval.ast)); }
#line 1906 "fcml_gas_parser_def.c" /* yacc.c:1646  */
    break;


#line 1910 "fcml_gas_parser_def.c" /* yacc.c:1646  */
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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (&yylloc, pd, YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (&yylloc, pd, yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }

  yyerror_range[1] = yylloc;

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, &yylloc, pd);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  yyerror_range[1] = yylsp[1-yylen];
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

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
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
                  yystos[yystate], yyvsp, yylsp, pd);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (&yylloc, pd, YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
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
                  yystos[*yyssp], yyvsp, yylsp, pd);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 230 "fcml_gas_parser_def.y" /* yacc.c:1906  */

