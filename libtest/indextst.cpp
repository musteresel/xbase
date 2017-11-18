/*  indextst.cpp 

    Xbase project source code

    This program creates a sample database and multiple indices.
    It tests the index logic.

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

int CheckIndex(
#ifdef XB_INDEX_NDX
               xbNdx *indx1, xbNdx *indx2, xbNdx *indx3
#endif
#if defined( XB_INDEX_NDX ) && defined ( XB_INDEX_NTX )
               ,
#endif
#ifdef XB_INDEX_NTX
               xbNtx *intx1, xbNtx *intx2, xbNtx *intx3
#endif
              );

int main()
{
  xbShort f1, f2, f3, rc, sts = 0;
  char charbuf[10];

  xbSchema MyRecord[] =
  {
    { "CHARFLD1",  XB_CHAR_FLD,      6, 0 },
    { "CHARFLD2",  XB_CHAR_FLD,      6, 0 },
    { "NUMFLD1",   XB_NUMERIC_FLD,   6, 0 },
    { "",0,0,0 }
  };

  /* define the classes */
  xbXBase x;			/* initialize xbase  */
  xbDbf MyFile( &x );		/* class for table   */

#ifdef XB_INDEX_NDX
  xbNdx indx1( &MyFile );	/* class for ndx index 1 */
  xbNdx indx2( &MyFile );	/* class for ndx index 2 */
  xbNdx indx3( &MyFile );	/* class for ndx index 3 */
#endif

#ifdef XB_INDEX_NTX
  xbNtx intx1( &MyFile );	/* class for ntx index 1 */
  xbNtx intx2( &MyFile );	/* class for ntx index 2 */
  xbNtx intx3( &MyFile );	/* class for ntx index 3 */
#endif

#ifndef XBASE_DEBUG
  std::cout << "XBASE_DEBUG support option not compiled into library";
  return 1;
#endif


  std::cout << "Creating test database and indices" << std::endl;
  if(( rc = MyFile.CreateDatabase( "IXTEST.DBF", MyRecord, XB_OVERLAY ))
        != XB_NO_ERROR )
     std::cout << "Error creating database = " << rc << "\n";
  else
  {
#ifdef XB_INDEX_NDX
     if(( rc = indx1.CreateIndex(
       "IXNDX1.NDX", "CHARFLD1", XB_NOT_UNIQUE, XB_OVERLAY )) != XB_NO_ERROR )
     {
        std::cout << "Error creating index 1 = " << rc << std::endl;
        exit( 1 );
     }

     if(( rc = indx2.CreateIndex(
       "IXNDX2.NDX", "CHARFLD1+CHARFLD2", XB_NOT_UNIQUE, XB_OVERLAY )) != XB_NO_ERROR )
     {
        std::cout << "Error creating index 2 = " << rc << std::endl;
        exit( 1 );
     }

     if(( rc = indx3.CreateIndex(
       "IXNDX3.NDX", "NUMFLD1", XB_NOT_UNIQUE, XB_OVERLAY )) != XB_NO_ERROR )
     {
        std::cout << "Error creating index 3 = " << rc << std::endl;
        exit( 1 );
     }
#endif


#ifdef XB_INDEX_NTX
     if(( rc = intx1.CreateIndex(
       "IXNTX1.NTX", "CHARFLD1", XB_NOT_UNIQUE, XB_OVERLAY )) != XB_NO_ERROR )
     {
        std::cout << "Error creating index 4 = " << rc << std::endl;
        exit( 1 );
     }

     if(( rc = intx2.CreateIndex( 
       "IXNTX2.NTX", "CHARFLD1+CHARFLD2", XB_NOT_UNIQUE, XB_OVERLAY )) != XB_NO_ERROR )
     {
        std::cout << "Error creating index 5 = " << rc << std::endl;
        exit( 1 );
     }

     if(( rc = intx3.CreateIndex( 
       "IXNTX3.NTX", "NUMFLD1", XB_NOT_UNIQUE, XB_OVERLAY )) != XB_NO_ERROR )
     {
        std::cout << "Error creating index 6 = " << rc << std::endl;
        exit( 1 );
     }
#endif
  }

  f1 = MyFile.GetFieldNo( "CHARFLD1" );
  f2 = MyFile.GetFieldNo( "CHARFLD2" );
  f3 = MyFile.GetFieldNo( "NUMFLD1" ); 

  std::cout << "Populating database and indices with data" << std::endl;
  std::cout << ".";
  std::cout.flush();
  for( int i = 0; i < 10000; i++ ){
    if( i % 100 == 0){
      std::cout << ".";
      std::cout.flush();
    }
    memset( charbuf, 0x00, 10 );
    sprintf( charbuf, "%d", i );
    MyFile.BlankRecord();
    MyFile.PutField( f1, charbuf );
    MyFile.PutField( f2, charbuf );
    MyFile.PutLongField( f3, i );
    MyFile.AppendRecord();


  }
  std::cout << " Done." << std::endl;

  // Check all indices.
  sts += CheckIndex(
#ifdef XB_INDEX_NDX
                    &indx1, &indx2, &indx3
#endif
#if defined( XB_INDEX_NDX ) && defined( XB_INDEX_NTX )
                    ,
#endif
#ifdef XB_INDEX_NTX
                    &intx1, &intx2, &intx3
#endif
                    );
  //
  // Appending a "Z" to the records will cause the index delete
  // functions to be used.
  //
  // - Bob Cotton <bob@synxis.com>
  //
  std::cout << "Reversing records." << std::endl;
  std::cout << ".";
  std::cout.flush();
    for( xbLong j = 1; j < MyFile.NoOfRecords(); j++ ){
      if (j  % 1000 == 0)
      {
          std::cout << ".";
          std::cout.flush();
      }
      MyFile.GetRecord(j);
      memset( charbuf, 0x00, 10 );
      sprintf( charbuf, "Z%d", (int)j-1 );
      MyFile.PutField( f1, charbuf );
      MyFile.PutField( f2, charbuf );
      MyFile.PutLongField( f3, j-1 );
      MyFile.PutRecord();
  }
  std::cout << " Done." << std::endl;
  // Check all indices
  sts += CheckIndex(
#ifdef XB_INDEX_NDX
                     &indx1, &indx2, &indx3
#endif
#if defined( XB_INDEX_NDX ) && defined( XB_INDEX_NTX )
                     ,
#endif
#ifdef XB_INDEX_NTX
                    &intx1, &intx2, &intx3
#endif
                    );
    

  std::cout << "Index testing completed" << std::endl;std::cout.flush();
  MyFile.CloseDatabase();   /* Close database and associated indexes */
  return sts;
}     


