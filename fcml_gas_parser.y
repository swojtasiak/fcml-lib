%define api.pure
%parse-param { struct fcml_st_parser_data *pd }
%name-prefix="gas_"

%{
	#include <stdio.h>
	#include <inttypes.h>
	#include "fcml_parser_data.h"
	#include "fcml_apc_ast.h"
	#include "fcml_parser_utils.h"
	
	void gas_error( struct fcml_st_parser_data *pd, const char *error );
	
	/* Macro responsible for handling 'Out of memory' errors. */
	#define HANDLE_ERRORS(x) if( !x ) { \
		yyerror(pd, "Out of memory."); \
		YYERROR; \
	}
	
	/* Macro responsible for adding error messages to result. */
	#define ADD_ERROR_MSG(x) { \
		yyerror(pd, x); \
	}
	
%}

//%debug

/*Terminal symbols.*/

/* Uexpected tokeens goes here. */
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

/* Literal symbol. It's used mainly for mnemonics.*/
%token <symbol> FCML_TK_SYMBOL

/* Prefixes */
%token <prefixes> FCML_TK_PREFIX

/*Non-terminal symbols.*/
%type <reg_value> reg
%type <reg_value> segment_selector
%type <ast> operand
%type <ast> operand_list
%type <ast> instruction
%type <ast> exp
%type <ast> effective_address
%type <ast> effective_address_components_without_dis
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
%printer { YYFPRINTF(yyoutput, "Integer: %ld Overflow: %d", $$.value, $$.overflow); } <integer_value>
%printer { YYFPRINTF(yyoutput, "Float: %f Overflow: %d", $$.value, $$.overflow); } <float_value>
%printer { YYFPRINTF(yyoutput, "AST-Type: %d", $$->type); } <ast>
%printer { YYFPRINTF(yyoutput, "Type: %s Size: %d Reg: %d x64_exp: %d", fcml_fn_pu_reg_type_to_string( $$.type ), $$.size, $$.reg, $$.x64_exp); } <reg_value>

%union {
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
}

%{
	#include "fcml_gas_lexer.h"
	#define YYLEX_PARAM ((yyscan_t)pd->scannerInfo)
%}

%initial-action { 
	//gas_debug = 1;
}

%%

start: 
| instruction { pd->tree = $1; }
;

instruction: mnemonic					{ $$ = fcml_fn_ast_alloc_node_instruction( 0, $1.text, $1.length, 0, NULL ); HANDLE_ERRORS($$); }
| mnemonic operand_list					{ $$ = fcml_fn_ast_alloc_node_instruction( 0, $1.text, $1.length, 0, $2 ); HANDLE_ERRORS($$); }
| inst_prefixes mnemonic				{ $$ = fcml_fn_ast_alloc_node_instruction( $1, $2.text, $2.length, 0, NULL ); HANDLE_ERRORS($$); }
| inst_prefixes mnemonic operand_list	{ $$ = fcml_fn_ast_alloc_node_instruction( $1, $2.text, $2.length, 0, $3 ); HANDLE_ERRORS($$); }
;

inst_prefixes: FCML_TK_PREFIX
| inst_prefixes FCML_TK_PREFIX	{ if( $1 & $2 ) { ADD_ERROR_MSG( "Doubled prefixes." ); YYERROR; } else { $$ = $1 | $2; } }
;

mnemonic: FCML_TK_SYMBOL 
;

operand_list: operand 			{ $$ = fcml_fn_ast_alloc_node_operand_list( $1, NULL ); HANDLE_ERRORS($$); }
| operand_list ',' operand 		{ $$ = fcml_fn_ast_alloc_node_operand_list( $1, $3 ); HANDLE_ERRORS($$); }
;

operand: '$' exp 				{ $$ = $2; }
| effective_address
| '*' effective_address			{ $$ = fcml_fn_ast_set_effective_address_hins( $2, FCML_HINT_INDIRECT_POINTER ); }
| reg 							{ $$ = fcml_fn_ast_alloc_node_register( &$1 ); HANDLE_ERRORS($$); }
;

effective_address:  effective_address_components
| segment_selector effective_address_components 	{ $$ = fcml_fn_ast_set_effective_address_details( &$1, FCML_OS_UNDEFINED, $2 ); }
;

effective_address_components:
  effective_address_components_without_dis
| exp effective_address_components_without_dis		{ $$ = fcml_fn_ast_set_displacemnt( $1, $2 ); }
| exp 												{ $$ = fcml_fn_ast_alloc_node_effective_address( NULL, NULL, NULL, $1, FCML_FALSE, 0); }
;

effective_address_components_without_dis:
  '(' FCML_TK_REG_RIP ')' 					{ $$ = fcml_fn_ast_alloc_node_effective_address( &$2, NULL, NULL, NULL, FCML_FALSE, 0 ); }
| '(' reg ')' 								{ $$ = fcml_fn_ast_alloc_node_effective_address( &$2, NULL, NULL, NULL, FCML_FALSE, 0 ); }
| '(' reg ',' reg ')' 						{ $$ = fcml_fn_ast_alloc_node_effective_address( &$2, &$4, NULL, NULL, FCML_FALSE, 0 ); }
| '(' ',' reg ')' 							{ $$ = fcml_fn_ast_alloc_node_effective_address( NULL, &$3, NULL, NULL, FCML_FALSE, 0 ); }
| '(' reg ',' reg ',' FCML_TK_INTEGER ')'	{ $$ = fcml_fn_ast_alloc_node_effective_address( &$2, &$4, &$6, NULL, FCML_FALSE, 0 ); }
| '(' ',' reg ',' FCML_TK_INTEGER ')'		{ $$ = fcml_fn_ast_alloc_node_effective_address( NULL, &$3, &$5, NULL, FCML_FALSE, 0 ); }
;

segment_selector: FCML_TK_REG_SEG ':' { $$ = $1; }
;

exp: 
  FCML_TK_INTEGER	 			{ $$ = fcml_fn_ast_alloc_node_integer( &$1 ); HANDLE_ERRORS($$); }
| exp '-' exp 					{ $$ = fcml_fn_ast_alloc_node_exp( FCML_EN_EXN_SUB, $1, $3 ); HANDLE_ERRORS($$); }
| exp '+' exp 					{ $$ = fcml_fn_ast_alloc_node_exp( FCML_EN_EXN_ADD, $1, $3 ); HANDLE_ERRORS($$); }
| exp '/' exp					{ $$ = fcml_fn_ast_alloc_node_exp( FCML_EN_EXN_DIV, $1, $3 ); HANDLE_ERRORS($$); }
| exp '*' exp					{ $$ = fcml_fn_ast_alloc_node_exp( FCML_EN_EXN_MUL, $1, $3 ); HANDLE_ERRORS($$); }
| '-' exp %prec FCML_OP_UMINUS	{ $$ = fcml_fn_ast_alloc_node_uminus( $2 ); HANDLE_ERRORS($$); }
| '(' exp ')'					{ $$ = $2; }
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
