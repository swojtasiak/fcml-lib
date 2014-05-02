noinst_PROGRAMS = fcml_internal_check

# Include all tests.

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
	common_utils_t.h

# Include all tested units directly to the executable. 

nodist_fcml_internal_check_SOURCES = ../../src/fcml_intel_lexer.h \
	../../src/fcml_intel_lexer.c \
	../../src/fcml_gas_lexer.h \
	../../src/fcml_gas_lexer.c \
	../../src/fcml_intel_parser_def.h \
	../../src/fcml_intel_parser_def.c \
	../../src/fcml_gas_parser_def.h \
	../../src/fcml_gas_parser_def.c \
	../../src/fcml_apc_ast.c \
	../../src/fcml_apc_ast.h \
	../../src/fcml_assembler.c \
	../../src/fcml_ceh.c \
	../../src/fcml_ceh.h \
	../../src/fcml_choosers.c \
	../../src/fcml_coll.c \
	../../src/fcml_coll.h \
	../../src/fcml_common_dialect.c \
	../../src/fcml_common_dialect.h \
	../../src/fcml_common_lex.h \
	../../src/fcml_common_utils.c \
	../../src/fcml_debug.h \
	../../src/fcml_decoding_tree.c \
	../../src/fcml_decoding_tree.h \
	../../src/fcml_def.c \
	../../src/fcml_def_enc.c \
	../../src/fcml_def.h \
	../../src/fcml_dialect.c \
	../../src/fcml_dialect_int.c \
	../../src/fcml_dialect_int.h \
	../../src/fcml_disassembler.c \
	../../src/fcml_encoding.c \
	../../src/fcml_encoding.h \
	../../src/fcml_env_int.c \
	../../src/fcml_env_int.h \
	../../src/fcml_gas_dialect.c \
	../../src/fcml_gas_parser.c \
	../../src/fcml_gas_parser.h \
	../../src/fcml_gas_rend.c \
	../../src/fcml_gas_rend.h \
	../../src/fcml_hints.c \
	../../src/fcml_hints.h \
	../../src/fcml_intel_dialect.c \
	../../src/fcml_intel_parser.c \
	../../src/fcml_intel_parser.h \
	../../src/fcml_intel_rend.c \
	../../src/fcml_intel_rend.h \
	../../src/fcml_messages.c \
	../../src/fcml_messages.h \
	../../src/fcml_mnemonic_parser.c \
	../../src/fcml_mnemonic_parser.h \
	../../src/fcml_modrm_decoder.c \
	../../src/fcml_modrm_decoder.h \
	../../src/fcml_modrm_encoder.c \
	../../src/fcml_modrm_encoder.h \
	../../src/fcml_modrm.h \
	../../src/fcml_optimizers.c \
	../../src/fcml_parser.c \
	../../src/fcml_parser_data.h \
	../../src/fcml_parser_utils.c \
	../../src/fcml_parser_utils.h \
	../../src/fcml_parser_int.c \
	../../src/fcml_parser_int.h \
	../../src/fcml_renderer.c \
	../../src/fcml_rend_utils.c \
	../../src/fcml_rend_utils.h \
	../../src/fcml_stream.c \
	../../src/fcml_trace.h \
	../../src/fcml_utils.c \
	../../src/fcml_utils.h \
	../../src/fcml_stream.h \
	../../src/fcml_lag_assembler.h \
	../../src/fcml_lag_assembler.c \
	../../src/fcml_symbols.c

fcml_internal_check_CPPFLAGS = -I$(top_srcdir)/include -I$(top_srcdir)/src -I$(top_srcdir)/check/stf

fcml_internal_check_LDADD = $(top_srcdir)/check/stf/libstf.la

check_SCRIPTS = fcml_internal_check

TESTS = $(check_SCRIPTS)

# Just in case, to rebuild missing files.

fcml_intel_lexer.c fcml_intel_lexer.h:
	$(MAKE) $(AM_MAKEFLAGS) -C $(top_srcdir)/src fcml_intel_lexer.c

fcml_gas_lexer.c fcml_gas_lexer.h:
	$(MAKE) $(AM_MAKEFLAGS) -C $(top_srcdir)/src fcml_gas_lexer.c
	
fcml_intel_parser_def.h fcml_intel_parser_def.c:
	$(MAKE) $(AM_MAKEFLAGS) -C $(top_srcdir)/src fcml_intel_parser_def.y
	
fcml_gas_parser_def.h fcml_gas_parser_def.c:
	$(MAKE) $(AM_MAKEFLAGS) -C $(top_srcdir)/src fcml_gas_parser_def.y
