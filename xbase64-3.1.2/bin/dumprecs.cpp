/*  dumprecs.cpp

    Thos program dumps a dbf file contents 

    Xbase64 project source code

    This sample program dumps Xbase records

    Copyright (C) 1997,2003  Gary A. Kunkel   

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

// next lines are helpful for debugging purposes
#include <xbase64/xbdbf.cpp>
#include <xbase64/xbexp.cpp>
#include <xbase64/xbexpprc.cpp>
#include <xbase64/xbexpfnc.cpp>
#include <xbase64/xbfields.cpp>
#include <xbase64/xbindex.cpp>
#include <xbase64/xbmemo.cpp>
#include <xbase64/xbndx.cpp>
#include <xbase64/xbntx.cpp>
#include <xbase64/xbase64.cpp>
#include <xbase64/xbdate.cpp>
#include <xbase64/xbfilter.cpp>
#include <xbase64/xblock.cpp>
#include <xbase64/xbstring.cpp>
#include <xbase64/xbfile.cpp>
#include <xbase64/xbcdx.cpp>



int main(int ac,char** av)
{
  xbXBase x;
  xbShort rc;  
 
  if (ac <= 1) {
    std::cout << "Usage: dumprecs filename..." << std::endl;
    return 1;
  }

  for(int i=1; i<ac; ++i){
    char* filename = av[i];

    xbDbf MyFile( &x );

    MyFile.SetVersion( 4 );
    rc = MyFile.OpenDatabase(filename);
    if( rc != XB_NO_ERROR) {
      std::cout << "Could not open file " << filename << std::endl;
      x.DisplayError( rc );
      return 1;
    }

    std::cout << "Processing file sequentially from beginning..." << std::endl;
    int i = 0;
    while(i<MyFile.NoOfRecords()){
      rc = MyFile.DumpRecord(++i);
      if( rc != XB_NO_ERROR )
        x.DisplayError( rc );
    }
    MyFile.CloseDatabase();	/* close database */
  }
  return 0;
}     

