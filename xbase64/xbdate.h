#ifndef __XB_XBDATE_H__
#define __XB_XBDATE_H__

#ifdef __GNU_LesserG__
#pragma interface
#endif

#ifdef __WIN32__
#include <xbase64/xbwincfg.h>
#else
#include <xbase64/xbconfig.h>
#endif

#include <xbase64/xbstring.h>

#define XB_FMT_WEEK 1
#define XB_FMT_MONTH 2
#define XB_FMT_YEAR 3

//! xbDate class
/*!
 */

class XBDLLEXPORT xbDate {
public:
	xbDate();
	xbDate(const char * Date8);
	xbDate(const xbString & Date8);
	virtual ~xbDate();

	//! Short description.
	/*!
	 */
	const xbString & GetDate() const { return cDate8; };
	//! Short description.
	/*!
	 */
	xbString & GetDate() { return cDate8; };
	//! Short description.
	/*!
	 */
	const xbString & GetFormattedDate() const { return fDate; };
	//! Short description.
	/*!
	 */
	xbString & GetFormattedDate() { return fDate; };

	int SetDate(const char * Date8);
	//! Short description.
	/*!
	 */
	int SetDate(const xbString & Date8) {
		return SetDate((const char *)Date8);
	};

	long JulianDays(const char * Date8) const;
	//! Short description.
	/*!
	 */
	long JulianDays(const xbString & Date8) const {
		return JulianDays((const char *)Date8);
	};
	//! Short description.
	/*!
	 */
	long JulianDays() const { return JulianDays((const char *)cDate8); };

	int YearOf(const char * Date8) const;
	//! Short description.
	/*!
	 */
	int YearOf(const xbString & Date8) const {
		return YearOf((const char *)Date8);
	};
	//! Short description.
	/*!
	 */
	int YearOf() const { return YearOf((const char *)cDate8); };

	//! Short description.
	/*!
	 */
	int CenturyOf(const char * Date8) const;

	int MonthOf(const char * Date8) const;
	//! Short description.
	/*!
	 */
	int MonthOf(const xbString & Date8) const {
		return MonthOf((const char *)Date8);
	};
	//! Short description.
	/*!
	 */
	int MonthOf() const { return MonthOf((const char *)cDate8); };

	int DayOf(int Format, const char * Date8) const;
	//! Short description.
	/*!
	 */
	int DayOf(int Format, const xbString & Date8) const {
		return DayOf(Format, (const char *)Date8);
	};
	//! Short description.
	/*!
	 */
	int DayOf(int Format) const { return DayOf(Format, (const char *)cDate8); };

	int IsLeapYear(const char * Date8) const;
	//! Short description.
	/*!
	 */
	int IsLeapYear(const xbString & Date8) const {
		return IsLeapYear((const char *)Date8);
	};
	//! Short description.
	/*!
	 */
	int IsLeapYear() const { return IsLeapYear((const char *)cDate8); };

	//! Short description.
	/*!
	 */
	int CalcRollingCenturyForYear(int) const;

	int DateIsValid(const char * Date8) const;
	//! Short description.
	/*!
	 */
	int DateIsValid(const xbString & Date8) const {
		return DateIsValid((const char *)Date8);
	};

	xbString & LastDayOfMonth(const char * Date8);
	//! Short description.
	/*!
	 */
	xbString & LastDayOfMonth(const xbString & Date8) {
		return LastDayOfMonth((const char *)Date8);
	};
	//! Short description.
	/*!
	 */
	xbString & LastDayOfMonth() {
		return LastDayOfMonth((const char *)cDate8);
	};

	xbString & Sysdate();
	xbString & JulToDate8(long);

	//! Short description.
	/*!
	 */
	xbString & FormatCTODdate(const char * indate);

	//! Short description.
	/*!
	 */
	xbString & FormatDate(const char * Format, const char * Date8);
	//! Short description.
	/*!
	 */
	xbString & FormatDate(const xbString & Format, const char * Date8) {
		return FormatDate((const char *)Format, Date8);
	};
	//! Short description.
	/*!
	 */
	xbString & FormatDate(const char * Format, const xbString & Date8) {
		return FormatDate(Format, (const char *)Date8);
	};
	//! Short description.
	/*!
	 */
	xbString & FormatDate(const xbString & Format, const xbString & Date8) {
		return FormatDate((const char *)Format, (const char *)Date8);
	};
	//! Short description.
	/*!
	 */
	xbString & FormatDate(const char * Format) {
		return FormatDate((const char *)Format, (const char *)cDate8);
	};
	//! Short description.
	/*!
	 */
	xbString & FormatDate(const xbString & Format) {
		return FormatDate((const char *)Format, (const char *)cDate8);
	};

	xbString & CharDayOf(const char * Date8);
	//! Short description.
	/*!
	 */
	xbString & CharDayOf(const xbString & Date8) {
		return CharDayOf((const char *)Date8);
	};
	//! Short description.
	/*!
	 */
	xbString & CharDayOf() { return CharDayOf((const char *)cDate8); };

	xbString & CharMonthOf(const char * Date8);
	//! Short description.
	/*!
	 */
	xbString & CharMonthOf(const xbString & Date8) {
		return CharMonthOf((const char *)Date8);
	};
	//! Short description.
	/*!
	 */
	xbString & CharMonthOf() { return CharMonthOf((const char *)cDate8); };

	xbString & operator+=(int);
	xbString & operator-=(int);
	xbString & operator++(int); /* post increment */
	xbString & operator--(int); /* post increment */
	xbString & operator+(int);
	xbString & operator-(int);
	long operator-(const xbDate &) const;
	int operator==(const xbDate &) const;
	int operator!=(const xbDate &) const;
	int operator<(const xbDate &) const;
	int operator>(const xbDate &) const;
	int operator<=(const xbDate &) const;
	int operator>=(const xbDate &) const;

protected:
	void SetDateTables();
	xbString cDate8; /* CCYYMMDD date format */
	xbString fDate;  /* other date format    */
	static int AggregatedDaysInMonths[2][13];
	static int DaysInMonths[2][13];
};

#endif  // __XB_XBDATE_H__
