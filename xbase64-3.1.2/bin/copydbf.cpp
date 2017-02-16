/* 
    Xbase64 project source code

    This sample program copies the structure of one dbf to another
    dbf file

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

int main(int ac,char** av)
{
   if (3 != ac) {
      std::cout <<
         "\nUsage: copydbf filename1 filename2\n"
         "This program copies the structure of one dbf file to another\n";
        return 1;
    }
    
   char* sfilename = av[1];
   char* tfilename = av[2];

   xbXBase x;
   xbDbf MyFile( &x );

    xbShort rc = MyFile.OpenDatabase( sfilename );
    if( rc != XB_NO_ERROR ) {
      std::cout << "Could not open file " << sfilename << " Error = " << rc
                << "\n";
        return 2;
   }

    //   OverlaySwitch = 0;    	/* dont overlay existing file if it exists */
    xbShort OverlaySwitch = 1;  /* overlay existing file if it exists */

   if(( rc = MyFile.CopyDbfStructure( tfilename, OverlaySwitch )) != XB_NO_ERROR )
   {
      std::cout << "Could not copy file " << tfilename << " Error = " << rc
                << "\n";
      return 3;
   }

   MyFile.CloseDatabase();	/* close database */
   return 0;
}     
