#include <xbase64/xbase64.h>

// next lines are helpful for debugging purposes
/*
#include <xbase64/xbase64.cpp>
#include <xbase64/xbcdx.cpp>
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
*/

xbXBase x;
xbDbf d(&x);
xbIndex * ix;

#ifdef XB_FILTERS
xbFilter * xbf;
#endif

class MyClass {
public:
	MyClass(){};
	void OpenFile();
	void CloseFile();
	void ConvertDatabase();
	void ReindexDatabase();
	void PackDatabase();
	void ZapDatabase();
	void DeleteMemoField();
	void UpdateMemoField();
	void ShowFieldInfo(int);
	void ShowFieldData();
	void UpdateFieldData();
	void PutRecord();
	void GetRecord();
	void DumpDbtHeader();
	void BlankRecord();
	void FindMemoBlocks();
	void GetMemoBlocks();
	void FileStats();
	void MainMenu();
	void FileMenu();
	void RecordMenu();
	void FieldMenu();
	void IndexMenu();
	void LockingMenu();
	void DebugMenu();
	void OpenIndex();
	void CloseIndex();
	void FindKey();
	void GetFirstKey();
	void GetLastKey();
	void GetNextKey();
	void GetPrevKey();
	void DumpIndexNodes();
	void ShowLockInfo();
	void SetRetryCount();
	void SetDefaultLockMode();
	void SetTableLockMode();
	void LockDbf();
	void UnlockDbf();
	void LockRecord();
	void UnlockRecord();
	void LockMemoFile(xbShort);
	void LockIndexFile(xbShort);
	void CreateNewIndex();
	void ProcessExpression();
	void FilterMenu();
	void SetFilter();
	void FirstFilterRec();
	void NextFilterRec();
	void PrevFilterRec();
	void LastFilterRec();
};
/************************************************************************/
#ifdef XB_FILTERS
void MyClass::FilterMenu() {
	int option = 0;

	while (option != 99) {
		std::cout << std::endl << std::endl << "Filter Menu" << std::endl;
		std::cout << "1  - Set Filter Expression" << std::endl;
		std::cout << "2  - Get First Filter Record" << std::endl;
		std::cout << "3  - Get Next Filter Record" << std::endl;
		std::cout << "4  - Get Previous Filter Record" << std::endl;
		std::cout << "5  - Get Last Filter Record" << std::endl;
		std::cout << "99 - Exit Menu" << std::endl;
		std::cin >> option;
		switch (option) {
		case 1:
			SetFilter();
			break;
		case 2:
			FirstFilterRec();
			break;
		case 3:
			NextFilterRec();
			break;
		case 4:
			PrevFilterRec();
			break;
		case 5:
			LastFilterRec();
			break;
		case 99:
			break;
		default:
			std::cout << "Invalid option" << std::endl;
			break;
		}
	}
}
/************************************************************************/
void MyClass::SetFilter() {
	char Expression[512];
	memset(Expression, 0x00, 512);
	while (!strlen(Expression)) {
		std::cout << "Enter filter expression (like AMOUNT<5)" << std::endl;
		fgets(Expression, sizeof(Expression), stdin);
	}
	if (xbf)
		delete xbf;

	xbf = new xbFilter(&d, 0, Expression);

	if (xbf->GetStatus())
		x.DisplayError(xbf->GetStatus());
	else
		std::cout << "Filter initialized" << std::endl;
}
/************************************************************************/
void MyClass::FirstFilterRec() {
	xbShort rc;
	if (!xbf)
		SetFilter();
	rc = xbf->GetFirstFilterRec();
	if (rc) {
		x.DisplayError(rc);
		return;
	}
	std::cout << "Record: " << d.GetCurRecNo() << std::endl;
	for (int i = 0; i < d.FieldCount() && i < 3; i++)
		printf("%-10s = %s\n", d.GetFieldName(i), d.GetStringField(i));
}
/************************************************************************/
void MyClass::NextFilterRec() {
	xbShort rc;
	if (!xbf)
		SetFilter();
	rc = xbf->GetNextFilterRec();
	if (rc) {
		x.DisplayError(rc);
		return;
	}
	std::cout << "Record: " << d.GetCurRecNo() << std::endl;
	for (int i = 0; i < d.FieldCount() && i < 3; i++)
		printf("%-10s = %s\n", d.GetFieldName(i), d.GetStringField(i));
}
/************************************************************************/
void MyClass::PrevFilterRec() {
	xbShort rc;
	if (!xbf)
		SetFilter();
	rc = xbf->GetPrevFilterRec();
	if (rc) {
		x.DisplayError(rc);
		return;
	}
	std::cout << "Record: " << d.GetCurRecNo() << std::endl;
	for (int i = 0; i < d.FieldCount() && i < 3; i++)
		printf("%-10s = %s\n", d.GetFieldName(i), d.GetStringField(i));
}
/************************************************************************/
void MyClass::LastFilterRec() {
	xbShort rc;
	if (!xbf)
		SetFilter();
	rc = xbf->GetLastFilterRec();
	if (rc) {
		x.DisplayError(rc);
		return;
	}
	std::cout << "Record: " << d.GetCurRecNo() << std::endl;
	for (int i = 0; i < d.FieldCount() && i < 3; i++)
		printf("%-10s = %s\n", d.GetFieldName(i), d.GetStringField(i));
}
#endif  // XB_FILTERS
/************************************************************************/
#ifdef XB_EXPRESSIONS
void MyClass::ProcessExpression() {
	char exprsn[256];
	char type;
	xbExpn * exp;  // expression
	xbShort rc;
	int debug = 0;
	memset(exprsn, 0x00, 256);

	std::cout << "Enter expression string or HELP" << std::endl;

	while (!strstr(exprsn, "QUIT") && !strstr(exprsn, "quit")) {
		std::cout << ">";
		fgets(exprsn, sizeof(exprsn), stdin);

		if (strstr(exprsn, "HELP") || strstr(exprsn, "help")) {
			std::cout << "** Command Help ***" << std::endl << std::endl;
			std::cout << "HELP  - This help screen" << std::endl;
			std::cout << "QUIT  - Exit the function" << std::endl;
#ifdef XBASE_DEBUG
			std::cout << "DEBUG - Toggle debug mode on/off" << std::endl;
#endif
			std::cout << "\nExamples expressions:" << std::endl;
			std::cout << "  5+5  or 5-2/7  or FUNC(op1,op2)" << std::endl;
			std::cout << "\nRecognized functions:" << std::endl;
			xbString s;
			xbShort i = 0;
			exp = new xbExpn(&x);
			s = exp->GetValidFuncName(i++);
			while (s.len()) {
				std::cout << s << "\t";
				s = exp->GetValidFuncName(i++);
			}

			delete exp;
			std::cout << "\n\nSee documentation for more expression info"
			          << std::endl
			          << std::endl;
		}

		else if (strstr(exprsn, "DEBUG") || strstr(exprsn, "debug")) {
			if (debug) {
				std::cout << "Debug mode toggled off" << std::endl;
				debug = 0;
			} else {
				std::cout << "Debug mode toggled on" << std::endl;
				debug = 1;
			}
		}

		else if (!strstr(exprsn, "QUIT") && !strstr(exprsn, "quit")) {
			exp = new xbExpn(&x);
			if ((rc = exp->ParseExpression(exprsn, &d)) != 0) {
				std::cout << "Error while parsing" << std::endl;
				x.DisplayError(rc);
			}

			else {
				if (debug) {
					exp->DumpExpressionTree(1);
					std::cout << "Expression tree dumped to file xbase64.log"
					          << std::endl;
				}

				if ((rc = exp->ProcessExpression()) != 0) {
					std::cout << "Error in processing " << std::endl;
					x.DisplayError(rc);
				} else {
					type = exp->GetExpressionResultType();

					std::cout << "Result Type = [" << type << "]" << std::endl;
					std::cout << "Result Data = [";
					switch (type) {
					case 'C':
					case 'D':
						std::cout << exp->GetStringResult() << "]" << std::endl;
						break;
					case 'N':
						std::cout << exp->GetDoubleResult() << "]" << std::endl;
						break;
					case 'L':
						std::cout << exp->GetIntResult() << "]" << std::endl;
						break;
					default:
						std::cout << "Unknown result type]" << std::endl;
						break;
					}
				}
				delete exp;
			}
		}
	}
}
#endif  // XB_EXPRESSIONS
/************************************************************************/
#ifdef XBASE_DEBUG
void MyClass::DumpIndexNodes() {
	xbLong NodeCnt = ix->GetTotalNodes();
	std::cout << "For NDX indices, output placed in xbase.log" << std::endl;
	std::cout << "total nodes = " << NodeCnt << std::endl;
	ix->DumpHdrNode(1);
	if (NodeCnt > 1)
		for (xbLong l = 1L; l <= NodeCnt - 1; l++)
			ix->DumpNodeRec(l);
}
#endif
/************************************************************************/
void MyClass::OpenIndex() {
	int rc;
	char Filename[51];

	if (d.GetDbfStatus() == XB_CLOSED) {
		std::cout << "No open database" << std::endl;
		return;
	}
	if (ix) {
		std::cout << "Index already opened" << std::endl;
		return;
	}

	std::cout << "Enter index name: ";
	std::cin >> Filename;
	if (strstr(Filename, "NDX") || strstr(Filename, "ndx")) {
		ix = new xbNdx(&d);
		rc = ix->OpenIndex(Filename);
	} else if (strstr(Filename, "NTX") || strstr(Filename, "ntx")) {
		ix = new xbNtx(&d);
		rc = ix->OpenIndex(Filename);
	} else {
		std::cout << "Invalid index name. Needs file extension. index.ndx or "
		             "index.ntx"
		          << std::endl;
		return;
	}
	x.DisplayError(rc);
	//  std::cout << "Return code " << rc << std::endl;
}
/************************************************************************/
void MyClass::FindKey() {
	if (!ix) {
		std::cout << "No open index" << std::endl;
		return;
	}

	char KeyBuf[101];
	memset(KeyBuf, 0x00, 101);
	std::cout << "This function only works for character keys (so far).."
	          << std::endl;
	std::cout << "Enter search key:" << std::endl;
	std::cin >> KeyBuf;
	x.DisplayError(ix->FindKey(KeyBuf));
}
/************************************************************************/
void MyClass::GetNextKey() {
	if (!ix)
		std::cout << "No open index" << std::endl;
	else
		x.DisplayError(ix->GetNextKey());
}
/************************************************************************/
void MyClass::GetPrevKey() {
	if (!ix)
		std::cout << "No open index" << std::endl;
	else
		x.DisplayError(ix->GetPrevKey());
}
/************************************************************************/
void MyClass::GetFirstKey() {
	if (!ix)
		std::cout << "No open index" << std::endl;
	else
		x.DisplayError(ix->GetFirstKey());
}
/************************************************************************/
void MyClass::GetLastKey() {
	if (!ix)
		std::cout << "No open index" << std::endl;
	else
		x.DisplayError(ix->GetLastKey());
}
/************************************************************************/
void MyClass::CloseIndex() {
	if (!ix) {
		std::cout << "No open index" << std::endl;
		return;
	}
	x.DisplayError(ix->CloseIndex());
	delete ix;
	ix = 0;
}
/************************************************************************/
/* stats */
void MyClass::FileStats() {
	if (d.GetDbfStatus() == XB_CLOSED) {
		std::cout << "No open database" << std::endl;
		return;
	}
	std::cout << "Database name       = " << d.GetDbfName() << std::endl;
	std::cout << "Number of records   = " << d.NoOfRecords() << std::endl;
	std::cout << "Physical no of recs = " << d.PhysicalNoOfRecords()
	          << std::endl;
	std::cout << "Number of fields    = " << d.FieldCount() << std::endl;
	std::cout << "Database Status     = ";
	switch (d.GetDbfStatus()) {
	case 0:
		std::cout << "XB_CLOSED" << std::endl;
		break;
	case 1:
		std::cout << "XB_OPEN" << std::endl;
		break;
	case 2:
		std::cout << "XB_UPDATED" << std::endl;
		break;
	default:
		std::cout << std::endl;
		break;
	}
	std::cout << "Record Length       = " << d.GetRecordLen() << std::endl;
#ifdef XB_MEMO_FIELDS
	std::cout << "Memo Fields Present = ";
	switch (d.MemoFieldsPresent()) {
	case 0:
		std::cout << "No " << std::endl;
		break;
	case 1:
		std::cout << "Yes" << std::endl;
		std::cout << "Memofile name       = " << d.GetDbtName() << std::endl;
		break;
	default:
		std::cout << std::endl;
		break;
	}
#endif
	std::cout << "Current Record No   = " << d.GetCurRecNo() << std::endl;
	std::cout << "Autolock status     = " << d.GetAutoLock() << std::endl;
	std::cout << "Real Delete status  = " << d.GetRealDelete() << std::endl;
	std::cout << "Index Count         = " << d.IndexCount() << std::endl;
}
/************************************************************************/
/* open database */
void MyClass::OpenFile() {
	int rc;
	char filename[50];
	std::cout << "Enter database file (.dbf) name: ";
	std::cin >> filename;

	rc = d.OpenDatabase(filename);
	x.DisplayError(rc);
}
/************************************************************************/
/* open database */
void MyClass::PackDatabase() {
	x.DisplayError(d.PackDatabase(0, 0, 0));
}
/************************************************************************/
/* open database */
void MyClass::ZapDatabase() {
	x.DisplayError(d.Zap(0));
}
/************************************************************************/
/* close database */
void MyClass::CloseFile() {
	int rc;
	rc = d.CloseDatabase();
	x.DisplayError(rc);
}
/************************************************************************/
/* convert database */
void MyClass::ConvertDatabase() {
	int rc;
	xbShort FieldNo;
	xbLong len, FieldCnt;
	xbDbf d2(&x);
	char * MemoFieldBuf = NULL;
	xbLong MemoFieldLen = 0L;

	std::cout << "Warning - check your results!!" << std::endl << std::endl;

	char filename[50];
	std::cout << "Enter database file name to convert to: ";
	std::cin >> filename;

	if ((rc = d2.OpenDatabase(filename)) != XB_NO_ERROR) {
		std::cout << "Error " << rc << " opening database" << std::endl;
		return;
	}

	rc = d.GetFirstRecord();
	FieldCnt = d.FieldCount();
	std::cout << "Database has " << FieldCnt << " fields to convert"
	          << std::endl;
	while (rc == XB_NO_ERROR) {
		d2.BlankRecord();
		for (xbShort i = 0; i < FieldCnt; i++) {
			if ((FieldNo = d2.GetFieldNo(d.GetFieldName(i))) == -1)
				std::cout << "Error converting field " << d.GetFieldName(i)
				          << std::endl;
			else {
				if (d.GetFieldType(i) != d2.GetFieldType(FieldNo))
					std::cout << "Error - different field types "
					          << d.GetFieldName(i);
				else {
					if (d.GetFieldType(i) == 'M') {
#ifdef XB_MEMO_FIELDS
						len = d.GetMemoFieldLen(i);
						if (len > MemoFieldLen) {
							if (MemoFieldLen > 0)
								delete MemoFieldBuf;
							MemoFieldBuf = new char[len];
							MemoFieldLen = len;
						}
						d.GetMemoField(i, len, MemoFieldBuf, XB_LOCK);
						d2.UpdateMemoData(FieldNo, len, MemoFieldBuf, XB_LOCK);
#else
						std::cout << "Memo fields not converted XB_MEMO_FIELDS "
						             "not compiled in\n";
#endif
					} else {
						if (d.GetFieldType(i) == 'N') {
							std::cout << "const code compile prob..."
							          << std::endl;

							//                d2.PutField( FieldNo, x.LTRIM(
							//                d.GetField( i )));
						} else
							d2.PutField(FieldNo, d.GetField(i));
					}
				}
			}
		}
		rc = d.GetNextRecord();
		d2.AppendRecord();
	}
	if (MemoFieldLen > 0)
		delete MemoFieldBuf;
	d2.CloseDatabase();
}
/************************************************************************/
void MyClass::ShowFieldInfo(int option) {
	FILE * out;
	xbString dbfName = d.GetDbfName();
	if (option) {
		if ((out = fopen("xbase64.dmp", "w")) == NULL) {
			std::cout << "File could not be opened" << std::endl;
			getchar();
		} else {
			fprintf(out, "Table Name = %s\n\n", dbfName.getData());
			fprintf(out, "Number   Name            Type      Len  Decs\n");
			for (int i = 0; i < d.FieldCount(); i++)
				fprintf(out,
				        "%3d     %-10s         %c     %5d   %d\n",
				        i + 1,
				        d.GetFieldName(i),
				        d.GetFieldType(i),
				        d.GetFieldLen(i),
				        d.GetFieldDecimal(i));
		}
		fclose(out);
	} else {
		printf("Table Name = %s\n", dbfName.getData());
		std::cout << "Number   Name            Type      Len  Decs"
		          << std::endl;
		for (int i = 0; i < d.FieldCount(); i++) {
			printf("%3d     %-10s         %c     %5d   %d\n",
			       i + 1,
			       d.GetFieldName(i),
			       d.GetFieldType(i),
			       d.GetFieldLen(i),
			       d.GetFieldDecimal(i));
			if (((i + 1) % 15) == 0) {
				std::cout << "Press a key to continue" << std::endl;
				getchar();
				std::cout << "Number   Name        Type  Len  Decs"
				          << std::endl;
			}
		}
	}
	std::cout << "Press a key to continue" << std::endl;
	getchar();
}
/************************************************************************/
void MyClass::ShowFieldData() {
	int done = 0;

	if (d.GetCurRecNo() == 0L) {
		d.GetRecord(1L);
	}

	while (!done) {
		std::cout << "Record: " << d.GetCurRecNo() << std::endl;
		std::cout << "FieldName    Data" << std::endl;
		std::cout << "=========    ====" << std::endl;
		if (d.RecordDeleted())
			std::cout << "Record is deleted" << std::endl;
		for (int i = 0; i < d.FieldCount(); i++) {
			printf("%-10s = %s\n", d.GetFieldName(i), d.GetStringField(i));
			if (((i + 1) % 15) == 0) {
				std::cout << "Press a key to continue" << std::endl;
				getchar();
				std::cout << " Name        Data" << std::endl;
			}
		}
		std::cout << "Press 'N' for next record or any other key to exit"
		          << std::endl;
		if (toupper(getchar()) == 'N') {
			d.GetRecord(d.GetCurRecNo() + 1L);
			getchar();
		} else
			done++;
	}
}
/************************************************************************/
void MyClass::UpdateFieldData() {
	char dbuf[100];
	int rc, fn;
	std::cout << "Enter Field Number to update (first field is 0): "
	          << std::endl;
	std::cin >> fn;
	std::cout << "Enter Field Data" << std::endl;
	std::cin >> dbuf;
	rc = d.PutField(fn, dbuf);
	x.DisplayError(rc);
}
/************************************************************************/
/* open database */
void MyClass::ReindexDatabase() {
	xbNdx n(&d);
	int rc;
	char filename[50];
	std::cout << "Enter index file name: ";
	std::cin >> filename;

	if ((rc = n.OpenIndex(filename)) != XB_NO_ERROR) {
		x.DisplayError(rc);
		return;
	}
	x.DisplayError(n.ReIndex());
}
/************************************************************************/
void MyClass::GetRecord() {
	xbLong RecNo;
	std::cout << "Enter record number: ";
	std::cin >> RecNo;

	x.DisplayError(d.GetRecord(RecNo));
}
/************************************************************************/
void MyClass::UpdateMemoField() {
#ifdef XB_MEMO_FIELDS
	xbShort fn, rc;
	xbLong len;
	char bufchar[2];
	char * buf;

	std::cout << "Enter Field Number: " << std::endl;
	std::cin >> fn;
	if (fn < 0 || fn > d.FieldCount()) {
		std::cout << "Invalid Field Number" << std::endl;
		return;
	}
	if (d.GetFieldType(fn) != 'M') {
		std::cout << "Field " << fn << " is not a memo field" << std::endl;
		std::cout << "Field Name = " << d.GetFieldName(fn) << " type= ";
		std::cout << d.GetFieldType(fn) << std::endl;
		return;
	}
	std::cout << "Enter length of memo data:" << std::endl;
	std::cin >> len;

	std::cout << "Enter character to populate memo data:" << std::endl;
	std::cin >> bufchar;

	buf = new char[len];
	memset(buf, bufchar[0], len);

	rc = d.UpdateMemoData(fn, len, buf, XB_LOCK);
	std::cout << "Return Code = " << rc << std::endl;
#else
	std::cout << "\nXB_MEMO_FIELDS is not compiled in\n";
#endif
}
/************************************************************************/
void MyClass::DeleteMemoField() {
#ifdef XB_MEMO_FIELDS
	xbShort fn, rc;
	std::cout << "Enter Field Number: " << std::endl;
	std::cin >> fn;
	if (fn < 0 || fn > d.FieldCount()) {
		std::cout << "Invalid Field Number" << std::endl;
		return;
	}
	if (d.GetFieldType(fn) != 'M') {
		std::cout << "Field " << fn << " is not a memo field" << std::endl;
		std::cout << "Field Name = " << d.GetFieldName(fn) << " type= ";
		std::cout << d.GetFieldType(fn) << std::endl;
		return;
	}
	rc = d.UpdateMemoData(fn, 0, 0, XB_LOCK);
	x.DisplayError(rc);
#else
	std::cout << "\nXB_MEMO_FIELDS is not compiled in\n";
#endif
}
/************************************************************************/
#ifdef XBASE_DEBUG
void MyClass::DumpDbtHeader() {
	int rc;

#ifdef XB_MEMO_FIELDS
#ifdef XBASE_DEBUG

	/* - This is used to peek in the file for debugging purposes
	     probably not to useful for anything else - Gary
	*/

	rc = d.DumpMemoFreeChain();
	x.DisplayError(rc);

#else
	std::cout << "\nXBASE_DEBUG is not compiled in\n";
#endif
#else
	std::cout << "\nXB_MEMO_FIELDS is not compiled in\n";
#endif
}
/************************************************************************/
void MyClass::GetMemoBlocks() {
#ifdef XB_MEMO_FIELDS
	xbLong BlocksNeeded, Location, PrevNode;
	int rc;

	std::cout << "Enter number of blocks: " << std::endl;
	std::cin >> BlocksNeeded;
	std::cout << "Enter starting location: " << std::endl;
	std::cin >> Location;
	std::cout << "Enter previous node: " << std::endl;
	std::cin >> PrevNode;
	rc = d.GetBlockSetFromChain(BlocksNeeded, Location, PrevNode);
	x.DisplayError(rc);

#else
	std::cout << "\nXB_MEMO_FIELDS is not compiled in\n";
#endif
}
/************************************************************************/
void MyClass::CreateNewIndex() {
	char IndexName[128];
	char KeyExpression[500];
	char Unique[25];
	xbShort uniqueSw = 0;
	xbShort rc;

	if (ix) {
		std::cout << "Program only supports one open index at a time"
		          << std::endl;
		std::cout << "Looking for volunteer to change that fact" << std::endl;
		return;
	}
	memset(IndexName, 0x00, 128);
	memset(KeyExpression, 0x00, 500);
	memset(Unique, 0x00, 25);
	std::cout << "This function creates a new index for an open table"
	          << std::endl;
	std::cout << "If the index already exists, it will be overlaid"
	          << std::endl;
	while (!strlen(IndexName) ||
	       (!strstr(IndexName, ".ndx") && !strstr(IndexName, ".ntx"))) {
		std::cout << "Enter index name (include .ntx or .ndx extension)"
		          << std::endl;
		std::cin >> IndexName;
		for (int i = 0; i < (int)strlen(IndexName); i++)
			IndexName[i] = tolower(IndexName[i]);
	}
	while (Unique[0] != 'U' && Unique[0] != 'N') {
		std::cout << "Enter U)nique or N)on unique" << std::endl;
		std::cin >> Unique;
		if (Unique[0] == 'U')
			uniqueSw++;
	}
	while (!strlen(KeyExpression)) {
		std::cout << "Enter key expression" << std::endl;
		std::cin >> KeyExpression;
	}
	if (strstr(IndexName, "ndx")) {
		ix = new xbNdx(&d);
		rc = ix->CreateIndex(IndexName, KeyExpression, uniqueSw, 1);
	} else if (strstr(IndexName, "ntx")) {
		ix = new xbNtx(&d);
		rc = ix->CreateIndex(IndexName, KeyExpression, uniqueSw, 1);
	}
	if (rc) {
		x.DisplayError(rc);
		ix->CloseIndex();
		ix = NULL;
		return;
	}
	std::cout << IndexName << " created. Loading data.." << std::endl;
	rc = ix->ReIndex();
	if (rc) {
		x.DisplayError(rc);
		return;
	}
	std::cout << "Index loaded successfully" << std::endl;
	return;
}
/************************************************************************/
void MyClass::FindMemoBlocks() {
#ifdef XB_MEMO_FIELDS
	xbLong BlocksNeeded, Location, PrevNode;
	int rc;

	std::cout << "Enter number of blocks: " << std::endl;
	std::cin >> BlocksNeeded;
	rc = d.FindBlockSetInChain(BlocksNeeded, 0, Location, PrevNode);
	std::cout << "Return code = " << rc << std::endl;
	std::cout << "Location = " << Location << std::endl;
	std::cout << "Previous Node = " << PrevNode << std::endl;
#else
	std::cout << "\nXB_MEMO_FIELDS is not compiled in\n";
#endif
}
#endif  // XBASE_DEBUG
/************************************************************************/
void MyClass::IndexMenu() {
	int option = 0;

	while (option != 99) {
		std::cout << std::endl
		          << std::endl
		          << "NDX and NTX Index Menu" << std::endl;
		std::cout << "This program only supports one open index at a time"
		          << std::endl;
		std::cout << "1  - Open Index" << std::endl;
		std::cout << "2  - Create New Index" << std::endl;
		if (ix) {
			std::cout << "3  - Find Key" << std::endl;
			std::cout << "4  - Get First Key" << std::endl;
			std::cout << "5  - Get Last Key" << std::endl;
			std::cout << "6  - Get Previous Key" << std::endl;
			std::cout << "7  - Get Next Key" << std::endl;
			std::cout << "8  - Close Index" << std::endl;
			std::cout << "9  - Check Index Integrity" << std::endl;
		}
		std::cout << "99 - Exit Menu" << std::endl;
		std::cin >> option;
		switch (option) {
		case 1:
			OpenIndex();
			break;
		case 2:
			CreateNewIndex();
			break;
		case 3:
			FindKey();
			break;
		case 4:
			GetFirstKey();
			break;
		case 5:
			GetLastKey();
			break;
		case 6:
			GetPrevKey();
			break;
		case 7:
			GetNextKey();
			break;
		case 8:
			CloseIndex();
			break;
		case 9:
			x.DisplayError(ix->CheckIndexIntegrity(1));
			break;
		case 99:
			break;
		default:
			std::cout << "Invalid option" << std::endl;
			break;
		}
	}
}
/************************************************************************/
#ifdef XBASE_DEBUG
void MyClass::DebugMenu() {
	int option = 0;

	while (option != 99) {
		std::cout << std::endl << std::endl << "Debug Menu" << std::endl;
		std::cout << "1 - Dislay DBT Header" << std::endl;
		std::cout << "2 - Find Memo Blocks" << std::endl;
		std::cout << "3 - Get Memo Blocks" << std::endl;
		std::cout << "4 - Dump index node chains to file xbase.dmp"
		          << std::endl;
		std::cout << "5 - Dump index node chain" << std::endl;
		std::cout << "99 - Exit Menu" << std::endl;
		std::cin >> option;
		switch (option) {
		case 1:
			DumpDbtHeader();
			break;
		case 2:
			FindMemoBlocks();
			break;
		case 3:
			GetMemoBlocks();
			break;
		case 4:
			DumpIndexNodes();
			break;
		case 5:
			ix->DumpNodeChain();
			break;
		case 99:
			break;
		default:
			std::cout << "Invalid option" << std::endl;
			break;
		}
	}
}
#endif  //  XBASE_DEBUG

	/************************************************************************/

