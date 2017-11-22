#include <xbase64/xbase64.h>

static void showStatus(xbLong itemNum, xbLong numItems) {
	printf("indexing record %ld of %ld\r", itemNum, numItems);
	fflush(stdout);
}

int main(int ac, char ** av) {
	if (3 != ac) {
		std::cout << "\nUsage: reindex dbf_file ndx_file\n";
		return 1;
	}

	char * filename = av[1];
	char * filename2 = av[2];

	xbXBase x;
	xbDbf MyFile(&x);
	xbNdx MyIndex(&MyFile);

	if (MyFile.OpenDatabase(filename)) {
		std::cout << "Could not open file " << filename << "\n";
		return 0;
	}
	if (MyIndex.OpenIndex(filename2)) {
		std::cout << "Could not open index file " << filename2 << "\n";
		return 0;
	}

	xbShort rc = MyIndex.ReIndex(showStatus);
	printf("\n");
	if (rc != XB_NO_ERROR) {
		std::cout << "\nError reindexing index ==> " << filename2;
		std::cout << " Return Code = " << rc;
	}

	/* or
   if(( rc = MyFile.RebuildAllIndicis()) != XB_NO_ERROR )
   {
	  std::cout << "\nError reindexing...";
	  std::cout << "\nReturn Code = " << rc;
   }
	*/
	MyFile.CloseDatabase(); /* close database */

	return 0;
}
