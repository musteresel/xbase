
rem This batch file builds the xbase sample programs
rem using the borland 5.5 compiler

del *.bak
del *.tds
del *.exe
del *.obj

bcc32 -I.. -I/borland/bcc55/include -L../xbase64 -L/borland/bcc55/lib sample1.cpp xbase64.lib >  compout
bcc32 -v -I.. -I/borland/bcc55/include -L../xbase64 -L/borland/bcc55/lib sample2.cpp xbase64.lib >> compout
bcc32 -I.. -I/borland/bcc55/include -L../xbase64 -L/borland/bcc55/lib sample3.cpp xbase64.lib >> compout
bcc32 -I.. -I/borland/bcc55/include -L../xbase64 -L/borland/bcc55/lib sample4.cpp xbase64.lib >> compout
bcc32 -I.. -I/borland/bcc55/include -L../xbase64 -L/borland/bcc55/lib sample5.cpp xbase64.lib >> compout
bcc32 -I.. -I/borland/bcc55/include -L../xbase64 -L/borland/bcc55/lib exfilter.cpp xbase64.lib >> compout
bcc32 -I.. -I/borland/bcc55/include -L../xbase64 -L/borland/bcc55/lib xbstring.cpp xbase64.lib >> compout

