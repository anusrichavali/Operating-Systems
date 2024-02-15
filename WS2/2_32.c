/* Author: Anusri Chavali  Date: 9/5/2023  Purpose: Input integer values and display some key figures about real estate properties using the input values. */
#include <stdio.h>

int main(void)
{
    /*Declare and scan in 2 integer values to represent the current and previous month's price */
    int currentPrice;
    int lastMonthsPrice;

    scanf("%d", &currentPrice);
    scanf("%d", &lastMonthsPrice);

    /* Variable to hold the value of the computation of mortgage. */
    double mortgage = (currentPrice * 0.051) / 12;
    /* Print the information using the provided text format. The inputs should be 2 integers and one float value. */
    printf("This house is $%d. The change is $%d since last month.\nThe estimated monthly mortgage is $%0.6lf.\n.", currentPrice, currentPrice - lastMonthsPrice, mortgage);
    return 0;
}