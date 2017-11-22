#include <xbase64/xbase64.h>

int main() {
	xbShort rc; /* return code */
	xbXBase x;
	xbDbf d(&x);
	d.AutoLockOff();

// dbase indices
#ifdef XB_INDEX_NDX
	xbNdx i1(&d);
	xbNdx i2(&d);
	xbNdx i3(&d);
#endif

// clipper indices
#ifdef XB_INDEX_NTX
	xbNtx i4(&d);
	xbNtx i5(&d);
#endif

	rc = d.OpenDatabase("MYFILE");
	x.DisplayError(rc);

#ifdef XB_INDEX_NDX
	rc = i1.OpenIndex("MYINDEX1");
	std::cout << "OpenIndex 1 - ";
	x.DisplayError(rc);

	rc = i2.OpenIndex("MYINDEX2");
	std::cout << "OpenIndex 2 - ";
	x.DisplayError(rc);

	rc = i3.OpenIndex("MYINDEX3");
	std::cout << "OpenIndex 3 - ";
	x.DisplayError(rc);

#endif

#ifdef XB_INDEX_NTX
	rc = i4.OpenIndex("MYINDEX4");
	std::cout << "OpenIndex 4 - ";
	x.DisplayError(rc);

	rc = i5.OpenIndex("MYINDEX5");
	std::cout << "OpenIndex 5 - ";
	x.DisplayError(rc);
#endif

#ifdef XB_INDEX_NDX
	rc = i1.FindKey("Queue"); /* alpha search   */
	std::cout << "NDX Find alpha key - ";
	x.DisplayError(rc);

	rc = i3.FindKey((xbDouble)76262);
	std::cout << "NDX Find numeric key - ";
	x.DisplayError(rc);
#endif

#ifdef XB_INDEX_NTX
	rc = i4.FindKey("Queue"); /* alpha search */
	std::cout << "NTX Find alpha key - ";
	x.DisplayError(rc);

	// looks like ntx doesn't support numeric keys
	rc = i5.FindKey((xbDouble)76262); /* numeric search */
	std::cout << "NTX Find numeric key - ";
	x.DisplayError(rc);
#endif

#ifdef XB_INDEX_NDX

	rc = i1.GetFirstKey();
	std::cout << "Get first key - ";
	x.DisplayError(rc);

	rc = i1.GetNextKey();
	std::cout << "Get next key - ";
	x.DisplayError(rc);

	rc = i1.GetLastKey();
	std::cout << "Get last key - ";
	x.DisplayError(rc);

	rc = i1.GetPrevKey();
	std::cout << "Get prev key - ";
	x.DisplayError(rc);
#endif

	d.CloseDatabase();
	return 0;
}
