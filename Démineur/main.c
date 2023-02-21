#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define GRID_LENGHT 10
#define BOMB_NUMBER 17

void displayGrid(unsigned char tableau[GRID_LENGHT][GRID_LENGHT]);
void placeBomb(unsigned char tableau[GRID_LENGHT][GRID_LENGHT], unsigned int quantity);
void play(unsigned char tableau[GRID_LENGHT][GRID_LENGHT], unsigned int x, unsigned int y);

int main(int argc, char **argv)
{
    unsigned char tableau[GRID_LENGHT][GRID_LENGHT] = { 0 };
    int locationX = 0;
    int locationY = 0;

    srand(time(NULL));

    placeBomb(tableau, BOMB_NUMBER);

    displayGrid(tableau);
    printf("Choississez vos coordonnées (sous forme x : y) : ");
    printf("x : ");
    scanf_s("%d", &locationX);
    printf("y");
    scanf_s("%d", &locationY);
    play(tableau, locationX, locationY);

    displayGrid(tableau);
    return 0;
}

void displayGrid(unsigned char tableau[GRID_LENGHT][GRID_LENGHT])
{
    printf("\n");
    for (int z = 0; z < GRID_LENGHT; z++) {
        printf("----");
    }
    printf("-\n");
    for (int i = 0; i < GRID_LENGHT; i++) {
        printf("|");
        for (int y = 0; y < GRID_LENGHT; y++) {
            switch (tableau[i][y]) {
                case 0:
                    printf(" - |");
                    continue;
                case 1:
                    printf(" - |");
                    continue;
                case 9:
                    printf("%d", tableau[i][y]);
                    continue;
                default:
                    printf(" %d |", tableau[i][y]);
                    continue;
            }           
        }
        printf("\n");
        for (int z = 0; z < GRID_LENGHT; z++) {
            printf("----");
        }
        printf("-\n");
    }
}

void placeBomb(unsigned char tableau[GRID_LENGHT][GRID_LENGHT], unsigned int quantity)
{
    int bomb = 1;

    for (int i = 0; i < quantity; i++)
    {
        int locationX = rand() % GRID_LENGHT;
        int locationY = rand() % GRID_LENGHT;
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

void play(unsigned char tableau[GRID_LENGHT][GRID_LENGHT], unsigned int x, unsigned int y)
{
    tableau[x][y] = 9;
}