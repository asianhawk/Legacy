#include <termios.h>
extern int openPort (const char *dev, int bps, tcflag_t cflag);
extern int openMCPort (const char *dev, int bps, tcflag_t cflag);
