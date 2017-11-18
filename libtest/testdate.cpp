/*
    Xbase project source code

    This program tests the xdate routines 

    This program tests and demonstrates usage of the various xbDate methods

    Several of the tests pass either StringDate or Chardate to the method 
    being tested - this is done to test the class methods.  In actual usage, 
    this may not be necessary due to the instance of the class already 
    containing a date value.  

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

#include <xbase64/xbase64.h>

int main()
{
   xbString StringDate( "19701007" );      /* oct 7 1960 */
   char     CharDate[9] = "19611109";      /* nov 9 1961 */

   xbDate d1;                              /* today is default   */
   xbDate d2( StringDate );                /* from string data   */ 
   xbDate d3( CharDate );                  /* from char data     */
   xbDate d4;                              /* another date class */

   std::cout << "This program tests the XDATE routines" << std::endl;
   std::cout << "Date 1 (Sysdate) is    " << d1.GetDate() << std::endl;
   std::cout << "Date 2 (StringDate) is " << d2.GetDate() << std::endl;
   std::cout << "Date 3 (CharDate) is   " << d3.GetDate() << std::endl;

   std::cout << "This year is  " << d1.YearOf() << std::endl;
   std::cout << "Year of xbString Date is " <<  d2.YearOf( StringDate )
             << std::endl;
   std::cout << "Year of char Date is "     <<  d3.YearOf( CharDate )
             << std::endl;

   std::cout << "This Month is " << d1.MonthOf() << std::endl;
   std::cout << "Month of xbString Date is " <<  d2.MonthOf( StringDate )
             << std::endl;
   std::cout << "Month of char Date is "     <<  d3.MonthOf( CharDate )
             << std::endl;

   std::cout << "Today is day " << d1.DayOf( XB_FMT_WEEK ) << " of the week"
             << std::endl; 
   std::cout << "StringDate is day " << d2.DayOf( XB_FMT_MONTH, StringDate )
             << " of the month" << std::endl;
   std::cout << "CharDate is day " << d3.DayOf( XB_FMT_YEAR, CharDate )
             << " of the year" << std::endl;

   if( d1.IsLeapYear())
      std::cout << "This is a leapyear" << std::endl;
   else
      std::cout << "This is not a leap year." << std::endl;
 
   if( d2.IsLeapYear( StringDate ))
      std::cout << "StringDate is a leapyear" << std::endl;
   else
      std::cout << "StringDate is not a leap year." << std::endl;
 
   if( d3.IsLeapYear( CharDate ))
      std::cout << "CharDate is a leapyear" << std::endl;
   else
      std::cout << "CharDate is not a leap year." << std::endl;
 
   std::cout << "Today is " << d1.Sysdate() << std::endl;

   if( d1.DateIsValid( "19951301" ))
      std::cout << "19951301 is a valid date" << std::endl;
   else
      std::cout << "19951301 is not a valid date" << std::endl;

   if( d1.DateIsValid( "19920229" ))
      std::cout << "19920229 is a valid date" << std::endl;
   else
      std::cout << "19920229 is not a valid date" << std::endl;

   if( d2.DateIsValid( StringDate ))
      std::cout << StringDate << " is a valid date" << std::endl;
   else
      std::cout << StringDate << " is not a valid date" << std::endl;

   std::cout << "Today's Julian date " << d1.JulianDays() << std::endl;
   std::cout << "Julian date of Jan 01, 1970 " << d2.JulianDays( "19700101" )
             << std::endl;
   std::cout << "StringDate Julian date " << d2.JulianDays( StringDate )
             << std::endl;

   std::cout << "There are "
             << ( d1.JulianDays( "19951101" ) - d1.JulianDays( "19951001" ))
             << " days between 10/1/95 and 11/1/95." << std::endl;

   std::cout << "Todays Julian date (Number of days since Jan 1 0100):"
             << d1.JulianDays() << std::endl; 

   d4 = d1;    // set d4 class = to sysdate 
   std::cout << "Object d4 initialized to " << d4.GetDate() << std::endl;
   std::cout << "This should be todays date: "  
             << d4.JulToDate8(d4.JulianDays()) << std::endl;
   std::cout << "In 7 days it will be "  
             << d4.JulToDate8(d4.JulianDays() + 7L ) << std::endl;

   std::cout << "Today is " << d1.CharDayOf() << std::endl;
   std::cout << "StringDate day is " << d2.CharDayOf( StringDate )
             << std::endl;
   std::cout << "This month is " << d1.CharMonthOf() << std::endl;
   std::cout << "StringDate month is " << d2.CharMonthOf() << std::endl;


   /* various format routines using different formats, strings and chars */
   xbString xbStFmt( "MM/DD/YY" );
   std::cout << "Format (YYDDD)     " << d1.FormatDate( "YYDDD" ) << std::endl;
   std::cout << "Format (MM/DD/YY)  " << d1.FormatDate( xbStFmt ) << std::endl;
   xbStFmt = "DD/MM/YY";
   std::cout << "Format (DD/MM/YY)  " << d1.FormatDate(xbStFmt, "19730110")
             << std::endl;
   std::cout << "Format (MMMM DD,YYYY)    "
             <<  d1.FormatDate( "MMMM DD,YYYY", d1.GetDate()) << std::endl;
   xbStFmt = "DDDD, MMMM DD YYYY";
   std::cout << "Format (DDDD, MMMM DD YYYY) "
             <<  d2.FormatDate( xbStFmt, d2.GetDate()) << std::endl;

   std::cout << "Last day this month " << d1.LastDayOfMonth() << std::endl;
   std::cout << "Last day of month for StringDate is "
             << d2.LastDayOfMonth( d2.GetDate()) << std::endl;

   std::cout << "Overloaded operators test..." << std::endl;

   if( d1 == d2 )
     std::cout << d1.GetDate() << " is equal to " << d2.GetDate()
               << std::endl;
   else
     std::cout << d1.GetDate() << " is not equal to " << d2.GetDate()
               << std::endl;

   if( d1 != d3 )
     std::cout << d1.GetDate() << " is not equal to " << d3.GetDate()
               << std::endl;
   else
     std::cout << d1.GetDate() << " is equal to " << d3.GetDate()
               << std::endl;
     
   if( d1 < d2 )
     std::cout << d1.GetDate() << " is less than " << d2.GetDate()
               << std::endl;
   else
     std::cout << d1.GetDate() << " is not less than " << d2.GetDate()
               << std::endl;
     
   if( d1 > d2 )
     std::cout << d1.GetDate() << " is greater than " << d2.GetDate()
               << std::endl;
   else
     std::cout << d1.GetDate() << " is not greater than " << d2.GetDate()
               << std::endl;
     
   if( d1 <= d2 )
     std::cout << d1.GetDate() << " is less than or equal to " << d2.GetDate()
               << std::endl;
   else
     std::cout << d1.GetDate() << " is not less than or equal to "
               << d2.GetDate() << std::endl;
     
   if( d1 >= d2 )
     std::cout << d1.GetDate() << " is greater than or equal to "
               << d2.GetDate() << std::endl;
   else
     std::cout << d1.GetDate() << " is not greater than or equal to "
               << d2.GetDate() << std::endl;

   d1.Sysdate();
   d1++;
   std::cout << "Tomorrow is " << d1.GetDate() << std::endl;
   d1-=2;
   std::cout << "Yesterday was " << d1.GetDate() << std::endl;
   std::cout << "There are " << d1 - d2 << " days between " << d1.GetDate() 
             << " and " << d2.GetDate() << std::endl;

   return 0;
}
    
