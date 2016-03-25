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
#define yyparse         intel_parse
#define yylex           intel_lex
#define yyerror         intel_error
#define yydebug         intel_debug
#define yynerrs         intel_nerrs


/* Copy the first part of user declarations.  */
#line 25 "fcml_intel_parser_def.y" /* yacc.c:339  */

    #include <stdio.h>
    
    #include "fcml_parser_utils.h"
    
    void intel_error( struct fcml_st_parser_data *pd, const char *error );
    
    /* Macro responsible for handling 'Out of memory' errors. */
    #define HANDLE_ERRORS(x) if( !x ) { yyerror(pd, "Out of memory."); YYERROR; }
    
    /* Macro responsible for adding error messages to result. */
    #define ADD_ERROR_MSG(x) { yyerror( pd, x ); }
    

#line 87 "fcml_intel_parser_def.c" /* yacc.c:339  */

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
#ifndef YY_INTEL_FCML_INTEL_PARSER_DEF_H_INCLUDED
# define YY_INTEL_FCML_INTEL_PARSER_DEF_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int intel_debug;
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

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 104 "fcml_intel_parser_def.y" /* yacc.c:355  */

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

#line 180 "fcml_intel_parser_def.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif



int intel_parse (struct fcml_st_parser_data *pd);

#endif /* !YY_INTEL_FCML_INTEL_PARSER_DEF_H_INCLUDED  */

/* Copy the second part of user declarations.  */
#line 119 "fcml_intel_parser_def.y" /* yacc.c:358  */

    #include "fcml_intel_lexer.h"
    #define yyscanner ((yyscan_t)pd->scannerInfo)

#line 200 "fcml_intel_parser_def.c" /* yacc.c:358  */

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
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

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
#define YYFINAL  8
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   166

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  30
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  14
/* YYNRULES -- Number of rules.  */
#define YYNRULES  60
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  99

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   274

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      28,    29,    21,    20,    25,    19,     2,    22,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    24,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    26,     2,    27,     2,     2,     2,     2,     2,     2,
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
      15,    16,    17,    18,    23
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,   131,   131,   132,   133,   134,   137,   138,   139,   140,
     141,   142,   145,   146,   149,   152,   153,   156,   157,   160,
     161,   162,   163,   166,   167,   168,   169,   172,   173,   174,
     175,   176,   177,   178,   179,   180,   181,   182,   183,   184,
     185,   186,   187,   188,   191,   194,   197,   198,   199,   200,
     201,   202,   203,   204,   205,   209,   210,   211,   212,   213,
     214
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "FCML_TK_UNEXPECTED", "FCML_TK_REG_GPR",
  "FCML_TK_REG_SIMD", "FCML_TK_REG_FPU", "FCML_TK_REG_SEG",
  "FCML_TK_REG_CR", "FCML_TK_REG_DR", "FCML_TK_REG_RIP", "FCML_TK_INTEGER",
  "FCML_TK_FLOAT", "FCML_TK_SIZE_OPERATOR", "FCML_TK_SYMBOL",
  "FCML_TK_HINTS", "FCML_TK_EAO_HINTS", "FCML_TK_SIB_HINT",
  "FCML_TK_PREFIX", "'-'", "'+'", "'*'", "'/'", "FCML_OP_UMINUS", "':'",
  "','", "'['", "']'", "'('", "')'", "$accept", "start", "instruction",
  "inst_prefixes", "mnemonic", "hint_list", "operand_list", "operand",
  "effective_address", "effective_address_components", "segment_selector",
  "far_pointer", "exp", "reg", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,    45,
      43,    42,    47,   274,    58,    44,    91,    93,    40,    41
};
# endif

