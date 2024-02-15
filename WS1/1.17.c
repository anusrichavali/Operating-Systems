/* Author: Anusri Chavali - Date: 8/28/2023 - Purpose: Print a right-facing arrow using 2 user input integers*/
#include <stdio.h>

int main(void)
{
    int baseInt;
    int headInt;
    // Scan 2 integers which the users will put in as the base and head integer
    scanf("%d", &baseInt);
    scanf("%d", &headInt);

    /* Print out values in the integer format on 7 lines in order to generate a right facing arrow */
    printf("    %d\n", headInt);
    printf("    %d%d\n", headInt, headInt);
    printf("%d%d%d%d%d%d%d\n", baseInt, baseInt, baseInt, baseInt, headInt, headInt, headInt);
    printf("%d%d%d%d%d%d%d%d\n", baseInt, baseInt, baseInt, baseInt, headInt, headInt, headInt, headInt);
    printf("%d%d%d%d%d%d%d\n", baseInt, baseInt, baseInt, baseInt, headInt, headInt, headInt);
    printf("    %d%d\n", headInt, headInt);
    printf("    %d\n", headInt);

    return 0;
}
