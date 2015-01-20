#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
//#include <sys/time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>
#include <assert.h>
 
#define DEBUG_PA	1

#include "input.h"
//#include "csv.h"
#include "settings.h"
#include "serial.h"
//#include "gpio.h"
#include "aimDIO16.h"
#include "PrintAndApply.h"

#define E_APPLICATOR_NOT_READY "APPLICATOR NOT READY\n"
#define E_PRINTERTEMPLATE_ZERO_LENGTH "Printer Template Length Not Defined\n"
#define E_PRINTERTEMPLATE_NOT_FOUND "Printer Template Not Found\n"
#define E_PARTPRESENT_TIMEOUT "Part Present Timeout\n"
#define E_CYCLECOMPLETE_TIMEOUT "Cycle Complete Timeout\n"
#define E_INVALID_DEVICE "INVALID DEVICE\n"
#define E_STATUS_NOTDEFINED "Return Status Not Defined\n"


#define GENERAL_WAITING_FOR_PARTPRESENT 	"Waiting For Part Present Timeout\n"
#define GENERAL_WAITING_FOR_CYCLECOMPLETE 	"Waiting For Cycle Complete\n"

static uint16_t inputs[] = {IN0, IN1, IN2, IN3, IN4, IN5, IN6, IN7 };
static uint32_t outputs[] = {OUT0, OUT1, OUT2, OUT3, OUT4, OUT5, OUT6, OUT7 };


void StartApplicator();
void ResetApplicator();
int WaitForPartPresent(int filedes);
int WaitForCycleComplete();
void ApplyLabelDemand(int nDemand);
int PollForAsyncInputs(int filedes);

#define TRUE	1
#define FALSE   0

//static int serial_console_fd = -1; 
//static int tcp_listener_fd = -1;


extern int processCommand(int filedes);
extern void LogEvents (char *strEvent); 

int PrintAndApplyLabel(int filedes, char* status, char* bytes)
{
int nTraceEnabled;
char strPurgePrinterBuffer[]="~JA";

	nTraceEnabled = Settings.nTraceEnabled;

	if (nTraceEnabled==1)
	{
	
		printf ("Begin PrintAndApplyLabel\n");
		printf("Template = [%s]\n\n",status);
		printf("Template = [%s]\n\n",bytes);
		
	}



	if (status==NULL)
	{
	    if (nTraceEnabled==1) LogEvents(E_PRINTERTEMPLATE_NOT_FOUND); 	
	    return -1;	
	}
	
	if (bytes==NULL)
	{
	    if (nTraceEnabled==1) LogEvents(E_PRINTERTEMPLATE_ZERO_LENGTH); 		
	    return -1;	
	}
	
	

	
	
	Settings.printer.fd = openPort(Settings.printer.dev, 9600, (CS8 | CLOCAL | CREAD));
	if (-1 == Settings.printer.fd)
	{

		if (nTraceEnabled==1) LogEvents(E_INVALID_DEVICE);
		if (nTraceEnabled==1) LogEvents ("End PrintAndApplyLabel [Error]\n");
		return -1;
	}	
	
	write(Settings.printer.fd, strPurgePrinterBuffer, strlen(strPurgePrinterBuffer));
	if (nTraceEnabled==1) LogEvents(strPurgePrinterBuffer); 
	
	usleep(Settings.nPPurgeDelay*1000);	
	if (nTraceEnabled==1) LogEvents("AFter ~JA Command"); 

	write(Settings.printer.fd, bytes, strlen(bytes));
	if (nTraceEnabled==1) LogEvents(bytes); 

	ApplyLabelDemand(TRUE);
	return 1;
	
	if (Settings.nFingerTrapEnabled==1)
	{ 

		if (nTraceEnabled==1) LogEvents("Finger TRAP Enable Waiting For CycleComplete");
		if (WaitForCycleComplete()==0) 
		{
			if (nTraceEnabled==1) LogEvents("WaitForCycleComplete() = TRUE");
			return 1;
		}
	}
	else
		if (nTraceEnabled==1) LogEvents("FingerTrap Not Required");

	if (nTraceEnabled==1) printf ("End PrintAndApplyLabel [Normal]");
	close(Settings.printer.fd);	
	return 1;
	
}

void StartApplicator()
{
	if (DEBUG_PA==1)   printf ("Begin StartApplicator\n");
	setOutputsPulse(outputs[Settings.applicator_pins.estop],1);
	setOutputsPulse(outputs[Settings.applicator_pins.start],1);


	
	if (DEBUG_PA==1) printf ("End StartApplicator\n");
}

void ResetApplicator()
{
	if (DEBUG_PA==1)   printf ("Begin ResetApplicator\n");
	clearOutputsPulse(outputs[Settings.applicator_pins.estop],1);
	clearOutputsPulse(outputs[Settings.applicator_pins.start],1);
	clearOutputsPulse(outputs[Settings.applicator_pins.stop],1);
	clearOutputsPulse(outputs[Settings.applicator_pins.demand],1);
	if (DEBUG_PA==1)   printf ("Reset ResetApplicator\n");

}

