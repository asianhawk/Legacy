#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "settings.h"
#include "input.h"
#include "serial.h"
#include "commands.h"

static int serial_console_fd = -1; 
static int tcp_listener_fd = -1;

static int
makeSocket (int port)
{
	int sock;
	struct sockaddr_in name;
	int yes = 1;

	/*
	 * Create the socket. 
	 */
	sock = socket (PF_INET, SOCK_STREAM, 0);
	if (sock < 0)
	{
		perror ("socket");
		exit (EXIT_FAILURE);
	}

	/*
	 * lose the pesky "address already in use"
	 */
	if (-1 == setsockopt (sock, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof (int)))
	{
		perror ("setsockopt");
		exit (1);
	}

	/*
	 * Give the socket a name. 
	 */
	name.sin_family = AF_INET;
	name.sin_port = htons (port);
	name.sin_addr.s_addr = htonl (INADDR_ANY);
	if (bind (sock, (struct sockaddr *) &name, sizeof (name)) < 0)
	{
		perror ("bind");
		exit (EXIT_FAILURE);
	}

	return sock;
}

static int
openFileDescriptors()
{
	scanner_t *s;

	/* Connect to each of the scanners */
	s = Settings.scanners;
	while (s != NULL)
	{
		s->fd = openPort (s->dev, 9600, (CS8 | CLOCAL | CREAD));
		printf ("scanner '%s' is open on file descriptor %d\n", s->description, s->fd);
		s = s->next;
	}
	
	/* Connect to the serial console, if applicable */
	if (strlen (Settings.console_dev) > 0)
	{
		serial_console_fd = openPort (Settings.console_dev, Settings.console_baud, (CS8 | CLOCAL | CREAD));
		if (-1 == serial_console_fd)
		{
			perror ("unable to open console\n");
			exit (EXIT_FAILURE);
		}
		printf ("serial console '%s' is open on file descriptor %d\n", Settings.console_dev, serial_console_fd);
	}
	
	/* Connect to the printer */
	Settings.printer.fd = openPort (Settings.printer.dev, Settings.printer.baud, (CS8 | CLOCAL | CREAD));
	printf("printer '%s' is open on file descriptor %d\n", Settings.printer.dev, Settings.printer.fd);
	
	/* Connect to the socket */
	if (Settings.tcp_port >= 0)
	{
		/*
	 	* Create the socket and set it up to accept connections. 
	 	*/
		tcp_listener_fd = makeSocket (Settings.tcp_port);
		if (listen (tcp_listener_fd, 1) < 0)
		{
			perror ("listen");
			exit (EXIT_FAILURE);
		}
		printf ("tcp port %d is open on file descriptor %d\n", Settings.tcp_port, tcp_listener_fd);
	}
	
	return 0;
}


int main()
{
	fd_set active_fd_set;
	fd_set read_fd_set;
	struct timeval timeout;
	int i;
	struct sockaddr_in clientname;
	size_t size;

	readSettings();
	
	openFileDescriptors();

	/*
	 * Initialize the set of active sockets (consoles only). 
	 */
	FD_ZERO (&active_fd_set);
	if (tcp_listener_fd > 0)
		FD_SET (tcp_listener_fd, &active_fd_set);
	if (serial_console_fd > 0)
		FD_SET (serial_console_fd, &active_fd_set);
	
	/*
	 * Initialize the timeout data structure. 
	 */
	timeout.tv_sec = (unsigned int) 10;
	timeout.tv_usec = 0;
	
	while (1)
	{
		/*
		 * Block until input arrives on one or more active consoles. 
		 * select returns 0 if timeout, 1 if input available, -1 if error. 
		 */
		read_fd_set = active_fd_set;
		if (select (FD_SETSIZE, &read_fd_set, NULL, NULL, &timeout) < 0)
		{
			perror ("select");
			exit (EXIT_FAILURE);
		}

		/*
		 * Service all the sockets with input pending. 
		 */
		for (i = 0; i < FD_SETSIZE; ++i)
		{
			if (FD_ISSET (i, &read_fd_set))
			{
				if (i == tcp_listener_fd)
				{
					/*
					 * Connection request on listening tcp socket. 
					 */
					int new;
					size = sizeof (clientname);
					new = accept (tcp_listener_fd, (struct sockaddr *) &clientname, &size);
					if (new < 0)
					{
						perror ("accept");
						exit (EXIT_FAILURE);
					}
					fprintf (stderr, "Server: connect from host %s, port %hd.\n", 
						inet_ntoa (clientname.sin_addr), ntohs (clientname.sin_port));
					FD_SET (new, &active_fd_set);
				}
				else if (i == serial_console_fd)
				{
					/*
					 * Data arriving on serial console. 
					 */
					processCommand (i);
					
				}
				else
				{
					/*
					 * Data arriving on an already-connected socket. 
					 */
					if (processCommand (i) == -1)
					{
						fprintf (stderr, "Server: disconnect from host %s, port %hd.\n", 
							inet_ntoa (clientname.sin_addr), ntohs (clientname.sin_port));
						close (i);
						FD_CLR (i, &active_fd_set);
					}
					
				}
			}
		}		// for	
	}			// while
	
	return (0);
}
