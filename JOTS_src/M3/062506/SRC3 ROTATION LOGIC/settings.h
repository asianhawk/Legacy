#ifndef _SETTINGS_H
#define _SETTINGS_H



typedef struct
{
	int fd;
	char *dev;
	char *description;
	char *trigger_cmd;
	void *next;
} scanner_t;
 
typedef struct
{
	int fd;
	char *dev;
	int baud;
	char *description;
} printer_t;


typedef struct
{
	int fd;
	char *dev;
	int baud;
	char *description;
} motioncontroller_t;


typedef struct
{
	char *version;
	char *name;
} m3_application;

/* gpio_pin_t allows other "extra" pins to be used such as light tower, etc. This
 * feature is resurved for future use */
typedef struct
{
	char description[20];
	int pin;
} gpio_pin_t;

typedef struct
{
	// Morphor Outputs
	uint32_t estop;
	uint32_t start;
	uint32_t stop;
	uint32_t demand;
	uint32_t fingertrap;

	
	// Morphor Inputs
	uint32_t partpresent;
	uint32_t cyclecomplete;
	uint32_t error;
	uint32_t ready;

} applicator_pins_t;

typedef struct
{
	m3_application app;
	char *console_dev;
	int console_baud;
	printer_t printer;
	scanner_t *scanners;
	motioncontroller_t mcontroller;
	gpio_pin_t *gpio_pins; /* for future use */
	applicator_pins_t applicator_pins;
	int tcp_port; /* -1 if not used */
	int nSwingDownDelay;
	int nPrintAndApplyTimeOut;
	int nTraceEnabled;
	int nFingerTrapEnabled;
	int nPPurgeDelay;
	int nEnableMotionController;
} m3_settings_t;

extern m3_settings_t Settings;
	
extern int readSettings();

#endif /* _SETTINGS_H */
