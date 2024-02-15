#include <stdio.h>

int main(void)
{
    int x, y, z;
    /* Take the 3 integer inputs. */
    printf("Enter 3 integers.\n");
    scanf("%d", &x);
    scanf("%d", &y);
    scanf("%d", &z);

    /*Find the minimum value of the 3 inputs using if statements and assign to a minimum variable.*/
    int min;
    if (x > y & y < z)
    {
        min = y;
    }
    else if (y > x & x < z)
    {
        min = x;
    }
    else
    {
        min = z;
    }
    /*print the minimum value*/
    printf("%d\n", min);
    return 0;
}