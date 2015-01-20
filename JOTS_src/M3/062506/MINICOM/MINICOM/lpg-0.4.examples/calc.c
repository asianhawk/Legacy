/*
 * CALC.C - A demonstration program for ncurses.
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


/* My background window has 22 rows and 70 columns. These 
 * two defines are logical coordinates to open the window
 * in the middle of the screen, whatever dimension it has.
 * TYPE_ROW is the beginning row for my program and TYPE_COL 
 * the beginning column. Every call to newwin(...) will check
 * these two defines.
 */
#define CALC_ROW (int) ((LINES-23)/2)
#define CALC_COL (int) ((COLS-28)/2)
#define ROW 5
#define COL 3
#define LEN 5
#define HEI 3


/*
 * Global variables. I need three windows (one for the red box,
 * one for the frame and one for the real output). Beg is for
 * the output as offset in s[]. Scroll is an enum for calls to
 * scroll_s (I hate to use integers for this).
 * s[] is defined in type.h as:
 * char *s[] = { <here is type.c> };
 */
WINDOW *screen_win;
WINDOW *calc_win;


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
void vdmerase(WINDOW *);
void init_calc();
void end_calc();
void vdmbox(WINDOW *, int, int, int, int, int, int);



/*
 * The main function.
 */
void main ()
{
bool okloop=TRUE;

 /* ncurses initializing */
 init_calc();

/* ok, the screen has a white window with a box and a red
 * border around it.
 * Our main loop. Wait for pressed keys. When the user pressed
 * 'q' or 'Q' then exit the program. On cursor down or 'd' or 'D'
 * scroll the text in the window one line down, on cursor up or
 * 'u' or 'U' one line up. On every other key do nothing.
 */
 while(okloop){
   switch(getch()){
     case 'q':
     case 'Q': okloop=FALSE;
     default : break;
   }
 }
 /* clean uop end exit */
 end_calc();
 exit(0);
}




/*
 *  init_type initialize the ncurses data structures, create the
 *            needed windows, print them on screen and set some
 *            usefull options.
 *
 */
