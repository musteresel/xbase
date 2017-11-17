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

static void
showStatus(xbLong itemNum, xbLong numItems)
{
  printf("indexing record %ld of %ld\r", itemNum, numItems);
  fflush(stdout);
}

int main(int ac,char** av)
{
    if (3 != ac) {
        std::cout << 
            "\nUsage: reindex dbf_file ndx_file\n"
            ;
        return 1;
    }
    
    char* filename = av[1];
    char* filename2 = av[2];

   xbXBase x;
   xbDbf MyFile( &x );
   xbNdx MyIndex( &MyFile );

    if( MyFile.OpenDatabase( filename )) {
      std::cout << "Could not open file " << filename << "\n";
      return 0;
   }
    if( MyIndex.OpenIndex( filename2 )) {
      std::cout << "Could not open index file " << filename2 << "\n";
      return 0;
   }

    xbShort rc = MyIndex.ReIndex(showStatus);
    printf("\n");
    if( rc != XB_NO_ERROR ) {
      std::cout << "\nError reindexing index ==> " << filename2;
      std::cout << " Return Code = " << rc;
   }

    /* or
   if(( rc = MyFile.RebuildAllIndicis()) != XB_NO_ERROR ) 
   {
      std::cout << "\nError reindexing...";
      std::cout << "\nReturn Code = " << rc;
   }
    */
   MyFile.CloseDatabase();	/* close database */
    
    return 0;
}     
