/*
 * Screen.C - A demonstration program for ncurses.
 *            This program is originally distributed as a part of 
 *            the <Linux Programmers Guide>
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


#include <ncurses/ncurses.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>


void init_screen();
void end_screen();
void vdmerase(WINDOW *);
void usage();
void winsizech();

WINDOW *leftwin;
WINDOW *rightwin;
int todo;

void main (int argc, char *argv[])
{
 if(strcmp(argv[1],NULL)>=0){
   usage();
 }
 todo=atoi(argv[1]);
 signal(SIGWINCH,winsizech);

 init_screen();

 while(!getch())
   ;

 end_screen();
exit(0);
}



void init_screen()
{
int mycols=0, myrows=0;
int leftcol=0, leftrow=0, rightcol=0, rightrow=0;

 if(!(stdscr=initscr())){
   fprintf(stderr,"type: initscr() failed\n\n");
   exit(1);
 }

 switch(todo){
   case 1:
            myrows=22;
            mycols=77;
            leftrow=((LINES-myrows)/2);
            leftcol=((COLS-mycols)/2);
            rightrow=leftrow;
            rightcol=leftcol;
            break;
   case 2:
            myrows=LINES-2;
            mycols=(COLS-6)/2;
            leftrow=1;
            leftcol=2;
            rightrow=1;
            rightcol=4+mycols;
            break;
   case 3:
            myrows=(LINES/2+LINES/4);
            mycols=(COLS/2+COLS/4);
            leftrow=((LINES-myrows)/2);
            leftcol=((COLS-2)-mycols)/2;
            mycols=(mycols/2);
            rightrow=leftrow;
            rightcol=leftcol+2+mycols;
            break;
   default: usage();
 }

 if (!(leftwin=newwin(myrows,mycols,leftrow,leftcol))){
   fprintf(stderr,"fileview: can't open dir_win\n\n");
   endwin(); exit(1);
 }

 if (!(rightwin=newwin(myrows,mycols,rightrow,rightcol))){
   fprintf(stderr,"fileview: can't open file_win\n\n");
   endwin(); exit (1);
 }

 start_color();
 if (has_colors()){
   init_pair(1,COLOR_WHITE,COLOR_RED);
   wattrset(leftwin,COLOR_PAIR(1));
   wattrset(rightwin,COLOR_PAIR(1));
 }
 else{
   wattrset(leftwin,A_REVERSE);
   wattrset(rightwin,A_REVERSE);
 }

 vdmerase(leftwin);
 vdmerase(rightwin);

 noecho();
 nodelay(stdscr,FALSE);
 cbreak();
 curs_set(FALSE);
 keypad(stdscr,TRUE);

 mvwprintw(leftwin,1,1,"LINES: %i,  COLS: %i",LINES,COLS);
 mvwprintw(leftwin,2,1,"Nlines: %i, Ncols: %i",myrows,mycols);
 mvwprintw(leftwin,3,1,"Begy: %i,    Begx: %i",leftrow,leftcol);
 mvwaddstr(leftwin,5,1,"Press any key to quit");

 mvwprintw(rightwin,1,1,"LINES: %i,  COLS: %i",LINES,COLS);
 mvwprintw(rightwin,2,1,"Nlines: %i, Ncols: %i",myrows,mycols);
 mvwprintw(rightwin,3,1,"Begy: %i,    Begx: %i",rightrow,rightcol);
 mvwaddstr(rightwin,5,1,"Press any key to quit");

 wnoutrefresh(leftwin);
 wnoutrefresh(rightwin);
 doupdate();
}



void end_screen()
{
 delwin(leftwin);
 delwin(rightwin);
 curs_set(TRUE);
 endwin();
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


void usage()
{
 printf("\nusage: screen[1|2|3]\n");
 printf("\n       1 = opens a window with 22 lines and 70 columns in the");
 printf("\n           middle of the screen.");
 printf("\n       2 = opens 2 windows with one line free on top and bottom");
 printf("\n           and two columns free on the left and on the right side");
 printf("\n           of the screen and two columns free between them.");
 printf("\n       3 = opens two windows, where for each window the number of"); 
 printf("\n           lines is 75%% from LINES and the number of columns is");
 printf("\n           43%% from COLS");
 printf("\n\n");
 exit(0);
}



/*
 * Signal handler for SIGWINCH. When this signal is received,
 * we clean up all windows (delwin), then call endwin and
 * reinitialize the whole program. it's not fine but it works.
 * For 'real' programs we need some better functions I think.
 *
 */
void winsizech()
{
 end_screen();
 init_screen();
 signal(SIGWINCH,winsizech);
}
