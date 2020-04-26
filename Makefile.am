
ACLOCAL_AMFLAGS = -I m4

EXTRA_DIST = win32/dist.bat \
	win32/vs2017/fcml/examples/hsdis/dllmain.cpp \
	win32/vs2017/fcml/examples/hsdis/hsdis.def \
	win32/vs2017/fcml/examples/hsdis/hsdis.rc \
	win32/vs2017/fcml/examples/hsdis/hsdis.vcxproj \
	win32/vs2017/fcml/examples/hsdis/hsdis.vcxproj.filters \
	win32/vs2017/fcml/examples/hsdis/resource.h \
	win32/vs2017/fcml/examples/hsdis/targetver.h \
	win32/vs2017/fcml/fcml-check-cpp/fcml-check-cpp.vcxproj \
	win32/vs2017/fcml/fcml-check-cpp/fcml-check-cpp.vcxproj.filters \
	win32/vs2017/fcml/fcml-check/fcml-check.vcxproj \
	win32/vs2017/fcml/fcml-check/fcml-check.vcxproj.filters \
	win32/vs2017/fcml/fcml.sln \
	win32/vs2017/fcml/fcml/dllmain.c \
	win32/vs2017/fcml/fcml/fcml.def \
	win32/vs2017/fcml/fcml/fcml.rc \
	win32/vs2017/fcml/fcml/fcml.vcxproj \
	win32/vs2017/fcml/fcml/fcml.vcxproj.filters \
	win32/vs2017/fcml/fcml/resource.h \
	win32/vs2017/fcml/fcml/resource1.h \
	win32/vs2019/fcml/examples/hsdis/dllmain.cpp \
	win32/vs2019/fcml/examples/hsdis/hsdis.def \
	win32/vs2019/fcml/examples/hsdis/hsdis.rc \
	win32/vs2019/fcml/examples/hsdis/hsdis.vcxproj \
	win32/vs2019/fcml/examples/hsdis/hsdis.vcxproj.filters \
	win32/vs2019/fcml/examples/hsdis/resource.h \
	win32/vs2019/fcml/examples/hsdis/targetver.h \
	win32/vs2019/fcml/fcml-check-cpp/fcml-check-cpp.vcxproj \
	win32/vs2019/fcml/fcml-check-cpp/fcml-check-cpp.vcxproj.filters \
	win32/vs2019/fcml/fcml-check/fcml-check.vcxproj \
	win32/vs2019/fcml/fcml-check/fcml-check.vcxproj.filters \
	win32/vs2019/fcml/fcml.sln \
	win32/vs2019/fcml/fcml/dllmain.c \
	win32/vs2019/fcml/fcml/fcml.def \
	win32/vs2019/fcml/fcml/fcml.rc \
	win32/vs2019/fcml/fcml/fcml.vcxproj \
	win32/vs2019/fcml/fcml/fcml.vcxproj.filters \
	win32/vs2019/fcml/fcml/resource.h \
	win32/vs2019/fcml/fcml/resource1.h

if HAVE_DOXYGEN
DOXYDIR = docs/doxygen
endif

SUBDIRS = include src check example $(DOXYDIR)

docker-build:
	@echo 'Building an image for dockerized unit tests.'
	docker-compose -f docker-compose.yml build

docker-tests: docker-build
	@echo 'Running the dockerized unit tests.'
	docker-compose -f docker-compose.yml run --rm tests
