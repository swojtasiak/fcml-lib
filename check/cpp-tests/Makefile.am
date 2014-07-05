noinst_PROGRAMS = fcml_cpp_check

# Include all tests.

fcml_cpp_check_SOURCES = main.cpp \
	dialect_t.cpp \
	dialect_t.hpp \
	struct_wrapper_t.cpp \
	struct_wrapper_t.hpp \
	assembler_t.cpp \
	assembler_t.hpp

fcml_cpp_check_CPPFLAGS = -Wall -Wno-write-strings -I$(top_srcdir)/include -I$(top_srcdir)/check/stf @FCML_IMPORT_LIB@

fcml_cpp_check_LDADD = $(top_srcdir)/src/libfcml.la $(top_srcdir)/check/stf/libstf.la

check_SCRIPTS = fcml_cpp_check

TESTS = $(check_SCRIPTS)

