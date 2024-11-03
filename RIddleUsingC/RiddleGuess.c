#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_RIDDLES 5
#define MAX_ATTEMPTS 3
#define HIGH_SCORE_FILE "highscore.txt"
int askedRiddlesCount = 0;
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
int asked[MAX_RIDDLES] = {0}; // To keep track of asked riddles
void readHighScore(int *highScore, char *highScorer)
{
    FILE *file = fopen(HIGH_SCORE_FILE, "r");
    if (file != NULL)
    {
        fscanf(file, "%d\n%s", highScore, highScorer);
        fclose(file);
    }
    else
    {
        *highScore = 0;
        strcpy(highScorer, "No one yet");
    }
}

void writeHighScore(int highScore, const char *highScorer)
{
    FILE *file = fopen(HIGH_SCORE_FILE, "w");
    if (file != NULL)
    {
        fprintf(file, "%d\n%s", highScore, highScorer);
        fclose(file);
    }
}

void getRiddle(int *riddleIndex)
{
    if (askedRiddlesCount >= MAX_RIDDLES)
    {
        return; // All riddles have been asked
    }

    do
    {
        *riddleIndex = rand() % MAX_RIDDLES;
    } while (asked[*riddleIndex] == 1);
    asked[*riddleIndex] = 1; // Mark as asked
    askedRiddlesCount++;     // Increment the count of asked riddles
}

void displayEndScreen(int score, int attemptsMade)
{
    printf("\n--- Game Over ---\n");
    printf("Final Score: %d\n", score);
    printf("Total Attempts Made: %d\n", attemptsMade);
    printf("Riddles Answered: %d out of %d\n", score, MAX_RIDDLES);
    // Add more statistics if desired
}
void clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    // Assume POSIX
    printf("\033[H\033[J");
#endif
}

int main()
{
    srand(time(NULL)); // Seed for random number generation

    char username[50];
    int score = 0, highScore = 0;
    char highScorer[50] = "No one yet";
    int attempts = MAX_ATTEMPTS, attemptsMade = 0;
    char answer[100];
    int riddleIndex;
    readHighScore(&highScore, highScorer);

    printf("Enter your username: ");
    scanf("%s", username);

    // Game loop
    while (attempts > 0 && askedRiddlesCount < MAX_RIDDLES)
    {
        getRiddle(&riddleIndex);

        if (askedRiddlesCount == MAX_RIDDLES)
        {
            printf("All riddles have been asked.\n");
            break;
        }

        printf("\nRiddle: %s\n", riddles[riddleIndex]);
        printf("Your answer (type '0' to skip): ");
        scanf("%s", answer);

        attemptsMade++;

        if (strcmp(answer, "0") == 0)
        {
            attempts--;
            printf("Skipped! Attempts left: %d\n", attempts);
            continue;
        }

        if (strcmp(answer, answers[riddleIndex]) == 0)
        {
            score++;
            printf("Correct! Your score: %d\n", score);
        }
        else
        {
            attempts--;
            printf("Wrong! Attempts left: %d\n", attempts);
        }

        if (score > highScore)
        {
            highScore = score;
            strcpy(highScorer, username);
            writeHighScore(score, username);
        }

        if (attempts == 0 || score == MAX_RIDDLES)
        {
            break; // Exit loop if attempts are over or all riddles are answered
        }
        clearScreen();
    }

    displayEndScreen(score, attemptsMade);

    printf("\nHigh score by %s: %d\n", highScorer, highScore);

    return 0;
}
