/*
    Xbase64 project source code

    This program extracts data from a dbf data file and puts it in
    a comma delimited output file,  suitable for input into an awk or
    perl script

    This program excludes all memo fields

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

/*************************************************************************/
void Usage();
void Usage() {
	std::cout
	    << "\nUsage: dbfxtrct -iDATABASE.DBF -sINDEX.N[TD]X -f -F -dMM/DD/YY\n";
	std::cout
	    << "\nWhere DATABASE.DBF is the name of the database file to dump\n";
	std::cout << "INDEX.NTX or .NDX is an optional index sort paramater\n";
	std::cout << "-f  optional field name list in first record\n";
	std::cout << "-F  optional field name and attributes in first record\n";
	std::cout
	    << "MM/DD/YY is an optional output date format for any date fields\n";
	std::cout
	    << "\nThis program creates output suitable for awk and perl scripts\n";
	std::cout << "\nThis program does not support memo fields (yet).\n";
}
/*************************************************************************/
int main(int ac, char ** av) {
	xbXBase x;
	xbDbf d(&x);
	xbShort rc, FieldOption = 0;
	xbIndex * ix = 0;
	xbNdx z(&d);

	char * dbfname = NULL;
	char * ixname = NULL;
	char * p;
	char buf[200];
	xbExpn exp(&x);

	/*  Get the input paramaters

	    -i  input datafile name
	    -s  optional sort index name
	    -f  optional field names in record one
	    -F  optional field names and attributes in record one
	    -d  date format
	*/
	for (int i = 1; i < ac; i++) {
		p = av[i];
		if (*p != '-') {
			std::cout << "Invalid paramater " << *p << std::endl;
			Usage();
			return 1;
		}
		p++;
		if (*p == 'i')
			dbfname = ++p;
		else if (*p == 's')
			ixname = ++p;
		else if (*p == 'f')
			FieldOption = 1;
		else if (*p == 'F')
			FieldOption = 2;
		else if (*p == 'd')
			x.SetDefaultDateFormat(++p);
		else {
			std::cout << "Invalid paramater " << *p << std::endl;
			Usage();
			return 1;
		}
	}

	/* if missing params, display a usage message and exit */

	if (!dbfname) {
		Usage();
		return 1;
	}

	/*  open the database file */

	if ((rc = d.OpenDatabase(dbfname)) != XB_NO_ERROR) {
		std::cout << "\nCould not open file " << dbfname << " rc = " << rc
		          << "\n";
		return 2;
	}

	/*  if an index was specified, open the index file */

	if (ixname) {
#ifdef XB_INDEX_NTX
		if (strstr(ixname, "NTX"))
			ix = new xbNtx(&d);
#endif

#ifdef XB_INDEX_NDX
		if (strstr(ixname, "NDX"))
			ix = new xbNdx(&d);
#endif
		if (!ix) {
			std::cout << "Unknown index type. .NTX and .NDX index file support "
			             "only\n";
			return 3;
		}
		if ((rc = ix->OpenIndex(ixname)) != XB_NO_ERROR) {
			std::cout << "\nCould not open index " << ixname << " rc = " << rc
			          << "\n";
			return 4;
		}
	}

	/*  if -f or -F paramater, dump the header information */
	if (FieldOption) {
		for (xbLong l = 0; l < d.FieldCount(); l++) {
			if (l)
				std::cout << ",";
			std::cout << d.GetFieldName(l);
			if (FieldOption == 2) {
				std::cout << "|" << d.GetFieldType(l) << "|"
				          << d.GetFieldLen(l);
				std::cout << "|" << d.GetFieldDecimal(l);
			}
		}
		std::cout << std::endl;
	}

	/*  if an index used, then loop thru each record, based on index, else
	    dump in dbf sort order */
	if (ixname)
		rc = ix->GetFirstKey();
	else
		rc = d.GetFirstRecord();

	while (rc == XB_NO_ERROR) {
		for (xbLong l = 0; l < d.FieldCount(); l++) {
			if (l)
				std::cout << ",";
			strcpy(buf, exp.LTRIM(d.GetStringField(l)));
			if (d.GetFieldType(l) == 'D')
				std::cout << exp.DTOC(buf);
			else
				std::cout << exp.TRIM(buf);
		}
		if (ixname)
			rc = ix->GetNextKey();
		else
			rc = d.GetNextRecord();
		std::cout << std::endl;
	}

	/*  close everything */
	d.CloseDatabase();
	return 0;
}
