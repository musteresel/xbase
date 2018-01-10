#include <gtest/gtest.h>

#include <xbase64/xbase64.h>

namespace {
	xbString string_date("19701007");
	char char_date[9] = "19611109";

	const xbDate now;

	const std::time_t _time_t = std::time(nullptr);
	struct tm * _tm = localtime(&_time_t);
	int year = _tm->tm_year + 1900;
	int mon = _tm->tm_mon + 1;
	int mday = _tm->tm_mday;
	int wday = _tm->tm_wday;
	int yday = _tm->tm_yday + 1;
}

TEST(xbDate, constructor) {
	ASSERT_NE(xbDate(string_date), xbDate(char_date));
	ASSERT_NE(xbDate(), xbDate(string_date));
	ASSERT_NE(xbDate(), xbDate(char_date));

	ASSERT_EQ(xbDate(string_date), xbDate(string_date));
	ASSERT_EQ(now, now);
}

TEST(xbDate, YearOf) {
	ASSERT_EQ(1970, xbDate(string_date).YearOf());
	ASSERT_EQ(1961, xbDate(char_date).YearOf());
	ASSERT_EQ(year, now.YearOf());
}

TEST(xbDate, MonthOf) {
	ASSERT_EQ(10, xbDate(string_date).MonthOf());
	ASSERT_EQ(11, xbDate(char_date).MonthOf());
	ASSERT_EQ(mon, now.MonthOf());
}

TEST(xbDate, DayOfWEEK) {
	ASSERT_EQ(3, xbDate(string_date).DayOf(XB_FMT_WEEK));
	ASSERT_EQ(4, xbDate(char_date).DayOf(XB_FMT_WEEK));
	ASSERT_EQ(wday, now.DayOf(XB_FMT_WEEK));
}

TEST(xbDate, DayOfMONTH) {
	ASSERT_EQ(7, xbDate(string_date).DayOf(XB_FMT_MONTH));
	ASSERT_EQ(9, xbDate(char_date).DayOf(XB_FMT_MONTH));
	ASSERT_EQ(mday, now.DayOf(XB_FMT_MONTH));
}

TEST(xbDate, DayOfYEAR) {
	ASSERT_EQ(280, xbDate(string_date).DayOf(XB_FMT_YEAR));
	ASSERT_EQ(313, xbDate(char_date).DayOf(XB_FMT_YEAR));
	ASSERT_EQ(yday, now.DayOf(XB_FMT_YEAR));
}

TEST(xbDate, IsLeapYear) {
	ASSERT_TRUE(xbDate("19040101").IsLeapYear());
	ASSERT_TRUE(xbDate("19080101").IsLeapYear());
	ASSERT_TRUE(xbDate("19120101").IsLeapYear());
	ASSERT_TRUE(xbDate("19160101").IsLeapYear());
	ASSERT_TRUE(xbDate("19200101").IsLeapYear());
	ASSERT_TRUE(xbDate("19240101").IsLeapYear());
	ASSERT_TRUE(xbDate("19280101").IsLeapYear());
	ASSERT_TRUE(xbDate("19320101").IsLeapYear());
	ASSERT_TRUE(xbDate("19360101").IsLeapYear());
	ASSERT_TRUE(xbDate("19400101").IsLeapYear());
	ASSERT_TRUE(xbDate("19440101").IsLeapYear());
	ASSERT_TRUE(xbDate("19480101").IsLeapYear());
	ASSERT_TRUE(xbDate("19520101").IsLeapYear());
	ASSERT_TRUE(xbDate("19560101").IsLeapYear());
	ASSERT_TRUE(xbDate("19600101").IsLeapYear());
	ASSERT_TRUE(xbDate("19640101").IsLeapYear());
	ASSERT_TRUE(xbDate("19680101").IsLeapYear());
	ASSERT_TRUE(xbDate("19720101").IsLeapYear());
	ASSERT_TRUE(xbDate("19760101").IsLeapYear());
	ASSERT_TRUE(xbDate("19800101").IsLeapYear());
	ASSERT_TRUE(xbDate("19840101").IsLeapYear());
	ASSERT_TRUE(xbDate("19880101").IsLeapYear());
	ASSERT_TRUE(xbDate("19920101").IsLeapYear());
	ASSERT_TRUE(xbDate("19960101").IsLeapYear());
	ASSERT_TRUE(xbDate("20000101").IsLeapYear());
	ASSERT_TRUE(xbDate("20040101").IsLeapYear());
	ASSERT_TRUE(xbDate("20080101").IsLeapYear());
	ASSERT_TRUE(xbDate("20120101").IsLeapYear());
	ASSERT_TRUE(xbDate("20160101").IsLeapYear());
	ASSERT_TRUE(xbDate("20200101").IsLeapYear());

	ASSERT_FALSE(xbDate("19000101").IsLeapYear());
	ASSERT_FALSE(xbDate("20010101").IsLeapYear());
	ASSERT_FALSE(xbDate("20050101").IsLeapYear());
}

TEST(xbDate, DateIsValid) {
	xbDate d;
	ASSERT_FALSE(d.DateIsValid("19951301"));

	ASSERT_TRUE(d.DateIsValid("19920229"));
	ASSERT_TRUE(d.DateIsValid(char_date));
	ASSERT_TRUE(d.DateIsValid(string_date));
}

TEST(xbDate, JulianDays) {
	ASSERT_EQ(xbDate(string_date).JulianDays(), 683282);
	ASSERT_EQ(xbDate(char_date).JulianDays(), 680028);
	ASSERT_EQ(xbDate("19700101").JulianDays(), 683003);
	ASSERT_EQ(xbDate("19951101").JulianDays() - xbDate("19951001").JulianDays(), 31);
}

TEST(xbDate, CharDayOf) {
	ASSERT_STREQ(xbDate(string_date).CharDayOf(), "Wednesday");
	ASSERT_STREQ(xbDate(char_date).CharDayOf(), "Thursday");
}

TEST(xbDate, CharMonthOf) {
	ASSERT_STREQ(xbDate(string_date).CharMonthOf(), "October");
	ASSERT_STREQ(xbDate(char_date).CharMonthOf(), "November");
}

TEST(xbDate, FormatDate) {
	ASSERT_STREQ(xbDate(string_date).FormatDate("YYDDD"), "70280");
	ASSERT_STREQ(xbDate(string_date).FormatDate("MM/DD/YY"), "10/07/70");
}

TEST(xbDate, LastDayOfMonth) {
	ASSERT_STREQ(xbDate(string_date).LastDayOfMonth(), "19701031");
}

TEST(xbDate, OpEq) {
	ASSERT_EQ(xbDate(string_date), xbDate(string_date));
	ASSERT_NE(xbDate(string_date), xbDate(char_date));
}

TEST(xbDate, OpLt) {
	ASSERT_LT(xbDate(char_date), xbDate(string_date));
	ASSERT_GE(xbDate(string_date), xbDate(string_date));
}

TEST(xbDate, OpLe) {
	ASSERT_LE(xbDate(char_date), xbDate(string_date));
	ASSERT_LE(xbDate(char_date), xbDate(char_date));
	ASSERT_GE(xbDate(string_date), xbDate(string_date));
}

TEST(xbDate, OpGt) {
	ASSERT_GT(xbDate(string_date), xbDate(char_date));
	ASSERT_LE(xbDate(char_date), xbDate(string_date));
}

TEST(xbDate, OpGe) {
	ASSERT_GE(xbDate(string_date), xbDate(char_date));
	ASSERT_GE(xbDate(string_date), xbDate(string_date));
	ASSERT_LE(xbDate(char_date), xbDate(string_date));
}
