#ifdef __GNU_LesserG__
#pragma implementation "xbfile.h"
#endif

#ifdef __WIN32__
#include <xbase64/xbwincfg.h>
#else
#include <xbase64/xbconfig.h>
#endif

#include <xbase64/xbase64.h>

xbString xbFile::MakeFileName(const char * name) {
	xbString file = name;
	if (file.isEmpty())
		return file;
	int len = strlen(name);
	const char * extLower = GetExtWithDot(true);
	const char * extUpper = GetExtWithDot(false);
	int lenLower = strlen(extLower);
	int lenUpper = strlen(extUpper);
	if ((len > lenLower && strcmp(&name[len - lenLower], extLower) == 0) ||
	    (len > lenUpper && strcmp(&name[len - lenUpper], extUpper) == 0))
		return file;
	char lastSymbol = name[len - 1];
	file += GetExtWithDot(lastSymbol < 'A' || lastSymbol > 'Z');
	return file;
}