#define YYPACT_NINF -24

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-24)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
       6,   -14,   -24,    42,   -24,    23,     0,    35,   -24,   -24,
     -24,     0,   -24,   -24,   -24,    -1,   -24,   -24,   -24,   -24,
      10,   -24,   -24,    36,    70,    36,    88,    27,   -24,   -24,
      30,   -24,    89,   -24,   -24,    88,    27,   -24,    -1,    70,
      37,   -24,   -24,    45,    36,   138,    41,   114,    51,   109,
     -24,    27,   113,    70,    36,    36,    36,    36,    36,    27,
      56,    70,    36,   114,   114,    71,   -24,    36,   138,   -24,
     -24,    58,    83,    83,   -24,   -24,   114,   -24,    61,   114,
      36,    36,   114,   114,    40,   -24,   -24,   114,   114,    36,
      36,    95,   114,   114,   134,    36,    36,   114,   114
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,    14,    12,     0,     3,     0,     6,     4,     1,    14,
      13,     9,    55,    56,    57,    58,    59,    60,    46,    47,
       0,    52,    15,     0,     0,     0,     0,     7,    17,    21,
       0,    20,    19,    22,     5,     0,    10,    44,     0,     0,
       0,    53,    58,    29,     0,     0,     0,    41,    27,     0,
      16,     8,     0,     0,     0,     0,     0,     0,     0,    11,
       0,     0,     0,    42,    43,    28,    23,     0,     0,    54,
      18,     0,    48,    49,    51,    50,    45,    24,     0,    37,
       0,     0,    39,    36,    30,    25,    26,    40,    38,     0,
       0,     0,    35,    34,    31,     0,     0,    33,    32
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -24,   -24,   105,   -24,   110,   112,    -8,    85,   -24,   -10,
     120,   -24,   -23,     1
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     3,     4,     5,     6,    26,    27,    28,    29,    46,
      30,    31,    32,    33
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      41,    47,    49,    36,    12,    13,    14,    15,    16,    17,
       7,    18,    19,    20,    21,    22,    47,    38,    51,    23,
       1,    63,    64,    37,     2,    48,    24,    59,    25,    60,
      47,    72,    73,    74,    75,    76,    39,     9,    47,    79,
      48,    10,     8,    71,    82,    83,    65,    18,    19,     9,
      21,    78,    52,     2,    48,    23,    53,    87,    88,    89,
      90,    91,    48,    61,    25,    62,    92,    93,    66,    84,
      67,    68,    97,    98,    12,    13,    14,    42,    16,    17,
      43,    18,    19,    77,    21,    85,    44,    45,    86,    23,
      80,    81,    12,    13,    14,    15,    16,    17,    25,    18,
      19,    20,    21,    50,    56,    57,    94,    23,    54,    55,
      56,    57,    34,    58,    24,    11,    25,    12,    13,    14,
      15,    16,    17,    35,    18,    19,    20,    21,    54,    55,
      56,    57,    23,    54,    55,    56,    57,    70,    69,    24,
      40,    25,    12,    13,    14,    42,    16,    17,     0,    18,
      19,     0,    21,    95,    96,     0,     0,    23,     0,     0,
       0,     0,     0,     0,     0,     0,    25
};

static const yytype_int8 yycheck[] =
{
      23,    24,    25,    11,     4,     5,     6,     7,     8,     9,
      24,    11,    12,    13,    14,    15,    39,     7,    26,    19,
      14,    44,    45,    24,    18,    24,    26,    35,    28,    39,
      53,    54,    55,    56,    57,    58,    26,    14,    61,    62,
      39,    18,     0,    53,    67,    68,    45,    11,    12,    14,
      14,    61,    25,    18,    53,    19,    26,    80,    81,    19,
      20,    21,    61,    26,    28,    20,    89,    90,    27,    68,
      19,    20,    95,    96,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    27,    14,    27,    16,    17,    27,    19,
      19,    20,     4,     5,     6,     7,     8,     9,    28,    11,
      12,    13,    14,    15,    21,    22,    11,    19,    19,    20,
      21,    22,     7,    24,    26,     5,    28,     4,     5,     6,
       7,     8,     9,    11,    11,    12,    13,    14,    19,    20,
      21,    22,    19,    19,    20,    21,    22,    52,    29,    26,
      20,    28,     4,     5,     6,     7,     8,     9,    -1,    11,
      12,    -1,    14,    19,    20,    -1,    -1,    19,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    28
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    14,    18,    31,    32,    33,    34,    24,     0,    14,
      18,    34,     4,     5,     6,     7,     8,     9,    11,    12,
      13,    14,    15,    19,    26,    28,    35,    36,    37,    38,
      40,    41,    42,    43,    32,    35,    36,    24,     7,    26,
      40,    42,     7,    10,    16,    17,    39,    42,    43,    42,
      15,    36,    25,    26,    19,    20,    21,    22,    24,    36,
      39,    26,    20,    42,    42,    43,    27,    19,    20,    29,
      37,    39,    42,    42,    42,    42,    42,    27,    39,    42,
      19,    20,    42,    42,    43,    27,    27,    42,    42,    19,
      20,    21,    42,    42,    11,    19,    20,    42,    42
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    30,    31,    31,    31,    31,    32,    32,    32,    32,
      32,    32,    33,    33,    34,    35,    35,    36,    36,    37,
      37,    37,    37,    38,    38,    38,    38,    39,    39,    39,
      39,    39,    39,    39,    39,    39,    39,    39,    39,    39,
      39,    39,    39,    39,    40,    41,    42,    42,    42,    42,
      42,    42,    42,    42,    42,    43,    43,    43,    43,    43,
      43
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     1,     2,     3,     1,     2,     3,     2,
       3,     4,     1,     2,     1,     1,     2,     1,     3,     1,
       1,     1,     1,     3,     4,     4,     5,     1,     2,     1,
       3,     5,     7,     7,     5,     5,     3,     3,     4,     3,
       4,     1,     2,     2,     2,     3,     1,     1,     3,     3,
       3,     3,     1,     2,     3,     1,     1,     1,     1,     1,
       1
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
      yyerror (pd, YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



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

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, pd); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, struct fcml_st_parser_data *pd)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
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
#line 102 "fcml_intel_parser_def.y" /* yacc.c:684  */
      { YYFPRINTF(yyoutput, "Type: %s Size: %d Reg: %d x64_exp: %d", fcml_fn_pu_reg_type_to_string( ((*yyvaluep).reg_value).type ), ((*yyvaluep).reg_value).size, ((*yyvaluep).reg_value).reg, ((*yyvaluep).reg_value).x64_exp); }
