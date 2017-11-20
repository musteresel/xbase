/*  exfilter.cpp

    Xbase project source code

    This program demonstrates the usage of the xbFilter class

    Copyright (C) 1997,2003  Gary A. Kunkel

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

    Contact:

     Email:

       xbase64-dev@lists.sourceforge.net


*/

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
