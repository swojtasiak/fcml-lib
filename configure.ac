#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([fcml], [1.3.0], [slawomir.wojtasiak@fcml-lib.com])
AM_INIT_AUTOMAKE
LT_PREREQ([2.2])
LT_INIT[win32-dll]
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_SRCDIR([include/fcml_common.h])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC
AC_PROG_CC_STDC
AC_PROG_CXX
AC_PROG_CPP
AC_PROG_AWK
AC_PROG_INSTALL
AM_PROG_LEX
AC_PROG_YACC
AM_PROG_CC_C_O
AC_PROG_LN_S
AC_PROG_MAKE_SET

# Configure options: --enable-debug[=no].
AC_ARG_ENABLE([debug],
	[AS_HELP_STRING([--enable-debug],
	[enable debug code @<:@default=no@:>@])],
	[debug="$withval"], [debug=no])

# Configure options: --disable-cpp-wrapper[=no].
AC_ARG_ENABLE([cpp_wrapper],
	[AS_HELP_STRING([--disable-cpp-wrapper],
	[disables c++ wrapper tests])],
	[], [cpp_wrapper=yes])

# Checks for libraries.

# Checks for header files.
AC_FUNC_ALLOCA
AC_CHECK_HEADERS([inttypes.h libintl.h malloc.h stddef.h stdint.h stdlib.h string.h unistd.h limits.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_C_INLINE
AC_TYPE_INT16_T
AC_TYPE_INT32_T
AC_TYPE_INT64_T
AC_TYPE_INT8_T
AC_TYPE_SIZE_T
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T
AC_TYPE_UINT64_T
AC_TYPE_UINT8_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_CHECK_FUNCS([memset strtoul strtoull vsnprintf memcpy strchr strtol])

# Configure DEBUG source code, if requested.
AS_IF([test "x$debug" = xyes],
	[AC_DEFINE([FCML_DEBUG], [1], [Define to enable FCML debug features])])

# Doxygen
AC_CHECK_PROG([DOXYGEN], [doxygen], [doxygen])
if test -z "$DOXYGEN"; then 
    AC_MSG_WARN([Doxygen not found - continuing without Doxygen support])
fi

# Disable the internal part of unit tests for cygwin and mingw, 
# due to the way Windows exports symbols in shared libraries.
AS_CASE(
	[$host_os], [cygwin*|mingw*],
	[internal_test=no
# Maybe not the most beatiful way to write it, but as least it doesn't have
# to be written in one line and Eclipse's parser doesn't complain.
internal_test_msg="(Don't be afraid of disabled internal unit tests for"
internal_test_msg="$internal_test_msg"$'\n'"                           this configuration. Integration tests which are"
internal_test_msg="$internal_test_msg"$'\n'"                           built on top of the public API are still executed.)"
	],
	[internal_test=yes]
)

AM_CONDITIONAL([CPP_WRAPPER], [ [test -n "$CXX"] && [test "x$cpp_wrapper" = xyes] ])
AM_CONDITIONAL([ENABLE_INTERNAL_TESTS], [test "x$internal_test" = xyes])
AM_CONDITIONAL([HAVE_DOXYGEN], [test -n "$DOXYGEN"])
AM_COND_IF([HAVE_DOXYGEN], [AC_CONFIG_FILES([docs/doxygen/doxyfile])])

# Configuration files.
AC_CONFIG_FILES([Makefile
                 src/Makefile
                 check/Makefile
                 check/stf/Makefile                 
                 check/internal-tests/Makefile
                 check/public-tests/Makefile
                 check/cpp-tests/Makefile
                 example/Makefile
                 example/fcml-disasm/Makefile
                 example/fcml-asm/Makefile
                 example/hsdis/Makefile
								 win32/Makefile
                 include/Makefile
                 docs/doxygen/Makefile])

# Enable __declspec(dllimport) for linking public tests with shared DLL.
AC_CANONICAL_HOST

AS_CASE(
	[$enable_shared], [yes],
	[AS_CASE(
		[$host_os], [cygwin*|mingw*],
		[FCML_IMPORT_LIB="-DLIBFCML_DLL_IMPORT"
			AC_SUBST([FCML_IMPORT_LIB])]
	)]
)

# Check whether the compiler can hide symbols
VISIBILITY_CFLAGS=""
AS_COMPILER_FLAG([-fvisibility=hidden], [VISIBILITY_CFLAGS="-fvisibility=hidden"])
AC_SUBST(VISIBILITY_CFLAGS)

AS_IF([test -n "$VISIBILITY_CFLAGS"],
    [AC_DEFINE([SUPPORT_VISIBILITY_HIDDEN], [1], [Support for -fvisibility=hidden flag.])])

CFLAGS="$CFLAGS $VISIBILITY_CFLAGS"

AC_OUTPUT
echo "***************************************************
${PACKAGE_NAME} version ${PACKAGE_VERSION}
Host CPU.............: $host_cpu
Host OS:.............: $host_os
Prefix:..............: ${prefix}
Debug Build..........: $debug
C++ wrapper tests....: ${cpp_wrapper:-no}
Internal unit tests..: ${internal_test} ${internal_test_msg}
Shared Library.......: $enable_shared
C Compiler...........: ${CC} ${CFLAGS} ${CPPFLAGS}
C++ Compiler.........: ${CXX} ${CXXFLAGS}
Linker...............: $LD $LDFLAGS $LIBS
Doxygen..............: ${DOXYGEN:-NONE}
***************************************************
"
