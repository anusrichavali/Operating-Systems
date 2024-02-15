/*Author: Anusri Chavali  Date: 09/16/2023  Purpose: Return user input values which are between a specified range*/
#include <stdio.h>

int main(void)
{
    const int NUM_ELEMENTS = 20;
    int userValues[NUM_ELEMENTS];

    /*Initialize values to determine size of user input array, then fill array with user input values*/
    int count = 0;
    int limit;
    scanf("%d", &limit);
    int num;
    while(count < limit)
    {
        scanf("%d", &num);
        userValues[count] = num;
        count++;
    }

    /*Read in user input to specify bounds of the range*/
    int lower, upper;
    scanf("%d", &lower);
    scanf("%d", &upper);
    /*Iterate through array and print values which are within the range*/
    for(int i = 0; i < count; i++)
    {
        int a = userValues[i];
        if(a >= lower && a <= upper)
        {
            printf("%d,", a);
        }
    }
    printf("\n");

    return 0;
}