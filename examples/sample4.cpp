#include <xbase64/xbase64.h>

int main() {
	xbShort rc;
	xbXBase x;
	xbDbf MyFile(&x);
	MyFile.AutoLockOff();

#ifdef XB_INDEX_NDX
	xbNdx MyIndex1(&MyFile);
	xbNdx MyIndex2(&MyFile);
	xbNdx MyIndex3(&MyFile);
#endif
#ifdef XB_INDEX_NTX
	xbNtx MyIndex4(&MyFile);
	xbNtx MyIndex5(&MyFile);
#endif

	if ((rc = MyFile.OpenDatabase("MYFILE.DBF")) != XB_NO_ERROR) {
		std::cout << "Error opening file" << std::endl;
		x.DisplayError(rc);
		exit(1);
	}

#ifdef XB_INDEX_NDX
	if ((rc = MyIndex1.OpenIndex("MYINDEX1.NDX")) != XB_NO_ERROR) {
		std::cout << "\nError opening index1" << std::endl;
		x.DisplayError(rc);
		exit(1);
	}

	if ((rc = MyIndex2.OpenIndex("MYINDEX2.NDX")) != XB_NO_ERROR) {
		std::cout << "\nError opening index2" << std::endl;
		x.DisplayError(rc);
		exit(1);
	}

	if ((rc = MyIndex3.OpenIndex("MYINDEX3.NDX")) != XB_NO_ERROR) {
		std::cout << "\nError opening index3" << std::endl;
		x.DisplayError(rc);
		exit(1);
	}

#endif
#ifdef XB_INDEX_NTX
	if ((rc = MyIndex4.OpenIndex("MYINDEX4.NTX")) != XB_NO_ERROR) {
		std::cout << "\nError opening index4" << std::endl;
		x.DisplayError(rc);
		exit(1);
	}
	if ((rc = MyIndex5.OpenIndex("MYINDEX5.NTX")) != XB_NO_ERROR) {
		std::cout << "\nError opening index5" << std::endl;
		x.DisplayError(rc);
		exit(1);
	}
#endif

	std::cout << "Sample GetRecord\n";

	//  MyFile.ExclusiveLock( XB_LOCK ); /* lock the files for our exclusive use
	//  */

	MyFile.GetRecord(2L); /* get the second record */

	MyFile.DeleteRecord(); /* delete it */

	if (MyFile.RecordDeleted())
		std::cout << "Record is deleted..." << std::endl;
	else
		std::cout << "Record is not deleted..." << std::endl;

	/* to undelete a record the following commented code could be used
	  MyFile.UndeleteRecord();
	  if( MyFile.RecordDeleted() )
	     std::cout << "Record is deleted...\n";
	  else
	    std::cout << "Record is not deleted...\n";
	*/

	/* to permanently remove deleted records from the file, pack the database */

	if ((rc = MyFile.PackDatabase(XB_LOCK)) != XB_NO_ERROR) {
		std::cout << "Error packing database" << std::endl;
		x.DisplayError(rc);
	} else
		std::cout << "Database packed." << std::endl;

	//  MyFile.ExclusiveUnlock();         /* unlock the files */
	MyFile.CloseDatabase(); /* close database */
	return 0;
}
