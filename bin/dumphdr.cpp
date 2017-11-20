/*
    This sample program dumps an Xbase header record

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
	xbShort rc;
	xbXBase x;

	if (ac <= 1) {
		std::cout << "\nUsage: dumphdr filename...\n";
		return 1;
	}
	for (int i = 1; i < ac; ++i) {
		char * filename = av[i];
		xbDbf MyFile(&x);

		if ((rc = MyFile.OpenDatabase(filename)) != 0) {
			std::cout << "Could not open file rc = " << rc
			          << " file = " << filename << "\n";
			return 0;
		}
		MyFile.DumpHeader(3);
		MyFile.CloseDatabase();
	}
#else
	std::cout << "\nXBASE_DEBUG is not compiled in\n";
#endif
	return 0;
}
