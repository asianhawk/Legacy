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
	char version[10];
	char name[20];
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
	int estop;
	int start;
	int stop;
	int partpresent;
	int cyclecomplete;
	int error;
	int ready;
} applicator_pins_t;

typedef struct
{
	m3_application app;
	char *console_dev;
	int console_baud;
	printer_t printer;
	scanner_t *scanners;
	gpio_pin_t *gpio_pins; /* for future use */
	applicator_pins_t applicator_pins;
	int tcp_port; /* -1 if not used */
} m3_settings_t;

extern m3_settings_t Settings;
	
extern int readSettings();

#endif /* _SETTINGS_H */
