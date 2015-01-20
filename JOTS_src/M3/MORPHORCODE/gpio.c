#include "gpio.h"

#include <libdevmem.h>

char* getPins()
{
    libdevmem_handle h;
    uint16_t read_result;
    static char pins[9];
    int i, j;
    
    /* libdevmem_read_uint16() returns a two-byte value (16-bits duh). For some reason, 
	 * I couldn't get it to read just one byte, which is all we need.  The manual hints that the 
	 * processor is not designed to interface with 8-bit peripherals, so one must read 16 bits
 	 * at a time.  However, in this case, only the least significat byte contains the data.  We 
	 * will zero the most significant byte to make things less confusing.
     */
    h = libdevmem_open(GPIO_ADDRESS, MAP_SIZE);
    read_result = libdevmem_read_uint16(h, 0);
	libdevmem_close(h);
	
    read_result = read_result << 8; // these two lines zero the most sig. byte
    read_result = read_result >> 8;

	j = 1;
	
	// Loop through each of the 8 input pins and fill the char array
    for(i=0; i<8; i++)
    {
		if(read_result & j)
		    pins[i] = '1';
        else
            pins[i] = '0';

        j = j << 1;
    }
    bin[8] = '\0';

    return (pins);
}

char *getPin(char *pinp)
{
	static char val[2];
	char *pins;
	int pin;
	
	/* determine which pin it is */
	if (strcmp(pinp, CYCLE_COMPLETE_BIT) == 0)
	{
		pin = Settings.applicator_pins.cyclecomplete;
	}
	else if (strcmp(pinp, ERROR_BIT) == 0)
	{
		pin = Settings.applicator_pins.error;
	}
	else if (strcmp(pinp, READY_BIT) == 0)
	{
		pin = Settings.applicator_pins.ready;
	}
	else
	{
		
		return (NULL);
	}
	
	pins = getPins();
	
	val[0] = pins[pin];
	val[1] = '\0';
	
	return (val);
	
}
