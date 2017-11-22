#include <xbase64/xbase64.h>

int main(int ac, char ** av) {
	if (ac <= 1) {
		std::cout
		    << "\nUsage: zap filename...\n"
		       "\nThis program does not automatically reindex any indices."
		       "\nUse the reindex program to reindex any indexes associated"
		       "\nwith the database, or build your own program which executes "
		       "\nthe PackDatabase() method after opening all the index files "
		       "\nassociated with the database.\n\n";
		return 1;
	}

	for (int i = 1; i < ac; ++i) {
		char * filename = av[i];

		xbXBase x;
		xbDbf MyFile(&x);
		if (MyFile.OpenDatabase(filename)) {
			std::cout << "Could not open file " << filename << std::endl;
			return 0;
		}

		xbShort rc = MyFile.Zap(XB_LOCK);
		if (rc != XB_NO_ERROR) {
			std::cout << "\nError zapping database ==> " << filename;
			std::cout << " Return Code = " << rc << std::endl;
		}
		MyFile.CloseDatabase(); /* close database */

		std::cout << "\nZap Database complete..." << std::endl;
	}

	return 0;
}
