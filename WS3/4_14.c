/* Author: Anusri Chavali  Date: 9/16/2023  Purpose: This program scans a user input and returns the reverse binary representation*/
#include <stdio.h>

int main(void){
    int x;
    scanf("%d", &x);

    /*prints the remainder of x/2 until int x is no longer a positive int*/
    while(x > 0)
    {
        printf("%d", x%2);
        x /= 2;
    }

    printf("\n");

    return 0;
}