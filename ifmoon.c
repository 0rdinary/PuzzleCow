//
//  ifmoon.c
//  ifmoon
//
//  Created by knuprime008 on 2018. 5. 17..
//  Copyright © 2018년 knuprime008. All rights reserved.
//

#include <stdio.h>
int marble_exist[11][15] = {0};

typedef struct marble{
    int x;
    int y;
    int color;
}marble;

int main(void){
    int xtemp, ytemp;
    marble now;
    while(1){
        scanf("%d %d %d",&now.x, &now.y, &now.color);
        if(now.x != 0 && now.y != 0){
            xtemp = 7; ytemp = 10;
            while(1){
                if((xtemp + now.x > 14 || xtemp + now.x < 0) || (ytemp + now.y > 10 || ytemp + now.y < 0)){
                    if(xtemp + now.x > 14 || xtemp + now.x < 0){
                        now.x = - now.x;
                    }
                    if(ytemp + now.y > 10 || ytemp + now.y < 0){
                        now.y = - now.y;
                    
                    }
                }
                else if(marble_exist[ytemp + now.y][xtemp + now.x] != 0){
                    if(xtemp == 7 && ytemp == 10){
                        printf("You lose");
                        exit(1);
                    }
                    else
                        marble_exist[ytemp][xtemp] = now.color;
                    break;
                }
                else if(ytemp - now.y < 0){
                    marble_exist[0][xtemp] = now.color;
                    break;
                }
                else if(ytemp == now.y){
                    marble_exist[0][xtemp + now.x] = now.color;
                    break;
                }
                else{
                    xtemp += now.x;
                    ytemp += now.y;
                }
            }
        }
    }
}
