#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void printBoard(int[][9], int);
void tprintBoard(int[][9], int, int);
void cls(void);
int checked[9][9][1];

int main()
{
    int Board[9][9] = {0}, ln, col;

    for(int *i=&checked[0][0][0]; i<=&checked[8][8][0]; i++)
    {
        *i = '?';
    }

    srand(time(NULL));
    for(int i=0; i<10; i++)
    {
        ln = rand() % 9;
        col = rand() % 9;
        Board[ln][col] = 1;
    }
    
    printBoard(Board, 0);
    
    while(1)
    {
        scanf("%d%d", &ln, &col);
        if(ln<1||ln>9||col<1||col>9) continue;
        ln--; col--;
        if(Board[ln][col])
        {
            printBoard(Board, 1);
            printf("GAME OVER!");
            break;
        }
        else
        {
            tprintBoard(Board, ln, col);
        }
    }
    
    return 0;
}

void printBoard(int board[][9], int minesVisible)
{
    cls();
    for(int i=0; i<9; i++)
    {
        if(i==0) printf("  1 2 3 4 5 6 7 8 9\n");
        printf("%d ", i+1);
        for(int j=0; j<9; j++)
        {
            if(board[i][j] && minesVisible)
                printf("■ ");
            else
                printf("□ ");
        }
        printf("\n");
    }
}

void tprintBoard(int board[][9], int ln, int col)
{
    int count=0;
    for(int i=-1; i<2; i++)
    {
        if(ln+i<1 || ln+i>8) continue;
        for(int j=-1; j<2; j++)
        {
            if(col+j<1 || col+j>8) continue;
            if(board[ln+i][col+j]) count++;
        }
    }
    
    checked[ln][col][0] = count;
    
    cls();
    
    for(int i=0; i<9; i++)
    {
        if(i==0) printf("  1 2 3 4 5 6 7 8 9\n");
        printf("%d ", i+1);
        for(int j=0; j<9; j++)
        {
            if(checked[i][j][0] != '?')
                printf("%d ", checked[i][j][0]);
            else
                printf("□ ");
        }
        printf("\n");
    }
}

void cls(void)
{
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}
    
