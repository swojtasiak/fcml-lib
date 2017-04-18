@SET_MAKE@

BUILT_SOURCES = fcml_intel_parser_def.h fcml_gas_parser_def.h fcml_intel_lexer.h fcml_gas_lexer.h

AM_YFLAGS = -d

lib_LTLIBRARIES = libfcml.la

libfcml_la_SOURCES = fcml_intel_lexer.l \
	fcml_intel_lexer.h \
	fcml_gas_lexer.l \
	fcml_gas_lexer.h \
	fcml_intel_parser_def.y \
	fcml_gas_parser_def.y \
	fcml_apc_ast.c \
	fcml_apc_ast.h \
	fcml_assembler.c \
	fcml_assembler_int.h \
	fcml_ceh.c \
	fcml_ceh.h \
	fcml_choosers.c \
	fcml_coll.c \
	fcml_coll.h \
	fcml_common_dialect.c \
	fcml_common_dialect.h \
	fcml_common_lex.h \
	fcml_common_utils.c \
	fcml_decoding_tree.c \
	fcml_decoding_tree.h \
	fcml_def.c \
	fcml_def_enc.c \
	fcml_def.h \
	fcml_dialect.c \
	fcml_dialect_int.c \
	fcml_dialect_int.h \
	fcml_disassembler.c \
	fcml_encoding.c \
	fcml_encoding.h \
	fcml_env_int.c \
	fcml_env_int.h \
	fcml_gas_dialect.c \
	fcml_gas_parser.c \
	fcml_gas_parser.h \
	fcml_gas_rend.c \
	fcml_gas_rend.h \
	fcml_hints.c \
	fcml_hints.h \
	fcml_intel_dialect.c \
	fcml_intel_parser.c \
	fcml_intel_parser.h \
	fcml_intel_rend.c \
	fcml_intel_rend.h \
	fcml_messages.c \
	fcml_messages.h \
	fcml_mnemonic_parser.c \
	fcml_mnemonic_parser.h \
	fcml_modrm_decoder.c \
	fcml_modrm_decoder.h \
	fcml_modrm_encoder.c \
	fcml_modrm_encoder.h \
	fcml_modrm.h \
	fcml_optimizers.c \
	fcml_parser.c \
	fcml_parser_int.c \
	fcml_parser_int.h \
	fcml_parser_utils.c \
	fcml_parser_utils.h \
	fcml_renderer.c \
	fcml_rend_utils.c \
	fcml_rend_utils.h \
	fcml_stream.c \
	fcml_trace.h \
	fcml_utils.c \
	fcml_utils.h \
	fcml_stream.h \
	fcml_lag_assembler.c \
	fcml_symbols.c \
	fcml_disp8_n.h \
	fcml_disp8_n.c

libfcml_la_CPPFLAGS = -I$(top_srcdir)/include
libfcml_la_LDFLAGS = -no-undefined

fcml_intel_lexer.h: fcml_intel_lexer.c
	@if test ! -f $@; then rm -f fcml_intel_lexer.c; else :; fi
	@if test ! -f $@; then $(MAKE) $(AM_MAKEFLAGS) fcml_gas_lexer.c; else :; fi

fcml_gas_lexer.h: fcml_gas_lexer.c
	@if test ! -f $@; then rm -f fcml_gas_lexer.c; else :; fi
	@if test ! -f $@; then $(MAKE) $(AM_MAKEFLAGS) fcml_gas_lexer.c; else :; fi

EXTRA_DIST = libfcml.pc.in

pkgconfigdir = $(libdir)/pkgconfig
nodist_pkgconfig_DATA = libfcml.pc

libfcml.pc: libfcml.pc.in
	@sed -e 's![@]prefix[@]!$(prefix)!g' \
		-e 's![@]exec_prefix[@]!$(exec_prefix)!g' \
		-e 's![@]includedir[@]!$(includedir)!g' \
		-e 's![@]libdir[@]!$(libdir)!g' \
		-e 's![@]PACKAGE_VERSION[@]!$(PACKAGE_VERSION)!g' \
		$(srcdir)/libfcml.pc.in > $@

CLEANFILES = *.pc