#ifdef XB_LOCKING_ON

void MyClass::LockDbf() {
	std::cout << "Locking table" << std::endl;
	//  rc = d.LockTable( XB_LOCK );
	//  x.DisplayError( rc );
	std::cout << "temporarily out of service" << std::endl;
}
/************************************************************************/

void MyClass::UnlockDbf() {
	std::cout << "Unlocking table" << std::endl;
	//  rc = d.LockTable( XB_UNLOCK );
	//  x.DisplayError( rc );

	std::cout << "temporarily out of service" << std::endl;
}

/************************************************************************/

void MyClass::LockRecord() {
	xbULong RecNo;
	xbULong RecCnt;

	std::cout << "Enter start record number to lock" << std::endl;
	std::cin >> RecNo;
	std::cout << "Enter number of records to lock" << std::endl;
	std::cin >> RecCnt;

	//  rc = d.LockRecord( XB_LOCK, RecNo, RecCnt );
	//  x.DisplayError( rc );

	std::cout << "temporarily out of service" << std::endl;
}
/************************************************************************/
void MyClass::UnlockRecord() {
	xbULong RecNo;
	xbULong RecCnt;
	std::cout << "Enter start record number to unlock" << std::endl;
	std::cin >> RecNo;
	std::cout << "Enter number of records to unlock" << std::endl;
	std::cin >> RecCnt;
	//  rc = d.LockRecord( XB_UNLOCK, RecNo, RecCnt );
	//  x.DisplayError( rc );

	std::cout << "temporarily out of service" << std::endl;
}
/************************************************************************/
void MyClass::ShowLockInfo() {
	std::cout << "Retry Count (in seconds)  => " << x.GetLockRetryCount()
	          << std::endl;
	//  std::cout << "No of table locks         => " << d.GetTableLockCnt()   <<
	//  std::endl;

#ifdef XB_MEMO_FIELDS
	//  std::cout << "Memo locks                => " << d.GetMemoLockCnt()    <<
	//  std::endl;
#endif

	std::cout << "Current default lock mode => ";
	switch (x.GetLockMode()) {
	case XB_SINGLE_USER_MODE:
		std::cout << "XB_SINGLE_USER_MODE" << std::endl;
		break;
	case XB_XBASE_LOCK_MODE:
		std::cout << "XB_XBASE_LOCK_MODE" << std::endl;
		break;
	case XB_DBASE5_LOCK_MODE:
		std::cout << "XB_DBASE5_LOCK_MODE" << std::endl;
		break;
	case XB_CLIPPER5_LOCK_MODE:
		std::cout << "XB_CLIPPER5_LOCK_MODE" << std::endl;
		break;
	case XB_FOXPRO3_LOCK_MODE:
		std::cout << "XB_FOXPRO3_LOCK_MODE" << std::endl;
		break;
	default:
		std::cout << "Unknown lock mode" << std::endl;
		break;
	}

	std::cout << "Current table lock mode   => ";
	switch (d.GetLockMode()) {
	case XB_SINGLE_USER_MODE:
		std::cout << "XB_SINGLE_USER_MODE" << std::endl;
		break;
	case XB_XBASE_LOCK_MODE:
		std::cout << "XB_XBASE_LOCK_MODE" << std::endl;
		break;
	case XB_DBASE5_LOCK_MODE:
		std::cout << "XB_DBASE5_LOCK_MODE" << std::endl;
		break;
	case XB_CLIPPER5_LOCK_MODE:
		std::cout << "XB_CLIPPER5_LOCK_MODE" << std::endl;
		break;
	case XB_FOXPRO3_LOCK_MODE:
		std::cout << "XB_FOXPRO3_LOCK_MODE" << std::endl;
		break;
	default:
		std::cout << "Unknown lock mode" << std::endl;
		break;
	}
}

