/*  sample5.cpp

    Xbase64 project source code

    This program demonstrates NDX index usage.  It is not very useful
    if NDX index logic has been disabled

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

      xbase64-devel@lists.sourceforge.net
      xbase64-users@lists.sourceforge.net


     Regular Mail:

       XBase Support
       149C South Main St
       Keller Texas, 76248
       USA

*/

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
