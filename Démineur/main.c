#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define GRID_LENGTH 10
#define BOMB_NUMBER 17
#define DISCOVERED_CELL 2
#define BOMB_CELL 1
#define HIDDEN_CELL 0

void displayGrid( char tableau[GRID_LENGTH][GRID_LENGTH]);
void placeBomb( char tableau[GRID_LENGTH][GRID_LENGTH],  int quantity, int x, int y);
int play( char tableau[GRID_LENGTH][GRID_LENGTH], int x,  int y);
int bombsAround( char tableau[GRID_LENGTH][GRID_LENGTH],  int x,  int y);

int main(int argc, char **argv)
{
    char tableau[GRID_LENGTH][GRID_LENGTH] = { 0 };
    int locationX = 0;
    int locationY = 0;
    int lap = 0;

    srand(time(NULL));

    displayGrid(tableau);
    printf("Choississez vos coordonnees : \n");
    printf("x : ");
    scanf_s("%d", &locationX);
    printf("y : ");
    scanf_s("%d", &locationY);

    placeBomb(tableau, BOMB_NUMBER, locationX - 1, locationX - 1);
    play(tableau, locationX - 1, locationY - 1);

    displayGrid(tableau);
    printf("TABLEAU AVANT PLAY\n");

    while (1) {
        printf("Choississez vos coordonnees : \n");
        printf("x : ");
        scanf_s("%d", &locationX);
        printf("y : ");
        scanf_s("%d", &locationY);


        play(tableau, locationX - 1, locationY - 1);

        displayGrid(tableau);
        printf("TABLEAU APRES PLAY\n");
        lap++;
    }
   
    return 0;
}

void displayGrid( char tableau[GRID_LENGTH][GRID_LENGTH])
{
    printf("\n");
    for (int z = 0; z < GRID_LENGTH; z++) {
        printf("----");
    }
    printf("-\n");
    for (int i  = 0; i < GRID_LENGTH; i++) {
        printf("|");
        for (int y = 0; y < GRID_LENGTH; y++) {
            switch (tableau[i][y]) {
                case HIDDEN_CELL:
                    printf(" - |");
                    continue;
                case BOMB_CELL:
                    printf(" X |");
                    continue;
                case DISCOVERED_CELL:
                    printf(" O |");
                    continue;
                default:
                    printf(" %d |", tableau[i][y] - 3);
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

void placeBomb( char tableau[GRID_LENGTH][GRID_LENGTH], int quantity, int x, int y)
{
    int bomb = 1;

    for (int i = 0; i < quantity; i++)
    {
        int locationX = rand() % GRID_LENGTH;
        int locationY = rand() % GRID_LENGTH;
        if (tableau[locationY][locationX] == BOMB_CELL && (x - 1 <= locationX && locationX <= x + 1 && y - 1 <= locationY && locationY <= y + 1)) {
            i--;
            continue;
        }
        else {
            printf("Bombe numero %d : %d | %d\n", bomb, locationX, locationY);
            tableau[locationY][locationX] = BOMB_CELL;
            bomb++;
        }
    }

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (x + i - 1 >= 0 && x + i - 1 < GRID_LENGTH && y + j - 1 >= 0 && y + j - 1 < GRID_LENGTH)
            {
                tableau[y + j - 1][x + i - 1] = HIDDEN_CELL;
            }
        }
    }

}


int play(char tableau[GRID_LENGTH][GRID_LENGTH],  int x,  int y)
{
    int bombs = bombsAround(tableau, x, y);
    printf("BEBONS %d\n", bombs);

    if (bombs != 0) {
        tableau[y][x] = bombs + 3;
        return 1;
    }

    tableau[y][x] = DISCOVERED_CELL;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (i - 1 != 0 || j - 1 != 0) {
                if ((x + i - 1 >= 0 && x + i - 1 < GRID_LENGTH && y + j - 1 >= 0 && y + j - 1 < GRID_LENGTH) && tableau[y + j - 1][x + i - 1] == HIDDEN_CELL) {
                    play(tableau, x + i - 1, y + j - 1);
                }
            }
        }
    }
    return 0;
}

int bombsAround( char tableau[GRID_LENGTH][GRID_LENGTH],  int x,  int y)
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