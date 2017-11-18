/*  
    This debugging program tests Xbase locking functions

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

int main(int, char**)
{
#if 0 // FIXME - seriously
#ifdef XB_LOCKING_ON
   xbShort rc;

   if(2!=ac){
     cout << "\nUsage: locktest filename\n";
     return 1;
   }

   if(( rc = d.OpenDatabase( av[1] )) != XB_NO_ERROR ) {
     cout << "\nError " << rc << " opening file " << av[1] << endl;
     exit(0);
   }
   xbXBase x;
   xbDbf d( &x );

   cout << "\nGoing to lock database..." << endl;
   rc = d.LockDatabase( F_SETLKW, F_WRLCK, 1L );
   if ( rc == -1 ){
     perror("Lock Error");
     return 2;
   }
   cout << "Database locked\n\nEnter a keystroke to release lock\n";
   char xx[4];
   cin  >> xx;

   rc = d.LockDatabase( F_SETLK, F_UNLCK, 1L );
   cout << "Unlock database rc = " << rc << "\n";
   d.CloseDatabase();
#else
   cout << "\nXB_LOCKING_ON is not compiled in\n";
#endif
#endif
   return 0;
}
