/*Author: Anusri Chavali  Date: 9/5/2023  Purpose: Take user input values and perform and print division operations. */
#include <stdio.h>

int main(void)
{
    /* Scan in 2 user input values as the value and value to divide by. */
    int userNum;
    int divNum;
    scanf("%d", &userNum);
    scanf("%d", &divNum);
    /* Use a loop to divide the values by the dividing value 3 times */
    for (int i = 0; i < 3; ++i)
    {
        userNum = userNum / divNum;
        printf("%d ", userNum);
    }

    return 0;
}