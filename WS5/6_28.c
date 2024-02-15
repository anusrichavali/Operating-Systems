/*Author: Anusri Chavali
Date: 9/27/2023
Purpose: Take a user input string and output the string without any of the alphanumeric characters */
#include <stdio.h>
#include <string.h>
#include <ctype.h>

//The function reads all non-null characters of the input string and only appends alphabet chars to AlphaOnly
void RemoveNonAlpha(char userString[], char userStringAlphaOnly[])
{
   int i = 0;
   while(userString[i] != 0)
   {
      if(isalpha(userString[i]))
      {
         strncat(userStringAlphaOnly, &userString[i], 1);
      }
      i++;
   }
   
   //print the alphabet only string
   printf("%s\n", userStringAlphaOnly); 
}

int main(void) {

   /* A string input, with spaces, is read in from stdin */
   char input[50] = {0};
   char onlyAlpha[50] = {0};
   fgets(input, 50, stdin);
   
   //the function is called on the input string and the alpha only is printed out from defined function
   RemoveNonAlpha(input, onlyAlpha);

   return 0;
}