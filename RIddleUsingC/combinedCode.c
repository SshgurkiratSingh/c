#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "cchalk.c"
#define MAX_RIDDLES 13
#define SIZE 3
const char *riddles[MAX_RIDDLES] = {
    "What has keys but can't open locks?",
    "What is always in front of you but can't be seen?",
    "What has words, but never speaks?",
    "I’m tall when I’m young, and I’m short when I’m old. What am I?",
    "What can travel around the world while staying in a corner?",
    "What has a head, a tail, is brown, and has no legs?",

    "David's father has three sons: Snap, Crackle, and _____?",
    "I speak without a mouth and hear without ears. I have no body, but I come alive with the wind. What am I?",
    "What is seen in the middle of March and April that can’t be seen at the beginning or end of either month?",
    "What English word has three consecutive double letters?",
    "I have cities, but no houses. I have mountains, but no trees. I have water, but no fish. What am I?"};

const char *answers[MAX_RIDDLES] = {
    "keyboard",
    "future",
    "book",
    "candle",
    "stamp",
    "coin",
    "David",
    "echo",
    "R",
    "bookkeeper",
    "map"};
int asked[MAX_RIDDLES] = {0};

char board[SIZE][SIZE];
char players[2] = {'X', 'O'};
void initializeBoard();
void printBoard();
void playerTurn(char player);
int checkWin();
int isBoardFull();
void getRiddle(int *riddleIndex);
int answerRiddle(int riddleIndex);
int main()
{
    srand(time(NULL));
    initializeBoard();

    int currentPlayer = 0;
    int riddleIndex;
    int winner = 0;

    while (1)
    {
        getRiddle(&riddleIndex);
        chalk_printf_ln(CHALK_BRIGHT_CYAN, "Player %c, answer this riddle for your turn:", players[currentPlayer]);
        printf("%s\n", riddles[riddleIndex]);

        if (answerRiddle(riddleIndex))
        {
            printBoard();
            playerTurn(players[currentPlayer]);
            winner = checkWin();

            if (winner != 0 || isBoardFull())
            {
                break;
            }
        }
        else
        {
            chalk_printf_background_ln(CHALK_BLACK, CHALK_WHEAT1, "Incorrect answer or skipped. Turn passes.");
        }

        currentPlayer = 1 - currentPlayer; // Switch player
    }

    printBoard();

    if (winner != 0)
    {
        chalk_printf_ln(CHALK_DARKRED, "Player %c wins!", players[winner - 1]);
    }
    else
    {
        chalk_printf_ln(CHALK_DARKVIOLET_1, "It's a draw!");
    }

    return 0;
}
void initializeBoard()
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            board[i][j] = ' ';
        }
    }
}

void printBoard()
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            printf(" %c ", board[i][j]);
            if (j < SIZE - 1)
                printf("|");
        }
        printf("\n");
        if (i < SIZE - 1)
            printf("---+---+---\n");
    }
}

void playerTurn(char player)
{
    int x, y;
    do
    {
        printf("Player %c, enter row and column (0, 1, 2): ", player);
        scanf("%d%d", &x, &y);
    } while (x < 0 || x >= SIZE || y < 0 || y >= SIZE || board[x][y] != ' ');
    board[x][y] = player;
}

int checkWin()
{
    // Rows and columns
    for (int i = 0; i < SIZE; i++)
    {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ')
        {
            return board[i][0] == 'X' ? 1 : 2;
        }
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != ' ')
        {
            return board[0][i] == 'X' ? 1 : 2;
        }
    }
    // Diagonals
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ')
    {
        return board[0][0] == 'X' ? 1 : 2;
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' ')
    {
        return board[0][2] == 'X' ? 1 : 2;
    }
    return 0;
}

int isBoardFull()
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (board[i][j] == ' ')
            {
                return 0;
            }
        }
    }
    return 1;
}

void getRiddle(int *riddleIndex)
{
    int unaskedRiddles = 0;
    for (int i = 0; i < MAX_RIDDLES; i++)
    {
        if (asked[i] == 0)
        {
            unaskedRiddles++;
        }
    }

    if (unaskedRiddles == 0)
    {
        *riddleIndex = -1; // No more riddles to ask
        return;
    }

    do
    {
        *riddleIndex = rand() % MAX_RIDDLES;
    } while (asked[*riddleIndex] == 1);

    asked[*riddleIndex] = 1;
}

int answerRiddle(int riddleIndex)
{
    if (riddleIndex == -1)
    {
        printf("No more riddles. You get a free turn.\n");
        return 1; // Free turn if no riddles left
    }

    char answer[100];
    printf("Answer: ");
    scanf("%s", answer);

    if (strcmp(answer, answers[riddleIndex]) == 0)
    {
        printf("Correct! You get to play.\n");
        return 1;
    }

    printf("Incorrect! Turn passes.\n");
    return 0;
}

// int main()
// {
//     srand(time(NULL));
//     initializeBoard();

//     int currentPlayer = 0;
//     int riddleIndex;
//     int winner = 0;

//     while (1)
//     {
//         getRiddle(&riddleIndex);
//         printf("\nPlayer %c, answer this riddle for your turn:\n", players[currentPlayer]);
//         if (riddleIndex != -1)
//         {
//             printf("%s\n", riddles[riddleIndex]);
//         }

//         if (answerRiddle(riddleIndex))
//         {
//             printBoard();
//             playerTurn(players[currentPlayer]);
//             winner = checkWin();

//             if (winner != 0 || isBoardFull())
//             {
//                 break;
//             }
//         }
//         else
//         {
//             printf("Incorrect answer or skipped. Turn passes.\n");
//         }

//         currentPlayer = 1 - currentPlayer; // Switch player
//     }

//     printBoard();

//     if (winner != 0)
//     {
//         printf("Player %c wins!\n", players[winner - 1]);
//     }
//     else
//     {
//         printf("It's a draw!\n");
//     }

//     return 0;
// }
