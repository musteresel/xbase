/*! \file xbfilter.h
 */

#ifndef __XB_FILTER_H__
#define __XB_FILTER_H__

#ifdef __GNU_LesserG__
#pragma interface
#endif

//! xbFilter class
/*!
 */

class XBDLLEXPORT xbFilter {
public:
	xbFilter(xbDbf * dbf, xbIndex * index, const char * expression);
	virtual ~xbFilter();

	xbShort GetFirstFilterRec();
	xbShort GetLastFilterRec();
	xbShort GetNextFilterRec();
	xbShort GetPrevFilterRec();
	xbShort GetStatus() { return Status; }

protected:
	xbULong CurFilterRecNo;
	xbShort Status;
	xbExpn * flExpn;
	xbDbf * d;
	xbIndex * i;
};

#endif