/************************************************************************/

void MyClass::SetDefaultLockMode() {
	xbShort option;

	std::cout << std::endl << std::endl;
	std::cout << "Default Lock Mode Selection" << std::endl;
	std::cout << "1  - XB_SINGLE_USER_MODE" << std::endl;
	std::cout << "2  - XB_XBASE_LOCK_MODE" << std::endl;
	std::cout << "3  - XB_DBASE5_LOCK_MODE" << std::endl;
	std::cout << "4  - XB_CLIPPER5_LOCK_MODE" << std::endl;
	std::cout << "5  - XB_FOXPRO3_LOCK_MODE" << std::endl;
	std::cout << "99 - Exit Menu" << std::endl;
	std::cin >> option;

	switch (option) {
	case 1:
		x.SetLockMode(XB_SINGLE_USER_MODE);
		break;
	case 2:
		x.SetLockMode(XB_XBASE_LOCK_MODE);
		break;
	case 3:
		x.SetLockMode(XB_DBASE5_LOCK_MODE);
		break;
	case 4:
		x.SetLockMode(XB_CLIPPER5_LOCK_MODE);
		break;
	case 5:
		x.SetLockMode(XB_FOXPRO3_LOCK_MODE);
		break;
	case 99:
		break;
	}
}

/************************************************************************/

