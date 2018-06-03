/************************************************************
 * Filename      : Shoot.c
 * Author        : Team Hobanwoo) mwJeong
 * Modified Date : June, 03, 2018    16:58
 * Purpose       : Shooting system in game
 ************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curses.h>
#include <unistd.h>
#include <math.h>
#include "library.h"

#define START_X 8
#define START_Y 10

/*
 * precondition : user give angle of shooting by arrow key
 * @TODO
 * scan user`s input
 */
void shoot(int angle)
{
	int i = 1, j = 1;
	int dirX, dirY = -1;
	int curX = START_X, curY = START_Y;
	int line = 4;
	char circle[CIR_MAX][CIR_MAX];
	char Stage[11][17] = { {"1010101010101010"},
						   {"0101010101010100"},
						   {"1010101010101010"},
						   {"0101010101010100"},
						   {"0000000000000000"},
						   {"0000000000000000"},
						   {"0000000000000000"},
						   {"0000000000000000"},
						   {"0000000000000000"},
						   {"0000000000000000"},
						   {"0000000010000000"} };
	// temperary code
	clear();

	makeCircle(circle, CIR_SIZE);
	printCircle(circle, COLS/2, LINES-2*CIR_SIZE);
	getchar();
	deleteCircle(COLS/2, LINES-2*CIR_SIZE);
	getchar();

	// temperary
	dirX = -1;
	dirY = -1;

	while (TRUE)
	{

		Stage[curY][curX] = '0';
		curY -= dirY;
		curX += dirX;
		if (curX < 0)
		{
			dirX *= -1;
			curX += dirX * 2;
		}

		deleteCircle(COLS/2 - i*CIR_SIZE, LINES-2*CIR_SIZE*j);
		j++;
		if (dirX < 0)
			i++;
		else
			i--;
		printCircle(circle, COLS/2 - i*CIR_SIZE, LINES - 2*CIR_SIZE*j);

		usleep(500000);

		if (j > 16)
			break;
	}

}