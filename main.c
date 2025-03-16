/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <string.h>
#define ROWS 5
#define COLS 6
#define SPACE 0
#define WALL 1
#define TARGET 2
#define BOX 3
#define BOX_ON_TARGET 4
#define PERSON 5
#define PERSON_ON_TARGET 6

void PrintRoom(int room[ROWS][COLS]) {
    int i, j;
    char zero = ' ';
    char one = '#';
    char two = '*';
    char three = 'O';
    char four = '@';
    char five = 'X';
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            if (room[i][j] == SPACE) {
                printf("%c", zero);
            }
            else if (room[i][j] == WALL) {
                printf("%c", one);
            }
            else if (room[i][j] == TARGET) {
                printf("%c", two);
            }
            else if (room[i][j] == BOX) {
                printf("%c", three);
            }
            else if (room[i][j] == BOX_ON_TARGET) {
                printf("%c", four);
            }
            else if (room[i][j] == PERSON || room[i][j] == PERSON_ON_TARGET) {
                printf("%c", five);
            }
        }
        printf("\n");
    }
}

void InitialiseRoom(int room[ROWS][COLS], char *layout) {
    int i;
    int j;
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            if ((i+j+i*(COLS-1)) >= strlen(layout)) {
                room[i][j] = WALL;
            }
            else {
            room[i][j] = (layout[i+j+i*(COLS-1)]-48);
            }
        }
    }
}

void LocatePerson(int room[ROWS][COLS], int *row, int *col) {
    int i;
    int j;
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            if (room[i][j] == PERSON || room[i][j] == PERSON_ON_TARGET) {
                *row = i;
                *col = j;
            }
        }
    }
}

void UndoMove(int room[ROWS][COLS], char *allMoves) {
    int row, col;
    int k = 1;
    int k2 = 0;
    int n = 0;
    int m = 0;
    int number;
    int move;
    LocatePerson(room, &row, &col);
    while (k < 100) {
        if (allMoves[k] == '0' || allMoves[k] == '1') {
        k = k+2;
        }
        else {
            if (allMoves[k-2] == '0' || allMoves[k-2] == '1') {
                number = allMoves[k-2];
                move = allMoves[k-3];
                k2 = k;
                k = 100;
            }
        }
    }
    if (move == 'w') {
        n = 1;
    }
    else if (move == 's') {
        n = -1;
    }
    else if (move == 'a') {
        m = 1;
    }
    else if (move == 'd') {
        m = -1;
    }
    if (number == '0') {
        if (room[row][col] == PERSON_ON_TARGET && room[row+n][col+m] == SPACE) {
            room[row+n][col+m] = PERSON;
            room[row][col] = TARGET;
        }
        else if (room[row][col] == PERSON_ON_TARGET && room[row+n][col+m] == TARGET) {
            room[row+n][col+m] = PERSON_ON_TARGET;
            room[row][col] = TARGET;
        }
        else if (room[row][col] == PERSON && room[row+n][col+m] == SPACE) {
            room[row+n][col+m] = PERSON;
            room[row][col] = SPACE;
        }
        else if (room[row][col] == PERSON && room[row+n][col+m] == TARGET) {
            room[row+n][col+m] = PERSON_ON_TARGET;
            room[row][col] = SPACE;
        }
    }
    else if (number == '1') {
        if (room[row][col] == PERSON && room[row+n][col+m] == TARGET && room[row-n][col-m] == BOX) {
            room[row+n][col+m] = PERSON_ON_TARGET;
            room[row-n][col-m] = SPACE;
            room[row][col] = BOX;
        }
        else if (room[row][col] == PERSON && room[row+n][col+m] == SPACE && room[row-n][col-m] == BOX) {
            room[row+n][col+m] = PERSON;
            room[row-n][col-m] = SPACE;
            room[row][col] = BOX;
        }
        else if (room[row][col] == PERSON && room[row+n][col+m] == TARGET && room[row-n][col-m] == BOX_ON_TARGET) {
            room[row+n][col+m] = PERSON_ON_TARGET;
            room[row-n][col-m] = TARGET;
            room[row][col] = BOX;
        }
        else if (room[row][col] == PERSON && room[row+n][col+m] == SPACE && room[row-n][col-m] == BOX_ON_TARGET) {
            room[row+n][col+m] = PERSON;
            room[row-n][col-m] = TARGET;
            room[row][col] = BOX;
        }
        else if (room[row+n][col+m] == TARGET && room[row-n][col-m] == BOX) {
            room[row+n][col+m] = PERSON_ON_TARGET;
            room[row-n][col-m] = SPACE;
            room[row][col] = BOX_ON_TARGET;
        }
        else if (room[row+n][col+m] == SPACE && room[row-n][col-m] == BOX) {
            room[row+n][col+m] = PERSON;
            room[row-n][col-m] = SPACE;
            room[row][col] = BOX_ON_TARGET;
        }
        else if (room[row+n][col+m] == TARGET && room[row-n][col-m] == BOX_ON_TARGET) {
            room[row+n][col+m] = PERSON_ON_TARGET;
            room[row-n][col-m] = TARGET;
            room[row][col] = BOX_ON_TARGET;
        }
        else if (room[row+n][col+m] == SPACE && room[row-n][col-m] == BOX_ON_TARGET) {
            room[row+n][col+m] = PERSON;
            room[row-n][col-m] = TARGET;
            room[row][col] = BOX_ON_TARGET;
        }
    }
    allMoves[k2-2] = 0;
    allMoves[k2-3] = 0;
}

