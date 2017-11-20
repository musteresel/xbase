/*  lfiletst.cpp

    Xbase project source code

    This program creates a sample database and multiple indices.
    It tests the 64 bit file support logic.

    Copyright (C) 1997,2003  Gary A Kunkel

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
	xbShort f1, f2, f3, f4, rc;
#ifdef XB_MEMO_FIELDS
	xbShort f5;
#endif
	char charbuf[10];

	xbSchema MyRecord[] = {{"CHARFLD1", XB_CHAR_FLD, 10, 0},
	                       {"NUMFLD1", XB_NUMERIC_FLD, 10, 0},
	                       {"BIGFIELD1", XB_CHAR_FLD, 255, 0},
	                       {"BIGFIELD2", XB_CHAR_FLD, 255, 0},
	                       {"BIGFIELD3", XB_CHAR_FLD, 255, 0},
	                       {"BIGFIELD4", XB_CHAR_FLD, 255, 0},
#ifdef XB_MEMO_FIELDS
	                       {"MEMOFLD", XB_MEMO_FLD, 10, 0},
#endif
	                       {"", 0, 0, 0}};

	/* define the classes */
	xbXBase x;        /* initialize xbase  */
	xbDbf MyFile(&x); /* class for table   */

#ifdef XB_INDEX_NDX
	xbNdx indx1(&MyFile); /* class for ndx index 1 */
#endif

#ifdef XB_INDEX_NTX
	xbNtx intx1(&MyFile); /* class for ntx index 1 */
#endif

#ifndef XBASE_64_BIT
	std::cout << "XBASE_64_BIT support option not compiled into library";
	return 1;
#endif

	std::cout << "Creating test database and indices" << std::endl;
	if ((rc = MyFile.CreateDatabase("LFTEST.DBF", MyRecord, XB_OVERLAY)) !=
	    XB_NO_ERROR)
		std::cout << "Error creating database = " << rc << "\n";
	else {
#ifdef XB_INDEX_NDX
		if ((rc = indx1.CreateIndex(
		         "LFNDX1.NDX", "CHARFLD1", XB_NOT_UNIQUE, XB_OVERLAY)) !=
		    XB_NO_ERROR) {
			std::cout << "Error creating index 1 = " << rc << std::endl;
			exit(1);
		}
#endif

#ifdef XB_INDEX_NTX
		if ((rc = intx1.CreateIndex(
		         "LFNTX1.NTX", "CHARFLD1", XB_NOT_UNIQUE, XB_OVERLAY)) !=
		    XB_NO_ERROR) {
			std::cout << "Error creating index 2 = " << rc << std::endl;
			exit(1);
		}
#endif
	}

	f1 = MyFile.GetFieldNo("CHARFLD1");
	f2 = MyFile.GetFieldNo("NUMFLD1");
	f3 = MyFile.GetFieldNo("BIGFIELD1");
	f4 = MyFile.GetFieldNo("BIGFIELD2");
#ifdef XB_MEMO_FIELDS
	f5 = MyFile.GetFieldNo("MEMOFLD");
#endif

	std::cout << "sizeof( XbOffT ) = " << sizeof(xbOffT) << std::endl;
	std::cout << "sizeof( xbLong ) = " << sizeof(xbLong) << std::endl;
	std::cout << "Populating database and indices with data" << std::endl;
	std::cout << "This will take a while and consume some 20G of disk space"
	          << std::endl;
	std::cout << "<ctrl><C> to kill this program" << std::endl;
	std::cout << ".";
	std::cout.flush();
	for (long i = 0; i < 20000000; i++) {
		if (i % 5000 == 0) {
			std::cout << ".";
			std::cout.flush();
		}
		memset(charbuf, 0x00, 10);
		sprintf(charbuf, "%ld", i);
		MyFile.BlankRecord();
		MyFile.PutField(f1, charbuf);
		MyFile.PutLongField(f2, i);
		MyFile.PutField(f3, charbuf);
		MyFile.PutField(f4, charbuf);
#ifdef XB_MEMO_FIELDS
		MyFile.UpdateMemoData(f5, strlen(charbuf), charbuf, 0);
#endif
		MyFile.AppendRecord();
	}
	std::cout << " Done." << std::endl;
}
