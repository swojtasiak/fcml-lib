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
	common_utils_t.h \
	symbols_t.h \
	symbols_t.c

fcml_internal_check_CPPFLAGS = -I$(top_srcdir)/include -I$(top_srcdir)/src -I$(top_srcdir)/check/stf

fcml_internal_check_LDADD = $(top_srcdir)/check/stf/libstf.la $(top_srcdir)/src/libfcml.la

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
