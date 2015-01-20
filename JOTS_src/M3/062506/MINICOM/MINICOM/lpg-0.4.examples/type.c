/*
 * TYPE.C - A demonstration program for ncurses.
 *          This program is originally distributed as a part of 
 *          the <Linux Programmers Guide>
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
#include "type.h"


/* My background window has 22 rows and 70 columns. These 
 * two defines are logical coordinates to open the window
 * in the middle of the screen, whatever dimension it has.
 * TYPE_ROW is the beginning row for my program and TYPE_COL 
 * the beginning column. Every call to newwin(...) will check
 * these two defines.
 */
#define TYPE_ROW (int) ((LINES-22)/2)
#define TYPE_COL (int) ((COLS-70)/2)


/*
 * Global variables. I need three windows (one for the red box,
 * one for the frame and one for the real output). Beg is for
 * the output as offset in s[]. Scroll is an enum for calls to
 * scroll_s (I hate to use integers for this).
 * s[] is defined in type.h as:
 * char *s[] = { <here is type.c> };
 */
WINDOW *screen_win;
WINDOW *type_win;
WINDOW *print_win;
int beg=0;
int max_s=340;
enum scroll{UP,DOWN};


/*
 * Local function prototypes.
 * init_type does the ncurses initializing
 * end_type  does the exit for type
 * vdmerase will erase a window with blanks (I had problems
 *          with the ncurses erase functions, so I wrote my
 *          function).
 * scroll_s will do the scrolling (UP or DOWN).
 * clear_line will send space characters from the current 
 *            cursor position up to
 *            the length from int.
 * winsizech() is a signalhandler for SIGWINCH. this signal
 *             will be caught when the screen size has changed
 *             (resized xterm e.g.).
 */
void init_type();
void end_type();
void vdmerase(WINDOW *);
void scroll_s(int);
void clear_line(int, WINDOW *);
void winsizech();



/*
 * The main function.
 */
void main ()
{
bool okloop=TRUE;

 /* ncurses initializing */
 init_type();

 /* set signal handler for SIGWINCH */
 signal(SIGWINCH,winsizech);

/* ok, the screen has a white window with a box and a red
 * border around it.
 * Our main loop. Wait for pressed keys. When the user pressed
 * 'q' or 'Q' then exit the program. On cursor down or 'd' or 'D'
 * scroll the text in the window one line down, on cursor up or
 * 'u' or 'U' one line up. On every other key do nothing.
 */
 while(okloop){
   switch(getch()){
     case KEY_UP:
     case 'u':
     case 'U': scroll_s(UP);
               break;
     case KEY_DOWN:
     case 'd':
     case 'D': scroll_s(DOWN);
               break;
     case 'q':
     case 'Q': okloop=FALSE;
               break;
     default : break;
   }
 }
 /* clean uop end exit */
 end_type();
 exit(0);
}




/*
 *  init_type initialize the ncurses data structures, create the
 *            needed windows, print them on screen and set some
 *            usefull options.
 *
 */
