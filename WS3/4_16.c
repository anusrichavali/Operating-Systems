/*Author: Anusri Chavali  Date: 9/16/2023  Purpose: takes in as many user inputs as the user provides, then returns the maximum value and average of the user inputs*/
#include <stdio.h>

int main(void)
{
    int num;
    int count = 0;
    int max = -1;
    double sum;
    /*If scanf successfully receives a value, it returns 1, so as long as it returns 1, we keep scanning values*/
    while(scanf("%d", &num) == 1)
    {
        /*if the input value is nonnegative, add it to our user input sum and incrememnt the count, update max*/
        if(num > 0)
        {
            sum += num;
            count++;
            if(max < num)
            {
                max = num;
            }
        } 
        /* leave the input loop if the input is negative */
        else
        {
            break;
        }  
    }

    /*return max and the average w/ 2 decimal places*/
    printf("%d %0.2lf\n", max, sum/count);
    return 0;
}