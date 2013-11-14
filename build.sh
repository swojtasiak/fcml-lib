#!/bin/sh
# bison -d --report=solved --graph --debug epl-parser.y
bison -d --report=solved fcml_x64intel_parser.y
flex fcml_x64intel_lexer.lex
