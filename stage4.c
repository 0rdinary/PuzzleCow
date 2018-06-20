#include "library.h"
#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <unistd.h>
#include <signal.h>
#include <math.h>
#include <time.h>
#include <sys/types.h>

extern char number0[7][5];
extern int score;
extern int bestScore;
extern int bestStage;

void stage4()
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
	char stage[12][15] = 	{ {"707000000000808"},
						      {"070500000006080"},
						      {"005080000080600"},
						      {"000806000708000"},
						      {"000060505070000"},
						      {"000000050000000"},
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
			system("say Game Over!");

			return;
		}

		if (isEnd(stage))
		{
			system("say Winner Winner Chiken Dinner!");

			if (bestStage < 4)
				bestStage = 4;

			return;
		}
	}
}
