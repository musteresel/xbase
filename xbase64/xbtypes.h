#ifndef __XB_XTYPES_H__
#define __XB_XTYPES_H__

#include <stdio.h>

/*! \file xbtypes.h
 */

//! xbULong type
/*!
 */
typedef unsigned long int xbULong;

//! xbUShort type
/*!
 */
typedef unsigned short int xbUShort;

//! xbShort type
/*!
 */
typedef short int xbShort;
typedef long xbLong;

//! xbFloat type
/*!
 */
typedef float xbFloat;

//! xbDouble type
/*!
 */
typedef double xbDouble;

//! xbBool type
/*!
 */
typedef short int xbBool;

//! xbOffT type
/*!
 */
#ifdef XB_LOCKING_ON
#ifdef __WIN32__
#else
#endif
#endif  // XB_LOCKING_ON

// 64 bit file processing
#if defined(HAVE_FSEEKO) && defined(HAVE_FTELLO) && \
    defined(XB_LARGEFILE_SUPPORT)
#define _ftell ftello
#define _fseek fseeko
typedef off_t xbOffT;
#else
#define _ftell ftell
#define _fseek fseek
typedef long xbOffT;
#endif

#endif  // __XB_XTYPES_H__
