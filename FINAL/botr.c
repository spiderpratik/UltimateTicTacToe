#include <math.h>
#include <malloc.h>
#include "gameio.h"

// Who has to play
char player(char**** board) {
    int i, j, k, l;
    int x=0;
    for (i=0; i<3; i++) {
        for (j=0; j<3; j++) {
            for (k=0; k<3; k++) {
                for (l=0; l<3; l++) {
                    if (board[i][j][k][l] == 'X') x++;
                    else if (board[i][j][k][l] == 'O') x--;
                }
            }
        }
    }
    if (x) return 'O';
    else return 'X';
}

int main() {
    // Initialization
    int x, y;
    char**** board = input4D(&x, &y);
    int i, j, k;
    int play;       // play has the square in which the last move was made (values = 0 to 80)
    char turn = player(board);
    char** bigBoard = (char**) malloc(3*sizeof(char*));
    for (i=0; i<3; i++) {
        bigBoard[i] = (char*) malloc(3*sizeof(char));
        for (j=0; j<3; j++) {
            k=check3x3(board[i][j]);
            if (k == 2)
                bigBoard[i][j] = 'O';
            else if (k == 1)
                bigBoard[i][j] = 'X';
            else if (k == 0) bigBoard[i][j] = 'D';
            else bigBoard[i][j] = '.';
        }
    }

    if (x!=-1 && y!=-1 && bigBoard[x][y]!='.')
        x=y=-1;

    // Analysis

    //TODO: A lot of things here
    if (x == -1) {
        for (i=0; i<3; i++) {
            for (j=0; j<3; j++) {
                if (bigBoard[i][j] == '.') {
                    x=i;
                    y=j;
                }
            }
        }
    }
    
    for (i=0; i<3; i++) {
        for (j=0; j<3; j++) {
            if (board[x][y][i][j] == '.') {
                play = 9*(3*x+i)+(3*y+j);
                board[x][y][i][j] = turn;
                x=i;
                y=j;
                i=j=3;
            }
        }
    }

    // Output
    if (check3x3(board[x][y])!= -1) {
        x=y=-1;
    }
    output2file(board,x,y);

    free(bigBoard);
    return play;
}
