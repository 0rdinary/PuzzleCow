#include <stdio.h>
#include <string.h>
#include <curses.h>
#include "library.h"

// make 
void makeCircle(char Circle[][CIR_MAX], int radius)
{
    int i,j,u;
    /*
    for(i = 0; i < radius*2; i++)
        for(j = 0 ; j < radius*2; j++)
        	if (radius * radius > (i+0.5-radius)*(i+0.5-radius) + (j+0.5-radius)*(j+0.5-radius) )
            	Circle[i][j] = '1';
            else
            	Circle[i][j] = '0';*/

    strcpy(Circle[0], "011110");
    strcpy(Circle[1], "111111");
    strcpy(Circle[2], "111111");
    strcpy(Circle[3], "111111");
    strcpy(Circle[4], "111111");
    strcpy(Circle[5], "011110");

}

void printCircle(char Circle[][CIR_MAX], int x, int y, int Color)
{
	int i, j;

    for (i = 0; Circle[i][0] != '\0'; i++)
    {
        for (j = 0; Circle[i][j] != '\0'; j++)
        {
            if (Circle[i][j] == '1')
                attron(COLOR_PAIR(Color));
            else if (Circle[i][j] == '0')
                attron(COLOR_PAIR(BACK_FAIR));
            else
            {
                attroff(COLOR_PAIR(FONT_FAIR));
                attroff(COLOR_PAIR(BACK_FAIR));
            }
            mvhline(y+i, x+j, ' ', 1);
        }
     }
     refresh();
}

void deleteCircle(int x, int y)
{
    int i;

    attron(COLOR_PAIR(BACK_FAIR));
    for (i = 0; i < CIR_SIZE*2; i++)
    {
        mvhline(y + i, x , ' ', CIR_SIZE*2);
    }
    attroff(COLOR_PAIR(BACK_FAIR));
    refresh();
}