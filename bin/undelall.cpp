#include <xbase64/xbase64.h>

int main(int ac, char ** av) {
	if (ac <= 1) {
		std::cout
		    << "\nUsage: undelall filename...\n"
		       "\nThis program does not automatically reindex any NDX indexes."
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
			std::cout << "Could not open file " << filename << "\n";
			return 0;
		}

		xbShort rc = MyFile.UndeleteAllRecords();
		if (rc != XB_NO_ERROR) {
			std::cout << "\nError undeleting records - database ==> "
			          << filename;
			std::cout << " Return Code = " << rc;
		}
		MyFile.CloseDatabase(); /* close database */

		std::cout << "\nUndelete all records complete...\n\n";
	}
	return 0;
}
