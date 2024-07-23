/********************************
*	SkiFree GNU				*
*	Rudolf Olah				*
*	Copyright 2005			*
*	Released under the GNU GPL	*
********************************/
#ifndef DRAW_H
#define DRAW_H

#include <curses.h>
#include <signal.h>
#include <stdlib.h>
#include "common.h"

#define angle_l		0
#define angle_cl	1
#define angle_c		2
#define angle_cr	3
#define angle_r		4

void add(int x, int y, char d)
{
	move(y,x);
	addch(d);
};

void drawSkiDude(int x, int y, int angle)
{
	color_set(COLOR_CYAN,0);
	switch (angle)
	{
		/*
		case angle_l:	add(y,x+2,'S');	add(y,x+1,'S');	add(y,x,'S'); break;
		case angle_cl:	add(y+2,x+2,'S');	add(y+1,x+1,'S');	add(y,x,'S'); break;
		case angle_c:	add(y+2,x,'S');	add(y+1,x,'S');	add(y,x,'S'); break;
		case angle_cr:	add(y+2,x-2,'S');	add(y+1,x-1,'S');	add(y,x,'S'); break;
		case angle_r:	add(y,x-2,'S');	add(y,x-1,'S');	add(y,x,'S'); break;
		*/
		case angle_l:	add(y,x+1,'|');	//add(y,x+2,'|');
						add(y+1,x+1,'|');	//add(y+1,x+2,'|');
						break;
		case angle_cl:	add(y+1,x+1,'\\');	//add(y+2,x+2,'\\');
						add(y+2,x+1,'\\');	//add(y+3,x+2,'\\');
						break;
		case angle_c:	add(y+1,x,'=');	//add(y+2,x,'=');
						break;
		case angle_cr:	add(y+1,x-1,'/');	//add(y+2,x-2,'/');
						add(y+2,x-1,'/');	//add(y+3,x-2,'/');
						break;
		case angle_r:	add(y,x-2,'|');	//add(y,x-1,'|');
						add(y+1,x-2,'|');	//add(y+1,x-1,'|');
						break;
	};
	color_set(COLOR_WHITE,0);
};

//Draws a tree
/*
	/|\
	/|\
	  |
*/
void drawTree(int x, int y)
{
	color_set(COLOR_GREEN,0);
	add(x,y,'/');		add(x+2,y,'\\');
	add(x,y+1,'/');	add(x+2,y+1,'\\');
	color_set(COLOR_YELLOW,0);
	add(x+1,y,'|');	add(x+1,y+1,'|');	add(x+1,y+2,'|');
	color_set(COLOR_WHITE,0);
};

//Draws a rock
/*
	@
*/
void drawRock(int x, int y)
{
	color_set(COLOR_WHITE,0);
	add(x,y,'@');
	color_set(COLOR_WHITE,0);
};

#endif
