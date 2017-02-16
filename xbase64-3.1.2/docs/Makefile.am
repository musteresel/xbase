all : docs

docs :
	doxygen doxygen.cfg

clean :
	-rm -r html
	-rm -r latex
	-rm -r man

EXTRA_DIST = \
	Makefile.am \
	Makefile.in \
	doxygen.cfg.in
