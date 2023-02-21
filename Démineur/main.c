#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define GRID_LENGTH 10
#define BOMB_NUMBER 17

void displayGrid(unsigned char tableau[GRID_LENGTH][GRID_LENGTH]);
void placeBomb(unsigned char tableau[GRID_LENGTH][GRID_LENGTH], unsigned int quantity);
void play(unsigned char tableau[GRID_LENGTH][GRID_LENGTH], unsigned int x, unsigned int y);
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
                case 0:
                    printf(" - |");
                    continue;
                case 1:
                    printf(" - |");
                    continue;
                case 9:
                    printf(" %d |", bombs);
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

void placeBomb(unsigned char tableau[GRID_LENGTH][GRID_LENGTH], unsigned int quantity)
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

void play(unsigned char tableau[GRID_LENGTH][GRID_LENGTH], unsigned int x, unsigned int y)
{
    tableau[x][y] = 9;
}

int bombsAround(unsigned char tableau[GRID_LENGTH][GRID_LENGTH], unsigned int x, unsigned int y)
{
    unsigned int bombsAround = 0;

    if (0 <= x - 1) 
        if (tableau[x - 1][y] == 1) 
            bombsAround++;
        
    if (0 <= y - 1) 
        if (tableau[x][y - 1] == 1) 
            bombsAround++;
        
    if (9 >= x + 1) 
        if (tableau[x + 1][y] == 1)
            bombsAround++;

    if (9 >= y + 1)
        if (tableau[x][y + 1] == 1)
            bombsAround++;

    if (0 <= x - 1 && 0 <= y - 1)
        if (tableau[x - 1][y - 1] == 1)
            bombsAround++;
    
    if (0 >= x + 1 && 0 >= y + 1)
        if (tableau[x + 1][y + 1] == 1)
            bombsAround++;

    if (0 <= x - 1 && 9 >= y + 1)
        if (tableau[x - 1][y + 1] == 1)
            bombsAround++;

    if (0 <= y - 1 && 9 >= x + 1)
        if (tableau[x + 1][y - 1] == 1)
            bombsAround++;

    return bombsAround;
}