#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define GRID_LENGTH 10
#define BOMB_NUMBER 17
#define DISCOVERED_CELL 2
#define BOMB_CELL 1
#define HIDDEN_CELL 0

void displayGrid(unsigned char tableau[GRID_LENGTH][GRID_LENGTH]);
void placeBomb(unsigned char tableau[GRID_LENGTH][GRID_LENGTH], unsigned int quantity);
int play(unsigned char tableau[GRID_LENGTH][GRID_LENGTH], unsigned int x, unsigned int y);
int bombsAround(unsigned char tableau[GRID_LENGTH][GRID_LENGTH], unsigned int x, unsigned int y);

int main(int argc, char **argv)
{
    unsigned char tableau[GRID_LENGTH][GRID_LENGTH] = { 0 };
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

void displayGrid(unsigned char tableau[GRID_LENGTH][GRID_LENGTH])
{
    printf("\n");
    for (int z = 0; z < GRID_LENGTH; z++) {
        printf("----");
    }
    printf("-\n");
    for (int i = 0; i < GRID_LENGTH; i++) {
        printf("|");
        for (int y = 0; y < GRID_LENGTH; y++) {
            int bombs = bombsAround(tableau, i, y);
            switch (tableau[i][y]) {
                case HIDDEN_CELL:
                    printf(" - |");
                    continue;
                case BOMB_CELL:
                    printf(" - |");
                    continue;
                case DISCOVERED_CELL:
                    printf(" %d |", bombsAround(tableau, i, y));
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

void placeBomb(unsigned char tableau[GRID_LENGTH][GRID_LENGTH], unsigned int quantity)
{
    int bomb = 1;

    for (int i = 0; i < quantity; i++)
    {
        int locationX = rand() % GRID_LENGTH;
        int locationY = rand() % GRID_LENGTH;
        if (tableau[locationX][locationY] == BOMB_CELL) {
            i--;
            continue;
        }
        else {
            printf("Bombe numero %d : %d | %d\n", bomb, locationX, locationY);
            tableau[locationX][locationY] = BOMB_CELL;
            bomb++;
        }
    }
}

int play(unsigned char tableau[GRID_LENGTH][GRID_LENGTH], unsigned int x, unsigned int y)
{
    tableau[x][y] = DISCOVERED_CELL;

    int bombs = bombsAround(tableau, x, y);

    if (bombs != 0) {
        tableau[x][y] = DISCOVERED_CELL;
        return 1;
    }

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (i - 1 != 0 || j - 1 != 0) {
                if ((x + i - 1 >= 0 && x + i - 1 < GRID_LENGTH && y + j - 1 >= 0 && y + j - 1 < GRID_LENGTH) && tableau[y + j - 1][x + i - 1] == BOMB_CELL) {
                    tableau[i][j] = DISCOVERED_CELL;
                    play(tableau, i, j);
                }
            }
        }
    }
}

int bombsAround(unsigned char tableau[GRID_LENGTH][GRID_LENGTH], unsigned int x, unsigned int y)
{
    int bombsAround = 0;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (i - 1 != 0 || j - 1 != 0) {
                if ((x + i - 1 >= 0 && x + i - 1 < GRID_LENGTH && y + j - 1 >= 0 && y + j - 1 < GRID_LENGTH) && tableau[y + j - 1][x + i - 1] == BOMB_CELL) {
                    bombsAround++;
                }
            }
        }
    }

        return bombsAround;
    
}