/****************************************************************************
 *  DIO Port I/O Driver Interface
 *  (c) Copyright 1998 Valley Software Systems, Inc.
 *  All Rights Reserved.
 *
 *  Win32 Prototypes for DIO Port I/O
 *
 * Revisions
 * 1     3/10/98 2:03p DaveB
 * Initial revision.
 *
 ****************************************************************************/

#ifndef DIO_H
  #define DIO_H

#ifndef UL
  #define UL unsigned long
#endif

// Make sure you extern "C" this if you are in C++ to avoid mangling
extern "C" {

UL _stdcall DIOReadArray(UL base, UL read_array[]);
UL _stdcall DIOReadLong(UL base, UL *read_result);

UL _stdcall DIOWriteArray(UL base, UL write_array[]);
UL _stdcall DIOWriteLong(UL base, UL long_write);

}

#endif // DIO_H
