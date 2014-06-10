# Make sure that FCML is built.
SUBDIRS = ../../src

lib_LTLIBRARIES = libhsdis.la

libhsdis_la_SOURCES = hsdis.c hsdis.h

libhsdis_la_CPPFLAGS = -I$(top_srcdir)/include

libhsdis_la_LIBADD = $(top_srcdir)/src/libfcml.la