void MakeMove(int room[ROWS][COLS], char move, char *allMoves) {
    int row, col;
    int k = 1;
    int n = 0;
    int m = 0;
    LocatePerson(room, &row, &col);
    if (move == 'z') {
        UndoMove(room, allMoves);
    }
    if (move == 'w') {
        n = -1;
    }
    else if (move == 'a') {
        m = -1;
    }
    else if (move == 's') {
        n = 1;
    } 
    else if (move == 'd') {
        m = 1;
    } 
    if (n != 0 || m != 0) {
        if (room[row][col] == PERSON_ON_TARGET && room[row+n][col+m] == SPACE) {
            room[row+n][col+m] = PERSON;
            room[row][col] = TARGET;
            while (k < 100) {
                if (allMoves[k] == '0' || allMoves[k] == '1') {
                    k = k+2;
                }
                else {
                    allMoves[k] = '0';
                    allMoves[k-1] = move;
                    k = 100;
                }
            }
        }
        else if (room[row][col] == PERSON_ON_TARGET && room[row+n][col+m] == TARGET) {
            room[row+n][col+m] = PERSON_ON_TARGET;
            room[row][col] = TARGET;
            while (k < 100) {
                if (allMoves[k] == '0' || allMoves[k] == '1') {
                    k = k+2;
                }
                else {
                    allMoves[k] = '0';
                    allMoves[k-1] = move;
                    k = 100;
                }
            }
        }
        else if (room[row+n][col+m] == SPACE) {
            room[row+n][col+m] = PERSON;
            room[row][col] = SPACE;
            while (k < 100) {
                if (allMoves[k] == '0' || allMoves[k] == '1') {
                    k = k+2;
                }
                else {
                    allMoves[k] = '0';
                    allMoves[k-1] = move;
                    k = 100;
                }
            }
        }
        else if (room[row+n][col+m] == TARGET) {
            room[row+n][col+m] = PERSON_ON_TARGET;
            room[row][col] = SPACE;
            while (k < 100) {
                if (allMoves[k] == '0' || allMoves[k] == '1') {
                    k = k+2;
                }
                else {
                    allMoves[k] = '0';
                    allMoves[k-1] = move;
                    k = 100;
                }
            }
        }
        else if (room[row][col] == PERSON_ON_TARGET && room[row+n][col+m] == BOX && room[row+n*2][col+m*2] == SPACE) {
            room[row+n][col+m] = PERSON;
            room[row+n*2][col+m*2] = BOX;
            room[row][col] = TARGET;
            while (k < 100) {
                if (allMoves[k] == '0' || allMoves[k] == '1') {
                    k = k+2;
                }
                else {
                    allMoves[k] = '1';
                    allMoves[k-1] = move;
                    k = 100;
                }
            }
        }
        else if (room[row+n][col+m] == BOX && room[row+n*2][col+m*2] == SPACE) {
            room[row+n][col+m] = PERSON;
            room[row+n*2][col+m*2] = BOX;
            room[row][col] = SPACE;
            while (k < 100) {
                if (allMoves[k] == '0' || allMoves[k] == '1') {
                    k = k+2;
                }
                else {
                    allMoves[k] = '1';
                    allMoves[k-1] = move;
                    k = 100;
                }
            }
        }
        else if (room[row][col] == PERSON_ON_TARGET && room[row+n][col+m] == BOX && room[row+n*2][col+m*2] == TARGET) {
            room[row+n][col+m] = PERSON;
            room[row+n*2][col+m*2] = BOX_ON_TARGET;
            room[row][col] = TARGET;
            while (k < 100) {
                if (allMoves[k] == '0' || allMoves[k] == '1') {
                    k = k+2;
                }
                else {
                    allMoves[k] = '1';
                    allMoves[k-1] = move;
                    k = 100;
                }
            }
        }
        else if (room[row+n][col+m] == BOX && room[row+n*2][col+m*2] == TARGET) {
            room[row+n][col+m] = PERSON;
            room[row+n*2][col+m*2] = BOX_ON_TARGET;
            room[row][col] = SPACE;
            while (k < 100) {
                if (allMoves[k] == '0' || allMoves[k] == '1') {
                    k = k+2;
                }
                else {
                    allMoves[k] = '1';
                    allMoves[k-1] = move;
                    k = 100;
                }
            }
        }
        else if (room[row][col] == PERSON_ON_TARGET && room[row+n][col+m] == BOX_ON_TARGET && room[row+n*2][col+m*2] == SPACE) {
            room[row+n][col+m] = PERSON_ON_TARGET;
            room[row+n*2][col+m*2] = BOX;
            room[row][col] = TARGET;
            while (k < 100) {
                if (allMoves[k] == '0' || allMoves[k] == '1') {
                    k = k+2;
                }
                else {
                    allMoves[k] = '1';
                    allMoves[k-1] = move;
                    k = 100;
                }
            }
        }
        else if (room[row+n][col+m] == BOX_ON_TARGET && room[row+n*2][col+m*2] == SPACE) {
            room[row+n][col+m] = PERSON_ON_TARGET;
            room[row+n*2][col+m*2] = BOX;
            room[row][col] = SPACE;
            while (k < 100) {
                if (allMoves[k] == '0' || allMoves[k] == '1') {
                    k = k+2;
                }
                else {
                    allMoves[k] = '1';
                    allMoves[k-1] = move;
                    k = 100;
                }
            }
        }
        else if (room[row][col] == PERSON_ON_TARGET && room[row+n][col+m] == BOX_ON_TARGET && room[row+n*2][col+m*2] == TARGET) {
            room[row+n][col+m] = PERSON_ON_TARGET;
            room[row+n*2][col+m*2] = BOX_ON_TARGET;
            room[row][col] = TARGET;
            while (k < 100) {
                if (allMoves[k] == '0' || allMoves[k] == '1') {
                    k = k+2;
                }
                else {
                    allMoves[k] = '1';
                    allMoves[k-1] = move;
                    k = 100;
                }
            }
        }
        else if (room[row+n][col+m] == BOX_ON_TARGET && room[row+n*2][col+m*2] == TARGET) {
            room[row+n][col+m] = PERSON_ON_TARGET;
            room[row+n*2][col+m*2] = BOX_ON_TARGET;
            room[row][col] = SPACE;
            while (k < 100) {
                if (allMoves[k] == '0' || allMoves[k] == '1') {
                    k = k+2;
                }
                else {
                    allMoves[k] = '1';
                    allMoves[k-1] = move;
                    k = 100;
                }
            }
        }
    }
}

int CheckGameOver(int room[ROWS][COLS]) {
    int i;
    int j;
    int anytarget = 0;
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            if (room[i][j] == TARGET || room[i][j] == BOX_ON_TARGET || room[i][j] == PERSON_ON_TARGET) {
                anytarget = 1;
            }
        }
    }
    if (anytarget == 0) {
        return 0;
    }
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            if (room[i][j] == TARGET || room[i][j] == PERSON_ON_TARGET) {
                return 0;
            }
        }
    }
    return 1;
}

void main(void)
{
char layout[200] = "111111153021103001100021111111";
char moves[100] = {0};
int room[ROWS][COLS];
InitialiseRoom(room, layout);
MakeMove(room, 'd', moves);
MakeMove(room, 'd', moves);
MakeMove(room, 'a', moves);
MakeMove(room, 's', moves);
MakeMove(room, 'a', moves);
MakeMove(room, 's', moves);
MakeMove(room, 'd', moves);
MakeMove(room, 'd', moves);
PrintRoom(room);
printf("Moves: %s", moves);
}