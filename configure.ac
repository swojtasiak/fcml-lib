#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([fcml], [1.0.0], [fcml-bugs@swksoftware.pl])
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

# Checks for libraries.

# Checks for header files.
AC_FUNC_ALLOCA
AC_CHECK_HEADERS([inttypes.h libintl.h malloc.h stddef.h stdint.h stdlib.h string.h unistd.h])

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
AC_CHECK_FUNCS([memset strtoul strtoull vsnprintf memcpy])

# Configure DEBUG source code, if requested.
AS_IF([test "x$debug" = xyes],
	[AC_DEFINE([FCML_DEBUG], [1], [Define to enable FCML debug features])])

# Doxygen
AC_CHECK_PROG([DOXYGEN], [doxygen], [doxygen])
if test -z "$DOXYGEN"; then 
    AC_MSG_WARN([Doxygen not found - continuing without Doxygen support])
fi

AM_CONDITIONAL([HAVE_DOXYGEN], [test -n "$DOXYGEN"])
AM_COND_IF([HAVE_DOXYGEN], [AC_CONFIG_FILES([docs/doxygen/doxyfile])])

# Configuration files.
AC_CONFIG_FILES([Makefile
                 src/Makefile
				 check/Makefile
				 check/stf/Makefile                 
				 check/internal-tests/Makefile
				 check/public-tests/Makefile
				 example/Makefile
				 example/fcml-disasm/Makefile
				 example/fcml-asm/Makefile
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

AC_OUTPUT
echo "***************************************************
${PACKAGE_NAME} version ${PACKAGE_VERSION}
Host CPU.........: $host_cpu
Host OS:.........: $host_os
Prefix:..........: ${prefix}
Debug Build......: $debug
Shared Library...: $enable_shared
Compiler.........: ${CC} ${CFLAGS} ${CPPFLAGS}
Linker...........: $LD $LDFLAGS $LIBS
Doxygen..........: ${DOXYGEN:-NONE}
***************************************************
"
