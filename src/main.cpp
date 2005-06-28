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
object *obstacles[OBJ_NUM];
skiDude *zero;

int main(int argc, char** argv)
{
	char d;
	int angle;
	WINDOW *wnd = initStuff(wnd);
	pthread_t moveThread, collideYThread;
	int moveTRet, collideYRet;
	
	collidex = false;	collidey = false;
	
	zero = new skiDude(0, 8, angle_c);
	
	//Make object x and y random
	for (int i = 0; i < OBJ_NUM/2; i++)
	{
		obstacles[i] = new tree(rndInt(3,60), rndInt(3,60));
	};
	for (int j = OBJ_NUM/2; j < OBJ_NUM; j++)
	{
		obstacles[j] = new rock(rndInt(3,60), rndInt(3,60));
	};
	
	clear();
	//Draw the ski dude
	zero->draw();
	//Draw the obstacles
	for (int i = 0; i < OBJ_NUM; i++)
		obstacles[i]->draw();
	refresh();
	
	//Start the threads
	moveTRet = pthread_create(&moveThread, NULL, timer, NULL);
	collideYRet = pthread_create(&collideYThread, NULL, collideY, NULL);
	
	while (!collidex && !collidey)
	{
		d = getch(); // input from keyboard
		switch (d)
		{
			case KEY_UP:	case '8':	zero->setAngle(zero->getAngle() + 1); 	break;
			case KEY_DOWN:	case '2':	zero->setAngle(zero->getAngle() - 1);	break;
			case KEY_RIGHT:	case '5':	break;
			case 'q':	finish(0);	break; // quit?
		};
		
		clear();
		
		if (!collidex && !collidey)
			zero->draw(); //Draw the ski dude
		else
		{
			zero->crash();
			break;
		};
		
		//Draw the obstacles
		for (int i = 0; i < OBJ_NUM; i++)
			obstacles[i]->draw();
		
		//Make sure ski dude goes in the right direction
		/*switch  (angle)
		{
			case angle_l:
			case angle_cl:	ski_next_y = ski_y+1;	break;
			case angle_r:
			case angle_cr:	ski_next_y = ski_y-1;	break;
		};*/

		if (!collidex && !collidey)
			zero->setY(zero->getNextY());
		//If ski dude is not complete left or right, add to the position
		if (angle > angle_l && angle < angle_r)
			zero->setX(zero->getX() + 1);
		refresh();
	}
	refresh();
	pthread_exit(NULL);
	finish(0);
	return 0;
};

void* timer(void* temp)
{
	//Check collisions with rocks
	for (int i = OBJ_NUM/2; i < OBJ_NUM; i++)
	{
		if (zero->getX() == obstacles[i]->getX())
			collidex = true;
	};
	system("sleep 2");
	//if (!collidex && !collidey)
		zero->setX(zero->getX() + 1);
};

void* collideY(void* temp)
{
	//Check collisions with rocks
	for (int i = OBJ_NUM/2; i < OBJ_NUM; i++)
	{
		if (zero->getNextY() == obstacles[i]->getY())
			collidey = true;
	};
};
