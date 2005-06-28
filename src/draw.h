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

class object
{
private:
public:
	int x, y;
	object();
	object(int newX, int newY);
	virtual void draw();
	virtual int getX();
	virtual int getY();
};

object::object()
{
	x = 0;
	y = 0;
};

object::object(int newX, int newY)
{
	x = newX;
	y = newY;
};

void object::draw()
{
};

int object::getX()
{
	return x;
};

int object::getY()
{
	return y;
};




class skiDude : public object
{
private:
	int nextX, nextY;
	int angle;
public:
	skiDude(int newX, int newY, int newAngle);
	void crash();
	void draw();
	void setX(int newX);
	void setY(int newY);
	void setAngle(int newAngle);
	int getX();
	int getY();
	int getNextX();
	int getNextY();
	int getAngle();
};

void skiDude::setX(int newX)
{
	x = newX;
	nextX = newX + 1;
};

void skiDude::setY(int newY)
{
	y = newY;
	switch (angle)
	{
		case angle_l:
		case angle_cl:	nextY = newY + 1;
						break;
		case angle_c:	nextY = newY;
						break;
		case angle_r:
		case angle_cr:	nextY = newY - 1;
						break;
	};
	nextY = newY + 1;
};

void skiDude::setAngle(int newAngle)
{
	if (newAngle > 4)
		angle = 4;
	else if (newAngle < 0)
			angle = 0;
		else
			angle = newAngle;
};

int skiDude::getX()	{	return x;	};

int skiDude::getY()	{	return y;	};

int skiDude::getNextX()	{	return nextX;	};

int skiDude::getNextY()	{	return nextY;	};

int skiDude::getAngle()	{	return angle;	};

skiDude::skiDude(int newX, int newY, int newAngle)
{
	setAngle(newAngle);
	setX(newX);
	setY(newY);
};

void skiDude::crash()
{
	add(x, y, 'X');
};

void skiDude::draw()
{
	color_set(COLOR_CYAN, 0);
	switch (angle)
	{
		case angle_l:	add(y, x+1, '|');
						add(y+1, x+1, '|');
						break;
		case angle_cl:	add(y+1, x+1, '\\');
						add(y+2, x+1, '\\');
						break;
		case angle_c:	add(y+1, x, '=');
						break;
		case angle_cr:	add(y+1, x-1, '/');
						add(y+2, x-1, '/');
						break;
		case angle_r:	add(y, x-2, '|');
						add(y+1, x-2, '|');
						break;
	};
	color_set(COLOR_WHITE, 0);
};




class tree : public object
{
public:
	tree(int newX, int newY);
	void draw();
};

tree::tree(int newX, int newY)
{
	x = newX;
	y = newY;
};

//Draws a tree
/*
	/|\
	/|\
	  |
*/
void tree::draw()
{
	color_set(COLOR_GREEN, 0);
	add(x, y, '/');		add(x+2, y, '\\');
	add(x, y+1, '/');	add(x+2, y+1, '\\');
	color_set(COLOR_YELLOW, 0);
	add(x+1, y, '|');	add(x+1, y+1, '|');	add(x+1, y+2, '|');
	color_set(COLOR_WHITE, 0);
};




class rock : public object
{
public:
	rock(int newX, int newY);
	void draw();
};

rock::rock(int newX, int newY)
{
	x = newX;
	y = newY;
};

//Draws a rock
/*
	@
*/
void rock::draw()
{
	color_set(COLOR_WHITE, 0);
	add(x, y, '@');
	color_set(COLOR_WHITE, 0);
};

#endif
