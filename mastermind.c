#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define CODE_LENGTH 4
#define NUM_COLORS 5
#define MAX_GUESSES 10

void generateSecretCode(int secretCode[]);
void getGuess(int guess[]);
int checkGuess(int secretCode[], int guess[]);

int main() {
    srand(time(NULL));

    int secretCode[CODE_LENGTH];
    int guess[CODE_LENGTH];
    int attemptCount = 0;

    generateSecretCode(secretCode);

    printf("Welcome to Mastermind!\n");
    printf("Try to guess the 4-color secret code using the following colors:\n");
    printf("0 - Red, 1 - Green, 2 - Blue, 3 - Yellow, 4 - Purple\n");

    while (attemptCount < MAX_GUESSES) {
        getGuess(guess);
        attemptCount++;

        int result = checkGuess(secretCode, guess);

        if (result == CODE_LENGTH) {
            printf("Congratulations! You guessed the secret code in %d attempts.\n", attemptCount);
            break;
        } else {
            printf("Incorrect guess. %d colors are in the correct position, and %d colors are correct but in the wrong position.\n", result / 10, result % 10);
        }
    }

    if (attemptCount == MAX_GUESSES) {
        printf("Sorry, you've reached the maximum number of attempts. The secret code was: ");
        for (int i = 0; i < CODE_LENGTH; i++) {
            printf("%d ", secretCode[i]);
        }
        printf("\n");
    }

    return 0;
}

void generateSecretCode(int secretCode[]) {
    for (int i = 0; i < CODE_LENGTH; i++) {
        secretCode[i] = rand() % NUM_COLORS;
    }
}

void getGuess(int guess[]) {
    printf("Enter your guess (4 space-separated colors): ");
    for (int i = 0; i < CODE_LENGTH; i++) {
        scanf("%d", &guess[i]);
    }
}

int checkGuess(int secretCode[], int guess[]) {
    int correctPositionCount = 0;
    int correctColorCount = 0;

    for (int i = 0; i < CODE_LENGTH; i++) {
        if (guess[i] == secretCode[i]) {
            correctPositionCount++;
        } else {
            for (int j = 0; j < CODE_LENGTH; j++) {
                if (j != i && guess[i] == secretCode[j]) {
                    correctColorCount++;
                    break;
                }
            }
        }
    }

    return correctPositionCount * 10 + correctColorCount;
}