void init_type()
{
int i;

/* don't forget this when using ncurses!!! */
 if(!(stdscr=initscr())){
   fprintf(stderr,"type: initscr() failed\n\n");
   exit (1);
 }

/* check screen size. we need 22 lines and 70 columns */
 if ((LINES<22)||(COLS<70)){
   fprintf(stderr,"type: screen to small\n\n");
   endwin(); exit (1);
 }

/* now we open our three windows */
 if (!(screen_win=newwin(22,70,TYPE_ROW,TYPE_COL))){
   fprintf(stderr,"type: can't open screen_win\n\n");
   endwin(); exit (1);
 }

 if (!(type_win=newwin(20,68,TYPE_ROW+1,TYPE_COL+1))){
   fprintf(stderr,"type: can't open type_win\n\n");
   endwin(); exit (1);
 }

 if (!(print_win=newwin(18,66,TYPE_ROW+2,TYPE_COL+2))){
   fprintf(stderr,"type: can't open type_win\n\n");
   endwin(); exit (1);
 }

/* ok windows are opened, check for color */
 start_color();
 if (has_colors()){
   /* fine we have colors, define color_pairs for foreground
    * and background colors
    */
   init_pair(1,COLOR_BLUE,COLOR_WHITE);
   init_pair(2,COLOR_WHITE,COLOR_RED);
   init_pair(3,COLOR_BLACK,COLOR_WHITE);
   /* now use the defined color_pairs for the windows */
   wattrset(screen_win,COLOR_PAIR(2));
   wattrset(type_win,COLOR_PAIR(1));
   wattrset(print_win,COLOR_PAIR(3));
 }
 else{
   /* ohh, no color (maybe a vt100 or xterm). ok we use b&w
    * attributes instead
    */
   wattrset(screen_win,A_REVERSE);
   wattrset(type_win,A_BOLD);
   wattrset(print_win,A_NORMAL);
 }

/* now clear the windows to get the attributes visible
 * (in memory not on the screen).
 */
 vdmerase(screen_win);
 vdmerase(type_win);
 vdmerase(print_win);

/* wborder with spaces will only paint the border red */
 wborder(screen_win,' ',' ',' ',' ',' ',' ',' ',' ');

/* and now the real box characters */
 box(type_win,0,0);

/* some additional information.
 * ACS_* character and german 'umlaute' are not printed
 * correctly in ncurses 1.8.5 and the terminfo from
 * slackware 2.0, so I don't use them
 */
 mvwaddstr(type_win,0,29,"[ type.c ]");
 mvwaddstr(screen_win,21,1,"[Q,q]-Quit   ");
 waddch(screen_win,ACS_DARROW);
 waddstr(screen_win,"[D,d]-Scroll down one line   ");
 waddch(screen_win,ACS_UARROW);
 waddstr(screen_win,"[U,u]-Scroll up one line");


/* it's time to print the strings on the screen */
 for(i=beg;i<19;i++)
   mvwaddnstr(print_win,i,0,s[i],66);


/* Now the terminal options.
 * noecho the user typed characters, don't wait for input,
 * make cursor invisible, don't wait for carriage return
 * while waiting for input and enable the keypad
 */
 noecho();
 nodelay(stdscr,FALSE);
 cbreak();
 curs_set(FALSE);
 keypad(stdscr,TRUE);


/* all window manipulations are done in the memory
 * now we are going to get in on the physical screen.
 * wnoutrefresh does everything in the memory, too, and
 * doupdate will paint our screen!!!
 */
 wnoutrefresh(screen_win);
 wnoutrefresh(type_win);
 wnoutrefresh(print_win);
 doupdate();
}



/* The user wants to terminate the program, ok clean up.
 * Delete all opened windows and make the cursor visible.
 * At least call endwin.
 */
void end_type()
{
 delwin(screen_win);
 delwin(type_win);
 delwin(print_win);
 curs_set(TRUE);
 endwin();
}



/*
 * With 'erase' and 'werase' from ncurses I don't get white
 * spaces on black background (any idea why?), so I use 
 * my own erase function.
 * This goes deep in the structure WINDOW, so I don't recommend
 * to use this function!!!
 */
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



/*
 * This function will scroll the lines on the screen, using
 * ncurses (and the optimization in ncurses).
 * UP and DOWN are enum's, beg is an offset for printing
 * s[].
 * If we scroll down (wscrl(win,positive integer) the last
 * line on screen is empty and we print the new one to
 * the screen (the same on scrolling up with the first line).
 * Clear_line prints spaces from the current cursor position
 * up to the end of the line.
 */
void scroll_s(int scroll)
{
WINDOW *win=print_win;

 if((scroll==DOWN)&&(beg<=(max_s-18))){
     beg++;
     scrollok(win, TRUE);
     wscrl(win, +1);
     scrollok(win, FALSE);
     mvwaddnstr(win,17,0,s[beg+17],66);
     clear_line(66,win);
 }
 else if((scroll==UP)&&(beg>0)){
     beg--;
     scrollok(win, TRUE);
     wscrl(win, -1);
     scrollok(win, FALSE);
     mvwaddnstr(win,0,0,s[beg],66);
     clear_line(66,win);
 }
 wrefresh(win);
return;
}



/*
 * Clear_line prints spaces from the current cursor position
 * up to length
 */
void clear_line(int length,WINDOW *win)
{
int i,y_start,x_start;
   getyx(win,y_start,x_start);
   for(i=x_start+1; i<=length;i++)
     waddch(win,' ');
return;
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
 end_type();
 init_type();
 signal(SIGWINCH,winsizech);
}
