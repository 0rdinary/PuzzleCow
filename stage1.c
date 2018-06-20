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
#include <signal.h>
#include <math.h>
#include <time.h>
#include <sys/types.h>

extern int bestStage;
extern int bestScore;
extern int score;

typedef struct location {
	int x;
	int y;
} location;

char number1[7][5] = { {"00100"},
					   {"01100"},
					   {"00100"},
					   {"00100"},
					   {"00100"},
				       {"00100"},
				 	   {"11111"} };
char number2[7][5] = { {"01110"},
					   {"10001"},
					   {"00001"},
					   {"00010"},
					   {"00100"},
					   {"01000"},
					   {"11111"} };
char number3[7][5] = { {"11111"},
					   {"00010"},
					   {"00100"},
					   {"00010"},
					   {"00001"},
					   {"10001"},
					   {"01110"} };
char number4[7][5] = { {"00010"},
					   {"00110"},
					   {"01010"},
					   {"10010"},
					   {"11111"},
					   {"00010"},
					   {"00010"} };
char number5[7][5] = { {"11111"},
					   {"10000"},
					   {"11110"},
					   {"00001"},
					   {"00001"},
					   {"10001"},
					   {"01110"} };
char number6[7][5] = { {"00110"},
					   {"01000"},
					   {"10000"},
					   {"11110"},
					   {"10001"},
					   {"10001"},
					   {"01110"} };
char number7[7][5] = { {"11111"},
					   {"00001"},
					   {"00010"},
					   {"00100"},
					   {"00100"},
					   {"00100"},
					   {"00100"} };
char number8[7][5] = { {"01110"},
					   {"10001"},
					   {"10001"},
					   {"01110"},
					   {"10001"},
					   {"10001"},
					   {"01110"} };
char number9[7][5] = { {"01110"},
					   {"10001"},
					   {"10001"},
					   {"01111"},
					   {"00001"},
					   {"00010"},
					   {"01100"} };
char number0[7][5] = { {"01110"},
					   {"10001"},
					   {"10011"},
					   {"10101"},
					   {"11001"},
					   {"10001"},
					   {"01110"} };

char smallP[6][5] = { {"11111"},
				      {"10001"},
				      {"10001"},
				      {"11111"},
				      {"10000"},
				      {"10000"} };

char smallU[6][5] = { {"10001"},
				      {"10001"},
				      {"10001"},
				      {"10001"},
				      {"11011"},
				      {"01110"} };

char smallZ[6][5] = { {"11111"},
				      {"00011"},
				      {"00110"},
				      {"01100"},
				      {"11000"},
				      {"11111"} };

char smallL[6][5] = { {"10000"},
				      {"10000"},
				      {"10000"},
				      {"10000"},
				      {"10000"},
				      {"11111"} };

char smallE[6][5] = { {"11111"},
				      {"10000"},
				      {"11110"},
				      {"11110"},
				      {"10000"},
				      {"11111"} };

char smallC[6][5] = { {"01111"},
				      {"11001"},
				      {"10000"},
				      {"10000"},
				      {"11001"},
				      {"01110"} };

char smallO[6][5] = { {"01110"},
				      {"11011"},
				      {"10001"},
				      {"10001"},
				      {"11011"},
				      {"01110"} };

char smallW[6][5] = { {"10001"},
				      {"10101"},
				      {"10101"},
				      {"10101"},
				      {"10101"},
				      {"01110"} };

char smallN[6][5] = { {"10001"},
				      {"11001"},
				      {"11101"},
				      {"10111"},
				      {"10011"},
				      {"10001"} };

char smallX[6][5] = { {"10001"},
				      {"11011"},
				      {"01110"},
				      {"00100"},
				      {"01010"},
				      {"10001"} };

char smallT[6][5] = { {"11111"},
				      {"10101"},
				      {"00100"},
				      {"00100"},
				      {"00100"},
				      {"00100"} };

