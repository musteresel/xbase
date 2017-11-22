#include <xbase64/xbase64.h>
#include <xbase64/xbase64.cpp>
#include <xbase64/xbdate.cpp>
#include <xbase64/xbdbf.cpp>
#include <xbase64/xbexp.cpp>
#include <xbase64/xbexpfnc.cpp>
#include <xbase64/xbexpprc.cpp>
#include <xbase64/xbfields.cpp>
#include <xbase64/xbfile.cpp>
#include <xbase64/xbfilter.cpp>
#include <xbase64/xbindex.cpp>
#include <xbase64/xblock.cpp>
#include <xbase64/xbmemo.cpp>
#include <xbase64/xbndx.cpp>
#include <xbase64/xbntx.cpp>
#include <xbase64/xbstring.cpp>

int main() {
	xbShort lname, fname, birthdate, startdate;
	xbShort amount, sw, f1, f2, f3, f4, m1, rc, z;
	xbFloat f;

	xbXBase x;
	xbDbf MyFile(&x);
	MyFile.AutoLockOff();  //  turn off locking

	char bigBuf[4096];

#undef XB_INDEX_NTX

#ifdef XB_INDEX_NDX
	xbNdx MyIndex1(&MyFile);
	xbNdx MyIndex2(&MyFile);
	xbNdx MyIndex3(&MyFile);
#endif

#ifdef XB_INDEX_NTX
	xbNtx MyIndex4(&MyFile);
	xbNtx MyIndex5(&MyFile);
#endif

	xbDate d;

	if ((rc = MyFile.OpenDatabase("MYFILE.DBF")) != XB_NO_ERROR)
		x.DisplayError(rc);

#ifdef XB_INDEX_NDX
	if ((rc = MyIndex1.OpenIndex("MYINDEX1.NDX")) != XB_NO_ERROR)
		x.DisplayError(rc);
	if ((rc = MyIndex2.OpenIndex("MYINDEX2.NDX")) != XB_NO_ERROR)
		x.DisplayError(rc);
	if ((rc = MyIndex3.OpenIndex("MYINDEX3.NDX")) != XB_NO_ERROR)
		x.DisplayError(rc);
#endif

#ifdef XB_INDEX_NTX
	if ((rc = MyIndex4.OpenIndex("MYINDEX4.NTX")) != XB_NO_ERROR)
		x.DisplayError(rc);
	if ((rc = MyIndex5.OpenIndex("MYINDEX5.NTX")) != XB_NO_ERROR)
		x.DisplayError(rc);
#endif

	fname = MyFile.GetFieldNo("FIRSTNAME");
	lname = MyFile.GetFieldNo("LASTNAME");
	birthdate = MyFile.GetFieldNo("BIRTHDATE");
	startdate = MyFile.GetFieldNo("STARTDATE");
	amount = MyFile.GetFieldNo("AMOUNT");
	sw = MyFile.GetFieldNo("SWITCH");
	f1 = MyFile.GetFieldNo("FLOAT1");
	f2 = MyFile.GetFieldNo("FLOAT2");
	f3 = MyFile.GetFieldNo("FLOAT3");
	f4 = MyFile.GetFieldNo("FLOAT4");
	m1 = MyFile.GetFieldNo("MEMO1");
	z = MyFile.GetFieldNo("ZIPCODE");

	std::cout << "First Name Id = " << fname << std::endl;
	std::cout << "Last Name Id  = " << lname << std::endl;
	std::cout << "Birthdate Id  = " << birthdate << std::endl;
	std::cout << "Startdate Id  = " << startdate << std::endl;
	std::cout << "Amount Id     = " << amount << std::endl;
	std::cout << "Switch Id     = " << sw << std::endl;
	std::cout << "Float 1 Id    = " << f1 << std::endl;
	std::cout << "Float 2 Id    = " << f2 << std::endl;
	std::cout << "Float 3 Id    = " << f3 << std::endl;
	std::cout << "Float 4 Id    = " << f4 << std::endl;
	std::cout << "Zipcode Id    = " << z << std::endl;
#ifdef XB_MEMO_FIELDS
	std::cout << "Memo1 Id      = " << m1 << std::endl << std::endl;
	;
#endif

	/* build record one */
	MyFile.BlankRecord();                    /* blank out the record buffer */
	MyFile.PutField(lname, "Queue");         /* a name */
	MyFile.PutField(fname, "Suzy");          /* a name */
	MyFile.PutField(birthdate, d.Sysdate()); /* a date */
	MyFile.PutField(startdate, "20040506");
	MyFile.PutField(amount, "99.99"); /* an amount */
	MyFile.PutField(sw, "Y");         /* a switch */
	f = 1.466f;
	MyFile.PutFloatField(f1, f);
	MyFile.PutFloatField("FLOAT2", f);
	MyFile.PutField(f3, "1");
	MyFile.PutField(f4, "1");
	MyFile.PutField(z, "76262");

	if ((rc = MyFile.AppendRecord()) != XB_NO_ERROR) /* write it */
		x.DisplayError(rc);

	/* build record two */
	MyFile.BlankRecord();                   /* blank out the record buffer */
	MyFile.PutField(lname, "Bob");          /* a name */
	MyFile.PutField(fname, "Billy");        /* a name */
	MyFile.PutField(birthdate, "19970304"); /* a date */
	MyFile.PutField(startdate, "19970310"); /* a date */
	MyFile.PutField(amount, "88.88");       /* an amount */
	MyFile.PutField(sw, "N");               /* a switch */
	f = -2.1f;
	MyFile.PutFloatField(f1, f);
	MyFile.PutFloatField("FLOAT2", -2.1f);
	MyFile.PutField(f1, "-2.1");
	MyFile.PutField(f2, "-2.1");
	MyFile.PutField(f3, "-2.1");
	MyFile.PutField(f4, "-2.1");
	MyFile.PutField(z, "76261");
#ifdef XB_MEMO_FIELDS
	memset(bigBuf, 0x00, 4096);
	memset(bigBuf, 'a', 596);
	bigBuf[0] = '[';
	strcat(bigBuf, "EOD]");
	MyFile.UpdateMemoData(m1, strlen(bigBuf), bigBuf, XB_LOCK);
#endif
	if ((rc = MyFile.AppendRecord()) != XB_NO_ERROR) /* write it */
		x.DisplayError(rc);
	/* build record three */
	MyFile.BlankRecord();                   /* blank out the record buffer */
	MyFile.PutField(lname, "Slippery");     /* a name */
	MyFile.PutField(fname, "Sam");          /* a name */
	MyFile.PutField(birthdate, "19970406"); /* a date */
	MyFile.PutField(startdate, "19990101"); /* a date */
	MyFile.PutField(amount, "77.77");       /* an amount */
	MyFile.PutField(sw, "T");               /* a switch */
	f = 3.21f;
	MyFile.PutFloatField(f1, f);
	MyFile.PutFloatField("FLOAT2", 3.21f);
	MyFile.PutField(f1, "3.21");
	MyFile.PutField(f2, "3.21");
	MyFile.PutField(f3, "3.21");
	MyFile.PutField(f4, "3.21");
	MyFile.PutField(z, "76263");
#ifdef XB_MEMO_FIELDS
	MyFile.UpdateMemoData(m1, 20, "Sample memo field 3", XB_LOCK);
#endif

	if ((rc = MyFile.AppendRecord()) != XB_NO_ERROR) /* write it */
		x.DisplayError(rc);

	/* build record four */
	MyFile.BlankRecord();                   /* blank out the record buffer */
	MyFile.PutField(lname, "Lucas");        /* a name */
	MyFile.PutField(fname, "George");       /* a name */
	MyFile.PutField(birthdate, "19470406"); /* a date */
	MyFile.PutField(amount, "77.77");       /* an amount */
	MyFile.PutField(sw, "T");               /* a switch */
	f = 4.321f;
	MyFile.PutFloatField(f1, f);
	MyFile.PutFloatField("FLOAT2", 4.321f);
	MyFile.PutField(f1, "4.321");
	MyFile.PutField(f2, "4.321");
	MyFile.PutField(f3, "4.321");
	MyFile.PutField(f4, "4.321");
	MyFile.PutField(z, "76260");
#ifdef XB_MEMO_FIELDS
	MyFile.UpdateMemoData(m1, 20, "Sample memo field 4", XB_LOCK);
#endif
	if ((rc = MyFile.AppendRecord()) != XB_NO_ERROR) /* write it */
		x.DisplayError(rc);

	MyFile.CloseDatabase(); /* close database */
	return 0;
}
