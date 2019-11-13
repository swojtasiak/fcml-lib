rem In order to build the project use VS directly. This file is here 
rem for internal purpose only and shouldn't be used to build anything.
set base=%1
rd /s /q %base%\dist
mkdir %base%\dist
rem x86
mkdir %base%\dist\x86
mkdir %base%\dist\x86\debug-dll
mkdir %base%\dist\x86\debug-lib
mkdir %base%\dist\x86\release-dll
mkdir %base%\dist\x86\release-lib
mkdir %base%\dist\x86\hsdis
rem x64
mkdir %base%\dist\x64
mkdir %base%\dist\x64\debug-dll
mkdir %base%\dist\x64\debug-lib
mkdir %base%\dist\x64\release-dll
mkdir %base%\dist\x64\release-lib
mkdir %base%\dist\x64\hsdis
rem x86
copy %base%\fcml\Debug-dll\fcml.dll %base%\dist\x86\debug-dll
copy %base%\fcml\Debug-dll\fcml.lib %base%\dist\x86\debug-dll
copy %base%\fcml\Release-dll\fcml.dll %base%\dist\x86\release-dll
copy %base%\fcml\Release-dll\fcml.lib %base%\dist\x86\release-dll
copy %base%\fcml\Debug-lib\fcml.lib %base%\dist\x86\debug-lib
copy %base%\fcml\Release-lib\fcml.lib %base%\dist\x86\release-lib
copy %base%\fcml\Release-lib\hsdis.dll %base%\dist\x86\hsdis\hsdis-i386.dll
copy %base%\fcml\Release-lib\hsdis.lib %base%\dist\x86\hsdis\hsdis-i386.lib
rem x64
copy %base%\fcml\x64\Debug-dll\fcml.dll %base%\dist\x64\debug-dll
copy %base%\fcml\x64\Debug-dll\fcml.lib %base%\dist\x64\debug-dll
copy %base%\fcml\x64\Release-dll\fcml.dll %base%\dist\x64\release-dll
copy %base%\fcml\x64\Release-dll\fcml.lib %base%\dist\x64\release-dll
copy %base%\fcml\x64\Debug-lib\fcml.lib %base%\dist\x64\debug-lib
copy %base%\fcml\x64\Release-lib\fcml.lib %base%\dist\x64\release-lib
copy %base%\fcml\x64\Release-lib\hsdis.dll %base%\dist\x64\hsdis\hsdis-amd64.dll
copy %base%\fcml\x64\Release-lib\hsdis.lib %base%\dist\x64\hsdis\hsdis-amd64.lib