char smallS[6][5] = { {"11111"},
				      {"10001"},
				      {"11100"},
				      {"00111"},
				      {"10001"},
				      {"11111"} };

char smallR[6][5] = { {"11111"},
				      {"10001"},
				      {"11111"},
				      {"11000"},
				      {"10110"},
				      {"10011"} };

char smallB[6][5] = { {"11110"},
					  {"10010"},
					  {"10010"},
					  {"11111"},
					  {"10001"},
					  {"11111"} };

char smallG[6][5] = { {"11111"},
					  {"10001"},
					  {"10000"},
					  {"10111"},
					  {"10001"},
					  {"11111"} };

char smallA[6][5] = { {"01110"},
					  {"11011"},
					  {"10001"},
					  {"11111"},
					  {"10001"},
					  {"10001"} };

char smallM[6][5] = { {"10001"},
					  {"11011"},
					  {"11111"},
					  {"10101"},
					  {"10101"},
					  {"10001"} };

char smallV[6][5] = { {"10001"},
					  {"10001"},
					  {"10001"},
					  {"11011"},
					  {"01110"},
					  {"00100"} };

char overPicture[32][32] = {{"00000000000000000000000000000000"},
    						{"00000000000000000000000000000000"},
    						{"00000000000000111100001111000000"},
   						    {"00000000000011222211012222100000"},
    						{"00000000000122222222122222210000"},
    						{"00000000001222222222212222221000"},
    						{"00000000012222211111212111111000"},
						    {"00000000012221122222111222222100"},
						    {"00000000122212222222112222111210"},
						    {"00000001122222222222221211222210"},
						    {"00000012122222221111112122111110"},
						    {"00000122122222211222221111333331"},
						    {"00001222222221122211111133331131"},
						    {"00001222222112221133333111311311"},
						    {"00012222222211113311131222111111"},
						    {"00012222222221333111311212222221"},
						    {"00122222222221111111111221111210"},
						    {"00122222222222222222212222222100"},
						    {"00122222222222222222122222222210"},
						    {"00122222222222222221222222222210"},
						    {"00122222222222222212222222221141"},
						    {"00122222222211111222222222114441"},
						    {"00122222222144444111111111444111"},
						    {"00122222221441111444444444411441"},
						    {"00012222222114444111111111144411"},
						    {"00001222222221111444444444441110"},
						    {"00001222222222222111111111121100"},
						    {"00000122222222222222211112211000"},
						    {"00000012222222222221111221100000"},
						    {"00000001122222222222222110000000"},
						    {"00000000011122222222211000000000"},
						    {"00000000000011111111100000000000"}};


