/********************************
*	SkiFree GNU				*
*	Rudolf Olah				*
*	Copyright 2005			*
*	Released under the GNU GPL	*
********************************/
#ifndef INIT_H
#define INIT_H

#include <curses.h>
#include <signal.h>
#include <stdlib.h>

static void finish(int sig);

//Code from VMS Empire (C-Empire)
void init_colors()
{
    start_color();

    init_pair(COLOR_BLACK, COLOR_BLACK, COLOR_BLACK);
    init_pair(COLOR_GREEN, COLOR_GREEN, COLOR_BLACK);
    init_pair(COLOR_RED, COLOR_RED, COLOR_BLACK);
    init_pair(COLOR_CYAN, COLOR_CYAN, COLOR_BLACK);
    init_pair(COLOR_WHITE, COLOR_WHITE, COLOR_BLACK);
    init_pair(COLOR_MAGENTA, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(COLOR_BLUE, COLOR_BLUE, COLOR_BLACK);
    init_pair(COLOR_YELLOW, COLOR_YELLOW, COLOR_BLACK);
};

WINDOW* initStuff(WINDOW* wnd)
{
	signal(SIGINT, finish);      // arrange interrupts to terminate

    wnd =  initscr();      //initialize the curses library
	attron(A_BOLD);
    keypad(stdscr, TRUE);  // enable keyboard mapping
    nonl();         		// tell curses not to do NL->CR/NL on output
    cbreak();       		// take input chars one at a time, no wait for \n
    noecho();       		// don't echo input

    init_colors();
	return wnd;
};

static void finish(int sig)
{
    endwin();
    /* do your non-curses wrapup here */
	echo();
    exit(0);
};
#endif
