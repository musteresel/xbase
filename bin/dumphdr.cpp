#include <xbase64/xbase64.h>

int main(int ac, char ** av) {
#ifdef XBASE_DEBUG
	xbShort rc;
	xbXBase x;

	if (ac <= 1) {
		std::cout << "\nUsage: dumphdr filename...\n";
		return 1;
	}
	for (int i = 1; i < ac; ++i) {
		char * filename = av[i];
		xbDbf MyFile(&x);

		if ((rc = MyFile.OpenDatabase(filename)) != 0) {
			std::cout << "Could not open file rc = " << rc
			          << " file = " << filename << "\n";
			return 0;
		}
		MyFile.DumpHeader(3);
		MyFile.CloseDatabase();
	}
#else
	std::cout << "\nXBASE_DEBUG is not compiled in\n";
#endif
	return 0;
}
