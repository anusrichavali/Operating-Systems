/* Author: Anusri Chavali - Date: 08/28/2023 - Purpose: Perform different operations on a user-input integer.. */
#include <stdio.h>

int main(void)
{
    /* Initialize two user input integers*/
    int userNum;
    int userNum2;

    /* Prompt and scan first user-input integer. */
    printf("Enter integer:\n");
    scanf("%d", &userNum);
    /* Perform different operations and print the result using %d formatting */
    printf("You entered: %d\n", userNum);
    printf("%d squared is %d\n", userNum, userNum * userNum);
    printf("And %d cubed is %d!!\n", userNum, userNum * userNum * userNum);
    /*Prompt and scan second user-input integer*/
    printf("Enter another integer:\n");
    scanf("%d", &userNum2);
    /*Perform different operations with both user-input integers and print the result using %d formatting */
    printf("%d + %d is %d\n", userNum, userNum2, userNum + userNum2);
    printf("%d * %d is %d\n", userNum, userNum2, userNum * userNum2);

    return 0;
}