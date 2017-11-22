#include <xbase64/xbase64.h>

int main(int ac, char ** av) {
#ifdef XBASE_DEBUG
	xbXBase x;
	xbDbf d(&x);
	xbNdx i(&d);
	xbShort rc;

	if (3 != ac) {
		std::cout << "\nUsage: checkndx dbf_file index_file\n";
		return 1;
	}

	if ((rc = d.OpenDatabase(av[1])) != XB_NO_ERROR) {
		std::cout << "\nCould not open file " << av[1] << " rc = " << rc
		          << "\n";
		return 2;
	}

	if ((rc = i.OpenIndex(av[2])) != XB_NO_ERROR) {
		std::cout << "\nCould not open file " << av[2] << " rc = " << rc
		          << "\n";
		return 3;
	}

	std::cout << "\nRunning...\n";
	rc = i.CheckIndexIntegrity(1);
	std::cout << "\nNdx integrity check = " << rc << "\n";

	i.DumpHdrNode(0);

	d.CloseDatabase();
#else
	std::cout << "\nXBASE_DEBUG is not compiled in\n";
#endif
	return 0;
}
