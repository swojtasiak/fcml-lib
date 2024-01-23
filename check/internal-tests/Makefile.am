#
# Builds unit tests for checking internal library code that is not
# exported. The tested source files are compiled directly into the
# test application instead of relying on the symbols exported by
# shared/static fcml-lib by default, as this technique is not portable
# (for instance Windows does not export all symbols by default).
# The build system uses "subdir-objects" to reference needed files directly
# from the main src directory where library source files are placed.
#
# Unfortunately `ylwrap` does not respect it and generates flex/yacc
# source and headers files into the current directory not into the
# directory where *.l/*.y files are located. It's why instead of
# referencing these files directly in the list of sources in
# 'fcml_internal_check_SOURCES' we have to generate these files
# by calling make for them (see yl task) and then reference the
# generated source files directly as if they were standard source
# files just like all others.
#
# This is not the best way to generate those files, as the generated
# source and header files should not ge referenced directly, so if you
# know a better way to handle it just let me know. Until then I have
# no choice but to leave it as it is.
#

AUTOMAKE_OPTIONS = subdir-objects

BUILT_SOURCES = yl

noinst_PROGRAMS = fcml_internal_check

fcml_internal_check_SOURCES = main.c \
	coll_t.c \
	coll_t.h \
	gas_parser_t.c \
	gas_parser_t.h \
	intel_parser_t.c \
	intel_parser_t.h \
	mnemonic_parser_t.c \
	mnemonic_parser_t.h \
	modrm_decoder_t.c \
	modrm_decoder_t.h \
	modrm_encoder_t.c \
	modrm_encoder_t.h \
	instruction_chooser_t.c \
	instruction_chooser_t.h \
	stream_t.c \
	stream_t.h \
	utils_t.c \
	utils_t.h \
	lag_assembler_t.c \
	lag_assembler_t.h \
	env_t.c \
	env_t.h \
	ceh_t.c \
	ceh_t.h \
	common_utils_t.c \
	common_utils_t.h \
	symbols_t.h \
	symbols_t.c \
	$(top_srcdir)/src/fcml_intel_lexer.h \
	$(top_srcdir)/src/fcml_intel_lexer.c \
	$(top_srcdir)/src/fcml_gas_lexer.h \
	$(top_srcdir)/src/fcml_gas_lexer.c \
	$(top_srcdir)/src/fcml_intel_parser_def.h \
	$(top_srcdir)/src/fcml_intel_parser_def.c \
	$(top_srcdir)/src/fcml_gas_parser_def.h \
	$(top_srcdir)/src/fcml_gas_parser_def.c \
	$(top_srcdir)/src/fcml_apc_ast.c \
	$(top_srcdir)/src/fcml_apc_ast.h \
	$(top_srcdir)/src/fcml_assembler.c \
	$(top_srcdir)/src/fcml_assembler_int.h \
	$(top_srcdir)/src/fcml_ceh.c \
	$(top_srcdir)/src/fcml_ceh.h \
	$(top_srcdir)/src/fcml_choosers.c \
	$(top_srcdir)/src/fcml_coll.c \
	$(top_srcdir)/src/fcml_coll.h \
	$(top_srcdir)/src/fcml_common_dialect.c \
	$(top_srcdir)/src/fcml_common_dialect.h \
	$(top_srcdir)/src/fcml_common_lex.h \
	$(top_srcdir)/src/fcml_common_utils.c \
	$(top_srcdir)/src/fcml_decoding_tree.c \
	$(top_srcdir)/src/fcml_decoding_tree.h \
	$(top_srcdir)/src/fcml_def.c \
	$(top_srcdir)/src/fcml_def_enc.c \
	$(top_srcdir)/src/fcml_def.h \
	$(top_srcdir)/src/fcml_dialect.c \
	$(top_srcdir)/src/fcml_dialect_int.c \
	$(top_srcdir)/src/fcml_dialect_int.h \
	$(top_srcdir)/src/fcml_disassembler.c \
	$(top_srcdir)/src/fcml_encoding.c \
	$(top_srcdir)/src/fcml_encoding.h \
	$(top_srcdir)/src/fcml_env_int.c \
	$(top_srcdir)/src/fcml_env_int.h \
	$(top_srcdir)/src/fcml_gas_dialect.c \
	$(top_srcdir)/src/fcml_gas_parser.c \
	$(top_srcdir)/src/fcml_gas_parser.h \
	$(top_srcdir)/src/fcml_gas_rend.c \
	$(top_srcdir)/src/fcml_gas_rend.h \
	$(top_srcdir)/src/fcml_hints.c \
	$(top_srcdir)/src/fcml_hints.h \
	$(top_srcdir)/src/fcml_intel_dialect.c \
	$(top_srcdir)/src/fcml_intel_parser.c \
	$(top_srcdir)/src/fcml_intel_parser.h \
	$(top_srcdir)/src/fcml_intel_rend.c \
	$(top_srcdir)/src/fcml_intel_rend.h \
	$(top_srcdir)/src/fcml_messages.c \
	$(top_srcdir)/src/fcml_messages.h \
	$(top_srcdir)/src/fcml_mnemonic_parser.c \
	$(top_srcdir)/src/fcml_mnemonic_parser.h \
	$(top_srcdir)/src/fcml_modrm_decoder.c \
	$(top_srcdir)/src/fcml_modrm_decoder.h \
	$(top_srcdir)/src/fcml_modrm_encoder.c \
	$(top_srcdir)/src/fcml_modrm_encoder.h \
	$(top_srcdir)/src/fcml_modrm.h \
	$(top_srcdir)/src/fcml_optimizers.c \
	$(top_srcdir)/src/fcml_parser.c \
	$(top_srcdir)/src/fcml_parser_int.c \
	$(top_srcdir)/src/fcml_parser_int.h \
	$(top_srcdir)/src/fcml_parser_utils.c \
	$(top_srcdir)/src/fcml_parser_utils.h \
	$(top_srcdir)/src/fcml_renderer.c \
	$(top_srcdir)/src/fcml_rend_utils.c \
	$(top_srcdir)/src/fcml_rend_utils.h \
	$(top_srcdir)/src/fcml_stream.c \
	$(top_srcdir)/src/fcml_trace.h \
	$(top_srcdir)/src/fcml_utils.c \
	$(top_srcdir)/src/fcml_utils.h \
	$(top_srcdir)/src/fcml_stream.h \
	$(top_srcdir)/src/fcml_lag_assembler.c \
	$(top_srcdir)/src/fcml_symbols.c \
	$(top_srcdir)/src/fcml_disp8_n.h \
	$(top_srcdir)/src/fcml_disp8_n.c \
	$(top_srcdir)/src/fcml_operand_decorators.h \
	$(top_srcdir)/src/fcml_operand_decorators.c

fcml_internal_check_CPPFLAGS = -I$(top_srcdir)/include -I$(top_srcdir)/src -I$(top_srcdir)/check/stf

fcml_internal_check_LDADD = $(top_srcdir)/check/stf/libstf.la 

check_SCRIPTS = fcml_internal_check

TESTS = $(check_SCRIPTS)

yl:
	$(MAKE) $(AM_MAKEFLAGS) -C $(top_srcdir)/src fcml_intel_lexer.c
	$(MAKE) $(AM_MAKEFLAGS) -C $(top_srcdir)/src fcml_gas_lexer.c
	$(MAKE) $(AM_MAKEFLAGS) -C $(top_srcdir)/src fcml_intel_parser_def.c
	$(MAKE) $(AM_MAKEFLAGS) -C $(top_srcdir)/src fcml_gas_parser_def.c