void MyClass::SetTableLockMode() {
	xbShort option;

	std::cout << std::endl << std::endl;
	std::cout << "Table Lock Mode Selection" << std::endl;
	std::cout << "1  - XB_SINGLE_USER_MODE" << std::endl;
	std::cout << "2  - XB_XBASE_LOCK_MODE" << std::endl;
	std::cout << "3  - XB_DBASE5_LOCK_MODE" << std::endl;
	std::cout << "4  - XB_CLIPPER5_LOCK_MODE" << std::endl;
	std::cout << "5  - XB_FOXPRO3_LOCK_MODE" << std::endl;
	std::cout << "99 - Exit Menu" << std::endl;
	std::cin >> option;

	switch (option) {
	case 1:
		d.SetLockMode(XB_SINGLE_USER_MODE);
		break;
	case 2:
		d.SetLockMode(XB_XBASE_LOCK_MODE);
		break;
	case 3:
		d.SetLockMode(XB_DBASE5_LOCK_MODE);
		break;
	case 4:
		d.SetLockMode(XB_CLIPPER5_LOCK_MODE);
		break;
	case 5:
		d.SetLockMode(XB_FOXPRO3_LOCK_MODE);
		break;
	case 99:
		break;
	}
}

/************************************************************************/

void MyClass::SetRetryCount() {
	xbShort retryCnt;
	std::cout << "Enter new Retry Count " << std::endl;
	std::cin >> retryCnt;
	x.SetLockRetryCount(retryCnt);
}

