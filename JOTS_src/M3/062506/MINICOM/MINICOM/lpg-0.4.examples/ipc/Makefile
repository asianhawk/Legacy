CC            =  gcc
FLAGS         =  -O6 -Wall -DPOSIX_SOURCE

CFLAGS    =  $(FLAGS) -I.
LDLIBS    =  
LDFLAGS   =  

all:	msgtool semtool shmtool pipe popen1 popen2 popen3 \
	fifoclient fifoserver semstat

msgtool: msgtool.c
	$(CC) $(CFLAGS) -o msgtool msgtool.c $(LDFLAGS) $(LDLIBS)
	strip msgtool

semtool: semtool.c
	$(CC) $(CFLAGS) -o semtool semtool.c $(LDFLAGS) $(LDLIBS)
	strip semtool

semstat: semstat.c
	$(CC) $(CFLAGS) -o semstat semstat.c $(LDFLAGS) $(LDLIBS)
	strip semstat

shmtool: shmtool.c
	$(CC) $(CFLAGS) -o shmtool shmtool.c $(LDFLAGS) $(LDLIBS)
	strip shmtool 

pipe:	pipe.c
	$(CC) $(CFLAGS) -o pipe pipe.c $(LDFLAGS) $(LDLIBS)
	strip pipe

popen1: popen1.c
	$(CC) $(CFLAGS) -o popen1 popen1.c $(LDFLAGS) $(LDLIBS)
	strip popen1 

popen2: popen2.c
	$(CC) $(CFLAGS) -o popen2 popen2.c $(LDFLAGS) $(LDLIBS)
	strip popen2

popen3: popen3.c
	$(CC) $(CFLAGS) -o popen3 popen3.c $(LDFLAGS) $(LDLIBS)
	strip popen3

fifoclient: fifoclient.c
	$(CC) $(CFLAGS) -o fifoclient fifoclient.c $(LDFLAGS) $(LDLIBS)
	strip fifoclient

fifoserver: fifoserver.c
	$(CC) $(CFLAGS) -o fifoserver fifoserver.c $(LDFLAGS) $(LDLIBS)
	strip fifoserver

clean:	
	rm -f *.o core* msgtool semtool shmtool pipe popen[123]

