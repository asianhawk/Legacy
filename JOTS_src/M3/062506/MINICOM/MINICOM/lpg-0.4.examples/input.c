/*
 * INP.C - A demonstration program for ncurses.
 *         This program is originally distributed as a part of
 *         the <Linux Programmers Guide>
 *
 *  AUTHOR: Sven van der Meer (vdmeer@cs.tu-berlin.de)
 *
 *  This program is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License as
 *  published by the Free Software Foundation; either version 2 of
 *  the License,or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include <ncurses/ncurses.h>  /* always needed */
#include <stdlib.h>   /* malloc is defined there */

void vdmerase (WINDOW *); /* for erasing the screen, werase has some probs */

WINDOW *maskwin;
WINDOW *findwin;

void main()
{
char *ptr=(char *)malloc(255); /* the pointer and 255 Byte of memory for it */

 if(!(stdscr=initscr())){  /* don't forget this!!! */
   fprintf(stderr,"inp: initscr() failed\n\n");
   exit (1);
 }
 if (!(findwin=newwin(3,37,9,21))){  /* open a window with error check */
   fprintf(stderr,"inp: can't open findwin\n\n");
   endwin(); exit (1);
 }
 if (!(maskwin=newwin(1,21,10,35))){  /* open a window with error check */
   fprintf(stderr,"inp: can't open maskwin\n\n");
   endwin(); exit (1);
 }

 start_color();  /* check for color and initialize the color or attributes */
 if (has_colors()){
   init_pair(1,COLOR_WHITE,COLOR_RED);
   init_pair(2,COLOR_BLACK,COLOR_WHITE);
   wattrset(findwin,COLOR_PAIR(2));
   wattrset(maskwin,COLOR_PAIR(1));
 }
 else{
   wattrset(findwin,A_REVERSE);
   wattrset(maskwin,A_NORMAL);
 }
 vdmerase(findwin); /* erase the windows, this will show the colors, too */
 vdmerase(maskwin);

 box(findwin,0,0);  /* draw a box around the window */
 mvwaddstr(findwin,1,2,"Inputstring: "); /* print this to the window */

 keypad(stdscr,TRUE);  /* enable keypad and cursor keys */
 timeout(-1);          /* don't wait on input */
 nonl();               /* no newline translation */

 wnoutrefresh(findwin);
 wnoutrefresh(maskwin);
 doupdate();  /* show the windows */

 mvwgetstr(maskwin,0,0,ptr); /* wait for input */

 delwin(maskwin); /* delete the windows and free up the resources */
 delwin(findwin);
 endwin();  /* end ncurses */
 printf("The input was: %s\n",ptr); /* print out the input */
 free(ptr); /* free up the ptr */
 return; /* exit */
}

void vdmerase (WINDOW *win)
{
int  y,x;

 for (y=0;y<=win->_maxy;y++)
   for (x=0;x<=win->_maxx;x++)
     (chtype *)win->_line[y][x]=' '|win->_attrs;
 win->_curx = win->_cury = 0;
 touchwin(win);
return;
}
