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


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <ctype.h>
#include <fcntl.h>
#include <sys/kd.h>
#include <sys/ioctl.h>

extern float name_to_val(char *tune);

main(int argc, char **argv)
{
int fd=1,tone,duration;
float frequency;
char sounddata[20];

 if (argc>1)
 {
  fprintf(stderr,"I need sounddatas from stdin !\n");
  exit(-1);
 }

 if (strncmp(getenv("TERM"), "xterm", 5) == 0)
 {
  fd = open("/dev/console", O_WRONLY);
  if (fd < 0) fd = 1; /* stdout */
 }

 while (fgets(sounddata,20,stdin)!=NULL)
 {

  if (isalpha(*sounddata))
  {
   strtok(sounddata,"\t, "); /* delimiters for frequency and length */
   frequency=name_to_val(sounddata);
   sscanf(strtok(NULL,"\r"),"%d",&duration);
  }
  else sscanf(sounddata,"%f%*c%d",&frequency,&duration);

  if (frequency!=0.0) tone=1190000/frequency;/*calculate value for pc speaker*/
  else tone=0;
  ioctl(fd,KIOCSOUND,tone); 
  usleep(duration*1000); /* duration in ms */

 }
 ioctl(fd,KIOCSOUND,0); /* sound off */
  
 if (fd>2) close(fd); /* console */

 exit(0);
}


