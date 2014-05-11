
ACLOCAL_AMFLAGS = -I m4

EXTRA_DIST = win32/vs2008/fcml/fcml-check/fcml-check.vcproj \
	win32/vs2008/fcml/fcml-check/stdafx.h \
	win32/vs2008/fcml/fcml-check/targetver.h \
	win32/vs2008/fcml/fcml.sln \
	win32/vs2008/fcml/fcml/dllmain.c \
	win32/vs2008/fcml/fcml/fcml.aps \
	win32/vs2008/fcml/fcml/fcml.def \
	win32/vs2008/fcml/fcml/fcml.rc \
	win32/vs2008/fcml/fcml/fcml.vcproj \
	win32/vs2008/fcml/fcml/resource.h \
	win32/vs2008/fcml/fcml/resource1.h \
	win32/vs2008/fcml/examples/hsdis/dllmain.cpp \
	win32/vs2008/fcml/examples/hsdis/hsdis.cpp \
	win32/vs2008/fcml/examples/hsdis/hsdis.def \
	win32/vs2008/fcml/examples/hsdis/hsdis.h \
	win32/vs2008/fcml/examples/hsdis/hsdis.aps \
	win32/vs2008/fcml/examples/hsdis/hsdis.rc \
	win32/vs2008/fcml/examples/hsdis/resource.h \
	win32/vs2008/fcml/examples/hsdis/hsdis.vcproj \
	win32/vs2008/fcml/examples/hsdis/stdafx.cpp \
	win32/vs2008/fcml/examples/hsdis/stdafx.h \
	win32/vs2008/fcml/examples/hsdis/targetver.h

if HAVE_DOXYGEN
DOXYDIR = docs/doxygen
endif

SUBDIRS = include src check example $(DOXYDIR)
