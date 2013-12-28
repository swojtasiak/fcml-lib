#!/bin/sh
# bison -d --report=solved --graph --debug epl-parser.y
bison -d --report=solved fcml_intel_parser.y
flex fcml_intel_lexer.lex
bison -d --report=solved fcml_gas_parser.y
flex fcml_gas_lexer.lex
