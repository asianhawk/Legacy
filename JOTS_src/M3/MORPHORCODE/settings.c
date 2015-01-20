#include <stdlib.h>
#include <string.h>


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
    printf("number of scanners is %d\n", numberOfScanners);
	
	/* For each scanner, read in all the settings */
	for (i=1; i<=numberOfScanners; i++)
	{
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

		printf("description = %s\n", s->description);
		printf("trigger_cmd = %s\n", s->trigger_cmd);
		printf("dev = %s\n", s->dev);
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

	/* Applicator IO Pins 
	 * These pins should be entered into the ini file as integers representing the 
	 * input or output pin number.  For example, "estop = 3;" means E-Stop is the 
	 * OUT3 pin, since E-Stop is an output.  Likewise, "cyclecomplete = 2;" means Cycle Complete
	 * is the IN2 pin. */
	Settings.applicator_pins.estop = iniparser_getint(d, "applicatorio:estop", -1);
	Settings.applicator_pins.start = iniparser_getint(d, "applicatorio:start", -1);
	Settings.applicator_pins.stop = iniparser_getint(d, "applicatorio:stop", -1);
	Settings.applicator_pins.partpresent = iniparser_getint(d, "applicatorio:partpresent", -1);
	Settings.applicator_pins.cyclecomplete = iniparser_getint(d, "applicatorio:cyclecomplete", -1);
	Settings.applicator_pins.error = iniparser_getint(d, "applicatorio:error", -1);
	Settings.applicator_pins.ready = iniparser_getint(d, "applicatorio:ready", -1);
		
	/* Debug Information */	
	printf("Settings.console_dev = %s\n", Settings.console_dev);
	printf("Settings.console_baud = %d\n", Settings.console_baud);
	printf("Settings.printer_dev = %s\n", Settings.printer.dev);
	printf("Settings.tcp_port = %d\n", Settings.tcp_port);
	
	/*
	 * Should be calling freedict, but I do not want to have to make a copy of all the settings for storage
	 *
	 *   iniparser_freedict(d);
	 */

	return 0;
}
