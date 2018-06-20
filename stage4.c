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
	FILE *fp;
	int input;
	int buffer[2];
	int xPower = 0;
	int pid;
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
		stage[startY][startX] = rand()%4 + '5';
		initStage(circle, stage);

		// loop shoot

		srand(time(NULL));

		while (!isEnd(stage))
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

			if (isOver(stage))
			{
				system("say Game Over!");

				ch = getchar();

				break;

				fp = fopen("best.bin", "wb");
				buffer[0] = bestStage;
				buffer[1] = bestScore;
				fwrite(buffer, sizeof(int), 2, fp);
				fclose(fp);
			}
		}

		if (isEnd(stage))
		{
			system("say Clear!");

			stage2();
		}
}
