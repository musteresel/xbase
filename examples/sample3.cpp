#include <xbase64/xbase64.h>

int main() {
	char buf[40];
	xbShort rc, i;
	xbShort lname, fname, birthdate, amount, sw, f1, memo;
	char * p;
	xbFloat f;

	xbXBase x;
	xbDbf MyFile(&x);
	MyFile.OpenDatabase("MYFILE.DBF");
	MyFile.AutoLockOff();

	lname = MyFile.GetFieldNo("LASTNAME");
	fname = MyFile.GetFieldNo("FIRSTNAME");
	birthdate = MyFile.GetFieldNo("BIRTHDATE");
	amount = MyFile.GetFieldNo("AMOUNT");
	sw = MyFile.GetFieldNo("SWITCH");
	f1 = MyFile.GetFieldNo("FLOAT1");
	memo = MyFile.GetFieldNo("MEMO1");

	std::cout << "There are " << MyFile.FieldCount() << " fields in the file"
	          << std::endl;
	std::cout << "There are " << MyFile.NoOfRecords() << " records in the file."
	          << std::endl;
	std::cout << "LASTNAME   is type: " << MyFile.GetFieldType(lname)
	          << " length: " << MyFile.GetFieldLen(lname) << std::endl;
	std::cout << "FIRSTNAME  is type: " << MyFile.GetFieldType(fname)
	          << " length: " << MyFile.GetFieldLen(fname) << std::endl;
	std::cout << "BIRTHDATE  is type: " << MyFile.GetFieldType(birthdate)
	          << " length: " << MyFile.GetFieldLen(birthdate) << std::endl;
	std::cout << "AMOUNT     is type: " << MyFile.GetFieldType(amount)
	          << " length: " << MyFile.GetFieldLen(amount) << std::endl;
	std::cout << "SWITCH     is type: " << MyFile.GetFieldType(sw)
	          << " length: " << MyFile.GetFieldLen(sw) << std::endl;
	std::cout << "MEMO1      is type: " << MyFile.GetFieldType(memo)
	          << " length: " << MyFile.GetFieldLen(memo) << std::endl
	          << std::endl;

	std::cout << "Sample GetRecord" << std::endl;
	MyFile.GetRecord(1L);
	MyFile.GetField(lname, buf);
	std::cout << "Name 1 = " << buf << std::endl;
	std::cout << "Name 1 = " << MyFile.GetStringField(lname) << std::endl;

	f = MyFile.GetFloatField(f1);
	std::cout << "FLOAT1 = " << f << std::endl;
	f = MyFile.GetFloatField("FLOAT2");
	std::cout << "FLOAT2 = " << f << std::endl;

	std::cout << "Sample GetRecordBuf" << std::endl;
	p = MyFile.GetRecordBuf(); /* pointer to record buffer */
	for (i = 0; i < 49; i++)
		std::cout << *p++; /* display the buffer */

	std::cout << std::endl << "Loop through forwards..." << std::endl;
	rc = MyFile.GetFirstRecord();
	while (rc == XB_NO_ERROR) {
		MyFile.GetField(lname, buf);
		std::cout << MyFile.GetCurRecNo();
		std::cout << " Name = " << buf << std::endl;
		rc = MyFile.GetNextRecord();
#ifdef XB_MEMO_FIELDS
		if (MyFile.MemoFieldExists(memo))
			std::cout << "Memo field MEMO1 len = "
			          << MyFile.GetMemoFieldLen(memo) << std::endl;
#endif
	}

	std::cout << "Sample PutRecord" << std::endl;
	MyFile.PutField(lname, "Stantonbob");
	MyFile.PutField(lname, "Sally");
	MyFile.PutRecord(MyFile.GetCurRecNo());

	std::cout << "Loop through backwards.." << std::endl;
	rc = MyFile.GetLastRecord();
	while (rc == XB_NO_ERROR) {
		std::cout << "Last Name = " << MyFile.GetStringField(lname)
		          << std::endl;
		std::cout << "Logical Field = " << MyFile.GetLogicalField("SWITCH")
		          << std::endl;
		rc = MyFile.GetPrevRecord();
	}

	std::cout << std::endl;
	MyFile.CloseDatabase(); /* close database */
	return 0;
}
