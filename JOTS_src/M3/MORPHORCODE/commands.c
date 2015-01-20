#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>
#include <assert.h>
 
#include "commands.h"
#include "input.h"
#include "csv.h"
#include "settings.h"
#include "serial.h"
#include "gpio.h"

#define RESULT_OK "OK\n"

#define CMD_SUFFIX '\n'

#define MAX_CMD_LENGTH 255

#define CMD_HOST_INQUIRY "!HI"
#define CMD_HOST_VERSION "!HV"
#define CMD_HOST_CONFIG "!HC"
#define CMD_BEGIN_PASSTHRU "!PT"
#define CMD_ABORT_PASSTHRU "!AP"
#define CMD_READ_SCANNER "!RS"
#define CMD_VIEW_PRINTER_STATUS "!PS"
#define CMD_SET_DIO "!DO"
#define CMD_GET_DIO "!DI"
#define CMD_EXIT "!XX"
#define E_MISSING_PARAMETERS "MISSING PARAMETERS\n"
#define E_NO_RESPONSE "NO RESPONSE\n"
#define E_INVALID_SCANNER "INVALID SCANNER\n"
#define E_INVALID_DEVICE "INVALID DEVICE\n"
#define E_INVALID_SCAN "INVALID SCAN\n"
#define E_PORT_NOT_AVAILABLE "PORT NOT AVAILABLE\n"
#define E_NOREAD "NOREAD\n"
#define SCANNER_BUFFER_SIZE 1024


static int
setDIOBit(int filedes, int bit, int value /*1 or 0*/, int pulse)
{
	assert(value <= 1 && value >= 0);
	
	
	
	write(filedes, RESULT_OK, strlen(RESULT_OK));
	return 0;
}

static int
getDIOBits(int filedes, int bit, int bitlength)
{
	return 0;
}

static int 
readFromScanner (int filedes, const char *description, const char *preDelay, const char *timeout, const char *expectedValue, const char *retries)
{
	scanner_t *s;
	struct timespec requested_time, remaining;
	int i;
	char scanbuf[SCANNER_BUFFER_SIZE];
	
	assert(description != NULL); assert(preDelay != NULL); assert(timeout != NULL);
	assert(expectedValue != NULL); assert(retries != NULL);
	
	/* Get the scanner */
	for (s=Settings.scanners; s != NULL; s = s->next)
		if (strcmp(s->description, description) == 0)
			break;
		
	/* If scanner doesn't exist... */
	if (s == NULL)
	{
		write (filedes, E_INVALID_SCANNER, strlen(E_INVALID_SCANNER));
		return -1;
	}
	
	/* Verify the port is open */
	if (s->fd <= 0)
	{
		write (filedes, E_PORT_NOT_AVAILABLE, strlen(E_PORT_NOT_AVAILABLE));
		return -1;
	}
	
	/* Pause the program for preDelay number of milliseconds */
	if (preDelay != NULL)
	{
		long milliseconds = strtol(preDelay, NULL, 10);

		/* Fill time structure according to pre_delay... */
		requested_time.tv_sec = (int) (milliseconds / 1000);
		requested_time.tv_nsec = (milliseconds % 1000) * 1000 * 1000;
		
		nanosleep (&requested_time, &remaining);
	}
	
	int r = strtol(retries, NULL, 10); 	/* Retries */
	int t = strtol(timeout, NULL, 10); 	/* Timeout */
	
	/* Loop through r number of retries, or until we get data back */
	for (i=0; i<r; i++)
	{
		/* Send the trigger command */
		write (s->fd, s->trigger_cmd, strlen(s->trigger_cmd));
		write (s->fd, "\n", 1);
		
		/* Wait for data to be available for t milliseconds.
		 * It is important to manually set the scanner's timeout to a bit
		 * smaller of a timeout.		 */
		if (1==inputTimeout(s->fd, t))
		{
			memset(scanbuf, 0, SCANNER_BUFFER_SIZE);
			if (0==readLine(s->fd, scanbuf, SCANNER_BUFFER_SIZE))
			{
				if (0==strlen(expectedValue))
				{
					/* If expectedValue is not given, just return the scanned value */
					write(filedes, scanbuf, strlen(scanbuf));
					write(filedes, "\n", 1); /* must send the line feed, because it was stripped in readLine() */
					return 0;
				}
				else /* we must compare the scanned value to expectedValue */
				{
					if (0==strcmp(scanbuf, expectedValue))
					{
						write(filedes, RESULT_OK, strlen(RESULT_OK));
						return 0;
					}
					else
					{
						write(filedes, E_INVALID_SCAN, strlen(E_INVALID_SCAN));
						return 0;
					}
				}
			}
		}
	}
	
	/* If we get here, it's a no-read */
	write(filedes, E_NOREAD, strlen(E_NOREAD));
	
	return 0;
}

