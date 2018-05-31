#include <stdio.h>
#include <curses.h>

#define WORD_SIZE  31
#define CIR_MAX    21

#define BACK_FAIR  1
#define FONT_FAIR  2
#define FBACK_FAIR 3
#define BOX_FAIR   4

// make 
void makeCircle(char Circle[][CIR_MAX], int radius)
{
    int i,j,u;

    for(i = 0; i < radius*2; i++)
        for(j = 0 ; j < radius*2; j++)
        	if (radius * radius > (i+0.5-radius)*(i+0.5-radius) + (j+0.5-radius)*(j+0.5-radius) )
            	Circle[i][j] = '1';
            else
            	Circle[i][j] = '0';
}

void printCircle(char Circle[][CIR_MAX], int x, int y)
{
	int i, j;

    for (i = 0; i < Circle[i][0] != '\0'; i++)
    {
        for (j = 0; Circle[i][j] != '\0'; j++)
        {
            if (Circle[i][j] == '1')
                attron(COLOR_PAIR(FONT_FAIR));
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