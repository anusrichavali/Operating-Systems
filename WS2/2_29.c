/*Author: Anusri Chavali  Date: 09/05/2023  Purpose: Take 3 double input values and perform various operations on them. */
#include <stdio.h>
#include <math.h>

int main(void)
{
    /* Declare and assign variables to user input values. */
    double x;
    double y;
    double z;
    scanf("%lf", &x);
    scanf("%lf", &y);
    scanf("%lf", &z);

    /* Perform and print various operations using exponents, absolute value for float, and square root. */
    printf("%0.2lf ", pow(x, z));
    printf("%0.2lf ", pow(x, pow(y, 2)));
    printf("%0.2lf ", fabs(y));
    printf("%0.2lf ", sqrt(pow(x * y, z)));

    return 0;
}