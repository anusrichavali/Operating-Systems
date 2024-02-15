/* Author: Anusri Chavali
Date: 09/27/2022
Purpose: Reads in an input and returns the count of non space, non period, non comma, non eclamation mark characters*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(void) {
   
   /* Initialize an array for the string and read in the string from stdin */
   char str[50];
   scanf("%[^\n]", str);
   
   //iterate through a while loop for each non-null character in string array
   //if they are not one of the sepcified non-counted characters, the count is updated
   int count = 0;
   int i = 0;
   while(str[i] != '\0')
   {
      if(str[i] != ' ' && str[i] != '.' && str[i] != ',' && str[i] != '!')
      {
         count++;
      }
      i++;
   }
   
   //print the count
   printf("%d\n", count);
   return 0;
}