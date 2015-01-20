#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>
#include <assert.h>

void LogEvents (char *strEvent)
{
//variable declarations
FILE *stream;
struct timeval tv;
struct tm* ptm;
char time_string[40];


	/* Obtain the time of day, and convert it to a tm struct. */
	 gettimeofday (&tv, NULL);
	 ptm = localtime (&tv.tv_sec);
	 /* Format the date and time, down to a single second. */
	 strftime (time_string, sizeof (time_string), "%Y-%m-%d %H:%M:%S", ptm);	

 	 char file[] = "/home/arcom/log.txt";

	//open the file
	stream = fopen( file, "a" );
	fprintf( stream, "%s %s\n",time_string, strEvent );

	fclose(stream);
}


