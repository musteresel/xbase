#include <xbase64/xbase64.h>

int main() {
#if defined(XB_FILTERS)
	xbShort rc;
	xbXBase x;
	xbDbf d(&x);
	xbNdx i(&d);

	std::cout << "exfilter program executing" << std::endl;

	if ((rc = d.OpenDatabase("MYFILE.DBF")) != XB_NO_ERROR) {
		std::cout << "Error opening database" << std::endl;
		return 1;
	}

	if ((rc = i.OpenIndex("MYINDEX1.NDX")) != XB_NO_ERROR) {
		std::cout << "Error opening index" << std::endl;
		return 2;
	}

	xbFilter f1(&d, 0, "FLOAT1>1");
	/* use filter 1 w/o index */
	rc = f1.GetFirstFilterRec();
	while (rc == XB_NO_ERROR) {
		std::cout << "Filter 1 Found Record " << d.GetCurRecNo() << std::endl;
		rc = f1.GetNextFilterRec();
	}
	xbFilter f2(&d, &i, "FLOAT1>1");
	/* use filter 2 w/ index */
	rc = f2.GetLastFilterRec();

	while (rc == XB_NO_ERROR) {
		std::cout << "Filter 2 Found Record " << d.GetCurRecNo() << std::endl;
		rc = f2.GetPrevFilterRec();
	}
	d.CloseDatabase();
#else
	std::cout << "XB_FILTERS not compiled into library" << std::endl;
#endif

	return 0;
}
