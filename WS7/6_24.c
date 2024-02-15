//Author: Anusri Chavali
//Date Last Modified: 10/13/2023
//Purpose: Swaps values based on reference to integer pointers

#include <stdio.h>

/* Function which stores the values from the pointer in temporary variables and then swaps*/ 
//Swaps 4 values
//Prints the swapped values
void SwapValues(int* userVal1, int* userVal2, int* userVal3, int* userVal4)
{
   int temp = *userVal1;
   int temp2 = *userVal3;
   *userVal1 = *userVal2;
   *userVal2 = temp;
   *userVal3 = *userVal4;
   *userVal4 = temp2;
   printf("%d %d %d %d\n", *userVal1, *userVal2, *userVal3, *userVal4);

}
//Scans 4 input values and stores them in pointers to pass into SwapValues
int main(void) {
   int a, b, c, d;
   int* a1;
   int* b1;
   int* c1;
   int* d1;
   scanf("%d %d %d %d\n", &a, &b, &c, &d);
   a1 = &a;
   b1 = &b;
   c1 = &c;
   d1 = &d;
   SwapValues(a1, b1, c1, d1);

   return 0;
}