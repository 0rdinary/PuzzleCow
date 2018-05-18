
#include <stdio.h>
int marble_exist[13][13] = { 0 };

typedef struct marble {
	int x;
	int y;
	int color;
}marble;

int main(void) {
	int xtemp, ytemp, i, j;
	marble now;
	while (1) {
		scanf_s("%d %d %d", &now.x, &now.y, &now.color);
		if (now.y < 0) {
			xtemp = 6; ytemp = 12;
			while (1) {
				if (now.x == 0) {
					if (xtemp + now.x > 12 || xtemp + now.x < 0) {
						now.x = -now.x;
					}
					else if (ytemp == 0) {
						marble_exist[0][xtemp] = now.color;
						break;
					}
					else if (ytemp % 2 == 0 && marble_exist[ytemp-2][xtemp] != 0) {
						if (xtemp == 6 && ytemp == 12) {
							printf("You lose");
							exit(1);
						}
						else
							marble_exist[ytemp][xtemp] = now.color;
						break;
					}
					
					else {
						xtemp += now.x;
						ytemp += now.y;
					}
				}
				else {
					if (xtemp + now.x > 12 || xtemp + now.x < 0) {
						now.x = -now.x;
					}
					else if (marble_exist[ytemp + now.y][xtemp + now.x] != 0) {
						if (xtemp == 6 && ytemp == 12) {
							printf("You lose");
							exit(1);
						}
						else
							marble_exist[ytemp][xtemp] = now.color;
						break;
					}
					else if (ytemp == 0) {
						marble_exist[0][xtemp] = now.color;
						break;
					}
					else {
						xtemp += now.x;
						ytemp += now.y;
					}
				}
			}
			for (i = 0; i < 13; i++) {
				for (j = 0; j < 13; j++)
					printf("%d ", marble_exist[i][j]);
				printf("\n");
			}
		}
	}
}
