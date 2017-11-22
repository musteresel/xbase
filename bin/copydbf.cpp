#include <xbase64/xbase64.h>

int main(int ac, char ** av) {
	if (3 != ac) {
		std::cout
		    << "\nUsage: copydbf filename1 filename2\n"
		       "This program copies the structure of one dbf file to another\n";
		return 1;
	}

	char * sfilename = av[1];
	char * tfilename = av[2];

	xbXBase x;
	xbDbf MyFile(&x);

	xbShort rc = MyFile.OpenDatabase(sfilename);
	if (rc != XB_NO_ERROR) {
		std::cout << "Could not open file " << sfilename << " Error = " << rc
		          << "\n";
		return 2;
	}

	//   OverlaySwitch = 0;    	/* dont overlay existing file if it exists */
	xbShort OverlaySwitch = 1; /* overlay existing file if it exists */

	if ((rc = MyFile.CopyDbfStructure(tfilename, OverlaySwitch)) !=
	    XB_NO_ERROR) {
		std::cout << "Could not copy file " << tfilename << " Error = " << rc
		          << "\n";
		return 3;
	}

	MyFile.CloseDatabase(); /* close database */
	return 0;
}
