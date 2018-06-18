/************************************************************
 * Filename      : PuzzleCow.c
 * Author        : Team Hobanwoo
 * Modified Date : June, 17, 2018    19:01
 * Purpose       : Implements stage1
 ************************************************************/
#include "library.h"
#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <unistd.h>
#include <math.h>
#include <time.h>

void printStageBorder()
{
	int y;
	move(COLS/2 - CIR_SIZE * 8 - 1, 0);
    attron(COLOR_PAIR(FBACK_FAIR));
    for (y = 0; y <= LINES; y++) {
    
        if (y == LINES || y == 0)
            mvhline(y, COLS/2 - CIR_SIZE * 8 - 2, ' ', CIR_SIZE*16+4);
        else if (y == CIR_SIZE * 22)
        {
        	mvhline(y, COLS/2 - CIR_SIZE * 8 - 2, ' ', 6);
        	mvhline(y, COLS/2 + CIR_SIZE * 8 - 4, ' ', 6);
        }
        else 
        {
            mvhline(y, COLS/2 - CIR_SIZE * 8 - 2, ' ', 2);
            mvhline(y, COLS/2 + CIR_SIZE * 8, ' ', 2);
        }
    }
    attroff(COLOR_PAIR(FBACK_FAIR));
    refresh();
}

void initStage(char circle[][CIR_MAX], char map[][15])
{
	int i, j;

	for (i = 0; i < 12; i++) {
		if (i%2 == 0)
			for (j = 0; j < 15; j += 2)
			{
				if (map[i][j] != '0')
					printCircle(circle, COLS/2 - CIR_SIZE * 8 + j/2 * CIR_SIZE*2, i * CIR_SIZE * 2, map[i][j] - '0');
			}
		else 
			for (j = 1; j < 15; j += 2)
			{
				if (map[i][j] != '0')
					printCircle(circle, COLS/2 - CIR_SIZE * 8 + CIR_SIZE + j/2 *CIR_SIZE*2, i * CIR_SIZE * 2, map[i][j] - '0');
			}
	}
	printPower(0);
}

void stage1()
{
	int tab = 3;
	int input;
	int xPower = 0;
	char ch;
	char startX = 7;
	char startY = 11;
	char stage[12][15] = 	{ {"505060607070808"},
						      {"050506060707080"},
						      {"707080805050606"},
						      {"070808050506060"},
						      {"000000000000000"},
						      {"000000000000000"},
						      {"000000000000000"},
						      {"000000000000000"},
						      {"000000000000000"},
						      {"000000000000000"},
						      {"000000000000000"},
						      {"000000050000000"} };

	char circle[CIR_MAX][CIR_MAX];
	makeCircle(circle, CIR_SIZE);
	clear();

	printStageBorder();
	stage[startY][startX] = rand()%4 + '5';
	initStage(circle, stage);

	// loop shoot

	srand(time(NULL));

	while (isEnd(stage, tab))
	{
		xPower = 0;
		printPower(xPower);

		stage[startY][startX] = rand()%4 + '5';
		printCircle(circle, COLS/2 - CIR_SIZE * 8 + CIR_SIZE + startX/2 *CIR_SIZE*2, startY * CIR_SIZE * 2, stage[startY][startX] - '0');

		// choose power
		input = getch();
		while (input != KEY_UP)
		{
			if (input == KEY_RIGHT && xPower < 4)
				xPower++;
			else if (input == KEY_LEFT && xPower > -4)
				xPower--;
			printPower(xPower);

			input = getch();
		}
		shoot(xPower, circle, stage, &tab);

	}

}