/************************************************************************/
#ifdef XB_MEMO_FIELDS

void MyClass::LockMemoFile(xbShort /*LockType*/) {
	//  rc = d.LockMemoFile( LockType );
	//  x.DisplayError( rc );
	std::cout << "no memo locking here" << std::endl;
}

#endif

/************************************************************************/

void MyClass::LockIndexFile(xbShort /*LockType*/) {
	if (ix) {
		//    rc = ix->LockIndex( LockType );
		//    x.DisplayError( rc );

		std::cout << "temporarily out of service" << std::endl;
	} else
		std::cout << "No open index" << std::endl;
}

#endif
/************************************************************************/
void MyClass::PutRecord() {
	xbLong l;
	std::cout << "Enter Record number for PutRecord()" << std::endl;
	std::cin >> l;
	int rc = d.PutRecord(l);
	x.DisplayError(rc);
}
/************************************************************************/
void MyClass::FieldMenu() {
	int option = 0;

	while (option != 99) {
		std::cout << std::endl << std::endl << "Field Menu" << std::endl;
		std::cout << "1  - Delete Memo Field" << std::endl;
		std::cout << "2  - Update Memo Field" << std::endl;
		std::cout << "3  - Show Field Info" << std::endl;
		std::cout << "4  - Dump Field Info to file xbase64.dmp" << std::endl;
		std::cout << "5  - Show Field Data" << std::endl;
		std::cout << "6  - Update Field Data" << std::endl;
		std::cout << "99 - Exit Menu" << std::endl;
		std::cin >> option;
		switch (option) {
		case 1:
			DeleteMemoField();
			break;
		case 2:
			UpdateMemoField();
			break;
		case 3:
			ShowFieldInfo(0);
			break;
		case 4:
			ShowFieldInfo(1);
			break;
		case 5:
			ShowFieldData();
			break;
		case 6:
			UpdateFieldData();
			break;
		case 99:
			break;
		default:
			std::cout << "Function not available" << std::endl;
			break;
		}
	}
}
/************************************************************************/
void MyClass::RecordMenu() {
	int option = 0;
	std::cout << "Record Menu" << std::endl;
	while (option != 99) {
		std::cout << std::endl << std::endl << "Record Menu" << std::endl;
		std::cout << "1  - Get Record" << std::endl;
		std::cout << "2  - Blank Record" << std::endl;
		std::cout << "3  - Append Record" << std::endl;
		std::cout << "4  - Put Record" << std::endl;
		std::cout << "5  - Delete Record" << std::endl;
		std::cout << "6  - Undelete Record" << std::endl;
		std::cout << "99 - Exit Menu" << std::endl;
		std::cin >> option;
		switch (option) {
		case 1:
			GetRecord();
			break;
		case 2:
			x.DisplayError(d.BlankRecord());
			break;
		case 3:
			x.DisplayError(d.AppendRecord());
			break;
		case 4:
			x.DisplayError(d.PutRecord());
			break;
		case 5:
			x.DisplayError(d.DeleteRecord());
			break;
		case 6:
			x.DisplayError(d.UndeleteRecord());
			break;
		case 99:
			break;
		default:
			std::cout << "Invalid option" << std::endl;
			break;
		}
	}
}
/************************************************************************/
void MyClass::FileMenu() {
	int option = 0;

	while (option != 99) {
		std::cout << std::endl << std::endl << "File Menu" << std::endl;
		std::cout << "1  - Open File" << std::endl;
		std::cout << "2  - Close File" << std::endl;
		std::cout << "3  - File Stats" << std::endl;
		std::cout << "4  - Convert Database" << std::endl;
		std::cout << "5  - Reindex Database" << std::endl;
		std::cout << "6  - Pack Database" << std::endl;
		std::cout << "7  - Zap Database" << std::endl;
		std::cout << "99 - Exit Menu" << std::endl;
		std::cin >> option;

		switch (option) {
		case 1:
			OpenFile();
			break;
		case 2:
			CloseFile();
			break;
		case 3:
			FileStats();
			break;
		case 4:
			ConvertDatabase();
			break;
		case 5:
			ReindexDatabase();
			break;
		case 6:
			PackDatabase();
			break;
		case 7:
			ZapDatabase();
			break;
		case 99:
			break;
		default:
			std::cout << "Invalid Option" << std::endl;
		}
	}
}
	/************************************************************************/

