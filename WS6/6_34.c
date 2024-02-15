//Author: Anusri Chavali
//Date: 10/3/2023
//Purpose: Read int values into array and return message to determine whether the array contains all multiples of 10, no multiples of 10, or mixed values
#include <stdio.h>
#include <stdbool.h>

/* isArrayMult10 reads the values of inputVals and if they all are multiples of 10, the function returns true*/

bool IsArrayMult10(int inputVals[], int numVals)
{
   int count = 0;
   for(int i = 0; i < numVals; i++)
   {
      if(inputVals[i] % 10 == 0)
      {
         count++;
      }
   }
   if(count == numVals)
   {
      return true;
   }
   return false;
}

/* isArrayMult10 reads the values of inputVals and if none are multiples of 10, the function returns true*/
bool IsArrayNoMult10(int inputVals[], int numVals)
{
   int count = 0;
   for(int i = 0; i < numVals; i++)
   {
      if(inputVals[i] % 10 == 0)
      {
         count++;
      }
   }
   if(count == 0)
   {
      return true;
   }
   return false;
}

//the values of numVals and the array values are read in from stdin, then previously defined functions are 
int main(void) {

   /* read in first value as the number of values in the array, and read the rest of the values in inputVals*/
   int numVals;
   scanf("%d ", &numVals);
   int inputVals[numVals];
   for(int i = 0; i < numVals; i++)
   {
      scanf("%d ", &inputVals[i]);
   }
   
   //use the defined functions to determine which message to print
   if(IsArrayMult10(inputVals, numVals) == true)
   {
      printf("all multiples of 10\n");
   }
   else if(IsArrayNoMult10(inputVals, numVals) == true)
   {
      printf("no multiples of 10\n");
   }
   else
   {
      printf("mixed values\n");
   }
   
   return 0;
   
}