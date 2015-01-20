#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "input.h"

int
inputTimeout (int filedes, unsigned int milliseconds)
{
   	fd_set set;
   	struct timeval timeout;
 
   	/* Initialize the file descriptor set. */
   	FD_ZERO (&set);
   	FD_SET (filedes, &set);
 
   	/* Initialize the timeout data structure. */
   	timeout.tv_sec = (long) (milliseconds / 1000);
   	timeout.tv_usec = (milliseconds % 1000) * 1000;
 
   	/* select returns 0 if timeout, 1 if input available, -1 if error. */
   	return (select (FD_SETSIZE, &set, NULL, NULL, &timeout));
}
 
int
readChar (int filedes, char *c)
{
	char buffer[1];
	int nbytes; 

	nbytes = read (filedes, buffer, 1);
	if (nbytes < 0)
	{
		assert(nbytes < 0);
		
		/* Read error. 	 */
		perror ("read");
		exit (EXIT_FAILURE);
	}
	else if (nbytes == 0)
		/* End-of-file.  */
		return -1;
	else
	{
		/* Data read. */
		*c = *buffer;

		return 0;
	}
}

int 
readLine(int filedes, char *line, int maxlen)
{
	char c;
	int result;
	int buflen;
	
	buflen = 0;
	
	memset(line, 0, maxlen);
	
	result = readChar(filedes, &c);
	while (0 == result && 0x0A != c)
	{
		line[buflen++] = c;
		
		if (buflen >= maxlen)
			return -1;
		
		result = readChar(filedes, &c);
	}
	
	if (0 != result)
		return -2;
	
	return 0;
}

ssize_t readAll(int fd, void * data, size_t count) 
{
   	ssize_t bytesRead;
   	char * dataPtr = data;
   	size_t total = 0;

	struct timeval timeout;
	
	/* Initialize the timeout data structure. */
	timeout.tv_sec = (long) 0;
	timeout.tv_usec = 500000;

	/* sleep for 500 milliseconds */	
	select (1, NULL, NULL, NULL, &timeout);			

   	while (count)
	{
    	bytesRead = read(fd, dataPtr, count);
		if (bytesRead < 0)
		{
			data=NULL;
			return -1;
		}
    	dataPtr += bytesRead;
    	count -= bytesRead;
    	total += bytesRead;
   	}

   	return total;
}
