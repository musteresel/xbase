#include <xbase64/xbase64.h>

int main(int ac, char ** av) {
	if (ac <= 1) {
		std::cout << "\nUsage: deletall filename...\n";
		return 1;
	}

	for (int i = 1; i < ac; ++i) {
		char * filename = av[i];

		xbXBase x;
		xbDbf MyFile(&x);

		if (MyFile.OpenDatabase(filename)) {
			std::cout << "Could not open file " << filename << "\n";
			return 2;
		}

		xbShort rc = MyFile.DeleteAllRecords();
		if (rc != XB_NO_ERROR) {
			std::cout << "\nError Deleting all records - database ==> "
			          << filename;
			std::cout << " Return Code = " << rc;
		}
		MyFile.CloseDatabase(); /* close database */

		std::cout << "\nDone...\n\n";
	}

	return 0;
}
