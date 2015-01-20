#include <stdio.h>
#include <fcntl.h>
//#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char** argv) {
	//variable declarations
	int fd = 0;
	char file[] = "/dev/watchdog";

	//open the file
	fd = open(file, O_RDWR | O_CREAT);

	//process
	if(fd == -1) {
	    printf("Error opening /dev/watchdog\n");
	    return 0;
	}
	else {		//we opened the watchdog
	    while(1) {
		//reset the watchdog
//		printf("resetting watchdog\n");
		write(fd, "\0", 1);

		//now wait a while or do some other stuff
		//if we do not loop again before 60 seconds has passes we will reboot
		//this will prevent a reboot
		usleep(50000000);

		//alternatively, you can comment out the above and use this to see a reboot happen
		//usleep(70000000);
	    }
	}
	return 0;
}
