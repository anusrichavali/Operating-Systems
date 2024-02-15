/* Author: Anusri Chavali  Date: 09/16/2023  Purpose: Return user input values which are below a specified threshold*/
#include <stdio.h>

int main(void)
{
    const int NUM_ELEMENTS = 20;
    int userValues[NUM_ELEMENTS];

    /*Initialize count and limit to determine array size*/
    int count = 0;
    int limit;
    scanf("%d", &limit);
    int num;
    /*Read in limit number of user values and add to array*/
    while(count <= limit)
    {
        scanf("%d", &num);
        userValues[count] = num;
        count++;
    }

    /*Assign last value of user input as threshold and return only values in the array which are below threshold*/
    int threshold = userValues[count - 1];
    for(int i = 0; i < count - 1; i++)
    {
        if(userValues[i] < threshold)
        {
            printf("%d,", userValues[i]);
        }
    }
    printf("\n");

    return 0;
}