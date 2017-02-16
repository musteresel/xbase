
INCLUDES= -I$(topdir)
LDADD	= -L$(topdir)/xbase64 -lxbase64

INSTALL_PROGRAM = @INSTALL@

bin_PROGRAMS = checkndx copydbf dbfxtrct deletall dumphdr dumprecs packdbf   \
               reindex undelall zap dbfutil1

noinst_PROGRAMS = dumpdbt

checkndx_SOURCES  = checkndx.cpp 
copydbf_SOURCES   = copydbf.cpp 
dbfxtrct_SOURCES  = dbfxtrct.cpp
dbfutil1_SOURCES  = dbfutil1.cpp
deletall_SOURCES  = deletall.cpp 
dumpdbt_SOURCES   = dumpdbt.cpp 
dumphdr_SOURCES   = dumphdr.cpp 
dumprecs_SOURCES  = dumprecs.cpp 
packdbf_SOURCES   = packdbf.cpp 
reindex_SOURCES   = reindex.cpp 
undelall_SOURCES  = undelall.cpp
zap_SOURCES       = zap.cpp

noinst_HEADERS =

EXTRA_DIST = makebcc.bat 

CLEANFILES = Makefile.in *.exe *.BAK *.tds *.obj *.tr2 *.ndx *.dbf *.dbt \
	*.ntx compout
