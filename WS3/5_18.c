/* Author: Anusri Chavali  Date: 09/16/2023  Purpose: Return the middle value of an array of user inputs*/
#include <stdio.h>

int main(void)
{
    const int NUM_ELEMENTS = 9;
    int userValues[NUM_ELEMENTS];

    /* Initialize count to 0*/
    int count = 0;
    int num;
    /*Scan user values as long as the user inputs 1 values*/
    while(scanf("%d", &num)==1)
    {
        /*If more than 9 values entered, return error message and leave program*/
        if(count > 9)
        {
            printf("Too many numbers\n");
            return 1;
        }

        /*only add positive values to the array; break to printing if input is negative*/
        if(num < 0)
        {
            break;
        }

        userValues[count] = num;
        count++;
    }

    /*calculate the middle index of the non-empty array and print*/
    if(count > 0)
    {
        int mid = count/2;
        printf("Middle item: %d\n", userValues[mid]);
    }

    return 0;
}