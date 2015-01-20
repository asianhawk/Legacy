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
 This is like all programs in the Linux Programmer's Guide meant
 as a simple practical demonstration.
 It can be used as a base for a real terminal program.
*/

#include <termios.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/signal.h>

#define BAUDRATE B115200
#define MODEMDEVICE "/dev/ttyS4"
#define ENDMINITERM 2 /* ctrl-b to quit miniterm */

#define _POSIX_SOURCE 1 /* POSIX compliant source */

#define FALSE 0
#define TRUE 1

volatile int STOP=FALSE; 

void child_handler(int s)
{
   STOP=TRUE;
}

main()
{
int fd,c;
struct termios oldtio,newtio,oldstdtio,newstdtio;
struct sigaction sa;
 printf("here1\n");
/* 
  Open modem device for reading and writing and not as controlling tty
  because we don't want to get killed if linenoise sends CTRL-C.
*/
 fd = open(MODEMDEVICE, O_RDWR | O_NOCTTY);
 if (fd <0) {perror(MODEMDEVICE); exit(-1); }
 
 tcgetattr(fd,&oldtio); /* save current modem settings */
 printf("here2\n");
 
/* 
  Set bps rate and hardware flow control and 8n1 (8bit,no parity,1 stopbit).
  Also don't hangup automatically and ignore modem status.
  Finally enable receiving characters.
*/
 newtio.c_cflag = BAUDRATE | CRTSCTS | CS8 | CLOCAL | CREAD;
 
/*
 Ignore bytes with parity errors and make terminal raw and dumb.
*/
 newtio.c_iflag = IGNPAR;
 
/*
 Raw output.
*/
 newtio.c_oflag = 0;
 
/*
 Don't echo characters because if you connect to a host it or your
 modem will echo characters for you. Don't generate signals.
*/
 newtio.c_lflag = 0;
 
/* blocking read until 1 char arrives */
 newtio.c_cc[VMIN]=1;
 newtio.c_cc[VTIME]=0;
 
/* now clean the modem line and activate the settings for modem */
 tcflush(fd, TCIFLUSH);
 tcsetattr(fd,TCSANOW,&newtio);

/*
  Strange, but if you uncomment this command miniterm will not work
  even if you stop canonical mode for stdout. This is a linux bug.
*/
 tcsetattr(1,TCSANOW,&newtio); /* stdout settings like modem settings */
 
/* next stop echo and buffering for stdin */
 tcgetattr(0,&oldstdtio);
 tcgetattr(0,&newstdtio); /* get working stdtio */
 newstdtio.c_lflag &= ~(ICANON | ECHO);
 tcsetattr(0,TCSANOW,&newstdtio);

/* terminal settings done, now handle in/ouput */
 switch (fork())
 {
  case 0: /* child */
   /* user input */
   close(1); /* stdout not needed */
   for (c=getchar(); c!= ENDMINITERM ; c=getchar()) write(fd,&c,1);
   tcsetattr(fd,TCSANOW,&oldtio); /* restore old modem setings */
   tcsetattr(0,TCSANOW,&oldstdtio); /* restore old tty setings */
   close(fd);
   exit(0); /* will send a SIGCHLD to the parent */
   break;
  case -1:
   perror("fork");
   tcsetattr(fd,TCSANOW,&oldtio);
   close(fd);
   exit(-1);
  default: /* parent */
   close(0); /* stdin not needed */
   sa.sa_handler = child_handler;
   sa.sa_flags = 0;
   sigaction(SIGCHLD,&sa,NULL); /* handle dying child */
   while (STOP==FALSE) /* modem input handler */
   {
    read(fd,&c,1); /* modem */
    write(1,&c,1); /* stdout */
   }
   wait(NULL); /* wait for child to die or it will become a zombie */
   break;
 }
}
