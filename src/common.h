/***************************************
Name: common.h
Desc: Contains common functions
Copyright (C) 2005  Rudolf Olah
See GPL.txt for more details
***************************************/
#ifndef COMMON_H
#define COMMON_H
#include <string.h>
#include <time.h>
#include <math.h>

int rndInt(int min, int max)
{
	//Swap numbers to make sure max = the maximum
	int temp = max;
	if (min>max)
	{
		max = min;
		min = temp;
	};
	// Generate a number between min and max inclusive
	int i = rand() % max + min;
	srand(time(NULL)+i*25-rand()*time(NULL));
	while (i < min || i > max)
	{
		i = rand() % max + min;
	};
	//printf("Generated number...%i\n",i);	//Debug message
	return i;
};
#endif