#line 769 "fcml_intel_parser_def.c" /* yacc.c:684  */
        break;

    case 5: /* FCML_TK_REG_SIMD  */
#line 102 "fcml_intel_parser_def.y" /* yacc.c:684  */
      { YYFPRINTF(yyoutput, "Type: %s Size: %d Reg: %d x64_exp: %d", fcml_fn_pu_reg_type_to_string( ((*yyvaluep).reg_value).type ), ((*yyvaluep).reg_value).size, ((*yyvaluep).reg_value).reg, ((*yyvaluep).reg_value).x64_exp); }
#line 775 "fcml_intel_parser_def.c" /* yacc.c:684  */
        break;

    case 6: /* FCML_TK_REG_FPU  */
#line 102 "fcml_intel_parser_def.y" /* yacc.c:684  */
      { YYFPRINTF(yyoutput, "Type: %s Size: %d Reg: %d x64_exp: %d", fcml_fn_pu_reg_type_to_string( ((*yyvaluep).reg_value).type ), ((*yyvaluep).reg_value).size, ((*yyvaluep).reg_value).reg, ((*yyvaluep).reg_value).x64_exp); }
#line 781 "fcml_intel_parser_def.c" /* yacc.c:684  */
        break;

    case 7: /* FCML_TK_REG_SEG  */
#line 102 "fcml_intel_parser_def.y" /* yacc.c:684  */
      { YYFPRINTF(yyoutput, "Type: %s Size: %d Reg: %d x64_exp: %d", fcml_fn_pu_reg_type_to_string( ((*yyvaluep).reg_value).type ), ((*yyvaluep).reg_value).size, ((*yyvaluep).reg_value).reg, ((*yyvaluep).reg_value).x64_exp); }
#line 787 "fcml_intel_parser_def.c" /* yacc.c:684  */
        break;

    case 8: /* FCML_TK_REG_CR  */
#line 102 "fcml_intel_parser_def.y" /* yacc.c:684  */
      { YYFPRINTF(yyoutput, "Type: %s Size: %d Reg: %d x64_exp: %d", fcml_fn_pu_reg_type_to_string( ((*yyvaluep).reg_value).type ), ((*yyvaluep).reg_value).size, ((*yyvaluep).reg_value).reg, ((*yyvaluep).reg_value).x64_exp); }
#line 793 "fcml_intel_parser_def.c" /* yacc.c:684  */
        break;

    case 9: /* FCML_TK_REG_DR  */
#line 102 "fcml_intel_parser_def.y" /* yacc.c:684  */
      { YYFPRINTF(yyoutput, "Type: %s Size: %d Reg: %d x64_exp: %d", fcml_fn_pu_reg_type_to_string( ((*yyvaluep).reg_value).type ), ((*yyvaluep).reg_value).size, ((*yyvaluep).reg_value).reg, ((*yyvaluep).reg_value).x64_exp); }
#line 799 "fcml_intel_parser_def.c" /* yacc.c:684  */
        break;

    case 10: /* FCML_TK_REG_RIP  */
#line 102 "fcml_intel_parser_def.y" /* yacc.c:684  */
      { YYFPRINTF(yyoutput, "Type: %s Size: %d Reg: %d x64_exp: %d", fcml_fn_pu_reg_type_to_string( ((*yyvaluep).reg_value).type ), ((*yyvaluep).reg_value).size, ((*yyvaluep).reg_value).reg, ((*yyvaluep).reg_value).x64_exp); }
#line 805 "fcml_intel_parser_def.c" /* yacc.c:684  */
        break;

    case 11: /* FCML_TK_INTEGER  */
#line 99 "fcml_intel_parser_def.y" /* yacc.c:684  */
      { YYFPRINTF(yyoutput, "Integer: %d Overflow: %d", ((*yyvaluep).integer_value).value, ((*yyvaluep).integer_value).overflow); }
#line 811 "fcml_intel_parser_def.c" /* yacc.c:684  */
        break;

    case 12: /* FCML_TK_FLOAT  */
#line 100 "fcml_intel_parser_def.y" /* yacc.c:684  */
      { YYFPRINTF(yyoutput, "Float: %f Overflow: %d", ((*yyvaluep).float_value).value, ((*yyvaluep).float_value).overflow); }
#line 817 "fcml_intel_parser_def.c" /* yacc.c:684  */
        break;

    case 32: /* instruction  */
#line 101 "fcml_intel_parser_def.y" /* yacc.c:684  */
      { YYFPRINTF(yyoutput, "AST-Type: %d", ((*yyvaluep).ast)->type); }
