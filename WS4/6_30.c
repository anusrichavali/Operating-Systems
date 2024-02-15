/*Author: Anusri Chavali
Date: 09/19/2023
Purpose: Define 2 functions to get the max of 4 numbers and min of 4 numbers and use both to get the max and min of 4 user input values*/
#include <stdio.h>

/* Pass in 4 integers as arguments and compare each until the maximum is returned */ 
int MaxNumber(int num1, int num2, int num3, int num4)
{
   int vals[4] = {num1, num2, num3, num4};
   int max = num1;
   /* iterate through the structure storing the ints and update max as necessary to print at the end */
   for(int i = 1; i < 4; i++)
   {
      if(vals[i] > max)
      {
         max = vals[i];
      }
   }
   return max;
}

/* Pass in 4 integers as arguments and compare each until the minimum is returned */ 
int MinNumber(int num1, int num2, int num3, int num4)
{
   int vals[4] = {num1, num2, num3, num4};
   int min = num1;
   /* iterate through the structure storing the ints and update max as necessary to print at the end */
   for(int i = 1; i < 4; i++)
   {
      if(vals[i] < min)
      {
         min = vals[i];
      }
   }
   return min;
}

int main(void) {

   /* Add the 4 user input values into na array */
   int v[4];
   for(int i = 0; i < 4; i++)
   {
      int num;
      scanf("%d", &num);
      v[i] = num;
   }
   
   /*print the max and min values of the user inputs by calling the defined functions on the int array*/
   printf("Maximum is %d\n", MaxNumber(v[0], v[1], v[2], v[3]));
   printf("Minimum is %d\n", MinNumber(v[0], v[1], v[2], v[3]));
   

   return 0;
}