/* 
    Xbase64 project source code

    This sample program packs an Xbase DBF file

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
    if (ac <= 1) {
        std::cout <<
            "\nUsage: packdbf filename...\n"
            "\nThis program does not automatically reindex any NDX indexes."
            "\nUse the reindex program to reindex any indexes associated"
            "\nwith the database, or build your own program which executes "
            "\nthe PackDatabase() method after opening all the index files "
            "\nassociated with the database.\n\n"
            ;
        return 1;
    }
    
    for (int i=1; i<ac; ++i) {
        char* filename = av[i];

   xbXBase x;
   xbDbf MyFile( &x );

        if( MyFile.OpenDatabase( filename )) {
      std::cout << "Could not open file " << filename << "\n";
            return 1;
   }

        xbShort rc = MyFile.PackDatabase( XB_LOCK );
        if( rc != XB_NO_ERROR ) {
      std::cout << "\nError packing database ==> " << filename;
      std::cout << " Return Code = " << rc;
   }
   MyFile.CloseDatabase();	/* close database */

   std::cout << "\nPack Database complete...\n\n";
    }

    return 0;
}     
