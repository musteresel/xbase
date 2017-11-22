#ifdef __GNU_LesserG__
#pragma implementation "xbfilter.h"
#endif

#ifdef __WIN32__
#include <xbase64/xbwincfg.h>
#else
#include <xbase64/xbconfig.h>
#endif

#include <xbase64/xbase64.h>
//#include <xbase64/xbexcept.h>

/*! \file xbfilter.cpp
 */

#ifdef XB_FILTERS
/************************************************************************/
//! Constructor.
/*!
  \param dbf
  \param index
  \param exp
*/
xbFilter::xbFilter(xbDbf * dbf, xbIndex * index, const char * exp) {
	xbShort rc;
	Status = 0;
	CurFilterRecNo = 0L;
	d = dbf;
	i = index;
	//  e = 0;

	flExpn = new xbExpn(d->xbase);
	if ((rc = flExpn->ParseExpression(exp, d)) != XB_NO_ERROR)
		Status = rc;
	else {
		if (flExpn->GetExpressionResultType() != 'L')
			Status = XB_PARSE_ERROR;
	}
}

/***********************************************************************/
//! Destructor.
/*!
 */
xbFilter::~xbFilter() {
	if (flExpn)
		delete flExpn;
}

/***********************************************************************/
//! Short description.
/*!
 */
xbShort xbFilter::GetFirstFilterRec() {
	xbShort rc;

	if (Status)
		return Status;

	if (i)
		rc = i->GetFirstKey();
	else
		rc = d->GetFirstRecord();

	while (rc == XB_NO_ERROR) {
		if ((rc = flExpn->ProcessExpression()) != XB_NO_ERROR)
			return rc;

		if (flExpn->GetIntResult()) {
			CurFilterRecNo = d->GetCurRecNo();
			return XB_NO_ERROR;
		}
		if (i)
			rc = i->GetNextKey();
		else
			rc = d->GetNextRecord();
	}
	return rc;
}
/***********************************************************************/
//! Short description.
/*!
 */
xbShort xbFilter::GetLastFilterRec() {
	xbShort rc;

	if (Status)
		return Status;

	if (i)
		rc = i->GetLastKey();
	else
		rc = d->GetLastRecord();

	while (rc == XB_NO_ERROR) {
		if ((rc = flExpn->ProcessExpression()) != XB_NO_ERROR)
			return rc;

		if (flExpn->GetIntResult()) {
			CurFilterRecNo = d->GetCurRecNo();
			return XB_NO_ERROR;
		}
		if (i)
			rc = i->GetPrevKey();
		else
			rc = d->GetPrevRecord();
	}
	return rc;
}
/***********************************************************************/
//! Short description.
/*!
 */
xbShort xbFilter::GetNextFilterRec() {
	xbShort rc;

	if (Status)
		return Status;

	if (!CurFilterRecNo)
		return GetFirstFilterRec();

	if (i) {
		rc = i->GetNextKey();
	} else
		rc = d->GetNextRecord();

	while (rc == XB_NO_ERROR) {
		if ((rc = flExpn->ProcessExpression()) != XB_NO_ERROR)
			return rc;

		if (flExpn->GetIntResult()) {
			CurFilterRecNo = d->GetCurRecNo();
			return XB_NO_ERROR;
		}
		if (i)
			rc = i->GetNextKey();
		else
			rc = d->GetNextRecord();
	}
	return rc;
}
/***********************************************************************/
//! Short description.
/*!
 */
xbShort xbFilter::GetPrevFilterRec() {
	xbShort rc;

	if (Status)
		return Status;

	if (!CurFilterRecNo)
		return GetLastFilterRec();

	if (i) {
		rc = i->GetPrevKey();
	} else
		rc = d->GetPrevRecord();

	while (rc == XB_NO_ERROR) {
		if ((rc = flExpn->ProcessExpression()) != XB_NO_ERROR)
			return rc;

		if (flExpn->GetIntResult()) {
			CurFilterRecNo = d->GetCurRecNo();
			return XB_NO_ERROR;
		}
		if (i)
			rc = i->GetPrevKey();
		else
			rc = d->GetPrevRecord();
	}
	return rc;
}
/***********************************************************************/
#endif  // XB_FILTERS_ON
