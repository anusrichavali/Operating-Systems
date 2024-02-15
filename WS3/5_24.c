/*Author: Anusri Chavali  Date: 09/16/2023  Purpose: Return the two smallest numbers in a user input array*/
#include <stdio.h>

int main(void)
{
    const int NUM_ELEMENTS = 20;
    int userValues[NUM_ELEMENTS];

    /*Initalize values to determine the length of the array, and read in user input values to fill the array*/
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

    /*Iterate through the array and find the smallest and second smallest values*/
    int min = userValues[0];
    int min2 = userValues[count - 1];
    for(int i = 0; i < count; i++)
    {
        if(userValues[i] < min)
        {
            min2 = min;
            min = userValues[i];
        }
        
        if(userValues[i] < min2 && userValues[i] > min)
        {
            min2 = userValues[i];
        }
    }
    /*print the two smallest values*/
    printf("%d and %d\n", min, min2);

    return 0;
}