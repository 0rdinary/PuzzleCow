
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int marble_exist[44][32] = { 0 };

int stack[500][500];

void pop(int* x, int* y);
typedef struct marble {
	int x;
	int y;
	int color;
}marble;

int blow(int x, int y){
    return 0;
}

void makeball(int x, int y, int color){
    int i;
    
    for(i = 0; i < 4; i++){
        marble_exist[y][x+i] = color;
    }
    for(i = 0; i < 4; i++){
        marble_exist[y+1][x+i] = color;
    }
    for(i = 0; i < 4; i++){
        marble_exist[y+2][x+i] = color;
    }
    for(i = 0; i < 4; i++){
        marble_exist[y+3][x+i] = color;
    }
    
}

int main(void) {
	int xtemp, ytemp, i, j;
	marble now;
	while (1) {
        srand(time(NULL));
		scanf("%d %d", &now.x, &now.y);
        now.color = rand() % 9 + 1;
		if (now.y < 0) {
			xtemp = 15; ytemp = 44;
			while (1) {
					if (xtemp + now.x > 29 || xtemp + now.x < 0) {  //if x is out
						now.x = -now.x;
					}
					else if (ytemp + now.y < 0) {  //if y arrived ceiling
						makeball(xtemp,ytemp,now.color);
						break;
					}
                    else if(ytemp == 0){
                        makeball(xtemp,ytemp,now.color);
                    }
					else if (marble_exist[ytemp + now.y][xtemp + now.x] != 0) {
						if (xtemp == 6 && ytemp == 12) {
							printf("You lose");
							exit(1);
						}
						else
							makeball(xtemp,ytemp,now.color);
						break;
					}
					
					else {
                        //marble_exist[ytemp][xtemp] = now.color;
						xtemp += now.x;
						ytemp += now.y;
					}
			}
			for (i = 0; i < 44; i++) {
				for (j = 0; j < 32; j++)
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
