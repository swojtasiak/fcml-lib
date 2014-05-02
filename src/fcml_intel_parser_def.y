%define api.pure
%parse-param { struct fcml_st_parser_data *pd }
%name-prefix="intel_"

%{
	#include <stdio.h>
	
	#include "fcml_parser_utils.h"
	
	/* Macro responsible for handling 'Out of memory' errors. */
    #define HANDLE_ERRORS(x) if( !x ) { yyerror(pd, "Out of memory."); YYERROR; }
    
    /* Macro responsible for adding error messages to result. */
    #define ADD_ERROR_MSG(x) { yyerror( pd, x ); }
	
%}

/* Uncomment it in order to enable debugging */
/* %debug */

/* Terminal symbols. */

/* Uexpected tokens goes here. */
%token FCML_TK_UNEXPECTED

/* Registers. */
%token <reg_value> FCML_TK_REG_GPR 
%token <reg_value> FCML_TK_REG_SIMD
%token <reg_value> FCML_TK_REG_FPU
%token <reg_value> FCML_TK_REG_SEG
%token <reg_value> FCML_TK_REG_CR
%token <reg_value> FCML_TK_REG_DR
%token <reg_value> FCML_TK_REG_RIP

/* Integer values. Encoding doesn't matters. */
%token <integer_value> FCML_TK_INTEGER

/* Single-precision floating-point in IEEE 754. */
%token <float_value> FCML_TK_FLOAT

/* Size operand (BYTE PTR etc.) */
%token <size_operator> FCML_TK_SIZE_OPERATOR;

/* Literal symbol. It's used mainly for mnemonics.*/
%token <symbol> FCML_TK_SYMBOL

/* Instruction addressing mode hints. */
%token <hints> FCML_TK_HINTS
%token <hints> FCML_TK_EAO_HINTS
%token <hints> FCML_TK_SIB_HINT

/* Prefixes */
%token <prefixes> FCML_TK_PREFIX

/*Non-terminal symbols.*/
%type <reg_value> reg
%type <reg_value> segment_selector
%type <hints> hint_list
%type <ast> operand
%type <ast> operand_list
%type <ast> instruction
%type <ast> exp
%type <ast> far_pointer
%type <ast> effective_address
%type <ast> effective_address_components
%type <symbol> mnemonic
%type <prefixes> inst_prefixes

/* Precedence levels and associativity. */
%left '-' '+'
%left '*' '/'
%left FCML_OP_UMINUS

/* Destructor for leafs of AST. */
%destructor { fcml_fn_ast_free_node($$); } <ast>

/* Printers goes here. */
%printer { YYFPRINTF(yyoutput, "Integer: %d Overflow: %d", $$.value, $$.overflow); } <integer_value>
%printer { YYFPRINTF(yyoutput, "Float: %f Overflow: %d", $$.value, $$.overflow); } <float_value>
%printer { YYFPRINTF(yyoutput, "AST-Type: %d", $$->type); } <ast>
%printer { YYFPRINTF(yyoutput, "Type: %s Size: %d Reg: %d x64_exp: %d", fcml_fn_pu_reg_type_to_string( $$.type ), $$.size, $$.reg, $$.x64_exp); } <reg_value>

%union {
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
}

%{
	#include "fcml_intel_lexer.h"
	#define YYLEX_PARAM ((yyscan_t)pd->scannerInfo)
%}

%initial-action { 
    /* Uncomment it in order to enable debugging */
	/* yydebug = 1; */
}

%%

start: 
| instruction { pd->tree = $1; pd->symbol = NULL; }
| FCML_TK_SYMBOL ':' { pd->tree = NULL; pd->symbol = fcml_fn_ast_alloc_node_define_symbol( pd->ip, $1.text, $1.length ); HANDLE_ERRORS( pd->symbol ); }
| FCML_TK_SYMBOL ':' instruction { pd->tree = $3; pd->symbol = fcml_fn_ast_alloc_node_define_symbol( pd->ip, $1.text, $1.length ); HANDLE_ERRORS( pd->symbol ); }
;

