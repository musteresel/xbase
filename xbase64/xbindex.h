#ifndef __XB_INDEX_H__
#define __XB_INDEX_H__

#ifdef __GNU_LesserG__
#pragma interface
#endif

#include <string.h>
#include <xbase64/xbase64.h>
/*! \file xbindex.h
 */

#define XB_UNIQUE 1
#define XB_NOT_UNIQUE 0

//! xbIndex class
/*!
 */

class XBDLLEXPORT xbIndex : protected xbFile {
public:
	xbIndex() {}
	xbIndex(xbDbf *);

	virtual ~xbIndex();

	xbShort OpenIndex(const char *);
	xbShort CloseIndex();
	virtual xbShort CreateIndex(const char *,
	                            const char *,
	                            xbShort,
	                            xbShort) = 0;
	virtual xbLong GetTotalNodes() = 0;
	virtual xbULong GetCurDbfRec() = 0;
	virtual xbShort CreateKey(xbShort, xbShort) = 0;
	virtual xbShort GetCurrentKey(char * key) = 0;
	virtual xbShort AddKey(xbLong) = 0;
	virtual xbShort UniqueIndex() = 0;
	virtual xbShort DeleteKey(xbLong) = 0;
	virtual xbShort KeyWasChanged() = 0;
	virtual xbShort FindKey(const char *) = 0;
	virtual xbShort FindKey() = 0;
	virtual xbShort FindKey(xbDouble) = 0;
	virtual xbShort GetNextKey() = 0;
	virtual xbShort GetLastKey() = 0;
	virtual xbShort GetFirstKey() = 0;
	virtual xbShort GetPrevKey() = 0;
	virtual xbShort ReIndex(void (*statusFunc)(xbLong itemNum,
	                                           xbLong numItems) = 0) = 0;
	//  virtual xbShort  KeyExists( char * Key ) { return FindKey( Key, strlen(
	//  Key ), 0 ); }
	virtual xbShort KeyExists(xbDouble) = 0;
	virtual xbShort TouchIndex() { return XB_NO_ERROR; }
	virtual void SetNodeSize(xbShort /*size*/) {}
	virtual xbShort GetNodeSize() { return NodeSize; }
	virtual void GetExpression(char * buf, int len) = 0;
	virtual void Flush();
	virtual const char * GetIxName() { return GetFileName().getData(); }
	xbShort AllocKeyBufs();
	xbBool IsOpen() { return indexfp != NULL; }

#ifdef XBASE_DEBUG
	virtual void DumpHdrNode(xbShort Option) = 0;
	virtual void DumpNodeRec(xbLong) = 0;
	virtual void DumpNodeChain() = 0;
	virtual xbShort CheckIndexIntegrity(xbShort) = 0;
#endif

#ifdef XB_LOCKING_ON
//     xbShort LockIndex( xbShort LockType );
//     virtual xbShort LockIndex( const xbShort, const xbShort );
#else
//     virtual xbShort  LockIndex( const xbShort, const xbShort ) const { return
//     XB_NO_ERROR; }
#endif

protected:
	virtual xbShort GetHeadNode() = 0;
	virtual xbUShort GetKeyLen() = 0;
	virtual const char * GetKeyExpression() = 0;
	virtual void FreeNodesMemory() = 0;

	xbIndex * index;
	xbDbf * dbf;
	xbExpn * IxExp; /* index expression defines keys */
	FILE * indexfp; /* NULL = closed, other = open   */
	//    int       IndexStatus;         /* old - 0 = closed, 1 = open    */
	xbULong CurDbfRec; /* current Dbf record number     */
	char * KeyBuf;     /* work area key buffer          */
	char * KeyBuf2;    /* work area key buffer          */
	xbShort NodeSize;

#ifdef XB_LOCKING_ON
	int LockCnt;      /* current index lock count      */
	int CurLockCount; /* old locking field             */
	int CurLockType;  /* old locking field             */
#endif
};

#endif /* __XB_INDEX_H__ */
