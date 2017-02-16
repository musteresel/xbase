
INCLUDES= -I$(topdir) $(all_includes)
LDADD	= -L$(topdir)/xbase64 -lxbase64

# for shadow passwords override the value
INSTALL_PROGRAM = @INSTALL@

noinst_PROGRAMS = sample1 sample2 sample3 sample4 sample5 \
               exfilter xbstring
	       
exfilter_SOURCES = exfilter.cpp
sample1_SOURCES  = sample1.cpp
sample2_SOURCES  = sample2.cpp
sample3_SOURCES  = sample3.cpp
sample4_SOURCES  = sample4.cpp
sample5_SOURCES  = sample5.cpp
xbstring_SOURCES = xbstring.cpp

noinst_HEADERS =

EXTRA_DIST = makebcc.bat 

CLEANFILES = Makefile.in *.obj *.exe *.dbf *.dbt *.ndx *.ntx compout *.tds *.bak