#ifdef XB_LOCKING_ON
void MyClass::LockingMenu() {
	int option = 0;

	while (option != 99) {
		std::cout << std::endl << std::endl << "Locking Menu" << std::endl;
		std::cout << "1  - Display lock info" << std::endl;
		std::cout << "2  - Set retry count" << std::endl;
		std::cout << "3  - Set default lock mode" << std::endl;
		std::cout << "4  - Set table lock mode" << std::endl;
		std::cout << "5  - Lock table (dbf file)" << std::endl;
		std::cout << "6  - Unlock table (dbf file)" << std::endl;
		std::cout << "7  - Lock Record" << std::endl;
		std::cout << "8  - Unlock Record" << std::endl;
		std::cout << "9  - Lock Memo File" << std::endl;
		std::cout << "10 - Unlock Memo File" << std::endl;
		std::cout << "11 - Lock Index File" << std::endl;
		std::cout << "12 - Unlock Index File" << std::endl;

		std::cout << "99 - Exit Menu" << std::endl;
		std::cin >> option;

		switch (option) {
		case 1:
			ShowLockInfo();
			break;
		case 2:
			SetRetryCount();
			break;
		case 3:
			SetDefaultLockMode();
			break;
		case 4:
			SetTableLockMode();
			break;
		case 5:
			LockDbf();
			break;
		case 6:
			UnlockDbf();
			break;
		case 7:
			LockRecord();
			break;
		case 8:
			UnlockRecord();
			break;
		case 9:
			LockMemoFile(XB_LOCK);
			break;
		case 10:
			LockMemoFile(XB_UNLOCK);
			break;
		case 11:
			LockIndexFile(XB_LOCK);
			break;
		case 12:
			LockIndexFile(XB_UNLOCK);
			break;

		case 99:
			break;
		default:
			std::cout << "Invalid Option" << std::endl;
		}
	}
}
#endif