instruction: mnemonic { $$ = fcml_fn_ast_alloc_node_instruction( 0, $1.text, $1.length, 0, NULL ); HANDLE_ERRORS($$); }
| mnemonic operand_list { $$ = fcml_fn_ast_alloc_node_instruction( 0, $1.text, $1.length, 0, $2 ); HANDLE_ERRORS($$); }
| mnemonic hint_list operand_list { $$ = fcml_fn_ast_alloc_node_instruction( 0, $1.text, $1.length, $2, $3 ); HANDLE_ERRORS($$); }
| inst_prefixes mnemonic { $$ = fcml_fn_ast_alloc_node_instruction( $1, $2.text, $2.length, 0, NULL ); HANDLE_ERRORS($$); }
| inst_prefixes mnemonic operand_list { $$ = fcml_fn_ast_alloc_node_instruction( $1, $2.text, $2.length, 0, $3 ); HANDLE_ERRORS($$); }
| inst_prefixes mnemonic hint_list operand_list { $$ = fcml_fn_ast_alloc_node_instruction( $1, $2.text, $2.length, $3, $4 ); HANDLE_ERRORS($$); }
;

inst_prefixes: FCML_TK_PREFIX
| inst_prefixes FCML_TK_PREFIX { if( $1 & $2 ) { ADD_ERROR_MSG( "Doubled prefixes." ); YYERROR; } else { $$ = $1 | $2; } }
;

mnemonic: FCML_TK_SYMBOL 
;

hint_list: FCML_TK_HINTS
| hint_list FCML_TK_HINTS  { $$ = $1 | $2; }
;

operand_list: operand { $$ = fcml_fn_ast_alloc_node_operand_list( $1, NULL ); HANDLE_ERRORS($$); }
| operand_list ',' operand { $$ = fcml_fn_ast_alloc_node_operand_list( $1, $3 ); HANDLE_ERRORS($$); }
;

operand: exp
| far_pointer
| effective_address
| reg {  $$ = fcml_fn_ast_alloc_node_register( &$1 ); HANDLE_ERRORS($$); }
;

effective_address:  '[' effective_address_components ']' { $$ = $2; }
| FCML_TK_SIZE_OPERATOR '[' effective_address_components ']' { $$ = fcml_fn_ast_set_effective_address_details( NULL, &$1, $3 ); }
| segment_selector '[' effective_address_components ']' { $$ = fcml_fn_ast_set_effective_address_details( &$1, FCML_OS_UNDEFINED, $3 ); }
| FCML_TK_SIZE_OPERATOR segment_selector '[' effective_address_components ']' { $$ = fcml_fn_ast_set_effective_address_details( &$2, &$1, $4 ); }
;

