/*  exptest.cpp 

    Xbase project source code

    This program tests the Xbase expression logic

    Copyright (C) 1997,2003  Gary A Kunkel
    
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA


    Contact:
    
     Email:
    
      xbase64-devel@lists.sourceforge.net
      xbase64-users@lists.sourceforge.net
      
      
     Regular Mail:
     
       XBase Support
       149C South Main St
       Keller Texas, 76248     
       USA


*/

#include "xbase64/xbase64.h"

class ExpTestor{
 public:ExpTestor( xbXBase *, xbDbf * );
  xbShort TestExpression( const char * TestExpression, 
                          const char * ExpectedResult );
  xbShort TestExpression( const char * TestExpression, 
                          const xbDouble ExpectedResult );
 private:
  xbXBase *xbptr;
  xbDbf   *dbfPtr;
};
/**************************************************************************/
ExpTestor::ExpTestor( xbXBase *xp, xbDbf *dp )
{
  xbptr  = xp;
  dbfPtr = dp;
}
/**************************************************************************/
xbShort ExpTestor::TestExpression( const char * Expression,
                                   const xbDouble ExpectedResult )
{
//  xbExpNode * e;
  xbExpn * exp;
  xbShort rc;
  
  exp = new xbExpn( xbptr );
  if(( rc = exp->ParseExpression( Expression, dbfPtr )) != 0 ){
    std::cout << "Parse Error " << rc << " in expression " << Expression
              << std::endl;
    if( exp )
      delete exp;
    return 1;
  }

  if(( rc = exp->ProcessExpression()) != 0 ){
    std::cout << "Error " << rc << " processing expression " << Expression
              << std::endl;
    if( exp )
      delete exp;
    return 1;
  }
  char type = exp->GetExpressionResultType();
  if( type != 'N' && type != 'L' ){
    std::cout << "Expression " << Expression;
    std::cout << " Expected result type Numeric or Logical, actual was ";
    std::cout << type << std::endl;
    delete exp;
    return 1;
  }

  if( type == 'N' ){
    xbString d1;
    xbString d2;
    d1.setNum( "2.4", ExpectedResult );
    d2.setNum( "2.4", exp->GetDoubleResult());
    if( d1 != d2 ){
      std::cout << "Expression " << Expression;
      std::cout << " Actual result of "  << d2  << " does not match";
      std::cout << " expected result of " << d1 << std::endl;
      delete exp;
      return 1;
    }
  }
  if( type == 'L' && ExpectedResult != (xbDouble) exp->GetIntResult()){
    std::cout << "Expression " << Expression;
    std::cout << " Actual result of " << exp->GetIntResult()
              << " does not match ";
    std::cout << " expected result of " << ExpectedResult << std::endl;
    delete exp;
    return 1;
  }

  std::cout << "Expression " << Expression << " returned " << ExpectedResult;
  std::cout << " OK" << std::endl;
  delete exp;
  return 0;
}
/**************************************************************************/
xbShort ExpTestor::TestExpression( const char * Expression,
                                   const char * ExpectedResult )
{
//  xbExpNode * e;
  xbExpn * exp;
  xbShort rc;
	
  exp = new xbExpn( xbptr );
  if(( rc = exp->ParseExpression( Expression, dbfPtr )) != 0 ){
    std::cout << "Parse Error " << rc << " in expression " << Expression
              << std::endl;
    if( exp )
      delete exp;
    return 1;
  }

  if(( rc = exp->ProcessExpression()) != 0 ){
    std::cout << "Error " << rc << " processing expression " << Expression
              << std::endl;
    delete exp;
    return 1;
  }
  char type = exp->GetExpressionResultType();
  if( type != 'C' ){
    std::cout << "Expression " << Expression;
    std::cout << " Expected result type Character, actual was " << type
              << std::endl;
    delete exp;
    return 1;
  }
  
  if( strlen( ExpectedResult ) != strlen( exp->GetStringResult())){
    std::cout << "Expression " << Expression;
    std::cout << " result length of "
              << strlen( exp->GetStringResult())
              << " different than expected of " << strlen( ExpectedResult )
              << std::endl;
    std::cout << "Calculated result =" << exp->GetStringResult()
              << "<" << std::endl;
    delete exp;
    return 1;
  }

  if( strcmp( ExpectedResult, exp->GetStringResult())){
    std::cout << "Expression " << Expression;
    std::cout << " Actual result of " << exp->GetStringResult()
              << " does not match ";
    std::cout << " expected result of " << ExpectedResult << std::endl;
    delete exp;
    return  1;
  }

  std::cout << "Expression " << Expression << " returned " << ExpectedResult;
  std::cout << " OK" << std::endl;
  return 0;
}
/*************************************************************************/
int main()
{
  xbSchema MyRecord[] =
  {
    { "FLOAT1", XB_FLOAT_FLD,  9, 2 },
    { "DATE1",  XB_DATE_FLD,   8, 0 },
    { "DATE2",  XB_DATE_FLD,   8, 0 },
    { "", 0, 0, 0 },
  };

  xbXBase x;
  xbDbf d( &x );
  xbExpn exp( &x );

  d.CreateDatabase( "TEST", MyRecord, XB_OVERLAY );
  d.PutFloatField( "FLOAT1", 5 );  
  d.PutField( "DATE1", "19990110" );
  d.PutField( "DATE2", "19990120" );
  d.AppendRecord();

  std::cout << "XBase Expression testing program.." << std::endl;
  std::cout << "This program tests the XBase expression logic." << std::endl;
  ExpTestor * e = new ExpTestor( &x, &d );

/* test functions which return a character value result */
  e->TestExpression( "CDOW( \"20000101\" )", "Saturday " );
  e->TestExpression( "CHR( 101 )", "e" );
  e->TestExpression( "CMONTH( \"20000101\" )", "January  " );
  e->TestExpression( "DATE()", exp.DATE() );
  e->TestExpression( "DTOC( \"20000101\" )", "01/01/00" );
  e->TestExpression( "DTOS( \"20000101\" )", "20000101" );
  e->TestExpression( "LEFT( \"STRING\", 3 )", "STR" );
  e->TestExpression( "LTRIM( \"   xxxxxx\" )", "xxxxxx" );
  e->TestExpression( "LOWER( \"AAAA\" )", "aaaa" );

  e->TestExpression( "REPLICATE( \"abc\", 3 )", "abcabcabc" );
  e->TestExpression( "RTRIM( \"zzz   \" )", "zzz" );
  e->TestExpression( "RTRIM( \"zzz   \" )+\"qqq\"", "zzzqqq" );
  e->TestExpression( "SPACE( 3 )", "   " );

  e->TestExpression( "STR( -52.345 )", "       -52" );    
  e->TestExpression( "STR( -52.345, 3 )", "-52" );    
  e->TestExpression( "STR( 52.34, 4, 1 )", "52.3" );
  
// not sure what the STRZERO function is supposed to do
/*
  e->TestExpression( "STRZERO( \"aaa\" )", "not sure" );
  e->TestExpression( "STRZERO( \"aaa\", 3, 3, )", "??" );
  e->TestExpression( "STRZERO( 22 )", "not sure" );
  e->TestExpression( "STRZERO( 22, 3 )", "not sure" );
  e->TestExpression( "STRZERO( 2, 3, 3 )", "not sure" );
  e->TestExpression( "STRZERO( \"ddd\", 4, 6 ), "not sure" );
*/  
  e->TestExpression( "TRIM( \"aaa    \" )", "aaa" );
  e->TestExpression( "UPPER( \"abcde\" )", "ABCDE" );

/* functions returning double values */
  e->TestExpression( "ABS( -222 )", 222 );
  e->TestExpression( "EXP( 1 )", (xbDouble) 2.7182800 );  
  e->TestExpression( "LOG( 2 )", (xbDouble) 0.69314700 );
  e->TestExpression( "MAX( 10, 27 )", 27 );
  e->TestExpression( "MIN( 10, 5 )", 5 );
  e->TestExpression( "SQRT( 9 )", 3 );
  
/* functions returning long values */
  e->TestExpression( "ASC( \"A\" )", 'A' );
  e->TestExpression( "AT( \"BC\", \"ABCD\" )", 2 );
  e->TestExpression( "DAY( 20000101 )", 1 );

  e->TestExpression( "DESCEND( 1500 )", -1500 );

  e->TestExpression( "DOW( 20000101 )", 6 );
  e->TestExpression( "INT( 621.5 )", 621 );
  e->TestExpression( "ISALPHA( \"A\" )", 1 );
  e->TestExpression( "ISLOWER( \"a\" )", 1 );
  e->TestExpression( "ISUPPER( \"A\" )", 1 );
  e->TestExpression( "LEN( \"AAAAA\" )", 5 );
  e->TestExpression( "MONTH( 20000101 )", 1 );
  e->TestExpression( "RECNO()", (xbDouble) 0 );
  e->TestExpression( "VAL( \"ABC\" )", 65 );
  e->TestExpression( "YEAR( \"20000101\" )", 2000 );

  e->TestExpression( "(25-3+2)*2", 48 );
  e->TestExpression( "(25+3+2)*2", 60 );
  e->TestExpression( "TEST->FLOAT1+1", 6 );
  e->TestExpression( "TEST->FLOAT1 + 1", 6 );
  e->TestExpression( "FLOAT1+1", 6 );
  e->TestExpression( "FLOAT1 + 1", 6 );

  e->TestExpression( "TEST->FLOAT1 < 1", (xbDouble) 0 );
  e->TestExpression( "TEST->FLOAT1 > 1", (xbDouble) 1 );
  e->TestExpression( "TEST->DATE2 - TEST->DATE1", (xbDouble) 10 );

  e->TestExpression( "IIF( \"TEST->FLOAT1>0\", \"T\", \"F\" )", "F" );
  e->TestExpression( "IIF( \"TEST->FLOAT1<=0\", \"T\", \"F\" )", "T" );


  delete e;
  return 0;
}     
