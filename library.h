#define WORD_SIZE  31
#define CIR_MAX    21
#define CIR_SIZE   3

#define BACK_FAIR  1
#define FONT_FAIR  2
#define FBACK_FAIR 3
#define BOX_FAIR   4

#define BALL1 5
#define BALL2 6
#define BALL3 7
#define BALL4 8

#define TRUE 1
#define FALSE 0

void makeCircle(char Circle[][CIR_MAX], int radius);
void printCircle(char Circle[][CIR_MAX], int x, int y, int Color);
void deleteCircle(int x, int y);
void shoot(int x, char circle[][CIR_MAX], char map[][15], int *tab);
void stage1();
void printStageBorder();
void initStage(char circle[][CIR_MAX], char map[][15]);
int isEnd(char map[][15]);
void printPower(int xPower);
int isAttached(char map[][15], int x, int y);
int isOver(char map[][15]);
void search(char map[][15], int xBall, int yBall, char ball);
void stage2();
void printScore(char number[][5], int x, int y);
void stage3();