/*Author: Anusri Chavali  Date: 9/16/2023  Purpose: Output user inputs in reverse order*/
#include <stdio.h>

int main(void)
{
    const int NUM_ELEMENTS = 20;
    int userVals[NUM_ELEMENTS];

    /* make count 0, take the first user input as the number of integers which will follow*/
    int count = 0;
    int limit;
    scanf("%d", &limit);
    int num;
    /* take in specified number of values, and add them to the array and increment count*/
    while(count < limit)
    {
        userVals[count] = num;
        count++;
    }

    /* iterate through array in reverse order and print the values*/
    for(int i = count - 1; i >= 0; i--)
    {
        printf("%d,", userVals[i]);
    }
    printf("\n");

    return 0;
}