void printStageBorder()
{
	int y;
	move(COLS/2 - CIR_SIZE * 8 - 1, 0);
    attron(COLOR_PAIR(FBACK_FAIR));
    for (y = 0; y <= LINES; y++)
    {
    
        if (y == CIR_SIZE * 22)
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

void printScore(char number[][5], int x, int y)
{
	int i, j;

	for (i = 0; i < 7; i++)
		for (j = 0; j < 5; j++)
			if (number[i][j] != '0')
			{
				attron(COLOR_PAIR(FBACK_FAIR));
				mvhline(y + i, x + j, ' ', 1);
				attroff(COLOR_PAIR(FBACK_FAIR));
			}
     

     refresh();
}

void deleteScore(int x, int y)
{
	int i, j;

	attron(COLOR_PAIR(BACK_FAIR));
	for (int i = 0; i < 7; i++)
		mvhline(y + i, x, ' ', 5);
	attroff(COLOR_PAIR(BACK_FAIR));
}

void initStage(char circle[][CIR_MAX], char map[][15])
{
	int i, j;
	char buffer1[10];
	char buffer2[10];

	score = 0;

	// set score
	printAlp(smallS, 0, 0);
	printAlp(smallC, 6, 0);
	printAlp(smallO, 12, 0);
	printAlp(smallR, 18, 0);
	printAlp(smallE, 24, 0);
	printScore(number0, 31, 0);

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

	sprintf(buffer1, "%d", bestStage);
		for (i = 0; buffer1[i] != '\0'; i++)
		{
			switch(buffer1[i] - '0')
			{
				case 0 : printScore(number0, 0, LINES-7);
						break;
				case 1 : printScore(number1, 0, LINES-7);
						break;
				case 2 : printScore(number2, 0, LINES-7);
						break;
				case 3 : printScore(number3, 0, LINES-7);
						break;
				case 4 : printScore(number4, 0, LINES-7);
						break;
				case 5 : printScore(number5, 0, LINES-7);
						break;
				case 6 : printScore(number6, 0, LINES-7);
						break;
				case 7 : printScore(number7, 0, LINES-7);
						break;
				case 8 : printScore(number8, 0, LINES-7);
						break;
				case 9 : printScore(number9, 0, LINES-7);
						break;
			}
		}

		// print bsetScore
		sprintf(buffer2, "%d", bestScore);
		for (i = 0; buffer2[i] != '\0'; i++)
		{
			switch(buffer2[i] - '0')
			{
				case 0 : printScore(number0, 10 + i * 6, LINES-7);
						break;
				case 1 : printScore(number1, 10 + i * 6, LINES-7);
						break;
				case 2 : printScore(number2, 10 + i * 6, LINES-7);
						break;
				case 3 : printScore(number3, 10 + i * 6, LINES-7);
						break;
				case 4 : printScore(number4, 10 + i * 6, LINES-7);
						break;
				case 5 : printScore(number5, 10 + i * 6, LINES-7);
						break;
				case 6 : printScore(number6, 10 + i * 6, LINES-7);
						break;
				case 7 : printScore(number7, 10 + i * 6, LINES-7);
						break;
				case 8 : printScore(number8, 10 + i * 6, LINES-7);
						break;
				case 9 : printScore(number9, 10 + i * 6, LINES-7);
						break;
			}
		}

	// print mark
	printGreenScore(smallP, COLS-36, 0);
	printGreenScore(smallU, COLS-30, 0);
	printGreenScore(smallZ, COLS-24, 0);
	printGreenScore(smallZ, COLS-18, 0);
	printGreenScore(smallL, COLS-12, 0);
	printGreenScore(smallE, COLS-6, 0);

	printGreenScore(smallC, COLS-18, 8);
	printGreenScore(smallO, COLS-12, 8);
	printGreenScore(smallW, COLS-6, 8);

	// print next
	printAlp(smallN, COLS - CIR_SIZE * 3 - 24, LINES-9);
	printAlp(smallE, COLS - CIR_SIZE * 3 - 18, LINES-9);
	printAlp(smallX, COLS - CIR_SIZE * 3 - 12, LINES-9);
	printAlp(smallT, COLS - CIR_SIZE * 3 - 6, LINES-9);

	// print best
	printAlp(smallB, 0, LINES - 14);
	printAlp(smallE, 6, LINES - 14);
	printAlp(smallS, 12, LINES - 14);
	printAlp(smallT, 18, LINES - 14);

}

void stage1()
{
	int tab = 3;
	int i;
	int input;
	int xPower = 0;
	char ballCycle[10];
	int ballIdx = 0;
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
						      {"000000000000000"} };

	char circle[CIR_MAX][CIR_MAX];


	makeCircle(circle, CIR_SIZE);
	clear();

	printStageBorder();
	initStage(circle, stage);

	// loop shoot

	srand(time(NULL));

	for (i = 0; i < 10; i++)
		ballCycle[i] = rand()%4 + '5';

	while (!isEnd(stage))
	{
		xPower = 0;
		printPower(xPower);

		if (ballIdx > 9)
			ballIdx = 0;
		stage[startY][startX] = ballCycle[ballIdx++];

		// print current and next ball
		printCircle(circle, COLS/2 - CIR_SIZE * 8 + CIR_SIZE + startX/2 *CIR_SIZE*2, startY * CIR_SIZE * 2, stage[startY][startX] - '0');
		printCircle(circle, COLS - CIR_SIZE * 3 , LINES - CIR_SIZE * 3 , ballCycle[ballIdx%10] - '0');

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

		if (isOver(stage))
		{
			gameOver();

			return;
		}

		if (isEnd(stage))
		{
			system("say Do you know da wae?");

			return;
		}
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
	while (true)
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

			usleep(100000);
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

				usleep(100000);

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

	usleep(100000);
	search(map, curX, curY, ball);
}

int isEnd(char map[][15])
{
	int res = 1;


	for (int i = 0; i < 15; i+=2)
		if (map[0][i] != '0')
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


	if (y == 0 && x%2 == 0)
		res = 1;
	else if (x >= 2 && x <= 12)
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

void search(char map[][15], int xBall, int yBall, char ball)
{
	int i, j;
	int count = 1;
	int check;
	int temp;
	char ch;
	char buffer[10] = {0, };
	char buffer1[10] = {0, };
	char buffer2[10] = {0, };
	location list[20];
	location cur;
	location same[20];
	int usedIdx = 1;
	int tempX, tempY;

	list[0].x = xBall;
	list[0].y = yBall;
	same[0].x = xBall;
	same[0].y = yBall;

	while (usedIdx > 0)
	{
		usedIdx--;

		cur = list[usedIdx];

		if (cur.y > 0 && cur.x > 0 && map[cur.y-1][cur.x-1] == ball)
		{
			check = 1;
			for (i = 0; i <= count; i++)
				if (same[i].x == cur.x-1 && same[i].y == cur.y-1)
					check = 0;

			if (check == 1)
			{
				list[usedIdx].x = cur.x-1;
				list[usedIdx++].y = cur.y-1;
				same[count].x = cur.x-1;
				same[count++].y = cur.y-1;
			}
		}
		if (cur.y > 0 && cur.x < 14 && map[cur.y-1][cur.x+1] == ball)
		{
			check = 1;
			for (i = 0; i <= count; i++)
				if (same[i].x == cur.x+1 && same[i].y == cur.y-1)
					check = 0;

			if (check == 1)
			{
				list[usedIdx].x = cur.x+1;
				list[usedIdx++].y = cur.y-1;
				same[count].x = cur.x+1;
				same[count++].y = cur.y-1;
			}
		}
		if (cur.x > 1 && map[cur.y][cur.x-2] == ball)
		{
			check = 1;
			for (i = 0; i <= count; i++)
				if (same[i].x == cur.x-2 && same[i].y == cur.y)
					check = 0;

			if (check == 1)
			{
				list[usedIdx].x = cur.x-2;
				list[usedIdx++].y = cur.y;
				same[count].x = cur.x-2;
				same[count++].y = cur.y;
			}
		}
		if (cur.x < 13 && map[cur.y][cur.x+2] == ball)
		{
			check = 1;
			for (i = 0; i <= count; i++)
				if (same[i].x == cur.x+2 && same[i].y == cur.y)
					check = 0;

			if (check == 1)
			{
				list[usedIdx].x = cur.x+2;
				list[usedIdx++].y = cur.y;
				same[count].x = cur.x+2;
				same[count++].y = cur.y;
			}
		}
		if (cur.y < 10 && cur.x > 0 && map[cur.y+1][cur.x-1] == ball)
		{
			check = 1;
			for (i = 0; i <= count; i++)
				if (same[i].x == cur.x-1 && same[i].y == cur.y+1)
					check = 0;

			if (check == 1)
			{
				list[usedIdx].x = cur.x-1;
				list[usedIdx++].y = cur.y+1;
				same[count].x = cur.x-1;
				same[count++].y = cur.y+1;
			}
		}
		if (cur.y < 10 && cur.x < 14 && map[cur.y+1][cur.x+1] == ball)
		{
			check = 1;
			for (i = 0; i <= count; i++)
				if (same[i].x == cur.x+1 && same[i].y == cur.y+1)
					check = 0;

			if (check == 1)
			{
				list[usedIdx].x = cur.x+1;
				list[usedIdx++].y = cur.y+1;
				same[count].x = cur.x+1;
				same[count++].y = cur.y+1;
			}
		}
	}

	if (count >= 3)
	{
		for (i = 0; i < count; i++)
		{
			tempX = same[i].x;
			tempY = same[i].y;

			map[tempY][tempX] = '0';

			if (tempY%2 == 0)
				deleteCircle(COLS/2 - CIR_SIZE * 8 + tempX/2 * CIR_SIZE * 2, tempY * CIR_SIZE * 2);
			else
				deleteCircle(COLS/2 - CIR_SIZE * 7 + tempX/2 * CIR_SIZE * 2, tempY * CIR_SIZE * 2);

			score++;
		}

		for (i = 1; i < 12; i++)
			for (j = 0; j < 15; j++)
			{
				if (map[i][j] != '0')
				{
					check = 0;

					if (i > 0 && j > 0 && map[i-1][j-1] != '0')
						check = 1;
					if (i > 0 && j < 14 && map[i-1][j+1] != '0')
						check = 1;
					if (j > 1 && map[i][j-2] != '0')
						check = 1;
					if (i < 13 && map[i][j+2] != '0')
						check = 1;

					if (check == 0)
					{
						map[i][j] = '0';

						if (i%2 == 0)
							deleteCircle(COLS/2 - CIR_SIZE * 8 + j/2 * CIR_SIZE * 2, i * CIR_SIZE * 2);
						
						else
							deleteCircle(COLS/2 - CIR_SIZE * 7 + j/2 * CIR_SIZE * 2, i * CIR_SIZE * 2);
						
						score++;
					}
				}
			}
		

		sprintf(buffer, "%d", score);
		if (score > bestScore)
			bestScore = score;

		for (i = 0; i < 7; i++)
		{
			attron(COLOR_PAIR(BACK_FAIR));
			mvhline(i, 31, ' ', 18);
			mvhline(LINES-7+i, 0, ' ', 25);
			attroff(COLOR_PAIR(BACK_FAIR));
		}

		// print Score
		for (i = 0; buffer[i] != '\0'; i++)
		{
			switch(buffer[i] - '0')
			{
				case 0 : printScore(number0, 31 + 6*i, 0);
						break;
				case 1 : printScore(number1, 31 + 6*i, 0);
						break;
				case 2 : printScore(number2, 31 + 6*i, 0);
						break;
				case 3 : printScore(number3, 31 + 6*i, 0);
						break;
				case 4 : printScore(number4, 31 + 6*i, 0);
						break;
				case 5 : printScore(number5, 31 + 6*i, 0);
						break;
				case 6 : printScore(number6, 31 + 6*i, 0);
						break;
				case 7 : printScore(number7, 31 + 6*i, 0);
						break;
				case 8 : printScore(number8, 31 + 6*i, 0);
						break;
				case 9 : printScore(number9, 31 + 6*i, 0);
						break;
			}
		}

		// print bestStage
		sprintf(buffer1, "%d", bestStage);
		for (i = 0; buffer1[i] != '\0'; i++)
		{
			switch(buffer1[i] - '0')
			{
				case 0 : printScore(number0, 0, LINES-7);
						break;
				case 1 : printScore(number1, 0, LINES-7);
						break;
				case 2 : printScore(number2, 0, LINES-7);
						break;
				case 3 : printScore(number3, 0, LINES-7);
						break;
				case 4 : printScore(number4, 0, LINES-7);
						break;
				case 5 : printScore(number5, 0, LINES-7);
						break;
				case 6 : printScore(number6, 0, LINES-7);
						break;
				case 7 : printScore(number7, 0, LINES-7);
						break;
				case 8 : printScore(number8, 0, LINES-7);
						break;
				case 9 : printScore(number9, 0, LINES-7);
						break;
			}
		}

		// print bsetScore
		sprintf(buffer2, "%d", bestScore);
		for (i = 0; buffer2[i] != '\0'; i++)
		{
			switch(buffer2[i] - '0')
			{
				case 0 : printScore(number0, 10 + i * 6, LINES-7);
						break;
				case 1 : printScore(number1, 10 + i * 6, LINES-7);
						break;
				case 2 : printScore(number2, 10 + i * 6, LINES-7);
						break;
				case 3 : printScore(number3, 10 + i * 6, LINES-7);
						break;
				case 4 : printScore(number4, 10 + i * 6, LINES-7);
						break;
				case 5 : printScore(number5, 10 + i * 6, LINES-7);
						break;
				case 6 : printScore(number6, 10 + i * 6, LINES-7);
						break;
				case 7 : printScore(number7, 10 + i * 6, LINES-7);
						break;
				case 8 : printScore(number8, 10 + i * 6, LINES-7);
						break;
				case 9 : printScore(number9, 10 + i * 6, LINES-7);
						break;
			}
		}

	}
}

void printRedScore(char number[][5], int x, int y)
{
	int i, j;

	for (i = 0; i < 7; i++)
		for (j = 0; j < 5; j++)
			if (number[i][j] != '0')
			{
				attron(COLOR_PAIR(BALL1));
				mvhline(y + i, x + j, ' ', 1);
				attroff(COLOR_PAIR(BALL1));
			}
     

     refresh();
}

void printGreenScore(char number[][5], int x, int y)
{
	int i, j;

	for (i = 0; i < 6; i++)
		for (j = 0; j < 5; j++)
			if (number[i][j] != '0')
			{
				attron(COLOR_PAIR(FONT_FAIR));
				mvhline(y + i, x + j, ' ', 1);
				attroff(COLOR_PAIR(FONT_FAIR));
			}
     

     refresh();
}

void printAlp(char number[][5], int x, int y)
{
	int i, j;

	for (i = 0; i < 6; i++)
		for (j = 0; j < 5; j++)
			if (number[i][j] != '0')
			{
				attron(COLOR_PAIR(FBACK_FAIR));
				mvhline(y + i, x + j, ' ', 1);
				attroff(COLOR_PAIR(FBACK_FAIR));
			}
     

     refresh();
}

void gameOver()
{
	int i, j;
	char ch;

	clear();

	for (i = 0; i < 32; i++)
		for (j = 0; j < 32; j++)
		{
			if (overPicture[i][j] == '0' || overPicture[i][j] == '1')
				attron(COLOR_PAIR(BACK_FAIR));

			else if (overPicture[i][j] == '3')
				attron(COLOR_PAIR(FBACK_FAIR));

			else if (overPicture[i][j] == '2')
				attron(COLOR_PAIR(FONT_FAIR));

			else if (overPicture[i][j] == '4')
				attron(COLOR_PAIR(BALL1));

			mvhline(LINES/2 - 24 + i, COLS/2 - 16 + j, ' ', 1);

			attroff(COLOR_PAIR(BACK_FAIR));
			attroff(COLOR_PAIR(FBACK_FAIR));
			attroff(COLOR_PAIR(FONT_FAIR));
			attroff(COLOR_PAIR(BALL1));
		}

	printAlp(smallG, COLS/2 - 24, LINES/2 + 14);
	printAlp(smallA, COLS/2 - 18, LINES/2 + 14);
	printAlp(smallM, COLS/2 - 12, LINES/2 + 14);
	printAlp(smallE, COLS/2 - 6, LINES/2 + 14);
	printAlp(smallO, COLS/2 + 6, LINES/2 + 14);
	printAlp(smallV, COLS/2 + 12, LINES/2 + 14);
	printAlp(smallE, COLS/2 + 18, LINES/2 + 14);
	printAlp(smallR, COLS/2 + 24, LINES/2 + 14);

	system("say Game Over!");

	fflush(stdin);
}