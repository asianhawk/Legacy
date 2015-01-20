#include <fcntl.h>
#include <string.h>
#include <stdio.h>

#include "serial.h"

/*
 * List of valid baud rates.
 */

struct speed 
{
   int speed_int;
	int speed_val;
} speeds[] = {
#ifdef B50
     { 50, B50 },
#endif
#ifdef B75
     { 75, B75 },
#endif
#ifdef B110
     { 110, B110 },
#endif
#ifdef B134
     { 134, B134 },
#endif
#ifdef B150
     { 150, B150 },
#endif
#ifdef B200
     { 200, B200 },
#endif
#ifdef B300
     { 300, B300 },
#endif
#ifdef B600
     { 600, B600 },
#endif
#ifdef B1200
     { 1200, B1200 },
#endif
#ifdef B1800
     { 1800, B1800 },
#endif
#ifdef B2000
     { 2000, B2000 },
#endif
#ifdef B2400
     { 2400, B2400 },
#endif
#ifdef B3600
     { 3600, B3600 },
#endif
#ifdef B4800
     { 4800, B4800 },
#endif
#ifdef B7200
     { 7200, B7200 },
#endif
#ifdef B9600
     { 9600, B9600 },
#endif
#ifdef B19200
     { 19200, B19200 }, 
#endif
#ifdef B38400
     { 38400, B38400 },
#endif
#ifdef B57600
     { 57600, B57600 },
#endif
#ifdef B115200
     { 115200, B115200 },
#endif
#ifdef EXTA
     { 19200, EXTA },
#endif
#ifdef EXTB
     { 38400, EXTB },
#endif
#ifdef B230400
     { 230400, B230400 },
#endif
#ifdef B460800
     { 460800, B460800 },
#endif
     { 0, 0 }
};

/********************************************************************
 *
 * Translate from bits/second to a speed_t.
 */

static int translate_speed (int bps)
{
   struct speed *speedp;
   
   if (bps != 0)
   {
     for (speedp = speeds; speedp->speed_int; speedp++)
     {
       if (bps == speedp->speed_int)
       {
         return speedp->speed_val;
       }
     }
     printf("speed %d not supported\n", bps);
   }
   return 0;
}

int
openPort (const char *dev, int bps, tcflag_t cflag)
{
	struct termios newtio;
	int fd;
	speed_t baud;
	
	baud = translate_speed(bps);
	
	fd = open (dev, O_RDWR | O_NOCTTY | O_NDELAY);

	// probably not necessary, but why not?
	memset (&newtio, 0, sizeof (newtio));

	// get the current settings
	// tcgetattr(fd, &newtio);

	// change the settings that we want to change
	newtio.c_cflag = baud | cflag;
	newtio.c_iflag = IGNPAR | ICRNL;
	newtio.c_lflag = ICANON;

	// set the new settings
	tcflush (fd, TCIFLUSH);
	tcsetattr (fd, TCSANOW, &newtio);

	return fd;
}