int CheckIndex(
#ifdef XB_INDEX_NDX
    xbNdx *indx1,
    xbNdx *indx2,
    xbNdx *indx3
#endif
#if defined( XB_INDEX_NDX ) && defined( XB_INDEX_NTX )
   ,
#endif
#ifdef XB_INDEX_NTX
    xbNtx *intx1,
    xbNtx *intx2,
    xbNtx *intx3
#endif
    )
{
    int rc;
    int sts = 0;
    
#if defined( XB_INDEX_NDX ) && defined( XBASE_DEBUG )
    std::cout << "Testing NDX index 1 "; std::cout.flush();
    if(( rc = indx1->CheckIndexIntegrity(0)) != XB_NO_ERROR ){
        std::cout << "Error " << rc << " with index indx1" << std::endl;
        sts++;
    }
    else
        std::cout << "OK" << std::endl;

    std::cout << "Testing NDX index 2 ";std::cout.flush();
    if(( rc = indx2->CheckIndexIntegrity(0)) != XB_NO_ERROR ){
        std::cout << "Error " << rc << " with index indx2" << std::endl;
        sts++;
    }
    else
        std::cout << "OK" << std::endl;


    std::cout << "Testing NDX index 3 ";std::cout.flush();
    if(( rc = indx3->CheckIndexIntegrity(0)) != XB_NO_ERROR ){
        std::cout << "Error " << rc << " with index indx3" << std::endl;
        sts++;
    }
    else
        std::cout << "OK" << std::endl;
#endif
#if defined( XB_INDEX_NTX ) && defined( XBASE_DEBUG )
    std::cout << "Testing NTX index 1 ";std::cout.flush();
    if(( rc = intx1->CheckIndexIntegrity(0)) != XB_NO_ERROR ){
        std::cout << "Error " << rc << " with index intx1" << std::endl;
        sts++;
    }
    else
        std::cout << "OK" << std::endl;

    std::cout << "Testing NTX index 2 ";std::cout.flush();
    if(( rc = intx2->CheckIndexIntegrity(0)) != XB_NO_ERROR ){
        std::cout << "Error " << rc << " with index intx2" << std::endl;
        sts++;
    }
    else
        std::cout << "OK" << std::endl;

    std::cout << "Testing NTX index 3 ";std::cout.flush();
    if(( rc = intx3->CheckIndexIntegrity(0)) != XB_NO_ERROR ){
        std::cout << "Error " << rc << " with index intx3" << std::endl;
        sts++;
    }
    else
        std::cout << "OK" << std::endl;
#endif
    return sts;

}