void init_calc()
{
int fg, bg;

/* don't forget this when using ncurses!!! */
 if(!(stdscr=initscr())){
   fprintf(stderr,"calc: initscr() failed\n\n");
   exit (1);
 }

/* check screen size. we need 20 lines and 18 columns */
 if ((LINES<20)||(COLS<18)){
   fprintf(stderr,"calc: screen to small\n\n");
   endwin(); exit (1);
 }

/* now we open our three windows */
 if (!(screen_win=newwin(0,0,0,0))){
   fprintf(stderr,"calc: can't open screen_win\n\n");
   endwin(); exit (1);
 }

 if (!(calc_win=newwin(22,26,CALC_ROW,CALC_COL))){
   fprintf(stderr,"calc: can't open calc_win\n\n");
   endwin(); exit (1);
 }


/* ok windows are opened, check for color */
 start_color();
 if (has_colors()){
   /* fine we have colors, define color_pairs for foreground
    * and background colors
    */
   init_pair(1,COLOR_BLACK,COLOR_BLUE);
   init_pair(2,COLOR_BLACK,COLOR_WHITE);
   init_pair(3,COLOR_WHITE,COLOR_WHITE);
   /* now use the defined color_pairs for the windows */
   wattrset(screen_win,COLOR_PAIR(1));
   wattrset(calc_win,COLOR_PAIR(2));
 }
 else{
   /* ohh, no color (maybe a vt100 or xterm). ok we use b&w
    * attributes instead
    */
   wattrset(screen_win,A_REVERSE);
   wattrset(calc_win,A_BOLD);
 }

/* now clear the windows to get the attributes visible
 * (in memory not on the screen).
 */
 vdmerase(screen_win);
 vdmerase(calc_win);

/* wborder with spaces will only paint the border red */
 wborder(screen_win,' ',' ',' ',' ',' ',' ',' ',' ');

/* and now the real box characters */
 vdmbox(calc_win,COLOR_PAIR(3)|A_STANDOUT,COLOR_PAIR(2),
        0,0,calc_win->_maxx,calc_win->_maxy);

 fg=COLOR_PAIR(2);
 bg=COLOR_PAIR(3)|A_BOLD;
 vdmbox(calc_win,fg,bg,COL,       ROW,       COL+LEN-1,   ROW+HEI-1);  /* Num */
 vdmbox(calc_win,fg,bg,COL+LEN,   ROW,       COL+2*LEN-1, ROW+HEI-1);  /* /   */
 vdmbox(calc_win,fg,bg,COL+2*LEN, ROW,       COL+3*LEN-1, ROW+HEI-1);  /* *   */
 vdmbox(calc_win,fg,bg,COL+3*LEN, ROW,       COL+4*LEN-1, ROW+HEI-1);  /* -   */
 vdmbox(calc_win,fg,bg,COL,       ROW+HEI,   COL+LEN-1,   ROW+2*HEI-1);/* 7   */
 vdmbox(calc_win,fg,bg,COL+LEN,   ROW+HEI,   COL+2*LEN-1, ROW+2*HEI-1);/* 8   */
 vdmbox(calc_win,fg,bg,COL+2*LEN, ROW+HEI,   COL+3*LEN-1, ROW+2*HEI-1);/* 9   */
 vdmbox(calc_win,fg,bg,COL,       ROW+2*HEI, COL+LEN-1,   ROW+3*HEI-1);/* 4   */
 vdmbox(calc_win,fg,bg,COL+LEN,   ROW+2*HEI, COL+2*LEN-1, ROW+3*HEI-1);/* 5   */
 vdmbox(calc_win,fg,bg,COL+2*LEN, ROW+2*HEI, COL+3*LEN-1, ROW+3*HEI-1);/* 6   */
 vdmbox(calc_win,fg,bg,COL,       ROW+3*HEI, COL+LEN-1,   ROW+4*HEI-1);/* 1   */
 vdmbox(calc_win,fg,bg,COL+LEN,   ROW+3*HEI, COL+2*LEN-1, ROW+4*HEI-1);/* 2   */
 vdmbox(calc_win,fg,bg,COL+2*LEN, ROW+3*HEI, COL+3*LEN-1, ROW+4*HEI-1);/* 3   */
 vdmbox(calc_win,fg,bg,COL+3*LEN, ROW+HEI,   COL+4*LEN-1, ROW+3*HEI-1);/* +   */
 vdmbox(calc_win,fg,bg,COL+3*LEN, ROW+3*HEI, COL+4*LEN-1, ROW+5*HEI-1);/* =   */
 vdmbox(calc_win,fg,bg,COL,       ROW+4*HEI, COL+2*LEN-1, ROW+5*HEI-1);/* 0   */
 vdmbox(calc_win,fg,bg,COL+2*LEN, ROW+4*HEI, COL+3*LEN-1, ROW+5*HEI-1);/* .   */

 mvwaddch(calc_win,ROW+1,       COL+LEN+2,   '/');
 mvwaddch(calc_win,ROW+1,       COL+2*LEN+2, '*');
 mvwaddch(calc_win,ROW+1,       COL+3*LEN+2, '-');
 mvwaddch(calc_win,ROW+HEI+1,   COL+2,       '7');
 mvwaddch(calc_win,ROW+HEI+1,   COL+LEN+2,   '8');
 mvwaddch(calc_win,ROW+HEI+1,   COL+2*LEN+2, '9');
 mvwaddch(calc_win,ROW+2*HEI+1, COL+2,       '4');
 mvwaddch(calc_win,ROW+2*HEI+1, COL+LEN+2,   '5');
 mvwaddch(calc_win,ROW+2*HEI+1, COL+2*LEN+2, '6');
 mvwaddch(calc_win,ROW+3*HEI+1, COL+2,       '1');
 mvwaddch(calc_win,ROW+3*HEI+1, COL+LEN+2,   '2');
 mvwaddch(calc_win,ROW+3*HEI+1, COL+2*LEN+2, '3');
 mvwaddch(calc_win,ROW+HEI+2,   COL+3*LEN+2, '+');
 mvwaddch(calc_win,ROW+3*HEI+2, COL+3*LEN+2, '=');
 mvwaddch(calc_win,ROW+4*HEI+1, COL+LEN,     '0');
 mvwaddch(calc_win,ROW+4*HEI+1, COL+2*LEN+2, ',');

 vdmbox(calc_win,fg,bg,3,2,22,4);
 wattrset(calc_win,COLOR_PAIR(2)|A_REVERSE);
 mvwaddstr(calc_win,3,4,"012345678901234567");
 wattrset(calc_win,COLOR_PAIR(2));

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
 wnoutrefresh(calc_win);
 doupdate();
}



/* The user wants to terminate the program, ok clean up.
 * Delete all opened windows and make the cursor visible.
 * At least call endwin.
 */
void end_calc()
{
 delwin(screen_win);
 delwin(calc_win);
 curs_set(TRUE);
 vdmerase(stdscr);
 refresh();
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



void vdmbox(WINDOW *win, int fg, int bg, int begx, int begy, int maxx, int maxy)
{
int x,y;

 wattrset(win,fg);
 mvwaddch(win,begy,begx,ACS_ULCORNER);
 mvwaddch(win,maxy,begx,ACS_LLCORNER);
 
 wattrset(win,bg);
 mvwaddch(win,begy,maxx,ACS_URCORNER);
 mvwaddch(win,maxy,maxx,ACS_LRCORNER);

 for(x=begx+1;x<maxx;x++){
   wattrset(win,fg);
   mvwaddch(win,begy,x,ACS_HLINE);
   wattrset(win,bg);
   mvwaddch(win,maxy,x,ACS_HLINE);
 }

 for(y=begy+1;y<maxy;y++){
   wattrset(win,fg);
   mvwaddch(win,y,begx,ACS_VLINE);
   wattrset(win,bg);
   mvwaddch(win,y,maxx,ACS_VLINE);
 }
 wattrset(win,fg);
return;
}
