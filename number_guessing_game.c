#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <unistd.h>
#include <windows.h>

#define MAX_GUESS 10
#define RANGE_MIN 1
#define RANGE_MAX 100

int main()
{
    int guess, targetNum, nGuess = 0;

    srand(time(0));
    targetNum = (rand() % (RANGE_MAX - RANGE_MIN + 1)) + RANGE_MIN;

    printf("Welcome to the number guessing game\n");
    printf("I have chosen a number between %d and %d.!\n", RANGE_MIN, RANGE_MAX);
    while (nGuess < MAX_GUESS)
    {
        printf("Write your guess (attempts %d/%d): ", nGuess + 1, MAX_GUESS);
        scanf("%d", &guess);
        if (guess == targetNum)
        {
            printf("Congratulation! You have guessed the right number after %d attempts and it's %d\n", nGuess + 1, targetNum);
            break;
        } else if (guess < targetNum)
        {
            printf("Too low, try again!\n");
        } else
        {
            printf("Too high, try again!\n");
        }
        nGuess++;
    }
        if (nGuess > MAX_GUESS) 
        {
            printf("Sorry you run our of guesses! The correct number is %d\n", targetNum);
        }
    return 0;
}