/*****************************************************************************
 Excerpt from "Linux Programmer's Guide - Chapter 6"
 (C)opyright 1994-1995, Scott Burkett
 ***************************************************************************** 
 MODULE: popen2.c
 *****************************************************************************/

#include <stdio.h>

int main(void)
{
	FILE *pipein_fp, *pipeout_fp;
	char readbuf[80];

	/* Create one way pipe line with call to popen() */
	if (( pipein_fp = popen("ls", "r")) == NULL)
	{
		perror("popen");
		exit(1);
	}

	/* Create one way pipe line with call to popen() */
	if (( pipeout_fp = popen("sort", "w")) == NULL)
	{
		perror("popen");
		exit(1);
	}

	/* Processing loop */
	while(fgets(readbuf, 80, pipein_fp))
		fputs(readbuf, pipeout_fp);

	/* Close the pipes */
	pclose(pipein_fp);
	pclose(pipeout_fp);

	return(0);
}
