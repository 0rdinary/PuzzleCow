/************************************************************
 * Filename      : PuzzleCow.c
 * Author        : Team Hobanwoo) mwJeong
 * Modified Date : May, 31, 2018    13:42
 * Purpose       : Main file of game with main()
 ************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curses.h>
#include <unistd.h>
#include <termios.h>
#include "library.h"

int bestStage = 0;
int bestScore = 0;
int score = 0;

void mainMenu();
void printAlphabet(char alphabet[][WORD_SIZE], int x, int y);
void printBox();

int main()
{
    FILE *fp;
    int buffer[2];    // store best Score

    //initialization
    char userInput;
    initscr();
    mainMenu();

    // read best
    fp = fopen("best.bin", "rb");
    if (fp != NULL)
    {
        fread(buffer, sizeof(int), 2, fp);
        bestStage = buffer[0];
        bestScore = buffer[1];
        fclose(fp);
    }

    fflush(stdin);
    userInput = getchar();
    while (userInput != 'q')
    {
        switch(userInput)
        {
            case '1' : stage1();
                        break;
            case '2' : stage2();
                        break;
            case '3' : stage3();
                        break;
            case '4' : stage4();
                        break;
        }

        userInput = getchar();
    }

    // save users data
    fp = fopen("best.bin", "wb");
    buffer[0] = bestStage;
    buffer[1] = bestScore;
    fwrite(buffer, sizeof(int), 2, fp);
    fclose(fp);

    endwin();
    return 0;
}

void mainMenu()
{
    int i , j;
    int ch;
    char string[20];
    char Circle[CIR_MAX][CIR_MAX] = {0, };
    struct termios ttystate;
    struct termios origin;

    char P[WORD_SIZE][WORD_SIZE] = { {"1111111111  "},
                                     {"11110000111 "},
                                     {"11110   111 "},
                                     {"11111111110 "},
                                     {"1111000000  "},
                                     {"11110       "},
                                     {"11110       "},
                                     {"00000       "}};

    char U[WORD_SIZE][WORD_SIZE] = { {"1110    1110"},
                                     {"1110    1110"},
                                     {"1110    1110"},
                                     {"1110    1110"},
                                     {"1110    1110"},
                                     {"111111111110"},
                                     {"  1111111110"},
                                     {"   000000000"} };

    char Z[WORD_SIZE][WORD_SIZE] = { {"111111111110"},
                                     {"111111111110"},
                                     {"       11110"},
                                     {"     111100 "},
                                     {"   111100   "},
                                     {" 111100     "},
                                     {"111111111110"},
                                     {"000000000000"} };

    char L[WORD_SIZE][WORD_SIZE] = { {"1110        "},
                                     {"1110        "},
                                     {"1110        "},
                                     {"1110        "},
                                     {"1110        "},
                                     {"1110        "},
                                     {"111111111110"},
                                     {"000000000000"}
                                                    };
    char E[WORD_SIZE][WORD_SIZE] = { {"111111111110"},
                                     {"111111111110"},
                                     {"111100      "},
                                     {"11111111110 "},
                                     {"11111111110 "},
                                     {"111100      "},
                                     {"111111111110"},
                                     {"111111111110"},
                                     {"000000000000"} };
                                      
    char C[WORD_SIZE][WORD_SIZE] = { {" 111111111  "},
                                     {"11100000111 "},
                                     {"1110    000 "},
                                     {"1110        "},
                                     {"1110        "},
                                     {"1110    111 "},
                                     {" 1111111110 "},
                                     {"  00000000  "} };
                                     
    char O[WORD_SIZE][WORD_SIZE] = { {" 111111111  "},
                                     {"111000001110"},
                                     {"1110    1110"},
                                     {"1110    1110"},
                                     {"1110    1110"},
                                     {"1110    1110"},
                                     {" 1111111110 "},
                                     {"  00000000"} };

    char W[WORD_SIZE][WORD_SIZE] = { {"110      110"},
                                     {"110 1110 110"},
                                     {"110 1110 110"},
                                     {"110 1110 110"},
                                     {"110 1110 110"},
                                     {" 1111111110 "},
                                     {"  11101110  "},
                                     {"   00  00   "} };

    
        // initialize curses and settings
        keypad(stdscr, TRUE);   // to use arrow key
        clear();
        //use to color_mode if return true;
        start_color();
        refresh();
        //init_pair(a,b,c) = setting color;
        // a = index, b = color, c = blink color
        init_pair(BACK_FAIR, COLOR_BLACK, COLOR_BLACK);
        init_pair(FONT_FAIR, COLOR_BLACK, COLOR_GREEN);
        init_pair(FBACK_FAIR, COLOR_BLACK, COLOR_WHITE);
        init_pair(BOX_FAIR, COLOR_BLACK, COLOR_YELLOW);
        init_pair(BALL1, COLOR_RED, COLOR_RED);
        init_pair(BALL2, COLOR_YELLOW, COLOR_YELLOW);
        init_pair(BALL3, COLOR_BLUE, COLOR_BLUE);
        init_pair(BALL4, COLOR_GREEN, COLOR_GREEN);


        // print Box
        printBox();

        // print puzzle
        printAlphabet(P, COLS/2 - 39, LINES/8);
        printAlphabet(U, COLS/2 - 26, LINES/8 - 1);
        printAlphabet(Z, COLS/2 - 12, LINES/8 - 2);
        printAlphabet(Z, COLS/2 + 2,  LINES/8 - 2);
        printAlphabet(L, COLS/2 + 16, LINES/8 - 1);
        printAlphabet(E, COLS/2 + 30, LINES/8);

        // print cow
        printAlphabet(C, COLS/2 - 19, LINES/8 + 11);
        printAlphabet(O, COLS/2 - 6, LINES/8 + 10);
        printAlphabet(W, COLS/2 + 8, LINES/8 + 11);
    
}

void printAlphabet(char alphabet[][WORD_SIZE], int x, int y)
{
    /*
    * purpose : print Title`s letters
    */
    int i, j;

    for (i = 0; i < alphabet[i][0] != '\0'; i++)
    {
        for (j = 0; alphabet[i][j] != '\0'; j++)
        {
            if (alphabet[i][j] == '1')
                attron(COLOR_PAIR(FONT_FAIR));
            else if (alphabet[i][j] == '0')
                attron(COLOR_PAIR(FBACK_FAIR));
            else
            {
                attroff(COLOR_PAIR(FONT_FAIR));
                attroff(COLOR_PAIR(FBACK_FAIR));
            }
            mvhline(y+i, x+j, ' ', 1);
        }
     }
     refresh();
}

void printBox()
{
    /*
     * purpose : print Box in Title
     */
    int y, x;

    move(COLS/2 - 44, LINES/8 - 4);
    attron(COLOR_PAIR(BOX_FAIR));
    for (y = LINES/8 - 4; y <= LINES/8 + 21; y++) {
    
        if (y == LINES/8 - 4 || y == LINES/8 + 21)
            mvhline(y, COLS/2 -44, ' ', 91);
        else 
        {
            mvhline(y, COLS/2 - 44, ' ', 2);
            mvhline(y, COLS/2 + 45, ' ', 2);
        }
    }
    attroff(COLOR_PAIR(BOX_FAIR));
    refresh();
}
