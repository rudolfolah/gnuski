/********************************
*	SkiFree GNU				*
*	Rudolf Olah				*
*	Copyright 2005			*
*	Released under the GNU GPL	*
********************************/
#include <curses.h>		//Include curses stuff
#include <signal.h>
#include <stdlib.h>
#include <pthread.h>	//Include posix thread stuff
#include "common.h"		//Include common functions
#include "init.h"		//Include initialization functions
#include "draw.h"		//Include draw functions

#define OBJ_NUM		30
#define GAME_SPEED	2

void* timer(void* temp);
void* collideY(void* temp);

//Global variables
bool collidex, collidey;
int ski_x, ski_y, ski_next_y;
int obj_x[OBJ_NUM], obj_y[OBJ_NUM];

int main(int argc, char** argv)
{
	char d;
	int angle;
	WINDOW *wnd = initStuff(wnd);
	pthread_t moveThread, collideYThread;
	int moveTRet, collideYRet;
	
	//Set starting skiDude position and angle
	ski_x = 0; ski_y = 8;	ski_next_y = 8;
	angle = 2;
	collidex = false;	collidey = false;
	//Make object x and y random
	for (int i = 0; i < OBJ_NUM; i++)
	{
		obj_x[i] = rndInt(3,60);
		obj_y[i] = rndInt(0,20);
	};
	
	clear();
	//Draw the ski dude
	drawSkiDude(ski_y,ski_x,angle);
	//Draw the trees
	for (int i = 0; i < OBJ_NUM/2; i++)
		drawTree(obj_x[i], obj_y[i]);
	//Draw the rocks
	for (int i = OBJ_NUM/2; i < OBJ_NUM; i++)
	{
		drawRock(obj_x[i], obj_y[i]);
	};
	refresh();
	
	//Start the threads
	moveTRet = pthread_create(&moveThread,NULL,timer,NULL);
	collideYRet = pthread_create(&collideYThread,NULL,collideY,NULL);
	
	while (!collidex && !collidey)
	{
		d = getch(); // input from keyboard
		switch (d)
		{
			case KEY_UP:	case '8':	angle+=1; 	break;
			case KEY_RIGHT:	case '5':			 	break;
			case KEY_DOWN:	case '2':	angle-=1;	break;
			case 'q':	finish(0);	break; // quit?
		};
		
		//Check angle bounds
		if (angle > 4)
			angle = 4;
		if (angle < 0)
			angle = 0;
		
		clear();
		
		if (!collidex && !collidey)
			drawSkiDude(ski_y,ski_x,angle); //Draw the ski dude
		else
		{
			add(ski_x,ski_y,'X');
			break;
		};
		
		//Draw the trees
		for (int i = 0; i < OBJ_NUM/2; i++)
			drawTree(obj_x[i], obj_y[i]);
		//Draw the rocks
		for (int i = OBJ_NUM/2; i < OBJ_NUM; i++)
		{
			drawRock(obj_x[i], obj_y[i]);
		};
		
		//Make sure ski dude goes in the right direction
		switch  (angle)
		{
			case angle_l:
			case angle_cl:	ski_next_y = ski_y+1;	break;
			case angle_r:
			case angle_cr:	ski_next_y = ski_y-1;	break;
		};

		if (!collidex && !collidey)
			ski_y = ski_next_y;
		//If ski dude is not complete left or right, add to the position
		if (angle > angle_l && angle < angle_r)
			ski_x++;
		refresh();
	}
	refresh();
	finish(0);
	return 0;
};

void* timer(void* temp)
{
	//Check collisions with rocks
	for (int i = OBJ_NUM/2; i < OBJ_NUM; i++)
	{
		if (ski_x == obj_x[i])
			collidex = true;
	};
	system("sleep 1");
	if (!collidex && !collidey)
		ski_x++;
};

void* collideY(void* temp)
{
	//Check collisions with rocks
	for (int i = OBJ_NUM/2; i < OBJ_NUM; i++)
	{
		if (ski_next_y == obj_y[i])
			collidey = true;
	};
};
