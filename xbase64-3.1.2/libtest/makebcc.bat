
rem This batch file builds the xbase sample programs
rem using the borland 5.5 compiler

del *.bak
del *.tds
del *.exe
del *.obj
del compout


bcc32 -Id:\xbase64 -Id:\borland\bcc55\include -L\borland\bcc55\lib -L..\xbase64 indextst.cpp  xbase64.lib >> compout
bcc32 -Id:\xbase64 -Id:\borland\bcc55\include -L\borland\bcc55\lib -L..\xbase64 exptest.cpp   xbase64.lib >> compout
bcc32 -Id:\xbase64 -Id:\borland\bcc55\include -L\borland\bcc55\lib -L..\xbase64 locktest.cpp  xbase64.lib >> compout
bcc32 -Id:\xbase64 -Id:\borland\bcc55\include -L\borland\bcc55\lib -L..\xbase64 testdate.cpp  xbase64.lib >> compout

