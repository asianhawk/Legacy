#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <inttypes.h>

#include "settings.h"
#include "iniparse/iniparser.h"

m3_settings_t Settings;

int readSettings()
{ 
	
	scanner_t *s;
    dictionary *d; /* used by the ini parser */
	int i;

    d = iniparser_load("m3.ini");
	
	/* Read in the number of scanner */
	int numberOfScanners = iniparser_getint(d, "scanners:number", 0);
	
	/* For each scanner, read in all the settings */
	for (i=1; i<=numberOfScanners; i++)
	{
		if (i==1)
		{
		  	printf("\t\t============= Scanner Info =====================\n");
			printf("\t Number Of Scanners is %d\n", numberOfScanners);
		
		
		}
		if (Settings.scanners == NULL)
		{
			Settings.scanners  = (scanner_t *) malloc(sizeof(scanner_t));
			memset(Settings.scanners, 0, sizeof(scanner_t));
			s = Settings.scanners;
		}
		else
		{
			s->next = (scanner_t *) malloc(sizeof(scanner_t));
			memset(s->next, 0, sizeof(scanner_t));
			s = s->next;
		}
		
		char desc[100]; memset(desc, 0, 100);
		char trig[100]; memset(trig, 0, 100);
		char dv[100]; memset(dv, 0, 100);
		
		sprintf(desc, "scanners/scanner%d:description", i);
		sprintf(trig, "scanners/scanner%d:trigger", i);
		sprintf(dv, "scanners/scanner%d:dev", i);
		
		s->description = iniparser_getstr(d, desc);
		s->trigger_cmd = iniparser_getstr(d, trig);
		s->dev = iniparser_getstr(d, dv);
		s->next = NULL;

		printf("\t Description = %s\n", s->description);
		printf("\t Trigger Command = %s\n", s->trigger_cmd);
		printf("\t Com Port = %s\n", s->dev);
	} /* scanners */
	
	/* Console Interface Settings */	
	Settings.console_dev = iniparser_getstr(d, "console:dev");
	Settings.console_baud = iniparser_getint(d, "console:baud", 9600);
	Settings.tcp_port = iniparser_getint(d, "tcp:port", 0);
	
	/* Printer Settings */
	Settings.printer.dev = iniparser_getstr(d, "printer:dev");
	Settings.printer.baud = iniparser_getint(d, "printer:baud", 9600);
	Settings.printer.description = iniparser_getstr(d, "printer:description");

	/* App name */
	Settings.app.name = iniparser_getstr(d, "application:name");
	Settings.app.version = iniparser_getstr(d, "application:version");
	Settings.nTraceEnabled = iniparser_getint(d, "application:Trace",0);
	Settings.nFingerTrapEnabled = iniparser_getint(d, "application:EnableFingerTrap",0);

	/* Applicator IO Pins 
	 * These pins should be entered into the ini file as integers representing the 
	 * input or output pin number.  For example, "estop = 3;" means E-Stop is the 
	 * OUT3 pin, since E-Stop is an output.  Likewise, "cyclecomplete = 2;" means Cycle Complete
	 * is the IN2 pin. */
	Settings.applicator_pins.estop = iniparser_getint(d, "applicatorio:estop", 0);
	Settings.applicator_pins.start = iniparser_getint(d, "applicatorio:start", 0);
	Settings.applicator_pins.stop = iniparser_getint(d, "applicatorio:stop", 0);
	Settings.applicator_pins.demand = iniparser_getint(d, "applicatorio:demand", 0);
	
	Settings.applicator_pins.partpresent = iniparser_getint(d, "applicatorio:partpresent", 0);
	Settings.applicator_pins.cyclecomplete = iniparser_getint(d, "applicatorio:cyclecomplete", 0);
	Settings.applicator_pins.error = iniparser_getint(d, "applicatorio:error", 0);
	Settings.applicator_pins.ready = iniparser_getint(d, "applicatorio:ready", 0);
	Settings.applicator_pins.fingertrap = iniparser_getint(d, "applicatorio:fingertrap", 0);


	/* Debug Information */	
	printf("\n\t\t========== DIO Outputs ==========================\n\n");
	
	printf("\tEStop = \t\t[%d]\n", Settings.applicator_pins.estop);
	printf("\tStart = \t\t[%d]\n", Settings.applicator_pins.start);
	printf("\tStop = \t\t\t[%d]\n", Settings.applicator_pins.stop);
	printf("\tApplicator Demand = \t[%d]\n\n", Settings.applicator_pins.demand);
	
	/* Debug Information */	
	printf("\t\t========== DIO Inputs ==========================\n\n");
	
	printf("\tPart Present (To M3) = \t[%d]\n", Settings.applicator_pins.partpresent);
	printf("\tCycle Complete = \t[%d]\n", Settings.applicator_pins.cyclecomplete);
	printf("\tError = \t\t[%d]\n", Settings.applicator_pins.error);
	printf("\tReady = \t\t[%d]\n",Settings.applicator_pins.ready);
	if (Settings.nFingerTrapEnabled==1)
	    printf("\tFingertrap = \t\t[%d]\n\n",Settings.applicator_pins.fingertrap);
	else
	    printf("\tFingertrap = \t\t[%d]\n\n",-1);

	
	// Applicator Variables
	Settings.nSwingDownDelay = iniparser_getint(d, "Applicator:swingdowndelay", 2);
	Settings.nPrintAndApplyTimeOut = iniparser_getint(d, "Applicator:printandapplytimeout", 5);
	Settings.nPrintAndApplyTimeOut = iniparser_getint(d, "Applicator:printandapplytimeout", 5);
	Settings.nPPurgeDelay = iniparser_getint(d, "Applicator:purgedelay", 2000);

	
		
	/* Debug Information */	
	printf("\t\t================= General Info =================\n\n");
	
	printf("\tSettings.console_dev = %s\n", Settings.console_dev);
	printf("\tSettings.console_baud = %d\n", Settings.console_baud);
	printf("\tSettings.printer_dev = %s\n", Settings.printer.dev);
	printf("\tSettings.tcp_port = %d\n", Settings.tcp_port);
	printf("\tSettings.nSwingDownDelay = %d\n", Settings.nSwingDownDelay);
	printf("\tSettings.nPrintAndApplyTimeOut = %d\n", Settings.nPrintAndApplyTimeOut);
	printf("\tSettings.nTraceEnabled = %d\n", Settings.nTraceEnabled);
	printf("\tSettings.nFingerTrapEnabled = %d\n\n", Settings.nFingerTrapEnabled);
	printf("\tSettings.nPPurgeDelay = %d\n\n", Settings.nPPurgeDelay);

	
	/*
	 * Should be calling freedict, but I do not want to have to make a copy of all the settings for storage
	 *
	 *   iniparser_freedict(d);
	 */

	return 0;
}
