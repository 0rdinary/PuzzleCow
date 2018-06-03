#define WORD_SIZE  31
#define CIR_MAX    21
#define CIR_SIZE   3

#define BACK_FAIR  1
#define FONT_FAIR  2
#define FBACK_FAIR 3
#define BOX_FAIR   4

#define TRUE 1
#define FALSE 0

void makeCircle(char Circle[][CIR_MAX], int radius);
void printCircle(char Circle[][CIR_MAX], int x, int y);
void shoot(int angle);