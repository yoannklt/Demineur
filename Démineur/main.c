#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <windows.h>

#define GRID_LENGTH 10
#define BOMB_NUMBER 14
#define DISCOVERED_CELL 2
#define BOMB_CELL 1
#define HIDDEN_CELL 0

void welcome();
void displayGrid( char tableau[GRID_LENGTH][GRID_LENGTH]);
void placeBomb( char tableau[GRID_LENGTH][GRID_LENGTH],  int quantity, int x, int y);
int play( char tableau[GRID_LENGTH][GRID_LENGTH], int x,  int y);
int bombsAround( char tableau[GRID_LENGTH][GRID_LENGTH],  int x,  int y);
int victory(char tableau[GRID_LENGTH][GRID_LENGTH]);
void Color(int couleurDuTexte, int couleurDeFond);

int main(int argc, char **argv)
{
    char tableau[GRID_LENGTH][GRID_LENGTH] = { 0 };
    int locationX = 0;
    int locationY = 0;
    srand(time(NULL));
    welcome();
    displayGrid(tableau);
   
    printf("Quelle case voulez-vous decouvrir ? :\n");
    printf("X:");
    scanf_s(" %d", &locationX);
    printf("Y:");
    scanf_s(" %d", &locationY);
    while (locationX - 1 > GRID_LENGTH || locationY - 1 > GRID_LENGTH) {
        printf("\nJouez des coordonnees X et Y comprises entre 1 et %d\n", GRID_LENGTH);
        printf("Quelle case voulez-vous decouvrir ? :\n");
        printf("X:");
        scanf_s(" %d", &locationX);
        printf("Y:");
        scanf_s(" %d", &locationY);
    }
    
    placeBomb(tableau, BOMB_NUMBER, locationX, locationY);
    play(tableau, locationX - 1, locationY - 1);
    system("cls");
    displayGrid(tableau);

   
    while (1) {
        int lap = 1;
        clock_t temps = clock();
        int score = temps / CLOCKS_PER_SEC / lap + 1;

        printf("\nTEMPS : %d     TOUR : %d     SCORE : %d\n", (int)temps / CLOCKS_PER_SEC, lap, score);
        printf("\nQuelle case voulez-vous decouvrir ? :\n");
        printf("X:");
        scanf_s(" %d", &locationX);
        printf("Y:");
        scanf_s(" %d", &locationY);
        while (locationX - 1 > GRID_LENGTH || locationY - 1 > GRID_LENGTH) {
            printf("\nJouez des coordonnees X et Y comprises entre 1 et %d", GRID_LENGTH);
            printf("\nQuelle case voulez-vous decouvrir ? :\n");
            printf("X:");
            scanf_s(" %d", &locationX);
            printf("Y:");
            scanf_s(" %d", &locationY);
        }
  
        if (play(tableau, locationX - 1, locationY - 1) == 3) {
            system("cls");
            displayGrid(tableau);
            printf("\nVous avez perdu... :(\n");
            printf("\nTEMPS : %d     TOUR : %d     SCORE : %d\n", (int)temps / CLOCKS_PER_SEC, lap, score);
            return 1;
        }
        else if (victory(tableau) == 0) {
            system("cls");
            displayGrid(tableau);
            printf("\nVOUS AVEZ GAGNE !!!\n");
            printf("\nTEMPS : %d     TOUR : %d     SCORE : %d\n", (int)temps / CLOCKS_PER_SEC, lap, score);
            return 2;
        }

        lap++;
        system("cls");
        displayGrid(tableau);
    }
   
    return 0;
}

void welcome() {
    printf("*****************************************************\n");
    printf("||                                                 ||\n");
    printf("||                  Bienvenue !!!!                 ||\n");
    printf("||  Il y a %d bombes dans la grille, bon courage ! ||\n", BOMB_NUMBER);
    printf("||                                                 ||\n");
    printf("*****************************************************\n\n");
}

void displayGrid( char tableau[GRID_LENGTH][GRID_LENGTH])
{
    printf("   ");
    for (int k = 0; k < GRID_LENGTH; k++) {
        printf("| ");
        printf("%d ", k + 1);
    }
    printf("\n");
    for (int z = 0; z < GRID_LENGTH + 4; z++) {
        printf("---");
    }
    printf("--\n");
    for (int i  = 0; i < GRID_LENGTH; i++) {
        if (i == 9)
            printf(" 10|");
        else
            printf(" %d |", i + 1);
        for (int y = 0; y < GRID_LENGTH; y++) {
            switch (tableau[i][y]) {
                case HIDDEN_CELL:
                    printf(" - |");
                    continue;
                case BOMB_CELL:
                    printf(" - |");
                    continue;
                case DISCOVERED_CELL:
                    printf("   |");
                    continue;
                case 9:
                    Color(4, 7);
                    printf(" * ");
                    Color(15, 0);
                    printf("|");
                    continue;
                default:
                    printf(" %d |", tableau[i][y] - 3);
                    continue;
            }           
        }
        printf("\n");
        for (int z = 0; z < GRID_LENGTH + 4; z++) {
            printf("---");
        }
        printf("--\n");
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
            tableau[locationY][locationX] = BOMB_CELL;
            bomb++;
        }
    }

    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
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

    if (tableau[y][x] == BOMB_CELL) {
        for (int i = 0; i < GRID_LENGTH; i++) {
            for (int j = 0; j < GRID_LENGTH; j++) {
                if (tableau[i][j] == BOMB_CELL)
                    tableau[i][j] = 9;
            }
        }
        return 3;
    }
    else 
        tableau[y][x] = DISCOVERED_CELL;

    if (bombs != 0) {
        tableau[y][x] = bombs + 3;
        return 1;
    }

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

int victory(char tableau[GRID_LENGTH][GRID_LENGTH])
{
    for (int i = 0; i < GRID_LENGTH; i++) {
        for (int j = 0; j < GRID_LENGTH; j++) {
            if (tableau[i][j] == HIDDEN_CELL)
                return 1;
        }   
    }
    return 0;
}

// FONCTION QUI MET DE LA COULEUR DANS MA VIE
void Color(int couleurDuTexte, int couleurDeFond) 
{
    HANDLE H = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H, couleurDeFond * 16 + couleurDuTexte);
}