#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Function Prototypes
void displayRules();
void playNumGame(char userName[], int *deposit);
void playSlotMachine(char userName[], int *deposit);

int main(void)
{
    char userName[50];
    int deposit;
    int continuePlaying = 1; // Initialize to 1 to indicate the user wants to play initially

    printf("Please Enter Your Name: ");
    scanf("%s", userName);

    printf("Hello, %s! Welcome to the Casino.\n\n", userName);

    printf("Please read the Rules carefully before proceeding.\n");
    displayRules();

    printf("Please enter your initial deposit Amount: $");
    scanf("%d", &deposit);

    while (deposit > 0 && continuePlaying) 
    {
        printf("\nWhat would you like to Play, Sir ?\n");
    
        printf("\n1. Play Number Guessing Game\n");
        printf("2. Play Slot Machine\n");
        printf("3. Quit\n");

        printf("Enter your choice: ");
        int choice;
        scanf("%d", &choice);

        switch (choice) 
        {
            case 1:
                playNumGame(userName, &deposit); // Pass deposit by reference
                break;
            case 2:
                playSlotMachine(userName, &deposit); // Pass deposit by reference
                break;
            case 3:
                printf("Thank You, %s! See you next time.\n", userName);
                printf("Have a Good Day!\n");
                continuePlaying = 0; // Set continuePlaying to 0 to exit the loop
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
        
    }

    return 0;
}

// Function for displaying Rules
void displayRules()
{
    printf("------------------------------------------------------------------------------------------------------------\n");
    printf("Rules:\n");
    printf("------------------------------------------------------------------------------------------------------------\n");
    printf("1. You will start with a deposit amount.\n");
    printf("2. You can play two different games: Number Guessing and Slot Machine.\n");
    printf("3. In Number Guessing, you bet on a number between 1 and 10, and win double your bet if you guess correctly.\n");
    printf("4. In Slot Machine, you bet on a combination of symbols, and win a prize if you match a winning combination.\n");
    printf("5. The game continues until you run out of money or choose to quit.\n");
    printf("----------------------------------------------------------------------------------------------------------\n\n");

}

// Function for  playing Number Guessing Game
void playNumGame(char userName[], int *deposit) // Change deposit to pointer
{
    srand(time(NULL));   // Seed the random number generator
    int bet, guess, computerChoice;

    while (*deposit > 0) // Check the value pointed by deposit
    {
        printf("Your current balance is: $%d\n", *deposit);
        printf("Enter your bet (0 to quit): $");
        scanf("%d", &bet);

        if (bet <= 0) 
        {
            printf("Thank you for playing, %s! See you next time.\n", userName);
            printf("Have a Good Day!\n\n");
            break;
        }

        if (bet > *deposit) 
        {
            printf("Sorry! You can't bet more than your current balance, %s.\n", userName);
            printf("Please place your bet again: $\n");
            continue;
        }

        printf("Enter your guess (between 1 and 10): ");
        scanf("%d", &guess);

        if (guess < 1 || guess > 10) 
        {
            printf("Invalid guess! Please guess a number between 1 and 10, %s.\n", userName);
            continue;
        }

        computerChoice = rand() % 10 + 1;
        printf("The WINNER is number: %d\n", computerChoice);

        if (guess == computerChoice) 
        {
            printf("Congratulations! You won $%d, %s.\n\n", bet * 2, userName);
            *deposit += bet; // Double the bet amount is added to the deposit
        } 
        else 
        {
            printf("Sorry! You lost $%d, %s.\n\n", bet, userName);
            *deposit -= bet; // Subtract the bet amount from the deposit
        }
    }

    if (*deposit == 0)
    {
        printf("You ran out of Money!, %s.\n", userName);
        printf("You can't play anymore, Game Over\n");
        printf("Have a Good Day!\n");
        return;
    }

}

// Function for playing Slot Machine game
void playSlotMachine(char userName[], int *deposit) // Change deposit to pointer
{
    srand(time(NULL)); // Seed the random number generator
    int bet, i, matchCount;
    char symbols[3][10] = {"Cherry", "Bar", "Seven"};
    int payouts[3] = {10, 50, 100};

    while (*deposit > 0) // Check the value pointed by deposit
    {
        printf("Your current balance is: $%d\n", *deposit);
        printf("Enter your bet (0 to quit): $");
        scanf("%d", &bet);

        if (bet <= 0)
        {
            printf("Thank you for playing, %s! See you next time.\n", userName);
            printf("Have a Good Day!\n\n");
            break;
        }

        if (bet > *deposit)
        {
            printf("Sorry! You can't bet more than your current balance, %s.\n", userName);
            printf("Please place your bet again: $\n");
            continue;
        }

        printf("Spinning the Slot Machine...\n");
        for (i = 0; i < 3; i++)
        {
            int randomIndex = rand() % 3;
            printf("%s ", symbols[randomIndex]);
        }
        printf("\n");

        matchCount = 0;
        for (i = 0; i < 2; i++)
        {
            if (symbols[i][0] == symbols[i+1][0] && symbols[i][0] == symbols[i+2][0])
            {
                matchCount++;
            }
        }

        switch (matchCount)
        {
            case 1:
                printf("Sorry, no match! You lost $%d, %s.\n\n", bet, userName);
                *deposit -= bet;
                break;
            case 2:
                printf("Congratulations, you have a match! You won $%d, %s.\n\n", bet * 2, userName);
                *deposit += bet * 2;
                break;
            case 3:
                printf("Congratulations, you have a match! You won $%d, %s.\n\n", bet * 5, userName);
                *deposit += bet * 5;
                break;
            default:
                printf("Sorry, no match! You lost $%d, %s.\n\n", bet, userName);
                *deposit -= bet;
                break;
        }
    }

    if (*deposit == 0)
    {
        printf("Sorry! You ran out of money!, %s.\n", userName);
        printf("You can't play anymore, Game Over\n");
        printf("Have a Good Day!");
    }

}
