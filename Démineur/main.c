#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define GRID_LENGTH 10
#define BOMB_NUMBER 5


void displayGrid( char tableau[GRID_LENGTH][GRID_LENGTH]);
void placeBomb( char tableau[GRID_LENGTH][GRID_LENGTH],  int quantity);
void play( char tableau[GRID_LENGTH][GRID_LENGTH],  int x,  int y);
int bombsAround( char tableau[GRID_LENGTH][GRID_LENGTH],  int x,  int y);

int main(int argc, char **argv)
{
    char tableau[GRID_LENGTH][GRID_LENGTH] = { 0 };
    int locationX = 0;
    int locationY = 0;

    srand(time(NULL));

    placeBomb(tableau, BOMB_NUMBER);

    displayGrid(tableau);


    printf("Choississez vos coordonnees : \n");
    printf("x : ");
    scanf_s("%d", &locationX);
    printf("y : ");
    scanf_s("%d", &locationY);
    if (locationX <= 10 || locationY <= 10)
        play(tableau, locationX - 1, locationY - 1);
    else
        printf("Jouez des coordonnees comprises entre 1 et 10\n");
    displayGrid(tableau);
    return 0;
}

void displayGrid( char tableau[GRID_LENGTH][GRID_LENGTH])
{
    printf("\n");
    for (int z = 0; z < GRID_LENGTH; z++) {
        printf("----");
    }
    printf("-\n");
    for (int i = 0; i < GRID_LENGTH; i++) {
        printf("|");
        for (int y = 0; y < GRID_LENGTH; y++) {
            switch (tableau[i][y]) {
                case 0:
                    printf(" - |");
                    continue;
                case 1:
                    printf(" - |");
                    continue;
                case 9:
                    if (tableau[i][y] != 1)
                        printf(" %d |", bombsAround(tableau, i, y));
                    continue;
                default:
                    printf(" %d |", tableau[i][y]);
                    continue;
            }           
        }
        printf("\n");
        for (int z = 0; z < GRID_LENGTH; z++) {
            printf("----");
        }
        printf("-\n");
    }
}

void placeBomb( char tableau[GRID_LENGTH][GRID_LENGTH],  int quantity)
{
    int bomb = 1;

    for (int i = 0; i < quantity; i++)
    {
        int locationX = rand() % GRID_LENGTH;
        int locationY = rand() % GRID_LENGTH;
        if (tableau[locationX][locationY] == 1) {
            i--;
            continue;
        }
        else {
            printf("Bombe numero %d : %d | %d\n", bomb, locationX, locationY);
            tableau[locationX][locationY] = 1;
            bomb++;
        }
    }
}

void play(char tableau[GRID_LENGTH][GRID_LENGTH], int x, int y)
{
    int bombs = bombsAround(tableau, x, y);
    
    tableau[x][y] = 9;

    /*while (bombs == 0)
    {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if ()
            }
        }
    }*/
}

int bombsAround(char tableau[GRID_LENGTH][GRID_LENGTH], int x, int y)
{
    int bombsAround = 0;

    if (x - 1 >= 0 ) {
        if (tableau[x - 1][y] == 1)
            bombsAround++;
    }

    if (GRID_LENGTH >= x + 1)
        if (tableau[x + 1][y] == 1)
            bombsAround++;

    if (0 <= y - 1)
        if (tableau[x][y - 1] == 1)
            bombsAround++;

    if (GRID_LENGTH >= y + 1)
        if (tableau[x][y + 1] == 1)
            bombsAround++;

    if (GRID_LENGTH >= x + 1 && GRID_LENGTH >= y + 1)
        if (tableau[x + 1][y + 1] == 1)
            bombsAround++;

    if (0 <= x - 1 && 0 <= y - 1)
        if (tableau[x - 1][y - 1] == 1)
            bombsAround++;

    if (0 <= x - 1 && GRID_LENGTH >= y + 1)
        if (tableau[x - 1][y + 1] == 1)
            bombsAround++;

    if (0 <= y - 1 && GRID_LENGTH >= x + 1)
        if (tableau[x + 1][y - 1] == 1)
            bombsAround++;

    return bombsAround;
}