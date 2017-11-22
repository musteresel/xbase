#include <xbase64/xbase64.h>

// next lines are helpful for debugging purposes
#include <xbase64/xbase64.cpp>
#include <xbase64/xbcdx.cpp>
#include <xbase64/xbdate.cpp>
#include <xbase64/xbdbf.cpp>
#include <xbase64/xbexp.cpp>
#include <xbase64/xbexpfnc.cpp>
#include <xbase64/xbexpprc.cpp>
#include <xbase64/xbfields.cpp>
#include <xbase64/xbfile.cpp>
#include <xbase64/xbfilter.cpp>
#include <xbase64/xbindex.cpp>
#include <xbase64/xblock.cpp>
#include <xbase64/xbmemo.cpp>
#include <xbase64/xbndx.cpp>
#include <xbase64/xbntx.cpp>
#include <xbase64/xbstring.cpp>

int main(int ac, char ** av) {
	xbXBase x;
	xbShort rc;

	if (ac <= 1) {
		std::cout << "Usage: dumprecs filename..." << std::endl;
		return 1;
	}

	for (int i = 1; i < ac; ++i) {
		char * filename = av[i];

		xbDbf MyFile(&x);

		MyFile.SetVersion(4);
		rc = MyFile.OpenDatabase(filename);
		if (rc != XB_NO_ERROR) {
			std::cout << "Could not open file " << filename << std::endl;
			x.DisplayError(rc);
			return 1;
		}

		std::cout << "Processing file sequentially from beginning..."
		          << std::endl;
		i = 0;
		while (i < MyFile.NoOfRecords()) {
			rc = MyFile.DumpRecord(++i);
			if (rc != XB_NO_ERROR)
				x.DisplayError(rc);
		}
		MyFile.CloseDatabase(); /* close database */
	}
	return 0;
}
