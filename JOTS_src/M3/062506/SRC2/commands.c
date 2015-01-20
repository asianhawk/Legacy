#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>
#include <assert.h>
#include <ctype.h>
#include <signal.h>
#include <fcntl.h>
 
#include "commands.h"
#include "input.h"
#include "csv.h"
#include "settings.h"
#include "serial.h"
//#include "gpio.h"
#include "aimDIO16.h"

#include "PrintAndApply.h"

#define DEBUG_LOGIC   
#define ERROR_TRAP	0
#define PRINTERERROR	'1'

#define RESULT_OK "OK\n"
#define RESULT_NOT_OK "Applicator Error\n"

#define CMD_SUFFIX '\n'


#define MAX_CMD_LENGTH 255

#define CMD_PRINT_APPLY "!PA"
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
#define CMD_KILL "!KILL"
#define CMD_UPDATE "!UPDATE"

#define E_MISSING_PARAMETERS "MISSING PARAMETERS\n"
#define E_NO_RESPONSE "NO RESPONSE\n"
#define E_INVALID_SCANNER "INVALID SCANNER\n"
#define E_INVALID_DEVICE "INVALID DEVICE\n"
#define E_INVALID_SCAN "INVALID SCAN\n"
#define E_PORT_NOT_AVAILABLE "PORT NOT AVAILABLE\n"
#define E_NOREAD "NOREAD\n"
#define E_INVALID_PIN "INVALID PIN\n"
#define E_INVALID_BIT_LENGTH "INVALID BIT LENGTH\n"
#define E_APPLICATOR_NOT_READY "APPLICATOR NOT READY\n"

#define TRACE_DEMAND_PAF_ART_OFF "PA = False, Applicator Ready = True, Demand Signal Off"
#define TRACE_DEMAND_PAF_ARF_OFF "PA = False, Applicator Ready = False, Demand Signal Off"

#define TRACE_DEMAND_PAT_CCT_OFF "PA = True, CC= True, Demand Signal Off"
#define TRACE_DEMAND_PAT_CCF_OFF "PA = True, CC= FALSE, Demand Signal Off"

#define TRACE_DEMAND_PAF_OFF "PA = False, Demand Signal On"

#define TRACE_DEMAND_PAT_ARF "PA = TRUE, Applicator Ready = FALSE"
#define TRACE_DEMAND_PAT_ART "PA = TRUE, Applicator Ready = TRUE"

#define SCANNER_BUFFER_SIZE 100

#define  STX  2;
#define  EOT  4;	

int m_blnPrintAndApply;
int m_blnCycleComplete;
int m_blnLabelDemand;

#define SHELL "/bin/sh"

//#define TRUE 1;
//#define FALSE 0;

static uint16_t inputs[] = {IN0, IN1, IN2, IN3, IN4, IN5, IN6, IN7 };
//static uint32_t outputs[] = {OUT0, OUT1, OUT2, OUT3, OUT4, OUT5, OUT6, OUT7 };


extern void LogEvents (char *strEvent);


static int DownloadFile(int filedes)
{
 //,*fh2;
FILE *fh;
char buffer[1];
//int buffer_character;
        printf("Begin Download File\n");
	
	
//	fh2 = fdopen(filedes,"rb");
	if (fh == (FILE *)0)
	{
	   printf("Error Creating File");
	  return 0;	
	}
	 
	
	
	// wait for start
	
	do
	{
  	  if (read (filedes, buffer, 1)<=0)
          {
	      printf("Waiting For Start  \n");
	  }
	  else
	  	printf("Input Received  = %d\n",*buffer);
	  
	  sleep(1);
	  
	}while (strcmp(buffer,"\0x02")!=0);	
	printf("Begin File Transfer\n");
	
	
/*	while (getc(fh2)!=4)
	{
		if ((buffer_character=getc(fh2))!=EOF) 
		{  
		  putc(buffer_character,fh);
		  printf(" Received Data = %d\n",buffer_character);
		}
		else
		  break;

	}
       printf("End File Transfer\n");
*/
       fclose(fh);	
//       fclose(fh2);  
	  	
   return 1;	
}


