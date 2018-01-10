#include <gtest/gtest.h>

#include <xbase64/xbase64.h>

struct Exp : public ::testing::Test {
	virtual void SetUp() override {
		x = new xbXBase();
		d = new xbDbf(x);
		e = new xbExpn(x);

		xbSchema MyRecord[] = {
			{"FLOAT1", XB_FLOAT_FLD, 9, 2},
			{"DATE1", XB_DATE_FLD, 8, 0},
			{"DATE2", XB_DATE_FLD, 8, 0},
			{"", 0, 0, 0},
		};
		d->CreateDatabase("TEST", MyRecord, XB_OVERLAY);
		d->PutFloatField("FLOAT1", 5);
		d->PutField("DATE1", "19990110");
		d->PutField("DATE2", "19990120");
		d->AppendRecord();
	}
	virtual void TearDown() override {
		d->CloseDatabase(1);

		delete e;
		delete d;
		delete x;
	}

	void do_exp(const char * exp) {
		xbShort rc = 0;
		if ((rc = e->ParseExpression(exp, d)) != 0) {
			FAIL() << "Parse error " << rc << " in expression " << exp;
		}
		if ((rc = e->ProcessExpression()) != 0) {
			FAIL() << "Error " << rc << " processing expression " << exp;
		}
	}

	xbXBase * x;
	xbDbf * d;
	xbExpn * e;
};

#define TSTR(name, exp, res) \
	TEST_F(Exp, name) { \
		do_exp(exp); \
		ASSERT_EQ(e->GetExpressionResultType(), 'C'); \
		ASSERT_STREQ(e->GetStringResult(), res); \
	}
#define TDOU(name, exp, res) \
	TEST_F(Exp, name) { \
		do_exp(exp); \
		ASSERT_EQ(e->GetExpressionResultType(), 'N'); \
		ASSERT_NEAR(e->GetDoubleResult(), res, 1e-10); \
	}
#define TLON(name, exp, res) \
	TEST_F(Exp, name) { \
		do_exp(exp); \
		ASSERT_EQ(e->GetExpressionResultType(), 'N'); \
		ASSERT_EQ(e->GetDoubleResult(), res); \
	}
#define TLOG(name, exp, res) \
	TEST_F(Exp, name) { \
		do_exp(exp); \
		ASSERT_EQ(e->GetExpressionResultType(), 'L'); \
		ASSERT_EQ(e->GetIntResult(), res); \
	}

TSTR(CDOW, "CDOW( \"20000101\" )", "Saturday ")
TSTR(CHR, "CHR( 101 )", "e")
TSTR(CMONTH, "CMONTH( \"20000101\" )", "January  ")
TSTR(DATE, "DATE()", e->DATE())
TSTR(DTOC, "DTOC( \"20000101\" )", "01/01/00")
TSTR(DTOS, "DTOS( \"20000101\" )", "20000101")
TSTR(LEFT, "LEFT( \"STRING\", 3 )", "STR")
TSTR(LTRIM, "LTRIM( \"   xxxxxx\" )", "xxxxxx")
TSTR(LOWER, "LOWER( \"AAAA\" )", "aaaa")
TSTR(REPLICATE, "REPLICATE( \"abc\", 3 )", "abcabcabc")
TSTR(RTRIM1, "RTRIM( \"zzz   \" )", "zzz")
TSTR(RTRIM2, "RTRIM( \"zzz   \" )+\"qqq\"", "zzzqqq")
TSTR(SPACE, "SPACE( 3 )", "   ")
TSTR(STR1, "STR( -52.345 )", "       -52")
TSTR(STR2, "STR( -52.345, 3 )", "-52")
TSTR(STR3, "STR( 52.34, 4, 1 )", "52.3")
TSTR(TRIM, "TRIM( \"aaa    \" )", "aaa")
TSTR(UPPER, "UPPER( \"abcde\" )", "ABCDE")

TDOU(ABS, "ABS( -222 )", 222)
TDOU(EXP, "EXP( 1 )", 2.7182818284)
TDOU(LOG, "LOG( 2 )", 0.6931471805)
TDOU(MAX, "MAX( 10, 27 )", 27)
TDOU(MIN, "MIN( 10, 5 )", 5)
TDOU(SQRT, "SQRT( 9 )", 3)

TLON(ASC, "ASC( \"A\" )", 'A')
TLON(AT, "AT( \"BC\", \"ABCD\" )", 2)
TLON(DAY, "DAY( 20000101 )", 1)
TLON(DESCEND, "DESCEND( 1500 )", -1500)
TLON(DOW, "DOW( 20000101 )", 6)
TLON(INT, "INT( 621.5 )", 621)
TLON(LEN, "LEN( \"AAAAA\" )", 5)
TLON(MONTH, "MONTH( 20000101 )", 1)
TLON(DISABLED_RECNO, "RECNO()", 1)
TLON(VAL, "VAL( \"ABC\" )", 65)
TLON(YEAR, "YEAR( \"20000101\" )", 2000)

TLOG(ISALPHA, "ISALPHA( \"A\" )", true)
TLOG(ISLOWER1, "ISLOWER( \"a\" )", true)
TLOG(ISUPPER1, "ISUPPER( \"A\" )", true)
TLOG(ISLOWER2, "ISLOWER( \"A\" )", false)
TLOG(ISUPPER2, "ISUPPER( \"a\" )", false)

TDOU(CALC1, "(25-3+2)*2", 48);
TDOU(CALC2, "(25+3+2)*2", 60);
TDOU(ADD1, "TEST->FLOAT1+1", 6);
TDOU(ADD2, "TEST->FLOAT1 + 1", 6);
TDOU(ADD3, "FLOAT1+1", 6);
TDOU(ADD4, "FLOAT1 + 1", 6);
TLOG(CMP1, "TEST->FLOAT1 < 1", false);
TLOG(CMP2, "TEST->FLOAT1 > 1", true);
TDOU(CMP3, "TEST->DATE2 - TEST->DATE1", (xbDouble)10);

TSTR(IIF1, "IIF( \"TEST->FLOAT1>0\", \"T\", \"F\" )", "T");
TSTR(IIF2, "IIF( \"TEST->FLOAT1<=0\", \"T\", \"F\" )", "F");
TSTR(IIF3, "IIF( \"TEST->FLOAT1<0\", \"T\", \"F\" )", "F");
TSTR(IIF4, "IIF( \"TEST->FLOAT1=5\", \"T\", \"F\" )", "T");

TEST_F(Exp, DISABLED_STRZERO) {
	//TSTR(STRZERO1, "STRZERO( \"aaa\" )", "not sure" );
	//TSTR(STRZERO2, "STRZERO( \"aaa\", 3, 3 )", "??" );
	//TSTR(STRZERO3, "STRZERO( 22 )", "not sure" );
	//TSTR(STRZERO4, "STRZERO( 22, 3 )", "not sure" );
	//TSTR(STRZERO5, "STRZERO( 2, 3, 3 )", "not sure" );
	//TSTR(STRZERO6, "STRZERO( \"ddd\", 4, 6 )", "not sure" );
}
