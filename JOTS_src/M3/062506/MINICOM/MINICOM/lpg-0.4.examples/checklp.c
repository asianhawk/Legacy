/*
 *  AUTHOR: Sven Goldt (goldt@math.tu-berlin.de)
 *
 *  This program is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  as published by the Free Software Foundation; either version 2
 *  of the License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
*/
/*
 *
 * Changes in 1.1: Fixed bit meaning for low active lines ! 
 *
*/

#include <stdio.h>
#include <fcntl.h>
/* #include <linux/lp.h>  DAMNED ! - Some butthead crippled that file !!! */
#include "oldlp.h"
#include <asm/io.h>

#ifndef LP_NO
#define LP_NO 3
#endif

main()
{
int i,fd,irq;
unsigned char status=0;
char printer[10];

 for (i=0;i<LP_NO;i++)
 {
  sprintf(printer,"/dev/lp%d",i);
  printf("\nchecking %s: ",printer);
  fflush(stdout);

  fd=open(printer,O_WRONLY);
  if (fd<0) { perror(NULL); continue; }
  irq=ioctl(fd,LPGETIRQ,0);
  close(fd);
  if (irq<0)  { perror(NULL); continue; }
  if (irq>0) printf("irq = %d\n",irq);
  else printf("polling driver used\n");

  printf(" I/O base address is 0x%x for %s\n",LP_B(i),printer);
  if (ioperm(LP_B(i)+1,1,1)<0)
  {
   printf("access to port 0x%x denied\n",LP_B(i)+1);
   continue;
  }
  status=inb(LP_B(i)+1);
  printf(" printer is%sand%sbusy\n",
							(status & LP_PSELECD) ? " online " : " offline ",
							(status & LP_PBUSY) ? " not " : " ");
  printf(" printer is%swaiting for datas\n",(status & LP_PACK) ? " not " : " ");
  printf(" paper is%sempty\n",(status & LP_POUTPA) ? " " : " not ");
  printf(" printer is signalling%serror\n",
									(status & LP_PERRORP) ? " no " : " an ");
 }
}