static int
setDIOBit(int filedes, char* bitptr, char* valueptr, char* pulseptr)
{
	//struct timespec requested_time, remaining;
uint32_t pin,nCCpin;
long pulse;
char *result;
int nTraceEnabled;
	
	assert(valueptr != NULL);
	assert(bitptr != NULL);
	assert(pulseptr != NULL);
	
	
	pin = translatePin(bitptr);
	nTraceEnabled = Settings.nTraceEnabled;
	if ((nTraceEnabled!=0)&&(nTraceEnabled!=1))
           nTraceEnabled=0; 
	if (pin < 0)
	{
		write (filedes, E_INVALID_PIN, strlen(E_INVALID_PIN));
		return 0;
	}
	
	pulse = strtol(pulseptr, NULL, 10);
	
	if (*valueptr == '1')
	{	
		setOutputsPulse(pin, pulse);
	}
	else
	{
		
		if (strcmp(bitptr, DEMAND_BIT)==0)
		{
		   if (m_blnPrintAndApply==1)
                   {
		       m_blnPrintAndApply=0;
		       nCCpin = inputs[Settings.applicator_pins.cyclecomplete];
		       result = getPin(nCCpin);	
		       if (*result=='1')
		       {		
		 	 if (nTraceEnabled) LogEvents(TRACE_DEMAND_PAT_CCT_OFF); 	
		         clearOutputsPulse(pin, pulse);
		       }

		       nCCpin = inputs[Settings.applicator_pins.ready];
		       result = getPin(nCCpin);	
		       if (*result=='1')
		       {		
	 	         if (nTraceEnabled) LogEvents(TRACE_DEMAND_PAT_ART);
		       }
		       else	
		       {
	 	         if (nTraceEnabled) LogEvents(TRACE_DEMAND_PAT_ARF);
		         clearOutputsPulse(pin, pulse);

		       }	

		   }
		   else
		   {
		       nCCpin = inputs[Settings.applicator_pins.ready];
		       result = getPin(nCCpin);	

 		       clearOutputsPulse(pin, pulse);
		       m_blnPrintAndApply=0; 
		      
		       if (*result=='1')
		       {		
	 	         if (nTraceEnabled) LogEvents(TRACE_DEMAND_PAF_ART_OFF);
		       }
		       else	
	 	         if (nTraceEnabled) LogEvents(TRACE_DEMAND_PAF_ARF_OFF);

		   }
		
                } 
 	        else
		{
 	              clearOutputsPulse(pin, pulse);
		}

	}	
	write(filedes, RESULT_OK, strlen(RESULT_OK));
	return 0;
}



static int
getDIOBits(int filedes, char *bit, char *bitlength)
{
char *result;

	assert (bit != NULL);
	assert (bitlength != NULL);
	
	if (*bitlength == '1')
	{
		/* Get the pin number */
		int pin;
		pin = translatePin(bit);
		
		/* Verify pin is valid */
		if (pin < 0)
		{
			write (filedes, E_INVALID_PIN, strlen(E_INVALID_PIN));
			return 0;
		}

		result = getPin(pin);

	}
	else if (*bitlength == '8')
	{
		result = getPins();
	}
	else /* bit length must be either 1 or 8 */
	{
		write (filedes, E_INVALID_BIT_LENGTH, strlen (E_INVALID_BIT_LENGTH));
		return 0;
	}
	
	write (filedes, result, strlen (result));

	return 0;
}

