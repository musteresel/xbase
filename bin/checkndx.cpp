/*
    Xbase64 project source code

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

int main(int ac, char ** av) {
#ifdef XBASE_DEBUG
	xbXBase x;
	xbDbf d(&x);
	xbNdx i(&d);
	xbShort rc;

	if (3 != ac) {
		std::cout << "\nUsage: checkndx dbf_file index_file\n";
		return 1;
	}

	if ((rc = d.OpenDatabase(av[1])) != XB_NO_ERROR) {
		std::cout << "\nCould not open file " << av[1] << " rc = " << rc
		          << "\n";
		return 2;
	}

	if ((rc = i.OpenIndex(av[2])) != XB_NO_ERROR) {
		std::cout << "\nCould not open file " << av[2] << " rc = " << rc
		          << "\n";
		return 3;
	}

	std::cout << "\nRunning...\n";
	rc = i.CheckIndexIntegrity(1);
	std::cout << "\nNdx integrity check = " << rc << "\n";

	i.DumpHdrNode(0);

	d.CloseDatabase();
#else
	std::cout << "\nXBASE_DEBUG is not compiled in\n";
#endif
	return 0;
}
