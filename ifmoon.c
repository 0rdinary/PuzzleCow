
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int marble_exist[13][13] = { 0 };

int stack[500][500];

void pop(int* x, int* y)
typedef struct marble {
	int x;
	int y;
	int color;
}marble;

int blow(int x, int y){
    return 0;
}

int main(void) {
	int xtemp, ytemp, i, j;
	marble now;
	while (1) {
        srand(time(NULL));
		scanf("%d %d", &now.x, &now.y);
        now.color = rand() % 9 + 1;
		if (now.y < 0) {
			xtemp = 6; ytemp = 12;
			while (1) {
					if (xtemp + now.x > 12 || xtemp + now.x < 0) {  //if x is out
						now.x = -now.x;
					}
					else if (ytemp + now.y < 0) {  //if y arrived ceiling
						marble_exist[0][xtemp] = now.color;
						break;
					}
                    else if(ytemp == 0){
                        marble_exist[ytemp][xtemp] = now.color;
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
					
					else {
                        marble_exist[ytemp][xtemp] = now.color;
						xtemp += now.x;
						ytemp += now.y;
					}
			}
			for (i = 0; i < 13; i++) {
				for (j = 0; j < 13; j++)
					printf("%d ", marble_exist[i][j]);
				printf("\n");
			}
            fflush(0);
		}
        else{
            printf("Y value must be negative\n");
        }
	}
}