static int
passthroughMode (int filedes, const char *dev)
{
	char buf[4];
	int i;
	int stop = -1;
	char *target_dev;
	int target_fd = -1;
	fd_set active_fd_set;
	fd_set read_fd_set;

	assert(dev != NULL);

	memset (buf, 0, 4);

	// Select the physical port based on the logical port name specified
	if (strcmp (dev, "PRINTER") == 0)
	{
		target_dev = Settings.printer.dev;
		target_fd = Settings.printer.fd;
	}
	else if (strcmp (dev, "COM1") == 0)
	{
		target_dev = "/dev/ttyS0";
	}
	else if (strcmp (dev, "COM2") == 0)
	{
		target_dev = "/dev/ttyS1";
	}
	else if (strcmp (dev, "COM3") == 0)
	{
		target_dev = "/dev/ttyS2";
	}
	else if (strcmp (dev, "COM4") == 0)
	{
		target_dev = "/dev/ttyS3";
	}
	else
	{
		scanner_t *s;
	
		/* Determine if the requested device is a
       	 * scanner, so we can re-use the file descriptor */
		s = Settings.scanners;
		while (s != NULL)
		{
			if (strcmp(s->dev, dev) == 0)
			{
				target_dev = s->dev;
				target_fd = s->fd;
				s = NULL;
			}
			else
			{
				s = s->next;
			}
		}
	}
	
	/*
	 * Open file descriptor (baud 9600), if not already open 
	 */
	if (-1 == target_fd)
	{
		target_fd = openPort(target_dev, 9600, (CS8 | CLOCAL | CREAD));
		if (-1 == target_fd)
		{
			write (filedes, E_INVALID_DEVICE, strlen (E_INVALID_DEVICE));
			return -1;
		}
	}

	/*
	 * Initialize the set of active sockets. 
	 */
	FD_ZERO (&active_fd_set);
	FD_SET (target_fd, &active_fd_set);
	FD_SET (filedes, &active_fd_set);

	while (-1 == stop)
	{
		int result;
		char c;

		/*
		 * Block until input arrives on one or more active file descriptor. 
		 * select returns 0 if timeout, 1 if input available, -1 if error. 
		 */
		read_fd_set = active_fd_set;
		if (select (FD_SETSIZE, &read_fd_set, NULL, NULL, NULL) < 0)
		{
			perror ("select2");
			exit (EXIT_FAILURE);
		}

		/*
		 * Service all the file descriptors with input pending. 
		 */
		for (i = 0; i < FD_SETSIZE; ++i)
		{
			if (FD_ISSET (i, &read_fd_set))
			{
				// take bytes from one port and write to the other
				result = readChar (i, &c);
				if (result == 0)
				{
					buf[0] = buf[1];
					buf[1] = buf[2];
					buf[2] = c;

					if (strcmp (buf, CMD_ABORT_PASSTHRU) == 0)
					{
						write (filedes, RESULT_OK, strlen(RESULT_OK));
						stop = 1;
					}
					
					if (i == target_fd)
						write (filedes, &c, 1);
					else
						write (target_fd, &c, 1);

				}
			}
		}
	}

	return 0;
}

static int 
viewPrinterStatus(int filedes)
{
	const char *statusCmd = "~HS\n";
	
	char inbuf[83];
	
	/* Send the Host Status Return command */
	write(Settings.printer.fd, statusCmd, strlen(statusCmd));
	
	/* The Zebra will return three lines of text.  Each line is prefixed with an STX and
	 * suffixed with an ETX, CR, LF combination.
	 */
	if (1==inputTimeout(Settings.printer.fd, 1000))
	{
		char result[1000];
		
		memset(result, 0, 1000);
		memset(inbuf, 0, 83);
		
		/* Read everything the printer sent back (it will send exactly 82 characters) */
		readAll(Settings.printer.fd, inbuf, 82);
		
		/* Get what we need */
		if (inbuf[5] == '1') strcat(result, "+++PAPEROUT\n");
		if (inbuf[7] == '1') strcat(result, "+++PAUSE\n");
		if (inbuf[43] == '1') strcat(result, "+++HEADUP\n");
		if (inbuf[45] == '1') strcat(result, "+++RIBBONOUT\n");
		strcat(result, "OK\n");
		
		write(filedes, result, strlen(result));
	}
	else
	{
		write(filedes, E_NO_RESPONSE, strlen(E_NO_RESPONSE));
		return 0;
	}

	return 0;
}

