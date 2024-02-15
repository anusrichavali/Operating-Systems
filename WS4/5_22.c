/*Author: Anusri Chavali
Date: 9/19/2023
Purpose: Read in a series of strings from user input and return the list of strings containing a specified letter */
#include <stdio.h>
#include <string.h>

int main(void) {

   /* Initialize the words array and its count*/
   int count;
   scanf("%d", &count);
   char arr[20][10];
   /*Add all user input strings into the array*/
   for(int i = 0; i < count; i++)
   {
      char str[10];
      scanf("%s", &str);
      strcpy(arr[i], str);
   }
   /*Read in the last user input as the character to look for in the strings*/
   char ch;
   scanf(" %c", &ch);
   
   /*Iterate through the array and use strchr to check if a character appears in the string; print all strings where strchr returns a pointer value to the character in the string*/
   for(int i = 0; i < count; i++)
   {
      if(strchr(arr[i], ch) != NULL)
      {
         printf("%s,", arr[i]);
      }
   }
   
   printf("\n");
   return 0;
}