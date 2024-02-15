//Author: Anusri Chavali
//Date: 10/23/2023
//Purpose: Count the number of times a user input character appears in a user input string

#include <stdio.h>
#include <string.h>

/* Returns the number of times a character appears in a string */
int CalcNumCharacters(char* userString, char userChar)
{
   int count = 0;
   for(int i = 0; i < strlen(userString); i++)
   {
      if(userString[i] == userChar)
      {
         count++;
      }
   }
   
   return count;
}

int main(void) {

   /* Scan in user input string and character */
   char userString[50];
   char userChar;
   scanf("%c %s", &userChar, userString);
   
   //store the value returned by the character counter function in a variable
   int count = CalcNumCharacters(userString, userChar);
   
   //return appropriate message
   if(count == 1)
   {
      printf("%d %c\n", count, userChar);
   }
   else
   {
      printf("%d %c's\n", count, userChar);
   }

   return 0;
}

