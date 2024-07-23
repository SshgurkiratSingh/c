#include <stdio.h>

#define SIZE 3

void initializeBoard(char board[][SIZE]);
void printBoard(char board[][SIZE]);
int checkWin(char board[][SIZE]);
void playerTurn(char board[][SIZE], char player);
int isBoardFull(char board[][SIZE]);

int main() {
    char board[SIZE][SIZE];
    int currentPlayer = 0;
    char players[2] = {'X', 'O'};
    int winner = 0;

    initializeBoard(board);

    while(1) {
        printBoard(board);
        playerTurn(board, players[currentPlayer]);
        winner = checkWin(board);

        if (winner != 0 || isBoardFull(board)) {
            break;
        }

        currentPlayer = 1 - currentPlayer; // Switch player
    }

    printBoard(board);

    if (winner != 0) {
        printf("Player %d wins!\n", winner);
    } else {
        printf("It's a draw!\n");
    }

    return 0;
}

void initializeBoard(char board[][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = ' ';
        }
    }
}

void printBoard(char board[][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf(" %c ", board[i][j]);
            if (j < SIZE - 1) printf("|");
        }
        printf("\n");
        if (i < SIZE - 1) printf("---+---+---\n");
    }
}

void playerTurn(char board[][SIZE], char player) {
    int x, y;

    do {
        printf("Player %c, enter row and column (0-2): ", player);
        scanf("%d%d", &x, &y);
    } while (x < 0 || x >= SIZE || y < 0 || y >= SIZE || board[x][y] != ' ');

    board[x][y] = player;
}

int checkWin(char board[][SIZE]) {
    // Check rows, columns, and diagonals for a win
    for (int i = 0; i < SIZE; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ') {
            return board[i][0] == 'X' ? 1 : 2;
        }

        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != ' ') {
            return board[0][i] == 'X' ? 1 : 2;
        }
    }

    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ') {
        return board[0][0] == 'X' ? 1 : 2;
    }

    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' ') {
        return board[0][2] == 'X' ? 1 : 2;
    }

    return 0;
}

int isBoardFull(char board[][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == ' ') {
                return 0;
            }
        }
    }
    return 1;
}
