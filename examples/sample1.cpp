#include <xbase64/xbase64.h>

int main() {
	xbSchema MyRecord[] = {{"FIRSTNAME", XB_CHAR_FLD, 15, 0},
	                       {"LASTNAME", XB_CHAR_FLD, 20, 0},
	                       {"BIRTHDATE", XB_DATE_FLD, 8, 0},
	                       {"STARTDATE", XB_DATE_FLD, 8, 0},
	                       {"AMOUNT", XB_NUMERIC_FLD, 9, 2},
	                       {"SWITCH", XB_LOGICAL_FLD, 1, 0},
	                       {"FLOAT1", XB_FLOAT_FLD, 9, 2},
	                       {"FLOAT2", XB_FLOAT_FLD, 9, 1},
	                       {"FLOAT3", XB_FLOAT_FLD, 9, 2},
	                       {"FLOAT4", XB_FLOAT_FLD, 9, 3},
	                       {"ZIPCODE", XB_NUMERIC_FLD, 5, 0},
#ifdef XB_MEMO_FIELDS
	                       {"MEMO1", XB_MEMO_FLD, 10, 0},
#endif
	                       {"", 0, 0, 0}};

	/* define the classes */
	xbXBase x;        /* initialize xbase  */
	xbDbf MyFile(&x); /* class for table   */

//  Create Dbase style indices
#ifdef XB_INDEX_NDX
	xbNdx MyIndex1(&MyFile); /* class for index 1 */
	xbNdx MyIndex2(&MyFile); /* class for index 2 */
	xbNdx MyIndex3(&MyFile); /* class for index 3 */
#endif

// Create Clipper style indices
#ifdef XB_INDEX_NTX
	xbNtx MyIndex4(&MyFile); /* class for index 4 */
	xbNtx MyIndex5(&MyFile); /* class for index 5 */
#endif

	xbShort rc;
	MyFile.SetVersion(4); /* create dbase IV style files */

	if ((rc = MyFile.CreateDatabase("MYFILE.DBF", MyRecord, XB_OVERLAY)) !=
	    XB_NO_ERROR)
		x.DisplayError(rc);
	else {
#ifdef XB_INDEX_NDX
		/* define a simple index */
		if ((rc = MyIndex1.CreateIndex(
		         "MYINDEX1.NDX", "LASTNAME", XB_NOT_UNIQUE, XB_OVERLAY)) !=
		    XB_NO_ERROR)
			x.DisplayError(rc);
		/* define a multi-field index "LASTNAME            FIRSTNAME" */
		if ((rc = MyIndex2.CreateIndex("MYINDEX2.NDX",
		                               "LASTNAME+FIRSTNAME",
		                               XB_NOT_UNIQUE,
		                               XB_OVERLAY)) != XB_NO_ERROR)
			x.DisplayError(rc);
		/* define a numeric index "ZIPCODE" */
		if ((rc = MyIndex3.CreateIndex(
		         "MYINDEX3.NDX", "ZIPCODE", XB_NOT_UNIQUE, XB_OVERLAY)) !=
		    XB_NO_ERROR)
			x.DisplayError(rc);

#endif
#ifdef XB_INDEX_NTX
		/* define a multi-field index "LASTNAMEFIRSTNAME" */
		if ((rc = MyIndex4.CreateIndex("MYINDEX4.NTX",
		                               "LASTNAME-FIRSTNAME",
		                               XB_NOT_UNIQUE,
		                               XB_OVERLAY)) != XB_NO_ERROR)
			x.DisplayError(rc);
		/* define a numeric index "ZIPCODE" */
		if ((rc = MyIndex5.CreateIndex(
		         "MYINDEX5.NTX", "ZIPCODE", XB_NOT_UNIQUE, XB_OVERLAY)) !=
		    XB_NO_ERROR)
			x.DisplayError(rc);
#endif
	}

	MyFile.CloseDatabase(); /* Close database and associated indexes */
	return 0;
}