effective_address_components: reg 			{ $$ = fcml_fn_ast_alloc_node_effective_address( &$1, NULL, NULL, NULL, FCML_FALSE, 0 ); }
| FCML_TK_SIB_HINT reg 						{ $$ = fcml_fn_ast_alloc_node_effective_address( &$2, NULL, NULL, NULL, FCML_FALSE, $1 ); }
| FCML_TK_REG_RIP 							{ $$ = fcml_fn_ast_alloc_node_effective_address( &$1, NULL, NULL, NULL, FCML_FALSE, 0 ); }
| reg '+' reg 								{ $$ = fcml_fn_ast_alloc_node_effective_address( &$1, &$3, NULL, NULL, FCML_FALSE, 0 ); }
| reg '+' reg '*' FCML_TK_INTEGER 			{ $$ = fcml_fn_ast_alloc_node_effective_address( &$1, &$3, &$5, NULL, FCML_FALSE, 0 ); }
| reg '+' reg '*' FCML_TK_INTEGER '+' exp	{ $$ = fcml_fn_ast_alloc_node_effective_address( &$1, &$3, &$5, $7, FCML_FALSE, 0 ); }
| reg '+' reg '*' FCML_TK_INTEGER '-' exp	{ $$ = fcml_fn_ast_alloc_node_effective_address( &$1, &$3, &$5, $7, FCML_TRUE, 0 ); }
| reg '+' reg '+' exp						{ $$ = fcml_fn_ast_alloc_node_effective_address( &$1, &$3, NULL, $5, FCML_FALSE, 0 ); }
| reg '+' reg '-' exp						{ $$ = fcml_fn_ast_alloc_node_effective_address( &$1, &$3, NULL, $5, FCML_TRUE, 0 ); }
| reg '+' exp								{ $$ = fcml_fn_ast_alloc_node_effective_address( &$1, NULL, NULL, $3, FCML_FALSE, 0 ); }
| FCML_TK_REG_RIP '+' exp					{ $$ = fcml_fn_ast_alloc_node_effective_address( &$1, NULL, NULL, $3, FCML_FALSE, 0 ); }
| FCML_TK_SIB_HINT reg '+' exp				{ $$ = fcml_fn_ast_alloc_node_effective_address( &$2, NULL, NULL, $4, FCML_FALSE, $1 ); }
| reg '-' exp								{ $$ = fcml_fn_ast_alloc_node_effective_address( &$1, NULL, NULL, $3, FCML_TRUE, 0 ); }
| FCML_TK_SIB_HINT reg '-' exp				{ $$ = fcml_fn_ast_alloc_node_effective_address( &$2, NULL, NULL, $4, FCML_TRUE, $1 ); }
| exp										{ $$ = fcml_fn_ast_alloc_node_effective_address( NULL, NULL, NULL, $1, FCML_FALSE, 0); }
| FCML_TK_EAO_HINTS exp						{ $$ = fcml_fn_ast_alloc_node_effective_address( NULL, NULL, NULL, $2, FCML_FALSE, $1); }
| FCML_TK_SIB_HINT exp						{ $$ = fcml_fn_ast_alloc_node_effective_address( NULL, NULL, NULL, $2, FCML_FALSE, $1); }
;

segment_selector: FCML_TK_REG_SEG ':' { $$ = $1; }
;

far_pointer: exp ':' exp { $$ = fcml_fn_ast_alloc_node_far_pointer( $1, $3 ); HANDLE_ERRORS($$); }
;

exp: FCML_TK_INTEGER { $$ = fcml_fn_ast_alloc_node_integer( &$1 ); HANDLE_ERRORS($$); }
| FCML_TK_FLOAT { $$ = fcml_fn_ast_alloc_node_float( &$1 ); HANDLE_ERRORS($$); }
| exp '-' exp { $$ = fcml_fn_ast_alloc_node_exp( FCML_EN_EXN_SUB, $1, $3 ); HANDLE_ERRORS($$); }
| exp '+' exp { $$ = fcml_fn_ast_alloc_node_exp( FCML_EN_EXN_ADD, $1, $3 ); HANDLE_ERRORS($$); }
| exp '/' exp { $$ = fcml_fn_ast_alloc_node_exp( FCML_EN_EXN_DIV, $1, $3 ); HANDLE_ERRORS($$); }
| exp '*' exp { $$ = fcml_fn_ast_alloc_node_exp( FCML_EN_EXN_MUL, $1, $3 ); HANDLE_ERRORS($$); }
| FCML_TK_SYMBOL { $$ = fcml_fn_ast_alloc_node_use_symbol( $1.text, $1.length ); HANDLE_ERRORS($$); }
| '-' exp %prec FCML_OP_UMINUS { $$ = fcml_fn_ast_alloc_node_uminus( $2 ); HANDLE_ERRORS($$); }
| '(' exp ')' { $$ = $2; }
;

/* Every register possible. */
reg: FCML_TK_REG_GPR
| FCML_TK_REG_SIMD
| FCML_TK_REG_FPU
| FCML_TK_REG_SEG
| FCML_TK_REG_CR
| FCML_TK_REG_DR
;

%%
