
rem This batch file builds the xbase utility programs
rem using the borland 5.5 compiler

del *.bak
del *.tds
del *.exe
del *.obj

bcc32 -I.. -I/borland/bcc55/include -L/borland/bcc55/lib -L../xbase64 checkndx.cpp xbase64.lib  > compout
bcc32 -I.. -I/borland/bcc55/include -L/borland/bcc55/lib -L../xbase64 copydbf.cpp  xbase64.lib >> compout
bcc32 -I.. -I/borland/bcc55/include -L/borland/bcc55/lib -L../xbase64 dbfutil1.cpp xbase64.lib >> compout
bcc32 -I.. -I/borland/bcc55/include -L/borland/bcc55/lib -L../xbase64 dbfxtrct.cpp xbase64.lib >> compout
bcc32 -I.. -I/borland/bcc55/include -L/borland/bcc55/lib -L../xbase64 deletall.cpp xbase64.lib >> compout
bcc32 -I.. -I/borland/bcc55/include -L/borland/bcc55/lib -L../xbase64 dumpdbt.cpp  xbase64.lib >> compout
bcc32 -I.. -I/borland/bcc55/include -L/borland/bcc55/lib -L../xbase64 dumphdr.cpp  xbase64.lib >> compout
bcc32 -I.. -I/borland/bcc55/include -L/borland/bcc55/lib -L../xbase64 dumprecs.cpp xbase64.lib >> compout
bcc32 -I.. -I/borland/bcc55/include -L/borland/bcc55/lib -L../xbase64 packdbf.cpp  xbase64.lib >> compout
bcc32 -I.. -I/borland/bcc55/include -L/borland/bcc55/lib -L../xbase64 reindex.cpp  xbase64.lib >> compout
bcc32 -I.. -I/borland/bcc55/include -L/borland/bcc55/lib -L../xbase64 undelall.cpp xbase64.lib >> compout
bcc32 -I.. -I/borland/bcc55/include -L/borland/bcc55/lib -L../xbase64 zap.cpp      xbase64.lib >> compout

