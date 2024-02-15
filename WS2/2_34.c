/*Author: Anusri Chavali  Date: 9/5/2023  Purpose: Take an input username and print a personalized welcome message. */
#include <stdio.h>

int main(void)
{
    /* Declare and accept a char user input for the username. */
    char userName[50];

    scanf("%s", userName);
    /* Print a personalized message using the input username. */
    printf("Hey %s!\nWelcome to zyBooks!\n", userName);

    return 0;
}