void shoot(int x, char circle[][CIR_MAX], char map[][15], int *tab)
{
	int i;
	int check = 0;
	int dir = 1;
	int distance = abs(x);
	int curX = 7;
	int curY = 11;
	int count = 0;
	char ball = map[curY][curX];
	char ch;

	if (x > 0)
		dir = 1;
	if (x < 0)
		dir = -1;

	deleteCircle(COLS/2 - CIR_SIZE * 8 + CIR_SIZE + curX/2 *CIR_SIZE*2, curY * CIR_SIZE * 2);
	while (!isOver(map))
	{

		// remove previous ball
		map[curY][curX] = '0';
		if (count%2 != 0)
			deleteCircle(COLS/2 - CIR_SIZE * 8 + curX/2 * CIR_SIZE*2, curY * CIR_SIZE * 2);
		else
			deleteCircle(COLS/2 - CIR_SIZE * 8 + CIR_SIZE + curX/2 *CIR_SIZE*2, curY * CIR_SIZE * 2);
		
		// progress ball shooting
		if (x == 0)
		{
			dir *= -1;
			curX += dir;

			if (isAttached(map, curX, curY-1))
			{
				check = 1;
				break;
			}

			if (count%2 == 0)
				printCircle(circle, COLS/2 - CIR_SIZE * 8 + curX/2 * CIR_SIZE * 2, (curY-1) * CIR_SIZE * 2, ball-'0');
			else
				printCircle(circle, COLS/2 - CIR_SIZE * 7 + curX/2 * CIR_SIZE * 2, (curY-1) * CIR_SIZE * 2, ball-'0');

			usleep(200000);
			count++;

		}

		else {
			for (i = 1; i <= distance; i++)
			{
				curX += dir;
				if (curX < 0)
				{
					dir *= -1;
					curX *= -1;
				}
				else if (curX > 14)
				{
					dir *= -1;
					curX -= curX-13;
				}

				if (isAttached(map, curX, curY-1))
				{
					check = 1;
					break;
				}

				if (isAttached(map, curX, curY))
				{
					check = 2;
					break;
				}

				if (count%2 == 0)
					printCircle(circle, COLS/2 - CIR_SIZE * 8 + curX/2 * CIR_SIZE * 2, curY * CIR_SIZE * 2 - 2*CIR_SIZE*((float)i/distance), ball-'0');
				else
					printCircle(circle, COLS/2 - CIR_SIZE * 7 + curX/2 * CIR_SIZE * 2, curY * CIR_SIZE * 2 - 2*CIR_SIZE*((float)i/distance), ball-'0');

				usleep(200000);

				if (i != distance)
				{
					if (count%2 == 0)
						deleteCircle(COLS/2 - CIR_SIZE * 8 + curX/2 * CIR_SIZE * 2, curY * CIR_SIZE * 2 - 2*CIR_SIZE*((float)i/distance));
					else
						deleteCircle(COLS/2 - CIR_SIZE * 7 + curX/2 * CIR_SIZE * 2, curY * CIR_SIZE * 2 - 2*CIR_SIZE*((float)i/distance));
				}

				count++;
			}
		}

		if (check == 1 || check == 2)
			break;

		curY--;
		map[curY][curX] = ball;
	}

	if (check == 1)
	{
		curY--;
		map[curY][curX] = ball;
		if (count%2 == 0)
			printCircle(circle, COLS/2 - CIR_SIZE * 8 + curX/2 * CIR_SIZE * 2, curY * CIR_SIZE * 2, ball-'0');
		else
			printCircle(circle, COLS/2 - CIR_SIZE * 7 + curX/2 * CIR_SIZE * 2, curY * CIR_SIZE * 2, ball-'0');
	}
	if (check == 2)
	{
		map[curY][curX] = ball;
		if (count%2 == 0)
			printCircle(circle, COLS/2 - CIR_SIZE * 8 + curX/2 * CIR_SIZE * 2, curY * CIR_SIZE * 2, ball-'0');
		else
			printCircle(circle, COLS/2 - CIR_SIZE * 7 + curX/2 * CIR_SIZE * 2, curY * CIR_SIZE * 2, ball-'0');
	}
}

int isEnd(char map[][15], int tab)
{
	int res = 1;

	if (tab > 10)
		return 0;

	for (int i = 0; i < 15; i+=2)
		if (map[0][i] == '0')
			res = 0;

	return res;
}

void printPower(int xPower)
{
	// remove previous power
	int yLocation = 14 * CIR_SIZE * 2;

	attron(COLOR_PAIR(BACK_FAIR));
	for (int i = 0; i < 6; i++)
		mvhline(yLocation - i, COLS/2 - CIR_SIZE * 8, ' ', CIR_SIZE * 16);
	attroff(COLOR_PAIR(BACK_FAIR));


	// print new Power
	attron(COLOR_PAIR(FBACK_FAIR));

	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < abs(xPower); j++)
		{
			if (xPower < 0)
				mvhline(yLocation - i, COLS/2 - 1 - abs(xPower) * i - j, ' ', 1);
			if (xPower > 0)
				mvhline(yLocation - i, COLS/2 + abs(xPower) * i - j, ' ', 1);
		}
		if (xPower == 0)
			mvhline(yLocation - i, COLS/2 - 1, ' ', 1);
	}

	attroff(COLOR_PAIR(FBACK_FAIR));
	refresh();
}

int isAttached(char map[][15], int x, int y)
{
	int res = 0;

	if (x >= 2 && x <= 12)
	{
		if (y > 0) {
			if (map[y-1][x-1] != '0' || map[y-1][x+1] != '0')
				res = 1;
		}

		if (map[y][x-2] !='0' || map[y][x+2] != '0')
			res = 1;
	}
	else if (x < 2)
	{
		if (y > 0)
		{
			if (x == 0)
			{
				if (map[y-1][x+1] != '0' || map[y][x+2] != '0')
					res = 1;
			}

			else
			{
				if (map[y-1][x-1] != '0' || map[y-1][x+1] != '0' || map[y][x+2] != '0')
				res = 1;
			}
		}

		else
		{
			if (map[y][x+2] != '0')
				res = 1;
		}

	}
	else if (x > 12)
	{
		if (y > 0)
		{
			if (x == 14)
			{
				if (map[y-1][x-1] != '0' || map[y][x-2] != '0')
					res = 1;
			}
			else
				if (map[y-1][x-1] != '0' || map[y-1][x+1] != '0' || map[y][x-2] != '0')
					res = 1;
		}
		else
			if (map[y][x-2] != '0')
				res = 1;
	}

	return res;
}

int isOver(char map[][15])
{
	int res = 0;

	if (map[10][6] != '0' && (map[9][5] != '0' || map[9][7] != '0' || map[10][4] != '0' || map[10][8] != '0'))
		res = 1;
	else if (map[10][7] != '0' && (map[9][6] != '0' || map[9][8] != '0' || map[10][5] != '0' || map[10][9] != '0'))
		res = 1;
	else if (map[10][8] != '0' && (map[9][7] != '0' || map[9][9] != '0' || map[10][6] != '0' || map[10][10] != '0'))
		res = 1;

	return res;
}