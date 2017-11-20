/*
    Xbase64 project source code

    This program is used for debugging the memo file logic

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
#ifdef XB_MEMO_FIELDS
	xbXBase x;

	if (ac <= 1) {
		std::cout << "\nUsage: dumpdbt filename...\n";
		return 1;
	}

	for (int i = 1; i < ac; ++i) {
		char * filename = av[i];
		xbDbf dbf(&x);

		if (dbf.OpenDatabase(filename)) {
			std::cout << "\nCant open input file " << filename;
			return 2;
		}

		std::cout << "\n\nFree Block Chain....";
#ifdef XBASE_DEBUG
		dbf.DumpMemoFreeChain();
		std::cout
		    << "\nEnd of free block chain\n***********************************";
#else
		std::cout << "\nXBASE_DEBUG is not compiled in\n";
#endif

		/* lock the memo file */
#ifdef XB_LOCKING_ON
//    dbf.LockMemoFile( XB_LOCK );
#endif /* XB_LOCKING_ON */

		if (!dbf.MemoFieldsPresent()) {
			std::cout << "No memo fields exist in " << filename << std::endl;
		} else {
			xbLong BufSize = 0L;
			char * Buf = NULL;
			for (xbLong l = 1; l <= dbf.NoOfRecords(); l++) {
				dbf.GetRecord(l);
				std::cout << "\nRecord # " << dbf.GetCurRecNo();
				for (int j = 0; j < dbf.FieldCount(); j++) {
					if (dbf.GetFieldType(j) == 'M') {
						int len = dbf.GetMemoFieldLen(j);
						std::cout << "\nMemo field " << dbf.GetFieldName(j)
						          << " length = " << len;
						std::cout << " Head Block = " << dbf.GetLongField(j)
						          << "\n";
						if (len > BufSize) {
							if (BufSize)
								free(Buf);
							if ((Buf = ((char *)malloc(len))) == NULL)
								return XB_NO_MEMORY;
							BufSize = len;
						}
						dbf.GetMemoField(j, len, Buf, XB_LOCK);
						for (int i = 0; i < len; i++)
							std::cout << Buf[i];
					}
				}
			}

				/* unlock the memo file */
#ifdef XB_LOCKING_ON
//      dbf.LockMemoFile( XB_UNLOCK );
#endif /* XB_LOCKING_ON */

			std::cout << "\n";
			dbf.CloseDatabase();
		}
	}
#else
	std::cout << "\nXB_MEMO_FIELDS is not compiled in\n";
#endif
	return 0;
}