#line 823 "fcml_intel_parser_def.c" /* yacc.c:684  */
        break;

    case 36: /* operand_list  */
#line 101 "fcml_intel_parser_def.y" /* yacc.c:684  */
      { YYFPRINTF(yyoutput, "AST-Type: %d", ((*yyvaluep).ast)->type); }
#line 829 "fcml_intel_parser_def.c" /* yacc.c:684  */
        break;

    case 37: /* operand  */
#line 101 "fcml_intel_parser_def.y" /* yacc.c:684  */
      { YYFPRINTF(yyoutput, "AST-Type: %d", ((*yyvaluep).ast)->type); }
#line 835 "fcml_intel_parser_def.c" /* yacc.c:684  */
        break;

    case 38: /* effective_address  */
#line 101 "fcml_intel_parser_def.y" /* yacc.c:684  */
      { YYFPRINTF(yyoutput, "AST-Type: %d", ((*yyvaluep).ast)->type); }
#line 841 "fcml_intel_parser_def.c" /* yacc.c:684  */
        break;

    case 39: /* effective_address_components  */
#line 101 "fcml_intel_parser_def.y" /* yacc.c:684  */
      { YYFPRINTF(yyoutput, "AST-Type: %d", ((*yyvaluep).ast)->type); }
#line 847 "fcml_intel_parser_def.c" /* yacc.c:684  */
        break;

    case 40: /* segment_selector  */
#line 102 "fcml_intel_parser_def.y" /* yacc.c:684  */
      { YYFPRINTF(yyoutput, "Type: %s Size: %d Reg: %d x64_exp: %d", fcml_fn_pu_reg_type_to_string( ((*yyvaluep).reg_value).type ), ((*yyvaluep).reg_value).size, ((*yyvaluep).reg_value).reg, ((*yyvaluep).reg_value).x64_exp); }
#line 853 "fcml_intel_parser_def.c" /* yacc.c:684  */
        break;

    case 41: /* far_pointer  */
#line 101 "fcml_intel_parser_def.y" /* yacc.c:684  */
      { YYFPRINTF(yyoutput, "AST-Type: %d", ((*yyvaluep).ast)->type); }
#line 859 "fcml_intel_parser_def.c" /* yacc.c:684  */
        break;

    case 42: /* exp  */
#line 101 "fcml_intel_parser_def.y" /* yacc.c:684  */
      { YYFPRINTF(yyoutput, "AST-Type: %d", ((*yyvaluep).ast)->type); }
#line 865 "fcml_intel_parser_def.c" /* yacc.c:684  */
        break;

    case 43: /* reg  */
#line 102 "fcml_intel_parser_def.y" /* yacc.c:684  */
      { YYFPRINTF(yyoutput, "Type: %s Size: %d Reg: %d x64_exp: %d", fcml_fn_pu_reg_type_to_string( ((*yyvaluep).reg_value).type ), ((*yyvaluep).reg_value).size, ((*yyvaluep).reg_value).reg, ((*yyvaluep).reg_value).x64_exp); }
