#ifndef _CSV_H
#define _CSV_H

/* Copyright (C) 1999 Lucent Technologies */
/* Excerpted from 'The Practice of Programming' */
/* by Brian W. Kernighan and Rob Pike */

/* csv.h: interface for csv library */

extern char *csvscanline(char *in);
extern char *csvfield(int n);	  /* return field n */
extern int csvnfield(void);		  /* return number of fields */

#endif /* _CSV_H */
