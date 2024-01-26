WIN32_FINAL_DIST = vs2019

define build_win32
	rm -Rf $(1)/dist

	mkdir -p $(1)/dist/x86
	mkdir -p $(1)/dist/x86/debug-dll
	mkdir -p $(1)/dist/x86/debug-lib
	mkdir -p $(1)/dist/x86/release-dll
	mkdir -p $(1)/dist/x86/release-lib
	mkdir -p $(1)/dist/x86_hsdis
	
	mkdir -p $(1)/dist/x64
	mkdir -p $(1)/dist/x64/debug-dll
	mkdir -p $(1)/dist/x64/debug-lib
	mkdir -p $(1)/dist/x64/release-dll
	mkdir -p $(1)/dist/x64/release-lib
	mkdir -p $(1)/dist/x64_hsdis
	
	cp $(1)/fcml/Debug-dll/fcml.dll $(1)/dist/x86/debug-dll
	cp $(1)/fcml/Debug-dll/fcml.lib $(1)/dist/x86/debug-dll
	cp $(1)/fcml/Release-dll/fcml.dll $(1)/dist/x86/release-dll
	cp $(1)/fcml/Release-dll/fcml.lib $(1)/dist/x86/release-dll
	cp $(1)/fcml/Debug-lib/fcml.lib $(1)/dist/x86/debug-lib
	cp $(1)/fcml/Release-lib/fcml.lib $(1)/dist/x86/release-lib

	cp $(1)/fcml/Release-lib/hsdis.dll $(1)/dist/x86_hsdis/hsdis.dll
	cp $(1)/fcml/Release-lib/hsdis.lib $(1)/dist/x86_hsdis/hsdis.lib
	cp ../example/hsdis/COPYING $(1)/dist/x86_hsdis/
	
	cp $(1)/fcml/x64/Debug-dll/fcml.dll $(1)/dist/x64/debug-dll
	cp $(1)/fcml/x64/Debug-dll/fcml.lib $(1)/dist/x64/debug-dll
	cp $(1)/fcml/x64/Release-dll/fcml.dll $(1)/dist/x64/release-dll
	cp $(1)/fcml/x64/Release-dll/fcml.lib $(1)/dist/x64/release-dll
	cp $(1)/fcml/x64/Debug-lib/fcml.lib $(1)/dist/x64/debug-lib
	cp $(1)/fcml/x64/Release-lib/fcml.lib $(1)/dist/x64/release-lib

	cp $(1)/fcml/x64/Release-lib/hsdis.dll $(1)/dist/x64_hsdis/hsdis.dll
	cp $(1)/fcml/x64/Release-lib/hsdis.lib $(1)/dist/x64_hsdis/hsdis.lib
	cp ../example/hsdis/COPYING $(1)/dist/x64_hsdis/

	cp -R ../include $(1)/dist/
	rm -f $(1)/dist/include/.gitignore
	rm -f $(1)/dist/include/Makefile*

	zip $(1)/dist/hsdis-$(PACKAGE_VERSION)-win32-x86.zip -9 -j $(1)/dist/x86_hsdis/hsdis.dll $(1)/dist/x86_hsdis/hsdis.lib $(1)/dist/x86_hsdis/COPYING
	zip $(1)/dist/hsdis-$(PACKAGE_VERSION)-win32-amd64.zip -9 -j $(1)/dist/x64_hsdis/hsdis.dll $(1)/dist/x64_hsdis/hsdis.lib $(1)/dist/x64_hsdis/COPYING

	cd $(1)/dist/; zip fcml-$(PACKAGE_VERSION)-win32-VS.zip -9 -r x86/ x64/ include/
endef

build-release:
	$(call build_win32,$(WIN32_FINAL_DIST))
	rm -Rf dist/
	mv $(WIN32_FINAL_DIST)/dist dist/

.PHONY: build-release
