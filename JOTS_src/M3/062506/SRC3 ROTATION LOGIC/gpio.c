#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <math.h>


#include <ctype.h>
#include <inttypes.h>
#include <time.h>

//#include "gpio.h"
#include "settings.h"
#include "linux/arcom/aim104.h"
#include "aimDIO16.h"


#include <libdevmem.h>

static uint16_t inputs[] = {IN0, IN1, IN2, IN3, IN4, IN5, IN6, IN7 };
static uint32_t outputs[] = {OUT0, OUT1, OUT2, OUT3, OUT4, OUT5, OUT6, OUT7 };

static unsigned short nOutput;

static char *binString(int value)
{
    static char bin[9];
    int index;

    for (index=0;index<8;index++)
    {
        if (value & 128)
            bin[index] = '1';
        else
            bin[index] = '0';

        value = value << 1;
    }
    bin[8] = 0x00;

    return(bin);
}

unsigned int getInputs()
{
int fd;

unsigned char inputs;

	/* open */
	if( (fd=open("/dev/arcom/aim104/in16/0\000" , O_RDONLY ))<0 ) {
		fprintf( stderr, "%s\n", strerror( errno ) );
		exit( 1 );
	}

        if( read(fd, &inputs, 1)<0 ) {
            fprintf( stderr, "read: %s\n", strerror( errno ) );
            exit( 1 );
        }

	if( close(fd)<0 )
	{
	      fprintf( stderr, "close: %s\n", strerror( errno ) );
              exit( 1 );
	}

	return (unsigned)inputs;

}



void setOutputs(uint32_t mask)
{
int fd;
	
	printf("mask = %d\n",mask);
//	if (mask!=0)
//	{	
		nOutput=(nOutput|(1<<mask))&0xFF;
		
//	}
//	else
//		nOutput=nOutput|0x01;

	/* open */
	if( (fd=open( "/dev/arcom/aim104/out16/0\000", O_RDWR ))<0 ) {
		fprintf( stderr, "%s: \n",  strerror( errno ) );
		exit( 1 );
	}


	/* enable outputs */
	
	if( ioctl(fd, AIM104_OUT16_IOC_ENABLE, 1)<0 ) {
		fprintf( stderr, "enable ioctl: %s\n", strerror( errno ) );
		exit( 1 );
	}


	if( write(fd, &nOutput, 2)<0 ) {
		fprintf( stderr, "write: %s\n", strerror( errno ) );
		exit( 1 );
	}

	/* close */
 	if( close(fd)<0 ) {
		fprintf( stderr, "close: %s\n", strerror( errno ) );
		exit( 1 );
	}
	printf("Output (ON) = %d\n",nOutput);
}

void clearOutputs(uint32_t nBitID)
{
int fd;
unsigned int nMask=0;
int nCount;


	for (nCount=0;nCount<8;nCount++)
	{
		if (nCount!=(int)nBitID)
			nMask=nMask+(1<<nCount);
	}
	nOutput=nOutput&nMask;

	/* open */
	if( (fd=open( "/dev/arcom/aim104/out16/0\000", O_RDWR ))<0 ) {
		fprintf( stderr, "%s: \n",  strerror( errno ) );
		exit( 1 );
	}


	/* enable outputs */
	if( ioctl(fd, AIM104_OUT16_IOC_ENABLE, 1)<0 ) {
		fprintf( stderr, "enable ioctl: %s\n", strerror( errno ) );
		exit( 1 );
	}


	if( write(fd, &nOutput, 2)<0 ) {
		fprintf( stderr, "write: %s\n", strerror( errno ) );
		exit( 1 );
	}

	/* close */
 	if( close(fd)<0 ) {
		fprintf( stderr, "close: %s\n", strerror( errno ) );
		exit( 1 );
	}
	printf("Output (OFF) = %d\n",nOutput);
}

void setOutputsPulse(uint32_t mask, int pulse)
{
	struct timespec requested_time, remaining;
		
	setOutputs(mask&0x07);
	
	if (pulse > 0)
	{
		/* delay for pulse milliseconds */
		/* Fill time structure according to pulse... */
		requested_time.tv_sec = (int) (pulse / 1000);
		requested_time.tv_nsec = (pulse % 1000) * 1000 * 1000;
		
		nanosleep (&requested_time, &remaining);
		
		clearOutputs(mask);
	}
}

void clearOutputsPulse(uint32_t mask, int pulse)
{
	struct timespec requested_time, remaining;
		
	clearOutputs(mask&0x07);
	
	if (pulse > 0)
	{
		/* delay for pulse milliseconds */
		/* Fill time structure according to pulse... */
		requested_time.tv_sec = (int) (pulse / 1000);
		requested_time.tv_nsec = (pulse % 1000) * 1000 * 1000;
		
		nanosleep (&requested_time, &remaining);
		
		setOutputs(mask);
	}
}

char* getPins()
{
    uint16_t read_result;
    static char* pins;
	
	read_result = getInputs();
	pins = binString(read_result);
	
    return (pins);
}

uint32_t translatePin(char *pinp)
{
	uint32_t pin = -1; /* remains the same if no match */
	
	/* determine which pin it is */
	if (strcmp(pinp, CYCLE_COMPLETE_BIT) == 0)
	{
		pin = inputs[Settings.applicator_pins.cyclecomplete];
	}
	else if (strcmp(pinp, ERROR_BIT) == 0)
	{
		pin = inputs[Settings.applicator_pins.error];
	}
	else if (strcmp(pinp, READY_BIT) == 0)
	{
		pin = inputs[Settings.applicator_pins.ready];
	}
	else if (strcmp(pinp, ESTOP_BIT) == 0)
	{
		pin = outputs[Settings.applicator_pins.estop];
	}
	else if (strcmp(pinp, START_BIT) == 0)
	{
		pin = outputs[Settings.applicator_pins.start];
	}
	else if (strcmp(pinp, STOP_BIT) == 0)
	{
		pin = outputs[Settings.applicator_pins.stop];
	}
	else if (strcmp(pinp, DEMAND_BIT) == 0)
	{
		pin = outputs[Settings.applicator_pins.demand];
	}

	else if (strcmp(pinp, PARTPRESENT_BIT) == 0)
	{
		pin = inputs[Settings.applicator_pins.partpresent];
	}
	else if (strcmp(pinp, FINGERTRAP_BIT) == 0)
	{
		pin = inputs[Settings.applicator_pins.fingertrap];
	}

	else if (pinp[0] == 'I' && pinp[1] == 'N')
	{
		pin = pinp[2] - (int)'0';
		pin = inputs[pin];
	}
	else if (pinp[0] == 'O' && pinp[1] == 'U' && pinp[2] == 'T')
	{
		pin = pinp[3] - (int)'0';
		pin = outputs[pin];
	}
	
	return (pin);
}

char *getPin(uint16_t pin)
{
	uint16_t read_result;
	
	assert (pin > 0);
	
	read_result = getInputs();
	
	if (read_result & pin)
		return ("1");
	/* else */
	return ("0");
}