static int 
readFromScanner (int filedes, const char *description, const char *preDelay, const char *timeout, const char *expectedValue, const char *retries)
{
	scanner_t *s;
	struct timespec;
	int i;
	char scanbuf[SCANNER_BUFFER_SIZE];
	char strReturnMessage[SCANNER_BUFFER_SIZE+10];
	char strTriggerCmd[15];
	char strTriggerOff[15];
	int nTraceEnabled;

	nTraceEnabled = Settings.nTraceEnabled;

	strcpy(strTriggerCmd,"\x16T\r\000");
	strcpy(strTriggerOff,"\x16U\r\000");

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
	else 
	{
		s->fd = openPort (s->dev, 9600, (CS8 | CLOCAL | CREAD));
		printf ("\tScanner [%s] \t\t\tDevice ID [%d]\n", s->dev, s->fd);

		if (nTraceEnabled==1) LogEvents("Scanner Open\n"); 
		
	}
	
	
	/* Verify the port is open */
	if (s->fd <= 0)
	{
		write (filedes, E_PORT_NOT_AVAILABLE, strlen(E_PORT_NOT_AVAILABLE));
		return -1;
	}
	
	/* Pause the program for preDelay number of milliseconds */
	
	int r = strtol(retries, NULL, 10); 	/* Retries */
	int t = strtol(timeout, NULL, 10); 	/* Timeout */
	
	/* Loop through r number of retries, or until we get data back */
	for (i=0; i<r; i++)
	{
		/* Send the trigger command */
		if (strcmp(s->description,"S2")==0)
		{
		   
		   
		   printf("Trigger = %s\n", strTriggerCmd);			
		   write (s->fd, strTriggerCmd, strlen(strTriggerCmd));
		}
		else
		{
		    write (s->fd, s->trigger_cmd, strlen(s->trigger_cmd));
		}

		
		
		
		if (nTraceEnabled==1) LogEvents("After Trigger"); 
		
		usleep(strtol(preDelay, NULL, 10)*1000);
		
		/* Wait for data to be available for t milliseconds.
		 * It is important to manually set the scanner's timeout to a bit
		 * smaller of a timeout.		 */
		if (1==inputTimeout(s->fd, t))
		{
			memset(scanbuf, '\000', SCANNER_BUFFER_SIZE);
			memset(strReturnMessage,'\000',SCANNER_BUFFER_SIZE+10);
			if (0==readScanner(s->fd, scanbuf, SCANNER_BUFFER_SIZE))
			{
				if (0==strlen(expectedValue))
				{
					/* If expectedValue is not given, just return the scanned value */
					write(filedes, scanbuf, strlen(scanbuf));
					strcat(scanbuf,"\n");
					if (nTraceEnabled==1) LogEvents(scanbuf); 

					if (strcmp(s->description,"S2")==0)
					 {
		   
		   				printf("Trigger Off \n");
					 	  write (s->fd, strTriggerOff, strlen(strTriggerOff));
					  }
					close (s->fd);
					return 0;
				}
				else /* we must compare the scanned value to expectedValue */
				{
					printf("Scanned Value = [%s], Expected Value = [%s]\n",scanbuf,expectedValue);
					if (0==strcmp(scanbuf, expectedValue))
					{
//						strcpy(strReturnMessage,RESULT_OK);
//						strcat(strReturnMessage,":");
//						strcat(strReturnMessage,scanbuf);
						
						write(filedes, scanbuf, strlen(scanbuf));
						close (s->fd);
						return 0;
					}
					else
					{
						if (i>=(r-1))
						{
							strcpy(strReturnMessage,E_INVALID_SCAN);
							write(filedes, strReturnMessage, strlen(strReturnMessage));
						}
						else
						{
						  if (strcmp(s->description,"S2")==0)
						  {
		   
		   					printf("Trigger Off \n");
					   write (s->fd, strTriggerOff, strlen(strTriggerOff));
						  }

						}
//
						close (s->fd);
						return 0;
					}
				}
			}
		}
		else
		{
		   if (strcmp(s->description,"S2")==0)
		   {
		     printf("Trigger Off \n");
		     write (s->fd, strTriggerOff, strlen(strTriggerOff));
						  
		   }
                }
	}
	
	if (strcmp(s->description,"S2")==0)
	{
	  
		printf("Trigger Off \n");
		write (s->fd, strTriggerOff, strlen(strTriggerOff));
	}

	/* If we get here, it's a no-read */
	write(filedes, E_NOREAD, strlen(E_NOREAD));
	close (s->fd);
	
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

		struct timeval timeout;
		
		/* Initialize the timeout data structure. */
		timeout.tv_sec = (long) 0;
		timeout.tv_usec = 500000;
	
		/* sleep for 500 milliseconds */	
		select (1, NULL, NULL, NULL, &timeout);			
		
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
int nOffset;
int nTraceEnabled;	
	char *command;
	assert(buf != NULL);
	
	csvscanline(buf); /* parse the command line */
	
	command = csvfield(0);
	nOffset=0;
	nTraceEnabled=Settings.nTraceEnabled;
	while (command[nOffset]!='\000')
	{
		// convert to uppercase , no need to check
		command[nOffset]=toupper(command[nOffset]);
		nOffset++;
	}
	printf("New Command [%s]\n",command);
	if (strcmp (command, CMD_HOST_INQUIRY) == 0)
	{
		write (filedes, RESULT_OK, strlen (RESULT_OK));
	}
	else if (strcmp (command, CMD_PRINT_APPLY) == 0)
	{
		
		if(PrintAndApplyLabel(filedes, csvfield(1), csvfield(2))==-1)
		{
			m_blnPrintAndApply=0;
			if (nTraceEnabled) LogEvents("ERROR Print Cycle Begins");
			return 0;
		
		};
		m_blnPrintAndApply=1;
		if (nTraceEnabled) LogEvents("Print Cycle Begins");
		write (filedes, RESULT_OK, strlen (RESULT_OK));
	}
	else if (strcmp (command, CMD_GET_DIO) == 0)
	{
		int i;
		for (i=1; i<=2; i++)
		{
			if (csvfield (i) == NULL)
			{
				write (filedes, E_MISSING_PARAMETERS, strlen(E_MISSING_PARAMETERS));
				return 0;
			}
		}
		
		getDIOBits(filedes, csvfield(1), csvfield(2));
	}
	else if (strcmp (command, CMD_SET_DIO) == 0)
	{
		int i;
		for (i=1; i<=3; i++)
		{
			if (csvfield (i) == NULL)
			{
				write (filedes, E_MISSING_PARAMETERS, strlen(E_MISSING_PARAMETERS));
				return 0;
			}
		}
		
		setDIOBit(filedes, csvfield(1), csvfield(2), csvfield(3));
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
		//write (filedes, RESULT_OK, strlen (RESULT_OK));
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

	else if (strcmp (command, CMD_KILL) == 0)
	{
       		pid_t pid;
		pid = fork();
		if (pid==0)
		{
		   execl(SHELL,SHELL,"-c","//home//arcom//usercfg.sh\0",NULL);
		  _exit(EXIT_FAILURE);
		}
		else if (pid<0)
		  _exit(EXIT_FAILURE);
		else
//		  if (waitpid(pid,&status,0)!=-pid)
		  _exit(0);
 
		kill(getpid(),SIGINT);
	}
	else if (strcmp (command, CMD_EXIT) == 0)
	{
       		pid_t pid;
		pid = fork();
		if (pid==0)
		{
		   execl(SHELL,SHELL,"-c","//home//arcom//usercfg.sh\0",NULL);
		  _exit(EXIT_FAILURE);
		}
		else if (pid<0)
		  _exit(EXIT_FAILURE);
		else
//		  if (waitpid(pid,&status,0)!=-pid)
		  _exit(0);
 
		kill(getpid(),SIGINT);
	}

	else if (strcmp (command, CMD_UPDATE) == 0)
	{
//		kill(getpid(),SIGINT);
		write (filedes, RESULT_OK, strlen (RESULT_OK));
		DownloadFile(filedes);
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
	
	return result;
}