/************************************************************************/

void MyClass::MainMenu() {
	int option = 0;
	std::cout << std::endl << std::endl << "XBase Utility Program";
	while (option != 99) {
		std::cout << std::endl << std::endl << "Main Menu" << std::endl;
		std::cout << "1  - File Menu" << std::endl;
		std::cout << "2  - Record Menu" << std::endl;
		std::cout << "3  - Field Menu" << std::endl;
		std::cout << "4  - Index Menu" << std::endl;
#ifdef XB_LOCKING_ON
		std::cout << "5  - Locking Menu" << std::endl;
#endif
#ifdef XBASE_DEBUG
		std::cout << "6  - Debug Menu" << std::endl;
#endif
#ifdef XB_EXPRESSIONS
		std::cout << "7  - Expression Testor" << std::endl;
#endif
#ifdef XB_FILTERS
		std::cout << "8  - Filter Menu" << std::endl;
#endif
		std::cout << "99 - Exit" << std::endl;
		std::cin >> option;
		switch (option) {
		case 1:
			FileMenu();
			break;
		case 2:
			RecordMenu();
			break;
		case 3:
			FieldMenu();
			break;
		case 4:
			IndexMenu();
			break;
#ifdef XB_LOCKING_ON
		case 5:
			LockingMenu();
			break;
#endif
#ifdef XBASE_DEBUG
		case 6:
			DebugMenu();
			break;
#endif
#ifdef XB_EXPRESSIONS
		case 7:
			ProcessExpression();
			break;
#endif
#ifdef XB_FILTERS
		case 8:
			FilterMenu();
			break;
#endif

		case 99:
			std::cout << "Bye!! - Thanks for using XBase64" << std::endl;
			break;
		default:
			std::cout << "Invalid function" << std::endl;
			break;
		}
	}
}

/************************************************************************/

int main(int, char **) {
	MyClass m;
	m.MainMenu();
	return 0;
}