#line 871 "fcml_intel_parser_def.c" /* yacc.c:684  */
        break;


      default:
        break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, struct fcml_st_parser_data *pd)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep, pd);
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule, struct fcml_st_parser_data *pd)
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
                                              , pd);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule, pd); \
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
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, struct fcml_st_parser_data *pd)
{
  YYUSE (yyvaluep);
  YYUSE (pd);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  switch (yytype)
    {
          case 32: /* instruction  */
#line 96 "fcml_intel_parser_def.y" /* yacc.c:1257  */
      { fcml_fn_ast_free_node(((*yyvaluep).ast)); }
#line 1218 "fcml_intel_parser_def.c" /* yacc.c:1257  */
        break;

    case 36: /* operand_list  */
#line 96 "fcml_intel_parser_def.y" /* yacc.c:1257  */
      { fcml_fn_ast_free_node(((*yyvaluep).ast)); }
#line 1224 "fcml_intel_parser_def.c" /* yacc.c:1257  */
        break;

    case 37: /* operand  */
#line 96 "fcml_intel_parser_def.y" /* yacc.c:1257  */
      { fcml_fn_ast_free_node(((*yyvaluep).ast)); }
#line 1230 "fcml_intel_parser_def.c" /* yacc.c:1257  */
        break;

    case 38: /* effective_address  */
#line 96 "fcml_intel_parser_def.y" /* yacc.c:1257  */
      { fcml_fn_ast_free_node(((*yyvaluep).ast)); }
#line 1236 "fcml_intel_parser_def.c" /* yacc.c:1257  */
        break;

    case 39: /* effective_address_components  */
#line 96 "fcml_intel_parser_def.y" /* yacc.c:1257  */
      { fcml_fn_ast_free_node(((*yyvaluep).ast)); }
#line 1242 "fcml_intel_parser_def.c" /* yacc.c:1257  */
        break;

    case 41: /* far_pointer  */
#line 96 "fcml_intel_parser_def.y" /* yacc.c:1257  */
      { fcml_fn_ast_free_node(((*yyvaluep).ast)); }
#line 1248 "fcml_intel_parser_def.c" /* yacc.c:1257  */
        break;

    case 42: /* exp  */
#line 96 "fcml_intel_parser_def.y" /* yacc.c:1257  */
      { fcml_fn_ast_free_node(((*yyvaluep).ast)); }
#line 1254 "fcml_intel_parser_def.c" /* yacc.c:1257  */
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

    /* Number of syntax errors so far.  */
    int yynerrs;

    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

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

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

/* User initialization code.  */
#line 124 "fcml_intel_parser_def.y" /* yacc.c:1429  */
{ 
    /* Uncomment it in order to enable debugging */
    /* yydebug = 1; */
}

#line 1349 "fcml_intel_parser_def.c" /* yacc.c:1429  */
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

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

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
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

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
      yychar = yylex (&yylval, yyscanner);
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


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 3:
#line 132 "fcml_intel_parser_def.y" /* yacc.c:1646  */
    { pd->tree = (yyvsp[0].ast); pd->symbol = NULL; }
#line 1531 "fcml_intel_parser_def.c" /* yacc.c:1646  */
    break;

  case 4:
#line 133 "fcml_intel_parser_def.y" /* yacc.c:1646  */
    { pd->tree = NULL; pd->symbol = fcml_fn_ast_alloc_node_define_symbol( pd->ip, (yyvsp[-1].symbol).text, (yyvsp[-1].symbol).length ); HANDLE_ERRORS( pd->symbol ); }
#line 1537 "fcml_intel_parser_def.c" /* yacc.c:1646  */
    break;

  case 5:
#line 134 "fcml_intel_parser_def.y" /* yacc.c:1646  */
    { pd->tree = (yyvsp[0].ast); pd->symbol = fcml_fn_ast_alloc_node_define_symbol( pd->ip, (yyvsp[-2].symbol).text, (yyvsp[-2].symbol).length ); HANDLE_ERRORS( pd->symbol ); }
#line 1543 "fcml_intel_parser_def.c" /* yacc.c:1646  */
    break;

  case 6:
#line 137 "fcml_intel_parser_def.y" /* yacc.c:1646  */
    { (yyval.ast) = fcml_fn_ast_alloc_node_instruction( 0, (yyvsp[0].symbol).text, (yyvsp[0].symbol).length, 0, NULL ); HANDLE_ERRORS((yyval.ast)); }
#line 1549 "fcml_intel_parser_def.c" /* yacc.c:1646  */
    break;

  case 7:
#line 138 "fcml_intel_parser_def.y" /* yacc.c:1646  */
    { (yyval.ast) = fcml_fn_ast_alloc_node_instruction( 0, (yyvsp[-1].symbol).text, (yyvsp[-1].symbol).length, 0, (yyvsp[0].ast) ); HANDLE_ERRORS((yyval.ast)); }
#line 1555 "fcml_intel_parser_def.c" /* yacc.c:1646  */
    break;

  case 8:
#line 139 "fcml_intel_parser_def.y" /* yacc.c:1646  */
    { (yyval.ast) = fcml_fn_ast_alloc_node_instruction( 0, (yyvsp[-2].symbol).text, (yyvsp[-2].symbol).length, (yyvsp[-1].hints), (yyvsp[0].ast) ); HANDLE_ERRORS((yyval.ast)); }
#line 1561 "fcml_intel_parser_def.c" /* yacc.c:1646  */
    break;

  case 9:
#line 140 "fcml_intel_parser_def.y" /* yacc.c:1646  */
    { (yyval.ast) = fcml_fn_ast_alloc_node_instruction( (yyvsp[-1].prefixes), (yyvsp[0].symbol).text, (yyvsp[0].symbol).length, 0, NULL ); HANDLE_ERRORS((yyval.ast)); }
#line 1567 "fcml_intel_parser_def.c" /* yacc.c:1646  */
    break;

  case 10:
#line 141 "fcml_intel_parser_def.y" /* yacc.c:1646  */
    { (yyval.ast) = fcml_fn_ast_alloc_node_instruction( (yyvsp[-2].prefixes), (yyvsp[-1].symbol).text, (yyvsp[-1].symbol).length, 0, (yyvsp[0].ast) ); HANDLE_ERRORS((yyval.ast)); }
#line 1573 "fcml_intel_parser_def.c" /* yacc.c:1646  */
    break;

  case 11:
#line 142 "fcml_intel_parser_def.y" /* yacc.c:1646  */
    { (yyval.ast) = fcml_fn_ast_alloc_node_instruction( (yyvsp[-3].prefixes), (yyvsp[-2].symbol).text, (yyvsp[-2].symbol).length, (yyvsp[-1].hints), (yyvsp[0].ast) ); HANDLE_ERRORS((yyval.ast)); }
#line 1579 "fcml_intel_parser_def.c" /* yacc.c:1646  */
    break;

  case 13:
#line 146 "fcml_intel_parser_def.y" /* yacc.c:1646  */
    { if( (yyvsp[-1].prefixes) & (yyvsp[0].prefixes) )  { ADD_ERROR_MSG( "Doubled prefixes." ); YYERROR; } else { (yyval.prefixes) = (yyvsp[-1].prefixes) | (yyvsp[0].prefixes); } }
#line 1585 "fcml_intel_parser_def.c" /* yacc.c:1646  */
    break;

  case 16:
#line 153 "fcml_intel_parser_def.y" /* yacc.c:1646  */
    { (yyval.hints) = (yyvsp[-1].hints) | (yyvsp[0].hints); }
#line 1591 "fcml_intel_parser_def.c" /* yacc.c:1646  */
    break;

  case 17:
#line 156 "fcml_intel_parser_def.y" /* yacc.c:1646  */
    { (yyval.ast) = fcml_fn_ast_alloc_node_operand_list( (yyvsp[0].ast), NULL ); HANDLE_ERRORS((yyval.ast)); }
#line 1597 "fcml_intel_parser_def.c" /* yacc.c:1646  */
    break;

  case 18:
#line 157 "fcml_intel_parser_def.y" /* yacc.c:1646  */
    { (yyval.ast) = fcml_fn_ast_alloc_node_operand_list( (yyvsp[-2].ast), (yyvsp[0].ast) ); HANDLE_ERRORS((yyval.ast)); }
#line 1603 "fcml_intel_parser_def.c" /* yacc.c:1646  */
    break;

  case 22:
#line 163 "fcml_intel_parser_def.y" /* yacc.c:1646  */
    {  (yyval.ast) = fcml_fn_ast_alloc_node_register( &(yyvsp[0].reg_value) ); HANDLE_ERRORS((yyval.ast)); }
#line 1609 "fcml_intel_parser_def.c" /* yacc.c:1646  */
    break;

  case 23:
#line 166 "fcml_intel_parser_def.y" /* yacc.c:1646  */
    { (yyval.ast) = (yyvsp[-1].ast); }
#line 1615 "fcml_intel_parser_def.c" /* yacc.c:1646  */
    break;

  case 24:
#line 167 "fcml_intel_parser_def.y" /* yacc.c:1646  */
    { (yyval.ast) = fcml_fn_ast_set_effective_address_details( NULL, &(yyvsp[-3].size_operator), (yyvsp[-1].ast) ); }
#line 1621 "fcml_intel_parser_def.c" /* yacc.c:1646  */
    break;

  case 25:
#line 168 "fcml_intel_parser_def.y" /* yacc.c:1646  */
    { (yyval.ast) = fcml_fn_ast_set_effective_address_details( &(yyvsp[-3].reg_value), FCML_OS_UNDEFINED, (yyvsp[-1].ast) ); }
#line 1627 "fcml_intel_parser_def.c" /* yacc.c:1646  */
    break;

  case 26:
#line 169 "fcml_intel_parser_def.y" /* yacc.c:1646  */
    { (yyval.ast) = fcml_fn_ast_set_effective_address_details( &(yyvsp[-3].reg_value), &(yyvsp[-4].size_operator), (yyvsp[-1].ast) ); }
#line 1633 "fcml_intel_parser_def.c" /* yacc.c:1646  */
    break;

  case 27:
#line 172 "fcml_intel_parser_def.y" /* yacc.c:1646  */
    { (yyval.ast) = fcml_fn_ast_alloc_node_effective_address( &(yyvsp[0].reg_value), NULL, NULL, NULL, FCML_FALSE, 0 ); }
#line 1639 "fcml_intel_parser_def.c" /* yacc.c:1646  */
    break;

  case 28:
#line 173 "fcml_intel_parser_def.y" /* yacc.c:1646  */
    { (yyval.ast) = fcml_fn_ast_alloc_node_effective_address( &(yyvsp[0].reg_value), NULL, NULL, NULL, FCML_FALSE, (yyvsp[-1].hints) ); }
#line 1645 "fcml_intel_parser_def.c" /* yacc.c:1646  */
    break;

  case 29:
#line 174 "fcml_intel_parser_def.y" /* yacc.c:1646  */
    { (yyval.ast) = fcml_fn_ast_alloc_node_effective_address( &(yyvsp[0].reg_value), NULL, NULL, NULL, FCML_FALSE, 0 ); }
#line 1651 "fcml_intel_parser_def.c" /* yacc.c:1646  */
    break;

  case 30:
#line 175 "fcml_intel_parser_def.y" /* yacc.c:1646  */
    { (yyval.ast) = fcml_fn_ast_alloc_node_effective_address( &(yyvsp[-2].reg_value), &(yyvsp[0].reg_value), NULL, NULL, FCML_FALSE, 0 ); }
#line 1657 "fcml_intel_parser_def.c" /* yacc.c:1646  */
    break;

  case 31:
#line 176 "fcml_intel_parser_def.y" /* yacc.c:1646  */
    { (yyval.ast) = fcml_fn_ast_alloc_node_effective_address( &(yyvsp[-4].reg_value), &(yyvsp[-2].reg_value), &(yyvsp[0].integer_value), NULL, FCML_FALSE, 0 ); }
#line 1663 "fcml_intel_parser_def.c" /* yacc.c:1646  */
    break;

  case 32:
#line 177 "fcml_intel_parser_def.y" /* yacc.c:1646  */
    { (yyval.ast) = fcml_fn_ast_alloc_node_effective_address( &(yyvsp[-6].reg_value), &(yyvsp[-4].reg_value), &(yyvsp[-2].integer_value), (yyvsp[0].ast), FCML_FALSE, 0 ); }
#line 1669 "fcml_intel_parser_def.c" /* yacc.c:1646  */
    break;

  case 33:
#line 178 "fcml_intel_parser_def.y" /* yacc.c:1646  */
    { (yyval.ast) = fcml_fn_ast_alloc_node_effective_address( &(yyvsp[-6].reg_value), &(yyvsp[-4].reg_value), &(yyvsp[-2].integer_value), (yyvsp[0].ast), FCML_TRUE, 0 ); }
#line 1675 "fcml_intel_parser_def.c" /* yacc.c:1646  */
    break;

  case 34:
#line 179 "fcml_intel_parser_def.y" /* yacc.c:1646  */
    { (yyval.ast) = fcml_fn_ast_alloc_node_effective_address( &(yyvsp[-4].reg_value), &(yyvsp[-2].reg_value), NULL, (yyvsp[0].ast), FCML_FALSE, 0 ); }
#line 1681 "fcml_intel_parser_def.c" /* yacc.c:1646  */
    break;

  case 35:
#line 180 "fcml_intel_parser_def.y" /* yacc.c:1646  */
    { (yyval.ast) = fcml_fn_ast_alloc_node_effective_address( &(yyvsp[-4].reg_value), &(yyvsp[-2].reg_value), NULL, (yyvsp[0].ast), FCML_TRUE, 0 ); }
#line 1687 "fcml_intel_parser_def.c" /* yacc.c:1646  */
    break;

  case 36:
#line 181 "fcml_intel_parser_def.y" /* yacc.c:1646  */
    { (yyval.ast) = fcml_fn_ast_alloc_node_effective_address( &(yyvsp[-2].reg_value), NULL, NULL, (yyvsp[0].ast), FCML_FALSE, 0 ); }
#line 1693 "fcml_intel_parser_def.c" /* yacc.c:1646  */
    break;

  case 37:
#line 182 "fcml_intel_parser_def.y" /* yacc.c:1646  */
    { (yyval.ast) = fcml_fn_ast_alloc_node_effective_address( &(yyvsp[-2].reg_value), NULL, NULL, (yyvsp[0].ast), FCML_FALSE, 0 ); }
#line 1699 "fcml_intel_parser_def.c" /* yacc.c:1646  */
    break;

  case 38:
#line 183 "fcml_intel_parser_def.y" /* yacc.c:1646  */
    { (yyval.ast) = fcml_fn_ast_alloc_node_effective_address( &(yyvsp[-2].reg_value), NULL, NULL, (yyvsp[0].ast), FCML_FALSE, (yyvsp[-3].hints) ); }
#line 1705 "fcml_intel_parser_def.c" /* yacc.c:1646  */
    break;

  case 39:
#line 184 "fcml_intel_parser_def.y" /* yacc.c:1646  */
    { (yyval.ast) = fcml_fn_ast_alloc_node_effective_address( &(yyvsp[-2].reg_value), NULL, NULL, (yyvsp[0].ast), FCML_TRUE, 0 ); }
#line 1711 "fcml_intel_parser_def.c" /* yacc.c:1646  */
    break;

  case 40:
#line 185 "fcml_intel_parser_def.y" /* yacc.c:1646  */
    { (yyval.ast) = fcml_fn_ast_alloc_node_effective_address( &(yyvsp[-2].reg_value), NULL, NULL, (yyvsp[0].ast), FCML_TRUE, (yyvsp[-3].hints) ); }
#line 1717 "fcml_intel_parser_def.c" /* yacc.c:1646  */
    break;

  case 41:
#line 186 "fcml_intel_parser_def.y" /* yacc.c:1646  */
    { (yyval.ast) = fcml_fn_ast_alloc_node_effective_address( NULL, NULL, NULL, (yyvsp[0].ast), FCML_FALSE, 0); }
#line 1723 "fcml_intel_parser_def.c" /* yacc.c:1646  */
    break;

  case 42:
#line 187 "fcml_intel_parser_def.y" /* yacc.c:1646  */
    { (yyval.ast) = fcml_fn_ast_alloc_node_effective_address( NULL, NULL, NULL, (yyvsp[0].ast), FCML_FALSE, (yyvsp[-1].hints)); }
#line 1729 "fcml_intel_parser_def.c" /* yacc.c:1646  */
    break;

  case 43:
#line 188 "fcml_intel_parser_def.y" /* yacc.c:1646  */
    { (yyval.ast) = fcml_fn_ast_alloc_node_effective_address( NULL, NULL, NULL, (yyvsp[0].ast), FCML_FALSE, (yyvsp[-1].hints)); }
#line 1735 "fcml_intel_parser_def.c" /* yacc.c:1646  */
    break;

  case 44:
#line 191 "fcml_intel_parser_def.y" /* yacc.c:1646  */
    { (yyval.reg_value) = (yyvsp[-1].reg_value); }
#line 1741 "fcml_intel_parser_def.c" /* yacc.c:1646  */
    break;

  case 45:
#line 194 "fcml_intel_parser_def.y" /* yacc.c:1646  */
    { (yyval.ast) = fcml_fn_ast_alloc_node_far_pointer( (yyvsp[-2].ast), (yyvsp[0].ast) ); HANDLE_ERRORS((yyval.ast)); }
#line 1747 "fcml_intel_parser_def.c" /* yacc.c:1646  */
    break;

  case 46:
#line 197 "fcml_intel_parser_def.y" /* yacc.c:1646  */
    { (yyval.ast) = fcml_fn_ast_alloc_node_integer( &(yyvsp[0].integer_value) ); HANDLE_ERRORS((yyval.ast)); }
#line 1753 "fcml_intel_parser_def.c" /* yacc.c:1646  */
    break;

  case 47:
#line 198 "fcml_intel_parser_def.y" /* yacc.c:1646  */
    { (yyval.ast) = fcml_fn_ast_alloc_node_float( &(yyvsp[0].float_value) ); HANDLE_ERRORS((yyval.ast)); }
#line 1759 "fcml_intel_parser_def.c" /* yacc.c:1646  */
    break;

  case 48:
#line 199 "fcml_intel_parser_def.y" /* yacc.c:1646  */
    { (yyval.ast) = fcml_fn_ast_alloc_node_exp( FCML_EN_EXN_SUB, (yyvsp[-2].ast), (yyvsp[0].ast) ); HANDLE_ERRORS((yyval.ast)); }
#line 1765 "fcml_intel_parser_def.c" /* yacc.c:1646  */
    break;

  case 49:
#line 200 "fcml_intel_parser_def.y" /* yacc.c:1646  */
    { (yyval.ast) = fcml_fn_ast_alloc_node_exp( FCML_EN_EXN_ADD, (yyvsp[-2].ast), (yyvsp[0].ast) ); HANDLE_ERRORS((yyval.ast)); }
#line 1771 "fcml_intel_parser_def.c" /* yacc.c:1646  */
    break;

  case 50:
#line 201 "fcml_intel_parser_def.y" /* yacc.c:1646  */
    { (yyval.ast) = fcml_fn_ast_alloc_node_exp( FCML_EN_EXN_DIV, (yyvsp[-2].ast), (yyvsp[0].ast) ); HANDLE_ERRORS((yyval.ast)); }
#line 1777 "fcml_intel_parser_def.c" /* yacc.c:1646  */
    break;

  case 51:
#line 202 "fcml_intel_parser_def.y" /* yacc.c:1646  */
    { (yyval.ast) = fcml_fn_ast_alloc_node_exp( FCML_EN_EXN_MUL, (yyvsp[-2].ast), (yyvsp[0].ast) ); HANDLE_ERRORS((yyval.ast)); }
#line 1783 "fcml_intel_parser_def.c" /* yacc.c:1646  */
    break;

  case 52:
#line 203 "fcml_intel_parser_def.y" /* yacc.c:1646  */
    { (yyval.ast) = fcml_fn_ast_alloc_node_use_symbol( (yyvsp[0].symbol).text, (yyvsp[0].symbol).length ); HANDLE_ERRORS((yyval.ast)); }
#line 1789 "fcml_intel_parser_def.c" /* yacc.c:1646  */
    break;

  case 53:
#line 204 "fcml_intel_parser_def.y" /* yacc.c:1646  */
    { (yyval.ast) = fcml_fn_ast_alloc_node_uminus( (yyvsp[0].ast) ); HANDLE_ERRORS((yyval.ast)); }
#line 1795 "fcml_intel_parser_def.c" /* yacc.c:1646  */
    break;

  case 54:
#line 205 "fcml_intel_parser_def.y" /* yacc.c:1646  */
    { (yyval.ast) = (yyvsp[-1].ast); }
#line 1801 "fcml_intel_parser_def.c" /* yacc.c:1646  */
    break;


#line 1805 "fcml_intel_parser_def.c" /* yacc.c:1646  */
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
      yyerror (pd, YY_("syntax error"));
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
        yyerror (pd, yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



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
                      yytoken, &yylval, pd);
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


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp, pd);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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
  yyerror (pd, YY_("memory exhausted"));
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
                  yytoken, &yylval, pd);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp, pd);
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
#line 217 "fcml_intel_parser_def.y" /* yacc.c:1906  */

