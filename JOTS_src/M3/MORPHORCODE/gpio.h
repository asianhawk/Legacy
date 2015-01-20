#ifndef _GPIO_H
#define _GPIO_H

#define MAP_SIZE 4096UL
#define GPIO_ADDRESS 0x14500000

#define IN0 0
#define IN1 1
#define IN2 2
#define IN3 3
#define IN4	4
#define IN5 5
#define IN6 6
#define IN7 7

#define CYCLE_COMPLETE_BIT "CC"
#define ERROR_BIT "ERR"
#define READY_BIT "RDY"

extern char* getPins();
extern bool getPin(char *pinp);

#endif /* _GPIO_H */
