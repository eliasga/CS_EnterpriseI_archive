@echo off
set COMPILER=cl 
				set COMPFLAGS=/c /GR /W3 /EHs /nologo /MD -I"C:\Program Files\MATLAB\R2014b\extern\include" -I"C:\Program Files\MATLAB\R2014b\simulink\include" -I"c:\Program Files (x86)\Microsoft Visual Studio 9.0\VC\redist\amd64\Microsoft.VC90.CRT"  /D_CRT_SECURE_NO_DEPRECATE /D_SCL_SECURE_NO_DEPRECATE /D_SECURE_SCL=0   /DMATLAB_MEX_FILE /D_CRT_SECURE_NO_DEPRECATE /D_SCL_SECURE_NO_DEPRECATE /D_SECURE_SCL=0   /DMATLAB_MEX_FILE  /DMATLAB_MEX_FILE 
				set OPTIMFLAGS=/O2 /Oy- /DNDEBUG 
				set DEBUGFLAGS=/Z7 
				set LINKER=link 
				set LINKFLAGS= /nologo /manifest kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /incremental:NO /export:%ENTRYPOINT% /DLL /LIBPATH:"C:\Program Files\MATLAB\R2014b\extern\lib\win64\microsoft" libmx.lib libmex.lib libmat.lib  /EXPORT:mexFunction 
				set LINKDEBUGFLAGS=/debug /PDB:"%OUTDIR%%MEX_NAME%.mexw64.pdb" 
				set NAME_OUTPUT=/out:"%OUTDIR%%MEX_NAME%%MEX_EXT%"
set PATH=c:\Program Files (x86)\Microsoft Visual Studio 9.0\VC\Bin\amd64;c:\Program Files (x86)\Microsoft Visual Studio 9.0\VC\Bin;c:\Program Files (x86)\Microsoft Visual Studio 9.0\VC\VCPackages;c:\Program Files (x86)\Microsoft Visual Studio 9.0\Common7\IDE;c:\Program Files (x86)\Microsoft Visual Studio 9.0\Common7\Tools;c:\Program Files (x86)\Microsoft Visual Studio 9.0\Common7\Tools\bin;C:\Program Files\Microsoft SDKs\Windows\v6.0A\\Bin\x64;C:\Program Files\Microsoft SDKs\Windows\v6.0A\\Bin\win64\x64;C:\Program Files\Microsoft SDKs\Windows\v6.0A\\Bin;C:\Program Files\MATLAB\R2014b\bin\win64;%MATLAB_BIN%;%PATH%
set INCLUDE=c:\Program Files (x86)\Microsoft Visual Studio 9.0\VC\ATLMFC\INCLUDE;c:\Program Files (x86)\Microsoft Visual Studio 9.0\VC\INCLUDE;C:\Program Files\Microsoft SDKs\Windows\v6.0A\\include;C:\Program Files\MATLAB\R2014b\extern\include;%INCLUDE%
set LIB=c:\Program Files (x86)\Microsoft Visual Studio 9.0\VC\ATLMFC\LIB\amd64;c:\Program Files (x86)\Microsoft Visual Studio 9.0\VC\Lib\amd64;C:\Program Files\Microsoft SDKs\Windows\v6.0A\\Lib\X64;C:\Program Files\Microsoft SDKs\Windows\v6.0A\\Lib;C:\Program Files\MATLAB\R2014b\bin\win64;C:\Program Files\MATLAB\R2014b\lib\win64;%LIB%
set LIBPATH=c:\Program Files (x86)\Microsoft Visual Studio 9.0\VC\Lib\amd64;c:\Program Files (x86)\Microsoft Visual Studio 9.0\VC\ATLMFC\LIB\amd64;c:\Program Files (x86)\Microsoft Visual Studio 9.0\VC\Lib\amd64;C:\Program Files\MATLAB\R2014b\extern\lib\win64\microsoft;C:\Program Files\Microsoft SDKs\Windows\v6.0A\\LIB\x64;C:\Program Files\MATLAB\R2014b\extern\lib\win64;;%LIBPATH%

nmake -f untitled_sfun.mak
