
INCLUDES= -I$(topdir)
LDADD	= -L$(topdir)/xbase64 -lxbase64

INSTALL_PROGRAM = @INSTALL@

noinst_PROGRAMS = indextst exptest locktest testdate lfiletst

indextst_SOURCES  = indextst.cpp
exptest_SOURCES   = exptest.cpp
locktest_SOURCES  = locktest.cpp
testdate_SOURCES  = testdate.cpp
lfiletst_SOURCES  = lfiletst.cpp 

noinst_HEADERS =

EXTRA_DIST = readme makebcc.bat

CLEANFILES = Makefile.in *.exe compout *.tds *.dbf *.dbt *.ndx *.ntx *.obj
