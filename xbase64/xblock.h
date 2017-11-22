#ifndef __XB_XBLOCK_H__
#define __XB_XBLOCK_H__

#ifdef __GNU_LesserG__
#pragma interface
#endif

#ifdef XB_LOCKING_ON

//! xbLock class
/*!
 */

class XBDLLEXPORT xbLock {
public:
	xbLock(xbDbf * dbf);
	virtual ~xbLock();
	virtual xbShort LockTableHeader(xbShort LockType) = 0;
	virtual xbShort LockTable(xbShort LockType) = 0;
	virtual xbShort LockRecord(xbShort LockType, xbULong RecNo, xbOffT len) = 0;
	virtual xbShort LockMemo(xbShort LockType) = 0;
	virtual xbShort LockIndex(xbShort LockType) = 0;
	virtual xbShort UnlockAll() = 0;
	virtual xbShort LockInit() { return XB_NO_ERROR; }

protected:
	xbDbf * dbf;
	xbShort HdrLockCnt;
	xbShort TableLockCnt;
	xbShort MemoLockCnt;
	xbShort IndexLockCnt;
	xbShort LockFile(int fn, xbShort LockType, xbOffT lockLen);
};

class XBDLLEXPORT xbaseLock : xbLock {
public:
	xbaseLock(xbDbf * pdbf);
	virtual ~xbaseLock() {}
	virtual xbShort LockTableHeader(xbShort LockType);
	virtual xbShort LockTable(xbShort LockType);
	virtual xbShort LockRecord(xbShort LockType, xbULong RecNo, xbOffT len);
	virtual xbShort LockMemo(xbShort LockType);
	virtual xbShort LockIndex(xbShort LockType);
	virtual xbShort UnlockAll();
	virtual xbShort LockInit();

private:
	FILE * lfh; /* lock file handle */
};

class XBDLLEXPORT dbaseLock : xbLock {
public:
	dbaseLock(xbDbf * pdbf);
	virtual ~dbaseLock() {}
	virtual xbShort LockTableHeader(xbShort LockType);
	virtual xbShort LockTable(xbShort LockType);
	virtual xbShort LockRecord(xbShort LockType, xbULong RecNo, xbOffT len);
	virtual xbShort LockMemo(xbShort LockType);
	virtual xbShort LockIndex(xbShort LockType);
	virtual xbShort UnlockAll();
};

class XBDLLEXPORT clipperLock : xbLock {
public:
	clipperLock(xbDbf * pdbf);
	virtual ~clipperLock() {}
	virtual xbShort LockTableHeader(xbShort LockType);
	virtual xbShort LockTable(xbShort LockType);
	virtual xbShort LockRecord(xbShort LockType, xbULong RecNo, xbOffT len);
	virtual xbShort LockMemo(xbShort LockType);
	virtual xbShort LockIndex(xbShort LockType);
	virtual xbShort UnlockAll();
};

class XBDLLEXPORT foxproLock : xbLock {
public:
	foxproLock(xbDbf * pdbf);
	virtual ~foxproLock() {}
	virtual xbShort LockTableHeader(xbShort LockType);
	virtual xbShort LockTable(xbShort LockType);
	virtual xbShort LockRecord(xbShort LockType, xbULong RecNo, xbOffT len);
	virtual xbShort LockMemo(xbShort LockType);
	virtual xbShort LockIndex(xbShort LockType);
	virtual xbShort UnlockAll();
};

class XBDLLEXPORT noLock : xbLock {
public:
	noLock(xbDbf * pdbf) : xbLock(pdbf){};
	virtual ~noLock() {}
	virtual xbShort LockTableHeader(xbShort LockType) { return XB_NO_ERROR; }
	virtual xbShort LockTable(xbShort LockType) { return XB_NO_ERROR; }
	virtual xbShort LockRecord(xbShort LockType, xbULong RecNo) {
		return XB_NO_ERROR;
	}
	virtual xbShort LockMemo(xbShort LockType) { return XB_NO_ERROR; }
	virtual xbShort LockIndex(xbShort LockType) { return XB_NO_ERROR; }
	virtual xbShort UnlockAll() { return XB_NO_ERROR; }
};

#endif  // XB_LOCKING_ON
#endif  // __XB_XBLOCK_H__
