#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([fcml], [0.0.1], [fcml-bugs@swksoftware.pl])
AM_INIT_AUTOMAKE
LT_PREREQ([2.2])
LT_INIT
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_SRCDIR([include/fcml_common.h])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC
AC_PROG_INSTALL
AM_PROG_LEX
AC_PROG_YACC

AM_PROG_CC_C_O

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
AC_C_RESTRICT
AC_TYPE_SIZE_T
AC_CHECK_HEADER_STDBOOL
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T
AC_TYPE_UINT64_T
AC_TYPE_UINT8_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_CHECK_FUNCS([memset pow strtoul strtoull])

# Configure DEBUG source code, if requested.
AS_IF([test "x$debug" = xyes],
	[AC_DEFINE([FCML_DEBUG], [1], [Define to enable FCML debug features])])

# Configuration files.
AC_CONFIG_FILES([Makefile
                 src/Makefile
				 check/Makefile                 
                 include/Makefile])

AC_OUTPUT
echo "***************************************************
${PACKAGE_NAME} version ${PACKAGE_VERSION}
Prefix:........: ${prefix}
Debug Build....: $debug
Compiler.......: ${CC} ${CFLAGS} ${CPPFLAGS}
Linker.........: $LD $LDFLAGS $LIBS
***************************************************
"
