#ifndef _AIMDIO16_H
#define _AIMDIO16_H


#define IN0 (1<<0)
#define IN1 (1<<1)
#define IN2 (1<<2)
#define IN3 (1<<3)
#define IN4 (1<<4)
#define IN5 (1<<5)
#define IN6 (1<<6)
#define IN7 (1<<7)

#define OUT0 0
#define OUT1 1
#define OUT2 2
#define OUT3 3
#define OUT4 4
#define OUT5 5
#define OUT6 6
#define OUT7 7

// M3 Inputs
#define PARTPRESENT_BIT "PPRESENT"
#define CYCLE_COMPLETE_BIT "CC"
#define ERROR_BIT "ERR"
#define READY_BIT "RDY"
#define FINGERTRAP_BIT "FINGERTRAP"

// M3 Outputs
#define ESTOP_BIT  "ESTOP"
#define START_BIT "START"
#define STOP_BIT "STOP"
#define DEMAND_BIT "DEMAND"

extern char* getPins();
extern char* getPin(uint16_t pin);
extern uint32_t translatePin(char *pinp);
extern void setOutputs(uint32_t mask);
extern void clearOutputs(uint32_t mask);
extern void clearOutputsPulse(uint32_t mask, int pulse);
extern void setOutputsPulse(uint32_t mask, int pulse);



#endif /* _AIMDIO16_H */