int WaitForPartPresent(int filedes)
{
	if (DEBUG_PA==1)   printf ("Begin WaitForPartPresent\n");

char *retval;
int nMaxTimeOut;
int pin;

	pin = inputs[Settings.applicator_pins.partpresent];

	nMaxTimeOut=0;
	do
	{
	
	/* sleep for 500 milliseconds */
		write (filedes, GENERAL_WAITING_FOR_PARTPRESENT, strlen(GENERAL_WAITING_FOR_PARTPRESENT));
		
		retval = getPin(pin);
		if (DEBUG_PA==1)
		printf ("PIN[%d] Value = [%d]\n",pin,*retval);			
		nMaxTimeOut++;
		if (nMaxTimeOut>=Settings.nPrintAndApplyTimeOut)
		{
//			write (filedes, E_PARTPRESENT_TIMEOUT, strlen(E_PARTPRESENT_TIMEOUT));
			if (DEBUG_PA==1)   printf ("End WaitForPartPresent Error\n");

			return -1;
		
		}
		
		
	}while(*retval!='0');		// sinking inputs means logical true=zero
	

	if (DEBUG_PA==1)   printf ("End WaitForPartPresent\n");

	return 1;

}

int WaitForCycleComplete()
{
	if (DEBUG_PA==1)   printf ("Begin WaitForCycleComplete\n");

char *retval;
int nMaxTimeOut;
int nMaxFingerTrapTimeOut;
int pin;
int nFingerTrap;
int blnCont;
int nResetDemandToTrue;
int nTraceEnabled;
char reply[100];
		
	nTraceEnabled = Settings.nTraceEnabled;

	pin = inputs[Settings.applicator_pins.cyclecomplete];
	nFingerTrap = inputs[Settings.applicator_pins.fingertrap];
	nMaxTimeOut=0;
	nMaxFingerTrapTimeOut=0;
	blnCont=TRUE;
	nResetDemandToTrue=FALSE;
	do
	{
		if(Settings.nFingerTrapEnabled)
		{
		   blnCont=TRUE;	
	 	   retval = getPin(nFingerTrap);
	 	   if (nTraceEnabled==1) LogEvents("Wait Cycle Complete Fingertrap Enabled");
		   sleep(3);		
		   while (*retval!='1')
		   {
		      
		      ApplyLabelDemand(FALSE);
		      nResetDemandToTrue=TRUE;
		      retval = getPin(nFingerTrap);
		      usleep(1000);
		      nMaxFingerTrapTimeOut++;
		      memset(reply, 0, 100);	
		      sprintf(reply, "Finger Trap Count = [%d],",nMaxFingerTrapTimeOut);

 	 	      if (nTraceEnabled==1) LogEvents(reply);
		      if (nMaxFingerTrapTimeOut>50)
		      {
		 	if (nTraceEnabled==1) LogEvents("Wait Cycle Complete Fingertrap Enabled -- nMaxFingerTrapTimeOut");
		 	blnCont=FALSE;
		 	break;
		      }				
	  	  }
  		  if (*retval=='1')
		  {
		 	if (nTraceEnabled==1) LogEvents("Wait Cycle Complete Fingertrap Enabled -- FingerTrap Active");
			nResetDemandToTrue=TRUE;

		  }
		  else
		  {
		 	if (nTraceEnabled==1) LogEvents("Wait Cycle Complete Fingertrap Enabled -- FingerTrap NOT Active");


		  }

		}
		else
		{
	 	   if (nTraceEnabled==1) LogEvents("Wait Cycle Complete Fingertrap Not Enabled");

		}
		if (nResetDemandToTrue==TRUE)
	           ApplyLabelDemand(TRUE);


		nMaxFingerTrapTimeOut=0;
		if (blnCont==TRUE)
		{

	 	        if (nTraceEnabled==1) LogEvents("Wait Cycle Complete Cont =  TRUE");
			retval = getPin(pin);
			nMaxTimeOut++;
			if (nMaxTimeOut>=Settings.nPrintAndApplyTimeOut)
			{
				return -1;
			}
		}
		else
		{
	           if (nTraceEnabled==1) LogEvents("Wait Cycle Complete Cont =  FALSE");
 		   
		}		
		
		retval = getPin(pin);

	}while(*retval!='1');		// sinking inputs means logical true=zero
	return 1;

}

void ApplyLabelDemand(int nDemand)
{
	if (DEBUG_PA==1)   printf ("Begin ApplyLabelDemand\n");
	uint32_t pin;
	pin = outputs[Settings.applicator_pins.demand];
	if (nDemand==TRUE)
	   setOutputsPulse(pin,0);
//	   setOutputs(outputs[Settings.applicator_pins.demand]);
	else   
	   clearOutputsPulse(outputs[Settings.applicator_pins.demand],0);
//	  clearOutputs(outputs[Settings.applicator_pins.demand]);
	if (DEBUG_PA==1) printf ("End ApplyLabelDemand\n");
}

int PollForAsyncInputs(int filedes)
{
	fd_set active_fd_set;
	fd_set read_fd_set;
	struct timeval timeout;
	int i;

//	struct sockaddr_in clientname;
//	size_t size;


	 /* Initialize the timeout data structure. 
	 */
	timeout.tv_sec = (unsigned int) 0;
	timeout.tv_usec = 5000;
	
	
	FD_ZERO (&active_fd_set);
	FD_SET (filedes, &active_fd_set);
	

	
	read_fd_set = active_fd_set;
	if (select (FD_SETSIZE, &read_fd_set, NULL, NULL, &timeout) < 0)
	{
		perror ("select");
		exit (EXIT_FAILURE);
	}
	
	/*
		* Service all the sockets with input pending. 
		*/
	for (i = 0; i < FD_SETSIZE; ++i)
	{

		if (FD_ISSET (i, &read_fd_set))
		{
			
			printf("Received  Data \n");
			processCommand (i);
				
			
			
		}
	}
	
	return 1;
}