static int
viewHostConfiguration(int filedes)
{
	char xml[4096]; memset (xml, 0, 4096);
	
	strcat (xml, "<?xml version=\"1.0\"?>\n");
	strcat (xml, "<M3>\n");
	strcat (xml, "<Application Name=\"appname\" Version=\"0.1\">\n");
	strcat (xml, "<Settings>\n");
	strcat (xml, "</Settings>\n");
	strcat (xml, "<PortMapping>\n");
	strcat (xml, "<Port Name=\"Console\" Dev=\"/dev/null\">\n");
	strcat (xml, "<Port Name=\"Printer\" Dev=\"/dev/null\">\n");
	strcat (xml, "</PortMapping>\n");
	strcat (xml, "<DIOMapping>\n");
	strcat (xml, "</DIOMapping>\n");
	strcat (xml, "</M3>\n");
	strcat (xml, RESULT_OK);
	
	write (filedes, xml, strlen(xml));
	
	return 0;
}

static int
determineCommand (char *buf, int filedes)
{
	char *command;

	assert(buf != NULL);
	
	csvscanline(buf); /* parse the command line */
	
	command = csvfield(0);
	
	if (strcmp (command, CMD_HOST_INQUIRY) == 0)
	{
		write (filedes, RESULT_OK, strlen (RESULT_OK));
	}
	else if (strcmp (command, CMD_GET_DIO) == 0)
	{
		getDIOBits(filedes, 1, 1);
	}
	else if (strcmp (command, CMD_SET_DIO) == 0)
	{
		setDIOBit(filedes, 1, 1, 1);
	}
	else if (strcmp (command, CMD_HOST_CONFIG) == 0)
	{
		viewHostConfiguration(filedes);
	}
	else if (strcmp (command, CMD_HOST_VERSION) == 0)
	{
		char reply[100];
		
		sprintf(reply, "%s,%s\nOK\n", Settings.app.name, Settings.app.version);
		write (filedes, reply, strlen(reply));
	}
	else if (strcmp (command, CMD_BEGIN_PASSTHRU) == 0)
	{
		/* CMD_BEGIN_PASSTHRU
		 * Passthrough mode allows the controlling terminal to access a port 
		 * by referencing it's physical (COM1) or logical (PRINTER) name. 
		 */
		
		if (csvfield(1) == NULL)
		{
			write (filedes, E_MISSING_PARAMETERS, strlen (E_MISSING_PARAMETERS));
			return 0;
		}
		passthroughMode (filedes, csvfield(1));
	}
	else if (strcmp (command, CMD_READ_SCANNER) == 0)
	{
		/* CMD_READ_SCANNER
		 * The read scaner command triggers the serial scanner by referencing 
		 * the name of the scanner you wish to trigger, along with a timeout and other parameters
		 */
		
		int i;
		for (i=1; i<6; i++)
		{
			if (csvfield (i) == NULL)
			{
				write (filedes, E_MISSING_PARAMETERS, strlen(E_MISSING_PARAMETERS));
				return 0;
			}
		}
		
		readFromScanner (filedes, csvfield(1), csvfield(2), csvfield(3), csvfield(4), csvfield(5));
	}
	else if (strcmp (command, CMD_VIEW_PRINTER_STATUS) == 0)
	{
		viewPrinterStatus(filedes);
	}
	else if (strcmp (command, CMD_EXIT) == 0)
	{
		exit (EXIT_SUCCESS);
	}

	return 0;
}

int
processCommand(int filedes)
{
	char buf[1000];
	int result;
	
	memset(buf, 0, 1000);
	
	if ((result = readLine(filedes, buf, 1000)) == -1)
		return -1;
	
	if (0 == result && 0 != buf[0])
	{
		result = determineCommand(buf, filedes);
	}
	
	return 0;
}
